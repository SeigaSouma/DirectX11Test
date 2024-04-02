//=============================================================================
//
// ����(�}�E�X)���� [input_mouse.h]
// Author : ���n�Ή�
//
//=============================================================================

#ifndef _INPUT_MOUSE_H_	//���̃}�N����`������Ă��Ȃ�������
#define _INPUT_MOUSE_H_	//��d�C���N���[�h�h�~�̃}�N�����`����

#include "input.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �}�E�X�N���X
class CInputMouse : public CInput
{
public:

	// �񋓌^��`
	enum BUTTON
	{
		BUTTON_LEFT = 0,
		BUTTON_RIGHT,
		BUTTON_WHEEL,
		BUTTON_SIDE_1,
		BUTTON_SIDE_2,
		BUTTON_MAX
	};

	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(BUTTON nKey);
	MyLib::Vector3 GetMouseMove();

	static CInputMouse* GetInstance() { return m_pThisPtr; }	// �C���X�^���X�擾
	static CInputMouse* Create(HINSTANCE hInstance, HWND hWnd);	// ��������

private:

	//=============================
	// �����o�ϐ�
	//=============================
	DIMOUSESTATE2 m_MouseState;			// �S���͏��̕ۊ�
	DIMOUSESTATE2 m_MouseStateTrigger;	// �g���K�[���
	DIMOUSESTATE2 m_MouseStateRerease;	// �����[�X���
	DIMOUSESTATE2 m_MouseStateRepeat;	// ���s�[�g���
	BYTE m_aOldState[BUTTON::BUTTON_MAX];	// �O��̓��͏���ۑ�

	static CInputMouse* m_pThisPtr;	// ���g�̃|�C���^
};

#endif