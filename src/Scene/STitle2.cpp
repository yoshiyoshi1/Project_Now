#include "../main.h"
#include "../GameWorld.h"

#include "../Map/map.h"
#include "../Camera/Camera.h"
#include "STitle.h"


STitle::STitle() 
{
	m_id = TITLE;

	//----------------------------------------
	// ライトの設定
	//----------------------------------------
	cdg.SetDirectionalLight(0,
		&CVector3(1, -1, 0),				// ライトの方向
		&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// 基本色(ディフーズ RGBA)
		&D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f),	// 環境色(アンビエント RGBA)
		&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)	// 反射色(スペキュラ RGBA)
	);

	//----------------------------------------
	// メンバのインスタンス化や初期化など
	//----------------------------------------
	m_Cam = new Camera();
	m_Cam->SetProj();
	m_map = new map();
	m_map->LoadMap();


	m_mTest.CreateMove(0, 0, 10);

	//----------------------------------------
	// データのロード
	//----------------------------------------
	//m_meshSample.LoadXFile("../data/Mesh/TestData/test.x");

	m_texSample[0].LoadTexture("../data/Sprite/TestData/back.png");
	m_texSample[1].LoadTexture("../data/Sprite/TestData/continue.png");

	m_meshSample.LoadXFile("../data/Mesh/Human/boy.x");

}

STitle::~STitle()
{
	Safe_Delete(m_Cam);
	Safe_Delete(m_map);
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

	// カメラの注視対象の移動（仮の処理）
	if (GetAsyncKeyState(VK_LEFT)) {
		m_mTest.Move_Local(-0.1f, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		m_mTest.Move_Local(0.1f, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState(VK_UP)) {
		m_mTest.Move_Local(0.0f, 0.0f, 0.1f);
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		m_mTest.Move_Local(0.0f, 0.0f, -0.1f);
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
	{
		CMatrix m;
		m.CreateMove(0, -2, 10);

		// セットした行列の場所を注視点とする
		m_Cam->SetView(m_mTest);
	}

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
		cdg.CullMode(D3DCULL_CCW);
		m_map->DrawMap(m_Cam->GetvPos());
		cdg.CullMode(D3DCULL_NONE);


		CMatrix m;
		m.CreateMove(0, -2, 10);

		m.RotateX_Local(r);
		m.RotateY_Local(r);
		r++;

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
	// FPS 表示
	//-------------------------------------------
	{
		CMatrix m;
		m.CreateMove(10, 10, 0);

		cdg.DrawFont(ARGB_FULL, &m, "FPS = %d", FpsProc());
	}

	//-------------------------------------------
	// 表示テスト用
	//-------------------------------------------
	{
		CMatrix m;
		m.CreateMove(100, 100, 0);

		int i = 1;
		float f = 1.5f;
		cdg.DrawFont(ARGB_FULL, &m, "タイトル : %d : %.2f", i, f);
	}

}
