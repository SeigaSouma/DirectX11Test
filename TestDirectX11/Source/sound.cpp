//==========================================================================
//
// �T�E���h���� [sound.cpp]
// Author : ���n�Ή�
//
//==========================================================================
#include "sound.h"
#include "calculation.h"

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
CSound::SOUNDINFO CSound::m_aSoundInfo[LABEL_MAX] = 
{
	{ "data/BGM/title.wav", -1 },			// �^�C�g��
	{ "data/BGM/game.wav", -1 },			// �Q�[����
	{ "data/BGM/gameclear.wav", -1 },		// �Q�[���N���A
	{ "data/BGM/enhance.wav", -1 },			// ����
	{ "data/BGM/enhance_wind.wav", -1 },	// �����̕�
	{ "data/BGM/boss.wav", -1 },			// �{�X
	{ "data/BGM/result.wav", -1 },			// �^�C�g��
	{ "data/BGM/galleryClear.wav", -1 },	// �ϋq
	{ "data/SE/walk01.wav", 0 },			// ���s1
	{ "data/SE/walk02.wav", 0 },			// ���s2
	{ "data/SE/dash01.wav", 0 },			// �_�b�V��1
	{ "data/SE/dash02.wav", 0 },			// �_�b�V��2
	{ "data/SE/jump.wav", 0 },				// �W�����v
	{ "data/SE/avoid.wav", 0 },				// ���
	{ "data/SE/knockback_passive.wav", 0 },	// �󂯐g
	{ "data/SE/atkswing_01.wav", 0 },		// �ʏ�U���X�C���O1
	{ "data/SE/atkswing_02.wav", 0 },		// �ʏ�U���X�C���O2
	{ "data/SE/atkswing_03.wav", 0 },		// �ʏ�U���X�C���O3
	{ "data/SE/atkswing_02_dash.wav", 0 },	// �_�b�V���U���X�C���O2
	{ "data/SE/atkhit_01.wav", 0 },			// �ʏ�U���q�b�g1
	{ "data/SE/atkhit_02.wav", 0 },			// �ʏ�U���q�b�g2
	{ "data/SE/atkhit_03.wav", 0 },			// �ʏ�U���q�b�g3
	{ "data/SE/gallery01.wav", 0 },			// �ϋq1
	{ "data/SE/gallery02.wav", 0 },			// �ϋq2
	{ "data/SE/Inenhance.wav", 0 },			// ��������
	{ "data/SE/battlestart.wav", 0 },			// �퓬�J�n
	{ "data/SE/battlestart_strart.wav", 0 },	// �퓬�J�n�J�n
	{ "data/SE/battlestart_charge.wav", 0 },	// �퓬�J�n����
	{ "data/SE/skilltreeStart.wav", 0 },		// �X�L���c���[�N��
	{ "data/SE/skillget.wav", 0 },				// �X�L���l��
	{ "data/SE/skilltree_wait.wav", -1 },		// �X�L���c���[�N���҂�
	{ "data/SE/gameclear.wav", 0 },				// �N���A
	{ "data/SE/battleresult.wav", 0 },			// ��ʕ\��
	{ "data/SE/battleresult_end.wav", 0 },		// ��ʕ\����
	{ "data/SE/battleresult_rank.wav", 0 },		// ��ʃ����N
	{ "data/SE/strongATK.wav", 0 },				// ���U������
	{ "data/SE/charge_start.wav", 0 },			// �`���[�W�U���J�n
	{ "data/SE/charge_complete.wav", 0 },		// �`���[�W�U������
	{ "data/SE/charge_endress.wav", -1 },		// �`���[�W����
	{ "data/SE/charge_move.wav", 0 },			// �`���[�W�U���ړ�
	{ "data/SE/chargeatk_hit.wav", 0 },			// �`���[�W�U���q�b�g
	{ "data/SE/cursor_move.wav", 0 },			// �J�[�\���ړ�
	{ "data/SE/surcor_end.wav", 0 },			// �J�[�\����
	{ "data/SE/cancel01.wav", 0 },				// �L�����Z��1
	{ "data/SE/cancel02.wav", 0 },				// �L�����Z��2
	{ "data/SE/counter_normal.wav", 0 },		// �J�E���^�[�ʏ�U��
	{ "data/SE/counter_strong.wav", 0 },		// �J�E���^�[���U��
	{ "data/SE/counter_hit4.wav", 0 },			// �J�E���^�[�U��
	{ "data/SE/playerdmg_01.wav", 0 },			// �ʏ�U����e
	{ "data/SE/playerdmg_big.wav", 0 },			// ���U����e
	{ "data/SE/guard.wav", 0 },					// �K�[�h��e
	{ "data/SE/guardbreak.wav", 0 },			// �K�[�h�u���C�N
	{ "data/SE/enemyField_strong.wav", 0 },		// �G�n��(��)
	{ "data/SE/enemyField_short.wav", 0 },		// �G�n��(�Z)
	{ "data/SE/enemyswing_01.wav", 0 },			// �G�U���X�C���O(�x)
	{ "data/SE/enemyswing_02.wav", 0 },			// �G�U���X�C���O(��)

};	// �T�E���h�̏��

//==========================================================================
// �}�N����`
//==========================================================================
CSound::CSound()
{
	
}

