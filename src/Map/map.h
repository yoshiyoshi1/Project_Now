#ifndef __map_h__ 
#define __map_h__

class map {
private:
	const int		MAPWIDTH = 80;
	const int		MAPHEIGHT = 80;

	void LoadXFile(void);
public:

	void LoadMap(void);
	void DrawMap(CVector3 _pos);

	// ’nŒ`
	FILE* t_fp;
	int t_MapData[80][80];

	// Œš•¨
	FILE* b_fp;
	int b_MapData[80][80];
	
	CMesh m_meshLand;
	CMesh m_meshRoad;
	CMesh m_meshHouse[5];

	CMatrix m[80][80];

};
#endif
