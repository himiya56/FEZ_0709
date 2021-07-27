//====================================================================
//
// ワイヤー（フック）処理 (wire.h)
// Author : 樋宮 匠
//
//====================================================================
#ifndef _WIRE_H_
#define _WIRE_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "polygon3d.h"
#include "camera.h"
#include "manager.h"
#include "player_hook.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//================================================
// クラス宣言
//================================================

// ビルボードクラス
class CWire : public CBillboard
{
public:
	CWire();
	~CWire();

	typedef enum
	{
		WIRE_NONE = 0,
		WIRE_SHOOT,
		WIRE_WINDING,
	}WIRE_STATE;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Load(void);
	static void Unload(void);
	static CWire *Create(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	static LPDIRECT3DTEXTURE9		m_pTexture;
	WIRE_STATE wire;
	bool m_bShoot;
};

#endif