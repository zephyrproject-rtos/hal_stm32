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

/**@file st_802154_ral_callbacks.h
 * @brief Provides function prototypes required by ST 802.15.4 Radio
 *
 * Functions whose prototypes are defined in this file are to be implemented
 * by an application using the ST 802.15.4 Radio.
 */

#ifndef ST_802154_RAL_CALLBACKS_H_
#define ST_802154_RAL_CALLBACKS_H_

#include <stdint.h>
#include <stdbool.h>

#include "st_802154_ral.h"

/**
 * @struct st_802154_ral_cbk_dispatch_tbl
 *
 * @brief structure of all callback functions used to notify upper layer of specific event start/completion
 */
struct st_802154_ral_cbk_dispatch_tbl{
	/**
	 * @brief  callback function called after the end of energy detection operation
	 *
	 * @param  a_rssi_result: The result for ED operation which is RSSI value
	 *
	 * @retval none
	 */
	void (*st_802154_ral_cbk_ed_scan_done)(int8_t a_rssi_result);
	
	/**
	 * @brief callback function called after the end of transmission operation
	 *
	 * @param  a_frame_ptr:	    Pointer to the transmitted frame.
	 * @param  a_error:	        Transmission error status of type st_802154_ral_error_t.
	 *              	        Indicates whether the transmission was successful or if an error occurred.
	 * @param  a_meta_data_ptr: Pointer to metadata of type st_802154_ral_transmit_done_metadata_t,
	 *                          containing additional information about the transmission.
	 *
	 * @retval none
	 */
	void (*st_802154_ral_cbk_tx_done)(uint8_t* a_frame_ptr, st_802154_ral_error_t a_error, const st_802154_ral_transmit_done_metadata_t* a_meta_data_ptr);
	
	/**
	 * @brief  callback function called after the end of reception operation
	 *
	 * @param  a_buffer_ptr:    Pointer to the buffer containing the received data.
	 * @param  a_meta_data_ptr: Pointer to the metadata associated with the received frame.
	 *
	 * @retval none
	 */
	void (*st_802154_ral_cbk_rx_done)(uint8_t* a_buffer_ptr, st_802154_ral_receive_done_metadata_t* a_meta_data_ptr);

	/**
	 * @brief  callback function notifies that the CCA procedure has finished.
	 *
	 * @param  a_error: If failed, reason of the failure.
	 *
	 * @retval none
	 */
	void (*st_802154_ral_cbk_cca_done)(uint8_t  a_error);
	
	/**
	 * @brief  callback function notifies about the start of the ACK frame transmission.
	 *
	 * @param  a_ack_fpb: Frame pending bit in the ACK frame.
	 * @param  a_ack_seb: Security enabled bit in the ACK frame.
	 *
	 * @retval none
	 */
	void (*st_802154_ral_cbk_tx_ack_started)(bool a_ack_fpb, bool a_ack_seb);

	/**
	 * @brief  callback function notifies about the start of the frame transmission.
	 *
	 * @retval none
	 */
	void (*st_802154_ral_cbk_tx_started)(uint64_t a_Timestamp);
};


/**
 * @brief  This function is called from upper layer init function to register the upper layer callback functions
 *
 * @param  a_cbk_dispatch_tbl_ptr: pointer to callback functions to be registered
 *
 * @retval none
 *
 */
void st_802154_ral_call_back_funcs_init(struct st_802154_ral_cbk_dispatch_tbl* a_cbk_dispatch_tbl_ptr);


#endif /* STM32WBA_802154_CALLBACKS_H_ */

/** @} */
