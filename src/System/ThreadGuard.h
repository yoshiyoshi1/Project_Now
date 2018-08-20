#ifndef __ThreadGuard_h__
#define __ThreadGuard_h__

//*************************************************
//
//	マルチスレッド用　安全に処理を行うためのクラス
//
//*************************************************

class ThreadGuard {
public:
	explicit ThreadGuard(std::thread& _thread) : thread(_thread) {}
	
	~ThreadGuard() 
	{
		// スレッドが関連付けされている場合
		if (thread.joinable())
			thread.join();	// スレッドの終了を待機
	}

	// コピーを禁止し、ムーブを許可する
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