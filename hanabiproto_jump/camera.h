#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
static CAMERA_2D	g_Camera;	//カメラ用データ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void DrawCamera(void);

D3DXVECTOR2 GetBase(void);
void SetCameraPos(float x, float y);

void ZoomOut();
void ZoomIn();
