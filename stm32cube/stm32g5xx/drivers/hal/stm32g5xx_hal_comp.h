/**
  ******************************************************************************
  * @file    stm32g5xx_hal_comp.h
  * @brief   Header file of COMP HAL module.
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
#ifndef STM32G5XX_HAL_COMP_H
#define STM32G5XX_HAL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_comp.h"
#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
#include "stm32g5xx_ll_exti.h"
#endif /* USE_HAL_COMP_EXTI */

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

#if defined (COMP1) || defined (COMP2) || defined (COMP3) || defined (COMP4) || defined (COMP5) || defined (COMP6) \
|| defined (COMP7) || defined (COMP8)

/** @defgroup COMP COMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup  COMP_Exported_Types HAL COMP Types
  * @{
  */

/**
  * @brief HAL COMP instance
  */
typedef enum
{
  HAL_COMP1 = COMP1_BASE,
  HAL_COMP2 = COMP2_BASE,
  HAL_COMP3 = COMP3_BASE,
  HAL_COMP4 = COMP4_BASE,
  HAL_COMP5 = COMP5_BASE,
  HAL_COMP6 = COMP6_BASE,
  HAL_COMP7 = COMP7_BASE,
  HAL_COMP8 = COMP8_BASE,
} hal_comp_t;

/**
  * @brief COMP Global state
  */
typedef enum
{
  HAL_COMP_STATE_RESET                  = 0UL,              /*!< HAL Comparator handle not yet initialized */
  HAL_COMP_STATE_INIT                   = (1UL << 31U),     /*!< HAL Comparator handle initialized but comparator
                                        not yet configured */
  HAL_COMP_STATE_IDLE                   = (1UL << 30U),     /*!< Comparator configured */
  HAL_COMP_STATE_ACTIVE                 = (1UL << 29U),     /*!< Comparator operating */
  HAL_COMP_STATE_LINKED                 = (1UL << 28U),     /*!< HAL Comparator handle linked to other
                                        comparator handle */
#if defined(COMP_WINDOW_MODE_SUPPORT)
#if defined(USE_HAL_COMP_WINDOW_MODE) && (USE_HAL_COMP_WINDOW_MODE == 1)
  HAL_COMP_STATE_WINDOW_IDLE            = (1UL << 27U),     /*!< Comparator configured in window mode (with other
                                        comparator handle) */
  HAL_COMP_STATE_WINDOW_ACTIVE          = (1UL << 26U),     /*!< Comparator operating in window mode (with other
                                        comparator handle) */
#endif /* USE_HAL_COMP_WINDOW_MODE */
#endif /* COMP_WINDOW_MODE_SUPPORT */
} hal_comp_state_t;

/**
  * @brief HAL COMP input plus.
  * @note     Inputs connected to another comparator instance for window mode are managed by window mode functions.
  */
typedef enum
{
  HAL_COMP_INPUT_PLUS_IO1               = LL_COMP_INPUT_PLUS_IO1, /*!< Comparator input plus connected to IO1
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP1") */
  HAL_COMP_INPUT_PLUS_IO2               = LL_COMP_INPUT_PLUS_IO2, /*!< Comparator input plus connected to IO2
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP2") */
  HAL_COMP_INPUT_PLUS_OPAMP1_OUT        = LL_COMP_INPUT_PLUS_OPAMP1_OUT, /*!< Comparator input plus connected to
                                        OPAMP1 output (specific to COMP instances: COMP1, COMP2) */
  HAL_COMP_INPUT_PLUS_OPAMP2_OUT        = LL_COMP_INPUT_PLUS_OPAMP2_OUT, /*!< Comparator input plus connected to
                                        OPAMP2 output (specific to COMP instances: COMP3, COMP4) */
  HAL_COMP_INPUT_PLUS_OPAMP3_OUT        = LL_COMP_INPUT_PLUS_OPAMP3_OUT  /*!< Comparator input plus connected to
                                        OPAMP3 output (specific to COMP instances: COMP5, COMP6) */
} hal_comp_input_plus_t;

/**
  * @brief HAL COMP input minus
  */
