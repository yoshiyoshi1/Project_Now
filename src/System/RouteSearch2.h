#ifndef __RouteSearch2_h__
#define __RouteSearch2_h__

class RouteSearch2
{
public:
	RouteSearch2();
	~RouteSearch2(){}

	void Update();

	int GetDistance(int fromX, int fromY, int toX, int toY);
	
	void StartNodeOpen(Node2& node);
	void NodeOpen(Node2& node, Node2* parentNode);
	void NodeClosed(Node2& node);
	void Search();

private:

	int startPos[2] = { 1,1 };
	int goalPos[2] = { 7.8 };
	static enum {
		X,
		Y
	};

	int nowCost;

	//-----------------------------
	// テストデータ
	static const int SIZE_X = 10;
	static const int SIZE_Y = 10;
	
	int m_RouteData[SIZE_Y][SIZE_X] = {
		{ 0,1,0,1,0,1,0,1,0,0 },
		{ 0,1,0,1,1,1,0,1,0,0 },
		{ 0,1,0,0,0,0,0,1,1,1 },
		{ 0,1,1,1,1,1,1,1,0,0 },
		{ 0,0,0,0,1,0,0,1,0,0 },
		{ 1,1,1,1,1,0,0,1,0,0 },
		{ 0,0,0,0,1,0,0,1,0,0 },
		{ 0,1,1,1,1,1,1,1,1,1 },
		{ 0,0,1,0,0,0,0,1,0,0 },
		{ 0,0,1,0,0,0,0,1,0,0 }
	};

	// 1: 道路
	// 0: その他
	// 実データは0 が道路なので注意

	Node2 m_NodeData[SIZE_Y][SIZE_X];
	//-----------------------------

};

#define KEYDATA(X, N) std::pair<Node2::Position, Node2>(X, N)

#endif