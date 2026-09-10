/**
  ******************************************************************************
  * @file    stm32_hal_types.h
  * @author  MCD Application Team
  * @brief   Header for stm32 driver module
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
#ifndef STM32_HAL_TYPES_H
#define STM32_HAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup STM32_HAL_MODULE
  * @{
  */

/** @addtogroup CORE
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup CORE_Exported_Types CORE Exported Types
  * @{
  */

/** @defgroup CORE_Errors_Code CORE Errors Code
  * @{
  */
typedef enum
{
  STM32_HAL_SUCCESS                      = 0x00U,
  STM32_HAL_ERROR                        = 0x01U,
  STM32_HAL_WRONG_KEY_TYPE               = 0x02U,
  STM32_HAL_STORAGE_ERROR                = 0x03U,
  STM32_HAL_ERROR_NOT_SUPPORTED          = 0x04U,
  STM32_HAL_BAD_STATE                    = 0x09U,
  STM32_HAL_INVALID_ARGUMENT             = 0x10U,
  STM32_HAL_INVALID_SIGNATURE            = 0x11U,
  STM32_HAL_BUFFER_TOO_SMALL             = 0x12U,
  STM32_HAL_OUT_OF_MEMORY                = 0x13U,
} STM32_HalStatusTypeDef;

/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_TYPES_H */
