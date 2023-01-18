/*==============================================================================

				   �G�l�~�[���� [enemy.cpp]


------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/

#include "enemy.h"
#include "input.h"
#include "score.h"
#include "stage.h"
#include "kappa_Enemy.h"

//*****************************************************************************			
// �}�N����`			
//*****************************************************************************			
#define KAPPA_SIZE_X (CHIPSIZE_X*3)
#define KAPPA_SIZE_Y (CHIPSIZE_Y*6)



//*****************************************************************************			
// �v���g�^�C�v�錾			
//*****************************************************************************			

//*****************************************************************************			
// �O���[�o���ϐ�			
//*****************************************************************************			
static int g_TexKappa;
static EnemyObject g_Kappa[NUM_ENEMY];

static float g_shrinkAmount[NUM_ENEMY];
static float g_shrinkSize[NUM_ENEMY];
bool KappaFollow;



//=============================================================================			
// ����������			
//=============================================================================			
HRESULT InitKappaEnemy(void)
{
	g_TexKappa = LoadTexture((char*)"data/TEXTURE/youkai_kappa.png");
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		//�͓��̏�����
		g_Kappa[i].frame = 0.0f;
		g_Kappa[i].use = false;
		/*���āI�I*/g_Kappa[i].pos = {2000,SCREEN_HEIGHT/2 };//�ǂ��ɂ���H
		g_Kappa[i].speed = ENEMY_WALK_SPEED;
		g_Kappa[i].siz = { KAPPA_SIZE_X,KAPPA_SIZE_Y};
		g_Kappa[i].fall = false;
		g_Kappa[i].sdrop.y = ENEMY_FALL_SPEED;
		g_Kappa[i].Health = ENEMY_HEALTH;
		g_Kappa[i].Attack = 10;

		g_shrinkAmount[i] = 1.0f;
		g_shrinkSize[i] = 1.0f;
		KappaFollow = false;
	}

	//�e�X�g
	g_Kappa[0].use = true;
	//

	return S_OK;
}

//=============================================================================			
// �I������			
//=============================================================================			
void UninitKappaEnemy(void)
{

}

//=============================================================================			
// �X�V����			
//=============================================================================			
void UpdateKappaEnemy(void)
{
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		g_Kappa[i].frame++;
		
		if (g_Kappa[i].use)
		{
			//���U�����e�X�g
			if (GetKeyboardTrigger(DIK_L))
			{
				g_Kappa[i].Health = 0;
			}
			if (g_Kappa[i].Health <= 0)
			{
				KappaEnemyDeadProcess(i);
			}

			/*���āI�I*/	//�ʏ�U��

			//�v���C���[�ɋ߂Â�
			//�C�F�����B���Ƀv���C���[�𔭌������ꍇ�͇@�ɍs��
			if (KappaFollow==false)
			{
				//�A�F�v���C���[�����G�͈͂��痣�ꂽ�Ƃ��A�ړ����~����B
				if (HitCheckCircleSq(GetPlayer()->pos, 1, g_Kappa[i].pos, CHIPSIZE_X * 10))
				{
					KappaFollow = true;
				}
			}
			else
			{
				if (!HitCheckCircleSq(GetPlayer()->pos, 1, g_Kappa[i].pos, CHIPSIZE_X * 15))
				{
					KappaFollow = false;
				}
			}

			if (KappaFollow)
			{
				//�@�F�v���C���[�����G�͈͂ɓ�����������A��Ƀv���C���[�̔��a6�}�X�ȓ���ڊ|���Ĉړ�����B
				if (GetPlayer()->pos.x + (CHIPSIZE_X * 6) < g_Kappa[i].pos.x)
				{
					g_Kappa[i].pos.x -= g_Kappa[i].speed;
				}
				else if (GetPlayer()->pos.x - (CHIPSIZE_X * 6) > g_Kappa[i].pos.x)
				{
					g_Kappa[i].pos.x += g_Kappa[i].speed;
				}
			}
			else
			{
				//�B�F����"�A"���ɕ����G�l�~�[���|����Ă���̂����m�����ꍇ�A�����G�l�~�[������X���W�ɍs���A�����G�l�~�[�𐶐�����
				if (/*�����G�l�~�[���|����Ă���*/GetSPEnemy()->isSPEnemydead)
				{
					if (GetSPEnemy()->pos.x < g_Kappa[i].pos.x)
					{
						g_Kappa[i].pos.x -= g_Kappa[i].speed;
					}
					else if (GetSPEnemy()->pos.x > g_Kappa[i].pos.x)
					{
						g_Kappa[i].pos.x += g_Kappa[i].speed;
					}
				}
			}

			//��������
			if (g_Kappa[i].fall == true) {
				g_Kappa[i].drop.y += g_Kappa[i].sdrop.y;
				g_Kappa[i].pos.y += g_Kappa[i].drop.y;
			}

			if (g_Kappa[i].pos.y > SCREEN_HEIGHT) {
				g_Kappa[i].use = false;
			}

			//�G�l�~�[�ƒn�ʂ̔���
			if (GetStageInfoEnemySITA(g_Kappa[i].pos, Float2(KAPPA_SIZE_X, KAPPA_SIZE_Y)))
			{
				//������ɓ���������
				if (GetStageInfoEnemySITA(g_Kappa[i].pos, Float2(KAPPA_SIZE_X, KAPPA_SIZE_Y)) == -1)
				{
					g_Kappa[i].fall = false;
					if (KappaFollow)
					{
						if (GetPlayer()->pos.x < g_Kappa[i].pos.x)
						{
							g_Kappa[i].pos.x -= g_Kappa[i].speed * 2;
						}
						else if (GetPlayer()->pos.x > g_Kappa[i].pos.x)
						{
							g_Kappa[i].pos.x += g_Kappa[i].speed * 2;
						}
					}
					else
					{
						if (GetSPEnemy()->pos.x < g_Kappa[i].pos.x)
						{
							g_Kappa[i].pos.x -= g_Kappa[i].speed * 2;
						}
						else if (GetSPEnemy()->pos.x > g_Kappa[i].pos.x)
						{
							g_Kappa[i].pos.x += g_Kappa[i].speed * 2;
						}
					}
					

					if (GetStageInfoEnemySITA({ g_Kappa[i].pos.x,g_Kappa[i].pos.y-CHIPSIZE_Y }, Float2(KAPPA_SIZE_X, KAPPA_SIZE_Y)))
					{
						g_Kappa[i].pos.y -= CHIPSIZE_Y;
					}
					
				}
				else
				{
					g_Kappa[i].drop.y = 0.0f;
					g_Kappa[i].pos.y = GetStageInfoEnemySITA(g_Kappa[i].pos, Float2(KAPPA_SIZE_X, KAPPA_SIZE_Y)) - (KAPPA_SIZE_Y / 2 + CHIPSIZE_Y / 2);
					g_Kappa[i].fall = false;
				}
				
			}
			else
			{
				//�u���b�N���Ȃ�����
				g_Kappa[i].fall = true;
			}
		}
	}
}

