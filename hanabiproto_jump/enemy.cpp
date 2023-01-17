/*==============================================================================

				   エネミー処理 [enemy.cpp]


------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#include "enemy.h"
#include "object.h"
#include "input.h"
#include "score.h"
#include "stage.h"



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
static int g_TexCupE;
static int g_TexSPE;
static int g_TexSPED;

static EnemyObject g_Enemy[NUM_ENEMY];

static EnemyObject* g_pEnemy[NUM_ENEMY];//仮置き
static CupEnemy cupE[NUM_CUPENEMY]; //一旦仮置き
static SpawnPointEnemy g_SPEnemy[NUM_ENEMY];
static int g_nowEnemyMax;

static float g_shrinkAmount[NUM_ENEMY];

static float g_shrinkSize[NUM_ENEMY];

static float random[10];

int EnemyMakeframe = 0;



//=============================================================================			
// 初期化処理			
//=============================================================================			
HRESULT InitEnemy(void)
{

	g_TextureNo = LoadTexture((char*)"data/TEXTURE/enemy00.png");
	g_TexCupE = LoadTexture((char*)"data/TEXTURE/ue.png");
	g_TexSPE  = LoadTexture((char*)"data/TEXTURE/HouseProto.png");
	g_TexSPED = LoadTexture((char*)"data/TEXTURE/HouseBrokedProto.png");
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		g_Enemy[i].frame = 0.0f;
		g_Enemy[i].use = false;
		g_Enemy[i].pos = { SCREEN_WIDTH/2 ,SCREEN_HEIGHT/2  };
		g_Enemy[i].speed = ENEMY_WALK_SPEED;
		g_Enemy[i].siz = { 32.0f,32.0f };
		g_Enemy[i].fall = false;
		g_Enemy[i].sdrop.y = ENEMY_FALL_SPEED;
		g_Enemy[i].Health =ENEMY_HEALTH;	//仮置き

		g_shrinkAmount[i] = 1.0f;
		g_shrinkSize[i] = 1.0f;
	}
	//↓このfor必要？上のforと統合？
	for (int i = 0; i < NUM_CUPENEMY; i++)
	{
		cupE[i].frame = 0.0f;
		cupE[i].use = false;
		cupE[i].pos = { SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2 };
		cupE[i].speed = 8.0f;
	}

	//2023/1/17
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		g_SPEnemy[i].frame = 0.0f;
		g_SPEnemy[i].scoreframe = 0.0f;
		g_SPEnemy[i].use = false;
		g_SPEnemy[i].color = { 1.0f,1.0f,1.0f,1.0f };
		g_SPEnemy[i].pos = { SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2 };
		g_SPEnemy[i].siz = { 32.0f * 8,32.0f * 9 };
		g_SPEnemy[i].Health = 500.0f;
		g_SPEnemy[i].isSPEnemydead = false;
		//色づけ
		{
			if (rand() % 2 == 0)
			{
				g_SPEnemy[i].color = { 0.5f,0.5f,1.0f,1.0f };
				g_SPEnemy[i].isColorBlue = true;
			}
			else if(rand() % 2 == 1)
			{
				g_SPEnemy[i].color = { 2.0f,0.5f,0.5f,1.0f };
				g_SPEnemy[i].isColorRed = true;
			}
			else
			{
				g_SPEnemy[i].color = { 0.5f,1.0f,0.5f,1.0f };
				g_SPEnemy[i].isColorGreen = true;
			}
			//float RGB[3];
			//int saidai = 0;
			//for (int j = 0; j < 3; j++)
			//{
			//	RGB[j] = frand();
			//	if (RGB[saidai] <= RGB[j])
			//		saidai = j;
			//}
			//RGB[saidai] = 1.0f;
			//g_SPEnemy[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
		}
	}
	g_SPEnemy[0].use = true;


	//テスト
	g_Enemy[0].use = true;
	cupE[0].use = true;
	return S_OK;
}

//=============================================================================			
// 終了処理			
//=============================================================================			
void UninitEnemy(void)
{

}

//=============================================================================			
// 更新処理			
//=============================================================================			
void UpdateEnemy(void)
{
	if (GetKeyboardTrigger(DIK_F))
	{
		SetEnemy({ SCREEN_WIDTH / 2, 250 }, 0, 0, 1);
	}

	//エネミー生成
	if (GetKeyboardTrigger(DIK_K))
	{
		SetEnemy({ SCREEN_WIDTH / 2, 250 }, 0, 1, 1);
	}

	EnemyMakeframe++;

	if ((EnemyMakeframe % 70) == 0)
		SetEnemy({ SCREEN_WIDTH / 2, 250 }, 0, 1, -1);

	//2023/1/17
	//テスト

	g_SPEnemy[0].pos = {1900,830};
	if (GetKeyboardTrigger(DIK_Y))
	{
		g_SPEnemy[0].Health -= 100.0f;
	}
	if (GetKeyboardTrigger(DIK_B))
	{
		PlusEnemyScore(100);
	}
	if (GetKeyboardTrigger(DIK_N))
	{
		PlusPlayerScore(100);
	}

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (g_SPEnemy[i].use) {
			g_SPEnemy[i].frame++;
			g_SPEnemy[i].scoreframe++;
			if (g_SPEnemy[i].frame >= 300)
			{
				g_SPEnemy[i].Action();
				g_SPEnemy[i].frame = 0.0f;
			}
			if (g_SPEnemy[i].scoreframe >= 600)
			{
				PlusEnemyScore(2000);
				g_SPEnemy[i].scoreframe = 0.0f;
			}

			if (g_SPEnemy[i].Health <= 0.0f)
			{
				g_SPEnemy[i].use = false;
				g_SPEnemy[i].isSPEnemydead = true;
			}

			if (g_SPEnemy[i].isSPEnemydead)
			{
				for (int i = 0; i < 1; i++)
				{
					if (g_SPEnemy[i].isColorBlue == true)
					{
						SetHouseAkari(g_SPEnemy[i].pos, 0);
					}
					if (g_SPEnemy[i].isColorRed == true)
					{
						SetHouseAkari(g_SPEnemy[i].pos, 1);
					}
					if (g_SPEnemy[i].isColorGreen == true)
					{
						SetHouseAkari(g_SPEnemy[i].pos, 2);
					}
					/*SetHouseAkari(g_SPEnemy[i].pos, 0);*/
					PlusPlayerScore(3000);
					//g_SPEnemy[i].isSPEnemydead = false;
				}
			}
		}
	}


	for (int i = 0; i < NUM_ENEMY; i++)
	{
		g_Enemy[i].frame++;
		

		if (g_Enemy[i].use)
		{
			//for (int j = 0; j < 5; j++)
			//{
			//	//エネミーとあかりの当たり判定処理
			//	if (HitCheckBox(g_Enemy[i].pos, g_Enemy[i].siz, GetAkariObject(j).pos, GetAkariObject(j).siz))
			//	{
			//		PlusPlayerScore(100);
			//		SetAkari(g_Enemy[i].pos);
			//		g_Enemy[i].use = false;
			//	}
			//}

			//爆散処理テスト
			if (GetKeyboardTrigger(DIK_L))
			{
				g_Enemy[i].Health = 0;
			}
			if (g_Enemy[i].Health <= 0)
			{
				EnemyDeadProcess(i);
			}

			//右か左に蟹歩き
			g_Enemy[i].pos.x += g_Enemy[i].speed * g_Enemy[i].directionX;

			//落下処理
			if (g_Enemy[i].fall == true) {
				g_Enemy[i].drop.y += g_Enemy[i].sdrop.y;
				g_Enemy[i].pos.y += g_Enemy[i].drop.y;
			}

			if (g_Enemy[i].pos.y > SCREEN_HEIGHT) {
				g_Enemy[i].use = false;
			}

			//エネミーと地面の判定
			if (GetStageInfoEnemySITA(g_Enemy[i].pos, Float2(ENEMY1_SIZEX, ENEMY1_SIZEY)))
			{
				//もし川に当たったら
				if (GetStageInfoEnemySITA(g_Enemy[i].pos, Float2(ENEMY1_SIZEX, ENEMY1_SIZEY)) == -1) {
					g_Enemy[i].use = false;
				}

				////もし旗に当たったら
				//if (GetStageInfoSITA(g_Player.pos) == -2)
				//{
				//	SetScene(SCENE_CRESULT);
				//}

				//下にブロックがあれば座標をそのブロックの上に調整する
				g_Enemy[i].drop.y = 0.0f;
				g_Enemy[i].pos.y = GetStageInfoEnemySITA(g_Enemy[i].pos, Float2(ENEMY1_SIZEX, ENEMY1_SIZEY)) - (ENEMY1_SIZEY / 2 + CHIPSIZE_Y / 2);
				g_Enemy[i].fall = false;
			}
			else
			{
				//ブロックがない＝空中
				g_Enemy[i].fall = true;
			}
		}
		
	}

	for (int i = 0; i < NUM_CUPENEMY; i++)
	{
		if (cupE[i].use)
		{
			cupE[i].frame += 1;
			for (int j = 0; j < 5; j++)
			{
				////エネミーとあかりの当たり判定処理
				//if (HitCheckBox(g_Enemy[i].pos, g_Enemy[i].siz, GetAkariObject(j).pos, GetAkariObject(j).siz))
				//{
				//	SetAkari(g_Enemy[i].pos);
				//	g_Enemy[i].use = false;
				//}

				//6秒間に1回手足茶碗がアクションを起こす
				if (cupE[i].frame >= 360)
				{
					cupE[i].Action();
					cupE[i].frame = 0;
				}
			}
		}
	}

	//描画されてる手足茶碗処理
	for (int i = 0; i < g_nowEnemyMax; i++)
	{
		if (g_pEnemy[i]->use == true)
		{
			//左に動かしてframeを1足す
			//g_pEnemy[i]->pos.x += -1.0f;
			g_pEnemy[i]->frame += 1;

			//１秒に1回明かりを5発飛ばす

			if(g_pEnemy[i]->frame >= 60)
			{
				SetCupAkari(g_pEnemy[i]->pos, 0, 0, 30, 150, 5, 3.0f);
				//for (int a = 0; a < 10; a++)
				//{
				//	random[a * 2] = (frand() / frand() - 1);
				//	random[a * 2 + 1] = frand();

				//	while (random[a * 2] > 1)
				//	{
				//		random[a * 2] = (frand() / frand() - 1);
				//	}
				//	while (random[a * 2 + 1] > 1)
				//	{
				//		random[a * 2 + 1] = frand();
				//	}

				//	SetAkari(g_pEnemy[i]->pos, { random[a * 2] + 0.2f,-random[a * 2 + 1] }, 1.5f);
				//}
				
				g_pEnemy[i]->frame = 0;
			}
		}
	}
}

