/*==============================================================================

			 �@�K�E������Ǘ�[akari_ex.h] [akariobject.cpp]
				Author : �~�J�~
				Date    : 2022/10/23(�ŏI�ҏW��)
------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#include "akari_ex.h"
#include "texture.h"
#include "collision.h"
#include "sprite.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "stage.h"


//*****************************************************************************							
// �}�N����`							
//*****************************************************************************							
//*****************************************************************************							
// �v���g�^�C�v�錾							
//*****************************************************************************							

//*****************************************************************************							
// �O���[�o���ϐ�							
//*****************************************************************************							
static int g_TextureNo;

static EX_AkariObject g_EX_AkariObject[EX_AKARI_NUM];

static float g_U, g_V;

Float2 ExMovePos[EX_AKARI_NUM];

Float2 ExPpos;

bool g_ex_composition;

D3DXCOLOR GatherExColor;

//=============================================================================							
// ����������							
//=============================================================================							
HRESULT InitExAkariObject(void)
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/proto_effect_akari.png");

	//������
	for (int i = 0; i < EX_AKARI_NUM; i++)
	{
		g_EX_AkariObject[i].use = false;
		g_EX_AkariObject[i].gather = false;
		g_EX_AkariObject[i].setvec = false;
		g_EX_AkariObject[i].dir.x = 0.0f;
		g_EX_AkariObject[i].dir.y = 0.0f;
		g_EX_AkariObject[i].pos.x = SCREEN_WIDTH;
		g_EX_AkariObject[i].pos.y = SCREEN_HEIGHT;
		g_EX_AkariObject[i].frame = 0;
		g_EX_AkariObject[i].color = { 1.0f,1.0f,1.0f,1.0f };
		g_EX_AkariObject[i].siz = { 32.0f,32.0f };
		g_EX_AkariObject[i].drop.x = 0.0f;
		g_EX_AkariObject[i].drop.y = 0.0f;
		g_EX_AkariObject[i].sdrop.x = 0.0f;
		g_EX_AkariObject[i].sdrop.y = 0.0f;
		g_EX_AkariObject[i].vec.x = 0.0f;
		g_EX_AkariObject[i].vec.y = 0.0f;
		g_EX_AkariObject[i].speed = 1.0f;

		g_EX_AkariObject[i].color = EX_COLOR_NONE;

		ExMovePos[i] = { 0.0f,0.0f };

		g_EX_AkariObject[i].gatherpos = { 0.0f,0.0f };
		g_EX_AkariObject[i].follow = false;

	}

	g_U = 0.0f;
	g_V = 0.0f;

	g_ex_composition = true;

	GatherExColor = { 0.0f,0.0f,0.0f,1.0f };

	return S_OK;
}

//=============================================================================							
// �I������							
//=============================================================================							
void UninitExAkariObject(void)
{

}

//=============================================================================							
// �X�V����							
//=============================================================================							
void UpdateExAkariObject(void)
{
	//�e�X�g
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		for (int i = 0; i < EX_AKARI_NUM; i++)
		{
			if (g_EX_AkariObject[i].use == false)
			{
				g_EX_AkariObject[i].use = true;
				g_EX_AkariObject[i].gather = false;
				g_EX_AkariObject[i].pos.x = frand() * SCREEN_WIDTH;
				g_EX_AkariObject[i].pos.y = frand() * SCREEN_HEIGHT;
				break;
			}
		}
	}

	//�e���˃e�X�g
	/*if (GetKeyboardTrigger(DIK_G))
	{
		SetAkari(GetPlayer()->pos, { 1.0f,-1.0f }, 1.5f);
	}*/
	//�e�X�g�I���



	//������ړ�����
	for (int i = 0; i < EX_AKARI_NUM; i++)
	{
		//�͂����͈͓��́uAKARI�v���W�܂�悤��
		if ((g_EX_AkariObject[i].gather == true) && (g_EX_AkariObject[i].use == true) && (g_EX_AkariObject[i].setvec == false) && (ExPpos.x != GetPlayer()->pos.x) && (ExPpos.y != GetPlayer()->pos.y))
		{
			//�n�_A����n�_B�̈ړ�����
			//MovePos=�n�_B - �n�_A;
			ExMovePos[i] = Centergather(g_EX_AkariObject[i].gatherpos, g_EX_AkariObject[i].gatherpos, g_EX_AkariObject[i].gatherpos, g_EX_AkariObject[i].gatherpos) - g_EX_AkariObject[i].pos;
			//���t���[�������ďW�܂邩
			ExMovePos[i].x /= (60 / (g_EX_AkariObject[i].frame + 1 * 5));
			ExMovePos[i].y /= (60 / (g_EX_AkariObject[i].frame + 1 * 5));

			//g_AkariObject[i].setvec = true;
		}


		//�W�܂�EX������̍��W�X�V
		if (g_EX_AkariObject[i].gather && g_EX_AkariObject[i].use)
		{
			g_EX_AkariObject[i].pos.x += ExMovePos[i].x;
			g_EX_AkariObject[i].pos.y += ExMovePos[i].y;

			if (g_EX_AkariObject[i].pos.x < g_EX_AkariObject[i].gatherpos.x + 19 && g_EX_AkariObject[i].pos.x > g_EX_AkariObject[i].gatherpos.x - 19
				&& g_EX_AkariObject[i].pos.y < g_EX_AkariObject[i].gatherpos.y + 19 && g_EX_AkariObject[i].pos.y > g_EX_AkariObject[i].gatherpos.y - 19)
			{
				ExMovePos[i].x = 0.0f;
				ExMovePos[i].y = 0.0f;
				g_EX_AkariObject[i].frame += 1;


				//��������Ł[�[�[
				if (g_EX_AkariObject[i].frame > 40)
				{
					for (int j = 0; j < EX_AKARI_NUM; j++)
					{
						if ((g_EX_AkariObject[j].gather == true) && (g_EX_AkariObject[j].use == true))
						{
							g_EX_AkariObject[j].use = false;
							g_EX_AkariObject[j].frame = 0;

						}
					}
				}
			}
		}
		//�͈͓��Ƀv���C���[�������Ƃ��̂�����̍��W�X�V
		else if ((g_EX_AkariObject[i].follow == true) && (g_EX_AkariObject[i].use == true))
		{
			ExMovePos[i] = Centergather(GetPlayer()->pos, GetPlayer()->pos, GetPlayer()->pos, GetPlayer()->pos) - g_EX_AkariObject[i].pos;
			//���t���[�������ďW�܂邩
			/*ExMovePos[i].x /= (EX_AKARI_FOLLOW_SPEED / (g_EX_AkariObject[i].frame + 1 * 5));
			ExMovePos[i].y /= (EX_AKARI_FOLLOW_SPEED / (g_EX_AkariObject[i].frame + 1 * 5));*/

			ExMovePos[i].x /= EX_AKARI_FOLLOW_SPEED;
			ExMovePos[i].y /= EX_AKARI_FOLLOW_SPEED;

			g_EX_AkariObject[i].pos.x += ExMovePos[i].x;
			g_EX_AkariObject[i].pos.y += ExMovePos[i].y;

			//�v���C���[�ƐڐG��
			if (g_EX_AkariObject[i].pos.x < GetPlayer()->pos.x + 19 && g_EX_AkariObject[i].pos.x > GetPlayer()->pos.x - 19
				&& g_EX_AkariObject[i].pos.y <GetPlayer()->pos.y + 19 && g_EX_AkariObject[i].pos.y > GetPlayer()->pos.y - 19)
			{
				ExMovePos[i].x = 0.0f;
				ExMovePos[i].y = 0.0f;
				g_EX_AkariObject[i].frame += 1;

				//��������Ł[�[�[
				if (g_EX_AkariObject[i].frame > 40)
				{
					for (int j = 0; j < EX_AKARI_NUM; j++)
					{
						if ((g_EX_AkariObject[j].gather == true) && (g_EX_AkariObject[j].use == true))
						{
							g_EX_AkariObject[j].use = false;
							g_EX_AkariObject[j].frame = 0;
							//plus_hissatuwaza(5);
						}
					}
				}
			}
		}
		//�W�܂�Ȃ�������̍��W�X�V
		else if (g_EX_AkariObject[i].use == true)
		{
			//�����鑬��
			g_EX_AkariObject[i].drop.y = 0.5f;

			g_EX_AkariObject[i].frame += 1;


			//����������̒��S���J�̃}�b�v�`�b�v�ɓ���������t���[������
			if (GetStageInfoRain(g_EX_AkariObject[i].pos)) {
				g_EX_AkariObject[i].frame = 500;
			}

			////�e����ԕ�
			//����̃t���[����ɏd�͔���
			if (g_EX_AkariObject[i].frame >= 80)
			{
				g_EX_AkariObject[i].pos.y += g_EX_AkariObject[i].drop.y * 2;
			}

			//�����ł������Ł[�[�[
			if (g_EX_AkariObject[i].frame >= 2000 || g_EX_AkariObject[i].pos.y > 1500)
			{
				g_EX_AkariObject[i].use = false;
				g_EX_AkariObject[i].frame = 0;
				g_EX_AkariObject[i].hitground = false;
			}
		}
	}

	for (int i = 0; i < EX_AKARI_NUM; i++)
	{
		if ((g_EX_AkariObject[i].use == true) && (g_EX_AkariObject[i].gather == false) && (g_EX_AkariObject[i].frame >= 80))
		{
			if (HitCheckCircleSq(GetPlayer()->pos, PLAYER_SIZEX, g_EX_AkariObject[i].pos, EX_AKARI_SEARCH_DIST)) {
				g_EX_AkariObject[i].follow = true;
			}
			else {
				g_EX_AkariObject[i].follow = false;
			}
		}
	}
}

