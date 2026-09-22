/**
  ******************************************************************************
  * @file    stm32_hal_hash.c
  * @brief   Implementation of STM32 hash core module
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
#include "stm32_hal_core_config.h"
#include "stm32_hal_hash.h"
#include "stm32_hal_types.h"
#include "stm32_hal_private.h"
#include "stm32_soc_hal.h"

#ifdef MBEDTLS_THREADING_C
#include <mbedtls/threading.h>
#endif /* MBEDTLS_THREADING_C */

#include <stdbool.h>
#include <string.h>

#include <stdio.h>

#if defined(STM32_HAL_HASH_DRIVER_ENABLED)

/*
 * struct stm32_hash_device - State of the STM32 HASH device
 *
 * @active_context - Currently active operation context or NULL if none
 * @mutex - Mutlithread access protection
 * @operation_refcount - Opened operations counter
 */
struct stm32_hash_device {
  stm32_hal_hash_ctx_t *active_context;
#ifdef MBEDTLS_THREADING_C
  mbedtls_threading_mutex_t mutex;
#endif /* MBEDTLS_THREADING_C */
  unsigned int operation_refcount;
};

static struct stm32_hash_device hash_device;

/*
 * Local helper functions to manage Hash device state and accesses.
 */

/* Lock mutex for hash_device access */
static void lock_device_mutex()
{
#ifdef MBEDTLS_THREADING_C
  mbedtls_mutex_lock(&hash_device.mutex);
#endif /* MBEDTLS_THREADING_C */
}

/* Unlock mutex for hash_device access */
static void unlock_device_mutex()
{
#ifdef MBEDTLS_THREADING_C
  mbedtls_mutex_unlock(&hash_device.mutex);
#endif /* MBEDTLS_THREADING_C */
}

/*
 * Increment the number of active operations.
 * Device access mutex must be locked when this function is called.
 * Return true if it's the first operation, false otherwise
 */
static bool increment_operation_counter(void)
{
  if (hash_device.operation_refcount == ~0)
  {
    while ( 1 )
    {
       /* Panic */
    }
  }

  hash_device.operation_refcount++;

  return hash_device.operation_refcount == 1;
}

/*
 * Decrement the number of active operations.
 * Device access mutex must be locked when this function is called.
 * Return true if it's the last operation, false otherwise
 */
static bool decrement_operation_counter(void)
{
  if (hash_device.operation_refcount == 0)
  {
    while ( 1 )
    {
       /* Panic */
    }
  }

  hash_device.operation_refcount--;

  return hash_device.operation_refcount == 0;
}

/*
 * Enable STM32 Hash device clock
 * Device must be locked when this function is called.
 */
static void enable_hash_clock(void)
{
#ifdef STM32_HASH_HAL_V2
 #if defined(USE_HAL_HASH_CLK_ENABLE_MODEL) && \
      (USE_HAL_HASH_CLK_ENABLE_MODEL == HAL_CLK_ENABLE_PERIPH_ONLY)
  /*  Nothing to do, the HAL function takes care of the HASH clock */
 #else
  HAL_RCC_HASH_EnableClock();
 #endif
#elif defined(__HAL_RCC_HASH1_CLK_ENABLE)
  __HAL_RCC_HASH1_CLK_ENABLE();
#else /* STM32_HASH_HAL_V2 */
  __HAL_RCC_HASH_CLK_ENABLE();
#endif /* STM32_HASH_HAL_V2 */
}

/*
 * Disable STM32 Hash device cloc
 * Device must be locked when this function is called.
 */