//=============================================================================			
// 描画処理			
//=============================================================================			
void DrawEnemy(void)
{
	//ベース座標を取得する
	D3DXVECTOR2 basePos = GetBase();

	//2023//1/17
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (g_SPEnemy[i].use) {
			DrawSpriteColor(g_TexSPE, basePos.x + g_SPEnemy[i].pos.x, basePos.y + g_SPEnemy[i].pos.y,
				32.0f * 8, 32.0f * 9,
				1.0f, 1.0f,
				1.0f, 1.0f, g_SPEnemy[i].color);
		}

		if (g_SPEnemy[i].isSPEnemydead)
		{
			DrawSpriteColor(g_TexSPED, basePos.x + g_SPEnemy[i].pos.x, basePos.y + g_SPEnemy[i].pos.y,
				32.0f * 8, 32.0f * 9,
				1.0f, 1.0f,
				1.0f, 1.0f, g_SPEnemy[i].color);
		}

			//DrawSprite(g_TexSPE, basePos.x + g_SPEnemy[i].pos.x, basePos.y + g_SPEnemy[i].pos.y,
			//	32.0f * 8, 32.0f * 9,
			//	1.0f, 1.0f,
			//	1.0f, 1.0f);


		
	
	}

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (g_Enemy[i].use)
		{
			if (g_Enemy[i].Health <= 0)//えねみーのHPが０の時
			{
				DrawSprite(g_TextureNo, basePos.x + g_Enemy[i].pos.x, basePos.y + g_Enemy[i].pos.y *g_shrinkSize[i],
					ENEMY1_SIZEX*g_shrinkAmount[i], ENEMY1_SIZEY*g_shrinkAmount[i],
					1.0f, 1.0f,
					1.0f, 1.0f);
			}
			else
			{
				DrawSprite(g_TextureNo, basePos.x + g_Enemy[i].pos.x, basePos.y + g_Enemy[i].pos.y,
					ENEMY1_SIZEX, ENEMY1_SIZEY,
					1.0f, 1.0f,
					1.0f, 1.0f);
			}
		}
	}


	for (int i = 0; i < g_nowEnemyMax; i++)
	{
		if (g_pEnemy[i]->use)
		{
			DrawSprite(g_TexCupE, basePos.x + g_pEnemy[i]->pos.x, basePos.y + g_pEnemy[i]->pos.y,
				ENEMY2_SIZEX, ENEMY2_SIZEY,
				1.0f, 1.0f,
				1.0f, 1.0f);
		}
	}
	
}

