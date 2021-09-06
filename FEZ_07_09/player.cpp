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

	return S_OK;
}

void CPlayer::Uninit(void) {
	CBillboard::Uninit();
}

void CPlayer::Update(void) {
	m_pCamera = CManager::GetCamera();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();
	m_posold = m_pos;

	if (m_posold.y == 0) {
		m_posold.y = -1.0f;
	}

	m_pos = RotationDifferentialShift(Orientation, m_pos, m_pCamera->GetRotake(), m_pCamera->GetRotakeOld());

	CollisionDetection();

	SetCol(D3DXCOLOR(0, 0, 0, 255));
	CBillboard::SetPos(m_pos);
	CBillboard::Update();
}

void CPlayer::CollisionDetection(void) {
	// ブロックとの当たり判定
	CCollisionDetection *pCollisionDetection = CCollisionDetection::GetCollisionDetectionOrientation();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();

	for (int nCntScene = 0; nCntScene < CCollisionDetection::GetNumAll(); nCntScene++) {
		// 中身があるなら
		if (pCollisionDetection != NULL) {
			// 次のシーンを記憶
			CCollisionDetection *pNextScene = pCollisionDetection->GetNextScene();

			//ZかX軸が一致した場合
			if (pCollisionDetection->GetPos().z == m_pos.z && Orientation == CCamera::ORIENTATION_FRONT || Orientation == CCamera::ORIENTATION_BACK ||
				pCollisionDetection->GetPos().x == m_pos.x && Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT) {
				bool bCollisionDetectionJudge = CollisionDetectionCalculation(m_posold, m_pos, m_siz, pCollisionDetection->GetPos(), pCollisionDetection->GetSiz(), COLLISION::COLLISION_HEIGHT);

				if (bCollisionDetectionJudge == true) {
					m_pos.y = pCollisionDetection->GetPos().y + ((pCollisionDetection->GetSiz().y / 2) + (m_siz.y / 2));
					m_bJumpJudge = true;
				}
			}

			// 次のシーンにする
			pCollisionDetection = pNextScene;
		}
		else {
			// 中身がないなら、そこで処理を終える
			break;
		}
	}
}

D3DXVECTOR3 CPlayer::RotationDifferentialShift(CCamera::ORIENTATION Orientation, D3DXVECTOR3 PlayerPos, CCamera::ROTATE Rotate, CCamera::ROTATE RotateOld) {
	D3DXVECTOR3 Pos = PlayerPos;
	D3DXVECTOR3 SavePlayerPos;

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