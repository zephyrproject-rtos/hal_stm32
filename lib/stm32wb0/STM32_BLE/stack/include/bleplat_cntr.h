/**
  ******************************************************************************
  * @file    bleplat_cntr.h
  * @author  GPM WBL Application team
  * @brief   This file contains the interface of the Bluetooth LE platform layer
  *          (lower interface of the Bluetooth LE stack library).
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef BLEPLAT_CNTR_H__
#define BLEPLAT_CNTR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup BLEPLAT_CNTR_Peripheral  BLE CONTROLLER
 * @{
 */

/** @defgroup BLEPLAT_CNTR_Exported_Types Exported Types
 * @{
 */


/* Enumerated values used to report the RNG result status after a process */
typedef enum
{
  BLEPLAT_CNTR_SUCCESS     =  0,
  BLEPLAT_CNTR_ERROR,
  BLEPLAT_CNTR_ERROR_TIMEOUT
} BLEPLAT_CNTR_ResultStatus;


typedef struct {
    volatile uint32_t WORD0;
    volatile uint32_t WORD1;
    volatile uint32_t WORD2;
    volatile uint32_t WORD3;
    volatile uint32_t WORD4;
} BLEPLAT_CNTR_TXRXPACK_TypeDef;

typedef enum
{
    BLEPLAT_CNTR_TxRx = 0,
    BLEPLAT_CNTR_RxTx,
    BLEPLAT_CNTR_TxTx,
    BLEPLAT_CNTR_RxRx
} BLEPLAT_CNTR_Transaction;
/**
 * @}
 */

/** @defgroup BLEPLAT_CNTR_Exported_Constants  Exported Constants
 * @{
 */

/**
 * @}
 */

/** @defgroup BLEPLAT_CNTR_Exported_Macros           Exported Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup BLEPLAT_CNTR_Exported_Functions        Exported Functions
 * @{
 */
BLEPLAT_CNTR_ResultStatus BLEPLAT_CNTR_Init(void);

BLEPLAT_CNTR_ResultStatus BLEPLAT_CNTR_Deinit(void);

