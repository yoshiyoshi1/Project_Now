#include "../main.h"
#include "../GameWorld.h"

#include "../Map/map.h"
#include "../Human/human.h"
#include "../Camera/Camera.h"
#include "SGame.h"

#include "../Car/CarBase.h"
#include "../Car/Taxi.h"

#include "../System/RouteSearch.h"

SGame::SGame()
{
	m_id = GAME;

	// �t�H�O�̐ݒ�
	//cdg.SetFog(1, XRGB(150,150,150), 15.0f, 17.0f);

	//----------------------------------------
	// ���C�g�̐ݒ�
	//----------------------------------------
	cdg.SetDirectionalLight(0,
		&CVector3(1, -1, 0),				// ���C�g�̕���
		&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// ��{�F(�f�B�t�[�Y RGBA)
		&D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f),	// ���F(�A���r�G���g RGBA)
		&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)	// ���ːF(�X�y�L���� RGBA)
	);

	//----------------------------------------
	// �����o�̃C���X�^���X���⏉�����Ȃ�
	//----------------------------------------
	m_Cam = new Camera();
	m_Cam->SetProj();
	m_map = new map();
	m_map->LoadMap();
	m_human = new human();
	m_human->SetMapData(m_map->t_MapData[0]);
	m_human->LoadHuman();

	m_Car = new Taxi();

	m_Route = new RouteSearch();
	m_Route->SetMapData(m_map->t_MapData[0]);

	m_mTest.CreateMove(0, 0, 10);

	//----------------------------------------
	// �f�[�^�̃��[�h
	//----------------------------------------
	//m_meshSample.LoadXFile("../data/Mesh/TestData/test.x");

	m_texSample[0].LoadTexture("../data/Sprite/TestData/back.png");
	m_texSample[1].LoadTexture("../data/Sprite/TestData/continue.png");

	m_meshSample.LoadXFile("../data/Mesh/Human/boy.x");

}

SGame::~SGame()
{
	Safe_Delete(m_Cam);
	Safe_Delete(m_map);
	Safe_Delete(m_human);
	Safe_Delete(m_Car);
	Safe_Delete(m_Route);
}

//===================================
// �Q�[����ʂ̍X�V
//===================================
int SGame::Update()
{
	// Esc �L�[�ŃQ�[���I��
	if (KeyCheck(VK_ESCAPE))
		return TITLE;

	// �f�o�b�O���[�h�ؑ�
	if (KeyCheck('1'))
		APP.m_isDebug = !APP.m_isDebug;
	
	m_human->Update();
	m_Car->Update();

	// �o�H�T�� ����e�X�g�p
	if(APP.m_isDebug){
		static int x = 1;
		static int y = 1;

		// �ړI�n�������_���Ɍ��߂�
		if (KeyCheck('G'))
			m_Route->ChangeGoal(RANDOM(1, 79), RANDOM(1, 79));

		// �����W����
		if (KeyCheck('L'))
			x++;
		if (KeyCheck('J'))
			x--;

		// �����W����
		if (KeyCheck('I'))
			y++;
		if (KeyCheck('K'))
			y--;

		// �T���J�n�n�_���Z�b�g����
		if (x > 0 && x < 80 && y>0 && y < 80)
			m_Route->ChangeStart(x, y);

		if (KeyCheck('U'))
			m_Route->ChangeSearchMode();
	}
	//m_Route->ChangeStart(1,1);
	m_Route->Update();

	return GAME;
}

//===================================
// �Q�[����ʂ̕`��
//===================================
void SGame::Draw()
{
	// �`��J�n
	cdg.GetDev()->BeginScene();

	// �o�b�N�o�b�t�@�� Z �o�b�t�@���N���A
	cdg.Clear(true, true, false, XRGB(0, 0, 100), 1.0f, 0);


	//-------------------------------------------
	// �J��������
	//-------------------------------------------
	{
		CMatrix m;
		m.CreateMove(0, -2, 10);

		// �Z�b�g�����s��̏ꏊ�𒍎��_�Ƃ���
		m_Cam->SetView(m_Car->GetMat());
	}

	//-------------------------------------------
	// �`�揈��
	//-------------------------------------------
	Render();


	cdg.BeginSprite();
	{
		//-------------------------------------------
		// �X�v���C�g	2D�摜
		//-------------------------------------------
		DrawSprite();

		//--------------------------------------------
		// �����\��
		//--------------------------------------------
		DisplayText();

	}
	cdg.EndSprite();

	// �`��I��
	cdg.GetDev()->EndScene();

}


//================================================================
// �`�揈��
//================================================================
void SGame::Render()
{

	//-------------------------------------------
	// �\���e�X�g�p
	//-------------------------------------------
	{
		cdg.CullMode(D3DCULL_CCW);
		m_map->DrawMap(m_Cam->GetvPos());
		m_human->DrawHuman();
		cdg.CullMode(D3DCULL_NONE);


		CMatrix m;
		m.CreateMove(0, -2, 10);

		m.RotateX_Local(r);
		m.RotateY_Local(r);
		r++;

		m_meshSample.Draw(&m);

		m_Car->Draw();
	}

	m_Route->Draw();

}

//================================================================
// �X�v���C�g�`��
//================================================================
void SGame::DrawSprite()
{

	//-------------------------------------------
	// �\���e�X�g�p
	//-------------------------------------------
	if(APP.m_isDebug){
		CMatrix m;

		m.CreateMove(0, 0, 1);
		cdg.DrawSprite(&m_texSample[0], ARGB_FULL, &m);

		m.CreateMove(100, 200, 1);
		cdg.DrawSprite(&m_texSample[1], ARGB_FULL, &m);
	}

}

//================================================================
// �e�L�X�g�\��
//================================================================
void SGame::DisplayText()
{
	//-------------------------------------------
	// FPS �\��
	//-------------------------------------------
	if(APP.m_isDebug){
		CMatrix m;
		m.CreateMove(10, 10, 0);

		cdg.DrawFont(ARGB_FULL, &m, "FPS = %d", FpsProc());
	}

	//-------------------------------------------
	// �o�H�T�� �֌W
	//-------------------------------------------
	if(APP.m_isDebug){
		CMatrix m;

		// ���݂̒T���A���S���Y��
		m.CreateMove(10, 40, 0);
		if (m_Route->GetSearchMode() == RouteSearch::SearchMode::ASTAR) {
			cdg.DrawFont(ARGB(255, 255, 0, 255), &m, "SearchMode : A-Star");
		}
		else if (m_Route->GetSearchMode() == RouteSearch::SearchMode::DIJKSTRA) {
			cdg.DrawFont(ARGB(255, 255, 0, 255), &m, "SearchMode : Dijkstra");
		}

		// �J�n�n�_�̍��W
		m.CreateMove(10, 70, 0);
		cdg.DrawFont(ARGB(255, 255, 0, 255), &m, "StartPos\t = %2d, %2d", m_Route->GetStartPosX(), m_Route->GetStartPosY());

		// �ړI�n�̍��W
		m.CreateMove(10, 100, 0);
		cdg.DrawFont(ARGB(255, 255, 0, 255), &m, "GoalPos \t = %2d, %2d", m_Route->GetGoalPosX(), m_Route->GetGoalPosY());

		// �o�H�T���ɂ����������ԁi�~���b�j
		m.CreateMove(10, 130, 0);
		cdg.DrawFont(ARGB(255, 255, 0, 255), &m, "ElapsedTime \t = %4d ms", m_Route->GetEndTime());

		
	}

}
