/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    bleplat_cntr.c
  * @author  GPM WBL Application Team
  * @brief   This file provides implementation of BLE controller interface.
  *          WARNING: This module is used by Bluetooth LE stack. Do not use this
  *          module while Bluetooth LE stack is active.
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "stm32wb0x.h"
#include "bleplat_cntr.h"
#include <string.h>

/** @defgroup BLE_Platform_Controller  BLE Manager
* @{
*/

/** @defgroup BLE_Platform_Controller_TypesDefinitions Private Type Definitions
* @{
*/
/**
* @}
*/

/** @defgroup BLE_Platform_Controller_Private_Defines Private Defines
* @{
*/

#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
__disable_irq(); \
  /* Must be called in the same or in a lower scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)

#define MAX_PA_LEVEL    31
#define HP_PA_LEVEL     32 /* Fake PA level that can be reached in high power mode. */

#ifndef CONV_ADR
#define CONV_ADR(ADDR) ((uint8_t*)(ADDR))
#endif

#ifndef LL_PHY_CODED
#define LL_PHY_CODED 0x04U
#endif

#define ANY_HW_ERROR_INTERRUPT_Msk ( \
        BLUE_STATUSREG_ADDPOINTERROR_Msk      |  \
        BLUE_STATUSREG_RXOVERFLOWERROR_Msk    |  \
        BLUE_STATUSREG_TXERROR_0_Msk          |  \
        BLUE_STATUSREG_TXERROR_1_Msk          |  \
        BLUE_STATUSREG_TXERROR_2_Msk          |  \
        BLUE_STATUSREG_TXERROR_3_Msk          |  \
        BLUE_STATUSREG_TXERROR_4_Msk          |  \
        BLUE_STATUSREG_ALLTABLEREADYERROR_Msk | \
        BLUE_STATUSREG_TXDATAREADYERROR_Msk   | \
        BLUE_STATUSREG_NOACTIVELERROR_Msk     | \
        BLUE_STATUSREG_SEMATIMEOUTERROR_Msk   | \
        BLUE_STATUSREG_ACTIVE2ERROR_Msk       | \
        BLUE_STATUSREG_CONFIGERROR_Msk          \
        )

#define WAKEUPINITDELAY_MT                   (64U)
#define TIMER12_INIT_DELAY_CAL               (63U)
#define TIMER2_INIT_DELAY_NO_CAL              (9U)
#define RCV_LEN_MARGIN_US                    (16U)
#define TX_DELAY_START                       (16U)
#define TX_DELAY_END                         (16U)

#define RADIO_FSM_RX_DELAY_CAL               (90U)
#define RADIO_FSM_RX_DELAY_NO_CAL            (50U)
#define RADIO_FSM_TX_DELAY_CAL               (92U)
#define RADIO_FSM_TX_DELAY_NO_CAL            (52U)

#define RECEIVE_CAL_DELAY_CHECK              (RADIO_FSM_RX_DELAY_CAL)
#define RECEIVE_NO_CAL_DELAY_CHECK           (RADIO_FSM_RX_DELAY_NO_CAL)
#define TRANSMIT_CAL_DELAY_CHECK             (RADIO_FSM_TX_DELAY_CAL - 2U)
#define TRANSMIT_NO_CAL_DELAY_CHECK          (RADIO_FSM_TX_DELAY_NO_CAL - 2U)

#define CONFIG_END_DURATION                  (20U)
#define TX_DATA_READY_CHECK                   (5U)
#define TX_READY_TIMEOUT                      (4U)

#ifndef LL_PHY_CODED
#define LL_PHY_CODED 0x04U
#endif

#ifndef CONV_ADR
#define CONV_ADR(ADDR) ((uint8_t*)(ADDR))
#endif

#ifndef BLUE_TRANS_STRUCT_PTR_CAST
#define BLUE_TRANS_STRUCT_PTR_CAST(PTR) ((BlueTransStruct*)(void*)(uint8_t*)(PTR))
#endif

#define PHY_1MBPS          (0x0U)
#define PHY_2MBPS          (0x1U)
#define PHY_CODED_S2       (0x6U)
#define PHY_CODED_S8       (0x4U)

#define BIT_TX_SKIP (0x0UL)

/**
* @}
*/

/** @defgroup BLE_Platform_Controller_Private_Variables Private Variables
* @{
*/

/**
* @}
*/

/** @defgroup BLE_Platform_Controller_External_Variables External Variables
* @{
*/
/**
* @}
*/

/** @defgroup BLE_Platform_Controller_Private_FunctionPrototypes Private Function Prototypes
* @{
*/

/**
* @}
*/

/** @defgroup BLE_Platform_Controller_Private_Functions Private Functions
* @{
*/

/**
* @}
*/

/** @defgroup BLE_Platform_Controller_Public_Functions Public Functions
* @{
*/

BLEPLAT_CNTR_ResultStatus BLEPLAT_CNTR_Init(void)
{

  return BLEPLAT_CNTR_SUCCESS;
}

