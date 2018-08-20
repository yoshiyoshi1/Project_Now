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
	float milliSecond = second * 1000;	// �~���b�Ɋ��Z

	// �w�肵���b��莞�Ԃ��o�߂��Ă���ꍇ�A���̎��Ԃ��Z�b�g����
	if (milliSecond <= ElapsedTime()) {
		SetTime();
		return true;
	}
	// ���Ԃ��o�߂��Ă��Ȃ��ꍇ�A
	else {
		return false;
	}
}

void Timer::SetTime()
{
	m_PrevTime = timeGetTime();
}
