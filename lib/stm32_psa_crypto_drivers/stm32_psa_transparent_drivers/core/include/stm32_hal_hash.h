/**
  ******************************************************************************
  * @file    stm32_hal_hash.h
  * @brief   Header for stm32 hal hash module
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
#ifndef STM32_HAL_HASH_H
#define STM32_HAL_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal_types.h"

typedef enum
{
  STM32_HAL_ALG_HASH_INVALID           = 0x00U,
  STM32_HAL_ALG_MD5                    = 0x01U,
  STM32_HAL_ALG_SHA1                   = 0x02U,
  STM32_HAL_ALG_SHA224                 = 0x03U,
  STM32_HAL_ALG_SHA256                 = 0x04U,
  STM32_HAL_ALG_SHA384                 = 0x05U,
  STM32_HAL_ALG_SHA512                 = 0x06U,
  STM32_HAL_ALG_SHA512_224             = 0x07U,
  STM32_HAL_ALG_SHA512_256             = 0x08U,
  STM32_HAL_ALG_COUNT
} STM32_HalHashAlgTypeDef;

typedef struct stm32_hal_hash_ctx_t
{
  uint32_t hal_algo_id;
  uint32_t hash_block_size;
  size_t hash_size;
} stm32_hal_hash_ctx_t;

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_HASH_H */
