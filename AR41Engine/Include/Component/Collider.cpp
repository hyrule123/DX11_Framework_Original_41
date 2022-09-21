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
			// 이전 충돌물체의 충돌영역 목록을 반복한다.
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

		// 서로 겹치는 충돌영역이 없으면 이전 프레임에 충돌하고 있다가 서로 다른 영역으로 충돌체가 포함된 것이다.
		// 둘이 충돌이 해제되었다는 통보를 해주어야 한다.
		if (!Check)
		{
			// 충돌 해제 통보.
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

	// Scene에 배치가 되고 Start가 호출되면 출력 목록으로 지정한다.
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

