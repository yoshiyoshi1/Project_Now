#ifndef __RouteSearch_h__
#define __RouteSearch_h__

#include "Node.h"

class Node;
class Timer;

//*************************************************
//
//	�o�H�T���p�N���X
//
//*************************************************

class RouteSearch
{
public:
	RouteSearch();
	~RouteSearch();

	void Update();
	void Draw();

	// �}�b�v�����Z�b�g����֐�
	void SetMapData(int* mapData);

	// �J�n�n�_��ύX����֐�
	void ChangeStart(int x, int y)
	{
		m_NextStartPos.Set(x, y);
	}
	// �J�n�n�_���W�i���j���擾����֐�
	int GetStartPosX()
	{
		return m_StartPos.x;
	}
	// �J�n�n�_���W�i���j���擾����֐�
	int GetStartPosY()
	{
		return m_StartPos.y;
	}

	// �ړI�n��ύX����֐�
	void ChangeGoal(int x, int y)
	{
		m_NextGoalPos.Set(x, y);
	}
	// �ړI�n���W�i���j���擾����֐�
	int GetGoalPosX()
	{
		return m_GoalPos.x;
	}
	// �ړI�n���W�i���j���擾����֐�
	int GetGoalPosY()
	{
		return m_GoalPos.y;
	}

	// �v���I�����Ԃ��擾����֐�
	DWORD GetEndTime()
	{
		return m_EndTime;
	}

private:

	void Reset(Position pos);
	bool CheckPos(Position pos);
	void ResetNodeData();
	int GetCount(int status);
	float GetDistance(Position pos);
	int BackTrace(Position pos);
	bool Search();
	
private:
	//-----------------------------
	// �e�X�g�f�[�^
	static const int SIZE_X = 80;
	static const int SIZE_Y = 80;

	//-----------------------------
	// ���� �v���p
	DWORD m_EndTime;			// �v���I������
	Timer* m_MeasureTimer;		// �v���p�^�C�}�[

	//-----------------------------

	int m_RouteData[SIZE_Y][SIZE_X];	// �}�b�v�̏��
	Node m_NodeData[SIZE_Y][SIZE_X];	// �m�[�h�̏��
	Node* m_LastSearchNode = nullptr;	// �Ō�ɒT�������m�[�h

	Position m_StartPos;		// �T���J�n�n�_
	Position m_GoalPos;			// �T���̖ړI�n
	Position m_NextStartPos;	// ���ɃZ�b�g����J�n�n�_
	Position m_NextGoalPos;		// ���ɃZ�b�g����ړI�n
	
	CMesh m_meshPin;			// ���[�g��\���s���̃��b�V��
	std::thread m_SearchThread;	// �T���p�X���b�h
	Timer* m_UpdateTimer;		// �X�V�̃^�C�~���O�𑪂�p

};

#endif