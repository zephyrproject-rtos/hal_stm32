/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dtm_cmds.c
  * @author  GPM WBL Application Team
  * @brief   DTM specific commands to be implemented on DTM context (not present on BLE stack)
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
#include "ble_stack.h"
#include "dtm_cmd_db.h"
#include "transport_layer.h"
#include "adv_buff_alloc.h"
#include "adv_buff_alloc_tiny.h"
#include "ble_const.h"
#include "dtm_burst.h"
#include "app_ble.h"
#include "app_common.h"

#ifndef MIN
#   define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifdef WATCHDOG
#include "rf_driver_ll_iwdg.h"
#endif

/* Private macro -------------------------------------------------------------*/
/** @name BLE stack v3.1 stack modular configurations bitmap
  * @{
  */
#define CONTROLLER_PRIVACY_BIT                 ((uint32_t)0x00000001)  /*!< Bit  0 selected */
#define SECURE_CONNECTIONS_BIT                 ((uint32_t)0x00000002)  /*!< Bit  1 selected */
/* Observer (scanner) or Central role support:
   -  Observer disabled (CONTROLLER_SCAN_BIT = 0) or enabled (CONTROLLER_SCAN_BIT = 1) if CONNECTION_BIT = 0;
   -  Observer and Central disabled (CONTROLLER_SCAN_BIT = 0) or enabled (CONTROLLER_SCAN_BIT = 1) if CONNECTION_BIT = 1.
*/
#define CONTROLLER_SCAN_BIT                  ((uint32_t)0x00000004)  /*!< Bit  2 selected */
#define CONTROLLER_DATA_LENGTH_EXTENSION_BIT   ((uint32_t)0x00000008)  /*!< Bit  3 selected */
#define LINK_LAYER_ONLY_BIT                    ((uint32_t)0x00000010)  /*!< Bit  4 selected */
#define CONTROLLER_2M_CODED_PHY_BIT            ((uint32_t)0x00000020)  /*!< Bit  5 selected */
#define CONTROLLER_EXT_ADV_SCAN_BIT            ((uint32_t)0x00000040)  /*!< Bit  6 selected */
#define L2CAP_COS_BIT                          ((uint32_t)0x00000080)  /*!< Bit  7 selected */
#define CONTROLLER_PERIODIC_ADV_BIT            ((uint32_t)0x00000100)  /*!< Bit  8 selected */
#define CONTROLLER_CTE_BIT                     ((uint32_t)0x00000200)  /*!< Bit  9 selected */
#define CONTROLLER_POWER_CONTROL_BIT           ((uint32_t)0x00000400)  /*!< Bit 10 selected */
/* Support to connections:
   - If CONNECTION_BIT = 0, connections are not supported;
     device is a broadcaster-only if CONTROLLER_SCAN_BIT = 0,
     or a broadcaster and observer if CONTROLLER_SCAN_BIT = 1.
   - If CONNECTION_BIT = 1, connections are supported;
     device can only act as broadcaster or peripheral if CONTROLLER_SCAN_BIT = 0,
     or any role (broadcaster, observer, peripheral, and central) if CONTROLLER_SCAN_BIT = 1.
*/
#define CONNECTION_BIT                         ((uint32_t)0x00000800)  /*!< Bit 11 selected */
#define CONTROLLER_ONLY_BIT                    ((uint32_t)0x00001000)  /*!< Bit 12 selected */
#define CONTROLLER_CHAN_CLASS_BIT              ((uint32_t)0x00010000)  /*!< Bit 16 selected */
#define CONTROLLER_BIS_BIT                     ((uint32_t)0x00020000)  /*!< Bit 17 selected */
#define CONNECTION_SUBRATING_BIT               ((uint32_t)0x00080000)  /*!< Bit 19 selected */
#define CONTROLLER_CIS_BIT                     ((uint32_t)0x00100000)  /*!< Bit 20 selected */
#define CONTROLLER_PERIODIC_ADV_WR_BIT         ((uint32_t)0x00400000)  /*!< Bit 22 selected */
/**
  * @}
  */

