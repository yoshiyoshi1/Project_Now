#ifndef __Node_h__
#define __Node_h__

class Node
{
public:
	struct Position {
		int x;
		int y;
		void Set(int _x, int _y) {
			x = _x;
			y = _y;
		}
	};
	Position pos;
	Position pos2;

	int cost;		// 実コスト(スタートからの距離)
	int heuristic;	// 推定コスト(障害物を無視したゴールまでの距離)
	Node* parent;	// 親へのポインタ
};

#endif