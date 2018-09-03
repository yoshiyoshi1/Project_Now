#ifndef __human_h__ 
#define __human_h__

class human {
public:
	void LoadXFile(void);							// ���b�V���f�[�^�ǂݍ���													
	void SetMapData(int* mapData);		// �}�b�v�����Z�b�g����֐�
	void LoadHuman(void);						// human�̓ǂݍ���
	void Update(void);					// human�̍X�V
	void DrawHuman(CVector3 _pos);		// human�̕`��

private:
	static const int SIZE_X = 80;
	static const int SIZE_Y = 80;
	static const int MAX_HUMAN = 80;

	int m_RouteData[SIZE_Y][SIZE_X];	// �}�b�v�̏��
	int d[MAX_HUMAN];							// �����p
	float move;
	bool moveflg;

	CMesh m_meshBoy;							// �j���b�V��
	CMesh m_meshGirl;							// �����b�V��
	CMesh m_meshIcon;							// �A�C�R�����b�V��

	CMatrix m[MAX_HUMAN];				// human�s��
	CMatrix micon[MAX_HUMAN];			// human�s��

};
#endif