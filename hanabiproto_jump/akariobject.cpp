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

static HanabiAkariObject g_AkariObject[AKARI_NUM];

static float g_U, g_V;

Float2 MovePos[AKARI_NUM];

Float2 Ppos;

bool g_composition;
//=============================================================================							
// ����������							
//=============================================================================							
HRESULT InitAkariObject(void)
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/proto_effect_akari.png");

	//������
	for (int i = 0; i < AKARI_NUM; i++)
	{
		g_AkariObject[i].use = false;
		g_AkariObject[i].gather = false;
		g_AkariObject[i].setvec = false;
		g_AkariObject[i].dir.x = 0.0f;
		g_AkariObject[i].dir.y = 0.0f;
		g_AkariObject[i].pos.x = SCREEN_WIDTH;
		g_AkariObject[i].pos.y = SCREEN_HEIGHT;
		g_AkariObject[i].frame = 0;
		g_AkariObject[i].color = { 1.0f,1.0f,1.0f,1.0f };
		g_AkariObject[i].siz = { 32.0f,32.0f };
		g_AkariObject[i].drop.x = 0.0f;
		g_AkariObject[i].drop.y = 0.0f;
		g_AkariObject[i].sdrop.x = 0.0f;
		g_AkariObject[i].sdrop.y = 0.0f;
		g_AkariObject[i].vec.x = 0.0f;
		g_AkariObject[i].vec.y = 0.0f;
		g_AkariObject[i].speed = 1.0f;

	}

	////������
	//for (int i = 0; i < 5; i++)
	//{
	//	g_AkariObject[i].gather = true;
	//	g_AkariObject[i].pos.x = frand() * SCREEN_WIDTH;
	//	g_AkariObject[i].pos.y = frand() * SCREEN_HEIGHT;
	//	g_AkariObject[i].use = true;
	//}

	for (int i = 0; i < AKARI_NUM; i++)
	{
		MovePos[i] = { 0.0f,0.0f };
	}

	g_U = 0.0f;
	g_V = 0.0f;

	g_composition = true;

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
	//�e�X�g
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		for (int i = 0; i < AKARI_NUM; i++)
		{
			if (g_AkariObject[i].use == false)
			{
				g_AkariObject[i].use = true;
				g_AkariObject[i].gather = false;
				g_AkariObject[i].pos.x = frand() * SCREEN_WIDTH;
				g_AkariObject[i].pos.y = frand() * SCREEN_HEIGHT;
				break;
			}
		}
	}

	if (GetKeyboardTrigger(DIK_G))
	{
		SetAkari(GetPlayer()->pos, { 1.0f,-1.0f }, 1.5f);
	}
	

	//�J�b�v������e�X�g
	if (GetKeyboardTrigger(DIK_C))
	{
		SetCupAkari(GetPlayer()->pos, 1, 1, 30, 60, 10, 5.0f);
	}



	//�e�X�g�I���



	//�͂����͈͓��́uAKARI�v���W�܂�悤��
	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].gather && g_AkariObject[i].use == true && g_AkariObject[i].setvec == false && Ppos.x != GetPlayer()->pos.x && Ppos.y != GetPlayer()->pos.y)
		{
			//�n�_A����n�_B�̈ړ�����
			//MovePos=�n�_B - �n�_A;
			MovePos[i] = Centergather(GetPlayer()->pos, GetPlayer()->pos, GetPlayer()->pos, GetPlayer()->pos) - g_AkariObject[i].pos;
			//MovePos[i].y = GetPlayer()->pos.y - g_AkariObject[i].pos.y;
			//���t���[�������ďW�܂邩
			MovePos[i].x /= (60 / (g_AkariObject[i].frame + 1 * 5));
			MovePos[i].y /= (60 / (g_AkariObject[i].frame + 1 * 5));

			//g_AkariObject[i].setvec = true;
		}


		if (g_AkariObject[i].gather && g_AkariObject[i].use)
		{
			g_AkariObject[i].pos.x += MovePos[i].x;
			g_AkariObject[i].pos.y += MovePos[i].y;

			if (g_AkariObject[i].pos.x < /*(SCREEN_WIDTH / 2)*/GetPlayer()->pos.x + 19 && g_AkariObject[i].pos.x >/*(SCREEN_WIDTH / 2)*/GetPlayer()->pos.x - 19
				&& g_AkariObject[i].pos.y </*(SCREEN_HEIGHT / 2)*/GetPlayer()->pos.y + 19 && g_AkariObject[i].pos.y > /*(SCREEN_HEIGHT / 2)*/GetPlayer()->pos.y - 19)
			{
				MovePos[i].x = 0.0f;
				MovePos[i].y = 0.0f;
				g_AkariObject[i].frame += 1;


				//��������Ł[�[�[
				if (g_AkariObject[i].frame > 40)
				{
					for (int j = 0; j < AKARI_NUM; j++)
					{
						if (g_AkariObject[j].gather == true && g_AkariObject[j].use == true)
						{
							g_AkariObject[j].use = false;
							g_AkariObject[j].frame = 0;
							plus_hissatuwaza(5);
						}
					}
				}
			}
		}
		else if (g_AkariObject[i].use == true)
		{
			if (g_AkariObject[i].hitground == true) {
				g_AkariObject[i].vec.y = 0;
			}
			else
			{
				g_AkariObject[i].pos.y += g_AkariObject[i].vec.y;
				g_AkariObject[i].pos.y += MovePos[i].y * g_AkariObject[i].speed * 3;
			}
			g_AkariObject[i].pos.x += MovePos[i].x * g_AkariObject[i].speed * 3;
			g_AkariObject[i].frame += 1;


			//����������̒��S���J�̃}�b�v�`�b�v�ɓ���������t���[������
			if (GetStageInfoRain(g_AkariObject[i].pos)){
				g_AkariObject[i].frame = 500;
			}
				

			//�����鑬��
			g_AkariObject[i].drop.y = 0.01f;
			//�����x
			g_AkariObject[i].sdrop.y = 0.03f;
			//�e����ԕ�
			MovePos[i].x /= 1.005f;
			//����̃t���[����ɏd�͔���
			if (g_AkariObject[i].frame >= 20)
			{
				g_AkariObject[i].drop.y += g_AkariObject[i].sdrop.y;
				g_AkariObject[i].vec.y += g_AkariObject[i].drop.y;
			}
			//�n�ʂɎc��
/*
			if (g_AkariObject[i].pos.y >= 360)
			{
				g_AkariObject[i].hitground = true;
				g_AkariObject[i].pos.y = 360;
			}
*/
			//�����ł������Ł[�[�[
			if (/*g_AkariObject[i].hitground == true &&*/ g_AkariObject[i].frame >= 400)
			{
				g_AkariObject[i].use = false;
				g_AkariObject[i].frame = 0;
				g_AkariObject[i].hitground = false;
			}
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
			DrawSpriteColor(g_TextureNo, basePos.x + g_AkariObject[i].pos.x, basePos.y + g_AkariObject[i].pos.y, 60.0f, 60.0f,
				1.0f, 1.0f, 1.0f, 1.0f, g_AkariObject[i].color);
		}
	}

}


