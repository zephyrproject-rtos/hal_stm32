/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    aci_adv_nwk.c
  * @author  MCD Application Team
  * @brief   Adaptation layer from stack native advertising interface
  *                      to network interface.
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

#include <string.h>
#include "aci_adv_nwk.h"
#include "app_common.h"
#include "adv_buff_alloc.h"
#include "adv_buff_alloc_tiny.h"
#include "pawr_buff_alloc.h"
#include "ble.h"

#define LEGACY_ADV_HANDLE   0xFE
#define MEM_ALLOC_OVERHEAD   8
#define MAX_ADV_DATA_LENGTH MIN(CFG_BLE_GATT_ADV_NWK_BUFFER_SIZE - CFG_BLE_ATT_QUEUED_WRITE_SIZE - MEM_ALLOC_OVERHEAD, 1650)

/** @name Operation codes for setting advertising data
  * @{
  */
#define INTERMEDIATE_FRAGMENT   0
#define FIRST_FRAGMENT          1
#define LAST_FRAGMENT           2
#define COMPLETE_DATA           3
#define UNCHANGED_DATA          4
/**
  * @}
  */

/** @name Options for layer parameter of set_legacy_adv_scan_data
  * @{
  */
#define LL                      0
#define GAP                     1
/**
  * @}
  */

#if (CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED == 0)

static tBleStatus allocate_and_set_data_legacy(uint8_t Advertising_Handle, uint8_t Operation,
                                               uint8_t Data_Length, uint8_t *Data, uint8_t adv_scan_resp, uint8_t layer);

static tBleStatus set_legacy_data_ptr(uint16_t Data_Length, uint8_t *Data, uint8_t adv_scan_resp, uint8_t layer);

void aci_adv_nwk_init(void)
{
  adv_tiny_buff_init();
}

static tBleStatus allocate_and_set_data(uint8_t Advertising_Handle, uint8_t Operation, uint8_t Data_Length, uint8_t *Data, uint8_t adv_scan_resp, uint8_t layer)
{
  return allocate_and_set_data_legacy(Advertising_Handle, Operation, Data_Length, Data, adv_scan_resp, layer);
}

/* Event raised by the stack when a new data pointer becomes active.
   The function will free the the memory pointed by the old pointer.
*/
int aci_hal_adv_scan_resp_data_update_event_preprocess(void *old_pointer, void *new_pointer)
{
  if (new_pointer != old_pointer)
  {
    adv_tiny_buff_free(old_pointer);
  }

  return 1;
}

// Advertising_Handle is actually not used
static tBleStatus allocate_and_set_data_legacy(uint8_t Advertising_Handle, uint8_t Operation, uint8_t Data_Length, uint8_t *Data, uint8_t adv_scan_resp, uint8_t layer)
{
  tBleStatus ret;
  uint8_t *adv_buffer;

  if(Operation != COMPLETE_DATA || Data_Length > 31)
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  adv_buffer = adv_tiny_buff_alloc();

  if(adv_buffer == NULL)
    return BLE_ERROR_CONTROLLER_BUSY;

  memcpy(adv_buffer, Data, Data_Length);

  ret = set_legacy_data_ptr(Data_Length, adv_buffer, adv_scan_resp, layer);

  if(ret)
  {
    adv_tiny_buff_free(adv_buffer);
  }

  return ret;
}

static tBleStatus set_legacy_data_ptr(uint16_t Data_Length, uint8_t *Data, uint8_t adv_scan_resp, uint8_t layer)
{
  if(adv_scan_resp == ADV_DATA){
    // Advertising Data
#if (BLESTACK_CONTROLLER_ONLY == 0)
    if(layer == GAP)
      return aci_gap_set_advertising_data(0, COMPLETE_DATA, Data_Length, Data);
    else
#endif
      return ll_set_legacy_advertising_data_ptr(Data_Length, Data);
  }
  else{
    // Scan Response
#if (BLESTACK_CONTROLLER_ONLY == 0)
    if(layer == GAP)
      return aci_gap_set_scan_response_data(0, Data_Length, Data);
    else
#endif
      return ll_set_legacy_scan_reponse_data_ptr(Data_Length, Data);
  }
}

