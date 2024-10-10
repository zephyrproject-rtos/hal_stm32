/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    flash_manager.c
  * @author  MCD Application Team
  * @brief   The Flash Manager module provides an interface to write raw data
  *          from SRAM to FLASH
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
#include <stdbool.h>
#include "utilities_conf.h"
#include "flash_manager.h"
#include "flash_driver.h"
#include "stm32wb0x_hal.h"

/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

/* Flash operation type */
typedef enum
{
  FM_NO_OP,
  FM_WRITE_OP,
  FM_ERASE_OP
} FM_FlashOp_t;

/**
 * @brief Flash operation configuration struct
 */
typedef struct FM_FlashOpConfig
{
  uint32_t *writeSrc;
  uint32_t *writeDest;
  int32_t  writeSize;
  uint32_t eraseFirstSect;
  uint32_t eraseNbrSect;
}FM_FlashOpConfig_t;

/* Private defines -----------------------------------------------------------*/

#define FLASH_WRITE_BLOCK_SIZE  4U
#define ALIGNMENT_32   0x00000003
#define ALIGNMENT_128  0x0000000F

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
  * @brief Semaphore on Flash
  */
static bool busy_flash_sem = FALSE;

/**
  * @brief Indicates if the flash manager module is available or not
  */
static bool flash_manager_busy = FALSE;

/**
  * @brief Callback node list for pending flash operation request
  */
static tListNode fm_cb_pending_list;

/**
  * @brief Flag indicating if pending node list has been initialized
  */
static bool fm_cb_pending_list_init = FALSE;

/**
  * @brief Pointer to current flash operation requester's callback
  */
static void (*fm_running_cb)(FM_FlashOp_Status_t);

/**
  * @brief Type of current flash operation (Write/Erase)
  */
static FM_FlashOp_t fm_flashop = FM_NO_OP;

/**
  * @brief Parameters for Flash operation
  */
static FM_FlashOpConfig_t fm_flashop_parameters;

/* Private function prototypes -----------------------------------------------*/

static FM_Cmd_Status_t FM_CheckFlashManagerState(FM_CallbackNode_t *CallbackNode);

/* Functions Definition ------------------------------------------------------*/

/**
  * @brief  Request the Flash Manager module to initiate a Flash Write operation
  * @param  Src: Address of the data to be stored in FLASH. It shall be 32bits aligned
  * @param  Dest: Address where the data shall be written. It shall be 128bits aligned
  * @param  Size: This is the number of words to be written in Flash.
  * @param  CallbackNode: Pointer to the callback node for storage in list
  * @retval FM_Cmd_Status_t: Status of the Flash Manager module
  */
FM_Cmd_Status_t FM_Write(uint32_t *Src, uint32_t *Dest, int32_t Size, FM_CallbackNode_t *CallbackNode)
{
  FM_Cmd_Status_t status;

  if (((uint32_t)Dest < FLASH_START_ADDR) || ((uint32_t)Dest > (FLASH_START_ADDR + FLASH_SIZE))
                                    || (((uint32_t)Dest + Size) > (FLASH_START_ADDR + FLASH_SIZE)))
  {/* Destination address not part of the flash */
    return FM_ERROR;
  }

  if (((uint32_t) Src & ALIGNMENT_32) || ((uint32_t) Dest & ALIGNMENT_32))
  { /* Source or destination address not properly aligned */
    return FM_ERROR;
  }

  status = FM_CheckFlashManagerState(CallbackNode);

  if (status == FM_OK)
  { /* Flash manager is available */

    /* Save Write parameters */
    fm_flashop_parameters.writeSrc = Src;
    fm_flashop_parameters.writeDest = Dest;
    fm_flashop_parameters.writeSize = Size;

    fm_flashop = FM_WRITE_OP;

    /* Window request to be executed in background */
    FM_ProcessRequest(TRUE);
  }
  return status;
}

