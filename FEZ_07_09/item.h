//=============================================================================
//
// アイテム処理 [item.h]
// Author : 佐藤颯紀
//
//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// インクルード
//=============================================================================
#include "billboard.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define COLLISION_SIZE_ITEM D3DXVECTOR3(100.0f, 100.0f, 100.0f)

//=============================================================================
// クラス宣言
//=============================================================================
class CItem : public CBillboard
{
public:
	CItem();
	~CItem();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddCreateCoin(void);
	static int GetCreateCoin(void) { return m_nCreateCoin; }
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_rot;
	static int m_nCreateCoin;
};

#endif // !_ITEM_H_
