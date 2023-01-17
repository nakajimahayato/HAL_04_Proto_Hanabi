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
	}

	if (GetKeyboardTrigger(DIK_G))
	{
		SetAkari(GetPlayer()->pos, { 1.0f,-1.0f }, 1.5f);
	}
	

	//カップあかりテスト
	if (GetKeyboardTrigger(DIK_C))
	{
		SetCupAkari(GetPlayer()->pos, 1, 1, 30, 60, 10, 5.0f);
	}



	//テスト終わり



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


			//もし明かりの中心が雨のマップチップに当たったらフレーム加速
			if (GetStageInfoRain(g_AkariObject[i].pos)){
				g_AkariObject[i].frame = 500;
			}
				

			//落ちる速さ
			g_AkariObject[i].drop.y = 0.01f;
			//加速度
			g_AkariObject[i].sdrop.y = 0.03f;
			//弾が飛ぶ幅
			MovePos[i].x /= 1.005f;
			//特定のフレーム後に重力発動
			if (g_AkariObject[i].frame >= 20)
			{
				g_AkariObject[i].drop.y += g_AkariObject[i].sdrop.y;
				g_AkariObject[i].vec.y += g_AkariObject[i].drop.y;
			}
			//地面に残留
/*
			if (g_AkariObject[i].pos.y >= 360)
			{
				g_AkariObject[i].hitground = true;
				g_AkariObject[i].pos.y = 360;
			}
*/
			//合成できず消滅ーーー
			if (/*g_AkariObject[i].hitground == true &&*/ g_AkariObject[i].frame >= 400)
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
void SetAkari(Float2 pos, int saidai, int damagetype)
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

