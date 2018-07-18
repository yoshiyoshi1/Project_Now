//======================================================================================
//
// ゲームサイクル
//
//======================================================================================
#include "main.h"
#include "GameWorld.h"

//=========================================================
//メイン
//=========================================================
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInst,LPSTR lpszArgs,int nWinMode)
{
	// メモリリークを知らせる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);

	if(APP.InitWindow(hInstance, 1280, 720) == false){
		return 0;
	}

	// その他の初期化
	APP.Init();

	// ループ
	APP.Loop();

	// 解放
	APP.Release();

	return 0;
}

//=========================================================
// 初期設定
//=========================================================
bool CApp::InitWindow(HINSTANCE hInstance,int w,int h)
{
	// カレントディレクトリ取得
	m_hInst = hInstance;

	//--------------------------------------------------------------------
	// メインウィンドウ作成
	//--------------------------------------------------------------------
	//ウィンドウクラスの定義
	WNDCLASSEX wc;											
	wc.cbSize=sizeof(WNDCLASSEX);							
	wc.style = 0;											
	wc.lpfnWndProc = &CApp::callWindowProc;					
	wc.cbClsExtra = 0;										
	wc.cbWndExtra = 0;										
	wc.hInstance = m_hInst;									
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);			
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);		
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);			
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	wc.lpszMenuName = nullptr;								
	wc.lpszClassName = "Window";							

	//ウィンドウクラスの登録
	if(!RegisterClassEx(&wc)){
		return FALSE;
	}

	//ウィンドウの作成
	m_hWnd = CreateWindow(
		"Window",										
		"Team_NOW",		// タイトルバー										
		WS_OVERLAPPEDWINDOW-WS_THICKFRAME,					
		0,												
		0,																	
		800,											
		600,											
		nullptr,										
		nullptr,										
		m_hInst,										
		nullptr);										

	// クライアントのサイズを設定
	SetClientSize(m_hWnd,w,h);

	timeBeginPeriod(1);

	//--------------------------------------------------------------------
	// フルスクリーン確認
	//--------------------------------------------------------------------
	bool bFullScreen = false;
	if (MessageBox(m_hWnd, "フルスクリーンにしますか？", "確認", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		bFullScreen = true;
	}

	//--------------------------------------------------------------------
	// Direct3D初期化
	//--------------------------------------------------------------------
	if(cdg.Init(m_hWnd, m_WndW, m_WndH, D3DFMT_X8R8G8B8, bFullScreen) == FALSE){
		MessageBox(m_hWnd,"Direct3D初期化ミス","",MB_OK);
		return FALSE;
	}

	// 基本的なレンダーステート設定
	cdg.SetState();

	//--------------------------------------------------------------------
	//ウィンドウの表示
	//--------------------------------------------------------------------
	ShowWindow(m_hWnd,SW_SHOW);
	//ウィンドウの更新
	UpdateWindow(m_hWnd);


	//--------------------------------------------------------------------
	// その他
	//--------------------------------------------------------------------
	m_CloseFlag = false;
	m_bEndFlag = false;

	return TRUE;
}

//======================================================
// 解放
//======================================================
void CApp::Release()
{
	// シングルトンのインスタンス削除
	GW->DeleteInstance();
	KINPUT->DeleteInstance();

	// Direct3D解放
	cdg.Release();
}

//======================================================
// 初期化
//======================================================
void CApp::Init()
{
	// シングルトンのインスタンス化
	GW->CreateInstance();
	KINPUT->CreateInstance();
}

//======================================================
// メインループ
//======================================================
int CApp::Loop()
{
	MSG msg;	
	
	//メッセージループ
	while(1){
		
		// ×ボタン押したら終了フラグON。
		if (m_CloseFlag) {
			m_bEndFlag = true;		// 終了フラグON
		}
		
		// 終了フラグが立っているなら、ループから出る
		if (m_bEndFlag)break;

		// メッセージ取得
		if(PeekMessage(&msg,nullptr,0,0,PM_REMOVE)){
			//メッセージ処理
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// ゲーム処理
		else{
			
			//------------------------------------------
			// FPS処理
			//------------------------------------------
			DWORD NowTime = timeGetTime();
			static DWORD PrevTime = 0;
			if ((NowTime - PrevTime) < 1000 / 60)continue;

			//------------------------------------------
			// ゲームの処理・描画
			//------------------------------------------
			GW->Update();
			
			GW->Draw();
			cdg.GetDev()->Present(nullptr, nullptr, nullptr, nullptr);


			//------------------------------------------
			// その他の処理
			//------------------------------------------
			// ホイール値はリセット
			m_MouseWheelVal = 0;

			PrevTime = NowTime;
			m_FrameCnt++;
		}
		
	}

	return 0;
}

//======================================================
//ウィンドウ関数 callWindowProc
//======================================================
LRESULT CALLBACK CApp::callWindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	return APP.WindowProc(hWnd,message,wParam,lParam);
}

//======================================================
// ウィンドウ関数 WindowProc
//======================================================
LRESULT CApp::WindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{

	//メッセージによって処理を選択
	switch(message){
		case WM_SIZE:
			{
				RECT rcWnd,rcCli;
				GetWindowRect(hWnd, &rcWnd); // ウィンドウのRECT取得
				GetClientRect(hWnd, &rcCli); // クライアント領域のRECT取得
				m_WndW = rcCli.right;
				m_WndH = rcCli.bottom;
			}
			break;
		case WM_CLOSE:// ウィンドウを閉じた時
			m_CloseFlag = true;
			break;
		// ホイールスクロール時
		case WM_MOUSEWHEEL:
			{
				m_MouseWheelVal = (short)HIWORD(wParam);
			}
			break;
        default:
			//不要なメッセージの後始末
			return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}


//======================================================
// ウィンドウのクライアントのサイズを指定サイズにする。
//======================================================
void CApp::SetClientSize(HWND hWnd,int w,int h)
{
	RECT rcWnd,rcCli;

	GetWindowRect(hWnd,&rcWnd); // ウィンドウのRECT取得
	GetClientRect(hWnd,&rcCli); // クライアント領域のRECT取得

	// ウィンドウの余白を考えて、クライアントのサイズを指定サイズにする。
	MoveWindow(hWnd,
			rcWnd.left,// X座標
			rcWnd.top,// Y座標
			w + (rcWnd.right-rcWnd.left)-(rcCli.right-rcCli.left),
			h + (rcWnd.bottom-rcWnd.top)-(rcCli.bottom-rcCli.top),
			TRUE);
}
