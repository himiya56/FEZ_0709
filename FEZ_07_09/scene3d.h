//====================================================================
//
// 3Dモデル処理 (scene3d.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _SCENE_3D_H_
#define _SCENE_3D_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLYGON_3D_SIZE 1000

//================================================
// クラス宣言
//================================================

// 3Dモデルクラス
class CScene3D : public CObject
{
public:
    CScene3D();
	CScene3D(OBJ_TYPE objType);
    virtual ~CScene3D();

    virtual HRESULT Init(void);
    virtual void Uninit(void);
    virtual void Update(void);
    virtual void Draw(void);
    void BindMesh(const LPD3DXMESH pMesh, const  LPD3DXBUFFER pBuffMat, const DWORD nNumMat);
    void BindTexture(const LPDIRECT3DTEXTURE9 pTex);
    void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
    void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
    void SetScale(const D3DXVECTOR3 scale) { m_scale = scale; }
	void SetCollisionSize(const D3DXVECTOR3 size) { m_collisionSize = size; }
	void SetIsCollision(const bool bIsCollision) { m_bCollision = bIsCollision; }
	void SetRotateMtx(const D3DXMATRIX mtx) { m_mtxRotate = mtx; }

    D3DXVECTOR3 GetPos(void) { return m_pos; }
    D3DXVECTOR3 GetRot(void) { return m_rot; }
    D3DXVECTOR3 GetScale(void) { return m_scale; }
	D3DXMATRIX  GetMtx(void) { return m_mtxWorld; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_collisionSize; }          // 衝突の大きさを返す
	bool		GetIsCollision(void) { return m_bCollision; }

private:
    LPDIRECT3DTEXTURE9		m_pTexture;
    LPD3DXMESH				m_pMesh;
    LPD3DXBUFFER			m_pBuffMat;
    DWORD					m_nNumMat;
    D3DXMATRIX			    m_mtxWorld;		// ワールドマトリックス
	D3DXMATRIX				m_mtxRotate;
    D3DXVECTOR3				m_pos;			// 座標
    D3DXVECTOR3				m_rot;			// 回転
    D3DXVECTOR3				m_scale;
	D3DXVECTOR3				m_collisionSize;     // 当たり判定の大きさ
	bool					m_bCollision;
};

#endif