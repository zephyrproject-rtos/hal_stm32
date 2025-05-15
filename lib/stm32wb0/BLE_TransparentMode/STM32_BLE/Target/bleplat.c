/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ble_plat.c
  * @author  GPM WBL Application Team
  * @brief   Bluetooth LE stack v3.x platform interface for pka, rng, aes,
  *          radio timer, controller.
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
#include "bleplat.h"
#include "pka_manager.h"
#include "hw_aes.h"
#include "hw_rng.h"
#if (BLESTACK_CONTROLLER_ONLY == 0)
#include "crypto.h"
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */
#include "miscutil.h"
#include "RADIO_utils.h"
#include "osal.h"
#include "stm32wb0x.h"
#include "stm32wb0x_ll_radio.h"

#define PLL_ADC_CALIB_CORR  2
#define CP_ISEL_Msk         (0x07UL)
#define SYNTH0_ANA_ENG      (*(volatile uint32_t *)0x60001610)
#define SYNTHCAL3_ANA_TST   (*(volatile uint32_t *)0x600015A4)
#define LL_DUMMY_ACCESS_ADDRESS (0x00000000U)
#define LL_DTM_ACCESS_ADDRESS   (0x71764129U)

#if defined(STM32WB06) || defined(STM32WB07) || defined(STM32WB09)
uint32_t SYNTH0_ANA_ENG_bak, PWR_ENGTRIM_bak;
#endif

void BLEPLAT_MemCpy(void *Dest, const void *Src, unsigned int Size)
{
  Osal_MemCpy(Dest, Src, Size);
}

void BLEPLAT_MemSet(void *Ptr, int Value, unsigned int Size)
{
  memset(Ptr, Value, Size);
}

int BLEPLAT_MemCmp(void *S1, void *S2, unsigned int Size)
{
  return memcmp(S1, S2, Size);
}

/**
 * @brief Get Device ID, Version and Revision numbers
 */
void BLEPLAT_GetPartInfo(uint8_t *pDeviceId, uint8_t *pMajorCut, uint8_t *pMinorCut)
{
   PartInfoType partInfo;

   /* get partInfo */
   GetPartInfo(&partInfo);

  /* Set device ID */
  *pDeviceId  = partInfo.die_id;

  /* Set major cut  */
  *pMajorCut = partInfo.die_major;

  /* Set minor cut */
  *pMinorCut = partInfo.die_cut;
}

BLEPLAT_PkaStatusTypeDef BLEPLAT_PkaStartP256Key(const uint32_t *private_key, BLEPLAT_PkaFuncCb funcCb)
{
  return (BLEPLAT_PkaStatusTypeDef)PKAMGR_StartP256PublicKeyGeneration(private_key, (PKAMGR_funcCB)funcCb);
}

BLEPLAT_PkaStatusTypeDef BLEPLAT_PkaStartDHkey(uint32_t* private_key,
                                         uint32_t* public_key,
                                         BLEPLAT_PkaFuncCb funcCb)
{
  return (BLEPLAT_PkaStatusTypeDef)HW_PKA_StartP256DHkeyGeneration(private_key, public_key, (PKAMGR_funcCB)funcCb);
}

void BLEPLAT_AesEcbEncrypt(const uint32_t *plainTextData,
                           const uint32_t *key,
                           uint32_t *encryptedData)
{
  HW_AES_Encrypt(plainTextData, key, encryptedData);
}
#if (BLESTACK_CONTROLLER_ONLY == 0)
int32_t BLEPLAT_AesCMACEncryptInit(BLEPLAT_AESCMACctxTypeDef *pAESCMACctx)
{
  return AES_CMAC_Encrypt_Init((AESCMACctx_stt*)pAESCMACctx);
}

int32_t BLEPLAT_AesCMACEncryptAppend(BLEPLAT_AESCMACctxTypeDef *pAESCMACctx,
                                     const uint8_t  *pInputBuffer,
                                     int32_t InputSize)
{
  return AES_CMAC_Encrypt_Append((AESCMACctx_stt*)pAESCMACctx, pInputBuffer, InputSize);
}

int32_t BLEPLAT_AesCMACEncryptFinish(BLEPLAT_AESCMACctxTypeDef *pAESCMACctx,
                                     uint8_t *pOutputBuffer,
                                     int32_t *pOutputSize)
{
  return AES_CMAC_Encrypt_Finish((AESCMACctx_stt*)pAESCMACctx, pOutputBuffer, pOutputSize);
}
#endif /* (BLESTACK_CONTROLLER_ONLY == 0) */

uint8_t BLEPLAT_DBmToPALevel(int8_t TX_dBm)
{
  return RADIO_DBmToPALevel(TX_dBm);
}

uint8_t BLEPLAT_DBmToPALevelGe(int8_t TX_dBm)
{
  return RADIO_DBmToPALevelGe(TX_dBm);
}

int8_t BLEPLAT_PALevelToDBm(uint8_t PA_Level)
{
  return RADIO_PALevelToDBm(PA_Level);
}

void BLEPLAT_ReadTransmitPower(int8_t *Min_Tx_Power, int8_t *Max_Tx_Power)
{
  RADIO_ReadTransmitPower(Min_Tx_Power, Max_Tx_Power);
}

