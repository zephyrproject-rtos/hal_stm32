/**
  ******************************************************************************
  * @file    st_radio.h
  * @author  802.15.4 Team
  * @brief   Defines the radio interface required by the ST 802.15.4 MAC
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************/

#ifndef ST_RADIO_H_
#define ST_RADIO_H_

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


#define ST_RADIO_POWER_INVALID     127
#define ST_RADIO_IE_HEADER_SIZE    2  ///< Size of IE header in bytes.


/**
 * @brief StRadioError - Error codes expected from radio 
 */
typedef enum
{
    ST_RADIO_ERROR_NONE                         = 0,   // !< No error.
    ST_RADIO_ERROR_FAILED                       = -1,  // !< Operation failed.
    ST_RADIO_ERROR_DROP                         = -2,  // !< Message was dropped.
    ST_RADIO_ERROR_NO_BUFS                      = -3,  // !< Insufficient buffers.
    ST_RADIO_ERROR_BUSY                         = -4,  // !< Service is busy and could not service the operation.
    ST_RADIO_ERROR_INVALID_ARGS                 = -5,  // !< Input arguments are invalid.
    ST_RADIO_ERROR_SECURITY                     = -6,  // !< Security checks failed.
	ST_RADIO_ERROR_NO_ADDRESS                   = -7,  // !< Address is not in the source match table.
	ST_RADIO_ERROR_ABORT                        = -8,  // !< Operation was aborted.
	ST_RADIO_ERROR_NOT_IMPLEMENTED              = -9,  // !< Function or method is not implemented.
	ST_RADIO_ERROR_INVALID_STATE                = -10, // !< Cannot complete due to invalid state.
	ST_RADIO_ERROR_NO_ACK                       = -11, // !< No acknowledgment was received after macMaxFrameRetries (IEEE 802.15.4-2006).
	ST_RADIO_ERROR_CHANNEL_ACCESS_FAILURE       = -12, // !< A transmission could not take place due to activity on the channel, i.e., the CSMA-CA mechanism has failed (IEEE 802.15.4-2006).
	ST_RADIO_ERROR_FCS                          = -13, // !< FCS check failure while receiving.
	ST_RADIO_ERROR_NO_FRAME_RECEIVED            = -14, // !< No frame received.
	ST_RADIO_ERROR_INVALID_SOURCE_ADDRESS       = -15, // !< Received a frame from an invalid source address.
	ST_RADIO_ERROR_DESTINATION_ADDRESS_FILTERED = -16, // !< Received a frame filtered by the destination address check.
	ST_RADIO_ERROR_NOT_FOUND                    = -17, // !< The requested item could not be found.
	ST_RADIO_ERROR_GENERIC                      = -18, // !< Generic error.
	ST_RADIO_ERROR_UNKNOWN                      = -255 // !< Unknown error.
} StRadioError;


typedef enum
{
    ST_RADIO_STATE_DISABLED = 0,
    ST_RADIO_STATE_SLEEP    = 1,
    ST_RADIO_STATE_RECEIVE  = 2,
    ST_RADIO_STATE_TRANSMIT = 3,
} StRadioState;

/**
 * Represents an IEEE 802.15.4 radio frame.
 */
