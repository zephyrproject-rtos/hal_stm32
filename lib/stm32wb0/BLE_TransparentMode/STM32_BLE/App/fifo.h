/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fifo.h
  * @author  VMA RF Application Team
  * @version V1.0.0
  * @date    July-2015
  * @brief
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
#ifndef __FIFO_H__
#define __FIFO_H__

typedef struct circular_fifo_s {
  uint16_t tail;
  uint16_t head;
  uint16_t max_size;
  uint8_t *buffer;
  uint8_t alignment;
} circular_fifo_t;

void fifo_init(circular_fifo_t *fifo, uint16_t max_size, uint8_t  *buffer, uint8_t alignment);
uint16_t fifo_size(circular_fifo_t *fifo);
uint8_t fifo_put(circular_fifo_t *fifo, uint16_t size, const uint8_t  *buffer);
uint8_t fifo_put_var_len_item(circular_fifo_t *fifo, uint16_t size1, const uint8_t  *buffer1, uint16_t size2, const uint8_t  *buffer2);
uint8_t fifo_get(circular_fifo_t *fifo, uint16_t size, uint8_t  *buffer);
uint8_t fifo_discard(circular_fifo_t *fifo, uint16_t size);
uint8_t fifo_get_ptr(circular_fifo_t *fifo, uint16_t size, uint8_t **ptr);
uint8_t fifo_get_var_len_item(circular_fifo_t *fifo, uint16_t *size, uint8_t  *buffer);
uint8_t fifo_get_ptr_var_len_item(circular_fifo_t *fifo, uint16_t *size, uint8_t  **ptr);
uint8_t fifo_discard_var_len_item(circular_fifo_t *fifo);
void fifo_flush(circular_fifo_t *fifo);
void fifo_roll_back(circular_fifo_t *fifo, uint16_t size);
#endif /* __FIFO_H__ */
