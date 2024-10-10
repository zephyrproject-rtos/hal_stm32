/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    aci_gatt_nwk.c
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

/******************************************************************************
 * INCLUDE HEADER FILES
 *****************************************************************************/
#include "app_common.h"
#include "ble.h"
#include "aci_gatt_nwk.h"
#include "gap_profile.h"
#include "gatt_profile.h"
#include "osal.h"
#include "eatt_pwrq.h"
#include "dm_alloc.h"
#include "dtm_cmd_db.h"

/******************************************************************************
 * LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *****************************************************************************/
typedef enum {
    DEF_TYPE_SERVICE = 0, /**< Service definition node. */
    DEF_TYPE_CHAR, /**< Characteristic definition node. */
    DEF_TYPE_DESCR, /**<Characteristic Descriptor definition node. */
} def_type_et;

/**
 * @brief Define a Characteristic or Descriptor value buffer.
 */
typedef struct ACI_gatt_nwk_buffer_s {
    bool is_variable; /**< Indicate if the value has or not a variable length. */
    uint8_t event_mask; /**< Store the events bit mask that are requested on value access. */
    uint16_t val_len; /**< Actual Value Length. */
    uint16_t buffer_len; /**< Value Buffer length. */
    uint8_t buffer_va[]; /**< Value buffer. */
} ACI_gatt_nwk_value_t;

/**
 * @brief Define an Attribute definition node.
 */
typedef struct ACI_gatt_nwk_def_entry_s {
    def_type_et def_type; /**< The type of definition. @see def_type_et */
    uint16_t attr_handle; /**< The attribute handle assigned to this definition. */
    uint8_t *def_p; /**< Pointer to the User Definition struct. The kind of definition is indicated by def_type parameter. */
    ACI_gatt_nwk_value_t *val_p; /**< Pointer to the value buffer. */
    struct ACI_gatt_nwk_def_entry_s *next_p; /**< Next node entry in the Single Linked list. */
} ACI_gatt_nwk_def_entry_t;

typedef struct ACI_gatt_nwk_write_ops_s {
    uint16_t conn_handle; /**< Write buffer mutex. */
    uint16_t cid; /**< Channel ID. */
    ble_gatt_clt_write_ops_t *write_ops_p; /**< Write parameters. */
    struct ACI_gatt_nwk_write_ops_s *next_p;
    uint8_t buffer[]; /**< Write value buffer. */
} ACI_gatt_nwk_write_ops_t;

struct {
    ACI_gatt_nwk_write_ops_t *write_ops_head_p;
    ACI_gatt_nwk_def_entry_t *head; /**< Head of definition list. */
} aci_gatt_nwk_ctx_s;

/*******************************************************************************
 * PRIVATE PROTOTYPES
 ******************************************************************************/

#if (CFG_BLE_CONNECTION_ENABLED == 1) && (BLESTACK_CONTROLLER_ONLY == 0)

/**
 * @brief Write all queued write for the given connection handle.
 *
 * @param conn_handle[in] Connection handle from witch the Prepared Write was
 *                        received.
 *
 * @return ATT error code.
 *
 */
static uint8_t ACI_gatt_nwk_write_queue(uint16_t conn_handle);

/**
 * @brief Add a new definition node.
 *
 * @param def_p[in] Pointer to the new node.
 *
 * @return void.
 *
 */
static void ACI_gatt_nwk_add_def_entry(ACI_gatt_nwk_def_entry_t *def_p);

/**
 * @brief Remove a definition node.
 *
 * @param def_p[in] Pointer to the node to remove.
 *
 * @return void.
 *
 */
static void ACI_gatt_nwk_rm_def_entry(ACI_gatt_nwk_def_entry_t *def_p);

/**
 * @brief Free memory assigned to store definition node.
 *
 * @param def_p[in] Pointer to the node to free.
 *
 * @return void.
 *
 */
static void ACI_gatt_nwk_free_def_entry(ACI_gatt_nwk_def_entry_t *def_p);

/**
 * @brief Release definition entry.
 *
 * @param def_p[in] Pointer to the definition node.
 * @param type[in] The type of node to release.
 *
 * @return void.
 *
 */
static void ACI_gatt_nwk_release_def(ACI_gatt_nwk_def_entry_t *def_p, def_type_et type);

/**
 * @brief Find definition entry through its attribute handle.
 *
 * @param attr_handle[in] The attribute handle to find.
 *
 * @return Pointer to found node or NULL.
 *
 */
static ACI_gatt_nwk_def_entry_t *ACI_gatt_nwk_find_def_entry(uint16_t attr_handle);

/**
 * @brief Set the UUID value.
 *
 * @param src_uuid_type[in] The UUID type
 *                          - 0x01: 16 bits UUID
 *                          - 0x02: 128 bits UUID.
 * @param src_uuid_p[in] Source UUID pointer.
 * @param uuid_p[out] The destination UUID pointer.
 *
 * @return Pointer to found node or NULL.
 *
 */
static tBleStatus ACI_gatt_nwk_set_uuid(const uint8_t src_uuid_type,
                                        const uint8_t *src_uuid_p,
                                        ble_uuid_t *uuid_p);

/**
 * @brief Allocate and add a write_ops structure and its buffer.
 *
 * @param conn_handle[in] The connection handle.
 * @param cid[in] The channel ID.
 * @param num_write_ops[in] Number of attribute to write.
 * @param buffer_size[in] Size of value buffer.
 *
 * @return Pointer to allocated write ops structure.
 *
 */
static ACI_gatt_nwk_write_ops_t *ACI_gatt_nwk_add_write_ops(uint16_t conn_handle,
                                                            uint16_t cid,
                                                            uint8_t num_write_ops,
                                                            uint16_t buffer_size);

/**
 * @brief Release a write_ops structure and its buffer.
 *
 * @param conn_handle[in] The connection handle.
 * @param cid[in] The channel ID.
 *
 * @return Pointer to allocated write ops structure.
 *
 */
static void ACI_gatt_nwk_rm_write_ops(uint16_t conn_handle, uint16_t cid);
/******************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************/
void ACI_gatt_nwk_reset(void)
{
    aci_gatt_nwk_ctx_s.head = NULL;
    aci_gatt_nwk_ctx_s.write_ops_head_p = NULL;

    /**
     * Reset Prepare Write Queue.
     */
    EATT_pwrq_reset();
}

void ACI_gatt_nwk_init(uint16_t pwrq_size)
{
    uint8_t *q_wr_p;

    ACI_gatt_nwk_reset();

    if (pwrq_size > 0U)
    {
        q_wr_p = (uint8_t *)dm_alloc(pwrq_size);
        if (q_wr_p == NULL)
        {
            pwrq_size = 0U;
        }
    }
    else
    {
        q_wr_p = NULL;
    }
    (void)EATT_pwrq_init(pwrq_size, q_wr_p);
}

void ACI_gatt_nwk_proc_complete(uint16_t Connection_Handle,
                                uint16_t CID,
                                uint8_t Error_Code)
{
    ACI_gatt_nwk_rm_write_ops(Connection_Handle, CID);
}

void ACI_gatt_nwk_disconnection(uint16_t Connection_Handle, uint16_t CID)
{
    ACI_gatt_nwk_rm_write_ops(Connection_Handle, CID);

    /**
     * Propagate disconnection event to the Prepare Write Queue module to flush
     * all pending prepared write.
     */
    EATT_pwrq_flush(Connection_Handle, EATT_PWRQ_CID_ALL);
}