HanabiAkariObject GetAkariObject(int index)
{
	return g_AkariObject[index];
}

void Akarigather(int index)
{
	g_AkariObject[index].gather = true;
	g_AkariObject[index].frame = 0;
}

//������̈ʒu���Z�b�g
void SetAkari(Float2 pos)
{
	int create_akari = 4;
	Float2 akarivec[4] =
	{
		{1.0f,0.0f},	//1
		{-1.0f,0.0f},	//2
		{0.0f,1.0f},	//3
		{0.0f,-1.0f}	//4
	};

	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			MovePos[i] = akarivec[create_akari - 1];
			//�F�Â�
			{
				float RGB[3];
				int saidai = 0;
				for (int j = 0; j < 3; j++)
				{
					RGB[j] = frand();
					if (RGB[saidai] <= RGB[j])
						saidai = j;
				}
				RGB[saidai] = 1.0f;
				g_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
			}

			create_akari -= 1;
			if (create_akari <= 0)
			{
				break;
			}
		}
	}
}

//������̈ʒu�ƍő�����Z�b�g
void SetAkari(Float2 pos, int saidai)
{
	int create_akari = 32;
	Float2 akarivec[32] =
	{
		{1.0f,0.0f},	//1
		{0.2f,0.7f},	//2
		{0.3f,0.8f},	//3
		{0.7f,0.2f},	//4
		{0.5f,0.5f},	//5
		{0.1f,0.6f},	//6
		{0.8f,0.3f},	//7
		{0.4f,0.9f},	//8
		{-1.0f,0.0f},	//9
		{-0.2f,0.7f},	//10
		{-0.3f,0.8f},	//11
		{-0.7f,0.2f},	//12
		{-0.5f,0.5f},	//13
		{-0.4f,0.9f},	//14
		{-0.8f,0.3f},	//15
		{-0.9f,0.4f},	//16
		{0.0f,1.0f},	//17
		{-0.2f,-0.7f},	//18
		{-0.3f,-0.8f},	//19
		{-0.7f,-0.2f},	//20
		{-0.5f,-0.5f},	//21
		{-0.4f,-0.9f},	//22
		{-0.8f,-0.3f},	//23
		{-0.4f,-0.9f},	//24
		{0.0f,-1.0f},	//25
		{0.2f,-0.7f},	//26
		{0.3f,-0.8f},	//27
		{0.7f,-0.2f},	//28
		{0.5f,-0.5f},	//29
		{0.4f,-0.9f},	//30
		{0.8f,-0.3f},	//31
		{0.9f,-0.4f}	//32
	};

	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			g_AkariObject[i].vec.y = 0.0f;
			g_AkariObject[i].hitground = false;
			MovePos[i] = akarivec[create_akari - 1];
			//�F�Â�
			{
				float RGB[3];
				for (int j = 0; j < 3; j++)
				{
					RGB[j] = frand();
				}
				RGB[saidai] = 1.0f;
				g_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
			}

			create_akari -= 1;
			if (create_akari <= 0)
			{
				break;
			}
		}
	}
}

