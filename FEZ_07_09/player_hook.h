//====================================================================
//
// プレイヤー12処理 (player_hook.h)
// Author : 樋宮 匠
//
//====================================================================
#ifndef _PLAYER_HOOK_H_
#define _PLAYER_HOOK_H_

//================================================
// インクルードファイル
//================================================
#include "player.h"
#include "camera.h"
#include "keyboard.h"
#include "spike.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEST_HOOK_POS D3DXVECTOR3(300.0f, 300.0f, 0.0f)
#define HOOK_SPD_RATE 10.0f
#define HOOK_STOP_SIZE 5.0f
#define HOOK_MOVE_FRAME 60.0f
#define HOOK_LEAST_DIST 50.0f

//================================================
// クラス宣言
//================================================

// ビルボードクラス
class CPlayerHook : public CPlayer
{
public:
	CPlayerHook();
	~CPlayerHook();

	// 円
	typedef struct
	{
		D3DXVECTOR3 centerPos = DEFAULT_VECTOR;
		D3DXVECTOR3 targetPos = DEFAULT_VECTOR;
		float fRadius = 0.0f;
		float fAngle = 0.0f;
	}Circle;

	// フック地点のデータ保存用
	typedef struct SPIKE
	{
		D3DXVECTOR3 pos = DEFAULT_VECTOR;
		CSpike *pSpike = NULL;
		float dist = 0.0f;
	};

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 SortSpike(void);
	void ShotHook(D3DXVECTOR3 pos);
	void MoveToHook(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	bool GetPlayerHookJump(void) { return m_bJumpJudge; }
	bool GetHookState(void) { return m_bHook; }
	D3DXVECTOR3 GetMove(void) { return m_move; }

	static CPlayerHook *Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz);
	static void Load(void);
	static void Unload(void);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_RidingBlockPos;

	bool m_bHook;
	bool m_bJumpJudge;
	Circle m_circle;
	int m_nAnimCount;

	static LPDIRECT3DTEXTURE9		m_pTexture;

	CCamera *m_pCamera;
};

#endif