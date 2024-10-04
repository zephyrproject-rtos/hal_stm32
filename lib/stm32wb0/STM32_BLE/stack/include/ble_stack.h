/**
  ******************************************************************************
  * @file    ble_stack.h
  * @author  GPM WBL Application team
  * @brief   Header file for Bluetooth LE stack configuration
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

  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BLE_STACK_H
#define BLE_STACK_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "ble_status.h"
#include "ble_stack_user_cfg.h"
#include "ble_api.h"
#include "ble_events.h"


#ifndef MIN
#define MIN(a,b)                        (((a) < (b))? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b)                        (((a) > (b))? (a) : (b))
#endif
#define DIV_CEIL(x, y)                  (((x) + (y) - 1U) / (y))
#define ALIGN_32(x)                     ((((x) - 1U) | 3U) + 1U)

/**
 * BLE_STACK_DEFAULT_ATT_MTU: minimum mtu value that GATT must support.
 * 5.2.1 ATT_MTU, BLUETOOTH SPECIFICATION Version 4.2 [Vol 3, Part G]
 */
#define BLE_STACK_DEFAULT_ATT_MTU                 (23U)

#define BLE_STACK_MEM_BLOCK_SIZE                  (32U)

#define BLE_STACK_DEFAULT_NUM_EATT_CHANNELS       (0U)

/**
 * @name  BLE_STACK_L2CAP_MPS_OCTETS
 * @brief Minimum and Maximum supported MPS values for L2CAP component.
 * @see   BLE Spec. v.5.2, Vol.3, Part A, Sec.4.1, Table 4.1
 * @{
 */
#define BLE_STACK_L2CAP_MPS_OCTETS_MIN             (23U)
#define BLE_STACK_L2CAP_MPS_OCTETS_MAX             (1024U) /* MPS limited to 1KB */
/**
 * @}
 */


/**
 * BLE_STACK_SM_SECURE_CONN_MTU: mtu size needed for Security Manager Channel Configuration
 * Parameters with LE Secure Connections.
 * 3.2 SECURITY MANAGER CHANNEL OVER L2CAP, BLUETOOTH SPECIFICATION Version 4.2
 * [Vol 3, Part H]
 */
#define BLE_STACK_SM_SECURE_CONN_MTU              (65U)

/*
 * BLE_STACK_MAX_ATT_MTU: maximum supported ATT_MTU size.
 */
#define BLE_STACK_MAX_ATT_MTU                     (1024U - 6U)  // (6 bytes for L2CAP header)

/**
 * BLE_STACK_DEFAULT_MAX_ATT_MTU: default max ATT_MTU size.
 */
#define BLE_STACK_DEFAULT_MAX_ATT_MTU             (251U - 6U) // (6 bytes for L2CAP header)

/**
 * BLE_STACK_DEFAULT_MAX_ATT_SIZE: maximum attribute size.
 */
#define BLE_STACK_DEFAULT_MAX_ATT_SIZE            (512U)

/**
 * BLE_STACK_MEM_BLOCK_X_MTU(mtu, n_links): compute how many memory blocks are needed to
 * support a maximum number (n_links) of simultaneous connections that use ATT
 * packet with ATT_MTU=mtu.
 * 7.2 FRAGMENTATION AND RECOMBINATION, BLUETOOTH SPECIFICATION Version 4.2
 * [Vol 3, Part A]
 */

#define BLE_STACK_MEM_BLOCK_X_TX(mtu)             (DIV_CEIL((mtu) + 6U, BLE_STACK_MEM_BLOCK_SIZE) + 1U)
#define BLE_STACK_MEM_BLOCK_X_RX(mtu, n_link)     ((DIV_CEIL((mtu) + 6U, BLE_STACK_MEM_BLOCK_SIZE) + 2U) * (n_link) + 1U)
#define BLE_STACK_MEM_BLOCK_X_MTU(mtu, n_link)    (BLE_STACK_MEM_BLOCK_X_TX(mtu) + BLE_STACK_MEM_BLOCK_X_RX(mtu, n_link))

/**
 * Minimum number of blocks required for secure connections
 */
#define BLE_STACK_MBLOCKS_SECURE_CONNECTIONS      (4U)

/**
 * BLE_STACK_MBLOCKS_CALC(mtu, n_link): minimum number of buffers needed by the stack.
 * This is the minimum racomanded value and depends on:
 *  - mtu: ATT_MTU size
 *  - n_link: maximum number of simultaneous connections
 *  - n_eatt_ch: number of EATT channels
 */
#define BLE_STACK_MBLOCKS_CALC(mtu, n_link, n_eatt_ch) MAX(BLE_STACK_MEM_BLOCK_X_MTU(mtu, (n_link) + (n_eatt_ch)), \
                                                           BLE_STACK_MBLOCKS_SECURE_CONNECTIONS)

/**
 * Default memory blocks count
 */
#define BLE_STACK_DEFAULT_MBLOCKS_COUNT BLE_STACK_MBLOCKS_CALC(BLE_STACK_DEFAULT_MAX_ATT_MTU, \
                                                               BLE_STACK_NUM_LINKS, \
                                                               BLE_STACK_DEFAULT_NUM_EATT_CHANNELS)

/**
 * Amount of memory used for each GATT attribute entry.
 */
#define BLE_STACK_GATT_ATTRIBUTE_SIZE (8U)

/**
 * Number of GATT attributes used for mandatory profiles (GATT and GAP).
 */
#define BLE_STACK_NUM_GATT_MANDATORY_ATTRIBUTES (19U)

/**
 * Amount of memory needed by each GATT Client procedure context
 */
#define COEFF_NUM_GATT_CLIENT_PROCS (36U)

/**
 * Amount of memory needed by each EATT channel.
 */
#define COEFF_NUM_EATT_CHANNELS (32U)

#define LL_TX_MAX_BUFFER_SIZE      (292UL)
#define LL_TX_DEFAULT_BUFFER_SIZE  (68UL)
#define LL_RX_MAX_BUFFER_SIZE      (260UL)
#define LL_RX_DEFAULT_BUFFER_SIZE  (44UL)
#define BLE_STACK_TX_BUFFER_SIZE(EXT_ADV_SCAN_EN, DL_EXT_EN, NUM_BRC_BIG, NUM_SYNC_BIG, NUM_CIG) \
                                    ((((EXT_ADV_SCAN_EN) == 1U) || ((DL_EXT_EN) == 1U) || ((NUM_CIG) > 0U) || ((NUM_BRC_BIG) > 0U) || ((NUM_SYNC_BIG) > 0U)) ? LL_TX_MAX_BUFFER_SIZE : LL_TX_DEFAULT_BUFFER_SIZE)
#define BLE_STACK_RX_BUFFER_SIZE(EXT_ADV_SCAN_EN, DL_EXT_EN, NUM_BRC_BIG, NUM_SYNC_BIG, NUM_CIG) \
                                    ((((EXT_ADV_SCAN_EN) == 1U) || ((DL_EXT_EN) == 1U) || ((NUM_CIG) > 0U) || ((NUM_BRC_BIG) > 0U) || ((NUM_SYNC_BIG) > 0U)) ? LL_RX_MAX_BUFFER_SIZE : LL_RX_DEFAULT_BUFFER_SIZE)

/**
 * Amount of memory needed to support ISO feature
 */
#define BLE_STACK_ISO_CMN_SIZE(NUM_BRC_BIG, NUM_SYNC_BIG, NUM_CIG)    ((((NUM_BRC_BIG) + (NUM_SYNC_BIG) + (NUM_CIG)) > 0U) ?                \
                                                                        (12U + 4U)                                                          \
                                                                       : 0U)

