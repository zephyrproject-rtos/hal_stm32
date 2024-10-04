
/**
  ******************************************************************************
  * @file    stack_user_cfg.c
  * @author  GPM WBL Application Team
  * @brief   BLE stack modular configuration options file
  * @details BLE_Config BLE stack configuration options
  *  - The BLE stack v4.0 or later supports the following outstanding features:
  *    -- Controller Privacy
  *    -- LE Secure Connections
  *    -- Controller Scan
  *    -- Controller Data Length Extension
  *    -- LE 2M/Coded PHY
  *    -- Extended Advertising
  *    -- Periodic Advertising and Synchronizer
  *    -- Periodic Advertising with Responses
  *    -- L2CAP Connection Oriented Channels
  *    -- Constant Tone Extension
  *    -- Power Control & Path Loss Monitoring
  *    -- Connection Support
  *    -- LE Channel Classification
  *    -- Broadcast Isochronous Streams
  *    -- Connected Isochronous Streams
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


#include "ble_stack_user_cfg.h"

/* check whether all the configuration flag macros are defined */
#if !defined(CFG_BLE_CONTROLLER_PRIVACY_ENABLED)
#   error "CFG_BLE_CONTROLLER_PRIVACY_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_SECURE_CONNECTIONS_ENABLED)
#   error "CFG_BLE_SECURE_CONNECTIONS_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_SCAN_ENABLED)
#   error "CFG_BLE_CONTROLLER_SCAN_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED)
#   error "CFG_BLE_CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_2M_CODED_PHY_ENABLED)
#   error "CFG_BLE_CONTROLLER_2M_CODED_PHY_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED)
#   error "CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_L2CAP_COS_ENABLED)
#   error "CFG_BLE_L2CAP_COS_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED)
#   error "CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_CTE_ENABLED)
#   error "CFG_BLE_CONTROLLER_CTE_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_POWER_CONTROL_ENABLED)
#   error "CFG_BLE_CONTROLLER_POWER_CONTROL_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONNECTION_ENABLED)
#   error "CFG_BLE_CONNECTION_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_CHAN_CLASS_ENABLED)
#   error "CFG_BLE_CONTROLLER_CHAN_CLASS_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_BIS_ENABLED)
#   error "CFG_BLE_CONTROLLER_BIS_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONNECTION_SUBRATING_ENABLED)
#   error "CFG_BLE_CONNECTION_SUBRATING_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_CIS_ENABLED)
#   error "(CFG_BLE_CONTROLLER_CIS_ENABLED is not defined"
#endif
#if !defined(CONTROLLER_ISO_ENABLED)
#   error "CONTROLLER_ISO_ENABLED is not defined"
#endif
#if !defined(CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED)
#   error "CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED is not defined"
#endif

/* check whether all the dependencies between the configuration flag macros are met */
#if (SECURE_CONNECTIONS_ENABLED == 1) && \
    (CONNECTION_ENABLED == 0)
#   error "SECURE_CONNECTIONS_ENABLED cannot be 1"
#endif
#if (L2CAP_COS_ENABLED == 1) && \
    (CONNECTION_ENABLED == 0)
#   error "L2CAP_COS_ENABLED cannot be 1"
#endif
#if (CONTROLLER_PERIODIC_ADV_ENABLED == 1) && \
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 0)
#   error "CONTROLLER_PERIODIC_ADV_ENABLED cannot be 1"
#endif
#if (CONTROLLER_POWER_CONTROL_ENABLED == 1) && \
    (CONNECTION_ENABLED == 0)
#   error "CONTROLLER_POWER_CONTROL_ENABLED cannot be 1"
#endif
#if (CONTROLLER_CHAN_CLASS_ENABLED == 1) && \
    (CONNECTION_ENABLED == 0)
#   error "CONTROLLER_CHAN_CLASS_ENABLED cannot be 1"
#endif
#if (CONTROLLER_BIS_ENABLED == 1) && \
   ((CONTROLLER_EXT_ADV_SCAN_ENABLED == 0) || \
    (CONTROLLER_PERIODIC_ADV_ENABLED == 0) || \
    (CONTROLLER_ISO_ENABLED == 0))
#   error "CONTROLLER_BIS_ENABLED cannot be 1"
#endif
#if (CONNECTION_SUBRATING_ENABLED == 1) && \
    (CONNECTION_ENABLED == 0)
#   error "CONNECTION_SUBRATING_ENABLED cannot be 1"
#endif
#if (CONTROLLER_CIS_ENABLED == 1) && \
   ((CONNECTION_ENABLED == 0) || \
    (CONTROLLER_ISO_ENABLED == 0))
#   error "CONTROLLER_CIS_ENABLED cannot be 1"
#endif
#if (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1) && \
   ((CONTROLLER_EXT_ADV_SCAN_ENABLED == 0) || \
    (CONTROLLER_PERIODIC_ADV_ENABLED == 0) || \
    (CONNECTION_ENABLED == 0))
#   error "CONTROLLER_PERIODIC_ADV_WR_ENABLED cannot be 1"
#endif


