/*
 * Copyright (c) 2025 STMicroelectronics
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of STMicroelectronics nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * @defgroup ST 802.15.4 radio driver
 * @{
 *
 */

#ifndef ST_802154_RAL_H_
#define ST_802154_RAL_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief st_802154_ral_error_t - Radio Abstraction Layer error/status codes
 *
 * Enumerates the return codes used by the ST Radio Abstraction Layer (ST RAL)
 * to indicate the result of API calls. Values represent success, specific
 * failure conditions and transient states (for example: timeout, busy,
 * invalid parameter). Callers should inspect returned st_802154_ral_error_t values
 * to determine appropriate recovery or error handling actions.
 */
typedef enum st_802154_ral_error_t
{
    ST_802154_RAL_ERROR_NONE                         = 0,   // !< No error.
    ST_802154_RAL_ERROR_FAILED                       = -1,  // !< Operation failed.
    ST_802154_RAL_ERROR_DROP                         = -2,  // !< Message was dropped.
    ST_802154_RAL_ERROR_NO_BUFS                      = -3,  // !< Insufficient buffers.
    ST_802154_RAL_ERROR_BUSY                         = -4,  // !< Service is busy and could not service the operation.
    ST_802154_RAL_ERROR_INVALID_ARGS                 = -5,  // !< Input arguments are invalid.
    ST_802154_RAL_ERROR_SECURITY                     = -6,  // !< Security checks failed.
	ST_802154_RAL_ERROR_NO_ADDRESS                   = -7,  // !< Address is not in the source match table.
	ST_802154_RAL_ERROR_ABORT                        = -8,  // !< Operation was aborted.
	ST_802154_RAL_ERROR_NOT_IMPLEMENTED              = -9,  // !< Function or method is not implemented.
	ST_802154_RAL_ERROR_INVALID_STATE                = -10, // !< Cannot complete due to invalid state.
	ST_802154_RAL_ERROR_NO_ACK                       = -11, // !< No acknowledgment was received after macMaxFrameRetries (IEEE 802.15.4-2006).
	ST_802154_RAL_ERROR_CHANNEL_ACCESS_FAILURE       = -12, // !< A transmission could not take place due to activity on the channel, i.e., the CSMA-CA mechanism has failed (IEEE 802.15.4-2006).
	ST_802154_RAL_ERROR_FCS                          = -13, // !< FCS check failure while receiving.
	ST_802154_RAL_ERROR_NO_FRAME_RECEIVED            = -14, // !< No frame received.
	ST_802154_RAL_ERROR_INVALID_SOURCE_ADDRESS       = -15, // !< Received a frame from an invalid source address.
	ST_802154_RAL_ERROR_DESTINATION_ADDRESS_FILTERED = -16, // !< Received a frame filtered by the destination address check.
	ST_802154_RAL_ERROR_NOT_FOUND                    = -17, // !< The requested item could not be found.
	ST_802154_RAL_ERROR_GENERIC                      = -18, // !< Generic error.
	ST_802154_RAL_ERROR_UNKNOWN                      = -255 // !< Unknown error.
} st_802154_ral_error_t;

#define ST_802154_RAL_MAC_KEY_SIZE 16 ///< Size of the MAC Key in bytes.


/**
 * Represents a MAC Key.
 */
typedef struct st_802154_ral_mac_key
{
    uint8_t    m8[ST_802154_RAL_MAC_KEY_SIZE]; // !<  MAC Key bytes.
}st_802154_ral_mac_key;

typedef uint32_t    st_802154_ral_mac_key_ref;

/**
 * @struct st_802154_ral_mac_key_material
 *
 * Represents a MAC Key.
 */
typedef struct st_802154_ral_mac_key_material
{
    union
    {
        st_802154_ral_mac_key_ref    a_key_ref; // !< Reference to the key stored.
        st_802154_ral_mac_key   	 a_key;     // !< Key stored as literal.
    } key_material;
}st_802154_ral_mac_key_material;


/**
 * This structure represents the IEEE 802.15.4 Header IE (Information Element) related information of a radio frame.
 */
typedef struct st_802154_ral_ie_info
{
    int64_t    a_network_time_offset; // !< The time offset to the Thread network time.
    uint8_t    a_time_ie_offset;      // !< The Time IE offset from the start of PSDU.
    uint8_t    a_time_sync_seq;       // !< The Time sync sequence.
} st_802154_ral_ie_info;


/**
 * @brief Structure metadata for transmission request.
 */
typedef struct
{
    bool                                     is_secured;               // !< If the frame to be transmitted is already secured (in the sense of IEEE 802.15.4 security operations).
    bool                                     dynamic_data_is_set;      // !< If dynamic data of the frame to be transmitted is set.
    bool                                     cca;                      // !< If the driver is to perform a CCA procedure before transmission.
    int8_t                                   tx_power;                 // !< Transmission power in dBm
    uint8_t                                  tx_channel;               // !< Transmission channel
	const st_802154_ral_mac_key_material*    aes_key_ptr;              // !< The key material used for AES-CCM frame security.
	st_802154_ral_ie_info*                   ie_info_ptr;              // !< The pointer to the Header IE(s) related information.
	uint32_t                                 tx_delay_base_time;       // !< The base time in microseconds for scheduled transmissions relative to the local radio clock.
	uint32_t                                 tx_delay;                 // !< The delay time in microseconds for this transmission referenced to `tx_delay_base_time`.
	uint8_t                                  max_csma_backoffs;        // !< Maximum number of CSMA backoff attempts before declaring channel access failure.
	uint8_t                                  max_frame_retries;        // !< Maximum number of retries allowed after a transmission failure.
	uint8_t                                  rx_channel_after_tx_done; // !< The RX channel after frame TX is done (after all frame retries - ack received, or timeout, or abort).
	bool                                     is_retx;                  // !< Indicates whether the frame is a retransmission or not.
	bool                                     csl_present;              // !< Set to true if CSL header IE is present.
	uint64_t                                 timestamp;                // !< The time of the local radio clock in microseconds when the end of the SFD was present at the local antenna.
} st_802154_ral_transmit_metadata_t;


