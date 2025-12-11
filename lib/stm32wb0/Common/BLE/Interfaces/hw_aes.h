/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hw_aes.h
  * @author  GPM WBL Application Team
  * @brief   This file contains all the functions prototypes for the AES MANAGER
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
#ifndef HW_AES_H
#define HW_AES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup HW_AES_Peripheral  AES MANAGER
 * @{
 */

/** @defgroup HW_AES_Exported_Types Exported Types
 * @{
 */

/* Enumerated values used to report the AES result status after a process */
typedef enum
{
  HW_AES_SUCCESS     =  0,
  HW_AES_ERROR
} HW_AES_ResultStatus;

/**
 * @}
 */

/** @defgroup HW_AES_Exported_Constants  Exported Constants
 * @{
 */
/**
 * @}
 */

/** @defgroup HW_AES_Exported_Macros           Exported Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup HW_AES_Exported_Functions        Exported Functions
 * @{
 */
HW_AES_ResultStatus HW_AES_Init(void);

HW_AES_ResultStatus HW_AES_Deinit(void);

HW_AES_ResultStatus HW_AES_Encrypt(const uint32_t *plainTextData, const uint32_t *key, uint32_t *encryptedData);

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

#endif /* HW_AES_H */
