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
	bool			gather;//集まるあかり
	bool			setvec;
};

class HanabiObject:public GameObject
{
	Float2			ShotPlayerpos;
	Float2			ShotCursorpos;
	float			speed;	//移動速度
	float			frame;	//持続時間
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
Float2 GetAkariObject(int index);

HRESULT InitAtHanabi(void);
void UninitAtHanabi(void);
void UpdateAtHanabi(void);
void DrawAtHanabi(void);