
#include "collision.h"

//円と円の当たり判定
bool HitCheckCircle(D3DXVECTOR2 cir1pos, float cir1r,
	                D3DXVECTOR2 cir2pos, float cir2r)
{
	//cir1からcir2に向かうベクトルを作る
	D3DXVECTOR2 dist;
	dist = cir2pos - cir1pos;

	//distベクトルの大きさを計算する
	float length;
	//ベクトルの大きさは「各成分を2乗して全部足す。全部足し終わったら平方根をとる」で計算
	length = sqrt((dist.x*dist.x) + (dist.y*dist.y));

	//circle1の半径とcircle2の半径を足した値を作る
	float R;
	R = (cir1r + cir2r);

	if (length < R)
		return true;
	else
		return false;
}

bool HitCheckCircleSq(D3DXVECTOR2 cir1pos, float cir1r,
	D3DXVECTOR2 cir2pos, float cir2r)
{
	//cir1からcir2に向かうベクトルを作る
	D3DXVECTOR2 dist;
	dist = cir2pos - cir1pos;

	//distベクトルの大きさを計算する
	float length;
	//ベクトルの大きさは「各成分を2乗して全部足す。全部足し終わったら平方根をとる」で計算
	length = (dist.x*dist.x) + (dist.y*dist.y);

	//circle1の半径とcircle2の半径を足した値を作る
	float R;
	R = (cir1r + cir2r) * (cir1r + cir2r);

	if (length < R)
		return true;
	else
		return false;
}