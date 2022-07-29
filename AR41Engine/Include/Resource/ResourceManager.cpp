
#include "ResourceManager.h"
#include "Mesh/MeshManager.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{
	m_MeshManager = new CMeshManager;

	m_MeshManager->Init();

	m_ShaderManager = new CShaderManager;

	m_ShaderManager->Init();
}

CResourceManager::~CResourceManager()
{
	SAFE_DELETE(m_ShaderManager);
	SAFE_DELETE(m_MeshManager);
}

bool CResourceManager::Init()
{

	return true;
}

void CResourceManager::Update()
{
}

bool CResourceManager::CreateMesh(CScene* Scene, MeshType Type,
	const std::string& Name, void* VtxData, int Size, 
	int Count, D3D11_USAGE VtxUsage, 
	D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IdxData, int IdxSize, 
	int IdxCount, D3D11_USAGE IdxUsage, DXGI_FORMAT Fmt)
{
	return m_MeshManager->CreateMesh(Scene, Type, Name, VtxData, Size,
		Count, VtxUsage, Primitive, IdxData, IdxSize, IdxCount, IdxUsage,
		Fmt);
}

CMesh* CResourceManager::FindMesh(const std::string& Name)
{
	return m_MeshManager->FindMesh(Name);
}

void CResourceManager::ReleaseMesh(const std::string& Name)
{
	m_MeshManager->ReleaseMesh(Name);
}

CShader* CResourceManager::FindShader(const std::string& Name)
{
	return m_ShaderManager->FindShader(Name);
}

void CResourceManager::ReleaseShader(const std::string& Name)
{
	m_ShaderManager->ReleaseShader(Name);
}

bool CResourceManager::CreateConstantBuffer(const std::string& Name, int Size,
	int Register, int ShaderBufferType)
{
	return m_ShaderManager->CreateConstantBuffer(Name, Size, Register, ShaderBufferType);
}

CConstantBuffer* CResourceManager::FindConstantBuffer(const std::string& Name)
{
	return m_ShaderManager->FindConstantBuffer(Name);
}
