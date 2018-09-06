#ifndef __CMesh_h__
#define __CMesh_h__

namespace SimpleLib{

//=================================================================
// ���b�V���N���X
//	X�t�@�C�����f����ǂݍ��݁E�`��(�Œ�@�\)���\�B
//�@����͎����ōs����
//=================================================================
class CMesh{
public:
	//===============================================================================================
	// ���擾�n
	//===============================================================================================
	LPD3DXMESH					GetMesh(){return m_lpMesh;}				// ���b�V���擾
	int							GetMaterialCnt(){return m_MaterialCnt;}	// �}�e���A�����擾
	CTexture*					GetTextures(){return m_Textures;}		// �e�N�X�`���z��擾
	D3DMATERIAL9*				GetMaterials(){return m_Materials;}		// �}�e���A���e�[�u���擾
	LPD3DXBUFFER				GetAdjacency(){return m_lpAdjacency;}	// �אڐ��f�[�^�擾

	
	CVector3 GetNormalVec(DWORD polyNo, CMatrix* mWorld)					// �@���x�N�g�����擾
	{ 
		CVector3 tmpVec = m_NormalVec[polyNo];
		tmpVec.TransformNormal(mWorld);			
		tmpVec.Normalize();
		return tmpVec; 
	}

	//===============================================================================================
	// �ǂݍ���
	//===============================================================================================
	// X�t�@�C���ǂݍ���
	BOOL LoadXFile(LPDIRECT3DDEVICE9 lpD3DDev, const char *lpFileName);
	BOOL LoadXFile(const char *lpFileName);

	//===============================================================================================
	// ���
	//===============================================================================================
	void Release();									// ���b�V�����

	//===============================================================================================
	// �`��֌W
	//===============================================================================================
	void Draw();									// ���b�V���`��
	void Draw(D3DXMATRIX* matrix);
	void Draw(D3DXMATRIX* matrix, D3DXCOLOR color);

	// 
	CMesh();
	~CMesh();

private:

	//=================================================================
	// �f�[�^
	//=================================================================
	LPD3DXMESH					m_lpMesh;		// ���b�V��
	CTexture*					m_Textures;		// �e�N�X�`���z��
	D3DMATERIAL9*				m_Materials;	// �}�e���A���z��
	int							m_MaterialCnt;	// �}�e���A����

	LPD3DXBUFFER				m_lpAdjacency;	// �אڐ��f�[�^
	std::string					m_FileName;		// �t�@�C����

	CVector3*					m_NormalVec;	// �@���x�N�g��
	

private:
	// �R�s�[�֎~�p
	//CMesh(const CMesh& src){}
	//void operator=(const CMesh& src){}

	void SetPolyNormal();
};

}
#endif
