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

//*****************************************************************************						
// プロトタイプ宣言						
//*****************************************************************************										

HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(Float2 pos, int saidai, int enemytype);
EnemyObject* GetEnemy();

EnemyObject** GetCupEnemy();










