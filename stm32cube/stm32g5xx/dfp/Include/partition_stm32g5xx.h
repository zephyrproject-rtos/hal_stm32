/**
  ******************************************************************************
  * @file    partition_stm32g5xx.h
  * @brief   CMSIS STM32G5xx Device Header File for Initial Setup
  *          for Secure / Non-Secure Zones.
  *
  *          The file is included in system_stm32g5xx_s.c in secure application.
  *          It includes the configuration section that allows to select the
  *          STM32G5xx device partitioning file for system core secure attributes
  *          and interrupt secure and non-secure assignment.
  *
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32g5xx
  * @{
  */

#ifndef PARTITION_STM32G5XX_H
#define PARTITION_STM32G5XX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup Secure_configuration_section
  * @{
  */

#if defined(STM32G534xx)
  #include "partition_stm32g534xx.h"
#elif defined(STM32G544xx)
  #include "partition_stm32g544xx.h"
#elif defined(STM32G553xx)
  #include "partition_stm32g553xx.h"
#elif defined(STM32G554xx)
  #include "partition_stm32g554xx.h"
#elif defined(STM32G563xx)
  #include "partition_stm32g563xx.h"
#elif defined(STM32G564xx)
  #include "partition_stm32g564xx.h"
#else
  #error "Please select the target STM32G5xx device used in your application"
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PARTITION_STM32G5XX_H */
/**
  * @}
  */

/**
  * @}
  */
