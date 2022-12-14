/*==============================================================================

   �v���C���[�Ǘ�[stage.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "main.h"
#include "renderer.h"
#include "BENRIclass.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STAGE_X	64
#define STAGE_Y 32
#define CHIPSIZE_X (SCREEN_WIDTH/60)  //32
#define CHIPSIZE_Y (SCREEN_HEIGHT/33) //32

class Stage
{
public:
	Float2			pos;//���W
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage(void);

int GetStageInfoSITA(Float2 playerpos);
int GetStageInfoUE(Float2 playerpos);
int GetStageInfoMIGI(Float2 playerpos);
int GetStageInfoHIDARI(Float2 playerpos);

bool GetStageInfoRain(Float2 akaripos);

int GetStageInfoEnemySITA(Float2 enemypos, Float2 enemysize);

void SetRespawnPos(float x, float y);
Float2 Respawn();