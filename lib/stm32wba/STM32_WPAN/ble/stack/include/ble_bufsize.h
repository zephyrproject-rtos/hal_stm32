/*****************************************************************************
 * @file    ble_bufsize.h
 *
 * @brief   Definition of BLE stack buffers size
 *****************************************************************************
 * @attention
 *
 * Copyright (c) 2018-2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 *****************************************************************************
 */

#ifndef BLE_BUFSIZE_H__
#define BLE_BUFSIZE_H__


/*
 * BLE_DEFAULT_ATT_MTU: minimum MTU value that GATT must support.
 */
#define BLE_DEFAULT_ATT_MTU                  23

/*
 * BLE_DEFAULT_MAX_ATT_SIZE: maximum attribute size.
 */
#define BLE_DEFAULT_MAX_ATT_SIZE            512

/*
 * BLE_PREP_WRITE_X_ATT: compute how many memory blocks are needed to store
 * Prepare Write Request packets when writing a characteristic with size
 * 'max_att' and the used ATT_MTU value is equal to BLE_DEFAULT_ATT_MTU (23).
 */
#define BLE_PREP_WRITE_X_ATT(max_att) \
        (DIVC(max_att, BLE_DEFAULT_ATT_MTU - 5) * 2)

/*
 * BLE_DEFAULT_PREP_WRITE_LIST_SIZE: default minimum Prepare Write List size.
 */
#define BLE_DEFAULT_PREP_WRITE_LIST_SIZE \
        BLE_PREP_WRITE_X_ATT(BLE_DEFAULT_MAX_ATT_SIZE)

/*
 * BLE_MEM_BLOCK_X_... compute how many memory blocks are needed to compose
 * ACL packets, based on the MTU (mtu) and the number of links (n_link)
 */
#define BLE_MEM_BLOCK_SIZE                   32

#define BLE_MEM_BLOCK_X_PTX(n_link)           (n_link)

#define BLE_MEM_BLOCK_X_TX(mtu) \
        (DIVC((mtu) + 4, BLE_MEM_BLOCK_SIZE) + 1)

#define BLE_MEM_BLOCK_X_RX(mtu, n_link) \
        (((DIVC((mtu) + 4, BLE_MEM_BLOCK_SIZE) + 2) * (n_link)) + 1)

/*
 * BLE_MBLOCKS_CALC: minimum number of buffers needed by the stack.
 * This is the minimum recommended value and depends on:
 *  - pw: size of Prepare Write List
 *  - mtu: maximum between ATT MTU, SMP MTU (65) and L2CAP COC MPS
 *  - n_link: maximum number of simultaneous connections
 */
#define BLE_MBLOCKS_CALC(pw, mtu, n_link) \
        ((pw) + BLE_MEM_BLOCK_X_TX(mtu) + BLE_MEM_BLOCK_X_PTX(n_link) + \
         BLE_MEM_BLOCK_X_RX(mtu, n_link))

/*
 * BLE_FIXED_BUFFER_SIZE_BYTES:
 * A part of the RAM, is dynamically allocated by initializing all the pointers
 * defined in a global context variable "mem_alloc_ctx_p".
 * This initialization is made in the Dynamic_allocator functions, which
 * assign a portion of RAM given by the external application to the above
 * mentioned "global pointers".
 *
 * The size of this Dynamic RAM is made of 2 main components:
 * - a part that is parameters-dependent (num of links, GATT buffers, ...),
 *   and which value is made explicit by the following macro;
 * - a part, that may be considered "fixed", i.e. independent from the above
 *   mentioned parameters.
*/
#define BLE_FIXED_BUFFER_SIZE_BYTES   272

/*
 * BLE_PER_LINK_SIZE_BYTES: additional memory size used per link
 */
#define BLE_PER_LINK_SIZE_BYTES       192

/*
 * BLE_PER_ADD_BEARER_SIZE_BYTES: additional memory size used per add. bearer
 */
#define BLE_PER_ADD_BEARER_SIZE_BYTES  40

/*
 * BLE_TOTAL_BUFFER_SIZE: this macro returns the amount of memory, in bytes,
 * needed for the storage of data structures (except GATT database elements)
 * whose size depends on the number of supported connections.
 *
 * @param n_link: Maximum number of simultaneous connections that the device
 * will support. Valid values are from 1 to 20.
 *
 * @param mblocks_count: Number of memory blocks allocated for packets.
 *
 * @param n_add_bearer: Number of additional EATT bearers
 */