#define BLE_STACK_BIG_SIZE(NUM_BRC_BIG, NUM_BRC_BIS, NUM_SYNC_BIG, NUM_SYNC_BIS)     ((((NUM_BRC_BIG) + (NUM_SYNC_BIG)) > 0U) ?             \
                                                                                        (248U * (NUM_BRC_BIG) +                             \
                                                                                           8U * (NUM_BRC_BIG) * (NUM_BRC_BIS) +             \
                                                                                         296U * (NUM_SYNC_BIG) +                            \
                                                                                          20U * (NUM_SYNC_BIS) * (NUM_SYNC_BIG))            \
                                                                                        : 0U)

#define BLE_STACK_CIG_SIZE(NUM_CIG, NUM_CIS)    (((NUM_CIG) > 0U) ?                                                                         \
                                                  (16U + 56U +                                                                              \
                                                  168U * (NUM_CIG) +                                                                        \
                                                  192U * (NUM_CIS))                                                                         \
                                                 : 0U)

#define BLE_STACK_ISOAL_SIZE(NUM_TX_STREAMS, NUM_RX_STREAMS)    ((((NUM_TX_STREAMS) + (NUM_RX_STREAMS)) > 0U) ?                             \
                                                                    (20U +                                                                  \
                                                                     12U * ((NUM_TX_STREAMS) + (NUM_RX_STREAMS)) +                          \
                                                                     52U * (NUM_TX_STREAMS) +                                               \
                                                                     28U * (NUM_RX_STREAMS))                                                \
                                                                   : 0U)

#define BLE_STACK_ISO_SIZE(NUM_BRC_BIG, NUM_BRC_BIS, NUM_SYNC_BIG, NUM_SYNC_BIS, NUM_CIG, NUM_CIS)                                          \
                                           (BLE_STACK_ISO_CMN_SIZE(NUM_BRC_BIG, NUM_SYNC_BIG, NUM_CIG) +                                    \
                                            BLE_STACK_BIG_SIZE(NUM_BRC_BIG, NUM_BRC_BIS, NUM_SYNC_BIG, NUM_SYNC_BIS) +                      \
                                            BLE_STACK_CIG_SIZE(NUM_CIG, NUM_CIS) +                                                          \
                                            BLE_STACK_ISOAL_SIZE((NUM_BRC_BIG) * (NUM_BRC_BIS) + (NUM_CIS),                                 \
                                                                 (NUM_SYNC_BIG) * (NUM_SYNC_BIS) + (NUM_CIS)))


#if (BLESTACK_CONTROLLER_ONLY == 0)

/**
 * A part of the RAM, is dynamically allocated by initializing all the pointers
 * defined in a global context variable "mem_alloc_ctx_p".
 * This initialization is made in the Dynamic_allocator functions, which
 * assign a portion of RAM given by the external application to the above
 * mentioned "global pointers".
 *
 * The size of this Dynamic RAM is made of 2 main components:
 * - a part that is parameters-dependent (num of links, GATT buffers, ...),
 *   and whose value is made explicit by the following macros BLE_STACK_*_SIZE;
 * - a part, that may be considered "fixed", i.e., independent from the above
 *   mentioned parameters.
*/
#   define BLE_STACK_FIXED_BUFFER_SIZE_BYTES (970U)

/**
 * Amount of memory needed by each radio link
 */
