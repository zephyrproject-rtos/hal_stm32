/**
  ******************************************************************************
  * @file    stm32_hal_rng.h
  * @author  MCD Application Team
  * @brief   Header for stm32_hal_rng.c module
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
#ifndef STM32_HAL_RNG_H
#define STM32_HAL_RNG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal_core_config.h"
#include "stm32_hal_types.h"

#if defined(STM32_HAL_RNG_DRIVER_ENABLED)

#if defined(RCC_RNGCLKSOURCE_HSI48)
#define RNGCLKSOURCE_HSI RCC_RNGCLKSOURCE_HSI48
#elif defined(RCC_RNGCLKSOURCE_HSI16KER)
#define RNGCLKSOURCE_HSI RCC_RNGCLKSOURCE_HSI16KER
#else
#define RNGCLKSOURCE_HSI RCC_RNGCLKSOURCE_HSI
#endif /* RCC_RNGCLKSOURCE_HSI48 */

/* Exported functions ------------------------------------------------------- */
STM32_HalStatusTypeDef STM32_RNGGetRandom(uint8_t *output, size_t output_size, size_t *output_length);

#endif /* STM32_HAL_RNG_DRIVER_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_RNG_H */
