/**
  ******************************************************************************
  * @file    ble_status.h
  * @author  GPM WBL Application team
  * @brief   Header file which contains definition of Bluetooth status and error codes.
  * @note    Error Codes are defined according to Bluetooth Specifications
  *              Vol.2 Part D.
  *           - HCI/Controller standard codes range is [0x00 : 0x3F].
  *             Their name is prefixed by "BLE_ERROR_"
  *           - Host specific (and proprietary) error codes range is [0x80 : 0xFF].
  *             Their name is prefixed by "BLE_STATUS_" and they're grouped by Layer
  *           - BLE_STATUS_SUCCESS value is 0x00 and is the unique error code
  *             used by both Controller and Host layers.
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

#ifndef __BLE_STATUS_H__
#define __BLE_STATUS_H__

#include <stdint.h>
typedef uint8_t tBleStatus;

/* @brief Standard Error Codes as specified by the Bluetooth Specifications
 * Vol.2, Part D ("Error Codes").
 * According to the spec the error codes range is from 0x00 to 0x3F.
 */
#define BLE_STATUS_SUCCESS                          ((tBleStatus)(0x00))

#define BLE_ERROR_UNKNOWN_HCI_COMMAND               ((tBleStatus)(0x01))
#define BLE_ERROR_UNKNOWN_CONNECTION_ID             ((tBleStatus)(0x02))

#define BLE_ERROR_HARDWARE_FAILURE                  ((tBleStatus)(0x03))

#define BLE_ERROR_AUTHENTICATION_FAILURE            ((tBleStatus)(0x05))
#define BLE_ERROR_KEY_MISSING                       ((tBleStatus)(0x06))
#define BLE_ERROR_MEMORY_CAPACITY_EXCEEDED          ((tBleStatus)(0x07))
#define BLE_ERROR_CONNECTION_TIMEOUT                ((tBleStatus)(0x08))
#define BLE_ERROR_CONN_LIMIT                        ((tBleStatus)(0x09))

#define BLE_ERROR_CONNECTION_ALREADY_EXISTS         ((tBleStatus)(0x0B))
#define BLE_ERROR_COMMAND_DISALLOWED                ((tBleStatus)(0x0C))

#define BLE_ERROR_CONN_REJECT_DUE_TO_LIMITED_RESOURCES ((tBleStatus)(0x0D))

#define BLE_ERROR_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED      ((tBleStatus)(0x10))

#define BLE_ERROR_UNSUPPORTED_FEATURE               ((tBleStatus)(0x11))

#define BLE_ERROR_INVALID_HCI_CMD_PARAMS            ((tBleStatus)(0x12))

#define BLE_ERROR_TERMINATED_REMOTE_USER            ((tBleStatus)(0x13))

#define BLE_ERROR_TERMINATED_LOCAL_HOST             ((tBleStatus)(0x16))

#define BLE_ERROR_UNSUPP_RMT_FEATURE                ((tBleStatus)(0x1A))

#define BLE_ERROR_INVALID_LMP_LL_PARAMS             ((tBleStatus)(0x1E))

#define BLE_ERROR_UNSPECIFIED                       ((tBleStatus)(0x1F))

#define BLE_ERROR_UNSUPP_LMP_LL_PARAM_VALUE         ((tBleStatus)(0x20))

#define BLE_ERROR_LL_RESPONSE_TIMEOUT               ((tBleStatus)(0x22))

#define BLE_ERROR_LL_PROCEDURE_COLLISION            ((tBleStatus)(0x23))

#define BLE_ERROR_LMP_PDU_NOT_ALLOWED               ((tBleStatus)(0x24))

#define BLE_ERROR_ENC_MODE_NOT_ACCEPTABLE           ((tBleStatus)(0x25))

#define BLE_ERROR_INSTANT_PASSED                    ((tBleStatus)(0x28))

#define BLE_ERROR_DIFFERENT_TRANSACTION_COLLISION   ((tBleStatus)(0x2A))

#define BLE_ERROR_CHANNEL_ASSESSMENT_NOT_SUPPORTED  ((tBleStatus)(0x2E))

#define BLE_ERROR_PARAMETER_OUT_OF_RANGE            ((tBleStatus)(0x30))

#define BLE_ERROR_HOST_BUSY_PAIRING                 ((tBleStatus)(0x38))

#define BLE_ERROR_CONTROLLER_BUSY                   ((tBleStatus)(0x3A))

