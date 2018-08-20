#include "../main.h"
#include "ThreadGuard.h"
#include "Timer.h"

#include "RouteSearch.h"

RouteSearch::RouteSearch()
{
	// 仮データ
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

	// 前回の更新から0.1秒経過していない場合、以降の処理を行わない
	if (m_UpdateTimer->ElapsedTime(0.1f) == false)
		return;

	// 目的地が変わっていない場合、
	if (m_GoalPos == m_NextGoalPos) {
		// 開始地点も変わっていない場合、以降の処理を行わない
		if (m_StartPos == m_NextStartPos)
			return;
		
		// 次の開始地点がCLOSEの場合、以降の処理を行わない
		//if (CheckPos(m_NextStartPos))
		//	return;
	}
	
	// m_NextGoalPos が道以外ならば、以降の処理を行わない
	if (m_RouteData[m_NextGoalPos.y][m_NextGoalPos.x] != 0)
		return;

	// 経路探索データをリセットする
	Reset(m_NextStartPos);
	
	// 新たな目的地として設定
	m_GoalPos = m_NextGoalPos;

	// 計測開始
	m_MeasureTimer->SetTime();

	// 経路探索を別スレッドで行う
	std::thread sThread(&RouteSearch::Search, this);	// 経路探索用スレッドの作成
	m_SearchThread = std::move(sThread);				// メンバー関数にスレッドを受け渡す
	//ThreadGuard threadGuard(searchThread);			// エラーで落ちた際に自動でJoinを行う
}

