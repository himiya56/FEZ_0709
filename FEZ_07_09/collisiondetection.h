//====================================================================
//
// �|���S��(�����蔻��p)���� (block.h)
// Author : �����N�m
//
//====================================================================
#ifndef _COLLISIONDETECTION_H_
#define _COLLISIONDETECTION_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "polygon2d.h"
#include "camera.h"

//================================================
// �N���X�錾
//================================================

// �r���{�[�h�N���X
class CCollisionDetection : public CPolygon2D
{
public:
	typedef enum
	{
		BLOCKTYPE_NULL = 0,
		BLOCKTYPE_NONE,
		BLOCKTYPE_HOOK,
		BLOCKTYPE_BUTTON,
		BLOCKTYPE_BUTTON_INCLUDED
	}BLOCKTYPE;

	CCollisionDetection();
	~CCollisionDetection();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ReleaseAll(void);
	void UpdateByType(BLOCKTYPE BlockType);

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

	bool m_bUse;

	CCamera *m_pCamera;
};

#endif