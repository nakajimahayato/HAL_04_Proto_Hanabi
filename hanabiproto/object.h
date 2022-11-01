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
#define AKARI_NUM	100


class GameObject
{
public:
	Float2			pos;//���W
	Float2			vec;//�ړ�
	Float2			siz;//�傫��
	Float2			dir;//�ړ�����
	bool			use;//use�t���O
	bool			setvec;
};

class HanabiAkariObject:public GameObject
{
public:
	bool			gather;//�W�܂邠����
};

class EnemyObject :public GameObject
{
	
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



HRESULT InitAtHanabi(void);
void UninitAtHanabi(void);
void UpdateAtHanabi(void);
void DrawAtHanabi(void);