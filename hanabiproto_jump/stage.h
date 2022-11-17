/*==============================================================================

   プレイヤー管理[stage.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "main.h"
#include "renderer.h"
#include "BENRIclass.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGE_X	30 
#define STAGE_Y 20
#define CHIPSIZE_X 64.0f
#define CHIPSIZE_Y 32.0f

class Stage
{
public:
	Float2			pos;//座標
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage(void);

bool GetStageInfoSITA(Float2 playerpos);
bool GetStageInfoUE(Float2 playerpos);
bool GetStageInfoMIGI(Float2 playerpos);
bool GetStageInfoHIDARI(Float2 playerpos);
