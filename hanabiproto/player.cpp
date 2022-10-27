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
#include "BENRIclass.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_DISP_X (SCREEN_WIDTH/2)
#define PLAYER_DISP_Y (SCREEN_HEIGHT/2)
#define PLAYER_CURSOR_NUM

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TextureNo;
static int g_TextureNo2;

static PLAYER g_Player;

static float g_U, g_V;

CURSOR		g_cursor[256];	//カーソルの軌跡点
int			g_nownum = -1;//カーソルの現在個数
Float2 cursorposf;
POINT cursorPos;

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
	g_TextureNo2 = LoadTexture((char*)"data/TEXTURE/proto_effect_explosion.png");

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

	//カーソル初期化
	for (int i = 0; i < 256; i++)
	{
		g_cursor[i].use = false;
	}

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
	//cursor処理＝＝＝＝＝＝＝＝＝
	if (GetKeyState(VK_LBUTTON) & 0x80)
	{
		bool flag = false;
		if (g_nownum != -1)
		{
			flag = true;
		}

		g_nownum++;
		GetCursorPos(&cursorPos);
		ScreenToClient(GethWnd(), &cursorPos);
		cursorposf.x = (float)cursorPos.x;
		cursorposf.y = (float)cursorPos.y;
		g_cursor[g_nownum].pos.x = (cursorposf.x);
		g_cursor[g_nownum].pos.y = (cursorposf.y);
		g_cursor[g_nownum].prev_pos.x = g_cursor[g_nownum].pos.x - 1;
		g_cursor[g_nownum].prev_pos.y = g_cursor[g_nownum].pos.y - 1;
		if (flag)
		{
			g_cursor[g_nownum].prev_pos = g_cursor[(g_nownum + 255) % 256].pos;
		}
		g_cursor[g_nownum].use = true;
		g_cursor[(g_nownum + 257) % 256].use = false;

		if (g_nownum >= 256)
			g_nownum = 0;

		for (int i = 1; i < 256; i++)
		{
			int j = (i + g_nownum) % 256;
			if (g_cursor[j].use == true)
			{
				if (HitCheckCross2nd(g_cursor[j].prev_pos, g_cursor[j].pos
					, g_cursor[g_nownum].prev_pos, g_cursor[g_nownum].pos) == true)
				{
					for (int i = 0; i < 256; i++)
					{
						g_cursor[i].use = false;
					}
					g_nownum = -1;
				}
			}
		}
	}
	else if(g_nownum != -1)
	{
		for (int i = 0; i < 256; i++)
		{
			g_cursor[i].use = false;
		}
		g_nownum = -1;
	}
	//==========================================




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

	for (int i = 0; i < 256; i++)
	{
		if (g_cursor[i].use == true)
		{
			DrawSprite(g_TextureNo2,g_cursor[i].pos.x,g_cursor[i].pos.y,
				120.0f, 120.0f,
				1.0f, 0.0,
				1.0f, 1.0f);

			//DrawSprite(g_TextureNo, basePos.x + g_cursor[i].pos.x, basePos.y + g_cursor[i].pos.y,
			//	120.0f, 120.0f,
			//	0.33333, 0.0,
			//	0.33333f, 1.0f);
		}
	}

}

bool CompositionAkari(Float2 akaripos)
{
	for (int i = 0; i < 256; i++)
	{
		if(0 < g_cursor[i].pos.x - g_cursor[i].prev_pos.x)
	}

	return true;
}

PLAYER* GetPlayer(void)
{
	return &g_Player;
}
