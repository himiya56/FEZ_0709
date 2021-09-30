//=============================================================================
//
// コインのパーティクル処理 [particle_coin.h]
// Author : 佐藤颯紀
//
//=============================================================================

#ifndef _PARTICLE_COIN_H_
#define _PARTICLE_COIN_H_

//=============================================================================
// インクルード
//=============================================================================
#include "particle.h"

//=============================================================================
// クラス宣言
//=============================================================================
class CParticle_Coin : public CParticle
{
public:
	CParticle_Coin();
	~CParticle_Coin();

	static CParticle_Coin *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void CoinEffect_Create(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_move;		// 移動
	int m_nLife;			// ライフ
};
#endif // !_PARTICLE_COIN_H_
