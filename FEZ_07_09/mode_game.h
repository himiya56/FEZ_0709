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
private:
	void InitCreate(void);
	void InitStageCreate(void);
	void Input(void);
	bool m_bCreatePause;	//�|�[�Y�𐶐����Ă邩
	STAGE m_Stage;			//�X�e�[�W
};
#endif
