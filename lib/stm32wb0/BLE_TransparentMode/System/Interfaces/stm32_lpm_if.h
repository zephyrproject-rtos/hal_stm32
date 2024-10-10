/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32_lpm_if.h
  * @author  GPM WBL Application Team
  * @brief   Header for stm32_lpm_f.c module (device specific LP management)
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
#ifndef STM32_TINY_LPM_IF_H
#define STM32_TINY_LPM_IF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @defgroup TINY_LPM_IF TINY LPM IF
  * @{
  */

/* Exported Functions ------------------------------------------------------------------*/

/** @defgroup TINY_LPM_IF_Exported_functions TINY LPM IF Exported functions
 * @{
 */

/**
  * @brief Enters Low Power Off Mode
  */
void PWR_EnterOffMode( void );
/**
  * @brief Exits Low Power Off Mode
  */
void PWR_ExitOffMode( void );

/**
  * @brief Enters Low Power Stop Mode
  */
void PWR_EnterStopMode( void );
/**
  * @brief Exits Low Power Stop Mode
  */
void PWR_ExitStopMode( void );

/**
  * @brief Enters Low Power Sleep Mode
  */
void PWR_EnterSleepMode( void );

/**
  * @brief Exits Low Power Sleep Mode
  */
void PWR_ExitSleepMode( void );

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* STM32_TINY_LPM_IF_H */

