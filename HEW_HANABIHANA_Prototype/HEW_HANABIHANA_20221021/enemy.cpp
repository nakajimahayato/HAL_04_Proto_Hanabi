/*==============================================================================

   �G�l�~�[���� [enemy.cpp]
														 Author : 
														 Date   : 2022/10/23
--------------------------------------------------------------------------------

==============================================================================*/
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void EnemyStateChase(int index);
void EnemyStateRest(int index);
void EnemyStateGoHome(int index);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_TextureNo;//�^�C�g����ʗp�e�N�X�`���̎��ʎq
//static int g_BGMNo;		//�^�C�g���pBGM�̎��ʎq
static ENEMY g_Enemy[NUM_ENEMY]; //�G�o�b�t�@

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitEnemy(void)
{
	//�e�N�X�`����ǂݍ���Ŏ��ʎq���󂯎��
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/spider0916.png");

	//�G�o�b�t�@�̏�����
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		g_Enemy[i].pos = D3DXVECTOR2(0.0f, 0.0f);		//�\�����W
		g_Enemy[i].dir = D3DXVECTOR2(0.0f, 0.0f);		//�ړ����@
		g_Enemy[i].speed = 0.0f;
		g_Enemy[i].state = ES_CHASE;//������Ԃ͒ǂ��������
		g_Enemy[i].frame = 0.0f;

		g_Enemy[i].use = false;
	}

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void UninitEnemy(void)
{


}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void UpdateEnemy(void)
{
	//�G�o�b�t�@�S�̂𑖍�����
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		//���t���O���I���̓G�������W���X�V����
		if (g_Enemy[i].use == true)
		{
			switch (g_Enemy[i].state)
			{
			case ES_CHASE:
				EnemyStateChase(i);
				break;
			case ES_REST:
				EnemyStateRest(i);
				break;
			case ES_RETURN:
				EnemyStateGoHome(i);
				break;
			case ES_NONE:
				break;
			}
			//���Ԍo��
			g_Enemy[i].frame += 1.0f;

			g_Enemy[i].dir = GetPlayer()->pos - g_Enemy[i].pos;
			D3DXVec2Normalize(&g_Enemy[i].dir, &g_Enemy[i].dir);

			//�G�̍��W�X�V
			g_Enemy[i].pos += g_Enemy[i].dir * g_Enemy[i].speed;
		}
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void DrawEnemy(void)
{
	//�x�[�X���W���擾����
	D3DXVECTOR2 basePos = GetBase();

	//�G�o�b�t�@�S�̂𑖍�����
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		//���t���O���I���̒e�����`�悷��
		if (g_Enemy[i].use == true)
		{
			float rot;

			//�ړ����������]�p�x�����߂�
			rot = atan2f(g_Enemy[i].dir.y, g_Enemy[i].dir.x) - (D3DX_PI / 2);

			DrawSpriteColorRotate(g_TextureNo, basePos.x + g_Enemy[i].pos.x, basePos.y + g_Enemy[i].pos.y,
				32.0f, 32.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				rot);
		}
	}



}
void SetEnemy(D3DXVECTOR2 pos, int muki)
{
	//�G�o�b�t�@�S�̂𑖍�����
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		//���t���O���I�t�̓G��T��
		if (g_Enemy[i].use == false)
		{
			g_Enemy[i].startPos = pos;
			g_Enemy[i].pos = g_Enemy[i].startPos;

			switch (muki)
			{
			case 0://�����
				g_Enemy[i].dir = D3DXVECTOR2(0.0f, -1.0f);
				break;
			case 1://�E����
				g_Enemy[i].dir = D3DXVECTOR2(1.0f, 0.0f);
				break;
			case 2://������
				g_Enemy[i].dir = D3DXVECTOR2(0.0f, 1.0f);
				break;
			case 3://������
				g_Enemy[i].dir = D3DXVECTOR2(-1.0f, 0.0f);
				break;
			}
			g_Enemy[i].speed = 0.5f;

			//������Ԃ͑ҋ@
			g_Enemy[i].state = ES_REST;

			//���t���O���I���ɂ���
			g_Enemy[i].use = true;

			//�G����Z�b�g������I��������
			break;
		}
	}
}