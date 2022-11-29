
/*==============================================================================

				   �G�l�~�[���� [enemy.cpp]


------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#include "enemy.h"
#include "object.h"
#include "input.h"

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
static int g_TexCupE;

static EnemyObject g_Enemy[NUM_ENEMY];

static EnemyObject* g_pEnemy[NUM_ENEMY];//���u��
static CupEnemy cupE[NUM_CUPENEMY]; //��U���u��
static int g_nowEnemyMax;
//=============================================================================			
// ����������			
//=============================================================================			
HRESULT InitEnemy(void)
{

	g_TextureNo = LoadTexture((char*)"data/TEXTURE/enemy00.png");
	g_TexCupE = LoadTexture((char*)"data/TEXTURE/proto_effect_explosion.png");

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		g_Enemy[i].frame = 0.0f;
		g_Enemy[i].use = false;
		g_Enemy[i].pos = { SCREEN_WIDTH/2 ,SCREEN_HEIGHT/2  };
		g_Enemy[i].speed = 8.0f;
		g_Enemy[i].siz = { 32.0f,32.0f };
	}
	//������for�K�v�H���for�Ɠ����H
	for (int i = 0; i < NUM_CUPENEMY; i++)
	{
		cupE[i].frame = 0.0f;
		cupE[i].use = false;
		cupE[i].pos = { SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2 };
		cupE[i].speed = 8.0f;
	}

	/*�e�X�g*/
	g_Enemy[0].use = true;
	cupE[0].use = true;
	return S_OK;
}

//=============================================================================			
// �I������			
//=============================================================================			
void UninitEnemy(void)
{

}

//=============================================================================			
// �X�V����			
//=============================================================================			
void UpdateEnemy(void)
{
	if (GetKeyboardTrigger(DIK_F))
	{
		SetEnemy({ 640,360 }, 0, 0);
	}

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (g_Enemy[i].use)
		{
			for (int j = 0; j < 5; j++)
			{
				//�G�l�~�[�Ƃ�����̓����蔻�菈��
				if (HitCheckBox(g_Enemy[i].pos, g_Enemy[i].siz, GetAkariObject(j).pos, GetAkariObject(j).siz))
				{
					SetAkari(g_Enemy[i].pos);
					g_Enemy[i].use = false;
				}


			}
		}
	}


	for (int i = 0; i < NUM_CUPENEMY; i++)
	{
		if (cupE[i].use)
		{
			cupE[i].frame += 1;
			for (int j = 0; j < 5; j++)
			{
				////�G�l�~�[�Ƃ�����̓����蔻�菈��
				//if (HitCheckBox(g_Enemy[i].pos, g_Enemy[i].siz, GetAkariObject(j).pos, GetAkariObject(j).siz))
				//{
				//	SetAkari(g_Enemy[i].pos);
				//	g_Enemy[i].use = false;
				//}

				//6�b�Ԃ�1��葫���q���A�N�V�������N����
				if (cupE[i].frame >= 360)
				{
					cupE[i].Action();
					cupE[i].frame = 0;
				}
			}
		}
	}

	//�`�悳��Ă�葫���q����
	for (int i = 0; i < g_nowEnemyMax; i++)
	{
		if (g_pEnemy[i]->use == true)
		{
			//���ɓ�������frame��1����
			g_pEnemy[i]->pos.x += -1.0f;
			g_pEnemy[i]->frame += 1;
			//�P�b��1�񖾂�����R����΂�
			if(g_pEnemy[i]->frame >= 60)
			{
				SetAkari(g_pEnemy[i]->pos, { 0.0f,-1.0f }, 1.5f);
				SetAkari(g_pEnemy[i]->pos, { 0.5f,-1.0f }, 1.5f);
				SetAkari(g_pEnemy[i]->pos, { -0.5f,-1.0f }, 1.5f);
				g_pEnemy[i]->frame = 0;
			}
		}
	}
}

//=============================================================================			
// �`�揈��			
//=============================================================================			
void DrawEnemy(void)
{
	//�x�[�X���W���擾����
	D3DXVECTOR2 basePos = GetBase();

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (g_Enemy[i].use)
		{
			DrawSprite(g_TextureNo, basePos.x + g_Enemy[i].pos.x, basePos.y + g_Enemy[i].pos.y,
				80.0f, 80.0f,
				1.0f, 1.0f,
				1.0f, 1.0f);
		}
	}


	for (int i = 0; i < g_nowEnemyMax; i++)
	{
		if (g_pEnemy[i]->use)
		{
			DrawSprite(g_TexCupE, basePos.x + g_pEnemy[i]->pos.x, basePos.y + g_pEnemy[i]->pos.y,
				80.0f, 80.0f,
				1.0f, 1.0f,
				1.0f, 1.0f);
		}
	}
	
}

EnemyObject* GetEnemy()
{
	return g_Enemy;
}

void CupEnemy::Action()
{
	SetAkari(pos);
}

//----------------------------------
// �G�l�~�[�̃Z�b�g����
//----------------------------------
//0�Ȃ�
//1�Ȃ�
//2�Ȃ�...(����)
void SetEnemy(Float2 pos, int saidai, int enemytype)
{
	switch (enemytype)
	{
	case 0:
		g_pEnemy[g_nowEnemyMax] = new CupEnemy;
		g_pEnemy[g_nowEnemyMax]->use = true;
		g_pEnemy[g_nowEnemyMax]->pos = pos;
		g_pEnemy[g_nowEnemyMax]->vec.x = 0.0f;
		g_pEnemy[g_nowEnemyMax]->vec.y = 0.0f;
		g_pEnemy[g_nowEnemyMax]->siz = { 32.0f,32.0f };
		g_pEnemy[g_nowEnemyMax]->frame = 0.0f;
		g_nowEnemyMax += 1;
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}