typedef enum
{
  HAL_COMP_INPUT_MINUS_VREFINT          = LL_COMP_INPUT_MINUS_VREFINT,    /*!< Comparator input minus connected to
                                        VrefInt (for VrefInt voltage value, refer to datasheet) */
  HAL_COMP_INPUT_MINUS_1_4VREFINT       = LL_COMP_INPUT_MINUS_1_4VREFINT, /*!< Comparator input minus connected to
                                        1/4 VrefInt (for VrefInt voltage value, refer to datasheet) */
  HAL_COMP_INPUT_MINUS_1_2VREFINT       = LL_COMP_INPUT_MINUS_1_2VREFINT, /*!< Comparator input minus connected to
                                        1/2 VrefInt (for VrefInt voltage value, refer to datasheet) */
  HAL_COMP_INPUT_MINUS_3_4VREFINT       = LL_COMP_INPUT_MINUS_3_4VREFINT, /*!< Comparator input minus connected to
                                        3/4 VrefInt (for VrefInt voltage value, refer to datasheet) */
  HAL_COMP_INPUT_MINUS_IO1              = LL_COMP_INPUT_MINUS_IO1, /*!< Comparator input minus connected to IO1
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INM1") */
  HAL_COMP_INPUT_MINUS_IO2              = LL_COMP_INPUT_MINUS_IO2, /*!< Comparator input minus connected to IO2
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INM2") */
  HAL_COMP_INPUT_MINUS_DAC1_CH1         = LL_COMP_INPUT_MINUS_DAC1_CH1, /*!< Comparator input minus connected
                                        to DAC1 channel 1 (specific to COMP instances: COMP1, COMP3, COMP4) */
  HAL_COMP_INPUT_MINUS_DAC2_CH1         = LL_COMP_INPUT_MINUS_DAC2_CH1, /*!< Comparator input minus connected
                                        to DAC2 channel 1 (specific to COMP instances: COMP2, COMP5) */
  HAL_COMP_INPUT_MINUS_DAC5_CH1         = LL_COMP_INPUT_MINUS_DAC5_CH1, /*!< Comparator input minus connected
                                        to DAC5 channel 1 (specific to COMP instances: COMP5, COMP8) */
  HAL_COMP_INPUT_MINUS_DAC6_CH1         = LL_COMP_INPUT_MINUS_DAC6_CH1, /*!< Comparator input minus connected
                                        to DAC6 channel 1 (specific to COMP instances: COMP6, COMP7) */
  HAL_COMP_INPUT_MINUS_DAC7_CH1         = LL_COMP_INPUT_MINUS_DAC7_CH1, /*!< Comparator input minus connected
                                        to DAC7 channel 1 (specific to COMP instances: COMP7) */
  HAL_COMP_INPUT_MINUS_DAC8_CH1         = LL_COMP_INPUT_MINUS_DAC8_CH1, /*!< Comparator input minus connected
                                        to DAC8 channel 1 (specific to COMP instances: COMP1, COMP6, COMP8) */
  HAL_COMP_INPUT_MINUS_DAC9_CH1         = LL_COMP_INPUT_MINUS_DAC9_CH1, /*!< Comparator input minus connected
                                        to DAC9 channel 1 (specific to COMP instances: COMP2, COMP3) */
  HAL_COMP_INPUT_MINUS_DAC10_CH1        = LL_COMP_INPUT_MINUS_DAC10_CH1, /*!< Comparator input minus connected
                                        to DAC10 channel 1 (specific to COMP instances: COMP4, COMP5) */
  HAL_COMP_INPUT_MINUS_COMP_PAIR        = LL_COMP_INPUT_MINUS_COMP_PAIR /*!< Comparator input minus connected
                                        to the other comparator instance input minus of the common pair
                                        (for comparator common instances, refer to reference manual
                                        or helper macro LL_COMP_COMMON_INSTANCE).
                                        This connection can be used to mutualize a connection to GPIO. */
} hal_comp_input_minus_t;

/**
  * @brief HAL COMP input hysteresis.
  * @note  Hysteresis applied to input plus, subtracted to input voltage value.
  * @note  For the electrical characteristics of comparator hysteresis (voltage amplitude),
  *        refer to device datasheet.
  */
typedef enum
{
  HAL_COMP_INPUT_HYSTERESIS_NONE        = LL_COMP_HYSTERESIS_NONE, /*!< No hysteresis */
  HAL_COMP_INPUT_HYSTERESIS_10MV        = LL_COMP_HYSTERESIS_10MV, /*!< Hysteresis level 10mV */
  HAL_COMP_INPUT_HYSTERESIS_20MV        = LL_COMP_HYSTERESIS_20MV, /*!< Hysteresis level 20mV */
  HAL_COMP_INPUT_HYSTERESIS_30MV        = LL_COMP_HYSTERESIS_30MV, /*!< Hysteresis level 30mV */
  HAL_COMP_INPUT_HYSTERESIS_40MV        = LL_COMP_HYSTERESIS_40MV, /*!< Hysteresis level 40mV */
  HAL_COMP_INPUT_HYSTERESIS_50MV        = LL_COMP_HYSTERESIS_50MV, /*!< Hysteresis level 50mV */
  HAL_COMP_INPUT_HYSTERESIS_60MV        = LL_COMP_HYSTERESIS_60MV, /*!< Hysteresis level 60mV */
  HAL_COMP_INPUT_HYSTERESIS_70MV        = LL_COMP_HYSTERESIS_70MV  /*!< Hysteresis level 70mV */
} hal_comp_input_hysteresis_t;

/** @brief COMP_HAL_EC_FILTERING_ANALOG Comparator filtering - Analog filter (deglitcher).
  * @note  Deglitcher increases propagation delay of the comparator with few nanoseconds (refer to device datasheet),
  *        reducing potential output oscillations. It can be combined with comparator input hysteresis.
  */
typedef enum
{
  HAL_COMP_FILT_ANA_DISABLE             = LL_COMP_FILT_ANA_DISABLE, /*!< Comparator analog filtering (deglitcher)
                                        disable */
  HAL_COMP_FILT_ANA_ENABLE              = LL_COMP_FILT_ANA_ENABLE /*!< Comparator analog filtering (deglitcher)
                                        enable */
} hal_comp_filtering_analog_t;

/** @brief COMP_LL_EC_FILTERING_DIGITAL Comparator filtering - Digital filter.
  * @note  Digital filter can filter low frequency noise on comparator inputs, based on a clock and count number
  *        of successive samples with stable state.
  * @note  Clock frequency used for digital filtering can be retrieved using function @ref HAL_COMP_GetClockFreq()
  */
