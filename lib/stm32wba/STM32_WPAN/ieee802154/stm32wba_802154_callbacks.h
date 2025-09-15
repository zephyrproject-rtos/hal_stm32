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

/**@file stm32wba_802154_callbacks.h
 * @brief Provides function prototypes required by STM32WBA 802.15.4 Radio Driver
 *
 * Functions whose prototypes are defined in this file are to be implemented
 * by an application using the STM32WBA 802.15.4 Radio Driver.
 */

#ifndef STM32WBA_802154_CALLBACKS_H_
#define STM32WBA_802154_CALLBACKS_H_

#include <stdint.h>
#include <stdbool.h>

#include "stm32wba_802154.h"

/**
 * @struct stm32wba_802154_ral_cbk_dispatch_tbl
 *
 * @brief structure of all callback functions used to notify 802.15.4 Zephyr driver after specific event compeletion
 */
struct stm32wba_802154_ral_cbk_dispatch_tbl{
	/**
	 * @brief  callback function called after the end of Energy detection operation
	 *
	 * @param  rssiResult	The result for ED operation which is RSSI value
	 *
	 * @retval none
	 */
	void (*stm32wba_802154_ral_cbk_ed_scan_done)(int8_t rssiResult);
	
	/**
	 * @brief  callback function called after the end of transmission operation
	 *
	 * @param p_frame	Pointer to the transmitted frame.
	 * @param error		Transmission error status of type stm32wba_802154_tx_error_t.
	 *              	 Indicates whether the transmission was successful or if an
	 *              	 error occurred.
	 * @param p_metadata 	Pointer to metadata of type stm32wba_802154_transmit_done_metadata_t, 
	 * 			 containing additional information about the transmission.
	 *
	 * @retval none
	 */
	void (*stm32wba_802154_ral_cbk_tx_done)(uint8_t * p_frame, stm32wba_802154_ral_tx_error_t error, const stm32wba_802154_ral_transmit_done_metadata_t *p_metadata);
	
	/**
	 * @brief  callback function called after the end of Reception operation
	 *
	 * @param p_buffer	Pointer to the buffer containing the received data.
	 * @param p_metadata 	Pointer to the metadata associated with the received frame.
	 *
	 * @retval none
	 */
	void (*stm32wba_802154_ral_cbk_rx_done)(uint8_t * p_buffer, stm32wba_802154_ral_receive_done_metadata_t *p_metadata);

	/**
	 * @brief callback function notifies that the CCA procedure has finished.
	 *
	 * @param[in]  error	If failed, reason of the failure.
	 *
	 * @retval none
	 */
	void (*stm32wba_802154_ral_cbk_cca_done)(uint8_t error);
	
	/**
	 * @brief callback function notifies about the start of the ACK frame transmission.
	 *
	 * @param[in]  ack_fpb	Frame pending bit in the ACK frame.
	 * @param[in]  ack_seb	Security enabled bit in the ACK frame.
	 *
	 * @retval none
	 */
	void (*stm32wba_802154_ral_cbk_tx_ack_started)(bool ack_fpb, bool ack_seb);
};


/**
 * @brief  This function called from upper layer init function (mac_init in case of mac integration e.g. Zigbee stack)
 * 		   to register the upper layer callback functions
 *
 * @param  ptr_cbk_dispatch_tbl		pointer to callback function to be registered
 *
 * @retval none
 *
 */
void stm32wba_802154_ral_call_back_funcs_init(struct stm32wba_802154_ral_cbk_dispatch_tbl * ptr_cbk_dispatch_tbl);


#endif /* STM32WBA_802154_CALLBACKS_H_ */

/** @} */

