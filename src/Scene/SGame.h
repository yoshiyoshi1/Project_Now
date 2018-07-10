//**********************************************
//
//		ゲーム画面を管理するクラス
//
//**********************************************


#ifndef __SGame_h__
#define __SGame_h__

#include "SceneBase.h"

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
	
};

#endif