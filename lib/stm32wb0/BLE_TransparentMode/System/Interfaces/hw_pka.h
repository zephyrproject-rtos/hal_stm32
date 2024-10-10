/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hw_pka.h
  * @author  GPM WBL Application Team
  * @brief   This file contains all the functions prototypes for PKA stm32wb09
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
#ifndef HW_PKA_H
#define HW_PKA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @defgroup HW_PKA  PKA Manager
* @{
*/

/** @defgroup HW_PKA_Exported_Types Exported Types
* @{
*/
/**
* @}
*/

/** @defgroup HW_PKA_Exported_Constants  Exported Constants
 * @{
 */
/**
 * @}
 */

/** @defgroup HW_PKA_Exported_Macros           Exported Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup HW_PKA_Exported_Functions        Exported Functions
 * @{
 */
#if defined STM32WB09
void HW_PKA_WriteSingleInput( uint32_t index,  int size, const uint32_t* word );
#elif defined STM32WB05
void HW_PKA_WriteSingleInput( uint32_t index, uint32_t word );
#endif

#if defined STM32WB09
void HW_PKA_ReadSingleOutput( uint32_t index, uint32_t* out);
#elif defined STM32WB05
uint32_t HW_PKA_ReadSingleOutput( uint32_t index );
#endif /* STM32WB09 elif STM32WB05 */

#if defined(STM32WB06) || defined(STM32WB07)
ErrorStatus HW_PKA_SetData(uint8_t dataType, uint32_t* srcData);
ErrorStatus HW_PKA_GetData(uint8_t dataType, uint8_t* dataTarget);
ErrorStatus HW_PKA_VerifyProcess(void);
#endif

void HW_PKA_WriteOperand( uint32_t index, int size, const uint32_t* in );
void HW_PKA_ReadResult( uint32_t index, int size, uint32_t* out );
uint8_t HW_PKA_PowerSaveLevelCheck(void);
void HW_PKA_Init(void);
void HW_PKA_IRQHandler(void);
/**
* @}
*/

/**
* @}
*/

#ifdef __cplusplus
}
#endif

#endif /* HW_PKA_H */
