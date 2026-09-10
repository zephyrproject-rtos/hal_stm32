/**
  ******************************************************************************
  * @file    stm32_hal_psa_random.h
  * @author  MCD Application Team
  * @brief   Header for stm32_hal_psa_random.c module
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
#ifndef STM32_HAL_PSA_RANDOM_H
#define STM32_HAL_PSA_RANDOM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#if defined(STM32_HAL_PSA_RNG_DRIVER_ENABLED)
#include "stm32_hal_rng.h"

/**
  * No APIs to declare for PSA random driver
  * PSA core uses mbedtls_platform_get_entropy()
  * and mbedtls_psa_external_get_random()
  * These functions are implemented in stm32_psa_random.c.
  */

#endif /* STM32_HAL_PSA_RNG_DRIVER_ENABLED */

#ifdef __cplusplus
}
#endif
#endif /* STM32_HAL_PSA_RANDOM_H */
