
#include "PrimitiveComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderManager.h"

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

	if (m_Mesh)
		SetMeshSize(m_Mesh->GetMeshSize());
}

void CPrimitiveComponent::SetMesh(CMesh* Mesh)
{
	m_Mesh = Mesh;

	if (m_Mesh)
		SetMeshSize(m_Mesh->GetMeshSize());
}

void CPrimitiveComponent::SetShader(const std::string& Name)
{
	m_Shader = m_Scene->GetResource()->FindShader(Name);
}

void CPrimitiveComponent::Start()
{
	CSceneComponent::Start();

	// Scene�� ��ġ�� �ǰ� Start�� ȣ��Ǹ� ��� ������� �����Ѵ�.
	CRenderManager::GetInst()->AddRenderList(this);
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

	m_Shader->SetShader();

	m_Mesh->Render();
}

CPrimitiveComponent* CPrimitiveComponent::Clone() const
{
	return new CPrimitiveComponent(*this);
}
