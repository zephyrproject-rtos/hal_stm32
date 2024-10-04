/**
  ******************************************************************************
  * @file    ble_const.h
  * @author  GPM WBL Application Team
  * @brief   Header file that includes Bluetooth LE stack defines for APIs
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

#ifndef __BLE_CONST_H__
#define __BLE_CONST_H__

#include "ble_gatt.h"
#include "uuid.h"
#include "compiler.h"
/**
 *@addtogroup HCI HCI
 *@{
 */

/**
 * @defgroup Link_Layer Link Layer constants and types
 * @brief Constants and types related to Link Layer functions
 * @{
 */

/* Macros for Enable parameters in HCI commands. */
#define HCI_DISABLE                                    0x00
#define HCI_ENABLE                                     0x01

#define BD_ADDR_SIZE                                   0x06U

/* Address types */
#define HCI_ADDR_PUBLIC                                0x00U
#define HCI_ADDR_RANDOM_ADDR                           0x01U
#define HCI_ADDR_STATIC_RANDOM_ADDR                    0x01U
#define HCI_ADDR_RESOLVABLE_PRIVATE_ADDR               0x02U
#define HCI_ADDR_NON_RESOLVABLE_PRIVATE_ADDR           0x03U

/* HCI_LE_Set_Advertising_Parameters: Advertising_Type */
#define HCI_ADV_TYPE_ADV_IND                           0x00U
#define HCI_ADV_TYPE_ADV_DIRECT_IND_HDC                0x01U
#define HCI_ADV_TYPE_ADV_SCAN_IND                      0x02U
#define HCI_ADV_TYPE_ADV_NONCONN_IND                   0x03U
#define HCI_ADV_TYPE_ADV_DIRECT_IND_LDC                0x04U

/* HCI_LE_Set_Advertising_Parameters: Advertising_Filter_Policy */
#define HCI_ADV_FILTER_NONE                            0x00U
#define HCI_ADV_FILTER_ACCEPT_LIST_SCAN                0x01U
#define HCI_ADV_FILTER_ACCEPT_LIST_CONNECT             0x02U
#define HCI_ADV_FILTER_ACCEPT_LIST_SCAN_CONNECT        0x03U

#define HCI_ADV_CH_37                                  0x01U
#define HCI_ADV_CH_38                                  0x02U
#define HCI_ADV_CH_39                                  0x04U
#define HCI_ADV_CH_ALL                                 0x07U

/* HCI_LE_Set_[Advertising/Scan]_Parameters: Own_Address_Type */
#define HCI_OWN_ADDR_TYPE_PUBLIC                       0x00U
#define HCI_OWN_ADDR_TYPE_RANDOM                       0x01U
#define HCI_OWN_ADDR_TYPE_RP_OR_PUBLIC                 0x02U
#define HCI_OWN_ADDR_TYPE_RP_OR_RANDOM                 0x03U

/* HCI_LE_Set_Scan_Parameters: LE_Scan_Type */
#define HCI_SCAN_TYPE_PASSIVE                          0x00U
#define HCI_SCAN_TYPE_ACTIVE                           0x01U

/* HCI_LE_Set_Scan_Parameters: Scanning_Filter_Policy */
#define HCI_SCAN_FILTER_BASIC_UNFILTERED               0x00U
#define HCI_SCAN_FILTER_BASIC_FILTERED                 0x01U
#define HCI_SCAN_FILTER_EXTENDED_UNFILTERED            0x02U
#define HCI_SCAN_FILTER_EXTENDED_FILTERED              0x03U

/* HCI_LE_Create_Connection: Initiator_Filter_Policy */
#define HCI_INIT_FILTER_ACCEPT_LIST_NONE               0x00U
#define HCI_INIT_FILTER_ACCEPT_LIST                    0x01U

/* HCI_LE_Read_PHY: TX_PHY */
#define HCI_TX_PHY_LE_1M                               0x01U
#define HCI_TX_PHY_LE_2M                               0x02U
#define HCI_TX_PHY_LE_CODED                            0x03U

/* HCI_LE_Read_PHY: RX_PHY */
#define HCI_RX_PHY_LE_1M                               0x01U
#define HCI_RX_PHY_LE_2M                               0x02U
#define HCI_RX_PHY_LE_CODED                            0x03U

/* HCI_LE_Set_PHY: ALL_PHYS */
#define HCI_ALL_PHYS_TX_NO_PREF                        0x01U
#define HCI_ALL_PHYS_RX_NO_PREF                        0x02U

/* HCI_LE_Set_PHY: TX_PHYS */
#define HCI_TX_PHYS_LE_1M_PREF                         0x01U
#define HCI_TX_PHYS_LE_2M_PREF                         0x02U
#define HCI_TX_PHYS_LE_CODED_PREF                      0x04U

/* HCI_LE_Set_PHY: RX_PHYS */
#define HCI_RX_PHYS_LE_1M_PREF                         0x01U
#define HCI_RX_PHYS_LE_2M_PREF                         0x02U
#define HCI_RX_PHYS_LE_CODED_PREF                      0x04U

/* HCI_LE_Set_Extended_Advertising_Parameters: Advertising_Event_Properties */
#define HCI_ADV_EVENT_PROP_NONE                        0x0000U
#define HCI_ADV_EVENT_PROP_CONNECTABLE                 0x0001U
#define HCI_ADV_EVENT_PROP_SCANNABLE                   0x0002U
#define HCI_ADV_EVENT_PROP_DIRECTED                    0x0004U
#define HCI_ADV_EVENT_PROP_HDC_DIRECTED                0x0008U
#define HCI_ADV_EVENT_PROP_LEGACY                      0x0010U
#define HCI_ADV_EVENT_PROP_ANONYMOUS                   0x0020U
#define HCI_ADV_EVENT_PROP_TXPOWER_INC                 0x0040U

