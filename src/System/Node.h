#ifndef __Node_h__
#define __Node_h__

class Node
{
public:
	struct Position {
		int x;
		int y;
	};

	//CVector2 pos;	// ���W
	//CVector2 pos2;	

	Position pos;
	Position pos2;

	int cost;		// ���R�X�g
	int hCost;		// ����R�X�g
	Node* parent;	// �e�ւ̃|�C���^
};

#endif