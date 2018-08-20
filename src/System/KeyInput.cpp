#include "../main.h"

#include "KeyInput.h"

KeyInput *KeyInput::m_lpInstance = NULL;

KeyInput::KeyInput() 
{
	m_lpInstance = this;
}

KeyInput::~KeyInput()
{

}

boolean KeyInput::isDoubleInput(const float ms)
{
	if (GetAsyncKeyState('W') & 0x8000) {
		if (!keyflg) {
			//時間を保存
			time.push_back(timeGetTime());

			//データが二つ以上あるか？(vectorの範囲外を参照しないように)
			if (time.size() >= 2) {
				auto interval = time[1] - time[0];		//入力の間隔を求める
				if (interval < ms) {
					time.clear();
					return true;
				}
				time.erase(time.begin());				//１回目に入力した時間を削除
			}
			keyflg = true;
		}
	}
	else { keyflg = false; }
	return false;
}