typedef enum
{
  HAL_COMP_FILT_DIG_DISABLE             = LL_COMP_FILT_DIG_DISABLE, /*!< Comparator digital filtering disable */
  HAL_COMP_FILT_DIG_DIV1_SMP2           = LL_COMP_FILT_DIG_DIV1_SMP2, /*!< Comparator
                                        digital filtering: kernel clock prescaler 1, samples with stable state: 2. */
  HAL_COMP_FILT_DIG_DIV1_SMP4           = LL_COMP_FILT_DIG_DIV1_SMP4, /*!< Comparator
                                        digital filtering: kernel clock prescaler 1, samples with stable state: 4. */
  HAL_COMP_FILT_DIG_DIV1_SMP8           = LL_COMP_FILT_DIG_DIV1_SMP8, /*!< Comparator
                                        digital filtering: kernel clock prescaler 1, samples with stable state: 8. */

  HAL_COMP_FILT_DIG_DIV2_SMP2           = LL_COMP_FILT_DIG_DIV2_SMP2, /*!< Comparator
                                        digital filtering: kernel clock prescaler 2, samples with stable state: 2. */
  HAL_COMP_FILT_DIG_DIV2_SMP4           = LL_COMP_FILT_DIG_DIV2_SMP4, /*!< Comparator
                                        digital filtering: kernel clock prescaler 2, samples with stable state: 4. */
  HAL_COMP_FILT_DIG_DIV2_SMP6           = LL_COMP_FILT_DIG_DIV2_SMP6, /*!< Comparator
                                        digital filtering: kernel clock prescaler 2, samples with stable state: 6. */
  HAL_COMP_FILT_DIG_DIV2_SMP8           = LL_COMP_FILT_DIG_DIV2_SMP8, /*!< Comparator
                                        digital filtering: kernel clock prescaler 2, samples with stable state: 8. */

  HAL_COMP_FILT_DIG_DIV4_SMP2           = LL_COMP_FILT_DIG_DIV4_SMP2, /*!< Comparator
                                        digital filtering: kernel clock prescaler 4, samples with stable state: 2. */
  HAL_COMP_FILT_DIG_DIV4_SMP4           = LL_COMP_FILT_DIG_DIV4_SMP4, /*!< Comparator
                                        digital filtering: kernel clock prescaler 4, samples with stable state: 4. */
  HAL_COMP_FILT_DIG_DIV4_SMP6           = LL_COMP_FILT_DIG_DIV4_SMP6, /*!< Comparator
                                        digital filtering: kernel clock prescaler 4, samples with stable state: 6. */
  HAL_COMP_FILT_DIG_DIV4_SMP8           = LL_COMP_FILT_DIG_DIV4_SMP8, /*!< Comparator
                                        digital filtering: kernel clock prescaler 4, samples with stable state: 8. */

  HAL_COMP_FILT_DIG_DIV8_SMP2           = LL_COMP_FILT_DIG_DIV8_SMP2, /*!< Comparator
                                        digital filtering: kernel clock prescaler 8, samples with stable state: 2. */
  HAL_COMP_FILT_DIG_DIV8_SMP4           = LL_COMP_FILT_DIG_DIV8_SMP4, /*!< Comparator
                                        digital filtering: kernel clock prescaler 8, samples with stable state: 4. */
  HAL_COMP_FILT_DIG_DIV8_SMP6           = LL_COMP_FILT_DIG_DIV8_SMP6, /*!< Comparator
                                        digital filtering: kernel clock prescaler 8, samples with stable state: 6. */
  HAL_COMP_FILT_DIG_DIV8_SMP8           = LL_COMP_FILT_DIG_DIV8_SMP8, /*!< Comparator
                                        digital filtering: kernel clock prescaler 8, samples with stable state: 8. */

  HAL_COMP_FILT_DIG_DIV16_SMP5          = LL_COMP_FILT_DIG_DIV16_SMP5, /*!< Comparator
                                        digital filtering: kernel clock prescaler 16, samples with stable state: 5. */
  HAL_COMP_FILT_DIG_DIV16_SMP6          = LL_COMP_FILT_DIG_DIV16_SMP6, /*!< Comparator
                                        digital filtering: kernel clock prescaler 16, samples with stable state: 6. */
  HAL_COMP_FILT_DIG_DIV16_SMP8          = LL_COMP_FILT_DIG_DIV16_SMP8, /*!< Comparator
                                        digital filtering: kernel clock prescaler 16, samples with stable state: 8. */

  HAL_COMP_FILT_DIG_DIV32_SMP5          = LL_COMP_FILT_DIG_DIV32_SMP5, /*!< Comparator
                                        digital filtering: kernel clock prescaler 32, samples with stable state: 5. */
  HAL_COMP_FILT_DIG_DIV32_SMP6          = LL_COMP_FILT_DIG_DIV32_SMP6, /*!< Comparator
                                        digital filtering: kernel clock prescaler 32, samples with stable state: 6. */
  HAL_COMP_FILT_DIG_DIV32_SMP8          = LL_COMP_FILT_DIG_DIV32_SMP8, /*!< Comparator
                                        digital filtering: kernel clock prescaler 32, samples with stable state: 8. */

  HAL_COMP_FILT_DIG_DIV64_SMP5         = LL_COMP_FILT_DIG_DIV64_SMP5, /*!< Comparator
                                        digital filtering: kernel clock prescaler 64, samples with stable state: 5. */
  HAL_COMP_FILT_DIG_DIV64_SMP6         = LL_COMP_FILT_DIG_DIV64_SMP6, /*!< Comparator
                                        digital filtering: kernel clock prescaler 64, samples with stable state: 6. */
  HAL_COMP_FILT_DIG_DIV64_SMP8         = LL_COMP_FILT_DIG_DIV64_SMP8, /*!< Comparator
                                        digital filtering: kernel clock prescaler 64, samples with stable state: 8. */

  HAL_COMP_FILT_DIG_DIV128_SMP5         = LL_COMP_FILT_DIG_DIV128_SMP5, /*!< Comparator
                                        digital filtering: kernel clock prescaler 128, samples with stable state: 5. */
  HAL_COMP_FILT_DIG_DIV128_SMP6         = LL_COMP_FILT_DIG_DIV128_SMP6, /*!< Comparator
                                        digital filtering: kernel clock prescaler 128, samples with stable state: 6. */
  HAL_COMP_FILT_DIG_DIV128_SMP8         = LL_COMP_FILT_DIG_DIV128_SMP8, /*!< Comparator
                                        digital filtering: kernel clock prescaler 128, samples with stable state: 8. */

  HAL_COMP_FILT_DIG_DIV256_SMP5         = LL_COMP_FILT_DIG_DIV256_SMP5, /*!< Comparator
                                        digital filtering: kernel clock prescaler 256, samples with stable state: 5. */
  HAL_COMP_FILT_DIG_DIV256_SMP6         = LL_COMP_FILT_DIG_DIV256_SMP6, /*!< Comparator
                                        digital filtering: kernel clock prescaler 256, samples with stable state: 6. */
  HAL_COMP_FILT_DIG_DIV256_SMP8         = LL_COMP_FILT_DIG_DIV256_SMP8 /*!< Comparator
                                        digital filtering: kernel clock prescaler 256, samples with stable state: 8. */
} hal_comp_filtering_digital_t;

