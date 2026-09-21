/**
  ******************************************************************************
  * @file    stm32_hal_aes.c
  * @author  MCD Application Team
  * @brief   Implementation of STM32 AES Middleware Core module
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

#include "stm32_hal_aes.h"
#include "stm32_hal_aes_private.h"
#include "stm32_hal_core_config.h"
#include "stm32_hal_private.h"
#include "stm32_soc_hal.h"

#ifdef MBEDTLS_THREADING_C
#include <mbedtls/threading.h>
#endif /* MBEDTLS_THREADING_C */

#include <string.h>
#include <stdlib.h>

/* HAL_AES_DEVICE helper macro to identify the target device for AES crypto */
#if defined(STM32_HAL_AES_DPA_DRIVER_ENABLED)
# ifdef STM32_AES_HAL_V2
#define HAL_AES_DEVICE   HAL_SAES
# else
#define HAL_AES_DEVICE   SAES
# endif /* STM32_AES_HAL_V2 */
#else
# ifdef STM32_AES_HAL_V2
#define HAL_AES_DEVICE   HAL_AES
# elif defined(AES1)
/* When 2 AES instances are integrated in, the SoC, only support AES1 */
#define HAL_AES_DEVICE   AES1
# elif defined(AES2)
#define HAL_AES_DEVICE   AES2
# elif defined(AES)
#define HAL_AES_DEVICE   AES
# elif defined(CRYP1)
/* When 2 CRYP instances are integrated in, the SoC, only support CRYP1 */
#define HAL_AES_DEVICE   CRYP1
# else
#define HAL_AES_DEVICE   CRYP
# endif /* STM32_AES_HAL_V2 */
#endif /* STM32_HAL_AES_DPA_DRIVER_ENABLED */

/* HAL_ENABLE_CLOCK() and HAL_DISABLE_CLOCK() helper macros  */
#ifdef STM32_HAL_AES_DPA_DRIVER_ENABLED
 #ifdef STM32_AES_HAL_V2
#define HAL_ENABLE_CLOCK() \
  do { HAL_RCC_RNG_EnableClock(); HAL_RCC_SAES_EnableClock(); } while (0)
#define HAL_DISABLE_CLOCK() \
  do { HAL_RCC_SAES_DisableClock(); /* Leave RNG On */ } while (0)
 #else
#define HAL_ENABLE_CLOCK()      __HAL_RCC_SAES_CLK_ENABLE()
#define HAL_DISABLE_CLOCK()     __HAL_RCC_SAES_CLK_DISABLE()
 #endif /* STM32_AES_HAL_V2 */
#else
 #ifdef STM32_AES_HAL_V2
#define HAL_ENABLE_CLOCK()      HAL_RCC_AES_EnableClock()
#define HAL_DISABLE_CLOCK()     HAL_RCC_AES_DisableClock()
 #elif defined(__HAL_RCC_AES1_CLK_ENABLE)
 /* When 2 AES instances are integrated in, the SoC, only support AES1 */
#define HAL_ENABLE_CLOCK()      __HAL_RCC_AES1_CLK_ENABLE()
#define HAL_DISABLE_CLOCK()     __HAL_RCC_AES1_CLK_DISABLE()
 #elif defined(__HAL_RCC_AES2_CLK_ENABLE)
#define HAL_ENABLE_CLOCK()      __HAL_RCC_AES2_CLK_ENABLE()
#define HAL_DISABLE_CLOCK()     __HAL_RCC_AES2_CLK_DISABLE()
 #elif defined(__HAL_RCC_AES_CLK_ENABLE)
#define HAL_ENABLE_CLOCK()      __HAL_RCC_AES_CLK_ENABLE()
#define HAL_DISABLE_CLOCK()     __HAL_RCC_AES_CLK_DISABLE()
 #elif defined(__HAL_RCC_CRYP1_CLK_ENABLE)
#define HAL_ENABLE_CLOCK()      __HAL_RCC_CRYP1_CLK_ENABLE()
#define HAL_DISABLE_CLOCK()     __HAL_RCC_CRYP1_CLK_DISABLE()
 #elif defined(__HAL_RCC_CRYP2_CLK_ENABLE)
