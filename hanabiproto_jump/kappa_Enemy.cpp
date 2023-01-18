/*==============================================================================

				   エネミー処理 [enemy.cpp]


------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/

#include "enemy.h"
#include "input.h"
#include "score.h"
#include "stage.h"
#include "kappa_Enemy.h"

//*****************************************************************************			
// マクロ定義			
//*****************************************************************************			
#define KAPPA_SIZE_X (CHIPSIZE_X*3)
#define KAPPA_SIZE_Y (CHIPSIZE_Y*6)



//*****************************************************************************			
// プロトタイプ宣言			
//*****************************************************************************			

//*****************************************************************************			
// グローバル変数			
//*****************************************************************************			
static int g_TexKappa;
static EnemyObject g_Kappa[NUM_ENEMY];

static float g_shrinkAmount[NUM_ENEMY];
static float g_shrinkSize[NUM_ENEMY];
bool KappaFollow;



//=============================================================================			
// 初期化処理			
//=============================================================================			
HRESULT InitKappaEnemy(void)
{
	g_TexKappa = LoadTexture((char*)"data/TEXTURE/youkai_kappa.png");
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		//河童の初期化
		g_Kappa[i].frame = 0.0f;
		g_Kappa[i].use = false;
		/*見て！！*/g_Kappa[i].pos = {2000,SCREEN_HEIGHT/2 };//どこにする？
		g_Kappa[i].speed = ENEMY_WALK_SPEED;
		g_Kappa[i].siz = { KAPPA_SIZE_X,KAPPA_SIZE_Y};
		g_Kappa[i].fall = false;
		g_Kappa[i].sdrop.y = ENEMY_FALL_SPEED;
		g_Kappa[i].Health = ENEMY_HEALTH;
		g_Kappa[i].Attack = 10;

		g_shrinkAmount[i] = 1.0f;
		g_shrinkSize[i] = 1.0f;
		KappaFollow = false;
	}

	//テスト
	g_Kappa[0].use = true;
	//

	return S_OK;
}

//=============================================================================			
// 終了処理			
//=============================================================================			
void UninitKappaEnemy(void)
{

}

