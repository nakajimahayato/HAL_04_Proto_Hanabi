/*==============================================================================

   �v���C���[�Ǘ�[object.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"
#include "BENRIclass.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define AKARI_NUM	30000


class GameObject
{
public:
	Float2			pos;//���W
	Float2			vec;//�ړ�
	float			speed;
	Float2			siz;//�傫��
	Float2			dir;//�ړ�����
	D3DXCOLOR		color;
	bool			use;//use�t���O
	float			frame;
	Float2			drop; //������
	Float2			sdrop;//����������x
	bool			hitground;
};

class HanabiAkariObject:public GameObject
{
public:
	bool			gather;//�W�܂邠����
	
	bool			setvec;
};

class EnemyObject :public GameObject
{
	float			Health;
	float			Attack;
	float			Gravity;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitAkariObject(void);
void UninitAkariObject(void);
void UpdateAkariObject(void);
void DrawAkariObject(void);
void Akarigather(int index);
HanabiAkariObject GetAkariObject(int index);
void SetAkari(Float2 pos);
void SetAkari(Float2 pos, int saidai);
Float2 Centergather(Float2 up, Float2 down, Float2 left, Float2 right);


HRESULT InitAtHanabi(void);
void UninitAtHanabi(void);
void UpdateAtHanabi(void);
void DrawAtHanabi(void);
Float2 GetAtHanabiDeadPos(int index);
Float2 GetAtHanabiPos(Float2 PosA, Float2 PosB);
void Normalizer(Float2 Player, Float2 Cursor);