//=============================================================================
//
// �������� [number.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("data/TEXTURE/ui_number.png")	//�e�N�X�`��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;							//�o�b�t�@�ւ̃|�C���^
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�T�C�Y
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CNumber::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE,							// �t�@�C���̖��O
		&m_pTexture);						// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CNumber::TextureUnload(void)
{
	//�����e�N�X�`����NULL����Ȃ��ꍇ
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CNumber * CNumber::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	//�ԍ��̃e�N�X�`���̃|�C���^
	CNumber * pNumber = NULL;
	//�����ԍ��̃e�N�X�`���̃|�C���^��NULL�̏ꍇ
	if (pNumber == NULL)
	{
		//�ԍ��̃e�N�X�`���̃������m��
		pNumber = new CNumber;
	}
	//�����ԍ��̃e�N�X�`���̃|�C���^��NULL����Ȃ��ꍇ
	if (pNumber != NULL)
	{
		//�ʒu��ݒ肷��
		pNumber->SetPostion(Position);
		//�T�C�Y���擾����
		pNumber->SetSize(Size);
		//�����������֐��Ăяo��
		pNumber->Init();
	}
	//�ԍ��̃e�N�X�`���̃|�C���^��Ԃ�
	return pNumber;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CNumber::Init(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	//���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CNumber::Uninit(void)
{
	//�������_�o�b�t�@��NULL����Ȃ��ꍇ
	if (m_pVtxBuff != NULL)
	{
		//�j�������֐��Ăяo��
		m_pVtxBuff->Release();
		//���_�o�b�t�@��NULL�ɂ���
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CNumber::Update(void)
{
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CNumber::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// �������蓖�ď����֐�
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	//���_���
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �ʒu�ݒ菈���֐�
//=============================================================================
void CNumber::SetPostion(D3DXVECTOR3 Position)
{
	//�ʒu�̐ݒ�
	m_Position = Position;
}

//=============================================================================
// �T�C�Y�ݒ菈���֐�
//=============================================================================
void CNumber::SetSize(D3DXVECTOR3 Size)
{
	//�T�C�Y�̐ݒ�
	m_Size = Size;
}
