
#include "BlendState.h"
#include "../Device.h"

CBlendState::CBlendState()	:
	m_SampleMask(0xffffffff),
	m_PrevSampleMask(0),
	m_BlendFactor{},
	m_PrevBlendFactor{}
{
	m_Type = ERenderStateType::Blend;
	SetTypeID<CBlendState>();
}

CBlendState::~CBlendState()
{
}

void CBlendState::AddBlendInfo(bool BlendEnable, D3D11_BLEND SrcBlend, 
	D3D11_BLEND DestBlend, D3D11_BLEND_OP BlendOp,
	D3D11_BLEND SrcAlphBlend, D3D11_BLEND DestAlphBlend,
	D3D11_BLEND_OP BlendAlphOp, UINT8 WriteMask)
{
	D3D11_RENDER_TARGET_BLEND_DESC	Desc = {};

	Desc.BlendEnable = BlendEnable;
	Desc.SrcBlend = SrcBlend;
	Desc.DestBlend = DestBlend;
	Desc.BlendOp = BlendOp;
	Desc.SrcBlendAlpha = SrcAlphBlend;
	Desc.DestBlendAlpha = DestAlphBlend;
	Desc.BlendOpAlpha = BlendAlphOp;
	Desc.RenderTargetWriteMask = WriteMask;

	m_vecDesc.push_back(Desc);
}

bool CBlendState::CreateState(bool AlphaToCoverageEnable, bool IndependentBlendEnable)
{
	if (m_vecDesc.empty())
		return false;

	D3D11_BLEND_DESC	Desc = {};

	Desc.AlphaToCoverageEnable = AlphaToCoverageEnable;
	Desc.IndependentBlendEnable = IndependentBlendEnable;

	for (int i = 0; i < 8; ++i)
	{
		Desc.RenderTarget[i].BlendEnable = false;
		Desc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[i].DestBlend = D3D11_BLEND_ZERO;
		Desc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
		Desc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	memcpy(Desc.RenderTarget, &m_vecDesc[0], sizeof(D3D11_RENDER_TARGET_BLEND_DESC) * m_vecDesc.size());

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBlendState(&Desc,
		(ID3D11BlendState**)&m_State)))
		return false;

	return true;
}

void CBlendState::SetState()
{
	CDevice::GetInst()->GetContext()->OMGetBlendState((ID3D11BlendState**)&m_PrevState,
		m_PrevBlendFactor, &m_PrevSampleMask);

	CDevice::GetInst()->GetContext()->OMSetBlendState((ID3D11BlendState*)m_State,
		m_BlendFactor, m_SampleMask);
}

void CBlendState::ResetState()
{
	CDevice::GetInst()->GetContext()->OMSetBlendState((ID3D11BlendState*)m_PrevState,
		m_PrevBlendFactor, m_PrevSampleMask);

	SAFE_RELEASE(m_PrevState);
}
