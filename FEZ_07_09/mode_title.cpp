//=============================================================================
//
// タイトルモード [mode_title.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
//#include "sound.h"
#include "mode_title.h"
#include "button_any.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleMode::CTitleMode()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleMode::~CTitleMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CTitleMode * CTitleMode::Create()
{
	//タイトルモードのポインタ
	CTitleMode * pTitleMode = NULL;
	//もしタイトルモードのポインタがNULLの場合
	if (pTitleMode == NULL)
	{
		//タイトルモードのメモリ確保
		pTitleMode = new CTitleMode;
		//もしタイトルモードのポインタがNULLではない場合
		if (pTitleMode != NULL)
		{
			//初期化処理関数呼び出し
			pTitleMode->Init();
		}
	}
	//タイトルモードのポインタを返す	
	return pTitleMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTitleMode::Init(void)
{
	////サウンドの取得
	//CSound * pSound = CManager::GetSound();
	////もしサウンドのポインタがNULLではない場合
	//if (pSound != NULL)
	//{
	//	//サウンドの停止
	//	pSound->StopSound();
	//	//タイトルのBGMを再生
	//	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);
	//}
	//初期全生成処理関数呼び出し
	InitCreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CTitleMode::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTitleMode::Update(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTitleMode::Draw(void)
{
}

//=============================================================================
// 初期全生成処理関数
//=============================================================================
void CTitleMode::InitCreateAll(void)
{
	//何かしらのボタン入力の生成
	CAnyButton::Create();
}
