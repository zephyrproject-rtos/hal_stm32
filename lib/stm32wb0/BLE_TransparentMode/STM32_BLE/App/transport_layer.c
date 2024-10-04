/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file    tramsport_layer.c
* @author  GPM WBL Application Team
* @brief   Transport layer file
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
#include "stm32wb0x.h"
#include "fifo.h"
#include "compiler.h"
#include "transport_layer.h"
#include "dtm_cmd_db.h"
#include "stm32wb0x_ll_usart.h"
#include "stm32wb0x_hal_dma.h"
#include "stm32wb0x_hal_uart.h"
#include "hci_parser.h"
#include "dtm_preprocess_events.h"
#include "app_common.h"

/* Private typedef -----------------------------------------------------------*/\

typedef PACKED(struct) event_lost_register_s {
  uint8_t event_lost;
  uint8_t event_register[5];
  uint64_t event_lost_code;
} event_lost_register_t;

/* Private define ------------------------------------------------------------*/

#define MAX_EVENT_SIZE  (536)

#if defined(STM32WB07) || defined(STM32WB06) || defined(STM32WB09)
#define COMMAND_BUFFER_SIZE  (536 + 4)
#define EVENT_BUFFER_SIZE    2300
#elif defined(STM32WB05)
#define COMMAND_BUFFER_SIZE  265        /* Decrease buffer size for reducing RAM footprint */
#define EVENT_BUFFER_SIZE    1024
#endif

#define FIFO_ALIGNMENT       4
#define FIFO_VAR_LEN_ITEM_MAX_SIZE (MAX_EVENT_SIZE)

#define DMA_CH_UART_TX          LL_DMA_CHANNEL_1
#define DMA_CH_UART_RX          LL_DMA_CHANNEL_2

#define HCI_RESET_OPCODE        0x0C03

#define LEGACY_ADV_OPCODE_LOW  0x2006 // Lowest opcode for legacy advertising commands
#define LEGACY_ADV_OPCODE_HIGH 0x200D // Highest opcode for legacy advertising commands

#define EXTENDED_ADV_OPCODE_LOW  0x2036 // Lowest opcode for extended advertising commands
#define EXTENDED_ADV_OPCODE_HIGH 0x204A // Highest opcode for extended advertising commands

// Opcodes of commands that returns command status instead of command complete events
#define HCI_LE_CREATE_CONNECTION_OPCODE                 0x200D
#define HCI_LE_EXTENDED_CREATE_CONNECTION_OPCODE        0x2043
#define HCI_LE_PERIODIC_ADVERTISING_CREATE_SYNC_OPCODE  0x2044

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifndef __ZEPHYR__
ALIGN(2) static uint8_t event_buffer[EVENT_BUFFER_SIZE + FIFO_VAR_LEN_ITEM_MAX_SIZE];
static uint8_t command_buffer[COMMAND_BUFFER_SIZE];
static circular_fifo_t event_fifo, command_fifo;
static uint8_t DMA_RX_Buffer[DMA_RX_BUFFER_SIZE];

static event_lost_register_t event_lost_register;
static uint8_t dma_state = DMA_IDLE;

#ifdef DEBUG_DTM
DebugLabel debug_buf[DEBUG_ARRAY_LEN] = {EMPTY,};
uint32_t debug_cnt = 0;
#endif

/* External variables --------------------------------------------------------*/

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef handle_DMA_Channel2;

/* Private function prototypes -----------------------------------------------*/

static void enqueue_event(circular_fifo_t *fifo, uint16_t buff_len1, const uint8_t *buff_evt1, uint16_t buff_len2, const uint8_t *buff_evt2, int8_t overflow_index);

/* Private functions ---------------------------------------------------------*/

/* "If, since the last power-on or reset, the Host has ever issued a legacy
  advertising command and then issues an extended advertising command, or
  has ever issued an extended advertising command and then issues a legacy
  advertising command, the Controller shall return the error code Command
  Disallowed (0x0C)."
  This function returns 1 if an error has to be given. */
