/*==============================================================================

   ゲーム内時間管理処理 [timemanager.h]
														 Author : 横田郁弥
														 Date   : 2022/12/10 14:35
--------------------------------------------------------------------------------
  ゲーム内時間を記録できる時間管理クラスを作成
  好きなように時間を動かせるようにする
  Updateにシーン遷移の条件

  時間管理.cppにクリア、ゲームオーバーの判定追加し、何らかの形でリザルトに渡す。
  リザルトにあるゲームクリアとゲームオーバーをどうやって切り替えるかを考える
  →(例)成功＆失敗フラグを時間管理クラスに作ってそのゲッターをリザルトに渡すとか
==============================================================================*/
#pragma once
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
class TimeManager
{
public:
	float		time;
	float		nowTime;
	float		frame;
};

#define	TIME_LIMIT	180	//制限時間(秒)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTimeManager(void);
void UninitTimeManager(void);
void UpdateTimeManager(void);
void DrawTimeManager(void);

void Result(float enemyscore, float playerscore);