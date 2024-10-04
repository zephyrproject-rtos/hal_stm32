/**
 ******************************************************************************
  * @file    ble_gatt.h
  * @author  GPM WBL Application team
  * @brief   Header file for Bluetooth LE GATT
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

#ifndef BLE_GATT_H
#define BLE_GATT_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>

/******************************************************************************
 * CONSTANT SYMBOLS
 *****************************************************************************/
/**
 *@addtogroup GATT GATT
 *@brief Generic Attribute Profile
 *@{
 */

/**
 *@addtogroup GATT_constants GATT Constants
 *@brief Constants for GATT layer
 *@{
 */

/**
 *@name BLE ATT
 * Constants for connection handles
 *@{
 */
#define BLE_ATT_INVALID_ATTR_HANDLE                     (0x0000U) /**< Invalid attribute handle */
#define BLE_ATT_MIN_ATTR_HANDLE                         (0x0001U) /**< Minimum valid attribute handle */
#define BLE_ATT_MAX_ATTR_HANDLE                         (0xFFFFU) /**< Maximum valid attribute handle */
#define BLE_ATT_ATTR_HANDLE_SIZE                        (2U) /**< Size of an attribute handle value */
#define BLE_GATT_MAX_ATTR_VALUE_SIZE                    (512U) /**< Max size of an attribute value. @see 3.2.9 Long
                                                                *   attribute values - BLUETOOTH CORE SPECIFICATION
                                                                *   Version 5.1 | Vol 3, Part F page 2297 */
/**
 *@}
 */

/**
 *@anchor GATT_SRV_TYPE
 *@name GATT_SRV_TYPE
 *@{
 */
#define BLE_GATT_SRV_PRIMARY_SRV_TYPE                   (1U)
#define BLE_GATT_SRV_SECONDARY_SRV_TYPE                 (2U)
/**
 *@}
 */

/**
 *@anchor GATT_SRV_KEY_SIZE
 *@name GATT_SRV_KEY_SIZE
 *@{
 */
#define BLE_GATT_SRV_MIN_ENCRY_KEY_SIZE                 (7U)
#define BLE_GATT_SRV_MAX_ENCRY_KEY_SIZE                 (16U)
/**
 *@}
 */

/**
 *@name GATT_SRV_UUID
 *@{
 */
#define BLE_GATT_SRV_PRIM_SERV_DECL_TYPE_UUID           (0x2800U)
#define BLE_GATT_SRV_SEC_SERV_DECL_TYPE_UUID            (0x2801U)
#define BLE_GATT_SRV_INCL_SERV_DECL_TYPE_UUID           (0x2802U)
#define BLE_GATT_SRV_CHAR_DECL_TYPE_UUID                (0x2803U)
#define BLE_GATT_SRV_CHAR_EXT_PROP_DESCR_TYPE_UUID      (0x2900U)
#define BLE_GATT_SRV_CHAR_USER_DESCR_TYPE_UUID          (0x2901U)
#define BLE_GATT_SRV_CLIENT_CHAR_CONF_DESCR_TYPE_UUID   (0x2902U)
#define BLE_GATT_SRV_SERVER_CHAR_CONF_DESCR_TYPE_UUID   (0x2903U)
#define BLE_GATT_SRV_CHAR_PRES_FORMAT_DESCR_TYPE_UUID   (0x2904U)
#define BLE_GATT_SRV_CHAR_AGGR_FORMAT_DESCR_TYPE_UUID   (0x2905U)
#define BLE_GATT_SRV_DEVICE_NAME_CHR_UUID               (0x2A00U)
#define BLE_GATT_SRV_APPEARANCE_CHR_UUID                (0x2A01U)
#define BLE_GATT_SRV_PERIPHERAL_PREFERRED_CONN_PARAMS_UUID   (0x2A04U)
#define BLE_GATT_SRV_SERVICE_CHANGE_CHR_UUID            (0x2A05U)
#define BLE_GATT_SRV_CENTRAL_ADDRESS_RESOLUTION_UUID    (0x2AA6U)
#define BLE_GATT_SRV_CLIENT_SUPP_FEATURE_CHR_UUID       (0x2B29U)
#define BLE_GATT_SRV_DB_HASH_CHR_UUID                   (0x2B2AU)
#define BLE_GATT_SRV_SUPPORTED_FEATURES_CHR_UUID        (0x2B3AU)
#define BLE_GATT_SRV_ENCRYPTED_DATA_KEY_MATERIAL_UUID   (0x2B88U)