void BLEPLAT_CNTR_ClearInterrupt(uint32_t x);
void BLEPLAT_CNTR_ClearSemareq(void);
void BLEPLAT_CNTR_TxRxSkip(void);
uint32_t* BLEPLAT_CNTR_GetCipherTextPtr(void);
uint32_t* BLEPLAT_CNTR_GetClrTextPtr(void);
uint32_t* BLEPLAT_CNTR_GetEncKeyPtr(void);
uint8_t BLEPLAT_CNTR_GetEncryptDoneStatus(void);
uint8_t BLEPLAT_CNTR_GetIqsamplesMissingError(void);
uint8_t BLEPLAT_CNTR_GetIqsamplesNumber(void);
uint8_t BLEPLAT_CNTR_getIqsamplesReady(void);
uint8_t BLEPLAT_CNTR_GetIsrLatency(void);
uint32_t BLEPLAT_CNTR_GetTimercapture(void);
void BLEPLAT_CNTR_GlobDisableBlue(void);
void BLEPLAT_CNTR_GlobEnableBlue(void);
void BLEPLAT_CNTR_GlobEnableIntnoactivelerrorInt(void);
void BLEPLAT_CNTR_GlobEnableTxRxSkipInt(void);
void BLEPLAT_CNTR_GlobEnableOverrunAct2Int(void);
uint8_t BLEPLAT_CNTR_GlobGetDefaultAntennaid(void);
uint8_t BLEPLAT_CNTR_GlobGetWakeupinitdelay(void);
void BLEPLAT_CNTR_GlobReloadRadioConfigP(void);
void BLEPLAT_CNTR_GlobSetChkflagautoclearena(void);
void BLEPLAT_CNTR_GlobSetDefaultAntennaid(uint8_t x);
void BLEPLAT_CNTR_GlobSetInitRadioDelayTxCal(uint8_t x);
void BLEPLAT_CNTR_GlobSetInitRadioDelayTxNocal(uint8_t x);
void BLEPLAT_CNTR_GlobSetRadioConfigP(volatile uint32_t* x);
void BLEPLAT_CNTR_GlobSetWakeupinitdelay(uint8_t x);
void BLEPLAT_CNTR_GlobWriteConfigEnd(uint8_t x);
void BLEPLAT_CNTR_GlobWritePeriodslow(uint16_t x);
void BLEPLAT_CNTR_GlobWriteRcvdelay(uint8_t x);
void BLEPLAT_CNTR_GlobWriteRcvdelay1(uint8_t x);
void BLEPLAT_CNTR_GlobWriteSlot(uint8_t slotNo);
void BLEPLAT_CNTR_GlobWriteTimer12initdelaycal(uint8_t x);
void BLEPLAT_CNTR_GlobWriteTimer2initdelaynocal(uint8_t x);
void BLEPLAT_CNTR_GlobWriteTxDataReadyCheck(uint8_t x);
void BLEPLAT_CNTR_GlobWriteTxReadyTimeout(uint8_t x);
void BLEPLAT_CNTR_GlobWriteTxdelay(uint8_t x) ;
void BLEPLAT_CNTR_GlobWriteTxdelayEnd(uint8_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusAnyHwError(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusRxOverflowError(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusBitAct2Error(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusBitTimerOverrun(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusCrcErr(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusDone(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusEncErr(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusLenErr(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusNoactiveError(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusRxOk(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusTimeout(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusTrigRcv(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusTxDone(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusTxOk(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusTxRxSkip(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusTxError1(uint32_t x);
uint32_t BLEPLAT_CNTR_IntGetIntStatusTxError3(uint32_t x);
void BLEPLAT_CNTR_PacketClrCrcinitSel(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketClrCteSamplingEn(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketClrIncChan(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketClrPllTrig(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketDisableWhitening(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
uint8_t BLEPLAT_CNTR_PacketGetCteSamplingEn(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
uint8_t* BLEPLAT_CNTR_PacketGetDataPtr(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketInitTo0(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetAdvPduFormat(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetCrcinitSel(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetCteSamplingEn(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetDataPduFormat(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetDataPtr(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP, void* dataP);
void BLEPLAT_CNTR_PacketSetIncChan(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetIntCrcErr(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetIntDone(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetIntRcvOk(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetIntTimeout(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetIntTrigRcv(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetIntTxOk(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetKeepsemareq(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetNextPtr(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP, BLEPLAT_CNTR_TXRXPACK_TypeDef* packetNextP);
void BLEPLAT_CNTR_PacketSetNextRxMode(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetNextSlot(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP, uint8_t slot);
void BLEPLAT_CNTR_PacketSetNextTxMode(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetNsEn(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetPllTrig(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetRxReady(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetTimeout(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP, uint32_t x);
void BLEPLAT_CNTR_PacketSetTimer2Active(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetTimerTrigDone(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetTimerTrigRcv(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_PacketSetTxReady(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_SetRadioConfig(uint8_t* value);
void BLEPLAT_CNTR_SetRcvLen(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP, uint32_t rcvLen);
void BLEPLAT_CNTR_SmCteOff(uint8_t smNo);
void BLEPLAT_CNTR_SmCteOn(uint8_t smNo);
void BLEPLAT_CNTR_SmEnRadioConfig(uint8_t smNo, uint32_t enable);
void BLEPLAT_CNTR_SmEncOff(uint8_t smNo);
void BLEPLAT_CNTR_SmEncOn(uint8_t smNo);
uint32_t BLEPLAT_CNTR_SmGetAccessAddr(uint8_t smNo);
void BLEPLAT_CNTR_SmGetChannelMap(uint8_t smNo, uint8_t* chanMap);
uint8_t BLEPLAT_CNTR_SmGetCteAntennaPatternLen(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetCteAodNaoa(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetCteSlotWidth(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetCteStatus(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetCteTime(uint8_t smNo);
uint32_t* BLEPLAT_CNTR_SmGetEncIvPtr(uint8_t smNo);
uint32_t* BLEPLAT_CNTR_SmGetEncKeyPtr(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetEncStatus(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetHopIncr(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetMode(uint8_t smNo);
uint8_t* BLEPLAT_CNTR_SmGetPrevRxPacketDataPtr(uint8_t smNo);
BLEPLAT_CNTR_TXRXPACK_TypeDef* BLEPLAT_CNTR_SmGetPrevRxPacketPtr(uint8_t smNo) ;
uint8_t* BLEPLAT_CNTR_SmGetPrevTxPacketDataPtr(uint8_t smNo);
BLEPLAT_CNTR_TXRXPACK_TypeDef* BLEPLAT_CNTR_SmGetPrevTxPacketPtr(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetRemapChan(uint8_t smNo);
void BLEPLAT_CNTR_SmGetRxCount(uint8_t smNo, uint32_t* packetCount);
uint8_t BLEPLAT_CNTR_SmGetRxPhy(uint8_t smNo);
BLEPLAT_CNTR_TXRXPACK_TypeDef* BLEPLAT_CNTR_SmGetTxPacketPtr(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetTxPhy(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetTxPwr(uint8_t smNo);
uint8_t BLEPLAT_CNTR_SmGetUnmappedChan(uint8_t smNo);
void BLEPLAT_CNTR_SmInitTo0(uint8_t smNo);
void BLEPLAT_CNTR_SmSetAccessAddr(uint8_t smNo, uint32_t x);
void BLEPLAT_CNTR_SmSetChannelMap(uint8_t smNo, uint8_t* chanMap);
void BLEPLAT_CNTR_SmSetCrcInit(uint8_t smNo, uint32_t x);
void BLEPLAT_CNTR_SmSetCteAntennaPatternLen(uint8_t smNo, uint8_t antPattLen);
void BLEPLAT_CNTR_SmSetCteAntennaPatternPtr(uint8_t smNo, uint8_t* antPattP);
uint32_t BLEPLAT_CNTR_SmGetCteAntennaPatternPtr(uint8_t smNo);
void BLEPLAT_CNTR_SmSetCteAoa(uint8_t smNo);
void BLEPLAT_CNTR_SmSetCteAod(uint8_t smNo);
void BLEPLAT_CNTR_SmSetCteIqsamplesPtr(uint8_t smNo, uint32_t* iqSamplesP);
void BLEPLAT_CNTR_SmSetCteMaxIqsamplesNumb(uint8_t smNo, uint8_t iqsamplesNumb);
void BLEPLAT_CNTR_SmSetCteSlotWidth(uint8_t smNo, uint32_t cteSlot);
void BLEPLAT_CNTR_SmSetCteTime(uint8_t smNo, uint8_t cteTime);
void BLEPLAT_CNTR_SmSetDataLength(uint8_t smNo, uint8_t length);
void BLEPLAT_CNTR_SmSetDataLengthExtnEn(uint8_t smNo);
void BLEPLAT_CNTR_SmSetHopIncr(uint8_t smNo, uint8_t x);
void BLEPLAT_CNTR_SmSetRemapChan(uint8_t smNo, uint8_t chan);
void BLEPLAT_CNTR_SmSetRxCount(uint8_t smNo, uint32_t* packetCount);
void BLEPLAT_CNTR_SmSetRxCountDirectionBit(uint8_t smNo);
void BLEPLAT_CNTR_SmSetRxMode(uint8_t smNo);
void BLEPLAT_CNTR_SmSetRxPacketPtr(uint8_t smNo, BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_SmSetRxPhy(uint8_t smNo, uint8_t rxPhy);
void BLEPLAT_CNTR_SmSetTxCount(uint8_t smNo, uint32_t* packetCount);
void BLEPLAT_CNTR_SmSetTxCountDirectionBit(uint8_t smNo);
void BLEPLAT_CNTR_SmSetTxMode(uint8_t smNo);
void BLEPLAT_CNTR_SmSetTxPacketPtr(uint8_t smNo, BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP);
void BLEPLAT_CNTR_SmSetTxPhy(uint8_t smNo, uint8_t txPhy);
void BLEPLAT_CNTR_SmEnTxHp(uint8_t smNo, uint8_t enable);
void BLEPLAT_CNTR_SmSetTxPwr(uint8_t smNo, uint8_t paLevel);
void BLEPLAT_CNTR_SmSetUnmappedChan(uint8_t smNo, uint8_t chan);
void BLEPLAT_CNTR_SmToggleNesn(uint8_t smNo);
void BLEPLAT_CNTR_SmToggleSn(uint8_t smNo);
void BLEPLAT_CNTR_StartEncrypt(void);
uint32_t BLEPLAT_CNTR_TimeDiff(uint32_t x, uint32_t y);
uint8_t BLEPLAT_CNTR_DemodDelaySt(uint8_t RxPHY);
uint32_t BLEPLAT_CNTR_GetTimer2TimeoutForIfs(uint32_t T_Ifs, BLEPLAT_CNTR_Transaction Transaction, uint8_t Cal_Enabled);


/**
  * @}
  */


/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* ! BLEPLAT_H__ */
