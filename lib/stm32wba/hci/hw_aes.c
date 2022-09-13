/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hw_aes.c
  * @author  MCD Application Team
  * @brief   This file contains the AES driver for STM32WBA
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#include "app_common.h"
#include "stm32wbaxx_ll_bus.h"

/*****************************************************************************/

#define HW_AESX AES

#define HW_AES_CLOCK_ENABLE( )    LL_AHB2_GRP1_EnableClock( LL_AHB2_GRP1_PERIPH_AES )
#define HW_AES_CLOCK_DISABLE( )   LL_AHB2_GRP1_DisableClock( LL_AHB2_GRP1_PERIPH_AES )

#define HW_AES_CLOCK_IS_ENABLE( ) LL_AHB2_GRP1_IsEnabledClock( LL_AHB2_GRP1_PERIPH_AES )

/*****************************************************************************/

typedef struct
{
  uint8_t  run;
} HW_AES_VAR_T;

/*****************************************************************************/

static HW_AES_VAR_T HW_AES_var;

/*****************************************************************************/

int HW_AES_Enable( void )
{
  HW_AES_VAR_T* av = &HW_AES_var;

  /* Test if the driver is not already in use */

  if ( HW_AES_CLOCK_IS_ENABLE() )
  {
    return FALSE;
  }
  av->run = TRUE;

  UTILS_ENTER_CRITICAL_SECTION( );

  /* Enable AES clock */
  HW_AES_CLOCK_ENABLE( );

  UTILS_EXIT_CRITICAL_SECTION( );

  return TRUE;
}

/*****************************************************************************/

void HW_AES_SetKey( uint32_t mode,
                    const uint8_t* key )
{
  uint32_t tmp[4];

  /* Retrieve all bytes of key */
  memcpy( tmp, key, 16 );

  /* Initialize the AES peripheral with default values:
     - Processing:     disabled
     - Data type:      32-bit
     - Operating mode: encryption
     - Chaining mode:  ECB
     - Key size:       128-bit
  */
  HW_AESX->CR = 0;

  /* Copy key bytes to the AES registers */

  if ( mode & HW_AES_REV )
  {
    HW_AESX->KEYR0 = tmp[0];
    HW_AESX->KEYR1 = tmp[1];
    HW_AESX->KEYR2 = tmp[2];
    HW_AESX->KEYR3 = tmp[3];
  }
  else
  {
    HW_AESX->KEYR3 = __REV( tmp[0] );
    HW_AESX->KEYR2 = __REV( tmp[1] );
    HW_AESX->KEYR1 = __REV( tmp[2] );
    HW_AESX->KEYR0 = __REV( tmp[3] );
  }

  if ( !(mode & HW_AES_ENC) )
  {
    /* Set key preparation mode */
    HW_AESX->CR = AES_CR_MODE_0;

    /* Enable AES processing */
    HW_AESX->CR |= AES_CR_EN;

    /* Wait for CCF flag to be raised */
    while ( ! (HW_AESX->SR & AES_SR_CCF) );

    /* Clear CCF Flag */
    HW_AESX->ICR |= AES_ICR_CCF;

    /* Set decryption mode */
    HW_AESX->CR = AES_CR_MODE_1;
  }

  /* Enable byte swapping if needed */
  if ( mode & HW_AES_SWAP )
    HW_AESX->CR |= AES_CR_DATATYPE_1;

  /* Wait until KEYVALID is set */
  while ( !(HW_AESX->SR & AES_SR_KEYVALID) );

  /* Enable AES processing */
  HW_AESX->CR |= AES_CR_EN;
}

/*****************************************************************************/

void HW_AES_Crypt( const uint32_t* input,
                   uint32_t* output )
{
  /* Write the input block into the input FIFO */
  HW_AESX->DINR = input[0];
  HW_AESX->DINR = input[1];
  HW_AESX->DINR = input[2];
  HW_AESX->DINR = input[3];

  /* Wait for CCF flag to be raised */
  while ( !(HW_AESX->SR & AES_SR_CCF) );

  /* Read the output block from the output FIFO */
  output[0] = HW_AESX->DOUTR;
  output[1] = HW_AESX->DOUTR;
  output[2] = HW_AESX->DOUTR;
  output[3] = HW_AESX->DOUTR;

  /* Clear CCF Flag */
  HW_AESX->ICR |= AES_ICR_CCF;
}

/*****************************************************************************/

void HW_AES_Disable( void )
{
  HW_AES_VAR_T* av = &HW_AES_var;

  if ( av->run )
  {
    /* Disable AES processing */
    HW_AESX->CR = 0;

    UTILS_ENTER_CRITICAL_SECTION( );

    /* Disable AES clock */
    HW_AES_CLOCK_DISABLE( );

    UTILS_EXIT_CRITICAL_SECTION( );

    av->run = FALSE;
  }
}

/*****************************************************************************/
