#include "../main.h"
#include "CarBase.h"

CarBase::CarBase() {

}

CarBase::~CarBase() {

}

void CarBase::Update()
{
}

void CarBase::Draw() {

}

void CarBase::Move(float maxSpeed)
{
	//������
	{
		if (GetAsyncKeyState('W')) {
			Speed += 0.1f;
		}
		if (KINPUT->isDoubleInput(400)) {
			Speed = maxSpeed;
		}
		if (GetAsyncKeyState('S')) {
			Speed -= 0.2f;
		}
		//�O�i���Ă��邩��ނ��Ă��邩�̔���
		if (Speed >= 0.01) { isForword = true; }
		else { isForword = false; }
		if (Speed <= -0.01) { isBack = true; }
		else { isBack = false; }

		//�L�[�������Ă��Ȃ��Ƃ��Ɍ���������
		if (!(GetAsyncKeyState('W') || GetAsyncKeyState('S'))) {
			if (isForword) {
				Speed -= reduce;
			}
			else if (isBack) {
				Speed += reduce;
			}
		}

		if (Speed >= maxSpeed) { Speed = maxSpeed; }
		if (Speed <= (-maxSpeed)*0.3f) { Speed = (-maxSpeed)* 0.3f; }

		bodyMat.Move_Local(0, 0, Speed);
	}
	//����
	{
		if (isForword || isBack) {
			if (GetAsyncKeyState('D')) {
				bodyMat.RotateY_Local(1.5f);
				FTireRot += 0.1f;
			}
			if (GetAsyncKeyState('A')) {
				bodyMat.RotateY_Local(-1.5f);
				FTireRot -= 0.1f;
			}
		}
		if (!(GetAsyncKeyState('D') || GetAsyncKeyState('A'))) {
			if (FTireRot >= 0.01f) {
				FTireRot -= 0.05f;
			}
			else if (FTireRot) {
				FTireRot += 0.05f;
			}
		}

		/*CMatrix tmpX, tmpY;

		tmpX.CreateRotateX(Speed);
		tmpY.CreateRotateY(FTireRot);

		tireMat[TirePos::FR] = tmpY * tmpX*tireMat[TirePos::FR];*/

		//�^�C����X����]
		/*for (auto &i : tireMat) {
			i.RotateX_Local(Speed);

		}*/
		//�O�^�C����Y����]
		CMatrix tmp[2];

		for (int i = 0; i <= TirePos::FL; i++) {
			tmp[i].CreateRotateY(FTireRot);
			tireMat[i] = tmp[i]*tireMat[i];
		}
	}

	

	/*�^�C���ʒu���킹�p
	if (GetAsyncKeyState('A')) {
	bodyMat.Move_Local(-1, 0, 0);
	}
	if (GetAsyncKeyState('D')) {
	bodyMat.Move_Local(1, 0, 0);
	}
	if (GetAsyncKeyState('E')) {
	bodyMat.RotateY_Local(5);
	}
	if (GetAsyncKeyState('Q')) {
	bodyMat.RotateY_Local(-5);
	}
	if (GetAsyncKeyState('Z')) {
	bodyMat.RotateX_Local(5);
	}
	if (GetAsyncKeyState('C')) {
	bodyMat.RotateX_Local(-5);
	}*/


	//�ԑ̂ƃ^�C���̐e�q�\��
	for (auto i : tmpTireMat) { i.CreateIdentity(); }
	tmpTireMat[TirePos::FR] = tireMat[TirePos::FR] * bodyMat;
	tmpTireMat[TirePos::FL] = tireMat[TirePos::FL] * bodyMat;
	tmpTireMat[TirePos::R1] = tireMat[TirePos::R1] * bodyMat;
	tmpTireMat[TirePos::R2] = tireMat[TirePos::R2] * bodyMat;
}

