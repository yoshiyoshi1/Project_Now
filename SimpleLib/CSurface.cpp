#include "SimpleLib.h"

using namespace SimpleLib;

BOOL CSurface::CreateDepthStencil(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard)
{
	Release();

	HRESULT hr = cdg.GetDev()->CreateDepthStencilSurface(Width, Height, Format,MultiSample, MultisampleQuality, Discard, &m_lpSur, nullptr);
	if(hr != D3D_OK)return FALSE;

	m_lpSur->GetDesc(&m_Desc);

	return TRUE;
}

void CSurface::SetDepthStencil()
{
	cdg.GetDev()->SetDepthStencilSurface(m_lpSur);
}

void CSurface::Release()
{
	SAFE_RELEASE(m_lpSur);
	ZeroMemory(&m_Desc,sizeof(m_Desc));
}
