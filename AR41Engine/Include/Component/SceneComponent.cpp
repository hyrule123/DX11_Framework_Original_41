
#include "SceneComponent.h"

CSceneComponent::CSceneComponent()	:
	m_Parent(nullptr)
{
	m_Transform = new CTransform;
}

CSceneComponent::CSceneComponent(const CSceneComponent& component)	:
	CComponent(component)
{
}

CSceneComponent::~CSceneComponent()
{
}

void CSceneComponent::Start()
{
	CComponent::Start();
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
}

void CSceneComponent::PostUpdate(float DeltaTime)
{
	CComponent::PostUpdate(DeltaTime);
}

void CSceneComponent::Render()
{
	CComponent::Render();
}

CSceneComponent* CSceneComponent::Clone() const
{
	return new CSceneComponent(*this);
}
