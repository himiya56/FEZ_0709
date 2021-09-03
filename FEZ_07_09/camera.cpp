//===============================================
//
// �J�������� (camera.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "player.h"
#include "player_hook.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixIdentity(&m_mtxProjection);

	m_posV = DEFAULT_VECTOR;
	m_posR = DEFAULT_VECTOR;
	m_posVDest = DEFAULT_VECTOR;
	m_posRDest = DEFAULT_VECTOR;
	m_fVerticalAngle = D3DXToRadian(270);
	m_fHorizontalAngle = D3DXToRadian(90);
	m_fOffset = INIT_OFFSET;
	m_fFOV = 90.0f;
	m_rotDir = ROTATE_NONE;
	m_rotDirOld = m_rotDir;
	m_nRotateCountFrame = 0;
	m_Orientation = ORIENTATION_FRONT;
	m_nOrientation = m_Orientation;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_posV = DEFAULT_VECTOR;
	m_posR = DEFAULT_VECTOR;
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fFOV = 90.0f;
	m_FollowPos = DEFAULT_VECTOR;

	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(m_fFOV), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 10000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	m_rotDirOld = m_rotDir;

	// �ړI�n�̌v�Z(���ʍ��W)
	m_posVDest.x = m_fOffset * (sinf(m_fHorizontalAngle) * cosf(m_fVerticalAngle));
	m_posVDest.y = m_fOffset * cosf(m_fHorizontalAngle) + 75.0f * 6.0f;
	m_posVDest.z = m_fOffset * (sinf(m_fHorizontalAngle) * sinf(m_fVerticalAngle));

	m_posRDest.y = 75.0f * 6.0f;

	// �ړI�n�ɋ߂Â���
	m_posR += (m_posRDest - m_posR) * 0.9f;
	m_posV += (m_posVDest - m_posV) * 0.9f;

	// ���W�X�V
	SetTargetPos(m_posR);
	SetPos(m_posV);

	// �J�����A�b�v�f�[�g
	SetCamera();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCamera::Draw(void)
{
}

//=============================================================================
// �J�����X�V����(�������e)
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(m_fFOV), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 10000.0f);
	D3DXMatrixOrthoLH(&m_mtxProjection, SCREEN_WIDTH, SCREEN_HEIGHT, 10.0f, 10000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//=============================================================================
// �J������90�x��]�����鏈��
//=============================================================================
void CCamera::RotateCamera(ROTATE dir)
{
	if (dir != ROTATE_NONE) {
		switch (dir)
		{
		case ROTATE_RIGHT:
			m_fVerticalAngle += D3DXToRadian(CAMERA_ROTATE_ANGLE / CAMERA_ROTATE_FRAME_LENGTH);
			if (m_fVerticalAngle >= D3DXToRadian(360))
			{
				m_fVerticalAngle = 0;
			}
			break;

		case ROTATE_LEFT:
			m_fVerticalAngle -= D3DXToRadian(CAMERA_ROTATE_ANGLE / CAMERA_ROTATE_FRAME_LENGTH);
			if (m_fVerticalAngle >= D3DXToRadian(360))
			{
				m_fVerticalAngle = 0;
			}
			break;

		default:
			break;
		}

		m_nRotateCountFrame++;
		if (m_nRotateCountFrame >= CAMERA_ROTATE_FRAME_LENGTH)
		{
			m_nRotateCountFrame = 0;
			m_rotDir = ROTATE_NONE;
		}
	}
}

//=============================================================================
// �ǂ̕������猩�Ă��邩�𐧌�
//=============================================================================
void CCamera::OrientationControl(ROTATE dir) {
	if (dir != ROTATE_NONE && m_rotDirOld == ROTATE_NONE) {
		switch (dir) {
		case ROTATE_RIGHT:
			if (++m_nOrientation >= ORIENTATION_MAX) {
				m_nOrientation = ORIENTATION_BACK;
			}
			break;

		case ROTATE_LEFT:
			if (--m_nOrientation < 0) {
				m_nOrientation = ORIENTATION_MAX - 1;
			}
			break;

		default:
			break;
		}
	}

	m_Orientation = ORIENTATION(m_nOrientation);
}

//=============================================================================
// �J��������
//=============================================================================
CCamera *CCamera::Create(void)
{
	CCamera *pCamera;
	pCamera = new CCamera;
	pCamera->Init();
	return pCamera;
}

//=============================================================================
// ��]����������
//=============================================================================
void CCamera::DecisionRotate(CInputKeyboard *pInputKeyboard) {
	if (m_rotDir == ROTATE_NONE)
	{
		// A�L�[�ŉE��]
		if (pInputKeyboard->GetKeyboardTrigger(DIK_A))
		{
			m_rotDir = ROTATE_RIGHT;
		}
		// D�L�[�ō���]
		if (pInputKeyboard->GetKeyboardTrigger(DIK_D))
		{
			m_rotDir = ROTATE_LEFT;
		}
	}

	RotateCamera(m_rotDir);
	OrientationControl(m_rotDir);
}