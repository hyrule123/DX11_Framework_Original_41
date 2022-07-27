
#include "SceneComponent.h"

CSceneComponent::CSceneComponent()	:
	m_Parent(nullptr)
{
	m_Transform = new CTransform;

	m_Transform->Init();
}

CSceneComponent::CSceneComponent(const CSceneComponent& component)	:
	CComponent(component)
{
	*this = component;

	m_Transform = component.m_Transform->Clone();

	m_Transform->m_Parent = nullptr;
	m_Transform->m_vecChild.clear();

	m_Transform->m_Owner = this;

	m_Parent = nullptr;
	m_vecChild.clear();
}

CSceneComponent::~CSceneComponent()
{
	SAFE_DELETE(m_Transform);
}

void CSceneComponent::SetScene(CScene* Scene)
{
	CComponent::SetScene(Scene);

	m_Transform->m_Scene = Scene;

	size_t	Size = m_vecChild.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecChild[i]->SetScene(Scene);
	}
}

void CSceneComponent::SetOwner(CGameObject* Owner)
{
	CComponent::SetOwner(Owner);

	m_Transform->m_Object = Owner;

	size_t	Size = m_vecChild.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecChild[i]->SetOwner(Owner);
	}
}

void CSceneComponent::Destroy()
{
	CComponent::Destroy();

	size_t	Size = m_vecChild.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecChild[i]->Destroy();
	}
}

void CSceneComponent::Start()
{
	CComponent::Start();

	m_Transform->Start();

	size_t	Size = m_vecChild.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecChild[i]->Start();
	}
}

bool CSceneComponent::Init()
{
	if (!CComponent::Init())
		return false;

	return true;
}

void CSceneComponent::Update(float DeltaTime)
{
	CComponent::Update(DeltaTime);

	m_Transform->Update(DeltaTime);
}

void CSceneComponent::PostUpdate(float DeltaTime)
{
	CComponent::PostUpdate(DeltaTime);

	m_Transform->PostUpdate(DeltaTime);
}

void CSceneComponent::Render()
{
	CComponent::Render();
}

CSceneComponent* CSceneComponent::Clone() const
{
	return new CSceneComponent(*this);
}