#   define COEFF_CONN_SUPP_EN   (840U + BLE_STACK_GATT_ATTRIBUTE_SIZE * BLE_STACK_NUM_GATT_MANDATORY_ATTRIBUTES)
#   define COEFF_NUM_OF_LINKS_0 (48U)
#   define COEFF_NUM_OF_LINKS_1 (656U)
#   define BLE_STACK_LINKS_SIZE(CONN_SUPP_EN, NUM_OF_LINKS) \
        (((CONN_SUPP_EN) == 1U) || ((NUM_OF_LINKS) > 0U) ? COEFF_CONN_SUPP_EN * (CONN_SUPP_EN) + COEFF_NUM_OF_LINKS_0 * (NUM_OF_LINKS) + COEFF_NUM_OF_LINKS_1 * (CONN_SUPP_EN) * (NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed for mem. blocks allocated for connections
 */
#   define BLE_STACK_MBLOCK_SIZE(MEM_BLOCK_COUNT) ((4U + BLE_STACK_MEM_BLOCK_SIZE) * (MEM_BLOCK_COUNT))

/**
 * Amount of memory needed to support PHY Update feature
 */
#   define BLE_STACK_PHY_UPD_SIZE(CONN_SUPP_EN, PHY_UPD_EN, NUM_OF_LINKS) (((PHY_UPD_EN) == 1U) ? 8U + 48U * (CONN_SUPP_EN) * (NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed to support extended advertising and scanning feature. Note that if
 * extended advertising is enabled the memory required by the legacy advertising set must be
 * subtracted from the total
 */
#   define BLE_STACK_CONTROLLER_EXT_ADV_SIZE(ENABLED, NUM_ADV_SET, NUM_AUX_EVENT, NUM_OF_LINKS) \
        (((ENABLED) == 1U) ? -276U + 368U * (NUM_ADV_SET) + 0U * (NUM_AUX_EVENT) + 0U * (NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed for the Filter Accept List and, if connections are supported, also for connection ID list
 */
#   define BLE_STACK_FILTER_ACCEPT_LIST_SIZE(WL_SIZE_LOG2) (8U * (1U << (WL_SIZE_LOG2)))
#   define BLE_STACK_CONN_ID_LIST_SIZE(CONN_SUPP_EN, WL_SIZE_LOG2) (((CONN_SUPP_EN) == 1U) ? BLE_STACK_FILTER_ACCEPT_LIST_SIZE(WL_SIZE_LOG2) : 0U)

/**
 * Amount of memory needed to support L2CAP COCs (Connection Oriented Channels)
 */
#   define BLE_STACK_L2C_COCS_SIZE(CONN_SUPP_EN, L2C_COS_EN, NUM_OF_COCS) (((CONN_SUPP_EN) == 1U) && ((L2C_COS_EN) == 1U) ? 84U * (NUM_OF_COCS) : 0U)

/**
 * Amount of memory needed to support Data Length Extension feature
 */
#   define BLE_STACK_D_LEN_EXT_SIZE(LEN_EXT_ENABLED, ADV_EXT_ENABLED) ((((LEN_EXT_ENABLED) == 1U) || ((ADV_EXT_ENABLED) == 1U)) ? 0U : 0U)

/**
 * Amount of memory needed to support periodic advertising and synchronizing feature
 */
#   define BLE_STACK_CONTROLLER_PERIODIC_ADV_WR_SIZE(PER_ADV_WR_EN, CONN_SUPP_EN, NUM_ADV_SET, NUM_SUBEVENTS_PAWR, MAX_SUBEVENT_DATA_COUNT_PAWR) \
        ((((PER_ADV_WR_EN) == 1U) && ((CONN_SUPP_EN) == 1U)) ? (132U + 8U * (NUM_SUBEVENTS_PAWR) + 16U * (MAX_SUBEVENT_DATA_COUNT_PAWR)) * (NUM_ADV_SET) : 0U)

#   define BLE_STACK_CONTROLLER_PERIODIC_ADV_SIZE(PER_ADV_EN, PER_ADV_WR_EN, CONN_SUPP_EN, NUM_LINKS, NUM_ADV_SET, NUM_SUBEVENTS_PAWR, MAX_SUBEVENT_DATA_COUNT_PAWR) \
        (((PER_ADV_EN) == 1U) ? (156U * (NUM_ADV_SET) + 32U * (NUM_LINKS) + \
                                 BLE_STACK_CONTROLLER_PERIODIC_ADV_WR_SIZE(PER_ADV_WR_EN, CONN_SUPP_EN, NUM_ADV_SET, NUM_SUBEVENTS_PAWR, MAX_SUBEVENT_DATA_COUNT_PAWR)) : \
                                0U)

/**
 * Amount of memory needed to support the scan feature
 */
#   define BLE_STACK_BASE_SIZE(CONN_SUPP_EN) (((CONN_SUPP_EN) == 1U) ? 32U : 20U)

#   define BLE_STACK_PAST_SIZE(CONN_SUPP_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) ? 24U * (NUM_OF_LINKS) : 0U)

#   define BLE_STACK_PER_SYNC_SIZE(PER_ADV_EN, CONN_SUPP_EN, NUM_SYNC_SLOTS, NUM_OF_LINKS, ADV_LIST_LIZE)\
        (((PER_ADV_EN) == 1U) ? BLE_STACK_BASE_SIZE(CONN_SUPP_EN) + 144U * (NUM_SYNC_SLOTS) + 8U * (1U << (ADV_LIST_LIZE)) + BLE_STACK_PAST_SIZE(CONN_SUPP_EN, NUM_OF_LINKS) : 0U)

#   define BLE_STACK_PER_SYNC_WR_SIZE(PER_ADV_EN, PER_ADV_WR_EN, CONN_SUPP_EN, NUM_SYNC_SLOTS, NUM_SYNC_SUBEVENTS)\
        (((PER_ADV_WR_EN & PER_ADV_EN & CONN_SUPP_EN) == 1U) ? 176U * (NUM_SYNC_SLOTS) + ALIGN_32(NUM_SYNC_SUBEVENTS) : 0U)

#   define BLE_STACK_CONTROLLER_SCAN_SIZE(SCAN_EN, EXT_ADV_EN, PER_ADV_EN, PER_ADV_WR_EN, CONN_SUPP_EN, NUM_AUX_EVENT,\
                                          NUM_SYNC_SLOTS, NUM_OF_LINKS, ADV_LIST_LIZE, NUM_SYNC_SUBEVENTS) \
        (((SCAN_EN) == 1U) ? 320U + (192U + 48U * (NUM_AUX_EVENT) + \
            BLE_STACK_PER_SYNC_SIZE(PER_ADV_EN, CONN_SUPP_EN, NUM_SYNC_SLOTS, NUM_OF_LINKS, ADV_LIST_LIZE) + \
            BLE_STACK_PER_SYNC_WR_SIZE(PER_ADV_EN, PER_ADV_WR_EN, CONN_SUPP_EN, NUM_SYNC_SLOTS, NUM_SYNC_SUBEVENTS)) * (EXT_ADV_EN) : 0U)


/**
 * Amount of memory needed to support controller privacy feature
 */
#   define BLE_STACK_CONTROLLER_PRIV_SIZE(ENABLED, FILTER_ACCEPT_LIST_SIZE_LOG2) (((ENABLED) == 1U) ? 104U + 80U * (1U << (FILTER_ACCEPT_LIST_SIZE_LOG2)) : 0U)

/**
 * Amount of memory needed to support CTE feature
 */
#   define BLE_STACK_CTE_NUM_OF_LINKS(CONN_SUPP_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) ? 8U * (NUM_OF_LINKS) : 0U)
#   define BLE_STACK_CTE_NUM_OF_ANT_IDS(CONN_SUPP_EN, NUM_OF_LINKS, NUM_OF_ANT_IDS)\
        (((NUM_OF_ANT_IDS) > 0U) ? (1U + 0U * (CONN_SUPP_EN) * (NUM_OF_LINKS)) * ALIGN_32(NUM_OF_ANT_IDS) : 0U)
    /** In the macro above, note that:
     *  - the contribution associated with the nr. of links is 0 because the macro CONN_ANT_PATT is not defined
     *  - the contribution associated with the nr. of antenna IDs is adapted to the word alignment
     */
#   define BLE_STACK_CTE_NUM_OF_IQ_SAMPLES(NUM_OF_IQSAMPLES) (4U * (NUM_OF_IQSAMPLES))
#   define BLE_STACK_CTE_TIMER(SCAN_EN, EXT_ADV_EN, PER_ADV_EN, NUM_OF_IQSAMPLES) \
        ((((SCAN_EN) == 1U) && ((EXT_ADV_EN) == 1U) && ((PER_ADV_EN) == 1U) && ((NUM_OF_IQSAMPLES) > 0U)) ? 24U : 0U)

#   define BLE_STACK_CTE_SIZE(SCAN_EN, EXT_ADV_EN, PER_ADV_EN, CONN_SUPP_EN, CTE_EN, NUM_OF_LINKS, NUM_OF_ANT_IDS, NUM_OF_IQSAMPLES) \
        (((CTE_EN) == 1U) ? 12U + \
                            BLE_STACK_CTE_NUM_OF_LINKS(CONN_SUPP_EN, NUM_OF_LINKS) + \
                            BLE_STACK_CTE_NUM_OF_ANT_IDS(CONN_SUPP_EN, NUM_OF_LINKS, NUM_OF_ANT_IDS) + \
                            BLE_STACK_CTE_NUM_OF_IQ_SAMPLES(NUM_OF_IQSAMPLES) + \
                            BLE_STACK_CTE_TIMER(SCAN_EN, EXT_ADV_EN, PER_ADV_EN, NUM_OF_IQSAMPLES) : \
                            0U)

/**
 * Amount of memory needed to support PCL feature
 */
#   define BLE_STACK_PCL_NUM_OF_LINKS(NUM_OF_LINKS)  (32U * (NUM_OF_LINKS))
#   define BLE_STACK_PCL_SIZE(CONN_SUPP_EN, PCL_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) && ((PCL_EN) == 1U) ? 20U + BLE_STACK_PCL_NUM_OF_LINKS(NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed to support the LE Channel Classification feature
 */
#   define BLE_STACK_CHC_NUM_OF_LINKS(NUM_OF_LINKS) (28U * (NUM_OF_LINKS))
#   define BLE_STACK_CHC_SIZE(CONN_SUPP_EN, CHC_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) && ((CHC_EN) == 1U) ? BLE_STACK_CHC_NUM_OF_LINKS(NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed by FIFOs
 */
#   define CALC_FIFO_SIZE(FS) ((((FS) + 3U) >> 2U) << 2U)
#   define BLE_STACK_FIFO_SIZE(ISR0_FS, ISR1_FS, USER_FS) (CALC_FIFO_SIZE(ISR0_FS) + CALC_FIFO_SIZE(ISR1_FS) + CALC_FIFO_SIZE(USER_FS))

/**
 * Amount of memory needed by GATT when connection support is enabled
 */
#   define BLE_STACK_GATT_SIZE(CONN_SUPP_EN, GATT_ATTRIBUTES, GATT_CLIENT_PROCS, GATT_NUM_EATT_CHANNELS) \
        (((CONN_SUPP_EN) == 1U) ? (BLE_STACK_GATT_ATTRIBUTE_SIZE * (GATT_ATTRIBUTES) + \
                                COEFF_NUM_GATT_CLIENT_PROCS * (GATT_CLIENT_PROCS) + \
                                COEFF_NUM_EATT_CHANNELS * (GATT_NUM_EATT_CHANNELS)) \
                                : 0U)


#else // (BLESTACK_CONTROLLER_ONLY == 1)

#   define BLE_STACK_FIXED_BUFFER_SIZE_BYTES (828U)

/**
 * Amount of memory needed by each radio link
 */
#   define COEFF_CONN_SUPP_EN   (180U)
#   define COEFF_NUM_OF_LINKS_0 (48U)  // [DB] NOTE: scheduler's tasks
#   define COEFF_NUM_OF_LINKS_1 (484U)
#   define BLE_STACK_LINKS_SIZE(CONN_SUPP_EN, NUM_OF_LINKS) \
        (((CONN_SUPP_EN) == 1U) || ((NUM_OF_LINKS) > 0U) ? COEFF_CONN_SUPP_EN * (CONN_SUPP_EN) + COEFF_NUM_OF_LINKS_0 * (NUM_OF_LINKS) + COEFF_NUM_OF_LINKS_1 * (CONN_SUPP_EN) * (NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed for mem. blocks allocated for connections
 */
#   define BLE_STACK_MBLOCK_SIZE(MEM_BLOCK_COUNT) ((4U + BLE_STACK_MEM_BLOCK_SIZE) * (MEM_BLOCK_COUNT))

/**
 * Amount of memory needed to support PHY Update feature
 */
#   define BLE_STACK_PHY_UPD_SIZE(CONN_SUPP_EN, PHY_UPD_EN, NUM_OF_LINKS) (((PHY_UPD_EN) == 1U) ? 16U * (CONN_SUPP_EN) * (NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed to support extended advertising and scanning feature. Note that if
 * extended advertising is enabled the memory required by the legacy advertising set must be
 * subtracted from the total
 */
#   define BLE_STACK_CONTROLLER_EXT_ADV_SIZE(ENABLED, NUM_ADV_SET, NUM_AUX_EVENT, NUM_OF_LINKS) \
        (((ENABLED) == 1U) ? -256U + 348U * (NUM_ADV_SET) + 0U * (NUM_AUX_EVENT) + 0U * (NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed for the Filter Accept List and, if connections are supported, also for connection ID list
 */
#   define BLE_STACK_FILTER_ACCEPT_LIST_SIZE(WL_SIZE_LOG2) (8U * (1U << (WL_SIZE_LOG2)))
#   define BLE_STACK_CONN_ID_LIST_SIZE(CONN_SUPP_EN, WL_SIZE_LOG2) (((CONN_SUPP_EN) == 1U) ? BLE_STACK_FILTER_ACCEPT_LIST_SIZE(WL_SIZE_LOG2) : 0U)

/**
 * Amount of memory needed to support L2CAP COCs (Connection Oriented Channels)
 */
#   define BLE_STACK_L2C_COCS_SIZE(CONN_SUPP_EN, L2C_COS_EN, NUM_OF_COCS) (0U)

/**
 * Amount of memory needed to support Data Length Extension feature
 */
#   define BLE_STACK_D_LEN_EXT_SIZE(LEN_EXT_ENABLED, ADV_EXT_ENABLED) ((((LEN_EXT_ENABLED) == 1U) || ((ADV_EXT_ENABLED) == 1U)) ? 0U : 0U)

/**
 * Amount of memory needed to support periodic advertising and synchronizing feature
 */
#   define BLE_STACK_CONTROLLER_PERIODIC_ADV_WR_SIZE(PER_ADV_WR_EN, CONN_SUPP_EN, NUM_ADV_SET, NUM_SUBEVENTS_PAWR, MAX_SUBEVENT_DATA_COUNT_PAWR) \
        ((((PER_ADV_WR_EN) == 1U) && ((CONN_SUPP_EN) == 1U)) ? (132U + 8U * (NUM_SUBEVENTS_PAWR) + 16U * (MAX_SUBEVENT_DATA_COUNT_PAWR)) * (NUM_ADV_SET) : 0U)

#   define BLE_STACK_CONTROLLER_PERIODIC_ADV_SIZE(PER_ADV_EN, PER_ADV_WR_EN, CONN_SUPP_EN, NUM_LINKS, NUM_ADV_SET, NUM_SUBEVENTS_PAWR, MAX_SUBEVENT_DATA_COUNT_PAWR) \
        (((PER_ADV_EN) == 1U) ? (156U * (NUM_ADV_SET) + 32U * (NUM_LINKS) + \
                                 BLE_STACK_CONTROLLER_PERIODIC_ADV_WR_SIZE(PER_ADV_WR_EN, CONN_SUPP_EN, NUM_ADV_SET, NUM_SUBEVENTS_PAWR, MAX_SUBEVENT_DATA_COUNT_PAWR)) : \
                                0U)

/**
 * Amount of memory needed to support the scan feature
 */
#   define BLE_STACK_BASE_SIZE(CONN_SUPP_EN) (((CONN_SUPP_EN) == 1U) ? 32U : 20U)

#   define BLE_STACK_PAST_SIZE(CONN_SUPP_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) ? 24U * (NUM_OF_LINKS) : 0U)

#   define BLE_STACK_PER_SYNC_SIZE(PER_ADV_EN, CONN_SUPP_EN, NUM_SYNC_SLOTS, NUM_OF_LINKS, ADV_LIST_LIZE)\
    (((PER_ADV_EN) == 1U) ? BLE_STACK_BASE_SIZE(CONN_SUPP_EN) + 144U * (NUM_SYNC_SLOTS) + 8U * (1U << (ADV_LIST_LIZE)) + BLE_STACK_PAST_SIZE(CONN_SUPP_EN, NUM_OF_LINKS) : 0U)

#   define BLE_STACK_PER_SYNC_WR_SIZE(PER_ADV_EN, PER_ADV_WR_EN, CONN_SUPP_EN, NUM_SYNC_SLOTS, NUM_SYNC_SUBEVENTS)\
        (((PER_ADV_WR_EN & PER_ADV_EN & CONN_SUPP_EN) == 1U) ? 176U * (NUM_SYNC_SLOTS) + ALIGN_32(NUM_SYNC_SUBEVENTS) : 0U)

#   define BLE_STACK_CONTROLLER_SCAN_SIZE(SCAN_EN, EXT_ADV_EN, PER_ADV_EN, PER_ADV_WR_EN, CONN_SUPP_EN, NUM_AUX_EVENT,\
                                          NUM_SYNC_SLOTS, NUM_OF_LINKS, ADV_LIST_LIZE, NUM_SYNC_SUBEVENTS) \
        (((SCAN_EN) == 1U) ? 320U + (164U + 48U * (NUM_AUX_EVENT) + \
                             BLE_STACK_PER_SYNC_SIZE(PER_ADV_EN, CONN_SUPP_EN, NUM_SYNC_SLOTS, NUM_OF_LINKS, ADV_LIST_LIZE) + \
                             BLE_STACK_PER_SYNC_WR_SIZE(PER_ADV_EN, PER_ADV_WR_EN, CONN_SUPP_EN, NUM_SYNC_SLOTS, NUM_SYNC_SUBEVENTS)) * (EXT_ADV_EN) : 0U)

/**
 * Amount of memory needed to support controller privacy feature
 */
#   define BLE_STACK_CONTROLLER_PRIV_SIZE(ENABLED, FILTER_ACCEPT_LIST_SIZE_LOG2) (((ENABLED) == 1U) ? 104U + 80U * (1U << (FILTER_ACCEPT_LIST_SIZE_LOG2)) : 0U)

/**
 * Amount of memory needed to support CTE feature
 */
#   define BLE_STACK_CTE_NUM_OF_LINKS(CONN_SUPP_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) ? 8U * (NUM_OF_LINKS) : 0U)
#   define BLE_STACK_CTE_NUM_OF_ANT_IDS(CONN_SUPP_EN, NUM_OF_LINKS, NUM_OF_ANT_IDS)\
        (((NUM_OF_ANT_IDS) > 0U) ? (1U + 0U * (CONN_SUPP_EN) * (NUM_OF_LINKS)) * (1U + (((NUM_OF_ANT_IDS) - 1U) | 3U)) : 0U)
    /** In the macro above, note that:
     *  - the contribution associated with the nr. of links is 0 because the macro CONN_ANT_PATT is not defined
     *  - the contribution associated with the nr. of antenna IDs is adapted to the word alignment
     */
#   define BLE_STACK_CTE_NUM_OF_IQ_SAMPLES(NUM_OF_IQSAMPLES) (4U * (NUM_OF_IQSAMPLES))

#   define BLE_STACK_CTE_TIMER(SCAN_EN, EXT_ADV_EN, PER_ADV_EN, NUM_OF_IQSAMPLES) \
        ((((SCAN_EN) == 1U) && ((EXT_ADV_EN) == 1U) && ((PER_ADV_EN) == 1U) && ((NUM_OF_IQSAMPLES) > 0U)) ? 24U : 0U)

#   define BLE_STACK_CTE_SIZE(SCAN_EN, EXT_ADV_EN, PER_ADV_EN, CONN_SUPP_EN, CTE_EN, NUM_OF_LINKS, NUM_OF_ANT_IDS, NUM_OF_IQSAMPLES) \
        (((CTE_EN) == 1U) ? 12U + \
                            BLE_STACK_CTE_NUM_OF_LINKS(CONN_SUPP_EN, NUM_OF_LINKS) + \
                            BLE_STACK_CTE_NUM_OF_ANT_IDS(CONN_SUPP_EN, NUM_OF_LINKS, NUM_OF_ANT_IDS) + \
                            BLE_STACK_CTE_NUM_OF_IQ_SAMPLES(NUM_OF_IQSAMPLES) + \
                            BLE_STACK_CTE_TIMER(SCAN_EN, EXT_ADV_EN, PER_ADV_EN, NUM_OF_IQSAMPLES) : \
                            0U)

/**
 * Amount of memory needed to support PCL feature
 */
#   define BLE_STACK_PCL_NUM_OF_LINKS(NUM_OF_LINKS)  (32U * (NUM_OF_LINKS))
#   define BLE_STACK_PCL_SIZE(CONN_SUPP_EN, PCL_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) && ((PCL_EN) == 1U) ? 20U + BLE_STACK_PCL_NUM_OF_LINKS(NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed to support the LE Channel Classification feature
 */
#   define BLE_STACK_CHC_NUM_OF_LINKS(NUM_OF_LINKS) (28U * (NUM_OF_LINKS))
#   define BLE_STACK_CHC_SIZE(CONN_SUPP_EN, CHC_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) && ((CHC_EN) == 1U) ? BLE_STACK_CHC_NUM_OF_LINKS(NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed by FIFOs
 */
#   define CALC_FIFO_SIZE(FS) ((((FS) + 3U) >> 2U) << 2U)
#   define BLE_STACK_FIFO_SIZE(ISR0_FS, ISR1_FS, USER_FS) (CALC_FIFO_SIZE(ISR0_FS) + CALC_FIFO_SIZE(ISR1_FS) + CALC_FIFO_SIZE(USER_FS))

/**
 * Amount of memory needed by GATT when connection support is enabled
 */
#   define BLE_STACK_GATT_SIZE(CONN_SUPP_EN, GATT_ATTRIBUTES, GATT_CLIENT_PROCS, NUM_EATT_CHANNELS) (0U)

#endif // BLESTACK_CONTROLLER_ONLY

/**
 *
 * This macro returns the amount of memory, in bytes, needed for the storage of GATT database elements
 * and other data structures whose size depends on the number of supported connections.
 *
 * @param BLE_STACK_NUM_LINKS: Maximum number of simultaneous connections that the device will support.
 * @param BLE_STACK_NUM_EATT_CHANNELS: Maximum number of simultaneous EATT active channels that the device will support.
 * @param BLE_STACK_NUM_GATT_ATTRIBUTES: Maximum number of Attributes (i.e. the number of characteristic + the number of characteristic values + the number of descriptors, excluding the services) that can be stored in the GATT database. Note that certain characteristics and relative descriptors are added automatically during device initialization so this parameters should be 9 plus the number of user Attributes
 * @param BLE_STACK_NUM_GATT_CLIENT_PROCS: Maximum number of concurrent GATT Client Procedures.
 * @param BLE_STACK_MBLOCKS_COUNT: Number of memory blocks allocated for packets.
 * @param BLE_STACK_D_LEN_EXT_EN: Enable or disable the Extended Packet length feature. Valid values are 0 or 1.
 * @param BLE_STACK_PHY_UPD_EN: Enable or disable the PHY Update feature. Valid values are 0 or 1.
 * @param BLE_STACK_EXT_ADV_SCAN_EN: Enable or disable the Extended Advertising and Scanning feature. Valid values are 0 or 1.
 * @param BLE_STACK_CTRL_PRIV_EN: Enable or disable the Controller privacy feature. Valid values are 0 or 1.
 * @param BLE_STACK_SEC_CONN_EN: Enable or disable the secure connection feature. Valid values are 0 or 1.
 * @param BLE_STACK_SCAN_EN: Enable or disable the Scan feature. Valid values are 0 or 1.
 * @param NUM_ADV_SET: Number of advertising sets. Valid values are > 0.
 * @param NUM_SUBEVENTS_PAWR: Number of periodic advertising with responses (PAwR) subevents. Valid values are > 0 if PAwR is supported.
 * @param MAX_SUBEVENT_DATA_COUNT_PAWR: Maximum number of periodic advertising with responses (PAwR) subevents that data can be requested for. Valid values are > 0 if PAwR is supported.
 * @param NUM_SUBEVENTS_PAWR: Maximum number of PAwR subevents.
 * @param NUM_AUX_EVENT: Number of radio tasks to allocate for secondary channels scanning (i.e., auxiliary events).
 * @param FILTER_ACCEPT_LIST_SIZE_LOG2: log2 ceiling of Filter Accept List size.
 * @param BLE_STACK_L2CAP_COS_EN: Enable or disable the L2CAP Channel Oriented Stream feature. Valid values are 0 or 1.
 * @param NUM_L2CAP_COCS: Number of L2CAP COS channels.
 * @param CONTROLLER_PERIODIC_ADV_EN: Enable or disable the Periodic Advertising and Synchronization feature. Valid values are 0 or 1.
 * @param CONTROLLER_PERIODIC_ADV_WR_EN: Enable or disable the Periodic Advertising and Synchronization with Responses feature. Valid values are 0 or 1.
 * @param NUM_SYNC_SLOTS: Number of radio tasks to allocate for synchronizing to periodic advertisements.
 * @param BLE_STACK_CTE_EN: Enable or disable the CTE feature. Valid values are 0 or 1.
 * @param NUM_CTE_ANT_IDS: Maximum antenna switching pattern length
 * @param NUM_CTE_IQSAMPLES: Maximum number of IQ-Samples in the buffer
 * @param BLE_STACK_PCL_EN: Enable or disable the Power Control & Path Loss Monitoring feature. Valid values are 0 or 1.
 * @param BLE_STACK_CONN_SUPP_EN: Enable or disable the support of ACL connections.
 * @param BLE_STACK_CHC_EN: Enable or disable the LE Channel Classification feature. Valid values are 0 or 1.
 * @param BLE_STACK_NUM_SYNC_BIG: Number of BIG Synchronous groups to support.
 * @param BLE_STACK_NUM_BRC_BIG: Number of BIG Broadcaster groups to support.
 * @param BLE_STACK_NUM_SYNC_BIS: Number of BIG Synchronous streams per group to support.
 * @param BLE_STACK_NUM_BRC_BIS: Number of BIG Broadcaster streams per group to support.
 * @param BLE_STACK_NUM_CIG: Number of CIG groups to support.
 * @param BLE_STACK_NUM_CIS: Number of CIS streams to support.
 * @param BLE_STACK_CIS_EN: Enable or disable the Connected Isochronous Streams feature. Valid values are 0 or 1.
 * @param ISR0_FIFO_SIZE: Size of the internal FIFO used for critical controller events produced by the ISR (e.g. rx data packets)
 * @param ISR1_FIFO_SIZE: Size of the internal FIFO used for non-critical controller events produced by the ISR (e.g. advertising or IQ sampling reports)
 * @param USER_FIFO_SIZE: Size of the internal FIFO used for controller and host events produced outside the ISR
 */
#define BLE_STACK_TOTAL_BUFFER_SIZE_EXT(\
    BLE_STACK_NUM_LINKS,\
    BLE_STACK_NUM_EATT_CHANNELS,\
    BLE_STACK_NUM_GATT_ATTRIBUTES,\
    BLE_STACK_NUM_GATT_CLIENT_PROCS,\
    BLE_STACK_MBLOCKS_COUNT,\
    BLE_STACK_D_LEN_EXT_EN,\
    BLE_STACK_PHY_UPD_EN,\
    BLE_STACK_EXT_ADV_SCAN_EN,\
    BLE_STACK_CTRL_PRIV_EN,\
    BLE_STACK_SEC_CONN_EN,\
    BLE_STACK_SCAN_EN,\
    NUM_ADV_SET,\
    NUM_SUBEVENTS_PAWR,\
    MAX_SUBEVENT_DATA_COUNT_PAWR,\
    NUM_AUX_EVENT,\
    FILTER_ACCEPT_LIST_SIZE_LOG2,\
    BLE_STACK_L2CAP_COS_EN,\
    NUM_L2CAP_COCS,\
    CONTROLLER_PERIODIC_ADV_EN,\
    CONTROLLER_PERIODIC_ADV_WR_EN,\
    NUM_SYNC_SLOTS,\
    BLE_STACK_CTE_EN,\
    NUM_CTE_ANT_IDS,\
    NUM_CTE_IQSAMPLES,\
    BLE_STACK_PCL_EN,\
    BLE_STACK_CONN_SUPP_EN,\
    BLE_STACK_CHC_EN,\
    BLE_STACK_NUM_SYNC_BIG,\
    BLE_STACK_NUM_BRC_BIG,\
    BLE_STACK_NUM_SYNC_BIS,\
    BLE_STACK_NUM_BRC_BIS,\
    BLE_STACK_NUM_CIG,\
    BLE_STACK_NUM_CIS,\
    ISR0_FIFO_SIZE,\
    ISR1_FIFO_SIZE,\
    USER_FIFO_SIZE)\
(\
  BLE_STACK_FIXED_BUFFER_SIZE_BYTES                                                                             + \
  BLE_STACK_LINKS_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_NUM_LINKS)                                             + \
  BLE_STACK_GATT_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_NUM_GATT_ATTRIBUTES, BLE_STACK_NUM_GATT_CLIENT_PROCS,     \
                      BLE_STACK_NUM_EATT_CHANNELS)                                                              + \
  BLE_STACK_MBLOCK_SIZE(BLE_STACK_MBLOCKS_COUNT)                                                                + \
  BLE_STACK_D_LEN_EXT_SIZE(BLE_STACK_D_LEN_EXT_EN, BLE_STACK_EXT_ADV_SCAN_EN)                                   + \
  BLE_STACK_PHY_UPD_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_PHY_UPD_EN, BLE_STACK_NUM_LINKS)                     + \
  BLE_STACK_TX_BUFFER_SIZE(BLE_STACK_EXT_ADV_SCAN_EN, BLE_STACK_D_LEN_EXT_EN, BLE_STACK_NUM_SYNC_BIG,             \
                             BLE_STACK_NUM_BRC_BIG, BLE_STACK_NUM_CIG)                                          + \
  BLE_STACK_RX_BUFFER_SIZE(BLE_STACK_EXT_ADV_SCAN_EN, BLE_STACK_D_LEN_EXT_EN, BLE_STACK_NUM_SYNC_BIG,             \
                             BLE_STACK_NUM_BRC_BIG, BLE_STACK_NUM_CIG)                                          + \
  BLE_STACK_CONTROLLER_EXT_ADV_SIZE(BLE_STACK_EXT_ADV_SCAN_EN, NUM_ADV_SET, NUM_AUX_EVENT, BLE_STACK_NUM_LINKS) + \
  BLE_STACK_FILTER_ACCEPT_LIST_SIZE(FILTER_ACCEPT_LIST_SIZE_LOG2)                                               + \
  BLE_STACK_CONN_ID_LIST_SIZE(BLE_STACK_CONN_SUPP_EN, FILTER_ACCEPT_LIST_SIZE_LOG2)                             + \
  BLE_STACK_CONTROLLER_PRIV_SIZE(BLE_STACK_CTRL_PRIV_EN, FILTER_ACCEPT_LIST_SIZE_LOG2)                          + \
  (0U * (BLE_STACK_SEC_CONN_EN))                                                                                + \
  BLE_STACK_CONTROLLER_SCAN_SIZE(                                                                                 \
    BLE_STACK_SCAN_EN, BLE_STACK_EXT_ADV_SCAN_EN, CONTROLLER_PERIODIC_ADV_EN, CONTROLLER_PERIODIC_ADV_WR_EN,      \
    BLE_STACK_CONN_SUPP_EN, NUM_AUX_EVENT, NUM_SYNC_SLOTS, BLE_STACK_NUM_LINKS, FILTER_ACCEPT_LIST_SIZE_LOG2,     \
    NUM_SUBEVENTS_PAWR)                                                                                         + \
  BLE_STACK_L2C_COCS_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_L2CAP_COS_EN, NUM_L2CAP_COCS)                       + \
  BLE_STACK_CONTROLLER_PERIODIC_ADV_SIZE(                                                                         \
    CONTROLLER_PERIODIC_ADV_EN, CONTROLLER_PERIODIC_ADV_WR_EN, BLE_STACK_CONN_SUPP_EN,                            \
    BLE_STACK_NUM_LINKS, NUM_ADV_SET, NUM_SUBEVENTS_PAWR, MAX_SUBEVENT_DATA_COUNT_PAWR)                         + \
  BLE_STACK_CTE_SIZE(                                                                                             \
    BLE_STACK_SCAN_EN, BLE_STACK_EXT_ADV_SCAN_EN, CONTROLLER_PERIODIC_ADV_EN, BLE_STACK_CONN_SUPP_EN,             \
    BLE_STACK_CTE_EN, BLE_STACK_NUM_LINKS, NUM_CTE_ANT_IDS, NUM_CTE_IQSAMPLES)                                  + \
  BLE_STACK_PCL_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_PCL_EN, BLE_STACK_NUM_LINKS)                             + \
  BLE_STACK_CHC_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_CHC_EN, BLE_STACK_NUM_LINKS)                             + \
  BLE_STACK_ISO_SIZE(BLE_STACK_NUM_BRC_BIG, BLE_STACK_NUM_BRC_BIS,                                                \
                     BLE_STACK_NUM_SYNC_BIG, BLE_STACK_NUM_SYNC_BIS,                                              \
                     BLE_STACK_NUM_CIG, BLE_STACK_NUM_CIS)                                                      + \
  BLE_STACK_FIFO_SIZE(ISR0_FIFO_SIZE, ISR1_FIFO_SIZE, USER_FIFO_SIZE)                                             \
)