//=============================================================================							
// �`�揈��							
//=============================================================================							
void DrawExAkariObject(void)
{
	//�x�[�X���W���擾����
	D3DXVECTOR2 basePos = GetBase();
	for (int i = 0; i < EX_AKARI_NUM; i++)
	{
		if (g_EX_AkariObject[i].use == true)
		{
			DrawSpriteColor(g_TextureNo, basePos.x + g_EX_AkariObject[i].pos.x, basePos.y + g_EX_AkariObject[i].pos.y, 80.0f, 80.0f,
				1.0f, 1.0f, 1.0f, 1.0f, g_EX_AkariObject[i].color);
		}
	}

}

//����:�J�b�v������̍��W,�F�̎�� (���ꂼ��true��false��),
//�U���̎��(�v���C���[�_���[�W0.�G�l�~�[�_���[�W1,����2),
//������̌�(�ő�300),�����{��,�F�̕���
void SetExAkariBase(Float2 pos, bool red, bool green, bool blue, int damagetype, int akarinum, float speed, EX_COLOR color)
{
	int create_akari = min(akarinum, 300); //�ő�300����

	for (int i = 0; i < EX_AKARI_NUM; i++)
	{
		if (g_EX_AkariObject[i].use == false)
		{
			switch (damagetype)
			{
			case 0:
				g_EX_AkariObject[i].damageplayerflug = true;
				g_EX_AkariObject[i].damageenemyflug = false;
				break;
			case 1:
				g_EX_AkariObject[i].damageplayerflug = false;
				g_EX_AkariObject[i].damageenemyflug = true;
				break;
			case 2:
				g_EX_AkariObject[i].damageplayerflug = true;
				g_EX_AkariObject[i].damageenemyflug = true;
				break;
			default:
				break;
			}
			g_EX_AkariObject[i].use = true;
			g_EX_AkariObject[i].pos = pos;
			g_EX_AkariObject[i].setvec = false;
			g_EX_AkariObject[i].gather = false;
			g_EX_AkariObject[i].vec.y = 0.0f;
			g_EX_AkariObject[i].hitground = false;

			//�����鑬��
			g_EX_AkariObject[i].drop.y = 0.01f;
			//�����x
			g_EX_AkariObject[i].sdrop.y = 0.03f;

			ExMovePos[i] = Float2{ 0.0f,0.0f };
			//�F�Â�
			{
				float RGB[3];
				for (int j = 0; j < 3; j++)
				{
					RGB[j] = frand() / 3;
				}
				if (red == true) {
					RGB[0] = 1.0f;
				}
				if (green == true) {
					RGB[1] = 1.0f;
				}
				if (blue == true) {
					RGB[2] = 1.0f;
				}
				g_EX_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
				g_EX_AkariObject[i].ex_color = color;

				break;
			}
		}
	}
}

