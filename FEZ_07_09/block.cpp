//===============================================
//
// �u���b�N���� (block.cpp)
// Author : ��{��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "block.h"
#include "manager.h"
#include "renderer.h"

//========================
// �ÓI�����o�ϐ��錾
//========================
LPD3DXMESH	CBlock::m_pMesh = NULL;
LPD3DXBUFFER CBlock::m_pBuffMat = NULL;
DWORD CBlock::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBlock::CBlock()
{
	m_rot = DEFAULT_VECTOR;
}

//=============================================================================
// �f�X�g���N�^
// Author : ��{��
//=============================================================================
CBlock::~CBlock()
{
}

//=============================================================================
// ����������
// Author : ��{��
//=============================================================================
HRESULT CBlock::Init(void)
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
void CBlock::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
// Author : ��{��
//=============================================================================
void CBlock::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// �`�揈��
// Author : ��{��
//=============================================================================
void CBlock::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�ǂݍ��ݏ���
// Author : ��{��
//=============================================================================
HRESULT CBlock::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/block1_1.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block1_1.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���E���f���f�[�^�j������
// Author : ��{��
//=============================================================================
void CBlock::Unload(void)
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
CBlock *CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock *pBlock = NULL;
	pBlock = new CBlock;
	pBlock->Init();
	pBlock->SetPos(pos);
	return pBlock;
}