/**
 *
 * This macro acts like the BLE_STACK_TOTAL_BUFFER_SIZE_EXT macro while makes use of the
 * modularity parameters defined in the app_conf.h file
 *
 * @param BLE_STACK_NUM_LINKS: Maximum number of simultaneous radio tasks that the device will support (Radio controller supports up to 128 simultaneous radio tasks, but actual usable max value depends
on the available device RAM)
 * @param BLE_STACK_NUM_EATT_CHANNELS: Maximum number of simultaneous EATT active channels that the device will support.
 * @param BLE_STACK_NUM_GATT_ATTRIBUTES: Maximum number of Attributes (i.e. the number of characteristic + the number of characteristic values + the number of descriptors, excluding the services) that can be stored in the GATT database. Note that certain characteristics and relative descriptors are added automatically during device initialization so this parameters should be 9 plus the number of user Attributes
 * @param BLE_STACK_NUM_GATT_CLIENT_PROCS: Maximum number of concurrent GATT Client Procedures.
 * @param BLE_STACK_MBLOCKS_COUNT: Number of memory blocks allocated for packets.
 * @param BLE_STACK_NUM_ADV_SET: Number of advertising sets.
 * @param BLE_STACK_NUM_ADV_SET_PAWR: Number of advertising sets for periodic advertising with responses.
 * @param BLE_STACK_NUM_SUBEVENTS_PAWR: Number of periodic advertising with responses subevents.
 * @param BLE_STACK_SUBEVENT_DATA_COUNT_PAWR: Maximum number of periodic advertising with responses subevents that data can be requested for
 * @param BLE_STACK_NUM_AUX_EVENT: Number of auxiliary scan slots.
 * @param BLE_STACK_FILTER_ACCEPT_LIST_SIZE_LOG2: log2 ceiling of Filter Accept List size.
 * @param BLE_STACK_NUM_L2CAP_COCS: number of L2CAP Connection Oriented Channels supported.
 * @param NUM_SYNC_SLOTS: Number of radio tasks to allocate for synchronizing to periodic advertisements.
 * @param BLE_STACK_NUM_CTE_ANT_IDS: Maximum antenna switching pattern length .
 * @param BLE_STACK_NUM_IQSAMPLES: Maximum number of IQ-Samples in the buffer.
 * @param ISR0_FIFO_SIZE: Size of the internal FIFO used for critical controller events produced by the ISR (e.g. rx data packets).
 * @param ISR1_FIFO_SIZE: Size of the internal FIFO used for non-critical controller events produced by the ISR (e.g. advertising or IQ sampling reports).
 * @param USER_FIFO_SIZE: Size of the internal FIFO used for controller and host events produced outside the ISR.
 */
