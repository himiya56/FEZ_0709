//=============================================================================
//
// チュートリアルボタン [button_tutorial.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BUTTON_TUTORIAL_H_
#define _BUTTON_TUTORIAL_H_

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
class CTutorialButton :public CButton
{
public:
	CTutorialButton();
	~CTutorialButton();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CTutorialButton * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Press(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};
#endif