static uint8_t check_legacy_extended_call(uint16_t opcode, uint8_t *buffer_out)
{
  static uint8_t legacy_cmd_issued = FALSE, extended_cmd_issued =  FALSE;
  uint8_t allowed = TRUE;

  if(opcode >= LEGACY_ADV_OPCODE_LOW && opcode <= LEGACY_ADV_OPCODE_HIGH){
    if(extended_cmd_issued)
      allowed = FALSE; // Error
    else {
      legacy_cmd_issued = TRUE;
      allowed = TRUE; // OK
    }
  }
  else if(opcode >= EXTENDED_ADV_OPCODE_LOW && opcode <= EXTENDED_ADV_OPCODE_HIGH){
    if(legacy_cmd_issued)
      allowed = FALSE; // Error
    else {
      extended_cmd_issued = TRUE;
      allowed = TRUE; // OK
    }
  }

  if(!allowed){
    if(opcode == HCI_LE_CREATE_CONNECTION_OPCODE ||
       opcode == HCI_LE_EXTENDED_CREATE_CONNECTION_OPCODE||
       opcode == HCI_LE_PERIODIC_ADVERTISING_CREATE_SYNC_OPCODE){
      buffer_out[0] = 0x04;
      buffer_out[1] = 0x0F;
      buffer_out[2] = 0x04;
      buffer_out[3] = 0x0C;
      buffer_out[4] = 0x01;
      HOST_TO_LE_16(buffer_out+5,opcode);
      return 7;
    }
    else {
      buffer_out[0] = 0x04;
      buffer_out[1] = 0x0E;
      buffer_out[2] = 0x04;
      buffer_out[3] = 0x01;
      HOST_TO_LE_16(buffer_out+4,opcode);
      buffer_out[6] = 0x0C;
      return 7;
    }
  }

  return 0;
}

/* Process Commands */
uint16_t process_command(uint16_t op_code, uint8_t *buffer_in, uint16_t buffer_in_length, uint8_t *buffer_out, uint16_t buffer_out_max_length)
{
  uint32_t i;
  uint16_t ret_val;

  ret_val = check_legacy_extended_call(op_code, buffer_out);
  if(ret_val != 0){
    return ret_val;
  }

  for (i = 0; hci_command_table[i].opcode != 0; i++) {
    if (op_code == hci_command_table[i].opcode) {
      ret_val = hci_command_table[i].execute(buffer_in, buffer_in_length, buffer_out, buffer_out_max_length);
      /* add get crash handler */
      return ret_val;
    }
  }

  // Unknown command length
  buffer_out[0] = 0x04;
  buffer_out[1] = 0x0F;
  buffer_out[2] = 0x04;
  buffer_out[3] = 0x01;
  buffer_out[4] = 0x01;
  HOST_TO_LE_16(buffer_out+5, op_code);
  return 7;
}

/**
* @brief  Transport Layer Init.
*	  Init the transport layer.
* @param  None
* @retval None
*/
void transport_layer_init(void)
{
  /* Queue index init */
  fifo_init(&event_fifo, EVENT_BUFFER_SIZE, event_buffer, FIFO_ALIGNMENT);
  fifo_init(&command_fifo, COMMAND_BUFFER_SIZE, command_buffer, FIFO_ALIGNMENT);

  /* event_lost_register init */
  event_lost_register.event_lost = 0;
  event_lost_register.event_register[0] = 0x04;
  event_lost_register.event_register[1] = 0xFF;
  event_lost_register.event_register[2] = 0x0A;
  event_lost_register.event_register[3] = 0x02;
  event_lost_register.event_register[4] = 0x00;
  event_lost_register.event_lost_code = 0;

  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, DMA_RX_Buffer, DMA_RX_BUFFER_SIZE);
}

static void transport_layer_send_data(uint8_t *data, uint16_t data_length)
{
  if (dma_state == DMA_IDLE) {
    dma_state = DMA_IN_PROGRESS;
    DEBUG_NOTES(DMA_REARM);
    HAL_UART_Transmit_DMA(&huart1, data, data_length);
  }
}

