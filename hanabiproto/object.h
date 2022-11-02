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
	Float2			siz;//大きさ
	Float2			dir;//移動方向
	D3DXCOLOR		color;
	bool			use;//useフラグ
	bool			setvec;
};

class HanabiAkariObject:public GameObject
{
public:
	bool			gather;//集まるあかり
	float			frame;
};

class EnemyObject :public GameObject
{
	
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



HRESULT InitAtHanabi(void);
void UninitAtHanabi(void);
void UpdateAtHanabi(void);
void DrawAtHanabi(void);
Float2 GetAtHanabiDeadPos(int index);
Float2 GetAtHanabiPos(Float2 PosA, Float2 PosB);
void Normalizer(Float2 Player, Float2 Cursor);