#define BLE_ERROR_UNACCEPTABLE_CONNECTION_PARAMS    ((tBleStatus)(0x3B))

#define BLE_ERROR_ADVERTISING_TIMEOUT               ((tBleStatus)(0x3C))

#define BLE_ERROR_CONNECTION_END_WITH_MIC_FAILURE   ((tBleStatus)(0x3D))

#define BLE_ERROR_CONNECTION_FAILED_TO_ESTABLISH    ((tBleStatus)(0x3E))

#define BLE_ERROR_COARSE_CLOCK_ADJ_REJECTED         ((tBleStatus)(0x40))

#define BLE_ERROR_TYPE0_SUBMAP_NOT_DEFINED          ((tBleStatus)(0x41))

#define BLE_ERROR_UNKNOWN_ADVERTISING_IDENTIFIER    ((tBleStatus)(0x42))

#define BLE_ERROR_LIMIT_REACHED                     ((tBleStatus)(0x43))

#define BLE_ERROR_OPERATION_CANCELLED_BY_HOST       ((tBleStatus)(0x44))

#define BLE_ERROR_PACKET_TOO_LONG                   ((tBleStatus)(0x45))

#define BLE_ERROR_TOO_LATE                          ((tBleStatus)(0x46))

#define BLE_ERROR_TOO_EARLY                         ((tBleStatus)(0x47))



/**
* @name Generic/System error codes
* @brief The error codes as reported by the different Protocol layers.
*        They start with 0x80
* @{
*/

/**
 * @brief The Connection Identifier does not exist.
 * Temporary remapped to corresponding Controller Error.
 */
#define BLE_STATUS_UNKNOWN_CONNECTION_ID    ((tBleStatus)(BLE_ERROR_UNKNOWN_CONNECTION_ID))

/**
 * @brief The Host failed while performing the requested operation.
 */
#define BLE_STATUS_FAILED                   ((tBleStatus)(0x81))

/**
 * @brief Invalid parameters passed at Host layer.
 */
#define BLE_STATUS_INVALID_PARAMS           ((tBleStatus)(BLE_ERROR_INVALID_HCI_CMD_PARAMS))


/**
 * @brief The Host is already processing another request received in advance.
 */
#define BLE_STATUS_BUSY                     ((tBleStatus)(0x83))

/**
 * @brief The operation requested cannot be completed immediately by the Host
 * (usually because of lack of resources).
 * The operation is generally put on hold by the caller and it's usually
 * retried on later time.
 */
#define BLE_STATUS_PENDING                  ((tBleStatus)(0x84))

/**
 * @brief The requested operation cannot be performed by the Host in the current status.
 */
#define BLE_STATUS_NOT_ALLOWED              ((tBleStatus)(BLE_ERROR_COMMAND_DISALLOWED))


/**
 * @brief The requested operation violates the logic of the called layer/function or
 * the format of the data to be processed during the operation.
 */
#define BLE_STATUS_ERROR                    ((tBleStatus)(0x86))

/**
 * @brief The requested operation failed because of lack of memory.
 * Out of memory shall be returned for situations where memory will never
 * become available again
 */
#define BLE_STATUS_OUT_OF_MEMORY            ((tBleStatus)(0x87))

/**
 * @brief The requested operation failed for a temporary lack of resources
 * (e.g. packet pool or timers), but it may be retried later when resources may
 * become available (packets or timers may have been released by other consumers).
 */
#define BLE_STATUS_INSUFFICIENT_RESOURCES   ((tBleStatus)(0x88))

/**
 * @brief A NULL pointer was passed as function parameter
 */
#define BLE_STATUS_NULL_PARAM               ((tBleStatus)(BLE_ERROR_INVALID_HCI_CMD_PARAMS))

/**
 * @brief The Host is temporarily waiting for user response, usually required
 *        through a (vendor specific) event that notifies the required action/response
 *        that shall be typically provided through a (vendor specific) command.
 */
#define BLE_STATUS_WAITING_FOR_USER_RESPONSE         ((tBleStatus)(0x90))

/**
 * @brief Indicate that the requested Security Level cannot be achieved based
 *        on available IO Capabilities and Authentication requirements.
 */
#define BLE_STATUS_SECURITY_REQUIREMENTS_NOT_ACHIEVABLE ((tBleStatus)(0x91))

/**
*@}
*/


