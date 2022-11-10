
/*==============================================================================

				   エネミー処理 [enemy.cpp]


------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
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
static int g_TextureNo;

static EnemyObject g_Enemy[NUM_ENEMY];
//=============================================================================			
// 初期化処理			
//=============================================================================			
HRESULT InitEnemy(void)
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/enemy00.png");

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		g_Enemy[i].frame = 0.0f;
		g_Enemy[i].use = false;
		g_Enemy[i].pos = { SCREEN_WIDTH/2 ,SCREEN_HEIGHT/2  };
		g_Enemy[i].speed = 8.0f;
		g_Enemy[i].siz = { 32.0f,32.0f };
	}

	/*テスト*/
	g_Enemy[0].use = true;
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
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (g_Enemy[i].use)
		{
			for (int j = 0; j < AKARI_NUM; j++)
			{
				if (HitCheckBox(g_Enemy[i].pos, g_Enemy[i].siz, GetAkariObject(j).pos, GetAkariObject(j).siz))
				{
					SetAkari(g_Enemy[i].pos);
					g_Enemy[i].use = false;
				}
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
	
}















