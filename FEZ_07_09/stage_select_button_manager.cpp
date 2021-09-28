//=============================================================================
//
// �X�e�[�W�I���{�^���}�l�[�W���[ [stage_select_button_manager.cpp]
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
#include "stage_select_button_manager.h"
#include "button_stage1.h"
#include "button_stage2.h"
#include "button_stage3.h"
#include "button_cancel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STAGE1_BUTTON_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))							//�X�e�[�W1�{�^���̈ʒu
#define STAGE2_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	//�X�e�[�W2�{�^���̈ʒu
#define STAGE3_BUTTON_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))							//�X�e�[�W3�{�^���̈ʒu
#define INPUT_INTERVAL (10)																//���͊Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStageSelectButtonManager::CStageSelectButtonManager(OBJ_TYPE nObjectType) : CObject(nObjectType)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//�{�^���̃|�C���^
	m_nButton = BUTTON_NONE;						//�{�^��
	m_nInputCount = 0;								//���͊Ԋu
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStageSelectButtonManager::~CStageSelectButtonManager()
{
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CStageSelectButtonManager * CStageSelectButtonManager::Create(void)
{
	//�X�e�[�W�I���{�^���}�l�[�W���[�̃|�C���^
	CStageSelectButtonManager * pStageSelectButtonManager = NULL;
	//�X�e�[�W�I���{�^���}�l�[�W���[�̃|�C���^NULL�̏ꍇ
	if (pStageSelectButtonManager == NULL)
	{
		//�X�e�[�W�I���{�^���}�l�[�W���[�̃������m��
		pStageSelectButtonManager = new CStageSelectButtonManager;
		//�X�e�[�W�I���{�^���}�l�[�W���[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pStageSelectButtonManager != NULL)
		{
			//�X�e�[�W�I���{�^���}�l�[�W���[�̏����������֐��Ăяo��
			pStageSelectButtonManager->Init();
		}
	}
	//�X�e�[�W�I���{�^���}�l�[�W���[�̃|�C���^��Ԃ�
	return pStageSelectButtonManager;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CStageSelectButtonManager::Init(void)
{
	//�����S�������֐��Ăяo��
	InitCreateAll();
	//�{�^���̏����ݒ�
	m_nButton = BUTTON_STAGE1;
	//�S�Ẵ{�^����I�����̐F�ɂ���
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//�{�^���̏����I�������֐��Ăяo��
		m_apButton[nCount]->SelectColor();
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CStageSelectButtonManager::Uninit(void)
{
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CStageSelectButtonManager::Update(void)
{
	//�I�������֐��Ăяo��
	Select();
	//���͏����֐��Ăяo��
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CStageSelectButtonManager::Draw(void)
{
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CStageSelectButtonManager::Input(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard * pKeyboard = CManager::GetInput();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice(JOYSTICK_1P);
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect(JOYSTICK_1P);
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_LEFT))
	{
		//���݂̃{�^�������Z����
		m_nButton--;
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//����{�^������X�e�B�b�N�����͂��ꂽ�ꍇ
	if (lpDIDevice != NULL &&js.rgdwPOV[0] == 0 || lpDIDevice != NULL &&js.lY == -1000)
	{
		//���͊Ԋu�����Z����
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//���݂̃{�^�������Z����
			m_nButton--;
			//�{�^���̑I�������Đ������֐��Ăяo��
			m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
		}
	}
	//�E���L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_RIGHT))
	{
		//���݂̃{�^�������Z����
		m_nButton++;
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//�����{�^�������X�e�B�b�N�����͂��ꂽ�ꍇ
	if (lpDIDevice != NULL &&js.rgdwPOV[0] == 18000 || lpDIDevice != NULL &&js.lY == 1000)
	{
		//���͊Ԋu�����Z����
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//���݂̃{�^�������Z����
			m_nButton++;
			//�{�^���̑I�������Đ������֐��Ăяo��
			m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
		}
	}
	//����ENTER�L�[���̓W���C�X�e�B�b�N��A�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A, JOYSTICK_1P))
	{
		//�{�^���̃v���X�����֐��Ăяo��
		m_apButton[m_nButton]->Press();
	}
	//�����L�����Z���L�[�����͂��ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_B))
	{
		//�L�����Z���{�^���̃v���X�����֐��Ăяo��
		m_apButton[BUTTON_CANCEL]->Press();
	}
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CStageSelectButtonManager::Select(void)
{
	//�������݂̃{�^�����X�e�[�W1�{�^����艺��������
	if (m_nButton < BUTTON_STAGE1)
	{
		//���݂̃{�^�����X�e�[�W3�{�^���ɂ���
		m_nButton = BUTTON_STAGE3;
	}
	//�������݂̃{�^�����X�e�[�W3�{�^�����z������
	if (m_nButton > BUTTON_STAGE3)
	{
		//���݂̃{�^�����X�e�[�W1�{�^���ɂ���
		m_nButton = BUTTON_STAGE1;
	}
	//�{�^���̍ő吔����
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//�{�^���̑I������ĂȂ����̐F�ύX�����֐��Ăяo��
		m_apButton[nCount]->NotSelectShrink();
	}
	//�{�^���̑I�����F�ύX�����֐��Ăяo��
	m_apButton[m_nButton]->SelectExpansion();
}

//=============================================================================
// �������������֐�
//=============================================================================
void CStageSelectButtonManager::InitCreateAll(void)
{
	//�X�e�[�W1�{�^���̐���
	m_apButton[BUTTON_STAGE1] = CStage1Button::Create(D3DXVECTOR3(STAGE2_BUTTON_POSITION.x - 500.0f, STAGE2_BUTTON_POSITION.y, STAGE2_BUTTON_POSITION.z));
	//�X�e�[�W2�{�^���̐���
	m_apButton[BUTTON_STAGE2] = CStage2Button::Create(STAGE2_BUTTON_POSITION);
	//�X�e�[�W3�{�^���̐���
	m_apButton[BUTTON_STAGE3] = CStage3Button::Create(D3DXVECTOR3(STAGE2_BUTTON_POSITION.x + 500.0f, STAGE2_BUTTON_POSITION.y, STAGE2_BUTTON_POSITION.z));
	//�L�����Z���{�^���̐���
	m_apButton[BUTTON_CANCEL] = CCancelButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 12, SCREEN_HEIGHT - 100.0f, 0.0f));
}