/*==============================================================================

				   �X�R�A���� [score.h]
				Author : ����
				Date   : 2022/12/12(�ŏI�ҏW��)
------------------------------------------------------------------------------------------------------------------------------------------

==============================================================================*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCORE_END_GAME    100000  //PlayerScore�����ȏ�ŃN���A
#define SCORE_DIGITS      6       //Player&EnemyScore�̌���
#define PLAYERSCORE_POSX  720.0f  //PlayerScore�̕\���ʒuX
#define ENEMYSCORE_POSX   1370.0f //EnemyScore�̕\���ʒuX
#define SCORE_POSY        290.0f  //Player&Enemy�̕\���ʒuY
#define SCORE_SIZE_X      40.0f   //Player&Enemy�̃T�C�YX
#define SCORE_SIZE_Y      40.0f   //Player&Enemy�̃T�C�YY

struct PLAYERSCORE {
	int   score;
	int   max_score;
};

struct ENEMYSCORE {
	int   score;
	int   max_score;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore();
void UninitScore();

//Player�̃X�R�A�֘A�̊֐�
void UpdatePlayerScore();
void DrawPlayerScore();
void PlusPlayerScore(int plusscore);
void SetPlayerScore(int score);
int GetPlayerScore();

//Enemy�̃X�R�A�֘A�̊֐�
void UpdateEnemyScore();
void DrawEnemyScore();
void PlusEnemyScore(int plusscore);
void SetEnemyScore(int score);
int GetEnemyScore();


