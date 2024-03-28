//=============================================================================
// 
//  メイン処理 [main.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _MAIN_H_	// このマクロ定義がされていなかったら
#define _MAIN_H_	// 二重インクルード防止のマクロを定義する

//==========================================================================
// マクロ定義
//==========================================================================
#define SCREEN_WIDTH		(1280)		// ウインドウの幅
#define SCREEN_HEIGHT		(720)		// ウインドウの高さ
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 頂点フォーマット
#define FVF_VERTEX_2D_MULTITEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2)
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// 頂点フォーマット3D
#define MESH_FVF (D3DFVF_XYZ | D3DFVF_NORMAL)

#define ACTION_MODE		(0)								// アクション
#define TOPCUR		(1)								// アクション
#define MODE_SCREENSHOT	(1)	// スクショモード

#if 0
#define AUTO_MOVE			(1)				// 移動の切り替え
#endif

//==========================================================================
// 頂点情報の構造体を宣言
//==========================================================================
typedef struct
{
	MyLib::Vector3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	MyLib::Vector2 tex;	// テクスチャ座標
}VERTEX_2D;

typedef struct
{
	MyLib::Vector3 pos;
	float rhw;
	D3DCOLOR col;
	MyLib::Vector2 tex;	// テクスチャ座標
	MyLib::Vector2 tex2;	// テクスチャ座標
}VERTEX_2D_MULTITEX;

// 頂点情報[3D]の構造体を定義
typedef struct
{
	MyLib::Vector3 pos;		// 頂点座標
	MyLib::Vector3 nor;		// 法線ベクトル
	D3DCOLOR col;			// 頂点カラー
	MyLib::Vector2 tex;		// テクスチャ座標
} VERTEX_3D;

struct VERTEX
{
	MyLib::Vector3 pos;
	MyLib::Color col;
};

//==========================================================================
// プロトタイプ宣言
//==========================================================================
int GetFPS();
HWND GetWnd();

class CMyEffekseer;
class CLoadManager;

CLoadManager* GetLoadManager();
//void Render(MyLib::Vector3 pos, MyLib::Vector3 scale, MyLib::Vector3 degree);

#endif