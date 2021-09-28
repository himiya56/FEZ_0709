//=============================================================================
//
// ジョイスティック処理 [joystick.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define JS_X	   (0)
#define JS_Y	   (1)
#define JS_A	   (2)
#define JS_B	   (3)
#define JS_LB	   (4)
#define JS_RB	   (5)
#define JS_LT	   (6)
#define JS_RT	   (7)
#define JS_LP	   (8)
#define JS_RP	   (9)
#define JS_BACK	   (10)
#define JS_START   (11)
#define JS_HOME    (12)
#define	NUM_JS_MAX (256)
#define MAX_JOYSTICK (2)
#define JOYSTICK_1P (1)
#define JOYSTICK_2P (2)

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CJoystick : public CInput
{
public:
	CJoystick();
	~CJoystick();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetJoystickPress(int nKey,int nJoystick);
	bool GetJoystickTrigger(int nKey, int nJoystick);
	bool GetJoystickRelease(int nKey, int nJoystick);
	BOOL CreateEffect(HWND);
	static BOOL CALLBACK EnumFFDevicesCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
	static LPDIRECTINPUTDEVICE8 GetDevice(int nJoystick) { return m_pJDevice[nJoystick]; }
	static LPDIRECTINPUTEFFECT GetEffect(int nJoystick) { return m_IpDIEffect[nJoystick]; }
private:
	static LPDIRECTINPUTDEVICE8 m_pJDevice[MAX_JOYSTICK];	// デバイス
	static LPDIRECTINPUTEFFECT m_IpDIEffect[MAX_JOYSTICK];	// エフェクト
	DIDEVCAPS	m_diDevCaps;								// Caps
	DWORD m_dwNumForceFeedbackAxis;							// フォースフィードバック
	DWORD m_rgdwAxes[2] = { DIJOFS_X , DIJOFS_Y };
	LONG  m_rglDirection[2] = { 1 , 1 };
	DICONSTANTFORCE cf;
	DIEFFECT        eff;
	BYTE m_aJoyState[NUM_JS_MAX][MAX_JOYSTICK];				// ジョイスティックの入力情報ワーク
	BYTE m_aJoyStateTrigger[NUM_JS_MAX][MAX_JOYSTICK];		// ジョイスティックトリガー情報
	BYTE m_aJoyStateRelease[NUM_JS_MAX][MAX_JOYSTICK];		// ジョイスティックリリース情報
};
#endif