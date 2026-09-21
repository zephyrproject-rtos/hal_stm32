/**
  ******************************************************************************
  * @file    stm32_hal_aes.h
  * @author  MCD Application Team
  * @brief   Header for stm32_hal_aes.c module
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
#ifndef STM32_HAL_AES_H
#define STM32_HAL_AES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32_soc_hal.h"
#include "stm32_hal_aes_types.h"
#include "stm32_hal_core_config.h"
#include "stm32_hal_types.h"
#include <stdbool.h>

/*
 * STM32_AES_HAL_V* helper macros to differenciate between the several HAL
 * API versions for the AES/CRYP/SAES devices among STM32 SoCs.
 */
#if defined(HAL_VERSION_MAIN) && (HAL_VERSION_MAIN == 2)
#define STM32_AES_HAL_V2
#elif defined(STM32L4) || defined(STM32L1) || defined(STM32L0)
#define STM32_AES_HAL_V1_L4
#else
#define STM32_HASH_HAL_V1
#endif

#if defined(STM32_HASH_HAL_V1)
#if defined(STM32F2) || defined(STM32F4) || defined(STM32F7) || defined(STM32H7) || \
    defined(STM32MP1)
/* A few SoC HAL drivers do not provide hardware backup/restore support */
#define STM32_AES_LOCAL_SUSPEND_CONTEXT
#elif !(defined(STM32H5) || defined(STM32U3) || defined(STM32U5) || \
        defined(STM32WBA) || defined(STM32WL))
/* Most SoCs under HAL v1 have fields in the handle to save the hardware context */
#define STM32_AES_INTERNAL_SUSPEND_CONTEXT
#endif
#endif /* STM32_HASH_HAL_V1 */

#define STM32_CIPHER_BLOCK_SIZE         16
#define STM32_CIPHER_KEY_MAX_SIZE       32

/*
 * AES/CRYP/SAES hardware register storage.
 * Structure use when HAL does not provide one.
 */
struct hal_aes_hw_ctx {
  uint32_t cr;
  uint32_t iv[4];
  uint32_t suspend[8];
};

/*
 * AEAD operation context
 */
struct hal_aes_aead_config {
  size_t aad_size;              /* Expected number of additional data bytes */
  size_t current_aad_size;      /* Number of additional data byte processed */
  uint32_t *aad_b1;             /* AAD/B1 buffer paased to HAL */
  size_t b1_size;               /* Size of aad_b1 buffer */
  size_t nonce_size;            /* Size of nonce/IV */
  size_t message_size;          /* Expected number of byte in the AE message */
  size_t current_message_size;  /* Number of message bytes processed */
  size_t tag_size;              /* Byte size of the authentication tag */
  bool message_size_set;        /* True only is message size was defined from SetLengths */
  bool aad_size_set;            /* True only is AAD size was defined from SetLengths */
};

typedef struct
{
#ifdef STM32_AES_HAL_V2
  struct hal_aes_handle_s hal_handle;
#else
  CRYP_HandleTypeDef hal_handle;
#endif /* STM32_AES_HAL_V2 */

  STM32_HalAesAlgTypeDef algo_id;
  struct hal_aes_aead_config aead_config;

  uint32_t key[STM32_CIPHER_KEY_MAX_SIZE / sizeof(uint32_t)];
  uint32_t iv[STM32_CIPHER_BLOCK_SIZE / sizeof(uint32_t)];

  size_t key_byte_size;
  bool encrypt;                 /* true: encryption, false: decryption */
  bool hw_was_used;             /* Debug helper, set when STM32 HW was used */
  bool hal_initialized;

  /* Context buffer to store input data if needed */
  uint8_t sbuf[STM32_CIPHER_BLOCK_SIZE];
  /* Number of bytes stored in context buffer */
  size_t sbuf_len;

#ifndef STM32_AES_INTERNAL_SUSPEND_CONTEXT
  /* Hardware context storage */
#ifdef STM32_AES_HAL_V2
  hal_aes_save_context_t hw_ctx;
#elif defined(STM32_AES_HAL_V1_L4) || defined(STM32_AES_LOCAL_SUSPEND_CONTEXT)
  struct hal_aes_hw_ctx hw_ctx;
#else
  CRYP_ContextTypeDef hw_ctx;
#endif /* STM32_AES_HAL_V2 */
#endif
} stm32_hal_aes_ctx_t;

STM32_HalStatusTypeDef STM32_HalAesInit(stm32_hal_aes_ctx_t *ctx);

STM32_HalStatusTypeDef STM32_HalAesDeInit(stm32_hal_aes_ctx_t *ctx);

STM32_HalStatusTypeDef STM32_HalAesDeviceInit(void);

STM32_HalStatusTypeDef STM32_HalAesDeviceSuspend(void);

STM32_HalStatusTypeDef STM32_HalAesDeviceResume(void);

#ifdef __cplusplus
}
#endif

#endif /*STM32_HAL_AES_H */
