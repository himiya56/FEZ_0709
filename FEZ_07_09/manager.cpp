//=============================================================================
//
// �I�u�W�F�N�g�Ǘ����� [manager.cpp]
// Author : ��{ ��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "object.h"
#include "input.h"
#include "joystick.h"
#include "Keyboard.h"
#include "camera.h"
#include "light.h"
#include "fade.h"
#include "mode_title.h"
#include "mode_stage_select.h"
#include "mode_game.h"
#include "mode_result.h"
#include "button_exit.h"
#include "button_start.h"
#include "button_tutorial.h"
#include "button_stage1.h"
#include "button_stage2.h"
#include "button_stage3.h"
#include "button_stage_select.h"
#include "button_back_to_title.h"
#include "button_cancel.h"
#include "bg_stage_select.h"
#include "bg_dot.h"
#include "bg_title.h"
#include "logo_title.h"

#include "testObj.h"
#include "player.h"
#include "collisiondetection.h"
#include "player_hook.h"
#include "spike.h"
#include "goal.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInput = NULL;
CJoystick * CManager::m_pJoystick = nullptr;			//�W���C�X�e�B�b�N�̃|�C���^
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CPlayerHook *CManager::m_pPlayerHook = NULL;
CManager::MODE  CManager::m_Mode = MODE_NONE;		//���[�h
bool CManager::m_bUseFade = false;					//�t�F�[�h�̎g�p���
CSound * CManager::m_pSound = NULL;
CGameMode * CManager::m_pGameMode = NULL;
CFade * CManager::m_pFade = NULL;					//�t�F�[�h�ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�C���X�^���X�����E����������
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	m_pInput = new CInputKeyboard;
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{
		return -1;
	}
	//�����W���C�X�e�B�b�N�̃|�C���^��NULL�̏ꍇ
	if (m_pJoystick == NULL)
	{
		//�W���C�X�e�B�b�N�̃������m��
		m_pJoystick = new CJoystick;
		//�����W���C�X�e�B�b�N�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (m_pJoystick != NULL)
		{
			//�W���C�X�e�B�b�N�̏����������֐��Ăяo��
			m_pJoystick->Init(hInstance, hWnd);
		}
	}
	// ���C�g�̐���
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	m_pCamera = CCamera::Create();
	//�����t�F�[�h�̃|�C���^��NULL�̏ꍇ
	if (m_pFade == NULL)
	{
		//�t�F�[�h�̐��������֐��Ăяo��
		m_pFade = CFade::Create(m_Mode);
	}
	//�����T�E���h�̃|�C���^��NULL�̏ꍇ
	if (m_pSound == NULL)
	{
		//�T�E���h�̃������m��
		m_pSound = new CSound;
		//�����T�E���h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pSound != nullptr)
		{
			//�T�E���h�̏����������֐��Ăяo��
			m_pSound->Init(hWnd);
		}
	}
	// �e�N�X�`���̓ǂݍ���
	Load();

	CTestObj::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//CTestObj::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f));
	//CTestObj::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f));

	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 170.0f, 0.0f), PLAYER_SIZE);

	// ���[�h�̐ݒ�
	SetMode(MODE_TITLE);

	return 0;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// �I������
	CObject::ReleaseAll();

	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		//�������j��
		delete m_pInput;
		m_pInput = NULL;
	}
	//�����W���C�X�e�B�b�N�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pJoystick != NULL)
	{
		//�W���C�X�e�B�b�N�̏I�������֐��Ăяo��
		m_pJoystick->Uninit();
		//�W���C�X�e�B�b�N�̃������j��
		delete m_pJoystick;
		//�W���C�X�e�B�b�N�̃|�C���^��nullptr�ɂ���
		m_pJoystick = nullptr;
	}
	//�����T�E���h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pSound != NULL)
	{
		//�T�E���h�̒�~
		m_pSound->StopSound();
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		//�������j��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	//�����t�F�[�h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pFade != NULL)
	{
		//�t�F�[�h�̏I�������֐��Ăяo��
		m_pFade->Uninit();
		//�t�F�[�h�̃������j��
		delete m_pFade;
		//�t�F�[�h�̃|�C���^��NULL�ɂ���
		m_pFade = NULL;
	}
	// �e�N�X�`���̔j��
	Unload();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �X�V����
	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}
	//�����W���C�X�e�B�b�N�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pJoystick != NULL)
	{
		//�W���C�X�e�B�b�N�̍X�V�����֐��Ăяo��
		m_pJoystick->Update();
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	//�����t�F�[�h���ꂽ��
	if (m_bUseFade == true)
	{
		//�����t�F�[�h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (m_pFade != NULL)
		{
			//�t�F�[�h�̍X�V�����֐��Ăяo��
			m_pFade->Update();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}


//=============================================================================
// �t�F�[�h�J�n�����֐�
//=============================================================================
void CManager::StartFade(MODE mode)
{
	//���[�h��ݒ肷��
	m_Mode = mode;
	//�t�F�[�h������
	m_bUseFade = true;
}

//=============================================================================
// �t�F�[�h��~�����֐�
//=============================================================================
void CManager::StopFade(void)
{
	//�t�F�[�h����߂�
	m_bUseFade = false;
}

//=============================================================================
// ���[�h�ݒ�֐�
//=============================================================================
void CManager::SetMode(MODE Mode)
{
	//�I�u�W�F�N�g�̑S�j�������֐��Ăяo��
	CObject::ReleaseAll();
	//���[�h��ݒ肷��
	m_Mode = Mode;
	//�e���[�h�̏���
	switch (m_Mode)
	{
	case MODE_TITLE:
		//�^�C�g�����[�h�̐��������֐��Ăяo��
		CTitleMode::Create();
		break;
	case MODE_STAGE_SELECT:
		//�X�e�[�W�I�����[�h�̐��������֐��Ăяo��
		CStageSelectMode::Create();
		break;
	case MODE_GAME_STAGE1:
		//�Q�[�����[�h�̐��������֐��Ăяo��
		m_pGameMode = CGameMode::Create(CGameMode::STAGE_1);
		break;
	case MODE_GAME_STAGE2:
		//�Q�[�����[�h�̐��������֐��Ăяo��
		m_pGameMode = CGameMode::Create(CGameMode::STAGE_2);
		break;
	case MODE_GAME_STAGE3:
		//�Q�[�����[�h�̐��������֐��Ăяo��
		m_pGameMode = CGameMode::Create(CGameMode::STAGE_3);
		break;
	case MODE_RESULT:
		//���U���g���[�h�̐��������֐��Ăяo��
		CResultMode::Create();
		break;
	default:
		break;
	}
}

//=============================================================================
// ���f���E�e�N�X�`���ǂݍ��ݏ���
//=============================================================================
void CManager::Load(void)
{
	CTestObj::Load();
	CPlayerHook::Load();
	CExitButton::TextureLoad();
	CStartButton::TextureLoad();
	CTutorialButton::TextureLoad();
	CStage1Button::TextureLoad();
	CStage2Button::TextureLoad();
	CStage3Button::TextureLoad();
	CCollisionDetection::Load();
	CSpike::Load();
	CBlock::Load();
	CStageSelectBG::TextureLoad();
	CStageSelectButton::TextureLoad();
	CBackToTitleButton::TextureLoad();
	CCancelButton::TextureLoad();
	CDotBG::TextureLoad();
	CTitleBG::TextureLoad();
	CTitleLogo::TextureLoad();
}

//=============================================================================
// ���f���E�e�N�X�`���j������
//=============================================================================
void CManager::Unload(void)
{
	CTestObj::Unload();
	CPlayerHook::Unload();
	CExitButton::TextureUnload();
	CStartButton::TextureUnload();
	CTutorialButton::TextureUnload();
	CStage1Button::TextureUnload();
	CStage2Button::TextureUnload();
	CStage3Button::TextureUnload();
	CCollisionDetection::Unload();
	CSpike::Unload();
	CBlock::Unload();
	CStageSelectBG::TextureUnload();
	CStageSelectButton::TextureUnload();
	CBackToTitleButton::TextureUnload();
	CCancelButton::TextureUnload();
	CDotBG::TextureUnload();
	CTitleBG::TextureUnload();
	CTitleLogo::TextureUnload();
}
