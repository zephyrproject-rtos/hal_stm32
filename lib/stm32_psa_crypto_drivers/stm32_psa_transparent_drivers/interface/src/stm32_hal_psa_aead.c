
/**
  ******************************************************************************
  * @file    stm32_hal_psa_aead.c
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

#include "stm32_hal_aead.h"
#include "stm32_hal_psa_aead.h"
#include "stm32_hal_psa_translator.h"

#ifdef STM32_HAL_PSA_AES_AEAD_DRIVER_ENABLED

/* Convert psa_algorithm_t ID into STM32_HAL_ALG_AES_* ID */
static psa_status_t convert_psa_algorithm(psa_algorithm_t alg,
                                          STM32_HalAesAlgTypeDef *hal_algo,
                                          uint8_t *tag_length)
{
  if (PSA_ALG_IS_AEAD(alg))
  {
    *tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

    switch (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg))
    {
#if defined(PSA_WANT_ALG_GCM)
    case PSA_ALG_GCM:
      *hal_algo = STM32_HAL_ALG_AES_GCM;
      break;
#endif
#if defined(PSA_WANT_ALG_CCM)
    case PSA_ALG_CCM:
      /* PSA Crypt test: test shall be in range [4 16] */
      if ((*tag_length < 4) || (*tag_length > 16))
      {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      *hal_algo = STM32_HAL_ALG_AES_CCM;
      break;
#endif
    default:
      return PSA_ERROR_NOT_SUPPORTED;
    }

    return PSA_SUCCESS;
  }

  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t stm32_hal_transparent_aead_encrypt(
  const psa_key_attributes_t *p_attributes,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *p_nonce, size_t nonce_length,
  const uint8_t *p_additional_data, size_t additional_data_length,
  const uint8_t *p_plaintext, size_t plaintext_length,
  uint8_t *p_ciphertext, size_t ciphertext_size, size_t *p_ciphertext_length)
{
  STM32_HalStatusTypeDef hal_status;
  STM32_HalAesAlgTypeDef hal_algo;
  psa_status_t psa_status;
  uint8_t tag_length = 0;

  psa_status = convert_psa_algorithm(alg, &hal_algo, &tag_length);
  if (psa_status != PSA_SUCCESS)
  {
    return psa_status;
  }

  hal_status = STM32_HalAesAeadEncrypt(hal_algo, p_key_buffer, key_buffer_size,
                                       p_nonce, nonce_length,
                                       p_additional_data, additional_data_length,
                                       p_plaintext, plaintext_length,
                                       p_ciphertext, ciphertext_size, p_ciphertext_length,
                                       tag_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

psa_status_t stm32_hal_transparent_aead_decrypt(
  const psa_key_attributes_t *p_attributes,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg,
  const uint8_t *p_nonce, size_t nonce_length,
  const uint8_t *p_additional_data, size_t additional_data_length,
  const uint8_t *p_ciphertext, size_t ciphertext_length,
  uint8_t *p_plaintext, size_t plaintext_size, size_t *p_plaintext_length)
{
  STM32_HalStatusTypeDef hal_status;
  STM32_HalAesAlgTypeDef hal_algo;
  psa_status_t psa_status;
  uint8_t tag_length = 0;

  psa_status = convert_psa_algorithm(alg, &hal_algo, &tag_length);
  if (psa_status != PSA_SUCCESS)
  {
    return psa_status;
  }

  hal_status = STM32_HalAesAeadDecrypt(hal_algo, p_key_buffer, key_buffer_size,
                                       p_nonce, nonce_length,
                                       p_additional_data, additional_data_length,
                                       p_ciphertext, ciphertext_length,
                                       p_plaintext, plaintext_size, p_plaintext_length,
                                       tag_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

psa_status_t stm32_hal_transparent_aead_encrypt_setup(
  stm32_hal_transparent_driver_aead_operation_t *operation,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg )
{
  STM32_HalStatusTypeDef hal_status;
  STM32_HalAesAlgTypeDef hal_algo;
  psa_status_t psa_status;
  uint8_t tag_length = 0;

  psa_status = convert_psa_algorithm(alg, &hal_algo, &tag_length);
  if (psa_status != PSA_SUCCESS)
  {
    return psa_status;
  }

  hal_status = STM32_HalAeadEncryptSetup(&operation->ctx, key_buffer, key_buffer_size,
                                         hal_algo, tag_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

psa_status_t stm32_hal_transparent_aead_decrypt_setup(
  stm32_hal_transparent_driver_aead_operation_t *operation,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer, size_t key_buffer_size,
  psa_algorithm_t alg )
{
  STM32_HalStatusTypeDef hal_status;
  STM32_HalAesAlgTypeDef hal_algo;
  psa_status_t psa_status;
  uint8_t tag_length = 0;

  psa_status = convert_psa_algorithm(alg, &hal_algo, &tag_length);
  if (psa_status != PSA_SUCCESS)
  {
    return psa_status;
  }

  hal_status = STM32_HalAeadDecryptSetup(&operation->ctx, key_buffer, key_buffer_size,
                                         hal_algo, tag_length);

  return STM32_HalStatusToPsaStatus(hal_status);
}

#endif /* STM32_HAL_PSA_AES_AEAD_DRIVER_ENABLED */