//�_���[�W�^�C�v��0�Ȃ�v���C���[�Ƀ_���[�W
//1�Ȃ�G�l�~�[�Ƀ_���[�W
//2�Ȃ痼��
void SetAkari(Float2 pos, int saidai, int damagetype)
{
	int create_akari = 32;
	Float2 akarivec[32] =
	{
		{1.0f,0.0f},	//1
		{0.2f,0.7f},	//2
		{0.3f,0.8f},	//3
		{0.7f,0.2f},	//4
		{0.5f,0.5f},	//5
		{0.1f,0.6f},	//6
		{0.8f,0.3f},	//7
		{0.4f,0.9f},	//8
		{-1.0f,0.0f},	//9
		{-0.2f,0.7f},	//10
		{-0.3f,0.8f},	//11
		{-0.7f,0.2f},	//12
		{-0.5f,0.5f},	//13
		{-0.4f,0.9f},	//14
		{-0.8f,0.3f},	//15
		{-0.9f,0.4f},	//16
		{0.0f,1.0f},	//17
		{-0.2f,-0.7f},	//18
		{-0.3f,-0.8f},	//19
		{-0.7f,-0.2f},	//20
		{-0.5f,-0.5f},	//21
		{-0.4f,-0.9f},	//22
		{-0.8f,-0.3f},	//23
		{-0.4f,-0.9f},	//24
		{0.0f,-1.0f},	//25
		{0.2f,-0.7f},	//26
		{0.3f,-0.8f},	//27
		{0.7f,-0.2f},	//28
		{0.5f,-0.5f},	//29
		{0.4f,-0.9f},	//30
		{0.8f,-0.3f},	//31
		{0.9f,-0.4f}	//32
	};

	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			switch (damagetype)
			{
			case 0:
				g_AkariObject[i].damageplayerflug = true;
				g_AkariObject[i].damageenemyflug = false;
				break;
			case 1:
				g_AkariObject[i].damageplayerflug = false;
				g_AkariObject[i].damageenemyflug = true;
				break;
			case 2:
				g_AkariObject[i].damageplayerflug = true;
				g_AkariObject[i].damageenemyflug = true;
				break;
			default:
				break;
			}
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			g_AkariObject[i].vec.y = 0.0f;
			g_AkariObject[i].hitground = false;
			MovePos[i] = akarivec[create_akari - 1];
			//�F�Â�
			{
				float RGB[3];
				for (int j = 0; j < 3; j++)
				{
					RGB[j] = frand();
				}
				RGB[saidai] = 1.0f;
				g_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
			}

			create_akari -= 1;
			if (create_akari <= 0)
			{
				break;
			}
		}
	}
}

