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

class HanabiAkariObject:public GameObject
{
public:
	bool			gather;//集まるあかり
	bool			setvec;
	bool			damageenemyflug;  //エネミーにダメージを与える
	bool			damageplayerflug; //プレイヤーにダメージを与える
	bool			wet;//濡れた状態
};

class EnemyObject :public GameObject
{
public:
	float			Health;
	bool            fall;
	int             directionX;
	float			Attack;
	float			Gravity;
	virtual void Action() {}

};

class CupEnemy :public EnemyObject
{
public:
	void Action() override;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitAkariObject(void);
void UninitAkariObject(void);
void UpdateAkariObject(void);
void DrawAkariObject(void);
void Akarigather(int index);
HanabiAkariObject GetAkariObject(int index);
void SetAkari(Float2 pos);
void SetAkari(Float2 pos, int saidai);
void SetAkari(Float2 pos, int saidai, int damagetype);
void SetAkari(Float2 pos, Float2 vec, float speed);
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