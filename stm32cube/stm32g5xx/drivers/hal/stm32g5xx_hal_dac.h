/**
  ******************************************************************************
  * @file    stm32g5xx_hal_dac.h
  * @brief   Header file for the DAC HAL module.
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
#ifndef STM32G5XX_HAL_DAC_H
#define STM32G5XX_HAL_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_dac.h"

/** @addtogroup DAC
  * @{
  */

#if defined(DAC1) || defined(DAC2) || defined(DAC5) || defined(DAC6) || defined(DAC7) || defined(DAC8) \
|| defined(DAC9) || defined(DAC10)

/* Exported types ------------------------------------------------------------*/

/** @defgroup DAC_Exported_Types HAL DAC Types
  * @{
  */

/** @defgroup DAC_Exported_Types_Group1 Enumerations
  * @{
  */

/**
  * @brief  HAL DAC instance
  */
typedef enum
{
#if defined(DAC1)
  HAL_DAC1 = DAC1_BASE, /*!< DAC1 */
#endif /* DAC1 */
#if defined(DAC2)
  HAL_DAC2 = DAC2_BASE, /*!< DAC2 */
#endif /* DAC2 */
#if defined(DAC5)
  HAL_DAC5 = DAC5_BASE, /*!< DAC5 */
#endif /* DAC5 */
#if defined(DAC6)
  HAL_DAC6 = DAC6_BASE, /*!< DAC6 */
#endif /* DAC6 */
#if defined(DAC7)
  HAL_DAC7 = DAC7_BASE, /*!< DAC7 */
#endif /* DAC7 */
#if defined(DAC8)
  HAL_DAC8 = DAC8_BASE, /*!< DAC8 */
#endif /* DAC8 */
#if defined(DAC9)
  HAL_DAC9 = DAC9_BASE, /*!< DAC9 */
#endif /* DAC9 */
#if defined(DAC10)
  HAL_DAC10 = DAC10_BASE, /*!< DAC10 */
#endif /* DAC10 */
} hal_dac_t;

/**
  * @brief  HAL DAC channels.
  */
typedef enum
{
  HAL_DAC_CHANNEL_1  = 0U, /*!< DAC channel 1 */
} hal_dac_channel_t;

/**
  * @brief  HAL DAC state definition
  */
typedef enum
{
  HAL_DAC_STATE_RESET                          = 0U,           /*!< DAC not yet initialized or is de-initialized */
  HAL_DAC_STATE_SEPARATE_CHANNEL_CONFIGURED    = (1U << 31U),  /*!< DAC is initialized
                                                                    and a global configuration has been applied,
                                                                    the channels are used separately */
} hal_dac_state_t;

/**
  * @brief  HAL DAC channel state definition
  */
typedef enum
{
  HAL_DAC_CHANNEL_STATE_RESET         = 0U,          /*!< DAC CHANNEL not yet initialized or disabled  */
  HAL_DAC_CHANNEL_STATE_IDLE          = (1U << 31U), /*!< DAC CHANNEL is initialized and a channel configuration
                                                          has been applied */
  HAL_DAC_CHANNEL_STATE_ACTIVE        = (1U << 30U), /*!< DAC CHANNEL is active, conversion is running */
#if defined(USE_HAL_DAC_DMA) && (USE_HAL_DAC_DMA == 1)
  HAL_DAC_CHANNEL_STATE_ACTIVE_SILENT = (1U << 29U)  /*!< DAC CHANNEL is active, conversion is running,
                                                          using DMA in silent mode */
#endif /* USE_HAL_DAC_DMA  */
} hal_dac_channel_state_t;

/**
  * @brief  HAL DAC channel trigger
  */
typedef enum
{
  HAL_DAC_TRIGGER_NONE                = 0xFFFFFFFFUL,                       /*!< Conversion is automatic once the DAC_DHRxxxx register*/
  HAL_DAC_TRIGGER_SOFTWARE            = LL_DAC_TRIGGER_SOFTWARE,            /*!< conversion started by software trigger for DAC channel */
  HAL_DAC_TRIGGER_TIM1_TRGO           = LL_DAC_TRIGGER_TIM1_TRGO,           /*!< TIM1 TRGO selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_TIM6_TRGO           = LL_DAC_TRIGGER_TIM6_TRGO,           /*!< TIM6 TRGO selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_TIM7_TRGO           = LL_DAC_TRIGGER_TIM7_TRGO,           /*!< TIM7 TRGO selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_TIM8_TRGO           = LL_DAC_TRIGGER_TIM8_TRGO,           /*!< TIM8 TRGO selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_TIM9_TRGO           = LL_DAC_TRIGGER_TIM9_TRGO,           /*!< TIM9 TRGO selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_TIM15_TRGO          = LL_DAC_TRIGGER_TIM15_TRGO,          /*!< TIM15 TRGO selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_TIM20_TRGO          = LL_DAC_TRIGGER_TIM20_TRGO,          /*!< TIM20 TRGO selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_TIM26_TRGO          = LL_DAC_TRIGGER_TIM26_TRGO,          /*!< TIM26 TRGO selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_TIM27_TRGO          = LL_DAC_TRIGGER_TIM27_TRGO,          /*!< TIM27 TRGO selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_LPTIM1_OC1          = LL_DAC_TRIGGER_LPTIM1_OC1,          /*!< LPTIM1 CH1 selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_EXTI9               = LL_DAC_TRIGGER_EXTI9,               /*!< EXTI Line9 event selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_PLAY_OUT            = LL_DAC_TRIGGER_PLAY_OUT,            /*!< PLAY OUT selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_HRTIM1_TRG1         = LL_DAC_TRIGGER_HRTIM1_TRG1,         /*!< HRTIM1 TRIG 1 selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_HRTIM1_TRG2         = LL_DAC_TRIGGER_HRTIM1_TRG2,         /*!< HRTIM1 TRIG 2 selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_HRTIM1_TRG3         = LL_DAC_TRIGGER_HRTIM1_TRG3,         /*!< HRTIM1 TRIG 3 selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_HRTIM1_RST1         = LL_DAC_TRIGGER_HRTIM1_RST1,         /*!< HRTIM1 RST TRIG 1 selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_HRTIM1_RST2         = LL_DAC_TRIGGER_HRTIM1_RST2,         /*!< HRTIM1 RST TRIG 2 selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_HRTIM1_RST3         = LL_DAC_TRIGGER_HRTIM1_RST3,         /*!< HRTIM1 RST TRIG 3 selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_HRTIM1_RST4         = LL_DAC_TRIGGER_HRTIM1_RST4,         /*!< HRTIM1 RST TRIG 4 selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_HRTIM1_RST5         = LL_DAC_TRIGGER_HRTIM1_RST5,         /*!< HRTIM1 RST TRIG 5 selected as external conversion trigger for DAC channel. */
  HAL_DAC_TRIGGER_HRTIM1_RST6         = LL_DAC_TRIGGER_HRTIM1_RST6,         /*!< HRTIM1 RST TRIG 6 selected as external conversion trigger for DAC channel. */
} hal_dac_trigger_t;

