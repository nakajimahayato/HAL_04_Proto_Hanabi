#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
static CAMERA_2D	g_Camera;	//�J�����p�f�[�^

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void DrawCamera(void);

D3DXVECTOR2 GetBase(void);
void SetCameraPos(float x, float y);

void ZoomOut();
void ZoomIn();