/**
  * @brief  Request the Flash Manager module to initiate a Flash Erase operation
  * @param  FirstSect: Index of the first sector to erase
  * @param  NbrSect: Number of sector to erase
  * @param  CallbackNode: Pointer to the callback node for storage in list
  * @retval FM_Cmd_Status_t: Status of the Flash Manager module
  */
FM_Cmd_Status_t FM_Erase(uint32_t FirstSect, uint32_t NbrSect, FM_CallbackNode_t *CallbackNode)
{
  FM_Cmd_Status_t status;

  if ((FirstSect > FLASH_PAGE_NUMBER) || ((FirstSect + NbrSect) > FLASH_PAGE_NUMBER))
  { /* Inconsistent request */
    return FM_ERROR;
  }

  if (NbrSect == 0)
  { /* Inconsistent request */
    return FM_ERROR;
  }

  status = FM_CheckFlashManagerState(CallbackNode);

  if (status == FM_OK)
  { /* Flash manager is available */

    /* Save Erase parameters */
    fm_flashop_parameters.eraseFirstSect = FirstSect;
    fm_flashop_parameters.eraseNbrSect = NbrSect;

    fm_flashop = FM_ERASE_OP;

    /* Window request to be executed in background */
    FM_ProcessRequest(TRUE);
  }
  return status;
}

/**
  * @brief  Execute Flash Manager background tasks
  * @param  None
  * @retval None
  */
void FM_BackgroundProcess (void)
{
  bool flashop_complete = false;
  FD_FlashOp_Status_t fdReturnValue = FD_FLASHOP_SUCCESS;
  FM_CallbackNode_t *pCbNode = NULL;

  if (fm_flashop == FM_WRITE_OP)
  {

    /* Write first non-aligned bytes */
    while(fm_flashop_parameters.writeSize > 0 && ((uint32_t)fm_flashop_parameters.writeDest & ALIGNMENT_128) &&
          fdReturnValue == FD_FLASHOP_SUCCESS)
    {
      /* Write single words */
      fdReturnValue = FD_WriteData32((uint32_t) fm_flashop_parameters.writeDest,
                                      fm_flashop_parameters.writeSrc);
      if (fdReturnValue == FD_FLASHOP_SUCCESS)
      {
        fm_flashop_parameters.writeDest += 1;
        fm_flashop_parameters.writeSrc += 1;
        fm_flashop_parameters.writeSize -= 1;
      }
    }

    /* Write aligned block */
    while((fm_flashop_parameters.writeSize >= 4) &&
          (fdReturnValue == FD_FLASHOP_SUCCESS))
    {
      fdReturnValue = FD_WriteData128((uint32_t) fm_flashop_parameters.writeDest,
                                      fm_flashop_parameters.writeSrc);

      if (fdReturnValue == FD_FLASHOP_SUCCESS)
      {
        fm_flashop_parameters.writeDest += FLASH_WRITE_BLOCK_SIZE;
        fm_flashop_parameters.writeSrc += FLASH_WRITE_BLOCK_SIZE;
        fm_flashop_parameters.writeSize -= FLASH_WRITE_BLOCK_SIZE;
      }
    }

    /* Write remaining words, if any */
    while(fm_flashop_parameters.writeSize > 0 &&
          fdReturnValue == FD_FLASHOP_SUCCESS)
    {
      /* Write single words */
      fdReturnValue = FD_WriteData32((uint32_t) fm_flashop_parameters.writeDest,
                                      fm_flashop_parameters.writeSrc);
      if (fdReturnValue == FD_FLASHOP_SUCCESS)
      {
        fm_flashop_parameters.writeDest += 1;
        fm_flashop_parameters.writeSrc += 1;
        fm_flashop_parameters.writeSize -= 1;
      }
    }

    /* Is write over ? */
    if (fm_flashop_parameters.writeSize <= 0)
    {
      flashop_complete = true;
    }
  }
  else if (fm_flashop == FM_ERASE_OP)
  {

    while((fm_flashop_parameters.eraseNbrSect > 0) &&
          (fdReturnValue == FD_FLASHOP_SUCCESS))
    {
      fdReturnValue = FD_EraseSectors(fm_flashop_parameters.eraseFirstSect);

      if (fdReturnValue == FD_FLASHOP_SUCCESS)
      {
        fm_flashop_parameters.eraseNbrSect--;
        fm_flashop_parameters.eraseFirstSect++;
      }
    }

    if (fm_flashop_parameters.eraseNbrSect == 0)
    {
      flashop_complete = true;
    }
  }

  if (flashop_complete == true)
  {
    fm_flashop = FM_NO_OP;

    UTILS_ENTER_CRITICAL_SECTION();

    /* Release semaphore on flash */
    busy_flash_sem = false;

    /* Set Flash Manager busy */
    flash_manager_busy = false;

    UTILS_EXIT_CRITICAL_SECTION();

    /* Invoke the running callback if present */
    if (fm_running_cb != NULL)
    {
      fm_running_cb(FM_OPERATION_COMPLETE);
    }

    /* notify pending requesters */
    while((LST_is_empty (&fm_cb_pending_list) == false) &&
          (busy_flash_sem == false) && (flash_manager_busy == false))
    {
      LST_remove_head (&fm_cb_pending_list, (tListNode**)&pCbNode);
      pCbNode->Callback(FM_OPERATION_AVAILABLE);
    }
  }
  else
  {
    FM_ProcessRequest(FALSE);
  }

}

