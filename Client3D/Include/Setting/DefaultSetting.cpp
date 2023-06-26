
#include "DefaultSetting.h"
#include "../GameObject/Player.h"
//#include "../GameObject/Monster.h"
//#include "../GameObject/Bullet.h"
//#include "../UI/StartSceneUI.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "CollisionManager.h"
#include "Resource/Particle/Particle.h"

CDefaultSetting::CDefaultSetting()
{
}

CDefaultSetting::~CDefaultSetting()
{
}

void CDefaultSetting::Init()
{
    LoadResource();

    CreateCDO();

    SetInput();

    SetCollision();
}

void CDefaultSetting::CreateCDO()
{
    CScene::CreateObjectCDO<CPlayer>("Player");
    //CScene::CreateObjectCDO<CMonster>("Monster");
    //CScene::CreateObjectCDO<CBullet>("Bullet");

    //CScene::CreateUIWindowCDO<CStartSceneUI>("StartSceneUI");
}

void CDefaultSetting::LoadResource()
{
    CResourceManager::GetInst()->LoadMesh(nullptr, MeshType::Static,
        "Blade", TEXT("Blade.msh"), MESH_PATH);

    CResourceManager::GetInst()->LoadMesh(nullptr, MeshType::Animation,
        "Player", TEXT("Player_Default.msh"), MESH_PATH);


    CResourceManager::GetInst()->LoadSkeleton(nullptr, 
        "PlayerSkeleton", TEXT("Player_Default.bne"), MESH_PATH);

    CResourceManager::GetInst()->SetMeshSkeleton("Player",
        "PlayerSkeleton");


    CResourceManager::GetInst()->AddSocket("PlayerSkeleton",
        "bone11", "Weapon", Vector3(0.f, -60.f, 0.f), Vector3(0.f, 0.f, 90.f));



    CResourceManager::GetInst()->LoadAnimationSequence("PlayerIdle",
        TEXT("sqc_Idle.sqc"), MESH_PATH);

    CResourceManager::GetInst()->LoadAnimationSequence("PlayerWalk",
        TEXT("sqc_Battle_Walk.sqc"), MESH_PATH);

    CResourceManager::GetInst()->LoadAnimationSequence("PlayerAttack",
        TEXT("sqc_Battle_OverHeadSlash.sqc"), MESH_PATH);


    CMaterial* Material = CResourceManager::GetInst()->CreateMaterial<CMaterial>("Bubble");

    Material->AddTexture(0, (int)EShaderBufferType::Pixel, "Bubble",
        TEXT("Particle/Bubbles50px.png"));
    

    CParticle* Particle = nullptr;
    
    CResourceManager::GetInst()->CreateParticle("Bubble");

    Particle = CResourceManager::GetInst()->FindParticle("Bubble");

    Particle->SetMaterial("Bubble");

    Particle->SetParticleSpawnTime(0.001f);
    Particle->SetParticleStartMin(Vector3(-100.f, -100.f, -100.f));
    Particle->SetParticleStartMax(Vector3(100.f, 100.f, 100.f));
    Particle->SetParticleSpawnCountMax(1000);
    Particle->SetParticleScaleMin(Vector3(20.f, 20.f, 20.f));
    Particle->SetParticleScaleMax(Vector3(50.f, 50.f, 50.f));
    Particle->SetParticleLifeTimeMin(2.f);
    Particle->SetParticleLifeTimeMax(3.f);
    Particle->SetParticleColorMin(Vector4(1.f, 0.f, 0.f, 1.f));
    Particle->SetParticleColorMax(Vector4(0.f, 1.f, 0.f, 0.f));
    Particle->SetParticleSpeedMin(100.f);
    Particle->SetParticleSpeedMax(200.f);
    Particle->SetParticleMoveEnable(true);
    Particle->SetParticleGravityEnable(true);
    Particle->SetParticleMoveDir(Vector3(0.f, 1.f, 0.f));
    Particle->SetParticleMoveDirEnable(true);
    Particle->SetParticleMoveAngle(Vector3(45.f, 45.f, 45.f));

    /*
	Vector3  ParticleMoveAngle;    // 기준이 될 방향으로부터 회전할 최대 각도.
	float   ParticleEmpty2;
    */
}

void CDefaultSetting::SetInput()
{
    // 키 등록
    CInput::GetInst()->AddBindKey("MoveRight", 'D');
    CInput::GetInst()->AddBindKey("MoveLeft", 'A');

    CInput::GetInst()->AddBindKey("MoveFront", 'W');
    CInput::GetInst()->AddBindKey("MoveBack", 'S');

    CInput::GetInst()->AddBindKey("Jump", VK_SPACE);

    CInput::GetInst()->AddBindKey("LButton", VK_LBUTTON);

    CInput::GetInst()->AddBindKey("RButton", VK_RBUTTON);
}

void CDefaultSetting::SetCollision()
{
    CCollisionManager::GetInst()->CreateChannel("Player", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("PlayerAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Monster", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("MonsterAttack", ECollision_Interaction::Collision);

    CCollisionManager::GetInst()->CreateProfile("Player", "Player", true);
    CCollisionManager::GetInst()->CreateProfile("PlayerAttack", "PlayerAttack", true);
    CCollisionManager::GetInst()->CreateProfile("Monster", "Monster", true);
    CCollisionManager::GetInst()->CreateProfile("MonsterAttack", "MonsterAttack", true);

    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Player", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "PlayerAttack", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Monster", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "PlayerAttack", ECollision_Interaction::Ignore);
}
