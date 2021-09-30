//========================
// �C���N���[�h�t�@�C��
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
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice(JOYSTICK_1P);
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	//LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect(JOYSTICK_1P);
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	m_pos = GetPos();

	if (CPlayer::GetJumpJudge() == true && CGameMode::GetPlayerHook()->GetPlayerHookJump() == true && !pHook->GetHookState()) {
		// �J�����̉�]���Ăяo��
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
			// ���L�[�ō��ړ�
			if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000) {
				m_pos.x += m_move.x;
			}
			// ���L�[�ŉE�ړ�
			if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000) {
				m_pos.x -= m_move.x;
			}
			break;

		case CCamera::ORIENTATION_LEFT:
			// ���L�[�ō��ړ�
			if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000) {
				m_pos.z += m_move.z;
			}
			// ���L�[�ŉE�ړ�
			if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000) {
				m_pos.z -= m_move.z;
			}
			break;

		case CCamera::ORIENTATION_FRONT:
			// ���L�[�ō��ړ�
			if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000) {
				m_pos.x -= m_move.x;
			}
			// ���L�[�ŉE�ړ�
			if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000) {
				m_pos.x += m_move.x;
			}
			break;

		case CCamera::ORIENTATION_RIGHT:
			// ���L�[�ō��ړ�
			if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000) {
				m_pos.z -= m_move.z;
			}
			// ���L�[�ŉE�ړ�
			if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000) {
				m_pos.z += m_move.z;
			}
			break;
		}

		if (CPlayer::GetCollisionDetectionJudge() == false || m_pCamera->GetRotake() == CCamera::ROTATE_NONE) {
			m_move.y -= GRAVITY_SIZ;
		}

		// W�L�[�ŃW�����v
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