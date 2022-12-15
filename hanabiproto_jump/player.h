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
#define PLAYER_SIZEX (CHIPSIZE_X * 1)  //
#define PLAYER_SIZEY (CHIPSIZE_Y * 3)  //192
#define PLAYER_FALL_SPEED_MAX 15.0f
#define PLAYER_ACCELERATION_X 0.5f //�v���C���[�̉������x
#define PLAYER_SPEEDMAX_X 8.0f //�v���C���[�̍ő呬�x
#define PLAYER_BRAKE 0.4 //�n�ʂƂ̖��C
#define PLAYER_MAXHP 30	
#define PLAYER_HP_PRINT 30	
#define PLAYER_HP_HEALFRAME  1//�񕜂��鑬�x
#define PLAYER_HP_HEAL 0.033333
#define PLAYER_RESPAWN_X 60	// �v���C���[�̃��X�|�[���n�_X
#define PLAYER_RESPAWN_Y 19 // �v���C���[�̃��X�|�[���n�_Y


struct PLAYER
{
	int		frame;	//�v���C���[�̃t���[��
	Float2		pos;	//�v���C���[�̌��݈ʒu
	Float2      oldpos; //�v���C���[�̉ߋ��̈ʒu
	Float2		vec;	//�v���C���[�̃x�N�g��
	Float2		spjp;	//�v���C���[�̈ړ��ƃW�����v���x
	//Float2      acceleration;//�v���C���[�̉����x
	Float2		jp;		//�v���C���[�̃W�����v����
	float			hp;
	int			hpframe;
	int			maxframe;
	int			respawnframe;
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
void HP_Minus(float damage);
void HP_Plus(float healing);


//PLAYER* GetPlayer(void);
