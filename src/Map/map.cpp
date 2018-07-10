#include "../main.h"
#include "map.h"

void map::LoadMap(void) {
	if ((fp = fopen("../data/Csv/map1.csv", "r")) == NULL) {
		MessageBox(APP.m_hWnd, "マップ読み込みミス", "", MB_OK);
	}

	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			fscanf(fp, "%d,", &MapData[i][j]);
		}
	}

	m_meshLand.LoadXFile("../data/Map/Land.x");
	m_meshLoad.LoadXFile("../data/Map/Load.x");

	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			//行列代入
			m[i][j].CreateMove(j + 0.0f, 0.0f, i + 0.0f);
		}
	}
	fclose(fp);
}

void map::DrawMap(void) {
	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
				if (MapData[i][j] == 0) {
					// Land表示
					m_meshLand.Draw(&m[i][j]);
				}
				else if (MapData[i][j] == 1) {
					// Load表示
					m_meshLoad.Draw(&m[i][j]);
				}
		}
	}
}


