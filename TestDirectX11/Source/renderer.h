//=============================================================================
// 
//  �����_���[�w�b�_�[ [renderer.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_	// ��d�C���N���[�h�h�~

#include "main.h"

#include "vs_test.h"
#include "ps_test.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �����_���[�N���X��`
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

	ID3D11Device* m_pDevice;						// Direct3D�f�o�C�X
	ID3D11DeviceContext* m_pImmediateContext;		// Direct3D�f�o�C�X�R���e�L�X�g
	IDXGISwapChain* m_pSwapChain;					// �X���b�v�`�F�C��
	ID3D11RenderTargetView* m_pRenderTargetView;	// �o�b�N�o�b�t�@�[��RT�r���[
	ID3D11DepthStencilView* m_pDepthStencilView;	// �[�x�X�e���V���r���[


	// 2D�p�V�F�[�_�[
	ID3D11Texture2D* m_pDepthStencilTexture;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11InputLayout* m_pInputLayout;// ���̓��C�A�E�g
	ID3D11VertexShader* m_pVertexShader;// ���_�V�F�[�_�[
	ID3D11PixelShader* m_pPixelShader;// �s�N�Z���V�F�[�_�[
	D3D11_VIEWPORT          m_Viewport;
};



#endif