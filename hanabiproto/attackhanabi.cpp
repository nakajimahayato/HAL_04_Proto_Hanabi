/*==============================================================================

   �U���ԉ΂̏��� [attackhanabi.cpp]
														 Author : ���c���
														 Date   : 2022/10/26
--------------------------------------------------------------------------------

==============================================================================*/
#include "object.h"
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_HANABI 100

//�e�̃f�[�^���Ǘ�����\����
struct AtHANABI
{
	Float2 pos;	//�\�����W
	Float2 dir;	//�ړ�����
	float       speed;	//�ړ����x
	float		frame;	//��������
	Float2		vec;

	bool			use;	//���t���O
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

//static GameObject g_Objects[256];
//static PLAYER g_Player;	//�v���C���[�p

static int g_AtHanabi;	//�U���ԉΗp�̃e�N�X�`���̎��ʎq
static AtHANABI g_HANABI[NUM_HANABI];	//�e�o�b�t�@
Float2 MovePosHanabi[NUM_HANABI];
D3DXVECTOR2 g_Test;
Float2 AtHanabiDeadPos[NUM_HANABI];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitAtHanabi(void)
{
	//------------��--------------------

	//�e�N�X�`����ǂݍ���Ŏ��ʎq���󂯎��
	g_AtHanabi = LoadTexture((char*)"data/TEXTURE/proto_effect_attack.png");
	g_Test = { 3.0f,3.0f };

	//�ԉ΃o�b�t�@�̏�����
	for (int i = 0; i < NUM_HANABI; i++)
	{
		g_HANABI[i].pos = Float2(0.0f, 0.0f);	//�\�����W
		g_HANABI[i].dir = Float2(0.0f, 0.0f);	//�ړ�����
		g_HANABI[i].speed = 3.0f;					//�ړ����x
		g_HANABI[i].frame = 0.0f;

		g_HANABI[i].use = true;
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
	if (GetKeyboardPress(DIK_C))
	{
		//�e�o�b�t�@�S�̂𑖍�����
		for (int i = 0; i < NUM_HANABI; i++)
		{
			//���t���O���I���̒e�������W���X�V����
			if (g_HANABI[i].use == true)
			{
				//�e�̍��W�X�V
				//g_HANABI[i].pos += g_HANABI[i].dir * g_HANABI[i].speed;
				g_HANABI[i].pos += g_Test;


				g_HANABI[i].frame += 1.0f;

				if (g_HANABI[i].frame > 50.0f)
				{
					g_HANABI[i].frame = 0.0f;
					AtHanabiDeadPos[i] = g_HANABI[i].pos;
					g_HANABI[i].use = false;

					SetAkari(g_HANABI[i].pos);
				}
			}
		}
	}



	

	//�ԉ΃o�b�t�@�S�̂𑖍�����
	//for (int i = 0; i < NUM_HANABI; i++)
	//{
	//	//���t���O���I���̉ԉ΂������W���X�V����
	//	if (g_HANABI[i].use == true)
	//	{
	//		//�ԉ΂̍��W�X�V
	//		g_HANABI[i].pos += g_HANABI[i].dir * g_HANABI[i].speed;

	//		g_HANABI[i].frame += 1.0f;

	//		//180�t���[���o�߂�����
	//		if (g_HANABI[i].frame > 180.0f)
	//		{
	//			//�ԉ΂���ʂ���폜����
	//			g_HANABI[i].use = false;
	//		}
	//	}
	//}
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
//void MoveHanabi(void)
//{
//	MovePosHanabi[0].x = SCREEN_WIDTH / 2 - GetPlayer()->pos.x;
//	MovePosHanabi[0].y = SCREEN_HEIGHT / 2 - GetPlayer()->pos.y;
//	//���t���[�������ďW�܂邩
//	MovePosHanabi[0].x /= 60;
//	MovePosHanabi[0].y /= 60;
//
//}

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
	plpos - cspos;


	//------------��--------------------

	//�ԉ΃o�b�t�@�S�̂𑖍�����
	//for (int i = 0; i < NUM_HANABI; i++)
	//{
		//���t���O���I�t�̉ԉ΂�T��
	//	if (g_HANABI[i].use == false)
	//	{
	//		g_HANABI[i].pos = plpos;

	//		switch ()
	//		{
	//		case 0://�����
	//			g_HANABI[i].dir = D3DXVECTOR2(0.0f, -1.0f);
	//			break;
	//		case 1://�E����
	//			g_HANABI[i].dir = D3DXVECTOR2(1.0f, 0.0f);
	//			break;
	//		case 2://������
	//			g_HANABI[i].dir = D3DXVECTOR2(0.0f, 1.0f);
	//			break;
	//		case 3://������
	//			g_HANABI[i].dir = D3DXVECTOR2(-1.0f, 0.0f);
	//			break;
	//		}

	//		g_HANABI[i].speed = 6.0f;

	//		//���t���O���I���ɂ���
	//		g_HANABI[i].use = true;

	//		//�������Ԃ����Z�b�g����
	//		g_HANABI[i].frame = 0.0f;

	//		//�ԉ΂���Z�b�g������I��������
	//		break;
	//	}
	//}
}

Float2 GetAtHanabiPos(Float2 PosA, Float2 PosB)
{
	//���W�擾
	Float2 HanabiVec;

	//�n�_A����n�_B�̈ړ�����
		//MovePos=�n�_B - �n�_A;
	HanabiVec.x = PosB.x - PosA.x;
	HanabiVec.y = PosB.y - PosA.y;
	
	//�����@���̈�萔�ɂ���ĕς��Ȃ��ᓮ���Ȃ�
	if (PosB.x < PosB.x + /*������*/1 && PosB.x >PosB.x - /*������*/1 && PosB.y <PosB.y + /*������*/1 && PosB.y >PosB.y - /*������*/1){}
	else
	{
		//��(float�^�̈�萔)���i�ނ�
		HanabiVec.x -= 1;
		HanabiVec.y -= 1;
	}

	return Float2(HanabiVec);
}

void Normalizer(Float2 Player, Float2 Cursor)
{
	Float2 Vec;

	Vec = Cursor - Player;

	D3DXVec2Normalize(&Vec, &Vec);
	for (int i = 0; i < NUM_HANABI; i++)
	{
		if (g_HANABI[i].use == false)
		{
			g_HANABI[i].use = true;
			g_HANABI[i].vec = Vec;
			break;
		}
	}
}

Float2 GetAtHanabiDeadPos(int index)
{
	return AtHanabiDeadPos[index];
}