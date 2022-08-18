#pragma once

#include "../EngineInfo.h"

class CRenderStateManager
{
	friend class CRenderManager;

private:
	CRenderStateManager();
	~CRenderStateManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CRenderState>>	m_mapState;

public:
	bool Init();

public:
	void SetBlendFactor(const std::string& Name, float r, float g, float b, float a);
	void AddBlendInfo(const std::string& Name, bool BlendEnable = true, 
		D3D11_BLEND SrcBlend = D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND DestBlend = D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_OP BlendOp = D3D11_BLEND_OP_ADD,
		D3D11_BLEND SrcAlphBlend = D3D11_BLEND_ONE,
		D3D11_BLEND DestAlphBlend = D3D11_BLEND_ZERO,
		D3D11_BLEND_OP BlendAlphOp = D3D11_BLEND_OP_ADD,
		UINT8 WriteMask = D3D11_COLOR_WRITE_ENABLE_ALL);
	bool CreateBlendState(const std::string& Name, bool AlphaToCoverageEnable, bool IndependentBlendEnable);

public:
	template <typename T>
	T* FindRenderState(const std::string& Name)
	{
		auto	iter = m_mapState.find(Name);

		if (iter == m_mapState.end())
			return nullptr;

		return (T*)iter->second.Get();
	}
};

