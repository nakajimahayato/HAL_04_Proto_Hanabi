/*==============================================================================

   ���U���g��ʏ��� [result.cpp]
														 Author : ���c���
														 Date   : 2022/12/07
--------------------------------------------------------------------------------

==============================================================================*/
#include "result.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_TextureNo;//�^�C�g����ʗp�e�N�X�`���̎��ʎq
static int g_BGMNo;		//�^�C�g���pBGM�̎��ʎq

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitResult(void)
{
	//�e�N�X�`����ǂݍ���Ŏ��ʎq���󂯎��
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/runningman002.png");

	//�����t�@�C����ǂݍ���Ŏ��ʎq���󂯎��
	//g_BGMNo = LoadSound("data/BGM/");

	//BGM�̍Đ�(2�ڂ̈����̓��[�v��)
	//���[�v�񐔂ɕ��̒l���w�肷��Ɩ������[�v
	//PlaySound(g_BGMNo, -1);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void UninitResult(void)
{
	//BGM��~
	//StopSound(g_BGMNo);
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void UpdateResult(void)
{
	//Enter�L�[�������ꂽ��SCENE_GAME�ֈڍs����
	//if ()
	//{
	//	//SetScene(SCENE_GAME);
	//}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void DrawResult(void)
{
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);
}