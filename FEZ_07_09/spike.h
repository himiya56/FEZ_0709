//====================================================================
//
// スパイク(フック地点)処理 (spike.h)
// Author : 樋宮 匠
//
//====================================================================
#ifndef _SPIKE_H_
#define _SPIKE_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "billboard.h"
#include "camera.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SPIKE_SIZE D3DXVECTOR3(50.0f,50.0f,0.0f)

//================================================
// クラス宣言
//================================================

// ビルボードクラス
class CSpike : public CBillboard
{
public:
	CSpike();
	~CSpike();

	typedef enum
	{
		SPIKE_NONE = 0,
		SPIKE_LOCK,
		SPIKE_SHOOT,
	}SPIKE_STATE;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Load(void);
	static void Unload(void);
	static CSpike *Create(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	static LPDIRECT3DTEXTURE9		m_pTexture;
	SPIKE_STATE state;
};

#endif