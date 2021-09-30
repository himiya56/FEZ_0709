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
#include "mode_game.h"
#include "player_hook.h"
#include "player_rotation.h"
#include "camera.h"

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
	CPlayerHook *pHook = CGameMode::GetPlayerHook();
	CPlayerRotation *pRot = CGameMode::GetPlayerRotation();

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
	
	CCamera *pCamera;
	pCamera = CManager::GetCamera();

	D3DXVECTOR3 hookPos = pHook->GetPos();
	D3DXVECTOR3 rotPos = pHook->GetPos();

	CCamera::ORIENTATION Orientation = pCamera->GetOrientation();

	if (Orientation == CCamera::ORIENTATION_FRONT &&
		0.0f <= hookPos.x && 75.0f >= hookPos.x && 75.0f * 24.0f <= hookPos.y &&
		0.0f <= rotPos.x && 75.0f >= rotPos.x && 75.0f * 24.0f <= rotPos.y)
	{
		CManager::StartFade(CManager::MODE_RESULT);
	}
	else if (Orientation == CCamera::ORIENTATION_BACK &&
		0.0f <= hookPos.x && 75.0f >= hookPos.x && 75.0f * 24.0f <= hookPos.y &&
		0.0f <= rotPos.x && 75.0f >= rotPos.x && 75.0f * 24.0f <= rotPos.y)
	{
		CManager::StartFade(CManager::MODE_RESULT);
	}
	else if (Orientation == CCamera::ORIENTATION_RIGHT &&
		-150.0f <= hookPos.z && 75.0f >= hookPos.z && 75.0f * 24.0f <= hookPos.y &&
		- 150.0f <= rotPos.z && 75.0f >= rotPos.z && 75.0f * 24.0f <= rotPos.y)
	{
		CManager::StartFade(CManager::MODE_RESULT);
	}
	else if (Orientation == CCamera::ORIENTATION_LEFT &&
		-150.0f <= hookPos.z && 75.0f >= hookPos.z && 75.0f * 24.0f <= hookPos.y &&
		-150.0f <= rotPos.z && 75.0f >= rotPos.z && 75.0f * 24.0f <= rotPos.y)
	{
		CManager::StartFade(CManager::MODE_RESULT);
	}
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
