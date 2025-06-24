/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_pcd.c
  * @author  MCD Application Team
  * @brief   PCD HAL module driver wrapper.
  *          This file includes the relevant driver file for firmware
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#if defined(STM32MP257Cxx)
#include "stm32mp2xx_hal_pcd_drd.c"
#else
#include "stm32mp2xx_hal_pcd_otg.c"
#endif /*STM32MP257Cxx*/

