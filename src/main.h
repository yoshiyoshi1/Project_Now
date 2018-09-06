#ifndef __main_h__
#define __main_h__

#include "../SimpleLib/SimpleLib.h"

using namespace SimpleLib;

//============================================================
//
// アプリケーションクラス
//	グローバル変数などを集めたようなクラス
//
//============================================================
class CApp
{
public:
	//=================================================
	// ウィンドウ関係
	HINSTANCE	m_hInst;			
	HWND		m_hWnd;				
	int			m_WndW,m_WndH;		
	bool		m_CloseFlag;		
	bool		m_bEndFlag;			// 終了フラグ	
	DWORD		m_FrameCnt;	

	bool		m_isDebug = false;	// デバッグ中かどうか

	// ウィンドウ初期化
	bool InitWindow(HINSTANCE hInstance,int w,int h);	

	// その他の初期化
	void Init();

	// メインループ
	int Loop();

	// 解放
	void Release();

	// ウィンドウ関数
	static LRESULT CALLBACK callWindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

	// クライアントサイズの設定
	void SetClientSize(HWND hWnd,int w,int h);

	//=====================================================
	// マウス用
	int		m_MouseWheelVal;

//*********************************************
// シングルトンパターン
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