/** @brief Link Layer Enabled or not based on LL_ONLY and BLESTACK_CONTROLLER_ONLY preprocessor options */
#ifndef BLESTACK_CONTROLLER_ONLY
#define BLESTACK_CONTROLLER_ONLY (0U)
#endif
#if (BLESTACK_CONTROLLER_ONLY == 1U)
#define LINK_LAYER_ONLY_ENABLED (1U)
#else
#define LINK_LAYER_ONLY_ENABLED (0U)
#endif

/** @brief Define BLE stack configurations variant bitmap value based on enabled BLE stack options and associated bits (LSB 5 bits) */
#define BLE_STACK_CONFIGURATIONS_VARIANT (                                                          \
    ((uint32_t)(CONTROLLER_PRIVACY_ENABLED * CONTROLLER_PRIVACY_BIT))                             | \
    ((uint32_t)(SECURE_CONNECTIONS_ENABLED * SECURE_CONNECTIONS_BIT))                             | \
    ((uint32_t)(CONTROLLER_SCAN_ENABLED * CONTROLLER_SCAN_BIT))                               | \
    ((uint32_t)(CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED * CONTROLLER_DATA_LENGTH_EXTENSION_BIT)) | \
    ((uint32_t)(LINK_LAYER_ONLY_ENABLED * LINK_LAYER_ONLY_BIT))                                   | \
    ((uint32_t)(CONTROLLER_2M_CODED_PHY_ENABLED * CONTROLLER_2M_CODED_PHY_BIT))                   | \
    ((uint32_t)(CONTROLLER_EXT_ADV_SCAN_ENABLED * CONTROLLER_EXT_ADV_SCAN_BIT))                   | \
    ((uint32_t)(L2CAP_COS_ENABLED * L2CAP_COS_BIT))                                               | \
    ((uint32_t)(CONTROLLER_PERIODIC_ADV_ENABLED * CONTROLLER_PERIODIC_ADV_BIT))                   | \
    ((uint32_t)(CONTROLLER_CTE_ENABLED * CONTROLLER_CTE_BIT))                                     | \
    ((uint32_t)(CONTROLLER_POWER_CONTROL_ENABLED * CONTROLLER_POWER_CONTROL_BIT))                 | \
    ((uint32_t)(CONNECTION_ENABLED * CONNECTION_BIT))                                             | \
    ((uint32_t)(BLESTACK_CONTROLLER_ONLY * CONTROLLER_ONLY_BIT))                                  | \
    ((uint32_t)(CONTROLLER_CHAN_CLASS_ENABLED * CONTROLLER_CHAN_CLASS_BIT))                       | \
    ((uint32_t)(CONTROLLER_BIS_ENABLED * CONTROLLER_BIS_BIT))                                     | \
    ((uint32_t)(CONNECTION_SUBRATING_ENABLED * CONNECTION_SUBRATING_BIT))                         | \
    ((uint32_t)(CONTROLLER_CIS_ENABLED * CONTROLLER_CIS_BIT))                                     | \
    ((uint32_t)(CONTROLLER_PERIODIC_ADV_WR_ENABLED * CONTROLLER_PERIODIC_ADV_WR_BIT))               \
)

tBleStatus aci_hal_get_firmware_details(uint8_t *DTM_version_major,
                                        uint8_t *DTM_version_minor,
                                        uint8_t *DTM_version_patch,
                                        uint8_t *DTM_variant,
                                        uint16_t *DTM_Build_Number,
                                        uint8_t *BTLE_Stack_version_major,
                                        uint8_t *BTLE_Stack_version_minor,
                                        uint8_t *BTLE_Stack_version_patch,
                                        uint8_t *BTLE_Stack_development,
                                        uint16_t *BTLE_Stack_variant,
                                        uint16_t *BTLE_Stack_Build_Number)
{
  tBleStatus ret;
  uint32_t BTLE_Stack_variant_ext;

  ret = aci_hal_get_firmware_details_v2(DTM_version_major,DTM_version_minor,DTM_version_patch,
                                         DTM_variant,DTM_Build_Number,BTLE_Stack_version_major,
                                         BTLE_Stack_version_minor,BTLE_Stack_version_patch,
                                         BTLE_Stack_development,&BTLE_Stack_variant_ext,
                                         BTLE_Stack_Build_Number);
  *BTLE_Stack_variant = BTLE_Stack_variant_ext;

  return ret;
}

