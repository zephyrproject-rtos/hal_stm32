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
 * @defgroup STM32WBA 802.15.4 radio driver
 * @{
 *
 */

#ifndef STM32WBA_802154_H_
#define STM32WBA_802154_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Errors reported during the frame transmission.
 */
typedef uint8_t stm32wba_802154_ral_tx_error_t;

#define STM32WBA_802154_RAL_TX_ERROR_NONE                0x00 // !< There is no transmit error.
#define STM32WBA_802154_RAL_TX_ERROR_BUSY_CHANNEL        0x0F // !< CCA reported busy channel before the transmission.
#define STM32WBA_802154_RAL_TX_ERROR_NO_MEM              0x03 // !< No receive buffer is available to receive an ACK.
#define STM32WBA_802154_RAL_TX_ERROR_NO_ACK              0x0E // !< ACK frame was not received during the timeout period.
#define STM32WBA_802154_RAL_TX_ERROR_ABORTED             0x0B // !< Procedure was aborted by another operation.

/**
 * @brief Possible errors during the frame reception.
 */
typedef uint8_t stm32wba_802154_ral_rx_error_t;

#define STM32WBA_802154_RAL_RX_ERROR_NONE                    0x00 // !< There is no receive error.
#define STM32WBA_802154_RAL_RX_ERROR_NO_BUFFERS              0x03 // !< Not enough buffers.

/**
 * @brief Structure with transmit request metadata for simple transmission request.
 */
typedef struct
{
    bool    is_secured;             // !< If the frame to be transmitted is already secured (in the sense of IEEE 802.15.4 security operations).
    bool    dynamic_data_is_set;    // !< If dynamic data of the frame to be transmitted is set.
    bool    cca;                    // !< If the driver is to perform a CCA procedure before transmission.
    int8_t  tx_power;               // !< Transmission power in dBm
    uint8_t tx_channel;             // !< Transmission channel
} stm32wba_802154_ral_transmit_metadata_t;

/**
 * @brief Structure that holds transmission result metadata.
 */
typedef struct
{
    bool    is_secured;             // !< If the transmitted frame was secured (in the sense of IEEE 802.15.4 security operations).
    bool    dynamic_data_is_set;    // !< If dynamic data of the transmitted frame was set.
    uint8_t * p_ack;                // !< p_ack is a pointer to a buffer that contains only the received ACK payload (PSDU excluding FCS).
                                    // If ACK was not requested or requested but not received, @ref p_ack is set to NULL.
    uint8_t  length;                // !< Length of the received ACK payload or 0 if @ref p_ack is NULL.
    int8_t   power;                 // !< RSSI of the received frame or 0 if @ref p_ack is NULL.
    uint8_t  lqi;                   // !< LQI of the received frame or 0 if @ref p_ack is NULL.
    uint64_t time;                  // !< Timestamp taken when the last symbol of ACK is received. If @ref p_ack is NULL, this field is set to 0, but is considered invalid.
} stm32wba_802154_ral_transmit_done_metadata_t;

/**
 * @brief Structure that holds receive result metadata.
 */
typedef struct
{
    uint8_t  length;                // !< Length of the received ACK payload.
    int8_t   power;                 // !< RSSI of the received frame.
    uint8_t  lqi;                   // !< LQI of the received frame.
    uint64_t time;                  // !< Timestamp taken when the last symbol is received.
    uint8_t error;                  // !< Error returned (if any)
} stm32wba_802154_ral_receive_done_metadata_t;

/**
 * @brief stm32wba_802154_ral_error_t - Radio Abstraction Layer error/status codes
 *
 * Enumerates the return codes used by the ST Radio Abstraction Layer (RAL)
 * to indicate the result of API calls. Values represent success, specific
 * failure conditions and transient states (for example: timeout, busy,
 * invalid parameter). Callers should inspect returned stm32wba_802154_ral_error_t values
 * to determine appropriate recovery or error handling actions.
 */
typedef enum stm32wba_802154_ral_error_t
{
    STM32WBA_802154_RAL_ERROR_NONE = 0,                           // !< No error.
    STM32WBA_802154_RAL_ERROR_FAILED = -1,                        // !< Operational failed.
    STM32WBA_802154_RAL_ERROR_DROP = -2,                          // !< Message was dropped.
    STM32WBA_802154_RAL_ERROR_NO_BUFS = -3,                       // !< Insufficient buffers.
    STM32WBA_802154_RAL_ERROR_BUSY = -4,                          // !< Service is busy and could not service the operation.
    STM32WBA_802154_RAL_ERROR_INVALID_ARGS = -5,                  // !< Input arguments are invalid.
    STM32WBA_802154_RAL_ERROR_SECURITY = -6,                      // !< Security checks failed.
    STM32WBA_802154_RAL_ERROR_NO_ADDRESS = -7,                    // !< Address is not in the source match table.
    STM32WBA_802154_RAL_ERROR_ABORT = -8,                         // !< Operation was aborted.
    STM32WBA_802154_RAL_ERROR_NOT_IMPLEMENTED = -9,               // !< Function or method is not implemented.
    STM32WBA_802154_RAL_ERROR_INVALID_STATE = -10,                // !< Cannot complete due to invalid state.
    STM32WBA_802154_RAL_ERROR_NO_ACK = -11,                       // !< No acknowledgment was received after macMaxFrameRetries (IEEE 802.15.4-2006).
    STM32WBA_802154_RAL_ERROR_CHANNEL_ACCESS_FAILURE = -12,       // !< A transmission could not take place due to activity on the channel, i.e., the CSMA-CA mechanism has failed (IEEE 802.15.4-2006).
    STM32WBA_802154_RAL_ERROR_FCS = -13,                          // !< FCS check failure while receiving.
    STM32WBA_802154_RAL_ERROR_NO_FRAME_RECEIVED = -14,            // !< No frame received.
    STM32WBA_802154_RAL_ERROR_INVALID_SOURCE_ADDRESS = -15,       // !< Received a frame from an invalid source address.
    STM32WBA_802154_RAL_ERROR_DESTINATION_ADDRESS_FILTERED = -16, // !< Received a frame filtered by the destination address check.
    STM32WBA_802154_RAL_ERROR_NOT_FOUND = -17,                    // !< The requested item could not be found.
    STM32WBA_802154_RAL_ERROR_GENERIC = -18,                      // !< Generic error.
    STM32WBA_802154_RAL_ERROR_UNKNOWN = -255                      // !< Unknown error.
} stm32wba_802154_ral_error_t;


/**
 * @brief Initializes the 802.15.4 driver.
 *
 * This function initializes the RADIO peripheral in the @ref RADIO_STATE_SLEEP state.
 *
 * @note This function is to be called once, before any other functions from this module.
 *       Only the functions setting the configuration can be called before this call.
 */
void stm32wba_802154_ral_init(void);

/**
 * @brief Sets the channel on which the radio is to operate.
 *
 * @param[in]  channel  Channel number (11-26).
 */
void stm32wba_802154_ral_set_channel(uint8_t channel);

/**
 * @brief Gets the channel on which the radio operates.
 *
 * @returns  Channel number (11-26).
 */
uint8_t stm32wba_802154_ral_channel_get(void);

/**
 * @brief Sets the transmit power.
 *
 * @note The driver recalculates the requested value to the nearest value accepted by the hardware.
 *       The calculation result is rounded up.
 *
 * @param[in]  power  Transmit power in dBm.
 */
void stm32wba_802154_ral_tx_power_set(int8_t power);

/**
 * @brief Gets the currently set transmit power.
 *
 * @param[out]  aPower  Pointer to the variable where the transmit power will be stored.
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_tx_power_get(int8_t *aPower);

/**
 * @brief Gets the current time.
 *
 * @returns Current time in microseconds.
 */
uint64_t stm32wba_802154_ral_time_get(void);

/**
 * @brief Sets the PAN ID used by the device.
 *
 * @param[in]  pan_id  PAN ID.
 *
 * This function makes a copy of the PAN ID.
 */
void stm32wba_802154_ral_pan_id_set(const uint16_t pan_id);

/**
 * @brief Sets the extended address of the device.
 *
 * @param[in]  aExtAddress  Pointer to the extended address (8 bytes, little-endian).
 *
 * This function makes a copy of the address.
 */
void stm32wba_802154_ral_extended_address_set(const uint8_t * aExtAddress);

/**
 * @brief Sets the short address of the device.
 *
 * @param[in]  short_address  Short address.
 *
 * This function makes a copy of the address.
 */
void stm32wba_802154_ral_short_address_set(const uint16_t short_address);

/**
 * @brief Get the EUI 64 bits of the device.
 *
 * @param[in]  p_eui64  Pointer to the EUI 64 bits.
 *
 * This function makes a copy of the address.
 */
void stm32wba_802154_ral_eui64_get(uint8_t *p_eui64);

/**
 * @brief Changes the radio state to the @ref RADIO_STATE_SLEEP state.
 *
 * The sleep state is the lowest power state. In this state, the radio cannot transmit or receive
 * frames. It is the only state in which the driver releases the high-frequency clock and does not
 * request timeslots from a radio arbiter.
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_sleep(void);

/**
 * @brief Changes the radio state to @ref RADIO_STATE_RX.
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_receive(void);

/**
 * @brief Changes the radio state to transmit.
 *
 * @param[in]  aData      Pointer to the data to be transmitted.
 * @param[in]  length     Length of the data to be transmitted.
 * @param[in]  aMetadata  Pointer to the metadata for the transmission.
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_transmit(uint8_t                                        *aData,
                                                         uint8_t                                        length,
                                                         const stm32wba_802154_ral_transmit_metadata_t  *aMetadata);

/**
 * @brief Changes the radio state to energy detection.
 *
 * In the energy detection state, the radio detects the maximum energy for a given time.
 * The result of the detection is reported to the higher layer by @ref stm32wba_802154_energy_scan_done.
 *
 * @note @ref stm32wba_802154_energy_scan_done can be called before this function returns a result.
 * @note Performing the energy detection procedure can take longer than requested in @p aScanDuration.
 *       The procedure is performed only during the timeslots granted by a radio arbiter.
 *       It can be interrupted by other protocols using the radio hardware. If the procedure is
 *       interrupted, it is automatically continued and the sum of time periods during which the
 *       procedure is carried out is not less than the requested @p aScanDuration.
 *
 * @param[in]  aScanDuration   The duration, in milliseconds, for the channel to be scanned.
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_energy_detection(uint16_t aScanDuration);

/**
 * @brief Changes the radio state to @ref RADIO_STATE_CCA.
 *
 * @note @ref st_ral_cca_done can be called before this function returns a result.
 *
 * In the CCA state, the radio verifies if the channel is clear. The result of the verification is
 * reported to the higher layer by @ref st_ral_cca_done.
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_cca(void);

/**
 * @brief Enables or disables the promiscuous radio mode.
 *
 * @note The promiscuous mode is disabled by default.
 *
 * In the promiscuous mode, the driver notifies the higher layer that it received any frame
 * (regardless frame type or destination address).
 * In normal mode (not promiscuous), the higher layer is not notified about ACK frames and frames
 * with unknown type. Also, frames with a destination address not matching the device address are
 * ignored.
 *
 * @param[in]  enabled  If the promiscuous mode is to be enabled.
 */
void stm32wba_802154_ral_promiscuous_set(bool enabled);

/**
 * @brief Configures the device as the PAN coordinator.
 *
 * @note That information is used for packet filtering.
 *
 * @param[in]  enabled  The radio is configured as the PAN coordinator.
 */
void stm32wba_802154_ral_pan_coord_set(bool enabled);

/**
 * @brief Enables or disables setting a pending bit in automatically transmitted ACK frames.
 *
 * @note Setting a pending bit in automatically transmitted ACK frames is enabled by default.
 *
 * The radio driver automatically sends ACK frames in response frames destined for this node with
 * the ACK Request bit set. The pending bit in the ACK frame can be set or cleared regarding data
 * in the indirect queue destined for the ACK destination.
 *
 * If setting a pending bit in ACK frames is disabled, the pending bit in every ACK frame is set.
 * If setting a pending bit in ACK frames is enabled, the radio driver checks if there is data
 * in the indirect queue destined for the  ACK destination. If there is no such data,
 * the pending bit is cleared.
 *
 * @note Due to the ISR latency, the radio driver might not be able to verify if there is data
 *       in the indirect queue before ACK is sent. In this case, the pending bit is set.
 *
 * @param[in]  aEnable  If setting a pending bit in ACK frames is enabled.
 */
void stm32wba_802154_ral_auto_pending_bit_set(bool aEnable);

/**
 * @brief Adds the short address of a peer node to the pending bit list.
 *
 * @note This function makes a copy of the given address.
 *
 * @param[in]  aShortAddress  The short address of the node.
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_pending_bit_for_short_addr_set(const uint16_t aShortAddress);

/**
 * @brief Adds the extended address of a peer node to the pending bit list.
 *
 * @note This function makes a copy of the given address.
 *
 * @param[in]  aExtAddress  Array of bytes containing the address of the node (little-endian).
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_pending_bit_for_ext_addr_set(const uint8_t * aExtAddress);

/**
 * @brief Removes short address of a peer node from the pending bit list.
 *
 * @param[in]  aShortAddress  The short address of the node.
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_pending_bit_for_short_addr_clear(const uint16_t aShortAddress);

/**
 * @brief Removes extended address of a peer node from the pending bit list.
 *
 * @param[in]  aExtAddress  Array of bytes containing the address of the node (little-endian).
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_pending_bit_for_ext_addr_clear(const uint8_t * aExtAddress);

/**
 * @brief Removes all short addresses from the pending bit list.
 *
 */
void stm32wba_802154_ral_pending_bit_for_short_addr_reset(void);

/**
 * @brief Removes all extended addresses from the pending bit list.

 */
void stm32wba_802154_ral_pending_bit_for_ext_addr_reset(void);

/**
 * @brief Sets the maximum number of frame retries.
 *
 * @param[in] max_retries The maximum number of frame retries.
 */
void stm32wba_802154_ral_set_max_frame_retries(uint8_t max_retries);

/**
 * @brief Enables or disables CSMA (Carrier Sense Multiple Access).
 *
 * @param[in] csma_en  Set to 1 to enable CSMA, 0 to disable.
 */
void stm32wba_802154_ral_set_csma_en(uint8_t csma_en);

/**
 * @brief Sets the maximum number of CSMA frame retries.
 *
 * @param[in] max_retries The maximum number of CSMA frame retries.
 */
void stm32wba_802154_ral_set_max_csma_frame_retries(uint8_t max_retries);

/**
 * @brief Sets the minimum value of the CSMA backoff exponent.
 *
 * @param[in] min_be The minimum backoff exponent.
 */
void stm32wba_802154_ral_set_min_csma_be(uint8_t min_be);

/**
 * @brief Sets the maximum value of the CSMA backoff exponent.
 *
 * @param[in] max_be The maximum backoff exponent.
 */
void stm32wba_802154_ral_set_max_csma_be(uint8_t max_be);

/**
 * @brief Sets the maximum number of CSMA backoffs.
 *
 * @param[in] max_backoff The maximum number of CSMA backoffs.
 */
void stm32wba_802154_ral_set_max_csma_backoff(uint8_t max_backoff);

/**
 * @brief Gets the current CCA energy detection threshold.
 *
 * @param[out] cca_thr Pointer to store the current CCA energy detection threshold.
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_get_cca_energy_detect_threshold(int8_t *cca_thr);

/**
 * @brief Sets the CCA energy detection threshold.
 *
 * @param[in] cca_thr The CCA energy detection threshold to set.
 * 
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_set_cca_energy_detect_threshold(int8_t cca_thr);

/**
 * @brief Enables or disables continuous reception mode.
 *
 * @param[in] enable True to enable, false to disable.
 */
void stm32wba_802154_ral_set_continuous_reception(bool aEnable);

/**
 * @brief Enables or disables implicit broadcast mode.
 *
 * @param[in] enable True to enable, false to disable.
 */
void stm32wba_802154_ral_set_implicitbroadcast(bool ImplicitBroadcast);

/**
 * @brief Resets the STM32WBA radio.
 *
 * This function performs a reset of the radio layer, restoring it to its default state.
 * It can be used to recover from unexpected states or errors.
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_radio_reset(void);

/**
 * @brief Generates random number.
 *
 * This function generates a random number using the specified parameters.
 *
 * @param[out] ptr_rnd Pointer to store the generated random number.
 * @param[in]  len    Length of the random number to generate.
 * @param[in]  check_cont_rx Indicates whether to check for continuous reception.
 * 
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_mac_gen_rnd_num(uint8_t *ptr_rnd, uint16_t len, uint8_t check_cont_rx);


/**
 *
 * @brief enable/disable antenna diversity
 *
 * @param[in]	enable	    : enable:1 / disable:0
 *
 * @returns  STM32WBA_802154_RAL_ERROR_NONE on success, or an error code on failure.
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_set_ant_div_enable(uint8_t enable);

/**
 *
 * @brief A wrapper function to set configurable library parameters
 *
 * @param[in]	support_openthread_1_2	    : support_openthread_1_2: true / false
 * @param[in]	mac_layer_build	            : mac_layer_build: true / false
 * @retval Error code
 */
stm32wba_802154_ral_error_t stm32wba_802154_ral_set_config_lib_params(bool support_openthread_1_2, bool mac_layer_build);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* STM32WBA_802154_H_ */

/** @} */
