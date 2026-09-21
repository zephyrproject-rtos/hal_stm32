/**
  ******************************************************************************
  * @file    stm32_hal_psa_translator.h
  * @brief   Header for stm32_hal_psa_translator.c module
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_HAL_PSA_TRANSLATOR_H
#define STM32_HAL_PSA_TRANSLATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psa/crypto_types.h"
#include "psa/crypto_values.h"
#include "stm32_hal_types.h"

psa_status_t STM32_HalStatusToPsaStatus_helper(STM32_HalStatusTypeDef hal_status);

/* Ensure inline quick conversion in case of success */
static inline psa_status_t STM32_HalStatusToPsaStatus(STM32_HalStatusTypeDef hal_status)
{
  if (hal_status == STM32_HAL_SUCCESS)
  {
    return PSA_SUCCESS;
  }

  return STM32_HalStatusToPsaStatus_helper(hal_status);
}

#if defined(STM32_HAL_PSA_SIGNATURE_DRIVER_ENABLED)
#include "stm32_hal_ec.h"

psa_status_t psa_to_stm32_hal_curve_id(
    const psa_key_attributes_t *attributes,
    STM32_HalEcIdTypeDef *curve_id);

#endif /* STM32_HAL_PSA_SIGNATURE_DRIVER_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_PSA_TRANSLATOR_H */
