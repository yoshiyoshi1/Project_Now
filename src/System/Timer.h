#ifndef __Timer_h__
#define __Timer_h__

//*************************************************
//
//	時間管理クラス
//
//*************************************************
class Timer {
public:
	Timer();
	~Timer(){}

	// 経過時間を取得する関数
	DWORD ElapsedTime();

	// 指定した秒、経過しているかを取得する関数
	//	（経過している場合、今の時間をセットする）
	bool ElapsedTime(float second);

	// 今の時間をセットする関数
	void SetTime();

private:
	DWORD m_PrevTime;	// 前回の時間
};

#endif