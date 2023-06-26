
#include "MainSceneInfo.h"
#include "Scene/Scene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Weapon.h"
#include "Component/TerrainComponent.h"
#include "Component/BillboardComponent.h"
#include "Component/ParticleComponent.h"
#include "Component/DecalComponent.h"

CMainSceneInfo::CMainSceneInfo()
{
}

CMainSceneInfo::~CMainSceneInfo()
{
}

bool CMainSceneInfo::Init()
{
	CSceneInfo::Init();

	CPlayer* Player = m_Owner->CreateObject<CPlayer>("Player");

	Player->SetWorldPosition(50.f, 0.f, 50.f);

	SetPlayerObject(Player);

	CWeapon* Weapon = m_Owner->CreateObject<CWeapon>("Weapon");

	Player->AddChildToSocket("Weapon", Weapon);

	OutputDebugStringA("Weapon Create\n");

	CGameObject* TerrainObj = m_Owner->CreateObject<CGameObject>("Terrain");

	CTerrainComponent* Terrain = TerrainObj->CreateComponent<CTerrainComponent>("Terrain");

	Terrain->CreateTerrain(129, 129, 100.f, 100.f,
		TEXT("LandScape/height1.bmp"));

	CGameObject* BillboardObj = m_Owner->CreateObject<CGameObject>("Billboard");

	CBillboardComponent* Billboard = BillboardObj->CreateComponent<CBillboardComponent>("Billboard");

	Billboard->SetWorldPosition(300.f, 0.f, 500.f);


	for (int i = 0; i < 10; ++i)
	{
		CGameObject* ParticleObj = m_Owner->CreateObject<CGameObject>("Particle");

		CParticleComponent* Particle = ParticleObj->CreateComponent<CParticleComponent>("Particle");

		Particle->SetParticle("Bubble");
		Particle->SetWorldPosition(300.f + i * 20.f, 0.f, 300.f);
	}

	CGameObject* DecalObj = m_Owner->CreateObject<CGameObject>("Decal");

	CDecalComponent* Decal = DecalObj->CreateComponent<CDecalComponent>("Decal");

	Decal->SetWorldScale(300.f, 300.f, 300.f);
	Decal->SetWorldPosition(200.f, 0.f, 200.f);

	Decal->SetFadeState(EDecalFadeState::FadeInOut);
	Decal->SetFadeInTime(5.f);
	Decal->SetFadeOutTime(5.f);
	Decal->SetFadeOutDelayTime(5.f);


	CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");

	Monster->SetWorldPosition(250.f, 0.f, 50.f);
	/*for (int i = 0; i < 100; ++i)
	{
		CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");

		Monster->SetWorldPosition(-250.f + i * 4.f, 0.f, 50.f);
	}*/

	/*CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");

	Monster->SetWorldPosition(-30.f, 0.f, 50.f);

	Monster = m_Owner->CreateObject<CMonster>("Monster");

	Monster->SetWorldPosition(-150.f, 0.f, -20.f);

	Monster = m_Owner->CreateObject<CMonster>("Monster");

	Monster->SetWorldPosition(30.f, 0.f, 50.f);*/

	//Monster = m_Owner->CreateObject<CMonster>("Monster");

	//Monster->SetWorldPosition(150.f, 0.f, -20.f);

	//CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");


	return true;
}
