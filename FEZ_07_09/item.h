//=============================================================================
//
// �A�C�e������ [item.h]
// Author : �����D�I
//
//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "billboard.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define COLLISION_SIZE_ITEM D3DXVECTOR3(100.0f, 100.0f, 100.0f)

//=============================================================================
// �N���X�錾
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
