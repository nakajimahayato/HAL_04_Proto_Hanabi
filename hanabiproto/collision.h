#pragma once

#include "main.h"

bool HitCheckCircle(D3DXVECTOR2 cir1pos, float cir1r,
	D3DXVECTOR2 cir2pos, float cir2r);

bool HitCheckCircleSq(D3DXVECTOR2 cir1pos, float cir1r,
	D3DXVECTOR2 cir2pos, float cir2r);