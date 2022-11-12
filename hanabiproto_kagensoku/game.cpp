/*==============================================================================

   �Q�[���{�ҏ��� [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "game.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "bg.h"
#include "collision.h"
#include "camera.h"
#include "object.h"
#include "stage.h"
#include "inputx.h"
#include "enemy.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	// ���_�Ǘ��̏���������
	InitAkariObject();
	InitPlayer();
	InitEnemy();
	InitAtHanabi();

	// �w�i�̏�����
	InitBG();
	InitStage();

	InitCamera();

	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	UninitCamera();


	//�w�i�̏I������
	UninitBG();
	UninitStage();
	// ���_�Ǘ��̏I������
	UninitPlayer();
	UninitEnemy();

	UninitAkariObject();

	UninitAtHanabi();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{

	// ���_�Ǘ��̍X�V����
	UpdateAkariObject();
	UpdatePlayer();
	UpdateEnemy();
	UpdateAtHanabi();
	//�w�i�̍X�V����
	UpdateBG();
	UpdateStage();
	UpdateCamera();

	

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();
	DrawStage();
	// ���_�Ǘ��̕`�揈��
	DrawAkariObject();
	DrawPlayer();
	DrawEnemy();

	DrawAtHanabi();

	DrawCamera();

}