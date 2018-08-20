//**********************************************
//
//		タイトル画面を管理するクラス
//
//**********************************************


#ifndef __STitle_h__
#define __STitle_h__

#include "SceneBase.h"

class Camera;
class map;
class human;

class Taxi;

class RouteSearch;

class STitle :public SceneBase 
{
public:
	STitle();
	~STitle();
	int Update()override;
	void Draw()override;
	
	// 3D描画
	void Render()override;
	// スプライト描画
	void DrawSprite()override;
	// テキスト表示
	void DisplayText()override;

private:
	Camera* m_Cam;
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