/**
 * @name L2CAP error codes, start with 0xA0
*  @brief Error codes returned by the L2CAP, start at 0xA0
 * @{
 */

/**
 * @brief An invalid L2CAP CID/channel has been selected to send data over.
 */
#define BLE_STATUS_INVALID_CID              ((tBleStatus)(0xA0))

/**
*@}
*/


/**
* @name  Security Manager error codes
* @brief Error codes returned by the Security Manager Protocol (SMP), start at
*        0xB0
* @{
*/

/**
 * @brief The remote device in in the Blacklist and the pairing operation it requested
 * cannot be performed.
 */
#define BLE_STATUS_DEV_IN_BLACKLIST         ((tBleStatus)(0xB0))

/**
 * @brief CSRK not found during validation of an incoming signed packet
 */
#define BLE_STATUS_CSRK_NOT_FOUND           ((tBleStatus)(0xB1))

/**
 * @brief Currently not used!
 */
#define BLE_STATUS_IRK_NOT_FOUND            ((tBleStatus)(0xB2))

/**
 * @brief A search for a specific remote device was unsuccessful because no entry exists
 * either into Security/GATT Database (flash-based) or in volatile database.
 */
#define BLE_STATUS_DEV_NOT_FOUND            ((tBleStatus)(0xB3))

/**
 * @brief The security database is full and no more records can be added.
 */
#define BLE_STATUS_SEC_DB_FULL              ((tBleStatus)(0xB4))

/**
 * @brief The remote device is not bonded, and no operations related to bonded devices
 * may be performed (e.g. writing Gatt Client data).
 */
#define BLE_STATUS_DEV_NOT_BONDED           ((tBleStatus)(0xB5))

/**
 * @brief The encryption key size used for encrypting the link is insufficient\n
 */
#define BLE_INSUFFICIENT_ENC_KEYSIZE        ((tBleStatus)(0xB6))

/**
 * @brief The security database is temporarily unaccessible because the
 *        underlying physical NVM module is busy with other operations.
 */
#define BLE_STATUS_SEC_DB_BUSY              ((tBleStatus)(0xB7))

/**
*@}
*/


/**
* @name Gatt layer Error Codes
* @brief Error codes returned by the Gatt layer, start at 0xC0
* @{
*/

/**
 * @brief Notification/Indication can't be sent to the requested remote device because
 * it doesn't satisfy the needed security permission.
 */
#define BLE_STATUS_SEC_PERMISSION_ERROR     ((tBleStatus)(0xC0))

/**
*@}
*/


/**
* @name GAP layer Error Codes
* @brief Error codes returned by the GAP layer. start at 0xD0
* @{
*/

/**
 *  @brief The address of the device could not be resolved using the IRK stored
 */
#define BLE_STATUS_ADDRESS_NOT_RESOLVED          ((tBleStatus)(0xD0))

/**
 *  @brief The configuration set by the aci_gap_set_scan_configuration command
 *         is not coherent with the GAP procedure that is requested to be started
 */
#define BLE_STATUS_INVALID_SCAN_CONFIGURATION    ((tBleStatus)(0xD1))

/**
 *  @brief The configuration set by the aci_gap_set_connect_configuration command
 *         is not coherent with the GAP procedure that is requested to be started
 */
#define BLE_STATUS_INVALID_CONNECT_CONFIGURATION ((tBleStatus)(0xD2))

/**
 *  @brief The configuration set by the aci_gap_set_advertising_configuration command
 *         is not valid
 */
#define BLE_STATUS_INVALID_ADV_CONFIGURATION     ((tBleStatus)(0xD3))

/**
 *  @brief The discoverability flags in the advertising data are not coherent
 *         with the discoverability mode set in the advertising configuration
 */
#define BLE_STATUS_INVALID_ADV_FLAGS             ((tBleStatus)(0xD4))
/**
*@}
*/


/**
* @name flash error codes
* @brief Flash sector read write error codes, start at 0xF0
*        and are currently remapped from 0xFA to 0xFC
* @{
*/
#define BLE_STATUS_NVM_READ_FAILED               ((tBleStatus)(0xF0))
#define BLE_STATUS_NVM_WRITE_FAILED              ((tBleStatus)(0xF1))
#define BLE_STATUS_NVM_ERASE_FAILED              ((tBleStatus)(0xF2))

/**
*@}
*/

#define BLE_STATUS_TIMEOUT                       ((tBleStatus)(0xFF))


#endif
