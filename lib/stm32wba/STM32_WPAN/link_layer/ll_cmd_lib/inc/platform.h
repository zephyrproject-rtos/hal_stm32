/*$Id: //dwh/bluetooth/DWC_ble154combo/firmware/rel/2.00a-lca04/firmware/public_inc/platform.h#1 $*/
/**
 ********************************************************************************
 * @file    platform.h
 * @brief   this file include all helper functions in radio.c which is not described in Openthread
 *
 *
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


#ifndef INCLUDE_PLATFORM_H_
#define INCLUDE_PLATFORM_H_

#include "radio.h"
#include "common_types.h"

/*====================================   MACROS   =======================================*/
/*
 * The following macros are used for testing purpose only
 */
#define ACK_FRAME_TYPE  0x2				///< ACK frame type
#define MAC_ACK_WAIT	864				///< The time in microseconds of waiting for ACK
/******************************************************************************************//**
 *  								 Enums
 *********************************************************************************************/
/**
 * @brief Enum defines the states of the radio event that used in coexistence
 *
 */
typedef enum _radio_evnt_type_enum
{
	TX_PCKT_STATE,      ///< Sending packet (not ACK)
	TX_ACK_STATE,       ///< Sending ACK
	RX_PCKT_STATE,		///< Receiving packet (not ACK)
	RX_ACK_STATE,		///< Receiving Ack
	RADIO_ED,			///< Energy detection
	RADIO_SLEEP_STATE,	///< Sleep state
	RADIO_DISABLED_STATE,///< Disable state
#if(SUPPORT_COEXISTENCE)
	TX_AT_STATE  ,       ///< Tx at specific time
	RX_AT_STATE  ,      ///< Rx at specific time
#endif /* SUPPORT_COEXISTENCE */
}radio_event_enum_t;
/******************************************************************************************//**
 *  								 Structures
 *********************************************************************************************/
/**  @ingroup systm_layer
*  @{
*/
/**
 * @brief Structure defines all callback functions used to notify MAC layer after specific event compeletion
 *
 */
struct mac_cbk_dispatch_tbl{
	/**
	 * @brief  Energy detection scan done callback
	 *
	 * @param[in] aInstance			: Radio instance
	 * @param[in] aEnergyScanMaxRssi: The result for ED operation which is RSSI value
	 *
	 * @note  This function is called after handling SM_DONE event in ral through a sequence of calls
	 * 		  ral_sm_done() -> ral_ed_scan_done() -> callback
	 */
	void (*mac_ed_scan_done)(otInstance *aInstance, int8_t aEnergyScanMaxRssi);
	/**
	 * @brief  Transmission done callback
	 *
	 * @param[in] aInstance	: Radio instance
	 * @param[in] aFrame	: Pointer to the transmitted frame
	 * @param[in] aAckFrame	: Pointer to the received ACK frame (in case of AR bit is detected in aFrame)
	 * @param[in] aError	: Error code if happens in transmission
	 *
	 * @note  This function is called after handling SM_DONE event in ral through a sequence of calls
	 * 		  ral_sm_done() -> ral_tx_done() -> callback
	 */
	void (*mac_tx_done)(otInstance *aInstance, otRadioFrame *aFrame, otRadioFrame *aAckFrame, otError aError);
	/**
	 * @brief  Reception done callback
	 *
	 * @param[in] aInstance	: Radio instance
	 * @param[in] aFrame	: Pointer to the received frame
	 * @param[in] aError	: Error code if happens in transmission
	 *
	 * @note  This function is called after handling SM_DONE event in ral through a sequence of calls
	 * 		  ral_sm_done() -> ral_rx_done() -> callback
	 */
	void (*mac_rx_done)(otInstance *aInstance, otRadioFrame *aFrame, otError aError);
	/**
	 * @brief  The start of successfull transmission callback
	 *
	 * @param[in] aInstance	: Radio instance
	 * @param[in] aFrame	: Pointer to the transmitted frame
	 * @param[in] aError	: Error code if happens in transmission
	 *
	 * @note  This function is called after calling proc_radio_tx which is called with calling of otplatRadioTransmit
	 *        in case of no error returned. These errors may be (CCA channel access failure, ral busy due to ongoing transmission ...etc )
	 */
	void (*mac_tx_strtd)(otInstance *aInstance, otRadioFrame *aFrame);
	/**
	 * @brief The frame update callback
	 *
	 * @param[in] aInstance	: Radio instance
	 * @param[in] aFrame	: Pointer to the frame
	 */
	void (*mac_frm_updtd)(otInstance *aInstance, otRadioFrame *aFrame);

};
/**
 * @}
 *
 */
