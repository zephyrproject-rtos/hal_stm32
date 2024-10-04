
/**
  ******************************************************************************
  * @file    ble_stack_user_cfg.h
  * @author  GPM WBL Application team
  * @brief   Bluetooth LE stack modular configuration options header file
  * @details BLE_Config BLE stack configuration options
  * - The BLE stack v4.0 or later supports the following outstanding features:
  *   -- Controller Privacy
  *   -- LE Secure Connections
  *   -- Controller Scan
  *   -- Controller Data Length Extension
  *   -- LE 2M/Coded PHY
  *   -- Extended Advertising
  *   -- Periodic Advertising and Synchronizer
 *    -- Periodic Advertising with Responses
  *   -- L2CAP Connection Oriented Channels
  *   -- Constant Tone Extension
  *   -- Power Control & Path Loss Monitoring
  *   -- Connection Support
  *   -- LE Channel Classification
  *   -- Broadcast Isochronous Streams
  *   -- Connected Isochronous Streams
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

#ifndef BLE_STACK_USER_CFG_H
#define BLE_STACK_USER_CFG_H

#include <ble_api.h>
#include <stdint.h>
#include "app_conf.h"

#define CONTROLLER_SCAN_ENABLED                   CFG_BLE_CONTROLLER_SCAN_ENABLED
#define CONTROLLER_PRIVACY_ENABLED                CFG_BLE_CONTROLLER_PRIVACY_ENABLED
#define SECURE_CONNECTIONS_ENABLED                CFG_BLE_SECURE_CONNECTIONS_ENABLED
#define CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED  CFG_BLE_CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED
#define CONTROLLER_2M_CODED_PHY_ENABLED           CFG_BLE_CONTROLLER_2M_CODED_PHY_ENABLED
#define CONTROLLER_EXT_ADV_SCAN_ENABLED           CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED
#define L2CAP_COS_ENABLED                         CFG_BLE_L2CAP_COS_ENABLED
#define CONTROLLER_PERIODIC_ADV_ENABLED           CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED
#define CONTROLLER_PERIODIC_ADV_WR_ENABLED        CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED
#define CONTROLLER_CTE_ENABLED                    CFG_BLE_CONTROLLER_CTE_ENABLED
#define CONTROLLER_POWER_CONTROL_ENABLED          CFG_BLE_CONTROLLER_POWER_CONTROL_ENABLED
#define CONNECTION_ENABLED                        CFG_BLE_CONNECTION_ENABLED
#define CONTROLLER_CHAN_CLASS_ENABLED             CFG_BLE_CONTROLLER_CHAN_CLASS_ENABLED
#define CONTROLLER_BIS_ENABLED                    CFG_BLE_CONTROLLER_BIS_ENABLED
#define CONNECTION_SUBRATING_ENABLED              CFG_BLE_CONNECTION_SUBRATING_ENABLED
#define CONTROLLER_CIS_ENABLED                    CFG_BLE_CONTROLLER_CIS_ENABLED


/**
 * @}
 */

/* --------------------- Derived defines --------------------- */
#if (CONTROLLER_BIS_ENABLED == 1U) || (CONTROLLER_CIS_ENABLED == 1U)
#  define CONTROLLER_ISO_ENABLED (1U) /* ISO Support: ENABLED */
#else
#  define CONTROLLER_ISO_ENABLED (0U) /* ISO Support: DISABLED */
#endif

/* --------------------- Defines used by function prototypes -------------------- */

#if !defined(LLC_MAX_NUM_DATA_CHAN)
#   define LLC_MAX_NUM_DATA_CHAN (37U)
#endif
#define LLC_MIN_NUM_DATA_CHAN_MAP_BYTES   (((LLC_MAX_NUM_DATA_CHAN - 1U) >> 3U) + 1U)
#define LLC_MIN_NUM_DATA_CHAN_CLASS_BYTES (((LLC_MAX_NUM_DATA_CHAN - 1U) >> 2U) + 1U)

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
                                                  uint8_t Scan_Request_Notification_Enable);
tBleStatus GAP_set_advertising_configuration_ucfg_weak(uint8_t Advertising_Handle,
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
                                                       uint8_t Scan_Request_Notification_Enable);
tBleStatus GAP_set_extended_advertising_configuration(uint8_t Advertising_Handle,
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
                                                      uint8_t Scan_Request_Notification_Enable);

tBleStatus GAP_set_scan_response_data_ucfg(uint8_t Advertising_Handle,
                                           uint16_t Scan_Response_Data_Length,
                                           uint8_t* Scan_Response_Data);
tBleStatus GAP_set_scan_response_data_ucfg_weak(uint8_t Advertising_Handle,
                                                uint16_t Scan_Response_Data_Length,
                                                uint8_t* Scan_Response_Data);
tBleStatus GAP_set_extended_scan_response_data(uint8_t Advertising_Handle,
                                               uint16_t Scan_Response_Data_Length,
                                               uint8_t* Scan_Response_Data);

tBleStatus GAP_set_advertising_data_ucfg(uint8_t Advertising_Handle,
                                         uint8_t Operation,
                                         uint16_t Advertising_Data_Length,
                                         uint8_t* Advertising_Data);
tBleStatus GAP_set_advertising_data_ucfg_weak(uint8_t Advertising_Handle,
                                              uint8_t Operation,
                                              uint16_t Advertising_Data_Length,
                                              uint8_t* Advertising_Data);
tBleStatus GAP_set_extended_advertising_data(uint8_t Advertising_Handle,
                                             uint8_t Operation,
                                             uint16_t Advertising_Data_Length,
                                             uint8_t* Advertising_Data);

tBleStatus GAP_set_advertising_enable_ucfg(uint8_t Enable,
                                           uint8_t Num_Of_Sets,
                                           Advertising_Set_Parameters_t* Advertising_Set_Parameters);
tBleStatus GAP_set_advertising_enable_ucfg_weak(uint8_t Enable,
                                                uint8_t Num_Of_Sets,
                                                Advertising_Set_Parameters_t* Advertising_Set_Parameters);
tBleStatus GAP_set_extended_advertising_enable(uint8_t Enable,
                                               uint8_t Num_Of_Sets,
                                               Advertising_Set_Parameters_t* Advertising_Set_Parameters);

tBleStatus GAP_create_connection_ucfg(uint8_t* peer_address,
                                      uint8_t peer_address_type,
                                      uint8_t own_address_type,
                                      uint8_t initiator_filter_policy,
                                      uint8_t phys);
tBleStatus GAP_create_connection_ucfg_weak(uint8_t* peer_address,
                                           uint8_t peer_address_type,
                                           uint8_t own_address_type,
                                           uint8_t initiator_filter_policy,
                                           uint8_t phys);
tBleStatus GAP_create_connection_ext(uint8_t* peer_address,
                                     uint8_t peer_address_type,
                                     uint8_t own_address_type,
                                     uint8_t initiator_filter_policy,
                                     uint8_t phys);

tBleStatus GAP_set_scan_parameters_ucfg(uint8_t own_address_type,
                                        uint8_t phys);
tBleStatus GAP_set_scan_parameters_ucfg_weak(uint8_t own_address_type,
                                             uint8_t phys);
tBleStatus GAP_set_scan_parameters_ext(uint8_t own_address_type,
                                       uint8_t phys);

tBleStatus GAP_enable_disable_scan_ucfg(uint8_t enable,
                                        uint8_t duplicate_filtering);
tBleStatus GAP_enable_disable_scan_ucfg_weak(uint8_t enable,
                                             uint8_t duplicate_filtering);
tBleStatus GAP_enable_disable_scan_legacy(uint8_t enable,
                                          uint8_t duplicate_filtering);
tBleStatus GAP_enable_disable_scan_ext(uint8_t enable,
                                       uint8_t duplicate_filtering);

tBleStatus GAP_connection_procedure_ucfg(uint8_t procedure_code,
                                         uint8_t phys,
                                         uint8_t peer_address_type,
                                         uint8_t peer_address[6]);
tBleStatus GAP_connection_procedure_ucfg_weak(uint8_t procedure_code,
                                              uint8_t phys,
                                              uint8_t peer_address_type,
                                              uint8_t peer_address[6]);
tBleStatus GAP_connection_procedure(uint8_t procedure_code,
                                    uint8_t phys,
                                    uint8_t peer_address_type,
                                    uint8_t peer_address[6]);

tBleStatus GAP_terminate_gap_procedure_ucfg(uint8_t procedure_code);
tBleStatus GAP_terminate_gap_procedure_ucfg_weak(uint8_t procedure_code);
tBleStatus GAP_terminate_gap_procedure(uint8_t procedure_code);

tBleStatus GAP_discover_peer_name_ucfg(void);
tBleStatus GAP_discover_peer_name_ucfg_weak(void);
tBleStatus GAP_discover_peer_name(void);

void GAP_name_disc_proc_connected_check_ucfg(uint16_t task_idx);
void GAP_name_disc_proc_connected_check_ucfg_weak(uint16_t task_idx);
void GAP_name_disc_proc_connected_check(uint16_t task_idx);

void GAP_central_connection_complete_handler_ucfg(uint8_t status,
                                                  uint16_t connectionHandle);
void GAP_central_connection_complete_handler_ucfg_weak(uint8_t status,
                                                       uint16_t connectionHandle);
void GAP_central_connection_complete_handler(uint8_t status,
                                             uint16_t connectionHandle);

uint8_t GAP_parse_connectable_advertising_report_ucfg(uint8_t* adv_buf,
                                                   uint8_t extended);
uint8_t GAP_parse_connectable_advertising_report_ucfg_weak(uint8_t* adv_buf,
                                                        uint8_t extended);
uint8_t GAP_parse_connectable_advertising_report(uint8_t* adv_buf,
                                              uint8_t extended);

uint8_t GAP_parse_advertising_report_ucfg(uint8_t* adv_buf,
                                       uint8_t extended);
uint8_t GAP_parse_advertising_report_ucfg_weak(uint8_t* adv_buf,
                                            uint8_t extended);
uint8_t GAP_parse_advertising_report(uint8_t* adv_buf,
                                  uint8_t extended);

void GAP_DiscProcTimeoutcb_ucfg(uint8_t timer_id);
void GAP_DiscProcTimeoutcb_ucfg_weak(uint8_t timer_id);
void GAP_DiscProcTimeoutcb(uint8_t timer_id);

void GAP_LimDiscTimeoutcb_ucfg(uint8_t timer_id);
void GAP_LimDiscTimeoutcb_ucfg_weak(uint8_t timer_id);
void GAP_LimDiscTimeoutcb(uint8_t timer_id);

void GAP_hci_le_advertising_set_terminated_evt_hndl_ucfg(uint8_t status,
                                                         uint8_t Advertising_Handle);
void GAP_hci_le_advertising_set_terminated_evt_hndl_ucfg_weak(uint8_t status,
                                                              uint8_t Advertising_Handle);
void GAP_hci_le_advertising_set_terminated_evt_hndl(uint8_t status,
                                                    uint8_t Advertising_Handle);

void GAP_peripheral_connection_complete_handler_ucfg(uint16_t connectionHandle);
void GAP_peripheral_connection_complete_handler_ucfg_weak(uint16_t connectionHandle);
void GAP_peripheral_connection_complete_handler(uint16_t connectionHandle);

tBleStatus GAP_enable_controller_privacy_ucfg(uint8_t* gapRole,
                                              uint8_t* numServiceRec);
tBleStatus GAP_enable_controller_privacy_ucfg_weak(uint8_t* gapRole,
                                                   uint8_t* numServiceRec);
tBleStatus GAP_enable_controller_privacy(uint8_t* gapRole,
                                         uint8_t* numServiceRec);

tBleStatus GAP_add_device_to_filter_accept_and_resolving_list_ucfg(uint8_t lists,
                                                                   uint8_t addr_type,
                                                                   uint8_t addr[6]);
tBleStatus GAP_add_device_to_filter_accept_and_resolving_list_ucfg_weak(uint8_t lists,
                                                                        uint8_t addr_type,
                                                                        uint8_t addr[6]);
tBleStatus GAP_add_device_to_filter_accept_and_resolving_list_full(uint8_t lists,
                                                                   uint8_t addr_type,
                                                                   uint8_t addr[6]);

tBleStatus GAP_clear_filter_accept_and_resolving_list_ucfg(uint8_t lists);
tBleStatus GAP_clear_filter_accept_and_resolving_list_ucfg_weak(uint8_t lists);
tBleStatus GAP_clear_filter_accept_and_resolving_list_full(uint8_t lists);

tBleStatus GAP_set_controller_random_address_ucfg(uint8_t random_address[6]);
tBleStatus GAP_set_controller_random_address_ucfg_weak(uint8_t random_address[6]);
tBleStatus GAP_set_controller_random_address_extended(uint8_t random_address[6]);

tBleStatus GAP_init_advertising_sets_ucfg(uint8_t own_address_type);
tBleStatus GAP_init_advertising_sets_ucfg_weak(uint8_t own_address_type);
tBleStatus GAP_init_advertising_sets(uint8_t own_address_type);

tBleStatus GAP_suspend_resume_active_advertising_sets_ucfg(uint8_t resume);
tBleStatus GAP_suspend_resume_active_advertising_sets_ucfg_weak(uint8_t resume);
tBleStatus GAP_suspend_resume_active_advertising_sets_extended(uint8_t resume);

void GAP_ResumeAdvertising_ucfg(uint16_t task_idx);
void GAP_ResumeAdvertising_ucfg_weak(uint16_t task_idx);
void GAP_ResumeAdvertising(uint16_t task_idx);

tBleStatus hci_acl_data_tx_cmpl_event_int_cb_ucfg(void* header_p,
                                                  uint8_t* buff_p);
tBleStatus hci_acl_data_tx_cmpl_event_int_cb_ucfg_weak(void* header_p,
                                                       uint8_t* buff_p);
tBleStatus hci_acl_data_tx_cmpl_event_int_cb(void* header_p,
                                             uint8_t* buff_p);

tBleStatus hci_acl_data_ind_event_int_cb_ucfg(void* header_p,
                                              uint8_t* buff_p);
tBleStatus hci_acl_data_ind_event_int_cb_ucfg_weak(void* header_p,
                                                   uint8_t* buff_p);
tBleStatus hci_acl_data_ind_event_int_cb(void* header_p,
                                         uint8_t* buff_p);

uint32_t chc_csr_ucfg(void);
uint32_t chc_csr_ucfg_weak(void);
uint32_t chc_csr(void);

void Controller_Process_Q_ucfg(uint16_t task_idx);
void Controller_Process_Q_ucfg_weak(uint16_t task_idx);
void Controller_Process_Q(uint16_t task_idx);

void LLC_offline_control_procedures_processing_ucfg(uint16_t task_idx);
void LLC_offline_control_procedures_processing_ucfg_weak(uint16_t task_idx);
void LLC_offline_control_procedures_processing(uint16_t task_idx);

uint32_t cte_csr_ucfg(void);
uint32_t cte_csr_ucfg_weak(void);
uint32_t cte_csr(void);

uint8_t hci_le_check_own_address_type_max_value_ucfg(void);
uint8_t hci_le_check_own_address_type_max_value_ucfg_weak(void);
uint8_t hci_le_check_own_address_type_max_value(void);

uint32_t data_length_extension_csr_ucfg(void);
uint32_t data_length_extension_csr_ucfg_weak(void);
uint32_t data_length_extension_csr(void);

uint32_t pcl_csr_ucfg(void);
uint32_t pcl_csr_ucfg_weak(void);
uint32_t pcl_csr(void);

uint32_t phy_upd_csr_ucfg(void);
uint32_t phy_upd_csr_ucfg_weak(void);
uint32_t phy_upd_csr(void);

uint32_t scan_csr_ucfg(void);
uint32_t scan_csr_ucfg_weak(void);
uint32_t scan_csr(void);

uint32_t conn_supp_csr_ucfg(void);
uint32_t conn_supp_csr_ucfg_weak(void);
uint32_t conn_supp_csr(void);

uint32_t subrate_csr_ucfg(void);
uint32_t subrate_csr_ucfg_weak(void);
uint32_t subrate_csr(void);

tBleStatus LLC_test_check_cte_params_ucfg(void* params);
tBleStatus LLC_test_check_cte_params_ucfg_weak(void* params);
tBleStatus LLC_test_check_cte_params(void* params);

