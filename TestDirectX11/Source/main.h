//=============================================================================
// 
//  ���C������ [main.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _MAIN_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//==========================================================================
// �}�N����`
//==========================================================================
#define SCREEN_WIDTH		(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT		(720)		// �E�C���h�E�̍���
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g
#define FVF_VERTEX_2D_MULTITEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2)
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���_�t�H�[�}�b�g3D
#define MESH_FVF (D3DFVF_XYZ | D3DFVF_NORMAL)

#define ACTION_MODE		(0)								// �A�N�V����
#define TOPCUR		(1)								// �A�N�V����
#define MODE_SCREENSHOT	(1)	// �X�N�V�����[�h

#if 0
#define AUTO_MOVE			(1)				// �ړ��̐؂�ւ�
#endif

//==========================================================================
// ���_���̍\���̂�錾
//==========================================================================
typedef struct
{
	MyLib::Vector3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	MyLib::Vector2 tex;	// �e�N�X�`�����W
}VERTEX_2D;

typedef struct
{
	MyLib::Vector3 pos;
	float rhw;
	D3DCOLOR col;
	MyLib::Vector2 tex;	// �e�N�X�`�����W
	MyLib::Vector2 tex2;	// �e�N�X�`�����W
}VERTEX_2D_MULTITEX;

// ���_���[3D]�̍\���̂��`
typedef struct
{
	MyLib::Vector3 pos;		// ���_���W
	MyLib::Vector3 nor;		// �@���x�N�g��
	D3DCOLOR col;			// ���_�J���[
	MyLib::Vector2 tex;		// �e�N�X�`�����W
} VERTEX_3D;

struct VERTEX
{
	MyLib::Vector3 pos;
	MyLib::Color col;
};

//==========================================================================
// �v���g�^�C�v�錾
//==========================================================================
int GetFPS();
HWND GetWnd();

class CMyEffekseer;
class CLoadManager;

CLoadManager* GetLoadManager();
//void Render(MyLib::Vector3 pos, MyLib::Vector3 scale, MyLib::Vector3 degree);

#endif