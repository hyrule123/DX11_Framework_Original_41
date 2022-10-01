#include "CircleCollTest.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderSphere2D.h"
#include "Resource/Material/Material.h"

CCircleCollTest::CCircleCollTest()
{
	SetTypeID<CCircleCollTest>();

	m_ObjectTypeName = "CircleCollTest";
}

CCircleCollTest::CCircleCollTest(const CCircleCollTest& Obj) :
	CGameObject(Obj)
{
}

CCircleCollTest::~CCircleCollTest()
{
}

void CCircleCollTest::Start()
{
	CGameObject::Start();

}

bool CCircleCollTest::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderSphere2D>("Body");
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");
	m_Sprite->SetTexture("CircleCollTest", TEXT("DefaultDistortionNormal1.png"));

	m_Body->AddChild(m_Sprite);

	m_Body->SetCollisionProfile("Monster");
	

	m_Sprite->SetPivot(0.5f, 0.f);
	m_Sprite->SetRelativeScale(100.f, 100.f);
	m_Sprite->SetRelativePosition(0.f, -50.f);
	//m_Body->SetWorldPosition(500.f, 600.f);

	//m_Sprite->SetWorldPositionZ(0.5f);

	//m_Sprite->GetMaterial(0)->SetOpacity(0.5f);
	//m_Sprite->GetMaterial(0)->SetRenderState("DepthDisable");


	m_Body->SetWorldPosition(-50.f, 50.f);
	return true;
}

void CCircleCollTest::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CCircleCollTest::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CCircleCollTest* CCircleCollTest::Clone() const
{
	return new CCircleCollTest(*this);
}