tBleStatus ACL_pkt_init_ucfg(void);
tBleStatus ACL_pkt_init_ucfg_weak(void);
tBleStatus ACL_pkt_init(void);

tBleStatus hci_disconnection_complete_event_int_cb_ucfg(void* header_p,
                                                        uint8_t* buff_p);
tBleStatus hci_disconnection_complete_event_int_cb_ucfg_weak(void* header_p,
                                                             uint8_t* buff_p);
tBleStatus hci_disconnection_complete_event_int_cb(void* header_p,
                                                   uint8_t* buff_p);

tBleStatus hci_encryption_change_event_int_cb_ucfg(void* header_p,
                                                   uint8_t* buff_p);
tBleStatus hci_encryption_change_event_int_cb_ucfg_weak(void* header_p,
                                                        uint8_t* buff_p);
tBleStatus hci_encryption_change_event_int_cb(void* header_p,
                                              uint8_t* buff_p);

tBleStatus hci_encryption_key_refresh_complete_event_int_cb_ucfg(void* header_p,
                                                                 uint8_t* buff_p);
tBleStatus hci_encryption_key_refresh_complete_event_int_cb_ucfg_weak(void* header_p,
                                                                      uint8_t* buff_p);
tBleStatus hci_encryption_key_refresh_complete_event_int_cb(void* header_p,
                                                            uint8_t* buff_p);

tBleStatus hci_le_connection_complete_event_int_cb_ucfg(void* header_p,
                                                        uint8_t* buff_p);
tBleStatus hci_le_connection_complete_event_int_cb_ucfg_weak(void* header_p,
                                                             uint8_t* buff_p);
tBleStatus hci_le_connection_complete_event_int_cb(void* header_p,
                                                   uint8_t* buff_p);

tBleStatus hci_le_enhanced_connection_complete_event_int_cb_ucfg(void* header_p,
                                                                 uint8_t* buff_p);
tBleStatus hci_le_enhanced_connection_complete_event_int_cb_ucfg_weak(void* header_p,
                                                                      uint8_t* buff_p);
tBleStatus hci_le_enhanced_connection_complete_event_int_cb(void* header_p,
                                                            uint8_t* buff_p);

tBleStatus hci_le_long_term_key_request_event_int_cb_ucfg(void* header_p,
                                                          uint8_t* buff_p);
tBleStatus hci_le_long_term_key_request_event_int_cb_ucfg_weak(void* header_p,
                                                               uint8_t* buff_p);
tBleStatus hci_le_long_term_key_request_event_int_cb(void* header_p,
                                                     uint8_t* buff_p);

tBleStatus hci_le_read_local_p256_public_key_complete_event_int_cb_ucfg(void* header_p,
                                                                        uint8_t* buff_p);
tBleStatus hci_le_read_local_p256_public_key_complete_event_int_cb_ucfg_weak(void* header_p,
                                                                             uint8_t* buff_p);
tBleStatus hci_le_read_local_p256_public_key_complete_event_int_cb(void* header_p,
                                                                   uint8_t* buff_p);

tBleStatus hci_le_generate_dhkey_complete_event_int_cb_ucfg(void* header_p,
                                                            uint8_t* buff_p);
tBleStatus hci_le_generate_dhkey_complete_event_int_cb_ucfg_weak(void* header_p,
                                                                 uint8_t* buff_p);
tBleStatus hci_le_generate_dhkey_complete_event_int_cb(void* header_p,
                                                       uint8_t* buff_p);

tBleStatus hci_le_advertising_report_event_int_cb_ucfg(void* header_p,
                                                       uint8_t* buff_p);
tBleStatus hci_le_advertising_report_event_int_cb_ucfg_weak(void* header_p,
                                                            uint8_t* buff_p);
tBleStatus hci_le_advertising_report_event_int_cb(void* header_p,
                                                  uint8_t* buff_p);

tBleStatus hci_le_directed_advertising_report_event_int_cb_ucfg(void* header_p,
                                                                uint8_t* buff_p);
tBleStatus hci_le_directed_advertising_report_event_int_cb_ucfg_weak(void* header_p,
                                                                     uint8_t* buff_p);
tBleStatus hci_le_directed_advertising_report_event_int_cb(void* header_p,
                                                           uint8_t* buff_p);

tBleStatus hci_le_extended_advertising_report_event_int_cb_ucfg(void* header_p,
                                                                uint8_t* buff_p);
tBleStatus hci_le_extended_advertising_report_event_int_cb_ucfg_weak(void* header_p,
                                                                     uint8_t* buff_p);
tBleStatus hci_le_extended_advertising_report_event_int_cb(void* header_p,
                                                           uint8_t* buff_p);

tBleStatus hci_le_scan_timeout_event_int_cb_ucfg(void* header_p,
                                                 uint8_t* buff_p);
tBleStatus hci_le_scan_timeout_event_int_cb_ucfg_weak(void* header_p,
                                                      uint8_t* buff_p);
tBleStatus hci_le_scan_timeout_event_int_cb(void* header_p,
                                            uint8_t* buff_p);

tBleStatus hci_le_advertising_set_terminated_event_int_cb_ucfg(void* header_p,
                                                               uint8_t* buff_p);
tBleStatus hci_le_advertising_set_terminated_event_int_cb_ucfg_weak(void* header_p,
                                                                    uint8_t* buff_p);
tBleStatus hci_le_advertising_set_terminated_event_int_cb(void* header_p,
                                                          uint8_t* buff_p);

tBleStatus hci_le_enhanced_connection_complete_v2_event_int_cb_ucfg(void* header_p,
                                                                    uint8_t* buff_p);
tBleStatus hci_le_enhanced_connection_complete_v2_event_int_cb_ucfg_weak(void* header_p,
                                                                         uint8_t* buff_p);
tBleStatus hci_le_enhanced_connection_complete_v2_event_int_cb(void* header_p,
                                                               uint8_t* buff_p);

tBleStatus MBM_init_ucfg(void);
tBleStatus MBM_init_ucfg_weak(void);
tBleStatus MBM_init(void);

uint32_t secure_connections_csr_ucfg(void);
uint32_t secure_connections_csr_ucfg_weak(void);
uint32_t secure_connections_csr(void);

tBleStatus smp_sap_scp_force_debug_key_usage_ucfg(uint8_t config_val);
tBleStatus smp_sap_scp_force_debug_key_usage_ucfg_weak(uint8_t config_val);
tBleStatus smp_sap_scp_force_debug_key_usage(uint8_t config_val);

void smp_sap_hci_le_read_local_p256_public_key_complete_evt_hndl_ucfg(uint8_t status,
                                                                      uint8_t local_p256_public_key[64]);
void smp_sap_hci_le_read_local_p256_public_key_complete_evt_hndl_ucfg_weak(uint8_t status,
                                                                           uint8_t local_p256_public_key[64]);
void smp_sap_hci_le_read_local_p256_public_key_complete_evt_hndl(uint8_t status,
                                                                 uint8_t local_p256_public_key[64]);

void smp_sap_hci_le_generate_dhkey_complete_evt_hndl_ucfg(uint8_t status,
                                                          uint8_t dhkey[32]);
void smp_sap_hci_le_generate_dhkey_complete_evt_hndl_ucfg_weak(uint8_t status,
                                                               uint8_t dhkey[32]);
void smp_sap_hci_le_generate_dhkey_complete_evt_hndl(uint8_t status,
                                                     uint8_t dhkey[32]);

uint32_t l2c_cos_csr_ucfg(void);
uint32_t l2c_cos_csr_ucfg_weak(void);
uint32_t l2c_cos_csr(void);

tBleStatus L2C_cos_cfc_init_ucfg(void);
tBleStatus L2C_cos_cfc_init_ucfg_weak(void);
tBleStatus L2C_cos_cfc_init(void);

void l2c_cos_process_pending_actions_tsk_ucfg(uint16_t task_idx);
void l2c_cos_process_pending_actions_tsk_ucfg_weak(uint16_t task_idx);
void l2c_cos_process_pending_actions_tsk(uint16_t task_idx);

void L2C_cos_physical_link_disconnection_hndl_ucfg(uint16_t connection_handle);
void L2C_cos_physical_link_disconnection_hndl_ucfg_weak(uint16_t connection_handle);
void L2C_cos_physical_link_disconnection_hndl(uint16_t connection_handle);

tBleStatus L2C_cos_process_cfc_mode_command_ucfg(void* params);
tBleStatus L2C_cos_process_cfc_mode_command_ucfg_weak(void* params);
tBleStatus L2C_cos_process_cfc_mode_command(void* params);

uint8_t L2C_cos_is_pdu_cframe_cfc_command_opcode_ucfg(uint8_t opCode);
uint8_t L2C_cos_is_pdu_cframe_cfc_command_opcode_ucfg_weak(uint8_t opCode);
uint8_t L2C_cos_is_pdu_cframe_cfc_command_opcode(uint8_t opCode);

tBleStatus l2c_cos_hndl_incoming_le_frame_ucfg(void* params);
tBleStatus l2c_cos_hndl_incoming_le_frame_ucfg_weak(void* params);
tBleStatus l2c_cos_hndl_incoming_le_frame(void* params);

void l2c_cos_sdu_reassembly_tsk_ucfg(uint16_t task_idx);
void l2c_cos_sdu_reassembly_tsk_ucfg_weak(uint16_t task_idx);
void l2c_cos_sdu_reassembly_tsk(uint16_t task_idx);

tBleStatus l2c_cos_sdu_enqueue_for_segmentation_ucfg(void* params);
tBleStatus l2c_cos_sdu_enqueue_for_segmentation_ucfg_weak(void* params);
tBleStatus l2c_cos_sdu_enqueue_for_segmentation(void* params);

void l2c_cos_sdu_segmentation_tsk_ucfg(uint16_t task_idx);
void l2c_cos_sdu_segmentation_tsk_ucfg_weak(uint16_t task_idx);
void l2c_cos_sdu_segmentation_tsk(uint16_t task_idx);

void l2c_cos_transmit_pdu_packets_tsk_ucfg(uint16_t task_idx);
void l2c_cos_transmit_pdu_packets_tsk_ucfg_weak(uint16_t task_idx);
void l2c_cos_transmit_pdu_packets_tsk(uint16_t task_idx);

tBleStatus L2C_init_ucfg(uint8_t cos_enabled);
tBleStatus L2C_init_ucfg_weak(uint8_t cos_enabled);
tBleStatus L2C_init(uint8_t cos_enabled);

void llc_conn_check_subrate_and_set_params_ucfg(void* cntxt_p,
                                                void* params_p);
void llc_conn_check_subrate_and_set_params_ucfg_weak(void* cntxt_p,
                                                     void* params_p);
void llc_conn_check_subrate_and_set_params(void* cntxt_p,
                                           void* params_p);

uint32_t llc_conn_calc_skip_ucfg(void* cntxt_p,
                                 uint16_t event_counter,
                                 uint16_t latency);
uint32_t llc_conn_calc_skip_ucfg_weak(void* cntxt_p,
                                      uint16_t event_counter,
                                      uint16_t latency);
uint32_t llc_conn_calc_skip(void* cntxt_p,
                            uint16_t event_counter,
                            uint16_t latency);

tBleStatus llc_conn_multi_link_connection_ucfg(uint8_t enable);
tBleStatus llc_conn_multi_link_connection_ucfg_weak(uint8_t enable);
tBleStatus llc_conn_multi_link_connection(uint8_t enable);

void llc_conn_peripheral_latency_cancellation_tsk_ucfg(uint16_t task_idx);
void llc_conn_peripheral_latency_cancellation_tsk_ucfg_weak(uint16_t task_idx);
void llc_conn_peripheral_latency_cancellation_tsk(uint16_t task_idx);

uint8_t llc_check_sreq_or_creq_tx_addr_ucfg(void* tx_addr7_p,
                                            uint8_t pdu_type,
                                            uint8_t adv_event_prop,
                                            uint8_t adv_filter_policy,
                                            void* peer_id_addr7_p,
                                            void* res_peer_id_addr7_p,
                                            uint8_t* rl_index_p);
uint8_t llc_check_sreq_or_creq_tx_addr_ucfg_weak(void* tx_addr7_p,
                                                 uint8_t pdu_type,
                                                 uint8_t adv_event_prop,
                                                 uint8_t adv_filter_policy,
                                                 void* peer_id_addr7_p,
                                                 void* res_peer_id_addr7_p,
                                                 uint8_t* rl_index_p);
uint8_t llc_check_sreq_or_creq_tx_addr(void* tx_addr7_p,
                                       uint8_t pdu_type,
                                       uint8_t adv_event_prop,
                                       uint8_t adv_filter_policy,
                                       void* peer_id_addr7_p,
                                       void* res_peer_id_addr7_p,
                                       uint8_t* rl_index_p);

uint8_t llc_check_adv_or_srsp_or_crsp_tx_addr_ucfg(uint8_t* tx_addr7_p,
                                                   uint8_t adv_pdu,
                                                   uint8_t filter_policy,
                                                   uint8_t* peer_id_addr7_p,
                                                   uint8_t* rl_index_p,
                                                   uint8_t* res_peer_id_addr7_p);
uint8_t llc_check_adv_or_srsp_or_crsp_tx_addr_ucfg_weak(uint8_t* tx_addr7_p,
                                                        uint8_t adv_pdu,
                                                        uint8_t filter_policy,
                                                        uint8_t* peer_id_addr7_p,
                                                        uint8_t* rl_index_p,
                                                        uint8_t* res_peer_id_addr7_p);
uint8_t llc_check_adv_or_srsp_or_crsp_tx_addr(uint8_t* tx_addr7_p,
                                              uint8_t adv_pdu,
                                              uint8_t filter_policy,
                                              uint8_t* peer_id_addr7_p,
                                              uint8_t* rl_index_p,
                                              uint8_t* res_peer_id_addr7_p);

uint8_t llc_check_adv_or_crsp_rx_addr_ucfg(uint8_t* rx_addr7_p,
                                           uint8_t adv_pdu,
                                           uint8_t filter_policy,
                                           uint8_t* local_addr7_p,
                                           uint8_t local_addr_type,
                                           uint8_t rl_index);
uint8_t llc_check_adv_or_crsp_rx_addr_ucfg_weak(uint8_t* rx_addr7_p,
                                                uint8_t adv_pdu,
                                                uint8_t filter_policy,
                                                uint8_t* local_addr7_p,
                                                uint8_t local_addr_type,
                                                uint8_t rl_index);
uint8_t llc_check_adv_or_crsp_rx_addr(uint8_t* rx_addr7_p,
                                      uint8_t adv_pdu,
                                      uint8_t filter_policy,
                                      uint8_t* local_addr7_p,
                                      uint8_t local_addr_type,
                                      uint8_t rl_index);

uint32_t bis_csr_ucfg(void);
uint32_t bis_csr_ucfg_weak(void);
uint32_t bis_csr(void);

uint32_t cis_csr_ucfg(void);
uint32_t cis_csr_ucfg_weak(void);
uint32_t cis_csr(void);

void llc_isoal_mem_alloc_ucfg(void);
void llc_isoal_mem_alloc_ucfg_weak(void);
void llc_isoal_mem_alloc(void);

uint32_t iso_csr_ucfg(void);
uint32_t iso_csr_ucfg_weak(void);
uint32_t iso_csr(void);

tBleStatus iso_rx_bn_pdu_event_int_cb_ucfg(void* header_p,
                                           uint8_t* buff_p);
tBleStatus iso_rx_bn_pdu_event_int_cb_ucfg_weak(void* header_p,
                                                uint8_t* buff_p);
tBleStatus iso_rx_bn_pdu_event_int_cb(void* header_p,
                                      uint8_t* buff_p);

tBleStatus iso_terminate_event_int_cb_ucfg(void* header_p,
                                           uint8_t* buff_p);
tBleStatus iso_terminate_event_int_cb_ucfg_weak(void* header_p,
                                                uint8_t* buff_p);
tBleStatus iso_terminate_event_int_cb(void* header_p,
                                      uint8_t* buff_p);

tBleStatus iso_tx_bn_pdu_event_int_cb_ucfg(void* header_p,
                                           uint8_t* buff_p);
tBleStatus iso_tx_bn_pdu_event_int_cb_ucfg_weak(void* header_p,
                                                uint8_t* buff_p);
tBleStatus iso_tx_bn_pdu_event_int_cb(void* header_p,
                                      uint8_t* buff_p);