/*
* *****************************************************************************
*                      BLE Stack INTERNAL core functions
* *****************************************************************************
*/

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_advertising_configuration_ucfg(uint8_t Advertising_Handle,
                                                  uint8_t Discoverability_Mode,
                                                  uint16_t Advertising_Event_Properties,
                                                  uint32_t Primary_Advertising_Interval_Min,
                                                  uint32_t Primary_Advertising_Interval_Max,
                                                  uint8_t Primary_Advertising_Channel_Map,
                                                  uint8_t Peer_Address_Type,
                                                  uint8_t Peer_Address[6],
                                                  uint8_t Advertising_Filter_Policy,
                                                  int8_t Advertising_Tx_Power,
                                                  uint8_t Primary_Advertising_PHY,
                                                  uint8_t Secondary_Advertising_Max_Skip,
                                                  uint8_t Secondary_Advertising_PHY,
                                                  uint8_t Advertising_SID,
                                                  uint8_t Scan_Request_Notification_Enable)
{
    return GAP_set_extended_advertising_configuration(Advertising_Handle,
                                                      Discoverability_Mode,
                                                      Advertising_Event_Properties,
                                                      Primary_Advertising_Interval_Min,
                                                      Primary_Advertising_Interval_Max,
                                                      Primary_Advertising_Channel_Map,
                                                      Peer_Address_Type,
                                                      Peer_Address,
                                                      Advertising_Filter_Policy,
                                                      Advertising_Tx_Power,
                                                      Primary_Advertising_PHY,
                                                      Secondary_Advertising_Max_Skip,
                                                      Secondary_Advertising_PHY,
                                                      Advertising_SID,
                                                      Scan_Request_Notification_Enable);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_scan_response_data_ucfg(uint8_t Advertising_Handle,
                                           uint16_t Scan_Response_Data_Length,
                                           uint8_t* Scan_Response_Data)
{
    return GAP_set_extended_scan_response_data(Advertising_Handle,
                                               Scan_Response_Data_Length,
                                               Scan_Response_Data);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_advertising_data_ucfg(uint8_t Advertising_Handle,
                                         uint8_t Operation,
                                         uint16_t Advertising_Data_Length,
                                         uint8_t* Advertising_Data)
{
    return GAP_set_extended_advertising_data(Advertising_Handle,
                                             Operation,
                                             Advertising_Data_Length,
                                             Advertising_Data);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_advertising_enable_ucfg(uint8_t Enable,
                                           uint8_t Num_Of_Sets,
                                           Advertising_Set_Parameters_t* Advertising_Set_Parameters)
{
    return GAP_set_extended_advertising_enable(Enable,
                                               Num_Of_Sets,
                                               Advertising_Set_Parameters);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus GAP_create_connection_ucfg(uint8_t* peer_address,
                                      uint8_t peer_address_type,
                                      uint8_t own_address_type,
                                      uint8_t initiator_filter_policy,
                                      uint8_t phys)
{
    return GAP_create_connection_ext(peer_address,
                                     peer_address_type,
                                     own_address_type,
                                     initiator_filter_policy,
                                     phys);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_scan_parameters_ucfg(uint8_t own_address_type,
                                        uint8_t phys)
{
    return GAP_set_scan_parameters_ext(own_address_type,
                                       phys);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_enable_disable_scan_ucfg(uint8_t enable,
                                        uint8_t duplicate_filtering)
{
    return GAP_enable_disable_scan_ext(enable,
                                       duplicate_filtering);
}
#else
tBleStatus GAP_enable_disable_scan_ucfg(uint8_t enable,
                                        uint8_t duplicate_filtering)
{
    return GAP_enable_disable_scan_legacy(enable,
                                          duplicate_filtering);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus GAP_connection_procedure_ucfg(uint8_t procedure_code,
                                         uint8_t phys,
                                         uint8_t peer_address_type,
                                         uint8_t peer_address[6])
{
    return GAP_connection_procedure(procedure_code,
                                    phys,
                                    peer_address_type,
                                    peer_address);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus GAP_terminate_gap_procedure_ucfg(uint8_t procedure_code)
{
    return GAP_terminate_gap_procedure(procedure_code);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus GAP_discover_peer_name_ucfg(void)
{
    return GAP_discover_peer_name();
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void GAP_name_disc_proc_connected_check_ucfg(uint16_t task_idx)
{
    GAP_name_disc_proc_connected_check(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
void GAP_central_connection_complete_handler_ucfg(uint8_t status,
                                                  uint16_t connectionHandle)
{
    GAP_central_connection_complete_handler(status,
                                            connectionHandle);
}
#endif
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
uint8_t GAP_parse_connectable_advertising_report_ucfg(uint8_t* adv_buf,
                                                   uint8_t extended)
{
    return GAP_parse_connectable_advertising_report(adv_buf,
                                                    extended);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1)
uint8_t GAP_parse_advertising_report_ucfg(uint8_t* adv_buf,
                                       uint8_t extended)
{
    return GAP_parse_advertising_report(adv_buf,
                                        extended);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void GAP_DiscProcTimeoutcb_ucfg(uint8_t timer_id)
{
    GAP_DiscProcTimeoutcb(timer_id);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void GAP_LimDiscTimeoutcb_ucfg(uint8_t timer_id)
{
    GAP_LimDiscTimeoutcb(timer_id);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void GAP_hci_le_advertising_set_terminated_evt_hndl_ucfg(uint8_t status,
                                                         uint8_t Advertising_Handle)
{
    GAP_hci_le_advertising_set_terminated_evt_hndl(status,
                                                   Advertising_Handle);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void GAP_peripheral_connection_complete_handler_ucfg(uint16_t connectionHandle)
{
    GAP_peripheral_connection_complete_handler(connectionHandle);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus GAP_enable_controller_privacy_ucfg(uint8_t* gapRole,
                                              uint8_t* numServiceRec)
{
    return GAP_enable_controller_privacy(gapRole,
                                         numServiceRec);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus GAP_add_device_to_filter_accept_and_resolving_list_ucfg(uint8_t lists,
                                                                   uint8_t addr_type,
                                                                   uint8_t addr[6])
{
    return GAP_add_device_to_filter_accept_and_resolving_list_full(lists,
                                                                   addr_type,
                                                                   addr);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus GAP_clear_filter_accept_and_resolving_list_ucfg(uint8_t lists)
{
    return GAP_clear_filter_accept_and_resolving_list_full(lists);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_set_controller_random_address_ucfg(uint8_t random_address[6])
{
    return GAP_set_controller_random_address_extended(random_address);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_init_advertising_sets_ucfg(uint8_t own_address_type)
{
    return GAP_init_advertising_sets(own_address_type);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus GAP_suspend_resume_active_advertising_sets_ucfg(uint8_t resume)
{
    return GAP_suspend_resume_active_advertising_sets_extended(resume);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void GAP_ResumeAdvertising_ucfg(uint16_t task_idx)
{
    GAP_ResumeAdvertising(task_idx);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_acl_data_tx_cmpl_event_int_cb_ucfg(void* header_p,
                                                  uint8_t* buff_p)
{
    return hci_acl_data_tx_cmpl_event_int_cb(header_p,
                                             buff_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_acl_data_ind_event_int_cb_ucfg(void* header_p,
                                              uint8_t* buff_p)
{
    return hci_acl_data_ind_event_int_cb(header_p,
                                         buff_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint32_t chc_csr_ucfg(void)
{
    return chc_csr();
}
#endif /* ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (CONNECTION_ENABLED == 1)
void Controller_Process_Q_ucfg(uint16_t task_idx)
{
    Controller_Process_Q(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
void LLC_offline_control_procedures_processing_ucfg(uint16_t task_idx)
{
    LLC_offline_control_procedures_processing(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
uint32_t cte_csr_ucfg(void)
{
    return cte_csr();
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
uint8_t hci_le_check_own_address_type_max_value_ucfg(void)
{
    return hci_le_check_own_address_type_max_value();
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1)
uint32_t data_length_extension_csr_ucfg(void)
{
    return data_length_extension_csr();
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint32_t pcl_csr_ucfg(void)
{
    return pcl_csr();
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
uint32_t phy_upd_csr_ucfg(void)
{
    return phy_upd_csr();
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1)
uint32_t scan_csr_ucfg(void)
{
    return scan_csr();
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
uint32_t conn_supp_csr_ucfg(void)
{
    return conn_supp_csr();
}
#endif /* (CONNECTION_ENABLED == 1) */

#if ((CONNECTION_SUBRATING_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint32_t subrate_csr_ucfg(void)
{
    return subrate_csr();
}
#endif /* ((CONNECTION_SUBRATING_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus LLC_test_check_cte_params_ucfg(void* params)
{
    return LLC_test_check_cte_params(params);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus ACL_pkt_init_ucfg(void)
{
    return ACL_pkt_init();
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_disconnection_complete_event_int_cb_ucfg(void* header_p,
                                                        uint8_t* buff_p)
{
    return hci_disconnection_complete_event_int_cb(header_p,
                                                   buff_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_encryption_change_event_int_cb_ucfg(void* header_p,
                                                   uint8_t* buff_p)
{
    return hci_encryption_change_event_int_cb(header_p,
                                              buff_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_encryption_key_refresh_complete_event_int_cb_ucfg(void* header_p,
                                                                 uint8_t* buff_p)
{
    return hci_encryption_key_refresh_complete_event_int_cb(header_p,
                                                            buff_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_connection_complete_event_int_cb_ucfg(void* header_p,
                                                        uint8_t* buff_p)
{
    return hci_le_connection_complete_event_int_cb(header_p,
                                                   buff_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_enhanced_connection_complete_event_int_cb_ucfg(void* header_p,
                                                                 uint8_t* buff_p)
{
    return hci_le_enhanced_connection_complete_event_int_cb(header_p,
                                                            buff_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_long_term_key_request_event_int_cb_ucfg(void* header_p,
                                                          uint8_t* buff_p)
{
    return hci_le_long_term_key_request_event_int_cb(header_p,
                                                     buff_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_read_local_p256_public_key_complete_event_int_cb_ucfg(void* header_p,
                                                                        uint8_t* buff_p)
{
    return hci_le_read_local_p256_public_key_complete_event_int_cb(header_p,
                                                                   buff_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_generate_dhkey_complete_event_int_cb_ucfg(void* header_p,
                                                            uint8_t* buff_p)
{
    return hci_le_generate_dhkey_complete_event_int_cb(header_p,
                                                       buff_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_advertising_report_event_int_cb_ucfg(void* header_p,
                                                       uint8_t* buff_p)
{
    return hci_le_advertising_report_event_int_cb(header_p,
                                                  buff_p);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_directed_advertising_report_event_int_cb_ucfg(void* header_p,
                                                                uint8_t* buff_p)
{
    return hci_le_directed_advertising_report_event_int_cb(header_p,
                                                           buff_p);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_extended_advertising_report_event_int_cb_ucfg(void* header_p,
                                                                uint8_t* buff_p)
{
    return hci_le_extended_advertising_report_event_int_cb(header_p,
                                                           buff_p);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_scan_timeout_event_int_cb_ucfg(void* header_p,
                                                 uint8_t* buff_p)
{
    return hci_le_scan_timeout_event_int_cb(header_p,
                                            buff_p);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_advertising_set_terminated_event_int_cb_ucfg(void* header_p,
                                                               uint8_t* buff_p)
{
    return hci_le_advertising_set_terminated_event_int_cb(header_p,
                                                          buff_p);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_enhanced_connection_complete_v2_event_int_cb_ucfg(void* header_p,
                                                                    uint8_t* buff_p)
{
    return hci_le_enhanced_connection_complete_v2_event_int_cb(header_p,
                                                               buff_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1) ||\
    (CONTROLLER_ISO_ENABLED == 1)
tBleStatus MBM_init_ucfg(void)
{
    return MBM_init();
}
#endif /* (CONNECTION_ENABLED == 1) ||\
          (CONTROLLER_ISO_ENABLED == 1) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint32_t secure_connections_csr_ucfg(void)
{
    return secure_connections_csr();
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus smp_sap_scp_force_debug_key_usage_ucfg(uint8_t config_val)
{
    return smp_sap_scp_force_debug_key_usage(config_val);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_sap_hci_le_read_local_p256_public_key_complete_evt_hndl_ucfg(uint8_t status,
                                                                      uint8_t local_p256_public_key[64])
{
    smp_sap_hci_le_read_local_p256_public_key_complete_evt_hndl(status,
                                                                local_p256_public_key);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_sap_hci_le_generate_dhkey_complete_evt_hndl_ucfg(uint8_t status,
                                                          uint8_t dhkey[32])
{
    smp_sap_hci_le_generate_dhkey_complete_evt_hndl(status,
                                                    dhkey);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint32_t l2c_cos_csr_ucfg(void)
{
    return l2c_cos_csr();
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus L2C_cos_cfc_init_ucfg(void)
{
    return L2C_cos_cfc_init();
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void l2c_cos_process_pending_actions_tsk_ucfg(uint16_t task_idx)
{
    l2c_cos_process_pending_actions_tsk(task_idx);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void L2C_cos_physical_link_disconnection_hndl_ucfg(uint16_t connection_handle)
{
    L2C_cos_physical_link_disconnection_hndl(connection_handle);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus L2C_cos_process_cfc_mode_command_ucfg(void* params)
{
    return L2C_cos_process_cfc_mode_command(params);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint8_t L2C_cos_is_pdu_cframe_cfc_command_opcode_ucfg(uint8_t opCode)
{
    return L2C_cos_is_pdu_cframe_cfc_command_opcode(opCode);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus l2c_cos_hndl_incoming_le_frame_ucfg(void* params)
{
    return l2c_cos_hndl_incoming_le_frame(params);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void l2c_cos_sdu_reassembly_tsk_ucfg(uint16_t task_idx)
{
    l2c_cos_sdu_reassembly_tsk(task_idx);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus l2c_cos_sdu_enqueue_for_segmentation_ucfg(void* params)
{
    return l2c_cos_sdu_enqueue_for_segmentation(params);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void l2c_cos_sdu_segmentation_tsk_ucfg(uint16_t task_idx)
{
    l2c_cos_sdu_segmentation_tsk(task_idx);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1))
void l2c_cos_transmit_pdu_packets_tsk_ucfg(uint16_t task_idx)
{
    l2c_cos_transmit_pdu_packets_tsk(task_idx);
}
#endif /* ((L2CAP_COS_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus L2C_init_ucfg(uint8_t cos_enabled)
{
    return L2C_init(cos_enabled);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if ((CONNECTION_SUBRATING_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void llc_conn_check_subrate_and_set_params_ucfg(void* cntxt_p,
                                                void* params_p)
{
    llc_conn_check_subrate_and_set_params(cntxt_p,
                                          params_p);
}
#endif /* ((CONNECTION_SUBRATING_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONNECTION_SUBRATING_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint32_t llc_conn_calc_skip_ucfg(void* cntxt_p,
                                 uint16_t event_counter,
                                 uint16_t latency)
{
    return llc_conn_calc_skip(cntxt_p,
                              event_counter,
                              latency);
}
#endif /* ((CONNECTION_SUBRATING_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (CONNECTION_ENABLED == 1)
tBleStatus llc_conn_multi_link_connection_ucfg(uint8_t enable)
{
    return llc_conn_multi_link_connection(enable);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
void llc_conn_peripheral_latency_cancellation_tsk_ucfg(uint16_t task_idx)
{
    llc_conn_peripheral_latency_cancellation_tsk(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
uint8_t llc_check_sreq_or_creq_tx_addr_ucfg(void* tx_addr7_p,
                                            uint8_t pdu_type,
                                            uint8_t adv_event_prop,
                                            uint8_t adv_filter_policy,
                                            void* peer_id_addr7_p,
                                            void* res_peer_id_addr7_p,
                                            uint8_t* rl_index_p)
{
    return llc_check_sreq_or_creq_tx_addr(tx_addr7_p,
                                          pdu_type,
                                          adv_event_prop,
                                          adv_filter_policy,
                                          peer_id_addr7_p,
                                          res_peer_id_addr7_p,
                                          rl_index_p);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
uint8_t llc_check_adv_or_srsp_or_crsp_tx_addr_ucfg(uint8_t* tx_addr7_p,
                                                   uint8_t adv_pdu,
                                                   uint8_t filter_policy,
                                                   uint8_t* peer_id_addr7_p,
                                                   uint8_t* rl_index_p,
                                                   uint8_t* res_peer_id_addr7_p)
{
    return llc_check_adv_or_srsp_or_crsp_tx_addr(tx_addr7_p,
                                                 adv_pdu,
                                                 filter_policy,
                                                 peer_id_addr7_p,
                                                 rl_index_p,
                                                 res_peer_id_addr7_p);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
uint8_t llc_check_adv_or_crsp_rx_addr_ucfg(uint8_t* rx_addr7_p,
                                           uint8_t adv_pdu,
                                           uint8_t filter_policy,
                                           uint8_t* local_addr7_p,
                                           uint8_t local_addr_type,
                                           uint8_t rl_index)
{
    return llc_check_adv_or_crsp_rx_addr(rx_addr7_p,
                                         adv_pdu,
                                         filter_policy,
                                         local_addr7_p,
                                         local_addr_type,
                                         rl_index);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
uint32_t bis_csr_ucfg(void)
{
    return bis_csr();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
uint32_t cis_csr_ucfg(void)
{
    return cis_csr();
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if (CONTROLLER_ISO_ENABLED == 1)
void llc_isoal_mem_alloc_ucfg(void)
{
    llc_isoal_mem_alloc();
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
uint32_t iso_csr_ucfg(void)
{
    return iso_csr();
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus iso_rx_bn_pdu_event_int_cb_ucfg(void* header_p,
                                           uint8_t* buff_p)
{
    return iso_rx_bn_pdu_event_int_cb(header_p,
                                      buff_p);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus iso_terminate_event_int_cb_ucfg(void* header_p,
                                           uint8_t* buff_p)
{
    return iso_terminate_event_int_cb(header_p,
                                      buff_p);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus iso_tx_bn_pdu_event_int_cb_ucfg(void* header_p,
                                           uint8_t* buff_p)
{
    return iso_tx_bn_pdu_event_int_cb(header_p,
                                      buff_p);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void llc_big_brc_mem_alloc_ucfg(void)
{
    llc_big_brc_mem_alloc();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus llc_big_brc_alloc_streams_ucfg(void* ctx,
                                          uint8_t stream_count)
{
    return llc_big_brc_alloc_streams(ctx,
                                     stream_count);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void llc_big_brc_add_biginfo_to_periodic_sync_packet_ucfg(void* pointer,
                                                          uint8_t* packet_p)
{
    llc_big_brc_add_biginfo_to_periodic_sync_packet(pointer,
                                                    packet_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void* llc_big_brc_get_group_descr_of_adv_ucfg(uint8_t adv_handle)
{
    return llc_big_brc_get_group_descr_of_adv(adv_handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus llc_big_brc_enqueue_pdu_ucfg(void* ctx_p,
                                        uint32_t iso_interval_idx,
                                        uint16_t conn_handle,
                                        void* pdu_p)
{
    return llc_big_brc_enqueue_pdu(ctx_p,
                                   iso_interval_idx,
                                   conn_handle,
                                   pdu_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
uint32_t llc_big_brc_get_own_big_event_time_ucfg(void* ctx_p,
                                                 uint16_t conn_handle,
                                                 uint16_t num_enq_packet)
{
    return llc_big_brc_get_own_big_event_time(ctx_p,
                                              conn_handle,
                                              num_enq_packet);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void llc_big_sync_mem_alloc_ucfg(void)
{
    llc_big_sync_mem_alloc();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus llc_big_sync_alloc_streams_ucfg(void* ctx,
                                           uint8_t stream_count)
{
    return llc_big_sync_alloc_streams(ctx,
                                      stream_count);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
void llc_big_sync_deploy_sync_ucfg(uint8_t* biginfo,
                                   uint16_t sync_handle,
                                   uint32_t periodic_reference_anchor,
                                   uint8_t sca_value)
{
    llc_big_sync_deploy_sync(biginfo,
                             sync_handle,
                             periodic_reference_anchor,
                             sca_value);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus llc_big_sync_decrypt_bis_packet_ucfg(void* ctx_p,
                                                void* pdu_p)
{
    return llc_big_sync_decrypt_bis_packet(ctx_p,
                                           pdu_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
uint32_t llc_big_sync_get_sdu_synchronization_us_ucfg(uint16_t conn_handle,
                                                      uint8_t framed,
                                                      uint32_t anchor_us,
                                                      uint32_t time_offset)
{
    return llc_big_sync_get_sdu_synchronization_us(conn_handle,
                                                   framed,
                                                   anchor_us,
                                                   time_offset);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus llc_big_cmn_get_iso_params_ucfg(uint8_t direction,
                                           uint16_t conn_handle,
                                           void* param_p)
{
    return llc_big_cmn_get_iso_params(direction,
                                      conn_handle,
                                      param_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONNECTION_ENABLED == 1) &&\
      (CONTROLLER_CIS_ENABLED == 1) &&\
      (CONTROLLER_ISO_ENABLED == 1)\
     )\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
uint32_t llc_cig_cen_get_cis_offset_from_acl_us_ucfg(void* ctx_p,
                                                     void* cis_p,
                                                     uint8_t conn_idx,
                                                     uint16_t* event_count_p,
                                                     uint32_t* cig_anchor_st_p)
{
    return llc_cig_cen_get_cis_offset_from_acl_us(ctx_p,
                                                  cis_p,
                                                  conn_idx,
                                                  event_count_p,
                                                  cig_anchor_st_p);
}
#endif

#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONNECTION_ENABLED == 1) &&\
      (CONTROLLER_CIS_ENABLED == 1) &&\
      (CONTROLLER_ISO_ENABLED == 1)\
     )\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
uint32_t llc_cig_cen_get_sdu_synchronization_us_ucfg(uint16_t conn_handle,
                                                     uint8_t framed,
                                                     uint32_t anchor_us,
                                                     uint32_t time_offset)
{
    return llc_cig_cen_get_sdu_synchronization_us(conn_handle,
                                                  framed,
                                                  anchor_us,
                                                  time_offset);
}
#endif

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
uint32_t llc_cig_per_get_sdu_synchronization_us_ucfg(uint16_t conn_handle,
                                                     uint8_t framed,
                                                     uint32_t anchor_us,
                                                     uint32_t time_offset)
{
    return llc_cig_per_get_sdu_synchronization_us(conn_handle,
                                                  framed,
                                                  anchor_us,
                                                  time_offset);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus llc_cig_cmn_disconnect_ucfg(uint16_t cis_handle,
                                       uint8_t reason)
{
    return llc_cig_cmn_disconnect(cis_handle,
                                  reason);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void llc_cig_cmn_mem_alloc_ucfg(void)
{
    llc_cig_cmn_mem_alloc();
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus llc_cig_cmn_alloc_streams_ucfg(void* ctx,
                                          uint8_t stream_count,
                                          uint8_t group_type)
{
    return llc_cig_cmn_alloc_streams(ctx,
                                     stream_count,
                                     group_type);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void llc_cig_cmn_terminate_stream_ucfg(void* cig_p,
                                       void* cis_p,
                                       uint8_t reason)
{
    llc_cig_cmn_terminate_stream(cig_p,
                                 cis_p,
                                 reason);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
uint32_t llc_cig_cmn_get_own_cig_event_time_ucfg(void* ctx_p,
                                                 uint16_t conn_handle,
                                                 uint16_t num_enq_packet)
{
    return llc_cig_cmn_get_own_cig_event_time(ctx_p,
                                              conn_handle,
                                              num_enq_packet);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus llc_cig_cmn_enqueue_pdu_to_tx_ucfg(void* ctx_p,
                                              uint32_t iso_interval_idx,
                                              uint16_t conn_handle,
                                              void* pdu_p)
{
    return llc_cig_cmn_enqueue_pdu_to_tx(ctx_p,
                                         iso_interval_idx,
                                         conn_handle,
                                         pdu_p);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus llc_cig_cmn_decrypt_packet_ucfg(void* ctx_p,
                                           void* pdu_p)
{
    return llc_cig_cmn_decrypt_packet(ctx_p,
                                      pdu_p);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void llc_cig_cmn_start_cis_ucfg(uint8_t conn_idx,
                                uint16_t instant)
{
    llc_cig_cmn_start_cis(conn_idx,
                          instant);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
uint8_t llc_cig_cmn_is_active_cis_on_acl_ucfg(uint16_t acl_conn_handle)
{
    return llc_cig_cmn_is_active_cis_on_acl(acl_conn_handle);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void llc_cig_cmn_terminate_cises_on_acl_ucfg(uint16_t acl_conn_handle)
{
    llc_cig_cmn_terminate_cises_on_acl(acl_conn_handle);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void llc_cig_cmn_cis_established_event_gen_ucfg(void* cig_p,
                                                void* cis_p,
                                                uint8_t status)
{
    llc_cig_cmn_cis_established_event_gen(cig_p,
                                          cis_p,
                                          status);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus llc_cig_cmn_get_iso_params_ucfg(uint8_t direction,
                                           uint16_t conn_handle,
                                           void* param_p)
{
    return llc_cig_cmn_get_iso_params(direction,
                                      conn_handle,
                                      param_p);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus llc_cig_cmn_read_iso_link_quality_ucfg(uint16_t conn_handle,
                                                  uint32_t* tx_unacked_packets_p,
                                                  uint32_t* tx_flushed_packets_p,
                                                  uint32_t* tx_last_subevent_packets_p,
                                                  uint32_t* retransmitted_packets_p,
                                                  uint32_t* crc_error_packets_p,
                                                  uint32_t* rx_unreceived_packets_p,
                                                  uint32_t* duplicate_packets_p)
{
    return llc_cig_cmn_read_iso_link_quality(conn_handle,
                                             tx_unacked_packets_p,
                                             tx_flushed_packets_p,
                                             tx_last_subevent_packets_p,
                                             retransmitted_packets_p,
                                             crc_error_packets_p,
                                             rx_unreceived_packets_p,
                                             duplicate_packets_p);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if (CONTROLLER_ISO_ENABLED == 1)
void llc_iso_cmn_mem_alloc_ucfg(void)
{
    llc_iso_cmn_mem_alloc();
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
#if ((CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
void llc_padv_mem_allocate_ucfg(uint8_t eadv_en,
                                uint8_t padv_en,
                                uint8_t nr_of_adv_sets,
                                uint8_t* more_info_p)
{
    llc_padv_wr_mem_allocate(eadv_en,
                             padv_en,
                             nr_of_adv_sets,
                             more_info_p);
}
#else
void llc_padv_mem_allocate_ucfg(uint8_t eadv_en,
                                uint8_t padv_en,
                                uint8_t nr_of_adv_sets,
                                uint8_t* more_info_p)
{
    llc_padv_mem_allocate(eadv_en,
                          padv_en,
                          nr_of_adv_sets,
                          more_info_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void llc_padv_init_ucfg(void)
{
    llc_padv_init();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus llc_padv_set_periodic_advertising_data_ucfg(uint16_t advertising_handle,
                                                       uint8_t operation,
                                                       uint16_t data_length,
                                                       uint8_t* data_p)
{
    return llc_padv_set_periodic_advertising_data(advertising_handle,
                                                  operation,
                                                  data_length,
                                                  data_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
uint8_t llc_padv_check_if_syncinfo_is_included_and_start_periodic_advertising_ucfg(void* context_p)
{
    return llc_padv_check_if_syncinfo_is_included_and_start_periodic_advertising(context_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
uint8_t llc_padv_update_sync_info_ucfg(void* padv_per_p,
                                    uint32_t aux_adv_ind_anchor)
{
    return llc_padv_update_sync_info(padv_per_p,
                                     aux_adv_ind_anchor);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
void llc_padv_prepare_periodic_advertising_payload_ucfg(void* padv_per_p,
                                                        uint8_t extended_header_flags,
                                                        uint8_t* payload_p)
{
    llc_padv_prepare_periodic_advertising_payload(padv_per_p,
                                                  extended_header_flags,
                                                  payload_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
uint32_t llc_padv_periodic_adv_sync_csr_ucfg(void)
{
    return llc_padv_periodic_adv_sync_csr();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
uint8_t llc_padv_wr_create_connection_cancel_ucfg(void* _padv_per_p,
                                               uint8_t advertising_handle)
{
    return llc_padv_wr_create_connection_cancel(_padv_per_p,
                                                advertising_handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
void llc_padv_wr_set_start_parameters_ucfg(void* set_padv_wr_start_parameters_p)
{
    llc_padv_wr_set_start_parameters(set_padv_wr_start_parameters_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus llc_padv_wr_set_periodic_advertising_subevent_data_ucfg(void* set_padv_wr_data_p)
{
    return llc_padv_wr_set_periodic_advertising_subevent_data(set_padv_wr_data_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
uint8_t llc_padv_wr_set_ctrdata_ucfg(void* padv_per_p,
                                  uint8_t* ctrdata_p)
{
    return llc_padv_wr_set_ctrdata(padv_per_p,
                                   ctrdata_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
void llc_padv_wr_set_acad_ucfg(void* padv_per_p,
                               uint8_t* ext_hdr_p)
{
    llc_padv_wr_set_acad(padv_per_p,
                         ext_hdr_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
void llc_padv_wr_init_anchors_and_counters_ucfg(void* padv_per_p)
{
    llc_padv_wr_init_anchors_and_counters(padv_per_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
uint32_t llc_padv_periodic_adv_sync_wr_csr_ucfg(void)
{
    return llc_padv_periodic_adv_sync_wr_csr();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
void llc_padv_wr_disable_ext_ucfg(void* _padv_per_p)
{
    llc_padv_wr_disable_ext(_padv_per_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void llc_priv_generate_peer_rpa_from_peer_id_ucfg(void* peer_p,
                                                  uint8_t in_isr)
{
    llc_priv_generate_peer_rpa_from_peer_id(peer_p,
                                            in_isr);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void llc_priv_init_ucfg(uint8_t first_call)
{
    llc_priv_init(first_call);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void llc_priv_generate_local_rpa_from_peer_id_ucfg(void* peer_id_p,
                                                   void* local_rpa_p)
{
    llc_priv_generate_local_rpa_from_peer_id(peer_id_p,
                                             local_rpa_p);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void llc_priv_offline_rpa_resolution_ucfg(uint16_t task_idx)
{
    llc_priv_offline_rpa_resolution(task_idx);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
uint32_t llc_priv_controller_privacy_csr_ucfg(void)
{
    return llc_priv_controller_privacy_csr();
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void llc_priv_set_filter_accept_list_flag_in_resolving_list_ucfg(void* addr8_p,
                                                                 uint8_t set)
{
    llc_priv_set_filter_accept_list_flag_in_resolving_list(addr8_p,
                                                           set);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void llc_priv_clr_all_filter_accept_list_flags_in_resolving_list_ucfg(void)
{
    llc_priv_clr_all_filter_accept_list_flags_in_resolving_list();
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void llc_priv_start_privacy_timer_ucfg(void)
{
    llc_priv_start_privacy_timer();
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void llc_priv_stop_privacy_timer_ucfg(void)
{
    llc_priv_stop_privacy_timer();
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
void llc_priv_init_random_part_of_one_local_rpa_ucfg(void* peer_id_p)
{
    llc_priv_init_random_part_of_one_local_rpa(peer_id_p);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void llc_pscan_cancel_slot_cte_ucfg(void* cntxt_per_p)
{
    llc_pscan_cancel_slot_cte(cntxt_per_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
uint8_t llc_pscan_isr_ucfg(void* cntxt_per_p)
{
    return llc_pscan_isr(cntxt_per_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
void llc_pscan_init_ucfg(void)
{
    llc_pscan_init();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
void llc_pscan_mem_allocate_ucfg(uint8_t scan_en,
                                 uint8_t ext_en,
                                 uint8_t pscan_en)
{
    llc_pscan_mem_allocate(scan_en,
                           ext_en,
                           pscan_en);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
uint8_t llc_pscan_create_sync_pending_ucfg(void)
{
    return llc_pscan_create_sync_pending();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void llc_pscan_enable_adv_addr_ucfg(void* list_p)
{
    llc_pscan_enable_adv_addr(list_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_pscan_push_padv_report_event_ucfg(void* params)
{
    llc_pscan_push_padv_report_event(params);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_pscan_push_past_received_event_ucfg(void* params)
{
    llc_pscan_push_past_received_event(params);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_pscan_push_sync_established_event_ucfg(void* params)
{
    llc_pscan_push_sync_established_event(params);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
uint8_t llc_pscan_check_address_ucfg(void* addr_p)
{
    return llc_pscan_check_address(addr_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
void llc_pscan_synchronizing_ucfg(void* params_p)
{
    llc_pscan_synchronizing(params_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void llc_pscan_wrong_cte_type_ucfg(void* cntxt_p)
{
    llc_pscan_wrong_cte_type(cntxt_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_pscan_wr_init_ucfg(void)
{
    llc_pscan_wr_init();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_pscan_wr_mem_allocate_ucfg(uint8_t scan_en,
                                    uint8_t ext_en,
                                    uint8_t pscan_en,
                                    uint8_t pscan_wr_en,
                                    uint8_t conn_en)
{
    llc_pscan_wr_mem_allocate(scan_en,
                              ext_en,
                              pscan_en,
                              pscan_wr_en,
                              conn_en);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_pscan_wr_per_init_ucfg(uint8_t sync_idx)
{
    llc_pscan_wr_per_init(sync_idx);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_pscan_wr_config_tx_blue_sm_ucfg(void* params_p,
                                         uint8_t pawr_feat)
{
    llc_pscan_wr_config_tx_blue_sm(params_p,
                                   pawr_feat);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
uint8_t llc_pscan_wr_get_pawr_info_ucfg(uint8_t acad_size,
                                     uint8_t* acad_p,
                                     uint8_t* pawr_info_p)
{
    return llc_pscan_wr_get_pawr_info(acad_size,
                                      acad_p,
                                      pawr_info_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
uint8_t llc_pscan_wr_check_pawr_active_ucfg(uint8_t conn_idx)
{
    return llc_pscan_wr_check_pawr_active(conn_idx);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
uint8_t llc_pscan_wr_check_pawr_info_ucfg(void* params_p)
{
    return llc_pscan_wr_check_pawr_info(params_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
uint8_t llc_pscan_wr_reserve_taskslots_ucfg(void* params_p,
                                            uint8_t pawr_feat)
{
    return llc_pscan_wr_reserve_taskslots(params_p,
                                          pawr_feat);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_pscan_wr_set_pscan_cntxt_ucfg(void* cntxt_p,
                                       void* params_p)
{
    llc_pscan_wr_set_pscan_cntxt(cntxt_p,
                                 params_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_pscan_wr_set_scheduler_params_ucfg(void* params_p)
{
    llc_pscan_wr_set_scheduler_params(params_p);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_scan_conn_ind_sent_ucfg(void* ptr,
                                 uint8_t idx)
{
    llc_scan_conn_ind_sent(ptr,
                           idx);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
uint8_t llc_scan_process_ext_adv_ucfg(void* scan_p,
                                   void* params_p,
                                   uint32_t direct_addr[2],
                                   uint8_t idx,
                                   uint8_t advertiser_addr_flag,
                                   uint8_t* send_report_p)
{
    return llc_scan_process_ext_adv(scan_p,
                                    params_p,
                                    direct_addr,
                                    idx,
                                    advertiser_addr_flag,
                                    send_report_p);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_scan_aux_conn_rsp_rcvd_ucfg(void* scan_p,
                                     void* aux_p,
                                     uint8_t idx)
{
    llc_scan_aux_conn_rsp_rcvd(scan_p,
                               aux_p,
                               idx);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1)
void llc_scan_init_ucfg(uint8_t ext_en)
{
    llc_scan_init(ext_en);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1)
void llc_scan_mem_allocate_ucfg(uint8_t scan_en,
                                uint8_t ext_en)
{
    llc_scan_mem_allocate(scan_en,
                          ext_en);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_scan_prepare_conn_ind_req_ucfg(void* ptr,
                                        uint8_t idx,
                                        uint8_t aux_conn_req)
{
    llc_scan_prepare_conn_ind_req(ptr,
                                  idx,
                                  aux_conn_req);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void llc_scan_enable_extended_ucfg(void* scan_p)
{
    llc_scan_enable_extended(scan_p);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void llc_scan_push_ext_adv_report_ucfg(void* ptr,
                                       uint8_t data_len,
                                       uint8_t data_offset,
                                       uint8_t event_type)
{
    llc_scan_push_ext_adv_report(ptr,
                                 data_len,
                                 data_offset,
                                 event_type);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus llc_scan_reserve_taskslots_ucfg(void* scan_en_p,
                                           void* scan_p)
{
    return llc_scan_reserve_taskslots(scan_en_p,
                                      scan_p);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_scan_set_conn_params_ucfg(Extended_Create_Connection_Parameters_t ext_create_conn_params,
                                   uint8_t initiating_phy)
{
    llc_scan_set_conn_params(ext_create_conn_params,
                             initiating_phy);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void llc_scan_disable_ucfg(void* scan_p)
{
    llc_scan_disable(scan_p);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if ((CONNECTION_SUBRATING_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint8_t llc_subrate_get_active_sr_req_proc_ucfg(uint8_t conn_idx)
{
    return llc_subrate_get_active_sr_req_proc(conn_idx);
}
#endif /* ((CONNECTION_SUBRATING_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONNECTION_SUBRATING_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void llc_subrate_new_sr_base_event_ucfg(uint16_t sr_factor,
                                        uint16_t* sr_base_event_p)
{
    llc_subrate_new_sr_base_event(sr_factor,
                                  sr_base_event_p);
}
#endif /* ((CONNECTION_SUBRATING_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONNECTION_SUBRATING_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void llc_subrate_update_cont_counter_ucfg(void* cntxt_p)
{
    llc_subrate_update_cont_counter(cntxt_p);
}
#endif /* ((CONNECTION_SUBRATING_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONNECTION_SUBRATING_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint8_t llc_subrate_offline_processing_ucfg(void* cntxt_p)
{
    return llc_subrate_offline_processing(cntxt_p);
}
#endif /* ((CONNECTION_SUBRATING_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (CONTROLLER_ISO_ENABLED == 1)
void llc_mngm_csa2_select_subevent_channel_ucfg(uint8_t subevent_counter,
                                                uint8_t* subevent_index_p,
                                                uint16_t prn_s,
                                                uint8_t remapping_index_of_last_used_channel,
                                                uint16_t* prn_subevent_lu_p,
                                                uint16_t channel_identifier,
                                                void* _csa2_table_p,
                                                uint8_t* channel_index_p)
{
    llc_mngm_csa2_select_subevent_channel(subevent_counter,
                                          subevent_index_p,
                                          prn_s,
                                          remapping_index_of_last_used_channel,
                                          prn_subevent_lu_p,
                                          channel_identifier,
                                          _csa2_table_p,
                                          channel_index_p);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_cpe_init_length_update_ucfg(void)
{
    LL_cpe_init_length_update();
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_cpe_init_phy_update_ucfg(void)
{
    LL_cpe_init_phy_update();
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_cpe_init_cte_ucfg(void)
{
    LL_cpe_init_cte();
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
void LL_cpe_init_past_ucfg(void)
{
    LL_cpe_init_past();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LL_cpe_init_pcl_ucfg(void)
{
    LL_cpe_init_pcl();
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (CONNECTION_ENABLED == 1)
void LL_cpe_init_conn_update_ucfg(void)
{
    LL_cpe_init_conn_update();
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
void LL_cpe_init_chmap_update_ucfg(void)
{
    LL_cpe_init_chmap_update();
}
#endif /* (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LL_cpe_init_chc_enable_ucfg(void)
{
    LL_cpe_init_chc_enable();
}
#endif /* ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LL_cpe_init_chc_reporting_ucfg(void)
{
    LL_cpe_init_chc_reporting();
}
#endif /* ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONNECTION_SUBRATING_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LL_cpe_init_subrate_ucfg(void)
{
    LL_cpe_init_subrate();
}
#endif /* ((CONNECTION_SUBRATING_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void LL_cpe_init_sca_upd_ucfg(void)
{
    LL_cpe_init_sca_upd();
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void LL_cpe_init_cis_ucfg(void)
{
    LL_cpe_init_cis();
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if (CONNECTION_ENABLED == 1)
void LL_cpe_init_ucfg(void)
{
    LL_cpe_init();
}
#endif /* (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LLC_channel_map_copy_to_cpf_context_ucfg(void* cntxt_p,
                                              uint8_t conn_idx)
{
    LLC_channel_map_copy_to_cpf_context(cntxt_p,
                                        conn_idx);
}
#endif /* ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
uint8_t LLC_channel_map_update_offline_processing_ucfg(uint8_t conn_idx)
{
    return LLC_channel_map_update_offline_processing(conn_idx);
}
#endif

#if ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LLC_conn_init_chc_ctxt_ucfg(uint8_t conn_idx)
{
    LLC_conn_init_chc_ctxt(conn_idx);
}
#endif /* ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LLC_chc_ll_cntxt_init_ucfg(void)
{
    LLC_chc_ll_cntxt_init();
}
#endif /* ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint8_t LLC_chc_reporting_offline_processing_ucfg(uint8_t conn_idx)
{
    return LLC_chc_reporting_offline_processing(conn_idx);
}
#endif /* ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
void LL_cpf_cis_processing_ucfg(uint16_t task_idx)
{
    LL_cpf_cis_processing(task_idx);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_conn_upd_max_tx_time_coded_ucfg(void* params)
{
    LL_conn_upd_max_tx_time_coded(params);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_conn_upd_data_length_change_event_ucfg(void* params)
{
    LL_conn_upd_data_length_change_event(params);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_conn_init_cte_ctxt_ucfg(uint8_t conn_idx)
{
    llc_conn_init_cte_ctxt(conn_idx);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
uint8_t LLC_cte_request_procedure_ucfg(void* params)
{
    return LLC_cte_request_procedure(params);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LLC_connection_cte_response_pause_resume_ucfg(uint8_t conn_idx,
                                                   uint8_t tx_phy)
{
    LLC_connection_cte_response_pause_resume(conn_idx,
                                             tx_phy);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LLC_connection_cte_response_disable_ucfg(uint8_t conn_idx,
                                              uint8_t taskslot_no)
{
    LLC_connection_cte_response_disable(conn_idx,
                                        taskslot_no);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void llc_cte_process_rx_cte_ucfg(void* params,
                                 uint8_t cte_type)
{
    llc_cte_process_rx_cte(params,
                           cte_type);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
void LLC_authenticated_payload_timeout_processing_ucfg(uint16_t task_idx)
{
    LLC_authenticated_payload_timeout_processing(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void llc_past_mem_allocate_ucfg(uint8_t scan_en,
                                uint8_t ext_en,
                                uint8_t pscan_en,
                                uint8_t conn_en)
{
    llc_past_mem_allocate(scan_en,
                          ext_en,
                          pscan_en,
                          conn_en);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_past_load_txctrl_packet_from_scanner_ucfg(void* params,
                                                  uint8_t* pdu_p,
                                                  uint32_t instant_anchor,
                                                  uint32_t connect_interval,
                                                  uint16_t connect_event_count,
                                                  uint16_t connect_event_cnt)
{
    LL_past_load_txctrl_packet_from_scanner(params,
                                            pdu_p,
                                            instant_anchor,
                                            connect_interval,
                                            connect_event_count,
                                            connect_event_cnt);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_periodicscan_deploy_scanner_from_past_ucfg(void* params,
                                                   uint8_t conn_idx,
                                                   uint8_t pawr_feat)
{
    LL_periodicscan_deploy_scanner_from_past(params,
                                             conn_idx,
                                             pawr_feat);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_past_initialize_connect_context_ucfg(uint8_t conn_idx)
{
    LL_past_initialize_connect_context(conn_idx);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_past_default_params_ucfg(uint8_t conn_idx)
{
    LL_past_default_params(conn_idx);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void llc_conn_init_pcl_ctxt_ucfg(uint8_t conn_idx)
{
    llc_conn_init_pcl_ctxt(conn_idx);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LLC_pcl_hal_cntxt_init_ucfg(uintptr_t pcl_cntxt_p)
{
    LLC_pcl_hal_cntxt_init(pcl_cntxt_p);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LLC_pcl_incr_rx_packets_ucfg(uint8_t conn_idx)
{
    LLC_pcl_incr_rx_packets(conn_idx);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LLC_pcl_update_avg_rssi_ucfg(void* params)
{
    LLC_pcl_update_avg_rssi(params);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LLC_pcl_set_radio_tx_power_conn_start_ucfg(uint8_t conn_idx)
{
    LLC_pcl_set_radio_tx_power_conn_start(conn_idx);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint8_t LLC_pcl_get_radio_tx_power_ucfg(uint8_t conn_idx,
                                        uint8_t phy_idx)
{
    return LLC_pcl_get_radio_tx_power(conn_idx,
                                      phy_idx);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void LLC_pcl_set_radio_tx_power_and_eval_indication_ucfg(uint8_t conn_idx,
                                                         uint8_t send_ind,
                                                         int8_t ind_delta,
                                                         uint8_t change_txpower)
{
    LLC_pcl_set_radio_tx_power_and_eval_indication(conn_idx,
                                                   send_ind,
                                                   ind_delta,
                                                   change_txpower);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
uint8_t LLC_pcl_offline_processing_ucfg(uint8_t conn_idx)
{
    return LLC_pcl_offline_processing(conn_idx);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus LL_Read_RSSI_ucfg(int8_t* rssiVal,
                             uint16_t connHandle)
{
    return LL_Read_RSSI(rssiVal,
                        connHandle);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
uint8_t LLC_pcl_get_number_of_phys_ucfg(void)
{
    return LLC_pcl_get_number_of_phys();
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
    (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_phy_upd_compute_data_PDU_length_params_ucfg(void* params)
{
    LL_phy_upd_compute_data_PDU_length_params(params);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
          (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
uint8_t LL_phy_upd_pending_ucfg(uint8_t conn_idx)
{
    return LL_phy_upd_pending(conn_idx);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus LL_phy_update_init_ucfg(void)
{
    return LL_phy_update_init();
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus LL_phy_update_init_per_st_data_ucfg(uint8_t conn_idx)
{
    return LL_phy_update_init_per_st_data(conn_idx);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
void LL_phy_upd_evt_pending_check_isr_ucfg(uint8_t conn_idx)
{
    LL_phy_upd_evt_pending_check_isr(conn_idx);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void LLC_blueapi_cte_ucfg(void* params)
{
    LLC_blueapi_cte(params);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void LLC_connless_process_rx_cte_ucfg(uint8_t iq_samples_ready,
                                      void* params,
                                      uint8_t iq_samples_number,
                                      uint8_t rx_cte_type,
                                      uint8_t channel)
{
    LLC_connless_process_rx_cte(iq_samples_ready,
                                params,
                                iq_samples_number,
                                rx_cte_type,
                                channel);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
uint8_t LLC_check_iq_samples_ready_ucfg(uint8_t* iq_samples_number,
                                     uint8_t* channel,
                                     uint8_t taskslot_no)
{
    return LLC_check_iq_samples_ready(iq_samples_number,
                                      channel,
                                      taskslot_no);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void llc_cte_init_ucfg(void)
{
    llc_cte_init();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void llc_cte_mem_allocate_ucfg(uint8_t cte_en,
                               uint8_t scan_en,
                               uint8_t ext_en,
                               uint8_t periodic_en)
{
    llc_cte_mem_allocate(cte_en,
                         scan_en,
                         ext_en,
                         periodic_en);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void llc_cte_timer_error_ucfg(void)
{
    llc_cte_timer_error();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_CTE_ENABLED == 1)
void llc_cte_timer_start_ucfg(void* params)
{
    llc_cte_timer_start(params);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_CTE_ENABLED == 1)
uint8_t llc_cte_timer_stop_ucfg(void)
{
    return llc_cte_timer_stop();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void LLC_test_process_rx_cte_ucfg(void* params)
{
    LLC_test_process_rx_cte(params);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
void LLC_test_set_cte_ucfg(void* params)
{
    LLC_test_set_cte(params);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
void ADV_ISR_connect_request_received_ucfg(void* pointer,
                                           uint8_t* packet,
                                           void* PeerIDAddress_p)
{
    ADV_ISR_connect_request_received(pointer,
                                     packet,
                                     PeerIDAddress_p);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
void LL_eadv_EauxIsr_connect_response_sent_ucfg(void* pointer)
{
    LL_eadv_EauxIsr_connect_response_sent(pointer);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
void LL_eadv_EauxIsr_connect_request_received_ucfg(void* pointer,
                                                   uint8_t* calibration_required)
{
    LL_eadv_EauxIsr_connect_request_received(pointer,
                                             calibration_required);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
uint8_t EADV_start_request_radio_tasks_ucfg(void* pointer)
{
    return EADV_start_request_radio_tasks(pointer);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus llc_eadv_max_supported_data_check_ucfg(uint16_t data_length,
                                                  void* pointer)
{
    return llc_eadv_max_supported_data_check(data_length,
                                             pointer);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
void LL_eadv_start_extended_ucfg(void* pointer)
{
    LL_eadv_start_extended(pointer);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
uint8_t ext_adv_scan_enabled_ucfg(void)
{
    return ext_adv_scan_enabled();
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus LL_Clear_Advertising_Sets_ucfg(void)
{
    return LL_Clear_Advertising_Sets();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus LL_Remove_Advertising_Set_ucfg(uint16_t Advertising_Handle)
{
    return LL_Remove_Advertising_Set(Advertising_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
uint8_t Data_Len_Update_Offline_Processing_ucfg(void* params,
                                             uint32_t ctrl_flds)
{
    return Data_Len_Update_Offline_Processing(params,
                                              ctrl_flds);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1)
tBleStatus ll_write_supported_data_ucfg(uint16_t Supported_Max_Tx_Octets,
                                        uint16_t Supported_Max_Tx_Time,
                                        uint16_t Supported_Max_Rx_Octets,
                                        uint16_t Supported_Max_Rx_Time)
{
    return ll_write_supported_data(Supported_Max_Tx_Octets,
                                   Supported_Max_Tx_Time,
                                   Supported_Max_Rx_Octets,
                                   Supported_Max_Rx_Time);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
void LL_init_ucfg(uint8_t dataLenExt,
                  uint8_t PhyUpd,
                  uint8_t ExtAdvScan,
                  uint8_t CtrlPriv,
                  uint8_t ScanSupp,
                  uint8_t PerAdvScan,
                  uint8_t PerAdvScanWr,
                  uint8_t Cte,
                  uint8_t Pcl,
                  uint8_t Cns,
                  uint8_t Chc)
{
    LL_init(dataLenExt,
            PhyUpd,
            ExtAdvScan,
            CtrlPriv,
            ScanSupp,
            PerAdvScan,
            PerAdvScanWr,
            Cte,
            Pcl,
            Cns,
            Chc);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus smp_debug_trudy__set_config_ucfg(uint32_t config)
{
    return smp_debug_trudy__set_config(config);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
tBleStatus smp_start_encryption_ucfg(void* params)
{
    return smp_start_encryption(params);
}
#endif
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus smp_pp1_cei_send_pairing_request_ucfg(void* params)
{
    return smp_pp1_cei_send_pairing_request(params);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus smp_pp1_cei_rxp_pairing_response_excerpt_scp_ucfg(void* params)
{
    return smp_pp1_cei_rxp_pairing_response_excerpt_scp(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_pp2_cei_auth_stage1_start_excerpt_scp_ucfg(void* params)
{
    smp_pp2_cei_auth_stage1_start_excerpt_scp(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_pp2_per_auth_stage1_start_excerpt_scp_ucfg(void* params)
{
    smp_pp2_per_auth_stage1_start_excerpt_scp(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_pp2_cei_send_pairing_confirm_excerpt_scp_ucfg(void* params)
{
    smp_pp2_cei_send_pairing_confirm_excerpt_scp(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus smp_pp2_cei_rx_process_pairing_random_excerpt1_scp_ucfg(void* params)
{
    return smp_pp2_cei_rx_process_pairing_random_excerpt1_scp(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_pp2_cei_rx_process_pairing_random_excerpt2_scp_ucfg(void* params)
{
    smp_pp2_cei_rx_process_pairing_random_excerpt2_scp(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_pp2_per_rx_process_pairing_confirm_excerpt_scp_ucfg(void* params)
{
    smp_pp2_per_rx_process_pairing_confirm_excerpt_scp(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_pp2_per_rx_process_pairing_random_excerpt_scp_ucfg(void* params)
{
    smp_pp2_per_rx_process_pairing_random_excerpt_scp(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_scp_init_ucfg(uint8_t use_debug_key)
{
    smp_scp_init(use_debug_key);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus smp_scp_continue_on_exclusive_sc_pairing_ucfg(void* params)
{
    return smp_scp_continue_on_exclusive_sc_pairing(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus smp_scp_public_key_prepare_and_exchange_ucfg(void* params)
{
    return smp_scp_public_key_prepare_and_exchange(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus smp_scp_oob_generate_new_local_data_ucfg(void)
{
    return smp_scp_oob_generate_new_local_data();
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_scp_stats_update_on_pairing_complete_ucfg(void* params)
{
    smp_scp_stats_update_on_pairing_complete(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void smp_fsm_process_actions_wrt_state_tsk_ucfg(uint16_t task_idx)
{
    smp_fsm_process_actions_wrt_state_tsk(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1))
void smp_fsm_execute_actions_scp_phase2as2_ucfg(void* params)
{
    smp_fsm_execute_actions_scp_phase2as2(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
void smp_fsm_execute_actions_excerpt_cei_ucfg(void* params)
{
    smp_fsm_execute_actions_excerpt_cei(params);
}
#endif
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
void smp_pka_process_ecc_computation_tsk_ucfg(uint16_t task_idx)
{
    smp_pka_process_ecc_computation_tsk(task_idx);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void smp_rxp_process_rxed_packets_tsk_ucfg(uint16_t task_idx)
{
    smp_rxp_process_rxed_packets_tsk(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus smp_rxp_process_exception_cases_excerpt_scp_ucfg(void* params)
{
    return smp_rxp_process_exception_cases_excerpt_scp(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus smp_rxp_process_wrt_current_fsm_excerpt_scp_ucfg(void* params)
{
    return smp_rxp_process_wrt_current_fsm_excerpt_scp(params);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
tBleStatus smp_rxp_process_wrt_current_fsm_excerpt_cei_ucfg(void* params)
{
    return smp_rxp_process_wrt_current_fsm_excerpt_cei(params);
}
#endif
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void smp_init_ucfg(void)
{
    smp_init();
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void GAT_att_cmn_init_ucfg(void)
{
    GAT_att_cmn_init();
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void GAT_att_cmn_timer_expire_tsk_ucfg(uint16_t task_idx)
{
    GAT_att_cmn_timer_expire_tsk(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void GAT_att_cmn_tx_pool_evt_tsk_ucfg(uint16_t task_idx)
{
    GAT_att_cmn_tx_pool_evt_tsk(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void GAT_att_srv_process_rx_pckt_tsk_ucfg(uint16_t task_idx)
{
    GAT_att_srv_process_rx_pckt_tsk(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void GAT_srv_db_hash_tsk_ucfg(uint16_t task_idx)
{
    GAT_srv_db_hash_tsk(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
void GAT_srv_send_srv_change_tsk_ucfg(uint16_t task_idx)
{
    GAT_srv_send_srv_change_tsk(task_idx);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */


/*
* *****************************************************************************
*                      BLE Stack API functions
* *****************************************************************************
*/

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_terminate(uint16_t Connection_Handle,
                             uint8_t Reason)
{
    return aci_gap_terminate_api(Connection_Handle,
                                 Reason);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
tBleStatus aci_gap_start_connection_update(uint16_t Connection_Handle,
                                           uint16_t Connection_Interval_Min,
                                           uint16_t Connection_Interval_Max,
                                           uint16_t Max_Latency,
                                           uint16_t Supervision_Timeout,
                                           uint16_t Min_CE_Length,
                                           uint16_t Max_CE_Length)
{
    return aci_gap_start_connection_update_api(Connection_Handle,
                                               Connection_Interval_Min,
                                               Connection_Interval_Max,
                                               Max_Latency,
                                               Supervision_Timeout,
                                               Min_CE_Length,
                                               Max_CE_Length);
}
#endif
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus aci_gap_set_scan_configuration(uint8_t duplicate_filtering,
                                          uint8_t scanning_filter_policy,
                                          uint8_t phy,
                                          uint8_t scan_type,
                                          uint16_t scan_interval,
                                          uint16_t scan_window)
{
    return aci_gap_set_scan_configuration_api(duplicate_filtering,
                                              scanning_filter_policy,
                                              phy,
                                              scan_type,
                                              scan_interval,
                                              scan_window);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_set_connection_configuration(uint8_t phy,
                                                uint16_t connection_interval_min,
                                                uint16_t connection_interval_max,
                                                uint16_t max_latency,
                                                uint16_t supervision_timeout,
                                                uint16_t min_ce_length,
                                                uint16_t max_ce_length)
{
    return aci_gap_set_connection_configuration_api(phy,
                                                    connection_interval_min,
                                                    connection_interval_max,
                                                    max_latency,
                                                    supervision_timeout,
                                                    min_ce_length,
                                                    max_ce_length);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_create_connection(uint8_t Initiating_PHY,
                                     uint8_t Peer_Address_Type,
                                     uint8_t Peer_Address[6])
{
    return aci_gap_create_connection_api(Initiating_PHY,
                                         Peer_Address_Type,
                                         Peer_Address);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus aci_gap_start_procedure(uint8_t procedure_code,
                                   uint8_t phys,
                                   uint16_t duration,
                                   uint16_t period)
{
    return aci_gap_start_procedure_api(procedure_code,
                                       phys,
                                       duration,
                                       period);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_discover_name(uint8_t PHYs,
                                 uint8_t Peer_Address_Type,
                                 uint8_t Peer_Address[6])
{
    return aci_gap_discover_name_api(PHYs,
                                     Peer_Address_Type,
                                     Peer_Address);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus aci_gap_terminate_proc(uint8_t Procedure_Code)
{
    return aci_gap_terminate_proc_api(Procedure_Code);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_create_periodic_advertising_connection(uint8_t Advertising_Handle,
                                                          uint8_t Subevent,
                                                          uint8_t Initiator_Filter_Policy,
                                                          uint8_t Own_Address_Type,
                                                          uint8_t Peer_Address_Type,
                                                          uint8_t Peer_Address[6],
                                                          uint16_t Connection_Interval_Min,
                                                          uint16_t Connection_Interval_Max,
                                                          uint16_t Max_Latency,
                                                          uint16_t Supervision_Timeout,
                                                          uint16_t Min_CE_Length,
                                                          uint16_t Max_CE_Length)
{
    return aci_gap_create_periodic_advertising_connection_api(Advertising_Handle,
                                                              Subevent,
                                                              Initiator_Filter_Policy,
                                                              Own_Address_Type,
                                                              Peer_Address_Type,
                                                              Peer_Address,
                                                              Connection_Interval_Min,
                                                              Connection_Interval_Max,
                                                              Max_Latency,
                                                              Supervision_Timeout,
                                                              Min_CE_Length,
                                                              Max_CE_Length);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus aci_gap_remove_advertising_set(uint8_t Advertising_Handle)
{
    return aci_gap_remove_advertising_set_api(Advertising_Handle);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus aci_gap_clear_advertising_sets(void)
{
    return aci_gap_clear_advertising_sets_api();
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_set_io_capability(uint8_t IO_Capability)
{
    return aci_gap_set_io_capability_api(IO_Capability);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_set_security_requirements(uint8_t Bonding_Mode,
                                             uint8_t MITM_Mode,
                                             uint8_t SC_Support,
                                             uint8_t KeyPress_Notification_Support,
                                             uint8_t Min_Encryption_Key_Size,
                                             uint8_t Max_Encryption_Key_Size,
                                             uint8_t Pairing_Response)
{
    return aci_gap_set_security_requirements_api(Bonding_Mode,
                                                 MITM_Mode,
                                                 SC_Support,
                                                 KeyPress_Notification_Support,
                                                 Min_Encryption_Key_Size,
                                                 Max_Encryption_Key_Size,
                                                 Pairing_Response);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_set_security(uint16_t Connection_Handle,
                                uint8_t Security_Level,
                                uint8_t Force_Pairing)
{
    return aci_gap_set_security_api(Connection_Handle,
                                    Security_Level,
                                    Force_Pairing);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_pairing_resp(uint16_t Connection_Handle,
                                uint8_t Accept)
{
    return aci_gap_pairing_resp_api(Connection_Handle,
                                    Accept);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_passkey_resp(uint16_t Connection_Handle,
                                uint32_t Passkey)
{
    return aci_gap_passkey_resp_api(Connection_Handle,
                                    Passkey);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus aci_gap_passkey_input(uint16_t Connection_Handle,
                                 uint8_t Input_Type)
{
    return aci_gap_passkey_input_api(Connection_Handle,
                                     Input_Type);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_get_oob_data(uint8_t OOB_Data_Type,
                                uint8_t* Address_Type,
                                uint8_t Address[6],
                                uint8_t* OOB_Data_Len,
                                uint8_t OOB_Data[16])
{
    return aci_gap_get_oob_data_api(OOB_Data_Type,
                                    Address_Type,
                                    Address,
                                    OOB_Data_Len,
                                    OOB_Data);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_set_oob_data(uint8_t Device_Type,
                                uint8_t Address_Type,
                                uint8_t Address[6],
                                uint8_t OOB_Data_Type,
                                uint8_t OOB_Data_Len,
                                uint8_t OOB_Data[16])
{
    return aci_gap_set_oob_data_api(Device_Type,
                                    Address_Type,
                                    Address,
                                    OOB_Data_Type,
                                    OOB_Data_Len,
                                    OOB_Data);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((SECURE_CONNECTIONS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus aci_gap_numeric_comparison_value_confirm_yesno(uint16_t Connection_Handle,
                                                          uint8_t Confirm_Yes_No)
{
    return aci_gap_numeric_comparison_value_confirm_yesno_api(Connection_Handle,
                                                              Confirm_Yes_No);
}
#endif /* ((SECURE_CONNECTIONS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_get_security_level(uint16_t Connection_Handle,
                                      uint8_t* Security_Mode,
                                      uint8_t* Security_Level)
{
    return aci_gap_get_security_level_api(Connection_Handle,
                                          Security_Mode,
                                          Security_Level);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_clear_security_db(void)
{
    return aci_gap_clear_security_db_api();
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_get_bonded_devices(uint8_t Offset,
                                      uint8_t Max_Num_Of_Addresses,
                                      uint8_t* Num_of_Addresses,
                                      Bonded_Device_Entry_t* Bonded_Device_Entry)
{
    return aci_gap_get_bonded_devices_api(Offset,
                                          Max_Num_Of_Addresses,
                                          Num_of_Addresses,
                                          Bonded_Device_Entry);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_is_device_bonded(uint8_t Peer_Address_Type,
                                    uint8_t Peer_Address[6])
{
    return aci_gap_is_device_bonded_api(Peer_Address_Type,
                                        Peer_Address);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gap_remove_bonded_device(uint8_t peerIdentityAddressType,
                                        uint8_t peerIdentityDeviceAddress[6])
{
    return aci_gap_remove_bonded_device_api(peerIdentityAddressType,
                                            peerIdentityDeviceAddress);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_add_service(ble_gatt_srv_def_t* Serv_p)
{
    return aci_gatt_srv_add_service_api(Serv_p);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_rm_service(uint16_t Serv_Attr_H)
{
    return aci_gatt_srv_rm_service_api(Serv_Attr_H);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
uint16_t aci_gatt_srv_get_service_handle(ble_gatt_srv_def_t* Serv_p)
{
    return aci_gatt_srv_get_service_handle_api(Serv_p);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_include_service(uint16_t Serv_Attr_H,
                                        uint16_t Incl_Serv_Attr_H)
{
    return aci_gatt_srv_include_service_api(Serv_Attr_H,
                                            Incl_Serv_Attr_H);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_rm_include_service(uint16_t Incl_Serv_Attr_H)
{
    return aci_gatt_srv_rm_include_service_api(Incl_Serv_Attr_H);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
uint16_t aci_gatt_srv_get_include_service_handle(uint16_t Serv_Attr_H,
                                                 ble_gatt_srv_def_t* Included_Srv_p)
{
    return aci_gatt_srv_get_include_service_handle_api(Serv_Attr_H,
                                                       Included_Srv_p);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_add_char(ble_gatt_chr_def_t* Char_p,
                                 uint16_t Serv_Attr_H)
{
    return aci_gatt_srv_add_char_api(Char_p,
                                     Serv_Attr_H);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_rm_char(uint16_t Char_Decl_Attr_H)
{
    return aci_gatt_srv_rm_char_api(Char_Decl_Attr_H);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
uint16_t aci_gatt_srv_get_char_decl_handle(ble_gatt_chr_def_t* Char_p)
{
    return aci_gatt_srv_get_char_decl_handle_api(Char_p);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_add_char_desc(ble_gatt_descr_def_t* Descr_p,
                                      uint16_t Char_Attr_H)
{
    return aci_gatt_srv_add_char_desc_api(Descr_p,
                                          Char_Attr_H);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
uint16_t aci_gatt_srv_get_descriptor_handle(ble_gatt_descr_def_t* Descr_p)
{
    return aci_gatt_srv_get_descriptor_handle_api(Descr_p);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_notify(uint16_t Connection_Handle,
                               uint16_t CID,
                               uint16_t Attr_Handle,
                               uint8_t Flags,
                               uint16_t Val_Length,
                               uint8_t* Val_p)
{
    return aci_gatt_srv_notify_api(Connection_Handle,
                                   CID,
                                   Attr_Handle,
                                   Flags,
                                   Val_Length,
                                   Val_p);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_multi_notify(uint16_t Connection_Handle,
                                     uint16_t CID,
                                     uint8_t Flags,
                                     uint8_t Num_Of_Attr,
                                     Gatt_Srv_Notify_Attr_t* Gatt_Srv_Notify_Attr)
{
    return aci_gatt_srv_multi_notify_api(Connection_Handle,
                                         CID,
                                         Flags,
                                         Num_Of_Attr,
                                         Gatt_Srv_Notify_Attr);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_resp(uint16_t Connection_Handle,
                             uint16_t CID,
                             uint16_t Attr_Handle,
                             uint8_t Error_Code,
                             uint16_t Data_Len,
                             uint8_t* Data_p)
{
    return aci_gatt_srv_resp_api(Connection_Handle,
                                 CID,
                                 Attr_Handle,
                                 Error_Code,
                                 Data_Len,
                                 Data_p);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_read_handle_value(uint16_t Attr_Handle,
                                          uint16_t* Val_Length_p,
                                          uint8_t** Val_pp)
{
    return aci_gatt_srv_read_handle_value_api(Attr_Handle,
                                              Val_Length_p,
                                              Val_pp);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_read_multiple_instance_handle_value(uint16_t Connection_Handle,
                                                            uint16_t Attr_Handle,
                                                            uint16_t* Val_Length_p,
                                                            uint8_t** Val_pp)
{
    return aci_gatt_srv_read_multiple_instance_handle_value_api(Connection_Handle,
                                                                Attr_Handle,
                                                                Val_Length_p,
                                                                Val_pp);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_srv_write_multiple_instance_handle_value(uint16_t Connection_Handle,
                                                             uint16_t Attr_Handle,
                                                             uint16_t Char_Value_Length,
                                                             uint8_t* Char_Value)
{
    return aci_gatt_srv_write_multiple_instance_handle_value_api(Connection_Handle,
                                                                 Attr_Handle,
                                                                 Char_Value_Length,
                                                                 Char_Value);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_set_event_mask(uint32_t GATT_Evt_Mask)
{
    return aci_gatt_set_event_mask_api(GATT_Evt_Mask);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_exchange_config(uint16_t Connection_Handle)
{
    return aci_gatt_clt_exchange_config_api(Connection_Handle);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_disc_all_primary_services(uint16_t Connection_Handle,
                                                  uint16_t CID)
{
    return aci_gatt_clt_disc_all_primary_services_api(Connection_Handle,
                                                      CID);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_disc_primary_service_by_uuid(uint16_t Connection_Handle,
                                                     uint16_t CID,
                                                     uint8_t UUID_Type,
                                                     UUID_t* UUID)
{
    return aci_gatt_clt_disc_primary_service_by_uuid_api(Connection_Handle,
                                                         CID,
                                                         UUID_Type,
                                                         UUID);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_disc_all_char_of_service(uint16_t Connection_Handle,
                                                 uint16_t CID,
                                                 uint16_t Start_Handle,
                                                 uint16_t End_Handle)
{
    return aci_gatt_clt_disc_all_char_of_service_api(Connection_Handle,
                                                     CID,
                                                     Start_Handle,
                                                     End_Handle);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_disc_char_by_uuid(uint16_t Connection_Handle,
                                          uint16_t CID,
                                          uint16_t Start_Handle,
                                          uint16_t End_Handle,
                                          uint8_t UUID_Type,
                                          UUID_t* UUID)
{
    return aci_gatt_clt_disc_char_by_uuid_api(Connection_Handle,
                                              CID,
                                              Start_Handle,
                                              End_Handle,
                                              UUID_Type,
                                              UUID);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_disc_all_char_desc(uint16_t Connection_Handle,
                                           uint16_t CID,
                                           uint16_t Char_Handle,
                                           uint16_t End_Handle)
{
    return aci_gatt_clt_disc_all_char_desc_api(Connection_Handle,
                                               CID,
                                               Char_Handle,
                                               End_Handle);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_find_included_services(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t Start_Handle,
                                               uint16_t End_Handle)
{
    return aci_gatt_clt_find_included_services_api(Connection_Handle,
                                                   CID,
                                                   Start_Handle,
                                                   End_Handle);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_read(uint16_t Connection_Handle,
                             uint16_t CID,
                             uint16_t Attr_Handle)
{
    return aci_gatt_clt_read_api(Connection_Handle,
                                 CID,
                                 Attr_Handle);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_read_long(uint16_t Connection_Handle,
                                  uint16_t CID,
                                  uint16_t Attr_Handle,
                                  uint16_t Val_Offset)
{
    return aci_gatt_clt_read_long_api(Connection_Handle,
                                      CID,
                                      Attr_Handle,
                                      Val_Offset);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_read_using_char_uuid(uint16_t Connection_Handle,
                                             uint16_t CID,
                                             uint16_t Start_Handle,
                                             uint16_t End_Handle,
                                             uint8_t UUID_Type,
                                             UUID_t* UUID)
{
    return aci_gatt_clt_read_using_char_uuid_api(Connection_Handle,
                                                 CID,
                                                 Start_Handle,
                                                 End_Handle,
                                                 UUID_Type,
                                                 UUID);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_read_multiple_char_value(uint16_t Connection_Handle,
                                                 uint16_t CID,
                                                 uint8_t Number_of_Handles,
                                                 uint16_t* Handle_Entry)
{
    return aci_gatt_clt_read_multiple_char_value_api(Connection_Handle,
                                                     CID,
                                                     Number_of_Handles,
                                                     Handle_Entry);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_read_multiple_var_len_char_value(uint16_t Connection_Handle,
                                                         uint16_t CID,
                                                         uint8_t Number_of_Handles,
                                                         uint16_t* Handle_Entry)
{
    return aci_gatt_clt_read_multiple_var_len_char_value_api(Connection_Handle,
                                                             CID,
                                                             Number_of_Handles,
                                                             Handle_Entry);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_write_without_resp(uint16_t Connection_Handle,
                                           uint16_t CID,
                                           uint16_t Attr_Handle,
                                           uint16_t Attribute_Val_Length,
                                           uint8_t* Attribute_Val)
{
    return aci_gatt_clt_write_without_resp_api(Connection_Handle,
                                               CID,
                                               Attr_Handle,
                                               Attribute_Val_Length,
                                               Attribute_Val);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_signed_write_without_resp(uint16_t Connection_Handle,
                                                  uint16_t Attr_Handle,
                                                  uint16_t Attribute_Val_Length,
                                                  uint8_t* Attribute_Val)
{
    return aci_gatt_clt_signed_write_without_resp_api(Connection_Handle,
                                                      Attr_Handle,
                                                      Attribute_Val_Length,
                                                      Attribute_Val);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_write(uint16_t Connection_Handle,
                              uint16_t CID,
                              uint16_t Attr_Handle,
                              uint16_t Attribute_Val_Length,
                              uint8_t* Attribute_Val)
{
    return aci_gatt_clt_write_api(Connection_Handle,
                                  CID,
                                  Attr_Handle,
                                  Attribute_Val_Length,
                                  Attribute_Val);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_write_long(uint16_t Connection_Handle,
                                   uint16_t CID,
                                   ble_gatt_clt_write_ops_t* Write_Ops_p)
{
    return aci_gatt_clt_write_long_api(Connection_Handle,
                                       CID,
                                       Write_Ops_p);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_write_char_reliable(uint16_t Connection_Handle,
                                            uint16_t CID,
                                            uint8_t Num_Attrs,
                                            ble_gatt_clt_write_ops_t* Write_Ops_p)
{
    return aci_gatt_clt_write_char_reliable_api(Connection_Handle,
                                                CID,
                                                Num_Attrs,
                                                Write_Ops_p);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_prepare_write_req(uint16_t Connection_Handle,
                                          uint16_t CID,
                                          uint16_t Attr_Handle,
                                          uint16_t Val_Offset,
                                          uint16_t Attribute_Val_Length,
                                          uint8_t* Attribute_Val)
{
    return aci_gatt_clt_prepare_write_req_api(Connection_Handle,
                                              CID,
                                              Attr_Handle,
                                              Val_Offset,
                                              Attribute_Val_Length,
                                              Attribute_Val);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_execute_write_req(uint16_t Connection_Handle,
                                          uint16_t CID,
                                          uint8_t Execute)
{
    return aci_gatt_clt_execute_write_req_api(Connection_Handle,
                                              CID,
                                              Execute);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_gatt_clt_confirm_indication(uint16_t Connection_Handle,
                                           uint16_t CID)
{
    return aci_gatt_clt_confirm_indication_api(Connection_Handle,
                                               CID);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (CONNECTION_ENABLED == 1)
tBleStatus aci_hal_peripheral_latency_enable(uint16_t Connection_Handle,
                                             uint8_t Enable)
{
    return aci_hal_peripheral_latency_enable_api(Connection_Handle,
                                                 Enable);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus aci_hal_set_le_power_control(uint8_t Enable,
                                        uint8_t PHY,
                                        int8_t RSSI_Target,
                                        uint8_t RSSI_Hysteresis,
                                        int8_t Initial_TX_Power,
                                        uint8_t RSSI_Filtering_Coefficient)
{
    return aci_hal_set_le_power_control_api(Enable,
                                            PHY,
                                            RSSI_Target,
                                            RSSI_Hysteresis,
                                            Initial_TX_Power,
                                            RSSI_Filtering_Coefficient);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (CONNECTION_ENABLED == 1)
tBleStatus aci_hal_get_anchor_point(uint16_t connection_handle,
                                    uint16_t* event_counter,
                                    uint32_t* anchor_point)
{
    return aci_hal_get_anchor_point_api(connection_handle,
                                        event_counter,
                                        anchor_point);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (CONNECTION_ENABLED == 1)
tBleStatus aci_l2cap_connection_parameter_update_req(uint16_t Connection_Handle,
                                                     uint16_t Connection_Interval_Min,
                                                     uint16_t Connection_Interval_Max,
                                                     uint16_t Peripheral_Latency,
                                                     uint16_t Timeout_Multiplier)
{
    return aci_l2cap_connection_parameter_update_req_api(Connection_Handle,
                                                         Connection_Interval_Min,
                                                         Connection_Interval_Max,
                                                         Peripheral_Latency,
                                                         Timeout_Multiplier);
}
#endif /* (CONNECTION_ENABLED == 1) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
tBleStatus aci_l2cap_connection_parameter_update_resp(uint16_t Connection_Handle,
                                                      uint16_t Connection_Interval_Min,
                                                      uint16_t Connection_Interval_Max,
                                                      uint16_t Peripheral_Latency,
                                                      uint16_t Timeout_Multiplier,
                                                      uint16_t Min_CE_Length,
                                                      uint16_t Max_CE_Length,
                                                      uint8_t Identifier,
                                                      uint8_t Accept)
{
    return aci_l2cap_connection_parameter_update_resp_api(Connection_Handle,
                                                          Connection_Interval_Min,
                                                          Connection_Interval_Max,
                                                          Peripheral_Latency,
                                                          Timeout_Multiplier,
                                                          Min_CE_Length,
                                                          Max_CE_Length,
                                                          Identifier,
                                                          Accept);
}
#endif
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus aci_l2cap_cos_connection_req(uint16_t connection_handle,
                                        uint16_t spsm,
                                        uint16_t mtu,
                                        uint16_t mps,
                                        uint8_t channel_type,
                                        uint8_t cid_count)
{
    return aci_l2cap_cos_connection_req_api(connection_handle,
                                            spsm,
                                            mtu,
                                            mps,
                                            channel_type,
                                            cid_count);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus aci_l2cap_cos_connection_resp(uint16_t connection_handle,
                                         uint8_t identifier,
                                         uint16_t mtu,
                                         uint16_t mps,
                                         uint16_t result,
                                         uint8_t cid_count,
                                         uint16_t* local_cid)
{
    return aci_l2cap_cos_connection_resp_api(connection_handle,
                                             identifier,
                                             mtu,
                                             mps,
                                             result,
                                             cid_count,
                                             local_cid);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus aci_l2cap_cos_disconnect_req(uint16_t Connection_Handle,
                                        uint16_t CID)
{
    return aci_l2cap_cos_disconnect_req_api(Connection_Handle,
                                            CID);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus aci_l2cap_cos_reconfigure_req(uint16_t connection_handle,
                                         uint16_t mtu,
                                         uint16_t mps,
                                         uint8_t cid_count,
                                         uint16_t* local_cid_array)
{
    return aci_l2cap_cos_reconfigure_req_api(connection_handle,
                                             mtu,
                                             mps,
                                             cid_count,
                                             local_cid_array);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus aci_l2cap_cos_reconfigure_resp(uint16_t connection_handle,
                                          uint8_t identifier,
                                          uint16_t result)
{
    return aci_l2cap_cos_reconfigure_resp_api(connection_handle,
                                              identifier,
                                              result);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus aci_l2cap_cos_sdu_data_transmit(uint16_t Connection_Handle,
                                           uint16_t CID,
                                           uint16_t SDU_Length,
                                           uint8_t* SDU_Data)
{
    return aci_l2cap_cos_sdu_data_transmit_api(Connection_Handle,
                                               CID,
                                               SDU_Length,
                                               SDU_Data);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (BLESTACK_CONTROLLER_ONLY == 0)
#if ((L2CAP_COS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus aci_l2cap_cos_sdu_data_extract(uint16_t Connection_Handle,
                                          uint16_t CID,
                                          uint16_t SDU_Data_Buffer_Size,
                                          void* SDU_Data_Buffer,
                                          uint16_t* SDU_Length)
{
    return aci_l2cap_cos_sdu_data_extract_api(Connection_Handle,
                                              CID,
                                              SDU_Data_Buffer_Size,
                                              SDU_Data_Buffer,
                                              SDU_Length);
}
#endif /* ((L2CAP_COS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus hci_le_read_buffer_size_v2(uint16_t* HC_LE_ACL_Data_Packet_Length,
                                      uint8_t* HC_Total_Num_LE_ACL_Data_Packets,
                                      uint16_t* HC_LE_ISO_Data_Packet_Length,
                                      uint8_t* HC_Total_Num_LE_ISO_Data_Packets)
{
    return hci_le_read_buffer_size_v2_api(HC_LE_ACL_Data_Packet_Length,
                                          HC_Total_Num_LE_ACL_Data_Packets,
                                          HC_LE_ISO_Data_Packet_Length,
                                          HC_Total_Num_LE_ISO_Data_Packets);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus hci_le_create_big_test(uint8_t big_handle,
                                  uint8_t advertising_handle,
                                  uint8_t num_bis,
                                  uint8_t* sdu_interval_us,
                                  uint16_t iso_interval_1_25ms,
                                  uint8_t nse,
                                  uint16_t max_sdu,
                                  uint16_t max_pdu,
                                  uint8_t phy,
                                  uint8_t packing_interleaved,
                                  uint8_t framing,
                                  uint8_t bn,
                                  uint8_t irc,
                                  uint8_t pto,
                                  uint8_t encryption,
                                  uint8_t* broadcast_code_ext)
{
    return hci_le_create_big_test_api(big_handle,
                                      advertising_handle,
                                      num_bis,
                                      sdu_interval_us,
                                      iso_interval_1_25ms,
                                      nse,
                                      max_sdu,
                                      max_pdu,
                                      phy,
                                      packing_interleaved,
                                      framing,
                                      bn,
                                      irc,
                                      pto,
                                      encryption,
                                      broadcast_code_ext);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_big_create_sync(uint8_t BIG_Handle,
                                  uint16_t Sync_Handle,
                                  uint8_t Encryption,
                                  uint8_t* Broadcast_Code,
                                  uint8_t MSE,
                                  uint16_t BIG_Sync_Timeout,
                                  uint8_t Num_BIS,
                                  uint8_t* BIS)
{
    return hci_le_big_create_sync_api(BIG_Handle,
                                      Sync_Handle,
                                      Encryption,
                                      Broadcast_Code,
                                      MSE,
                                      BIG_Sync_Timeout,
                                      Num_BIS,
                                      BIS);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus hci_le_terminate_big(uint8_t Terminate_Big,
                                uint8_t Reason)
{
    return hci_le_terminate_big_api(Terminate_Big,
                                    Reason);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_big_terminate_sync(uint8_t Big_handle)
{
    return hci_le_big_terminate_sync_api(Big_handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_BIS_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus hci_le_create_big(uint8_t big_handle,
                             uint8_t advertising_handle,
                             uint8_t num_bis,
                             uint8_t* sdu_interval_us,
                             uint16_t max_sdu,
                             uint16_t Max_Transport_Latency,
                             uint8_t RTN,
                             uint8_t phy,
                             uint8_t packing_interleaved,
                             uint8_t framing,
                             uint8_t encryption,
                             uint8_t* broadcast_code_ext)
{
    return hci_le_create_big_api(big_handle,
                                 advertising_handle,
                                 num_bis,
                                 sdu_interval_us,
                                 max_sdu,
                                 Max_Transport_Latency,
                                 RTN,
                                 phy,
                                 packing_interleaved,
                                 framing,
                                 encryption,
                                 broadcast_code_ext);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_BIS_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus hci_read_afh_channel_assessment_mode(uint8_t* AFH_Channel_Assessment_Mode)
{
    return hci_read_afh_channel_assessment_mode_api(AFH_Channel_Assessment_Mode);
}
#endif /* ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus hci_write_afh_channel_assessment_mode(uint8_t AFH_Channel_Assessment_Mode)
{
    return hci_write_afh_channel_assessment_mode_api(AFH_Channel_Assessment_Mode);
}
#endif /* ((CONTROLLER_CHAN_CLASS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (\
     (\
      (CONNECTION_ENABLED == 1)\
      &&\
      (\
       (CONTROLLER_SCAN_ENABLED == 1)\
       ||\
       (CONTROLLER_CHAN_CLASS_ENABLED == 1)\
      )\
     )\
     ||\
     (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)\
    )
tBleStatus hci_le_set_host_channel_classification(uint8_t Channel_Map[LLC_MIN_NUM_DATA_CHAN_MAP_BYTES])
{
    return hci_le_set_host_channel_classification_api(Channel_Map);
}
#endif

#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONNECTION_ENABLED == 1) &&\
      (CONTROLLER_CIS_ENABLED == 1) &&\
      (CONTROLLER_ISO_ENABLED == 1)\
     )\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
tBleStatus hci_le_set_cig_parameters(uint8_t CIG_ID,
                                     uint8_t SDU_Interval_C_To_P[3],
                                     uint8_t SDU_Interval_P_To_C[3],
                                     uint8_t Worst_Case_SCA,
                                     uint8_t Packing,
                                     uint8_t Framing,
                                     uint16_t Max_Transport_Latency_C_To_P,
                                     uint16_t Max_Transport_Latency_P_To_C,
                                     uint8_t CIS_Count,
                                     CIS_Param_t* CIS_params,
                                     uint16_t* CIS_Conn_Handles)
{
    return hci_le_set_cig_parameters_api(CIG_ID,
                                         SDU_Interval_C_To_P,
                                         SDU_Interval_P_To_C,
                                         Worst_Case_SCA,
                                         Packing,
                                         Framing,
                                         Max_Transport_Latency_C_To_P,
                                         Max_Transport_Latency_P_To_C,
                                         CIS_Count,
                                         CIS_params,
                                         CIS_Conn_Handles);
}
#endif

#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONNECTION_ENABLED == 1) &&\
      (CONTROLLER_CIS_ENABLED == 1) &&\
      (CONTROLLER_ISO_ENABLED == 1)\
     )\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
tBleStatus hci_le_set_cig_parameters_test(uint8_t CIG_ID,
                                          uint8_t SDU_Interval_C_To_P[3],
                                          uint8_t SDU_Interval_P_To_C[3],
                                          uint8_t FT_C_To_P,
                                          uint8_t FT_P_To_C,
                                          uint16_t ISO_Interval,
                                          uint8_t Worst_Case_SCA,
                                          uint8_t Packing,
                                          uint8_t Framing,
                                          uint8_t CIS_Count,
                                          CIS_Param_Test_t* CIS_Param_test,
                                          uint16_t* CIS_Conn_Handles)
{
    return hci_le_set_cig_parameters_test_api(CIG_ID,
                                              SDU_Interval_C_To_P,
                                              SDU_Interval_P_To_C,
                                              FT_C_To_P,
                                              FT_P_To_C,
                                              ISO_Interval,
                                              Worst_Case_SCA,
                                              Packing,
                                              Framing,
                                              CIS_Count,
                                              CIS_Param_test,
                                              CIS_Conn_Handles);
}
#endif

#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONNECTION_ENABLED == 1) &&\
      (CONTROLLER_CIS_ENABLED == 1) &&\
      (CONTROLLER_ISO_ENABLED == 1)\
     )\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
tBleStatus hci_le_create_cis(uint8_t CIS_Count,
                             CIS_Handles_t* create_cis_connection_params)
{
    return hci_le_create_cis_api(CIS_Count,
                                 create_cis_connection_params);
}
#endif

#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONNECTION_ENABLED == 1) &&\
      (CONTROLLER_CIS_ENABLED == 1) &&\
      (CONTROLLER_ISO_ENABLED == 1)\
     )\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
tBleStatus hci_le_remove_cig(uint8_t CIG_ID)
{
    return hci_le_remove_cig_api(CIG_ID);
}
#endif

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus hci_le_accept_cis_request(uint16_t Connection_Handle)
{
    return hci_le_accept_cis_request_api(Connection_Handle);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus hci_le_reject_cis_request(uint16_t Connection_Handle,
                                     uint8_t Reason)
{
    return hci_le_reject_cis_request_api(Connection_Handle,
                                         Reason);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus hci_read_connection_accept_timeout(uint16_t* Connection_Accept_Timeout)
{
    return hci_read_connection_accept_timeout_api(Connection_Accept_Timeout);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus hci_write_connection_accept_timeout(uint16_t Connection_Accept_Timeout)
{
    return hci_write_connection_accept_timeout_api(Connection_Accept_Timeout);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) ||\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_set_host_feature(uint8_t Bit_Number,
                                   uint8_t Bit_Value)
{
    return hci_le_set_host_feature_api(Bit_Number,
                                       Bit_Value);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) ||\
          (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_read_remote_version_information(uint16_t Connection_Handle)
{
    return hci_read_remote_version_information_api(Connection_Handle);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_read_remote_features(uint16_t Connection_Handle)
{
    return hci_le_read_remote_features_api(Connection_Handle);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_read_transmit_power_level(uint16_t Connection_Handle,
                                         uint8_t Type,
                                         int8_t* Transmit_Power_Level)
{
    return hci_read_transmit_power_level_api(Connection_Handle,
                                             Type,
                                             Transmit_Power_Level);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_read_rssi(uint16_t Connection_Handle,
                         int8_t* RSSI)
{
    return hci_read_rssi_api(Connection_Handle,
                             RSSI);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_read_channel_map(uint16_t Connection_Handle,
                                   uint8_t LE_Channel_Map[LLC_MIN_NUM_DATA_CHAN_MAP_BYTES])
{
    return hci_le_read_channel_map_api(Connection_Handle,
                                       LE_Channel_Map);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_disconnect(uint16_t Connection_Handle,
                          uint8_t Reason)
{
    return hci_disconnect_api(Connection_Handle,
                              Reason);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_create_connection(uint16_t LE_Scan_Interval,
                                    uint16_t LE_Scan_Window,
                                    uint8_t Initiator_Filter_Policy,
                                    uint8_t Peer_Address_Type,
                                    uint8_t Peer_Address[6],
                                    uint8_t Own_Address_Type,
                                    uint16_t Connection_Interval_Min,
                                    uint16_t Connection_Interval_Max,
                                    uint16_t Max_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Min_CE_Length,
                                    uint16_t Max_CE_Length)
{
    return hci_le_create_connection_api(LE_Scan_Interval,
                                        LE_Scan_Window,
                                        Initiator_Filter_Policy,
                                        Peer_Address_Type,
                                        Peer_Address,
                                        Own_Address_Type,
                                        Connection_Interval_Min,
                                        Connection_Interval_Max,
                                        Max_Latency,
                                        Supervision_Timeout,
                                        Min_CE_Length,
                                        Max_CE_Length);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_create_connection_cancel(void)
{
    return hci_le_create_connection_cancel_api();
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_extended_create_connection(uint8_t Initiator_Filter_Policy,
                                             uint8_t Own_Address_Type,
                                             uint8_t Peer_Address_Type,
                                             uint8_t Peer_Address[6],
                                             uint8_t Initiating_PHYs,
                                             Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters)
{
    return hci_le_extended_create_connection_api(Initiator_Filter_Policy,
                                                 Own_Address_Type,
                                                 Peer_Address_Type,
                                                 Peer_Address,
                                                 Initiating_PHYs,
                                                 Extended_Create_Connection_Parameters);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_extended_create_connection_v2(uint8_t Advertising_Handle,
                                                uint8_t Subevent,
                                                uint8_t Initiator_Filter_Policy,
                                                uint8_t Own_Address_Type,
                                                uint8_t Peer_Address_Type,
                                                uint8_t Peer_Address[6],
                                                uint8_t Initiating_PHYs,
                                                Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters)
{
    return hci_le_extended_create_connection_v2_api(Advertising_Handle,
                                                    Subevent,
                                                    Initiator_Filter_Policy,
                                                    Own_Address_Type,
                                                    Peer_Address_Type,
                                                    Peer_Address,
                                                    Initiating_PHYs,
                                                    Extended_Create_Connection_Parameters);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_set_connectionless_cte_transmit_parameters(uint8_t Advertising_Handle,
                                                             uint8_t CTE_Length,
                                                             uint8_t CTE_Type,
                                                             uint8_t CTE_Count,
                                                             uint8_t Switching_Pattern_Length,
                                                             uint8_t* Antenna_IDs)
{
    return hci_le_set_connectionless_cte_transmit_parameters_api(Advertising_Handle,
                                                                 CTE_Length,
                                                                 CTE_Type,
                                                                 CTE_Count,
                                                                 Switching_Pattern_Length,
                                                                 Antenna_IDs);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_set_connectionless_cte_transmit_enable(uint8_t Advertising_Handle,
                                                         uint8_t CTE_Enable)
{
    return hci_le_set_connectionless_cte_transmit_enable_api(Advertising_Handle,
                                                             CTE_Enable);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_set_connectionless_iq_sampling_enable(uint16_t Sync_Handle,
                                                        uint8_t Sampling_Enable,
                                                        uint8_t Slot_Durations,
                                                        uint8_t Max_Sampled_CTEs,
                                                        uint8_t Switching_Pattern_Length,
                                                        uint8_t* Antenna_IDs)
{
    return hci_le_set_connectionless_iq_sampling_enable_api(Sync_Handle,
                                                            Sampling_Enable,
                                                            Slot_Durations,
                                                            Max_Sampled_CTEs,
                                                            Switching_Pattern_Length,
                                                            Antenna_IDs);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_set_connection_cte_receive_parameters(uint16_t Connection_Handle,
                                                        uint8_t Sampling_Enable,
                                                        uint8_t Slot_Durations,
                                                        uint8_t Switching_Pattern_Length,
                                                        uint8_t* Antenna_IDs)
{
    return hci_le_set_connection_cte_receive_parameters_api(Connection_Handle,
                                                            Sampling_Enable,
                                                            Slot_Durations,
                                                            Switching_Pattern_Length,
                                                            Antenna_IDs);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_set_connection_cte_transmit_parameters(uint16_t Connection_Handle,
                                                         uint8_t CTE_Type,
                                                         uint8_t Switching_Pattern_Length,
                                                         uint8_t* Antenna_IDs)
{
    return hci_le_set_connection_cte_transmit_parameters_api(Connection_Handle,
                                                             CTE_Type,
                                                             Switching_Pattern_Length,
                                                             Antenna_IDs);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_connection_cte_request_enable(uint16_t Connection_Handle,
                                                uint8_t Enable,
                                                uint16_t CTE_Request_Interval,
                                                uint8_t Requested_CTE_Length,
                                                uint8_t Requested_CTE_Type)
{
    return hci_le_connection_cte_request_enable_api(Connection_Handle,
                                                    Enable,
                                                    CTE_Request_Interval,
                                                    Requested_CTE_Length,
                                                    Requested_CTE_Type);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_connection_cte_response_enable(uint16_t Connection_Handle,
                                                 uint8_t Enable)
{
    return hci_le_connection_cte_response_enable_api(Connection_Handle,
                                                     Enable);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_read_antenna_information(uint8_t* Supported_Switching_Sampling_Rates,
                                           uint8_t* Num_Antennae,
                                           uint8_t* Max_Switching_Pattern_Length,
                                           uint8_t* Max_CTE_Length)
{
    return hci_le_read_antenna_information_api(Supported_Switching_Sampling_Rates,
                                               Num_Antennae,
                                               Max_Switching_Pattern_Length,
                                               Max_CTE_Length);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (\
     (CONNECTION_ENABLED == 1)\
     &&\
     (\
      (CONTROLLER_SCAN_ENABLED == 1)\
      ||\
      (\
       (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
       (CONNECTION_ENABLED == 1) &&\
       (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)\
      )\
     )\
    )
tBleStatus hci_le_enable_encryption(uint16_t Connection_Handle,
                                    uint8_t Random_Number[8],
                                    uint16_t Encrypted_Diversifier,
                                    uint8_t Long_Term_Key[16])
{
    return hci_le_enable_encryption_api(Connection_Handle,
                                        Random_Number,
                                        Encrypted_Diversifier,
                                        Long_Term_Key);
}
#endif

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_long_term_key_request_reply(uint16_t Connection_Handle,
                                              uint8_t Long_Term_Key[16])
{
    return hci_le_long_term_key_request_reply_api(Connection_Handle,
                                                  Long_Term_Key);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_long_term_key_request_negative_reply(uint16_t Connection_Handle)
{
    return hci_le_long_term_key_request_negative_reply_api(Connection_Handle);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_read_local_p256_public_key(void)
{
    return hci_le_read_local_p256_public_key_api();
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_generate_dhkey(uint8_t Remote_P256_Public_Key[64])
{
    return hci_le_generate_dhkey_api(Remote_P256_Public_Key);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_read_authenticated_payload_timeout(uint16_t Connection_Handle,
                                                  uint16_t* Authenticated_Payload_Timeout)
{
    return hci_read_authenticated_payload_timeout_api(Connection_Handle,
                                                      Authenticated_Payload_Timeout);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_write_authenticated_payload_timeout(uint16_t Connection_Handle,
                                                   uint16_t Authenticated_Payload_Timeout)
{
    return hci_write_authenticated_payload_timeout_api(Connection_Handle,
                                                       Authenticated_Payload_Timeout);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_extended_advertising_parameters(uint8_t Advertising_Handle,
                                                      uint16_t Advertising_Event_Properties,
                                                      uint8_t Primary_Advertising_Interval_Min[3],
                                                      uint8_t Primary_Advertising_Interval_Max[3],
                                                      uint8_t Primary_Advertising_Channel_Map,
                                                      uint8_t Own_Address_Type,
                                                      uint8_t Peer_Address_Type,
                                                      uint8_t Peer_Address[6],
                                                      uint8_t Advertising_Filter_Policy,
                                                      int8_t Advertising_Tx_Power,
                                                      uint8_t Primary_Advertising_PHY,
                                                      uint8_t Secondary_Advertising_Max_Skip,
                                                      uint8_t Secondary_Advertising_PHY,
                                                      uint8_t Advertising_SID,
                                                      uint8_t Scan_Request_Notification_Enable,
                                                      int8_t* Selected_Tx_Power)
{
    return hci_le_set_extended_advertising_parameters_api(Advertising_Handle,
                                                          Advertising_Event_Properties,
                                                          Primary_Advertising_Interval_Min,
                                                          Primary_Advertising_Interval_Max,
                                                          Primary_Advertising_Channel_Map,
                                                          Own_Address_Type,
                                                          Peer_Address_Type,
                                                          Peer_Address,
                                                          Advertising_Filter_Policy,
                                                          Advertising_Tx_Power,
                                                          Primary_Advertising_PHY,
                                                          Secondary_Advertising_Max_Skip,
                                                          Secondary_Advertising_PHY,
                                                          Advertising_SID,
                                                          Scan_Request_Notification_Enable,
                                                          Selected_Tx_Power);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_extended_advertising_parameters_v2(uint8_t Advertising_Handle,
                                                         uint16_t Advertising_Event_Properties,
                                                         uint8_t Primary_Advertising_Interval_Min[3],
                                                         uint8_t Primary_Advertising_Interval_Max[3],
                                                         uint8_t Primary_Advertising_Channel_Map,
                                                         uint8_t Own_Address_Type,
                                                         uint8_t Peer_Address_Type,
                                                         uint8_t Peer_Address[6],
                                                         uint8_t Advertising_Filter_Policy,
                                                         int8_t Advertising_Tx_Power,
                                                         uint8_t Primary_Advertising_PHY,
                                                         uint8_t Secondary_Advertising_Max_Skip,
                                                         uint8_t Secondary_Advertising_PHY,
                                                         uint8_t Advertising_SID,
                                                         uint8_t Scan_Request_Notification_Enable,
                                                         uint8_t Primary_Advertising_PHY_Options,
                                                         uint8_t Secondary_Advertising_PHY_Options,
                                                         int8_t* Selected_Tx_Power)
{
    return hci_le_set_extended_advertising_parameters_v2_api(Advertising_Handle,
                                                             Advertising_Event_Properties,
                                                             Primary_Advertising_Interval_Min,
                                                             Primary_Advertising_Interval_Max,
                                                             Primary_Advertising_Channel_Map,
                                                             Own_Address_Type,
                                                             Peer_Address_Type,
                                                             Peer_Address,
                                                             Advertising_Filter_Policy,
                                                             Advertising_Tx_Power,
                                                             Primary_Advertising_PHY,
                                                             Secondary_Advertising_Max_Skip,
                                                             Secondary_Advertising_PHY,
                                                             Advertising_SID,
                                                             Scan_Request_Notification_Enable,
                                                             Primary_Advertising_PHY_Options,
                                                             Secondary_Advertising_PHY_Options,
                                                             Selected_Tx_Power);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_advertising_set_random_address(uint8_t Advertising_Handle,
                                                     uint8_t Advertising_Random_Address[6])
{
    return hci_le_set_advertising_set_random_address_api(Advertising_Handle,
                                                         Advertising_Random_Address);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_extended_advertising_enable(uint8_t Enable,
                                                  uint8_t Number_of_Sets,
                                                  Advertising_Set_Parameters_t* Advertising_Set_Parameters)
{
    return hci_le_set_extended_advertising_enable_api(Enable,
                                                      Number_of_Sets,
                                                      Advertising_Set_Parameters);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_read_number_of_supported_advertising_sets(uint8_t* Num_Supported_Advertising_Sets)
{
    return hci_le_read_number_of_supported_advertising_sets_api(Num_Supported_Advertising_Sets);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_remove_advertising_set(uint8_t Advertising_Handle)
{
    return hci_le_remove_advertising_set_api(Advertising_Handle);
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_clear_advertising_sets(void)
{
    return hci_le_clear_advertising_sets_api();
}
#endif /* (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_set_default_periodic_advertising_sync_transfer_parameters(uint8_t Mode,
                                                                            uint16_t Skip,
                                                                            uint16_t Sync_Timeout,
                                                                            uint8_t CTE_Type)
{
    return hci_le_set_default_periodic_advertising_sync_transfer_parameters_api(Mode,
                                                                                Skip,
                                                                                Sync_Timeout,
                                                                                CTE_Type);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_set_periodic_advertising_sync_transfer_parameters(uint16_t Connection_Handle,
                                                                    uint8_t Mode,
                                                                    uint16_t Skip,
                                                                    uint16_t Sync_Timeout,
                                                                    uint8_t CTE_Type)
{
    return hci_le_set_periodic_advertising_sync_transfer_parameters_api(Connection_Handle,
                                                                        Mode,
                                                                        Skip,
                                                                        Sync_Timeout,
                                                                        CTE_Type);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_periodic_advertising_set_info_transfer(uint16_t Connection_Handle,
                                                         uint16_t Service_Data,
                                                         uint8_t Advertising_Handle)
{
    return hci_le_periodic_advertising_set_info_transfer_api(Connection_Handle,
                                                             Service_Data,
                                                             Advertising_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_periodic_advertising_sync_transfer(uint16_t Connection_Handle,
                                                     uint16_t Service_Data,
                                                     uint16_t Sync_Handle)
{
    return hci_le_periodic_advertising_sync_transfer_api(Connection_Handle,
                                                         Service_Data,
                                                         Sync_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus hci_le_iso_transmit_test(uint16_t Connection_Handle,
                                    uint8_t Payload_Type)
{
    return hci_le_iso_transmit_test_api(Connection_Handle,
                                        Payload_Type);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus hci_le_iso_receive_test(uint16_t Connection_Handle,
                                   uint8_t Payload_Type)
{
    return hci_le_iso_receive_test_api(Connection_Handle,
                                       Payload_Type);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus hci_le_iso_read_test_counters(uint16_t Connection_Handle,
                                         uint32_t* Received_Packet_Count,
                                         uint32_t* Missed_Packet_Count,
                                         uint32_t* Failed_Packet_Count)
{
    return hci_le_iso_read_test_counters_api(Connection_Handle,
                                             Received_Packet_Count,
                                             Missed_Packet_Count,
                                             Failed_Packet_Count);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus hci_le_iso_test_end(uint16_t Connection_Handle,
                               uint32_t* Received_Packet_Count,
                               uint32_t* Missed_Packet_Count,
                               uint32_t* Failed_Packet_Count)
{
    return hci_le_iso_test_end_api(Connection_Handle,
                                   Received_Packet_Count,
                                   Missed_Packet_Count,
                                   Failed_Packet_Count);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus hci_le_setup_iso_data_path(uint16_t Connection_Handle,
                                      uint8_t Data_Path_Direction,
                                      uint8_t Data_Path_ID,
                                      uint8_t* CODEC_ID,
                                      uint8_t* Controller_Delay,
                                      uint8_t Codec_Configuration_Length,
                                      uint8_t* Codec_Configuration)
{
    return hci_le_setup_iso_data_path_api(Connection_Handle,
                                          Data_Path_Direction,
                                          Data_Path_ID,
                                          CODEC_ID,
                                          Controller_Delay,
                                          Codec_Configuration_Length,
                                          Codec_Configuration);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus hci_le_remove_iso_data_path(uint16_t Connection_Handle,
                                       uint8_t Data_Path_Direction)
{
    return hci_le_remove_iso_data_path_api(Connection_Handle,
                                           Data_Path_Direction);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus hci_le_read_iso_link_quality(uint16_t connection_handle,
                                        uint32_t* tx_unacked_packets,
                                        uint32_t* tx_flushed_packets,
                                        uint32_t* tx_last_subevent_packets,
                                        uint32_t* retransmitted_packets,
                                        uint32_t* CRC_error_packets,
                                        uint32_t* rx_unreceived_packets,
                                        uint32_t* duplicate_packets)
{
    return hci_le_read_iso_link_quality_api(connection_handle,
                                            tx_unacked_packets,
                                            tx_flushed_packets,
                                            tx_last_subevent_packets,
                                            retransmitted_packets,
                                            CRC_error_packets,
                                            rx_unreceived_packets,
                                            duplicate_packets);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus hci_le_read_iso_tx_sync(uint16_t connection_handle,
                                   uint16_t* packet_sequence_number,
                                   uint32_t* timestamp,
                                   uint8_t* timeoffset)
{
    return hci_le_read_iso_tx_sync_api(connection_handle,
                                       packet_sequence_number,
                                       timestamp,
                                       timeoffset);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_ISO_ENABLED == 1)
tBleStatus hci_tx_iso_data(uint16_t connection_handle,
                           uint8_t pb_flag,
                           uint8_t ts_flag,
                           uint16_t iso_data_load_len,
                           uint8_t* iso_data_load_p)
{
    return hci_tx_iso_data_api(connection_handle,
                               pb_flag,
                               ts_flag,
                               iso_data_load_len,
                               iso_data_load_p);
}
#endif /* (CONTROLLER_ISO_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_set_data_length(uint16_t Connection_Handle,
                                  uint16_t Tx_Octets,
                                  uint16_t Tx_Time)
{
    return hci_le_set_data_length_api(Connection_Handle,
                                      Tx_Octets,
                                      Tx_Time);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_read_suggested_default_data_length(uint16_t* Suggested_Max_Tx_Octets,
                                                     uint16_t* Suggested_Max_Tx_Time)
{
    return hci_le_read_suggested_default_data_length_api(Suggested_Max_Tx_Octets,
                                                         Suggested_Max_Tx_Time);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_write_suggested_default_data_length(uint16_t Suggested_Max_Tx_Octets,
                                                      uint16_t Suggested_Max_Tx_Time)
{
    return hci_le_write_suggested_default_data_length_api(Suggested_Max_Tx_Octets,
                                                          Suggested_Max_Tx_Time);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_read_maximum_data_length(uint16_t* Supported_Max_Tx_Octets,
                                           uint16_t* Supported_Max_Tx_Time,
                                           uint16_t* Supported_Max_Rx_Octets,
                                           uint16_t* Supported_Max_Rx_Time)
{
    return hci_le_read_maximum_data_length_api(Supported_Max_Tx_Octets,
                                               Supported_Max_Tx_Time,
                                               Supported_Max_Rx_Octets,
                                               Supported_Max_Rx_Time);
}
#endif /* (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_periodic_advertising_parameters(uint8_t Advertising_Handle,
                                                      uint16_t Periodic_Advertising_Interval_Min,
                                                      uint16_t Periodic_Advertising_Interval_Max,
                                                      uint16_t Periodic_Advertising_Properties)
{
    return hci_le_set_periodic_advertising_parameters_api(Advertising_Handle,
                                                          Periodic_Advertising_Interval_Min,
                                                          Periodic_Advertising_Interval_Max,
                                                          Periodic_Advertising_Properties);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_periodic_advertising_enable(uint8_t Enable,
                                                  uint8_t Advertising_Handle)
{
    return hci_le_set_periodic_advertising_enable_api(Enable,
                                                      Advertising_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_set_periodic_advertising_parameters_v2(uint8_t Advertising_Handle,
                                                         uint16_t Periodic_Advertising_Interval_Min,
                                                         uint16_t Periodic_Advertising_Interval_Max,
                                                         uint16_t Periodic_Advertising_Properties,
                                                         uint8_t Num_Subevents,
                                                         uint8_t Subevent_Interval,
                                                         uint8_t Response_Slot_Delay,
                                                         uint8_t Response_Slot_Spacing,
                                                         uint8_t Num_Response_Slots)
{
    return hci_le_set_periodic_advertising_parameters_v2_api(Advertising_Handle,
                                                             Periodic_Advertising_Interval_Min,
                                                             Periodic_Advertising_Interval_Max,
                                                             Periodic_Advertising_Properties,
                                                             Num_Subevents,
                                                             Subevent_Interval,
                                                             Response_Slot_Delay,
                                                             Response_Slot_Spacing,
                                                             Num_Response_Slots);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus hci_le_enhanced_read_transmit_power_level(uint16_t Connection_Handle,
                                                     uint8_t PHY,
                                                     int8_t* Current_TX_Power_Level,
                                                     int8_t* Max_TX_Power_Level)
{
    return hci_le_enhanced_read_transmit_power_level_api(Connection_Handle,
                                                         PHY,
                                                         Current_TX_Power_Level,
                                                         Max_TX_Power_Level);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus hci_le_read_remote_transmit_power_level(uint16_t Connection_Handle,
                                                   uint8_t PHY)
{
    return hci_le_read_remote_transmit_power_level_api(Connection_Handle,
                                                       PHY);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus hci_le_set_path_loss_reporting_parameters(uint16_t Connection_Handle,
                                                     uint8_t High_Threshold,
                                                     uint8_t High_Hysteresis,
                                                     uint8_t Low_Threshold,
                                                     uint8_t Low_Hysteresis,
                                                     uint16_t Min_Time_Spent)
{
    return hci_le_set_path_loss_reporting_parameters_api(Connection_Handle,
                                                         High_Threshold,
                                                         High_Hysteresis,
                                                         Low_Threshold,
                                                         Low_Hysteresis,
                                                         Min_Time_Spent);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus hci_le_set_path_loss_reporting_enable(uint16_t Connection_Handle,
                                                 uint8_t Enable)
{
    return hci_le_set_path_loss_reporting_enable_api(Connection_Handle,
                                                     Enable);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus hci_le_set_transmit_power_reporting_enable(uint16_t Connection_Handle,
                                                      uint8_t Local_Enable,
                                                      uint8_t Remote_Enable)
{
    return hci_le_set_transmit_power_reporting_enable_api(Connection_Handle,
                                                          Local_Enable,
                                                          Remote_Enable);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_read_phy(uint16_t Connection_Handle,
                           uint8_t* TX_PHY,
                           uint8_t* RX_PHY)
{
    return hci_le_read_phy_api(Connection_Handle,
                               TX_PHY,
                               RX_PHY);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
tBleStatus hci_le_set_default_phy(uint8_t ALL_PHYS,
                                  uint8_t TX_PHYS,
                                  uint8_t RX_PHYS)
{
    return hci_le_set_default_phy_api(ALL_PHYS,
                                      TX_PHYS,
                                      RX_PHYS);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_set_phy(uint16_t Connection_Handle,
                          uint8_t ALL_PHYS,
                          uint8_t TX_PHYS,
                          uint8_t RX_PHYS,
                          uint16_t PHY_options)
{
    return hci_le_set_phy_api(Connection_Handle,
                              ALL_PHYS,
                              TX_PHYS,
                              RX_PHYS,
                              PHY_options);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_add_device_to_resolving_list(uint8_t Peer_Identity_Address_Type,
                                               uint8_t Peer_Identity_Address[6],
                                               uint8_t Peer_IRK[16],
                                               uint8_t Local_IRK[16])
{
    return hci_le_add_device_to_resolving_list_api(Peer_Identity_Address_Type,
                                                   Peer_Identity_Address,
                                                   Peer_IRK,
                                                   Local_IRK);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_remove_device_from_resolving_list(uint8_t Peer_Identity_Address_Type,
                                                    uint8_t Peer_Identity_Address[6])
{
    return hci_le_remove_device_from_resolving_list_api(Peer_Identity_Address_Type,
                                                        Peer_Identity_Address);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_clear_resolving_list(void)
{
    return hci_le_clear_resolving_list_api();
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_read_resolving_list_size(uint8_t* Resolving_List_Size)
{
    return hci_le_read_resolving_list_size_api(Resolving_List_Size);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_read_peer_resolvable_address(uint8_t Peer_Identity_Address_Type,
                                               uint8_t Peer_Identity_Address[6],
                                               uint8_t Peer_Resolvable_Address[6])
{
    return hci_le_read_peer_resolvable_address_api(Peer_Identity_Address_Type,
                                                   Peer_Identity_Address,
                                                   Peer_Resolvable_Address);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_read_local_resolvable_address(uint8_t Peer_Identity_Address_Type,
                                                uint8_t Peer_Identity_Address[6],
                                                uint8_t Local_Resolvable_Address[6])
{
    return hci_le_read_local_resolvable_address_api(Peer_Identity_Address_Type,
                                                    Peer_Identity_Address,
                                                    Local_Resolvable_Address);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_set_address_resolution_enable(uint8_t Address_Resolution_Enable)
{
    return hci_le_set_address_resolution_enable_api(Address_Resolution_Enable);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_set_resolvable_private_address_timeout(uint16_t RPA_Timeout)
{
    return hci_le_set_resolvable_private_address_timeout_api(RPA_Timeout);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_set_privacy_mode(uint8_t Peer_Identity_Address_Type,
                                   uint8_t Peer_Identity_Address[6],
                                   uint8_t Privacy_Mode)
{
    return hci_le_set_privacy_mode_api(Peer_Identity_Address_Type,
                                       Peer_Identity_Address,
                                       Privacy_Mode);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if (CONTROLLER_PRIVACY_ENABLED == 1)
tBleStatus hci_le_set_data_related_address_changes(uint8_t Advertising_Handle,
                                                   uint8_t Change_Reasons)
{
    return hci_le_set_data_related_address_changes_api(Advertising_Handle,
                                                       Change_Reasons);
}
#endif /* (CONTROLLER_PRIVACY_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_add_device_to_periodic_advertiser_list(uint8_t Advertiser_Address_Type,
                                                         uint8_t Advertiser_Address[6],
                                                         uint8_t Advertising_SID)
{
    return hci_le_add_device_to_periodic_advertiser_list_api(Advertiser_Address_Type,
                                                             Advertiser_Address,
                                                             Advertising_SID);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_clear_periodic_advertiser_list(void)
{
    return hci_le_clear_periodic_advertiser_list_api();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_periodic_advertising_create_sync(uint8_t Options,
                                                   uint8_t Advertising_SID,
                                                   uint8_t Advertising_Address_Type,
                                                   uint8_t Advertiser_Address[6],
                                                   uint16_t Skip,
                                                   uint16_t Sync_Timeout,
                                                   uint8_t Sync_CTE_Type)
{
    return hci_le_periodic_advertising_create_sync_api(Options,
                                                       Advertising_SID,
                                                       Advertising_Address_Type,
                                                       Advertiser_Address,
                                                       Skip,
                                                       Sync_Timeout,
                                                       Sync_CTE_Type);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_periodic_advertising_create_sync_cancel(void)
{
    return hci_le_periodic_advertising_create_sync_cancel_api();
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_periodic_advertising_terminate_sync(uint16_t Sync_Handle)
{
    return hci_le_periodic_advertising_terminate_sync_api(Sync_Handle);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_read_periodic_advertiser_list_size(uint8_t* Periodic_Advertiser_List_Size)
{
    return hci_le_read_periodic_advertiser_list_size_api(Periodic_Advertiser_List_Size);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_remove_device_from_periodic_advertiser_list(uint8_t Advertiser_Address_Type,
                                                              uint8_t Advertiser_Address[6],
                                                              uint8_t Advertising_SID)
{
    return hci_le_remove_device_from_periodic_advertiser_list_api(Advertiser_Address_Type,
                                                                  Advertiser_Address,
                                                                  Advertising_SID);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_set_periodic_advertising_receive_enable(uint16_t Sync_Handle,
                                                          uint8_t Enable)
{
    return hci_le_set_periodic_advertising_receive_enable_api(Sync_Handle,
                                                              Enable);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) */

#if ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
    (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
    (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1)
tBleStatus hci_le_set_periodic_sync_subevent(uint16_t Sync_Handle,
                                             uint16_t Periodic_Advertising_Properties,
                                             uint8_t Num_Subevents,
                                             uint8_t* Subevent)
{
    return hci_le_set_periodic_sync_subevent_api(Sync_Handle,
                                                 Periodic_Advertising_Properties,
                                                 Num_Subevents,
                                                 Subevent);
}
#endif /* ((CONTROLLER_PERIODIC_ADV_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) &&\
          (CONTROLLER_PERIODIC_ADV_WR_ENABLED == 1)) &&\
          (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) */

#if ((CONTROLLER_CIS_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1) &&\
    (CONTROLLER_ISO_ENABLED == 1))
tBleStatus hci_le_request_peer_sca(uint16_t Connection_Handle)
{
    return hci_le_request_peer_sca_api(Connection_Handle);
}
#endif /* ((CONTROLLER_CIS_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1) &&\
          (CONTROLLER_ISO_ENABLED == 1)) */

#if (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_set_scan_parameters(uint8_t LE_Scan_Type,
                                      uint16_t LE_Scan_Interval,
                                      uint16_t LE_Scan_Window,
                                      uint8_t Own_Address_Type,
                                      uint8_t Scanning_Filter_Policy)
{
    return hci_le_set_scan_parameters_api(LE_Scan_Type,
                                          LE_Scan_Interval,
                                          LE_Scan_Window,
                                          Own_Address_Type,
                                          Scanning_Filter_Policy);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1)
tBleStatus hci_le_set_scan_enable(uint8_t LE_Scan_Enable,
                                  uint8_t Filter_Duplicates)
{
    return hci_le_set_scan_enable_api(LE_Scan_Enable,
                                      Filter_Duplicates);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_extended_scan_parameters(uint8_t Own_Address_Type,
                                               uint8_t Scanning_Filter_Policy,
                                               uint8_t Scanning_PHYs,
                                               Extended_Scan_Parameters_t* Extended_Scan_Parameters)
{
    return hci_le_set_extended_scan_parameters_api(Own_Address_Type,
                                                   Scanning_Filter_Policy,
                                                   Scanning_PHYs,
                                                   Extended_Scan_Parameters);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONTROLLER_SCAN_ENABLED == 1) &&\
    (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1)
tBleStatus hci_le_set_extended_scan_enable(uint8_t Enable,
                                           uint8_t Filter_Duplicates,
                                           uint16_t Duration,
                                           uint16_t Period)
{
    return hci_le_set_extended_scan_enable_api(Enable,
                                               Filter_Duplicates,
                                               Duration,
                                               Period);
}
#endif /* (CONTROLLER_SCAN_ENABLED == 1) &&\
          (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1) */

#if (CONNECTION_ENABLED == 1)
tBleStatus hci_le_connection_update(uint16_t Connection_Handle,
                                    uint16_t Connection_Interval_Min,
                                    uint16_t Connection_Interval_Max,
                                    uint16_t Max_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Min_CE_Length,
                                    uint16_t Max_CE_Length)
{
    return hci_le_connection_update_api(Connection_Handle,
                                        Connection_Interval_Min,
                                        Connection_Interval_Max,
                                        Max_Latency,
                                        Supervision_Timeout,
                                        Min_CE_Length,
                                        Max_CE_Length);
}
#endif /* (CONNECTION_ENABLED == 1) */

#if ((CONNECTION_SUBRATING_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus hci_le_set_default_subrate(uint16_t Subrate_Min,
                                      uint16_t Subrate_Max,
                                      uint16_t Max_Latency,
                                      uint16_t Continuation_Number,
                                      uint16_t Supervision_Timeout)
{
    return hci_le_set_default_subrate_api(Subrate_Min,
                                          Subrate_Max,
                                          Max_Latency,
                                          Continuation_Number,
                                          Supervision_Timeout);
}
#endif /* ((CONNECTION_SUBRATING_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if ((CONNECTION_SUBRATING_ENABLED == 1) &&\
    (CONNECTION_ENABLED == 1))
tBleStatus hci_le_subrate_request(uint16_t Connection_Handle,
                                  uint16_t Subrate_Min,
                                  uint16_t Subrate_Max,
                                  uint16_t Max_Latency,
                                  uint16_t Continuation_Number,
                                  uint16_t Supervision_Timeout)
{
    return hci_le_subrate_request_api(Connection_Handle,
                                      Subrate_Min,
                                      Subrate_Max,
                                      Max_Latency,
                                      Continuation_Number,
                                      Supervision_Timeout);
}
#endif /* ((CONNECTION_SUBRATING_ENABLED == 1) &&\
          (CONNECTION_ENABLED == 1)) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
tBleStatus hci_le_receiver_test_v2(uint8_t RX_Frequency,
                                   uint8_t Phy,
                                   uint8_t Modulation_index)
{
    return hci_le_receiver_test_v2_api(RX_Frequency,
                                       Phy,
                                       Modulation_index);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_receiver_test_v3(uint8_t RX_Channel,
                                   uint8_t PHY,
                                   uint8_t Modulation_Index,
                                   uint8_t Expected_CTE_Length,
                                   uint8_t Expected_CTE_Type,
                                   uint8_t Slot_Durations,
                                   uint8_t Switching_Pattern_Length,
                                   uint8_t* Antenna_IDs)
{
    return hci_le_receiver_test_v3_api(RX_Channel,
                                       PHY,
                                       Modulation_Index,
                                       Expected_CTE_Length,
                                       Expected_CTE_Type,
                                       Slot_Durations,
                                       Switching_Pattern_Length,
                                       Antenna_IDs);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if (CONTROLLER_2M_CODED_PHY_ENABLED == 1)
tBleStatus hci_le_transmitter_test_v2(uint8_t TX_Frequency,
                                      uint8_t Length_Of_Test_Data,
                                      uint8_t Packet_Payload,
                                      uint8_t Phy)
{
    return hci_le_transmitter_test_v2_api(TX_Frequency,
                                          Length_Of_Test_Data,
                                          Packet_Payload,
                                          Phy);
}
#endif /* (CONTROLLER_2M_CODED_PHY_ENABLED == 1) */

#if (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_transmitter_test_v3(uint8_t TX_Channel,
                                      uint8_t Test_Data_Length,
                                      uint8_t Packet_Payload,
                                      uint8_t PHY,
                                      uint8_t CTE_Length,
                                      uint8_t CTE_Type,
                                      uint8_t Switching_Pattern_Length,
                                      uint8_t* Antenna_IDs)
{
    return hci_le_transmitter_test_v3_api(TX_Channel,
                                          Test_Data_Length,
                                          Packet_Payload,
                                          PHY,
                                          CTE_Length,
                                          CTE_Type,
                                          Switching_Pattern_Length,
                                          Antenna_IDs);
}
#endif /* (CONTROLLER_CTE_ENABLED == 1) */

#if ((CONTROLLER_POWER_CONTROL_ENABLED == 1)) ||\
    (CONTROLLER_CTE_ENABLED == 1)
tBleStatus hci_le_transmitter_test_v4(uint8_t TX_Channel,
                                      uint8_t Test_Data_Length,
                                      uint8_t Packet_Payload,
                                      uint8_t PHY,
                                      uint8_t CTE_Length,
                                      uint8_t CTE_Type,
                                      uint8_t Switching_Pattern_Length,
                                      uint8_t* Antenna_IDs,
                                      int8_t Transmit_Power_Level)
{
    return hci_le_transmitter_test_v4_api(TX_Channel,
                                          Test_Data_Length,
                                          Packet_Payload,
                                          PHY,
                                          CTE_Length,
                                          CTE_Type,
                                          Switching_Pattern_Length,
                                          Antenna_IDs,
                                          Transmit_Power_Level);
}
#endif /* ((CONTROLLER_POWER_CONTROL_ENABLED == 1)) ||\
          (CONTROLLER_CTE_ENABLED == 1) */

