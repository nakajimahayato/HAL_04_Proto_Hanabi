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

enum COLOR_AKARI
{
	RED_AKARI,
	GREEN_AKARI,
	BLUE_AKARI,

	COLOR_NUM
};

class HanabiAkariObject:public GameObject
{
public:
	bool			gather;//�W�܂邠����
	Float2          gatherpos;
	bool			setvec;
	bool			damageenemyflug;  //�G�l�~�[�Ƀ_���[�W��^����
	bool			damageplayerflug; //�v���C���[�Ƀ_���[�W��^����
	bool			wet;//�G�ꂽ���
	COLOR_AKARI     colortype;
	int             gathernum; //���������ۂ̐����ԍ�
};

class EnemyObject :public GameObject
{
protected:
	float			Attack;
	float			Gravity;

public:
	float			Health;
	bool            fall;
	int             directionX;
	virtual void Action() {}

};

class CupEnemy :public EnemyObject
{
public:
	void Action() override;
};

class SpawnPointEnemy :public EnemyObject
{
public:
	float			scoreframe;
	bool			isSPEnemydead;
	bool			isColorBlue;
	bool			isColorRed;
	bool			isColorGreen;
	void Action()override;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitAkariObject(void);
void UninitAkariObject(void);
void UpdateAkariObject(void);
void DrawAkariObject(void);
void Akarigather(int index, Float2 gatherpos, int gather_num);
HanabiAkariObject GetAkariObject(int index);
void SetAkari(Float2 pos);
void SetAkari(Float2 pos, int saidai);
void SetAkari(Float2 pos, int saidai, int damagetype);
void SetAkari(Float2 pos, Float2 vec, float speed);
void SetCupAkari(Float2 pos, int saidai, int damagetype, int firstangle, int endangle, int akarinum, float speed);
void SetHouseAkari(Float2 pos, int color);
Float2 Centergather(Float2 up, Float2 down, Float2 left, Float2 right);


HRESULT InitAtHanabi(void);
void UninitAtHanabi(void);
void UpdateAtHanabi(void);
void DrawAtHanabi(void);
Float2 GetAtHanabiDeadPos(int index);
Float2 GetAtHanabiPos(Float2 PosA, Float2 PosB);
void Normalizer(Float2 Player, Float2 Cursor);
void RedBurst(int akarinum);