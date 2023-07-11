/**
  ******************************************************************************
  * @file    stm32h5xx_util_i3c.h
  * @author  MCD Application Team
  * @brief   Header of stm32h5xx_util_i3c.c
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I3C_UTILITY_H
#define __I3C_UTILITY_H

/* Includes ------------------------------------------------------------------*/
#if defined (USE_HAL_DRIVER)
#include "stm32h5xx_hal.h"
#else
#include "stm32h5xx_ll_i3c.h"
#endif /* USE_HAL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup I3C_BUS_TYPE I3C BUS TYPE
  * @{
  */
#define I3C_PURE_I3C_BUS        0U      /*!< Pure I3C bus, no I2C    */
#define I3C_MIXED_BUS           1U      /*!< Mixed bus I3C and I2C   */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
ErrorStatus I3C_CtrlTimingComputation(LL_I3C_CtrlBusConfTypeDef *pConfig, uint32_t clockSrcFreq, uint32_t i3cFreq,
                                      uint32_t i2cFreq, uint32_t dutyCycle, uint32_t busType);
ErrorStatus I3C_TgtTimingComputation(LL_I3C_TgtBusConfTypeDef *pConfig, uint32_t clockSrcFreq);

#endif /* __I3C_UTILITY_H */
