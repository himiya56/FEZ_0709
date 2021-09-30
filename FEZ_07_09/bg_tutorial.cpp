//=============================================================================
//
// �`���[�g���A����ʂ̔w�i [bg_tutorial.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "bg_tutorial.h"
#include "joystick.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define KEYBOARD_GUID_TEXTURE ("data/TEXTURE/bg_title.png")			//�e�N�X�`���̃p�X
#define JOYSTICK_GUID_TEXTURE ("data/TEXTURE/Tutorial_FEZ.png")			//�e�N�X�`���̃p�X
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	//�ʒu
#define SIZE (D3DXVECTOR3(1080.0f,1920.0f,0.0f))						//�T�C�Y

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTutorialBG::m_apTexture[TEXTURE_MAX] = {};	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorialBG::CTutorialBG()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorialBG::~CTutorialBG()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CTutorialBG::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,			//�f�o�C�X�ւ̃|�C���^
		KEYBOARD_GUID_TEXTURE,					//�t�@�C���̖��O
		&m_apTexture[TEXTURE_KEYBOARD_GUID]);	//�ǂݍ��ރ������[
												//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,			//�f�o�C�X�ւ̃|�C���^
		JOYSTICK_GUID_TEXTURE,					//�t�@�C���̖��O
		&m_apTexture[TEXTURE_JOYSTICK_GUID]);	//�ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CTutorialBG::TextureUnload(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//�����e�N�X�`���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (m_apTexture[nCount] != NULL)
		{
			//�e�N�X�`���̔j�������֐��Ăяo��
			m_apTexture[nCount]->Release();
			//�e�N�X�`����NULL�ɂ���
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CTutorialBG * CTutorialBG::Create(void)
{
	//�`���[�g���A����ʔw�i�̃|�C���^
	CTutorialBG * pTutorialBG = NULL;
	//�`���[�g���A����ʔw�i�̃|�C���^��NULL�̏ꍇ
	if (pTutorialBG == NULL)
	{
		//�`���[�g���A����ʔw�i�̃������m��
		pTutorialBG = new CTutorialBG;
		//�`���[�g���A����ʔw�i�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pTutorialBG != NULL)
		{
			//�`���[�g���A����ʔw�i�̏����������֐��Ăяo��
			pTutorialBG->Init();
		}
	}
	//�`���[�g���A����ʔw�i�̃|�C���^��Ԃ�
	return pTutorialBG;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CTutorialBG::Init(void)
{
	//�|���S��2D�̏����������֐��Ăяo��
	CPolygon2D::Init();
	//�e�N�X�`���̐ݒ�
	SetTexUV(0.0f, 1.0f, 0.0f, 1.0f);
	//�ʒu��ݒ�
	SetPos(POSITION);
	//�T�C�Y�ݒ�
	SetSize(SIZE.y, SIZE.x);
	//�����W���C�X�e�B�b�N��NULL��������
	if (CJoystick::GetDevice(JOYSTICK_1P) == NULL)
	{
		//�e�N�X�`���̊��蓖��
		BindTexture(m_apTexture[TEXTURE_KEYBOARD_GUID]);
	}
	else
	{
		//�e�N�X�`���̊��蓖��
		BindTexture(m_apTexture[TEXTURE_JOYSTICK_GUID]);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CTutorialBG::Uninit(void)
{
	//�|���S��2D�̏I�������֐��Ăяo��
	CPolygon2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CTutorialBG::Update(void)
{
	//�|���S��2D�̍X�V�����֐��Ăяo��
	CPolygon2D::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CTutorialBG::Draw(void)
{
	//�|���S��2D�̕`�揈���֐��Ăяo��
	CPolygon2D::Draw();
}