tBleStatus aci_gap_set_advertising_enable_preprocess(uint8_t Enable,
                                                     uint8_t Number_of_Sets,
                                                     Advertising_Set_Parameters_t Advertising_Set_Parameters[])
{
  return BLE_STATUS_SUCCESS;
}

#else /* (CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

tBleStatus hci_le_read_maximum_advertising_data_length(uint16_t *Maximum_Advertising_Data_Length)
{
  *Maximum_Advertising_Data_Length = MAX_ADV_DATA_LENGTH;

  return BLE_STATUS_SUCCESS;
}

static tBleStatus allocate_and_set_data_ext(uint8_t Advertising_Handle,
                                            uint8_t Operation, uint8_t Data_Length, uint8_t *Data, uint8_t data_type, uint8_t layer);

void aci_adv_nwk_init(void)
{
  adv_buff_init();
#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)
  pawr_buff_init();
#endif
}

static tBleStatus allocate_and_set_data(uint8_t Advertising_Handle, uint8_t Operation, uint8_t Data_Length, uint8_t *Data, uint8_t data_type, uint8_t layer)
{
  return allocate_and_set_data_ext(Advertising_Handle, Operation, Data_Length, Data, data_type, layer);
}

tBleStatus hci_le_set_extended_advertising_data(uint8_t Advertising_Handle, uint8_t Operation,
                                                uint8_t Fragment_Preference,
                                                uint8_t Advertising_Data_Length, uint8_t *Advertising_Data)
{
  return allocate_and_set_data(Advertising_Handle,
                                Operation, Advertising_Data_Length, Advertising_Data, ADV_DATA, LL);

}

tBleStatus hci_le_set_extended_scan_response_data(uint8_t Advertising_Handle, uint8_t Operation,
                                                uint8_t Fragment_Preference,
                                                uint8_t Scan_Response_Data_Length, uint8_t *Scan_Response_Data)
{
  return allocate_and_set_data(Advertising_Handle,
                                Operation, Scan_Response_Data_Length, Scan_Response_Data, SCAN_RESP_DATA, LL);
}

#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED == 1)
tBleStatus hci_le_set_periodic_advertising_data(uint8_t Advertising_Handle, uint8_t Operation,
                                                uint8_t Advertising_Data_Length, uint8_t *Advertising_Data)
{
  return allocate_and_set_data(Advertising_Handle,
                               Operation, Advertising_Data_Length, Advertising_Data, PERIODIC_ADV_DATA, LL);
}

#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)

