/*==============================================================================

				   スコア処理 [score.h]
				Author : 中島
				Date   : 2022/12/12(最終編集日)
------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCORE_END_GAME    100000  //PlayerScoreが一定以上でクリア
#define SCORE_DIGITS      6       //Player&EnemyScoreの桁数
#define PLAYERSCORE_POSX  720.0f  //PlayerScoreの表示位置X
#define ENEMYSCORE_POSX   1370.0f //EnemyScoreの表示位置X
#define SCORE_POSY        290.0f  //Player&Enemyの表示位置Y
#define SCORE_SIZE_X      40.0f   //Player&EnemyのサイズX
#define SCORE_SIZE_Y      40.0f   //Player&EnemyのサイズY

struct PLAYERSCORE {
	int   score;
	int   max_score;
};

struct ENEMYSCORE {
	int   score;
	int   max_score;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore();
void UninitScore();

//Playerのスコア関連の関数
void UpdatePlayerScore();
void DrawPlayerScore();
void PlusPlayerScore(int plusscore);
void SetPlayerScore(int score);
int GetPlayerScore();

//Enemyのスコア関連の関数
void UpdateEnemyScore();
void DrawEnemyScore();
void PlusEnemyScore(int plusscore);
void SetEnemyScore(int score);
int GetEnemyScore();


