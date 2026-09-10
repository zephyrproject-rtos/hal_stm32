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

#include "stm32_hal_aes_types.h"

typedef struct
{
  STM32_HalAesAlgTypeDef algo_id;
} stm32_hal_aes_ctx_t;

#ifdef __cplusplus
}
#endif

#endif /*STM32_HAL_AES_H */
