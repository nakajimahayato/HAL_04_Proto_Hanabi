/*==============================================================================

   カメラ処理 [camera.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "camera.h"
#include "input.h"
#include "player.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define ZOOM_SCALE 1.0f
#define SCREEN_WIDTH_RATE 16
#define SCREEN_HEIGHT_RATE 9

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//static CAMERA_2D	g_Camera;	//カメラ用データ
static D3DXVECTOR2	g_Base;		//ベース座標


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.up =1.0f;
	g_Camera.down = 1.0f;
	g_Camera.left = 1.0f;
	g_Camera.right = 1.0f;

	g_Base = D3DXVECTOR2(0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCamera(void)
{
	SetWorldViewProjection2D(g_Camera);
	

	//カメラ座標を反転した値をベース座標として使う
	g_Base =(g_Camera.pos * -1);

	if (GetKeyboardPress(DIK_UP))
	{
		//ズームアウト（遠ざかる）
		//g_Camera.up += ZOOM_SCALE *SCREEN_HEIGHT_RATE;
		//g_Camera.down += ZOOM_SCALE * SCREEN_HEIGHT_RATE;
		//g_Camera.left += ZOOM_SCALE * SCREEN_WIDTH_RATE;
		//g_Camera.right += ZOOM_SCALE * SCREEN_WIDTH_RATE;

		//SetWorldViewProjection2D(g_Camera);
		ZoomOut();
	}
	else
	{
		SetWorldViewProjection2D(g_Camera);
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		//ズームイン（近づく）
		//g_Camera.up -= ZOOM_SCALE * SCREEN_HEIGHT_RATE;
		//g_Camera.down -= ZOOM_SCALE * SCREEN_HEIGHT_RATE;
		//g_Camera.left -= ZOOM_SCALE * SCREEN_WIDTH_RATE;
		//g_Camera.right -= ZOOM_SCALE * SCREEN_WIDTH_RATE;

		//if (g_Camera.right <= -SCREEN_WIDTH/4)
		//{
		//	g_Camera.up += ZOOM_SCALE * SCREEN_HEIGHT_RATE;
		//	g_Camera.down += ZOOM_SCALE * SCREEN_HEIGHT_RATE;
		//	g_Camera.left += ZOOM_SCALE * SCREEN_WIDTH_RATE;
		//	g_Camera.right += ZOOM_SCALE * SCREEN_WIDTH_RATE;
		//}
		//SetWorldViewProjection2D(g_Camera);
		ZoomIn();
		
	}
	else
	{
		SetWorldViewProjection2D(g_Camera);
	}

	if (GetKeyboardTrigger(DIK_R))
	{
		g_Camera.up = ZOOM_SCALE;
		g_Camera.down = ZOOM_SCALE;
		g_Camera.left = ZOOM_SCALE;
		g_Camera.right = ZOOM_SCALE;
		SetWorldViewProjection2D(g_Camera);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCamera(void)
{

}

D3DXVECTOR2 GetBase(void)
{
	return g_Base;
}

void SetCameraPos(float x, float y)
{
	g_Camera.pos.x = x;
	g_Camera.pos.y = y;
}

void ZoomIn()
{
	//ズームイン（近づく）
	g_Camera.up -= ZOOM_SCALE * SCREEN_HEIGHT_RATE;
	g_Camera.down -= ZOOM_SCALE * SCREEN_HEIGHT_RATE;
	g_Camera.left -= ZOOM_SCALE * SCREEN_WIDTH_RATE;
	g_Camera.right -= ZOOM_SCALE * SCREEN_WIDTH_RATE;

	if (g_Camera.right <= SCREEN_WIDTH/128 )
	{
			g_Camera.up += ZOOM_SCALE * SCREEN_HEIGHT_RATE;
			g_Camera.down += ZOOM_SCALE * SCREEN_HEIGHT_RATE;
			g_Camera.left += ZOOM_SCALE * SCREEN_WIDTH_RATE;
			g_Camera.right += ZOOM_SCALE * SCREEN_WIDTH_RATE;
	}
	SetWorldViewProjection2D(g_Camera);
}

void ZoomOut()
{
	//ズームアウト（遠ざかる）
	g_Camera.up += ZOOM_SCALE * SCREEN_HEIGHT_RATE;
	g_Camera.down += ZOOM_SCALE * SCREEN_HEIGHT_RATE;
	g_Camera.left += ZOOM_SCALE * SCREEN_WIDTH_RATE;
	g_Camera.right += ZOOM_SCALE * SCREEN_WIDTH_RATE;

	SetWorldViewProjection2D(g_Camera);
}