/**
  * @brief DAC channel increment trigger for sawtooth generation
  */
typedef enum
{
  HAL_DAC_INC_TRIGGER_NONE                = 0xFFFFFFFFUL,                           /*!< Conversion is automatic once the DAC_DHRxxxx register*/
  HAL_DAC_INC_TRIGGER_SOFTWARE            = LL_DAC_INC_TRIGGER_SOFTWARE,            /*!< conversion started by software trigger for DAC channel */
  HAL_DAC_INC_TRIGGER_TIM1_TRGO           = LL_DAC_INC_TRIGGER_TIM1_TRGO,           /*!< TIM1 TRGO selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM1_TRGO2          = LL_DAC_INC_TRIGGER_TIM1_TRGO2,          /*!< TIM1 TRGO2 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM2_TRGO           = LL_DAC_INC_TRIGGER_TIM2_TRGO,           /*!< TIM2 TRGO selected as increment trigger for DAC channel (specific to DAC instances: DAC1, DAC7). Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM3_TRGO           = LL_DAC_INC_TRIGGER_TIM3_TRGO,           /*!< TIM3 TRGO selected as increment trigger for DAC channel (specific to DAC instances: DAC2, DAC8). Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM4_TRGO           = LL_DAC_INC_TRIGGER_TIM4_TRGO,           /*!< TIM4 TRGO selected as increment trigger for DAC channel (specific to DAC instances: DAC3, DAC9). Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM5_TRGO           = LL_DAC_INC_TRIGGER_TIM5_TRGO,           /*!< TIM5 TRGO selected as increment trigger for DAC channel (specific to DAC instances: DAC4, DAC10). Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM6_TRGO           = LL_DAC_INC_TRIGGER_TIM6_TRGO,           /*!< TIM6 TRGO selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM7_TRGO           = LL_DAC_INC_TRIGGER_TIM7_TRGO,           /*!< TIM7 TRGO selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM8_TRGO           = LL_DAC_INC_TRIGGER_TIM8_TRGO,           /*!< TIM8 TRGO selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM8_TRGO2          = LL_DAC_INC_TRIGGER_TIM8_TRGO2,          /*!< TIM8 TRGO2 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM9_TRGO           = LL_DAC_INC_TRIGGER_TIM9_TRGO,           /*!< TIM9 TRGO selected as increment trigger for DAC channel TIM9 TRGO (specific to DAC instances: DAC2, DAC6, DAC8, DAC10). Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM12_TRGO          = LL_DAC_INC_TRIGGER_TIM12_TRGO,          /*!< TIM12 TRGO selected as increment trigger for DAC channel (specific to DAC instances: DAC1, DAC5, DAC7, DAC9). Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM15_TRGO          = LL_DAC_INC_TRIGGER_TIM15_TRGO,          /*!< TIM15 TRGO selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM20_TRGO          = LL_DAC_INC_TRIGGER_TIM20_TRGO,          /*!< TIM20 TRGO selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM20_TRGO2         = LL_DAC_INC_TRIGGER_TIM20_TRGO2,         /*!< TIM20 TRGO2 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM26_TRGO          = LL_DAC_INC_TRIGGER_TIM26_TRGO,          /*!< TIM26 TRGO selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_TIM27_TRGO          = LL_DAC_INC_TRIGGER_TIM27_TRGO,          /*!< TIM27 TRGO selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_LPTIM1_OC1          = LL_DAC_INC_TRIGGER_LPTIM1_OC1,          /*!< LPTIM1 CH1 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_EXTI10              = LL_DAC_INC_TRIGGER_EXTI10,              /*!< EXTI Line10 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_PLAY_OUT            = LL_DAC_INC_TRIGGER_PLAY_OUT,            /*!< PLAY OUT selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_HRTIM1_STP1         = LL_DAC_INC_TRIGGER_HRTIM1_STP1,         /*!< HRTIM1 STEP TRIG OUT1 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_HRTIM1_STP2         = LL_DAC_INC_TRIGGER_HRTIM1_STP2,         /*!< HRTIM1 STEP TRIG OUT2 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_HRTIM1_STP3         = LL_DAC_INC_TRIGGER_HRTIM1_STP3,         /*!< HRTIM1 STEP TRIG OUT3 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_HRTIM1_STP4         = LL_DAC_INC_TRIGGER_HRTIM1_STP4,         /*!< HRTIM1 STEP TRIG OUT4 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_HRTIM1_STP5         = LL_DAC_INC_TRIGGER_HRTIM1_STP5,         /*!< HRTIM1 STEP TRIG OUT5 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
  HAL_DAC_INC_TRIGGER_HRTIM1_STP6         = LL_DAC_INC_TRIGGER_HRTIM1_STP6,         /*!< HRTIM1 STEP TRIG OUT6 selected as increment trigger for DAC channel. Note: only to be used as step (sawtooth generation) trigger. */
} hal_dac_sawtooth_inc_trigger_t;

