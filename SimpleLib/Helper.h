#ifndef __Helper_h__
#define __Helper_h__

//=================================================================
//
// あると便利なマクロや関数
//
//=================================================================


#pragma warning(disable:4996)
#include <string>

namespace SimpleLib{

//---------------------------------------------------------
// 角度変換
//---------------------------------------------------------
// 度 -> ラジアン 変換
#define ToRadian(x) ((x)*0.017453f)
// ラジアン -> 度 変換
#define ToDegree(x) ((x)*57.3f)

//---------------------------------------------------------
// 安全なポインタの解放
//---------------------------------------------------------
#define SAFE_FREE(p)		{if(p){free(p);p=nullptr;}}				// mallocしたものを安全にfreeするマクロ
#define SAFE_RELEASE(p)		{if(p){p->Release();p=nullptr;}}		// COMオブジェクト系を安全にReleaseするマクロ
#define SAFE_DELETE(p)		{if(p){delete p;p=nullptr;}}			// newされた変数を安全に解放するマクロ
#define SAFE_DELETE_ARRAY(p){if(p){delete[] p;p=nullptr;}}			// newされた配列を安全に解放するマクロ

// COMオブジェクト系を安全にReleaseする
template<class T>
void Safe_Release(T p)
{
	p->Release();
	p = nullptr;
}
// newされた変数を安全に解放する
template<class T>
void Safe_Delete(T p)
{
	delete p;
	p = nullptr;
}
// newされた配列を安全に解放する
template<class T>
void Safe_Delete_Array(T p) 
{
	delete[] p; 
	p = nullptr;
}

//---------------------------------------------------------
// 色関係の短縮名用
//---------------------------------------------------------
#define XRGB(r,g,b) D3DCOLOR_XRGB(r,g,b)
#define ARGB(a,r,g,b) D3DCOLOR_ARGB(a,r,g,b)
#define RGBA(r,g,b,a) D3DCOLOR_RGBA(r,g,b,a)
#define COLORVALUE(a,r,g,b) D3DCOLOR_COLORVALUE(r,g,b,a)
#define ARGB_FULL D3DCOLOR_ARGB(255,255,255,255)
#define ARGB_D3DX(a,r,g,b) ((D3DXCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

//---------------------------------------------------------
// 表示関係
//---------------------------------------------------------
// FPS計測
DWORD FpsProc();

// ログ出力
void AddLogFile(char *LogFileName,char *str, bool bData=false);

//=================================================================
// 可変引数メッセージボックス
//=================================================================
inline void DispMsg(HWND hWnd,char *format, ...)
{
	char str[1024];
	va_list argptr;

	va_start(argptr, format);
	vsprintf(str,format, argptr);
	va_end(argptr);

	MessageBox(hWnd,str,"Message",MB_OK);
}

// キー判定(1回押し)
bool KeyCheck(int keyCode);


//==========================================================
// 配列を０で埋めるテンプレート関数
//	適用したい配列　と　その配列のサイズ　を引数に
//	例) int sample[10][10];
//		ArrayZeroClear(&**sample, sizeof(sample));
//==========================================================
template<class T>
bool ArrayZeroClear(T* array, int size) {
	for (int i = 0; i < (size/sizeof(T)); i++) {
		array[i] = 0;
	}
	return true;
}

//==========================================================
// 動的に配列の領域を確保するテンプレート関数
//	適用したい配列　と　その配列のサイズ　を引数に
//	例) int sample[20]　のような配列を作る場合
//		int* sample;
//		sample = Dynamic1DArray<int, 20>();
//	※解放を忘れずに行うこと
//==========================================================
template<class T, int size>
T* Dynamic1DArray() {
	T* p = new T[size];
	return p;
}

//==========================================================
// 動的に２次元配列の領域を確保するテンプレート関数
//	適用したい配列　と　その配列のサイズ　を引数に
//	例) int sample[20][10]　のような配列を作る場合
//		int** sample;
//		sample = Dynamic2DArray<int, 20, 10>();
//	※解放を忘れずに行うこと
//==========================================================
template<class T, int sizeY, int sizeX>
T** Dynamic2DArray() {
	T** p = new T*[sizeY];
	for (int i = 0; i < sizeY; i++) {
		p[i] = new T[sizeX];
	}
	return p;
}

//==========================================================
// 動的に確保した２次元配列を解放するテンプレート関数
//	適用したい配列　と　その配列のサイズ　を引数に
//	例) int sample[20][10]　のように作った配列を解放する場合
//		Safe_Delete2DArray<int, 20>(sample);
//==========================================================
template<class T, int sizeY>
void Safe_Delete_2DArray(T** p)
{
	// 動的に確保した２次元配列を解放
	for (int i = 0; i < sizeY; i++) {
		Safe_Delete(p[i]);
	}
	Safe_Delete(p);
}

//---------------------------------------------------------
// 乱数関係
//---------------------------------------------------------
// 乱数の初期化
#define INIT_RANDOM srand((unsigned)time(nullptr))
// 乱数の取得
#define RANDOM(Min, Max) rand()%Max + Min

}


#endif
