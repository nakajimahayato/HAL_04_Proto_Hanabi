/*==============================================================================

   �e�N�X�`���̓ǂݍ��� [texture.h]
														 Author : 
														 Date   : 2022/10/23
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "renderer.h"

int LoadTexture(char* fileName);
void UninitTexture(void);

ID3D11ShaderResourceView** GetTexture(int index);

