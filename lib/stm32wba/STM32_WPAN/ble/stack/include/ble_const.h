/*****************************************************************************
 * @file    ble_const.h
 *
 * @brief   This file contains the definitions which are compiler dependent.
 *****************************************************************************
 * @attention
 *
 * Copyright (c) 2018-2025 STMicroelectronics.
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


/* Default BLE variant
 */
#ifndef BASIC_PLUS
#define BASIC_PLUS 0
#endif
#ifndef BASIC_FEATURES
#define BASIC_FEATURES 0
#endif
#ifndef PERIPHERAL_ONLY
#define PERIPHERAL_ONLY 0
#endif
#ifndef LL_ONLY
#define LL_ONLY 0
#endif
#ifndef LL_ONLY_BASIC
#define LL_ONLY_BASIC 0
#endif

/* Maximum parameter size of BLE commands.
 */
#define BLE_CMD_MAX_PARAM_LEN HCI_COMMAND_MAX_PARAM_LEN

/* Maximum parameter size of BLE responses/events.
 */
#define BLE_EVT_MAX_PARAM_LEN HCI_EVENT_MAX_PARAM_LEN


#endif /* BLE_CONST_H__ */
