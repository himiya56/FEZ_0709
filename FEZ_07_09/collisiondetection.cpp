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
	m_nNum++;
}

CCollisionDetection::~CCollisionDetection() {
	m_nNum--;
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

	BlockShift(m_BlockType, pCamera, orientarion, rotate);
	UpdateByType(m_BlockType);
	CBillboard::SetPos(m_pos);
	CBillboard::SetSize(m_siz);
	CBillboard::SetCol(D3DXCOLOR(255, 255, 255, 255));
	CBillboard::Update();
}

void CCollisionDetection::BlockShift(BLOCKTYPE BlockType, CCamera *pCamera, CCamera::ORIENTATION orientarion, CCamera::ROTATE rotate) {
	// 回転中は基準座標に戻す
	if (rotate == CCamera::ROTATE_LEFT ||
		rotate == CCamera::ROTATE_RIGHT)
	{
		m_pos = m_defaultPos;
	}
	else if (BlockType != BLOCKTYPE_NULL)
	{
		switch (orientarion)
		{
		case CCamera::ORIENTATION_FRONT:
			if (-75.0f >= m_defaultPos.x ||
				150.0f <= m_defaultPos.x ||
				-75.0f <= m_defaultPos.x && 150.0f >= m_defaultPos.x && -75.0f / 2 >= m_defaultPos.z)
			{
				m_pos = D3DXVECTOR3(m_pos.x, m_pos.y, CCamera::ORIENTATION_FRONT_POS);
			}
			break;
		case CCamera::ORIENTATION_BACK:
			if (-75.0f >= m_defaultPos.x ||
				150.0f <= m_defaultPos.x ||
				-75.0f <= m_defaultPos.x && 150.0f >= m_defaultPos.x && -75.0f / 2 <= m_defaultPos.z)
			{
				m_pos = D3DXVECTOR3(m_pos.x, m_pos.y, CCamera::ORIENTATION_BACK_POS);
			}
			break;
		case CCamera::ORIENTATION_LEFT:
			if (-150.0f >= m_defaultPos.z ||
				75.0f <= m_defaultPos.z ||
				-150.0f <= m_defaultPos.z && 75.0f >= m_defaultPos.z && 0.0f >= m_defaultPos.x)
			{
				m_pos = D3DXVECTOR3(CCamera::ORIENTATION_LEFT_POS, m_pos.y, m_pos.z);
			}
			break;
		case CCamera::ORIENTATION_RIGHT:
			if (-150.0f >= m_defaultPos.z ||
				75.0f <= m_defaultPos.z ||
				-150.0f <= m_defaultPos.z && 75.0f >= m_defaultPos.z && 150.0f <= m_defaultPos.x)
			{
				m_pos = D3DXVECTOR3(CCamera::ORIENTATION_RIGHT_POS, m_pos.y, m_pos.z);
			}
			break;
		default:
			break;
		}
	}
}

void CCollisionDetection::UpdateByType(BLOCKTYPE BlockType) {
	switch (BlockType) {
	case BLOCKTYPE_BUTTON:
		break;
	}
}

void CCollisionDetection::BlockColorJudge(CCollisionDetection::BUTTONCOLOR ButtonColor, bool Judge) {
	CObject *pObj = CObject::GetTopObj(CObject::OBJ_TYPE_BLOCK);

	for (int nCntScene = 0; nCntScene < CObject::GetNumObj(CObject::OBJ_TYPE_BLOCK); nCntScene++) {
		// 中身があるなら
		if (pObj != NULL) {
			// 次のシーンを記憶
			CCollisionDetection *pCollisionDetection = (CCollisionDetection*)pObj;

			if (pCollisionDetection->m_ButtonColorBlock.ButtonColor == ButtonColor) {
				pCollisionDetection->m_ButtonColorBlock.bJudge = Judge;
			}

			// 次のシーンにする
			pObj = pObj->GetNextObj();
		}
		else {
			// 中身がないなら、そこで処理を終える
			break;
		}
	}
}

void CCollisionDetection::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/block1_1.png", &m_apTexture[BLOCKTYPE_NONE]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/block1_0.png", &m_apTexture[BLOCKTYPE_BUTTON_INCLUDED]);
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
	if (m_BlockType != BLOCKTYPE_NULL /*&& m_ButtonColorBlock.bJudge == true*/) 
	{
		CBillboard::Draw();
	}
}

CCollisionDetection *CCollisionDetection::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz, BLOCKTYPE BlockType, BUTTONCOLOR ButtonColor) {
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

	//CBlock::Create(pos);

	switch (BlockType) {
	case BLOCKTYPE_BUTTON_INCLUDED:
		pCollisionDetection->m_ButtonColorBlock.ButtonColor = ButtonColor;
		pCollisionDetection->m_ButtonColorBlock.bJudge = false;
		break;

	case BLOCKTYPE_BUTTON:
		pCollisionDetection->m_ButtonColorBlock.ButtonColor = ButtonColor;
		pCollisionDetection->m_ButtonColorBlock.bJudge = true;
		break;

	default:
		pCollisionDetection->m_ButtonColorBlock.bJudge = true;
		break;
	}

	return pCollisionDetection;
}

void CCollisionDetection::ReleaseAll(void)
{

}