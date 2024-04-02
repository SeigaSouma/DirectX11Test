//=============================================================================
// 
//  メイン処理 [main.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "manager.h"
//#include "MyEffekseer.h"
//#include "loadmanager.h"

//==========================================================================
// マクロ定義
//==========================================================================
#define CLASS_NAME		"WindowsClass"	// ウインドウクラスの名前
#define WINDOW_NAME		"DirectX11"		// ウインドウの名前(キャプション)

//==========================================================================
// プロトタイプ宣言
//==========================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//==========================================================================
// グローバル変数宣言
//==========================================================================
int g_nCountFPS;
CLoadManager* LoadManager = nullptr;
HWND hWnd;	// ウインドウハンドル(識別子)

//=====================================================================//
//! ポリゴン出力用カスタムバーテックス構造体
//=====================================================================//
struct CustomVertex
{
	MyLib::Vector3 Position;		// 座標(x, y, z)
	MyLib::Vector3 Normal;			// 法線
	MyLib::Color Color;			// 頂点カラー
	MyLib::Vector2 TexturePos;		// テクスチャ座標(u, v)
};


struct ObjMaterial
{
	ObjMaterial()
	{
		for (int i = 0; i < 4; i++)
		{
			Ambient[i] = 1.0f;
			Diffuse[i] = 1.0f;
			Specular[i] = 1.0f;
		}
		//TextureKeyWord = "";
		//TextureName = "";
	}

	void SetAmbient(float r, float g, float b, float factor)
	{
		Ambient[0] = r;
		Ambient[1] = g;
		Ambient[2] = b;
		Ambient[3] = factor;
	}

	void SetDiffuse(float r, float g, float b, float factor)
	{
		Diffuse[0] = r;
		Diffuse[1] = g;
		Diffuse[2] = b;
		Diffuse[3] = factor;
	}

	void SetSpecular(float r, float g, float b, float factor)
	{
		Specular[0] = r;
		Specular[1] = g;
		Specular[2] = b;
		Specular[3] = factor;
	}

	float Ambient[4];
	float Diffuse[4];
	float Specular[4];
	float Alpha;
	//std::string TextureKeyWord;
	//std::string TextureName;
};

struct MeshData
{
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;			//!< @brief 頂点バッファ(Shader送信用)
	LPDIRECT3DINDEXBUFFER9 m_IndexBuffer;			//!< @brief インデックスバッファ(Shader送信用)
	std::vector<CustomVertex> m_Vertices;
	std::vector<UINT> m_Indices;
	std::string m_MaterialName;
};

std::vector<MeshData> m_MeshList;
std::map<std::string, ObjMaterial> m_Materials;


// Direct3Dデバイス
ComPtr<ID3D11Device>		m_device;

// Direct3Dデバイスコンテキスト
ComPtr<ID3D11DeviceContext>	m_deviceContext;

// スワップチェイン
ComPtr<IDXGISwapChain>		m_swapChain;

// バックバッファーのRTビュー
ComPtr<ID3D11RenderTargetView> m_backBufferView;

