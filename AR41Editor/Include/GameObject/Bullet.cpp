
#include "Bullet.h"
#include "Component/SpriteComponent.h"

CBullet::CBullet()
{
	SetTypeID<CBullet>();

	m_ObjectTypeName = "Bullet";
}

CBullet::CBullet(const CBullet& Obj) :
	CGameObject(Obj)
{
}

CBullet::~CBullet()
{
}

void CBullet::Start()
{
	CGameObject::Start();
}

bool CBullet::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

	m_Sprite->SetRelativeScale(50.f, 50.f);

	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	AddWorldPosition(GetWorldAxis(AXIS_Y) * 300.f * DeltaTime);
}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBullet* CBullet::Clone() const
{
	return new CBullet(*this);
}
