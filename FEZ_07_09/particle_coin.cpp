//=============================================================================
//
// コインのパーティクル処理 [particle_coin.cpp]
// Author : 佐藤颯紀
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "particle_coin.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define COIN_POS		(D3DXVECTOR3(pos.x,pos.y,pos.z))					// 位置
#define COIN_SIZE		(D3DXVECTOR3(50.0f,50.0f,0.0f))						// サイズ
#define COIN_ROT		(D3DXVECTOR3(0.0f,0.0f,0.0f))						// 向き
#define COIN_COLOR		(D3DXCOLOR(0.0f,1.0f,1.0f,1.0f))					// 色
#define ADD_ROT_VALUE	(D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(15.0f)))		// 角度乱数
#define COIN_MOVE		(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*4.0f, sinf(D3DXToRadian(fAngle))*4.0f,0.0f))	// 移動
#define MAX_LIFE		(40)												// ライフの最大値
#define MIN_LIFE		(0)													// ライフ最小値
#define RANDOM_ANGLE	(360)												// 角度ランダム
#define MAX_PARTICLE	(30)												// パーティクルの最大数

//=============================================================================
// コンストラクタ
//=============================================================================
CParticle_Coin::CParticle_Coin()
{
	m_move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_nLife = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CParticle_Coin::~CParticle_Coin()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CParticle_Coin * CParticle_Coin::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move)
{
	// クラスのポインタ
	CParticle_Coin *pCParticle_Coin;

	// メモリ確保
	pCParticle_Coin = new CParticle_Coin;

	// 情報設定
	pCParticle_Coin->SetParticle(pos, size, COIN_ROT, col, CParticle::TEX_TYPE_1);

	// 移動量代入
	pCParticle_Coin->m_move = move;

	// 初期化処理
	pCParticle_Coin->Init();

	// メモリの開放
	return pCParticle_Coin;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CParticle_Coin::Init(void)
{
	// 初期化処理
	CParticle::Init();

	// ライフ設定
	m_nLife = MAX_LIFE;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CParticle_Coin::Uninit(void)
{
	// 終了処理
	CParticle::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CParticle_Coin::Update(void)
{
	// 更新
	CParticle::Update();

	// デクリメント
	m_nLife--;

	// 位置座標取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = DEFAULT_VECTOR;//GetRot();

	// 位置更新
	pos += m_move;

	// 向き加算
	rot.z += ADD_ROT_VALUE.z;

	// 位置座標設定
	SetPos(pos);

	// 向き設定
	SetRot(rot);

	// αが0.0f以下の場合
	if (m_nLife <= MIN_LIFE)
	{
		// 終了処理
		Uninit();
		return;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CParticle_Coin::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// カリング処理を無効
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 描画処理
	CParticle::Draw();

	// カリング処理を有効
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// エフェクト生成
//=============================================================================
void CParticle_Coin::CoinEffect_Create(D3DXVECTOR3 pos)
{
	// 指定された数だけ繰り返す
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		// 角度を360ランダム
		float fAngle = float(rand() % RANDOM_ANGLE);

		// 生成
		Create(pos, COIN_SIZE, COIN_COLOR, COIN_MOVE);
	}
}