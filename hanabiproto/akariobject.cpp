/*==============================================================================

				   �I�u�W�F�N�g���� [akariobject.cpp]
				Author : ���ł���
				Date    : 2022/10/23(�ŏI�ҏW��)
------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#include "object.h"	
#include "texture.h"
#include "collision.h"
#include "sprite.h"
#include "camera.h"

//*****************************************************************************							
// �}�N����`							
//*****************************************************************************							
#define AKARI_NUM	100
//*****************************************************************************							
// �v���g�^�C�v�錾							
//*****************************************************************************							

//*****************************************************************************							
// �O���[�o���ϐ�							
//*****************************************************************************							
static int g_TextureNo;

static HanabiAkariObject g_AkariObject[AKARI_NUM];

static float g_U, g_V;
//=============================================================================							
// ����������							
//=============================================================================							
HRESULT InitAkariObject(void)
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/proto_effect_explosion.png");

	//������
	for (int i = 0; i < AKARI_NUM; i++)
	{
		g_AkariObject[i].use = false;
		g_AkariObject[i].gather = false;
		g_AkariObject[i].pos.x = SCREEN_WIDTH / 2;
		g_AkariObject[i].pos.y = SCREEN_HEIGHT / 2;
	}

	//������
	/*for (int i = 0; i < 5; i++)
	{
		g_AkariObject[i].pos.x = frand() * SCREEN_WIDTH;
		g_AkariObject[i].pos.y = frand() * SCREEN_HEIGHT;
		g_AkariObject[i].use = true;
	}*/
	

	g_U = 0.0f;
	g_V = 0.0f;

	return S_OK;
}

//=============================================================================							
// �I������							
//=============================================================================							
void UninitAkariObject(void)
{

}

//=============================================================================							
// �X�V����							
//=============================================================================							
void UpdateAkariObject(void)
{
	//�͂����͈͓��́uAKARI�v���W�܂�悤��
	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].gather&&g_AkariObject[i].use)
		{
			g_AkariObject[i].pos.x = SCREEN_WIDTH / 2;
			g_AkariObject[i].pos.y = SCREEN_HEIGHT / 2;
		}
	}
}

//=============================================================================							
// �`�揈��							
//=============================================================================							
void DrawAkariObject(void)
{
	//�x�[�X���W���擾����
	D3DXVECTOR2 basePos = GetBase();
	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == true)
		{
			DrawSprite(g_TextureNo, basePos.x + g_AkariObject[i].pos.x, basePos.y + g_AkariObject[i].pos.y, 120.0f, 120.0f,
				1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	
	
}

//�ԉ΂́uAKARI�v��ԁF�W�܂���
void AKARIGather(int index)
{
	//���݂́uAKARI�v�ƏW�܂�ʒu�Ƃ̈ʒu�֌W����ړ��������X�V
	g_AkariObject[index].dir = /*�ԉ΂̔����ʒu*/->pos - g_AkariObject[index].pos;
	D3DXVec2Normalize(&g_AkariObject[index].dir, &g_AkariObject[index].dir);

	//�G�̍��W�X�V
	g_AkariObject[index].pos += g_AkariObject[index].dir * 0.8f;
}