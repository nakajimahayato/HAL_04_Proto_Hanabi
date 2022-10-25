
#include "collision.h"
#include "main.h"


//�~�Ɖ~�̓����蔻��
bool HitCheckCircle(Float2 cir1pos, float cir1r,
	                Float2 cir2pos, float cir2r)
{
	//cir1����cir2�Ɍ������x�N�g�������
	Float2 dist;
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

bool HitCheckCircleSq(Float2 cir1pos, float cir1r,
	Float2 cir2pos, float cir2r)
{
	//cir1����cir2�Ɍ������x�N�g�������
	Float2 dist;
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

//���Ɣ��̓����蔻��
bool HitCheckBox(Float2 box1pos, Float2 box1siz
				,Float2 box2pos, Float2 box2siz)
{
	//���Ɣ��̒��S���m�̋���
	Float2 boxdis(box1pos - box2pos);
	//���̑傫���̍��v
	Float2 boxsiz(box1siz + box2siz);
	//���̑傫���̍��v�̔���
	Float2 boxsiz_half(boxsiz.x / 2, boxsiz.y / 2);

	if (-boxsiz_half.x < boxdis.x < boxdis.x &&
		-boxsiz_half.y < boxdis.y < boxdis.y)
	{
		return true;
	}

	return false;
}

bool HitCheckCross(Float2 start1pos, Float2 end1pos
				 , Float2 start2pos, Float2 end2pos)
{
	if (start2pos.x - start1pos.x == 0)
	{
		start2pos.x++;
	}
	if (end2pos.x - start1pos.x == 0)
	{
		end2pos.x++;
	}
	if (end1pos.x - start1pos.x == 0)
	{
		end1pos.x++;
	}

	Float2 s1s2vec(1,(start2pos.y - start1pos.y) / (start2pos.x - start1pos.x));
	Float2 s1e2vec(1,(end2pos.y - start1pos.y) / (end2pos.x - start1pos.x));
	Float2 s1e1vec(1,(end1pos.y - start1pos.y) / (end1pos.x - start1pos.x));



	if (s1e1vec.y < s1s2vec.y && s1e1vec.y > s1e2vec.y)
	{
		if (fabsf(start2pos.y - start1pos.y) + fabsf(start2pos.x - start1pos.x) < fabsf(end1pos.y - start1pos.y) + fabsf(end1pos.x - start1pos.x) && 
			fabsf(end2pos.y - start1pos.y) + fabsf(end2pos.x - start1pos.x) < fabsf(end1pos.y - start1pos.y) + fabsf(end1pos.x - start1pos.x))
		{
			return true;
		}
	}
	if (s1e1vec.y > s1s2vec.y && s1e1vec.y < s1e2vec.y)
	{
		if (fabsf(start2pos.y - start1pos.y) + fabsf(start2pos.x - start1pos.x) < fabsf(end1pos.y - start1pos.y) + fabsf(end1pos.x - start1pos.x) &&
			fabsf(end2pos.y - start1pos.y) + fabsf(end2pos.x - start1pos.x) < fabsf(end1pos.y - start1pos.y) + fabsf(end1pos.x - start1pos.x))
		{
			return true;
		}
	}
	return false;
}