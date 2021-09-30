//====================================================================
//
// スパイク(フック地点)処理 (spike.cpp)
// Author : 樋宮 匠
//
//====================================================================

//================================================
// インクルードファイル
//================================================
#include "sky.h"

//========================================
// 静的メンバ変数宣言
//========================================
LPDIRECT3DTEXTURE9 CSky::m_pTexture = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CSky::CSky()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSky::~CSky()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSky::Init(void)
{
	CPolygon3D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSky::Uninit(void)
{
	CPolygon3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSky::Update(void)
{
	CPolygon3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CSky::Draw(void)
{
	CPolygon3D::Draw();
}

//=============================================================================
// テクスチャ読み込み処理
//=============================================================================
void CSky::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/sky.jpg", &m_pTexture);
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CSky::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CSky * CSky::Create(D3DXVECTOR3 pos, D3DXVECTOR2 texUv)
{
	CSky *pSpike = NULL;
	pSpike = new CSky;
	pSpike->Init();
	pSpike->SetPos(pos);
	pSpike->SetSize(SKY_SIZE.x, SKY_SIZE.y);
	pSpike->SetTexUV(texUv.x, texUv.y, 1.0f, 0.0f);
	return pSpike;
}