//==========================================================================
// �}�N����`
//==========================================================================
CSound::~CSound()
{

}

//==========================================================================
// ����������
//==========================================================================
HRESULT CSound::Init(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(m_pXAudio2 != nullptr)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
			m_pXAudio2 = nullptr;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for(int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(m_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �\�[�X�{�C�X�̐���
		hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = m_aSoundInfo[nCntSound].nCntLoop;
		SetVolume.dwFlags = DSBCAPS_CTRLVOLUME;		//���ʒ����̃t���O

		m_fVolume = 1.0f;

		//���ʂ��Z�b�g����
		m_pMasteringVoice->SetVolume(1.0f);

		// �I�[�f�B�I�o�b�t�@�̓o�^
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		m_wfx[nCntSound] = wfx;

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CSound::Uninit()
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound] != nullptr)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = nullptr;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = nullptr;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = nullptr;
	
	if(m_pXAudio2 != nullptr)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = nullptr;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}

//==========================================================================
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
//==========================================================================
HRESULT CSound::PlaySound(LABEL label, bool stop)
{
#if 0
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = m_aSoundInfo[label].nCntLoop;

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_apSourceVoice[label]->Start(0);

	// ���g�����Z�b�g
	m_apSourceVoice[label]->SetFrequencyRatio(1.0f);

#else
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[label].nCntLoop;

	if (m_apSourceVoice[label] != nullptr)
	{
		// ��Ԏ擾
		XAUDIO2_VOICE_STATE xa2state;
		m_apSourceVoice[label]->GetState(&xa2state);
		if (xa2state.BuffersQueued != 0 &&
			(buffer.LoopCount == -1 || stop))
		{// �Đ���
			// �ꎞ��~
			m_apSourceVoice[label]->Stop(0);

			// �I�[�f�B�I�o�b�t�@�̍폜
			m_apSourceVoice[label]->FlushSourceBuffers();
		}
	}

	// �\�[�X�{�C�X��V�����쐬���čĐ�
	HRESULT hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[label], &(m_wfx[label].Format));
	if (FAILED(hr))
	{
		MessageBox(GetWnd(), "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return S_FALSE;
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_apSourceVoice[label]->Start(0);

	// ���g�����Z�b�g
	m_apSourceVoice[label]->SetFrequencyRatio(1.0f);

	// ���ʃ��Z�b�g
	m_apSourceVoice[label]->SetVolume(1.0f);

#endif
	return S_OK;

}

//==========================================================================
// �Z�O�����g��~(���x���w��)
//==========================================================================
void CSound::StopSound(LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	if (m_apSourceVoice[label] == nullptr)
	{
		return;
	}

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);

	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();

		// ���g�����Z�b�g
		m_apSourceVoice[label]->SetFrequencyRatio(1.0f);
	}

	if (m_apSourceVoice[label] != nullptr)
	{
		m_apSourceVoice[label]->Stop(0);
		m_apSourceVoice[label]->FlushSourceBuffers();
		m_apSourceVoice[label]->DestroyVoice();
		m_apSourceVoice[label] = nullptr;
	}
}

//==========================================================================
// �Z�O�����g��~(�S��)
//==========================================================================
void CSound::StopSound()
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound] != nullptr)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);

			// ���g�����Z�b�g
			m_apSourceVoice[nCntSound]->SetFrequencyRatio(1.0f);
		}

		if (m_apSourceVoice[nCntSound] != nullptr)
		{
			m_apSourceVoice[nCntSound]->Stop(0);
			m_apSourceVoice[nCntSound]->FlushSourceBuffers();
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = nullptr;
		}
	}
}

//==========================================================================
// �`�����N�̃`�F�b�N
//==========================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, nullptr) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, nullptr) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, nullptr) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, nullptr, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//==========================================================================
// �`�����N�f�[�^�̓ǂݍ���
//==========================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, nullptr) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

//==========================================================================
// ���ʐݒ�
//==========================================================================
void CSound::VolumeChange(LABEL label, float volume)
{
	if (m_apSourceVoice[label] == nullptr)
	{
		return;
	}
	UtilFunc::Transformation::ValueNormalize(volume, 2.0f, 0.0f);

	// ���ʐݒ�
	m_apSourceVoice[label]->SetVolume(volume);
}

//==========================================================================
// ���ʒ���(�}�X�^�[�{�����[���ݒ�)
//==========================================================================
void CSound::VolumeChange(float fVolume)
{
	m_fVolume += fVolume;
	UtilFunc::Transformation::ValueNormalize(m_fVolume, 2.0f, 0.0f);

	//���ʂ��Z�b�g����
	m_pMasteringVoice->SetVolume(m_fVolume);
}

//==========================================================================
// ���ʎ擾(3���\��)
//==========================================================================
int CSound::GetVolume()
{
	return (int)((m_fVolume + 0.009) * 100);
}

//==========================================================================
// ���g���ݒ�
//==========================================================================
void CSound::SetFrequency(LABEL label, float fValue)
{
	XAUDIO2_VOICE_STATE state;

	if (m_apSourceVoice[label] == nullptr){
		return;
	}

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&state);

	if (state.BuffersQueued != 0)
	{// �Đ���
		m_apSourceVoice[label]->SetFrequencyRatio(fValue);
	}
}
