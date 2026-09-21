/**
  ******************************************************************************
  * @file    stm32_hal_psa_translator.c
  * @brief   Implementation of STM32 translator driver interface module to PSA API
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "psa/crypto.h"
#include "stm32_hal_psa_translator.h"
#include "stm32_hal_types.h"

psa_status_t STM32_HalStatusToPsaStatus_helper(STM32_HalStatusTypeDef hal_status)
{
  switch (hal_status)
  {
    case STM32_HAL_SUCCESS:
      return PSA_SUCCESS;

    case STM32_HAL_ERROR_NOT_SUPPORTED:
      return PSA_ERROR_NOT_SUPPORTED;

    case STM32_HAL_WRONG_KEY_TYPE:
      return PSA_ERROR_INVALID_ARGUMENT;

    case STM32_HAL_STORAGE_ERROR:
      return PSA_ERROR_STORAGE_FAILURE;

    case STM32_HAL_BUFFER_TOO_SMALL:
      return PSA_ERROR_BUFFER_TOO_SMALL;

    case STM32_HAL_BAD_STATE:
      return PSA_ERROR_BAD_STATE;

    case STM32_HAL_INVALID_ARGUMENT:
      return PSA_ERROR_INVALID_ARGUMENT;

    case STM32_HAL_INVALID_SIGNATURE:
      return PSA_ERROR_INVALID_SIGNATURE;

    case STM32_HAL_OUT_OF_MEMORY:
      return PSA_ERROR_INSUFFICIENT_MEMORY;

    case STM32_HAL_ERROR:
    default:
      return PSA_ERROR_HARDWARE_FAILURE;
  }
}
