#include "../main.h"
#include "human.h"

void human::LoadHuman(void) {
	
	LoadXFile();

	moveflg = true;

	int i = 0;
	int r1, r2;
	do {	
		d[i] = rand() % 2;
		r1 = rand() % 80;
		r2 = rand() % 80;
		if (m_RouteData[r1][r2] == 1 && m_RouteData[r1 - 1][r2] == 0) {
			m[i].CreateMove((r2 *2.0f), -3.8f, ((r1 * 2.0f) - 1.1f));
			micon[i] = m[i];
			i++;
		}
	} while (i < MAX_HUMAN);
	
}

void human::Update(void) {
	
	for (int i = 0; i < MAX_HUMAN; i++) {
		micon[i]._42 =(-3.5f + move);
	}

	if (move >= 0.3f) {	 moveflg = true; }
	else if (move <= -0.3f) { moveflg = false; }
	if (moveflg == true) { move -= 0.01f; }
	else if (moveflg == false) { move += 0.01f; }

}

void human::DrawHuman(CVector3 _pos) {

	for (int i = 0; i < MAX_HUMAN; i++) {
		if (d[i] == 0) {
			m_meshBoy.Draw(&m[i]);
		} else {
			m_meshGirl.Draw(&m[i]);
		}
		m_meshIcon.Draw(&micon[i]);
	}

}

void human::LoadXFile(void) {

	m_meshBoy.LoadXFile("../data/Mesh/Human/boy.x");
	m_meshGirl.LoadXFile("../data/Mesh/Human/girl.x");
	m_meshIcon.LoadXFile("../data/Mesh/Human/icon.x");
}

void human::SetMapData(int* mapData) {
	int i = 0;
	for (int cntY = 0; cntY != SIZE_Y; cntY++) {
		for (int cntX = 0; cntX != SIZE_X; cntX++, i++) {
			m_RouteData[cntY][cntX] = mapData[i];
		}
	}
}