#include "../main.h"
#include "CarBase.h"
#include "Taxi.h"

Taxi::Taxi()
{
	carType = CarType::Taxi;

	//メッシュのロード
	Body.LoadXFile("../data/Mesh/Car/Taxi/Taxi.x");
	FTire.LoadXFile("../data/Mesh/Car/Tire/FrontTire.x");
	RTire.LoadXFile("../data/Mesh/Car/Tire/RearTire.x");
	bodyMat.CreateMove(0, -3.5f, 0);
	bodyMat.Scale_Local(0.005f, 0.005f, 0.005f);

	tireTrans[TirePos::FR].CreateMove(45, -26, 54);
	tireTrans[TirePos::FL].CreateMove(-45, -26, 54);
	tireTrans[TirePos::R1].CreateMove(0, -26, -54);
}

Taxi::~Taxi()
{
	Body.Release();
	FTire.Release();
	RTire.Release();
}

void Taxi::Update()
{
	Move(MAX_SPEED);

}

void Taxi::Draw()
{
	Body.Draw(&bodyMat);
	FTire.Draw(&tmpTireMat[TirePos::FR]);
	FTire.Draw(&tmpTireMat[TirePos::FL]);
	RTire.Draw(&tmpTireMat[TirePos::R1]);
}
