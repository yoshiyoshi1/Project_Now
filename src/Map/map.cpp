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

	m_meshLand.LoadXFile("../data/Mesh/Map/Land.x");
	m_meshRoad.LoadXFile("../data/Mesh/Map/Road.x");
	m_meshHouse[0].LoadXFile("../data/Mesh/Map/House1.x");
	m_meshHouse[1].LoadXFile("../data/Mesh/Map/House2.x");
	m_meshHouse[2].LoadXFile("../data/Mesh/Map/House3.x");

	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			//行列代入
			m[i][j].CreateMove(j * 2.0f, -5.0f, i * 2.0f);
			int r1 = rand() % 10;
			house[i][j] = r1;
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
					if (house[i][j] == 1) {
						m_meshHouse[0].Draw(&m[i][j]);
					} else if (house[i][j] == 2) {
						m_meshHouse[1].Draw(&m[i][j]);
					} else if (house[i][j] == 3) {
						m_meshHouse[2].Draw(&m[i][j]);
					}
				}
				else if (MapData[i][j] == 1) {
					// Load表示
					m_meshRoad.Draw(&m[i][j]);
				}
		}
	}
}


