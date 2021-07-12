//=============================================================================
//
// �^�C�g���{�^���}�l�[�W���[ [title_button_manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _START_BUTTON_MANAGER_H_
#define _START_BUTTON_MANAGER_H_

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
class CTitleButtonManager : public CObject
{
public:
	CTitleButtonManager(OBJ_TYPE ObjectType = OBJ_TYPE_BUTTON);
	~CTitleButtonManager();
	static CTitleButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_START,
		BUTTON_TUTORIAL,
		BUTTON_EXIT,
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