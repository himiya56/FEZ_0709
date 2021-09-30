//=============================================================================
//
// ゲームモード [mode_game.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MODE_GAME_H_
#define _MODE_GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CPlayerHook;
class CPlayerRotation;
class CItem_coin;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGameMode : CObject
{
public:
	typedef enum
	{
		STAGE_1 = 1,
		STAGE_2,
		STAGE_3,
		STAGE_MAX
	}STAGE;
	CGameMode();
	~CGameMode();
	static CGameMode * Create(STAGE Stage);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetbCreatePause(bool bPouse) { m_bCreatePause = bPouse; }
	bool GetbCreatePause(void) { return m_bCreatePause; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CPlayerHook* GetPlayerHook(void) { return m_pPlayerHook; }
	static CPlayerRotation* GetPlayerRotation(void) { return m_pPlayerRotation; }
	CItem_coin * GetItem(void) { return m_pCoin; }
private:
	void SaveCreateCoin(void);
	void SaveGetCoin(void);
	void InitCreate(void);
	void InitStageCreate(void);
	bool m_bCreatePause;	//ポーズを生成してるか
	STAGE m_Stage;			//ステージ
	static CPlayer * m_pPlayer;
	static CPlayerHook *m_pPlayerHook;
	static CPlayerRotation *m_pPlayerRotation;
	CItem_coin * m_pCoin;
};
#endif
