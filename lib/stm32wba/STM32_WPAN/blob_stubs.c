/*
 * Copyright (c) 2026 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Empty function stubs to enable building with CONFIG_BUILD_ONLY_NO_BLOBS.
 */

#include <cmsis_compiler.h>
#if defined(CONFIG_BT_STM32WBA)
#include <blestack.h>
#include <bleplat.h>
#endif /* CONFIG_BT_STM32WBA */
#include <ll_intf_cmn.h>
#include <ll_sys.h>
#include <ll_intf.h>
#include <os_wrapper.h>
#include <event_manager.h>
#include <evnt_schdlr_gnrc_if.h>
#if defined(CONFIG_IEEE802154_STM32WBA)
#include <st_802154_ral_callbacks.h>
#endif /* CONFIG_IEEE802154_STM32WBA */

#if defined(CONFIG_BT_STM32WBA)
tBleStatus BleStack_Init( const BleStack_init_t* init_params_p )
{
	(void)init_params_p;
	return 0;
}

uint8_t BleStack_Process( void )
{
	return 0;
}

uint16_t BleStack_Request( uint8_t* buffer )
{
	(void)buffer;
	return 0;
}

void BLEPLATCB_PkaComplete( void )
{

}

void ll_intf_chng_evnt_hndlr_state(change_state_options_t options)
{
	(void)options;
}
#endif /* CONFIG_BT_STM32WBA */

ble_stat_t ll_intf_init(const struct hci_dispatch_tbl* p_dispatch_tbl,
	uint8_t num_sm_needed,
	int8_t *ll_memory_buffer,
	uint16_t ll_memory_buffer_size,
	uint32_t supported_feature
	)
{
	(void)p_dispatch_tbl;
	(void)num_sm_needed;
	(void)ll_memory_buffer;
	(void)ll_memory_buffer_size;
	(void)supported_feature;
	return 0;
}

uint8_t ll_intf_cmn_get_slptmr_state(void)
{
	return 0;
}

void ll_intf_cmn_set_temperature_sensor_state(void)
{

}

uint32_t  ll_intf_cmn_set_temperature_value(uint32_t temperature)
{
	(void)temperature;
	return 0;
}

ble_stat_t ll_intf_cmn_le_set_dp_slp_mode(uint8_t dp_slp_mode)
{
	(void)dp_slp_mode;
	return 0;
}

ble_stat_t ll_intf_cmn_le_select_slp_clk_src(uint8_t slp_clk_src, uint16_t *ptr_slp_clk_freq_value)
{
	(void)slp_clk_src;
	(void)ptr_slp_clk_freq_value;
	return 0;
}

ble_stat_t ll_intf_cmn_config_ll_ctx_params(uint8_t allow_low_isr, uint8_t run_post_evnt_frm_isr)
{
	(void)allow_low_isr;
	(void)run_post_evnt_frm_isr;
	return 0;
}

void hci_get_dis_tbl(const struct hci_dispatch_tbl** p_p_dispatch_tbl)
{
	(void)p_p_dispatch_tbl;
}

void *ble_memcpy(void *ptr_dstntion, const void *ptr_src, uint16_t n)
{
	(void)ptr_dstntion;
	(void)ptr_src;
	(void)n;
	return 0;
}

void *ble_memset(void *ptr_mem,	uint8_t value, uint16_t n)
{
	(void)ptr_mem;
	(void)value;
	(void)n;
	return 0;
}

int8_t ble_memcmp(const void *ptr_dstntion, const void *ptr_src, uint16_t n)
{
	(void)ptr_dstntion;
	(void)ptr_src;
	(void)n;
	return 0;
}

void *ble_memmov(void *ptr_dstntion, const void *ptr_src, uint16_t n)
{
	(void)ptr_dstntion;
	(void)ptr_src;
	(void)n;
	return 0;
}

void ble_memcpy_n_bytes(uint8_t *destination,
			const uint8_t *source,
			uint8_t num_bytes,
			uint8_t keep_endian)
{
	(void)destination;
	(void)source;
	(void)num_bytes;
	(void)keep_endian;
}

void* os_timer_create(t_timer_callbk p_callbk, os_timer_type type, void *argument)
{
	(void)p_callbk;
	(void)type;
	(void)argument;
	return 0;
}

