//===============================================
//
// ブロック処理 (block.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "stage.h"
#include "manager.h"
#include "renderer.h"

//========================
// 静的メンバ変数宣言
//========================
LPD3DXMESH	CStage::m_pMesh = NULL;
LPD3DXBUFFER CStage::m_pBuffMat = NULL;
DWORD CStage::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CStage::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CStage::CStage()
{
	m_rot = DEFAULT_VECTOR;
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CStage::~CStage()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CStage::Init(void)
{
	CScene3D::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);
	//SetScale(D3DXVECTOR3(0.99f, 0.99f, 0.99f));

	m_rot = DEFAULT_VECTOR;

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : 樋宮匠
//=============================================================================
void CStage::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CStage::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CStage::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// テクスチャ・モデルデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CStage::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/Stage1.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block3_1.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャ・モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CStage::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// インスタンス生成処理
// Author : 樋宮匠
//=============================================================================
CStage *CStage::Create(D3DXVECTOR3 pos)
{
	CStage *pBlock = NULL;
	pBlock = new CStage;
	pBlock->Init();
	pBlock->SetPos(pos);
	return pBlock;
}
