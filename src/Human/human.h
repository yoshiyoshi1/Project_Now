#ifndef __human_h__ 
#define __human_h__

class human {
private:
	void LoadXFile(void);							// メッシュデータ読み込み

public:
	void LoadHuman(void);						// humanの読み込み
	void DrawHuman(CVector3 _pos);		// humanの描画

	int d[40];											// 乱数用

	CMesh m_meshBoy;							// 男メッシュ
	CMesh m_meshGirl;							// 女メッシュ

	CMatrix m[40];									// human行列

};
#endif