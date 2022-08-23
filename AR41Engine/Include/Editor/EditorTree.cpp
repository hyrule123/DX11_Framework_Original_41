
#include "EditorTree.h"

CEditorTree::CEditorTree()	:
	m_Root(nullptr)
{
}

CEditorTree::~CEditorTree()
{
	SAFE_DELETE(m_Root);
}

void CEditorTree::AddItem(const std::string& Item, const std::string& ParentItem)
{

	//Ʈ���� ������� ���(��Ʈ��尡 ���� ���)
	if (!m_Root)
	{
		m_Root = new CEditorTreeItem;

		m_Root->m_Item = Item;

		TCHAR	wText[256] = {};

		int Length = (int)MultiByteToWideChar(CP_ACP, 0, Item.c_str(), -1, nullptr, 0);

		MultiByteToWideChar(CP_ACP, 0, Item.c_str(), -1, wText, Length);

		char	TextUTF8[256] = {};

		Length = WideCharToMultiByte(CP_UTF8, 0, wText, -1, nullptr, 0, nullptr, nullptr);

		WideCharToMultiByte(CP_UTF8, 0, wText, -1, TextUTF8, Length, nullptr, nullptr);

		m_Root->m_ItemUTF8 = TextUTF8;

		m_Root->SetSelectCallback<CEditorTree>(this, &CEditorTree::NodeSelect);
	}

	//Ʈ���� �ϳ��� ���� ���
	else
	{
		// Root�� ��ü�� ���
		if (ParentItem == "")
		{
			CEditorTreeItem* NewItem = new CEditorTreeItem;
			NewItem->m_Item = Item;

			TCHAR	wText[256] = {};

			int Length = (int)MultiByteToWideChar(CP_ACP, 0, Item.c_str(), -1, nullptr, 0);

			MultiByteToWideChar(CP_ACP, 0, Item.c_str(), -1, wText, Length);

			char	TextUTF8[256] = {};

			Length = WideCharToMultiByte(CP_UTF8, 0, wText, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_UTF8, 0, wText, -1, TextUTF8, Length, nullptr, nullptr);

			NewItem->m_ItemUTF8 = TextUTF8;

			NewItem->m_SelectCallback = m_Root->m_SelectCallback;
			NewItem->AddItem(m_Root);

			m_Root = NewItem;
		}

		//��Ʈ�� ��ü���� ���� ���
		else
		{
			// �θ� �������� ã�´�.
			CEditorTreeItem* Parent = m_Root->FindItem(ParentItem);

			if (Parent)
				Parent->AddItem(Item);
		}
	}
}

void CEditorTree::DeleteItem(const std::string& Item)
{
	if (!m_Root)
		return;

	CEditorTreeItem* Find = m_Root->FindItem(Item);

	if (!Find)
		return;

	CEditorTreeItem* Parent = Find->m_Parent;

	// ��Ʈ����� ��� ������ �ִ� ù��° �������� ��Ʈ�� �������ش�.
	if (!Parent)
	{
		// ��Ʈ��� �ϳ� �������� ����ٴ� �ǹ��̴�.
		if (m_Root->m_vecChild.empty())
		{
			SAFE_DELETE(m_Root);
		}

		else
		{
			CEditorTreeItem* Root = m_Root->m_vecChild[0];

			size_t	Size = m_Root->m_vecChild.size();

			for (size_t i = 1; i < Size; ++i)
			{
				Root->AddItem(m_Root->m_vecChild[i]);
			}

			m_Root->m_vecChild.clear();

			Root->m_Parent = nullptr;

			SAFE_DELETE(m_Root);

			m_Root = Root;
		}
	}

	// ��Ʈ�� �ƴ� ���
	else
	{
		//���� ã�� ����� �θ� ��忡�� ã�� ��带 �����Ѵ�.
		size_t Size = Parent->m_vecChild.size();
		for (size_t i = 0; i < Size; ++i)
		{
			if (Parent->m_vecChild[i] == Find)
			{
				auto iter = Parent->m_vecChild.begin() + i;
				Parent->m_vecChild.erase(iter);

				break;
			}
		}


		Size = Find->m_vecChild.size();

		for (size_t i = 0; i < Size; ++i)
		{
			Parent->m_vecChild.push_back(Find->m_vecChild[i]);
		}
		Find->m_vecChild.clear();


		SAFE_DELETE(Find);
	}
}

void CEditorTree::Clear()
{
	if (m_Root)
	{
		m_Root->Clear();
		SAFE_DELETE(m_Root);
	}
}

bool CEditorTree::Init()
{
	return true;
}

void CEditorTree::Render()
{
	if (!m_Root)
		return;

	m_Root->Render();
}

void CEditorTree::NodeSelect(CEditorTreeItem* Node, const std::string& Item)
{
	if (m_SelectCallback)
		m_SelectCallback(Item);
}
