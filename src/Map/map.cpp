#include "../main.h"
#include "map.h"


void map::LoadMap(void) {
	
	LoadXFile();

	// 地形
	if ((t_fp = fopen("../data/Csv/TerrainMap.csv", "r")) == NULL) {
		MessageBox(APP.m_hWnd, "マップ読み込みミス", "", MB_OK);
	}
	
	// 建物
	if ((b_fp = fopen("../data/Csv/BuildingMap.csv", "r")) == NULL) {
		MessageBox(APP.m_hWnd, "マップ読み込みミス", "", MB_OK);
	}

	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			fscanf(t_fp, "%d,", &t_MapData[i][j]);
			fscanf(b_fp, "%d,", &b_MapData[i][j]);
			//行列代入
			m[i][j].CreateMove(j * 2.0f, -5.0f, i * 2.0f);
		}
	}

	fclose(t_fp);
	fclose(b_fp);

}

void map::LoadXFile(void) {

	m_meshLand.LoadXFile("../data/Mesh/Map/Land.x");
	m_meshRoad.LoadXFile("../data/Mesh/Map/Road.x");
	m_meshHouse[0].LoadXFile("../data/Mesh/Map/House1.x");
	m_meshHouse[1].LoadXFile("../data/Mesh/Map/House2.x");
	m_meshHouse[2].LoadXFile("../data/Mesh/Map/House3.x");
	m_meshHouse[3].LoadXFile("../data/Mesh/Map/building1.x");
	m_meshHouse[4].LoadXFile("../data/Mesh/Map/building2.x");

}


void map::DrawMap(CVector3 _pos) {
	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			if (!(_pos.x >(m[i][j].GetPos().x - 25) && (_pos.x < (m[i][j].GetPos().x + 25))))continue;
			if (!(_pos.z > (m[i][j].GetPos().z - 30) && (_pos.z < (m[i][j].GetPos().z + 5))))continue;
			if (t_MapData[i][j] == 1) {
				// Land表示
				m_meshLand.Draw(&m[i][j]);
				if (b_MapData[i][j] == 1) {
					m_meshHouse[0].Draw(&m[i][j]);
				} else if (b_MapData[i][j] == 2) {
					m_meshHouse[1].Draw(&m[i][j]);
				} else if (b_MapData[i][j] == 3) {
					m_meshHouse[2].Draw(&m[i][j]);
				} else if (b_MapData[i][j] == 4) {
					m_meshHouse[3].Draw(&m[i][j]);
				} else if (b_MapData[i][j] == 5) {
					m_meshHouse[4].Draw(&m[i][j]);
				}
			} else if (t_MapData[i][j] == 0) {
				// Load表示
				m_meshRoad.Draw(&m[i][j]);
			}
		}
	}
}


