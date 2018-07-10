#include "SimpleLib.h"

using namespace SimpleLib;

CTexture::CTexture()
{
	m_lpTex = nullptr;
	m_lpSur = nullptr;
	ZeroMemory(&m_Info,sizeof(m_Info));
	SetRect(&m_rc,0,0,0,0);
}

CTexture::~CTexture()
{
	Release();
}

BOOL CTexture::LoadTexture(LPCTSTR pSrcFile, bool nonPow2)
{
	Release();

	m_strName = pSrcFile;

	UINT sizeFlag = D3DX_DEFAULT;
	if (nonPow2) {
		sizeFlag = D3DX_DEFAULT_NONPOW2;
	}

	HRESULT hr;
	//hr = D3DXCreateTextureFromFile(cdg.GetDev(), pSrcFile, &m_lpTex);

	// テクスチャ読み込み
	hr = D3DXCreateTextureFromFileEx(cdg.GetDev(),
		pSrcFile,
		sizeFlag,			// Width
		sizeFlag,			// Height
		D3DX_DEFAULT,		// MipLevels,
		0,					// Usage,
		D3DFMT_UNKNOWN,		// Format,
		D3DPOOL_MANAGED,	// Pool
		D3DX_DEFAULT,		// Filter,
		D3DX_DEFAULT,		// MipFilter,
		0,					// ColorKey,		//カラーキー ARGBで指定。0で無し。 
		&m_Info,
		nullptr,
		&m_lpTex);

	if(hr != S_OK)
	{
		return FALSE;
	}

	// サーフェイス取得
	hr = m_lpTex->GetSurfaceLevel(0,&m_lpSur);
	if(hr != D3D_OK){
		return FALSE;
	}

	// 情報取得
	D3DSURFACE_DESC desc;
	m_lpTex->GetLevelDesc(0, &desc);

	// 画像のRECTも作成しとこ
	SetRect(&m_rc, 0, 0, m_Info.Width, m_Info.Height);

	return TRUE;
}


BOOL CTexture::LoadTextureEx(
    LPCTSTR pSrcFile,
    UINT Width,
    UINT Height,
    UINT MipLevels,
    DWORD Usage,
    D3DFORMAT Format,
    D3DPOOL Pool,
    DWORD Filter,
    DWORD MipFilter,
    D3DCOLOR ColorKey,
    PALETTEENTRY *pPalette
)
{
	Release();

	m_strName = pSrcFile;

	HRESULT hr;

	// テクスチャ読み込み
	hr = D3DXCreateTextureFromFileEx(cdg.GetDev(),
								pSrcFile,
								Width,
								Height,
								MipLevels,
								Usage,
								Format,
								Pool,
								Filter,
								MipFilter,
								ColorKey,		//カラーキー ARGBで指定。0で無し。 
								&m_Info,
								pPalette,
								&m_lpTex);
	if(hr != D3D_OK){
		return FALSE;
	}

	// サーフェイスアドレス取得
	hr = m_lpTex->GetSurfaceLevel(0,&m_lpSur);
	if(hr != D3D_OK){
		return FALSE;
	}

	// 情報取得
	D3DSURFACE_DESC desc;
	m_lpTex->GetLevelDesc(0,&desc);

	// 画像のRECTも作成しとこ
	SetRect(&m_rc,0,0,m_Info.Width,m_Info.Height);


	return TRUE;
}

BOOL CTexture::CreateTexture(
					UINT Width,
					UINT Height,
					UINT MipLevels,
					DWORD Usage,
					D3DFORMAT Format,
					D3DPOOL Pool
){
	Release();

	HRESULT hr;
	hr = D3DXCreateTexture(cdg.GetDev(),Width,Height,MipLevels,Usage,Format,Pool,&m_lpTex);
	if(hr != D3D_OK){
		return FALSE;
	}

	// サーフェイスアドレス取得
	hr = m_lpTex->GetSurfaceLevel(0,&m_lpSur);
	if(hr != D3D_OK){
		return FALSE;
	}

	// 画像情報作成
	D3DSURFACE_DESC desc;
	m_lpSur->GetDesc(&desc);

	m_Info.Width = desc.Width;
	m_Info.Height = desc.Height;
	m_Info.MipLevels = m_lpTex->GetLevelCount();
	m_Info.Format = desc.Format;

	SetRect(&m_rc,0,0,m_Info.Width,m_Info.Height);

	// 情報取得
	m_lpTex->GetLevelDesc(0, &desc);

	return TRUE;
}

void CTexture::SetTexture(DWORD StageNo)
{
	cdg.GetDev()->SetTexture(StageNo, m_lpTex);
}

HRESULT CTexture::SetRenderTarget(DWORD Index)
{
	return cdg.GetDev()->SetRenderTarget(Index, m_lpSur);
}

void CTexture::Release()
{
	SAFE_RELEASE(m_lpSur);// サーフェス解放
	SAFE_RELEASE(m_lpTex);// テクスチャー解放
	m_strName.clear();

	ZeroMemory(&m_Info,sizeof(m_Info));
	SetRect(&m_rc,0,0,0,0);
}
