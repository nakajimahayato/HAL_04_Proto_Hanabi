/*==============================================================================

   エネミー処理 [enemy.cpp]
														 Author : 
														 Date   : 2022/10/23
--------------------------------------------------------------------------------

==============================================================================*/
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void EnemyStateChase(int index);
void EnemyStateRest(int index);
void EnemyStateGoHome(int index);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TextureNo;//タイトル画面用テクスチャの識別子
//static int g_BGMNo;		//タイトル用BGMの識別子
static ENEMY g_Enemy[NUM_ENEMY]; //敵バッファ

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitEnemy(void)
{
	//テクスチャを読み込んで識別子を受け取る
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/spider0916.png");

	//敵バッファの初期化
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		g_Enemy[i].pos = D3DXVECTOR2(0.0f, 0.0f);		//表示座標
		g_Enemy[i].dir = D3DXVECTOR2(0.0f, 0.0f);		//移動方法
		g_Enemy[i].speed = 0.0f;
		g_Enemy[i].state = ES_CHASE;//初期状態は追いかけ状態
		g_Enemy[i].frame = 0.0f;

		g_Enemy[i].use = false;
	}

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void UninitEnemy(void)
{


}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void UpdateEnemy(void)
{
	//敵バッファ全体を走査する
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		//可視フラグがオンの敵だけ座標を更新する
		if (g_Enemy[i].use == true)
		{
			switch (g_Enemy[i].state)
			{
			case ES_CHASE:
				EnemyStateChase(i);
				break;
			case ES_REST:
				EnemyStateRest(i);
				break;
			case ES_RETURN:
				EnemyStateGoHome(i);
				break;
			case ES_NONE:
				break;
			}
			//時間経過
			g_Enemy[i].frame += 1.0f;

			g_Enemy[i].dir = GetPlayer()->pos - g_Enemy[i].pos;
			D3DXVec2Normalize(&g_Enemy[i].dir, &g_Enemy[i].dir);

			//敵の座標更新
			g_Enemy[i].pos += g_Enemy[i].dir * g_Enemy[i].speed;
		}
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void DrawEnemy(void)
{
	//ベース座標を取得する
	D3DXVECTOR2 basePos = GetBase();

	//敵バッファ全体を走査する
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		//可視フラグがオンの弾だけ描画する
		if (g_Enemy[i].use == true)
		{
			float rot;

			//移動方向から回転角度を求める
			rot = atan2f(g_Enemy[i].dir.y, g_Enemy[i].dir.x) - (D3DX_PI / 2);

			DrawSpriteColorRotate(g_TextureNo, basePos.x + g_Enemy[i].pos.x, basePos.y + g_Enemy[i].pos.y,
				32.0f, 32.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				rot);
		}
	}



}
void SetEnemy(D3DXVECTOR2 pos, int muki)
{
	//敵バッファ全体を走査する
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		//可視フラグがオフの敵を探す
		if (g_Enemy[i].use == false)
		{
			g_Enemy[i].startPos = pos;
			g_Enemy[i].pos = g_Enemy[i].startPos;

			switch (muki)
			{
			case 0://上向き
				g_Enemy[i].dir = D3DXVECTOR2(0.0f, -1.0f);
				break;
			case 1://右向き
				g_Enemy[i].dir = D3DXVECTOR2(1.0f, 0.0f);
				break;
			case 2://下向き
				g_Enemy[i].dir = D3DXVECTOR2(0.0f, 1.0f);
				break;
			case 3://左向き
				g_Enemy[i].dir = D3DXVECTOR2(-1.0f, 0.0f);
				break;
			}
			g_Enemy[i].speed = 0.5f;

			//初期状態は待機
			g_Enemy[i].state = ES_REST;

			//可視フラグをオンにする
			g_Enemy[i].use = true;

			//敵を一つセットしたら終了させる
			break;
		}
	}
}