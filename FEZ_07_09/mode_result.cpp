//=============================================================================
//
// ���U���g���[�h [mode_result.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "mode_result.h"
#include "bg_result.h"
#include "ui_coin.h"
#include "ui_get_coin.h"
#include "item.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResultMode::CResultMode()
{
	m_pCoinUI = NULL;		//��������Ă���R�C������UI�̃|�C���^
	m_pGetCoinUI = NULL;	//�擾�����R�C������UI�̃|�C���^
	m_nCreateCoin = 0;
	m_nGetCoin = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResultMode::~CResultMode()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CResultMode * CResultMode::Create()
{
	//���U���g���[�h�̃|�C���^
	CResultMode * pResultMode = NULL;
	//�������U���g���[�h�̃|�C���^��NULL�̏ꍇ
	if (pResultMode == NULL)
	{
		//���U���g���[�h�̃������m��
		pResultMode = new CResultMode;
		//�������U���g���[�h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pResultMode != NULL)
		{
			//�����������֐��Ăяo��
			pResultMode->Init();
		}
	}
	//���U���g���[�h�̃|�C���^��Ԃ�	
	return pResultMode;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CResultMode::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (pSound != NULL)
	{
		//�T�E���h�̒�~
		pSound->StopSound();
		//���U���g��BGM���Đ�
		pSound->Play(CSound::SOUND_LABEL_BGM_RESULT);
	}
	//�����S���������֐��Ăяo��
	InitCreateAll();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CResultMode::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CResultMode::Update(void)
{
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CResultMode::Draw(void)
{
}

//=============================================================================
// �����S���������֐�
//=============================================================================
void CResultMode::InitCreateAll(void)
{
	LoadCreateCoin();
	LoadGetCoin();
	//���U���g��ʂ̔w�i����
	CResultBG::Create();
	//��������Ă���R�C������UI�̐���
	m_pCoinUI = CCoinUI::Create();
	//�擾�����R�C������UI�̐���
	m_pGetCoinUI = CGetCoinUI::Create();
	m_pCoinUI->SetCoin(m_nCreateCoin);
	m_pGetCoinUI->SetGetCoin(m_nGetCoin);
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CResultMode::Input(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard * pKeyboard = CManager::GetInput();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice(JOYSTICK_1P);
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	//LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect(JOYSTICK_1P);
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//����ENTER�L�[���̓W���C�X�e�B�b�N��A�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A, JOYSTICK_1P))
	{
		//�^�C�g�����[�h�ɑJ�ڂ���
		CManager::StartFade(CManager::MODE_TITLE);
	}
}

void CResultMode::LoadCreateCoin(void)
{
	//�t�@�C���̃|�C���^
	FILE *pFile;
	//�t�@�C���̓ǂݍ���
	pFile = fopen("data/TEXT/CreateCoinData.txt", "r");
	//�t�@�C����NULL�`�F�b�N
	if (pFile != NULL)
	{
		//���͏��ǂݍ���
		fscanf(pFile, "%d", &m_nCreateCoin);
		//�t�@�C�������
		fclose(pFile);
	}
}

void CResultMode::LoadGetCoin(void)
{
	//�t�@�C���̃|�C���^
	FILE *pFile;
	//�t�@�C���̓ǂݍ���
	pFile = fopen("data/TEXT/GetCoinData.txt", "r");
	//�t�@�C����NULL�`�F�b�N
	if (pFile != NULL)
	{
		//���͏��ǂݍ���
		fscanf(pFile, "%d", &m_nGetCoin);
		//�t�@�C�������
		fclose(pFile);
	}
}