typedef struct 
{
    uint8_t* mPsduPtr; ///< The PSDU.
    uint16_t mLength;  ///< Length of the PSDU.
    uint8_t  mChannel; ///< Channel used to transmit/receive the frame.

    /**
     * The union of transmit and receive information for a radio frame.
     */
    union
    {
        /**
         * Structure representing radio frame transmit information.
         */
        struct
        {

            /**
             * Maximum number of CSMA backoff attempts before declaring channel access failure.
             *
             *
             * This field MUST be ignored if `mCsmaCaEnabled` is set to `false` (CCA is disabled) 
             *
             * It can be set to `0` to skip backoff mechanism (note that CCA MUST still be performed assuming
             * `mCsmaCaEnabled` is `true`).
             */
            uint8_t mMaxCsmaBackoffs;

            uint8_t mMaxFrameRetries; ///< Maximum number of retries allowed after a transmission failure.

            /**
             * The RX channel after frame TX is done (after all frame retries - ack received, or timeout, or abort).
             */
            uint8_t mRxChannelAfterTxDone;

            /**
             * The transmit power in dBm.
             * If the value is ST_RADIO_POWER_INVALID, then the platform should ignore this value and transmit the frame
             * with its default transmit power.
             */
            int8_t mTxPower;

            bool mIsARetx; ///< Indicates whether the frame is a retransmission or not.
            /**
             * Set to true to enable CSMA-CA for this packet, false to disable both CSMA backoff and CCA.
             *
             * When it is set to `false`, the frame MUST be sent without performing CCA. In this case `mMaxCsmaBackoffs`
             * MUST also be ignored.
             */
            bool mCsmaCaEnabled;
        } mTxInfo;

        /**
         * Structure representing radio frame receive information.
         */
        struct
        {
            /**
             * The time of the local radio clock in microseconds when the end of
             * the SFD was present at the local antenna.
             */
            uint64_t mTimestamp;
            int8_t   mRssi;            ///< Received signal strength indicator in dBm for received frames.
            uint8_t  mLqi;             ///< Link Quality Indicator for received frames.

            // Flags
            bool mAckedWithFramePending : 1; ///< This indicates if this frame was acknowledged with frame pending set.
        } mRxInfo;
    } mInfo;
} StRadioFrame_t;


/**
 * @brief Structure defines all callback functions used to notify ST MAC layer after specific event compeletion
 *
 */
typedef struct
{
	/**
	 * @brief  Energy detection scan done callback
	 *
	 * @param[in] aEnergyScanMaxRssi: The result for ED operation which is RSSI value
	 */
	void (*st_mac_ed_scan_done)(int8_t aEnergyScanMaxRssi);
	/**
	 * @brief  Transmission done callback
	 *
	 * @param[in] aFramePtr	    : Pointer to the transmitted frame
	 * @param[in] aAckFramePtr	: Pointer to the received ACK frame (in case of AR bit is detected in aFrame)
	 * @param[in] aError	    : Error code if happens in transmission
	 */
	void (*st_mac_tx_done)(StRadioFrame_t* aFramePtr, StRadioFrame_t* aAckFramePtr, StRadioError aError);
	/**
	 * @brief  Reception done callback
	 *
	 * @param[in] aFramePtr	: Pointer to the received frame
	 * @param[in] aError	: Error code if happens in transmission
	 */
	void (*st_mac_rx_done)(StRadioFrame_t* aFramePtr, StRadioError aError);
	/**
	 * @brief  The start of successful transmission callback
	 *
	 * @param[in] aFramePtr	: Pointer to the transmitted frame
	 * @param[in] aError	: Error code if happens in transmission
	 */
	void (*st_mac_tx_strtd)(StRadioFrame_t* aFramePtr);
}StMacCbkDispatchTbl_t;


/**
 * @brief  Initialize radio layer 
 *
 */
void StRadioInit(void);


/**
 * @brief  Register MAC callback functions.
 *
 * @param[in] aMacCbkDispatchTblPtr : Pointer to callback functions to be registered
 */
void StRadioCallbackFuncsInit(StMacCbkDispatchTbl_t* aMacCbkDispatchTblPtr);


/**
 * @brief Reset radio layer operation which in turns stop all running operations
 * 
 * @return ST_RADIO_ERROR_NONE on success, failure otherwise 
 */
StRadioError StRadioReset(void);


/**
 * Gets the factory-assigned IEEE EUI-64 for this interface.
 *
 * @param[out] aIeeeEui64Ptr  A pointer to the factory-assigned IEEE EUI-64.
 */
void StRadioGetIeeeEui64(uint8_t* aIeeeEui64Ptr);


/**
 * Set the PAN ID for address filtering.
 *
 * @param[in] aPanId     The IEEE 802.15.4 PAN ID.
 */
