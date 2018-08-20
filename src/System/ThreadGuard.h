#ifndef __ThreadGuard_h__
#define __ThreadGuard_h__

//*************************************************
//
//	�}���`�X���b�h�p�@���S�ɏ������s�����߂̃N���X
//
//*************************************************

class ThreadGuard {
public:
	explicit ThreadGuard(std::thread& _thread) : thread(_thread) {}
	
	~ThreadGuard() 
	{
		// �X���b�h���֘A�t������Ă���ꍇ
		if (thread.joinable())
			thread.join();	// �X���b�h�̏I����ҋ@
	}

	// �R�s�[���֎~���A���[�u��������
	ThreadGuard(ThreadGuard const&) = delete;
	ThreadGuard& operator=(ThreadGuard const&) = delete;

	void SetThread(std::thread& _thread)
	{
		thread = std::move(_thread);
	}

private:
	std::thread& thread;

};

#endif