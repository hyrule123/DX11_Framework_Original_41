
#include "MeshManager.h"
#include "SpriteMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

bool CMeshManager::Init()
{
	return true;
}

bool CMeshManager::CreateMesh(CScene* Scene, MeshType Type, const std::string& Name,
	void* VtxData, int Size, int Count, D3D11_USAGE VtxUsage,
	D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IdxData, int IdxSize, 
	int IdxCount, D3D11_USAGE IdxUsage, DXGI_FORMAT Fmt)
{
	if (FindMesh(Name))
		return true;

	CMesh* Mesh = nullptr;

	switch (Type)
	{
	case MeshType::Sprite:
		Mesh = new CSpriteMesh;
		break;
	case MeshType::UI:
		break;
	case MeshType::Static:
		break;
	case MeshType::Animation:
		break;
	}

	Mesh->SetScene(Scene);
	Mesh->SetName(Name);

	if (!Mesh->CreateMesh(VtxData, Size, Count, VtxUsage, Primitive,
		IdxData, IdxSize, IdxCount, IdxUsage, Fmt))
	{
		SAFE_RELEASE(Mesh);
		return false;
	}

	m_mapMesh.insert(std::make_pair(Name, Mesh));

	return true;
}

CMesh* CMeshManager::FindMesh(const std::string& Name)
{
	auto	iter = m_mapMesh.find(Name);

	if (iter == m_mapMesh.end())
		return nullptr;

	return iter->second;
}

void CMeshManager::ReleaseMesh(const std::string& Name)
{
	auto	iter = m_mapMesh.find(Name);

	if (iter != m_mapMesh.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapMesh.erase(iter);
	}
}
