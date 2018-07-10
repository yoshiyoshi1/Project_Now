#ifndef __CTexture_h__
#define __CTexture_h__

namespace SimpleLib{

//==============================================================================================
// テクスチャクラス
//	テクスチャの読み込み、RTテクスチャの作成・セットなどが可能
//　解放は自動で行われる
//==============================================================================================
class CTexture{
public:
	//===============================================================================================
	// 情報取得
	//===============================================================================================
	LPDIRECT3DTEXTURE9	GetTex(){return m_lpTex;}	// テクスチャ取得
	LPDIRECT3DSURFACE9	GetSur(){return m_lpSur;}	// サーフェイス取得
	RECT*				GetRect(){return &m_rc;}	// RECT取得
	std::string			GetName(){return m_strName;}// ファイル名
	D3DXIMAGE_INFO*		GetInfo(){return &m_Info;}	// 情報

	//===============================================================================================
	// 読み込み・作成
	//===============================================================================================

	// 簡易版ファイルからテクスチャ読み込み
	// [引数] nonPow2 … 読み込んだテクスチャを2のべき乗に拡縮しないようにする
	BOOL LoadTexture(LPCTSTR pSrcFile, bool nonPow2 = true);


	// ファイルからテクスチャ読み込み(拡張)
	// 引数はD3DXCreateTextureFromFileEx()とほぼ同じ
	BOOL LoadTextureEx(
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
						);

	// テクスチャ作成
	BOOL CreateTexture(	
						UINT Width,
						UINT Height,
						UINT MipLevels,
						DWORD Usage,
						D3DFORMAT Format,
						D3DPOOL Pool
						);

	// レンダーターゲットテクスチャとして作成
	BOOL CreateRenderTarget(UINT Width,	UINT Height, D3DFORMAT Format = D3DFMT_A8R8G8B8){
		return CreateTexture(Width, Height, 1, D3DUSAGE_RENDERTARGET, Format, D3DPOOL_DEFAULT);
	}

	//===============================================================================================
	// テクスチャをデバイスに設定
	//===============================================================================================
	void SetTexture(DWORD StageNo=0);

	//===============================================================================================
	// 解放
	//===============================================================================================
	void Release();
	
	//===============================================================================================
	// レンダーターゲットに設定
	//===============================================================================================
	HRESULT SetRenderTarget(DWORD Index=0);

	//===============================================================================================
	// 直接加工
	//===============================================================================================
	template<class T>
	bool Fill(T fill, DWORD LockFlag=0);	// 塗りつぶし

	// 
	CTexture();
	~CTexture();

private:
	LPDIRECT3DTEXTURE9	m_lpTex;		// テクスチャ
	LPDIRECT3DSURFACE9	m_lpSur;		// サーフェイス
	D3DXIMAGE_INFO		m_Info;			// 情報
	RECT				m_rc;			// RECT
	std::string			m_strName;		// ファイル名

private:
	// コピー禁止用
	CTexture(const CTexture& src){}
	void operator=(const CTexture& src){}
};



// 
template<class T>
bool CTexture::Fill(T fill,DWORD LockFlag)
{
	D3DLOCKED_RECT LockedRect;
	// ロックして、ピクセルの先頭アドレス取得
	if(SUCCEEDED(m_lpTex->LockRect(0, &LockedRect, nullptr, LockFlag))){
		//==================================
		//ここで画像データを転送
		//==================================
		T* p1 = (T*)LockedRect.pBits;
		T pitch = LockedRect.Pitch / sizeof(T);
		for ( UINT y = 0; y < m_Info.Height ; y++ )
		{
			for ( UINT x = 0; x < m_Info.Width; x++ )
			{
				p1[x] = fill;
			}
			p1 += pitch;    //次の行
		}
	
		m_lpTex->UnlockRect(0);
		return true;
	}
	return false;
}

}

#endif
