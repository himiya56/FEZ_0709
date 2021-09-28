//=============================================================================
//
// ジョイスティック処理 [joystick.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "input.h"
#include "joystick.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECTINPUTDEVICE8 CJoystick::m_pJDevice[MAX_JOYSTICK] = {};
LPDIRECTINPUTEFFECT CJoystick::m_IpDIEffect[MAX_JOYSTICK] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CJoystick::CJoystick()
{
	memset(m_aJoyState, 0, sizeof(m_aJoyState));
	memset(m_aJoyStateTrigger, 0, sizeof(m_aJoyStateTrigger));
	memset(m_aJoyStateRelease, 0, sizeof(m_aJoyStateRelease));
}

//=============================================================================
// デストラクタ
//=============================================================================
CJoystick::~CJoystick()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CJoystick::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT  hr;

	hr = CInput::Init(hInstance, hWnd);

	hr = m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY);

	if (FAILED(hr)) {
		MessageBox(hWnd, "Can't create Device.", "Error", MB_OK);
		return FALSE;
	}
	// 接続できるジョイスティックの最大数分回す
	for (int nCount = 0; nCount < MAX_JOYSTICK; nCount++)
	{
		if (m_pJDevice[nCount] != NULL)
		{
			hr = m_pJDevice[nCount]->SetDataFormat(&c_dfDIJoystick);
			if (FAILED(hr)) {
				MessageBox(hWnd, "Can't set data format.", "Error", MB_OK);
				return FALSE;
			}

			hr = m_pJDevice[nCount]->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
			if (FAILED(hr)) {
				MessageBox(hWnd, "Can't set cooperative level.", "Error", MB_OK);
				return FALSE;
			}

			m_diDevCaps.dwSize = sizeof(DIDEVCAPS);
			hr = m_pJDevice[nCount]->GetCapabilities(&m_diDevCaps);
			if (FAILED(hr)) {
				MessageBox(hWnd, "Can't create device capabilities.", "Error", MB_OK);
				return FALSE;
			}

			hr = m_pJDevice[nCount]->EnumObjects(EnumAxesCallback, (VOID*)&m_dwNumForceFeedbackAxis, DIDFT_AXIS);
			if (FAILED(hr)) {
				MessageBox(hWnd, "Can't set property.", "Error", MB_OK);
				return FALSE;
			}

			if (m_dwNumForceFeedbackAxis > 2)
			{
				m_dwNumForceFeedbackAxis = 2;
			}

			if (!CreateEffect(hWnd)) {
				MessageBox(hWnd, "Can't create effect.", "Error", MB_OK);
				return FALSE;
			}

			hr = m_pJDevice[nCount]->Poll();
			if (FAILED(hr)) {
				hr = m_pJDevice[nCount]->Acquire();
				while (hr == DIERR_INPUTLOST) {
					hr = m_pJDevice[nCount]->Acquire();
				}
			}
		}
	}
	return TRUE;
}


