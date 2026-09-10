/**
  ******************************************************************************
  * @file    stm32_hal_psa_cipher.c
  * @author  MCD Application Team
  * @brief   Implementation of STM32 HAL AES driver interface to PSA API
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

#include "psa/crypto.h"

#include "stm32_hal_psa_cipher.h"

#ifdef STM32_HAL_PSA_AES_CIPHER_DRIVER_ENABLED

psa_status_t stm32_hal_transparent_cipher_encrypt(
  const psa_key_attributes_t *p_attributes,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *p_iv, size_t iv_length,
  const uint8_t *p_plaintext, size_t plaintext_length,
  uint8_t *p_ciphertext, size_t ciphertext_size, size_t *p_ciphertext_length)
{
  (void)p_attributes;
  (void)p_key_buffer;
  (void)key_buffer_size;
  (void)alg;
  (void)p_iv;
  (void)iv_length;
  (void)p_plaintext;
  (void)plaintext_length;
  (void)p_ciphertext;
  (void)ciphertext_size;
  (void)p_ciphertext_length;

  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t stm32_hal_transparent_cipher_decrypt(
  const psa_key_attributes_t *p_attributes,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *p_ciphertext, size_t input_length,
  uint8_t *p_plaintext, size_t plaintext_size, size_t *p_plaintext_length)
{
  (void)p_attributes;
  (void)p_key_buffer;
  (void)key_buffer_size;
  (void)alg;
  (void)p_ciphertext;
  (void)input_length;
  (void)p_plaintext;
  (void)plaintext_size;
  (void)p_plaintext_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t stm32_hal_transparent_cipher_encrypt_setup(
  stm32_hal_transparent_driver_cipher_operation_t *operation,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg )
{
  (void)operation;
  (void)attributes;
  (void)key_buffer;
  (void)key_buffer_size;
  (void)alg;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t stm32_hal_transparent_cipher_decrypt_setup(
  stm32_hal_transparent_driver_cipher_operation_t *operation,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg )
{
  (void)operation;
  (void)attributes;
  (void)key_buffer;
  (void)key_buffer_size;
  (void)alg;
  return PSA_ERROR_NOT_SUPPORTED;
}

#endif /* STM32_HAL_PSA_AES_CIPHER_DRIVER_ENABLED */


