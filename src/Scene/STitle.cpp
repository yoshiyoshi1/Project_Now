#include "../main.h"
#include "../GameWorld.h"

#include "../Map/map.h"
#include "../Human/human.h"
#include "../Camera/Camera.h"
#include "STitle.h"

#include "../Car/CarBase.h"
#include "../Car/Taxi.h"

#include "../System/RouteSearch.h"

STitle::STitle()
{
	m_id = TITLE;

	// フォグの設定
	//cdg.SetFog(1, XRGB(150,150,150), 15.0f, 17.0f);

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
	m_human = new human();
	m_human->SetMapData(m_map->t_MapData[0]);
	m_human->LoadHuman();
	m_Car = new Taxi();

	m_Route = new RouteSearch();
	m_Route->SetMapData(m_map->t_MapData[0]);

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
	Safe_Delete(m_human);
	Safe_Delete(m_Car);
	Safe_Delete(m_Route);
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

	/*
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
	*/

	// 経路探索 動作テスト用
	{
		static int x = 1;
		static int y = 1;

		// 目的地をランダムに決める
		if (KeyCheck('G'))
			m_Route->ChangeGoal(RANDOM(1, 79), RANDOM(1, 79));

		// ｘ座標操作
		if (KeyCheck('K'))
			x++;
		if (KeyCheck('H'))
			x--;

		// ｘ座標操作
		if (KeyCheck('U'))
			y++;
		if (KeyCheck('J'))
			y--;

		// 探索開始地点をセットする
		if (x > 0 && x < 80 && y>0 && y < 80)
			m_Route->ChangeStart(x, y);

	}

	m_Car->Update();

	m_Route->Update();

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
		m_Cam->SetView(m_Car->GetMat());
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
		m_human->DrawHuman(m_Cam->GetvPos());
		cdg.CullMode(D3DCULL_NONE);


		CMatrix m;
		m.CreateMove(0, -2, 10);

		m.RotateX_Local(r);
		m.RotateY_Local(r);
		r++;

		m_meshSample.Draw(&m);

		m_Car->Draw();
	}

	m_Route->Draw();

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
	// 経路探索 関係
	//-------------------------------------------
	{
		CMatrix m;

		// 開始地点の座標
		m.CreateMove(10, 40, 0);
		cdg.DrawFont(ARGB(255, 255, 0, 255), &m, "StartPos\t = %2d, %2d", m_Route->GetStartPosX(), m_Route->GetStartPosY());

		// 目的地の座標
		m.CreateMove(10, 70, 0);
		cdg.DrawFont(ARGB(255, 255, 0, 255), &m, "GoalPos \t = %2d, %2d", m_Route->GetGoalPosX(), m_Route->GetGoalPosY());

		// 経路探索にかかった時間（ミリ秒）
		m.CreateMove(10, 100, 0);
		cdg.DrawFont(ARGB(255, 255, 0, 255), &m, "ElapsedTime \t = %4d ms", m_Route->GetEndTime());

	}

}