void os_timer_set_prio(os_timer_id timer_id, os_timer_prio tmr_prio)
{
	(void)timer_id;
	(void)tmr_prio;
}

os_timer_state os_get_tmr_state(os_timer_id timer_id)
{
	(void)timer_id;
	return 0;
}

int32_t os_timer_start(os_timer_id timer_id, uint32_t steps)
{
	(void)timer_id;
	(void)steps;
	return 0;
}

int32_t os_timer_free(os_timer_id timer_id)
{
	(void)timer_id;
	return 0;
}

int32_t os_timer_stop(os_timer_id timer_id)
{
	(void)timer_id;
	return 0;
}

void * os_mem_pool_alloc(os_pool_def_t * pool)
{
	(void)pool;
	return 0;
}

void os_mem_pool_free(void *block)
{
	(void)block;
}

void* os_shrd_mem_alloc(os_pool_def_t * pool)
{
	(void)pool;
	return 0;
}

uint8_t emngr_can_mcu_sleep(void)
{
	return 0;
}

void emngr_handle_all_events(void)
{

}

ext_evnt_hndl_t evnt_schdlr_rgstr_gnrc_evnt(extrnl_evnt_st_t* p_extrnl_evnt_st)
{
	(void)p_extrnl_evnt_st;
	return 0;
}

uint32_t evnt_schdlr_gnrc_evnt_cmplt(ext_evnt_hndl_t evnt_hndl)
{
	(void)evnt_hndl;
	return 0;
}

#if defined(CONFIG_IEEE802154_STM32WBA)
void st_802154_ral_init(void)
{

}

void st_802154_ral_set_channel(uint8_t channel)
{
	(void)channel;
}

uint8_t st_802154_ral_channel_get(void)
{
	return 0;
}

st_802154_ral_error_t st_802154_ral_tx_power_set(int8_t a_power)
{
	(void)a_power;
	return 0;
}

st_802154_ral_error_t st_802154_ral_tx_power_get(int8_t *a_power_ptr)
{
	(void)a_power_ptr;
	return 0;
}

uint64_t st_802154_ral_time_get(void)
{
	return 0;
}

void st_802154_ral_pan_id_set(const uint16_t a_pan_id)
{
	(void)a_pan_id;
}

void st_802154_ral_extended_address_set(const uint8_t* a_ext_address_ptr)
{
	(void)a_ext_address_ptr;
}

void st_802154_ral_short_address_set(const uint16_t a_short_address)
{
	(void)a_short_address;
}

void st_802154_ral_eui64_get(uint8_t* a_eui64_ptr)
{
	(void)a_eui64_ptr;
}

st_802154_ral_error_t st_802154_ral_sleep(void)
{
	return 0;
}

st_802154_ral_error_t st_802154_ral_receive(uint8_t a_channel)
{
	(void)a_channel;
	return 0;
}

st_802154_ral_error_t st_802154_ral_transmit(
					uint8_t* a_data_ptr,
					uint8_t a_length,
					const st_802154_ral_transmit_metadata_t* a_meta_data)
{
	(void)a_data_ptr;
	(void)a_length;
	(void)a_meta_data;
	return 0;
}

st_802154_ral_error_t st_802154_ral_energy_detection(
					uint16_t a_scan_duration,
					const st_802154_ral_scan_ed_metadata_t* a_meta_data)

{
	(void)a_scan_duration;
	(void)a_meta_data;
	return 0;
}

st_802154_ral_error_t st_802154_ral_cca(void)
{
	return 0;
}

void st_802154_ral_promiscuous_set(bool a_enabled)
{
	(void)a_enabled;
}

bool st_802154_ral_promiscuous_get(void)
{
	return 0;
}

void st_802154_ral_pan_coord_set(bool a_enabled)
{
	(void)a_enabled;
}

void st_802154_ral_auto_pending_bit_set(bool a_enabled)
{
	(void)a_enabled;
}

st_802154_ral_error_t st_802154_ral_pending_bit_for_short_addr_set(const uint16_t a_short_address)
{
	(void)a_short_address;
	return 0;
}

st_802154_ral_error_t st_802154_ral_pending_bit_for_ext_addr_set(const uint8_t* a_ext_address_ptr)
{
	(void)a_ext_address_ptr;
	return 0;
}

