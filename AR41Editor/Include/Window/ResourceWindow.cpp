#include "ResourceWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"
#include "PathManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../GameObject\Player2D.h"
#include "../GameObject\Bullet.h"
#include "../GameObject\Monster.h"
#include "ObjectWindow.h"
#include "ComponentWindow.h"
#include "Editor/EditorGUIManager.h"

#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Resource/ResourceManager.h"

CResourceWindow::CResourceWindow()
{
}

CResourceWindow::~CResourceWindow()
{
}

bool CResourceWindow::Init()
{

	CEditorLabel* Label = CreateWidget<CEditorLabel>("TextureList");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(150.f, 30.f);

	m_TextureList = CreateWidget<CEditorListBox>("TextureListBox");

	m_TextureList->SetHideName("TextureListBox");

	m_TextureList->SetSize(500.f, 300.f);
	m_TextureList->SetPageItemCount(6);

	m_TextureList->SetSelectCallback<CResourceWindow>(this, &CResourceWindow::TextureClickCallback);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	m_TextureImageBox = CreateWidget<CEditorImage>("Texture");

	m_TextureImageBox->SetSize(100.f, 100.f);
	m_TextureImageBox->SetHideName("Texture");

    LoadTextureList();

    return true;
}

void CResourceWindow::Update(float DeltaTime)
{
    CEditorWindow::Update(DeltaTime);
}

void CResourceWindow::LoadTextureList()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);

	char	Directory[MAX_PATH] = {};

	strcpy_s(Directory, Path);

	// Editor의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Texture/");

	int DirLen = (int)strlen(Directory);

	const char* TextureExtArray[5] = { ".BMP", ".JPG", ".PNG", ".TGA", ".DDS" };

	for (const auto& file : std::filesystem::recursive_directory_iterator(Directory))
	{
		char	Name[MAX_PATH] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		strcpy_s(Name, MAX_PATH, &FullPath[DirLen]);

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, nullptr, 0, Ext, _MAX_EXT);

		_strupr_s(Ext);

		bool	FileExt = false;

		for (int i = 0; i < 5; ++i)
		{
			if (strcmp(Ext, TextureExtArray[i]) == 0)
			{
				FileExt = true;
				break;
			}
		}

		if (!FileExt)
			continue;

		m_TextureList->AddItem(Name);

		TCHAR	FileName[MAX_PATH] = {};

		int Length = (int)MultiByteToWideChar(CP_ACP, 0, Name, -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Name, -1, FileName, Length);

		CResourceManager::GetInst()->LoadTexture(Name, FileName);
	}
}

void CResourceWindow::TextureClickCallback(int Index, const std::string& Item)
{
	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Item);

	m_TextureImageBox->SetTexture(Texture);
}
