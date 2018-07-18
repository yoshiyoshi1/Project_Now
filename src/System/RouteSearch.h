#ifndef __RouteSearch_h__
#define __RouteSearch_h__

class RouteSearch
{
public:
	RouteSearch();
	~RouteSearch(){}

	void Update();

	int out(int(*d)[10]);
	Node* SetNode(Node *n, int nx, int ny, int npx, int npy, int ncost);
	int GetDistance(int from_x, int from_y, int to_x, int to_y);
	int BackTrace(int x, int y);
	int Search(int count);
	void TraceRoute(int x, int y);
	int _tmain(int argc, char* argv[]);

private:

	std::map <int, Node> mapOpen;
	std::map <int, Node> mapClose;

	CVector2 startPos;
	CVector2 goalPos;

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
	//-----------------------------
};


#define KEY(X,Y) ((X) * 100 + (Y))
#define KEYDATA(X, Y, N) std::pair<int, Node>(KEY(X,Y), N)

#endif