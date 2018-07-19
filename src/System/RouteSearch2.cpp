#include "../main.h"

#include "Node2.h"
#include "RouteSearch2.h"

RouteSearch2::RouteSearch2()
{
	// �m�[�h�̏�����
	for (int cntY = 0; cntY < SIZE_Y; cntY++) {
		for (int cntX = 0; cntX < SIZE_X; cntX++) {
			m_NodeData[cntY][cntX].pos.y = cntY;					// ���W�̃Z�b�g
			m_NodeData[cntY][cntX].pos.x = cntX;					// ���W�̃Z�b�g
			m_NodeData[cntY][cntX].status = Node2::Status::NONE;	
			m_NodeData[cntY][cntX].parentNode = nullptr;

		}
	}

	StartNodeOpen(m_NodeData[startPos.y][startPos.x]);
}

void RouteSearch2::Update()
{
}

// �}���n�b�^������
int RouteSearch2::GetDistance(int fromX, int fromY, int toX, int toY)
{
	int x = fromX - toX;
	int y = fromY - toY;

	if (x < 0) x *= -1;
	if (y < 0) y *= -1;

	// ����ړ��R�X�g���v�Z
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
	// ���͂W������OPEN����
	for (int cntY = node.pos.y - 1; cntY < node.pos.x + 2; cntY++) {
		for (int cntX = node.pos.x - 1; cntX < node.pos.x + 2; cntX++) {
			// ���̈ʒu�����ȊO�ł���Έȍ~�̏������s��Ȃ�
			if (m_RouteData[cntY][cntX] != 1)continue;

			// �͈͊O�̈ʒu�ł���Έȍ~�̏������s��Ȃ�
			if (cntY < 0 || cntY >= SIZE_Y) continue;
			if (cntX < 0 || cntX >= SIZE_X) continue;
			
			// �������g�̈ʒu�ł���Έȍ~�̏������s��Ȃ�
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

	// OPEN ���X�g�̍쐬
	for (int cntY = 0; cntY < SIZE_Y; cntY++) {
		for (int cntX = 0; cntX < SIZE_X; cntX++) {
			Node2* tmpNode = &m_NodeData[cntY][cntX];

			if (tmpNode->status == Node2::Status::OPEN) {
				mapOpen.insert(KEYDATA(tmpNode->pos, *tmpNode));
			}
		}
	}

	// OPEN ���X�g����Ȃ�ΒT���I��
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
// �m�[�h�N���X
//===========================================================================
class Node
{
public:
	//-----------------------------------------------------------
	//! @name ������
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
	Node * _pParentNode;       // �e�m�[�h
	int   _posX;              // X���W
	int   _posY;              // Y���W
	int   _costFromStartNode; // �X�^�[�g�m�[�h����̍ŏ��R�X�g
	int   _costToGoalNode;    // �S�[���m�[�h�܂ł̍ŏ��R�X�g
};
typedef std::shared_ptr&lt; Node&gt; NodePtr;
typedef std::vector&lt; NodePtr&gt; NodePtrVector;
namespace {
	//---------------------------------------------------------------------------
	//  �ǔ���
	//! @param [in] posX X���W
	//! @param [in] posY Y���W
	//! @return �ǂȂ�true
	//---------------------------------------------------------------------------
	bool IsWall(int posX, int posY)
	{
		if (posX &lt; 0 || Map::WIDTH  &lt; = posX) return true;
		if (posY &lt; 0 || Map::HEIGHT &lt; = posY) return true;
		return (Map::DATA[posX + posY * Map::WIDTH] == 0);
	}
	//---------------------------------------------------------------------------
	//  �S�[���܂ł̐���R�X�g���v�Z
	//! @param [in] posX X���W
	//! @param [in] posY Y���W
	//! @return �S�[���܂ł̋���
	//---------------------------------------------------------------------------
	int CalcCostToGoalNode(int posX, int posY)
	{
		return std::abs(Map::GOAL_X - posX) + std::abs(Map::GOAL_Y - posY);
	}
	//---------------------------------------------------------------------------
	//  �S�[���܂ł̐���R�X�g���v�Z
	//! @param [in] node �m�[�h
	//! @return �S�[���܂ł̋���
	//---------------------------------------------------------------------------
	int CalcCostToGoalNode(const Node& node)
	{
		return CalcCostToGoalNode(node.GetPosX(), node.GetPosY());
	}
}
//---------------------------------------------------------------------------
//    �X�^�[�g�A�b�v
//---------------------------------------------------------------------------
int main()
{
	//------------------------------------------------------------
	// �ϐ���`
	//------------------------------------------------------------
	NodePtrVector openList;
	NodePtrVector closeList;
	//------------------------------------------------------------
	// �����_����p�����֐���`
	//------------------------------------------------------------
	// Node�ʒu��r�p�֐�
	auto compareNodeByTotalCost = [](NodePtr pNode1, NodePtr pNode2) - &gt; int
	{
		return pNode1 - &gt; GetTotalCost() &gt; pNode2 - &gt; GetTotalCost();
	};
	// ���X�g���Ɋ܂܂�Ă��邩�ǂ����̔���p�֐�
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
	// A*�̃A���S���Y��
	//------------------------------------------------------------
	// �X�^�[�g�m�[�h
	NodePtr pStartNode(new Node(Map::START_X, Map::START_Y));
	int startNodeCostToGoalNode = CalcCostToGoalNode(*pStartNode);
	pStartNode - &gt; SetCostToGoalNode(startNodeCostToGoalNode);
	// �S�[���m�[�h
	NodePtr pGoalNode(new Node(Map::GOAL_X, Map::GOAL_Y));
	// �I�[�v�����X�g������o��
	openList.push_back(pStartNode);
	while (true)
	{
		// �I�[�v�����X�g����Ȃ猟�����s
		if (openList.empty())
		{
			std::cout &lt; &lt; "�T�����s" &lt; &lt; std::endl;
			exit(1);
		}
		// �ŏ��R�X�g�̃m�[�h���I�[�v�����X�g������o��
		std::sort(openList.begin(), openList.end(), compareNodeByTotalCost);
		NodePtr pBaseNode = openList.back();
		openList.pop_back();
		// �S�[���m�[�h�ƈ�v�����猟���I��
		if (*pBaseNode == *pGoalNode)
		{
			*pGoalNode = *pBaseNode;
			break;
		}
		// ���o�����m�[�h���N���[�Y���X�g�Ɉڂ�
		closeList.push_back(pBaseNode);
		// �אڃm�[�h���`�F�b�N
		// ����͏㉺���E�̂�
		for (int dy = -1; dy &lt; = 1; ++dy)
		{
			for (int dx = -1; dx &lt; = 1; ++dx)
			{
				// ���ʒu����
				if (dx == 0 && dy == 0) continue;
				// �΂߂��l�����Ȃ�
				if (dx != 0 && dy != 0) continue;
				// �אڃm�[�h�ʒu
				int pAdjacentNodePosX = pBaseNode - &gt; GetPosX() + dx;
				int pAdjacentNodePosY = pBaseNode - &gt; GetPosY() + dy;
				// �ǔ���
				if (IsWall(pAdjacentNodePosX, pAdjacentNodePosY)) continue;
				// �אڃm�[�h�̊e�R�X�g
				int adjacentNodeCostFromStart = pBaseNode - &gt; GetCostFromStartNode() + 1;  // �e����q�ւ̈ړ��R�X�g��1
				int adjacentNodeCostToGoalNode = CalcCostToGoalNode(pAdjacentNodePosX, pAdjacentNodePosY);
				// �אڃm�[�h
				NodePtr pAdjacentNode(new Node(pAdjacentNodePosX, pAdjacentNodePosY));
				pAdjacentNode - &gt; SetParentNode(pBaseNode.get())
					.SetCostFromStartNode(adjacentNodeCostFromStart)
					.SetCostToGoalNode(adjacentNodeCostToGoalNode);
				NodePtr pSearchedNode = nullptr;
				// �I�[�v�����X�g�Ɋ܂܂�Ă��邩
				pSearchedNode = isInNodeList(openList, pAdjacentNode);
				if (pSearchedNode)
				{
					// �I�[�v�����X�g�ɂ������m�[�h���אڃm�[�h�̃R�X�g����������΁A�I�[�v�����X�g�̃m�[�h���㏑��
					if (pAdjacentNode - &gt; GetTotalCost() &lt; pSearchedNode - &gt; GetTotalCost())
					{
						*pSearchedNode = *pAdjacentNode;
					}
					continue;
				}
				// �N���[�Y���X�g�Ɋ܂܂�Ă��邩
				pSearchedNode = isInNodeList(closeList, pAdjacentNode);
				if (pSearchedNode)
				{
					// �N���[�Y���X�g�ɂ������m�[�h���אڃm�[�h�̃R�X�g����������΁A�N���[�Y���X�g����폜���ăI�[�v�����X�g�ɒǉ�
					if (pAdjacentNode - &gt; GetTotalCost() &lt; pSearchedNode - &gt; GetTotalCost())
					{
						std::remove(closeList.begin(), closeList.end(), pSearchedNode);
						openList.push_back(pAdjacentNode);
					}
					continue;
				}
				// �ǂ���ɂ��܂܂�Ă��Ȃ���΃I�[�v�����X�g�ɒǉ�
				openList.push_back(pAdjacentNode);
			}
		}
	}
	//------------------------------------------------------------
	// ����
	//------------------------------------------------------------
	// �S�[���m�[�h����e�m�[�h��H�邱�ƂŁA�X�^�[�g�m�[�h�܂ł̌o�H���Z�o�����
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