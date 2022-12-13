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
#include "enemy.h"

//*****************************************************************************							
// マクロ定義							
//*****************************************************************************							

//*****************************************************************************							
// プロトタイプ宣言							
//*****************************************************************************							

//*****************************************************************************							
// グローバル変数							
//*****************************************************************************							
static int g_TextureNo;	//ブロック
static int g_TextureNo2;//川
static int g_TextureNo3;//雨
static int g_TextureNo4;//ゴール
static Stage g_Stage;
static Float2 g_Block;

static int StageBase[STAGE_Y][STAGE_X] =/*０：空気　１：ブロック　２：川　３：雨　４：ゴール(?)*/
{
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0 },
{ 0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,1,1,1,1,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,2,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2 },
};

static float g_U, g_V;
//=============================================================================							
// 初期化処理							
//=============================================================================							
HRESULT InitStage(void)
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/proto_robot_stage_zimen2.png");
	g_TextureNo2 = LoadTexture((char*)"data/TEXTURE/River-sample.png");
	g_TextureNo3 = LoadTexture((char*)"data/TEXTURE/Rain-sample.png");
	g_TextureNo4 = LoadTexture((char*)"data/TEXTURE/Flag.png");

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
			switch (StageBase[y][x])
			{
			case 1:
				DrawSprite(g_TextureNo, basePos.x + CHIPSIZE_X / 2 + CHIPSIZE_X * x, basePos.y + CHIPSIZE_Y * y,
					CHIPSIZE_X, CHIPSIZE_Y, 1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case 2:
				DrawSprite(g_TextureNo2, basePos.x + CHIPSIZE_X / 2 + CHIPSIZE_X * x, basePos.y + CHIPSIZE_Y * y,
					CHIPSIZE_X, CHIPSIZE_Y, 1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case 3:
				DrawSprite(g_TextureNo3, basePos.x + CHIPSIZE_X / 2 + CHIPSIZE_X * x, basePos.y + CHIPSIZE_Y * y,
					CHIPSIZE_X, CHIPSIZE_Y, 1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case 4:
				DrawSprite(g_TextureNo4, basePos.x + CHIPSIZE_X + CHIPSIZE_X * x, basePos.y + CHIPSIZE_Y * y,
					CHIPSIZE_X*1.5, CHIPSIZE_Y*4, 1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}
		}
	}
}

int GetStageInfoUE(Float2 playerpos)
{
	int StageY, StageXL, StageXR;
	int ReturnPos = NULL;

	Float2 playerhead;
	playerhead.y = playerpos.y - PLAYER_SIZEY / 2;
	playerhead.x = playerpos.x - PLAYER_SIZEX / 2;

	StageY = (int)((playerhead.y + CHIPSIZE_Y / 2) / CHIPSIZE_Y);
	StageXL = (int)(playerhead.x / CHIPSIZE_X);
	StageXR = (int)((playerhead.x + PLAYER_SIZEX) / CHIPSIZE_X);

	for (int i = 0; i < (int)(PLAYER_SIZEX / CHIPSIZE_X); i++)
	{
		switch (StageBase[StageY][StageXL + i])
		{
		case 0:
			break;
		case 1:
			ReturnPos = (StageY * CHIPSIZE_Y);
			break;
		case 2:
			return -1;
			break;
		case 4:
			return -2;
			break;
		}
	}

	switch (StageBase[StageY][StageXR])
	{
	case 0:
		break;
	case 1:
		ReturnPos = (StageY * CHIPSIZE_Y);
		break;
	case 2:
		return -1;
		break;
	case 4:
		return -2;
		break;
	}

	return ReturnPos;
}

int GetStageInfoSITA(Float2 playerpos)
{
	int StageY, StageXL, StageXR;
	int ReturnPos = NULL;
	
	Float2 playerfoot;
	playerfoot.y = (playerpos.y + PLAYER_SIZEY / 2);
	playerfoot.x = playerpos.x - PLAYER_SIZEX / 2;

	StageY = (int)((playerfoot.y + CHIPSIZE_Y / 2) / CHIPSIZE_Y);
	StageXL = (int)(playerfoot.x /CHIPSIZE_X);
	StageXR = (int)((playerfoot.x + PLAYER_SIZEX) / CHIPSIZE_X);
	
	for (int i = 0; i < (int)(PLAYER_SIZEX / CHIPSIZE_X); i++)
	{

		switch (StageBase[StageY][StageXL + i])
		{
		case 0:
			break;
		case 1:
			ReturnPos = (StageY * CHIPSIZE_Y);
			break;
		case 2:
			return -1;
			break;
		case 4:
			return -2;
			break;
		}
	}

	switch (StageBase[StageY][StageXR])
	{
	case 0:
		break;
	case 1:
		ReturnPos = (StageY * CHIPSIZE_Y);
		break;
	case 2:
		return -1;
		break;
	case 4:
		return -2;
		break;
	}

	return ReturnPos;
}

int GetStageInfoMIGI(Float2 playerpos)
{
	int StageYT, StageYB, StageX;
	int ReturnPos = NULL;

	Float2 playerfront;
	playerfront.y = playerpos.y - PLAYER_SIZEY / 2;
	playerfront.x = playerpos.x + PLAYER_SIZEX / 2;

	StageX = (int)(playerfront.x / CHIPSIZE_X);
	StageYT = (int)(playerfront.y / CHIPSIZE_Y);
	StageYB = (int)((playerfront.y + PLAYER_SIZEY) / CHIPSIZE_Y);

	for (int i = 0; i < (int)(PLAYER_SIZEY / CHIPSIZE_Y); i++)
	{
		switch (StageBase[StageYT + i][StageX])
		{
			case 0:
				break;
			case 1:
				ReturnPos = (StageX * CHIPSIZE_X);
				break;
			case 2:
				return -1;
				break;
			case 4:
				return -2;
				break;
		}
	}

	switch (StageBase[StageYB][StageX])
	{
	case 0:
		break;
	case 1:
		ReturnPos = (StageX * CHIPSIZE_X);
		break;
	case 2:
		return -1;
		break;
	case 4:
		return -2;
		break;
	}

	return ReturnPos;
}

int GetStageInfoHIDARI(Float2 playerpos)
{
	int StageYT, StageYB, StageX;
	int ReturnPos = NULL;

	Float2 playerback;
	playerback.y = (playerpos.y - PLAYER_SIZEY / 2);
	playerback.x = (playerpos.x - PLAYER_SIZEX / 2);

	StageYT = (int)(playerback.y / CHIPSIZE_Y);
	StageX = (int)(playerback.x / CHIPSIZE_X);
	StageYB = (int)((playerback.y + PLAYER_SIZEY) / CHIPSIZE_Y);
	

	for (int i = 0; i < (int)(PLAYER_SIZEY / CHIPSIZE_Y); i++)
	{
		switch (StageBase[StageYT + i][StageX])
		{
		case 0:
			break;
		case 1:
			ReturnPos = (StageX * CHIPSIZE_X);
			break;
		case 2:
			return -1;
			break;
		case 4:
			return -2;
			break;
		}
	}

	switch (StageBase[StageYB][StageX])
	{
	case 0:
		break;
	case 1:
		ReturnPos = (StageX * CHIPSIZE_X);
		break;
	case 2:
		return -1;
		break;
	case 4:
		return -2;
		break;
	}
	return ReturnPos;
}

bool GetStageInfoRain(Float2 akaripos)
{
	int StageY, StageX;

	StageX = (int)(akaripos.x / CHIPSIZE_X);
	StageY = (int)(akaripos.y / CHIPSIZE_Y);

	switch (StageBase[StageY][StageX])
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		return true;
		break;
	}
	return false;
}

