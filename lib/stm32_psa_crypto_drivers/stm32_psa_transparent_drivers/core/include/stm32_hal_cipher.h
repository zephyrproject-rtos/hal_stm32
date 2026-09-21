/**
  ******************************************************************************
  * @file    stm32_hal_cipher.h
  * @author  MCD Application Team
  * @brief   Header for stm32_hal_cipher.c module
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
#ifndef STM32_HAL_CIPHER_H
#define STM32_HAL_CIPHER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32_hal_aes.h"
#include "stm32_hal_aes_types.h"
#include "stm32_hal_core_config.h"
#include "stm32_hal_types.h"

#ifdef STM32_HAL_AES_CIPHER_DRIVER_ENABLED

STM32_HalStatusTypeDef STM32_HalAesEncrypt(
  STM32_HalAesAlgTypeDef aes_alg,
  const uint8_t *key_buffer, size_t key_buffer_size,
  const uint8_t *nonce, size_t nonce_length,
  const uint8_t *plaintext, size_t plaintext_length,
  uint8_t *ciphertext, size_t ciphertext_size, size_t *ciphertext_length);

STM32_HalStatusTypeDef STM32_HalAesDecrypt(
  STM32_HalAesAlgTypeDef aes_alg,
  const uint8_t *key_buffer, size_t key_buffer_size,
  const uint8_t *input, size_t input_length,
  uint8_t *output, size_t output_size, size_t *output_length);

STM32_HalStatusTypeDef STM32_HalCipherEncryptSetup(
  stm32_hal_aes_ctx_t *ctx,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  STM32_HalAesAlgTypeDef aes_alg);

STM32_HalStatusTypeDef STM32_HalCipherDecryptSetup(
  stm32_hal_aes_ctx_t *ctx,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  STM32_HalAesAlgTypeDef aes_alg);

STM32_HalStatusTypeDef STM32_HalCipherSetIV(
  stm32_hal_aes_ctx_t *ctx,
  const uint8_t *iv, size_t iv_length);

STM32_HalStatusTypeDef STM32_HalCipherUpdate(
  stm32_hal_aes_ctx_t *ctx,
  const uint8_t *input, size_t input_length,
  uint8_t *output, size_t output_size,
  size_t *output_length);

STM32_HalStatusTypeDef STM32_HalCipherFinish(
  stm32_hal_aes_ctx_t *ctx,
  uint8_t *output, size_t output_size,
  size_t *output_length);

STM32_HalStatusTypeDef STM32_HalCipherAbort(
  stm32_hal_aes_ctx_t *ctx);

#endif /* STM32_HAL_AES_CIPHER_DRIVER_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /*STM32_HAL_CIPHER_H */
