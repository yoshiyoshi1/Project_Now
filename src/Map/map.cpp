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

	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
			fscanf(t_fp, "%d,", &t_MapData[i][j]);
			fscanf(b_fp, "%d,", &b_MapData[i][j]);
			//行列代入
			m[i][j].CreateMove(j * 2.0f, -5.0f, i * 2.0f);
		}
	}

	//海
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			//行列代入
			mSee[i][j].CreateMove(((j * 2.0f) - 10 * 2.0f), -5.0f, ((i * 2.0f) - 10 * 2.0f));
		}
	}

	fclose(t_fp);
	fclose(b_fp);

}

void map::DrawMap(CVector3 _pos) {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (!(_pos.x >(mSee[i][j].GetPos().x - 25) && (_pos.x < (mSee[i][j].GetPos().x + 25))))continue;
			if (!(_pos.z >(mSee[i][j].GetPos().z - 30) && (_pos.z < (mSee[i][j].GetPos().z + 5))))continue;
			m_meshSee.Draw(&mSee[i][j]);
		}	
	}

	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
			if (!(_pos.x >(m[i][j].GetPos().x - 25) && (_pos.x < (m[i][j].GetPos().x + 25))))continue;
			if (!(_pos.z > (m[i][j].GetPos().z - 30) && (_pos.z < (m[i][j].GetPos().z + 5))))continue;
				// Load表示
			if (t_MapData[i][j] == 0) {
				m_meshRoad.Draw(&m[i][j]);
			} else if (t_MapData[i][j] == 1) {
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
				} else if (b_MapData[i][j] == 11) {
					m_meshHouse[5].Draw(&m[i][j]);
				}  else if (b_MapData[i][j] == 12) {
					m_meshHouse[6].Draw(&m[i][j]);
				}  else if (b_MapData[i][j] == 13) {
					m_meshHouse[7].Draw(&m[i][j]);
				}  else if (b_MapData[i][j] == 14) {
					m_meshHouse[8].Draw(&m[i][j]);
				} 
			} else if(t_MapData[i][j] == 2){
				m_meshSand.Draw(&m[i][j]);
			}
		}
	}
}

void map::LoadXFile(void) {

	m_meshLand.LoadXFile("../data/Mesh/Map/Land.x");
	m_meshRoad.LoadXFile("../data/Mesh/Map/Road.x");
	m_meshSee.LoadXFile("../data/Mesh/Map/See.x");
	m_meshSand.LoadXFile("../data/Mesh/Map/Sand.x");
	m_meshHouse[0].LoadXFile("../data/Mesh/Map/house1.x");
	m_meshHouse[1].LoadXFile("../data/Mesh/Map/house2.x");
	m_meshHouse[2].LoadXFile("../data/Mesh/Map/house3.x");
	m_meshHouse[3].LoadXFile("../data/Mesh/Map/building1.x");
	m_meshHouse[4].LoadXFile("../data/Mesh/Map/building2.x");

	m_meshHouse[5].LoadXFile("../data/Mesh/Map/targethouse1.x");
	m_meshHouse[6].LoadXFile("../data/Mesh/Map/targethouse2.x");
	m_meshHouse[7].LoadXFile("../data/Mesh/Map/targethouse3.x");
	m_meshHouse[8].LoadXFile("../data/Mesh/Map/targebuilding1.x");
}
