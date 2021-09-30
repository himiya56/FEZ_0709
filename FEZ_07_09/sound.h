//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ��{ ��
//
//=============================================================================

// 2�d�C���N���[�h�h�~�p
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
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
// �T�E���h�N���X
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// �񋓌^�錾
	typedef enum
	{
		SOUND_LABEL_SE_BUTTON_SELECT,	// �{�^���I����
		SOUND_LABEL_SE_BUTTON_PUSH,		// �{�^����������
		SOUND_LABEL_SE_BUTTON_CANCEL,	// �{�^���L�����Z����
		SOUND_LABEL_BGM_TITLE,			// �^�C�g��BGM
		SOUND_LABEL_BGM_TUTORIAL,		// �`���[�g���A��BGM
		SOUND_LABEL_BGM_STAGE_SELECT,	// �X�e�[�W�I��BGM
		SOUND_LABEL_BGM_RESULT,			// ���U���gBGM
		SOUND_LABEL_BGM_STAGE1,			// �X�e�[�W1BGM
		SOUND_LABEL_BGM_GOAL,			// �S�[��BGM
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);


private:
	// �\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;

	IXAudio2				*m_pXAudio2 = NULL;						// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};	// �I�[�f�B�I�f�[�^
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};		// �I�[�f�B�I�f�[�^�T�C�Y
	static PARAM			m_aParam[SOUND_LABEL_MAX];				// �e���f�ނ̃p�����[�^

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
};

#endif