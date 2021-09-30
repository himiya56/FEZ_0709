//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 樋宮 匠
//
//=============================================================================

// 2重インクルード防止用
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SOUND_PASS_BUTTON_SELECT "data/SOUND/SE/se_button_select.wav"
#define SOUND_PASS_BUTTON_PUSH "data/SOUND/SE/se_button_push.wav"
#define SOUND_PASS_BUTTON_CANCEL "data/SOUND/SE/se_button_cancel.wav"
#define SOUND_PASS_BGM_TITLE "data/SOUND/BGM/title.wav"
#define SOUND_PASS_BGM_TUTORIAL "data/SOUND/BGM/Tutorial.wav"
#define SOUND_PASS_BGM_STAGE_SELECT "data/SOUND/BGM/stage_select.wav"
#define SOUND_PASS_BGM_RESULT "data/SOUND/BGM/result.wav"
#define SOUND_PASS_BGM_STAGE1 "data/SOUND/BGM/stage1.wav"
#define SOUND_PASS_BGM_GOAL "data/SOUND/BGM/goal.wav"

//*****************************************************************************
// サウンドクラス
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// 列挙型宣言
	typedef enum
	{
		SOUND_LABEL_SE_BUTTON_SELECT,	// ボタン選択音
		SOUND_LABEL_SE_BUTTON_PUSH,		// ボタンを押す音
		SOUND_LABEL_SE_BUTTON_CANCEL,	// ボタンキャンセル音
		SOUND_LABEL_BGM_TITLE,			// タイトルBGM
		SOUND_LABEL_BGM_TUTORIAL,		// チュートリアルBGM
		SOUND_LABEL_BGM_STAGE_SELECT,	// ステージ選択BGM
		SOUND_LABEL_BGM_RESULT,			// リザルトBGM
		SOUND_LABEL_BGM_STAGE1,			// ステージ1BGM
		SOUND_LABEL_BGM_GOAL,			// ゴールBGM
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);


private:
	// 構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;

	IXAudio2				*m_pXAudio2 = NULL;						// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;				// マスターボイス
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};	// オーディオデータ
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};		// オーディオデータサイズ
	static PARAM			m_aParam[SOUND_LABEL_MAX];				// 各音素材のパラメータ

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
};

#endif