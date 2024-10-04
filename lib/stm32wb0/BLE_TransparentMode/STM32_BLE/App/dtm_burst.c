/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dtm_burst.c
  * @author  GPM WBL Application Team
  * @brief   Module that implements test burst commands
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
#include "ble.h"
#include "dtm_burst.h"
#include "app_common.h"

#define OFF                0
#define NOTIFICATIONS      1
#define WRITE_COMMANDS     2

#if (CFG_BLE_CONNECTION_ENABLED == 1) && (BLESTACK_CONTROLLER_ONLY == 0)

struct {
  uint8_t  Enable; // OFF, NOTIFICATIONS or WRITE_COMMANDS
  uint8_t  tx_buffer_full;
  uint16_t Connection_Handle;
  uint16_t Service_Handle; // Not used for write commands
  uint16_t Handle; // Characteristic handle in case of notifications, attribute handle in case of write commands
  uint16_t Value_Length;
  uint32_t Seq_Num;
}TXBurstData;

struct {
  uint8_t  Enable; // OFF, NOTIFICATIONS or WRITE_COMMANDS
  uint16_t Connection_Handle;
  uint16_t Attribute_Handle;
  uint32_t Received_Packets;
  uint32_t Next_Seq_Num;
  uint32_t Seq_Errors;
  uint16_t Value_Length; // Holds length of last packet only
}RxBurstData;

tBleStatus BURST_TXNotificationStart(uint16_t Connection_Handle, uint16_t Service_Handle,
                                      uint16_t Char_Handle, uint16_t Value_Length)
{
  tBleStatus ret;
  uint32_t Value[(CFG_BLE_ATT_MTU_MAX+3)/4];
  uint32_t *pSeqNum = Value;

  if(TXBurstData.Enable != OFF)
    return BLE_ERROR_COMMAND_DISALLOWED;

  memset(Value,0, sizeof(Value));

  TXBurstData.Seq_Num = 0;

  *pSeqNum = TXBurstData.Seq_Num;

  ret = aci_gatt_srv_notify(Connection_Handle, BLE_GATT_UNENHANCED_ATT_L2CAP_CID, Char_Handle + 1, GATT_NOTIFICATION, Value_Length, (uint8_t *)Value);

  if(ret == BLE_STATUS_SUCCESS){
    // Everything went well. Store all the information
    TXBurstData.Connection_Handle = Connection_Handle;
    TXBurstData.Service_Handle = Service_Handle;
    TXBurstData.Handle = Char_Handle;
    TXBurstData.Value_Length = Value_Length;
    TXBurstData.Seq_Num = 1;
    TXBurstData.Enable = NOTIFICATIONS;
    TXBurstData.tx_buffer_full = FALSE;

    BURST_StartCallback();

    return BLE_STATUS_SUCCESS;
  }

  return ret;
}

tBleStatus BURST_TXWriteCommandStart(uint16_t Connection_Handle, uint16_t Attr_Handle,
                                     uint16_t Value_Length)
{
  tBleStatus ret;
  uint32_t Value[(CFG_BLE_ATT_MTU_MAX+3)/4];
  uint32_t *pSeqNum = Value;

  if(TXBurstData.Enable != OFF)
    return BLE_ERROR_COMMAND_DISALLOWED;

  memset(Value,0, sizeof(Value));

  TXBurstData.Seq_Num = 0;

  *pSeqNum = TXBurstData.Seq_Num;

  //TBR Replace with new API
  ret = aci_gatt_clt_write_without_resp(Connection_Handle, BLE_GATT_UNENHANCED_ATT_L2CAP_CID, Attr_Handle,
                                         Value_Length, (uint8_t *)Value);
  if(ret == BLE_STATUS_SUCCESS){
    // Everything went well. Store all the information
    TXBurstData.Connection_Handle = Connection_Handle;
    TXBurstData.Handle = Attr_Handle;
    TXBurstData.Value_Length = Value_Length;
    TXBurstData.Seq_Num = 1;
    TXBurstData.Enable = WRITE_COMMANDS;
    TXBurstData.tx_buffer_full = FALSE;

    BURST_StartCallback();

    return BLE_STATUS_SUCCESS;
  }

  return ret;
}

tBleStatus BURST_RXStart(uint16_t Connection_Handle, uint16_t Attribute_Handle, uint8_t Notifications_WriteCmds)
{
  if(RxBurstData.Enable != OFF)
    return BLE_ERROR_COMMAND_DISALLOWED;

  if(Notifications_WriteCmds == 0)
    RxBurstData.Enable = NOTIFICATIONS;
  else
    RxBurstData.Enable = WRITE_COMMANDS;

  RxBurstData.Connection_Handle = Connection_Handle;
  RxBurstData.Attribute_Handle = Attribute_Handle;
  RxBurstData.Received_Packets = 0;
  RxBurstData.Next_Seq_Num = 0;
  RxBurstData.Seq_Errors = 0;

  return BLE_STATUS_SUCCESS;
}

tBleStatus BURST_TXStop(void)
{
  if(TXBurstData.Enable == OFF)
    return BLE_ERROR_COMMAND_DISALLOWED;

  TXBurstData.Enable = OFF;

  return BLE_STATUS_SUCCESS;
}

