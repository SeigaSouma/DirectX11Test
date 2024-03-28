//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���n�Ή�
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �T�E���h�N���X
class CSound
{
public:

	// �񋓌^��`
	enum LABEL
	{
		LABEL_BGM_TITLE = 0,			// �^�C�g��
		LABEL_BGM_GAME,					// �Q�[��
		LABEL_BGM_GAMECLEAR,			// �N���A
		LABEL_BGM_ENHANCE,				// ����
		LABEL_BGM_ENHANCE_WIND,			// �����̕�
		LABEL_BGM_BOSS,					// �{�X
		LABEL_BGM_RESULT,				// ���U���g
		LABEL_BGM_GALLERY,				// �ϋq
		LABEL_SE_WALK1,					// ���s1
		LABEL_SE_WALK2,					// ���s2
		LABEL_SE_DASH1,					// �_�b�V��1
		LABEL_SE_DASH2,					// �_�b�V��2
		LABEL_SE_JUMP,					// �W�����v
		LABEL_SE_AVOID,					// ���
		LABEL_SE_PASSIVE,				// �󂯐g
		LABEL_SE_NORMALATK_SWING1,		// �ʏ�U���X�C���O1
		LABEL_SE_NORMALATK_SWING2,		// �ʏ�U���X�C���O2
		LABEL_SE_NORMALATK_SWING3,		// �ʏ�U���X�C���O3
		LABEL_SE_DASHATK_SWING2,		// �_�b�V���U���X�C���O2
		LABEL_SE_NORMALATK_HIT1,		// �ʏ�U���q�b�g1
		LABEL_SE_NORMALATK_HIT2,		// �ʏ�U���q�b�g2
		LABEL_SE_NORMALATK_HIT3,		// �ʏ�U���q�b�g3
		LABEL_SE_GALLERY1,				// �ϋq1
		LABEL_SE_GALLERY2,				// �ϋq2
		LABEL_SE_IN_ENHANCE,			// ��������
		LABEL_SE_BATTLESTART,			// �퓬�J�n
		LABEL_SE_BATTLESTART_START,		// �퓬�J�n�J�n
		LABEL_SE_BATTLESTART_CHARGE,	// �퓬�J�n����
		LABEL_SE_SKILLTREE_START,		// �X�L���c���[�N��
		LABEL_SE_SKILLTREE_GET,			// �X�L���l��
		LABEL_SE_SKILLTREE_WAIT,		// �X�L���N���҂�
		LABEL_SE_BATTLERESULT_CLEAR,	// �N���A
		LABEL_SE_BATTLERESULT,			// ��ʕ\��
		LABEL_SE_BATTLERESULT_END,		// ��ʕ\����
		LABEL_SE_BATTLERESULT_RANK,		// ��ʃ����N
		LABEL_SE_STRONGATK,				// ���U������
		LABEL_SE_CHARGEATK_START,		// �`���[�W�U���J�n
		LABEL_SE_CHARGEATK_COMPLETE,	// �`���[�W�U������
		LABEL_SE_CHARGEATK_ENDRESS,		// �`���[�W��������
		LABEL_SE_CHARGEATK_MOVE,		// �`���[�W�U���ړ�
		LABEL_SE_CHARGEATK_HIT,			// �`���[�W�U���q�b�g
		LABEL_SE_CURSOR_MOVE,			// �J�[�\���ړ�
		LABEL_SE_CURSOR_END,			// �J�[�\����
		LABEL_SE_CANCEL1,				// �L�����Z��1
		LABEL_SE_CANCEL2,				// �L�����Z��2
		LABEL_SE_COUNTER_TURN,			// �J�E���^�[�󂯗���
		LABEL_SE_COUNTER_ATTACK,		// �J�E���^�[����
		LABEL_SE_COUNTER_HIT,			// �J�E���^�[�U��
		LABEL_SE_PLAYERDMG_NORMAL,		// �ʏ�U����e
		LABEL_SE_PLAYERDMG_STRONG,		// ���U����e
		LABEL_SE_GUARD_DMG,				// �K�[�h��e
		LABEL_SE_GUARD_BREAK,			// �K�[�h�u���C�N
		LABEL_SE_ENEMY_FIELD_STRONG,	// �G�n��(��)
		LABEL_SE_ENEMY_FIELD_SHORT,		// �G�n��(�Z)
		LABEL_SE_ENEMY_SWING_SLOW,		// �G�U���X�C���O1
		LABEL_SE_ENEMY_SWING_FAST,		// �G�U���X�C���O1
		LABEL_MAX,
	};

	typedef struct
	{
		const char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit();
	HRESULT PlaySound(LABEL label, bool stop = false);
	void StopSound();
	void StopSound(LABEL label);
	void VolumeChange(LABEL label, float volume);	// ���ʐݒ�
	void VolumeChange(float fVolume);				// �}�X�^�[�{�����[���ݒ�
	int GetVolume();
	void SetFrequency(LABEL label, float fValue);	// ���g���ݒ�

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y
	DSBUFFERDESC SetVolume;								// ���ʒ���
	float m_fVolume;									// ����
	static SOUNDINFO m_aSoundInfo[LABEL_MAX];			// �T�E���h�̏��
	WAVEFORMATEXTENSIBLE m_wfx[LABEL_MAX];
};


#endif
