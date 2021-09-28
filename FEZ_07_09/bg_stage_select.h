//=============================================================================
//
// ステージ選択画面の背景 [bg_stage_select.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BG_STAGE_SELECT_H_
#define _BG_STAGE_SELECT_H_

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
class CStageSelectBG :public CPolygon2D
{
public:
	CStageSelectBG();
	~CStageSelectBG();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CStageSelectBG * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};
#endif