#define BLE_GATT_SRV_GATT_SERVICE_UUID                  (0x1801U)
#define BLE_GATT_SRV_GAP_SERVICE_UUID                   (0x1800U)

/**
 *@}
 */

/**
 *@name GATT_SRV_CHAR_PROP
 * @brief The following macro are used to define the characteristic properties as
 * defined in BLUETOOTH CORE SPECIFICATION Version 5.1 | Vol 3, Part G, 3.3.1.1
 * Table 3.5.
 *@{
 */
#define BLE_GATT_SRV_CHAR_PROP_NONE                     (0x00U)
/** If set, it permits broadcasts of the
 * Characteristic Value using Server Characteristic Configuration Descriptor.
 * If set, the Server Characteristic Configuration Descriptor shall exist. */
#define BLE_GATT_SRV_CHAR_PROP_BROADCAST                (0x01U)
/** If set, it permits reads of the Characteristic Value. */
#define BLE_GATT_SRV_CHAR_PROP_READ                     (0x02U)
/** If set, it permit writes of the Characteristic Value without response. */
#define BLE_GATT_SRV_CHAR_PROP_WRITE_NO_RESP            (0x04U)
/** If set, it permits writes of the Characteristic Value with response. */
#define BLE_GATT_SRV_CHAR_PROP_WRITE                    (0x08U)
/** If set, it permits notifications of a
 * Characteristic Value without acknowledgment. If set, the Client
 * Characteristic Configuration Descriptor shall exist. */
#define BLE_GATT_SRV_CHAR_PROP_NOTIFY                   (0x10U)
/** If set, it permits indications of a
 * Characteristic Value with acknowledgment. If set, the Client Characteristic
 * Configuration Descriptor shall exist. */
#define BLE_GATT_SRV_CHAR_PROP_INDICATE                 (0x20U)
/** If set, it permits signed writes to the
 * Characteristic Value. */
#define BLE_GATT_SRV_CHAR_PROP_AUTH_SIGN_WRITE          (0x40U)
/** If set, additional characteristic
 * properties are defined in the Characteristic Extended Properties Descriptor.
 * If set, the Characteristic Extended Properties Descriptor shall exist. */
#define BLE_GATT_SRV_CHAR_PROP_EXTENDED_PROP            (0x80U)

#define BLE_GATT_SRV_CHAR_PROP_ACCESS_PERM_MASK         (BLE_GATT_SRV_CHAR_PROP_READ | \
                                                         BLE_GATT_SRV_CHAR_PROP_WRITE | \
                                                         BLE_GATT_SRV_CHAR_PROP_WRITE_NO_RESP | \
                                                         BLE_GATT_SRV_CHAR_PROP_AUTH_SIGN_WRITE)
/**
 *@}
 */

/**
 *@anchor GATT_SRV_DESCR_PROP
 *@name GATT_SRV_DESCR_PROP constants
 * The following macro are used to define the descriptor access properties.
 *@{
 */
#define BLE_GATT_SRV_DESCR_PROP_READ                    (0x01U)
#define BLE_GATT_SRV_DESCR_PROP_WRITE                   (0x02U)
/**
 *@}
 */

/**
 *@anchor SRV_VALBUFFER_OP_FLAGS
 *@name SRV_VALBUFFER_OP_FLAGS
 * The following flags enable some behaviour on how to handle the value
 * buffers used in the profile definition structures.
 *@{
 */
#define BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG        (0x01U)
#define BLE_GATT_SRV_OP_VALUE_VAR_LENGTH_FLAG           (0x02U)
/**
 *@}
 */

/**
 *@name ATT_ERROR_CODES
 * Available Error Codes as reported in:
 * Table 3.3 | Vol 3, Part F.
 *@{
 */
