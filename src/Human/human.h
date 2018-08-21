#ifndef __human_h__ 
#define __human_h__

class human {
public:
	void LoadXFile(void);							// メッシュデータ読み込み													
	void SetMapData(int* mapData);		// マップ情報をセットする関数
	void LoadHuman(void);						// humanの読み込み
	void DrawHuman(CVector3 _pos);		// humanの描画

private:
	static const int SIZE_X = 80;
	static const int SIZE_Y = 80;
	static const int MAX_HUMAN = 80;

	int m_RouteData[SIZE_Y][SIZE_X];	// マップの情報
	int d[MAX_HUMAN];							// 乱数用

	CMesh m_meshBoy;							// 男メッシュ
	CMesh m_meshGirl;							// 女メッシュ

	CMatrix m[MAX_HUMAN];				// human行列

};
#endif