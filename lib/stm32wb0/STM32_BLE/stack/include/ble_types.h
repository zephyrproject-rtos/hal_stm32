/**
  ******************************************************************************
  * @file    ble_types.h
  * @author  GPM WBL Application Team
  * @brief   Header file for Bluetooth Low Energy stack types.
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
#ifndef _BLE_TYPES_H_
#define _BLE_TYPES_H_

#include <stdint.h>

/** Documentation for C struct Handle_Packets_Pair_Entry_t */
typedef PACKED(struct) packed_Handle_Packets_Pair_Entry_t_s {
  /** Connection handle
   */
  uint16_t Connection_Handle;
  /** The number of HCI Data Packets that have been completed (transmitted or flushed)
   *  for the associated Connection_Handle since the previous time the event was
   *  returned.
   */
  uint16_t HC_Num_Of_Completed_Packets;
} packed_Handle_Packets_Pair_Entry_t;

/** Documentation for C struct Attribute_Group_Handle_Pair_t */
typedef PACKED(struct) packed_Attribute_Group_Handle_Pair_t_s {
  /** Found Attribute handle
   */
  uint16_t Found_Attribute_Handle;
  /** Group End handle
   */
  uint16_t Group_End_Handle;
} packed_Attribute_Group_Handle_Pair_t;

/** Documentation for C struct Advertising_Report_t */
typedef PACKED(struct) packed_Advertising_Report_t_s {
  /** Type of advertising report event: ADV_IND: Connectable undirected advertising',
   *  ADV_DIRECT_IND: Connectable directed advertising, ADV_SCAN_IND: Scannable
   *  undirected advertising, ADV_NONCONN_IND: Non connectable undirected
   *  advertising, SCAN_RSP: Scan response.
   *  Values:
   *  - 0x00: ADV_IND
   *  - 0x01: ADV_DIRECT_IND
   *  - 0x02: ADV_SCAN_IND
   *  - 0x03: ADV_NONCONN_IND
   *  - 0x04: SCAN_RSP
   */
  uint8_t Event_Type;
  /** 0x00 Public Device Address 0x01 Random Device Address 0x02 Public Identity
   *  Address (Corresponds to Resolved Private Address) 0x03 Random (Static)
   *  Identity Address (Corresponds to Resolved Private Address)
   *  Values:
   *  - 0x00: Public Device Address
   *  - 0x01: Random Device Address
   *  - 0x02: Public Identity Address
   *  - 0x03: Random (Static) Identity Address
   */
  uint8_t Address_Type;
  /** Public Device Address, Random Device Address, Public Identity Address or Random
   *  (static) Identity Address of the advertising device.
   */
  uint8_t Address[6];
  /** Length of the Data[i] field for each device which responded.
   *  Values:
   *  - 0 ... 31
   */
  uint8_t Data_Length;
  /** Data_Length octets of advertising or scan response data formatted as defined in
   *  [Vol 3] Part C, Section 8, plus one byte for RSSI (signed integer, dBm units).
   */
  uint8_t Data_RSSI[0];
} packed_Advertising_Report_t;

/** Documentation for C struct Direct_Advertising_Report_t */
typedef PACKED(struct) packed_Direct_Advertising_Report_t_s {
  /** Advertising type
   *  Values:
   *  - 0x01: Connectable directed advertising (ADV_DIRECT_IND)
   */
  uint8_t Event_Type;
  /** 0x00 Public Device Address 0x01 Random Device Address 0x02 Public Identity
   *  Address (Corresponds to Resolved Private Address) 0x03 Random (Static)
   *  Identity Address (Corresponds to Resolved Private Address)
   *  Values:
   *  - 0x00: Public Device Address
   *  - 0x01: Random Device Address
   *  - 0x02: Public Identity Address
   *  - 0x03: Random (Static) Identity Address
   */
  uint8_t Address_Type;
  /** Public Device Address, Random Device Address, Public Identity Address or Random
   *  (static) Identity Address of the advertising device.
   */
  uint8_t Address[6];
  /** 0x01 Random Device Address
   *  Values:
   *  - 0x01: Random Device Address
   */
  uint8_t Direct_Address_Type;
  /** Random Device Address
   */
  uint8_t Direct_Address[6];
  /** N Size: 1 Octet (signed integer) Units: dBm
   *  Values:
   *  - -127 ... 20
   *  - 127: RSSI not available
   */
  int8_t RSSI;
} packed_Direct_Advertising_Report_t;

