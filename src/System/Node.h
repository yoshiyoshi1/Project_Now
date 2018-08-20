#ifndef __Node_h__
#define __Node_h__

//*************************************************
//
//	ノードの座標用クラス
//
//*************************************************
class Position {
public:
	Position(){}
	Position(int _x, int _y) 
	{
		x = _x;
		y = _y;
	}

	//-------------------------------------------
	// オペレータ関連

	// 比較
	bool operator==(const Position& value) const
	{
		return (this->x == value.x && this->y == value.y);
	}
	// 加算
	const Position operator+(const Position& value) const
	{
		Position tmp;
		tmp.x = this->x + value.x;
		tmp.y = this->y + value.y;
		return tmp;
	}
	// 減算
	const Position operator-(const Position& value) const
	{
		Position tmp;
		tmp.x = this->x - value.x;
		tmp.y = this->y - value.y;
		return tmp;
	}

	//-------------------------------------------
	// メンバ関数
	void Set(int _x, int _y) 
	{
		x = _x;
		y = _y;
	}

public:
	int x;
	int y;
};

//*************************************************
//
//	ノードクラス
//
//*************************************************
class Node
{
public:
	// メンバ変数を初期化する関数
	void Reset() 
	{
		this->pos.Set(0, 0);
		this->score = 0;
		this->status = NONE;
		this->parent = nullptr;
	}

	//	ノード情報をセットする関数
	void SetNode(float score, Node* parentNode)
	{
		this->score = score;
		this->parent = parentNode;
	}

	enum Status {
		NONE,
		OPEN,
		CLOSE
	};

public:
	Position	pos;
	float		score;		// 実コスト(スタートからの距離)と推定コスト(ゴールまでの距離)の合計値
	int			status;		// ノードの状態
	Node*		parent;		// 親へのポインタ
};

#endif