tBleStatus aci_gatt_srv_add_service_nwk(uint8_t Service_UUID_Type,
                                        Service_UUID_t *Service_UUID,
                                        uint8_t Service_Type,
                                        uint8_t Max_Attribute_Records,
                                        uint16_t *Service_Handle)
{
    ble_gatt_srv_def_t *srv_def_p;
    ACI_gatt_nwk_def_entry_t *def_p;
    tBleStatus ret;

    /**
     * Allocate service node.
     */
    def_p = (ACI_gatt_nwk_def_entry_t *)dm_alloc(sizeof(ACI_gatt_nwk_def_entry_t));
    if (def_p == NULL)
    {
        return BLE_STATUS_OUT_OF_MEMORY;
    }
    memset(def_p, 0, sizeof(ACI_gatt_nwk_def_entry_t));

    /**
     * Allocate service definition.
     */
    srv_def_p = (ble_gatt_srv_def_t *)dm_alloc(sizeof(ble_gatt_srv_def_t));
    if (srv_def_p == NULL)
    {
        return BLE_STATUS_OUT_OF_MEMORY;
    }
    memset(srv_def_p, 0, sizeof(ble_gatt_srv_def_t));

    /**
     * Populate service definition.
     */
    srv_def_p->chrs.chr_count = 0U;
    srv_def_p->group_size = Max_Attribute_Records;
    srv_def_p->type = Service_Type;
    srv_def_p->included_srv.incl_srv_count = 0U;
    ACI_gatt_nwk_set_uuid(Service_UUID_Type, (uint8_t const *)Service_UUID,
                          &srv_def_p->uuid);

    /**
     * Add new service.
     */
    ret = aci_gatt_srv_add_service(srv_def_p);
    if (ret == BLE_STATUS_SUCCESS)
    {
        def_p->attr_handle = aci_gatt_srv_get_service_handle(srv_def_p);
        def_p->val_p = NULL;
        def_p->def_p = (uint8_t *)srv_def_p;
        def_p->def_type = DEF_TYPE_SERVICE;

        /**
         * Add new node to attribute definition list.
         */
        ACI_gatt_nwk_add_def_entry(def_p);

        *Service_Handle = def_p->attr_handle;
    }
    else
    {
        /**
         * The service is not registered. Release allocated resources.
         */
        dm_free((uint32_t *)def_p->def_p);
        dm_free((uint32_t *)def_p);
    }

    return ret;
}

tBleStatus aci_gatt_srv_include_service_nwk(uint16_t Service_Handle,
                                            uint16_t Included_Service_Handle,
                                            uint16_t *Include_Handle)
{
    tBleStatus ret;
    uint16_t handle;
    ble_gatt_srv_def_t *srv_def_p;

    ret = aci_gatt_srv_include_service(Service_Handle, Included_Service_Handle);
    if (ret == BLE_STATUS_SUCCESS)
    {
        srv_def_p = NULL;
        handle = Gatt_profile_get_service_handle();
        if (handle == Included_Service_Handle)
        {
            srv_def_p = Gatt_profile_get_service_definition_p();
        }
        else
        {
            handle = Gap_profile_get_service_handle();
            if (handle == Included_Service_Handle)
            {
                srv_def_p = Gap_profile_get_service_definition_p();
            }
            else
            {
                ACI_gatt_nwk_def_entry_t *def_p;

                def_p = ACI_gatt_nwk_find_def_entry(Included_Service_Handle);
                srv_def_p = (ble_gatt_srv_def_t *)def_p->def_p;
            }
        }

        *Include_Handle = aci_gatt_srv_get_include_service_handle(Service_Handle,
                                                                  srv_def_p);
    }

    return ret;
}

