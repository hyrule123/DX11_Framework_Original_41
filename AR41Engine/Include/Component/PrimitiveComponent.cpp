
#include "PrimitiveComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CPrimitiveComponent::CPrimitiveComponent()
{
	SetTypeID<CPrimitiveComponent>();
}

CPrimitiveComponent::CPrimitiveComponent(const CPrimitiveComponent& component)	:
	CSceneComponent(component)
{
}

CPrimitiveComponent::~CPrimitiveComponent()
{
}

void CPrimitiveComponent::SetMesh(const std::string& Name)
{
	m_Mesh = m_Scene->GetResource()->FindMesh(Name);
}

void CPrimitiveComponent::SetMesh(CMesh* Mesh)
{
	m_Mesh = Mesh;
}

void CPrimitiveComponent::SetShader(const std::string& Name)
{
	m_Shader = m_Scene->GetResource()->FindShader(Name);
}

void CPrimitiveComponent::Start()
{
	CSceneComponent::Start();
}

bool CPrimitiveComponent::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CPrimitiveComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CPrimitiveComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CPrimitiveComponent::Render()
{
	CSceneComponent::Render();
}

CPrimitiveComponent* CPrimitiveComponent::Clone() const
{
	return new CPrimitiveComponent(*this);
}
