//=============================================================================
//
// ゲームモード [mode_game.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
//#include "sound.h"
#include "light.h"
#include "camera.h"
#include "keyboard.h"
#include "joystick.h"
#include "mode_game.h"
#include "player_hook.h"
#include "player_rotation.h"
#include "testObj.h"
#include "spike.h"
#include "collisiondetection.h"
#include "sound.h"
#include "player.h"
#include "goal.h"
#include "testObj.h"
#include "Stage.h"
#include "sky.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CPlayerHook *CGameMode::m_pPlayerHook = NULL;
CPlayerRotation *CGameMode::m_pPlayerRotation = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGameMode::CGameMode()
{
	m_bCreatePause = false;		//ポーズを使用してるか
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameMode::~CGameMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CGameMode * CGameMode::Create(STAGE stage)
{
	//ゲームモードのポインタ
	CGameMode * pGameMode = NULL;
	//もしゲームモードのポインタをNULLだった場合
	if (pGameMode == NULL)
	{
		//ゲームモードのメモリ確保
		pGameMode = new CGameMode;
		//もしゲームモードのポインタをNULLではない場合
		if (pGameMode != NULL)
		{
			pGameMode->m_Stage = stage;	//ステージの設定

			//ゲームモードの初期化関数呼び出し
			pGameMode->Init();
		}
	}
	//ゲームモードのポインタを返す
	return pGameMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGameMode::Init(void)
{
	//初期生成処理関数呼び出し(共通)
	InitCreate();
	//各ステージの生成
	InitStageCreate();
	////サウンドの取得
	//CSound * pSound = CManager::GetSound();
	////もしサウンドのポインタがnullptrではない場合
	//if (pSound != nullptr)
	//{
	//	//名前入力のBGM停止 
	//	pSound->StopSound(CSound::SOUND_LABEL_BGM_NAME);
	//}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameMode::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameMode::Update(void)
{
	////入力処理関数呼び出し
	//Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// 初期生成処理関数
//=============================================================================
void CGameMode::InitCreate(void)
{
}

//=============================================================================
// 初期各ステージ生成処理関数
//=============================================================================
void CGameMode::InitStageCreate(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがNULLではない場合
	if (pSound != NULL)
	{
		//サウンドの停止
		pSound->StopSound();
		switch (m_Stage)
		{
		case STAGE_1:
			//ステージ1のBGMを再生
			pSound->Play(CSound::SOUND_LABEL_BGM_STAGE1);

			m_pPlayerHook = CPlayerHook::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 1.0f, 75.0f * -2.0f), BLOCK_SIZE);
			m_pPlayerRotation = CPlayerRotation::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 2.0f + 70.0f, 75.0f * 0.0f), BLOCK_SIZE);

			//75.0f * 27.0f, 75.0f * 30.0f

			CStage::Create(D3DXVECTOR3(75.0f / 2.0f, 75.0f * -2.2f, -75.0f / 2.0f));
			CSky::Create(D3DXVECTOR3(0.0f, 75.0f * 15.0f, 75.0f * 13.5f), D3DXVECTOR2(0.0f, 0.25f));

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 0.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 3.0f, 75.0f * 1.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 2.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 2.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 3.0f, 75.0f * 2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 4.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 4.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -2.0f, 75.0f * 5.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 6.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 7.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 8.0f, 75.0f * -5.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 9.0f, 75.0f * -4.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 10.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 10.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 10.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 10.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 10.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 10.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 10.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 10.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 11.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_RED);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 12.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_RED);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 13.0f, 75.0f * -3.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 14.0f, 75.0f * -3.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON, CCollisionDetection::BUTTONCOLOR_RED);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 13.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CSpike::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 14.0f, 75.0f * -2.0f));

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 14.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_RED);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 15.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_RED);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 16.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 16.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 16.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 16.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 16.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 16.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 16.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 16.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 17.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 18.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_BLUE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 19.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_BLUE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 3.0f, 75.0f * 19.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 4.0f, 75.0f * 19.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CSpike::Create(D3DXVECTOR3(75.0f * 3.0f, 75.0f * 20.0f, 75.0f * -1.0f));
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 4.0f, 75.0f * 20.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON, CCollisionDetection::BUTTONCOLOR_BLUE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 19.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 20.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON, CCollisionDetection::BUTTONCOLOR_YELLOW);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 20.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 21.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 3.0f, 75.0f * 22.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 23.0f, 75.0f * -2.0f), BLOCK_SIZE,  CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 23.0f, 75.0f * -2.0f), BLOCK_SIZE,  CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 23.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 23.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 23.0f, 75.0f * 0.0f), BLOCK_SIZE,  CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 23.0f, 75.0f * 1.0f), BLOCK_SIZE,  CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 23.0f, 75.0f * 1.0f), BLOCK_SIZE,   CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 23.0f, 75.0f * 1.0f), BLOCK_SIZE,   CCollisionDetection::BLOCKTYPE_BUTTON_INCLUDED, CCollisionDetection::BUTTONCOLOR_YELLOW);

			CGoal::Create(D3DXVECTOR3(75.0f * 0.5f, 75.0f * 25.0f, 75.0f * -0.5f));

			break;
		case STAGE_2:
			break;
		case STAGE_3:
			break;
		default:
			break;
		}
	}
}