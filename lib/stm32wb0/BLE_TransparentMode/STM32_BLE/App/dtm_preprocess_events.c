/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dtm_preprocess_events.c
  * @author  GPM WBL Application Team
  * @brief   File containing hooks for network processor mode.
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
#include "dtm_preprocess_events.h"
#include "ble.h"

int hci_disconnection_complete_event_process(uint8_t *buffer_in);
int aci_hal_adv_scan_resp_data_update_event_process(uint8_t *buffer_in);
int aci_hal_pawr_data_free_event_process(uint8_t *buffer_in);
int aci_l2cap_cos_disconnection_complete_event_process(uint8_t *buffer_in);
int aci_l2cap_cos_connection_event_process(uint8_t *buffer_in);
int aci_l2cap_cos_sdu_data_rx_event_process(uint8_t *buffer_in);
int aci_gatt_srv_attribute_modified_event_process(uint8_t *buffer_in);
int aci_gatt_clt_notification_event_process(uint8_t *buffer_in);
int aci_gatt_clt_proc_complete_event_process(uint8_t *buffer_in);
int aci_gatt_tx_pool_available_event_process(uint8_t *buffer_in);
int aci_gatt_srv_read_event_process(uint8_t *buffer_in);
int aci_gatt_srv_write_event_process(uint8_t *buffer_in);
int aci_att_srv_prepare_write_req_event_process(uint8_t *buffer_in);

const hci_events_table_type hci_events_table[] = {
#if (BLESTACK_CONTROLLER_ONLY == 0)
  {HCI_DISCONNECTION_COMPLETE_EVT_CODE, hci_disconnection_complete_event_process},
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */
  {0,NULL},
};
const hci_le_meta_events_table_type hci_le_meta_events_table[] = {
  {0,NULL},
};
const hci_vendor_specific_events_table_type hci_vendor_specific_events_table[] = {
  {ACI_HAL_ADV_SCAN_RESP_DATA_UPDATE_VSEVT_CODE, aci_hal_adv_scan_resp_data_update_event_process},
#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)
  {ACI_HAL_PAWR_DATA_FREE_VSEVT_CODE, aci_hal_pawr_data_free_event_process},
#endif /* (CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1) */
#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CFG_BLE_L2CAP_COS_ENABLED == 1)
  {ACI_L2CAP_COS_DISCONNECTION_COMPLETE_VSEVT_CODE, aci_l2cap_cos_disconnection_complete_event_process},
  {ACI_L2CAP_COS_SDU_DATA_RX_VSEVT_CODE, aci_l2cap_cos_sdu_data_rx_event_process},
#endif /* (CFG_BLE_L2CAP_COS_ENABLED == 1) */
#if (CFG_BLE_CONNECTION_ENABLED == 1)
  {ACI_GATT_SRV_ATTRIBUTE_MODIFIED_VSEVT_CODE, aci_gatt_srv_attribute_modified_event_process},
  {ACI_GATT_CLT_NOTIFICATION_VSEVT_CODE, aci_gatt_clt_notification_event_process},
  {ACI_GATT_CLT_PROC_COMPLETE_VSEVT_CODE, aci_gatt_clt_proc_complete_event_process},
  {ACI_GATT_TX_POOL_AVAILABLE_VSEVT_CODE, aci_gatt_tx_pool_available_event_process},
  {ACI_GATT_SRV_READ_VSEVT_CODE, aci_gatt_srv_read_event_process},
  {ACI_GATT_SRV_WRITE_VSEVT_CODE, aci_gatt_srv_write_event_process},
  {ACI_ATT_SRV_PREPARE_WRITE_REQ_VSEVT_CODE, aci_att_srv_prepare_write_req_event_process},
#endif /* (CFG_BLE_CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */
  {0,NULL},
};

int hci_disconnection_complete_event_process(uint8_t *buffer_in)
{
  tBleStatus ret;
  /* Input params */
  hci_disconnection_complete_event_rp0 *evt = (hci_disconnection_complete_event_rp0 *)buffer_in;

  ret = hci_disconnection_complete_event_preprocess(evt->Status,
                                                    evt->Connection_Handle,
                                                    evt->Reason);

  return ret;
}

int aci_hal_adv_scan_resp_data_update_event_process(uint8_t *buffer_in)
{
  int ret;
  /* Input params */
  aci_hal_adv_scan_resp_data_update_event_rp0 *evt = (aci_hal_adv_scan_resp_data_update_event_rp0 *)buffer_in;

  ret = aci_hal_adv_scan_resp_data_update_event_preprocess(evt->Old_Pointer, evt->New_Pointer);

  return ret;
}

#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)