BLEPLAT_CNTR_ResultStatus BLEPLAT_CNTR_Deinit(void)
{

  return BLEPLAT_CNTR_SUCCESS;
}

/* Moved from the Stack library to the application environment
 *
 */
/* Calculate the Timeout to be programmed on Timer2 to obtain a give T_IFS
 * when the next packet is a transmit one
*/
uint32_t BLEPLAT_CNTR_GetTimer2TimeoutForIfs(uint32_t T_Ifs, BLEPLAT_CNTR_Transaction Transaction, uint8_t Cal_Enabled)
{
    uint32_t Timeout = T_Ifs;
    uint32_t Tx_Delay_Comp;
    uint32_t Init_Delay=0;

    if(Transaction == BLEPLAT_CNTR_RxTx)
    {
        /* The correction values below have been determined by sniffer
         * T_IFS measurements in connection, initiating and active
         * scanning
         */
#ifdef STM32WB05
        const int32_t Adjust_Value = 4;
#else
        const int32_t Adjust_Value = 6;
#endif
        Tx_Delay_Comp = (TX_DELAY_START>>3) + Adjust_Value;
    }
    else if(Transaction == BLEPLAT_CNTR_TxRx)
    {
        /* The correction values below have been set to correspond to the hardcoded
         * values used in prrevious versions of the stack.
         * They could be optimized after careful analysis of timing margins and
         * AGC behavior.
         */
#ifdef STM32WB05
        const int32_t Adjust_Value = 4;
#else
        const int32_t Adjust_Value = 4;
#endif
        Tx_Delay_Comp = (TX_DELAY_END>>3) + Adjust_Value;
    }
    else if(Transaction == BLEPLAT_CNTR_TxTx)
    {
        /* The correction values below have been determined by sniffer
         * T_IFS measurements in extended advertising (AUX_CHAIN_IND)
         */
#ifdef STM32WB05
        const int32_t Adjust_Value = 1;
#else
        const int32_t Adjust_Value = 2;
#endif
        Tx_Delay_Comp = ((TX_DELAY_START + TX_DELAY_END)>>3) + Adjust_Value;
    }
    else
    {
        Tx_Delay_Comp = 0;
    }

    if((Transaction == BLEPLAT_CNTR_RxTx) || (Transaction == BLEPLAT_CNTR_TxTx))
    {
        if(Cal_Enabled == TRUE)
        {
            Init_Delay = TIMER12_INIT_DELAY_CAL + RADIO_FSM_TX_DELAY_CAL;
        }
        else
        {
            Init_Delay = TIMER2_INIT_DELAY_NO_CAL + RADIO_FSM_TX_DELAY_NO_CAL;
        }
    }
    else if((Transaction == BLEPLAT_CNTR_TxRx) || (Transaction == BLEPLAT_CNTR_RxRx))
    {
        /* The calculation below is based on the following sequence:
         * - When Timer2 expires the sequencer performs the 1st initialization step and sends
         *   a take_req to the radio
         * - When TIMER12_INIT_DELAY_CAL or TIMER2_INIT_DELAY_NO_CAL expire the sequencer sends
         *   a tx_rx_req to the radio
         * - When the radio FSM reaches the RX state (after RADIO_FSM_RX_DELAY_CAL or
         *   RADIO_FSM_RX_DELAY_NO_CAL) the demodulator is turned on
         *
         * The sum of Timer2 timeout +  TIMER(1)2_INIT_DELAY(_NO)_CAL + RADIO_FSM_RX_DELAY(_NO)_CAL
         * must be equal to the T IFS.
         *
         * The current calculation of Timer2 for TX-RX events is slightly conservative
         * since it soes not consider the delay from digital modulator to antenna and from
         * antenna to digital demodulator. As a consequence the demodulator is turned on
         * a few microseconds earlier than stricty needed.
         */
        if(Cal_Enabled == TRUE)
        {
            Init_Delay = TIMER12_INIT_DELAY_CAL + RADIO_FSM_RX_DELAY_CAL;
        }
        else
        {
            Init_Delay = TIMER2_INIT_DELAY_NO_CAL + RADIO_FSM_RX_DELAY_NO_CAL;
        }
    }
    else
    {
    }

    Timeout -= (Init_Delay + Tx_Delay_Comp);

    return Timeout;
}

void BLEPLAT_CNTR_ClearInterrupt(uint32_t x)
{
    LL_RADIO_BlueSetInterrupt1RegRegister(x);
}

void BLEPLAT_CNTR_ClearSemareq(void)
{
    LL_RADIO_BlueSetClearSemaphoreRequest(0x1U);
}

void BLEPLAT_CNTR_TxRxSkip(void)
{
    LL_RADIO_BlueSetTxRxSkip(0x1U);
}

uint32_t* BLEPLAT_CNTR_GetCipherTextPtr()
{
    return (uint32_t*)&BLUE->MANAESCIPHERTEXT0REG;
}

