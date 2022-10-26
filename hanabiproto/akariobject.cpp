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

//*****************************************************************************							
// マクロ定義							
//*****************************************************************************							
#define AKARI_NUM	100
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
		g_AkariObject[i].dir.x = 0.0f;
		g_AkariObject[i].dir.y = 0.0f;
		g_AkariObject[i].pos.x = SCREEN_WIDTH / 2;
		g_AkariObject[i].pos.y = SCREEN_HEIGHT / 2;
		MovePos[i].x = (SCREEN_WIDTH / 2) - g_AkariObject[i].pos.x;
		MovePos[i].y = (SCREEN_HEIGHT / 2) - g_AkariObject[i].pos.y;
		//何フレームかけて集まるか
		MovePos[i].x /= 60;
		MovePos[i].y /= 60;
	}

	//お試し
	for (int i = 0; i < 5; i++)
	{
		g_AkariObject[i].gather = true;
		g_AkariObject[i].pos.x = frand() * SCREEN_WIDTH;
		g_AkariObject[i].pos.y = frand() * SCREEN_HEIGHT;
		g_AkariObject[i].use = true;
		MovePos[i].x = (SCREEN_WIDTH / 2) - g_AkariObject[i].pos.x;
		MovePos[i].y = (SCREEN_HEIGHT / 2) - g_AkariObject[i].pos.y;
		MovePos[i].x /= 60;
		MovePos[i].y /= 60;
	}

	g_U = 0.0f;
	g_V = 0.0f;

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
	//囲った範囲内の「AKARI」が集まるように
	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].gather&&g_AkariObject[i].use)
		{
			if (g_AkariObject[i].pos.x > (SCREEN_WIDTH / 2) + 5 || g_AkariObject[i].pos.x <(SCREEN_WIDTH / 2) - 5
				&& g_AkariObject[i].pos.y >(SCREEN_HEIGHT / 2) + 5 || g_AkariObject[i].pos.y < (SCREEN_HEIGHT / 2) - 5)
			{
					g_AkariObject[i].pos.x += MovePos[i].x;
					g_AkariObject[i].pos.y += MovePos[i].y;
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
	D3DXVECTOR2 basePos = GetBase();
	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == true)
		{
			DrawSprite(g_TextureNo, basePos.x + g_AkariObject[i].pos.x, basePos.y + g_AkariObject[i].pos.y, 120.0f, 120.0f,
				1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

}

Float2 GetAkariObject(void)
{
	//座標取得
	Float2 AkariObject;
	AkariObject.x = g_AkariObject->pos.x;
	AkariObject.y = g_AkariObject->pos.y;
	return Float2(AkariObject);
}