int aci_hal_pawr_data_free_event_process(uint8_t *buffer_in)
{
  int ret = 0;

  /* Input params */
  aci_hal_pawr_data_free_event_rp0 *evt = (aci_hal_pawr_data_free_event_rp0 *)buffer_in;
  ret = aci_hal_pawr_data_free_event_preprocess(evt->Buffer, evt->Type);

  return ret;
}

#endif /* (CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CFG_BLE_L2CAP_COS_ENABLED == 1)

int aci_l2cap_cos_disconnection_complete_event_process(uint8_t *buffer_in)
{
  int ret;
  /* Input params */
  aci_l2cap_cos_disconnection_complete_event_rp0 *evt = (aci_l2cap_cos_disconnection_complete_event_rp0 *)buffer_in;
  ret = aci_l2cap_cos_disconnection_complete_event_preprocess(evt->Connection_Handle,
                                                          evt->CID);

  return ret;
}

int aci_l2cap_cos_sdu_data_rx_event_process(uint8_t *buffer_in)
{
  int ret;

  aci_l2cap_cos_sdu_data_rx_event_rp0 *evt = (aci_l2cap_cos_sdu_data_rx_event_rp0 *)buffer_in;

  ret = aci_l2cap_cos_sdu_data_rx_event_preprocess(evt->Connection_Handle,
                                                   evt->CID,
                                                   evt->RX_Credit_Balance,
                                                   evt->SDU_Length);

  return ret;
}

#endif /* (CFG_BLE_L2CAP_COS_ENABLED == 1) */

#if (CFG_BLE_CONNECTION_ENABLED == 1)

int aci_gatt_tx_pool_available_event_process(uint8_t *buffer_in)
{
  int ret;

  aci_gatt_tx_pool_available_event_rp0 *evt = (aci_gatt_tx_pool_available_event_rp0 *)buffer_in;
  ret = aci_gatt_tx_pool_available_event_preprocess(evt->Connection_Handle,
                                                    evt->Available_Buffers);

  return ret;
}

int aci_gatt_srv_attribute_modified_event_process(uint8_t *buffer_in)
{
  int ret;

  aci_gatt_srv_attribute_modified_event_rp0 *evt = (aci_gatt_srv_attribute_modified_event_rp0 *)buffer_in;
  ret = aci_gatt_srv_attribute_modified_event_preprocess(evt->Connection_Handle,
                                                         evt->CID,
                                                         evt->Attr_Handle,
                                                         evt->Attr_Data_Length,
                                                         evt->Attr_Data);

  return ret;
}

int aci_gatt_clt_notification_event_process(uint8_t *buffer_in)
{
  int ret;
  /* Input params */
  aci_gatt_clt_notification_event_rp0 *evt = (aci_gatt_clt_notification_event_rp0 *)buffer_in;
  ret = aci_gatt_clt_notification_event_preprocess(evt->Connection_Handle,
                                                   evt->CID,
                                                   evt->Attribute_Handle,
                                                   evt->Attribute_Value_Length,
                                                   evt->Attribute_Value);

  return ret;
}

int aci_gatt_clt_proc_complete_event_process(uint8_t *buffer_in)
{
  tBleStatus ret;
  /* Input params */
  aci_gatt_clt_proc_complete_event_rp0 *evt = (aci_gatt_clt_proc_complete_event_rp0 *)buffer_in;
  ret = aci_gatt_clt_proc_complete_event_preprocess(evt->Connection_Handle,
                                                    evt->CID,
                                                    evt->Error_Code);

  return ret;
}

int aci_gatt_srv_read_event_process(uint8_t *buffer_in)
{
  int ret;

  aci_gatt_srv_read_event_rp0 *evt = (aci_gatt_srv_read_event_rp0 *)buffer_in;
  ret = aci_gatt_srv_read_event_preprocess(evt->Connection_Handle, evt->CID, evt->Attribute_Handle, evt->Data_Offset);

  return ret;
}

int aci_gatt_srv_write_event_process(uint8_t *buffer_in)
{
  int ret;

  aci_gatt_srv_write_event_rp0 *evt = (aci_gatt_srv_write_event_rp0 *)buffer_in;
  ret = aci_gatt_srv_write_event_preprocess(evt->Connection_Handle, evt->CID, evt->Resp_Needed,
                                            evt->Attribute_Handle, evt->Data_Length, evt->Data);

  return ret;
}

int aci_att_srv_prepare_write_req_event_process(uint8_t *buffer_in)
{
  int ret = 0;

  /* Input params */
  aci_att_srv_prepare_write_req_event_rp0 *evt = (aci_att_srv_prepare_write_req_event_rp0 *)buffer_in;
  ret = aci_att_srv_prepare_write_req_event_preprocess(evt->Connection_Handle, evt->CID, evt->Attribute_Handle,
                                                       evt->Data_Offset, evt->Data_Length, evt->Data);
  return ret;
}

#endif /* (CFG_BLE_CONNECTION_ENABLED == 1) */

#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */
