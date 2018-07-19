#ifndef __Node2_h__
#define __Node2_h__

class Node2
{
public:

	int GetScore() 
	{
		return cost + heuristic;
	}

	// ステータス
	static enum Status {
		NONE,
		OPEN,
		CLOSED
	};

	struct Position {
		int x;
		int y;
		void Set(int _x, int _y) {
			x = _x;
			y = _y;
		}
	};

	Position pos;

	int status;		// ステータス(ノードの状態)
	int cost;		// 実コスト(スタートからの距離)
	int heuristic;	// 推定コスト(障害物を無視したゴールまでの距離)
	Node2* parentNode;	// 親のポインタ
};

#endif