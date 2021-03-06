//====================================================================
//
// プレイヤー2処理 (player_hook.cpp)
// Author : 樋宮 匠
//
//====================================================================

//================================================
// インクルードファイル
//================================================
#include "player_hook.h"
#include "wire.h"
#include "spike.h"

//========================================
// 静的メンバ変数宣言
//========================================
LPDIRECT3DTEXTURE9 CPlayerHook::m_pTexture = NULL;
CWire *pWire = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayerHook::CPlayerHook()
{
	m_pos = DEFAULT_VECTOR;
	m_move = DEFAULT_VECTOR;
	m_bHook = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayerHook::~CPlayerHook()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayerHook::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CPlayer::Init();
	m_move = MOVE_SPECIFIED;
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Player2.jpg", &m_pTexture);
	BindTexture(m_pTexture);

	m_bJumpJudge = true;

	pWire = CWire::Create(D3DXVECTOR3(200.0f, 50.0f, 0.0f));
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayerHook::Uninit(void)
{
	CPlayer::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayerHook::Update(void)
{
	m_pCamera = CManager::GetCamera();
	CCamera::ORIENTATION Orientation = m_pCamera->GetOrientation();
	CInputKeyboard *pKeyboard = CManager::GetInput();
	D3DXVECTOR3 destPos;

	m_pos = GetPos();
	destPos = SortSpike();
	m_move.y -= GRAVITY_SIZ;

	if (pKeyboard->GetKeyboardTrigger(DIK_F) && m_bHook == false)
	{
		// 周りにフックをかけれるか探索
		// かけられるならフラグをtrueに
		m_bHook = true;

	}

	if (m_bHook)
	{
		// 当たり判定オフ
		// プレイヤーの一番近い場所にフックでの移動処理
		MoveToHook(destPos);
	}
	else
	{
		// プレイヤー操作
		if (m_pCamera->GetRotake() == CCamera::ROTATE_NONE) {
			switch (Orientation) {
			case CCamera::ORIENTATION_BACK:
				// ←キーで左移動
				if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
					m_pos.x += m_move.x;
				}
				// →キーで右移動
				if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
					m_pos.x -= m_move.x;
				}
				break;

			case CCamera::ORIENTATION_LEFT:
				// ←キーで左移動
				if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
					m_pos.z += m_move.z;
				}
				// →キーで右移動
				if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
					m_pos.z -= m_move.z;
				}
				break;

			case CCamera::ORIENTATION_FRONT:
				// ←キーで左移動
				if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
					m_pos.x -= m_move.x;
				}
				// →キーで右移動
				if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
					m_pos.x += m_move.x;
				}
				break;

			case CCamera::ORIENTATION_RIGHT:
				// ←キーで左移動
				if (pKeyboard->GetKeyboardPress(DIK_LEFT)) {
					m_pos.z -= m_move.z;
				}
				// →キーで右移動
				if (pKeyboard->GetKeyboardPress(DIK_RIGHT)) {
					m_pos.z += m_move.z;
				}
				break;
			}

			// スペースキーでジャンプ
			if (m_bJumpJudge == true && pKeyboard->GetKeyboardTrigger(DIK_UP)) {
				m_bJumpJudge = false;
				m_move.y = JUMP_SIZ;
			}
		}
	}

	m_pos.y += m_move.y;
	if (m_pos.y <= 0) {
		m_pos.y = 0;
		m_bJumpJudge = true;
	}

	SetCol(D3DXCOLOR(0, 0, 0, 255));
	SetPos(m_pos);
	CPlayer::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayerHook::Draw(void)
{
	CPlayer::Draw();
}