uint8_t BLEPLAT_GetMaxPALevel(void)
{
  return RADIO_GetMaxPALevel();
}

uint8_t BLEPLAT_GetDefaultPALevel(void)
{
  return RADIO_GetDefaultPALevel();
}

void BLEPLAT_SetHighPower(uint8_t enable)
{
  RADIO_SetHighPower((FunctionalState)enable);
}

int8_t BLEPLAT_CalculateRSSI(void)
{
  return HAL_RADIO_ReadRSSI();
}

int8_t BLEPLAT_UpdateAvgRSSI(int8_t avg_rssi, int8_t rssi, uint8_t rssi_filter_coeff)
{
  return RADIO_UpdateAvgRSSI(avg_rssi, rssi, rssi_filter_coeff);
}

uint8_t BLEPLAT_GetDemodCI(void)
{
  return GetDemodCI();
}

void BLEPLAT_InitCTE(uint8_t smNo)
{
#if defined(STM32WB06) || defined(STM32WB07) || defined(STM32WB09)
  SYNTH0_ANA_ENG_bak = SYNTH0_ANA_ENG;
  PWR_ENGTRIM_bak = PWR->ENGTRIM;

  SYNTHCAL3_ANA_TST = 0;
  // Set RFD_PLL_CP_ISEL = 0 in RRM->SYNTH0_ANA_ENG
  SYNTH0_ANA_ENG &= ~CP_ISEL_Msk;
  PWR->ENGTRIM = 0x00000001;

  /* First packet does not have the fix, so it needs to be discarded. Set an
     invalid Access Address. */
  LL_RADIO_SetAccessAddress(smNo, LL_DUMMY_ACCESS_ADDRESS);
#endif
}

void BLEPLAT_DeinitCTE(void)
{
#if defined(STM32WB06) || defined(STM32WB07) || defined(STM32WB09)
  PWR->ENGTRIM = PWR_ENGTRIM_bak;
  SYNTH0_ANA_ENG = SYNTH0_ANA_ENG_bak;
  SYNTHCAL3_ANA_TST = 0;
#endif
}

void BLEPLAT_CalibrateCTE(uint8_t smNo)
{
#if defined(STM32WB06) || defined(STM32WB07) || defined(STM32WB09)
  uint32_t dac_word = RRM->SYNTHCAL4_DIG_OUT & RRM_SYNTHCAL4_DIG_OUT_MOD_REF_DAC_WORD_OUT_Msk;
  dac_word += PLL_ADC_CALIB_CORR;
  dac_word &= RRM_SYNTHCAL4_DIG_OUT_MOD_REF_DAC_WORD_OUT_Msk;
  // Set SYNTHCAL3_ANA_TST
  SYNTHCAL3_ANA_TST = dac_word | 0x80;

  /* Restore access address. */
  LL_RADIO_SetAccessAddress(smNo, LL_DTM_ACCESS_ADDRESS);
#endif
}

void BLEPLAT_AntIdxRemap(uint8_t AntPattLen, uint8_t *pAntRamTable, const uint8_t* pAntPatt)
{
  RADIO_AntIdxRemap(AntPattLen, pAntRamTable, pAntPatt);
}

uint64_t BLEPLAT_GetCurrentSysTime(void)
{
  return HAL_RADIO_TIMER_GetCurrentSysTime();

}
uint64_t BLEPLAT_GetFutureSysTime64(uint32_t SysTime)
{
  return HAL_RADIO_TIMER_GetFutureSysTime64(SysTime);
}

int BLEPLAT_StartTimer(BLEPLAT_TimerHandleTypeDef *TimerHandle, uint64_t Time)
{
  return HAL_RADIO_TIMER_StartVirtualTimerSysTime((VTIMER_HandleType*)TimerHandle, Time);
}

void BLEPLAT_StopTimer(BLEPLAT_TimerHandleTypeDef *TimerHandle)
{
  HAL_RADIO_TIMER_StopVirtualTimer((VTIMER_HandleType*)TimerHandle);
}

uint8_t BLEPLAT_SetRadioTimerValue(uint32_t Time, uint8_t EventType, uint8_t CalReq)
{
  return HAL_RADIO_TIMER_SetRadioTimerValue(Time, EventType, CalReq);
}

uint8_t BLEPLAT_ClearRadioTimerValue(void)
{
  return HAL_RADIO_TIMER_ClearRadioTimerValue();
}

uint64_t BLEPLAT_GetAnchorPoint(uint64_t *pCurrentSysTime)
{
  return HAL_RADIO_TIMER_GetAnchorPoint(pCurrentSysTime);
}

void BLEPLAT_SetRadioCloseTimeout(void)
{
  HAL_RADIO_TIMER_SetRadioCloseTimeout();
}

uint8_t BLEPLAT_SetRadioTimerRelativeUsValue(uint32_t RelTimeoutUs, uint8_t Tx, uint8_t PLLCal)
{
  return HAL_RADIO_TIMER_SetRadioTimerRelativeUsValue(RelTimeoutUs, Tx, PLLCal);
}
