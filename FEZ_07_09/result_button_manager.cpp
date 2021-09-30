//=============================================================================
//
// ステージ選択ボタンマネージャー [stage_select_button_manager.cpp]
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
#include "result_button_manager.h"
#include "button_stage_select.h"
#include "button_back_to_title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGE_SELECT_BUTTON_POSITION (D3DXVECTOR3(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 4,0.0f)))							//ステージ選択ボタンの位置
#define BACK_TO_TITLE_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	//タイトルに戻るボタンの位置
#define INPUT_INTERVAL (10)																//入力間隔

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CResultButtonManager::CResultButtonManager(OBJ_TYPE nObjectType) : CObject(nObjectType)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//ボタンのポインタ
	m_nButton = BUTTON_NONE;						//ボタン
	m_nInputCount = 0;								//入力間隔
}

//=============================================================================
// デストラクタ
//=============================================================================
CResultButtonManager::~CResultButtonManager()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CResultButtonManager * CResultButtonManager::Create(void)
{
	//リザルトボタンマネージャーのポインタ
	CResultButtonManager * pResultButtonManager = NULL;
	//リザルトボタンマネージャーのポインタNULLの場合
	if (pResultButtonManager == NULL)
	{
		//リザルトボタンマネージャーのメモリ確保
		pResultButtonManager = new CResultButtonManager;
		//リザルトボタンマネージャーのポインタがNULLではない場合
		if (pResultButtonManager != NULL)
		{
			//リザルトボタンマネージャーの初期化処理関数呼び出し
			pResultButtonManager->Init();
		}
	}
	//リザルトボタンマネージャーのポインタを返す
	return pResultButtonManager;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CResultButtonManager::Init(void)
{
	//初期全性処理関数呼び出し
	InitCreateAll();
	//ボタンの初期設定
	m_nButton = BUTTON_STAGE_SELECT;
	//全てのボタンを選択時の色にする
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//ボタンの初期選択処理関数呼び出し
		m_apButton[nCount]->SelectColor();
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CResultButtonManager::Uninit(void)
{
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CResultButtonManager::Update(void)
{
	//選択処理関数呼び出し
	Select();
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CResultButtonManager::Draw(void)
{
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CResultButtonManager::Input(void)
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
	//上矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN))
	{
		//現在のボタンを減算する
		m_nButton--;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//上矢印ボタンか上スティックが入力された場合
	if (lpDIDevice != NULL &&js.rgdwPOV[0] == 0 || lpDIDevice != NULL &&js.lY == -1000)
	{
		//入力間隔を加算する
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//現在のボタンを減算する
			m_nButton--;
			//ボタンの選択時音再生処理関数呼び出し
			m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
		}
	}
	//上矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_UP))
	{
		//現在のボタンを減算する
		m_nButton++;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//下矢印ボタンか下スティックが入力された場合
	if (lpDIDevice != NULL &&js.rgdwPOV[0] == 18000 || lpDIDevice != NULL &&js.lY == 1000)
	{
		//入力間隔を加算する
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//現在のボタンを減算する
			m_nButton++;
			//ボタンの選択時音再生処理関数呼び出し
			m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
		}
	}
	//もしENTERキー又はジョイスティックのAボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN)/* || pJoystick->GetJoystickTrigger(JS_A)*/)
	{
		//ボタンのプレス処理関数呼び出し
		m_apButton[m_nButton]->Press();
	}
}

//=============================================================================
// 選択処理関数
//=============================================================================
void CResultButtonManager::Select(void)
{
	//もし現在のボタンがステージ選択ボタンより下だったら
	if (m_nButton < BUTTON_STAGE_SELECT)
	{
		//現在のボタンをタイトルに戻るボタンにする
		m_nButton = BUTTON_BACK_TO_TITLE;
	}
	//もし現在のボタンがタイトルに戻るボタンを越えたら
	if (m_nButton > BUTTON_BACK_TO_TITLE)
	{
		//現在のボタンをステージ選択ボタンにする
		m_nButton = BUTTON_STAGE_SELECT;
	}
	//ボタンの最大数分回す
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//ボタンの選択されてない時の色変更処理関数呼び出し
		m_apButton[nCount]->NotSelectColor();
	}
	//ボタンの選択時色変更処理関数呼び出し
	m_apButton[m_nButton]->SelectColor();
}

//=============================================================================
// 初期生成処理関数
//=============================================================================
void CResultButtonManager::InitCreateAll(void)
{
	//ステージ選択ボタンの生成
	m_apButton[BUTTON_STAGE_SELECT] = CStageSelectButton::Create(STAGE_SELECT_BUTTON_POSITION);
	//タイトルに戻るボタンの生成
	m_apButton[BUTTON_BACK_TO_TITLE] = CBackToTitleButton::Create(BACK_TO_TITLE_POSITION);
}