//========================
// インクルードファイル
//========================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "collisiondetection.h"
#include "polygon2d.h"

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

CPlayer::CPlayer(): CBillboard(OBJ_TYPE::OBJ_TYPE_PLAYER) {

}

CPlayer::~CPlayer() {

}

HRESULT CPlayer::Init(void) {
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CBillboard::Init();
	m_move = D3DXVECTOR3(MOVE_SIZ, 0, MOVE_SIZ);

	m_bJumpJudge = true;
	m_bCollisionDetectionJudge = false;

	return S_OK;
}

void CPlayer::Uninit(void) {
	CBillboard::Uninit();
}

void CPlayer::Update(void) {
	m_pCamera = CManager::GetCamera();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();
	m_pos = GetPos();

	if (m_pCamera->GetRotake() != CCamera::ROTATE_NONE) {
		m_pos = RotationDifferentialShift(Orientation);
	}

	CollisionDetection();

	if (m_pos.y <= 0) {
		m_pos.y = 0;
		SetJumpJudge(true);
		m_bCollisionDetectionJudge = true;
	}

	SetPos(m_pos);
	m_posold = m_pos;
	CBillboard::Update();
}

void CPlayer::CollisionDetection(void) {
	// ブロックとの当たり判定
	CObject *pObj = CObject::GetTopObj(CObject::OBJ_TYPE_BLOCK);
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();

	for (int nCntScene = 0; nCntScene < CObject::GetNumObj(CObject::OBJ_TYPE_BLOCK); nCntScene++) {
		// 中身があるなら
		if (pObj != NULL) {
			// 次のシーンを記憶
			CCollisionDetection *pCollisionDetection = (CCollisionDetection*)pObj;
			D3DXVECTOR3 pos = pCollisionDetection->GetPos();

			//ZかX軸が一致した場合
			if (pCollisionDetection->GetButtonColorBlock().bJudge == true) {
				m_bCollisionDetectionJudge = CollisionDetectionCalculation(m_posold, m_pos, PLAYER_SIZE, pos, PLAYER_SIZE, COLLISION::COLLISION_HEIGHT);

				if (m_bCollisionDetectionJudge == true) 
				{
					m_pos.y = pos.y + PLAYER_SIZE.y;
					SetJumpJudge(true);
					m_RidingBlockPos = pCollisionDetection->GetDefaultPos();

					if (pCollisionDetection->GetBlockType() == CCollisionDetection::BLOCKTYPE_BUTTON) {
						pCollisionDetection->BlockColorJudge(pCollisionDetection->GetButtonColorBlock().ButtonColor, true);
					}

					break;
				}
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

D3DXVECTOR3 CPlayer::RotationDifferentialShift(CCamera::ORIENTATION Orientation) 
{
	D3DXVECTOR3 Pos;

	if (Orientation == CCamera::ORIENTATION_FRONT) {
		Pos = D3DXVECTOR3(m_RidingBlockPos.x, m_pos.y + 0.01f, CCamera::ORIENTATION_FRONT_POS);
	}
	if (Orientation == CCamera::ORIENTATION_BACK) {
		Pos = D3DXVECTOR3(m_RidingBlockPos.x, m_pos.y + 0.01f, CCamera::ORIENTATION_BACK_POS);
	}
	if (Orientation == CCamera::ORIENTATION_LEFT) {
		Pos = D3DXVECTOR3(CCamera::ORIENTATION_LEFT_POS, m_pos.y + 0.01f, m_RidingBlockPos.z);
	}
	if (Orientation == CCamera::ORIENTATION_RIGHT) {
		Pos = D3DXVECTOR3(CCamera::ORIENTATION_RIGHT_POS, m_pos.y + 0.01f, m_RidingBlockPos.z);
	}

	return Pos;
}

void CPlayer::Draw(void) {
	CBillboard::Draw();
}