void StRadioSetPanId(uint16_t aPanId);


/**
 * Set the Extended Address for address filtering.
 *
 * @param[in] aExtAddressPtr  A pointer to the IEEE 802.15.4 Extended Address stored in little-endian byte order.
 */
void StRadioSetExtendedAddress(const uint8_t* aExtAddressPtr);


/**
 * Set the Short Address for address filtering.
 *
 * @param[in] aShortAddress  The IEEE 802.15.4 Short Address.
 */
void StRadioSetShortAddress(uint16_t aShortAddress);


/**
 * Get Radio State.
 *
 *  @retval Radio state.
 */
StRadioState StRadioGetState(void);


/**
 * @brief Set PAN coordinator role in HW to be used while applying MAC 802.15.4 filtration policies
 * 
 * @param[in] aEnable : PAN coordinator role flag (TRUE to enable, FALSE to disable)
 */
void StRadioSetPanCoordinator(bool aEnable);


/**
 * @brief Request continuous reception from radio driver when idle
 * 
 * @param[in] aEnable : Continuous reception state (TRUE to enable, FALSE to disable)
 */
void StRadioSetContinuousReception(bool aEnable);


 /* @brief  Get the latest LQI value
 * 
 * @retval LQI value
 */
uint8_t StRadioGetLqiValue(void);


/**
 * Get the radio's transmit power in dBm.
 *
 * @param[out] aPowerPtr    The transmit power in dBm.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise 
 */
StRadioError StRadioGetTransmitPower(int8_t* aPowerPtr);


/**
 * Set the radio's transmit power in dBm for all channels.
 *
 * @param[in] aPower     The transmit power in dBm.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise 

 */
StRadioError StRadioSetTransmitPower(int8_t aPower);


/**
 * Get the radio's CCA ED threshold in dBm measured at antenna connector per IEEE 802.15.4 - 2015 section 10.1.4.
 *
 * @param[out] aThresholdPtr  The CCA ED threshold in dBm.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise 

 */
StRadioError StRadioGetCcaEnergyDetectThreshold(int8_t* aThresholdPtr);


/**
 * Set the radio's CCA ED threshold in dBm measured at antenna connector per IEEE 802.15.4 - 2015 section 10.1.4.
 *
 * @param[in] aThreshold  The CCA ED threshold in dBm.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise 

 */
StRadioError StRadioSetCcaEnergyDetectThreshold(int8_t aThreshold);


/**
 * @brief Set minimum CSMA backoff exponent
 * 
 * @param[in] aValue : Minimum csma backoff exponent
 */
void StRadioSetMinCsmaBe(uint8_t  aValue);
/**
 * @brief Set maximum CSMA backoff exponent
 * 
 * @param[in] aValue : Maximum CSMA backoff exponent
 */
void StRadioSetMaxCsmaBe(uint8_t aValue);
/**
 * @brief Set maximum CSMA backoff counter
 * 
 * @param[in] aValue : Maximum CSMA backoff counter
 */
void StRadioSetMaxCsmaBackoff(uint8_t aValue);
/**
 * @brief Set custom maximum full CSMA frame retries
 * 
 * @param[in] aValue : Maximum full CSMA retrials
 */
void StRadioSetMaxFullCsmaFrmRetries(uint8_t aValue);


/**
 * @brief Set maximum frame retries
 * 
 * @param[in] aValue : Maximum frame retries
 */
void StRadioSetMaxFrmRetries(uint8_t aValue);

/**
 * Begin the energy scan sequence on the radio.
 *
 * @param[in] aScanChannel   The channel to perform the energy scan on.
 * @param[in] aScanDuration  The duration, in milliseconds, for the channel to be scanned.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioEnergyScan(uint8_t aScanChannel, uint16_t aScanDuration);

/**
 * Get the status of promiscuous mode.
 *
 * @param         none
 *
 * @retval TRUE   Promiscuous mode is enabled.
 * @retval FALSE  Promiscuous mode is disabled.
 */
