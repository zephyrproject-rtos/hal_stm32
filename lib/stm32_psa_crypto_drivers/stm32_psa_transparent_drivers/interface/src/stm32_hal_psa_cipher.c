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

#include "stm32_hal_cipher.h"
#include "stm32_hal_psa_cipher.h"
#include "stm32_hal_psa_translator.h"

#ifdef STM32_HAL_PSA_AES_CIPHER_DRIVER_ENABLED

static psa_status_t convert_psa_algorithm(psa_algorithm_t psa_alg, STM32_HalAesAlgTypeDef *hal_algo)
{
  if (!PSA_ALG_IS_CIPHER(psa_alg))
  {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  switch (psa_alg)
  {
#if defined(PSA_WANT_ALG_ECB_NO_PADDING)
  case PSA_ALG_ECB_NO_PADDING:
    *hal_algo = STM32_HAL_ALG_AES_ECB;
    break;
#endif
#if defined(PSA_WANT_ALG_CBC_NO_PADDING)
  case PSA_ALG_CBC_NO_PADDING:
    *hal_algo = STM32_HAL_ALG_AES_CBC;
    break;
#endif
#if defined(PSA_WANT_ALG_CTR)
  case PSA_ALG_CTR:
    *hal_algo = STM32_HAL_ALG_AES_CTR;
    break;
#endif
  default:
    return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

#include <stdio.h>

psa_status_t stm32_hal_transparent_cipher_encrypt(
  const psa_key_attributes_t *p_attributes,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *p_iv, size_t iv_length,
  const uint8_t *p_plaintext, size_t plaintext_length,
  uint8_t *p_ciphertext, size_t ciphertext_size, size_t *p_ciphertext_length)
{
  psa_status_t psa_status = PSA_ERROR_HARDWARE_FAILURE;
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;
  STM32_HalAesAlgTypeDef hal_algo;

  psa_status = convert_psa_algorithm(alg, &hal_algo);
  if (psa_status != PSA_SUCCESS)
  {
    return psa_status;
  }

  hal_status = STM32_HalAesEncrypt(hal_algo,
                                   p_key_buffer, key_buffer_size,
                                   p_iv, iv_length,
                                   p_plaintext, plaintext_length,
                                   p_ciphertext, ciphertext_size, p_ciphertext_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

psa_status_t stm32_hal_transparent_cipher_decrypt(
  const psa_key_attributes_t *p_attributes,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *p_ciphertext, size_t input_length,
  uint8_t *p_plaintext, size_t plaintext_size, size_t *p_plaintext_length)
{
  psa_status_t psa_status = PSA_ERROR_HARDWARE_FAILURE;
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;
  STM32_HalAesAlgTypeDef hal_algo;

  psa_status = convert_psa_algorithm(alg, &hal_algo);
  if (psa_status != PSA_SUCCESS)
  {
    return psa_status;
  }

  hal_status = STM32_HalAesDecrypt(hal_algo,
                                   p_key_buffer, key_buffer_size,
                                   p_ciphertext, input_length,
                                   p_plaintext, plaintext_size, p_plaintext_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

psa_status_t stm32_hal_transparent_cipher_encrypt_setup(
  stm32_hal_transparent_driver_cipher_operation_t *operation,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg )
{
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;
  psa_status_t psa_status = PSA_ERROR_HARDWARE_FAILURE;
  STM32_HalAesAlgTypeDef hal_algo;

  psa_status = convert_psa_algorithm(alg, &hal_algo);
  if (psa_status != PSA_SUCCESS)
  {
    return psa_status;
  }

  hal_status = STM32_HalCipherEncryptSetup(&operation->ctx,
                                           key_buffer, key_buffer_size, hal_algo);

  return STM32_HalStatusToPsaStatus(hal_status);
}

psa_status_t stm32_hal_transparent_cipher_decrypt_setup(
  stm32_hal_transparent_driver_cipher_operation_t *operation,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg )
{
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;
  psa_status_t psa_status = PSA_ERROR_HARDWARE_FAILURE;
  STM32_HalAesAlgTypeDef hal_algo;

  psa_status = convert_psa_algorithm(alg, &hal_algo);
  if (psa_status != PSA_SUCCESS)
  {
    return psa_status;
  }

  hal_status = STM32_HalCipherDecryptSetup(&operation->ctx,
                                           key_buffer, key_buffer_size, hal_algo);

  return STM32_HalStatusToPsaStatus(hal_status);
}

#endif /* STM32_HAL_PSA_AES_CIPHER_DRIVER_ENABLED */


