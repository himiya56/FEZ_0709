//=============================================================================
//
// �`���[�g���A����ʂ̔w�i [bg_tutorial.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BG_TUTORIAL_H_
#define _BG_TUTORIAL_H_

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
class CTutorialBG :public CPolygon2D
{
public:
	CTutorialBG();
	~CTutorialBG();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CTutorialBG * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		TEXTURE_NONE = -1,
		TEXTURE_KEYBOARD_GUID,	//�L�[�{�[�h�̑������
		TEXTURE_JOYSTICK_GUID,	//�W���C�X�e�B�b�N�̑������
		TEXTURE_MAX
	}TEXTURE;
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];	//�e�N�X�`���̃|�C���^
};
#endif