
#include "ResourceManager.h"
#include "Mesh/MeshManager.h"
#include "Texture/TextureManager.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
	SAFE_DELETE(m_AnimationManager);
	SAFE_DELETE(m_MaterialManager);
	SAFE_DELETE(m_TextureManager);
	SAFE_DELETE(m_ShaderManager);
	SAFE_DELETE(m_MeshManager);
}

bool CResourceManager::Init()
{
	m_ShaderManager = new CShaderManager;

	m_ShaderManager->Init();

	m_TextureManager = new CTextureManager;

	m_TextureManager->Init();

	m_MaterialManager = new CMaterialManager;

	m_MaterialManager->Init();

	m_MeshManager = new CMeshManager;

	m_MeshManager->Init();

	m_AnimationManager = new CAnimationManager;

	m_AnimationManager->Init();

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

CColliderConstantBuffer* CResourceManager::GetColliderCBuffer() const
{
	return m_ShaderManager->GetColliderCBuffer();
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

bool CResourceManager::LoadTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	return m_TextureManager->LoadTexture(Name, FileName, PathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	return m_TextureManager->LoadTextureFullPath(Name, FullPath);
}

bool CResourceManager::LoadTexture(const std::string& Name,
	const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	return m_TextureManager->LoadTexture(Name, vecFileName, PathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& Name, 
	const std::vector<const TCHAR*>& vecFullPath)
{
	return m_TextureManager->LoadTextureFullPath(Name, vecFullPath);
}

CTexture* CResourceManager::FindTexture(const std::string& Name)
{
	return m_TextureManager->FindTexture(Name);
}

void CResourceManager::ReleaseTexture(const std::string& Name)
{
	m_TextureManager->ReleaseTexture(Name);
}

CMaterial* CResourceManager::FindMaterial(const std::string& Name)
{
	return m_MaterialManager->FindMaterial(Name);
}

void CResourceManager::ReleaseMaterial(const std::string& Name)
{
	m_MaterialManager->ReleaseMaterial(Name);
}

bool CResourceManager::CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, const std::string& PathName)
{
	return m_AnimationManager->CreateAnimationSequence2D(Name, TextureName, FileName, PathName);
}

bool CResourceManager::CreateAnimationSequence2D(const std::string& Name, CTexture* Texture)
{
	return m_AnimationManager->CreateAnimationSequence2D(Name, Texture);
}

bool CResourceManager::CreateAnimationSequence2DFullPath(
	const std::string& Name, const std::string& TextureName,
	const TCHAR* FullPath)
{
	return m_AnimationManager->CreateAnimationSequence2DFullPath(Name, TextureName, FullPath);
}

bool CResourceManager::CreateAnimationSequence2D(const std::string& Name,
	const std::string& TextureName, 
	const std::vector<const TCHAR*>& vecFileName,
	const std::string& PathName)
{
	return m_AnimationManager->CreateAnimationSequence2D(Name, TextureName,
		vecFileName, PathName);
}

bool CResourceManager::CreateAnimationSequence2DFullPath(
	const std::string& Name, const std::string& TextureName, 
	const std::vector<const TCHAR*>& vecFullPath)
{
	return m_AnimationManager->CreateAnimationSequence2DFullPath(Name, TextureName,
		vecFullPath);
}

bool CResourceManager::AddAnimationSequence2DFrame(const std::string& Name, const Vector2& Start, const Vector2& End)
{
	return m_AnimationManager->AddSequence2DFrame(Name, Start, End);
}

bool CResourceManager::AddAnimationSequence2DFrame(const std::string& Name, float StartX, float StartY, float EndX, float EndY)
{
	return m_AnimationManager->AddSequence2DFrame(Name, StartX, StartY, EndX, EndY);
}

bool CResourceManager::AddAnimationSequence2DFrameAll(const std::string& Name, int Count, const Vector2& Start, const Vector2& End)
{
	return m_AnimationManager->AddSequence2DFrameAll(Name, Count, Start, End);
}

bool CResourceManager::AddAnimationSequence2DFrameAll(const std::string& Name, int Count, float StartX, float StartY, float EndX, float EndY)
{
	return m_AnimationManager->AddSequence2DFrameAll(Name, Count, StartX, StartY, EndX, EndY);
}

bool CResourceManager::SaveSequence2D(const std::string& Name, const char* FullPath)
{
	return m_AnimationManager->SaveSequence2D(Name, FullPath);
}

bool CResourceManager::LoadSequence2D(const std::string& Name, const char* FullPath)
{
	return m_AnimationManager->LoadSequence2D(Name, FullPath);
}

bool CResourceManager::SaveSequence2D(const std::string& Name, const char* FileName, const std::string& PathName)
{
	return m_AnimationManager->SaveSequence2D(Name, FileName, PathName);
}

bool CResourceManager::LoadSequence2D(const std::string& Name, const char* FileName, const std::string& PathName)
{
	return m_AnimationManager->LoadSequence2D(Name, FileName, PathName);
}

CAnimationSequence2D* CResourceManager::FindAnimationSequence2D(const std::string& Name)
{
	return m_AnimationManager->FindAnimationSequence2D(Name);
}

void CResourceManager::ReleaseAnimationSequence2D(const std::string& Name)
{
	m_AnimationManager->ReleaseAnimationSequence2D(Name);
}

CAnimation2DConstantBuffer* CResourceManager::GetAnim2DConstantBuffer() const
{
	return m_AnimationManager->GetAnim2DConstantBuffer();
}
