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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_SIZ 7.0f
#define JUMP_SIZ 10.0f
#define GRAVITY_SIZ 0.27f
#define MOVE_SPECIFIED D3DXVECTOR3(MOVE_SIZ, 0, MOVE_SIZ)
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

	D3DXVECTOR3 CPlayer::RotationDifferentialShift(CCamera::ORIENTATION Orientation, D3DXVECTOR3 PlayerPos, CCamera::ROTATE Rotate, CCamera::ROTATE RotateOld);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_siz;
	D3DXVECTOR3 m_move;
	bool m_bJumpJudge;

	static LPDIRECT3DTEXTURE9		m_pTexture;

	CCamera *m_pCamera;
};

#endif