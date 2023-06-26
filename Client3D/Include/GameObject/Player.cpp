
#include "Player.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/NavigationAgent3D.h"
#include "Component/ColliderSphere3D.h"
#include "Input.h"
#include "Engine.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Device.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation.h"
#include "Scene/NavigationManager3D.h"

CPlayer::CPlayer()
{
	SetTypeID<CPlayer>();

	m_ObjectTypeName = "Player";
}

CPlayer::CPlayer(const CPlayer& Obj) :
	CGameObject(Obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_Arm = (CTargetArm*)FindComponent("Arm");
	m_NavAgent = (CNavigationAgent3D*)FindComponent("NavAgent");
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);

	CInput::GetInst()->AddBindFunction<CPlayer>("MoveFront", Input_Type::Push,
		this, &CPlayer::MoveFront, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer>("MoveBack", Input_Type::Push,
		this, &CPlayer::MoveBack, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer>("MoveLeft", Input_Type::Push,
		this, &CPlayer::MoveLeft, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer>("MoveRight", Input_Type::Push,
		this, &CPlayer::MoveRight, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer>("Jump", Input_Type::Down,
		this, &CPlayer::Jump, m_Scene);

	/*CInput::GetInst()->AddBindFunction<CPlayer>("LButton", Input_Type::Down,
		this, &CPlayer::AttackKey, m_Scene);*/


	CInput::GetInst()->AddBindFunction<CPlayer>("LButton", Input_Type::Down,
		this, &CPlayer::ClickMove, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer>("RButton", Input_Type::Push,
		this, &CPlayer::CameraRotationKey, m_Scene);

}

bool CPlayer::Init()
{
	CGameObject::Init();

	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");
	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Arm = CreateComponent<CTargetArm>("Arm");
	m_NavAgent = CreateComponent<CNavigationAgent3D>("NavAgent");
	m_Body = CreateComponent<CColliderSphere3D>("Body");

	SetRootComponent(m_Mesh);

	m_Mesh->SetReceiveDecal(false);

	m_Mesh->AddChild(m_Body);
	m_Mesh->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	m_Camera->SetInheritRotX(true);
	m_Camera->SetInheritRotY(true);

	m_Arm->SetInheritRotY(true);

	m_Arm->SetTargetOffset(0.f, 150.f, 0.f);

	m_Mesh->SetMesh("Player");

	m_Body->SetRadius(m_Mesh->GetMeshSize().Length() * 0.5f);

	m_Animation = m_Mesh->SetAnimation<CAnimation>("PlayerAnimation");

	m_Animation->AddAnimation("PlayerIdle", "PlayerIdle",
		1.f, 1.f, true);

	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	PickingResult	result;
	if (m_Scene->Picking(result))
	{
		TCHAR	Text[256] = {};

		wsprintf(Text, TEXT("Pick : %s\n"),
			result.PickObject->GetName().c_str());

		OutputDebugString(Text);
	}

	//m_Sprite->AddRelativeRotationZ(180.f * DeltaTime);

	//m_RightChild->AddRelativeRotationZ(360.f * DeltaTime);
}

void CPlayer::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayer* CPlayer::Clone() const
{
	return new CPlayer(*this);
}

void CPlayer::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CPlayer::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CPlayer::MoveFront()
{
	AddWorldPosition(GetWorldAxis(AXIS_Z) * 500.f * CEngine::GetInst()->GetDeltaTime());

	CNavigationManager3D* Nav = (CNavigationManager3D*)m_Scene->GetNavigationManager();

	float Y = Nav->GetHeight(GetWorldPos());

	SetWorldPositionY(Y);
}

void CPlayer::MoveBack()
{
	AddWorldPosition(GetWorldAxis(AXIS_Z) * -500.f * CEngine::GetInst()->GetDeltaTime());

	CNavigationManager3D* Nav = (CNavigationManager3D*)m_Scene->GetNavigationManager();

	float Y = Nav->GetHeight(GetWorldPos());

	SetWorldPositionY(Y);
}

void CPlayer::MoveLeft()
{
	AddWorldRotationY(-180.f * CEngine::GetInst()->GetDeltaTime());
}

void CPlayer::MoveRight()
{
	AddWorldRotationY(180.f * CEngine::GetInst()->GetDeltaTime());
}

void CPlayer::Jump()
{
}

void CPlayer::AttackKey()
{
}

void CPlayer::CameraRotationKey()
{
	const Vector2& MouseMove = CInput::GetInst()->GetMouseMove();

	float	DeltaTime = CEngine::GetInst()->GetDeltaTime();

	if (MouseMove.x != 0.f)
	{
		m_Arm->AddRelativeRotationY(MouseMove.x * DeltaTime * 180.f);
	}

	if (MouseMove.y != 0.f)
		m_Arm->AddRelativeRotationX(MouseMove.y * DeltaTime * 180.f);
}

void CPlayer::ClickMove()
{
	//m_NavAgent->MovePicking();
}
