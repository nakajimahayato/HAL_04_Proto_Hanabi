/*==============================================================================

   プレイヤー管理[object.h]
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
#define AKARI_NUM	30000


class GameObject
{
public:
	Float2			pos;//座標
	Float2			vec;//移動
	float			speed;
	Float2			siz;//大きさ
	Float2			dir;//移動方向
	D3DXCOLOR		color;
	bool			use;//useフラグ
	float			frame;
	Float2			drop; //落ちる
	Float2			sdrop;//落ちる加速度
	bool			hitground;
};

enum COLOR_AKARI
{
	RED_AKARI,
	GREEN_AKARI,
	BLUE_AKARI,

	COLOR_NUM
};

class HanabiAkariObject :public GameObject
{
public:
	bool			gather;//集まるあかり
	Float2          gatherpos;
	bool			setvec;
	bool			damageenemyflug;  //エネミーにダメージを与える
	bool			damageplayerflug; //プレイヤーにダメージを与える
	bool			wet;//濡れた状態
	COLOR_AKARI     colortype;
	int             gathernum; //合成される際の整理番号
};

class EnemyObject :public GameObject
{
public:
	float			Health;
	bool            fall;
	int             directionX;
	float			Attack;
	float			Gravity;
	bool			enemydead;		//エネミー死亡フラグ
	int				deadframe;		//死亡後のフレーム数
	int				akaricount;		//明かりを交互に打つカウント
	float			shrinkAmount;	//死亡時の収縮値
	virtual void Action() {}

};

class CupEnemy :public EnemyObject
{
public:
	void Action() override;
};

class SoulEnemy :public EnemyObject
{
public:
	void Action() override;
};

class SpawnPointEnemy :public EnemyObject
{
public:
	float			scoreframe;
	bool			isSPEnemydead;	//わきどころエネミーの死亡フラグ
	bool			isColorBlue;	//わきどころエネミーの青色フラグ
	bool			isColorRed;		//わきどころエネミーの赤色フラグ
	bool			isColorGreen;	//わきどころエネミーの緑色フラグ
	void Action()override;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitAkariObject(void);
void UninitAkariObject(void);
void UpdateAkariObject(void);
void DrawAkariObject(void);
void Akarigather(int index, Float2 gatherpos, int gather_num);
HanabiAkariObject GetAkariObject(int index);
void SetAkari(Float2 pos);
void SetAkari(Float2 pos, int saidai);
void SetAkari(Float2 pos, int saidai, int damagetype);
void SetAkari(Float2 pos, Float2 vec, float speed);
void SoulAkari(Float2 pos, Float2 vec);
void SetHouseAkari(Float2 pos, int color);
void SetCupAkari(Float2 pos, int saidai, int damagetype, int firstangle, int endangle, int akarinum, float speed);
Float2 Centergather(Float2 up, Float2 down, Float2 left, Float2 right);


HRESULT InitAtHanabi(void);
void UninitAtHanabi(void);
void UpdateAtHanabi(void);
void DrawAtHanabi(void);
Float2 GetAtHanabiDeadPos(int index);
Float2 GetAtHanabiPos(Float2 PosA, Float2 PosB);
void Normalizer(Float2 Player, Float2 Cursor);
void RedBurst(int akarinum);