#define HAL_ENABLE_CLOCK()      __HAL_RCC_CRYP2_CLK_ENABLE()
#define HAL_DISABLE_CLOCK()     __HAL_RCC_CRYP2_CLK_DISABLE()
 #else
#define HAL_ENABLE_CLOCK()      __HAL_RCC_CRYP_CLK_ENABLE()
#define HAL_DISABLE_CLOCK()     __HAL_RCC_CRYP_CLK_DISABLE()
 #endif /* STM32_AES_HAL_V2 */
#endif /* STM32_HAL_AES_DPA_DRIVER_ENABLED */

/*
 * struct stm32_aes_device - State of the STM32 AES/CRYP/SAES device
 *
 * @active_context - Currently active operation context or NULL if none
 * @mutex - Mutlithread access protection
 * @operation_refcount - Opened operations counter
 */
struct stm32_hal_aes_device {
  stm32_hal_aes_ctx_t *active_context;
  unsigned int operation_refcount;
#ifdef MBEDTLS_THREADING_C
  mbedtls_threading_mutex_t mutex;
#endif /* MBEDTLS_THREADING_C */
};

/* State of the STM32 device used for cipher/AEAD hardware acceleration */
static struct stm32_hal_aes_device stm32_hal_aes_device_state;

/*
 * Helper functions for the STM32 device hardware state management
 */

/* Lock mutex for hash_device access */
static void stm32_hal_aes_device_lock(void)
{
#ifdef MBEDTLS_THREADING_C
  mbedtls_mutex_lock(&stm32_hal_aes_device_state.mutex);
#endif /* MBEDTLS_THREADING_C */
}

/* Unlock mutex for hash_device access */
static void stm32_hal_aes_device_unlock(void)
{
#ifdef MBEDTLS_THREADING_C
  mbedtls_mutex_unlock(&stm32_hal_aes_device_state.mutex);
#endif /* MBEDTLS_THREADING_C */
}

/*
 * Increment the number of active operations.
 * Device access mutex must be locked when this function is called.
 * Return true if first operation, false otherwise
 */
static bool stm32_hal_aes_device_increment_refcount(void)
{
  if (stm32_hal_aes_device_state.operation_refcount == ~0)
  {
    while ( 1 )
    {
       /* Panic */
    }
  }

  stm32_hal_aes_device_state.operation_refcount++;

  return stm32_hal_aes_device_state.operation_refcount == 1;
}

/*
 * Decrement the number of active operations.
 * Device access mutex must be locked when this function is called.
 * Return true if last operation, false otherwise
 */
static bool stm32_hal_aes_device_decrement_refcount(void)
{
  if (stm32_hal_aes_device_state.operation_refcount == 0)
  {
    while ( 1 )
    {
       /* Panic */
    }
  }

  stm32_hal_aes_device_state.operation_refcount--;

  return stm32_hal_aes_device_state.operation_refcount == 0;
}

/*
 * Enable STM32 device clock
 * Device access mutex must be locked when this function is called.
 */
static void stm32_hal_aes_device_enable_clock(void)
{
#if defined(STM32_AES_HAL_V2) && defined(USE_HAL_AES_CLK_ENABLE_MODEL) && \
    (USE_HAL_AES_CLK_ENABLE_MODEL == HAL_CLK_ENABLE_PERIPH_ONLY)
  /*  Nothing to do, the HAL function takes care of the AES/SAES clock */
  return;
#endif

  HAL_ENABLE_CLOCK();
}

/*
 * Disable STM32 device clock
 * Device access mutex must be locked when this function is called.
 */
static void stm32_hal_aes_device_disable_clock(void)
{
  HAL_DISABLE_CLOCK();
}

#ifdef STM32_AES_LOCAL_SUSPEND_CONTEXT
static void save_u32_regs(uint32_t *out, volatile uint32_t *in, size_t count)
{
  while (count--)
  {
    *(out++) = *(in++);
  }
}
static void restore_u32_regs(volatile uint32_t *out, uint32_t *in, size_t count)
{
  while (count--)
  {
    *(out++) = *(in++);
  }
}

