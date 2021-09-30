//=============================================================================
//
// �Q�[�����[�h [mode_game.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
//#include "sound.h"
#include "light.h"
#include "camera.h"
#include "keyboard.h"
#include "joystick.h"
#include "mode_game.h"
#include "player_hook.h"
#include "player_rotation.h"
#include "testObj.h"
#include "spike.h"
#include "collisiondetection.h"
#include "sound.h"
#include "player.h"
#include "goal.h"
#include "testObj.h"
#include "Stage.h"
#include "sky.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CPlayerHook *CGameMode::m_pPlayerHook = NULL;
CPlayerRotation *CGameMode::m_pPlayerRotation = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameMode::CGameMode()
{
	m_bCreatePause = false;		//�|�[�Y���g�p���Ă邩
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameMode::~CGameMode()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CGameMode * CGameMode::Create(STAGE stage)
{
	//�Q�[�����[�h�̃|�C���^
	CGameMode * pGameMode = NULL;
	//�����Q�[�����[�h�̃|�C���^��NULL�������ꍇ
	if (pGameMode == NULL)
	{
		//�Q�[�����[�h�̃������m��
		pGameMode = new CGameMode;
		//�����Q�[�����[�h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pGameMode != NULL)
		{
			pGameMode->m_Stage = stage;	//�X�e�[�W�̐ݒ�

			//�Q�[�����[�h�̏������֐��Ăяo��
			pGameMode->Init();
		}
	}
	//�Q�[�����[�h�̃|�C���^��Ԃ�
	return pGameMode;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CGameMode::Init(void)
{
	//�������������֐��Ăяo��(����)
	InitCreate();
	//�e�X�e�[�W�̐���
	InitStageCreate();
	////�T�E���h�̎擾
	//CSound * pSound = CManager::GetSound();
	////�����T�E���h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	//if (pSound != nullptr)
	//{
	//	//���O���͂�BGM��~ 
	//	pSound->StopSound(CSound::SOUND_LABEL_BGM_NAME);
	//}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameMode::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGameMode::Update(void)
{
	////���͏����֐��Ăяo��
	//Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// �������������֐�
//=============================================================================
void CGameMode::InitCreate(void)
{
}

//=============================================================================
// �����e�X�e�[�W���������֐�
//=============================================================================
void CGameMode::InitStageCreate(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (pSound != NULL)
	{
		//�T�E���h�̒�~
		pSound->StopSound();
		switch (m_Stage)
		{
		case STAGE_1:
			//�X�e�[�W1��BGM���Đ�
			pSound->Play(CSound::SOUND_LABEL_BGM_STAGE1);

			m_pPlayerHook = CPlayerHook::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 1.0f, 75.0f * -2.0f), BLOCK_SIZE);
			m_pPlayerRotation = CPlayerRotation::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 2.0f + 70.0f, 75.0f * 0.0f), BLOCK_SIZE);

			//75.0f * 27.0f, 75.0f * 30.0f

			CStage::Create(D3DXVECTOR3(75.0f / 2.0f, 75.0f * -2.2f, -75.0f / 2.0f));
			CSky::Create(D3DXVECTOR3(0.0f, 75.0f * 15.0f, 75.0f * 13.5f), D3DXVECTOR2(0.0f, 0.25f));

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 0.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 3.0f, 75.0f * 1.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 2.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 2.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 3.0f, 75.0f * 2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 4.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 4.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -2.0f, 75.0f * 5.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 6.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 7.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 8.0f, 75.0f * -5.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 9.0f, 75.0f * -4.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 10.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 10.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 10.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 10.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 10.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 10.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 10.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 10.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 11.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_RED);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 12.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_RED);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 13.0f, 75.0f * -3.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 14.0f, 75.0f * -3.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON, CCollisionDetection::BUTTONCOLOR_RED);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 13.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CSpike::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 14.0f, 75.0f * -2.0f));

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 14.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_RED);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 15.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_RED);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 16.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 16.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 16.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 16.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 16.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 16.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 16.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 16.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 17.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 18.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_BLUE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 19.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_BLUE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 3.0f, 75.0f * 19.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 4.0f, 75.0f * 19.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CSpike::Create(D3DXVECTOR3(75.0f * 3.0f, 75.0f * 20.0f, 75.0f * -1.0f));
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 4.0f, 75.0f * 20.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON, CCollisionDetection::BUTTONCOLOR_BLUE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 19.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 20.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON, CCollisionDetection::BUTTONCOLOR_YELLOW);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 20.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 21.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 3.0f, 75.0f * 22.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 23.0f, 75.0f * -2.0f), BLOCK_SIZE,  CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 23.0f, 75.0f * -2.0f), BLOCK_SIZE,  CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 23.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 23.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 23.0f, 75.0f * 0.0f), BLOCK_SIZE,  CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 23.0f, 75.0f * 1.0f), BLOCK_SIZE,  CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 23.0f, 75.0f * 1.0f), BLOCK_SIZE,   CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 23.0f, 75.0f * 1.0f), BLOCK_SIZE,   CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);

			CGoal::Create(D3DXVECTOR3(75.0f * 0.5f, 75.0f * 25.0f, 75.0f * -0.5f));

			break;
		case STAGE_2:
			break;
		case STAGE_3:
			break;
		default:
			break;
		}
	}
}