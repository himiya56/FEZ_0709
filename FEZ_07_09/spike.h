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
#define SPIKE_SIZE D3DXVECTOR3(75.0f,75.0f,0.0f)

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
		SPIKE_MAX,
	}SPIKE_STATE;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(SPIKE_STATE state) { BindTexture(m_apTexture[state]); }
	static void Load(void);
	static void Unload(void);
	static CSpike *Create(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	static LPDIRECT3DTEXTURE9		m_apTexture[SPIKE_MAX];
	SPIKE_STATE state;
};

#endif