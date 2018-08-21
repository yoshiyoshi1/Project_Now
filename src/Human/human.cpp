#include "../main.h"
#include "human.h"

void human::LoadHuman(void) {
	
	LoadXFile();

	int i = 0;
	int r1, r2;
	do {	
		d[i] = rand() % 2;
		r1 = rand() % 80;
		r2 = rand() % 80;
		if (m_RouteData[r1][r2] == 1 && m_RouteData[r1 - 1][r2] == 0) {
			m[i].CreateMove((r2 *2.0f), -3.8f, ((r1 * 2.0f) - 1.1f));
			i++;
		}
	} while (i < MAX_HUMAN);

}

void human::DrawHuman(CVector3 _pos) {

	for (int i = 0; i < MAX_HUMAN; i++) {
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

void human::SetMapData(int* mapData) {
	int i = 0;
	for (int cntY = 0; cntY != SIZE_Y; cntY++) {
		for (int cntX = 0; cntX != SIZE_X; cntX++, i++) {
			m_RouteData[cntY][cntX] = mapData[i];
		}
	}
}