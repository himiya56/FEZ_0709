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
<<<<<<< HEAD
=======
//#include "sound.h"
>>>>>>> remotes/origin/sinnikaido
#include "light.h"
#include "camera.h"
#include "keyboard.h"
#include "joystick.h"
#include "mode_game.h"
#include "player_hook.h"
#include "player_rotation.h"
#include "player.h"
#include "testObj.h"
#include "spike.h"
#include "collisiondetection.h"
#include "sound.h"
#include "player.h"
<<<<<<< HEAD
#include "goal.h"
=======
#include "testObj.h"
>>>>>>> remotes/origin/sinnikaido

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CPlayerHook *CGameMode::m_pPlayerHook = NULL;
CPlayerRotation *CGameMode::m_pPlayerRotation = NULL;
<<<<<<< HEAD
=======
// 静的メンバ変数の初期化
//*****************************************************************************
>>>>>>> remotes/origin/sinnikaido

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
<<<<<<< HEAD

=======
										//ゲームモードの初期化関数呼び出し
>>>>>>> remotes/origin/sinnikaido
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
<<<<<<< HEAD
	////入力処理関数呼び出し
	//Input();
=======
>>>>>>> remotes/origin/sinnikaido
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
<<<<<<< HEAD

			m_pPlayerHook = CPlayerHook::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 1.0f, 75.0f * -2.0f), BLOCK_SIZE);
			m_pPlayerRotation = CPlayerRotation::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 2.0f + 70.0f, 75.0f * 0.0f), BLOCK_SIZE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f / 2.0f, (75.0f * 23) / 2.0f, -75.0f / 2.0f), D3DXVECTOR3(150.0f, 1800.0f, 0.0f), CCollisionDetection::BLOCKTYPE_WALL);
=======
			m_pPlayerHook = CPlayerHook::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 1.0f, 75.0f * -2.0f), BLOCK_SIZE);
			m_pPlayerRotation = CPlayerRotation::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 2.0f + 70.0f, 75.0f * 0.0f), BLOCK_SIZE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f / 2.0f, 1725.0f / 2.0f, -75.0f / 2.0f), D3DXVECTOR3(150.0f, 1800.0f, 0.0f), CCollisionDetection::BLOCKTYPE_WALL);
>>>>>>> remotes/origin/sinnikaido

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 0.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 3.0f, 75.0f * 1.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 2.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CSpike::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 3.0f, 75.0f * 0.0f));

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 2.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 3.0f, 75.0f * 2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 4.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 4.0f, 75.0f * 1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
<<<<<<< HEAD

			CSpike::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 5.0f, 75.0f * 1.0f));

=======
>>>>>>> remotes/origin/sinnikaido
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -2.0f, 75.0f * 5.0f, 75.0f * 0.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * -1.0f, 75.0f * 6.0f, 75.0f * -1.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 0.0f, 75.0f * 7.0f, 75.0f * -2.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 1.0f, 75.0f * 8.0f, 75.0f * -5.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);
			CCollisionDetection::Create(D3DXVECTOR3(75.0f * 2.0f, 75.0f * 9.0f, 75.0f * -4.0f), BLOCK_SIZE, CCollisionDetection::BLOCKTYPE_NONE);

<<<<<<< HEAD
			CGoal::Create(D3DXVECTOR3(75.0f * -2.0f, 75.0f * 3.0f, 75.0f * -2.0f));
=======
>>>>>>> remotes/origin/sinnikaido
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