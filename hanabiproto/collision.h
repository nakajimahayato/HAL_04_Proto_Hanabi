#pragma once

#include "main.h"
#include"BENRIclass.h"

bool HitCheckCircle(Float2 cir1pos, float cir1r,
	Float2 cir2pos, float cir2r);

bool HitCheckCircleSq(Float2 cir1pos, float cir1r,
	Float2 cir2pos, float cir2r);

bool HitCheckBox(Float2 box1pos, Float2 box1siz
	, Float2 box2pos, Float2 box2siz);