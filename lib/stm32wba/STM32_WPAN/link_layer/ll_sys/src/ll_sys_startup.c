/**
  ******************************************************************************
  * @file    ll_sys_startup.c
  * @author  MCD Application Team
  * @brief   Link Layer IP system interface startup module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "ll_fw_config.h"
#include "ll_sys.h"
#include "ll_intf.h"
#include "ll_sys_startup.h"
#include "ll_intf_cmn.h"
#include "common_types.h"

#if defined(CONFIG_NET_L2_CUSTOM_IEEE802154_STM32WBA)
#if defined(MAC)
#ifndef OPENTHREAD_CONFIG_FILE
/* Projects with MAC Layer (i.e. 15.4 except Thread) */
#include "st_mac_802_15_4_sap.h"
#endif /* OPENTHREAD_CONFIG_FILE */
#endif /* MAC */
#endif /* CONFIG_NET_L2_CUSTOM_IEEE802154_STM32WBA */

static void ll_init(void);

#if SUPPORT_BLE
static uint8_t num_sm = 0;
static int8_t *ll_mem_buffer = NULL;
static uint16_t ll_mem_size = 0;
static uint32_t ll_feature_supported = 0;
#endif /* SUPPORT_BLE */

static void ll_sys_dependencies_init(void);
#if SUPPORT_BLE

/**
  * @brief  Initialize the Link Layer IP BLE controller
  * @param  None
  * @retval None
  */
void ll_sys_ble_cntrl_init(hst_cbk hostCallback,
                           hst_cbk_queue_full eventMissedCallback,
                           uint8_t num_sm_needed,
                           int8_t *ll_memory_buffer,
                           uint16_t ll_memory_buffer_size,
                           uint32_t supported_feature
                           )
{
  num_sm = num_sm_needed;
  ll_mem_buffer = ll_memory_buffer;
  ll_mem_size = ll_memory_buffer_size;
  ll_feature_supported = supported_feature;

  /* Only initilize if sleep timer is not initialized*/
  if(ll_intf_cmn_get_slptmr_state())
    return;

  ll_init();

  ll_intf_rgstr_hst_cbk(hostCallback);

  ll_intf_rgstr_hst_cbk_ll_queue_full( eventMissedCallback );
}
#endif /* SUPPORT_BLE */

#if defined(CONFIG_NET_L2_CUSTOM_IEEE802154_STM32WBA)
#if defined(MAC)
#ifndef OPENTHREAD_CONFIG_FILE
/**
  * @brief  Initialize the Link Layer IP 802.15.4 MAC controller
  * @param  None
  * @retval None
  */
void ll_sys_mac_cntrl_init(void)
{
  ST_MAC_preInit();
#if SUPPORT_BLE
  /* Only initilize if sleep timer is not initialized*/
  if(ll_intf_cmn_get_slptmr_state())
    return;
#endif

  ll_init();
}
#endif /* OPENTHREAD_CONFIG_FILE */
#endif /* MAC */
#endif /* CONFIG_NET_L2_CUSTOM_IEEE802154_STM32WBA */
/**
  * @brief  Start the Link Layer IP in OpenThread configuration
  * @param  None
  * @retval None
  */
void ll_sys_thread_init(void)
{
#if SUPPORT_BLE
  /* Only initilize if sleep timer is not initialized*/
  if(ll_intf_cmn_get_slptmr_state())
    return;
#endif
  ll_init();
}

/**
  * @brief  Initialize the Link Layer resources for startup.
  *         This includes: - Deep Sleep feature resources
  *                        - Link Layer background task
  * @param  None
  * @retval None
  */
static void ll_sys_dependencies_init(void)
{

  ll_sys_status_t dp_slp_status;

  /* Deep sleep feature initialization */
  dp_slp_status = ll_sys_dp_slp_init();
  ll_sys_assert(dp_slp_status == LL_SYS_OK);

  /* Background task initialization */
  ll_sys_bg_process_init();

  /* Link Layer user parameters application */
  ll_sys_config_params();
}

/**
  * @brief  Initialize the Link Layer IP BLE/802.15.4 MAC controller
  * @param  None
  * @retval None
  */
static void ll_init(void)
{
#if SUPPORT_BLE
  const struct hci_dispatch_tbl* p_hci_dis_tbl = NULL;
#endif /* SUPPORT_BLE */

#if SUPPORT_BLE
  hci_get_dis_tbl( &p_hci_dis_tbl );
  ll_intf_init(p_hci_dis_tbl,
    num_sm,
    ll_mem_buffer,
    ll_mem_size,
    ll_feature_supported
  );

#endif /* SUPPORT_BLE */


  ll_sys_dependencies_init();
}

__WEAK void ll_sys_handle_missed_event_cb(uint16_t length,
                                          uint8_t* data)
{

}
