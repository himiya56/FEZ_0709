//====================================================================
//
// �X�p�C�N(�t�b�N�n�_)���� (spike.h)
// Author : ��{ ��
//
//====================================================================
#ifndef _SPIKE_H_
#define _SPIKE_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "billboard.h"
#include "camera.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SPIKE_SIZE D3DXVECTOR3(50.0f,50.0f,0.0f)

//================================================
// �N���X�錾
//================================================

// �r���{�[�h�N���X
class CSpike : public CBillboard
{
public:
	CSpike();
	~CSpike();

	typedef enum
	{
		SPIKE_NONE = 0,
		SPIKE_LOCK,
		SPIKE_SHOOT,
	}SPIKE_STATE;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Load(void);
	static void Unload(void);
	static CSpike *Create(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	static LPDIRECT3DTEXTURE9		m_pTexture;
	SPIKE_STATE state;
};

#endif