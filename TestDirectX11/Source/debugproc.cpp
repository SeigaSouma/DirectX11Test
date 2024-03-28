//=============================================================================
//
// �f�o�b�O�\������[debugproc.cpp]
// Author : Ibuki Okusada
//
//=============================================================================
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"

#include "sound.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================

//==========================================================================
// �}�N����`
//==========================================================================
#define MAX_FLOATNUM	(2)		//�����_�ȉ��̕\������

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CDebugProc::CDebugProc()
{
	// �f�o�b�O�\�����̃N���A
	m_bDisp = false;
	memset(&m_aStr[0], 0, sizeof(m_aStr));
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CDebugProc::~CDebugProc()
{
	
}

//==========================================================================
// �f�o�b�O�\���̏���������
//==========================================================================
HRESULT CDebugProc::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	HRESULT hr;

	//�f�o�b�O�\���p�t�H���g�̐���
	//hr = D3DXCreateFont(pDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//if (FAILED(hr))
	//{// ���s���Ă�����

	//	return E_FAIL;
	//}

	//�����\���ݒ�
#if _DEBUG

	// ON
	m_bDisp = true;

#else

	// OFF
	m_bDisp = false;

#endif
	
	// ON
	//m_bDisp = true;

	return S_OK;
}

//==========================================================================
// �f�o�b�O�\���̏I������
//==========================================================================
void CDebugProc::Uninit()
{
	// �t�H���g�̔j��
	
}

//==========================================================================
// �f�o�b�O�\���̍X�V����
//==========================================================================
void CDebugProc::Update()
{

}

//==========================================================================
// �f�o�b�O�\���̕`�揈��
//==========================================================================
void CDebugProc::Draw()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//if (m_bDisp == true)
	//{// �f�o�b�N���[�h���I���̎�

	//	// �e�L�X�g�̕`��
	//	m_pFont->DrawText(nullptr, &m_aStr[0], -1, &rect, DT_LEFT, MyLib::Color(1.0f, 1.0f, 1.0f, 1.0f));
	//}

	// �f�o�b�O�\�����̃N���A
	memset(&m_aStr[0], 0, sizeof(m_aStr));
}

//==========================================================================
// �f�o�b�O�\���̐ݒ菈��
//==========================================================================
void CDebugProc::Print(const char *fmt, ...)
{
	va_list args;
	char aString[MAX_DEBUGSTRING];		// �w�蕶���i�[�p
	char aSaveString[MAX_DEBUGSTRING];	// �ψ������g�i�[�p
	int nLength = 0;	// �ψ������̕����̒���
	int nStopLength;	// �ψ����}���ꏊ���

	// ������̑��
	strcpy(&aString[0], fmt);

	va_start(args, fmt);

	for (char *p = &aString[0]; *p != '\0'; p++)
	{
		if (*p == '%')
		{// �m�F����������ꍇ

			p++;			// �m�F�����܂Ői�߂�

			nLength = 0;	// �����̒������Z�b�g

			// �w�肳�ꂽ��ނ��Ƃɕϐ��̒l�𔲂��o��(va_arg)
			switch (*p)
			{
			case 'd':	// ����

				sprintf(&aSaveString[0], "%d", va_arg(args, int));

				break;
			case 'f':	// ����

				sprintf(&aSaveString[0], "%f", va_arg(args, double));

				// ������̒������擾
				nLength = (int)strlen(&aSaveString[0]);

				// �����_�ȉ���1�����ڂ܂Ŋm�F
				for (int nCntlength = 0; aSaveString[nCntlength] != '\0'; nCntlength++)
				{
					if (aSaveString[nCntlength] == '.')
					{// �����_���������ꍇ

						// �����_�ȉ��̌��������߂�
						int nMin = (int)strlen(&aSaveString[nCntlength + 1]);

						// �����_����̕������Ǝw�肵���l�܂ł̍��������߂�
						nMin -= MAX_FLOATNUM;

						// ������̒����������_�ȉ����ʂ܂łɕ␳
						nLength -= nMin;
					}
				}

				break;

			case 'c':	// ����

				sprintf(&aSaveString[0], "%c", va_arg(args, char));
				break;

			case 's':	// ������

				sprintf(&aSaveString[0], "%s", va_arg(args, const char*));
				break;
			}

			if (nLength == 0)
			{// �����̒������擾���Ă��Ȃ��ꍇ

				// ������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
			}

			nStopLength = (int)strlen(p) + 1;

			// ���������̊m�F����(%�`)�����̕���������炷
			memmove(p + nLength - 2, p, nStopLength);

			p--;	// �|�C���^��%�܂Ŗ߂�

			// �ψ������w�肳�ꂽ�ꏊ�ɑ}��
			memcpy(p, &aSaveString[0], nLength);
		}
	}

	va_end(args);

	// �������A������
	strcat(&m_aStr[0], &aString[0]);
}

