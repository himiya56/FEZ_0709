//====================================================================
//
// �r���{�[�h���� (billboard.h)
// Author : �����N�m
//
//====================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "billboard.h"
#include "camera.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_SIZ 5.0f // �v���C���[�̈ړ���
#define PLAYER_SIZE D3DXVECTOR3(150.0f, 150.0f, 0.0f)

//================================================
// �N���X�錾
//================================================

// �r���{�[�h�N���X
class CPlayer : public CBillboard
{
public:
	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CollisionDetection(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz);

private:
	D3DXVECTOR3 m_pos;
	float m_move;

	static LPDIRECT3DTEXTURE9		m_pTexture;

	CCamera *m_pCamera;
};

#endif