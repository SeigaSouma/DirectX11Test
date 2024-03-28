//=============================================================================
// 
// フォグ [fog.h]
// Author : 相馬靜雅
// 
//=============================================================================

#ifndef _FOG_H_
#define _FOG_H_		// 二重インクルード防止

#include "manager.h"
#include "renderer.h"

/**
	@brief	フォグの機能
*/
namespace MyFog
{
    // 定数バッファーの定義
    struct FogBuffer
    {
        DirectX::XMFLOAT4 fogColor; // フォグの色
        float fogStart;             // フォグの開始距離
        float fogRange;             // フォグの終了距離と開始距離の差
    };

    extern MyLib::Color Color;
    extern float Start;
    extern float End;
    extern D3DFOGMODE Mode;
    extern bool bOnScreen;

    /**
    @brief	フォグのパラメータを設定
    @param	color	[in]	フォグの色
    @param	start	[in]	フォグの開始距離
    @param	end 	[in]	フォグの終了距離
    @param	mode 	[in]	フォグの種類
    */
    inline void SetFogparam(const MyLib::Color& color, float start, float end, D3DFOGMODE mode)
    {
        Color = color;
        Start = start;
        End = end;
        Mode = mode;
    }

    /**
    @brief	フォグのフラグ切り替え
    @param	onscreen	[in]	フォグのフラグ
    */
    inline void ToggleFogFrag(bool onscreen)
    {
        bOnScreen = onscreen;
    }

    /**
    @brief	フォグのフラグ切り替え
    */
    inline void ToggleFogFrag()
    {
        bOnScreen = bOnScreen ? false : true;
    }

    /**
    @brief	フォグを設定
    @param	device	[in]	使用されてるデバイス
    @param	color	[in]	フォグの色
    @param	start	[in]	フォグの開始距離
    @param	end 	[in]	フォグの終了距離
    @param	mode 	[in]	フォグの種類
    */
    inline void SetFog()
    {
        CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();

        // レンダーステートオブジェクトの作成
        ID3D11Device* pDevice = pRenderer->GetDevice(); // デバイスオブジェクトの取得が必要
        ID3D11DeviceContext* pContext = pRenderer->GetDeviceContext(); // デバイスコンテキストの取得が必要
        ID3D11RasterizerState* pRasterizerState;

        D3D11_RASTERIZER_DESC rasterizerDesc;
        ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));

        // 霧を無効にするために必要な設定を追加
        if (!bOnScreen)
        {
            rasterizerDesc.DepthClipEnable = FALSE; // 深度クリッピングを無効にする
            return;
        }

        rasterizerDesc.DepthClipEnable = FALSE; // 深度クリッピングを有効にする



        // 定数バッファーの作成
        ID3D11Buffer* pFogBuffer;
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = sizeof(FogBuffer);
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        pDevice->CreateBuffer(&bufferDesc, NULL, &pFogBuffer);

        // フォグのパラメーターを設定
        FogBuffer fogBufferData;
        fogBufferData.fogColor.x = Color.r; // 霧の色
        fogBufferData.fogColor.y = Color.g; // 霧の色
        fogBufferData.fogColor.z = Color.b; // 霧の色
        fogBufferData.fogColor.w = Color.a; // 霧の色
        fogBufferData.fogStart = Start; // 霧の開始距離
        fogBufferData.fogRange = End; // 霧の終了距離と開始距離の差

        // 定数バッファーをシェーダーに送信
        pContext->UpdateSubresource(pFogBuffer, 0, NULL, &fogBufferData, 0, 0);
        pContext->VSSetConstantBuffers(1, 1, &pFogBuffer); // 頂点シェーダーに送信
        pContext->PSSetConstantBuffers(1, 1, &pFogBuffer); // ピクセルシェーダーに送信


        // レンダーステートオブジェクトの作成
        pDevice->CreateRasterizerState(&rasterizerDesc, &pRasterizerState);

        // レンダーステートオブジェクトの設定
        pContext->RSSetState(pRasterizerState);

        // レンダーステートオブジェクトの解放
        pRasterizerState->Release();
    }

    /**
    @brief	フォグを無効
    */
    inline void DisableFog(LPDIRECT3DDEVICE9 device)
    {
        device->SetRenderState(D3DRS_FOGENABLE, FALSE);
    }
}

#endif