//==========================================================================
// �����ݒ菈��
//==========================================================================
void CDebugProc::SetText()
{
	// �f�o�b�O�̏��擾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();

	pDebug->Print("FPS�F%d\n", GetFPS());
	pDebug->Print("�f���^�^�C���F%f\n", CManager::GetInstance()->GetDeltaTime());
	pDebug->Print("�I�u�W�F�N�g�̑����F%d\n", CObject::GetNumAll());

	pDebug->Print("\n--------------------------------[ F�n ]--------------------------------\n");
	pDebug->Print("[F2]�F���C���[�t���[���؂�ւ�\n");
	pDebug->Print("[F3]�F�N���̃G�f�B�b�g�؂�ւ�\n");
	pDebug->Print("[F4]�F�}�b�v����_�G�f�B�b�g�؂�ւ�\n");
	pDebug->Print("[F5]�F�v���C���[�z�u���Z�b�g\n");
	pDebug->Print("[F6]�F�t�H�O�؂�ւ�\n");
	pDebug->Print("[F7]�F�J�����Ǐ]�؂�ւ�\n");
	pDebug->Print("[F8]�F�G�f�B�b�g���[�h�؂�ւ�\n");

	pDebug->Print("\n");
}

// DirectWrite �e�L�X�g�t�@�N�g��������������֐�
IDWriteFactory* InitializeDirectWrite()
{
	IDWriteFactory* pDWriteFactory = nullptr;
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory)
	);
	return pDWriteFactory;
}

// �e�L�X�g��`�悷��֐�
void DrawText(ID2D1RenderTarget* pRenderTarget, IDWriteFactory* pDWriteFactory, LPCWSTR text, D2D1_RECT_F layoutRect, ID2D1Brush* pBrush)
{
	// DirectWrite �e�L�X�g�t�@�N�g��������������Ă��Ȃ��ꍇ�͏���������
	if (!pDWriteFactory)
		pDWriteFactory = InitializeDirectWrite();

	// DirectWrite �e�L�X�g�t�H�[�}�b�g���쐬����
	IDWriteTextFormat* pTextFormat = nullptr;
	pDWriteFactory->CreateTextFormat(
		L"Arial", // �t�H���g�t�@�~���[
		NULL, // �t�H���g�R���N�V����
		DWRITE_FONT_WEIGHT_REGULAR, // �t�H���g�̑���
		DWRITE_FONT_STYLE_NORMAL, // �t�H���g�̃X�^�C��
		DWRITE_FONT_STRETCH_NORMAL, // �t�H���g�̃X�g���b�`
		12.0f, // �t�H���g�T�C�Y
		L"en-US", // ����
		&pTextFormat
	);

	// �e�L�X�g��`�悷��
	pRenderTarget->DrawText(
		text, // �`�悷��e�L�X�g
		wcslen(text), // �e�L�X�g�̒���
		pTextFormat, // �e�L�X�g�t�H�[�}�b�g
		layoutRect, // ���C�A�E�g��`
		pBrush // �u���V
	);

	// �g�p�����e�L�X�g�t�H�[�}�b�g���������
	if (pTextFormat)
		pTextFormat->Release();
}
