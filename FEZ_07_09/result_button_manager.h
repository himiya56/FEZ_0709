//=============================================================================
//
// リザルトボタンマネージャー [result_button_manager.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _RESULT_BUTTON_MANAGER_H_
#define _RESULT_BUTTON_MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CButton;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CResultButtonManager : public CObject
{
public:
	CResultButtonManager(OBJ_TYPE ObjectType = OBJ_TYPE_BUTTON);
	~CResultButtonManager();
	static CResultButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_STAGE_SELECT,
		BUTTON_BACK_TO_TITLE,
		BUTTON_MAX
	}BUTTON;
	void Input(void);
	void Select(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	//ボタンのポインタ
	int m_nButton;						//ボタン
	int m_nInputCount;					//入力間隔
};
#endif