/**
  ******************************************************************************
  * @file    stm32_hal_aes_private.h
  * @author  MCD Application Team
  * @brief   Header for AES related drivers
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
#ifndef STM32_HAL_AES_PRIVATE_H
#define STM32_HAL_AES_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32_hal_aes_types.h"
#include "stm32_hal_core_config.h"
#include "stm32_hal_types.h"
#include "stm32_hal_private.h"
#include "stm32_soc_hal.h"

#include <stdbool.h>

#define ST_HAL_AES_TIMEOUT     0xFFU

/*
 * CTX_AES_KEY_xxxBIT is defined and holds the HAL key size ID
 * when the key size is supported by the hardware device (and HAL drivers)
 */
#if defined(STM32_AES_HAL_V2)
#define CTX_AES_KEY_128BIT      HAL_AES_KEY_SIZE_128BIT
#define CTX_AES_KEY_256BIT      HAL_AES_KEY_SIZE_256BIT
#else /* STM32_AES_HAL_V2 */
 #if defined(CRYP_KEYSIZE_128B)
#define CTX_AES_KEY_128BIT      CRYP_KEYSIZE_128B
 #endif
 #if defined(CRYP_KEYSIZE_192B)
#define CTX_AES_KEY_192BIT      CRYP_KEYSIZE_192B
 #endif
 #if defined(CRYP_KEYSIZE_256B)
#define CTX_AES_KEY_256BIT      CRYP_KEYSIZE_256B
 #endif
#endif /* STM32_AES_HAL_V2 */

/**
 * 32-bit integer manipulation macros (big endian)
 */
#define READ_U32_BE(ptr, off)                          \
  (((uint32_t)((uint8_t *)(ptr))[(off)    ] << 24 ) |  \
   ((uint32_t)((uint8_t *)(ptr))[(off) + 1] << 16 ) |  \
   ((uint32_t)((uint8_t *)(ptr))[(off) + 2] <<  8 ) |  \
   ((uint32_t)((uint8_t *)(ptr))[(off) + 3]))

/* Helper function for LE to BE conversion */
static inline void read_u32_swapped(uint32_t *out, const uint8_t *in,
                                    size_t byte_size)
{
  size_t i;

  for (i = 0; i < byte_size; i += sizeof(uint32_t))
  {
    out[i / sizeof(uint32_t)] = READ_U32_BE(in, i);
  }
}

/*
 * AES/CRYP/SAES common function to manage access to hardware device
 * and save/reestore the hardware context related to a operation context.
 */

/* Function type for the callback passed to stm32_hal_aes_init_hal_hw()  */
typedef STM32_HalStatusTypeDef (*stm32_hal_aes_hal_config_func_t)(stm32_hal_aes_ctx_t *ctx);

/*
 * Get access to hardware device, possibly initializing the HAL and run its
 * configuration function (callback function passed as argument) if not
 * already initialized and configured.
 * Upon successful completion, the mutex for concurrent access protection
 * on the hardware device is locked. It must be unlocked with
 * stm32_hal_aes_put_hw_context().
 */
STM32_HalStatusTypeDef stm32_hal_aes_get_hal_hw(stm32_hal_aes_ctx_t *ctx,
                                                stm32_hal_aes_hal_config_func_t config_fn);

/* Unlock access to the hardware device */
void stm32_hal_aes_put_hal_hw(void);

/*
 * The operation context is being destroyed and will no more request access
 * to the device.
 */
void stm32_hal_aes_release_hal_hw(stm32_hal_aes_ctx_t *ctx);

/* Check if the key size is supported and provide the related HAL ID */
static inline STM32_HalStatusTypeDef stm32_hal_aes_key_size_id(size_t key_byte_size,
                                                               uint32_t *out_id)
{
  uint32_t id;

  switch (key_byte_size)
  {
#ifdef CTX_AES_KEY_128BIT
  case 16U:
    id = CTX_AES_KEY_128BIT;
    break;
#endif /* CTX_AES_KEY_128BIT */

#ifdef CTX_AES_KEY_192BIT
  case 24U:
    id = CTX_AES_KEY_192BIT;
    break;
#endif /* CTX_AES_KEY_192BIT */

#ifdef CTX_AES_KEY_256BIT
  case 32U:
    id = CTX_AES_KEY_256BIT;
    break;
#endif /* CTX_AES_KEY_256BIT */

  default:
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  if (out_id != NULL)
  {
    *out_id = id;
  }

  return STM32_HAL_SUCCESS;
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_AES_PRIVATE_H */

