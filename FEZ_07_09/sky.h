//====================================================================
//
// �X�p�C�N(�t�b�N�n�_)���� (spike.h)
// Author : ��{ ��
//
//====================================================================
#ifndef _SKY_H_
#define _SKY_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "polygon3d.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SKY_SIZE D3DXVECTOR3(75.0f * 27.0f, 75.0f * 30.0f, 0.0f)

//================================================
// �N���X�錾
//================================================

// �r���{�[�h�N���X
class CSky : public CPolygon3D
{
public:
	CSky();
	~CSky();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Load(void);
	static void Unload(void);
	static CSky *Create(D3DXVECTOR3 pos, D3DXVECTOR2 texUv);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	static LPDIRECT3DTEXTURE9		m_pTexture;
};

#endif