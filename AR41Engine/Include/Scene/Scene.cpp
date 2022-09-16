
#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "../Input.h"
#include "../Component/SpriteComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/TargetArm.h"
#include "../Component/SceneComponent.h"
#include "../Animation/Animation2D.h"

std::unordered_map<std::string, CSceneInfo*> CScene::m_mapSceneInfoCDO;

CScene::CScene()	:
	m_Change(false),
	m_Start(false)
{
	m_Name = "Scene";

	m_SceneInfo = new CSceneInfo;

	m_SceneInfo->m_Owner = this;

	m_SceneInfo->Init();

	m_Resource = new CSceneResource;

	m_Resource->m_Owner = this;

	m_Resource->Init();

	m_CameraManager = new CCameraManager;

	m_CameraManager->m_Owner = this;

	m_CameraManager->Init();
}

CScene::~CScene()
{
	CInput::GetInst()->ClearCallback(this);

	SAFE_DELETE(m_CameraManager);
	SAFE_DELETE(m_Resource);
	SAFE_DELETE(m_SceneInfo);
}

void CScene::CreateCDO()
{
	CSceneInfo* Info = new CSceneInfo;

	Info->Init();

	CScene::AddSceneInfoCDO("SceneInfo", Info);

	CGameObject* ObjCDO = new CGameObject;

	ObjCDO->Init();

	CGameObject::AddObjectCDO("GameObject", ObjCDO);

	CComponent* ComCDO = new CSceneComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("SceneComponent", ComCDO);

	ComCDO = new CSpriteComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("SpriteComponent", ComCDO);

	ComCDO = new CCameraComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("CameraComponent", ComCDO);

	ComCDO = new CTargetArm;

	ComCDO->Init();

	CComponent::AddComponentCDO("TargetArm", ComCDO);

	CAnimation2D* AnimCDO = new CAnimation2D;

	AnimCDO->Init();

	CAnimation2D::AddAnimationCDO("Animation2D", AnimCDO);

}

void CScene::Start()
{
	m_Start = true;

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}

	m_CameraManager->Start();
}

bool CScene::Init()
{
	return true;
}

void CScene::Update(float DeltaTime)
{
	if (m_SceneInfo)
		m_SceneInfo->Update(DeltaTime);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}

	m_CameraManager->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	if (m_SceneInfo)
		m_SceneInfo->PostUpdate(DeltaTime);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}

	m_CameraManager->PostUpdate(DeltaTime);
}

void CScene::Save(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "wb");

	if (!File)
		return;

	// �̸� ����
	int	Length = (int)m_Name.length();

	fwrite(&Length, 4, 1, File);
	fwrite(m_Name.c_str(), 1, Length, File);

	// SceneInfo ����
	m_SceneInfo->Save(File);

	int	ObjCount = (int)m_ObjList.size();

	fwrite(&ObjCount, 4, 1, File);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		std::string	ClassTypeName = (*iter)->GetObjectTypeName();

		Length = (int)ClassTypeName.length();

		fwrite(&Length, 4, 1, File);
		fwrite(ClassTypeName.c_str(), 1, Length, File);

		(*iter)->Save(File);
	}

	fclose(File);
}

void CScene::Load(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "rb");

	if (!File)
		return;

	// �̸� ����
	int	Length = 0;
	char	Name[256] = {};

	fread(&Length, 4, 1, File);
	fread(Name, 1, Length, File);

	m_Name = Name;

	// SceneInfo ����
	Length = 0;
	char	SceneInfoName[256] = {};

	fread(&Length, 4, 1, File);
	fread(SceneInfoName, 1, Length, File);

	SAFE_DELETE(m_SceneInfo);

	CSceneInfo* CDO = FindSceneInfoCDO(SceneInfoName);

	m_SceneInfo = CDO->Clone();

	m_SceneInfo->Load(File);

	int	ObjCount = 0;

	fread(&ObjCount, 4, 1, File);

	for (int i = 0; i < ObjCount; ++i)
	{
		Length = 0;

		char	ObjClassTypeName[256] = {};

		fread(&Length, 4, 1, File);
		fread(ObjClassTypeName, 1, Length, File);

		CGameObject* ObjCDO = CGameObject::FindCDO(ObjClassTypeName);

		CGameObject* NewObj = ObjCDO->Clone();

		NewObj->SetScene(this);

		NewObj->Load(File);

		m_ObjList.push_back(NewObj);
	}

	m_SceneInfo->LoadComplete();

	fclose(File);
}

void CScene::GetAllGameObjectHierarchyName(std::vector<HierarchyObjectName>& vecName)
{
	auto    iter = m_ObjList.begin();
	auto    iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		HierarchyObjectName	Names;

		//CGameObject* Parent = (*iter)->GetParent();

		Names.Name = (*iter)->GetName();
		Names.ClassName = (*iter)->GetObjectTypeName();
		Names.Obj= *iter;
		//Names.Parent = Parent;

		/*if (Parent)
		{
			Names.ParentName = Parent->GetName();
			Names.ParentClassName = Parent->GetComponentTypeName();
		}*/

		vecName.push_back(Names);
	}
}

CGameObject* CScene::FindObject(const std::string& Name)
{
	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == Name)
			return *iter;
	}

	return nullptr;
}
