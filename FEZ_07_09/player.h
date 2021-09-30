//====================================================================
//
// ビルボード処理 (billboard.h)
// Author : 東村哲士
//
//====================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "billboard.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_SIZ 7.0f
#define JUMP_SIZ 7.0f
#define GRAVITY_SIZ 0.27f
#define MOVE_SPECIFIED D3DXVECTOR3(MOVE_SIZ, 0, MOVE_SIZ)
#define PLAYER_SIZE D3DXVECTOR3(75.0f, 75.0f, 0.0f)
#define ANIM_RATE 8

//================================================
// クラス宣言
//================================================

// ビルボードクラス
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
	void SetJumpJudge(bool JumpJudge) { m_bJumpJudge = JumpJudge; }
	
	bool GetJumpJudge(void) { return m_bJumpJudge; }
	bool GetCollisionDetectionJudge(void) { return m_bCollisionDetectionJudge; }
	D3DXVECTOR3 GetRidingBlockPos(void) { return m_RidingBlockPos; }
	D3DXVECTOR3 CPlayer::RotationDifferentialShift(CCamera::ORIENTATION Orientation, D3DXVECTOR3 PlayerPos, CCamera::ROTATE Rotate, CCamera::ROTATE RotateOld);
	void AddCoin(int nValue) { m_nCoin += nValue; }
	int GetCoin(void) { return m_nCoin; }
	D3DXVECTOR3 CPlayer::RotationDifferentialShift(CCamera::ORIENTATION Orientation);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_siz;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_RidingBlockPos;
	bool m_bJumpJudge;
	bool m_bCollisionDetectionJudge;
	static LPDIRECT3DTEXTURE9		m_pTexture;
	int m_nCoin;    // コインの所持数
	CCamera *m_pCamera;
};

#endif