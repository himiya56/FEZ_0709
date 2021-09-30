//====================================================================
//
// �v���C���[2���� (player_hook.cpp)
// Author : ��{ ��
//
//====================================================================

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "player_hook.h"
#include "wire.h"
#include "spike.h"
#include "joystick.h"

//========================================
// �ÓI�����o�ϐ��錾
//========================================
LPDIRECT3DTEXTURE9 CPlayerHook::m_pTexture = NULL;
CWire *pWire = NULL;

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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CPlayer::Init();
	m_move = MOVE_SPECIFIED;
	BindTexture(m_pTexture);

	m_bJumpJudge = true;
	m_nAnimCount = 0.0f;

	pWire = CWire::Create(D3DXVECTOR3(200.0f, 50.0f, 0.0f));
	SetTexUVX(0.8f,1.0f);
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
	m_pCamera = CManager::GetCamera();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice(JOYSTICK_2P);
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	//LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect(JOYSTICK_2P);
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	D3DXVECTOR3 destPos;
	D3DXVECTOR2 texUV = GetTexUVX();

	m_pos = GetPos();
	destPos = SortSpike();

	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) && m_bHook == false && m_pCamera->GetRotake() == CCamera::ROTATE_NONE)
	{
		// ����Ƀt�b�N��������邩�T��
		// ��������Ȃ�t���O��true��
		m_bHook = true;
	}
	if (m_bHook)
	{
		// �����蔻��I�t
		// �v���C���[�̈�ԋ߂��ꏊ�Ƀt�b�N�ł̈ړ�����
		if (destPos != DEFAULT_VECTOR)
		{
			MoveToHook(destPos);
			texUV = D3DXVECTOR2(0.8f, 1.0f);
		}
		else
		{
			m_bHook = false;
		}
	}
	else
	{
		if (CPlayer::GetCollisionDetectionJudge() == true ||
			m_pCamera->GetRotake() != CCamera::ROTATE_NONE) {
			m_move.y = 0.0f;
		}
		// �v���C���[����
		if (m_pCamera->GetRotake() == CCamera::ROTATE_NONE) 
		{

			switch (Orientation) {
			case CCamera::ORIENTATION_BACK:
				// ���L�[�ō��ړ�
				if (pKeyboard->GetKeyboardPress(DIK_LEFT) || lpDIDevice != NULL &&js.lX == -1000) {
					m_pos.x += m_move.x;
					m_nAnimCount++;
					SetTexDir(1);
				}
				// ���L�[�ŉE�ړ�
				if (pKeyboard->GetKeyboardPress(DIK_RIGHT) || lpDIDevice != NULL &&js.lX == 1000) {
					m_pos.x -= m_move.x;
					m_nAnimCount++;
					SetTexDir(0);
				}
				break;

			case CCamera::ORIENTATION_LEFT:
				// ���L�[�ō��ړ�
				if (pKeyboard->GetKeyboardPress(DIK_LEFT) || lpDIDevice != NULL &&js.lX == -1000) {
					m_pos.z += m_move.z;
					m_nAnimCount++;
					SetTexDir(1);
				}
				// ���L�[�ŉE�ړ�
				if (pKeyboard->GetKeyboardPress(DIK_RIGHT) || lpDIDevice != NULL &&js.lX == 1000) {
					m_pos.z -= m_move.z;
					m_nAnimCount++;
					SetTexDir(0);
				}
				break;

			case CCamera::ORIENTATION_FRONT:
				// ���L�[�ō��ړ�
				if (pKeyboard->GetKeyboardPress(DIK_LEFT) || lpDIDevice != NULL &&js.lX == -1000) {
					m_pos.x -= m_move.x;
					m_nAnimCount++;
					SetTexDir(1);
				}
				// ���L�[�ŉE�ړ�
				if (pKeyboard->GetKeyboardPress(DIK_RIGHT) || lpDIDevice != NULL &&js.lX == 1000) {
					m_pos.x += m_move.x;
					m_nAnimCount++;
					SetTexDir(0);
				}
				break;

			case CCamera::ORIENTATION_RIGHT:
				// ���L�[�ō��ړ�
				if (pKeyboard->GetKeyboardPress(DIK_LEFT) || lpDIDevice != NULL &&js.lX == -1000) {
					m_pos.z -= m_move.z;
					m_nAnimCount++;
					SetTexDir(1);
				}
				// ���L�[�ŉE�ړ�
				if (pKeyboard->GetKeyboardPress(DIK_RIGHT) || lpDIDevice != NULL &&js.lX == 1000) {
					m_pos.z += m_move.z;
					m_nAnimCount++;
					SetTexDir(0);
				}
				break;
			default:
				texUV = D3DXVECTOR2(0.8f, 1.0f);
				m_nAnimCount = 0;
				break;
			}

			if (CPlayer::GetCollisionDetectionJudge() == false || m_pCamera->GetRotake() == CCamera::ROTATE_NONE) {
				m_move.y -= GRAVITY_SIZ;
			}

			// W�L�[�ŃW�����v
			if (CPlayer::GetJumpJudge() == true && CPlayer::GetCollisionDetectionJudge() == true)
			{
				if (pKeyboard->GetKeyboardTrigger(DIK_UP) || lpDIDevice != NULL && pJoystick->GetJoystickTrigger(JS_A, JOYSTICK_1P))
				{
					CPlayer::SetJumpJudge(false);
					m_move.y = JUMP_SIZ;
					texUV = D3DXVECTOR2(0.8f, 1.0f);
					m_nAnimCount = 0;
				}
			}
		}
	}

	m_pos.y += m_move.y;
	if (m_nAnimCount >=  ANIM_RATE)
	{
		texUV.x += 0.2f;
		texUV.y += 0.2f;
		if (texUV.y >= 1.0f)
		{
			texUV.x = 0.0f;
			texUV.y = 0.2f;
		}
		m_nAnimCount = 0;
	}

	m_bJumpJudge = CPlayer::GetJumpJudge();

	SetTexUVX(texUV.x, texUV.y);
	SetPos(m_pos);
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
// �t�b�N�n�_�\�[�g����
//=============================================================================
D3DXVECTOR3 CPlayerHook::SortSpike(void)
{

	// ����
	float distHorizon = 0.0f;
	float distVert = 0.0f;
	float dist = 0.0f;
	int nArrayCount = 0;

	// �t�b�N�n�_
	CObject *pObj;
	pObj = CObject::GetTopObj(CObject::OBJ_TYPE_SPIKE);
	D3DXVECTOR3 spikePos = DEFAULT_VECTOR;
	D3DXVECTOR3 destPos = DEFAULT_VECTOR;
	CSpike *pDestSpike = NULL;

	// �J�����̈ʒu���擾
	CCamera *pCamera;
	pCamera = CManager::GetCamera();
	CCamera::ORIENTATION Orientation = pCamera->GetOrientation();
	SPIKE spike[50];

	for (int nCntScene = 0; nCntScene < CObject::GetNumObj(CObject::OBJ_TYPE_SPIKE); nCntScene++)
	{
		// ���g������Ȃ�
		if (pObj != NULL)
		{
			// ���̃V�[�����L��
			CObject *pNextObj = pObj->GetNextObj();

			// �u���b�N�ɃL���X�g
			CSpike *pSpike = (CSpike*)pObj;

			spikePos = pSpike->GetPos();
			spike[nCntScene].pos = spikePos;

			// �������v�Z
			if (Orientation == CCamera::ORIENTATION_BACK || Orientation == CCamera::ORIENTATION_FRONT)
			{
				distHorizon = spikePos.x - m_pos.x;
				distVert = spikePos.y - m_pos.y;
			}
			else if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT)
			{
				distHorizon = spikePos.z - m_pos.z;
				distVert = spikePos.y - m_pos.y;
			}

			spike[nCntScene].dist = sqrtf(distHorizon*distHorizon + distVert*distVert);

			// �͈͊O��spike�����O
			if (Orientation == CCamera::ORIENTATION_FRONT &&
				0.0f <= spikePos.x && 75.0f >= spikePos.x && -75.0f / 2 >= spikePos.z)
			{
				spike[nCntScene].dist = 10000.0f;
			}
			else if (Orientation == CCamera::ORIENTATION_BACK &&
				0.0f <= spikePos.x && 75.0f >= spikePos.x && -75.0f / 2 <= spikePos.z)
			{
				spike[nCntScene].dist = 10000.0f;
			}
			else if (Orientation == CCamera::ORIENTATION_RIGHT &&
				-150.0f <= spikePos.z && 75.0f >= spikePos.z && 150.0f >= spikePos.x)
			{
				spike[nCntScene].dist = 10000.0f;
			}
			else if (Orientation == CCamera::ORIENTATION_LEFT &&
				-150.0f <= spikePos.z && 75.0f >= spikePos.z && 0.0f <= spikePos.x)
			{
				spike[nCntScene].dist = 10000.0f;
			}
			else if (m_pos.y > spikePos.y)
			{
				spike[nCntScene].dist = 10000.0f;
			}

			if (nCntScene == 0)
			{
				spike[0].pSpike = pSpike;
			}
			else if (spike[nCntScene].dist < spike[nArrayCount].dist)
			{
				nArrayCount = nCntScene;
				spike[nArrayCount].pSpike = pSpike;
				spike[0].pSpike->SetTexture(CSpike::SPIKE_NONE);
			}
			else
			{
				pSpike->SetTexture(CSpike::SPIKE_NONE);
			}

			spike[nArrayCount].pSpike->SetTexture(CSpike::SPIKE_LOCK);

			// ���̃V�[���ɂ���
			pObj = pNextObj;
		}
		else
		{
			break;
		}
	}

	spike[nArrayCount].pos.y += 3.5f;

	if (spike[nArrayCount].dist <= 500.0f)
	{
		return spike[nArrayCount].pos;
	}
	else
	{
		return DEFAULT_VECTOR;
	}

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
	// ����
	float distHorizon = 0.0f;
	float distVert = 0.0f;
	// �p�x
	float fAngle = 0.0f;

	// �J�����̈ʒu���擾
	CCamera *pCamera;
	pCamera = CManager::GetCamera();
	CCamera::ORIENTATION Orientation = pCamera->GetOrientation();

	// �v���C���[�̃T�C�Y���ڕW���W�����炷
	pos.z += PLAYER_SIZE.z / 2.0f;

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

	// �v���C���[�ւ̊p�x�����Z
	m_circle.fAngle += D3DXToRadian(90) / HOOK_MOVE_FRAME;
	// 180���ȏ�ŏC��
	if (m_circle.fAngle >= D3DXToRadian(90))
	{
		m_circle.fAngle = D3DXToRadian(90);
	}

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
	m_pos += m_move * sinf(m_circle.fAngle);

	// �t�b�N�ɂ��ړ����I�������t���O��false�ɂ���
	if (Orientation == CCamera::ORIENTATION_BACK || Orientation == CCamera::ORIENTATION_FRONT)
	{
		if (fabsf(pos.x - m_pos.x) <= HOOK_STOP_SIZE &&
			fabsf(pos.y - m_pos.y) <= HOOK_STOP_SIZE)
		{
			m_bHook = false;
			m_circle.fAngle = 0.0f;
			m_move = MOVE_SPECIFIED;
		}
	}
	else if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT)
	{
		if (fabsf(pos.z - m_pos.z) <= HOOK_STOP_SIZE &&
			fabsf(pos.y - m_pos.y) <= HOOK_STOP_SIZE)
		{
			m_bHook = false;
			m_circle.fAngle = 0.0f;
			m_move = MOVE_SPECIFIED;
		}
	}

	// �ʒu���X�V
	m_move = MOVE_SPECIFIED;
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

	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Character2_Animation.png", &m_pTexture);
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
