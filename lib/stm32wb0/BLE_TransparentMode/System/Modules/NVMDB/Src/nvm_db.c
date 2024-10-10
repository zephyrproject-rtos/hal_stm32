/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    nvm_db.c
  * @author  GPM WBL Application Team
  * @brief   This file provides functions to implement sequential databases.
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

#include <string.h>
#include <stdint.h>
#include "stm32wb0x.h"
#include "nvm_db.h"
#include "nvm_db_conf.h"

/* Process all commands in cache till there is time to do it. */
#define PROCESS_CACHE_AT_ONCE   1
#define NVM_CACHE               0

/** @defgroup NVM_Manager  NVM Manager
 * @{
 */

/** @defgroup NVM_Manager_TypesDefinitions Private Type Definitions
 * @{
 */

typedef struct
{
  uint8_t valid_flag;
  uint8_t record_id;
  NVMDB_RecordSizeType length;
} NVMDB_RecordHeaderType;

#define RECORD_HEADER_SIZE  4

typedef struct
{
  NVMDB_RecordHeaderType header;
  uint8_t data[];
} NVMDB_RecordType, *NVMDB_RecordType_ptr;

typedef struct
{
  uint32_t start_address;
  uint32_t end_address;
  uint16_t valid_records;
  uint16_t invalid_records;
  uint16_t free_space;  // Free space at the end of last record. It is a real free space, not virtual. After a clean, the free space may increase. It takes also into account all the records in cache.
  uint8_t locked;
  uint16_t clean_threshold;
} NVMDB_info;

typedef struct
{
  uint8_t move_to_next_record;
  NVMDB_RecordSizeType record_offset;
  NVMDB_RecordSizeType record_length;
}ReadStateType;

// Generic structure
typedef struct
{
  uint16_t length;
  uint8_t op;
  NVMDB_IdType id;
}CacheOperationType;

typedef struct
{
  uint16_t length;
  uint8_t op;
  NVMDB_IdType id;
}CacheNoOperationType;

typedef struct
{
  uint16_t length;
  uint8_t op;
  NVMDB_IdType id;
  uint8_t record_type;
}CacheWriteOperationType;

typedef struct
{
  uint16_t length;
  uint8_t op;
  NVMDB_IdType id;
  uint32_t address;
}CacheDeleteOperationType;

typedef struct
{
  uint16_t length;
  uint8_t op;
  NVMDB_HandleType handle;  // NVMDB_IdType id is first field of NVMDB_HandleType structure
  uint32_t flash_address;
  ReadStateType read_state;
}CacheCleanLargeOperationType;

typedef struct
{
  uint16_t length;
  uint8_t op;
  NVMDB_IdType id;
  uint8_t page_num_start;
  uint8_t num_pages;
}CachePageEraseOperationType;

typedef struct
{
  uint16_t length;
  uint8_t op;
  NVMDB_IdType id;
  const NVMDB_SmallDBContainerType *smallDBContainer_p;
}CacheSmallDBEraseOperationType;

/**
 * @}
 */

/** @defgroup NVM_Manager_Private_Defines Private Defines
 * @{
 */
#define DEBUG_GPIO_HIGH()
#define DEBUG_GPIO_LOW()

#define NO_RECORD           0xFF
#define VALID_RECORD        0xFE
#define INVALID_RECORD      0x00

#define NVM_CACHE_SIZE  256

/* If 1 the buffer used to temporarily store data is static, otherwise it is allocated in CSTACK. */
#define NVMDB_STATIC_BUFF       0

#define CACHE_NOP               0
#define CACHE_WRITE_OP          1
#define CACHE_DELETE_OP         2
#define CACHE_CLEAN_LARGE_DB_OP 3
#define CACHE_PAGE_ERASE_OP     4
#define CACHE_SMALL_DB_ERASE_OP 5
#define CACHE_ALL               6

#define SMALL_DB 1
#define LARGE_DB 2

#ifdef DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
                                __disable_irq(); \
/* Must be called in the same or in a lower scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)

/**
 * @}
 */

/** @defgroup NVM_Manager_Private_Macros Private Macros
 * @{
 */

#define PAGE_OFFSET_MASK    (PAGE_SIZE - 1)

#define MIN_RECORD_SIZE     (RECORD_HEADER_SIZE + 1)
#define MAX_RECORD_SIZE     ((NVMDB_RecordSizeType)(-1))

#ifndef MIN
#define MIN(a, b)            (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)            (((a) > (b)) ? (a) : (b))
#endif

#define ROUND4_L(a)         (((a) >> 2) << 2)  // Round to previous multiple of 4.
#define ROUND_R(a, b)       ((((a) - 1) | (b - 1)) + 1)  // Round 'a' to next multiple of 'b', being 'b' a power of 2.
#define ROUND4_R(a)         ROUND_R(a, 4)// Round to next multiple of 4
#define ROUNDPAGE_R(a)      ROUND_R(a, PAGE_SIZE)// Round to next right multiple of page size
#define BEGIN_OF_PAGE(a)     ((a) & (~PAGE_OFFSET_MASK))

#define CACHE_EMPTY()   (cache_head == cache_tail)

/**
 * @}
 */

/** @defgroup NVM_Manager_Private_Variables Private Variables
 * @{
 */
#if NVMDB_STATIC_BUFF
static uint8_t NVM_buffer[PAGE_SIZE];
#endif
static NVMDB_info DBInfo[NUM_DB];
#if NVM_CACHE
static uint8_t NVM_cache[NVM_CACHE_SIZE];
static uint16_t cache_head = 0, cache_tail = 0;
#endif

/**
 * @}
 */

/** @defgroup NVM_Manager_External_Variables External Variables
 * @{
 */

extern const NVMDB_SmallDBContainerType NVM_SMALL_DB_STATIC_INFO[];
extern const NVMDB_StaticInfoType NVM_LARGE_DB_STATIC_INFO[];

/**
 * @}
 */

/** @defgroup NVM_Manager_Private_FunctionPrototypes Private Function Prototypes
 * @{
 */
#if NVM_CACHE
static NVMDB_status_t ScheduleCleanLargeDBOperation(NVMDB_HandleType handle, uint32_t flash_address, ReadStateType state);
static NVMDB_status_t SchedulePageEraseOperation(NVMDB_IdType NVMDB_id, uint8_t page_num_start, uint8_t num_pages);
static uint8_t CacheRequestBuffer(uint16_t length);
static uint8_t CacheInsertData(const void *data, uint16_t length);
static uint16_t CacheGetDataSize(void);
#endif

#if AUTO_CLEAN
static int8_t NVMDB_CleanCheck(void);
#endif

/**
 * @}
 */

/** @defgroup NVM_Manager_Private_Functions Private Functions
 * @{
 */

#if NVM_CACHE

static void CacheAdvanceHead(uint16_t length)
{
  cache_head += length;
  if(cache_head == cache_tail)
  {
    cache_head = cache_tail = 0;
  }
}

// If advance_to_next is true, it advances to next record before searching for the given operation.
static uint8_t CacheFindOperation(NVMDB_IdType NVMDB_id, uint8_t op, uint16_t index_in, uint16_t *index_out_p, uint8_t advance_to_next)
{
  uint16_t i = index_in;
  uint8_t skip_record = advance_to_next;

  while(1)
  {

    if(i == cache_tail)
    {
      return FALSE;
    }

    CacheOperationType cache_op;
    memcpy(&cache_op, &NVM_cache[i], sizeof(cache_op));

    if(!skip_record && cache_op.id == NVMDB_id && (op == CACHE_ALL || op == cache_op.op))
    {
      break;
    }
    i += cache_op.length;

    skip_record = FALSE;
  }

  if(index_out_p != NULL)
  {
    *index_out_p = i;
  }

  return TRUE;
}

// If advance_to_next is true, read next record. If false, read current record. If handle does not point in cache, always read first record in cache.
static NVMDB_status_t ReadRecordInCache(NVMDB_HandleType *handle_p, uint8_t **data_p, NVMDB_RecordSizeType *data_len, uint8_t advance_to_next, uint8_t *type)
{
  uint16_t index_in, index_out;
  //uint8_t advance_to_next;

  if(!handle_p->cache)
  {
    index_in = cache_head;
    advance_to_next = FALSE;
  }
  else
  {
    index_in = handle_p->cache_index;
    //advance_to_next = TRUE;
  }

  if(!CacheFindOperation(handle_p->id, CACHE_WRITE_OP, index_in, &index_out, advance_to_next))
  {
    return NVMDB_STATUS_END_OF_DB;
  }

  handle_p->cache = TRUE;
  handle_p->cache_index = index_out;

  CacheWriteOperationType write_op;
  memcpy(&write_op, &NVM_cache[index_out], sizeof(write_op));
  *data_p = &NVM_cache[index_out] + sizeof(write_op);
  *data_len = write_op.length - sizeof(write_op);
  *type = write_op.record_type;

  return NVMDB_STATUS_OK;
}

static void RemoveCacheOp(NVMDB_IdType NVMDB_id)
{
  uint16_t index = cache_head;
  uint8_t advance_to_next = FALSE;

  while(CacheFindOperation(NVMDB_id, CACHE_ALL, index, &index, advance_to_next))
  {

    CacheOperationType cache_op;
    memcpy(&cache_op, &NVM_cache[index], sizeof(cache_op));
    // Shift cache content. Another solution that avoids this memory operation is to write CACHE_NOP inside op field.
    memmove(NVM_cache + index, NVM_cache + index + cache_op.length, CacheGetDataSize() - cache_op.length);
    cache_tail -= cache_op.length;

    advance_to_next = TRUE;
  }
}

