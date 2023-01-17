/*==============================================================================

   必殺あかり管理[akari_ex.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#ifndef AKARI_EX_H_
#define AKARI_EX_H_

#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define EX_AKARI_NUM 2000
#define EX_AKARI_SEARCH_DIST 300
#define EX_AKARI_FOLLOW_SPEED 400 //数字が大きくなるほどゆっくりに

enum EX_COLOR
{
	EX_COLOR_NONE,		//色なし

	EX_COLOR_RED,		//赤
	EX_COLOR_BLUE,		//青
	EX_COLOR_GREEN,		//緑
	EX_COLOR_CYAN,		//シアン
	EX_COLOR_MAGENTA,	//マゼンタ
	EX_COLOR_YELLOW,	//イエロー
	EX_COLOR_WHITE,		//白

	EX_COLOR_NUM //終端コード
};

class EX_AkariObject :public HanabiAkariObject
{
public:
	EX_COLOR ex_color;
	bool follow;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT InitExAkariObject(void);
void UninitExAkariObject(void);
void UpdateExAkariObject(void);
void DrawExAkariObject(void);

void SetExAkariBase(Float2 pos, bool red, bool green, bool blue, int damagetype, int akarinum, float speed, EX_COLOR color);
void SetExAkari(Float2 pos, EX_COLOR color);

EX_AkariObject GetExAkari(int index);
void ExAkariGather(int index, Float2 gatherpos);
void ExAkariFollow(int index, bool follow);
void ExColorPlus(COLOR_AKARI colortype, Float2 gatherpos);

#endif // !AKARI_EX_H_
