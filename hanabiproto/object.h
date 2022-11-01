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
#define AKARI_NUM	100


class GameObject
{
public:
	Float2			pos;//座標
	Float2			vec;//移動
	Float2			siz;//大きさ
	Float2			dir;//移動方向
	bool			use;//useフラグ
	bool			setvec;
};

class HanabiAkariObject:public GameObject
{
public:
	bool			gather;//集まるあかり
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