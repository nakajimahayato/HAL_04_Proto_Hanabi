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
		g_AkariObject[i].pos.x = SCREEN_WIDTH / 2;
		g_AkariObject[i].pos.y = SCREEN_HEIGHT / 2;
	}

	//お試し
	/*for (int i = 0; i < 5; i++)
	{
		g_AkariObject[i].pos.x = frand() * SCREEN_WIDTH;
		g_AkariObject[i].pos.y = frand() * SCREEN_HEIGHT;
		g_AkariObject[i].use = true;
	}*/
	

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
			g_AkariObject[i].pos.x = SCREEN_WIDTH / 2;
			g_AkariObject[i].pos.y = SCREEN_HEIGHT / 2;
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

//花火の「AKARI」状態：集まり状態
void AKARIGather(int index)
{
	//現在の「AKARI」と集まる位置との位置関係から移動方向を更新
	g_AkariObject[index].dir = /*花火の爆発位置*/->pos - g_AkariObject[index].pos;
	D3DXVec2Normalize(&g_AkariObject[index].dir, &g_AkariObject[index].dir);

	//敵の座標更新
	g_AkariObject[index].pos += g_AkariObject[index].dir * 0.8f;
}