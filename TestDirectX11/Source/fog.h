//=============================================================================
// 
// �t�H�O [fog.h]
// Author : ���n�Ή�
// 
//=============================================================================

#ifndef _FOG_H_
#define _FOG_H_		// ��d�C���N���[�h�h�~

#include "manager.h"
#include "renderer.h"

/**
	@brief	�t�H�O�̋@�\
*/
namespace MyFog
{
    // �萔�o�b�t�@�[�̒�`
    struct FogBuffer
    {
        DirectX::XMFLOAT4 fogColor; // �t�H�O�̐F
        float fogStart;             // �t�H�O�̊J�n����
        float fogRange;             // �t�H�O�̏I�������ƊJ�n�����̍�
    };

    extern MyLib::Color Color;
    extern float Start;
    extern float End;
    extern D3DFOGMODE Mode;
    extern bool bOnScreen;

    /**
    @brief	�t�H�O�̃p�����[�^��ݒ�
    @param	color	[in]	�t�H�O�̐F
    @param	start	[in]	�t�H�O�̊J�n����
    @param	end 	[in]	�t�H�O�̏I������
    @param	mode 	[in]	�t�H�O�̎��
    */
    inline void SetFogparam(const MyLib::Color& color, float start, float end, D3DFOGMODE mode)
    {
        Color = color;
        Start = start;
        End = end;
        Mode = mode;
    }

    /**
    @brief	�t�H�O�̃t���O�؂�ւ�
    @param	onscreen	[in]	�t�H�O�̃t���O
    */
    inline void ToggleFogFrag(bool onscreen)
    {
        bOnScreen = onscreen;
    }

    /**
    @brief	�t�H�O�̃t���O�؂�ւ�
    */
    inline void ToggleFogFrag()
    {
        bOnScreen = bOnScreen ? false : true;
    }

    /**
    @brief	�t�H�O��ݒ�
    @param	device	[in]	�g�p����Ă�f�o�C�X
    @param	color	[in]	�t�H�O�̐F
    @param	start	[in]	�t�H�O�̊J�n����
    @param	end 	[in]	�t�H�O�̏I������
    @param	mode 	[in]	�t�H�O�̎��
    */
    inline void SetFog()
    {
        CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();

        // �����_�[�X�e�[�g�I�u�W�F�N�g�̍쐬
        ID3D11Device* pDevice = pRenderer->GetDevice(); // �f�o�C�X�I�u�W�F�N�g�̎擾���K�v
        ID3D11DeviceContext* pContext = pRenderer->GetDeviceContext(); // �f�o�C�X�R���e�L�X�g�̎擾���K�v
        ID3D11RasterizerState* pRasterizerState;

        D3D11_RASTERIZER_DESC rasterizerDesc;
        ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));

        // ���𖳌��ɂ��邽�߂ɕK�v�Ȑݒ��ǉ�
        if (!bOnScreen)
        {
            rasterizerDesc.DepthClipEnable = FALSE; // �[�x�N���b�s���O�𖳌��ɂ���
            return;
        }

        rasterizerDesc.DepthClipEnable = FALSE; // �[�x�N���b�s���O��L���ɂ���



        // �萔�o�b�t�@�[�̍쐬
        ID3D11Buffer* pFogBuffer;
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = sizeof(FogBuffer);
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        pDevice->CreateBuffer(&bufferDesc, NULL, &pFogBuffer);

        // �t�H�O�̃p�����[�^�[��ݒ�
        FogBuffer fogBufferData;
        fogBufferData.fogColor.x = Color.r; // ���̐F
        fogBufferData.fogColor.y = Color.g; // ���̐F
        fogBufferData.fogColor.z = Color.b; // ���̐F
        fogBufferData.fogColor.w = Color.a; // ���̐F
        fogBufferData.fogStart = Start; // ���̊J�n����
        fogBufferData.fogRange = End; // ���̏I�������ƊJ�n�����̍�

        // �萔�o�b�t�@�[���V�F�[�_�[�ɑ��M
        pContext->UpdateSubresource(pFogBuffer, 0, NULL, &fogBufferData, 0, 0);
        pContext->VSSetConstantBuffers(1, 1, &pFogBuffer); // ���_�V�F�[�_�[�ɑ��M
        pContext->PSSetConstantBuffers(1, 1, &pFogBuffer); // �s�N�Z���V�F�[�_�[�ɑ��M


        // �����_�[�X�e�[�g�I�u�W�F�N�g�̍쐬
        pDevice->CreateRasterizerState(&rasterizerDesc, &pRasterizerState);

        // �����_�[�X�e�[�g�I�u�W�F�N�g�̐ݒ�
        pContext->RSSetState(pRasterizerState);

        // �����_�[�X�e�[�g�I�u�W�F�N�g�̉��
        pRasterizerState->Release();
    }

    /**
    @brief	�t�H�O�𖳌�
    */
    inline void DisableFog(LPDIRECT3DDEVICE9 device)
    {
        device->SetRenderState(D3DRS_FOGENABLE, FALSE);
    }
}

#endif