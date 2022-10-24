#include "TileMapComponent.h"
#include "../Resource/Material/Material.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Shader/Animation2DConstantBuffer.h"

CTileMapComponent::CTileMapComponent()
{
	SetTypeID<CTileMapComponent>();

	m_ComponentTypeName = "TileMapComponent";
}

CTileMapComponent::CTileMapComponent(const CTileMapComponent& component) :
	CPrimitiveComponent(component)
{
}

CTileMapComponent::~CTileMapComponent()
{
}

void CTileMapComponent::Start()
{
	CPrimitiveComponent::Start();
}

bool CTileMapComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	m_Transform->Set2D(true);

	return true;
}

void CTileMapComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);
}

void CTileMapComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
}

void CTileMapComponent::Render()
{
	CPrimitiveComponent::Render();
}

CTileMapComponent* CTileMapComponent::Clone() const
{
	return new CTileMapComponent(*this);
}

void CTileMapComponent::Save(FILE* File)
{
	CPrimitiveComponent::Save(File);
}

void CTileMapComponent::Load(FILE* File)
{
	CPrimitiveComponent::Load(File);
}

