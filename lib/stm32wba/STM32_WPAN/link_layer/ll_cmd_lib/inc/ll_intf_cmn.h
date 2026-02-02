/*$Id: //dwh/bluetooth/DWC_ble154combo/firmware/rel/2.00a-lca04/firmware/public_inc/ll_intf_cmn.h#1 $*/
/**
 ********************************************************************************
 * @file    ll_intf_cmn.h
 * @brief   This file includes declaration of common interfaces of MAC only and BLE/COEXISTENCE APIs.
 ******************************************************************************
 * @copy
 * Synopsys MIT License:
 * Copyright (c) 2020-Present Synopsys, Inc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of the software and
 * associated documentation files (the “Software”), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING, BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE
 * ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * */
#ifndef INCLUDE_LL_INTF_CMN_H_
#define INCLUDE_LL_INTF_CMN_H_
#include "common_types.h"
/*========================================================================================================*/
/*================================  Configure LL Context Control Command =================================*/
/*========================================================================================================*/
/** @ingroup  ll_common_interface_functions
 *  @{
 */
/**
 * @brief Configure the LL contexts, where:
 * 			  1. For bare-metal:
 * 			    - High ISR is executed in the ISR context
 * 			    - Low ISR can be executed in the high ISR context, or switched to low ISR context
 * 			  2. For RTOS:
 * 			    - High ISR is executed in the ISR context
 * 			    - Low ISR is executed in the thread of the "linkLayerHighPrioTask"
 *
 * @param[in] allow_low_isr         : Configuration parameter for the context of the low ISR in the bare-metal model. Range is [0,1].
 * 								                    0: Low ISR code is executed in the same context of the high ISR.
 * 								                    1: Low ISR code is executed in the context of the low ISR (by configuring a low priority interrupt that is triggered by FW).
 * @param[in] run_post_evnt_frm_isr : Configuration parameter to decide whether the scheduling of the next BLE event is done in the low ISR context or to be handled by the LL main thread. Range is [0,1].
 * 								                    0: BLE next event scheduling is handled in the LL main thread.
 * 								                    1: BLE next event scheduling is handled in the low ISR context.
 * @return Command status
 */
ble_stat_t ll_intf_cmn_config_ll_ctx_params(uint8_t allow_low_isr, uint8_t run_post_evnt_frm_isr);
/*========================================================================================================*/
/*==================================  LE Select Sleep Clock Source =======================================*/
/*========================================================================================================*/
#if (USE_NON_ACCURATE_32K_SLEEP_CLK)
/**
 * @brief Select the source that drives the sleep clock, whether to use an external crystal oscillator or an integrated RC oscillator (RCO).
 *
 * @param[in] slp_clk_src 				    : Indicate which source to drive the sleep clock. 0: Crystal Oscillator (default). 1: RC0
 * @param[out] ptr_slp_clk_freq_value : Indicate the nominal frequency value of the sleep clock.
 * @return Command status to be sent to the Host.
 */
ble_stat_t ll_intf_cmn_le_select_slp_clk_src(uint8_t slp_clk_src, uint16_t *ptr_slp_clk_freq_value);
/*========================================================================================================*/
/*===============================  LE Set RCO Calibration Event Parameters ===============================*/
/*========================================================================================================*/
/**
 * @brief Configure the runtime RCO calibration event parameters.
 *
 * @param[in] rco_clbr_event_duration : Indicate the number of sleep clock cycles for performing the RCO calibration process.
 * @param[in] rco_clbr_event_interval : Indicate the periodicity of running the runtime RCO calibration event.
 * @return Command status to be sent to the Host.
 */
ble_stat_t ll_intf_cmn_le_set_rco_clbr_evnt_params(uint8_t rco_clbr_event_duration, uint32_t rco_clbr_event_interval);
#endif
/*========================================================================================================*/
/*======================================  LE Select TX_Power Table =======================================*/
/*========================================================================================================*/
/**
 * @brief Specify the used power table and its size based on the selected TX_Power table ID.
 *
 * @param[in] tx_power_table_id : Selected TX_Power table ID.
 * @return Status 		 : 0: SUCCESS. Otherwise: Error code.
 */
uint8_t ll_intf_cmn_select_tx_power_table(uint8_t tx_power_table_id);
/**
 * @brief flag to the LL the existence of a temperature sensor
 *
 */
