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

static HanabiAkariObject g_AkariObject[AKARI_NUM];

static float g_U, g_V;

Float2 MovePos[AKARI_NUM];

Float2 Ppos;

bool g_composition;
//=============================================================================							
// 初期化処理							
//=============================================================================							
HRESULT InitAkariObject(void)
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/proto_effect_akari.png");

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
		g_AkariObject[i].frame = 0;
		g_AkariObject[i].color = { 1.0f,1.0f,1.0f,1.0f };
		g_AkariObject[i].siz = { 32.0f,32.0f };
		g_AkariObject[i].drop.x = 0.0f;
		g_AkariObject[i].drop.y = 0.0f;
		g_AkariObject[i].sdrop.x = 0.0f;
		g_AkariObject[i].sdrop.y = 0.0f;
		g_AkariObject[i].vec.x = 0.0f;
		g_AkariObject[i].vec.y = 0.0f;
		g_AkariObject[i].speed = 1.0f;

	}

	////お試し
	//for (int i = 0; i < 5; i++)
	//{
	//	g_AkariObject[i].gather = true;
	//	g_AkariObject[i].pos.x = frand() * SCREEN_WIDTH;
	//	g_AkariObject[i].pos.y = frand() * SCREEN_HEIGHT;
	//	g_AkariObject[i].use = true;
	//}

	for (int i = 0; i < AKARI_NUM; i++)
	{
		MovePos[i] = { 0.0f,0.0f };
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

	if (GetKeyboardTrigger(DIK_G))
	{
		SetAkari(GetPlayer()->pos, { 1.0f,-1.0f },1.5f);
	}//テスト終わり



	//囲った範囲内の「AKARI」が集まるように
	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].gather && g_AkariObject[i].use == true && g_AkariObject[i].setvec == false && Ppos.x != GetPlayer()->pos.x && Ppos.y != GetPlayer()->pos.y)
		{
			//地点Aから地点Bの移動距離
			//MovePos=地点B - 地点A;
			MovePos[i] = Centergather(GetPlayer()->pos, GetPlayer()->pos, GetPlayer()->pos, GetPlayer()->pos) - g_AkariObject[i].pos;
			//MovePos[i].y = GetPlayer()->pos.y - g_AkariObject[i].pos.y;
			//何フレームかけて集まるか
			MovePos[i].x /= (60 / (g_AkariObject[i].frame + 1 * 5));
			MovePos[i].y /= (60 / (g_AkariObject[i].frame + 1 * 5));

			//g_AkariObject[i].setvec = true;
		}


		if (g_AkariObject[i].gather && g_AkariObject[i].use)
		{
			g_AkariObject[i].pos.x += MovePos[i].x;
			g_AkariObject[i].pos.y += MovePos[i].y;

			if (g_AkariObject[i].pos.x < /*(SCREEN_WIDTH / 2)*/GetPlayer()->pos.x + 19 && g_AkariObject[i].pos.x >/*(SCREEN_WIDTH / 2)*/GetPlayer()->pos.x - 19
				&& g_AkariObject[i].pos.y </*(SCREEN_HEIGHT / 2)*/GetPlayer()->pos.y + 19 && g_AkariObject[i].pos.y > /*(SCREEN_HEIGHT / 2)*/GetPlayer()->pos.y - 19)
			{
				MovePos[i].x = 0.0f;
				MovePos[i].y = 0.0f;
				g_AkariObject[i].frame += 1;


				//合成後消滅ーーー
				if (g_AkariObject[i].frame > 40)
				{
					for (int j = 0; j < AKARI_NUM; j++)
					{
						if (g_AkariObject[j].gather == true && g_AkariObject[j].use == true)
						{
							g_AkariObject[j].use = false;
							g_AkariObject[j].frame = 0;
							plus_hissatuwaza(5);
						}
					}
				}
			}
		}
		else if (g_AkariObject[i].use == true)
		{
			if (g_AkariObject[i].hitground == true) {
				g_AkariObject[i].vec.y = 0;
			}
			else
			{
				g_AkariObject[i].pos.y += g_AkariObject[i].vec.y;
				g_AkariObject[i].pos.y += MovePos[i].y * g_AkariObject[i].speed * 3;
			}
			g_AkariObject[i].pos.x += MovePos[i].x * g_AkariObject[i].speed * 3;
			g_AkariObject[i].frame += 1;
			//落ちる速さ
			g_AkariObject[i].drop.y = 0.01f;
			//加速度
			g_AkariObject[i].sdrop.y = 0.03f;
			//弾が飛ぶ幅
			MovePos[i].x /= 1.005;
			//特定のフレーム後に重力発動
			if (g_AkariObject[i].frame >= 20)
			{
				g_AkariObject[i].drop.y += g_AkariObject[i].sdrop.y;
				g_AkariObject[i].vec.y += g_AkariObject[i].drop.y;
			}
			//地面に残留
			if (g_AkariObject[i].pos.y >= 360)
			{
				g_AkariObject[i].hitground = true;
				g_AkariObject[i].pos.y = 360;
			}
			//合成できず消滅ーーー
			if(g_AkariObject[i].hitground == true && g_AkariObject[i].frame == 400)
			{
				g_AkariObject[i].use = false;
				g_AkariObject[i].frame = 0;
				g_AkariObject[i].hitground = false;
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
			DrawSpriteColor(g_TextureNo, basePos.x + g_AkariObject[i].pos.x, basePos.y + g_AkariObject[i].pos.y, 60.0f, 60.0f,
				1.0f, 1.0f, 1.0f, 1.0f, g_AkariObject[i].color);
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
	g_AkariObject[index].frame = 0;
}

//明かりの位置をセット
void SetAkari(Float2 pos)
{
	int create_akari = 4;
	Float2 akarivec[4] =
	{
		{1.0f,0.0f},	//1
		{-1.0f,0.0f},	//2
		{0.0f,1.0f},	//3
		{0.0f,-1.0f}	//4
	};

	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			MovePos[i] = akarivec[create_akari - 1];
			//色づけ
			{
				float RGB[3];
				int saidai = 0;
				for (int j = 0; j < 3; j++)
				{
					RGB[j] = frand();
					if (RGB[saidai] <= RGB[j])
						saidai = j;
				}
				RGB[saidai] = 1.0f;
				g_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
			}

			create_akari -= 1;
			if (create_akari <= 0)
			{
				break;
			}
		}
	}
}