/**
  * @brief HAL COMP output polarity
  */
typedef enum
{
  HAL_COMP_OUTPUT_POLARITY_NONINVERTED  = LL_COMP_OUTPUTPOL_NONINVERTED, /*!< Comparator output polarity not inverted:
                                        comparator output at high level when input voltages: plus higher than minus */
  HAL_COMP_OUTPUT_POLARITY_INVERTED     = LL_COMP_OUTPUTPOL_INVERTED     /*!< Comparator output polarity not inverted:
                                        comparator output at low level when input voltages: plus higher than minus */
} hal_comp_output_polarity_t;

/**
  * @brief HAL COMP output blanking
  */
typedef enum
{
  HAL_COMP_OUTPUT_BLANK_NONE            = 0x00000000UL, /*!< Comp. output without blanking */
  HAL_COMP_OUTPUT_BLANK_TIM1_OC5        = LL_COMP_BLANKINGSRC_TIM1_OC5, /*!< Comp. output blanking source TIM1 OC5,
                                        common to all COMP instances. */
  HAL_COMP_OUTPUT_BLANK_TIM1_OC6        = LL_COMP_BLANKINGSRC_TIM1_OC6, /*!< Comp. output blanking source TIM1 OC7,
                                        specific to COMP instance: COMP2, COMP3, COMP5, COMP7. */
  HAL_COMP_OUTPUT_BLANK_TIM1_OC7        = LL_COMP_BLANKINGSRC_TIM1_OC7, /*!< Comp. output blanking source TIM1 OC7,
                                        specific to COMP instance: COMP1, COMP2, COMP6, COMP8. */
  HAL_COMP_OUTPUT_BLANK_TIM2_OC3        = LL_COMP_BLANKINGSRC_TIM2_OC3, /*!< Comp. output blanking source TIM2 OC3,
                                        specific to COMP instance: COMP1, COMP2, COMP5. */
  HAL_COMP_OUTPUT_BLANK_TIM2_OC4        = LL_COMP_BLANKINGSRC_TIM2_OC4, /*!< Comp. output blanking source TIM2 OC4,
                                        specific to COMP instance: COMP3, COMP6. */
  HAL_COMP_OUTPUT_BLANK_TIM3_OC3        = LL_COMP_BLANKINGSRC_TIM3_OC3, /*!< Comp. output blanking source TIM3 OC3,
                                        specific to COMP instance: COMP1, COMP2, COMP3, COMP5, COMP7, COMP8. */
  HAL_COMP_OUTPUT_BLANK_TIM3_OC4        = LL_COMP_BLANKINGSRC_TIM3_OC4, /*!< Comp. output blanking source TIM3 OC4,
                                        specific to COMP instance: COMP4. */
  HAL_COMP_OUTPUT_BLANK_TIM4_OC3        = LL_COMP_BLANKINGSRC_TIM4_OC3, /*!< Comp. output blanking source TIM4 OC3,
                                        common to all COMP instances. */
  HAL_COMP_OUTPUT_BLANK_TIM8_OC5        = LL_COMP_BLANKINGSRC_TIM8_OC5, /*!< Comp. output blanking source TIM8 OC5,
                                        common to all COMP instances. */
  HAL_COMP_OUTPUT_BLANK_TIM8_OC6        = LL_COMP_BLANKINGSRC_TIM8_OC6, /*!< Comp. output blanking source TIM8 OC7,
                                        specific to COMP instance: COMP2, COMP4, COMP5, COMP7. */
  HAL_COMP_OUTPUT_BLANK_TIM8_OC7        = LL_COMP_BLANKINGSRC_TIM8_OC7, /*!< Comp. output blanking source TIM8 OC7,
                                        specific to COMP instance: COMP1, COMP3, COMP6, COMP8. */
  HAL_COMP_OUTPUT_BLANK_TIM12_OC1       = LL_COMP_BLANKINGSRC_TIM12_OC1, /*!< Comp. output blanking source TIM12 OC1,
                                        common to all COMP instances. */
  HAL_COMP_OUTPUT_BLANK_TIM20_OC5       = LL_COMP_BLANKINGSRC_TIM20_OC5, /*!< Comp. output blanking source TIM20 OC5,
                                        common to all COMP instances. */
  HAL_COMP_OUTPUT_BLANK_TIM20_OC6       = LL_COMP_BLANKINGSRC_TIM20_OC6, /*!< Comp. output blanking source TIM20 OC6,
                                        specific to COMP instance: COMP2, COMP4, COMP5, COMP7. */
  HAL_COMP_OUTPUT_BLANK_TIM20_OC7       = LL_COMP_BLANKINGSRC_TIM20_OC7, /*!< Comp. output blanking source TIM20 OC7,
                                        specific to COMP instance: COMP1, COMP3, COMP6, COMP8. */
  HAL_COMP_OUTPUT_BLANK_TIM15_OC1       = LL_COMP_BLANKINGSRC_TIM15_OC1, /*!< Comp. output blanking source TIM15 OC1,
                                        common to all COMP instances. */
  HAL_COMP_OUTPUT_BLANK_TIM15_OC2       = LL_COMP_BLANKINGSRC_TIM15_OC2, /*!< Comp. output blanking source TIM15 OC2,
                                        common to all COMP instances. */
  HAL_COMP_OUTPUT_BLANK_TIM9_OC1        = LL_COMP_BLANKINGSRC_TIM9_OC1, /*!< Comp. output blanking source TIM9 OC1,
                                        specific to COMP instance: COMP1. */
  HAL_COMP_OUTPUT_BLANK_PLAY1_OUT6      = LL_COMP_BLANKINGSRC_PLAY1_OUT6, /*!< Comp. output blanking source
                                        PLAY1 out 6, specific to COMP instance: COMP1. */
  HAL_COMP_OUTPUT_BLANK_PLAY1_OUT7      = LL_COMP_BLANKINGSRC_PLAY1_OUT7, /*!< Comp. output blanking source
                                        PLAY1 out 7, specific to COMP instance: COMP2. */
  HAL_COMP_OUTPUT_BLANK_PLAY1_OUT8      = LL_COMP_BLANKINGSRC_PLAY1_OUT8, /*!< Comp. output blanking source
                                        PLAY1 out 8, specific to COMP instance: COMP3. */
  HAL_COMP_OUTPUT_BLANK_PLAY1_OUT9      = LL_COMP_BLANKINGSRC_PLAY1_OUT9, /*!< Comp. output blanking source
                                        PLAY1 out 9, specific to COMP instance: COMP4. */
  HAL_COMP_OUTPUT_BLANK_PLAY1_OUT10     = LL_COMP_BLANKINGSRC_PLAY1_OUT10, /*!< Comp. output blanking source
                                        PLAY1 out 10, specific to COMP instance: COMP5. */
  HAL_COMP_OUTPUT_BLANK_PLAY1_OUT11     = LL_COMP_BLANKINGSRC_PLAY1_OUT11, /*!< Comp. output blanking source
                                        PLAY1 out 11, specific to COMP instance: COMP6. */
  HAL_COMP_OUTPUT_BLANK_PLAY1_OUT12     = LL_COMP_BLANKINGSRC_PLAY1_OUT12, /*!< Comp. output blanking source
                                        PLAY1 out 12, specific to COMP instance: COMP7. */
  HAL_COMP_OUTPUT_BLANK_PLAY1_OUT13     = LL_COMP_BLANKINGSRC_PLAY1_OUT13, /*!< Comp. output blanking source
                                        PLAY1 out 13, specific to COMP instance: COMP8. */
} hal_comp_output_blank_t;

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
/**
  * @brief HAL COMP output trigger to system.
  * @note  When output set to generate a trigger, impact depends on programming model used:
  *        - with @ref HAL_COMP_Start():    generates a system wake-up event and a CPU event
  *        - with @ref HAL_COMP_Start_IT(): generates a system wake-up event and a CPU interrupt
  */
