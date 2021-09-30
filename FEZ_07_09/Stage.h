#pragma once
//====================================================================
//
// ステージの処理 (stage.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

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
class CStage : public CScene3D
{
public:
	CStage();
	~CStage();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CStage *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_rot;
};

#endif