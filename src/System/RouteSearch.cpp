#include "../main.h"
#include "ThreadGuard.h"
#include "Timer.h"

#include "RouteSearch.h"

RouteSearch::RouteSearch()
{
	// ���f�[�^
	m_NextGoalPos.Set(68, 71);
	m_NextStartPos.Set(1, 1);

	m_meshPin.LoadXFile("../data/Mesh/TestData/pin.x");
	
	m_UpdateTimer = new Timer();
	m_MeasureTimer = new Timer();
}

RouteSearch::~RouteSearch()
{
	ResetNodeData();
}

void RouteSearch::Update()
{

	// �O��̍X�V����0.1�b�o�߂��Ă��Ȃ��ꍇ�A�ȍ~�̏������s��Ȃ�
	if (m_UpdateTimer->ElapsedTime(0.1f) == false)
		return;

	// �ړI�n���ς���Ă��Ȃ��ꍇ�A
	if (m_GoalPos == m_NextGoalPos) {
		// �J�n�n�_���ς���Ă��Ȃ��ꍇ�A�ȍ~�̏������s��Ȃ�
		if (m_StartPos == m_NextStartPos)
			return;
		
		// ���̊J�n�n�_��CLOSE�̏ꍇ�A�ȍ~�̏������s��Ȃ�
		//if (CheckPos(m_NextStartPos))
		//	return;
	}
	
	// m_NextGoalPos �����ȊO�Ȃ�΁A�ȍ~�̏������s��Ȃ�
	if (m_RouteData[m_NextGoalPos.y][m_NextGoalPos.x] != 0)
		return;

	// �o�H�T���f�[�^�����Z�b�g����
	Reset(m_NextStartPos);
	
	// �V���ȖړI�n�Ƃ��Đݒ�
	m_GoalPos = m_NextGoalPos;

	// �v���J�n
	m_MeasureTimer->SetTime();

	// �o�H�T����ʃX���b�h�ōs��
	std::thread sThread(&RouteSearch::Search, this);	// �o�H�T���p�X���b�h�̍쐬
	m_SearchThread = std::move(sThread);				// �����o�[�֐��ɃX���b�h���󂯓n��
	//ThreadGuard threadGuard(searchThread);			// �G���[�ŗ������ۂɎ�����Join���s��
}

void RouteSearch::Draw()
{
	// �o�H�T���p�X���b�h�������Ă���ꍇ�A
	if (m_SearchThread.joinable()) {
		m_SearchThread.join();						// �T���I���܂őҋ@
		m_EndTime = m_MeasureTimer->ElapsedTime();	// �T���I���܂ł̌o�ߎ���
	}

	// �Ō�ɒT�������m�[�h���Z�b�g����
	Node* pNode;
	pNode = m_LastSearchNode;
	if (pNode == nullptr)
		return;

	// CLOSE�ȃm�[�h�̐����擾
	int closeSize = GetCount(Node::Status::CLOSE);

	for (int i = 0; ; i++) {

		// �o�H���s���̃��b�V���ŕ\��
		CMatrix m;
		int blue = (int)(i * (255.0f / closeSize));
		int red = 255 - blue;
		m.CreateMove(pNode->pos.x * 2.0f, -3.0f, pNode->pos.y * 2.0f);
		m_meshPin.Draw(&m, ARGB_D3DX(255, red, 0, blue));

		// �e�����Ȃ��ꍇ�A�������I������
		if (pNode->parent == nullptr)
			return;

		// �e�̃m�[�h�ōX�V
		pNode = pNode->parent;
		if (pNode->status != Node::Status::CLOSE)
			return;
	}
}

void RouteSearch::SetMapData(int* mapData)
{
	int i = 0;
	for (int cntY = 0; cntY != SIZE_Y; cntY++) {
		for (int cntX = 0; cntX != SIZE_X; cntX++, i++) {
			m_RouteData[cntY][cntX] = mapData[i];
		}
	}
}

//=======================================================
// �m�[�h�f�[�^�����������ăX�^�[�g�n�_���Z�b�g����֐�
//=======================================================
void RouteSearch::Reset(Position pos)
{
	ResetNodeData();

	m_StartPos = pos;

	// �X�^�[�g�n�_�̃m�[�h��OPEN�ɂ���
	Node* pStartNode = &m_NodeData[m_StartPos.y][m_StartPos.x];
	pStartNode->SetNode(0, nullptr);
	pStartNode->status = Node::Status::OPEN;
}

