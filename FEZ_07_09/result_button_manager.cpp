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
#include "result_button_manager.h"
#include "button_stage_select.h"
#include "button_back_to_title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STAGE_SELECT_BUTTON_POSITION (D3DXVECTOR3(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 4,0.0f)))							//�X�e�[�W�I���{�^���̈ʒu
#define BACK_TO_TITLE_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	//�^�C�g���ɖ߂�{�^���̈ʒu
#define INPUT_INTERVAL (10)																//���͊Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResultButtonManager::CResultButtonManager(OBJ_TYPE nObjectType) : CObject(nObjectType)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//�{�^���̃|�C���^
	m_nButton = BUTTON_NONE;						//�{�^��
	m_nInputCount = 0;								//���͊Ԋu
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResultButtonManager::~CResultButtonManager()
{
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CResultButtonManager * CResultButtonManager::Create(void)
{
	//���U���g�{�^���}�l�[�W���[�̃|�C���^
	CResultButtonManager * pResultButtonManager = NULL;
	//���U���g�{�^���}�l�[�W���[�̃|�C���^NULL�̏ꍇ
	if (pResultButtonManager == NULL)
	{
		//���U���g�{�^���}�l�[�W���[�̃������m��
		pResultButtonManager = new CResultButtonManager;
		//���U���g�{�^���}�l�[�W���[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pResultButtonManager != NULL)
		{
			//���U���g�{�^���}�l�[�W���[�̏����������֐��Ăяo��
			pResultButtonManager->Init();
		}
	}
	//���U���g�{�^���}�l�[�W���[�̃|�C���^��Ԃ�
	return pResultButtonManager;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CResultButtonManager::Init(void)
{
	//�����S�������֐��Ăяo��
	InitCreateAll();
	//�{�^���̏����ݒ�
	m_nButton = BUTTON_STAGE_SELECT;
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
void CResultButtonManager::Uninit(void)
{
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CResultButtonManager::Update(void)
{
	//�I�������֐��Ăяo��
	Select();
	//���͏����֐��Ăяo��
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CResultButtonManager::Draw(void)
{
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CResultButtonManager::Input(void)
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
	//����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN))
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
	//����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_UP))
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
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN)/* || pJoystick->GetJoystickTrigger(JS_A)*/)
	{
		//�{�^���̃v���X�����֐��Ăяo��
		m_apButton[m_nButton]->Press();
	}
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CResultButtonManager::Select(void)
{
	//�������݂̃{�^�����X�e�[�W�I���{�^����艺��������
	if (m_nButton < BUTTON_STAGE_SELECT)
	{
		//���݂̃{�^�����^�C�g���ɖ߂�{�^���ɂ���
		m_nButton = BUTTON_BACK_TO_TITLE;
	}
	//�������݂̃{�^�����^�C�g���ɖ߂�{�^�����z������
	if (m_nButton > BUTTON_BACK_TO_TITLE)
	{
		//���݂̃{�^�����X�e�[�W�I���{�^���ɂ���
		m_nButton = BUTTON_STAGE_SELECT;
	}
	//�{�^���̍ő吔����
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//�{�^���̑I������ĂȂ����̐F�ύX�����֐��Ăяo��
		m_apButton[nCount]->NotSelectColor();
	}
	//�{�^���̑I�����F�ύX�����֐��Ăяo��
	m_apButton[m_nButton]->SelectColor();
}

//=============================================================================
// �������������֐�
//=============================================================================
void CResultButtonManager::InitCreateAll(void)
{
	//�X�e�[�W�I���{�^���̐���
	m_apButton[BUTTON_STAGE_SELECT] = CStageSelectButton::Create(STAGE_SELECT_BUTTON_POSITION);
	//�^�C�g���ɖ߂�{�^���̐���
	m_apButton[BUTTON_BACK_TO_TITLE] = CBackToTitleButton::Create(BACK_TO_TITLE_POSITION);
}