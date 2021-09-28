//=============================================================================
//
// �{�^�� [button.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BUTTON_H_
#define _BUTTON_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "polygon2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CButton :public CPolygon2D
{
public:
	typedef enum
	{
		BUTTON_SE_NONE = -1,
		BUTTON_SE_SELECT,
		BUTTON_SE_PUSH,
		BUTTON_SE_CANCEL,
		BUTTON_SE_MAX
	}BUTTON_SE;
	CButton(OBJ_TYPE ObjectType = OBJ_TYPE_BUTTON);
	~CButton();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void NotSelectColor(void);
	void SelectColor(void);
	void PlayButtonSE(BUTTON_SE PlayButtonSE);
	virtual void SelectExpansion(void) {};
	virtual void NotSelectShrink(void) {};
	virtual void Press(void) = 0;
private:
};
#endif