#define BLE_TOTAL_BUFFER_SIZE(n_link, mblocks_count, n_add_bearer) \
        (16 + BLE_FIXED_BUFFER_SIZE_BYTES + \
         (BLE_PER_LINK_SIZE_BYTES * (n_link)) + \
         (BLE_PER_ADD_BEARER_SIZE_BYTES * (n_add_bearer)) + \
         ((BLE_MEM_BLOCK_SIZE + 8) * (mblocks_count)))

/*
 * BLE_DEFAULT_NUM_GATT_SERVICES: this macro returns the number of services
 * created by the BLE stack after call to ACI_GATT_INIT and ACI_GAP_INIT.
 */
#define BLE_DEFAULT_NUM_GATT_SERVICES 2

/*
 * BLE_DEFAULT_NUM_GATT_ATTRIBUTES: this macro returns the number of attributes
 * created by the BLE stack after call to ACI_GATT_INIT and ACI_GAP_INIT.
 *
 * @param options: option flags used at BLE stack initialization
 *
 * @param privacy_en: 1 if privacy is used; otherwise 0
 */
#define BLE_DEFAULT_NUM_GATT_ATTRIBUTES(options, privacy_en) \
        ((((options) & BLE_OPTIONS_ENHANCED_ATT) ? \
          (((options) & BLE_OPTIONS_NO_SVC_CHANGE_DESC) ? 4 : \
           ((options) & BLE_OPTIONS_GATT_CACHING) ? 9 : 7) : \
          (((options) & BLE_OPTIONS_NO_SVC_CHANGE_DESC) ? 0 : \
           ((options) & BLE_OPTIONS_GATT_CACHING) ?  7 : 3)) + \
         ((privacy_en) ? 8 : 6))

/*
 * BLE_DEFAULT_ATT_VALUE_ARRAY_SIZE : this macro returns the size of attribute
 * values array used by the BLE stack after call to ACI_GATT_INIT and
 * ACI_GAP_INIT.
 *
 * @param options: option flags used at BLE stack initialization
 *
 * @param n_link: Maximum number of simultaneous connections that the device
 * supports. Valid values are from 1 to 20.
 *
 * @param dev_name_len: Length of the device name as passed to ACI_GAP_INIT
 */
#define BLE_DEFAULT_ATT_VALUE_ARRAY_SIZE(options, n_link, dev_name_len) \
        ((((options) & BLE_OPTIONS_NO_SVC_CHANGE_DESC) ? \
          (((options) & BLE_OPTIONS_ENHANCED_ATT) ? (11 + (n_link)) : 0) : \
          (((options) & BLE_OPTIONS_GATT_CACHING) ? (41 + ((n_link) * 3)) : \
           ((options) & BLE_OPTIONS_ENHANCED_ATT) ? (20 + ((n_link) * 3)) : \
            (9 + ((n_link) * 2)))) + 31 + (dev_name_len))

/*
 * BLE_TOTAL_BUFFER_SIZE_GATT: this macro returns the amount of memory,
 * in bytes, needed for the storage of GATT database elements.
 *
 * @param num_gatt_attributes: Maximum number of Attributes (i.e. the number
 * of characteristic + the number of characteristic values + the number of
 * descriptors, excluding the services) that can be stored in the GATT
 * database. Note that certain characteristics and relative descriptors are
 * added automatically during device initialization so this parameters should
 * be 9 plus the number of user Attributes
 *
 * @param num_gatt_services: Maximum number of Services that can be stored in
 * the GATT database. Note that the GAP and GATT services are automatically
 * added so this parameter should be 2 plus the number of user services
 *
 * @param att_value_array_size: Size of the storage area for Attribute values.
  */
#define BLE_TOTAL_BUFFER_SIZE_GATT(num_gatt_attributes, num_gatt_services, att_value_array_size) \
        (((((att_value_array_size) - 1) | 3) + 1) + \
         (40 * (num_gatt_attributes)) + (48 * (num_gatt_services)))

/*
 * Defintions for Link Layer buffer
 */
#if (BLE_STACK_PERIPHERAL_ONLY)               /* PERIPHERAL ONLY */
#define BLE_LL_MEM_STATIC_SIZE          1204
#define BLE_LL_MEM_PER_SM_SIZE          668
#elif (BLE_STACK_BASIC_FEATURES)              /* BASIC */
#define BLE_LL_MEM_STATIC_SIZE          1376
#define BLE_LL_MEM_PER_SM_SIZE          668
#elif (BLE_STACK_BASIC_PLUS)                  /* BASIC PLUS */
#define BLE_LL_MEM_STATIC_SIZE          1668
#define BLE_LL_MEM_PER_SM_SIZE          776
#else                                         /* FULL */
#if !defined(STM32WBA2xxx)
#define BLE_LL_MEM_STATIC_SIZE          1872
#define BLE_LL_MEM_PER_SM_SIZE          928
#elif defined(STM32WBA20xx) || defined(STM32WBA23xx) || defined(STM32WBA25xx)
#define BLE_LL_MEM_STATIC_SIZE          2012
#define BLE_LL_MEM_PER_SM_SIZE          984
#endif
#endif

