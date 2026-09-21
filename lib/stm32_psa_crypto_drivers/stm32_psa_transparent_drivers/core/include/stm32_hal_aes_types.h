/**
  ******************************************************************************
  * @file    stm32_hal_aes_types.h
  * @author  MCD Application Team
  * @brief   Header for AES module
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
#ifndef STM32_HAL_AES_TYPES_H
#define STM32_HAL_AES_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  STM32_HAL_ALG_AES_CBC                      = 0x01U,
  STM32_HAL_ALG_AES_CTR                      = 0x02U,
  STM32_HAL_ALG_AES_ECB                      = 0x03U,
  STM32_HAL_ALG_AES_CCM                      = 0x04U,
  STM32_HAL_ALG_AES_GCM                      = 0x05U
} STM32_HalAesAlgTypeDef;

#ifdef __cplusplus
}
#endif

#endif /*STM32_HAL_AES_TYPES_H */
