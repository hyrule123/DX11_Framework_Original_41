#include "TileMapComponent.h"
#include "../Resource/Material/Material.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Mesh/Mesh.h"
#include "../Resource/Shader/Animation2DConstantBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/Shader/TileMapConstantBuffer.h"

CTileMapComponent::CTileMapComponent()	:
	m_CountX(0),
	m_CountY(0),
	m_Count(0),
	m_RenderCount(0),
	m_TileMapCBuffer(nullptr)
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
	SAFE_DELETE(m_TileMapCBuffer);

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

void CTileMapComponent::SetTileTexture(CTexture* Texture)
{
	m_TileMaterial->SetTexture(0, 0, (int)EShaderBufferType::Pixel,
		Texture->GetName(), Texture);
}

void CTileMapComponent::SetTileTexture(const std::string& Name,
	const TCHAR* FileName, const std::string& PathName)
{
	m_TileMaterial->SetTexture(0, 0, (int)EShaderBufferType::Pixel, 
		Name, FileName, PathName);
}

void CTileMapComponent::SetTileTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	m_TileMaterial->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel,
		Name, FullPath);
}

void CTileMapComponent::SetTileTextureArray(const std::string& Name,
	const std::vector<const TCHAR*>& vecFileName, 
	const std::string& PathName)
{
	m_TileMaterial->SetTextureArray(0, 0, (int)EShaderBufferType::Pixel,
		Name, vecFileName, PathName);
}

void CTileMapComponent::SetTileTextureArrayFullPath(
	const std::string& Name,
	const std::vector<const TCHAR*>& vecFullPath)
{
	m_TileMaterial->SetTextureArrayFullPath(0, 0, (int)EShaderBufferType::Pixel,
		Name, vecFullPath);
}

void CTileMapComponent::SetTileBaseColor(const Vector4& Color)
{
	m_TileMaterial->SetBaseColor(Color);
}

void CTileMapComponent::CreateTile(ETileShape Shape, int CountX, 
	int CountY, const Vector2& TileSize)
{
	m_Shape = Shape;

	m_CountX = CountX;
	m_CountY = CountY;
	m_Count = m_CountX * m_CountY;

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
		for (int i = 0; i < m_CountY; ++i)
		{
			for (int j = 0; j < m_CountX; ++j)
			{
				int	Index = i * m_CountX + j;

				m_vecTile[Index]->m_Pos.x = j * m_TileSize.x;
				m_vecTile[Index]->m_Pos.y = i * m_TileSize.y;
			}
		}
		break;
	case ETileShape::Isometric:
	{
		float	StartX = 0.f;

		for (int i = 0; i < m_CountY; ++i)
		{
			if (i % 2 == 0)
				StartX = 0.f;

			else
				StartX = m_TileSize.x * 0.5f;

			for (int j = 0; j < m_CountX; ++j)
			{
				int	Index = i * m_CountX + j;

				m_vecTile[Index]->m_Pos.x = StartX + j * m_TileSize.x;
				m_vecTile[Index]->m_Pos.y = i * m_TileSize.y * 0.5f;
			}
		}
	}
		break;
	}

	m_TileMapCBuffer->SetTileSize(m_TileSize);
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

	SetTileMaterial("TileMap");

	m_TileMapCBuffer = new CTileMapConstantBuffer;

	m_TileMapCBuffer->Init();

	m_TileMapCBuffer->SetImageSize(Vector2(64.f, 320.f));

	m_TileMapCBuffer->SetStart(Vector2(0.f, 0.f));
	m_TileMapCBuffer->SetEnd(Vector2(64.f, 64.f));
	m_TileMapCBuffer->SetFrame(0);

	return true;
}

void CTileMapComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->Update(DeltaTime);
	}
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

