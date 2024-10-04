/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    miscutil.h
  * @author  GPM WBL Application Team
  * @brief   Header file for HW miscellaneous utilities.
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

#ifndef __MISCUTIL_H__
#define __MISCUTIL_H__

#include <stdint.h>
#include "crash_handler.h"
#include "stm32wb0x.h"

#if defined(STM32WB09)
#define DIE_SW_ID_STM32WB09XX     ((uint8_t)6)
#define JTAG_ID_CODE_STM32WB09XX  ((uint32_t)0x02032041)
#elif defined(STM32WB07) || defined(STM32WB06)
#define DIE_SW_ID_STM32WB07XX     ((uint8_t)3)
#define JTAG_ID_CODE_STM32WB07XX  ((uint32_t)0x0201E041)
#elif defined(STM32WB05)
#define DIE_SW_ID_STM32WB05XX     ((uint8_t)5)
#define JTAG_ID_CODE_STM32WB05XX  ((uint32_t)0x02028041)
#endif

#define DIE_SW_ID_UNKOWN          ((uint8_t)0xFF)

/**
 * @brief A structure that represents part information details
 *
 */
typedef struct PartInfoS {
  /** DIE ID number */
  uint8_t  die_id;
  /** Die major number */
  uint8_t  die_major;
  /** Die cut number */
  uint8_t  die_cut;
  /** JTAG ID */
  uint32_t jtag_id_code;
  /** Flash size in bytes */
  uint32_t flash_size;
  /** Flash size in bytes */
  uint32_t ram_size;
} PartInfoType;

/**
 * @brief This function return a structure with information about the device
 *
 * @param[out] partInfo Pointer to a PartInfoType structure
 *
 * @retval None
 */
void GetPartInfo(PartInfoType *partInfo);
/**
 * @brief Get Crash Information utility
 *
 * This function return the crash information that are stored in RAM, by hard
 * handler, nmi handler and assert handler.
 * This function reset the crash information stored in RAM before it returns.
 * So it avoid to report the same crash information after a normal reboot.
 *
 * @param[out] crashInfo Pointer to a crash_info_t structure
 *
 * @retval None
 */
void GetCrashInfo(crash_info_t *crashInfo);
/**
 * @brief Set Crash Information utility
 *
 * This function stores crash information in RAM and reset the device
 * Crash information can be retrieved by using API HAL_GetCrashInfo
 *
 * @param[in] msp Stack pointer containing crash info
 * @param[out] signature CRash reason signature
 *
 * @retval None
 */
void CrashHandler(uint32_t msp, uint32_t signature);

/**
 * @brief Read CI field from demodulation register
 *
 * @param[in] None
 *
 * @retval CI value
 */
uint8_t GetDemodCI(void);

#endif /* __MISCUTIL_H__ */
