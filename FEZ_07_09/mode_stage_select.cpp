//=============================================================================
//
// ステージ選択モード [mode_stage_select.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
//#include "sound.h"
#include "mode_stage_select.h"
#include "stage_select_button_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CStageSelectMode::CStageSelectMode()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CStageSelectMode::~CStageSelectMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CStageSelectMode * CStageSelectMode::Create()
{
	//ステージ選択モードのポインタ
	CStageSelectMode * pStageSelectMode = NULL;
	//もしステージ選択モードのポインタがNULLの場合
	if (pStageSelectMode == NULL)
	{
		//ステージ選択モードのメモリ確保
		pStageSelectMode = new CStageSelectMode;
		//もしステージ選択モードのポインタがNULLではない場合
		if (pStageSelectMode != NULL)
		{
			//初期化処理関数呼び出し
			pStageSelectMode->Init();
		}
	}
	//ステージ選択モードのポインタを返す	
	return pStageSelectMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CStageSelectMode::Init(void)
{
	////サウンドの取得
	//CSound * pSound = CManager::GetSound();
	////もしサウンドのポインタがnullptrではない場合
	//if (pSound != nullptr)
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
void CStageSelectMode::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CStageSelectMode::Update(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CStageSelectMode::Draw(void)
{
}

//=============================================================================
// 初期全生成処理関数
//=============================================================================
void CStageSelectMode::InitCreateAll(void)
{
	//ステージ選択ボタンマネージャーの生成処理関数呼び出し
	CStageSelectButtonManager::Create();
}
