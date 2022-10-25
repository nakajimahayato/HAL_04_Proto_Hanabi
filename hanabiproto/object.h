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
class GameObject
{
public:
	Float2			pos;//���W
	Float2			vec;//�ړ�
	Float2			siz;//�傫��
	Float2			dir;//�ړ�����
	bool			use;//use�t���O
};

class HanabiObject:public GameObject
{
	Float2			ShotPlayerpos;
	Float2			ShotCursorpos;
};

class HanabiAkariObject:public GameObject
{

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

HRESULT InitAtHanabi(void);
void UninitAtHanabi(void);
void UpdateAtHanabi(void);
void DrawAtHanabi(void);