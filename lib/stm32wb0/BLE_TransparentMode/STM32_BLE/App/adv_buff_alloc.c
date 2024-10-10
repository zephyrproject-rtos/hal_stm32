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
#include "app_common.h"
#include "adv_buff_alloc.h"
#include "dm_alloc.h"

#define NUM_ADV_BUFF_TYPES  3

/* Bidimensional array. First dimension for the differetn types of data:
 * advertising data, scan response data, periodic advertsing data. */
struct adv_set_info_s{
  uint8_t  handle;
  uint8_t *old_buff_data;
  uint8_t *curr_buff_data;
  uint8_t *next_buff_data;
  uint16_t next_buff_len;
}adv_buf_info[NUM_ADV_BUFF_TYPES][CFG_BLE_NUM_ADV_SETS];

/**
* @brief  Initialize the module for buffer allocation. Mandatory before any use of the module.
* @retval None
*/
void adv_buff_init(void)
{
  uint8_t i, j;

  for(i = 0; i < NUM_ADV_BUFF_TYPES; i++)
    for(j = 0; j < CFG_BLE_NUM_ADV_SETS; j++)
    adv_buf_info[i][j].handle = 0xFF;
}

/**
* @brief  Retrieve buffer info
* @param  handle Advertising handle
* @param  data_type Type of advertising data (see @ref ADV_DATA_TYPES)
* @retval It returns the pointer to the buffer info structure
*/
static struct adv_set_info_s *search_handle(uint8_t handle, uint8_t data_type)
{
  int i;

  /* Just a check, but this should not happen. */
  if(data_type >= NUM_ADV_BUFF_TYPES)
    return NULL;

  for(i = 0; i < CFG_BLE_NUM_ADV_SETS; i++){
    if(adv_buf_info[data_type][i].handle == handle)
      return &adv_buf_info[data_type][i];
  }
  return NULL;
}

/**
* @brief  Check if a new buffer is allocated with data not yet passed to the stack (i.e. buffer not yet activated).
* @param  handle Advertising handle
* @param  data_type Type of advertising data (see @ref ADV_DATA_TYPES)
* @retval It returns TRUE if there is a new buffer to be activated.
*/
uint8_t new_buff_pending(uint8_t handle, uint8_t data_type)
{
  struct adv_set_info_s *info;

  info = search_handle(handle, data_type);

  if(info == NULL || info->next_buff_data == NULL){
    return FALSE;
  }
  else {
    return TRUE;
  }

}

/**
* @brief  It allocates a buffer for advertising or scan response data.
* @param  handle Advertising handle
* @param  buffer_len New length to be allocated
* @param  extend If 0, it allocates a new buffer for the given advertising set, after having been
*                freed any previously allocated buffer.
*                If 1, increase the size of the current block allocated for the advertising set, possibly
*                allocating a new block different from the previous one (in this case with a different address).
* @param[out] old_buff_len Size of the old buffer in case of an extension, otherwise 0.
* @param  data_type Type of advertising data (see @ref ADV_DATA_TYPES)
* @retval It returns the pointer to the entire buffer.
*/
uint8_t *adv_buff_alloc(uint8_t handle, uint16_t buffer_len, uint8_t extend, uint16_t *old_buff_len, uint8_t data_type)
{
  struct adv_set_info_s *info;

  *old_buff_len = 0;

  info = search_handle(handle, data_type);
  if(info == NULL){
    // No existing handle found. Search free locations.
    info = search_handle(0xFF, data_type);
    if(info){
      info->handle = handle;
      info->old_buff_data = NULL;
      info->curr_buff_data = NULL;
      info->next_buff_data = NULL;
      info->next_buff_len = 0;
    }
    else {
      // No free locations
      return NULL;
    }
  }

  if(!extend){ // New allocation

    if(info->old_buff_data) // A buffer which still need to be freed. Do not allow new allocations.
      return NULL;

    if(info->next_buff_data) // A buffer has been previously allocated
      dm_free(info->next_buff_data);

    if(buffer_len)
      info->next_buff_data = dm_alloc(buffer_len);
    else
      info->next_buff_data = NULL;
    if(info->next_buff_data)
      info->next_buff_len = buffer_len;
    else
      info->next_buff_len = 0;
  }
  else { // Reallocation
    uint8_t *buffer;
    if(!info->next_buff_data) // No buffer previously allocated
      return NULL;
    buffer = dm_realloc(info->next_buff_data, info->next_buff_len + buffer_len);
    if(buffer){
      info->next_buff_data = buffer;
      *old_buff_len = info->next_buff_len;
      info->next_buff_len += buffer_len;
    }
    else {
      dm_free(info->next_buff_data);
      info->next_buff_data = 0;
      info->next_buff_len = 0;
    }
  }
  return info->next_buff_data;
}

