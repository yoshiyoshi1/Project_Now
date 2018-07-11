#include "../main.h"
#include "CarBase.h"
#include "Taxi.h"

Taxi::Taxi()
{
	//メッシュのロード
	body.LoadXFile("../data/Mesh/Car/Taxi/Taxi.x");
	FTire.LoadXFile("../data/Mesh/Car/Tire/FrontTire.x");
	RTire.LoadXFile("../data/Mesh/Car/Tire/RearTire.x");
	mat.CreateMove(0, -2, 500);
	//mat.CreateRotateY(45);
	Tiremat.CreateMove(-50,0,0);
}

Taxi::~Taxi()
{
	body.Release();
}

void Taxi::Update()
{
	if (GetAsyncKeyState('W')) {
		mat.Move_Local(0, 0, 1);
	}
	if (GetAsyncKeyState('S')) {
		mat.Move_Local(0, 0, -1);
	}
	if (GetAsyncKeyState('A')) {
		mat.Move_Local(-1, 0, 0);
	}
	if (GetAsyncKeyState('D')) {
		mat.Move_Local(1, 0, 0);
	}
	if (GetAsyncKeyState('E')) {
		mat.RotateY_Local(5);
	}
	if (GetAsyncKeyState('Q')) {
		mat.RotateY_Local(-5);
	}
	
	tmp.CreateIdentity();
	tmp = Tiremat * mat;

}

void Taxi::Draw()
{
	body.Draw(&mat);
	FTire.Draw(&tmp);
}
