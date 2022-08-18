
#include "RenderStateManager.h"
#include "BlendState.h"

CRenderStateManager::CRenderStateManager()
{
}

CRenderStateManager::~CRenderStateManager()
{
}

bool CRenderStateManager::Init()
{
	AddBlendInfo("AlphaBlend");
	CreateBlendState("AlphaBlend", false, false);

	return true;
}

void CRenderStateManager::SetBlendFactor(const std::string& Name, float r, float g, float b, float a)
{
	CBlendState* State = FindRenderState<CBlendState>(Name);

	if (!State)
	{
		State = new CBlendState;

		State->SetName(Name);

		m_mapState.insert(std::make_pair(Name, State));
	}

	State->SetBlendFactor(r, g, b, a);
}

void CRenderStateManager::AddBlendInfo(const std::string& Name, bool BlendEnable,
	D3D11_BLEND SrcBlend, D3D11_BLEND DestBlend, D3D11_BLEND_OP BlendOp,
	D3D11_BLEND SrcAlphBlend, D3D11_BLEND DestAlphBlend, D3D11_BLEND_OP BlendAlphOp,
	UINT8 WriteMask)
{
	CBlendState* State = FindRenderState<CBlendState>(Name);

	if (!State)
	{
		State = new CBlendState;

		State->SetName(Name);

		m_mapState.insert(std::make_pair(Name, State));
	}

	State->AddBlendInfo(BlendEnable, SrcBlend, DestBlend, BlendOp, SrcAlphBlend,
		DestAlphBlend, BlendAlphOp, WriteMask);
}

bool CRenderStateManager::CreateBlendState(const std::string& Name, 
	bool AlphaToCoverageEnable, bool IndependentBlendEnable)
{
	CBlendState* State = FindRenderState<CBlendState>(Name);

	if (!State)
		return false;

	if (!State->CreateState(AlphaToCoverageEnable, IndependentBlendEnable))
	{
		SAFE_RELEASE(State);
		return false;
	}

	return true;
}