int GetStageInfoEnemySITA(Float2 enemypos, Float2 enemysize)
{
	int StageY, StageXL, StageXR;
	int ReturnPos = NULL;

	Float2 enemyfoot;
	enemyfoot.y = (enemypos.y + enemysize.y / 2);
	enemyfoot.x = enemypos.x - enemysize.x / 2;

	StageY = (int)((enemyfoot.y + CHIPSIZE_Y / 2) / CHIPSIZE_Y);
	StageXL = (int)(enemyfoot.x / CHIPSIZE_X);
	StageXR = (int)((enemyfoot.x + enemysize.x) / CHIPSIZE_X);

	for (int i = 0; i < (int)(enemysize.x / CHIPSIZE_X); i++)
	{
		switch (StageBase[StageY][StageXL + i])
		{
		case 0:
			break;
		case 1:
			ReturnPos = (StageY * CHIPSIZE_Y);
			break;
		case 2:
			return -1;
			break;
		case 4:
			return -2;
			break;
		}
	}

	switch (StageBase[StageY][StageXR])
	{
	case 0:
		break;
	case 1:
		ReturnPos = (StageY * CHIPSIZE_Y);
		break;
	case 2:
		return -1;
		break;
	case 4:
		return -2;
		break;
	}

	return ReturnPos;
}