/* Local implementation not provided by the related HAL drivers */
static void stm32_hal_aes_device_save_context_local(stm32_hal_aes_ctx_t *ctx)
{
#if defined(STM32F2) || defined(STM32F4) || defined(STM32F7) || defined(STM32H7) || \
    defined(STM32MP1)
  ctx->hw_ctx.cr = ctx->hal_handle.Instance->CR;

  save_u32_regs(ctx->hw_ctx.iv, &ctx->hal_handle.Instance->IV0LR, 4);

  if (ctx->algo_id == STM32_HAL_ALG_AES_CCM)
  {
    save_u32_regs(ctx->hw_ctx.suspend, &ctx->hal_handle.Instance->CSGCM0R, 8);
  }
  if (ctx->algo_id == STM32_HAL_ALG_AES_GCM)
  {
    save_u32_regs(ctx->hw_ctx.suspend, &ctx->hal_handle.Instance->CSGCMCCM0R, 8);
  }
#else
  ASSERT(0);
#endif /* STM32F2 || STM32F4 || STM32F7 || STM32H7 */
}

static void stm32_hal_aes_device_restore_context_local(stm32_hal_aes_ctx_t *ctx)
{
#if defined(STM32F2) || defined(STM32F4) || defined(STM32F7) || defined(STM32H7) || \
    defined(STM32MP1)
  ctx->hal_handle.Instance->CR = ctx->hw_ctx.cr;

  restore_u32_regs(&ctx->hal_handle.Instance->IV0LR, ctx->hw_ctx.iv, 4);

  if (ctx->algo_id == STM32_HAL_ALG_AES_CCM)
  {
    restore_u32_regs(&ctx->hal_handle.Instance->CSGCM0R, ctx->hw_ctx.suspend, 8);
  }
  if (ctx->algo_id == STM32_HAL_ALG_AES_GCM)
  {
    restore_u32_regs(&ctx->hal_handle.Instance->CSGCMCCM0R, ctx->hw_ctx.suspend, 8);
  }

  restore_u32_regs(&ctx->hal_handle.Instance->K0LR, ctx->key,
                   ctx->key_byte_size / sizeof(uint32_t));
#else
  ASSERT(0);
#endif /* STM32F2 || STM32F4 || STM32F7 || STM32H7 */
}
#endif /* STM32_AES_LOCAL_SUSPEND_CONTEXT */

/*
 * Save STM32 device hardware state in its related operation context.
 * Device access mutex must be locked when this function is called.
 */
static void stm32_hal_aes_device_save_context(stm32_hal_aes_ctx_t *ctx)
{
#ifdef STM32_AES_HAL_V2
  ctx->hal_handle.global_state = HAL_AES_STATE_SUSPENDED;
  HAL_AES_SaveContext(&ctx->hal_handle, &ctx->hw_ctx);
#elif defined(STM32_AES_HAL_V1_L4)
  HAL_CRYPEx_Read_ControlRegister(&ctx->hal_handle, (uint8_t *)&ctx->hw_ctx.cr);
  if (ctx->algo_id != STM32_HAL_ALG_AES_ECB)
  {
    HAL_CRYPEx_Read_IVRegisters(&ctx->hal_handle, (uint8_t *)ctx->hw_ctx.iv);
  }
  if ((ctx->algo_id == STM32_HAL_ALG_AES_CCM) || (ctx->algo_id == STM32_HAL_ALG_AES_GCM))
  {
    HAL_CRYPEx_Read_SuspendRegisters(&ctx->hal_handle, (uint8_t *)ctx->hw_ctx.suspend);
  }
#elif defined(STM32_AES_INTERNAL_SUSPEND_CONTEXT)
  HAL_CRYP_Suspend(&ctx->hal_handle);
#elif defined(STM32_AES_LOCAL_SUSPEND_CONTEXT)
  stm32_hal_aes_device_save_context_local(ctx);
#else
  HAL_CRYP_SaveContext(&ctx->hal_handle, &ctx->hw_ctx);
#endif /* STM32_AES_HAL_V2 */
}

