#include "../main.h"

#include "Node.h"
#include "RouteSearch.h"

RouteSearch::RouteSearch()
{
	startPos.Set(0, 0);
	goalPos.Set(2, 4);
}

void RouteSearch::Update()
{

}

/*
// �}�b�v�̏����Y��ɕ\������
int RouteSearch::out(int(*d)[SIZE_X])
{
	for (int h = 0; h < SIZE_Y; h++) {
		for (int w = 0; w < SIZE_X; w++) {
			char ch = ' ';
			if (w == goalPos.x && h == goalPos.y) ch = '*';
			if (w == startPos.x && h == startPos.y) ch = '@';

			printf("%c", ch);

			if (d[h][w] > 0)  ch = 'o';
			if (d[h][w] < 0)  ch = '#';
			if (d[h][w] == 0) ch = '.';

			printf("%c", ch);
		}
		printf("\n");
	}
	return 0;
}
*/

// �m�[�h�����Z�b�g����֐�
Node* RouteSearch::SetNode(Node* node, int x, int y, int cost, Node* parentNode)
{
	node->pos.Set(x, y);
	//node->pos2.Set(px, py);
	
	node->cost = cost;
	node->parent = parentNode;

	return node;
}

// �}���n�b�^�����������߂�
int RouteSearch::GetDistance(int fromX, int fromY, int toX, int toY)
{
	int x = fromX - toX;
	int y = fromY - toY;

	// �␳
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

// �w�肵���n�_����X�^�[�g�n�_�܂ł̋��������߂�
int RouteSearch::BackTrace(int x, int y)
{
	if (x == startPos.x && y == startPos.y) {
		return 1;
	}

	std::map <Node::Position, Node > ::iterator tmp = mapClose.find(Node::Position{x,y});

	if (tmp == mapClose.end()) return 0;

	return BackTrace(tmp->second.pos2.x, tmp->second.pos2.y) + 1;
}

// A*�Ōo�H�T������
int RouteSearch::Search(int count) 
{

	// Open���X�g����Ȃ�I��
	if (mapOpen.empty()) return -9;

	int costMin = 9999;
	int backCost = 0;
	
	Node node;
	{
		std::map<Node::Position, Node>::iterator itMin;
		{
			//Open���X�g����ŏ��̃R�X�g�����m�[�h�����o��
			std::map<Node::Position, Node>::iterator it = mapOpen.begin();
			while (it != mapOpen.end()) {
				if (costMin > GetDistance(it->second.pos.x, it->second.pos.y, goalPos.x, goalPos.y)) {
					costMin = GetDistance(it->second.pos.x, it->second.pos.y, goalPos.x, goalPos.y);
					itMin = it;
				}
				it++;
			}
		}

		SetNode(
			&node,
			itMin->second.pos.x, itMin->second.pos.y,
			itMin->second.cost,
			nullptr
		);
	}

	// Open���X�g����Close���X�g�ֈړ�
	mapClose.insert(KEYDATA(node.pos.x, node.pos.y, node));
	mapOpen.erase(POS(node.pos.x, node.pos.y));

	// �ŏ��R�X�g�̃m�[�h����X�^�[�g�܂ł̈ړ��R�X�g
	backCost = BackTrace(node.pos.x, node.pos.y);

	Node nodes[4];

	int way[4][2] = {
		{  0, -1 },
		{  1,  0 },
		{  0,  1 },
		{ -1,  0 },
	};

	for (int i = 0; i < 4; i++) {
		// �אڂ���}�X�̍��W���v�Z (�S����)
		int cx = node.pos.x + way[i][0];
		int cy = node.pos.y + way[i][1];

		// �͈͊O�̏ꍇ�͏������s��Ȃ�
		if (cx < 0) continue;
		if (cy < 0) continue;
		if (cx >= SIZE_X) continue;
		if (cy >= SIZE_Y) continue;

		// ���ȊO���悯��
		if (m_RouteData[cy][cx] == 0) continue;

		SetNode(
			&nodes[i],													// ��������m�[�h
			cx, cy,														// ���W
			backCost + GetDistance(cx, cy, goalPos.x, goalPos.y) + 1,	// ����ړ��R�X�g
			&node														// �e�̃m�[�h
		);

		{
			//Open���X�g�ɋ��߂����W�Ɠ����m�[�h�����邩�m�F
			Node::Position tmpPos = { cx,cy };
			if (mapOpen.find(tmpPos) != mapOpen.end()) {	// ����ꍇ

				// ���X�g�ł̃R�X�g��苁�߂��R�X�g�����Ȃ��ꍇ
				if (nodes[i].cost < mapOpen[tmpPos].cost) {
					mapOpen[tmpPos].parent = &node;
					mapOpen[tmpPos].cost = nodes[i].cost;
				}
				continue;
			}

			//Close���X�g�ɂ��̍��W�Ɠ����m�[�h�����邩�m�F
			if (mapClose.find(tmpPos) != mapClose.end()) {
				if (nodes[i].cost < mapClose[tmpPos].cost) {
					Node tmp;

					SetNode(
						&tmp,
						cx, cy,
						nodes[i].cost,
						&node
					);

					mapOpen.insert(KEYDATA(cx, cy, tmp));
					mapClose.erase(tmpPos);
				}
				continue;
			}

			// ������Ȃ���ΐV�K�Ƃ���Open���X�g�֒ǉ�
			mapOpen.insert(KEYDATA(nodes[i].pos.x, nodes[i].pos.y, nodes[i]));
		}

	}

	//����������T���I��
	if (node.pos.x == goalPos.x && node.pos.y == goalPos.y) return -1;

	return Search(count + 1);
}

// �ŒZ���[�g���}�b�v�f�[�^�ɏ����o��
void RouteSearch::TraceRoute(int x, int y)
{
	if (x == startPos.x && y == startPos.y) {
		printf("�J�n�m�[�h>");
		return;
	}

	std::map<Node::Position, Node>::iterator node_it = mapClose.find(POS(x, y));

	if (node_it != mapClose.end()) {
		m_RouteData[y][x] = 1;

		TraceRoute(node_it->second.pos2.x, node_it->second.pos2.y);

		if (x == goalPos.x && y == goalPos.y) {
			printf("�S�[��\n");
			return;
		}
		else {
			printf("(%d,%d)>", x, y);
		}
	}

	return;
}

/*
int RouteSearch::_tmain(int argc, char* argv[])
{
	Node start;

	SetNode(
		&start,
		startPos.x, startPos.y,
		-1, -1,
		0
	);

	mapOpen.insert(KEYDATA(startPos.x, startPos.y, start));

	if (Search(0) == -1) {
		printf("���������I\n");
	}
	TraceRoute(goalPos.x, goalPos.y);

	out(m_RouteData);

	return 0;
}
*/