uint32_t* BLEPLAT_CNTR_GetClrTextPtr()
{
    return (uint32_t*)&BLUE->MANAESCLEARTEXT0REG;
}

uint32_t* BLEPLAT_CNTR_GetEncKeyPtr()
{
    return (uint32_t*)&BLUE->MANAESKEY0REG;
}

uint8_t BLEPLAT_CNTR_GetEncryptDoneStatus()
{
    return (uint8_t)!LL_RADIO_BlueGetManAESStatusBusy();
}

uint8_t BLEPLAT_CNTR_GetIqsamplesMissingError(void)
{
#if defined(STM32WB09) || defined(STM32WB05)
  return (uint8_t)LL_RADIO_GetIQSamplesMissingError();
#elif defined(STM32WB06) || defined(STM32WB07)
  return (uint8_t)0;
#endif
}

uint8_t BLEPLAT_CNTR_GetIqsamplesNumber(void)
{
#if defined(STM32WB09) || defined(STM32WB05)
  return (uint8_t)LL_RADIO_GetIQSamplesNumber();
#elif defined(STM32WB06) || defined(STM32WB07)
  return (uint8_t)0;
#endif
}

uint8_t BLEPLAT_CNTR_getIqsamplesReady(void)
{
#if defined(STM32WB09) || defined(STM32WB05)
    return (uint8_t)LL_RADIO_GetIQSamplesReady();
#elif defined(STM32WB06) || defined(STM32WB07)
  return (uint8_t)0;
#endif
}

uint8_t BLEPLAT_CNTR_GetIsrLatency()
{
    return (uint8_t)LL_RADIO_BlueGetInterrupt1Latency();
}

uint32_t BLEPLAT_CNTR_GetTimercapture()
{
    return LL_RADIO_BlueGetTimerCapture();
}

void BLEPLAT_CNTR_GlobDisableBlue()
{
    LL_RADIO_GlobalDisableBlue();
}

void BLEPLAT_CNTR_GlobEnableBlue()
{
    LL_RADIO_GlobalEnableBlue();
}

void BLEPLAT_CNTR_GlobEnableIntnoactivelerrorInt()
{
   LL_RADIO_NoActiveLErrorInterrupt_Enable();
}

void BLEPLAT_CNTR_GlobEnableOverrunAct2Int()
{
    LL_RADIO_Active2ErrorInterrupt_Enable();
}

uint8_t BLEPLAT_CNTR_GlobGetDefaultAntennaid()
{
#if defined(GLOBAL_WORD6_DEFAULTANTENNAID_Msk)
    return (uint8_t)LL_RADIO_GetDefaultAntennaID();
#else
    return (uint8_t)0;
#endif
}

uint8_t BLEPLAT_CNTR_GlobGetWakeupinitdelay()
{
    return (uint8_t) LL_RADIO_GetWakeupInitDelay();
}

void BLEPLAT_CNTR_GlobReloadRadioConfigP()
{
    *(uint32_t*)(RRM_BASE + 0x10U) = 0x01U;
}

void BLEPLAT_CNTR_GlobSetChkflagautoclearena()
{
    LL_RADIO_ChkFlagAutoclearEnable_Enable();
}

void BLEPLAT_CNTR_GlobSetDefaultAntennaid(uint8_t x)
{
#if defined(GLOBAL_WORD6_DEFAULTANTENNAID_Msk)
    LL_RADIO_SetDefaultAntennaID((uint32_t)x);
#else
    /* nothing to do */
#endif
}

void BLEPLAT_CNTR_GlobSetInitRadioDelayTxCal(uint8_t x)
{
    LL_RADIO_SetTransmitCalDelayChk((uint32_t) x);
}

void BLEPLAT_CNTR_GlobSetInitRadioDelayTxNocal(uint8_t x)
{
    LL_RADIO_SetTransmitNoCalDelayChk((uint32_t) x);
}

void BLEPLAT_CNTR_GlobSetRadioConfigP(volatile uint32_t* x)
{
    LL_RADIO_SetRadioConfigurationAddressPointer(x[0]);
}

void BLEPLAT_CNTR_GlobSetWakeupinitdelay(uint8_t x)
{
    LL_RADIO_SetWakeupInitDelay((uint32_t) x);
}

void BLEPLAT_CNTR_GlobWriteConfigEnd(uint8_t x)
{
    LL_RADIO_SetConfigurationEndDuration((uint32_t) x);
}

void BLEPLAT_CNTR_GlobWritePeriodslow(uint16_t x)
{
    /* nothing to do */
}

void BLEPLAT_CNTR_GlobWriteRcvdelay(uint8_t x)
{
    LL_RADIO_SetReceivedCalDelayChk((uint32_t) x);
}

void BLEPLAT_CNTR_GlobWriteRcvdelay1(uint8_t x)
{
    LL_RADIO_SetReceivedNoCalDelayChk((uint32_t) x);
}

void BLEPLAT_CNTR_GlobWriteSlot(uint8_t slotNo)
{
    LL_RADIO_SetCurrentConnectionMachineNumber((uint32_t) slotNo);
}

