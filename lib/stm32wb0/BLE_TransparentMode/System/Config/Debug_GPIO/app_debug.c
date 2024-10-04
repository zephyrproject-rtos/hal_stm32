/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_debug.c
  * @author  GPM WBL Application Team
  * @brief   Real Time Debug module application side APIs
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

#include "app_debug.h"

/****************************/
/** Application debug APIs **/
/****************************/

void APP_DEBUG_SIGNAL_SET(app_debug_signal_t signal)
{
#if(RT_DEBUG_GPIO_MODULE == 1)
  GENERIC_DEBUG_GPIO_SET(signal, app_debug_table);
#endif /* RT_DEBUG_GPIO_MODULE */
}
void APP_DEBUG_SIGNAL_RESET(app_debug_signal_t signal)
{
#if(RT_DEBUG_GPIO_MODULE == 1)
  GENERIC_DEBUG_GPIO_RESET(signal, app_debug_table);
#endif /* RT_DEBUG_GPIO_MODULE */
}

void APP_DEBUG_SIGNAL_TOGGLE(app_debug_signal_t signal)
{
#if(RT_DEBUG_GPIO_MODULE == 1)
  GENERIC_DEBUG_GPIO_TOGGLE(signal, app_debug_table);
#endif /* RT_DEBUG_GPIO_MODULE */
}

/*******************************/
/** Debug GPIO Initialization **/
/*******************************/

void RT_DEBUG_GPIO_Init(void)
{
#if(RT_DEBUG_GPIO_MODULE == 1)
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  uint32_t general_table_size = sizeof(general_debug_table)/sizeof(general_debug_table[0]);

  GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = 0;

  for(unsigned int cpt = 0; cpt<general_table_size ; cpt++)
  {
    if(general_debug_table[cpt].GPIO_pin != RT_DEBUG_SIGNAL_UNUSED)
    {
      GPIO_InitStruct.Pin = general_debug_table[cpt].GPIO_pin;
      HAL_GPIO_Init(general_debug_table[cpt].GPIO_port, &GPIO_InitStruct);
    }
  }
#endif /* RT_DEBUG_GPIO_MODULE */
}
