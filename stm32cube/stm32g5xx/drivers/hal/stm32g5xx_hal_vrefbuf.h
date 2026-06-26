/**
  ******************************************************************************
  * @file    stm32g5xx_hal_vrefbuf.h
  * @brief   Header file of VREFBUF HAL module.
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
#ifndef STM32G5XX_HAL_VREFBUF_H
#define STM32G5XX_HAL_VREFBUF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_vrefbuf.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

#if defined (VREFBUF)

/** @defgroup VREFBUF VREFBUF
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup VREFBUF_Exported_Types HAL VREFBUF Types
  * @{
  */
/** @defgroup VREFBUF_Exported_Types_Group1 Configuration enumerations
  * @{
  */

/**
  * @brief HAL VREFBUF instance definition.
  */
typedef enum
{
  HAL_VREFBUF = VREFBUF_BASE,                               /*!< VREFBUF instance */
} hal_vrefbuf_t;

/**
  * @brief HAL VREFBUF mode definition.
  */
typedef enum
{
  HAL_VREFBUF_MODE_PULL_DOWN        = LL_VREFBUF_MODE_PULL_DOWN,       /*!< VREFBUF is in the OFF mode */
  HAL_VREFBUF_MODE_EXT_VOLTAGE_REF  = LL_VREFBUF_MODE_EXT_VOLTAGE_REF, /*!< VREFBUF functions in external voltage reference mode */
  HAL_VREFBUF_MODE_INT_VOLTAGE_REF  = LL_VREFBUF_MODE_INT_VOLTAGE_REF, /*!< VREFBUF functions in internal voltage reference mode */
  HAL_VREFBUF_MODE_HOLD             = LL_VREFBUF_MODE_HOLD,            /*!< VREFBUF functions in hold mode */
} hal_vrefbuf_mode_t;

/**
  * @brief HAL VREFBUF voltage scale definition.
  */
typedef enum
{
  HAL_VREFBUF_VOLTAGE_2_9V    = LL_VREFBUF_VOLTAGE_SCALE0,  /*!< Voltage reference scale 0 = 2,9V   */
  HAL_VREFBUF_VOLTAGE_2_5V    = LL_VREFBUF_VOLTAGE_SCALE1,  /*!< Voltage reference scale 1 = 2,5V   */
  HAL_VREFBUF_VOLTAGE_2_048V  = LL_VREFBUF_VOLTAGE_SCALE2,  /*!< Voltage reference scale 2 = 2,048V */
  HAL_VREFBUF_VOLTAGE_1_8V    = LL_VREFBUF_VOLTAGE_SCALE3,  /*!< Voltage reference scale 3 = 1,8V   */
} hal_vrefbuf_voltage_scale_t;

/**
  * @}
  */

/** @defgroup VREFBUF_Exported_Types_Group2 Configuration structure
  * @{
  */
/**
  * @brief HAL VREFBUF configuration definition.
  */
typedef struct
{
  hal_vrefbuf_mode_t mode;                     /*!< VREFBUF functional mode     */
  hal_vrefbuf_voltage_scale_t voltage_scale;   /*!< VREFBUF voltage scale: this parameter is only applicable
                                                    when VREFBUF is set to use the internal reference voltage mode */
} hal_vrefbuf_config_t;

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup VREFBUF_Exported_Functions  VREFBUF Exported Functions
  * @{
  */

/** @defgroup VREFBUF_Exported_Functions_Group1 Configuration functions
  * @{
  */
hal_vrefbuf_t       HAL_VREFBUF_GetInstance(hal_vrefbuf_t instance);
VREFBUF_TypeDef    *HAL_VREFBUF_GetLLInstance(hal_vrefbuf_t instance);
hal_status_t        HAL_VREFBUF_SetConfig(hal_vrefbuf_t instance, const hal_vrefbuf_config_t *p_config);
void                HAL_VREFBUF_GetConfig(hal_vrefbuf_t instance, hal_vrefbuf_config_t *p_config);
hal_status_t        HAL_VREFBUF_SetMode(hal_vrefbuf_t instance, hal_vrefbuf_mode_t mode);
hal_vrefbuf_mode_t  HAL_VREFBUF_GetMode(hal_vrefbuf_t instance);
hal_status_t        HAL_VREFBUF_SetVoltageScale(hal_vrefbuf_t instance, hal_vrefbuf_voltage_scale_t voltage_scale);
hal_vrefbuf_voltage_scale_t  HAL_VREFBUF_GetVoltageScale(hal_vrefbuf_t instance);

/**
  * @}
  */

/** @defgroup VREFBUF_Exported_Functions_Group2 Advanced configuration functions
  * @{
  */
hal_status_t  HAL_VREFBUF_SetTrimming(hal_vrefbuf_t instance, uint32_t trimming_value);
uint32_t  HAL_VREFBUF_GetTrimming(hal_vrefbuf_t instance);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* VREFBUF */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_HAL_VREFBUF_H */
