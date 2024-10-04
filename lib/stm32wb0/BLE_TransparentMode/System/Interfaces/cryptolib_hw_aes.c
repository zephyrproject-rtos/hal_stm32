/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    crypto_hw_aes.c
  * @author  GPM WBL Application Team
  * @brief   Implementation of AES encryption needed by crypto library.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "crypto.h"
#include "hw_aes.h"

/* Implementation of the AES 128 required by the crypto library. */
void AES_128_HW_enc(const uint32_t *P_pInputBuffer,
                    uint32_t *P_pOutputBuffer,
                    const uint8_t *P_pKey)
{
  uint32_t tmp_key_32[4], input_32[4], output_32[4];
  uint8_t *tmp_key = (uint8_t *)tmp_key_32;
  uint8_t *input = (uint8_t *)input_32;
  uint8_t *output = (uint8_t *)output_32;
  int32_t i;

  for (i = 0; i < 16; i++)
  {
    tmp_key[15 - i] =  P_pKey[i];
  }

  for (i = 0; i < AES_BLOCK_SIZE; i++)
  {
    LEW32_2_BUFFER(input, i * 4, P_pInputBuffer[3 - i]);
  }

  HW_AES_Encrypt(input_32, tmp_key_32, output_32);

  for (i = 0; i < AES_BLOCK_SIZE; i++)
  {
    P_pOutputBuffer[3 - i] = BUFFER_2_LEW32(output, i * 4);
  }
}

