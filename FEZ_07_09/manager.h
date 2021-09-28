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
class CJoystick;
class CCamera;
class CLight;
class CPlayer;
class CCollisionDetection;
class CSound;
class CGameMode;
class CFade;
class CPlayerHook;

//*****************************************************************************
// �}�l�[�W���[�N���X��`
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_STAGE_SELECT,
		MODE_GAME_STAGE1,
		MODE_GAME_STAGE2,
		MODE_GAME_STAGE3,
		MODE_RESULT,
		MODE_MAX
	}MODE;
	// �����o�֐�
	CManager();													 // �R���X�g���N�^
	~CManager();												 // �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);  // ����������
	void Uninit(void);											 // �I������
	void Update(void);											 // �X�V����
	void Draw(void);											 // �`�揈��
	void Load(void);											 // ���f���E�e�N�X�`���ǂݍ���
	void Unload(void);											 // ���f���E�e�N�X�`���j��
	static void StartFade(MODE mode);
	static void StopFade(void);
	static void SetMode(MODE Mode);
	static MODE GetMode(void) { return m_Mode; }
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard *GetInput(void) { return m_pInput; }
	static CJoystick *GetJoystick(void) { return m_pJoystick; }
	static CCamera *GetCamera(void) { return m_pCamera; }

	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CPlayerHook *GetPlayerHook(void) { return m_pPlayerHook; }
	static CSound *GetSound(void) { return m_pSound; }
	static CGameMode *GetGameMode(void) { return m_pGameMode; }
	static CFade * GetFade(void) { return m_pFade; }

	static void SetPlayerHook(CPlayerHook *pPlayerHook) { m_pPlayerHook = pPlayerHook; }
private:
	// �����o�ϐ�
	static MODE				 m_Mode;					  //���[�h
	static bool				 m_bUseFade;				  //�t�F�[�h�̎g�p���

	static CRenderer		*m_pRenderer;
	static CSound           *m_pSound;
	static CInputKeyboard   *m_pInput;
	static CJoystick		*m_pJoystick;				//�W���C�X�e�B�b�N�̃|�C���^
	static CCamera			*m_pCamera;

	static CLight			*m_pLight;		                     // ���C�g�̃|�C���^
	static CPlayer          *m_pPlayer;
	static CPlayerHook		*m_pPlayerHook;
	static CCollisionDetection *m_CollisionDetection;

	static CGameMode		*m_pGameMode;				  // �Q�[�����[�h�̃|�C���^
	static CFade			*m_pFade;					  //�t�F�[�h�̃|�C���^

};

#endif