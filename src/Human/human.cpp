#include "../main.h"
#include "human.h"

void human::LoadHuman(void) {
	
	LoadXFile();

	for (int i = 0; i < 40; i++) {
		d[i] = rand() % 2;
		int r1,r2;
		r1 = rand() % 74;
		r2 = rand() % 74;
		m[i].CreateMove(5.0f + ( 2 * r1 ), -3.8f, 5.0f + (2 * r2));
	}

}

void human::DrawHuman(CVector3 _pos) {

	for (int i = 0; i < 40; i++) {
		if (d[i] == 0) {
			m_meshBoy.Draw(&m[i]);
		} else {
			m_meshGirl.Draw(&m[i]);
		}
	}

}

void human::LoadXFile(void) {

	m_meshBoy.LoadXFile("../data/Mesh/Human/boy.x");
	m_meshGirl.LoadXFile("../data/Mesh/Human/girl.x");
}
