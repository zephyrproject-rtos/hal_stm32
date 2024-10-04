/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adv_buff_alloc.c
  * @author  AMS - RF Application team
  * @brief   Module providing buffer allocation for advertising data.
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
#include <stdint.h>
#include <stdlib.h>
#include "ble.h"
#include "pawr_buff_alloc.h"

#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)

static uint8_t pawr_subevent_buf[CFG_BLE_PAWR_SUBEVENT_DATA_COUNT_MAX][MAX_PAWR_SUBEVENT_DATA_SIZE];

static uint8_t pawr_resp_buff[MAX_PAWR_RESPONSE_SUBEVENT_COUNT][MAX_PAWR_SUBEVENT_DATA_SIZE];

#if CFG_BLE_PAWR_SUBEVENT_DATA_COUNT_MAX < 33
/* Variable used to keep which buffer is used and which one is not in use by the link layer.
   Up to 32 buffers can be handled.  */
static uint32_t used_subevent_buff_msk;

#elif CFG_BLE_PAWR_SUBEVENT_DATA_COUNT_MAX < 65

static uint64_t used_subevent_buff_msk;

#else

#error "This implementation does not allow to handle more than 64 buffers for subevents."

#endif

#if MAX_PAWR_RESPONSE_SUBEVENT_COUNT < 9
/* Variable used to keep which buffer is used and which one is not in use by the link layer.
   Up to 32 buffers can be handled.  */
static uint8_t used_resp_buff_msk;

#else

#error "This implementation does not allow to handle more than 8 buffers for pawr responses."

#endif

#define BUFFER_IN_USE(mask, i)        (mask & (1<<i))
#define SET_BUFFER_IN_USE(mask, i)    (mask |= (1<<i))
#define CLEAR_BUFFER_IN_USE(mask, i)  (mask &= ~(1<<i))

/**
* @brief  Initialize the module for buffer allocation. Mandatory before any use of the module.
* @retval None
*/
void pawr_buff_init(void)
{
  used_subevent_buff_msk = 0;
  used_resp_buff_msk = 0;
}

static void subevent_buff_free(void *p)
{
  for(int i = 0; i < CFG_BLE_PAWR_SUBEVENT_DATA_COUNT_MAX; i++)
    {
      if(p == pawr_subevent_buf[i])
      {
        CLEAR_BUFFER_IN_USE(used_subevent_buff_msk, i);
        return;
      }
    }
}

static void response_buff_free(void *p)
{
  for(int i = 0; i < MAX_PAWR_RESPONSE_SUBEVENT_COUNT; i++)
  {
    if(p == pawr_resp_buff[i])
    {
      CLEAR_BUFFER_IN_USE(used_resp_buff_msk, i);
      return;
    }
  }
}

/**
* @brief  Mark a buffer as free.
* @param  p Pointer to the buffer
* @param  t Type of buffer between subevent data and response data
* @retval None
*/
void pawr_buff_free(void * p, uint8_t t)
{
  switch (t)
  {
  case HAL_PAWR_DATA_TYPE_SUBEVENT:
    // p is a buffer for PAwR subevents
    subevent_buff_free(p);
    break;
  case HAL_PAWR_DATA_TYPE_RESPONSE:
    // p is a buffer for PAwR responses
    response_buff_free(p);
    break;
  default:
    break;
  }
}

/**
* @brief  Allocate a buffer of MAX_PAWR_SUBEVENT_DATA_SIZE bytes for PaWR subevents.
* @retval It returns the pointer to the buffer.
*/
void * pawr_buff_subevent_alloc(void)
{
  uint8_t i;

  for(i = 0; i < CFG_BLE_PAWR_SUBEVENT_DATA_COUNT_MAX && BUFFER_IN_USE(used_subevent_buff_msk, i) ; i++);

  if(i == CFG_BLE_PAWR_SUBEVENT_DATA_COUNT_MAX)
  {
    // No free buffer found.
    return NULL;
  }

  SET_BUFFER_IN_USE(used_subevent_buff_msk, i);

  return pawr_subevent_buf[i];
}

/**
* @brief  Allocate a buffer of MAX_PAWR_RESPONSE_DATA_SIZE bytes for PaWR response data.
* @retval It returns the pointer to the buffer.
*/
void * pawr_buff_resp_alloc(void)
{
  uint8_t i;

  for(i = 0; i < MAX_PAWR_RESPONSE_SUBEVENT_COUNT && BUFFER_IN_USE(used_resp_buff_msk, i) ; i++);

  if(i == MAX_PAWR_RESPONSE_SUBEVENT_COUNT)
  {
    // No free buffer found.
    return NULL;
  }

  SET_BUFFER_IN_USE(used_resp_buff_msk, i);

  return pawr_resp_buff[i];
}

uint8_t pawr_buff_subevent_num_available(void)
{
  uint8_t i;
  uint8_t available_buff = 0;

  for(i = 0; i < CFG_BLE_PAWR_SUBEVENT_DATA_COUNT_MAX; i++)
  {
    if(!BUFFER_IN_USE(used_subevent_buff_msk, i))
    {
      available_buff++;
    }
  }

  return available_buff;
}

#endif /* CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1 */

