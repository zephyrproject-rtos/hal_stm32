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
#include "stm32_soc_hal.h"
#include "stm32_hal_core_config.h"
#include "stm32_hal_types.h"

#define STM32_HASH_BLOCK_MAX_BYTE_SIZE  ((size_t)128)    /*!< Max block size to support SHA384/SHA512 */
#define STM32_HASH_EXTRA_BYTES          ((size_t)4)      /*!< One supplementary word on first block */
#define STM32_HASH_TIMEOUT              ((uint32_t)3)    /* HAL ABI timeout value in ticks */

/*
 * STM32_HASH_HAL_V* helper macros to differenciate between the several HAL
 * API versions.
 */
#if defined(HAL_VERSION_MAIN) && (HAL_VERSION_MAIN == 2)
#define STM32_HASH_HAL_V2
#elif defined(HAL_HASH_VERSION) && (HAL_HASH_VERSION == 200)
#define STM32_HASH_HAL_V1_2
#else
#define STM32_HASH_HAL_V1_0
#endif

#ifdef STM32_HASH_HAL_V1_2
/* Magic byte size value not exposed by HAL header files */
#define STM32_HASH_HW_CTX_SIZE  ((103 + 3) * 4)
#endif

#ifdef STM32_HASH_HAL_V1_0
/* Magic byte size value not exposed by HAL header files */
#define STM32_HASH_HW_CTX_SIZE  ((54 + 3) * 4)
#endif

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
#ifdef STM32_HASH_HAL_V2
  hal_hash_handle_t hhash;
#else /* STM32_HASH_HAL_V2 */
  HASH_HandleTypeDef hhash;
#endif /* STM32_HASH_HAL_V2 */

  uint32_t hal_algo_id;
  uint32_t hash_block_size;
  size_t hash_size;
  uint8_t initialized;
  uint8_t hw_was_used;

  uint8_t sbuf[STM32_HASH_BLOCK_MAX_BYTE_SIZE + STM32_HASH_EXTRA_BYTES];
  size_t sbuf_len; /*!< Number of bytes stored in context buffer */
  size_t first; /*!< Number of bytes already processed in first block */

  /* HW context when context switcing is needed */
#ifdef STM32_HASH_HAL_V2
  hal_hash_suspended_context_t hw_ctx;
#elif defined(STM32MP13)
  uint32_t hw_ctx[STM32_HASH_HW_CTX_SIZE / sizeof(uint32_t)];
#else
  uint8_t hw_ctx[STM32_HASH_HW_CTX_SIZE];
#endif
} stm32_hal_hash_ctx_t;

#if defined(STM32_HAL_HASH_DRIVER_ENABLED)
STM32_HalStatusTypeDef STM32_HalHashInit(void);

STM32_HalStatusTypeDef STM32_HalHashSetup(
  stm32_hal_hash_ctx_t *ctx,
  STM32_HalHashAlgTypeDef alg);

STM32_HalStatusTypeDef STM32_HalHashClone(
  const stm32_hal_hash_ctx_t *src_ctx,
  stm32_hal_hash_ctx_t *dst_ctx);

STM32_HalStatusTypeDef STM32_HalHashUpdate(
  stm32_hal_hash_ctx_t *ctx,
  const uint8_t *input, size_t input_length);

STM32_HalStatusTypeDef STM32_HalHashFinish(
  stm32_hal_hash_ctx_t *ctx,
  uint8_t *hash, size_t hash_size, size_t *hash_length);

STM32_HalStatusTypeDef STM32_HalHashAbort(
  stm32_hal_hash_ctx_t *ctx);

STM32_HalStatusTypeDef STM32_HalHashSuspend(void);

STM32_HalStatusTypeDef STM32_HalHashResume(void);
#endif /* STM32_HAL_HASH_DRIVER_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_HASH_H */
