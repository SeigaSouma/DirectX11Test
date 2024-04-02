//=============================================================================
//
// ���͏��� [input.cpp]
// Author : ���n�Ή�
//
//=============================================================================
#include "input.h"
#include "debugproc.h"
#include "manager.h"
#include "calculation.h"

#include "input_mouse.h"
#include "input_keyboard.h"
#include "input_gamepad.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
LPDIRECTINPUT8 CInput::m_pInput = nullptr;			// DirectInput�I�u�W�F�N�g�ւ̃|�C���^

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CInput::CInput()
{
	m_pMouse = nullptr;
	m_pKeyboard = nullptr;
	m_pGamepad = nullptr;
	m_pDevice = nullptr;
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CInput::~CInput()
{

}

//==========================================================================
// ��������
//==========================================================================
CInput* CInput::Create(HINSTANCE hInstance, HWND hWnd)
{
	CInput* pInput = nullptr;

	pInput = DEBUG_NEW CInput;
	if (pInput == nullptr) {
		return nullptr;
	}

	// �}�E�X
	pInput->m_pMouse = CInputMouse::Create(hInstance, hWnd);
	if (pInput->m_pMouse == nullptr) {
		return nullptr;
	}

	// �L�[�{�[�h
	pInput->m_pKeyboard = CInputKeyboard::Create(hInstance, hWnd);
	if (pInput->m_pKeyboard == nullptr) {
		return nullptr;
	}

	// �Q�[���p�b�h
	pInput->m_pGamepad = CInputGamepad::Create(hInstance, hWnd);
	if (pInput->m_pGamepad == nullptr) {
		return nullptr;
	}

	return pInput;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	if (m_pInput == nullptr)
	{// �܂��������Ă��Ȃ�������

		// DirectInput�I�u�W�F�N�g�̐���
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr);
		if (FAILED(hr))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CInput::Uninit()
{
	if (m_pMouse != nullptr) {
		m_pMouse->Uninit();
		m_pMouse = nullptr;
	}

	if (m_pKeyboard != nullptr) {
		m_pKeyboard->Uninit();
		m_pKeyboard = nullptr;
	}

	if (m_pGamepad != nullptr) {
		m_pGamepad->Uninit();
		m_pGamepad = nullptr;
	}

	// ���̓f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();	// �A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// �I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//==========================================================================
// �X�V����
//==========================================================================
void CInput::Update()
{
	m_pMouse->Update();
	m_pKeyboard->Update();
	m_pGamepad->Update();
}