#include "main.h"
#include "GameWorld.h"

#include "Scene/SceneBase.h"
#include "Scene/STitle.h"
#include "Scene/SGame.h"


GameWorld *GameWorld::m_lpInstance = NULL;

GameWorld::GameWorld() {
	m_lpInstance = this;

	// 初期画面はタイトル画面
	m_lpNowScene = new STitle();
}

GameWorld::~GameWorld() {
	
	if (m_lpNowScene != NULL) {
		delete m_lpNowScene;
	}
}

//==========================================
// ゲーム全体の更新
//==========================================
void GameWorld::Update()
{
	// 各シーンの更新
	if (m_lpNowScene == NULL) { return; }
	int next = m_lpNowScene->Update();

	// シーン切り替え
	if (m_lpNowScene->GetID() != next) {
		ChangeScene(next);
	}
}

//==========================================
// ゲーム全体の描画
//==========================================
void GameWorld::Draw()
{
	// 各シーンの描画
	if (m_lpNowScene != NULL) {
		m_lpNowScene->Draw();
	}
}


//==========================================
// シーンの切り替えをする関数
//==========================================
void GameWorld::ChangeScene(int _next)
{
	if (m_lpNowScene) {
		delete m_lpNowScene;
		m_lpNowScene = NULL;
	}
	if (_next == SceneBase::TITLE) {
		m_lpNowScene = new STitle();
	}
	if (_next == SceneBase::GAME) {
		m_lpNowScene = new SGame();
	}

}


