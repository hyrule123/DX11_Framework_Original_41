#include "BoxText.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Resource/Material/Material.h"

CBoxText::CBoxText()
{
	SetTypeID<CBoxText>();

	m_ObjectTypeName = "BoxTest";
}

CBoxText::CBoxText(const CBoxText& Obj) :
	CGameObject(Obj)
{
}

CBoxText::~CBoxText()
{
}

void CBoxText::Start()
{
	CGameObject::Start();

}

bool CBoxText::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

	m_Body->AddChild(m_Sprite);

	m_Body->SetCollisionProfile("Monster");


	m_Sprite->SetPivot(0.5f, 0.f);
	m_Sprite->SetRelativeScale(100.f, 100.f);
	m_Sprite->SetRelativePosition(0.f, -50.f);
	m_Body->SetWorldPosition(500.f, 600.f);

	//m_Sprite->SetWorldPositionZ(0.5f);

	//m_Sprite->GetMaterial(0)->SetOpacity(0.5f);
	//m_Sprite->GetMaterial(0)->SetRenderState("DepthDisable");


	m_Body->SetWorldPosition(50.f, 50.f);
	return true;
}

void CBoxText::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBoxText::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBoxText* CBoxText::Clone() const
{
	return new CBoxText(*this);
}
