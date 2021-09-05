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
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Character1.1.png", &m_pTexture);
	BindTexture(m_pTexture);

	m_bJumpJudge = true;

	return S_OK;
}

void CPlayer::Uninit(void) {
	CBillboard::Uninit();
}

void CPlayer::Update(void) {
	m_pCamera = CManager::GetCamera();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();
	m_posold = m_pos;
	m_pos = GetPos();
	m_move.y -= GRAVITY_SIZ;

	if (m_posold.y == 0) {
		m_posold.y = -1.0f;
	}

	m_pos = RotationDifferentialShift(Orientation, m_pos, m_pCamera->GetRotake(), m_pCamera->GetRotakeOld());

	// カメラの回転を呼び出す
	m_pCamera->DecisionRotate(pKeyboard);

	if (m_pCamera->GetRotake() == CCamera::ROTATE_NONE) {
		switch (Orientation) {
		case CCamera::ORIENTATION_BACK:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.x += m_move.x;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.x -= m_move.x;
			}
			break;

		case CCamera::ORIENTATION_LEFT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.z += m_move.z;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.z -= m_move.z;
			}
			break;

		case CCamera::ORIENTATION_FRONT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.x -= m_move.x;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.x += m_move.x;
			}
			break;

		case CCamera::ORIENTATION_RIGHT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
				m_pos.z -= m_move.z;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
				m_pos.z += m_move.z;
			}
			break;
		}

		// スペースキーでジャンプ
		if (m_bJumpJudge == true && pKeyboard->GetKeyboardTrigger(DIK_UP)) {
			m_bJumpJudge = false;
			m_move.y = JUMP_SIZ;
		}
	}

	m_pos.y += m_move.y;
	if (m_pos.y <= 0) {
		m_pos.y = 0;
		m_bJumpJudge = true;
	}

	CollisionDetection();

	SetCol(D3DXCOLOR(0, 0, 0, 255));
	SetPos(m_pos);
	CBillboard::Update();
}

void CPlayer::CollisionDetection(void) {
	// ブロックとの当たり判定
	CObject *pObject = CObject::GetTopObj(OBJ_TYPE_BLOCK);
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();

	for (int nCntObj = 0; nCntObj < CObject::GetNumObj(OBJ_TYPE_BLOCK); nCntObj++) {
		// 中身があるなら
		if (pObject != NULL) {
			// 次のシーンを記憶
			CObject *pNextObj = pObject->GetNextObj();

			if (pObject->GetType() == CObject::OBJ_TYPE_BLOCK) {
				CCollisionDetection *pCollisionDetection = (CCollisionDetection*)pObject;

				//ZかX軸が一致した場合
				if (pCollisionDetection->GetPos().z == m_pos.z && Orientation == CCamera::ORIENTATION_FRONT || Orientation == CCamera::ORIENTATION_BACK ||
					pCollisionDetection->GetPos().x == m_pos.x && Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT) {

					if (CollisionDetectionCalculation(m_posold, m_pos, m_siz, pCollisionDetection->GetPos(), pCollisionDetection->GetSiz(), COLLISION::COLLISION_HEIGHT) == true) {
						m_pos.y = pCollisionDetection->GetPos().y + ((pCollisionDetection->GetSiz().y / 2) + (m_siz.y / 2));
						m_bJumpJudge = true;
					}
				}
			}

			// 次のシーンにする
			pObject = pNextObj;
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

CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz) {
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetSize(siz);
	pPlayer->m_pos = pos;
	pPlayer->m_siz = siz;
	return pPlayer;
}