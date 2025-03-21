/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_mce.h
  * @author  MCD Application Team
  * @brief   Header file of MCE HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP13xx_HAL_MCE_H
#define STM32MP13xx_HAL_MCE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stm32mp13xx_hal_def.h"

#if defined (MCE)

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @addtogroup MCE
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup MCE_Exported_Types MCE Exported Types
  * @{
  */

/**
  * @brief  HAL MCE region type definition
  */
typedef enum
{
  HAL_MCE_NORMAL_REGION = 0x0U,    /*!< MCE normal region */
  HAL_MCE_ENCRYPTED_REGION = 0x1U, /*!< MCE encrypted region */
} HAL_MCE_RegionTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup MCE_Exported_Constants MCE Exported Constants
  * @{
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup MCE_Exported_Macros MCE Exported Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup MCE_Exported_Functions
  * @{
  */

void HAL_MCE_Init(void);
HAL_StatusTypeDef HAL_MCE_Enable_Region(uint32_t address, uint32_t size,
                                        HAL_MCE_RegionTypeDef type);
void HAL_MCE_IRQHandler(void);

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/** @defgroup MCE_Private_Types MCE Private Types
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup MCE_Private_Variables MCE Private Variables
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup MCE_Private_Constants MCE Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup MCE_Private_Macros MCE Private Macros
  * @{
  */

/**
  * @}
  */
/* Private functions ---------------------------------------------------------*/
/** @defgroup MCE_Private_Functions MCE Private Functions
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* MCE */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP13xx_HAL_MCE_H */
