//=============================================================================
//
// コイン処理 [item_coin.h]
// Author : 佐藤颯紀
//
//=============================================================================

#ifndef _ITEM_COIN_H_
#define _ITEM_COIN_H_

//=============================================================================
// インクルード
//=============================================================================
#include "item.h"

//=============================================================================
// クラス宣言
//=============================================================================
class CItem_coin : public CItem
{
public:
	CItem_coin();
	~CItem_coin();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void CollisionDetection(void);		// 当たり判定
	static HRESULT Load(void);
	static void Unload(void);
	static CItem_coin *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_rot;
};

#endif // !_ITEM_COIN_H_
