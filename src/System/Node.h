#ifndef __Node_h__
#define __Node_h__

class Node
{
public:
	struct Position {
		int x;
		int y;
		void Set(int _x, int _y) {
			x = _x;
			y = _y;
		}
	};
	Position pos;
	Position pos2;

	int cost;		// ���R�X�g(�X�^�[�g����̋���)
	int heuristic;	// ����R�X�g(��Q���𖳎������S�[���܂ł̋���)
	Node* parent;	// �e�ւ̃|�C���^
};

#endif