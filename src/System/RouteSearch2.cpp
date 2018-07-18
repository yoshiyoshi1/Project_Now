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

	StartNodeOpen(m_NodeData[startPos[Y]][startPos[X]]);
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
	node.heuristic = GetDistance(node.pos.x, node.pos.y, goalPos[X], goalPos[Y]);
	node.parentNode = nullptr;

	nowCost++;
}

void RouteSearch2::NodeOpen(Node2& node, Node2* parentNode) 
{
	node.status = Node2::Status::OPEN;
	node.cost = nowCost;
	node.heuristic = GetDistance(node.pos.x, node.pos.y, goalPos[X], goalPos[Y]);
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

}