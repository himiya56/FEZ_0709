#pragma once
//====================================================================
//
// ゴールの処理 (block.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

//================================================
// インクルードファイル
//================================================
#include "scene3d.h"

//================================================
// マクロ定義
//================================================
#define HOVER_RANGE 10.0f  // ゴールオブジェクトの浮遊範囲

//================================================
// クラス宣言
//================================================

// UIクラス
class CGoal : public CScene3D
{
public:
	CGoal();
	~CGoal();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CGoal *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_pos;
	D3DXVECTOR3						m_rot;
	float							m_fAngle;
};

#endif