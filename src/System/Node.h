#ifndef __Node_h__
#define __Node_h__

class Node
{
public:
	struct Position {
		int x;
		int y;
	};

	//CVector2 pos;	// 座標
	//CVector2 pos2;	

	Position pos;
	Position pos2;

	int cost;		// 実コスト
	int hCost;		// 推定コスト
	Node* parent;	// 親へのポインタ
};

#endif