/*==============================================================================

   攻撃花火の処理 [attackhanabi.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "object.h"
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_HANABI 100

//弾のデータを管理する構造体
struct AtHANABI
{
	D3DXVECTOR2 pos;	//表示座標
	D3DXVECTOR2 dir;	//移動方向
	float       speed;	//移動速度
	float		frame;	//持続時間

	int			use;	//可視フラグ
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void HitHanabi(bool isHit);
void CreateHanabi(Float2 plpos, Float2 cspos);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
static GameObject g_Hanabi0bj;
static EnemyObject g_Enemy0bj;

static GameObject g_Objects[256];
static PLAYER g_Player;	//プレイヤー用

static int g_AtHanabi;	//攻撃花火用のテクスチャの識別子
static AtHANABI g_HANABI[NUM_HANABI];	//弾バッファ
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitAtHanabi(void)
{
	//------------仮--------------------

	//テクスチャを読み込んで識別子を受け取る
	g_AtHanabi = LoadTexture((char*)"data/TEXTURE/bullet00.png");


	//花火バッファの初期化
	for (int i = 0; i < NUM_HANABI; i++)
	{
		g_HANABI[i].pos = D3DXVECTOR2(0.0f, 0.0f);	//表示座標
		g_HANABI[i].dir = D3DXVECTOR2(0.0f, 0.0f);	//移動方向
		g_HANABI[i].speed = 0.0f;					//移動速度

		g_HANABI[i].use = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitAtHanabi(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateAtHanabi(void)
{
	//------------仮--------------------

	//花火バッファ全体を走査する
	for (int i = 0; i < NUM_HANABI; i++)
	{
		//可視フラグがオンの花火だけ座標を更新する
		if (g_HANABI[i].use == true)
		{
			//花火の座標更新
			g_HANABI[i].pos += g_HANABI[i].dir * g_HANABI[i].speed;

			g_HANABI[i].frame += 1.0f;

			//180フレーム経過したら
			if (g_HANABI[i].frame > 180.0f)
			{
				//花火を画面から削除する
				g_HANABI[i].use = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawAtHanabi(void)
{

	//------------仮--------------------

	//ベース座標を取得する
	D3DXVECTOR2 basePos = GetBase();


	//花火バッファ全体を走査する
	for (int i = 0; i < NUM_HANABI; i++)
	{
		//可視フラグがオンの花火だけ描画する
		if (g_HANABI[i].use == true)
		{
			float rot;

			//移動方向から回転角度を求める
			rot = atan2f(g_HANABI[i].dir.y, g_HANABI[i].dir.x) + (D3DX_PI / 2);

			DrawSpriteColorRotate(g_AtHanabi, basePos.x + g_HANABI[i].pos.x, basePos.y + g_HANABI[i].pos.y,
				32.0f, 32.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				rot);
		}
	}
}


//=============================================================================
// 攻撃花火の移動処理
//=============================================================================
void MoveHanabi(void)
{


}
void MoveHanabiAI(void)
{

}

//=============================================================================
// 攻撃花火の当たり判定処理
//=============================================================================
void HitHanabi(bool isHit)
{
	//if (g_Hanabi0bj.pos.x == g_Enemy0bj.pos.x || g_Hanabi0bj.pos.y == g_Enemy0bj.pos.y)
	//{
	//	isHit = true;
	//}
	
}
void CreateHanabi(Float2 plpos, Float2 cspos)
{
	g_Player.pos = plpos;
	g_Player.cspos = cspos;


	//------------仮--------------------

	//花火バッファ全体を走査する
	for (int i = 0; i < NUM_HANABI; i++)
	{
		//可視フラグがオフの花火を探す
		if (g_HANABI[i].use == false)
		{
			g_HANABI[i].pos = plpos;

			switch ()
			{
			case 0://上向き
				g_HANABI[i].dir = D3DXVECTOR2(0.0f, -1.0f);
				break;
			case 1://右向き
				g_HANABI[i].dir = D3DXVECTOR2(1.0f, 0.0f);
				break;
			case 2://下向き
				g_HANABI[i].dir = D3DXVECTOR2(0.0f, 1.0f);
				break;
			case 3://左向き
				g_HANABI[i].dir = D3DXVECTOR2(-1.0f, 0.0f);
				break;
			}

			g_HANABI[i].speed = 6.0f;

			//可視フラグをオンにする
			g_HANABI[i].use = true;

			//持続時間をリセットする
			g_HANABI[i].frame = 0.0f;

			//花火を一つセットしたら終了させる
			break;
		}
	}
}