#include "../main.h"
#include "../GameWorld.h"

#include "../Map/map.h"
#include "../Camera/Camera.h"
#include "STitle.h"


STitle::STitle() 
{
	m_id = TITLE;

	cdg.SetDirectionalLight(0,
		&CVector3(1, -1, 0),				// ライトの方向
		&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// 基本色(ディフーズ RGBA)
		&D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f),	// 環境色(アンビエント RGBA)
		&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)	// 反射色(スペキュラ RGBA)
	);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m_test[i][j] = 999;
		}
	}
	ArrayZeroClear(&**m_test, sizeof(m_test));

	m_Cam = new Camera();
	m_Cam->SetProj();
	m_map = new map();
	m_map->LoadMap();

	m_meshSample.LoadXFile("../data/Mesh/TestData/Model.x");
	m_texSample[0].LoadTexture("../data/Sprite/TestData/back.png");
	m_texSample[1].LoadTexture("../data/Sprite/TestData/continue.png");

	
}

STitle::~STitle()
{
	Safe_Delete(m_Cam);
}

//===================================
// タイトル画面の更新
//===================================
int STitle::Update()
{
	// Esc キーでゲーム終了
	if (GetAsyncKeyState(VK_ESCAPE)) {
		APP.m_CloseFlag = true;
	}

	return TITLE;
}

//===================================
// タイトル画面の描画
//===================================
void STitle::Draw()
{
	// 描画開始
	cdg.GetDev()->BeginScene();

	// バックバッファと Z バッファをクリア
	cdg.Clear(true, true, false, XRGB(0, 0, 100), 1.0f, 0);


	//-------------------------------------------
	// カメラ処理
	//-------------------------------------------
	//m_Cam->SetView();

	//-------------------------------------------
	// 描画処理
	//-------------------------------------------
	Render();


	cdg.BeginSprite();
	{
		//-------------------------------------------
		// スプライト	2D画像
		//-------------------------------------------
		DrawSprite();

		//--------------------------------------------
		// 文字表示
		//--------------------------------------------
		DisplayText();

	}
	cdg.EndSprite();

	// 描画終了
	cdg.GetDev()->EndScene();

	// バックバッファをプライマリバッファにコピー
	cdg.GetDev()->Present(nullptr, nullptr, nullptr, nullptr);

}


//================================================================
// 描画処理
//================================================================
void STitle::Render()
{

	//-------------------------------------------
	// 表示テスト用
	//-------------------------------------------
	{
		m_map->DrawMap();

		CMatrix m;
		m.CreateMove(0, -2, 10);
		m.RotateY_Local(45);

		m_meshSample.Draw(&m);
	}
}

//================================================================
// スプライト描画
//================================================================
void STitle::DrawSprite()
{

	//-------------------------------------------
	// 表示テスト用
	//-------------------------------------------
	{
		CMatrix m;
	
		m.CreateMove(0, 0, 1);
		cdg.DrawSprite(&m_texSample[0], ARGB_FULL, &m);

		m.CreateMove(100, 200, 1);
		cdg.DrawSprite(&m_texSample[1], ARGB_FULL, &m);
	}
}

//================================================================
// テキスト表示
//================================================================
void STitle::DisplayText()
{

	//-------------------------------------------
	// 表示テスト用
	//-------------------------------------------
	{
		CMatrix m;
		m.CreateMove(100, 100, 0);
		cdg.DrawFont("タイトル", ARGB_FULL, &m);
	}
}
