#pragma once
//====================================================================
//
// �S�[���̏��� (block.h)
// Author : ��{��
//
//====================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "scene3d.h"

//================================================
// �}�N����`
//================================================
#define HOVER_RANGE 10.0f  // �S�[���I�u�W�F�N�g�̕��V�͈�

//================================================
// �N���X�錾
//================================================

// UI�N���X
class CGoal : public CScene3D
{
public:
	CGoal();
	~CGoal();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CGoal *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_pos;
	D3DXVECTOR3						m_rot;
	float							m_fAngle;
};

#endif