/*
 * Restore STM32 device hardware state from a hash operation context.
 * Device access mutex must be locked when this function is called.
 */
static void stm32_hal_aes_device_restore_context(stm32_hal_aes_ctx_t *ctx)
{
#ifdef STM32_AES_HAL_V2
  HAL_AES_RestoreContext(&ctx->hal_handle, &ctx->hw_ctx);
#elif defined(STM32_AES_HAL_V1_L4)
  uint32_t key_size_id;
  STM32_HalStatusTypeDef status;

  HAL_CRYPEx_Write_ControlRegister(&ctx->hal_handle, (uint8_t *)&ctx->hw_ctx.cr);

  status = stm32_hal_aes_key_size_id(ctx->key_byte_size, &key_size_id);
  ASSERT(status == STM32_HAL_SUCCESS);
  HAL_CRYPEx_Write_KeyRegisters(&ctx->hal_handle, (uint8_t *)ctx->key, key_size_id);

  if (ctx->algo_id != STM32_HAL_ALG_AES_ECB)
  {
    HAL_CRYPEx_Write_IVRegisters(&ctx->hal_handle, (uint8_t *)ctx->hw_ctx.iv);
  }
  if ((ctx->algo_id == STM32_HAL_ALG_AES_CCM) || (ctx->algo_id == STM32_HAL_ALG_AES_GCM))
  {
    HAL_CRYPEx_Write_SuspendRegisters(&ctx->hal_handle, (uint8_t *)ctx->hw_ctx.suspend);
  }
#elif defined(STM32_AES_INTERNAL_SUSPEND_CONTEXT)
  HAL_CRYP_Resume(&ctx->hal_handle);
#elif defined(STM32_AES_LOCAL_SUSPEND_CONTEXT)
  stm32_hal_aes_device_restore_context_local(ctx);
#else
  HAL_CRYP_RestoreContext(&ctx->hal_handle, &ctx->hw_ctx);
#endif /* STM32_AES_HAL_V2 */
}

/*
 * Load STM32 device hardware state from a hash operation context.
 * If there was a active operation, save STM32 HASH device hardware state
 * in that context before. The new operation context becomes the active one.
 * Device access mutex must be locked when this function is called.
 */
static void stm32_hal_aes_device_load_context(stm32_hal_aes_ctx_t *ctx)
{
  if (ctx != stm32_hal_aes_device_state.active_context)
  {
    if (stm32_hal_aes_device_state.active_context != NULL)
    {
      stm32_hal_aes_device_save_context(stm32_hal_aes_device_state.active_context);
    }

    stm32_hal_aes_device_restore_context(ctx);
    stm32_hal_aes_device_state.active_context = ctx;
  }
}

/*
 * Save the device hardware context for the active context.
 * Device access mutex must be locked when this function is called.
 */
static void stm32_hal_aes_device_save_active_context(void)
{
  if (stm32_hal_aes_device_state.active_context != NULL)
  {
    stm32_hal_aes_device_save_context(stm32_hal_aes_device_state.active_context);
    stm32_hal_aes_device_state.active_context = NULL;
  }
}

/* Set @p ctx as the active context */
static void stm32_hal_aes_device_set_active_context(stm32_hal_aes_ctx_t *ctx)
{
  ASSERT(stm32_hal_aes_device_state.active_context == NULL);
  stm32_hal_aes_device_state.active_context = ctx;
}

/* Context @p ctx is released and cannot be active */
static void stm32_hal_aes_device_context_released(stm32_hal_aes_ctx_t *ctx)
{
  if (stm32_hal_aes_device_state.active_context == ctx)
  {
    stm32_hal_aes_device_state.active_context = NULL;
  }
}

/*
 * Device hardware context managment functions
 */

