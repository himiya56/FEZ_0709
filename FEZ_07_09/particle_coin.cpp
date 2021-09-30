//=============================================================================
//
// �R�C���̃p�[�e�B�N������ [particle_coin.cpp]
// Author : �����D�I
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "particle_coin.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define COIN_POS		(D3DXVECTOR3(pos.x,pos.y,pos.z))					// �ʒu
#define COIN_SIZE		(D3DXVECTOR3(50.0f,50.0f,0.0f))						// �T�C�Y
#define COIN_ROT		(D3DXVECTOR3(0.0f,0.0f,0.0f))						// ����
#define COIN_COLOR		(D3DXCOLOR(0.0f,1.0f,1.0f,1.0f))					// �F
#define ADD_ROT_VALUE	(D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(15.0f)))		// �p�x����
#define COIN_MOVE		(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*4.0f, sinf(D3DXToRadian(fAngle))*4.0f,0.0f))	// �ړ�
#define MAX_LIFE		(40)												// ���C�t�̍ő�l
#define MIN_LIFE		(0)													// ���C�t�ŏ��l
#define RANDOM_ANGLE	(360)												// �p�x�����_��
#define MAX_PARTICLE	(30)												// �p�[�e�B�N���̍ő吔

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CParticle_Coin::CParticle_Coin()
{
	m_move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_nLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CParticle_Coin::~CParticle_Coin()
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CParticle_Coin * CParticle_Coin::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move)
{
	// �N���X�̃|�C���^
	CParticle_Coin *pCParticle_Coin;

	// �������m��
	pCParticle_Coin = new CParticle_Coin;

	// ���ݒ�
	pCParticle_Coin->SetParticle(pos, size, COIN_ROT, col, CParticle::TEX_TYPE_1);

	// �ړ��ʑ��
	pCParticle_Coin->m_move = move;

	// ����������
	pCParticle_Coin->Init();

	// �������̊J��
	return pCParticle_Coin;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CParticle_Coin::Init(void)
{
	// ����������
	CParticle::Init();

	// ���C�t�ݒ�
	m_nLife = MAX_LIFE;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CParticle_Coin::Uninit(void)
{
	// �I������
	CParticle::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CParticle_Coin::Update(void)
{
	// �X�V
	CParticle::Update();

	// �f�N�������g
	m_nLife--;

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = DEFAULT_VECTOR;//GetRot();

	// �ʒu�X�V
	pos += m_move;

	// �������Z
	rot.z += ADD_ROT_VALUE.z;

	// �ʒu���W�ݒ�
	SetPos(pos);

	// �����ݒ�
	SetRot(rot);

	// ����0.0f�ȉ��̏ꍇ
	if (m_nLife <= MIN_LIFE)
	{
		// �I������
		Uninit();
		return;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CParticle_Coin::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �J�����O�����𖳌�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �`�揈��
	CParticle::Draw();

	// �J�����O������L��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �G�t�F�N�g����
//=============================================================================
void CParticle_Coin::CoinEffect_Create(D3DXVECTOR3 pos)
{
	// �w�肳�ꂽ�������J��Ԃ�
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		// �p�x��360�����_��
		float fAngle = float(rand() % RANDOM_ANGLE);

		// ����
		Create(pos, COIN_SIZE, COIN_COLOR, COIN_MOVE);
	}
}