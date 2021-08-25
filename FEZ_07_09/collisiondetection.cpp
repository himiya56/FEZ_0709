//========================
// �C���N���[�h�t�@�C��
//========================
#include "collisiondetection.h"
#include "manager.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
int CCollisionDetection::m_nNum = 0;
CCollisionDetection *CCollisionDetection::m_CollisionDetectionListTop;
CCollisionDetection *CCollisionDetection::m_CollisionDetectionListCur;

CCollisionDetection::CCollisionDetection() {
	// �擪���Ȃ��Ȃ�A�擪��
	if (m_CollisionDetectionListTop == NULL)
	{
		m_CollisionDetectionListTop = this;
	}

	// ���݂ɂ�����ŐV�̃I�u�W�F�N�g���Ȃ��Ȃ�A�ŐV��
	if (m_CollisionDetectionListCur == NULL)
	{
		m_CollisionDetectionListCur = this;
	}

	// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���A�����ɂ���
	m_CollisionDetectionListCur->m_pNext = this;

	// ���݂̃I�u�W�F�N�g�������̏ꍇ
	if (m_CollisionDetectionListCur == this)
	{
		// �����̑O�̃I�u�W�F�N�g���ANULL�ɂ���
		m_pPrev = NULL;
	}
	else
	{
		// �����̑O�̃I�u�W�F�N�g���A���݂̃I�u�W�F�N�g�ɂ���
		m_pPrev = m_CollisionDetectionListCur;
	}

	// ���݂̃I�u�W�F�N�g���A�����ɂ���
	m_CollisionDetectionListCur = this;

	// �����̎��̃I�u�W�F�N�g���ANULL�ɂ���
	m_pNext = NULL;

	// �g�p����t���O��true��
	m_bUse = true;

	// �������I�u�W�F�N�g���J�E���g
	m_nNum++;
}

CCollisionDetection::~CCollisionDetection() {

}

HRESULT CCollisionDetection::Init(void) {
	CPolygon2D::Init();

	return S_OK;
}

void CCollisionDetection::Uninit(void) {
	CPolygon2D::Uninit();
}

void CCollisionDetection::Update(void) {
	// �擪�A�ŐV�̂��̂�����Ȃ�
	if (m_CollisionDetectionListTop != NULL && m_CollisionDetectionListCur != NULL)
	{
		// �L���p�̕ϐ�
		CCollisionDetection *pCollisionDetection = m_CollisionDetectionListTop;

		do
		{
			// �L���p�̕ϐ�(Update���ɁAUninit����邱�Ƃ��l��)
			CCollisionDetection *pNextCollisionDetection = pCollisionDetection->m_pNext;

			// �g�p�t���O��false�Ȃ�
			if (pCollisionDetection->m_bUse == false)
			{
				// �������̊J��
				//delete pScene;
				pCollisionDetection = NULL;
			}

			UpdateByType(pCollisionDetection->m_BlockType);
			// ���̃V�[���ɕς��Ă���
			pCollisionDetection = pNextCollisionDetection;

		} while (pCollisionDetection != NULL);
	}
}

void CCollisionDetection::UpdateByType(BLOCKTYPE BlockType) {
	switch (BlockType) {
	case BLOCKTYPE_HOOK:
		break;

	case BLOCKTYPE_BUTTON:
		break;

	case BLOCKTYPE_BUTTON_INCLUDED:
		break;
	}
}

void CCollisionDetection::Draw(void) {
	CPolygon2D::Draw();
}

CCollisionDetection *CCollisionDetection::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz, BLOCKTYPE BlockType) {
	CCollisionDetection* pCollisionDetection = NULL;
	pCollisionDetection = new CCollisionDetection;
	pCollisionDetection->Init();
	pCollisionDetection->SetPos(pos);
	pCollisionDetection->SetSize(siz.y, siz.x);
	pCollisionDetection->m_pos = pos;
	pCollisionDetection->m_siz = siz;
	pCollisionDetection->m_BlockType = BlockType;
	return pCollisionDetection;
}

void CCollisionDetection::ReleaseAll(void)
{
	// �擪�A�ŐV�̂��̂�����Ȃ�
	if (m_CollisionDetectionListTop != NULL && m_CollisionDetectionListCur != NULL)
	{
		// �L���p�̕ϐ�
		CCollisionDetection *pCollisionDetection = m_CollisionDetectionListCur;

		do
		{
			// �L���p�̕ϐ�
			CCollisionDetection *pNextpCollisionDetection = pCollisionDetection->m_pNext;

			// �I������
			pCollisionDetection->Uninit();

			// �g�p�t���O��false�Ȃ�
			if (pCollisionDetection->m_bUse == false)
			{
				// �������̊J��
				//delete pScene;
				pCollisionDetection = NULL;
			}

			// ���̃V�[���ɕς��Ă���
			pCollisionDetection = pNextpCollisionDetection;

		} while (pCollisionDetection != NULL);
	}
}