typedef enum
{
  HAL_COMP_OUTPUT_TRIG_NONE             = LL_EXTI_TRIGGER_NONE, /*!< Comparator output does not generate a trigger */
  HAL_COMP_OUTPUT_TRIG_RISING           = LL_EXTI_TRIGGER_RISING, /*!< Comparator output generates a trigger
                                        event to system on rising edge */
  HAL_COMP_OUTPUT_TRIG_FALLING          = LL_EXTI_TRIGGER_FALLING, /*!< Comparator output generates a trigger
                                        event to system on falling edge */
  HAL_COMP_OUTPUT_TRIG_RISING_FALLING   = LL_EXTI_TRIGGER_RISING_FALLING  /*!< Comparator output generates a trigger
                                        event to system on both rising and falling edges */
} hal_comp_output_trigger_t;
#endif /* USE_HAL_COMP_EXTI */

#if defined(COMP_WINDOW_MODE_SUPPORT)
#if defined(USE_HAL_COMP_WINDOW_MODE) && (USE_HAL_COMP_WINDOW_MODE == 1)
/**
  * @brief HAL COMP window output
  */
typedef enum
{
  HAL_COMP_WINDOW_OUTPUT_INDEPT         = LL_COMP_WINDOW_OUTPUT_INDEPT, /*!< Comparators window output default mode:
                                        both comparators output are independent, indicating each their own state.
                                        Note: To know signal state versus window thresholds, read each comparator
                                              output and perform a logical "exclusive or" operation. */
  HAL_COMP_WINDOW_OUTPUT_XOR            = LL_COMP_WINDOW_OUTPUT_XOR_BOTH, /*!< Comparators window output synthesized on
                                        a single comparator output: comparator no more indicating its own state,
                                        but window state (XOR: logical "exclusive or"). Logical high means monitored
                                        signal is within comparators window thresholds.
                                        Comparator instance selected corresponds to handle assigned as upper threshold
                                        in @ref HAL_COMP_WINDOW_SetHandle().
                                        Note: impacts only comparator output signal level (propagated to GPIO,
                                              EXTI lines, timers, ...), does not impact output digital state
                                              (hal_comp_output_level_t) always reflecting each comparator
                                              output state. */
} hal_comp_window_output_mode_t;

