/**
  **********************************************************************************************************************
  * @file    stm32mp2xx_util_i3c.h
  * @author  MCD Application Team
  * @brief   Header of stm32mp2xx_util_i3c.c
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32MP2xx_UTIL_I3C_H
#define STM32MP2xx_UTIL_I3C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#if defined (USE_HAL_DRIVER)
#include "stm32mp2xx_hal.h"
#endif /* USE_HAL_DRIVER */

#if defined (USE_FULL_LL_DRIVER)
#include "stm32mp2xx_ll_i3c.h"
#endif /* USE_FULL_LL_DRIVER */

/** @addtogroup STM32MP2xx_UTIL_Driver
  * @{
  */

/** @addtogroup I3C
  * @{
  */
/* Exported define ---------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_UTIL_Exported_Define I3C Utility Exported Define
  * @{
  */

/** @defgroup I3C_UTIL_EC_BUS_TYPE I3C Utility Bus Type
  * @brief    Bus type defines which can be used with I3C_CtrlTimingComputation function
  * @{
  */
#define I3C_PURE_I3C_BUS        0U      /*!< Pure I3C bus, no I2C    */
#define I3C_MIXED_BUS           1U      /*!< Mixed bus I3C and I2C   */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup I3C_UTIL_Exported_Functions
  * @{
  */
/** @addtogroup I3C_UTIL_EF_Computation
  * @{
  */
ErrorStatus I3C_CtrlTimingComputation(LL_I3C_CtrlBusConfTypeDef *pConfig, uint32_t clockSrcFreq, uint32_t i3cFreq,
                                      uint32_t i2cFreq, uint32_t dutyCycle, uint32_t busType);
ErrorStatus I3C_TgtTimingComputation(LL_I3C_TgtBusConfTypeDef *pConfig, uint32_t clockSrcFreq);
/**
  * @}
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

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP2xx_UTIL_I3C_H */