//引数:カップ明かりの座標,色の種類 (赤:0.緑:1.青:2),攻撃の種類(プレイヤーダメージ0.エネミーダメージ1,両方2),
//範囲選択開始角度,範囲選択終了地点,明かりの個数(最大300),速さ倍率
//角度は右を0度として上を90度、左を180度、下を270度とし、
//選択開始角度から左回りに回って終了地点までを範囲とする。
//(追記)サンプルとしてスピードも設定できるようにしました
void SetCupAkari(Float2 pos, int saidai, int damagetype, int firstangle, int endangle, int akarinum, float speed)
{

	float firstrad, endrad; //ラジアン角用
	Float2 vec; //配列代入用
	int create_akari = min(akarinum, 300); //最大300個生成
	Float2 akarivec[300];

	//角度の是正処置
	while (firstangle >= 360) {
		firstangle -= 360;
	}
	while (endangle >= 360) {
		firstangle -= 360;
	}

	//ラジアンに変換
	firstrad = firstangle * (D3DX_PI / 180);
	endrad = endangle * (D3DX_PI / 180);

	//角度の範囲のパターン分け
	//終わりの角度は開始の角度より大きくする
	if (firstangle > endangle) {
		endangle += 360;
	}
	switch ((int)(firstangle / 90)) //開始角度がどこのエリアか
	{
	case 0: //0～89度のとき
		switch ((int)(endangle / 90)) //終わりの角度がどこのエリアか
		{
		case 0: //同じエリアかつ90度をまたがない
			//ここで発射角度の設定
			for (int i = 0; i < create_akari; i++)
			{
				//xを範囲内になるまで取り直し
				while (1) {
					vec.x = frand() + frand() - 1; //-1.0~1.0
					if ((cos(endrad) <= vec.x) && (vec.x <= cos(firstrad))) {
						break;
					}
				}//yを範囲内になるまで取り直し
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(firstrad) <= vec.y) && (vec.y <= sin(endrad))) {
						break;
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 1: //90度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを範囲内になるまで取り直し
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((cos(endrad) <= vec.x) && (vec.x <= cos(firstrad))) {
						break;
					}
				}
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((sin(firstrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					} 
					else {
						if ((sin(endrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 2: //90度と180度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを範囲内になるまで取り直し
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((-1.0f <= vec.x) && (vec.x <= cos(firstrad))) {
						break;
					}
				}
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((sin(firstrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
					else {
						if ((sin(endrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 3: //90度と180度と270度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//yを先に取る
				vec.y = frand() + frand() - 1;
				//xを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.x = frand() + frand() - 1;
					if (0 <= vec.y) {
						if ((-1.0f <= vec.x) && (vec.x <= cos(firstrad))) {
							break;
						}
					}
					else {
						if ((-1.0f <= vec.x) && (vec.x <= cos(endrad))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 4: //同じエリアかつ90、180、270、0度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを先に取る
				vec.x = frand() + frand() - 1;
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if (! ((sin(endrad) <= vec.y) && (vec.y <= sin(firstrad)))) {
							break;
						}
					}
					else {
						break;
					}
				}
				akarivec[i] = vec;
			}
			break;
		}
		break;
		//ここまで開始角度が0～89度のとき

	case 1: //90～179°
		switch ((int)(endangle / 90)) //終わりの角度がどこのエリアか
		{
		case 1: //同じエリアかつ180度をまたがない
			for (int i = 0; i < create_akari; i++)
			{
				//xを範囲内になるまで取り直し
				while (1) {
					vec.x = frand() + frand() - 1; //-1.0~1.0
					if ((cos(endrad) <= vec.x) && (vec.x <= cos(firstrad))) {
						break;
					}
				}//yを範囲内になるまで取り直し
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(endrad) <= vec.y) && (vec.y <= sin(firstrad))) {
						break;
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 2: //180度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//yを範囲内になるまで取り直し
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(endrad) <= vec.y) && (vec.y <= sin(firstrad))) {
						break;
					}
				}
				//xを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.x = frand() + frand() - 1;
					if (0 <= vec.y) {
						if ((cos(firstrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
					else {
						if ((cos(endrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 3: //180度と270度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを範囲内になるまで取り直し
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((-1.0f <= vec.x) && (vec.x <= cos(endrad))) {
						break;
					}
				}
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((-1.0f <= vec.y) && (vec.y <= sin(endrad))) {
							break;
						}
					}
					else {
						if ((-1.0f <= vec.y) && (vec.y <= sin(firstrad))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 4: //180度と270度と0度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを先に取る
				vec.x = frand() + frand() - 1;
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((-1.0f <= vec.y) && (vec.y <= sin(endrad))) {
							break;
						}
					}
					else {
						if ((-1.0f <= vec.y) && (vec.y <= sin(firstrad))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 5: //同じエリアかつ180、270、0、90度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを先に取る
				vec.x = frand() + frand() - 1;
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						break;
					}
					else {
						if (!((sin(firstrad) <= vec.y) && (vec.y <= sin(endrad)))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		}
		break;
	case 2: //180～269°
		switch ((int)(endangle / 90)) //終わりの角度がどこのエリアか
		{
		case 2: //同じエリアかつ270度をまたがない
			for (int i = 0; i < create_akari; i++)
			{
				//xを範囲内になるまで取り直し
				while (1) {
					vec.x = frand() + frand() - 1; //-1.0~1.0
					if ((cos(firstrad) <= vec.x) && (vec.x <= cos(endrad))) {
						break;
					}
				}//yを範囲内になるまで取り直し
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(endrad) <= vec.y) && (vec.y <= sin(firstrad))) {
						break;
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 3: //270度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを範囲内になるまで取り直し
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((cos(firstrad) <= vec.x) && (vec.x <= cos(endrad))) {
						break;
					}
				}
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((-1.0f <= vec.y) && (vec.y <= sin(endrad))) {
							break;
						}
					}
					else {
						if ((-1.0f <= vec.y) && (vec.y <= sin(firstrad))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 4: //270度と0度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを範囲内になるまで取り直し
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((cos(firstrad) <= vec.x) && (vec.x <= 1.0f)) {
						break;
					}
				}
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((-1.0f <= vec.y) && (vec.y <= sin(endrad))) {
							break;
						}
					}
					else {
						if ((-1.0f <= vec.y) && (vec.y <= sin(firstrad))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 5: //270度と0度と90度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//yを先に取る
				vec.y = frand() + frand() - 1;
				//xを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.x = frand() + frand() - 1;
					if (0 <= vec.y) {
						if ((cos(endrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
					else {
						if ((cos(firstrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 6: //同じエリアかつ270、0、90、180度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを先に取る
				vec.x = frand() + frand() - 1;
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						break;
					}
					else {
						if (!((sin(firstrad) <= vec.y) && (vec.y <= sin(endrad)))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		}
		break;
	case 3: //270～359°
		switch ((int)(endangle / 90)) //終わりの角度がどこのエリアか
		{
		case 3: //同じエリアかつ0度をまたがない
			//ここで発射角度の設定
			for (int i = 0; i < create_akari; i++)
			{
				//xを範囲内になるまで取り直し
				while (1) {
					vec.x = frand() + frand() - 1; //-1.0~1.0
					if ((cos(firstrad) <= vec.x) && (vec.x <= cos(endrad))) {
						break;
					}
				}//yを範囲内になるまで取り直し
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(firstrad) <= vec.y) && (vec.y <= sin(endrad))) {
						break;
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 4: //0度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//yを範囲内になるまで取り直し
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(firstrad) <= vec.y) && (vec.y <= sin(endrad))) {
						break;
					}
				}
				//xを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.x = frand() + frand() - 1;
					if (0 <= vec.y) {
						if ((cos(endrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
					else {
						if ((cos(firstrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 5: //0度と90度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを範囲内になるまで取り直し
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((cos(endrad) <= vec.x) && (vec.x <= 1.0f)) {
						break;
					}
				}
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((sin(firstrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
					else {
						if ((sin(endrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 6: //0度と90度と180度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを先に取る
				vec.x = frand() + frand() - 1;
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((sin(firstrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
					else {
						if ((sin(endrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 7: //同じエリアかつ0、90、180、270度をまたぐ
			for (int i = 0; i < create_akari; i++)
			{
				//xを先に取る
				vec.x = frand() + frand() - 1;
				//yを範囲内になるまで取り直し
				//2パターン想定する
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						break;
					}
					else {
						if (!((sin(endrad) <= vec.y) && (vec.y <= sin(firstrad)))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		}
		break;
	}

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
			//MovePos[i] = akarivec[create_akari - 1];

			//ここのakarivecにスピードを掛けると加速するよ
			//(追記)とりまスピード追加、要らんかったら消してくれ
			//追加した奴→引数のspeed,この下の( * speed)
			MovePos[i].x = akarivec[create_akari - 1].x * speed;
			MovePos[i].y = -akarivec[create_akari - 1].y * speed; //単位円上yは上が正になるがゲーム上だと上は負になるため

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

void SetAkari(Float2 pos, Float2 vec, float speed)
{
	Float2 akarivec = { vec.x,vec.y };


	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			g_AkariObject[i].speed = speed;
			g_AkariObject[i].vec = { 0.0f,0.0f };

			MovePos[i] = akarivec;
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
			break;
		}
	}
}

void SoulAkari(Float2 pos, Float2 vec)
{
	Float2 akarivec = { vec.x,vec.y };

	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			g_AkariObject[i].vec = { 0.0f,0.0f };

			MovePos[i] = akarivec;
			//色づけ
			{
				////ランダムで赤か青になる
				//if (rand() % 2 == 0)
				//{
				//	g_AkariObject[i].color = { 0.5f,0.5f,1.0f,1.0f };
				//}
				//else
				//{
				//	g_AkariObject[i].color = { 2.0f,0.5f,0.5f,1.0f };
				//}

				if (rand() % 2 == 0)
				{
					g_AkariObject[i].color = { 0.5f,0.5f,1.0f,1.0f };
				}
				else
				{
					g_AkariObject[i].color = { 2.0f,0.5f,0.5f,1.0f };
				}
			}
			break;
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