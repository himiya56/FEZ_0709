//=============================================================================
//
// リザルトモード [mode_result.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "mode_result.h"
#include "bg_result.h"
#include "ui_coin.h"
#include "ui_get_coin.h"
#include "item.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CResultMode::CResultMode()
{
	m_pCoinUI = NULL;		//生成されているコイン枚数UIのポインタ
	m_pGetCoinUI = NULL;	//取得したコイン枚数UIのポインタ
	m_nCreateCoin = 0;
	m_nGetCoin = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResultMode::~CResultMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CResultMode * CResultMode::Create()
{
	//リザルトモードのポインタ
	CResultMode * pResultMode = NULL;
	//もしリザルトモードのポインタがNULLの場合
	if (pResultMode == NULL)
	{
		//リザルトモードのメモリ確保
		pResultMode = new CResultMode;
		//もしリザルトモードのポインタがNULLではない場合
		if (pResultMode != NULL)
		{
			//初期化処理関数呼び出し
			pResultMode->Init();
		}
	}
	//リザルトモードのポインタを返す	
	return pResultMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CResultMode::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがNULLではない場合
	if (pSound != NULL)
	{
		//サウンドの停止
		pSound->StopSound();
		//リザルトのBGMを再生
		pSound->Play(CSound::SOUND_LABEL_BGM_RESULT);
	}
	//初期全生成処理関数呼び出し
	InitCreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CResultMode::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CResultMode::Update(void)
{
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CResultMode::Draw(void)
{
}

//=============================================================================
// 初期全生成処理関数
//=============================================================================
void CResultMode::InitCreateAll(void)
{
	LoadCreateCoin();
	LoadGetCoin();
	//リザルト画面の背景生成
	CResultBG::Create();
	//生成されているコイン枚数UIの生成
	m_pCoinUI = CCoinUI::Create();
	//取得したコイン枚数UIの生成
	m_pGetCoinUI = CGetCoinUI::Create();
	m_pCoinUI->SetCoin(m_nCreateCoin);
	m_pGetCoinUI->SetGetCoin(m_nGetCoin);
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CResultMode::Input(void)
{
	//キーボードの取得
	CInputKeyboard * pKeyboard = CManager::GetInput();
	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice(JOYSTICK_1P);
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	//LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect(JOYSTICK_1P);
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//もしENTERキー又はジョイスティックのAボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A, JOYSTICK_1P))
	{
		//タイトルモードに遷移する
		CManager::StartFade(CManager::MODE_TITLE);
	}
}

void CResultMode::LoadCreateCoin(void)
{
	//ファイルのポインタ
	FILE *pFile;
	//ファイルの読み込み
	pFile = fopen("data/TEXT/CreateCoinData.txt", "r");
	//ファイルのNULLチェック
	if (pFile != NULL)
	{
		//入力情報読み込み
		fscanf(pFile, "%d", &m_nCreateCoin);
		//ファイルを閉じる
		fclose(pFile);
	}
}

void CResultMode::LoadGetCoin(void)
{
	//ファイルのポインタ
	FILE *pFile;
	//ファイルの読み込み
	pFile = fopen("data/TEXT/GetCoinData.txt", "r");
	//ファイルのNULLチェック
	if (pFile != NULL)
	{
		//入力情報読み込み
		fscanf(pFile, "%d", &m_nGetCoin);
		//ファイルを閉じる
		fclose(pFile);
	}
}