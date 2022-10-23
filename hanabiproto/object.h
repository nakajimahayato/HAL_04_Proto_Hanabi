/*==============================================================================

   プレイヤー管理[object.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct PLAYER
{
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2     uv;
	int				muki;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGameObject(void);
void UninitGameObject(void);
void UpdateGameObject(void);
void DrawGameObject(void);

PLAYER* GetGameObject(void);