/**
 * @brief Structure metadata for transmission result.
 */
typedef struct
{
    bool        is_secured;          // !< If the transmitted frame was secured (in the sense of IEEE 802.15.4 security operations).
    bool        dynamic_data_is_set; // !< If dynamic data of the transmitted frame was set.
    uint8_t*    ack_ptr;             // !< ack_ptr is a pointer to a buffer that contains only the received ACK payload (PSDU excluding FCS).
                                     // If ACK was not requested or requested but not received, @ref p_ack is set to NULL.
    uint8_t     length;              // !< Length of the received ACK payload or 0 if @ref p_ack is NULL.
    int8_t      power;               // !< RSSI of the received frame or 0 if @ref p_ack is NULL.
    uint8_t     lqi;                 // !< LQI of the received frame or 0 if @ref p_ack is NULL.
    uint64_t    time;                // !< Timestamp taken when the last symbol of ACK is received. If @ref p_ack is NULL, this field is set to 0, but is considered invalid.
	uint8_t     ack_channel;		 // !< Channel on which ACK is received
} st_802154_ral_transmit_done_metadata_t;


/**
 * @brief Structure metadata for energy detection request.
 */
typedef struct
{
    uint8_t    channel;             // !< Channel on which to perform energy detection
} st_802154_ral_scan_ed_metadata_t;


/**
 * @brief Structure that holds receive indication metadata.
 */
typedef struct
{
    uint8_t                  length;                   // !< Length of the received ACK payload.
    int8_t                   power;                    // !< RSSI of the received frame.
    uint8_t                  lqi;                      // !< LQI of the received frame.
    uint64_t                 time;                     // !< Timestamp taken when the last symbol is received.
	bool                     acked_with_frame_pending; // !< This indicates if this frame was acknowledged with frame pending set.
	bool                     acked_with_sec_enh_ack;   // !< This indicates if this frame was acknowledged with secured enhance ACK.
	uint32_t                 ack_frame_counter;        // !< ACK security frame counter (applicable when `acked_with_sec_enh_ack` is set).
	uint8_t                  ack_key_id;               // !< ACK security key index (applicable when `acked_with_sec_enh_ack` is set).
    st_802154_ral_error_t    error;                    // !< Error returned (if any)
} st_802154_ral_receive_done_metadata_t;


typedef struct 
{
    uint32_t    num_grant_glitch;                        // !< Number of grant glitches.
    uint32_t    num_tx_request;                          // !< Number of tx requests.
    uint32_t    num_tx_grant_immediate;                  // !< Number of tx requests while grant was active.
    uint32_t    num_tx_grant_wait;                       // !< Number of tx requests while grant was inactive.
    uint32_t    num_tx_grant_wait_activated;             // !< Number of tx requests while grant was inactive that were ultimately granted.
    uint32_t    num_tx_grant_wait_timeout;               // !< Number of tx requests while grant was inactive that timed out.
    uint32_t    mum_tx_grant_deactivated_during_request; // !< Number of tx that were in progress when grant was deactivated.
    uint32_t    num_tx_delayed_grant;                    // !< Number of tx requests that were not granted within 50us.
    uint32_t    avg_tx_request_to_grant_time;            // !< Average time in usec from tx request to grant.
    uint32_t    num_rx_request;                          // !< Number of rx requests.
    uint32_t    num_rx_grant_immediate;                  // !< Number of rx requests while grant was active.
    uint32_t    num_rx_grant_wait;                       // !< Number of rx requests while grant was inactive.
    uint32_t    num_rx_grant_wait_activated;             // !< Number of rx requests while grant was inactive that were ultimately granted.
    uint32_t    num_rx_grant_wait_timeout;               // !< Number of rx requests while grant was inactive that timed out.
    uint32_t    num_rx_grant_deactivated_during_request; // !< Number of rx that were in progress when grant was deactivated.
    uint32_t    num_rx_delayed_grant;                    // !<< Number of rx requests that were not granted within 50us.
    uint32_t    avg_rx_request_to_grant_time;            // !< Average time in usec from rx request to grant.
    uint32_t    num_rx_grant_none;                       // !<< Number of rx requests that completed without receiving grant.
    bool        stopped;                                 // !<< Stats collection stopped due to saturation.
} st_802154_ral_coex_metrics;


/**
 * @enum st_802154_ral_state_t
 * @brief States the radio state
 *
 */
typedef enum st_802154_ral_state_t
{
    ST_802154_RAL_STATE_SLEEP,    // !< Sleep state.
    ST_802154_RAL_STATE_RECEIVE,  // !< Receive state.
    ST_802154_RAL_STATE_TRANSMIT, // !< Transmit state.
    ST_802154_RAL_STATE_DISABLED, // !< Disabled state.
} st_802154_ral_state_t;


/**
 * @enum crypto_endian_enum_t
 * @brief States the available endian formats.
 *
 */
typedef enum 
{
	ST_802154_RAL_CRYPTO_LITTLE_ENDIAN,
	ST_802154_RAL_CRYPTO_BIG_ENDIAN
} st_802154_ral_crypto_endian_enum_t;