/** Documentation for C struct Extended_Advertising_Report_t */
typedef PACKED(struct) packed_Extended_Advertising_Report_t_s {
  /** Event Type parameter. Bits from 0 to 4: 0 Connectable advertising 1 Scannable
   *  advertising 2 Directed advertising 3 Scan response 4 Legacy advertising
   *  PDUs used Bits 5-6 Data status: 00b = Complete 01b = Incomplete, more data
   *  to come 10b = Incomplete, data truncated, no more to come 11b = Reserved
   *  for future use
   *  Flags:
   *  - 0x0001: Connectable advertising
   *  - 0x0002: Scannable advertising
   *  - 0x0004: Directed advertising
   *  - 0x0008: Scan response
   *  - 0x0010: Legacy advertising PDUs used
   */
  uint16_t Event_Type;
  /** Address Type
   *  Values:
   *  - 0x00: Public Device Address
   *  - 0x01: Random Device Address
   *  - 0x02: Public Identity Address (corresponds to Resolved Private Address)
   *  - 0x03: Random (static) Identity Address (corresponds to Resolved Private
Address)
   *  - 0xFF: No address provided (anonymous advertisement)
   */
  uint8_t Address_Type;
  /** Public Device Address, Random Device Address, Public Identity Address or Random
   *  (static) Identity Address of the advertising device.
   */
  uint8_t Address[6];
  /** PHY used to send the advertising PDU on the primary advertising physical
   *  channel.
   *  Values:
   *  - 0x01: LE_1M_PHY
   *  - 0x03: LE_CODED_PHY
   */
  uint8_t Primary_PHY;
  /** This parameter indicates the PHY used to send the advertising PDU(s), if any, on
   *  the secondary advertising physical channel.
   *  Values:
   *  - 0x00: No packets
   *  - 0x01: LE_1M_PHY
   *  - 0x02: LE_2M_PHY
   *  - 0x03: LE_CODED_PHY
   */
  uint8_t Secondary_PHY;
  /** Advertising SID subfield in the ADI field of the PDU
   *  Values:
   *  - 0x00 ... 0x0F
   *  - 0xFF: NA
   */
  uint8_t Advertising_SID;
  /** Tx Power. Units: dBm.
   *  Values:
   *  - -127 ... 126
   *  - 127: NA
   */
  int8_t TX_Power;
  /** RSSI value; Units: dBm; All other values Reserved for future use.
   *  Values:
   *  - -127 ... 20
   *  - 127: NA
   */
  int8_t RSSI;
  /** Interval of the periodic advertising. Time = N * 1.25 ms; Time Range: 7.5 ms to
   *  81,918.75 s.
   *  Values:
   *  - 0x0000 (NaN) : NA
   *  - 0x0006 (7.50 ms)  ... 0xFFFF (NaN)
   */
  uint16_t Periodic_Advertising_Interval;
  /** Direct address type
   *  Values:
   *  - 0x00: Public Device Address
   *  - 0x01: Random Device Address
   *  - 0x02: Public Identity Address (Corresponds to Resolved PrivateAddress)
   *  - 0x03: Random (static) Identity Address (Corresponds to Resolved PrivateAddress)
   *  - 0x04 ... 0xFD: Reserved for future use
   *  - 0xFE: Random Device Address (Controller unable to resolve)
   *  - 0xFF: Reserved for future use
   */
  uint8_t Direct_Address_Type;
  /** Public Device Address, Random Device Address, Public Identity Address or Random
   *  (static) Identity Address of the target device
   */
  uint8_t Direct_Address[6];
  /** Length of the Data[i] field for each device which responded
   *  Values:
   *  - 0 ... 229
   */
  uint8_t Data_Length;
  /** Data_Length[i] octets of advertising or scan response data formatted as defined
   *  in [Vol 3] Part C, Section 11. Note: Each element of this array has a
   *  variable length.
   */
  uint8_t Data[0];
} packed_Extended_Advertising_Report_t;

/** Documentation for C struct Samples_t */
typedef PACKED(struct) packed_Samples_t_s {
  /** The list of I samples for the reported packet. Each sample is a signed integer.
   *  The list is in the order of the sampling points within the packet.
   */
  int8_t I_Sample;
  /** The list of Q samples for the reported packet. Each sample is a signed integer.
   *  The list is in the order of the sampling points within the packet.
   */
  int8_t Q_Sample;
} packed_Samples_t;

/** Documentation for C struct Periodic_Advertising_Response_t */
typedef PACKED(struct) packed_Periodic_Advertising_Response_t_s {
  /** Range: -127 to +20 (units: dBm). If 0x7F, Tx Power information is not available.
   *  Values:
   *  - -127 ... 20
   *  - 127: NA
   */
  int8_t TX_Power;
  /** Range: -127 to +20 (units: dBm) If 0x7F, RSSI is not available.
   *  Values:
   *  - -127 ... 20
   *  - 127: NA
   */
  int8_t RSSI;
  /** CTE type in the response.
   *  Values:
   *  - 0x00: AoA
   *  - 0x01: AoD_1us
   *  - 0x02: AoD_2us
   *  - 0xFF: NO_CTE
   */
  uint8_t CTE_Type;
  /** The response slot the data was received in.
   */
  uint8_t Response_Slot;
  /** 0x00: Data complete 0x01: Data incomplete, more data to come 0xFF: Failed to
   *  receive an AUX_SYNC_SUBEVENT_RSP PDU
   *  Values:
   *  - 0x00: DATA_COMPLETE
   *  - 0x01: MORE_DATA
   *  - 0xFF: RX_FAILED
   */
  uint8_t Data_Status;
  /** Length of the Data field.
   */
  uint8_t Data_Length;
  /** Periodic advertising response data formatted as defined in [Vol 3] Part C,
   *  Section 11. Note: Each element of this array has a variable length.
   */
  uint8_t Data[0];
} packed_Periodic_Advertising_Response_t;

#endif /* _BLE_TYPES_H_ */
