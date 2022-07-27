#include "GameObject.h"

CGameObject::CGameObject()  :
	m_Parent(nullptr),
	m_Scene(nullptr),
	m_LifeTime(-1.f)
{
}

CGameObject::CGameObject(const CGameObject& Obj)    :
	CRef(Obj)
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::Destroy()
{
}

CComponent* CGameObject::FindComponent(const std::string& Name)
{
	auto    iter = m_SceneComponentList.begin();
	auto    iterEnd = m_SceneComponentList.end();
	
	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == Name)
			return *iter;
	}

	auto    iter1 = m_vecObjectComponent.begin();
	auto    iter1End = m_vecObjectComponent.end();

	for (; iter1 != iter1End; ++iter1)
	{
		if ((*iter1)->GetName() == Name)
			return *iter1;
	}

	return nullptr;
}

void CGameObject::Start()
{
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float DeltaTime)
{
}

void CGameObject::PostUpdate(float DeltaTime)
{
}

CGameObject* CGameObject::Clone() const
{
	return new CGameObject(*this);
}
