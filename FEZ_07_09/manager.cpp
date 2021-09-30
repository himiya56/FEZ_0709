//=============================================================================
//
// オブジェクト管理処理 [manager.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "object.h"
#include "input.h"
#include "joystick.h"
#include "Keyboard.h"
#include "camera.h"
#include "light.h"
#include "fade.h"
#include "mode_title.h"
#include "mode_stage_select.h"
#include "mode_game.h"
#include "mode_result.h"
#include "button_exit.h"
#include "button_start.h"
#include "button_tutorial.h"
#include "button_stage1.h"
#include "button_stage2.h"
#include "button_stage3.h"
#include "button_stage_select.h"
#include "button_back_to_title.h"
#include "button_cancel.h"
#include "bg_stage_select.h"
#include "bg_dot.h"
#include "bg_title.h"
#include "logo_title.h"

#include "testObj.h"
#include "player.h"
#include "collisiondetection.h"
#include "player_hook.h"
#include "spike.h"
#include "goal.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInput = NULL;
CJoystick * CManager::m_pJoystick = nullptr;			//ジョイスティックのポインタ
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CPlayerHook *CManager::m_pPlayerHook = NULL;
CManager::MODE  CManager::m_Mode = MODE_NONE;		//モード
bool CManager::m_bUseFade = false;					//フェードの使用状態
CSound * CManager::m_pSound = NULL;
CGameMode * CManager::m_pGameMode = NULL;
CFade * CManager::m_pFade = NULL;					//フェードへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//インスタンス生成・初期化処理
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	m_pInput = new CInputKeyboard;
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{
		return -1;
	}
	//もしジョイスティックのポインタがNULLの場合
	if (m_pJoystick == NULL)
	{
		//ジョイスティックのメモリ確保
		m_pJoystick = new CJoystick;
		//もしジョイスティックのポインタがNULLではない場合
		if (m_pJoystick != NULL)
		{
			//ジョイスティックの初期化処理関数呼び出し
			m_pJoystick->Init(hInstance, hWnd);
		}
	}
	// ライトの生成
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	m_pCamera = CCamera::Create();
	//もしフェードのポインタがNULLの場合
	if (m_pFade == NULL)
	{
		//フェードの生成処理関数呼び出し
		m_pFade = CFade::Create(m_Mode);
	}
	//もしサウンドのポインタがNULLの場合
	if (m_pSound == NULL)
	{
		//サウンドのメモリ確保
		m_pSound = new CSound;
		//もしサウンドのポインタがnullptrではない場合
		if (m_pSound != nullptr)
		{
			//サウンドの初期化処理関数呼び出し
			m_pSound->Init(hWnd);
		}
	}
	// テクスチャの読み込み
	Load();

	CTestObj::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//CTestObj::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f));
	//CTestObj::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f));

	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 170.0f, 0.0f), PLAYER_SIZE);

	// モードの設定
	SetMode(MODE_TITLE);

	return 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// 終了処理
	CObject::ReleaseAll();

	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		//メモリ破棄
		delete m_pInput;
		m_pInput = NULL;
	}
	//もしジョイスティックのポインタがNULLではない場合
	if (m_pJoystick != NULL)
	{
		//ジョイスティックの終了処理関数呼び出し
		m_pJoystick->Uninit();
		//ジョイスティックのメモリ破棄
		delete m_pJoystick;
		//ジョイスティックのポインタをnullptrにする
		m_pJoystick = nullptr;
	}
	//もしサウンドのポインタがNULLではない場合
	if (m_pSound != NULL)
	{
		//サウンドの停止
		m_pSound->StopSound();
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		//メモリ破棄
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	//もしフェードのポインタがNULLではない場合
	if (m_pFade != NULL)
	{
		//フェードの終了処理関数呼び出し
		m_pFade->Uninit();
		//フェードのメモリ破棄
		delete m_pFade;
		//フェードのポインタをNULLにする
		m_pFade = NULL;
	}
	// テクスチャの破棄
	Unload();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	// 更新処理
	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}
	//もしジョイスティックのポインタがNULLではない場合
	if (m_pJoystick != NULL)
	{
		//ジョイスティックの更新処理関数呼び出し
		m_pJoystick->Update();
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	//もしフェードされたら
	if (m_bUseFade == true)
	{
		//もしフェードのポインタがNULLではない場合
		if (m_pFade != NULL)
		{
			//フェードの更新処理関数呼び出し
			m_pFade->Update();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// 描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}


//=============================================================================
// フェード開始処理関数
//=============================================================================
void CManager::StartFade(MODE mode)
{
	//モードを設定する
	m_Mode = mode;
	//フェードをする
	m_bUseFade = true;
}

//=============================================================================
// フェード停止処理関数
//=============================================================================
void CManager::StopFade(void)
{
	//フェードをやめる
	m_bUseFade = false;
}

//=============================================================================
// モード設定関数
//=============================================================================
void CManager::SetMode(MODE Mode)
{
	//オブジェクトの全破棄処理関数呼び出し
	CObject::ReleaseAll();
	//モードを設定する
	m_Mode = Mode;
	//各モードの処理
	switch (m_Mode)
	{
	case MODE_TITLE:
		//タイトルモードの生成処理関数呼び出し
		CTitleMode::Create();
		break;
	case MODE_STAGE_SELECT:
		//ステージ選択モードの生成処理関数呼び出し
		CStageSelectMode::Create();
		break;
	case MODE_GAME_STAGE1:
		//ゲームモードの生成処理関数呼び出し
		m_pGameMode = CGameMode::Create(CGameMode::STAGE_1);
		break;
	case MODE_GAME_STAGE2:
		//ゲームモードの生成処理関数呼び出し
		m_pGameMode = CGameMode::Create(CGameMode::STAGE_2);
		break;
	case MODE_GAME_STAGE3:
		//ゲームモードの生成処理関数呼び出し
		m_pGameMode = CGameMode::Create(CGameMode::STAGE_3);
		break;
	case MODE_RESULT:
		//リザルトモードの生成処理関数呼び出し
		CResultMode::Create();
		break;
	default:
		break;
	}
}

//=============================================================================
// モデル・テクスチャ読み込み処理
//=============================================================================
void CManager::Load(void)
{
	CTestObj::Load();
	CPlayerHook::Load();
	CExitButton::TextureLoad();
	CStartButton::TextureLoad();
	CTutorialButton::TextureLoad();
	CStage1Button::TextureLoad();
	CStage2Button::TextureLoad();
	CStage3Button::TextureLoad();
	CCollisionDetection::Load();
	CSpike::Load();
	CBlock::Load();
	CStageSelectBG::TextureLoad();
	CStageSelectButton::TextureLoad();
	CBackToTitleButton::TextureLoad();
	CCancelButton::TextureLoad();
	CDotBG::TextureLoad();
	CTitleBG::TextureLoad();
	CTitleLogo::TextureLoad();
}

//=============================================================================
// モデル・テクスチャ破棄処理
//=============================================================================
void CManager::Unload(void)
{
	CTestObj::Unload();
	CPlayerHook::Unload();
	CExitButton::TextureUnload();
	CStartButton::TextureUnload();
	CTutorialButton::TextureUnload();
	CStage1Button::TextureUnload();
	CStage2Button::TextureUnload();
	CStage3Button::TextureUnload();
	CCollisionDetection::Unload();
	CSpike::Unload();
	CBlock::Unload();
	CStageSelectBG::TextureUnload();
	CStageSelectButton::TextureUnload();
	CBackToTitleButton::TextureUnload();
	CCancelButton::TextureUnload();
	CDotBG::TextureUnload();
	CTitleBG::TextureUnload();
	CTitleLogo::TextureUnload();
}
