#pragma once
//====================================================================
//
// �e�X�g�I�u�W�F�N�g�̏��� (testObj.h)
// Author : ��{��
//
//====================================================================
#ifndef _TESTOBJ_H_
#define _TESTOBJ_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "scene3d.h"

//================================================
// �}�N����`
//================================================

//================================================
// �N���X�錾
//================================================

// UI�N���X
class CTestObj : public CScene3D
{
public:
	CTestObj();
	~CTestObj();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CTestObj *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_rot;
};

#endif