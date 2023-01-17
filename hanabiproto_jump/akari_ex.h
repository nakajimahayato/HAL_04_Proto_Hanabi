/*==============================================================================

   �K�E������Ǘ�[akari_ex.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#ifndef AKARI_EX_H_
#define AKARI_EX_H_

#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define EX_AKARI_NUM 2000
#define EX_AKARI_SEARCH_DIST 300
#define EX_AKARI_FOLLOW_SPEED 400 //�������傫���Ȃ�قǂ�������

enum EX_COLOR
{
	EX_COLOR_NONE,		//�F�Ȃ�

	EX_COLOR_RED,		//��
	EX_COLOR_BLUE,		//��
	EX_COLOR_GREEN,		//��
	EX_COLOR_CYAN,		//�V�A��
	EX_COLOR_MAGENTA,	//�}�[���^
	EX_COLOR_YELLOW,	//�C�G���[
	EX_COLOR_WHITE,		//��

	EX_COLOR_NUM //�I�[�R�[�h
};

class EX_AkariObject :public HanabiAkariObject
{
public:
	EX_COLOR ex_color;
	bool follow;
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT InitExAkariObject(void);
void UninitExAkariObject(void);
void UpdateExAkariObject(void);
void DrawExAkariObject(void);

void SetExAkariBase(Float2 pos, bool red, bool green, bool blue, int damagetype, int akarinum, float speed, EX_COLOR color);
void SetExAkari(Float2 pos, EX_COLOR color);

EX_AkariObject GetExAkari(int index);
void ExAkariGather(int index, Float2 gatherpos);
void ExAkariFollow(int index, bool follow);
void ExColorPlus(COLOR_AKARI colortype, Float2 gatherpos);

#endif // !AKARI_EX_H_
