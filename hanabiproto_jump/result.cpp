/*==============================================================================

   リザルト画面処理 [result.cpp]
														 Author : 横田郁弥
														 Date   : 2022/12/07
--------------------------------------------------------------------------------

==============================================================================*/
#include "result.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TextureNo;//タイトル画面用テクスチャの識別子
static int g_BGMNo;		//タイトル用BGMの識別子

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitResult(void)
{
	//テクスチャを読み込んで識別子を受け取る
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/result.png");

	//音声ファイルを読み込んで識別子を受け取る
	//g_BGMNo = LoadSound("data/BGM/");

	//BGMの再生(2つ目の引数はループ回数)
	//ループ回数に負の値を指定すると無限ループ
	//PlaySound(g_BGMNo, -1);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void UninitResult(void)
{
	//BGM停止
	//StopSound(g_BGMNo);
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void UpdateResult(void)
{
	//Enterキーが押されたらSCENE_GAMEへ移行する
	//if ()
	//{
	//	//SetScene(SCENE_GAME);
	//}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void DrawResult(void)
{
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);
}