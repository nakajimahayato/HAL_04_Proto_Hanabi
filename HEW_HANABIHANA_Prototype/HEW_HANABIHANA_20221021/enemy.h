/*==============================================================================

   エネミー処理 [enemy.h]
														 Author : 
														 Date   : 2022/10/23
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_ENEMY 10

struct ENEMY
{
	D3DXVECTOR2 pos;		//表示座標
	D3DXVECTOR2 dir;		//移動方法
	float		speed;		//移動速度

	D3DXVECTOR2 startPos; //配置座標

	int			state;	//敵の状態管理
	float		frame;	//経過フレーム管理

	int use;				//可視フラグ
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void SetEnemy(D3DXVECTOR2 pos, int muki);

ENEMY* GetEnemy(void);