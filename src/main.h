#ifndef __main_h__
#define __main_h__

#include "../SimpleLib/SimpleLib.h"

using namespace SimpleLib;

//============================================================
//
// �A�v���P�[�V�����N���X
//	�O���[�o���ϐ��Ȃǂ��W�߂��悤�ȃN���X
//
//============================================================
class CApp
{
public:
	//=================================================
	// �E�B���h�E�֌W
	HINSTANCE	m_hInst;			
	HWND		m_hWnd;				
	int			m_WndW,m_WndH;		
	bool		m_CloseFlag;		
	bool		m_bEndFlag;			// �I���t���O	
	DWORD		m_FrameCnt;	

	bool		m_isDebug = false;	// �f�o�b�O�����ǂ���

	// �E�B���h�E������
	bool InitWindow(HINSTANCE hInstance,int w,int h);	

	// ���̑��̏�����
	void Init();

	// ���C�����[�v
	int Loop();

	// ���
	void Release();

	// �E�B���h�E�֐�
	static LRESULT CALLBACK callWindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

	// �N���C�A���g�T�C�Y�̐ݒ�
	void SetClientSize(HWND hWnd,int w,int h);

	//=====================================================
	// �}�E�X�p
	int		m_MouseWheelVal;

//*********************************************
// �V���O���g���p�^�[��
private:
	// 
	CApp(){
		m_hWnd = nullptr;
		m_WndW = 0;
		m_WndH = 0;
		m_hInst = nullptr;
		m_CloseFlag = false;
		m_bEndFlag = false;
		m_FrameCnt = 0;
		m_MouseWheelVal = 0;

	}

public:
	static CApp &GetInstance(){
		static CApp Instance;
		return Instance;
	}
//*********************************************

};

#define APP CApp::GetInstance()


#endif