void ll_intf_cmn_set_temperature_sensor_state(void);
/**
 * @brief Set the current temperature
 *
 * @param[in] temperature :	The current temperature
 * @return Command status
 */
ble_stat_t  ll_intf_cmn_set_temperature_value(uint32_t temperature);
/*========================================================================================================*/
/*====================================  Random Number Generation Group ===================================*/
/*========================================================================================================*/
 /**
  * @brief  Request new random number.
  *
  * @param[out] ptr_rnd	: Pointer to the output random bytes .
  * @param[in] len	 	  : Number of required random bytes.
  *
  * @return Status.
  */
uint32_t ll_intf_cmn_gen_rnd_num(uint8_t *ptr_rnd, uint32_t len);
/**
 * @brief A common wrapper for BLE-ECB and MAC-CCM security modes
 *
 * @param[in]	ptr_pckt		  : Pointer to the data buffer (variable length in case of CCM mode, 16 bytes in case of ECB mode).
 *                            The resulting Encrypted/Decrypted data overwrites this buffer.
 * @param[in]	ptr_key		    : Pointer to the security key buffer (16 bytes).
 * @param[in]	ptr_nonce	    : Pointer to the security nonce buffer (13 bytes in case of CCM mode, a Null pointer in case of ECB mode).
 * @param[in]	mic_len		    : Length of MIC, supported values are 0, 4, 6, 8, 10, 12, 14, and 16 in case of CCM, 0 only in case of ECB.
 * @param[in]	ad_len		    : Length of Data to be authenticated.
 * @param[in]	md_len		    : Length of Data to be encrypted.
 * @param[in]	key_endian	  : Represents the format of the security key.
 * @param[in]	data_endian	  : Represents the endian format of the data.
 * @param[in]	security_mode : Hardware security mode.
 * @return Status
 */
uint32_t ll_intf_cmn_crypto(uint8_t *ptr_pckt, const uint8_t *ptr_key,
		uint8_t *ptr_nonce, uint32_t mic_len, uint32_t ad_len, uint32_t md_len,
		crypto_endian_enum_t key_endian, crypto_endian_enum_t data_endian,
		security_mode_enum_t security_mode);
/*===============  LL Common Interface LE Set Deep Sleep Mode  ===============*/
/**
 * @brief Switches the controller to and from Deep Sleep mode.
 *
 * @param[in]  dp_slp_mode  : Input according to dpslp_state_e.
 *                            DEEP_SLEEP_ENABLE  -> Activate Deep Sleep.
 *                            DEEP_SLEEP_DISABLE -> Deactivate Deep Sleep.
 * @return Status.
 */
ble_stat_t ll_intf_cmn_le_set_dp_slp_mode(uint8_t dp_slp_mode);
#if SUPPORT_CONFIGURABLE_GAIN_FIX
/**
 * @brief  Initialize RSSI gain fix region and select resistor measured
 *			   percentage that affects pre-emphasis sequence.
 *
 * @param[in] region_0x1f_val : Absolute gain fix for region 0x1F in dbm.
 * @param[in] region_0x0f_val : Absolute gain fix for region 0x0F in dbm.
 * @param[in] region_0x0b_val : Absolute gain fix for region 0x0B in dbm.
 * @param[in] region_0x09_val : Absolute gain fix for region 0x09 in dbm.
 * @param[in] r_msur_percent  : Percentage of the measured resistor value that will be used
 * 				                      to select the update values in pre-emphasis sequence (range: 0 to 99).
 */
void ll_intf_cmn_gain_fix_init(
		uint8_t region_0x1f_val, uint8_t region_0x0f_val,
		uint8_t region_0x0b_val, uint8_t region_0x09_val,
		uint8_t r_msur_percent);
#endif /* SUPPORT_CONFIGURABLE_GAIN_FIX */
/*===============  Set PHY Calibration Period  =================*/
/**
 * @brief  Set PHY calibration period.
 *
 * @param[in] phy_clbr_evnt_period  : Indicate the periodicity of the PHY calibration event. Periodicity = phy_clbr_evnt_period * 1s.
 * @param[in] phy_clbr_evnt_count 	: Indicate the number of the PHY calibration events to be executed.
 */
void ll_intf_cmn_set_phy_clbr_period(uint32_t phy_clbr_evnt_period, uint32_t phy_clbr_evnt_count);
/** @}
*/

#endif /* INCLUDE_LL_INTF_CMN_H_ */