#define BLE_STACK_TOTAL_BUFFER_SIZE(\
    BLE_STACK_NUM_LINKS,\
    BLE_STACK_NUM_EATT_CHANNELS,\
    BLE_STACK_NUM_GATT_ATTRIBUTES,\
    BLE_STACK_NUM_GATT_CLIENT_PROCS,\
    BLE_STACK_MBLOCKS_COUNT,\
    BLE_STACK_NUM_ADV_SET,\
    BLE_STACK_NUM_SUBEVENTS_PAWR,\
    BLE_STACK_SUBEVENT_DATA_COUNT_PAWR,\
    BLE_STACK_NUM_AUX_EVENT,\
    BLE_STACK_FILTER_ACCEPT_LIST_SIZE_LOG2,\
    BLE_STACK_NUM_L2CAP_COCS,\
    NUM_SYNC_SLOTS,\
    BLE_STACK_NUM_CTE_ANT_IDS,\
    BLE_STACK_NUM_IQSAMPLES,\
    BLE_STACK_NUM_SYNC_BIG,\
    BLE_STACK_NUM_BRC_BIG,\
    BLE_STACK_NUM_SYNC_BIS,\
    BLE_STACK_NUM_BRC_BIS,\
    BLE_STACK_NUM_CIG,\
    BLE_STACK_NUM_CIS,\
    ISR0_FIFO_SIZE,\
    ISR1_FIFO_SIZE,\
    USER_FIFO_SIZE)\
