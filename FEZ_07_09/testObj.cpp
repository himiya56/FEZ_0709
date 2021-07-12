//===============================================
//
// �e�X�g�I�u�W�F�N�g���� (testObj.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "testObj.h"
#include "manager.h"
#include "renderer.h"

//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CTestObj::m_pMesh = NULL;
LPD3DXBUFFER CTestObj::m_pBuffMat = NULL;
DWORD CTestObj::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CTestObj::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTestObj::CTestObj()
{
	m_rot = DEFAULT_VECTOR;
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CTestObj::~CTestObj()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CTestObj::Init(void)
{
	CScene3D::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);

	m_rot = DEFAULT_VECTOR;

	return S_OK;
}

//=============================================================================
// �I������
// Author : ��{��
//=============================================================================
void CTestObj::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CTestObj::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CTestObj::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CTestObj::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/demos_Stage.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/color.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CTestObj::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �C���X�^���X��������
// Author : ��{��
//=============================================================================
CTestObj *CTestObj::Create(D3DXVECTOR3 pos)
{
	CTestObj *pCube = NULL;
	pCube = new CTestObj;
	pCube->Init();
	pCube->SetPos(pos);
	return pCube;
}
