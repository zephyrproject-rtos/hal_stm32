/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    nvm_db.h
  * @author  GPM WBL Application Team
  * @brief   This file contains all the functions prototypes for the NVM Manager.
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
#ifndef NVM_DB_H
#define NVM_DB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup NVM_Manager_Peripheral  NVM Manager
 * @{
 */

/** @defgroup NVM_Manager_Exported_Types Exported Types
 * @{
 */

typedef uint8_t NVMDB_status_t;

typedef uint8_t NVMDB_IdType;

typedef struct _NVMDB_HandleType
{
  NVMDB_IdType id;
  uint32_t address;
  uint32_t end_address;      // This info may also be retrieved from id.
  uint8_t first_read;
  uint8_t cache;             // If TRUE, the handle points in cache
  uint16_t cache_index;      // If cache is TRUE, cache_index is the index of the current write operation.
}NVMDB_HandleType;

typedef uint16_t NVMDB_RecordSizeType;

/**
 * @}
 */

/** @defgroup NVM_Manager_Exported_Constants  Exported Constants
 * @{
 */

/**
 * @name Return codes
 * @{
 */
#define NVMDB_STATUS_OK                 0
#define NVMDB_STATUS_INVALID_ID         1
#define NVMDB_STATUS_FULL_DB            2
#define NVMDB_STATUS_CORRUPTED_DB       3
#define NVMDB_STATUS_END_OF_DB          4
#define NVMDB_STATUS_INVALID_RECORD     5
#define NVMDB_STATUS_INVALID_OFFSET     6
#define NVMDB_STATUS_NOT_ENOUGH_TIME    7
#define NVMDB_STATUS_CACHE_FULL         8
#define NVMDB_STATUS_CACHE_OP_PENDING   9
#define NVMDB_STATUS_LOCKED             10
#define NVMDB_STATUS_CLEAN_NEEDED       11
#define NVMDB_STATUS_CACHE_ERROR        12
/**
 * @}
 */

/**
 * Record type. If set to ALL_TYPES, all record types are returned. Values are
 * defined by application.
 */
#define ALL_TYPES                       0xFF

/**
 * @}
 */

/** @defgroup NVM_Manager_Exported_Macros           Exported Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup NVM_Manager_Exported_Functions        Exported Functions
 * @{
 */

NVMDB_status_t NVMDB_Init(void);

NVMDB_status_t NVMDB_HandleInit(NVMDB_IdType NVMDB_id, NVMDB_HandleType *handle_p);

NVMDB_status_t NVMDB_ReadNextRecord(NVMDB_HandleType *handle_p, uint8_t record_type, NVMDB_RecordSizeType data_offset, uint8_t *data_p, NVMDB_RecordSizeType max_size, NVMDB_RecordSizeType *size_p);

NVMDB_status_t NVMDB_ReadCurrentRecord(NVMDB_HandleType *handle_p, NVMDB_RecordSizeType offset, uint8_t *data_p, NVMDB_RecordSizeType max_size, NVMDB_RecordSizeType *size_p);

NVMDB_status_t NVMDB_FindNextRecord(NVMDB_HandleType *handle_p, uint8_t type, NVMDB_RecordSizeType pattern_offset, const uint8_t *pattern_p, NVMDB_RecordSizeType pattern_length, NVMDB_RecordSizeType data_offset, uint8_t *data_p, NVMDB_RecordSizeType max_size, NVMDB_RecordSizeType *size_p);

NVMDB_status_t NVMDB_AppendRecord(NVMDB_HandleType *handle_p, uint8_t record_type, uint16_t header_length, const void *header, uint16_t data_length, const void *data);

NVMDB_status_t NVMDB_DeleteRecord(const NVMDB_HandleType *handle_p);

NVMDB_status_t NVMDB_CleanDB(NVMDB_IdType NVMDB_id);

NVMDB_status_t NVMDB_Erase(NVMDB_IdType NVMDB_id);

NVMDB_status_t NVMDB_Tick(void);

uint8_t NVMDB_TimeCheck(int32_t time);

int NVMDB_CompareCurrentRecord(NVMDB_HandleType *handle_p, NVMDB_RecordSizeType offset, const uint8_t *data_p, NVMDB_RecordSizeType size);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* NVM_DB_H */