/**
 * @enum security_mode_enum_t
 * @brief Contains the available security modes.
 *
 */
typedef enum 
{
	ST_802154_RAL_ECB_DECRYPT = 0,
	ST_802154_RAL_CCM_DECRYPT = 1,
	ST_802154_RAL_ECB_ENCRYPT = 2,
	ST_802154_RAL_CCM_ENCRYPT = 3,
	ST_802154_RAL_CTR_ENCRYPT = 4,
	ST_802154_RAL_CTR_DECRYPT = 5,
	ST_802154_RAL_MODES_MAX_NUM
} st_802154_ral_security_mode_enum_t;


/**
 * Defines constants about key types.
 */
typedef enum
{
	ST_802154_RAL_KEY_TYPE_LITERAL_KEY = 0, ///< Use Literal Keys.
	ST_802154_RAL_KEY_TYPE_KEY_REF     = 1, ///< Use Reference to Key.
} st_802154_ral_key_type_enum_t;


/**
 * Defines constants that are used to indicate different radio capabilities.
 */
typedef enum
{
	ST_802154_RAL_CAPS_NONE                 = 0,       ///< Radio supports no capability.
	ST_802154_RAL_CAPS_ACK_TIMEOUT          = 1 << 0,  ///< Radio supports AckTime event.
	ST_802154_RAL_CAPS_ENERGY_SCAN          = 1 << 1,  ///< Radio supports Energy Scans.
	ST_802154_RAL_CAPS_TRANSMIT_RETRIES     = 1 << 2,  ///< Radio supports tx retry logic with collision avoidance (CSMA).
	ST_802154_RAL_CAPS_CSMA_BACKOFF         = 1 << 3,  ///< Radio supports CSMA backoff for frame tx (but no retry).
	ST_802154_RAL_CAPS_SLEEP_TO_TX          = 1 << 4,  ///< Radio supports direct transition from sleep to TX with CSMA.
	ST_802154_RAL_CAPS_TRANSMIT_SEC         = 1 << 5,  ///< Radio supports tx security.
	ST_802154_RAL_CAPS_TRANSMIT_TIMING      = 1 << 6,  ///< Radio supports tx at specific time.
	ST_802154_RAL_CAPS_RECEIVE_TIMING       = 1 << 7,  ///< Radio supports rx at specific time.
	ST_802154_RAL_CAPS_RX_ON_WHEN_IDLE      = 1 << 8,  ///< Radio supports RxOnWhenIdle handling.
	ST_802154_RAL_CAPS_TRANSMIT_FRAME_POWER = 1 << 9,  ///< Radio supports setting per-frame transmit power.
	ST_802154_RAL_CAPS_ALT_SHORT_ADDR       = 1 << 10, ///< Radio supports setting alternate short address.
}st_802154_ral_caps_enum_t;


/**
 * @brief    Initializes the 802.15.4 ST RAL.
 *
 * @note     This function is to be called once, before any other functions from this module.
 *           Only the functions setting the configuration can be called before this call.
 *
 * @param    none
 *
 * @returns  none
 */
void st_802154_ral_init(void);


/**
 * @brief      Sets the channel on which the radio is to operate.
 *
 * @param[in]  a_channel  Channel number (11-26).
 *
 * @returns	   none
 */
void st_802154_ral_set_channel(uint8_t    a_channel);


/**
 * @brief    Gets the channel on which the radio operates.
 *
 * @param    none
 *
 * @returns  Channel number (11-26).
 */
uint8_t st_802154_ral_channel_get(void);


/**
 * @brief      Sets the transmit power.
 *
 * @note       The the requested value is rounded up to the nearest value accepted by the hardware.
 *
 * @param[in]  a_power: Transmit power in dBm.
 *
 * @returns     ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_tx_power_set(int8_t    a_power);


/**
 * @brief       Gets the currently set transmit power.
 *
 * @param[out]  a_power_ptr: Pointer to the variable where the transmit power will be returned.
 *
 * @returns     ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_tx_power_get(int8_t*    a_power_ptr);


/**
 * @brief    Gets the current time.
 *
 * @param    none
 *
 * @returns  Current time in microseconds.
 */
uint64_t st_802154_ral_time_get(void);


/**
 * @brief      Sets the PAN ID used by the device.
 *
 * @param[in]  a_pan_id: PAN ID.
 *
 * @returns	   none
 */
void st_802154_ral_pan_id_set(const uint16_t    a_pan_id);


/**
 * @brief      Sets the extended address of the device.
 *
 * @param[in]  a_ext_address_ptr: Pointer to the extended address (8 bytes, little-endian).
 *
 * @returns    none
 */
void st_802154_ral_extended_address_set(const uint8_t*    a_ext_address_ptr);


/**
 * @brief      Sets the short address of the device.
 *
 * @param[in]  short_address: Short address.
 *
 * @returns    none
 */
void st_802154_ral_short_address_set(const uint16_t    a_short_address);


/**
 * @brief      Gets the EUI 64 bits of the device.
 *
 * @param[in]  a_eui64_Ptr: Pointer to the EUI 64 bits.
 *
 * @returns    none
 */
void st_802154_ral_eui64_get(uint8_t*    a_eui64_Ptr);