void SetExAkari(Float2 pos, EX_COLOR color)
{
	switch (color)
	{
	case EX_COLOR_NONE:
		break;
	case EX_COLOR_RED:
		SetExAkariBase(pos, true, false, false, 1, 5, 1.5, EX_COLOR_RED);
		break;
	case EX_COLOR_BLUE:
		SetExAkariBase(pos, false, false, true, 1, 5, 1.5, EX_COLOR_BLUE);
		break;
	case EX_COLOR_GREEN:
		SetExAkariBase(pos, false, true, false, 1, 5, 1.5, EX_COLOR_GREEN);
		break;
	case EX_COLOR_CYAN:
		SetExAkariBase(pos, false, true, true, 1, 5, 1.5, EX_COLOR_CYAN);
		break;
	case EX_COLOR_MAGENTA:
		SetExAkariBase(pos, true, false, true, 1, 5, 1.5, EX_COLOR_MAGENTA);
		break;
	case EX_COLOR_YELLOW:
		SetExAkariBase(pos, true, true, false, 1, 5, 1.5, EX_COLOR_YELLOW);
		break;
	case EX_COLOR_WHITE:
		SetExAkariBase(pos, true, true, true, 1, 5, 1.5, EX_COLOR_WHITE);
		break;
	case EX_COLOR_NUM:
		break;
	default:
		break;
	}
}

EX_AkariObject GetExAkari(int index)
{
	return g_EX_AkariObject[index];
}

void ExAkariGather(int index, Float2 gatherpos)
{
	g_EX_AkariObject[index].gather = true;
	g_EX_AkariObject[index].frame = 0;
	g_EX_AkariObject[index].gatherpos = gatherpos - Float2{ GetBase().x, GetBase().y };
	g_EX_AkariObject[index].follow = false;
}

void ExAkariFollow(int index, bool follow)
{
	g_EX_AkariObject[index].frame = 0;
	g_EX_AkariObject[index].follow = follow;
}

void ExColorPlus(COLOR_AKARI colortype, Float2 gatherpos)
{

}
