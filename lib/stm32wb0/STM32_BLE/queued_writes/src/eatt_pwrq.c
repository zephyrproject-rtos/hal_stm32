/**
  ******************************************************************************
  * @file    att_pwrq.c
  * @author  GPM WBL Application Team
  * @brief   EATT Prepare Write Queue implementation
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

/******************************************************************************
 * INCLUDE HEADER FILES
 *****************************************************************************/
#include "ble_api.h"
#include "eatt_pwrq.h"
#include "osal.h"
#include <string.h>
/******************************************************************************
 * LOCAL TYPES
 *****************************************************************************/
/**
 * @brief Prepare Write Context.
 */
static struct EATT_pwrq_ctx_s {
    uint16_t wr_buffer_size; /**< Written buffer size. */
    uint16_t buffer_length; /**< Total buffer length. */
    uint8_t *buffer_p; /**< Buffer pointer. */
} EATT_pwrq_ctx = { 0 };

/**
 * Header of each stored prepared write entry.
 */
struct EATT_pwrq_entry_s {
    uint16_t conn_handle; /**< Connection handle from which the prepare write was received. */
    uint16_t cid; /**< Channel ID from which the prepare write was received. */
    uint16_t att_handle; /**< Attribute handle to write. */
    uint16_t pwr_offset; /**< Attribute value offset from where start to write the data. */
    uint16_t pwr_size; /**< Data size. */
};

/******************************************************************************
 * LOCAL MACROS
 *****************************************************************************/
#define SIZE_32BITS_ALIGNED(VAL)        ((VAL)&(~(sizeof(uint32_t) - 1U)))
#define ALIGN_UPTO_32BITS(VAL)            (((((unsigned int)(VAL)) - 1U) | \
                                            (sizeof(uint32_t) - 1U)) + 1U)
#define ADDRESS_32BITS_ALIGNED(ADDR)    ALIGN_UPTO_32BITS(ADDR)
#define PWRQ_GET_AVAILABLE_SPACE()      (EATT_pwrq_ctx.buffer_length - EATT_pwrq_ctx.wr_buffer_size)
#define INVALID_CONN_HANDLE_BIT         (0x8000U)
#define CONN_HANDLE_ALL_MASK            (INVALID_CONN_HANDLE_BIT - 1U)
#define CONN_HANDLE_VALID_MASK          (0xFFFFU)
/*******************************************************************************
 * PRIVATE PROTOTYPES
 ******************************************************************************/

/**
 * @brief Optimized function to move up fifo data.
 *
 * @param dest_p[in] Destination pointer.
 * @param src_p[in] Source pointer.
 * @param length[in] Data length.
 *
 * @return void
 *
 */
static void EATT_pwrq_cp32align_blk_left_move(uint32_t *dest_p,
                                              uint32_t *src_p,
                                              uint16_t length);

/**
 * @brief Find a prepared write entry in the queue.
 *
 * @param conn_handle[in] The connection handle of the prepare write to find.
 * @param conn_handle_mask[in] The mask to apply to connection handle value for
 *                             matching.
 * @param cid[in] The channel ID of the prepare write. If set to 0 means the
 *                channel id is not checket.
 * @param idx[in] The prepare write index in the queue.
 * @param entry_pp[out] The entry pointer.
 *
 * @return
 * - BLE_STATUS_SUCCESS: a prepare write was found.
 * - BLE_STATUS_ERROR: no prepare write was found.
 *
 */
static tBleStatus EATT_pwrq_get_entry(uint16_t conn_handle,
                                      uint16_t conn_handle_mask,
                                      uint16_t cid,
                                      uint16_t idx,
                                      struct EATT_pwrq_entry_s **entry_pp);

/**
 * @brief Remove a prepared write entry from the queue.
 *
 * @param entry_pp[in] The entry to remove.
 *
 * @return void.
 *
 */
static void EATT_pwrq_rm_entry(struct EATT_pwrq_entry_s *entry_p);

void EATT_pwrq_reset()
{
    EATT_pwrq_ctx.wr_buffer_size = 0U;
}

