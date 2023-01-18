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
// プロトタイプ宣言						
//*****************************************************************************										

HRESULT InitKappaEnemy(void);
void UninitKappaEnemy(void);
void UpdateKappaEnemy(void);
void DrawKappaEnemy(void);
EnemyObject* GetKappaEnemy();

void KappaEnemyDeadProcess(int i);