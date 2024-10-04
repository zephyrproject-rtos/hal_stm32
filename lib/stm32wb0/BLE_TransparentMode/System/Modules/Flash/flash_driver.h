/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    flash_driver.h
  * @author  MCD Application Team
  * @brief   Header for flash_driver.c module
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
#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "utilities_common.h"

/* Exported types ------------------------------------------------------------*/

/* Bit mask to modify Flash Control status */
typedef uint32_t  FD_Flash_ctrl_bm_t;

/* Flash operation status */
typedef enum
{
  FD_FLASHOP_SUCCESS,
  FD_FLASHOP_FAILURE
} FD_FlashOp_Status_t;

/* Flash Driver commands to enable or disable flash access */
typedef enum
{
  FD_FLASH_ENABLE,
  FD_FLASH_DISABLE,
} FD_FLASH_Status_t;

/**
 * @brief Bit mask to modify Flash Control status
 *
 * @details Those bitmasks are used to enable/disable access to the flash:
 *   - RFTS:
 *     -# FD_FLASHACCESS_RFTS_BYPASS: Bypass check of radio activity before Flash operation.
 *                                    This means that every Flash operation will start even if
 *                                    a system is close to a radio activity.
 *
 */
typedef enum FD_FlashAccess_bm
{
  /* Bypass of RF Timing Synchro flash access bitfield */
  FD_FLASHACCESS_RFTS_BYPASS,
}FD_FlashAccess_bm_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FD_SetStatus(FD_FlashAccess_bm_t Flags_bm, FD_FLASH_Status_t Status);
FD_FlashOp_Status_t FD_WriteData32(uint32_t Dest, uint32_t *Payload);
FD_FlashOp_Status_t FD_WriteData128(uint32_t Dest, uint32_t *Payload);
FD_FlashOp_Status_t FD_EraseSectors(uint32_t Sect);

#ifdef __cplusplus
}
#endif

#endif /*FLASH_DRIVER_H */
