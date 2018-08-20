#include "../main.h"

#include "Timer.h"

Timer::Timer()
{
	SetTime();
}

DWORD Timer::ElapsedTime()
{
	return timeGetTime() - m_PrevTime;
}

bool Timer::ElapsedTime(float second)
{
	float milliSecond = second * 1000;	// ミリ秒に換算

	// 指定した秒より時間が経過している場合、今の時間をセットする
	if (milliSecond <= ElapsedTime()) {
		SetTime();
		return true;
	}
	// 時間が経過していない場合、
	else {
		return false;
	}
}

void Timer::SetTime()
{
	m_PrevTime = timeGetTime();
}
