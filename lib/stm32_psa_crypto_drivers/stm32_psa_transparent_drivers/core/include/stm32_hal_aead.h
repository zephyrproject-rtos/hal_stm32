
/**
  ******************************************************************************
  * @file    stm32_hal_aead.h
  * @author  MCD Application Team
  * @brief   Header for stm32_hal_aes.c module
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

#ifndef STM32_HAL_AEAD_H
#define STM32_HAL_AEAD_H

#include "stm32_hal_aes.h"
#include "stm32_hal_aes_types.h"
#include "stm32_hal_core_config.h"
#include "stm32_hal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32_HAL_AES_AEAD_DRIVER_ENABLED

STM32_HalStatusTypeDef STM32_HalAesAeadEncrypt(
  STM32_HalAesAlgTypeDef algo,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  const uint8_t *p_nonce, size_t nonce_length,
  const uint8_t *p_additional_data, size_t additional_data_length,
  const uint8_t *p_plaintext, size_t plaintext_length,
  uint8_t *p_ciphertext, size_t ciphertext_size, size_t *p_ciphertext_length,
  size_t tag_length);

STM32_HalStatusTypeDef STM32_HalAesAeadDecrypt(
  STM32_HalAesAlgTypeDef algo,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  const uint8_t *p_nonce, size_t nonce_length,
  const uint8_t *p_additional_data, size_t additional_data_length,
  const uint8_t *p_ciphertext, size_t ciphertext_length,
  uint8_t *p_plaintext, size_t plaintext_size, size_t *p_plaintext_length,
  size_t tag_length);

STM32_HalStatusTypeDef STM32_HalAeadEncryptSetup(
  stm32_hal_aes_ctx_t *ctx,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  STM32_HalAesAlgTypeDef algo,
  size_t tag_length);

STM32_HalStatusTypeDef STM32_HalAeadDecryptSetup(
  stm32_hal_aes_ctx_t *ctx,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  STM32_HalAesAlgTypeDef algo,
  size_t tag_length);

STM32_HalStatusTypeDef STM32_HalAeadSetNonce(
  stm32_hal_aes_ctx_t *ctx,
  const uint8_t *nonce, size_t nonce_length);

STM32_HalStatusTypeDef STM32_HalAeadSetLengths(
  stm32_hal_aes_ctx_t *ctx,
  size_t ad_length, size_t plaintext_length);

STM32_HalStatusTypeDef STM32_HalAeadUpdateAd(
  stm32_hal_aes_ctx_t *ctx,
  const uint8_t *input, size_t input_length);

STM32_HalStatusTypeDef STM32_HalAeadUpdate(
  stm32_hal_aes_ctx_t *ctx,
  const uint8_t *input, size_t input_length,
  uint8_t *output, size_t output_size,
  size_t *output_length);

STM32_HalStatusTypeDef STM32_HalAeadFinish(
  stm32_hal_aes_ctx_t *ctx,
  uint8_t *ciphertext, size_t ciphertext_size,
  size_t *ciphertext_length,
  uint8_t *tag, size_t tag_size,
  size_t *tag_length);

STM32_HalStatusTypeDef STM32_HalAeadVerify(
  stm32_hal_aes_ctx_t *ctx,
  uint8_t *plaintext, size_t plaintext_size,
  size_t *plaintext_length,
  const uint8_t *tag, size_t tag_length);

STM32_HalStatusTypeDef STM32_HalAeadAbort(
  stm32_hal_aes_ctx_t *ctx);

#endif /* STM32_HAL_AES_AEAD_DRIVER_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_AEAD_H */