void BLEPLAT_CNTR_GlobWriteTimer12initdelaycal(uint8_t x)
{
    LL_RADIO_SetTimer12InitDelayCal((uint32_t) x);
}

void BLEPLAT_CNTR_GlobWriteTimer2initdelaynocal(uint8_t x)
{
    LL_RADIO_SetTimer12InitDelayNoCal((uint32_t) x);
}

void BLEPLAT_CNTR_GlobWriteTxDataReadyCheck(uint8_t x)
{
    LL_RADIO_SetTxDataReadyCheck((uint32_t) x);
}

void BLEPLAT_CNTR_GlobWriteTxReadyTimeout(uint8_t x)
{
	LL_RADIO_SetTransmissionReadyTimeout((uint32_t) x);
}

void BLEPLAT_CNTR_GlobWriteTxdelay(uint8_t x)
{
    LL_RADIO_SetTxDelayStart((uint32_t) x);
}

void BLEPLAT_CNTR_GlobWriteTxdelayEnd(uint8_t x)
{
    LL_RADIO_SetTxDelayEnd((uint32_t) x);
}

uint32_t BLEPLAT_CNTR_IntGetIntStatusAnyHwError(uint32_t x)
{
    return (uint32_t)(x & ANY_HW_ERROR_INTERRUPT_Msk);
}

uint32_t BLEPLAT_CNTR_IntGetIntStatusRxOverflowError(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_RXOVERFLOWERROR_Msk);
}

uint32_t BLEPLAT_CNTR_IntGetIntStatusBitAct2Error(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_ACTIVE2ERROR_Msk);
}

uint32_t BLEPLAT_CNTR_IntGetIntStatusBitTimerOverrun(uint32_t x)
{
    return 0;
}

#if defined(BLUE_STATUSREG_RCVCRCERR_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusCrcErr(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_RCVCRCERR_Msk);
}
#endif

#if defined(BLUE_STATUSREG_DONE_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusDone(uint32_t x)
{
	return (uint32_t)(x & BLUE_STATUSREG_DONE_Msk);
}
#endif

#if defined(BLUE_STATUSREG_ENCERROR_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusEncErr(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_ENCERROR_Msk);
}
#endif

#if defined(BLUE_STATUSREG_RCVLENGTHERROR_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusLenErr(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_RCVLENGTHERROR_Msk);
}
#endif

#if defined(BLUE_STATUSREG_NOACTIVELERROR_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusNoactiveError(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_NOACTIVELERROR_Msk);
}
#endif

#if defined(BLUE_STATUSREG_TXRXSKIP_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusTxRxSkip(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_TXRXSKIP_Msk);
}
#endif

#if defined(BLUE_STATUSREG_TXERROR_1_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusTxError1(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_TXERROR_1_Msk);
}
#endif

#if defined(BLUE_STATUSREG_TXERROR_3_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusTxError3(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_TXERROR_3_Msk);
}
#endif

#if defined(BLUE_STATUSREG_RCVOK_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusRxOk(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_RCVOK_Msk);
}
#endif

#if defined(BLUE_STATUSREG_RCVTIMEOUT_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusTimeout(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_RCVTIMEOUT_Msk);
}
#endif

#if defined(BLUE_STATUSREG_TIMECAPTURETRIG_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusTrigRcv(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_TIMECAPTURETRIG_Msk);
}
#endif

#if defined(BLUE_STATUSREG_PREVTRANSMIT_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusTxDone(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_PREVTRANSMIT_Msk);
}
#endif

#if defined(BLUE_STATUSREG_TXOK_Msk)
uint32_t BLEPLAT_CNTR_IntGetIntStatusTxOk(uint32_t x)
{
    return (uint32_t)(x & BLUE_STATUSREG_TXOK_Msk);
}
#endif

