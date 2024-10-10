/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dtm_cmd_en.h
  * @author  AMS - RF Application team
  * @version V1.0.0
  * @date    21 July 2022
  * @brief   List of macros used to configure the DTM ACI/HCI command table
  *          with modularity
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

#ifndef _DTM_CMD_EN_H_
#define _DTM_CMD_EN_H_

/* Include header file containing macros for command exported by stack library */
#include "ble_stack_user_cfg.h"
#include "dtm_cmd_stack_en.h"

/* Enabling macros for functions outside of the stack */
#define HCI_LE_READ_MAXIMUM_ADVERTISING_DATA_LENGTH_ENABLED\
        (CONTROLLER_EXT_ADV_SCAN_ENABLED)
#define HCI_LE_SET_EXTENDED_ADVERTISING_DATA_ENABLED\
        (CONTROLLER_EXT_ADV_SCAN_ENABLED)
#define HCI_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_ENABLED\
        (CONTROLLER_EXT_ADV_SCAN_ENABLED)
#define HCI_LE_SET_PERIODIC_ADVERTISING_DATA_ENABLED\
        (CONTROLLER_PERIODIC_ADV_ENABLED)
#define HCI_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA_ENABLED\
        (CONTROLLER_PERIODIC_ADV_WR_ENABLED)
#define HCI_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA_ENABLED\
        (CONTROLLER_PERIODIC_ADV_WR_ENABLED)
#define ACI_GATT_SRV_ADD_SERVICE_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_INCLUDE_SERVICE_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_ADD_CHAR_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_ADD_CHAR_DESC_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_WRITE_HANDLE_VALUE_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_RM_CHAR_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_RM_SERVICE_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_RM_INCLUDE_SERVICE_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_CLT_WRITE_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_CLT_WRITE_LONG_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_CLT_WRITE_CHAR_RELIABLE_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_SET_SECURITY_PERMISSION_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_READ_HANDLE_VALUE_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_SET_ACCESS_PERMISSION_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_EXEC_WRITE_RESP_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_AUTHORIZE_RESP_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_READ_PREPARE_QUEUE_NWK_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_GATT_SRV_READ_MULTIPLE_INSTANCE_HANDLE_VALUE_NWK_ENABLED\
        (CONNECTION_ENABLED)
#ifndef __ZEPHYR__
#define ACI_HAL_TRANSMITTER_TEST_PACKETS_V2_ENABLED\
       (CONTROLLER_CTE_ENABLED)
#endif /* __ZEPHYR__ */
#define ACI_TEST_TX_NOTIFICATION_START_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_TEST_TX_WRITE_COMMAND_START_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_TEST_RX_START_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_TEST_STOP_ENABLED\
        (CONNECTION_ENABLED)
#define ACI_TEST_REPORT_ENABLED\
        (CONNECTION_ENABLED)

