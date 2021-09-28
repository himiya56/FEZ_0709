//====================================================================
//
// ビルボード処理 (billboard.h)
// Author : 東村哲士
//
//====================================================================
#ifndef _PLAYER_ROTATION_H_
#define _PLAYER_ROTATION_H_

//================================================
// インクルードファイル
//================================================
#include "player.h"
#include "camera.h"
#include "keyboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//================================================
// クラス宣言
//================================================

// ビルボードクラス
class CPlayerRotation : public CPlayer
{
public:
	CPlayerRotation();
	~CPlayerRotation();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerRotation *Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz);

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