tBleStatus aci_gatt_srv_add_char_nwk(uint16_t Service_Handle,
                                     uint8_t Char_UUID_Type,
                                     Char_UUID_t *Char_UUID,
                                     uint16_t Char_Value_Length,
                                     uint8_t Char_Properties,
                                     uint8_t Security_Permissions,
                                     uint8_t GATT_Evt_Mask,
                                     uint8_t Enc_Key_Size,
                                     uint8_t Is_Variable,
                                     uint16_t *Char_Handle)
{
    ble_gatt_chr_def_t *chr_def_p;
    ACI_gatt_nwk_def_entry_t *def_p;
    Char_Desc_Uuid_t uuid;
    tBleStatus ret;

    if (Char_Value_Length > BLE_GATT_MAX_ATTR_VALUE_SIZE)
    {
        return BLE_STATUS_INVALID_PARAMS;
    }

    /**
     * Allocate characteristic node.
     */
    def_p = (ACI_gatt_nwk_def_entry_t *)dm_alloc(sizeof(ACI_gatt_nwk_def_entry_t));
    if (def_p == NULL)
    {
        return BLE_STATUS_OUT_OF_MEMORY;
    }
    memset(def_p, 0, sizeof(ACI_gatt_nwk_def_entry_t));

    /**
     * Allocate characteristic definition.
     */
    chr_def_p = (ble_gatt_chr_def_t *)dm_alloc(sizeof(ble_gatt_chr_def_t));
    if (chr_def_p == NULL)
    {
        dm_free((uint32_t *)def_p);

        return BLE_STATUS_OUT_OF_MEMORY;
    }
    memset(chr_def_p, 0, sizeof(ble_gatt_chr_def_t));

    /**
     * Populate characteristic definition.
     */
    ACI_gatt_nwk_set_uuid(Char_UUID_Type, (uint8_t const *)Char_UUID,
                          &chr_def_p->uuid);
    chr_def_p->min_key_size = Enc_Key_Size;
    chr_def_p->properties = Char_Properties;
    chr_def_p->permissions = Security_Permissions;
    chr_def_p->descrs.descr_count = 0U;

    /**
     * Set characteristic node definition pointer.
     */
    def_p->def_p = (uint8_t *)chr_def_p;

    /**
     * Allocate structure to store characteristic value.
     */
    def_p->val_p = (ACI_gatt_nwk_value_t *)dm_alloc(sizeof(ACI_gatt_nwk_value_t) +
                                                    Char_Value_Length);
    if (def_p->val_p == NULL)
    {
        dm_free((uint32_t *)def_p->def_p);
        dm_free((uint32_t *)def_p);

        return BLE_STATUS_OUT_OF_MEMORY;
    }

    /**
     * Populate characteristic value structure.
     */
    def_p->val_p->val_len = Char_Value_Length;
    def_p->val_p->is_variable = Is_Variable;
    def_p->val_p->buffer_len = Char_Value_Length;
    def_p->val_p->event_mask = GATT_Evt_Mask;
    memset(def_p->val_p->buffer_va, 0, Char_Value_Length);

    /**
     * Register the characteristic.
     */
    ret = aci_gatt_srv_add_char(chr_def_p, Service_Handle);
    if (ret == BLE_STATUS_SUCCESS)
    {
        *Char_Handle = aci_gatt_srv_get_char_decl_handle(chr_def_p);
        def_p->attr_handle = *Char_Handle + 1;
        def_p->def_type = DEF_TYPE_CHAR;

        /**
         * Add new node to attribute definition list.
         */
        ACI_gatt_nwk_add_def_entry(def_p);
    }
    else
    {
        /**
         * The characteristic is not register. Release any allocated resources.
         */
        dm_free((uint32_t *)def_p->val_p);
        dm_free((uint32_t *)def_p->def_p);
        dm_free((uint32_t *)def_p);
    }

    /**
     * Register mandatory descriptor on the basis of characteristic properties.
     */
    if ((ret == BLE_STATUS_SUCCESS) &&
        ((chr_def_p->properties & (BLE_GATT_SRV_CHAR_PROP_NOTIFY | BLE_GATT_SRV_CHAR_PROP_INDICATE)) != 0U))
    {
        /**
         * Add CCCD.
         */
        uint16_t attr_handle;
        uint8_t cccd_val[BLE_GATT_SRV_CCCD_BUFF_SIZE(ACI_GATT_WR_MAX_NUM_OF_LINK)] = { 0 };

        uuid.Char_UUID_16 = BLE_GATT_SRV_CLIENT_CHAR_CONF_DESCR_TYPE_UUID;
        ret = aci_gatt_srv_add_char_desc_nwk(*Char_Handle,
                                             0x01,
                                             &uuid,
                                             BLE_GATT_SRV_CCCD_BUFF_SIZE(ACI_GATT_WR_MAX_NUM_OF_LINK),
                                             BLE_GATT_SRV_CCCD_BUFF_SIZE(ACI_GATT_WR_MAX_NUM_OF_LINK),
                                             cccd_val,
                                             Security_Permissions &
                                             (BLE_GATT_SRV_PERM_AUTHEN_WRITE |
                                              BLE_GATT_SRV_PERM_ENCRY_WRITE),
                                             GATT_DESCR_ACCESS_PERM_READ |
                                             GATT_DESCR_ACCESS_PERM_WRITE,
                                             GATT_SERVER_ATTR_WRITE,
                                             0x07U,
                                             FALSE,
                                             &attr_handle);
    }
    if ((ret == BLE_STATUS_SUCCESS) &&
        ((chr_def_p->properties & BLE_GATT_SRV_CHAR_PROP_BROADCAST) != 0U))
    {
        /**
         * Add Server Characteristic Configuration Descriptor.
         */
        uint16_t attr_handle;
        uint8_t val[2] = { 0 };

        uuid.Char_UUID_16 = BLE_GATT_SRV_SERVER_CHAR_CONF_DESCR_TYPE_UUID;
        ret = aci_gatt_srv_add_char_desc_nwk(*Char_Handle,
                                             0x01,
                                             &uuid,
                                             2,
                                             2,
                                             val,
                                             Security_Permissions &
                                             (BLE_GATT_SRV_PERM_AUTHEN_WRITE |
                                              BLE_GATT_SRV_PERM_ENCRY_WRITE),
                                             GATT_DESCR_ACCESS_PERM_READ |
                                             GATT_DESCR_ACCESS_PERM_WRITE,
                                             GATT_SERVER_ATTR_WRITE,
                                             0x07U,
                                             FALSE,
                                             &attr_handle);
    }
    if ((ret == BLE_STATUS_SUCCESS) &&
        ((chr_def_p->properties & BLE_GATT_SRV_CHAR_PROP_EXTENDED_PROP) != 0U))
    {
        /**
         * Add Server Characteristic Extended Properties Descriptor.
         */
        uint16_t attr_handle;
        uint8_t val[2] = { 0 };

        uuid.Char_UUID_16 = BLE_GATT_SRV_CHAR_EXT_PROP_DESCR_TYPE_UUID;
        ret = aci_gatt_srv_add_char_desc_nwk(*Char_Handle,
                                             0x01,
                                             &uuid,
                                             2,
                                             2,
                                             val,
                                             BLE_GATT_SRV_PERM_NONE,
                                             GATT_DESCR_ACCESS_PERM_READ,
                                             0x00U,
                                             0x07U,
                                             FALSE,
                                             &attr_handle);
    }

    return ret;
}

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
                                          uint16_t *Char_Desc_Handle)
{
    ble_gatt_descr_def_t *descr_def_p;
    ACI_gatt_nwk_def_entry_t *def_p;
    tBleStatus ret = BLE_STATUS_OUT_OF_MEMORY;

    descr_def_p = NULL;
    if (Char_Desc_Value_Max_Len > BLE_GATT_MAX_ATTR_VALUE_SIZE)
    {
        return BLE_STATUS_INVALID_PARAMS;
    }

    /**
     * Allocate characteristic descriptor node.
     */
    def_p = (ACI_gatt_nwk_def_entry_t *)dm_alloc(sizeof(ACI_gatt_nwk_def_entry_t));
    if (def_p == NULL)
    {
        goto __error;
    }
    memset(def_p, 0, sizeof(ACI_gatt_nwk_def_entry_t));

    /**
     * Allocate characteristic descriptor definition.
     */
    descr_def_p = (ble_gatt_descr_def_t *)dm_alloc(sizeof(ble_gatt_descr_def_t));
    if (descr_def_p == NULL)
    {
        goto __error;
    }
    memset(descr_def_p, 0, sizeof(ble_gatt_descr_def_t));

    /**
     * Set characteristic descriptor node definition pointer.
     */
    def_p->def_p = (uint8_t *)descr_def_p;

    if ((Char_Desc_Uuid_Type == 0x01) &&
        ((Char_Desc_Uuid->Char_UUID_16 == BLE_GATT_SRV_CLIENT_CHAR_CONF_DESCR_TYPE_UUID) ||
         (Char_Desc_Uuid->Char_UUID_16 == BLE_GATT_SRV_CHAR_EXT_PROP_DESCR_TYPE_UUID)))
    {
        /**
         * For CCCD and Characteristic Extended Properties Descriptor the value
         * buffer shall be directly accessible by the stack hence the value
         * buffer shall be allocated.
         */
        descr_def_p->val_buffer_p = (ble_gatt_val_buffer_def_t *)
                                    dm_alloc(sizeof(ble_gatt_val_buffer_def_t));
        if (descr_def_p->val_buffer_p == NULL)
        {
            goto __error;
        }
        memset(descr_def_p->val_buffer_p, 0, sizeof(ble_gatt_val_buffer_def_t));

        /**
         * Allocate the buffer that store descriptor value.
         */
        descr_def_p->val_buffer_p->buffer_p = (uint8_t *)dm_alloc(
            sizeof(uint8_t) * Char_Desc_Value_Max_Len);
        if (descr_def_p->val_buffer_p->buffer_p == NULL)
        {
            goto __error;
        }

        /**
         * Copy provided initial descriptor value.
         */
        (void)Osal_MemCpy(descr_def_p->val_buffer_p->buffer_p, Char_Desc_Value,
                          Char_Desc_Value_Length);
        descr_def_p->val_buffer_p->buffer_len = Char_Desc_Value_Max_Len;
        if ((GATT_Evt_Mask & GATT_NOTIFY_ATTRIBUTE_WRITE) != 0U)
        {
            /**
             * Once the descriptor value is changed by a client an attribute
             * modified event shall be generated to indicate such value to user
             * application.
             */
            descr_def_p->val_buffer_p->op_flags =
                BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG;
        }
    }
    else
    {
        /**
         * Characteristic descriptor value is access by the stack through the
         * events mechanism (aci_gatt_srv_write_event and aci_gatt_srv_read_event).
         * Allocate value buffer to store descriptor value.
         */
        def_p->val_p = (ACI_gatt_nwk_value_t *)dm_alloc(sizeof(ACI_gatt_nwk_value_t) +
                                                        Char_Desc_Value_Max_Len);
        if (def_p->val_p == NULL)
        {
            goto __error;
        }

        /**
         * Copy provided initial descriptor value.
         */
        (void)Osal_MemCpy(def_p->val_p->buffer_va, Char_Desc_Value,
                          Char_Desc_Value_Length);

        def_p->val_p->val_len = Char_Desc_Value_Length;
        def_p->val_p->is_variable = Is_Variable;
        def_p->val_p->buffer_len = Char_Desc_Value_Max_Len;
        def_p->val_p->event_mask = GATT_Evt_Mask;
        descr_def_p->val_buffer_p = NULL;
    }
    /**
     * Copy descriptor's UUID value.
     */
    ACI_gatt_nwk_set_uuid(Char_Desc_Uuid_Type, (uint8_t const *)Char_Desc_Uuid,
                          &descr_def_p->uuid);

    /**
     * Set minimum encryption key size to access descriptor value.
     */
    descr_def_p->min_key_size = Enc_Key_Size;

    /**
     * Set descriptor's access properties.
     */
    descr_def_p->properties = Access_Permissions & (BLE_GATT_SRV_DESCR_PROP_READ |
                                                    BLE_GATT_SRV_DESCR_PROP_WRITE);

    /**
     * Set descriptor's security permissions.
     */
    descr_def_p->permissions = Security_Permissions;

    /**
     * Add descriptor to ATT DB.
     */
    ret = aci_gatt_srv_add_char_desc(descr_def_p, Char_Handle);
    if (ret == BLE_STATUS_SUCCESS)
    {
        def_p->attr_handle = aci_gatt_srv_get_descriptor_handle(descr_def_p);
        *Char_Desc_Handle = def_p->attr_handle;
        def_p->def_type = DEF_TYPE_DESCR;

        /**
         * Add new node to attribute definition list.
         */
        ACI_gatt_nwk_add_def_entry(def_p);
    }
    else
    {
        goto __error;
    }

    return ret;

__error:
    /**
     * An error arise. Release all allocated memory.
     */
    if (descr_def_p != NULL)
    {
        if (descr_def_p->val_buffer_p != NULL)
        {
            if (descr_def_p->val_buffer_p->buffer_p != NULL)
            {
                dm_free((uint32_t *)descr_def_p->val_buffer_p->buffer_p);
            }
            dm_free((uint32_t *)descr_def_p->val_buffer_p);
        }
        dm_free((uint32_t *)descr_def_p);
    }
    if (def_p != NULL)
    {
        if (def_p->val_p != NULL)
        {
            dm_free((uint32_t *)def_p->val_p);
        }
        dm_free((uint32_t *)def_p);
    }

    return ret;
}

tBleStatus aci_gatt_srv_rm_char_nwk(uint16_t Char_Handle)
{
    tBleStatus ret;
    ACI_gatt_nwk_def_entry_t *def_p;

    /**
     * Remove characteristic from Attribute DB.
     */
    ret = aci_gatt_srv_rm_char(Char_Handle);
    if (ret == BLE_STATUS_SUCCESS)
    {
        def_p = ACI_gatt_nwk_find_def_entry(Char_Handle + 1U);
        if (def_p != NULL)
        {
            /**
             * Characteristic attribute and all attributes of the group was removed.
             * Release attribute nodes and all the allocated resources. All nested
             * nodes (descriptors) will be released.
             */
            ACI_gatt_nwk_release_def(def_p, DEF_TYPE_CHAR);
        }
    }

    return ret;
}

