#include "../main.h"

#include "CarBase.h"
#include "OneBox.h" 
 
 
OneBox::OneBox() { 
	carType = CarType::Onebox;


} 
 
OneBox::~OneBox() { 
 
} 

void OneBox::Update()
{
	Move(MAX_SPEED);

}

void OneBox::Draw()
{
	Body.Draw(&bodyMat);
	FTire.Draw(&tmpTireMat[TirePos::FR]);
	FTire.Draw(&tmpTireMat[TirePos::FL]);
	RTire.Draw(&tmpTireMat[TirePos::R1]);
}