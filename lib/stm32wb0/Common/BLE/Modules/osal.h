/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    osal.h
  * @author  GPM WBL Application Team
  * @brief   This header file defines the OS abstraction layer. OSAL defines the
  *          set of functions which needs to be ported to target operating
  *          system and target platform.
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
#ifndef __OSAL_H__
#define __OSAL_H__

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief This function copies size number of bytes from a
 * memory location pointed by src to a destination
 * memory location pointed by dest. The locations must not overlap.
 *
 * @param[out] dest Destination address
 * @param[in] src  Source address
 * @param[in] size Number of bytes to copy
 */

extern void Osal_MemCpy(void *dest, const void *src, unsigned int size);

/**
 * @brief This function copies a given number of bytes, multiple of 4, from a
 * memory location pointed by src to a destination memory location pointed by
 * dest, by using only 32-bit accesses. The locations must not overlap.
 *
 * @param[out] dest Destination address. It must be 32-bit aligned.
 * @param[in]  src  Source address. It must be 32-bit aligned.
 * @param[in]  size Number of bytes to copy. It must be a multiple of 4.
 */
extern void Osal_MemCpy4(uint32_t *dest, const uint32_t *src, unsigned int size);

#endif /* __OSAL_H__ */
