/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gap_profile.h
  * @author  GPM WBL Application Team
  * @brief   Header file for Generic Access Profile Service (GAP)
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

#ifndef GAP_PROFILE_H
#define GAP_PROFILE_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "ble_status.h"
#include "ble_api.h"
/******************************************************************************
 * CONSTANT SYMBOLS
 *****************************************************************************/
#define GAP_CHR_DEVICE_NAME_VAL_LEN_MAX     (50U)
#define GAP_CHR_APPEARANCE_VAL_LEN          (2U)
#define GAP_CHR_PERIPH_PREF_CONN_PARAMS_LEN (8U)
#define GAP_CHR_CENTRAL_ADDR_RESOLUTION_LEN (1U)

/******************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************/

/**
 * @brief Initialize GAP Profile
 */
tBleStatus aci_gap_profile_init(uint8_t Role,
                                uint8_t Privacy_Type,
                                uint16_t *Dev_Name_Char_Handle,
                                uint16_t *Appearance_Char_Handle,
                                uint16_t *Periph_Pref_Conn_Param_Char_Handle);

/**
 * @brief Set device name value.
 *
 * @param offset Offset from which start to write the device name.
 * @param length Data length.
 * @param[in] dev_name_p Pointer to the data to write.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the characteristic value is updated correctly
 * - BLE_STATUS_INVALID_PARAMS: invalid parameter.
 *
 */
tBleStatus Gap_profile_set_dev_name(uint16_t offset,
                                    uint16_t length,
                                    uint8_t *dev_name_p);

/**
 * @brief Set appearance value.
 *
 * @param offset Offset from which start to write appearance value.
 * @param length Data length.
 * @param[in] appearance_p Pointer to the data to write.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the characteristic value is updated correctly
 * - BLE_STATUS_INVALID_PARAMS: invalid parameter.
 *
 */
tBleStatus Gap_profile_set_appearance(uint16_t offset,
                                      uint16_t length,
                                      uint8_t *appearance_p);

/**
 * @brief Set preferred connection parameter value.
 *
 * @param offset Offset from which start to write value.
 * @param length Data length.
 * @param[in] pref_conn_param_p Pointer to the data to write.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the characteristic value is updated correctly
 * - BLE_STATUS_INVALID_PARAMS: invalid parameter.
 *
 */
tBleStatus Gap_profile_set_pref_conn_par(uint16_t offset,
                                         uint16_t length,
                                         uint8_t *pref_conn_param_p);

/**
 * @brief Set GAP characteristic value.
 *
 * @param attr_h Attribute handle to write.
 * @param val_offset Offset from which start to write the device name.
 * @param val_length Data length.
 * @param[in] val_p Pointer to the data to write.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the characteristic value is updated correctly
 * - BLE_STATUS_INVALID_PARAMS: invalid parameter.
 *
 */
tBleStatus Gap_profile_set_char_value(uint16_t attr_h,
                                      uint16_t val_offset,
                                      uint16_t val_length,
                                      uint8_t *val_p);

/**
 * @brief Change access permission for the provided attribute handle.
 *
 * @param attr_h The requested attribute handle to change.
 * @param perm the new permission value.
 *
 * @return:
 * - BLE_STATUS_SUCCESS: the access permission are set
 * - BLE_STATUS_FAILED: the requested attribute is not in the GAP service group
 *                      or the attribute can't be altered.
 *
 */
tBleStatus Gap_profile_set_access_permission(uint16_t attr_h, uint8_t perm);

/**
 * @brief Change security permission for the provided attribute handle.
 *
 * @param attr_h The requested attribute handle to change.
 * @param perm the new permission value.
 *
 * @return:
 * - BLE_STATUS_SUCCESS: the security permission are set.
 * - BLE_STATUS_NOT_ALLOWED: the requested permissions are not allowed.
 * - BLE_STATUS_FAILED: the requested attribute is not in the GAP service group
 *                      or the attribute can't be altered.
 *
 */
tBleStatus Gap_profile_set_security_permission(uint16_t attr_h, uint8_t perm);

/**
 * @brief Retrieve GAP profile service handle.
 *
 * @return: service handle.
 *
 */
uint16_t Gap_profile_get_service_handle(void);

/**
 * @brief Retrieve GAP service definition pointer.
 *
 * @return: service definition pointer.
 *
 */
ble_gatt_srv_def_t *Gap_profile_get_service_definition_p(void);

#endif

