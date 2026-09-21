/**
  ******************************************************************************
  * @file    stm32_hal_psa_cipher.h
  * @author  MCD Application Team
  * @brief   Header for stm32_hal_psa_cipher.c module
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
#ifndef STM32_HAL_PSA_CIPHER_H
#define STM32_HAL_PSA_CIPHER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "psa/crypto_types.h"
#include "stm32_hal_cipher.h"
#include "stm32_hal_types.h"
#include "stm32_hal_psa_translator.h"

#ifdef STM32_HAL_PSA_AES_CIPHER_DRIVER_ENABLED

typedef struct stm32_hal_transparent_driver_cipher_operation_t
{
  stm32_hal_aes_ctx_t ctx;
} stm32_hal_transparent_driver_cipher_operation_t;

psa_status_t stm32_hal_transparent_cipher_encrypt(
  const psa_key_attributes_t *p_attributes,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *p_iv, size_t iv_length,
  const uint8_t *p_plaintext, size_t plaintext_length,
  uint8_t *p_ciphertext, size_t ciphertext_size, size_t *p_ciphertext_length);

psa_status_t stm32_hal_transparent_cipher_decrypt(
  const psa_key_attributes_t *p_attributes,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *p_ciphertext, size_t input_length,
  uint8_t *p_plaintext, size_t plaintext_size, size_t *p_plaintext_length);

psa_status_t stm32_hal_transparent_cipher_encrypt_setup(
  stm32_hal_transparent_driver_cipher_operation_t *operation,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg);

psa_status_t stm32_hal_transparent_cipher_decrypt_setup(
  stm32_hal_transparent_driver_cipher_operation_t *operation,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg);

static inline psa_status_t stm32_hal_transparent_cipher_set_iv(
  stm32_hal_transparent_driver_cipher_operation_t *operation,
  const uint8_t *iv,
  size_t iv_length)
{
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;

  hal_status = STM32_HalCipherSetIV(&operation->ctx, iv, iv_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

static inline psa_status_t stm32_hal_transparent_cipher_update(
  stm32_hal_transparent_driver_cipher_operation_t *operation,
  const uint8_t *input,
  size_t input_length,
  uint8_t *output,
  size_t output_size,
  size_t *output_length)
{
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;

  hal_status = STM32_HalCipherUpdate(&operation->ctx, input, input_length,
                                     output, output_size, output_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

static inline psa_status_t stm32_hal_transparent_cipher_finish(
  stm32_hal_transparent_driver_cipher_operation_t *operation,
  uint8_t *output,
  size_t output_size,
  size_t *output_length)
{
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;

  hal_status = STM32_HalCipherFinish(&operation->ctx, output, output_size,
                                     output_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

static inline psa_status_t stm32_hal_transparent_cipher_abort(
  stm32_hal_transparent_driver_cipher_operation_t *operation )
{
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;

  hal_status = STM32_HalCipherAbort(&operation->ctx);

  return STM32_HalStatusToPsaStatus(hal_status);
}

#endif /* STM32_HAL_PSA_AES_CIPHER_DRIVER_ENABLED */

#ifdef __cplusplus
}
#endif
#endif /* STM32_HAL_PSA_CIPHER_H */