//==========================================================================
// メイン関数
//==========================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmbLine, int nCmbShow)
{
	// メモリリークを出力
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// WICファイル読込のため、COMを初期化しておく
	auto result = CoInitializeEx(NULL, COINITBASE_MULTITHREADED);
	if (FAILED(result)) return 1;

	/*DXApplication dxApp(1280, 720, L"DX Sample");
	Win32Application::Run(&dxApp, hInstance);*/

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WNDCLASSのメモリサイズ
		CS_CLASSDC,							// ウインドウのスタイル
		WindowProc,							// ウインドウプロシージャ
		0,									// 0にする(通常は使用しない)
		0,									// 0にする(通常は使用しない)
		hInstance,							// インスタンスハンドル
		LoadIcon(nullptr, IDI_APPLICATION),	// タスクバーのアイコン
		LoadCursor(nullptr, IDC_ARROW),		// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			// クライアント領域の背景色
		nullptr,								// メニューバー
		CLASS_NAME,							// ウインドウクラスの名前
		LoadIcon(nullptr, IDI_APPLICATION)		// ファイルのアイコン
	};

	//HWND hWnd;	// ウインドウハンドル(識別子)
	MSG msg;	// メッセージを格納する変数

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	// 画面サイズの構造体

	// ウインドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウインドウの生成
	hWnd = CreateWindowEx(
		0,									// 拡張ウインドウスタイル
		CLASS_NAME,							// ウインドウクラスの名前
		WINDOW_NAME,						// ウインドウの名前
		WS_OVERLAPPEDWINDOW,				// ウインドウスタイル
		CW_USEDEFAULT,						// ウインドウの左上X座標
		CW_USEDEFAULT,						// ウインドウの左上Y座標
		(rect.right - rect.left),			// ウインドウの幅
		(rect.bottom - rect.top),			// ウインドウの高さ
		nullptr,								// 親ウインドウのハンドル
		nullptr,								// メニューハンドルまたは子ウインドウID
		hInstance,							// インスタンスハンドル
		nullptr								// ウインドウ作成データ
	);

	DWORD dwCurrentTime;					// 現在時刻
	DWORD dwExecLastTime;					// 最後に処理した時刻
	DWORD dwFrameCount;						// フレームカウント
	DWORD dwFPSLastTime;					// 最後にFPSを計測した時刻

	// マネージャの生成
	CManager *pManager = nullptr;

	// マネージャの生成
	if (pManager == nullptr)
	{// nullptrだったら

		// メモリ確保
		pManager = CManager::Create();
	}

	//if (LoadManager != nullptr)
	//{
	//	LoadManager->Uninit();
	//	delete LoadManager;
	//	LoadManager = nullptr;
	//}

	//// ロードマネージャの生成
	//LoadManager = CLoadManager::Create();

	if (pManager != nullptr)
	{// メモリの確保が出来ていたら

		// 初期化処理
		if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
		{// 初期化処理が失敗した場合

			return -1;
		}
	}

	g_nCountFPS = 0;

	// 分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;				// 初期化する
	dwExecLastTime = timeGetTime();	// 現在時刻を取得(保存)

	// ウインドウの表示
	ShowWindow(hWnd, nCmbShow);		// ウインドウの表示状態を設定
	UpdateWindow(hWnd);				// クライアント領域を更新

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();


	// メッセージループ
	while(1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{// Windowの処理
			if (msg.message == WM_QUIT)
			{// WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				// メッセージの設定
				TranslateMessage(&msg);		// 仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);		// ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{// DirectXの処理

			dwCurrentTime = timeGetTime();	// 現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;		// FPSを測定した時刻を保存
				dwFrameCount = 0;					// フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60分の1秒経過

				// 処理開始の時刻[現在時刻]を保存
				dwExecLastTime = dwCurrentTime;

				if (pManager != nullptr)
				{// メモリの確保が出来ていたら

					// 更新処理
					pManager->Update();

					// 描画処理
					pManager->Draw();
				}
				

				// フレームカウントを加算
				dwFrameCount++;
			}
		}
	}

	if (pManager != nullptr)
	{// メモリの確保が出来ていたら

		// 終了処理
		pManager->Uninit();

		// メモリの開放
		delete pManager;
		pManager = nullptr;
	}

	/*if (LoadManager != nullptr)
	{
		LoadManager->Uninit();
		delete LoadManager;
		LoadManager = nullptr;
	}*/


	// 分解能を戻す
	timeEndPeriod(1);

	// ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
		
	return (int)msg.wParam;
}

//==========================================================================
// ウインドウプロシージャ
//==========================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;	// 返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY:				// ウインドウ破棄のメッセージ
		// WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:				// キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:				// ESCキー入力

			// メッセージボックスを表示
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				// ウインドウを破棄する(VK_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	case WM_CLOSE:				// バツ閉じ
		// メッセージボックスを表示
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			// ウインドウを破棄する(VK_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;			// 0を返して終了を防ぐ
		}
		break;

	case WM_LBUTTONDOWN:		// マウス左クリック
		// 対象ウインドウにフォーカスを合わせる
		SetFocus(hWnd);
		break;

	case WM_TIMER:				// タイマー発行のメッセージ
		break;
	}

	/*if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;*/

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// 既定の処理を返す
}

CLoadManager* GetLoadManager()
{
	return LoadManager;
}

//==========================================================================
// FPS取得
//==========================================================================
int GetFPS()
{
	return g_nCountFPS;
}

HWND GetWnd() { return hWnd; }