//=======================================================
// �w�肵�����W��CLOSE�ȃm�[�h���ǂ������ׂ�֐�
//	@return	: CLOSE���ǂ���
//=======================================================
bool RouteSearch::CheckPos(Position pos)
{
	Node* pNode;
	pNode = &m_NodeData[pos.y][pos.x];

	// CLOSE�ȊO�Ȃ��false
	if (pNode->status != Node::Status::CLOSE)
		return false;

	//------------------------------------------
	// �e�����݂��Ȃ��ꍇ
	//------------------------------------------
	if (pNode->parent == nullptr) {
		m_StartPos = pos;
		return true;
	}

	//------------------------------------------
	// �e�����݂���ꍇ
	//------------------------------------------
	std::vector<Node*> parentNodeList;	// �e�m�[�h�̃��X�g
	parentNodeList.clear();
	
	while (true) {
		// �J�n�n�_�܂Ŗ߂����ꍇ�A�������I������
		if (pNode->pos == m_StartPos)
			break;
		if (pNode->parent == nullptr)
			break;

		if (pNode->status != Node::Status::CLOSE)
			break;

		// �e�̃m�[�h�ōX�V
		pNode = pNode->parent;
		
		// �e�̃|�C���^�����X�g�ɕۑ����Ă���
		parentNodeList.push_back(pNode);
	}

	// �e�̃m�[�h�����Z�b�g����
	for (Node* pParentNode : parentNodeList) {
		pParentNode->Reset();
	}

	// �w�肵�����W���J�n�n�_�Ƃ���
	m_NodeData[pos.y][pos.x].parent = nullptr;
	m_StartPos = pos;
	
	return true;
}

//=======================================================
// �m�[�h�f�[�^�����Z�b�g����֐�
//=======================================================
void RouteSearch::ResetNodeData()
{
	for (int cntY = 0; cntY != SIZE_Y; cntY++) {
		for (int cntX = 0; cntX != SIZE_X; cntX++) {
			m_NodeData[cntY][cntX].Reset();
			m_NodeData[cntY][cntX].pos = Position(cntX, cntY);
		}
	}
}

//==================================================================
// �m�[�h�f�[�^����w�肳�ꂽ��Ԃ̃m�[�h�������邩�擾����֐�
//	@return	: ��
//==================================================================
int RouteSearch::GetCount(int status)
{
	int ret = 0;	// �J�E���^

	for (int cntY = 0; cntY < SIZE_Y; cntY++) {
		for (int cntX = 0; cntX < SIZE_X; cntX++) {
			// �w�肳�ꂽ��Ԃł���΃J�E���^�ɉ��Z����
			if (m_NodeData[cntY][cntX].status == status)
				ret++;
		}
	}

	return ret;
}

//=======================================================
// �w�肵���n�_����S�[���܂ł̋��������߂�i����j
//	@return	: ����
//=======================================================
float RouteSearch::GetDistance(Position pos)
{
	float ret;	// ����
	
	// ��Βl�ɏC��
	int x = abs(pos.x - m_GoalPos.x);
	int y = abs(pos.y - m_GoalPos.y);

	ret = (float)std::sqrt(x * x + y * y);	// ���[�N���b�h���������߂�
	ret = floor(ret * 10) / 10;			// ������Q�ʈȉ��؂�̂�

	return ret;
}

//=======================================================
// �w�肵���n�_����X�^�[�g�n�_�܂ł̋��������߂�
//	@return	: ����
//=======================================================
int RouteSearch::BackTrace(Position pos)
{
	int ret = 0;	// ����
	
	Node* pNode;
	pNode = &m_NodeData[pos.y][pos.x];

	//------------------------------------------
	// �e��k���Ă����A���������߂�
	//------------------------------------------
	while (true) {
		// �J�n�n�_�܂Ŗ߂����ꍇ�A�������I������
		if (pNode->pos == m_StartPos)
			break;
		if (pNode->parent == nullptr)
			break;

		// CLOSE�ȃm�[�h���m�F
		if (pNode->status != Node::Status::CLOSE)
			break;
		
		// �e�̃m�[�h�ōX�V
		pNode = pNode->parent;

		ret++;
	}

	return ret;
}