/**
  * @brief HAL COMP window output level.
  * @note  Comparator output level depends on inputs voltages and output polarity.
  */
typedef enum
{
  HAL_COMP_WINDOW_OUTPUT_LEVEL_BELOW    = (0x00000000UL), /*!< Comparators window output below window low threshold */
  HAL_COMP_WINDOW_OUTPUT_LEVEL_WITHIN   = (0x00000001UL), /*!< Comparators window output within window thresholds */
  HAL_COMP_WINDOW_OUTPUT_LEVEL_ABOVE    = (0x00000002UL), /*!< Comparators window output above window high threshold */
} hal_comp_window_output_level_t;

/**
  * @brief HAL COMP window instances assignment
  */
typedef enum
{
  HAL_COMP_WINDOW_INST_NONE             = (0x00000000UL), /*!< Comparators window instance not assigned */
  HAL_COMP_WINDOW_INST_UPPER            = (0x00000001UL), /*!< Comparators window instance assignment upper */
  HAL_COMP_WINDOW_INST_LOWER            = (0x00000002UL)  /*!< Comparators window instance assignment lower */
} hal_comp_window_instance_t;

#endif /* USE_HAL_COMP_WINDOW_MODE */
#endif /* COMP_WINDOW_MODE_SUPPORT */

/**
  * @brief HAL COMP lock state
  */
typedef enum
{
  HAL_COMP_LOCK_DISABLED                = (0x00000000UL), /*!< Comparator not locked */
  HAL_COMP_LOCK_ENABLED                 = (0x00000001UL)  /*!< Comparator locked */
} hal_comp_lock_status_t;

/**
  * @brief HAL COMP output level.
  * @note  Comparator output level depends on inputs voltages and output polarity.
  */
typedef enum
{
  HAL_COMP_OUTPUT_LEVEL_LOW             = LL_COMP_OUTPUT_LEVEL_LOW, /*!< Comparator output logical level low */
  HAL_COMP_OUTPUT_LEVEL_HIGH            = LL_COMP_OUTPUT_LEVEL_HIGH /*!< Comparator output logical level high */
} hal_comp_output_level_t;

/**
  * @brief COMP filtering configuration
  */
typedef struct
{
  hal_comp_filtering_analog_t           filtering_analog;  /*!< Comparator analog filter (deglitcher) */
  hal_comp_filtering_digital_t          filtering_digital; /*!< Comparator digital filter
                                        Note: Digital filter can filter low frequency noise on comparator inputs, based
                                              on a clock and count number of successive samples with stable state.
                                        Note: Clock frequency used for digital filtering can be retrieved
                                              using function @ref HAL_COMP_GetClockFreq(). */
} hal_comp_filtering_t;

/**
  * @brief COMP Global configuration
  */
typedef struct
{
  hal_comp_input_plus_t                 input_plus;         /*!< Comparator input plus */
  hal_comp_input_minus_t                input_minus;        /*!< Comparator input minus */
  hal_comp_input_hysteresis_t           input_hysteresis;   /*!< Comparator input hysteresis */
  hal_comp_output_polarity_t            output_polarity;    /*!< Comparator output polarity */
#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
  hal_comp_output_trigger_t             output_trigger;     /*!< Comparator output trigger to system (wake up, CPU) */
#endif /* USE_HAL_COMP_EXTI */
} hal_comp_config_t;

#if defined(COMP_WINDOW_MODE_SUPPORT)
#if defined(USE_HAL_COMP_WINDOW_MODE) && (USE_HAL_COMP_WINDOW_MODE == 1)
/**
  * @brief COMP window mode configuration
  */
