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

#if defined(STM32_HAL_PSA_HASH_DRIVER_ENABLED)

psa_status_t stm32_hal_transparent_hash_compute(
  psa_algorithm_t alg,
  const uint8_t *input, size_t input_length,
  uint8_t *hash, size_t hash_size, size_t *hash_length)
{
  (void)alg;
  (void)input;
  (void)input_length;
  (void)hash;
  (void)hash_size;
  (void)hash_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t stm32_hal_transparent_hash_clone(
  const stm32_hal_transparent_driver_hash_operation_t *source_operation,
  stm32_hal_transparent_driver_hash_operation_t *target_operation)
{
  (void)source_operation;
  (void)target_operation;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t stm32_hal_transparent_hash_setup(
  stm32_hal_transparent_driver_hash_operation_t *operation,
  psa_algorithm_t alg)
{
  (void)operation;
  (void)alg;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t stm32_hal_transparent_hash_init(void)
{
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t stm32_hal_transparent_hash_suspend(void)
{
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t stm32_hal_transparent_hash_resume(void)
{
  return PSA_ERROR_NOT_SUPPORTED;
}

#endif /* STM32_HAL_PSA_HASH_DRIVER_ENABLED */
