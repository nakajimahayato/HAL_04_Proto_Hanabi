
#include "collision.h"

//�~�Ɖ~�̓����蔻��
bool HitCheckCircle(D3DXVECTOR2 cir1pos, float cir1r,
	                D3DXVECTOR2 cir2pos, float cir2r)
{
	//cir1����cir2�Ɍ������x�N�g�������
	D3DXVECTOR2 dist;
	dist = cir2pos - cir1pos;

	//dist�x�N�g���̑傫�����v�Z����
	float length;
	//�x�N�g���̑傫���́u�e������2�悵�đS�������B�S�������I������畽�������Ƃ�v�Ōv�Z
	length = sqrt((dist.x*dist.x) + (dist.y*dist.y));

	//circle1�̔��a��circle2�̔��a�𑫂����l�����
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
	//cir1����cir2�Ɍ������x�N�g�������
	D3DXVECTOR2 dist;
	dist = cir2pos - cir1pos;

	//dist�x�N�g���̑傫�����v�Z����
	float length;
	//�x�N�g���̑傫���́u�e������2�悵�đS�������B�S�������I������畽�������Ƃ�v�Ōv�Z
	length = (dist.x*dist.x) + (dist.y*dist.y);

	//circle1�̔��a��circle2�̔��a�𑫂����l�����
	float R;
	R = (cir1r + cir2r) * (cir1r + cir2r);

	if (length < R)
		return true;
	else
		return false;
}