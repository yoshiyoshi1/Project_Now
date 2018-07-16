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
	//加減速
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
		//前進しているか後退しているかの判定
		if (Speed >= 0.01) { isForword = true; }
		else { isForword = false; }
		if (Speed <= -0.01) { isBack = true; }
		else { isBack = false; }

		//キーを押していないときに減速させる
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
	//旋回
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

		//タイヤのX軸回転
		/*for (auto &i : tireMat) {
			i.RotateX_Local(Speed);

		}*/
		//前タイヤのY軸回転
		CMatrix tmp[2];

		for (int i = 0; i <= TirePos::FL; i++) {
			tmp[i].CreateRotateY(FTireRot);
			tireMat[i] = tmp[i]*tireMat[i];
		}
	}

	

	/*タイヤ位置合わせ用
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


	//車体とタイヤの親子構造
	for (auto i : tmpTireMat) { i.CreateIdentity(); }
	tmpTireMat[TirePos::FR] = tireMat[TirePos::FR] * bodyMat;
	tmpTireMat[TirePos::FL] = tireMat[TirePos::FL] * bodyMat;
	tmpTireMat[TirePos::R1] = tireMat[TirePos::R1] * bodyMat;
	tmpTireMat[TirePos::R2] = tireMat[TirePos::R2] * bodyMat;
}

