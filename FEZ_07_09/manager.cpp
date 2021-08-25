//=============================================================================
//
// �I�u�W�F�N�g�Ǘ����� [manager.cpp]
// Author : ��{ ��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "input.h"
#include "Keyboard.h"
#include "camera.h"
#include "light.h"

#include "testObj.h"
#include "player.h"
#include "collisiondetection.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInput = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CCollisionDetection *CManager::m_CollisionDetection = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�C���X�^���X�����E����������
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	m_pInput = new CInputKeyboard;
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{
		return -1;
	}

	// ���C�g�̐���
	//m_pLight = new CLight;
	//if (FAILED(m_pLight->Init()))
	//{
	//	return E_FAIL;
	//}

	m_pCamera = CCamera::Create();

	// �e�N�X�`���̓ǂݍ���
	Load();

	//CTestObj::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CTestObj::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f));
	//CTestObj::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f));

	CCollisionDetection::Create(D3DXVECTOR3(0.0f, 0.0f, CCamera::ORIENTATION_FRONT_POS), D3DXVECTOR3(70.0f, 70.0f, 0.0f), CCollisionDetection::BLOCKTYPE_NONE);
	CCollisionDetection::Create(D3DXVECTOR3(0.0f, 0.0f, CCamera::ORIENTATION_BACK_POS), D3DXVECTOR3(70.0f, 70.0f, 0.0f), CCollisionDetection::BLOCKTYPE_NONE);
	CCollisionDetection::Create(D3DXVECTOR3(CCamera::ORIENTATION_LEFT_POS, 0.0f, -30.0f), D3DXVECTOR3(0.0f, 70.0f, 70.0f), CCollisionDetection::BLOCKTYPE_NONE);
	CCollisionDetection::Create(D3DXVECTOR3(CCamera::ORIENTATION_RIGHT, 0.0f, 30.0f), D3DXVECTOR3(0.0f, 70.0f, 70.0f), CCollisionDetection::BLOCKTYPE_NONE);

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f));

	return 0;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// �I������
	CObject::ReleaseAll();

	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		//�������j��
		delete m_pInput;
		m_pInput = NULL;
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		//�������j��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// �e�N�X�`���̔j��
	Unload();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �X�V����
	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// ���f���E�e�N�X�`���ǂݍ��ݏ���
//=============================================================================
void CManager::Load(void)
{
	CTestObj::Load();
}

//=============================================================================
// ���f���E�e�N�X�`���j������
//=============================================================================
void CManager::Unload(void)
{
	CTestObj::Unload();
}