tBleStatus aci_gatt_srv_rm_service_nwk(uint16_t Serv_Handle)
{
    ACI_gatt_nwk_def_entry_t *def_p;
    tBleStatus ret;

    /**
     * Remove service from Attribute DB.
     */
    ret = aci_gatt_srv_rm_service(Serv_Handle);
    if (ret == BLE_STATUS_SUCCESS)
    {
        def_p = ACI_gatt_nwk_find_def_entry(Serv_Handle);
        if (def_p != NULL)
        {
            /**
             * Service and all attributes of the group was removed. Release
             * attribute nodes and all the allocated resources. All nested nodes
             * (characteristics and descriptors) will be released.
             */
            ACI_gatt_nwk_release_def(def_p, DEF_TYPE_SERVICE);
        }
    }

    return ret;
}

tBleStatus aci_gatt_srv_rm_include_service_nwk(uint16_t Include_Handle)
{
    return aci_gatt_srv_rm_include_service(Include_Handle);
}

tBleStatus aci_gatt_srv_read_handle_value_nwk(uint16_t Attr_Handle,
                                              uint16_t Offset,
                                              uint16_t Value_Length_Requested,
                                              uint16_t *Length,
                                              uint16_t *Value_Length,
                                              uint8_t Value[])
{
    ACI_gatt_nwk_def_entry_t *def_p;
    tBleStatus ret;
    uint8_t *val;

    /**
     * If the attribute value is directly handled by the stack (eg. CCCD)its
     * value shall be returned by the stack itself.
     */
    ret = aci_gatt_srv_read_handle_value(Attr_Handle, Length, &val);
    if (ret == BLE_STATUS_SUCCESS)
    {
        /**
         * The value is returned by the stack.
         */
        *Value_Length = MIN((*Length - Offset), Value_Length_Requested);
        (void)Osal_MemCpy(Value, val, *Value_Length);
    }
    else
    {
        /**
         * The value is handled by this wrapper.
         * Search for attribute definition node.
         */
        def_p = ACI_gatt_nwk_find_def_entry(Attr_Handle);
        if (def_p == NULL)
        {
            /**
             * Invalid attribute handle.
             */
            ret = BLE_STATUS_INVALID_PARAMS;
        }
        else
        {
            /**
             * We should not send the complete data length of attribute in the
             * event but only the length we are sending in the event if Length
             * is of Value_Length_Requested bytes and the offset provided is
             * also Value_Length_Requested, then we end up not copying anything,
             * as _dataLen-Offset turns out to be 0 and in this case we will
             * never increase the pBuffer index of the event packet.
             */
            if (Offset >= def_p->val_p->val_len)
            {
                return BLE_STATUS_INVALID_PARAMS;
            }
            *Length = def_p->val_p->val_len - Offset;
            *Value_Length = MIN((def_p->val_p->val_len - Offset),
                                Value_Length_Requested);

            /**
             * Copy attribute value.
             */
            (void)Osal_MemCpy(Value, &def_p->val_p->buffer_va[Offset],
                              *Value_Length);

            ret = BLE_STATUS_SUCCESS;
        }
    }

    return ret;
}

tBleStatus aci_gatt_srv_write_handle_value_nwk(uint16_t Attr_Handle,
                                               uint16_t Val_Offset,
                                               uint16_t Char_Value_Length,
                                               uint8_t Char_Value[])
{
    tBleStatus ret;
    ACI_gatt_nwk_def_entry_t *def_p;

    /**
     * Check if the attribute value to change is a GAP Profile's attribute and
     * if true write it.
     */
    ret = Gap_profile_set_char_value(Attr_Handle, Val_Offset, Char_Value_Length,
                                     Char_Value);
    if (ret == BLE_STATUS_SUCCESS)
    {
        return ret;
    }

    /**
     * Find attribute definition node.
     */
    def_p = ACI_gatt_nwk_find_def_entry(Attr_Handle);
    if ((def_p == NULL) ||
        ((Val_Offset + Char_Value_Length) > def_p->val_p->buffer_len))
    {
        /**
         * Value length or offset is wrong.
         */
        return BLE_STATUS_INVALID_PARAMS;
    }

    if (def_p->def_type == DEF_TYPE_DESCR)
    {
        ble_gatt_descr_def_t *descr_def_p;

        descr_def_p = (ble_gatt_descr_def_t *)def_p->def_p;
        if ((descr_def_p->uuid.uuid_type == BLE_UUID_TYPE_16BITS) &&
            (descr_def_p->uuid.v_16.v == BLE_GATT_SRV_CLIENT_CHAR_CONF_DESCR_TYPE_UUID))
        {
            return BLE_STATUS_NOT_ALLOWED;
        }
    }

    if (def_p->val_p->is_variable == TRUE)
    {
        /**
         * It is a variable length attribute. Update the length parameter to the
         * new value.
         */
        def_p->val_p->val_len = Char_Value_Length;
    }

    /**
     * Write attribute value.
     */
    (void)Osal_MemCpy(&def_p->val_p->buffer_va[Val_Offset], Char_Value,
                      Char_Value_Length);

    return BLE_STATUS_SUCCESS;
}

tBleStatus aci_gatt_srv_set_security_permission_nwk(uint16_t Attr_Handle,
                                                    uint8_t Security_Permissions)
{
    tBleStatus ret;
    ACI_gatt_nwk_def_entry_t *def_p;
    ble_gatt_descr_def_t *descr_def_p;
    ble_gatt_chr_def_t *chr_def_p;

    if ((Security_Permissions & (~BLE_GATT_SRV_PERM_ALL)) != 0U)
    {
        return BLE_STATUS_INVALID_PARAMS;
    }

    ret = Gatt_profile_set_security_permission(Attr_Handle, Security_Permissions);
    if (ret != BLE_STATUS_FAILED)
    {
        return ret;
    }

    ret = Gap_profile_set_security_permission(Attr_Handle, Security_Permissions);
    if (ret != BLE_STATUS_FAILED)
    {
        return ret;
    }

    /**
     * Search for attribute definition node.
     */
    def_p = ACI_gatt_nwk_find_def_entry(Attr_Handle);
    if (def_p == NULL)
    {
        return BLE_STATUS_INVALID_PARAMS;
    }

    /**
     * Extract definition structure casting it on the basis of the type and
     * update its security permissions.
     */
    if (def_p->def_type == DEF_TYPE_CHAR)
    {
        chr_def_p = (ble_gatt_chr_def_t *)def_p->def_p;
        chr_def_p->permissions = Security_Permissions;
    }
    else if (def_p->def_type == DEF_TYPE_DESCR)
    {
        descr_def_p = (ble_gatt_descr_def_t *)def_p->def_p;
        if (descr_def_p->uuid.uuid_type == BLE_UUID_TYPE_16BITS)
        {
            if ((descr_def_p->uuid.v_16.v == BLE_GATT_SRV_CLIENT_CHAR_CONF_DESCR_TYPE_UUID) ||
                (descr_def_p->uuid.v_16.v == BLE_GATT_SRV_SERVER_CHAR_CONF_DESCR_TYPE_UUID))
            {
                if ((Security_Permissions & (BLE_GATT_SRV_PERM_ENCRY_READ |
                                             BLE_GATT_SRV_PERM_AUTHEN_READ)) != 0U)
                {
                    /**
                     * <<Readable with no authentication or authorization.
                     *   Writable with authentication and authorization defined by a
                     *   higher layer specification or is implementation specific.>>
                     *
                     * Table 3.10: Client Characteristic Configuration declaration
                     * BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part G page 1556
                     *
                     * Table 3.12: Server Characteristic Configuration declaration
                     * BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part G page 1557
                     */
                    return BLE_STATUS_NOT_ALLOWED;
                }
            }
            else if ((descr_def_p->uuid.v_16.v == BLE_GATT_SRV_CHAR_EXT_PROP_DESCR_TYPE_UUID) ||
                     (descr_def_p->uuid.v_16.v == BLE_GATT_SRV_CHAR_PRES_FORMAT_DESCR_TYPE_UUID) ||
                     (descr_def_p->uuid.v_16.v == BLE_GATT_SRV_CHAR_AGGR_FORMAT_DESCR_TYPE_UUID))
            {
                /**
                 * The security permission can't be changed for this descriptor.
                 */
                return BLE_STATUS_NOT_ALLOWED;
            }
        }
        descr_def_p->permissions = Security_Permissions;
    }
    else
    {
        return BLE_STATUS_INVALID_PARAMS;
    }

    return BLE_STATUS_SUCCESS;
}

