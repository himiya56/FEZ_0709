//=============================================================================
//
// チュートリアルボタン [button_tutorial.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
//#include "sound.h"
#include "button_tutorial.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("data/TEXTURE/Button_Tutorial.png")	

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTutorialButton::m_pTexture;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorialButton::CTutorialButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorialButton::~CTutorialButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CTutorialButton::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	//デバイスへのポインタ
		TEXTURE_PASS,					//ファイルの名前
		&m_pTexture);					//読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CTutorialButton::TextureUnload(void)
{
	//もしテクスチャのポインタがNULLではない場合
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをNULLにする
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CTutorialButton * CTutorialButton::Create(D3DXVECTOR3 Position)
{
	//チュートリアルボタンのポインタ
	CTutorialButton * pTutorialButton = NULL;
	//チュートリアルボタンのポインタがNULLの場合
	if (pTutorialButton == NULL)
	{
		//チュートリアルボタンのメモリ確保
		pTutorialButton = new CTutorialButton;
		//チュートリアルボタンのポインタがNULLではない場合
		if (pTutorialButton != NULL)
		{
			//チュートリアルボタンの位置設定
			pTutorialButton->SetPos(Position);
			//チュートリアルボタンの初期化処理関数呼び出し
			pTutorialButton->Init();
		}
	}
	//チュートリアルボタンのポインタを返す
	return pTutorialButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTutorialButton::Init(void)
{
	//ボタンの初期化処理関数呼び出し
	CButton::Init();
	//テクスチャの設定
	SetTexUV(0.0f, 1.0f, 0.0f, 1.0f);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CTutorialButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTutorialButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTutorialButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CTutorialButton::Press(void)
{
	////サウンドの取得
	//CSound * pSound = CManager::GetSound();
	////もしサウンドのポインタがNULLではない場合
	//if (pSound != NULL)
	//{
	//	//決定音の再生
	//	pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	//}
	//ステージ1モードに遷移する
	CManager::StartFade(CManager::MODE_GAME_STAGE1);
}