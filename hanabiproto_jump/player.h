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
#include "stage.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_CURSOR_NUM (56)
#define PLAYER_SIZEX (CHIPSIZE_X * 1)  //
#define PLAYER_SIZEY (CHIPSIZE_Y * 3)  //192
#define PLAYER_FALL_SPEED_MAX 15.0f
#define PLAYER_ACCELERATION_X 0.5f //プレイヤーの横加速度
#define PLAYER_SPEEDMAX_X 8.0f //プレイヤーの最大速度
#define PLAYER_BRAKE 0.4 //地面との摩擦
#define PLAYER_MAXHP 30	
#define PLAYER_HP_PRINT 30	


struct PLAYER
{
	int		frame;	//プレイヤーのフレーム
	Float2		pos;	//プレイヤーの現在位置
	Float2      oldpos; //プレイヤーの過去の位置
	Float2		vec;	//プレイヤーのベクトル
	Float2		spjp;	//プレイヤーの移動とジャンプ速度
	//Float2      acceleration;//プレイヤーの加速度
	Float2		jp;		//プレイヤーのジャンプ処理
	int			hp;
	int			hpframe;
	int			maxframe;
};

struct CURSOR
{
public:
	Float2		pos;
	Float2		prev_pos;
	D3DXCOLOR	color;

	//bool		csInp;	//カーソル入力判別用
	bool		use;
};

static PLAYER g_Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
bool CompositionAkari(int clossStart, int clossGoal);
PLAYER* GetPlayer(void);
void plus_hissatuwaza(int index);
void HP_Minus(int damage);
void HP_Plus(int healing);


//PLAYER* GetPlayer(void);
