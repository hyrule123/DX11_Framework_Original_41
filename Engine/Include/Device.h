#pragma once

#include "EngineInfo.h"

class CDevice
{
private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_Context;
	IDXGISwapChain* m_SwapChain;

	ID3D11RenderTargetView* m_TargetView;
	ID3D11DepthStencilView* m_DepthView;

	HWND	m_hWnd;
	Resolution	m_RS;

public:
	Resolution GetResolution()	const
	{
		return m_RS;
	}

public:
	bool Init(HWND hWnd, unsigned int DeviceWidth, unsigned int DeviceHeight,
		bool WindowMode);

	DECLARE_SINGLE(CDevice)
};