static int32_t CalculateFlashTimeOperation(uint16_t write_length, uint8_t num_pages_to_be_erased)
{
  return PAGE_ERASE_TIME_SYS * num_pages_to_be_erased + (write_length / 4 + 1) * WORD_WRITE_TIME_SYS + MARGIN_TIME_SYS;
}

static NVMDB_status_t EraseWithTimeCheck(uint8_t *page_num_start, uint8_t *num_pages_p)
{
  int32_t needed_time;

  while(*num_pages_p > 0)
  {

    needed_time = CalculateFlashTimeOperation(0, 1);

    ATOMIC_SECTION_BEGIN();
    if(NVMDB_TimeCheck(needed_time))
    {
      DEBUG_GPIO_HIGH();
      NVMDB_FLASH_ERASE_PAGE(*page_num_start, 1);  // Erase one page at a time. Check if there is time before each erase.
      DEBUG_GPIO_LOW();
      ATOMIC_SECTION_END();
      (*page_num_start)++;
      (*num_pages_p)--;
    }
    else
    {
      ATOMIC_SECTION_END();
      return NVMDB_STATUS_NOT_ENOUGH_TIME;
    }
  }

  return NVMDB_STATUS_OK;
}

#endif

static NVMDB_status_t NVMDB_get_info(NVMDB_info *info)
{
  uint32_t address = info->start_address;
  NVMDB_RecordType_ptr record_p;

  info->valid_records = 0;
  info->invalid_records = 0;
  info->free_space = 0;
  info->locked = FALSE;

  while(1)
  {

    record_p = (NVMDB_RecordType_ptr)address;

    if(record_p->header.valid_flag == NO_RECORD)
    {
      info->free_space = info->end_address - address - RECORD_HEADER_SIZE;
      return NVMDB_STATUS_OK;
    }
    else if(record_p->header.valid_flag == VALID_RECORD)
    {
      info->valid_records++;
    }
    else if(record_p->header.valid_flag == INVALID_RECORD)
    {
      info->invalid_records++;
    }
    else
    {
      // Wrong flag
      return NVMDB_STATUS_CORRUPTED_DB;
    }

    address += ROUND4_R(record_p->header.length + RECORD_HEADER_SIZE);

    if(address + MIN_RECORD_SIZE >= info->end_address)  // End of DB reached
    {
      return NVMDB_STATUS_OK;
    }
  }
}

/* Current_record_length is used to read the next record when the current record
   is no more present (because, for example, a clean operation has canceled it). */
static NVMDB_status_t NextRecordNoLock(NVMDB_HandleType *handle_p, uint8_t type, uint8_t **data_p, NVMDB_RecordSizeType *data_len, NVMDB_RecordSizeType current_record_length, uint8_t *record_type)
{
  NVMDB_RecordHeaderType header;
  NVMDB_RecordType_ptr record_p;

#if NVM_CACHE

  if(handle_p->cache)  // Handle points to records in cache
  {
    if(ReadRecordInCache(handle_p, data_p, data_len, TRUE, record_type) == NVMDB_STATUS_OK)
    {
      // A record to be written has been found in cache
      return NVMDB_STATUS_OK;
    }
    else
    {
      return NVMDB_STATUS_END_OF_DB;
    }
  }
#endif

  if(current_record_length)
  {
    header.length = current_record_length;
    header.valid_flag = VALID_RECORD;
    record_p = (NVMDB_RecordType_ptr) & header;
  }
  else
  {
    record_p = (NVMDB_RecordType_ptr)handle_p->address;
  }

  if(handle_p->address >= handle_p->end_address || record_p->header.valid_flag == NO_RECORD)
  {
    return NVMDB_STATUS_END_OF_DB;
  }

  // If we are not at the end we can move to next record.

  while(1)
  {

    // If it is the first read, the pointer already points to first record.
    // If it is not the first read, advance the pointer to the next record (word aligned).
    if(handle_p->first_read)
    {
      handle_p->first_read = FALSE;
    }
    else
    {
      handle_p->address += ROUND4_R(record_p->header.length + RECORD_HEADER_SIZE);
      record_p = (NVMDB_RecordType_ptr)handle_p->address;

      if(handle_p->address >= handle_p->end_address || record_p->header.valid_flag == NO_RECORD)
      {
#if NVM_CACHE
        // Check records in cache.
        if(ReadRecordInCache(handle_p, data_p, data_len, TRUE, record_type) == NVMDB_STATUS_OK)
        {
          // A record to be written has been found in cache
          return NVMDB_STATUS_OK;
        }
#endif
        return NVMDB_STATUS_END_OF_DB;
      }
    }

    if(record_p->header.valid_flag == INVALID_RECORD)
    {
      // If record is invalidated, address is updated in next cycle.
      continue;
    }

    if(record_p->header.valid_flag != VALID_RECORD)
    {
      return NVMDB_STATUS_CORRUPTED_DB;
    }

    if(type == ALL_TYPES || record_p->header.record_id == type)
    {

#if NVM_CACHE
      uint16_t index = cache_head;
      uint8_t record_is_deleted_in_cache = FALSE;
      uint8_t advance_to_next_record = FALSE;

      // Check if there is a delete operation in cache on this record.
      while(CacheFindOperation(handle_p->id, CACHE_DELETE_OP, index, &index, advance_to_next_record))
      {
        CacheDeleteOperationType del_op;
        memcpy(&del_op, &NVM_cache[index], sizeof(del_op));
        if(del_op.address == handle_p->address)
        {
          // Record will be deleted
          record_is_deleted_in_cache = TRUE;
          break;
        }
        advance_to_next_record = TRUE;
      }
      if(record_is_deleted_in_cache)
      {
        continue;
      }
#endif

      *data_p = (uint8_t *)handle_p->address + RECORD_HEADER_SIZE;
      *data_len = record_p->header.length;

      if(record_type != NULL)
      {
        *record_type = record_p->header.record_id;
      }

      //memcpy(data_p, (uint8_t*)handle_p->address + RECORD_HEADER_SIZE + offset, MIN(record_p->header.length - offset, max_size));
      //*size_p = record_p->header.length;

      return NVMDB_STATUS_OK;
    }
  }
}

static NVMDB_status_t ReadNextRecordNoLock(NVMDB_HandleType *handle_p, uint8_t record_type, NVMDB_RecordSizeType offset, uint8_t *data_p, NVMDB_RecordSizeType max_size, NVMDB_RecordSizeType *size_p, NVMDB_RecordSizeType current_record_length, uint8_t *record_type_out)
{
  NVMDB_status_t status;

  uint8_t *data;
  NVMDB_RecordSizeType data_len;

  *size_p = 0;

  status = NextRecordNoLock(handle_p, record_type, &data, &data_len, current_record_length, record_type_out);

  if(status != NVMDB_STATUS_OK)
  {
    return status;
  }

  if(offset >= data_len)
  {
    return NVMDB_STATUS_INVALID_OFFSET;
  }

  memcpy(data_p, data + offset, MIN(data_len - offset, max_size));
  *size_p = data_len;

  return NVMDB_STATUS_OK;
}

/**
 * @brief      Estimate if there is time to perform operations on DBs.
 *
 *             This is a weak function. Application has to implement it, so that
 *             the NVM manager can safely execute Flash operations while radio is
 *             active. Weak definition always return TRUEe.
 *
 * @param      time This is the time (in system time units) required for the operation
 * @retval     It returns TRUE is there is enough time, otherwise FALSE.
 */
__weak uint8_t NVMDB_TimeCheck(int32_t time)
{
  return TRUE;
}

/* flash_address must be word aligned. */
static void write_data(uint32_t flash_address, uint16_t data_length, const void *data)
{
  uint32_t word;
  uint16_t length_word;
  uint8_t rest;
  const uint8_t *data_8 = data;

  length_word = (data_length >> 2) << 2;
  rest = data_length - length_word;

  for(int i = 0; i < length_word; i += 4)
  {
    memcpy(&word, data_8 + i, sizeof(word));
    NVMDB_FLASH_WRITE(flash_address + i, word);
  }
  word = 0xFFFFFFFF;
  memcpy(&word, data_8 + length_word, rest);
  NVMDB_FLASH_WRITE(flash_address + length_word, word);
}

static NVMDB_status_t WriteRecord(uint32_t flash_address, uint8_t record_id, uint16_t data1_length, const void *data1, uint16_t data2_length, const void *data2)
{
  uint32_t word;
  NVMDB_RecordHeaderType *header_p = (NVMDB_RecordHeaderType *)&word;
#if NVM_CACHE
  int32_t needed_time;
#endif

  data1_length = ROUND4_R(data1_length); // Make sure data1_length is multiple of 4.

  header_p->valid_flag = VALID_RECORD;
  header_p->record_id = record_id;
  header_p->length = data1_length + data2_length;

#if NVM_CACHE
  needed_time = CalculateFlashTimeOperation(data1_length + data2_length + 4, 0);

  // Disable interrupts, to be sure that there are no additional delays while writing, which can cause writes to happen during
  // radio activity.
  ATOMIC_SECTION_BEGIN();
  if(!NVMDB_TimeCheck(needed_time))
  {
    // Not enough time
    ATOMIC_SECTION_END();
    return NVMDB_STATUS_NOT_ENOUGH_TIME;
  }
#endif

  DEBUG_GPIO_HIGH();

  NVMDB_FLASH_WRITE(flash_address, word);

  write_data(flash_address + 4, data1_length, data1);
  write_data(flash_address + 4 + data1_length, data2_length, data2);

  DEBUG_GPIO_LOW();
#if NVM_CACHE
  ATOMIC_SECTION_END();
#endif

  return NVMDB_STATUS_OK;
}

