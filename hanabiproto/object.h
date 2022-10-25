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
	bool			use;//useフラグ
	bool			gather;//集まるあかり
};

class HanabiObject:public GameObject
{
	Float2			ShotPlayerpos;
	Float2			ShotCursorpos;
};

class HanabiAkariObject:public GameObject
{

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitAkariObject(void);
void UninitAkariObject(void);
void UpdateAkariObject(void);
void DrawAkariObject(void);
