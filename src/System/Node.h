#ifndef __Node_h__
#define __Node_h__

//*************************************************
//
//	�m�[�h�̍��W�p�N���X
//
//*************************************************
class Position {
public:
	Position(){}
	Position(int _x, int _y) 
	{
		x = _x;
		y = _y;
	}

	//-------------------------------------------
	// �I�y���[�^�֘A

	// ��r
	bool operator==(const Position& value) const
	{
		return (this->x == value.x && this->y == value.y);
	}
	// ���Z
	const Position operator+(const Position& value) const
	{
		Position tmp;
		tmp.x = this->x + value.x;
		tmp.y = this->y + value.y;
		return tmp;
	}
	// ���Z
	const Position operator-(const Position& value) const
	{
		Position tmp;
		tmp.x = this->x - value.x;
		tmp.y = this->y - value.y;
		return tmp;
	}

	//-------------------------------------------
	// �����o�֐�
	void Set(int _x, int _y) 
	{
		x = _x;
		y = _y;
	}

public:
	int x;
	int y;
};

//*************************************************
//
//	�m�[�h�N���X
//
//*************************************************
class Node
{
public:
	// �����o�ϐ�������������֐�
	void Reset() 
	{
		this->pos.Set(0, 0);
		this->score = 0;
		this->status = NONE;
		this->parent = nullptr;
	}

	//	�m�[�h�����Z�b�g����֐�
	void SetNode(float score, Node* parentNode)
	{
		this->score = score;
		this->parent = parentNode;
	}

	enum Status {
		NONE,
		OPEN,
		CLOSE
	};

public:
	Position	pos;
	float		score;		// ���R�X�g(�X�^�[�g����̋���)�Ɛ���R�X�g(�S�[���܂ł̋���)�̍��v�l
	int			status;		// �m�[�h�̏��
	Node*		parent;		// �e�ւ̃|�C���^
};

#endif