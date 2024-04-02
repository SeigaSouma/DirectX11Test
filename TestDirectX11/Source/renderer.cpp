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
#include "input.h"
#include "input_mouse.h"
#include "WICTextureLoader11.cpp"
#include "calculation.h"

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

#if 0
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

#else

VERTEX g_VertexList[]{
	{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, {0.0f, 0.0f} },
	{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, {1.0f, 0.0f} },
	{ { -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, {0.0f, 1.0f} },
	{ {  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, {1.0f, 1.0f} },

	{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, {0.0f, 0.0f} },
	{ { -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, {1.0f, 0.0f} },
	{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, {0.0f, 1.0f} },
	{ {  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, {1.0f, 1.0f} },

	{ { -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },
	{ { -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, {1.0f, 0.0f} },
	{ { -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, {0.0f, 1.0f} },
	{ { -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, {1.0f, 1.0f} },

	{ {  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },
	{ {  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, {1.0f, 0.0f} },
	{ {  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, {0.0f, 1.0f} },
	{ {  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, {1.0f, 1.0f} },

	{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, {0.0f, 0.0f} },
	{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, {1.0f, 0.0f} },
	{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, {0.0f, 1.0f} },
	{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, {1.0f, 1.0f} },

	{ { -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, {0.0f, 0.0f} },
	{ { -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, {1.0f, 0.0f} },
	{ {  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, {0.0f, 1.0f} },
	{ {  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, {1.0f, 1.0f} },
};

WORD g_IndexList[]{
	 0,  1,  2,     3,  2,  1,
	 4,  5,  6,     7,  6,  5,
	 8,  9, 10,    11, 10,  9,
	12, 13, 14,    15, 14, 13,
	16, 17, 18,    19, 18, 17,
	20, 21, 22,    23, 22, 21,
};

int SEGMENT = 36;


struct ConstantBuffer {

#if 1
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
	XMFLOAT4   light;
#else
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
	DirectX::XMVECTOR light;
#endif
};

#endif

//D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{
//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};

D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

struct ConstantMatrixBuffer 
{
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

struct ConstantLight 
{
	XMFLOAT4 pos;				// 座標(x,y,z)
	XMFLOAT4 diffuse;			// 拡散(r,g,b)
	XMFLOAT4 specular;			// 反射(r,g,b)
	XMFLOAT4 attenuate;			// 減衰(a,b,c)
};

struct ConstantMaterial 
{
	XMFLOAT4 ambient;			// 環境(r,g,b)
	XMFLOAT4 diffuse;			// 拡散(r,g,b)
	XMFLOAT4 specular;			// 反射(r,g,b,光沢度係数)
};

struct ConstantLightBuffer 
{
	XMFLOAT4         eyePos;	// 視点座標
	XMFLOAT4         ambient;	// 環境光(r,g,b)
	ConstantLight    pntLight;	// 点光源
	ConstantMaterial material;	// 物体の質感
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

	hr = m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &m_pDepthStencilTexture);
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

	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &depthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(hr))
	{
		// エラーハンドリング
		if (pDXGIFactory) pDXGIFactory->Release();
		if (m_pDepthStencilTexture) m_pDepthStencilTexture->Release();
		return hr;
	}

	// 深度ステンシルバッファの解放
	if (m_pDepthStencilTexture) m_pDepthStencilTexture->Release();

	// DXGIファクトリーの解放
	if (pDXGIFactory) pDXGIFactory->Release();



#if 0
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

	hr = m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
	if (FAILED(hr))
		return hr;


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
#else

	// 頂点バッファ作成
	D3D11_BUFFER_DESC vbDesc;
	vbDesc.ByteWidth = sizeof(VERTEX) * 24;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.MiscFlags = 0;
	vbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vrData;
	vrData.pSysMem = g_VertexList;
	vrData.SysMemPitch = 0;
	vrData.SysMemSlicePitch = 0;

	hr = m_pDevice->CreateBuffer(&vbDesc, &vrData, &m_pVertexBuffer);
	if (FAILED(hr))
		return hr;

	for (int i = 0; i < ARRAYSIZE(g_VertexList); ++i)
	{
		g_VertexList[i].pos[0] += 2.0f;
	}

	// バッファにデータを再度コピーする
	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, 0, nullptr, g_VertexList, 0, 0);


	// インデックスバッファ作成
	D3D11_BUFFER_DESC ibDesc;
	ibDesc.ByteWidth = sizeof(WORD) * 6 * 6;
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


	// 定数バッファ作成
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstantBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	hr = m_pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantBuffer);
	if (FAILED(hr)) return hr;


	cbDesc.ByteWidth = sizeof(ConstantBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	hr = m_pDevice->CreateBuffer(&cbDesc, NULL, &m_pMatrixBuffer);
	if (FAILED(hr)) return hr;


	// テクスチャ読み込み
	const wchar_t* texaaa = L"data/TEXTURE/tutorial.png";
	hr = CreateWICTextureFromFile(m_pDevice, texaaa, &m_pTexture, &m_pTextureView);
	if (FAILED(hr))
		return hr;

	D3D11_SAMPLER_DESC smpDesc;
	::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = m_pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
	if (FAILED(hr))
		return hr;

#endif


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


#if 0
	UINT strides = sizeof(VERTEX);
	UINT offsets = 0;

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pImmediateContext->RSSetViewports(1, &m_Viewport);
	m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// インデックスで描画
	m_pImmediateContext->DrawIndexed(6, 0, 0);

#else

	// 定数バッファへ視点情報セット
	XMMATRIX worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);



	//------------------------------------------------------------
	// 初期設定
	//------------------------------------------------------------
	static FLOAT fTheta = 0.0f;	// カメラ横方向角度
	static FLOAT fDelta = -0.25f;	// カメラ縦方向角度
	static FLOAT fDistance = 5.0f;		// カメラ位置から焦点までの距離
	static FLOAT MOVE = 0.025f;		// カメラ位置から焦点までの距離
	static FLOAT fCameraX = 0.0f;	// カメラの位置X座標
	static FLOAT fCameraY = 0.0f;	// カメラの位置Y座標
	static FLOAT fCameraZ = 0.0f;	// カメラの位置Z座標
	static MyLib::Vector3 cameraPos = 0.0f;	// カメラの位置Z座標

	DIMOUSESTATE2 aa;

	//------------------------------------------------------------
	// キー入力関係
	//------------------------------------------------------------
	// マウス取得
	CInputMouse* pInputMouse = CInputMouse::GetInstance();

	// マウス右クリック
	if (pInputMouse->GetPress(CInputMouse::BUTTON_LEFT) &&
		pInputMouse->GetPress(CInputMouse::BUTTON_RIGHT))
	{// 左右同時押し

		MyLib::Vector3 mouseMove = pInputMouse->GetMouseMove();

		cameraPos.x +=
			(mouseMove.x * sinf(-XM_PI * 0.5f + fTheta) * MOVE) -
			(mouseMove.y * cosf(-XM_PI * 0.5f + fTheta) * MOVE);

		cameraPos.z +=
			(mouseMove.x * cosf(-XM_PI * 0.5f + fTheta) * MOVE) +
			(mouseMove.y * sinf(-XM_PI * 0.5f + fTheta) * MOVE);
	}
	else if (pInputMouse->GetPress(CInputMouse::BUTTON_LEFT))
	{
		MyLib::Vector3 mouseMove = pInputMouse->GetMouseMove();

		fTheta += mouseMove.x * 0.025f;
		fDelta += mouseMove.y * 0.025f;
	}

#define MIN_ROT		(-XM_PI * 0.49f)	// カメラ固定用
#define MAX_ROT		(XM_PI * 0.49f)	// カメラ固定用

	// 値の正規化
	UtilFunc::Transformation::RotNormalize(fTheta);
	UtilFunc::Transformation::ValueNormalize(fDelta, MAX_ROT, MIN_ROT);

	// マウスホイールで距離調整
	fDistance += pInputMouse->GetMouseMove().z * (MOVE * 0.3f);

	//カメラ位置決定
	fCameraX = cameraPos.x + cosf(fDelta) * sinf(fTheta) * -fDistance;
	fCameraY = cameraPos.y + sinf(fDelta) * -fDistance;
	fCameraZ = cameraPos.z + cosf(fDelta) * cosf(fTheta) * -fDistance;



	XMVECTOR eye = XMVectorSet(fCameraX, fCameraY, fCameraZ, 0.0f);	// 視点
	XMVECTOR focus = XMVectorSet(cameraPos.x, cameraPos.y, cameraPos.z, 0.0f);			// 注視点
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(eye, focus, up);


	float    fov = XMConvertToRadians(45.0f);
	float    aspect = m_Viewport.Width / m_Viewport.Height;
	float    nearZ = 0.1f;
	float    farZ = 100.0f;
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

	XMVECTOR lightPosition = XMVectorSet(-9.5f, 9.5f, -1.0f, 0.0f);
	XMVECTOR lightAmbient = XMVectorSet(0.6f, 0.6f, 0.6f, 0.0f);
	XMVECTOR lightDiffuse = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR lightSpecular = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR lightAttenuate = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR materialAmbient = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR materialDiffuse = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR materialSpecular = XMVectorSet(0.5f, 0.5f, 0.5f, 50.0f);


	ConstantMatrixBuffer cmb;
	XMStoreFloat4x4(&cmb.world, XMMatrixTranspose(worldMatrix));
	XMStoreFloat4x4(&cmb.view, XMMatrixTranspose(viewMatrix));
	XMStoreFloat4x4(&cmb.projection, XMMatrixTranspose(projMatrix));
	ConstantLightBuffer clb;
	XMStoreFloat4(&clb.eyePos, eye);
	XMStoreFloat4(&clb.ambient, lightAmbient);
	XMStoreFloat4(&clb.pntLight.pos, lightPosition);
	XMStoreFloat4(&clb.pntLight.diffuse, lightDiffuse);
	XMStoreFloat4(&clb.pntLight.specular, lightSpecular);
	XMStoreFloat4(&clb.pntLight.attenuate, lightAttenuate);
	XMStoreFloat4(&clb.material.ambient, materialAmbient);
	XMStoreFloat4(&clb.material.diffuse, materialDiffuse);
	XMStoreFloat4(&clb.material.specular, materialSpecular);
	m_pImmediateContext->UpdateSubresource(m_pMatrixBuffer, 0, NULL, &cmb, 0, 0);
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &clb, 0, 0);


	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha

	UINT strides = sizeof(VERTEX);
	UINT offsets = 0;
	m_pImmediateContext->IASetInputLayout(m_pInputLayout);
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pMatrixBuffer);
	m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pImmediateContext->RSSetViewports(1, &m_Viewport);
	m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);
	m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTextureView);
	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler);
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->DrawIndexed(36, 0, 0);

	////------------------------------------------------------------
	//// 文字操作
	////------------------------------------------------------------
	////カメラ角度表示用
	//WCHAR wcText2[256] = { 0 };
	//swprintf(wcText2, 256, L"fTheta=%f, fDelta=%f", fTheta, fDelta);

	////カメラ位置表示用
	//WCHAR wcText3[256] = { 0 };
	//swprintf(wcText3, 256, L"fCameraX=%f, fCameraY=%f, fCameraZ=%f", fCameraX, fCameraY, fCameraZ);

	////------------------------------------------------------------
	//// 2D描画
	////------------------------------------------------------------
	//m_pImmediateContext->BeginDraw();
	//m_pImmediateContext->DrawText(wcText1, ARRAYSIZE(wcText1) - 1, m_DWriteTextFormat.Get(), D2D1::RectF(0, 0, 800, 20), m_D2DSolidBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);//m_DWriteTextFormatではなくm_DWriteTextFormat.Get()
	//m_pImmediateContext->DrawText(wcText2, ARRAYSIZE(wcText2) - 1, m_DWriteTextFormat.Get(), D2D1::RectF(0, 20, 800, 40), m_D2DSolidBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);//m_DWriteTextFormatではなくm_DWriteTextFormat.Get()
	//m_pImmediateContext->DrawText(wcText3, ARRAYSIZE(wcText3) - 1, m_DWriteTextFormat.Get(), D2D1::RectF(0, 40, 800, 60), m_D2DSolidBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);//m_DWriteTextFormatではなくm_DWriteTextFormat.Get()
	//m_pImmediateContext->EndDraw();

#endif

	if (CManager::GetInstance()->IsLoadComplete())
	{
		// 全ての描画
		CObject::DrawAll();

		// デバッグ表示の描画処理
		CManager::GetInstance()->GetDebugProc()->Draw();

		// テキストの設定
		CDebugProc::SetText();
	}
	else
		// ロードマネージャの更新
	{
		//GetLoadManager()->Draw();
	}


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
