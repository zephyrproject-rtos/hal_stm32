/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hw_aes.c
  * @author  GPM WBL Application Team
  * @brief   This file provides functions implementation for AES Manager
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
#include "stm32wb0x.h"
#include "stm32wb0x_ll_bus.h"
#include "hw_aes.h"

/** @defgroup AES_Manager  AES Manager
* @{
*/

/** @defgroup AES_Manager_TypesDefinitions Private Type Definitions
* @{
*/
/**
* @}
*/

/** @defgroup AES_Manager_Private_Defines Private Defines
* @{
*/
#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
__disable_irq(); \
  /* Must be called in the same or in a lower scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)

/**
* @}
*/

__STATIC_INLINE uint8_t HW_AES_Start(void);
__STATIC_INLINE void LL_AES_StartManualEncription(BLUE_TypeDef *BLUEx);
__STATIC_INLINE uint32_t LL_AES_IsBusy(BLUE_TypeDef *BLUEx);

/** @defgroup AES_Manager_Private_Variables Private Variables
* @{
*/
/**
* @}
*/

/** @defgroup AES_Manager_External_Variables External Variables
* @{
*/
/**
* @}
*/

/** @defgroup AES_Manager_Public_Functions Public Functions
* @{
*/

HW_AES_ResultStatus HW_AES_Init(void)
{
  if(!LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_MRBLE))
  {
    /* Peripheral reset */
    LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_MRBLE);
    LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_MRBLE);

    /* Enable MR_BLE's clock */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_MRBLE);
  }
  return HW_AES_SUCCESS;
}

HW_AES_ResultStatus HW_AES_Deinit(void)
{
  return HW_AES_SUCCESS;
}

HW_AES_ResultStatus HW_AES_Encrypt(const uint32_t *plainTextData, const uint32_t *key, uint32_t *encryptedData)
{
  /* Counter to signal interruption by a higher priority routine. */
  static volatile uint8_t start_cnt;
  uint8_t priv_start_cnt;

  start_cnt++;

  do
  {
    priv_start_cnt = start_cnt;
    /* Starting from this point, any call to HW_AES_Encrypt will change start_cnt. */

    /* Write the Key in the BLE register */
    BLUE->MANAESKEY0REG = key[0];
    BLUE->MANAESKEY1REG = key[1];
    BLUE->MANAESKEY2REG = key[2];
    BLUE->MANAESKEY3REG = key[3];

    /* Write the plain text data in the BLE register */
    BLUE->MANAESCLEARTEXT0REG = plainTextData[0];
    BLUE->MANAESCLEARTEXT1REG = plainTextData[1];
    BLUE->MANAESCLEARTEXT2REG = plainTextData[2];
    BLUE->MANAESCLEARTEXT3REG = plainTextData[3];

    HW_AES_Start();

    /* Read the plain text data in the BLE register */
    encryptedData[0] = BLUE->MANAESCIPHERTEXT0REG;
    encryptedData[1] = BLUE->MANAESCIPHERTEXT1REG;
    encryptedData[2] = BLUE->MANAESCIPHERTEXT2REG;
    encryptedData[3] = BLUE->MANAESCIPHERTEXT3REG;

  } while (priv_start_cnt != start_cnt);

  return HW_AES_SUCCESS;
}

/**
 * @brief Function to start the AES 128 encryption in blocking mode.
 * @param  None
 *
 * @retval i
 */
__STATIC_INLINE uint8_t HW_AES_Start(void)
{
    volatile uint8_t i = 100U;

    /* Start AES encryption */
    LL_AES_StartManualEncription(BLUE);
    do
    {
        i--;
        if( !LL_AES_IsBusy(BLUE) )
        {
            break;
        }
    } while (i != 0U);

    return i;
}

/**
* @}
*/

/** @defgroup AES_Manager_Private_Functions Private Functions
* @{
*/

/**
  * @brief  AES manual encryption Start function.
  * @rmtoll MANAESCMDREG          START         LL_AES_StartManualEncription
  * @param  BLUEx BLUE Instance
  * @retval None
  */
__STATIC_INLINE void LL_AES_StartManualEncription(BLUE_TypeDef *BLUEx)
{
  SET_BIT(BLUEx->MANAESCMDREG, BLUE_MANAESCMDREG_START);
}

/**
  * @brief  Indicate if AES is busy
  * @rmtoll MANAESSTATREG          BUSY         LL_AES_IsBusy
  * @param  BLUEx BLUE Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AES_IsBusy(BLUE_TypeDef *BLUEx)
{
  return ((READ_BIT(BLUEx->MANAESSTATREG, BLUE_MANAESSTATREG_BUSY) == (BLUE_MANAESSTATREG_BUSY)) ? 1U : 0U);
}

/**
* @}
*/

/**
* @}
*/