tBleStatus hci_le_set_periodic_advertising_subevent_data(uint8_t Advertising_Handle,
                                                         uint8_t Num_Subevents,
                                                         Subevent_Data_Parameters_t Subevent_Data_Parameters[])
{
  tBleStatus ret;
  uint8_t i;
  void * p;
  Subevent_Data_Ptr_Parameters_t Subevent_Data_Ptr_Parameters[CFG_BLE_PAWR_SUBEVENT_DATA_COUNT_MAX] = {0};
  uint16_t adv_event_prop;
  uint8_t adv_enabled, periodic_adv_configured, periodic_adv_enabled;

  if (Advertising_Handle > 0xEF)
  {
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
  }

  /* Check if advertising set exists, so that error 0x42 will be returned. */
  ret = ll_get_advertising_info(Advertising_Handle, &adv_enabled, &periodic_adv_configured, &periodic_adv_enabled, &adv_event_prop);
  if(ret!=0)
  {
    return BLE_ERROR_UNKNOWN_ADVERTISING_IDENTIFIER;
  }

  if(pawr_buff_subevent_num_available() < Num_Subevents)
  {
    /* This happens is host has given more data than what requested by the Controller.  */
    return BLE_ERROR_COMMAND_DISALLOWED;
  }

  for(i = 0; i < Num_Subevents; i++)
  {
    if(Subevent_Data_Parameters[i].Subevent_Data_Length > MAX_PAWR_SUBEVENT_DATA_SIZE)
    {
      /* This should never happen as long as MAX_PAWR_SUBEVENT_DATA_SIZE >= 249. */
      ret = BLE_ERROR_MEMORY_CAPACITY_EXCEEDED;
      goto fail;
    }

    p = pawr_buff_subevent_alloc();

    if(p != NULL)
    {
      Subevent_Data_Ptr_Parameters[i].Subevent = Subevent_Data_Parameters[i].Subevent;
      Subevent_Data_Ptr_Parameters[i].Response_Slot_Start = Subevent_Data_Parameters[i].Response_Slot_Start;
      Subevent_Data_Ptr_Parameters[i].Response_Slot_Count = Subevent_Data_Parameters[i].Response_Slot_Count;
      Subevent_Data_Ptr_Parameters[i].Subevent_Data_Length = Subevent_Data_Parameters[i].Subevent_Data_Length;
      memcpy(p, Subevent_Data_Parameters[i].Subevent_Data, Subevent_Data_Parameters[i].Subevent_Data_Length);
      Subevent_Data_Ptr_Parameters[i].Subevent_Data = p;
    }
    else
    {
      /* This should never happen since we checked num of available buffers before. */
      goto fail;
    }
  }

  ret = ll_set_periodic_advertising_subevent_data_ptr(Advertising_Handle,
                                                      Num_Subevents,
                                                      Subevent_Data_Ptr_Parameters);

  if(ret == BLE_STATUS_SUCCESS)
    return ret;

fail:

  /* Free allocated buffers */
  for(i = 0; i < Num_Subevents; i++)
  {
    pawr_buff_free(Subevent_Data_Ptr_Parameters[i].Subevent_Data, HAL_PAWR_DATA_TYPE_SUBEVENT);
  }
  return ret;
}

tBleStatus hci_le_set_periodic_advertising_response_data(uint16_t Sync_Handle,
                                                         uint16_t Request_Event,
                                                         uint8_t Request_Subevent,
                                                         uint8_t Response_Subevent,
                                                         uint8_t Response_Slot,
                                                         uint8_t Response_Data_Length,
                                                         uint8_t Response_Data[])
{
  tBleStatus ret;
  void * p;

  if(Response_Data_Length > MAX_PAWR_RESPONSE_DATA_SIZE)
  {
    /* This should never happen as long as MAX_PAWR_RESPONSE_DATA_SIZE >= 247. */
    return BLE_ERROR_MEMORY_CAPACITY_EXCEEDED;
  }

  p = pawr_buff_resp_alloc();

  if(p == NULL)
  {
    return BLE_ERROR_MEMORY_CAPACITY_EXCEEDED;
  }

  memcpy(p, Response_Data, Response_Data_Length);

  ret = ll_set_periodic_advertising_response_data_ptr(Sync_Handle, Request_Event,
                                                      Request_Subevent, Response_Subevent,
                                                      Response_Slot, Response_Data_Length,
                                                      p);

  if(ret != BLE_STATUS_SUCCESS)
  {
    pawr_buff_free(p, HAL_PAWR_DATA_TYPE_RESPONSE);
  }

  return ret;
}

#endif /* (CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1) */
#endif /* (CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED == 1) */

int aci_hal_adv_scan_resp_data_update_event_preprocess(void *old_pointer, void *new_pointer)
{
  if (new_pointer != old_pointer)
  {
    adv_buff_free_old(old_pointer);
  }

  /* Do not forward the event. */
  return 1;
}

#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)
int aci_hal_pawr_data_free_event_preprocess(void *buffer, uint8_t type)
{
  pawr_buff_free(buffer, type);

  /* Do not forward the event. */
  return 1;
}
#endif