#if CONFIG_NO_HCI_COMMANDS
/* Macros to force exclusion of some unnecessary HCI/ACI commands from DTM */
#define HCI_DISCONNECT_FORCE_DISABLED                                                   1
#define HCI_READ_TRANSMIT_POWER_LEVEL_FORCE_DISABLED                                    1
#define HCI_READ_LOCAL_SUPPORTED_COMMANDS_FORCE_DISABLED                                1
#define HCI_READ_LOCAL_SUPPORTED_FEATURES_FORCE_DISABLED                                1
#define HCI_READ_BD_ADDR_FORCE_DISABLED                                                 1
#define HCI_LE_READ_BUFFER_SIZE_FORCE_DISABLED                                          1
#define HCI_LE_READ_BUFFER_SIZE_V2_FORCE_DISABLED                                       1
#define HCI_LE_READ_LOCAL_SUPPORTED_FEATURES_FORCE_DISABLED                             1
#define HCI_LE_SET_RANDOM_ADDRESS_FORCE_DISABLED                                        1
#define HCI_LE_SET_ADVERTISING_PARAMETERS_FORCE_DISABLED                                1
#define HCI_LE_READ_ADVERTISING_PHYSICAL_CHANNEL_TX_POWER_FORCE_DISABLED                1
#define HCI_LE_SET_ADVERTISING_DATA_FORCE_DISABLED                                      1
#define HCI_LE_SET_SCAN_RESPONSE_DATA_FORCE_DISABLED                                    1
#define HCI_LE_SET_ADVERTISING_ENABLE_FORCE_DISABLED                                    1
#define HCI_LE_SET_SCAN_PARAMETERS_FORCE_DISABLED                                       1
#define HCI_LE_SET_SCAN_ENABLE_FORCE_DISABLED                                           1
#define HCI_LE_CREATE_CONNECTION_FORCE_DISABLED                                         1
#define HCI_LE_CREATE_CONNECTION_CANCEL_FORCE_DISABLED                                  1
#define HCI_LE_CLEAR_FILTER_ACCEPT_LIST_FORCE_DISABLED                                  1
#define HCI_LE_ADD_DEVICE_TO_FILTER_ACCEPT_LIST_FORCE_DISABLED                          1
#define HCI_LE_REMOVE_DEVICE_FROM_FILTER_ACCEPT_LIST_FORCE_DISABLED                     1
#define HCI_LE_CONNECTION_UPDATE_FORCE_DISABLED                                         1
#define HCI_LE_READ_CHANNEL_MAP_FORCE_DISABLED                                          1
#define HCI_LE_ENCRYPT_FORCE_DISABLED                                                   1
#define HCI_LE_RAND_FORCE_DISABLED                                                      1
#define HCI_LE_ENABLE_ENCRYPTION_FORCE_DISABLED                                         1
#define HCI_LE_LONG_TERM_KEY_REQUEST_REPLY_FORCE_DISABLED                               1
#define HCI_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_FORCE_DISABLED                      1
#define HCI_LE_READ_SUPPORTED_STATES_FORCE_DISABLED                                     1
#define HCI_LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH_FORCE_DISABLED                        1
#define HCI_LE_GENERATE_DHKEY_FORCE_DISABLED                                            1
#define HCI_LE_ADD_DEVICE_TO_RESOLVING_LIST_FORCE_DISABLED                              1
#define HCI_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST_FORCE_DISABLED                         1
#define HCI_LE_CLEAR_RESOLVING_LIST_FORCE_DISABLED                                      1
#define HCI_LE_SET_ADDRESS_RESOLUTION_ENABLE_FORCE_DISABLED                             1
#define HCI_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT_FORCE_DISABLED                    1
#define HCI_LE_READ_MAXIMUM_DATA_LENGTH_FORCE_DISABLED                                  0
#define HCI_LE_READ_PHY_FORCE_DISABLED                                                  1
#define HCI_LE_SET_ADVERTISING_SET_RANDOM_ADDRESS_FORCE_DISABLED                        1
#define HCI_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_FORCE_DISABLED                       1
#define HCI_LE_SET_EXTENDED_ADVERTISING_DATA_FORCE_DISABLED                             1
#define HCI_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_FORCE_DISABLED                           1
#define HCI_LE_SET_EXTENDED_ADVERTISING_ENABLE_FORCE_DISABLED                           1
#define HCI_LE_READ_NUMBER_OF_SUPPORTED_ADVERTISING_SETS_FORCE_DISABLED                 1
#define HCI_LE_REMOVE_ADVERTISING_SET_FORCE_DISABLED                                    1
#define HCI_LE_CLEAR_ADVERTISING_SETS_FORCE_DISABLED                                    1
#define HCI_LE_SET_EXTENDED_SCAN_PARAMETERS_FORCE_DISABLED                              1
#define HCI_LE_SET_EXTENDED_SCAN_ENABLE_FORCE_DISABLED                                  1
#define HCI_LE_EXTENDED_CREATE_CONNECTION_FORCE_DISABLED                                1
#define HCI_LE_READ_TRANSMIT_POWER_FORCE_DISABLED                                       1
#define HCI_LE_READ_RF_PATH_COMPENSATION_FORCE_DISABLED                                 1
#define HCI_LE_READ_ANTENNA_INFORMATION_FORCE_DISABLED                                  1
#define ACI_HAL_GET_FW_BUILD_NUMBER_FORCE_DISABLED                                      1
#endif

#endif /* _DTM_CMD_EN_H_ */

