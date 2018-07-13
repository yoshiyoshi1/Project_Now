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
	if (GetAsyncKeyState('W')) {
		Speed += 0.1f;
	}

	if (KINPUT->isDoubleInput(500)) {
		Speed = maxSpeed;
	}

	if (GetAsyncKeyState('S')) {
		Speed -= 0.2f;
	}

	if (Speed > maxSpeed) {
		Speed = maxSpeed;
	}
	bodyMat.Move_Local(0, 0, Speed);

	//旋回
	if (GetAsyncKeyState('D')) {
		bodyMat.RotateY_Local(1);
	}
	if (GetAsyncKeyState('A')) {
		bodyMat.RotateY_Local(-1);
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

	//タイヤの回転
	for (auto &i : tireMat) {
		i.RotateX_Local(Speed);
	}

	//車体とタイヤの親子構造
	for (auto i : tmpTireMat) { i.CreateIdentity(); }
	tmpTireMat[TirePos::FR] = tireMat[TirePos::FR] * bodyMat;
	tmpTireMat[TirePos::FL] = tireMat[TirePos::FL] * bodyMat;
	tmpTireMat[TirePos::R1] = tireMat[TirePos::R1] * bodyMat;
	tmpTireMat[TirePos::R2] = tireMat[TirePos::R2] * bodyMat;
}

