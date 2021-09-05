#pragma once
//====================================================================
//
// ブロックの処理 (block.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//================================================
// インクルードファイル
//================================================
#include "scene3d.h"

//================================================
// マクロ定義
//================================================

//================================================
// クラス宣言
//================================================

// UIクラス
class CBlock : public CScene3D
{
public:
	CBlock();
	~CBlock();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CBlock *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_rot;
};

#endif