(\
    BLE_STACK_TOTAL_BUFFER_SIZE_EXT(\
        BLE_STACK_NUM_LINKS,\
        BLE_STACK_NUM_EATT_CHANNELS,\
        BLE_STACK_NUM_GATT_ATTRIBUTES,\
        BLE_STACK_NUM_GATT_CLIENT_PROCS,\
        BLE_STACK_MBLOCKS_COUNT,\
        CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED,\
        CONTROLLER_2M_CODED_PHY_ENABLED,\
        CONTROLLER_EXT_ADV_SCAN_ENABLED,\
        CONTROLLER_PRIVACY_ENABLED,\
        SECURE_CONNECTIONS_ENABLED,\
        CONTROLLER_SCAN_ENABLED,\
        BLE_STACK_NUM_ADV_SET,\
        BLE_STACK_NUM_SUBEVENTS_PAWR,\
        BLE_STACK_SUBEVENT_DATA_COUNT_PAWR,\
        BLE_STACK_NUM_AUX_EVENT,\
        BLE_STACK_FILTER_ACCEPT_LIST_SIZE_LOG2,\
        L2CAP_COS_ENABLED,\
        BLE_STACK_NUM_L2CAP_COCS,\
        CONTROLLER_PERIODIC_ADV_ENABLED,\
        CONTROLLER_PERIODIC_ADV_WR_ENABLED,\
        NUM_SYNC_SLOTS,\
        CONTROLLER_CTE_ENABLED,\
        BLE_STACK_NUM_CTE_ANT_IDS,\
        BLE_STACK_NUM_IQSAMPLES,\
        CONTROLLER_POWER_CONTROL_ENABLED,\
        CONNECTION_ENABLED,\
        CONTROLLER_CHAN_CLASS_ENABLED,\
        BLE_STACK_NUM_SYNC_BIG,\
        BLE_STACK_NUM_BRC_BIG,\
        BLE_STACK_NUM_SYNC_BIS,\
        BLE_STACK_NUM_BRC_BIS,\
        BLE_STACK_NUM_CIG,\
        BLE_STACK_NUM_CIS,\
        ISR0_FIFO_SIZE,\
        ISR1_FIFO_SIZE,\
        USER_FIFO_SIZE\
))

