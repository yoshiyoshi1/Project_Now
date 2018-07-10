#include "../main.h"
#include "CarBase.h"

CarBase::CarBase() {

	mesh.LoadXFile("../data\Mesh\Car\Taxi/Taxi.x");
	mat.CreateIdentity();
}

CarBase::~CarBase() {

}

void CarBase::Update() {
	
}

void CarBase::Draw() {


	mesh.Draw(&mat);
}

