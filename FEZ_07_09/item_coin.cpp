//=============================================================================
//
// コイン処理 [item_coin.cpp]
// Author : 佐藤颯紀
//
//=============================================================================

//=============================================================================
// インクルード
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
// マクロ定義
//=============================================================================
#define EFFECT_POS (D3DXVECTOR3(pos.x,pos.y,pos.z + 20.0f))		// エフェクトの位置

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH	CItem_coin::m_pMesh = NULL;
LPD3DXBUFFER CItem_coin::m_pBuffMat = NULL;
DWORD CItem_coin::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CItem_coin::m_pTexture = NULL;

//=============================================================================
// クリエイト処理
//=============================================================================
CItem_coin *CItem_coin::Create(D3DXVECTOR3 pos)
{
	CItem_coin *pCoin = NULL;
	pCoin = new CItem_coin;
	// coinの生成した数を増やす
	pCoin->Init();
	pCoin->SetPos(pos);
	return pCoin;
}

//=============================================================================
// モデルの読み込み
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
// モデルの破棄
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
// コンストラクタ
//=============================================================================
CItem_coin::CItem_coin()
{
	m_rot = DEFAULT_VECTOR;	// 向き設定
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem_coin::~CItem_coin()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItem_coin::Init(void)
{
	AddCreateCoin();
	// 初期化処理
	CItem::Init();
	//BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);

	// 向きの初期化
	m_rot = DEFAULT_VECTOR;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItem_coin::Uninit(void)
{
	// 終了処理
	CItem::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItem_coin::Update(void)
{
	// 更新処理
	CItem::Update();

	// 当たり判定
	CollisionDetection();
}

//=============================================================================
// 描画処理
//=============================================================================
void CItem_coin::Draw(void)
{
	// 描画処理
	CItem::Draw();
}

//=============================================================================
// 当たり判定
//=============================================================================
void CItem_coin::CollisionDetection(void)
{
	// 位置情報の取得
	D3DXVECTOR3 pos = GetPos();

	// プレイヤー情報の取得
	CPlayerHook *pPlayerHook = CGameMode::GetPlayerHook();
	// プレイヤーの位置情報の取得
	D3DXVECTOR3 playerHookPos = pPlayerHook->GetPos();

	// プレイヤーとアイテム位置が重なった場合
	if (playerHookPos.x >= pos.x - COLLISION_SIZE_ITEM.x / 2 &&
		playerHookPos.x <= pos.x + COLLISION_SIZE_ITEM.x / 2 &&
		playerHookPos.y >= pos.y - COLLISION_SIZE_ITEM.y / 2 &&
		playerHookPos.y <= pos.y + COLLISION_SIZE_ITEM.y / 2 &&
		playerHookPos.z >= pos.z - COLLISION_SIZE_ITEM.z / 2 &&
		playerHookPos.z <= pos.z + COLLISION_SIZE_ITEM.z / 2)
	{
		// コインのparticleの生成
		CParticle_Coin::CoinEffect_Create(EFFECT_POS);
		pPlayerHook->AddCoin(1);
		// 終了処理
		Uninit();
		return;
	}

	// プレイヤー情報の取得
	CPlayerRotation *pPlayerRotation = CGameMode::GetPlayerRotation();
	// プレイヤーの位置情報の取得
	D3DXVECTOR3 playerRotationPos = pPlayerRotation->GetPos();

	// プレイヤーとアイテム位置が重なった場合
	if (playerRotationPos.x >= pos.x - COLLISION_SIZE_ITEM.x / 2 &&
		playerRotationPos.x <= pos.x + COLLISION_SIZE_ITEM.x / 2 &&
		playerRotationPos.y >= pos.y - COLLISION_SIZE_ITEM.y / 2 &&
		playerRotationPos.y <= pos.y + COLLISION_SIZE_ITEM.y / 2 &&
		playerRotationPos.z >= pos.z - COLLISION_SIZE_ITEM.z / 2 &&
		playerRotationPos.z <= pos.z + COLLISION_SIZE_ITEM.z / 2)
	{
		// コインのparticleの生成
		CParticle_Coin::CoinEffect_Create(EFFECT_POS);
		pPlayerRotation->AddCoin(1);
		// 終了処理
		Uninit();
		return;
	}
}