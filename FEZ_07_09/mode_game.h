//=============================================================================
//
// �Q�[�����[�h [mode_game.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MODE_GAME_H_
#define _MODE_GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CPlayerHook;
class CPlayerRotation;
class CItem_coin;

//*****************************************************************************
// �N���X��`
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
	bool m_bCreatePause;	//�|�[�Y�𐶐����Ă邩
	STAGE m_Stage;			//�X�e�[�W
	static CPlayer * m_pPlayer;
	static CPlayerHook *m_pPlayerHook;
	static CPlayerRotation *m_pPlayerRotation;
	CItem_coin * m_pCoin;
};
#endif