tBleStatus BURST_RXStop(void)
{
  if(RxBurstData.Enable == OFF)
    return BLE_ERROR_COMMAND_DISALLOWED;

  RxBurstData.Enable = OFF;

  return BLE_STATUS_SUCCESS;
}

static uint8_t PacketReceived(uint16_t Connection_Handle, uint16_t Attribute_Handle, uint16_t Value_Length, uint8_t Value[])
{
  uint32_t seq_num;

  if(RxBurstData.Connection_Handle == Connection_Handle && RxBurstData.Attribute_Handle == Attribute_Handle){

    seq_num = LE_TO_HOST_32(Value);

    if(seq_num != RxBurstData.Next_Seq_Num){
      // Sequence error
      RxBurstData.Seq_Errors++;
    }

    RxBurstData.Next_Seq_Num = seq_num + 1;
    RxBurstData.Received_Packets++;
    RxBurstData.Value_Length = Value_Length;

    return 1;
  }

  return 0;
}

/* To be called from the aci_gatt_clt_notification_event(). Returns 1 if burst mode is ON
  and notification event should not be sent to application. */
uint8_t BURST_NotificationReceived(uint16_t Connection_Handle, uint16_t Attribute_Handle, uint16_t Value_Length, uint8_t Value[])
{
  if(RxBurstData.Enable == NOTIFICATIONS)
    return PacketReceived(Connection_Handle, Attribute_Handle, Value_Length, Value);

  return 0;
}

/* To be called from the aci_gatt_srv_attribute_modified_event(). Returns 1 if burst mode is ON
  and attribute_modified event should not be sent to application. */
uint8_t BURST_WriteReceived(uint16_t Connection_Handle, uint16_t Attribute_Handle, uint16_t Value_Length, uint8_t Value[])
{
  if(RxBurstData.Enable == WRITE_COMMANDS)
    return PacketReceived(Connection_Handle, Attribute_Handle, Value_Length, Value);

  return 0;
}

/* To be called from the aci_gatt_tx_pool_available_event() */
uint8_t BURST_BufferAvailableNotify(void)
{
  if(TXBurstData.Enable != OFF){
    TXBurstData.tx_buffer_full = FALSE;
    return 1;
  }
  return 0;
}

uint32_t BURST_TXReport(void)
{
  return TXBurstData.Seq_Num;
}

uint32_t BURST_RXReport(uint16_t *Data_Length, uint32_t *Sequence_Errors)
{
  if(Data_Length != NULL)
    *Data_Length = RxBurstData.Value_Length;
  if(Sequence_Errors != NULL)
    *Sequence_Errors = RxBurstData.Seq_Errors;

  return RxBurstData.Received_Packets;
}

static void SendNotificationBurst(void)
{
  uint32_t Value[(CFG_BLE_ATT_MTU_MAX+3)/4];
  uint32_t *pSeqNum = Value;
  tBleStatus ret = BLE_STATUS_SUCCESS;

  memset(Value,0, sizeof(Value));

  *pSeqNum = TXBurstData.Seq_Num;

  while(ret == BLE_STATUS_SUCCESS){

    ret = aci_gatt_srv_notify(TXBurstData.Connection_Handle, BLE_GATT_UNENHANCED_ATT_L2CAP_CID, TXBurstData.Handle + 1, 0,  TXBurstData.Value_Length, (uint8_t *)Value);
    if(ret == BLE_STATUS_SUCCESS){
      (*pSeqNum)++;
    }
  }

  if(ret == BLE_STATUS_INSUFFICIENT_RESOURCES){
    TXBurstData.tx_buffer_full = TRUE;
  }

  TXBurstData.Seq_Num = *pSeqNum;
}

static void SendWriteCommandBurst(void)
{
  uint32_t Value[(CFG_BLE_ATT_MTU_MAX+3)/4];
  uint32_t *pSeqNum = Value;
  tBleStatus ret = BLE_STATUS_SUCCESS;

  memset(Value,0, sizeof(Value));

  *pSeqNum = TXBurstData.Seq_Num;

  while(ret == BLE_STATUS_SUCCESS){

    ret = aci_gatt_clt_write_without_resp(TXBurstData.Connection_Handle, BLE_GATT_UNENHANCED_ATT_L2CAP_CID, TXBurstData.Handle,
                                          TXBurstData.Value_Length, (uint8_t *)Value);
    if(ret == BLE_STATUS_SUCCESS){
      (*pSeqNum)++;
    }
  }

  if(ret == BLE_STATUS_INSUFFICIENT_RESOURCES){
    TXBurstData.tx_buffer_full = TRUE;
  }

  TXBurstData.Seq_Num = *pSeqNum;
}

void BURST_Tick(void)
{
  if(TXBurstData.tx_buffer_full == FALSE){
    if(TXBurstData.Enable == NOTIFICATIONS){
      SendNotificationBurst();
    }
    else if(TXBurstData.Enable == WRITE_COMMANDS){
      SendWriteCommandBurst();
    }
  }
}

__weak void BURST_StartCallback(void){}

#else

void BURST_Tick(void){}

#endif
