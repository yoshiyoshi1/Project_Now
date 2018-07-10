//**********************************************
//
//		ゲーム全体を管理するクラス
//
//**********************************************

#ifndef __GameWorld_h__
#define __GameWorld_h__

class SceneBase;
class ObjectBase;

class GameWorld 
{
public:
	void Update();
	void Draw();
	void ChangeScene(int _next);
	
private:
	SceneBase *m_lpNowScene;				// 現在のシーン

//*********************************************
// シングルトン実装
public:
	static void CreateInstance() { new GameWorld(); }
	static void DeleteInstance() { delete m_lpInstance; }
	static GameWorld* GetInstance() { return m_lpInstance; }
private:
	GameWorld();
	~GameWorld();
	GameWorld(GameWorld &);
	GameWorld & operator= (GameWorld &);
	static GameWorld *m_lpInstance;

//*********************************************
};

#define GW GameWorld::GetInstance()

#endif