bool StRadioGetPromiscuous(void);

/**
 * Enable or disable promiscuous mode.
 *
 * @param[in]  aEnable   TRUE to enable or FALSE to disable promiscuous mode.
 */
void StRadioSetPromiscuous(bool aEnable);


/**
 * Transition the radio from Sleep to Receive (turn on the radio).
 *
 * @param[in]  aChannel   The channel to use for receiving.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise 

 */
StRadioError StRadioReceive(uint8_t aChannel);


/**
 * Begin the transmit sequence on the radio.
 *
 * The caller must form the IEEE 802.15.4 frame in the buffer provided by `StRadioGetTransmitBuffer()` before
 * requesting transmission.  The channel and transmit power are also included in the StRadioFrame structure.
 *

 * @param[in] aFramePtr     A pointer to the frame to be transmitted.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise 
 */
StRadioError StRadioTransmit(StRadioFrame_t* aFramePtr);


/**
 * Transition the radio to Sleep (turn off the radio).
 *
 * @param  none
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioSleep(void);


/**
 * Get the most recent RSSI measurement.
 *
 * @param[in] none
 *
 * @returns The RSSI in dBm when it is valid.  127 when RSSI is invalid.
 */
int8_t StRadioGetRssi(void);


/**
 * Enable/Disable source address match feature.
 *
 * The source address match feature controls how the radio layer decides the "frame pending" bit for acks sent in
 * response to data request commands from children.
 *
 * If disabled, the radio layer must set the "frame pending" on all acks to data request commands.
 *
 * If enabled, the radio layer uses the source address match table to determine whether to set or clear the "frame
 * pending" bit in an ack to a data request command.
 *
 * The source address match table provides the list of children for which there is a pending frame. Either a short
 * address or an extended/long address can be added to the source address match table.
 *
 * @param[in]  aEnable     Enable/disable source address match feature.
 */
void StRadioEnableSrcMatch(bool aEnable);


/**
 * Add a short address to the source address match table.
 *
 * @param[in]  aShortAddress  The short address to be added.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise 
 */
StRadioError StRadioAddSrcMatchShortEntry(uint16_t aShortAddress);


/**
 * Add an extended address to the source address match table.
 *
 * @param[in]  aExtAddressPtr  The extended address to be added stored in little-endian byte order.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioAddSrcMatchExtEntry(uint8_t* aExtAddressPtr);


/**
 * Remove a short address from the source address match table.
 *
 * @param[in]  aShortAddress  The short address to be removed.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioClearSrcMatchShortEntry(uint16_t aShortAddress);


/**
 * Remove an extended address from the source address match table.
 *
 * @param[in]  aExtAddressPtr  The extended address to be removed stored in little-endian byte order.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioClearSrcMatchExtEntry(uint8_t* aExtAddressPtr);


/**
 * Clear all short addresses from the source address match table.
 *
 * @param[in]  none
 */
void StRadioClearSrcMatchShortEntries(void);


/**
 * Clear all the extended/long addresses from source address match table.
 *
 * @param[in]  none
 */
void StRadioClearSrcMatchExtEntries(void);


/**
 * @brief Generate random number
 *
 * @param[out] aRndPtr		: Pointer to the output random bytes
 * @param[in]  aLength	    : Number of required random bytes
 * @param[in]  aCheckContRx : Flag to check continuous reception
 *
 * @return ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioGenRndNum(uint8_t* aRndPtr, uint16_t aLength, bool aCheckContRx);


/**
 * @brief Set the PHY continuous modulation and continuous wave modes upon enable
 *
 * @param[in] aType			: The type of the modulation (0: modulation, 1: wave)
 * @param[in] aEnableMode	: TRUE to enable the selected mode, FALSE to disable it
 * @param[in] aChannel		: Channel number to be used in modulation (range: 0 to 15)
 * @param[in] aPwr         	: The used power in dBm.
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioZigbeeSetPhyContModulMode(uint8_t aType, uint8_t aEnableMode, uint8_t aChannel, int8_t aPwr);


/**
 * @brief   Set MAC implicit broadcast PIB from MAC layer to be used in filtration
 *
 * @param[in] ImplicitBroadcast: Value for MAC implicit broadcast PIB to be set
 */