//=======================================================
// A*�Ōo�H�T������
//	@return	: �ړI�n�܂ŒT���ł������ǂ���
//=======================================================
bool RouteSearch::Search()
{

	while (true) {

		//-----------------------------------------------
		// ���x���ێ����邽�߂̏���
		//-----------------------------------------------
		// �T���ς݂̃m�[�h����萔�ȏ�̏ꍇ�A�T�����I������
		if (GetCount(Node::Status::CLOSE) >= 25) 
			return false;

		// 60FPS �������ꍇ�A�T�����I������
		if (m_MeasureTimer->ElapsedTime() >= 1000 / 60)
			return false;

		//-----------------------------------------------------------
		//OPEN�ȃm�[�h����S�[���܂ł̋�������ԒZ�����̂����o��
		//-----------------------------------------------------------
		Node* pNode = nullptr;	// �ŏ��̃R�X�g�����m�[�h�̃|�C���^
		{
			float costMin = 9999;
			for (int cntY = 0; cntY < SIZE_Y; cntY++) {
				for (int cntX = 0; cntX < SIZE_X; cntX++) {
					Node* pTmpNode = &m_NodeData[cntY][cntX];	// ���ݒ��ׂĂ���m�[�h
					
					// OPEN�ȃm�[�h�ȊO�̏ꍇ�A�����X�L�b�v
					if (pTmpNode->status != Node::Status::OPEN)
						continue;
					
					float tmpDis = GetDistance(pTmpNode->pos);	// �S�[���܂ł̋���

					/*
					// ���ݍŏ��̃R�X�g�Ɠ����ꍇ�A�T�����Ă��������Ɠ��������̂��̂�D�悷��
					if(costMin == tmpDis){
						if (pTmpNode->parent == nullptr)
							continue;
						if (pTmpNode->parent->parent == nullptr)
							continue;

						// �T�����Ă������������߂�
						Position parentPos = pTmpNode->parent->pos;
						Position parentParentPos = pTmpNode->parent->parent->pos;
						Position way = parentPos - parentParentPos;

						// ���������ł���΍X�V����
						if ((parentPos + way) == pTmpNode->pos) {
							costMin = tmpDis;
							pNode = &m_NodeData[cntY][cntX];
						}
					}
					// �������ꍇ�A�X�V����
					else if(costMin > tmpDis){
						costMin = tmpDis;
						pNode = &m_NodeData[cntY][cntX];
					}
					*/

					if (costMin > tmpDis) {
						costMin = tmpDis;
						pNode = &m_NodeData[cntY][cntX];
					}

				}
			}

			// OPEN�ȃm�[�h����Ȃ�T���I���i�S�[���܂ł̓����Ȃ���ԁj
			if (pNode == nullptr)
				return false;

			
			// �m�[�h�̏�Ԃ�CLOSE�ɂ���
			pNode->status = Node::Status::CLOSE;
			m_LastSearchNode = &m_NodeData[pNode->pos.y][pNode->pos.x];
			m_LastSearchNode = pNode;
		}


		// �ŏ��R�X�g�̃m�[�h����X�^�[�g�܂ł̈ړ��R�X�g
		int backCost = 0;
		backCost = BackTrace(pNode->pos);


		//-----------------------------------------------
		// �㉺���E�̂S�������m�F
		//-----------------------------------------------
		Node* pSubNode;
		Position way[] = {
			{  0, -1 },		// ��
			{  1,  0 },		// ��
			{  0,  1 },		// ��
			{ -1,  0 },		// �E
		};

		for (int i = 0; i < 4; i++) {
			// �אڂ���}�X�̍��W���v�Z (�S����)
			Position tmpPos;
			tmpPos = pNode->pos + way[i];

			// �͈͊O�̏ꍇ�͏������s��Ȃ�
			if (tmpPos.x < 0) continue;
			if (tmpPos.y < 0) continue;
			if (tmpPos.x >= SIZE_X) continue;
			if (tmpPos.y >= SIZE_Y) continue;

			// ���ȊO�̏ꍇ�͏������s��Ȃ�
			if (m_RouteData[tmpPos.y][tmpPos.x] != 0) continue;

			float score = backCost + GetDistance(tmpPos);
			pSubNode = &m_NodeData[tmpPos.y][tmpPos.x];

			// �T������Ă��Ȃ��m�[�h�̏ꍇ
			if (pSubNode->status == Node::Status::NONE) {
				// �f�[�^���Z�b�g���A�m�[�h�̏�Ԃ�OPEN�ɂ���
				pSubNode->SetNode(score, pNode);
				pSubNode->status = Node::Status::OPEN;
			}
			// ���ɒT�����ꂽ�m�[�h�̏ꍇ
			else if (score < pSubNode->score) {
				// �X�R�A���ȑO�̂��̂��Ⴏ��Ώ����ς��A��Ԃ�OPEN�ɂ���
				pSubNode->score = score;
				pSubNode->status = Node::Status::OPEN;
				pSubNode->parent = pNode;
			}

		}

		
		//-----------------------------------------------
		//����������T���I��
		//-----------------------------------------------
		if (pNode->pos == m_GoalPos)
			return true;

	}
}