typedef struct
{
  hal_comp_input_plus_t                 input;              /*!< Window comparators input.
                                        @note This parameter corresponds to common input plus. Comparators instances
                                              pair have their input plus connected together (common input plus).
                                              The input plus used corresponds to handle used in first argument
                                              (hcomp_upper_threshold) of function @ref HAL_COMP_WINDOW_SetHandle()
                                               (input plus of the other comparator is no more accessible) */
  hal_comp_input_minus_t                upper_threshold;    /*!< Window comparators upper threshold.
                                        @note This parameter corresponds to input minus of handle used in
                                              first argument (hcomp_upper_threshold) of function
                                              @ref HAL_COMP_WINDOW_SetHandle().
                                        @note Term "upper" does not imply voltage value must
                                              be higher than the other threshold.
                                              This is an arbitrary selection to determine window
                                              output level (@ref hal_comp_window_output_level_t).*/
  hal_comp_input_minus_t                lower_threshold;    /*!< Window comparators lower threshold.
                                        @note This parameter corresponds to input minus of handle used in
                                              second argument (hcomp_lower_threshold) of function
                                              @ref HAL_COMP_WINDOW_SetHandle().
                                        @note Term "lower" does not imply voltage value must be higher than the other
                                              threshold. This is an arbitrary selection to determine window
                                              output level (@ref hal_comp_window_output_level_t).*/
  hal_comp_input_hysteresis_t           input_hysteresis;   /*!< Comparator input hysteresis */
  hal_comp_output_polarity_t            output_polarity;    /*!< Comparator output polarity */
#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
  hal_comp_output_trigger_t             output_trigger;     /*!< Comparator output trigger to system (wake up, CPU) */
#endif /* USE_HAL_COMP_EXTI */
  hal_comp_window_output_mode_t         window_output_mode; /*!< Comparator window output */
} hal_comp_window_config_t;
#endif /* USE_HAL_COMP_WINDOW_MODE */
#endif /* COMP_WINDOW_MODE_SUPPORT */

typedef struct hal_comp_handle_s hal_comp_handle_t; /*!< COMP handle type definition */

#if defined (USE_HAL_COMP_REGISTER_CALLBACKS) && (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
typedef  void (*hal_comp_cb_t)(hal_comp_handle_t *hcomp);  /*!< pointer to COMP callback functions */
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

/**
  * @brief COMP Handle Structure Definition
  */
struct hal_comp_handle_s
{
  hal_comp_t instance;                    /*!< Peripheral instance */

#if defined(COMP_WINDOW_MODE_SUPPORT)
#if defined(USE_HAL_COMP_WINDOW_MODE) && (USE_HAL_COMP_WINDOW_MODE == 1)
  hal_comp_handle_t                     *p_link_next_handle;  /*!< Pointer to another HAL COMP handle of instance
                                        belonging to the same COMP common instance (therefore, sharing common features).
                                        Used to access multiple HAL COMP handles (daisy chain: from one to another
                                        and circular).
                                        Set using function @ref HAL_COMP_WINDOW_SetHandle(). */
  hal_comp_window_instance_t            window_instance; /*!< Comparators window instance assignment */
#endif /* USE_HAL_COMP_WINDOW_MODE */
#endif /* COMP_WINDOW_MODE_SUPPORT */

