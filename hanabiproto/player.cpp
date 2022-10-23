/*==============================================================================

   ���_�Ǘ� [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_DISP_X (SCREEN_WIDTH/2)
#define PLAYER_DISP_Y (SCREEN_HEIGHT/2)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_TextureNo;

static PLAYER g_Player;

static float g_U, g_V;

//static int g_AnimeIndex;
//static int g_AnimeWait;

static unsigned int g_StartTime;
static unsigned int g_Second;
static unsigned int g_MiliSecond;

static float g_AnimeTable[4] =
{
	0.0f,
	0.333333f,
	0.666667f,
	1.0f,
};

//static float g_AnimeTable[4] =
//{
//	0.0f,
//	0.333333f,
//	0.666667f,
//	0.333333f,
//};
//
//static float g_MukiTable[4] =
//{
//	0.75f,	//�����
//	0.5f,	//�E����
//	0.0f,	//������
//	0.25f,	//������
//};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/proto_Hanabi_character.png");

	//������
	g_Player.pos.x = PLAYER_DISP_X;
	g_Player.pos.y = PLAYER_DISP_Y;

	g_Player.spjp.x = 8.0f;
	g_Player.spjp.y = 8.0f;

	//g_AnimeIndex = 0;
	//g_AnimeWait = 0;
	
	g_U = 0.0f;
	g_V = 0.0f;

	//�Q�[���J�n���̎������擾����
	g_StartTime = timeGetTime();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	//�L�[�{�[�h��A�L�[�������ꂽ�獶�Ɉړ�����
	if (GetKeyboardPress(DIK_A))
	{
		g_Player.pos.x -= g_Player.spjp.x;
		g_Player.vec.x = -2.0;
	}
	//�L�[�{�[�h��D�L�[�������ꂽ��E�Ɉړ�����
	if (GetKeyboardPress(DIK_D))
	{
		g_Player.pos.x += g_Player.spjp.x;
		g_Player.vec.x = 2.0;
	}

	//if (GetKeyboardPress(DIK_W))
	//{
	//	g_Player.pos.y -= 2.0f;
	//}
	//if (GetKeyboardPress(DIK_S))
	//{
	//	g_Player.pos.y += 2.0f;
	//}


	//�J�������W�̍X�V
	//�v���C���[���W����\�����W�����������l���J�������W�Ƃ��ăZ�b�g����
	D3DXVECTOR2 cameraPos;
	cameraPos.x = g_Player.pos.x - PLAYER_DISP_X;
	cameraPos.y = g_Player.pos.y - PLAYER_DISP_Y;
	if (cameraPos.x < 0) cameraPos.x = 0.0f;
	if (cameraPos.y < 0) cameraPos.y = 0.0f;
	if (cameraPos.x > 960) cameraPos.x = 960.0f;
	if (cameraPos.y > 540) cameraPos.y = 540.0f;
	SetCameraPos(cameraPos.x, cameraPos.y);



	unsigned int nowTime = timeGetTime();

//	SetNumber(30000-(nowTime - g_StartTime));
	g_Second = (nowTime - g_StartTime) / 1000;
	g_MiliSecond = ((nowTime - g_StartTime) % 1000) / 10;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	//�x�[�X���W���擾����
	D3DXVECTOR2 basePos = GetBase();

	DrawSprite(g_TextureNo, basePos.x + g_Player.pos.x, basePos.y + g_Player.pos.y, 
		120.0f, 120.0f,
		0.33333, 0.0, 
		0.33333f, 1.0f);

	//0.33333f, 0.25f);
}


//PLAYER* GetPlayer(void)
//{
//	return &g_Player;
//}
