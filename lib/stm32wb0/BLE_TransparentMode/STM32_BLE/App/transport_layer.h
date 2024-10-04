/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    transport_layer.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TRANSPORT_LAYER_H
#define TRANSPORT_LAYER_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "crash_handler.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define BLUE_FLAG_RAM_RESET             0x01010101

#define DMA_IDLE        0
#define DMA_IN_PROGRESS 1

#define DMA_RX_BUFFER_SIZE 64

typedef enum {
  SPI_PROT_INIT_STATE = 0,                  /* Initialization phase         */
  SPI_PROT_CONFIGURED_STATE,                /* Configuration phase          */
  SPI_PROT_SLEEP_STATE,                     /* Sleep phase                  */
  SPI_PROT_CONFIGURED_HOST_REQ_STATE,       /* Host request phase           */
  SPI_PROT_CONFIGURED_EVENT_PEND_STATE,     /* Event pending phase          */
  SPI_PROT_WAITING_HEADER_STATE,            /* Waiting header phase         */
  SPI_PROT_HEADER_RECEIVED_STATE,           /* Header received phase        */
  SPI_PROT_WAITING_DATA_STATE,              /* Waiting data phase           */
  SPI_PROT_TRANS_COMPLETE_STATE,            /* Transaction complete phase   */
} SpiProtoType;

extern SpiProtoType spi_proto_state;

#ifdef DEBUG_DTM
typedef enum {
  EMPTY = 0,                  /* Initialization phase         */
  GPIO_IRQ = 1000,                  /* Initialization phase         */
  GPIO_CS_FALLING,                /* Configuration phase          */
  GPIO_CS_RISING,           /* Event pending phase          */
  PARSE_HOST_REQ,             /* Host request phase           */
  PARSE_EVENT_PEND,                     /* Sleep phase                  */
  ADVANCE_DMA_WRITE,            /* Waiting header phase         */
  ADVANCE_DMA_READ,           /* Header received phase        */
  ADVANCE_DMA_EVENT_PEND,              /* Waiting data phase           */
  ADVANCE_DMA_RESTORE_0,
  ADVANCE_DMA_RESTORE_1,
  ADVANCE_DMA_RESTORE,
  RESTORE_SAVE,
  ADVANCE_DMA_DISCARD,
  ENQUEUE_EVENT,
  SEND_DATA,
  RECEIVE_DATA,
  BTLE_STACK_TICK_ON,
  BTLE_STACK_TICK_OFF,
  HEADER_RECEIVED,
  HEADER_NOT_RECEIVED,
  ENTER_SLEEP_FUNC,
  EXIT_SLEEP_FUNC,
  COMMAND_PROCESSED,
  CPU_HALT0,
  CPU_HALT1,
  CPU_HALT2,
  CPU_RUNNING0,
  CPU_RUNNING1,
  DEEP_SLEEP0,
  DEEP_SLEEP1,
  SPI_PROT_TRANS_COMPLETE,
  SPI_PROT_WAITING_DATA,
  EDGE_SENSITIVE,
  SLEEP_CHECK_PERFORMED,
  DISABLE_IRQ0,
  DISABLE_IRQ1,
  DMA_REARM,
  DMA_TC,
  IRQ_FALL,
  IRQ_RISE,
  TXFIFO_NE,
  SPI_PROT_INIT_STATE_ANN,                      /* Initialization phase         */
  SPI_PROT_CONFIGURED_STATE_ANN,                /* Configuration phase          */
  SPI_PROT_SLEEP_STATE_ANN,                     /* Sleep phase                  */
  SPI_PROT_CONFIGURED_HOST_REQ_STATE_ANN,       /* Host request phase           */
  SPI_PROT_CONFIGURED_EVENT_PEND_STATE_ANN,     /* Event pending phase          */
  SPI_PROT_WAITING_HEADER_STATE_ANN,            /* Waiting header phase         */
  SPI_PROT_HEADER_RECEIVED_STATE_ANN,           /* Header received phase        */
  SPI_PROT_WAITING_DATA_STATE_ANN,              /* Waiting data phase           */
  SPI_PROT_TRANS_COMPLETE_STATE_ANN,            /* Transaction complete phase   */
} DebugLabel;

#define DEBUG_ARRAY_LEN 1000
extern DebugLabel debug_buf[DEBUG_ARRAY_LEN];
extern uint32_t debug_cnt;
#define DEBUG_NOTES(NOTE)       do{\
                                  debug_buf[debug_cnt] = NOTE; debug_cnt = (debug_cnt+1)%DEBUG_ARRAY_LEN;\
                                 }while(0)

#define SPI_STATE_TRANSACTION(NEWSTATE)        do{                             \
                                                  spi_proto_state = NEWSTATE;  \
                                                  DEBUG_NOTES(NEWSTATE ## _ANN); \
                                                  LL_GPIO_SetOutputPin(DEBUG_GPIO_PORT, DEBUG_TEST_1_PIN); __NOP;\
                                                  LL_GPIO_ResetOutputPin(DEBUG_GPIO_PORT, DEBUG_TEST_1_PIN);\
                                               }while(0)

#else

#define DEBUG_NOTES(NOTE)

#define SPI_STATE_TRANSACTION(NEWSTATE)        (spi_proto_state = NEWSTATE)

#endif

#define SPI_STATE_CHECK(STATE)                (spi_proto_state==STATE)
#define SPI_STATE_FROM(STATE)                 (spi_proto_state>=STATE)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern void transport_layer_init(void);
extern void transport_layer_tick (void);
extern void command_received(uint8_t *cmd, uint16_t len);
extern void send_event(const uint8_t *buffer_out, uint16_t buffer_out_length, int8_t overflow_index);
extern void send_event_2buffers(const uint8_t *buffer_out1, uint16_t buffer_out_length1, const uint8_t *buffer_out2, uint16_t buffer_out_length2, int8_t overflow_index);
extern void advance_dma(void);
/* The transport layer request to process a command or event in the queue. */
void TL_ProcessReqCallback(void);
/* A request to reset the devie has been received. */
void TL_ResetReqCallback(void);

#endif /* TRANSPORT_LAYER_H */
