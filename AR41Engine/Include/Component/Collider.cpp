#include "Collider.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"
#include "../Engine.h"

CCollider::CCollider()
{
	SetTypeID<CCollider>();

	m_ComponentTypeName = "Collider";
}

CCollider::CCollider(const CCollider& component) :
	CSceneComponent(component)
{
	m_Mesh = component.m_Mesh;
	m_Color = component.m_Color;
	m_ColliderType = component.m_ColliderType;
	m_Min = component.m_Min;
	m_Max = component.m_Max;
}

CCollider::~CCollider()
{
}

void CCollider::Start()
{
	CSceneComponent::Start();

	// Scene�� ��ġ�� �ǰ� Start�� ȣ��Ǹ� ��� ������� �����Ѵ�.
	if (CEngine::GetEditorMode())
		CRenderManager::GetInst()->AddRenderList(this);
}

bool CCollider::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CCollider::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CCollider::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CCollider::Render()
{
	CSceneComponent::Render();
}

CCollider* CCollider::Clone() const
{
	return new CCollider(*this);
}

void CCollider::Save(FILE* File)
{
	CSceneComponent::Save(File);
}

void CCollider::Load(FILE* File)
{
	CSceneComponent::Load(File);
}