/**
  * @brief DAC channel reset trigger for sawtooth generation
  */
typedef enum
{
  HAL_DAC_RST_TRIGGER_NONE                = 0xFFFFFFFFUL,                           /*!< Conversion is automatic once the DAC_DHRxxxx register*/
  HAL_DAC_RST_TRIGGER_SOFTWARE            = LL_DAC_RST_TRIGGER_SOFTWARE,            /*!< conversion started by software trigger for DAC channel */
  HAL_DAC_RST_TRIGGER_TIM1_TRGO           = LL_DAC_RST_TRIGGER_TIM1_TRGO,           /*!< TIM1 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_TIM6_TRGO           = LL_DAC_RST_TRIGGER_TIM6_TRGO,           /*!< TIM6 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_TIM7_TRGO           = LL_DAC_RST_TRIGGER_TIM7_TRGO,           /*!< TIM7 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_TIM8_TRGO           = LL_DAC_RST_TRIGGER_TIM8_TRGO,           /*!< TIM8 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_TIM9_TRGO           = LL_DAC_RST_TRIGGER_TIM9_TRGO,           /*!< TIM9 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_TIM15_TRGO          = LL_DAC_RST_TRIGGER_TIM15_TRGO,          /*!< TIM15 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_TIM20_TRGO          = LL_DAC_RST_TRIGGER_TIM20_TRGO,          /*!< TIM20 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_TIM26_TRGO          = LL_DAC_RST_TRIGGER_TIM26_TRGO,          /*!< TIM26 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_TIM27_TRGO          = LL_DAC_RST_TRIGGER_TIM27_TRGO,          /*!< TIM27 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_LPTIM1_OC1          = LL_DAC_RST_TRIGGER_LPTIM1_OC1,          /*!< LPTIM CH1 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_EXTI9               = LL_DAC_RST_TRIGGER_EXTI9,               /*!< EXTI Line9 TRGO selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_PLAY_OUT            = LL_DAC_RST_TRIGGER_PLAY_OUT,            /*!< PLAY OUT selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_HRTIM1_TRG1         = LL_DAC_RST_TRIGGER_HRTIM1_TRG1,         /*!< HRTIM DAC TRG1 selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_HRTIM1_TRG2         = LL_DAC_RST_TRIGGER_HRTIM1_TRG2,         /*!< HRTIM DAC TRG2 selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_HRTIM1_TRG3         = LL_DAC_RST_TRIGGER_HRTIM1_TRG3,         /*!< HRTIM DAC TRG3 selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_HRTIM1_RST1         = LL_DAC_RST_TRIGGER_HRTIM1_RST1,         /*!< HRTIM1 DAC RESET TRG1 selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_HRTIM1_RST2         = LL_DAC_RST_TRIGGER_HRTIM1_RST2,         /*!< HRTIM1 DAC RESET TRG2 selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_HRTIM1_RST3         = LL_DAC_RST_TRIGGER_HRTIM1_RST3,         /*!< HRTIM1 DAC RESET TRG3 selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_HRTIM1_RST4         = LL_DAC_RST_TRIGGER_HRTIM1_RST4,         /*!< HRTIM1 DAC RESET TRG4 selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_HRTIM1_RST5         = LL_DAC_RST_TRIGGER_HRTIM1_RST5,         /*!< HRTIM1 DAC RESET TRG5 selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
  HAL_DAC_RST_TRIGGER_HRTIM1_RST6         = LL_DAC_RST_TRIGGER_HRTIM1_RST6,         /*!< HRTIM1 DAC RESET TRG6 selected as reset trigger for DAC channel. Note: only to be used as reset (sawtooth generation) trigger. */
} hal_dac_sawtooth_rst_trigger_t;

/**
  * @brief DAC sawtooth wave generation status
  */
typedef enum
{
  HAL_DAC_SAWTOOTH_DISABLED = 0U,  /*!< The sawtooth wave generation is disabled */
  HAL_DAC_SAWTOOTH_ENABLED  = 1U   /*!< The sawtooth wave generation is enabled */
} hal_dac_sawtooth_status_t;

/**
  * @brief DAC extended sawtooth wave generation status
  */
typedef enum
{
  HAL_DAC_EXTENDED_SAWTOOTH_DISABLED = LL_DAC_EXTENDED_SAWTOOTH_DISABLED,  /*!< The extended sawtooth feature is disabled */
  HAL_DAC_EXTENDED_SAWTOOTH_ENABLED  = LL_DAC_EXTENDED_SAWTOOTH_ENABLED    /*!< The extended sawtooth feature is enabled */
} hal_dac_extended_sawtooth_t;

