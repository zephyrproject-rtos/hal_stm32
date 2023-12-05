/*****************************************************************************
 * @file    ble_const.h
 * @author  MDG
 * @brief   This file contains the definitions which are compiler dependent.
 *****************************************************************************
 * @attention
 *
 * Copyright (c) 2018-2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 *****************************************************************************
 */

#ifndef BLE_CONST_H__
#define BLE_CONST_H__


#include <stdint.h>
#include <string.h>
#include "ble_std.h"
#include "ble_defs.h"


/* Default BLE variant */
#ifndef BASIC_FEATURES
#define BASIC_FEATURES 0
#endif
#ifndef LL_ONLY
#define LL_ONLY 0
#endif
#ifndef LL_ONLY_BASIC
#define LL_ONLY_BASIC 0
#endif

/* Size of command/events buffers:
 *
 * To change the size of commands and events parameters used in the
 * auto-generated files, you need to update 2 defines:
 *
 *  - BLE_CMD_MAX_PARAM_LEN          
 *  - BLE_EVT_MAX_PARAM_LEN          
 *
 * These 2 defines are set below with default values and can be changed.
 *
 * To compute the value to support a characteristic of 512 bytes for a specific
 * command or an event, you need to look in "ble_types.h".
 *
 * Here are 2 examples, one with a command and one with an event:
 *
 * - aci_gatt_update_char_value_ext_cp0
 *   ----------------------------------
 *
 *   we have in the structure:
 *
 *      uint8_t Value[(BLE_CMD_MAX_PARAM_LEN- 12)/sizeof(uint8_t)];
 *
 *   so to support a 512 byte value, we need to have
 *
 *   BLE_CMD_MAX_PARAM_LEN at least equal to: 512 + 12 = 524
 *
 * - aci_gatt_read_handle_value_rp0
 *   ------------------------------
 *
 *   we have in the structure:
 *
 *     uint8_t Value[((BLE_EVT_MAX_PARAM_LEN - 3) - 5)/sizeof(uint8_t)];
 *
 *   so to support a 512 byte value, we need to have
 *
 *   BLE_EVT_MAX_PARAM_LEN at least equal to: 512 + 3 + 5 = 520
 *
 * If you need several events or commands with 512-size values, you need to
 * take the maximum values for BLE_EVT_MAX_PARAM_LEN and BLE_CMD_MAX_PARAM_LEN.
 *
 */

/* Maximum parameter size of BLE commands.
 * Change this value if needed. */
#define BLE_CMD_MAX_PARAM_LEN          HCI_COMMAND_MAX_PARAM_LEN

/* Maximum parameter size of BLE responses/events.
 * Change this value if needed. */
#define BLE_EVT_MAX_PARAM_LEN          HCI_EVENT_MAX_PARAM_LEN


#endif /* BLE_CONST_H__ */