static void disable_hash_clock(void)
{
#ifdef STM32_HASH_HAL_V2
 #if defined (USE_HAL_HASH_CLK_ENABLE_MODEL) && \
     (USE_HAL_HASH_CLK_ENABLE_MODEL == HAL_CLK_ENABLE_PERIPH_ONLY)
  /*  Nothing to do, the HAL function takes care of the HASH clock */
 #else
  HAL_RCC_HASH_DisableClock();
 #endif
#elif defined(__HAL_RCC_HASH1_CLK_DISABLE)
  __HAL_RCC_HASH1_CLK_DISABLE();
#else /* STM32_HASH_HAL_V2 */
  __HAL_RCC_HASH_CLK_DISABLE();
#endif /* STM32_HASH_HAL_V2 */
}

/*
 * Helper for HAL HASH de-initialization API function.
 * Device must be locked when this function is called.
 */
static STM32_HalStatusTypeDef deinit_hash_hal(stm32_hal_hash_ctx_t *ctx)
{
#ifdef STM32_HASH_HAL_V2
  HAL_HASH_DeInit(&ctx->hhash);
#else
  if (HAL_HASH_DeInit(&ctx->hhash) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }
#endif /* STM32_HASH_HAL_V2 */

  return STM32_HAL_SUCCESS;
}

/*
 * Helper for HAL HASH initialization and configuration API functions.
 * Device must be locked when this function is called.
 */
static STM32_HalStatusTypeDef init_configure_hash_hal(stm32_hal_hash_ctx_t *ctx)
{
  if (ctx->initialized == 1)
  {
    deinit_hash_hal(ctx);
    ctx->initialized = 0;
  }

#ifdef STM32_HASH_HAL_V2
  if (HAL_HASH_Init(&ctx->hhash, HAL_HASH) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  hal_hash_config_t hash_cfg = {
    .data_swapping = HAL_HASH_DATA_SWAP_BYTE,
    .algorithm = ctx->hal_algo_id,
  };

  if (HAL_HASH_SetConfig(&ctx->hhash, &hash_cfg) != HAL_OK)
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }
#else

 #ifdef STM32_HASH_HAL_V1_2
  /* Set HASH instance */
  ctx->hhash.Instance = HASH;
 #else
  ctx->hhash.Init.DataType = HASH_DATATYPE_8B;
 #endif /* STM32_HASH_HAL_V1_2 */

  if (HAL_HASH_Init(&ctx->hhash) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

 #if defined(STM32_HASH_HAL_V1_2)
  HASH_ConfigTypeDef hash_cfg = {
    .DataType = HASH_BYTE_SWAP,
    .Algorithm = ctx->hal_algo_id,
  };

  if (HAL_HASH_SetConfig(&ctx->hhash, &hash_cfg) != HAL_OK)
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }
 #endif /* STM32_HASH_HAL_V1_2 */
#endif /* STM32_HASH_HAL_V2 */

  return STM32_HAL_SUCCESS;
}

/*
 * Save STM32 HASH device hardware state in a hash operation context.
 * Device must be locked when this function is called.
 */
static void save_hw_context(stm32_hal_hash_ctx_t *ctx)
{
#ifdef STM32_HASH_HAL_V2
  HAL_HASH_SaveContext(&ctx->hhash, &ctx->hw_ctx);
#endif
#ifdef STM32_HASH_HAL_V1_2
  HAL_HASH_Suspend(&ctx->hhash, ctx->hw_ctx);
#endif
#ifdef STM32_HASH_HAL_V1_0
  HAL_HASH_ContextSaving(&ctx->hhash, ctx->hw_ctx);
#endif
}

/*
 * Restore STM32 HASH device hardware state from a hash operation context.
 * Device must be locked when this function is called.
 */
static void restore_hw_context(stm32_hal_hash_ctx_t *ctx)
{
#ifdef STM32_HASH_HAL_V2
  HAL_HASH_RestoreContext(&ctx->hhash, &ctx->hw_ctx);
#endif
#ifdef STM32_HASH_HAL_V1_2
  HAL_HASH_Resume(&ctx->hhash, ctx->hw_ctx);
#endif
#ifdef STM32_HASH_HAL_V1_0
  HAL_HASH_ContextRestoring(&ctx->hhash, ctx->hw_ctx);
#endif
}