void llc_big_brc_mem_alloc_ucfg(void);
void llc_big_brc_mem_alloc_ucfg_weak(void);
void llc_big_brc_mem_alloc(void);

tBleStatus llc_big_brc_alloc_streams_ucfg(void* ctx,
                                          uint8_t stream_count);
tBleStatus llc_big_brc_alloc_streams_ucfg_weak(void* ctx,
                                               uint8_t stream_count);
tBleStatus llc_big_brc_alloc_streams(void* ctx,
                                     uint8_t stream_count);

void llc_big_brc_add_biginfo_to_periodic_sync_packet_ucfg(void* pointer,
                                                          uint8_t* packet_p);
void llc_big_brc_add_biginfo_to_periodic_sync_packet_ucfg_weak(void* pointer,
                                                               uint8_t* packet_p);
void llc_big_brc_add_biginfo_to_periodic_sync_packet(void* pointer,
                                                     uint8_t* packet_p);

void* llc_big_brc_get_group_descr_of_adv_ucfg(uint8_t adv_handle);
void* llc_big_brc_get_group_descr_of_adv_ucfg_weak(uint8_t adv_handle);
void* llc_big_brc_get_group_descr_of_adv(uint8_t adv_handle);

tBleStatus llc_big_brc_enqueue_pdu_ucfg(void* ctx_p,
                                        uint32_t iso_interval_idx,
                                        uint16_t conn_handle,
                                        void* pdu_p);
tBleStatus llc_big_brc_enqueue_pdu_ucfg_weak(void* ctx_p,
                                             uint32_t iso_interval_idx,
                                             uint16_t conn_handle,
                                             void* pdu_p);
tBleStatus llc_big_brc_enqueue_pdu(void* ctx_p,
                                   uint32_t iso_interval_idx,
                                   uint16_t conn_handle,
                                   void* pdu_p);

uint32_t llc_big_brc_get_own_big_event_time_ucfg(void* ctx_p,
                                                 uint16_t conn_handle,
                                                 uint16_t num_enq_packet);
uint32_t llc_big_brc_get_own_big_event_time_ucfg_weak(void* ctx_p,
                                                      uint16_t conn_handle,
                                                      uint16_t num_enq_packet);
uint32_t llc_big_brc_get_own_big_event_time(void* ctx_p,
                                            uint16_t conn_handle,
                                            uint16_t num_enq_packet);

void llc_big_sync_mem_alloc_ucfg(void);
void llc_big_sync_mem_alloc_ucfg_weak(void);
void llc_big_sync_mem_alloc(void);

tBleStatus llc_big_sync_alloc_streams_ucfg(void* ctx,
                                           uint8_t stream_count);
tBleStatus llc_big_sync_alloc_streams_ucfg_weak(void* ctx,
                                                uint8_t stream_count);
tBleStatus llc_big_sync_alloc_streams(void* ctx,
                                      uint8_t stream_count);

void llc_big_sync_deploy_sync_ucfg(uint8_t* biginfo,
                                   uint16_t sync_handle,
                                   uint32_t periodic_reference_anchor,
                                   uint8_t sca_value);
void llc_big_sync_deploy_sync_ucfg_weak(uint8_t* biginfo,
                                        uint16_t sync_handle,
                                        uint32_t periodic_reference_anchor,
                                        uint8_t sca_value);
void llc_big_sync_deploy_sync(uint8_t* biginfo,
                              uint16_t sync_handle,
                              uint32_t periodic_reference_anchor,
                              uint8_t sca_value);

tBleStatus llc_big_sync_decrypt_bis_packet_ucfg(void* ctx_p,
                                                void* pdu_p);
tBleStatus llc_big_sync_decrypt_bis_packet_ucfg_weak(void* ctx_p,
                                                     void* pdu_p);
tBleStatus llc_big_sync_decrypt_bis_packet(void* ctx_p,
                                           void* pdu_p);

uint32_t llc_big_sync_get_sdu_synchronization_us_ucfg(uint16_t conn_handle,
                                                      uint8_t framed,
                                                      uint32_t anchor_us,
                                                      uint32_t time_offset);
uint32_t llc_big_sync_get_sdu_synchronization_us_ucfg_weak(uint16_t conn_handle,
                                                           uint8_t framed,
                                                           uint32_t anchor_us,
                                                           uint32_t time_offset);
uint32_t llc_big_sync_get_sdu_synchronization_us(uint16_t conn_handle,
                                                 uint8_t framed,
                                                 uint32_t anchor_us,
                                                 uint32_t time_offset);

tBleStatus llc_big_cmn_get_iso_params_ucfg(uint8_t direction,
                                           uint16_t conn_handle,
                                           void* param_p);
tBleStatus llc_big_cmn_get_iso_params_ucfg_weak(uint8_t direction,
                                                uint16_t conn_handle,
                                                void* param_p);
tBleStatus llc_big_cmn_get_iso_params(uint8_t direction,
                                      uint16_t conn_handle,
                                      void* param_p);

uint32_t llc_cig_cen_get_cis_offset_from_acl_us_ucfg(void* ctx_p,
                                                     void* cis_p,
                                                     uint8_t conn_idx,
                                                     uint16_t* event_count_p,
                                                     uint32_t* cig_anchor_st_p);
uint32_t llc_cig_cen_get_cis_offset_from_acl_us_ucfg_weak(void* ctx_p,
                                                          void* cis_p,
                                                          uint8_t conn_idx,
                                                          uint16_t* event_count_p,
                                                          uint32_t* cig_anchor_st_p);
uint32_t llc_cig_cen_get_cis_offset_from_acl_us(void* ctx_p,
                                                void* cis_p,
                                                uint8_t conn_idx,
                                                uint16_t* event_count_p,
                                                uint32_t* cig_anchor_st_p);

uint32_t llc_cig_cen_get_sdu_synchronization_us_ucfg(uint16_t conn_handle,
                                                     uint8_t framed,
                                                     uint32_t anchor_us,
                                                     uint32_t time_offset);
uint32_t llc_cig_cen_get_sdu_synchronization_us_ucfg_weak(uint16_t conn_handle,
                                                          uint8_t framed,
                                                          uint32_t anchor_us,
                                                          uint32_t time_offset);
uint32_t llc_cig_cen_get_sdu_synchronization_us(uint16_t conn_handle,
                                                uint8_t framed,
                                                uint32_t anchor_us,
                                                uint32_t time_offset);

uint32_t llc_cig_per_get_sdu_synchronization_us_ucfg(uint16_t conn_handle,
                                                     uint8_t framed,
                                                     uint32_t anchor_us,
                                                     uint32_t time_offset);
uint32_t llc_cig_per_get_sdu_synchronization_us_ucfg_weak(uint16_t conn_handle,
                                                          uint8_t framed,
                                                          uint32_t anchor_us,
                                                          uint32_t time_offset);
uint32_t llc_cig_per_get_sdu_synchronization_us(uint16_t conn_handle,
                                                uint8_t framed,
                                                uint32_t anchor_us,
                                                uint32_t time_offset);

tBleStatus llc_cig_cmn_disconnect_ucfg(uint16_t cis_handle,
                                       uint8_t reason);
tBleStatus llc_cig_cmn_disconnect_ucfg_weak(uint16_t cis_handle,
                                            uint8_t reason);
tBleStatus llc_cig_cmn_disconnect(uint16_t cis_handle,
                                  uint8_t reason);

void llc_cig_cmn_mem_alloc_ucfg(void);
void llc_cig_cmn_mem_alloc_ucfg_weak(void);
void llc_cig_cmn_mem_alloc(void);

tBleStatus llc_cig_cmn_alloc_streams_ucfg(void* ctx,
                                          uint8_t stream_count,
                                          uint8_t group_type);
tBleStatus llc_cig_cmn_alloc_streams_ucfg_weak(void* ctx,
                                               uint8_t stream_count,
                                               uint8_t group_type);
tBleStatus llc_cig_cmn_alloc_streams(void* ctx,
                                     uint8_t stream_count,
                                     uint8_t group_type);

void llc_cig_cmn_terminate_stream_ucfg(void* cig_p,
                                       void* cis_p,
                                       uint8_t reason);
void llc_cig_cmn_terminate_stream_ucfg_weak(void* cig_p,
                                            void* cis_p,
                                            uint8_t reason);
void llc_cig_cmn_terminate_stream(void* cig_p,
                                  void* cis_p,
                                  uint8_t reason);

uint32_t llc_cig_cmn_get_own_cig_event_time_ucfg(void* ctx_p,
                                                 uint16_t conn_handle,
                                                 uint16_t num_enq_packet);
uint32_t llc_cig_cmn_get_own_cig_event_time_ucfg_weak(void* ctx_p,
                                                      uint16_t conn_handle,
                                                      uint16_t num_enq_packet);
uint32_t llc_cig_cmn_get_own_cig_event_time(void* ctx_p,
                                            uint16_t conn_handle,
                                            uint16_t num_enq_packet);

tBleStatus llc_cig_cmn_enqueue_pdu_to_tx_ucfg(void* ctx_p,
                                              uint32_t iso_interval_idx,
                                              uint16_t conn_handle,
                                              void* pdu_p);
tBleStatus llc_cig_cmn_enqueue_pdu_to_tx_ucfg_weak(void* ctx_p,
                                                   uint32_t iso_interval_idx,
                                                   uint16_t conn_handle,
                                                   void* pdu_p);
tBleStatus llc_cig_cmn_enqueue_pdu_to_tx(void* ctx_p,
                                         uint32_t iso_interval_idx,
                                         uint16_t conn_handle,
                                         void* pdu_p);

tBleStatus llc_cig_cmn_decrypt_packet_ucfg(void* ctx_p,
                                           void* pdu_p);
tBleStatus llc_cig_cmn_decrypt_packet_ucfg_weak(void* ctx_p,
                                                void* pdu_p);
tBleStatus llc_cig_cmn_decrypt_packet(void* ctx_p,
                                      void* pdu_p);

void llc_cig_cmn_start_cis_ucfg(uint8_t conn_idx,
                                uint16_t instant);
void llc_cig_cmn_start_cis_ucfg_weak(uint8_t conn_idx,
                                     uint16_t instant);
void llc_cig_cmn_start_cis(uint8_t conn_idx,
                           uint16_t instant);

uint8_t llc_cig_cmn_is_active_cis_on_acl_ucfg(uint16_t acl_conn_handle);
uint8_t llc_cig_cmn_is_active_cis_on_acl_ucfg_weak(uint16_t acl_conn_handle);
uint8_t llc_cig_cmn_is_active_cis_on_acl(uint16_t acl_conn_handle);

void llc_cig_cmn_terminate_cises_on_acl_ucfg(uint16_t acl_conn_handle);
void llc_cig_cmn_terminate_cises_on_acl_ucfg_weak(uint16_t acl_conn_handle);
void llc_cig_cmn_terminate_cises_on_acl(uint16_t acl_conn_handle);

void llc_cig_cmn_cis_established_event_gen_ucfg(void* cig_p,
                                                void* cis_p,
                                                uint8_t status);
void llc_cig_cmn_cis_established_event_gen_ucfg_weak(void* cig_p,
                                                     void* cis_p,
                                                     uint8_t status);
void llc_cig_cmn_cis_established_event_gen(void* cig_p,
                                           void* cis_p,
                                           uint8_t status);

tBleStatus llc_cig_cmn_get_iso_params_ucfg(uint8_t direction,
                                           uint16_t conn_handle,
                                           void* param_p);
tBleStatus llc_cig_cmn_get_iso_params_ucfg_weak(uint8_t direction,
                                                uint16_t conn_handle,
                                                void* param_p);
tBleStatus llc_cig_cmn_get_iso_params(uint8_t direction,
                                      uint16_t conn_handle,
                                      void* param_p);

tBleStatus llc_cig_cmn_read_iso_link_quality_ucfg(uint16_t conn_handle,
                                                  uint32_t* tx_unacked_packets_p,
                                                  uint32_t* tx_flushed_packets_p,
                                                  uint32_t* tx_last_subevent_packets_p,
                                                  uint32_t* retransmitted_packets_p,
                                                  uint32_t* crc_error_packets_p,
                                                  uint32_t* rx_unreceived_packets_p,
                                                  uint32_t* duplicate_packets_p);
tBleStatus llc_cig_cmn_read_iso_link_quality_ucfg_weak(uint16_t conn_handle,
                                                       uint32_t* tx_unacked_packets_p,
                                                       uint32_t* tx_flushed_packets_p,
                                                       uint32_t* tx_last_subevent_packets_p,
                                                       uint32_t* retransmitted_packets_p,
                                                       uint32_t* crc_error_packets_p,
                                                       uint32_t* rx_unreceived_packets_p,
                                                       uint32_t* duplicate_packets_p);
tBleStatus llc_cig_cmn_read_iso_link_quality(uint16_t conn_handle,
                                             uint32_t* tx_unacked_packets_p,
                                             uint32_t* tx_flushed_packets_p,
                                             uint32_t* tx_last_subevent_packets_p,
                                             uint32_t* retransmitted_packets_p,
                                             uint32_t* crc_error_packets_p,
                                             uint32_t* rx_unreceived_packets_p,
                                             uint32_t* duplicate_packets_p);

void llc_iso_cmn_mem_alloc_ucfg(void);
void llc_iso_cmn_mem_alloc_ucfg_weak(void);
void llc_iso_cmn_mem_alloc(void);

void llc_padv_mem_allocate_ucfg(uint8_t eadv_en,
                                uint8_t padv_en,
                                uint8_t nr_of_adv_sets,
                                uint8_t* more_info_p);
void llc_padv_mem_allocate_ucfg_weak(uint8_t eadv_en,
                                     uint8_t padv_en,
                                     uint8_t nr_of_adv_sets,
                                     uint8_t* more_info_p);
void llc_padv_mem_allocate(uint8_t eadv_en,
                           uint8_t padv_en,
                           uint8_t nr_of_adv_sets,
                           uint8_t* more_info_p);
void llc_padv_wr_mem_allocate(uint8_t eadv_en,
                              uint8_t padv_en,
                              uint8_t nr_of_adv_sets,
                              uint8_t* more_info_p);

void llc_padv_init_ucfg(void);
void llc_padv_init_ucfg_weak(void);
void llc_padv_init(void);

tBleStatus llc_padv_set_periodic_advertising_data_ucfg(uint16_t advertising_handle,
                                                       uint8_t operation,
                                                       uint16_t data_length,
                                                       uint8_t* data_p);
tBleStatus llc_padv_set_periodic_advertising_data_ucfg_weak(uint16_t advertising_handle,
                                                            uint8_t operation,
                                                            uint16_t data_length,
                                                            uint8_t* data_p);
tBleStatus llc_padv_set_periodic_advertising_data(uint16_t advertising_handle,
                                                  uint8_t operation,
                                                  uint16_t data_length,
                                                  uint8_t* data_p);

uint8_t llc_padv_check_if_syncinfo_is_included_and_start_periodic_advertising_ucfg(void* context_p);
uint8_t llc_padv_check_if_syncinfo_is_included_and_start_periodic_advertising_ucfg_weak(void* context_p);
uint8_t llc_padv_check_if_syncinfo_is_included_and_start_periodic_advertising(void* context_p);

uint8_t llc_padv_update_sync_info_ucfg(void* padv_per_p,
                                    uint32_t aux_adv_ind_anchor);
uint8_t llc_padv_update_sync_info_ucfg_weak(void* padv_per_p,
                                         uint32_t aux_adv_ind_anchor);
uint8_t llc_padv_update_sync_info(void* padv_per_p,
                               uint32_t aux_adv_ind_anchor);

void llc_padv_prepare_periodic_advertising_payload_ucfg(void* padv_per_p,
                                                        uint8_t extended_header_flags,
                                                        uint8_t* payload_p);
void llc_padv_prepare_periodic_advertising_payload_ucfg_weak(void* padv_per_p,
                                                             uint8_t extended_header_flags,
                                                             uint8_t* payload_p);
void llc_padv_prepare_periodic_advertising_payload(void* padv_per_p,
                                                   uint8_t extended_header_flags,
                                                   uint8_t* payload_p);

uint32_t llc_padv_periodic_adv_sync_csr_ucfg(void);
uint32_t llc_padv_periodic_adv_sync_csr_ucfg_weak(void);
uint32_t llc_padv_periodic_adv_sync_csr(void);