//=============================================================================
// フック地点ソート処理
//=============================================================================
D3DXVECTOR3 CPlayerHook::SortSpike(void)
{

	// 距離
	float distHorizon = 0.0f;
	float distVert = 0.0f;
	float dist = 0.0f;
	int nArrayCount = 0;

	// フック地点
	CObject *pObj;
	pObj = CObject::GetTopObj(CObject::OBJ_TYPE_SPIKE);
	D3DXVECTOR3 spikePos = DEFAULT_VECTOR;
	D3DXVECTOR3 destPos = DEFAULT_VECTOR;
	CSpike *pDestSpike = NULL;

	// カメラの位置を取得
	CCamera *pCamera;
	pCamera = CManager::GetCamera();
	CCamera::ORIENTATION Orientation = pCamera->GetOrientation();
	SPIKE spike[50];

	for (int nCntScene = 0; nCntScene < CObject::GetNumObj(CObject::OBJ_TYPE_SPIKE); nCntScene++)
	{
		// 中身があるなら
		if (pObj != NULL)
		{
			// 次のシーンを記憶
			CObject *pNextObj = pObj->GetNextObj();

			// ブロックにキャスト
			CSpike *pSpike = (CSpike*)pObj;

			spikePos = pSpike->GetPos();
			spike[nCntScene].pos = spikePos;

			// 距離を計算
			if (Orientation == CCamera::ORIENTATION_BACK || Orientation == CCamera::ORIENTATION_FRONT)
			{
				distHorizon = spikePos.x - m_pos.x;
				distVert = spikePos.y - m_pos.y;
			}
			else if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT)
			{
				distHorizon = spikePos.z - m_pos.z;
				distVert = spikePos.y - m_pos.y;
			}

			spike[nCntScene].dist = sqrtf(distHorizon*distHorizon + distVert*distVert);

			if (nCntScene == 0)
			{
				spike[0].pSpike = pSpike;
			}
			else if (spike[nCntScene].dist < spike[nArrayCount].dist)
			{
				nArrayCount = nCntScene;
				spike[nArrayCount].pSpike = pSpike;
				spike[0].pSpike->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
			}
			else
			{
				pSpike->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
			}

			spike[nArrayCount].pSpike->SetCol(D3DCOLOR_RGBA(255, 0, 0, 255));

			// 次のシーンにする
			pObj = pNextObj;
		}
		else
		{
			break;
		}
	}

	return spike[nArrayCount].pos;
}

//=============================================================================
// フックを飛ばす処理
//=============================================================================
void CPlayerHook::ShotHook(D3DXVECTOR3 pos)
{
}

//=============================================================================
// 指定した座標まで飛ぶ処理
//=============================================================================
void CPlayerHook::MoveToHook(D3DXVECTOR3 pos)
{
	// 距離
	float distHorizon = 0.0f;
	float distVert = 0.0f;
	// 角度
	float fAngle = 0.0f;

	// カメラの位置を取得
	CCamera *pCamera;
	pCamera = CManager::GetCamera();
	CCamera::ORIENTATION Orientation = pCamera->GetOrientation();

	// プレイヤーのサイズ分目標座標をずらす
	pos.z += PLAYER_SIZE.z / 2.0f;

	// 指定座標との距離を出す
	if (Orientation == CCamera::ORIENTATION_BACK || Orientation == CCamera::ORIENTATION_FRONT)
	{
		distHorizon = pos.x - m_pos.x;
	}
	else if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT)
	{
		distHorizon = pos.z - m_pos.z;
	}

	distVert = pos.y - m_pos.y;

	// プレイヤーへの角度を加算
	m_circle.fAngle += D3DXToRadian(90) / HOOK_MOVE_FRAME;
	// 180°以上で修正
	if (m_circle.fAngle >= D3DXToRadian(90))
	{
		m_circle.fAngle = D3DXToRadian(90);
	}

	// 距離から角度を計算
	fAngle = atan2f(distVert, distHorizon);

	// 移動量を計算
	if (Orientation == CCamera::ORIENTATION_BACK || Orientation == CCamera::ORIENTATION_FRONT)
	{
		m_move = D3DXVECTOR3(cos(fAngle) * HOOK_SPD_RATE, sin(fAngle) * HOOK_SPD_RATE, 0.0f);
	}
	else if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT)
	{
		m_move = D3DXVECTOR3(0.0f, sin(fAngle) * HOOK_SPD_RATE, cos(fAngle) * HOOK_SPD_RATE);
	}

	// 移動量を加算
	m_pos += m_move * sinf(m_circle.fAngle);

	// フックによる移動が終わったらフラグをfalseにする
	if (Orientation == CCamera::ORIENTATION_BACK || Orientation == CCamera::ORIENTATION_FRONT)
	{
		if (fabsf(pos.x - m_pos.x) <= HOOK_STOP_SIZE &&
			fabsf(pos.y - m_pos.y) <= HOOK_STOP_SIZE)
		{
			m_bHook = false;
			m_pos.z = pos.z;
			m_circle.fAngle = 0.0f;
		}
	}
	else if (Orientation == CCamera::ORIENTATION_LEFT || Orientation == CCamera::ORIENTATION_RIGHT)
	{
		if (fabsf(pos.z - m_pos.z) <= HOOK_STOP_SIZE &&
			fabsf(pos.y - m_pos.y) <= HOOK_STOP_SIZE)
		{
			m_bHook = false;
			m_pos.x = pos.x;
			m_circle.fAngle = 0.0f;
		}
	}

	// 位置を更新
	SetPos(m_pos);
}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CPlayerHook * CPlayerHook::Create(D3DXVECTOR3 pos, D3DXVECTOR3 siz)
{
	CPlayerHook *pPlayerHook = NULL;
	pPlayerHook = new CPlayerHook;
	pPlayerHook->Init();
	pPlayerHook->SetPos(pos);
	pPlayerHook->SetSize(siz);
	return pPlayerHook;
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
void CPlayerHook::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/Player2.jpg", &m_pTexture);
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CPlayerHook::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
