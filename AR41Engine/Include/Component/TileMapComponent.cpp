#include "TileMapComponent.h"
#include "../Resource/Material/Material.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Mesh/Mesh.h"
#include "../Resource/Shader/Animation2DConstantBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/Shader/TileMapConstantBuffer.h"
#include "../Device.h"
#include "../Resource/Shader/StructuredBuffer.h"

CTileMapComponent::CTileMapComponent()	:
	m_CountX(0),
	m_CountY(0),
	m_Count(0),
	m_RenderCount(0),
	m_TileMapCBuffer(nullptr),
	m_TileInfoBuffer(nullptr)
{
	SetTypeID<CTileMapComponent>();

	m_ComponentTypeName = "TileMapComponent";

	m_TileTypeColor[(int)ETileOption::None] = Vector4::White;
	m_TileTypeColor[(int)ETileOption::Wall] = Vector4::Red;
}

CTileMapComponent::CTileMapComponent(const CTileMapComponent& component) :
	CPrimitiveComponent(component)
{
	m_TileMesh = component.m_TileMesh;

	if (component.m_TileMaterial)
		m_TileMaterial = component.m_TileMaterial->Clone();

	if (component.m_TileMapCBuffer)
		m_TileMapCBuffer = component.m_TileMapCBuffer->Clone();

	if (component.m_TileInfoBuffer)
		m_TileInfoBuffer = component.m_TileInfoBuffer->Clone();


	m_Shape = component.m_Shape;
	m_CountX = component.m_CountX;
	m_CountY = component.m_CountY;
	m_Count = component.m_Count;
	m_RenderCount = component.m_RenderCount;
	m_TileSize = component.m_TileSize;
	m_TileTypeColor[(int)ETileOption::None] = component.m_TileTypeColor[(int)ETileOption::None];
	m_TileTypeColor[(int)ETileOption::Wall] = component.m_TileTypeColor[(int)ETileOption::Wall];

	m_vecTile.clear();

	size_t	Size = component.m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		CTile* Tile = component.m_vecTile[i]->Clone();

		Tile->m_Owner = this;

		m_vecTile.push_back(Tile);
	}

	m_vecTileInfo.resize(m_vecTile.size());
}

CTileMapComponent::~CTileMapComponent()
{
	SAFE_DELETE(m_TileMapCBuffer);
	SAFE_DELETE(m_TileInfoBuffer);

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

	int	RenderCountX = 0, RenderCountY = 0;

	switch (m_Shape)
	{
	case ETileShape::Rect:
		RenderCountX = (int)(CDevice::GetInst()->GetResolution().Width /
			m_TileSize.x) + 2;
		RenderCountY = (int)(CDevice::GetInst()->GetResolution().Height /
			m_TileSize.y) + 2;

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
		RenderCountX = (int)(CDevice::GetInst()->GetResolution().Width /
			m_TileSize.x) + 2;
		RenderCountY = (int)(CDevice::GetInst()->GetResolution().Height /
			m_TileSize.y) * 2 + 2;

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

	// 구조화 버퍼를 생성한다. 구조화버퍼에는 출력할 타일정보가 들어가야
	// 하기 때문에 출력되는 최대 타일 개수를 이용해서 생성한다.
	SAFE_DELETE(m_TileInfoBuffer);

	m_TileInfoBuffer = new CStructuredBuffer;

	m_TileInfoBuffer->Init("TileInfo", sizeof(TileInfo),
		RenderCountX * RenderCountY, 40, true, 
		(int)EShaderBufferType::Vertex);

	m_vecTileInfo.resize((size_t)m_Count);

	for (int i = 0; i < m_Count; ++i)
	{
		m_vecTileInfo[i].TypeColor = Vector4(1.f, 1.f, 1.f, 1.f);
		m_vecTileInfo[i].Opacity = 1.f;
	}
}

int CTileMapComponent::GetTileIndexX(const Vector2& Pos)
{
	if (m_Shape == ETileShape::Rect)
	{
		float ConvertX = Pos.x - GetWorldPos().x;

		int	IndexX = (int)(ConvertX / m_TileSize.x);

		if (IndexX < 0 || IndexX >= m_CountX)
			return -1;

		return IndexX;
	}

	return 0;
}

int CTileMapComponent::GetTileIndexX(const Vector3& Pos)
{
	if (m_Shape == ETileShape::Rect)
	{
		float ConvertX = Pos.x - GetWorldPos().x;

		int	IndexX = (int)(ConvertX / m_TileSize.x);

		if (IndexX < 0 || IndexX >= m_CountX)
			return -1;

		return IndexX;
	}

	return 0;
}

int CTileMapComponent::GetTileIndexY(const Vector2& Pos)
{
	if (m_Shape == ETileShape::Rect)
	{
		float ConvertY = Pos.y - GetWorldPos().y;

		int	IndexY = (int)(ConvertY / m_TileSize.y);

		if (IndexY < 0 || IndexY >= m_CountY)
			return -1;

		return IndexY;
	}



	return 0;
}

int CTileMapComponent::GetTileIndexY(const Vector3& Pos)
{
	if (m_Shape == ETileShape::Rect)
	{
		float ConvertY = Pos.y - GetWorldPos().y;

		int	IndexY = (int)(ConvertY / m_TileSize.y);

		if (IndexY < 0 || IndexY >= m_CountY)
			return -1;

		return IndexY;
	}

	return 0;
}

int CTileMapComponent::GetTileIndex(const Vector2& Pos)
{
	if (m_Shape == ETileShape::Rect)
	{
		int	IndexX = GetTileIndexX(Pos);

		if (IndexX == -1)
			return -1;

		int	IndexY = GetTileIndexY(Pos);

		if (IndexY == -1)
			return -1;

		return IndexY * m_CountX + IndexX;
	}

	return 0;
}

int CTileMapComponent::GetTileIndex(const Vector3& Pos)
{
	if (m_Shape == ETileShape::Rect)
	{
		int	IndexX = GetTileIndexX(Pos);

		if (IndexX == -1)
			return -1;

		int	IndexY = GetTileIndexY(Pos);

		if (IndexY == -1)
			return -1;

		return IndexY * m_CountX + IndexX;
	}

	return 0;
}

CTile* CTileMapComponent::GetTile(const Vector2& Pos)
{
	return nullptr;
}

CTile* CTileMapComponent::GetTile(const Vector3& Pos)
{
	return nullptr;
}

CTile* CTileMapComponent::GetTile(int X, int Y)
{
	return nullptr;
}

CTile* CTileMapComponent::GetTile(int Index)
{
	return nullptr;
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