#define BLE_ATT_ERR_NONE                                (0x00U) /**< Not an error! */
#define BLE_ATT_ERR_INVALID_HANDLE                      (0x01U) /**< The attribute handle given was not valid on this server. */
#define BLE_ATT_ERR_READ_NOT_PERM                       (0x02U) /**< The attribute cannot be read. */
#define BLE_ATT_ERR_WRITE_NOT_PERM                      (0x03U) /**< The attribute cannot be written. */
#define BLE_ATT_ERR_INVALID_PDU                         (0x04U) /**< The attribute PDU was invalid. */
#define BLE_ATT_ERR_INSUFF_AUTHENTICATION               (0x05U) /**< The attribute requires authentication before it can be read or written. */
#define BLE_ATT_ERR_REQ_NOT_SUPP                        (0x06U) /**< Attribute server does not support the request received from the client. */
#define BLE_ATT_ERR_INVALID_OFFSET                      (0x07U) /**< Offset specified was past the end of the attribute. */
#define BLE_ATT_ERR_INSUFF_AUTHORIZATION                (0x08U) /**< The attribute requires authorization before it can be read or written. */
#define BLE_ATT_ERR_PREP_QUEUE_FULL                     (0x09U) /**< Too many prepare writes have been queued. */
#define BLE_ATT_ERR_ATTR_NOT_FOUND                      (0x0AU) /**< No attribute found within the given attribute handle range. */
#define BLE_ATT_ERR_ATTR_NOT_LONG                       (0x0BU) /**< The attribute cannot be read using the Read Blob Request. */
#define BLE_ATT_ERR_INSUFF_ENCR_KEY_SIZE                (0x0CU) /**< The Encryption Key Size used for encrypting this link is insufficient. */
#define BLE_ATT_ERR_INVAL_ATTR_VALUE_LEN                (0x0DU) /**< The attribute value length is invalid for the operation. */
#define BLE_ATT_ERR_UNLIKELY                            (0x0EU) /**< The attribute request that was requested has encountered an error
                                                                 *   that was unlikely, and therefore could not be completed as requested. */
#define BLE_ATT_ERR_INSUFF_ENCRYPT                      (0x0FU) /**< The attribute requires encryption before it can be read or written. */
#define BLE_ATT_ERR_UNSUPP_GRP_TYPE                     (0x10U) /**< The attribute type is not a supported grouping attribute as defined by
                                                                 *   a higher layer specification. */
#define BLE_ATT_ERR_INSUFF_RESOURCES                    (0x11U) /**< Insufficient Resources to complete the request. */
#define BLE_ATT_ERR_DB_OUT_OF_SYNC                      (0x12U) /**< The server requests the client to rediscover the database. */
#define BLE_ATT_ERR_VALUE_NOT_ALLOWED                   (0x13U) /**< The attribute parameter value was not allowed. */
#define BLE_ATT_ERR_APPL_MIN                            (0x80U) /**< Application error code defined by a higher layer specification.
                                                                 *   Lower error value.
                                                                 */
#define BLE_ATT_ERR_APPL_MAX                            (0x9FU) /**< Application error code defined by a higher layer specification.
                                                                 *   Higher error value.
                                                                 */
#define BLE_ATT_ERR_CMN_PROF_SRVC_MIN                   (0xE0U) /**< Common profile and service error codes defined in [Core Specification
                                                                 *   Supplement], Part B.
                                                                 *   Lower error value.
                                                                 */
#define BLE_ATT_ERR_CCCD_IMPROPERLY_CONFIGURED          (0xFDU) /**< The Client Characteristic Configuration Descriptor Improperly Configured error
                                                                 *   code is used when a Client Characteristic Configuration descriptor is not
                                                                 *   configured according to the requirements of the profile or service.
                                                                 *   2.3 CLIENT CHARACTERISTIC CONFIGURATION DESCRIPTOR IMPROPERLY CONFIGURED (0xFD)
                                                                 *   Supplement to the Bluetooth Core Specification | CSS v10, Part B page 34
                                                                 */
#define BLE_ATT_ERR_CMN_PROF_SRVC_MAX                   (0xFFU) /**< Common profile and service error codes defined in [Core Specification
                                                                 *   Supplement], Part B.
                                                                 *   Higher error value. */
/**
 *@}
 */