//=============================================================================
// 終了処理関数
//=============================================================================
void CJoystick::Uninit(void)
{
	CInput::Uninit();
	// 接続できるジョイスティックの最大数分回す
	for (int nJoystick = 0; nJoystick < MAX_JOYSTICK; nJoystick++)
	{
		if (m_pJDevice[nJoystick] != NULL)
		{
			//デバイス制御の停止
			m_pJDevice[nJoystick]->Unacquire();
			m_IpDIEffect[nJoystick]->Release();
			m_pJDevice[nJoystick]->Release();
			m_pJDevice[nJoystick] = NULL;
		}
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CJoystick::Update(void)
{
	int nCntKey;
	DIJOYSTATE js;
	// 接続できるジョイスティックの最大数分回す
	for (int nJoystick = 0; nJoystick < MAX_JOYSTICK; nJoystick++)
	{
		if (m_pJDevice[nJoystick] != NULL)
		{
			m_pJDevice[nJoystick]->Poll();
			m_pJDevice[nJoystick]->GetDeviceState(sizeof(DIJOYSTATE), &js);
			//デバイスからデータを取得
			if (SUCCEEDED(m_pJDevice[nJoystick]->GetDeviceState(sizeof(DIJOYSTATE), &js)))
			{
				for (nCntKey = 0; nCntKey < NUM_JS_MAX; nCntKey++)
				{
					//キープレス情報を保存
					m_aJoyState[nCntKey][nJoystick] = m_aJoyState[nCntKey][nJoystick];

					//キートリガー
					m_aJoyStateTrigger[nCntKey][nJoystick] = (m_aJoyState[nCntKey][nJoystick] ^ js.rgbButtons[nCntKey]) &  js.rgbButtons[nCntKey];

					//キーリリース
					m_aJoyStateRelease[nCntKey][nJoystick] = (m_aJoyState[nCntKey][nJoystick] ^ js.rgbButtons[nCntKey]) & ~js.rgbButtons[nCntKey];

					//キープレス情報を保存
					m_aJoyState[nCntKey][nJoystick] = js.rgbButtons[nCntKey];
				}
			}
			else
			{
				m_pJDevice[nJoystick]->Acquire();
			}
		}
	}
}

//=============================================================================
// PRESS
//=============================================================================
bool CJoystick::GetJoystickPress(int nKey,int nJoysytick)
{
	return m_aJoyState[nKey][nJoysytick] & 0x80 ? true : false;
}

//=============================================================================
// TRIGGER
//=============================================================================
bool CJoystick::GetJoystickTrigger(int nKey, int nJoysytick)
{
	return m_aJoyStateTrigger[nKey][nJoysytick] & 0x80 ? true : false;
}

//=============================================================================
// RELEASE
//=============================================================================
bool CJoystick::GetJoystickRelease(int nKey, int nJoysytick)
{
	return m_aJoyStateRelease[nKey][nJoysytick] & 0x80 ? true : false;
}

//=============================================================================
//    Force Feedback Callback.
//=============================================================================
BOOL CJoystick::EnumFFDevicesCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext)
{
	HRESULT hr;
	// 接続できるジョイスティックの最大数分回す
	for (int nJoystick = 0; nJoystick < MAX_JOYSTICK; nJoystick++)
	{
		hr = m_pDInput->CreateDevice(pdidInstance->guidInstance, &m_pJDevice[nJoystick], NULL);
		if (FAILED(hr)) return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}

//=============================================================================
//EnumJoysticksCallback
//=============================================================================
BOOL CALLBACK CJoystick::EnumJoysticksCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext)
{
	HRESULT hr;
	// 接続できるジョイスティックの最大数分回す
	for (int nJoystick = 0; nJoystick < MAX_JOYSTICK; nJoystick++)
	{
		hr = m_pDInput->CreateDevice(pdidInstance->guidInstance, &m_pJDevice[nJoystick], NULL);

		if (FAILED(hr)) return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}

//=============================================================================
// EnumAxesCallback
//=============================================================================
BOOL CALLBACK CJoystick::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE * pdidoi, VOID * pContext)
{
	HRESULT     hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = 0 - 1000;
	diprg.lMax = 0 + 1000;
	// 接続できるジョイスティックの最大数分回す
	for (int nJoystick = 0; nJoystick < MAX_JOYSTICK; nJoystick++)
	{
		hr = m_pJDevice[nJoystick]->SetProperty(DIPROP_RANGE, &diprg.diph);
	}
	if (FAILED(hr)) return DIENUM_STOP;

	DWORD *pdwNumForceFeedbackAxis = (DWORD*)pContext;
	if ((pdidoi->dwFlags & DIDOI_FFACTUATOR) != 0) (*pdwNumForceFeedbackAxis)++;

	return DIENUM_CONTINUE;
}

//=============================================================================
// Create Effect.
//=============================================================================
BOOL CJoystick::CreateEffect(HWND hWnd)
{
	DWORD           rgdwAxes[2] = { DIJOFS_X , DIJOFS_Y };
	LONG            rglDirection[2] = { 1 , 1 };
	DICONSTANTFORCE cf;
	DIEFFECT        eff;
	HRESULT         hr;

	ZeroMemory(&eff, sizeof(eff));
	eff.dwSize = sizeof(DIEFFECT);
	eff.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	eff.dwDuration = INFINITE;
	eff.dwSamplePeriod = 0;
	eff.dwGain = DI_FFNOMINALMAX;
	eff.dwTriggerButton = DIEB_NOTRIGGER;
	eff.dwTriggerRepeatInterval = 0;
	eff.cAxes = m_dwNumForceFeedbackAxis;
	eff.rgdwAxes = rgdwAxes;
	eff.rglDirection = rglDirection;
	eff.lpEnvelope = 0;
	eff.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
	eff.lpvTypeSpecificParams = &cf;
	eff.dwStartDelay = 0;
	// 接続できるジョイスティックの最大数分回す
	for (int nJoystick = 0; nJoystick < MAX_JOYSTICK; nJoystick++)
	{
		hr = m_pJDevice[nJoystick]->CreateEffect(GUID_ConstantForce, &eff,
			&m_IpDIEffect[nJoystick], NULL);
	}
	if (FAILED(hr)) {
		MessageBox(hWnd, "Can't create effect.", "Error", MB_OK);
		return FALSE;
	}

	return TRUE;
}