/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    aci_adv_nwk.h
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

#ifndef ACI_ADV_NWK_H
#define ACI_ADV_NWK_H

#include "ble.h"

/** Documentation for C struct Subevent_Data_Parameters_t */
typedef struct Subevent_Data_Parameters_t_s {
  /** The subevent index of the data.
   *  Values:
   *  - 0x00 ... 0x7F
   */
  uint8_t Subevent;
  /** The first response slots to be used in this subevent.
   */
  uint8_t Response_Slot_Start;
  /** The number of response slots to be used.
   */
  uint8_t Response_Slot_Count;
  /** The number of octets in the Subevent_Data parameter.
   *  Values:
   *  - 0x00 ... 0xFB
   */
  uint8_t Subevent_Data_Length;
  /** Advertising data formatted as defined in [Vol 3] Part C, Section 11.
   */
  uint8_t *Subevent_Data;
} Subevent_Data_Parameters_t;

void aci_adv_nwk_init(void);

tBleStatus aci_gap_set_advertising_data_nwk(uint8_t Advertising_Handle,
                                            uint8_t Operation,
                                            uint8_t Advertising_Data_Length,
                                            uint8_t *Advertising_Data);

tBleStatus aci_gap_set_scan_response_data_nwk(uint8_t Advertising_Handle,
                                              uint8_t Operation,
                                              uint8_t Scan_Response_Data_Length,
                                              uint8_t *Scan_Response_Data);

tBleStatus hci_le_set_advertising_data(uint8_t Advertising_Data_Length,
                                       uint8_t Advertising_Data[31]);

tBleStatus hci_le_set_scan_response_data(uint8_t Scan_Response_Data_Length,
                                         uint8_t Scan_Response_Data[31]);

tBleStatus hci_le_set_extended_advertising_data(uint8_t Advertising_Handle,
                                                uint8_t Operation,
                                                uint8_t Fragment_Preference,
                                                uint8_t Advertising_Data_Length,
                                                uint8_t *Advertising_Data);

tBleStatus hci_le_set_extended_scan_response_data(uint8_t Advertising_Handle,
                                                  uint8_t Operation,
                                                  uint8_t Fragment_Preference,
                                                  uint8_t Scan_Response_Data_Length,
                                                  uint8_t *Scan_Response_Data);

tBleStatus hci_le_set_periodic_advertising_data(uint8_t Advertising_Handle,
                                                uint8_t Operation,
                                                uint8_t Advertising_Data_Length,
                                                uint8_t Advertising_Data[]);

tBleStatus hci_le_set_periodic_advertising_subevent_data(uint8_t Advertising_Handle,
                                                         uint8_t Num_Subevents,
                                                         Subevent_Data_Parameters_t Subevent_Data_Parameters[]);

tBleStatus hci_le_set_periodic_advertising_response_data(uint16_t Sync_Handle,
                                                         uint16_t Request_Event,
                                                         uint8_t Request_Subevent,
                                                         uint8_t Response_Subevent,
                                                         uint8_t Response_Slot,
                                                         uint8_t Response_Data_Length,
                                                         uint8_t Response_Data[]);

tBleStatus aci_gap_encrypt_adv_data_nwk(uint8_t session_key[16],
                                        uint8_t iv[8],
                                        uint8_t adv_payload_data_len,
                                        uint8_t adv_payload_data_clear[],
                                        uint8_t *adv_payload_data_encrypted_len,
                                        uint8_t adv_payload_data_encrypted[]);

tBleStatus aci_gap_decrypt_adv_data_nwk(uint8_t session_key[16],
                                        uint8_t iv[8],
                                        uint8_t adv_payload_encrypted_data_len,
                                        uint8_t adv_payload_encrypted_data[],
                                        uint8_t *adv_payload_clear_data_len,
                                        uint8_t adv_payload_clear_data[]);

#endif /* ACI_ADV_NWK_H */