/* The length of the Value buffer must be at least equal to 16 octets. */
tBleStatus aci_gatt_srv_read_multiple_instance_handle_value_nwk(uint16_t Connection_Handle,
                                                            uint16_t Attr_Handle,
                                                            uint16_t *Value_Length,
                                                            uint8_t Value[])
{
  uint8_t *value_p;
  tBleStatus ret;

  ret = aci_gatt_srv_read_multiple_instance_handle_value(Connection_Handle,
                                                          Attr_Handle,
                                                          Value_Length,
                                                          &value_p);

  if(ret == BLE_STATUS_SUCCESS)
  {
    if(*Value_Length > 16)
      return BLE_ERROR_MEMORY_CAPACITY_EXCEEDED;

    Osal_MemCpy(Value,value_p, *Value_Length);
  }

  return ret;

}

tBleStatus aci_gatt_srv_set_access_permission_nwk(uint16_t Attr_Handle,
                                                  uint8_t Access_Permissions)
{
    uint8_t *prop, perm;
    tBleStatus ret;
    ACI_gatt_nwk_def_entry_t *def_p;
    ble_gatt_descr_def_t *descr_def_p;
    ble_gatt_chr_def_t *chr_def_p;

    perm = 0U;
    if ((Access_Permissions & 0x01U) != 0U)
    {
        perm |= BLE_GATT_SRV_CHAR_PROP_READ;
    }
    if ((Access_Permissions & 0x02) != 0U)
    {
        perm |= BLE_GATT_SRV_CHAR_PROP_WRITE;
    }
    if ((Access_Permissions & 0x04) != 0U)
    {
        perm |= BLE_GATT_SRV_CHAR_PROP_WRITE_NO_RESP;
    }
    if ((Access_Permissions & 0x08) != 0U)
    {
        perm |= BLE_GATT_SRV_CHAR_PROP_AUTH_SIGN_WRITE;
    }

    ret = Gatt_profile_set_access_permission(Attr_Handle, perm);
    if (ret == BLE_STATUS_SUCCESS)
    {
        return ret;
    }

    ret = Gap_profile_set_access_permission(Attr_Handle, perm);
    if (ret == BLE_STATUS_SUCCESS)
    {
        return ret;
    }

    /**
     * Search for attribute definition node.
     */
    def_p = ACI_gatt_nwk_find_def_entry(Attr_Handle);
    if (def_p == NULL)
    {
        return BLE_STATUS_INVALID_PARAMS;
    }

    /**
     * Extract definition structure casting it on the basis of the type and
     * get pointer to the properties field.
     */
    if (def_p->def_type == DEF_TYPE_CHAR)
    {
        chr_def_p = (ble_gatt_chr_def_t *)def_p->def_p;
        prop = &chr_def_p->properties;
    }
    else if (def_p->def_type == DEF_TYPE_DESCR)
    {
        descr_def_p = (ble_gatt_descr_def_t *)def_p->def_p;
        if ((descr_def_p->uuid.uuid_type == BLE_UUID_TYPE_16BITS) &&
            ((descr_def_p->uuid.v_16.v == BLE_GATT_SRV_CHAR_PRES_FORMAT_DESCR_TYPE_UUID) ||
             (descr_def_p->uuid.v_16.v == BLE_GATT_SRV_CHAR_AGGR_FORMAT_DESCR_TYPE_UUID) ||
             (descr_def_p->uuid.v_16.v == BLE_GATT_SRV_CHAR_EXT_PROP_DESCR_TYPE_UUID)))
        {
            /**
             * The attribute permission of the following descriptors are standard
             * defined and can't be altered:
             * - 3.3.3.1 Characteristic Extended Properties
             * - 3.3.3.5 Characteristic Presentation Format
             * - 3.3.3.6 Characteristic Aggregate Format
             */
            return BLE_STATUS_NOT_ALLOWED;
        }
        prop = &descr_def_p->properties;
    }
    else
    {
        return BLE_STATUS_INVALID_PARAMS;
    }

    /**
     * Update properties.
     */
    *prop &= ~BLE_GATT_SRV_CHAR_PROP_ACCESS_PERM_MASK;
    *prop |= perm;

    return BLE_STATUS_SUCCESS;
}

tBleStatus aci_gatt_srv_authorize_resp_nwk(uint16_t Conn_Handle,
                                           uint16_t CID,
                                           uint16_t Attr_Handle,
                                           uint8_t Operation_Type,
                                           uint8_t Error_Code,
                                           uint16_t Data_Offset,
                                           uint16_t Data_Length,
                                           uint8_t Data[])
{
    tBleStatus ret;
    uint8_t att_err, *data_p;
    uint16_t data_len;
    ACI_gatt_nwk_def_entry_t *def_p;

    if ((Error_Code != BLE_ATT_ERR_NONE) &&
        (Error_Code != BLE_ATT_ERR_INSUFF_AUTHORIZATION) &&
        !((Error_Code >= BLE_ATT_ERR_APPL_MIN) &&
          (Error_Code <= BLE_ATT_ERR_APPL_MAX)))
    {
        /**
         * Invalid error code.
         */
        return BLE_STATUS_INVALID_PARAMS;
    }

    data_len = 0;
    data_p = NULL;
    if (Error_Code == BLE_ATT_ERR_NONE)
    {
        att_err = BLE_ATT_ERR_NONE;
        if (Operation_Type == GATT_AUTHOR_OP_TYPE_READ)
        {
            def_p = ACI_gatt_nwk_find_def_entry(Attr_Handle);
            if (def_p == NULL)
            {
                /**
                 * Invalid attribute handle.
                 */
                return BLE_STATUS_INVALID_PARAMS;
            }
            /**
             * Check read offset parameter.
             */
            if (Data_Offset > def_p->val_p->val_len)
            {
                /**
                 * Invalid offset.
                 */
                att_err = BLE_ATT_ERR_INVALID_OFFSET;
            }
            else
            {
                /**
                 * Populate variables to return to the stack.
                 */
                data_len = def_p->val_p->val_len;
                data_p = &def_p->val_p->buffer_va[Data_Offset];
            }
        }
        else if (Operation_Type == GATT_AUTHOR_OP_TYPE_PREP_WRITE)
        {
            /**
             * Push the prepare write in the queue.
             */
            ret = EATT_pwrq_push(Conn_Handle, CID, Attr_Handle,
                                 Data_Offset, Data_Length, Data);
            if (ret != BLE_STATUS_SUCCESS)
            {
                att_err = BLE_ATT_ERR_PREP_QUEUE_FULL;
            }
            data_len = Data_Length;
            data_p = Data;
        }
        else if ((Operation_Type == GATT_AUTHOR_OP_TYPE_WRITE) ||
                 (Operation_Type == GATT_AUTHOR_OP_TYPE_WRITE_CMD))
        {
            def_p = ACI_gatt_nwk_find_def_entry(Attr_Handle);
            if (Data_Length > def_p->val_p->buffer_len)
            {
                att_err = BLE_ATT_ERR_INVAL_ATTR_VALUE_LEN;
            }
            else
            {
                /**
                 * Write received data into attribute value buffer.
                 */
                Osal_MemCpy(def_p->val_p->buffer_va, Data, Data_Length);
                att_err = BLE_ATT_ERR_NONE;
            }
            if (def_p->val_p->is_variable == TRUE)
            {
                /**
                 * Update value length.
                 */
                def_p->val_p->val_len = Data_Length;
            }
            if ((def_p->val_p->event_mask & GATT_SERVER_ATTR_WRITE) != 0x00U)
            {
              /**
              * The application expects to receive the attribute modified event.
              */
              aci_gatt_srv_attribute_modified_event(Conn_Handle,
                                                    CID,
                                                    Attr_Handle,
                                                    Data_Length,
                                                    def_p->val_p->buffer_va);

            }
        }
    }
    else
    {
        att_err = Error_Code;
    }

    if (Operation_Type != GATT_AUTHOR_OP_TYPE_WRITE_CMD)
    {
      aci_gatt_srv_resp(Conn_Handle, CID, Attr_Handle, att_err, data_len, data_p);
    }

    return BLE_STATUS_SUCCESS;
}

