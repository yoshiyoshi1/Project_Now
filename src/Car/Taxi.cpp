#include "../main.h"
#include "CarBase.h"
#include "Taxi.h"

Taxi::Taxi()
{
	//メッシュのロード
	body.LoadXFile("../data/Mesh/Car/Taxi/Taxi.x");
	FTire.LoadXFile("../data/Mesh/Car/Tire/FrontTire.x");
	RTire.LoadXFile("../data/Mesh/Car/Tire/RearTire.x");
	bodyMat.CreateMove(0, -2, 500);
	//bodyMat.CreateRotateY(45);
	tireMat[TirePos::FR].CreateMove(45, -26, 54);
	tireMat[TirePos::FL].CreateMove(-45, -26, 54);
	tireMat[TirePos::R1].CreateMove(0, -26, -54);
}

Taxi::~Taxi()
{
	body.Release();
}

void Taxi::Update()
{
	Move();

}

void Taxi::Draw()
{
	body.Draw(&bodyMat);
	FTire.Draw(&tmpTireMat[TirePos::FR]);
	FTire.Draw(&tmpTireMat[TirePos::FL]);
	RTire.Draw(&tmpTireMat[TirePos::R1]);
}