void RouteSearch::Draw()
{
	// 経路探索用スレッドが動いている場合、
	if (m_SearchThread.joinable()) {
		m_SearchThread.join();						// 探索終了まで待機
		m_EndTime = m_MeasureTimer->ElapsedTime();	// 探索終了までの経過時間
	}

	// 最後に探索したノードをセットする
	Node* pNode;
	pNode = m_LastSearchNode;
	if (pNode == nullptr)
		return;

	// CLOSEなノードの数を取得
	int closeSize = GetCount(Node::Status::CLOSE);

	for (int i = 0; ; i++) {

		// 経路をピンのメッシュで表示
		CMatrix m;
		int blue = (int)(i * (255.0f / closeSize));
		int red = 255 - blue;
		m.CreateMove(pNode->pos.x * 2.0f, -3.0f, pNode->pos.y * 2.0f);
		m_meshPin.Draw(&m, ARGB_D3DX(255, red, 0, blue));

		// 親がいない場合、処理を終了する
		if (pNode->parent == nullptr)
			return;

		// 親のノードで更新
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
// ノードデータを初期化してスタート地点をセットする関数
//=======================================================
void RouteSearch::Reset(Position pos)
{
	ResetNodeData();

	m_StartPos = pos;

	// スタート地点のノードをOPENにする
	Node* pStartNode = &m_NodeData[m_StartPos.y][m_StartPos.x];
	pStartNode->SetNode(0, nullptr);
	pStartNode->status = Node::Status::OPEN;
}

//=======================================================
// 指定した座標がCLOSEなノードかどうか調べる関数
//	@return	: CLOSEかどうか
//=======================================================
bool RouteSearch::CheckPos(Position pos)
{
	Node* pNode;
	pNode = &m_NodeData[pos.y][pos.x];

	// CLOSE以外ならばfalse
	if (pNode->status != Node::Status::CLOSE)
		return false;

	//------------------------------------------
	// 親が存在しない場合
	//------------------------------------------
	if (pNode->parent == nullptr) {
		m_StartPos = pos;
		return true;
	}

	//------------------------------------------
	// 親が存在する場合
	//------------------------------------------
	std::vector<Node*> parentNodeList;	// 親ノードのリスト
	parentNodeList.clear();
	
	while (true) {
		// 開始地点まで戻った場合、処理を終了する
		if (pNode->pos == m_StartPos)
			break;
		if (pNode->parent == nullptr)
			break;

		if (pNode->status != Node::Status::CLOSE)
			break;

		// 親のノードで更新
		pNode = pNode->parent;
		
		// 親のポインタをリストに保存しておく
		parentNodeList.push_back(pNode);
	}

	// 親のノードをリセットする
	for (Node* pParentNode : parentNodeList) {
		pParentNode->Reset();
	}

	// 指定した座標を開始地点とする
	m_NodeData[pos.y][pos.x].parent = nullptr;
	m_StartPos = pos;
	
	return true;
}

//=======================================================
// ノードデータをリセットする関数
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
// ノードデータから指定された状態のノードが何個あるか取得する関数
//	@return	: 個数
//==================================================================
int RouteSearch::GetCount(int status)
{
	int ret = 0;	// カウンタ

	for (int cntY = 0; cntY < SIZE_Y; cntY++) {
		for (int cntX = 0; cntX < SIZE_X; cntX++) {
			// 指定された状態であればカウンタに加算する
			if (m_NodeData[cntY][cntX].status == status)
				ret++;
		}
	}

	return ret;
}

//=======================================================
// 指定した地点からゴールまでの距離を求める（推定）
//	@return	: 距離
//=======================================================
float RouteSearch::GetDistance(Position pos)
{
	float ret;	// 距離
	
	// 絶対値に修正
	int x = abs(pos.x - m_GoalPos.x);
	int y = abs(pos.y - m_GoalPos.y);

	ret = (float)std::sqrt(x * x + y * y);	// ユークリッド距離を求める
	ret = floor(ret * 10) / 10;			// 小数第２位以下切り捨て

	return ret;
}

//=======================================================
// 指定した地点からスタート地点までの距離を求める
//	@return	: 距離
//=======================================================
int RouteSearch::BackTrace(Position pos)
{
	int ret = 0;	// 距離
	
	Node* pNode;
	pNode = &m_NodeData[pos.y][pos.x];

	//------------------------------------------
	// 親を遡っていき、距離を求める
	//------------------------------------------
	while (true) {
		// 開始地点まで戻った場合、処理を終了する
		if (pNode->pos == m_StartPos)
			break;
		if (pNode->parent == nullptr)
			break;

		// CLOSEなノードか確認
		if (pNode->status != Node::Status::CLOSE)
			break;
		
		// 親のノードで更新
		pNode = pNode->parent;

		ret++;
	}

	return ret;
}

//=======================================================
// A*で経路探索する
//	@return	: 目的地まで探索できたかどうか
//=======================================================
bool RouteSearch::Search()
{

	while (true) {

		//-----------------------------------------------
		// 速度を維持するための処理
		//-----------------------------------------------
		// 探索済みのノードが一定数以上の場合、探索を終了する
		if (GetCount(Node::Status::CLOSE) >= 25) 
			return false;

		// 60FPS を下回る場合、探索を終了する
		if (m_MeasureTimer->ElapsedTime() >= 1000 / 60)
			return false;

		//-----------------------------------------------------------
		//OPENなノードからゴールまでの距離が一番短いものを取り出す
		//-----------------------------------------------------------
		Node* pNode = nullptr;	// 最小のコストを持つノードのポインタ
		{
			float costMin = 9999;
			for (int cntY = 0; cntY < SIZE_Y; cntY++) {
				for (int cntX = 0; cntX < SIZE_X; cntX++) {
					Node* pTmpNode = &m_NodeData[cntY][cntX];	// 現在調べているノード
					
					// OPENなノード以外の場合、処理スキップ
					if (pTmpNode->status != Node::Status::OPEN)
						continue;
					
					float tmpDis = GetDistance(pTmpNode->pos);	// ゴールまでの距離

					/*
					// 現在最小のコストと同じ場合、探索してきた方向と同じ方向のものを優先する
					if(costMin == tmpDis){
						if (pTmpNode->parent == nullptr)
							continue;
						if (pTmpNode->parent->parent == nullptr)
							continue;

						// 探索してきた方向を求める
						Position parentPos = pTmpNode->parent->pos;
						Position parentParentPos = pTmpNode->parent->parent->pos;
						Position way = parentPos - parentParentPos;

						// 同じ方向であれば更新する
						if ((parentPos + way) == pTmpNode->pos) {
							costMin = tmpDis;
							pNode = &m_NodeData[cntY][cntX];
						}
					}
					// 小さい場合、更新する
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

			// OPENなノードが空なら探索終了（ゴールまでの道がない状態）
			if (pNode == nullptr)
				return false;

			
			// ノードの状態をCLOSEにする
			pNode->status = Node::Status::CLOSE;
			m_LastSearchNode = &m_NodeData[pNode->pos.y][pNode->pos.x];
			m_LastSearchNode = pNode;
		}


		// 最小コストのノードからスタートまでの移動コスト
		int backCost = 0;
		backCost = BackTrace(pNode->pos);


		//-----------------------------------------------
		// 上下左右の４方向を確認
		//-----------------------------------------------
		Node* pSubNode;
		Position way[] = {
			{  0, -1 },		// 下
			{  1,  0 },		// 左
			{  0,  1 },		// 上
			{ -1,  0 },		// 右
		};

		for (int i = 0; i < 4; i++) {
			// 隣接するマスの座標を計算 (４方向)
			Position tmpPos;
			tmpPos = pNode->pos + way[i];

			// 範囲外の場合は処理を行わない
			if (tmpPos.x < 0) continue;
			if (tmpPos.y < 0) continue;
			if (tmpPos.x >= SIZE_X) continue;
			if (tmpPos.y >= SIZE_Y) continue;

			// 道以外の場合は処理を行わない
			if (m_RouteData[tmpPos.y][tmpPos.x] != 0) continue;

			float score = backCost + GetDistance(tmpPos);
			pSubNode = &m_NodeData[tmpPos.y][tmpPos.x];

			// 探索されていないノードの場合
			if (pSubNode->status == Node::Status::NONE) {
				// データをセットし、ノードの状態をOPENにする
				pSubNode->SetNode(score, pNode);
				pSubNode->status = Node::Status::OPEN;
			}
			// 既に探索されたノードの場合
			else if (score < pSubNode->score) {
				// スコアが以前のものより低ければ書き変え、状態をOPENにする
				pSubNode->score = score;
				pSubNode->status = Node::Status::OPEN;
				pSubNode->parent = pNode;
			}

		}

		
		//-----------------------------------------------
		//見つかったら探索終了
		//-----------------------------------------------
		if (pNode->pos == m_GoalPos)
			return true;

	}
}