/**
  * @brief DAC channel output buffer mode
  */
typedef enum
{
  HAL_DAC_OUTPUT_BUFFER_ENABLED  = LL_DAC_OUTPUT_BUFFER_ENABLE,  /*!< The output is buffered:
                                                                      higher drive current capability,
                                                                      but also higher current consumption */
  HAL_DAC_OUTPUT_BUFFER_DISABLED = LL_DAC_OUTPUT_BUFFER_DISABLE, /*!< The output is not buffered:
                                                                      lower drive current capability,
                                                                      but also lower current consumption */
} hal_dac_output_buffer_status_t;

/**
  * @brief   DAC channel data alignment
  */
typedef enum
{
  HAL_DAC_DATA_ALIGN_12_BITS_RIGHT = 0x00000000U, /*!< Data must be written in 12-bit right alignment */
  HAL_DAC_DATA_ALIGN_12_BITS_LEFT  = 0x00000001U, /*!< Data must be written in 12-bit left  alignment */
  HAL_DAC_DATA_ALIGN_8_BITS_RIGHT  = 0x00000002U  /*!< Data must be written in  8-bit right alignment */
} hal_dac_data_alignment_t;

/**
  * @brief DAC channel output connection.
  * @note  With some configuration of mode and buffer, there are both internal and external connections.
  *        This applies regardless of this hal_dac_output_connection_t value.
  */
typedef enum
{
  HAL_DAC_OUTPUT_CONNECTION_EXTERNAL = LL_DAC_OUTPUT_CONNECT_EXTERNAL,    /*!< DAC channel output is connected to external
                                        pin.
                                        Note: Depending on other parameters (mode normal or sample and hold,
                                              output buffer state), output can also be connected to on-chip
                                              peripherals, refer to ref manual. */
  HAL_DAC_OUTPUT_CONNECTION_INTERNAL = LL_DAC_OUTPUT_CONNECT_INTERNAL /*!< DAC channel output is connected to on-chip
                                        peripherals (via internal paths).
                                        Note: Depending on other parameters (mode normal or sample and hold,
                                              output buffer state), output can also be connected to external pin,
                                              refer to ref manual. */
} hal_dac_output_connection_t ;

/**
  * @brief DAC channel sample and hold mode
  */
typedef enum
{
  HAL_DAC_SAMPLE_AND_HOLD_DISABLED = LL_DAC_OUTPUT_MODE_NORMAL,         /*!< The output is in normal mode */
  HAL_DAC_SAMPLE_AND_HOLD_ENABLED  = LL_DAC_OUTPUT_MODE_SAMPLE_AND_HOLD /*!< The output is in sample-and-hold mode.
                                                                             Note: the sample-and-hold mode requires
                                                                             an external capacitor */
} hal_dac_sample_and_hold_status_t;

/**
  * @brief  DAC high frequency interface mode
  */
typedef enum
{
  HAL_DAC_HIGH_FREQ_MODE_DISABLED     = LL_DAC_HIGH_FREQ_MODE_DISABLED,    /*!< High frequency interface mode disabled*/
  HAL_DAC_HIGH_FREQ_MODE_ABOVE_80MHZ  = LL_DAC_HIGH_FREQ_MODE_ABOVE_80MHZ, /*!< High frequency interface
                                                                                mode compatible to AHB>80MHz enabled */
  HAL_DAC_HIGH_FREQ_MODE_ABOVE_160MHZ = LL_DAC_HIGH_FREQ_MODE_ABOVE_160MHZ /*!< High frequency interface
                                                                                mode compatible to AHB>160MHz enabled */
} hal_dac_high_freq_mode_t;

/**
  * @brief  DAC channel signed or unsigned data format
  */
typedef enum
{
  HAL_DAC_SIGN_FORMAT_UNSIGNED = LL_DAC_SIGN_FORMAT_UNSIGNED, /*!< The data format is not signed */
  HAL_DAC_SIGN_FORMAT_SIGNED   = LL_DAC_SIGN_FORMAT_SIGNED    /*!< The data format is signed */
} hal_dac_sign_format_t;

/**
  * @brief  DAC channel DMA double data mode
  */
typedef enum
{
  HAL_DAC_DMA_DOUBLE_DATA_MODE_DISABLED = 0U,  /*!< The DMA data mode is the single data mode */
  HAL_DAC_DMA_DOUBLE_DATA_MODE_ENABLED  = 1U   /*!< The DMA data mode is the double data mode */
} hal_dac_dma_double_data_mode_status_t;

/**
  * @brief  HAL DAC channel triangle wave and pseudo noise amplitude
  */