/**
*
* This structure contains memory and low level hardware configuration data for the device
*/
typedef struct {
  uint8_t* BLEStartRamAddress;      /**< Start address of the RAM buffer required by the Bluetooth stack. It must be 32-bit aligned. Use BLE_STACK_TOTAL_BUFFER_SIZE to calculate the correct size. */
  uint32_t TotalBufferSize;         /**< BLE_STACK_TOTAL_BUFFER_SIZE return value, used to check the MACRO correctness*/
  uint16_t NumAttrRecords;          /**< Maximum number of attributes that can be stored in the GATT database. */
  uint8_t MaxNumOfClientProcs;      /**< Maximum number of concurrent client's procedures. This value shall be less or equal to NumOfRadioTasks. */
  uint8_t NumOfRadioTasks;          /**< Maximum number of simultaneous radio tasks. Radio controller supports up to 128 simultaneous radio tasks, but actual usable max value depends on the available device RAM (NUM_LINKS used in the calculation of BLE_STACK_TOTAL_BUFFER_SIZE). */
  uint8_t NumOfEATTChannels;        /**< Maximum number of simultaneous EATT active channels */
  uint16_t NumBlockCount;           /**< Number of allocated memory blocks */
  uint16_t ATT_MTU;                 /**< Maximum supported ATT_MTU size [23-1020]*/
  uint32_t MaxConnEventLength;      /**< Maximum duration of the connection event when the device is peripheral, in units of 625/256 us (~2.44 us) */
  uint16_t SleepClockAccuracy;      /**< Sleep clock accuracy (ppm value)*/
  uint8_t NumOfAdvDataSet;          /**< Maximum number of advertising data sets, valid only when Advertising Extension Feature is enabled  */
  uint8_t NumOfSubeventsPAwR;       /**< Maximum number of Periodic Advertising with Responses subevents */
  uint8_t MaxPAwRSubeventDataCount; /**< Maximum number of Periodic Advertising with Responses subevents that data can be requested for */
  uint8_t NumOfAuxScanSlots;        /**< Maximum number of slots for scanning on the secondary advertising channel, valid only when Advertising Extension Feature is enabled  */
  uint8_t NumOfSyncSlots;           /**< Maximum number of slots for synchronizing to a periodic advertising train, valid only when Periodic Advertising and Synchronizing Feature is enabled  */
  uint8_t FilterAcceptListSizeLog2; /**< Two's logarithm of Filter Accept, Resolving and advertiser list size. */
  uint16_t L2CAP_MPS;               /**< The maximum size of payload data in octets that the L2CAP layer entity is capable of accepting [0-1024].*/
  uint8_t L2CAP_NumChannels;        /**< Maximum number of channels in LE Credit Based Flow Control mode [0-255].*/
  uint8_t CTE_MaxNumAntennaIDs;     /**< Maximum number of Antenna IDs in the antenna pattern used in CTE connection oriented mode. */
  uint8_t CTE_MaxNumIQSamples;      /**< Maximum number of IQ samples in the buffer used in CTE connection oriented mode. */
  uint8_t NumOfSyncBIG;             /**< Maximum number of ISO Synchronizer groups. */
  uint8_t NumOfBrcBIG;              /**< Maximum number of ISO Broadcaster groups. */
  uint8_t NumOfSyncBIS;             /**< Maximum number of ISO Synchronizer streams. */
  uint8_t NumOfBrcBIS;              /**< Maximum number of ISO Broadcaster streams. */
  uint8_t NumOfCIG;                 /**< Maximum number of Connected Isochronous Groups. */
  uint8_t NumOfCIS;                 /**< Maximum number of Connected Isochronous Streams. */
  uint16_t isr0_fifo_size;          /**< Size of the internal FIFO used for critical controller events produced by the ISR (e.g. rx data packets)*/
  uint16_t isr1_fifo_size;          /**< Size of the internal FIFO used for non-critical controller events produced by the ISR (e.g. advertising or IQ sampling reports)*/
  uint16_t user_fifo_size;          /**< Size of the internal FIFO used for controller and host events produced outside the ISR */
} BLE_STACK_InitTypeDef;