EnemyObject* GetEnemy()

{
	return g_Enemy;
}

EnemyObject** GetCupEnemy()
{
	return g_pEnemy;
}

void CupEnemy::Action()
{
	SetAkari(pos);
}
//----------------------------------
// エネミーのセット処理
//----------------------------------
//0なら
//1なら
//2なら...(未定)
//向きがプラスで→
//マイナスで←
void SetEnemy(Float2 pos, int saidai, int enemytype, int muki)
{
	switch (enemytype)
	{
	case 0:
		g_pEnemy[g_nowEnemyMax] = new CupEnemy;
		g_pEnemy[g_nowEnemyMax]->use = true;
		g_pEnemy[g_nowEnemyMax]->pos = pos;
		g_pEnemy[g_nowEnemyMax]->vec.x = 0.0f;
		g_pEnemy[g_nowEnemyMax]->vec.y = 0.0f;
		g_pEnemy[g_nowEnemyMax]->siz = { 32.0f,32.0f };
		g_pEnemy[g_nowEnemyMax]->frame = 0.0f;

		g_nowEnemyMax += 1;
		break;
	case 1:
		for (int i = 0; i < NUM_ENEMY; i++) {
			if (g_Enemy[i].use == false) {
				g_Enemy[i].use = true;
				g_Enemy[i].pos = pos;
				if (muki > 0) {
					g_Enemy[i].directionX = 1;
				}
				else {
					g_Enemy[i].directionX = -1;
				}
				break;
			}
		}
		break;
	case 2:
		break;
	default:
		break;
	}
}

