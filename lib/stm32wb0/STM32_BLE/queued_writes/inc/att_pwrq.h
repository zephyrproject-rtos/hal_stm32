/**
  ******************************************************************************
  * @file    att_pwrq.h
  * @author  GPM WBL Application Team
  * @brief   Header file for ATT Prepare Write Queue implementation
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

#ifndef __ATT_PWRQ_H__
#define __ATT_PWRQ_H__

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "ble_gatt.h"
/******************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************/
/**
 *@defgroup PWRQ_APIs Prepare Write Queue support module
 *@brief Module to help managing prepare write queue
 *@{
 */

/**
 * @brief This function is used to initialize the PWRQ module
 *
 * @param queue_length the queue buffer size.
 * @param[in] queue_buffer_p pointer to queue buffer memory area.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the PWRQ module is initialized correctly.
 * - BLE_STATUS_FAILED: an error arise on initialization.
 *
 */
tBleStatus ATT_pwrq_init(uint16_t queue_length,
                         uint8_t *queue_buffer_p);

/**
 * @brief Reset PWRQ module flushing any present Prepare Writes.
 *
 * @return void
 *
 */
void ATT_pwrq_reset(void);

/**
 * @brief This function is used to store a prepare write request in the queue.
 *
 * @param conn_handle the connection handle from which the request is received.
 * @param attr_h handle of attribute to write
 * @param data_offset offset from which the write has to be start
 * @param data_length length of data
 * @param[in] data data to write.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the prepare write request is queued correctly
 * - BLE_STATUS_ERROR: the queue is full.
 */
tBleStatus ATT_pwrq_push(uint16_t conn_handle,
                         uint16_t attr_h,
                         uint16_t data_offset,
                         uint16_t data_length,
                         uint8_t *data);

/**
 * @brief Flush prepared write for the given connection handle.
 *
 * @param conn_handle The connection handle of the prepare write to flush.
 *
 * @return void
 */
void ATT_pwrq_flush(uint16_t conn_handle);

/**
 * @brief This function is used to read a prepare write from the queue.
 *
 * @param conn_handle the connection handle from which the request is received.
 * @param idx The index of the prepare write in the queue.
 * @param[out] wr_ops_p The prepare write pointer.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the prepare write request is found and returned correctly
 * - BLE_STATUS_ERROR: no prepare write request was found.
 */
tBleStatus ATT_pwrq_read(uint16_t conn_handle, uint16_t idx,
                         ble_gatt_clt_write_ops_t *wr_ops_p);

/**
 * @brief This function is used to extract a prepare write from the queue.
 *
 * @param conn_handle the connection handle from which the request is received.
 * @param attr_handle The requested attribute handle to find. If it is set to
 *                        0x0000 then the first found prepare write entry will
 *                        be returned.
 * @param[out] wr_ops_p The prepare write pointer.
 *
 * @return
 * - BLE_STATUS_SUCCESS: the prepare write request is found and returned correctly
 * - BLE_STATUS_ERROR: no prepare write request was found.
 */
tBleStatus ATT_pwrq_pop(uint16_t conn_handle, uint16_t attr_handle,
                        ble_gatt_clt_write_ops_t *wr_ops_p);

/**
 *@}
 */

#endif