tBleStatus EATT_pwrq_init(uint16_t queue_length,
                          uint8_t *queue_buffer_p)
{
    /**
     * Align buffer to 32 bits.
     */
    EATT_pwrq_ctx.buffer_length = (uint16_t)SIZE_32BITS_ALIGNED(queue_length);
    EATT_pwrq_ctx.buffer_p = (uint8_t *)ADDRESS_32BITS_ALIGNED((uintptr_t)queue_buffer_p);

    EATT_pwrq_reset();

    return BLE_STATUS_SUCCESS;
}

void EATT_pwrq_flush(uint16_t conn_handle,
                     uint16_t cid)
{
    tBleStatus ret;
    struct EATT_pwrq_entry_s *entry_p;

    while (1U)
    {
        ret = EATT_pwrq_get_entry(conn_handle, CONN_HANDLE_ALL_MASK, cid, 0U, &entry_p);
        if (ret == BLE_STATUS_SUCCESS)
        {
            EATT_pwrq_rm_entry(entry_p);
        }
        else
        {
            break;
        }
    }
}

tBleStatus EATT_pwrq_read(uint16_t conn_handle,
                          uint16_t cid,
                          uint16_t idx,
                          ble_gatt_clt_write_ops_t *wr_ops_p)
{
    tBleStatus ret;
    struct EATT_pwrq_entry_s *entry_p;

    ret = EATT_pwrq_get_entry(conn_handle, CONN_HANDLE_VALID_MASK, cid, idx, &entry_p);
    if (ret == BLE_STATUS_SUCCESS)
    {
        wr_ops_p->attr_h = entry_p->att_handle;
        wr_ops_p->attr_offset = entry_p->pwr_offset;
        wr_ops_p->data_len = entry_p->pwr_size;
        wr_ops_p->data_p = (uint8_t *)(((uint8_t *)entry_p) + sizeof(struct EATT_pwrq_entry_s));
    }

    return ret;
}

tBleStatus EATT_pwrq_pop(uint16_t conn_handle,
                         uint16_t cid,
                         uint16_t attr_handle,
                         ble_gatt_clt_write_ops_t *wr_ops_p)
{
    tBleStatus ret;
    uint16_t idx;
    struct EATT_pwrq_entry_s *entry_p;

    idx = 0U;
    while (1U)
    {
        ret = EATT_pwrq_get_entry(conn_handle, CONN_HANDLE_VALID_MASK, cid, idx, &entry_p);
        if (ret == BLE_STATUS_SUCCESS)
        {
            if ((attr_handle == EATT_PWRQ_ATTR_HANDLE_INVALID) ||
                (entry_p->att_handle == attr_handle))
            {
                wr_ops_p->attr_h = entry_p->att_handle;
                wr_ops_p->attr_offset = entry_p->pwr_offset;
                wr_ops_p->data_len = entry_p->pwr_size;
                wr_ops_p->data_p = (uint8_t *)(((uint8_t *)entry_p) + sizeof(struct EATT_pwrq_entry_s));
                entry_p->conn_handle |= INVALID_CONN_HANDLE_BIT;

                break;
            }
            idx++;
        }
        else
        {
            break;
        }
    }

    return ret;
}