uint8_t llc_padv_wr_create_connection_cancel_ucfg(void* _padv_per_p,
                                               uint8_t advertising_handle);
uint8_t llc_padv_wr_create_connection_cancel_ucfg_weak(void* _padv_per_p,
                                                    uint8_t advertising_handle);
uint8_t llc_padv_wr_create_connection_cancel(void* _padv_per_p,
                                          uint8_t advertising_handle);

void llc_padv_wr_set_start_parameters_ucfg(void* set_padv_wr_start_parameters_p);
void llc_padv_wr_set_start_parameters_ucfg_weak(void* set_padv_wr_start_parameters_p);
void llc_padv_wr_set_start_parameters(void* set_padv_wr_start_parameters_p);

tBleStatus llc_padv_wr_set_periodic_advertising_subevent_data_ucfg(void* set_padv_wr_data_p);
tBleStatus llc_padv_wr_set_periodic_advertising_subevent_data_ucfg_weak(void* set_padv_wr_data_p);
tBleStatus llc_padv_wr_set_periodic_advertising_subevent_data(void* set_padv_wr_data_p);

uint8_t llc_padv_wr_set_ctrdata_ucfg(void* padv_per_p,
                                  uint8_t* ctrdata_p);
uint8_t llc_padv_wr_set_ctrdata_ucfg_weak(void* padv_per_p,
                                       uint8_t* ctrdata_p);
uint8_t llc_padv_wr_set_ctrdata(void* padv_per_p,
                             uint8_t* ctrdata_p);

void llc_padv_wr_set_acad_ucfg(void* padv_per_p,
                               uint8_t* ext_hdr_p);
void llc_padv_wr_set_acad_ucfg_weak(void* padv_per_p,
                                    uint8_t* ext_hdr_p);
void llc_padv_wr_set_acad(void* padv_per_p,
                          uint8_t* ext_hdr_p);

void llc_padv_wr_init_anchors_and_counters_ucfg(void* padv_per_p);
void llc_padv_wr_init_anchors_and_counters_ucfg_weak(void* padv_per_p);
void llc_padv_wr_init_anchors_and_counters(void* padv_per_p);

uint32_t llc_padv_periodic_adv_sync_wr_csr_ucfg(void);
uint32_t llc_padv_periodic_adv_sync_wr_csr_ucfg_weak(void);
uint32_t llc_padv_periodic_adv_sync_wr_csr(void);

void llc_padv_wr_disable_ext_ucfg(void* _padv_per_p);
void llc_padv_wr_disable_ext_ucfg_weak(void* _padv_per_p);
void llc_padv_wr_disable_ext(void* _padv_per_p);

void llc_priv_generate_peer_rpa_from_peer_id_ucfg(void* peer_p,
                                                  uint8_t in_isr);
void llc_priv_generate_peer_rpa_from_peer_id_ucfg_weak(void* peer_p,
                                                       uint8_t in_isr);
void llc_priv_generate_peer_rpa_from_peer_id(void* peer_p,
                                             uint8_t in_isr);

void llc_priv_init_ucfg(uint8_t first_call);
void llc_priv_init_ucfg_weak(uint8_t first_call);
void llc_priv_init(uint8_t first_call);

void llc_priv_generate_local_rpa_from_peer_id_ucfg(void* peer_id_p,
                                                   void* local_rpa_p);
void llc_priv_generate_local_rpa_from_peer_id_ucfg_weak(void* peer_id_p,
                                                        void* local_rpa_p);
void llc_priv_generate_local_rpa_from_peer_id(void* peer_id_p,
                                              void* local_rpa_p);

void llc_priv_offline_rpa_resolution_ucfg(uint16_t task_idx);
void llc_priv_offline_rpa_resolution_ucfg_weak(uint16_t task_idx);
void llc_priv_offline_rpa_resolution(uint16_t task_idx);

uint32_t llc_priv_controller_privacy_csr_ucfg(void);
uint32_t llc_priv_controller_privacy_csr_ucfg_weak(void);
uint32_t llc_priv_controller_privacy_csr(void);

void llc_priv_set_filter_accept_list_flag_in_resolving_list_ucfg(void* addr8_p,
                                                                 uint8_t set);
void llc_priv_set_filter_accept_list_flag_in_resolving_list_ucfg_weak(void* addr8_p,
                                                                      uint8_t set);
void llc_priv_set_filter_accept_list_flag_in_resolving_list(void* addr8_p,
                                                            uint8_t set);

void llc_priv_clr_all_filter_accept_list_flags_in_resolving_list_ucfg(void);
void llc_priv_clr_all_filter_accept_list_flags_in_resolving_list_ucfg_weak(void);
void llc_priv_clr_all_filter_accept_list_flags_in_resolving_list(void);

void llc_priv_start_privacy_timer_ucfg(void);
void llc_priv_start_privacy_timer_ucfg_weak(void);
void llc_priv_start_privacy_timer(void);

void llc_priv_stop_privacy_timer_ucfg(void);
void llc_priv_stop_privacy_timer_ucfg_weak(void);
void llc_priv_stop_privacy_timer(void);

void llc_priv_init_random_part_of_one_local_rpa_ucfg(void* peer_id_p);
void llc_priv_init_random_part_of_one_local_rpa_ucfg_weak(void* peer_id_p);
void llc_priv_init_random_part_of_one_local_rpa(void* peer_id_p);

void llc_pscan_cancel_slot_cte_ucfg(void* cntxt_per_p);
void llc_pscan_cancel_slot_cte_ucfg_weak(void* cntxt_per_p);
void llc_pscan_cancel_slot_cte(void* cntxt_per_p);

uint8_t llc_pscan_isr_ucfg(void* cntxt_per_p);
uint8_t llc_pscan_isr_ucfg_weak(void* cntxt_per_p);
uint8_t llc_pscan_isr(void* cntxt_per_p);

void llc_pscan_init_ucfg(void);
void llc_pscan_init_ucfg_weak(void);
void llc_pscan_init(void);

void llc_pscan_mem_allocate_ucfg(uint8_t scan_en,
                                 uint8_t ext_en,
                                 uint8_t pscan_en);
void llc_pscan_mem_allocate_ucfg_weak(uint8_t scan_en,
                                      uint8_t ext_en,
                                      uint8_t pscan_en);
void llc_pscan_mem_allocate(uint8_t scan_en,
                            uint8_t ext_en,
                            uint8_t pscan_en);

uint8_t llc_pscan_create_sync_pending_ucfg(void);
uint8_t llc_pscan_create_sync_pending_ucfg_weak(void);
uint8_t llc_pscan_create_sync_pending(void);

void llc_pscan_enable_adv_addr_ucfg(void* list_p);
void llc_pscan_enable_adv_addr_ucfg_weak(void* list_p);
void llc_pscan_enable_adv_addr(void* list_p);

void llc_pscan_push_padv_report_event_ucfg(void* params);
void llc_pscan_push_padv_report_event_ucfg_weak(void* params);
void llc_pscan_push_padv_report_event(void* params);

void llc_pscan_push_past_received_event_ucfg(void* params);
void llc_pscan_push_past_received_event_ucfg_weak(void* params);
void llc_pscan_push_past_received_event(void* params);

void llc_pscan_push_sync_established_event_ucfg(void* params);
void llc_pscan_push_sync_established_event_ucfg_weak(void* params);
void llc_pscan_push_sync_established_event(void* params);

uint8_t llc_pscan_check_address_ucfg(void* addr_p);
uint8_t llc_pscan_check_address_ucfg_weak(void* addr_p);
uint8_t llc_pscan_check_address(void* addr_p);

void llc_pscan_synchronizing_ucfg(void* params_p);
void llc_pscan_synchronizing_ucfg_weak(void* params_p);
void llc_pscan_synchronizing(void* params_p);

void llc_pscan_wrong_cte_type_ucfg(void* cntxt_p);
void llc_pscan_wrong_cte_type_ucfg_weak(void* cntxt_p);
void llc_pscan_wrong_cte_type(void* cntxt_p);

void llc_pscan_wr_init_ucfg(void);
void llc_pscan_wr_init_ucfg_weak(void);
void llc_pscan_wr_init(void);

void llc_pscan_wr_mem_allocate_ucfg(uint8_t scan_en,
                                    uint8_t ext_en,
                                    uint8_t pscan_en,
                                    uint8_t pscan_wr_en,
                                    uint8_t conn_en);
void llc_pscan_wr_mem_allocate_ucfg_weak(uint8_t scan_en,
                                         uint8_t ext_en,
                                         uint8_t pscan_en,
                                         uint8_t pscan_wr_en,
                                         uint8_t conn_en);
void llc_pscan_wr_mem_allocate(uint8_t scan_en,
                               uint8_t ext_en,
                               uint8_t pscan_en,
                               uint8_t pscan_wr_en,
                               uint8_t conn_en);

void llc_pscan_wr_per_init_ucfg(uint8_t sync_idx);
void llc_pscan_wr_per_init_ucfg_weak(uint8_t sync_idx);
void llc_pscan_wr_per_init(uint8_t sync_idx);

void llc_pscan_wr_config_tx_blue_sm_ucfg(void* params_p,
                                         uint8_t pawr_feat);
void llc_pscan_wr_config_tx_blue_sm_ucfg_weak(void* params_p,
                                              uint8_t pawr_feat);
void llc_pscan_wr_config_tx_blue_sm(void* params_p,
                                    uint8_t pawr_feat);

uint8_t llc_pscan_wr_get_pawr_info_ucfg(uint8_t acad_size,
                                     uint8_t* acad_p,
                                     uint8_t* pawr_info_p);
uint8_t llc_pscan_wr_get_pawr_info_ucfg_weak(uint8_t acad_size,
                                          uint8_t* acad_p,
                                          uint8_t* pawr_info_p);
uint8_t llc_pscan_wr_get_pawr_info(uint8_t acad_size,
                                uint8_t* acad_p,
                                uint8_t* pawr_info_p);

uint8_t llc_pscan_wr_check_pawr_active_ucfg(uint8_t conn_idx);
uint8_t llc_pscan_wr_check_pawr_active_ucfg_weak(uint8_t conn_idx);
uint8_t llc_pscan_wr_check_pawr_active(uint8_t conn_idx);

uint8_t llc_pscan_wr_check_pawr_info_ucfg(void* params_p);
uint8_t llc_pscan_wr_check_pawr_info_ucfg_weak(void* params_p);
uint8_t llc_pscan_wr_check_pawr_info(void* params_p);

uint8_t llc_pscan_wr_reserve_taskslots_ucfg(void* params_p,
                                            uint8_t pawr_feat);
uint8_t llc_pscan_wr_reserve_taskslots_ucfg_weak(void* params_p,
                                                 uint8_t pawr_feat);
uint8_t llc_pscan_wr_reserve_taskslots(void* params_p,
                                       uint8_t pawr_feat);

void llc_pscan_wr_set_pscan_cntxt_ucfg(void* cntxt_p,
                                       void* params_p);
void llc_pscan_wr_set_pscan_cntxt_ucfg_weak(void* cntxt_p,
                                            void* params_p);
void llc_pscan_wr_set_pscan_cntxt(void* cntxt_p,
                                  void* params_p);

void llc_pscan_wr_set_scheduler_params_ucfg(void* params_p);
void llc_pscan_wr_set_scheduler_params_ucfg_weak(void* params_p);
void llc_pscan_wr_set_scheduler_params(void* params_p);

void llc_scan_conn_ind_sent_ucfg(void* ptr,
                                 uint8_t idx);
void llc_scan_conn_ind_sent_ucfg_weak(void* ptr,
                                      uint8_t idx);
void llc_scan_conn_ind_sent(void* ptr,
                            uint8_t idx);

uint8_t llc_scan_process_ext_adv_ucfg(void* scan_p,
                                   void* params_p,
                                   uint32_t direct_addr[2],
                                   uint8_t idx,
                                   uint8_t advertiser_addr_flag,
                                   uint8_t* send_report_p);
uint8_t llc_scan_process_ext_adv_ucfg_weak(void* scan_p,
                                        void* params_p,
                                        uint32_t direct_addr[2],
                                        uint8_t idx,
                                        uint8_t advertiser_addr_flag,
                                        uint8_t* send_report_p);
uint8_t llc_scan_process_ext_adv(void* scan_p,
                              void* params_p,
                              uint32_t direct_addr[2],
                              uint8_t idx,
                              uint8_t advertiser_addr_flag,
                              uint8_t* send_report_p);

void llc_scan_aux_conn_rsp_rcvd_ucfg(void* scan_p,
                                     void* aux_p,
                                     uint8_t idx);
void llc_scan_aux_conn_rsp_rcvd_ucfg_weak(void* scan_p,
                                          void* aux_p,
                                          uint8_t idx);
void llc_scan_aux_conn_rsp_rcvd(void* scan_p,
                                void* aux_p,
                                uint8_t idx);

void llc_scan_init_ucfg(uint8_t ext_en);
void llc_scan_init_ucfg_weak(uint8_t ext_en);
void llc_scan_init(uint8_t ext_en);

void llc_scan_mem_allocate_ucfg(uint8_t scan_en,
                                uint8_t ext_en);
void llc_scan_mem_allocate_ucfg_weak(uint8_t scan_en,
                                     uint8_t ext_en);
void llc_scan_mem_allocate(uint8_t scan_en,
                           uint8_t ext_en);

void llc_scan_prepare_conn_ind_req_ucfg(void* ptr,
                                        uint8_t idx,
                                        uint8_t aux_conn_req);
void llc_scan_prepare_conn_ind_req_ucfg_weak(void* ptr,
                                             uint8_t idx,
                                             uint8_t aux_conn_req);
void llc_scan_prepare_conn_ind_req(void* ptr,
                                   uint8_t idx,
                                   uint8_t aux_conn_req);

void llc_scan_enable_extended_ucfg(void* scan_p);
void llc_scan_enable_extended_ucfg_weak(void* scan_p);
void llc_scan_enable_extended(void* scan_p);

void llc_scan_push_ext_adv_report_ucfg(void* ptr,
                                       uint8_t data_len,
                                       uint8_t data_offset,
                                       uint8_t event_type);
void llc_scan_push_ext_adv_report_ucfg_weak(void* ptr,
                                            uint8_t data_len,
                                            uint8_t data_offset,
                                            uint8_t event_type);
void llc_scan_push_ext_adv_report(void* ptr,
                                  uint8_t data_len,
                                  uint8_t data_offset,
                                  uint8_t event_type);

tBleStatus llc_scan_reserve_taskslots_ucfg(void* scan_en_p,
                                           void* scan_p);
tBleStatus llc_scan_reserve_taskslots_ucfg_weak(void* scan_en_p,
                                                void* scan_p);
tBleStatus llc_scan_reserve_taskslots(void* scan_en_p,
                                      void* scan_p);

void llc_scan_set_conn_params_ucfg(Extended_Create_Connection_Parameters_t ext_create_conn_params,
                                   uint8_t initiating_phy);
void llc_scan_set_conn_params_ucfg_weak(Extended_Create_Connection_Parameters_t ext_create_conn_params,
                                        uint8_t initiating_phy);
void llc_scan_set_conn_params(Extended_Create_Connection_Parameters_t ext_create_conn_params,
                              uint8_t initiating_phy);

void llc_scan_disable_ucfg(void* scan_p);
void llc_scan_disable_ucfg_weak(void* scan_p);
void llc_scan_disable(void* scan_p);

uint8_t llc_subrate_get_active_sr_req_proc_ucfg(uint8_t conn_idx);
uint8_t llc_subrate_get_active_sr_req_proc_ucfg_weak(uint8_t conn_idx);
uint8_t llc_subrate_get_active_sr_req_proc(uint8_t conn_idx);

void llc_subrate_new_sr_base_event_ucfg(uint16_t sr_factor,
                                        uint16_t* sr_base_event_p);
void llc_subrate_new_sr_base_event_ucfg_weak(uint16_t sr_factor,
                                             uint16_t* sr_base_event_p);
void llc_subrate_new_sr_base_event(uint16_t sr_factor,
                                   uint16_t* sr_base_event_p);

void llc_subrate_update_cont_counter_ucfg(void* cntxt_p);
void llc_subrate_update_cont_counter_ucfg_weak(void* cntxt_p);
void llc_subrate_update_cont_counter(void* cntxt_p);

uint8_t llc_subrate_offline_processing_ucfg(void* cntxt_p);
uint8_t llc_subrate_offline_processing_ucfg_weak(void* cntxt_p);
uint8_t llc_subrate_offline_processing(void* cntxt_p);

