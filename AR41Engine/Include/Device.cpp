#include "Device.h"

DEFINITION_SINGLE(CDevice)

CDevice::CDevice()	:
	m_Device(nullptr),
	m_Context(nullptr),
	m_SwapChain(nullptr),
	m_TargetView(nullptr),
	m_DepthView(nullptr),
	m_RS{},
	m_hWnd(0)
{
}

CDevice::~CDevice()
{
	SAFE_RELEASE(m_TargetView);
	SAFE_RELEASE(m_DepthView);
	SAFE_RELEASE(m_SwapChain);

	if (m_Context)
		m_Context->ClearState();

	SAFE_RELEASE(m_Context);
	SAFE_RELEASE(m_Device);
}

bool CDevice::Init(HWND hWnd, unsigned int DeviceWidth, unsigned int DeviceHeight,
	bool WindowMode)
{
	m_hWnd = hWnd;
	m_RS.Width = DeviceWidth;
	m_RS.Height = DeviceHeight;

	unsigned int	Flag = 0;

#ifdef _DEBUG
	Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG


	return true;
}
