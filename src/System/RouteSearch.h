#ifndef __RouteSearch_h__
#define __RouteSearch_h__

#include "Node.h"

class Node;
class Timer;

//*************************************************
//
//	経路探索用クラス
//
//*************************************************

class RouteSearch
{
public:
	RouteSearch();
	~RouteSearch();

	void Update();
	void Draw();

	// マップ情報をセットする関数
	void SetMapData(int* mapData);

	// 開始地点を変更する関数
	void ChangeStart(int x, int y)
	{
		m_NextStartPos.Set(x, y);
	}
	// 開始地点座標（ｘ）を取得する関数
	int GetStartPosX()
	{
		return m_StartPos.x;
	}
	// 開始地点座標（ｙ）を取得する関数
	int GetStartPosY()
	{
		return m_StartPos.y;
	}

	// 目的地を変更する関数
	void ChangeGoal(int x, int y)
	{
		m_NextGoalPos.Set(x, y);
	}
	// 目的地座標（ｘ）を取得する関数
	int GetGoalPosX()
	{
		return m_GoalPos.x;
	}
	// 目的地座標（ｙ）を取得する関数
	int GetGoalPosY()
	{
		return m_GoalPos.y;
	}

	// 計測終了時間を取得する関数
	DWORD GetEndTime()
	{
		return m_EndTime;
	}

	// 探索アルゴリズムを変更する関数
	void ChangeSearchMode()
	{
		if (m_SearchMode == SearchMode::ASTAR) {
			m_NextSearchMode = SearchMode::DIJKSTRA;
		}
		else if (m_SearchMode == SearchMode::DIJKSTRA) {
			m_NextSearchMode = SearchMode::ASTAR;
		}
	}
	// 現在の探索アルゴリズムを取得する関数
	int GetSearchMode()
	{
		return m_NextSearchMode;
	}

private:

	void Reset(Position pos);
	bool CheckPos(Position pos);
	void ResetNodeData();
	int GetCount(int status);
	float GetDistance(Position pos);
	int BackTrace(Position pos);
	bool Search_AStar();
	bool Search_Dijkstra();
	
public:

	// 探索アルゴリズム
	enum SearchMode {
		ASTAR,		// A*(A-Star)
		DIJKSTRA	// ダイクストラ法
	};

private:

	//-----------------------------
	// 時間 計測用
	DWORD m_EndTime;			// 計測終了時間
	Timer* m_MeasureTimer;		// 計測用タイマー
	Timer* m_UpdateTimer;		// 更新のタイミングを測る用

	//-----------------------------

	int m_SearchMode;			// どの探索アルゴリズムを使用するか
	int m_NextSearchMode;		// 次の探索でどのアルゴリズムを使用するか

	int** m_RouteData;			// マップの情報
	Node** m_NodeData;			// ノードの情報
	Node* m_LastSearchNode;		// 最後に探索したノード

	Position m_StartPos;		// 探索開始地点
	Position m_GoalPos;			// 探索の目的地
	Position m_NextStartPos;	// 次にセットする開始地点
	Position m_NextGoalPos;		// 次にセットする目的地
	
	CMesh m_meshPin;			// ルートを表すピンのメッシュ
	std::thread m_SearchThread;	// 探索用スレッド

};

#endif