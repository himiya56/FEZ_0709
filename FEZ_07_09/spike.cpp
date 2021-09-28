//====================================================================
//
// スパイク(フック地点)処理 (spike.cpp)
// Author : 樋宮 匠
//
//====================================================================

//================================================
// インクルードファイル
//================================================
#include "spike.h"

//========================================
// 静的メンバ変数宣言
//========================================
LPDIRECT3DTEXTURE9 CSpike::m_apTexture[SPIKE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CSpike::CSpike() :CBillboard(OBJ_TYPE::OBJ_TYPE_SPIKE)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSpike::~CSpike()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSpike::Init(void)
{
	CBillboard::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSpike::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSpike::Update(void)
{
	CBillboard::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CSpike::Draw(void)
{
	CBillboard::Draw();
}

//=============================================================================
// テクスチャ読み込み処理
//=============================================================================
void CSpike::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Hook_object1.png", &m_apTexture[SPIKE_NONE]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Hook_object3.png", &m_apTexture[SPIKE_LOCK]);
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CSpike::Unload(void)
{
	for (int nCount = 0; nCount < SPIKE_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CSpike * CSpike::Create(D3DXVECTOR3 pos)
{
	CSpike *pSpike = NULL;
	pSpike = new CSpike;
	pSpike->Init();
	pSpike->SetPos(pos);
	pSpike->SetSize(SPIKE_SIZE);
	return pSpike;
}