static void transport_layer_DMA_RX_Data(uint16_t dma_counter)
{
  static uint16_t rx_index = 0;

  if(rx_index != dma_counter)
  {
    if(dma_counter > rx_index)
    {
      hci_input(&DMA_RX_Buffer[rx_index], dma_counter - rx_index);
    }
    else
    {
      hci_input(&DMA_RX_Buffer[rx_index], DMA_RX_BUFFER_SIZE - rx_index);
      if(dma_counter != 0)
      {
        hci_input(&DMA_RX_Buffer[0], dma_counter);
      }
    }
    rx_index = dma_counter;
    if(rx_index == DMA_RX_BUFFER_SIZE)
    {
      rx_index = 0;
    }
  }
}

/**
* @brief  Advance transport layer state machine
* @param  None
* @retval Desired sleep level
*/
void transport_layer_tick(void)
{
  uint8_t buffer[COMMAND_BUFFER_SIZE], buffer_out[FIFO_VAR_LEN_ITEM_MAX_SIZE];
  uint16_t len;
  uint16_t size = 0;

  /* Event queue */
  if ((fifo_size(&event_fifo) > 0) && (dma_state == DMA_IDLE)) {
    uint8_t *ptr;
    DEBUG_NOTES(SEND_DATA);
    if (fifo_get_ptr_var_len_item(&event_fifo, &size, &ptr) == 0) {
      transport_layer_send_data(ptr+FIFO_ALIGNMENT, size);
    }
  }

  /* Command FIFO */
  if (fifo_size(&command_fifo) > 0) {
    uint16_t opcode;
    uint8_t offset;

    fifo_get_var_len_item(&command_fifo, &size, buffer);
    /*  */
    if(buffer[0] == HCI_COMMAND_PKT){
      hci_cmd_hdr *hdr = (hci_cmd_hdr *)buffer;
      opcode = hdr->opcode;
      offset = sizeof(hci_cmd_hdr);
    }
    else if(buffer[0] == HCI_COMMAND_EXT_PKT){
      hci_cmd_ext_hdr *hdr = (hci_cmd_ext_hdr *)buffer;
      opcode = hdr->opcode;
      offset = sizeof(hci_cmd_ext_hdr);
    }
    else {
      /* Unknown packet type */
      fifo_flush(&command_fifo);
      return;
    }

    if(opcode == HCI_RESET_OPCODE)
    {
      while(dma_state == DMA_IN_PROGRESS);
      while(LL_USART_IsActiveFlag_TXE_TXFNF(USART1) == RESET);
      while(LL_USART_IsActiveFlag_TC(USART1) == RESET);
      TL_ResetReqCallback();
    }

    len=process_command(opcode, buffer+offset, size-offset, buffer_out, sizeof(buffer_out));

#if (BUFFER_CMDS_ON_BUSY == 1)
    uint8_t status_offset = (buffer_out[1] == 0x0E) ? 6 : 3; /* 0x0E: command complete, 0x0F: command status */
    /* Apply command buffering in case of CONTROLLER BUSY error with the exception of the
     * aci_l2cap_connection_parameter_update_resp command (see  req_pbs #990070)
     */
    if ((*(buffer_out+status_offset) != BLE_ERROR_CONTROLLER_BUSY) || (opcode == 0xfd82))
    {
      DEBUG_NOTES(COMMAND_PROCESSED);
      /* Set user events back to normal queue */
      send_event(buffer_out, len, 1);
      fifo_flush(&command_fifo);
    }
    else
    {
      fifo_roll_back(&command_fifo, size);
    }
#else
    DEBUG_NOTES(COMMAND_PROCESSED);
    /* Set user events back to normal queue */
    send_event(buffer_out, len, 1);
    fifo_flush(&command_fifo);
#endif
  }

  if(event_lost_register.event_lost==1) {
    if (fifo_put_var_len_item(&event_fifo, 13, event_lost_register.event_register,0,NULL) == 0) {
      event_lost_register.event_lost = 0;
      event_lost_register.event_lost_code = 0;
    }
  }
}

void command_received(uint8_t *cmd, uint16_t len)
{
  fifo_put_var_len_item(&command_fifo, len, cmd, 0, NULL);
  TL_ProcessReqCallback();
}

void enqueue_event(circular_fifo_t *fifo, uint16_t buff_len1, const uint8_t *buff_evt1, uint16_t buff_len2, const uint8_t *buff_evt2, int8_t overflow_index)
{
  if (fifo_put_var_len_item(fifo, buff_len1, buff_evt1, buff_len2, buff_evt2) != 0) {
    /* Event queue overflow */
    if ((overflow_index >=0) && (overflow_index < 64)) {
      event_lost_register.event_lost = 1;
      event_lost_register.event_lost_code |= (1 << overflow_index);
    } else {
      /* assert */
    }
  }
  TL_ProcessReqCallback();
}

