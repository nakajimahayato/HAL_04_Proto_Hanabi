
/*==============================================================================

				   エネミー処理 [enemy.cpp]


------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#include "enemy.h"
#include "object.h"
#include "input.h"

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

static EnemyObject g_Enemy[NUM_ENEMY];

static EnemyObject* g_pEnemy[NUM_ENEMY];//仮置き
static CupEnemy cupE[NUM_CUPENEMY]; //一旦仮置き
static int g_nowEnemyMax;
//=============================================================================			
// 初期化処理			
//=============================================================================			
HRESULT InitEnemy(void)
{

	g_TextureNo = LoadTexture((char*)"data/TEXTURE/enemy00.png");
	g_TexCupE = LoadTexture((char*)"data/TEXTURE/proto_effect_explosion.png");

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		g_Enemy[i].frame = 0.0f;
		g_Enemy[i].use = false;
		g_Enemy[i].pos = { SCREEN_WIDTH/2 ,SCREEN_HEIGHT/2  };
		g_Enemy[i].speed = 8.0f;
		g_Enemy[i].siz = { 32.0f,32.0f };
	}
	//↓このfor必要？上のforと統合？
	for (int i = 0; i < NUM_CUPENEMY; i++)
	{
		cupE[i].frame = 0.0f;
		cupE[i].use = false;
		cupE[i].pos = { SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2 };
		cupE[i].speed = 8.0f;
	}

	/*テスト*/
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
		SetEnemy({ 640,360 }, 0, 0);
	}

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (g_Enemy[i].use)
		{
			for (int j = 0; j < 5; j++)
			{
				//エネミーとあかりの当たり判定処理
				if (HitCheckBox(g_Enemy[i].pos, g_Enemy[i].siz, GetAkariObject(j).pos, GetAkariObject(j).siz))
				{
					SetAkari(g_Enemy[i].pos);
					g_Enemy[i].use = false;
				}


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
			g_pEnemy[i]->pos.x += -1.0f;
			g_pEnemy[i]->frame += 1;
			//１秒に1回明かりを３発飛ばす
			if(g_pEnemy[i]->frame >= 60)
			{
				SetAkari(g_pEnemy[i]->pos, { 0.0f,-1.0f }, 1.5f);
				SetAkari(g_pEnemy[i]->pos, { 0.5f,-1.0f }, 1.5f);
				SetAkari(g_pEnemy[i]->pos, { -0.5f,-1.0f }, 1.5f);
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

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (g_Enemy[i].use)
		{
			DrawSprite(g_TextureNo, basePos.x + g_Enemy[i].pos.x, basePos.y + g_Enemy[i].pos.y,
				80.0f, 80.0f,
				1.0f, 1.0f,
				1.0f, 1.0f);
		}
	}


	for (int i = 0; i < g_nowEnemyMax; i++)
	{
		if (g_pEnemy[i]->use)
		{
			DrawSprite(g_TexCupE, basePos.x + g_pEnemy[i]->pos.x, basePos.y + g_pEnemy[i]->pos.y,
				80.0f, 80.0f,
				1.0f, 1.0f,
				1.0f, 1.0f);
		}
	}
	
}

EnemyObject* GetEnemy()
{
	return g_Enemy;
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
void SetEnemy(Float2 pos, int saidai, int enemytype)
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
		break;
	case 2:
		break;
	default:
		break;
	}
}