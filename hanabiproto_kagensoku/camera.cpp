/*==============================================================================

   �J�������� [camera.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "camera.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAMERA_2D	g_Camera;	//�J�����p�f�[�^
static D3DXVECTOR2	g_Base;		//�x�[�X���W


//=============================================================================
// ����������
//=============================================================================
HRESULT InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR2(0.0f, 0.0f);

	g_Base = D3DXVECTOR2(0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCamera(void)
{
	//�J�������W�𔽓]�����l���x�[�X���W�Ƃ��Ďg��
	g_Base = (g_Camera.pos * -1);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCamera(void)
{

}

D3DXVECTOR2 GetBase(void)
{
	return g_Base;
}

void SetCameraPos(float x, float y)
{
	g_Camera.pos.x = x;
	g_Camera.pos.y = y;
}