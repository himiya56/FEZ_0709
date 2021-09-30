//=============================================================================
//
// �R�C������ [item_coin.cpp]
// Author : �����D�I
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item_coin.h"
#include "manager.h"
#include "renderer.h"
#include "mode_game.h"
#include "player.h"

#include "particle_coin.h"
#include "player_hook.h"
#include "player_rotation.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EFFECT_POS (D3DXVECTOR3(pos.x,pos.y,pos.z + 20.0f))		// �G�t�F�N�g�̈ʒu

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH	CItem_coin::m_pMesh = NULL;
LPD3DXBUFFER CItem_coin::m_pBuffMat = NULL;
DWORD CItem_coin::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CItem_coin::m_pTexture = NULL;

//=============================================================================
// �N���G�C�g����
//=============================================================================
CItem_coin *CItem_coin::Create(D3DXVECTOR3 pos)
{
	CItem_coin *pCoin = NULL;
	pCoin = new CItem_coin;
	// coin�̐����������𑝂₷
	pCoin->Init();
	pCoin->SetPos(pos);
	return pCoin;
}

//=============================================================================
// ���f���̓ǂݍ���
//=============================================================================
HRESULT CItem_coin::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("data/MODEL/Coin_FEZ.x"),
		D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	D3DXCreateTextureFromFile(pDevice, 
		"./data/TEXTURE/coin.png", 
		&m_pTexture);

	return S_OK;

}

//=============================================================================
// ���f���̔j��
//=============================================================================
void CItem_coin::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItem_coin::CItem_coin()
{
	m_rot = DEFAULT_VECTOR;	// �����ݒ�
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItem_coin::~CItem_coin()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItem_coin::Init(void)
{
	AddCreateCoin();
	// ����������
	CItem::Init();
	//BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);

	// �����̏�����
	m_rot = DEFAULT_VECTOR;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItem_coin::Uninit(void)
{
	// �I������
	CItem::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItem_coin::Update(void)
{
	// �X�V����
	CItem::Update();

	// �����蔻��
	CollisionDetection();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItem_coin::Draw(void)
{
	// �`�揈��
	CItem::Draw();
}

//=============================================================================
// �����蔻��
//=============================================================================
void CItem_coin::CollisionDetection(void)
{
	// �ʒu���̎擾
	D3DXVECTOR3 pos = GetPos();

	// �v���C���[���̎擾
	CPlayerHook *pPlayerHook = CGameMode::GetPlayerHook();
	// �v���C���[�̈ʒu���̎擾
	D3DXVECTOR3 playerHookPos = pPlayerHook->GetPos();

	// �v���C���[�ƃA�C�e���ʒu���d�Ȃ����ꍇ
	if (playerHookPos.x >= pos.x - COLLISION_SIZE_ITEM.x / 2 &&
		playerHookPos.x <= pos.x + COLLISION_SIZE_ITEM.x / 2 &&
		playerHookPos.y >= pos.y - COLLISION_SIZE_ITEM.y / 2 &&
		playerHookPos.y <= pos.y + COLLISION_SIZE_ITEM.y / 2 &&
		playerHookPos.z >= pos.z - COLLISION_SIZE_ITEM.z / 2 &&
		playerHookPos.z <= pos.z + COLLISION_SIZE_ITEM.z / 2)
	{
		// �R�C����particle�̐���
		CParticle_Coin::CoinEffect_Create(EFFECT_POS);
		pPlayerHook->AddCoin(1);
		// �I������
		Uninit();
		return;
	}

	// �v���C���[���̎擾
	CPlayerRotation *pPlayerRotation = CGameMode::GetPlayerRotation();
	// �v���C���[�̈ʒu���̎擾
	D3DXVECTOR3 playerRotationPos = pPlayerRotation->GetPos();

	// �v���C���[�ƃA�C�e���ʒu���d�Ȃ����ꍇ
	if (playerRotationPos.x >= pos.x - COLLISION_SIZE_ITEM.x / 2 &&
		playerRotationPos.x <= pos.x + COLLISION_SIZE_ITEM.x / 2 &&
		playerRotationPos.y >= pos.y - COLLISION_SIZE_ITEM.y / 2 &&
		playerRotationPos.y <= pos.y + COLLISION_SIZE_ITEM.y / 2 &&
		playerRotationPos.z >= pos.z - COLLISION_SIZE_ITEM.z / 2 &&
		playerRotationPos.z <= pos.z + COLLISION_SIZE_ITEM.z / 2)
	{
		// �R�C����particle�̐���
		CParticle_Coin::CoinEffect_Create(EFFECT_POS);
		pPlayerRotation->AddCoin(1);
		// �I������
		Uninit();
		return;
	}
}