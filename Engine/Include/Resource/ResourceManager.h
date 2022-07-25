#pragma once

#include "../EngineInfo.h"
#include "Shader/ShaderManager.h"

class CResourceManager
{
private:
	class CMeshManager* m_MeshManager;
	CShaderManager* m_ShaderManager;

public:
	bool Init();
	void Update();


public:	// ===================== Mesh =========================
	bool CreateMesh(class CScene* Scene, MeshType Type, const std::string& Name,
		void* VtxData, int Size, int Count,
		D3D11_USAGE VtxUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IdxData = nullptr, int IdxSize = 0, int IdxCount = 0,
		D3D11_USAGE IdxUsage = D3D11_USAGE_DEFAULT,
		DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN);

	class CMesh* FindMesh(const std::string& Name);
	void ReleaseMesh(const std::string& Name);



public:	// ===================== Shader =========================
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		return m_ShaderManager->CreateShader<T>(Name);
	}

	class CShader* FindShader(const std::string& Name);
	void ReleaseShader(const std::string& Name);



	DECLARE_SINGLE(CResourceManager)
};

