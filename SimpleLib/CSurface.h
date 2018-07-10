#ifndef __CSurface_h__
#define __CSurface_h__

namespace SimpleLib{

//==================================
// サーフェイスクラス
//	特にZバッファの作成・セットが可能なことに重点を置いています
//==================================
class CSurface{
public:
	//==================================================================================
	// 取得
	//==================================================================================
	LPDIRECT3DSURFACE9		GetSur(){return m_lpSur;}		// サーフェイス取得
	D3DSURFACE_DESC*		GetDesc(){return &m_Desc;}		// 情報取得

	//==================================================================================
	// 作成
	//==================================================================================
	// Zバッファとして作成
	BOOL CreateDepthStencil(UINT Width, UINT Height, D3DFORMAT Format = D3DFMT_D24S8, D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_NONE, DWORD MultisampleQuality = 0, BOOL Discard = FALSE);

	//==================================================================================
	// 深度バッファとしてセットする
	//==================================================================================
	void SetDepthStencil();

	//==================================================================================
	// 解放
	//==================================================================================
	void Release();

	// 
	CSurface() : m_lpSur(0){
	}
	~CSurface(){
		Release();
	}

private:
	LPDIRECT3DSURFACE9		m_lpSur;
	D3DSURFACE_DESC			m_Desc;

private:
	// コピー禁止用
	CSurface(const CSurface& src){}
	void operator=(const CSurface& src){}
};

}
#endif