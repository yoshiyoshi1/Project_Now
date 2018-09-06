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

	// �T���A���S���Y����ύX����֐�
	void ChangeSearchMode()
	{
		if (m_SearchMode == SearchMode::ASTAR) {
			m_NextSearchMode = SearchMode::DIJKSTRA;
		}
		else if (m_SearchMode == SearchMode::DIJKSTRA) {
			m_NextSearchMode = SearchMode::ASTAR;
		}
	}
	// ���݂̒T���A���S���Y�����擾����֐�
	int GetSearchMode()
	{
		return m_NextSearchMode;
	}

private:

	void Reset(Position pos);
	bool CheckPos(Position pos);
	void ResetNodeData();
	int GetCount(int status);
	float GetDistance(Position pos);
	int BackTrace(Position pos);
	bool Search_AStar();
	bool Search_Dijkstra();
	
public:

	// �T���A���S���Y��
	enum SearchMode {
		ASTAR,		// A*(A-Star)
		DIJKSTRA	// �_�C�N�X�g���@
	};

private:

	//-----------------------------
	// ���� �v���p
	DWORD m_EndTime;			// �v���I������
	Timer* m_MeasureTimer;		// �v���p�^�C�}�[
	Timer* m_UpdateTimer;		// �X�V�̃^�C�~���O�𑪂�p

	//-----------------------------

	int m_SearchMode;			// �ǂ̒T���A���S���Y�����g�p���邩
	int m_NextSearchMode;		// ���̒T���łǂ̃A���S���Y�����g�p���邩

	int** m_RouteData;			// �}�b�v�̏��
	Node** m_NodeData;			// �m�[�h�̏��
	Node* m_LastSearchNode;		// �Ō�ɒT�������m�[�h

	Position m_StartPos;		// �T���J�n�n�_
	Position m_GoalPos;			// �T���̖ړI�n
	Position m_NextStartPos;	// ���ɃZ�b�g����J�n�n�_
	Position m_NextGoalPos;		// ���ɃZ�b�g����ړI�n
	
	CMesh m_meshPin;			// ���[�g��\���s���̃��b�V��
	std::thread m_SearchThread;	// �T���p�X���b�h

};

#endif