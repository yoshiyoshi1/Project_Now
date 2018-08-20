#ifndef __map_h__ 
#define __map_h__

class map {
private:
	const int		MAPWIDTH = 80;		// Map�ő剡��
	const int		MAPHEIGHT = 80;	// Map�ő�c��

	void LoadXFile(void);						// ���b�V���f�[�^�ǂݍ���

public:
	void LoadMap(void);						// map�̓ǂݍ���
	void DrawMap(CVector3 _pos);		// map�̕`��

	// �n�`
	FILE* t_fp;									// �n�`file�|�C���^
	int t_MapData[80][80];					// �n�`map�f�[�^

	// ����
	FILE* b_fp;									// ����file�|�C���^
	int b_MapData[80][80];					// ����map�f�[�^
	
	CMesh m_meshLand;					// �n�`���b�V��
	CMesh m_meshRoad;					// ���H���b�V��
	CMesh m_meshSee;						// �C���b�V��
	CMesh m_meshSand;					// �����b�V��
	CMesh m_meshHouse[20];			// �������b�V��

	CMatrix m[80][80];						// map�s��
	CMatrix mSee[100][100];					// map�s��(�C�p)

};
#endif
