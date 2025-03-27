/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_usb.c
  * @author  MCD Application Team
  * @brief   USB Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
    [..]
      (#) Fill parameters of Init structure in USB_DWC3_CfgTypeDef structure.

      (#) Call USB_CoreInit() API to initialize the USB Core peripheral.

      (#) The upper HAL HCD/PCD driver will call the right routines for its internal processes.

  @endverbatim
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
#include "stm32mp2xx_ll_usb_drd.c"
#else
#include "stm32mp2xx_ll_usb_otg.c"
#endif /*STM32MP257Cxx*/

