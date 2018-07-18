#include "../main.h"

#include "Node.h"
#include "RouteSearch.h"

RouteSearch::RouteSearch()
{
	startPos.Set(1, 1);
	goalPos.Set(7, 8);
}

void RouteSearch::Update()
{
}

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

// �m�[�h�����Z�b�g����֐�
Node* RouteSearch::SetNode(Node *node, int x, int y, int px, int py, int cost)
{
	//node->pos.Set(x, y);
	//node->pos2.Set(px, py);
	
	node->pos.x = x;
	node->pos.x = y;
	node->pos2.x = px;
	node->pos2.x = py;

	node->cost = cost;

	return node;
}

// �}���n�b�^���������΂߈ړ�������l�����ċ��߂�
int RouteSearch::GetDistance(int from_x, int from_y, int to_x, int to_y)
{
	int cx = from_x - to_x;
	int cy = from_y - to_y;

	if (cx < 0) cx *= -1;
	if (cy < 0) cy *= -1;

	// ����ړ��R�X�g���v�Z
	if (cx < cy) {
		return (cx + (cy - cx));
	}
	else {
		return (cy + (cx - cy));
	}
}

// �w�肵���n�_����X�^�[�g�n�_�܂ł̋��������߂�
int RouteSearch::BackTrace(int x, int y)
{
	if (x == startPos.x && y == startPos.y) {
		return 1;
	}

	std::map<int, Node>::iterator tmp = mapClose.find(KEY(x, y));

	if (tmp == mapClose.end()) return 0;

	return BackTrace(tmp->second.pos2.x, tmp->second.pos2.y) + 1;
}

// A*�Ōo�H�T������
int RouteSearch::Search(int count) {

	// open���X�g����Ȃ�I��
	if (mapOpen.empty()) return -9;

	Node nodes[8];

	int way[8][2] = {
		{ -1, -1 },
	{ 0, -1 },
	{ 1, -1 },
	{ 1,  0 },
	{ 1,  1 },
	{ 0,  1 },
	{ -1,  1 },
	{ -1,  0 },
	};

	std::map<int, Node>::iterator it;
	std::map<int, Node>::iterator it_min;

	Node node;

	int cost_min = 9999;
	int BackCost = 0;

	//Open���X�g����ŏ��̃R�X�g�����m�[�h�����o��
	it = mapOpen.begin();
	while (it != mapOpen.end()) {
		if (cost_min > GetDistance(it->second.pos.x, it->second.pos.y, goalPos.x, goalPos.y)) {
			cost_min = GetDistance(it->second.pos.x, it->second.pos.y, goalPos.x, goalPos.y);
			it_min = it;
		}
		it++;
	}

	SetNode(
		&node,
		it_min->second.pos.x, it_min->second.pos.y,
		it_min->second.pos2.x, it_min->second.pos2.y,
		it_min->second.cost
	);

	// Open���X�g����Close���X�g�ֈړ�
	mapClose.insert(KEYDATA(node.pos.x, node.pos.y, node));
	mapOpen.erase(KEY(node.pos.x, node.pos.y));

	// �ŏ��R�X�g�̃m�[�h����X�^�[�g�܂ł̈ړ��R�X�g
	BackCost = BackTrace(node.pos.x, node.pos.y);

	for (int i = 0; i < 8; i++) {
		// �אڂ���}�X�̍��W���v�Z
		int cx = node.pos.x + way[i][0];
		int cy = node.pos.y + way[i][1];

		if (cx < 0) continue;
		if (cy < 0) continue;

		if (cx >= SIZE_X) continue;
		if (cy >= SIZE_Y) continue;

		// �ʂ�Ȃ������悯��
		if (m_RouteData[cy][cx] == -1) continue;

		SetNode(
			&nodes[i],
			cx, cy,
			node.pos.x, node.pos.y,
			BackCost + GetDistance(cx, cy, goalPos.x, goalPos.y) + 1	// ����ړ��R�X�g
		);

		//Open���X�g�ɂ��̍��W�Ɠ����m�[�h�����邩�m�F
		if (mapOpen.find(KEY(cx, cy)) != mapOpen.end()) {
			if (nodes[i].cost < mapOpen[KEY(cx, cy)].cost) {
				mapOpen[KEY(cx, cy)].pos2.x = node.pos.x;
				mapOpen[KEY(cx, cy)].pos2.y = node.pos.y;

				mapOpen[KEY(cx, cy)].cost = nodes[i].cost;
			}
			continue;
		}

		//Close���X�g�ɂ��̍��W�Ɠ����m�[�h�����邩�m�F
		if (mapClose.find(KEY(cx, cy)) != mapClose.end()) {
			if (nodes[i].cost < mapClose[KEY(cx, cy)].cost) {
				Node tmp;

				SetNode(
					&tmp,
					cx, cy,
					node.pos.x, node.pos.y,
					nodes[i].cost
				);

				mapOpen.insert(KEYDATA(cx, cy, tmp));
				mapClose.erase(KEY(cx, cy));
			}
			continue;
		}

		// ������Ȃ���ΐV�K�Ƃ���Open���X�g�֒ǉ�
		mapOpen.insert(KEYDATA(nodes[i].pos.x, nodes[i].pos.y, nodes[i]));
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

	std::map<int, Node>::iterator node_it = mapClose.find(KEY(x, y));

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