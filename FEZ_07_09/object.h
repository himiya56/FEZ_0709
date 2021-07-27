//=============================================================================
//
// �|���S������ [object.h]
// Author : ��{ ��
//
//=============================================================================

// ��d�C���N���[�h�h�~�p
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �I�u�W�F�N�g�N���X��`
//*****************************************************************************
class CObject
{
public:
	// �񋓌^�錾
	typedef enum
	{
		OBJ_TYPE_NONE = 0,
		OBJ_TYPE_HOOK,
		OBJ_TYPE_BUTTON,
		OBJ_TYPE_SPIKE,
		OBJ_TYPE_MAX
	}OBJ_TYPE;

	// �����o�֐�
	CObject();
	CObject(OBJ_TYPE objType);
	virtual ~CObject();
	// �������z�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static  void UpdateAll(void);
	static  void DrawAll(void);
	static  void ReleaseAll(void);	// �S�I�u�W�F�N�g�j���֐�

	static  int GetNumObj(OBJ_TYPE objType) {return m_nNumObj[objType]; }
	static  CObject*GetTopObj(OBJ_TYPE objType) { return m_pTop[objType]; }
	CObject* GetNextObj(void) { return m_pNext; }
protected:
	void Release(void);		// �I�u�W�F�N�g�j���֐�
private:
	static CObject *m_pTop[OBJ_TYPE_MAX];
	static CObject *m_pCur[OBJ_TYPE_MAX];
	CObject *m_pPrev;
	CObject *m_pNext;

	static int m_nNumAll;
	static int m_nNumObj[OBJ_TYPE_MAX];
	OBJ_TYPE	m_type;

	bool m_bUse;
};

#endif