st_802154_ral_error_t st_802154_ral_pending_bit_for_short_addr_clear(const uint16_t a_short_address)
{
	(void)a_short_address;
	return 0;
}

st_802154_ral_error_t st_802154_ral_pending_bit_for_ext_addr_clear(const uint8_t* a_ext_address_ptr)
{
	(void)a_ext_address_ptr;
	return 0;
}

void st_802154_ral_pending_bit_for_short_addr_reset(void)
{

}

void st_802154_ral_pending_bit_for_ext_addr_reset(void)
{

}

void st_802154_ral_set_max_frame_retries(uint8_t a_max_retries)
{
	(void)a_max_retries;
}

void st_802154_ral_set_csma_en(uint8_t a_csma_en)
{
	(void)a_csma_en;
}

uint8_t st_802154_ral_get_csma_en(void)
{
	return 0;
}

void st_802154_ral_set_cca_en(uint8_t    a_cca_en)
{
	(void)a_cca_en;
}

uint8_t st_802154_ral_get_cca_en(void)
{
	return 0;
}

void st_802154_ral_set_max_csma_frame_retries(uint8_t a_max_retries)
{
	(void)a_max_retries;
}

void st_802154_ral_set_min_csma_be(uint8_t a_min_be)
{
	(void)a_min_be;
}

void st_802154_ral_set_max_csma_be(uint8_t a_max_be)
{
	(void)a_max_be;
}

void st_802154_ral_set_max_csma_backoff(uint8_t a_max_backoff)
{
	(void)a_max_backoff;
}

st_802154_ral_error_t st_802154_ral_get_cca_energy_detect_threshold(int8_t* a_cca_thr_ptr)
{
	(void)a_cca_thr_ptr;
	return 0;
}

st_802154_ral_error_t st_802154_ral_set_cca_energy_detect_threshold(int8_t a_cca_thr)
{
	(void)a_cca_thr;
	return 0;
}

void st_802154_ral_set_continuous_reception(bool a_enable)
{
	(void)a_enable;
}

void st_802154_ral_set_implicit_broadcast(bool a_implicit_broadcast)
{
	(void)a_implicit_broadcast;
}

st_802154_ral_error_t st_802154_ral_radio_reset(void)
{
	return 0;
}
st_802154_ral_error_t st_802154_ral_mac_gen_rnd_num(uint8_t* a_rnd_ptr,
						    uint16_t a_len,
						    uint8_t a_check_cont_rx)
{
	(void)a_rnd_ptr;
	(void)a_len;
	(void)a_check_cont_rx;
	return 0;
}

st_802154_ral_error_t st_802154_ral_set_ant_div_enable(uint8_t a_enable)
{
	(void)a_enable;
	return 0;
}

st_802154_ral_error_t st_802154_ral_set_ant_div_params(antenna_diversity_st* a_ant_div_params_ptr)
{
	(void)a_ant_div_params_ptr;
	return 0;
}

void st_802154_ral_get_ant_div_params(antenna_diversity_st*    a_ant_div_params_ptr)
{
	(void)a_ant_div_params_ptr;
}

st_802154_ral_error_t st_802154_ral_set_default_ant_id(uint8_t a_default_ant_id)
{
	(void)a_default_ant_id;
	return 0;
}

st_802154_ral_error_t st_802154_ral_set_ant_div_rssi_threshold(int8_t a_rssi_threshold)
{
	(void)a_rssi_threshold;
	return 0;
}

st_802154_ral_error_t st_802154_ral_set_config_lib_params(
						bool a_support_openthread_1_2,
						bool a_mac_layer_build,
						bool a_ack_all_received_frames_with_ar_bit_set)
{
	(void)a_support_openthread_1_2;
	(void)a_mac_layer_build;
	(void)a_ack_all_received_frames_with_ar_bit_set;
	return 0;
}

void st_802154_ral_get_config_lib_params(bool* a_support_openthread_1_2_ptr,
					 bool* a_mac_layer_build_ptr,
					 bool* a_ack_all_received_frames_with_ar_bit_set_ptr)
{
	(void)a_support_openthread_1_2_ptr;
	(void)a_mac_layer_build_ptr;
	(void)a_ack_all_received_frames_with_ar_bit_set_ptr;
}

