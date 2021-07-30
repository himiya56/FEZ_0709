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
	CPlayer::Init();
	m_move = DEFAULT_VECTOR;
	BindTexture(m_pTexture);
	pWire = CWire::Create(D3DXVECTOR3(200.0f, 50.0f, 0.0f));
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
	D3DXVECTOR3 destPos;

	m_pos = GetPos();
	destPos = SortSpike();


	if (pKeyboard->GetKeyboardTrigger(DIK_F) && m_bHook == false)
	{
		// ����Ƀt�b�N��������邩�T��
		// ��������Ȃ�t���O��true��
		m_bHook = true;

	}

	if (m_bHook)
	{
		// �����蔻��I�t
		// �v���C���[�̈�ԋ߂��ꏊ�Ƀt�b�N�ł̈ړ�����
		MoveToHook(destPos);
	}
	else
	{
		// �v���C���[����
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

			if (nCntScene == 0)
			{
				spike[0].pSpike = pSpike;
			}
			else if (spike[nCntScene].dist < spike[nArrayCount].dist)
			{
				nArrayCount = nCntScene;
				spike[nArrayCount].pSpike = pSpike;
				spike[0].pSpike->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
			}
			else
			{
				pSpike->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
			}

			spike[nArrayCount].pSpike->SetCol(D3DCOLOR_RGBA(255, 0, 0, 255));

			// ���̃V�[���ɂ���
			pObj = pNextObj;
		}
		else
		{
			break;
		}
	}

	return spike[nArrayCount].pos;
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
			m_pos.z = pos.z;
			m_circle.fAngle = 0.0f;
		}
	}
	else if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT)
	{
		if (fabsf(pos.z - m_pos.z) <= HOOK_STOP_SIZE &&
			fabsf(pos.y - m_pos.y) <= HOOK_STOP_SIZE)
		{
			m_bHook = false;
			m_pos.x = pos.x;
			m_circle.fAngle = 0.0f;
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
