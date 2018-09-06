//**********************************************
//
//		�Q�[����ʂ��Ǘ�����N���X
//
//**********************************************


#ifndef __SGame_h__
#define __SGame_h__

#include "SceneBase.h"

class Camera;
class map;
class human;

class Taxi;

class RouteSearch;

class SGame :public SceneBase
{
public:
	SGame();
	~SGame();

	int Update()override;
	void Draw()override;

	// 3D�`��
	void Render()override;
	// �X�v���C�g�`��
	void DrawSprite()override;
	// �e�L�X�g�\��
	void DisplayText()override;

private:
	Camera * m_Cam;
	map* m_map;
	human* m_human;

	Taxi* m_Car;

	// �\���e�X�g�p
	CTexture m_texSample[2];
	CMesh m_meshSample;
	CMatrix m_mTest;	// �����Ώۂ̍s��

	float r;

	RouteSearch* m_Route;
};

#endif