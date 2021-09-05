//===============================================
//
// ブロック処理 (block.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "block.h"
#include "manager.h"
#include "renderer.h"

//========================
// 静的メンバ変数宣言
//========================
LPD3DXMESH	CBlock::m_pMesh = NULL;
LPD3DXBUFFER CBlock::m_pBuffMat = NULL;
DWORD CBlock::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CBlock::CBlock()
{
	m_rot = DEFAULT_VECTOR;
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CBlock::~CBlock()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CBlock::Init(void)
{
	CScene3D::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);

	m_rot = DEFAULT_VECTOR;

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : 樋宮匠
//=============================================================================
void CBlock::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CBlock::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CBlock::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// テクスチャ・モデルデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CBlock::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/block1_1.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block1_1.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャ・モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CBlock::Unload(void)
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
CBlock *CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock *pBlock = NULL;
	pBlock = new CBlock;
	pBlock->Init();
	pBlock->SetPos(pos);
	return pBlock;
}
