//=============================================================================
//
// ���U���g�{�^���}�l�[�W���[ [result_button_manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _RESULT_BUTTON_MANAGER_H_
#define _RESULT_BUTTON_MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"
#include "button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CButton;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResultButtonManager : public CObject
{
public:
	CResultButtonManager(OBJ_TYPE ObjectType = OBJ_TYPE_BUTTON);
	~CResultButtonManager();
	static CResultButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_STAGE_SELECT,
		BUTTON_BACK_TO_TITLE,
		BUTTON_MAX
	}BUTTON;
	void Input(void);
	void Select(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	//�{�^���̃|�C���^
	int m_nButton;						//�{�^��
	int m_nInputCount;					//���͊Ԋu
};
#endif