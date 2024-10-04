/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_debug_signal_def.h
  * @author  GPM WBL Application Team
  * @brief   Real Time Debug module application signal definition
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

#if (USE_RT_DEBUG_APP_APPE_INIT == 1)
  RT_DEBUG_APP_APPE_INIT,
#endif /* USE_RT_DEBUG_APP_APPE_INIT */

#if (USE_RT_DEBUG_APP_STACK_PROCESS == 1)
  RT_DEBUG_APP_STACK_PROCESS,
#endif /* USE_RT_DEBUG_APP_STACK_PROCESS */

#if (USE_RT_DEBUG_APP_BLE_NOTIF == 1)
  RT_DEBUG_APP_BLE_NOTIF,
#endif /* USE_RT_DEBUG_APP_BLE_NOTIF */

#if (USE_RT_DEBUG_APP_BLE_NO_RESOURCES == 1)
  RT_DEBUG_APP_BLE_NO_RESOURCES,
#endif /* USE_RT_DEBUG_APP_BLE_NO_RESOURCES */
