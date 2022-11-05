#include "NavigationAgent.h"
#include "SceneComponent.h"

CNavigationAgent::CNavigationAgent()
{
	m_ComponentType = ComponentType::Object;

	SetTypeID<CNavigationAgent>();

	m_ComponentTypeName = "NavigationAgent";
}

CNavigationAgent::CNavigationAgent(const CNavigationAgent& Obj) :
    CObjectComponent(Obj)
{
}

CNavigationAgent::~CNavigationAgent()
{
}

void CNavigationAgent::SetUpdateComponent(CSceneComponent* Component)
{
	m_UpdateComponent = Component;
}

void CNavigationAgent::Destroy()
{
	CObjectComponent::Start();
}

void CNavigationAgent::Start()
{
	CObjectComponent::Start();
}

bool CNavigationAgent::Init()
{
	if (!CObjectComponent::Init())
		return false;

    return true;
}

void CNavigationAgent::Update(float DeltaTime)
{
	CObjectComponent::Update(DeltaTime);
}

void CNavigationAgent::PostUpdate(float DeltaTime)
{
	CObjectComponent::PostUpdate(DeltaTime);
}

void CNavigationAgent::Render()
{
	CObjectComponent::Render();
}

CNavigationAgent* CNavigationAgent::Clone() const
{
    return new CNavigationAgent(*this);
}

void CNavigationAgent::Save(FILE* File)
{
	CObjectComponent::Save(File);
}

void CNavigationAgent::Load(FILE* File)
{
	CObjectComponent::Load(File);
}
