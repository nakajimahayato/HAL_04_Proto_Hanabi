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
#include "object.h"
#include "stage.h"
#include "inputx.h"
#include "enemy.h"
#include "timemanager.h"
#include "score.h"
#include "kappa_Enemy.h"
#include "akari_ex.h"
#include "time.h"

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
	InitTimeManager();
	InitAkariObject();
	InitPlayer();
	InitEnemy();
	InitAtHanabi();
	InitExAkariObject();
	InitScore();
	InitKappaEnemy();
	InitTime();

	// 背景の初期化
	InitBG();
	InitStage();

	InitCamera();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	UninitCamera();
	UninitTimeManager();
	
	//背景の終了処理
	UninitBG();
	UninitStage();
	// 頂点管理の終了処理
	UninitPlayer();
	UninitEnemy();
	UninitKappaEnemy();

	UninitAkariObject();

	UninitAtHanabi();
	UninitExAkariObject();
	UninitScore();
	UninitTime();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{

	// 頂点管理の更新処理
	UpdateTimeManager();
	UpdateAkariObject();
	UpdatePlayer();
	UpdateEnemy();
	UpdateKappaEnemy();
	UpdateAtHanabi();
	UpdateExAkariObject();
	UpdateScore();
	UpdateTime();
	
	//背景の更新処理
	UpdateBG();
	UpdateStage();
	UpdateCamera();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();
	DrawStage();
	// 頂点管理の描画処理
	DrawAkariObject();
	DrawEnemy();
	DrawKappaEnemy();
	DrawAtHanabi();
	DrawExAkariObject();
	DrawScore();
	DrawTime();
	DrawPlayer();
	
	DrawCamera();
}
