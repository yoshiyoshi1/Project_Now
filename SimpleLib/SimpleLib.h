#ifndef __SimpleLib_h__
#define __SimpleLib_h__

//=========================================================
//
// ライブラリ関係
//
//=========================================================

//===============================================
// DirectX Lib
//===============================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"dxerr.lib")

//===============================================
//
//===============================================
#pragma comment(lib,"winmm.lib")


#pragma warning(disable : 4996)
#pragma warning(disable : 4819)

//=========================================================
//
// ヘッダファイルのインクルード
//
//=========================================================

//===============================================
// 基本
//===============================================
#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <math.h>
#include <commctrl.h>
#include <ctime>

//===============================================
// DirectX9
//===============================================
#include "d3d9.h"
#include "d3dx9.h"
#include "dsound.h"
#include "dxerr.h"

//===============================================
// STL
//===============================================
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <iterator>
#include <queue>
#include <algorithm>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

//===============================================
// SimpleLib
//	2年生授業用の簡易DirectX9操作クラス群
//===============================================
#include "Helper.h"
#include "CVector2.h"
#include "CVector3.h"
#include "CMatrix.h"
#include "CTexture.h"
#include "CDirectXGraphics.h"
#include "CSurface.h"
#include "CMesh.h"

//===============================================
// System
//===============================================
#include "../src/System/KeyInput.h"

#endif
