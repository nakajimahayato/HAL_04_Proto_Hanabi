/*==============================================================================


				   エネミー処理 [enemy.h]
									Author	 :
									Date	 : (最終編集日)
------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "BENRIclass.h"	
#include "main.h"
#include "collision.h"
#include "object.h"
#include "player.h"
#include "sprite.h"
#include "texture.h"
#include "sound.h"
#include "camera.h"

//*****************************************************************************						
// マクロ定義						
//*****************************************************************************						
#define NUM_ENEMY 100
#define NUM_CUPENEMY 100 
#define NUM_SOULENEMY 100
#define ENEMY_HEALTH 10.0f

#define ENEMY1_SIZEX (80.0f) //必要に応じて変えてください
#define ENEMY1_SIZEY (80.0f)

#define ENEMY2_SIZEX (90.0f)
#define ENEMY2_SIZEY (80.0f)

#define ENEMY3_SIZEX (80.0f)
#define ENEMY3_SIZEY (80.0f)

#define ENEMY_FALL_SPEED (1.5f)
#define ENEMY_WALK_SPEED (2.0f)

//*****************************************************************************						
// プロトタイプ宣言						
//*****************************************************************************										

HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(Float2 pos, int saidai, int enemytype, int muki);
void SetSoulEnemy(Float2 pos, int saidai, int enemytype, int muki);
EnemyObject* GetEnemy();

EnemyObject** GetCupEnemy();
SoulEnemy* GetSoulEnemy();

void EnemyDeadProcess(int i);
