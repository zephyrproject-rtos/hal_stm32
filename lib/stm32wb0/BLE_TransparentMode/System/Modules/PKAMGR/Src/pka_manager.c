/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    pka_manager.c
  * @author  GPM WBL Application Team
  * @brief   This file provides utility functions for concurrent access to PKA
  *          peripheral.
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

/* Includes ------------------------------------------------------------------*/
#include "pka_manager.h"
#include "stm32wb0x.h"

/** @defgroup PKA_Manager  PKA Manager
* @{
*/

/** @defgroup PKA_Manager_Private_Variables Private Variables
* @{
*/

/**
* @}
*/

/** @defgroup PKA_Manager_TypesDefinitions Private Type Definitions
* @{
*/

/* Internal state of the PKA */
typedef enum
{
  PKAMGR_STATE_READY     =  0,
  PKAMGR_STATE_IDLE,
  PKAMGR_STATE_RESET,
  PKAMGR_STATE_BUSY
} PKAMGR_State;

/**
* @}
*/

/** @defgroup PKA_Manager_Private_Defines Private Defines
* @{
*/
#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
__disable_irq(); \
  /* Must be called in the same or in a lower scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)
/**
* @}
*/

/** @defgroup PKA_Manager_Private_Variables Private Variables
* @{
*/
static volatile uint32_t internalState = PKAMGR_STATE_RESET;
/**
* @}
*/

/** @defgroup PKA_Manager_Private_FunctionPrototypes Private Function Prototypes
* @{
*/
PKAMGR_ResultStatus HW_PKA_PrivateInit(void);

PKAMGR_ResultStatus HW_PKA_PrivateDeinit(void);

PKAMGR_ResultStatus PKAMGR_Status(void);
/**
* @}
*/

/** @defgroup PKA_Manager_Public_Functions Public Functions
* @{
*/
PKAMGR_ResultStatus PKAMGR_Init(void)
{
    internalState = PKAMGR_STATE_IDLE;

  return PKAMGR_SUCCESS;
}

PKAMGR_ResultStatus PKAMGR_Deinit(void)
{
    internalState = PKAMGR_STATE_RESET;

  return PKAMGR_SUCCESS;
}

PKAMGR_ResultStatus PKAMGR_SleepCheck(void)
{
  PKAMGR_ResultStatus return_value = PKAMGR_ERR_BUSY;

  if(internalState == PKAMGR_STATE_IDLE)
    return_value = PKAMGR_SUCCESS;

  return return_value;
}

PKAMGR_ResultStatus PKAMGR_Lock()
{
  PKAMGR_ResultStatus return_value = PKAMGR_SUCCESS;

  /* Only one consumer (Application layer or Stack) can use the PKA at the time */
  ATOMIC_SECTION_BEGIN();
  if(internalState != PKAMGR_STATE_IDLE)
  {
    return_value = PKAMGR_ERR_BUSY;
  }
  else
  {
    /* Lock mechanism to access concurrently at the PKA resource */
    internalState = PKAMGR_STATE_BUSY;
  }
  ATOMIC_SECTION_END();

  return return_value;
}

PKAMGR_ResultStatus PKAMGR_Unlock()
{
  PKAMGR_ResultStatus return_value = PKAMGR_SUCCESS;

  /* Only one consumer (Application layer or Stack) can use the PKA at the time */
  ATOMIC_SECTION_BEGIN();
  if(internalState != PKAMGR_STATE_BUSY)
  {
    return_value = PKAMGR_ERR_BUSY;
  }
  else
  {
    /* Unlock mechanism to access concurrently at the PKA resource */
    internalState = PKAMGR_STATE_IDLE;
  }
  ATOMIC_SECTION_END();

  return return_value;
}

PKAMGR_ResultStatus PKAMGR_StartP256PublicKeyGeneration(const uint32_t *privateKey, PKAMGR_funcCB funcCB)
{
  return HW_PKA_StartP256DHkeyGeneration(privateKey, (uint32_t *)&PKAStartPoint[0], funcCB);
}

__weak void PKAMGR_IRQCallback(void)
{
}

/**
* @}
*/

/**
* @}
*/