tBleStatus aci_hal_get_firmware_details_v2(uint8_t *DTM_version_major,
                                           uint8_t *DTM_version_minor,
                                           uint8_t *DTM_version_patch,
                                           uint8_t *DTM_variant,
                                           uint16_t *DTM_Build_Number,
                                           uint8_t *BTLE_Stack_version_major,
                                           uint8_t *BTLE_Stack_version_minor,
                                           uint8_t *BTLE_Stack_version_patch,
                                           uint8_t *BTLE_Stack_development,
                                           uint32_t *BTLE_Stack_variant,
                                           uint16_t *BTLE_Stack_Build_Number)
{

    aci_hal_get_fw_build_number(BTLE_Stack_Build_Number);
    uint8_t HCI_Version = 0;
    uint16_t HCI_Revision = 0;
    uint8_t LMP_PAL_Version = 0;
    uint16_t Manufacturer_Name = 0;
    uint16_t LMP_PAL_Subversion = 0;

    hci_read_local_version_information(&HCI_Version, &HCI_Revision, &LMP_PAL_Version,
                                       &Manufacturer_Name, &LMP_PAL_Subversion);

    *DTM_version_major  = DTM_FW_VERSION_MAJOR;
    *DTM_version_minor  = DTM_FW_VERSION_MINOR;
    *DTM_version_patch  = DTM_FW_VERSION_PATCH;
    *DTM_variant = DTM_VARIANT;
    *DTM_Build_Number = 0;
    *BTLE_Stack_version_major = HCI_Revision&0x0F;
    *BTLE_Stack_version_minor = (LMP_PAL_Subversion>>4)&0x0F;
    *BTLE_Stack_version_patch = LMP_PAL_Subversion&0x0F;
    *BTLE_Stack_development = (LMP_PAL_Subversion>>15)&0x01;

    /* Set the stack configurations variant bitmap value:
       first LSB 7 bits are reserved for BLE stack modular options + Link Layer only*/
    *BTLE_Stack_variant = BLE_STACK_CONFIGURATIONS_VARIANT;

    return (BLE_STATUS_SUCCESS);

}

/**
 * @brief  This API implements the hci le transmitter test with
 *         the capability to set the number of packets to be sent.
 * @param  TX_Frequency: TX frequency
 * @param  Length_Of_Test_Data: length of test data
 * @param  Packet_Payload: packet payload
 * @param  Number_Of_Packets: number pf packets to be sent on test
 * @param  PHY: PHY to be used by the transmitter
 * @retval status
*/
tBleStatus aci_hal_transmitter_test_packets(uint8_t TX_Frequency,
                                            uint8_t Length_Of_Test_Data,
                                            uint8_t Packet_Payload,
                                            uint16_t Number_Of_Packets,
                                            uint8_t PHY)
{
  extern uint16_t num_packets;
  tBleStatus status;

  if(Number_Of_Packets == 0)
  {
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
  }

#if CONTROLLER_2M_CODED_PHY_ENABLED

  status =  hci_le_transmitter_test_v2(TX_Frequency,
                                       Length_Of_Test_Data,
                                       Packet_Payload,
                                       PHY);

#else

  status = hci_le_transmitter_test(TX_Frequency /* 1 */,
                                   Length_Of_Test_Data /* 1 */,
                                   Packet_Payload /* 1 */);
#endif

  if(status == 0x00)
  {
    num_packets = Number_Of_Packets;
  }

  return status;
}

