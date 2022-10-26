#pragma once

#include "main.h"
#include"BENRIclass.h"

bool HitCheckCircle(Float2 cir1pos, float cir1r,
	Float2 cir2pos, float cir2r);

bool HitCheckCircleSq(Float2 cir1pos, float cir1r,
	Float2 cir2pos, float cir2r);

bool HitCheckBox(Float2 box1pos, Float2 box1siz
	, Float2 box2pos, Float2 box2siz);

bool HitCheckCross(Float2 start1pos, Float2 end1pos
	, Float2 start2pos, Float2 end2pos);

bool HitCheckCross2nd(Float2 start1pos, Float2 end1pos
	, Float2 start2pos, Float2 end2pos);