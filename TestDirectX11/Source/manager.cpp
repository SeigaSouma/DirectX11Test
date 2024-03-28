//=============================================================================
// 
//  �}�l�[�W������ [manager.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "calculation.h"
#include "light.h"
#include "fog.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	const float TIME_LOAD = 2.0f;	// ���[�h����

#if _DEBUG
	const CScene::MODE STARTMODE = CScene::MODE_GAME;
#else
	const CScene::MODE STARTMODE = CScene::MODE_TITLE;
#endif
}

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
CManager *CManager::m_pManager = nullptr;					// �}�l�[�W���̃I�u�W�F�N�g

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CManager::CManager()
{
	m_pRenderer = nullptr;			// �����_���[
	m_pInputKeyboard = nullptr;		// �L�[�{�[�h
	m_pInputGamepad = nullptr;		// �Q�[���p�b�h
	m_pSound = nullptr;				// �T�E���h
	m_pInputMouse = nullptr;		// �}�E�X
	m_pDebugProc = nullptr;			// �f�o�b�O�\��
	m_pLight = nullptr;				// ���C�g
	m_pCamera = nullptr;			// �J����
	m_pTexture = nullptr;			// �e�N�X�`��
	m_pXLoad = nullptr;				// X�t�@�C��
	m_pEdit = nullptr;				// �G�f�B�b�g
	m_pScene = nullptr;				// �V�[��
	m_pFade = nullptr;				// �t�F�[�h
	m_pInstantFade = nullptr;		// �J�ڂȂ��t�F�[�h
	m_pBlackFrame = nullptr;		// ���t���[��
	m_pPause = nullptr;				// �|�[�Y
	m_pResultManager = nullptr;		// ���U���g�}�l�[�W��
	m_pRankingManager = nullptr;	// �����L���O�}�l�[�W��
	m_pMyEffekseer = nullptr;		// �G�t�F�N�V�A
	m_bWireframe = false;			// ���C���[�t���[��
	m_bHitStop = false;				// �q�b�g�X�g�b�v�̔���
	m_nCntHitStop = 0;				// �q�b�g�X�g�b�v�̃J�E���^�[
	m_OldMode = CScene::MODE_NONE;	// �O��̃��[�h
	m_CurrentTime = 0;				// ���ݎ���
	m_OldTime = 0;					// �ߋ��̎���
	m_fDeltaTime = 0.0f;			// �o�ߎ���
	m_nNumPlayer = 0;				// �v���C���[�̐�
	m_fLoadTimer = 0.0f;			// ���[�h�̃^�C�}�[
	m_bLoadComplete = false;		// ���[�h�����̃t���O
	m_bFirstLoad = false;			// ���񃍁[�h

	// ���[�h�t���O���Z�b�g
	m_bLoadComplete = false;

	// ���[�h�̃t�F�[�h�ݒ�t���O
	m_bLoadFadeSet = false;
	m_bNowLoading = false;				// ���[�h�����̃t���O
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CManager::~CManager()
{

}

//==========================================================================
// ��������
//==========================================================================
CManager *CManager::Create()
{
	if (m_pManager == nullptr)
	{// �܂��������Ă��Ȃ�������

		// �}�l�[�W���̃C���X�^���X����
		m_pManager = DEBUG_NEW CManager;
	}
	else
	{
		// �C���X�^���X�擾
		m_pManager->GetInstance();
	}

	return m_pManager;
}

//==========================================================================
// �C���X�^���X�擾
//==========================================================================
CManager *CManager::GetInstance()
{
	return m_pManager;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	HRESULT hr;
	m_bHitStop = false;		// �q�b�g�X�g�b�v�̔���
	m_nCntHitStop = 0;		// �q�b�g�X�g�b�v�̃J�E���^�[
	m_nNumPlayer = 0;		// �v���C���[�̐�


	//**********************************
	// �����_���[
	//**********************************
	if (m_pRenderer != nullptr)
	{// �m�ۂ���Ă�����

		return E_FAIL;
	}

	// �������m��
	m_pRenderer = DEBUG_NEW CRenderer;

	if (m_pRenderer != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		// ����������
		hr = m_pRenderer->Init(hWnd, TRUE);
		if (FAILED(hr))
		{// ���������������s�����ꍇ
			return E_FAIL;
		}
	}


	// Imgui�̏�����
	//ImguiMgr::Init(hWnd, m_pRenderer->GetDevice());

	//**********************************
	// �T�E���h
	//**********************************
	if (m_pSound != nullptr)
	{// �m�ۂ���Ă�����
		return E_FAIL;
	}

	// �������m��
	m_pSound = DEBUG_NEW CSound;

	if (m_pSound != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		// ����������
		hr = m_pSound->Init(hWnd);
		if (FAILED(hr))
		{// ���������������s�����ꍇ
			return E_FAIL;
		}
	}


	//**********************************
	// �f�o�b�O�\��
	//**********************************
	if (m_pDebugProc != nullptr)
	{// �m�ۂ���Ă�����
		return E_FAIL;
	}

	// �������m��
	m_pDebugProc = DEBUG_NEW CDebugProc;

	if (m_pDebugProc != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		// ����������
		hr = m_pDebugProc->Init(hInstance, hWnd);
		if (FAILED(hr))
		{// ���������������s�����ꍇ
			return E_FAIL;
		}
	}


	//**********************************
	// ���C�g
	//**********************************
	if (m_pLight != nullptr)
	{// �m�ۂ���Ă�����
		return E_FAIL;
	}

	// �������m��
	m_pLight = DEBUG_NEW CLight;

	if (m_pLight != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		// ����������
		hr = m_pLight->Init();
		if (FAILED(hr))
		{// ���������������s�����ꍇ
			return E_FAIL;
		}
	}



	// ���[�h�t���O���Z�b�g
	m_bLoadComplete = false;
	m_bLoadFadeSet = false;	// ���[�h�̃t�F�[�h�ݒ�t���O
	m_bNowLoading = true;

	// �V�[���̃��[�h���J�n
	//GetLoadManager()->LoadScene(CScene::MODE_NONE);

	return S_OK;
}

//==========================================================================
// �ǂݍ���
//==========================================================================
void CManager::Load()
{

	//// �S�Ẵe�N�X�`���ǂݍ���
	//m_pTexture->LoadAll();

	//// �S�Ẵ��f���ǂݍ���
	//m_pXLoad->LoadAll();

	////**********************************
	//// �J�ڂȂ��t�F�[�h
	////**********************************
	//m_pInstantFade = CInstantFade::Create();
	//if (m_pInstantFade == nullptr)
	//{
	//	return;
	//}

	////**********************************
	//// ���t���[��
	////**********************************
	//m_pBlackFrame = CBlackFrame::Create();
	//if (m_pBlackFrame == nullptr)
	//{
	//	return;
	//}

	////**********************************
	//// �|�[�Y
	////**********************************
	//m_pPause = CPause::Create(STARTMODE);
	//if (m_pPause == nullptr)
	//{
	//	return;
	//}

	////**********************************
	//// ���U���g�}�l�[�W��
	////**********************************
	//m_pResultManager = CResultManager::Create();
	//if (m_pResultManager == nullptr)
	//{
	//	return;
	//}

	////**********************************
	//// �����L���O�}�l�[�W��
	////**********************************
	//m_pRankingManager = CRankingManager::Create();
	//if (m_pRankingManager == nullptr)
	//{
	//	return;
	//}

	// ���[�h�ݒ�
	NoLoadSetMode(STARTMODE);
}

//==========================================================================
// ���̃��[�h�ݒ�
//==========================================================================
void CManager::SetMode(CScene::MODE mode)
{
	//GetLoadManager()->UnLoad();

	// ���̃��[�h�ݒ�
	NoLoadSetMode(mode);

	// ���[�h�̃^�C�}�[���Z�b�g
	m_fLoadTimer = 0.0f;

	// ���[�h�t���O���Z�b�g
	m_bLoadComplete = false;
	m_bLoadFadeSet = false;				// ���[�h�̃t�F�[�h�ݒ�t���O
	m_bNowLoading = true;

	// �V�[���̃��[�h���J�n
	//GetLoadManager()->LoadScene(mode);
}

//==========================================================================
// ���̃��[�h�ݒ�
//==========================================================================
void CManager::NoLoadSetMode(CScene::MODE mode)
{
	// ���Z�b�g
	Reset(mode);

	// ��������
	m_pScene = CScene::Create(mode);

	// ���[�h�̃^�C�}�[���Z�b�g
	m_fLoadTimer = 0.0f;
}

//==========================================================================
// ���Z�b�g
//==========================================================================
void CManager::Reset(CScene::MODE mode)
{
	m_bHitStop = false;		// �q�b�g�X�g�b�v�̔���
	m_nCntHitStop = 0;		// �q�b�g�X�g�b�v�̃J�E���^�[

	// �O��̃��[�h�ݒ�
	m_OldMode = GetMode();

	

	// BGM�X�g�b�v
	if (m_pSound != nullptr && mode != CScene::MODE_RANKING)
	{
		m_pSound->StopSound();
	}

	// �������̊m�ۂ�����Ă�����
	if (m_pScene != nullptr)
	{
		// �I������
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	// �S�ẴI�u�W�F�N�g�j��
	CObject::ReleaseAll();

	//// �|�[�Y�󋵓���ւ�
	//if (m_pPause != nullptr)
	//{
	//	ChangePauseMode(mode);

	//	if (m_pPause->IsPause() == true)
	//	{// �|�[�Y����������
	//		m_pPause->SetPause();
	//	}
	//}

	//// ���t���[�����Z�b�g
	//m_pBlackFrame->Reset();

	//// �J�����̏�񃊃Z�b�g
	//if (m_pCamera != nullptr)
	//{
	//	m_pCamera->Reset(mode);
	//}
}

//==========================================================================
// ���݂̃��[�h�擾
//==========================================================================
CScene::MODE CManager::GetMode()
{
	// ���[�h�擾
	if (m_pScene != nullptr)
	{
		return m_pScene->GetMode();
	}
	else
	{
		return CScene::MODE_NONE;
	}
}

//==========================================================================
// �I������
//==========================================================================
void CManager::Uninit()
{
	// �S�ẴI�u�W�F�N�g�j��
	CObject::ReleaseAll();

	// BGM�X�g�b�v
	m_pSound->StopSound();

	//// �L�[�{�[�h�̔j��
	//if (m_pInputKeyboard != nullptr)
	//{// �������̊m�ۂ��o���Ă�����

	//	// �I������
	//	m_pInputKeyboard->Uninit();

	//	// �������̊J��
	//	delete m_pInputKeyboard;
	//	m_pInputKeyboard = nullptr;
	//}

	//// �Q�[���p�b�h�̔j��
	//if (m_pInputGamepad != nullptr)
	//{// �������̊m�ۂ��o���Ă�����

	//	// �I������
	//	m_pInputGamepad->Uninit();

	//	// �������̊J��
	//	delete m_pInputGamepad;
	//	m_pInputGamepad = nullptr;
	//}

	//// �}�E�X�̔j��
	//if (m_pInputMouse != nullptr)
	//{// �������̊m�ۂ��o���Ă�����

	//	// �I������
	//	m_pInputMouse->Uninit();

	//	// �������̊J��
	//	delete m_pInputMouse;
	//	m_pInputMouse = nullptr;
	//}

	// �����_���[�̔j��
	if (m_pRenderer != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		// �I������
		m_pRenderer->Uninit();

		// �������̊J��
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// Imgui�̏I��
	//ImguiMgr::Uninit();

	// ���C�g�̔j��
	if (m_pLight != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		// �I������
		m_pLight->Uninit();

		// �������̊J��
		delete m_pLight;
		m_pLight = nullptr;
	}

	//// �J�����̔j��
	//if (m_pCamera != nullptr)
	//{// �������̊m�ۂ��o���Ă�����

	//	// �I������
	//	m_pCamera->Uninit();

	//	// �������̊J��
	//	delete m_pCamera;
	//	m_pCamera = nullptr;
	//}

	//if (m_pMyEffekseer != nullptr)
	//{
	//	// �I������
	//	m_pMyEffekseer->Uninit();
	//	m_pMyEffekseer = nullptr;
	//}

	// �T�E���h�̔j��
	if (m_pSound != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		// �I������
		m_pSound->Uninit();

		// �������̊J��
		delete m_pSound;
		m_pSound = nullptr;
	}

	// �f�o�b�O�\���̔j��
	if (m_pDebugProc != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		// �I������
		m_pDebugProc->Uninit();

		// �������̊J��
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

	// �G�f�B�b�g�̔j��
	if (m_pEdit != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		m_pEdit = nullptr;
	}

	//**********************************
	// �S�Ẵe�N�X�`���j��
	//**********************************
	//if (m_pTexture != nullptr)
	//{// �������̊m�ۂ��o���Ă�����

	//	// �I������
	//	m_pTexture->Unload();

	//	// �������̊J��
	//	delete m_pTexture;
	//	m_pTexture = nullptr;
	//}

	//if (m_pXLoad != nullptr)
	//{
	//	// �I������
	//	m_pXLoad->Uninit();

	//	// �������̊J��
	//	m_pXLoad = nullptr;
	//}

	if (m_pScene != nullptr)
	{// �������̊m�ۂ��o���Ă�����

		// �I������
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//// �t�F�[�h�̔j��
	//if (m_pFade != nullptr)
	//{// �������̊m�ۂ�����Ă�����

	//	// �I������
	//	m_pFade->Uninit();
	//	delete m_pFade;
	//	m_pFade = nullptr;
	//}

	//// �J�ڂȂ��t�F�[�h�̔j��
	//if (m_pInstantFade != nullptr)
	//{// �������̊m�ۂ�����Ă�����

	//	// �I������
	//	m_pInstantFade->Uninit();
	//	delete m_pInstantFade;
	//	m_pInstantFade = nullptr;
	//}

	//// ���t���[���̔j��
	//if (m_pBlackFrame != nullptr)
	//{// �������̊m�ۂ�����Ă�����

	//	// �I������
	//	m_pBlackFrame->Uninit();
	//	delete m_pBlackFrame;
	//	m_pBlackFrame = nullptr;
	//}

	//if (m_pPause != nullptr)
	//{// �������̊m�ۂ�����Ă�����

	//	// �I������
	//	m_pPause->Uninit();
	//	delete m_pPause;
	//	m_pPause = nullptr;
	//}

	//if (m_pResultManager != nullptr)
	//{// �������̊m�ۂ�����Ă�����

	//	// �I������
	//	m_pResultManager->Uninit();
	//	delete m_pResultManager;
	//	m_pResultManager = nullptr;
	//}

	//if (m_pRankingManager != nullptr)
	//{// �������̊m�ۂ�����Ă�����

	//	// �I������
	//	m_pRankingManager->Uninit();
	//	delete m_pRankingManager;
	//	m_pRankingManager = nullptr;
	//}

}

//==========================================================================
// �X�V����
//==========================================================================
void CManager::Update()
{
	// �L�[�{�[�h���擾
	CInputKeyboard *pInputKeyboard = GetInputKeyboard();

	// �ߋ��̎��ԕۑ�
	m_OldTime = m_CurrentTime;

	// �o�ߎ���
	m_CurrentTime = timeGetTime();
	m_fDeltaTime = (float)(m_CurrentTime - m_OldTime) / 1000;

	// Imgui�̍X�V
	//ImguiMgr::Update();

	
}

//==========================================================================
// �`�揈��
//==========================================================================
void CManager::Draw()
{
	/*if (!m_bLoadComplete)
	{
		GetLoadManager()->Draw();
		return;
	}*/

	//// �f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = m_pRenderer->GetDevice();

	//if (m_bWireframe)
	//{
	//	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	// ���߂郂�[�h
	//}

	// �����_���[�̕`�揈��
	m_pRenderer->Draw();

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	// ���߂郂�[�h
}

//==========================================================================
// �v���C���[�̐��擾
//==========================================================================
int CManager::GetNumPlayer()
{
	return m_nNumPlayer;
}

//==========================================================================
// �v���C���[�̐��ݒ�
//==========================================================================
void CManager::SetNumPlayer(int nNum)
{
	// �l�̐��K������
	UtilFunc::Transformation::ValueNormalize(nNum, mylib_const::MAX_PLAYER, 0);

	m_nNumPlayer = nNum;
}

//==========================================================================
// �|�[�Y�̎�ސ؂�ւ�
//==========================================================================
void CManager::ChangePauseMode(CScene::MODE mode)
{
	switch (mode)
	{
	case CScene::MODE::MODE_GAME:
	case CScene::MODE::MODE_GAMETUTORIAL:

		//// �폜
		//if (m_pPause!= nullptr)
		//{
		//	m_pPause->Kill();
		//	delete m_pPause;
		//	m_pPause = nullptr;
		//}

		//// �Đ���
		//m_pPause = CPause::Create(mode);
		break;

	default:
		break;
	}
}

//==========================================================================
// �o�ߎ��Ԏ擾
//==========================================================================
float CManager::GetDeltaTime()
{
	return m_fDeltaTime;
}

//==========================================================================
// �q�b�g�X�g�b�v�̐ݒ�
//==========================================================================
void CManager::SetEnableHitStop(int nCntHitStop)
{
	m_bHitStop = true;
	m_nCntHitStop = nCntHitStop;
}

//==========================================================================
// �����_���[�̎擾
//==========================================================================
CRenderer *CManager::GetRenderer()
{
	return m_pRenderer;
}

//==========================================================================
// �L�[�{�[�h�̎擾
//==========================================================================
CInputKeyboard *CManager::GetInputKeyboard()
{
	return m_pInputKeyboard;
}

//==========================================================================
// �Q�[���p�b�h�̎擾
//==========================================================================
CInputGamepad *CManager::GetInputGamepad()
{
	return m_pInputGamepad;
}

//==========================================================================
// �}�E�X�̎擾
//==========================================================================
CInputMouse *CManager::GetInputMouse()
{
	return m_pInputMouse;
}

//==========================================================================
// �T�E���h�̎擾
//==========================================================================
CSound *CManager::GetSound()
{
	return m_pSound;
}

//==========================================================================
// �f�o�b�O�\���̎擾
//==========================================================================
CDebugProc *CManager::GetDebugProc()
{
	return m_pDebugProc;
}

//==========================================================================
// ���C�g�̎擾
//==========================================================================
CLight *CManager::GetLight()
{
	return m_pLight;
}

//==========================================================================
// �J�����̎擾
//==========================================================================
CCamera *CManager::GetCamera()
{
	return m_pCamera;
}

//==========================================================================
// �G�f�B�b�g�̎擾
//==========================================================================
CEdit *CManager::GetEdit()
{
	return m_pEdit;
}

//==========================================================================
// �t�F�[�h�̎擾
//==========================================================================
CFade *CManager::GetFade()
{
	return m_pFade;
}

//==========================================================================
// �J�ڂȂ��t�F�[�h�̎擾
//==========================================================================
CInstantFade *CManager::GetInstantFade()
{
	return m_pInstantFade;
}

//==========================================================================
// ���t���[���̎擾
//==========================================================================
CBlackFrame *CManager::GetBlackFrame()
{
	return m_pBlackFrame;
}

//==========================================================================
// �|�[�Y�̎擾
//==========================================================================
CPause *CManager::GetPause()
{
	return m_pPause;
}

//==========================================================================
// ���U���g�}�l�[�W���擾
//==========================================================================
CResultManager *CManager::GetResultManager()
{
	return m_pResultManager;
}

//==========================================================================
// �����L���O�}�l�[�W���̃I�u�W�F�N�g
//==========================================================================
CRankingManager *CManager::GetRankingManager()
{
	return m_pRankingManager;
}

//==========================================================================
// �V�[���擾
//==========================================================================
CScene *CManager::GetScene()
{
	return m_pScene;
}

