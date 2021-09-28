//=============================================================================
//
// ステージ選択ボタン [button_stage_select.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BUTTON_STAGE_SELECT_H_
#define _BUTTON_STAGE_SELECT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CStageSelectButton :public CButton
{
public:
	CStageSelectButton();
	~CStageSelectButton();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CStageSelectButton * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Press(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};
#endif