void llc_mngm_csa2_select_subevent_channel_ucfg(uint8_t subevent_counter,
                                                uint8_t* subevent_index_p,
                                                uint16_t prn_s,
                                                uint8_t remapping_index_of_last_used_channel,
                                                uint16_t* prn_subevent_lu_p,
                                                uint16_t channel_identifier,
                                                void* _csa2_table_p,
                                                uint8_t* channel_index_p);
void llc_mngm_csa2_select_subevent_channel_ucfg_weak(uint8_t subevent_counter,
                                                     uint8_t* subevent_index_p,
                                                     uint16_t prn_s,
                                                     uint8_t remapping_index_of_last_used_channel,
                                                     uint16_t* prn_subevent_lu_p,
                                                     uint16_t channel_identifier,
                                                     void* _csa2_table_p,
                                                     uint8_t* channel_index_p);
void llc_mngm_csa2_select_subevent_channel(uint8_t subevent_counter,
                                           uint8_t* subevent_index_p,
                                           uint16_t prn_s,
                                           uint8_t remapping_index_of_last_used_channel,
                                           uint16_t* prn_subevent_lu_p,
                                           uint16_t channel_identifier,
                                           void* _csa2_table_p,
                                           uint8_t* channel_index_p);

void LL_cpe_init_length_update_ucfg(void);
void LL_cpe_init_length_update_ucfg_weak(void);
void LL_cpe_init_length_update(void);

void LL_cpe_init_phy_update_ucfg(void);
void LL_cpe_init_phy_update_ucfg_weak(void);
void LL_cpe_init_phy_update(void);

void LL_cpe_init_cte_ucfg(void);
void LL_cpe_init_cte_ucfg_weak(void);
void LL_cpe_init_cte(void);

void LL_cpe_init_past_ucfg(void);
void LL_cpe_init_past_ucfg_weak(void);
void LL_cpe_init_past(void);

void LL_cpe_init_pcl_ucfg(void);
void LL_cpe_init_pcl_ucfg_weak(void);
void LL_cpe_init_pcl(void);

void LL_cpe_init_conn_update_ucfg(void);
void LL_cpe_init_conn_update_ucfg_weak(void);
void LL_cpe_init_conn_update(void);

void LL_cpe_init_chmap_update_ucfg(void);
void LL_cpe_init_chmap_update_ucfg_weak(void);
void LL_cpe_init_chmap_update(void);

void LL_cpe_init_chc_enable_ucfg(void);
void LL_cpe_init_chc_enable_ucfg_weak(void);
void LL_cpe_init_chc_enable(void);

void LL_cpe_init_chc_reporting_ucfg(void);
void LL_cpe_init_chc_reporting_ucfg_weak(void);
void LL_cpe_init_chc_reporting(void);

void LL_cpe_init_subrate_ucfg(void);
void LL_cpe_init_subrate_ucfg_weak(void);
void LL_cpe_init_subrate(void);

void LL_cpe_init_sca_upd_ucfg(void);
void LL_cpe_init_sca_upd_ucfg_weak(void);
void LL_cpe_init_sca_upd(void);

void LL_cpe_init_cis_ucfg(void);
void LL_cpe_init_cis_ucfg_weak(void);
void LL_cpe_init_cis(void);

void LL_cpe_init_ucfg(void);
void LL_cpe_init_ucfg_weak(void);
void LL_cpe_init(void);

void LLC_channel_map_copy_to_cpf_context_ucfg(void* cntxt_p,
                                              uint8_t conn_idx);
void LLC_channel_map_copy_to_cpf_context_ucfg_weak(void* cntxt_p,
                                                   uint8_t conn_idx);
void LLC_channel_map_copy_to_cpf_context(void* cntxt_p,
                                         uint8_t conn_idx);

uint8_t LLC_channel_map_update_offline_processing_ucfg(uint8_t conn_idx);
uint8_t LLC_channel_map_update_offline_processing_ucfg_weak(uint8_t conn_idx);
uint8_t LLC_channel_map_update_offline_processing(uint8_t conn_idx);

void LLC_conn_init_chc_ctxt_ucfg(uint8_t conn_idx);
void LLC_conn_init_chc_ctxt_ucfg_weak(uint8_t conn_idx);
void LLC_conn_init_chc_ctxt(uint8_t conn_idx);

void LLC_chc_ll_cntxt_init_ucfg(void);
void LLC_chc_ll_cntxt_init_ucfg_weak(void);
void LLC_chc_ll_cntxt_init(void);

uint8_t LLC_chc_reporting_offline_processing_ucfg(uint8_t conn_idx);
uint8_t LLC_chc_reporting_offline_processing_ucfg_weak(uint8_t conn_idx);
uint8_t LLC_chc_reporting_offline_processing(uint8_t conn_idx);

void LL_cpf_cis_processing_ucfg(uint16_t task_idx);
void LL_cpf_cis_processing_ucfg_weak(uint16_t task_idx);
void LL_cpf_cis_processing(uint16_t task_idx);

void LL_conn_upd_max_tx_time_coded_ucfg(void* params);
void LL_conn_upd_max_tx_time_coded_ucfg_weak(void* params);
void LL_conn_upd_max_tx_time_coded(void* params);

void LL_conn_upd_data_length_change_event_ucfg(void* params);
void LL_conn_upd_data_length_change_event_ucfg_weak(void* params);
void LL_conn_upd_data_length_change_event(void* params);

void llc_conn_init_cte_ctxt_ucfg(uint8_t conn_idx);
void llc_conn_init_cte_ctxt_ucfg_weak(uint8_t conn_idx);
void llc_conn_init_cte_ctxt(uint8_t conn_idx);

uint8_t LLC_cte_request_procedure_ucfg(void* params);
uint8_t LLC_cte_request_procedure_ucfg_weak(void* params);
uint8_t LLC_cte_request_procedure(void* params);

void LLC_connection_cte_response_pause_resume_ucfg(uint8_t conn_idx,
                                                   uint8_t tx_phy);
void LLC_connection_cte_response_pause_resume_ucfg_weak(uint8_t conn_idx,
                                                        uint8_t tx_phy);
void LLC_connection_cte_response_pause_resume(uint8_t conn_idx,
                                              uint8_t tx_phy);

void LLC_connection_cte_response_disable_ucfg(uint8_t conn_idx,
                                              uint8_t taskslot_no);
void LLC_connection_cte_response_disable_ucfg_weak(uint8_t conn_idx,
                                                   uint8_t taskslot_no);
void LLC_connection_cte_response_disable(uint8_t conn_idx,
                                         uint8_t taskslot_no);

void llc_cte_process_rx_cte_ucfg(void* params,
                                 uint8_t cte_type);
void llc_cte_process_rx_cte_ucfg_weak(void* params,
                                      uint8_t cte_type);
void llc_cte_process_rx_cte(void* params,
                            uint8_t cte_type);

void LLC_authenticated_payload_timeout_processing_ucfg(uint16_t task_idx);
void LLC_authenticated_payload_timeout_processing_ucfg_weak(uint16_t task_idx);
void LLC_authenticated_payload_timeout_processing(uint16_t task_idx);

void llc_past_mem_allocate_ucfg(uint8_t scan_en,
                                uint8_t ext_en,
                                uint8_t pscan_en,
                                uint8_t conn_en);
void llc_past_mem_allocate_ucfg_weak(uint8_t scan_en,
                                     uint8_t ext_en,
                                     uint8_t pscan_en,
                                     uint8_t conn_en);
void llc_past_mem_allocate(uint8_t scan_en,
                           uint8_t ext_en,
                           uint8_t pscan_en,
                           uint8_t conn_en);

void LL_past_load_txctrl_packet_from_scanner_ucfg(void* params,
                                                  uint8_t* pdu_p,
                                                  uint32_t instant_anchor,
                                                  uint32_t connect_interval,
                                                  uint16_t connect_event_count,
                                                  uint16_t connect_event_cnt);
void LL_past_load_txctrl_packet_from_scanner_ucfg_weak(void* params,
                                                       uint8_t* pdu_p,
                                                       uint32_t instant_anchor,
                                                       uint32_t connect_interval,
                                                       uint16_t connect_event_count,
                                                       uint16_t connect_event_cnt);
void LL_past_load_txctrl_packet_from_scanner(void* params,
                                             uint8_t* pdu_p,
                                             uint32_t instant_anchor,
                                             uint32_t connect_interval,
                                             uint16_t connect_event_count,
                                             uint16_t connect_event_cnt);

void LL_periodicscan_deploy_scanner_from_past_ucfg(void* params,
                                                   uint8_t conn_idx,
                                                   uint8_t pawr_feat);
void LL_periodicscan_deploy_scanner_from_past_ucfg_weak(void* params,
                                                        uint8_t conn_idx,
                                                        uint8_t pawr_feat);
void LL_periodicscan_deploy_scanner_from_past(void* params,
                                              uint8_t conn_idx,
                                              uint8_t pawr_feat);

void LL_past_initialize_connect_context_ucfg(uint8_t conn_idx);
void LL_past_initialize_connect_context_ucfg_weak(uint8_t conn_idx);
void LL_past_initialize_connect_context(uint8_t conn_idx);

void LL_past_default_params_ucfg(uint8_t conn_idx);
void LL_past_default_params_ucfg_weak(uint8_t conn_idx);
void LL_past_default_params(uint8_t conn_idx);

void llc_conn_init_pcl_ctxt_ucfg(uint8_t conn_idx);
void llc_conn_init_pcl_ctxt_ucfg_weak(uint8_t conn_idx);
void llc_conn_init_pcl_ctxt(uint8_t conn_idx);

void LLC_pcl_hal_cntxt_init_ucfg(uintptr_t pcl_cntxt_p);
void LLC_pcl_hal_cntxt_init_ucfg_weak(uintptr_t pcl_cntxt_p);
void LLC_pcl_hal_cntxt_init(uintptr_t pcl_cntxt_p);

void LLC_pcl_incr_rx_packets_ucfg(uint8_t conn_idx);
void LLC_pcl_incr_rx_packets_ucfg_weak(uint8_t conn_idx);
void LLC_pcl_incr_rx_packets(uint8_t conn_idx);

void LLC_pcl_update_avg_rssi_ucfg(void* params);
void LLC_pcl_update_avg_rssi_ucfg_weak(void* params);
void LLC_pcl_update_avg_rssi(void* params);

void LLC_pcl_set_radio_tx_power_conn_start_ucfg(uint8_t conn_idx);
void LLC_pcl_set_radio_tx_power_conn_start_ucfg_weak(uint8_t conn_idx);
void LLC_pcl_set_radio_tx_power_conn_start(uint8_t conn_idx);

uint8_t LLC_pcl_get_radio_tx_power_ucfg(uint8_t conn_idx,
                                        uint8_t phy_idx);
uint8_t LLC_pcl_get_radio_tx_power_ucfg_weak(uint8_t conn_idx,
                                             uint8_t phy_idx);
uint8_t LLC_pcl_get_radio_tx_power(uint8_t conn_idx,
                                   uint8_t phy_idx);

void LLC_pcl_set_radio_tx_power_and_eval_indication_ucfg(uint8_t conn_idx,
                                                         uint8_t send_ind,
                                                         int8_t ind_delta,
                                                         uint8_t change_txpower);
void LLC_pcl_set_radio_tx_power_and_eval_indication_ucfg_weak(uint8_t conn_idx,
                                                              uint8_t send_ind,
                                                              int8_t ind_delta,
                                                              uint8_t change_txpower);
void LLC_pcl_set_radio_tx_power_and_eval_indication(uint8_t conn_idx,
                                                    uint8_t send_ind,
                                                    int8_t ind_delta,
                                                    uint8_t change_txpower);

uint8_t LLC_pcl_offline_processing_ucfg(uint8_t conn_idx);
uint8_t LLC_pcl_offline_processing_ucfg_weak(uint8_t conn_idx);
uint8_t LLC_pcl_offline_processing(uint8_t conn_idx);

tBleStatus LL_Read_RSSI_ucfg(int8_t* rssiVal,
                             uint16_t connHandle);
tBleStatus LL_Read_RSSI_ucfg_weak(int8_t* rssiVal,
                                  uint16_t connHandle);
tBleStatus LL_Read_RSSI(int8_t* rssiVal,
                        uint16_t connHandle);

uint8_t LLC_pcl_get_number_of_phys_ucfg(void);
uint8_t LLC_pcl_get_number_of_phys_ucfg_weak(void);
uint8_t LLC_pcl_get_number_of_phys(void);

void LL_phy_upd_compute_data_PDU_length_params_ucfg(void* params);
void LL_phy_upd_compute_data_PDU_length_params_ucfg_weak(void* params);
void LL_phy_upd_compute_data_PDU_length_params(void* params);

uint8_t LL_phy_upd_pending_ucfg(uint8_t conn_idx);
uint8_t LL_phy_upd_pending_ucfg_weak(uint8_t conn_idx);
uint8_t LL_phy_upd_pending(uint8_t conn_idx);

tBleStatus LL_phy_update_init_ucfg(void);
tBleStatus LL_phy_update_init_ucfg_weak(void);
tBleStatus LL_phy_update_init(void);

tBleStatus LL_phy_update_init_per_st_data_ucfg(uint8_t conn_idx);
tBleStatus LL_phy_update_init_per_st_data_ucfg_weak(uint8_t conn_idx);
tBleStatus LL_phy_update_init_per_st_data(uint8_t conn_idx);

void LL_phy_upd_evt_pending_check_isr_ucfg(uint8_t conn_idx);
void LL_phy_upd_evt_pending_check_isr_ucfg_weak(uint8_t conn_idx);
void LL_phy_upd_evt_pending_check_isr(uint8_t conn_idx);

void LLC_blueapi_cte_ucfg(void* params);
void LLC_blueapi_cte_ucfg_weak(void* params);
void LLC_blueapi_cte(void* params);

void LLC_connless_process_rx_cte_ucfg(uint8_t iq_samples_ready,
                                      void* params,
                                      uint8_t iq_samples_number,
                                      uint8_t rx_cte_type,
                                      uint8_t channel);
void LLC_connless_process_rx_cte_ucfg_weak(uint8_t iq_samples_ready,
                                           void* params,
                                           uint8_t iq_samples_number,
                                           uint8_t rx_cte_type,
                                           uint8_t channel);
void LLC_connless_process_rx_cte(uint8_t iq_samples_ready,
                                 void* params,
                                 uint8_t iq_samples_number,
                                 uint8_t rx_cte_type,
                                 uint8_t channel);

uint8_t LLC_check_iq_samples_ready_ucfg(uint8_t* iq_samples_number,
                                     uint8_t* channel,
                                     uint8_t taskslot_no);
uint8_t LLC_check_iq_samples_ready_ucfg_weak(uint8_t* iq_samples_number,
                                          uint8_t* channel,
                                          uint8_t taskslot_no);
uint8_t LLC_check_iq_samples_ready(uint8_t* iq_samples_number,
                                uint8_t* channel,
                                uint8_t taskslot_no);

void llc_cte_init_ucfg(void);
void llc_cte_init_ucfg_weak(void);
void llc_cte_init(void);

void llc_cte_mem_allocate_ucfg(uint8_t cte_en,
                               uint8_t scan_en,
                               uint8_t ext_en,
                               uint8_t periodic_en);
void llc_cte_mem_allocate_ucfg_weak(uint8_t cte_en,
                                    uint8_t scan_en,
                                    uint8_t ext_en,
                                    uint8_t periodic_en);
void llc_cte_mem_allocate(uint8_t cte_en,
                          uint8_t scan_en,
                          uint8_t ext_en,
                          uint8_t periodic_en);

void llc_cte_timer_error_ucfg(void);
void llc_cte_timer_error_ucfg_weak(void);
void llc_cte_timer_error(void);

void llc_cte_timer_start_ucfg(void* params);
void llc_cte_timer_start_ucfg_weak(void* params);
void llc_cte_timer_start(void* params);

uint8_t llc_cte_timer_stop_ucfg(void);
uint8_t llc_cte_timer_stop_ucfg_weak(void);
uint8_t llc_cte_timer_stop(void);

void LLC_test_process_rx_cte_ucfg(void* params);
void LLC_test_process_rx_cte_ucfg_weak(void* params);
void LLC_test_process_rx_cte(void* params);