tBleStatus aci_gatt_srv_exec_write_resp_nwk(uint16_t Conn_Handle,
                                            uint16_t CID,
                                            uint8_t Exec)
{
    uint8_t att_error;

    att_error = BLE_ATT_ERR_NONE;
    if (Exec == 1U)
    {
        att_error = ACI_gatt_nwk_write_queue(Conn_Handle);
    }

    /**
     * Flush the queue from all prepared write received by this connection handle.
     */
    EATT_pwrq_flush(Conn_Handle, EATT_PWRQ_CID_ALL);

    /**
     * Return to the stack to send the Execute Write Response or in case the
     * error response if the att_error is not zero.
     */
    aci_gatt_srv_resp(Conn_Handle, CID, 0U, att_error, 0U, NULL);

    return BLE_STATUS_SUCCESS;
}

tBleStatus aci_gatt_srv_read_prepare_queue_nwk(uint16_t Conn_Handle,
                                               uint8_t Item_Index,
                                               uint16_t *Attr_Handle,
                                               uint16_t *Value_Offset,
                                               uint16_t *Value_Length,
                                               uint8_t Value[])
{
    tBleStatus ret;
    ble_gatt_clt_write_ops_t wr_ops;

    /**
     * Read the queued write at the given queue index.
     */
    ret = EATT_pwrq_read(Conn_Handle, EATT_PWRQ_CID_ALL, Item_Index, &wr_ops);
    if (ret == BLE_STATUS_SUCCESS)
    {
        *Attr_Handle = wr_ops.attr_h;
        *Value_Offset = wr_ops.attr_offset;
        *Value_Length = wr_ops.data_len;
        (void)Osal_MemCpy(Value, wr_ops.data_p, wr_ops.data_len);
    }

    return ret;
}

tBleStatus aci_gatt_clt_write_long_nwk(uint16_t Connection_Handle,
                                       uint16_t CID,
                                       uint16_t Attr_Handle,
                                       uint16_t Val_Offset,
                                       uint16_t Attribute_Val_Length,
                                       uint8_t Attribute_Val[])
{
    ACI_gatt_nwk_write_ops_t *ops_p;
    tBleStatus ret;

    ret = BLE_STATUS_FAILED;
    ops_p = ACI_gatt_nwk_add_write_ops(Connection_Handle, CID, 1U, Attribute_Val_Length);
    if (ops_p != NULL)
    {
        ops_p->write_ops_p->attr_h = Attr_Handle;
        ops_p->write_ops_p->attr_offset = Val_Offset;
        ops_p->write_ops_p->data_len = Attribute_Val_Length;
        ops_p->write_ops_p->data_p = ops_p->buffer;
        (void)Osal_MemCpy(ops_p->buffer, Attribute_Val, Attribute_Val_Length);

        ret = aci_gatt_clt_write_long(Connection_Handle, CID, ops_p->write_ops_p);
        if (ret != BLE_STATUS_SUCCESS)
        {
            ACI_gatt_nwk_rm_write_ops(Connection_Handle, CID);
        }
    }

    return ret;
}

tBleStatus aci_gatt_clt_write_char_reliable_nwk(uint16_t Connection_Handle,
                                                uint16_t CID,
                                                uint16_t Attr_Handle,
                                                uint16_t Val_Offset,
                                                uint16_t Attribute_Val_Length,
                                                uint8_t Attribute_Val[])
{
    ACI_gatt_nwk_write_ops_t *ops_p;
    tBleStatus ret;

    ret = BLE_STATUS_FAILED;
    ops_p = ACI_gatt_nwk_add_write_ops(Connection_Handle, CID, 1U, Attribute_Val_Length);
    if (ops_p != NULL)
    {
        ops_p->write_ops_p[0].attr_h = Attr_Handle;
        ops_p->write_ops_p[0].attr_offset = Val_Offset;
        ops_p->write_ops_p[0].data_len = Attribute_Val_Length;
        ops_p->write_ops_p[0].data_p = &ops_p->buffer[0];
        (void)Osal_MemCpy(ops_p->write_ops_p[0].data_p, Attribute_Val,
                          Attribute_Val_Length);

         ret = aci_gatt_clt_write_char_reliable(Connection_Handle,
                                                CID,
                                                1U,
                                                ops_p->write_ops_p);
        if (ret != BLE_STATUS_SUCCESS)
        {
            ACI_gatt_nwk_rm_write_ops(Connection_Handle, CID);
        }
    }

    return ret;
}

tBleStatus aci_gatt_clt_write_nwk(uint16_t Connection_Handle,
                                  uint16_t CID,
                                  uint16_t Attr_Handle,
                                  uint16_t Attribute_Val_Length,
                                  uint8_t Attribute_Val[])
{
    ACI_gatt_nwk_write_ops_t *ops_p;
    tBleStatus ret;

    ret = BLE_STATUS_FAILED;
    ops_p = ACI_gatt_nwk_add_write_ops(Connection_Handle, CID, 1U, Attribute_Val_Length);
    if (ops_p != NULL)
    {
        (void)Osal_MemCpy(ops_p->buffer, Attribute_Val, Attribute_Val_Length);

        ret = aci_gatt_clt_write(Connection_Handle, CID, Attr_Handle,
                                      Attribute_Val_Length, ops_p->buffer);
        if (ret != BLE_STATUS_SUCCESS)
        {
            ACI_gatt_nwk_rm_write_ops(Connection_Handle, CID);
        }
    }

    return ret;
}

/******************************************************************************
 * EVENT HANDLERS
 *****************************************************************************/
int aci_gatt_srv_write_event_preprocess(uint16_t Connection_Handle,
                                        uint16_t CID,
                                        uint8_t Resp_Needed,
                                        uint16_t Attribute_Handle,
                                        uint16_t Data_Length,
                                        uint8_t Data[])
{
    uint8_t att_err;
    ACI_gatt_nwk_def_entry_t *def_p;

    /**
     * Search for attribute definition node.
     */
    def_p = ACI_gatt_nwk_find_def_entry(Attribute_Handle);
    if (def_p != NULL)
    {
        if ((def_p->val_p->event_mask & GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP) != 0U)
        {
            /**
             * The user application has to authorize this write operation.
             */
            uint8_t op_type;

            if (Resp_Needed)
            {
                op_type = GATT_AUTHOR_OP_TYPE_WRITE;
            }
            else
            {
                op_type = GATT_AUTHOR_OP_TYPE_WRITE_CMD;
            }
            aci_gatt_srv_authorize_nwk_event(Connection_Handle,
                                             CID,
                                             Attribute_Handle,
                                             op_type,
                                             0x0000U,
                                             Data_Length, Data);

            return 1;
        }
        else
        {
            if (Data_Length > def_p->val_p->buffer_len)
            {
                att_err = BLE_ATT_ERR_INVAL_ATTR_VALUE_LEN;
            }
            else
            {
                /**
                 * Write received data into attribute value buffer.
                 */
                Osal_MemCpy(def_p->val_p->buffer_va, Data, Data_Length);
                att_err = BLE_ATT_ERR_NONE;
            }
            if (def_p->val_p->is_variable == TRUE)
            {
                /**
                 * Update value length.
                 */
                def_p->val_p->val_len = Data_Length;
            }
        }
        if (Resp_Needed == 1U)
        {
          /**
          * It is a write request then call response function to generate
          * write response message.
          */
          aci_gatt_srv_resp(Connection_Handle,
                                 CID,
                                 Attribute_Handle,
                                 att_err,
                                 0,
                                 NULL);
        }
        if ((att_err == BLE_ATT_ERR_NONE) &&
            ((def_p->val_p->event_mask & GATT_SERVER_ATTR_WRITE) != 0x00U))
        {
            /**
             * The application expect to receive the attribute modified event.
             */
            uint16_t event_data_len;

            if (def_p->val_p->is_variable == TRUE)
            {
                event_data_len = def_p->val_p->val_len;
            }
            else
            {
                event_data_len = def_p->val_p->buffer_len;
            }
            aci_gatt_srv_attribute_modified_event(Connection_Handle,
                                                  CID,
                                                  Attribute_Handle,
                                                  event_data_len,
                                                  def_p->val_p->buffer_va);
        }
    }

    return 1;
}

