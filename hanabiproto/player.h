/*==============================================================================

   プレイヤー管理[player.h]
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
struct PLAYER
{
	Float2		pos;	//プレイヤーの現在位置
	Float2		vec;	//プレイヤーのベクトル
	Float2		spjp;	//プレイヤーの移動とジャンプ速度

};

struct CURSOR
{

	Float2		pos;
	Float2		prev_pos;

	//bool		csInp;	//カーソル入力判別用
	bool		use;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);



//PLAYER* GetPlayer(void);
