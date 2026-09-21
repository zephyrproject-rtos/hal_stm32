
/**
  ******************************************************************************
  * @file    stm32_hal_psa_aead.h
  * @author  MCD Application Team
  * @brief   Header for stm32_hal_psa_aead.c module
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
#ifndef STM32_HAL_PSA_AEAD_H
#define STM32_HAL_PSA_AEAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "psa/crypto_types.h"
#include "stm32_hal_aead.h"
#include "stm32_hal_types.h"
#include "stm32_hal_psa_translator.h"

#ifdef STM32_HAL_PSA_AES_AEAD_DRIVER_ENABLED

/* Context used in PSA Crypto Driver composite context */
typedef struct stm32_hal_transparent_driver_aead_operation_t
{
  stm32_hal_aes_ctx_t ctx;
} stm32_hal_transparent_driver_aead_operation_t;

psa_status_t stm32_hal_transparent_aead_encrypt(
  const psa_key_attributes_t *p_attributes,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *p_nonce, size_t nonce_length,
  const uint8_t *p_additional_data, size_t additional_data_length,
  const uint8_t *p_plaintext, size_t plaintext_length,
  uint8_t *p_ciphertext, size_t ciphertext_size, size_t *p_ciphertext_length);

psa_status_t stm32_hal_transparent_aead_decrypt(
  const psa_key_attributes_t *p_attributes,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *p_nonce, size_t nonce_length,
  const uint8_t *p_additional_data, size_t additional_data_length,
  const uint8_t *p_ciphertext, size_t ciphertext_length,
  uint8_t *p_plaintext, size_t plaintext_size, size_t *p_plaintext_length);

psa_status_t stm32_hal_transparent_aead_encrypt_setup(
  stm32_hal_transparent_driver_aead_operation_t *operation,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg);

psa_status_t stm32_hal_transparent_aead_decrypt_setup(
  stm32_hal_transparent_driver_aead_operation_t *operation,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg);

static inline psa_status_t stm32_hal_transparent_aead_set_nonce(
  stm32_hal_transparent_driver_aead_operation_t *operation,
  const uint8_t *nonce,
  size_t nonce_length)
{
  STM32_HalStatusTypeDef hal_status;

  hal_status = STM32_HalAeadSetNonce(&operation->ctx, nonce, nonce_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

static inline psa_status_t stm32_hal_transparent_aead_set_lengths(
  stm32_hal_transparent_driver_aead_operation_t *operation,
  size_t ad_length,
  size_t plaintext_length)
{
  STM32_HalStatusTypeDef hal_status;

  hal_status = STM32_HalAeadSetLengths(&operation->ctx, ad_length, plaintext_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

static inline psa_status_t stm32_hal_transparent_aead_update_ad(
  stm32_hal_transparent_driver_aead_operation_t *operation,
  const uint8_t *input,
  size_t input_length)
{
  STM32_HalStatusTypeDef hal_status;

  hal_status = STM32_HalAeadUpdateAd(&operation->ctx, input, input_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

static inline psa_status_t stm32_hal_transparent_aead_update(
  stm32_hal_transparent_driver_aead_operation_t *operation,
  const uint8_t *input,
  size_t input_length,
  uint8_t *output,
  size_t output_size,
  size_t *output_length)
{
  STM32_HalStatusTypeDef hal_status;

  hal_status = STM32_HalAeadUpdate(&operation->ctx, input, input_length, output,
                                   output_size, output_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

static inline psa_status_t stm32_hal_transparent_aead_finish(
  stm32_hal_transparent_driver_aead_operation_t *operation,
  uint8_t *ciphertext,
  size_t ciphertext_size,
  size_t *ciphertext_length,
  uint8_t *tag,
  size_t tag_size,
  size_t *tag_length)
{
  STM32_HalStatusTypeDef hal_status;

  hal_status = STM32_HalAeadFinish(&operation->ctx, ciphertext, ciphertext_size,
                                   ciphertext_length, tag, tag_size, tag_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

static inline psa_status_t stm32_hal_transparent_aead_verify(
  stm32_hal_transparent_driver_aead_operation_t *operation,
  uint8_t *plaintext,
  size_t plaintext_size,
  size_t *plaintext_length,
  const uint8_t *tag,
  size_t tag_length)
{
  STM32_HalStatusTypeDef hal_status;

  hal_status = STM32_HalAeadVerify(&operation->ctx, plaintext, plaintext_size,
                                   plaintext_length, tag, tag_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

static inline psa_status_t stm32_hal_transparent_aead_abort(
  stm32_hal_transparent_driver_aead_operation_t *operation)
{
  STM32_HalStatusTypeDef hal_status;

  hal_status = STM32_HalAeadAbort(&operation->ctx);

  return STM32_HalStatusToPsaStatus(hal_status);
}

#endif /* STM32_HAL_PSA_AES_AEAD_DRIVER_ENABLED */

#ifdef __cplusplus
}
#endif
#endif /* STM32_HAL_PSA_AEAD_H */

