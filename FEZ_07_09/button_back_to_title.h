//=============================================================================
//
// �^�C�g���ɖ߂�{�^�� [button_back_to_title.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BUTTON_BACK_TO_TITLE_H_
#define _BUTTON_BACK_TO_TITLE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBackToTitleButton :public CButton
{
public:
	CBackToTitleButton();
	~CBackToTitleButton();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBackToTitleButton * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Press(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
};
#endif