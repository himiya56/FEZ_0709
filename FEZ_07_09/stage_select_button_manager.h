//=============================================================================
//
// �X�e�[�W�I���{�^���}�l�[�W���[ [stage_select_button_manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _STAGE_SELECT_BUTTON_MANAGER_H_
#define _STAGE_SELECT_BUTTON_MANAGER_H_

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
class CStageSelectButtonManager : public CObject
{
public:
	CStageSelectButtonManager(OBJ_TYPE ObjectType = OBJ_TYPE_BUTTON);
	~CStageSelectButtonManager();
	static CStageSelectButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_STAGE1,
		BUTTON_STAGE2,
		BUTTON_STAGE3,
		BUTTON_MAX
	}BUTTON;
	void Input(void);
	void Select(void);
	void CancelSound(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	//�{�^���̃|�C���^
	int m_nButton;						//�{�^��
	int m_nInputCount;					//���͊Ԋu
};
#endif