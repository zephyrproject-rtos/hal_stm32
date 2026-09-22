/**
  ******************************************************************************
  * @file    stm32_hal_psa_transparent_driver_config_template.h
  * @brief   Config file for STM32 HAL PSA transparent driver
  *          This file should be copied to the application folder and renamed
  *          to stm32_hal_psa_transparent_driver_config.h
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
#ifndef STM32_HAL_PSA_TRANSPARENT_DRIVER_CONFIG_H
#define STM32_HAL_PSA_TRANSPARENT_DRIVER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif


#if defined(USE_STM32_HAL_PSA_RNG_DRIVER) || \
    defined(USE_STM32_HAL_PSA_HASH_DRIVER)

/**
  * \def PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
  *
  * Enables PSA crypto accelerator drivers to enable drivers linking to the
  * PSA crypto core through PSA crypto driver wrappers.
  *
  * Comment a macro to disable the PSA crypto accelerator drivers.
  *
  * Requires MBEDTLS_PSA_CRYPTO_C.
  */
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT

/**
  * \def STM32_HAL_PSA_DRIVER_ENABLED
  *
  * Enables STM32 HAL PSA transparent driver to use STM32 hardware crypto
  * accelerator that manages hash, aes, rsa and elliptic curve operations using
  * keys in transparent forme.
  *
  * Comment a macro to disable the STM32 HAL PSA transparent driver for STM32
  * hardware crypto accelerator.
  *
  * Requires PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT.
  */
#define STM32_HAL_PSA_DRIVER_ENABLED

/**
  * \def STM32_HAL_PSA_HASH_DRIVER_ENABLED
  *
  * Enables STM32 HAL PSA hash module to use STM32 hardware HASH crypto
  * accelerator that manages hash operations.
  *
  * Requires STM32_HAL_PSA_DRIVER_ENABLED.
  */
#if defined(USE_STM32_HAL_PSA_HASH_DRIVER)
#define STM32_HAL_PSA_HASH_DRIVER_ENABLED
#endif

/**
  * \def STM32_HAL_PSA_RNG_DRIVER_ENABLED
  *
  * Enables STM32 HAL PSA RNG module to use STM32 hardware RNG crypto
  * accelerator that provides true random number generation.
  *
  * Requires STM32_HAL_PSA_DRIVER_ENABLED.
  *
  * This configuration is disabled in Zephyr since we're using Zephyr native
  * entropy driver, see CONFIG_MBEDTLS_PSA_DRIVER_GET_ENTROPY and
  * CONFIG_MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG.
  */
#if defined(USE_STM32_HAL_PSA_RNG_DRIVER)
#define STM32_HAL_PSA_RNG_DRIVER_ENABLED
#endif

/**
  * \def STM32_HAL_PSA_AES_CIPHER_DRIVER_ENABLED
  *
  *  Enables STM32 HAL PSA AES module to use STM32 hardware AES operations
  *
  *  Uncomment the macro to enable the STM32 HAL PSA AES module for STM32
  *  AES hardware accelerator
  *
  *  Requires STM32_HAL_PSA_DRIVER_ENABLED.
  */
//#define STM32_HAL_PSA_AES_CIPHER_DRIVER_ENABLED

/**
  * \def STM32_HAL_PSA_AES_DPA_DRIVER_ENABLED Allows DPA resistance for AES modes by using secure
  *        crypto processor (SAES), when this option is enabled,
  *        AES-ECB/CBC modes become DPA-protected.
  *
  * @note Using DPA resistance degrades the performance.
  *
  * Uncomment the macro to enable DPA
  *
  */
//#define STM32_HAL_AES_DPA_PSA_DRIVER_ENABLED

/**
  * \def STM32_HAL_PSA_AES_AEAD_DRIVER_ENABLED
  *
  * Enables STM32 HAL PSA AES AEAD module to use STM32 hardware AES crypto
  * accelerator that manages AES AEAD operations.
  *
  * Uncomment the macro to enable the STM32 HAL PSA AES AEAD module for STM32 hardware
  * AES crypto accelerator.
  *
  * Requires STM32_HAL_PSA_DRIVER_ENABLED.
  *
  */
//#define STM32_HAL_PSA_AES_AEAD_DRIVER_ENABLED

#endif /* USE_STM32_HAL_PSA_RNG_DRIVER || USE_STM32_HAL_PSA_HASH_DRIVER */

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_PSA_TRANSPARENT_DRIVER_CONFIG_H */
