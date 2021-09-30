//===============================================
//
// �u���b�N���� (block.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "stage.h"
#include "manager.h"
#include "renderer.h"

//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CStage::m_pMesh = NULL;
LPD3DXBUFFER CStage::m_pBuffMat = NULL;
DWORD CStage::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CStage::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStage::CStage()
{
	m_rot = DEFAULT_VECTOR;
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CStage::~CStage()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CStage::Init(void)
{
	CScene3D::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);
	//SetScale(D3DXVECTOR3(0.99f, 0.99f, 0.99f));

	m_rot = DEFAULT_VECTOR;

	return S_OK;
}

//=============================================================================
// �I������
// Author : ��{��
//=============================================================================
void CStage::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CStage::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CStage::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CStage::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/Stage1.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block3_1.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CStage::Unload(void)
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
CStage *CStage::Create(D3DXVECTOR3 pos)
{
	CStage *pBlock = NULL;
	pBlock = new CStage;
	pBlock->Init();
	pBlock->SetPos(pos);
	return pBlock;
}