/*
 * Load STM32 HASH device hardware state from a hash operation context.
 * If there was a active operation, save STM32 HASH device hardware state
 * in that context before. The new operation context becomes the active one.
 * Device must be locked when this function is called.
 */
static void load_hw_context(stm32_hal_hash_ctx_t *ctx)
{
  if (ctx != hash_device.active_context)
  {
    if (hash_device.active_context != NULL)
    {
      save_hw_context(hash_device.active_context);
    }

    restore_hw_context(ctx);
    hash_device.active_context = ctx;
  }
}

/*
 * Feed hash operation for @p ctx context with input data.
 * Device must be locked when this function is called.
 */
static STM32_HalStatusTypeDef stm32_hash_accumulate(stm32_hal_hash_ctx_t *ctx,
                                          const uint8_t *in_buf, size_t in_len)
{
  stm32_hal_status_t hal_status = HAL_ERROR;

  if (in_len == 0)
  {
    return STM32_HAL_SUCCESS;
  }

#if defined(STM32_HASH_HAL_V2)

  hal_status = HAL_HASH_Update(&ctx->hhash, in_buf, in_len, STM32_HASH_TIMEOUT);
  {
    return STM32_HAL_ERROR;
  }

#elif defined(STM32MP1) || defined(STM32MP13)
  HAL_StatusTypeDef (*handler)(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size);

  switch (ctx->hal_algo_id)
  {
#ifdef HASH_ALGOSELECTION_MD5
  case HASH_ALGOSELECTION_MD5:
    handler = HAL_HASH_MD5_Accumulate;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA1
  case HASH_ALGOSELECTION_SHA1:
    handler = HAL_HASH_SHA1_Accumulate;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA224
  case HASH_ALGOSELECTION_SHA224:
    handler = HAL_HASHEx_SHA224_Accumulate;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA256
  case HASH_ALGOSELECTION_SHA256:
    handler = HAL_HASHEx_SHA256_Accumulate;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA384
  case HASH_ALGOSELECTION_SHA384:
    handler = HAL_HASHEx_SHA384_Accumulate;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA512
  case HASH_ALGOSELECTION_SHA512:
    handler = HAL_HASHEx_SHA512_Accumulate;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA512_224
  case HASH_ALGOSELECTION_SHA512_224:
    handler = HAL_HASHEx_SHA512_224_Accumulate;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA512_256
  case HASH_ALGOSELECTION_SHA512_256:
    handler = HAL_HASHEx_SHA512_256_Accumulate;
    break;
#endif


  default:
    /* Should not happen */
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  hal_status = handler(&ctx->hhash, (uint8_t *)in_buf, in_len);

#elif defined(STM32_HASH_HAL_V1_2)

  hal_status = HAL_HASH_Accumulate(&ctx->hhash, in_buf, in_len, STM32_HASH_TIMEOUT);

#elif defined(STM32_HASH_HAL_V1_0)
  HAL_StatusTypeDef (*handler)(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer,
                               uint32_t Size);

  switch (ctx->hal_algo_id)
  {
#ifdef HASH_ALGOSELECTION_MD5
  case HASH_ALGOSELECTION_MD5:
    handler = HAL_HASH_MD5_Accmlt;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA1
  case HASH_ALGOSELECTION_SHA1:
    handler = HAL_HASH_SHA1_Accmlt;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA224
  case HASH_ALGOSELECTION_SHA224:
    handler = HAL_HASHEx_SHA224_Accmlt;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA256
  case HASH_ALGOSELECTION_SHA256:
    handler = HAL_HASHEx_SHA256_Accmlt;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA384
  case HASH_ALGOSELECTION_SHA384:
    handler = HAL_HASHEx_SHA384_Accmlt;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA512
  case HASH_ALGOSELECTION_SHA512:
    handler = HAL_HASHEx_512_Accmlt;
    break;
#endif

  default:
    /* Should not happen */
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  hal_status = handler(&ctx->hhash, in_buf, in_len);

#endif /* STM32_HASH_HAL_V2 */

  if (hal_status != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  return STM32_HAL_SUCCESS;
}

/*
 * Complete hash operation for @p ctx context and retrieve the hash value.
 * Device must be locked when this function is called.
 */
static STM32_HalStatusTypeDef stm32_hash_finish(stm32_hal_hash_ctx_t *ctx,
                                      uint8_t *hash_buf)
{
  stm32_hal_status_t hal_status = HAL_ERROR;

#if defined(STM32_HASH_HAL_V2)
  STM32_HalStatusTypeDef status;
  uint32_t out_length;

  status = stm32_hash_accumulate(ctx, ctx->sbuf, ctx->sbuf_len);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  hal_status = HAL_HASH_Finish(&ctx->hhash, hash_buf, ctx->hash_size, &out_length,
                               STM32_HASH_TIMEOUT);
  if ((hal_status == HAL_OK) && (out_length != ctx->hash_size))
  {
    hal_status = HAL_ERROR;
  }

#elif defined(STM32MP1) || defined(STM32MP13)
  HAL_StatusTypeDef (*handler)(HASH_HandleTypeDef *hhash, uint8_t *pInBuffer, uint32_t Size,
                               uint8_t *pOutBuffer, uint32_t Timeout);

  switch (ctx->hal_algo_id)
  {
#ifdef HASH_ALGOSELECTION_MD5
  case HASH_ALGOSELECTION_MD5:
    handler = HAL_HASH_MD5_Start;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA1
  case HASH_ALGOSELECTION_SHA1:
    handler = HAL_HASH_SHA1_Start;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA224
  case HASH_ALGOSELECTION_SHA224:
    handler = HAL_HASHEx_SHA224_Start;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA256
  case HASH_ALGOSELECTION_SHA256:
    handler = HAL_HASHEx_SHA256_Start;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA384
  case HASH_ALGOSELECTION_SHA384:

    handler = HAL_HASHEx_SHA384_Start;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA512
  case HASH_ALGOSELECTION_SHA512:
    handler = HAL_HASHEx_SHA512_Start;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA512_224
  case HASH_ALGOSELECTION_SHA512_224:
    handler = HAL_HASHEx_SHA512_224_Start;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA512_256
  case HASH_ALGOSELECTION_SHA512_256:
    handler = HAL_HASHEx_SHA512_256_Start;
    break;
#endif

  default:
    /* Should not happen */
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  hal_status = handler(&ctx->hhash, ctx->sbuf, ctx->sbuf_len, hash_buf, STM32_HASH_TIMEOUT);

#elif defined(STM32_HASH_HAL_V1_2)

  hal_status = HAL_HASH_AccumulateLast(&ctx->hhash, ctx->sbuf, ctx->sbuf_len, hash_buf,
                                       STM32_HASH_TIMEOUT);

#elif defined(STM32_HASH_HAL_V1_0)
  HAL_StatusTypeDef (*handler)(HASH_HandleTypeDef *hhash,
                               const uint8_t *const pInBuffer,
                               uint32_t Size, uint8_t *pOutBuffer,
                               uint32_t Timeout);

  switch (ctx->hal_algo_id) {
#ifdef HASH_ALGOSELECTION_MD5
  case HASH_ALGOSELECTION_MD5:
    handler = HAL_HASH_MD5_Accmlt_End;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA1
  case HASH_ALGOSELECTION_SHA1:
    handler = HAL_HASH_SHA1_Accmlt_End;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA224
  case HASH_ALGOSELECTION_SHA224:
    handler = HAL_HASHEx_SHA224_Accmlt_End;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA256
  case HASH_ALGOSELECTION_SHA256:
    handler = HAL_HASHEx_SHA256_Accmlt_End;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA384
  case HASH_ALGOSELECTION_SHA384:
    handler = HAL_HASHEx_SHA384_Accmlt_End;
    break;
#endif
#ifdef HASH_ALGOSELECTION_SHA512
  case HASH_ALGOSELECTION_SHA512:
    handler = HAL_HASHEx_SHA512_Accmlt_End;
    break;
#endif
  default:
    /* Should not happen */
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  hal_status = handler(&ctx->hhash, ctx->sbuf, ctx->sbuf_len, hash_buf, STM32_HASH_TIMEOUT);

#endif /* STM32_HASH_HAL_V2 */

  if (hal_status != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  return STM32_HAL_SUCCESS;
}

/* Convert interface algo ID into an STM32 HAL ID */
static STM32_HalStatusTypeDef stm32_hal_hash_algo_id(stm32_hal_hash_ctx_t *ctx,
                                                     STM32_HalHashAlgTypeDef alg)
{
  static const uint8_t hash_size_ref[] = {
    [STM32_HAL_ALG_MD5] = 16U,
    [STM32_HAL_ALG_SHA1] = 20U,
    [STM32_HAL_ALG_SHA224] = 28U,
    [STM32_HAL_ALG_SHA256] = 32U,
    [STM32_HAL_ALG_SHA384] = 48U,
    [STM32_HAL_ALG_SHA512] = 64U,
    [STM32_HAL_ALG_SHA512_224] = 28U,
    [STM32_HAL_ALG_SHA512_256] = 32U,
  };
  static const uint8_t hash_block_ref[] = {
    [STM32_HAL_ALG_MD5] = 64U,
    [STM32_HAL_ALG_SHA1] = 64U,
    [STM32_HAL_ALG_SHA224] = 64U,
    [STM32_HAL_ALG_SHA256] = 64U,
    [STM32_HAL_ALG_SHA384] = 128U,
    [STM32_HAL_ALG_SHA512] = 128U,
    [STM32_HAL_ALG_SHA512_224] = 128U,
    [STM32_HAL_ALG_SHA512_256] = 128U,
  };

  ASSERT((sizeof(hash_size_ref) < 10) && (sizeof(hash_block_ref) < 10));

  switch (alg)
  {
#ifdef STM32_HASH_HAL_V2

    case STM32_HAL_ALG_SHA1:
      ctx->hal_algo_id = HAL_HASH_ALGO_SHA1;
      break;
    case STM32_HAL_ALG_SHA224:
      ctx->hal_algo_id = HAL_HASH_ALGO_SHA224;
      break;
    case STM32_HAL_ALG_SHA256:
      ctx->hal_algo_id = HAL_HASH_ALGO_SHA256;
      break;
 /*
  * Use HAL2 way to know if HAL_HASH_ALGO_xxx are defined in
  * enumerated type hal_hash_algo_t:
  * for SHA384/512/512_224/512_256
  * for SHA3_224/SHA3_256/SHA3_384/SHA3_512
  * for SHAKE128/SHAKE256
  */
 #if defined(HASH_CR_ALGO_2) && defined(HASH_CR_ALGO_3)
  #if defined(STM32C5)
    case STM32_HAL_ALG_SHA384:
      ctx->hal_algo_id = HAL_HASH_ALGO_SHA384;
      break;
    case STM32_HAL_ALG_SHA512:
      ctx->hal_algo_id = HAL_HASH_ALGO_SHA512;
      break;
    case STM32_HAL_ALG_SHA512_224:
      ctx->hal_algo_id = HAL_HASH_ALGO_SHA512224;
      break;
    case STM32_HAL_ALG_SHA512_256:
      ctx->hal_algo_id = HAL_HASH_ALGO_SHA512256;
      break;
  #endif /* STM32C5 */
 #endif /* HASH_CR_ALGO_2 && HASH_CR_ALGO_3 */

#else /* STM32_HASH_HAL_V2 */

 #if defined(HASH_ALGOSELECTION_MD5)
    case STM32_HAL_ALG_MD5:
      ctx->hal_algo_id = HASH_ALGOSELECTION_MD5;
      break;
 #endif
 #if defined(HASH_ALGOSELECTION_SHA1)
    case STM32_HAL_ALG_SHA1:
      ctx->hal_algo_id = HASH_ALGOSELECTION_SHA1;
      break;
 #endif
 #if defined(HASH_ALGOSELECTION_SHA224)
    case STM32_HAL_ALG_SHA224:
      ctx->hal_algo_id = HASH_ALGOSELECTION_SHA224;
      break;
 #endif
 #if defined(HASH_ALGOSELECTION_SHA256)
    case STM32_HAL_ALG_SHA256:
      ctx->hal_algo_id = HASH_ALGOSELECTION_SHA256;
      break;
 #endif
 #if defined(HASH_ALGOSELECTION_SHA384)
    case STM32_HAL_ALG_SHA384:
      ctx->hal_algo_id = HASH_ALGOSELECTION_SHA384;
      break;
 #endif
 #if defined(HASH_ALGOSELECTION_SHA512)
    case STM32_HAL_ALG_SHA512:
      ctx->hal_algo_id = HASH_ALGOSELECTION_SHA512;
      break;
 #endif
 #if defined(HASH_ALGOSELECTION_SHA512_224)
    case STM32_HAL_ALG_SHA512_224:
      ctx->hal_algo_id = HASH_ALGOSELECTION_SHA512_224;
      break;
 #endif
 #if defined(HASH_ALGOSELECTION_SHA512_256)
    case STM32_HAL_ALG_SHA512_256:
      ctx->hal_algo_id = HASH_ALGOSELECTION_SHA512_256;
      break;
 #endif

#endif /* STM32_HASH_HAL_V2 */
    default:
      return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  ASSERT(alg < STM32_HAL_ALG_COUNT);

  ctx->hash_size = hash_size_ref[alg];
  ASSERT(ctx->hash_size != 0);

  ctx->hash_block_size = hash_block_ref[alg];
  ASSERT(ctx->hash_block_size != 0);

  return STM32_HAL_SUCCESS;
}

/*
 * STM32 HASH API functions exposed to PSA Crypto Driver interface
 */

STM32_HalStatusTypeDef STM32_HalHashSetup(stm32_hal_hash_ctx_t *ctx,
                                          STM32_HalHashAlgTypeDef alg)
{
  STM32_HalStatusTypeDef status;

  memset(ctx, 0, sizeof(*ctx));

  status = stm32_hal_hash_algo_id(ctx, alg);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  lock_device_mutex();

  if (increment_operation_counter())
  {
    enable_hash_clock();
  }

  if (hash_device.active_context != NULL && hash_device.active_context != ctx)
  {
    save_hw_context(hash_device.active_context);
    hash_device.active_context = NULL;
  }

  status = init_configure_hash_hal(ctx);

  if (status == STM32_HAL_SUCCESS)
  {
    ctx->first = STM32_HASH_EXTRA_BYTES;
    hash_device.active_context = ctx;

    ctx->initialized = 1;
  }
  else
  {
    if (decrement_operation_counter())
    {
      disable_hash_clock();
    }
  }

  unlock_device_mutex();

  return status;
}

STM32_HalStatusTypeDef STM32_HalHashClone(const stm32_hal_hash_ctx_t *src_ctx,
                                          stm32_hal_hash_ctx_t *dst_ctx)
{
  if (src_ctx->initialized != 1)
  {
    return STM32_HAL_BAD_STATE;
  }

  lock_device_mutex();

  (void)increment_operation_counter();
  enable_hash_clock();

  /* Save source context current HW state if it is the active one */
  if (hash_device.active_context == src_ctx)
  {
    save_hw_context(dst_ctx);
  }

  unlock_device_mutex();

  return STM32_HAL_SUCCESS;

}

STM32_HalStatusTypeDef STM32_HalHashUpdate(stm32_hal_hash_ctx_t *ctx,
                                           const uint8_t *input, size_t input_length)
{
  STM32_HalStatusTypeDef status;
  size_t currentlen = input_length;

  if (ctx->initialized != 1)
  {
    return STM32_HAL_BAD_STATE;
  }

  if (currentlen < (ctx->hash_block_size + ctx->first - ctx->sbuf_len))
  {
    /* only store input data in context buffer */
    memcpy(ctx->sbuf + ctx->sbuf_len, input, currentlen);
    ctx->sbuf_len += currentlen;
  }
  else
  {
    /* fill context buffer until hash block size bytes, and process it */
    memcpy(ctx->sbuf + ctx->sbuf_len, input, (ctx->hash_block_size + ctx->first - ctx->sbuf_len));
    currentlen -= (ctx->hash_block_size + ctx->first - ctx->sbuf_len);

    lock_device_mutex();
    load_hw_context(ctx);

    status = stm32_hash_accumulate(ctx, ctx->sbuf, ctx->hash_block_size + ctx->first);

    if (status == STM32_HAL_SUCCESS)
    {
      /* Process following input data with size multiple of the hash block size */
      size_t iter = currentlen / ctx->hash_block_size;

      if (iter != 0)
      {
        status = stm32_hash_accumulate(ctx,
                                       input + ctx->hash_block_size + ctx->first - ctx->sbuf_len,
                                       iter * ctx->hash_block_size);
      }
    }

    /* following blocks on 16 words */
    ctx->first = 0;

    unlock_device_mutex();

    if (status != STM32_HAL_SUCCESS)
    {
      return status;
    }

    /* Store only the remaining input data up to hash block size minus 1 byte */
    ctx->sbuf_len = currentlen % ctx->hash_block_size;
    if (ctx->sbuf_len != 0)
    {
      memcpy(ctx->sbuf, input + input_length - ctx->sbuf_len, ctx->sbuf_len);
    }
  }

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalHashFinish(stm32_hal_hash_ctx_t *ctx,
                                           uint8_t *hash, size_t hash_size,
                                           size_t *hash_length)
{
  STM32_HalStatusTypeDef status;

  if (ctx->initialized != 1)
  {
    return STM32_HAL_BAD_STATE;
  }

  if (hash_size < ctx->hash_size)
  {
    return STM32_HAL_BUFFER_TOO_SMALL;
  }

  lock_device_mutex();
  load_hw_context(ctx);

  status = stm32_hash_finish(ctx, hash);

  unlock_device_mutex();

  if (status == STM32_HAL_SUCCESS)
  {
    *hash_length = ctx->hash_size;
  }

  return status;
}

STM32_HalStatusTypeDef STM32_HalHashAbort(stm32_hal_hash_ctx_t *ctx)
{
  lock_device_mutex();

  if (hash_device.active_context == ctx)
  {
    hash_device.active_context = NULL;
  }

  if (decrement_operation_counter())
  {
    disable_hash_clock();
  }

  unlock_device_mutex();

  memset(ctx, 0, sizeof(*ctx));

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalHashInit(void)
{
#if defined(MBEDTLS_THREADING_C)
  mbedtls_mutex_init(&hash_device.mutex);
#endif

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalHashSuspend(void)
{
  if (hash_device.active_context != NULL)
  {
    save_hw_context(hash_device.active_context);
  }

  disable_hash_clock();

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalHashResume(void)
{
  if (hash_device.operation_refcount != 0)
  {
    enable_hash_clock();

    if (hash_device.active_context != NULL)
    {
      restore_hw_context(hash_device.active_context);
    }
  }

  return STM32_HAL_SUCCESS;
}
#endif /* STM32_HAL_HASH_DRIVER_ENABLED */
