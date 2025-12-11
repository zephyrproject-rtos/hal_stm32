/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hw_rng.h
  * @author  GPM WBL Application Team
  * @brief   This file contains all the functions prototypes for the RNG MANAGER.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HW_RNG_H
#define HW_RNG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/** @addtogroup HW_RNG_Peripheral  RNG MANAGER
 * @{
 */

/** @defgroup HW_RNG_Exported_Types Exported Types
 * @{
 */

/* Enumerated values used to report the RNG result status after a process */
typedef enum
{
  HW_RNG_SUCCESS     =  0,
  HW_RNG_ERROR,
  HW_RNG_ERROR_TIMEOUT
} HW_RNG_ResultStatus;

/**
 * @}
 */

/** @defgroup HW_RNG_Exported_Constants  Exported Constants
 * @{
 */
/**
 * @}
 */

/** @defgroup HW_RNG_Exported_Macros           Exported Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup HW_RNG_Exported_Functions        Exported Functions
 * @{
 */
HW_RNG_ResultStatus HW_RNG_Init(void);

HW_RNG_ResultStatus HW_RNG_Deinit(void);

HW_RNG_ResultStatus HW_RNG_GetRandom16(uint16_t* num);

HW_RNG_ResultStatus HW_RNG_GetRandom32(uint32_t* num);

/**
  * @}
  */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HW_RNG_H */