/**
 *@anchor GATT_SRV_PERMS
 *@name GATT_SRV_PERMS
 * The following macro define the attribute permissions.
 *@{
 */
/** Read and Write can be performed on the attribute with no requirements. */
#define BLE_GATT_SRV_PERM_NONE                          (0x00U)
/** Attribute can be read only on authenticated links (MITM on). */
#define BLE_GATT_SRV_PERM_AUTHEN_READ                   (0x01U)
/** Attribute can be read only on encrypted links. */
#define BLE_GATT_SRV_PERM_ENCRY_READ                    (0x04U)
/** Attribute can be written only on authenticated links (MITM on). */
#define BLE_GATT_SRV_PERM_AUTHEN_WRITE                  (0x08U)
/** Attribute can be written only on encrypted links. */
#define BLE_GATT_SRV_PERM_ENCRY_WRITE                   (0x20U)
#define BLE_GATT_SRV_PERM_ALL                           (BLE_GATT_SRV_PERM_AUTHEN_READ | \
                                                         BLE_GATT_SRV_PERM_ENCRY_READ | \
                                                         BLE_GATT_SRV_PERM_AUTHEN_WRITE | \
                                                         BLE_GATT_SRV_PERM_ENCRY_WRITE)
/**
 *@}
 */

/**
 *@name GATT_SRV_CCCD
 *@brief The Client Characteristic Configuration is a special descriptor that
 *       has to store the subscription of each client to receive notification
 *       and indication value.
 *@{
 */
#define BLE_GATT_SRV_CCCD_VALUE_LEN                     (2U)
#define BLE_GATT_SRV_CCCD_NOTIFICATION_BIT              (0U)
#define BLE_GATT_SRV_CCCD_INDICATION_BIT                (1U)
#define BLE_GATT_SRV_CCCD_NOTIFICATION                  (1U << BLE_GATT_SRV_CCCD_NOTIFICATION_BIT)
#define BLE_GATT_SRV_CCCD_INDICATION                    (1U << BLE_GATT_SRV_CCCD_INDICATION_BIT)

#define BLE_GATT_SRV_CCCD_NUM_BITS_PER_CONN             (2U)
#define BLE_GATT_SRV_CCCD_VAL_MASK                      (BLE_GATT_SRV_CCCD_NUM_BITS_PER_CONN | \
                                                         (BLE_GATT_SRV_CCCD_NUM_BITS_PER_CONN - 1))
#define BLE_GATT_SRV_CCCD_NUM_CONN_PER_BYTE             (8U / BLE_GATT_SRV_CCCD_NUM_BITS_PER_CONN)
/** Return the number of bytes needed to store a CCCD giving the number of connections. */
#define BLE_GATT_SRV_CCCD_BUFF_SIZE(NUM_CONN)           (((NUM_CONN) / BLE_GATT_SRV_CCCD_NUM_CONN_PER_BYTE) + 1U)
/** Declare a storage buffer with the giving name to store the CCCD. */
#define BLE_GATT_SRV_CCCD_BUFF_DECLARE(NAME, NUM_CONN)   uint8_t(NAME)[BLE_GATT_SRV_CCCD_BUFF_SIZE(NUM_CONN)]

#define BLE_GATT_SRV_CCCD_BUFFER_NAME(NAME)             NAME##_cccd_buffer
#define BLE_GATT_SRV_CCCD_VAL_BUFFER_NAME(NAME)         NAME##_cccd_val_buffer

#define BLE_GATT_SRV_CCCD_BUFFER_DECLARE(NAME, NUM_CONN, OP_FLAGS)                  \
    static uint8_t BLE_GATT_SRV_CCCD_BUFFER_NAME(NAME)[BLE_GATT_SRV_CCCD_BUFF_SIZE(NUM_CONN)]; \
    static const ble_gatt_val_buffer_def_t BLE_GATT_SRV_CCCD_VAL_BUFFER_NAME(NAME) = {   \
        .op_flags = (OP_FLAGS & BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG),          \
        .buffer_len = BLE_GATT_SRV_CCCD_BUFF_SIZE(NUM_CONN),                        \
        .buffer_p = BLE_GATT_SRV_CCCD_BUFFER_NAME(NAME),                            \
    }

