
#include "CameraComponent.h"

CCameraComponent::CCameraComponent()
{
}

CCameraComponent::CCameraComponent(const CCameraComponent& component)
{
}

CCameraComponent::~CCameraComponent()
{
}

void CCameraComponent::Destroy()
{
	CSceneComponent::Destroy();
}

void CCameraComponent::Start()
{
	CSceneComponent::Start();
}

bool CCameraComponent::Init()
{
	CSceneComponent::Init();

	return true;
}

void CCameraComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CCameraComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CCameraComponent::Render()
{
	CSceneComponent::Render();
}

CCameraComponent* CCameraComponent::Clone() const
{
	return new CCameraComponent(*this);
}
