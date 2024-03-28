//=============================================================================
// 
//  レンダラーヘッダー [renderer.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_	// 二重インクルード防止

#include "main.h"

#include "vs_test.h"
#include "ps_test.h"

//==========================================================================
// クラス定義
//==========================================================================
// レンダラークラス定義
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);

	void Uninit();
	void Update();
	void Draw();

	ID3D11Device* GetDevice() { return m_pDevice; }
	ID3D11DeviceContext* GetDeviceContext() { return m_pImmediateContext; }
	ID3D11DepthStencilView* GetDepthStencilView() { return m_pDepthStencilView; }

private:

	ID3D11Device* m_pDevice;						// Direct3Dデバイス
	ID3D11DeviceContext* m_pImmediateContext;		// Direct3Dデバイスコンテキスト
	IDXGISwapChain* m_pSwapChain;					// スワップチェイン
	ID3D11RenderTargetView* m_pRenderTargetView;	// バックバッファーのRTビュー
	ID3D11DepthStencilView* m_pDepthStencilView;	// 深度ステンシルビュー


	// 2D用シェーダー
	ID3D11Texture2D* m_pDepthStencilTexture;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11InputLayout* m_pInputLayout;// 入力レイアウト
	ID3D11VertexShader* m_pVertexShader;// 頂点シェーダー
	ID3D11PixelShader* m_pPixelShader;// ピクセルシェーダー
	D3D11_VIEWPORT          m_Viewport;
};



#endif