static uint8_t adv_data_check_param(uint8_t Advertising_Handle, uint8_t Operation, uint8_t Advertising_Data_Length, uint8_t *adv_enabled)
{
  uint16_t adv_event_prop;
  uint8_t ret;
  uint8_t periodic_adv_configured;
  uint8_t periodic_adv_enabled;

  if(Advertising_Handle == LEGACY_ADV_HANDLE){

    *adv_enabled = TRUE;

    if(Operation != COMPLETE_DATA || Advertising_Data_Length > 31)
      return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

    return BLE_STATUS_SUCCESS;
  }

  if(Advertising_Handle > 0xEF || Operation > UNCHANGED_DATA)
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  ret = ll_get_advertising_info(Advertising_Handle, adv_enabled, &periodic_adv_configured, &periodic_adv_enabled, &adv_event_prop);

  /* "If the advertising set corresponding to the Advertising_Handle parameter does
  not exist, then the Controller shall return the error code Unknown Advertising
  Identifier (0x42)." */
  if(ret!=0) // Advertising set does not exist.
    return BLE_ERROR_UNKNOWN_ADVERTISING_IDENTIFIER;

  /* "If the advertising set specifies a type that does not support advertising data, the
  Controller shall return the error code Invalid HCI Command Parameters (0x12)." */
  if((adv_event_prop & HCI_ADV_EVENT_PROP_LEGACY && adv_event_prop & HCI_ADV_EVENT_PROP_DIRECTED) || // Legacy, directed advertising
     (adv_event_prop & HCI_ADV_EVENT_PROP_SCANNABLE && !(adv_event_prop & HCI_ADV_EVENT_PROP_LEGACY))) // Scannable, non-legacy
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  /* "If the advertising set uses legacy advertising PDUs that support advertising
  data and either Operation is not 0x03 or the Advertising_Data_Length
  parameter exceeds 31 octets, the Controller shall return the error code Invalid
  HCI Command Parameters (0x12)."  */
  if(adv_event_prop & HCI_ADV_EVENT_PROP_LEGACY && (Operation != COMPLETE_DATA || Advertising_Data_Length > 31)) // Legacy advertising
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  /* "If Operation is not 0x03 or 0x04 and Advertising_Data_Length is zero, the
  Controller shall return the error code Invalid HCI Command Parameters (0x12)." */
  if(Operation != COMPLETE_DATA && Operation != UNCHANGED_DATA && Advertising_Data_Length == 0)
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  /* "If advertising is currently enabled for the specified advertising set and
  Operation does not have the value 0x03 or 0x04, the Controller shall return the
  error code Command Disallowed (0x0C)." */
  if(*adv_enabled && Operation != COMPLETE_DATA && Operation != UNCHANGED_DATA)
    return BLE_ERROR_COMMAND_DISALLOWED;

  return BLE_STATUS_SUCCESS;
}

static uint8_t scan_resp_data_check_param(uint8_t Advertising_Handle, uint8_t Operation, uint8_t Scan_Resp_Data_Length, uint8_t *adv_enabled)
{
  uint16_t adv_event_prop;
  uint8_t ret;
  uint8_t periodic_adv_configured;
  uint8_t periodic_adv_enabled;

  if(Advertising_Handle == LEGACY_ADV_HANDLE){

    /* Assume advertising is always enabled, even if this is not true.
       In this way the old buffer cannot be freed even if the advertising is not enabled. */
    *adv_enabled = TRUE;

    if(Operation != COMPLETE_DATA || Scan_Resp_Data_Length > 31)
      return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

    return BLE_STATUS_SUCCESS;
  }

  if(Operation > COMPLETE_DATA)
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  ret = ll_get_advertising_info(Advertising_Handle, adv_enabled, &periodic_adv_configured, &periodic_adv_enabled, &adv_event_prop);

  /* "If the advertising set corresponding to the Advertising_Handle parameter does
  not exist, then the Controller shall return the error code Unknown Advertising
  Identifier (0x42)." */
  if(ret!=0) // Advertising set does not exist.
    return BLE_ERROR_UNKNOWN_ADVERTISING_IDENTIFIER;

  /* "If the advertising set is non-scannable and the Host uses this command other
      than to discard existing data, the Controller shall return the error code Invalid
      HCI Command Parameters (0x12)." */
  if((!(adv_event_prop & HCI_ADV_EVENT_PROP_SCANNABLE) && Scan_Resp_Data_Length != 0))
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  /* If the advertising set uses scannable legacy advertising PDUs and either
     Operation is not 0x03 or the Scan_Response_Data_Length parameter exceeds
     31 octets, the Controller shall return the error code Invalid HCI Command
     Parameters (0x12). */
  if(adv_event_prop & HCI_ADV_EVENT_PROP_LEGACY && adv_event_prop & HCI_ADV_EVENT_PROP_SCANNABLE
     && (Operation != COMPLETE_DATA || Scan_Resp_Data_Length > 31))
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  /* "If Operation is not 0x03 and Scan_Response_Data_Length is zero, the
      Controller shall return the error code Invalid HCl Command Parameters (0x12)." */
  if(Operation != COMPLETE_DATA && Scan_Resp_Data_Length == 0)
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  /* "If advertising is currently enabled for the specified advertising set and
      Operation does not have the value 0x03, the Controller shall return the error
      code Command Disallowed (0x0C)." */
  if(*adv_enabled && Operation != COMPLETE_DATA)
    return BLE_ERROR_COMMAND_DISALLOWED;

  return BLE_STATUS_SUCCESS;
}

