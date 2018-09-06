#ifndef __CMesh_h__
#define __CMesh_h__

namespace SimpleLib{

//=================================================================
// メッシュクラス
//	Xファイルモデルを読み込み・描画(固定機能)が可能。
//　解放は自動で行われる
//=================================================================
class CMesh{
public:
	//===============================================================================================
	// 情報取得系
	//===============================================================================================
	LPD3DXMESH					GetMesh(){return m_lpMesh;}				// メッシュ取得
	int							GetMaterialCnt(){return m_MaterialCnt;}	// マテリアル数取得
	CTexture*					GetTextures(){return m_Textures;}		// テクスチャ配列取得
	D3DMATERIAL9*				GetMaterials(){return m_Materials;}		// マテリアルテーブル取得
	LPD3DXBUFFER				GetAdjacency(){return m_lpAdjacency;}	// 隣接性データ取得

	
	CVector3 GetNormalVec(DWORD polyNo, CMatrix* mWorld)					// 法線ベクトルを取得
	{ 
		CVector3 tmpVec = m_NormalVec[polyNo];
		tmpVec.TransformNormal(mWorld);			
		tmpVec.Normalize();
		return tmpVec; 
	}

	//===============================================================================================
	// 読み込み
	//===============================================================================================
	// Xファイル読み込み
	BOOL LoadXFile(LPDIRECT3DDEVICE9 lpD3DDev, const char *lpFileName);
	BOOL LoadXFile(const char *lpFileName);

	//===============================================================================================
	// 解放
	//===============================================================================================
	void Release();									// メッシュ解放

	//===============================================================================================
	// 描画関係
	//===============================================================================================
	void Draw();									// メッシュ描画
	void Draw(D3DXMATRIX* matrix);
	void Draw(D3DXMATRIX* matrix, D3DXCOLOR color);

	// 
	CMesh();
	~CMesh();

private:

	//=================================================================
	// データ
	//=================================================================
	LPD3DXMESH					m_lpMesh;		// メッシュ
	CTexture*					m_Textures;		// テクスチャ配列
	D3DMATERIAL9*				m_Materials;	// マテリアル配列
	int							m_MaterialCnt;	// マテリアル数

	LPD3DXBUFFER				m_lpAdjacency;	// 隣接性データ
	std::string					m_FileName;		// ファイル名

	CVector3*					m_NormalVec;	// 法線ベクトル
	

private:
	// コピー禁止用
	//CMesh(const CMesh& src){}
	//void operator=(const CMesh& src){}

	void SetPolyNormal();
};

}
#endif
