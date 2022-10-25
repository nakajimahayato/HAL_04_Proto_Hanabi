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
	bool			use;//use�t���O
	bool			gather;//�W�܂邠����
};

class HanabiObject:public GameObject
{
	Float2			ShotPlayerpos;
	Float2			ShotCursorpos;
};

class HanabiAkariObject:public GameObject
{

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitAkariObject(void);
void UninitAkariObject(void);
void UpdateAkariObject(void);
void DrawAkariObject(void);
