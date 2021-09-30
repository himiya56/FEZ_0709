//=============================================================================
//
// �R�C���̃p�[�e�B�N������ [particle_coin.h]
// Author : �����D�I
//
//=============================================================================

#ifndef _PARTICLE_COIN_H_
#define _PARTICLE_COIN_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "particle.h"

//=============================================================================
// �N���X�錾
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
	D3DXVECTOR3 m_move;		// �ړ�
	int m_nLife;			// ���C�t
};
#endif // !_PARTICLE_COIN_H_
