/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ll_sys_if.h
  * @author  MCD Application Team
  * @brief   Header file for initiating system
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#ifndef LL_SYS_IF_H
#define LL_SYS_IF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
#define DRIFT_TIME_DEFAULT                      (13)
#define DRIFT_TIME_EXTRA_LSI2                   (9)
#define DRIFT_TIME_EXTRA_GCC_DEBUG              (6)
#ifdef __ZEPHYR__
#define DRIFT_TIME_EXTRA_ZEPHYR                 (15)
#endif

#define EXEC_TIME_DEFAULT                       (10)
#define EXEC_TIME_EXTRA_LSI2                    (3)
#define EXEC_TIME_EXTRA_GCC_DEBUG               (4)
#ifdef __ZEPHYR__
#define EXEC_TIME_EXTRA_ZEPHYR                  (15)
#endif

#define SCHDL_TIME_DEFAULT                      (20)
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
#if (USE_TEMPERATURE_BASED_RADIO_CALIBRATION == 1)
void ll_sys_bg_temperature_measurement(void);
#endif /* USE_TEMPERATURE_BASED_RADIO_CALIBRATION */
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*LL_SYS_IF_H */