/**
* @brief  Free the buffer that is currently active.
* @param  handle Advertising handle
* @param  data_type Type of advertising data (see @ref ADV_DATA_TYPES)
* @retval None
*/
void adv_buff_free_current(uint8_t handle, uint8_t data_type)
{
  struct adv_set_info_s *info;

  info = search_handle(handle, data_type);
  if(info == NULL)
    return;

  dm_free(info->curr_buff_data);
  info->curr_buff_data = NULL;
}

/**
* @brief  Free the buffer that is allocated to hold next data
* @param  handle Advertising handle
* @param  data_type Type of advertising data (see @ref ADV_DATA_TYPES)
* @retval None
*/
void adv_buff_free_next(uint8_t handle, uint8_t data_type)
{
  struct adv_set_info_s *info;

  info = search_handle(handle, data_type);
  if(info == NULL)
    return;

  dm_free(info->next_buff_data);
  info->next_buff_data = NULL;
  info->next_buff_len = 0;
}

/**
* @brief  Free the old buffer, which was waiting to be abandoned by the stack
* @param  buff Pointer to the buffer
* @retval None
*/
void adv_buff_free_old(uint8_t *buff)
{
  uint8_t i, j;

  if(buff == NULL)
    return;

  for(j = 0; j < NUM_ADV_BUFF_TYPES; j++){

    for(i = 0; i < CFG_BLE_NUM_ADV_SETS; i++){
      if(adv_buf_info[j][i].old_buff_data == buff){
        dm_free(buff);
        adv_buf_info[j][i].old_buff_data = NULL;
        return;
      }
      /* Check also if it has been requested to free the current buffer.
         This may happen if the advertising set is removed. */
      if(adv_buf_info[j][i].curr_buff_data == buff){
        /* Free buffers and remove info about this handle, since advertising set
           has been removed */
        dm_free(adv_buf_info[j][i].curr_buff_data);
        adv_buf_info[j][i].curr_buff_data = NULL;
        //dm_free(adv_buf_info[i].old_buff_data); This line should not be needed.
        adv_buf_info[j][i].handle = 0xFF;
        return;
      }
    }

  }
}

/**
* @brief  Function to be called when the new allocated buffer is successfully passed
*         to the stack to be the new buffer. The new allocated buffer is now
*         considered as the current buffer in use by the stack. If needed, call
*         adv_buff_deactivate_current() before calling this function.
* @param  handle Advertising handle
* @param  data_type Type of advertising data (see @ref ADV_DATA_TYPES)
* @retval None
*/
void adv_buff_activate_next(uint8_t handle, uint8_t data_type)
{
  struct adv_set_info_s *info;

  info = search_handle(handle, data_type);
  if(info == NULL)
    return;

  info->curr_buff_data = info->next_buff_data;
  info->next_buff_data = NULL;
  info->next_buff_len = 0;
}

/**
* @brief  Function to be called after having been informed the stack that the current
          buffer does not have to be used anymore.
* @param  handle Advertising handle
* @param  data_type Type of advertising data (see @ref ADV_DATA_TYPES)
* @retval None
*/
void adv_buff_deactivate_current(uint8_t handle, uint8_t data_type)
{
  struct adv_set_info_s *info;

  info = search_handle(handle, data_type);
  if(info == NULL)
    return;

  info->old_buff_data = info->curr_buff_data; // What is in old_buff_data has to be freed.
  info->curr_buff_data = NULL;
}

