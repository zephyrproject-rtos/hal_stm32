/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    aci_gatt_nwk.h
  * @author  MCD Application Team
  * @brief   Adaptation layer from GATT native interface to GATT network
  *                      processor interface
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

#ifndef ACI_GATT_NWK_H
#define ACI_GATT_NWK_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "app_conf.h"

/******************************************************************************
 * CONSTANT SYMBOLS
 *****************************************************************************/
#define ACI_GATT_WR_MAX_NUM_OF_LINK                 (CFG_BLE_NUM_RADIO_TASKS)

/**
 * If this bit is set, then Attribute  Modified Event is generated
 */
#define GATT_SERVER_ATTR_WRITE                      (0x01U)

#define GATT_DESCR_ACCESS_PERM_NONE                 (0x00U)
#define GATT_DESCR_ACCESS_PERM_READ                 (0x01U)
#define GATT_DESCR_ACCESS_PERM_WRITE                (0x02U)
#define GATT_DESCR_ACCESS_PERM_WRITE_NO_RESP        (0x04U)
#define GATT_DESCR_ACCESS_PERM_SIGNED_WRITE         (0x08U)

#define GATT_AUTHOR_OP_TYPE_READ                    (0x00U)
#define GATT_AUTHOR_OP_TYPE_WRITE                   (0x10U)
#define GATT_AUTHOR_OP_TYPE_WRITE_CMD               (0x11U)
#define GATT_AUTHOR_OP_TYPE_PREP_WRITE              (0x12U)

#define L2C_CID_ATTRIBUTE_PROTOCOL                  (4U)

/******************************************************************************
 * TYPES
 *****************************************************************************/
/** Documentation for C union Service_UUID_t */
typedef union Service_UUID_t_s
{
    /** 16-bit UUID
     */
    uint16_t Service_UUID_16;
    /** 128-bit UUID
     */
    uint8_t Service_UUID_128[16];
} Service_UUID_t;
/** Documentation for C union Char_UUID_t */
typedef union Char_UUID_t_s
{
    /** 16-bit UUID
     */
    uint16_t Char_UUID_16;
    /** 128-bit UUID
     */
    uint8_t Char_UUID_128[16];
} Char_UUID_t;
/** Documentation for C union Char_Desc_Uuid_t */
typedef union Char_Desc_Uuid_t_s
{
    /** 16-bit UUID
     */
    uint16_t Char_UUID_16;
    /** 128-bit UUID
     */
    uint8_t Char_UUID_128[16];
} Char_Desc_Uuid_t;
/******************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************/

/**
 * @brief Initialize ACI GATT nwk component
 *
 * @param pwrq_size[in] The size of the buffer assigned to PWRQ module.
 *
 * @return void
 *
 */
void ACI_gatt_nwk_init(uint16_t pwrq_size);

/**
 * @brief Reset ACI GATT nwk component, erasing any allocated attributes and values.
 *
 * @return void
 *
 */
void ACI_gatt_nwk_reset(void);

/**
 * @brief Procedure Complete Event handler. This function is used to release the
 * locket value buffer.
 *
 * @param Connection_Handle[in] The connection handle for which the Procedure
 *                              Complete event is issued.
 * @param CID[in] The channel ID.
 * @param Error_Code[in] The returned error coded.
 *
 * @return void
 *
 */
void ACI_gatt_nwk_proc_complete(uint16_t Connection_Handle, uint16_t CID, uint8_t Error_Code);

/**
 * @brief Disconnection Event handler. This function is used to release the
 * allocated resources for the given connection handle.
 *
 * @param Connection_Handle[in] The connection handle
 * @param CID[in] The channel ID.
 *
 * @return void
 *
 */
void ACI_gatt_nwk_disconnection(uint16_t Connection_Handle, uint16_t CID);