void EnemyDeadProcess(int i)//ＨＰが0になった場合、1.3秒ほどかけて収縮爆散し、周囲にあかりをまき散らす※収縮は横、高さともに0.75倍になる
{
	if (g_Enemy[i].Health <= 0.0f && (int)g_Enemy[i].frame % 3==0 && g_Enemy[i].use)//ＨＰが0になった場合かつフレームが３進むたび
	{
		if (g_shrinkAmount[i] < 0.75f)//収縮は横、高さともに0.75倍になる
		{
			if ((int)g_Enemy[i].frame % 240 == 0)
			{
				//セットあかり
				SetAkari(g_Enemy[i].pos, 0);

				g_Enemy[i].use = false;
				g_shrinkAmount[i] = 1.0f;
			}
		}
		else
		{
			g_shrinkAmount[i] -= 0.01f;
			g_shrinkSize[i] += 0.00075f;
		}
		
	}
}

//2023/1/17
void SpawnPointEnemy::Action()
{
	for (int i = 0; i < NUM_ENEMY; i++) 
	{
		if (g_SPEnemy[i].use)
		{
			if (!g_SPEnemy[i].isSPEnemydead)
			{
				SetEnemy({ g_SPEnemy[i].pos.x,g_SPEnemy[i].pos.y + 100 }, 0, 1, 0);
			}
		}
	}
}