int NVMDB_CompareCurrentRecord(NVMDB_HandleType *handle_p, NVMDB_RecordSizeType offset, const uint8_t *data_p, NVMDB_RecordSizeType size)
{
  NVMDB_RecordType_ptr record_p;

#if NVM_CACHE

  NVMDB_RecordSizeType record_size;
  NVMDB_RecordSizeType remaining_size;

  if(handle_p->cache)  // Handle points to records in cache
  {
    uint8_t *data_src;

    if(ReadRecordInCache(handle_p, &data_src, &record_size, FALSE, NULL) == NVMDB_STATUS_OK)
    {
      remaining_size = record_size - offset;
      if(size <= remaining_size && memcmp(data_p, data_src + offset, size) == 0)
      {
        return NVMDB_STATUS_OK;
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return NVMDB_STATUS_INVALID_RECORD;
    }
  }

#endif

  record_p = (NVMDB_RecordType_ptr)handle_p->address;

  if(handle_p->address >= handle_p->end_address || record_p->header.valid_flag == NO_RECORD)
  {
    return NVMDB_STATUS_END_OF_DB;
  }

  if(handle_p->first_read || record_p->header.valid_flag != VALID_RECORD)
  {
    return NVMDB_STATUS_INVALID_RECORD;
  }

#if NVM_CACHE
  // Check if there is a delete operation in cache on this record.
  uint16_t index = cache_head;

  while(CacheFindOperation(handle_p->id, CACHE_DELETE_OP, index, &index, TRUE))
  {
    CacheDeleteOperationType del_op;
    memcpy(&del_op, &NVM_cache[index], sizeof(del_op));
    if(del_op.address == handle_p->address)
    {
      // Record will be deleted
      return NVMDB_STATUS_INVALID_RECORD;
    }
  }
#endif

  if(offset >= record_p->header.length)
  {
    return NVMDB_STATUS_INVALID_OFFSET;
  }

  handle_p->first_read = FALSE;

  if(memcmp(data_p, (uint8_t *)handle_p->address + RECORD_HEADER_SIZE + offset, size) == 0)
  {
    return NVMDB_STATUS_OK;
  }
  else
  {
    return -1;
  }
}

static NVMDB_status_t ReadCurrentRecordNoLock(NVMDB_HandleType *handle_p, NVMDB_RecordSizeType offset, uint8_t *data_p, NVMDB_RecordSizeType max_size, NVMDB_RecordSizeType *size_p, NVMDB_RecordSizeType current_record_length)
{
  NVMDB_RecordHeaderType header;
  NVMDB_RecordType_ptr record_p;

  *size_p = 0;

#if NVM_CACHE
  if(handle_p->cache)  // Handle points to records in cache
  {
    uint8_t *data_src;

    if(ReadRecordInCache(handle_p, &data_src, size_p, FALSE, NULL) == NVMDB_STATUS_OK)
    {
      // A record to be written has been found in cache
      memcpy(data_p, data_src + offset, MIN(*size_p - offset, max_size));
      return NVMDB_STATUS_OK;
    }
    else
    {
      return NVMDB_STATUS_INVALID_RECORD;
    }
  }
#endif

  if(current_record_length)
  {
    header.length = current_record_length;
    header.valid_flag = VALID_RECORD;
    record_p = (NVMDB_RecordType_ptr) & header;
  }
  else
  {
    record_p = (NVMDB_RecordType_ptr)handle_p->address;
  }

  if(handle_p->address >= handle_p->end_address || record_p->header.valid_flag == NO_RECORD)
  {
    return NVMDB_STATUS_END_OF_DB;
  }

  if(handle_p->first_read || record_p->header.valid_flag != VALID_RECORD)
  {
    return NVMDB_STATUS_INVALID_RECORD;
  }

#if NVM_CACHE
  // Check if there is a delete operation in cache on this record.
  uint16_t index = cache_head;

  while(CacheFindOperation(handle_p->id, CACHE_DELETE_OP, index, &index, TRUE))
  {
    CacheDeleteOperationType del_op;
    memcpy(&del_op, &NVM_cache[index], sizeof(del_op));
    if(del_op.address == handle_p->address)
    {
      // Record will be deleted
      return NVMDB_STATUS_INVALID_RECORD;
    }
  }
#endif

  if(offset >= record_p->header.length)
  {
    return NVMDB_STATUS_INVALID_OFFSET;
  }

  handle_p->first_read = FALSE;

  memcpy(data_p, (uint8_t *)handle_p->address + RECORD_HEADER_SIZE + offset, MIN(record_p->header.length - offset, max_size));
  *size_p = record_p->header.length;

  return NVMDB_STATUS_OK;
}

static NVMDB_status_t InvalidateRecord(uint32_t address)
{
  uint32_t word = 0xFFFFFF00;

#if NVM_CACHE
  int32_t needed_time;

  needed_time = CalculateFlashTimeOperation(4, 0);

  ATOMIC_SECTION_BEGIN();
  if(!NVMDB_TimeCheck(needed_time))
  {
    // Not enough time
    ATOMIC_SECTION_END();
    return NVMDB_STATUS_NOT_ENOUGH_TIME;
  }
#endif
  DEBUG_GPIO_HIGH();
  NVMDB_FLASH_WRITE(address, word);
  DEBUG_GPIO_LOW();

#if NVM_CACHE
  ATOMIC_SECTION_END();
#endif

  return NVMDB_STATUS_OK;
}

static NVMDB_status_t NVMDB_DeleteRecordNoCache(const NVMDB_HandleType *handle_p)
{
  NVMDB_RecordType *record_p;
  NVMDB_status_t status;

  record_p = (NVMDB_RecordType_ptr)handle_p->address;

  if(handle_p->address >= handle_p->end_address || record_p->header.valid_flag == NO_RECORD)
  {
    return NVMDB_STATUS_END_OF_DB;
  }
  if(record_p->header.valid_flag == VALID_RECORD)
  {

    status = InvalidateRecord((uint32_t)record_p);
    if(status)
    {
      return status;
    }

    DBInfo[handle_p->id].valid_records--;
    DBInfo[handle_p->id].invalid_records++;

    return NVMDB_STATUS_OK;
  }
  else
  {
    return NVMDB_STATUS_INVALID_RECORD;
  }
}

static void ErasePage(uint32_t address, uint8_t num_pages)
{
  int page_num = (address - _MEMORY_FLASH_BEGIN_) / PAGE_SIZE;

  DEBUG_GPIO_HIGH();
  NVMDB_FLASH_ERASE_PAGE(page_num, num_pages);
  DEBUG_GPIO_LOW();
}

/* Size of data must be multiple of 4. This function also erases the page if needed. */
static void WriteBufferToFlash(uint32_t address, uint32_t *data, uint32_t size)
{
  /* Check if we are writing the same data in entire pages.
     If size is less than a page size, we need to erase the page to clean it. */
  if((size % PAGE_SIZE) == 0 && memcmp((uint8_t *)address, data, size) == 0)
  {
    return;
  }

  ErasePage(address, ROUNDPAGE_R(size) / PAGE_SIZE);

  DEBUG_GPIO_HIGH();
  for(int i = 0; i < size; i += 4)
  {
    NVMDB_FLASH_WRITE(address + i, data[i / 4]);
  }
  DEBUG_GPIO_LOW();
}

static void InitReadState(ReadStateType *state_p)
{
  state_p->move_to_next_record = TRUE;
  state_p->record_offset = 0;
  state_p->record_length = 0;
}

/* Call InitReadState() to initialize read_state before passing it to the function to start loading data from the database.
   This function returns NVMDB_STATUS_OK if other calls must be done to the same function to continue reading the database.
   Pass the same read_state variable to the function if calling it again to continue reading from the same database. */

static NVMDB_status_t LoadDBToRAM(NVMDB_HandleType *handle_p, uint8_t *buff, uint16_t buff_size, uint16_t *num_read_bytes_p, ReadStateType *read_state)
{
  NVMDB_status_t status;
  uint16_t free_buffer_size;
  NVMDB_RecordSizeType record_size, remaining_record_bytes;
  NVMDB_RecordHeaderType header;
  uint16_t index = 0;

  memset(buff, 0xFF, buff_size);

  header.valid_flag = VALID_RECORD;

  while(1)
  {

    free_buffer_size = buff_size - index - RECORD_HEADER_SIZE;

    // Read the record
    if(read_state->move_to_next_record)
    {
      /* Passing read_state->record_length to the function because we do not want
         the function to retrieve the info from the header of the current record,
         since it may not be anymore in the same position in flash. */
      status = ReadNextRecordNoLock(handle_p, ALL_TYPES, 0, buff + index + RECORD_HEADER_SIZE, free_buffer_size, &record_size, read_state->record_length, &header.record_id);
      read_state->record_length = record_size;

      if(status != NVMDB_STATUS_OK)
      {
        *num_read_bytes_p = index;
        return status;
      }

      // Prepare the header and copy it to buffer
      header.length = record_size;
      memcpy(buff + index, &header, RECORD_HEADER_SIZE);
      index += ROUND4_R(header.length + RECORD_HEADER_SIZE);
    }
    else
    {

      status = ReadCurrentRecordNoLock(handle_p, read_state->record_offset, buff + index, free_buffer_size, &record_size, read_state->record_length); // It will not read record in cache because this operation is not allowed if there are any.

      if(status != NVMDB_STATUS_OK)
      {
        // This should not happen
        return status;
      }
      index = ROUND4_R(record_size - read_state->record_offset);
    }

    // The number of remaining bytes for the current record that were to be read before calling last NVMDB_ReadNextRecord().
    // Rounded to the next multiple of 4 to find out if buffer can now be written inside the page or not.
    remaining_record_bytes = ROUND4_R(record_size - read_state->record_offset);

    if(remaining_record_bytes > free_buffer_size)
    {
      // Not able to read the entire record.
      read_state->move_to_next_record = FALSE;
      read_state->record_offset += free_buffer_size;
      *num_read_bytes_p = buff_size;
      return NVMDB_STATUS_OK;
    }
    else if(remaining_record_bytes == free_buffer_size)
    {
      read_state->move_to_next_record = TRUE;
      read_state->record_offset = 0;
      *num_read_bytes_p = buff_size;
      return NVMDB_STATUS_OK;
    }
    else if(remaining_record_bytes < free_buffer_size)
    {
      read_state->move_to_next_record = TRUE;
      read_state->record_offset = 0;
    }
  }
}
// No inline to avoid allocating NVM_buffer multiple times at the same time.
__NOINLINE static NVMDB_status_t CleanLargeDB(NVMDB_IdType NVMDB_id)
{
  NVMDB_status_t status;
  uint32_t flash_write_address;
  uint16_t num_read_bytes;
  NVMDB_HandleType handle;
  ReadStateType state;
#if NVM_CACHE
  NVMDB_HandleType previous_handle;
  ReadStateType previous_state;
  int32_t needed_time;
  uint8_t clean_started = FALSE;
#endif

  if(!DBInfo[NVMDB_id].invalid_records)
  {
    return NVMDB_STATUS_OK;
  }

#if NVM_CACHE
  // Check if there are any operations in cache
  if(CacheFindOperation(NVMDB_id, CACHE_ALL, cache_head, NULL, FALSE))
  {
    return NVMDB_STATUS_CACHE_OP_PENDING;
  }

  //Check if there is enough space in cache for a potential clean or erase operation.
  if(!CacheRequestBuffer(MAX(sizeof(CacheCleanLargeOperationType), sizeof(CachePageEraseOperationType))))
  {
    return NVMDB_STATUS_CACHE_FULL;
  }
#endif

  status = NVMDB_HandleInit(NVMDB_id, &handle);
  flash_write_address = (uint32_t)handle.address;

  InitReadState(&state);

  while(1)
  {
#if !NVMDB_STATIC_BUFF
    uint8_t NVM_buffer[PAGE_SIZE];
#endif

#if NVM_CACHE
    previous_state = state;
    previous_handle = handle;
#endif

    status = LoadDBToRAM(&handle, NVM_buffer, sizeof(NVM_buffer), &num_read_bytes, &state);
    if(status != NVMDB_STATUS_END_OF_DB && status != NVMDB_STATUS_OK) // No other error codes are expected. This should not happen.
    {
      return status;
    }

    if(num_read_bytes == sizeof(NVM_buffer) || status != NVMDB_STATUS_OK)
    {
      if(num_read_bytes == 0)
      {
        // This can happen if the end of the database is reached at the beginning of the LoadDBToRAM() function.
        break;
      }

#if NVM_CACHE
      needed_time = CalculateFlashTimeOperation(num_read_bytes, 1);

      ATOMIC_SECTION_BEGIN();

      if(!NVMDB_TimeCheck(needed_time))
      {
        /* Not enough time. Do not schedule clean operation if it is the first write. NVMDB_Tick() will try again later.
           This avoids locking the database. */
        ATOMIC_SECTION_END();
        if(!clean_started)
        {
          return NVMDB_STATUS_NOT_ENOUGH_TIME;
        }
        else
        {
          return ScheduleCleanLargeDBOperation(previous_handle, flash_write_address, previous_state);
        }
      }
#endif

      // Write buffer to flash
      WriteBufferToFlash(flash_write_address, (uint32_t *)NVM_buffer, num_read_bytes);
#if NVM_CACHE
      ATOMIC_SECTION_END();

      clean_started = TRUE;
#endif
      flash_write_address += sizeof(NVM_buffer);
      if(status != NVMDB_STATUS_OK)
      {
        break;
      }
    }
  }
  // Erase remaining pages. A possible optimization could be to erase the page only if it is not already erased.
  uint8_t num_pages = (ROUNDPAGE_R(handle.end_address) - flash_write_address) / PAGE_SIZE;
  uint8_t page_num_start = (flash_write_address - _MEMORY_FLASH_BEGIN_) / PAGE_SIZE;

#if NVM_CACHE

  if(EraseWithTimeCheck(&page_num_start, &num_pages) == NVMDB_STATUS_NOT_ENOUGH_TIME)
  {
    return SchedulePageEraseOperation(NVMDB_id, page_num_start, num_pages);
  }
#else
  NVMDB_FLASH_ERASE_PAGE(page_num_start, num_pages);
#endif

  // Update free space.
  return NVMDB_get_info(&DBInfo[NVMDB_id]);
}

#if NVM_CACHE
__NOINLINE static NVMDB_status_t ContinueCleanLargeDB(CacheCleanLargeOperationType *op)
{
  NVMDB_status_t status;
  NVMDB_HandleType previous_handle;
  uint16_t num_read_bytes;
  ReadStateType previous_state;
  int32_t needed_time;

#if !NVMDB_STATIC_BUFF
    uint8_t NVM_buffer[PAGE_SIZE];
#endif

  while(1)
  {

    previous_state = op->read_state;
    previous_handle = op->handle;
    status = LoadDBToRAM(&op->handle, NVM_buffer, sizeof(NVM_buffer), &num_read_bytes, &op->read_state);
    if(num_read_bytes == sizeof(NVM_buffer) || status != NVMDB_STATUS_OK)
    {
      if(num_read_bytes == 0)
      {
        // This can happen if the end of the database is reached at the beginning of the LoadDBToRAM() function.
        break;
      }

      needed_time = CalculateFlashTimeOperation(num_read_bytes, 0);

      ATOMIC_SECTION_BEGIN();

      if(!NVMDB_TimeCheck(needed_time))
      {
        // Not enough time. Restore state to the one before the load.
        ATOMIC_SECTION_END();
        op->handle = previous_handle;
        op->read_state = previous_state;
        return NVMDB_STATUS_NOT_ENOUGH_TIME;
      }

      // Write buffer to flash
      WriteBufferToFlash(op->flash_address, (uint32_t *)NVM_buffer, num_read_bytes);

      ATOMIC_SECTION_END();

      op->flash_address += sizeof(NVM_buffer);
      if(status != NVMDB_STATUS_OK)
      {
        break;
      }
    }
  }

  // Erase remaining pages. A possible optimization could be to erase the page only if it is not already erased.
  uint8_t num_pages = (ROUNDPAGE_R(op->handle.end_address) - op->flash_address) / PAGE_SIZE;
  uint8_t page_num_start = (op->flash_address - _MEMORY_FLASH_BEGIN_) / PAGE_SIZE;

  if(EraseWithTimeCheck(&page_num_start, &num_pages) == NVMDB_STATUS_NOT_ENOUGH_TIME)
  {
    return SchedulePageEraseOperation(op->handle.id, page_num_start, num_pages);
  }

  // Update free space.
  return NVMDB_get_info(&DBInfo[op->handle.id]);
}
#endif

__NOINLINE static NVMDB_status_t CleanPage(const NVMDB_SmallDBContainerType *smallDBContainer_p)
{
  NVMDB_status_t status;
  NVMDB_status_t ret = NVMDB_STATUS_OK;
  uint8_t NVMDB_id;
  NVMDB_HandleType handle;
  uint32_t page_offset;
  uint16_t num_bytes;
  ReadStateType state;
  int i;
  uint8_t found = FALSE;
#if NVM_CACHE
  int32_t needed_time;
#endif

#if !NVMDB_STATIC_BUFF
  uint8_t NVM_buffer[PAGE_SIZE];
#endif

  /* Check if there are invalids record in the page and if there are pending operations on the databases. */
  for(i = 0; i < smallDBContainer_p->num_db; i++)
  {
    NVMDB_id = smallDBContainer_p->dbs[i].id;
    if(DBInfo[NVMDB_id].invalid_records)
    {
      found = TRUE;
    }
#if NVM_CACHE
    if(CacheFindOperation(NVMDB_id, CACHE_ALL, cache_head, NULL, FALSE))
    {
      return NVMDB_STATUS_CACHE_OP_PENDING;
    }
#endif
  }
  if(!found)
  {
    /* No invalid records found. */
    return NVMDB_STATUS_OK;
  }

  memset(NVM_buffer, 0xFF, sizeof(NVM_buffer));

  for(i = 0; i < smallDBContainer_p->num_db; i++)
  {
    NVMDB_id = smallDBContainer_p->dbs[i].id;
    page_offset = smallDBContainer_p->dbs[i].offset;

    status = NVMDB_HandleInit(NVMDB_id, &handle);
    if(status) // This should not happen
    {
      return NVMDB_STATUS_OK;
    }

    InitReadState(&state);
    // It cannot happen that the database does not fill inside the buffer. So we call LoadDBToRAM() just once for each db.
    LoadDBToRAM(&handle, NVM_buffer + page_offset, sizeof(NVM_buffer) - page_offset, &num_bytes, &state);
  }

#if NVM_CACHE

  needed_time = CalculateFlashTimeOperation(sizeof(NVM_buffer), 1);

  ATOMIC_SECTION_BEGIN();

  if(!NVMDB_TimeCheck(needed_time))
  {
    // Not enough time
    ATOMIC_SECTION_END();
    return NVMDB_STATUS_NOT_ENOUGH_TIME;
  }
#endif

  WriteBufferToFlash(smallDBContainer_p->page_address, (uint32_t *)NVM_buffer, sizeof(NVM_buffer));

#if NVM_CACHE
  ATOMIC_SECTION_END();
#endif

  for(i = 0; i < smallDBContainer_p->num_db; i++)
  {
    NVMDB_id = smallDBContainer_p->dbs[i].id;
    // Update free space.
    status = NVMDB_get_info(&DBInfo[NVMDB_id]);
    if(status)
    {
      ret = status; // Return last error if any.
    }
  }

  return ret;
}

static uint8_t GetDBType(NVMDB_IdType NVMDB_id, const NVMDB_SmallDBContainerType **smallDBContainer)
{
  uint8_t id;

  /* Check if it is a large DB. */

  for(int i = 0; i < NUM_LARGE_DBS; i++)
  {

    id = NVM_LARGE_DB_STATIC_INFO[i].id;

    if(id == NVMDB_id)
    {
      return LARGE_DB;
    }
  }

  for(int i = 0; i < NUM_SMALL_DB_PAGES; i++)
  {

    for(int j = 0; j < NVM_SMALL_DB_STATIC_INFO[i].num_db; j++)
    {
      id = NVM_SMALL_DB_STATIC_INFO[i].dbs[j].id;

      if(id == NVMDB_id)
      {
        // DB found inside this small db container.
        *smallDBContainer = &NVM_SMALL_DB_STATIC_INFO[i];
        return SMALL_DB;
      }
    }
  }

  return 0;
}

#if NVM_CACHE

static uint16_t CacheGetDataSize(void)
{
  return cache_tail - cache_head;
}

static uint8_t CacheRequestBuffer(uint16_t length)
{
  uint16_t data_size = CacheGetDataSize();

  if(length > NVM_CACHE_SIZE - data_size)
  {
    return FALSE;
  }

  if(NVM_CACHE_SIZE - cache_tail < length)
  {
    /* Shift buffer content */
    memmove(NVM_cache, NVM_cache + cache_head, data_size);
    cache_head = 0;
    cache_tail = data_size;
  }
  return TRUE;
}

static uint8_t CacheInsertData(const void *data, uint16_t length)
{
  if(length > NVM_CACHE_SIZE - cache_tail)
  {
    return FALSE;
  }

  memcpy(NVM_cache + cache_tail, data, length);
  cache_tail += length;

  return TRUE;
}

static NVMDB_status_t ScheduleWriteOperation(NVMDB_IdType NVMDB_id, uint8_t record_type, uint32_t flash_address, uint16_t data1_length, const void *data1, uint16_t data2_length, const void *data2)
{
  CacheWriteOperationType write_op;

  data1_length = ROUND4_R(data1_length);

  if(!CacheRequestBuffer(sizeof(CacheWriteOperationType) + data1_length + data2_length))
  {
    // Not enough space in cache
    return NVMDB_STATUS_CACHE_FULL;
  }

  write_op.op = CACHE_WRITE_OP;
  write_op.length = data1_length + data2_length + sizeof(write_op);
  //write_op.address = flash_address;
  write_op.id = NVMDB_id;
  write_op.record_type = record_type;

  CacheInsertData(&write_op, sizeof(write_op));
  CacheInsertData(data1, data1_length);
  CacheInsertData(data2, data2_length);

  return NVMDB_STATUS_OK;
}

static NVMDB_status_t ScheduleDeleteOperation(NVMDB_IdType NVMDB_id, uint32_t flash_address)
{
  CacheDeleteOperationType del_op;

  if(!CacheRequestBuffer(sizeof(CacheDeleteOperationType)))
  {
    // Not enough space in cache
    return NVMDB_STATUS_CACHE_FULL;
  }

  del_op.length = sizeof(del_op);
  del_op.op = CACHE_DELETE_OP;
  del_op.id = NVMDB_id;
  del_op.address = flash_address;

  CacheInsertData(&del_op, sizeof(del_op));

  return NVMDB_STATUS_OK;
}

static NVMDB_status_t ScheduleSmallDBEraseOperation(NVMDB_IdType NVMDB_id, const NVMDB_SmallDBContainerType *smallDBContainer_p)
{
  CacheSmallDBEraseOperationType erase_op;

  if(!CacheRequestBuffer(sizeof(CacheSmallDBEraseOperationType)))
  {
    // Not enough space in cache
    return NVMDB_STATUS_CACHE_FULL;
  }

  // We can remove all the cache operations for this DB. They are no more needed. Save space for other DB operations.
  RemoveCacheOp(NVMDB_id);

  erase_op.length = sizeof(erase_op);
  erase_op.op = CACHE_SMALL_DB_ERASE_OP;
  erase_op.id = NVMDB_id;
  erase_op.smallDBContainer_p = smallDBContainer_p;

  CacheInsertData(&erase_op, sizeof(erase_op));

  // Lock operations on erased DB.

  DBInfo[NVMDB_id].locked = TRUE;

  return NVMDB_STATUS_OK;
}

static NVMDB_status_t ScheduleCleanLargeDBOperation(NVMDB_HandleType handle, uint32_t flash_address, ReadStateType state)
{
  CacheCleanLargeOperationType clean_op;

  if(!CacheRequestBuffer(sizeof(clean_op)))
  {
    // Not enough space in cache
    return NVMDB_STATUS_CACHE_FULL;
  }

  clean_op.length = sizeof(clean_op);
  clean_op.op = CACHE_CLEAN_LARGE_DB_OP;
  clean_op.handle = handle;
  clean_op.flash_address = flash_address;
  clean_op.read_state = state;

  CacheInsertData(&clean_op, sizeof(clean_op));

  DBInfo[handle.id].locked = TRUE;

  return NVMDB_STATUS_OK;
}

static NVMDB_status_t SchedulePageEraseOperation(NVMDB_IdType NVMDB_id, uint8_t page_num_start, uint8_t num_pages)
{
  CachePageEraseOperationType erase_op;

  if(!CacheRequestBuffer(sizeof(erase_op)))
  {
    // Not enough space in cache
    return NVMDB_STATUS_CACHE_FULL;
  }

  erase_op.length = sizeof(erase_op);
  erase_op.op = CACHE_PAGE_ERASE_OP;
  erase_op.id = NVMDB_id;
  erase_op.page_num_start = page_num_start;
  erase_op.num_pages = num_pages;

  CacheInsertData(&erase_op, sizeof(erase_op));

  DBInfo[NVMDB_id].locked = TRUE;

  return NVMDB_STATUS_OK;
}

#endif

__NOINLINE static NVMDB_status_t EraseSmallDB(NVMDB_IdType NVMDB_id, const NVMDB_SmallDBContainerType *smallDBContainer_p)
{
#if NVM_CACHE
  int32_t needed_time;
#endif
#if !NVMDB_STATIC_BUFF
  uint8_t NVM_buffer[PAGE_SIZE];
#endif

  memset(NVM_buffer, 0xFF, sizeof(NVM_buffer));

  // Search other databases in the same page
  for(int i = 0; i < smallDBContainer_p->num_db; i++)
  {
    NVMDB_HandleType handle;
    uint16_t num_read_bytes;
    ReadStateType state;
    NVMDB_IdType id = smallDBContainer_p->dbs[i].id;
    if(id != NVMDB_id)
    {
      // This is not the db to be erased. Save it.
      NVMDB_HandleInit(id, &handle);
      uint32_t offset = smallDBContainer_p->dbs[i].offset;
      InitReadState(&state);
      LoadDBToRAM(&handle, NVM_buffer + offset, sizeof(NVM_buffer) - offset, &num_read_bytes, &state);
    }
  }

  // All other databases are saved in RAM
#if NVM_CACHE
  needed_time = CalculateFlashTimeOperation(sizeof(NVM_buffer), 1);

  ATOMIC_SECTION_BEGIN();

  if(!NVMDB_TimeCheck(needed_time))
  {
    // Not enough time. Restore state to the one before the load.
    ATOMIC_SECTION_END();
    //return ScheduleSmallDBEraseOperation(NVMDB_id, smallDBContainer_p);
    return NVMDB_STATUS_NOT_ENOUGH_TIME;
  }
#endif

  // Write buffer to flash
  WriteBufferToFlash(smallDBContainer_p->page_address, (uint32_t *)NVM_buffer, sizeof(NVM_buffer));

#if NVM_CACHE
  ATOMIC_SECTION_END();
#endif

  return NVMDB_STATUS_OK;
}

static NVMDB_status_t NVMDB_AppendRecordNoCache(NVMDB_HandleType *handle_p, uint8_t record_id, uint16_t data1_length, const void *data1, uint16_t data2_length, const void *data2)
{
  NVMDB_RecordType *record_p;
  NVMDB_RecordSizeType available_size;
  NVMDB_status_t status;

  data1_length = ROUND4_R(data1_length);

  /* Check if there is space in the db. Not strictly needed. But this check is faster in case the db is full (instead of parsing every records).  */
//  if(length > DBInfo[handle_p->id].free_space){
//    if(DBInfo[handle_p->id].invalid_records)
//      return NVMDB_STATUS_CLEAN_NEEDED;
//    return NVMDB_STATUS_FULL_DB;
//  }

  /* Search for first available entry. */

  while(1)
  {

    if(handle_p->address + MIN_RECORD_SIZE >= handle_p->end_address)
    {
      /* End of DB reached. This should not happen since the free space has been checked before.
         Should we remove this code or keep it to be safer?  */
      if(DBInfo[handle_p->id].invalid_records)
      {
        return NVMDB_STATUS_CLEAN_NEEDED;
      }
      return NVMDB_STATUS_FULL_DB;
    }

    record_p = (NVMDB_RecordType_ptr)handle_p->address;

    if(record_p->header.valid_flag == NO_RECORD)
    {
      available_size = MIN(handle_p->end_address - handle_p->address, MAX_RECORD_SIZE);
      break;
    }
    else if(record_p->header.valid_flag != VALID_RECORD && record_p->header.valid_flag != INVALID_RECORD)
    {
      return NVMDB_STATUS_CORRUPTED_DB;
    }

    handle_p->address += ROUND4_R(record_p->header.length + RECORD_HEADER_SIZE);
  }

  if(available_size < data1_length + data2_length + RECORD_HEADER_SIZE)
  {
    /* End of DB reached. This should not happen since the free space has been checked before.
       Should we remove this code or keep it to be safer?  */
    if(DBInfo[handle_p->id].invalid_records)
    {
      return NVMDB_STATUS_CLEAN_NEEDED;
    }
    return NVMDB_STATUS_FULL_DB;
  }

  status = WriteRecord(handle_p->address, record_id, data1_length, data1, data2_length, data2);
  if(status)
  {
    return status;
  }

  DBInfo[handle_p->id].valid_records++;

  return NVMDB_STATUS_OK;
}

/**
 * @}
 */

/** @defgroup NVM_Manager_Public_Functions Public Functions
 * @{
 */

/**
 * @brief  Initialize the NVM Manager.
 *
 *         Function to be called before using the library.
 *
 * @param  None
 * @retval Indicates if the function executed successfully.
 */
NVMDB_status_t NVMDB_Init(void)
{
  // Checks DB consistency. Reads number of records.

  NVMDB_status_t status;
  uint32_t page_address, offset;
  uint16_t clean_threshold;
  uint8_t id;

  /* Parse small DBs. */
  for(int i = 0; i < NUM_SMALL_DB_PAGES; i++)
  {

    page_address = NVM_SMALL_DB_STATIC_INFO[i].page_address;

    for(int j = 0; j < NVM_SMALL_DB_STATIC_INFO[i].num_db; j++)
    {
      id = NVM_SMALL_DB_STATIC_INFO[i].dbs[j].id;
      offset = NVM_SMALL_DB_STATIC_INFO[i].dbs[j].offset;
#if AUTO_CLEAN
      clean_threshold = NVM_SMALL_DB_STATIC_INFO[i].dbs[j].clean_threshold;
#endif
      if(DBInfo[id].start_address || id >= NUM_DB)
      {
        // ID already used.
        return NVMDB_STATUS_INVALID_ID;
      }
      DBInfo[id].start_address = page_address + offset;

      if(j == NVM_SMALL_DB_STATIC_INFO[i].num_db - 1)
      {
        // If it is the last db of the page, end address is the last address of the page
        DBInfo[id].end_address = page_address + PAGE_SIZE;
      }
      else
      {
        // If it is not the last db of the page, end address is the start address of the next db
        DBInfo[id].end_address = page_address + NVM_SMALL_DB_STATIC_INFO[i].dbs[j + 1].offset;
      }
      DBInfo[id].clean_threshold = clean_threshold;

      status = NVMDB_get_info(&DBInfo[id]);
      if(status)
      {
        return status;
      }
    }
  }

  /* Parse large DBs. */
  for(int i = 0; i < NUM_LARGE_DBS; i++)
  {

    id = NVM_LARGE_DB_STATIC_INFO[i].id;

    if(DBInfo[id].start_address || id >= NUM_DB)
    {
      // ID already used.
      return NVMDB_STATUS_INVALID_ID;
    }

    DBInfo[id].start_address = NVM_LARGE_DB_STATIC_INFO[i].address;
    DBInfo[id].end_address = NVM_LARGE_DB_STATIC_INFO[i].address + NVM_LARGE_DB_STATIC_INFO[i].size;
#if AUTO_CLEAN
    DBInfo[id].clean_threshold = NVM_LARGE_DB_STATIC_INFO[i].clean_threshold;
#endif

    status = NVMDB_get_info(&DBInfo[id]);
    if(status)
    {
      return status;
    }
  }

  return NVMDB_STATUS_OK;
}

/**
 * @brief      Initialize the handle that points to the given database.
 *
 *             NVMDB_HandleInit has to be called before using functions that
 *             need an handle.
 *
 * @param      NVMDB_id ID of the database. This is a number that uniquely identifies
 *             the database. The IDs are decided when declaring the database structure
 *             through NVM_SMALL_DB_STATIC_INFO and NVM_LARGE_DB_STATIC_INFO variables.
 * @param[out] handle_p Pointer to the handle to be initialized.
 * @retval Indicates if the function executed successfully.
 */
NVMDB_status_t NVMDB_HandleInit(NVMDB_IdType NVMDB_id, NVMDB_HandleType *handle_p)
{
  if(NVMDB_id >= NUM_DB)
  {
    return NVMDB_STATUS_INVALID_ID;
  }

  handle_p->address = DBInfo[NVMDB_id].start_address;
  handle_p->end_address = DBInfo[NVMDB_id].end_address;
  handle_p->first_read = TRUE;
  handle_p->id = NVMDB_id;
  handle_p->cache = FALSE;

  return NVMDB_STATUS_OK;
}

/**
 * @brief      Read data from the next record in the database.
 *
 *             Retrieve data from the next valid record in the database.
 *             Each time NVMDB_ReadNextRecord is called, the handle is firstly
 *             moved forward in order to point to the next valid record in the database.
 *             Record data is copied into the provided buffer.
 *
 * @param[in,out] handle_p Handle pointing to the database. It must have been previously
 *             initialized with NVMDB_HandleInit. After calling the function, the
 *             handle can be used again to read the next record.
 * @param      record_type Type of the record. This value is application-specific. Use
 *             ALL_TYPES to read every records, regardless of the type.
 * @param      data_offset Offset inside the record from which data has to be copied.
 *             Normally it is set to 0.
 * @param[out] data_p Array in which data will be copied.
 * @param      max_size Size of the buffer pointed by data_p.
 * @param[out] size_p Size of the read record.
 * @retval     Indicates if the function executed successfully.
 */
NVMDB_status_t NVMDB_ReadNextRecord(NVMDB_HandleType *handle_p, uint8_t record_type, NVMDB_RecordSizeType data_offset, uint8_t *data_p, NVMDB_RecordSizeType max_size, NVMDB_RecordSizeType *size_p)
{
  if(DBInfo[handle_p->id].locked)
  {
    return NVMDB_STATUS_LOCKED;
  }

  return ReadNextRecordNoLock(handle_p, record_type, data_offset, data_p, max_size, size_p, 0, NULL);
}

/**
 * @brief      Read data from the current record in the database.
 *
 *             Retrieve data from the current valid record in the database.
 *             Handle is not moved before retrieving the data.
 *
 * @param[in,out] handle_p Handle pointing to the database. It must have been previously
 *             initialized with NVMDB_HandleInit.
 * @param      data_offset Offset inside the record from which data has to be copied.
 *             Normally it is set to 0.
 * @param[out] data_p Array in which data will be copied.
 * @param      max_size Size of the buffer pointed by data_p.
 * @param[out] size_p Size of the read record.
 * @retval     Indicates if the function executed successfully.
 */
NVMDB_status_t NVMDB_ReadCurrentRecord(NVMDB_HandleType *handle_p, NVMDB_RecordSizeType data_offset, uint8_t *data_p, NVMDB_RecordSizeType max_size, NVMDB_RecordSizeType *size_p)
{
  if(DBInfo[handle_p->id].locked)
  {
    return NVMDB_STATUS_LOCKED;
  }

  return ReadCurrentRecordNoLock(handle_p, data_offset, data_p, max_size, size_p, 0);
}

/**
 * @brief      Find next record in the database that matches the given pattern.
 *
 *             NVMDB_FindNextRecord searches inside the database starting from the
 *             record pointed by the given handle. If the pattern is found starting
 *             from pattern_offset, the function returns NVMDB_STATUS_OK and the
 *             handle points to the found record. The value of the record can be
 *             retrieved by providing a buffer where data will be copied.
 *
 * @note The handle is moved while searching inside the database.
 *
 * @param[in,out] handle_p Handle pointing to the database. It must have been previously
 *             initialized with NVMDB_HandleInit. After calling the function, the
 *             handle can be used again to search the pattern, starting from the next record.
 * @param      record_type Type of the record to search for. This value is application-specific. Use
 *             ALL_TYPES to read every records, regardless of the type.
 * @param      pattern_offset Offset at which the pattern has to be located inside the record.
 * @param[in]  pattern_p The pattern that has to be found inside the database.
 * @param      pattern_length Length of the pattern.
 * @param      data_offset Offset inside the record from which data has to be copied.
 *             Normally it is set to 0.
 * @param      data_offset Length of the pattern.
 * @param[out] data_p Array in which data will be copied. If NULL, no data is copied.
 * @param      max_size Size of the buffer pointed by data_p.
 * @param[out] size_p Size of the read record.
 * @retval     Indicates if the function executed successfully.
 */
NVMDB_status_t NVMDB_FindNextRecord(NVMDB_HandleType *handle_p, uint8_t record_type, NVMDB_RecordSizeType pattern_offset, const uint8_t *pattern_p, NVMDB_RecordSizeType pattern_length, NVMDB_RecordSizeType data_offset, uint8_t *data_p, NVMDB_RecordSizeType max_size, NVMDB_RecordSizeType *size_p)
{
  NVMDB_status_t status;
  uint8_t *data;
  NVMDB_RecordSizeType record_len;

  if(DBInfo[handle_p->id].locked)
  {
    return NVMDB_STATUS_CACHE_OP_PENDING;
  }

  while(1)
  {

    status = NextRecordNoLock(handle_p, record_type, &data, &record_len, 0, NULL);

    if(status != NVMDB_STATUS_OK)
    {
      return status;
    }

    if(pattern_offset >= record_len || pattern_length > record_len - pattern_offset)
    {
      continue;
    }

    if(memcmp(data + pattern_offset, pattern_p, pattern_length) == 0)
    {
      // Record has been found
      if(data_p != NULL)
      {
        *size_p = record_len;
        if(data_offset >= record_len)
        {
          return NVMDB_STATUS_INVALID_OFFSET;
        }
        memcpy(data_p, data + data_offset, MIN(record_len - data_offset, max_size));
      }

      return NVMDB_STATUS_OK;
    }
  }
}

/**
 * @brief      Add a record in the database.
 *
 *             The record is added at the end of the database pointed by the given handle.
 * @note       If the handle points to the last record in the database, the append
 *             operation is faster.
 * @note       A write or erase operation on the Flash prevents access to the
 *             Flash for a certain amount of time, potentially delaying execution
 *             of the time-critical radio interrupt service routine. Thus, it is checked
 *             that enough time is present before the next scheduled radio activity
 *             will start. If there is no enough time, this operation is scheduled. A
 *             cache is used to temporarily store the record.
 *
 * @param[in,out] handle_p Handle pointing to the database. It must have been previously
 *             initialized with NVMDB_HandleInit. If the function returns NVMDB_STATUS_OK,
 *             the handle points to the added record.
 *             @note If the returned value is not NVMDB_STATUS_OK, the handle my points to
 *             any record in the database.
 * @param      record_type One byte that can be used by the application to identify the type
 *             of record.
 * @param      header_length Length of bytes in header. It must be a multiple of 4. Set it to 0
 *             if header is NULL.
 * @param[in]  header Data to be stored at the beginning of the record. It can be used by the
 *             application to add an header to the record. The number of bytes must be a
 *             multiple of 4. Set it to NULL if no header has to be added to the record.
 * @param      header_length Length of bytes in data.
 * @param[in]  data Data to be stored inside the record.
 * @retval     Indicates if the function executed successfully.
 */
NVMDB_status_t NVMDB_AppendRecord(NVMDB_HandleType *handle_p, uint8_t record_type, uint16_t header_length, const void *header, uint16_t data_length, const void *data)
{
  NVMDB_status_t status;

#if NVM_CACHE

  if(DBInfo[handle_p->id].locked)
  {
    return NVMDB_STATUS_CACHE_OP_PENDING;
  }

  header_length = ROUND4_R(header_length);

  /* Check if there is space in the db.
     free_space is the real free space in Flash, taking also into account all the record to be added that are currently in cache. */
  if(header_length + data_length > DBInfo[handle_p->id].free_space)
  {
    if(DBInfo[handle_p->id].invalid_records)
    {
      return NVMDB_STATUS_CLEAN_NEEDED;
    }
    return NVMDB_STATUS_FULL_DB;
  }

  /* Check if there are other operations in cache for that db. In fact, if
     there is already a record in cache, that record must be written before this one.
     If there is also an erase pending, this record cannot be written and must be stored
     temporarily in cache. Instead, if there are delete record operations in cache it
     should be possible to try to write immediately the record (this case is not checked now).
     A future improvement could be to try to perform some operations in cache (in case we have time now). */
  if(CacheFindOperation(handle_p->id, CACHE_ALL, cache_head, NULL, FALSE))
  {
    status = ScheduleWriteOperation(handle_p->id, record_type, handle_p->address, header_length, header, data_length, data);
    if(status == NVMDB_STATUS_OK)
    {
      goto success;
    }
    else
    {
      return status;
    }
  }

  status = NVMDB_AppendRecordNoCache(handle_p, record_type, header_length, header, data_length, data);

  if(status == NVMDB_STATUS_OK)
  {
    goto success;
  }

  if(status != NVMDB_STATUS_NOT_ENOUGH_TIME)
  {
    return status;
  }

  /* No time to complete the operation immediately.  */
  status = ScheduleWriteOperation(handle_p->id, record_type, handle_p->address, header_length, header, data_length, data);

  if(status != NVMDB_STATUS_OK)
  {
    return status;
  }

success:

#else /* NVM_CACHE */
  status = NVMDB_AppendRecordNoCache(handle_p, record_type, header_length, header, data_length, data);

  if(status != NVMDB_STATUS_OK)
  {
    return status;
  }

#endif

  /* Take into account that the free space is reduced, even if the record is actually in cache.  */
  DBInfo[handle_p->id].free_space -= ROUND4_R(header_length + data_length) + RECORD_HEADER_SIZE;

  return NVMDB_STATUS_OK;
}

/**
 * @brief      Delete a record.
 *
 *             NVMDB_DeleteRecord deletes the record pointed by the given handle.
 *             Since the database is in Flash, the record is actually invalidated
 *             and cannot be read by other functions.
 *             A clean operation of the database definitively removes the record.
 *
 * @note       A write operation on the Flash prevents access to the
 *             Flash for a certain amount of time, potentially delaying execution
 *             of the time-critical radio interrupt service routine. Thus, it is checked
 *             that enough time is present before the next scheduled radio activity
 *             will start. If there is no enough time, this operation is scheduled. A
 *             cache is used to temporarily store the operation.
 *
 * @param[in,out] handle_p Handle pointing to the record to be deleted.
 * @retval     Indicates if the function executed successfully.
 */
NVMDB_status_t NVMDB_DeleteRecord(const NVMDB_HandleType *handle_p)
{
#if NVM_CACHE

  NVMDB_status_t status;

  if(DBInfo[handle_p->id].locked)
  {
    return NVMDB_STATUS_CACHE_OP_PENDING;
  }

  /* Try to delete the record, even if there are other operations in cache.
     In fact there is no reason to keep the order of this delete operation with
     respect to other delete or write operations. Instead it is important not to have
     clean operation pending, since the address of the record to be deleted would
     change.
   */
  if(handle_p->cache)  // Handle points to records in cache
  {
    CacheWriteOperationType write_op;
    memcpy(&write_op, &NVM_cache[handle_p->cache_index], sizeof(write_op));
    write_op.op = CACHE_NOP;
    memcpy(&NVM_cache[handle_p->cache_index], &write_op, sizeof(write_op));
    return NVMDB_STATUS_OK;
  }

  status = NVMDB_DeleteRecordNoCache(handle_p);

  if(status == NVMDB_STATUS_OK)
  {
    return NVMDB_STATUS_OK;
  }

  if(status != NVMDB_STATUS_NOT_ENOUGH_TIME)
  {
    return status;
  }

  /* No time to complete the operation immediately.  */
  return ScheduleDeleteOperation(handle_p->id, handle_p->address);

#else /* NVM_CACHE */

  return NVMDB_DeleteRecordNoCache(handle_p);

#endif
}

/**
 * @brief      Erase a database.
 *
 *             NVMDB_Erase removes all the records from the database, bringing it
 *             back to the original state when no records have been written.
 *
 * @note       An erase operation on the Flash prevents access to the
 *             Flash for a certain amount of time, potentially delaying execution
 *             of the time-critical radio interrupt service routine. Thus, it is checked
 *             that enough time is present before the next scheduled radio activity
 *             will start. If there is no enough time, this operation is scheduled. A
 *             cache is used to temporarily store the operation.
 *
 * @param      NVMDB_id The ID of the record to be erased.
 * @retval     Indicates if the function executed successfully.
 */
NVMDB_status_t NVMDB_Erase(NVMDB_IdType NVMDB_id)
{
  /* This function schedules a flash erase. Another possible implementation can
   * invalidate all the records of the database and let a clean operation erase the page.
   */
  const NVMDB_SmallDBContainerType *smallDBContainer_p;
  uint8_t type;
  NVMDB_status_t status;

#if NVM_CACHE
  if(DBInfo[NVMDB_id].locked)
  {
    return NVMDB_STATUS_CACHE_OP_PENDING;
  }
#endif

  type = GetDBType(NVMDB_id, &smallDBContainer_p);

  if(type == LARGE_DB)
  {
    uint8_t page_num_start, num_pages;
    uint32_t start_address = DBInfo[NVMDB_id].start_address;
    uint32_t end_address = DBInfo[NVMDB_id].end_address;

    page_num_start = (start_address - _MEMORY_FLASH_BEGIN_) / PAGE_SIZE;
    num_pages = (ROUNDPAGE_R(end_address) - start_address) / PAGE_SIZE;

#if NVM_CACHE

    RemoveCacheOp(NVMDB_id);

    if(EraseWithTimeCheck(&page_num_start, &num_pages) == NVMDB_STATUS_NOT_ENOUGH_TIME)
    {
      return SchedulePageEraseOperation(NVMDB_id, page_num_start, num_pages);
    }

#else

    NVMDB_FLASH_ERASE_PAGE(page_num_start, num_pages);

#endif

    NVMDB_get_info(&DBInfo[NVMDB_id]);

    return NVMDB_STATUS_OK;
  }

  if(type == SMALL_DB)
  {

    status = EraseSmallDB(NVMDB_id, smallDBContainer_p);

    if(status == NVMDB_STATUS_OK)
    {
      // Remove any operations in cache for all the DBs in the page. This means write and delete operations.
      // Cache operations for all the DBs in the same page have been executed by LoadDBToRAM().
      for(int i = 0; i < smallDBContainer_p->num_db; i++)
      {
        NVMDB_IdType id = smallDBContainer_p->dbs[i].id;
#if NVM_CACHE
        RemoveCacheOp(id);
#endif
        NVMDB_get_info(&DBInfo[id]);
      }
    }
    else if(status == NVMDB_STATUS_NOT_ENOUGH_TIME)
    {
#if NVM_CACHE
      return ScheduleSmallDBEraseOperation(NVMDB_id, smallDBContainer_p);
#endif
    }

    return status;
  }

  return NVMDB_STATUS_INVALID_ID;
}

/**
 * @brief      Clean the database.
 *
 *             It reads the entire database and writes back only valid records.
 *
 * @note       Erase and write operations on the Flash prevents access to the
 *             Flash for a certain amount of time, potentially delaying execution
 *             of the time-critical radio interrupt service routine. Thus, it is checked
 *             that enough time is present before the next scheduled radio activity
 *             will start. If there is no enough time to clean a small DB,
 *             NVMDB_STATUS_NOT_ENOUGH_TIME is returned. In this case the operation
 *             should be retried again later. In case a clean operation is requested
 *             for a large DB, NVMDB_STATUS_NOT_ENOUGH_TIME is returned only if there is
 *             no time to write the first Flash page. If there is time to write this
 *             page, the other write an erase operations are scheduled. Scheduled
 *             operations are temporarily stored in cache. While a clean operation
 *             is scheduled in cache, no other operations are allowed.
 *
 * @param      NVMDB_id The ID of the record to be cleaned.
 * @retval     Indicates if the function executed successfully.
 */
NVMDB_status_t NVMDB_CleanDB(NVMDB_IdType NVMDB_id)
{
  const NVMDB_SmallDBContainerType *smallDBContainer;
  uint8_t type;

  type = GetDBType(NVMDB_id, &smallDBContainer);
  if(type == LARGE_DB)
  {
    return CleanLargeDB(NVMDB_id);
  }
  if(type == SMALL_DB)
  {
    return CleanPage(smallDBContainer);
  }

  return NVMDB_STATUS_INVALID_ID;
}

/**
 * @brief      Function performing maintenance operations.
 *
 *             This function must be called periodically. Its main task is to
 *             perform scheduled operations.
 *
 * @retval     Returned values is NVMDB_STATUS_OK if no other operations are scheduled.
 *             The value NVMDB_STATUS_NOT_ENOUGH_TIME indicates that some operations
 *             cannot be performed because there is not enough time. Other values
 *             indicates unexpected conditions of the database.
 */
NVMDB_status_t NVMDB_Tick(void)
{
#if AUTO_CLEAN
  int8_t dirty_db_id;
#endif

#if NVM_CACHE

  NVMDB_status_t status;

  /* Check if there are operations in cache. */
#if PROCESS_CACHE_AT_ONCE
  while(!CACHE_EMPTY())
  {
#else
  if(!CACHE_EMPTY())
  {
#endif
    CacheOperationType cache_op;
    memcpy(&cache_op, &NVM_cache[cache_head], sizeof(cache_op));

    switch(cache_op.op)
    {

      case CACHE_WRITE_OP:
      {
        NVMDB_HandleType handle;
        CacheWriteOperationType write_op;
        memcpy(&write_op, &NVM_cache[cache_head], sizeof(write_op));
        NVMDB_HandleInit(write_op.id, &handle);
        status = NVMDB_AppendRecordNoCache(&handle, write_op.record_type, write_op.length - sizeof(write_op), NVM_cache + cache_head + sizeof(write_op), 0, NULL);
        PRINTF("Write operation from cache. Handle possibly not valid anymore!\r\n");
        if(status != NVMDB_STATUS_OK)
        {
          return status;
        }
      }
      break;
      case CACHE_DELETE_OP:
      {
        CacheDeleteOperationType del_op;
        memcpy(&del_op, &NVM_cache[cache_head], sizeof(del_op));

        status = InvalidateRecord(del_op.address);
        if(status == NVMDB_STATUS_OK)
        {
          DBInfo[del_op.id].valid_records--;
          DBInfo[del_op.id].invalid_records++;
        }
        else
        {
          return status;
        }
      }
      break;
      case CACHE_CLEAN_LARGE_DB_OP: /* A clean operation has started on a large multipage db. */
      {
        CacheCleanLargeOperationType clean_large_op;
        memcpy(&clean_large_op, &NVM_cache[cache_head], sizeof(clean_large_op));
        status = ContinueCleanLargeDB(&clean_large_op);
        if(status != NVMDB_STATUS_OK)
        {
          return status;
        }
      }
      break;
      case CACHE_PAGE_ERASE_OP:
      {
        CachePageEraseOperationType erase_op;
        memcpy(&erase_op, &NVM_cache[cache_head], sizeof(erase_op));
        status = EraseWithTimeCheck(&erase_op.page_num_start, &erase_op.num_pages);
        memcpy(&NVM_cache[cache_head], &erase_op, sizeof(erase_op));
        if(status == NVMDB_STATUS_OK)
        {
          NVMDB_get_info(&DBInfo[erase_op.id]);
        }
        else
        {
          return status;
        }
      }
      break;
      case CACHE_SMALL_DB_ERASE_OP:
      {
        CacheSmallDBEraseOperationType erase_op;
        memcpy(&erase_op, &NVM_cache[cache_head], sizeof(erase_op));
        status = EraseSmallDB(erase_op.id, erase_op.smallDBContainer_p); // This also removes lock
        if(status == NVMDB_STATUS_OK)
        {
          // Remove any operations in cache for all the DBs in the page. This means write and delete operations.
          // Cache operations for all the DBs in the same page have been executed by LoadDBToRAM().
          for(int i = 0; i < erase_op.smallDBContainer_p->num_db; i++)
          {
            NVMDB_IdType id = erase_op.smallDBContainer_p->dbs[i].id;
            // Except the DB that has been erased, otherwise it will remove also current cache operation.
            // cache operations for the erased DB has been removed by the ScheduleSmallDBEraseOperation.
            if(id != erase_op.id)
            {
              RemoveCacheOp(id);
            }
            NVMDB_get_info(&DBInfo[id]); // This also removes lock
          }
        }
        if(status != NVMDB_STATUS_OK)
        {
          return status;
        }
      }
      break;
//    case CACHE_NOP:
//      {
//        CacheNoOperationType nop;
//        memcpy(&nop, &NVM_cache[cache_head], sizeof(nop));
//      }
//      break;
      default:
        // Something wrong
        return NVMDB_STATUS_CACHE_ERROR;
    }
    CacheAdvanceHead(cache_op.length);
  }

#if !PROCESS_CACHE_AT_ONCE
  if(!CACHE_EMPTY())
  {
    return NVMDB_STATUS_CACHE_OP_PENDING;
  }
#endif

#endif /* NVM_CACHE */

#if AUTO_CLEAN
  dirty_db_id = NVMDB_CleanCheck();
  if(dirty_db_id >= 0)
  {
    NVMDB_CleanDB((NVMDB_IdType)dirty_db_id);
    PRINTF("Handle possibly not valid anymore!\r\n");
  }
#endif

  return NVMDB_STATUS_OK;
}

#if AUTO_CLEAN
// Checks if it is a good time to perform a clean operation
static int8_t NVMDB_CleanCheck(void)
{
  static int8_t db_start_index = 0;
  uint8_t i = db_start_index;

  do
  {
    if(DBInfo[i].invalid_records)
    {
      if(DBInfo[i].free_space < DBInfo[i].clean_threshold)
      {
        // Next time do not start from this db.
        // There may be time to clean another one if this one has not been successfully cleaned.
        db_start_index = i + 1;
        if(db_start_index == NUM_DB)
        {
          db_start_index = 0;
        }
        return i;
      }
    }

    i++;
    if(i == NUM_DB)
    {
      i = 0;
    }
  }
  while(i != db_start_index);

  // All databases have been checked. We can start from first position next time (but not strictly needed).
  db_start_index = 0;

  return -1; // No db to clean
}

#endif

/**
 * @}
 */

/**
 * @}
 */