int aci_gatt_srv_read_event_preprocess(uint16_t Connection_Handle,
                                       uint16_t CID,
                                       uint16_t Attribute_Handle,
                                       uint16_t Data_Offset)
{
    uint8_t att_err, *data_p;
    uint16_t data_len;
    ACI_gatt_nwk_def_entry_t *def_p;

    data_len = 0U;
    data_p = NULL;
    /**
     * Search for attribute definition node.
     */
    def_p = ACI_gatt_nwk_find_def_entry(Attribute_Handle);
    if (def_p == NULL)
    {
        /**
         * Invalid attribute handle.
         */
        att_err = BLE_ATT_ERR_INVALID_HANDLE;
    }
    else
    {
        if (def_p->val_p == NULL)
        {
            att_err = BLE_ATT_ERR_UNLIKELY;
        }
        else if ((def_p->val_p->event_mask & GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP) != 0x00U)
        {
          /**
          * The application has to authorize read operation for the requested
          * attribute value.
          */
          aci_gatt_srv_authorize_nwk_event(Connection_Handle,
                                           CID,
                                           Attribute_Handle,
                                           GATT_AUTHOR_OP_TYPE_READ,
                                           Data_Offset,
                                           0U, NULL);
          return 1;
        }
        else
        {
            /**
             * Check read offset parameter.
             */
            if (Data_Offset > def_p->val_p->val_len)
            {
                /**
                 * Invalid offset.
                 */
                att_err = BLE_ATT_ERR_INVALID_OFFSET;
            }
            else
            {
                /**
                 * Populate variables to return to the stack.
                 */
                data_len = def_p->val_p->val_len;
                data_p = &def_p->val_p->buffer_va[Data_Offset];
                att_err = BLE_ATT_ERR_NONE;
            }
        }
    }

    /**
     * Return to the stack the value to read information and in case the error
     * code.
     */
    aci_gatt_srv_resp(Connection_Handle, CID, Attribute_Handle, att_err,
                      data_len, data_p);

    return 1; /* Discard event */
}

int aci_att_srv_prepare_write_req_event_preprocess(uint16_t Connection_Handle,
                                                   uint16_t CID,
                                                   uint16_t Attribute_Handle,
                                                   uint16_t Data_Offset,
                                                   uint16_t Data_Length,
                                                   uint8_t Data[])
{
    ACI_gatt_nwk_def_entry_t *def_p;
    uint8_t att_err;
    tBleStatus ret;

    def_p = ACI_gatt_nwk_find_def_entry(Attribute_Handle);
    if (def_p != NULL)
    {
        if ((def_p->val_p->event_mask & GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP) != 0U)
        {
            /**
             * Generate authorization event.
             */
          aci_gatt_srv_authorize_nwk_event(Connection_Handle,
                                           CID,
                                           Attribute_Handle,
                                           GATT_AUTHOR_OP_TYPE_PREP_WRITE,
                                           Data_Offset,
                                           Data_Length,
                                           Data);

            /**
             * No response has to be sent before application response.
             */
            return 1;
        }
        else
        {
            /**
             * This attribute has not be set for authorization. Push the received
             * prepare write in the queue.
             */
            ret = EATT_pwrq_push(Connection_Handle, CID, Attribute_Handle,
                                 Data_Offset, Data_Length, Data);
            if (ret != BLE_STATUS_SUCCESS)
            {
                att_err = BLE_ATT_ERR_PREP_QUEUE_FULL;
            }
            else
            {
                att_err = BLE_ATT_ERR_NONE;
            }
        }
    }
    else
    {
        att_err = BLE_ATT_ERR_INVALID_HANDLE;
    }

    /**
     * Send response.
     */
    aci_gatt_srv_resp(Connection_Handle, CID, Attribute_Handle, att_err,
                      Data_Length, Data);
    return 1;
}

/******************************************************************************
 * PRIVATE FUNCTIONS
 *****************************************************************************/
static void ACI_gatt_nwk_add_def_entry(ACI_gatt_nwk_def_entry_t *def_p)
{
    ACI_gatt_nwk_def_entry_t *p;

    if (aci_gatt_nwk_ctx_s.head == NULL)
    {
        /**
         * Definition list is empty.
         */
        aci_gatt_nwk_ctx_s.head = def_p;
        def_p->next_p = NULL;
    }
    else
    {
        p = aci_gatt_nwk_ctx_s.head;
        if (p->attr_handle > def_p->attr_handle)
        {
            def_p->next_p = p;
            aci_gatt_nwk_ctx_s.head = def_p;
        }
        else
        {
            while (p->next_p != NULL)
            {
                /**
                 * Search for the node with an attribute handle greater than the
                 * new one.
                 */
                if (p->next_p->attr_handle > def_p->attr_handle)
                {
                    break;
                }
                p = p->next_p;
            }
            /**
             * Insert new node.
             */
            def_p->next_p = p->next_p;
            p->next_p = def_p;
        }
    }
}

static void ACI_gatt_nwk_rm_def_entry(ACI_gatt_nwk_def_entry_t *def_p)
{
    ACI_gatt_nwk_def_entry_t *p;

    if (aci_gatt_nwk_ctx_s.head != NULL)
    {
        p = aci_gatt_nwk_ctx_s.head;
        if (p->attr_handle == def_p->attr_handle)
        {
            /**
             * It is the head of the list.
             */
            aci_gatt_nwk_ctx_s.head = p->next_p;
        }
        else
        {
            while (p->next_p != NULL)
            {
                if (p->next_p->attr_handle == def_p->attr_handle)
                {
                    /**
                     * Next node has the required attribute handle. Un-link it.
                     */
                    p->next_p = p->next_p->next_p;

                    break;
                }
                p = p->next_p;
            }
        }
    }
}

static void ACI_gatt_nwk_free_def_entry(ACI_gatt_nwk_def_entry_t *def_p)
{
    ble_gatt_val_buffer_def_t *val_buffer_p;

    switch (def_p->def_type)
    {
        case DEF_TYPE_DESCR:
        {
            ble_gatt_descr_def_t *descr_p = (ble_gatt_descr_def_t *)def_p->def_p;
            val_buffer_p = descr_p->val_buffer_p;
        }
        break;

        case DEF_TYPE_CHAR:
        {
            ble_gatt_chr_def_t *chr_p = (ble_gatt_chr_def_t *)def_p->def_p;
            val_buffer_p = chr_p->val_buffer_p;
        }

        break;

        default:
            val_buffer_p = NULL;
            break;
    }

    if (val_buffer_p != NULL)
    {
        /**
         * Release value buffer memory.
         */
        if (val_buffer_p->buffer_p != NULL)
        {
            dm_free((uint32_t *)val_buffer_p->buffer_p);
        }
        dm_free((uint32_t *)val_buffer_p);
    }

    if (def_p->val_p != NULL)
    {
        /**
         * Release value buffer definition memory.
         */
        dm_free((uint32_t *)def_p->val_p);
    }

    /**
     * Release Attribute definition memory.
     */
    dm_free((uint32_t *)def_p->def_p);

    /**
     * Release node memory.
     */
    dm_free((uint32_t *)def_p);
}

static void ACI_gatt_nwk_release_def(ACI_gatt_nwk_def_entry_t *def_p, def_type_et type)
{
    ACI_gatt_nwk_def_entry_t *next_def_p;

    while (def_p != NULL)
    {
        next_def_p = def_p->next_p;

        /**
         * Unlink node.
         */
        ACI_gatt_nwk_rm_def_entry(def_p);

        /**
         * Release node memory.
         */
        ACI_gatt_nwk_free_def_entry(def_p);

        if (next_def_p->def_type == type)
        {
            /**
             * Next node has the same group type of the removing entry. Stop!
             */
            break;
        }
        def_p = next_def_p;
    }
}

static ACI_gatt_nwk_def_entry_t *ACI_gatt_nwk_find_def_entry(uint16_t attr_handle)
{
    ACI_gatt_nwk_def_entry_t *p;

    p = aci_gatt_nwk_ctx_s.head;
    while (p != NULL)
    {
        if (p->attr_handle == attr_handle)
        {
            return p;
        }
        p = p->next_p;
    }

    return NULL;
}

static tBleStatus ACI_gatt_nwk_set_uuid(const uint8_t src_uuid_type,
                                        const uint8_t *src_uuid_p,
                                        ble_uuid_t *uuid_p)
{
    if (src_uuid_type == 0x01)
    {
        /**
         * Copy 16 bits UUID.
         */
        (void)Osal_MemCpy((uint8_t *)&uuid_p->v_16.v, src_uuid_p, BLE_UUID_16_LENGTH);
        uuid_p->uuid_type = BLE_UUID_TYPE_16BITS;
    }
    else if (src_uuid_type == 0x02)
    {
        /**
         * Copy 128 bits UUID.
         */

        (void)Osal_MemCpy(uuid_p->v_128.v, src_uuid_p, BLE_UUID_128_LENGTH);
        uuid_p->uuid_type = BLE_UUID_TYPE_128BITS;
    }
    else
    {
        return BLE_STATUS_INVALID_PARAMS;
    }

    return BLE_STATUS_SUCCESS;
}

