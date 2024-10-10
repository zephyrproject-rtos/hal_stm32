/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    debug_signals.h
  * @author  GPM WBL Application Team
  * @brief   Real Time Debug module System and Link Layer signal definition
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

#ifndef DEBUG_SIGNALS_H
#define DEBUG_SIGNALS_H

/**********************************************/
/** Specific System debug signals definition **/
/**********************************************/
typedef enum {
  LOW_POWER_STOP_MODE_ENTER,
  LOW_POWER_STOP_MODE_EXIT,
  LOW_POWER_STOP_MODE_ACTIVE,
  LOW_POWER_STANDBY_MODE_ENTER,
  LOW_POWER_STANDBY_MODE_EXIT,
  LOW_POWER_STANDBY_MODE_ACTIVE,
} system_debug_signal_t;

#if(RT_DEBUG_GPIO_MODULE == 1)

/*************************************/
/** Global debug signals definition **/
/*************************************/

typedef enum {
  RT_DEBUG_SIGNAL_UNUSED = 0x0,

/********************/
/** System signals **/
/********************/

#if (USE_RT_DEBUG_LOW_POWER_STOP_MODE_ENTER == 1)
  RT_DEBUG_LOW_POWER_STOP_MODE_ENTER,
#endif /* USE_RT_DEBUG_LOW_POWER_STOP_MODE_ENTER */

#if (USE_RT_DEBUG_LOW_POWER_STOP_MODE_EXIT == 1)
  RT_DEBUG_LOW_POWER_STOP_MODE_EXIT,
#endif /* USE_RT_DEBUG_LOW_POWER_STOP_MODE_EXIT */

#if (USE_RT_DEBUG_LOW_POWER_STOP_MODE_ACTIVE == 1)
  RT_DEBUG_LOW_POWER_STOP_MODE_ACTIVE,
#endif /* USE_RT_DEBUG_LOW_POWER_STOP_MODE_ACTIVE */

#if (USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ENTER == 1)
  RT_DEBUG_LOW_POWER_STANDBY_MODE_ENTER,
#endif /* USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ENTER */

#if (USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_EXIT == 1)
  RT_DEBUG_LOW_POWER_STANDBY_MODE_EXIT,
#endif /* USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_EXIT */

#if (USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE == 1)
  RT_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE,
#endif /* USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE */

#include "app_debug_signal_def.h"

  RT_DEBUG_SIGNALS_TOTAL_NUM
} rt_debug_signal_t;

#endif /* RT_DEBUG_GPIO_MODULE */

#endif /* DEBUG_SIGNALS_H */