void LLC_test_set_cte_ucfg(void* params);
void LLC_test_set_cte_ucfg_weak(void* params);
void LLC_test_set_cte(void* params);

void ADV_ISR_connect_request_received_ucfg(void* pointer,
                                           uint8_t* packet,
                                           void* PeerIDAddress_p);
void ADV_ISR_connect_request_received_ucfg_weak(void* pointer,
                                                uint8_t* packet,
                                                void* PeerIDAddress_p);
void ADV_ISR_connect_request_received(void* pointer,
                                      uint8_t* packet,
                                      void* PeerIDAddress_p);

void LL_eadv_EauxIsr_connect_response_sent_ucfg(void* pointer);
void LL_eadv_EauxIsr_connect_response_sent_ucfg_weak(void* pointer);
void LL_eadv_EauxIsr_connect_response_sent(void* pointer);

void LL_eadv_EauxIsr_connect_request_received_ucfg(void* pointer,
                                                   uint8_t* calibration_required);
void LL_eadv_EauxIsr_connect_request_received_ucfg_weak(void* pointer,
                                                        uint8_t* calibration_required);
void LL_eadv_EauxIsr_connect_request_received(void* pointer,
                                              uint8_t* calibration_required);

uint8_t EADV_start_request_radio_tasks_ucfg(void* pointer);
uint8_t EADV_start_request_radio_tasks_ucfg_weak(void* pointer);
uint8_t EADV_start_request_radio_tasks(void* pointer);

tBleStatus llc_eadv_max_supported_data_check_ucfg(uint16_t data_length,
                                                  void* pointer);
tBleStatus llc_eadv_max_supported_data_check_ucfg_weak(uint16_t data_length,
                                                       void* pointer);
tBleStatus llc_eadv_max_supported_data_check(uint16_t data_length,
                                             void* pointer);

void LL_eadv_start_extended_ucfg(void* pointer);
void LL_eadv_start_extended_ucfg_weak(void* pointer);
void LL_eadv_start_extended(void* pointer);

uint8_t ext_adv_scan_enabled_ucfg(void);
uint8_t ext_adv_scan_enabled_ucfg_weak(void);
uint8_t ext_adv_scan_enabled(void);

tBleStatus LL_Clear_Advertising_Sets_ucfg(void);
tBleStatus LL_Clear_Advertising_Sets_ucfg_weak(void);
tBleStatus LL_Clear_Advertising_Sets(void);

tBleStatus LL_Remove_Advertising_Set_ucfg(uint16_t Advertising_Handle);
tBleStatus LL_Remove_Advertising_Set_ucfg_weak(uint16_t Advertising_Handle);
tBleStatus LL_Remove_Advertising_Set(uint16_t Advertising_Handle);

uint8_t Data_Len_Update_Offline_Processing_ucfg(void* params,
                                             uint32_t ctrl_flds);
uint8_t Data_Len_Update_Offline_Processing_ucfg_weak(void* params,
                                                  uint32_t ctrl_flds);
uint8_t Data_Len_Update_Offline_Processing(void* params,
                                        uint32_t ctrl_flds);

tBleStatus ll_write_supported_data_ucfg(uint16_t Supported_Max_Tx_Octets,
                                        uint16_t Supported_Max_Tx_Time,
                                        uint16_t Supported_Max_Rx_Octets,
                                        uint16_t Supported_Max_Rx_Time);
tBleStatus ll_write_supported_data_ucfg_weak(uint16_t Supported_Max_Tx_Octets,
                                             uint16_t Supported_Max_Tx_Time,
                                             uint16_t Supported_Max_Rx_Octets,
                                             uint16_t Supported_Max_Rx_Time);
tBleStatus ll_write_supported_data(uint16_t Supported_Max_Tx_Octets,
                                   uint16_t Supported_Max_Tx_Time,
                                   uint16_t Supported_Max_Rx_Octets,
                                   uint16_t Supported_Max_Rx_Time);

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
                  uint8_t Chc);
void LL_init_ucfg_weak(uint8_t dataLenExt,
                       uint8_t PhyUpd,
                       uint8_t ExtAdvScan,
                       uint8_t CtrlPriv,
                       uint8_t ScanSupp,
                       uint8_t PerAdvScan,
                       uint8_t PerAdvScanWr,
                       uint8_t Cte,
                       uint8_t Pcl,
                       uint8_t Cns,
                       uint8_t Chc);
void LL_init(uint8_t dataLenExt,
             uint8_t PhyUpd,
             uint8_t ExtAdvScan,
             uint8_t CtrlPriv,
             uint8_t ScanSupp,
             uint8_t PerAdvScan,
             uint8_t PerAdvScanWr,
             uint8_t Cte,
             uint8_t Pcl,
             uint8_t Cns,
             uint8_t Chc);

tBleStatus smp_debug_trudy__set_config_ucfg(uint32_t config);
tBleStatus smp_debug_trudy__set_config_ucfg_weak(uint32_t config);
tBleStatus smp_debug_trudy__set_config(uint32_t config);

tBleStatus smp_start_encryption_ucfg(void* params);
tBleStatus smp_start_encryption_ucfg_weak(void* params);
tBleStatus smp_start_encryption(void* params);

tBleStatus smp_pp1_cei_send_pairing_request_ucfg(void* params);
tBleStatus smp_pp1_cei_send_pairing_request_ucfg_weak(void* params);
tBleStatus smp_pp1_cei_send_pairing_request(void* params);

tBleStatus smp_pp1_cei_rxp_pairing_response_excerpt_scp_ucfg(void* params);
tBleStatus smp_pp1_cei_rxp_pairing_response_excerpt_scp_ucfg_weak(void* params);
tBleStatus smp_pp1_cei_rxp_pairing_response_excerpt_scp(void* params);

void smp_pp2_cei_auth_stage1_start_excerpt_scp_ucfg(void* params);
void smp_pp2_cei_auth_stage1_start_excerpt_scp_ucfg_weak(void* params);
void smp_pp2_cei_auth_stage1_start_excerpt_scp(void* params);

void smp_pp2_per_auth_stage1_start_excerpt_scp_ucfg(void* params);
void smp_pp2_per_auth_stage1_start_excerpt_scp_ucfg_weak(void* params);
void smp_pp2_per_auth_stage1_start_excerpt_scp(void* params);

void smp_pp2_cei_send_pairing_confirm_excerpt_scp_ucfg(void* params);
void smp_pp2_cei_send_pairing_confirm_excerpt_scp_ucfg_weak(void* params);
void smp_pp2_cei_send_pairing_confirm_excerpt_scp(void* params);

tBleStatus smp_pp2_cei_rx_process_pairing_random_excerpt1_scp_ucfg(void* params);
tBleStatus smp_pp2_cei_rx_process_pairing_random_excerpt1_scp_ucfg_weak(void* params);
tBleStatus smp_pp2_cei_rx_process_pairing_random_excerpt1_scp(void* params);

void smp_pp2_cei_rx_process_pairing_random_excerpt2_scp_ucfg(void* params);
void smp_pp2_cei_rx_process_pairing_random_excerpt2_scp_ucfg_weak(void* params);
void smp_pp2_cei_rx_process_pairing_random_excerpt2_scp(void* params);

void smp_pp2_per_rx_process_pairing_confirm_excerpt_scp_ucfg(void* params);
void smp_pp2_per_rx_process_pairing_confirm_excerpt_scp_ucfg_weak(void* params);
void smp_pp2_per_rx_process_pairing_confirm_excerpt_scp(void* params);

void smp_pp2_per_rx_process_pairing_random_excerpt_scp_ucfg(void* params);
void smp_pp2_per_rx_process_pairing_random_excerpt_scp_ucfg_weak(void* params);
void smp_pp2_per_rx_process_pairing_random_excerpt_scp(void* params);

void smp_scp_init_ucfg(uint8_t use_debug_key);
void smp_scp_init_ucfg_weak(uint8_t use_debug_key);
void smp_scp_init(uint8_t use_debug_key);

tBleStatus smp_scp_continue_on_exclusive_sc_pairing_ucfg(void* params);
tBleStatus smp_scp_continue_on_exclusive_sc_pairing_ucfg_weak(void* params);
tBleStatus smp_scp_continue_on_exclusive_sc_pairing(void* params);

tBleStatus smp_scp_public_key_prepare_and_exchange_ucfg(void* params);
tBleStatus smp_scp_public_key_prepare_and_exchange_ucfg_weak(void* params);
tBleStatus smp_scp_public_key_prepare_and_exchange(void* params);

tBleStatus smp_scp_oob_generate_new_local_data_ucfg(void);
tBleStatus smp_scp_oob_generate_new_local_data_ucfg_weak(void);
tBleStatus smp_scp_oob_generate_new_local_data(void);

void smp_scp_stats_update_on_pairing_complete_ucfg(void* params);
void smp_scp_stats_update_on_pairing_complete_ucfg_weak(void* params);
void smp_scp_stats_update_on_pairing_complete(void* params);

void smp_fsm_process_actions_wrt_state_tsk_ucfg(uint16_t task_idx);
void smp_fsm_process_actions_wrt_state_tsk_ucfg_weak(uint16_t task_idx);
void smp_fsm_process_actions_wrt_state_tsk(uint16_t task_idx);

void smp_fsm_execute_actions_scp_phase2as2_ucfg(void* params);
void smp_fsm_execute_actions_scp_phase2as2_ucfg_weak(void* params);
void smp_fsm_execute_actions_scp_phase2as2(void* params);

void smp_fsm_execute_actions_excerpt_cei_ucfg(void* params);
void smp_fsm_execute_actions_excerpt_cei_ucfg_weak(void* params);
void smp_fsm_execute_actions_excerpt_cei(void* params);

void smp_pka_process_ecc_computation_tsk_ucfg(uint16_t task_idx);
void smp_pka_process_ecc_computation_tsk_ucfg_weak(uint16_t task_idx);
void smp_pka_process_ecc_computation_tsk(uint16_t task_idx);

void smp_rxp_process_rxed_packets_tsk_ucfg(uint16_t task_idx);
void smp_rxp_process_rxed_packets_tsk_ucfg_weak(uint16_t task_idx);
void smp_rxp_process_rxed_packets_tsk(uint16_t task_idx);

tBleStatus smp_rxp_process_exception_cases_excerpt_scp_ucfg(void* params);
tBleStatus smp_rxp_process_exception_cases_excerpt_scp_ucfg_weak(void* params);
tBleStatus smp_rxp_process_exception_cases_excerpt_scp(void* params);

tBleStatus smp_rxp_process_wrt_current_fsm_excerpt_scp_ucfg(void* params);
tBleStatus smp_rxp_process_wrt_current_fsm_excerpt_scp_ucfg_weak(void* params);
tBleStatus smp_rxp_process_wrt_current_fsm_excerpt_scp(void* params);

tBleStatus smp_rxp_process_wrt_current_fsm_excerpt_cei_ucfg(void* params);
tBleStatus smp_rxp_process_wrt_current_fsm_excerpt_cei_ucfg_weak(void* params);
tBleStatus smp_rxp_process_wrt_current_fsm_excerpt_cei(void* params);

void smp_init_ucfg(void);
void smp_init_ucfg_weak(void);
void smp_init(void);

void GAT_att_cmn_init_ucfg(void);
void GAT_att_cmn_init_ucfg_weak(void);
void GAT_att_cmn_init(void);

void GAT_att_cmn_timer_expire_tsk_ucfg(uint16_t task_idx);
void GAT_att_cmn_timer_expire_tsk_ucfg_weak(uint16_t task_idx);
void GAT_att_cmn_timer_expire_tsk(uint16_t task_idx);

void GAT_att_cmn_tx_pool_evt_tsk_ucfg(uint16_t task_idx);
void GAT_att_cmn_tx_pool_evt_tsk_ucfg_weak(uint16_t task_idx);
void GAT_att_cmn_tx_pool_evt_tsk(uint16_t task_idx);

void GAT_att_srv_process_rx_pckt_tsk_ucfg(uint16_t task_idx);
void GAT_att_srv_process_rx_pckt_tsk_ucfg_weak(uint16_t task_idx);
void GAT_att_srv_process_rx_pckt_tsk(uint16_t task_idx);

void GAT_srv_db_hash_tsk_ucfg(uint16_t task_idx);
void GAT_srv_db_hash_tsk_ucfg_weak(uint16_t task_idx);
void GAT_srv_db_hash_tsk(uint16_t task_idx);

void GAT_srv_send_srv_change_tsk_ucfg(uint16_t task_idx);
void GAT_srv_send_srv_change_tsk_ucfg_weak(uint16_t task_idx);
void GAT_srv_send_srv_change_tsk(uint16_t task_idx);

tBleStatus aci_gap_terminate_api(uint16_t Connection_Handle,
                                 uint8_t Reason);

tBleStatus aci_gap_start_connection_update_api(uint16_t Connection_Handle,
                                               uint16_t Connection_Interval_Min,
                                               uint16_t Connection_Interval_Max,
                                               uint16_t Max_Latency,
                                               uint16_t Supervision_Timeout,
                                               uint16_t Min_CE_Length,
                                               uint16_t Max_CE_Length);

tBleStatus aci_gap_set_scan_configuration_api(uint8_t duplicate_filtering,
                                              uint8_t scanning_filter_policy,
                                              uint8_t phy,
                                              uint8_t scan_type,
                                              uint16_t scan_interval,
                                              uint16_t scan_window);

tBleStatus aci_gap_set_connection_configuration_api(uint8_t phy,
                                                    uint16_t connection_interval_min,
                                                    uint16_t connection_interval_max,
                                                    uint16_t max_latency,
                                                    uint16_t supervision_timeout,
                                                    uint16_t min_ce_length,
                                                    uint16_t max_ce_length);

tBleStatus aci_gap_create_connection_api(uint8_t Initiating_PHY,
                                         uint8_t Peer_Address_Type,
                                         uint8_t Peer_Address[6]);

tBleStatus aci_gap_start_procedure_api(uint8_t procedure_code,
                                       uint8_t phys,
                                       uint16_t duration,
                                       uint16_t period);

tBleStatus aci_gap_discover_name_api(uint8_t PHYs,
                                     uint8_t Peer_Address_Type,
                                     uint8_t Peer_Address[6]);

tBleStatus aci_gap_terminate_proc_api(uint8_t Procedure_Code);

tBleStatus aci_gap_create_periodic_advertising_connection_api(uint8_t Advertising_Handle,
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
                                                              uint16_t Max_CE_Length);

tBleStatus aci_gap_remove_advertising_set_api(uint8_t Advertising_Handle);

tBleStatus aci_gap_clear_advertising_sets_api(void);

tBleStatus aci_gap_set_io_capability_api(uint8_t IO_Capability);

tBleStatus aci_gap_set_security_requirements_api(uint8_t Bonding_Mode,
                                                 uint8_t MITM_Mode,
                                                 uint8_t SC_Support,
                                                 uint8_t KeyPress_Notification_Support,
                                                 uint8_t Min_Encryption_Key_Size,
                                                 uint8_t Max_Encryption_Key_Size,
                                                 uint8_t Pairing_Response);

tBleStatus aci_gap_set_security_api(uint16_t Connection_Handle,
                                    uint8_t Security_Level,
                                    uint8_t Force_Pairing);

tBleStatus aci_gap_pairing_resp_api(uint16_t Connection_Handle,
                                    uint8_t Accept);

tBleStatus aci_gap_passkey_resp_api(uint16_t Connection_Handle,
                                    uint32_t Passkey);

tBleStatus aci_gap_passkey_input_api(uint16_t Connection_Handle,
                                     uint8_t Input_Type);

tBleStatus aci_gap_get_oob_data_api(uint8_t OOB_Data_Type,
                                    uint8_t* Address_Type,
                                    uint8_t Address[6],
                                    uint8_t* OOB_Data_Len,
                                    uint8_t OOB_Data[16]);

tBleStatus aci_gap_set_oob_data_api(uint8_t Device_Type,
                                    uint8_t Address_Type,
                                    uint8_t Address[6],
                                    uint8_t OOB_Data_Type,
                                    uint8_t OOB_Data_Len,
                                    uint8_t OOB_Data[16]);

tBleStatus aci_gap_numeric_comparison_value_confirm_yesno_api(uint16_t Connection_Handle,
                                                              uint8_t Confirm_Yes_No);

tBleStatus aci_gap_get_security_level_api(uint16_t Connection_Handle,
                                          uint8_t* Security_Mode,
                                          uint8_t* Security_Level);

