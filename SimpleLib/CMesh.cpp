#include "SimpleLib.h"

using namespace SimpleLib;

// コンストラクタ
CMesh::CMesh()
{
	m_lpMesh = nullptr;
	m_MaterialCnt = 0;
	m_Textures = nullptr;
	m_Materials = nullptr;
	m_lpAdjacency = nullptr;
}
// デストラクタ
CMesh::~CMesh()
{
	Release();
}



BOOL CMesh::LoadXFile(LPDIRECT3DDEVICE9 lpD3DDev,const char *lpFileName)
{
	// パス、ファイル名分解
	std::string Path;
	char szDir  [_MAX_PATH]; 
	char szFname[_MAX_FNAME]; 
	char szExt  [_MAX_EXT]; 
	_splitpath( lpFileName, nullptr, szDir, szFname, szExt);
	Path = szDir;
	m_FileName = szFname;
	m_FileName += szExt;

	HRESULT hr;

	LPD3DXBUFFER	pD3DXMtrlBuffer;

	// Xファイル読み込み
	DWORD mateNum;
	hr = D3DXLoadMeshFromX( lpFileName, 
							D3DXMESH_MANAGED, 
							lpD3DDev, 
							&m_lpAdjacency, 
							&pD3DXMtrlBuffer, // マテリアルデータを格納するための変数を指定
							nullptr,
							&mateNum, // マテリアル数を格納するための変数を指定
							&m_lpMesh);	// メッシュデータを格納するための変数を指定
	if(FAILED(hr)) return FALSE;

	// マテリアル数
	m_MaterialCnt = mateNum;
	// pD3DXMtrlBuffer から、質感やテクスチャーの情報を読み取る
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	// メッシュのマテリアルの総数に基づいて、マテリアル配列を作成
	m_Textures = new CTexture[mateNum];
	m_Materials = new D3DMATERIAL9[mateNum];

	// マテリアルコピー、テクスチャ読み込み
	std::string strTexFile;
	for(DWORD i=0; i<mateNum; i++ ){
		// 材質
		m_Materials[i] = d3dxMaterials[i].MatD3D;			// 質感のコピー
		m_Materials[i].Ambient = m_Materials[i].Diffuse;	// AmbientはDiffuseのコピーを使用

		// テクスチャ名
		strTexFile = Path;
		if(d3dxMaterials[i].pTextureFilename)strTexFile += d3dxMaterials[i].pTextureFilename;

		// テクスチャ読み込み
		m_Textures[i].LoadTexture(strTexFile.c_str());
	}

	// 作業用マテリアル バッファ開放
	SAFE_RELEASE(pD3DXMtrlBuffer);

	return TRUE;
}
BOOL CMesh::LoadXFile(const char *lpFileName)
{
	if (LoadXFile(cdg.GetDev(), lpFileName) == FALSE) {
		return FALSE;
	}

	return TRUE;
}

void CMesh::Release()
{
	// 全マテリアル解放
	for(int i=0;i<m_MaterialCnt;i++){
		m_Textures[i].Release();
	}
	m_MaterialCnt = 0;

	SAFE_DELETE_ARRAY(m_Textures);
	SAFE_DELETE_ARRAY(m_Materials);

	// 隣接面データ削除
	SAFE_RELEASE(m_lpAdjacency);

	// メッシュ オブジェクト解放
	SAFE_RELEASE(m_lpMesh);

	m_FileName = "";
}

void CMesh::Draw()
{
	// マテリアルの数ぶんループ
	for(int i=0; i < m_MaterialCnt; i++ ){
		// i番目のマテリアルを設定
		cdg.GetDev()->SetMaterial( &m_Materials[i] );
		// i番目のテクスチャを設定
		cdg.GetDev()->SetTexture( 0, m_Textures[i].GetTex() );

		// i番目のマテリアルのメッシュを描画
		m_lpMesh->DrawSubset( i );
	}
}

void CMesh::Draw(D3DXMATRIX* matrix) 
{
	cdg.GetDev()->SetTransform(D3DTS_WORLD, matrix);
	Draw();
}
