//========================
// インクルードファイル
//========================
#include "collisiondetection.h"
#include "manager.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CCollisionDetection::m_nNum = 0;
CCollisionDetection *CCollisionDetection::m_CollisionDetectionListTop;
CCollisionDetection *CCollisionDetection::m_CollisionDetectionListCur;

LPDIRECT3DTEXTURE9 CCollisionDetection::m_apTexture[BLOCK_TYPE_MAX] = {};


CCollisionDetection::CCollisionDetection() {

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
	UpdateByType(m_BlockType);
	CBillboard::SetPos(D3DXVECTOR3(m_pos));
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

void CCollisionDetection::Draw(void) {
	CBillboard::Draw();
}

CCollisionDetection *CCollisionDetection::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz, BLOCKTYPE BlockType) {
	CCollisionDetection* pCollisionDetection = NULL;
	pCollisionDetection = new CCollisionDetection;
	pCollisionDetection->Init();
	pCollisionDetection->SetPos(pos);
	pCollisionDetection->SetSize(siz);
	pCollisionDetection->BindTexture(m_apTexture[BlockType]);
	pCollisionDetection->SetType(CObject::OBJ_TYPE_BLOCK);

	pCollisionDetection->m_pos = pos;
	pCollisionDetection->m_siz = siz;
	pCollisionDetection->m_BlockType = BlockType;
	return pCollisionDetection;
}

void CCollisionDetection::ReleaseAll(void)
{

}