#define BLE_GATT_SRV_CCCD_DEF_NAME(NAME)                NAME##_cccd
#define BLE_GATT_SRV_CCCD_DEF_STR_FIELDS(NAME, NUM_CONN, PERM)                      \
    .val_buffer_p = (ble_gatt_val_buffer_def_t *)&BLE_GATT_SRV_CCCD_VAL_BUFFER_NAME(NAME), \
    .properties = BLE_GATT_SRV_DESCR_PROP_WRITE | BLE_GATT_SRV_DESCR_PROP_READ,     \
    .permissions = (PERM),                                                          \
    .min_key_size = BLE_GATT_SRV_MIN_ENCRY_KEY_SIZE,                                \
    .uuid = BLE_UUID_INIT_16(BLE_GATT_SRV_CLIENT_CHAR_CONF_DESCR_TYPE_UUID)

#define BLE_GATT_SRV_CCCD_DEF_STR_DECLARE(NAME, NUM_CONN, PERM)                     \
    ble_gatt_descr_def_t BLE_GATT_SRV_CCCD_DEF_NAME(NAME) = {                       \
        BLE_GATT_SRV_CCCD_DEF_STR_FIELDS(NAME, NUM_CONN, PERM),                     \
    }

#define BLE_GATT_SRV_CCCD_PERM_DEFAULT                 (BLE_GATT_SRV_PERM_NONE)
#define BLE_GATT_SRV_CCCD_DECLARE(NAME, NUM_CONN, PERM, OP_FLAGS)                   \
    BLE_GATT_SRV_CCCD_BUFFER_DECLARE(NAME, NUM_CONN, OP_FLAGS);                     \
    BLE_GATT_SRV_CCCD_DEF_STR_DECLARE(NAME, NUM_CONN, PERM)
/**
 *@}
 */

/**
 *@name GATT_SRV_CLIENT_SUP_FEATURE
 * Use 1 bit for each Client to store Client Supported Feature, since just one
 * bit is defined in the spec.:
 * @see Table 7.6: Client Supported Features bit assignments, 7.2 CLIENT
 * SUPPORTED FEATURES, BLUETOOTH CORE SPECIFICATION Version 5.1 | Vol 3, Part G
 *@{
 */

/**
 * Bit assigned for Robust Caching Support
 *
 * 7.2 CLIENT SUPPORTED FEATURES, Table 7.6: Client Supported Features bit
 * assignments, BLUETOOTH CORE SPECIFICATION Version 5.1 | Vol 3, Part G page 2404
 */
#define BLE_GATT_SRV_CSF_ROBUST_CACHING                 (0x01U)

/**
 * Bit assigned for Enhanced ATT bearer
 *
 * Table 7.6: Client Supported Features bit assignments
 * BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part G page 1602
 */
#define BLE_GATT_SRV_CSF_EATT                           (0x02U)

/**
 * Bit assigned for Multiple Handle Value Notifications
 *
 * Table 7.6: Client Supported Features bit assignments
 * BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part G page 1603
 */
#define BLE_GATT_SRV_CSF_MULTI_HANDLE_VAL_NOTIFICATION  (0x04U)

#define BLE_GATT_SRV_CLIENT_SUP_FEATURE_NUM_BITS_PER_CONN    (4U)

#define BLE_GATT_SRV_CLIENT_SUP_FEATURE_VAL_MASK        (0x07U)

#define BLE_GATT_SRV_CLIENT_SUP_FEATURE_VALUE_LEN       (1U)
#define BLE_GATT_SRV_CLIENT_SUP_FEATURE_NUM_CONN_PER_BYTE    (8U / BLE_GATT_SRV_CLIENT_SUP_FEATURE_NUM_BITS_PER_CONN)
#define BLE_GATT_SRV_CLIENT_SUP_FEATURE_SIZE_X_CONN(NUM_CONN)  (((NUM_CONN) / \
                                                                 BLE_GATT_SRV_CLIENT_SUP_FEATURE_NUM_CONN_PER_BYTE) + 1U)
/**
 *@}
 */

/**
 *@name GATT_SRV_SUPPORTED_FEATURES
 * Server Supported Features Characteristic is used to indicate support for
 * server features. The server shall set a bit only if the corresponding
 * feature is supported.
 *
 * Table 7.11: Server Supported Features bit assignments
 * 7.4 SERVER SUPPORTED FEATURES
 * BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part G page 1605
 *@{
 */