void send_event(const uint8_t *buffer_out, uint16_t buffer_out_length, int8_t overflow_index)
{
  if(buffer_out_length != 0) {
    DEBUG_NOTES(ENQUEUE_EVENT);
    enqueue_event(&event_fifo, buffer_out_length, buffer_out, 0, NULL, overflow_index);
  }
}

void send_event_2buffers(const uint8_t *buffer_out1, uint16_t buffer_out_length1, const  uint8_t *buffer_out2, uint16_t buffer_out_length2, int8_t overflow_index)
{
  if(buffer_out_length1 != 0) {
    DEBUG_NOTES(ENQUEUE_EVENT);
    enqueue_event(&event_fifo, buffer_out_length1, buffer_out1, buffer_out_length2, buffer_out2, overflow_index);
  }
}

void advance_dma(void)
{
  uint8_t *ptr;
  uint16_t size;
  fifo_discard_var_len_item(&event_fifo);

  if (fifo_size(&event_fifo) > 0) {
    if (fifo_get_ptr_var_len_item(&event_fifo, &size, &ptr) == 0) {
      transport_layer_send_data(ptr+FIFO_ALIGNMENT, size);
    }
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  /* DMA1 finished the transfer of SrcBuffer */
  dma_state = DMA_IDLE;

  DEBUG_NOTES(DMA_TC);

  advance_dma();
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  transport_layer_DMA_RX_Data(Size);
}

__weak void TL_ProcessReqCallback(void){}

__weak void TL_ResetReqCallback(void){}

#endif /* __ZEPHYR__ */

void BLE_STACK_Event(hci_pckt *hci_pckt, uint16_t length)
{
  uint16_t i;
  int ret = 0;

  if(hci_pckt->type == HCI_EVENT_PKT)
  {
    hci_event_pckt *event_pckt = (hci_event_pckt*)hci_pckt->data;

    if(event_pckt->evt == EVT_LE_META_EVENT)
    {
      evt_le_meta_event *evt = (evt_le_meta_event *)event_pckt->data;

      for (i = 0; hci_le_meta_events_table[i].evt_code != 0; i++)
      {
        if (evt->subevent == hci_le_meta_events_table[i].evt_code)
        {
          ret = hci_le_meta_events_table[i].process((void *)evt->data);
          goto send_event;
        }
      }
    }
    else if(event_pckt->evt != HCI_VENDOR_PKT)
    {
      for (i = 0; hci_events_table[i].evt_code != 0; i++)
      {
        if (event_pckt->evt == hci_events_table[i].evt_code)
        {
          ret = hci_events_table[i].process(event_pckt->data);
          goto send_event;
        }
      }
    }
  }
  if(hci_pckt->type == HCI_EVENT_PKT || hci_pckt->type == HCI_EVENT_EXT_PKT)
  {
    uint8_t   evt_code;
    uint8_t  *evt_payload;

    if(hci_pckt->type == HCI_EVENT_PKT)
    {
      hci_event_pckt *event_pckt = (hci_event_pckt*)hci_pckt->data;
      evt_code = event_pckt->evt;
      evt_payload = event_pckt->data;
    }
    else
    {
      hci_event_ext_pckt *event_pckt = (hci_event_ext_pckt*)hci_pckt->data;
      evt_code = event_pckt->evt;
      evt_payload = event_pckt->data;
    }

    if(evt_code == HCI_VENDOR_PKT)
    {
      evt_blue_aci *blue_evt = (evt_blue_aci *)evt_payload;

      for (i = 0; hci_vendor_specific_events_table[i].evt_code != 0; i++)
      {
        if (blue_evt->ecode == hci_vendor_specific_events_table[i].evt_code)
        {
          ret = hci_vendor_specific_events_table[i].process((void *)blue_evt->data);
          break;
        }
      }
    }
  }

send_event:

  if(ret == 0)
  {
    send_event((uint8_t *)hci_pckt, length, -1);
  }
}

