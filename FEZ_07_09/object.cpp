//=============================================================================
//
// �|���S������ [object.cpp]
// Author : ��{ ��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
int CObject::m_nNumAll = 0;
int CObject::m_nNumObj[CObject::OBJ_TYPE_MAX] = {};

CObject *CObject::m_pTop[CObject::OBJ_TYPE_MAX] = {};
CObject *CObject::m_pCur[CObject::OBJ_TYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject()
{
	// �I�u�W�F�N�g�̎�ނ��w�肪�Ȃ��̂�NONE�ɂ���
	m_type = OBJ_TYPE_NONE;

	// �擪���Ȃ��Ȃ�A�擪��
	if (m_pTop[m_type] == NULL)
	{
		m_pTop[m_type] = this;
	}

	// ���݂ɂ�����ŐV�̃I�u�W�F�N�g���Ȃ��Ȃ�A�ŐV��
	if (m_pCur[m_type] == NULL)
	{
		m_pCur[m_type] = this;
	}

	// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���A�����ɂ���
	m_pCur[m_type]->m_pNext = this;

	// ���݂̃I�u�W�F�N�g�������̏ꍇ
	if (m_pCur[m_type] == this)
	{
		// �����̑O�̃I�u�W�F�N�g���ANULL�ɂ���
		m_pPrev = NULL;
	}
	else
	{
		// �����̑O�̃I�u�W�F�N�g���A���݂̃I�u�W�F�N�g�ɂ���
		m_pPrev = m_pCur[m_type];
	}

	// ���݂̃I�u�W�F�N�g���A�����ɂ���
	m_pCur[m_type] = this;

	// �����̎��̃I�u�W�F�N�g���ANULL�ɂ���
	m_pNext = NULL;

	// �������I�u�W�F�N�g���J�E���g
	m_nNumObj[m_type]++;

	// �S�̂̐����C���N�������g
	m_nNumAll++;

	// �g�p����t���O��true��
	m_bUse = true;
}

//=============================================================================
// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
//=============================================================================
CObject::CObject(OBJ_TYPE objType)
{
	// �I�u�W�F�N�g�̎�ނ��w��
	m_type = objType;

	// �擪���Ȃ��Ȃ�A�擪��
	if (m_pTop[m_type] == NULL)
	{
		m_pTop[m_type] = this;
	}

	// ���݂ɂ�����ŐV�̃I�u�W�F�N�g���Ȃ��Ȃ�A�ŐV��
	if (m_pCur[m_type] == NULL)
	{
		m_pCur[m_type] = this;
	}

	// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���A�����ɂ���
	m_pCur[m_type]->m_pNext = this;

	// ���݂̃I�u�W�F�N�g�������̏ꍇ
	if (m_pCur[m_type] == this)
	{
		// �����̑O�̃I�u�W�F�N�g���ANULL�ɂ���
		m_pPrev = NULL;
	}
	else
	{
		// �����̑O�̃I�u�W�F�N�g���A���݂̃I�u�W�F�N�g�ɂ���
		m_pPrev = m_pCur[m_type];
	}

	// ���݂̃I�u�W�F�N�g���A�����ɂ���
	m_pCur[m_type] = this;

	// �����̎��̃I�u�W�F�N�g���ANULL�ɂ���
	m_pNext = NULL;

	// �������I�u�W�F�N�g���J�E���g
	m_nNumObj[m_type]++;

	// �S�̂̐����C���N�������g
	m_nNumAll++;

	// �g�p����t���O��true��
	m_bUse = true;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// �S�X�V����
//=============================================================================
void CObject::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < OBJ_TYPE_MAX; nCnt++)
	{
		// �擪�A�ŐV�̂��̂�����Ȃ�
		if (m_pTop[nCnt] != NULL && m_pCur[nCnt] != NULL)
		{
			// �L���p�̕ϐ�
			CObject*pObj = m_pTop[nCnt];

			do
			{
				// �L���p�̕ϐ�(Update���ɁAUninit����邱�Ƃ��l��)
				CObject*pNextScene = pObj->m_pNext;

				// �X�V����
				pObj->Update();

				// �g�p�t���O��false�Ȃ�
				if (pObj->m_bUse == false)
				{
					// �������̊J��
					delete pObj;
					pObj = NULL;
				}

				// ���̃V�[���ɕς��Ă���
				pObj = pNextScene;

			} while (pObj != NULL);
		}
	}
}

//=============================================================================
// �S�`�揈��
//=============================================================================
void CObject::DrawAll(void)
{
	for (int nCnt = 0; nCnt < OBJ_TYPE_MAX; nCnt++)
	{
		// �擪�A�ŐV�̂��̂�����Ȃ�
		if (m_pTop[nCnt] != NULL && m_pCur[nCnt] != NULL)
		{
			// �L���p�̕ϐ�
			CObject*pObj = m_pTop[nCnt];

			do
			{
				// �`�揈��
				pObj->Draw();

				// ���̃V�[���ɕς��Ă���
				pObj = pObj->m_pNext;

			} while (pObj != NULL);
		}
	}

	// �f�o�b�O�p
	int nDebug = m_nNumAll;
	nDebug = nDebug;
}

//=============================================================================
// �S�I�u�W�F�N�g�j������
//=============================================================================
void CObject::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < OBJ_TYPE_MAX; nCnt++)
	{
		// �擪�A�ŐV�̂��̂�����Ȃ�
		if (m_pTop[nCnt] != NULL && m_pCur[nCnt] != NULL)
		{
			// �L���p�̕ϐ�
			CObject*pObj = m_pTop[nCnt];

			do
			{
				// �L���p�̕ϐ�
				CObject*pNextScene = pObj->m_pNext;

				// �I������
				pObj->Uninit();

				// �g�p�t���O��false�Ȃ�
				if (pObj->m_bUse == false)
				{
					// �������̊J��
					delete pObj;
					pObj = NULL;
				}

				// ���̃V�[���ɕς��Ă���
				pObj = pNextScene;

			} while (pObj != NULL);
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�j������
//=============================================================================
void CObject::Release(void)
{
	// ���g������Ȃ�A
	if (this != NULL)
	{
		// �擪�Ȃ�
		if (this == m_pTop[m_type])
		{
			// ���̒��g������Ȃ�
			if (m_pNext != NULL)
			{
				// ���̂��̂̑O�̏����ANULL��
				m_pNext->m_pPrev = NULL;

				// �����擪��
				m_pTop[m_type] = m_pNext;
			}
			else
			{
				// �擪�̎����Ȃ��Ȃ�A�擪�ƌ��݂������|�C���^��NULL��
				m_pTop[m_type] = NULL;
				m_pCur[m_type] = NULL;
			}
		}
		// �擪�łȂ��Ȃ�
		else
		{
			// ���̒��g������Ȃ�
			if (m_pNext != NULL)
			{
				// �O�̂��̂̎��̏����A���g�̎��̏���
				m_pPrev->m_pNext = m_pNext;

				// ���̂��̂̑O�̏����A���g�̑O�̏���
				m_pNext->m_pPrev = m_pPrev;
			}
			else
			{
				// �O�̂��̂̎��̏����A�Ȃ���
				m_pPrev->m_pNext = NULL;

				// ���݂̍ŐV�̂��̂��A�O�̏���
				m_pCur[m_type] = m_pPrev;
			}
		}

		// �g�p�t���O��false��
		m_bUse = false;

		// ��ނ��Ƃ̑��������炷
		m_nNumObj[m_type]--;

		// �S�̂̐����f�N�������g
		m_nNumAll--;
	}
}