//=============================================================================
// 
//  �����_���[���� [renderer.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "debugproc.h"
#include "fog.h"

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CRenderer::CRenderer()
{
	
}

//==========================================================================
// �f�X�g���N�^
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
	// DXGI�t�@�N�g���[�̍쐬
	IDXGIFactory* pDXGIFactory = nullptr;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pDXGIFactory));
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		return hr;
	}

	// �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;														// �o�b�t�@��
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;										// �Q�[����ʃT�C�Y(��)
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;									// �Q�[����ʃT�C�Y(����)
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;						// �o�b�t�@�̌`��
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;								// ���t���b�V�����[�g�̕��q
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;								// ���t���b�V�����[�g�̕���
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;						// �o�b�t�@�̎g�p���@
	swapChainDesc.OutputWindow = hWnd;													// �E�B���h�E�n���h��
	swapChainDesc.SampleDesc.Count = 1;													// �}���`�T���v�����O�̐�
	swapChainDesc.SampleDesc.Quality = 0;												// �}���`�T���v�����O�̕i��
	swapChainDesc.Windowed = bWindow;													// �E�B���h�E���[�h
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;								// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	swapChainDesc.Flags = 0;

	// Direct3D�f�o�C�X�ƃX���b�v�`�F�[���̍쐬
	D3D_FEATURE_LEVEL featureLevel;
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
		D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, &featureLevel, &m_pImmediateContext);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		if (pDXGIFactory) pDXGIFactory->Release();
		return hr;
	}

	// �o�b�N�o�b�t�@�̃����_�[�^�[�Q�b�g�r���[�̎擾
	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		if (pDXGIFactory) pDXGIFactory->Release();
		return hr;
	}

	// �o�b�N�o�b�t�@���烌���_�[�^�[�Q�b�g�r���[���쐬
	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		if (pDXGIFactory) pDXGIFactory->Release();
		if (pBackBuffer) pBackBuffer->Release();
		return hr;
	}

	// �o�b�N�o�b�t�@�̉��
	if (pBackBuffer) pBackBuffer->Release();

	// �[�x�X�e���V���r���[�̍쐬
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = SCREEN_WIDTH;                // �e�N�X�`���̕�
	depthStencilDesc.Height = SCREEN_HEIGHT;              // �e�N�X�`���̍���
	depthStencilDesc.MipLevels = 1;                       // �~�b�v�}�b�v ���x����
	depthStencilDesc.ArraySize = 1;                       // �z��̃T�C�Y
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // �t�H�[�}�b�g
	depthStencilDesc.SampleDesc.Count = 1;                // �T���v���̐�
	depthStencilDesc.SampleDesc.Quality = 0;              // �T���v���̕i��
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;         // �e�N�X�`���̎g�p���@
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // �e�N�X�`���̃o�C���h �t���O
	depthStencilDesc.CPUAccessFlags = 0;                  // CPU�A�N�Z�X �t���O
	depthStencilDesc.MiscFlags = 0;                       // �~�X�t���O

	ID3D11Texture2D* pDepthStencilBuffer;
	hr = m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &pDepthStencilBuffer);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		if (pDXGIFactory) pDXGIFactory->Release();
		return hr;
	}

	// �[�x�X�e���V���r���[�̍쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Format = depthStencilDesc.Format; // �t�H�[�}�b�g
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // �r���[�̎���
	depthStencilViewDesc.Texture2D.MipSlice = 0;           // �~�b�v �X���C�X

	hr = m_pDevice->CreateDepthStencilView(pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		if (pDXGIFactory) pDXGIFactory->Release();
		if (pDepthStencilBuffer) pDepthStencilBuffer->Release();
		return hr;
	}

	// �[�x�X�e���V���o�b�t�@�̉��
	if (pDepthStencilBuffer) pDepthStencilBuffer->Release();

	// DXGI�t�@�N�g���[�̉��
	if (pDXGIFactory) pDXGIFactory->Release();




	// ���_�o�b�t�@�쐬
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



	// �C���f�b�N�X�o�b�t�@�쐬
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




	// ���_���C�A�E�g�쐬
	hr = m_pDevice->CreateInputLayout(g_VertexDesc, ARRAYSIZE(g_VertexDesc),
		g_vs_main, sizeof(g_vs_main), &m_pInputLayout);
	if (FAILED(hr))
		return hr;

	// ���_�V�F�[�_�[����
	hr = m_pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &m_pVertexShader);
	if (FAILED(hr))
		return hr;

	// �s�N�Z���V�F�[�_�[����
	hr = m_pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &m_pPixelShader);
	if (FAILED(hr))
		return hr;


	// �r���[�|�[�g�ݒ�
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = (FLOAT)SCREEN_WIDTH;
	m_Viewport.Height = (FLOAT)SCREEN_HEIGHT;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;






	return S_OK;
}

//==========================================================================
// �I������
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
// �X�V����
//==========================================================================
void CRenderer::Update()
{
	// �S�Ă̍X�V
	CObject::UpdateAll();
}

//==========================================================================
// �`�揈��
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
		// �S�Ă̕`��
		CObject::DrawAll();

		// �J�����̐ݒ�
		//CManager::GetInstance()->GetCamera()->SetCamera();

		// �f�o�b�O�\���̕`�揈��
		CManager::GetInstance()->GetDebugProc()->Draw();

		// �e�L�X�g�̐ݒ�
		CDebugProc::SetText();

		//// �|�[�Y�`�揈��
		//if (bDisp)
		//{
		//	CManager::GetInstance()->GetPause()->Draw();
		//}

		//// ���t���[��
		//CManager::GetInstance()->GetBlackFrame()->Draw();
	}
	else
		// ���[�h�}�l�[�W���̍X�V
	{
		//GetLoadManager()->Draw();
	}

	//// �J�ڂȂ��t�F�[�h�`�揈��
	//CInstantFade* pfalsefade = CManager::GetInstance()->GetInstantFade();
	//if (pfalsefade != nullptr)
	//{
	//	pfalsefade->Draw();
	//}

	//// �t�F�[�h�`�揈��
	//CFade* pfade = CManager::GetInstance()->GetFade();
	//if (pfade != nullptr)
	//{
	//	pfade->Draw();
	//}

	// �r���[�|�[�g�����ɖ߂�
	//m_pImmediateContext->RSSetViewports(numViewports, &viewportDef);


	// Imgui�̕`��
	//ImguiMgr::Draw();

	// �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[������
	m_pImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);

	// �����_�[�X�e�[�g�A�V�F�[�_�[�A���̓��C�A�E�g�A�[�x�X�e���V���X�e�[�g�A�u�����h�X�e�[�g������
	m_pImmediateContext->RSSetState(nullptr);
	m_pImmediateContext->PSSetShader(nullptr, nullptr, 0);
	m_pImmediateContext->VSSetShader(nullptr, nullptr, 0);
	m_pImmediateContext->IASetInputLayout(nullptr);
	m_pImmediateContext->OMSetDepthStencilState(nullptr, 0);
	m_pImmediateContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pSwapChain->Present(0, 0);
}