STM32_HalStatusTypeDef stm32_hal_aes_get_hal_hw(stm32_hal_aes_ctx_t *ctx,
                                      stm32_hal_aes_hal_config_func_t config_fn)
{
  STM32_HalStatusTypeDef status;

  stm32_hal_aes_device_lock();

  if (ctx->hal_initialized)
  {
    stm32_hal_aes_device_load_context(ctx);

    return STM32_HAL_SUCCESS;
  }

  if (stm32_hal_aes_device_increment_refcount())
  {
    stm32_hal_aes_device_enable_clock();
  }

  /*
   * We're about to possibly access the hardware device.
   * The current hardware state need to be saved in the active context.
   */
  stm32_hal_aes_device_save_active_context();

  (void)memset(&ctx->hal_handle, 0, sizeof(ctx->hal_handle));

  status = STM32_HalAesInit(ctx);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  status = config_fn(ctx);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  /* From this point, our context is ready and is the active one  */
  ctx->hal_initialized = true;
  stm32_hal_aes_device_set_active_context(ctx);

exit:
  if (status != STM32_HAL_SUCCESS)
  {
    (void)STM32_HalAesDeInit(ctx);

    if (stm32_hal_aes_device_decrement_refcount())
    {
      stm32_hal_aes_device_disable_clock();
    }

    stm32_hal_aes_device_unlock();
  }

  return status;
}

void stm32_hal_aes_put_hal_hw(void)
{
  stm32_hal_aes_device_unlock();
}

void stm32_hal_aes_release_hal_hw(stm32_hal_aes_ctx_t *ctx)
{
  if (ctx->hal_initialized)
  {
    stm32_hal_aes_device_lock();

    stm32_hal_aes_device_load_context(ctx);

    (void)STM32_HalAesDeInit(ctx);

    stm32_hal_aes_device_context_released(ctx);

    if (stm32_hal_aes_device_decrement_refcount())
    {
      stm32_hal_aes_device_disable_clock();
    }

    stm32_hal_aes_device_unlock();

    ctx->hal_initialized = false;
  }
}

/*
 * Device init/suspend/resume functions
 */

STM32_HalStatusTypeDef STM32_HalAesDeviceInit(void)
{
#if defined(MBEDTLS_THREADING_C)
  mbedtls_mutex_init(&stm32_hal_aes_device_state.mutex);
#endif

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAesDeviceSuspend(void)
{
  if (stm32_hal_aes_device_state.active_context != NULL)
  {
    stm32_hal_aes_device_save_context(stm32_hal_aes_device_state.active_context);
  }

  stm32_hal_aes_device_disable_clock();

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAesDeviceResume(void)
{
  if (stm32_hal_aes_device_state.operation_refcount != 0)
  {
    stm32_hal_aes_device_enable_clock();

    if (stm32_hal_aes_device_state.active_context != NULL)
    {
      stm32_hal_aes_device_restore_context(stm32_hal_aes_device_state.active_context);
    }
  }

  return STM32_HAL_SUCCESS;
}

/*
 * HAL init/de-init abstraction functions
 */

STM32_HalStatusTypeDef STM32_HalAesInit(stm32_hal_aes_ctx_t *ctx)
{
  ASSERT(ctx != NULL);

  memset(&ctx->hal_handle, 0, sizeof(ctx->hal_handle));

#ifdef STM32_AES_HAL_V2
  if (HAL_AES_Init(&ctx->hal_handle, HAL_AES_DEVICE) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }
#else /* STM32_AES_HAL_V2 */
  ctx->hal_handle.Instance = HAL_AES_DEVICE;

#if !defined(STM32_AES_HAL_V1_L4)
  if (HAL_CRYP_Init(&ctx->hal_handle) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }
#endif /* !STM32_AES_HAL_V1_L4 */
#endif /* STM32_AES_HAL_V2 */

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAesDeInit(stm32_hal_aes_ctx_t *ctx)
{
#ifdef STM32_AES_HAL_V2
  HAL_AES_DeInit(&ctx->hal_handle);
#elif !defined(STM32_AES_HAL_V1_L4)
  if (HAL_CRYP_DeInit(&ctx->hal_handle) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }
#endif /* STM32_AES_HAL_V2 */

  return STM32_HAL_SUCCESS;
}