/******************************************************************************************//**
 *  								 APIs
 *********************************************************************************************/
/**  @ingroup systm_layer_cmn_proc
*  @{
*/
/**
 * @brief  Initialize radio layer including registeration for RAL callbacks, some filter configurations,
 * 		   and some automatic configurations like auto_sleep and auto_ack...etc
 *
 */
void radio_init(void);
/**
 * @brief  Register upper layer callback functions.
 * 		   This function called from upper layer init function (mac_init in case of MAC integration e.g. Zigbee stack).
 *
 * @param[in] ptr_cbk_dispatch_tbl : Pointer to callback functions to be registered
 */
void radio_call_back_funcs_init(struct mac_cbk_dispatch_tbl * ptr_cbk_dispatch_tbl);
/**
 * @}
 *
 */
/**
 * @brief Initialize openthread dispatch table
 *
 * @param sInstance	: Radio instance
 */
void otDispatch_tbl_init(otInstance *sInstance);

/**  @ingroup systm_layer_enc
*  @{
*/
/**
 * @brief  Encrypt frame pointed to by ptr_pckt
 *
 * @param[in] ptr_pckt 			: Pointer to the data buffer (variable length in case of CCM mode, 16 bytes in case of ECB mode).
 * 								  The resulting Encrypted/Decrypted data overwrites this buffer.
 * @param[in] ptr_session_key 	: Pointer to the security key buffer (16 bytes)
 * @param[in] ptr_ccm_nonce 	: Pointer to the security nonce buffer (13 bytes in case of CCM mode, a Null pointer in case of ECB mode).
 * @param[in] mic_len 			: Length of MIC, supported values are 0, 4, 6, 8, 10, 12, 14, and 16 in case of CCM, 0 only in case of ECB.
 * @param[in] ad_len 			: Length of Data to be authenticated
 * @param[in] md_len 			: Length of Data to be encrypted
 * @retval Status of the encryption process
 */
uint32_t radio_encrypt_pckts( uint8_t *ptr_pckt,
		 const  uint8_t  *ptr_session_key,
		 uint8_t  *ptr_ccm_nonce,
		 uint32_t  mic_len,
		 uint32_t  ad_len,
		 uint32_t  md_len);
/**
 * @}
 *
 */
/**  @ingroup systm_layer_cmn_config
*  @{
*/
/**
 * @brief  Configure automatic ACK response by RAL layer including AIFS, ACK frame timeout.. etc
 *
 * @param[in] auto_ack_state : Auto ACK state (TRUE to enable, FALSE to disable)
 * @retval Status of configuration
 */
otError radio_set_auto_Ack_state(uint8_t auto_ack_state);
/**
 * @}
 *
 */
/**  @ingroup systm_layer_cmn_proc
*  @{
*/
/**
 * @brief Reset radio layer operation which in turns stop all running operations
 *
 * @return Status
 */
uint32_t radio_reset(void);
/**
 * @}
 *
 */
/**
 * @brief Control RAL setup for reception
 *
 * @param[in] aChannel : Channel to receive on
 * @param[in] duration : Reception duration in microsecond, 0 means receive forever
 * @return Status
 */
otError proc_radio_rcv(uint8_t aChannel ,uint32_t duration);
/**
 * @brief Control RAL setup for transmission based on CCA procedure.
 *
 * @param[in] aFrame 	: Pointer to the transmitted frame
 * @param[in] strt_time : Pointer to TX request time
 * @return Status
 */
otError proc_radio_tx(otRadioFrame *aFrame , ble_time_t* strt_time);
/**
 * @brief Control RAL setup for energy detection scan
 *
 * @param[in] aScanChannel 	: Channel to perform ED on
 * @param[in] aScanDuration : Scan duration
 * @return Status
 */
otError proc_radio_ed(uint8_t aScanChannel, uint16_t aScanDuration);
/**  @ingroup systm_layer_cmn_config
*  @{
*/
/**
 * @brief Set PAN coordinator role in HW to be used while applying MAC 802.15.4 filtration policies
 *
 * @param[in] aEnable : PAN coordinator role flag (TRUE to enable, FALSE to disable)
 */
void setPANcoordinator(uint8_t aEnable);
/**
 * @brief Notify RAL layer of RX on when idle state
 *
 * @param[in] aEnable : Continuous reception state (TRUE to enable, FALSE to disable)
 */
void setContRecp(uint8_t aEnable);
/**
 * @brief Disable filtration policies while performing scan
 *
 * @param[in] aInstance : Radio instance
 */
