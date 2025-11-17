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
#include <stm32wba_802154_callbacks.h>
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

ble_stat_t ll_intf_init(const struct hci_dispatch_tbl* p_dispatch_tbl)
{
	(void)p_dispatch_tbl;
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
void stm32wba_802154_ral_init(void)
{

}

void stm32wba_802154_ral_set_channel(uint8_t channel)
{
	(void)channel;
}

uint8_t stm32wba_802154_ral_channel_get(void)
{
	return 0;
}

void stm32wba_802154_ral_tx_power_set(int8_t power)
{
	(void)power;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_tx_power_get(int8_t *aPower)
{
	(void)aPower;
	return 0;
}

uint64_t stm32wba_802154_ral_time_get(void)
{
	return 0;
}

void stm32wba_802154_ral_pan_id_set(const uint16_t pan_id)
{
	(void)pan_id;
}

void stm32wba_802154_ral_extended_address_set(const uint8_t * aExtAddress)
{
	(void)aExtAddress;
}

void stm32wba_802154_ral_short_address_set(const uint16_t short_address)
{
	(void)short_address;
}

void stm32wba_802154_ral_eui64_get(uint8_t *p_eui64)
{
	(void)p_eui64;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_sleep(void)
{
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_receive(void)
{
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_transmit(uint8_t *aData,
					uint8_t length,
					const stm32wba_802154_ral_transmit_metadata_t  *aMetadata)
{
	(void)aData;
	(void)length;
	(void)aMetadata;
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_energy_detection(uint16_t aScanDuration)
{
	(void)aScanDuration;
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_cca(void)
{
	return 0;
}

void stm32wba_802154_ral_promiscuous_set(bool enabled)
{
	(void)enabled;
}

void stm32wba_802154_ral_pan_coord_set(bool enabled)
{
	(void)enabled;
}

void stm32wba_802154_ral_auto_pending_bit_set(bool aEnable)
{
	(void)aEnable;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_pending_bit_for_short_addr_set(
	const uint16_t aShortAddress)
{
	(void)aShortAddress;
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_pending_bit_for_ext_addr_set(
	const uint8_t * aExtAddress)
{
	(void)aExtAddress;
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_pending_bit_for_short_addr_clear(
	const uint16_t aShortAddress)
{
	(void)aShortAddress;
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_pending_bit_for_ext_addr_clear(
	const uint8_t * aExtAddress)
{
	(void)aExtAddress;
	return 0;
}

void stm32wba_802154_ral_pending_bit_for_short_addr_reset(void)
{

}

void stm32wba_802154_ral_pending_bit_for_ext_addr_reset(void)
{

}

void stm32wba_802154_ral_set_max_frame_retries(uint8_t max_retries)
{
	(void)max_retries;
}

void stm32wba_802154_ral_set_csma_en(uint8_t csma_en)
{
	(void)csma_en;
}

void stm32wba_802154_ral_set_max_csma_frame_retries(uint8_t max_retries)
{
	(void)max_retries;
}

void stm32wba_802154_ral_set_min_csma_be(uint8_t min_be)
{
	(void)min_be;
}

void stm32wba_802154_ral_set_max_csma_be(uint8_t max_be)
{
	(void)max_be;
}

void stm32wba_802154_ral_set_max_csma_backoff(uint8_t max_backoff)
{
	(void)max_backoff;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_get_cca_energy_detect_threshold(int8_t *cca_thr)
{
	(void)cca_thr;
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_set_cca_energy_detect_threshold(int8_t cca_thr)
{
	(void)cca_thr;
	return 0;
}

void stm32wba_802154_ral_set_continuous_reception(bool aEnable)
{
	(void)aEnable;
}

void stm32wba_802154_ral_set_implicitbroadcast(bool ImplicitBroadcast)
{
	(void)ImplicitBroadcast;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_radio_reset(void)
{
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_mac_gen_rnd_num(uint8_t *ptr_rnd,
								uint16_t len,
								uint8_t check_cont_rx)
{
	(void)ptr_rnd;
	(void)len;
	(void)check_cont_rx;
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_set_ant_div_enable(uint8_t enable)
{
	(void)enable;
	return 0;
}

stm32wba_802154_ral_error_t stm32wba_802154_ral_set_config_lib_params(bool support_openthread_1_2,
								      bool mac_layer_build)
{
	(void)support_openthread_1_2;
	(void)mac_layer_build;
	return 0;
}

void stm32wba_802154_ral_set_mac_frame_counter(uint32_t aMacFrameCounter)
{
	(void)aMacFrameCounter;
}

void stm32wba_802154_ral_set_mac_frame_counter_if_larger(uint32_t aMacFrameCounter)
{
	(void)aMacFrameCounter;
}

void stm32wba_802154_ral_set_mac_key(uint8_t aKeyIdMode,
				     uint8_t aKeyId,
				     const uint8_t *aPrevKey,
				     const uint8_t *aCurrKey,
				     const uint8_t *aNextKey)
{
	(void)aKeyIdMode;
	(void)aKeyId;
	(void)aPrevKey;
	(void)aCurrKey;
	(void)aNextKey;
}
void stm32wba_802154_ral_call_back_funcs_init(
	struct stm32wba_802154_ral_cbk_dispatch_tbl * ptr_cbk_dispatch_tbl)
{
	(void)ptr_cbk_dispatch_tbl;
}
#endif /* CONFIG_IEEE802154_STM32WBA */
