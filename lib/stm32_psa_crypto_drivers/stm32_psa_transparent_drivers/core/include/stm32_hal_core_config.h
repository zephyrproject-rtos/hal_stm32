/**
  ******************************************************************************
  * @file    stm32_hal_core_config.h
  * @brief   Config file for STM32 HAL core driver
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
#ifndef STM32_HAL_CORE_CONFIG_H
#define STM32_HAL_CORE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
  * \def STM32_HAL_HASH_DRIVER_ENABLED
  *
  * Enables STM32 HAL hash core to use STM32 hardware HASH crypto
  * accelerator that manages hash operations.
  *
  * Requires HAL_HASH_MODULE_ENABLED.
  */
#if defined(USE_STM32_HAL_PSA_HASH_DRIVER)
#define STM32_HAL_HASH_DRIVER_ENABLED
#endif

/**
  * \def STM32_HAL_RNG_DRIVER_ENABLED
  *
  * Enables STM32 HAL RNG core to use STM32 hardware RNG crypto
  * accelerator that manages random number generation.
  *
  * Requires HAL_RNG_MODULE_ENABLED.
  */
#if defined(USE_STM32_HAL_PSA_RNG_DRIVER)
#define STM32_HAL_RNG_DRIVER_ENABLED
#endif

/**
  * \def STM32_HAL_AES_CIPHER_DRIVER_ENABLED
  *
  * Enables STM32 HAL RNG core to use STM32 hardware AES
  * crypto accelerator that manages AES CIPHER operations.
  *
  * Requires HAL_AES_MODULE_ENABLED.
  */
#if defined(USE_STM32_HAL_PSA_AES_DRIVER)
#define STM32_HAL_AES_CIPHER_DRIVER_ENABLED
#endif

/**
  * \def STM32_HAL_AES_DPA_DRIVER_ENABLED
  *
  * Enable STM32 DPA resistance core for SAES, secure crypto operations.
  * When this option is enabled, AES-ECB/CBC modes become DPA-protected.
  *
  * Requires STM32_HAL_AES_CIPHER_DRIVER_ENABLED or STM32_HAL_AES_AEAD_DRIVER_ENABLED.
  */
#if defined(USE_STM32_HAL_PSA_AES_DPA_DRIVER)
#define STM32_HAL_AES_DPA_DRIVER_ENABLED
#endif

/**
  * \def STM32_HAL_AES_AEAD_DRIVER_ENABLED
  *
  * Enables STM32 HAL AES AEAD core to use STM32 hardware AES
  * crypto accelerator that manages AES AEAD operations.
  *
  * Requires HAL_AES_MODULE_ENABLED.
  */
#if defined(USE_STM32_HAL_PSA_AES_DRIVER)
#define STM32_HAL_AES_AEAD_DRIVER_ENABLED
#endif

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_CORE_CONFIG_H */