/**
 * @brief   Changes the radio state to the @ref ST_802154_RAL_STATE_SLEEP state.
 *          The sleep state is the lowest power state. In this state, the radio cannot transmit or receive frames.
 *
 * @param    none
 *
 * @returns  ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_sleep(void);


/**
 * @brief      Changes the radio state to @ref ST_802154_RAL_STATE_RECEIVE.
 *
 * @param[in]  a_channel  Channel number (11-26) on which the device should try to receive.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_receive(uint8_t    a_channel);


/**
 * @brief      Changes the radio state to @ref ST_802154_RAL_STATE_TRANSMIT.
 *
 * @param[in]  a_data_ptr   Pointer to the data to be transmitted.
 * @param[in]  a_length     Length of the data to be transmitted.
 * @param[in]  a_meta_data  Pointer to the metadata for the transmission.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_transmit(uint8_t*                                    a_data_ptr,
                                             uint8_t                                     a_length,
                                             const st_802154_ral_transmit_metadata_t*    a_meta_data);


/**
 * @brief      Requests radio to perform energy detection.
 *             The radio detects the maximum energy for a given time.
 *             The result of the detection is reported to the higher layer by @ref st_802154_ral_energy_scan_done.
 *
 * @note       @ref st_802154_ral_energy_scan_done can be called before this function returns a result.
 * @note       Performing the energy detection procedure can take longer than requested in @p aScanDuration.
 *             The procedure is performed only during the timeslots granted by a radio arbitrator.
 *             It can be interrupted by other protocols using the radio hardware. If the procedure is
 *             interrupted, it is automatically continued and the sum of time periods during which the
 *             procedure is carried out is not less than the requested @p aScanDuration.
 *
 * @param[in]  a_scan_duration  The duration, in milliseconds, for the channel to be scanned.
 * @param[in]  a_meta_data      Pointer to the metadata for the energy detection procedure.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_energy_detection(uint16_t                                   a_scan_duration,
 											         const st_802154_ral_scan_ed_metadata_t*    a_meta_data);


/**
 * @brief    Requests perfroming CCA. The radio verifies if the channel is clear.
 *           The result of the verification is reported to the higher layer by @ref st_ral_cca_done.
 *
 * @param    none
 *
 * @returns  ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_cca(void);


/**
 * @brief     Enables or disables the promiscuous radio mode.
 *
 * @note      The promiscuous mode is disabled by default.
 *
 * 			  In the promiscuous mode, the driver notifies the higher layer that it received any frame
 * 			  (regardless frame type or destination address).
 * 			  In normal mode (not promiscuous), the higher layer is not notified about ACK frames and frames
 *            with unknown type. Also, frames with a destination address not matching the device address are
 *            ignored.
 *
 * @param[in]  a_enabled  If the promiscuous mode is to be enabled.
 *
 * @returns    none
 */
void st_802154_ral_promiscuous_set(bool    a_enabled);


/**
 * @brief    Get the status of promiscuous mode.
 *
 * @param    none
 *
 * @returns  TRUE   Promiscuous mode is enabled.
 * @returns  FALSE  Promiscuous mode is disabled.
 */
bool st_802154_ral_promiscuous_get(void);


/**
 * @brief      Configures the device as the PAN coordinator.
 *
 * @param[in]  a_enabled  The radio is configured as the PAN coordinator.
 *
 * @returns    none
 */
void st_802154_ral_pan_coord_set(bool    a_enabled);


/**
 * @brief      Enables or disables setting a pending bit in transmitted ACK frames in response to data request commands
 *             based on whether there is pending data for the destination device.
 *             If this API is called with FALSE, the pending bit in every ACK frame is set.
 *             If this API is called with TRUE, the radio driver checks if there is pending data in the indirect queue
 *             destined for the  ACK destination. If there is no such data, the pending bit is cleared.
 *
 * @param[in]  a_enabled  If setting a pending bit in ACK frames based on whether there is pending indirect data for the destination is enabled.
 *
 * @returns    none
 */
void st_802154_ral_auto_pending_bit_set(bool    a_enabled);


/**
 * @brief      Adds the short address of a peer node to the pending bit list.
 *
 * @param[in]  a_short_address  The short address of the node.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_pending_bit_for_short_addr_set(const uint16_t    a_short_address);


/**
 * @brief      Adds the extended address of a peer node to the pending bit list.
 *
 * @param[in]  a_ext_address_ptr  Array of bytes containing the address of the node (little-endian).
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_pending_bit_for_ext_addr_set(const uint8_t*    a_ext_address_ptr);


/**
 * @brief      Removes short address of a peer node from the pending bit list.
 *
 * @param[in]  a_short_address  The short address of the node.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_pending_bit_for_short_addr_clear(const uint16_t    a_short_address);


/**
 * @brief      Removes extended address of a peer node from the pending bit list.
 *
 * @param[in]  a_ext_address_ptr  Array of bytes containing the address of the node (little-endian).
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_pending_bit_for_ext_addr_clear(const uint8_t*    a_ext_address_ptr);


/**
 * @brief    Removes all short addresses from the pending bit list.
 *
 * @param    none
 *
 * @returns  none
 */
void st_802154_ral_pending_bit_for_short_addr_reset(void);


/**
 * @brief    Removes all extended addresses from the pending bit list.
 *
 * @param    none
 *
 * @returns  none
 */
void st_802154_ral_pending_bit_for_ext_addr_reset(void);


/**
 * @brief      Sets the maximum number of frame retries.
 *
 * @param[in]  a_max_retries The maximum number of frame retries.
 *
 * @returns    none
 */
void st_802154_ral_set_max_frame_retries(uint8_t    a_max_retries);



/**
 * @brief      Enables or disables CSMA (Carrier Sense Multiple Access).
 *
 * @param[in]  a_csma_en  Set to 1 to enable CSMA, 0 to disable.
 *
 * @returns    none
 */
