/*$Id: //dwh/bluetooth/DWC_ble154combo/firmware/rel/2.00a-lca04/firmware/public_inc/dtm.h#1 $*/
/**
 ********************************************************************************
 * @file    dtm.h
 * @brief   header file for  Synopsys zigbee phy testing APIs
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

#ifndef MAC_CONTROLLER_INC_DTM_H_
#define MAC_CONTROLLER_INC_DTM_H_

/********************************************************************************************
 *  								Includes
 *********************************************************************************************/

#include "ral.h"

/*=========================================== MACROS ======================================*/
#define aMaxSIFSFrameSize           18      ///< Maximum SIFS frame size in bytes
#define macMinSIFSPeriod            192     ///< Minimum SIFS period in microseconds
#define macMinLIFSPeriod            640     ///< Minimum LIFS period in microseconds
#define MAX_PHY_PACKET_SIZE         127     ///< Maximum PHY packet size in bytes
#define MAX_ERROR_PER_SINGLE_TX     5       ///< Maximum error types per single TX
/*============================= Enumerations ================================*/
/**
 * @brief  Enum represents the current DTM State.
 *
 */
typedef enum z_dtm_mode {
	Z_DTM_STOPPED = 0,
	Z_DTM_TX = 1,
	Z_DTM_RX = 2,
	Z_DTM_TX_ACK = 3,
	Z_DTM_CHECK_TX_ERROR = 4
} z_dtm_mode_e;

/*============================= Structures ================================*/
/**
 * @brief  Structure represents the current state of DTM TX.
 *
 */
typedef struct Tx_Info
{
    uint16_t TxTotal;    ///< Total number of transmitted frames (with/without errors)
    uint16_t NoErr;      ///< Number of frames transmitted successfully
    uint16_t ErrNoAck;   ///< Number of frames requesting ACK and no ACK received after transmission
    uint16_t ErrOther;   ///< Number of frames transmitted with errors excluding no ACK error
} TxInfo_s;

/**
 * @brief Structure represents the current state of DTM RX.
 *
 */
typedef struct Rx_Info
{
    uint16_t RxTotal;    ///< Total number of received frames (with/without errors)
    uint16_t NoErr;      ///< Number of frames successfully received
    uint16_t ErrFcs;     ///< Number of frames received with invalid FCS
    uint16_t ErrOther;   ///< Number of frames received with errors excluding invalid FCS error
    uint8_t  lqi;        ///< LQI of the received frame
} RxInfo_s;

/**
 * @brief Structure represents all information related to DTM.
 *
 */
typedef struct dtmInfo_st
{
    z_dtm_mode_e curr_mode;  ///< Current State (TX, RX, Stopped)
	/**
	 * @brief Union represents DTM TX/RX information.
	 *
	 */
    union{
        TxInfo_s TxInfo;     ///< DTM information in case of TX and TX_ACK
        RxInfo_s RxInfo;     ///< DTM information in case of RX
    } tx_rx_info_u;
} dtmInfo_t;

/** @ingroup  mac_dtm
*  @{
*/
/*=========================================== API  ============================================*/
/**
 * @brief  Initialize or reset DTM, or stop the current running DTM.
 *
 */
void dtmReset(void);

/**
 * @brief  Get the state of DTM (running or stopped).
 *
 * @return TRUE if DTM is running, FALSE if DTM is stopped.
 */
uint8_t dtmIsEnabled(void);

/**
 * @brief  Start continuous DTM transmission with the given input parameters until the dtmStop() API is called.
 *
 * @param[in]  mPsdu     : Pointer to MAC DTM frame including MAC header.
 * @param[in]  mLength   : Length of the frame to be transmitted.
 * @param[in]  mChannel  : Channel to transmit the frame on.
 * @param[in]  IFS       : Interframe spacing in us.
 * @return MAC error state of starting transmission.
 */
mac_status_enum_t dtmStartTransmit(uint8_t * mPsdu, uint8_t mLength, uint8_t mChannel, uint16_t IFS);

/**
 * @brief  Start transmission of a single DTM frame that is requesting ACK with the given input parameters.
 *
 * @param[in]  mPsdu     : Pointer to MAC DTM frame including MAC header.
 * @param[in]  mLength   : Length of the frame to be transmitted.
 * @param[in]  mChannel  : Channel to transmit the frame on.
 * @param[in]  IFS       : Interframe spacing in us.
 * @return MAC error state of starting transmission.
 */
