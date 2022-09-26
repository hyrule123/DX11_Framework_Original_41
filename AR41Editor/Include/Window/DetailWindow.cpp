#include "DetailWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorCheckbox.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Engine.h"
#include "PathManager.h"
#include "Animation/Animation2D.h"
#include "Resource/Animation/AnimationSequence2D.h"




CDetailWindow::CDetailWindow()
{
}

CDetailWindow::~CDetailWindow()
{
	ClearWidget();

	{
		size_t	Size = m_vecSceneComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecSceneComponent[i]);
		}

		m_vecSceneComponent.clear();
	}

	{
		size_t	Size = m_vecSpriteComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecSpriteComponent[i]);
		}

		m_vecSpriteComponent.clear();
	}

	{
		size_t	Size = m_vecCameraComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecCameraComponent[i]);
		}

		m_vecCameraComponent.clear();
	}

	{
		size_t	Size = m_vecTargetArmComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecTargetArmComponent[i]);
		}

		m_vecTargetArmComponent.clear();
	}
}

void CDetailWindow::SetSelectComponent(CSceneComponent* Component)
{
	if (m_SelectComponent && Component)
	{
		if (m_SelectComponent != Component)
		{
			ClearWidget();

			// 타입에 맞는 GUI 추가
			ChangeWidget(Component);
		}
	}

	m_SelectComponent = Component;
}

bool CDetailWindow::Init()
{
	CreateSceneComponentWidget();
	CreateSpriteComponentWidget();
	CreateCameraComponentWidget();
	CreateTargetArmComponentWidget();

	// 위젯 한번 지워주기
	ClearWidget();

	return true;
}

void CDetailWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	if (m_SelectComponent)
	{
		if (!m_SelectComponent->GetActive())
		{
			m_SelectComponent = nullptr;
			ClearWidget();
		}
	}
}

void CDetailWindow::CreateSceneComponentWidget()
{
}

void CDetailWindow::CreateSpriteComponentWidget()
{
	CEditorTree<void*>* Category = CreateWidget<CEditorTree<void*>>("SpriteComponent");

	Category->SetHideName("SpriteComponent");

	Category->SetSize(400.f, 300.f);

	Category->AddItem(nullptr, "Sprite");

	Category->CreateWidget<CEditorImage>("Sprite", "SpriteImage");

	Category->CreateWidget<CEditorSameLine>("Sprite", "Line");

	CEditorButton* LoadButton = Category->CreateWidget<CEditorButton>("Sprite", "Load");

	LoadButton->SetClickCallback<CDetailWindow>(this, &CDetailWindow::LoadButtonClick);

	Category->AddItem(nullptr, "Animation");

	CEditorCheckbox* Checkbox = Category->CreateWidget<CEditorCheckbox>("Animation", "Use Animation", 100.f, 100.f);

	Checkbox->SetCheckCallbackFunc<CDetailWindow>(this, &CDetailWindow::SetAnimation);

	m_vecSpriteComponent.push_back(Category);
}

void CDetailWindow::CreateCameraComponentWidget()
{
}

void CDetailWindow::CreateTargetArmComponentWidget()
{
}

void CDetailWindow::ChangeWidget(CSceneComponent* Component)
{
	if (Component->GetComponentTypeName() == "SceneComponent")
	{
		size_t	Size = m_vecSceneComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecSceneComponent[i]);
		}
	}

	else if (Component->GetComponentTypeName() == "SpriteComponent")
	{
		size_t	Size = m_vecSpriteComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecSpriteComponent[i]);
			
		}

		if (Component)
		{
			CTexture* Texture = ((CSpriteComponent*)Component)->GetTexture();

			CEditorTree<void*>* Category = (CEditorTree<void*>*)m_vecSpriteComponent[0];

			CEditorImage* ImageWidget = Category->FindWidget<CEditorImage>("SpriteImage");

			ImageWidget->SetTexture(Texture);

			if (((CSpriteComponent*)Component)->GetAnimation())
			{

				CEditorCheckbox* Check = Category->FindWidget<CEditorCheckbox>("Use Animation");

				if (Check)
				{
					Check->SetChecked(true);
					Check->SetReadOnly(true);
				}
			}

			LoadAnimation(Component);
		}
	}

	else if (Component->GetComponentTypeName() == "CameraComponent")
	{
		size_t	Size = m_vecCameraComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecCameraComponent[i]);
		}
	}

	else if (Component->GetComponentTypeName() == "TargetArmComponent")
	{
		size_t	Size = m_vecTargetArmComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecTargetArmComponent[i]);
		}
	}

}

