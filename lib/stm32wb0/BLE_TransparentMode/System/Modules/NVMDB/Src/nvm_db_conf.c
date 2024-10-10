/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    nvm_db_conf.c
  * @author  GPM WBL Application Team
  * @brief   This file provides the structure of the database.
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
#include "nvm_db_conf.h"
#include <stdlib.h>

/** @defgroup NVM_Manager  NVM Manager
 * @{
 */

/** @defgroup NVM_Manager_TypesDefinitions Private Type Definitions
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_Manager_Private_Defines Private Defines
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_Manager_Conf_Private_Macros NVM Manager Configuration Private Macros
 * @{
 */

#if PRESET1

#define FLASH_NVM_DATASIZE  (2 * PAGE_SIZE)  // Make sure this space is reserved in the linker script.
#define NVM_START_ADDRESS   (_MEMORY_FLASH_END_ - FLASH_NVM_DATASIZE + 1)

#define DB0_SIZE  (PAGE_SIZE)
#define DB1_SIZE  (PAGE_SIZE - 8) // Last 8 bytes in Flash are reserved for the lock/unlock word.

#elif PRESET2

#define FLASH_NVM_DATASIZE  (1 * PAGE_SIZE)  // Make sure this space is reserved in the linker script.
#define NVM_START_ADDRESS   (_MEMORY_FLASH_END_ - FLASH_NVM_DATASIZE + 1)

#define DB0_SIZE  (PAGE_SIZE - 8 - 64) // Last 8 bytes in Flash are reserved for the lock/unlock word.
#define DB1_SIZE  (64)

#endif

/**
 * @}
 */

/** @defgroup NVM_Manager_Conf_Constants NVM Manager Configuration Constants
 * @{
 */

#if PRESET1

const NVMDB_SmallDBContainerType *NVM_SMALL_DB_STATIC_INFO = NULL;
const NVMDB_StaticInfoType NVM_LARGE_DB_STATIC_INFO[NUM_LARGE_DBS] =
{
  {
    .address = NVM_START_ADDRESS,
    .size = DB0_SIZE,
    .id = 0,
#if AUTO_CLEAN
    .clean_threshold = DB0_SIZE / 3
#endif
  },
  {
    .address = NVM_START_ADDRESS + DB0_SIZE,
    .size = DB1_SIZE,
    .id = 1,
#if AUTO_CLEAN
    .clean_threshold = 0
#endif
  },
};

#elif PRESET2

const NVMDB_SmallDBType dbs[NUM_SMALL_DBS] =
{
  {
    .id = 0,
    .offset = 0,
#if AUTO_CLEAN
    .clean_threshold = DB0_SIZE / 3
#endif
  },
  {
    .id = 1,
    .offset = DB0_SIZE,
#if AUTO_CLEAN
    .clean_threshold = 0
#endif
  }
};

const NVMDB_SmallDBContainerType NVM_SMALL_DB_STATIC_INFO[NUM_SMALL_DB_PAGES] = { { .page_address = NVM_START_ADDRESS, .num_db = NUM_SMALL_DBS, .dbs = dbs } };
const NVMDB_StaticInfoType *NVM_LARGE_DB_STATIC_INFO = NULL;

#endif /* PRESET2 */

/**
 * @}
 */

/**
 * @}
 */
