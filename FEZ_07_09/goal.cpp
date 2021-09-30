//===============================================
//
// ブロック処理 (block.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "goal.h"
#include "manager.h"
#include "renderer.h"

//========================
// 静的メンバ変数宣言
//========================
LPD3DXMESH	CGoal::m_pMesh = NULL;
LPD3DXBUFFER CGoal::m_pBuffMat = NULL;
DWORD CGoal::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CGoal::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGoal::CGoal()
{
	m_pos = DEFAULT_VECTOR;
	m_rot = DEFAULT_VECTOR;
	m_fAngle = 0.0f;
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CGoal::~CGoal()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CGoal::Init(D3DXVECTOR3 pos)
{
	CScene3D::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);

	m_pos = pos;
	m_rot = DEFAULT_VECTOR;
	m_fAngle = 0.0f;

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : 樋宮匠
//=============================================================================
void CGoal::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CGoal::Update(void)
{
	// ふわふわさせる
	m_fAngle += D3DXToRadian(1);

	if (m_fAngle >= D3DXToRadian(360))
	{
		m_fAngle = 0.0f;
	}

	D3DXVECTOR3 pos = m_pos;
	pos.y = m_pos.y + sinf(m_fAngle) * HOVER_RANGE;

	// 回す
	m_rot.y += D3DXToRadian(0.5);
	m_rot.x += D3DXToRadian(0.5);

	if (m_rot.y >= D3DXToRadian(360))
	{
		m_rot.y = 0.0f;
	}
	if (m_rot.x >= D3DXToRadian(360))
	{
		m_rot.x = 0.0f;
	}

	SetPos(pos);
	SetRot(m_rot);

	CScene3D::Update();
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CGoal::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// テクスチャ・モデルデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CGoal::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/goal.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	return S_OK;
}

//=============================================================================
// テクスチャ・モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CGoal::Unload(void)
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
CGoal *CGoal::Create(D3DXVECTOR3 pos)
{
	CGoal *pBlock = NULL;
	pBlock = new CGoal;
	pBlock->Init(pos);
	pBlock->SetPos(pos);
	return pBlock;
}
