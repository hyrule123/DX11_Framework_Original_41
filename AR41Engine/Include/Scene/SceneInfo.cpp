
#include "SceneInfo.h"
#include "../GameObject/GameObject.h"

CSceneInfo::CSceneInfo()
{
	m_ClassTypeName = "SceneInfo";
}

CSceneInfo::~CSceneInfo()
{
}

void CSceneInfo::SetPlayerObject(CGameObject* Player)
{
	m_PlayerObject = Player;
}

bool CSceneInfo::Init()
{
	return true;
}

void CSceneInfo::Update(float DeltaTime)
{
}

void CSceneInfo::PostUpdate(float DeltaTime)
{
}

void CSceneInfo::Save(FILE* File)
{
	// 클래스 타입 저장
	int	Length = (int)m_ClassTypeName.length();

	fwrite(&Length, 4, 1, File);
	fwrite(m_ClassTypeName.c_str(), 1, Length, File);

	bool	PlayerEnable = false;

	if (m_PlayerObject)
		PlayerEnable = true;

	fwrite(&PlayerEnable, 1, 1, File);

	if (PlayerEnable)
	{
		Length = (int)m_PlayerObject->GetName().length();

		fwrite(&Length, 4, 1, File);
		fwrite(m_PlayerObject->GetName().c_str(), 1, Length, File);
	}
}

void CSceneInfo::Load(FILE* File)
{
}