/* HCI_LE_Set_Extended_Advertising_Parameters: Primary_Advertising_PHY and Secondary_Advertising_PHY */
#define HCI_ADV_PHY_LE_1M                      0x01U
#define HCI_ADV_PHY_LE_2M                      0x02U
#define HCI_ADV_PHY_LE_CODED                   0x03U

/* HCI_LE_Set_Extended_Advertising_Data: Operation */
#define HCI_SET_ADV_DATA_OPERATION_INTERMEDIATE        0x00U
#define HCI_SET_ADV_DATA_OPERATION_FIRST               0x01U
#define HCI_SET_ADV_DATA_OPERATION_LAST                0x02U
#define HCI_SET_ADV_DATA_OPERATION_COMPLETE            0x03U
#define HCI_SET_ADV_DATA_OPERATION_UNCHANGED           0x04U

/* HCI_LE_Advertising_Report: Event_Type */
#define HCI_ADV_EVT_TYPE_ADV_IND                       0x00U
#define HCI_ADV_EVT_TYPE_ADV_DIRECT_IND                0x01U
#define HCI_ADV_EVT_TYPE_ADV_SCAN_IND                  0x02U
#define HCI_ADV_EVT_TYPE_ADV_NONCONN_IND               0x03U
#define HCI_ADV_EVT_TYPE_SCAN_RSP                      0x04U

/* HCI_LE_Extended_Advertising_Report: Event_Type */
#define HCI_EXT_ADV_EVT_TYPE_CONNECTABLE               0x0001U
#define HCI_EXT_ADV_EVT_TYPE_SCANNABLE                 0x0002U
#define HCI_EXT_ADV_EVT_TYPE_DIRECTED                  0x0004U
#define HCI_EXT_ADV_EVT_TYPE_SCAN_RESP                 0x0008U
#define HCI_EXT_ADV_EVT_TYPE_LEGACY                    0x0010U
#define HCI_EXT_ADV_EVT_TYPE_DATA_STATUS_MASK          0x0060U
#define HCI_EXT_ADV_EVT_TYPE_DATA_STATUS_COMPLETE      0x0000U
#define HCI_EXT_ADV_EVT_TYPE_DATA_STATUS_MORE_DATA     0x0020U
#define HCI_EXT_ADV_EVT_TYPE_DATA_STATUS_TRUNCATED     0x0040U

/* HCI_LE_Set_Extended_Scan_Parameters: Scanning_PHYs */
#define HCI_SCANNING_PHYS_LE_1M                        0x01U
#define HCI_SCANNING_PHYS_LE_CODED                     0x04U

/* HCI_LE_Extended_Create_Connection: Initiating_PHYs */
#define HCI_INIT_PHYS_SCAN_CONN_LE_1M                  0x01U
#define HCI_INIT_PHYS_CONN_LE_2M                       0x02U
#define HCI_INIT_PHYS_SCAN_CONN_LE_CODED               0x04U

/* HCI_LE_Receiver_Test/HCI_LE_Transmitter_Test [v2]: PHY */
#define HCI_TEST_PHY_LE_1M                             0x01U
#define HCI_TEST_PHY_LE_2M                             0x02U

/* HCI_LE_Connection_Complete/HCI_LE_Enhanced_Connection_Complete: Role */
#define HCI_ROLE_CENTRAL                               0x00U
#define HCI_ROLE_PERIPHERAL                            0x01U

/* HCI_LE_Set_Privacy_Mode: Privacy_Mode */
#define HCI_PRIV_MODE_NETWORK                          0x00U
#define HCI_PRIV_MODE_DEVICE                           0x01U

/* HCI_LE_Periodic_Advertising_Report: Data_Status */
#define HCI_PADV_DATA_STATUS_COMPLETE                  0x00U
#define HCI_PADV_DATA_STATUS_MORE_DATA                 0x01U
#define HCI_PADV_DATA_STATUS_TRUNCATED                 0x02U
#define HCI_PADV_DATA_STATUS_FAILED                    0xFFU


/**
 * @name Duplicate filtering
 * @{
 */
#define DUPLICATE_FILTER_DISABLED                   0
#define DUPLICATE_FILTER_ENABLED                    1
#define DUPLICATE_FILTER_ENABLED_FOR_SCAN_PERIOD    2
/**
 * @}
 */

/**
 * @name Bitmasks for Link Layer PHYs
 * @{
 */
#define LE_1M_PHY_BIT       0x01
#define LE_2M_PHY_BIT       0x02
#define LE_CODED_PHY_BIT    0x04

/**
 * @}
 */

/**
 * @name Values for Link Layer PHYs
 * @{
 */
#define HCI_PHY_LE_1M                   0x01
#define HCI_PHY_LE_2M                   0x02
#define HCI_PHY_LE_CODED                0x03
#define HCI_PHY_LE_CODED_S8             0x03
#define HCI_PHY_LE_CODED_S2             0x04

/**
 * @}
 */

/**
 * @name Link Layer State
 * @{
 */
#define LL_IDLE         0x00
#define LL_ADV          0x01
#define LL_CONN_SLAVE   0x02
#define LL_SCAN         0x03
#define LL_CONN_REQ     0x04
#define LL_CONN_MASTER  0x05
#define LL_TX_TEST      0x06
#define LL_RX_TEST      0x07
/**
 * @}
 */

/**
 * @name CTE Type
 * @{
 */
#define CTE_AOA         0x00
#define CTE_AOD_1us     0x01
#define CTE_AOD_2us     0x02
/**
 * @}
 */

/**
 * @name CTE Type bitmask
 * @{
 */
