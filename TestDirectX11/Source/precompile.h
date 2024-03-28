//=============================================================================
// 
//  プリコンパイルヘッダー [precompile.h]
//  Author : 相馬靜雅＆東先生
// 
//=============================================================================
#ifndef _PRECOMPIRE_H_
#define _PRECOMPIRE_H_	// 二重インクルード防止

#include <Windows.h>
#define WIN32_LEAN_AND_MEAN		// Windows ヘッダーからほとんど使用されていない部分を除外する

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <DirectXMath.h>	// ベクトルやFLOAT3など便利な算術ライブラリ
using namespace DirectX;

#include <d2d1.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

// C++のstd用
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iterator>
#include <codecvt>
#include <fstream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <stack>


// ライブラリのリンク
#pragma comment(lib, "d3d11.lib")		// 描画処理に必要
#ifndef _DEBUG
#pragma comment(lib, "d3dx11.lib")		// [d3d11.lib]の拡張ライブラリ
#else
#pragma comment(lib, "d3dx11d.lib")		// [d3d11.lib]の拡張ライブラリ
#endif
#pragma comment(lib, "dxguid.lib")		// DirectXコンポネート(部品)使用に必要
#pragma comment(lib, "winmm.lib")		// システム時刻取得に必要
#pragma comment(lib, "dinput8.lib")		// 入力処理に必要
#pragma comment(lib, "dsound.lib")

#define DIRECTINPUT_VERSION	(0x0800)	// ビルド時の警告用マクロ
#include <dinput.h>						// 入力処理に必要
#include <xaudio2.h>					// サウンド処理に必要
#include <dsound.h>						// サウンド内部処理に必要
#include <Xinput.h>


// DirectXAPI関係のリンク
#pragma comment(lib, "dxgi.lib")

// シェーダコンパイル周りの機能をインクルード
#include <d3dcompiler.h>

// シェーダコンパイル用の静的ライブラリをリンク
#pragma comment(lib, "d3dcompiler.lib")

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

#include <d3d11.h>			// 描画処理に必要
#include <wrl/client.h>		// デバイスの管理をしやすくするためのDirectX版のスマートポインタのようなもの
using Microsoft::WRL::ComPtr;

// マイライブラリ
#include "mylib.h"

// エフェクシア
#ifndef _DEBUG
#pragma comment(lib, "Effekseer.lib")
#else
#pragma comment(lib, "Effekseerd.lib")
#endif
#include <Effekseer.h>

#ifndef _DEBUG
#pragma comment(lib, "EffekseerRendererDX9.lib")
#else
#pragma comment(lib, "EffekseerRendererDX9d.lib")
#endif
#include <EffekseerRendererDX9.h>

// json
#include <json.hpp>
using json = nlohmann::json;
//
//// Imgui
//#define IMGUI_DEFINE_MATH_OPERATORS
//#include "imgui.h"
//#include "imgui_impl_dx9.h"
//#include "imgui_impl_win32.h"
//#include <implot.h>
//#include <implot_internal.h>

// メモリリーク出力用マクロ
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>		// メモリリーク検出に必要

// crtdbg.hのバグ対策用マクロ
#if _DEBUG
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else

#define DEBUG_NEW new
#endif

#endif	// _PRECOMPIRE_H_