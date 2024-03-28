//=============================================================================
// 
//  ライト処理 [light.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"


//==========================================================================
// コンストラクタ
//==========================================================================
CLight::CLight()
{
	for (int nCntLight = 0; nCntLight < TYPE_MAX; nCntLight++)
	{
		// ライトの情報をクリアする
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));
	}
}

//==========================================================================
// デストラクタ
//==========================================================================
CLight::~CLight()
{

}

//==========================================================================
// ライトの初期化処理
//==========================================================================
HRESULT CLight::Init()
{
	//  デバイスの取得
	ID3D11Device* pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	MyLib::Vector3 vecDir;	// 設定用方向ベクトル

	for (int nCntLight = 0; nCntLight < TYPE_MAX; nCntLight++)
	{
		// ライトの情報をクリアする
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));

		switch (nCntLight)
		{
		case TYPE_DIRECTIONAL_01:
			// ライトの種類を設定
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ライトの拡散光を設定
			m_aLight[nCntLight].Diffuse.r = 1.0f;
			m_aLight[nCntLight].Diffuse.g = 1.0f;
			m_aLight[nCntLight].Diffuse.b = 1.0f;
			m_aLight[nCntLight].Diffuse.a = 1.0f;

			// ライトの方向を設定
			vecDir = MyLib::Vector3(0.22f, -0.87f, 0.44f);
			break;

		case TYPE_DIRECTIONAL_02:
			// ライトの種類を設定
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ライトの拡散光を設定
			m_aLight[nCntLight].Diffuse.r = 0.65f;
			m_aLight[nCntLight].Diffuse.g = 0.65f;
			m_aLight[nCntLight].Diffuse.b = 0.65f;
			m_aLight[nCntLight].Diffuse.a = 1.0f;

			// ライトの方向を設定
			vecDir = MyLib::Vector3(-0.18f, 0.88f, -0.44f);
			break;

		case TYPE_DIRECTIONAL_03:
			// ライトの種類を設定
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ライトの拡散光を設定
			m_aLight[nCntLight].Diffuse.r = 0.15f;
			m_aLight[nCntLight].Diffuse.g = 0.15f;
			m_aLight[nCntLight].Diffuse.b = 0.15f;
			m_aLight[nCntLight].Diffuse.a = 1.0f;

			// ライトの方向を設定
			vecDir = MyLib::Vector3(0.89f, -0.11f, 0.44f);
			break;

		case TYPE_SPOT_01:
			// ライトの種類をスポットライトに設定
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// スポットライトの拡散光を設定
			m_aLight[nCntLight].Diffuse.r = 0.6f;
			m_aLight[nCntLight].Diffuse.g = 0.6f;
			m_aLight[nCntLight].Diffuse.b = 0.6f;
			m_aLight[nCntLight].Diffuse.a = 1.0f;

			// スポットライトの方向を設定
			vecDir = MyLib::Vector3(0.0f, 0.0f, 0.0f);
			break;
		}

		// ベクトルを正規化する(1.0にする)
		vecDir = vecDir.Normal();
		m_aLight[nCntLight].Direction.x = vecDir.x;
		m_aLight[nCntLight].Direction.y = vecDir.y;
		m_aLight[nCntLight].Direction.z = vecDir.z;

		//// ライトを設定する
		//pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		//// ライトを有効にする
		//pDevice->LightEnable(nCntLight, TRUE);
	}

	return S_OK;
}

//==========================================================================
// ライトの終了処理
//==========================================================================
void CLight::Uninit()
{

}

//==========================================================================
// ライトの更新処理
//==========================================================================
void CLight::Update()
{

}

//==========================================================================
// スポットライトの向き更新
//==========================================================================
void CLight::UpdateSpotLightDirection(MyLib::Vector3 vec)
{
	////  デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//// スポットライトの方向を設定
	//MyLib::Vector3 vecDir = vec.Normal();
	//m_aLight[TYPE_SPOT_01].Direction.x = vecDir.x;
	//m_aLight[TYPE_SPOT_01].Direction.y = vecDir.y;
	//m_aLight[TYPE_SPOT_01].Direction.z = vecDir.z;

	//// ライトを設定する
	//pDevice->SetLight(TYPE_SPOT_01, &m_aLight[TYPE_SPOT_01]);

	//// ライトを有効にする
	//pDevice->LightEnable(TYPE_SPOT_01, TRUE);
}
