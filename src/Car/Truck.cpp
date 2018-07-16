#include "../main.h"

#include "CarBase.h"
#include "Truck.h" 
 
 
Truck::Truck() { 
	carType = CarType::Bus;
} 
 
Truck::~Truck() { 
 
}

void Truck::Update()
{
	Move(MAX_SPEED);

}

void Truck::Draw()
{
	Body.Draw(&bodyMat);
	FTire.Draw(&tmpTireMat[TirePos::FR]);
	FTire.Draw(&tmpTireMat[TirePos::FL]);
	RTire.Draw(&tmpTireMat[TirePos::R1]);
}
