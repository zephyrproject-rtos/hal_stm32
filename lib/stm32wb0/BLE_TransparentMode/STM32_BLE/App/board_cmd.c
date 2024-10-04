/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    board_cmd.c
  * @author  GPM WBL Application Team
  * @brief   Module that implements board commands
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

#include "stm32wb0x.h"
#include "board_cmd.h"
#include "hci_parser.h"
#include "transport_layer.h"

#define RESP_VENDOR_CODE_OFFSET     1
#define RESP_LEN_OFFSET_LSB         2
#define RESP_LEN_OFFSET_MSB         3
#define RESP_CMDCODE_OFFSET         4
#define RESP_STATUS_OFFSET          5
#define RESP_PARAM_OFFSET           6

/* Types of vendor codes */
#define ERROR               0
/* Error codes */
#define UNKNOWN_COMMAND	        0x01
#define INVALID_PARAMETERS	0x12

#define RESPONSE                   1
/* end of vendor codes */

/* Command parser
 * bytes
 * 1         Type of packet (FF for special command)
 * 1         cmdcode
 * 2         cmd length (length of arguments)
 * variable  payload
 */
   /* Actually only for UART INTERFACE */

uint16_t parse_cmd(uint8_t *hci_buffer, uint16_t hci_pckt_len, uint8_t *buffer_out)
{
    uint16_t len = 0;
    buffer_out[0] = HCI_VENDOR_PKT;
    buffer_out[RESP_VENDOR_CODE_OFFSET] = RESPONSE;
    buffer_out[RESP_CMDCODE_OFFSET] = hci_buffer[HCI_VENDOR_CMDCODE_OFFSET];
    buffer_out[RESP_STATUS_OFFSET] = 0;

    switch(hci_buffer[HCI_VENDOR_CMDCODE_OFFSET])
    {
    case SYSTEM_RESET:
        NVIC_SystemReset();
        break;
#if defined(STM32WB05N)
    case HW_BOOTLOADER:
        RAM_VR.BlueFlag = BLUE_FLAG_RAM_RESET;
        NVIC_SystemReset();
        break;
#endif
    default:
        buffer_out[RESP_VENDOR_CODE_OFFSET] = ERROR;
        buffer_out[RESP_STATUS_OFFSET] = UNKNOWN_COMMAND;
    }

    len += 2; // Status and Command code
    PACK_2_BYTE_PARAMETER(buffer_out+RESP_LEN_OFFSET_LSB,len);
    len += RESP_CMDCODE_OFFSET;

    return len;
}

