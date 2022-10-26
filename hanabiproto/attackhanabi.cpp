/*==============================================================================

   �U���ԉ΂̏��� [attackhanabi.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "object.h"
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_HANABI 100

//�e�̃f�[�^���Ǘ�����\����
struct AtHANABI
{
	D3DXVECTOR2 pos;	//�\�����W
	D3DXVECTOR2 dir;	//�ړ�����
	float       speed;	//�ړ����x
	float		frame;	//��������

	int			use;	//���t���O
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void HitHanabi(bool isHit);
void CreateHanabi(Float2 plpos, Float2 cspos);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static GameObject g_Hanabi0bj;
static EnemyObject g_Enemy0bj;

static GameObject g_Objects[256];
static PLAYER g_Player;	//�v���C���[�p

static int g_AtHanabi;	//�U���ԉΗp�̃e�N�X�`���̎��ʎq
static AtHANABI g_HANABI[NUM_HANABI];	//�e�o�b�t�@
//=============================================================================
// ����������
//=============================================================================
HRESULT InitAtHanabi(void)
{
	//------------��--------------------

	//�e�N�X�`����ǂݍ���Ŏ��ʎq���󂯎��
	g_AtHanabi = LoadTexture((char*)"data/TEXTURE/bullet00.png");


	//�ԉ΃o�b�t�@�̏�����
	for (int i = 0; i < NUM_HANABI; i++)
	{
		g_HANABI[i].pos = D3DXVECTOR2(0.0f, 0.0f);	//�\�����W
		g_HANABI[i].dir = D3DXVECTOR2(0.0f, 0.0f);	//�ړ�����
		g_HANABI[i].speed = 0.0f;					//�ړ����x

		g_HANABI[i].use = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitAtHanabi(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateAtHanabi(void)
{
	//------------��--------------------

	//�ԉ΃o�b�t�@�S�̂𑖍�����
	for (int i = 0; i < NUM_HANABI; i++)
	{
		//���t���O���I���̉ԉ΂������W���X�V����
		if (g_HANABI[i].use == true)
		{
			//�ԉ΂̍��W�X�V
			g_HANABI[i].pos += g_HANABI[i].dir * g_HANABI[i].speed;

			g_HANABI[i].frame += 1.0f;

			//180�t���[���o�߂�����
			if (g_HANABI[i].frame > 180.0f)
			{
				//�ԉ΂���ʂ���폜����
				g_HANABI[i].use = false;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawAtHanabi(void)
{

	//------------��--------------------

	//�x�[�X���W���擾����
	D3DXVECTOR2 basePos = GetBase();


	//�ԉ΃o�b�t�@�S�̂𑖍�����
	for (int i = 0; i < NUM_HANABI; i++)
	{
		//���t���O���I���̉ԉ΂����`�悷��
		if (g_HANABI[i].use == true)
		{
			float rot;

			//�ړ����������]�p�x�����߂�
			rot = atan2f(g_HANABI[i].dir.y, g_HANABI[i].dir.x) + (D3DX_PI / 2);

			DrawSpriteColorRotate(g_AtHanabi, basePos.x + g_HANABI[i].pos.x, basePos.y + g_HANABI[i].pos.y,
				32.0f, 32.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				rot);
		}
	}
}


//=============================================================================
// �U���ԉ΂̈ړ�����
//=============================================================================
void MoveHanabi(void)
{


}
void MoveHanabiAI(void)
{

}

//=============================================================================
// �U���ԉ΂̓����蔻�菈��
//=============================================================================
void HitHanabi(bool isHit)
{
	//if (g_Hanabi0bj.pos.x == g_Enemy0bj.pos.x || g_Hanabi0bj.pos.y == g_Enemy0bj.pos.y)
	//{
	//	isHit = true;
	//}
	
}
void CreateHanabi(Float2 plpos, Float2 cspos)
{
	g_Player.pos = plpos;
	g_Player.cspos = cspos;


	//------------��--------------------

	//�ԉ΃o�b�t�@�S�̂𑖍�����
	for (int i = 0; i < NUM_HANABI; i++)
	{
		//���t���O���I�t�̉ԉ΂�T��
		if (g_HANABI[i].use == false)
		{
			g_HANABI[i].pos = plpos;

			switch ()
			{
			case 0://�����
				g_HANABI[i].dir = D3DXVECTOR2(0.0f, -1.0f);
				break;
			case 1://�E����
				g_HANABI[i].dir = D3DXVECTOR2(1.0f, 0.0f);
				break;
			case 2://������
				g_HANABI[i].dir = D3DXVECTOR2(0.0f, 1.0f);
				break;
			case 3://������
				g_HANABI[i].dir = D3DXVECTOR2(-1.0f, 0.0f);
				break;
			}

			g_HANABI[i].speed = 6.0f;

			//���t���O���I���ɂ���
			g_HANABI[i].use = true;

			//�������Ԃ����Z�b�g����
			g_HANABI[i].frame = 0.0f;

			//�ԉ΂���Z�b�g������I��������
			break;
		}
	}
}