mac_status_enum_t dtmStartTransmitwithAck(uint8_t * mPsdu, uint8_t mLength, uint8_t mChannel, uint16_t IFS);
/**
 * @brief  Stop the current running DTM (TX or RX).
 *
 * @param[out] num_rec_pckts : Pointer to number of received packets.
 * @param[out] lqi           : Pointer to average LQI.
 * @return MAC error state of stopping DTM.
 */
mac_status_enum_t dtmStop(uint16_t *num_rec_pckts, uint8_t *lqi);

/**
 * @brief  Start continuous DTM reception on the given channel.
 *
 * @param[in]  aChannel : Channel to receive on.
 * @return MAC error state of starting reception.
 */
mac_status_enum_t dtmStartReceive(uint8_t aChannel);

/**
 * @brief  Start CCA on the given channel.
 *
 * @param[in]  channel : Channel to perform CCA on.
 * @return MAC error state of performing CCA.
 */
mac_status_enum_t dtmPerformCCA(uint8_t channel);


/**
 * @brief  Get the current LQI of the last received packet.
 *
 * @return LQI value.
 */
uint8_t dtmGetLQIValue(void);

/**
 * @brief  get the current RSSI of the last received packet
 * @retval int8_t. RSSI value
 */
int8_t dtmGetRSSIValue(void);

/**
 * @}
 */
/**
 * @brief  Check if there are more DTM frames to transmit.
 *
 * @return TRUE to continue DTM transmission, FALSE to stop DTM transmission.
 */
uint8_t dtmCheckMoreTx(void);

/**
 * @brief  Check if DTM is in reception state.
 *
 * @return TRUE if DTM is in reception mode, FALSE otherwise.
 */
uint8_t dtmCheckRxState(void);

/**
 * @brief  Done function called after each DTM event.
 *
 * @param[in] aFrame : Pointer to MAC transmitted/received frame.
 * @param[in] aError : Status error of overall transmission (success, No_ack, and other errors).
 */
void dtmRadioDone(otRadioFrame *aFrame, otError aError);

/**
 * @brief  Check if in Z_DTM_CHECK_TX_ERROR transmission mode or not.
 *
 * @return TRUE if in Z_DTM_CHECK_TX_ERROR transmission mode, FALSE otherwise.
 */
uint8_t dtmCheckTxErrorState(void);
/**
 * @brief  Count errors that happen in single TX in Z_DTM_CHECK_TX_ERROR transmission mode.
 *
 * @param[in] tx_error : Type of error to be counted for this trial.
 */
void dtmCheckTxErrorCount(otError tx_error);
/**
 * @brief  Gives stored errors and their count that happen in single TX in Z_DTM_CHECK_TX_ERROR transmission mode.
 *
 * @param[out] errors      : Pointer to array of stored errors in Z_DTM_CHECK_TX_ERROR transmission mode.
 * @param[out] error_count : Pointer to number of errors stored in errors array.
 */
void dtmTxCheckErrorCountDone(uint8_t ** errors, uint8_t *error_count);
/**
 * @brief  Start transmission in Z_DTM_CHECK_TX_ERROR transmission mode.
 *
 * @param[in]  mac_hndl           : MAC instance handle.
 * @param[in]  mPsdu              : Pointer to TX packet.
 * @param[in]  mLength            : Length of TX packet.
 * @param[in]  mChannel           : Channel that packet will be sent on.
 * @param[in]  IFS                : Used inter-frame-spacing.
 * @param[in]  csma_en            : Flag to indicate to apply CSMA in this transmission if max_csma_retry_count != 0.
 * @param[in]  backoff_count_max  : Maximum number of TX trials in every full CSMA trial.
 * @param[in]  frame_retry        : Maximum number of trials after failure not related to CCA failure.
 * @param[in]  ack_req            : Indicate if this packet requires ACK or not.
 * @return Status.
 */
mac_status_enum_t dtmTxSpecificErrorCount(uint32_t mac_hndl, uint8_t * mPsdu, uint8_t mLength, uint8_t mChannel, uint16_t IFS,
		uint8_t csma_en, uint8_t backoff_count_max, uint8_t frame_retry, uint8_t ack_req);

/**
 * @brief  Reset tx_check_err_arr array and its counter for Z_DTM_CHECK_TX_ERROR mode.
 *
 */
void dtmTxErrorCountReset(void);

#endif /* MAC_CONTROLLER_INC_DTM_H_ */