//����:�J�b�v������̍��W,�F�̎�� (��:0.��:1.��:2),�U���̎��(�v���C���[�_���[�W0.�G�l�~�[�_���[�W1,����2),
//�͈͑I���J�n�p�x,�͈͑I���I���n�_,������̌�(�ő�300),�����{��
//�p�x�͉E��0�x�Ƃ��ď��90�x�A����180�x�A����270�x�Ƃ��A
//�I���J�n�p�x���獶���ɉ���ďI���n�_�܂ł�͈͂Ƃ���B
//(�ǋL)�T���v���Ƃ��ăX�s�[�h���ݒ�ł���悤�ɂ��܂���
void SetCupAkari(Float2 pos, int saidai, int damagetype, int firstangle, int endangle, int akarinum, float speed)
{

	float firstrad, endrad; //���W�A���p�p
	Float2 vec; //�z�����p
	int create_akari = min(akarinum, 300); //�ő�300����
	Float2 akarivec[300];

	//�p�x�̐������u
	while (firstangle >= 360) {
		firstangle -= 360;
	}
	while (endangle >= 360) {
		firstangle -= 360;
	}

	//���W�A���ɕϊ�
	firstrad = firstangle * (D3DX_PI / 180);
	endrad = endangle * (D3DX_PI / 180);

	//�p�x�͈̔͂̃p�^�[������
	//�I���̊p�x�͊J�n�̊p�x���傫������
	if (firstangle > endangle) {
		endangle += 360;
	}
	switch ((int)(firstangle / 90)) //�J�n�p�x���ǂ��̃G���A��
	{
	case 0: //0�`89�x�̂Ƃ�
		switch ((int)(endangle / 90)) //�I���̊p�x���ǂ��̃G���A��
		{
		case 0: //�����G���A����90�x���܂����Ȃ�
			//�����Ŕ��ˊp�x�̐ݒ�
			for (int i = 0; i < create_akari; i++)
			{
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.x = frand() + frand() - 1; //-1.0~1.0
					if ((cos(endrad) <= vec.x) && (vec.x <= cos(firstrad))) {
						break;
					}
				}//y��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(firstrad) <= vec.y) && (vec.y <= sin(endrad))) {
						break;
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 1: //90�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((cos(endrad) <= vec.x) && (vec.x <= cos(firstrad))) {
						break;
					}
				}
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((sin(firstrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					} 
					else {
						if ((sin(endrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 2: //90�x��180�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((-1.0f <= vec.x) && (vec.x <= cos(firstrad))) {
						break;
					}
				}
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((sin(firstrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
					else {
						if ((sin(endrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 3: //90�x��180�x��270�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//y���Ɏ��
				vec.y = frand() + frand() - 1;
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.x = frand() + frand() - 1;
					if (0 <= vec.y) {
						if ((-1.0f <= vec.x) && (vec.x <= cos(firstrad))) {
							break;
						}
					}
					else {
						if ((-1.0f <= vec.x) && (vec.x <= cos(endrad))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 4: //�����G���A����90�A180�A270�A0�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x���Ɏ��
				vec.x = frand() + frand() - 1;
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if (! ((sin(endrad) <= vec.y) && (vec.y <= sin(firstrad)))) {
							break;
						}
					}
					else {
						break;
					}
				}
				akarivec[i] = vec;
			}
			break;
		}
		break;
		//�����܂ŊJ�n�p�x��0�`89�x�̂Ƃ�

	case 1: //90�`179��
		switch ((int)(endangle / 90)) //�I���̊p�x���ǂ��̃G���A��
		{
		case 1: //�����G���A����180�x���܂����Ȃ�
			for (int i = 0; i < create_akari; i++)
			{
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.x = frand() + frand() - 1; //-1.0~1.0
					if ((cos(endrad) <= vec.x) && (vec.x <= cos(firstrad))) {
						break;
					}
				}//y��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(endrad) <= vec.y) && (vec.y <= sin(firstrad))) {
						break;
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 2: //180�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(endrad) <= vec.y) && (vec.y <= sin(firstrad))) {
						break;
					}
				}
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.x = frand() + frand() - 1;
					if (0 <= vec.y) {
						if ((cos(firstrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
					else {
						if ((cos(endrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 3: //180�x��270�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((-1.0f <= vec.x) && (vec.x <= cos(endrad))) {
						break;
					}
				}
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((-1.0f <= vec.y) && (vec.y <= sin(endrad))) {
							break;
						}
					}
					else {
						if ((-1.0f <= vec.y) && (vec.y <= sin(firstrad))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 4: //180�x��270�x��0�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x���Ɏ��
				vec.x = frand() + frand() - 1;
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((-1.0f <= vec.y) && (vec.y <= sin(endrad))) {
							break;
						}
					}
					else {
						if ((-1.0f <= vec.y) && (vec.y <= sin(firstrad))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 5: //�����G���A����180�A270�A0�A90�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x���Ɏ��
				vec.x = frand() + frand() - 1;
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						break;
					}
					else {
						if (!((sin(firstrad) <= vec.y) && (vec.y <= sin(endrad)))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		}
		break;
	case 2: //180�`269��
		switch ((int)(endangle / 90)) //�I���̊p�x���ǂ��̃G���A��
		{
		case 2: //�����G���A����270�x���܂����Ȃ�
			for (int i = 0; i < create_akari; i++)
			{
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.x = frand() + frand() - 1; //-1.0~1.0
					if ((cos(firstrad) <= vec.x) && (vec.x <= cos(endrad))) {
						break;
					}
				}//y��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(endrad) <= vec.y) && (vec.y <= sin(firstrad))) {
						break;
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 3: //270�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((cos(firstrad) <= vec.x) && (vec.x <= cos(endrad))) {
						break;
					}
				}
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((-1.0f <= vec.y) && (vec.y <= sin(endrad))) {
							break;
						}
					}
					else {
						if ((-1.0f <= vec.y) && (vec.y <= sin(firstrad))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 4: //270�x��0�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((cos(firstrad) <= vec.x) && (vec.x <= 1.0f)) {
						break;
					}
				}
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((-1.0f <= vec.y) && (vec.y <= sin(endrad))) {
							break;
						}
					}
					else {
						if ((-1.0f <= vec.y) && (vec.y <= sin(firstrad))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 5: //270�x��0�x��90�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//y���Ɏ��
				vec.y = frand() + frand() - 1;
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.x = frand() + frand() - 1;
					if (0 <= vec.y) {
						if ((cos(endrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
					else {
						if ((cos(firstrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 6: //�����G���A����270�A0�A90�A180�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x���Ɏ��
				vec.x = frand() + frand() - 1;
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						break;
					}
					else {
						if (!((sin(firstrad) <= vec.y) && (vec.y <= sin(endrad)))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		}
		break;
	case 3: //270�`359��
		switch ((int)(endangle / 90)) //�I���̊p�x���ǂ��̃G���A��
		{
		case 3: //�����G���A����0�x���܂����Ȃ�
			//�����Ŕ��ˊp�x�̐ݒ�
			for (int i = 0; i < create_akari; i++)
			{
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.x = frand() + frand() - 1; //-1.0~1.0
					if ((cos(firstrad) <= vec.x) && (vec.x <= cos(endrad))) {
						break;
					}
				}//y��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(firstrad) <= vec.y) && (vec.y <= sin(endrad))) {
						break;
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 4: //0�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.y = frand() + frand() - 1;
					if ((sin(firstrad) <= vec.y) && (vec.y <= sin(endrad))) {
						break;
					}
				}
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.x = frand() + frand() - 1;
					if (0 <= vec.y) {
						if ((cos(endrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
					else {
						if ((cos(firstrad) <= vec.x) && (vec.x <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 5: //0�x��90�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x��͈͓��ɂȂ�܂Ŏ�蒼��
				while (1) {
					vec.x = frand() + frand() - 1;
					if ((cos(endrad) <= vec.x) && (vec.x <= 1.0f)) {
						break;
					}
				}
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((sin(firstrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
					else {
						if ((sin(endrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 6: //0�x��90�x��180�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x���Ɏ��
				vec.x = frand() + frand() - 1;
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						if ((sin(firstrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
					else {
						if ((sin(endrad) <= vec.y) && (vec.y <= 1.0f)) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		case 7: //�����G���A����0�A90�A180�A270�x���܂���
			for (int i = 0; i < create_akari; i++)
			{
				//x���Ɏ��
				vec.x = frand() + frand() - 1;
				//y��͈͓��ɂȂ�܂Ŏ�蒼��
				//2�p�^�[���z�肷��
				while (1) {
					vec.y = frand() + frand() - 1;
					if (0 <= vec.x) {
						break;
					}
					else {
						if (!((sin(endrad) <= vec.y) && (vec.y <= sin(firstrad)))) {
							break;
						}
					}
				}
				akarivec[i] = vec;
			}
			break;
		}
		break;
	}

	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			switch (damagetype)
			{
			case 0:
				g_AkariObject[i].damageplayerflug = true;
				g_AkariObject[i].damageenemyflug = false;
				break;
			case 1:
				g_AkariObject[i].damageplayerflug = false;
				g_AkariObject[i].damageenemyflug = true;
				break;
			case 2:
				g_AkariObject[i].damageplayerflug = true;
				g_AkariObject[i].damageenemyflug = true;
				break;
			default:
				break;
			}
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			g_AkariObject[i].vec.y = 0.0f;
			g_AkariObject[i].hitground = false;
			//MovePos[i] = akarivec[create_akari - 1];

			//������akarivec�ɃX�s�[�h���|����Ɖ��������
			//(�ǋL)�Ƃ�܃X�s�[�h�ǉ��A�v��񂩂���������Ă���
			//�ǉ������z��������speed,���̉���( * speed)
			MovePos[i].x = akarivec[create_akari - 1].x * speed;
			MovePos[i].y = -akarivec[create_akari - 1].y * speed; //�P�ʉ~��y�͏オ���ɂȂ邪�Q�[���ゾ�Ə�͕��ɂȂ邽��

			//�F�Â�
			{
				float RGB[3];
				for (int j = 0; j < 3; j++)
				{
					RGB[j] = frand();
				}
				RGB[saidai] = 1.0f;
				g_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
			}

			create_akari -= 1;
			if (create_akari <= 0)
			{
				break;
			}
		}
	}
}

void SetAkari(Float2 pos, Float2 vec, float speed)
{
	Float2 akarivec = { vec.x,vec.y };


	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			g_AkariObject[i].speed = speed;
			g_AkariObject[i].vec = { 0.0f,0.0f };

			MovePos[i] = akarivec;
			//�F�Â�
			{
				float RGB[3];
				int saidai = 0;
				for (int j = 0; j < 3; j++)
				{
					RGB[j] = frand();
					if (RGB[saidai] <= RGB[j])
						saidai = j;
				}
				RGB[saidai] = 1.0f;
				g_AkariObject[i].color = { RGB[0],RGB[1],RGB[2],1.0f };
			}
			break;
		}
	}
}

void SoulAkari(Float2 pos, Float2 vec)
{
	Float2 akarivec = { vec.x,vec.y };

	for (int i = 0; i < AKARI_NUM; i++)
	{
		if (g_AkariObject[i].use == false)
		{
			g_AkariObject[i].use = true;
			g_AkariObject[i].pos = pos;
			g_AkariObject[i].setvec = false;
			g_AkariObject[i].gather = false;
			g_AkariObject[i].vec = { 0.0f,0.0f };

			MovePos[i] = akarivec;
			//�F�Â�
			{
				////�����_���ŐԂ��ɂȂ�
				//if (rand() % 2 == 0)
				//{
				//	g_AkariObject[i].color = { 0.5f,0.5f,1.0f,1.0f };
				//}
				//else
				//{
				//	g_AkariObject[i].color = { 2.0f,0.5f,0.5f,1.0f };
				//}

				if (rand() % 2 == 0)
				{
					g_AkariObject[i].color = { 0.5f,0.5f,1.0f,1.0f };
				}
				else
				{
					g_AkariObject[i].color = { 2.0f,0.5f,0.5f,1.0f };
				}
			}
			break;
		}
	}
}

Float2 Centergather(Float2 up, Float2 down, Float2 left, Float2 right)
{
	Float2 cp;
	float y = (up.y + down.y) / 2;
	float x = (left.x + right.x) / 2;

	cp.y = y;
	cp.x = x;

	return cp;
}