#if CONTROLLER_CTE_ENABLED
/**
 * @brief  This API implements the hci le transmitter test v2 with
 *         the capability to set the number of packets to be sent.
 * @param  TX_Channel: TX channel
 * @param  Test_Data_Length: length of test data
 * @param  Packet_Payload: packet payload
 * @param  Number_Of_Packets: number of packets to be sent on test
 * @param  PHY: PHY to be used by the transmitter
 * @param  CTE_Length: CTE length
 * @param  CTE_Type: CTE type
 * @param  Switching_Pattern_Length: switching pattern length
 * @param  Antenna_IDs: antenna ids
 * @param  Transmit_Power_Level: tx power level
 * @retval status
*/
tBleStatus aci_hal_transmitter_test_packets_v2(uint8_t TX_Channel,
                                               uint8_t Test_Data_Length,
                                               uint8_t Packet_Payload,
                                               uint16_t Number_Of_Packets,
                                               uint8_t PHY,
                                               uint8_t CTE_Length,
                                               uint8_t CTE_Type,
                                               uint8_t Switching_Pattern_Length,
                                               uint8_t Antenna_IDs[])
{
  extern uint16_t num_packets;
  tBleStatus status;

  if(Number_Of_Packets == 0)
  {
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
  }

  status =  hci_le_transmitter_test_v3(TX_Channel,
                                       Test_Data_Length,
                                       Packet_Payload,
                                       PHY,
                                       CTE_Length,
                                       CTE_Type,
                                       Switching_Pattern_Length,
                                       Antenna_IDs);

  if(status == 0x00)
  {
    num_packets = Number_Of_Packets;
  }

  return status;
}
#endif

#if (CONNECTION_ENABLED == 1) && (BLESTACK_CONTROLLER_ONLY==0)

tBleStatus aci_test_tx_notification_start(uint16_t Connection_Handle, uint16_t Service_Handle, uint16_t Char_Handle, uint16_t Value_Length)
{
  return BURST_TXNotificationStart(Connection_Handle, Service_Handle, Char_Handle, Value_Length);
}

tBleStatus aci_test_tx_write_command_start(uint16_t Connection_Handle, uint16_t Attr_Handle, uint16_t Value_Length)
{
  return BURST_TXWriteCommandStart(Connection_Handle, Attr_Handle, Value_Length);
}

tBleStatus aci_test_rx_start(uint16_t Connection_Handle, uint16_t Attribute_Handle, uint8_t Notifications_WriteCmds)
{
  return BURST_RXStart(Connection_Handle, Attribute_Handle, Notifications_WriteCmds);
}

tBleStatus aci_test_stop(uint8_t TX_RX)
{
  switch(TX_RX){
  case 0:
    BURST_TXStop();
    break;
  case 1:
    BURST_RXStop();
    break;
  default:
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
  }

  return BLE_STATUS_SUCCESS;
}

tBleStatus aci_test_report(uint32_t *TX_Packets, uint32_t *RX_Packets, uint16_t *RX_Data_Length, uint32_t *RX_Sequence_Errors)
{
  *TX_Packets = BURST_TXReport();
  *RX_Packets = BURST_RXReport(RX_Data_Length, RX_Sequence_Errors);

  return BLE_STATUS_SUCCESS;
}

#endif

tBleStatus aci_hal_write_radio_reg(uint32_t Start_Address,
                                   uint8_t Num_Bytes,
                                   uint8_t Data[])
{
    uint32_t *address = (uint32_t *)Start_Address;

    if (((Num_Bytes & 0x03U) != 0x00U) ||
        ((Start_Address & 0x03U) != 0x00U))
    {
        return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
    }

    for (uint32_t word = 0; word < ((uint32_t)Num_Bytes >> 2); word++)
    {
        uint32_t tmp_word = 0x00000000;
        for (int byte = 3; byte >= 0; byte--)
        {
            tmp_word <<= 8;
            tmp_word |= Data[word * 4U + (uint32_t)byte];
        }
        address[word] = tmp_word;
    }

    return BLE_STATUS_SUCCESS;
}

tBleStatus aci_hal_read_radio_reg(uint32_t Start_Address,
                                  uint8_t Num_Bytes,
                                  uint8_t *Data_Length,
                                  uint8_t Data[])
{
    uint32_t *address = (uint32_t *)Start_Address;

    if (((Num_Bytes & 0x03U) != 0x00U) ||
        ((Start_Address & 0x03U) != 0x00U))
    {
        return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
    }

    ATOMIC_SECTION_BEGIN();
    for (uint32_t word = 0; word < ((uint32_t)Num_Bytes >> 2); word++)
    {
        uint32_t tmp_word = address[word];
        for (int byte = 0; byte < 4; byte++)
        {
            Data[word * 4U + (uint32_t)byte] = (uint8_t)(tmp_word & 0x000000FFU);
            tmp_word >>= 8;
        }
    }
    ATOMIC_SECTION_END();
    * Data_Length = Num_Bytes;

    return BLE_STATUS_SUCCESS;
}