void st_802154_ral_set_rtl_polling_time(uint8_t a_rtl_polling_time)
{
	(void)a_rtl_polling_time;
}

uint8_t st_802154_ral_get_rtl_polling_time(void)
{
	return 0;
}

void st_802154_ral_set_mac_frame_counter(uint32_t a_mac_frame_counter)
{
	(void)a_mac_frame_counter;
}

void st_802154_ral_set_mac_frame_counter_if_larger(uint32_t a_mac_frame_counter)
{
	(void)a_mac_frame_counter;
}

void st_802154_ral_set_mac_key(uint8_t a_key_id_mode,
			       uint8_t a_key_id,
			       const uint8_t* a_prev_key_ptr,
			       uint32_t a_prev_key_reference,
			       const uint8_t* a_curr_key_ptr,
			       uint32_t a_curr_key_reference,
			       const uint8_t* a_next_key_ptr,
			       uint32_t a_next_key_reference,
			       st_802154_ral_key_type_enum_t a_key_type)
{
	(void)a_key_id_mode;
	(void)a_key_id;
	(void)a_prev_key_ptr;
	(void)a_prev_key_reference;
	(void)a_curr_key_ptr;
	(void)a_curr_key_reference;
	(void)a_next_key_ptr;
	(void)a_next_key_reference;
	(void)a_key_type;
}

uint32_t st_802154_ral_platform_gen_rnd_num(uint8_t* a_rnd_ptr,
					    uint32_t a_len)
{
	(void)a_rnd_ptr;
	(void)a_len;
	return 0;
}

uint32_t st_802154_ral_platform_crypto(uint8_t* a_pckt_ptr,
				       const uint8_t* a_key_ptr,
				       uint8_t* a_nonce_ptr,
				       uint32_t a_mic_len,
				       uint32_t a_ad_len,
				       uint32_t a_md_len,
				       st_802154_ral_crypto_endian_enum_t a_key_endian,
				       st_802154_ral_crypto_endian_enum_t a_data_endian,
				       st_802154_ral_security_mode_enum_t a_security_mode)
{
	(void)a_pckt_ptr;
	(void)a_key_ptr;
	(void)a_nonce_ptr;
	(void)a_mic_len;
	(void)a_ad_len;
	(void)a_md_len;
	(void)a_key_endian;
	(void)a_data_endian;
	(void)a_security_mode;
	return 0;
}

st_802154_ral_state_t st_802154_ral_get_state(void)
{
	return 0;
}

st_802154_ral_error_t st_802154_ral_enable(void)
{
	return 0;
}

st_802154_ral_error_t st_802154_ral_disable(void)
{
	return 0;
}

bool st_802154_ral_is_enabled(void)
{
	return 0;
}

uint16_t st_802154_ral_get_capabilities(void)
{
	return 0;
}

int8_t st_802154_ral_get_receive_sensitivity(void)
{
	return 0;
}

uint32_t st_802154_ral_get_bus_latency(void)
{
	return 0;
}

void st_802154_ral_set_bus_latency(uint32_t a_bus_latency)
{
	(void)a_bus_latency;
}

uint32_t st_802154_ral_get_bus_speed(void)
{
	return 0;
}


st_802154_ral_error_t st_802154_ral_receive_at(uint8_t a_channel,
					       uint32_t a_start,
					       uint32_t a_duration)
{
	(void)a_channel;
	(void)a_start;
	(void)a_duration;
	return 0;
}

st_802154_ral_error_t  st_802154_ral_enable_csl(uint32_t a_csl_period,
						const uint16_t a_short_addr,
						const uint8_t* a_ext_Addr_ptr)
{
	(void)a_csl_period;
	(void)a_short_addr;
	(void)a_ext_Addr_ptr;
	return 0;
}

st_802154_ral_error_t st_802154_ral_reset_csl(void)
{
	return 0;
}

void st_802154_ral_update_csl_sample_time(uint32_t a_csl_sample_time)
{
	(void)a_csl_sample_time;
}

uint8_t st_802154_ral_get_csl_accuracy(void)
{
	return 0;
}

uint8_t st_802154_ral_get_csl_uncertainty(void)
{
	return 0;
}

void st_802154_ral_set_clk_accuracy(uint8_t a_clk_acc)
{
	(void)a_clk_acc;
}