/**
  * @brief  Check if the Flash Manager is busy or available
  * @param  CallbackNode: Pointer to the callback node for storage in list
  * @retval FM_Cmd_Status_t: Status of the Flash Manager module
  */
static FM_Cmd_Status_t FM_CheckFlashManagerState(FM_CallbackNode_t *CallbackNode)
{
  bool fm_process_cmd = false;
  FM_Cmd_Status_t status = FM_ERROR;

  /* Check if semaphore on flash is available */
  UTILS_ENTER_CRITICAL_SECTION();

  /* Initialize pending list if not done */
  if (fm_cb_pending_list_init == false)
  {
    LST_init_head(&fm_cb_pending_list);
    fm_cb_pending_list_init = true;
  }
  /* Check if semaphore on flash is available */
  if (busy_flash_sem == false)
  { /* Check if Flash Manager is already busy */
    if (flash_manager_busy == false)
    {
      busy_flash_sem = true; /* Get semaphore on flash */
      flash_manager_busy = true; /* Set Flash Manager busy */
      fm_process_cmd = true;
    }
    else
    {
      fm_process_cmd = false;
    }
  }
  else
  {
    fm_process_cmd = false;
  }
  UTILS_EXIT_CRITICAL_SECTION();

  if (fm_process_cmd == false)
  { /* Flash manager busy */

    /* Append callback to the pending list */
    if ((CallbackNode != NULL) && (CallbackNode->Callback != NULL))
    {
      LST_insert_tail(&fm_cb_pending_list, &(CallbackNode->NodeList));
    }

    status = FM_BUSY;
  }
  else
  { /* Flash manager is available */

    if ((CallbackNode != NULL) && (CallbackNode->Callback != NULL))
    {
      UTILS_ENTER_CRITICAL_SECTION();

      fm_running_cb = CallbackNode->Callback;

      UTILS_EXIT_CRITICAL_SECTION();
    }
    else
    {
      UTILS_ENTER_CRITICAL_SECTION();

      fm_running_cb = NULL;

      UTILS_EXIT_CRITICAL_SECTION();
    }

    status = FM_OK;
  }
  return status;
}

/**
  * @brief  This is the function called by the module when it is requested to call
  *         FM_BackgroundProcess().
  * @param  immediate: if 1, FM_BackgroundProcess() should be called as soon as possible,
  *                    otherwise it may be called after a while.
  * @retval None
  */
__weak void FM_ProcessRequest(uint8_t immediate)
{
    UNUSED(immediate);
}
