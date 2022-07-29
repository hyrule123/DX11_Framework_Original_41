
#include "MainSceneInfo.h"
#include "Scene/Scene.h"
#include "../GameObject/Player2D.h"

CMainSceneInfo::CMainSceneInfo()
{
}

CMainSceneInfo::~CMainSceneInfo()
{
}

bool CMainSceneInfo::Init()
{
	CSceneInfo::Init();

	CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");

	SetPlayerObject(Player);


	return true;
}