void st_802154_ral_set_csma_en(uint8_t    a_csma_en);


/**
 * @brief    Gets whether CSMA (Carrier Sense Multiple Access) is enabled or disabled.
 *
 * @param    none
 *
 * @returns  1 if enabled, 0 if disabled
 */
uint8_t st_802154_ral_get_csma_en(void);



/**
 * @brief      Enables or disables CCA
 *
 * @param[in]  a_cca_en  Set to 1 to enable CCA, 0 to disable.
 *
 * @returns    none
 */
void st_802154_ral_set_cca_en(uint8_t    a_cca_en);


/**
 * @brief    Gets whether CCA is enabled or disabled.
 *
 * @param    none
 *
 * @returns  1 if enabled, 0 if disabled
 */
uint8_t st_802154_ral_get_cca_en(void);


/**
 * @brief      Sets the maximum number of CSMA frame retries.
 *
 * @param[in]  a_max_retries The maximum number of CSMA frame retries.
 *
 * @returns    none
 */
void st_802154_ral_set_max_csma_frame_retries(uint8_t    a_max_retries);


/**
 * @brief      Sets the minimum value of the CSMA backoff exponent.
 *
 * @param[in]  a_min_be The minimum backoff exponent.
 *
 * @returns    none
 */
void st_802154_ral_set_min_csma_be(uint8_t    a_min_be);


/**
 * @brief      Sets the maximum value of the CSMA backoff exponent.
 *
 * @param[in]  a_max_be The maximum backoff exponent.
 *
 * @returns    none
 */
void st_802154_ral_set_max_csma_be(uint8_t    a_max_be);


/**
 * @brief      Sets the maximum number of CSMA backoffs.
 *
 * @param[in]  a_max_backoff The maximum number of CSMA backoffs.
 *
 * @returns    none
 */
void st_802154_ral_set_max_csma_backoff(uint8_t    a_max_backoff);


/**
 * @brief       Gets the current CCA energy detection threshold.
 *
 * @param[out]  a_cca_thr_ptr Pointer to the current CCA energy detection threshold.
 *
 * @returns     ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_get_cca_energy_detect_threshold(int8_t*    a_cca_thr_ptr);


/**
 * @brief      Sets the CCA energy detection threshold.
 *
 * @param[in]  a_cca_thr The CCA energy detection threshold to set.
 * 
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_cca_energy_detect_threshold(int8_t    a_cca_thr);


/**
 * @brief      Enables or disables continuous reception mode.
 *
 * @param[in]  a_enable True to enable, false to disable.
 *
 * @returns    none
 */
void st_802154_ral_set_continuous_reception(bool    a_enable);


/**
 * @brief      Enables or disables implicit broadcast mode.
 *
 * @param[in]  a_implicit_broadcast True to enable, false to disable.
 *
 * @returns    none
 */
void st_802154_ral_set_implicit_broadcast(bool    a_implicit_broadcast);

/**
 * @brief    Resets the ST radio.
 *
 *           This function performs a reset of the radio layer, restoring it to its default state.
 *           It can be used to recover from unexpected states or errors.
 *
 * @param    none
 *
 * @returns  ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_radio_reset(void);


/**
 * @brief      Generates random number.
 *
 * @param[out] a_rnd_ptr       Pointer to store the generated random number.
 * @param[in]  a_len           Length of the random number to generate.
 * @param[in]  a_check_cont_rx Indicates whether to check for continuous reception.
 * 
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_mac_gen_rnd_num(uint8_t*    a_rnd_ptr,
													uint16_t    a_len,
													uint8_t     a_check_cont_rx);


/**
 * @brief      enable/disable antenna diversity
 *
 * @param[in]  a_enable: enable:1 / disable:0
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_ant_div_enable(uint8_t    a_enable);


/**
 * @brief      sets the antenna diversity configuration parameters
 *
 * @param[in]  a_ant_div_params_ptr pointer to the antenna diversity configurations
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_ant_div_params(antenna_diversity_st*    a_ant_div_params_ptr);

/**
 * @brief       Gets the antenna diversity configuration parameters
 *
 * @param[out]  a_ant_div_params_ptr pointer to the antenna diversity configurations
 *
 * @returns     none
 */
void st_802154_ral_get_ant_div_params(antenna_diversity_st*    a_ant_div_params_ptr);


/**
 * @brief       Sets the default antenna
 *
 * @param[out]  a_default_ant_id ID of the antenna to be used as default
 *
 * @returns     ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_default_ant_id(uint8_t    a_default_ant_id);


/**
 * @brief       Sets the antenna diversity algorithm RSSI threshold
 *
 * @param[out]  a_rssi_threshold RSSI threshold used to decide on switching between antennas
 *
 * @returns     ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_ant_div_rssi_threshold(int8_t    a_rssi_threshold);


/**
 * @brief       Sets configurable library parameters
 *
 * @param[in]	a_support_openthread_1_2	    : support_openthread_1_2: true / false
 * @param[in]	a_mac_layer_build	            : mac_layer_build: true / false
 * @param[in]   a_ack_all_received_frames_with_ar_bit_set
 *
 * @returns     ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_config_lib_params(bool    a_support_openthread_1_2,
														  bool    a_mac_layer_build,
														  bool    a_ack_all_received_frames_with_ar_bit_set);


/**
 *
 * @brief       Gets configurable library parameters
 *
 * @param[out]	a_support_openthread_1_2_ptr	    : support_openthread_1_2: true / false
 * @param[out]	a_mac_layer_build_ptr	            : mac_layer_build: true / false
 * @param[out]  a_ack_all_received_frames_with_ar_bit_set_ptr
 *
 * @returns     none
 */
