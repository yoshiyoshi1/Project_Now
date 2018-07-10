//**********************************************
//
//		各シーンクラスのベース
//
//**********************************************

#ifndef __SceneBase_h__
#define __SceneBase_h__

class SceneBase 
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}
	virtual int Update() = 0;
	virtual void Draw() = 0;
	
	// 3D描画
	virtual void Render(){}
	// スプライト描画
	virtual void DrawSprite(){}
	// テキスト表示
	virtual void DisplayText(){}

	enum { TITLE, GAME, RESULT };
	int GetID() { return m_id; }
protected:
	int m_id;
};

#endif