//========================
// インクルードファイル
//========================
#include "collisiondetection.h"
#include "manager.h"
#include "camera.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CCollisionDetection::m_nNum = 0;
CCollisionDetection *CCollisionDetection::m_CollisionDetectionListTop;
CCollisionDetection *CCollisionDetection::m_CollisionDetectionListCur;

LPDIRECT3DTEXTURE9 CCollisionDetection::m_apTexture[BLOCK_TYPE_MAX] = {};


CCollisionDetection::CCollisionDetection() :CBillboard(OBJ_TYPE::OBJ_TYPE_BLOCK){

}

CCollisionDetection::~CCollisionDetection() {

}

HRESULT CCollisionDetection::Init(void) {
	CBillboard::Init();

	return S_OK;
}

void CCollisionDetection::Uninit(void) {
	CBillboard::Uninit();
}

void CCollisionDetection::Update(void) {

	CCamera *pCamera = CManager::GetCamera();
	CCamera::ORIENTATION orientarion = pCamera->GetOrientation();
	CCamera::ROTATE rotate = pCamera->GetRotake();

	// 回転中は基準座標に戻す
	if (rotate == CCamera::ROTATE_LEFT ||
		rotate == CCamera::ROTATE_RIGHT)
	{
		m_pos = m_defaultPos;
	}
	else if(m_BlockType == BLOCKTYPE_NONE)
	{
		switch (orientarion)
		{
		case CCamera::ORIENTATION_FRONT:
			if (-75.0f > m_defaultPos.x ||
				150.0f < m_defaultPos.x)
			{
				m_pos = D3DXVECTOR3(m_pos.x, m_pos.y, CCamera::ORIENTATION_FRONT_POS);
			}
			break;
		case CCamera::ORIENTATION_BACK:
			if (-75.0f > m_defaultPos.x ||
				150.0f < m_defaultPos.x)
			{
				m_pos = D3DXVECTOR3(m_pos.x, m_pos.y, CCamera::ORIENTATION_BACK_POS);
			}
			break;
		case CCamera::ORIENTATION_LEFT:
			if (-150.0f > m_defaultPos.z ||
				75.0f < m_defaultPos.z)
			{
				m_pos = D3DXVECTOR3(CCamera::ORIENTATION_LEFT_POS, m_pos.y, m_pos.z);
			}
			break;
		case CCamera::ORIENTATION_RIGHT:
			if (-150.0f > m_defaultPos.z ||
				75.0f < m_defaultPos.z)
			{
				m_pos = D3DXVECTOR3(CCamera::ORIENTATION_RIGHT_POS, m_pos.y, m_pos.z);
			}
			break;
		default:
			break;
		}
	}

	UpdateByType(m_BlockType);
	CBillboard::SetPos(m_pos);
	CBillboard::SetSize(m_siz);
	CBillboard::SetCol(D3DXCOLOR(255, 255, 255, 255));
	CBillboard::Update();
}

void CCollisionDetection::UpdateByType(BLOCKTYPE BlockType) {
	switch (BlockType) {
	case BLOCKTYPE_HOOK:
		break;

	case BLOCKTYPE_BUTTON:
		break;

	case BLOCKTYPE_BUTTON_INCLUDED:
		break;
	}
}

void CCollisionDetection::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/block1_1.png", &m_apTexture[BLOCKTYPE_NONE]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/jimmy-malachier-tile-metal-01.jpg", &m_apTexture[BLOCKTYPE_WALL]);
}

void CCollisionDetection::Unload(void)
{
	for (int nCount = 0; nCount < BLOCK_TYPE_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

void CCollisionDetection::Draw(void) 
{
	if (m_BlockType != BLOCKTYPE_NONE)
	{
		CBillboard::Draw();
	}
}

CCollisionDetection *CCollisionDetection::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz, BLOCKTYPE BlockType) {
	CCollisionDetection* pCollisionDetection = NULL;
	pCollisionDetection = new CCollisionDetection;
	pCollisionDetection->Init();
	pCollisionDetection->SetPos(pos);
	pCollisionDetection->SetSize(siz);
	pCollisionDetection->BindTexture(m_apTexture[BlockType]);

	pCollisionDetection->m_pos = pos;
	pCollisionDetection->m_defaultPos = pos;
	pCollisionDetection->m_siz = siz;
	pCollisionDetection->m_BlockType = BlockType;

	if (BlockType == BLOCKTYPE_NONE)
	{
		CBlock::Create(pos);
	}

	return pCollisionDetection;
}

void CCollisionDetection::ReleaseAll(void)
{

}