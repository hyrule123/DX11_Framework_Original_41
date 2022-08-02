
#include "Player2D.h"
#include "Component/SpriteComponent.h"
#include "Input.h"

CPlayer2D::CPlayer2D()
{
	SetTypeID<CPlayer2D>();
}

CPlayer2D::CPlayer2D(const CPlayer2D& Obj)	:
	CGameObject(Obj)
{
}

CPlayer2D::~CPlayer2D()
{
}

void CPlayer2D::Start()
{
	CGameObject::Start();
}

bool CPlayer2D::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("sprite");
	m_RightChild = CreateComponent<CSceneComponent>("RightChild");
	m_SpriteChild = CreateComponent<CSpriteComponent>("spriteChild");

	m_Sprite->AddChild(m_RightChild);
	m_RightChild->AddChild(m_SpriteChild);

	m_Sprite->SetRelativeScale(100.f, 100.f);
	m_Sprite->SetWorldPosition(500.f, 500.f);

	m_RightChild->SetRelativePosition(150.f, 0.f);
	m_RightChild->SetInheritRotZ(true);

	m_SpriteChild->SetRelativeScale(50.f, 50.f);
	m_SpriteChild->SetRelativePosition(100.f, 0.f);
	m_SpriteChild->SetInheritRotZ(true);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Rotation", Input_Type::Push,
		this, &CPlayer2D::RotationInv, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("RotationInv", Input_Type::Push,
		this, &CPlayer2D::Rotation, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveUp", Input_Type::Push,
		this, &CPlayer2D::MoveUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveDown", Input_Type::Push,
		this, &CPlayer2D::MoveDown, m_Scene);

	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//m_Sprite->AddRelativeRotationZ(180.f * DeltaTime);

	//m_RightChild->AddRelativeRotationZ(360.f * DeltaTime);
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayer2D* CPlayer2D::Clone() const
{
	return new CPlayer2D(*this);
}

void CPlayer2D::MoveUp()
{
	m_Sprite->AddWorldPosition(m_Sprite->GetWorldAxis(AXIS_Y) * 300.f * g_DeltaTime);
}

void CPlayer2D::MoveDown()
{
	m_Sprite->AddWorldPosition(m_Sprite->GetWorldAxis(AXIS_Y) * -300.f * g_DeltaTime);
}

void CPlayer2D::Rotation()
{
	m_Sprite->AddWorldRotationZ(360.f * g_DeltaTime);
}

void CPlayer2D::RotationInv()
{
	m_Sprite->AddWorldRotationZ(-360.f * g_DeltaTime);
}