//明かりの位置と最大個数をセット
void SetAkari(Float2 pos, int saidai)
{
	int create_akari = 32;
	Float2 akarivec[32] =
	{
		{1.0f,0.0f},	//1
		{0.2f,0.7f},	//2
		{0.3f,0.8f},	//3
		{0.7f,0.2f},	//4
		{0.5f,0.5f},	//5
		{0.1f,0.6f},	//6
		{0.8f,0.3f},	//7
		{0.4f,0.9f},	//8
		{-1.0f,0.0f},	//9
		{-0.2f,0.7f},	//10
		{-0.3f,0.8f},	//11
		{-0.7f,0.2f},	//12
		{-0.5f,0.5f},	//13
		{-0.4f,0.9f},	//14
		{-0.8f,0.3f},	//15
		{-0.9f,0.4f},	//16
		{0.0f,1.0f},	//17
		{-0.2f,-0.7f},	//18
		{-0.3f,-0.8f},	//19
		{-0.7f,-0.2f},	//20
		{-0.5f,-0.5f},	//21
		{-0.4f,-0.9f},	//22
		{-0.8f,-0.3f},	//23
		{-0.4f,-0.9f},	//24
		{0.0f,-1.0f},	//25
		{0.2f,-0.7f},	//26
		{0.3f,-0.8f},	//27
		{0.7f,-0.2f},	//28
		{0.5f,-0.5f},	//29
		{0.4f,-0.9f},	//30
		{0.8f,-0.3f},	//31
		{0.9f,-0.4f}	//32
	};

	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			g_AkariObject[i].vec.y = 0.0f;
			g_AkariObject[i].hitground = false;
			MovePos[i] = akarivec[create_akari - 1];
			//色づけ
			{
				float RGB[3];
				for (int j = 0; j < 3; j++)
				{
					RGB[j] = frand();
				}
				RGB[saidai] = 1.0f;
				g_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
			}

			create_akari -= 1;
			if (create_akari <= 0)
			{
				break;
			}
		}
	}
}

