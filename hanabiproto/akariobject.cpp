/*==============================================================================

				   オブジェクト処理 [akariobject.cpp]
				Author : いでうら
				Date    : 2022/10/23(最終編集日)
------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#include "object.h"	
#include "texture.h"
#include "collision.h"
#include "sprite.h"
#include "camera.h"
#include "input.h"
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

static HanabiAkariObject g_AkariObject[AKARI_NUM];

static float g_U, g_V;

Float2 MovePos[AKARI_NUM];

bool g_composition;
//=============================================================================							
// 初期化処理							
//=============================================================================							
HRESULT InitAkariObject(void)
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/proto_effect_explosion.png");

	//初期化
	for (int i = 0; i < AKARI_NUM; i++)
	{
		g_AkariObject[i].use = false;
		g_AkariObject[i].gather = false;
		g_AkariObject[i].setvec = false;
		g_AkariObject[i].dir.x = 0.0f;
		g_AkariObject[i].dir.y = 0.0f;
		g_AkariObject[i].pos.x = SCREEN_WIDTH;
		g_AkariObject[i].pos.y = SCREEN_HEIGHT;
	}

	//お試し
	for (int i = 0; i < 5; i++)
	{
		g_AkariObject[i].gather = true;
		g_AkariObject[i].pos.x = frand() * SCREEN_WIDTH;
		g_AkariObject[i].pos.y = frand() * SCREEN_HEIGHT;
		g_AkariObject[i].use = true;
	}

	g_U = 0.0f;
	g_V = 0.0f;

	g_composition = true;

	return S_OK;
}

//=============================================================================							
// 終了処理							
//=============================================================================							
void UninitAkariObject(void)
{

}

//=============================================================================							
// 更新処理							
//=============================================================================							
void UpdateAkariObject(void)
{
	//テスト
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		for (int i = 0; i < AKARI_NUM; i++)
		{
			if (g_AkariObject[i].use == false)
			{
				g_AkariObject[i].use = true;
				g_AkariObject[i].gather = false;
				g_AkariObject[i].pos.x = frand() * SCREEN_WIDTH;
				g_AkariObject[i].pos.y = frand() * SCREEN_HEIGHT;
				break;
			}
		}
	}//テスト終わり

	
		

	//囲った範囲内の「AKARI」が集まるように
	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use && g_AkariObject[i].setvec == false)
		{
				//地点Aから地点Bの移動距離
				//MovePos=地点B - 地点A;
				MovePos[i].x = /*(SCREEN_WIDTH / 2)*/GetPlayer()->pos.x - g_AkariObject[i].pos.x;
				MovePos[i].y = /*(SCREEN_HEIGHT / 2)*/GetPlayer()->pos.y - g_AkariObject[i].pos.y;
				//何フレームかけて集まるか
				MovePos[i].x /= 60;
				MovePos[i].y /= 60;

				g_AkariObject[i].setvec = true;
		}


		if (g_AkariObject[i].gather&&g_AkariObject[i].use)
		{
			g_AkariObject[i].pos.x += MovePos[i].x;
			g_AkariObject[i].pos.y += MovePos[i].y;

			if (g_AkariObject[i].pos.x < /*(SCREEN_WIDTH / 2)*/GetPlayer()->pos.x + 10 && g_AkariObject[i].pos.x >/*(SCREEN_WIDTH / 2)*/GetPlayer()->pos.x - 10
				&& g_AkariObject[i].pos.y </*(SCREEN_HEIGHT / 2)*/GetPlayer()->pos.y + 10 && g_AkariObject[i].pos.y > /*(SCREEN_HEIGHT / 2)*/GetPlayer()->pos.y - 10)
			{
				MovePos[i].x = 0.0f;
				MovePos[i].y = 0.0f;
			}
		}
	}
}

//=============================================================================							
// 描画処理							
//=============================================================================							
void DrawAkariObject(void)
{
	//ベース座標を取得する
	//D3DXVECTOR2 basePos = GetBase();
	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == true)
		{
			DrawSprite(g_TextureNo,g_AkariObject[i].pos.x,g_AkariObject[i].pos.y, 120.0f, 120.0f,
				1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

}


HanabiAkariObject GetAkariObject(int index)
{
	return g_AkariObject[index];
}

void Akarigather(int index)
{
	g_AkariObject[index].gather = true;
}