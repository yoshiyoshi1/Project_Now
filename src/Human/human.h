#ifndef __human_h__ 
#define __human_h__

class human {
private:
	void LoadXFile(void);							// ���b�V���f�[�^�ǂݍ���

public:
	void LoadHuman(void);						// human�̓ǂݍ���
	void DrawHuman(CVector3 _pos);		// human�̕`��

	int d[40];											// �����p

	CMesh m_meshBoy;							// �j���b�V��
	CMesh m_meshGirl;							// �����b�V��

	CMatrix m[40];									// human�s��

};
#endif