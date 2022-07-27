
#include "Component.h"

CComponent::CComponent()
{
}

CComponent::CComponent(const CComponent& Obj)
{
}

CComponent::~CComponent()
{
}

void CComponent::Destroy()
{
	CRef::Destroy();
}

void CComponent::Start()
{
}

bool CComponent::Init()
{
	return false;
}

void CComponent::Update(float DeltaTime)
{
}

void CComponent::PostUpdate(float DeltaTime)
{
}

void CComponent::Render()
{
}

CComponent* CComponent::Clone() const
{
	return nullptr;
}