void st_802154_ral_get_config_lib_params(bool*    a_support_openthread_1_2_ptr,
										 bool*    a_mac_layer_build_ptr,
										 bool*    a_ack_all_received_frames_with_ar_bit_set_ptr);


/**
 * @brief       Sets RTL polling time
 *
 * @param[in]	a_rtl_polling_time
 *
 * @returns     none
 */
void st_802154_ral_set_rtl_polling_time(uint8_t    a_rtl_polling_time);


/**
 * @brief    Gets RTL polling time
 *
 * @param    none
 *
 * @returns  rtl_polling_time
 */
uint8_t st_802154_ral_get_rtl_polling_time(void);


/** 
 * @brief      Sets the MAC frame counter.
 *
 * @param[in]  a_mac_frame_counter The MAC frame counter value to set.
 *
 * @returns    none
 */
void st_802154_ral_set_mac_frame_counter(uint32_t    a_mac_frame_counter);


/** 
 * @brief      Sets the MAC frame counter if the provided value is larger than the current one.
 *
 * @param[in]  a_mac_frame_counter The MAC frame counter value to compare and set.
 *
 * @returns    none
 */
void st_802154_ral_set_mac_frame_counter_if_larger(uint32_t    a_mac_frame_counter);


/** 
 * @brief Sets the MAC key for secure communications.
 *
 * @param[in]  a_key_id_mode   The key ID mode.
 * @param[in]  a_key_id        The key ID.
 * @param[in]  a_prev_key_ptr  Pointer to the previous key.
 * @param[in]  a_prev_key_reference  previous key reference.
 * @param[in]  a_curr_key_ptr  Pointer to the current key.
 * @param[in]  a_curr_key_reference  current key reference.
 * @param[in]  a_next_key_ptr  Pointer to the next key.
 * @param[in]  a_next_key_reference  next key reference.
 *
 * @returns    none
 */
void st_802154_ral_set_mac_key(uint8_t                          a_key_id_mode,
                          	   uint8_t                          a_key_id,
                          	   const uint8_t*	                a_prev_key_ptr,
							   uint32_t                         a_prev_key_reference,
                          	   const uint8_t*                   a_curr_key_ptr,
							   uint32_t                         a_curr_key_reference,
                          	   const uint8_t*                   a_next_key_ptr,
							   uint32_t                         a_next_key_reference,
							   st_802154_ral_key_type_enum_t    a_key_type);


/**
 * @brief       Generates random number.
 *
 * @param[out]  a_rnd_ptr Pointer to store the generated random number.
 * @param[in]   a_len     Length of the random number to generate.
 *
 * @returns     0 on success, failure otherwise
 */
uint32_t st_802154_ral_platform_gen_rnd_num(uint8_t*    a_rnd_ptr,
											uint32_t    a_len);


/**
 * @brief      Provides MAC-CCM security mode
 *
 * @param[in]  a_pckt_ptr	   : Pointer to the data buffer (variable length in case of CCM mode, 16 bytes in case of ECB mode).
 * 							     The resulting Encrypted/Decrypted data overwrites this buffer.
 * @param[in]  a_key_ptr	   : Pointer to the security key buffer (16 bytes).
 * @param[in]  a_nonce_ptr	   : Pointer to the security nonce buffer (13 bytes in case of CCM mode, a Null pointer in case of ECB mode).
 * @param[in]  a_mic_len	   : Length of MIC, supported values are 0, 4, 6, 8, 10, 12, 14, and 16 in case of CCM, 0 only in case of ECB.
 * @param[in]  a_ad_len		   : Length of Data to be authenticated.
 * @param[in]  a_md_len		   : Length of Data to be encrypted.
 * @param[in]  a_key_endian	   : Represents the format of the security key.
 * @param[in]  a_data_endian   : Represents the endian format of the data.
 * @param[in]  a_security_mode : Hardware security mode.
 *
 * @returns    0 if success, failure otherwise
 */
uint32_t st_802154_ral_platform_crypto(uint8_t*                              a_pckt_ptr,
									   const uint8_t*                        a_key_ptr,
									   uint8_t*                              a_nonce_ptr,
									   uint32_t                              a_mic_len,
									   uint32_t                              a_ad_len,
									   uint32_t                              a_md_len,
									   st_802154_ral_crypto_endian_enum_t    a_key_endian,
									   st_802154_ral_crypto_endian_enum_t    a_data_endian,
									   st_802154_ral_security_mode_enum_t    a_security_mode);


/**
 * @brief    Returns the ST Radio Abstraction Layer state
 *
 * @param    none
 *
 * @returns  st_802154_ral_state_t
 */
st_802154_ral_state_t st_802154_ral_get_state(void);


/**
 * @brief    Enables the radio
 *
 * @param    none
 *
 * @returns  ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_enable(void);


/**
 * @brief    Disables the radio
 *
 * @param    none
 *
 * @returns  ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_disable(void);


/**
 * @brief    Gets whether the radio is enabled or disabled
 *
 * @param    none
 *
 * @returns  TRUE if radio is enabled, FALSE if radio is disabled.
 */
bool st_802154_ral_is_enabled(void);


/**
 * @brief   Get the radio capabilities.
 *
 * @param   none
 *
 * @returns The radio capability bit vector (see st_802154_ral_caps_enum_t definitions).
 */
uint16_t st_802154_ral_get_capabilities(void);


/**
 * @brief   Get the radio receive sensitivity value.
 *
 * @param   none
 *
 * @returns The radio receive sensitivity value in dBm.
 */
int8_t st_802154_ral_get_receive_sensitivity(void);


