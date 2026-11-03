/**
  ******************************************************************************
  * @file    stm32_hal_aes_private.h
  * @author  MCD Application Team
  * @brief   Header for stm32_hal_aes.c module
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
#ifndef STM32_HAL_PRIVATE_H
#define STM32_HAL_PRIVATE_H

#include "stm32_hal_core_config.h"
#include "stm32_soc_hal.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STM32_STRINGIFY
#define _STM32_STRINGIFY(msg) #msg
#define STM32_STRINGIFY(msg)  _STM32_STRINGIFY(msg)
#endif /* STM32_STRINGIFY */

#if !defined(ASSERT)
 #if !defined(NDEBUG)
 /* Trap CPU upon unsatisfied condition */
#define ASSERT(cond) ({                           \
    if (!(cond))                                  \
    {                                             \
      printf("%s:%u %s(): asserting \"%s\"",      \
            __FILE__, __LINE__, __func__, STM32_STRINGIFY(cond)); \
      do { } while (1);                           \
    }                                             \
  })
 #else
#define ASSERT(cond) ({ do { } while (0); })
#endif /* !NDEBUG */
#endif /* !ASSERT */

/* Helper typedef stm32_hal_status_t for HAL return values  */
#if defined(HAL_VERSION_MAIN) && (HAL_VERSION_MAIN == 2)
typedef hal_status_t      stm32_hal_status_t;
#else
typedef HAL_StatusTypeDef stm32_hal_status_t;
#endif /* HAL_VERSION_MAIN == 2 */

#ifdef __cplusplus
}
#endif

#endif /* STM32_HAL_PRIVATE_H */

