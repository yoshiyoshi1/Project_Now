#include "../main.h"

#include "Node2.h"
#include "RouteSearch2.h"

RouteSearch2::RouteSearch2()
{
	// ノードの初期化
	for (int cntY = 0; cntY < SIZE_Y; cntY++) {
		for (int cntX = 0; cntX < SIZE_X; cntX++) {
			m_NodeData[cntY][cntX].pos.y = cntY;					// 座標のセット
			m_NodeData[cntY][cntX].pos.x = cntX;					// 座標のセット
			m_NodeData[cntY][cntX].status = Node2::Status::NONE;	
			m_NodeData[cntY][cntX].parentNode = nullptr;

		}
	}

	StartNodeOpen(m_NodeData[startPos.y][startPos.x]);
}

void RouteSearch2::Update()
{
}

// マンハッタン距離
int RouteSearch2::GetDistance(int fromX, int fromY, int toX, int toY)
{
	int x = fromX - toX;
	int y = fromY - toY;

	if (x < 0) x *= -1;
	if (y < 0) y *= -1;

	// 推定移動コストを計算
	if (x < y) {
		return (x + (y - x));
	}
	else {
		return (y + (x - y));
	}
}

void RouteSearch2::StartNodeOpen(Node2& node)
{
	node.status = Node2::Status::OPEN;
	node.cost = nowCost;
	node.heuristic = GetDistance(node.pos.x, node.pos.y, goalPos.x, goalPos.y);
	node.parentNode = nullptr;

	nowCost++;
}

void RouteSearch2::NodeOpen(Node2& node, Node2* parentNode) 
{
	node.status = Node2::Status::OPEN;
	node.cost = nowCost;
	node.heuristic = GetDistance(node.pos.x, node.pos.y, goalPos.x, goalPos.y);
	node.parentNode = parentNode;
}

void RouteSearch2::NodeClosed(Node2& node)
{
	// 周囲８方向をOPENする
	for (int cntY = node.pos.y - 1; cntY < node.pos.x + 2; cntY++) {
		for (int cntX = node.pos.x - 1; cntX < node.pos.x + 2; cntX++) {
			// その位置が道以外であれば以降の処理を行わない
			if (m_RouteData[cntY][cntX] != 1)continue;

			// 範囲外の位置であれば以降の処理を行わない
			if (cntY < 0 || cntY >= SIZE_Y) continue;
			if (cntX < 0 || cntX >= SIZE_X) continue;
			
			// 自分自身の位置であれば以降の処理を行わない
			if (cntY == node.pos.y) continue;
			if (cntX == node.pos.x) continue;

			NodeOpen(m_NodeData[cntY][cntX], &node);
		}
	}

	node.status = Node2::Status::CLOSED;
	nowCost++;
}



void RouteSearch2::Search()
{
	std::map<Node2::Position, Node2> mapOpen;
	mapOpen.clear();

	// OPEN リストの作成
	for (int cntY = 0; cntY < SIZE_Y; cntY++) {
		for (int cntX = 0; cntX < SIZE_X; cntX++) {
			Node2* tmpNode = &m_NodeData[cntY][cntX];

			if (tmpNode->status == Node2::Status::OPEN) {
				mapOpen.insert(KEYDATA(tmpNode->pos, *tmpNode));
			}
		}
	}

	// OPEN リストが空ならば探索終了
	if (mapOpen.empty()) {
		return;
	}


}

