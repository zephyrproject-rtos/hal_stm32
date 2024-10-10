/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    RTDebug.c
  * @author  GPM WBL Application Team
  * @brief   Real Time Debug module API definition
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#include "RTDebug.h"
#include "local_debug_tables.h"
#include "stm32wb0x_hal.h"
#include <assert.h>

#if(RT_DEBUG_GPIO_MODULE == 1)
static_assert((sizeof(general_debug_table)/sizeof(st_gpio_debug_t)) == RT_DEBUG_SIGNALS_TOTAL_NUM,
              "Debug signals number is different from debug signal table size."
);
#endif /* RT_DEBUG_GPIO_MODULE */

/***********************/
/** System debug APIs **/
/***********************/

void SYSTEM_DEBUG_SIGNAL_SET(system_debug_signal_t signal)
{
#if(RT_DEBUG_GPIO_MODULE == 1)
  GENERIC_DEBUG_GPIO_SET(signal, system_debug_table);
#endif /* RT_DEBUG_GPIO_MODULE */
}

void SYSTEM_DEBUG_SIGNAL_RESET(system_debug_signal_t signal)
{
#if(RT_DEBUG_GPIO_MODULE == 1)
  GENERIC_DEBUG_GPIO_RESET(signal, system_debug_table);
#endif /* RT_DEBUG_GPIO_MODULE */
}

void SYSTEM_DEBUG_SIGNAL_TOGGLE(system_debug_signal_t signal)
{
#if(RT_DEBUG_GPIO_MODULE == 1)
  GENERIC_DEBUG_GPIO_TOGGLE(signal, system_debug_table);
#endif /* RT_DEBUG_GPIO_MODULE */
}