//ダメージタイプが0ならプレイヤーにダメージ
//1ならエネミーにダメージ
//2なら両方
void SetAkari(Float2 pos, int saidai,int damagetype)
{
	int create_akari = 32;
	Float2 akarivec[32] =
	{
		{1.0f,0.0f},	//1
		{0.2f,0.7f},	//2
		{0.3f,0.8f},	//3
		{0.7f,0.2f},	//4
		{0.5f,0.5f},	//5
		{0.1f,0.6f},	//6
		{0.8f,0.3f},	//7
		{0.4f,0.9f},	//8
		{-1.0f,0.0f},	//9
		{-0.2f,0.7f},	//10
		{-0.3f,0.8f},	//11
		{-0.7f,0.2f},	//12
		{-0.5f,0.5f},	//13
		{-0.4f,0.9f},	//14
		{-0.8f,0.3f},	//15
		{-0.9f,0.4f},	//16
		{0.0f,1.0f},	//17
		{-0.2f,-0.7f},	//18
		{-0.3f,-0.8f},	//19
		{-0.7f,-0.2f},	//20
		{-0.5f,-0.5f},	//21
		{-0.4f,-0.9f},	//22
		{-0.8f,-0.3f},	//23
		{-0.4f,-0.9f},	//24
		{0.0f,-1.0f},	//25
		{0.2f,-0.7f},	//26
		{0.3f,-0.8f},	//27
		{0.7f,-0.2f},	//28
		{0.5f,-0.5f},	//29
		{0.4f,-0.9f},	//30
		{0.8f,-0.3f},	//31
		{0.9f,-0.4f}	//32
	};

	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			switch (damagetype)
			{
			case 0:
				g_AkariObject[i].damageplayerflug = true;
				g_AkariObject[i].damageenemyflug = false;
				break;
			case 1:
				g_AkariObject[i].damageplayerflug = false;
				g_AkariObject[i].damageenemyflug = true;
				break;
			case 2:
				g_AkariObject[i].damageplayerflug = true;
				g_AkariObject[i].damageenemyflug = true;
				break;
			default:
				break;
			}
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			g_AkariObject[i].vec.y = 0.0f;
			g_AkariObject[i].hitground = false;
			MovePos[i] = akarivec[create_akari - 1];
			//色づけ
			{
				float RGB[3];
				for (int j = 0; j < 3; j++)
				{
					RGB[j] = frand();
				}
				RGB[saidai] = 1.0f;
				g_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
			}

			create_akari -= 1;
			if (create_akari <= 0)
			{
				break;
			}
		}
	}
}

void SetCupAkari(Float2 pos, int saidai, int damagetype, Float2 vec, float angle)
{

	D3DXVECTOR2 vVEC = GetPlayer()->pos - GetEnemy()->pos;
	D3DXVec2Normalize(&vVEC, &vVEC);

	Float2 randomvec;
	float  anglef = ((int)angle % 181) / 180;

	randomvec.x = frand();
	randomvec.y = frand();
	//vecとramdomvec(angle)との位置関係とベクトル途で内積を計算する
	D3DXVec2Dot(&vec,&randomvec);

	if (D3DXVec2Dot(&vec, &randomvec) <= anglef)
	{
		int create_akari = 15;
		Float2 akarivec[15] =
		{
			{-0.2f,-0.7f},	//1
			{-0.3f,-0.8f},	//2
			{-0.7f,-0.2f},	//3
			{-0.5f,-0.5f},	//4
			{-0.4f,-0.9f},	//5
			{-0.8f,-0.3f},	//6
			{-0.4f,-0.9f},	//7
			{0.0f,-1.0f},	//8
			{0.2f,-0.7f},	//9
			{0.3f,-0.8f},	//10
			{0.7f,-0.2f},	//11
			{0.5f,-0.5f},	//12
			{0.4f,-0.9f},	//13
			{0.8f,-0.3f},	//14
			{0.9f,-0.4f}	//15
		};

		for (int i = 0; i < AKARI_NUM; i++)
		{
			if (g_AkariObject[i].use == false)
			{
				switch (damagetype)
				{
				case 0:
					g_AkariObject[i].damageplayerflug = true;
					g_AkariObject[i].damageenemyflug = false;
					break;
				case 1:
					g_AkariObject[i].damageplayerflug = false;
					g_AkariObject[i].damageenemyflug = true;
					break;
				case 2:
					g_AkariObject[i].damageplayerflug = true;
					g_AkariObject[i].damageenemyflug = true;
					break;
				default:
					break;
				}
				g_AkariObject[i].use = true;
				g_AkariObject[i].pos = pos;
				g_AkariObject[i].setvec = false;
				g_AkariObject[i].gather = false;
				g_AkariObject[i].vec.y = 0.0f;
				g_AkariObject[i].hitground = false;
				MovePos[i] = akarivec[create_akari - 1];
				//色づけ
				{
					float RGB[3];
					for (int j = 0; j < 3; j++)
					{
						RGB[j] = frand();
					}
					RGB[saidai] = 1.0f;
					g_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
				}

				create_akari -= 1;
				if (create_akari <= 0)
				{
					break;
				}
			}
		}


	}
}

void SetAkari(Float2 pos, Float2 vec,float speed)
{
	int create_akari = 1;
	Float2 akarivec[1] =
	{
		{vec.x,vec.y},
	};


	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			g_AkariObject[i].speed = speed;
			MovePos[i] = akarivec[create_akari - 1];
			//色づけ
			{
				float RGB[3];
				int saidai = 0;
				for (int j = 0; j < 3; j++)
				{
					RGB[j] = frand();
					if (RGB[saidai] <= RGB[j])
						saidai = j;
				}
				RGB[saidai] = 1.0f;
				g_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
			}

			create_akari -= 1;
			if (create_akari <= 0)
			{
				break;
			}
		}
	}
}

Float2 Centergather(Float2 up, Float2 down, Float2 left, Float2 right)
{
	Float2 cp;
	float y = (up.y + down.y) / 2;
	float x = (left.x + right.x) / 2;
	
	cp.y = y;
	cp.x = x;

	return cp;
}