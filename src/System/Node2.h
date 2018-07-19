#ifndef __Node2_h__
#define __Node2_h__

class Node2
{
public:

	int GetScore() 
	{
		return cost + heuristic;
	}

	// �X�e�[�^�X
	static enum Status {
		NONE,
		OPEN,
		CLOSED
	};

	struct Position {
		int x;
		int y;
		void Set(int _x, int _y) {
			x = _x;
			y = _y;
		}
	};

	Position pos;

	int status;		// �X�e�[�^�X(�m�[�h�̏��)
	int cost;		// ���R�X�g(�X�^�[�g����̋���)
	int heuristic;	// ����R�X�g(��Q���𖳎������S�[���܂ł̋���)
	Node2* parentNode;	// �e�̃|�C���^
};

#endif