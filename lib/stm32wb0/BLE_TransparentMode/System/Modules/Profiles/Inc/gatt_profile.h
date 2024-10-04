/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gatt_profile.h
  * @author  GPM WBL Application Team
  * @brief   Header file for Generic Attribute Profile Service (GATT)
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

#ifndef GATT_PROFILE_H
#define GATT_PROFILE_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "stdint.h"
#include "ble_status.h"
#include "ble_api.h"
/******************************************************************************
 * CONSTANT SYMBOLS
 *****************************************************************************/
#if defined(CONFIG_NUM_MAX_LINKS)
#define GATT_SRV_MAX_CONN                                   (CONFIG_NUM_MAX_LINKS)
#else
#define GATT_SRV_MAX_CONN                                   (8U)
#endif

#define GATT_CHR_SERVICE_CHANGED_VALUE_LEN                  (4U)

#define GATT_INIT_SERVICE_CHANGED_BIT                       (0x01)

/******************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************/

/**
 * @brief Initialize GATT Profile
 *
 * @return:
 * - BLE_STATUS_SUCCESS: the service is correctly loaded
 *
 */
tBleStatus aci_gatt_srv_profile_init(uint8_t Characteristics,
                                     uint16_t *Service_Changed_Handle);

/**
 * @brief Change access permission for the provided attribute handle.
 *
 * @param attr_h The requested attribute handle to change.
 * @param perm the new permission value.
 *
 * @return:
 * - BLE_STATUS_SUCCESS: the access permission are set
 * - BLE_STATUS_FAILED: the requested attribute is not in the GATT service group
 *                     or the attribute can't be altered.
 *
 */
tBleStatus Gatt_profile_set_access_permission(uint16_t attr_h, uint8_t perm);

/**
 * @brief Change security permission for the provided attribute handle.
 *
 * @param attr_h The requested attribute handle to change.
 * @param perm the new permission value.
 *
 * @return:
 * - BLE_STATUS_SUCCESS: the security permission are set.
 * - BLE_STATUS_NOT_ALLOWED: the requested permissions are not allowed.
 * - BLE_STATUS_FAILED: the requested attribute is not in the GATT service group
 *                     or the attribute can't be altered.
 *
 */
tBleStatus Gatt_profile_set_security_permission(uint16_t attr_h, uint8_t perm);

/**
 * @brief Retrieve GATT profile service handle.
 *
 * @return: service handle.
 *
 */
uint16_t Gatt_profile_get_service_handle(void);

/**
 * @brief Retrieve GATT service definition pointer.
 *
 * @return: service definition pointer.
 *
 */
ble_gatt_srv_def_t *Gatt_profile_get_service_definition_p(void);

#endif