void enableScanFilters(otInstance *aInstance);
/**
 * @brief Restore filtration policies after the scan is completed
 *
 * @param[in] aInstance : Radio instance
 */
void disableScanFilters(otInstance *aInstance);

/**
 * @}
 *
 */
/**  @ingroup systm_layer_cmn_proc
*  @{
*/
/**
 * @brief  Get the latest LQI value
 *
 * @retval LQI value
 */
uint8_t radio_GetLQIValue(void);
/**
 * @}
 *
 */
#if RADIO_CSMA
/**  @ingroup systm_layer_cmn_config
*  @{
*/
/**
 * @brief Set minimum CSMA backoff exponent
 *
 * @param[in] value : Minimum csma backoff exponent
 */
void set_min_csma_be(uint8_t value);
/**
 * @brief Set maximum CSMA backoff exponent
 *
 * @param[in] value : Maximum CSMA backoff exponent
 */
void set_max_csma_be(uint8_t value);
/**
 * @brief Set maximum CSMA backoff counter
 *
 * @param[in] value : Maximum CSMA backoff counter
 */
void set_max_csma_backoff(uint8_t value);
/**
 * @brief Set custom maximum full CSMA frame retries
 *
 * @param[in] value : Maximum full CSMA retrials
 */
void set_max_full_csma_frm_retries(uint8_t value);
#endif /*end of RADIO_CSMA*/
/**
 * @brief Set maximum frame retries
 *
 * @param[in] value : Maximum frame retries
 */
void set_max_frm_retries(uint8_t value);
/**
 * @}
 *
 */
/**  @ingroup systm_layer_cmn_proc
*  @{
*/
/**
 * @brief Generate random number
 *
 * @param[out] ptr_rnd		: Pointer to the output random bytes
 * @param[in] len	 		: Number of required random bytes
 * @param[in] check_cont_rx : Flag to check continuous reception
 * @return Status
 */
uint32_t mac_gen_rnd_num(uint8_t *ptr_rnd, uint16_t len, uint8_t check_cont_rx);
/**
 * @}
 *
 */
/**  @ingroup systm_layer_enc
*  @{
*/
/**
 * @brief  Decrypt frame pointed to by ptr_pckt
 *
 * @param[in] ptr_pckt 			: Pointer to the data buffer (variable length in case of CCM mode, 16 bytes in case of ECB mode).
 * 								  The resulting Encrypted/Decrypted data overwrites this buffer.
 * @param[in] ptr_session_key 	: Pointer to the security key buffer (16 bytes)
 * @param[in] ptr_ccm_nonce 	: Pointer to the security nonce buffer (13 bytes in case of CCM mode, a Null pointer in case of ECB mode).
 * @param[in] mic_len 			: Length of MIC, supported values are 0, 4, 6, 8, 10, 12, 14, and 16 in case of CCM, 0 only in case of ECB.
 * @param[in] ad_len 			: Length of Data to be authenticated
 * @param[in] md_len 			: Length of Data to be decrypted
 * @retval Status of the decryption process
 */
uint32_t radio_decrypt_pckts( uint8_t *ptr_pckt,
		 uint8_t  *ptr_session_key,
		 uint8_t  *ptr_ccm_nonce,
		 uint32_t  mic_len,
		 uint32_t  ad_len,
		 uint32_t  md_len);
/**
 * @}
 *
 */
/**
 * @brief Call MAC radio rx done callback after the end of reception.
 *
 * @param[in] aFrame : Pointer to the received frame
 * @param[in] aError : Reception error
 */
void radio_mac_rx_done(otRadioFrame *aFrame, otError aError);

#if (SUPPORT_ENH_ACK_LINK_METRICS_PROBING_OT_1_2)
/**
 * @brief Set the link metrics noise floor value needed to calculate the link margin
 *
 * @param[in] noise_floor : The noise floor used by Link Metrics.
 * 							It should be set to the platform's noise floor (measured noise floor, receiver sensitivity or a constant).
 */
void radio_link_metrics_set_noise_floor(int8_t noise_floor);
#endif
#if(SUPPORT_OPENTHREAD_1_2 && CONFIG_MAC_CSL_TRANSMITTER_ENABLE)
/**
 * @brief Call MAC radio TX done
 *
 * @param[in] tx_frame	: Pointer to the transmitted frame
 * @param[in] aError	: TX error
 */