//=============================================================================			
// 更新処理			
//=============================================================================			
void UpdateKappaEnemy(void)
{
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		g_Kappa[i].frame++;
		
		if (g_Kappa[i].use)
		{
			//爆散処理テスト
			if (GetKeyboardTrigger(DIK_L))
			{
				g_Kappa[i].Health = 0;
			}
			if (g_Kappa[i].Health <= 0)
			{
				KappaEnemyDeadProcess(i);
			}

			/*見て！！*/	//通常攻撃

			//プレイヤーに近づく
			//④：もし③中にプレイヤーを発見した場合は①に行く
			if (KappaFollow==false)
			{
				//②：プレイヤーが索敵範囲から離れたとき、移動を停止する。
				if (HitCheckCircleSq(GetPlayer()->pos, 1, g_Kappa[i].pos, CHIPSIZE_X * 10))
				{
					KappaFollow = true;
				}
			}
			else
			{
				if (!HitCheckCircleSq(GetPlayer()->pos, 1, g_Kappa[i].pos, CHIPSIZE_X * 15))
				{
					KappaFollow = false;
				}
			}

			if (KappaFollow)
			{
				//①：プレイヤーが索敵範囲に入った時から、常にプレイヤーの半径6マス以内を目掛けて移動する。
				if (GetPlayer()->pos.x + (CHIPSIZE_X * 6) < g_Kappa[i].pos.x)
				{
					g_Kappa[i].pos.x -= g_Kappa[i].speed;
				}
				else if (GetPlayer()->pos.x - (CHIPSIZE_X * 6) > g_Kappa[i].pos.x)
				{
					g_Kappa[i].pos.x += g_Kappa[i].speed;
				}
			}
			else
			{
				//③：もし"②"中に沸きエネミーが倒されているのを感知した場合、沸きエネミーがいたX座標に行き、沸きエネミーを生成する
				if (/*沸きエネミーが倒されている*/GetSPEnemy()->isSPEnemydead)
				{
					if (GetSPEnemy()->pos.x < g_Kappa[i].pos.x)
					{
						g_Kappa[i].pos.x -= g_Kappa[i].speed;
					}
					else if (GetSPEnemy()->pos.x > g_Kappa[i].pos.x)
					{
						g_Kappa[i].pos.x += g_Kappa[i].speed;
					}
				}
			}

			//落下処理
			if (g_Kappa[i].fall == true) {
				g_Kappa[i].drop.y += g_Kappa[i].sdrop.y;
				g_Kappa[i].pos.y += g_Kappa[i].drop.y;
			}

			if (g_Kappa[i].pos.y > SCREEN_HEIGHT) {
				g_Kappa[i].use = false;
			}

			//エネミーと地面の判定
			if (GetStageInfoEnemySITA(g_Kappa[i].pos, Float2(KAPPA_SIZE_X, KAPPA_SIZE_Y)))
			{
				//もし川に当たったら
				if (GetStageInfoEnemySITA(g_Kappa[i].pos, Float2(KAPPA_SIZE_X, KAPPA_SIZE_Y)) == -1)
				{
					g_Kappa[i].fall = false;
					if (KappaFollow)
					{
						if (GetPlayer()->pos.x < g_Kappa[i].pos.x)
						{
							g_Kappa[i].pos.x -= g_Kappa[i].speed * 2;
						}
						else if (GetPlayer()->pos.x > g_Kappa[i].pos.x)
						{
							g_Kappa[i].pos.x += g_Kappa[i].speed * 2;
						}
					}
					else
					{
						if (GetSPEnemy()->pos.x < g_Kappa[i].pos.x)
						{
							g_Kappa[i].pos.x -= g_Kappa[i].speed * 2;
						}
						else if (GetSPEnemy()->pos.x > g_Kappa[i].pos.x)
						{
							g_Kappa[i].pos.x += g_Kappa[i].speed * 2;
						}
					}
					

					if (GetStageInfoEnemySITA({ g_Kappa[i].pos.x,g_Kappa[i].pos.y-CHIPSIZE_Y }, Float2(KAPPA_SIZE_X, KAPPA_SIZE_Y)))
					{
						g_Kappa[i].pos.y -= CHIPSIZE_Y;
					}
					
				}
				else
				{
					g_Kappa[i].drop.y = 0.0f;
					g_Kappa[i].pos.y = GetStageInfoEnemySITA(g_Kappa[i].pos, Float2(KAPPA_SIZE_X, KAPPA_SIZE_Y)) - (KAPPA_SIZE_Y / 2 + CHIPSIZE_Y / 2);
					g_Kappa[i].fall = false;
				}
				
			}
			else
			{
				//ブロックがない＝空中
				g_Kappa[i].fall = true;
			}
		}
	}
}

//=============================================================================			
// 描画処理			
//=============================================================================			
void DrawKappaEnemy(void)
{
	//ベース座標を取得する
	D3DXVECTOR2 basePos = GetBase();

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (g_Kappa[i].use)
		{
			if (g_Kappa[i].Health <= 0)//えねみーのHPが０の時
			{
				DrawSprite(g_TexKappa, basePos.x + g_Kappa[i].pos.x, basePos.y + g_Kappa[i].pos.y *g_shrinkSize[i],
					KAPPA_SIZE_X*g_shrinkAmount[i], KAPPA_SIZE_Y*g_shrinkAmount[i],
					1.0f, 1.0f,
					1.0f, 1.0f);
			}
			else
			{
				DrawSprite(g_TexKappa, basePos.x + g_Kappa[i].pos.x, basePos.y + g_Kappa[i].pos.y,
					KAPPA_SIZE_X, KAPPA_SIZE_Y,
					1.0f, 1.0f,
					1.0f, 1.0f);
			}
		}
	}
}

EnemyObject* GetKappaEnemy()
{
	return g_Kappa;
}

void KappaEnemyDeadProcess(int i)//ＨＰが0になった場合、1.3秒ほどかけて収縮爆散し、周囲にあかりをまき散らす※収縮は横、高さともに0.75倍になる
{
	if (g_Kappa[i].Health <= 0.0f && (int)g_Kappa[i].frame % 3 == 0 && g_Kappa[i].use)//ＨＰが0になった場合かつフレームが３進むたび
	{
		if (g_shrinkAmount[i] < 0.75f)//収縮は横、高さともに0.75倍になる
		{
			if ((int)g_Kappa[i].frame % 60 == 0)
			{
				//セットあかり
				SetAkari(g_Kappa[i].pos, 0);

				g_Kappa[i].use = false;
				g_shrinkAmount[i] = 1.0f;
			}
		}
		else
		{
			g_shrinkAmount[i] -= 0.01f;
			g_shrinkSize[i] += 0.00105f;
		}

	}
}