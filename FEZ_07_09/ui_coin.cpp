//=============================================================================
//
// �R�C����UI [ui_coin.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <cmath>
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "number.h"
#include "ui_coin.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4 - 35.0f,SCREEN_HEIGHT / 2+ SCREEN_HEIGHT / 4 - 15.0f,0.0f))
#define SIZE (D3DXVECTOR3(47.0f,47.0f,0.0f))
#define MINIMUM_INTEGER (0)
#define MINIMUM_COUNT_NUMBER (0)
#define NUM_CONVERSION (10.0f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCoinUI::CCoinUI(OBJ_TYPE nPriority) :CObject(nPriority)
{
	memset(m_apNumberTexture, NULL, sizeof(m_apNumberTexture));	//UI�p�e�N�X�`���ւ̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCoinUI::~CCoinUI()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CCoinUI * CCoinUI::Create(void)
{
	//�X�R�A��UI�̃|�C���^
	CCoinUI * pCoinUI = NULL;
	//�����X�R�A��UI�̃|�C���^��NULL�̏ꍇ
	if (pCoinUI == NULL)
	{
		//�X�R�A��UI�̃������m��
		pCoinUI = new CCoinUI;
		//�����X�R�A��UI�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pCoinUI != NULL)
		{
			//�����������֐��Ăяo��
			pCoinUI->Init();
		}
	}
	return pCoinUI;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CCoinUI::Init(void)
{
	//�ő包������
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//�����̃e�N�X�`���̐��������֐��Ăяo��
		m_apNumberTexture[nCount] = CNumber::Create(D3DXVECTOR3(POSITION.x - (SIZE.x * nCount), POSITION.y, 0.0f), SIZE);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CCoinUI::Uninit(void)
{
	//�ő包������
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//���������̃e�N�X�`����NULL����Ȃ��ꍇ
		if (m_apNumberTexture[nCount] != NULL)
		{
			//�����̃e�N�X�`���̏I�������֐��Ăяo��
			m_apNumberTexture[nCount]->Uninit();
			//�����̃e�N�X�`���̃������j��
			delete m_apNumberTexture[nCount];
			//�����̃e�N�X�`����NULL�ɂ���
			m_apNumberTexture[nCount] = NULL;
		}
	}
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CCoinUI::Update(void)
{
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CCoinUI::Draw(void)
{
	//�ő包������
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//�����̃e�N�X�`���̕`�揈���֐��Ăяo��
		m_apNumberTexture[nCount]->Draw();
	}
}

//=============================================================================
// �X�R�A�ݒ�֐�
//=============================================================================
void CCoinUI::SetCoin(int nCoin)
{
	int integer = MINIMUM_INTEGER;			//�v�Z�p�ϐ�
	int nCntNumber = MINIMUM_COUNT_NUMBER;	//�ԍ��J�E���^
											//�ő包������
	for (int nCntDigit = 1; nCntDigit <= MAX_NUMBER; nCntDigit++, nCntNumber++)
	{
		//�o�������l�̌����̈��̌����̐������o
		integer = int(nCoin / std::pow(NUM_CONVERSION, nCntDigit));
		//�؂�̂Ă��������������|����
		integer = int(integer * std::pow(NUM_CONVERSION, nCntDigit));
		//������ݒ肷���̌����̐����Ɖ��̌����̐����������Ď�菜��
		m_apNumberTexture[nCntNumber]->SetNumber(int((nCoin - integer) / std::pow(NUM_CONVERSION, nCntDigit - 1)));
	}
}