/**
 * @brief Add a service to GATT Server. When a service is created in the server, the host needs to
 * reserve the handle ranges for this service using Max_Attribute_Records parameter. This
 * parameter specifies the maximum number of attribute records that can be added to this
 * service (including the service attribute, include attribute, characteristic attribute,
 * characteristic value attribute and characteristic descriptor attribute). Handle of the created
 * service is returned in command complete event. Service declaration is taken from the service pool.
 * The attributes for characteristics and descriptors are allocated from the attribute pool.
 * @param Service_UUID_Type UUID type.
 * Values:
 * - 0x01: 16-bit UUID
 * - 0x02: 128-bit UUID
 * @param Service_UUID See @ref Service_UUID_t
 * @param Service_Type Service type.
 * Values:
 * - 0x01: Primary Service
 * - 0x02: Secondary Service
 * @param Max_Attribute_Records Maximum number of attribute records that can be added to this service
 * @param[out] Service_Handle Handle of the Service.
 * When this service is added, a handle is allocated by the server for this service.
 * Server also allocates a range of handles for this service from serviceHandle to <serviceHandle + max_attr_records - 1>
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_add_service_nwk(uint8_t Service_UUID_Type,
                                        Service_UUID_t *Service_UUID,
                                        uint8_t Service_Type,
                                        uint8_t Max_Attribute_Records,
                                        uint16_t *Service_Handle);
/**
 * @brief Include a service given by Included_Handle to another
 * service given by Service_Handle. Attribute server creates an INCLUDE definition
 * attribute and return the handle of this attribute in Included_handle.
 * @param Service_Handle Handle of the Service to which another service has to be included.
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param Included_Service_Handle Attribute Handle of the Service which has to be included in service
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param[out] Include_Handle Handle of the include declaration
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_include_service_nwk(uint16_t Service_Handle,
                                            uint16_t Included_Service_Handle,
                                            uint16_t *Include_Handle);
/**
 * @brief Add a characteristic to a service.
 * @param Service_Handle Handle of the Service to which the characteristic will be added
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param Char_UUID_Type UUID type.
 * Values:
 * - 0x01: 16-bit UUID
 * - 0x02: 128-bit UUID
 * @param Char_UUID See @ref Char_UUID_t
 * @param Char_Value_Length Maximum length of the characteristic value.
 * Values:
 * - 0 ... 512
 * @param Char_Properties Characteristic Properties (Volume 3, Part G, section 3.3.1.1 of Bluetooth Specification 4.1)
 * Flags:
 * - 0x00: CHAR_PROP_NONE
 * - 0x01: CHAR_PROP_BROADCAST (Broadcast)
 * - 0x02: CHAR_PROP_READ (Read)
 * - 0x04: CHAR_PROP_WRITE_WITHOUT_RESP (Write w/o resp)
 * - 0x08: CHAR_PROP_WRITE (Write)
 * - 0x10: CHAR_PROP_NOTIFY (Notify)
 * - 0x20: CHAR_PROP_INDICATE (Indicate)
 * - 0x40: CHAR_PROP_SIGNED_WRITE (Authenticated Signed Writes)
 * - 0x80: CHAR_PROP_EXT (Extended Properties)
 * @param Security_Permissions Security permission flags.
 * Flags:
 * - 0x00: None
 * - 0x01: AUTHEN_READ (Need authentication to read)
 * - 0x04: ENCRY_READ (Need encryption to read)
 * - 0x08: AUTHEN_WRITE (need authentication to write)
 * - 0x20: ENCRY_WRITE (need encryption to write)
 * @param GATT_Evt_Mask GATT event mask.
 * Flags:
 * - 0x00: GATT_DONT_NOTIFY_EVENTS
 * - 0x01: GATT_NOTIFY_ATTRIBUTE_WRITE
 * - 0x02: GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP
 * - 0x04: GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP
 * @param Enc_Key_Size Minimum encryption key size required to read the characteristic.
 * Values:
 * - 0x07 ... 0x10
 * @param Is_Variable Specify if the characteristic value has a fixed length or
 * a variable length.
 * Values:
 * - 0x00: Fixed length
 * - 0x01: Variable length
 * @param[out] Char_Handle Handle of the Characteristic that has been added.
 * It is the handle of the characteristic declaration.
 * The attribute that holds the characteristic value is allocated at the next handle,
 * followed by the Client Characteristic Configuration descriptor if the characteristic
 * has CHAR_PROP_NOTIFY or CHAR_PROP_INDICATE properties.
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_add_char_nwk(uint16_t Service_Handle,
                                     uint8_t Char_UUID_Type,
                                     Char_UUID_t *Char_UUID,
                                     uint16_t Char_Value_Length,
                                     uint8_t Char_Properties,
                                     uint8_t Security_Permissions,
                                     uint8_t GATT_Evt_Mask,
                                     uint8_t Enc_Key_Size,
                                     uint8_t Is_Variable,
                                     uint16_t *Char_Handle);

/**
 * @brief Add a characteristic descriptor to a characteristic.
 * @param Char_Handle Handle of the characteristic to which description has to be added
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param Char_Desc_Uuid_Type UUID type.
 * Values:
 * - 0x01: 16-bit UUID
 * - 0x02: 128-bit UUID
 * @param Char_Desc_Uuid See @ref Char_Desc_Uuid_t
 * @param Char_Desc_Value_Max_Len The maximum length of the descriptor value
 * Values:
 * - 0 ... 512
 * @param Char_Desc_Value_Length Current Length of the characteristic descriptor value
 * Values:
 * - 0 ... 512
 * @param Char_Desc_Value Value of the characteristic description
 * @param Security_Permissions Security permission flags.
 * Flags:
 * - 0x00: None
 * - 0x01: AUTHEN_READ (Need authentication to read)
 * - 0x04: ENCRY_READ (Need encryption to read)
 * - 0x08: AUTHEN_WRITE (need authentication to write)
 * - 0x20: ENCRY_WRITE (need encryption to write)
 * @param Access_Permissions Access permission
 * Flags:
 * - 0x00: None
 * - 0x01: READ
 * - 0x02: WRITE
 * - 0x04: WRITE_WO_RESP
 * - 0x08: SIGNED_WRITE
 * @param GATT_Evt_Mask GATT event mask.
 * Flags:
 * - 0x00: GATT_DONT_NOTIFY_EVENTS
 * - 0x01: GATT_NOTIFY_ATTRIBUTE_WRITE
 * - 0x02: GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP
 * - 0x04: GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP
 * @param Enc_Key_Size Minimum encryption key size required to read the characteristic.
 * Values:
 * - 0x07 ... 0x10
 * @param Is_Variable Specify if the characteristic value has a fixed length or
 * a variable length.
 * Values:
 * - 0x00: Fixed length
 * - 0x01: Variable length
 * @param[out] Char_Desc_Handle Handle of the characteristic descriptor
 * Values:
 * - 0x0001 ... 0xFFFF
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_add_char_desc_nwk(uint16_t Char_Handle,
                                          uint8_t Char_Desc_Uuid_Type,
                                          Char_Desc_Uuid_t *Char_Desc_Uuid,
                                          uint16_t Char_Desc_Value_Max_Len,
                                          uint16_t Char_Desc_Value_Length,
                                          uint8_t Char_Desc_Value[],
                                          uint8_t Security_Permissions,
                                          uint8_t Access_Permissions,
                                          uint8_t GATT_Evt_Mask,
                                          uint8_t Enc_Key_Size,
                                          uint8_t Is_Variable,
                                          uint16_t *Char_Desc_Handle);

/**
 * @brief Update an attribute value.
 *
 * @param Attr_Handle Handle of the attribute
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param Val_Offset The offset from which the attribute value has to be updated.
 * If this is set to 0 and the attribute value is of variable length, then the length of the attribute will be set to the Char_Value_Length.
 * If the Val_Offset is set to a value greater than 0, then the length of the attribute will be set to the maximum length as
 * specified for the attribute while adding the characteristic.
 * Values:
 * - 0 ... 511
 * @param Value_Length Length of the attribute value in octets
 * @param Value Attribute value
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_write_handle_value_nwk(uint16_t Attr_Handle,
                                               uint16_t Val_Offset,
                                               uint16_t Value_Length,
                                               uint8_t Value[]);
/**
 * @brief Delete the specified characteristic from the service.
 * @param Char_Handle Handle of the characteristic which has to be deleted
 * Values:
 * - 0x0001 ... 0xFFFF
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_rm_char_nwk(uint16_t Char_Handle);
/**
 * @brief Delete the specified service from the GATT server database.
 * @param Serv_Handle Handle of the service to be deleted
 * Values:
 * - 0x0001 ... 0xFFFF
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_rm_service_nwk(uint16_t Serv_Handle);
/**
 * @brief Delete the Include definition from the service.
 * @param Include_Handle Handle of the included service which has to be deleted
 * Values:
 * - 0x0001 ... 0xFFFF
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_rm_include_service_nwk(uint16_t Include_Handle);

/**
 * @brief This command sets the security permission for the attribute handle specified. Currently the
 * setting of security permission is allowed only for client configuration descriptor.
 * @param Attr_Handle Handle of the attribute whose security permission has to be modified
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param Security_Permissions Security permission flags.
 * Flags:
 * - 0x00: None
 * - 0x01: AUTHEN_READ (Need authentication to read)
 * - 0x04: ENCRY_READ (Need encryption to read)
 * - 0x08: AUTHEN_WRITE (need authentication to write)
 * - 0x20: ENCRY_WRITE (need encryption to write)
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_set_security_permission_nwk(uint16_t Attr_Handle,
                                                    uint8_t Security_Permissions);
/**
 * @brief Reads the value of the attribute handle specified from the local GATT database.
 * @param Attr_Handle Handle of the attribute to read
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param Offset Offset from which the value needs to be read
 * Values:
 * - 0 ... 511
 * @param Value_Length_Requested Maximum number of octets to be returned as attribute value
 * Values:
 * - 0 ... 512
 * @param[out] Length Length of the attribute value
 * @param[out] Value_Length Length in octets of the Value parameter
 * @param[out] Value Attribute value
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_read_handle_value_nwk(uint16_t Attr_Handle,
                                              uint16_t Offset,
                                              uint16_t Value_Length_Requested,
                                              uint16_t *Length,
                                              uint16_t *Value_Length,
                                              uint8_t Value[]);

/**
 * @brief Reads the value for that kind of attributes that have different values
 * for each connection, e.g. the Client Characteristic Configuration Descriptors.
 * @param Connection_Handle Connection handle for which the attribute value will be read.
 * @param Attr_Handle Handle of the attribute to read
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param[out] Value_Length Length in octets of the Value parameter.
 * @param[out] Value Where value is stored. The length of the Value buffer should
 *                   be at least equal to 16 octets.
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_read_multiple_instance_handle_value_nwk(uint16_t Connection_Handle,
                                                                uint16_t Attr_Handle,
                                                                uint16_t *Value_Length,
                                                                uint8_t Value[]);
/**
 * @brief This command sets the access permission for the attribute handle specified.
 * @param Attr_Handle Handle of the attribute whose security permission has to be modified
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param Access_Permissions Access permission
 * Values:
 * - 0x00: None
 * - 0x01: READ
 * - 0x02: WRITE
 * - 0x04: WRITE_NO_RESP
 * - 0x08: SIGNED_WRITE
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_set_access_permission_nwk(uint16_t Attr_Handle,
                                                  uint8_t Access_Permissions);

/**
 * @brief
 * @param Conn_Handle Connection handle to be used to identify the connection with the peer device.
 * Values:
 * - 0x0000 ... 0x0EFF
 * @param Item_Index
 * @param[out] Attr_Handle
 * @param[out] Value_Offset
 * @param[out] Value_Length Length in octets of the Value parameter
 * @param[out] Value Attribute value
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_read_prepare_queue_nwk(uint16_t Conn_Handle,
                                               uint8_t Item_Index,
                                               uint16_t *Attr_Handle,
                                               uint16_t *Value_Offset,
                                               uint16_t *Value_Length,
                                               uint8_t Value[]);
/**
 * @brief Start the procedure to write an attribute value.
 * When the procedure is completed, a @ref aci_gatt_clt_proc_complete_event event is generated.
 * During the procedure, @ref aci_att_clt_prepare_write_resp_event and @ref aci_att_clt_exec_write_resp_event
 * events are raised.
 * @param Connection_Handle Connection handle that identifies the connection.
 * Values:
 * - 0x0000 ... 0x0EFF
 * @param Attr_Handle Handle of the attribute to be written
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param Attribute_Val_Length Length of the value to be written
 * @param Attribute_Val Value to be written
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_clt_write_nwk(uint16_t Connection_Handle,
                                  uint16_t CID,
                                  uint16_t Attr_Handle,
                                  uint16_t Attribute_Val_Length,
                                  uint8_t Attribute_Val[]);
/**
 * @brief Start the procedure to write a long attribute value.
 * When the procedure is completed, a @ref aci_gatt_clt_proc_complete_event event is generated.
 * During the procedure, @ref aci_att_clt_prepare_write_resp_event and @ref aci_att_clt_exec_write_resp_event
 * events are raised.
 * @param Connection_Handle Connection handle that identifies the connection.
 * Values:
 * - 0x0000 ... 0x0EFF
 * @param Attr_Handle Handle of the attribute to be written
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param Val_Offset Offset at which the attribute has to be written
 * Values:
 * - 0 ... 511
 * @param Attribute_Val_Length Length of the value to be written
 * @param Attribute_Val Value to be written
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_clt_write_long_nwk(uint16_t Connection_Handle,
                                       uint16_t CID,
                                       uint16_t Attr_Handle,
                                       uint16_t Val_Offset,
                                       uint16_t Attribute_Val_Length,
                                       uint8_t Attribute_Val[]);
/**
 * @brief Start the procedure to write a characteristic reliably.
 * When the procedure is completed, a  @ref aci_gatt_clt_proc_complete_event event is generated.
 * During the procedure, @ref aci_att_clt_prepare_write_resp_event and @ref aci_att_clt_exec_write_resp_event
 * events are raised.
 * @param Connection_Handle Connection handle that identifies the connection.
 * Values:
 * - 0x0000 ... 0x0EFF
 * @param Attr_Handle Handle of the attribute to be written
 * Values:
 * - 0x0001 ... 0xFFFF
 * @param Val_Offset Offset at which the attribute has to be written
 * Values:
 * - 0 ... 511
 * @param Attribute_Val_Length Length of the value to be written
 * @param Attribute_Val Value to be written
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_clt_write_char_reliable_nwk(uint16_t Connection_Handle,
                                                uint16_t CID,
                                                uint16_t Attr_Handle,
                                                uint16_t Val_Offset,
                                                uint16_t Attribute_Val_Length,
                                                uint8_t Attribute_Val[]);

/**
 * @brief
 * @param Conn_Handle Connection handle to be used to identify the connection with the peer device.
 * Values:
 * - 0x0000 ... 0x0EFF
 * @param Attr_Handle Offset from which the value needs to be read or write
 * Values:
 * - 0 ... 511
 * @param Operation_Type
 * Values:
 * - 0x00: Read
 * - 0x10: Write Request
 * - 0x11: Write Command or Signed Write Command
 * - 0x12: Prepare Write Request
 * @param Error_Code Offset from which the value needs to be read or write
 * Values:
 * - 0 ... 511
 * @param Data_Offset Offset from which the value needs to be read or write
 * Values:
 * - 0 ... 511
 * @param Data_Length Length of Data field
 * @param Data The data that the client has requested to write
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_authorize_resp_nwk(uint16_t Conn_Handle,
                                           uint16_t CID,
                                           uint16_t Attr_Handle,
                                           uint8_t Operation_Type,
                                           uint8_t Error_Code,
                                           uint16_t Data_Offset,
                                           uint16_t Data_Length,
                                           uint8_t Data[]);

/**
 * @brief This event is generated if authorization is needed to access the attribute value.
 * @ref aci_gatt_srv_authorize_resp_nwk command must be sent in response to this event.
 * @param Conn_Handle Connection handle to be used to identify the connection with the peer device.
 * Values:
 * - 0x0000 ... 0x0EFF
 * @param Attr_Handle
 * @param Operation_Type
 * Values:
 * - 0x00: Read
 * - 0x10: Write Request
 * - 0x11: Write Command or Signed Write Command
 * - 0x12: Prepare Write Request
 * @param Attr_Val_Offset Offset from which the value needs to be read or write
 * Values:
 * - 0 ... 511
 * @param Data_Length Length of Data field
 * @param Data The data that the client has requested to write
 * @retval None
 */
void aci_gatt_srv_authorize_nwk_event(uint16_t Conn_Handle,
                                      uint16_t CID,
                                      uint16_t Attr_Handle,
                                      uint8_t Operation_Type,
                                      uint16_t Attr_Val_Offset,
                                      uint8_t Data_Length,
                                      uint8_t Data[]);

/**
 * @brief Response to aci_att_srv_exec_write_req_event.
 * @param Conn_Handle Connection handle that identifies the connection.
 *        Values:
 *        - 0x0000 ... 0x0EFF
 * @param Exec If 1, allow execution of queued writes. If 0 flush all queued
 *        writes for the given connection handle.
 *        Values:
 *        - 0x00: FLUSH
 *        - 0x01: EXECUTE
 * @retval Value indicating success or error code.
 */
tBleStatus aci_gatt_srv_exec_write_resp_nwk(uint16_t Conn_Handle,
                                            uint16_t CID,
                                            uint8_t Exec);

#endif