#define BLE_GATT_SRV_SUPPORTED_FEATURES_EATT            (1U) /**< Enhanced ATT bearer supported. */

#define BLE_GATT_SRV_SUPPORTED_FEATURES_VAL_LEN         (1U)
/**
 *@}
 */

/**
 *@name GATT_SRV_CLIENT_SUP_FEATURE
 * Flags for aci_gatt_srv_notify
 *@{
 */
#define BLE_GATT_SRV_NOTIFY_FLAG_NOTIFICATION           (0x00U)
#define BLE_GATT_SRV_NOTIFY_FLAG_FLUSHABLE_NOTIFICATION (0x01U)
#define BLE_GATT_SRV_NOTIFY_FLAG_INDICATION             (0x02U)
/**
 *@}
 */

#define BLE_GATT_UNENHANCED_ATT_L2CAP_CID               (0x0004)

/**
 *@name UUID_TYPE
 * The following macro are used to define the type of an UUID:
 * @def BLE_UUID_TYPE_16BITS used for short 16 bits UUIDs. These are SIG defined.
 * @def BLE_UUID_TYPE_32BITS used for 32 bits UUIDs. These are SIG defined.
 * @def BLE_UUID_TYPE_128BITS used for long 128 bits UUIDs.
 *@{
 */
/** Used for short 16 bits UUIDs. These are SIG defined. */
#define BLE_UUID_TYPE_16BITS                            (16U)
/** Used for 32 bits UUIDs. These are SIG defined. */
#define BLE_UUID_TYPE_32BITS                            (32U)
/** Used for long 128 bits UUIDs. */
#define BLE_UUID_TYPE_128BITS                           (128U)
/**
 *@}
 */

/**
 *@name UUID_LENGTH
 *@{
 */
#define BLE_UUID_128_LENGTH                             (16U)
#define BLE_UUID_16_LENGTH                              (2U)
/**
 *@}
 */

/**
 *@name UUID_BASE
 *@{
 */
#define BLE_UUID_BASE_LENGTH                            (12U)
#define BLE_UUID_BASE                                   0xFB, 0x34, 0x9B, 0x5F, \
                                                        0x80, 0x00, 0x00, 0x80, \
                                                        0x00, 0x10, 0x00, 0x00
/**
 *@}
 */

/**
 *@anchor BLE_UUID_INIT
 *@name BLE_UUID_INIT Macros
 *@{
 */
#define BLE_UUID_INIT_128(UUID)     {                                           \
        .v_128.v = { UUID },                                                    \
        .uuid_type = BLE_UUID_TYPE_128BITS,                                     \
}
#define BLE_UUID_INIT_32(UUID)      {                                           \
        .v_32.base = { BLE_UUID_BASE },                                         \
        .v_32.v = UUID,                                                         \
        .uuid_type = BLE_UUID_TYPE_128BITS,                                     \
}
#define BLE_UUID_INIT_16(UUID)      {                                           \
        .v_16.base = { BLE_UUID_BASE },                                         \
        .v_16.v = UUID,                                                         \
        .v_16.empty = 0x0000U,                                                  \
        .uuid_type = BLE_UUID_TYPE_16BITS,                                      \
}

#define BLE_COPY_UUID_16(p, UUID)      do{                                      \
        const uint8_t uuid_base[] = {BLE_UUID_BASE};                            \
        memcpy((p).v_16.base,uuid_base,sizeof((p).v_16.base));                  \
        (p).v_16.v = UUID;                                                      \
        (p).v_16.empty = 0x0000U;                                               \
        (p).uuid_type = BLE_UUID_TYPE_16BITS;                                   \
}while(0);
/**
 *@}
 */
/**
 *@}
 */
/******************************************************************************
 * TYPES
 *****************************************************************************/
