//====================================================================
//
// ポリゴン(当たり判定用)処理 (block.h)
// Author : 東村哲士
//
//====================================================================
#ifndef _COLLISIONDETECTION_H_
#define _COLLISIONDETECTION_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "billboard.h"
#include "camera.h"

//================================================
// マクロ定義
//================================================
#define BLOCK_SIZE D3DXVECTOR3(75.0f,75.0f,75.0f)

//================================================
// クラス宣言
//================================================

// ビルボードクラス
class CCollisionDetection : public CBillboard
{
public:
	typedef enum
	{
		BLOCKTYPE_NULL = 0,
		BLOCKTYPE_NONE,
		BLOCKTYPE_WALL,
		BLOCKTYPE_HOOK,
		BLOCKTYPE_BUTTON,
		BLOCKTYPE_BUTTON_INCLUDED,
		BLOCK_TYPE_MAX
	}BLOCKTYPE;

	CCollisionDetection();
	~CCollisionDetection();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ReleaseAll(void);
	void UpdateByType(BLOCKTYPE BlockType);
	
	static void Load(void);
	static void Unload(void);

	CCollisionDetection* GetNextScene(void) { return m_pNext; }
	D3DXVECTOR3 GetSiz(void) { return m_siz; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	static CCollisionDetection *GetCollisionDetectionOrientation(void) { return m_CollisionDetectionListTop; }
	static int GetNumAll(void) { return m_nNum; }
	static CCollisionDetection *Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz, BLOCKTYPE BlockType);

private:
	static int m_nNum;

	static CCollisionDetection *m_CollisionDetectionListTop;
	static CCollisionDetection *m_CollisionDetectionListCur;
	CCollisionDetection *m_pPrev;
	CCollisionDetection *m_pNext;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_siz;
	BLOCKTYPE m_BlockType;

	static LPDIRECT3DTEXTURE9		m_apTexture[BLOCK_TYPE_MAX];

	bool m_bUse;

	CCamera *m_pCamera;
};

#endif