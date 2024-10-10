/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    flash_manager.h
  * @author  MCD Application Team
  * @brief   Header for flash_manager.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FLASH_MANAGER_H
#define FLASH_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "utilities_common.h"
#include "stm_list.h"

/* Exported types ------------------------------------------------------------*/

/* Flash Manager command status */
typedef enum
{
  FM_OK,    /* The Flash Manager is available and a window request is scheduled */
  FM_BUSY,  /* The Flash Manager is busy and the caller will be called back when it is available */
  FM_ERROR  /* An error occurred while processing the command */
} FM_Cmd_Status_t;

/* Flash operation status */
typedef enum
{
  FM_OPERATION_COMPLETE,  /* The requested flash operation is complete */
  FM_OPERATION_AVAILABLE  /* A flash operation can be requested */
} FM_FlashOp_Status_t;

/**
 * @brief  Flash Manager callback node type to store them in a chained list
 */
typedef struct FM_CallbackNode
{
  tListNode NodeList;  /* Next and previous nodes in the list */
  void (*Callback)(FM_FlashOp_Status_t Status);  /* Callback function pointer for Flash Manager caller */
}FM_CallbackNode_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
FM_Cmd_Status_t FM_Write(uint32_t *Src, uint32_t *Dest, int32_t Size, FM_CallbackNode_t *CallbackNode);
FM_Cmd_Status_t FM_Erase(uint32_t FirstSect, uint32_t NbrSect, FM_CallbackNode_t *CallbackNode);
void FM_BackgroundProcess (void);
void FM_ProcessRequest(uint8_t immediate);

#ifdef __cplusplus
}
#endif

#endif /*FLASH_MANAGER_H */