#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED == 1)
static uint8_t periodic_adv_data_check_param(uint8_t Advertising_Handle, uint8_t Operation, uint8_t Advertising_Data_Length, uint8_t *adv_enabled, uint8_t *periodic_adv_enabled)
{
  uint16_t adv_event_prop;
  uint8_t periodic_adv_configured;
  uint8_t ret;

  if(Operation > UNCHANGED_DATA)
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  ret = ll_get_advertising_info(Advertising_Handle, adv_enabled, &periodic_adv_configured, periodic_adv_enabled, &adv_event_prop);

  /* "If the advertising set corresponding to the Advertising_Handle parameter does
     not exist, then the Controller shall return the error code Unknown Advertising
     Identifier (0x42)." */
  if(ret!=0) // Advertising set does not exist.
    return BLE_ERROR_UNKNOWN_ADVERTISING_IDENTIFIER;

  /* "If the advertising set has not been configured for periodic advertising,
     then the Controller shall return the error code Command Disallowed (0x0C)." */
  if(!periodic_adv_configured)
    return BLE_ERROR_COMMAND_DISALLOWED;

  if(Advertising_Data_Length > 252)
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;

  if ((Operation != COMPLETE_DATA) && (Operation != UNCHANGED_DATA))
  {
    /* "If periodic advertising is currently enabled for the specified advertising set and
        Operation does not have the value 0x03 or 0x04, then the Controller shall
        return the error code Command Disallowed (0x0C)." */
    if(*periodic_adv_enabled)
      return BLE_ERROR_COMMAND_DISALLOWED;

    if(Advertising_Data_Length == 0U)
      return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
  }

  return  BLE_STATUS_SUCCESS;
}
#endif

static tBleStatus set_data_ptr(uint8_t Advertising_Handle,
                                    uint8_t Operation, uint16_t Data_Length, uint8_t *Data, uint8_t data_type, uint8_t gap)
{
  if(data_type == ADV_DATA)
  {
    // Advertising Data
#if (BLESTACK_CONTROLLER_ONLY == 0)
    if(gap)
    {
      return aci_gap_set_advertising_data(Advertising_Handle, Operation,
                                          Data_Length, Data);
	}
    else
#endif
    {
      if(Advertising_Handle == LEGACY_ADV_HANDLE)
      {
        return ll_set_legacy_advertising_data_ptr(Data_Length, Data);
      }
      else
      {
        return ll_set_advertising_data_ptr(Advertising_Handle, Operation, Data_Length, Data);
      }
    }
  }
  else if (data_type == SCAN_RESP_DATA)
  {
    // Scan Response
#if (BLESTACK_CONTROLLER_ONLY == 0)
    if(gap)
    {
      return aci_gap_set_scan_response_data(Advertising_Handle,
                                            Data_Length, Data);
	}
    else
#endif
    {
      if(Advertising_Handle == LEGACY_ADV_HANDLE)
      {
        return ll_set_legacy_scan_reponse_data_ptr(Data_Length, Data);
      }
      else
      {
        return ll_set_scan_reponse_data_ptr(Advertising_Handle, Data_Length, Data);
      }
    }
  }
#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED == 1)
  else
  { /* data_type == PERIODIC_ADV_DATA */
    return ll_set_periodic_advertising_data_ptr(Advertising_Handle, Operation, Data_Length, Data);
  }
#else
  return BLE_ERROR_UNKNOWN_HCI_COMMAND;
#endif
}

