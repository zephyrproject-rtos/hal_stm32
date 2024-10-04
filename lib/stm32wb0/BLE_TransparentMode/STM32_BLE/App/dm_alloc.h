/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dm_alloc.h
  * @author  GPM WBL Application Team
  * @brief   Dynamic Memory Allocator
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

#ifndef __DM_ALLOC_H__
#define __DM_ALLOC_H__
/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
/******************************************************************************
 * CONSTANT SYMBOLS
 *****************************************************************************/
/******************************************************************************
 * LOCAL MACROS
 *****************************************************************************/
/******************************************************************************
 * TYPES
 *****************************************************************************/
/******************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************/
void dm_init(uint16_t buffer_size, uint32_t *buffer_p);
void *dm_alloc(uint16_t size);
void *dm_realloc(void *buffer_p, uint16_t size);
void dm_free(void *buffer_p);

#endif
