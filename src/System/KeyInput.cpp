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
			//���Ԃ�ۑ�
			time.push_back(timeGetTime());

			//�f�[�^����ȏ゠�邩�H(vector�͈̔͊O���Q�Ƃ��Ȃ��悤��)
			if (time.size() >= 2) {
				auto interval = time[1] - time[0];		//���͂̊Ԋu�����߂�
				if (interval < ms) {
					time.clear();
					return true;
				}
				time.erase(time.begin());				//�P��ڂɓ��͂������Ԃ��폜
			}
			keyflg = true;
		}
	}
	else { keyflg = false; }
	return false;
}

