//====================================================================
//
// �v���C���[12���� (player_hook.h)
// Author : ��{ ��
//
//====================================================================

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "player_hook.h"

//========================================
// �ÓI�����o�ϐ��錾
//========================================
LPDIRECT3DTEXTURE9 CPlayerHook::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayerHook::CPlayerHook()
{
	m_pos = DEFAULT_VECTOR;
	m_move = DEFAULT_VECTOR;
	m_bHook = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayerHook::~CPlayerHook()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayerHook::Init(void)
{
	CPlayer::Init();
	m_move = DEFAULT_VECTOR;
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayerHook::Uninit(void)
{
	CPlayer::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayerHook::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInput();

	m_pos = GetPos();

	if (pKeyboard->GetKeyboardTrigger(DIK_F) && m_bHook == false)
	{
		// ����Ƀt�b�N��������邩�T��
		// ��������Ȃ�t���O��true��
		m_bHook = true;

	}

	if (m_bHook)
	{
		// �����蔻��I�t
		// �v���C���[�̌����Ă�������̈�ԋ߂��ꏊ�Ƀt�b�N�ł̈ړ�����
		MoveToHook(TEST_HOOK_POS);
	}
	CPlayer::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayerHook::Draw(void)
{
	CPlayer::Draw();
}

//=============================================================================
// �t�b�N���΂�����
//=============================================================================
void CPlayerHook::ShotHook(D3DXVECTOR3 pos)
{
}

//=============================================================================
// �w�肵�����W�܂Ŕ�ԏ���
//=============================================================================
void CPlayerHook::MoveToHook(D3DXVECTOR3 pos)
{
	float distHorizon = 0.0f;
	float distVert = 0.0f;
	float fAngle = 0.0f;

	// �J�����̈ʒu���擾
	CCamera *pCamera;
	pCamera = CManager::GetCamera();
	CCamera::ORIENTATION Orientation = pCamera->GetOrientation();

	// �v���C���[�̃T�C�Y���ڕW���W�����炷
	pos.z = pos.z += PLAYER_SIZE.z / 2;

	// �w����W�Ƃ̋������o��
	if (Orientation == CCamera::ORIENTATION_BACK || Orientation == CCamera::ORIENTATION_FRONT)
	{
		distHorizon = pos.x - m_pos.x;
	}
	else if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT)
	{
		distHorizon = pos.z - m_pos.z;
	}

	distVert = pos.y - m_pos.y;

	// ��������p�x���v�Z
	fAngle = atan2f(distVert, distHorizon);

	// �ړ��ʂ��v�Z
	if (Orientation == CCamera::ORIENTATION_BACK || Orientation == CCamera::ORIENTATION_FRONT)
	{
		m_move = D3DXVECTOR3(cos(fAngle) * HOOK_SPD_RATE, sin(fAngle) * HOOK_SPD_RATE, 0.0f);
	}
	else if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT)
	{
		m_move = D3DXVECTOR3(0.0f, sin(fAngle) * HOOK_SPD_RATE, cos(fAngle) * HOOK_SPD_RATE);
	}

	// �ړ��ʂ����Z
	m_pos += m_move;

	// �t�b�N�ɂ��ړ����I�������t���O��false�ɂ���
	if (Orientation == CCamera::ORIENTATION_BACK || Orientation == CCamera::ORIENTATION_FRONT)
	{
		if (fabsf(pos.x - m_pos.x) <= HOOK_STOP_SIZE &&
			fabsf(pos.y - m_pos.y) <= HOOK_STOP_SIZE)
		{
			m_bHook = false;
		}
	}
	else if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT)
	{
		if (fabsf(pos.z - m_pos.z) <= HOOK_STOP_SIZE &&
			fabsf(pos.y - m_pos.y) <= HOOK_STOP_SIZE)
		{
			m_bHook = false;
		}
	}

	// �ʒu���X�V
	SetPos(m_pos);
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CPlayerHook * CPlayerHook::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz)
{
	CPlayerHook *pPlayerHook = NULL;
	pPlayerHook = new CPlayerHook;
	pPlayerHook->Init();
	pPlayerHook->SetPos(pos);
	pPlayerHook->SetSize(siz);
	return pPlayerHook;
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
void CPlayerHook::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Player2.jpg", &m_pTexture);
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CPlayerHook::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