static tBleStatus allocate_and_set_data_ext(uint8_t Advertising_Handle,
                                  uint8_t Operation, uint8_t Data_Length, uint8_t *Data, uint8_t data_type, uint8_t layer)
{
  uint8_t *buffer;
  uint16_t buff_len;
  uint8_t adv_enabled;
#if CONTROLLER_PERIODIC_ADV_ENABLED
  uint8_t periodic_adv_enabled;
#endif
  uint8_t status = BLE_ERROR_UNKNOWN_HCI_COMMAND;
  uint16_t old_buff_len;
  uint8_t extend = FALSE;

  if(Advertising_Handle == LEGACY_ADV_HANDLE && layer != LL){
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS; // This should not happen
  }

  if(data_type == ADV_DATA){
    status = adv_data_check_param(Advertising_Handle, Operation, Data_Length, &adv_enabled);
  }
  else if(data_type == SCAN_RESP_DATA){
    status = scan_resp_data_check_param(Advertising_Handle, Operation, Data_Length, &adv_enabled);
  }
#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED == 1)
  else { /* PERIODIC_ADV_DATA */
    status = periodic_adv_data_check_param(Advertising_Handle, Operation, Data_Length, &adv_enabled, &periodic_adv_enabled);
  }
#endif

  if(status)
    return status;

  /* Allocate the buffer */
  switch(Operation){

  case UNCHANGED_DATA:
    return set_data_ptr(Advertising_Handle, Operation, Data_Length, Data, data_type, layer);

  case FIRST_FRAGMENT:
  case COMPLETE_DATA:
    extend = FALSE;
    adv_buff_free_next(Advertising_Handle, data_type);
    break;

  case INTERMEDIATE_FRAGMENT:
  case LAST_FRAGMENT:
    extend = TRUE;
    break;

  }

  buffer = adv_buff_alloc(Advertising_Handle, Data_Length, extend, &old_buff_len, data_type);
  if((buffer == NULL && Data_Length != 0) || (old_buff_len + Data_Length > MAX_ADV_DATA_LENGTH)){
    // Tell the stack that current advertising data has to be cancelled.
    set_data_ptr(Advertising_Handle, COMPLETE_DATA, 0, NULL, data_type, layer);
    adv_buff_deactivate_current(Advertising_Handle, data_type);
    adv_buff_free_next(Advertising_Handle, data_type);

    return BLE_ERROR_MEMORY_CAPACITY_EXCEEDED;
  }

  memcpy(buffer + old_buff_len, Data, Data_Length);

  buff_len = old_buff_len + Data_Length;

  if(Operation == LAST_FRAGMENT || Operation == COMPLETE_DATA){
    status = set_data_ptr(Advertising_Handle, COMPLETE_DATA, buff_len, buffer, data_type, layer);
    if(status == BLE_STATUS_SUCCESS){
      adv_buff_deactivate_current(Advertising_Handle, data_type);
      adv_buff_activate_next(Advertising_Handle, data_type);
    }
    else{
      // Free what has been allocated so far for this advertising handle
      adv_buff_free_next(Advertising_Handle, data_type);
    }
  }
  else if(Operation == FIRST_FRAGMENT){
    // Discard any existing partial or complete advertising data.
    set_data_ptr(Advertising_Handle, COMPLETE_DATA, 0, NULL, data_type, layer);
    adv_buff_deactivate_current(Advertising_Handle, data_type);
  }

  return status;
}

