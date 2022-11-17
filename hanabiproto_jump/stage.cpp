/*==============================================================================

				   オブジェクト処理 [stage.cpp]
				Author : いでうら
				Date    : 2022/10/23(最終編集日)
------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#include "stage.h"	
#include "texture.h"
#include "collision.h"
#include "sprite.h"
#include "camera.h"
#include "player.h"

//*****************************************************************************							
// マクロ定義							
//*****************************************************************************							

//*****************************************************************************							
// プロトタイプ宣言							
//*****************************************************************************							

//*****************************************************************************							
// グローバル変数							
//*****************************************************************************							
static int g_TextureNo;
static Stage g_Stage;

static PLAYER* g_Player = GetPlayer();
static Float2 g_Block;

static int StageBase[STAGE_Y][STAGE_X] =
{
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1 },
};

static float g_U, g_V;
//=============================================================================							
// 初期化処理							
//=============================================================================							
HRESULT InitStage(void)
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/proto_robot_stage_zimen2.png");

	//初期化
	g_Stage.pos.x = SCREEN_WIDTH;
	g_Stage.pos.y = SCREEN_HEIGHT;

	g_U = 0.0f;
	g_V = 0.0f;

	return S_OK;
}

//=============================================================================							
// 終了処理							
//=============================================================================							
void UninitStage(void)
{

}

//=============================================================================							
// 更新処理							
//=============================================================================							
void UpdateStage(void)
{
}

//=============================================================================							
// 描画処理							
//=============================================================================							
void DrawStage(void)
{
	//ベース座標を取得する
	D3DXVECTOR2 basePos = GetBase();

	//ベースレイヤーの描画
	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (StageBase[y][x] == 1)
			{

				DrawSprite(g_TextureNo, basePos.x + 32.0f + CHIPSIZE_X * x, basePos.y + CHIPSIZE_Y * y,
					CHIPSIZE_X, CHIPSIZE_Y, 1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}
}

bool GetStageInfoUE(Float2 playerpos)
{
	int StageY, StageXL, StageXR;
	Float2 playerhead;
	playerhead.y = (playerpos.y- PLAYER_SIZEY / 2);
	playerhead.x = playerpos.x;

	StageY = (int)((playerhead.y - CHIPSIZE_Y / 2) / CHIPSIZE_Y);
	StageXR = (int)((playerhead.x + CHIPSIZE_X / 2) / CHIPSIZE_X);
	StageXL = (int)((playerhead.x - CHIPSIZE_X / 2) / CHIPSIZE_X);

	switch (StageBase[StageY+1][StageXR])
	{
	case 0:
		break;
	case 1:
		return true;
		break;
	}
	switch (StageBase[StageY+1][StageXL])
	{
	case 0:
		break;
	case 1:
		return true;
		break;
	}
	return false;
}

bool GetStageInfoSITA(Float2 playerpos)
{
	int StageY, StageXL,StageXR;
	Float2 playerfoot;
	playerfoot.y = (playerpos.y + PLAYER_SIZEY / 2);
	playerfoot.x = playerpos.x;

	StageY = (int)((playerfoot.y + CHIPSIZE_Y / 2) / CHIPSIZE_Y);
	StageXR = (int)((playerfoot.x + CHIPSIZE_X / 2) / CHIPSIZE_X);
	StageXL = (int)((playerfoot.x - CHIPSIZE_X / 2) / CHIPSIZE_X);

	switch (StageBase[StageY][StageXR])
	{
	case 0:
		break;
	case 1 :
		return true;
		break;
	}
	switch (StageBase[StageY][StageXL])
	{
	case 0:
		break;
	case 1:
		return true;
		break;
	}
	return false;
}

bool GetStageInfoMIGI(Float2 playerpos)
{
	int StageYU, StageYD, StageX;
	Float2 playerfront;
	playerfront.y = playerpos.y;
	playerfront.x = playerpos.x+PLAYER_SIZEX/2;

	StageX = (int)((playerfront.x + CHIPSIZE_X / 2) / CHIPSIZE_X);
	//StageX = (int)(playerfront.x);
	StageYD = (int)(playerfront.y /CHIPSIZE_Y);
	StageYU = (int)(playerfront.y - CHIPSIZE_Y / 2);

	switch (StageBase[StageYU][StageX])
	{
	case 0:
		break;
	case 1:
		return true;
		break;
	}
	switch (StageBase[StageYD][StageX])
	{
	case 0:
		break;
	case 1:
		return true;
		break;
	}
	return false;
}

bool GetStageInfoHIDARI(Float2 playerpos)
{
	return 0;
}