static ACI_gatt_nwk_write_ops_t *ACI_gatt_nwk_add_write_ops(uint16_t conn_handle,
                                                            uint16_t cid,
                                                            uint8_t num_write_ops,
                                                            uint16_t buffer_size)
{
    ACI_gatt_nwk_write_ops_t *ops_p, *prev_p;

    ops_p = (ACI_gatt_nwk_write_ops_t *)dm_alloc(sizeof(ACI_gatt_nwk_write_ops_t) + buffer_size);
    if (ops_p != NULL)
    {
        ops_p->write_ops_p = (ble_gatt_clt_write_ops_t *)
                             dm_alloc(sizeof(ble_gatt_clt_write_ops_t) * num_write_ops);
        if (ops_p->write_ops_p == NULL)
        {
            dm_free((uint32_t *)ops_p);
            ops_p = NULL;
        }
        else
        {
            ops_p->next_p = NULL;
            ops_p->conn_handle = conn_handle;
            ops_p->cid = cid;
            if (aci_gatt_nwk_ctx_s.write_ops_head_p == NULL)
            {
                aci_gatt_nwk_ctx_s.write_ops_head_p = ops_p;
            }
            else
            {
                prev_p = aci_gatt_nwk_ctx_s.write_ops_head_p;
                while (prev_p->next_p != NULL)
                {
                    prev_p = prev_p->next_p;
                }
                prev_p->next_p = ops_p;
            }
        }
    }

    return ops_p;
}

static void ACI_gatt_nwk_rm_write_ops(uint16_t conn_handle, uint16_t cid)
{
  ACI_gatt_nwk_write_ops_t *ops_p = NULL, *prev_p = NULL;

  ops_p = aci_gatt_nwk_ctx_s.write_ops_head_p;

  while (ops_p != NULL)
  {
    if ((ops_p->conn_handle == conn_handle) && (ops_p->cid == cid))
    {
      if(ops_p == aci_gatt_nwk_ctx_s.write_ops_head_p)
      {
        /* First element in the list */
        aci_gatt_nwk_ctx_s.write_ops_head_p = ops_p->next_p;
      }
      else
      {
        prev_p->next_p = ops_p->next_p;
      }
      break;
    }
    prev_p = ops_p;
    ops_p = ops_p->next_p;
  }

  if (ops_p != NULL)
  {
    dm_free((uint32_t *)ops_p->write_ops_p);
    dm_free((uint32_t *)ops_p);
  }
}

static uint8_t ACI_gatt_nwk_write_queue(uint16_t conn_handle)
{
    tBleStatus ret;
    uint16_t attr_h, data_len;
    ble_gatt_clt_write_ops_t wr_ops;
    ACI_gatt_nwk_def_entry_t *def_p;

    /**
     * Set attribute handle to 0x0000 to extract the first found entry.
     */
    attr_h = EATT_PWRQ_ATTR_HANDLE_INVALID;
    def_p = NULL;
    while (TRUE)
    {
        /**
         * Extract queued write.
         */
        ret = EATT_pwrq_pop(conn_handle, EATT_PWRQ_CID_ALL, attr_h, &wr_ops);
        if (ret == BLE_STATUS_SUCCESS)
        {
            if (attr_h == EATT_PWRQ_ATTR_HANDLE_INVALID)
            {
                /**
                 * Select the first extracted attribute handle for the next
                 * search.
                 */
                attr_h = wr_ops.attr_h;

                /**
                 * Search for attribute definition node.
                 */
                def_p = ACI_gatt_nwk_find_def_entry(wr_ops.attr_h);
                if (def_p == NULL)
                {
                    /**
                     * Invalid attribute handle.
                     */
                    return BLE_ATT_ERR_UNLIKELY;
                }
            }

            if (def_p == NULL)
            {
                return BLE_ATT_ERR_ATTR_NOT_FOUND;
            }

            /**
             * Check write offset.
             */
            if (wr_ops.attr_offset > def_p->val_p->buffer_len)
            {
                return BLE_ATT_ERR_INVALID_OFFSET;
            }

            /**
             * Check write length.
             */
            if ((wr_ops.attr_offset + wr_ops.data_len) > def_p->val_p->buffer_len)
            {
                return BLE_ATT_ERR_INVAL_ATTR_VALUE_LEN;
            }

            /**
             * Write dato into attribute value buffer.
             */
            (void)Osal_MemCpy(&def_p->val_p->buffer_va[wr_ops.attr_offset],
                              wr_ops.data_p,
                              wr_ops.data_len);

            if (def_p->val_p->is_variable == TRUE)
            {
                /**
                 * Update attribute value length.
                 */
                def_p->val_p->val_len = wr_ops.attr_offset + wr_ops.data_len;
            }
        }
        else
        {
            if (attr_h != 0x0000U)
            {
                /**
                 * No more entries are present for the selected attribute handle.
                 */
                if (def_p != NULL)
                {
                    if ((def_p->val_p->event_mask & GATT_SERVER_ATTR_WRITE) != 0x00U)
                    {
                        if (def_p->val_p->is_variable == TRUE)
                        {
                            data_len = def_p->val_p->val_len;
                        }
                        else
                        {
                            data_len = def_p->val_p->buffer_len;
                        }

                        /**
                         * The application expect to receive the attribute modified event.
                         */
                        aci_gatt_srv_attribute_modified_event(conn_handle,
                                                              EATT_PWRQ_CID_ALL,
                                                              attr_h,
                                                              data_len,
                                                              def_p->val_p->buffer_va);
                    }
                }

                /**
                 * Reset attribute handle to extract the next first found entry.
                 */
                attr_h = 0x0000U;
            }
            else
            {
                /**
                 * No more entries are present for the selected connection handle.
                 */
                break;
            }
        }
    }

    return BLE_ATT_ERR_NONE;
}

/* Hooks for DTM commands */

int hci_disconnection_complete_event_preprocess(uint8_t Status,
                                                uint16_t Connection_Handle,
                                                uint8_t Reason)
{
  /* This is needed to remove all write ops for unenhanced ATT and fush prepare
     write queue. */
  ACI_gatt_nwk_disconnection(Connection_Handle, L2C_CID_ATTRIBUTE_PROTOCOL);

  return 0;
}

int aci_gatt_clt_proc_complete_event_preprocess(uint16_t Connection_Handle,
                                                uint16_t CID,
                                                uint8_t Error_Code)
{
  ACI_gatt_nwk_proc_complete(Connection_Handle, CID, Error_Code);

  return 0;
}

#else /* (CFG_BLE_CONNECTION_ENABLED == 1) && (BLESTACK_CONTROLLER_ONLY == 0) */

void ACI_gatt_nwk_init(uint16_t buffer_size)
{
}

void ACI_gatt_nwk_reset(void)
{
}

void ACI_gatt_nwk_proc_complete(uint16_t Connection_Handle, uint16_t CID, uint8_t Error_Code)
{
}

void ACI_gatt_nwk_disconnection(uint16_t Connection_Handle, uint16_t CID)
{
}

int hci_disconnection_complete_event_preprocess(uint8_t Status,
                                                uint16_t Connection_Handle,
                                                uint8_t Reason)
{
  return 0;
}

int aci_gatt_clt_proc_complete_event_preprocess(uint16_t Connection_Handle,
                                                uint16_t CID,
                                                uint8_t Error_Code)
{
  return 0;
}

int aci_gatt_srv_write_event_preprocess(uint16_t Connection_Handle,
                                        uint16_t CID,
                                        uint8_t Resp_Needed,
                                        uint16_t Attribute_Handle,
                                        uint16_t Data_Length,
                                        uint8_t Data[])
{
  return 0;
}

int aci_gatt_srv_read_event_preprocess(uint16_t Connection_Handle,
                                       uint16_t CID,
                                       uint16_t Attribute_Handle,
                                       uint16_t Data_Offset)
{
  return 0;
}

int aci_att_srv_prepare_write_req_event_preprocess(uint16_t Connection_Handle,
                                                   uint16_t CID,
                                                   uint16_t Attribute_Handle,
                                                   uint16_t Data_Offset,
                                                   uint16_t Data_Length,
                                                   uint8_t Data[])
{
  return 0;
}

#endif /* (CFG_BLE_CONNECTION_ENABLED == 1) && (BLESTACK_CONTROLLER_ONLY == 0) */

