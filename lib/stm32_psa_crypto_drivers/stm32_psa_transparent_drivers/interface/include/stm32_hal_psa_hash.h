/**
  ******************************************************************************
  * @file    stm32_hal_psa_hash.h
  * @brief   Header for stm32_hal_psa_hash.c module
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
#ifndef STM32_HAL_PSA_HASH_H
#define STM32_HAL_PSA_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "psa/crypto_types.h"
#include "psa/crypto_values.h"

#include "stm32_hal_hash.h"
#include "stm32_hal_types.h"

#if defined(STM32_HAL_PSA_HASH_DRIVER_ENABLED)

/* Context used in PSA Crypto Driver primites context */
typedef struct stm32_hal_transparent_driver_hash_operation_t
{
  stm32_hal_hash_ctx_t ctx;
} stm32_hal_transparent_driver_hash_operation_t;

psa_status_t stm32_hal_transparent_hash_init(void);

psa_status_t stm32_hal_transparent_hash_compute(
  psa_algorithm_t alg,
  const uint8_t *input, size_t input_length,
  uint8_t *hash, size_t hash_size, size_t *hash_length);

psa_status_t stm32_hal_transparent_hash_setup(
  stm32_hal_transparent_driver_hash_operation_t *operation,
  psa_algorithm_t alg);

psa_status_t stm32_hal_transparent_hash_clone(
  const stm32_hal_transparent_driver_hash_operation_t *source_operation,
  stm32_hal_transparent_driver_hash_operation_t *target_operation);

static inline psa_status_t stm32_hal_transparent_hash_update(
  stm32_hal_transparent_driver_hash_operation_t *operation,
  const uint8_t *input, size_t input_length)
{
  (void)operation;
  (void)input;
  (void)input_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

static inline psa_status_t stm32_hal_transparent_hash_finish(
  stm32_hal_transparent_driver_hash_operation_t *operation,
  uint8_t *hash, size_t hash_size, size_t *hash_length)
{
  (void)operation;
  (void)hash;
  (void)hash_size;
  (void)hash_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

static inline psa_status_t stm32_hal_transparent_hash_abort(
  stm32_hal_transparent_driver_hash_operation_t *operation)
{
  (void)operation;
  return PSA_ERROR_NOT_SUPPORTED;
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_PSA_HASH_DRIVER_ENABLED */
#endif /* STM32_HAL_PSA_HASH_H */
