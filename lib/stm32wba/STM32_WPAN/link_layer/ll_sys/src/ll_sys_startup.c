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
static void ll_sys_dependencies_init(void);
#if SUPPORT_BLE
static void ll_sys_event_missed_cb( ble_buff_hdr_t* ptr_evnt_hdr )
{
  if (( ptr_evnt_hdr != NULL ) && (ptr_evnt_hdr->data_size >= 2)
      && (ptr_evnt_hdr->ble_hdr_flags == BLE_BUFF_HDR_EVNT_CMD_PCKT))
  {
    uint8_t *event_data = ptr_evnt_hdr->buff_start + ptr_evnt_hdr->data_offset;
    ll_sys_handle_missed_event_cb(event_data[1],
                                  event_data);
  }
}

/**
  * @brief  Initialize the Link Layer IP BLE controller
  * @param  None
  * @retval None
  */
void ll_sys_ble_cntrl_init(hst_cbk hostCallback)
{
  ll_init();

  ll_intf_rgstr_hst_cbk(hostCallback);

  ll_intf_rgstr_hst_cbk_ll_queue_full( ll_sys_event_missed_cb );
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
  static uint8_t is_ll_initialized = 0;
#if SUPPORT_BLE
  const struct hci_dispatch_tbl* p_hci_dis_tbl = NULL;
#endif /* SUPPORT_BLE */

  /* Ensure Link Layer resources are created only once */
  if (is_ll_initialized == 1) {
    return;
  }
  is_ll_initialized = 1;

#if SUPPORT_BLE
  hci_get_dis_tbl( &p_hci_dis_tbl );

  ll_intf_init(p_hci_dis_tbl);
#endif /* SUPPORT_BLE */


  ll_sys_dependencies_init();
}

__WEAK void ll_sys_handle_missed_event_cb(uint16_t length,
                                          uint8_t* data)
{

}