tBleStatus aci_gap_clear_security_db_api(void);

tBleStatus aci_gap_get_bonded_devices_api(uint8_t Offset,
                                          uint8_t Max_Num_Of_Addresses,
                                          uint8_t* Num_of_Addresses,
                                          Bonded_Device_Entry_t* Bonded_Device_Entry);

tBleStatus aci_gap_is_device_bonded_api(uint8_t Peer_Address_Type,
                                        uint8_t Peer_Address[6]);

tBleStatus aci_gap_remove_bonded_device_api(uint8_t peerIdentityAddressType,
                                            uint8_t peerIdentityDeviceAddress[6]);

tBleStatus aci_gatt_srv_add_service_api(ble_gatt_srv_def_t* Serv_p);

tBleStatus aci_gatt_srv_rm_service_api(uint16_t Serv_Attr_H);

uint16_t aci_gatt_srv_get_service_handle_api(ble_gatt_srv_def_t* Serv_p);

tBleStatus aci_gatt_srv_include_service_api(uint16_t Serv_Attr_H,
                                            uint16_t Incl_Serv_Attr_H);

tBleStatus aci_gatt_srv_rm_include_service_api(uint16_t Incl_Serv_Attr_H);

uint16_t aci_gatt_srv_get_include_service_handle_api(uint16_t Serv_Attr_H,
                                                     ble_gatt_srv_def_t* Included_Srv_p);

tBleStatus aci_gatt_srv_add_char_api(ble_gatt_chr_def_t* Char_p,
                                     uint16_t Serv_Attr_H);

tBleStatus aci_gatt_srv_rm_char_api(uint16_t Char_Decl_Attr_H);

uint16_t aci_gatt_srv_get_char_decl_handle_api(ble_gatt_chr_def_t* Char_p);

tBleStatus aci_gatt_srv_add_char_desc_api(ble_gatt_descr_def_t* Descr_p,
                                          uint16_t Char_Attr_H);

uint16_t aci_gatt_srv_get_descriptor_handle_api(ble_gatt_descr_def_t* Descr_p);

tBleStatus aci_gatt_srv_notify_api(uint16_t Connection_Handle,
                                   uint16_t CID,
                                   uint16_t Attr_Handle,
                                   uint8_t Flags,
                                   uint16_t Val_Length,
                                   uint8_t* Val_p);

tBleStatus aci_gatt_srv_multi_notify_api(uint16_t Connection_Handle,
                                         uint16_t CID,
                                         uint8_t Flags,
                                         uint8_t Num_Of_Attr,
                                         Gatt_Srv_Notify_Attr_t* Gatt_Srv_Notify_Attr);

tBleStatus aci_gatt_srv_resp_api(uint16_t Connection_Handle,
                                 uint16_t CID,
                                 uint16_t Attr_Handle,
                                 uint8_t Error_Code,
                                 uint16_t Data_Len,
                                 uint8_t* Data_p);

tBleStatus aci_gatt_srv_read_handle_value_api(uint16_t Attr_Handle,
                                              uint16_t* Val_Length_p,
                                              uint8_t** Val_pp);

tBleStatus aci_gatt_srv_read_multiple_instance_handle_value_api(uint16_t Connection_Handle,
                                                                uint16_t Attr_Handle,
                                                                uint16_t* Val_Length_p,
                                                                uint8_t** Val_pp);

tBleStatus aci_gatt_srv_write_multiple_instance_handle_value_api(uint16_t Connection_Handle,
                                                                 uint16_t Attr_Handle,
                                                                 uint16_t Char_Value_Length,
                                                                 uint8_t* Char_Value);

tBleStatus aci_gatt_set_event_mask_api(uint32_t GATT_Evt_Mask);

tBleStatus aci_gatt_clt_exchange_config_api(uint16_t Connection_Handle);

tBleStatus aci_gatt_clt_disc_all_primary_services_api(uint16_t Connection_Handle,
                                                      uint16_t CID);

tBleStatus aci_gatt_clt_disc_primary_service_by_uuid_api(uint16_t Connection_Handle,
                                                         uint16_t CID,
                                                         uint8_t UUID_Type,
                                                         UUID_t* UUID);

tBleStatus aci_gatt_clt_disc_all_char_of_service_api(uint16_t Connection_Handle,
                                                     uint16_t CID,
                                                     uint16_t Start_Handle,
                                                     uint16_t End_Handle);

tBleStatus aci_gatt_clt_disc_char_by_uuid_api(uint16_t Connection_Handle,
                                              uint16_t CID,
                                              uint16_t Start_Handle,
                                              uint16_t End_Handle,
                                              uint8_t UUID_Type,
                                              UUID_t* UUID);

tBleStatus aci_gatt_clt_disc_all_char_desc_api(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t Char_Handle,
                                               uint16_t End_Handle);

tBleStatus aci_gatt_clt_find_included_services_api(uint16_t Connection_Handle,
                                                   uint16_t CID,
                                                   uint16_t Start_Handle,
                                                   uint16_t End_Handle);

tBleStatus aci_gatt_clt_read_api(uint16_t Connection_Handle,
                                 uint16_t CID,
                                 uint16_t Attr_Handle);

tBleStatus aci_gatt_clt_read_long_api(uint16_t Connection_Handle,
                                      uint16_t CID,
                                      uint16_t Attr_Handle,
                                      uint16_t Val_Offset);

tBleStatus aci_gatt_clt_read_using_char_uuid_api(uint16_t Connection_Handle,
                                                 uint16_t CID,
                                                 uint16_t Start_Handle,
                                                 uint16_t End_Handle,
                                                 uint8_t UUID_Type,
                                                 UUID_t* UUID);

tBleStatus aci_gatt_clt_read_multiple_char_value_api(uint16_t Connection_Handle,
                                                     uint16_t CID,
                                                     uint8_t Number_of_Handles,
                                                     uint16_t* Handle_Entry);

tBleStatus aci_gatt_clt_read_multiple_var_len_char_value_api(uint16_t Connection_Handle,
                                                             uint16_t CID,
                                                             uint8_t Number_of_Handles,
                                                             uint16_t* Handle_Entry);

tBleStatus aci_gatt_clt_write_without_resp_api(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t Attr_Handle,
                                               uint16_t Attribute_Val_Length,
                                               uint8_t* Attribute_Val);

tBleStatus aci_gatt_clt_signed_write_without_resp_api(uint16_t Connection_Handle,
                                                      uint16_t Attr_Handle,
                                                      uint16_t Attribute_Val_Length,
                                                      uint8_t* Attribute_Val);

tBleStatus aci_gatt_clt_write_api(uint16_t Connection_Handle,
                                  uint16_t CID,
                                  uint16_t Attr_Handle,
                                  uint16_t Attribute_Val_Length,
                                  uint8_t* Attribute_Val);

tBleStatus aci_gatt_clt_write_long_api(uint16_t Connection_Handle,
                                       uint16_t CID,
                                       ble_gatt_clt_write_ops_t* Write_Ops_p);

tBleStatus aci_gatt_clt_write_char_reliable_api(uint16_t Connection_Handle,
                                                uint16_t CID,
                                                uint8_t Num_Attrs,
                                                ble_gatt_clt_write_ops_t* Write_Ops_p);

tBleStatus aci_gatt_clt_prepare_write_req_api(uint16_t Connection_Handle,
                                              uint16_t CID,
                                              uint16_t Attr_Handle,
                                              uint16_t Val_Offset,
                                              uint16_t Attribute_Val_Length,
                                              uint8_t* Attribute_Val);

tBleStatus aci_gatt_clt_execute_write_req_api(uint16_t Connection_Handle,
                                              uint16_t CID,
                                              uint8_t Execute);

tBleStatus aci_gatt_clt_confirm_indication_api(uint16_t Connection_Handle,
                                               uint16_t CID);

tBleStatus aci_hal_peripheral_latency_enable_api(uint16_t Connection_Handle,
                                                 uint8_t Enable);

tBleStatus aci_hal_set_le_power_control_api(uint8_t Enable,
                                            uint8_t PHY,
                                            int8_t RSSI_Target,
                                            uint8_t RSSI_Hysteresis,
                                            int8_t Initial_TX_Power,
                                            uint8_t RSSI_Filtering_Coefficient);

tBleStatus aci_hal_get_anchor_point_api(uint16_t connection_handle,
                                        uint16_t* event_counter,
                                        uint32_t* anchor_point);

tBleStatus aci_l2cap_connection_parameter_update_req_api(uint16_t Connection_Handle,
                                                         uint16_t Connection_Interval_Min,
                                                         uint16_t Connection_Interval_Max,
                                                         uint16_t Peripheral_Latency,
                                                         uint16_t Timeout_Multiplier);

tBleStatus aci_l2cap_connection_parameter_update_resp_api(uint16_t Connection_Handle,
                                                          uint16_t Connection_Interval_Min,
                                                          uint16_t Connection_Interval_Max,
                                                          uint16_t Peripheral_Latency,
                                                          uint16_t Timeout_Multiplier,
                                                          uint16_t Min_CE_Length,
                                                          uint16_t Max_CE_Length,
                                                          uint8_t Identifier,
                                                          uint8_t Accept);

tBleStatus aci_l2cap_cos_connection_req_api(uint16_t connection_handle,
                                            uint16_t spsm,
                                            uint16_t mtu,
                                            uint16_t mps,
                                            uint8_t channel_type,
                                            uint8_t cid_count);

tBleStatus aci_l2cap_cos_connection_resp_api(uint16_t connection_handle,
                                             uint8_t identifier,
                                             uint16_t mtu,
                                             uint16_t mps,
                                             uint16_t result,
                                             uint8_t cid_count,
                                             uint16_t* local_cid);

tBleStatus aci_l2cap_cos_flow_control_credits_ind_api(uint16_t Connection_Handle,
                                                      uint16_t CID,
                                                      uint16_t RX_Credits,
                                                      uint8_t CFC_Policy,
                                                      uint16_t* RX_Credit_Balance);

tBleStatus aci_l2cap_cos_disconnect_req_api(uint16_t Connection_Handle,
                                            uint16_t CID);

tBleStatus aci_l2cap_cos_reconfigure_req_api(uint16_t connection_handle,
                                             uint16_t mtu,
                                             uint16_t mps,
                                             uint8_t cid_count,
                                             uint16_t* local_cid_array);

tBleStatus aci_l2cap_cos_reconfigure_resp_api(uint16_t connection_handle,
                                              uint8_t identifier,
                                              uint16_t result);

tBleStatus aci_l2cap_cos_sdu_data_transmit_api(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t SDU_Length,
                                               uint8_t* SDU_Data);

tBleStatus aci_l2cap_cos_sdu_data_extract_api(uint16_t Connection_Handle,
                                              uint16_t CID,
                                              uint16_t SDU_Data_Buffer_Size,
                                              void* SDU_Data_Buffer,
                                              uint16_t* SDU_Length);

tBleStatus hci_le_read_buffer_size_v2_api(uint16_t* HC_LE_ACL_Data_Packet_Length,
                                          uint8_t* HC_Total_Num_LE_ACL_Data_Packets,
                                          uint16_t* HC_LE_ISO_Data_Packet_Length,
                                          uint8_t* HC_Total_Num_LE_ISO_Data_Packets);

tBleStatus hci_le_create_big_test_api(uint8_t big_handle,
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
                                      uint8_t* broadcast_code_ext);

tBleStatus hci_le_big_create_sync_api(uint8_t BIG_Handle,
                                      uint16_t Sync_Handle,
                                      uint8_t Encryption,
                                      uint8_t* Broadcast_Code,
                                      uint8_t MSE,
                                      uint16_t BIG_Sync_Timeout,
                                      uint8_t Num_BIS,
                                      uint8_t* BIS);

tBleStatus hci_le_terminate_big_api(uint8_t Terminate_Big,
                                    uint8_t Reason);

tBleStatus hci_le_big_terminate_sync_api(uint8_t Big_handle);

tBleStatus hci_le_create_big_api(uint8_t big_handle,
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
                                 uint8_t* broadcast_code_ext);

tBleStatus hci_read_afh_channel_assessment_mode_api(uint8_t* AFH_Channel_Assessment_Mode);

tBleStatus hci_write_afh_channel_assessment_mode_api(uint8_t AFH_Channel_Assessment_Mode);

tBleStatus hci_le_set_host_channel_classification_api(uint8_t Channel_Map[LLC_MIN_NUM_DATA_CHAN_MAP_BYTES]);

tBleStatus hci_le_set_cig_parameters_api(uint8_t CIG_ID,
                                         uint8_t SDU_Interval_C_To_P[3],
                                         uint8_t SDU_Interval_P_To_C[3],
                                         uint8_t Worst_Case_SCA,
                                         uint8_t Packing,
                                         uint8_t Framing,
                                         uint16_t Max_Transport_Latency_C_To_P,
                                         uint16_t Max_Transport_Latency_P_To_C,
                                         uint8_t CIS_Count,
                                         CIS_Param_t* CIS_params,
                                         uint16_t* CIS_Conn_Handles);

tBleStatus hci_le_set_cig_parameters_test_api(uint8_t CIG_ID,
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
                                              uint16_t* CIS_Conn_Handles);

tBleStatus hci_le_create_cis_api(uint8_t CIS_Count,
                                 CIS_Handles_t* create_cis_connection_params);

tBleStatus hci_le_remove_cig_api(uint8_t CIG_ID);

tBleStatus hci_le_accept_cis_request_api(uint16_t Connection_Handle);

tBleStatus hci_le_reject_cis_request_api(uint16_t Connection_Handle,
                                         uint8_t Reason);

tBleStatus hci_read_connection_accept_timeout_api(uint16_t* Connection_Accept_Timeout);

tBleStatus hci_write_connection_accept_timeout_api(uint16_t Connection_Accept_Timeout);

tBleStatus hci_le_set_host_feature_api(uint8_t Bit_Number,
                                       uint8_t Bit_Value);

tBleStatus hci_read_remote_version_information_api(uint16_t Connection_Handle);

tBleStatus hci_le_read_remote_features_api(uint16_t Connection_Handle);

tBleStatus hci_read_transmit_power_level_api(uint16_t Connection_Handle,
                                             uint8_t Type,
                                             int8_t* Transmit_Power_Level);

tBleStatus hci_read_rssi_api(uint16_t Connection_Handle,
                             int8_t* RSSI);

tBleStatus hci_le_read_channel_map_api(uint16_t Connection_Handle,
                                       uint8_t LE_Channel_Map[LLC_MIN_NUM_DATA_CHAN_MAP_BYTES]);

tBleStatus hci_disconnect_api(uint16_t Connection_Handle,
                              uint8_t Reason);

tBleStatus hci_le_create_connection_api(uint16_t LE_Scan_Interval,
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
                                        uint16_t Max_CE_Length);

tBleStatus hci_le_create_connection_cancel_api(void);

tBleStatus hci_le_extended_create_connection_api(uint8_t Initiator_Filter_Policy,
                                                 uint8_t Own_Address_Type,
                                                 uint8_t Peer_Address_Type,
                                                 uint8_t Peer_Address[6],
                                                 uint8_t Initiating_PHYs,
                                                 Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters);

tBleStatus hci_le_extended_create_connection_v2_api(uint8_t Advertising_Handle,
                                                    uint8_t Subevent,
                                                    uint8_t Initiator_Filter_Policy,
                                                    uint8_t Own_Address_Type,
                                                    uint8_t Peer_Address_Type,
                                                    uint8_t Peer_Address[6],
                                                    uint8_t Initiating_PHYs,
                                                    Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters);

tBleStatus hci_le_set_connectionless_cte_transmit_parameters_api(uint8_t Advertising_Handle,
                                                                 uint8_t CTE_Length,
                                                                 uint8_t CTE_Type,
                                                                 uint8_t CTE_Count,
                                                                 uint8_t Switching_Pattern_Length,
                                                                 uint8_t* Antenna_IDs);

tBleStatus hci_le_set_connectionless_cte_transmit_enable_api(uint8_t Advertising_Handle,
                                                             uint8_t CTE_Enable);

tBleStatus hci_le_set_connectionless_iq_sampling_enable_api(uint16_t Sync_Handle,
                                                            uint8_t Sampling_Enable,
                                                            uint8_t Slot_Durations,
                                                            uint8_t Max_Sampled_CTEs,
                                                            uint8_t Switching_Pattern_Length,
                                                            uint8_t* Antenna_IDs);

