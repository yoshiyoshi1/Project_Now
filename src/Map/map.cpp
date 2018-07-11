#include "../main.h"
#include "map.h"

void map::LoadMap(void) {
	if ((fp = fopen("../data/Csv/map1.csv", "r")) == NULL) {
		MessageBox(APP.m_hWnd, "�}�b�v�ǂݍ��݃~�X", "", MB_OK);
	}

	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			fscanf(fp, "%d,", &MapData[i][j]);
		}
	}

	m_meshLand.LoadXFile("../data/Mesh/Map/Land.x");
	m_meshRoad.LoadXFile("../data/Mesh/Map/Road.x");

	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			//�s����
			m[i][j].CreateMove(j * 2.0f, -10.0f, i * 2.0f);
		}
	}
	fclose(fp);
}

void map::DrawMap(void) {
	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
				if (MapData[i][j] == 0) {
					// Land�\��
					m_meshLand.Draw(&m[i][j]);
				}
				else if (MapData[i][j] == 1) {
					// Load�\��
					m_meshRoad.Draw(&m[i][j]);
				}
		}
	}
}


