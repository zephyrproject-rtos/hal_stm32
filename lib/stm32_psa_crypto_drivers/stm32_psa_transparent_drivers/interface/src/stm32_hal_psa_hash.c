/**
  ******************************************************************************
  * @file    stm32_hal_psa_hash.c
  * @brief   Implementation of STM32 hash driver interface module to PSA API
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

/* Includes ------------------------------------------------------------------*/
#include "psa/crypto.h"

#include "stm32_hal_psa_hash.h"
#include "stm32_hal_psa_translator.h"

#if defined(STM32_HAL_PSA_HASH_DRIVER_ENABLED)

static psa_status_t convert_psa_algorithm(psa_algorithm_t alg,
                                          STM32_HalHashAlgTypeDef *hal_algo)
{
  if (!PSA_ALG_IS_HASH(alg))
  {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  switch (alg)
  {
#if defined(PSA_WANT_ALG_MD5)
    case PSA_ALG_MD5:
      *hal_algo = STM32_HAL_ALG_MD5;
      break;
#endif /* PSA_WANT_ALG_SHA_1 */

#if defined(PSA_WANT_ALG_SHA_1)
    case PSA_ALG_SHA_1:
      *hal_algo = STM32_HAL_ALG_SHA1;
      break;
#endif /* PSA_WANT_ALG_SHA_1 */

#if defined(PSA_WANT_ALG_SHA_224)
    case PSA_ALG_SHA_224:
      *hal_algo = STM32_HAL_ALG_SHA224;
      break;
#endif /* PSA_WANT_ALG_SHA_224 */

#if defined(PSA_WANT_ALG_SHA_256)
    case PSA_ALG_SHA_256:
      *hal_algo = STM32_HAL_ALG_SHA256;
      break;
#endif /* PSA_WANT_ALG_SHA_256 */

#if defined(PSA_WANT_ALG_SHA_384)
    case PSA_ALG_SHA_384:
      *hal_algo = STM32_HAL_ALG_SHA384;
      break;
#endif /* PSA_WANT_ALG_SHA_384 */

#if defined(PSA_WANT_ALG_SHA_512)
    case PSA_ALG_SHA_512:
      *hal_algo = STM32_HAL_ALG_SHA512;
      break;
    case PSA_ALG_SHA_512_224:
      *hal_algo = STM32_HAL_ALG_SHA512_224;
      break;
    case PSA_ALG_SHA_512_256:
      *hal_algo = STM32_HAL_ALG_SHA512_256;
      break;
#endif /* PSA_WANT_ALG_SHA_512 */

    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

psa_status_t stm32_hal_transparent_hash_compute(
  psa_algorithm_t alg,
  const uint8_t *input, size_t input_length,
  uint8_t *hash, size_t hash_size, size_t *hash_length)
{
  stm32_hal_transparent_driver_hash_operation_t operation = {0};
  psa_status_t abort_psa_status = PSA_ERROR_HARDWARE_FAILURE;
  psa_status_t psa_status = PSA_ERROR_HARDWARE_FAILURE;

  psa_status = stm32_hal_transparent_hash_setup(&operation, alg);
  if (psa_status != PSA_SUCCESS)
  {
    goto exit;
  }

  psa_status = stm32_hal_transparent_hash_update(&operation, input, input_length);
  if (psa_status != PSA_SUCCESS)
  {
    goto exit_abort;
  }

  psa_status = stm32_hal_transparent_hash_finish(&operation, hash, hash_size, hash_length);
  if (psa_status != PSA_SUCCESS)
  {
    goto exit_abort;
  }

exit_abort:
  abort_psa_status = stm32_hal_transparent_hash_abort(&operation);
  if (psa_status == PSA_SUCCESS)
  {
    psa_status = abort_psa_status;
  }

exit:
  return psa_status;
}

psa_status_t stm32_hal_transparent_hash_clone(
  const stm32_hal_transparent_driver_hash_operation_t *source_operation,
  stm32_hal_transparent_driver_hash_operation_t *target_operation)
{
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;

  if ((source_operation == NULL) || (target_operation == NULL))
  {
    return PSA_ERROR_BAD_STATE;
  }

  *target_operation = *source_operation;
  hal_status = STM32_HalHashClone(&source_operation->ctx, &target_operation->ctx);

  return STM32_HalStatusToPsaStatus(hal_status);
}

psa_status_t stm32_hal_transparent_hash_setup(
  stm32_hal_transparent_driver_hash_operation_t *operation,
  psa_algorithm_t alg)
{
  STM32_HalHashAlgTypeDef hal_algo = STM32_HAL_ALG_HASH_INVALID;
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;
  psa_status_t psa_status = PSA_ERROR_HARDWARE_FAILURE;

  psa_status = convert_psa_algorithm(alg, &hal_algo);
  if (psa_status != PSA_SUCCESS)
  {
    return psa_status;
  }

  hal_status = STM32_HalHashSetup(&operation->ctx, hal_algo);

  return STM32_HalStatusToPsaStatus(hal_status);
}

psa_status_t stm32_hal_transparent_hash_init(void)
{
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;

  hal_status = STM32_HalHashInit();

  return STM32_HalStatusToPsaStatus(hal_status);
}

psa_status_t stm32_hal_transparent_hash_suspend(void)
{
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;

  hal_status = STM32_HalHashSuspend();

  return STM32_HalStatusToPsaStatus(hal_status);
}

psa_status_t stm32_hal_transparent_hash_resume(void)
{
  STM32_HalStatusTypeDef hal_status = STM32_HAL_ERROR;

  hal_status = STM32_HalHashResume();

  return STM32_HalStatusToPsaStatus(hal_status);
}

#endif /* STM32_HAL_PSA_HASH_DRIVER_ENABLED */
