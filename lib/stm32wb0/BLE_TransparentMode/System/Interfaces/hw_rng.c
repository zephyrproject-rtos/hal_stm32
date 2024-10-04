/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hw_rng.c
  * @author  GPM WBL Application Team
  * @brief   This file provides functions implementation for RNG Manager.
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
#include "hw_rng.h"
#include "stm32wb0x_ll_rng.h"
#include "stm32wb0x_ll_bus.h"

/** @defgroup RNG_Manager  RNG Manager
* @{
*/

/** @defgroup RNG_Manager_TypesDefinitions Private Type Definitions
* @{
*/
/**
* @}
*/

/** @defgroup RNG_Manager_Private_Defines Private Defines
* @{
*/
/**
* @}
*/

/** @defgroup RNG_Manager_Private_Variables Private Variables
* @{
*/
/**
* @}
*/

/** @defgroup RNG_Manager_External_Variables External Variables
* @{
*/
/**
* @}
*/

/** @defgroup RNG_Manager_Public_Functions Public Functions
* @{
*/

HW_RNG_ResultStatus HW_RNG_Init(void)
{
#ifdef STM32WB09
  /* Peripheral clock enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_RNG);

  uint32_t SamplingClockDivider = 0;

  /* Check that the divider value is equal to the one to configure. If not, it must redo the write and checking. */
  while( LL_RNG_GetSamplingClockEnableDivider(RNG) != SamplingClockDivider)
  {
     /* While the new divider value is being resynchronized with the TRNG core clock domain, it is not possible to write another new value. */
     LL_RNG_SetSamplingClockEnableDivider(RNG, SamplingClockDivider);
  }

  /* Initialize random numbers generation */
  LL_RNG_Enable(RNG);

  /* Wait for RNG enable operation */
  while (LL_RNG_IsActiveFlag_DISABLED(RNG));

  /* Check if internal clock error occurs */
  if (LL_RNG_IsActiveFlag_REVEAL_CLK_ERR(RNG))
  {
    return HW_RNG_ERROR;
  }
#endif /* STM32WB09 */

#if defined (STM32WB07) || defined (STM32WB06) || defined(STM32WB05)
  /* Peripheral clock enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_RNG);

  /* Initialize random numbers generation */
  LL_RNG_Enable(RNG);

  /* Wait for DRDY flag to be raised */
  while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));

  /* Check if error occurs */
  if (  LL_RNG_IsActiveFlag_FAULT(RNG)  )
  {
    /* Clock or Seed Error detected. Set LED to blinking mode (Error type)*/
    return HW_RNG_ERROR;
  }

  /* Values of Generated Random numbers are now available in num array. */

#endif /* STM32WB07 || STM32WB06 || STM32WB05*/
  return HW_RNG_SUCCESS;
}

HW_RNG_ResultStatus HW_RNG_Deinit(void)
{
  /* Stop random numbers generation */
  LL_RNG_Disable(RNG);
  return HW_RNG_SUCCESS;
}

/**
 * @brief Provide a 16-bit true random number
 * @param num: pointer to the random value returned
 * @return error status: 0 = No error
 */
HW_RNG_ResultStatus HW_RNG_GetRandom16(uint16_t* num)
{
#ifdef STM32WB09
  /* Wait for VAL_READY signal */
  while (!LL_RNG_IsActiveFlag_VAL_READY(RNG));

  *num = LL_RNG_READRANDDATA32(RNG);

#endif /* STM32WB09 */

#if defined (STM32WB07) || defined (STM32WB06) || defined(STM32WB05)
  /* Wait for RNGRDY signal */
  while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));

  *num = (uint16_t)LL_RNG_ReadRandData16(RNG);

#endif /* STM32WB07 || STM32WB06 || STM32WB05*/

  return HW_RNG_SUCCESS;
}

/**
 * @brief Provide a 32-bit true random number
 * @param num: pointer to the random value returned
 *
 * @return error status: 0 = No error
 */
HW_RNG_ResultStatus HW_RNG_GetRandom32(uint32_t* num)
{
#ifdef STM32WB09
  /* Wait for VAL_READY signal */
  while (!LL_RNG_IsActiveFlag_VAL_READY(RNG));

  *num = LL_RNG_READRANDDATA32(RNG);
#endif /* STM32WB09 */

#if defined (STM32WB07) || defined (STM32WB06) || defined(STM32WB05)
  uint16_t *num_16 = (uint16_t *) num;

  /* Wait for RNGRDY signal */
  while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));

  num_16[0] = (uint16_t)LL_RNG_ReadRandData16(RNG);

  /* Wait for RNGRDY signal */
  while (!LL_RNG_IsActiveFlag_RNGRDY(RNG));

  num_16[1] = (uint16_t)LL_RNG_ReadRandData16(RNG);
#endif /* STM32WB07 || STM32WB06 || STM32WB05*/

  return HW_RNG_SUCCESS;
}

/**
* @}
*/

/**
* @}
*/
