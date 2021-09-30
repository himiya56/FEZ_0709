//========================
// インクルードファイル
//========================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "collisiondetection.h"
#include "polygon2d.h"

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

CPlayer::CPlayer() {

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

	m_pos = RotationDifferentialShift(Orientation, m_pos, m_pCamera->GetRotake(), m_pCamera->GetRotakeOld());

	CollisionDetection();

	if (m_pos.y <= 0) {
		m_pos.y = 0;
		SetJumpJudge(true);
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
			if (pos.z == m_pos.z && Orientation == CCamera::ORIENTATION_FRONT || Orientation == CCamera::ORIENTATION_BACK ||
				pos.x == m_pos.x && Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT) {
				m_bCollisionDetectionJudge = CollisionDetectionCalculation(m_posold, m_pos, PLAYER_SIZE, pos, PLAYER_SIZE, COLLISION::COLLISION_HEIGHT);

				if (m_bCollisionDetectionJudge == true) 
				{
					m_pos.y = pos.y + PLAYER_SIZE.y;
					SetJumpJudge(true);
					m_RidingBlockPos = pos;
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

D3DXVECTOR3 CPlayer::RotationDifferentialShift(CCamera::ORIENTATION Orientation, D3DXVECTOR3 PlayerPos, CCamera::ROTATE Rotate, CCamera::ROTATE RotateOld) 
{
	D3DXVECTOR3 Pos = PlayerPos;

	if (Orientation == CCamera::ORIENTATION_FRONT) {
		Pos = D3DXVECTOR3(PlayerPos.x, PlayerPos.y, CCamera::ORIENTATION_FRONT_POS);
	}
	if (Orientation == CCamera::ORIENTATION_BACK) {
		Pos = D3DXVECTOR3(PlayerPos.x, PlayerPos.y, CCamera::ORIENTATION_BACK_POS);
	}
	if (Orientation == CCamera::ORIENTATION_LEFT) {
		Pos = D3DXVECTOR3(CCamera::ORIENTATION_LEFT_POS, PlayerPos.y, PlayerPos.z);
	}
	if (Orientation == CCamera::ORIENTATION_RIGHT) {
		Pos = D3DXVECTOR3(CCamera::ORIENTATION_RIGHT_POS, PlayerPos.y, PlayerPos.z);
	}

	return Pos;
}

void CPlayer::Draw(void) {
	CBillboard::Draw();
}