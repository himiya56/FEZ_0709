//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : �����D�I
//
//=============================================================================

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "billboard.h"

//=============================================================================
// �N���X�錾
//=============================================================================
class CParticle : public CBillboard
{
public:
	// �e�N�X�`���[�^�C�v
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_1,
		TEX_TYPE_MAX
	}TEX_TYPE;

	CParticle();
	~CParticle();

	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE TexType);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_TYPE_MAX];	// �e�N�X�`�����̃|�C���^
	TEX_TYPE m_TexType;										// �e�N�X�`���^�C�v

};

#endif