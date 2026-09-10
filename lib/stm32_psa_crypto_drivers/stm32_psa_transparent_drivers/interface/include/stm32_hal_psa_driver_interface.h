/**
  ******************************************************************************
  * @file    stm32_hal_psa_driver_interface.h
  * @brief   Header for stm32_hal_psa_driver_interface.c module
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
#ifndef STM32_HAL_PSA_DRIVER_INTERFACE_H
#define STM32_HAL_PSA_DRIVER_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#if defined(STM32_HAL_PSA_DRIVER_ENABLED)

#if defined(STM32_HAL_PSA_RNG_DRIVER_ENABLED)
/**
  * Nothing to include for RNG driver
  * PSA core uses mbedtls_platform_get_entropy() and
  * mbedtls_psa_external_get_random()
  * These functions are implemented in stm32_psa_random.c.
  */
#endif /* STM32_HAL_PSA_RNG_DRIVER_ENABLED */

#if defined(STM32_HAL_PSA_HASH_DRIVER_ENABLED)
#include "stm32_hal_psa_hash.h"
#endif /* STM32_HAL_PSA_HASH_DRIVER_ENABLED */

#if defined(STM32_HAL_PSA_AES_CIPHER_DRIVER_ENABLED)
#include "stm32_hal_psa_cipher.h"
#endif /* STM32_HAL_PSA_AES_CIPHER_DRIVER_ENABLED */

#if defined(STM32_HAL_PSA_AES_AEAD_DRIVER_ENABLED)
#include "stm32_hal_psa_aead.h"
#endif /* STM32_HAL_PSA_AES_AEAD_DRIVER_ENABLED */

#endif /* STM32_HAL_PSA_DRIVER_ENABLED */

#ifdef __cplusplus
}
#endif
#endif /* STM32_HAL_PSA_DRIVER_INTERFACE_H */