void CDetailWindow::LoadButtonClick()
{
	OPENFILENAME	ofn = {};

	TCHAR	FullPath[MAX_PATH] = {};

	TCHAR	Filter[] = TEXT("모든 파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetOpenFileName(&ofn) != 0)
	{
		CEditorTree<void*>* Category = (CEditorTree<void*>*)m_vecSpriteComponent[0];

		CEditorImage* ImageWidget = Category->FindWidget<CEditorImage>("SpriteImage");

		if (ImageWidget)
		{
			TCHAR	wTexName[256] = {};

			_wsplitpath_s(FullPath, 0, 0, 0, 0, wTexName, 256, 0, 0);

			char	TexName[256] = {};

			int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);

			ImageWidget->SetTextureFullPath(TexName, FullPath);

			// 선택한 SpriteComponent의 Texture를 교체한다.
			if (m_SelectComponent)
			{
				((CSpriteComponent*)m_SelectComponent.Get())->SetTextureFullPath(TexName, FullPath);
			}
		}
	}
}

void CDetailWindow::SetAnimation(bool& B)
{
	CSpriteComponent* Com = (CSpriteComponent*)m_SelectComponent.Get();

	if (B)
	{
		if(!Com->GetAnimation())
			Com->SetAnimation<CAnimation2D>("Anim");
		
		CEditorTree<void*>* Tree = (CEditorTree<void*>*)FindWidget("SpriteComponent");
		if (Tree)
		{
			CEditorCheckbox* Check = Tree->FindWidget<CEditorCheckbox>("Use Animation");

			if (Check)
				Check->SetReadOnly(true);
		}
	}
}

void CDetailWindow::LoadAnimation(CSceneComponent* Component)
{
	CAnimation2D* Anim = nullptr;

	if (Component)
		Anim = ((CSpriteComponent*)Component)->GetAnimation();

	if (!Anim)
		return;

	std::unordered_map<std::string, CAnimation2DData*> mapAnim = Anim->GetmapAnim();

	if (!mapAnim.empty())
	{
		CAnimation2DData* Data = mapAnim.begin()->second;

		CAnimationSequence2D* Seq = Data->GetAnimationSequence();

		int count = Seq->GetFrameCount();

		for (int i = 0; i < count; ++i)
		{
			AnimFrameInfo* Info = new AnimFrameInfo;

			Animation2DFrameData FData = Seq->GetFrameData(i);

			Info->StartX = CreateWidget<CEditorInput>("StartX");
			Info->SameLine1 = CreateWidget<CEditorSameLine>("SameLine");
			Info->StartY = CreateWidget<CEditorInput>("StartY");
			Info->SameLine2 = CreateWidget<CEditorSameLine>("SameLine");
			Info->EndX = CreateWidget<CEditorInput>("EndX");
			Info->SameLine3 = CreateWidget<CEditorSameLine>("SameLine");
			Info->EndY = CreateWidget<CEditorInput>("EndY");

			Info->StartX->ReadOnly(true);
			Info->StartY->ReadOnly(true);
			Info->EndX->ReadOnly(true);
			Info->EndY->ReadOnly(true);

			
			Info->StartX->SetFloat(FData.Start.x);
			Info->StartY->SetFloat(FData.Start.y);
			Info->EndX->SetFloat(FData.End.x);
			Info->EndY->SetFloat(FData.End.y);

			m_AnimFrameInfo.push_back(Info);
		}


	}
}

