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
CCollisionDetection *CCollisionDetection::m_CollisionDetectionOrientationTop;
CCollisionDetection *CCollisionDetection::m_CollisionDetectionOrientationCur;

CCollisionDetection::CCollisionDetection() {
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
	m_pCamera = CManager::GetCamera();

	// �擪�A�ŐV�̂��̂�����Ȃ�
	if (m_CollisionDetectionListTop != NULL && m_CollisionDetectionListCur != NULL)
	{
		// �L���p�̕ϐ�
		CCollisionDetection *pCollisionDetection = m_CollisionDetectionListTop;

		do
		{
			// �L���p�̕ϐ�(Update���ɁAUninit����邱�Ƃ��l��)
			CCollisionDetection *pNextCollisionDetection = pCollisionDetection->m_pNext;

			if (m_pCamera->GetOrientation() != CCamera::ROTATE_NONE) {
				ReleaseAll();
			}

			if (pCollisionDetection->m_Orientation == m_pCamera->GetOrientation()) {
				SetCollisionDetectionOrientation(pCollisionDetection->m_pos, pCollisionDetection->m_siz);
			}

			// �g�p�t���O��false�Ȃ�
			if (pCollisionDetection->m_bUse == false)
			{
				// �������̊J��
				//delete pScene;
				pCollisionDetection = NULL;
			}

			// ���̃V�[���ɕς��Ă���
			pCollisionDetection = pNextCollisionDetection;

		} while (pCollisionDetection != NULL);
	}
}

void CCollisionDetection::Draw(void) {
	CPolygon2D::Draw();
}

CCollisionDetection *CCollisionDetection::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz, CCamera::ORIENTATION Orientation) {
	CCollisionDetection *pCollisionDetection = NULL;
	pCollisionDetection = new CCollisionDetection;
	pCollisionDetection->Init();
	pCollisionDetection->SetPos(pos);
	pCollisionDetection->SetSize(siz.y, siz.x);
	pCollisionDetection->SetCollisionDetectionList(pos, siz, Orientation);
	return pCollisionDetection;
}

void CCollisionDetection::SetCollisionDetectionList(D3DXVECTOR3 pos, D3DXVECTOR3 siz, CCamera::ORIENTATION Orientation) {
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

	// ������NONE�ɂ���
	m_Orientation = Orientation;

	// �g�p����t���O��true��
	m_bUse = true;
}

void CCollisionDetection::SetCollisionDetectionOrientation(D3DXVECTOR3 pos, D3DXVECTOR3 siz) {
	// �擪���Ȃ��Ȃ�A�擪��
	if (m_CollisionDetectionOrientationTop == NULL)
	{
		m_CollisionDetectionOrientationTop = this;
	}

	// ���݂ɂ�����ŐV�̃I�u�W�F�N�g���Ȃ��Ȃ�A�ŐV��
	if (m_CollisionDetectionOrientationCur == NULL)
	{
		m_CollisionDetectionOrientationCur = this;
	}

	// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���A�����ɂ���
	m_CollisionDetectionOrientationCur->m_pNext = this;

	// ���݂̃I�u�W�F�N�g�������̏ꍇ
	if (m_CollisionDetectionOrientationCur == this)
	{
		// �����̑O�̃I�u�W�F�N�g���ANULL�ɂ���
		m_pPrev = NULL;
	}
	else
	{
		// �����̑O�̃I�u�W�F�N�g���A���݂̃I�u�W�F�N�g�ɂ���
		m_pPrev = m_CollisionDetectionOrientationCur;
	}

	// ���݂̃I�u�W�F�N�g���A�����ɂ���
	m_CollisionDetectionOrientationCur = this;

	// �����̎��̃I�u�W�F�N�g���ANULL�ɂ���
	m_pNext = NULL;

	// �g�p����t���O��true��
	m_bUse = true;
}

void CCollisionDetection::ReleaseAll(void)
{
	// �擪�A�ŐV�̂��̂�����Ȃ�
	if (m_CollisionDetectionOrientationTop != NULL && m_CollisionDetectionOrientationCur != NULL)
	{
		// �L���p�̕ϐ�
		CCollisionDetection *pCollisionDetection = m_CollisionDetectionOrientationTop;

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