void st_802154_ral_set_clk_uncertainty(uint8_t a_clk_uncer)
{
	(void)a_clk_uncer;
}

st_802154_ral_error_t st_802154_ral_configure_enh_ack_probing(bool a_pdu_count,
							      bool a_lqi,
							      bool a_link_margin,
							      bool a_rssi,
							      const uint16_t a_short_address,
							      const uint8_t* a_ext_address_ptr)
{
	(void)a_pdu_count;
	(void)a_lqi;
	(void)a_link_margin;
	(void)a_rssi;
	(void)a_short_address;
	(void)a_ext_address_ptr;
	return 0;
}

void st_802154_ral_radio_link_metrics_set_noise_floor(int8_t a_noise_floor)
{
	(void)a_noise_floor;
}

st_802154_ral_error_t st_802154_ral_get_fem_lna_gain(int8_t* a_gain_ptr)
{
	(void)a_gain_ptr;
	return 0;
}

st_802154_ral_error_t st_802154_ral_set_fem_lna_gain(int8_t a_gain)
{
	(void)a_gain;
	return 0;
}

st_802154_ral_error_t st_802154_ral_set_region(uint16_t a_region_code)
{
	(void)a_region_code;
	return 0;
}

st_802154_ral_error_t st_802154_ral_get_region(uint16_t* a_region_code_ptr)
{
	(void)a_region_code_ptr;
	return 0;
}

int8_t st_802154_ral_get_rssi(void)
{
	return 0;
}

uint8_t st_802154_ral_get_lqi_value(void)
{
	return 0;
}

uint32_t st_802154_ral_get_supported_channel_mask(void)
{
	return 0;
}

uint32_t st_802154_ral_get_preferred_channel_mask(void)
{
	return 0;
}

st_802154_ral_error_t st_802154_ral_add_calibrated_power(uint8_t a_channel,
							 int16_t a_actual_power,
							 const uint8_t* a_raw_power_setting_ptr,
							 uint16_t a_raw_power_setting_length)
{
	(void)a_channel;
	(void)a_actual_power;
	(void)a_raw_power_setting_ptr;
	(void)a_raw_power_setting_length;
	return 0;
}

st_802154_ral_error_t st_802154_ral_clear_calibrated_power(void)
{
	return 0;
}

st_802154_ral_error_t st_802154_ral_set_channel_target_power(uint8_t a_channel,
							     int16_t a_target_power)
{
	(void)a_channel;
	(void)a_target_power;
	return 0;
}

st_802154_ral_error_t st_802154_ral_get_raw_power_setting(uint8_t a_channel,
							  uint8_t* a_raw_power_setting,
							  uint16_t* a_raw_power_setting_length)
{
	(void)a_channel;
	(void)a_raw_power_setting;
	(void)a_raw_power_setting_length;
	return 0;
}

st_802154_ral_error_t st_802154_ral_set_coex_enabled(bool a_enabled)
{
	(void)a_enabled;
	return 0;
}

bool st_802154_ral_is_coex_enabled(void)
{
	return 0;
}

st_802154_ral_error_t st_802154_ral_get_coex_metrics(st_802154_ral_coex_metrics* a_coex_metrics_ptr)
{
	(void)a_coex_metrics_ptr;
	return 0;
}

st_802154_ral_error_t st_802154_ral_platform_zigbee_set_phy_cont_modul_mode(uint8_t a_type,
									    uint8_t a_enable_mode,
									    uint8_t a_chnl_num,
									    int8_t a_pwr)
{
	(void)a_type;
	(void)a_enable_mode;
	(void)a_chnl_num;
	(void)a_pwr;
	return 0;
}

void st_802154_ral_set_rx_on_when_idle(bool a_enable)
{
	(void)a_enable;
}

st_802154_ral_error_t st_802154_ral_set_auto_ack_state(uint8_t a_auto_ack_state)
{
	(void)a_auto_ack_state;
	return 0;
}
void st_802154_ral_call_back_funcs_init(
	struct st_802154_ral_cbk_dispatch_tbl* a_cbk_dispatch_tbl_ptr)
{
	(void)a_cbk_dispatch_tbl_ptr;
}
#endif /* CONFIG_IEEE802154_STM32WBA */