#if (CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED == 1)
tBleStatus hci_le_set_periodic_advertising_enable_preprocess(uint8_t Enable,
                                                             uint8_t Advertising_Handle)
{
  /* If bit 0 of Enable in the HCI_LE_Set_Periodic_Advertising_Enable command is set to 1
     (periodic advertising is enabled) and the advertising set contains partial periodic
     advertising data, the Status value in the response to the command shall be
     Command Disallowed (0x0C). */
  if(((Enable & 0x01U) == 0x01U) && (new_buff_pending(Advertising_Handle, PERIODIC_ADV_DATA) == TRUE))
    return BLE_ERROR_COMMAND_DISALLOWED;

  return BLE_STATUS_SUCCESS;
}
#endif

tBleStatus hci_le_set_extended_advertising_enable_preprocess(uint8_t Enable,
                                                             uint8_t Number_of_Sets,
                                                             Advertising_Set_Parameters_t Advertising_Set_Parameters[])
{
  /*  The remainder of this section only applies if Enable is set to 0x01.
  If the advertising data or scan response data in the advertising set is not
  complete, the Controller shall return the error code Command Disallowed
  (0x0C). */
  if(Enable == 0x01){

    for(int i = 0; i < Number_of_Sets; i++){
      if(new_buff_pending(Advertising_Set_Parameters[i].Advertising_Handle, ADV_DATA) == TRUE ||
         new_buff_pending(Advertising_Set_Parameters[i].Advertising_Handle, SCAN_RESP_DATA) == TRUE)
        return BLE_ERROR_COMMAND_DISALLOWED;
    }

  }

  return BLE_STATUS_SUCCESS;
}

tBleStatus aci_gap_set_advertising_enable_preprocess(uint8_t Enable,
                                                     uint8_t Number_of_Sets,
                                                     Advertising_Set_Parameters_t Advertising_Set_Parameters[])
{
  return hci_le_set_extended_advertising_enable_preprocess(Enable, Number_of_Sets, Advertising_Set_Parameters);
}

#endif /* CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED == 0 */

tBleStatus hci_le_set_advertising_data(uint8_t Advertising_Data_Length,
                                       uint8_t Advertising_Data[31])
{
  return allocate_and_set_data(LEGACY_ADV_HANDLE, COMPLETE_DATA, Advertising_Data_Length, Advertising_Data, ADV_DATA, LL);
}

tBleStatus hci_le_set_scan_response_data(uint8_t Scan_Response_Data_Length,
                                         uint8_t Scan_Response_Data[31])
{
  return allocate_and_set_data(LEGACY_ADV_HANDLE, COMPLETE_DATA, Scan_Response_Data_Length, Scan_Response_Data, SCAN_RESP_DATA, LL);
}

tBleStatus aci_gap_set_advertising_data_nwk(uint8_t Advertising_Handle,
                                            uint8_t Operation, uint8_t Advertising_Data_Length, uint8_t *Advertising_Data)
{
  return allocate_and_set_data(Advertising_Handle,
                                Operation, Advertising_Data_Length, Advertising_Data, ADV_DATA, GAP);
}

tBleStatus aci_gap_set_scan_response_data_nwk(uint8_t Advertising_Handle,
                                              uint8_t Operation, uint8_t Scan_Response_Data_Length, uint8_t *Scan_Response_Data)
{
  return allocate_and_set_data(Advertising_Handle,
                                Operation, Scan_Response_Data_Length, Scan_Response_Data, SCAN_RESP_DATA, GAP);
}

/* --------------------- E A D --------------------- */

#if (BLESTACK_CONTROLLER_ONLY == 0)

extern void char_copy(volatile uint8_t *from, volatile uint8_t *q, size_t n);

#define ACI_EAD_PAYLOAD_CLEAR_DATA_LEN_MAX (241U)
#define ACI_EAD_PAYLOAD_ENCRY_DATA_LEN_MAX (254U)
/* the overhead for Encrypted data is given by the leading Randomizer field (5 octets)
 * and by the trailing MIC field (4 octes) */
#define ACI_EAD_PAYLOAD_OVERHEAD_SIZE      (9U)

