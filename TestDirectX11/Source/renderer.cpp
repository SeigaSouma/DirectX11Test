//=============================================================================
// 
//  レンダラー処理 [renderer.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "debugproc.h"
#include "fog.h"

//==========================================================================
// コンストラクタ
//==========================================================================
CRenderer::CRenderer()
{
	
}

//==========================================================================
// デストラクタ
//==========================================================================
CRenderer::~CRenderer()
{

}

VERTEX g_VertexList[]{
		{ { -0.5f,  0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ {  0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
		{ {  0.5f,  0.5f, 0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } }
};

WORD g_IndexList[]{
		0, 1, 2,
		0, 3, 1,
};

D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	// DXGIファクトリーの作成
	IDXGIFactory* pDXGIFactory = nullptr;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pDXGIFactory));
	if (FAILED(hr))
	{
		// エラーハンドリング
		return hr;
	}

	// スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;														// バッファ数
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;										// ゲーム画面サイズ(幅)
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;									// ゲーム画面サイズ(高さ)
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;						// バッファの形式
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;								// リフレッシュレートの分子
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;								// リフレッシュレートの分母
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;						// バッファの使用方法
	swapChainDesc.OutputWindow = hWnd;													// ウィンドウハンドル
	swapChainDesc.SampleDesc.Count = 1;													// マルチサンプリングの数
	swapChainDesc.SampleDesc.Quality = 0;												// マルチサンプリングの品質
	swapChainDesc.Windowed = bWindow;													// ウィンドウモード
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;								// ダブルバッファの切り替え(映像信号に同期)
	swapChainDesc.Flags = 0;

	// Direct3Dデバイスとスワップチェーンの作成
	D3D_FEATURE_LEVEL featureLevel;
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
		D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, &featureLevel, &m_pImmediateContext);
	if (FAILED(hr))
	{
		// エラーハンドリング
		if (pDXGIFactory) pDXGIFactory->Release();
		return hr;
	}

	// バックバッファのレンダーターゲットビューの取得
	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
	{
		// エラーハンドリング
		if (pDXGIFactory) pDXGIFactory->Release();
		return hr;
	}

	// バックバッファからレンダーターゲットビューを作成
	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
	if (FAILED(hr))
	{
		// エラーハンドリング
		if (pDXGIFactory) pDXGIFactory->Release();
		if (pBackBuffer) pBackBuffer->Release();
		return hr;
	}

	// バックバッファの解放
	if (pBackBuffer) pBackBuffer->Release();

	// 深度ステンシルビューの作成
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = SCREEN_WIDTH;                // テクスチャの幅
	depthStencilDesc.Height = SCREEN_HEIGHT;              // テクスチャの高さ
	depthStencilDesc.MipLevels = 1;                       // ミップマップ レベル数
	depthStencilDesc.ArraySize = 1;                       // 配列のサイズ
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // フォーマット
	depthStencilDesc.SampleDesc.Count = 1;                // サンプルの数
	depthStencilDesc.SampleDesc.Quality = 0;              // サンプルの品質
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;         // テクスチャの使用方法
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // テクスチャのバインド フラグ
	depthStencilDesc.CPUAccessFlags = 0;                  // CPUアクセス フラグ
	depthStencilDesc.MiscFlags = 0;                       // ミスフラグ

	ID3D11Texture2D* pDepthStencilBuffer;
	hr = m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &pDepthStencilBuffer);
	if (FAILED(hr))
	{
		// エラーハンドリング
		if (pDXGIFactory) pDXGIFactory->Release();
		return hr;
	}

	// 深度ステンシルビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Format = depthStencilDesc.Format; // フォーマット
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // ビューの次元
	depthStencilViewDesc.Texture2D.MipSlice = 0;           // ミップ スライス

	hr = m_pDevice->CreateDepthStencilView(pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(hr))
	{
		// エラーハンドリング
		if (pDXGIFactory) pDXGIFactory->Release();
		if (pDepthStencilBuffer) pDepthStencilBuffer->Release();
		return hr;
	}

	// 深度ステンシルバッファの解放
	if (pDepthStencilBuffer) pDepthStencilBuffer->Release();

	// DXGIファクトリーの解放
	if (pDXGIFactory) pDXGIFactory->Release();




	// 頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(VERTEX) * 4;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = g_VertexList;
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;



	// インデックスバッファ作成
	D3D11_BUFFER_DESC ibDesc;
	ibDesc.ByteWidth = sizeof(WORD) * 6;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA irData;
	irData.pSysMem = g_IndexList;
	irData.SysMemPitch = 0;
	irData.SysMemSlicePitch = 0;

	hr = m_pDevice->CreateBuffer(&ibDesc, &irData, &m_pIndexBuffer);
	if (FAILED(hr))
		return hr;




	hr = m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
	if (FAILED(hr))
		return hr;




	// 頂点レイアウト作成
	hr = m_pDevice->CreateInputLayout(g_VertexDesc, ARRAYSIZE(g_VertexDesc),
		g_vs_main, sizeof(g_vs_main), &m_pInputLayout);
	if (FAILED(hr))
		return hr;

	// 頂点シェーダー生成
	hr = m_pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &m_pVertexShader);
	if (FAILED(hr))
		return hr;

	// ピクセルシェーダー生成
	hr = m_pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &m_pPixelShader);
	if (FAILED(hr))
		return hr;


	// ビューポート設定
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = (FLOAT)SCREEN_WIDTH;
	m_Viewport.Height = (FLOAT)SCREEN_HEIGHT;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;






	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CRenderer::Uninit()
{
	if (m_pImmediateContext) {
		m_pImmediateContext->ClearState();
	}

	if (nullptr != m_pRenderTargetView) {
		m_pRenderTargetView->Release();
		m_pRenderTargetView = nullptr;
	}
	if (nullptr != m_pSwapChain) {
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}
	if (nullptr != m_pImmediateContext) {
		m_pImmediateContext->Release();
		m_pImmediateContext = nullptr;
	}
	if (nullptr != m_pDevice) {
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}

//==========================================================================
// 更新処理
//==========================================================================
void CRenderer::Update()
{
	// 全ての更新
	CObject::UpdateAll();
}

//==========================================================================
// 描画処理
//==========================================================================
void CRenderer::Draw()
{
	static bool bDisp = true;




	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha

	/*UINT strides = sizeof(VERTEX);
	UINT offsets = 0;
	m_pImmediateContext->IASetInputLayout(m_pInputLayout);
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pImmediateContext->RSSetViewports(1, &m_Viewport);
	m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->Draw(4, 0);

	m_pSwapChain->Present(0, 0);*/



	UINT strides = sizeof(VERTEX);
	UINT offsets = 0;
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	m_pImmediateContext->IASetInputLayout(m_pInputLayout);
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pImmediateContext->RSSetViewports(1, &m_Viewport);
	m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	m_pImmediateContext->DrawIndexed(6, 0, 0);





	//m_pSwapChain->Present(0, 0);

	if (CManager::GetInstance()->IsLoadComplete())
	{
		// 全ての描画
		CObject::DrawAll();

		// カメラの設定
		//CManager::GetInstance()->GetCamera()->SetCamera();

		// デバッグ表示の描画処理
		CManager::GetInstance()->GetDebugProc()->Draw();

		// テキストの設定
		CDebugProc::SetText();

		//// ポーズ描画処理
		//if (bDisp)
		//{
		//	CManager::GetInstance()->GetPause()->Draw();
		//}

		//// 黒フレーム
		//CManager::GetInstance()->GetBlackFrame()->Draw();
	}
	else
		// ロードマネージャの更新
	{
		//GetLoadManager()->Draw();
	}

	//// 遷移なしフェード描画処理
	//CInstantFade* pfalsefade = CManager::GetInstance()->GetInstantFade();
	//if (pfalsefade != nullptr)
	//{
	//	pfalsefade->Draw();
	//}

	//// フェード描画処理
	//CFade* pfade = CManager::GetInstance()->GetFade();
	//if (pfade != nullptr)
	//{
	//	pfade->Draw();
	//}

	// ビューポートを元に戻す
	//m_pImmediateContext->RSSetViewports(numViewports, &viewportDef);


	// Imguiの描画
	//ImguiMgr::Draw();

	// レンダーターゲットと深度ステンシルビューを解除
	m_pImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);

	// レンダーステート、シェーダー、入力レイアウト、深度ステンシルステート、ブレンドステートを解除
	m_pImmediateContext->RSSetState(nullptr);
	m_pImmediateContext->PSSetShader(nullptr, nullptr, 0);
	m_pImmediateContext->VSSetShader(nullptr, nullptr, 0);
	m_pImmediateContext->IASetInputLayout(nullptr);
	m_pImmediateContext->OMSetDepthStencilState(nullptr, 0);
	m_pImmediateContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);

	// バックバッファとフロントバッファの入れ替え
	m_pSwapChain->Present(0, 0);
}