tBleStatus EATT_pwrq_push(uint16_t conn_handle,
                          uint16_t cid,
                          uint16_t attr_h,
                          uint16_t data_offset,
                          uint16_t data_length,
                          uint8_t *data)
{
    tBleStatus ret;
    uint16_t avail_space;
    uint8_t *pwrq_data_p;
    struct EATT_pwrq_entry_s *entry_p;

    ret = BLE_STATUS_ERROR;
    if (EATT_pwrq_ctx.buffer_length != 0U)
    {
        avail_space = PWRQ_GET_AVAILABLE_SPACE();
        if (avail_space >= (sizeof(struct EATT_pwrq_entry_s) + data_length))
        {
            /**
             * Extract prepare write entry from the buffer.
             */
            entry_p = (struct EATT_pwrq_entry_s *)(void *)
                      &EATT_pwrq_ctx.buffer_p[EATT_pwrq_ctx.wr_buffer_size];

            /**
             * Extract entry buffer to write received data.
             */
            pwrq_data_p = &EATT_pwrq_ctx.buffer_p[EATT_pwrq_ctx.wr_buffer_size +
                                                  sizeof(struct EATT_pwrq_entry_s)];

            /**
             * Write entry parameters.
             */
            entry_p->conn_handle = conn_handle;
            entry_p->cid = cid;
            entry_p->att_handle = attr_h;
            entry_p->pwr_offset = data_offset;
            entry_p->pwr_size = data_length;

            /**
             * Write received data in the entry buffer.
             */
            Osal_MemCpy(pwrq_data_p, data, data_length);

            /**
             * Prepare entry is added. Update written buffer size.
             */
            EATT_pwrq_ctx.wr_buffer_size += (uint16_t)ALIGN_UPTO_32BITS(data_length +
                                                                        sizeof(struct EATT_pwrq_entry_s));

            ret = BLE_STATUS_SUCCESS;
        }
    }

    return ret;
}

static tBleStatus EATT_pwrq_get_entry(uint16_t conn_handle,
                                      uint16_t conn_handle_mask,
                                      uint16_t cid,
                                      uint16_t idx,
                                      struct EATT_pwrq_entry_s **entry_pp)
{
    struct EATT_pwrq_entry_s *entry_p;
    uint16_t offset;

    offset = 0U;
    while (offset < EATT_pwrq_ctx.wr_buffer_size)
    {
        /**
         * Extract prepare write entry from the buffer.
         */
        entry_p = (struct EATT_pwrq_entry_s *)(void *)
                  &EATT_pwrq_ctx.buffer_p[offset];

        /**
         * Check if the pointed prepare write entry has the requested connection
         * handle.
         */
        if ((entry_p->conn_handle & conn_handle_mask) == conn_handle)
        {
            if (idx == 0U)
            {
                if (((cid != EATT_PWRQ_CID_ALL) && (cid == entry_p->cid)) ||  /** Filter CID */
                    (cid == EATT_PWRQ_CID_ALL))                               /** Any CID */
                {
                    *entry_pp = entry_p;

                    return BLE_STATUS_SUCCESS;
                }
            }
            idx--;
        }
        offset += (uint16_t)ALIGN_UPTO_32BITS(sizeof(struct EATT_pwrq_entry_s) +
                                              entry_p->pwr_size);
    }

    return BLE_STATUS_ERROR;
}

static void EATT_pwrq_cp32align_blk_left_move(uint32_t *dest_p,
                                              uint32_t *src_p,
                                              uint16_t length)
{
    register uint16_t i;

    for (i = (length >> 2U); i > 0U; i--)
    {
        *dest_p = *src_p;
        dest_p++;
        src_p++;
    }
}

static void EATT_pwrq_rm_entry(struct EATT_pwrq_entry_s *entry_p)
{
    uint16_t pwrq_offset, pwrq_todel_size;
    uint32_t *desti, *srci;

    pwrq_offset = (uintptr_t)(uint8_t *)entry_p - (uintptr_t)EATT_pwrq_ctx.buffer_p;

    /**
     * Compute released fifo size.
     */
    pwrq_todel_size = (uint16_t)ALIGN_UPTO_32BITS(sizeof(struct EATT_pwrq_entry_s) +
                                                  entry_p->pwr_size);

    /**
     * Compute destination and source pointers for copy.
     */
    desti = (uint32_t *)(void *)entry_p;
    srci = (uint32_t *)(void *)&EATT_pwrq_ctx.buffer_p[pwrq_offset +
                                                       pwrq_todel_size];

    /**
     * Move data.
     */
    EATT_pwrq_cp32align_blk_left_move(desti, srci,
                                      EATT_pwrq_ctx.wr_buffer_size -
                                      pwrq_todel_size - pwrq_offset);

    /**
     * Remove released fifo from written buffer size.
     */
    EATT_pwrq_ctx.wr_buffer_size -= pwrq_todel_size;
}

