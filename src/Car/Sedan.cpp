#include "../main.h"

#include "CarBase.h"
#include "Sedan.h" 
 
 
Sedan::Sedan() { 
	carType = CarType::Sedan;
} 
 
Sedan::~Sedan() { 
 
} 

void Sedan::Update()
{
	Move(MAX_SPEED);

}

void Sedan::Draw()
{
	Body.Draw(&bodyMat);
	FTire.Draw(&tmpTireMat[TirePos::FR]);
	FTire.Draw(&tmpTireMat[TirePos::FL]);
	RTire.Draw(&tmpTireMat[TirePos::R1]);
}