typedef enum
{
  HAL_DAC_WAVE_AMPLITUDE_1    = LL_DAC_TRIANGLE_AMPLITUDE_1,    /*!< Noise/triangle amplitude equal to 1 */
  HAL_DAC_WAVE_AMPLITUDE_3    = LL_DAC_TRIANGLE_AMPLITUDE_3,    /*!< Noise/triangle amplitude equal to 3 */
  HAL_DAC_WAVE_AMPLITUDE_7    = LL_DAC_TRIANGLE_AMPLITUDE_7,    /*!< Noise/triangle amplitude equal to 7 */
  HAL_DAC_WAVE_AMPLITUDE_15   = LL_DAC_TRIANGLE_AMPLITUDE_15,   /*!< Noise/triangle amplitude equal to 15 */
  HAL_DAC_WAVE_AMPLITUDE_31   = LL_DAC_TRIANGLE_AMPLITUDE_31,   /*!< Noise/triangle amplitude equal to 31 */
  HAL_DAC_WAVE_AMPLITUDE_63   = LL_DAC_TRIANGLE_AMPLITUDE_63,   /*!< Noise/triangle amplitude equal to 63 */
  HAL_DAC_WAVE_AMPLITUDE_127  = LL_DAC_TRIANGLE_AMPLITUDE_127,  /*!< Noise/triangle amplitude equal to 127 */
  HAL_DAC_WAVE_AMPLITUDE_255  = LL_DAC_TRIANGLE_AMPLITUDE_255,  /*!< Noise/triangle amplitude equal to 255 */
  HAL_DAC_WAVE_AMPLITUDE_511  = LL_DAC_TRIANGLE_AMPLITUDE_511,  /*!< Noise/triangle amplitude equal to 511 */
  HAL_DAC_WAVE_AMPLITUDE_1023 = LL_DAC_TRIANGLE_AMPLITUDE_1023, /*!< Noise/triangle amplitude equal to 1023 */
  HAL_DAC_WAVE_AMPLITUDE_2047 = LL_DAC_TRIANGLE_AMPLITUDE_2047, /*!< Noise/triangle amplitude equal to 2047  */
  HAL_DAC_WAVE_AMPLITUDE_4095 = LL_DAC_TRIANGLE_AMPLITUDE_4095, /*!< Noise/triangle amplitude equal to 4095  */
} hal_dac_wave_amplitude_t;


/**
  * @brief  HAL DAC channel sawtooth direction mode
  */

typedef enum
{
  HAL_DAC_SAWTOOTH_DIRECTION_DECREMENT  = LL_DAC_SAWTOOTH_DIRECTION_DECREMENT, /*!< Sawtooth wave generation:
                                                                                    direction is decrement */
  HAL_DAC_SAWTOOTH_DIRECTION_INCREMENT  = LL_DAC_SAWTOOTH_DIRECTION_INCREMENT  /*!< Sawtooth wave generation:
                                                                                    direction is increment */
} hal_dac_sawtooth_direction_t;

/**
  * @}
  */
/* Exported Constants --------------------------------------------------------*/
/** @defgroup DAC_Exported_Constants HAL DAC Constants
  * @{
  */
/**
  * @brief  HAL DAC error code,
  *         declared and used has bit fields in HAL_DAC_GetLastErrorCodes()
  */
#if defined(USE_HAL_DAC_GET_LAST_ERRORS) && (USE_HAL_DAC_GET_LAST_ERRORS == 1)
#define HAL_DAC_ERROR_NONE              (0UL)      /*!< No error */
#define HAL_DAC_ERROR_DMA_UNDERRUN_CH1  (1UL << 0U) /*!< DMA underrun error on channel 1 */
#define HAL_DAC_ERROR_DMA_CH1           (1UL << 1U) /*!< DMA transfer error on channel 1 */

#endif /* USE_HAL_DAC_GET_LAST_ERRORS */

#if defined(USE_HAL_DAC_DMA) && (USE_HAL_DAC_DMA == 1)
/**
  * @brief  HAL DAC optional interrupts
  */
#define HAL_DAC_OPT_DMA_IT_NONE     HAL_DMA_OPT_IT_NONE     /*!< All optional interrupts are disabled */
#define HAL_DAC_OPT_DMA_IT_HT       HAL_DMA_OPT_IT_HT       /*!< Enable optional IT half completed transfer */
#define HAL_DAC_OPT_DMA_IT_DEFAULT  HAL_DMA_OPT_IT_DEFAULT  /*!< Enable all optional IT */
#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#define HAL_DAC_OPT_DMA_IT_SILENT   HAL_DMA_OPT_IT_SILENT   /*!< DMA in silent mode */
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /*  USE_HAL_DAC_DMA */

/**
  * @}
  */

/* Exported macro --------------------------------------------------------*/
/** @defgroup DAC_Exported_Macro DAC Exported Macro
  * @{
  */

/**
  * @brief  Helper macro to calculate the DAC conversion data (unit: digital
  *         value) corresponding to a voltage (unit: mVolt).
  * @param  vrefanalog_voltage Analog reference voltage (unit: mV)
  * @param  dac_voltage Voltage to be generated by DAC channel (unit: mVolt).
  * @param  dac_resolution This parameter can be one of the following values:
  *         @arg @ref HAL_DAC_DATA_ALIGN_12_BITS_RIGHT
  *         @arg @ref HAL_DAC_DATA_ALIGN_8_BITS_RIGHT
  * @note   This helper macro is intended to provide input data in voltage
  *         rather than digital value,
  *         to be used with HAL DAC functions such as
  *         @ref HAL_DAC_SetChannelData().
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro HAL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @retval DAC conversion data (unit: digital value)
  */
#define HAL_DAC_CALC_VOLTAGE_TO_DATA(vrefanalog_voltage, dac_voltage, dac_resolution) \
  LL_DAC_CALC_VOLTAGE_TO_DATA(vrefanalog_voltage, dac_voltage, (uint32_t)(dac_resolution))

/**
  * @}
  */

/** @defgroup DAC_Exported_Types_Group2 Handle Structure
  * @{
  */
/**
  * @brief DAC Handle structure Definition
  *
  */
/*!< DAC handle structure definition */
typedef struct hal_dac_handle_s hal_dac_handle_t; /*!< DAC handle type definition */
/**
  * @}
  */

