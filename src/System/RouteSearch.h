#ifndef __RouteSearch_h__
#define __RouteSearch_h__

class RouteSearch
{
public:
	RouteSearch();
	~RouteSearch(){}

	void Update();

	Node* SetNode(Node* node, int x, int y, int cost, Node* parentNode);
	int GetDistance(int fromX, int fromY, int toX, int toY);

	int BackTrace(int x, int y);
	int Search(int count);
	void TraceRoute(int x, int y);
	
	
	int out(int(*d)[10]);
	int _tmain(int argc, char* argv[]);

private:

	std::map <Node::Position, Node> mapOpen;
	std::map <Node::Position, Node> mapClose;

	//CVector2 startPos;
	//CVector2 goalPos;

	Node::Position startPos;
	Node::Position goalPos;

	//-----------------------------
	// テストデータ
	static const int SIZE_X = 5;
	static const int SIZE_Y = 5;
	
	int m_RouteData[SIZE_Y][SIZE_X] = {
		{ 0,1,0,1,0 },
		{ 0,1,0,1,1 },
		{ 0,1,0,0,0 },
		{ 0,1,1,0,1 },
		{ 0,0,0,0,1 },
	};
	//-----------------------------
};


//#define KEY(X,Y) ((X) * 100 + (Y))
#define POS(X,Y) Node::Position{X, Y}
//#define KEYDATA(X, Y, N) std::pair<int, Node>(KEY(X,Y), N)
#define KEYDATA(X, Y, N) std::pair<Node::Position, Node>(POS(X,Y), N)

#endif