tBleStatus aci_gap_encrypt_adv_data_nwk(uint8_t session_key[16],
                                        uint8_t iv[8],
                                        uint8_t adv_payload_data_clear_len,
                                        uint8_t adv_payload_data_clear[],
                                        uint8_t *adv_payload_data_encrypted_len,
                                        uint8_t adv_payload_data_encrypted[])
{
    uint8_t Status;

    /* Check that length of adv_payload_data_clear (declared in adv_payload_data_clear_len)
    * does not exceed 241 octets, that is an upper bound deriving from the maximum allowed length
    * of adv_payload_data_encrypted that will be returned into the HCI_Command_Complete event -
    * that has an overhead of 3+2 octets - thus with a remaining net data payload of 255 - (3+2) = 250 octets;
    * hence, considering that adv_payload_data_encrypted will carry also 2 extra fields
    * accounting for total 5+4=9 octets, then the maximum allowed length for adv_payload_data_clear is
    * 255 - (3+2) - (5+4) = 241 octets.
    */
    if ((adv_payload_data_clear_len == 0) ||
        (adv_payload_data_clear_len > ACI_EAD_PAYLOAD_CLEAR_DATA_LEN_MAX))
    {
        return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
    }

    uint32_t clear_data_aligned[((ACI_EAD_PAYLOAD_CLEAR_DATA_LEN_MAX - 1) / sizeof(uint32_t))+1] = { 0U };
    char_copy((uint8_t *)adv_payload_data_clear, (uint8_t *)clear_data_aligned, adv_payload_data_clear_len);

    Status = aci_gap_encrypt_adv_data(session_key /* 16 */,
                                      iv /* 8 */,
                                      adv_payload_data_clear_len,
                                      clear_data_aligned,
                                      adv_payload_data_encrypted);

    if (Status == BLE_STATUS_SUCCESS)
    {
        /* the size of returned field adv_payload_data_encrypted is 9 octets longer
        * w.r.t. adv_payload_data_clear since it contains 2 more fields:
        * - the Randomizer (5 octets in front of payload), and
        * - the MIC (4 octets appended as a footer).
        */
        *adv_payload_data_encrypted_len = adv_payload_data_clear_len + 9U;
    }
    else
    {
        *adv_payload_data_encrypted_len = 0U;
    }

    return Status;
}

tBleStatus aci_gap_decrypt_adv_data_nwk(uint8_t session_key[16],
                                        uint8_t iv[8],
                                        uint8_t adv_payload_data_encrypted_len,
                                        uint8_t adv_payload_data_encrypted[],
                                        uint8_t *adv_payload_data_clear_len,
                                        uint8_t adv_payload_data_clear[])
{
    uint8_t Status;

    /* Check that length of adv_payload_data_encrypted (declared in adv_payload_data_encrypted_len)
     * does not exceed 254 octets, that is an upper bound deriving from the Core Spec v.5.x, Part C, Sec. 11,
     * where the Length field in the ADV header has a size of 1 octet.
     */
    if (adv_payload_data_encrypted_len > ACI_EAD_PAYLOAD_ENCRY_DATA_LEN_MAX)
    {
        return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
    }

    uint32_t clear_data_aligned[((ACI_EAD_PAYLOAD_ENCRY_DATA_LEN_MAX - ACI_EAD_PAYLOAD_OVERHEAD_SIZE -1) / sizeof(uint32_t))+1] = { 0U };

    Status = aci_gap_decrypt_adv_data(session_key,
                                      iv,
                                      adv_payload_data_encrypted_len,
                                      adv_payload_data_encrypted,
                                      clear_data_aligned);

    if (Status == BLE_STATUS_SUCCESS)
    {
        /* returned adv_payload_data_clear is 9 octets shorter w.r.t. adv_payload_data_encrypted
        * since it doesn't contain the 2 extra fields attached to encryped data, i.e.:
        * - the Randomizer (5 octets in front of payload), and
        * - the MIC (4 octets appended as a footer).
        */
        *adv_payload_data_clear_len = adv_payload_data_encrypted_len - ACI_EAD_PAYLOAD_OVERHEAD_SIZE;
        char_copy((uint8_t *)clear_data_aligned, (uint8_t *)adv_payload_data_clear, (*adv_payload_data_clear_len));
    }
    else
    {
        *adv_payload_data_clear_len = 0U;
    }

    return Status;
}

#endif

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