/** @defgroup DAC_Exported_Types_Group_Callback callback prototype
  * @{
  */
/* DAC callback prototype and error callback prototype */
typedef void (* hal_dac_cb_t)(hal_dac_handle_t *hdac, hal_dac_channel_t channel); /*!< Callback prototype
                                                                                       for converter completed */
typedef void (* hal_dac_error_cb_t)(hal_dac_handle_t *hdac);        /*!< Callback prototype for error callback */
/**
  * @}
  */

/** @addtogroup DAC_Exported_Types_Group2 Handle Structure
  * @{
  */

/**
  * @brief  DAC handle structure definition,
  *         contains: DAC instance, states, callbacks, DMA handles linked with DAC channels.
  */
struct hal_dac_handle_s
{
  hal_dac_t                         instance;      /*!< Peripheral instance */
  volatile hal_dac_state_t          global_state;  /*!< DAC global state */
  volatile hal_dac_channel_state_t  channel_state[DAC_NB_OF_CHANNEL]; /*!< State for channels subinstances,
                                                                           they can be active in parallel */
  volatile uint32_t                *channel_dhr_address[DAC_NB_OF_CHANNEL]; /*!< DHR (data holding register) address
                                                                                 according to the alignment */

#if defined(USE_HAL_DAC_GET_LAST_ERRORS) && (USE_HAL_DAC_GET_LAST_ERRORS == 1)
  volatile uint16_t                 last_error_codes[DAC_NB_OF_CHANNEL]; /*!< DAC channel errors codes
                                                    array of uint16_t to avoid race condition between the channels */
#endif /* USE_HAL_DAC_GET_LAST_ERRORS */

#if defined(USE_HAL_DAC_DMA) && (USE_HAL_DAC_DMA == 1)
  hal_dma_handle_t                 *dma_ch[DAC_NB_OF_CHANNEL];   /*!< Pointer to a DMA handle */
#endif /* USE_HAL_DAC_DMA  */

#if defined(USE_HAL_DAC_REGISTER_CALLBACKS) && (USE_HAL_DAC_REGISTER_CALLBACKS == 1)
  hal_dac_cb_t                 p_conv_cplt_cb;      /*!< Converter completed callback */
  hal_dac_cb_t                 p_conv_half_cplt_cb; /*!< Converter half completed callback */
  hal_dac_cb_t                 p_stop_cplt_cb;      /*!< Stop completed callback */
  hal_dac_error_cb_t           p_error_cb;          /*!< Converter error callback */
#endif /* USE_HAL_DAC_REGISTER_CALLBACKS */

#if defined(USE_HAL_DAC_USER_DATA) && (USE_HAL_DAC_USER_DATA == 1)
  const void                  *p_user_data; /*!< User Data Pointer */
#endif /* USE_HAL_DAC_USER_DATA */
};

/**
  * @}
  */

/** @defgroup DAC_Exported_Types_Group4 Configuration Structure
  * @{
  */

/**
  * @brief   DAC configuration "sample and hold" structure definition
  */
typedef struct
{
  uint32_t sample_time_cycle;/*!< The sample time for the channel, unit is in number of clock period.
                                  This parameter must be a number the range [0, 1023].
                                  The sample_time_cycle is applied when the sample_and_hold mode is
                                  HAL_DAC_SAMPLE_AND_HOLD_ENABLED */

  uint32_t hold_time_cycle;  /*!< The hold time for the channel, unit is in number of clock period.
                                  This parameter must be a number the range [0, 1023].
                                  The hold_time is applied when the sample_and_hold mode is
                                  HAL_DAC_SAMPLE_AND_HOLD_ENABLED */

  uint32_t refresh_time_cycle; /*!< The refresh time for the channel, unit is in number of clock period.
                                    This parameter must be a number the range [0, 255].
                                    The refresh_time is applied when the sample_and_hold mode is
                                    HAL_DAC_SAMPLE_AND_HOLD_ENABLED */
} hal_dac_channel_sample_and_hold_config_t;

/**
  * @brief   DAC configuration structure definition
  */
typedef struct
{
  hal_dac_high_freq_mode_t high_frequency_mode;  /*!< The frequency interface mode
                                                      Note: HAL_DAC_GetOptimumFrequencyMode() API allows
                                                      to select and update the high frequency mode afterwards */
} hal_dac_config_t;

/**
  * @brief   DAC channel configuration structure definition
  */
typedef struct
{
  hal_dac_sign_format_t           data_sign_format;  /*!< The data format: signed data or unsigned data */
  hal_dac_trigger_t               trigger;           /*!< The external trigger for the channel */
  hal_dac_output_buffer_status_t  output_buffer;     /*!< The DAC channel output buffer: enabled or disabled */
  hal_dac_output_connection_t     output_connection; /*!< The DAC channel output connection:
                                                          to external pin or to on chip peripheral */
  hal_dac_data_alignment_t        alignment;         /*!< Default alignment and width, for both channel:
                                                          12bit right or left align, 8bit right align */
} hal_dac_channel_config_t;


/**
  * @brief   DAC configuration "sawtooth" structure definition
  */
