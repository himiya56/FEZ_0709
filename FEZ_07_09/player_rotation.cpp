//========================
// インクルードファイル
//========================
#include "player_rotation.h"
#include "player_hook.h"
#include "mode_game.h"
#include "manager.h"
#include "keyboard.h"
#include "collisiondetection.h"
#include "polygon2d.h"

LPDIRECT3DTEXTURE9 CPlayerRotation::m_pTexture = NULL;

CPlayerRotation::CPlayerRotation() {

}

CPlayerRotation::~CPlayerRotation() {

}

HRESULT CPlayerRotation::Init(void) {
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CPlayer::Init();
	m_move = MOVE_SPECIFIED;
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Character1.png", &m_pTexture);
	BindTexture(m_pTexture);

	m_bJumpJudge = true;

	return S_OK;
}

void CPlayerRotation::Uninit(void) {
	CPlayer::Uninit();
}

void CPlayerRotation::Update(void) {
	m_pCamera = CManager::GetCamera();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();
	m_pos = GetPos();
	m_move.y -= GRAVITY_SIZ;

	if (m_posold.y == 0) {
		m_posold.y = -1.0f;
	}

	m_pos = RotationDifferentialShift(Orientation, m_pos, m_pCamera->GetRotake(), m_pCamera->GetRotakeOld());

	if (m_bJumpJudge == true && CGameMode::GetPlayerHook()->GetPlayerHookJump() == true) {
		// カメラの回転を呼び出す
		m_pCamera->DecisionRotate(pKeyboard);
	}

	if (m_pCamera->GetRotake() == CCamera::ROTATE_NONE) {
		switch (Orientation) {
		case CCamera::ORIENTATION_BACK:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_A)) {
				m_pos.x += m_move.x;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_D)) {
				m_pos.x -= m_move.x;
			}
			break;

		case CCamera::ORIENTATION_LEFT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_A)) {
				m_pos.z += m_move.z;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_D)) {
				m_pos.z -= m_move.z;
			}
			break;

		case CCamera::ORIENTATION_FRONT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_A)) {
				m_pos.x -= m_move.x;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_D)) {
				m_pos.x += m_move.x;
			}
			break;

		case CCamera::ORIENTATION_RIGHT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_A)) {
				m_pos.z -= m_move.z;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_D)) {
				m_pos.z += m_move.z;
			}
			break;
		}

		// Wキーでジャンプ
		if (m_bJumpJudge == true) {
			if (pKeyboard->GetKeyboardTrigger(DIK_W)) {
				m_bJumpJudge = false;
				m_move.y = JUMP_SIZ;
			}
		}
	}

	m_pos.y += m_move.y;
	if (m_pos.y <= 0) {
		m_pos.y = 0;
		m_bJumpJudge = true;
	}

	SetCol(D3DXCOLOR(0, 0, 0, 255));
	SetPos(m_pos);
	CPlayer::Update();
}

void CPlayerRotation::Draw(void) {
	CPlayer::Draw();
}

CPlayerRotation *CPlayerRotation::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz) {
	CPlayerRotation *pPlayer = NULL;
	pPlayer = new CPlayerRotation;
	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetSize(siz);
	pPlayer->m_pos = pos;
	pPlayer->m_siz = siz;
	return pPlayer;
}