#define BLE_LL_MAC_MEM_STATIC_SIZE       948

#if (BLE_STACK_BASIC_FEATURES || BLE_STACK_PERIPHERAL_ONLY)
                                              /* PERIPHERAL ONLY / BASIC */
#define BLE_LL_FEAT_EXT_ADV_SIZE        0
#define BLE_LL_FEAT_ISO_COMMON_SIZE     0
#define BLE_LL_FEAT_ISO_CIS_SIZE        0
#define BLE_LL_FEAT_ISO_BIS_SIZE        0
#define BLE_LL_FEAT_PAWR_SIZE           0
#define BLE_LL_FEAT_CS_SIZE             0
#elif (BLE_STACK_BASIC_PLUS)                  /* BASIC PLUS */
#if !defined(STM32WBA2xxx)
#define BLE_LL_FEAT_EXT_ADV_SIZE        1236
#else
#define BLE_LL_FEAT_EXT_ADV_SIZE        1716
#endif
#define BLE_LL_FEAT_ISO_COMMON_SIZE     0
#define BLE_LL_FEAT_ISO_CIS_SIZE        0
#define BLE_LL_FEAT_ISO_BIS_SIZE        0
#define BLE_LL_FEAT_PAWR_SIZE           0
#define BLE_LL_FEAT_CS_SIZE             0
#else                                         /* FULL */
#if !defined(STM32WBA2xxx)
#define BLE_LL_FEAT_EXT_ADV_SIZE        1236
#define BLE_LL_FEAT_ISO_COMMON_SIZE     5536
#define BLE_LL_FEAT_ISO_CIS_SIZE        96
#define BLE_LL_FEAT_ISO_BIS_SIZE        1512
#define BLE_LL_FEAT_PAWR_SIZE           0
#define BLE_LL_FEAT_CS_SIZE             0
#else /* STM32WBA2xxx */
#define BLE_LL_FEAT_EXT_ADV_SIZE        1720
#define BLE_LL_FEAT_ISO_COMMON_SIZE     0
#define BLE_LL_FEAT_ISO_CIS_SIZE        0
#define BLE_LL_FEAT_ISO_BIS_SIZE        0
#define BLE_LL_FEAT_PAWR_SIZE           2640
#define BLE_LL_FEAT_CS_SIZE             0
#endif
#endif

#define BLE_LL_PER_SM_MARGIN            8
#define BLE_LL_STATIC_MARGIN            8

/*
 * BLE_LL_BUFFER_SIZE: this macro returns the amount of memory, in bytes,
 * needed for the Link Layer.
 *
 * @param n_sm: Maximum number of simultaneous state machine that the Link layer
 * will support. Valid values are from 1 to 20.
 *
 * @param options: Flags indicating the features to support by the Link Layer.
 *
 * @param coex: Boolean value to indicate if the coexistence mode is needed.
 */
#define BLE_LL_BUFFER_SIZE(n_sm, options, coex) \
        ((BLE_LL_MEM_STATIC_SIZE + BLE_LL_STATIC_MARGIN) + \
         ((BLE_LL_MEM_PER_SM_SIZE + BLE_LL_PER_SM_MARGIN) * (n_sm)) + \
         (((options) & BLE_OPTIONS_EXTENDED_ADV) ? \
          BLE_LL_FEAT_EXT_ADV_SIZE : 0) + \
         (((options) & BLE_OPTIONS_CIS) ? BLE_LL_FEAT_ISO_CIS_SIZE : 0) + \
         (((options) & BLE_OPTIONS_BIS) ? BLE_LL_FEAT_ISO_BIS_SIZE : 0) + \
         (((options) & (BLE_OPTIONS_CIS | BLE_OPTIONS_BIS)) ? \
          BLE_LL_FEAT_ISO_COMMON_SIZE : 0) + \
         (((options) & BLE_OPTIONS_PAWR) ? BLE_LL_FEAT_PAWR_SIZE : 0) + \
         (((options) & BLE_OPTIONS_CHAN_SOUNDING) ? BLE_LL_FEAT_CS_SIZE : 0) +\
         ((coex) ? BLE_LL_MAC_MEM_STATIC_SIZE : 0) \
        )


#endif /* BLE_BUFSIZE_H__ */
