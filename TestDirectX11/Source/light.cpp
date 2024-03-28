//=============================================================================
// 
//  ���C�g���� [light.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"


//==========================================================================
// �R���X�g���N�^
//==========================================================================
CLight::CLight()
{
	for (int nCntLight = 0; nCntLight < TYPE_MAX; nCntLight++)
	{
		// ���C�g�̏����N���A����
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));
	}
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CLight::~CLight()
{

}

//==========================================================================
// ���C�g�̏���������
//==========================================================================
HRESULT CLight::Init()
{
	//  �f�o�C�X�̎擾
	ID3D11Device* pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	MyLib::Vector3 vecDir;	// �ݒ�p�����x�N�g��

	for (int nCntLight = 0; nCntLight < TYPE_MAX; nCntLight++)
	{
		// ���C�g�̏����N���A����
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));

		switch (nCntLight)
		{
		case TYPE_DIRECTIONAL_01:
			// ���C�g�̎�ނ�ݒ�
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			m_aLight[nCntLight].Diffuse.r = 1.0f;
			m_aLight[nCntLight].Diffuse.g = 1.0f;
			m_aLight[nCntLight].Diffuse.b = 1.0f;
			m_aLight[nCntLight].Diffuse.a = 1.0f;

			// ���C�g�̕�����ݒ�
			vecDir = MyLib::Vector3(0.22f, -0.87f, 0.44f);
			break;

		case TYPE_DIRECTIONAL_02:
			// ���C�g�̎�ނ�ݒ�
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			m_aLight[nCntLight].Diffuse.r = 0.65f;
			m_aLight[nCntLight].Diffuse.g = 0.65f;
			m_aLight[nCntLight].Diffuse.b = 0.65f;
			m_aLight[nCntLight].Diffuse.a = 1.0f;

			// ���C�g�̕�����ݒ�
			vecDir = MyLib::Vector3(-0.18f, 0.88f, -0.44f);
			break;

		case TYPE_DIRECTIONAL_03:
			// ���C�g�̎�ނ�ݒ�
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			m_aLight[nCntLight].Diffuse.r = 0.15f;
			m_aLight[nCntLight].Diffuse.g = 0.15f;
			m_aLight[nCntLight].Diffuse.b = 0.15f;
			m_aLight[nCntLight].Diffuse.a = 1.0f;

			// ���C�g�̕�����ݒ�
			vecDir = MyLib::Vector3(0.89f, -0.11f, 0.44f);
			break;

		case TYPE_SPOT_01:
			// ���C�g�̎�ނ��X�|�b�g���C�g�ɐݒ�
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// �X�|�b�g���C�g�̊g�U����ݒ�
			m_aLight[nCntLight].Diffuse.r = 0.6f;
			m_aLight[nCntLight].Diffuse.g = 0.6f;
			m_aLight[nCntLight].Diffuse.b = 0.6f;
			m_aLight[nCntLight].Diffuse.a = 1.0f;

			// �X�|�b�g���C�g�̕�����ݒ�
			vecDir = MyLib::Vector3(0.0f, 0.0f, 0.0f);
			break;
		}

		// �x�N�g���𐳋K������(1.0�ɂ���)
		vecDir = vecDir.Normal();
		m_aLight[nCntLight].Direction.x = vecDir.x;
		m_aLight[nCntLight].Direction.y = vecDir.y;
		m_aLight[nCntLight].Direction.z = vecDir.z;

		//// ���C�g��ݒ肷��
		//pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		//// ���C�g��L���ɂ���
		//pDevice->LightEnable(nCntLight, TRUE);
	}

	return S_OK;
}

//==========================================================================
// ���C�g�̏I������
//==========================================================================
void CLight::Uninit()
{

}

//==========================================================================
// ���C�g�̍X�V����
//==========================================================================
void CLight::Update()
{

}

//==========================================================================
// �X�|�b�g���C�g�̌����X�V
//==========================================================================
void CLight::UpdateSpotLightDirection(MyLib::Vector3 vec)
{
	////  �f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//// �X�|�b�g���C�g�̕�����ݒ�
	//MyLib::Vector3 vecDir = vec.Normal();
	//m_aLight[TYPE_SPOT_01].Direction.x = vecDir.x;
	//m_aLight[TYPE_SPOT_01].Direction.y = vecDir.y;
	//m_aLight[TYPE_SPOT_01].Direction.z = vecDir.z;

	//// ���C�g��ݒ肷��
	//pDevice->SetLight(TYPE_SPOT_01, &m_aLight[TYPE_SPOT_01]);

	//// ���C�g��L���ɂ���
	//pDevice->LightEnable(TYPE_SPOT_01, TRUE);
}