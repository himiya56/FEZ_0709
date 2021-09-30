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
#include "joystick.h"

LPDIRECT3DTEXTURE9 CPlayerRotation::m_pTexture = NULL;

CPlayerRotation::CPlayerRotation() {

}

CPlayerRotation::~CPlayerRotation() {

}

HRESULT CPlayerRotation::Init(void) {
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CPlayer::Init();
	m_move = MOVE_SPECIFIED;
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Character1.png", &m_pTexture);
	BindTexture(m_pTexture);

	return S_OK;
}

void CPlayerRotation::Uninit(void) {
	CPlayer::Uninit();
}

void CPlayerRotation::Update(void) 
{
	m_pCamera = CManager::GetCamera();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();
	CPlayerHook *pHook = CGameMode::GetPlayerHook();
	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice(JOYSTICK_1P);
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	//LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect(JOYSTICK_1P);
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	m_pos = GetPos();

	if (CPlayer::GetJumpJudge() == true && CGameMode::GetPlayerHook()->GetPlayerHookJump() == true && !pHook->GetHookState()) {
		// カメラの回転を呼び出す
		m_pCamera->DecisionRotate(pKeyboard, pJoystick);
	}

	if (CPlayer::GetCollisionDetectionJudge() == true ||
		m_pCamera->GetRotake() != CCamera::ROTATE_NONE) {
		m_move.y = 0.0f;
	}
	if (m_pCamera->GetRotake() == CCamera::ROTATE_NONE)
	{
		switch (Orientation)
		{
		case CCamera::ORIENTATION_BACK:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000) {
				m_pos.x += m_move.x;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000) {
				m_pos.x -= m_move.x;
			}
			break;

		case CCamera::ORIENTATION_LEFT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000) {
				m_pos.z += m_move.z;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000) {
				m_pos.z -= m_move.z;
			}
			break;

		case CCamera::ORIENTATION_FRONT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000) {
				m_pos.x -= m_move.x;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000) {
				m_pos.x += m_move.x;
			}
			break;

		case CCamera::ORIENTATION_RIGHT:
			// ←キーで左移動
			if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000) {
				m_pos.z -= m_move.z;
			}
			// →キーで右移動
			if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000) {
				m_pos.z += m_move.z;
			}
			break;
		}

		if (CPlayer::GetCollisionDetectionJudge() == false || m_pCamera->GetRotake() == CCamera::ROTATE_NONE) {
			m_move.y -= GRAVITY_SIZ;
		}

		// Wキーでジャンプ
		if (CPlayer::GetJumpJudge() == true && CPlayer::GetCollisionDetectionJudge() == true)
		{
			if (pKeyboard->GetKeyboardTrigger(DIK_W) || lpDIDevice != NULL && pJoystick->GetJoystickTrigger(JS_A, JOYSTICK_1P))
			{
				CPlayer::SetJumpJudge(false);
				m_move.y = JUMP_SIZ;
			}
		}
	}

	m_pos.y += m_move.y;

	SetPos(m_pos);
	CPlayer::Update();
}

void CPlayerRotation::Draw(void) 
{
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