/*
#include &lt;functional&gt;
#include &lt;iostream&gt;
#include &lt;vector&gt;
#include &lt;queue&gt;
#include &lt;memory&gt;
#include "MapData.h"
//===========================================================================
// ノードクラス
//===========================================================================
class Node
{
public:
	//-----------------------------------------------------------
	//! @name 初期化
	//-----------------------------------------------------------
	//@{
	Node(int posX, int posY)
		: _pParentNode(nullptr)
		, _posX(posX)
		, _posY(posY)
		, _costFromStartNode(0)
		, _costToGoalNode(0)
	{}
	//@}
	//-----------------------------------------------------------
	//! @name setter/getter
	//-----------------------------------------------------------
	//@{
	Node& SetParentNode(Node* pNode) { _pParentNode = pNode; return *this; }
	Node* GetParentNode(void) const { return _pParentNode; }
	Node& SetPosX(int posX) { _posX = posX; return *this; }
	int GetPosX(void) const { return _posX; }
	Node& SetPosY(int posY) { _posY = posY; return *this; }
	int GetPosY(void) const { return _posY; }
	Node& SetCostFromStartNode(int costFromStartNode) { _costFromStartNode = costFromStartNode; return *this; }
	int GetCostFromStartNode(void) const { return _costFromStartNode; }
	Node& SetCostToGoalNode(int costToGoalNode) { _costToGoalNode = costToGoalNode; return *this; }
	int GetCostToGoalNode(void) const { return _costToGoalNode; }
	int GetTotalCost(void) const { return _costFromStartNode + _costToGoalNode; }
	//@}
	//-----------------------------------------------------------
	//! @name operator
	//-----------------------------------------------------------
	//@{
	bool operator == (Node node)
	{
		return (this - &gt; _posX == node._posX && this - &gt; _posY == node._posY);
	}
	void operator = (Node node)
	{
		this - &gt; _pParentNode = node._pParentNode;
		this - &gt; _posX = node._posX;
		this - &gt; _posY = node._posY;
		this - &gt; _costFromStartNode = node._costFromStartNode;
		this - &gt; _costToGoalNode = node._costToGoalNode;
	}
	//@}
private:
	Node * _pParentNode;       // 親ノード
	int   _posX;              // X座標
	int   _posY;              // Y座標
	int   _costFromStartNode; // スタートノードからの最小コスト
	int   _costToGoalNode;    // ゴールノードまでの最小コスト
};
typedef std::shared_ptr&lt; Node&gt; NodePtr;
typedef std::vector&lt; NodePtr&gt; NodePtrVector;
namespace {
	//---------------------------------------------------------------------------
	//  壁判定
	//! @param [in] posX X座標
	//! @param [in] posY Y座標
	//! @return 壁ならtrue
	//---------------------------------------------------------------------------
	bool IsWall(int posX, int posY)
	{
		if (posX &lt; 0 || Map::WIDTH  &lt; = posX) return true;
		if (posY &lt; 0 || Map::HEIGHT &lt; = posY) return true;
		return (Map::DATA[posX + posY * Map::WIDTH] == 0);
	}
	//---------------------------------------------------------------------------
	//  ゴールまでの推定コストを計算
	//! @param [in] posX X座標
	//! @param [in] posY Y座標
	//! @return ゴールまでの距離
	//---------------------------------------------------------------------------
	int CalcCostToGoalNode(int posX, int posY)
	{
		return std::abs(Map::GOAL_X - posX) + std::abs(Map::GOAL_Y - posY);
	}
	//---------------------------------------------------------------------------
	//  ゴールまでの推定コストを計算
	//! @param [in] node ノード
	//! @return ゴールまでの距離
	//---------------------------------------------------------------------------
	int CalcCostToGoalNode(const Node& node)
	{
		return CalcCostToGoalNode(node.GetPosX(), node.GetPosY());
	}
}
//---------------------------------------------------------------------------
//    スタートアップ
//---------------------------------------------------------------------------
int main()
{
	//------------------------------------------------------------
	// 変数定義
	//------------------------------------------------------------
	NodePtrVector openList;
	NodePtrVector closeList;
	//------------------------------------------------------------
	// ラムダ式を用いた関数定義
	//------------------------------------------------------------
	// Node位置比較用関数
	auto compareNodeByTotalCost = [](NodePtr pNode1, NodePtr pNode2) - &gt; int
	{
		return pNode1 - &gt; GetTotalCost() &gt; pNode2 - &gt; GetTotalCost();
	};
	// リスト内に含まれているかどうかの判定用関数
	auto isInNodeList = [](NodePtrVector& list, const NodePtr& node) - &gt; NodePtr
	{
		for (NodePtrVector::iterator it = list.begin(); it != list.end(); ++it)
		{
			NodePtr nodeItem = (*it);
			if (*node == *nodeItem)
			{
				return nodeItem;
			}
		}
	return nullptr;
	};
	//------------------------------------------------------------
	// A*のアルゴリズム
	//------------------------------------------------------------
	// スタートノード
	NodePtr pStartNode(new Node(Map::START_X, Map::START_Y));
	int startNodeCostToGoalNode = CalcCostToGoalNode(*pStartNode);
	pStartNode - &gt; SetCostToGoalNode(startNodeCostToGoalNode);
	// ゴールノード
	NodePtr pGoalNode(new Node(Map::GOAL_X, Map::GOAL_Y));
	// オープンリストから取り出す
	openList.push_back(pStartNode);
	while (true)
	{
		// オープンリストが空なら検索失敗
		if (openList.empty())
		{
			std::cout &lt; &lt; "探索失敗" &lt; &lt; std::endl;
			exit(1);
		}
		// 最小コストのノードをオープンリストから取り出す
		std::sort(openList.begin(), openList.end(), compareNodeByTotalCost);
		NodePtr pBaseNode = openList.back();
		openList.pop_back();
		// ゴールノードと一致したら検索終了
		if (*pBaseNode == *pGoalNode)
		{
			*pGoalNode = *pBaseNode;
			break;
		}
		// 取り出したノードをクローズリストに移す
		closeList.push_back(pBaseNode);
		// 隣接ノードをチェック
		// 今回は上下左右のみ
		for (int dy = -1; dy &lt; = 1; ++dy)
		{
			for (int dx = -1; dx &lt; = 1; ++dx)
			{
				// 同位置判定
				if (dx == 0 && dy == 0) continue;
				// 斜めを考慮しない
				if (dx != 0 && dy != 0) continue;
				// 隣接ノード位置
				int pAdjacentNodePosX = pBaseNode - &gt; GetPosX() + dx;
				int pAdjacentNodePosY = pBaseNode - &gt; GetPosY() + dy;
				// 壁判定
				if (IsWall(pAdjacentNodePosX, pAdjacentNodePosY)) continue;
				// 隣接ノードの各コスト
				int adjacentNodeCostFromStart = pBaseNode - &gt; GetCostFromStartNode() + 1;  // 親から子への移動コストは1
				int adjacentNodeCostToGoalNode = CalcCostToGoalNode(pAdjacentNodePosX, pAdjacentNodePosY);
				// 隣接ノード
				NodePtr pAdjacentNode(new Node(pAdjacentNodePosX, pAdjacentNodePosY));
				pAdjacentNode - &gt; SetParentNode(pBaseNode.get())
					.SetCostFromStartNode(adjacentNodeCostFromStart)
					.SetCostToGoalNode(adjacentNodeCostToGoalNode);
				NodePtr pSearchedNode = nullptr;
				// オープンリストに含まれているか
				pSearchedNode = isInNodeList(openList, pAdjacentNode);
				if (pSearchedNode)
				{
					// オープンリストにあったノードより隣接ノードのコストが小さければ、オープンリストのノードを上書き
					if (pAdjacentNode - &gt; GetTotalCost() &lt; pSearchedNode - &gt; GetTotalCost())
					{
						*pSearchedNode = *pAdjacentNode;
					}
					continue;
				}
				// クローズリストに含まれているか
				pSearchedNode = isInNodeList(closeList, pAdjacentNode);
				if (pSearchedNode)
				{
					// クローズリストにあったノードより隣接ノードのコストが小さければ、クローズリストから削除してオープンリストに追加
					if (pAdjacentNode - &gt; GetTotalCost() &lt; pSearchedNode - &gt; GetTotalCost())
					{
						std::remove(closeList.begin(), closeList.end(), pSearchedNode);
						openList.push_back(pAdjacentNode);
					}
					continue;
				}
				// どちらにも含まれていなければオープンリストに追加
				openList.push_back(pAdjacentNode);
			}
		}
	}
	//------------------------------------------------------------
	// 結果
	//------------------------------------------------------------
	// ゴールノードから親ノードを辿ることで、スタートノードまでの経路が算出される
	Node* pNode = pGoalNode.get();
	while (true)
	{
		std::cout &lt; &lt; "X:" &lt; &lt; pNode - &gt; GetPosX() &lt; &lt; ", Y:" &lt; &lt; pNode - &gt; GetPosY() &lt; &lt; std::endl;
		if ((pNode = pNode - &gt; GetParentNode()) == nullptr)
		{
			break;
		}
	}
}
*/