/**
 * @brief This function executes the processing of all Host Stack layers.
 *
 * The BLE Stack Tick function has to be executed regularly to process incoming Link Layer packets and to process Host Layers procedures. All
 * stack callbacks are called by this function.
 *
 * If Low Speed Ring Oscillator is used instead of the LS Crystal oscillator this function performs also the LS RO calibration and hence must
 * be called at least once at every system wake-up in order to keep the 500 ppm accuracy (at least 500 ppm accuracy is mandatory if acting as a Central).
 *
 * No BLE stack function must be called while the BLE_STACK_Tick is running. For example, if a BLE stack function may be called inside an
 * interrupt routine, that interrupt must be disabled during the execution of BLE_STACK_Tick(). Example (if a stack function may be called inside
 * UART ISR):
 * @code
 * NVIC_DisableIRQ(UART_IRQn);
 * BLE_STACK_Tick();
 * NVIC_EnableIRQ(UART_IRQn);
 * @endcode

 * @note The API name and parameters are subject to change in future releases.
 * @return None
 */
void BLE_STACK_Tick(void);

/**
 * @brief The BLE Stack initialization routine
 *
 * @note The API name and parameters are subject to change in future releases.
 *
 * @param[in]  BLE_STACK_InitStruct      pointer to the const structure containing memory and low level
 *                                              hardware configuration data for the device
 *
 * @return Value indicating success or error code.
 *
 */
tBleStatus BLE_STACK_Init(const BLE_STACK_InitTypeDef *BLE_STACK_InitStruct);

/**
 * @brief This function is called when an event is coming from the BLE stack
 *
 * @param  hci_pckt: The user event received from the BLE stack
 * @param  length:   Length of the event
 * @retval None
 */
void BLE_STACK_Event(hci_pckt *hci_pckt, uint16_t length);


/**
 * @brief Returns the BLE Stack matching sleep mode
 *
 * @note The API name and parameters are subject to change in future releases.
 *
 * @return
 *  SLEEPMODE_RUNNING       = 0,
 *  SLEEPMODE_NOTIMER       = 3,
 */
uint8_t BLE_STACK_SleepCheck(void);

/**
 *
 * @brief Radio ISR routine.
 *
 * This is the base function called for any radio ISR.
 *
 * @param[in]  BlueInterrupt    value of the radio interrupt register
 *
 * @return None
 */
void BLE_STACK_RadioHandler(uint32_t BlueInterrupt);

/**
  * @brief This function provide information when a new radio activity will be performed.
Information provided includes type of radio activity and absolute time in system ticks when a new radio activity is schedule, if any.
  * @param NextStateSysTime 32bit absolute current time expressed in internal time units.
  * @retval Value indicating the next state:
  - 0x00: Idle
  - 0x01: Advertising
  - 0x02: Connection event Peripheral
  - 0x03: Scanning
  - 0x04: Connection request
  - 0x05: Connection event Central
  - 0x06: TX test mode
  - 0x07: RX test mode
  */
uint8_t BLE_STACK_ReadNextRadioActivity(uint32_t *NextStateSysTime);

/* Statistics per link */
typedef struct llc_conn_per_statistic_s {

    uint16_t num_pkts;          /**< The number of received packets, valid or with CRC errors. */
    uint16_t num_crc_err;       /**< The number of packets received with CRC errors. */
    uint16_t num_evts;          /**< The number of past connection events, including missed ones. */
    uint16_t num_miss_evts;     /**< The number of missed RX packets, because of RX timeout or invalid packet length. */

} llc_conn_per_statistic_st;

/**
 * @brief     LLC function to collect statistics per link:
 *             - statistics are stored in a buffer allocated by the application
 *             - counters are reset every time the function is called
 *             - counters are stopped when the function is called with a pointer to NULL
 *
 * @param[in] conn_handle Connection handle that identifies the connection
 * @param[in] statistics_p pointer to the structure where statistics will be noted
 * @return    BLE_ERROR_UNKNOWN_CONNECTION_ID in case of invalid conn_handle
 *            BLE_STATUS_SUCCESS otherwise
 */
tBleStatus llc_conn_per_statistic(uint16_t conn_handle,
                                  llc_conn_per_statistic_st *statistics_p);


/* Statistics per link and per channel */
#if !defined(LLC_MAX_NUM_DATA_CHAN)
#   define LLC_MAX_NUM_DATA_CHAN (37U)
#endif

typedef struct llc_conn_per_statistic_by_channel_s {
    uint16_t num_pkts[LLC_MAX_NUM_DATA_CHAN];              /**< The number of received packets, valid or with CRC errors. */
    uint16_t num_crc_err[LLC_MAX_NUM_DATA_CHAN];           /**< The number of packets received with CRC errors. */
    uint16_t num_miss_evts[LLC_MAX_NUM_DATA_CHAN];         /**< The number of missed RX events, because of RX timeout or invalid packet length. */
} llc_conn_per_statistic_by_channel_st;

/**
 * @brief     LLC function to collect statistics per link and per channel:
 *             - statistics are stored in a buffer allocated by the application
 *             - counters are reset every time the function is called
 *             - counters are stopped when the function is called with a pointer to NULL
 *
 * @param[in] conn_handle - connection handle that identifies the connection
 * @param[in] statistics_p - pointer to the structure where statistics will be noted
 * @return    BLE_ERROR_UNKNOWN_CONNECTION_ID in case of invalid conn_handle
 *            BLE_STATUS_SUCCESS otherwise
 */
tBleStatus llc_conn_per_statistic_by_channel(uint16_t conn_handle,
                                             llc_conn_per_statistic_by_channel_st *statistics_p);


#endif /* BLE_STACK_H */