#define CTE_AOA_BIT         0x01
#define CTE_AOD_1us_BIT     0x02
#define CTE_AOD_2us_BIT     0x04
/**
 * @}
 */

/**
 * @name CTE Slot Duration
 * @{
 */
#define CTE_SLOT_1us        0x01
#define CTE_SLOT_2us        0x02
/**
 * @}
 */

/**
 * @name Reason for hci_le_transmit_power_reporting_event()
 * @{
 */
#define LOCAL_TX_POWER_CHANGE               0x00
#define REMOTE_TX_POWER_CHANGE              0x01
#define READ_REMOTE_TX_POWER_COMPLETE       0x02
/**
 * @}
 */

/**
 * @name Transmit_Power_Level value
 * @{
 */
#define POWER_NOT_MANAGED                   0x7E
#define POWER_NA                            0x7F
/**
 * @}
 */

/**
 * @name Transmit_Power_Level_Flag values
 * @{
 */
#define MIN_TX_POWER_BIT                    0x01
#define MAX_TX_POWER_BIT                    0x02
/**
 * @}
 */

/**
 * @name LE Event Mask
 * @see hci_le_set_event_mask()
 * @{
 */
#define HCI_LE_EVT_MASK_BYTE0_CONNECTION_COMPLETE                                         (0x01U)
#define HCI_LE_EVT_MASK_BYTE0_ADVERTISING_REPORT                                          (0x02U)
#define HCI_LE_EVT_MASK_BYTE0_CONNECTION_UPDATE_COMPLETE                                  (0x04U)
#define HCI_LE_EVT_MASK_BYTE0_READ_REMOTE_FEATURES_COMPLETE                               (0x08U)
#define HCI_LE_EVT_MASK_BYTE0_LTK_REQUEST                                                 (0x10U)
#define HCI_LE_EVT_MASK_BYTE0_REMOTE_CONNECTION_PARAMETER_REQUEST                         (0x20U)
#define HCI_LE_EVT_MASK_BYTE0_DATA_LEN_CHANGE                                             (0x40U)
#define HCI_LE_EVT_MASK_BYTE0_READ_LOCAL_P256_COMPLETE                                    (0x80U)
#define HCI_LE_EVT_MASK_BYTE1_GENERATE_DHKEY_COMPLETE                                     (0x01U)
#define HCI_LE_EVT_MASK_BYTE1_ENHANCED_CONNECTION_COMPLETE                                (0x02U)
#define HCI_LE_EVT_MASK_BYTE1_DIRECTED_ADVERTISING_REPORT                                 (0x04U)
#define HCI_LE_EVT_MASK_BYTE1_PHY_UPDATE_COMPLETE                                         (0x08U)
#define HCI_LE_EVT_MASK_BYTE1_EXTENDED_ADVERTISING_REPORT                                 (0x10U)
#define HCI_LE_EVT_MASK_BYTE1_PERIODIC_ADVERTISING_SYNC_ESTABLISHED                       (0x20U)
#define HCI_LE_EVT_MASK_BYTE1_PERIODIC_ADVERTISING_REPORT                                 (0x40U)
#define HCI_LE_EVT_MASK_BYTE1_PERIODIC_ADVERTISING_SYNC_LOST                              (0x80U)
#define HCI_LE_EVT_MASK_BYTE2_SCAN_TIMEOUT                                                (0x01U)
#define HCI_LE_EVT_MASK_BYTE2_ADVERTISING_SET_TERMINATED                                  (0x02U)
#define HCI_LE_EVT_MASK_BYTE2_SCAN_REQUEST_RECEIVED                                       (0x04U)
#define HCI_LE_EVT_MASK_BYTE2_CHANNEL_SELECTION_ALGORITHM                                 (0x08U)
#define HCI_LE_EVT_MASK_BYTE2_CONNECTIONLESS_IQ_REPORT                                    (0x10U)
#define HCI_LE_EVT_MASK_BYTE2_CONNECTION_IQ_REPORT                                        (0x20U)
#define HCI_LE_EVT_MASK_BYTE2_CTE_REQUEST_FAILED                                          (0x40U)
#define HCI_LE_EVT_MASK_BYTE2_PERIODIC_ADVERTISING_SYNC_TRANSFER                          (0x80U)
#define HCI_LE_EVT_MASK_BYTE3_CIS_ESTABLISHED                                             (0x01U)
#define HCI_LE_EVT_MASK_BYTE3_CIS_REQUEST                                                 (0x02U)
#define HCI_LE_EVT_MASK_BYTE3_CREATE_BIG_COMPLETE                                         (0x04U)
#define HCI_LE_EVT_MASK_BYTE3_TERMINATE_BIG_COMPLETE                                      (0x08U)
#define HCI_LE_EVT_MASK_BYTE3_BIG_SYNC_ESTABLISHED                                        (0x10U)
#define HCI_LE_EVT_MASK_BYTE3_BIG_SYNC_LOST                                               (0x20U)
#define HCI_LE_EVT_MASK_BYTE3_REQUEST_PEER_SCA_COMPLETE                                   (0x40U)
#define HCI_LE_EVT_MASK_BYTE3_PATH_LOSS_THRESHOLD                                         (0x80U)
#define HCI_LE_EVT_MASK_BYTE4_TRANSMIT_POWER_REPORTING                                    (0x01U)
#define HCI_LE_EVT_MASK_BYTE4_BIG_INFO_ADVERTISING_REPORT                                 (0x02U)
#define HCI_LE_EVT_MASK_BYTE4_SUBRATE_CHANGE                                              (0x04U)
#define HCI_LE_EVT_MASK_BYTE4_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V2                    (0x08U)
#define HCI_LE_EVT_MASK_BYTE4_PERIODIC_ADVERTISING_REPORT_V2                              (0x10U)
#define HCI_LE_EVT_MASK_BYTE4_PERIODIC_ADVERTISING_SYNC_TRANSFER_V2                       (0x20U)
#define HCI_LE_EVT_MASK_BYTE4_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQ                      (0x40U)
#define HCI_LE_EVT_MASK_BYTE4_PERIODIC_ADVERTISING_RESPONSE_REPORT                        (0x80U)
#define HCI_LE_EVT_MASK_BYTE5_ENHANCED_CONNECTION_COMPLETE_V2                             (0x01U)

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 *@addtogroup HAL_LL HAL/LL
 *@{
 */
/**
 *@addtogroup HAL_constants HAL/LL Constants
 *@brief Constants for Hardware abstraction Layer and Link Layer.
 *@{
 */

/**
 * @name Configuration values.
 * See @ref aci_hal_write_config_data() and @ref aci_hal_read_config_data().
 * @{
 */
#define CONFIG_DATA_PUBADDR_OFFSET                  (0x00) /**< Bluetooth public address */
#define CONFIG_DATA_ER_OFFSET                       (0x08) /**< Encryption root key used to derive LTK and CSRK */
#define CONFIG_DATA_IR_OFFSET                       (0x18) /**< Identity root key used to derive LTK and CSRK */
#define CONFIG_DATA_LL_WITHOUT_HOST                 (0x2C) /**< Switch on/off Link Layer only mode. Set to 1 to disable Host.
                           It can be written only if aci_hal_write_config_data() is the first command
                           after reset. */
#define CONFIG_DATA_STATIC_RANDOM_ADDRESS           (0x2E) /**< To set the static random address used by the stack, instead of the one stored in NVM. */
#define CONFIG_DATA_SCAN_CH_MAP                     (0x2F) /**< To set the channel map for scanning. */
#define CONFIG_DATA_STORED_STATIC_RANDOM_ADDRESS    (0x80) /**< The static random address stored in NVM. */
#define CONFIG_DATA_DEBUG_KEY                       (0xD0) /**< Use debug key for secure connections. */
#define CONFIG_DATA_DLE                             (0xD1) /**< To set the maximum allowed parameter values for Data Length Extension */
/**
 * @}
 */

/**
 * @name Length for configuration values.
 * See @ref aci_hal_write_config_data() and @ref aci_hal_read_config_data().
 * @{
 */
#define CONFIG_DATA_PUBADDR_LEN                 (6)
#define CONFIG_DATA_ER_LEN                      (16)
#define CONFIG_DATA_IR_LEN                      (16)
#define CONFIG_DATA_LL_WITHOUT_HOST_LEN         (1)
#define CONFIG_DATA_STATIC_RANDOM_ADDRESS_LEN   (6)
#define CONFIG_DATA_SCAN_CH_MAP_LEN             (1)
#define CONFIG_DATA_DEBUG_KEY_LEN               (1)
#define CONFIG_DATA_DLE_LEN                     (1)
/**
 * @}
 */


/**
 * @name Types for fw error event
 * @brief See aci_hal_fw_error_event().
 * @{
 */

#define HAL_FW_L2CAP_RECOMBINATION_ERROR            0x01 /**< L2CAP layer failed recombining a PDU */
#define HAL_FW_GATT_UNEXPECTED_RESPONSE_ERROR       0x02 /**< GATT layer received an unexpteced response. Peer probably violated the ATT protocol. */
#define HAL_FW_GATT_SEQUENTIAL_PROTOCOL_ERROR       0x03 /**< GATT layer received an unexpteced request. Peer probably violated the sequentiality of ATT protocol. */
#define HAL_FW_BONDING_DB_FULL_GATTSERVICE_ERROR    0x04 /**< No space to store info GATT database info in NVM. Database needs to be cleaned up (remove invalidated records) or some bonding entries need to be removed. */
#define HAL_FW_BONDING_DB_FULL_PAIRING_ERROR        0x05 /**< No space to store bonding info in NVM. Database needs to be cleaned up (remove invalidated records) or some bonding entries need to be removed. */
#define HAL_FW_SCHEDULER_OVERRUN_ERROR              0x06 /**< Link Layer scheduler failed to reschedule slots for too many times. This may indicate an unrecoverable situation. A system reset is recommended. */
#define HAL_FW_MEMBUF_NOT_AVAILABLE                 0x07 /**< Out of memory resources for isochronous channels. */
#define HAL_FW_CTE_TIMER_PROGRAM_ERROR              0x08 /**< Error in programming timer for CTE reception functionality. */
#define HAL_FW_MBM_RESOURCE_MISS                    0x09 /**< Requested resources are not available. */

/**
 * @}
 */

 /**
 * @name Types for aci_hal_pawr_data_free_event()
 * @brief See aci_hal_pawr_data_free_event().
 * @{
 */

#define HAL_PAWR_DATA_TYPE_SUBEVENT                 0x00 /**< PAwR subevevent data */
#define HAL_PAWR_DATA_TYPE_RESPONSE                 0x01 /**< PAwR response data */

/**
 * @}
 */

/**
 * @}
 */
/**
 * @}
 */


/**
 *@addtogroup GAP GAP
 *@brief Generic Access Profile
 *@{
 */

/**
 *@addtogroup GAP_constants GAP Constants
 *@brief Constants for GAP layer
 *@{
 */

/**
 * @name Characteristic value lengths
 * @{
 */
#define APPEARANCE_CHAR_LEN                     (2)
#define PERIPHERAL_PREFERRED_CONN_PARAMS_CHAR_LEN (8)
#define CENTRAL_ADDRESS_RESOLUTION_CHAR_LEN         (1)
/**
 * @}
 */

/**
 * @name AD Types
 * @brief AD types for adv data and scan response data
 * @{
 */

#define AD_TYPE_FLAGS                   (0x01)

#define AD_TYPE_16_BIT_SERV_UUID          (0x02)
#define AD_TYPE_16_BIT_SERV_UUID_CMPLT_LIST     (0x03)
#define AD_TYPE_32_BIT_SERV_UUID                (0x04)
#define AD_TYPE_32_BIT_SERV_UUID_CMPLT_LIST     (0x05)
#define AD_TYPE_128_BIT_SERV_UUID               (0x06)
#define AD_TYPE_128_BIT_SERV_UUID_CMPLT_LIST    (0x07)

#define AD_TYPE_SHORTENED_LOCAL_NAME            (0x08)
#define AD_TYPE_COMPLETE_LOCAL_NAME             (0x09)

/** TX power level AD type*/
#define AD_TYPE_TX_POWER_LEVEL                  (0x0A)

/** Class of device */
#define AD_TYPE_CLASS_OF_DEVICE                 (0x0D)

/** Security manager TK value AD type */
#define AD_TYPE_SEC_MGR_TK_VALUE                (0x10)

/** Security manager OOB flags */
#define AD_TYPE_SEC_MGR_OOB_FLAGS               (0x11)

/** Slave connection interval AD type */
#define AD_TYPE_SLAVE_CONN_INTERVAL             (0x12)

#define AD_TYPE_SERV_SOLICIT_16_BIT_UUID_LIST   (0x14)
#define AD_TYPE_SERV_SOLICIT_32_BIT_UUID_LIST   (0x1F)
#define AD_TYPE_SERV_SOLICIT_128_BIT_UUID_LIST  (0x15)

#define AD_TYPE_16_BIT_UUID_SERVICE_DATA        (0x16)
#define AD_TYPE_32_BIT_UUID_SERVICE_DATA        (0x20)
#define AD_TYPE_128_BIT_UUID_SERVICE_DATA       (0x21)

/** Manufaturer specific data AD type */
#define AD_TYPE_MANUFACTURER_SPECIFIC_DATA      (0xFF)

/**
 * @}
 */

/**
 * @name Flags AD Type bits
 * @brief Bits for Flags AD Type
 * @{
 */
#define FLAG_BIT_LE_LIMITED_DISCOVERABLE_MODE   (0x01)
#define FLAG_BIT_LE_GENERAL_DISCOVERABLE_MODE   (0x02)
#define FLAG_BIT_BR_EDR_NOT_SUPPORTED           (0x04)
#define FLAG_BIT_LE_BR_EDR_CONTROLLER           (0x08)
#define FLAG_BIT_LE_BR_EDR_HOST                 (0x10)
/**
 * @}
 */


/**
 * @name GAP modes
 * @{
 */
#define GAP_MODE_NON_DISCOVERABLE             0
#define GAP_MODE_LIMITED_DISCOVERABLE         1
#define GAP_MODE_GENERAL_DISCOVERABLE         2
#define GAP_MODE_BROADCAST                    3
/**
 * @}
 */

/**
 * @name Privacy type
 * @{
 */
#define PRIVACY_DISABLED                        (0x00)
#define PRIVACY_HOST_ENABLED                    (0x01)
#define PRIVACY_CONTROLLER_ENABLED              (0x02)
/**
 * @}
 */

/**
 * @name Operation
 * Values for Operation parameter (see aci_gap_set_advertising_data()).
 * @{
 */
#define ADV_COMPLETE_DATA           (0x03)
#define ADV_UNCHANGED_DATA            (0x04)
/**
 * @}
 */

/**
 * @name Recommended advertising intervals
 * Intervals in terms of 625 micro seconds
 * @{
 */
#define GAP_ADV_INT_MIN_USER_INITIATED_CONN          (48)   /* 30 ms  */
#define GAP_ADV_INT_MAX_USER_INITIATED_CONN          (96)   /* 60 ms  */
#define GAP_ADV_INT_MIN_USER_INITIATED_NONCONN       (160)  /* 100 ms */
#define GAP_ADV_INT_MAX_USER_INITIATED_NONCONN       (240)  /* 150 ms */
#define GAP_ADV_INT_MIN_BACKGROUND                   (1600) /* 1 s    */
#define GAP_ADV_INT_MAX_BACKGROUND                   (1920) /* 1.2 s  */
/**
 * @}
 */

/**
 * @anchor gap_roles
 * @name GAP Roles
 * @{
*/
#define GAP_PERIPHERAL_ROLE                     (0x01)
#define GAP_BROADCASTER_ROLE                    (0x02)
#define GAP_CENTRAL_ROLE                        (0x04)
#define GAP_OBSERVER_ROLE                       (0x08)
/**
 * @}
 */

/**
 * @anchor gap_procedure_codes
 * @name GAP procedure codes
 * Procedure codes for aci_gap_start_procedure()
 * and aci_gap_terminate_proc() commands.
 * @{
 */
#define GAP_LIMITED_DISCOVERY_PROC                  (0x00)
#define GAP_GENERAL_DISCOVERY_PROC                  (0x01)
#define GAP_AUTO_CONNECTION_ESTABLISHMENT_PROC      (0x02)
#define GAP_GENERAL_CONNECTION_ESTABLISHMENT_PROC   (0x03)
#define GAP_SELECTIVE_CONNECTION_ESTABLISHMENT_PROC (0x04)
#define GAP_OBSERVATION_PROC                        (0x05)
#define GAP_DIRECT_CONNECTION_ESTABLISHMENT_PROC    (0x06)
#define GAP_NAME_DISCOVERY_PROC                     (0x07)

/**
 * @}
 */

/**
 * @anchor gap_appearance_values
 * @name GAP Appearance values
 * Values for GAP Appearance characteristic.
 * @{
 */
#define GAP_APPEARANCE_UNKNOWN                                 0x0000
#define GAP_APPEARANCE_GENERIC_PHONE                           0x0040
#define GAP_APPEARANCE_GENERIC_COMPUTER                        0x0080
#define GAP_APPEARANCE_GENERIC_WATCH                           0x00C0
#define GAP_APPEARANCE_WATCH_SPORT_WATCH                       0x00C1
#define GAP_APPEARANCE_GENERIC_CLOCK                           0x0100
#define GAP_APPEARANCE_GENERIC_DISPLAY                         0x0140
#define GAP_APPEARANCE_GENERIC_REMOTE_CONTROL                  0x0180
#define GAP_APPEARANCE_GENERIC_EYE_GLASSES                     0x01C0
#define GAP_APPEARANCE_GENERIC_TAG                             0x0200
#define GAP_APPEARANCE_GENERIC_KEYRING                         0x0240
#define GAP_APPEARANCE_GENERIC_MEDIA_PLAYER                    0x0280
#define GAP_APPEARANCE_GENERIC_BARCODE_SCANNER                 0x02C0
#define GAP_APPEARANCE_GENERIC_THERMOMETER                     0x0300
#define GAP_APPEARANCE_THERMOMETER_EAR                         0x0301
#define GAP_APPEARANCE_GENERIC_HEART_RATE_SENSOR               0x0340
#define GAP_APPEARANCE_HEART_RATE_SENSOR_HEART_RATE_BELT       0x0341
#define GAP_APPEARANCE_GENERIC_BLOOD_PRESSURE                  0x0380
#define GAP_APPEARANCE_BLOOD_PRESSURE_ARM                      0x0381
#define GAP_APPEARANCE_BLOOD_PRESSURE_WRIST                    0x0382
#define GAP_APPEARANCE_HUMAN_INTERFACE_DEVICE                  0x03C0
#define GAP_APPEARANCE_KEYBOARD                                0x03C1
#define GAP_APPEARANCE_MOUSE                                   0x03C2
#define GAP_APPEARANCE_JOYSTICK                                0x03C3
#define GAP_APPEARANCE_GAMEPAD                                 0x03C4
#define GAP_APPEARANCE_DIGITIZER_TABLET                        0x03C5
#define GAP_APPEARANCE_CARD_READER                             0x03C6
#define GAP_APPEARANCE_DIGITAL_PEN                             0x03C7
#define GAP_APPEARANCE_BARCODE_SCANNER                         0x03C8
#define GAP_APPEARANCE_GENERIC_GLUCOSE_METER                   0x0400
#define GAP_APPEARANCE_GENERIC_RUNNING_WALKING_SENSOR          0x0440
#define GAP_APPEARANCE_RUNNING_WALKING_IN_SHOE                 0x0441
#define GAP_APPEARANCE_RUNNING_WALKING_ON_SHOE                 0x0442
#define GAP_APPEARANCE_RUNNING_WALKING_ON_HIP                  0x0443
#define GAP_APPEARANCE_GENERIC_CYCLING                         0x0480
#define GAP_APPEARANCE_CYCLING_CYCLING_COMPUTER                0x0481
#define GAP_APPEARANCE_CYCLING_SPEED_SENSOR                    0x0482
#define GAP_APPEARANCE_CYCLING_CADENCE_SENSOR                  0x0483
#define GAP_APPEARANCE_CYCLING_POWER_SENSOR                    0x0484
#define GAP_APPEARANCE_CYCLING_SPEED_AND_CADENCE_SENSOR        0x0485
#define GAP_APPEARANCE_GENERIC_PULSE_OXYMETER                  0x0C40
#define GAP_APPEARANCE_FINGERTIP                               0x0C41
#define GAP_APPEARANCE_WRIST_WORN                              0x0C42
#define GAP_APPEARANCE_GENERIC_WEIGHT_SCALE                    0x0C80
#define GAP_APPEARANCE_GENERIC_OUTDOOR_SPORT_ACTIVITY          0x1440
#define GAP_APPEARANCE_LOCATION_DISPLAY_DEVICE                 0x1441
#define GAP_APPEARANCE_LOCATION_AND_NAVIGATION_DISPLAY_DEVICE  0x1442
#define GAP_APPEARANCE_LOCATION_POD                            0x1443
#define GAP_APPEARANCE_LOCATION_AND_NAVIGATION_POD             0x1444
#define GAP_APPEARANCE_GENERIC_ENVIRONMENTAL_SENSOR            0x1640

/**
 * @}
 */

/**
 * @anchor IO_capabilities
 * @name IO capabilities
 * @{
 */
#define GAP_IO_CAP_DISPLAY_ONLY                                 0x00
#define GAP_IO_CAP_DISPLAY_YES_NO                               0x01
#define GAP_IO_CAP_KEYBOARD_ONLY                                0x02
#define GAP_IO_CAP_NO_INPUT_NO_OUTPUT                           0x03
#define GAP_IO_CAP_KEYBOARD_DISPLAY                             0x04
/**
 * @}
 */

/**
 * @anchor Auth_req
 * @name Authentication requirements
 * @{
 */
#define BONDING                (0x01)
#define NO_BONDING         (0x00)
/**
 * @}
 */

/**
 * @anchor MITM_req
 * @name MITM protection requirements
 * @{
 */
#define GAP_MITM_PROTECTION_NOT_REQUIRED                        0x00
#define GAP_MITM_PROTECTION_REQUIRED                            0x01
/**
 * @}
 */

/**
 * @anchor OOB_Data
 * @name Out-Of-Band data
 * @{
 */
#define OOB_AUTH_DATA_ABSENT     (0x00)
#define OOB_AUTH_DATA_PRESENT        (0x01)
/**
 * @}
 */

/**
 * @anchor Author_req
 * @name Authorization requirements
 * @{
 */
#define AUTHORIZATION_NOT_REQUIRED    (0x00)
#define AUTHORIZATION_REQUIRED      (0x01)
/**
 * @}
 */

/**
 * @anchor Conn_authorization
 * @name Connection authorization
 * @{
 */
#define CONNECTION_AUTHORIZED     (0x01)
#define CONNECTION_REJECTED     (0x02)
/**
 * @}
 */

/**
 * @anchor link_security_status
 * @name Link security status
 * @{
 */
#define SM_LINK_AUTHENTICATED               (0x01)
#define SM_LINK_AUTHORIZED                  (0x02)
#define SM_LINK_ENCRYPTED                   (0x04)
/**
 * @}
 */

/**
 * @anchor SMP_pairing_failed_codes
 * @name SMP pairing failed reason codes
 * @{
 */
#define PASSKEY_ENTRY_FAILED      (0x01)
#define OOB_NOT_AVAILABLE     (0x02)
#define AUTH_REQ_CANNOT_BE_MET      (0x03)
#define CONFIRM_VALUE_FAILED      (0x04)
#define PAIRING_NOT_SUPPORTED     (0x05)
#define INSUFF_ENCRYPTION_KEY_SIZE    (0x06)
#define CMD_NOT_SUPPORTED     (0x07)
#define UNSPECIFIED_REASON      (0x08)
#define VERY_EARLY_NEXT_ATTEMPT     (0x09)
#define SM_INVALID_PARAMS     (0x0A)
/**
 * @}
 */

/**
 * @anchor pairing_failed_codes
 * @name Pairing failed error codes
 * Error codes in @ref aci_gap_pairing_complete_event event
 * @{
 */
#define SM_PAIRING_SUCCESS              (0x00)
#define SM_PAIRING_TIMEOUT              (0x01)
#define SM_PAIRING_FAILED               (0x02)
/**
 * @}
 */

/**
 * @anchor secure_connections_support
 * @name Secure connection support option code
 * Error codes in @ref aci_gap_set_authentication_requirement API
 * @{
 */
#define GAP_SC_NOT_SUPPORTED (0x00) /* Not supported */
#define GAP_SC_OPTIONAL      (0x01) /* Supported but optional (i.e. a Legacy Pairing may be accepted) */
#define GAP_SC_MANDATORY     (0x02) /* Supported but mandatory (i.e. do not accept Legacy Pairing but only Secure Connections v.4.2 Pairing) */

/**
 * @}
 */

/**
 * @anchor keypress_support
 * @name Secure connection key press notification option code
 * Error codes in @ref aci_gap_set_authentication_requirement API
 * @{
 */
#define GAP_KEYPRESS_NOT_SUPPORTED (0x00)
#define GAP_KEYPRESS_SUPPORTED     (0x01)

/**
 * @}
 */

/**
 * @anchor gap_pairing_resp
 * @name Values for Pairing_Response parameter of aci_gap_set_security_requirements
 * @{
 */
#define GAP_PAIRING_RESP_NONE                   (0x00)
#define GAP_PAIRING_RESP_FOR_BONDED_DEVICES     (0x01)
#define GAP_PAIRING_RESP_FOR_ALL                (0x02)


/**
 * @}
 */

 /**
 * @anchor gap_security_level
 * @name Values for Security_Level parameter of aci_gap_set_security
 * @{
 */
#define GAP_SECURITY_LEVEL_1                   	(0x01)
#define GAP_SECURITY_LEVEL_2                  	(0x02)
#define GAP_SECURITY_LEVEL_3                   	(0x03)
#define GAP_SECURITY_LEVEL_4                   	(0x04)


/**
 * @}
 */


/**
 * @}
 */

/**
 * @}
 */

/**
 *@addtogroup GATT GATT
 *@{
 */
/**
 *@defgroup GATT_constants GATT Constants
 *@{
 */

/**
 * @anchor Access_permissions
 * @name Access permissions
 * Access permissions for an attribute
 * @{
 */
#define ATTR_NO_ACCESS                             (0x00)
#define ATTR_ACCESS_READ_ONLY                      (0x01)
#define ATTR_ACCESS_WRITE_REQ_ONLY                 (0x02)
#define ATTR_ACCESS_READ_WRITE                     (0x03)
#define ATTR_ACCESS_WRITE_WITHOUT_RESPONSE         (0x04)
#define ATTR_ACCESS_SIGNED_WRITE_ALLOWED           (0x08)
/**
 * Allows all write procedures
 */
#define ATTR_ACCESS_WRITE_ANY                      (0x0E)
/**
 * @}
 */

/**
 * @anchor Char_properties
 * @name Characteristic properties.
 * @{
 */
#define CHAR_PROP_BROADCAST               (0x01)
#define CHAR_PROP_READ          (0x02)
#define CHAR_PROP_WRITE_WITHOUT_RESP      (0x04)
#define CHAR_PROP_WRITE                     (0x08)
#define CHAR_PROP_NOTIFY              (0x10)
#define CHAR_PROP_INDICATE              (0x20)
#define CHAR_PROP_SIGNED_WRITE                          (0x40)
#define CHAR_PROP_EXT                             (0x80)
/**
 * @}
 */


/**
 * @anchor Security_permissions
 * @name Security permissions for an attribute.
 * @{
 */
#define ATTR_PERMISSION_NONE                       (0x00) /**< No security. */
#define ATTR_PERMISSION_AUTHEN_READ                (0x01) /**< Need authentication to read */
#define ATTR_PERMISSION_AUTHOR_READ                (0x02) /**< Need authorization to read */
#define ATTR_PERMISSION_ENCRY_READ                 (0x04) /**< Link must be encrypted to read */
#define ATTR_PERMISSION_AUTHEN_WRITE               (0x08) /**< Need authentication to write */
#define ATTR_PERMISSION_AUTHOR_WRITE               (0x10) /**< Need authorization to write */
#define ATTR_PERMISSION_ENCRY_WRITE                (0x20) /**< Link must be encrypted for write */
/**
 * @}
 */

/**
 * @anchor UUID_Types
 * @name Type of UUID (16 bit or 128 bit).
 * @{
 */
#define UUID_TYPE_16                               (0x01)
#define UUID_TYPE_128                              (0x02)
/**
 * @}
 */

/**
 * @anchor Service_type
 * @name Type of service (primary or secondary)
 * @{
 */
#define PRIMARY_SERVICE                            (0x01)
#define SECONDARY_SERVICE                          (0x02)
/**
 * @}
 */

/**
 * @anchor Notification_type
 * @name Type of notification
 * @{
 */
#define GATT_NOTIFICATION                          (0x00)
#define GATT_INDICATION                            (0x02)
/**
 * @}
 */

/**
 * @anchor Gatt_Event_Mask
 * @name Gatt Event Mask
 * Type of event generated by GATT server
 * @{
 */
#define GATT_DONT_NOTIFY_EVENTS                       (0x00) /**< Do not notify events. */
#define GATT_NOTIFY_ATTRIBUTE_WRITE                   (0x01) /**< The application will be notified when a client writes to this attribute.
                                                                  An @ref aci_gatt_srv_attribute_modified_event will be issued. */
#define GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP  (0x02) /**< The application will be notified when a write request, a write cmd
                                                                    or a signed write cmd are received by the server for this attribute.*/
#define GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP   (0x04) /**< The application will be notified when a read request of any type is
                                                                  received for this attribute. */
/**
 * @}
 */

/**
 * @name Type of characteristic length
 * See aci_gatt_add_char()
 * @{
 */
#define CHAR_VALUE_LEN_CONSTANT           (0x00)
#define CHAR_VALUE_LEN_VARIABLE           (0x01)
/**
 * @}
 */


/**
 * @name Encryption key size
 * @{
 */
/**
 * Minimum encryption key size
 */
#define MIN_ENCRY_KEY_SIZE                (7)

/**
 * Maximum encryption key size
 */
#define MAX_ENCRY_KEY_SIZE                (0x10)
/**
 * @}
 */

/**
 * @name Characteristic Presentation Format
 * @{
 */
typedef PACKED(struct) _charactFormat {
    uint8_t format;
    int8_t exp;
    uint16_t unit;
    uint8_t name_space;
    uint16_t desc;
} charactFormat;

/**
 * @}
 */

/**
 * @name Format
 * @{
 */
#define FORMAT_UINT8         0x04
#define FORMAT_UINT16        0x06
#define FORMAT_SINT16        0x0E
#define FORMAT_SINT24        0x0F
/**
 * @}
 */

/**
 * @name Unit
 * @{
 */
#define UNIT_UNITLESS        0x2700
#define UNIT_TEMP_CELSIUS    0x272F
#define UNIT_PRESSURE_BAR    0x2780
/**
 * @}
 */


/**
 * @}
 */
/**
 * @}
 */


/**
 *@addtogroup L2CAP L2CAP
 *@{
 */
/**
 *@addtogroup L2CAP_constants L2CAP Constants
 *@brief Constants for L2CAP layer.
 *@{
 */

/**
 *@name L2CAP Connection Event Type
 *@see aci_l2cap_cfc_connection_event
 *@{
 */
#define L2CAP_CONN_REQ                 0
#define L2CAP_CONN_RESP                1
/**
 *@}
 */

#define L2CAP_CHANNEL_TYPE_LE_CFC 0x00
#define L2CAP_CHANNEL_TYPE_ECFC   0x01

#define L2CAP_CONN_SUCCESSFUL                           0x0000
#define L2CAP_CONN_FAIL_SPSM_NOT_SUPPORTED              0x0002
#define L2CAP_CONN_FAIL_INSUFFICIENT_RESOURCES          0x0004
#define L2CAP_CONN_FAIL_INSUFFICIENT_AUTHENTICATION     0x0005
#define L2CAP_CONN_FAIL_INSUFFICIENT_AUTHORIZATION      0x0006
#define L2CAP_CONN_FAIL_KEY_SIZE_TOO_SHORT              0x0007
#define L2CAP_CONN_FAIL_INSUFFICIENT_ENCRYPTION         0x0008
#define L2CAP_CONN_FAIL_INVALID_SOURCE_CID              0x0009
#define L2CAP_CONN_FAIL_SOURCE_CID_ALREADY_ALLOCATED    0x000A
#define L2CAP_CONN_FAIL_UNACCEPTABLE_PARAMETERS         0x000B
#define L2CAP_CONN_FAIL_INVALID_PARAMETERS              0x000C
#define L2CAP_CONN_FAIL_NO_INFO                         0x000D
#define L2CAP_CONN_FAIL_AUTHENTICATION_PENDING          0x000E
#define L2CAP_CONN_FAIL_AUTHORIZATION_PENDING           0x000F

#define L2CAP_CFC_MANUAL                                0x00
#define L2CAP_CFC_AUTO                                  0x01

/**
 *@}
 */
/**
 *@}
 */


#endif /* __BLE_CONST_H__ */
