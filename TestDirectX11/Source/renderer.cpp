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
#include "input.h"
#include "input_mouse.h"
#include "WICTextureLoader11.cpp"
#include "calculation.h"

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
	XMFLOAT4 pos;				// ���W(x,y,z)
	XMFLOAT4 diffuse;			// �g�U(r,g,b)
	XMFLOAT4 specular;			// ����(r,g,b)
	XMFLOAT4 attenuate;			// ����(a,b,c)
};

struct ConstantMaterial 
{
	XMFLOAT4 ambient;			// ��(r,g,b)
	XMFLOAT4 diffuse;			// �g�U(r,g,b)
	XMFLOAT4 specular;			// ����(r,g,b,����x�W��)
};

struct ConstantLightBuffer 
{
	XMFLOAT4         eyePos;	// ���_���W
	XMFLOAT4         ambient;	// ����(r,g,b)
	ConstantLight    pntLight;	// �_����
	ConstantMaterial material;	// ���̂̎���
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

	hr = m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &m_pDepthStencilTexture);
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

	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &depthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		if (pDXGIFactory) pDXGIFactory->Release();
		if (m_pDepthStencilTexture) m_pDepthStencilTexture->Release();
		return hr;
	}

	// �[�x�X�e���V���o�b�t�@�̉��
	if (m_pDepthStencilTexture) m_pDepthStencilTexture->Release();

	// DXGI�t�@�N�g���[�̉��
	if (pDXGIFactory) pDXGIFactory->Release();



#if 0
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

	hr = m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
	if (FAILED(hr))
		return hr;


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
#else

	// ���_�o�b�t�@�쐬
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

	// �o�b�t�@�Ƀf�[�^���ēx�R�s�[����
	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, 0, nullptr, g_VertexList, 0, 0);


	// �C���f�b�N�X�o�b�t�@�쐬
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


	// �萔�o�b�t�@�쐬
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


	// �e�N�X�`���ǂݍ���
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

	// �C���f�b�N�X�ŕ`��
	m_pImmediateContext->DrawIndexed(6, 0, 0);

#else

	// �萔�o�b�t�@�֎��_���Z�b�g
	XMMATRIX worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);



	//------------------------------------------------------------
	// �����ݒ�
	//------------------------------------------------------------
	static FLOAT fTheta = 0.0f;	// �J�����������p�x
	static FLOAT fDelta = -0.25f;	// �J�����c�����p�x
	static FLOAT fDistance = 5.0f;		// �J�����ʒu����œ_�܂ł̋���
	static FLOAT MOVE = 0.025f;		// �J�����ʒu����œ_�܂ł̋���
	static FLOAT fCameraX = 0.0f;	// �J�����̈ʒuX���W
	static FLOAT fCameraY = 0.0f;	// �J�����̈ʒuY���W
	static FLOAT fCameraZ = 0.0f;	// �J�����̈ʒuZ���W
	static MyLib::Vector3 cameraPos = 0.0f;	// �J�����̈ʒuZ���W

	DIMOUSESTATE2 aa;

	//------------------------------------------------------------
	// �L�[���͊֌W
	//------------------------------------------------------------
	// �}�E�X�擾
	CInputMouse* pInputMouse = CInputMouse::GetInstance();

	// �}�E�X�E�N���b�N
	if (pInputMouse->GetPress(CInputMouse::BUTTON_LEFT) &&
		pInputMouse->GetPress(CInputMouse::BUTTON_RIGHT))
	{// ���E��������

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

#define MIN_ROT		(-XM_PI * 0.49f)	// �J�����Œ�p
#define MAX_ROT		(XM_PI * 0.49f)	// �J�����Œ�p

	// �l�̐��K��
	UtilFunc::Transformation::RotNormalize(fTheta);
	UtilFunc::Transformation::ValueNormalize(fDelta, MAX_ROT, MIN_ROT);

	// �}�E�X�z�C�[���ŋ�������
	fDistance += pInputMouse->GetMouseMove().z * (MOVE * 0.3f);

	//�J�����ʒu����
	fCameraX = cameraPos.x + cosf(fDelta) * sinf(fTheta) * -fDistance;
	fCameraY = cameraPos.y + sinf(fDelta) * -fDistance;
	fCameraZ = cameraPos.z + cosf(fDelta) * cosf(fTheta) * -fDistance;



	XMVECTOR eye = XMVectorSet(fCameraX, fCameraY, fCameraZ, 0.0f);	// ���_
	XMVECTOR focus = XMVectorSet(cameraPos.x, cameraPos.y, cameraPos.z, 0.0f);			// �����_
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
	//// ��������
	////------------------------------------------------------------
	////�J�����p�x�\���p
	//WCHAR wcText2[256] = { 0 };
	//swprintf(wcText2, 256, L"fTheta=%f, fDelta=%f", fTheta, fDelta);

	////�J�����ʒu�\���p
	//WCHAR wcText3[256] = { 0 };
	//swprintf(wcText3, 256, L"fCameraX=%f, fCameraY=%f, fCameraZ=%f", fCameraX, fCameraY, fCameraZ);

	////------------------------------------------------------------
	//// 2D�`��
	////------------------------------------------------------------
	//m_pImmediateContext->BeginDraw();
	//m_pImmediateContext->DrawText(wcText1, ARRAYSIZE(wcText1) - 1, m_DWriteTextFormat.Get(), D2D1::RectF(0, 0, 800, 20), m_D2DSolidBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);//m_DWriteTextFormat�ł͂Ȃ�m_DWriteTextFormat.Get()
	//m_pImmediateContext->DrawText(wcText2, ARRAYSIZE(wcText2) - 1, m_DWriteTextFormat.Get(), D2D1::RectF(0, 20, 800, 40), m_D2DSolidBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);//m_DWriteTextFormat�ł͂Ȃ�m_DWriteTextFormat.Get()
	//m_pImmediateContext->DrawText(wcText3, ARRAYSIZE(wcText3) - 1, m_DWriteTextFormat.Get(), D2D1::RectF(0, 40, 800, 60), m_D2DSolidBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);//m_DWriteTextFormat�ł͂Ȃ�m_DWriteTextFormat.Get()
	//m_pImmediateContext->EndDraw();

#endif

	if (CManager::GetInstance()->IsLoadComplete())
	{
		// �S�Ă̕`��
		CObject::DrawAll();

		// �f�o�b�O�\���̕`�揈��
		CManager::GetInstance()->GetDebugProc()->Draw();

		// �e�L�X�g�̐ݒ�
		CDebugProc::SetText();
	}
	else
		// ���[�h�}�l�[�W���̍X�V
	{
		//GetLoadManager()->Draw();
	}


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
