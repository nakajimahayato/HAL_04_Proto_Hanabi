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
class GameObject
{
public:
	Float2			pos;//座標
	Float2			vec;//移動
	Float2			siz;//大きさ
	Float2			dir;//移動方向
	bool			use;//useフラグ
};

class HanabiObject:public GameObject
{
	Float2			ShotPlayerpos;
	Float2			ShotCursorpos;
};

class HanabiAkariObject:public GameObject
{

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

HRESULT InitAtHanabi(void);
void UninitAtHanabi(void);
void UpdateAtHanabi(void);
void DrawAtHanabi(void);