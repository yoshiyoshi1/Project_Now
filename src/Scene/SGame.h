//**********************************************
//
//		ゲーム画面を管理するクラス
//
//**********************************************


#ifndef __SGame_h__
#define __SGame_h__

#include "SceneBase.h"

class Camera;
class map;
class human;

class Taxi;

class RouteSearch;

class SGame :public SceneBase
{
public:
	SGame();
	~SGame();

	int Update()override;
	void Draw()override;

	// 3D描画
	void Render()override;
	// スプライト描画
	void DrawSprite()override;
	// テキスト表示
	void DisplayText()override;

private:
	Camera * m_Cam;
	map* m_map;
	human* m_human;

	Taxi* m_Car;

	// 表示テスト用
	CTexture m_texSample[2];
	CMesh m_meshSample;
	CMatrix m_mTest;	// 注視対象の行列

	float r;

	RouteSearch* m_Route;
};

#endif