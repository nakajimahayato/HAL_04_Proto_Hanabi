/*==============================================================================

   ゲーム本編処理 [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "game.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "bg.h"
#include "collision.h"
#include "camera.h"
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


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	// 頂点管理の初期化処理
	InitPlayer();

	// 背景の初期化
	InitBG();

	InitCamera();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	UninitCamera();


	//背景の終了処理
	UninitBG();

	// 頂点管理の終了処理
	UninitPlayer();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{

	// 頂点管理の更新処理
	UpdatePlayer();

	//背景の更新処理
	UpdateBG();

	UpdateCamera();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();

	// 頂点管理の描画処理
	DrawPlayer();

	DrawCamera();

}
