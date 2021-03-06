//=============================================================================
//
// ボタン [button.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BUTTON_H_
#define _BUTTON_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "polygon2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CButton :public CPolygon2D
{
public:
	CButton(OBJ_TYPE ObjectType = OBJ_TYPE_BUTTON);
	~CButton();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void NotSelectColor(void);
	void SelectColor(void);
	void SelectSound(void);
	virtual void Press(void) = 0;
private:
};
#endif