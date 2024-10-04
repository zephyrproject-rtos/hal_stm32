/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hci_parser.h
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
#ifndef HCI_PARSER_H
#define HCI_PARSER_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "compiler.h"
/* Exported macro ------------------------------------------------------------*/

/* HCI Packet types */
#define HCI_COMMAND_PKT		0x01
#define HCI_ACLDATA_PKT		0x02
#define HCI_SCODATA_PKT		0x03
#define HCI_EVENT_PKT		0x04
#define HCI_ISO_DATA_PKT	0x05
#define HCI_COMMAND_EXT_PKT	0x81
#define HCI_EVENT_EXT_PKT	0x82
#define HCI_VENDOR_PKT		0xFF

#define HCI_TYPE_OFFSET                 0
#define HCI_VENDOR_CMDCODE_OFFSET       1
#define HCI_VENDOR_LEN_OFFSET           2
#define HCI_VENDOR_PARAM_OFFSET         4

/* Exported constants --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef enum {
  WAITING_TYPE,
  WAITING_HEADER,
  WAITING_PAYLOAD
}hci_state;

typedef PACKED(struct) _hci_uart_pckt{
  uint8_t       type;
  uint8_t       data[0];
}  hci_uart_pckt;
#define HCI_TYPE_SIZE 1

typedef PACKED(struct) _hci_cmd_hdr{
  uint8_t       type;
  uint16_t      opcode;
  uint8_t       param_len;
} hci_cmd_hdr;

typedef PACKED(struct) _hci_acl_hdr{
  uint8_t       type;
  uint16_t      handle;		/* Connection handle & Flags(PB, BC) */
  uint16_t      dlen;
} hci_acl_hdr;

typedef PACKED(struct) _hci_iso_data_hdr{
  uint8_t       type;
  uint16_t      handle;		/* Connection handle & Flags(PB, TS) */
  uint16_t      dlen;       /* ISO Data Load Length (2 msb are reserved) */
} hci_iso_data_hdr;

typedef PACKED(struct) _hci_cmd_ext_hdr{
  uint8_t       type;
  uint16_t      opcode;
  uint16_t      param_len;
} hci_cmd_ext_hdr;

typedef PACKED(struct) _hci_vendor_hdr{
  uint8_t       type;
  uint8_t	    opcode;
  uint16_t	    param_len;
} hci_vendor_hdr;

#define EVT_LE_META_EVENT	0x3E
typedef PACKED(struct) _evt_le_meta_event{
  uint8_t       subevent;
  uint8_t       data[0];
}  evt_le_meta_event;
#define EVT_LE_META_EVENT_SIZE 1

typedef PACKED(struct) _evt_blue_aci{
  uint16_t      ecode; /**< One of the BlueNRG event codes. */
  uint8_t       data[0];
} evt_blue_aci;

/* Exported functions ------------------------------------------------------- */

/* HCI library functions. */
extern hci_state hci_input(uint8_t *buff, uint16_t len);

extern uint8_t buffer_out[];
extern uint16_t buffer_out_len;

#endif /* HCI_PARSER_H */
