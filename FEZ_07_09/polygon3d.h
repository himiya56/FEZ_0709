//====================================================================
//
// �V�[�����3D�|���S������ (scene2d.h)
// Author : ��{��
//
//====================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DIR_RIGHT 0
#define DIR_LEFT 1

//================================================
// �N���X�錾
//================================================

// 3D�|���S���N���X
class CPolygon3D : public CObject
{
public:
	CPolygon3D();
	virtual ~CPolygon3D();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void BindTexture(const LPDIRECT3DTEXTURE9 pTex) { m_pTexture = pTex; }// �e�N�X�`�����蓖��
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }		// ���W�ݒ�p
	void SetCol(const D3DXCOLOR col) { m_col = col; };
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetScale(const D3DXVECTOR3 scale) { m_scale = scale; }
	void SetSize(const float sizey, const float sizex) { m_fSizeX = sizex; m_fSizeY = sizey; }
	void SetDir(const int dir) { m_nDir = dir; }
	void SetTexUV(const float leftX, const float rightX, const float topY, const float bottomY);
	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	void GetTexUV(float* leftX, float* rightX, float* topY, float* bottomY);
private:
	LPDIRECT3DTEXTURE9		m_pTexture;
	D3DXMATRIX			    m_mtxWorld;		// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;
	D3DXVECTOR3				m_pos;			// ���W
	D3DXVECTOR3				m_rot;			// ��]
	D3DXVECTOR3				m_scale;
	D3DXCOLOR				m_col;
	int						m_nDir;
	float					m_fSizeX;
	float					m_fSizeY;
	float					m_TexLeftX;
	float					m_TexRightX;
	float					m_TexTopY;
	float					m_TexBottomY;
};

#endif