/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dtm_preprocess_events.h
  * @author  GPM WBL Application Team
  * @brief   Header file preprocess hooks for events.
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
#ifndef DTM_PREPROCESS_EVENTS_H
#define DTM_PREPROCESS_EVENTS_H

#include <stdint.h>
#include "ble_status.h"

typedef int (*hci_event_process)(uint8_t *buffer_in);
typedef struct hci_event_table_type_s {
  uint16_t evt_code;
  hci_event_process process;
} hci_events_table_type, hci_le_meta_events_table_type, hci_vendor_specific_events_table_type;

extern const hci_events_table_type hci_events_table[];
extern const hci_le_meta_events_table_type hci_le_meta_events_table[];
extern const hci_vendor_specific_events_table_type hci_vendor_specific_events_table[];

int hci_disconnection_complete_event_preprocess(uint8_t Status,
                                                uint16_t Connection_Handle,
                                                uint8_t Reason);

int aci_gatt_srv_attribute_modified_event_preprocess(uint16_t Connection_Handle,
                                                     uint16_t CID,
                                                     uint16_t Attr_Handle,
                                                     uint16_t Attr_Data_Length,
                                                     uint8_t Attr_Data[]);

int aci_gatt_clt_notification_event_preprocess(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t Attribute_Handle,
                                               uint16_t Attribute_Value_Length,
                                               uint8_t Attribute_Value[]);

int aci_gatt_clt_proc_complete_event_preprocess(uint16_t Connection_Handle,
                                                uint16_t CID,
                                                uint8_t Error_Code);

int aci_gatt_tx_pool_available_event_preprocess(uint16_t Connection_Handle,
                                                uint16_t Available_Buffers);

int aci_gatt_srv_read_event_preprocess(uint16_t Connection_Handle,
                                       uint16_t CID,
                                       uint16_t Attribute_Handle,
                                       uint16_t Data_Offset);

int aci_gatt_srv_write_event_preprocess(uint16_t Connection_Handle,
                                        uint16_t CID,
                                        uint8_t Resp_Needed,
                                        uint16_t Attribute_Handle,
                                        uint16_t Data_Length,
                                        uint8_t Data[]);

int aci_att_srv_prepare_write_req_event_preprocess(uint16_t Connection_Handle,
                                                   uint16_t CID,
                                                   uint16_t Attribute_Handle,
                                                   uint16_t Data_Offset,
                                                   uint16_t Data_Length,
                                                   uint8_t Data[]);

int aci_l2cap_cos_disconnection_complete_event_preprocess(uint16_t Connection_Handle,
                                                          uint16_t CID);

int aci_l2cap_cos_sdu_data_tx_event_preprocess(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t SDU_Length,
                                               void * SDU_Data_Buffer,
                                               uint16_t TX_Credit_Balance);

int aci_l2cap_cos_sdu_data_rx_event_preprocess(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t RX_Credit_Balance,
                                               uint16_t SDU_Length);

int aci_hal_adv_scan_resp_data_update_event_preprocess(void * Old_Pointer,
                                                       void * New_Pointer);

int aci_hal_pawr_data_free_event_preprocess(void * Buffer,
                                            uint8_t Type);

#endif /* DTM_PREPROCESS_EVENTS_H */