typedef struct
{
  hal_dac_sawtooth_inc_trigger_t  inc_trigger;      /*!< The increment trigger,   DAC_STMODR : STINCTRIGSEL1[4:0] */
  hal_dac_sawtooth_rst_trigger_t  rst_trigger;      /*!< The reset value trigger, DAC_STMODR : STRSTTRIGSEL1[4:0] */
  hal_dac_sawtooth_direction_t    direction ;       /*!< The direction to be used for wave generation:
                                                         increment or decrement. */
  int32_t                         reset_value;      /*!< The sawtooth wave reset value.
                                                         Value is signed, DAC sawtooth counter value can be negative
                                                         (Please refer to Reference Manual "DAC extended sawtooth wave
                                                         generation").
                                                         Value is 16bit in 2's complement signed format.
                                                         Range is from 0x8000 to 0x7FFF */
  uint32_t                        increment_value;  /*!< The sawtooth wave increment value.
                                                         12.4 bit format, unsigned: 12 bits exponent / 4 bits mantissa
                                                         Step value step is 1/16 = 0.0625
                                                         Step value range is 0.0000 to 4095.9375 (0xFFF.F) */
  hal_dac_extended_sawtooth_t     extended_mode;    /*!< The extended sawtooth feature: enabled or disabled */

  uint32_t                        max_value;        /*!< The sawtooth wave max saturation value
                                                         Range is from 0 to DAC full range 4095 (0xFFF) */

  uint32_t                        min_value;        /*!< The sawtooth wave min saturation value
                                                         Range is from 0 to DAC full range 4095 (0xFFF) */
} hal_dac_sawtooth_config_t;

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup DAC_Exported_Functions
  * @{
  */

/** @addtogroup DAC_Exported_Functions_Group1_1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
hal_status_t HAL_DAC_Init(hal_dac_handle_t *hdac, hal_dac_t instance);
void         HAL_DAC_DeInit(hal_dac_handle_t *hdac);
hal_dac_t    HAL_DAC_GetInstance(const hal_dac_handle_t *hdac);
DAC_TypeDef *HAL_DAC_GetLLInstance(const hal_dac_handle_t *hdac);
/* Peripheral configuration */
hal_dac_high_freq_mode_t HAL_DAC_GetOptimumFrequencyMode(const hal_dac_handle_t *hdac);
hal_status_t HAL_DAC_SetConfig(hal_dac_handle_t *hdac, const hal_dac_config_t *p_config);
void         HAL_DAC_GetConfig(const hal_dac_handle_t *hdac, hal_dac_config_t *p_config);
void         HAL_DAC_ResetConfig(hal_dac_handle_t *hdac);
/* Calibration functions */
hal_status_t HAL_DAC_CalibrateChannelBuffer(hal_dac_handle_t *hdac, hal_dac_channel_t channel);
hal_status_t HAL_DAC_SetChannelBufferCalibrationValue(hal_dac_handle_t *hdac, hal_dac_channel_t channel,
                                                      uint32_t value);
uint32_t     HAL_DAC_GetChannelBufferCalibrationValue(const hal_dac_handle_t *hdac, hal_dac_channel_t channel);

/**
  * @}
  */

/** @addtogroup DAC_Exported_Functions_Group1_2
  * @{
  */
/* Peripheral channel configuration */
hal_status_t HAL_DAC_SetConfigChannel(hal_dac_handle_t *hdac, hal_dac_channel_t channel,
                                      const hal_dac_channel_config_t *p_config);

void         HAL_DAC_GetConfigChannel(const hal_dac_handle_t *hdac, hal_dac_channel_t channel,
                                      hal_dac_channel_config_t *p_config);

hal_status_t HAL_DAC_SetChannelAlignment(hal_dac_handle_t *hdac, hal_dac_channel_t channel,
                                         hal_dac_data_alignment_t        alignment);

hal_dac_data_alignment_t HAL_DAC_GetChannelAlignment(const hal_dac_handle_t *hdac, hal_dac_channel_t channel);

/**
  * @}
  */

/* Input and output operation functions *****************************************************/
/** @addtogroup DAC_Exported_Functions_Group2_1
  * @{
  */

hal_status_t HAL_DAC_TrigSWConversionChannel(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_status_t HAL_DAC_StartChannel(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_status_t HAL_DAC_StopChannel(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_status_t HAL_DAC_SetChannelData(hal_dac_handle_t *hdac, hal_dac_channel_t channel, uint32_t data);

uint32_t     HAL_DAC_GetChannelData(const hal_dac_handle_t *hdac, hal_dac_channel_t channel);

#if defined(USE_HAL_DAC_DMA) && (USE_HAL_DAC_DMA == 1)
/* DMA separate channel functions to link DAC channel with DMA */
hal_status_t HAL_DAC_SetChannelDMA(hal_dac_handle_t *hdac, hal_dma_handle_t *hdma, hal_dac_channel_t channel);

hal_status_t HAL_DAC_StartChannel_DMA(hal_dac_handle_t *hdac, hal_dac_channel_t channel, const void *p_data,
                                      uint32_t size_byte);

hal_status_t HAL_DAC_StartChannel_DMA_Opt(hal_dac_handle_t *hdac, hal_dac_channel_t channel, const void *p_data,
                                          uint32_t size_byte, uint32_t dac_opt_interrupt);

hal_status_t HAL_DAC_StopChannel_DMA(hal_dac_handle_t *hdac, hal_dac_channel_t channel);
#endif /* USE_HAL_DAC_DMA */

/**
  * @}
  */


/** @addtogroup DAC_Exported_Functions_Group3
  * @{
  */

/* Peripheral control functions */

#if defined(USE_HAL_DAC_DMA) && (USE_HAL_DAC_DMA == 1)
/* DMA double data mode functions  */
hal_status_t HAL_DAC_EnableChannelDMADoubleDataMode(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_status_t HAL_DAC_DisableChannelDMADoubleDataMode(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_dac_dma_double_data_mode_status_t HAL_DAC_IsEnabledChannelDMADoubleDataMode(hal_dac_handle_t *hdac,
                                                                                hal_dac_channel_t channel);
#endif /* USE_HAL_DAC_DMA */

/* Peripheral channel configuration and control functions */
hal_status_t HAL_DAC_EnableChannelAddingTriangleWave(hal_dac_handle_t *hdac, hal_dac_channel_t channel,
                                                     hal_dac_wave_amplitude_t amplitude);

hal_status_t HAL_DAC_DisableChannelAddingTriangleWave(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_status_t HAL_DAC_EnableChannelAddingNoiseWave(hal_dac_handle_t *hdac, hal_dac_channel_t channel,
                                                  hal_dac_wave_amplitude_t amplitude);

hal_status_t HAL_DAC_DisableChannelAddingNoiseWave(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_status_t HAL_DAC_SetConfigChannelSawtoothWave(hal_dac_handle_t *hdac, hal_dac_channel_t channel,
                                                  const hal_dac_sawtooth_config_t *p_config);

hal_status_t HAL_DAC_GetConfigChannelSawtoothWave(const hal_dac_handle_t *hdac, hal_dac_channel_t channel,
                                                  hal_dac_sawtooth_config_t *p_config);

hal_status_t HAL_DAC_EnableChannelSawtoothWave(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_status_t HAL_DAC_DisableChannelSawtoothWave(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_dac_sawtooth_status_t HAL_DAC_IsEnabledChannelSawtoothWave(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_status_t HAL_DAC_ResetChannelSawtoothWave(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_status_t HAL_DAC_TrigSWChannelSawtoothWave(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

/* Sample and hold functions  */
hal_status_t HAL_DAC_SetConfigChannelSampleAndHold(hal_dac_handle_t *hdac, hal_dac_channel_t channel,
                                                   const hal_dac_channel_sample_and_hold_config_t *p_config);

void HAL_DAC_GetConfigChannelSampleAndHold(const hal_dac_handle_t *hdac, hal_dac_channel_t channel,
                                           hal_dac_channel_sample_and_hold_config_t *p_config);

hal_status_t HAL_DAC_EnableChannelSampleAndHold(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_status_t HAL_DAC_DisableChannelSampleAndHold(hal_dac_handle_t *hdac, hal_dac_channel_t channel);

hal_dac_sample_and_hold_status_t HAL_DAC_IsEnabledChannelSampleAndHold(hal_dac_handle_t *hdac,
                                                                       hal_dac_channel_t channel);

/**
  * @}
  */

/** @addtogroup DAC_Exported_Functions_Group4
  * @{
  */
/* Callbacks functions *****************************/
/* DAC callback */
void HAL_DAC_ConvCpltCallback(hal_dac_handle_t *hdac, hal_dac_channel_t channel);
void HAL_DAC_ConvHalfCpltCallback(hal_dac_handle_t *hdac, hal_dac_channel_t channel);
void HAL_DAC_StopCpltCallback(hal_dac_handle_t *hdac, hal_dac_channel_t channel);
void HAL_DAC_ErrorCallback(hal_dac_handle_t *hdac);

#if (USE_HAL_DAC_REGISTER_CALLBACKS == 1)
/* DAC callback registering */
hal_status_t HAL_DAC_RegisterConvCpltCallback(hal_dac_handle_t *hdac, hal_dac_cb_t p_callback);
hal_status_t HAL_DAC_RegisterConvHalfCpltCallback(hal_dac_handle_t *hdac, hal_dac_cb_t p_callback);
hal_status_t HAL_DAC_RegisterStopCpltCallback(hal_dac_handle_t *hdac, hal_dac_cb_t p_callback);
hal_status_t HAL_DAC_RegisterErrorCallback(hal_dac_handle_t *hdac, hal_dac_error_cb_t p_callback);
#endif /* USE_HAL_DAC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup DAC_Exported_Functions_Group5
  * @{
  */
/* Peripheral State, kernel clock frequency, and Error functions ***************************************/
hal_dac_state_t         HAL_DAC_GetState(const hal_dac_handle_t *hdac);

hal_dac_channel_state_t HAL_DAC_GetChannelState(const hal_dac_handle_t *hdac, hal_dac_channel_t channel);

uint32_t HAL_DAC_GetClockFreq(const hal_dac_handle_t *hdac);

void HAL_DAC_IRQHandler(hal_dac_handle_t *hdac);

#if defined(USE_HAL_DAC_GET_LAST_ERRORS) && (USE_HAL_DAC_GET_LAST_ERRORS == 1)
uint32_t                HAL_DAC_GetLastErrorCodes(const hal_dac_handle_t *hdac);
#endif /* USE_HAL_DAC_GET_LAST_ERRORS */

/**
  * @}
  */

/** @addtogroup DAC_Exported_Functions_Group6
  * @{
  */
/* User Data API functions ***************************************/
#if defined(USE_HAL_DAC_USER_DATA) && (USE_HAL_DAC_USER_DATA == 1)
void HAL_DAC_SetUserData(hal_dac_handle_t *hdac, const void *p_user_data);

const void *HAL_DAC_GetUserData(const hal_dac_handle_t *hdac);
#endif /* USE_HAL_DAC_USER_DATA */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* DAC1 || DAC2 || DAC5 || DAC6 || DAC7 || DAC8 || DAC9 || DAC10 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G5XX_HAL_DAC_H */