typedef struct ble_uuid_s {
#if defined(__CC_ARM)
    #pragma anon_unions
#endif
    union
    {
        struct {
            uint8_t v[BLE_UUID_128_LENGTH];
        } v_128;
        struct {
            uint8_t base[BLE_UUID_BASE_LENGTH];
            uint32_t v;
        } v_32;
        struct {
            uint8_t base[BLE_UUID_BASE_LENGTH];
            uint16_t v;
            uint16_t empty;
        } v_16;
    };
    uint8_t uuid_type;
} ble_uuid_t;

/**
 * @brief The following structure hold the information needed to write an
 * attribute. These information shall be valid for all the time the procedure is
 * in execution and can be freed on the reception of PROCEDURE COMPLETE event.
 */
typedef struct {
    uint16_t attr_h; /**< Attribute handle to write. */
    uint16_t attr_offset; /**< Offset from which start to write the attribute value */
    uint16_t data_len; /**< Length of data to write. */
    uint8_t *data_p; /**< Pointer to the data to write. */
} ble_gatt_clt_write_ops_t;

typedef struct ble_gatt_val_buffer_def_s {
    uint8_t op_flags; /**< See @ref SRV_VALBUFFER_OP_FLAGS */
    uint16_t val_len; /**< Actual value length. It can differ from buffer_len if BLE_GATT_SRV_PERM_ENCRY_READ the BLE_GATT_SRV_OP_VALUE_VAR_LENGTH_FLAG is set in op_flags */
    uint16_t buffer_len; /**< Buffer length. */
    uint8_t *buffer_p; /**< Pointer to the storage buffer. */
} ble_gatt_val_buffer_def_t;

typedef struct ble_gatt_descr_def_s {
    uint8_t properties; /**< See @ref GATT_SRV_DESCR_PROP. */
    /** Minimum key size required to access descriptor value. Valid only if permissions are
     *  BLE_GATT_SRV_PERM_ENCRY_READ or BLE_GATT_SRV_PERM_ENCRY_WRITE, otherwise ignored.
     *  See @ref GATT_SRV_KEY_SIZE for minimum and maximum values.
     */
    uint8_t min_key_size;
    uint8_t permissions; /**< Access permissions. See @ref GATT_SRV_PERMS. */
    ble_uuid_t uuid; /**< UUID for this descriptor */
    ble_gatt_val_buffer_def_t *val_buffer_p; /**< Pointer to the value buffer structure. */
} ble_gatt_descr_def_t;

typedef struct ble_gatt_chr_def_s {
    uint8_t properties; /**< @see GATT_SRV_CHAR_PROP */
    /** Minimum key size required to access characteristic value. Valid only if permissions are
     *  BLE_GATT_SRV_PERM_ENCRY_READ or BLE_GATT_SRV_PERM_ENCRY_WRITE, otherwise ignored.
     *  @see GATT_SRV_KEY_SIZE for minimum and maximum values.
     */
    uint8_t min_key_size;
    uint8_t permissions; /**< Access permissions. See @ref GATT_SRV_PERMS. */
    ble_uuid_t uuid; /**< UUID for this characteristic. Macros can be used to initialize the UUID: see @ref BLE_UUID_INIT. */
    struct {
        uint8_t descr_count; /**< Number of descriptors. */
        ble_gatt_descr_def_t *descrs_p; /**< Pointer to the descriptors vector. */
    } descrs; /**< List of descriptors. */
    ble_gatt_val_buffer_def_t *val_buffer_p; /**< Pointer to the value buffer structure. */
} ble_gatt_chr_def_t;

typedef struct ble_gatt_srv_def_s {
    ble_uuid_t uuid; /**< UUID for this service. Macros can be used to initialize the UUID: see @ref BLE_UUID_INIT. */
    uint8_t type; /**< primary/secondary. See @ref GATT_SRV_TYPE */
    uint16_t group_size; /**< Define the number of attribute handles reserved for this service. */
    struct {
        uint8_t incl_srv_count; /**< Number of services. */
        struct ble_gatt_srv_def_s **included_srv_pp; /**< List of pointers to the included service definition. */
    } included_srv;
    struct {
        uint8_t chr_count; /**< Number of characteristics. */
        ble_gatt_chr_def_t *chrs_p; /**< Pointer to characteristics vector. */
    } chrs; /**< List of characteristics. */
} ble_gatt_srv_def_t;

/******************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************/

/**
 *@}
 */

#endif /* BLE_GATT_H */
