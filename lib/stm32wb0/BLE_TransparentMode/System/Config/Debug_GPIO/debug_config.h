/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    debug_config.h
  * @author  GPM WBL Application Team
  * @brief   Real Time Debug module general configuration file
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

#ifndef DEBUG_CONFIG_H
#define DEBUG_CONFIG_H

#include "app_conf.h"

#if(RT_DEBUG_GPIO_MODULE == 1)

/*********************************/
/** GPIO debug signal selection **/
/*********************************/

#define USE_RT_DEBUG_LOW_POWER_STOP_MODE_ENTER                (0)
#define GPIO_DEBUG_LOW_POWER_STOP_MODE_ENTER                  {GPIOA, GPIO_PIN_0}

#define USE_RT_DEBUG_LOW_POWER_STOP_MODE_EXIT                 (0)
#define GPIO_DEBUG_LOW_POWER_STOP_MODE_EXIT                   {GPIOA, GPIO_PIN_0}

#define USE_RT_DEBUG_LOW_POWER_STOP_MODE_ACTIVE               (0)
#define GPIO_DEBUG_LOW_POWER_STOP_MODE_ACTIVE                 {GPIOA, GPIO_PIN_0}

#define USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ENTER             (0)
#define GPIO_DEBUG_LOW_POWER_STANDBY_MODE_ENTER               {GPIOA, GPIO_PIN_0}

#define USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_EXIT              (0)
#define GPIO_DEBUG_LOW_POWER_STANDBY_MODE_EXIT                {GPIOA, GPIO_PIN_0}

#define USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE            (0)
#define GPIO_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE              {GPIOA, GPIO_PIN_0}

/* Application signal selection and GPIO assignment.
   CAN BE MODIFIED BY USER */

#define USE_RT_DEBUG_APP_APPE_INIT                            (1)
#define GPIO_DEBUG_APP_APPE_INIT                              {GPIOA, GPIO_PIN_8}

#define USE_RT_DEBUG_APP_STACK_PROCESS                        (0)
#define GPIO_DEBUG_APP_STACK_PROCESS                          {GPIOA, GPIO_PIN_9}

#define USE_RT_DEBUG_APP_BLE_NOTIF                            (0)
#define GPIO_DEBUG_APP_BLE_NOTIF                              {GPIOA, GPIO_PIN_11}

#define USE_RT_DEBUG_APP_BLE_NO_RESOURCES                     (0)
#define GPIO_DEBUG_APP_BLE_NO_RESOURCES                       {GPIOB, GPIO_PIN_8}

#endif /* RT_DEBUG_GPIO_MODULE */

/******************************************************************/
/** Association table between general debug signal and used gpio **/
/******************************************************************/

#include "debug_signals.h"

#if(RT_DEBUG_GPIO_MODULE == 1)

#include "stm32wb0x_hal.h"

typedef struct {
  GPIO_TypeDef* GPIO_port;
  uint16_t GPIO_pin;
} st_gpio_debug_t;

static const st_gpio_debug_t general_debug_table[] = {

#if (USE_RT_DEBUG_LOW_POWER_STOP_MODE_ENTER == 1)
  [RT_DEBUG_LOW_POWER_STOP_MODE_ENTER] = GPIO_DEBUG_LOW_POWER_STOP_MODE_ENTER,
#endif /* USE_RT_DEBUG_LOW_POWER_STOP_MODE_ENTER */

#if (USE_RT_DEBUG_LOW_POWER_STOP_MODE_EXIT == 1)
  [RT_DEBUG_LOW_POWER_STOP_MODE_EXIT] = GPIO_DEBUG_LOW_POWER_STOP_MODE_EXIT,
#endif /* USE_RT_DEBUG_LOW_POWER_STOP_MODE_EXIT */

#if (USE_RT_DEBUG_LOW_POWER_STOP_MODE_ACTIVE == 1)
  [RT_DEBUG_LOW_POWER_STOP_MODE_ACTIVE] = GPIO_DEBUG_LOW_POWER_STOP_MODE_ACTIVE,
#endif /* USE_RT_DEBUG_LOW_POWER_STOP_MODE_ACTIVE */

#if (USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ENTER == 1)
  [RT_DEBUG_LOW_POWER_STANDBY_MODE_ENTER] = GPIO_DEBUG_LOW_POWER_STANDBY_MODE_ENTER,
#endif /* USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ENTER */

#if (USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_EXIT == 1)
  [RT_DEBUG_LOW_POWER_STANDBY_MODE_EXIT] = GPIO_DEBUG_LOW_POWER_STANDBY_MODE_EXIT,
#endif /* USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_EXIT */

#if (USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE == 1)
  [RT_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE] = GPIO_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE,
#endif /* USE_RT_DEBUG_LOW_POWER_STANDBY_MODE_ACTIVE */

/************************************************/
/** Application signals in general debug table **/
/************************************************/

#if (USE_RT_DEBUG_APP_APPE_INIT == 1)
  [RT_DEBUG_APP_APPE_INIT] = GPIO_DEBUG_APP_APPE_INIT,
#endif /* USE_RT_DEBUG_APP_APPE_INIT */

#if (USE_RT_DEBUG_APP_STACK_PROCESS == 1)
  [RT_DEBUG_APP_STACK_PROCESS] = GPIO_DEBUG_APP_STACK_PROCESS,
#endif /* USE_RT_DEBUG_APP_STACK_PROCESS */

#if (USE_RT_DEBUG_APP_BLE_NOTIF == 1)
  [RT_DEBUG_APP_BLE_NOTIF] = GPIO_DEBUG_APP_BLE_NOTIF,
#endif /* USE_RT_DEBUG_APP_BLE_NOTIF */

#if (USE_RT_DEBUG_APP_BLE_NO_RESOURCES == 1)
  [RT_DEBUG_APP_BLE_NO_RESOURCES] = GPIO_DEBUG_APP_BLE_NO_RESOURCES,
#endif /* USE_RT_DEBUG_APP_BLE_NO_RESOURCES */

};

#endif /* RT_DEBUG_GPIO_MODULE */

#endif /* DEBUG_CONFIG_H */
