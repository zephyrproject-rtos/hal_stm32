/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_hrtim.h
  * @brief   Header file of HRTIM HAL module.
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
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7PXX_HAL_HRTIM_H
#define STM32H7PXX_HAL_HRTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_hrtim.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */
#if defined(HRTIM1)

/** @defgroup HRTIM HRTIM
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup HRTIM_Exported_Constants HAL HRTIM Constants
  * @{
  */

/** @defgroup Timer_Identifiers HRTIM timer identifiers
  * @{
  * @brief Constants identifying the master timer and timers (TIMA..F).
  */
#define HAL_HRTIM_MASTER   LL_HRTIM_MASTER     /*!< Master timer identifier */
#define HAL_HRTIM_TIMA     LL_HRTIM_TIMA       /*!< Timer A identifier */
#define HAL_HRTIM_TIMB     LL_HRTIM_TIMB       /*!< Timer B identifier */
#define HAL_HRTIM_TIMC     LL_HRTIM_TIMC       /*!< Timer C identifier */
#define HAL_HRTIM_TIMD     LL_HRTIM_TIMD       /*!< Timer D identifier */
#define HAL_HRTIM_TIME     LL_HRTIM_TIME       /*!< Timer E identifier */
#define HAL_HRTIM_TIMF     LL_HRTIM_TIMF       /*!< Timer F identifier */
/**
  * @}
  */

/** @defgroup Output_Identifiers HRTIM output identifiers
  * @{
  * @brief Constants defining the HRTIM output (CHxy) identifiers.
  *        CHxy where :
  *          x is the timing unit controlling the output (x= A to F)
  *          y is the output (y = 1 or 2)
  *        e.g. HAL_HRTIM_CHC1 corresponds to the timer C output 2.
  */
#define HAL_HRTIM_CHA1     LL_HRTIM_OUTPUT_CHA1    /*!< Timer A - output 1 */
#define HAL_HRTIM_CHA2     LL_HRTIM_OUTPUT_CHA2    /*!< Timer A - output 2 */
#define HAL_HRTIM_CHB1     LL_HRTIM_OUTPUT_CHB1    /*!< Timer B - output 1 */
#define HAL_HRTIM_CHB2     LL_HRTIM_OUTPUT_CHB2    /*!< Timer B - output 2 */
#define HAL_HRTIM_CHC1     LL_HRTIM_OUTPUT_CHC1    /*!< Timer C - output 1 */
#define HAL_HRTIM_CHC2     LL_HRTIM_OUTPUT_CHC2    /*!< Timer C - output 2 */
#define HAL_HRTIM_CHD1     LL_HRTIM_OUTPUT_CHD1    /*!< Timer D - output 1 */
#define HAL_HRTIM_CHD2     LL_HRTIM_OUTPUT_CHD2    /*!< Timer D - output 2 */
#define HAL_HRTIM_CHE1     LL_HRTIM_OUTPUT_CHE1    /*!< Timer E - output 1 */
#define HAL_HRTIM_CHE2     LL_HRTIM_OUTPUT_CHE2    /*!< Timer E - output 2 */
#define HAL_HRTIM_CHF1     LL_HRTIM_OUTPUT_CHF1    /*!< Timer F - output 1 */
#define HAL_HRTIM_CHF2     LL_HRTIM_OUTPUT_CHF2    /*!< Timer F - output 2 */
/**
  * @}
  */

/** @defgroup External_Event_Identifiers HRTIM external event identifiers
  * @{
  * @brief Constants defining the HRTIM external event (EEVx) identifiers.
  *
  * Bits 31 | Bit30             | Bits 15:0
  * ------- | ----------------- | ----- ---
  * Filter  | Fast mode         | External event number
  *
  */
#define HAL_HRTIM_EEV1     (LL_HRTIM_EEV1  | LL_HRTIM_EEV_FAST_MODE)   /*!< HRTIM external event 1 */
#define HAL_HRTIM_EEV2     (LL_HRTIM_EEV2  | LL_HRTIM_EEV_FAST_MODE)   /*!< HRTIM external event 2 */
#define HAL_HRTIM_EEV3     (LL_HRTIM_EEV3  | LL_HRTIM_EEV_FAST_MODE)   /*!< HRTIM external event 3 */
#define HAL_HRTIM_EEV4     (LL_HRTIM_EEV4  | LL_HRTIM_EEV_FAST_MODE)   /*!< HRTIM external event 4 */
#define HAL_HRTIM_EEV5     (LL_HRTIM_EEV5  | LL_HRTIM_EEV_FAST_MODE)   /*!< HRTIM external event 5 */
#define HAL_HRTIM_EEV6     (LL_HRTIM_EEV6  | LL_HRTIM_EEV_FILTER)      /*!< HRTIM external event 6 */
#define HAL_HRTIM_EEV7     (LL_HRTIM_EEV7  | LL_HRTIM_EEV_FILTER)      /*!< HRTIM external event 7 */
#define HAL_HRTIM_EEV8     (LL_HRTIM_EEV8  | LL_HRTIM_EEV_FILTER)      /*!< HRTIM external event 8 */
#define HAL_HRTIM_EEV9     (LL_HRTIM_EEV9  | LL_HRTIM_EEV_FILTER)      /*!< HRTIM external event 9 */
#define HAL_HRTIM_EEV10    (LL_HRTIM_EEV10 | LL_HRTIM_EEV_FILTER)      /*!< HRTIM external event 10 */
#define HAL_HRTIM_EEV11    (LL_HRTIM_EEV11 | LL_HRTIM_EEV_FAST_MODE)   /*!< HRTIM external event 11 */
#define HAL_HRTIM_EEV12    (LL_HRTIM_EEV12 | LL_HRTIM_EEV_FAST_MODE)   /*!< HRTIM external event 12 */
#define HAL_HRTIM_EEV13    (LL_HRTIM_EEV13 | LL_HRTIM_EEV_FAST_MODE)   /*!< HRTIM external event 13 */
#define HAL_HRTIM_EEV14    (LL_HRTIM_EEV14 | LL_HRTIM_EEV_FILTER)      /*!< HRTIM external event 14 */
#define HAL_HRTIM_EEV15    (LL_HRTIM_EEV15 | LL_HRTIM_EEV_FILTER)      /*!< HRTIM external event 15 */
#define HAL_HRTIM_EEV16    (LL_HRTIM_EEV16 | LL_HRTIM_EEV_FILTER)      /*!< HRTIM external event 16 */
/**
  * @}
  */

/** @defgroup Fault_Input_Identifiers HRTIM fault input identifiers
  * @{
  * @brief Constants defining the HRTIM fault input (FLTx) identifiers.
  */
#define HAL_HRTIM_FLT1     LL_HRTIM_FLT1       /*!< HRTIM fault input 1 */
#define HAL_HRTIM_FLT2     LL_HRTIM_FLT2       /*!< HRTIM fault input 2 */
#define HAL_HRTIM_FLT3     LL_HRTIM_FLT3       /*!< HRTIM fault input 3 */
#define HAL_HRTIM_FLT4     LL_HRTIM_FLT4       /*!< HRTIM fault input 4 */
#define HAL_HRTIM_FLT5     LL_HRTIM_FLT5       /*!< HRTIM fault input 5 */
#define HAL_HRTIM_FLT6     LL_HRTIM_FLT6       /*!< HRTIM fault input 6 */
#define HAL_HRTIM_FLT7     LL_HRTIM_FLT7       /*!< HRTIM fault input 7 */
#define HAL_HRTIM_FLT8     LL_HRTIM_FLT8       /*!< HRTIM fault input 8 */
/**
  * @}
  */

/** @defgroup Combined_Fault_Inputs  Combined fault inputs
  * @{
  * @brief Constants identifying combined fault inputs.
  */
#define HAL_HRTIM_FLT1_FLT2     LL_HRTIM_FLT1_FLT2     /*!< Fault 1 AND Fault 2 */
#define HAL_HRTIM_FLT2_FLT3     LL_HRTIM_FLT2_FLT3     /*!< Fault 2 AND Fault 3 */
#define HAL_HRTIM_FLT3_FLT4     LL_HRTIM_FLT3_FLT4     /*!< Fault 3 AND Fault 4 */
#define HAL_HRTIM_FLT4_FLT5     LL_HRTIM_FLT4_FLT5     /*!< Fault 4 AND Fault 5 */
#define HAL_HRTIM_FLT5_FLT6     LL_HRTIM_FLT5_FLT6     /*!< Fault 5 AND Fault 6 */
#define HAL_HRTIM_FLT6_FLT7     LL_HRTIM_FLT6_FLT7     /*!< Fault 6 AND Fault 7 */
#define HAL_HRTIM_FLT7_FLT8     LL_HRTIM_FLT7_FLT8     /*!< Fault 7 AND Fault 8 */
/**
  * @}
  */

/** @defgroup Combined_Event_Identifiers HRTIM combined events identifiers
  * @{
  * @brief Constants defining the combination of multiple external events (EVTx).
  */
#define HAL_HRTIM_EEVA     LL_HRTIM_EEVA   /*!< HRTIM external event A */
#define HAL_HRTIM_EEVB     LL_HRTIM_EEVB   /*!< HRTIM external event B */
#define HAL_HRTIM_EEVC     LL_HRTIM_EEVC   /*!< HRTIM external event C */
#define HAL_HRTIM_EEVD     LL_HRTIM_EEVD   /*!< HRTIM external event D */
#define HAL_HRTIM_EEVE     LL_HRTIM_EEVE   /*!< HRTIM external event E */
#define HAL_HRTIM_EEVF     LL_HRTIM_EEVF   /*!< HRTIM external event F */
#define HAL_HRTIM_EEVG     LL_HRTIM_EEVG   /*!< HRTIM external event G */
#define HAL_HRTIM_EEVH     LL_HRTIM_EEVH   /*!< HRTIM external event H */
#define HAL_HRTIM_EEVI     LL_HRTIM_EEVI   /*!< HRTIM external event I */
#define HAL_HRTIM_EEVJ     LL_HRTIM_EEVJ   /*!< HRTIM external event J */
/**
  * @}
  */

/** @defgroup ADC_Triggers HRTIM ADC triggers
  * @{
  * @brief Up to 32 events can be combined (ORed) for ADC triggers 1 to 4.
  *        The ADC triggers 1/3 and 2/4 are using the same source set.
  *        A single source can be selected at once for ADC triggers 5 to 10
  *        (1 out of 32 possible events).
  *        The ADC triggers 5/7/9 and 6/8/10 are using the same source set.
  */
/** Sources for ADC triggers 1 and 3 */
#define HAL_HRTIM_ADC13_TRIGGER_NONE           LL_HRTIM_ADCTRIG_SRC13_NONE           /*!< No ADC trigger */
#define HAL_HRTIM_ADC13_TRIGGER_MASTER_CMP1    LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP1    /*!< ADC trigger 1 or 3 on master compare 1 */
#define HAL_HRTIM_ADC13_TRIGGER_MASTER_CMP2    LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP2    /*!< ADC trigger 1 or 3 on master compare 2 */
#define HAL_HRTIM_ADC13_TRIGGER_MASTER_CMP3    LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP3    /*!< ADC trigger 1 or 3 on master compare 3 */
#define HAL_HRTIM_ADC13_TRIGGER_MASTER_CMP4    LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP4    /*!< ADC trigger 1 or 3 on master compare 4 */
#define HAL_HRTIM_ADC13_TRIGGER_MASTER_PERIOD  LL_HRTIM_ADCTRIG_SRC13_MASTER_PERIOD  /*!< ADC trigger 1 or 3 on master period */
#define HAL_HRTIM_ADC13_TRIGGER_EEV1           LL_HRTIM_ADCTRIG_SRC13_EEV1           /*!< ADC trigger 1 or 3 on external event 1 */
#define HAL_HRTIM_ADC13_TRIGGER_EEV2           LL_HRTIM_ADCTRIG_SRC13_EEV2           /*!< ADC trigger 1 or 3 on external event 2 */
#define HAL_HRTIM_ADC13_TRIGGER_EEV3           LL_HRTIM_ADCTRIG_SRC13_EEV3           /*!< ADC trigger 1 or 3 on external event 3 */
#define HAL_HRTIM_ADC13_TRIGGER_EEV4           LL_HRTIM_ADCTRIG_SRC13_EEV4           /*!< ADC trigger 1 or 3 on external event 4 */
#define HAL_HRTIM_ADC13_TRIGGER_EEV5           LL_HRTIM_ADCTRIG_SRC13_EEV5           /*!< ADC trigger 1 or 3 on external event 5 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMA_CMP3      LL_HRTIM_ADCTRIG_SRC13_TIMA_CMP3      /*!< ADC trigger 1 or 3 on timer A compare 3 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMA_CMP4      LL_HRTIM_ADCTRIG_SRC13_TIMA_CMP4      /*!< ADC trigger 1 or 3 on timer A compare 4 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMA_PERIOD    LL_HRTIM_ADCTRIG_SRC13_TIMA_PERIOD    /*!< ADC trigger 1 or 3 on timer A period */
#define HAL_HRTIM_ADC13_TRIGGER_TIMA_RESET     LL_HRTIM_ADCTRIG_SRC13_TIMA_RESET     /*!< ADC trigger 1 or 3 on master reset */
#define HAL_HRTIM_ADC13_TRIGGER_TIMB_CMP3      LL_HRTIM_ADCTRIG_SRC13_TIMB_CMP3      /*!< ADC trigger 1 or 3 on timer B compare 3 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMB_CMP4      LL_HRTIM_ADCTRIG_SRC13_TIMB_CMP4      /*!< ADC trigger 1 or 3 on timer B compare 4 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMB_PERIOD    LL_HRTIM_ADCTRIG_SRC13_TIMB_PERIOD    /*!< ADC trigger 1 or 3 on timer B period */
#define HAL_HRTIM_ADC13_TRIGGER_TIMB_RESET     LL_HRTIM_ADCTRIG_SRC13_TIMB_RESET     /*!< ADC trigger 1 or 3 on timer B reset */
#define HAL_HRTIM_ADC13_TRIGGER_TIMC_CMP3      LL_HRTIM_ADCTRIG_SRC13_TIMC_CMP3      /*!< ADC trigger 1 or 3 on timer C compare 3 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMC_CMP4      LL_HRTIM_ADCTRIG_SRC13_TIMC_CMP4      /*!< ADC trigger 1 or 3 on timer C compare 4 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMC_PERIOD    LL_HRTIM_ADCTRIG_SRC13_TIMC_PERIOD    /*!< ADC trigger 1 or 3 on timer C period */
#define HAL_HRTIM_ADC13_TRIGGER_TIMD_CMP3      LL_HRTIM_ADCTRIG_SRC13_TIMD_CMP3      /*!< ADC trigger 1 or 3 on timer D compare 3 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMD_CMP4      LL_HRTIM_ADCTRIG_SRC13_TIMD_CMP4      /*!< ADC trigger 1 or 3 on timer D compare 4 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMD_PERIOD    LL_HRTIM_ADCTRIG_SRC13_TIMD_PERIOD    /*!< ADC trigger 1 or 3 on timer D period */
#define HAL_HRTIM_ADC13_TRIGGER_TIME_CMP3      LL_HRTIM_ADCTRIG_SRC13_TIME_CMP3      /*!< ADC trigger 1 or 3 on timer E compare 3 */
#define HAL_HRTIM_ADC13_TRIGGER_TIME_CMP4      LL_HRTIM_ADCTRIG_SRC13_TIME_CMP4      /*!< ADC trigger 1 or 3 on timer E compare 4 */
#define HAL_HRTIM_ADC13_TRIGGER_TIME_PERIOD    LL_HRTIM_ADCTRIG_SRC13_TIME_PERIOD    /*!< ADC trigger 1 or 3 on timer E period */
#define HAL_HRTIM_ADC13_TRIGGER_TIMF_CMP2      LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP2      /*!< ADC trigger 1 or 3 on timer F compare 2 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMF_CMP3      LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP3      /*!< ADC trigger 1 or 3 on timer F compare 3 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMF_CMP4      LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP4      /*!< ADC trigger 1 or 3 on timer F compare 4 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMF_PERIOD    LL_HRTIM_ADCTRIG_SRC13_TIMF_PERIOD    /*!< ADC trigger 1 or 3 on master compare 1 */
#define HAL_HRTIM_ADC13_TRIGGER_TIMF_RESET     LL_HRTIM_ADCTRIG_SRC13_TIMF_RESET     /*!< ADC trigger 1 or 3 on timer F reset */

/** Sources for ADC triggers 2 and 4 */
#define HAL_HRTIM_ADC24_TRIGGER_NONE           LL_HRTIM_ADCTRIG_SRC24_NONE           /*!< No ADC trigger */
#define HAL_HRTIM_ADC24_TRIGGER_MASTER_CMP1    LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP1    /*!< ADC trigger 2 or 4 on master compare 1 */
#define HAL_HRTIM_ADC24_TRIGGER_MASTER_CMP2    LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP2    /*!< ADC trigger 2 or 4 on master compare 2 */
#define HAL_HRTIM_ADC24_TRIGGER_MASTER_CMP3    LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP3    /*!< ADC trigger 2 or 4 on master compare 3 */
#define HAL_HRTIM_ADC24_TRIGGER_MASTER_CMP4    LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP4    /*!< ADC trigger 2 or 4 on master compare 4 */
#define HAL_HRTIM_ADC24_TRIGGER_MASTER_PERIOD  LL_HRTIM_ADCTRIG_SRC24_MASTER_PERIOD  /*!< ADC trigger 2 or 4 on master period */
#define HAL_HRTIM_ADC24_TRIGGER_EEV6           LL_HRTIM_ADCTRIG_SRC24_EEV6           /*!< ADC trigger 2 or 4 on external event 6 */
#define HAL_HRTIM_ADC24_TRIGGER_EEV7           LL_HRTIM_ADCTRIG_SRC24_EEV7           /*!< ADC trigger 2 or 4 on external event 7 */
#define HAL_HRTIM_ADC24_TRIGGER_EEV8           LL_HRTIM_ADCTRIG_SRC24_EEV8           /*!< ADC trigger 2 or 4 on external event 8 */
#define HAL_HRTIM_ADC24_TRIGGER_EEV9           LL_HRTIM_ADCTRIG_SRC24_EEV9           /*!< ADC trigger 2 or 4 on external event 9 */
#define HAL_HRTIM_ADC24_TRIGGER_EEV10          LL_HRTIM_ADCTRIG_SRC24_EEV10          /*!< ADC trigger 2 or 4 on external event 10 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMA_CMP2      LL_HRTIM_ADCTRIG_SRC24_TIMA_CMP2      /*!< ADC trigger 2 or 4 on timer A compare 2 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMA_CMP4      LL_HRTIM_ADCTRIG_SRC24_TIMA_CMP4      /*!< ADC trigger 2 or 4 on timer A compare 4 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMA_PERIOD    LL_HRTIM_ADCTRIG_SRC24_TIMA_PERIOD    /*!< ADC trigger 2 or 4 on timer A period */
#define HAL_HRTIM_ADC24_TRIGGER_TIMB_CMP2      LL_HRTIM_ADCTRIG_SRC24_TIMB_CMP2      /*!< ADC trigger 2 or 4 on timer B compare 2 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMB_CMP4      LL_HRTIM_ADCTRIG_SRC24_TIMB_CMP4      /*!< ADC trigger 2 or 4 on timer B compare 4 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMB_PERIOD    LL_HRTIM_ADCTRIG_SRC24_TIMB_PERIOD    /*!< ADC trigger 2 or 4 on timer B period */
#define HAL_HRTIM_ADC24_TRIGGER_TIMC_CMP2      LL_HRTIM_ADCTRIG_SRC24_TIMC_CMP2      /*!< ADC trigger 2 or 4 on timer C compare 2 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMC_CMP4      LL_HRTIM_ADCTRIG_SRC24_TIMC_CMP4      /*!< ADC trigger 2 or 4 on timer C compare 4 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMC_PERIOD    LL_HRTIM_ADCTRIG_SRC24_TIMC_PERIOD    /*!< ADC trigger 2 or 4 on timer C period */
#define HAL_HRTIM_ADC24_TRIGGER_TIMC_RESET     LL_HRTIM_ADCTRIG_SRC24_TIMC_RESET     /*!< ADC trigger 2 or 4 on timer C reset */
#define HAL_HRTIM_ADC24_TRIGGER_TIMD_CMP2      LL_HRTIM_ADCTRIG_SRC24_TIMD_CMP2      /*!< ADC trigger 2 or 4 on timer D compare 2 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMD_CMP4      LL_HRTIM_ADCTRIG_SRC24_TIMD_CMP4      /*!< ADC trigger 2 or 4 on timer D compare 4 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMD_PERIOD    LL_HRTIM_ADCTRIG_SRC24_TIMD_PERIOD    /*!< ADC trigger 2 or 4 on timer D period */
#define HAL_HRTIM_ADC24_TRIGGER_TIMD_RESET     LL_HRTIM_ADCTRIG_SRC24_TIMD_RESET     /*!< ADC trigger 2 or 4 on timer D reset */
#define HAL_HRTIM_ADC24_TRIGGER_TIME_CMP2      LL_HRTIM_ADCTRIG_SRC24_TIME_CMP2      /*!< ADC trigger 2 or 4 on timer E compare 2 */
#define HAL_HRTIM_ADC24_TRIGGER_TIME_CMP3      LL_HRTIM_ADCTRIG_SRC24_TIME_CMP3      /*!< ADC trigger 2 or 4 on timer E compare 3 */
#define HAL_HRTIM_ADC24_TRIGGER_TIME_CMP4      LL_HRTIM_ADCTRIG_SRC24_TIME_CMP4      /*!< ADC trigger 2 or 4 on timer E compare 4 */
#define HAL_HRTIM_ADC24_TRIGGER_TIME_RESET     LL_HRTIM_ADCTRIG_SRC24_TIME_RESET     /*!< ADC trigger 2 or 4 on timer E reset */
#define HAL_HRTIM_ADC24_TRIGGER_TIMF_CMP2      LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP2      /*!< ADC trigger 2 or 4 on timer F compare 2 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMF_CMP3      LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP3      /*!< ADC trigger 2 or 4 on timer F compare 3 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMF_CMP4      LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP4      /*!< ADC trigger 2 or 4 on timer F compare 4 */
#define HAL_HRTIM_ADC24_TRIGGER_TIMF_PERIOD    LL_HRTIM_ADCTRIG_SRC24_TIMF_PERIOD    /*!< ADC trigger 2 or 4 on timer F period */

/** Sources for ADC triggers 5, 7 and 9 */
#define HAL_HRTIM_ADC579_TRIGGER_MASTER_CMP1    LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP1    /*!< ADC trigger 5, 7 or 9 on master compare 1 */
#define HAL_HRTIM_ADC579_TRIGGER_MASTER_CMP2    LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP2    /*!< ADC trigger 5, 7 or 9 on master compare 2 */
#define HAL_HRTIM_ADC579_TRIGGER_MASTER_CMP3    LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP3    /*!< ADC trigger 5, 7 or 9 on master compare 3 */
#define HAL_HRTIM_ADC579_TRIGGER_MASTER_CMP4    LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP4    /*!< ADC trigger 5, 7 or 9 on master compare 4 */
#define HAL_HRTIM_ADC579_TRIGGER_MASTER_PERIOD  LL_HRTIM_ADCTRIG_SRC579_MASTER_PERIOD  /*!< ADC trigger 5, 7 or 9 on master period */
#define HAL_HRTIM_ADC579_TRIGGER_EEV1           LL_HRTIM_ADCTRIG_SRC579_EEV1           /*!< ADC trigger 5, 7 or 9 on external event 1 */
#define HAL_HRTIM_ADC579_TRIGGER_EEV2           LL_HRTIM_ADCTRIG_SRC579_EEV2           /*!< ADC trigger 5, 7 or 9 on external event 2 */
#define HAL_HRTIM_ADC579_TRIGGER_EEV3           LL_HRTIM_ADCTRIG_SRC579_EEV3           /*!< ADC trigger 5, 7 or 9 on external event 3 */
#define HAL_HRTIM_ADC579_TRIGGER_EEV4           LL_HRTIM_ADCTRIG_SRC579_EEV4           /*!< ADC trigger 5, 7 or 9 on external event 4 */
#define HAL_HRTIM_ADC579_TRIGGER_EEV5           LL_HRTIM_ADCTRIG_SRC579_EEV5           /*!< ADC trigger 5, 7 or 9 on external event 5 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMA_CMP3      LL_HRTIM_ADCTRIG_SRC579_TIMA_CMP3      /*!< ADC trigger 5, 7 or 9 on timer A compare 3 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMA_CMP4      LL_HRTIM_ADCTRIG_SRC579_TIMA_CMP4      /*!< ADC trigger 5, 7 or 9 on timer A compare 4 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMA_PERIOD    LL_HRTIM_ADCTRIG_SRC579_TIMA_PERIOD    /*!< ADC trigger 5, 7 or 9 on timer A period */
#define HAL_HRTIM_ADC579_TRIGGER_TIMA_RESET     LL_HRTIM_ADCTRIG_SRC579_TIMA_RESET     /*!< ADC trigger 5, 7 or 9 on master reset */
#define HAL_HRTIM_ADC579_TRIGGER_TIMB_CMP3      LL_HRTIM_ADCTRIG_SRC579_TIMB_CMP3      /*!< ADC trigger 5, 7 or 9 on timer B compare 3 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMB_CMP4      LL_HRTIM_ADCTRIG_SRC579_TIMB_CMP4      /*!< ADC trigger 5, 7 or 9 on timer B compare 4 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMB_PERIOD    LL_HRTIM_ADCTRIG_SRC579_TIMB_PERIOD    /*!< ADC trigger 5, 7 or 9 on timer B period */
#define HAL_HRTIM_ADC579_TRIGGER_TIMB_RESET     LL_HRTIM_ADCTRIG_SRC579_TIMB_RESET     /*!< ADC trigger 5, 7 or 9 on timer B reset */
#define HAL_HRTIM_ADC579_TRIGGER_TIMC_CMP3      LL_HRTIM_ADCTRIG_SRC579_TIMC_CMP3      /*!< ADC trigger 5, 7 or 9 on timer C compare 3 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMC_CMP4      LL_HRTIM_ADCTRIG_SRC579_TIMC_CMP4      /*!< ADC trigger 5, 7 or 9 on timer C compare 4 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMC_PERIOD    LL_HRTIM_ADCTRIG_SRC579_TIMC_PERIOD    /*!< ADC trigger 5, 7 or 9 on timer C period */
#define HAL_HRTIM_ADC579_TRIGGER_TIMD_CMP3      LL_HRTIM_ADCTRIG_SRC579_TIMD_CMP3      /*!< ADC trigger 5, 7 or 9 on timer D compare 3 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMD_CMP4      LL_HRTIM_ADCTRIG_SRC579_TIMD_CMP4      /*!< ADC trigger 5, 7 or 9 on timer D compare 4 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMD_PERIOD    LL_HRTIM_ADCTRIG_SRC579_TIMD_PERIOD    /*!< ADC trigger 5, 7 or 9 on timer D period */
#define HAL_HRTIM_ADC579_TRIGGER_TIME_CMP3      LL_HRTIM_ADCTRIG_SRC579_TIME_CMP3      /*!< ADC trigger 5, 7 or 9 on timer E compare 3 */
#define HAL_HRTIM_ADC579_TRIGGER_TIME_CMP4      LL_HRTIM_ADCTRIG_SRC579_TIME_CMP4      /*!< ADC trigger 5, 7 or 9 on timer E compare 4 */
#define HAL_HRTIM_ADC579_TRIGGER_TIME_PERIOD    LL_HRTIM_ADCTRIG_SRC579_TIME_PERIOD    /*!< ADC trigger 5, 7 or 9 on timer E period */
#define HAL_HRTIM_ADC579_TRIGGER_TIMF_CMP2      LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP2      /*!< ADC trigger 5, 7 or 9 on timer F compare 2 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMF_CMP3      LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP3      /*!< ADC trigger 5, 7 or 9 on timer F compare 3 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMF_CMP4      LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP4      /*!< ADC trigger 5, 7 or 9 on timer F compare 4 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMF_PERIOD    LL_HRTIM_ADCTRIG_SRC579_TIMF_PERIOD    /*!< ADC trigger 5, 7 or 9 on master compare 1 */
#define HAL_HRTIM_ADC579_TRIGGER_TIMF_RESET     LL_HRTIM_ADCTRIG_SRC579_TIMF_RESET     /*!< ADC trigger 5, 7 or 9 on timer F reset */

/** Sources for ADC triggers 6, 8 and 10 */
#define HAL_HRTIM_ADC6810_TRIGGER_MASTER_CMP1   LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP1   /*!< ADC trigger 6, 8 or 10 on master compare 1 */
#define HAL_HRTIM_ADC6810_TRIGGER_MASTER_CMP2   LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP2   /*!< ADC trigger 6, 8 or 10 on master compare 2 */
#define HAL_HRTIM_ADC6810_TRIGGER_MASTER_CMP3   LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP3   /*!< ADC trigger 6, 8 or 10 on master compare 3 */
#define HAL_HRTIM_ADC6810_TRIGGER_MASTER_CMP4   LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP4   /*!< ADC trigger 6, 8 or 10 on master compare 4 */
#define HAL_HRTIM_ADC6810_TRIGGER_MASTER_PERIOD LL_HRTIM_ADCTRIG_SRC6810_MASTER_PERIOD /*!< ADC trigger 6, 8 or 10 on master period */
#define HAL_HRTIM_ADC6810_TRIGGER_EEV6          LL_HRTIM_ADCTRIG_SRC6810_EEV6          /*!< ADC trigger 6, 8 or 10 on external event 6 */
#define HAL_HRTIM_ADC6810_TRIGGER_EEV7          LL_HRTIM_ADCTRIG_SRC6810_EEV7          /*!< ADC trigger 6, 8 or 10 on external event 7 */
#define HAL_HRTIM_ADC6810_TRIGGER_EEV8          LL_HRTIM_ADCTRIG_SRC6810_EEV8          /*!< ADC trigger 6, 8 or 10 on external event 8 */
#define HAL_HRTIM_ADC6810_TRIGGER_EEV9          LL_HRTIM_ADCTRIG_SRC6810_EEV9          /*!< ADC trigger 6, 8 or 10 on external event 9 */
#define HAL_HRTIM_ADC6810_TRIGGER_EEV10         LL_HRTIM_ADCTRIG_SRC6810_EEV10         /*!< ADC trigger 6, 8 or 10 on external event 10 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMA_CMP2     LL_HRTIM_ADCTRIG_SRC6810_TIMA_CMP2     /*!< ADC trigger 6, 8 or 10 on timer A compare 2 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMA_CMP4     LL_HRTIM_ADCTRIG_SRC6810_TIMA_CMP4     /*!< ADC trigger 6, 8 or 10 on timer A compare 4 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMA_PERIOD   LL_HRTIM_ADCTRIG_SRC6810_TIMA_PERIOD   /*!< ADC trigger 6, 8 or 10 on timer A period */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMB_CMP2     LL_HRTIM_ADCTRIG_SRC6810_TIMB_CMP2     /*!< ADC trigger 6, 8 or 10 on timer B compare 2 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMB_CMP4     LL_HRTIM_ADCTRIG_SRC6810_TIMB_CMP4     /*!< ADC trigger 6, 8 or 10 on timer B compare 4 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMB_PERIOD   LL_HRTIM_ADCTRIG_SRC6810_TIMB_PERIOD   /*!< ADC trigger 6, 8 or 10 on timer B period */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMC_CMP2     LL_HRTIM_ADCTRIG_SRC6810_TIMC_CMP2     /*!< ADC trigger 6, 8 or 10 on timer C compare 2 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMC_CMP4     LL_HRTIM_ADCTRIG_SRC6810_TIMC_CMP4     /*!< ADC trigger 6, 8 or 10 on timer C compare 4 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMC_PERIOD   LL_HRTIM_ADCTRIG_SRC6810_TIMC_PERIOD   /*!< ADC trigger 6, 8 or 10 on timer C period */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMC_RESET    LL_HRTIM_ADCTRIG_SRC6810_TIMC_RESET    /*!< ADC trigger 6, 8 or 10 on timer C reset */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMD_CMP2     LL_HRTIM_ADCTRIG_SRC6810_TIMD_CMP2     /*!< ADC trigger 6, 8 or 10 on timer D compare 2 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMD_CMP4     LL_HRTIM_ADCTRIG_SRC6810_TIMD_CMP4     /*!< ADC trigger 6, 8 or 10 on timer D compare 4 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMD_PERIOD   LL_HRTIM_ADCTRIG_SRC6810_TIMD_PERIOD   /*!< ADC trigger 6, 8 or 10 on timer D period */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMD_RESET    LL_HRTIM_ADCTRIG_SRC6810_TIMD_RESET    /*!< ADC trigger 6, 8 or 10 on timer D reset */
#define HAL_HRTIM_ADC6810_TRIGGER_TIME_CMP2     LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP2     /*!< ADC trigger 6, 8 or 10 on timer E compare 2 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIME_CMP3     LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP3     /*!< ADC trigger 6, 8 or 10 on timer E compare 3 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIME_CMP4     LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP4     /*!< ADC trigger 6, 8 or 10 on timer E compare 4 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIME_RESET    LL_HRTIM_ADCTRIG_SRC6810_TIME_RESET    /*!< ADC trigger 6, 8 or 10 on timer E reset */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMF_CMP2     LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP2     /*!< ADC trigger 6, 8 or 10 on timer F compare 2 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMF_CMP3     LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP3     /*!< ADC trigger 6, 8 or 10 on timer F compare 3 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMF_CMP4     LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP4     /*!< ADC trigger 6, 8 or 10 on timer F compare 4 */
#define HAL_HRTIM_ADC6810_TRIGGER_TIMF_PERIOD   LL_HRTIM_ADCTRIG_SRC6810_TIMF_PERIOD   /*!< ADC trigger 6, 8 or 10 on timer F period */
/**
  * @}
  */

/** @defgroup Event_Blanking_Windowing External event filtering in timing units
  * @{
  * @brief External events can be filtered by a timing unit to have an action limited
  *        in time.
  *        Two operations can be performed:
  *          - blanking, to mask external events during a defined time period,
  *          - windowing, to enable external events only during a defined time period.
  */
#define HAL_HRTIM_NO_FILTERING          LL_HRTIM_NO_FILTERING        /*!< No filtering.*/
#define HAL_HRTIM_BLK_RST_CMP1          LL_HRTIM_BLK_RST_CMP1        /*!< Blanking from counter reset/roll-over
                                                                          to compare 1.*/
#define HAL_HRTIM_BLK_RST_CMP2          LL_HRTIM_BLK_RST_CMP2        /*!< In up counting mode: blanking from
                                                                          counter reset/roll-over to compare 2.
                                                                          In up/down counting mode: blanking
                                                                          from compare 1 to compare 2, only
                                                                          during the up-counting phase.*/
#define HAL_HRTIM_BLK_RST_CMP3          LL_HRTIM_BLK_RST_CMP3        /*!< Blanking from counter reset/roll-over
                                                                          to compare 3.*/
#define HAL_HRTIM_BLK_RST_CMP4          LL_HRTIM_BLK_RST_CMP4        /*!< In up counting mode: blanking from
                                                                          counter reset/roll-over to compare 4.
                                                                          In up/down counting mode: blanking
                                                                          from compare 3 to compare 4, only
                                                                          during the up-counting phase.*/
#define HAL_HRTIM_BLK_CMP1_RST          LL_HRTIM_BLK_CMP1_RST        /*!< In up counting mode: blanking from
                                                                          compare 1 to counter reset/roll-over.
                                                                          In up/down counting mode: blanking
                                                                          from compare 1 (down-counting) to
                                                                          compare 2 (up-counting).*/
#define HAL_HRTIM_BLK_CMP2_RST          LL_HRTIM_BLK_CMP2_RST        /*!< In up counting mode: blanking from
                                                                          compare 2 to counter reset/roll-over.
                                                                          In up/down counting mode: blanking
                                                                          from compare 1 (up-counting) to
                                                                          compare 2 (down-counting).*/
#define HAL_HRTIM_BLK_CMP1_CMP2         LL_HRTIM_BLK_CMP1_CMP2       /*!< In up counting mode: blanking from
                                                                          compare 1 to compare 2.
                                                                          In up/down counting mode: blanking
                                                                          from compare 1 (up-counting) to
                                                                          compare 2 (down-counting).*/
#define HAL_HRTIM_BLK_CMP3_CMP4         LL_HRTIM_BLK_CMP3_CMP4        /*!< In up counting mode: blanking from
                                                                           compare 3 to compare 4.
                                                                           In up/down counting mode: blanking
                                                                           from compare 3 (down-counting) to
                                                                           compare 4 (up-counting).*/
#define HAL_HRTIM_BLK_PER_CMP1          LL_HRTIM_BLK_PER_CMP1         /*!< Blanking from period to compare 1.*/
#define HAL_HRTIM_BLK_PER_CMP2          LL_HRTIM_BLK_PER_CMP2         /*!< Blanking from Period to compare 2. */
#define HAL_HRTIM_BLK_RST_CMP1_CPPSTAT  LL_HRTIM_BLK_RST_CMP1_CPPSTAT /*!< Blanking from counter reset/roll-over
                                                                           to cmp1 when CPPSTAT = 0 and unconditional 
                                                                           blanking when CPPSTAT = 1 */
#define HAL_HRTIM_WIN_RST_CMP2          LL_HRTIM_WIN_RST_CMP2         /*!< In up counting mode: windowing from
                                                                           counter reset/roll-over to compare 2.
                                                                           In up/down counting mode: windowing
                                                                           from compare 1 to compare 2, only
                                                                           during the down-counting phase. */
#define HAL_HRTIM_WIN_RST_CMP3          LL_HRTIM_WIN_RST_CMP3         /*!< In up counting mode: windowing from
                                                                           counter reset/roll-over to compare 3.
                                                                           In up/down counting mode: windowing
                                                                           from compare 2 to compare 3, only
                                                                           during the down-counting phase */
#define HAL_HRTIM_WIN_CMP1_RST          LL_HRTIM_WIN_CMP1_RST         /*!< Windowing from compare 1 to
                                                                           counter reset/roll-over).*/
#define HAL_HRTIM_WIN_CMP2_RST          LL_HRTIM_WIN_CMP2_RST         /*!< Windowing from compare 2 to
                                                                           counter reset/roll-over).*/
#define HAL_HRTIM_WIN_CMP1_CMP2         LL_HRTIM_WIN_CMP1_CMP2        /*!< In up counting mode: windowing from
                                                                           compare 1 to compare 2.
                                                                           In up/down counting mode: windowing
                                                                           from compare 1 (up-counting) to
                                                                           compare 2 (down-counting).*/
#define HAL_HRTIM_WIN_CMP3_CMP4         LL_HRTIM_WIN_CMP3_CMP4        /*!< In up counting mode: windowing from
                                                                           compare 3 to compare 4.
                                                                           In up/down counting mode: windowing
                                                                           from compare 3 (down-counting) to
                                                                           compare 4 (up-counting).*/

/* Events from other timing units that can be used as filtering signals for Timer A */
#define HAL_HRTIM_BLK_TIMA_TBRST_TBCMP1  LL_HRTIM_BLK_TIMA_TBRST_TBCMP1  /*!< Blanking from Timer B counter reset to Timer B compare 1 match (TIMFLTR1) */
#define HAL_HRTIM_BLK_TIMA_TBRST_TBCMP4  LL_HRTIM_BLK_TIMA_TBRST_TBCMP4  /*!< Blanking from Timer B counter reset to Timer B compare 4 match (TIMFLTR2) */
#define HAL_HRTIM_BLK_TIMA_CHB2          LL_HRTIM_BLK_TIMA_CHB2          /*!< Blanking is Timer B output 2 (CHB2) waveform (TIMFLTR3) */
#define HAL_HRTIM_BLK_TIMA_TCRST_TCCMP1  LL_HRTIM_BLK_TIMA_TCRST_TCCMP1  /*!< Blanking from Timer C counter reset to Timer C compare 1 match (TIMFLTR4) */
#define HAL_HRTIM_BLK_TIMA_TCRST_TCCMP4  LL_HRTIM_BLK_TIMA_TCRST_TCCMP4  /*!< Blanking from Timer C counter reset to Timer C compare 4 match (TIMFLTR5) */
#define HAL_HRTIM_BLK_TIMA_TFRST_TFCMP1  LL_HRTIM_BLK_TIMA_TFRST_TFCMP1  /*!< Blanking from Timer F counter reset to Timer F compare 1 match (TIMFLTR6) */
#define HAL_HRTIM_BLK_TIMA_TDRST_TDCMP1  LL_HRTIM_BLK_TIMA_TDRST_TDCMP1  /*!< Blanking from Timer D counter reset to Timer D compare 1 match (TIMFLTR7) */
#define HAL_HRTIM_BLK_TIMA_TERST_TECMP2  LL_HRTIM_BLK_TIMA_TERST_TECMP2  /*!< Blanking from Timer E counter reset to Timer E compare 2 match (TIMFLTR8) */
#define HAL_HRTIM_WIN_TIMA_TBRST_TBCMP2  LL_HRTIM_WIN_TIMA_TBRST_TBCMP2  /*!< Windowing from timer B counter reset to Timer B compare 2 match (TIMWIN)  */
#define HAL_HRTIM_WIN_TIMA_TBCMP2_TBRST  LL_HRTIM_WIN_TIMA_TBCMP2_TBRST  /*!< Windowing from Timer B compare 2 match to timer B counter reset (TIMWIN2) */
#define HAL_HRTIM_WIN_TIMA_TBCMP1_TBRST  LL_HRTIM_WIN_TIMA_TBCMP1_TBRST  /*!< Windowing from Timer B compare 1 match to timer B compare 2 match (TIMWIN3) */

/* Events from other timing units that can be used as filtering signals for Timer B */
#define HAL_HRTIM_BLK_TIMB_TARST_TACMP1  LL_HRTIM_BLK_TIMB_TARST_TACMP1  /*!< Blanking from Timer A counter reset to Timer A compare 1 match (TIMFLTR1) */
#define HAL_HRTIM_BLK_TIMB_TARST_TACMP4  LL_HRTIM_BLK_TIMB_TARST_TACMP4  /*!< Blanking from Timer A counter reset to Timer A compare 4 match (TIMFLTR2) */
#define HAL_HRTIM_BLK_TIMB_CHA2          LL_HRTIM_BLK_TIMB_CHA2          /*!< Blanking is Timer A output 2 (CHA2) waveform (TIMFLTR3) */
#define HAL_HRTIM_BLK_TIMB_TCRST_TCCMP1  LL_HRTIM_BLK_TIMB_TCRST_TCCMP1  /*!< Blanking from Timer C counter reset to Timer C compare 1 match (TIMFLTR4) */
#define HAL_HRTIM_BLK_TIMB_TCRST_TCCMP2  LL_HRTIM_BLK_TIMB_TCRST_TCCMP2  /*!< Blanking from Timer C counter reset to Timer C compare 2 match (TIMFLTR5) */
#define HAL_HRTIM_BLK_TIMB_TFRST_TFCMP2  LL_HRTIM_BLK_TIMB_TFRST_TFCMP2  /*!< Blanking from Timer F counter reset to Timer F compare 2 match (TIMFLTR6) */
#define HAL_HRTIM_BLK_TIMB_TDRST_TDCMP2  LL_HRTIM_BLK_TIMB_TDRST_TDCMP2  /*!< Blanking from Timer D counter reset to Timer D compare 2 match (TIMFLTR7) */
#define HAL_HRTIM_BLK_TIMB_TERST_TECMP1  LL_HRTIM_BLK_TIMB_TERST_TECMP1  /*!< Blanking from Timer E counter reset to Timer E compare 1 match (TIMFLTR8) */
#define HAL_HRTIM_WIN_TIMB_TARST_TACMP2  LL_HRTIM_WIN_TIMB_TARST_TACMP2  /*!< Windowing from timer A counter reset to Timer A compare 2 match (TIMWIN) */
#define HAL_HRTIM_WIN_TIMB_TACMP2_TARST  LL_HRTIM_WIN_TIMB_TACMP2_TARST  /*!< Windowing from Timer A compare 2 match to timer A counter reset (TIMWIN2) */
#define HAL_HRTIM_WIN_TIMB_TACMP1_TARST  LL_HRTIM_WIN_TIMB_TACMP1_TARST  /*!< Windowing from Timer A compare 1 match to timer A compare 2 match (TIMWIN3) */

/* Events from other timing units that can be used as filtering signals for Timer C */
#define HAL_HRTIM_BLK_TIMC_TARST_TACMP2  LL_HRTIM_BLK_TIMC_TARST_TACMP2  /*!< Blanking from Timer A counter reset to Timer A compare 2 match (TIMFLTR1) */
#define HAL_HRTIM_BLK_TIMC_TBRST_TBCMP1  LL_HRTIM_BLK_TIMC_TBRST_TBCMP1  /*!< Blanking from Timer B counter reset to Timer B compare 1 match (TIMFLTR2) */
#define HAL_HRTIM_BLK_TIMC_TBRST_TBCMP4  LL_HRTIM_BLK_TIMC_TBRST_TBCMP4  /*!< Blanking from Timer B counter reset to Timer B compare 4 match (TIMFLTR3) */
#define HAL_HRTIM_BLK_TIMC_TFRST_TFCMP1  LL_HRTIM_BLK_TIMC_TFRST_TFCMP1  /*!< Blanking from Timer F counter reset to Timer F compare 1 match (TIMFLTR4) */
#define HAL_HRTIM_BLK_TIMC_TDRST_TDCMP1  LL_HRTIM_BLK_TIMC_TDRST_TDCMP1  /*!< Blanking from Timer D counter reset to Timer D compare 1 match (TIMFLTR5) */
#define HAL_HRTIM_BLK_TIMC_TDRST_TDCMP4  LL_HRTIM_BLK_TIMC_TDRST_TDCMP4  /*!< Blanking from Timer D counter reset to Timer D compare 4 match (TIMFLTR6) */
#define HAL_HRTIM_BLK_TIMC_CHD2          LL_HRTIM_BLK_TIMC_CHD2          /*!< Blanking is Timer D output 2 (CHD2) waveform (TIMFLTR7) */
#define HAL_HRTIM_BLK_TIMC_TERST_TECMP4  LL_HRTIM_BLK_TIMC_TERST_TECMP4  /*!< Blanking from Timer E counter reset to Timer E compare 4 match (TIMFLTR8) */
#define HAL_HRTIM_WIN_TIMC_TDRST_TDCMP2  LL_HRTIM_WIN_TIMC_TDRST_TDCMP2  /*!< Windowing from timer D counter reset to Timer D compare 2 match (TIMWIN) */
#define HAL_HRTIM_WIN_TIMC_TDCMP2_TDRST  LL_HRTIM_WIN_TIMC_TDCMP2_TDRST  /*!< Windowing from Timer D compare 2 match to timer D counter reset (TIMWIN2) */
#define HAL_HRTIM_WIN_TIMC_TDCMP1_TDRST  LL_HRTIM_WIN_TIMC_TDCMP1_TDRST  /*!< Windowing from Timer D compare 1 match to timer D compare 2 match (TIMWIN3) */

/* Events from other timing units that can be used as filtering signals for Timer D */
#define HAL_HRTIM_BLK_TIMD_TARST_TACMP1  LL_HRTIM_BLK_TIMD_TARST_TACMP1  /*!< Blanking from Timer A counter reset to Timer A compare 1 match (TIMFLTR1) */
#define HAL_HRTIM_BLK_TIMD_TBRST_TBCMP2  LL_HRTIM_BLK_TIMD_TBRST_TBCMP2  /*!< Blanking from Timer B counter reset to Timer B compare 2 match (TIMFLTR2) */
#define HAL_HRTIM_BLK_TIMD_TCRST_TCCMP1  LL_HRTIM_BLK_TIMD_TCRST_TCCMP1  /*!< Blanking from Timer C counter reset to Timer C compare 1 match (TIMFLTR3) */
#define HAL_HRTIM_BLK_TIMD_TCRST_TCCMP2  LL_HRTIM_BLK_TIMD_TCRST_TCCMP2  /*!< Blanking from Timer F counter reset to Timer C compare 2 match (TIMFLTR4) */
#define HAL_HRTIM_BLK_TIMD_CHC2          LL_HRTIM_BLK_TIMD_CHC2          /*!< Blanking is Timer C output 2 (CHC2) waveform (TIMFLTR5) */
#define HAL_HRTIM_BLK_TIMD_TERST_TECMP1  LL_HRTIM_BLK_TIMD_TERST_TECMP1  /*!< Blanking from Timer E counter reset to Timer E compare 1 match (TIMFLTR6) */
#define HAL_HRTIM_BLK_TIMD_TERST_TECMP4  LL_HRTIM_BLK_TIMD_TERST_TECMP4  /*!< Blanking from Timer E counter reset to Timer E compare 4 match (TIMFLTR7) */
#define HAL_HRTIM_BLK_TIMD_TFRST_TFCMP4  LL_HRTIM_BLK_TIMD_TFRST_TFCMP4  /*!< Blanking from Timer F counter reset to Timer E compare 4 match (TIMFLTR8) */
#define HAL_HRTIM_WIN_TIMD_TCRST_TCCMP2  LL_HRTIM_WIN_TIMD_TCRST_TCCMP2  /*!< Windowing from timer C counter reset to Timer C compare 2 match (TIMWIN) */
#define HAL_HRTIM_WIN_TIMD_TCCMP2_TCRST  LL_HRTIM_WIN_TIMD_TCCMP2_TCRST  /*!< Windowing from Timer C compare 2 match to timer C counter reset (TIMWIN2) */
#define HAL_HRTIM_WIN_TIMD_TCCMP1_TCRST  LL_HRTIM_WIN_TIMD_TCCMP1_TCRST  /*!< Windowing from Timer C compare 1 match to timer C compare 2 match (TIMWIN3) */

/* Events from other timing units that can be used as filtering signals for Timer E */
#define HAL_HRTIM_BLK_TIME_TARST_TACMP2  LL_HRTIM_BLK_TIME_TARST_TACMP2  /*!< Blanking from Timer A counter reset to Timer A compare 1 match (TIMFLTR1) */
#define HAL_HRTIM_BLK_TIME_TBRST_TBCMP1  LL_HRTIM_BLK_TIME_TBRST_TBCMP1  /*!< Blanking from Timer B counter reset to Timer B compare 1 match (TIMFLTR2) */
#define HAL_HRTIM_BLK_TIME_TCRST_TCCMP1  LL_HRTIM_BLK_TIME_TCRST_TCCMP1  /*!< Blanking from Timer C counter reset to Timer C compare 1 match (TIMFLTR3) */
#define HAL_HRTIM_BLK_TIME_TFRST_TFCMP4  LL_HRTIM_BLK_TIME_TFRST_TFCMP4  /*!< Blanking from Timer F counter reset to Timer C compare 4 match (TIMFLTR4) */
#define HAL_HRTIM_BLK_TIME_CHF2          LL_HRTIM_BLK_TIME_CHF2          /*!< Blanking is Timer F output 2 (CHF2) waveform (TIMFLTR5) */
#define HAL_HRTIM_BLK_TIME_TDRST_TDCMP1  LL_HRTIM_BLK_TIME_TDRST_TDCMP1  /*!< Blanking from Timer D counter reset to Timer D compare 1 match (TIMFLTR6) */
#define HAL_HRTIM_BLK_TIME_TDRST_TDCMP4  LL_HRTIM_BLK_TIME_TDRST_TDCMP4  /*!< Blanking from Timer D counter reset to Timer D compare 4 match (TIMFLTR7) */
#define HAL_HRTIM_BLK_TIME_CHD2          LL_HRTIM_BLK_TIME_CHD2          /*!< Blanking is Timer F output 2 (CHE2) waveform (TIMFLTR8) */
#define HAL_HRTIM_WIN_TIME_TFRST_TFCMP2  LL_HRTIM_WIN_TIME_TFRST_TFCMP2  /*!< Windowing from timer F counter reset to Timer F compare 2 match (TIMWIN) */
#define HAL_HRTIM_WIN_TIME_TFCMP2_TFRST  LL_HRTIM_WIN_TIME_TFCMP2_TFRST  /*!< Windowing from Timer F compare 2 match to timer F counter reset (TIMWIN2) */
#define HAL_HRTIM_WIN_TIME_TFCMP1_TFRST  LL_HRTIM_WIN_TIME_TFCMP1_TFRST  /*!< Windowing from Timer F compare 1 match to timer F compare 2 match (TIMWIN3) */

/* Events from other timing units that can be used as filtering signals for Timer F */
#define HAL_HRTIM_BLK_TIMF_TARST_TACMP4  LL_HRTIM_BLK_TIMF_TARST_TACMP4  /*!< Blanking from Timer A counter reset to Timer A compare 4 match (TIMFLTR1) */
#define HAL_HRTIM_BLK_TIMF_TBRST_TBCMP2  LL_HRTIM_BLK_TIMF_TBRST_TBCMP2  /*!< Blanking from Timer B counter reset to Timer B compare 2 match (TIMFLTR2) */
#define HAL_HRTIM_BLK_TIMF_TCRST_TCCMP4  LL_HRTIM_BLK_TIMF_TCRST_TCCMP4  /*!< Blanking from Timer C counter reset to Timer C compare 4 match (TIMFLTR3) */
#define HAL_HRTIM_BLK_TIMF_TDRST_TDCMP2  LL_HRTIM_BLK_TIMF_TDRST_TDCMP2  /*!< Blanking from Timer D counter reset to Timer D compare 2 match (TIMFLTR4) */
#define HAL_HRTIM_BLK_TIMF_TDRST_TDCMP4  LL_HRTIM_BLK_TIMF_TDRST_TDCMP4  /*!< Blanking from Timer D counter reset to Timer D compare 2 match (TIMFLTR5) */
#define HAL_HRTIM_BLK_TIMF_TERST_TECMP1  LL_HRTIM_BLK_TIMF_TERST_TECMP1  /*!< Blanking from Timer E counter reset to Timer E compare 1 match (TIMFLTR6) */
#define HAL_HRTIM_BLK_TIMF_TERST_TECMP4  LL_HRTIM_BLK_TIMF_TERST_TECMP4  /*!< Blanking from Timer E counter reset to Timer E compare 4 match (TIMFLTR7) */
#define HAL_HRTIM_BLK_TIMF_CHE2          LL_HRTIM_BLK_TIMF_CHE2          /*!< Blanking is Timer E output 2 (CHE2) waveform (TIMFLTR8) */
#define HAL_HRTIM_WIN_TIMF_TERST_TECMP2  LL_HRTIM_WIN_TIMF_TERST_TECMP2  /*!< Windowing from timer E counter reset to Timer E compare 2 match (TIMWIN) */
#define HAL_HRTIM_WIN_TIMF_TECMP2_TERST  LL_HRTIM_WIN_TIMF_TECMP2_TERST  /*!< Windowing from Timer E compare 2 match to timer E counter reset (TIMWIN2) */
#define HAL_HRTIM_WIN_TIMF_TECMP1_TERST  LL_HRTIM_WIN_TIMF_TECMP1_TERST  /*!< Windowing from Timer E compare 1 match to timer E compare 2 match (TIMWIN3) */
/**
  * @}
  */

/** @defgroup Burst_Mode_Triggers Burst mode (BM) triggers
  * @{
  * @brief Up to 32 events can be combined (ORed) to trigger the burst operation.
  */
#define HAL_HRTIM_BM_TRIGGER_NONE               0x00000000U                          /*!< No trigger */
#define HAL_HRTIM_BM_TRIGGER_MASTER_RESET       LL_HRTIM_BM_TRIG_MASTER_RESET        /*!< The master timer reset and roll-over event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_MASTER_REPETITION  LL_HRTIM_BM_TRIG_MASTER_REPETITION   /*!< The master timer repetition event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_MASTER_CMP1        LL_HRTIM_BM_TRIG_MASTER_CMP1         /*!< The master timer compare 1 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_MASTER_CMP2        LL_HRTIM_BM_TRIG_MASTER_CMP2         /*!< The master timer compare 2 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_MASTER_CMP3        LL_HRTIM_BM_TRIG_MASTER_CMP3         /*!< The master timer compare 3 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_MASTER_CMP4        LL_HRTIM_BM_TRIG_MASTER_CMP4         /*!< The master timer compare 4 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMA_RESET         LL_HRTIM_BM_TRIG_TIMA_RESET          /*!< The Timer A reset or roll-over event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMA_REPETITION    LL_HRTIM_BM_TRIG_TIMA_REPETITION     /*!< The Timer A repetition event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMA_CMP1          LL_HRTIM_BM_TRIG_TIMA_CMP1           /*!< The timer A compare 1 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMA_CMP2          LL_HRTIM_BM_TRIG_TIMA_CMP2           /*!< The timer A compare 2 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMB_RESET         LL_HRTIM_BM_TRIG_TIMB_RESET          /*!< The Timer B reset or roll-over event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMB_REPETITION    LL_HRTIM_BM_TRIG_TIMB_REPETITION     /*!< The Timer B repetition event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMB_CMP1          LL_HRTIM_BM_TRIG_TIMB_CMP1           /*!< The timer B compare 1 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMB_CMP2          LL_HRTIM_BM_TRIG_TIMB_CMP2           /*!< The timer B compare 2 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMC_RESET         LL_HRTIM_BM_TRIG_TIMC_RESET          /*!< The Timer C reset or roll-over event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMC_REPETITION    LL_HRTIM_BM_TRIG_TIMC_REPETITION     /*!< The Timer C repetition event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMC_CMP1          LL_HRTIM_BM_TRIG_TIMC_CMP1           /*!< The timer C compare 1 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMD_RESET         LL_HRTIM_BM_TRIG_TIMD_RESET          /*!< The Timer D reset or roll-over event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMD_REPETITION    LL_HRTIM_BM_TRIG_TIMD_REPETITION     /*!< The Timer D repetition event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMD_CMP2          LL_HRTIM_BM_TRIG_TIMD_CMP2           /*!< The timer D compare 2 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIME_REPETITION    LL_HRTIM_BM_TRIG_TIME_REPETITION     /*!< The Timer E repetition event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIME_CMP1          LL_HRTIM_BM_TRIG_TIME_CMP1           /*!< The timer E compare 1 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIME_CMP2          LL_HRTIM_BM_TRIG_TIME_CMP2           /*!< The timer E compare 2 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMF_RESET         LL_HRTIM_BM_TRIG_TIMF_RESET          /*!< The Timer F reset or roll-over event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMF_REPETITION    LL_HRTIM_BM_TRIG_TIMF_REPETITION     /*!< The Timer F repetition event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMF_CMP1          LL_HRTIM_BM_TRIG_TIMF_CMP1           /*!< The timer F compare 1 event is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMA_EEVG          LL_HRTIM_BM_TRIG_TIMA_EEVG           /*!< The timer A period following an external event G (conditioned by TIMA filters) is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIMD_EEVH          LL_HRTIM_BM_TRIG_TIMD_EEVH           /*!< The timer D period following an external event H (conditioned by TIMD filters) is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_EEVG               LL_HRTIM_BM_TRIG_EEVG                /*!< The external event G conditioned by TIMA filters is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_EEVH               LL_HRTIM_BM_TRIG_EEVH                /*!< The external event H conditioned by TIMD filters is starting the burst mode operation */
#define HAL_HRTIM_BM_TRIGGER_TIM6_TRGO          LL_HRTIM_BM_TRIG_ONCHIP              /*!< A rising edge on the TIM6 trigger output (TRGO) is starting the burst mode operation */
/**
  * @}
  */

/** @defgroup Interrupts Interrupt sources
  * @{
  * @brief Up to 8 interrupts can be combined (ORed) for the whole HRTIM.
  *        Up to 7 interrupts can be combined (ORed) for the master timer.
  *        Up to 14 interrupts can be combined (ORed) for each timer (TIMA..F).
  */
#define HAL_HRTIM_OPT_IT_NONE                (0UL)                      /*!< No interrupts */

#define HAL_HRTIM_OPT_IT_CMP1                LL_HRTIM_MDIER_MCMP1IE     /*!< Master or Timer x (x = A to F) compare 1 interrupt */
#define HAL_HRTIM_OPT_IT_CMP2                LL_HRTIM_MDIER_MCMP2IE     /*!< Master or Timer x (x = A to F) compare 2 interrupt */
#define HAL_HRTIM_OPT_IT_CMP3                LL_HRTIM_MDIER_MCMP3IE     /*!< Master or Timer x (x = A to F) compare 3 interrupt */
#define HAL_HRTIM_OPT_IT_CMP4                LL_HRTIM_MDIER_MCMP4IE     /*!< Master or Timer x (x = A to F) compare 4 interrupt */
#define HAL_HRTIM_OPT_IT_REPETITION          LL_HRTIM_MDIER_MREPIE      /*!< Master or Timer x (x = A to F) repetition interrupt */
#define HAL_HRTIM_OPT_IT_SYNCHRO             LL_HRTIM_MDIER_SYNCIE      /*!< Synchronization input interrupt */
#define HAL_HRTIM_OPT_IT_UPDATE              LL_HRTIM_MDIER_MUPDIE      /*!< Master or Timer x (x = A to F) registers update interrupt */
#define HAL_HRTIM_OPT_IT_CPT1                LL_HRTIM_TIMDIER_CPT1IE    /*!< Timer x (x = A to F) capture 1 interrupt */
#define HAL_HRTIM_OPT_IT_CPT2                LL_HRTIM_TIMDIER_CPT2IE    /*!< Timer x (x = A to F) capture 2 interrupt */
#define HAL_HRTIM_OPT_IT_SET1                LL_HRTIM_TIMDIER_SET1IE    /*!< Timer x (x = A to F) output 1 set interrupt */
#define HAL_HRTIM_OPT_IT_RESET1              LL_HRTIM_TIMDIER_RST1IE    /*!< Timer x (x = A to F) output 1 reset interrupt */
#define HAL_HRTIM_OPT_IT_SET2                LL_HRTIM_TIMDIER_SET2IE    /*!< Timer x (x = A to F) output 2 set  interrupt */
#define HAL_HRTIM_OPT_IT_RESET2              LL_HRTIM_TIMDIER_RST2IE    /*!< Timer x (x = A to F) output 2 reset interrupt */
#define HAL_HRTIM_OPT_IT_RESET               LL_HRTIM_TIMDIER_RSTIE     /*!< Timer x (x = A to F) reset or roll-over interrupt */
#define HAL_HRTIM_OPT_IT_DELAYED_PROT        LL_HRTIM_TIMDIER_DLYPRTIE  /*!< Timer x (x = A to F) delayed protection triggered interrupt */
#define HAL_HRTIM_OPT_IT_XBAR_OVR_TRIGGER    LL_HRTIM_TIMDIER_COTIE     /*!< Timer x (x = A to F) crossbar override trigger interrupt */
#define HAL_HRTIM_OPT_IT_XBAR_OVR_REARM      LL_HRTIM_TIMDIER_CORDEIE   /*!< Timer x (x = A to F) crossbar override rearm delay elapsed interrupt */

#define HAL_HRTIM_OPT_IT_FLT1                LL_HRTIM_IER_FLT1IE        /*!< Fault 1 interrupt */
#define HAL_HRTIM_OPT_IT_FLT2                LL_HRTIM_IER_FLT2IE        /*!< Fault 2 interrupt */
#define HAL_HRTIM_OPT_IT_FLT3                LL_HRTIM_IER_FLT3IE        /*!< Fault 3 interrupt */
#define HAL_HRTIM_OPT_IT_FLT4                LL_HRTIM_IER_FLT4IE        /*!< Fault 4 interrupt */
#define HAL_HRTIM_OPT_IT_FLT5                LL_HRTIM_IER_FLT5IE        /*!< Fault 5 interrupt */
#define HAL_HRTIM_OPT_IT_FLT6                LL_HRTIM_IER_FLT6IE        /*!< Fault 6 interrupt */
#define HAL_HRTIM_OPT_IT_FLT7                LL_HRTIM_IER_FLT7IE        /*!< Fault 7 interrupt */
#define HAL_HRTIM_OPT_IT_FLT8                LL_HRTIM_IER_FLT8IE        /*!< Fault 8 interrupt */
#define HAL_HRTIM_OPT_IT_SYSFLT              LL_HRTIM_IER_SYSFLTIE      /*!< System fault interrupt */
#define HAL_HRTIM_OPT_IT_BURST_MODE_PERIOD   LL_HRTIM_IER_BMPERIE       /*!< Burst mode period completed interrupt */
/**
  * @}
  */

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/** @defgroup DMA_Requests DMA requests
  * @{
  * @brief Up to 8 DMA requests can be combined (ORed) for the master timer.
  *        Up to 14 DMA requests can be combined (ORed) for each timer (TIMA..F).
  */
#define HAL_HRTIM_OPT_DMA_IT_NONE  HAL_DMA_OPT_IT_NONE       /*!< All DMA channel optional interrupts are disabled */
#define HAL_HRTIM_OPT_DMA_IT_HT  HAL_DMA_OPT_IT_HT           /*!< DMA channel half transfer optional interrupt is enabled   */
#define HAL_HRTIM_OPT_DMA_IT_DEFAULT  HAL_DMA_OPT_IT_DEFAULT /*!< All DMA channel optional interrupts are enabled   */

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#define HAL_HRTIM_OPT_DMA_IT_SILENT   HAL_DMA_OPT_IT_SILENT  /*!< All DMA channel interrupts are disabled   */
#endif /* USE_HAL_DMA_LINKEDLIST */

#define HAL_HRTIM_OPT_DMA_NONE               0x0u                        /*!< All DMA requests are disabled */
#define HAL_HRTIM_OPT_DMA_CMP1               LL_HRTIM_MDIER_MCMP1DE      /*!< Master or Timer x (x = A to F) compare 1 DMA request */
#define HAL_HRTIM_OPT_DMA_CMP2               LL_HRTIM_MDIER_MCMP2DE      /*!< Master or Timer x (x = A to F) compare 2 DMA request */
#define HAL_HRTIM_OPT_DMA_CMP3               LL_HRTIM_MDIER_MCMP3DE      /*!< Master or Timer x (x = A to F) compare 3 DMA request */
#define HAL_HRTIM_OPT_DMA_CMP4               LL_HRTIM_MDIER_MCMP4DE      /*!< Master or Timer x (x = A to F) compare 4 DMA request */
#define HAL_HRTIM_OPT_DMA_REPETITION         LL_HRTIM_MDIER_MREPDE       /*!< Master or Timer x (x = A to F) repetition DMA request */
#define HAL_HRTIM_OPT_DMA_SYNCHRO            LL_HRTIM_MDIER_SYNCDE       /*!< Synchronization input DMA request */
#define HAL_HRTIM_OPT_DMA_UPDATE             LL_HRTIM_MDIER_MUPDDE       /*!< Master or Timer x (x = A to F) registers update DMA request */
#define HAL_HRTIM_OPT_DMA_CPT1               LL_HRTIM_TIMDIER_CPT1DE     /*!< Timer x (x = A to F) capture 1 DMA request */
#define HAL_HRTIM_OPT_DMA_CPT2               LL_HRTIM_TIMDIER_CPT2DE     /*!< Timer x (x = A to F) capture 2 DMA request */
#define HAL_HRTIM_OPT_DMA_SET1               LL_HRTIM_TIMDIER_SET1DE     /*!< Timer x (x = A to F) output 1 set DMA request */
#define HAL_HRTIM_OPT_DMA_RESET1             LL_HRTIM_TIMDIER_RST1DE     /*!< Timer x (x = A to F) output 1 reset DMA request */
#define HAL_HRTIM_OPT_DMA_SET2               LL_HRTIM_TIMDIER_SET2DE     /*!< Timer x (x = A to F) output 2 set  DMA request */
#define HAL_HRTIM_OPT_DMA_RESET2             LL_HRTIM_TIMDIER_RST2DE     /*!< Timer x (x = A to F) output 2 reset DMA request */
#define HAL_HRTIM_OPT_DMA_RESET              LL_HRTIM_TIMDIER_RSTDE      /*!< Timer x (x = A to F) reset or roll-over DMA request */
#define HAL_HRTIM_OPT_DMA_DELAYED_PROT       LL_HRTIM_TIMDIER_DLYPRTDE   /*!< Timer x (x = A to F) delayed protection triggered DMA request */
#define HAL_HRTIM_OPT_DMA_XBAR_OVR_TRIGGER   LL_HRTIM_TIMDIER_COTDE      /*!< Timer x (x = A to F) crossbar override trigger DMA request */
#define HAL_HRTIM_OPT_DMA_XBAR_OVR_REARM     LL_HRTIM_TIMDIER_CORDEDE    /*!< Timer x (x = A to F) crossbar override rearm delay elapsed DMA request */

/**
  * @}
  */

#endif /* USE_HAL_HRTIM_DMA */

/** @defgroup Update_Source Preloaded registers update source
  * @{
  * @brief Several update sources can be combined (ORed) for a timer:
  *        - Update done when the counter rolls over and the repetition
  *          counter is equal to 0,
  *        - Update done when the counter is reset or rolls over in
  *          continuous mode,
  *        - Update done synchronously with any other timer or master update.
  */
#define HAL_HRTIM_UPDATE_SOURCE_NONE          LL_HRTIM_UPDATETRIG_NONE           /*!< Update event isn't hardware triggered */
#define HAL_HRTIM_UPDATE_SOURCE_REPETITION    LL_HRTIM_UPDATETRIG_REPETITION     /*!< Update event is triggered by the repetition event */
#define HAL_HRTIM_UPDATE_SOURCE_RESET         LL_HRTIM_UPDATETRIG_RESET          /*!< Update event is triggered by the counter reset or period event */
#define HAL_HRTIM_UPDATE_SOURCE_MASTER_UPDATE LL_HRTIM_UPDATETRIG_MASTER_UPDATE  /*!< Update event is triggered by the master timer update */
#define HAL_HRTIM_UPDATE_SOURCE_TIMA_UPDATE   LL_HRTIM_UPDATETRIG_TIMA_UPDATE    /*!< Update event is triggered by the timer A update */
#define HAL_HRTIM_UPDATE_SOURCE_TIMB_UPDATE   LL_HRTIM_UPDATETRIG_TIMB_UPDATE    /*!< Update event is triggered by the timer B update */
#define HAL_HRTIM_UPDATE_SOURCE_TIMC_UPDATE   LL_HRTIM_UPDATETRIG_TIMC_UPDATE    /*!< Update event is triggered by the timer C update */
#define HAL_HRTIM_UPDATE_SOURCE_TIMD_UPDATE   LL_HRTIM_UPDATETRIG_TIMD_UPDATE    /*!< Update event is triggered by the timer D update */
#define HAL_HRTIM_UPDATE_SOURCE_TIME_UPDATE   LL_HRTIM_UPDATETRIG_TIME_UPDATE    /*!< Update event is triggered by the timer E update */
#define HAL_HRTIM_UPDATE_SOURCE_TIMF_UPDATE   LL_HRTIM_UPDATETRIG_TIMF_UPDATE    /*!< Update event is triggered by the timer F update */
/**
  * @}
  */

/** @defgroup Reset_Triggers Timer (TIMA..F) counter reset triggers
  * @{
  * @brief Up to 30 events can be combined (ORed) to reset the counter of a
  *        timing unit.
  */
#define HAL_HRTIM_RESET_NONE          LL_HRTIM_RESETTRIG_NONE           /*!< No reset trigger */
#define HAL_HRTIM_RESET_UPDATE        LL_HRTIM_RESETTRIG_UPDATE         /*!< The timer counter is reset upon update event */
#define HAL_HRTIM_RESET_CMP2          LL_HRTIM_RESETTRIG_CMP2           /*!< The timer counter is reset upon timer Compare 2 event */
#define HAL_HRTIM_RESET_CMP4          LL_HRTIM_RESETTRIG_CMP4           /*!< The timer counter is reset upon timer Compare 4 event */
#define HAL_HRTIM_RESET_MASTER_PERIOD LL_HRTIM_RESETTRIG_MASTER_PERIOD  /*!< The timer counter is reset upon master timer period event */
#define HAL_HRTIM_RESET_MASTER_CMP1   LL_HRTIM_RESETTRIG_MASTER_CMP1    /*!< The timer counter is reset upon master timer Compare 1 event */
#define HAL_HRTIM_RESET_MASTER_CMP2   LL_HRTIM_RESETTRIG_MASTER_CMP2    /*!< The timer counter is reset upon master timer Compare 2 event */
#define HAL_HRTIM_RESET_MASTER_CMP3   LL_HRTIM_RESETTRIG_MASTER_CMP3    /*!< The timer counter is reset upon master timer Compare 3 event */
#define HAL_HRTIM_RESET_MASTER_CMP4   LL_HRTIM_RESETTRIG_MASTER_CMP4    /*!< The timer counter is reset upon master timer Compare 4 event */
#define HAL_HRTIM_RESET_EEVA          LL_HRTIM_RESETTRIG_EEVA           /*!< The timer counter is reset upon external event A */
#define HAL_HRTIM_RESET_EEVB          LL_HRTIM_RESETTRIG_EEVB           /*!< The timer counter is reset upon external event B */
#define HAL_HRTIM_RESET_EEVC          LL_HRTIM_RESETTRIG_EEVC           /*!< The timer counter is reset upon external event C */
#define HAL_HRTIM_RESET_EEVD          LL_HRTIM_RESETTRIG_EEVD           /*!< The timer counter is reset upon external event D */
#define HAL_HRTIM_RESET_EEVE          LL_HRTIM_RESETTRIG_EEVE           /*!< The timer counter is reset upon external event E */
#define HAL_HRTIM_RESET_EEVF          LL_HRTIM_RESETTRIG_EEVF           /*!< The timer counter is reset upon external event F */
#define HAL_HRTIM_RESET_EEVG          LL_HRTIM_RESETTRIG_EEVG           /*!< The timer counter is reset upon external event G */
#define HAL_HRTIM_RESET_EEVH          LL_HRTIM_RESETTRIG_EEVH           /*!< The timer counter is reset upon external event H */
#define HAL_HRTIM_RESET_EEVI          LL_HRTIM_RESETTRIG_EEVI           /*!< The timer counter is reset upon external event I */
#define HAL_HRTIM_RESET_EEVJ          LL_HRTIM_RESETTRIG_EEVJ           /*!< The timer counter is reset upon external event J */

/* Events from other timing units that can be used to reset Timer A counter */
#define HAL_HRTIM_RESET_TIMA_TBCMP1   LL_HRTIM_RESETTRIG_TIMA_TBCMP1   /*!< The timer A counter is reset upon Timer B compare 1 event */
#define HAL_HRTIM_RESET_TIMA_TBCMP2   LL_HRTIM_RESETTRIG_TIMA_TBCMP2   /*!< The timer A counter is reset upon Timer B compare 2 event */
#define HAL_HRTIM_RESET_TIMA_TBCMP4   LL_HRTIM_RESETTRIG_TIMA_TBCMP4   /*!< The timer A counter is reset upon Timer B compare 4 event */
#define HAL_HRTIM_RESET_TIMA_TCCMP1   LL_HRTIM_RESETTRIG_TIMA_TCCMP1   /*!< The timer A counter is reset upon Timer C compare 1 event */
#define HAL_HRTIM_RESET_TIMA_TCCMP2   LL_HRTIM_RESETTRIG_TIMA_TCCMP2   /*!< The timer A counter is reset upon Timer C compare 2 event */
#define HAL_HRTIM_RESET_TIMA_TCCMP4   LL_HRTIM_RESETTRIG_TIMA_TCCMP4   /*!< The timer A counter is reset upon Timer C compare 4 event */
#define HAL_HRTIM_RESET_TIMA_TDCMP1   LL_HRTIM_RESETTRIG_TIMA_TDCMP1   /*!< The timer A counter is reset upon Timer D compare 1 event */
#define HAL_HRTIM_RESET_TIMA_TDCMP2   LL_HRTIM_RESETTRIG_TIMA_TDCMP2   /*!< The timer A counter is reset upon Timer D compare 2 event */
#define HAL_HRTIM_RESET_TIMA_TDCMP4   LL_HRTIM_RESETTRIG_TIMA_TDCMP4   /*!< The timer A counter is reset upon Timer D compare 4 event */
#define HAL_HRTIM_RESET_TIMA_TECMP1   LL_HRTIM_RESETTRIG_TIMA_TECMP1   /*!< The timer A counter is reset upon Timer E compare 1 event */
#define HAL_HRTIM_RESET_TIMA_TECMP2   LL_HRTIM_RESETTRIG_TIMA_TECMP2   /*!< The timer A counter is reset upon Timer E compare 2 event */
#define HAL_HRTIM_RESET_TIMA_TECMP4   LL_HRTIM_RESETTRIG_TIMA_TECMP4   /*!< The timer A counter is reset upon Timer E compare 4 event */
#define HAL_HRTIM_RESET_TIMA_TFCMP1   LL_HRTIM_RESETTRIG_TIMA_TFCMP1   /*!< The timer A counter is reset upon Timer F compare 1 event */
#define HAL_HRTIM_RESET_TIMA_TFCMP2   LL_HRTIM_RESETTRIG_TIMA_TFCMP2   /*!< The timer A counter is reset upon Timer F compare 2 event */

/* Events from other timing units that can be used to reset Timer B counter */
#define HAL_HRTIM_RESET_TIMB_TACMP1   LL_HRTIM_RESETTRIG_TIMB_TACMP1   /*!< The timer B counter is reset upon Timer A compare 1 event */
#define HAL_HRTIM_RESET_TIMB_TACMP2   LL_HRTIM_RESETTRIG_TIMB_TACMP2   /*!< The timer B counter is reset upon Timer A compare 2 event */
#define HAL_HRTIM_RESET_TIMB_TACMP4   LL_HRTIM_RESETTRIG_TIMB_TACMP4   /*!< The timer B counter is reset upon Timer A compare 4 event */
#define HAL_HRTIM_RESET_TIMB_TCCMP1   LL_HRTIM_RESETTRIG_TIMB_TCCMP1   /*!< The timer B counter is reset upon Timer C compare 1 event */
#define HAL_HRTIM_RESET_TIMB_TCCMP2   LL_HRTIM_RESETTRIG_TIMB_TCCMP2   /*!< The timer B counter is reset upon Timer C compare 2 event */
#define HAL_HRTIM_RESET_TIMB_TCCMP4   LL_HRTIM_RESETTRIG_TIMB_TCCMP4   /*!< The timer B counter is reset upon Timer C compare 4 event */
#define HAL_HRTIM_RESET_TIMB_TDCMP1   LL_HRTIM_RESETTRIG_TIMB_TDCMP1   /*!< The timer B counter is reset upon Timer D compare 1 event */
#define HAL_HRTIM_RESET_TIMB_TDCMP2   LL_HRTIM_RESETTRIG_TIMB_TDCMP2   /*!< The timer B counter is reset upon Timer D compare 2 event */
#define HAL_HRTIM_RESET_TIMB_TDCMP4   LL_HRTIM_RESETTRIG_TIMB_TDCMP4   /*!< The timer B counter is reset upon Timer D compare 4 event */
#define HAL_HRTIM_RESET_TIMB_TECMP1   LL_HRTIM_RESETTRIG_TIMB_TECMP1   /*!< The timer B counter is reset upon Timer E compare 1 event */
#define HAL_HRTIM_RESET_TIMB_TECMP2   LL_HRTIM_RESETTRIG_TIMB_TECMP2   /*!< The timer B counter is reset upon Timer E compare 2 event */
#define HAL_HRTIM_RESET_TIMB_TECMP4   LL_HRTIM_RESETTRIG_TIMB_TECMP4   /*!< The timer B counter is reset upon Timer E compare 4 event */
#define HAL_HRTIM_RESET_TIMB_TFCMP1   LL_HRTIM_RESETTRIG_TIMB_TFCMP1   /*!< The timer B counter is reset upon Timer F compare 1 event */
#define HAL_HRTIM_RESET_TIMB_TFCMP2   LL_HRTIM_RESETTRIG_TIMB_TFCMP2   /*!< The timer B counter is reset upon Timer F compare 2 event */

/* Events from other timing units that can be used to reset Timer C counter */
#define HAL_HRTIM_RESET_TIMC_TACMP1   LL_HRTIM_RESETTRIG_TIMC_TACMP1   /*!< The timer C counter is reset upon Timer A compare 1 event */
#define HAL_HRTIM_RESET_TIMC_TACMP2   LL_HRTIM_RESETTRIG_TIMC_TACMP2   /*!< The timer C counter is reset upon Timer A compare 2 event */
#define HAL_HRTIM_RESET_TIMC_TACMP4   LL_HRTIM_RESETTRIG_TIMC_TACMP4   /*!< The timer C counter is reset upon Timer A compare 4 event */
#define HAL_HRTIM_RESET_TIMC_TBCMP1   LL_HRTIM_RESETTRIG_TIMC_TBCMP1   /*!< The timer C counter is reset upon Timer B compare 1 event */
#define HAL_HRTIM_RESET_TIMC_TBCMP2   LL_HRTIM_RESETTRIG_TIMC_TBCMP2   /*!< The timer C counter is reset upon Timer B compare 2 event */
#define HAL_HRTIM_RESET_TIMC_TBCMP4   LL_HRTIM_RESETTRIG_TIMC_TBCMP4   /*!< The timer C counter is reset upon Timer B compare 4 event */
#define HAL_HRTIM_RESET_TIMC_TDCMP1   LL_HRTIM_RESETTRIG_TIMC_TDCMP1   /*!< The timer C counter is reset upon Timer D compare 1 event */
#define HAL_HRTIM_RESET_TIMC_TDCMP2   LL_HRTIM_RESETTRIG_TIMC_TDCMP2   /*!< The timer C counter is reset upon Timer D compare 2 event */
#define HAL_HRTIM_RESET_TIMC_TDCMP4   LL_HRTIM_RESETTRIG_TIMC_TDCMP4   /*!< The timer C counter is reset upon Timer D compare 4 event */
#define HAL_HRTIM_RESET_TIMC_TECMP1   LL_HRTIM_RESETTRIG_TIMC_TECMP1   /*!< The timer C counter is reset upon Timer E compare 1 event */
#define HAL_HRTIM_RESET_TIMC_TECMP2   LL_HRTIM_RESETTRIG_TIMC_TECMP2   /*!< The timer C counter is reset upon Timer E compare 2 event */
#define HAL_HRTIM_RESET_TIMC_TECMP4   LL_HRTIM_RESETTRIG_TIMC_TECMP4   /*!< The timer C counter is reset upon Timer E compare 4 event */
#define HAL_HRTIM_RESET_TIMC_TFCMP1   LL_HRTIM_RESETTRIG_TIMC_TFCMP1   /*!< The timer C counter is reset upon Timer F compare 1 event */
#define HAL_HRTIM_RESET_TIMC_TFCMP2   LL_HRTIM_RESETTRIG_TIMC_TFCMP2   /*!< The timer C counter is reset upon Timer F compare 2 event */

/* Events from other timing units that can be used to reset Timer D counter */
#define HAL_HRTIM_RESET_TIMD_TACMP1   LL_HRTIM_RESETTRIG_TIMD_TACMP1   /*!< The timer D counter is reset upon Timer A compare 1 event */
#define HAL_HRTIM_RESET_TIMD_TACMP2   LL_HRTIM_RESETTRIG_TIMD_TACMP2   /*!< The timer D counter is reset upon Timer A compare 2 event */
#define HAL_HRTIM_RESET_TIMD_TACMP4   LL_HRTIM_RESETTRIG_TIMD_TACMP4   /*!< The timer D counter is reset upon Timer A compare 4 event */
#define HAL_HRTIM_RESET_TIMD_TBCMP1   LL_HRTIM_RESETTRIG_TIMD_TBCMP1   /*!< The timer D counter is reset upon Timer B compare 1 event */
#define HAL_HRTIM_RESET_TIMD_TBCMP2   LL_HRTIM_RESETTRIG_TIMD_TBCMP2   /*!< The timer D counter is reset upon Timer B compare 2 event */
#define HAL_HRTIM_RESET_TIMD_TBCMP4   LL_HRTIM_RESETTRIG_TIMD_TBCMP4   /*!< The timer D counter is reset upon Timer B compare 4 event */
#define HAL_HRTIM_RESET_TIMD_TCCMP1   LL_HRTIM_RESETTRIG_TIMD_TCCMP1   /*!< The timer D counter is reset upon Timer C compare 1 event */
#define HAL_HRTIM_RESET_TIMD_TCCMP2   LL_HRTIM_RESETTRIG_TIMD_TCCMP2   /*!< The timer D counter is reset upon Timer C compare 2 event */
#define HAL_HRTIM_RESET_TIMD_TCCMP4   LL_HRTIM_RESETTRIG_TIMD_TCCMP4   /*!< The timer D counter is reset upon Timer C compare 4 event */
#define HAL_HRTIM_RESET_TIMD_TECMP1   LL_HRTIM_RESETTRIG_TIMD_TECMP1   /*!< The timer D counter is reset upon Timer E compare 1 event */
#define HAL_HRTIM_RESET_TIMD_TECMP2   LL_HRTIM_RESETTRIG_TIMD_TECMP2   /*!< The timer D counter is reset upon Timer E compare 2 event */
#define HAL_HRTIM_RESET_TIMD_TECMP4   LL_HRTIM_RESETTRIG_TIMD_TECMP4   /*!< The timer D counter is reset upon Timer E compare 4 event */
#define HAL_HRTIM_RESET_TIMD_TFCMP1   LL_HRTIM_RESETTRIG_TIMD_TFCMP1   /*!< The timer D counter is reset upon Timer F compare 1 event */
#define HAL_HRTIM_RESET_TIMD_TFCMP2   LL_HRTIM_RESETTRIG_TIMD_TFCMP2   /*!< The timer D counter is reset upon Timer F compare 2 event */

/* Events from other timing units that can be used to reset Timer E counter */
#define HAL_HRTIM_RESET_TIME_TACMP1   LL_HRTIM_RESETTRIG_TIME_TACMP1   /*!< The timer E counter is reset upon Timer A compare 1 event */
#define HAL_HRTIM_RESET_TIME_TACMP2   LL_HRTIM_RESETTRIG_TIME_TACMP2   /*!< The timer E counter is reset upon Timer A compare 2 event */
#define HAL_HRTIM_RESET_TIME_TACMP4   LL_HRTIM_RESETTRIG_TIME_TACMP4   /*!< The timer E counter is reset upon Timer A compare 4 event */
#define HAL_HRTIM_RESET_TIME_TBCMP1   LL_HRTIM_RESETTRIG_TIME_TBCMP1   /*!< The timer E counter is reset upon Timer B compare 1 event */
#define HAL_HRTIM_RESET_TIME_TBCMP2   LL_HRTIM_RESETTRIG_TIME_TBCMP2   /*!< The timer E counter is reset upon Timer B compare 2 event */
#define HAL_HRTIM_RESET_TIME_TBCMP4   LL_HRTIM_RESETTRIG_TIME_TBCMP4   /*!< The timer E counter is reset upon Timer B compare 4 event */
#define HAL_HRTIM_RESET_TIME_TCCMP1   LL_HRTIM_RESETTRIG_TIME_TCCMP1   /*!< The timer E counter is reset upon Timer C compare 1 event */
#define HAL_HRTIM_RESET_TIME_TCCMP2   LL_HRTIM_RESETTRIG_TIME_TCCMP2   /*!< The timer E counter is reset upon Timer C compare 2 event */
#define HAL_HRTIM_RESET_TIME_TCCMP4   LL_HRTIM_RESETTRIG_TIME_TCCMP4   /*!< The timer E counter is reset upon Timer C compare 4 event */
#define HAL_HRTIM_RESET_TIME_TDCMP1   LL_HRTIM_RESETTRIG_TIME_TDCMP1   /*!< The timer E counter is reset upon Timer D compare 1 event */
#define HAL_HRTIM_RESET_TIME_TDCMP2   LL_HRTIM_RESETTRIG_TIME_TDCMP2   /*!< The timer E counter is reset upon Timer D compare 2 event */
#define HAL_HRTIM_RESET_TIME_TDCMP4   LL_HRTIM_RESETTRIG_TIME_TDCMP4   /*!< The timer E counter is reset upon Timer D compare 4 event */
#define HAL_HRTIM_RESET_TIME_TFCMP1   LL_HRTIM_RESETTRIG_TIME_TFCMP1   /*!< The timer E counter is reset upon Timer F compare 1 event */
#define HAL_HRTIM_RESET_TIME_TFCMP2   LL_HRTIM_RESETTRIG_TIME_TFCMP2   /*!< The timer E counter is reset upon Timer F compare 2 event */

/* Events from other timing units that can be used to reset Timer E counter */
#define HAL_HRTIM_RESET_TIMF_TACMP1   LL_HRTIM_RESETTRIG_TIMF_TACMP1   /*!< The timer F counter is reset upon Timer A compare 1 event */
#define HAL_HRTIM_RESET_TIMF_TACMP2   LL_HRTIM_RESETTRIG_TIMF_TACMP2   /*!< The timer F counter is reset upon Timer A compare 2 event */
#define HAL_HRTIM_RESET_TIMF_TACMP4   LL_HRTIM_RESETTRIG_TIMF_TACMP4   /*!< The timer F counter is reset upon Timer A compare 4 event */
#define HAL_HRTIM_RESET_TIMF_TBCMP1   LL_HRTIM_RESETTRIG_TIMF_TBCMP1   /*!< The timer F counter is reset upon Timer B compare 1 event */
#define HAL_HRTIM_RESET_TIMF_TBCMP2   LL_HRTIM_RESETTRIG_TIMF_TBCMP2   /*!< The timer F counter is reset upon Timer B compare 2 event */
#define HAL_HRTIM_RESET_TIMF_TBCMP4   LL_HRTIM_RESETTRIG_TIMF_TBCMP4   /*!< The timer F counter is reset upon Timer B compare 4 event */
#define HAL_HRTIM_RESET_TIMF_TCCMP1   LL_HRTIM_RESETTRIG_TIMF_TCCMP1   /*!< The timer F counter is reset upon Timer C compare 1 event */
#define HAL_HRTIM_RESET_TIMF_TCCMP2   LL_HRTIM_RESETTRIG_TIMF_TCCMP2   /*!< The timer F counter is reset upon Timer C compare 2 event */
#define HAL_HRTIM_RESET_TIMF_TCCMP4   LL_HRTIM_RESETTRIG_TIMF_TCCMP4   /*!< The timer F counter is reset upon Timer C compare 4 event */
#define HAL_HRTIM_RESET_TIMF_TDCMP1   LL_HRTIM_RESETTRIG_TIMF_TDCMP1   /*!< The timer F counter is reset upon Timer D compare 1 event */
#define HAL_HRTIM_RESET_TIMF_TDCMP2   LL_HRTIM_RESETTRIG_TIMF_TDCMP2   /*!< The timer F counter is reset upon Timer D compare 2 event */
#define HAL_HRTIM_RESET_TIMF_TDCMP4   LL_HRTIM_RESETTRIG_TIMF_TDCMP4   /*!< The timer F counter is reset upon Timer D compare 4 event */
#define HAL_HRTIM_RESET_TIMF_TECMP1   LL_HRTIM_RESETTRIG_TIMF_TECMP1   /*!< The timer F counter is reset upon Timer E compare 1 event */
#define HAL_HRTIM_RESET_TIMF_TECMP2   LL_HRTIM_RESETTRIG_TIMF_TECMP2   /*!< The timer F counter is reset upon Timer E compare 2 event */

/**
  * @}
  */

/** @defgroup Output_Set_Events  Events setting an HRTIM output to its active state
  * @{
  * @brief Up to 31 events can be combined (ORed) to set an HRTIM output.
  */
#define HAL_HRTIM_OUT_SET_NONE          LL_HRTIM_OUTPUTSET_NONE               /*!< No output set event */
#define HAL_HRTIM_OUT_SET_RESYNC        LL_HRTIM_OUTPUTSET_RESYNC             /*!< The timer reset event coming solely from software or SYNC input forces the output to its active state */
#define HAL_HRTIM_OUT_SET_PERIOD        LL_HRTIM_OUTPUTSET_PERIOD             /*!< The timer period event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_UPDATE        LL_HRTIM_OUTPUTSET_UPDATE             /*!< The timer register update event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_CMP1          LL_HRTIM_OUTPUTSET_CMP1               /*!< The timer compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_CMP2          LL_HRTIM_OUTPUTSET_CMP2               /*!< The timer compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_CMP3          LL_HRTIM_OUTPUTSET_CMP3               /*!< The timer compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_CMP4          LL_HRTIM_OUTPUTSET_CMP4               /*!< The timer compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_MASTER_PERIOD LL_HRTIM_OUTPUTSET_MASTER_PERIOD      /*!< The master timer period event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_MASTER_CMP1   LL_HRTIM_OUTPUTSET_MASTER_CMP1        /*!< The master timer compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_MASTER_CMP2   LL_HRTIM_OUTPUTSET_MASTER_CMP2        /*!< The master timer compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_MASTER_CMP3   LL_HRTIM_OUTPUTSET_MASTER_CMP3        /*!< The master timer compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_MASTER_CMP4   LL_HRTIM_OUTPUTSET_MASTER_CMP4        /*!< The master timer compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_EEVA           LL_HRTIM_OUTPUTSET_EEVA               /*!< External event A forces the output to its active state */
#define HAL_HRTIM_OUT_SET_EEVB           LL_HRTIM_OUTPUTSET_EEVB               /*!< External event B forces the output to its active state */
#define HAL_HRTIM_OUT_SET_EEVC           LL_HRTIM_OUTPUTSET_EEVC               /*!< External event C forces the output to its active state */
#define HAL_HRTIM_OUT_SET_EEVD           LL_HRTIM_OUTPUTSET_EEVD               /*!< External event D forces the output to its active state */
#define HAL_HRTIM_OUT_SET_EEVE           LL_HRTIM_OUTPUTSET_EEVE               /*!< External event E forces the output to its active state */
#define HAL_HRTIM_OUT_SET_EEVF           LL_HRTIM_OUTPUTSET_EEVF               /*!< External event F forces the output to its active state */
#define HAL_HRTIM_OUT_SET_EEVG           LL_HRTIM_OUTPUTSET_EEVG               /*!< External event G forces the output to its active state */
#define HAL_HRTIM_OUT_SET_EEVH           LL_HRTIM_OUTPUTSET_EEVH               /*!< External event H forces the output to its active state */
#define HAL_HRTIM_OUT_SET_EEVI           LL_HRTIM_OUTPUTSET_EEVI               /*!< External event I forces the output to its active state */
#define HAL_HRTIM_OUT_SET_EEVJ           LL_HRTIM_OUTPUTSET_EEVJ                /*!< External event J forces the output to its active state */

/* Events from other timing units that can be used to set Timer A outputs */
#define HAL_HRTIM_OUT_SET_TIMA_TBCMP1   LL_HRTIM_OUTPUTSET_TIMA_TBCMP1   /*!< The timer B compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMA_TBCMP2   LL_HRTIM_OUTPUTSET_TIMA_TBCMP2   /*!< The timer B compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMA_TCCMP2   LL_HRTIM_OUTPUTSET_TIMA_TCCMP2   /*!< The timer C compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMA_TCCMP3   LL_HRTIM_OUTPUTSET_TIMA_TCCMP3   /*!< The timer C compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMA_TDCMP1   LL_HRTIM_OUTPUTSET_TIMA_TDCMP1   /*!< The timer D compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMA_TDCMP2   LL_HRTIM_OUTPUTSET_TIMA_TDCMP2   /*!< The timer D compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMA_TECMP3   LL_HRTIM_OUTPUTSET_TIMA_TECMP3   /*!< The timer E compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMA_TECMP4   LL_HRTIM_OUTPUTSET_TIMA_TECMP4   /*!< The timer E compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMA_TFCMP4   LL_HRTIM_OUTPUTSET_TIMA_TFCMP4   /*!< The timer F compare 4 event forces the output to its active state */

/* Events from other timing unitthat can be used to set Timer B outputs */
#define HAL_HRTIM_OUT_SET_TIMB_TACMP1   LL_HRTIM_OUTPUTSET_TIMB_TACMP1   /*!< The timer A compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMB_TACMP2   LL_HRTIM_OUTPUTSET_TIMB_TACMP2   /*!< The timer A compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMB_TCCMP3   LL_HRTIM_OUTPUTSET_TIMB_TCCMP3   /*!< The timer C compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMB_TCCMP4   LL_HRTIM_OUTPUTSET_TIMB_TCCMP4   /*!< The timer C compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMB_TDCMP3   LL_HRTIM_OUTPUTSET_TIMB_TDCMP3   /*!< The timer D compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMB_TDCMP4   LL_HRTIM_OUTPUTSET_TIMB_TDCMP4   /*!< The timer D compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMB_TECMP1   LL_HRTIM_OUTPUTSET_TIMB_TECMP1   /*!< The timer E compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMB_TECMP2   LL_HRTIM_OUTPUTSET_TIMB_TECMP2   /*!< The timer E compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMB_TFCMP3   LL_HRTIM_OUTPUTSET_TIMB_TFCMP3   /*!< The timer F compare 3 event forces the output to its active state */

/* Events from other timing units that can be used to set Timer C outputs */
#define HAL_HRTIM_OUT_SET_TIMC_TACMP2   LL_HRTIM_OUTPUTSET_TIMC_TACMP2   /*!< The timer A compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMC_TACMP3   LL_HRTIM_OUTPUTSET_TIMC_TACMP3   /*!< The timer A compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMC_TBCMP2   LL_HRTIM_OUTPUTSET_TIMC_TBCMP2   /*!< The timer B compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMC_TBCMP3   LL_HRTIM_OUTPUTSET_TIMC_TBCMP3   /*!< The timer B compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMC_TDCMP2   LL_HRTIM_OUTPUTSET_TIMC_TDCMP2   /*!< The timer D compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMC_TDCMP4   LL_HRTIM_OUTPUTSET_TIMC_TDCMP4   /*!< The timer D compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMC_TECMP3   LL_HRTIM_OUTPUTSET_TIMC_TECMP3   /*!< The timer E compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMC_TECMP4   LL_HRTIM_OUTPUTSET_TIMC_TECMP4   /*!< The timer E compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMC_TFCMP2   LL_HRTIM_OUTPUTSET_TIMC_TFCMP2   /*!< The timer F compare 2 event forces the output to its active state */

/* Events from other timing units that can be used to set Timer D outputs */
#define HAL_HRTIM_OUT_SET_TIMD_TACMP1   LL_HRTIM_OUTPUTSET_TIMD_TACMP1   /*!< The timer A compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMD_TACMP4   LL_HRTIM_OUTPUTSET_TIMD_TACMP4   /*!< The timer A compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMD_TBCMP2   LL_HRTIM_OUTPUTSET_TIMD_TBCMP2   /*!< The timer B compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMD_TBCMP4   LL_HRTIM_OUTPUTSET_TIMD_TBCMP4   /*!< The timer B compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMD_TCCMP4   LL_HRTIM_OUTPUTSET_TIMD_TCCMP4   /*!< The timer C compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMD_TECMP1   LL_HRTIM_OUTPUTSET_TIMD_TECMP1   /*!< The timer E compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMD_TECMP4   LL_HRTIM_OUTPUTSET_TIMD_TECMP4   /*!< The timer E compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMD_TFCMP1   LL_HRTIM_OUTPUTSET_TIMD_TFCMP1   /*!< The timer F compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMD_TFCMP3   LL_HRTIM_OUTPUTSET_TIMD_TFCMP3   /*!< The timer F compare 3 event forces the output to its active state */

/* Events from other timing units that can be used to set Timer E outputs */
#define HAL_HRTIM_OUT_SET_TIME_TACMP4   LL_HRTIM_OUTPUTSET_TIME_TACMP4   /*!< The timer A compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIME_TBCMP3   LL_HRTIM_OUTPUTSET_TIME_TBCMP3   /*!< The timer B compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIME_TBCMP4   LL_HRTIM_OUTPUTSET_TIME_TBCMP4   /*!< The timer B compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIME_TCCMP1   LL_HRTIM_OUTPUTSET_TIME_TCCMP1   /*!< The timer C compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIME_TCCMP2   LL_HRTIM_OUTPUTSET_TIME_TCCMP2   /*!< The timer C compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIME_TDCMP1   LL_HRTIM_OUTPUTSET_TIME_TDCMP1   /*!< The timer D compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIME_TDCMP2   LL_HRTIM_OUTPUTSET_TIME_TDCMP2   /*!< The timer D compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIME_TFCMP3   LL_HRTIM_OUTPUTSET_TIME_TFCMP3   /*!< The timer F compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIME_TFCMP4   LL_HRTIM_OUTPUTSET_TIME_TFCMP4   /*!< The timer F compare 4 event forces the output to its active state */

/* Events from other timing units that can be used to set Timer F outputs */
#define HAL_HRTIM_OUT_SET_TIMF_TACMP3   LL_HRTIM_OUTPUTSET_TIMF_TACMP3   /*!< The timer A compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMF_TBCMP1   LL_HRTIM_OUTPUTSET_TIMF_TBCMP1   /*!< The timer B compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMF_TBCMP4   LL_HRTIM_OUTPUTSET_TIMF_TBCMP4   /*!< The timer B compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMF_TCCMP1   LL_HRTIM_OUTPUTSET_TIMF_TCCMP1   /*!< The timer C compare 1 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMF_TCCMP4   LL_HRTIM_OUTPUTSET_TIMF_TCCMP4   /*!< The timer C compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMF_TDCMP3   LL_HRTIM_OUTPUTSET_TIMF_TDCMP3   /*!< The timer D compare 3 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMF_TDCMP4   LL_HRTIM_OUTPUTSET_TIMF_TDCMP4   /*!< The timer D compare 4 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMF_TECMP2   LL_HRTIM_OUTPUTSET_TIMF_TECMP2   /*!< The timer E compare 2 event forces the output to its active state */
#define HAL_HRTIM_OUT_SET_TIMF_TECMP3   LL_HRTIM_OUTPUTSET_TIMF_TECMP3   /*!< The timer F compare 3 event forces the output to its active state */

/**
  * @}
  */

/** @defgroup Output_Reset_Events  Events setting an HRTIM output to its inactive state
  * @{
  * @brief Up to 31 events can be combined (ORed) to reset an HRTIM output.
  */
#define HAL_HRTIM_OUT_RESET_NONE          HAL_HRTIM_OUT_SET_NONE          /*!< No output reset event */
#define HAL_HRTIM_OUT_RESET_RESYNC        HAL_HRTIM_OUT_SET_RESYNC        /*!< The timer reset event coming solely from software or SYNC input forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_PERIOD        HAL_HRTIM_OUT_SET_PERIOD        /*!< The timer period event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_UPDATE        HAL_HRTIM_OUT_SET_UPDATE        /*!< The timer register update event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_CMP1          HAL_HRTIM_OUT_SET_CMP1          /*!< The timer compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_CMP2          HAL_HRTIM_OUT_SET_CMP2          /*!< The timer compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_CMP3          HAL_HRTIM_OUT_SET_CMP3          /*!< The timer compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_CMP4          HAL_HRTIM_OUT_SET_CMP4          /*!< The timer compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_MASTER_PERIOD HAL_HRTIM_OUT_SET_MASTER_PERIOD /*!< The master timer period event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_MASTER_CMP1   HAL_HRTIM_OUT_SET_MASTER_CMP1   /*!< The master timer compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_MASTER_CMP2   HAL_HRTIM_OUT_SET_MASTER_CMP2   /*!< The master timer compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_MASTER_CMP3   HAL_HRTIM_OUT_SET_MASTER_CMP3   /*!< The master timer compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_MASTER_CMP4   HAL_HRTIM_OUT_SET_MASTER_CMP4   /*!< The master timer compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_EEVA           HAL_HRTIM_OUT_SET_EEVA           /*!< External event A forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_EEVB           HAL_HRTIM_OUT_SET_EEVB           /*!< External event B forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_EEVC           HAL_HRTIM_OUT_SET_EEVC           /*!< External event C forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_EEVD           HAL_HRTIM_OUT_SET_EEVD           /*!< External event D forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_EEVE           HAL_HRTIM_OUT_SET_EEVE           /*!< External event E forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_EEVF           HAL_HRTIM_OUT_SET_EEVF           /*!< External event F forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_EEVG           HAL_HRTIM_OUT_SET_EEVG           /*!< External event G forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_EEVH           HAL_HRTIM_OUT_SET_EEVH           /*!< External event H forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_EEVI           HAL_HRTIM_OUT_SET_EEVI           /*!< External event I forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_EEVJ           HAL_HRTIM_OUT_SET_EEVJ           /*!< External event J forces the output to its inactive state */

/* Events from other timing units that ca n be used to reset Timer A outputs */
#define HAL_HRTIM_OUT_RESET_TIMA_TBCMP1   HAL_HRTIM_OUT_SET_TIMA_TBCMP1   /*!< The timer B compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMA_TBCMP2   HAL_HRTIM_OUT_SET_TIMA_TBCMP2   /*!< The timer B compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMA_TCCMP2   HAL_HRTIM_OUT_SET_TIMA_TCCMP2   /*!< The timer C compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMA_TCCMP3   HAL_HRTIM_OUT_SET_TIMA_TCCMP3   /*!< The timer C compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMA_TDCMP1   HAL_HRTIM_OUT_SET_TIMA_TDCMP1   /*!< The timer D compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMA_TDCMP2   HAL_HRTIM_OUT_SET_TIMA_TDCMP2   /*!< The timer D compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMA_TECMP3   HAL_HRTIM_OUT_SET_TIMA_TECMP3   /*!< The timer E compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMA_TECMP4   HAL_HRTIM_OUT_SET_TIMA_TECMP4   /*!< The timer E compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMA_TFCMP4   HAL_HRTIM_OUT_SET_TIMA_TFCMP4   /*!< The timer F compare 4 event forces the output to its inactive state */

/* Events from other timing units that can be used to reset Timer B outputs */
#define HAL_HRTIM_OUT_RESET_TIMB_TACMP1   HAL_HRTIM_OUT_SET_TIMB_TACMP1   /*!< The timer A compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMB_TACMP2   HAL_HRTIM_OUT_SET_TIMB_TACMP2   /*!< The timer A compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMB_TCCMP3   HAL_HRTIM_OUT_SET_TIMB_TCCMP3   /*!< The timer C compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMB_TCCMP4   HAL_HRTIM_OUT_SET_TIMB_TCCMP4   /*!< The timer C compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMB_TDCMP3   HAL_HRTIM_OUT_SET_TIMB_TDCMP3   /*!< The timer D compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMB_TDCMP4   HAL_HRTIM_OUT_SET_TIMB_TDCMP4   /*!< The timer D compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMB_TECMP1   HAL_HRTIM_OUT_SET_TIMB_TECMP1   /*!< The timer E compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMB_TECMP2   HAL_HRTIM_OUT_SET_TIMB_TECMP2   /*!< The timer E compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMB_TFCMP3   HAL_HRTIM_OUT_SET_TIMB_TFCMP3   /*!< The timer F compare 3 event forces the output to its inactive state */

/* Events from other timing units that can be used to reset Timer C outputs */
#define HAL_HRTIM_OUT_RESET_TIMC_TACMP2   HAL_HRTIM_OUT_SET_TIMC_TACMP2   /*!< The timer A compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMC_TACMP3   HAL_HRTIM_OUT_SET_TIMC_TACMP3   /*!< The timer A compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMC_TBCMP2   HAL_HRTIM_OUT_SET_TIMC_TBCMP2   /*!< The timer B compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMC_TBCMP3   HAL_HRTIM_OUT_SET_TIMC_TBCMP3   /*!< The timer B compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMC_TDCMP2   HAL_HRTIM_OUT_SET_TIMC_TDCMP2   /*!< The timer D compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMC_TDCMP4   HAL_HRTIM_OUT_SET_TIMC_TDCMP4   /*!< The timer D compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMC_TECMP3   HAL_HRTIM_OUT_SET_TIMC_TECMP3   /*!< The timer E compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMC_TECMP4   HAL_HRTIM_OUT_SET_TIMC_TECMP4   /*!< The timer E compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMC_TFCMP2   HAL_HRTIM_OUT_SET_TIMC_TFCMP2   /*!< The timer F compare 2 event forces the output to its inactive state */

/* Events from other timing units that can be used to reset Timer D outputs */
#define HAL_HRTIM_OUT_RESET_TIMD_TACMP1   HAL_HRTIM_OUT_SET_TIMD_TACMP1   /*!< The timer A compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMD_TACMP4   HAL_HRTIM_OUT_SET_TIMD_TACMP4   /*!< The timer A compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMD_TBCMP2   HAL_HRTIM_OUT_SET_TIMD_TBCMP2   /*!< The timer B compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMD_TBCMP4   HAL_HRTIM_OUT_SET_TIMD_TBCMP4   /*!< The timer B compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMD_TCCMP4   HAL_HRTIM_OUT_SET_TIMD_TCCMP4   /*!< The timer C compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMD_TECMP1   HAL_HRTIM_OUT_SET_TIMD_TECMP1   /*!< The timer E compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMD_TECMP4   HAL_HRTIM_OUT_SET_TIMD_TECMP4   /*!< The timer E compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMD_TFCMP1   HAL_HRTIM_OUT_SET_TIMD_TFCMP1   /*!< The timer F compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMD_TFCMP3   HAL_HRTIM_OUT_SET_TIMD_TFCMP3   /*!< The timer F compare 3 event forces the output to its inactive state */

/* Events from other timing units that can be used to reset Timer E outputs */
#define HAL_HRTIM_OUT_RESET_TIME_TACMP4   HAL_HRTIM_OUT_SET_TIME_TACMP4   /*!< The timer A compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIME_TBCMP3   HAL_HRTIM_OUT_SET_TIME_TBCMP3   /*!< The timer B compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIME_TBCMP4   HAL_HRTIM_OUT_SET_TIME_TBCMP4   /*!< The timer B compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIME_TCCMP1   HAL_HRTIM_OUT_SET_TIME_TCCMP1   /*!< The timer C compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIME_TCCMP2   HAL_HRTIM_OUT_SET_TIME_TCCMP2   /*!< The timer C compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIME_TDCMP1   HAL_HRTIM_OUT_SET_TIME_TDCMP1   /*!< The timer D compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIME_TDCMP2   HAL_HRTIM_OUT_SET_TIME_TDCMP2   /*!< The timer D compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIME_TFCMP3   HAL_HRTIM_OUT_SET_TIME_TFCMP3   /*!< The timer F compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIME_TFCMP4   HAL_HRTIM_OUT_SET_TIME_TFCMP4   /*!< The timer F compare 4 event forces the output to its inactive state */

/* Events from other timing units that can be used to reset Timer F outputs */
#define HAL_HRTIM_OUT_RESET_TIMF_TACMP3   HAL_HRTIM_OUT_SET_TIMF_TACMP3   /*!< The timer A compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMF_TBCMP1   HAL_HRTIM_OUT_SET_TIMF_TBCMP1   /*!< The timer B compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMF_TBCMP4   HAL_HRTIM_OUT_SET_TIMF_TBCMP4   /*!< The timer B compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMF_TCCMP1   HAL_HRTIM_OUT_SET_TIMF_TCCMP1   /*!< The timer C compare 1 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMF_TCCMP4   HAL_HRTIM_OUT_SET_TIMF_TCCMP4   /*!< The timer C compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMF_TDCMP3   HAL_HRTIM_OUT_SET_TIMF_TDCMP3   /*!< The timer D compare 3 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMF_TDCMP4   HAL_HRTIM_OUT_SET_TIMF_TDCMP4   /*!< The timer D compare 4 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMF_TECMP2   HAL_HRTIM_OUT_SET_TIMF_TECMP2   /*!< The timer E compare 2 event forces the output to its inactive state */
#define HAL_HRTIM_OUT_RESET_TIMF_TECMP3   HAL_HRTIM_OUT_SET_TIMF_TECMP3   /*!< The timer F compare 3 event forces the output to its inactive state */
/**
  * @}
  */

/** @defgroup Capture triggers  Events triggering a capture
  * @{
  * @brief Up to 28 events can be combined (ORed) to trigger a capture.
  */
#define HAL_HRTIM_CAPTURE_NONE            0x0U                            /*!< No capture triggered */
#define HAL_HRTIM_CAPTURE_UPDATE          LL_HRTIM_CAPTURETRIG_UPDATE     /*!< The update event triggers the capture */
#define HAL_HRTIM_CAPTURE_EEVA            LL_HRTIM_CAPTURETRIG_EEVA       /*!< External event A triggers the capture */
#define HAL_HRTIM_CAPTURE_EEVB            LL_HRTIM_CAPTURETRIG_EEVB       /*!< External event B triggers the capture */
#define HAL_HRTIM_CAPTURE_EEVC            LL_HRTIM_CAPTURETRIG_EEVC       /*!< External event C triggers the capture */
#define HAL_HRTIM_CAPTURE_EEVD            LL_HRTIM_CAPTURETRIG_EEVD       /*!< External event D triggers the capture */
#define HAL_HRTIM_CAPTURE_EEVE            LL_HRTIM_CAPTURETRIG_EEVE       /*!< External event E triggers the capture */
#define HAL_HRTIM_CAPTURE_EEVF            LL_HRTIM_CAPTURETRIG_EEVF       /*!< External event F triggers the capture */
#define HAL_HRTIM_CAPTURE_EEVG            LL_HRTIM_CAPTURETRIG_EEVG       /*!< External event G triggers the capture */
#define HAL_HRTIM_CAPTURE_EEVH            LL_HRTIM_CAPTURETRIG_EEVH       /*!< External event H triggers the capture */
#define HAL_HRTIM_CAPTURE_EEVI            LL_HRTIM_CAPTURETRIG_EEVI       /*!< External event I triggers the capture */
#define HAL_HRTIM_CAPTURE_EEVJ            LL_HRTIM_CAPTURETRIG_EEVJ       /*!< External event J triggers the capture */

/* Events from other timing units that can be used to trigger a capture on Timer A */
#define HAL_HRTIM_CAPTURE_TIMA_CHB1_SET   LL_HRTIM_CAPTURETRIG_TIMA_CHB1_SET    /*!< CHB1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_CHB1_RESET LL_HRTIM_CAPTURETRIG_TIMA_CHB1_RESET  /*!< CHB1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_TBCMP1     LL_HRTIM_CAPTURETRIG_TIMA_TBCMP1      /*!< The timer B compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_TBCMP2     LL_HRTIM_CAPTURETRIG_TIMA_TBCMP2      /*!< The timer B compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_CHC1_SET   LL_HRTIM_CAPTURETRIG_TIMA_CHC1_SET    /*!< CHC1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_CHC1_RESET LL_HRTIM_CAPTURETRIG_TIMA_CHC1_RESET  /*!< CHC1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_TCCMP1     LL_HRTIM_CAPTURETRIG_TIMA_TCCMP1      /*!< The timer C compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_TCCMP2     LL_HRTIM_CAPTURETRIG_TIMA_TCCMP2      /*!< The timer C compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_CHD1_SET   LL_HRTIM_CAPTURETRIG_TIMA_CHD1_SET    /*!< CHD1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_CHD1_RESET LL_HRTIM_CAPTURETRIG_TIMA_CHD1_RESET  /*!< CHD1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_TDCMP1     LL_HRTIM_CAPTURETRIG_TIMA_TDCMP1      /*!< The timer D compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_TDCMP2     LL_HRTIM_CAPTURETRIG_TIMA_TDCMP2      /*!< The timer D compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_CHE1_SET   LL_HRTIM_CAPTURETRIG_TIMA_CHE1_SET    /*!< CHE1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_CHE1_RESET LL_HRTIM_CAPTURETRIG_TIMA_CHE1_RESET  /*!< CHE1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_TECMP1     LL_HRTIM_CAPTURETRIG_TIMA_TECMP1      /*!< The timer E compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_TECMP2     LL_HRTIM_CAPTURETRIG_TIMA_TECMP2      /*!< The timer E compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_CHF1_SET   LL_HRTIM_CAPTURETRIG_TIMA_CHF1_SET    /*!< CHF1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_CHF1_RESET LL_HRTIM_CAPTURETRIG_TIMA_CHF1_RESET  /*!< CHF1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_TFCMP1     LL_HRTIM_CAPTURETRIG_TIMA_TFCMP1      /*!< The timer F compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMA_TFCMP2     LL_HRTIM_CAPTURETRIG_TIMA_TFCMP2      /*!< The timer F compare 2 event triggers the capture */

/* Events from other timing units that can be used to trigger a capture on Timer B */
#define HAL_HRTIM_CAPTURE_TIMB_CHA1_SET   LL_HRTIM_CAPTURETRIG_TIMB_CHA1_SET    /*!< CHA1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_CHA1_RESET LL_HRTIM_CAPTURETRIG_TIMB_CHA1_RESET  /*!< CHA1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_TACMP1     LL_HRTIM_CAPTURETRIG_TIMB_TACMP1      /*!< The timer A compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_TACMP2     LL_HRTIM_CAPTURETRIG_TIMB_TACMP2      /*!< The timer A compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_CHC1_SET   LL_HRTIM_CAPTURETRIG_TIMB_CHC1_SET    /*!< CHC1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_CHC1_RESET LL_HRTIM_CAPTURETRIG_TIMB_CHC1_RESET  /*!< CHC1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_TCCMP1     LL_HRTIM_CAPTURETRIG_TIMB_TCCMP1      /*!< The timer C compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_TCCMP2     LL_HRTIM_CAPTURETRIG_TIMB_TCCMP2      /*!< The timer C compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_CHD1_SET   LL_HRTIM_CAPTURETRIG_TIMB_CHD1_SET    /*!< CHD1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_CHD1_RESET LL_HRTIM_CAPTURETRIG_TIMB_CHD1_RESET  /*!< CHD1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_TDCMP1     LL_HRTIM_CAPTURETRIG_TIMB_TDCMP1      /*!< The timer D compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_TDCMP2     LL_HRTIM_CAPTURETRIG_TIMB_TDCMP2      /*!< The timer D compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_CHE1_SET   LL_HRTIM_CAPTURETRIG_TIMB_CHE1_SET    /*!< CHE1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_CHE1_RESET LL_HRTIM_CAPTURETRIG_TIMB_CHE1_RESET  /*!< CHE1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_TECMP1     LL_HRTIM_CAPTURETRIG_TIMB_TECMP1      /*!< The timer E compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_TECMP2     LL_HRTIM_CAPTURETRIG_TIMB_TECMP2      /*!< The timer E compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_CHF1_SET   LL_HRTIM_CAPTURETRIG_TIMB_CHF1_SET    /*!< CHF1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_CHF1_RESET LL_HRTIM_CAPTURETRIG_TIMB_CHF1_RESET  /*!< CHF1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_TFCMP1     LL_HRTIM_CAPTURETRIG_TIMB_TFCMP1      /*!< The timer F compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMB_TFCMP2     LL_HRTIM_CAPTURETRIG_TIMB_TFCMP2       /*!< The timer F compare 2 event triggers the capture */

/* Events from other timing units that can be used to trigger a capture on Timer C */
#define HAL_HRTIM_CAPTURE_TIMC_CHA1_SET   LL_HRTIM_CAPTURETRIG_TIMC_CHA1_SET    /*!< CHA1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_CHA1_RESET LL_HRTIM_CAPTURETRIG_TIMC_CHA1_RESET  /*!< CHA1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_TACMP1     LL_HRTIM_CAPTURETRIG_TIMC_TACMP1      /*!< The timer A compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_TACMP2     LL_HRTIM_CAPTURETRIG_TIMC_TACMP2      /*!< The timer A compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_CHB1_SET   LL_HRTIM_CAPTURETRIG_TIMC_CHB1_SET    /*!< CHB1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_CHB1_RESET LL_HRTIM_CAPTURETRIG_TIMC_CHB1_RESET  /*!< CHB1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_TBCMP1     LL_HRTIM_CAPTURETRIG_TIMC_TBCMP1      /*!< The timer B compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_TBCMP2     LL_HRTIM_CAPTURETRIG_TIMC_TBCMP2      /*!< The timer B compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_CHD1_SET   LL_HRTIM_CAPTURETRIG_TIMC_CHD1_SET    /*!< CHD1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_CHD1_RESET LL_HRTIM_CAPTURETRIG_TIMC_CHD1_RESET  /*!< CHD1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_TDCMP1     LL_HRTIM_CAPTURETRIG_TIMC_TDCMP1      /*!< The timer D compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_TDCMP2     LL_HRTIM_CAPTURETRIG_TIMC_TDCMP2      /*!< The timer D compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_CHE1_SET   LL_HRTIM_CAPTURETRIG_TIMC_CHE1_SET    /*!< CHE1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_CHE1_RESET LL_HRTIM_CAPTURETRIG_TIMC_CHE1_RESET  /*!< CHE1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_TECMP1     LL_HRTIM_CAPTURETRIG_TIMC_TECMP1      /*!< The timer E compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_TECMP2     LL_HRTIM_CAPTURETRIG_TIMC_TECMP2      /*!< The timer E compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_CHF1_SET   LL_HRTIM_CAPTURETRIG_TIMC_CHF1_SET    /*!< CHF1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_CHF1_RESET LL_HRTIM_CAPTURETRIG_TIMC_CHF1_RESET  /*!< CHF1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_TFCMP1     LL_HRTIM_CAPTURETRIG_TIMC_TFCMP1      /*!< The timer F compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMC_TFCMP2     LL_HRTIM_CAPTURETRIG_TIMC_TFCMP2      /*!< The timer F compare 2 event triggers the capture */

/* Events from other timing units that can be used to trigger a capture on Timer D */
#define HAL_HRTIM_CAPTURE_TIMD_CHA1_SET   LL_HRTIM_CAPTURETRIG_TIMD_CHA1_SET    /*!< CHA1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_CHA1_RESET LL_HRTIM_CAPTURETRIG_TIMD_CHA1_RESET  /*!< CHA1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_TACMP1     LL_HRTIM_CAPTURETRIG_TIMD_TACMP1      /*!< The timer A compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_TACMP2     LL_HRTIM_CAPTURETRIG_TIMD_TACMP2      /*!< The timer A compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_CHB1_SET   LL_HRTIM_CAPTURETRIG_TIMD_CHB1_SET    /*!< CHB1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_CHB1_RESET LL_HRTIM_CAPTURETRIG_TIMD_CHB1_RESET  /*!< CHB1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_TBCMP1     LL_HRTIM_CAPTURETRIG_TIMD_TBCMP1      /*!< The timer B compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_TBCMP2     LL_HRTIM_CAPTURETRIG_TIMD_TBCMP2      /*!< The timer B compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_CHC1_SET   LL_HRTIM_CAPTURETRIG_TIMD_CHC1_SET    /*!< CHC1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_CHC1_RESET LL_HRTIM_CAPTURETRIG_TIMD_CHC1_RESET  /*!< CHC1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_TCCMP1     LL_HRTIM_CAPTURETRIG_TIMD_TCCMP1      /*!< The timer C compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_TCCMP2     LL_HRTIM_CAPTURETRIG_TIMD_TCCMP2      /*!< The timer C compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_CHE1_SET   LL_HRTIM_CAPTURETRIG_TIMD_CHE1_SET    /*!< CHE1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_CHE1_RESET LL_HRTIM_CAPTURETRIG_TIMD_CHE1_RESET  /*!< CHE1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_TECMP1     LL_HRTIM_CAPTURETRIG_TIMD_TECMP1      /*!< The timer E compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_TECMP2     LL_HRTIM_CAPTURETRIG_TIMD_TECMP2      /*!< The timer E compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_CHF1_SET   LL_HRTIM_CAPTURETRIG_TIMD_CHF1_SET    /*!< CHF1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_CHF1_RESET LL_HRTIM_CAPTURETRIG_TIMD_CHF1_RESET  /*!< CHF1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_TFCMP1     LL_HRTIM_CAPTURETRIG_TIMD_TFCMP1      /*!< The timer F compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMD_TFCMP2     LL_HRTIM_CAPTURETRIG_TIMD_TFCMP2      /*!< The timer F compare 2 event triggers the capture */

/* Events from other timing units that can be used to trigger a capture on Timer E */
#define HAL_HRTIM_CAPTURE_TIME_CHA1_SET   LL_HRTIM_CAPTURETRIG_TIME_CHA1_SET    /*!< CHA1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_CHA1_RESET LL_HRTIM_CAPTURETRIG_TIME_CHA1_RESET  /*!< CHA1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_TACMP1     LL_HRTIM_CAPTURETRIG_TIME_TACMP1      /*!< The timer A compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_TACMP2     LL_HRTIM_CAPTURETRIG_TIME_TACMP2      /*!< The timer A compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_CHB1_SET   LL_HRTIM_CAPTURETRIG_TIME_CHB1_SET    /*!< CHB1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_CHB1_RESET LL_HRTIM_CAPTURETRIG_TIME_CHB1_RESET  /*!< CHB1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_TBCMP1     LL_HRTIM_CAPTURETRIG_TIME_TBCMP1      /*!< The timer B compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_TBCMP2     LL_HRTIM_CAPTURETRIG_TIME_TBCMP2      /*!< The timer B compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_CHC1_SET   LL_HRTIM_CAPTURETRIG_TIME_CHC1_SET    /*!< CHC1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_CHC1_RESET LL_HRTIM_CAPTURETRIG_TIME_CHC1_RESET  /*!< CHC1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_TCCMP1     LL_HRTIM_CAPTURETRIG_TIME_TCCMP1      /*!< The timer C compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_TCCMP2     LL_HRTIM_CAPTURETRIG_TIME_TCCMP2      /*!< The timer C compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_CHD1_SET   LL_HRTIM_CAPTURETRIG_TIME_CHD1_SET    /*!< CHD1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_CHD1_RESET LL_HRTIM_CAPTURETRIG_TIME_CHD1_RESET  /*!< CHD1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_TDCMP1     LL_HRTIM_CAPTURETRIG_TIME_TDCMP1      /*!< The timer D compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_TDCMP2     LL_HRTIM_CAPTURETRIG_TIME_TDCMP2      /*!< The timer D compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_CHF1_SET   LL_HRTIM_CAPTURETRIG_TIME_CHF1_SET    /*!< CHF1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_CHF1_RESET LL_HRTIM_CAPTURETRIG_TIME_CHF1_RESET  /*!< CHF1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_TFCMP1     LL_HRTIM_CAPTURETRIG_TIME_TFCMP1      /*!< The timer F compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIME_TFCMP2     LL_HRTIM_CAPTURETRIG_TIME_TFCMP2      /*!< The timer F compare 2 event triggers the capture */

/* Events from other timing units that can be used to trigger a capture on Timer F */
#define HAL_HRTIM_CAPTURE_TIMF_CHA1_SET   LL_HRTIM_CAPTURETRIG_TIMF_CHA1_SET    /*!< CHA1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_CHA1_RESET LL_HRTIM_CAPTURETRIG_TIMF_CHA1_RESET  /*!< CHA1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_TACMP1     LL_HRTIM_CAPTURETRIG_TIMF_TACMP1      /*!< The timer A compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_TACMP2     LL_HRTIM_CAPTURETRIG_TIMF_TACMP2      /*!< The timer A compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_CHB1_SET   LL_HRTIM_CAPTURETRIG_TIMF_CHB1_SET    /*!< CHB1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_CHB1_RESET LL_HRTIM_CAPTURETRIG_TIMF_CHB1_RESET  /*!< CHB1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_TBCMP1     LL_HRTIM_CAPTURETRIG_TIMF_TBCMP1      /*!< The timer B compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_TBCMP2     LL_HRTIM_CAPTURETRIG_TIMF_TBCMP2      /*!< The timer B compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_CHC1_SET   LL_HRTIM_CAPTURETRIG_TIMF_CHC1_SET    /*!< CHC1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_CHC1_RESET LL_HRTIM_CAPTURETRIG_TIMF_CHC1_RESET  /*!< CHC1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_TCCMP1     LL_HRTIM_CAPTURETRIG_TIMF_TCCMP1      /*!< The timer C compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_TCCMP2     LL_HRTIM_CAPTURETRIG_TIMF_TCCMP2      /*!< The timer C compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_CHD1_SET   LL_HRTIM_CAPTURETRIG_TIMF_CHD1_SET    /*!< CHD1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_CHD1_RESET LL_HRTIM_CAPTURETRIG_TIMF_CHD1_RESET  /*!< CHD1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_TDCMP1     LL_HRTIM_CAPTURETRIG_TIMF_TDCMP1      /*!< The timer D compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_TDCMP2     LL_HRTIM_CAPTURETRIG_TIMF_TDCMP2      /*!< The timer D compare 2 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_CHE1_SET   LL_HRTIM_CAPTURETRIG_TIMF_CHE1_SET    /*!< CHE1 output inactive to active transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_CHE1_RESET LL_HRTIM_CAPTURETRIG_TIMF_CHE1_RESET  /*!< CHE1 output active to inactive transition triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_TECMP1     LL_HRTIM_CAPTURETRIG_TIMF_TECMP1      /*!< The timer E compare 1 event triggers the capture */
#define HAL_HRTIM_CAPTURE_TIMF_TECMP2     LL_HRTIM_CAPTURETRIG_TIMF_TECMP2      /*!< The timer E compare 2 event triggers the capture */
/**
  * @}
  */

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/** @defgroup DMA_Burst_Update DMA Burst update registers
  * @{
  * @brief Up to 10 registers can be updated for the master timer.
  *        Up to 23 registers can be updated for each timer (TIMA..F).
  */
#define HAL_HRTIM_DMA_BURST_NONE    0x00U                       /*!< No register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_CR      LL_HRTIM_BURSTDMA_TIMCR     /*!< HRTIM_MCR or HRTIM_TIMxCR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_ICR     LL_HRTIM_BURSTDMA_TIMICR    /*!< HRTIM_MICR or HRTIM_TIMxICR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_DIER    LL_HRTIM_BURSTDMA_TIMDIER   /*!< HRTIM_MDIER or HRTIM_TIMxDIER register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_CNT     LL_HRTIM_BURSTDMA_TIMCNT    /*!< HRTIM_MCNTR or HRTIM_CNTxCR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_PER     LL_HRTIM_BURSTDMA_TIMPER    /*!< HRTIM_MPER or HRTIM_PERxR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_REP     LL_HRTIM_BURSTDMA_TIMREP    /*!< HRTIM_MREPR or HRTIM_REPxR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_CMP1    LL_HRTIM_BURSTDMA_TIMCMP1   /*!< HRTIM_MCMP1R or HRTIM_CMP1xR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_CMP2    LL_HRTIM_BURSTDMA_TIMCMP2   /*!< HRTIM_MCMP2R or HRTIM_CMP2xR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_CMP3    LL_HRTIM_BURSTDMA_TIMCMP3   /*!< HRTIM_MCMP3R or HRTIM_CMP3xR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_CMP4    LL_HRTIM_BURSTDMA_TIMCMP4   /*!< HRTIM_MCMP4R or HRTIM_CMP4xR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_DTR     LL_HRTIM_BURSTDMA_TIMDTR    /*!< HRTIM_DTxR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_SET1R   LL_HRTIM_BURSTDMA_TIMSET1R  /*!< HRTIM_SETx1R register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_RST1R   LL_HRTIM_BURSTDMA_TIMRST1R  /*!< HRTIM_RSTx1R register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_SET2R   LL_HRTIM_BURSTDMA_TIMSET2R  /*!< HRTIM_SETx2R register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_RST2R   LL_HRTIM_BURSTDMA_TIMRST2R  /*!< HRTIM_RSTx1R register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_EEFR1   LL_HRTIM_BURSTDMA_TIMEEFR1  /*!< HRTIM_EEFxR1 register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_EEFR2   LL_HRTIM_BURSTDMA_TIMEEFR2  /*!< HRTIM_EEFxR2 register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_RSTR    LL_HRTIM_BURSTDMA_TIMRSTR   /*!< HRTIM_RSTxR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_CHPR    LL_HRTIM_BURSTDMA_TIMCHPR   /*!< HRTIM_CHPxR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_OUTR    LL_HRTIM_BURSTDMA_TIMOUTR   /*!< HRTIM_OUTxR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_FLTR    LL_HRTIM_BURSTDMA_TIMFLTR   /*!< HRTIM_FLTxR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_CR2     LL_HRTIM_BURSTDMA_TIMCR2    /*!< HRTIM_TIMxCR2 register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_EEFR3   LL_HRTIM_BURSTDMA_TIMEEFR3  /*!< HRTIM_TIMxEEFR3 register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_EESELR  LL_HRTIM_BURSTDMA_TIMEESELR /*!< HRTIM_EESELxR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_COTRGR  LL_HRTIM_BURSTDMA_TIMCOTRGR /*!< HRTIM_COTRGxR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_COFER   LL_HRTIM_BURSTDMA_TIMCOFER  /*!< HRTIM_COFExR register is updated by DMA burst accesses */
#define HAL_HRTIM_DMA_BURST_CODER   LL_HRTIM_BURSTDMA_TIMCODER  /*!< HRTIM_CODExR register is updated by DMA burst accesses */
/**
  * @}
  */
#endif /* USE_HAL_HRTIM_DMA */

/** @defgroup Xbar_Ovr_triggers Crossbar override triggers
  * @{
  * @brief Up to 31 events can be combined (ORed) to trigger a crossbar override.
  */
#define HAL_HRTIM_XBAR_OVR_NONE           LL_HRTIM_CO_TRIG_NONE            /*!< All crossbar override triggers are ignored */
#define HAL_HRTIM_XBAR_OVR_SW             LL_HRTIM_CO_TRIG_SW              /*!< Crossbar override software trigger */
#define HAL_HRTIM_XBAR_OVR_FLT1           LL_HRTIM_CO_TRIG_FLT1            /*!< Fault 1 input trigger */
#define HAL_HRTIM_XBAR_OVR_FLT2           LL_HRTIM_CO_TRIG_FLT2            /*!< Fault 2 input trigger */
#define HAL_HRTIM_XBAR_OVR_FLT3           LL_HRTIM_CO_TRIG_FLT3            /*!< Fault 3 input trigger */
#define HAL_HRTIM_XBAR_OVR_FLT4           LL_HRTIM_CO_TRIG_FLT4            /*!< Fault 4 input trigger */
#define HAL_HRTIM_XBAR_OVR_FLT5           LL_HRTIM_CO_TRIG_FLT5            /*!< Fault 5 input trigger */
#define HAL_HRTIM_XBAR_OVR_FLT6           LL_HRTIM_CO_TRIG_FLT6            /*!< Fault 6 input trigger */
#define HAL_HRTIM_XBAR_OVR_FLT7           LL_HRTIM_CO_TRIG_FLT7            /*!< Fault 7 input trigger */
#define HAL_HRTIM_XBAR_OVR_FLT8           LL_HRTIM_CO_TRIG_FLT8            /*!< Fault 8 input trigger */
#define HAL_HRTIM_XBAR_OVR_FLT1_FLT2      LL_HRTIM_CO_TRIG_FLT1_FLT2       /*!< Fault 1 and Fault 2 trigger */
#define HAL_HRTIM_XBAR_OVR_FLT2_FLT3      LL_HRTIM_CO_TRIG_FLT2_FLT3       /*!< Fault 2 and Fault 3 trigger */
#define HAL_HRTIM_XBAR_OVR_FLT3_FLT4      LL_HRTIM_CO_TRIG_FLT3_FLT4       /*!< Fault 3 and Fault 4 trigger */
#define HAL_HRTIM_XBAR_OVR_FLT4_FLT5      LL_HRTIM_CO_TRIG_FLT4_FLT5       /*!< Fault 4 and Fault 5 trigger */
#define HAL_HRTIM_XBAR_OVR_FLT5_FLT6      LL_HRTIM_CO_TRIG_FLT5_FLT6       /*!< Fault 5 and Fault 6 trigger */
#define HAL_HRTIM_XBAR_OVR_FLT6_FLT7      LL_HRTIM_CO_TRIG_FLT6_FLT7       /*!< Fault 6 and Fault 7 trigger */
#define HAL_HRTIM_XBAR_OVR_FLT7_FLT8      LL_HRTIM_CO_TRIG_FLT7_FLT8       /*!< Fault 7 and Fault 8 trigger */
#define HAL_HRTIM_XBAR_OVR_EEVA           LL_HRTIM_CO_TRIG_EEVA            /*!< External event A trigger */
#define HAL_HRTIM_XBAR_OVR_EEVB           LL_HRTIM_CO_TRIG_EEVB            /*!< External event B trigger */
#define HAL_HRTIM_XBAR_OVR_EEVC           LL_HRTIM_CO_TRIG_EEVC            /*!< External event C trigger */
#define HAL_HRTIM_XBAR_OVR_EEVD           LL_HRTIM_CO_TRIG_EEVD            /*!< External event D trigger */
#define HAL_HRTIM_XBAR_OVR_EEVE           LL_HRTIM_CO_TRIG_EEVE            /*!< External event E trigger */
#define HAL_HRTIM_XBAR_OVR_EEVF           LL_HRTIM_CO_TRIG_EEVF            /*!< External event F trigger */
#define HAL_HRTIM_XBAR_OVR_EEVG           LL_HRTIM_CO_TRIG_EEVG            /*!< External event G trigger */
#define HAL_HRTIM_XBAR_OVR_EEVH           LL_HRTIM_CO_TRIG_EEVH            /*!< External event H trigger */
#define HAL_HRTIM_XBAR_OVR_EEVI           LL_HRTIM_CO_TRIG_EEVI            /*!< External event I trigger */
#define HAL_HRTIM_XBAR_OVR_EEVJ           LL_HRTIM_CO_TRIG_EEVJ            /*!< External event J trigger */
/**
  * @}
  */

/** @defgroup Xbar_Ovr_forcing_events Crossbar override forcing events
  * @{
  * @brief External events can be combined (Ored) to force an output to its active level when the crossbar override
  *        is triggered.
  */
#define HAL_HRTIM_XBAR_OVR_FORCING_NONE          LL_HRTIM_CO_FORCEON_NONE           /*!< No external event force the output to its active level */
#define HAL_HRTIM_XBAR_OVR_FORCING_EEVA          LL_HRTIM_CO_FORCEON_EEVA           /*!< Output level is forced active on external event A */
#define HAL_HRTIM_XBAR_OVR_FORCING_EEVB          LL_HRTIM_CO_FORCEON_EEVB           /*!< Output level is forced active on external event B */
#define HAL_HRTIM_XBAR_OVR_FORCING_EEVC          LL_HRTIM_CO_FORCEON_EEVC           /*!< Output level is forced active on external event C */
#define HAL_HRTIM_XBAR_OVR_FORCING_EEVD          LL_HRTIM_CO_FORCEON_EEVD           /*!< Output level is forced active on external event D */
#define HAL_HRTIM_XBAR_OVR_FORCING_EEVE          LL_HRTIM_CO_FORCEON_EEVE           /*!< Output level is forced active on external event E */
#define HAL_HRTIM_XBAR_OVR_FORCING_EEVF          LL_HRTIM_CO_FORCEON_EEVF           /*!< Output level is forced active on external event F */
#define HAL_HRTIM_XBAR_OVR_FORCING_EEVG          LL_HRTIM_CO_FORCEON_EEVG           /*!< Output level is forced active on external event G */
#define HAL_HRTIM_XBAR_OVR_FORCING_EEVH          LL_HRTIM_CO_FORCEON_EEVH           /*!< Output level is forced active on external event H */
#define HAL_HRTIM_XBAR_OVR_FORCING_EEVI          LL_HRTIM_CO_FORCEON_EEVI           /*!< Output level is forced active on external event I */
#define HAL_HRTIM_XBAR_OVR_FORCING_EEVJ          LL_HRTIM_CO_FORCEON_EEVJ           /*!< Output level is forced active on external event J */
/**
  * @}
  */

/**
  * @}
  */
/* End of exported constants -------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/** @defgroup HRTIM_Exported_Types HAL HRTIM Types
  * @{
  */

/**
  * @brief HAL HRTIM instance.
  */
typedef enum
{
  HAL_HRTIM1 = HRTIM1_BASE,
  HAL_HRTIM2 = HRTIM2_BASE,

} hal_hrtim_t;


/**
  * @brief HAL HRTIM compare units identifiers.
  */
typedef enum
{
  /** Compare unit 1 */
  HAL_HRTIM_COMPARE_UNIT_1 = LL_HRTIM_COMPARE_UNIT_1,

  /** Compare unit 2 */
  HAL_HRTIM_COMPARE_UNIT_2 = LL_HRTIM_COMPARE_UNIT_2,

  /** Compare unit 3 */
  HAL_HRTIM_COMPARE_UNIT_3 = LL_HRTIM_COMPARE_UNIT_3,

  /** Compare unit 4 */
  HAL_HRTIM_COMPARE_UNIT_4 = LL_HRTIM_COMPARE_UNIT_4

} hal_hrtim_compare_unit_t;

/**
  * @brief HAL HRTIM capture units identifiers.
  */
typedef enum
{
  /** Capture unit 1 */
  HAL_HRTIM_CAPTURE_UNIT_1 = LL_HRTIM_CAPTURE_UNIT_1,

  /** Capture unit 2 */
  HAL_HRTIM_CAPTURE_UNIT_2 = LL_HRTIM_CAPTURE_UNIT_2

} hal_hrtim_capture_unit_t;

/**
  * @brief HAL HRTIM global states definition.
  */
typedef enum
{
  /** Peripheral not yet initialized */
  HAL_HRTIM_STATE_RESET   = 0,

  /** Peripheral initialized */
  HAL_HRTIM_STATE_INIT    = (1U << 31U),

} hal_hrtim_state_t;

/**
  * @brief HAL HRTIM timer states definition.
  */
typedef enum
{
  /** HRTIM timer initial state */
  HAL_HRTIM_TIM_STATE_RESET   = (1U << 31U),

  /** HRTIM timer ready for use */
  HAL_HRTIM_TIM_STATE_IDLE    = (1U << 30U),

  /** HRTIM timer counter is enabled */
  HAL_HRTIM_TIM_STATE_ACTIVE  = (1U << 29U),

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
  /** HRTIM timer counter is enabled, DMA interrupts are disabled */
  HAL_HRTIM_TIM_STATE_ACTIVE_SILENT     = (1U << 28U),
#endif /* USE_HAL_HRTIM_DMA */

} hal_hrtim_timer_state_t;


/**
  * @brief HAL HRTIM output states definition.
  */
typedef enum
{
  /** Default output state after output has been configured, when the outputs
      are disabled by software or during a burst mode operation */
  HAL_HRTIM_OUTPUT_DISABLED,

  /** Main output status, where the output can take the active or
      inactive level as per crossbar unit configuration */
  HAL_HRTIM_OUTPUT_ENABLED,

  /** Safety status, entered in case of a shut-down request on FAULTx input(s) */
  HAL_HRTIM_OUTPUT_FAULT,

} hal_hrtim_output_status_t;


/**
  *  @brief HAL HRTIM interrupt source.
  */
typedef enum
{
  /** Master timer interrupts */
  HAL_HRTIM_INTERRUPT_MASTER       = 0x0000U,

  /** Timer A interrupts */
  HAL_HRTIM_INTERRUPT_TIMA         = 0x0001U,

  /** Timer B interrupts */
  HAL_HRTIM_INTERRUPT_TIMB         = 0x0002U,

  /** Timer C interrupts */
  HAL_HRTIM_INTERRUPT_TIMC         = 0x0003U,

  /** Timer D interrupts */
  HAL_HRTIM_INTERRUPT_TIMD         = 0x0004U,

  /** Timer E interrupts */
  HAL_HRTIM_INTERRUPT_TIME         = 0x0005U,

  /** Timer F interrupts */
  HAL_HRTIM_INTERRUPT_TIMF         = 0x0006U,

  /** HRTIM global interrupts */
  HAL_HRTIM_INTERRUPT_COMMON       = 0x0007U,

} hal_hrtim_interrupt_src_t;

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/**
  *  @brief HAL HRTIM DMA request source.
  */
typedef enum
{
  /** Master timer DMA requests */
  HAL_HRTIM_DMA_MASTER      = 0x0000U,

  /** Timer A DMA requests */
  HAL_HRTIM_DMA_TIMA         = 0x0001U,

  /** Timer B DMA requests */
  HAL_HRTIM_DMA_TIMB         = 0x0002U,

  /** Timer C DMA requests */
  HAL_HRTIM_DMA_TIMC         = 0x0003U,

  /** Timer D DMA requests */
  HAL_HRTIM_DMA_TIMD         = 0x0004U,

  /** Timer E DMA requests */
  HAL_HRTIM_DMA_TIME         = 0x0005U,

  /** Timer F DMA requests */
  HAL_HRTIM_DMA_TIMF         = 0x0006U,

} hal_hrtim_dma_source_t;

/**
  *  @brief HAL HRTIM DMA configuration.
  */
typedef struct
{
  /** DMA requests to enable */
  uint32_t requests;

  /** DMA transfer source address */
  uint32_t src_addr;

  /** DMA transfer destination address */
  uint32_t dest_addr;

  /** DMA transfer size (in bytes) */
  uint32_t size_byte;

} hal_hrtim_dma_config_t;

#endif /* USE_HAL_HRTIM_DMA */

/**
  * @brief HAL HRTIM synchronization input source.
  */
typedef enum
{
  /** Synchronization input is disabled */
  HAL_HRTIM_SYNC_INPUT_DISABLE = ((LL_HRTIM_INSTANCE_HRTIM2 | LL_HRTIM_INSTANCE_HRTIM1) \
                                  | LL_HRTIM_SYNCIN_SRC_NONE),

  /** Synchronization input source is HRTIM_SCIN pin */
  HAL_HRTIM_SYNC_INPUT_GPIO = ((LL_HRTIM_INSTANCE_HRTIM2 | LL_HRTIM_INSTANCE_HRTIM1) \
                               | LL_HRTIM_SYNCIN_SRC_GPIO),

  /** Synchronization input source is HRTIM2 synchronization output */
  HAL_HRTIM_SYNC_INPUT_HRTIM1_SYNCOUT = ((LL_HRTIM_INSTANCE_HRTIM2) \
                                         | LL_HRTIM_SYNCIN_SRC_HRTIM1_SYNCOUT),

  /** Synchronization input source is HRTIM1 synchronization output */
  HAL_HRTIM_SYNC_INPUT_HRTIM2_SYNCOUT = ((LL_HRTIM_INSTANCE_HRTIM1) \
                                         | LL_HRTIM_SYNCIN_SRC_HRTIM2_SYNCOUT),

  /** Synchronization input source is TIM1 TRGO */
  HAL_HRTIM_SYNC_INPUT_TIM1_TRGO = ((LL_HRTIM_INSTANCE_HRTIM2 | LL_HRTIM_INSTANCE_HRTIM1) \
                                    | LL_HRTIM_SYNCIN_SRC_TIM1_TRGO),

} hal_hrtim_sync_input_src_t;

/**
  * @brief HAL HRTIM synchronization output pulse.
  */
typedef enum
{
  /** Synchronization output is disabled. */
  HAL_HRTIM_SYNC_OUTPUT_DISABLE = LL_HRTIM_SYNCOUT_DISABLE,

  /** Positive pulse on HRTIM_SCOUT output (16x fHRTIM clock cycles). */
  HAL_HRTIM_SYNC_OUTPUT_POSITIVE_PULSE = LL_HRTIM_SYNCOUT_POSITIVE_PULSE,

  /** Negative pulse on HRTIM_SCOUT output (16x fHRTIM clock cycles). */
  HAL_HRTIM_SYNC_OUTPUT_NEGATIVE_PULSE = LL_HRTIM_SYNCOUT_NEGATIVE_PULSE,

  /** On-chip synchronization sent to other HRTIM instances. */
  HAL_HRTIM_SYNC_OUTPUT_ONCHIP = LL_HRTIM_SYNCOUT_ONCHIP,

} hal_hrtim_sync_output_mode_t;

/**
  * @brief HAL HRTIM synchronization output source.
  */
typedef enum
{
  /** Master timer start is selected as the source to be sent to the synchronization output. */
  HAL_HRTIM_SYNC_OUTPUT_MASTER_START = LL_HRTIM_SYNCOUT_SRC_MASTER_START,

  /** Master timer compare 1 event is selected as the source to be sent to the synchronization output. */
  HAL_HRTIM_SYNC_OUTPUT_MASTER_CMP1 = LL_HRTIM_SYNCOUT_SRC_MASTER_CMP1,

  /** Timer A start is selected as the source to be sent to the synchronization output. */
  HAL_HRTIM_SYNC_OUTPUT_TIMA_START = LL_HRTIM_SYNCOUT_SRC_TIMA_START,

  /** Timer A compare 1 event is selected as the source to be sent to the synchronization output. */
  HAL_HRTIM_SYNC_OUTPUT_TIMA_CMP1 = LL_HRTIM_SYNCOUT_SRC_TIMA_CMP1,

} hal_hrtim_sync_output_src_t;

/**
  * @brief HAL HRTIM synchronization output configuration structure.
  */
typedef struct
{
  /** Event to be sent on the synchronization output. */
  hal_hrtim_sync_output_src_t source;

  /** Synchronization output mode. */
  hal_hrtim_sync_output_mode_t mode;

} hal_hrtim_sync_output_config_t;


/**
  * @brief HAL HRTIM slave modes.
  */
typedef enum
{
  /** Slave mode disabled. */
  HAL_HRTIM_TIM_SLAVE_DISABLE = 0U,

  /** Reset Mode
    *  Rising edge on the synchronization input resets the counter. */
  HAL_HRTIM_TIM_SLAVE_RESET   = HRTIM_MCR_SYNCRSTM,

  /** Trigger Mode
    *  Rising edge on the synchronization input starts the counter. */
  HAL_HRTIM_TIM_SLAVE_TRIGGER = HRTIM_MCR_SYNCSTRTM,

  /** Combined reset + trigger mode
    *  Rising edge on the synchronization input resets and starts the counter. */
  HAL_HRTIM_TIM_SLAVE_RESET_AND_TRIGGER = (HRTIM_MCR_SYNCSTRTM | HRTIM_MCR_SYNCRSTM),

} hal_hrtim_tim_slave_mode_t;


/**
  * @brief HAL HRTIM ADC trigger identifier.
  */
typedef enum
{
  /** ADC trigger 1 */
  HAL_HRTIM_ADC_TRIGGER1 = LL_HRTIM_ADCTRIG1,

  /** ADC trigger 2 */
  HAL_HRTIM_ADC_TRIGGER2 = LL_HRTIM_ADCTRIG2,

  /** ADC trigger 3 */
  HAL_HRTIM_ADC_TRIGGER3 = LL_HRTIM_ADCTRIG3,

  /** ADC trigger 4 */
  HAL_HRTIM_ADC_TRIGGER4 = LL_HRTIM_ADCTRIG4,

  /** ADC trigger 5 */
  HAL_HRTIM_ADC_TRIGGER5 = LL_HRTIM_ADCTRIG5,

  /** ADC trigger 6 */
  HAL_HRTIM_ADC_TRIGGER6 = LL_HRTIM_ADCTRIG6,

  /** ADC trigger 7 */
  HAL_HRTIM_ADC_TRIGGER7 = LL_HRTIM_ADCTRIG7,

  /** ADC trigger 8 */
  HAL_HRTIM_ADC_TRIGGER8 = LL_HRTIM_ADCTRIG8,

  /** ADC trigger 9 */
  HAL_HRTIM_ADC_TRIGGER9 = LL_HRTIM_ADCTRIG9,

  /** ADC trigger 10 */
  HAL_HRTIM_ADC_TRIGGER10 = LL_HRTIM_ADCTRIG10,

} hal_hrtim_adc_trigger_t;

/**
  * @brief HAL HRTIM ADC synchronization configuration structure.
  */
typedef struct
{
  /** ADC trigger source(s) configuration (see @ref ADC_Triggers) */
  uint32_t source;

  /** Timer triggering the update of the ADC trigger source configuration register (see @ref Timer_Identifiers) */
  uint32_t update;

} hal_hrtim_adc_sync_config_t;

/**
  * @brief HAL HRTIM DAC synchronization.
  */
typedef enum
{
  /** No DAC trigger generated */
  HAL_HRTIM_DAC_TRIGGER_NONE = LL_HRTIM_DACTRIG_NONE,

  /** DAC trigger generated on hrtim_dac_trg1 output */
  HAL_HRTIM_DAC_TRIGGER1 = LL_HRTIM_DACTRIG_DACTRIGOUT1,

  /** DAC trigger generated on hrtim_dac_trg2 output */
  HAL_HRTIM_DAC_TRIGGER2 = LL_HRTIM_DACTRIG_DACTRIGOUT2,

  /** DAC trigger generated on hrtim_dac_trg3 output */
  HAL_HRTIM_DAC_TRIGGER3 = LL_HRTIM_DACTRIG_DACTRIGOUT3,

} hal_hrtim_dac_trigger_t;

/**
  * @brief HAL HRTIM dual channel DAC reset trigger.
  */
typedef enum
{
  /** Reset trigger is generated on counter reset or roll-over event */
  HAL_HRTIM_DUAL_DAC_RESET_RESET =  LL_HRTIM_DCDR_RESET,

  /** Reset trigger is generated on output 1 set event */
  HAL_HRTIM_DUAL_DAC_RESET_OUT1_SET =  LL_HRTIM_DCDR_OUT1_SET,

} hal_hrtim_dual_channel_dac_reset_trigger_t;

/**
  * @brief HAL HRTIM dual channel DAC step trigger.
  */
typedef enum
{
  /** Step trigger is generated on compare 2 event */
  HAL_HRTIM_DUAL_DAC_STEP_CMP2 =  LL_HRTIM_DCDS_CMP2,

  /** Step trigger is generated on output 1 reset event */
  HAL_HRTIM_DUAL_DAC_STEP_OUT1_RESET =  LL_HRTIM_DCDS_OUT1_RESET,

} hal_hrtim_dual_channel_dac_step_trigger_t;

/**
  * @brief HAL HRTIM dual channel DAC triggers configuration structure.
  */
typedef struct
{
  /** Dual channel DAC reset trigger */
  hal_hrtim_dual_channel_dac_reset_trigger_t reset_trigger;

  /** Dual channel DAC step trigger */
  hal_hrtim_dual_channel_dac_step_trigger_t step_trigger;

} hal_hrtim_dual_channel_dac_triggers_config_t;

/**
  * @brief HAL HRTIM dual channel DAC triggers status.
  */
typedef enum
{
  /** Dual channel DAC triggers are disabled */
  HAL_HRTIM_DUAL_DAC_DISABLED = 0U,

  /** Dual channel DAC triggers are enabled */
  HAL_HRTIM_DUAL_DAC_ENABLED = 1U,

} hal_hrtim_dual_channel_dac_status_t;

/**
  * @brief HAL HRTIM digital filter applied to HRTIM external events or faults.
  *        External events filtering: sampling frequency (fSAMPLING) is derived from fEEVS.
  *        Faults filtering: sampling frequency (fSAMPLING) is derived from fFLTS.
  */
typedef enum
{
  /** No filter                                                 */
  HAL_HRTIM_FDIV1    = LL_HRTIM_FDIV1,

  /** fSAMPLING=fHRTIM, N=2                                    */
  HAL_HRTIM_FDIV1_N2 = LL_HRTIM_FDIV1_N2,

  /** fSAMPLING=fHRTIM, N=4                                    */
  HAL_HRTIM_FDIV1_N4 = LL_HRTIM_FDIV1_N4,

  /** fSAMPLING=fHRTIM, N=8                                    */
  HAL_HRTIM_FDIV1_N8 = LL_HRTIM_FDIV1_N8,

  /** fSAMPLING=fEEVS/2 or fFLTS/2, N=6                        */
  HAL_HRTIM_FDIV2_N6 = LL_HRTIM_FDIV2_N6,

  /** fSAMPLING=fEEVS/2 or fFLTS/2, N=8                        */
  HAL_HRTIM_FDIV2_N8 = LL_HRTIM_FDIV2_N8,

  /** fSAMPLING=fEEVS/4 or fFLTS/4, N=6                        */
  HAL_HRTIM_FDIV4_N6 = LL_HRTIM_FDIV4_N6,

  /** fSAMPLING=fEEVS/4 or fFLTS/4, N=8                        */
  HAL_HRTIM_FDIV4_N8 = LL_HRTIM_FDIV4_N8,

  /** fSAMPLING=fEEVS/8 or fFLTS/8, N=6                        */
  HAL_HRTIM_FDIV8_N6 = LL_HRTIM_FDIV8_N6,

  /** fSAMPLING=fEEVS/8 or fFLTS/8, N=8                        */
  HAL_HRTIM_FDIV8_N8 = LL_HRTIM_FDIV8_N8,

  /** fSAMPLING=fEEVS/16 or fFLTS/16, N=5                      */
  HAL_HRTIM_FDIV16_N5 = LL_HRTIM_FDIV16_N5,

  /** fSAMPLING=fEEVS/16 or fFLTS/16, N=6                      */
  HAL_HRTIM_FDIV16_N6 = LL_HRTIM_FDIV16_N6,

  /** fSAMPLING=fEEVS/16 or fFLTS/16, N=8                      */
  HAL_HRTIM_FDIV16_N8 = LL_HRTIM_FDIV16_N8,

  /** fSAMPLING=fEEVS/32 or fFLTS/32, N=5                      */
  HAL_HRTIM_FDIV32_N5 = LL_HRTIM_FDIV32_N5,

  /** fSAMPLING=fEEVS/32 or fFLTS/32, N=6                      */
  HAL_HRTIM_FDIV32_N6 = LL_HRTIM_FDIV32_N6,

  /** fSAMPLING=fEEVS/32 or fFLTS/32, N=8                      */
  HAL_HRTIM_FDIV32_N8 = LL_HRTIM_FDIV32_N8,

} hal_hrtim_filter_t;

/**
  * @brief HAL HRTIM external event sources.
  *
  * Bits 18:16                  | Bits 15:0
  * --------------------------- | ----- ---
  * Event source                | Event identifier
  *
  */
typedef enum
{
  /** External event 1 is connected to GPIO */
  HAL_HRTIM_EEV1_GPIO = ((LL_HRTIM_EEV1SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV1),

  /** External event 1 is connected to COMP2_OUT */
  HAL_HRTIM_EEV1_COMP2 = ((LL_HRTIM_EEV1SRC_COMP2 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV1),

  /** External event 1 is connected to TIM1 TRGO */
  HAL_HRTIM_EEV1_TIM1_TRGO = ((LL_HRTIM_EEV1SRC_TIM1_TRGO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV1),

  /** External event 1 is connected to ADC1 AWD1 */
  HAL_HRTIM_EEV1_ADC1_AWD1 = ((LL_HRTIM_EEV1SRC_ADC1_AWD1 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV1),

  /** External event 1 is connected to ADC4 AWD1 */
  HAL_HRTIM_EEV1_ADC4_AWD1 = ((LL_HRTIM_EEV1SRC_ADC4_AWD1 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV1),

  /** External event 2 is connected to GPIO */
  HAL_HRTIM_EEV2_GPIO = ((LL_HRTIM_EEV2SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV2),

  /** External event 2 is connected to COMP4_OUT */
  HAL_HRTIM_EEV2_COMP4 = ((LL_HRTIM_EEV2SRC_COMP4 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV2),

  /** External event 2 is connected to TIM2 TRGO */
  HAL_HRTIM_EEV2_TIM2_TRGO = ((LL_HRTIM_EEV2SRC_TIM2_TRGO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV2),

  /** External event 2 is connected to ADC1 AWD2 */
  HAL_HRTIM_EEV2_ADC1_AWD2 = ((LL_HRTIM_EEV2SRC_ADC1_AWD2 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV2),

  /** External event 2 is connected to ADC4 AWD2 */
  HAL_HRTIM_EEV2_ADC4_AWD2 = ((LL_HRTIM_EEV2SRC_ADC4_AWD2 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV2),

  /** External event 3 is connected to GPIO */
  HAL_HRTIM_EEV3_GPIO = ((LL_HRTIM_EEV3SRC_GPIO << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV3),

  /** External event 3 is connected to COMP6_OUT */
  HAL_HRTIM_EEV3_COMP6 = ((LL_HRTIM_EEV3SRC_COMP6 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV3),

  /** External event 3 is connected to TIM3 TRGO */
  HAL_HRTIM_EEV3_TIM3_TRGO = ((LL_HRTIM_EEV3SRC_TIM3_TRGO << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV3),

  /** External event 3 is connected to ADC1 AWD3 */
  HAL_HRTIM_EEV3_ADC1_AWD3 = ((LL_HRTIM_EEV3SRC_ADC1_AWD3 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV3),

  /** External event 3 is connected to ADC4 AWD3 */
  HAL_HRTIM_EEV3_ADC4_AWD3 = ((LL_HRTIM_EEV3SRC_ADC4_AWD3 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV3),

  /** External event 4 is connected to GPIO */
  HAL_HRTIM_EEV4_GPIO = ((LL_HRTIM_EEV4SRC_GPIO << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV4),

  /** External event 4 is connected to COMP1 OUT */
  HAL_HRTIM_EEV4_COMP1 = ((LL_HRTIM_EEV4SRC_COMP1 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV4),

  /** External event 4 is connected to COMP5 OUT */
  HAL_HRTIM_EEV4_COMP5 = ((LL_HRTIM_EEV4SRC_COMP5 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV4),

  /** External event 4 is connected to ADC2 AWD1 */
  HAL_HRTIM_EEV4_ADC2_AWD1 = ((LL_HRTIM_EEV4SRC_ADC2_AWD1 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV4),

  /** External event 4 is connected to ADC3 AWD1 */
  HAL_HRTIM_EEV4_ADC3_AWD1 = ((LL_HRTIM_EEV4SRC_ADC3_AWD1 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV4),

  /** External event 5 is connected to GPIO */
  HAL_HRTIM_EEV5_GPIO = ((LL_HRTIM_EEV5SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV5),

  /** External event 5 is connected to COMP3_OUT */
  HAL_HRTIM_EEV5_COMP3 = ((LL_HRTIM_EEV5SRC_COMP3 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV5),

  /** External event 5 is connected to COMP7_OUT */
  HAL_HRTIM_EEV5_COMP7 = ((LL_HRTIM_EEV5SRC_COMP7 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV5),

  /** External event 5 is connected to ADC2 AWD2 */
  HAL_HRTIM_EEV5_ADC2_AWD2 = ((LL_HRTIM_EEV5SRC_ADC2_AWD2 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV5),

  /** External event 5 is connected to ADC3 AWD2 */
  HAL_HRTIM_EEV5_ADC3_AWD2 = ((LL_HRTIM_EEV5SRC_ADC3_AWD2 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV5),

  /** External event 6 is connected to GPIO */
  HAL_HRTIM_EEV6_GPIO = ((LL_HRTIM_EEV6SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV6),

  /** External event 6 is connected to COMP2_OUT */
  HAL_HRTIM_EEV6_COMP2 = ((LL_HRTIM_EEV6SRC_COMP2 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV6),

  /** External event 6 is connected to COMP1_OUT */
  HAL_HRTIM_EEV6_COMP1 = ((LL_HRTIM_EEV6SRC_COMP1 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV6),

  /** External event 6 is connected to ADC2 AWD3 */
  HAL_HRTIM_EEV6_ADC2_AWD3 = ((LL_HRTIM_EEV6SRC_ADC2_AWD3 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV6),

  /** External event 6 is connected to ADC3 AWD3 */
  HAL_HRTIM_EEV6_ADC3_AWD3 = ((LL_HRTIM_EEV6SRC_ADC3_AWD3 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV6),

  /** External event 7 is connected to GPIO */
  HAL_HRTIM_EEV7_GPIO = ((LL_HRTIM_EEV7SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV7),

  /** External event 7 is connected to COMP4_OUT */
  HAL_HRTIM_EEV7_COMP4 = ((LL_HRTIM_EEV7SRC_COMP4 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV7),

  /** External event 7 is connected to COMP7_OUT */
  HAL_HRTIM_EEV7_COMP7 = ((LL_HRTIM_EEV7SRC_COMP7 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV7),

  /** External event 7 is connected to ADC3 AWD1 */
  HAL_HRTIM_EEV7_ADC3_AWD1 = ((LL_HRTIM_EEV7SRC_ADC3_AWD1 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV7),

  /** External event 7 is connected to ADC4 AWD1 */
  HAL_HRTIM_EEV7_ADC4_AWD1 = ((LL_HRTIM_EEV7SRC_ADC4_AWD1 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV7),

  /** External event 8 is connected to GPIO */
  HAL_HRTIM_EEV8_GPIO = ((LL_HRTIM_EEV8SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV8),

  /** External event 8 is connected to COMP3 OUT */
  HAL_HRTIM_EEV8_COMP3 = ((LL_HRTIM_EEV8SRC_COMP3 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV8),

  /** External event 8 is connected to COMP6 OUT */
  HAL_HRTIM_EEV8_COMP6 = ((LL_HRTIM_EEV8SRC_COMP6 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV8),

  /** External event 8 is connected to ADC3 AWD2 */
  HAL_HRTIM_EEV8_ADC3_AWD2 = ((LL_HRTIM_EEV8SRC_ADC3_AWD2 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV8),

  /** External event 8 is connected to ADC4 AWD2 */
  HAL_HRTIM_EEV8_ADC4_AWD2 = ((LL_HRTIM_EEV8SRC_ADC4_AWD2 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV8),

  /** External event 9 is connected to GPIO */
  HAL_HRTIM_EEV9_GPIO = ((LL_HRTIM_EEV9SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV9),

  /** External event 9 is connected to COMP5 OUT */
  HAL_HRTIM_EEV9_COMP5 = ((LL_HRTIM_EEV9SRC_COMP5 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV9),

  /** External event 9 is connected to COMP8 OUT */
  HAL_HRTIM_EEV9_COMP8 = ((LL_HRTIM_EEV9SRC_COMP8 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV9),

  /** External event 9 is connected to COMP4 OUT */
  HAL_HRTIM_EEV9_COMP4 = ((LL_HRTIM_EEV9SRC_COMP4 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV9),

  /** External event 10 is connected to GPIO */
  HAL_HRTIM_EEV10_GPIO = ((LL_HRTIM_EEV10SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV10),

  /** External event 10 is connected to COMP7_OUT */
  HAL_HRTIM_EEV10_COMP7 = ((LL_HRTIM_EEV10SRC_COMP7 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV10),

  /** External event 10 is connected to TIM6 TRGO */
  HAL_HRTIM_EEV10_TIM6_TRGO = ((LL_HRTIM_EEV10SRC_TIM6_TRGO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV10),

  /** External event 10 is connected to ADC3 AWD3 */
  HAL_HRTIM_EEV10_ADC3_AWD3 = ((LL_HRTIM_EEV10SRC_ADC3_AWD3 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV10),

  /** External event 10 is connected to ADC4 AWD3 */
  HAL_HRTIM_EEV10_ADC4_AWD3 = ((LL_HRTIM_EEV10SRC_ADC4_AWD3 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV10),

  /** External event 11 is connected to GPIO */
  HAL_HRTIM_EEV11_GPIO = ((LL_HRTIM_EEV11SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV11),

  /** External event 11 is connected to COMP7_OUT */
  HAL_HRTIM_EEV11_COMP7 = ((LL_HRTIM_EEV11SRC_COMP7 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV11),

  /** External event 11 is connected to TIM9 TRGO */
  HAL_HRTIM_EEV11_TIM9_TRGO = ((LL_HRTIM_EEV11SRC_TIM9_TRGO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV11),

  /** External event 11 is connected to ADC2 AWD1 */
  HAL_HRTIM_EEV11_ADC2_AWD1 = ((LL_HRTIM_EEV11SRC_ADC2_AWD1 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV11),

  /** External event 12 is connected to GPIO */
  HAL_HRTIM_EEV12_GPIO = ((LL_HRTIM_EEV12SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV12),

  /** External event 12 is connected to COMP8_OUT */
  HAL_HRTIM_EEV12_COMP8 = ((LL_HRTIM_EEV12SRC_COMP8 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV12),

  /** External event 12 is connected to TIM12 TRGO */
  HAL_HRTIM_EEV12_TIM12_TRGO = ((LL_HRTIM_EEV12SRC_TIM12_TRGO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV12),

  /** External event 12 is connected to ADC2 AWD2 */
  HAL_HRTIM_EEV12_ADC2_AWD2 = ((LL_HRTIM_EEV12SRC_ADC2_AWD2 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV12),

  /** External event 13 is connected to GPIO */
  HAL_HRTIM_EEV13_GPIO = ((LL_HRTIM_EEV13SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV13),

  /** External event 13 is connected to COMP5_OUT */
  HAL_HRTIM_EEV13_COMP5 = ((LL_HRTIM_EEV13SRC_COMP5 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV13),

  /** External event 13 is connected to TIM15 TRGO */
  HAL_HRTIM_EEV13_TIM15_TRGO = ((LL_HRTIM_EEV13SRC_TIM15_TRGO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV13),

  /** External event 13 is connected to ADC2 AWD3 */
  HAL_HRTIM_EEV13_ADC2_AWD3 = ((LL_HRTIM_EEV13SRC_ADC2_AWD3 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV13),

  /** External event 14 is connected to GPIO */
  HAL_HRTIM_EEV14_GPIO = ((LL_HRTIM_EEV14SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV14),

  /** External event 14 is connected to COMP8_OUT */
  HAL_HRTIM_EEV14_COMP8 = ((LL_HRTIM_EEV14SRC_COMP8 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV14),

  /** External event 14 is connected to TIM1 TRGO */
  HAL_HRTIM_EEV14_TIM1_TRGO = ((LL_HRTIM_EEV14SRC_TIM1_TRGO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV14),

  /** External event 14 is connected to ADC1 AWD1 */
  HAL_HRTIM_EEV14_ADC1_AWD1 = ((LL_HRTIM_EEV14SRC_ADC1_AWD1 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV14),

  /** External event 15 is connected to GPIO */
  HAL_HRTIM_EEV15_GPIO = ((LL_HRTIM_EEV15SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV15),

  /** External event 15 is connected to COMP1_OUT */
  HAL_HRTIM_EEV15_COMP1 = ((LL_HRTIM_EEV15SRC_COMP1 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV15),

  /** External event 15 is connected to TIM8 TRGO */
  HAL_HRTIM_EEV15_TIM8_TRGO = ((LL_HRTIM_EEV15SRC_TIM8_TRGO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV15),

  /** External event 15 is connected to ADC1 AWD2 */
  HAL_HRTIM_EEV15_ADC1_AWD2 = ((LL_HRTIM_EEV15SRC_ADC1_AWD2 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV15),

  /** External event 16 is connected to GPIO */
  HAL_HRTIM_EEV16_GPIO = ((LL_HRTIM_EEV16SRC_GPIO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV16),

  /** External event 16 is connected to COMP3_OUT */
  HAL_HRTIM_EEV16_COMP3 = ((LL_HRTIM_EEV16SRC_COMP3 << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV16),

  /** External event 16 is connected to TIM20 TRGO */
  HAL_HRTIM_EEV16_TIM20_TRGO = ((LL_HRTIM_EEV16SRC_TIM20_TRGO << LL_HRTIM_EEV_SRC_POS) | HAL_HRTIM_EEV16),

  /** External event 16 is connected to ADC1 AWD3 */
  HAL_HRTIM_EEV16_ADC1_AWD3 = ((LL_HRTIM_EEV16SRC_ADC1_AWD3 << LL_HRTIM_EEV_SRC_POS)  | HAL_HRTIM_EEV16),

} hal_hrtim_eev_src_t;

/**
  * @brief HAL HRTIM external event sensitivity.
  */
typedef enum
{
  /** External event is active on rising edge detection. */
  HAL_HRTIM_EEV_EDGE_RISING         = LL_HRTIM_EE_SENSITIVITY_RISING,

  /** External event is active on falling edge detection. */
  HAL_HRTIM_EEV_EDGE_FALLING        = LL_HRTIM_EE_SENSITIVITY_FALLING,

  /** External event is active on rising or falling edges detection. */
  HAL_HRTIM_EEV_EDGE_RISING_FALLING = LL_HRTIM_EE_SENSITIVITY_RISING_FALLING,

  /** External event is active on high level detection. */
  HAL_HRTIM_EEV_LEVEL_HIGH          = LL_HRTIM_EE_POLARITY_HIGH,

  /** External event is active on low level detection. */
  HAL_HRTIM_EEV_LEVEL_LOW           = LL_HRTIM_EE_POLARITY_LOW,

} hal_hrtim_eev_sensitivity_t;

/**
  * @brief HAL HRTIM external event operating mode.
  */
typedef enum
{
  /** External event is resampled with the clock before acting on the output crossbar. */
  HAL_HRTIM_EEV_SYNCHRONOUS          = LL_HRTIM_EE_FASTMODE_DISABLE,

  /** Latency between the external event and the action on the output is minimized. */
  HAL_HRTIM_EEV_ASYNCHRONOUS         = LL_HRTIM_EE_FASTMODE_ENABLE,

} hal_hrtim_eev_mode_t;

/**
  * @brief HAL HRTIM external event configuration structure.
  */
typedef struct
{
  /** HRTIM external event source */
  hal_hrtim_eev_src_t source;

  /** HRTIM external event sensitivity */
  hal_hrtim_eev_sensitivity_t sensitivity;

  /** HRTIM external event digital filter */
  hal_hrtim_filter_t filter;

  /** HRTIM external event operating mode */
  hal_hrtim_eev_mode_t mode;

} hal_hrtim_eev_config_t;

/**
  * @brief HAL HRTIM external event prescaler.
  *        Division ratio between the HRTIM clock frequency (fHRTIM) and the external
  *        event signal sampling clock (fEEVS) used by the digital filters.
  */
typedef enum
{
  /** fEEVS = fHRTIM */
  HAL_HRTIM_EEV_DIV1 = LL_HRTIM_EE_PRESCALER_DIV1,

  /** fEEVS = fHRTIM/2 */
  HAL_HRTIM_EEV_DIV2 = LL_HRTIM_EE_PRESCALER_DIV2,

  /** fEEVS = fHRTIM/4 */
  HAL_HRTIM_EEV_DIV4 = LL_HRTIM_EE_PRESCALER_DIV4,

  /** fEEVS = fHRTIM/8 */
  HAL_HRTIM_EEV_DIV8 = LL_HRTIM_EE_PRESCALER_DIV8,

} hal_hrtim_eev_prescaler_t;

/**
  * @brief HAL HRTIM combined event sources.
  */
typedef enum
{
  /** Combined event A is connected to external event 1 */
  HAL_HRTIM_EEVA_SRC_EEV1 = LL_HRTIM_EEVA_SRC_EEV1,

  /** Combined event A is connected to external event 11 */
  HAL_HRTIM_EEVA_SRC_EEV11 = LL_HRTIM_EEVA_SRC_EEV11,

  /** Combined event A is connected to external events 1 and 2 */
  HAL_HRTIM_EEVA_SRC_EEV1_EEV2 = LL_HRTIM_EEVA_SRC_EEV1_EEV2,

  /** Combined event A is connected to external events 1 and 11 */
  HAL_HRTIM_EEVA_SRC_EEV1_EEV11 = LL_HRTIM_EEVA_SRC_EEV1_EEV11,

  /** Combined event B is connected to external event 2 */
  HAL_HRTIM_EEVB_SRC_EEV2 = LL_HRTIM_EEVB_SRC_EEV2,

  /** Combined event B is connected to external event 12 */
  HAL_HRTIM_EEVB_SRC_EEV12 = LL_HRTIM_EEVB_SRC_EEV12,

  /** Combined event B is connected to external events 2 and 3 */
  HAL_HRTIM_EEVB_SRC_EEV2_EEV3 = LL_HRTIM_EEVB_SRC_EEV2_EEV3,

  /** Combined event B is connected to external events 2 and 12 */
  HAL_HRTIM_EEVB_SRC_EEV2_EEV12 = LL_HRTIM_EEVB_SRC_EEV2_EEV12,

  /** Combined event C is connected to external event 3 */
  HAL_HRTIM_EEVC_SRC_EEV3 = LL_HRTIM_EEVC_SRC_EEV3,

  /** Combined event C is connected to external event 13 */
  HAL_HRTIM_EEVC_SRC_EEV13 = LL_HRTIM_EEVC_SRC_EEV13,

  /** Combined event C is connected to external events 3 and 4 */
  HAL_HRTIM_EEVC_SRC_EEV3_EEV4 = LL_HRTIM_EEVC_SRC_EEV3_EEV4,

  /** Combined event C is connected to external events 3 and 13 */
  HAL_HRTIM_EEVC_SRC_EEV3_EEV13 = LL_HRTIM_EEVC_SRC_EEV3_EEV13,

  /** Combined event D is connected to external event 4 */
  HAL_HRTIM_EEVD_SRC_EEV4 = LL_HRTIM_EEVD_SRC_EEV4,

  /** Combined event D is connected to external event 14 */
  HAL_HRTIM_EEVD_SRC_EEV14 = LL_HRTIM_EEVD_SRC_EEV14,

  /** Combined event D is connected to external events 4 and 5 */
  HAL_HRTIM_EEVD_SRC_EEV4_EEV5 = LL_HRTIM_EEVD_SRC_EEV4_EEV5,

  /** Combined event D is connected to external events 4 and 14 */
  HAL_HRTIM_EEVD_SRC_EEV4_EEV14 = LL_HRTIM_EEVD_SRC_EEV4_EEV14,

  /** Combined event E is connected to external event 5 */
  HAL_HRTIM_EEVE_SRC_EEV5 = LL_HRTIM_EEVE_SRC_EEV5,

  /** Combined event E is connected to external event 15 */
  HAL_HRTIM_EEVE_SRC_EEV15 = LL_HRTIM_EEVE_SRC_EEV15,

  /** Combined event E is connected to external events 5 and 6 */
  HAL_HRTIM_EEVE_SRC_EEV5_EEV6 = LL_HRTIM_EEVE_SRC_EEV5_EEV6,

  /** Combined event E is connected to external events 5 and 15 */
  HAL_HRTIM_EEVE_SRC_EEV5_EEV15 = LL_HRTIM_EEVE_SRC_EEV5_EEV15,

  /** Combined event F is connected to external event 6 */
  HAL_HRTIM_EEVF_SRC_EEV6 = LL_HRTIM_EEVF_SRC_EEV6,

  /** Combined event F is connected to external event 16 */
  HAL_HRTIM_EEVF_SRC_EEV16 = LL_HRTIM_EEVF_SRC_EEV16,

  /** Combined event F is connected to external events 6 and 7 */
  HAL_HRTIM_EEVF_SRC_EEV6_EEV7 = LL_HRTIM_EEVF_SRC_EEV6_EEV7,

  /** Combined event F is connected to external events 6 and 16 */
  HAL_HRTIM_EEVF_SRC_EEV6_EEV16 = LL_HRTIM_EEVF_SRC_EEV6_EEV16,

  /** Combined event G is connected to external event 7 */
  HAL_HRTIM_EEVG_SRC_EEV7 = LL_HRTIM_EEVG_SRC_EEV7,

  /** Combined event G is connected to external event 11 */
  HAL_HRTIM_EEVG_SRC_EEV11 = LL_HRTIM_EEVG_SRC_EEV11,

  /** Combined event G is connected to external events 7 and 8 */
  HAL_HRTIM_EEVG_SRC_EEV7_EEV8 = LL_HRTIM_EEVG_SRC_EEV7_EEV8,

  /** Combined event G is connected to external events 7 and 11 */
  HAL_HRTIM_EEVG_SRC_EEV7_EEV11 = LL_HRTIM_EEVG_SRC_EEV7_EEV11,

  /** Combined event H is connected to external event 8 */
  HAL_HRTIM_EEVH_SRC_EEV8 = LL_HRTIM_EEVH_SRC_EEV8,

  /** Combined event H is connected to external event 12 */
  HAL_HRTIM_EEVH_SRC_EEV12 = LL_HRTIM_EEVH_SRC_EEV12,

  /** Combined event H is connected to external events 8 and 9 */
  HAL_HRTIM_EEVH_SRC_EEV8_EEV9 = LL_HRTIM_EEVH_SRC_EEV8_EEV9,

  /** Combined event H is connected to external events 8 and 12 */
  HAL_HRTIM_EEVH_SRC_EEV8_EEV12 = LL_HRTIM_EEVH_SRC_EEV8_EEV12,

  /** Combined event I is connected to external event 9 */
  HAL_HRTIM_EEVI_SRC_EEV9 = LL_HRTIM_EEVI_SRC_EEV9,

  /** Combined event I is connected to external event 13 */
  HAL_HRTIM_EEVI_SRC_EEV13 = LL_HRTIM_EEVI_SRC_EEV13,

  /** Combined event I is connected to external events 9 and 10 */
  HAL_HRTIM_EEVI_SRC_EEV9_EEV10 = LL_HRTIM_EEVI_SRC_EEV9_EEV10,

  /** Combined event I is connected to external events 9 and 13 */
  HAL_HRTIM_EEVI_SRC_EEV9_EEV13 = LL_HRTIM_EEVI_SRC_EEV9_EEV13,

  /** Combined event J is connected to external event 10 */
  HAL_HRTIM_EEVJ_SRC_EEV10 = LL_HRTIM_EEVJ_SRC_EEV10,

  /** Combined event J is connected to external event 14 */
  HAL_HRTIM_EEVJ_SRC_EEV14 = LL_HRTIM_EEVJ_SRC_EEV14,

  /** Combined event J is connected to external events 10 and 11 */
  HAL_HRTIM_EEVJ_SRC_EEV10_EEV11 = LL_HRTIM_EEVJ_SRC_EEV10_EEV11,

  /** Combined event J is connected to external events 10 and 14 */
  HAL_HRTIM_EEVJ_SRC_EEV10_EEV14 = LL_HRTIM_EEVJ_SRC_EEV10_EEV14,

} hal_hrtim_combined_eev_src_t;

/**
  * @brief HAL HRTIM external event notification mode.
  */
typedef enum
{
  /** Event is ignored if it happens during a blanking period, or passed through during a given time window */
  HAL_HRTIM_EEV_IMMEDIATE =  LL_HRTIM_EELATCH_DISABLE,

  /** Event is latched and delayed till the end of the blanking period or time window */
  HAL_HRTIM_EEV_POSTPONED =  LL_HRTIM_EELATCH_ENABLE,

} hal_hrtim_eev_notification_t;

/**
  * @brief HAL HRTIM external event filter configuration structure.
  *        Structure containing the information allowing to configure external event filtering at timing unit level.
  */
typedef struct
{
  /** HRTIM external event filter  (see @ref Event_Blanking_Windowing).
      Blanking mode: external event is ignored if it happens during a given blanking period.
      Windowing mode: external event is taken into account only if it occurs within a given time window. */
  uint32_t filter;

  /** HRTIM External Event notification mode (immediate or postponed) */
  hal_hrtim_eev_notification_t notification;

} hal_hrtim_eev_filter_config_t;

/**
  * @brief HAL HRTIM external event counter identifier.
  */
typedef enum
{
  /** Counter external event Y */
  HAL_HRTIM_EEV_COUNTER_Y =  LL_HRTIM_EE_COUNTER_Y,

  /** Counter external event Z */
  HAL_HRTIM_EEV_COUNTER_Z =  LL_HRTIM_EE_COUNTER_Z,

} hal_hrtim_eev_counter_t;

/**
  * @brief HAL HRTIM external event counter reset mode.
  */
typedef enum
{
  /** Event counter is reset on each reset / roll-over event */
  HAL_HRTIM_EEV_COUNTER_RESET_UNCONDITIONAL =  LL_HRTIM_EE_COUNTER_RSTMODE_UNCONDITIONAL,

  /** Event counter is reset on each reset / roll-over event only if no event occurs during last
      counting period */
  HAL_HRTIM_EEV_COUNTER_RESET_CUMULATIVE =  LL_HRTIM_EE_COUNTER_RSTMODE_CONDITIONAL,

} hal_hrtim_eev_counter_reset_mode_t;

/**
  * @brief HAL HRTIM external event counter configuration structure.
  */
typedef struct
{
  /** External Event Counter source selection (see @ref Combined_Event_Identifiers) */
  uint32_t event;

  /** External Event Counter threshold.
      This parameter can be a number between Min_Data = 0x0 and Max_Data = 0x3F.
      External event selected as event counter source is propagated to the timer only if the number
      of active edges is greater or equal to the counter threshold. */
  uint32_t threshold;

  /** External Event Counter reset mode */
  hal_hrtim_eev_counter_reset_mode_t reset_mode;

} hal_hrtim_eev_counter_config_t;

/**
  * @brief HAL HRTIM event counter status.
  */
typedef enum
{
  /** Event counter is disabled */
  HAL_HRTIM_EEV_COUNTER_DISABLED =  0U,

  /** Event counter is enabled */
  HAL_HRTIM_EEV_COUNTER_ENABLED =  1U,

} hal_hrtim_eev_counter_status_t;

/**
  * @brief HAL HRTIM fault input source.
  *
  * Bits 24:8     | Bits 7:0
  * ------------- | ----------------
  * Fault source  | Fault identifier
  *
  */
typedef enum
{
  /** Fault input 1 is connected to GPIO */
  HAL_HRTIM_FLT1_GPIO = HAL_HRTIM_FLT1,

  /** Fault input 1 is connected to COMP2_OUT */
  HAL_HRTIM_FLT1_COMP2 = ((LL_HRTIM_FLT1SRC_COMP2 << LL_HRTIM_FLT_SRC_POS) | HAL_HRTIM_FLT1),

  /** Fault input 2 is connected to GPIO */
  HAL_HRTIM_FLT2_GPIO = HAL_HRTIM_FLT2,

  /** Fault input 2 is connected to COMP4_OUT */
  HAL_HRTIM_FLT2_COMP4 = ((LL_HRTIM_FLT2SRC_COMP4 << LL_HRTIM_FLT_SRC_POS) | HAL_HRTIM_FLT2),

  /** Fault input 3 is connected to GPIO */
  HAL_HRTIM_FLT3_GPIO = HAL_HRTIM_FLT3,

  /** Fault input 3 is connected to COMP6_OUT */
  HAL_HRTIM_FLT3_COMP6 = ((LL_HRTIM_FLT3SRC_COMP6 << LL_HRTIM_FLT_SRC_POS) | HAL_HRTIM_FLT3),

  /** Fault input 4 is connected to GPIO */
  HAL_HRTIM_FLT4_GPIO = HAL_HRTIM_FLT4,

  /** Fault input 4 is connected to COMP1_OUT */
  HAL_HRTIM_FLT4_COMP1 = ((LL_HRTIM_FLT4SRC_COMP1 << LL_HRTIM_FLT_SRC_POS) | HAL_HRTIM_FLT4),

  /** Fault input 5 is connected to GPIO */
  HAL_HRTIM_FLT5_GPIO = HAL_HRTIM_FLT5,

  /** Fault input 5 is connected to COMP3_OUT */
  HAL_HRTIM_FLT5_COMP3 = ((LL_HRTIM_FLT5SRC_COMP3 << LL_HRTIM_FLT_SRC_POS) | HAL_HRTIM_FLT5),

  /** Fault input 6 is connected to GPIO */
  HAL_HRTIM_FLT6_GPIO = HAL_HRTIM_FLT6,

  /** Fault input 6 is connected to COMP5_OUT */
  HAL_HRTIM_FLT6_COMP5 = ((LL_HRTIM_FLT6SRC_COMP5 << LL_HRTIM_FLT_SRC_POS) | HAL_HRTIM_FLT6),

  /** Fault input 7 is connected to GPIO */
  HAL_HRTIM_FLT7_GPIO = HAL_HRTIM_FLT7,

  /** Fault input 7 is connected to COMP7_OUT */
  HAL_HRTIM_FLT7_COMP7 = ((LL_HRTIM_FLT7SRC_COMP7 << LL_HRTIM_FLT_SRC_POS) | HAL_HRTIM_FLT7),

  /** Fault input 8 is connected to GPIO */
  HAL_HRTIM_FLT8_GPIO = HAL_HRTIM_FLT8,

  /** Fault input 8 is connected to COMP8_OUT */
  HAL_HRTIM_FLT8_COMP8 = ((LL_HRTIM_FLT8SRC_COMP8 << LL_HRTIM_FLT_SRC_POS) | HAL_HRTIM_FLT8),


} hal_hrtim_flt_src_t;

/**
  * @brief HAL HRTIM system fault input source.
  *
  * Bits 17:16           | Bits 15:0
  * -------------------- | ----------
  * HRTIM instance mask  |  source
  *
  */
typedef enum
{
  HAL_HRTIM_SYSFLT_PWM_SAFE = ((LL_HRTIM_INSTANCE_HRTIM2 | LL_HRTIM_INSTANCE_HRTIM1) \
                               | LL_HRTIM_SYSFLTSRC_PWM_SAFE),
  HAL_HRTIM_SYSFLT_HSP_BREAK0_PWM_SAFE = ((LL_HRTIM_INSTANCE_HRTIM1) \
                                          | LL_HRTIM_SYSFLTSRC_HSP_BREAK0_PWM_SAFE),
  HAL_HRTIM_SYSFLT_HSP_BREAK2_PWM_SAFE = ((LL_HRTIM_INSTANCE_HRTIM2) | \
                                          LL_HRTIM_SYSFLTSRC_HSP_BREAK2_PWM_SAFE),
} hal_hrtim_sysflt_src_t;

/**
  * @brief HAL HRTIM fault input polarity.
  */
typedef enum
{
  /** Fault input is active low   */
  HAL_HRTIM_FLT_LOW = LL_HRTIM_FLT_POLARITY_LOW,

  /** fault input is active high  */
  HAL_HRTIM_FLT_HIGH = LL_HRTIM_FLT_POLARITY_HIGH,

} hal_hrtim_flt_polarity_t;

/**
  * @brief HAL HRTIM fault input configuration.
  */
typedef struct
{
  /** Fault input source */
  hal_hrtim_flt_src_t source;

  /** Fault input polarity */
  hal_hrtim_flt_polarity_t polarity;

  /** Fault input digital filter */
  hal_hrtim_filter_t filter;

} hal_hrtim_flt_config_t;

/**
  * @brief HAL HRTIM fault input prescaler.
  *        Division ratio between the HR_Timer clock frequency (fHRTIM) and the fault
  *        signal sampling clock frequency fFLTS) used by the digital filters.
  */
typedef enum
{
  /** fFLTS = fHRTIM */
  HAL_HRTIM_FLT_DIV1 = LL_HRTIM_FLT_PRESCALER_DIV1,

  /** fFLTS = fHRTIM/2 */
  HAL_HRTIM_FLT_DIV2 = LL_HRTIM_FLT_PRESCALER_DIV2,

  /** fFLTS = fHRTIM/4 */
  HAL_HRTIM_FLT_DIV4 = LL_HRTIM_FLT_PRESCALER_DIV4,

  /** fFLTS = fHRTIM/8 */
  HAL_HRTIM_FLT_DIV8 = LL_HRTIM_FLT_PRESCALER_DIV8,

} hal_hrtim_flt_prescaler_t;

/**
  * @brief HAL HRTIM fault input blanking source.
  *
  * Bit 16           | Bits 15:0
  * ---------------- | ----------------
  * Blanking source  | Fault identifier
  *
  *   Bit 16: blanking source\n
  *   0: Reset aligned window\n
  *   1: Moving window
  *
  */
typedef enum
{
  /** Blanking from Timer A reset/roll-over to Timer A compare 3 event */
  HAL_HRTIM_FLT_BLK_TARST_TACMP3 = HAL_HRTIM_FLT1,

  /** Blanking from Timer A compare 4 event to Timer A compare 3 event */
  HAL_HRTIM_FLT_BLK_TACMP4_TACMP3 = (LL_HRTIM_FLTBLK_SEL | HAL_HRTIM_FLT1),

  /** Blanking from Timer B reset/roll-over to Timer B compare 3 event */
  HAL_HRTIM_FLT_BLK_TBRST_TBCMP3 = HAL_HRTIM_FLT2,

  /** Blanking from Timer B compare 4 event to Timer B compare 3 event */
  HAL_HRTIM_FLT_BLK_TBCMP4_TBCMP3 = (LL_HRTIM_FLTBLK_SEL | HAL_HRTIM_FLT2),

  /** Blanking from Timer C reset/roll-over to Timer C compare 3 event */
  HAL_HRTIM_FLT_BLK_TCRST_TCCMP3 = HAL_HRTIM_FLT3,

  /** Blanking from Timer C compare 4 event to Timer C compare 3 event */
  HAL_HRTIM_FLT_BLK_TCCMP4_TCCMP3 = (LL_HRTIM_FLTBLK_SEL | HAL_HRTIM_FLT3),

  /** Blanking from Timer D reset/roll-over to Timer D compare 3 event */
  HAL_HRTIM_FLT_BLK_TDRST_TDCMP3 = HAL_HRTIM_FLT4,

  /** Blanking from Timer D compare 4 event to Timer D compare 3 event */
  HAL_HRTIM_FLT_BLK_TDCMP4_TDCMP3 = (LL_HRTIM_FLTBLK_SEL | HAL_HRTIM_FLT4),

  /** Blanking from Timer E reset/roll-over to Timer E compare 3 event */
  HAL_HRTIM_FLT_BLK_TERST_TECMP3 = HAL_HRTIM_FLT5,

  /** Blanking from Timer E compare 4 event to Timer E compare 3 event */
  HAL_HRTIM_FLT_BLK_TECMP4_TECMP3 = (LL_HRTIM_FLTBLK_SEL | HAL_HRTIM_FLT5),

  /** Blanking from Timer F reset/roll-over to Timer F compare 3 event */
  HAL_HRTIM_FLT_BLK_TFRST_TFCMP3 = HAL_HRTIM_FLT6,

  /** Blanking from Timer F compare 4 event to Timer F compare 3 event */
  HAL_HRTIM_FLT_BLK_TFCMP4_TFCMP3 = (LL_HRTIM_FLTBLK_SEL | HAL_HRTIM_FLT6),

  /** Blanking from Timer D reset/roll-over to Timer D compare 1 event */
  HAL_HRTIM_FLT_BLK_TDRST_TDCMP1 = HAL_HRTIM_FLT7,

  /** Blanking from Timer D compare 2 event to Timer D compare 1 event */
  HAL_HRTIM_FLT_BLK_TDCMP2_TDCMP1 = (LL_HRTIM_FLTBLK_SEL | HAL_HRTIM_FLT7),

  /** Blanking from Timer F reset/roll-over to Timer F compare 1 event */
  HAL_HRTIM_FLT_BLK_TFRST_TFCMP1 = HAL_HRTIM_FLT8,

  /** Blanking from Timer F compare 2 event to Timer F compare 1 event */
  HAL_HRTIM_FLT_BLK_TFCMP2_TFCMP1 = (LL_HRTIM_FLTBLK_SEL | HAL_HRTIM_FLT8),

} hal_hrtim_flt_blk_t;

/**
  * @brief HAL HRTIM fault blanking status.
  */
typedef enum
{
  /** Fault blanking is disabled */
  HAL_HRTIM_FLT_BLK_DISABLED = 0U,

  /** Fault blanking is enabled */
  HAL_HRTIM_FLT_BLK_ENABLED = 1U,

} hal_hrtim_flt_blk_status_t;

/**
  * @brief HAL HRTIM fault input status.
  */
typedef enum
{
  /** Fault input is disabled */
  HAL_HRTIM_FLT_DISABLED = 0U,

  /** Fault input is enabled */
  HAL_HRTIM_FLT_ENABLED = 1U,

} hal_hrtim_flt_status_t;

/**
  * @brief HAL HRTIM fault counter reset mode.
  */
typedef enum
{
  /** Fault counter is reset on each reset / roll-over event */
  HAL_HRTIM_FLT_COUNTER_RESET_UNCONDITIONAL =  LL_HRTIM_FLT_COUNTERRST_UNCONDITIONAL,

  /** Fault counter is reset on each reset / roll-over event only if no event occurs during last
      counting period */
  HAL_HRTIM_FLT_COUNTER_RESET_CUMULATIVE =  LL_HRTIM_FLT_COUNTERRST_CONDITIONAL,

} hal_hrtim_flt_counter_reset_mode_t;


/**
  * @brief HAL HRTIM fault counter configuration structure.
  */
typedef struct
{
  /** Fault Counter threshold.
      This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF.
      Fault is propagated to the timer only if the number of fault detection events is greater or equal
      to the counter threshold. */
  uint8_t threshold;

  /** Fault Counter reset mode */
  hal_hrtim_flt_counter_reset_mode_t reset_mode;

} hal_hrtim_flt_counter_config_t;

/**
  * @brief HAL HRTIM burst mode operating mode.
  */
typedef enum
{
  /** The idle sequence is executed once, following the burst mode trigger */
  HAL_HRTIM_BURST_MODE_SINGLE_SHOT = LL_HRTIM_BM_MODE_SINGLE_SHOT,

  /** The burst mode is maintained until it is explicitly terminated */
  HAL_HRTIM_BURST_MODE_CONTINUOUS =  LL_HRTIM_BM_MODE_CONTINUOUS,

} hal_hrtim_burst_mode_operating_mode_t;

/**
  * @brief HAL HRTIM burst mode clock source.
  */
typedef enum
{
  /** The burst mode counter is clocked by Master timer counter reset/roll-over event */
  HAL_HRTIM_BURST_MODE_CLK_MASTER =  LL_HRTIM_BM_CLKSRC_MASTER,

  /** The burst mode counter is clocked by timer A counter reset/roll-over event */
  HAL_HRTIM_BURST_MODE_CLK_TIMA =  LL_HRTIM_BM_CLKSRC_TIMA,

  /** The burst mode counter is clocked by timer counter B reset/roll-over event */
  HAL_HRTIM_BURST_MODE_CLK_TIMB =  LL_HRTIM_BM_CLKSRC_TIMB,

  /** The burst mode counter is clocked by timer counter C reset/roll-over event */
  HAL_HRTIM_BURST_MODE_CLK_TIMC =  LL_HRTIM_BM_CLKSRC_TIMC,

  /** The burst mode counter is clocked by timer counter D reset/roll-over event */
  HAL_HRTIM_BURST_MODE_CLK_TIMD =  LL_HRTIM_BM_CLKSRC_TIMD,

  /** The burst mode counter is clocked by timer counter E reset/roll-over event */
  HAL_HRTIM_BURST_MODE_CLK_TIME =  LL_HRTIM_BM_CLKSRC_TIME,

  /** The burst mode counter is clocked by timer counter F reset/roll-over event */
  HAL_HRTIM_BURST_MODE_CLK_TIMF =  LL_HRTIM_BM_CLKSRC_TIMF,

  /** The burst mode counter is clocked by TIM12 output channel 1 */
  HAL_HRTIM_BURST_MODE_CLK_TIM12_OC1 =  LL_HRTIM_BM_CLKSRC_TIM12_OC1,

  /** The burst mode counter is clocked by TIM13 output channel 1 */
  HAL_HRTIM_BURST_MODE_CLK_TIM13_OC1 =  LL_HRTIM_BM_CLKSRC_TIM13_OC1,

  /** The burst mode counter is clocked by TIM7 trigger output */
  HAL_HRTIM_BURST_MODE_CLK_TIM7_TRGO =  LL_HRTIM_BM_CLKSRC_TIM7_TRGO,

  /** The burst mode counter is clocked by TIM10 output channel 1 */
  HAL_HRTIM_BURST_MODE_CLK_TIM10_OC1 =  LL_HRTIM_BM_CLKSRC_TIM10_OC1,

  /** The burst mode counter is clocked by prescaled main HRTIM clock (fHRTIM) clock */
  HAL_HRTIM_BURST_MODE_CLK_HRTIM =  LL_HRTIM_BM_CLKSRC_HRTIM,

} hal_hrtim_burst_mode_clock_src_t;

/**
  * @brief HAL HRTIM burst mode prescaler.
  *        Division ratio between the HRTIM clock frequency (fHRTIM) and the burst
  *        mode controller counter clock frequency (fBRST).
  */
typedef enum
{
  /** fBRST = fHRTIM */
  HAL_HRTIM_BURST_MODE_DIV1 = LL_HRTIM_BM_PRESCALER_DIV1,

  /** fBRST = fHRTIM/2 */
  HAL_HRTIM_BURST_MODE_DIV2 = LL_HRTIM_BM_PRESCALER_DIV2,

  /** fBRST = fHRTIM/4 */
  HAL_HRTIM_BURST_MODE_DIV4 = LL_HRTIM_BM_PRESCALER_DIV4,

  /** fBRST = fHRTIM/8 */
  HAL_HRTIM_BURST_MODE_DIV8 = LL_HRTIM_BM_PRESCALER_DIV8,

  /** fBRST = fHRTIM/16 */
  HAL_HRTIM_BURST_MODE_DIV16 = LL_HRTIM_BM_PRESCALER_DIV16,

  /** fBRST = fHRTIM/32 */
  HAL_HRTIM_BURST_MODE_DIV32 = LL_HRTIM_BM_PRESCALER_DIV32,

  /** fBRST = fHRTIM/64 */
  HAL_HRTIM_BURST_MODE_DIV64 = LL_HRTIM_BM_PRESCALER_DIV64,

  /** fBRST = fHRTIM/128 */
  HAL_HRTIM_BURST_MODE_DIV128 = LL_HRTIM_BM_PRESCALER_DIV128,

  /** fBRST = fHRTIM/256 */
  HAL_HRTIM_BURST_MODE_DIV256 = LL_HRTIM_BM_PRESCALER_DIV256,

  /** fBRST = fHRTIM/512 */
  HAL_HRTIM_BURST_MODE_DIV512 = LL_HRTIM_BM_PRESCALER_DIV512,

  /** fBRST = fHRTIM/1024 */
  HAL_HRTIM_BURST_MODE_DIV1024 = LL_HRTIM_BM_PRESCALER_DIV1024,

  /** fBRST = fHRTIM/2048 */
  HAL_HRTIM_BURST_MODE_DIV2048 = LL_HRTIM_BM_PRESCALER_DIV2048,

  /** fBRST = fHRTIM/4096 */
  HAL_HRTIM_BURST_MODE_DIV4096 = LL_HRTIM_BM_PRESCALER_DIV4096,

  /** fBRST = fHRTIM/8192 */
  HAL_HRTIM_BURST_MODE_DIV8192 = LL_HRTIM_BM_PRESCALER_DIV8192,

  /** fBRST = fHRTIM/16384 */
  HAL_HRTIM_BURST_MODE_DIV16384 = LL_HRTIM_BM_PRESCALER_DIV16384,

  /** fBRST = fHRTIM/32768 */
  HAL_HRTIM_BURST_MODE_DIV32768 = LL_HRTIM_BM_PRESCALER_DIV32768,

} hal_hrtim_burst_mode_prescaler_t;

/**
  * @brief HAL HRTIM burst mode configuration structure.
  *         Overall burst mode period is the sum of the idle and run periods.
  */
typedef struct
{
  /** Operating mode*/
  hal_hrtim_burst_mode_operating_mode_t mode;

  /** clock source */
  hal_hrtim_burst_mode_clock_src_t clock;

  /** prescaler */
  hal_hrtim_burst_mode_prescaler_t prescaler;

  /** Number of run periods.
      This parameter can be a number between Min_Data = 0x0000
      and Max_Data = 0xFFFF */
  uint16_t period;

  /** Number of idle periods
      This parameter can be a number between Min_Data = 0x0000
      and Max_Data = 0xFFFF */
  uint16_t idle_periods;

  /** Burst mode trigger(s) (see @ref Burst_Mode_Triggers) */
  uint32_t triggers;

} hal_hrtim_burst_mode_config_t;

/**
  * @brief HAL HRTIM timer burst mode.
  */
typedef enum
{
  /** Timer counter clock is maintained and the timer operates normally during the burst idle period */
  HAL_HRTIM_TIM_BURST_MODE_MAINTAIN = LL_HRTIM_BURSTMODE_MAINTAINCLOCK,

  /** Timer counter clock is stopped and the counter is reset during the burst idle period */
  HAL_HRTIM_TIM_BURST_MODE_STOP_AND_RESET = LL_HRTIM_BURSTMODE_RESETCOUNTER,

} hal_hrtim_timer_burst_mode_t;

/**
  * @brief HAL HRTIM output burst mode.
  *
  * HRTIM_OUTxR programming:
  * Burst mode | IDLEM | DIDL
  * ---------- | ----- | ----
  * DISABLED   |   0   |   x
  * IMMEDIATE  |   1   |   0
  * DELAYED    |   1   |   1
  *
  */
typedef enum
{
  /** The output is not affected by the burst mode operation */
  HAL_HRTIM_OUT_BURST_MODE_DISABLE = LL_HRTIM_OUT_NO_IDLE,

  /** Configured Idle state is applied immediately to the output */
  HAL_HRTIM_OUT_BURST_MODE_IMMEDIATE = (LL_HRTIM_OUT_IDLE_WHEN_BURST | LL_HRTIM_OUT_BM_ENTRYMODE_REGULAR),

  /** Deadtime is inserted on output before entering the idle mode */
  HAL_HRTIM_OUT_BURST_MODE_DELAYED = (LL_HRTIM_OUT_IDLE_WHEN_BURST | LL_HRTIM_OUT_BM_ENTRYMODE_DELAYED),

} hal_hrtim_output_burst_mode_t;

/**
  * @brief HAL HRTIM burst mode preload status.
  */
typedef enum
{
  /** Burst mode preload is disabled */
  HAL_HRTIM_BURST_MODE_PRELOAD_DISABLED = 0U,

  /** Burst mode preload is enabled */
  HAL_HRTIM_BURST_MODE_PRELOAD_ENABLED = 1U,

} hal_hrtim_burst_mode_preload_status_t;

/**
  * @brief HAL HRTIM burst mode status.
  */
typedef enum
{
  /** Burst mode is disabled */
  HAL_HRTIM_BURST_MODE_DISABLED = 0U,

  /** Burst mode is enabled */
  HAL_HRTIM_BURST_MODE_ENABLED = 1U,

} hal_hrtim_burst_mode_status_t;

/**
  * @brief HAL HRTIM Burst mode operating status.
  */
typedef enum
{
  /** Normal operation */
  HAL_HRTIM_BURST_MODE_INACTIVE = 0U,

  /** Burst mode on going */
  HAL_HRTIM_BURST_MODE_ACTIVE = LL_HRTIM_BM_STATUS_BURST_ONGOING,

} hal_hrtim_burst_mode_operating_status_t;

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/**
  * @brief HAL HRTIM DMA burst configuration structure.
  */
typedef struct
{
  /** DMA burst source (see @ref Timer_Identifiers) */
  uint32_t timer;

  /** Timer's DMA request source to enable (see @ref DMA_Requests) */
  uint32_t requests;

  /** Master timer registers to be updated by the DMA burst operation (see @ref DMA_Burst_Update) */
  uint32_t master_update;

  /** Timer A registers to be updated by the DMA burst operation (see @ref DMA_Burst_Update) */
  uint32_t timer_a_update;

  /** Timer B registers to be updated by the DMA burst operation (see @ref DMA_Burst_Update) */
  uint32_t timer_b_update;

  /** Timer C registers to be updated by the DMA burst operation (see @ref DMA_Burst_Update) */
  uint32_t timer_c_update;

  /** Timer D registers to be updated by the DMA burst operation (see @ref DMA_Burst_Update) */
  uint32_t timer_d_update;

  /** Timer E registers to be updated by the DMA burst operation (see @ref DMA_Burst_Update) */
  uint32_t timer_e_update;

  /** Timer F registers to be updated by the DMA burst operation (see @ref DMA_Burst_Update) */
  uint32_t timer_f_update;

} hal_hrtim_dmaburst_config_t;
#endif /* USE_HAL_HRTIM_DMA */

/**
  * @brief HAL HRTIM timer clock prescaler ratio.
  *        Division ratio between the high-resolution equivalent clock frequency (fHRCK) and the HRTIM clock
  *        frequency (fHRTIM).
  */
typedef enum
{
  /** fHRCK: fHRTIM */
  HAL_HRTIM_TIM_PRESCALER_DIV1 = LL_HRTIM_PRESCALERRATIO_DIV1,

  /** fHRCK: fHRTIM / 2 */
  HAL_HRTIM_TIM_PRESCALER_DIV2 = LL_HRTIM_PRESCALERRATIO_DIV2,

  /** fHRCK: fHRTIM / 4 */
  HAL_HRTIM_TIM_PRESCALER_DIV4 = LL_HRTIM_PRESCALERRATIO_DIV4,

} hal_hrtim_timer_prescaler_t;

/**
  * @brief HAL HRTIM timer operating mode.
  */
typedef enum
{
  /** The timer operates in continuous (free-running) mode */
  HAL_HRTIM_TIM_MODE_CONTINUOUS = LL_HRTIM_MODE_CONTINUOUS,

  /** The timer operates in non retriggerable single-shot mode */
  HAL_HRTIM_TIM_MODE_SINGLESHOT = LL_HRTIM_MODE_SINGLESHOT,

  /** The timer operates in retriggerable single-shot mode */
  HAL_HRTIM_TIM_MODE_SINGLESHOT_RETRIGGERABLE = LL_HRTIM_MODE_SINGLESHOT_RETRIGGERABLE,

} hal_hrtim_timer_operating_mode_t;

/**
  * @brief HAL HRTIM timer counter mode.
  */
typedef enum
{
  /** Counter is operating in up-counting mode */
  HAL_HRTIM_TIM_COUNTING_UP = LL_HRTIM_COUNTING_MODE_UP,

  /** Counter is operating in up-down counting mode */
  HAL_HRTIM_TIM_COUNTING_UP_DOWN = LL_HRTIM_COUNTING_MODE_UP_DOWN,

} hal_hrtim_timer_counting_mode_t;

/**
  * @brief HAL HRTIM timer configuration structure.
  */
typedef struct
{
  /** Timer period
      The period value must be above 3 periods of the fHRTIM clock.
      Maximum value is 0xFFFD.
  */
  uint16_t period;

  /** Timer repetition counter
      This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF */
  uint16_t repetition;

  /** Timer operating mode */
  hal_hrtim_timer_operating_mode_t operating_mode;

  /** Timer counter mode */
  hal_hrtim_timer_counting_mode_t counting_mode;

  /** Clock prescaler ratio*/
  hal_hrtim_timer_prescaler_t prescaler;

} hal_hrtim_timer_config_t;

/**
  * @brief HAL HRTIM roll-over mode destination.
  */
typedef enum
{
  /** Roll-over configuration destined the update trigger, IRQ and DMA requests, repetition counter decrement and
      external event filtering. */
  HAL_HRTIM_ROLL_OVER_UPDATE = 0U,

  /** Roll-over configuration destined to the set/reset crossbar */
  HAL_HRTIM_ROLL_OVER_OUTPUT = 1U,

  /** Roll-over configuration destined to the ADC triggers */
  HAL_HRTIM_ROLL_OVER_ADC = 2U,

  /** Roll-over configuration destined to the burst mode controller */
  HAL_HRTIM_ROLL_OVER_BURST_MODE = 3U,

  /** Roll-over configuration destined to the fault and event counters */
  HAL_HRTIM_ROLL_OVER_FLT_EEV = 4U,

} hal_hrtim_roll_over_destination_t;

/**
  * @brief HAL HRTIM roll-over event generation mode.
  */
typedef enum
{
  /** Roll-over event is generated when the counter is equal to 0 or to the period value */
  HAL_HRTIM_ROLL_OVER_BOTH = 0U,

  /** Roll-over event is generated when the counter is equal to 0 */
  HAL_HRTIM_ROLL_OVER_VALLEY = 1U,

  /** Roll-over event is generated when the counter is equal to the period value */
  HAL_HRTIM_ROLL_OVER_CREST = 2U,

} hal_hrtim_roll_over_mode_t;

/**
  * @brief HAL HRTIM register preload status.
  */
typedef enum
{
  /** Register preload is disabled (write access is directly done into the active register) */
  HAL_HRTIM_PRELOAD_DISABLED = 0U,

  /** Register preload is enabled (write access is done into the preload register) */
  HAL_HRTIM_PRELOAD_ENABLED = 1U,

} hal_hrtim_preload_status_t;

/**
  * @brief HAL HRTIM preloaded registers update triggers.
  */
typedef enum
{
  /** The update occurs independently from the DMA burst transfer */
  HAL_HRTIM_UPDATE_DMABURST_INDEPENDENT = LL_HRTIM_UPDATEGAT_INDEPENDENT,

  /** The update occurs when the DMA burst transfer is completed */
  HAL_HRTIM_UPDATE_DMABURST_COMPLETE = LL_HRTIM_UPDATEGAT_DMABURST_COMPLETE,

  /** The update occurs on the update event following the DMA burst transfer completion */
  HAL_HRTIM_UPDATE_DMABURST_UPDATE = LL_HRTIM_UPDATEGAT_DMABURST_UPDATE,

  /** Preloaded registers are updated following a rising edge on TIM10 OC1 signal.
      Applicable to timing units only (HAL_HRTIM_TIMx, with x = A to F) */
  HAL_HRTIM_UPDATE_TIM10_OC1 = LL_HRTIM_UPDATEGAT_TIM10_OC1,

  /** Preloaded registers are updated following a rising edge on TIM11 OC1 signal.
      Applicable to timing units only (HAL_HRTIM_TIMx, with x = A to F) */
  HAL_HRTIM_UPDATE_TIM11_OC1 = LL_HRTIM_UPDATEGAT_TIM11_OC1,

  /** Preloaded registers are updated following a rising edge on TIM11 OC1 signal.
      Applicable to timing units only (HAL_HRTIM_TIMx, with x = A to F) */
  HAL_HRTIM_UPDATE_TIM6_TRGO = LL_HRTIM_UPDATEGAT_TIM6_TRGO,

  /** Preloaded registers are updated on the update event following a rising edge on TIM10 OC1 signal.
      Applicable to timing units only (HAL_HRTIM_TIMx, with x = A to F) */
  HAL_HRTIM_UPDATE_TIM10_OC1_UPDATE = LL_HRTIM_UPDATEGAT_TIM10_OC1_UPDATE,

  /** Preloaded registers are updated on the update event following a rising edge on TIM11 OC1 signal.
      Applicable to timing units only (HAL_HRTIM_TIMx, with x = A to F) */
  HAL_HRTIM_UPDATE_TIM11_OC1_UPDATE = LL_HRTIM_UPDATEGAT_TIM11_OC1_UPDATE,

  /** Preloaded registers are updated on the update event following a rising edge on TIM6 TRGO signal.
      Applicable to timing units only (HAL_HRTIM_TIMx, with x = A to F) */
  HAL_HRTIM_UPDATE_TIM6_TRGO_UPDATE = LL_HRTIM_UPDATEGAT_TIM6_TRGO_UPDATE,

} hal_hrtim_update_gating_t;

/**
  * @brief HAL HRTIM timer update status.
  */
typedef enum
{
  /** Update event generation is disabled */
  HAL_HRTIM_UPDATE_DISABLED = 0U,

  /** Update event generation is enabled */
  HAL_HRTIM_UPDATE_ENABLED = 1U,

} hal_hrtim_update_status_t;

/**
  * @brief HAL HRTIM remote timer update status.
  */
typedef enum
{
  /** Remote Timer update is disabled. */
  HAL_HRTIM_REMOTE_UPDATE_DISABLED = 0U,

  /** Remote Timer update is disabled. */
  HAL_HRTIM_REMOTE_UPDATE_ENABLED = 1U,

} hal_hrtim_remote_update_status_t;

/**
  * @brief HAL HRTIM remote timer update request status.
  */
typedef enum
{
  /** Remote Timer update request is ignored. */
  HAL_HRTIM_REMOTE_UPDATE_REQ_DISABLED = 0U,

  /** Remote Timer update request is authorized. */
  HAL_HRTIM_REMOTE_UPDATE_REQ_ENABLED = 1U,

} hal_hrtim_remote_update_request_status_t;

/**
  * @brief HAL HRTIM timer re-synchronized update status.
  *        The update coming from adjacent timers or from a software update
  *        can either be taken into account immediately or re-synchronized with
  *        the timers reset/roll-over event.
  */
typedef enum
{
  /** The update coming from adjacent timers or from a software update is taken into account immediately */
  HAL_HRTIM_UPDATE_RESYNC_DISABLED = 0U,

  /** The update coming from adjacent timers or from a software update is taken into account on the following
      reset/roll-over event. */
  HAL_HRTIM_UPDATE_RESYNC_ENABLED = 1U,

} hal_hrtim_update_resync_status_t;

/**
  * @brief HAL HRTIM output Channel polarity.
  */
typedef enum
{
  /** Output active level is HIGH */
  HAL_HRTIM_OUTPUT_ACTIVE_HIGH = LL_HRTIM_OUT_POSITIVE_POLARITY,

  /** Output active level is LOW */
  HAL_HRTIM_OUTPUT_ACTIVE_LOW = LL_HRTIM_OUT_NEGATIVE_POLARITY,

} hal_hrtim_output_polarity_t;

/**
  * @brief HAL HRTIM output channel IDLE level.
  */
typedef enum
{
  /** Output at inactive level when in IDLE state */
  HAL_HRTIM_OUTPUT_IDLE_INACTIVE = LL_HRTIM_OUT_IDLELEVEL_INACTIVE,

  /** Output at active level when in IDLE state */
  HAL_HRTIM_OUTPUT_IDLE_ACTIVE = LL_HRTIM_OUT_IDLELEVEL_ACTIVE,

} hal_hrtim_output_idle_level_t;

/**
  * @brief HAL HRTIM output channel FAULT level.
  */
typedef enum
{
  /** The output is not affected by the fault input */
  HAL_HRTIM_OUTPUT_FAULT_NONE = LL_HRTIM_OUT_FAULTSTATE_NONE,

  /** Output at active level when in FAULT state */
  HAL_HRTIM_OUTPUT_FAULT_ACTIVE = LL_HRTIM_OUT_FAULTSTATE_ACTIVE,

  /** Output at inactive level when in FAULT state */
  HAL_HRTIM_OUTPUT_FAULT_INACTIVE = LL_HRTIM_OUT_FAULTSTATE_INACTIVE,

  /** Output is tri-stated when in FAULT state */
  HAL_HRTIM_OUTPUT_FAULT_HIGHZ = LL_HRTIM_OUT_FAULTSTATE_HIGHZ,

} hal_hrtim_output_fault_level_t;

/**
  * @brief HAL HRTIM output channel configuration structure.
  */
typedef struct
{
  /** Combination of events forcing the output to its ACTIVE level (see @ref Output_Set_Events) */
  uint32_t set;

  /** Combination of events forcing the output to its INACTIVE level (see @ref Output_Reset_Events) */
  uint32_t reset;

  /** Output polarity */
  hal_hrtim_output_polarity_t polarity;

  /** Output IDLE level */
  hal_hrtim_output_idle_level_t idle_level;

  /** Output FAULT level */
  hal_hrtim_output_fault_level_t fault_level;

} hal_hrtim_output_config_t;

/**
  * @brief HAL HRTIM output level.
  */
typedef enum
{
  /** Output is currently set to its INACTIVE level either by the crossbar unit or by the burst mode controller */
  HAL_HRTIM_OUTPUT_INACTIVE = 0U,

  /** Output is currently set to its ACTIVE level either by the crossbar unit or by the burst mode controller */
  HAL_HRTIM_OUTPUT_ACTIVE = 1U,

} hal_hrtim_output_level_t;

/**
  * @brief HAL HRTIM output swap status.
  */
typedef enum
{
  /** Timer's outputs aren't swapped */
  HAL_HRTIM_SWAP_DISABLED = 0U,

  /** Timer's outputs are swapped */
  HAL_HRTIM_SWAP_ENABLED = 1U,

} hal_hrtim_swap_mode_status_t;

/**
  * @brief HAL HRTIM interleaved modes.
  *
  * HRTIM_TIMxCR programming:
  * Interleaved mode | INTLVD[1:0] | HALF
  * ---------------- | -----       | ----
  * DISABLED         |     0 0     |   0
  * DUAL             |     0 0     |   1
  * TRIPLE           |     0 1     |   0
  * QUAD             |     1 0     |   0
  *
  */
typedef enum
{
  /** Interleaved mode disabled */
  HAL_HRTIM_INTERLEAVED_DISABLE = LL_HRTIM_INTERLEAVED_MODE_DISABLE,

  /** Dual interleaved 180 degrees */
  HAL_HRTIM_INTERLEAVED_DUAL = LL_HRTIM_INTERLEAVED_MODE_DUAL,

  /** Triple interleaved 120 degrees */
  HAL_HRTIM_INTERLEAVED_TRIPLE = LL_HRTIM_INTERLEAVED_MODE_TRIPLE,

  /** Quad interleaved 90 degrees */
  HAL_HRTIM_INTERLEAVED_QUAD = LL_HRTIM_INTERLEAVED_MODE_QUAD,

} hal_hrtim_interleaved_mode_t;

/**
  * @brief HAL HRTIM greater than (GT) comparison status.
  */
typedef enum
{
  /** Greater than compare mode is disabled. The compare event is generated when the counter is equal to
      the compare value (regular compare match mode) */
  HAL_HRTIM_GTCMP_DISABLED = 0U,

  /** Greater than compare mode is enabled. The compare event is generated when the counter is greater than the
      compare value. If the compare value is changed on-the-fly, the new compare value is compared with the current
      counter value and an output SET or RESET can be generated. */
  HAL_HRTIM_GTCMP_ENABLED = 1U,

} hal_hrtim_greater_than_compare_status_t;

/**
  * @brief HAL HRTIM triggered half mode.
  */
typedef enum
{
  /** Triggered-half mode is disabled: compare 2 value is set by software only */
  HAL_HRTIM_TRIG_HALF_DISABLE = LL_HRTIM_TRIGHALF_DISABLE,

  /** Triggered-half mode is enabled: compare 2 value is set set by hardware as soon as a capture 1 event occurs */
  HAL_HRTIM_TRIG_HALF_ENABLE = LL_HRTIM_TRIGHALF_ENABLE,

  /** Triggered-half mode is enabled: compare 2 value is set set by hardware as soon as a capture 1 event occurs.
      If no capture is triggered when the counter matches the period value, compare 2 value is set to period/2
      (timeout on period). */
  HAL_HRTIM_TRIG_HALF_ENABLE_TIMEOUT = LL_HRTIM_TRIGHALF_ENABLE_TIMEOUT,

} hal_hrtim_trig_half_mode_t;

/**
  * @brief HAL HRTIM auto-delayed modes.
  */
typedef enum
{
  /** Standard compare mode */
  HAL_HRTIM_AUTODELAYED_DISABLE = LL_HRTIM_COMPAREMODE_REGULAR,

  /** Compare event generated only if a capture has occurred */
  HAL_HRTIM_AUTODELAYED_TIMEOUT_NONE = LL_HRTIM_COMPAREMODE_DELAY_NOTIMEOUT,

  /** Compare event generated if a capture has occurred or after a compare 1 match
     (timeout if capture event is missing) */
  HAL_HRTIM_AUTODELAYED_TIMEOUT_CMP1 = LL_HRTIM_COMPAREMODE_DELAY_CMP1,

  /** Compare event generated if a capture has occurred or after a compare 3 match
     (timeout if capture event is missing) */
  HAL_HRTIM_AUTODELAYED_TIMEOUT_CMP3 = LL_HRTIM_COMPAREMODE_DELAY_CMP3,

} hal_hrtim_auto_delayed_mode_t;

/**
  * @brief HAL HRTIM auto-delayed mode configuration structure.
  */
typedef struct
{
  /** Auto delayed mode */
  hal_hrtim_auto_delayed_mode_t mode;

  /** Timeout value (significant only for auto-delayed mode with timeout) */
  uint16_t timeout_cycles;

} hal_hrtim_auto_delayed_config_t;


/**
  * @brief HAL HRTIM capture direction status.
  */
typedef enum
{
  /** Timer was counting up when the capture event occurred */
  HAL_HRTIM_DIRECTION_UP = LL_HRTIM_COUNTING_MODE_UP,

  /** Timer was counting down when the capture event occurred */
  HAL_HRTIM_DIRECTION_DOWN = LL_HRTIM_COUNTING_MODE_UP_DOWN,

} hal_hrtim_capture_direction_t;

/**
  * @brief HAL HRTIM capture information.
  */
typedef struct
{
  /** counter value when the capture event occurred */
  uint16_t value;

  /** Counting direction when the capture event occurred */
  hal_hrtim_capture_direction_t direction;

} hal_hrtim_capture_t;

/**
  * @brief HAL HRTIM delayed protection modes.
  */
typedef enum
{
  /** The selected external event causes the output to enter in idle mode at the end of the active pulse */
  HAL_HRTIM_DELAYED_IDLE = 0U,

  /** The pulsewidth, terminated earlier than programmed, is copied on the alternate output, then the two outputs are
      put in idle state, until the normal operation is resumed by software */
  HAL_HRTIM_BALANCED_IDLE = 1U,

  /** The pulse width, terminated earlier than programmed, is copied on the alternate output, then the two outputs are
      put in idle state. Outputs are automatically re-enabled after a balanced idle event.  */
  HAL_HRTIM_BALANCED_IDLE_AUTO_RESUME = 2U,

} hal_hrtim_delayed_protection_mode_t;

/**
  * @brief HAL HRTIM Timing unit output(s).
  */
typedef enum
{
  /** Timer A..F output 1 */
  HAL_HRTIM_TIM_OUT1 = 0x1,

  /** Timer A..F output 2 */
  HAL_HRTIM_TIM_OUT2 = 0x2,

  /** Timer A..F both output 1 and output 2 */
  HAL_HRTIM_TIM_OUT1_OUT2 = 0x3

} hal_hrtim_tim_outputs_t;

/**
  * @brief HAL HRTIM delayed protection configuration structure.
  */
typedef struct
{
  /** Delayed protection mode */
  hal_hrtim_delayed_protection_mode_t mode;

  /** External event triggering the delayed protection
      Timers A, B or C: HAL_HRTIM_EEVF or HAL_HRTIM_EEVG
      Timers D, E or F: HAL_HRTIM_EEVH or HAL_HRTIM_EEVI
  */
  uint32_t event;

  /** The delayed idle mode can be applied to a single output or to both outputs */
  hal_hrtim_tim_outputs_t outputs;

} hal_hrtim_delayed_prot_config_t;

/**
  * @brief HAL HRTIM delayed protection status.
  */
typedef enum
{
  /** Delayed protection is disabled */
  HAL_HRTIM_DELAYED_PROTECTION_DISABLED = 0U,

  /** Delayed protection is enabled */
  HAL_HRTIM_DELAYED_PROTECTION_ENABLED = 1U,

} hal_hrtim_delayed_protection_status_t;

/**
  * @brief HAL HRTIM balanced idle automatic resume status.
  */
typedef enum
{
  /** Balanced idle automatic resume is disabled */
  HAL_HRTIM_BIAR_DISABLED = 0U,

  /** Balanced idle automatic resume is enabled */
  HAL_HRTIM_BIAR_ENABLED = 1U,

} hal_hrtim_balanced_idle_auto_resume_status_t;

/**
  * @brief HAL HRTIM deadtime mode.
  */
typedef enum
{
  /** Deadtime is generated from a single reference waveform to produce a couple of complementary signals. */
  HAL_HRTIM_DEADTIME_COMPLEMENTARY = LL_HRTIM_DT_MODE_COMPLEMENTARY,

  /** Deadtime is inserted between two independent signals. */
  HAL_HRTIM_DEADTIME_INSERTION = LL_HRTIM_DT_MODE_INSERTION,

  /** Deadtime is inserted between two independent signals. Output 2 is disarmed (i.e, it can't be set again)
      until the next reset/roll-over event. */
  HAL_HRTIM_DEADTIME_INSERTION_AND_DISARM = LL_HRTIM_DT_MODE_INSERTION_AND_DISARM,

} hal_hrtim_deadtime_mode_t;

/**
  * @brief HAL HRTIM deadtime insertion edges.
  */
typedef enum
{
  /** Rising edge deadtime */
  HAL_HRTIM_DEADTIME_RISING = 0U,

  /** Falling edge deadtime */
  HAL_HRTIM_DEADTIME_FALLING = 1U,

} hal_hrtim_deadtime_t;

/**
  * @brief HAL HRTIM deadtime sign.
  */
typedef enum
{
  /** Positive deadtime (signals not overlapping) */
  HAL_HRTIM_DEADTIME_POSITIVE = LL_HRTIM_DT_RISING_POSITIVE,

  /** Negative deadtime (signals overlapping) */
  HAL_HRTIM_DEADTIME_NEGATIVE = LL_HRTIM_DT_RISING_NEGATIVE,

} hal_hrtim_deadtime_sign_t;

/**
  * @brief HAL HRTIM deadtime configuration structure.
  */
typedef struct
{
  /** Deadtime value. Can be a number between Min_Data = 0x00 and Max_Data = 0x1FF */
  uint16_t value;

  /** Deadtime sign */
  hal_hrtim_deadtime_sign_t sign;

} hal_hrtim_deadtime_config_t;

/**
  * @brief HAL HRTIM deadtime lock level.
  */
typedef enum
{
  /** Lock the deadtime rising/falling sign */
  HAL_HRTIM_DEADTIME_LOCK_SIGN = 0U,

  /** Lock the deadtime rising/falling sign and value */
  HAL_HRTIM_DEADTIME_LOCK_SIGN_AND_VALUE = 1U,

} hal_hrtim_deadtime_lock_t;


/**
  * @brief HAL HRTIM deadtime prescaler.
  *        Prescaler value for the deadtime generator time step (tDTG) relative to the HR-Timer clock
  *        period (tHRTIM)
  */
typedef enum
{
  /** tDTG = tHRTIM * 16 */
  HAL_HRTIM_DEADTIME_MUL16  = LL_HRTIM_DT_PRESCALER_MUL16,

  /** tDTG = tHRTIM * 8 */
  HAL_HRTIM_DEADTIME_MUL8  = LL_HRTIM_DT_PRESCALER_MUL8,

  /** tDTG = tHRTIM * 4 */
  HAL_HRTIM_DEADTIME_MUL4  = LL_HRTIM_DT_PRESCALER_MUL4,

  /** tDTG = tHRTIM * 2 */
  HAL_HRTIM_DEADTIME_MUL2  = LL_HRTIM_DT_PRESCALER_MUL2,

  /** tDTG = tHRTIM / 1 */
  HAL_HRTIM_DEADTIME_DIV1  = LL_HRTIM_DT_PRESCALER_DIV1,

} hal_hrtim_deadtime_prescaler_t;

/**
  * @brief HAL HRTIM deadtime lock status.
  */
typedef enum
{
  /** Read/write access to deadtime configuration */
  HAL_HRTIM_DEADTIME_UNLOCKED = 0U,

  /** Read-only access to deadtime rising/falling sign configuration */
  HAL_HRTIM_DEADTIME_LOCKED_SIGN = 1U,

  /** Read-only access to deadtime rising/falling sign and value configuration */
  HAL_HRTIM_DEADTIME_LOCKED_SIGN_AND_VALUE = 2U,

} hal_hrtim_deadtime_lock_status_t;

/**
  * @brief HAL HRTIM deadtime insertion status.
  */
typedef enum
{
  /** Deadtime insertion is disabled */
  HAL_HRTIM_DEADTIME_DISABLED = 0U,

  /** Deadtime insertion is enabled */
  HAL_HRTIM_DEADTIME_ENABLED = 1U,

} hal_hrtim_deadtime_status_t;

/**
  * @brief HAL HRTIM chopper prescaler.
  *        Ratio between the chopper clock frequency (fCHPFRQ) and the HRTIM clock frequency (fHRTIM).
  */
typedef enum
{
  /** fCHPFRQ = fHRTIM / 16  */
  HAL_HRTIM_CHOPPER_DIV16 = LL_HRTIM_CHP_PRESCALER_DIV16,

  /** fCHPFRQ = fHRTIM / 32  */
  HAL_HRTIM_CHOPPER_DIV32 = LL_HRTIM_CHP_PRESCALER_DIV32,

  /** fCHPFRQ = fHRTIM / 48  */
  HAL_HRTIM_CHOPPER_DIV48 = LL_HRTIM_CHP_PRESCALER_DIV48,

  /** fCHPFRQ = fHRTIM / 48  */
  HAL_HRTIM_CHOPPER_DIV64 = LL_HRTIM_CHP_PRESCALER_DIV64,

  /** fCHPFRQ = fHRTIM / 80  */
  HAL_HRTIM_CHOPPER_DIV80 = LL_HRTIM_CHP_PRESCALER_DIV80,

  /** fCHPFRQ = fHRTIM / 96  */
  HAL_HRTIM_CHOPPER_DIV96 = LL_HRTIM_CHP_PRESCALER_DIV96,

  /** fCHPFRQ = fHRTIM / 112  */
  HAL_HRTIM_CHOPPER_DIV112 = LL_HRTIM_CHP_PRESCALER_DIV112,

  /** fCHPFRQ = fHRTIM / 128  */
  HAL_HRTIM_CHOPPER_DIV128 = LL_HRTIM_CHP_PRESCALER_DIV128,

  /** fCHPFRQ = fHRTIM / 144  */
  HAL_HRTIM_CHOPPER_DIV144 = LL_HRTIM_CHP_PRESCALER_DIV144,

  /** fCHPFRQ = fHRTIM / 160  */
  HAL_HRTIM_CHOPPER_DIV160 = LL_HRTIM_CHP_PRESCALER_DIV160,

  /** fCHPFRQ = fHRTIM / 176  */
  HAL_HRTIM_CHOPPER_DIV176 = LL_HRTIM_CHP_PRESCALER_DIV176,

  /** fCHPFRQ = fHRTIM / 192  */
  HAL_HRTIM_CHOPPER_DIV192 = LL_HRTIM_CHP_PRESCALER_DIV192,

  /** fCHPFRQ = fHRTIM / 208  */
  HAL_HRTIM_CHOPPER_DIV208 = LL_HRTIM_CHP_PRESCALER_DIV208,

  /** fCHPFRQ = fHRTIM / 224  */
  HAL_HRTIM_CHOPPER_DIV224 = LL_HRTIM_CHP_PRESCALER_DIV224,

  /** fCHPFRQ = fHRTIM / 240  */
  HAL_HRTIM_CHOPPER_DIV240 = LL_HRTIM_CHP_PRESCALER_DIV240,

  /** fCHPFRQ = fHRTIM / 256  */
  HAL_HRTIM_CHOPPER_DIV256 = LL_HRTIM_CHP_PRESCALER_DIV256,

} hal_hrtim_chopper_prescaler_t;

/**
  * @brief HAL HRTIM chopper first pulse width.
  *        Multiplication factor used to calculate the width of the initial pulse in chopper mode (t1STPW) from the
  *        HRTIM clock period (tHRTIM).
  */
typedef enum
{
  /** t1STPW = tHRTIM * 16  */
  HAL_HRTIM_CHOPPER_MUL16 = LL_HRTIM_CHP_PULSEWIDTH_16,

  /** t1STPW = tHRTIM * 32  */
  HAL_HRTIM_CHOPPER_MUL32 = LL_HRTIM_CHP_PULSEWIDTH_32,

  /** t1STPW = tHRTIM * 48  */
  HAL_HRTIM_CHOPPER_MUL48 = LL_HRTIM_CHP_PULSEWIDTH_48,

  /** t1STPW = tHRTIM * 48  */
  HAL_HRTIM_CHOPPER_MUL64 = LL_HRTIM_CHP_PULSEWIDTH_64,

  /** t1STPW = tHRTIM * 80  */
  HAL_HRTIM_CHOPPER_MUL80 = LL_HRTIM_CHP_PULSEWIDTH_80,

  /** t1STPW = tHRTIM * 96  */
  HAL_HRTIM_CHOPPER_MUL96 = LL_HRTIM_CHP_PULSEWIDTH_96,

  /** t1STPW = tHRTIM * 112  */
  HAL_HRTIM_CHOPPER_MUL112 = LL_HRTIM_CHP_PULSEWIDTH_112,

  /** t1STPW = tHRTIM * 128  */
  HAL_HRTIM_CHOPPER_MUL128 = LL_HRTIM_CHP_PULSEWIDTH_128,

  /** t1STPW = tHRTIM * 144  */
  HAL_HRTIM_CHOPPER_MUL144 = LL_HRTIM_CHP_PULSEWIDTH_144,

  /** t1STPW = tHRTIM * 160  */
  HAL_HRTIM_CHOPPER_MUL160 = LL_HRTIM_CHP_PULSEWIDTH_160,

  /** t1STPW = tHRTIM * 176  */
  HAL_HRTIM_CHOPPER_MUL176 = LL_HRTIM_CHP_PULSEWIDTH_176,

  /** t1STPW = tHRTIM * 192  */
  HAL_HRTIM_CHOPPER_MUL192 = LL_HRTIM_CHP_PULSEWIDTH_192,

  /** t1STPW = tHRTIM * 208  */
  HAL_HRTIM_CHOPPER_MUL208 = LL_HRTIM_CHP_PULSEWIDTH_208,

  /** t1STPW = tHRTIM * 224  */
  HAL_HRTIM_CHOPPER_MUL224 = LL_HRTIM_CHP_PULSEWIDTH_224,

  /** t1STPW = tHRTIM * 240  */
  HAL_HRTIM_CHOPPER_MUL240 = LL_HRTIM_CHP_PULSEWIDTH_240,

  /** t1STPW = tHRTIM * 256  */
  HAL_HRTIM_CHOPPER_MUL256 = LL_HRTIM_CHP_PULSEWIDTH_256,

} hal_hrtim_chopper_pulse_t;

/**
  * @brief HAL HRTIM chopper duty cycle.
  *        Constant defining the (positive) duty cycle of the generated high frequency carrier.
  *        Duty cycle can be adjusted by 1/8 (12.5%) step, from 0/8 (0%) up to 7/8 (87.5%).
  */
typedef enum
{
  /** Duty cycle of the carrier signal is 0%. Only 1st pulse is present */
  HAL_HRTIM_CHOPPER_DTY0 = LL_HRTIM_CHP_DUTYCYCLE_0,

  /** Duty cycle of the carrier signal is 12.5 % */
  HAL_HRTIM_CHOPPER_DTY125 = LL_HRTIM_CHP_DUTYCYCLE_125,

  /** Duty cycle of the carrier signal is 25 % */
  HAL_HRTIM_CHOPPER_DTY250 = LL_HRTIM_CHP_DUTYCYCLE_250,

  /** Duty cycle of the carrier signal is 37.5 % */
  HAL_HRTIM_CHOPPER_DTY375 = LL_HRTIM_CHP_DUTYCYCLE_375,

  /** Duty cycle of the carrier signal is 50 % */
  HAL_HRTIM_CHOPPER_DTY500 = LL_HRTIM_CHP_DUTYCYCLE_500,

  /** Duty cycle of the carrier signal is 62.5 % */
  HAL_HRTIM_CHOPPER_DTY625 = LL_HRTIM_CHP_DUTYCYCLE_625,

  /** Duty cycle of the carrier signal is 75 % */
  HAL_HRTIM_CHOPPER_DTY750 = LL_HRTIM_CHP_DUTYCYCLE_750,

  /** Duty cycle of the carrier signal is 87.5 % */
  HAL_HRTIM_CHOPPER_DTY875 = LL_HRTIM_CHP_DUTYCYCLE_875,

} hal_hrtim_chopper_duty_cycle_t;

/**
  * @brief HAL HRTIM chopper mode configuration structure.
  */
typedef struct
{
  /** Chopper prescaler determining the carrier frequency value */
  hal_hrtim_chopper_prescaler_t prescaler;

  /** Length of the initial pulse */
  hal_hrtim_chopper_pulse_t start_pulse_width;

  /** Duty cycle */
  hal_hrtim_chopper_duty_cycle_t duty_cycle;

} hal_hrtim_chopper_config_t;

/**
  * @brief HAL HRTIM output chopper status.
  */
typedef enum
{
  /** Chopper is disabled on HRTIM output */
  HAL_HRTIM_CHOPPER_DISABLED = 0U,

  /** Chopper is enabled on HRTIM output */
  HAL_HRTIM_CHOPPER_ENABLED = 1U,

} hal_hrtim_chopper_status_t;

/**
  * @brief HAL HRTIM push-pull status.
  */
typedef enum
{
  /** push-pull mode is disabled */
  HAL_HRTIM_PUSHPULL_DISABLED = 0U,

  /** Push-pull mode is enabled */
  HAL_HRTIM_PUSHPULL_ENABLED = 1U,

} hal_hrtim_pushpull_status_t;

/**
  * @brief HAL HRTIM push-pull current status.
  *        Indicates on which output the signal is currently applied, in push-pull mode.
  */
typedef enum
{
  /** Signal applied on output 1 and output 2 forced inactive */
  HAL_HRTIM_PUSHPULL_CURRENT_OUT1 = LL_HRTIM_CPPSTAT_OUT1,

  /** Signal applied on output 2 and output 1 forced inactive */
  HAL_HRTIM_PUSHPULL_CURRENT_OUT2 = LL_HRTIM_CPPSTAT_OUT2,

} hal_hrtim_pushpull_current_output_t;

/**
  * @brief HAL HRTIM push-pull idle status.
  *        Indicates on which output the signal was applied, in push-pull mode balanced fault mode or delayed idle
  *        mode, when the protection was triggered.
  */
typedef enum
{
  /** Protection occurred when the output 1 was active and output 2 forced inactive */
  HAL_HRTIM_PUSHPULL_IDLE_OUT1 = LL_HRTIM_IPPSTAT_OUT1,

  /** Protection occurred when the output 2 was active and output 1 forced inactive */
  HAL_HRTIM_PUSHPULL_IDLE_OUT2 = LL_HRTIM_IPPSTAT_OUT2,

} hal_hrtim_pushpull_idle_output_t;

/**
  * @brief HAL HRTIM push-pull ADC trigger.
  *        Possibility to have the ADC triggered only while output 1 (resp. output 2) is active (in push-pull mode).
  */
typedef enum
{
  /** ADC triggers are generated only when the output 1 is active */
  HAL_HRTIM_PUSHPULL_ADC_OUT1 = LL_HRTIM_ADCTRIG_OUT1,

  /** ADC triggers are generated only when the output 2 is active */
  HAL_HRTIM_PUSHPULL_ADC_OUT2 = LL_HRTIM_ADCTRIG_OUT2,

  /** ADC triggers are generated when both Channel 1 and Channel 2 are active */
  HAL_HRTIM_PUSHPULL_ADC_OUT1_OUT2 = LL_HRTIM_ADCTRIG_OUT1_OUT2,

} hal_hrtim_pushpull_adc_trigger_t;


/**
  * @brief HAL HRTIM crossbar override mode.
  *        Determines how the crossbar override logic operates.
  */
typedef enum
{
  /** Crossbar override is automatically disengaged on the next reset/roll-over event following the disappearance
      of the triggering condition */
  HAL_HRTIM_XBAR_OVR_CYCLE_BY_CYCLE = LL_HRTIM_CO_MODE_CYCLE_BY_CYCLE,

  /** Once activated, crossbar override remains engaged until disengaged by software (crossbar override rearm) */
  HAL_HRTIM_XBAR_OVR_LATCHED = LL_HRTIM_CO_MODE_LATCHED,

} hal_hrtim_xbar_ovr_mode_t;

/**
  * @brief HAL HRTIM crossbar override configuration structure.
  */
typedef struct
{
  /** Crossbar override triggers (see @ref Xbar_Ovr_triggers)  */
  uint32_t triggers;

  /** Crossbar override mode */
  hal_hrtim_xbar_ovr_mode_t mode;

} hal_hrtim_xbar_ovr_config_t;

/**
  * @brief HAL HRTIM crossbar override force mode.
  *        Determines how an output is handled once the crossbar override mode is triggered.
  */
typedef enum
{
  /** Output is forced to its ACTIVE level */
  HAL_HRTIM_XBAR_OVR_FORCE_ACTIVE = LL_HRTIM_CO_FORCEMODE_ACTIVE,

  /** Output is forced to its INACTIVE level */
  HAL_HRTIM_XBAR_OVR_FORCE_INACTIVE = LL_HRTIM_CO_FORCEMODE_INACTIVE,

  /** Output is forced to its INACTIVE level after Delay 1 */
  HAL_HRTIM_XBAR_OVR_FORCE_DELAY1 = LL_HRTIM_CO_FORCEMODE_DELAY1,

  /** Output is forced to its INACTIVE level after Delay 2 */
  HAL_HRTIM_XBAR_OVR_FORCE_DELAY2 = LL_HRTIM_CO_FORCEMODE_DELAY2,

  /** Output is forced to its ACTIVE level on selected combined event(s) */
  HAL_HRTIM_XBAR_OVR_FORCE_EVENT = LL_HRTIM_CO_FORCEMODE_EVENT,

} hal_hrtim_xbar_ovr_force_mode_t;

/**
  * @brief HAL HRTIM crossbar override delay option.
  *        Configurable delays when the delayed fault operation (HAL_HRTIM_XBAR_OVR_FORCE_DELAY1/2)
  *        is selected as crossbar override force mode.
  */
typedef enum
{
  /** Delayed 1 fault duration */
  HAL_HRTIM_XBAR_OVR_DELAY1 = LL_HRTIM_CO_FORCEMODE_DELAY1,

  /** Delayed 2 fault duration */
  HAL_HRTIM_XBAR_OVR_DELAY2 = LL_HRTIM_CO_FORCEMODE_DELAY2,

} hal_hrtim_xbar_ovr_delay_option_t;

/**
  * @brief HAL HRTIM crossbar override status.
  */
typedef enum
{
  /** Crossbar override is disabled */
  HAL_HRTIM_XBAR_OVR_DISABLED = 0U,

  /** Crossbar override is enabled */
  HAL_HRTIM_XBAR_OVR_ENABLED = 1U,

} hal_hrtim_xbar_ovr_status_t;

/**
  * @brief HAL HRTIM dual channel DAC crossbar override status.
  */
typedef enum
{
  /** Dual channel DAC crossbar override is disabled */
  HAL_HRTIM_DUAL_DAC_XBAR_OVR_DISABLED = 0U,

  /** Dual channel DAC cverride is enabled */
  HAL_HRTIM_DUAL_DAC_XBAR_OVR_ENABLED = 1U,

} hal_hrtim_dual_channel_dac_xbar_ovr_status_t;

/**
  * @brief HAL HRTIM crossbar override mode status.
  */
typedef enum
{
  /** Crossbar override mode is engaged */
  HAL_HRTIM_XBAR_OVR_MODE_INACTIVE = LL_HRTIM_CO_STATUS_INACTIVE,

  /** Crossbar override is disengaged */
  HAL_HRTIM_XBAR_OVR_MODE_ACTIVE = LL_HRTIM_CO_STATUS_ACTIVE,

} hal_hrtim_xbar_ovr_mode_status_t;

/**
  * @brief HAL HRTIM crossbar override trigger status.
  */
typedef enum
{
  /** Crossbar override trigger is active */
  HAL_HRTIM_XBAR_OVR_TRIGGER_INACTIVE = LL_HRTIM_CO_TRIGGER_INACTIVE,

  /** Crossbar override trigger is inactive */
  HAL_HRTIM_XBAR_OVR_TRIGGER_ACTIVE = LL_HRTIM_CO_TRIGGER_ACTIVE,

} hal_hrtim_xbar_ovr_trigger_status_t;

/**
  * @brief HAL HRTIM handle type definition.
  */

/** HAL HRTIM handler type */
typedef struct hal_hrtim_handle_s hal_hrtim_handle_t;

/*
 * Types definitions for the callbacks
 */
#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)

#if defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
/** HAL HRTIM generic callback function pointer type definition */
typedef void (* hal_hrtim_cb_t)(hal_hrtim_handle_t *hhrtim);

/** HAL HRTIM fault callback function pointer type definition */
typedef void (* hal_hrtim_fault_cb_t)(hal_hrtim_handle_t *hhrtim, uint32_t fault);
#endif /* USE_HAL_HRTIM_GLOBAL_CALLBACKS */

#if (defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)) \
 || (defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)) \
 || (defined(USE_HAL_HRTIM_XBAR_OVR_CALLBACKS) && (USE_HAL_HRTIM_XBAR_OVR_CALLBACKS == 1))
/** HAL HRTIM timer callback pointer type definition */
typedef void (* hal_hrtim_timer_cb_t)(hal_hrtim_handle_t *hhrtim, uint32_t timer);
#endif /* USE_HAL_HRTIM_TIMER_CALLBACKS || USE_HAL_HRTIM_TIMER_CALLBACKS || USE_HAL_HRTIM_XBAR_OVR_CALLBACKS */

#if defined(USE_HAL_HRTIM_OUTPUT_CALLBACKS) && (USE_HAL_HRTIM_OUTPUT_CALLBACKS == 1)
/** HAL HRTIM output callback pointer type definition */
typedef void (* hal_hrtim_output_cb_t)(hal_hrtim_handle_t *hhrtim, uint32_t output);
#endif /* USE_HAL_HRTIM_OUTPUT_CALLBACKS */

#if defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
/** HAL HRTIM compare unit callback pointer type definition */
typedef void (* hal_hrtim_cmp_cb_t)(hal_hrtim_handle_t *hhrtim, uint32_t timer, hal_hrtim_compare_unit_t compare_unit);

/** HAL HRTIM capture unit callback pointer type definition */
typedef void (* hal_hrtim_cpt_cb_t)(hal_hrtim_handle_t *hhrtim, uint32_t timer, hal_hrtim_capture_unit_t capture_unit);
#endif /* USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */

#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */

/**
  * @brief HAL HRTIM handle structure definition
  */
struct hal_hrtim_handle_s
{
  /** HAL HRTIM instance */
  hal_hrtim_t instance;

  /** HRTIM global state */
  volatile hal_hrtim_state_t global_state;

  /** HRTIM timers states array */
  volatile hal_hrtim_timer_state_t timer_states[HRTIM_TIMERS_NB];

  /** Interrupts configuration array */
  uint32_t interrupts[HRTIM_TIMERS_NB];

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
  /** DMA Handles array */
  hal_dma_handle_t *hdma[HRTIM_TIMERS_NB];

  /** DMA configuration array */
  hal_hrtim_dma_config_t *p_dma_config[HRTIM_TIMERS_NB];
#endif /* USE_HAL_HRTIM_DMA */

#if defined(USE_HAL_HRTIM_USER_DATA) && (USE_HAL_HRTIM_USER_DATA == 1)
  /** User Data Pointer  */
  const void *p_user_data;
#endif /* USE_HAL_HRTIM_USER_DATA */

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
  /** HRTIM DMA transfer half completed callback function pointer */
  hal_hrtim_timer_cb_t dma_xfer_half_cplt_callback;

  /** HRTIM DMA transfer completed callback function pointer */
  hal_hrtim_timer_cb_t dma_xfer_cplt_callback;

  /** HRTIM DMA transfer stopped callback function pointer */
  hal_hrtim_timer_cb_t dma_xfer_stop_callback;

  /** HRTIM DMA transfer error callback function pointer */
  hal_hrtim_timer_cb_t dma_xfer_error_callback;
#endif /* USE_HAL_HRTIM_DMA && USE_HAL_HRTIM_TIMER_CALLBACKS */

#if defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
  /** HRTIM fault callback function pointer */
  hal_hrtim_fault_cb_t fault_callback;

  /** HRTIM system fault callback function pointer */
  hal_hrtim_cb_t system_fault_callback;

  /** HRTIM burst mode period callback function pointer */
  hal_hrtim_cb_t burst_mode_period_callback;

  /** HRTIM synchronization input callback function pointer */
  hal_hrtim_cb_t synchro_callback;
#endif /* USE_HAL_HRTIM_GLOBAL_CALLBACKS */

#if defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
  /** HRTIM timer registers update callback function pointer */
  hal_hrtim_timer_cb_t update_callback;

  /** HRTIM timer repetition callback function pointer */
  hal_hrtim_timer_cb_t repetition_callback;

  /** HRTIM timer counter reset callback function pointer */
  hal_hrtim_timer_cb_t reset_callback;

  /** HRTIM timer delayed protection callback function pointer */
  hal_hrtim_timer_cb_t delayed_protection_callback;
#endif /* USE_HAL_HRTIM_TIMER_CALLBACKS */

#if defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
  /** HRTIM compare Match callback function pointer */
  hal_hrtim_cmp_cb_t compare_match_callback;

  /** HRTIM capture callback function pointer */
  hal_hrtim_cpt_cb_t capture_callback;
#endif /* USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */

#if defined(USE_HAL_HRTIM_OUTPUT_CALLBACKS) && (USE_HAL_HRTIM_OUTPUT_CALLBACKS == 1)
  /** HRTIM output set callback function pointer */
  hal_hrtim_output_cb_t output_set_callback;

  /** HRTIM output reset callback function pointer */
  hal_hrtim_output_cb_t output_reset_callback;
#endif /* USE_HAL_HRTIM_OUTPUT_CALLBACKS */

#if defined(USE_HAL_HRTIM_XBAR_OVR_CALLBACKS) && (USE_HAL_HRTIM_XBAR_OVR_CALLBACKS == 1)
  /** HRTIM crossbar override trigger callback function pointer */
  hal_hrtim_timer_cb_t xbar_ovr_trigger_callback;

  /** HRTIM HRTIM crossbar override rearm delay elapsed callback function pointer */
  hal_hrtim_timer_cb_t xbar_ovr_rearm_delay_callback;
#endif /* USE_HAL_HRTIM_XBAR_OVR_CALLBACKS */

#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */

};

/**
  * @}
  */
/* End of exported types -----------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
/** @defgroup HRTIM_Exported_Functions HAL HRTIM Functions
  * @{
  */


/** @defgroup HRTIM_Exported_Functions_Group1 HRTIM Initialization/Deinitialization functions
  *
  *            To configure and control the HRTIM, several preliminary steps are required:
  *
  *            1. HRTIM Driver Initialization (Mandatory):
  *               - This step involves associating the HRTIM handle with a physical HRTIM instance.
  *               - It also nitializes the HAL HRTIM driver context data.
  *
  *            2. DMA Channel Handles Assignment (Optional):
  *               - This step involves storing the DMA handle associated with the master timer or a timing unit into
  *                 the HRTIM handle..
  *
  *            When the HRTIM instance is no longer needed, a deinitialization function can be called to reset the
  *            HAL HRTIM driver to its initial state.
  * @{
  */
hal_status_t HAL_HRTIM_Init(hal_hrtim_handle_t *hhrtim, hal_hrtim_t instance);
void HAL_HRTIM_DeInit(hal_hrtim_handle_t *hhrtim);
hal_hrtim_t HAL_HRTIM_GetInstance(const hal_hrtim_handle_t *hhrtim);
HRTIM_TypeDef *HAL_HRTIM_GetLLInstance(const hal_hrtim_handle_t *hhrtim);

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
hal_status_t HAL_HRTIM_SetDMA(hal_hrtim_handle_t *hhrtim,
                              hal_hrtim_dma_source_t dma_source,
                              hal_dma_handle_t *hdma);
#endif /* USE_HAL_HRTIM_DMA */
/**
  * @}
  */


/** @defgroup HRTIM_Exported_Functions_Group2 HRTIM Peripheral State functions
  *
  *           Several functions can be used to retrieve the current operating state of the HAL HRTIM driver, any of the
  *           timers, or any of the HRTIM outputs whenever needed.
  *
  *           Also a function is provided to get the frequency of the main HRTIM clock (fHRTIM).
  * @{
  */
hal_hrtim_state_t HAL_HRTIM_GetState(const hal_hrtim_handle_t *hhrtim);

hal_hrtim_timer_state_t HAL_HRTIM_TIM_GetState(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t timer);

hal_hrtim_output_status_t HAL_HRTIM_OUT_GetStatus(const hal_hrtim_handle_t *hhrtim,
                                                  uint32_t output);

uint32_t HAL_HRTIM_GetClockFreq(const hal_hrtim_handle_t *hhrtim);
/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group3 HRTIM interrupts and DMA requests configuration functions
  *
  *           HRTIM related interrupts and DMA request related information are stored in dedicated tables
  *           declared at application's level (if needed). They contain one element per potential interrupts
  *           or DMA requests source. Both tables are fed thanks to dedicated configuration functions.
  *
  *           The HRTIM interrupts configuration function allows to select which HRTIM interrupts must be
  *           enabled when a timer is started in interrupts mode.
  *
  *           Interrupts can be selected for the following interrupts sources:
  *            - Master timer (7 interrupts)
  *            - Timer A to F (16 interrupts)
  *            - HRTIM (10 interrupts).
  *
  *           The HRTIM interrupts configuration function allows to select which HRTIM interrupts must be
  *           enabled when a timer is started in interrupts mode.
  *
  *           DMA requests can be selected for the following DMA requests sources:
  *            - Master timer (7 DMA requests)
  *            - Timer A to F (16 DMA requests)
  *
  * @{
  */

hal_status_t HAL_HRTIM_SetConfigInterrupts(hal_hrtim_handle_t *hhrtim,
                                           hal_hrtim_interrupt_src_t source,
                                           uint32_t interrupts);

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
hal_status_t HAL_HRTIM_SetConfigDMA(hal_hrtim_handle_t *hhrtim,
                                    hal_hrtim_dma_source_t dma_source,
                                    hal_hrtim_dma_config_t *p_config);
#endif /* USE_HAL_HRTIM_DMA */

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group4 HRTIM external synchronization input/output configuration functions
  *
  *            The HRTIM provides options for synchronizing multiple HRTIM instances, as a master unit
  *            (generating a synchronization signal) or as a slave (waiting for a trigger to be synchronized).
  *
  *            Configuration of the pulse generated on the synchronization output pin (HRTIM_SCOUT).
  *
  *            Selection of the synchronization input source used to synchronize the whole HRTIM with
  *            on-chip (TIM1) or off-chip (through HRTIM_SCIN pin) resources.
  *
  *            Notes:
  *              - When needed, the synchronization output must be configured before starting the timer.
  *              - HRTIM_SCOUT pin configuration must be done after the synchronization output signal configuration.
  *
  *            When the synchronization input is enabled, it is possible to configure the behavior of each timer's
  *            counter when an active edge is detected on the synchronization input.
  *
  *            Notes:
  *              - When the synchronization input is enabled, HAL_HRTIM_TIM_Start must have been called to have the
  *                timer enabled and the counter ready to start.
  *              - The synchronization input pin (HRTIM_SCIN) is rising-edge sensitive.
  *
  * @{
  */

hal_status_t HAL_HRTIM_SetSynchroOutput(const hal_hrtim_handle_t *hhrtim,
                                        const hal_hrtim_sync_output_config_t *p_config);
void HAL_HRTIM_GetSynchroOutput(const hal_hrtim_handle_t *hhrtim,
                                hal_hrtim_sync_output_config_t *p_config);

hal_status_t HAL_HRTIM_SetSynchroInputSource(const hal_hrtim_handle_t *hhrtim,
                                             hal_hrtim_sync_input_src_t sync_input_source);
hal_hrtim_sync_input_src_t HAL_HRTIM_GetSynchroInputSource(const hal_hrtim_handle_t *hhrtim);

hal_status_t HAL_HRTIM_TIM_SetSlaveMode(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        hal_hrtim_tim_slave_mode_t slave_mode);
hal_hrtim_tim_slave_mode_t HAL_HRTIM_TIM_GetSlaveMode(const hal_hrtim_handle_t *hhrtim,
                                                      uint32_t timer);

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group5 ADC triggers configuration functions
  *
  *           The HRTIM has 10 ADC triggers (HAL_HRTIM_ADCTRG_n, n=1 to 10).
  *
  *           Each ADC trigger has 32 sources, including 5 from the master timer, 5 from external events and
  *           3 or 4 for each timing unit. For ADC triggers 1 to 4, these sources can be combined (ORed) while
  *           for ADC triggers 5 to 10 only one source can be selected.
  *
  *           Notes:
  *           - ADC triggers 1 and 3 share the same sources.
  *           - ADC triggers 2 and 4 share the same sources.
  *           - ADC triggers 5, 7 and 9 share the same sources.
  *           - ADC triggers 6, 8 and 10 share the same sources.
  *
  *           It is possible to associate an ADC trigger to a timer so that the update ot the configuration register of
  *           the ADC trigger can be synchronized with the update event of the timer it is associated with.
  *
  *           Notes:
  *           - The ADC trigger configuration register is preloaded when the registers preload mechanism is enabled for
  *             the timer it is associated with.
  *           - Update gating condition at timer level is defined by calling the xxx function.
  *
  *           Each ADC trigger rate can be reduced with a dedicated ADC post-scaler.
  * @{
  */

hal_status_t HAL_HRTIM_SetADCSynchro(const hal_hrtim_handle_t *hhrtim,
                                     hal_hrtim_adc_trigger_t adc_trigger,
                                     const hal_hrtim_adc_sync_config_t *p_config);
void HAL_HRTIM_GetADCSynchro(const hal_hrtim_handle_t *hhrtim,
                             hal_hrtim_adc_trigger_t adc_trigger,
                             hal_hrtim_adc_sync_config_t *p_config);

hal_status_t HAL_HRTIM_SetADCPostscaler(const hal_hrtim_handle_t *hhrtim,
                                        hal_hrtim_adc_trigger_t adc_trigger,
                                        uint8_t postscaler);
uint8_t HAL_HRTIM_GetADCPostscaler(const hal_hrtim_handle_t *hhrtim,
                                   hal_hrtim_adc_trigger_t adc_trigger);

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group6 DAC triggers configuration functions
  *
  *           2 standard DAC triggers allow to synchronize the DAC conversions with the timer update events from the
  *           master and the slave timers. It is possible to have multiple concurrent sources (timers) for the same
  *           DAC trigger.
  *
  *           Dual channel DAC triggers allow to synchronize the sawtooth generated by a DAC with the PWM waveform
  *           generated by a timing unit. Each timing unit support two DAC triggers, one to reset the sawtooth signal,
  *           and another one to regularly decrease the DAC values.
  * @{
  */

hal_status_t HAL_HRTIM_TIM_SetDACTrigger(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer,
                                         hal_hrtim_dac_trigger_t dac_trigger);
hal_hrtim_dac_trigger_t HAL_HRTIM_TIM_GetDACTrigger(const hal_hrtim_handle_t *hhrtim,
                                                    uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetDualChannelDACTriggers(const hal_hrtim_handle_t *hhrtim,
                                                     uint32_t timer,
                                                     const hal_hrtim_dual_channel_dac_triggers_config_t *p_config);
void HAL_HRTIM_TIM_GetDualChannelDACTriggers(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer,
                                             hal_hrtim_dual_channel_dac_triggers_config_t *p_config);

hal_status_t HAL_HRTIM_TIM_EnableDualChannelDAC(const hal_hrtim_handle_t *hhrtim,
                                                uint32_t timer);
hal_status_t HAL_HRTIM_TIM_DisableDualChannelDAC(const hal_hrtim_handle_t *hhrtim,
                                                 uint32_t timer);
hal_hrtim_dual_channel_dac_status_t HAL_HRTIM_TIM_IsEnabledDualChannelDAC(const hal_hrtim_handle_t *hhrtim,
                                                                          uint32_t timer);

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group7 HRTIM External events configuration functions
  *
  *           The HRTIM has 16 external events (HAL_HRTIM_EEVn, n=1 to 16), available for any timing unit.
  *
  *           External events are used to:
  *             - trigger the burst mode controller,
  *             - generate an ADC trigger event,
  *             - reset the timer's counter,
  *             - set or reset a HRTIM output,
  *             - trigger the delayed protection mode.
  *
  *           External event global conditioning is performed at HRTIM level (it is common to all the
  *           timing units). For each external event, the application can:
  *             - select the source of the external event,
  *             - choose between edge-sensitivity or level-sensitivity,
  *             - apply (or not) a configurable digital noise filter,
  *             - select the operating mode: synchronous (fast mode disabled) or asynchronous (fast mode enabled).
  *
  *           Note:
  *           - When digital filtering is needed, external event signal sampling clock is either the fHRTIM clock
  *             or a specific prescaled clock (fEEVS) derived from fHRTIM as per configured external event prescaler.
  *
  *           Once conditioned, the 16 external events are available for all timing units (Timer A to F).
  *          External events can be combined (HAL_HRTIM_EEVx, where x = A to J). The source for each combined event can
  *          be selected from four different options (see the tables below).
  *
  *                EEVA     |      EEVB     |      EEVC     |      EEVD     |      EEVE
  *           ------------- | ------------- | ------------- | ------------- | -------------
  *           EEV1          | EEV2          | EEV3          | EEV4          | EEV5
  *           EEV11         | EEV12         | EEV13         | EEV14         | EEV15
  *           EEV1 & EEV2   | EEV2 & EEV3   | EEV3 & EEV4   | EEV4 & EEV5   | EEV5 & EEV6
  *           EEV1 & EEV11  | EEV2 & EEV12  | EEV3 & EEV13  | EEV4 & EEV15  | EEV5 & EEV15
  *
  *                EEVF     |      EEVG     |      EEVH     |      EEVI     |      EEVJ
  *           ------------- | ------------- | ------------- | ------------- | -------------
  *           EEV6          | EEV7          | EEV8          | EEV9          | EEV10
  *           EEV16         | EEV11         | EEV12         | EEV13         | EEV14
  *           EEV6 & EEV7   | EEV7 & EEV8   | EEV8 & EEV9   | EEV9 & EEV10  | EEV10 & EEV11
  *           EEV6 & EEV16  | EEV7 & EEV11  | EEV8 & EEV12  | EEV9 & EEV13  | EEV10 & EEV14
  *
  *          Another filtering level (blanking or windowing) can be configured separately for each timing unit.
  *          Event detection can also be latched so that, resulting event notification is delayed till the end of the
  *          blanking or windowing period.
  *
  *          Note:
  *          - The external event is active as soon as the timing unit is started.
  *
  *          Each timing unit features an external event counter following the filtering unit. When the external event
  *          counter is enabled, concerned external event is propagated to the timing unit only if the number of
  *          active edges is greater or equal to a configurable threshold.
  *          External event counter is reset:
  *            - unconditionally on each reset/roll-over event (non-cumulative mode),
  *            - on reset/roll-over event only if no event occurredduring last counting period (cumulative mode),
  *            - upon software request.
  *
  *          Note:
  *          - Only edge-sensitive external events can be selected as event counter source.
  *          - The external event counter must be enabled after having programmed the counter threshold.
  *          - External event counter can be enabled or disabled on the fly.
  * @{
  */

hal_status_t HAL_HRTIM_EEV_SetPrescaler(const hal_hrtim_handle_t *hhrtim,
                                        hal_hrtim_eev_prescaler_t prescaler);
hal_hrtim_eev_prescaler_t HAL_HRTIM_EEV_GetPrescaler(const hal_hrtim_handle_t *hhrtim);

hal_status_t HAL_HRTIM_EEV_SetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t event,
                                     const hal_hrtim_eev_config_t *p_config);
hal_status_t HAL_HRTIM_EEV_GetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t event,
                                     hal_hrtim_eev_config_t *p_config);

hal_status_t HAL_HRTIM_TIM_SetCombinedEventSource(const hal_hrtim_handle_t *hhrtim,
                                                  uint32_t timer,
                                                  uint32_t event,
                                                  hal_hrtim_combined_eev_src_t combined_event_source);
hal_hrtim_combined_eev_src_t HAL_HRTIM_TIM_GetCombinedEventSource(const hal_hrtim_handle_t *hhrtim,
                                                                  uint32_t timer,
                                                                  uint32_t event);

hal_status_t HAL_HRTIM_TIM_SetEventFilter(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer,
                                          uint32_t event,
                                          const hal_hrtim_eev_filter_config_t *p_config);
hal_status_t HAL_HRTIM_TIM_GetEventFilter(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer,
                                          uint32_t event,
                                          hal_hrtim_eev_filter_config_t *p_config);

hal_status_t HAL_HRTIM_TIM_SetEventCounter(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_eev_counter_t counter,
                                           const hal_hrtim_eev_counter_config_t *p_config);
hal_status_t HAL_HRTIM_TIM_GetEventCounter(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_eev_counter_t counter,
                                           hal_hrtim_eev_counter_config_t *p_config);

hal_status_t HAL_HRTIM_TIM_SetEventCounterThreshold(const hal_hrtim_handle_t *hhrtim,
                                                    uint32_t timer,
                                                    hal_hrtim_eev_counter_t counter,
                                                    uint8_t threshold);

uint8_t HAL_HRTIM_TIM_GetEventCounterThreshold(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t timer,
                                               hal_hrtim_eev_counter_t counter);

hal_status_t HAL_HRTIM_TIM_EnableEventCounter(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timer,
                                              hal_hrtim_eev_counter_t counter);
hal_status_t HAL_HRTIM_TIM_DisableEventCounter(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t timer,
                                               hal_hrtim_eev_counter_t counter);
hal_hrtim_eev_counter_status_t HAL_HRTIM_TIM_IsEnabledEventCounter(const hal_hrtim_handle_t *hhrtim,
                                                                   uint32_t timer,
                                                                   hal_hrtim_eev_counter_t counter);

hal_status_t HAL_HRTIM_TIM_ResetEventCounter(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer,
                                             hal_hrtim_eev_counter_t counter);

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group8 HRTIM Faults configuration functions
  *
  *           The HRTIM has 8 fault inputs (HAL_HRTIM_FLTn, n=1 to 8). all of them are available
  *           and can be combined (logically ORed) for each of the 8 timing units.
  *
  *           Fault input global conditioning is performed at HRTIM level (it is common to all the
  *           timing units). For each fault input, the application can:
  *             - select the source of the fault input,
  *             - choose between fault input polarity,
  *             - apply (or not) a configurable digital noise filter.
  *
  *           Note:
  *           - When digital filtering is needed, fault input signal sampling clock is either the fHRTIM clock
  *             or a specific prescaled clock (fFLTS) derived from fHRTIM as per configured external fault prescaler.
  *
  *           Each fault input can also be temporarily disabled to blank spurious fault events. It can also be enabled
  *           or disabled unconditionally at HRTIM level and/or for every timing unit.
  *
  *           Some fault input pairs can be ANDed at the timing unit level, meaning the resulting fault signal is active
  *           only if both fault x and fault y are active.
  *
  *           The HRTIM features fault counters (one per fault input). When a fault input counter is enabled, the
  *           concerned fault input is considered only if the number of active edges is greater or equal to a
  *           configurable threshold.
  *           A fault input counter is reset:
  *            - unconditionally on each reset/roll-over event (non-cumulative mode),
  *            - on reset/roll-over event only if no event occurred during last counting period (cumulative mode),
  *            - upon software request.
  *
  *           A protection mechanism can be used to protect the fault configuration against undesirable changes. Once
  *           a fault configuration is locked, it can't be changed any longer until the next HRTIM or system reset.
  *
  *           Note:
  *           When a fault input is active the outputs of the timing units are forced to a predefined safe state which
  *           is configured by the output configuration function.
  *           By default, the HRTIM system fault input is connected to system fault sources coming from:
  *             - the clock security system (CSS),
  *             - the SRAM ECC double error detection,
  *             - the core lockup signal,
  *             - the PVD detector,
  *             - the DCACHE ECC double error detection (PVD),
  *             - the flash memory ECC double error detection.
  *          Additionally:
  *            - The HRTIM1 system fault input can also be connected to the HSP break output 0 signal.
  *            - The HRTIM2 system fault input can also be connected to the HSP break output 2 signal.
  * @{
  */

hal_status_t HAL_HRTIM_FLT_SetPrescaler(const hal_hrtim_handle_t *hhrtim,
                                        hal_hrtim_flt_prescaler_t prescaler);
hal_hrtim_flt_prescaler_t HAL_HRTIM_FLT_GetPrescaler(const hal_hrtim_handle_t *hhrtim);

hal_status_t HAL_HRTIM_FLT_SetSystemFaultInputSource(const hal_hrtim_handle_t *hhrtim,
                                                     hal_hrtim_sysflt_src_t sysflt_source);

hal_hrtim_sysflt_src_t HAL_HRTIM_FLT_GetSystemFaultInputSource(const hal_hrtim_handle_t *hhrtim);

hal_status_t HAL_HRTIM_FLT_SetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t fault,
                                     const hal_hrtim_flt_config_t *p_config);
hal_status_t HAL_HRTIM_FLT_GetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t fault,
                                     hal_hrtim_flt_config_t *p_config);

hal_status_t HAL_HRTIM_FLT_SetBlanking(const hal_hrtim_handle_t *hhrtim,
                                       uint32_t fault,
                                       hal_hrtim_flt_blk_t blanking);
hal_hrtim_flt_blk_t HAL_HRTIM_FLT_GetBlanking(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t fault);

hal_status_t HAL_HRTIM_FLT_EnableBlanking(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t fault);
hal_status_t HAL_HRTIM_FLT_DisableBlanking(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t fault);
hal_hrtim_flt_blk_status_t HAL_HRTIM_FLT_IsEnabledBlanking(const hal_hrtim_handle_t *hhrtim,
                                                           uint32_t fault);

hal_status_t HAL_HRTIM_FLT_Enable(const hal_hrtim_handle_t *hhrtim,
                                  uint32_t fault);
hal_status_t HAL_HRTIM_FLT_Disable(const hal_hrtim_handle_t *hhrtim,
                                   uint32_t fault);
hal_hrtim_flt_status_t HAL_HRTIM_FLT_IsEnabled(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t fault);

hal_status_t HAL_HRTIM_FLT_Lock(const hal_hrtim_handle_t *hhrtim,
                                uint32_t fault);

hal_status_t HAL_HRTIM_FLT_SetCounter(const hal_hrtim_handle_t *hhrtim,
                                      uint32_t fault,
                                      const hal_hrtim_flt_counter_config_t *p_config);
hal_status_t HAL_HRTIM_FLT_GetCounter(const hal_hrtim_handle_t *hhrtim,
                                      uint32_t fault,
                                      hal_hrtim_flt_counter_config_t *p_config);

hal_status_t HAL_HRTIM_FLT_SetCounterThreshold(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t fault,
                                               uint8_t threshold);

uint8_t HAL_HRTIM_FLT_GetCounterThreshold(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t fault);

hal_status_t HAL_HRTIM_FLT_ResetCounter(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t fault);

hal_status_t HAL_HRTIM_TIM_EnableFault(const hal_hrtim_handle_t *hhrtim,
                                       uint32_t timer,
                                       uint32_t faults);
hal_status_t HAL_HRTIM_TIM_DisableFault(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        uint32_t faults);
hal_hrtim_flt_status_t HAL_HRTIM_TIM_IsEnabledFault(const hal_hrtim_handle_t *hhrtim,
                                                    uint32_t timer,
                                                    uint32_t fault);

hal_status_t HAL_HRTIM_TIM_LockFault(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer);

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group9 HRTIM Burst Mode controller management functions
  *
  *           The Burst mode configuration consists in defining:
  *             - the burst mode controller operating mode (one-shot or continuous),
  *             - the source of the burst mode counter (either within or outside the HRTIM),
  *             - the idle period (number of counting periods where outputs are in Idle state),
  *             - the burst period (sum of idle and run periods Run state),
  *             - the event(s) triggering the burst mode operation.
  *
  *           Notes :
  *             - the burst repetition rate corresponds to the sum of the idle and run periods.
  *             - Trigger events can be combined to have multiple concurrent triggers.
  *             - When the burst mode counter is clocked by the main HRTIM clock (fHRTIM), it is possible to
  *               configure a prescaler to divide the burst mode counter clock frequency.
  *             - The registers configuring the burst mode period and idle period the can be
  *               preloaded. In that case transfer from preload to active registers happens when the burst mode
  *               controller is enabled or at the end of the burst mode period.
  *
  *           During the burst idle period, the counters of the timing units (HAL_HRTIM_TIMx, with x = A to F) and
  *           the master timer (HAL_HRTIM_MASTER) can be either maintained or stopped and reset.
  *
  *           Each HRTIM output (HAL_HRTIM_CHxy, x = A to F, y = 1 to 2) can be individually configured for the burst
  *           mode operation. By default, when an HRTIM output is under the burst mode controller control, it takes
  *           its idle level immediately after the burst mode is triggered. However, it is possible to force the output
  *           to an inactive state during a programmable deadtime before the output takes its idle state (burst mode
  *           delayed entry).
  *
  *           Notes :
  *             - When burst mode entry is delayed for HAL_HRTIM_CHx1y deadtime rising value is applied.
  *             - When burst mode entry is delayed for HAL_HRTIM_CHx2y deadtime falling value is applied.
  *
  *           When the burst mode is enabled, it is ready to receive the start trigger. The burst mode operation starts
  *           upon detection of an active trigger event.
  *
  *           Note :
  *             - The burst mode operation can also be started by software.
  *
  *           When the burst mode controller operates in continuous mode, the burst mode exit can be forced
  *           by software. When the burst mode controller operates in one-shot mode, the burst mode ends automatically
  *           at the end of the idle period.
  *
  *           The operating state of the burst mode (normal operation vs. burst operation on-going) can be recovered at
  *           any moment.
  *
  * @{
  */

hal_status_t HAL_HRTIM_SetConfigBurstMode(const hal_hrtim_handle_t *hhrtim,
                                          const hal_hrtim_burst_mode_config_t *p_config);
hal_status_t HAL_HRTIM_GetConfigBurstMode(const hal_hrtim_handle_t *hhrtim,
                                          hal_hrtim_burst_mode_config_t *p_config);

hal_status_t HAL_HRTIM_SetBurstModePeriod(const hal_hrtim_handle_t *hhrtim,
                                          uint16_t period);
uint16_t HAL_HRTIM_GetBurstModePeriod(const hal_hrtim_handle_t *hhrtim);
hal_status_t HAL_HRTIM_SetBurstModeIdlePeriods(hal_hrtim_handle_t *hhrtim,
                                               uint16_t idle_periods);
uint16_t HAL_HRTIM_GetBurstModeIdlePeriods(const hal_hrtim_handle_t *hhrtim);

hal_status_t HAL_HRTIM_TIM_SetBurstMode(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        hal_hrtim_timer_burst_mode_t timer_burst_mode);
hal_hrtim_timer_burst_mode_t HAL_HRTIM_TIM_GetBurstMode(const hal_hrtim_handle_t *hhrtim,
                                                        uint32_t timer);

hal_status_t HAL_HRTIM_OUT_SetBurstMode(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t output,
                                        hal_hrtim_output_burst_mode_t output_burst_mode);
hal_hrtim_output_burst_mode_t HAL_HRTIM_OUT_GetBurstMode(const hal_hrtim_handle_t *hhrtim,
                                                         uint32_t output);

hal_status_t HAL_HRTIM_EnableBurstModePreload(const hal_hrtim_handle_t *hhrtim);
hal_status_t HAL_HRTIM_DisableBurstModePreload(const hal_hrtim_handle_t *hhrtim);
hal_hrtim_burst_mode_preload_status_t HAL_HRTIM_IsEnabledBurstModePreload(const hal_hrtim_handle_t *hhrtim);

hal_status_t HAL_HRTIM_EnableBurstMode(const hal_hrtim_handle_t *hhrtim);
hal_status_t HAL_HRTIM_DisableBurstMode(const hal_hrtim_handle_t *hhrtim);
hal_hrtim_burst_mode_status_t HAL_HRTIM_IsEnabledBurstMode(const hal_hrtim_handle_t *hhrtim);

hal_status_t HAL_HRTIM_StartBurstMode(const hal_hrtim_handle_t *hhrtim);
hal_status_t HAL_HRTIM_StopBurstMode(const hal_hrtim_handle_t *hhrtim);

hal_hrtim_burst_mode_operating_status_t HAL_HRTIM_GetBurstModeOperatingStatus(const hal_hrtim_handle_t *hhrtim);

/**
  * @}
  */

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/** @defgroup HRTIM_Exported_Functions_Group10 HRTIM DMA Burst transfer functions
  *
  *           A DMA burst transfer allows to have multiple HRTIM registers updated with a single DMA request.
  *           The registers that can be written by the DMA during a DMA Burst operation are:
  *             - Master timer registers,
  *             - Timer A to timer F registers.
  *
  *           Note:
  *             - Only write accessible registers can be addressed by the DMA burst.
  *
  *           The way the registers of a timer are updated relatively to the DMA burst operation when the preload
  *           is enabled can be individually configured. Hence, the three following options are proposed:
  *             - the timer's registers are updated independently from the DMA burst transfer completion,
  *             - the timer's registers are updated when the DMA burst transfer is completed,
  *             - the timer's registers are updated on timer roll-over event following the DMA burst transfer
  *               completion.
  *
  *           The source of the DMA burst transfer must be selected among the available timers (HAL_HRTIM_MASTER
  *           or HAL_HRTIM_TIMx, with x = A to F), i.e. any DMA request generated by the timer selected as the DMA burst
  *           source will trigger the DMA burst operation.
  *
  *           Note:
  *             - When DMA burst operation is completed it is automatically restarted when another DMA request is
  *               generated by the timer selected as the DMA burst source.
  * @{
  */

hal_status_t HAL_HRTIM_SetConfigDMABurst(const hal_hrtim_handle_t *hhrtim,
                                         const hal_hrtim_dmaburst_config_t *p_config);

hal_status_t HAL_HRTIM_StartDMABurst(hal_hrtim_handle_t *hhrtim,
                                     hal_hrtim_dma_source_t dma_source,
                                     const uint8_t *p_data,
                                     uint32_t size_byte);

/**
  * @}
  */
#endif /* USE_HAL_HRTIM_DMA */

/**  @defgroup HRTIM_Exported_Functions_Group11 HRTIM Timer's time base configuration functions
  *
  *            Needed HRTIM timers (HAL_HRTIM_MASTER or HAL_HRTIM_TIMx, with x = A to F), must be individually
  *            configured prior being started.
  *            Configuring a HRTIM timer's consists in defining:
  *              - its clock prescaler ratio,
  *              - its counter period,
  *              - its repetition counter value,
  *              - its operating mode (continuous our single-shot),
  *              - its counting mode (up or up-down),
  *              - the timer's interrupt sources to enable (several interrupt sources can be combined),
  *              - the timer's DMA requests to enable (several DMA requests can be combined).
  *              - When at least one DMA request is enabled:
  *                 . the source address of the DMA transfer,
  *                 . the destination address of the DMA transfer,
  *                 . the size of the DMA transfer (number of bytes).
  *
  *            Notes:
  *              - The counting mode isn't significant for master timer.
  *              - Interrupt sources and DMA requests aren't the same for the master timer and the timing units
  *                (Timers A to F).
  *
  *            Whenever needed the timer's counter value can be set or retrieved by sowftare.
  *
  *            When the timing unit operates in up-down mode, it is possible to configure when the roll-over event is
  *            generated:
  *              - Roll over event is generated when the counter is equal to 0 (valley mode)
  *              - Roll over event is generated when the counter reaches the period value  (crests mode)
  *              - Roll over event is generated when both conditions are met (either 0 or period value)
  *            The roll over event is used for multiple purposes in the HRTIM: and it can be programmed individually
  *            depending on its destination (see below):
  *              - General purpose:
  *                . To trigger the register content update (transfer from preload to active).
  *                . To trigger an IRQ or a DMA request.
  *                . To decrease the repetition counter.
  *              - Set/Reset crossbar:
  *                . To set/reset the outputs (period event).
  *              - Burst mode controller:
  *                . To serve as a burst mode clock source or a burst start trigger.
  *              - Fault and external event counters:
  *                . To reset fault and external event counters.
  *              - ADC trigger:
  *                . To generate an ADC trigger.
  *
  *            Note:
  *              - For ADC trigger, roll over mode configuration applies to any event that can trigger the ADC,
  *                i.e. reset, roll-over (period) and compare events. Thus event is either generated:
  *                . both during up and down-counting phases,
  *                . during up-counting phases,
  *                . during down-counting phases.
  *
  * @{
  */

hal_status_t HAL_HRTIM_TIM_SetConfig(hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer,
                                     const hal_hrtim_timer_config_t *p_config);
hal_status_t HAL_HRTIM_TIM_GetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer,
                                     hal_hrtim_timer_config_t *p_config);

hal_status_t HAL_HRTIM_TIM_SetPrescaler(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        hal_hrtim_timer_prescaler_t prescaler);
hal_hrtim_timer_prescaler_t HAL_HRTIM_TIM_GetPrescaler(const hal_hrtim_handle_t *hhrtim,
                                                       uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetPeriod(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer,
                                     uint16_t period);
uint16_t HAL_HRTIM_TIM_GetPeriod(const hal_hrtim_handle_t *hhrtim,
                                 uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetRepetition(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer,
                                         uint16_t repetition);

uint16_t HAL_HRTIM_TIM_GetRepetition(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetOperatingMode(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            hal_hrtim_timer_operating_mode_t operating_mode);
hal_hrtim_timer_operating_mode_t HAL_HRTIM_TIM_GetOperatingMode(const hal_hrtim_handle_t *hhrtim,
                                                                uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetCountingMode(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_timer_counting_mode_t counting_mode);
hal_hrtim_timer_counting_mode_t HAL_HRTIM_TIM_GetCountingMode(const hal_hrtim_handle_t *hhrtim,
                                                              uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetCounter(const hal_hrtim_handle_t *hhrtim,
                                      uint32_t timer,
                                      uint16_t counter_value);
uint16_t HAL_HRTIM_TIM_GetCounter(const hal_hrtim_handle_t *hhrtim,
                                  uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetRollOverMode(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_roll_over_destination_t destination,
                                           hal_hrtim_roll_over_mode_t mode);
hal_hrtim_roll_over_mode_t HAL_HRTIM_TIM_GetRollOverMode(const hal_hrtim_handle_t *hhrtim,
                                                         uint32_t timer,
                                                         hal_hrtim_roll_over_destination_t destination);

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group12 HRTIM timers' Registers preload and update management functions
  *
  *            Register preload and update management
  *
  *            Most of HRTIM registers are buffered and can be preloaded if needed. The register preload mode
  *            can be enabled or disabled for the master timer and each timing unit. When the preload mode is disabled
  *           (default) registers aren't preloaded and any write operation directly updates the active registers.
  *            When the preload mode is enabled, accessed registers are shadow registers. Their content is transferred
  *            into the active register after an update request.
  *
  *            The update event sources can be selected among the following sources:
  *              - for the master timer (HAL_HRTIM_MASTER):
  *                . the counter repetition period.
  *              - for timing units (HAL_HRTIM_TIMx, with x = A to F):
  *                . the counter repetition period,
  *                . the counter reset,
  *                . the master timer update,
  *                . the adjacent timers update (e.g master timer or timers B to F for timer A).
  *
  *            The update request trigger can be configured separately for each timer.
  *            The master timer's registers update can be triggered:
  *               - by the update event (see above),
  *               - when the DMA burst transfer is completed,
  *               - by the update event following the DMA burst transfer completion.
  *            The timing unit's registers update can be triggered:
  *               - by the update event (see above),
  *               - when the DMA burst transfer is completed,
  *               - by the update event following the DMA burst transfer completion,
  *               - by a pulse on one of the update enable inputs (on-chip interconnect),
  *               - by the update event following a pulse on one of the update enable inputs.
  *
  *            Notes:
  *              - The update request can also be triggered by software.
  *              - Transfer from preload to active registers can be temporarily disabled (whatever the selected update
  *                trigger).
  *
  *            The update coming from adjacent timers or from a software update can either be considered
               immediately or re-synchronized with the timers reset/roll-over event.
  * @{
  */

hal_status_t HAL_HRTIM_TIM_EnablePreload(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer);
hal_status_t HAL_HRTIM_TIM_DisablePreload(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer);
hal_hrtim_preload_status_t HAL_HRTIM_TIM_IsEnabledPreload(const hal_hrtim_handle_t *hhrtim,
                                                          uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetUpdateSource(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           uint32_t update_source);
uint32_t HAL_HRTIM_TIM_GetUpdateSource(const hal_hrtim_handle_t *hhrtim,
                                       uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetUpdateGating(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_update_gating_t update_gating);
hal_hrtim_update_gating_t HAL_HRTIM_TIM_GetUpdateGating(const hal_hrtim_handle_t *hhrtim,
                                                        uint32_t timer);

hal_status_t HAL_HRTIM_EnableUpdate(const hal_hrtim_handle_t *hhrtim,
                                    uint32_t timers);
hal_status_t HAL_HRTIM_DisableUpdate(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t timers);
hal_hrtim_update_status_t HAL_HRTIM_IsEnabledUpdate(const hal_hrtim_handle_t *hhrtim,
                                                    uint32_t timer);

hal_status_t HAL_HRTIM_Update(const hal_hrtim_handle_t *hhrtim,
                              uint32_t timers);

hal_status_t HAL_HRTIM_TIM_EnableUpdateResync(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timer);
hal_status_t HAL_HRTIM_TIM_DisableUpdateResync(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t timer);
hal_hrtim_update_resync_status_t HAL_HRTIM_TIM_IsEnabledUpdateResync(const hal_hrtim_handle_t *hhrtim,
                                                                     uint32_t timer);

hal_status_t HAL_HRTIM_EnableRemoteUpdate(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timers);
hal_status_t HAL_HRTIM_DisableRemoteUpdate(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timers);
hal_hrtim_remote_update_status_t HAL_HRTIM_IsEnabledRemoteUpdate(const hal_hrtim_handle_t *hhrtim,
                                                                 uint32_t timer);

hal_status_t HAL_HRTIM_EnableRemoteUpdateRequest(const hal_hrtim_handle_t *hhrtim,
                                                 uint32_t timers);
hal_status_t HAL_HRTIM_DisableRemoteUpdateRequest(const hal_hrtim_handle_t *hhrtim,
                                                  uint32_t timers);
hal_hrtim_remote_update_request_status_t HAL_HRTIM_IsEnabledRemoteUpdateRequest(const hal_hrtim_handle_t *hhrtim,
                                                                                uint32_t timer);

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group13 HRTIM Timer's control functions
  *
  *            Once configured, the timers (HAL_HRTIM_MASTER or HAL_HRTIM_TIMx, with x = A to F) can be started either
  *            individually or together (synchronous start).
  *
  *            Three operating modes are proposed to start the timers:
  *              - Polling mode: the counters of the concerned timers are enabled.
  *              - Interrupt mode: for each concerned timer, the interrupt source(s) specified during the timer's
  *                configuration are enabled. Then the counters of the concerned timers are enabled. When a timer
  *                interrupt is generated, the associated callback function is invoked from within the timer's interrupt
  *                service routine.
  *               - DMA mode: for each concerned timer, the DMA request(s) specified during the timer's configuration
  *                 are enabled and the corresponding DMA channel is enabled. Then the counters of the concerned timers
  *                 are enabled. The DMA transfer is triggered when the DMA request is sent by the timer. When the
  *                 DMA transfer completes or in case of DMA error, the associated callback function is invoked from
  *                 within the DMA channel interrupt service routine.
  *
  *            Reversely, three operating modes are proposed to stop the timers:
  *              - Polling mode: the counters of the concerned timers are disabled.
  *              - Interrupt mode: the counters of the concerned timers are disabled. Then for each concerned timer,
  *                the interrupt source(s) specified during the timer's configuration are disabled.
  *              - DMA mode: first DMA channel(s) are disabled, then for each concerned timer, the DMA request(s)
  *                specified during the timer's configuration are disabled. Finally, the counters of the concerned
  *                timers are disabled.
  *
  *            Note:
  *              - When the timer's counter operates in single-shot mode, the counting is started by a reset event.
  *                Still the start function must be called.
  * @{
  */

hal_status_t HAL_HRTIM_TIM_Start(hal_hrtim_handle_t *hhrtim,
                                 uint32_t timers);

hal_status_t HAL_HRTIM_TIM_Stop(hal_hrtim_handle_t *hhrtim,
                                uint32_t timers);

hal_status_t HAL_HRTIM_TIM_Start_IT(hal_hrtim_handle_t *hhrtim,
                                    uint32_t timers);

hal_status_t HAL_HRTIM_TIM_Stop_IT(hal_hrtim_handle_t *hhrtim,
                                   uint32_t timers);

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
hal_status_t HAL_HRTIM_TIM_Start_DMA(hal_hrtim_handle_t *hhrtim,
                                     uint32_t timers);

hal_status_t HAL_HRTIM_TIM_Stop_DMA(hal_hrtim_handle_t *hhrtim,
                                    uint32_t timers);
#endif /* USE_HAL_HRTIM_DMA */

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group14 HRTIM timer's counter reset configuration and control functions
  *
  *            The counter of a timing unit (HAL_HRTIM_TIMx, with x = A to F) can be reset before  before reaching
  *            the period value (variable frequency operation).
  *
  *            The reset of a timing unit counter can be triggered by up to 30 events that can be selected
  *            simultaneously among the following sources:
  *              - The timing unit: compare 2, compare 4 and update (3 events)
  *              - The master timer: period and compare 1..4 (5 events)
  *              - Any external events (16 events)
  *              - Other timing units (e.g. timer B..F for timer A): compare 1, 2 and 4 (14 events)
  *
  *            At any moment, the counter also be reset by software.
  * @{
  */

hal_status_t HAL_HRTIM_TIM_SetResetSource(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer,
                                          uint32_t reset_sources);
uint32_t HAL_HRTIM_TIM_GetResetSource(const hal_hrtim_handle_t *hhrtim,
                                      uint32_t timer);

hal_status_t HAL_HRTIM_TIM_Reset(const hal_hrtim_handle_t *hhrtim,
                                 uint32_t timers);

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group15 HRTIM outputs configuration functions
  *
  *           The HRTIM has 12 outputs (HAL_HRTIM_CHxy, x= A to F and y = 1 or 2).
  *
  *            Configuring an output consists in defining:
  *              - the event(s) setting the output (transition to the active state),
  *              - the event(s) resetting the output (transition to the inactive state),
  *              - the polarity of the output (active, output level can be high or low),
  *              - the IDLE state of the output (active or inactive).
  *              - the FAULT state of the output (no action, active, inactive or High-Z).
  *
  *            Notes:
  *               - IDLE state is entered when the output is disabled or when it is under the burst mode controller
  *                 (during the idle period).
  *               - FAULT state is entered upon detection of an active fault by the timing unit controlling the output.
  *
  *            The outputs set/reset events can be triggered by up to 31 events that can be selected among the following
  *            sources:
  *              - The timing unit: resynchronization, period, compare 1..4, registers update (7 events)
  *              - The master timer: period and compare 1..4 (5 events)
  *              - Any external events (16 events)
  *              - Other timing units (e.g. timer B..F for timer A): compare events 1..4 (9 events)
  *
  *            HRTIM outputs can be started individually or together. When an output is started, it is immediately
  *             connected to the crossbar output. Reversely, HRTIM outputs can be stopped individually or together.
  *
  *            Notes:
  *              - Any output can be set (forced to its active state) or reset (forced to its inactive state) by
  *                software.
  *              - Any output set/reset event (except software requests) are ignored as long as the output is disabled.
  *
  *            Each HRTIM output has three operating states:
  *              - IDLE: entered when the output is stopped.
  *              - RUN: entered when the output is started.
  *              - FAULT: entered upon fault detection.
  *
  *            When and output is in the IDLE state it takes is INACTIVE level. When an output is in the RUN state
  *            it can take inactive or active level as per crossbar configuration. When an output is in fault state
  *            it can take its inactive or inactive level or left opened (High-Z) as per output fault state
  *            configuration.
  *
  *            The output level before the output stage is called the raw output level. It can be retrieved at any
  *            moment, for instance to check the current output level (ACTIVE or INACTIVE) before re-enabling the output
  *            after a delayed protection.
  *
  *            The outputs of a timing unit can be swapped meaning that the output 1 signal is connected to the output 2
  *            pin and the output 2 signal is connected to output 1 pin. Swap mode can be enabled or disabled
  *            simultaneously for several timing units.
  * @{
  */

hal_status_t HAL_HRTIM_OUT_SetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t output,
                                     const hal_hrtim_output_config_t *p_config);
hal_status_t HAL_HRTIM_OUT_GetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t output,
                                     hal_hrtim_output_config_t *p_config);

hal_status_t HAL_HRTIM_OUT_Enable(const hal_hrtim_handle_t *hhrtim,
                                  uint32_t outputs);

hal_status_t HAL_HRTIM_OUT_Disable(const hal_hrtim_handle_t *hhrtim,
                                   uint32_t outputs);

hal_status_t HAL_HRTIM_OUT_Set(const hal_hrtim_handle_t *hhrtim,
                               uint32_t output);

hal_status_t HAL_HRTIM_OUT_Reset(const hal_hrtim_handle_t *hhrtim,
                                 uint32_t output);

hal_hrtim_output_level_t HAL_HRTIM_OUT_GetRawLevel(const hal_hrtim_handle_t *hhrtim,
                                                   uint32_t output);

hal_status_t HAL_HRTIM_TIM_EnableSwapMode(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timers);
hal_status_t HAL_HRTIM_TIM_DisableSwapMode(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timers);
hal_hrtim_swap_mode_status_t HAL_HRTIM_TIM_IsEnabledSwapMode(const hal_hrtim_handle_t *hhrtim,
                                                             uint32_t timer);

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group16 HRTIM compare unit configuration functions
  *
  *            HRTIM timers (HAL_HRTIM_MASTER or HAL_HRTIM_TIMx, with x = A to F) embed 4 compare units
  *            (HAL_HRTIM_COMPARE_UNIT_x, with x = 1 to 4). A compare event is generated when the counter exactly
  *            matches the compare value configured for the compare unit.
  *
  *            Compare events can be used to:
  *              - Reset the counter of a timing unit,
  *              - Set or Reset an HRTIM output,
  *              - Trigger a capture,
  *              - Trigger the burst mode controller.
  *
  *            Notes:
  *              - When the timer operates in interleaved mode HAL_HRTIM_COMPARE_UNIT_1, HAL_HRTIM_COMPARE_UNIT_2 and
  *                HAL_HRTIM_COMPARE_UNIT_3 compare values are automatically set by the hardware as per selected
  *                inteleaved mode (see below).
  *                | Mode               | CMP1 value | CMP2 value | CMP3 value |
  *                |--------------------|------------|------------|------------|
  *                | Dual interleaved   | Period/2   |      -     |      -     |
  *                | Triple interleaved | Period/3   | 2*Period/3 |      -     |
  *                | Quad interleaved   | Period/4   | Period /2  | 3*Period/4 |
  *
  *            Compare units 1 and 3 of the timing units (HAL_HRTIM_TIMx, with x = A to F) support the 'Greater Than'
  *            (GT) compare mode. This mode is intended to have the new compare value taken into account as soon as
  *            possible after a new value write, without waiting for the preload to active register transfer.
  *
  *            Compare unit 2 of the timing units (HAL_HRTIM_TIMx, with x = A to F) supports the Triggered Half Mode.
  *            When triggered half mode is enabled, when an capture 1 event occurs, CMP2 value is set with the captured
  *            value divided by 2.
  *
  *            Note:
  *              - A timeout event can be generated if no capture is triggered within the counting period.
  *
  *            Compare units 2 and 4 of the timing units (HAL_HRTIM_TIMx, with x = A to F) support the Auto Delayed
  *            Mode. When auto delayed mode is enabled, the compare value is summed with the captured counter value.
  *            Compare unit 2 is associated with capture unit 1 while compare unit 4 is associated to capture unit 2.
  *
  *            Notes:
  *              - When the auto delayed mode is enabled, the compare event is inhibited until the capture is triggered.
  *              - A safety mechanism et available to force the capture when the counter equals the timeout threshold
  *                defined in the compare 1 or the compare 3 value.
  *
  * @{
  */

hal_status_t HAL_HRTIM_TIM_SetCompareValue(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_compare_unit_t compare_unit,
                                           uint16_t compare_value);
uint16_t HAL_HRTIM_TIM_GetCompareValue(const hal_hrtim_handle_t *hhrtim,
                                       uint32_t timer,
                                       hal_hrtim_compare_unit_t compare_unit);

hal_status_t HAL_HRTIM_TIM_SetInterleavedMode(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timer,
                                              hal_hrtim_interleaved_mode_t mode);
hal_hrtim_interleaved_mode_t HAL_HRTIM_TIM_GetInterleavedMode(const hal_hrtim_handle_t *hhrtim,
                                                              uint32_t timer);

hal_status_t HAL_HRTIM_TIM_EnableGTCompare(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_compare_unit_t compare_unit);
hal_status_t HAL_HRTIM_TIM_DisableGTCompare(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            hal_hrtim_compare_unit_t compare_unit);
hal_hrtim_greater_than_compare_status_t HAL_HRTIM_TIM_IsEnabledGTCompare(const hal_hrtim_handle_t *hhrtim,
                                                                         uint32_t timer,
                                                                         hal_hrtim_compare_unit_t compare_unit);

hal_status_t HAL_HRTIM_TIM_SetTriggeredHalfMode(const hal_hrtim_handle_t *hhrtim,
                                                uint32_t timer,
                                                hal_hrtim_trig_half_mode_t mode);
hal_hrtim_trig_half_mode_t HAL_HRTIM_TIM_GetTriggeredHalfMode(const hal_hrtim_handle_t *hhrtim,
                                                              uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetAutoDelayedMode(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timer,
                                              hal_hrtim_compare_unit_t compare_unit,
                                              const hal_hrtim_auto_delayed_config_t *p_config);
hal_status_t HAL_HRTIM_TIM_GetAutoDelayedMode(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timer,
                                              hal_hrtim_compare_unit_t compare_unit,
                                              hal_hrtim_auto_delayed_config_t *p_config);

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group17 HRTIM capture unit configuration functions
  *
  *            HRTIM timing units (HAL_HRTIM_TIMx, with x = A to F) embed 2 capture units
  *           (HAL_HRTIM_CAPTURE_UNIT_x, with x = 1 to 2).
  *
  *            The capture can be triggered by up to 31 events that can be selected among the following sources:
  *              - The timing unit: registers update (1 event)
  *              - Any external events (16 events)
  *              - Other timing units (e.g. timer B..F for timer A): output 1 set/reset events, compare events 1 and 2
  *                (20 events)
  *
  *            A capture can also be triggered by software.
  *
  *            When a capture is triggered both the counter's value and the counter's direction (up or down) are
  *            latched and can be retrieved either all together or separately.
  *
  * @{
  */

hal_status_t HAL_HRTIM_TIM_SetCaptureTrigger(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer,
                                             hal_hrtim_capture_unit_t capture_unit,
                                             uint64_t triggers);
uint64_t HAL_HRTIM_TIM_GetCaptureTrigger(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer,
                                         hal_hrtim_capture_unit_t capture_unit);

hal_status_t HAL_HRTIM_TIM_Capture(const hal_hrtim_handle_t *hhrtim,
                                   uint32_t timer,
                                   hal_hrtim_capture_unit_t capture_unit);

hal_status_t HAL_HRTIM_TIM_GetCapture(const hal_hrtim_handle_t *hhrtim,
                                      uint32_t timer,
                                      hal_hrtim_capture_unit_t capture_unit,
                                      hal_hrtim_capture_t *capture);

uint16_t HAL_HRTIM_TIM_GetCapturedValue(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        hal_hrtim_capture_unit_t capture_unit);

hal_hrtim_capture_direction_t HAL_HRTIM_TIM_GetCapturedDirection(const hal_hrtim_handle_t *hhrtim,
                                                                 uint32_t timer,
                                                                 hal_hrtim_capture_unit_t capture_unit);

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group18 HRTIM fault protection related functions
  *
  *            The HRTIM offers multiple fault protection options allowing to shut down
  *            the PWM outputs and asynchronously forces a user-defined safety state.
  *
  *            Delayed protection is a mechanism allowing to shut down the PWM outputs in a delayed manner
  *            in response to specific external events.
  *            Several modes are proposed:
  *              - Delayed idle: the selected external event causes the output(s) to enter in idle mode at the end of
  *                the active pulse.
  *              - Balanced idle: the pulse width, terminated earlier than programmed, is copied on the alternate
  *                output, then the two outputs are put in idle state, until the normal operation is resumed by
  *                software.
  *
  *           Notes:
  *             - Delayed protection mode can be set for output 1, output 2 or both.
  *             - For timing units A, B and C, delayed protection uses external events F or G while for timing units
  *               D, E and F, delayed protection uses external events H or I.
  *             - Delayed idle mode cannot be exited immediately after having been entered. It is mandatory to make sure
  *               that the outputs are INACTIVE before resuming the run mode (see HAL_HRTIM_OUT_GetRawLevel).
  *             - Balanced idle mode is only available when push-pull mode is enabled.
  *             - When balanced idle mode is enabled, compare unit 4 isn't user accessible.
  *
  *           It is possible to retrieve the level (ACTIVE or INACTIVE) of an output when the delayed idle protection
  *           was triggered.
  *
  *           The balanced Idle mode can be configured to have an automatic resuming of operation after a trigger.
  *           In that case, outputs are automatically re-enabled after a balanced idle event.
  *
  * @{
  */

hal_status_t HAL_HRTIM_TIM_SetConfigDelayedProtection(const hal_hrtim_handle_t *hhrtim,
                                                      uint32_t timer,
                                                      const hal_hrtim_delayed_prot_config_t *p_config);

hal_status_t HAL_HRTIM_TIM_GetConfigDelayedProtection(const hal_hrtim_handle_t *hhrtim,
                                                      uint32_t timer,
                                                      hal_hrtim_delayed_prot_config_t *p_config);

hal_status_t HAL_HRTIM_TIM_EnableDelayedProtection(const hal_hrtim_handle_t *hhrtim,
                                                   uint32_t timer);
hal_status_t HAL_HRTIM_TIM_DisableDelayedProtection(const hal_hrtim_handle_t *hhrtim,
                                                    uint32_t timer);
hal_hrtim_delayed_protection_status_t HAL_HRTIM_TIM_IsEnabledDelayedProtection(const hal_hrtim_handle_t *hhrtim,
                                                                               uint32_t timer);

hal_hrtim_output_level_t HAL_HRTIM_OUT_GetDelayedProtectionLevel(const hal_hrtim_handle_t *hhrtim,
                                                                 uint32_t output);

hal_status_t HAL_HRTIM_TIM_EnableBalancedIdleAutoResume(const hal_hrtim_handle_t *hhrtim,
                                                        uint32_t timer);
hal_status_t HAL_HRTIM_TIM_DisableBalancedIdleAutoResume(const hal_hrtim_handle_t *hhrtim,
                                                         uint32_t timer);
hal_hrtim_balanced_idle_auto_resume_status_t HAL_HRTIM_TIM_IsEnabledBalancedIdleAutoResume(
  const hal_hrtim_handle_t *hhrtim,
  uint32_t timer);

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group19 HRTIM deadtime configuration functions
  *
  *            Three deadtime modes are proposed:
  *              - Deadtime complementary mode: deadtime is inserted between two complementary PWM signals generated
  *                from a single reference waveform.
  *              - Deadtime insertion mode: deadtime is inserted between a couple of two independent waveforms.
  *              - Deadtime insertion and disarm mode: in addition to the deadtime insertion mode Output 2 is disarmed
  *                until the next reset/roll-over event if:
  *                  - one (or multiple) EEV(s) event is selected to reset the output 1,
  *                  - at least one external event is active.
  *
  *            The deadtime value can be individually adjusted for both the rising and falling edges, asymmetrically.
  *            For very specific cases, it is also possible to configure a negative deadtime and have some controlled
  *            outputs overlap.
  *
  *            Note:
  *              - Deadtime values are based on a specific clock prescaled according to a confnigurable deadtime
  *                prescaler.
  *
  *            For functional safety purposes, it is optionally possible to write protect the values or the signs of the
  *            deadtime.
  *
  *            Note:
  *              - Deadtime prescaler value is write protected as soon as on of the deadtime configuration pamater
  *                is locked.
  *
  *            Deadtime insertion is enabled or disabled at timing unit level.
  * @{
  */

hal_status_t HAL_HRTIM_TIM_SetDeadtimeMode(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_deadtime_mode_t deadtime_mode);
hal_hrtim_deadtime_mode_t HAL_HRTIM_TIM_GetDeadtimeMode(const hal_hrtim_handle_t *hhrtim,
                                                        uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetConfigDeadtime(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer,
                                             hal_hrtim_deadtime_t deadtime,
                                             const hal_hrtim_deadtime_config_t *p_config);
hal_status_t HAL_HRTIM_TIM_GetConfigDeadtime(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer,
                                             hal_hrtim_deadtime_t deadtime,
                                             hal_hrtim_deadtime_config_t *p_config);

hal_status_t HAL_HRTIM_TIM_SetDeadtimePrescaler(const hal_hrtim_handle_t *hhrtim,
                                                uint32_t timer,
                                                hal_hrtim_deadtime_prescaler_t prescaler);
hal_hrtim_deadtime_prescaler_t HAL_HRTIM_TIM_GetDeadtimePrescaler(const hal_hrtim_handle_t *hhrtim,
                                                                  uint32_t timer);

hal_status_t HAL_HRTIM_TIM_LockDeadtime(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        hal_hrtim_deadtime_t deadtime,
                                        hal_hrtim_deadtime_lock_t lock);
hal_hrtim_deadtime_lock_status_t HAL_HRTIM_TIM_GetLockDeadtime(const hal_hrtim_handle_t *hhrtim,
                                                               uint32_t timer,
                                                               hal_hrtim_deadtime_t deadtime);

hal_status_t HAL_HRTIM_TIM_EnableDeadtime(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer);
hal_status_t HAL_HRTIM_TIM_DisableDeadtime(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer);
hal_hrtim_deadtime_status_t HAL_HRTIM_TIM_IsEnabledDeadtime(const hal_hrtim_handle_t *hhrtim,
                                                            uint32_t timer);

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group20 HRTIM chopper mode configuration functions
  *
  *            The chopper unit can superimpose a carrier signal on top of the active PWM waveform.
  *            A carrier generator is started by the incoming pulse and added to the incoming signal by means of
  *            an AND gate.
  *
  *            For each timing unit (HAL_HRTIM_TIMx, with x = A to F), the carrier waveform can be configured with
  *            following parameters:
  *              - the modulation frequency,
  *              - the 1st pulse length to adjust the settling time,
  *              - the duty cycle to set the sustain current.
  *
  *           Chopper mode can be enabled or disabled separately for each HRTIM output (HAL_HRTIM_CHxy, x = A to F,
  *           y = 1 to 2).
  * @{
  */

hal_status_t HAL_HRTIM_TIM_SetConfigChopper(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            const hal_hrtim_chopper_config_t *p_config);
hal_status_t HAL_HRTIM_TIM_GetConfigChopper(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            hal_hrtim_chopper_config_t *p_config);

hal_status_t HAL_HRTIM_TIM_EnableChopper(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer,
                                         hal_hrtim_tim_outputs_t outputs);
hal_status_t HAL_HRTIM_TIM_DisableChopper(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer,
                                          hal_hrtim_tim_outputs_t outputs);
hal_hrtim_chopper_status_t HAL_HRTIM_TIM_IsEnabledChopper(const hal_hrtim_handle_t *hhrtim,
                                                          uint32_t timer,
                                                          hal_hrtim_tim_outputs_t outputs);

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group21 HRTIM push-pull mode configuration functions
  *
  *            When a timing unit operates in push-pull mode, its outputs are alternatively enabled and put in idle
  *            state to maintain the balance between the two PWM outputs. Both signals can be built using a single
  *            compare value to set the PWM duty cycle.
  *
  *            Notes:
  *              - It is possible to unbalance the signals and generate asymmetrical waveforms. For instance a PWM using
  *                Compare 1 for Output 1 and a PWM using Compare 2 for Output 2.
  *              - Push-pull mode must be enabled when the delayed idle protection is required (balanced idle.
  *
  *            It is possible to retrieve on which output the signal is currently active when the push-pull mode is
  *            enabled. It is also possible to retrieve which output was active when the delayed protection was
  *            triggered when the balanced idle mode is enabled.
  *
  *            In push-pull mode, it is possible to have the ADC triggered only while output1 (resp. output2) is active.
  * @{
  */

hal_status_t HAL_HRTIM_TIM_EnablePushPull(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer);
hal_status_t HAL_HRTIM_TIM_DisablePushPull(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer);
hal_hrtim_pushpull_status_t HAL_HRTIM_TIM_IsEnabledPushPull(const hal_hrtim_handle_t *hhrtim,
                                                            uint32_t timer);

hal_hrtim_pushpull_current_output_t HAL_HRTIM_TIM_GetPushPullCurrentStatus(const hal_hrtim_handle_t *hhrtim,
                                                                           uint32_t timer);

hal_hrtim_pushpull_idle_output_t HAL_HRTIM_TIM_GetPushPullIdleStatus(const hal_hrtim_handle_t *hhrtim,
                                                                     uint32_t timer);

hal_status_t HAL_HRTIM_TIM_SetPushPullAdcTrigger(const hal_hrtim_handle_t *hhrtim,
                                                 uint32_t timer,
                                                 hal_hrtim_pushpull_adc_trigger_t pushpull_adc_trigger);
hal_hrtim_pushpull_adc_trigger_t HAL_HRTIM_TIM_GetPushPullAdcTrigger(const hal_hrtim_handle_t *hhrtim,
                                                                     uint32_t timer);

/**
  * @}
  */

/**  @defgroup HRTIM_Exported_Functions_Group24 Crossbar override mode configuration functions
  *
  *            Regular crossbar configuration can be temporarily overridden to force the outputs to their active or
  *            inactive level.
  *
  *            The crossbar override mode can be configured for each timing unit. it consists of specifying the sources
  *            triggering the crossbar override and the crossbar override mode (cycle-by-cycle or latched).
  *
  *            The crossbar override can be triggered by up to 31 events that can be selected among the following
  *            sources:
  *              - Fault inputs (8 events)
  *              - Combined faults (7 events)
  *              - combined external events (10 events)
  *              - External triggers, e.g. PLAY1 outputs (6 events)
  *
  *            Crossbar override can also be triggered by software.
  *
  *            Notes:
  *              - In cycle-by-cycle mode, the regular crossbar operation is resumed automatically at the next
  *                reset/roll-over event, once the triggering conditions have disappeared.
  *              - In latched mode it must be be explicitly rearmed by software.
  *
  *            For each output, one of the following crossbar override force modes can be configured:
  *              - Output is forced to its active or inactive level when crossbar override starts,
  *              - Output is forced to its inactive level after delay when crossbar override starts,
  *              - Output is forced to its active level on external event.
  *
  *            When dual-channel DAC crossbar override is enabled, dual-channel DAC step/reset triggers are generated
  *            under the following conditions:
  *              - Step triggers are generated as per the dual-channel DAC step trigger configuration as long as
  *                the crossbar override is active.
  *              - Reset triggers are generated only in cycle-by-cycle mode upon exiting the the crossbar override mode.
  *
  *            Whenever needed, it is possible to get the actual crossbar override status and the crossbar override
  *            trigger state.
  * @{
  */
hal_status_t HAL_HRTIM_TIM_SetConfigXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            const hal_hrtim_xbar_ovr_config_t *p_config);
hal_status_t HAL_HRTIM_TIM_GetConfigXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            hal_hrtim_xbar_ovr_config_t *p_config);

hal_status_t HAL_HRTIM_OUT_SetXbarOvrForceMode(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t output,
                                               hal_hrtim_xbar_ovr_force_mode_t mode);
hal_hrtim_xbar_ovr_force_mode_t HAL_HRTIM_OUT_GetXbarOvrForceMode(const hal_hrtim_handle_t *hhrtim,
                                                                  uint32_t output);

hal_status_t HAL_HRTIM_OUT_SetXbarOvrForcingEvents(const hal_hrtim_handle_t *hhrtim,
                                                   uint32_t output,
                                                   uint32_t forcing_events);
uint32_t HAL_HRTIM_OUT_GetXbarOvrForcingEvents(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t output);

hal_status_t HAL_HRTIM_TIM_SetXbarOvrDelay(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_xbar_ovr_delay_option_t delay_option,
                                           uint16_t delay_value);
uint16_t HAL_HRTIM_TIM_GetXbarOvrDelay(const hal_hrtim_handle_t *hhrtim,
                                       uint32_t timer,
                                       hal_hrtim_xbar_ovr_delay_option_t delay_option);

hal_status_t HAL_HRTIM_TIM_EnableXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer);
hal_status_t HAL_HRTIM_TIM_DisableXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer);
hal_hrtim_xbar_ovr_status_t HAL_HRTIM_TIM_IsEnabledXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                                           uint32_t timer);

hal_status_t HAL_HRTIM_TIM_EnableDualDACXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                                uint32_t timer);
hal_status_t HAL_HRTIM_TIM_DisableDualDACXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                                 uint32_t timer);
hal_hrtim_dual_channel_dac_xbar_ovr_status_t HAL_HRTIM_TIM_IsEnabledDualDACXbarOvr(
  const hal_hrtim_handle_t *hhrtim,
  uint32_t timer);


hal_hrtim_xbar_ovr_mode_status_t HAL_HRTIM_TIM_GetXbarOvrStatus(const hal_hrtim_handle_t *hhrtim,
                                                                uint32_t timer);
hal_hrtim_xbar_ovr_trigger_status_t HAL_HRTIM_TIM_GetXbarOvrTriggerStatus(const hal_hrtim_handle_t *hhrtim,
                                                                          uint32_t timer);
hal_status_t HAL_HRTIM_TIM_RearmXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer);

hal_status_t HAL_HRTIM_TIM_XbarOvr(const hal_hrtim_handle_t *hhrtim,
                                   uint32_t timer);

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group22 High Resolution Timer IRQ Handler and Callbacks functions
  *
  *            IRQ handlers are the functions called from HRTIM interrupt service routines (ISR) when an HRTIM interrupt
  *            arises. There are as many IRQ handlers as there are HRTIM interrupt vectors. The callback functions are
  *            invoked from within the IRQ handlers based on the interrupt sources.
  *
  *            Note that the DMA-related callback functions (half transfer complete, transfer complete, or transfer
  *            error) are called from the DMA IRQ handler function.
  * @{
  */

/* Interrupt Handler functions   ***********************************************/
void HAL_HRTIM_M_IRQHandler(hal_hrtim_handle_t *hhrtim);
void HAL_HRTIM_TIMA_IRQHandler(hal_hrtim_handle_t *hhrtim);
void HAL_HRTIM_TIMB_IRQHandler(hal_hrtim_handle_t *hhrtim);
void HAL_HRTIM_TIMC_IRQHandler(hal_hrtim_handle_t *hhrtim);
void HAL_HRTIM_TIMD_IRQHandler(hal_hrtim_handle_t *hhrtim);
void HAL_HRTIM_TIME_IRQHandler(hal_hrtim_handle_t *hhrtim);
void HAL_HRTIM_TIMF_IRQHandler(hal_hrtim_handle_t *hhrtim);
void HAL_HRTIM_FLT_IRQHandler(hal_hrtim_handle_t *hhrtim);


/* Declaration for the weak callbacks *******************************************/
#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
void HAL_HRTIM_DMAHalfCpltCallback(hal_hrtim_handle_t *hhrtim,
                                   uint32_t timer);
void HAL_HRTIM_DMACpltCallback(hal_hrtim_handle_t *hhrtim,
                               uint32_t timer);
void HAL_HRTIM_DMAStopCallback(hal_hrtim_handle_t *hhrtim,
                               uint32_t timer);
void HAL_HRTIM_DMAErrorCallback(hal_hrtim_handle_t *hhrtim,
                                uint32_t timer);
#endif /* USE_HAL_HRTIM_DMA */

void HAL_HRTIM_FaultCallback(hal_hrtim_handle_t *hhrtim,
                             uint32_t fault);

void HAL_HRTIM_SystemFaultCallback(hal_hrtim_handle_t *hhrtim);

void HAL_HRTIM_BurstModePeriodCallback(hal_hrtim_handle_t *hhrtim);

void HAL_HRTIM_SynchroCallback(hal_hrtim_handle_t *hhrtim);

void HAL_HRTIM_UpdateCallback(hal_hrtim_handle_t *hhrtim,
                              uint32_t timer);

void HAL_HRTIM_RepetitionCallback(hal_hrtim_handle_t *hhrtim,
                                  uint32_t timer);

void HAL_HRTIM_ResetCallback(hal_hrtim_handle_t *hhrtim,
                             uint32_t timer);

void HAL_HRTIM_DelayedProtectionCallback(hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer);

void HAL_HRTIM_CompareMatchCallback(hal_hrtim_handle_t *hhrtim,
                                    uint32_t timer,
                                    hal_hrtim_compare_unit_t compare_unit);

void HAL_HRTIM_CaptureCallback(hal_hrtim_handle_t *hhrtim,
                               uint32_t timer,
                               hal_hrtim_capture_unit_t capture_unit);

void HAL_HRTIM_OutputSetCallback(hal_hrtim_handle_t *hhrtim,
                                 uint32_t output);

void HAL_HRTIM_OutputResetCallback(hal_hrtim_handle_t *hhrtim,
                                   uint32_t output);

void HAL_HRTIM_XbarOvrTriggerCallback(hal_hrtim_handle_t *hhrtim,
                                      uint32_t timer);

void HAL_HRTIM_XbarOvrRearmDelayCallback(hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer);

/* Interfaces for registering callbacks ***************************************/
#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
hal_status_t HAL_HRTIM_RegisterDMAHalfCallback(hal_hrtim_handle_t *hhrtim,
                                               hal_hrtim_timer_cb_t fct);

hal_status_t HAL_HRTIM_RegisterDMACpltCallback(hal_hrtim_handle_t *hhrtim,
                                               hal_hrtim_timer_cb_t fct);

hal_status_t HAL_HRTIM_RegisterDMAStopCallback(hal_hrtim_handle_t *hhrtim,
                                               hal_hrtim_timer_cb_t fct);

hal_status_t HAL_HRTIM_RegisterDMAErrorCallback(hal_hrtim_handle_t *hhrtim,
                                                hal_hrtim_timer_cb_t fct);
#endif /* USE_HAL_HRTIM_DMA */

#if defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
hal_status_t HAL_HRTIM_RegisterFaultCallback(hal_hrtim_handle_t *hhrtim,
                                             hal_hrtim_fault_cb_t fct);

hal_status_t HAL_HRTIM_RegisterSystemFaultCallback(hal_hrtim_handle_t *hhrtim,
                                                   hal_hrtim_cb_t fct);

hal_status_t HAL_HRTIM_RegisterBurstModePeriodCallback(hal_hrtim_handle_t *hhrtim,
                                                       hal_hrtim_cb_t fct);

hal_status_t HAL_HRTIM_RegisterSynchroCallback(hal_hrtim_handle_t *hhrtim,
                                               hal_hrtim_cb_t fct);
#endif /* USE_HAL_HRTIM_GLOBAL_CALLBACKS */

#if defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
hal_status_t HAL_HRTIM_RegisterUpdateCallback(hal_hrtim_handle_t *hhrtim,
                                              hal_hrtim_timer_cb_t fct);

hal_status_t HAL_HRTIM_RegisterRepetitionCallback(hal_hrtim_handle_t *hhrtim,
                                                  hal_hrtim_timer_cb_t fct);

hal_status_t HAL_HRTIM_RegisterResetCallback(hal_hrtim_handle_t *hhrtim,
                                             hal_hrtim_timer_cb_t fct);

hal_status_t HAL_HRTIM_RegisterDelayedProtectionCallback(hal_hrtim_handle_t *hhrtim,
                                                         hal_hrtim_timer_cb_t fct);
#endif /* USE_HAL_HRTIM_TIMER_CALLBACKS */

#if defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
hal_status_t HAL_HRTIM_RegisterCompareMatchCallback(hal_hrtim_handle_t *hhrtim,
                                                    hal_hrtim_cmp_cb_t fct);

hal_status_t HAL_HRTIM_RegisterCaptureCallback(hal_hrtim_handle_t *hhrtim,
                                               hal_hrtim_cpt_cb_t fct);
#endif /* USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */

#if defined(USE_HAL_HRTIM_OUTPUT_CALLBACKS) && (USE_HAL_HRTIM_OUTPUT_CALLBACKS == 1)
hal_status_t HAL_HRTIM_RegisterOutputSetCallback(hal_hrtim_handle_t *hhrtim,
                                                 hal_hrtim_output_cb_t fct);

hal_status_t HAL_HRTIM_RegisterOutputResetCallback(hal_hrtim_handle_t *hhrtim,
                                                   hal_hrtim_output_cb_t fct);
#endif /* USE_HAL_HRTIM_OUTPUT_CALLBACKS */

#if (defined(USE_HAL_HRTIM_XBAR_OVR_CALLBACKS) && (USE_HAL_HRTIM_XBAR_OVR_CALLBACKS == 1))
hal_status_t HAL_HRTIM_RegisterXbarOvrTriggerCallback(hal_hrtim_handle_t *hhrtim,
                                                      hal_hrtim_timer_cb_t fct);

hal_status_t HAL_HRTIM_RegisterXbarOvrRearmDelayCallback(hal_hrtim_handle_t *hhrtim,
                                                         hal_hrtim_timer_cb_t fct);
#endif /* USE_HAL_HRTIM_XBAR_OVR_CALLBACKS */

/**
  * @}
  */
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */

#if defined (USE_HAL_HRTIM_USER_DATA) && (USE_HAL_HRTIM_USER_DATA == 1)
/** @defgroup HRTIM_Exported_Functions_Group23 High Resolution Timer Setter and Getter of the user data.
  * @{
  *           At any moment, the application can store a pointer to its user data (eg. the application's private
  *           context information) into the HRTIM handle. The application can also retrieve the registered pointer to
  *           the user data whenever needed..
  */
void HAL_HRTIM_SetUserData(hal_hrtim_handle_t *hhrtim, const void *p_user_data);
const void *HAL_HRTIM_GetUserData(const hal_hrtim_handle_t *hhrtim);
/**
  * @}
  */
#endif /* USE_HAL_HRTIM_USER_DATA */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* HRTIM1 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_HAL_HRTIM_H */
