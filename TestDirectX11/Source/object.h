//=============================================================================
// 
//  �I�u�W�F�N�g�w�b�_�[ [object.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "constans.h"
#include "renderer.h"
//#include "texture.h"

class CObject2D;
class CObject3D;
class CObject3DMesh;
class CObjectX;
class CObjectChara;
class CEffect3D;

//==========================================================================
// �N���X��`
//==========================================================================
// �I�u�W�F�N�g�N���X��`
class CObject
{
public:

	// �񋓌^��`
	enum TYPE
	{
		TYPE_NONE = 0,		// ����
		TYPE_PLAYER,		// �v���C���[
		TYPE_ENEMY,			// �G
		TYPE_BOSS,			// �{�X
		TYPE_BULLET,		// �e
		TYPE_EXPLOSION,		// ����
		TYPE_BG,			// �w�i
		TYPE_EFFECT2D,		// 2D�G�t�F�N�g
		TYPE_EFFECT3D,		// 3D�G�t�F�N�g
		TYPE_SCORE,			// �X�R�A
		TYPE_TIMER,			// �^�C�}�[
		TYPE_BLOCK,			// �u���b�N
		TYPE_ITEM,			// �A�C�e��
		TYPE_FIELD,			// �t�B�[���h
		TYPE_HPGAUGE,		// HP�Q�[�W
		TYPE_SHADOW,		// �e
		TYPE_MAP,			// �}�b�v
		TYPE_XFILE,			// X�t�@�C��
		TYPE_STAGE,			// X�t�@�C��
		TYPE_MODEL,			// ���f��
		TYPE_EDIT,			// �G�f�B�b�g
		TYPE_MESHFIELD,		// ���b�V���t�B�[���h
		TYPE_ELEVATION,		// �N���t�B�[���h
		TYPE_ELEVATION_OUTSIDE,		// �N���t�B�[���h
		TYPE_WATERFIELD,	// ���̃t�B�[���h
		TYPE_MAGMA,		// �}�O�}�t�B�[���h
		TYPE_MESHWALL,		// ���b�V���E�H�[��
		TYPE_MESHCYLINDER,	// ���b�V���V�����_�[
		TYPE_MESHDOME,		// ���b�V���h�[��
		TYPE_MESHDONUTS,	// ���b�V���h�[�i�c
		TYPE_MESHSPHERE,	// ���b�V���X�t�B�A
		TYPE_FOG,			// �t�H�O
		TYPE_BALLAST,		// ���I
		TYPE_FADE,			// �t�F�[�h
		TYPE_NUMBER,		// ����
		TYPE_OBJECT2D,		// �I�u�W�F�N�g2D
		TYPE_OBJECT3D,		// �I�u�W�F�N�g3D
		TYPE_OBJECTMESH,		// �I�u�W�F�N�g3D
		TYPE_OBJECTX,		// �I�u�W�F�N�gX
		TYPE_OBJECTBILLBOARD,		// �I�u�W�F�N�g�r���{�[�h
		TYPE_MAX
	};

	enum LAYER
	{
		LAYER_MAP = 0,
		LAYER_DEFAULT,
		LAYER_2D,
		LAYER_MAX
	};

	CObject(int nPriority = mylib_const::PRIORITY_DEFAULT, const LAYER layer = LAYER::LAYER_DEFAULT);
	virtual ~CObject();

	// �h���N���X�ŃI�[�o�[���C�h���ꂽ�֐�����ΕK�v(�������z�֐�)
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void SetVtx();
	virtual void SetPosition(const MyLib::Vector3& pos);		// �ʒu�ݒ�
	virtual MyLib::Vector3 GetPosition() const;			// �ʒu�擾
	virtual void SetOldPosition(const MyLib::Vector3& posOld);	// �ߋ��̈ʒu�ݒ�
	virtual MyLib::Vector3 GetOldPosition() const;			// �ߋ��̈ʒu�擾
	virtual void SetOriginPosition(const MyLib::Vector3& pos);	// ���̈ʒu�ݒ�
	virtual MyLib::Vector3 GetOriginPosition() const;		// ���̈ʒu�擾
	virtual void SetMove(const MyLib::Vector3& move);			// �ړ��ʐݒ�
	virtual MyLib::Vector3 GetMove() const;				// �ړ��ʎ擾
	virtual void SetRotation(const MyLib::Vector3& rot);		// �����ݒ�
	virtual MyLib::Vector3 GetRotation() const;			// �����擾
	virtual void SetOriginRotation(const MyLib::Vector3& rot);	// ���̌����ݒ�
	virtual MyLib::Vector3 GetOriginRotation() const;		// ���̌����擾

	// �ύX����
	virtual void AddPosition(const MyLib::Vector3& pos);		// �ʒu�ݒ�

	float ScreenZ() const;
	static bool ZSort(const CObject *obj1, const CObject *obj2);	// Z�\�[�g�̔�r�֐�
	int GetPriority() { return m_nPriority; }	// �D�揇�ʎ擾
	void SetEnableDisp(bool bDisp);		// �`��ݒ�
	bool IsDisp() { return m_bDisp; }					// �`��󋵎擾
	void SetEnableHitstopMove() { m_bHitstopMove = true; }	// �q�b�g�X�g�b�v���ɓ����t���O�L��

	int SetEffectParent(CEffect3D *pEffect3D);	// �G�t�F�N�g�ݒ�
	CEffect3D *GetEffectParent(int nIdx);	// �e�ݒ肵���G�t�F�N�g�擾
	int GetEffectParentNum();			// �e�ݒ肵���G�t�F�N�g�̐��擾
	void ReleaseEffect(int nIdx);			// �G�t�F�N�g�̉��
	void UninitEffect();				// �G�t�F�N�g�̉��

	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	static const int GetNumAll() { return m_nNumAll; }

	bool IsDeath();						// ���S�̔���
	void SetType(const TYPE type);
	TYPE GetType() const;
	virtual CObject *GetObject();
	virtual CObject2D *GetObject2D();
	virtual CObject3D *GetObject3D();
	virtual CObject3DMesh *GetObject3DMesh();
	virtual CObjectX *GetObjectX();
	virtual CObjectChara *GetObjectChara();

protected:

	void Release();	// �J������

private:

	static void DrawNone(const LAYER layer, int nPriority);	// �ʏ�`��
	static void DrawZSort(const LAYER layer, int nPriority);	// Z�\�[�g�`��

	MyLib::Vector3 m_pos;			// �ʒu
	MyLib::Vector3 m_posOld;		// �O��̈ʒu
	MyLib::Vector3 m_posOrigin;	// ���̈ʒu
	MyLib::Vector3 m_rot;			// ����
	MyLib::Vector3 m_rotOrigin;	// ���̌���
	MyLib::Vector3 m_move;			// �ړ���

	int m_nPriority;		// �D�揇��
	LAYER m_Layer;	// ���C���[��
	static int m_nNumAll;	// �I�u�W�F�N�g�̑���
	TYPE m_type;			// ���
	bool m_bDeath;		// ���S�t���O
	bool m_bDisp;		// �`��t���O
	CEffect3D *m_pEffect[mylib_const::MAX_OBJ];	// �G�t�F�N�g�̃|�C���^
	int m_nNumEffectParent;	// �G�t�F�N�g�̐e�ݒ肵����
	bool m_bHitstopMove;		// �q�b�g�X�g�b�v���ɓ������̃t���O
	static std::map<LAYER, std::map<int, std::vector<CObject*>>> m_pObj;	// �I�u�W�F�N�g�i�[�p

};

#endif