#include "Collider.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderManager.h"
#include "../Resource/Material/Material.h"
#include "../Engine.h"
#include "../Scene/SceneCollision.h"
#include "../CollisionManager.h"

CCollider::CCollider()
{
	SetTypeID<CCollider>();

	m_ComponentTypeName = "Collider";
	m_Result.Src = this;
}

CCollider::CCollider(const CCollider& component) :
	CSceneComponent(component)
{
	m_Mesh = component.m_Mesh;
	m_Color = component.m_Color;
	m_ColliderType = component.m_ColliderType;
	m_Min = component.m_Min;
	m_Max = component.m_Max;
	m_Profile = component.m_Profile;
	m_Result.Src = this;
}

CCollider::~CCollider()
{
	auto	iter = m_PrevCollisionList.begin();
	auto	iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeletePrevCollisionCollider(this);

		(*iter)->m_Result.Src = *iter;
		(*iter)->m_Result.Dest = this;
		(*iter)->CallCollisionCallback(ECollision_Result::Release);

		m_Result.Src = this;
		m_Result.Dest = *iter;
		CallCollisionCallback(ECollision_Result::Release);
	}
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

bool CCollider::CheckPrevCollision(CCollider* Collider)
{
	auto	iter = m_PrevCollisionList.begin();
	auto	iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == Collider)
			return true;
	}

	return false;
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
			m_Result.Src = this;
			m_Result.Dest = *iter;

			CallCollisionCallback(ECollision_Result::Release);

			(*iter)->m_Result.Src = *iter;
			(*iter)->m_Result.Dest = this;

			(*iter)->CallCollisionCallback(ECollision_Result::Release);

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
	auto	iter = m_PrevCollisionList.begin();
	auto	iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeletePrevCollisionCollider(this);

		(*iter)->m_Result.Src = *iter;
		(*iter)->m_Result.Dest = this;
		(*iter)->CallCollisionCallback(ECollision_Result::Release);

		m_Result.Src = this;
		m_Result.Dest = *iter;
		CallCollisionCallback(ECollision_Result::Release);
	}

	m_PrevCollisionList.clear();
}

void CCollider::CallCollisionCallback(ECollision_Result Type)
{
	if (m_CollisionCallback[(int)Type])
		m_CollisionCallback[(int)Type](m_Result);
}

void CCollider::CallCollisionMouseCallback(ECollision_Result Type)
{
	if (m_CollisionMouseCallback[(int)Type])
		m_CollisionMouseCallback[(int)Type](m_MouseResult);
}

void CCollider::ClearFrame()
{
	m_CurrentSectionList.clear();
}

int CCollider::CheckOverlapSection(CCollider* Dest)
{
	int	OverlapCount = 0;
	int	MinIndex = INT_MAX;

	auto	iter1 = m_CurrentSectionList.begin();
	auto	iter1End = m_CurrentSectionList.end();

	for (; iter1 != iter1End; ++iter1)
	{
		auto	iter2 = Dest->m_CurrentSectionList.begin();
		auto	iter2End = Dest->m_CurrentSectionList.end();

		for (; iter2 != iter2End; ++iter2)
		{
			if (*iter1 == *iter2)
			{
				++OverlapCount;

				if (*iter1 < MinIndex)
					MinIndex = *iter1;

				break;
			}
		}
	}

	if (OverlapCount < 2)
		return -1;

	return MinIndex;
}

void CCollider::SetCollisionProfile(const std::string& Name)
{
	m_Profile = CCollisionManager::GetInst()->FindProfile(Name);
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

	m_Profile = CCollisionManager::GetInst()->FindProfile("Default");

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

	if (m_PrevCollisionList.empty())
		m_Color = Vector4(0.f, 1.f, 0.f, 1.f);

	else
		m_Color = Vector4(1.f, 0.f, 0.f, 1.f);
}

void CCollider::Save(FILE* File)
{
	CSceneComponent::Save(File);
}

void CCollider::Load(FILE* File)
{
	CSceneComponent::Load(File);
}

