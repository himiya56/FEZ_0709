//=============================================================================
//
// �J�������� [camera.h]
// Author : ��{��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INIT_OFFSET			1000.0f	// �����_����̋���
#define CAMERA_FIT_ANGLE D3DXToRadian(-90)
#define CAMERA_ROTATE_FRAME_LENGTH 90 // �J������90�x��]������܂ł̃t���[����
#define CAMERA_ROTATE_ANGLE 90 // ���̉�]�ŉ񂷊p�x

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CInputKeyboard;

//================================================
// ���C�g�N���X�錾
//================================================
class CCamera :public CObject
{
public:
	typedef enum
	{
		ROTATE_NONE = 0,
		ROTATE_LEFT,
		ROTATE_RIGHT,
	}ROTATE;

	typedef enum
	{
		ORIENTATION_NONE = -1,
		ORIENTATION_BACK,
		ORIENTATION_LEFT,
		ORIENTATION_FRONT,
		ORIENTATION_RIGHT,
		ORIENTATION_MAX,
	}ORIENTATION;

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCamera(void);
	void RotateCamera(ROTATE dir);
	void OrientationControl(ROTATE dir);

	void SetTargetPos(D3DXVECTOR3 pos) { m_posR = pos; }	// �����_�ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_posV = pos; }			// ���W�ݒ�
	void SetFOV(float fFOV) { m_fFOV = fFOV; }				// ����p�ݒ�
	void DecisionRotate(CInputKeyboard *pInputKeyboard);

	static CCamera *Create(void);

	ROTATE GetRotake(void) { return m_rotDir; }
	ROTATE GetRotakeOld(void) { return m_rotDirOld; }
	ORIENTATION GetOrientation(void) { return m_Orientation; }

	D3DXVECTOR3 GetTargtPos(void) { return m_posR; }		// �����_�擾
	D3DXVECTOR3 GetPos(void) { return m_posV; }				// ���W�擾

private:
	D3DXVECTOR3 m_posV;
	D3DXVECTOR3 m_posR;
	D3DXVECTOR3 m_vecU;
	D3DXVECTOR3 m_posVDest;								// ���W�ڕW�l
	D3DXVECTOR3 m_posRDest;
	D3DXVECTOR3 m_FollowPos;

	D3DXMATRIX  m_mtxProjection;
	D3DXMATRIX  m_mtxView;

	ROTATE      m_rotDir;
	ROTATE      m_rotDirOld;

	ORIENTATION m_Orientation;

	int			m_nRotateCountFrame;
	int         m_nOrientation;

	float		m_fFOV;
	float		m_fOffset;								// �����_����̋���
	float		m_fVerticalAngle;						// ���ʍ��W�J�����c��]
	float		m_fHorizontalAngle;
};

#endif