void radio_mac_tx_done_error(otRadioFrame * tx_frame,otError aError);
#endif /*(SUPPORT_OPENTHREAD_1_2 && CONFIG_MAC_CSL_TRANSMITTER_ENABLE)*/
#if !SUPPORT_COEXISTENCE
/*##### Random Number Generation Group #####*/
/** @ingroup rnd_gen_functions
 *  @{
 */
 /**
  * @brief  Request new random number.
  *
  * @param[out] ptr_rnd	: Pointer to the output random bytes .
  * @param[in] len	 	: Number of required random bytes.
  *
  * @retval Status.
  */
 uint32_t platform_gen_rnd_num(
 	uint8_t *ptr_rnd,
 	uint32_t len);
/**  @}
*/
/**
 * @brief A common wrapper for BLE-ECB and MAC-CCM security modes
 *
 * @param[in] ptr_pckt		: Pointer to the data buffer (variable length in case of CCM mode, 16 bytes in case of ECB mode).
 * 							  The resulting Encrypted/Decrypted data overwrites this buffer.
 * @param[in] ptr_key		: Pointer to the security key buffer (16 bytes).
 * @param[in] ptr_nonce		: Pointer to the security nonce buffer (13 bytes in case of CCM mode, a Null pointer in case of ECB mode).
 * @param[in] mic_len		: Length of MIC, supported values are 0, 4, 6, 8, 10, 12, 14, and 16 in case of CCM, 0 only in case of ECB.
 * @param[in] ad_len		: Length of Data to be authenticated.
 * @param[in] md_len		: Length of Data to be encrypted.
 * @param[in] key_endian	: Represents the format of the security key.
 * @param[in] data_endian	: Represents the endian format of the data.
 * @param[in] security_mode	: Hardware security mode.
 * @retval Status
 */
uint32_t platform_crypto(uint8_t *ptr_pckt, const uint8_t *ptr_key,
		uint8_t *ptr_nonce, uint32_t mic_len, uint32_t ad_len, uint32_t md_len,
		crypto_endian_enum_t key_endian, crypto_endian_enum_t data_endian,
		security_mode_enum_t security_mode);

/**
 * @brief Run periodic calibration if tempature has changed
 *
 */
void radio_run_phy_clbr_on_temp_change(void);
#endif /*!SUPPORT_COEXISTENCE*/

#if (!SUPPORT_COEXISTENCE)
/**
 * @brief   Set link layer deep sleep mode
 *
 * @param[in] dp_slp_mode : Deep sleep mode (enable or disable)
 * @retval Status .
 */
otError radio_set_dp_slp_mode(dpslp_state_e dp_slp_mode);
#endif /*end of (!SUPPORT_COEXISTENCE)*/
#if SUPPORT_MAC_CONT_TESTING_CMDS_PHY_SUPPORT
/**
 * @brief Set the PHY continuous modulation and continuous wave modes upon enable
 *
 * @param[in] type			: The type of the modulation (0: modulation, 1: wave)
 * @param[in] enable_mode	: TRUE to enable the selected mode, FALSE to disable it
 * @param[in] chnl_num		: Channel number to be used in modulation (range: 0 to 15)
 * @param[in] pwr         	: The used power in dBm.
 * @retval Status
 */
otError platform_zigbee_set_phy_cont_modul_mode(uint8_t type, uint8_t enable_mode, uint8_t chnl_num, int8_t pwr);
#endif /*end of SUPPORT_MAC_CONT_TESTING_CMDS_PHY_SUPPORT */
#if SUPPORT_ANT_DIV
/**
 * @brief Set antenna diversity feature parameters
 *
 * @param[in] aInstance     	: Radio instance
 * @param[in] ptr_ant_div_params: Pointer to antenna diversity feature parameters
 * @retval Status
 */
otError radio_set_ant_div_params(otInstance *aInstance, antenna_diversity_st* ptr_ant_div_params);
/**
 * @brief Get antenna diversity feature parameters
 *
 * @param[in] aInstance 			: Radio instance
 * @param[out] ptr_ant_div_params	: Pointer to antenna diversity feature parameters
 */
void radio_get_ant_div_params(otInstance *aInstance, antenna_diversity_st* ptr_ant_div_params);
/**
 * @brief Set antenna diversity feature state
 *
 * @param[in] aInstance	: Radio instance
 * @param[in] enable	: Antenna diversity feature state (TRUE to enable, FALSE to disable)
 * @retval Status
 */
otError radio_set_ant_div_enable(otInstance *aInstance, uint8_t enable);
/**
 * @brief Set the default antenna ID of the antenna diversity feature to be used for transmission and reception
 *
 * @param[in] aInstance	    	: Radio instance
 * @param[in] default_ant_id	: Default antenna ID
 * @retval Status
 */
