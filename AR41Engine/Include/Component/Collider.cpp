#include "Collider.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"
#include "../Engine.h"
#include "../Scene/SceneCollision.h"

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

void CCollider::DeletePrevCollisionCollider(CCollider* Collider)
{
	auto	iter = m_PrevCollisionList.begin();
	auto	iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == Collider)
		{
			m_PrevCollisionList.erase(iter);
			return;
		}
	}
}

void CCollider::CheckPrevCollisionColliderSection()
{
	auto	iter = m_PrevCollisionList.begin();
	auto	iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd;)
	{
		bool	Check = false;

		auto	iterIndex = m_CurrentSectionList.begin();
		auto	iterIndexEnd = m_CurrentSectionList.end();

		for (; iterIndex != iterIndexEnd; ++iterIndex)
		{
			// ���� �浹��ü�� �浹���� ����� �ݺ��Ѵ�.
			auto	iterDestIndex = (*iter)->m_CurrentSectionList.begin();
			auto	iterDestIndexEnd = (*iter)->m_CurrentSectionList.end();

			for (; iterDestIndex != iterDestIndexEnd; ++iterDestIndex)
			{
				if (*iterIndex == *iterDestIndex)
				{
					Check = true;
					break;
				}
			}

			if (Check)
				break;
		}

		// ���� ��ġ�� �浹������ ������ ���� �����ӿ� �浹�ϰ� �ִٰ� ���� �ٸ� �������� �浹ü�� ���Ե� ���̴�.
		// ���� �浹�� �����Ǿ��ٴ� �뺸�� ���־�� �Ѵ�.
		if (!Check)
		{
			// �浹 ���� �뺸.
			(*iter)->DeletePrevCollisionCollider(this);
			iter = m_PrevCollisionList.erase(iter);
			iterEnd = m_PrevCollisionList.end();
			continue;
		}

		++iter;
	}
}

void CCollider::SendPrevCollisionEnd()
{
}

void CCollider::Start()
{
	CSceneComponent::Start();

	// Scene�� ��ġ�� �ǰ� Start�� ȣ��Ǹ� ��� ������� �����Ѵ�.
	if (CEngine::GetEditorMode())
		CRenderManager::GetInst()->AddRenderList(this);

	if (m_Scene)
	{
		m_Scene->GetCollisionManager()->AddCollider(this);
	}
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