  volatile hal_comp_state_t             global_state; /*!< Global state */

#if defined (USE_HAL_COMP_USER_DATA) && (USE_HAL_COMP_USER_DATA == 1)
  const void                            *p_user_data; /*!< User data pointer */
#endif /* USE_HAL_COMP_USER_DATA */

#if defined (USE_HAL_COMP_REGISTER_CALLBACKS) && (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
  hal_comp_cb_t                         p_output_trigger_cb; /*!< COMP output trigger callback */
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
  uint32_t                              exti_line; /*!< EXTI line (needed for event and IT operation)
                                        on LL driver format */
  hal_comp_output_trigger_t             output_trigger; /*!< Comparator output trigger configured */
#endif /* USE_HAL_COMP_EXTI */
};

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup COMP_Exported_Functions HAL COMP Functions
  * @{
  */

/** @defgroup COMP_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_COMP_Init(hal_comp_handle_t *hcomp, hal_comp_t instance);
void HAL_COMP_DeInit(hal_comp_handle_t *hcomp);
hal_comp_t HAL_COMP_GetInstance(const hal_comp_handle_t *hcomp);
COMP_TypeDef *HAL_COMP_GetLLInstance(const hal_comp_handle_t *hcomp);
#if defined(COMP_WINDOW_MODE_SUPPORT)
#if defined(USE_HAL_COMP_WINDOW_MODE) && (USE_HAL_COMP_WINDOW_MODE == 1)
hal_status_t HAL_COMP_WINDOW_SetHandle(hal_comp_handle_t *hcomp_upper,
                                       hal_comp_handle_t *hcomp_lower);
#endif /* USE_HAL_COMP_WINDOW_MODE */
#endif /* COMP_WINDOW_MODE_SUPPORT */
/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group2 Configuration functions
  * @{
  */
hal_status_t HAL_COMP_SetConfig(hal_comp_handle_t *hcomp, const hal_comp_config_t *p_config);
void HAL_COMP_GetConfig(const hal_comp_handle_t *hcomp, hal_comp_config_t *p_config);

hal_status_t HAL_COMP_SetInputPlus(hal_comp_handle_t *hcomp, hal_comp_input_plus_t input_plus);
hal_comp_input_plus_t HAL_COMP_GetInputPlus(const hal_comp_handle_t *hcomp);
hal_status_t HAL_COMP_SetInputMinus(hal_comp_handle_t *hcomp, hal_comp_input_minus_t input_minus);
hal_comp_input_minus_t HAL_COMP_GetInputMinus(const hal_comp_handle_t *hcomp);

hal_status_t HAL_COMP_SetFiltering(hal_comp_handle_t *hcomp, const hal_comp_filtering_t *p_filtering);
void HAL_COMP_GetFiltering(hal_comp_handle_t *hcomp, hal_comp_filtering_t *p_filtering);

hal_status_t HAL_COMP_SetOutputBlanking(hal_comp_handle_t *hcomp, hal_comp_output_blank_t output_blank);
hal_comp_output_blank_t HAL_COMP_GetOutputBlanking(hal_comp_handle_t *hcomp);

#if defined(COMP_WINDOW_MODE_SUPPORT)
#if defined(USE_HAL_COMP_WINDOW_MODE) && (USE_HAL_COMP_WINDOW_MODE == 1)
hal_status_t HAL_COMP_WINDOW_SetConfig(hal_comp_handle_t *hcomp, const hal_comp_window_config_t *p_config);
void HAL_COMP_WINDOW_GetConfig(const hal_comp_handle_t *hcomp, hal_comp_window_config_t *p_config);

hal_status_t HAL_COMP_WINDOW_SetInput(hal_comp_handle_t *hcomp, hal_comp_input_plus_t input);
hal_comp_input_plus_t HAL_COMP_WINDOW_GetInput(const hal_comp_handle_t *hcomp);
hal_status_t HAL_COMP_WINDOW_SetUpperThreshold(hal_comp_handle_t *hcomp, hal_comp_input_minus_t upper_threshold);
hal_comp_input_minus_t HAL_COMP_WINDOW_GetUpperThreshold(const hal_comp_handle_t *hcomp);
hal_status_t HAL_COMP_WINDOW_SetLowerThreshold(hal_comp_handle_t *hcomp, hal_comp_input_minus_t lower_threshold);
hal_comp_input_minus_t HAL_COMP_WINDOW_GetLowerThreshold(const hal_comp_handle_t *hcomp);

hal_status_t HAL_COMP_WINDOW_SetFiltering(hal_comp_handle_t *hcomp, const hal_comp_filtering_t *p_filtering);
void HAL_COMP_WINDOW_GetFiltering(hal_comp_handle_t *hcomp, hal_comp_filtering_t *p_filtering);

hal_status_t HAL_COMP_WINDOW_SetOutputBlanking(hal_comp_handle_t *hcomp, hal_comp_output_blank_t output_blank);
hal_comp_output_blank_t HAL_COMP_WINDOW_GetOutputBlanking(const hal_comp_handle_t *hcomp);
#endif /* USE_HAL_COMP_WINDOW_MODE */
#endif /* COMP_WINDOW_MODE_SUPPORT */
/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group3 IRQHandler and Callbacks functions
  * @{
  */
void HAL_COMP_IRQHandler(hal_comp_handle_t *hcomp);
void HAL_COMP_OutputTriggerCallback(hal_comp_handle_t *hcomp);
#if defined (USE_HAL_COMP_REGISTER_CALLBACKS) && (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
hal_status_t HAL_COMP_RegisterOutputTriggerCallback(hal_comp_handle_t *hcomp, hal_comp_cb_t p_callback);
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group4 Peripheral State, Error functions
  * @{
  */
hal_comp_state_t HAL_COMP_GetState(const hal_comp_handle_t *hcomp);
uint32_t HAL_COMP_GetClockFreq(const hal_comp_handle_t *hcomp);
/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group5 Process functions
  * @{
  */
hal_status_t HAL_COMP_Start(hal_comp_handle_t *hcomp);
hal_status_t HAL_COMP_Stop(hal_comp_handle_t *hcomp);
#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
hal_status_t HAL_COMP_Start_IT(hal_comp_handle_t *hcomp);
hal_status_t HAL_COMP_Stop_IT(hal_comp_handle_t *hcomp);
#endif /* USE_HAL_COMP_EXTI */
hal_status_t HAL_COMP_Lock(hal_comp_handle_t *hcomp);
hal_comp_lock_status_t HAL_COMP_IsLocked(hal_comp_handle_t *hcomp);
hal_comp_output_level_t HAL_COMP_GetOutputLevel(hal_comp_handle_t *hcomp);
#if defined(COMP_WINDOW_MODE_SUPPORT)
#if defined(USE_HAL_COMP_WINDOW_MODE) && (USE_HAL_COMP_WINDOW_MODE == 1)
hal_status_t HAL_COMP_WINDOW_Start(hal_comp_handle_t *hcomp);
hal_status_t HAL_COMP_WINDOW_Stop(hal_comp_handle_t *hcomp);
#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
hal_status_t HAL_COMP_WINDOW_Start_IT(hal_comp_handle_t *hcomp);
hal_status_t HAL_COMP_WINDOW_Stop_IT(hal_comp_handle_t *hcomp);
#endif /* USE_HAL_COMP_EXTI */
hal_status_t HAL_COMP_WINDOW_Lock(hal_comp_handle_t *hcomp);
hal_comp_lock_status_t HAL_COMP_WINDOW_IsLocked(hal_comp_handle_t *hcomp);
hal_comp_window_output_level_t HAL_COMP_WINDOW_GetOutputLevel(hal_comp_handle_t *hcomp);
#endif /* USE_HAL_COMP_WINDOW_MODE */
#endif /* COMP_WINDOW_MODE_SUPPORT */
/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group6 User data functions
  * @{
  */
#if defined(USE_HAL_COMP_USER_DATA) && (USE_HAL_COMP_USER_DATA == 1)
void HAL_COMP_SetUserData(hal_comp_handle_t *hcomp, const void *p_user_data);
const void *HAL_COMP_GetUserData(const hal_comp_handle_t *hcomp);
#endif /* USE_HAL_COMP_USER_DATA */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* COMP1 || COMP2 || COMP3 || COMP4 || COMP5 || COMP6 || COMP7 || COMP8 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_HAL_COMP_H */
