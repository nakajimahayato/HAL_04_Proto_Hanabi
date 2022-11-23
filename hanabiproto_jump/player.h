/*==============================================================================

   �v���C���[�Ǘ�[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"
#include "BENRIclass.h"
#include "stage.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_CURSOR_NUM (56)
#define PLAYER_SIZEX (CHIPSIZE_X*1.5)*2
#define PLAYER_SIZEY (CHIPSIZE_Y*3)*2
#define PLAYER_FALL_SPEED_MAX 15.0f


struct PLAYER
{
	float		frame;	//�v���C���[�̃t���[��
	Float2		pos;	//�v���C���[�̌��݈ʒu
	Float2		vec;	//�v���C���[�̃x�N�g��
	Float2		spjp;	//�v���C���[�̈ړ��ƃW�����v���x
	Float2		jp;		//�v���C���[�̃W�����v����
};

struct CURSOR
{
public:
	Float2		pos;
	Float2		prev_pos;
	D3DXCOLOR	color;

	//bool		csInp;	//�J�[�\�����͔��ʗp
	bool		use;
};

static PLAYER g_Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
bool CompositionAkari(int clossStart, int clossGoal);
PLAYER* GetPlayer(void);
void plus_hissatuwaza(int index);



//PLAYER* GetPlayer(void);