/**
 * @brief    Get the bus latency in microseconds between the host and the radio chip.
 *
 * @param    none
 *
 * @returns  The bus latency in microseconds between the host and the radio chip.
 *           Return 0 when the MAC and above layer and Radio layer resides on the same chip.
 */
uint32_t st_802154_ral_get_bus_latency(void);


/**
 * @brief    Sets the bus latency between the host and the radio chip in microseconds.
 *
 * @param    a_bus_latency in microseconds
 *
 * @returns  none
 */
void st_802154_ral_set_bus_latency(uint32_t    a_bus_latency);


/**
 * @brief    Gets the bus speed in bits/second between the host and the radio chip.
 *
 * @param    none
 *
 * @returns  The bus speed in bits/second between the host and the radio chip.
 *           Return 0 when the MAC and above layer and Radio layer resides on the same chip.
 */
uint32_t st_802154_ral_get_bus_speed(void);


/**
 * @brief      Schedules a radio reception window at a specific time and duration.
 *
 * @param[in]  a_channel   The radio channel on which to receive.
 * @param[in]  a_start     The receive window start time relative to the local
 *                         radio clock, see `st_802154_ral_time_get`. The radio
 *                         receiver SHALL be on and ready to receive the first
 *                         symbol of a frame's SHR at the window start time.
 * @param[in]  a_duration  The receive window duration, in microseconds, as
 *                         measured by the local radio clock. The radio SHOULD be
 *                         turned off (or switched to TX mode if an ACK frame
 *                         needs to be sent) after that duration unless it is
 *                         still actively receiving a frame. In the latter case
 *                         the radio SHALL be kept in reception mode until frame
 *                         reception has either succeeded or failed.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_receive_at(uint8_t     a_channel,
											   uint32_t    a_start,
		                                       uint32_t    a_duration);


/**
 * @brief      Enable or disable CSL receiver.
 *
 * @param[in]  a_csl_period    CSL period, 0 for disabling CSL. CSL period is in unit of 10 symbols.
 * @param[in]  a_short_addr    The short source address of CSL receiver's peer.
 * @param[in]  a_ext_Addr_ptr  The extended source address of CSL receiver's peer.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t  st_802154_ral_enable_csl( uint32_t            a_csl_period,
                             					 const uint16_t      a_short_addr,
					                             const uint8_t*      a_ext_Addr_ptr);


/**
 * @brief    Resets CSL receiver in the platform.
 *
 * @param    none
 *
 * @returns  ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_reset_csl(void);


/**
 * @brief      Update CSL sample time in radio.
 *
 *			   Sample time is stored in radio driver as a copy to calculate phase when
 * 			   sending ACK with CSL IE. The CSL sample (window) of the CSL receiver extends
 * 			   before and after the sample time. The CSL sample time marks a timestamp in
 *             the CSL sample window when a frame should be received in "ideal conditions"
 *             if there would be no inaccuracy/clock-drift.
 *
 * @param[in]  a_csl_sample_time  The next sample time, in microseconds.
 *                                It is the time when the first symbol of the MHR of the frame is expected.
 *
 * @returns    none
 */
void st_802154_ral_update_csl_sample_time(uint32_t     a_csl_sample_time);


/**
 * @brief  Get the current estimated worst case accuracy (maximum +/- deviation from the
 *         nominal frequency) of the local radio clock in units of PPM.
 *         This is the clock used to schedule CSL operations.
 *
 * @param    none
 *
 * @returns  The current CSL rx/tx scheduling drift, in PPM.
 */
uint8_t st_802154_ral_get_csl_accuracy(void);


/**
 * @brief    The fixed uncertainty (i.e. random jitter) of the arrival time of CSL
 *           transmissions received by this device in units of 10 microseconds.

 * @param    none
 *
 * @returns  The CSL Uncertainty in units of 10 us.
 */
uint8_t st_802154_ral_get_csl_uncertainty(void);


/**
 * @brief    Sets the clock accuracy
 *
 * @param    a_clk_acc in PPM
 *
 * @returns  none
 */
void st_802154_ral_set_clk_accuracy(uint8_t     a_clk_acc);


/**
 * @brief    Sets the clock uncertainty
 *
 * @param    a_clk_uncer in units of 10us
 *
 * @returns  none
 */
void st_802154_ral_set_clk_uncertainty(uint8_t     a_clk_uncer);


/**
 * @brief Enable/disable or update Enhanced-ACK Based Probing in radio for a specific Initiator.
 *
 * @param[in]  a_pdu_count        PDU count
 * @param[in]  a_lqi              link quality indicator
 * @param[in]  a_link_margin      link margin
 * @param[in]  a_rssi             Received Signal Strength Indicator
 * @param[in]  a_short_address    The short address of the Probing Initiator.
 * @param[in]  a_ext_address_ptr  The extended source address of the Probing Initiator. @p aExtAddr MUST NOT be `NULL`.
 *
 * @returns  ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_configure_enh_ack_probing(bool              a_pdu_count,
										  					  bool              a_lqi,
										  					  bool              a_link_margin,
										  					  bool              a_rssi,
										  					  const uint16_t    a_short_address,
										  					  const uint8_t*    a_ext_address_ptr);


/**
 * @brief       Sets the radio link metrics noise floor
 *
 * @param[in]   a_noise_floor
 *
 * @returns     none
 */
void st_802154_ral_radio_link_metrics_set_noise_floor(int8_t    a_noise_floor);


