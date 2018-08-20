#include "../main.h"

#include "CarBase.h"
#include "Bus.h" 
 
 
Bus::Bus() 
{ 
	carType = CarType::Bus;


} 
 
Bus::~Bus() { 
 
}

void Bus::Update()
{
	Move(MAX_SPEED);

}

void Bus::Draw()
{
	Body.Draw(&bodyMat);
	FTire.Draw(&tmpTireMat[TirePos::FR]);
	FTire.Draw(&tmpTireMat[TirePos::FL]);
	RTire.Draw(&tmpTireMat[TirePos::R1]);
}