//=============================================================================			
// �`�揈��			
//=============================================================================			
void DrawKappaEnemy(void)
{
	//�x�[�X���W���擾����
	D3DXVECTOR2 basePos = GetBase();

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (g_Kappa[i].use)
		{
			if (g_Kappa[i].Health <= 0)//���˂݁[��HP���O�̎�
			{
				DrawSprite(g_TexKappa, basePos.x + g_Kappa[i].pos.x, basePos.y + g_Kappa[i].pos.y *g_shrinkSize[i],
					KAPPA_SIZE_X*g_shrinkAmount[i], KAPPA_SIZE_Y*g_shrinkAmount[i],
					1.0f, 1.0f,
					1.0f, 1.0f);
			}
			else
			{
				DrawSprite(g_TexKappa, basePos.x + g_Kappa[i].pos.x, basePos.y + g_Kappa[i].pos.y,
					KAPPA_SIZE_X, KAPPA_SIZE_Y,
					1.0f, 1.0f,
					1.0f, 1.0f);
			}
		}
	}
}

EnemyObject* GetKappaEnemy()
{
	return g_Kappa;
}

void KappaEnemyDeadProcess(int i)//�g�o��0�ɂȂ����ꍇ�A1.3�b�قǂ����Ď��k���U���A���͂ɂ�������܂��U�炷�����k�͉��A�����Ƃ���0.75�{�ɂȂ�
{
	if (g_Kappa[i].Health <= 0.0f && (int)g_Kappa[i].frame % 3 == 0 && g_Kappa[i].use)//�g�o��0�ɂȂ����ꍇ���t���[�����R�i�ނ���
	{
		if (g_shrinkAmount[i] < 0.75f)//���k�͉��A�����Ƃ���0.75�{�ɂȂ�
		{
			if ((int)g_Kappa[i].frame % 60 == 0)
			{
				//�Z�b�g������
				SetAkari(g_Kappa[i].pos, 0);

				g_Kappa[i].use = false;
				g_shrinkAmount[i] = 1.0f;
			}
		}
		else
		{
			g_shrinkAmount[i] -= 0.01f;
			g_shrinkSize[i] += 0.00105f;
		}

	}
}