/**
 * @brief       Gets the external FEM's Rx LNA gain in dBm.
 *
 * @param[out]  a_gain_ptr  The external FEM's Rx LNA gain in dBm.
 *
 * @returns     ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_get_fem_lna_gain(int8_t*    a_gain_ptr);


/**
 * @brief      Sets the external FEM's Rx LNA gain in dBm.
 *
 * @param[in]  a_gain  The external FEM's Rx LNA gain in dBm.
 *
 * @returns     ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_fem_lna_gain(int8_t    a_gain);


/**
 * @brief      Sets the region code.
 *
 * @param[in]  a_region_code  The radio region code. The `aRegionCode >> 8` is first ascii char
 *                            and the `aRegionCode & 0xff` is the second ascii char.
 *
 * @returns     ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_region(uint16_t    a_region_code);


/**
 * @brief      Get the region code. The radio region format is the 2-bytes ascii representation of the ISO 3166 alpha-2 code.
 *
 * @param[out] a_region_code_ptr  The radio region.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_get_region(uint16_t*   a_region_code_ptr);


/**
 * @brief    Gets the most recent RSSI measurement.
 *
 * @param    none
 *
 * @returns  The RSSI in dBm when it is valid.  127 when RSSI is invalid.
 */
int8_t st_802154_ral_get_rssi(void);


/**
 * @brief    Gets the most recent LQI.
 *
 * @param    none
 *
 * @returns  The LQI
 */
uint8_t st_802154_ral_get_lqi_value(void);

/**
 *  @brief  Gets the radio supported channel mask that the device is allowed to be on.
 *
 * @param   none
 *
 * @returns The radio supported channel mask.
 */
uint32_t st_802154_ral_get_supported_channel_mask(void);


/**
 * @brief    Gets the radio preferred channel mask that the device prefers to form on.
 *
 * @param    none
 *
 * @returns  The radio preferred channel mask.
 */
uint32_t st_802154_ral_get_preferred_channel_mask(void);


/**
 * @brief      Adds a calibrated power of the specified channel to the power calibration table.
 *
 * @param[in]  a_channel                   The radio channel.
 * @param[in]  a_actual_power              The actual power in 0.01dBm.
 * @param[in]  a_raw_power_setting_ptr     A pointer to the raw power setting byte array.
 * @param[in]  a_raw_power_setting_length  The length of the @p aRawPowerSetting.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_add_calibrated_power(uint8_t           a_channel,
                                      					 int16_t           a_actual_power,
                                      					 const uint8_t*    a_raw_power_setting_ptr,
                                     					 uint16_t          a_raw_power_setting_length);


/**
 * @brief    Clears all calibrated powers from the power calibration table.
 *
 * @param    none
 *
 * @returns  ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_clear_calibrated_power(void);


/**
 * @brief      Sets the target power for the given channel.

 * @param[in]  a_channel       The radio channel.
 * @param[in]  a_target_power  The target power in 0.01dBm.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_channel_target_power(uint8_t    a_channel,
															 int16_t    a_target_power);


/**
 *  @brief         Gets the raw power setting for the given channel.
 *
 * @param[in]      aChannel                The radio channel.
 * @param[out]     aRawPowerSetting        A pointer to the raw power setting byte array.
 * @param[in,out]  aRawPowerSettingLength  On input, a pointer to the size of @p aRawPowerSetting.
 *                                         On output, a pointer to the length of the raw power setting data.
 *
 * @returns        ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_get_raw_power_setting(
                                             uint8_t      aChannel,
                                             uint8_t*     aRawPowerSetting,
                                             uint16_t*    aRawPowerSettingLength);


/**
 * @brief      Enable the radio coex.
 *
 * @param[in]  a_enabled   TRUE to enable the radio coex, FALSE otherwise.
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_coex_enabled(bool    a_enabled);


/**
 * @brief   Check whether radio coex is enabled or not.
 *
 * @param   none
 *
 * @returns TRUE if the radio coex is enabled, FALSE otherwise.
 */
bool st_802154_ral_is_coex_enabled(void);


/**
 * @brief       Get the radio coexistence metrics
 *
 * @param[out]  a_coex_metrics_ptr  A pointer to the coexistence metrics structure.
 *
 * @returns     ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_get_coex_metrics(st_802154_ral_coex_metrics*    a_coex_metrics_ptr);


/**
 * @brief Set the PHY continuous modulation and continuous wave modes upon enable
 *
 * @param[in] a_type	    : The type of the modulation (0: modulation, 1: wave)
 * @param[in] a_enable_mode	: TRUE to enable the selected mode, FALSE to disable it
 * @param[in] a_chnl_num	: Channel number to be used in modulation (range: 0 to 15)
 * @param[in] a_pwr         : The used power in dBm.
 * @retval Status
 */
st_802154_ral_error_t st_802154_ral_platform_zigbee_set_phy_cont_modul_mode(uint8_t    a_type, 
																			uint8_t    a_enable_mode, 
																			uint8_t    a_chnl_num, 
																			int8_t     a_pwr);


/**
 * @brief      Sets the rx-on-when-idle state to the radio platform.
 *
 * @param[in]  a_enable  TRUE to keep radio in Receive state, FALSE to put to Sleep state during idle periods.
 *
 * @returns    none
 */
void st_802154_ral_set_rx_on_when_idle(bool    a_enable);


/**
 * @brief      Configures automatic ACK response by ST RAL layer
 *
 * @param[in]  a_auto_ack_state : Auto ACK state (TRUE to enable, FALSE to disable)
 *
 * @returns    ST_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
st_802154_ral_error_t st_802154_ral_set_auto_ack_state(uint8_t    a_auto_ack_state);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* ST_802154_RAL_H_ */

/** @} */
