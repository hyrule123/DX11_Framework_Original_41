#include "Animation2DWindow.h"
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

CAnimation2DWindow::CAnimation2DWindow()
{
}

CAnimation2DWindow::~CAnimation2DWindow()
{
}

bool CAnimation2DWindow::Init()
{
	CEditorLabel* Label = CreateWidget<CEditorLabel>("Animation2DClass");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(150.f, 30.f);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(330.f);

	Label = CreateWidget<CEditorLabel>("Sequence2DClass");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(150.f, 30.f);

	m_Animation2DClassList = CreateWidget<CEditorListBox>("Animation2DClassListBox");

	m_Animation2DClassList->SetHideName("Animation2DClassListBox");

	m_Animation2DClassList->SetSize(300.f, 300.f);
	m_Animation2DClassList->SetPageItemCount(6);

	Line = CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(330.f);

	m_Animation2DSequenceList = CreateWidget<CEditorListBox>("Animation2DSequenceListBox");

	m_Animation2DSequenceList->SetHideName("Animation2DSequenceListBox");

	m_Animation2DSequenceList->SetSize(300.f, 300.f);
	m_Animation2DSequenceList->SetPageItemCount(6);

	LoadAnimation2DClassList();
	LoadAnimation2DSequenceList();

    return true;
}

void CAnimation2DWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CAnimation2DWindow::LoadAnimation2DClassList()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);

	int	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	char	Directory[MAX_PATH] = {};

	strcpy_s(Directory, Path);

	// Editor의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Include/Animation2D/");


	//이부분은 원본에서 최적화해서 수정해놓았음.

	// Animation2D/까지의 길이를 구해놓는다.
	int DirLen = (int)strlen(Directory);

	for (const auto& file : std::filesystem::recursive_directory_iterator(Directory))
	{
		char	Name[256] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};
		char	FolderName[_MAX_DIR] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());


		char FileDirPath[MAX_PATH] = {};
		char OnlyDirPath[MAX_PATH] = {};
		_splitpath_s(FullPath, FileDirPath, _MAX_DRIVE, OnlyDirPath, MAX_PATH, nullptr, 0, nullptr, 0);

		strcat_s(FileDirPath, MAX_PATH, OnlyDirPath);

		int FileDirLen = (int)strlen(FileDirPath);

		if (DirLen > FileDirLen)
			assert(0);

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, nullptr, 0, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") != 0)
			continue;


		strcpy_s(Name, &FullPath[DirLen]);


		Length = (int)strlen(Name);

		//".cpp" 제거
		memset(&Name[Length - 4], 0, 4);
		

		m_Animation2DClassList->AddItem(Name);
	}

	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	m_Animation2DClassList->AddItem("Animation2D");
}

void CAnimation2DWindow::LoadAnimation2DSequenceList()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);

	char	Directory[MAX_PATH] = {};

	strcpy_s(Directory, Path);

	// Editor의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Animation2D/");

	// Animation2D/까지의 길이를 구해놓는다.
	int DirLen = (int)strlen(Directory);

	for (const auto& file : std::filesystem::recursive_directory_iterator(Directory))
	{
		char	Name[256] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};
		char	FolderName[14] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		char FileDirPath[MAX_PATH] = {};
		char OnlyDirPath[MAX_PATH] = {};
		_splitpath_s(FullPath, FileDirPath, _MAX_DRIVE, OnlyDirPath, MAX_PATH, nullptr, 0, nullptr, 0);

		strcat_s(FileDirPath, MAX_PATH, OnlyDirPath);

		int FileDirLen = (int)strlen(FileDirPath);

		if (DirLen > FileDirLen)
			assert(0);

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, nullptr, 0, Ext, _MAX_EXT);

		_strupr_s(Ext);

		if (strcmp(Ext, ".SQC") != 0)
			continue;

		strcpy_s(Name, &FullPath[DirLen]);


		int Length = (int)strlen(Name);

		//".sqc" 제거
		memset(&Name[Length - 4], 0, 4);

		m_Animation2DSequenceList->AddItem(Name);
	}
}