tBleStatus hci_le_set_connection_cte_receive_parameters_api(uint16_t Connection_Handle,
                                                            uint8_t Sampling_Enable,
                                                            uint8_t Slot_Durations,
                                                            uint8_t Switching_Pattern_Length,
                                                            uint8_t* Antenna_IDs);

tBleStatus hci_le_set_connection_cte_transmit_parameters_api(uint16_t Connection_Handle,
                                                             uint8_t CTE_Type,
                                                             uint8_t Switching_Pattern_Length,
                                                             uint8_t* Antenna_IDs);

tBleStatus hci_le_connection_cte_request_enable_api(uint16_t Connection_Handle,
                                                    uint8_t Enable,
                                                    uint16_t CTE_Request_Interval,
                                                    uint8_t Requested_CTE_Length,
                                                    uint8_t Requested_CTE_Type);

tBleStatus hci_le_connection_cte_response_enable_api(uint16_t Connection_Handle,
                                                     uint8_t Enable);

tBleStatus hci_le_read_antenna_information_api(uint8_t* Supported_Switching_Sampling_Rates,
                                               uint8_t* Num_Antennae,
                                               uint8_t* Max_Switching_Pattern_Length,
                                               uint8_t* Max_CTE_Length);

tBleStatus hci_le_enable_encryption_api(uint16_t Connection_Handle,
                                        uint8_t Random_Number[8],
                                        uint16_t Encrypted_Diversifier,
                                        uint8_t Long_Term_Key[16]);

tBleStatus hci_le_long_term_key_request_reply_api(uint16_t Connection_Handle,
                                                  uint8_t Long_Term_Key[16]);

tBleStatus hci_le_long_term_key_request_negative_reply_api(uint16_t Connection_Handle);

tBleStatus hci_le_read_local_p256_public_key_api(void);

tBleStatus hci_le_generate_dhkey_api(uint8_t Remote_P256_Public_Key[64]);

tBleStatus hci_read_authenticated_payload_timeout_api(uint16_t Connection_Handle,
                                                      uint16_t* Authenticated_Payload_Timeout);

tBleStatus hci_write_authenticated_payload_timeout_api(uint16_t Connection_Handle,
                                                       uint16_t Authenticated_Payload_Timeout);

tBleStatus hci_le_set_extended_advertising_parameters_api(uint8_t Advertising_Handle,
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
                                                          int8_t* Selected_Tx_Power);

tBleStatus hci_le_set_extended_advertising_parameters_v2_api(uint8_t Advertising_Handle,
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
                                                             int8_t* Selected_Tx_Power);

tBleStatus hci_le_set_advertising_set_random_address_api(uint8_t Advertising_Handle,
                                                         uint8_t Advertising_Random_Address[6]);

tBleStatus hci_le_set_extended_advertising_enable_api(uint8_t Enable,
                                                      uint8_t Number_of_Sets,
                                                      Advertising_Set_Parameters_t* Advertising_Set_Parameters);

tBleStatus hci_le_read_number_of_supported_advertising_sets_api(uint8_t* Num_Supported_Advertising_Sets);

tBleStatus hci_le_remove_advertising_set_api(uint8_t Advertising_Handle);

tBleStatus hci_le_clear_advertising_sets_api(void);

tBleStatus hci_le_set_default_periodic_advertising_sync_transfer_parameters_api(uint8_t Mode,
                                                                                uint16_t Skip,
                                                                                uint16_t Sync_Timeout,
                                                                                uint8_t CTE_Type);

tBleStatus hci_le_set_periodic_advertising_sync_transfer_parameters_api(uint16_t Connection_Handle,
                                                                        uint8_t Mode,
                                                                        uint16_t Skip,
                                                                        uint16_t Sync_Timeout,
                                                                        uint8_t CTE_Type);

tBleStatus hci_le_periodic_advertising_set_info_transfer_api(uint16_t Connection_Handle,
                                                             uint16_t Service_Data,
                                                             uint8_t Advertising_Handle);

tBleStatus hci_le_periodic_advertising_sync_transfer_api(uint16_t Connection_Handle,
                                                         uint16_t Service_Data,
                                                         uint16_t Sync_Handle);

tBleStatus hci_le_iso_transmit_test_api(uint16_t Connection_Handle,
                                        uint8_t Payload_Type);

tBleStatus hci_le_iso_receive_test_api(uint16_t Connection_Handle,
                                       uint8_t Payload_Type);

tBleStatus hci_le_iso_read_test_counters_api(uint16_t Connection_Handle,
                                             uint32_t* Received_Packet_Count,
                                             uint32_t* Missed_Packet_Count,
                                             uint32_t* Failed_Packet_Count);

tBleStatus hci_le_iso_test_end_api(uint16_t Connection_Handle,
                                   uint32_t* Received_Packet_Count,
                                   uint32_t* Missed_Packet_Count,
                                   uint32_t* Failed_Packet_Count);

tBleStatus hci_le_setup_iso_data_path_api(uint16_t Connection_Handle,
                                          uint8_t Data_Path_Direction,
                                          uint8_t Data_Path_ID,
                                          uint8_t* CODEC_ID,
                                          uint8_t* Controller_Delay,
                                          uint8_t Codec_Configuration_Length,
                                          uint8_t* Codec_Configuration);

tBleStatus hci_le_remove_iso_data_path_api(uint16_t Connection_Handle,
                                           uint8_t Data_Path_Direction);

tBleStatus hci_le_read_iso_link_quality_api(uint16_t connection_handle,
                                            uint32_t* tx_unacked_packets,
                                            uint32_t* tx_flushed_packets,
                                            uint32_t* tx_last_subevent_packets,
                                            uint32_t* retransmitted_packets,
                                            uint32_t* CRC_error_packets,
                                            uint32_t* rx_unreceived_packets,
                                            uint32_t* duplicate_packets);

tBleStatus hci_le_read_iso_tx_sync_api(uint16_t connection_handle,
                                       uint16_t* packet_sequence_number,
                                       uint32_t* timestamp,
                                       uint8_t* timeoffset);

tBleStatus hci_tx_iso_data_api(uint16_t connection_handle,
                               uint8_t pb_flag,
                               uint8_t ts_flag,
                               uint16_t iso_data_load_len,
                               uint8_t* iso_data_load_p);

tBleStatus hci_le_set_data_length_api(uint16_t Connection_Handle,
                                      uint16_t Tx_Octets,
                                      uint16_t Tx_Time);

tBleStatus hci_le_read_suggested_default_data_length_api(uint16_t* Suggested_Max_Tx_Octets,
                                                         uint16_t* Suggested_Max_Tx_Time);

tBleStatus hci_le_write_suggested_default_data_length_api(uint16_t Suggested_Max_Tx_Octets,
                                                          uint16_t Suggested_Max_Tx_Time);

tBleStatus hci_le_read_maximum_data_length_api(uint16_t* Supported_Max_Tx_Octets,
                                               uint16_t* Supported_Max_Tx_Time,
                                               uint16_t* Supported_Max_Rx_Octets,
                                               uint16_t* Supported_Max_Rx_Time);

tBleStatus hci_le_set_periodic_advertising_parameters_api(uint8_t Advertising_Handle,
                                                          uint16_t Periodic_Advertising_Interval_Min,
                                                          uint16_t Periodic_Advertising_Interval_Max,
                                                          uint16_t Periodic_Advertising_Properties);

tBleStatus hci_le_set_periodic_advertising_enable_api(uint8_t Enable,
                                                      uint8_t Advertising_Handle);

tBleStatus hci_le_set_periodic_advertising_parameters_v2_api(uint8_t Advertising_Handle,
                                                             uint16_t Periodic_Advertising_Interval_Min,
                                                             uint16_t Periodic_Advertising_Interval_Max,
                                                             uint16_t Periodic_Advertising_Properties,
                                                             uint8_t Num_Subevents,
                                                             uint8_t Subevent_Interval,
                                                             uint8_t Response_Slot_Delay,
                                                             uint8_t Response_Slot_Spacing,
                                                             uint8_t Num_Response_Slots);

tBleStatus hci_le_enhanced_read_transmit_power_level_api(uint16_t Connection_Handle,
                                                         uint8_t PHY,
                                                         int8_t* Current_TX_Power_Level,
                                                         int8_t* Max_TX_Power_Level);

tBleStatus hci_le_read_remote_transmit_power_level_api(uint16_t Connection_Handle,
                                                       uint8_t PHY);

tBleStatus hci_le_set_path_loss_reporting_parameters_api(uint16_t Connection_Handle,
                                                         uint8_t High_Threshold,
                                                         uint8_t High_Hysteresis,
                                                         uint8_t Low_Threshold,
                                                         uint8_t Low_Hysteresis,
                                                         uint16_t Min_Time_Spent);

tBleStatus hci_le_set_path_loss_reporting_enable_api(uint16_t Connection_Handle,
                                                     uint8_t Enable);

tBleStatus hci_le_set_transmit_power_reporting_enable_api(uint16_t Connection_Handle,
                                                          uint8_t Local_Enable,
                                                          uint8_t Remote_Enable);

tBleStatus hci_le_read_phy_api(uint16_t Connection_Handle,
                               uint8_t* TX_PHY,
                               uint8_t* RX_PHY);

tBleStatus hci_le_set_default_phy_api(uint8_t ALL_PHYS,
                                      uint8_t TX_PHYS,
                                      uint8_t RX_PHYS);

tBleStatus hci_le_set_phy_api(uint16_t Connection_Handle,
                              uint8_t ALL_PHYS,
                              uint8_t TX_PHYS,
                              uint8_t RX_PHYS,
                              uint16_t PHY_options);

tBleStatus hci_le_add_device_to_resolving_list_api(uint8_t Peer_Identity_Address_Type,
                                                   uint8_t Peer_Identity_Address[6],
                                                   uint8_t Peer_IRK[16],
                                                   uint8_t Local_IRK[16]);

tBleStatus hci_le_remove_device_from_resolving_list_api(uint8_t Peer_Identity_Address_Type,
                                                        uint8_t Peer_Identity_Address[6]);

tBleStatus hci_le_clear_resolving_list_api(void);

tBleStatus hci_le_read_resolving_list_size_api(uint8_t* Resolving_List_Size);

tBleStatus hci_le_read_peer_resolvable_address_api(uint8_t Peer_Identity_Address_Type,
                                                   uint8_t Peer_Identity_Address[6],
                                                   uint8_t Peer_Resolvable_Address[6]);

tBleStatus hci_le_read_local_resolvable_address_api(uint8_t Peer_Identity_Address_Type,
                                                    uint8_t Peer_Identity_Address[6],
                                                    uint8_t Local_Resolvable_Address[6]);

tBleStatus hci_le_set_address_resolution_enable_api(uint8_t Address_Resolution_Enable);

tBleStatus hci_le_set_resolvable_private_address_timeout_api(uint16_t RPA_Timeout);

tBleStatus hci_le_set_privacy_mode_api(uint8_t Peer_Identity_Address_Type,
                                       uint8_t Peer_Identity_Address[6],
                                       uint8_t Privacy_Mode);

tBleStatus hci_le_set_data_related_address_changes_api(uint8_t Advertising_Handle,
                                                       uint8_t Change_Reasons);

tBleStatus hci_le_add_device_to_periodic_advertiser_list_api(uint8_t Advertiser_Address_Type,
                                                             uint8_t Advertiser_Address[6],
                                                             uint8_t Advertising_SID);

tBleStatus hci_le_clear_periodic_advertiser_list_api(void);

tBleStatus hci_le_periodic_advertising_create_sync_api(uint8_t Options,
                                                       uint8_t Advertising_SID,
                                                       uint8_t Advertising_Address_Type,
                                                       uint8_t Advertiser_Address[6],
                                                       uint16_t Skip,
                                                       uint16_t Sync_Timeout,
                                                       uint8_t Sync_CTE_Type);

tBleStatus hci_le_periodic_advertising_create_sync_cancel_api(void);

tBleStatus hci_le_periodic_advertising_terminate_sync_api(uint16_t Sync_Handle);

tBleStatus hci_le_read_periodic_advertiser_list_size_api(uint8_t* Periodic_Advertiser_List_Size);

tBleStatus hci_le_remove_device_from_periodic_advertiser_list_api(uint8_t Advertiser_Address_Type,
                                                                  uint8_t Advertiser_Address[6],
                                                                  uint8_t Advertising_SID);

tBleStatus hci_le_set_periodic_advertising_receive_enable_api(uint16_t Sync_Handle,
                                                              uint8_t Enable);

tBleStatus hci_le_set_periodic_sync_subevent_api(uint16_t Sync_Handle,
                                                 uint16_t Periodic_Advertising_Properties,
                                                 uint8_t Num_Subevents,
                                                 uint8_t* Subevent);

tBleStatus hci_le_request_peer_sca_api(uint16_t Connection_Handle);

tBleStatus hci_le_set_scan_parameters_api(uint8_t LE_Scan_Type,
                                          uint16_t LE_Scan_Interval,
                                          uint16_t LE_Scan_Window,
                                          uint8_t Own_Address_Type,
                                          uint8_t Scanning_Filter_Policy);

tBleStatus hci_le_set_scan_enable_api(uint8_t LE_Scan_Enable,
                                      uint8_t Filter_Duplicates);

tBleStatus hci_le_set_extended_scan_parameters_api(uint8_t Own_Address_Type,
                                                   uint8_t Scanning_Filter_Policy,
                                                   uint8_t Scanning_PHYs,
                                                   Extended_Scan_Parameters_t* Extended_Scan_Parameters);

tBleStatus hci_le_set_extended_scan_enable_api(uint8_t Enable,
                                               uint8_t Filter_Duplicates,
                                               uint16_t Duration,
                                               uint16_t Period);

tBleStatus hci_le_connection_update_api(uint16_t Connection_Handle,
                                        uint16_t Connection_Interval_Min,
                                        uint16_t Connection_Interval_Max,
                                        uint16_t Max_Latency,
                                        uint16_t Supervision_Timeout,
                                        uint16_t Min_CE_Length,
                                        uint16_t Max_CE_Length);

tBleStatus hci_le_set_default_subrate_api(uint16_t Subrate_Min,
                                          uint16_t Subrate_Max,
                                          uint16_t Max_Latency,
                                          uint16_t Continuation_Number,
                                          uint16_t Supervision_Timeout);

tBleStatus hci_le_subrate_request_api(uint16_t Connection_Handle,
                                      uint16_t Subrate_Min,
                                      uint16_t Subrate_Max,
                                      uint16_t Max_Latency,
                                      uint16_t Continuation_Number,
                                      uint16_t Supervision_Timeout);

tBleStatus hci_le_receiver_test_v2_api(uint8_t RX_Frequency,
                                       uint8_t Phy,
                                       uint8_t Modulation_index);

tBleStatus hci_le_receiver_test_v3_api(uint8_t RX_Channel,
                                       uint8_t PHY,
                                       uint8_t Modulation_Index,
                                       uint8_t Expected_CTE_Length,
                                       uint8_t Expected_CTE_Type,
                                       uint8_t Slot_Durations,
                                       uint8_t Switching_Pattern_Length,
                                       uint8_t* Antenna_IDs);

tBleStatus hci_le_transmitter_test_v2_api(uint8_t TX_Frequency,
                                          uint8_t Length_Of_Test_Data,
                                          uint8_t Packet_Payload,
                                          uint8_t Phy);

tBleStatus hci_le_transmitter_test_v3_api(uint8_t TX_Channel,
                                          uint8_t Test_Data_Length,
                                          uint8_t Packet_Payload,
                                          uint8_t PHY,
                                          uint8_t CTE_Length,
                                          uint8_t CTE_Type,
                                          uint8_t Switching_Pattern_Length,
                                          uint8_t* Antenna_IDs);

tBleStatus hci_le_transmitter_test_v4_api(uint8_t TX_Channel,
                                          uint8_t Test_Data_Length,
                                          uint8_t Packet_Payload,
                                          uint8_t PHY,
                                          uint8_t CTE_Length,
                                          uint8_t CTE_Type,
                                          uint8_t Switching_Pattern_Length,
                                          uint8_t* Antenna_IDs,
                                          int8_t Transmit_Power_Level);


void Get_Random_Addr(uint8_t *randBdAddr);

#endif /* BLE_STACK_USER_CFG_H */

