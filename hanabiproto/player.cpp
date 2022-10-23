/*==============================================================================

   頂点管理 [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_DISP_X (SCREEN_WIDTH/2)
#define PLAYER_DISP_Y (SCREEN_HEIGHT/2)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TextureNo;

static PLAYER g_Player;

static float g_U, g_V;

//static int g_AnimeIndex;
//static int g_AnimeWait;

static unsigned int g_StartTime;
static unsigned int g_Second;
static unsigned int g_MiliSecond;

static float g_AnimeTable[4] =
{
	0.0f,
	0.333333f,
	0.666667f,
	1.0f,
};

//static float g_AnimeTable[4] =
//{
//	0.0f,
//	0.333333f,
//	0.666667f,
//	0.333333f,
//};
//
//static float g_MukiTable[4] =
//{
//	0.75f,	//上向き
//	0.5f,	//右向き
//	0.0f,	//下向き
//	0.25f,	//左向き
//};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/proto_Hanabi_character.png");

	//初期化
	g_Player.pos.x = PLAYER_DISP_X;
	g_Player.pos.y = PLAYER_DISP_Y;

	g_Player.spjp.x = 8.0f;
	g_Player.spjp.y = 8.0f;

	//g_AnimeIndex = 0;
	//g_AnimeWait = 0;
	
	g_U = 0.0f;
	g_V = 0.0f;

	//ゲーム開始時の時刻を取得する
	g_StartTime = timeGetTime();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//キーボードのAキーが押されたら左に移動する
	if (GetKeyboardPress(DIK_A))
	{
		g_Player.pos.x -= g_Player.spjp.x;
		g_Player.vec.x = -2.0;
	}
	//キーボードのDキーが押されたら右に移動する
	if (GetKeyboardPress(DIK_D))
	{
		g_Player.pos.x += g_Player.spjp.x;
		g_Player.vec.x = 2.0;
	}

	//if (GetKeyboardPress(DIK_W))
	//{
	//	g_Player.pos.y -= 2.0f;
	//}
	//if (GetKeyboardPress(DIK_S))
	//{
	//	g_Player.pos.y += 2.0f;
	//}


	//カメラ座標の更新
	//プレイヤー座標から表示座標分を引いた値をカメラ座標としてセットする
	D3DXVECTOR2 cameraPos;
	cameraPos.x = g_Player.pos.x - PLAYER_DISP_X;
	cameraPos.y = g_Player.pos.y - PLAYER_DISP_Y;
	if (cameraPos.x < 0) cameraPos.x = 0.0f;
	if (cameraPos.y < 0) cameraPos.y = 0.0f;
	if (cameraPos.x > 960) cameraPos.x = 960.0f;
	if (cameraPos.y > 540) cameraPos.y = 540.0f;
	SetCameraPos(cameraPos.x, cameraPos.y);



	unsigned int nowTime = timeGetTime();

//	SetNumber(30000-(nowTime - g_StartTime));
	g_Second = (nowTime - g_StartTime) / 1000;
	g_MiliSecond = ((nowTime - g_StartTime) % 1000) / 10;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	//ベース座標を取得する
	D3DXVECTOR2 basePos = GetBase();

	DrawSprite(g_TextureNo, basePos.x + g_Player.pos.x, basePos.y + g_Player.pos.y, 
		120.0f, 120.0f,
		0.33333, 0.0, 
		0.33333f, 1.0f);

	//0.33333f, 0.25f);
}


//PLAYER* GetPlayer(void)
//{
//	return &g_Player;
//}
