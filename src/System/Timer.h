#ifndef __Timer_h__
#define __Timer_h__

//*************************************************
//
//	���ԊǗ��N���X
//
//*************************************************
class Timer {
public:
	Timer();
	~Timer(){}

	// �o�ߎ��Ԃ��擾����֐�
	DWORD ElapsedTime();

	// �w�肵���b�A�o�߂��Ă��邩���擾����֐�
	//	�i�o�߂��Ă���ꍇ�A���̎��Ԃ��Z�b�g����j
	bool ElapsedTime(float second);

	// ���̎��Ԃ��Z�b�g����֐�
	void SetTime();

private:
	DWORD m_PrevTime;	// �O��̎���
};

#endif