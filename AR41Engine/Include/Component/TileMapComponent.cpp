#include "TileMapComponent.h"
#include "../Resource/Material/Material.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Mesh/Mesh.h"
#include "../Resource/Shader/Animation2DConstantBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CTileMapComponent::CTileMapComponent()	:
	m_CountX(0),
	m_CountY(0),
	m_Count(0),
	m_RenderCount(0)
{
	SetTypeID<CTileMapComponent>();

	m_ComponentTypeName = "TileMapComponent";

	m_TileTypeColor[(int)ETileOption::None] = Vector4::White;
	m_TileTypeColor[(int)ETileOption::Wall] = Vector4::Red;
}

CTileMapComponent::CTileMapComponent(const CTileMapComponent& component) :
	CPrimitiveComponent(component)
{
}

CTileMapComponent::~CTileMapComponent()
{
	auto	iter = m_vecTile.begin();
	auto	iterEnd = m_vecTile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_vecTile.clear();
}

void CTileMapComponent::SetTileMaterial(const std::string& Name)
{
	if (m_Scene)
		m_TileMaterial = m_Scene->GetResource()->FindMaterial(Name);

	else
		m_TileMaterial = CResourceManager::GetInst()->FindMaterial(Name);
}

void CTileMapComponent::SetTileMaterial(CMaterial* Material)
{
	m_TileMaterial = Material;
}

void CTileMapComponent::CreateTile(ETileShape Shape, int CountX, 
	int CountY, const Vector2& TileSize)
{
	m_Shape = Shape;

	m_CountX = CountX;
	m_CountY = CountY;

	m_TileSize = TileSize;

	auto	iter = m_vecTile.begin();
	auto	iterEnd = m_vecTile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_vecTile.clear();

	m_vecTile.resize((size_t)(m_CountX * m_CountY));

	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			CTile* Tile = new CTile;

			Tile->m_Owner = this;

			int	Index = i * m_CountX + j;

			Tile->m_IndexX = j;
			Tile->m_IndexY = i;
			Tile->m_Index = Index;

			Tile->m_Size.x = m_TileSize.x;
			Tile->m_Size.y = m_TileSize.y;

			m_vecTile[Index] = Tile;
		}
	}

	switch (m_Shape)
	{
	case ETileShape::Rect:
		break;
	case ETileShape::Isometric:
		break;
	}
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

	// 배경용 메쉬 등록
	SetMesh("LBUVRect");

	m_TileMesh = m_Mesh;

	m_Shape = ETileShape::Rect;

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

