/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    local_debug_tables.h
  * @author  GPM WBL Application Team
  * @brief   Real Time Debug module System and Link Layer signal
             correspondence tables
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

#ifndef LOCAL_DEBUG_TABLES_H
#define LOCAL_DEBUG_TABLES_H

#if(RT_DEBUG_GPIO_MODULE == 1)

/*******************************/
/** System local signal table **/
/*******************************/

static const rt_debug_signal_t system_debug_table[] = {

#if (USE_RT_DEBUG_LOW_POWER_STOP_MODE_ENTER == 1)
  [LOW_POWER_STOP_MODE_ENTER] = RT_DEBUG_LOW_POWER_STOP_MODE_ENTER,
#else
  [LOW_POWER_STOP_MODE_ENTER] = RT_DEBUG_SIGNAL_UNUSED,
#endif /* USE_RT_DEBUG_LOW_POWER_STOP_MODE_ENTER */

#if (USE_RT_DEBUG_LOW_POWER_STOP_MODE_EXIT == 1)
  [LOW_POWER_STOP_MODE_EXIT] = RT_DEBUG_LOW_POWER_STOP_MODE_EXIT,
#else
  [LOW_POWER_STOP_MODE_EXIT] = RT_DEBUG_SIGNAL_UNUSED,
#endif /* USE_RT_DEBUG_LOW_POWER_STOP_MODE_EXIT */

#if (USE_RT_DEBUG_LOW_POWER_STOP_MODE_ACTIVE == 1)
  [LOW_POWER_STOP_MODE_ACTIVE] = RT_DEBUG_LOW_POWER_STOP_MODE_ACTIVE,
#else
  [LOW_POWER_STOP_MODE_ACTIVE] = RT_DEBUG_SIGNAL_UNUSED,
#endif /* USE_RT_DEBUG_LOW_POWER_STOP_MODE_ACTIVE */

#if (USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ENTER == 1)
  [LOW_POWER_STANDBY_MODE_ENTER] = RT_DEBUG_LOW_POWER_STANDBY_MODE_ENTER,
#else
  [LOW_POWER_STANDBY_MODE_ENTER] = RT_DEBUG_SIGNAL_UNUSED,
#endif /* USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ENTER */

#if (USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_EXIT == 1)
  [LOW_POWER_STANDBY_MODE_EXIT] = RT_DEBUG_LOW_POWER_STANDBY_MODE_EXIT,
#else
  [LOW_POWER_STANDBY_MODE_EXIT] = RT_DEBUG_SIGNAL_UNUSED,
#endif /* USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_EXIT */

#if (USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE == 1)
  [LOW_POWER_STANDBY_MODE_ACTIVE] = RT_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE,
#else
  [LOW_POWER_STANDBY_MODE_ACTIVE] = RT_DEBUG_SIGNAL_UNUSED,
#endif /* USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE */
};

#endif /* RT_DEBUG_GPIO_MODULE */

#endif /* LOCAL_DEBUG_TABLES_H*/