otError radio_set_default_ant_id(otInstance *aInstance, uint8_t default_ant_id);
/**
 * @brief Set the RSSI threshold for antenna diversity feature
 *
 * @param[in] aInstance	    : Radio instance
 * @param[in] rssi_threshold: RSSI threshold to compare with during antenna diversity measurements
 * @retval Status
 */
otError radio_set_ant_div_rssi_threshold(otInstance *aInstance, int8_t rssi_threshold);
#endif /* SUPPORT_ANT_DIV */
/**
 * @brief Set bus latency between thread core and radio platform
 *
 * @param[in] aInstance	    : Radio instance
 * @param[in] bus_latency	: Time in microseconds for latency between thread core and radio platform
 */
void otPlatRadioSetBusLatency(otInstance *aInstance, uint32_t bus_latency);
#if SUPPORT_OPENTHREAD_1_2
/**
 * @brief   Set clock accuracy
 *
 * @param[in] clk_acc: Clock accuracy in PPM
 */
void radio_set_clk_accuracy(uint8_t clk_acc);
/**
 * @brief   Set clock uncertainty
 *
 * @param[in] clk_uncer: Clock uncertainty in units of 10 us.
 */
void radio_set_clk_uncertainty(uint8_t clk_uncer);
#endif /*SUPPORT_OPENTHREAD_1_2*/

#if SUPPORT_CONFIGURABLE_GAIN_FIX
/**
 * @brief  Initialize RSSI gain fix region and select resistor measured percentage that affects pre-emphasis sequence.
 *
 * @param[in] region_0x1f_val: Absolute gain fix for region 0x1F in dbm.
 * @param[in] region_0x0f_val: Absolute gain fix for region 0x0F in dbm.
 * @param[in] region_0x0b_val: Absolute gain fix for region 0x0B in dbm.
 * @param[in] region_0x09_val: Absolute gain fix for region 0x09 in dbm.
 * @param[in] r_msur_percent : Percentage of the measured resistor value that will be used
 * 							   to select the update values in pre-emphasis sequence (range: 0 to 99).
 */
void radio_gain_fix_init(
		uint8_t region_0x1f_val, uint8_t region_0x0f_val,
		uint8_t region_0x0b_val, uint8_t region_0x09_val,
		uint8_t r_msur_percent);

#endif /* SUPPORT_CONFIGURABLE_GAIN_FIX */
#if SUPPORT_CONFIG_LIB
/**
 * @brief Set configurable library feature parameters
 *
 * @param[in] aInstance 			: Radio instance
 * @param[in] ptr_config_lib_params : pointer to configurable library feature parameters
 * @retval Status
 */
otError radio_set_config_lib_params(otInstance *aInstance, config_lib_st* ptr_config_lib_params);
/**
 * @brief Get current configurable library parameters
 *
 * @param[in] aInstance	            : Radio instance
 * @param[out] ptr_config_lib_params: Pointer to configurable library feature parameters
 */
void radio_get_config_lib_params(otInstance *aInstance, config_lib_st* ptr_config_lib_params);
/**
 * @brief Set RTL polling time
 *
 * @param[in] aInstance       : Radio instance
 * @param[in] rtl_polling_time: RTL polling time value
 */
void radio_set_rtl_polling_time(otInstance *aInstance, uint8_t rtl_polling_time);
/**
 * @brief Get current RTL polling time
 *
 * @param[in] aInstance : Radio instance
 * @retval Current RTL polling time
 */
uint8_t radio_get_rtl_polling_time(otInstance *aInstance);
#endif /* SUPPORT_CONFIG_LIB */
#if !SUPPORT_COEXISTENCE && DEFAULT_PHY_CALIBRATION_PERIOD
/**
 * @brief Set PHY calibration period
 *
 * @param[in] phy_clbr_evnt_period : PHY calibration period
 */
void radio_set_phy_clbr_period(uint32_t phy_clbr_evnt_period);
#endif /* !SUPPORT_COEXISTENCE && DEFAULT_PHY_CALIBRATION_PERIOD */
#if SUPPORT_COEXISTENCE && RADIO_CSMA
/**
 * @brief  Get minimum block counter of TX packet to increase priority to critical.
 *
 * @retval Minimum block number of TX packets to be critical
 */
uint8_t radio_get_min_blck_cnt_to_be_critical(void);
#endif /* SUPPORT_COEXISTENCE && RADIO_CSMA */

#endif /* INCLUDE_PLATFORM_H_ */
