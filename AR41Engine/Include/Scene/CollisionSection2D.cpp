#include "CollisionSection2D.h"
#include "../Component/Collider2D.h"

CCollisionSection2D::CCollisionSection2D()
{
}

CCollisionSection2D::~CCollisionSection2D()
{
}

void CCollisionSection2D::AddCollider(CCollider2D* Collider)
{
	m_ColliderList.push_back(Collider);

	Collider->AddSectionIndex(m_Index);
}
