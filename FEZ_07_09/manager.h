//=============================================================================
//
// �}�l�[�W���[ [manager.h]
// Author : ��{ ��
//
//=============================================================================

// ��d�C���N���[�h�h�~�p
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CCamera;
class CLight;
class CPlayer;
class CCollisionDetection;

//*****************************************************************************
// �}�l�[�W���[�N���X��`
//*****************************************************************************
class CManager
{
public:
	// �����o�֐�
	CManager();													 // �R���X�g���N�^
	~CManager();												 // �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);  // ����������
	void Uninit(void);											 // �I������
	void Update(void);											 // �X�V����
	void Draw(void);											 // �`�揈��
	void Load(void);											 // ���f���E�e�N�X�`���ǂݍ���
	void Unload(void);											 // ���f���E�e�N�X�`���j��

	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard *GetInput(void) { return m_pInput; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CCollisionDetection *GetCollisionDetection(void) { return m_CollisionDetection; }
private:
	// �����o�ϐ�
	static CRenderer		*m_pRenderer;
	static CInputKeyboard   *m_pInput;
	static CCamera			*m_pCamera;
	static CLight			*m_pLight;		                     // ���C�g�̃|�C���^
	static CPlayer          *m_pPlayer;
	static CCollisionDetection *m_CollisionDetection;
};

#endif