void BLEPLAT_CNTR_PacketClrCrcinitSel(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetCRCInitializationSelector((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x0);
}

void BLEPLAT_CNTR_PacketClrCteSamplingEn(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetCTEAndSamplingEnable((TXRXPACK_TypeDef*)packetP, 0x0);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_PacketClrIncChan(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IncrementerChannel_Disable((TXRXPACK_TypeDef*)packetP);
}

void BLEPLAT_CNTR_PacketClrPllTrig(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetCalibrationRequest((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x0);
}

void BLEPLAT_CNTR_PacketDisableWhitening(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetDisableWhitening((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

uint8_t BLEPLAT_CNTR_PacketGetCteSamplingEn(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
#if defined(STM32WB05) || defined(STM32WB09)
  return (uint8_t)LL_RADIO_GetCTEAndSamplingEnable((TXRXPACK_TypeDef *)packetP);
#elif defined(STM32WB06) || defined(STM32WB07)
  return (uint8_t)0;
#endif

}

uint8_t* BLEPLAT_CNTR_PacketGetDataPtr(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    return (uint8_t*)CONV_ADR(LL_RADIO_GetDataPointer((TXRXPACK_TypeDef*)packetP));
}

void BLEPLAT_CNTR_PacketInitTo0(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    memset((void*)packetP, 0, sizeof(TXRXPACK_WORD_TypeDef));
}

void BLEPLAT_CNTR_PacketSetAdvPduFormat(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetAdvertise((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLEPLAT_CNTR_PacketSetCrcinitSel(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetCRCInitializationSelector((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLEPLAT_CNTR_PacketSetCteSamplingEn(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetCTEAndSamplingEnable((TXRXPACK_TypeDef*)packetP, 0x01);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_PacketSetDataPduFormat(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
     LL_RADIO_SetAdvertise((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x0);
}

void BLEPLAT_CNTR_PacketSetDataPtr(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP, void* dataP)
{
    LL_RADIO_SetDataPointer((TXRXPACK_TypeDef*)packetP, BLUE_DATA_PTR_CAST(dataP));
}

void BLEPLAT_CNTR_PacketSetIncChan(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IncrementerChannel_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLEPLAT_CNTR_PacketSetIntCrcErr(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IntRcvCRCErr_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLEPLAT_CNTR_PacketSetIntDone(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IntDone_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLEPLAT_CNTR_PacketSetIntRcvOk(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IntRcvOk_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLEPLAT_CNTR_PacketSetIntTimeout(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_IntRcvTimeout_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLEPLAT_CNTR_PacketSetIntTrigRcv(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
  LL_RADIO_SetIntTimeCapture((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1U);
}

void BLEPLAT_CNTR_PacketSetIntTxOk(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetIntTxOk((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLEPLAT_CNTR_PacketSetKeepsemareq(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetKeepSemaRequest((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLEPLAT_CNTR_PacketSetNextPtr(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP, BLEPLAT_CNTR_TXRXPACK_TypeDef* packetNextP)
{
    LL_RADIO_SetNextPointer((TXRXPACK_TypeDef*)packetP, (uint32_t) BLUE_STRUCT_PTR_CAST((TXRXPACK_TypeDef*)packetNextP));
}

void BLEPLAT_CNTR_PacketSetNextRxMode(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetNextTxMode((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x0);
}

void BLEPLAT_CNTR_PacketSetNextSlot(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP, uint8_t slot)
{
    /* nothing to do */
}

void BLEPLAT_CNTR_PacketSetNextTxMode(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetNextTxMode((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLEPLAT_CNTR_PacketSetNsEn(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_AutomaticSnNesnHardwareMechanism_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLEPLAT_CNTR_PacketSetPllTrig(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetCalibrationRequest((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLEPLAT_CNTR_PacketSetRxReady(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetAllTableDataReady((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLEPLAT_CNTR_PacketSetTimeout(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP, uint32_t x)
{
    LL_RADIO_SetTimer2Triggering((TXRXPACK_TypeDef*)packetP, x);
}

void BLEPLAT_CNTR_PacketSetTimer2Active(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_Timer2_Enable((TXRXPACK_TypeDef*)packetP);
}

void BLEPLAT_CNTR_PacketSetTimerTrigDone(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetTrigDone((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLEPLAT_CNTR_PacketSetTimerTrigRcv(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetTrigRcv((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLEPLAT_CNTR_PacketSetTxReady(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetTransmissionDataReady((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
    LL_RADIO_SetAllTableDataReady((TXRXPACK_TypeDef*)packetP, (uint32_t) 0x1);
}

void BLEPLAT_CNTR_SetRadioConfig(uint8_t* value)
{
    /* nothing to do */
}

void BLEPLAT_CNTR_SetRcvLen(BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP, uint32_t rcvLen)
{
  (void)packetP;
  LL_RADIO_SetReceiveWindowTimeout((uint32_t) (rcvLen & 0xFFFFFU));
}

void BLEPLAT_CNTR_SmCteOff(uint8_t smNo)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetCTEDisable(smNo, 0x01);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_SmCteOn(uint8_t smNo)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetCTEDisable(smNo, 0x00);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_SmEnRadioConfig(uint8_t smNo, uint32_t enable)
{
    if(enable)
	    LL_RADIO_RadioCommandList_Enable(smNo);
	else
	    LL_RADIO_RadioCommandList_Disable(smNo);
}

void BLEPLAT_CNTR_SmEncOff(uint8_t smNo)
{
    LL_RADIO_Encryption_Disable(smNo);
    LL_RADIO_ReceiveEncryptionErrorInterrupt_Disable(smNo);
}

void BLEPLAT_CNTR_SmEncOn(uint8_t smNo)
{
    LL_RADIO_Encryption_Enable(smNo);
    LL_RADIO_ReceiveEncryptionErrorInterrupt_Enable(smNo);
}

uint32_t BLEPLAT_CNTR_SmGetAccessAddr(uint8_t smNo)
{
    return LL_RADIO_GetAccessAddress(smNo);
}

void BLEPLAT_CNTR_SmGetChannelMap(uint8_t smNo, uint8_t* chanMap)
{
    chanMap[0] = (uint8_t)(LL_RADIO_GetUsedChannelFlags_15_0(smNo));
    chanMap[1] = (uint8_t)(LL_RADIO_GetUsedChannelFlags_15_0(smNo) >> 8U);
    chanMap[2] = (uint8_t)(LL_RADIO_GetUsedChannelFlags_36_16(smNo));
    chanMap[3] = (uint8_t)(LL_RADIO_GetUsedChannelFlags_36_16(smNo) >> 8U);
    chanMap[4] = (uint8_t)(LL_RADIO_GetUsedChannelFlags_36_16(smNo) >> 16U);
}

uint8_t BLEPLAT_CNTR_SmGetCteAntennaPatternLen(uint8_t smNo)
{
#if defined(STM32WB05) || defined(STM32WB09)
    return (uint8_t)LL_RADIO_GetAntennaPatternLength(smNo);
#elif defined(STM32WB06) || defined(STM32WB07)
  return (uint8_t)0;
#endif
}

uint8_t BLEPLAT_CNTR_SmGetCteAodNaoa(uint8_t smNo)
{
#if defined(STM32WB05) || defined(STM32WB09)
    return (uint8_t)LL_RADIO_GetAodNaoa(smNo);
#elif defined(STM32WB06) || defined(STM32WB07)
  return (uint8_t)0;
#endif
}

uint8_t BLEPLAT_CNTR_SmGetCteSlotWidth(uint8_t smNo)
{
#if defined(STM32WB05) || defined(STM32WB09)
  return (uint8_t)LL_RADIO_GetCTESlotWidth(smNo);
#elif defined(STM32WB06) || defined(STM32WB07)
  return (uint8_t)0;
#endif
}

uint8_t BLEPLAT_CNTR_SmGetCteStatus(uint8_t smNo)
{
#if defined(STM32WB05) || defined(STM32WB09)
    return (uint8_t)LL_RADIO_GetCTEDisable(smNo);
#elif defined(STM32WB06) || defined(STM32WB07)
  return (uint8_t)0;
#endif
}

uint8_t BLEPLAT_CNTR_SmGetCteTime(uint8_t smNo)
{
#if defined(STM32WB05) || defined(STM32WB09)
  return (uint8_t)LL_RADIO_GetCTETime(smNo);
#elif defined(STM32WB06) || defined(STM32WB07)
  return (uint8_t)0;
#endif
}

uint32_t* BLEPLAT_CNTR_SmGetEncIvPtr(uint8_t smNo)
{
    return (uint32_t*)&(bluedata + smNo)->ENCRYPTIV[0];
}

uint32_t* BLEPLAT_CNTR_SmGetEncKeyPtr(uint8_t smNo)
{
	return (uint32_t*)&(bluedata + smNo)->ENCRYPTK[0];
}

uint8_t BLEPLAT_CNTR_SmGetEncStatus(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_Encryption_IsEnabled(smNo);
}

uint8_t BLEPLAT_CNTR_SmGetHopIncr(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetHopIncrement(smNo);
}

uint8_t BLEPLAT_CNTR_SmGetMode(uint8_t smNo)
{
    return LL_RADIO_TxMode_IsEnabled(smNo);
}

uint8_t* BLEPLAT_CNTR_SmGetPrevRxPacketDataPtr(uint8_t smNo)
{
    return (uint8_t*)CONV_ADR(BLUE_TRANS_STRUCT_PTR_CAST(LL_RADIO_GetRcvPointPrevious(smNo))->DATAPTR);
}

BLEPLAT_CNTR_TXRXPACK_TypeDef* BLEPLAT_CNTR_SmGetPrevRxPacketPtr(uint8_t smNo)
{
    return (BLEPLAT_CNTR_TXRXPACK_TypeDef*)BLUE_TRANS_STRUCT_PTR_CAST(CONV_ADR(LL_RADIO_GetRcvPointPrevious(smNo)));
}

uint8_t* BLEPLAT_CNTR_SmGetPrevTxPacketDataPtr(uint8_t smNo)
{
    return (uint8_t*)CONV_ADR(BLUE_TRANS_STRUCT_PTR_CAST(LL_RADIO_GetTxPointPrevious(smNo))->DATAPTR);
}

BLEPLAT_CNTR_TXRXPACK_TypeDef* BLEPLAT_CNTR_SmGetPrevTxPacketPtr(uint8_t smNo)
{
    return (BLEPLAT_CNTR_TXRXPACK_TypeDef*)BLUE_TRANS_STRUCT_PTR_CAST(CONV_ADR(LL_RADIO_GetTxPointPrevious(smNo)));
}

uint8_t BLEPLAT_CNTR_SmGetRemapChan(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetRemapChannel(smNo);
}

void BLEPLAT_CNTR_SmGetRxCount(uint8_t smNo, uint32_t* packetCount)
{

    packetCount[0] = LL_RADIO_GetPacketCounterRx_23_0(smNo);
    packetCount[0] = packetCount[0] | ((uint32_t)LL_RADIO_GetPacketCounterRx_39_24(smNo) << 24U);
    packetCount[1] = LL_RADIO_GetPacketCounterRx_39_24(smNo) >> 8U;
}

uint8_t BLEPLAT_CNTR_SmGetRxPhy(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetReceptionPhy(smNo);
}

BLEPLAT_CNTR_TXRXPACK_TypeDef* BLEPLAT_CNTR_SmGetTxPacketPtr(uint8_t smNo)
{
    return (BLEPLAT_CNTR_TXRXPACK_TypeDef*)BLUE_TRANS_STRUCT_PTR_CAST(CONV_ADR(LL_RADIO_GetTxPoint(smNo)));
}

uint8_t BLEPLAT_CNTR_SmGetTxPhy(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetTransmissionPhy(smNo);
}

uint8_t BLEPLAT_CNTR_SmGetTxPwr(uint8_t smNo)
{
    uint8_t pa_level = LL_RADIO_GetPAPower(smNo);

#if defined(STM32WB09)
    if (LL_RADIO_TxHp_IsEnabled(smNo) && (pa_level == MAX_PA_LEVEL))
    {
        pa_level = HP_PA_LEVEL;
    }
#endif
    return pa_level;
}

uint8_t BLEPLAT_CNTR_SmGetUnmappedChan(uint8_t smNo)
{
    return (uint8_t)LL_RADIO_GetUnmappedChannel(smNo);
}

void BLEPLAT_CNTR_SmInitTo0(uint8_t smNo)
{
  memset((void*)&bluedata[smNo], 0, sizeof(STATMACH_TypeDef));
  BLEPLAT_CNTR_SmEnRadioConfig(smNo, 0x01);
}

void BLEPLAT_CNTR_SmSetAccessAddr(uint8_t smNo, uint32_t x)
{
    LL_RADIO_SetAccessAddress(smNo, x);
}

void BLEPLAT_CNTR_SmSetChannelMap(uint8_t smNo, uint8_t* chanMap)
{
    uint32_t value = (uint32_t)chanMap[0] | ((uint32_t)chanMap[1] << 8U);
    LL_RADIO_SetUsedChannelFlags_15_0(smNo, value);
    value = (uint32_t)chanMap[2] | ((uint32_t)chanMap[3] << 8U) | ((uint32_t)chanMap[4] << 16U);
    LL_RADIO_SetUsedChannelFlags_36_16(smNo, value);
}

void BLEPLAT_CNTR_SmSetCrcInit(uint8_t smNo, uint32_t x)
{
  LL_RADIO_SetCRCInitializationValue(smNo, x);
}

void BLEPLAT_CNTR_SmSetCteAntennaPatternLen(uint8_t smNo, uint8_t antPattLen)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetAntennaPatternLength(smNo, (uint32_t) antPattLen);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

uint32_t BLEPLAT_CNTR_SmGetCteAntennaPatternPtr(uint8_t smNo)
{
#if defined(STM32WB05) || defined(STM32WB09)
  return LL_RADIO_GetAntennaPatternPtr(smNo);
#elif defined(STM32WB06) || defined(STM32WB07)
  return 0x00UL;
#endif
}

void BLEPLAT_CNTR_SmSetCteAntennaPatternPtr(uint8_t smNo, uint8_t* antPattP)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetAntennaPatternPtr(smNo, (uint32_t)(uintptr_t)antPattP);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_SmSetCteAoa(uint8_t smNo)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetAodNaoa(smNo, 0x0);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_SmSetCteAod(uint8_t smNo)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetAodNaoa(smNo, 0x01);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_SmSetCteIqsamplesPtr(uint8_t smNo, uint32_t* iqSamplesP)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetIQSamplesPtr(smNo, (uint32_t)(uintptr_t)iqSamplesP);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_SmSetCteMaxIqsamplesNumb(uint8_t smNo, uint8_t iqsamplesNumb)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetMaximumIQSamplesNumber(smNo, (uint32_t) iqsamplesNumb);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_SmSetCteSlotWidth(uint8_t smNo, uint32_t cteSlot)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetCTESlotWidth(smNo, cteSlot);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_SmSetCteTime(uint8_t smNo, uint8_t cteTime)
{
#if defined(STM32WB05) || defined(STM32WB09)
  LL_RADIO_SetCTETime(smNo, (uint32_t) cteTime);
#elif defined(STM32WB06) || defined(STM32WB07)
  /* nothing to do */
#endif
}

void BLEPLAT_CNTR_SmSetDataLength(uint8_t smNo, uint8_t length)
{
    LL_RADIO_SetMaximumReceiveLength(smNo, (uint32_t) length);
}

void BLEPLAT_CNTR_SmSetDataLengthExtnEn(uint8_t smNo)
{
    /* nothing to do */
}

void BLEPLAT_CNTR_SmSetHopIncr(uint8_t smNo, uint8_t x)
{
    LL_RADIO_SetHopIncrement(smNo, (uint32_t) x);
}

void BLEPLAT_CNTR_SmSetRemapChan(uint8_t smNo, uint8_t chan)
{
    LL_RADIO_SetRemapChannel(smNo, chan);
}

void BLEPLAT_CNTR_SmSetRxCount(uint8_t smNo, uint32_t* packetCount)
{
    LL_RADIO_SetPacketCounterRx_23_0(smNo, (uint32_t) packetCount[0]);
    uint32_t value = (uint32_t)(packetCount[1] << 8U) | (uint32_t)(packetCount[0] >> 24U);
    LL_RADIO_SetPacketCounterRx_39_24(smNo, value);
}

void BLEPLAT_CNTR_SmSetRxCountDirectionBit(uint8_t smNo)
{
    uint32_t value = LL_RADIO_GetPacketCounterRx_39_24(smNo) | 0x8000U;
    LL_RADIO_SetPacketCounterRx_39_24(smNo, value);
}

void BLEPLAT_CNTR_SmSetRxMode(uint8_t smNo)
{
    LL_RADIO_TxMode_Disable(smNo);
}

void BLEPLAT_CNTR_SmSetRxPacketPtr(uint8_t smNo, BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetRcvPoint(smNo, (uint32_t) BLUE_STRUCT_PTR_CAST((TXRXPACK_TypeDef*)packetP));
}

void BLEPLAT_CNTR_SmSetRxPhy(uint8_t smNo, uint8_t rxPhy)
{
    LL_RADIO_SetReceptionPhy(smNo, (uint32_t) rxPhy);
}

void BLEPLAT_CNTR_SmSetTxCount(uint8_t smNo, uint32_t* packetCount)
{
    LL_RADIO_SetPacketCounterTx_31_0(smNo, (uint32_t) packetCount[0]);
    LL_RADIO_SetPacketCounterTx_39_32(smNo, (uint32_t) packetCount[1]);
}

void BLEPLAT_CNTR_SmSetTxCountDirectionBit(uint8_t smNo)
{
    uint32_t value =  (LL_RADIO_GetPacketCounterTx_39_32(smNo) | 0x00000080U);
    LL_RADIO_SetPacketCounterTx_39_32(smNo,  value);
}

void BLEPLAT_CNTR_SmSetTxMode(uint8_t smNo)
{
    LL_RADIO_TxMode_Enable(smNo);
}

void BLEPLAT_CNTR_SmSetTxPacketPtr(uint8_t smNo, BLEPLAT_CNTR_TXRXPACK_TypeDef* packetP)
{
    LL_RADIO_SetTxPoint(smNo, (uint32_t) BLUE_STRUCT_PTR_CAST((TXRXPACK_TypeDef*)packetP));
}

void BLEPLAT_CNTR_SmSetTxPhy(uint8_t smNo, uint8_t txPhy)
{
    LL_RADIO_SetTransmissionPhy(smNo, (uint32_t) txPhy);
}

void BLEPLAT_CNTR_SmEnTxHp(uint8_t smNo, uint8_t enable)
{
#if defined(STM32WB09)
  if(enable)
  {
    LL_RADIO_TxHp_Enable(smNo);
  }
  else
  {
    LL_RADIO_TxHp_Disable(smNo);
  }
#endif
}

/* Consider PA Level 32 the one used to enable high power. */
void BLEPLAT_CNTR_SmSetTxPwr(uint8_t smNo, uint8_t paLevel)
{
#if defined(STM32WB09)
  if(paLevel == HP_PA_LEVEL)
  {
    LL_RADIO_TxHp_Enable(smNo);
    paLevel = MAX_PA_LEVEL;
  }
  else
  {
    LL_RADIO_TxHp_Disable(smNo);
  }
#endif

  LL_RADIO_SetPAPower(smNo, (uint32_t) paLevel);
}

void BLEPLAT_CNTR_SmSetUnmappedChan(uint8_t smNo, uint8_t chan)
{
    LL_RADIO_SetUnmappedChannel(smNo, (uint32_t) chan);
}

void BLEPLAT_CNTR_SmToggleNesn(uint8_t smNo)
{
  LL_RADIO_ToggleNextExpectedSequenceNumber(smNo);
}

void BLEPLAT_CNTR_SmToggleSn(uint8_t smNo)
{
    LL_RADIO_ToggleSequenceNumber(smNo);
}

void BLEPLAT_CNTR_StartEncrypt()
{
     LL_RADIO_BlueSetManAESCmdStart(0x1U);
}

uint32_t BLEPLAT_CNTR_TimeDiff(uint32_t x, uint32_t y)
{
    return (uint32_t)(x - y);
}

uint8_t BLEPLAT_CNTR_DemodDelaySt(uint8_t RxPHY)
{
    return (uint8_t)((LL_PHY_CODED == RxPHY) ? 0x9DU : 0x12U);
}

/**
* @}
*/

/**
* @}
*/