void StRadioSetImplicitBroadcast(uint8_t aImplicitBroadcast);

/**
 * @brief   Set CSMA enable flag
 *
 * @param[in] csma_en : Value for CSMA enable flag to be set
 */
void StRadioSetCsmaEnable(uint8_t aCsmaEnable);


/**
 * @brief	Get CSMA enable flag
 *
 * @retval CSMA enable flag
 */
uint8_t StRadioGetCsmaEnable(void);

/**
 * @brief   Set CCA enable flag
 *
 * @param[in] cca_en : Value for CCA enable flag to be set
 */
void StRadioSetCcaEnable(uint8_t aCcaEnable);


/**
 * @brief   Get CCA enable flag
 *
 * @retval CCA enable flag .
 */
uint8_t StRadioGetCcaEnable(void);

/**
 * @brief Set antenna diversity feature parameters
 *
 * @param[in] aAntDivParamsPtr: Pointer to antenna diversity feature parameters
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioSetAntDivParams(antenna_diversity_st* aAntDivParamsPtr);


/**
 * @brief Get antenna diversity feature parameters
 *
 * @param[out] aAntDivParamsPtr	: Pointer to antenna diversity feature parameters
 */
void StRadioGetAntDivParams(antenna_diversity_st* aAntDivParamsPtr);


/**
 * @brief Set antenna diversity feature state
 *
 * @param[in] aEnable	: Antenna diversity feature state (TRUE to enable, FALSE to disable)
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioSetAntDivEnable(bool aEnable);


/**
 * @brief Set the default antenna ID of the antenna diversity feature to be used for transmission and reception
 *
 * @param[in] aDefaultAntId	: Default antenna ID
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioSetDefaultAntId(uint8_t aDefaultAntId);


/**
 * @brief Set the RSSI threshold for antenna diversity feature
 *
 * @param[in] aRssiThreshold RSSI threshold to compare with during antenna diversity measurements'
 *
 * @retval ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioSetAntDivRssiThreshold(int8_t aRssiThreshold);


/**
 * @brief Set configurable library feature parameters
 *
 * @param[in]	aSupportOpenthread  : support_openthread_1_2: true / false
 * @param[in]	aMacLayerBuild	    : mac_layer_build: true / false
 * @param[in]   aAckAllReceivedFramesWithArBitSet
 *
 * @retval      ST_RADIO_ERROR_NONE on success, failure otherwise
 */
StRadioError StRadioSetConfigLibParams(bool aSupportOpenthread, 
                                       bool aMacLayerBuild, 
									   bool aAckAllReceivedFramesWithArBitSet);


/**
 * @brief Get current configurable library parameters
 *
 * @param[out]	aSupportOpenthreadPtr  : support_openthread_1_2: true / false
 * @param[out]	aMacLayerBuildPtr	   : mac_layer_build: true / false
 * @param[out]  aAckAllReceivedFramesWithArBitSetPtr
 */
void StRadioGetConfigLibParams(bool* aSupportOpenthreadPtr, 
                               bool* aMacLayerBuildPtr, 
							   bool* aAckAllReceivedFramesWithArBitSetPtr);
							   
/**
 * @brief Set RTL polling time
 *
 * @param[in] aRtlPollingTime: RTL polling time value
 */
void StRadioSetRtlPollingTime(uint8_t aRtlPollingTime);


/**
 * @brief Get current RTL polling time
 *
 * @retval Current RTL polling time
 */
uint8_t StRadioGetRtlPollingTime(void);							   


#ifdef __cplusplus
} // end of extern "C"
#endif

#endif // ST_RADIO_H_
