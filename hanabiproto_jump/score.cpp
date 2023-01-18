/*==============================================================================

				   スコア処理 [score.cpp]
				Author : 中島
				Date   : 2023/01/17(最終編集日)
------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "renderer.h"
#include "BENRIclass.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"
#include "main.h"

//*****************************************************************************							
// マクロ定義							
//*****************************************************************************							
//*****************************************************************************							
// プロトタイプ宣言							
//*****************************************************************************							

//*****************************************************************************							
// グローバル変数							
//*****************************************************************************	
static int g_Texture;

static PLAYERSCORE g_PlayerScore;
static ENEMYSCORE  g_EnemyScore;

//=============================================================================							
// 初期化処理							
//=============================================================================							
HRESULT InitScore()
{
	g_Texture = LoadTexture((char*)"data/TEXTURE/score.png");

	g_PlayerScore.score = 0;
	g_PlayerScore.max_score = 0;
	g_EnemyScore.score = 0;
	g_EnemyScore.max_score = 0;

	SetPlayerScore(0);
	SetEnemyScore(0);

	return S_OK;
}

//=============================================================================							
// 終了処理							
//=============================================================================	
void UninitScore()
{
}

//=============================================================================							
// 更新処理							
//=============================================================================	
void UpdateScore()
{
	UpdatePlayerScore();
	UpdateEnemyScore();
}

//=============================================================================							
// 描画処理							
//=============================================================================	
void DrawScore()
{
	DrawPlayerScore();
	DrawEnemyScore();
}


//PlayerScore関連
void UpdatePlayerScore() {
	g_PlayerScore.score+= 11;
	if (g_PlayerScore.score > g_PlayerScore.max_score) {
		g_PlayerScore.score = g_PlayerScore.max_score;
	}
}

void DrawPlayerScore() {
	int drawscore = g_PlayerScore.score;

	for (int i = 0; i < SCORE_DIGITS; i++) {
		int num = drawscore % 10;
		DrawSpriteLeftTop(g_Texture, PLAYERSCORE_POSX - (i * 40.0f), SCORE_POSY, SCORE_SIZE_X, SCORE_SIZE_Y, 0.1f * num, 0.0f, 0.1f, 1.0f);
		drawscore /= 10;
	}
}

void PlusPlayerScore(int score) {
	g_PlayerScore.max_score += score;
	if (g_PlayerScore.max_score < 0) {
		g_PlayerScore.max_score = 0;
	}
}

void SetPlayerScore(int score) {
	g_PlayerScore.score = score;
}

int GetPlayerScore() {
	return g_PlayerScore.score;
}

//EnemyScore関連
void UpdateEnemyScore()
{
	g_EnemyScore.score += 11;
	if (g_EnemyScore.score > g_EnemyScore.max_score) {
		g_EnemyScore.score = g_EnemyScore.max_score;
	}
}

void DrawEnemyScore() {
	int drawscore = g_EnemyScore.score;

	for (int i = 0; i < SCORE_DIGITS; i++) {
		int num = drawscore % 10;
		DrawSpriteLeftTop(g_Texture, ENEMYSCORE_POSX - (i * 40.0f), SCORE_POSY, SCORE_SIZE_X, SCORE_SIZE_Y, 0.1f * num, 0.0f, 0.1f, 1.0f);
		drawscore /= 10;
	}
}

void PlusEnemyScore(int score) {
	g_EnemyScore.max_score += score;
	if (g_EnemyScore.max_score < 0) {
		g_EnemyScore.max_score = 0;
	}
}

void SetEnemyScore(int score) {
	g_EnemyScore.score = score;
}

int GetEnemyScore() {
	return g_EnemyScore.score;
}
