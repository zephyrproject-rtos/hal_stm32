/**
  **********************************************************************************************************************
  * @file    stm32g5xx_ll_adc.h
  * @brief   Header file of ADC LL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32G5XX_LL_ADC_H
#define STM32G5XX_LL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */

#if defined(ADC1) || defined(ADC2) || defined(ADC3)

/** @defgroup ADC_LL ADC
  * @{
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Constants ADC Private Constants
  * @{
  */

/* Internal mask for ADC group regular sequencer.
To select into literal LL_ADC_REG_RANK_x the relevant bits for:
- sequencer register offset
- sequencer rank bits position into the selected register */
/* Internal register offset for ADC group regular sequencer configuration (offset placed into a spare area of
literal definition) */
#define LL_ADC_SQR1_REGOFFSET           (0x00000000UL)
#define LL_ADC_SQR2_REGOFFSET           (0x00000100UL)
#define LL_ADC_SQR3_REGOFFSET           (0x00000200UL)
#define LL_ADC_SQR4_REGOFFSET           (0x00000300UL)

#define LL_ADC_REG_SQRX_REGOFFSET_MASK  (LL_ADC_SQR1_REGOFFSET\
                                         | LL_ADC_SQR2_REGOFFSET | LL_ADC_SQR3_REGOFFSET | LL_ADC_SQR4_REGOFFSET)
#define LL_ADC_SQRX_REGOFFSET_POS       (8UL) /* Position of bits ADC_SQRx_REGOFFSET
                                        in LL_ADC_REG_SQRX_REGOFFSET_MASK */
#define LL_ADC_REG_RANK_ID_SQRX_MASK    (LL_ADC_CHANNEL_ID_NB_MASK_POSBIT0)

/* Internal mask for ADC group injected sequencer.
To select into literal LL_ADC_INJ_RANK_x the relevant bits for:
- data register offset
- sequencer rank bits position into the selected register */
/* Internal register offset for ADC group injected data register (offset placed into a spare area of
literal definition) */
#define LL_ADC_JDR1_REGOFFSET           (0x00000000UL)
#define LL_ADC_JDR2_REGOFFSET           (0x00000100UL)
#define LL_ADC_JDR3_REGOFFSET           (0x00000200UL)
#define LL_ADC_JDR4_REGOFFSET           (0x00000300UL)

#define LL_ADC_INJ_JDRX_REGOFFSET_MASK  (LL_ADC_JDR1_REGOFFSET\
                                         | LL_ADC_JDR2_REGOFFSET | LL_ADC_JDR3_REGOFFSET | LL_ADC_JDR4_REGOFFSET)
#define LL_ADC_INJ_RANK_ID_JSQR_MASK    (LL_ADC_CHANNEL_ID_NB_MASK_POSBIT0)
#define LL_ADC_JDRX_REGOFFSET_POS       (8UL) /* Position of bits ADC_JDRx_REGOFFSET in
                                        LL_ADC_INJ_JDRX_REGOFFSET_MASK */

/* Internal mask for ADC group regular trigger.
To select into literal LL_ADC_REG_TRIG_x the relevant bits for:
- regular trigger source
- regular trigger edge */
#define LL_ADC_REG_TRIG_EDGE_DEFAULT    (ADC_CFGR1_EXTEN_0) /* Trigger edge set to rising edge (default setting
                                        for compatibility with some ADC on other STM32 series having this setting
                                        set by HW default value) */

/* Mask containing trigger source masks for each of possible trigger edge selection duplicated with shifts [0; 4; 8; 12]
corresponding to {SW start; ext trigger; ext trigger; ext trigger}. */
#define LL_ADC_REG_TRIG_SOURCE_MASK     (((LL_ADC_REG_TRIG_SOFTWARE & ADC_CFGR1_EXTSEL) << (4U * 0UL)) | \
                                         ((ADC_CFGR1_EXTSEL)                            << (4U * 1UL)) | \
                                         ((ADC_CFGR1_EXTSEL)                            << (4U * 2UL)) | \
                                         ((ADC_CFGR1_EXTSEL)                            << (4U * 3UL))  )

/* Mask containing trigger edge masks for each of possible trigger edge selection duplicated with shifts [0; 4; 8; 12]
corresponding to {SW start; ext trigger; ext trigger; ext trigger}. */
#define LL_ADC_REG_TRIG_EDGE_MASK       (((LL_ADC_REG_TRIG_SOFTWARE & ADC_CFGR1_EXTEN) << (4U * 0UL)) | \
                                         ((LL_ADC_REG_TRIG_EDGE_DEFAULT)               << (4U * 1UL)) | \
                                         ((LL_ADC_REG_TRIG_EDGE_DEFAULT)               << (4U * 2UL)) | \
                                         ((LL_ADC_REG_TRIG_EDGE_DEFAULT)               << (4U * 3UL))  )

/* Internal mask for ADC group injected trigger:
To select into literal LL_ADC_INJ_TRIG_x the relevant bits for:
- injected trigger source
- injected trigger edge */
#define LL_ADC_INJ_TRIG_EDGE_DEFAULT    (ADC_JSQR_JEXTEN_0) /* Trigger edge set to rising edge (default setting for
                                        compatibility with some ADC on other STM32 series having this setting
                                        set by HW default value) */

/* Mask containing trigger source masks for each of possible trigger edge selection duplicated with shifts [0; 4; 8; 12]
corresponding to {SW start; ext trigger; ext trigger; ext trigger}. */
#define LL_ADC_INJ_TRIG_SOURCE_MASK     (((LL_ADC_INJ_TRIG_SOFTWARE & ADC_JSQR_JEXTSEL) << (4U * 0UL)) | \
                                         ((ADC_JSQR_JEXTSEL)                            << (4U * 1UL)) | \
                                         ((ADC_JSQR_JEXTSEL)                            << (4U * 2UL)) | \
                                         ((ADC_JSQR_JEXTSEL)                            << (4U * 3UL))  )

/* Mask containing trigger edge masks for each of possible trigger edge selection duplicated with shifts [0; 4; 8; 12]
corresponding to {SW start; ext trigger; ext trigger; ext trigger}. */
#define LL_ADC_INJ_TRIG_EDGE_MASK       (((LL_ADC_INJ_TRIG_SOFTWARE & ADC_JSQR_JEXTEN) << (4U * 0UL)) | \
                                         ((LL_ADC_INJ_TRIG_EDGE_DEFAULT)               << (4U * 1UL)) | \
                                         ((LL_ADC_INJ_TRIG_EDGE_DEFAULT)               << (4U * 2UL)) | \
                                         ((LL_ADC_INJ_TRIG_EDGE_DEFAULT)               << (4U * 3UL))  )

#define LL_ADC_TRIG_NA 0xFFU /* ADC trigger source not available */

/* Internal mask for ADC conversion trigger specific (depending on instance or option register config) */
#if defined(ADC3)
#define LL_ADC_TRIG_OP_NB_POS           (5U) /* Marker of trigger source depending on option register config:
                                        bitfield position */
#define LL_ADC_TRIG_OP_NB_MASK          (0x3UL << LL_ADC_TRIG_OP_NB_POS) /* Marker of trigger source depending
                                        on option register config: bitfield mask. Covering value in range [3; 0].
                                        Note: mask not inducing LSB corresponding to LL_ADC_TRIG_OP_NB_POS
                                              because not in range of option bits
                                              and used by LL_ADC_TRIG_OP_STATE_MASK. */
#define LL_ADC_TRIG_OP_NB_ADD_REG       (3U) /* Value to be added to option bit number: option bits for trigger source
                                        in range [7; 4] (value 3 excluded to not have bitfield equal to 0) */
#define LL_ADC_TRIG_OP_NB_ADD_INJ       (4U) /* Value to be added to option bit number: option bits for trigger source
                                        in range [7; 5] (value 4 excluded to not have bitfield equal to 0) */
#define LL_ADC_TRIG_OP_STATE_POS        (7UL) /* Marker of trigger source depending on option register config:
                                        bitfield position.
                                        Note: overlap with LL_ADC_TRIG_OP_NB_MASK due to LSB unused. */
#else /* Implementation without look up table */
#define LL_ADC_TRIG_OP_NB_POS           (24U) /* Marker of trigger source depending on option register config:
                                        bitfield position */
#define LL_ADC_TRIG_OP_NB_MASK          (0x0FUL << LL_ADC_TRIG_OP_NB_POS) /* Marker of trigger source depending
                                        on option register config: bitfield mask */
#define LL_ADC_TRIG_OP_NB_ADD_REG       (0U) /* Value to be added to option bit number */
#define LL_ADC_TRIG_OP_NB_ADD_INJ       (0U) /* Value to be added to option bit number */
#define LL_ADC_TRIG_OP_STATE_POS        (9UL) /* Marker of trigger source depending on option register config:
                                        bitfield position */
#endif /* ADC3 */
#define LL_ADC_TRIG_OP_STATE_0          (0UL << LL_ADC_TRIG_OP_STATE_POS) /* Marker of trigger source depending
                                        on option register config: bit reset */
#define LL_ADC_TRIG_OP_STATE_1          (1UL << LL_ADC_TRIG_OP_STATE_POS) /* Marker of trigger source depending
                                        on option register config: bit set */
#define LL_ADC_TRIG_OP_STATE_MASK       (LL_ADC_TRIG_OP_STATE_1 | LL_ADC_TRIG_OP_STATE_0) /* Marker of trigger source
                                        depending on option register config: bitfield mask */

#define LL_ADC_TRIG_OP4_RESET           (((4UL - LL_ADC_TRIG_OP_NB_ADD_REG) << LL_ADC_TRIG_OP_NB_POS) \
                                         | LL_ADC_TRIG_OP_STATE_0) /* Marker of trigger source specific to
                                         option bit 4, bit reset (for ADC group regular) */
#define LL_ADC_TRIG_OP4_SET             (((4UL - LL_ADC_TRIG_OP_NB_ADD_REG) << LL_ADC_TRIG_OP_NB_POS) \
                                         | LL_ADC_TRIG_OP_STATE_1) /* Marker of trigger source specific to
                                         option bit 4, bit set (for ADC group regular) */
#define LL_ADC_TRIG_OP5_RESET           (((5UL - LL_ADC_TRIG_OP_NB_ADD_REG) << LL_ADC_TRIG_OP_NB_POS) \
                                         | LL_ADC_TRIG_OP_STATE_0) /* Marker of trigger source specific to
                                         option bit 5, bit reset (for ADC group regular) */
#define LL_ADC_TRIG_OP5_SET             (((5UL - LL_ADC_TRIG_OP_NB_ADD_REG) << LL_ADC_TRIG_OP_NB_POS) \
                                         | LL_ADC_TRIG_OP_STATE_1) /* Marker of trigger source specific to
                                         option bit 5, bit set (for ADC group regular) */
#define LL_ADC_TRIG_OP6_RESET           (((6UL - LL_ADC_TRIG_OP_NB_ADD_INJ) << LL_ADC_TRIG_OP_NB_POS) \
                                         | LL_ADC_TRIG_OP_STATE_0) /* Marker of trigger source specific to
                                         option bit 6, bit reset (for ADC group injected) */
#define LL_ADC_TRIG_OP6_SET             (((6UL - LL_ADC_TRIG_OP_NB_ADD_INJ) << LL_ADC_TRIG_OP_NB_POS) \
                                         | LL_ADC_TRIG_OP_STATE_1) /* Marker of trigger source specific to
                                         option bit 6, bit set (for ADC group injected) */
#define LL_ADC_TRIG_OP7_RESET           (((7UL - LL_ADC_TRIG_OP_NB_ADD_INJ) << LL_ADC_TRIG_OP_NB_POS) \
                                         | LL_ADC_TRIG_OP_STATE_0) /* Marker of trigger source specific to
                                         option bit 7, bit reset (for ADC group injected) */
#define LL_ADC_TRIG_OP7_SET             (((7UL - LL_ADC_TRIG_OP_NB_ADD_INJ) << LL_ADC_TRIG_OP_NB_POS) \
                                         | LL_ADC_TRIG_OP_STATE_1) /* Marker of trigger source specific to
                                         option bit 7, bit set (for ADC group injected) */

#if defined(ADC3)
#define LL_ADC_TRIG_REG_OPX_POS (0U) /* ADC regular trigger source available with option bit: position of bitfield
                                        vs option bit position in register */
#define LL_ADC_TRIG_INJ_OPX_POS (2U) /* ADC injected trigger source available with option bit: position of bitfield
                                        vs option bit position in register */
#else /* Implementation without look up table */
#define LL_ADC_TRIG_REG_OPX_POS (4U) /* ADC regular trigger source available with option bit: position of bitfield
                                        vs option bit position in register */
#define LL_ADC_TRIG_INJ_OPX_POS (6U) /* ADC injected trigger source available with option bit: position of bitfield
                                        vs option bit position in register */
#endif /* ADC3 */

/* Number of unique trigger sources */
#if defined(ADC4)
#define LL_ADC_REG_TRIG_SRC_COUNT (66U)
#define LL_ADC_INJ_TRIG_SRC_COUNT (64U)
#else
#define LL_ADC_REG_TRIG_SRC_COUNT (42U)
#define LL_ADC_INJ_TRIG_SRC_COUNT (40U)
#endif /* ADC4 */

#if defined(ADC3)

/* Private macro to adapt trigger source look up table size in function of instances available on each device
   - ADC instances not available on this device are ignored
   - ADC instances are grouped by common instance (example: trig_adc1 and trig_adc2 are common, only trig_adc1 kept)
*/
#if (ADC_COMMON_COUNT == 4)
#define LL_ADC_TRIG_INST(trig_adc12, trig_adc3, trig_adc45, trig_adc6) \
  {(trig_adc12), (trig_adc3), (trig_adc45), (trig_adc6)}
#elif (ADC_COMMON_COUNT == 2)
#define LL_ADC_TRIG_INST(trig_adc12, trig_adc3, trig_adc45, trig_adc6) \
  {(trig_adc12), (trig_adc3)}
#else
#define LL_ADC_TRIG_INST(trig_adc12, trig_adc3, trig_adc45, trig_adc6) \
  {(trig_adc12)}
#endif /* ADC_COMMON_COUNT */

/* Look up table of ADC group regular trigger sources in function of ADC common instances
  Values details:
   - between 0 and 31: trigger number written in register bitfield
   - LL_ADC_TRIG_OPx: option bit associated to the trigger number
   - LL_ADC_TRIG_NA: trigger not available
*/
static const uint8_t LL_ADC_REG_TRIG_SRC_LUT[LL_ADC_REG_TRIG_SRC_COUNT][ADC_COMMON_COUNT] =
{
  /* Triggers common to all ADC instances (including devices featuring other ADC instances) */
  LL_ADC_TRIG_INST(4U,              2U,             2U,             1U),            /* Index 0: TIM1_TRGO */
  LL_ADC_TRIG_INST(5U,              3U,             3U,             2U),            /* Index 1: TIM1_TRGO2 */
  LL_ADC_TRIG_INST(7U,              6U,             4U,             3U),            /* Index 2: TIM2_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP5_RESET | 9U, LL_ADC_TRIG_OP5_RESET | 9U, 5U,  4U), /* Index 3: TIM3_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP5_SET | 9U, LL_ADC_TRIG_OP5_SET | 9U, 6U,     5U), /* Index 4: TIM4_TRGO */
  LL_ADC_TRIG_INST(10U,            10U,             8U,             8U),            /* Index 5: TIM6_TRGO */
  LL_ADC_TRIG_INST(11U,            12U,             9U,             9U),            /* Index 6: TIM8_TRGO */
  LL_ADC_TRIG_INST(12U,            13U,            10U,            10U),            /* Index 7: TIM8_TRGO2 */
  LL_ADC_TRIG_INST(13U,            14U,            11U,            11U),            /* Index 8: TIM9_TRGO */
  LL_ADC_TRIG_INST(14U,            15U,            12U,            12U),            /* Index 9: TIM15_TRGO */
#if defined(ADC4)
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP8_RESET | 17U, LL_ADC_TRIG_OP8_RESET | 17U, 13U, 13U), /* Index 10: TIM20_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP8_RESET | 18U, LL_ADC_TRIG_OP8_RESET | 18U, 11U, 11U), /* Index 11: TIM20_TRGO2 */
#else
  LL_ADC_TRIG_INST(17U,            17U,            13U,            13U),            /* Index 10: TIM20_TRGO */
  LL_ADC_TRIG_INST(18U,            18U,            11U,            11U),            /* Index 11: TIM20_TRGO2 */
#endif /* ADC4 */
  LL_ADC_TRIG_INST(19U,            19U,            19U,            19U),            /* Index 12: TIM26_TRGO */
  LL_ADC_TRIG_INST(22U,            22U,            22U,            22U),            /* Index 13: HRTIM1_TRG1 */
  LL_ADC_TRIG_INST(23U,            23U,            23U,            23U),            /* Index 14: HRTIM1_TRG2 */
  LL_ADC_TRIG_INST(24U,            24U,            24U,            24U),            /* Index 15: HRTIM1_TRG3 */
  LL_ADC_TRIG_INST(25U,            25U,            25U,            25U),            /* Index 16: HRTIM1_TRG4 */
  LL_ADC_TRIG_INST(26U,            26U,            26U,            26U),            /* Index 17: HRTIM1_TRG5 */
  LL_ADC_TRIG_INST(27U,            27U,            27U,            27U),            /* Index 18: HRTIM1_TRG6 */
  LL_ADC_TRIG_INST(28U,            28U,            28U,            28U),            /* Index 19: HRTIM1_TRG7 */
  LL_ADC_TRIG_INST(29U,            29U,            29U,            29U),            /* Index 20: HRTIM1_TRG8 */
  LL_ADC_TRIG_INST(30U,            30U,            30U,            30U),            /* Index 21: HRTIM1_TRG9 */
  LL_ADC_TRIG_INST(31U,            31U,            31U,            31U),            /* Index 22: HRTIM1_TRG10 */
  /* Triggers specific to ADC instances: ADC1, ADC2, ADC3 */
  LL_ADC_TRIG_INST(3U,             1U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 23: TIM1_OC3 */
  LL_ADC_TRIG_INST(20U,            20U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),            /* Index 24: LPTIM1_OC1 */
  LL_ADC_TRIG_INST(15U,            16U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),            /* Index 25: TIM20_OC1 */
  /* Triggers specific to ADC instances: ADC1, ADC2 */
  LL_ADC_TRIG_INST(0U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 26: EXTI_LINE11 */
  LL_ADC_TRIG_INST(1U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 27: TIM1_OC1 */
  LL_ADC_TRIG_INST(2U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 28: TIM1_OC2 */
  LL_ADC_TRIG_INST(6U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 29: TIM2_OC2 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP4_RESET | 8U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 30: TIM3_OC4 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP4_SET | 8U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 31: TIM4_OC4 */
  LL_ADC_TRIG_INST(16U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),            /* Index 32: TIM20_OC2 */
  LL_ADC_TRIG_INST(21U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),            /* Index 33: PLAY_OUT11 */
#if defined(ADC3)
  /* Triggers specific to ADC instances: ADC3 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,             0U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 34: EXTI_LINE2 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,             4U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 35: TIM2_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,             5U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 36: TIM2_OC3 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,             7U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 37: TIM3_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_OP4_RESET | 8U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 38: TIM3_OC2 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_OP4_SET | 8U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 39: TIM4_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,            11U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 40: TIM8_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,            21U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 41: PLAY_OUT12 */
#if defined(ADC4)
  /* Triggers specific to ADC instances: ADC4, ADC5, ADC6 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,             0U, LL_ADC_TRIG_NA), /* Index 42: EXTI_LINE0 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,             0U), /* Index 43: EXTI_LINE4 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,             1U, LL_ADC_TRIG_NA), /* Index 44: TIM1_OC5 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,             6U), /* Index 45: TIM5_OC2 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,             7U,             7U), /* Index 46: TIM5_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_OP | 17U, LL_ADC_TRIG_NA), /* Index 47: TIM23_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_OP | 17U), /* Index 48: TIM23_OC2 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,            15U,            15U), /* Index 49: TIM23_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,            16U,            16U), /* Index 50: TIM24_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,            20U,            20U), /* Index 51: LPTIM2_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,            21U, LL_ADC_TRIG_NA), /* Index 52: PLAY_OUT13 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,            21U), /* Index 53: PLAY_OUT14 */

  /* Triggers specific: TIM25, HRTIM2 (not available on all devices) */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP8_SET | 17U, LL_ADC_TRIG_OP8_SET | 17U, 17U, 17U), /* Index 54: TIM25_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP8_SET | 18U, LL_ADC_TRIG_OP8_SET | 18U, 18U, 18U), /* Index 55: TIM25_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 22U, LL_ADC_TRIG_OP | 22U, LL_ADC_TRIG_OP | 22U, LL_ADC_TRIG_OP | 22U), /* Index 56:
                                        HRTIM2_TRG1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 23U, LL_ADC_TRIG_OP | 23U, LL_ADC_TRIG_OP | 23U, LL_ADC_TRIG_OP | 23U), /* Index 57:
                                        HRTIM2_TRG2 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 24U, LL_ADC_TRIG_OP | 24U, LL_ADC_TRIG_OP | 24U, LL_ADC_TRIG_OP | 24U), /* Index 58:
                                        HRTIM2_TRG3 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 25U, LL_ADC_TRIG_OP | 25U, LL_ADC_TRIG_OP | 25U, LL_ADC_TRIG_OP | 25U), /* Index 59:
                                        HRTIM2_TRG4 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 26U, LL_ADC_TRIG_OP | 26U, LL_ADC_TRIG_OP | 26U, LL_ADC_TRIG_OP | 26U), /* Index 60:
                                        HRTIM2_TRG5 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 27U, LL_ADC_TRIG_OP | 27U, LL_ADC_TRIG_OP | 27U, LL_ADC_TRIG_OP | 27U), /* Index 61:
                                        HRTIM2_TRG6 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 28U, LL_ADC_TRIG_OP | 28U, LL_ADC_TRIG_OP | 28U, LL_ADC_TRIG_OP | 28U), /* Index 62:
                                        HRTIM2_TRG7 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 29U, LL_ADC_TRIG_OP | 29U, LL_ADC_TRIG_OP | 29U, LL_ADC_TRIG_OP | 29U), /* Index 63:
                                        HRTIM2_TRG8 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 30U, LL_ADC_TRIG_OP | 30U, LL_ADC_TRIG_OP | 30U, LL_ADC_TRIG_OP | 30U), /* Index 64:
                                        HRTIM2_TRG9 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 31U, LL_ADC_TRIG_OP | 31U, LL_ADC_TRIG_OP | 31U, LL_ADC_TRIG_OP | 31U), /* Index 65:
                                        HRTIM2_TRG10 */
#endif /* ADC4 */
#endif /* ADC3 */
};
#define LL_ADC_REG_TRIG_SRC_LUT_COUNT (sizeof(LL_ADC_REG_TRIG_SRC_LUT) / sizeof(*(LL_ADC_REG_TRIG_SRC_LUT)))

/* Look up table of ADC group injected trigger sources in function of ADC common instances
  Values details:
   - between 0 and 31: trigger number written in register bitfield
   - LL_ADC_TRIG_OPx: option bit associated to the trigger number
   - LL_ADC_TRIG_NA: trigger not available
*/
static const uint8_t LL_ADC_INJ_TRIG_SRC_LUT[LL_ADC_INJ_TRIG_SRC_COUNT][ADC_COMMON_COUNT] =
{
  /* Triggers common to all ADC instances (including devices featuring other ADC instances) */
  LL_ADC_TRIG_INST(2U,             3U,             1U,             1U),             /* Index 0: TIM1_TRGO */
  LL_ADC_TRIG_INST(3U,             4U,             2U,             2U),             /* Index 1: TIM1_TRGO2 */
  LL_ADC_TRIG_INST(5U,             5U,             3U,             3U),             /* Index 2: TIM2_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP6_RESET | 9U, 6U, 4U,              4U),            /* Index 3: TIM3_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP6_SET | 9U, LL_ADC_TRIG_OP7_SET | 9U,  5U,     5U), /* Index 4: TIM4_TRGO */
  LL_ADC_TRIG_INST(10U,             7U,             8U,             8U),            /* Index 5: TIM7_TRGO */
  LL_ADC_TRIG_INST(12U,            10U,             9U,             9U),            /* Index 6: TIM8_TRGO */
  LL_ADC_TRIG_INST(13U,            11U,            10U,            10U),            /* Index 7: TIM8_TRGO2 */
  LL_ADC_TRIG_INST(14U,            12U,            11U,            11U),            /* Index 8: TIM12_TRGO */
  LL_ADC_TRIG_INST(15U,            13U,            12U,            12U),            /* Index 9: TIM15_TRGO */
#if defined(ADC4)
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP8_RESET | 17U, LL_ADC_TRIG_OP8_RESET | 17U, 13U, 13U), /* Index 10: TIM20_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP8_RESET | 18U, LL_ADC_TRIG_OP8_RESET | 18U, 14U, 14U), /* Index 11: TIM20_TRGO2 */
#else
  LL_ADC_TRIG_INST(17U,            17U,            13U,            13U),            /* Index 10: TIM20_TRGO */
  LL_ADC_TRIG_INST(18U,            18U,            14U,            14U),            /* Index 11: TIM20_TRGO2 */
#endif /* ADC4 */
  LL_ADC_TRIG_INST(19U,            19U,            19U,            19U),            /* Index 12: TIM27_TRGO */
  LL_ADC_TRIG_INST(22U,            22U,            22U,            22U),            /* Index 13: HRTIM1_TRG1 */
  LL_ADC_TRIG_INST(23U,            23U,            23U,            23U),            /* Index 14: HRTIM1_TRG2 */
  LL_ADC_TRIG_INST(24U,            24U,            24U,            24U),            /* Index 15: HRTIM1_TRG3 */
  LL_ADC_TRIG_INST(25U,            25U,            25U,            25U),            /* Index 16: HRTIM1_TRG4 */
  LL_ADC_TRIG_INST(26U,            26U,            26U,            26U),            /* Index 17: HRTIM1_TRG5 */
  LL_ADC_TRIG_INST(27U,            27U,            27U,            27U),            /* Index 18: HRTIM1_TRG6 */
  LL_ADC_TRIG_INST(28U,            28U,            28U,            28U),            /* Index 19: HRTIM1_TRG7 */
  LL_ADC_TRIG_INST(29U,            29U,            29U,            29U),            /* Index 20: HRTIM1_TRG8 */
  LL_ADC_TRIG_INST(30U,            30U,            30U,            30U),            /* Index 21: HRTIM1_TRG9 */
  LL_ADC_TRIG_INST(31U,            31U,            31U,            31U),            /* Index 22: HRTIM1_TRG10 */
  /* Triggers specific to ADC instances: ADC1, ADC2, ADC3 */
  LL_ADC_TRIG_INST(1U,             2U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 23: TIM1_OC4 */
  LL_ADC_TRIG_INST(6U,             7U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 24: TIM3_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_OP6_SET | 8U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 25: TIM4_OC3 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_OP6_RESET | 8U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 26: TIM8_OC2 */
  LL_ADC_TRIG_INST(11U, LL_ADC_TRIG_OP7_RESET | 9U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),            /* Index 27: TIM8_OC4 */
  LL_ADC_TRIG_INST(16U,            14U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),            /* Index 28: TIM16_OC1 */
  LL_ADC_TRIG_INST(20U,            20U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),            /* Index 29: LPTIM1_OC2 */
  /* Triggers specific to ADC instances: ADC1, ADC2 */
  LL_ADC_TRIG_INST(0U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 30: EXTI_LINE15 */
  LL_ADC_TRIG_INST(4U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 31: TIM2_OC1 */
  LL_ADC_TRIG_INST(7U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 32: TIM3_OC3 */
  LL_ADC_TRIG_INST(8U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),             /* Index 33: TIM3_OC4 */
  LL_ADC_TRIG_INST(21U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA),            /* Index 34: PLAY_OUT13 */
#if defined(ADC3)
  /* Triggers specific to ADC instances: ADC3 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,             0U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 35: EXTI_LINE3 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,             1U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 36: TIM1_OC3 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,            15U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 37: TIM17_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,            16U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 38: TIM20_OC2 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA,            21U, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA), /* Index 39: PLAY_OUT14 */
#if defined(ADC4)
  /* Triggers specific to ADC instances: ADC4, ADC5, ADC6 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,             0U, LL_ADC_TRIG_NA), /* Index 40: EXTI_LINE1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,             0U), /* Index 41: EXTI_LINE5 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,             6U, LL_ADC_TRIG_NA), /* Index 42: TIM5_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,             6U), /* Index 43: TIM5_OC3 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,             7U,             7U), /* Index 44: TIM5_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,            15U,            15U), /* Index 45: TIM23_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_OP | 17U, LL_ADC_TRIG_NA), /* Index 46: TIM24_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_OP | 17U), /* Index 47: TIM24_OC2 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,            16U,            16U), /* Index 48: TIM24_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,            20U,            20U), /* Index 49: LPTIM2_OC1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,            21U, LL_ADC_TRIG_NA), /* Index 50: PLAY_OUT15 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_NA, LL_ADC_TRIG_NA, LL_ADC_TRIG_NA,            21U), /* Index 51: PLAY_OUT16 */
  /* Triggers specific: TIM25, HRTIM2 (not available on all devices) */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP8_SET | 17U, LL_ADC_TRIG_OP8_SET | 17U, 18U, 18U), /* Index 52: TIM25_TRGO */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP8_SET | 18U, LL_ADC_TRIG_OP8_SET | 18U, 18U, 18U), /* Index 53: TIM25_TRGO2 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 22U, LL_ADC_TRIG_OP | 22U, LL_ADC_TRIG_OP | 22U, LL_ADC_TRIG_OP | 22U), /* Index 54:
                                        HRTIM2_TRG1 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 23U, LL_ADC_TRIG_OP | 23U, LL_ADC_TRIG_OP | 23U, LL_ADC_TRIG_OP | 23U), /* Index 55:
                                        HRTIM2_TRG2 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 24U, LL_ADC_TRIG_OP | 24U, LL_ADC_TRIG_OP | 24U, LL_ADC_TRIG_OP | 24U), /* Index 56:
                                        HRTIM2_TRG3 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 25U, LL_ADC_TRIG_OP | 25U, LL_ADC_TRIG_OP | 25U, LL_ADC_TRIG_OP | 25U), /* Index 57:
                                        HRTIM2_TRG4 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 26U, LL_ADC_TRIG_OP | 26U, LL_ADC_TRIG_OP | 26U, LL_ADC_TRIG_OP | 26U), /* Index 58:
                                        HRTIM2_TRG5 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 27U, LL_ADC_TRIG_OP | 27U, LL_ADC_TRIG_OP | 27U, LL_ADC_TRIG_OP | 27U), /* Index 59:
                                        HRTIM2_TRG6 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 28U, LL_ADC_TRIG_OP | 28U, LL_ADC_TRIG_OP | 28U, LL_ADC_TRIG_OP | 28U), /* Index 60:
                                        HRTIM2_TRG7 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 29U, LL_ADC_TRIG_OP | 29U, LL_ADC_TRIG_OP | 29U, LL_ADC_TRIG_OP | 29U), /* Index 61:
                                        HRTIM2_TRG8 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 30U, LL_ADC_TRIG_OP | 30U, LL_ADC_TRIG_OP | 30U, LL_ADC_TRIG_OP | 30U), /* Index 62:
                                        HRTIM2_TRG9 */
  LL_ADC_TRIG_INST(LL_ADC_TRIG_OP | 31U, LL_ADC_TRIG_OP | 31U, LL_ADC_TRIG_OP | 31U, LL_ADC_TRIG_OP | 31U), /* Index 63:
                                        HRTIM2_TRG10 */
#endif /* ADC4 */
#endif /* ADC3 */
};
#define LL_ADC_INJ_TRIG_SRC_LUT_COUNT (sizeof(LL_ADC_INJ_TRIG_SRC_LUT) / sizeof(*(LL_ADC_INJ_TRIG_SRC_LUT)))

#endif /* ADC3 */

/* Internal mask for ADC channel.
To select into literal LL_ADC_CHANNEL_LUT[] the relevant bits for:
- channel identifier defined by bitfield
- channel sampling time defined by SMPRx register offset and SMPx bits positions into SMPRx register */
#define LL_ADC_CHANNEL_ID_BITFIELD_MASK (ADC_AWD2CR_AWDCH)
#define LL_ADC_CHANNEL_ID_NB_MASK_POSBIT0 (ADC_SQR2_SQ5) /* Aligned on register LSB, equivalent to shift in register:
                                        (LL_ADC_CH_NUMBER_MASK >> [Position of bitfield "LL_ADC_CH_NUMBER_MASK"] */

#define LL_ADC_CH_EXTERNAL         (0x00000000UL) /* Marker of external channel */
#define LL_ADC_CH_INTERNAL_ADC1    (0x00000400UL) /* Marker of internal channel of ADC1 */
#define LL_ADC_CH_INTERNAL_ADC2    (0x00000800UL) /* Marker of internal channel of ADC2 */
#define LL_ADC_CH_INTERNAL_ADC3    (0x00001000UL) /* Marker of internal channel of ADC3 */

/* Internal mask for channel number remapped to an alternate number depending on ADC instance */
#define LL_ADC_CH_REMAP                 (0x00010000UL) /* Channel number remapped */

/* Internal mask for specific virtual channel */
#define LL_ADC_CH_NUMBER_RANGE_MAX      (19UL) /* ADC channel number max value */
#define ADC_CH_NONE_NUMBER              (LL_ADC_CH_NUMBER_RANGE_MAX + 1UL)
#define ADC_CH_ALL_NUMBER               (LL_ADC_CH_NUMBER_RANGE_MAX + 2UL)

#define LL_ADC_CH_NUMBER_MASK           (0x0000001FUL) /* Mask of channel number region in LL_ADC_CHANNEL_X
                                        bitfield (values as decimal number in range [0; 255]) */
#define LL_ADC_CH_INTERNAL_MASK         (0x0000FF00UL) /* Mask of internal channel region in LL_ADC_CHANNEL_X
                                        bitfield (values as bitfield for each config) */

/* Internal register offset for ADC channel sampling time configuration */
/* (offset placed into a spare area of literal definition) */
#define LL_ADC_CH_SMPR1_REGOFFSET       (0x00000000UL)
#define LL_ADC_CH_SMPR2_REGOFFSET       (0x02000000UL)
#define LL_ADC_CH_SMPRX_REGOFFSET_MASK  (LL_ADC_CH_SMPR1_REGOFFSET | LL_ADC_CH_SMPR2_REGOFFSET)
#define LL_ADC_CH_SMPRX_REGOFFSET_POS   (25UL) /* Position of bitfield ADC_SMPRx_REGOFFSET
                                        in LL_ADC_CH_SMPRX_REGOFFSET_MASK */
#define LL_ADC_CH_SMPX_BITOFFSET_MASK   (0x01F00000UL)
#define LL_ADC_CH_SMPX_BITOFFSET_POS    (20UL) /* Position of bitfield LL_ADC_CH_SMPX_BITOFFSET_MASK in register */

/* Definition of channels ID bitfield information to be inserted into channels literals definition */
#define LL_ADC_CHANNEL_0_BITFIELD       (ADC_AWD2CR_AWDCH_0)
#define LL_ADC_CHANNEL_1_BITFIELD       (ADC_AWD2CR_AWDCH_1)
#define LL_ADC_CHANNEL_2_BITFIELD       (ADC_AWD2CR_AWDCH_2)
#define LL_ADC_CHANNEL_3_BITFIELD       (ADC_AWD2CR_AWDCH_3)
#define LL_ADC_CHANNEL_4_BITFIELD       (ADC_AWD2CR_AWDCH_4)
#define LL_ADC_CHANNEL_5_BITFIELD       (ADC_AWD2CR_AWDCH_5)
#define LL_ADC_CHANNEL_6_BITFIELD       (ADC_AWD2CR_AWDCH_6)
#define LL_ADC_CHANNEL_7_BITFIELD       (ADC_AWD2CR_AWDCH_7)
#define LL_ADC_CHANNEL_8_BITFIELD       (ADC_AWD2CR_AWDCH_8)
#define LL_ADC_CHANNEL_9_BITFIELD       (ADC_AWD2CR_AWDCH_9)
#define LL_ADC_CHANNEL_10_BITFIELD      (ADC_AWD2CR_AWDCH_10)
#define LL_ADC_CHANNEL_11_BITFIELD      (ADC_AWD2CR_AWDCH_11)
#define LL_ADC_CHANNEL_12_BITFIELD      (ADC_AWD2CR_AWDCH_12)
#define LL_ADC_CHANNEL_13_BITFIELD      (ADC_AWD2CR_AWDCH_13)
#define LL_ADC_CHANNEL_14_BITFIELD      (ADC_AWD2CR_AWDCH_14)
#define LL_ADC_CHANNEL_15_BITFIELD      (ADC_AWD2CR_AWDCH_15)
#define LL_ADC_CHANNEL_16_BITFIELD      (ADC_AWD2CR_AWDCH_16)
#define LL_ADC_CHANNEL_17_BITFIELD      (ADC_AWD2CR_AWDCH_17)
#define LL_ADC_CHANNEL_18_BITFIELD      (ADC_AWD2CR_AWDCH_18)
#define LL_ADC_CHANNEL_19_BITFIELD      (ADC_AWD2CR_AWDCH_19)
#define LL_ADC_CHANNEL_NONE_BITFIELD    (0x00000000UL)
#define LL_ADC_CHANNEL_ALL_BITFIELD     (ADC_AWD2CR_AWDCH)

/* Definition of channels sampling time information to be inserted into channels literals definition */
#define LL_ADC_CHANNEL_0_SMP            (LL_ADC_CH_SMPR1_REGOFFSET | (( 0UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_1_SMP            (LL_ADC_CH_SMPR1_REGOFFSET | (( 3UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_2_SMP            (LL_ADC_CH_SMPR1_REGOFFSET | (( 6UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_3_SMP            (LL_ADC_CH_SMPR1_REGOFFSET | (( 9UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_4_SMP            (LL_ADC_CH_SMPR1_REGOFFSET | ((12UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_5_SMP            (LL_ADC_CH_SMPR1_REGOFFSET | ((15UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_6_SMP            (LL_ADC_CH_SMPR1_REGOFFSET | ((18UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_7_SMP            (LL_ADC_CH_SMPR1_REGOFFSET | ((21UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_8_SMP            (LL_ADC_CH_SMPR1_REGOFFSET | ((24UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_9_SMP            (LL_ADC_CH_SMPR1_REGOFFSET | ((27UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_10_SMP           (LL_ADC_CH_SMPR2_REGOFFSET | (( 0UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_11_SMP           (LL_ADC_CH_SMPR2_REGOFFSET | (( 3UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_12_SMP           (LL_ADC_CH_SMPR2_REGOFFSET | (( 6UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_13_SMP           (LL_ADC_CH_SMPR2_REGOFFSET | (( 9UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_14_SMP           (LL_ADC_CH_SMPR2_REGOFFSET | ((12UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_15_SMP           (LL_ADC_CH_SMPR2_REGOFFSET | ((15UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_16_SMP           (LL_ADC_CH_SMPR2_REGOFFSET | ((18UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_17_SMP           (LL_ADC_CH_SMPR2_REGOFFSET | ((21UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_18_SMP           (LL_ADC_CH_SMPR2_REGOFFSET | ((24UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_19_SMP           (LL_ADC_CH_SMPR2_REGOFFSET | ((27UL) << LL_ADC_CH_SMPX_BITOFFSET_POS))
#define LL_ADC_CHANNEL_NONE_SMP         (LL_ADC_CH_SMPR1_REGOFFSET) /* Channel virtual without any register */
#define LL_ADC_CHANNEL_ALL_SMP          (LL_ADC_CH_SMPR1_REGOFFSET) /* Channel virtual without any register */

/* Definition of ADC channel look up table containing channels information */
static const uint32_t LL_ADC_CHANNEL_LUT[] =
{
  (LL_ADC_CHANNEL_0_SMP   | LL_ADC_CHANNEL_0_BITFIELD),     /*!< ADC channel ADCx_IN0  */
  (LL_ADC_CHANNEL_1_SMP   | LL_ADC_CHANNEL_1_BITFIELD),     /*!< ADC channel ADCx_IN1  */
  (LL_ADC_CHANNEL_2_SMP   | LL_ADC_CHANNEL_2_BITFIELD),     /*!< ADC channel ADCx_IN2  */
  (LL_ADC_CHANNEL_3_SMP   | LL_ADC_CHANNEL_3_BITFIELD),     /*!< ADC channel ADCx_IN3  */
  (LL_ADC_CHANNEL_4_SMP   | LL_ADC_CHANNEL_4_BITFIELD),     /*!< ADC channel ADCx_IN4  */
  (LL_ADC_CHANNEL_5_SMP   | LL_ADC_CHANNEL_5_BITFIELD),     /*!< ADC channel ADCx_IN5  */
  (LL_ADC_CHANNEL_6_SMP   | LL_ADC_CHANNEL_6_BITFIELD),     /*!< ADC channel ADCx_IN6  */
  (LL_ADC_CHANNEL_7_SMP   | LL_ADC_CHANNEL_7_BITFIELD),     /*!< ADC channel ADCx_IN7  */
  (LL_ADC_CHANNEL_8_SMP   | LL_ADC_CHANNEL_8_BITFIELD),     /*!< ADC channel ADCx_IN8  */
  (LL_ADC_CHANNEL_9_SMP   | LL_ADC_CHANNEL_9_BITFIELD),     /*!< ADC channel ADCx_IN9  */
  (LL_ADC_CHANNEL_10_SMP  | LL_ADC_CHANNEL_10_BITFIELD),    /*!< ADC channel ADCx_IN10 */
  (LL_ADC_CHANNEL_11_SMP  | LL_ADC_CHANNEL_11_BITFIELD),    /*!< ADC channel ADCx_IN11 */
  (LL_ADC_CHANNEL_12_SMP  | LL_ADC_CHANNEL_12_BITFIELD),    /*!< ADC channel ADCx_IN12 */
  (LL_ADC_CHANNEL_13_SMP  | LL_ADC_CHANNEL_13_BITFIELD),    /*!< ADC channel ADCx_IN13 */
  (LL_ADC_CHANNEL_14_SMP  | LL_ADC_CHANNEL_14_BITFIELD),    /*!< ADC channel ADCx_IN14 */
  (LL_ADC_CHANNEL_15_SMP  | LL_ADC_CHANNEL_15_BITFIELD),    /*!< ADC channel ADCx_IN15 */
  (LL_ADC_CHANNEL_16_SMP  | LL_ADC_CHANNEL_16_BITFIELD),    /*!< ADC channel ADCx_IN16 */
  (LL_ADC_CHANNEL_17_SMP  | LL_ADC_CHANNEL_17_BITFIELD),    /*!< ADC channel ADCx_IN17 */
  (LL_ADC_CHANNEL_18_SMP  | LL_ADC_CHANNEL_18_BITFIELD),    /*!< ADC channel ADCx_IN18 */
  (LL_ADC_CHANNEL_19_SMP  | LL_ADC_CHANNEL_19_BITFIELD),    /*!< ADC channel ADCx_IN19 */
  (LL_ADC_CHANNEL_NONE_SMP | LL_ADC_CHANNEL_NONE_BITFIELD), /*!< ADC channel virtual (no channel) */
  (LL_ADC_CHANNEL_ALL_SMP  | LL_ADC_CHANNEL_ALL_BITFIELD),  /*!< ADC channel virtual (all channels) */
};
#define LL_ADC_CHANNEL_LUT_COUNT (sizeof(LL_ADC_CHANNEL_LUT) / sizeof(*(LL_ADC_CHANNEL_LUT)))

/* Internal mask for ADC mode single or differential ended.
To select into literals LL_ADC_IN_SINGLE_ENDED or LL_ADC_IN_DIFFERENTIAL the relevant bits for (concatenation of
multiple bits used in different registers):
- ADC calibration: calibration start, calibration factor get or set
- ADC channels: set each ADC channel ending mode */
#define LL_ADC_SGLDIFF_CAL_START_MASK   (ADC_CR_ADCALDIF)
#define LL_ADC_SGLDIFF_CAL_FACTOR_MASK  (ADC_CALFACT_CALFACT_D | ADC_CALFACT_CALFACT_S)
#define LL_ADC_SGLDIFF_CH_MASK          (LL_ADC_CHANNEL_ID_BITFIELD_MASK) /* Equivalent to ADC_DIFSEL_DIFSEL */
#define LL_ADC_SGLDIFF_CH_SHIFT_MASK    (ADC_CALFACT_CALFACT_S_4 | ADC_CALFACT_CALFACT_S_3) /* Value to perform
                                        shift when single mode is selected, shift value out of channels bits range. */
#define LL_ADC_SGLDIFF_CAL_F_BIT_D_MASK (0x00010000UL) /* Selection of 1 bit to discriminate differential mode:
                                        mask of bit */
#define LL_ADC_SGLDIFF_CAL_F_BIT_D_POS  (16UL)          /* Selection of 1 bit to discriminate differential mode:
                                        position of bit */
#define LL_ADC_SGLDIFF_CAL_F_BIT_D_SHIFT4 (LL_ADC_SGLDIFF_CAL_F_BIT_D_POS - 4UL) /* Shift of bit
                                        LL_ADC_SGLDIFF_CAL_F_BIT_D to perform a shift of 4 ranks */

#define LL_ADC_AWD_CH_NB_MASK           (ADC_CFGR1_AWD1CH)
#define LL_ADC_AWD_CH_NB_BITOFFSET_POS  (ADC_CFGR1_AWD1CH_Pos)

/* Internal register offset for ADC analog watchdog channel configuration */
#define LL_ADC_AWD_CR1_REGOFFSET        (0x00000000UL)
#define LL_ADC_AWD_CR2_REGOFFSET        (0x00100000UL)
#define LL_ADC_AWD_CR3_REGOFFSET        (0x00200000UL)

/* Register offset gap between AWD1 and AWD2-AWD3 configuration registers (Set separately as ADC_AWD_CRX_REGOFFSET
to spare 32 bits space */
#define LL_ADC_AWD_CR12_REGOFFSETGAP_MASK (ADC_AWD2CR_AWDCH_0)
#define LL_ADC_AWD_CR12_REGOFFSETGAP_VAL  (0x00000024UL)

#define LL_ADC_AWD_CRX_REGOFFSET_MASK   (LL_ADC_AWD_CR1_REGOFFSET | LL_ADC_AWD_CR2_REGOFFSET | LL_ADC_AWD_CR3_REGOFFSET)

#define LL_ADC_AWD_CR1_CHANNEL_MASK     (ADC_CFGR1_AWD1CH | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)
#define LL_ADC_AWD_CHANNEL_MASK         (LL_ADC_CH_NUMBER_MASK)
#define LL_ADC_AWD_CR23_CHANNEL_MASK    (ADC_AWD2CR_AWDCH)
#define LL_ADC_AWD_CR_ALL_CHANNEL_MASK  (LL_ADC_AWD_CR1_CHANNEL_MASK | LL_ADC_AWD_CR23_CHANNEL_MASK)

#define LL_ADC_AWD_CRX_REGOFFSET_POS    (20UL) /* Position of bits ADC_AWD_CRx_REGOFFSET
                                        in LL_ADC_AWD_CRX_REGOFFSET_MASK */

/* Internal register offset for ADC analog watchdog threshold configuration */
#define LL_ADC_AWD_TR1_REGOFFSET        (LL_ADC_AWD_CR1_REGOFFSET)
#define LL_ADC_AWD_TR2_REGOFFSET        (LL_ADC_AWD_CR2_REGOFFSET)
#define LL_ADC_AWD_TR3_REGOFFSET        (LL_ADC_AWD_CR3_REGOFFSET)
#define LL_ADC_AWD_TRX_REGOFFSET_MASK   (LL_ADC_AWD_TR1_REGOFFSET | LL_ADC_AWD_TR2_REGOFFSET | LL_ADC_AWD_TR3_REGOFFSET)
#define LL_ADC_AWD_TRX_REGOFFSET_POS    (LL_ADC_AWD_CRX_REGOFFSET_POS) /* Position of bits ADC_TRx_REGOFFSET
                                        in LL_ADC_AWD_TRX_REGOFFSET_MASK */

#define LL_ADC_AWD_TRX_BIT_HIGH_MASK    (0x00010000UL) /* Selection of 1 bit to discriminate threshold high:
                                        mask of bit */
#define LL_ADC_AWD_TRX_BIT_HIGH_POS     (16UL)         /* Selection of 1 bit to discriminate threshold high:
                                        position of bit */
#define LL_ADC_AWD_TRX_BIT_HIGH_SHIFT4  (LL_ADC_AWD_TRX_BIT_HIGH_POS - 4UL) /* Shift of bit ADC_AWD_TRX_BIT_HIGH
                                        to position to perform a shift of 4 ranks */

/* Internal definitions for oversampling */
#define LL_ADC_OVS_INJ_PARALLEL_SEL_POS (ADC_CFGR3_JOVSE_Pos + 1U) /* Bitfield position to avoid overlap
                                        of LL_ADC_OVS_x definitions in registers CFGR2 and CFGR3 */
#define LL_ADC_OVS_INJ_PARALLEL_SEL     ((ADC_CFGR3_JOVSE | ADC_CFGR3_JOVSPAR) << LL_ADC_OVS_INJ_PARALLEL_SEL_POS) /*
                                        Selection of oversampling injected parallel: all bitfields */
#define LL_ADC_OVS_INJ_PARALLEL_SEQ     ((ADC_CFGR3_JOVSE) << LL_ADC_OVS_INJ_PARALLEL_SEL_POS) /*
                                        Selection of oversampling injected parallel: mode sequential (legacy) */
#define LL_ADC_OVS_INJ_PARALLEL_INTERL  ((ADC_CFGR3_JOVSE | ADC_CFGR3_JOVSPAR) << LL_ADC_OVS_INJ_PARALLEL_SEL_POS) /*
                                        Selection of oversampling injected parallel: mode interleaved */

/* Internal mask for ADC offset: Internal register offset for ADC offset number configuration */
#define LL_ADC_OFR1_REGOFFSET           (0x00000000UL)
#define LL_ADC_OFR2_REGOFFSET           (0x00000001UL)
#define LL_ADC_OFR3_REGOFFSET           (0x00000002UL)
#define LL_ADC_OFR4_REGOFFSET           (0x00000003UL)
#define LL_ADC_OFRX_REGOFFSET_MASK      (LL_ADC_OFR1_REGOFFSET\
                                         | LL_ADC_OFR2_REGOFFSET | LL_ADC_OFR3_REGOFFSET | LL_ADC_OFR4_REGOFFSET)

#define LL_ADC_GAIN_COMPENSATION_DIV    (4096UL) /* ADC divisor for gain compensation coefficient */

/* ADC registers bits groups */
#define LL_ADC_CR_BITS_PROPERTY_RS      (ADC_CR_ADCAL | ADC_CR_JADSTP | ADC_CR_ADSTP | ADC_CR_JADSTART \
                                         | ADC_CR_ADSTART | ADC_CR_ADDIS | ADC_CR_ADEN) /* ADC register CR bits with
                                        HW property "rs": Software can read as well as set these bitfields,
                                        writing '0' has no effect on the bit value. */

/* Internal mask for ADC channel internal path */
#define LL_ADC_PATH_INTERNAL_OR_MASK    (ADC_OR_OP0) /*!< ADC measurement path
                                        to internal channel mask in LL_ADC_CHANNEL bitfield (instance wise) */
#define LL_ADC_COMMON_PATH_INTERNAL_MASK (ADCC_CCR_VREFEN | ADCC_CCR_TSEN)  /*!< ADC measurement path
                                        to internal channel mask in LL_ADC_CHANNEL bitfield (in ADC common instance) */
#define LL_ADC_PATH_INTERNAL_POS        (16UL) /*!< ADC measurement path to internal channel position
                                        in LL_ADC_CHANNEL_x bitfield */
#define LL_ADC_PATH_INTERNAL_MASK       (LL_ADC_PATH_INTERNAL_OR_MASK << LL_ADC_PATH_INTERNAL_POS) /*!< ADC measurement
                                        path to internal channel mask in LL_ADC_CHANNEL bitfield */

/* ADC internal channels related definitions */
/* Internal voltage reference VrefInt */
#define LL_ADC_VREFINT_CAL_ADDR         ((const uint16_t*) (0x08FFF810UL)) /* Internal voltage reference, address of
                                        parameter VREFINT_CAL: On this STM32 series, VrefInt ADC raw data acquired at
                                        Vref+ = LL_ADC_VREFINT_CAL_VREF (tolerance: +-10 mVolt). */
#define LL_ADC_VREFINT_CAL_VREF         (3300UL)                     /* Analog voltage reference (Vref+) value with
                                        which VrefInt has been calibrated in production
                                        (tolerance: +-10 mVolt) (unit: mVolt). */
/* Temperature sensor */
#define LL_ADC_TEMPSENSOR_CAL1_ADDR     ((const uint16_t*) (0x08FFF814UL)) /* Internal temperature sensor, address of
                                        parameter TS_CAL1: On this STM32 series, temperature sensor ADC raw data
                                        acquired at temperature LL_ADC_TEMPSENSOR_CAL1_TEMP,
                                        Vref+ = LL_ADC_TEMPSENSOR_CAL_VREF (tolerance: +-10 mVolt). */
#define LL_ADC_TEMPSENSOR_CAL2_ADDR     ((const uint16_t*) (0x08FFF818UL)) /* Internal temperature sensor, address of
                                        parameter TS_CAL2: On this STM32 series, temperature sensor ADC raw data
                                        acquired at temperature LL_ADC_TEMPSENSOR_CAL2_TEMP,
                                        Vref+ = LL_ADC_TEMPSENSOR_CAL_VREF (tolerance: +-10 mVolt). */
#define LL_ADC_TEMPSENSOR_CAL1_TEMP     (30L) /* Internal temperature sensor, temperature
                                        at which temperature sensor has been calibrated in production for data
                                        into LL_ADC_TEMPSENSOR_CAL1_ADDR (tolerance: +-5 DegC) (unit: DegC). */
#define LL_ADC_TEMPSENSOR_CAL2_TEMP     (110L) /* Internal temperature sensor, temperature
                                        at which temperature sensor has been calibrated in production for data
                                        into LL_ADC_TEMPSENSOR_CAL2_ADDR (tolerance: +-5 DegC) (unit: DegC). */
#define LL_ADC_TEMPSENSOR_CAL_VREF      (3300UL) /* Analog voltage reference (Vref+) value
                                        with which temperature sensor has been calibrated in production
                                        (tolerance: +-10 mVolt) (unit: mVolt). */

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Macros ADC Private Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: isolate bits with the
  *         selected mask and shift them to the register LSB
  *         (shift mask on register position bit 0).
  * @param  bits Bits in register 32 bits
  * @param  mask Mask in register 32 bits
  * @retval Bits in register 32 bits
  */
#define LL_ADC_MASK_SHIFT(bits, mask) \
  (((bits) & (mask)) >> STM32_POSITION_VAL((mask)))

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  reg Register basis from which the offset is applied.
  * @param  reg_offset Offset to be applied (unit: number of registers).
  * @retval Pointer to register address
  */
#define LL_ADC_PTR_REG_OFFSET(reg, reg_offset) \
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(reg)) + ((reg_offset) << 2UL))))

/**
  * @brief Helper macro to access the ADC instance corresponding index in conversion trigger source
  *        look up table LL_ADC_[REG|INJ]_TRIG_SRC_LUT[].
  * @param instance ADC instance
  * @retval look-up table index
  */
#if defined(ADC4)
#define LL_ADC_TRIG_SRC_LUT_INST_INDEX(instance) \
  ((uint8_t)(((uint32_t)ADC_COMMON_INSTANCE(instance) - (uint32_t)ADC_COMMON_INSTANCE(ADC1)) >> 10U))
#elif defined(ADC3)
#define LL_ADC_TRIG_SRC_LUT_INST_INDEX(instance) \
  (((instance) == ADC3) ? (1U) \
   : (0U))
#else /* ADC1 or ADC2 */
#define LL_ADC_TRIG_SRC_LUT_INST_INDEX(instance) \
  (0U)
#endif /* ADC4 */

/**
  * @brief Helper macro to access the ADC instance corresponding index in channel
  *        look up table LL_ADC_CHANNEL_LUT[].
  * @param channel ADC channel
  * @retval look-up table index
  */
__STATIC_INLINE uint32_t LL_ADC_CHANNEL_LUT_INDEX(uint32_t channel)
{
  uint32_t channel_lut_index = (channel & LL_ADC_CH_NUMBER_MASK);
  return ((channel_lut_index < LL_ADC_CHANNEL_LUT_COUNT) ? channel_lut_index : ADC_CH_NONE_NUMBER);
}

/**
  * @brief Helper macro to access the ADC instance corresponding index in differential channel
  *        look up table LL_ADC_CHANNEL_DIFF_LUT[].
  * @param p_adc ADC instance
  * @retval look-up table index
  */
__STATIC_INLINE uint8_t LL_ADC_INSTANCE_LUT_INDEX(const ADC_TypeDef *p_adc) \
{
#if defined(ADC3)
  if (p_adc == ADC3)
  {
    return 2U;
  }
  else
#endif /* ADC3 */
  {
    uint32_t p_adc_addr = (uint32_t)p_adc;
    return (uint8_t)((p_adc_addr - (uint32_t)(ADC1)) >> 8U);
  }
}

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Constants LL ADC Constants
  * @{
  */

/** @defgroup ADC_LL_EC_HELPER_MACRO  Definitions of constants used by helper macro
  * @{
  */
#define LL_ADC_TEMPERATURE_CALC_ERROR   ((int16_t)0x7FFF) /*!< Temperature calculation error using helper macro
                                        @ref LL_ADC_CALC_TEMPERATURE(), due to issue on calibration parameters.
                                        This value is coded on 16 bits (to fit on signed word or double word)
                                        and corresponds to an inconsistent temperature value. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_FLAG ADC flags
  * @brief    Flags defines which can be used with LL_ADC_ReadReg function
  * @{
  */
#define LL_ADC_FLAG_ADRDY               ADC_ISR_ADRDY      /*!< ADC flag instance ready */
#define LL_ADC_FLAG_EOC                 ADC_ISR_EOC        /*!< ADC flag group regular end of unitary conversion */
#define LL_ADC_FLAG_EOS                 ADC_ISR_EOS        /*!< ADC flag group regular end of sequence conversions */
#define LL_ADC_FLAG_OVR                 ADC_ISR_OVR        /*!< ADC flag group regular overrun */
#define LL_ADC_FLAG_EOSMP               ADC_ISR_EOSMP      /*!< ADC flag group regular end of sampling phase */
#define LL_ADC_FLAG_JEOC                ADC_ISR_JEOC       /*!< ADC flag group injected end of unitary conversion */
#define LL_ADC_FLAG_JEOS                ADC_ISR_JEOS       /*!< ADC flag group injected end of sequence conversions */
#define LL_ADC_FLAG_JQOVF               ADC_ISR_JQOVF      /*!< ADC flag ADC group injected contexts queue overflow */
#define LL_ADC_FLAG_AWD1                ADC_ISR_AWD1       /*!< ADC flag analog watchdog 1 out of window event */
#define LL_ADC_FLAG_AWD2                ADC_ISR_AWD2       /*!< ADC flag analog watchdog 2 out of window event */
#define LL_ADC_FLAG_AWD3                ADC_ISR_AWD3       /*!< ADC flag analog watchdog 3 out of window event */
#define LL_ADC_FLAG_LDORDY              ADC_ISR_LDORDY     /*!< ADC flag internal voltage regulator (LDO) ready */

#define LL_ADC_FLAG_ALL                 (LL_ADC_FLAG_ADRDY \
                                         | LL_ADC_FLAG_EOC | LL_ADC_FLAG_EOS | LL_ADC_FLAG_OVR | LL_ADC_FLAG_EOSMP \
                                         | LL_ADC_FLAG_JEOC | LL_ADC_FLAG_JEOS | LL_ADC_FLAG_JQOVF \
                                         | LL_ADC_FLAG_AWD1 | LL_ADC_FLAG_AWD2 | LL_ADC_FLAG_AWD3 \
                                         | LL_ADC_FLAG_LDORDY) /*!< ADC all flags */

#define LL_ADC_FLAG_ADRDY_MST           ADCC_CSR_ADRDY_MST  /*!< ADC flag multimode master instance ready */
#define LL_ADC_FLAG_ADRDY_SLV           ADCC_CSR_ADRDY_SLV  /*!< ADC flag multimode slave instance ready */
#define LL_ADC_FLAG_EOC_MST             ADCC_CSR_EOC_MST    /*!< ADC flag multimode master group regular end
                                        of unitary conversion */
#define LL_ADC_FLAG_EOC_SLV             ADCC_CSR_EOC_SLV    /*!< ADC flag multimode slave group regular end
                                        of unitary conversion */
#define LL_ADC_FLAG_EOS_MST             ADCC_CSR_EOS_MST    /*!< ADC flag multimode master group regular end
                                        of sequence conversions */
#define LL_ADC_FLAG_EOS_SLV             ADCC_CSR_EOS_SLV    /*!< ADC flag multimode slave group regular end
                                        of sequence conversions */
#define LL_ADC_FLAG_OVR_MST             ADCC_CSR_OVR_MST    /*!< ADC flag multimode master group regular overrun */
#define LL_ADC_FLAG_OVR_SLV             ADCC_CSR_OVR_SLV    /*!< ADC flag multimode slave group regular overrun */
#define LL_ADC_FLAG_EOSMP_MST           ADCC_CSR_EOSMP_MST  /*!< ADC flag multimode master group regular end
                                        of sampling phase */
#define LL_ADC_FLAG_EOSMP_SLV           ADCC_CSR_EOSMP_SLV  /*!< ADC flag multimode slave group regular end
                                        of sampling phase */
#define LL_ADC_FLAG_JEOC_MST            ADCC_CSR_JEOC_MST   /*!< ADC flag multimode master group injected end
                                        of unitary conversion */
#define LL_ADC_FLAG_JEOC_SLV            ADCC_CSR_JEOC_SLV   /*!< ADC flag multimode slave group injected end
                                        of unitary conversion */
#define LL_ADC_FLAG_JEOS_MST            ADCC_CSR_JEOS_MST   /*!< ADC flag multimode master group injected end
                                        of sequence conversions */
#define LL_ADC_FLAG_JEOS_SLV            ADCC_CSR_JEOS_SLV   /*!< ADC flag multimode slave group injected end
                                        of sequence conversions */
#define LL_ADC_FLAG_JQOVF_MST           ADCC_CSR_JQOVF_MST  /*!< ADC flag multimode master group injected
                                        contexts queue overflow */
#define LL_ADC_FLAG_JQOVF_SLV           ADCC_CSR_JQOVF_SLV  /*!< ADC flag multimode slave group injected
                                        contexts queue overflow */
#define LL_ADC_FLAG_AWD1_MST            ADCC_CSR_AWD1_MST   /*!< ADC flag multimode master analog watchdog 1
                                        of the ADC master */
#define LL_ADC_FLAG_AWD1_SLV            ADCC_CSR_AWD1_SLV   /*!< ADC flag multimode slave analog watchdog 1
                                        of the ADC slave */
#define LL_ADC_FLAG_AWD2_MST            ADCC_CSR_AWD2_MST   /*!< ADC flag multimode master analog watchdog 2
                                        of the ADC master */
#define LL_ADC_FLAG_AWD2_SLV            ADCC_CSR_AWD2_SLV   /*!< ADC flag multimode slave analog watchdog 2
                                        of the ADC slave */
#define LL_ADC_FLAG_AWD3_MST            ADCC_CSR_AWD3_MST   /*!< ADC flag multimode master analog watchdog 3
                                        of the ADC master */
#define LL_ADC_FLAG_AWD3_SLV            ADCC_CSR_AWD3_SLV   /*!< ADC flag multimode slave analog watchdog 3
                                        of the ADC slave */
#define LL_ADC_FLAG_LDORDY_MST          ADCC_CSR_LDORDY_MST /*!< ADC flag internal voltage regulator (LDO) ready
                                        of the ADC master */
#define LL_ADC_FLAG_LDORDY_SLV          ADCC_CSR_LDORDY_SLV /*!< ADC flag internal voltage regulator (LDO) ready
                                        of the ADC slave */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_IT ADC interruptions for configuration (interruption enable or disable)
  * @brief    IT defines which can be used with LL_ADC_ReadReg and  LL_ADC_WriteReg functions
  * @{
  */
#define LL_ADC_IT_ADRDY                 ADC_IER_ADRDYIE    /*!< ADC interruption instance ready */
#define LL_ADC_IT_EOC                   ADC_IER_EOCIE      /*!< ADC interruption group regular end of
                                        unitary conversion */
#define LL_ADC_IT_EOS                   ADC_IER_EOSIE      /*!< ADC interruption group regular end of
                                        sequence conversions */
#define LL_ADC_IT_OVR                   ADC_IER_OVRIE      /*!< ADC interruption group regular overrun */
#define LL_ADC_IT_EOSMP                 ADC_IER_EOSMPIE    /*!< ADC interruption group regular end of
                                        sampling phase */
#define LL_ADC_IT_JEOC                  ADC_IER_JEOCIE     /*!< ADC interruption group injected end of
                                        unitary conversion */
#define LL_ADC_IT_JEOS                  ADC_IER_JEOSIE     /*!< ADC interruption group injected end of
                                        sequence conversions */
#define LL_ADC_IT_JQOVF                 ADC_IER_JQOVFIE    /*!< ADC interruption group injected
                                        contexts queue overflow */
#define LL_ADC_IT_AWD1                  ADC_IER_AWD1IE     /*!< ADC interruption analog watchdog 1 */
#define LL_ADC_IT_AWD2                  ADC_IER_AWD2IE     /*!< ADC interruption analog watchdog 2 */
#define LL_ADC_IT_AWD3                  ADC_IER_AWD3IE     /*!< ADC interruption analog watchdog 3 */
#define LL_ADC_IT_LDORDY                ADC_IER_LDORDYIE   /*!< ADC interruption internal voltage regulator(LDO) */

#define LL_ADC_IT_ALL                   (LL_ADC_IT_ADRDY \
                                         | LL_ADC_IT_EOC | LL_ADC_IT_EOS | LL_ADC_IT_OVR | LL_ADC_IT_EOSMP \
                                         | LL_ADC_IT_JEOC | LL_ADC_IT_JEOS | LL_ADC_IT_JQOVF \
                                         | LL_ADC_IT_AWD1 | LL_ADC_IT_AWD2 | LL_ADC_IT_AWD3 \
                                         | LL_ADC_IT_LDORDY) /*!< ADC all interruptions */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REGISTERS  ADC registers compliant with specific purpose
  * @{
  */
/* List of ADC registers intended to be used (most commonly) with             */
/* DMA transfer.                                                              */
/* Refer to function @ref LL_ADC_DMA_GetRegAddr().                            */
#define LL_ADC_DMA_REG_REGULAR_DATA     (0x00000000UL)    /* ADC group regular conversion data register
                                        (corresponding to register DR) to be used with ADC configured in independent
                                        mode.
                                        Without DMA transfer, register accessed by LL function
                                        @ref LL_ADC_REG_ReadConversionData32() and
                                        other functions LL_ADC_REG_ReadConversionDatax. */
#if defined(ADC_MULTIMODE_SUPPORT)
#define LL_ADC_DMA_REG_MM_REGULAR_PACK_DATA (0x00000001UL)  /* ADC multimode group regular conversion data register
                                        (corresponding to register CDR) to be used with ADC configured in multimode
                                        (availability depending on STM32 devices).
                                        Register with data packing: ADC master and slave data are concatenated
                                        in a single register, therefore constraint on data width.
                                        Data width depends on multimode configuration (refer to literals
                                        LL_ADC_MULTI_REG_DMA_RES_x).
                                        Without DMA transfer, register accessed by LL function
                                        @ref LL_ADC_REG_ReadMultiConversionData32().
                                        Note: For debug, caution when watching common data registers (CDR, CDR2)
                                              with a setup using DMA and data transfer mode unlimited (circular mode):
                                              unintended DMA transfer requests can be triggered. */

#define LL_ADC_DMA_REG_MM_REGULAR_UNPACK_DATA (0x00000002UL) /* ADC multimode group regular conversion data register
                                        (corresponding to register CDR2) to be used with ADC configured in multimode
                                        (availability depending on STM32 devices).
                                        Register without data packing: ADC master and slave data are alternatively set
                                        in full register width 32 bits, therefore no constraint on data width.
                                        Register intended to be used only with DMA transfer.
                                        Note: For debug, caution when watching common data registers (CDR, CDR2)
                                              with a setup using DMA and data transfer mode unlimited (circular mode):
                                              unintended DMA transfer requests can be triggered. */
#endif /* ADC_MULTIMODE_SUPPORT */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_COMMON_PATH_INTERNAL  ADC common - Measurement path to internal channels
  * @{
  */
/* Note: Other measurement paths to internal channels can be available (connections to other peripherals).
         If not listed below, they do not require any specific path enable. In this case, access to measurement path
         is done only by selecting the corresponding ADC internal channel. */
#define LL_ADC_PATH_INTERNAL_NONE       (0x00000000UL)     /*!< ADC measurement paths all disabled */
#define LL_ADC_PATH_INTERNAL_VREFINT    (ADCC_CCR_VREFEN)  /*!< ADC measurement path to internal channel VrefInt */
#define LL_ADC_PATH_INTERNAL_TEMPSENSOR (ADCC_CCR_TSEN)    /*!< ADC measurement path to internal channel
                                        temperature sensor */
#define LL_ADC_PATH_INTERNAL_VDDCORE    (ADC_OR_OP0 << LL_ADC_PATH_INTERNAL_POS) /*!< ADC measurement path to internal
                                        channel VddCore.
                                        Specific to ADC instance: ADC1, ADC2, ADC3. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_RESOLUTION  ADC instance - Resolution
  * @{
  */
#define LL_ADC_RESOLUTION_12B           (0x00000000UL) /*!< ADC resolution 12 bit */
#define LL_ADC_RESOLUTION_10B           (ADC_CFGR1_RES_0)  /*!< ADC resolution 10 bit */
#define LL_ADC_RESOLUTION_8B            (ADC_CFGR1_RES_1)  /*!< ADC resolution 8 bit */
#define LL_ADC_RESOLUTION_6B            (ADC_CFGR1_RES_1 | ADC_CFGR1_RES_0) /*!< ADC resolution 6 bit */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_LEFT_BIT_SHIFT   ADC left bit shift
  * @{
  */
#define LL_ADC_LEFT_BIT_SHIFT_NONE      (0x00000000UL)                              /*!< ADC conversion data not
                                        shifted (alignment right) */
#define LL_ADC_LEFT_BIT_SHIFT_1         (ADC_CFGR2_LSHIFT_0)                        /*!< ADC conversion data shift
                                        left of 1 bit (data multiplied by 2). */
#define LL_ADC_LEFT_BIT_SHIFT_2         (ADC_CFGR2_LSHIFT_1)                        /*!< ADC conversion data shift
                                        left of 2 bits (data multiplied by 4). */
#define LL_ADC_LEFT_BIT_SHIFT_3         (ADC_CFGR2_LSHIFT_1 | ADC_CFGR2_LSHIFT_0)   /*!< ADC conversion data shift
                                        left of 3 bits (data multiplied by 8). */
#define LL_ADC_LEFT_BIT_SHIFT_4         (ADC_CFGR2_LSHIFT_2)                        /*!< ADC conversion data shift
                                        left of 4 bits (data multiplied by 16). */
#define LL_ADC_LEFT_BIT_SHIFT_5         (ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_0)   /*!< ADC conversion data shift
                                        left of 5 bits (data multiplied by 32). */
#define LL_ADC_LEFT_BIT_SHIFT_6         (ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_1)   /*!< ADC conversion data shift
                                        left of 6 bits (data multiplied by 64). */
#define LL_ADC_LEFT_BIT_SHIFT_7         (ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_1 \
                                         | ADC_CFGR2_LSHIFT_0)                      /*!< ADC conversion data shift
                                        left of 7 bits (data multiplied by 128). */
#define LL_ADC_LEFT_BIT_SHIFT_8         (ADC_CFGR2_LSHIFT_3)                        /*!< ADC conversion data shift
                                        left of 8 bits (data multiplied by 256). */
#define LL_ADC_LEFT_BIT_SHIFT_9         (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_0)   /*!< ADC conversion data shift
                                        left of 9 bits (data multiplied by 512). */
#define LL_ADC_LEFT_BIT_SHIFT_10        (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_1)   /*!< ADC conversion data shift
                                        left of 10 bits (data multiplied by 1024). */
#define LL_ADC_LEFT_BIT_SHIFT_11        (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_1 \
                                         | ADC_CFGR2_LSHIFT_0)                      /*!< ADC conversion data shift
                                        left of 11 bits (data multiplied by 2048). */
#define LL_ADC_LEFT_BIT_SHIFT_12        (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2)   /*!< ADC conversion data shift
                                        left of 12 bits (data multiplied by 4096). */
#define LL_ADC_LEFT_BIT_SHIFT_13        (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2 \
                                         | ADC_CFGR2_LSHIFT_0)                      /*!< ADC conversion data shift
                                        left of 13 bits (data multiplied by 8192). */
#define LL_ADC_LEFT_BIT_SHIFT_14        (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2 \
                                         | ADC_CFGR2_LSHIFT_1)                      /*!< ADC conversion data shift
                                        left of 14 bits (data multiplied by 16384). */
#define LL_ADC_LEFT_BIT_SHIFT_15        (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2 \
                                         | ADC_CFGR2_LSHIFT_1 | ADC_CFGR2_LSHIFT_0) /*!< ADC conversion data shift
                                        left of 15 bits (data multiplied by 32768). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_LP_AUTO_WAIT  ADC instance - Low power auto wait
  * @{
  */
#define LL_ADC_LP_AUTO_WAIT_DISABLE     (0x00000000UL)   /*!< ADC low power mode auto delay disabled */
#define LL_ADC_LP_AUTO_WAIT_ENABLE      (ADC_CFGR1_AUTDLY) /*!< ADC low power mode auto delay enabled:
                                        dynamic low power mode, ADC conversions are performed only when necessary
                                        (when previous ADC conversion data is read). In the meantime, ADC remains idle:
                                        does not perform any other conversion.
                                        Note: This mode allows to automatically adapt the ADC conversions triggers
                                              to the speed of the software that reads the data.
                                              Moreover, this avoids risk of overrun for low frequency applications.
                                        Note: How to use this low power mode:
                                              - It is not recommended to use with interruption or DMA since these modes
                                                have to clear immediately EOC flag (by CPU to free the IRQ pending event
                                                or by DMA).
                                                Auto wait will work but fort a very short time, discarding its intended
                                                benefit (except specific case of high load of CPU or DMA transfers
                                                which can justify usage of auto wait).
                                              - Do use with polling:
                                                1. Start conversion,
                                                2. Later on, when conversion data is needed: poll for end of conversion
                                                   to ensure that conversion is completed and retrieve ADC conversion
                                                   data. This will trig another ADC conversion start.
                                        Note: With ADC low power mode "auto wait", the ADC conversion data read
                                              is corresponding to previous ADC conversion start, independently
                                              of delay during which ADC was idle.
                                              Therefore, the ADC conversion data can be outdated: does not correspond
                                              to the current voltage level on the selected ADC channel. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_LP_AUTO_WAIT_LEGACY  ADC instance - Low power auto wait legacy definitions
  * @{
  */
#define LL_ADC_LP_MODE_NONE             LL_ADC_LP_AUTO_WAIT_DISABLE /*!< Legacy definition, refer to main definition. */
#define LL_ADC_LP_AUTOWAIT              LL_ADC_LP_AUTO_WAIT_ENABLE /*!< Legacy definition, refer to main definition. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_SAMPLING_MODE  ADC instance - Sampling mode
  * @{
  */
#define LL_ADC_SAMPLING_MODE_NORMAL     (0x00000000UL) /*!< ADC conversions sampling phase duration
                                        is defined using @ref ADC_LL_EC_CHANNEL_SAMPLINGTIME. */
#define LL_ADC_SAMPLING_MODE_BULB       (ADC_CFGR2_BULB) /*!< ADC conversions sampling phase starts immediately
                                        after end of conversion, stops upon trigger event.
                                        Note: first conversion is using minimal sampling time
                                             (see @ref ADC_LL_EC_CHANNEL_SAMPLINGTIME).
                                        Note: Usable only if conversions from ADC group regular (not ADC group injected)
                                              and not in continuous mode. */
#define LL_ADC_SAMPLING_MODE_TRIGGER_CTRL (ADC_CFGR2_SMPTRIG) /*!< ADC conversions sampling phase is controlled
                                        by trigger events: trigger rising edge starts sampling,
                                        trigger falling edge stops sampling and start conversion.
                                        Note: Usable only if conversions from ADC group regular (not ADC group injected)
                                              and not in continuous mode. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_GROUPS  ADC instance - Groups
  * @{
  */
#define LL_ADC_GROUP_REGULAR            (0x00000001UL) /*!< ADC group regular (available on all STM32 devices) */
#define LL_ADC_GROUP_INJECTED           (0x00000002UL) /*!< ADC group injected (not available on all STM32 devices)*/
#define LL_ADC_GROUP_REGULAR_INJECTED   (0x00000003UL) /*!< ADC both groups regular and injected */
#define LL_ADC_GROUP_NONE               (0x00000000UL) /*!< ADC group none */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL  ADC instance - Channels
  * @{
  */
#define LL_ADC_CHANNEL_0                (0UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN0 */
#define LL_ADC_CHANNEL_1                (1UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN1 */
#define LL_ADC_CHANNEL_2                (2UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN2 */
#define LL_ADC_CHANNEL_3                (3UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN3 */
#define LL_ADC_CHANNEL_4                (4UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN4 */
#define LL_ADC_CHANNEL_5                (5UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN5 */
#define LL_ADC_CHANNEL_6                (6UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN6 */
#define LL_ADC_CHANNEL_7                (7UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN7 */
#define LL_ADC_CHANNEL_8                (8UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN8 */
#define LL_ADC_CHANNEL_9                (9UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN9 */
#define LL_ADC_CHANNEL_10               (10UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN10 */
#define LL_ADC_CHANNEL_11               (11UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN11 */
#define LL_ADC_CHANNEL_12               (12UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN12 */
#define LL_ADC_CHANNEL_13               (13UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN13 */
#define LL_ADC_CHANNEL_14               (14UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN14 */
#define LL_ADC_CHANNEL_15               (15UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN15 */
#define LL_ADC_CHANNEL_16               (16UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN16 */
#define LL_ADC_CHANNEL_17               (17UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< Channel ADCx_IN17 */
#define LL_ADC_CHANNEL_18               (18UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< channel ADCx_IN18 */
#define LL_ADC_CHANNEL_19               (19UL \
                                         | LL_ADC_CH_EXTERNAL | LL_ADC_PATH_INTERNAL_NONE) /*!< channel ADCx_IN19 */
#define LL_ADC_CHANNEL_VREFINT          (18UL \
                                         | LL_ADC_CH_INTERNAL_ADC1 | LL_ADC_CH_INTERNAL_ADC2 \
                                         | LL_ADC_CH_INTERNAL_ADC3 \
                                         | LL_ADC_PATH_INTERNAL_VREFINT) /*!< ADC channel to VrefInt (internal
                                        voltage reference).
                                        Common to all instances. */
#define LL_ADC_CHANNEL_TEMPSENSOR       (16UL \
                                         | LL_ADC_CH_INTERNAL_ADC1 \
                                         | LL_ADC_PATH_INTERNAL_TEMPSENSOR) /*!< ADC channel to internal temperature
                                        sensor.
                                        Specific to ADC instance: ADC1. */
#define LL_ADC_CHANNEL_VDDCORE          (17UL \
                                         | LL_ADC_CH_INTERNAL_ADC1 \
                                         | LL_ADC_CH_INTERNAL_ADC3 \
                                         | LL_ADC_PATH_INTERNAL_VDDCORE \
                                         | LL_ADC_CH_REMAP) /*!< ADC channel to
                                        VddCore (internal core voltage).
                                        Specific to ADC instance: ADC1, ADC2, ADC3.
                                        Note: Definition with channel number for ADC1.
                                              For other ADC instances, channel number is remapped
                                              through @ref LL_ADC_REMAP_CHANNEL_SET() in LL ADC functions. */
#define LL_ADC_CHANNEL_OPAMP1_OUT       (13UL \
                                         | LL_ADC_CH_INTERNAL_ADC1 \
                                         | LL_ADC_CH_INTERNAL_ADC3 \
                                         | LL_ADC_CH_REMAP) /*!< ADC channel OPAMP1 output.
                                        Specific to ADC instance: ADC1, ADC3.
                                        Note: Definition with channel number for ADC1.
                                              For other ADC instances, channel number is remapped
                                              through @ref LL_ADC_REMAP_CHANNEL_SET() in LL ADC functions. */
#define LL_ADC_CHANNEL_OPAMP2_OUT       (19UL \
                                         | LL_ADC_CH_INTERNAL_ADC1 \
                                         | LL_ADC_CH_INTERNAL_ADC2 \
                                         | LL_ADC_CH_REMAP) /*!< ADC channel OPAMP2 output.
                                        Specific to ADC instance: ADC1, ADC2.
                                        Note: Definition with channel number for ADC1.
                                              For other ADC instances, channel number is remapped
                                              through @ref LL_ADC_REMAP_CHANNEL_SET() in LL ADC functions. */
#define LL_ADC_CHANNEL_OPAMP3_OUT       (19UL \
                                         | LL_ADC_CH_INTERNAL_ADC2 \
                                         | LL_ADC_CH_INTERNAL_ADC3 \
                                         | LL_ADC_CH_REMAP) /*!< ADC channel OPAMP3 output.
                                        Specific to ADC instance: ADC2, ADC3.
                                        Note: Definition with channel number for ADC2.
                                              For other ADC instances, channel number is remapped
                                              through @ref LL_ADC_REMAP_CHANNEL_SET() in LL ADC functions. */
#define LL_ADC_CHANNEL_NONE             (ADC_CH_NONE_NUMBER      \
                                         | LL_ADC_CH_EXTERNAL       \
                                         | LL_ADC_PATH_INTERNAL_NONE) /*!< ADC no channel */
#define LL_ADC_CHANNEL_ALL              (ADC_CH_ALL_NUMBER       \
                                         | LL_ADC_CH_EXTERNAL       \
                                         | LL_ADC_PATH_INTERNAL_NONE) /*!< ADC all channels */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRIGGER_SOURCE  ADC group regular - Trigger source
  * @note     Triggers from timers capture compare are input capture or output capture.
  * @{
  */
#if !defined(ADC3)
/* Triggers common to all ADC instances (including devices featuring other ADC instances) */
#define LL_ADC_REG_TRIG_SOFTWARE        (0x00000000UL) /*!< ADC group regular conversion trigger internal: SW start. */
#define LL_ADC_REG_TRIG_TIM1_OC3        ((3UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM1 channel 3 event,
                                        (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM1_TRGO       ((4UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM1 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM1_TRGO2      ((5UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM1 TRGO2 event (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM2_TRGO       ((7UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM2 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM3_TRGO       ((9UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT \
                                         | LL_ADC_TRIG_OP5_RESET) /*!< ADC group regular conversion
                                        trigger from periph: TIM3 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM4_TRGO       ((9UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT \
                                         | LL_ADC_TRIG_OP5_SET) /*!< ADC group regular conversion
                                        trigger from periph: TIM4 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM6_TRGO       ((10UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM6 TRGO event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM20_TRGO      ((17UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM20 TRGO */
#define LL_ADC_REG_TRIG_TIM20_TRGO2     ((18UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM20 TRGO2 */
#define LL_ADC_REG_TRIG_TIM26_TRGO      ((19UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM26 TRGO  */
#define LL_ADC_REG_TRIG_LPTIM1_OC1      ((20UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: LPTIM1 channel 1  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG1     ((22UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: HRTIM1 ADC trigger 1  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG2     ((23UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: HRTIM1 ADC trigger 2  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG3     ((24UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: HRTIM1 ADC trigger 3  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG4     ((25UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: HRTIM1 ADC trigger 4  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG5     ((26UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: HRTIM1 ADC trigger 5  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG6     ((27UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: HRTIM1 ADC trigger 6  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG7     ((28UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: HRTIM1 ADC trigger 7  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG8     ((29UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: HRTIM1 ADC trigger 8  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG9     ((30UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: HRTIM1 ADC trigger 9  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG10    ((31UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: HRTIM trigger 10  */
#define LL_ADC_REG_TRIG_TIM8_TRGO       ((11UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM8 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM8_TRGO2      ((12UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM8 TRGO2 event (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM9_TRGO       ((13UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM9 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM15_TRGO      ((14UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM15 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM20_OC1       ((15UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM20 channel 1 event,
                                        (bitfield value for ADC1, ADC2) */
#define LL_ADC_REG_TRIG_TIM20_OC2       ((16UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM20 channel 2 event,
                                        (bitfield value for ADC1, ADC2) */

/* Triggers specific to ADC instances: ADC1, ADC2 (for other devices of series featuring instance ADC3) */
#define LL_ADC_REG_TRIG_EXTI11          ((0UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: EXTI line 11 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM1_OC1        ((1UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM1 channel 1 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM1_OC2        ((2UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM1 channel 2 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM2_OC2        ((6UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: TIM2 channel 2 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM3_OC4        ((8UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT \
                                         | LL_ADC_TRIG_OP4_RESET) /*!< ADC group regular conversion
                                        trigger from periph: TIM3 channel 4 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM4_OC4        ((8UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT \
                                         | LL_ADC_TRIG_OP4_SET) /*!< ADC group regular conversion
                                        trigger from periph: TIM4 channel 4 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_PLAY1_OUT11     ((21UL << ADC_CFGR1_EXTSEL_Pos) \
                                         | LL_ADC_REG_TRIG_EDGE_DEFAULT) /*!< ADC group regular conversion
                                        trigger from periph: PLAY1 out 11 event,
                                        specific to ADC instance: ADC1, ADC2. */
#else /* Manage trigger sources diversity across instances with look up table */
/* Triggers common to all ADC instances (including devices featuring other ADC instances) */
#define LL_ADC_REG_TRIG_SOFTWARE        (0xFFU) /*!< ADC group regular conversion trigger internal: SW start. */
#define LL_ADC_REG_TRIG_TIM1_TRGO       (0U) /*!< ADC group regular conversion trigger from periph: TIM1 TRGO */
#define LL_ADC_REG_TRIG_TIM1_TRGO2      (1U) /*!< ADC group regular conversion trigger from periph: TIM1 TRGO2 */
#define LL_ADC_REG_TRIG_TIM2_TRGO       (2U) /*!< ADC group regular conversion trigger from periph: TIM2 TRGO */
#define LL_ADC_REG_TRIG_TIM3_TRGO       (3U) /*!< ADC group regular conversion trigger from periph: TIM3 TRGO */
#define LL_ADC_REG_TRIG_TIM4_TRGO       (4U) /*!< ADC group regular conversion trigger from periph: TIM4 TRGO */
#define LL_ADC_REG_TRIG_TIM6_TRGO       (5U) /*!< ADC group regular conversion trigger from periph: TIM6 TRGO */
#define LL_ADC_REG_TRIG_TIM8_TRGO       (6U) /*!< ADC group regular conversion trigger from periph: TIM8 TRGO */
#define LL_ADC_REG_TRIG_TIM8_TRGO2      (7U) /*!< ADC group regular conversion trigger from periph: TIM8 TRGO2 */
#define LL_ADC_REG_TRIG_TIM9_TRGO       (8U) /*!< ADC group regular conversion trigger from periph: TIM9 TRGO */
#define LL_ADC_REG_TRIG_TIM15_TRGO      (9U) /*!< ADC group regular conversiontrigger from periph: TIM15 TRGO */
#define LL_ADC_REG_TRIG_TIM20_TRGO      (10U) /*!< ADC group regular conversion trigger from periph: TIM20 TRGO */
#define LL_ADC_REG_TRIG_TIM20_TRGO2     (11U) /*!< ADC group regular conversion trigger from periph: TIM20 TRGO2 */
#define LL_ADC_REG_TRIG_TIM26_TRGO      (12U) /*!< ADC group regular conversion trigger from periph: TIM26 TRGO  */
#define LL_ADC_REG_TRIG_HRTIM1_TRG1     (13U) /*!< ADC group regular conversion trigger from periph: HRTIM trigger 1 */
#define LL_ADC_REG_TRIG_HRTIM1_TRG2     (14U) /*!< ADC group regular conversion trigger from periph: HRTIM trigger 2 */
#define LL_ADC_REG_TRIG_HRTIM1_TRG3     (15U) /*!< ADC group regular conversion trigger from periph: HRTIM trigger 3 */
#define LL_ADC_REG_TRIG_HRTIM1_TRG4     (16U) /*!< ADC group regular conversion trigger from periph: HRTIM trigger 4 */
#define LL_ADC_REG_TRIG_HRTIM1_TRG5     (17U) /*!< ADC group regular conversion trigger from periph: HRTIM trigger 5 */
#define LL_ADC_REG_TRIG_HRTIM1_TRG6     (18U) /*!< ADC group regular conversion trigger from periph: HRTIM trigger 6 */
#define LL_ADC_REG_TRIG_HRTIM1_TRG7     (19U) /*!< ADC group regular conversion trigger from periph: HRTIM trigger 7 */
#define LL_ADC_REG_TRIG_HRTIM1_TRG8     (20U) /*!< ADC group regular conversion trigger from periph: HRTIM trigger 8 */
#define LL_ADC_REG_TRIG_HRTIM1_TRG9     (21U) /*!< ADC group regular conversion trigger from periph: HRTIM trigger 9 */
#define LL_ADC_REG_TRIG_HRTIM1_TRG10    (22U) /*!< ADC group regular conversion trigger from periph: HRTIM trigger 10*/
/* Triggers specific to ADC instances: ADC1, ADC2, ADC3 */
#define LL_ADC_REG_TRIG_TIM1_OC3        (23U) /*!< ADC group regular conversion trigger from periph: TIM1 channel 3 */
#define LL_ADC_REG_TRIG_LPTIM1_OC1      (24U) /*!< ADC group regular conversion trigger from periph: LPTIM1 channel 1 */
#define LL_ADC_REG_TRIG_TIM20_OC1       (25U) /*!< ADC group regular conversion trigger from periph: TIM20 channel 1
                                        */
/* Triggers specific to ADC instances: ADC1, ADC2 */
#define LL_ADC_REG_TRIG_EXTI11          (26U) /*!< ADC group regular conversion trigger from periph: EXTI line 11,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM1_OC1        (27U) /*!< ADC group regular conversion trigger from periph: TIM1 channel 1,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM1_OC2        (28U) /*!< ADC group regular conversion trigger from periph: TIM1 channel 2,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM2_OC2        (29U) /*!< ADC group regular conversion trigger from periph: TIM2 channel 2,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM3_OC4        (30U) /*!< ADC group regular conversion trigger from periph: TIM3 channel 4,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM4_OC4        (31U) /*!< ADC group regular conversion trigger from periph: TIM4 channel 4,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_REG_TRIG_TIM20_OC2       (32U) /*!< ADC group regular conversion trigger from periph: TIM20 channel 2 */
#define LL_ADC_REG_TRIG_PLAY1_OUT11     (33U) /*!< ADC group regular conversion trigger from periph: PLAY1 out 11,
                                        specific to ADC instance: ADC1, ADC2. */
#if defined(ADC3)
/* Triggers specific to ADC instances: ADC3 */
#define LL_ADC_REG_TRIG_EXTI2           (34U) /*!< ADC group regular conversion trigger from periph: EXTI line 2,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_REG_TRIG_TIM2_OC1        (35U) /*!< ADC group regular conversion trigger from periph: TIM2 channel 1,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_REG_TRIG_TIM2_OC3        (36U) /*!< ADC group regular conversion trigger from periph: TIM2 channel 3,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_REG_TRIG_TIM3_OC1        (37U) /*!< ADC group regular conversion trigger from periph: TIM3 channel 1,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_REG_TRIG_TIM3_OC2        (38U) /*!< ADC group regular conversion trigger from periph: TIM3 channel 2,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_REG_TRIG_TIM4_OC1        (39U) /*!< ADC group regular conversion trigger from periph: TIM4 channel 1,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_REG_TRIG_TIM8_OC1        (40U) /*!< ADC group regular conversion trigger from periph: TIM8 channel 1,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_REG_TRIG_PLAY1_OUT12     (41U) /*!< ADC group regular conversion trigger from periph: PLAY1 out 12,
                                        specific to ADC instance: ADC3. */
#endif /* ADC3 */
#endif /* ADC3 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRIGGER_EDGE  ADC group regular - Trigger edge
  * @{
  */
#define LL_ADC_REG_TRIG_RISING          (ADC_CFGR1_EXTEN_0)   /*!< ADC group regular conversion
                                        trigger polarity set to rising edge */
#define LL_ADC_REG_TRIG_FALLING         (ADC_CFGR1_EXTEN_1)   /*!< ADC group regular conversion
                                        trigger polarity set to falling edge */
#define LL_ADC_REG_TRIG_RISING_FALLING  (ADC_CFGR1_EXTEN_1 | ADC_CFGR1_EXTEN_0)  /*!< ADC group regular conversion
                                        trigger polarity set to both rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_CONTINUOUS_MODE  ADC group regular - Continuous mode
  * @{
  */
#define LL_ADC_REG_CONV_SINGLE          (0x00000000UL)   /*!< ADC conversions performed in single mode:
                                        conversions start from a trigger, are performed for each channel of
                                        the sequence, then stop. */
#define LL_ADC_REG_CONV_CONTINUOUS      (ADC_CFGR1_CONT) /*!< ADC conversions performed in continuous mode:
                                        conversions start from a trigger, are performed for each channel of
                                        the sequence, then restart automatically. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRANSFER_MODE  ADC group regular - Data transfer mode of ADC conversion data
  * @{
  */
#define LL_ADC_REG_TRANSFER_DR          (0x00000000UL) /*!< ADC conversion data available in
                                        data register only (not transferred to other peripheral).
                                        Note: conversion data can be retrieved
                                              using @ref LL_ADC_REG_ReadConversionData(). */
#define LL_ADC_REG_TRANSFER_DMA_LIMITED (ADC_CFGR1_DMNGT_0) /*!< ADC conversion data transferred by DMA,
                                        in limited mode (one shot mode): DMA transfer requests are stopped
                                        when number of DMA data transfers (number of ADC conversions) is reached.
                                        This ADC mode is intended to be used with DMA mode non-circular.
                                        Note: To configure DMA source address (peripheral address),
                                              use function @ref LL_ADC_DMA_GetRegAddr().*/
#define LL_ADC_REG_TRANSFER_DMA_UNLIMITED (ADC_CFGR1_DMNGT_1 | ADC_CFGR1_DMNGT_0) /*!< ADC conversion data
                                        transferred by DMA, in unlimited mode: DMA transfer requests are unlimited,
                                        whatever number of DMA data transferred(number of ADC conversions).
                                        This ADC mode is intended to be used with DMA mode circular.
                                        Note: If ADC DMA requests mode is set to unlimited and DMA is set to
                                              mode non-circular: when DMA transfers size will be reached,
                                              DMA will stop transfers of ADC conversions data ADC will raise
                                              an overrun event (overrun flag and interruption if enabled).
                                        Note: To configure DMA source address (peripheral address),
                                              use function @ref LL_ADC_DMA_GetRegAddr().*/
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRANSFER_LEGACY  ADC group regular - Data transfer mode legacy definitions
  * @{
  */
#define LL_ADC_REG_DR_TRANSFER          LL_ADC_REG_TRANSFER_DR /*!< Legacy definition, refer to main definition. */
#define LL_ADC_REG_DMA_TRANSFER_NONE    LL_ADC_REG_TRANSFER_DR /*!< Legacy definition, refer to main definition.*/
#define LL_ADC_REG_DMA_TRANSFER_LIMITED LL_ADC_REG_TRANSFER_DMA_LIMITED /*!< Legacy definition,
                                        refer to main definition. */
#define LL_ADC_REG_DMA_TRANSFER_UNLIMITED LL_ADC_REG_TRANSFER_DMA_UNLIMITED /*!< Legacy definition,
                                        refer to main definition. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_OVR_DATA_BEHAVIOR  ADC group regular - Overrun behavior on conversion data
  * @note     Overrun occurs when conversion is completed while conversion data in data register (from previous
  *           conversion) has not been fetched (by CPU or DMA).
  * @{
  */
#define LL_ADC_REG_OVR_DATA_PRESERVED   (0x00000000UL)      /*!< ADC group regular behavior in case of overrun:
                                        data preserved.
                                        Note: an internal FIFO of 8 elements in enabled in this mode. Overrun occurs
                                              when the FIFO overflows. FIFO is emptied by successive reads of
                                              data register. */
#define LL_ADC_REG_OVR_DATA_OVERWRITTEN (ADC_CFGR1_OVRMOD)  /*!< ADC group regular behavior in case of overrun:
                                        data overwritten */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_SCAN_LENGTH  ADC group regular - Sequencer scan length
  * @{
  */
#define LL_ADC_REG_SEQ_SCAN_DISABLE        (0x00000000UL) /*!< ADC group regular sequencer disable (equivalent to
                                        sequencer of 1 rank: ADC conversion on only 1 channel) */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS  (ADC_SQR1_LEN_0) /*!< ADC group regular sequencer enable
                                        with 2 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS  (ADC_SQR1_LEN_1) /*!< ADC group regular sequencer enable
                                        with 3 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS  (ADC_SQR1_LEN_1 | ADC_SQR1_LEN_0) /*!< ADC group regular sequencer enable
                                        with 4 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS  (ADC_SQR1_LEN_2) /*!< ADC group regular sequencer enable
                                        with 5 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS  (ADC_SQR1_LEN_2| ADC_SQR1_LEN_0) /*!< ADC group regular sequencer enable
                                        with 6 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS  (ADC_SQR1_LEN_2 | ADC_SQR1_LEN_1) /*!< ADC group regular sequencer enable
                                        with 7 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS  (ADC_SQR1_LEN_2 | ADC_SQR1_LEN_1 \
                                            | ADC_SQR1_LEN_0) /*!< ADC group regular sequencer enable
                                        with 8 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS  (ADC_SQR1_LEN_3) /*!< ADC group regular sequencer enable
                                        with 9 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS (ADC_SQR1_LEN_3| ADC_SQR1_LEN_0) /*!< ADC group regular sequencer enable
                                        with 10 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS (ADC_SQR1_LEN_3| ADC_SQR1_LEN_1) /*!< ADC group regular sequencer enable
                                        with 11 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS (ADC_SQR1_LEN_3| ADC_SQR1_LEN_1 \
                                            | ADC_SQR1_LEN_0) /*!< ADC group regular sequencer enable
                                        with 12 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS (ADC_SQR1_LEN_3 | ADC_SQR1_LEN_2) /*!< ADC group regular sequencer enable
                                        with 13 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS (ADC_SQR1_LEN_3 | ADC_SQR1_LEN_2 \
                                            | ADC_SQR1_LEN_0) /*!< ADC group regular sequencer enable
                                        with 14 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS (ADC_SQR1_LEN_3 | ADC_SQR1_LEN_2 \
                                            | ADC_SQR1_LEN_1) /*!< ADC group regular sequencer enable
                                        with 15 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS (ADC_SQR1_LEN_3 | ADC_SQR1_LEN_2 \
                                            | ADC_SQR1_LEN_1 | ADC_SQR1_LEN_0) /*!< ADC group regular sequencer enable
                                        with 16 ranks in the sequence */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_DISCONT_MODE  ADC group regular - Sequencer discontinuous mode
  * @{
  */
#define LL_ADC_REG_SEQ_DISCONT_DISABLE  (0x00000000UL)                               /*!< ADC group regular sequencer
                                        discontinuous mode disabled */
#define LL_ADC_REG_SEQ_DISCONT_1RANK    (ADC_CFGR1_DISCEN)                           /*!< ADC group regular sequencer
                                        discontinuous mode enabled with sequence interruption every rank */
#define LL_ADC_REG_SEQ_DISCONT_2RANKS   (ADC_CFGR1_DISCNUM_0 | ADC_CFGR1_DISCEN)     /*!< ADC group regular sequencer
                                        discontinuous mode enabled with sequence interruption every 2 ranks */
#define LL_ADC_REG_SEQ_DISCONT_3RANKS   (ADC_CFGR1_DISCNUM_1 | ADC_CFGR1_DISCEN)     /*!< ADC group regular sequencer
                                        discontinuous mode enabled with sequence interruption every 3 ranks */
#define LL_ADC_REG_SEQ_DISCONT_4RANKS   (ADC_CFGR1_DISCNUM_1 | ADC_CFGR1_DISCNUM_0 \
                                         | ADC_CFGR1_DISCEN)                          /*!< ADC group regular sequencer
                                        discontinuous mode enabled with sequence interruption every 4 ranks */
#define LL_ADC_REG_SEQ_DISCONT_5RANKS   (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCEN)     /*!< ADC group regular sequencer
                                        discontinuous mode enabled with sequence interruption every 5 ranks */
#define LL_ADC_REG_SEQ_DISCONT_6RANKS   (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCNUM_0 \
                                         | ADC_CFGR1_DISCEN)                          /*!< ADC group regular sequencer
                                        discontinuous mode enabled with sequence interruption every 6 ranks */
#define LL_ADC_REG_SEQ_DISCONT_7RANKS   (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCNUM_1 \
                                         | ADC_CFGR1_DISCEN)                          /*!< ADC group regular sequencer
                                        discontinuous mode enabled with sequence interruption every 7 ranks */
#define LL_ADC_REG_SEQ_DISCONT_8RANKS   (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCNUM_1 \
                                         | ADC_CFGR1_DISCNUM_0 | ADC_CFGR1_DISCEN)    /*!< ADC group regular sequencer
                                        discontinuous mode enabled with sequence interruption every 8 ranks */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_RANKS  ADC group regular - Sequencer ranks
  * @{
  */
#define LL_ADC_REG_RANK_1               (LL_ADC_SQR1_REGOFFSET | ADC_SQR1_SQ1_Pos)  /*!< ADC group regular sequencer
                                        rank 1 */
#define LL_ADC_REG_RANK_2               (LL_ADC_SQR1_REGOFFSET | ADC_SQR1_SQ2_Pos)  /*!< ADC group regular sequencer
                                        rank 2 */
#define LL_ADC_REG_RANK_3               (LL_ADC_SQR1_REGOFFSET | ADC_SQR1_SQ3_Pos)  /*!< ADC group regular sequencer
                                        rank 3 */
#define LL_ADC_REG_RANK_4               (LL_ADC_SQR1_REGOFFSET | ADC_SQR1_SQ4_Pos)  /*!< ADC group regular sequencer
                                        rank 4 */
#define LL_ADC_REG_RANK_5               (LL_ADC_SQR2_REGOFFSET | ADC_SQR2_SQ5_Pos)  /*!< ADC group regular sequencer
                                        rank 5 */
#define LL_ADC_REG_RANK_6               (LL_ADC_SQR2_REGOFFSET | ADC_SQR2_SQ6_Pos)  /*!< ADC group regular sequencer
                                        rank 6 */
#define LL_ADC_REG_RANK_7               (LL_ADC_SQR2_REGOFFSET | ADC_SQR2_SQ7_Pos)  /*!< ADC group regular sequencer
                                        rank 7 */
#define LL_ADC_REG_RANK_8               (LL_ADC_SQR2_REGOFFSET | ADC_SQR2_SQ8_Pos)  /*!< ADC group regular sequencer
                                        rank 8 */
#define LL_ADC_REG_RANK_9               (LL_ADC_SQR2_REGOFFSET | ADC_SQR2_SQ9_Pos)  /*!< ADC group regular sequencer
                                        rank 9 */
#define LL_ADC_REG_RANK_10              (LL_ADC_SQR3_REGOFFSET | ADC_SQR3_SQ10_Pos) /*!< ADC group regular sequencer
                                        rank 10 */
#define LL_ADC_REG_RANK_11              (LL_ADC_SQR3_REGOFFSET | ADC_SQR3_SQ11_Pos) /*!< ADC group regular sequencer
                                        rank 11 */
#define LL_ADC_REG_RANK_12              (LL_ADC_SQR3_REGOFFSET | ADC_SQR3_SQ12_Pos) /*!< ADC group regular sequencer
                                        rank 12 */
#define LL_ADC_REG_RANK_13              (LL_ADC_SQR3_REGOFFSET | ADC_SQR3_SQ13_Pos) /*!< ADC group regular sequencer
                                        rank 13 */
#define LL_ADC_REG_RANK_14              (LL_ADC_SQR3_REGOFFSET | ADC_SQR3_SQ14_Pos) /*!< ADC group regular sequencer
                                        rank 14 */
#define LL_ADC_REG_RANK_15              (LL_ADC_SQR4_REGOFFSET | ADC_SQR4_SQ15_Pos) /*!< ADC group regular sequencer
                                        rank 15 */
#define LL_ADC_REG_RANK_16              (LL_ADC_SQR4_REGOFFSET | ADC_SQR4_SQ16_Pos) /*!< ADC group regular sequencer
                                        rank 16 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIGGER_SOURCE  ADC group injected - Trigger source
  * @note     Triggers from timers capture compare are input capture or output capture.
  * @{
  */
#if !defined(ADC3)
/* Triggers common to all ADC instances (including devices featuring other ADC instances) */
#define LL_ADC_INJ_TRIG_SOFTWARE        (0x00000000UL) /*!< ADC group injected conversion trigger internal: SW start. */
#define LL_ADC_INJ_TRIG_TIM1_OC4        ((1UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM1 channel 4 event
                                        (bitfield value for ADC1, ADC2) */
#define LL_ADC_INJ_TRIG_TIM1_TRGO       ((2UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM1 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_INJ_TRIG_TIM1_TRGO2      ((3UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM1 TRGO2 event (bitfield value for ADC1, ADC2) */
#define LL_ADC_INJ_TRIG_TIM2_TRGO       ((5UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM2 TRGO  */
#define LL_ADC_INJ_TRIG_TIM7_TRGO       ((10UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM7 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_INJ_TRIG_TIM8_TRGO       ((12UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM8 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_INJ_TRIG_TIM8_TRGO2      ((13UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM8 TRGO2 event (bitfield value for ADC1, ADC2) */
#define LL_ADC_INJ_TRIG_TIM12_TRGO      ((14UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM12 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_INJ_TRIG_TIM15_TRGO      ((15UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM15 TRGO event (bitfield value for ADC1, ADC2) */
#define LL_ADC_INJ_TRIG_TIM16_OC1       ((16UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT \
                                         | LL_ADC_TRIG_OP7_RESET) /*!< ADC group injected conversion
                                        trigger from periph: TIM16 channel 1 event
                                        (bitfield value for ADC1, ADC2) */
#define LL_ADC_INJ_TRIG_TIM20_TRGO      ((17UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM20 TRGO event,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_INJ_TRIG_TIM20_TRGO2     ((18UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM20 TRGO2 event,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_INJ_TRIG_TIM27_TRGO      ((19UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM27 TRGO event,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_INJ_TRIG_LPTIM1_OC2      ((0UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: LPTIM1 channel 2 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG1     ((22UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: HRTIM1 ADC trigger 1 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG2     ((23UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: HRTIM1 ADC trigger 2 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG3     ((24UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: HRTIM1 ADC trigger 3 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG4     ((25UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: HRTIM1 ADC trigger 4 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG5     ((26UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: HRTIM1 ADC trigger 5 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG6     ((27UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: HRTIM1 ADC trigger 6 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG7     ((28UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: HRTIM1 ADC trigger 7 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG8     ((29UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: HRTIM1 ADC trigger 8 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG9     ((30UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: HRTIM1 ADC trigger 9 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG10    ((31UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: HRTIM1 ADC trigger 10 */

/* Triggers specific to ADC instances: ADC1, ADC2 (for other devices of series featuring instance ADC3) */
#define LL_ADC_INJ_TRIG_EXTI15          ((0UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: EXTI line 15 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_TIM2_OC1        ((4UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM2 channel 12 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_TIM3_OC1        ((6UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM3 channel 1 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_TIM3_OC3        ((7UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: TIM3 channel 3 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_TIM3_OC4        ((8UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT \
                                         | LL_ADC_TRIG_OP7_RESET) /*!< ADC group injected conversion
                                        trigger from periph: TIM3 channel 4 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_TIM3_TRGO       ((9UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT \
                                         | LL_ADC_TRIG_OP6_RESET) /*!< ADC group injected conversion
                                        trigger from periph: TIM3 TRGO event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_TIM4_TRGO       ((9UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT \
                                         | LL_ADC_TRIG_OP6_SET) /*!< ADC group injected conversion
                                        trigger from periph: TIM4 TRGO event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_TIM8_OC4        ((11UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT \
                                         | LL_ADC_TRIG_OP7_RESET) /*!< ADC group injected conversion
                                        trigger from periph: TIM8 channel 4 event,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_PLAY1_OUT13     ((21UL << ADC_JSQR_JEXTSEL_Pos) \
                                         | LL_ADC_INJ_TRIG_EDGE_DEFAULT) /*!< ADC group injected conversion
                                        trigger from periph: PLAY1 out 13 event,
                                        specific to ADC instance: ADC1, ADC2. */
#else /* Manage trigger sources diversity across instances with look up table */
/* Triggers common to all ADC instances (including devices featuring other ADC instances) */
#define LL_ADC_INJ_TRIG_SOFTWARE        (0xFFU) /*!< ADC group injected conversion trigger internal: SW start. */
#define LL_ADC_INJ_TRIG_TIM1_TRGO       (0U) /*!< ADC group injected conversion trigger from periph: TIM1 TRGO */
#define LL_ADC_INJ_TRIG_TIM1_TRGO2      (1U) /*!< ADC group injected conversion trigger from periph: TIM1 TRGO2 */
#define LL_ADC_INJ_TRIG_TIM2_TRGO       (2U) /*!< ADC group injected conversion trigger from periph: TIM2 TRGO */
#define LL_ADC_INJ_TRIG_TIM3_TRGO       (3U) /*!< ADC group injected conversion trigger from periph: TIM3 TRGO */
#define LL_ADC_INJ_TRIG_TIM4_TRGO       (4U) /*!< ADC group injected conversion trigger from periph: TIM4 TRGO */
#define LL_ADC_INJ_TRIG_TIM7_TRGO       (5U) /*!< ADC group injected conversion trigger from periph: TIM7 TRGO */
#define LL_ADC_INJ_TRIG_TIM8_TRGO       (6U) /*!< ADC group injected conversion trigger from periph: TIM8 TRGO */
#define LL_ADC_INJ_TRIG_TIM8_TRGO2      (7U) /*!< ADC group injected conversion trigger from periph: TIM8 TRGO2 */
#define LL_ADC_INJ_TRIG_TIM12_TRGO      (8U) /*!< ADC group injected conversion trigger from periph: TIM12 TRGO */
#define LL_ADC_INJ_TRIG_TIM15_TRGO      (9U) /*!< ADC group injected conversion trigger from periph: TIM15 TRGO */
#define LL_ADC_INJ_TRIG_TIM20_TRGO      (10U) /*!< ADC group injected conversion trigger from periph: TIM20 TRGO */
#define LL_ADC_INJ_TRIG_TIM20_TRGO2     (11U) /*!< ADC group injected conversiontrigger from periph: TIM20 TRGO2 */
#define LL_ADC_INJ_TRIG_TIM27_TRGO      (12U) /*!< ADC group injected conversion trigger from periph: TIM27 TRGO */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG1     (13U) /*!< ADC group injected conversion trigger from periph: HRTIM1
                                        trigger 1 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG2     (14U) /*!< ADC group injected conversion trigger from periph: HRTIM1
                                        trigger 2 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG3     (15U) /*!< ADC group injected conversion trigger from periph: HRTIM1
                                        trigger 3 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG4     (16U) /*!< ADC group injected conversion trigger from periph: HRTIM1
                                        trigger 4 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG5     (17U) /*!< ADC group injected conversion trigger from periph: HRTIM1
                                        trigger 5 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG6     (18U) /*!< ADC group injected conversion trigger from periph: HRTIM1
                                        trigger 6 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG7     (19U) /*!< ADC group injected conversion trigger from periph: HRTIM1
                                        trigger 7 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG8     (20U) /*!< ADC group injected conversion trigger from periph: HRTIM1
                                        trigger 8 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG9     (21U) /*!< ADC group injected conversion trigger from periph: HRTIM1
                                        trigger 9 */
#define LL_ADC_INJ_TRIG_HRTIM1_TRG10    (22U) /*!< ADC group injected conversion trigger from periph: HRTIM1
                                        trigger 10*/
/* Triggers specific to ADC instances: ADC1, ADC2, ADC3 */
#define LL_ADC_INJ_TRIG_TIM1_OC4        (23U) /*!< ADC group injected conversiontrigger from periph: TIM1 channel 4 */
#define LL_ADC_INJ_TRIG_TIM3_OC1        (24U) /*!< ADC group injected conversion trigger from periph: TIM3 channel 1 */
#define LL_ADC_INJ_TRIG_TIM4_OC3        (25U) /*!< ADC group injected conversion trigger from periph: TIM4 channel 3 */
#define LL_ADC_INJ_TRIG_TIM8_OC2        (26U) /*!< ADC group injected conversion trigger from periph: TIM8 channel 2 */
#define LL_ADC_INJ_TRIG_TIM8_OC4        (27U) /*!< ADC group injected conversion trigger from periph: TIM8 channel 2 */
#define LL_ADC_INJ_TRIG_TIM16_OC1       (28U) /*!< ADC group injected conversion trigger from periph: TIM3 channel 1 */
#define LL_ADC_INJ_TRIG_LPTIM1_OC2      (29U) /*!< ADC group injected conversion trigger from periph: LPTIM1 channel 2*/
/* Triggers specific to ADC instances: ADC1, ADC2 */
#define LL_ADC_INJ_TRIG_EXTI15          (30U) /*!< ADC group injected conversion trigger from periph: EXTI line 15,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_TIM2_OC1        (31U) /*!< ADC group injected conversion trigger from periph: TIM2 channel 12,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_TIM3_OC3        (32U) /*!< ADC group injected conversion trigger from periph: TIM3 channel 3,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_TIM3_OC4        (33U) /*!< ADC group injected conversion trigger from periph: TIM3 channel 4,
                                        specific to ADC instance: ADC1, ADC2. */
#define LL_ADC_INJ_TRIG_PLAY1_OUT13     (34U) /*!< ADC group injected conversion trigger from periph: PLAY1 out 13,
                                        specific to ADC instance: ADC1, ADC2. */
#if defined(ADC3)
/* Triggers specific to ADC instances: ADC3 */
#define LL_ADC_INJ_TRIG_EXTI3           (35U) /*!< ADC group injected conversion trigger from periph: EXTI
                                        line 3 event,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_INJ_TRIG_TIM1_OC3        (36U) /*!< ADC group injected conversion trigger from periph: TIM1 channel 3,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_INJ_TRIG_TIM17_OC1       (37U) /*!< ADC group injected conversion trigger from periph: TIM1 channel 3,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_INJ_TRIG_TIM20_OC2       (38U) /*!< ADC group injected conversion trigger from periph: TIM1 channel 3,
                                        specific to ADC instance: ADC3. */
#define LL_ADC_INJ_TRIG_PLAY1_OUT14     (39U) /*!< ADC group injected conversion trigger from periph: PLAY1 out 14,
                                        specific to ADC instance: ADC3. */
#endif /* ADC3 */
#endif /* ADC3 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIGGER_EDGE  ADC group injected - Trigger edge
  * @{
  */
#define LL_ADC_INJ_TRIG_RISING          (ADC_JSQR_JEXTEN_0) /*!< ADC group injected conversion trigger polarity
                                        set to rising edge */
#define LL_ADC_INJ_TRIG_FALLING         (ADC_JSQR_JEXTEN_1) /*!< ADC group injected conversion trigger polarity
                                        set to falling edge */
#define LL_ADC_INJ_TRIG_RISING_FALLING  (ADC_JSQR_JEXTEN_1 | ADC_JSQR_JEXTEN_0) /*!< ADC group injected conversion
                                        trigger polarity set to both rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIG_AUTO  ADC group injected - Automatic trigger mode
  * @{
  */
#define LL_ADC_INJ_TRIG_INDEPENDENT     (0x00000000UL)    /*!< ADC group injected conversion trigger independent.
                                        Setting mandatory if ADC group injected injected trigger source is set
                                        to an external trigger. */
#define LL_ADC_INJ_TRIG_FROM_REGULAR    (ADC_CFGR1_JAUTO) /*!< ADC group injected conversion trigger from ADC group
                                        regular. Setting compliant only with group injected trigger source set
                                        to SW start, without any further action on ADC group injected conversion
                                        start or stop: in this case, ADC group injected is controlled only
                                        from ADC group regular. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_QUEUE_CONTEXT  ADC group injected - Contexts queue mode
  * @{
  */
#define LL_ADC_INJ_QUEUE_DISABLE        (ADC_CFGR1_JQDIS) /* Group injected sequence contexts queue is disabled:
                                        disabled: only 1 sequence is configured and active permanently. */
#define LL_ADC_INJ_QUEUE_CTX_LAST_ACTIVE (0x00000000UL)   /* Group injected sequence contexts queue is
                                        enabled and can contain up to 2 contexts. When all contexts have been processed,
                                        the queue maintains the last context active permanently. */
#define LL_ADC_INJ_QUEUE_CTX_END_EMPTY  (ADC_CFGR1_JQM)   /* Group injected sequence contexts queue is
                                        enabled and can contain up to 2 contexts. When all contexts have been processed,
                                        the queue is empty and injected group trigger is disabled. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_SCAN_LENGTH  ADC group injected - Sequencer scan length
  * @{
  */
#define LL_ADC_INJ_SEQ_SCAN_DISABLE     (0x00000000UL)  /*!< ADC group injected sequencer disable (equivalent to
                                        sequencer of 1 rank: ADC conversion on only 1 channel) */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS (ADC_JSQR_JLEN_0) /*!< ADC group injected sequencer enable with 2 ranks
                                        in the sequence */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS (ADC_JSQR_JLEN_1) /*!< ADC group injected sequencer enable with 3 ranks
                                        in the sequence */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS (ADC_JSQR_JLEN_1 | ADC_JSQR_JLEN_0) /*!< ADC group injected sequencer enable
                                        with 4 ranks in the sequence */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_DISCONT_MODE  ADC group injected - Sequencer discontinuous mode
  * @{
  */
#define LL_ADC_INJ_SEQ_DISCONT_DISABLE  (0x00000000UL)      /*!< ADC group injected sequencer discontinuous mode
                                        disabled */
#define LL_ADC_INJ_SEQ_DISCONT_1RANK    (ADC_CFGR1_JDISCEN) /*!< ADC group injected sequencer discontinuous mode
                                        enabled with sequence interruption every rank */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_RANKS  ADC group injected - Sequencer ranks
  * @{
  */
#define LL_ADC_INJ_RANK_1               (LL_ADC_JDR1_REGOFFSET | ADC_JSQR_JSQ1_Pos) /*!< ADC group
                                        injected sequencer rank 1 */
#define LL_ADC_INJ_RANK_2               (LL_ADC_JDR2_REGOFFSET | ADC_JSQR_JSQ2_Pos) /*!< ADC group
                                        injected sequencer rank 2 */
#define LL_ADC_INJ_RANK_3               (LL_ADC_JDR3_REGOFFSET | ADC_JSQR_JSQ3_Pos) /*!< ADC group
                                        injected sequencer rank 3 */
#define LL_ADC_INJ_RANK_4               (LL_ADC_JDR4_REGOFFSET | ADC_JSQR_JSQ4_Pos) /*!< ADC group
                                        injected sequencer rank 4 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL_SAMPLINGTIME  Channel - Sampling time
  * @{
  */
#define LL_ADC_SAMPLINGTIME_2CYCLES_5   (0x00000000UL)         /*!< Sampling time 2.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_4CYCLES_5   (ADC_SMPR2_SMP10_0)    /*!< Sampling time 4.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_7CYCLES_5   (ADC_SMPR2_SMP10_1)    /*!< Sampling time 7.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_12CYCLES_5  (ADC_SMPR2_SMP10_1 \
                                         | ADC_SMPR2_SMP10_0)  /*!< Sampling time 12.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_24CYCLES_5  (ADC_SMPR2_SMP10_2)    /*!< Sampling time 24.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_47CYCLES_5  (ADC_SMPR2_SMP10_2 \
                                         | ADC_SMPR2_SMP10_0)  /*!< Sampling time 47.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_256CYCLES_5 (ADC_SMPR2_SMP10_2 \
                                         | ADC_SMPR2_SMP10_1)  /*!< Sampling time 256.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_848CYCLES_5 (ADC_SMPR2_SMP10_2 | ADC_SMPR2_SMP10_1 \
                                         | ADC_SMPR2_SMP10_0) /*!< Sampling time 848.5 ADC clock cycles */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL_IN_SINGLE_DIFF  Channel - Input mode (single ended, differential)
  * @{
  */
#define LL_ADC_IN_SINGLE_ENDED          (0x0000FFFFUL) /*!< ADC channel input set to single ended
                                        (literal also used to set calibration mode) */
#define LL_ADC_IN_DIFFERENTIAL          (0xFFFF0000UL) /*!< ADC channel input set to differential
                                        (literal also used to set calibration mode) */
#define LL_ADC_IN_SINGLE_DIFF           (LL_ADC_IN_SINGLE_ENDED \
                                         | LL_ADC_IN_DIFFERENTIAL) /*!< ADC channel input set to both single ended
                                        and differential (literal used only to set calibration factors) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL_IN_PSEUDO_DIFF  Channel - Differential input mode pseudo differential configuration
  * @note     Overrides differential mode for the entire ADC instance. If all channels
  *           are in single ended mode, this parameters has no effect.
  * @{
  */
#define LL_ADC_IN_PSEUDO_DIFF_DISABLE   (0x00000000UL) /*!< ADC channel input set to standard
                                        differential mode: ADC channel minus connected to ADCx_VINNy pin. */
#define LL_ADC_IN_PSEUDO_DIFF_VREFM     (ADC_CFGR2_PDIFF) /*!< ADC channel input set to pseudo
                                        differential mode with Vref-: overrides differential mode with
                                        ADC channel minus connected to Vref- voltage level. */
#define LL_ADC_IN_PSEUDO_DIFF_VREFP_2   (ADC_CFGR2_PDIFFREF | ADC_CFGR2_PDIFF) /*!< ADC channel input set to pseudo
                                        differential mode with Vref+/2: overrides differential mode with
                                        ADC channel minus connected to Vref+/2 voltage level. */
/**
  * @}
  */


/** @defgroup ADC_LL_EC_AWD_NB Analog watchdog - Analog watchdog instance
  * @{
  */
#define LL_ADC_AWD_1                    (LL_ADC_AWD_CR1_CHANNEL_MASK  | LL_ADC_AWD_CR1_REGOFFSET) /*!< ADC analog
                                        watchdog instance 1 */
#define LL_ADC_AWD_2                    (LL_ADC_AWD_CR23_CHANNEL_MASK | LL_ADC_AWD_CR2_REGOFFSET) /*!< ADC analog
                                        watchdog instance 2 */
#define LL_ADC_AWD_3                    (LL_ADC_AWD_CR23_CHANNEL_MASK | LL_ADC_AWD_CR3_REGOFFSET) /*!< ADC analog
                                        watchdog instance 3 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_THRESHOLDS  Analog watchdog - Thresholds
  * @{
  */
#define LL_ADC_AWD_THRESHOLD_HIGH       (0x1UL)                     /*!< ADC analog watchdog threshold high */
#define LL_ADC_AWD_THRESHOLD_LOW        (0x0UL)                     /*!< ADC analog watchdog threshold low */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_FILTERING_CONFIG  Analog watchdog - Filtering config
  * @{
  */
#define LL_ADC_AWD_FILTERING_NONE       (0x00000000UL)      /*!< ADC analog watchdog no filtering, one out-of-window
                                        sample is needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_2SAMPLES   (ADC_AWD1HTR_AWDFILT_0) /*!< ADC analog watchdog 2 consecutives out-of-window
                                        samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_3SAMPLES   (ADC_AWD1HTR_AWDFILT_1) /*!< ADC analog watchdog 3 consecutives out-of-window
                                        samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_4SAMPLES   (ADC_AWD1HTR_AWDFILT_1 | ADC_AWD1HTR_AWDFILT_0) /*!< ADC analog watchdog 4
                                        consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_5SAMPLES   (ADC_AWD1HTR_AWDFILT_2) /*!< ADC analog watchdog 5 consecutives out-of-window
                                        samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_6SAMPLES   (ADC_AWD1HTR_AWDFILT_2 | ADC_AWD1HTR_AWDFILT_0) /*!< ADC analog watchdog 6
                                        consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_7SAMPLES   (ADC_AWD1HTR_AWDFILT_2 | ADC_AWD1HTR_AWDFILT_1) /*!< ADC analog watchdog 7
                                        consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_8SAMPLES   (ADC_AWD1HTR_AWDFILT_2 | ADC_AWD1HTR_AWDFILT_1 \
                                         | ADC_AWD1HTR_AWDFILT_0) /*!< ADC analog watchdog 8 consecutives out-of-window
                                        samples are needed to raise flag or interrupt */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_INSTANCE  Oversampling - Oversampling instance
  * @{
  */
#define LL_ADC_OVS_1                    (0U) /*!< ADC oversampling instance for oversampling on
                                        group regular.
                                        Note: This device supports parallel injected oversampling, allowing to
                                              perform oversampling on groups regular and injected independently
                                              (different accumulators with their own settings ratio and shift). */
#define LL_ADC_OVS_INJ_1                (1U) /*!< ADC oversampling instance for oversampling on
                                        group injected.
                                        For constraints of oversampling on groups regular and injected,
                                        refer to parameters of ADC_LL_EC_OVS_SCOPE.
                                        Note: This device supports parallel injected oversampling, allowing to
                                              perform oversampling on groups regular and injected independently
                                              (different accumulators with their own settings ratio and shift).
                                        Note: Each injected data register has its own accumulator
                                              (common settings ratio and shift for all injected conversions). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_SCOPE  Oversampling - Oversampling scope
  * @{
  */
#define LL_ADC_OVS_DISABLE              (0x00000000UL) /*!< ADC oversampling disabled. */
#define LL_ADC_OVS_REG_CONTINUED        (ADC_CFGR2_ROVSE) /*!< ADC oversampling on conversions of
                                        ADC group regular.
                                        If ADC group injected conversion insertion within regular sequence: oversampling
                                        on group regular is temporary stopped and, after injected conversion, continued
                                        (oversampling accumulator maintained). */
#define LL_ADC_OVS_REG_RESUMED          (ADC_CFGR2_ROVSM | ADC_CFGR2_ROVSE) /*!< ADC oversampling on conversions of
                                        ADC group regular.
                                        If ADC group injected conversion insertion within regular sequence: after
                                        injected conversion, oversampling on group regular is resumed from start
                                        (oversampler accumulator reset). */
#define LL_ADC_OVS_INJ                  (LL_ADC_OVS_INJ_PARALLEL_SEQ) /*!< ADC oversampling on conversions of
                                        ADC group injected with extended features, sequential mode (legacy):
                                        oversampling conversions sequence sequential, switching data registers
                                        after each oversampling process (all ratio occurrences, shift).
                                        Note: This device supports parallel injected oversampling, allowing to
                                              perform oversampling on groups regular and injected independently
                                              (different accumulators with their own settings ratio and shift).
                                              To set parallel injected oversampling parameters, refer to functions
                                              LL_ADC_SetOverSamplingInj...(). */
#define LL_ADC_OVS_INJ_PARALLEL         (LL_ADC_OVS_INJ_PARALLEL_INTERL) /*!< ADC oversampling on conversions of
                                        ADC group injected with extended features, interleaved mode:
                                        oversampling conversions sequence interleaved, switching data registers
                                        after each unitary conversion.
                                        Note: This device supports parallel injected oversampling, allowing to
                                              perform oversampling on groups regular and injected independently
                                              (different accumulators with their own settings ratio and shift).
                                              To set parallel injected oversampling parameters, refer to functions
                                              LL_ADC_SetOverSamplingInj...(). */
#define LL_ADC_OVS_INJ_REG_RESUMED      (LL_ADC_OVS_REG_RESUMED | LL_ADC_OVS_INJ) /*!< ADC oversampling on conversions
                                        of ADC groups regular and injected.
                                        Combination of LL_ADC_OVS_REG_RESUMED and LL_ADC_OVS_INJ: refer to
                                        description of these parameters.
                                        Note: Can be used only with function @ref LL_ADC_SetOverSamplingScope().
                                              For configuration with accumulator explicit selection,
                                              refer to @ref LL_ADC_SetOverSamplingInstScope(), used with combination
                                              of regular and injected related parameters. */
#define LL_ADC_OVS_INJ_PARALL_REG_RESUM (LL_ADC_OVS_REG_RESUMED | LL_ADC_OVS_INJ_PARALLEL) /*!< ADC oversampling on
                                        conversions of ADC groups regular and injected.
                                        Combination of LL_ADC_OVS_REG_RESUMED and LL_ADC_OVS_INJ_PARALLEL: refer to
                                        description of these parameters.
                                        Note: Can be used only with function @ref LL_ADC_SetOverSamplingScope().
                                              For configuration with accumulator explicit selection,
                                              refer to @ref LL_ADC_SetOverSamplingInstScope(), used with combination
                                              of regular and injected related parameters. */
#define LL_ADC_OVS_INJ_PARALL_REG_CONT  (LL_ADC_OVS_REG_CONTINUED | LL_ADC_OVS_INJ_PARALLEL) /*!< ADC oversampling on
                                        conversions of ADC groups regular and injected.
                                        Combination of LL_ADC_OVS_REG_CONTINUED and LL_ADC_OVS_INJ_PARALLEL: refer to
                                        description of these parameters.
                                        Note: Can be used only with function @ref LL_ADC_SetOverSamplingScope().
                                              For configuration with accumulator explicit selection,
                                              refer to @ref LL_ADC_SetOverSamplingInstScope(), used with combination
                                              of regular and injected related parameters. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_DISCONT_MODE  Oversampling - Discontinuous mode (triggered mode)
  * @{
  */
#define LL_ADC_OVS_CONT                 (0x00000000UL)    /*!< ADC oversampling discontinuous mode: continuous mode
                                        (all conversions of oversampling ratio start from 1 trigger) */
#define LL_ADC_OVS_DISCONT              (ADC_CFGR2_TROVS) /*!< ADC oversampling discontinuous mode: discontinuous
                                        mode (each conversion of oversampling ratio needs a trigger)
                                        Note: Discontinuous mode applied only on group regular and parallel injected
                                              oversampling (not standard injected oversampling). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_SHIFT  Oversampling - Data shift
  * @{
  */
#define LL_ADC_OVS_SHIFT_NONE           (0UL) /*!< ADC oversampling no shift (no division) */
#define LL_ADC_OVS_SHIFT_RIGHT_1        (1UL) /*!< ADC oversampling shift of 1 (division by 2) */
#define LL_ADC_OVS_SHIFT_RIGHT_2        (2UL) /*!< ADC oversampling shift of 2 (division by 4) */
#define LL_ADC_OVS_SHIFT_RIGHT_3        (3UL) /*!< ADC oversampling shift of 3 (division by 8) */
#define LL_ADC_OVS_SHIFT_RIGHT_4        (4UL) /*!< ADC oversampling shift of 4 (division by 16) */
#define LL_ADC_OVS_SHIFT_RIGHT_5        (5UL) /*!< ADC oversampling shift of 5 (division by 32) */
#define LL_ADC_OVS_SHIFT_RIGHT_6        (6UL) /*!< ADC oversampling shift of 6 (division by 64) */
#define LL_ADC_OVS_SHIFT_RIGHT_7        (7UL) /*!< ADC oversampling shift of 7 (division by 128) */
#define LL_ADC_OVS_SHIFT_RIGHT_8        (8UL) /*!< ADC oversampling shift of 8 (division by 256) */
#define LL_ADC_OVS_SHIFT_RIGHT_9        (9UL) /*!< ADC oversampling shift of 9 (division by 512) */
#define LL_ADC_OVS_SHIFT_RIGHT_10       (10UL) /*!< ADC oversampling shift of 10 (division by 1024) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_INTERM_ACC  Oversampling - Intermediate accumulated values
  * @{
  */
#define LL_ADC_OVS_INTERM_ACC_DISABLE   (0x00000000UL) /*!< ADC oversampling intermediate accumulated values disable. */
#define LL_ADC_OVS_INTERM_ACC_ENABLE    (ADC_CFGR3_JOVSIVE) /*!< ADC oversampling intermediate accumulated values
                                        enable. When injected conversion is stopped, for each injected data register:
                                        - get intermediate accumulated value,
                                          refer to @ref LL_ADC_INJ_ReadConversionDataRank().
                                        - get intermediate accumulated data count,
                                          refer to @ref LL_ADC_INJ_ReadOVSIntermAccCount().
                                        Available only with parallel injected oversampling,
                                        refer to @ref LL_ADC_OVS_INJ_PARALLEL. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OFFSET_NB  ADC instance - Offset number
  * @{
  */
#define LL_ADC_OFFSET_1                 (LL_ADC_OFR1_REGOFFSET) /*!< ADC offset instance 1: ADC channel and offset level
                                        to which the offset programmed will be applied (independently of channel
                                        assigned on ADC group regular or injected sequencer) */
#define LL_ADC_OFFSET_2                 (LL_ADC_OFR2_REGOFFSET) /*!< ADC offset instance 2: ADC channel and offset level
                                        to which the offset programmed will be applied (independently of channel
                                        assigned on ADC group regular or injected sequencer) */
#define LL_ADC_OFFSET_3                 (LL_ADC_OFR3_REGOFFSET) /*!< ADC offset instance 3: ADC channel and offset level
                                        to which the offset programmed will be applied (independently of channel
                                        assigned on ADC group regular or injected sequencer) */
#define LL_ADC_OFFSET_4                 (LL_ADC_OFR4_REGOFFSET) /*!< ADC offset instance 4: ADC channel and offset level
                                        to which the offset programmed will be applied (independently of channel
                                        assigned on ADC group regular or injected sequencer) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OFFSET_SIGNED_SATURATION ADC instance - Offset signed saturation mode
  * @{
  */
#define LL_ADC_OFFSET_SIGNED_SATURATION_DISABLE   (0x00000000UL)     /*!< ADC offset signed saturation is disabled
                                        (among ADC selected offset number 1, 2, 3 or 4) */
#define LL_ADC_OFFSET_SIGNED_SATURATION_ENABLE    (ADC_OFCFGR_SSAT)  /*!< ADC offset signed saturation is enabled
                                        (among ADC selected offset number 1, 2, 3 or 4) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OFFSET_UNSIGNED_SATURATION ADC instance - Offset unsigned saturation mode
  * @{
  */
#define LL_ADC_OFFSET_UNSIGNED_SATURATION_DISABLE   (0x00000000UL)   /*!< ADC offset unsigned saturation is disabled
                                        (among ADC selected offset number 1, 2, 3 or 4) */
#define LL_ADC_OFFSET_UNSIGNED_SATURATION_ENABLE    (ADC_OFCFGR_USAT)  /*!< ADC offset unsigned saturation is enabled
                                        (among ADC selected offset number 1, 2, 3 or 4) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OFFSET_SIGN ADC instance - Offset sign
  * @{
  */
#define LL_ADC_OFFSET_SIGN_NEGATIVE     (0x00000000UL)       /*!< ADC offset is negative
                                        (among ADC selected offset number 1, 2, 3 or 4) */
#define LL_ADC_OFFSET_SIGN_POSITIVE     (ADC_OFCFGR_POSOFF)  /*!< ADC offset is positive
                                        (among ADC selected offset number 1, 2, 3 or 4) */
/**
  * @}
  */

#if defined(ADC_MULTIMODE_SUPPORT)
/** @defgroup ADC_LL_EC_MULTI_MODE  Multimode - Mode
  * @{
  */
#define LL_ADC_MULTI_INDEPENDENT        (0x00000000UL) /*!< ADC dual mode disabled (ADC independent mode) */
#define LL_ADC_MULTI_DUAL_REG_SIMULT    (ADCC_CCR_DUAL_2 | ADCC_CCR_DUAL_1) /*!< ADC dual mode enabled: group regular
                                        simultaneous */
#define LL_ADC_MULTI_DUAL_REG_INTERL    (ADCC_CCR_DUAL_2 | ADCC_CCR_DUAL_1 \
                                         | ADCC_CCR_DUAL_0) /*!< ADC dual mode enabled: Combined group regular
                                        interleaved */
#define LL_ADC_MULTI_DUAL_INJ_SIMULT    (ADCC_CCR_DUAL_2 | ADCC_CCR_DUAL_0) /*!< ADC dual mode enabled: group injected
                                        simultaneous */
#define LL_ADC_MULTI_DUAL_INJ_ALTERN    (ADCC_CCR_DUAL_3 | ADCC_CCR_DUAL_0) /*!< ADC dual mode enabled: group injected
                                        alternate trigger. Works only with external triggers (not SW start) */
#define LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM (ADCC_CCR_DUAL_0) /*!< ADC dual mode enabled: Combined group regular
                                        simultaneous + group injected simultaneous */
#define LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT (ADCC_CCR_DUAL_1) /*!< ADC dual mode enabled: Combined group regular
                                        simultaneous + group injected alternate trigger */
#define LL_ADC_MULTI_DUAL_REG_INT_INJ_SIM (ADCC_CCR_DUAL_1 | ADCC_CCR_DUAL_0) /*!< ADC dual mode enabled: Combined
                                        group regular interleaved + group injected simultaneous */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_MULTI_DMA_TRANSFER  Multimode - Data format
  * @{
  */
#define LL_ADC_MULTI_REG_DMA_EACH_ADC   (0x00000000UL)                      /*!< ADC multimode group regular
                                        data format: full range, no data packing.
                                        Intended for cases:
                                        - multimode without DMA transfer
                                        - multimode with DMA transfer in two different buffers.
                                        - high data width (can exceed ADC resolution in case of
                                          oversampling or post-processing) over data packing constraints.
                                        For no data transfer:
                                        - to retrieve conversion data, use @ref LL_ADC_REG_ReadConversionData32()
                                          with each ADC instance.
                                        For data transfer by DMA:
                                        - configure DMA to get data from register DR of ADC instance
                                          with @ref LL_ADC_DMA_GetRegAddr().
                                          Each ADC uses its own DMA channel, with its individual DMA transfer
                                          settings. Therefore, two destination buffers. */
#define LL_ADC_MULTI_REG_DMA_RES_32_16B (ADCC_CCR_DAMDF_1)                  /*!< ADC multimode group regular
                                        data format: full range and 2 data packing on 32 bits.
                                        Intended for cases:
                                        - multimode with DMA transfer in a single buffer.
                                        - high data width (can exceed ADC resolution in case of
                                          oversampling or post-processing) over data packing constraints.
                                        For no data transfer:
                                        - to retrieve conversion data, use @ref LL_ADC_REG_ReadMultiConversionData32()
                                          or @ref LL_ADC_REG_ReadConversionData32() with each ADC instance.
                                        For data transfer by DMA:
                                        - configure DMA to get data from register CDR or CDR2
                                          with @ref LL_ADC_DMA_GetRegAddr().
                                        Note: conversion data in two ADC common instance data registers
                                              (CDR, CDR2) with packing option on 32 bits.
                                              - Register CDR: data packing on 32 bits: ADC master and slave data
                                                are concatenated (data master in [15; 0], data slave in [31; 16]),
                                                therefore data width must be lower than 16 bits (can exceed ADC
                                                resolution with post-processing: oversampling, offset, ...).
                                              - Register CDR2: data of master and slave are alternatively set in full
                                                register width 32 bits, therefore no constraint on data width.
                                                In case of usage with DMA, CDR generates one transfer request
                                                and CDR2 two transfer requests per conversion. */
#define LL_ADC_MULTI_REG_DMA_RES_8B     (ADCC_CCR_DAMDF_1 | ADCC_CCR_DAMDF_0) /*!< ADC multimode group regular
                                        data format: full range and 2 data packing on 16 bits.
                                        Intended for cases:
                                        - multimode with DMA transfer in a single buffer with elements 16 bits.
                                        For no data transfer:
                                        - to retrieve conversion data, use @ref LL_ADC_REG_ReadConversionData32()
                                          with each ADC instance.
                                        For data transfer by DMA:
                                        - configure DMA to get data from register CDR or CDR2
                                          with @ref LL_ADC_DMA_GetRegAddr().
                                        Note: conversion data in two ADC common instance data registers
                                              (CDR, CDR2) with packing option on 16 bits.
                                              - Register CDR: data packing on 16 bits: ADC master and slave data
                                                are concatenated (data master in [7; 0], data slave in [15; 8]),
                                                therefore data width must be lower than 8 bits (can exceed ADC
                                                resolution with post-processing: oversampling, offset, ...).
                                              - Register CDR2: data of master and slave are alternatively set in full
                                                register width 32 bits, therefore no constraint on data width.
                                                In case of usage with DMA, CDR generates one transfer request
                                                and CDR2 two transfer requests per conversion. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_MULTI_TWOSMP_DELAY  Multimode - Delay between two sampling phases (for mode interleaved)
  * @{
  */
#define LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE (0x00000000UL) /*!< ADC multimode (mode interleaved)
                                        delay between two sampling phases: 1 ADC clock cycle for all resolutions */
#define LL_ADC_MULTI_TWOSMP_DELAY_2CYCLES (ADCC_CCR_DELAY_0) /*!< ADC multimode (mode interleaved)
                                        delay between two sampling phases: 2 ADC clock cycles for all resolutions */
#define LL_ADC_MULTI_TWOSMP_DELAY_3CYCLES (ADCC_CCR_DELAY_1) /*!< ADC multimode (mode interleaved)
                                        delay between two sampling phases: 3 ADC clock cycles for all resolutions */
#define LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES (ADCC_CCR_DELAY_1 | ADCC_CCR_DELAY_0) /*!< ADC multimode (mode interleaved)
                                        delay between two sampling phases: 4 ADC clock cycles for all resolutions */
#define LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES (ADCC_CCR_DELAY_2) /*!< ADC multimode (mode interleaved)
                                        delay between two sampling phases: 5 ADC clock cycles for all resolutions */
#define LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES (ADCC_CCR_DELAY_2 | ADCC_CCR_DELAY_0) /*!< ADC multimode (mode interleaved)
                                        delay between two sampling phases: 6 ADC clock cycles for all resolutions */
#define LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES (ADCC_CCR_DELAY_2 | ADCC_CCR_DELAY_1) /*!< ADC multimode (mode interleaved)
                                        delay between two sampling phases: 7 ADC clock cycles for all resolutions */
#define LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES (ADCC_CCR_DELAY_2 | ADCC_CCR_DELAY_1 \
                                           | ADCC_CCR_DELAY_0) /*!< ADC multimode (mode interleaved
                                        delay between two sampling phases: 8 ADC clock cycles
                                        for resolution 12, 10, 8 bit */
#define LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES (ADCC_CCR_DELAY_3) /*!< ADC multimode (mode interleaved
                                        delay between two sampling phases: 9 ADC clock cycles
                                        for resolution 12, 10, 8 bit */
#define LL_ADC_MULTI_TWOSMP_DELAY_10CYCLES (ADCC_CCR_DELAY_3 | ADCC_CCR_DELAY_0) /*!< ADC multimode (mode interleaved
                                        delay between two sampling phases: 10 ADC clock cycles
                                        for resolution 12, 10 bit */
#define LL_ADC_MULTI_TWOSMP_DELAY_11CYCLES (ADCC_CCR_DELAY_3 | ADCC_CCR_DELAY_1) /*!< ADC multimode (mode interleaved
                                        delay between two sampling phases: 11 ADC clock cycles
                                        for resolution 12, 10 bit */
#define LL_ADC_MULTI_TWOSMP_DELAY_12CYCLES (ADCC_CCR_DELAY_3 | ADCC_CCR_DELAY_1 \
                                            | ADCC_CCR_DELAY_0) /*!< ADC multimode (mode interleaved
                                        delay between two sampling phases: 12 ADC clock cycles for resolution 12 bit */
#define LL_ADC_MULTI_TWOSMP_DELAY_13CYCLES (ADCC_CCR_DELAY_3 | ADCC_CCR_DELAY_2) /*!< ADC multimode (mode interleaved)
                                        delay between two sampling phases: 13 ADC clock cycles for resolution 12 bit */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_MULTI_MASTER_SLAVE  Multimode - ADC master or slave
  * @{
  */
#define LL_ADC_MULTI_MASTER             (ADCC_CDR_RDATA_MST) /*!< In multimode, selection among several ADC instances:
                                        ADC master */
#define LL_ADC_MULTI_SLAVE              (ADCC_CDR_RDATA_SLV) /*!< In multimode, selection among several ADC instances:
                                        ADC slave */
#define LL_ADC_MULTI_MASTER_SLAVE       (ADCC_CDR_RDATA_SLV | ADCC_CDR_RDATA_MST) /*!< In multimode, selection among
                                        several ADC instances: both ADC master and ADC slave */
/**
  * @}
  */

#endif /* ADC_MULTIMODE_SUPPORT */

/** @defgroup ADC_LL_EC_HW_DELAYS  Definitions of ADC hardware constraints delays
  * @note   Only ADC peripheral HW delays are defined in ADC LL driver driver, not timeout values.
  * @note   Timeout values for ADC operations are dependent to device clock configuration (system clock versus
  *         ADC clock), and therefore must be defined in user application.
  *         Indications for estimation of ADC timeout delays, for this STM32 series:
  *         - ADC calibration time: maximum delay is 16384/fADC (refer to device datasheet, parameter "tCAL")
  *         - ADC enable time: maximum delay is 1 conversion cycle (refer to device datasheet, parameter "tSTAB")
  *         - ADC disable time: maximum delay is few ADC clock cycles
  *         - ADC stop conversion time: maximum delay is few ADC clock cycles
  *         - ADC conversion time: duration depending on ADC clock and ADC configuration (refer to device
  *           reference manual, section "Timing")
  * @{
  */
#define LL_ADC_DELAY_INTERNAL_REGUL_STAB_US ( 10UL) /*!< Delay for ADC stabilization time (ADC voltage regulator
                                        start-up time).
                                        Delay set to maximum value (refer to device datasheet,
                                        parameter "tADCVREG_STUP").
                                        Unit: us */

#define LL_ADC_DELAY_VREFINT_STAB_US    (5UL) /*!< Delay for internal voltage reference stabilization time.
                                        Delay set to maximum value (refer to device datasheet,
                                        parameter "tstart_vrefint").
                                        Unit: us */

#define LL_ADC_DELAY_TEMPSENSOR_STAB_US (25UL) /*!< Delay for temperature sensor stabilization time.
                                        Literal set to maximum value (refer to device datasheet, parameter "tSTART").
                                        Unit: us */

#define LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES (4UL) /*!< Delay required between ADC end of calibration and ADC enable.
                                        Note: On this STM32 series, a minimum number of ADC clock cycles are required
                                              between ADC end of calibration and ADC enable.
                                              Wait time can be computed in user application by waiting for the
                                              equivalent number of CPU cycles, by taking into account ratio of CPU clock
                                              versus ADC clock prescalers.
                                        Unit: ADC clock cycles. */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Macros LL ADC Macros
  * @{
  */

/** @defgroup ADC_LL_EM_WRITE_READ Common write and read registers macro
  * @{
  */

/**
  * @brief  Write a value in ADC register.
  * @param  instance ADC Instance
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_ADC_WRITE_REG(instance, reg, value) STM32_WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in ADC register.
  * @param  instance ADC Instance
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_ADC_READ_REG(instance, reg) STM32_READ_REG((instance)->reg)
/**
  * @}
  */

/** @defgroup ADC_LL_EM_HELPER_MACRO ADC helper macro
  * @{
  */

/**
  * @brief  Helper macro to get ADC channel number in decimal format
  *         from literals LL_ADC_CHANNEL_x.
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   Example:
  *           LL_ADC_CHANNEL_TO_DECIMAL_NB(LL_ADC_CHANNEL_4)
  *           will return decimal number "4".
  * @note   The input can be a value from functions where a channel
  *         number is returned, either defined with number
  *         or with bitfield (only one bit must be set).
  * @retval Value between Min_Data=0 and Max_Data=19
  */
#define LL_ADC_CHANNEL_TO_DECIMAL_NB(channel)  ((channel) & LL_ADC_CH_NUMBER_MASK)

/**
  * @brief  Helper macro to get ADC channel in literal format LL_ADC_CHANNEL_x
  *         from number in decimal format.
  * @param  decimal_nb Value between Min_Data=0 and Max_Data=19
  * @note   Example:
  *           LL_ADC_DECIMAL_NB_TO_CHANNEL(4)
  *           will return a data equivalent to "LL_ADC_CHANNEL_4".
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  */
#define LL_ADC_DECIMAL_NB_TO_CHANNEL(decimal_nb) (decimal_nb)

/**
  * @brief  Helper macro to determine whether the selected channel
  *         corresponds to literal definitions of driver.
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   The different literal definitions of ADC channels are:
  *         - ADC internal channel:
  *           LL_ADC_CHANNEL_VREFINT, LL_ADC_CHANNEL_TEMPSENSOR, ...
  *         - ADC external channel (channel connected to a GPIO pin):
  *           LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...
  * @note   The channel parameter must be a value defined from literal
  *         definition of a ADC internal channel (LL_ADC_CHANNEL_VREFINT,
  *         LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         ADC external channel (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...),
  *         must not be a value from functions where a channel number is
  *         returned from ADC registers,
  *         because internal and external channels share the same channel
  *         number in ADC registers. The differentiation is made only with
  *         parameters definitions of driver.
  * @retval Value "0" if the channel corresponds to a parameter definition of a ADC external channel
  *         (channel connected to a GPIO pin).
  *         Value "1" if the channel corresponds to a parameter definition of a ADC internal channel.
  */
#define LL_ADC_IS_CHANNEL_INTERNAL(channel) (((channel) & LL_ADC_CH_INTERNAL_MASK) != 0UL)

/**
  * @brief  Helper macro to convert a channel defined from parameter
  *         definition of a ADC internal channel (LL_ADC_CHANNEL_VREFINT,
  *         LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         to its equivalent parameter definition of a ADC external channel
  *         (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...).
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  * @note   The channel parameter can be, additionally to a value
  *         defined from parameter definition of a ADC internal channel
  *         (LL_ADC_CHANNEL_VREFINT, LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         a value defined from parameter definition of
  *         ADC external channel (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...)
  *         or a value from functions where a channel number is returned
  *         from ADC registers.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  */
#define LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL(channel) ((channel) & LL_ADC_CH_NUMBER_MASK)

/**
  * @brief Helper macro to remap internal channels to their alternative channel number
  *        when they are shared on several instances with different numbers.
  * @param instance ADC instance
  * @param channel ADC channel
  * @retval Remapped channel number if applicable, else same channel number as input
  * @note   Returned value is channel number only, without other metadata of LL_ADC_CHANNEL_x definition.
  */
__STATIC_INLINE uint32_t LL_ADC_REMAP_CHANNEL_SET(const ADC_TypeDef *instance, uint32_t channel)
{
  /* Look up tables of ADC channels to be remapped in function of ADC instances
     Note: Indexes correspond to ADC instances ordered (refer to LL_ADC_INSTANCE_LUT_INDEX()).
     Note: Value 0xFF for channel not available. */
#if defined(ADC3)
  static const uint8_t LL_ADC_REMAP_CHANNEL_VDDCORE_LUT[] = {17U, 10U, 10U};
  static const uint8_t LL_ADC_REMAP_CHANNEL_OPAMP1_OUT_LUT[] = {13U, 0xFFU, 19U};
  static const uint8_t LL_ADC_REMAP_CHANNEL_OPAMP2_OUT_LUT[] = {19U, 16U, 0xFFU};
  static const uint8_t LL_ADC_REMAP_CHANNEL_OPAMP3_OUT_LUT[] = {0xFFU, 19U, 13U};
#else
  static const uint8_t LL_ADC_REMAP_CHANNEL_VDDCORE_LUT[] = {17U, 10U};
  static const uint8_t LL_ADC_REMAP_CHANNEL_OPAMP2_OUT_LUT[] = {19U, 16U};
#endif /* ADC3 */

  uint32_t channel_remapped;

  if ((channel & LL_ADC_CH_REMAP) != 0U)
  {
    uint32_t adc_instance_lut_index = (uint32_t)LL_ADC_INSTANCE_LUT_INDEX(instance);

    if (channel == LL_ADC_CHANNEL_VDDCORE)
    {
      channel_remapped = LL_ADC_REMAP_CHANNEL_VDDCORE_LUT[adc_instance_lut_index];
    }
    else
    {
#if defined(ADC3)
      if (channel == LL_ADC_CHANNEL_OPAMP1_OUT)
      {
        channel_remapped = LL_ADC_REMAP_CHANNEL_OPAMP1_OUT_LUT[adc_instance_lut_index];
      }
      else
      {
        if (channel == LL_ADC_CHANNEL_OPAMP2_OUT)
        {
          channel_remapped = LL_ADC_REMAP_CHANNEL_OPAMP2_OUT_LUT[adc_instance_lut_index];
        }
        else /* LL_ADC_CHANNEL_OPAMP3_OUT */
        {
          channel_remapped = LL_ADC_REMAP_CHANNEL_OPAMP3_OUT_LUT[adc_instance_lut_index];
        }
      }
#else
      channel_remapped = LL_ADC_REMAP_CHANNEL_OPAMP2_OUT_LUT[adc_instance_lut_index];
#endif /* ADC3 */
    }
  }
  else
  {
    channel_remapped = channel;
  }

  return channel_remapped;
}

/**
  * @brief Helper macro to remap internal channels from their alternative channel number
  *        when they are shared on several instances with different numbers.
  * @param instance ADC instance
  * @param channel ADC channel
  * @retval Remapped channel number if applicable, else same channel number as input
  * @note   Returned value is channel number only, without other metadata of LL_ADC_CHANNEL_x definition.
  */
__STATIC_INLINE uint32_t LL_ADC_REMAP_CHANNEL_GET(const ADC_TypeDef *instance, uint32_t channel)
{
  /* Look up tables of ADC channels to be remapped in function of ADC instances
     Note: Indexes correspond to ADC instances ordered (refer to LL_ADC_INSTANCE_LUT_INDEX()).
     Note: Value 0xFF for channel not available. */
#if defined(ADC3)
  static const uint8_t LL_ADC_REMAP_CHANNEL_10[] = {10U, 17U, 17U}; /* ADC2-3 ch16: VDDCORE defined with ADC1 ch17 */
  static const uint8_t LL_ADC_REMAP_CHANNEL_16[] = {16U, 19U, 16U}; /* ADC2 ch16: OPAMP2_OUT defined with ADC1 ch19 */
  static const uint8_t LL_ADC_REMAP_CHANNEL_13[] = {13U, 13U, 19U}; /* ADC3 ch13: OPAMP3_OUT defined with ADC2 ch19 */
  static const uint8_t LL_ADC_REMAP_CHANNEL_19[] = {19U, 19U, 13U}; /* ADC3 ch19: OPAMP1_OUT defined with ADC1 ch13 */
#else
  static const uint8_t LL_ADC_REMAP_CHANNEL_10[] = {10U, 17U}; /* ADC2 ch16: VDDCORE defined with ADC1 ch17 */
  static const uint8_t LL_ADC_REMAP_CHANNEL_16[] = {16U, 19U}; /* ADC2 ch16: OPAMP2_OUT defined with ADC1 ch19 */
#endif /* ADC3 */

  uint32_t channel_remapped;
  /* Use channel number without other metadata of LL_ADC_CHANNEL_x definition for usage with LL functions
     retrieving only channel number */
  uint32_t channel_nb = LL_ADC_CHANNEL_TO_DECIMAL_NB(channel);

  if (instance == ADC1)
  {
    /* Channels numbers definitions corresponding to ADC1: no remap needed */
    channel_remapped = channel;
  }
  else
  {
    uint32_t adc_instance_lut_index = (uint32_t)LL_ADC_INSTANCE_LUT_INDEX(instance);

    if (channel_nb == 10U)
    {
      channel_remapped = LL_ADC_REMAP_CHANNEL_10[adc_instance_lut_index];
    }
    else
    {
      if (channel_nb == 16U)
      {
        channel_remapped = LL_ADC_REMAP_CHANNEL_16[adc_instance_lut_index];
      }
      else
      {
#if defined(ADC3)
        if (channel_nb == 13U)
        {
          channel_remapped = LL_ADC_REMAP_CHANNEL_13[adc_instance_lut_index];
        }
        else
        {
          if (channel_nb == 19U)
          {
            channel_remapped = LL_ADC_REMAP_CHANNEL_19[adc_instance_lut_index];
          }
          else
          {
            channel_remapped = channel;
          }
        }
#else
        channel_remapped = channel;
#endif /* ADC3 */
      }
    }
  }

  return channel_remapped;
}

/**
  * @brief  Helper macro to determine, from a selected channel in differential mode (positive input),
  *         the corresponding negative input.
  * @param  instance ADC instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  */
__STATIC_INLINE uint8_t LL_ADC_CHANNEL_DIFF_NEG_INPUT(ADC_TypeDef *instance, uint32_t channel)
{
  /* ADC differential channels related definitions */
  static const uint8_t LL_ADC_CHANNEL_DIFF_LUT[3][(LL_ADC_CH_NUMBER_RANGE_MAX + 3UL)] =
  {
    {
      (uint8_t)(LL_ADC_CHANNEL_1),        /*!< Channel ADCx_INN0  -> ADCx_INP1  */
      (uint8_t)(LL_ADC_CHANNEL_2),        /*!< Channel ADCx_INN1  -> ADCx_INP2  */
      (uint8_t)(LL_ADC_CHANNEL_3),        /*!< Channel ADCx_INN2  -> ADCx_INP3  */
      (uint8_t)(LL_ADC_CHANNEL_4),        /*!< Channel ADCx_INN3  -> ADCx_INP4  */
      (uint8_t)(LL_ADC_CHANNEL_5),        /*!< Channel ADCx_INN4  -> ADCx_INP8  */
      (uint8_t)(LL_ADC_CHANNEL_6),        /*!< Channel ADCx_INN5  -> ADCx_INP9  */
      (uint8_t)(LL_ADC_CHANNEL_7),        /*!< Channel ADCx_INN6  -> ADCx_INP9  */
      (uint8_t)(LL_ADC_CHANNEL_8),        /*!< Channel ADCx_INN7  -> ADCx_INP9  */
      (uint8_t)(LL_ADC_CHANNEL_9),        /*!< Channel ADCx_INN8  -> ADCx_INP9  */
      (uint8_t)(LL_ADC_CHANNEL_10),       /*!< Channel ADCx_INN9  -> ADCx_INP9  */
      (uint8_t)(LL_ADC_CHANNEL_11),       /*!< Channel ADCx_INN10 -> ADCx_INP11 */
      (uint8_t)(LL_ADC_CHANNEL_12),       /*!< Channel ADCx_INN11 -> ADCx_INP12 */
      (uint8_t)(LL_ADC_CHANNEL_14),       /*!< Channel ADCx_INN12 -> ADCx_INP14 */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN13 -> VSSA       */
      (uint8_t)(LL_ADC_CHANNEL_15),       /*!< Channel ADCx_INN14 -> ADCx_INP15 */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN15 -> Vref-      */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN16 -> VSSA       */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN17 -> VSS        */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN18 -> VSSA       */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN19 -> Vref-      */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Virtual channel : none           */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Virtual channel : all            */
    },
    {
      (uint8_t)(LL_ADC_CHANNEL_1),        /*!< Channel ADCx_INN0  -> ADCx_INP1  */
      (uint8_t)(LL_ADC_CHANNEL_2),        /*!< Channel ADCx_INN1  -> ADCx_INP2  */
      (uint8_t)(LL_ADC_CHANNEL_3),        /*!< Channel ADCx_INN2  -> ADCx_INP3  */
      (uint8_t)(LL_ADC_CHANNEL_4),        /*!< Channel ADCx_INN3  -> ADCx_INP4  */
      (uint8_t)(LL_ADC_CHANNEL_5),        /*!< Channel ADCx_INN4  -> ADCx_INP5  */
      (uint8_t)(LL_ADC_CHANNEL_6),        /*!< Channel ADCx_INN5  -> ADCx_INP6  */
      (uint8_t)(LL_ADC_CHANNEL_7),        /*!< Channel ADCx_INN6  -> ADCx_INP7  */
      (uint8_t)(LL_ADC_CHANNEL_8),        /*!< Channel ADCx_INN7  -> ADCx_INP8  */
      (uint8_t)(LL_ADC_CHANNEL_9),        /*!< Channel ADCx_INN8  -> ADCx_INP9  */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN9  -> no connect.*/
      (uint8_t)(LL_ADC_CHANNEL_11),       /*!< Channel ADCx_INN10 -> ADCx_INP11 */
      (uint8_t)(LL_ADC_CHANNEL_12),       /*!< Channel ADCx_INN11 -> ADCx_INP12 */
      (uint8_t)(LL_ADC_CHANNEL_13),       /*!< Channel ADCx_INN12 -> ADCx_INP13 */
      (uint8_t)(LL_ADC_CHANNEL_14),       /*!< Channel ADCx_INN13 -> ADCx_INP14 */
      (uint8_t)(LL_ADC_CHANNEL_15),       /*!< Channel ADCx_INN14 -> ADCx_INP15 */
      (uint8_t)(LL_ADC_CHANNEL_17),       /*!< Channel ADCx_INN15 -> ADCx_INP17 */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN16 -> Vref-      */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN17 -> Vref-      */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN18 -> VSSA       */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN19 -> Vref-      */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Virtual channel : none           */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Virtual channel : all            */
    },
    {
      (uint8_t)(LL_ADC_CHANNEL_1),        /*!< Channel ADCx_INN0  -> ADCx_INP1  */
      (uint8_t)(LL_ADC_CHANNEL_2),        /*!< Channel ADCx_INN1  -> ADCx_INP2  */
      (uint8_t)(LL_ADC_CHANNEL_3),        /*!< Channel ADCx_INN2  -> ADCx_INP3  */
      (uint8_t)(LL_ADC_CHANNEL_4),        /*!< Channel ADCx_INN3  -> ADCx_INP4  */
      (uint8_t)(LL_ADC_CHANNEL_5),        /*!< Channel ADCx_INN4  -> ADCx_INP5  */
      (uint8_t)(LL_ADC_CHANNEL_6),        /*!< Channel ADCx_INN5  -> ADCx_INP6  */
      (uint8_t)(LL_ADC_CHANNEL_7),        /*!< Channel ADCx_INN6  -> ADCx_INP7  */
      (uint8_t)(LL_ADC_CHANNEL_8),        /*!< Channel ADCx_INN7  -> ADCx_INP8  */
      (uint8_t)(LL_ADC_CHANNEL_9),        /*!< Channel ADCx_INN8  -> ADCx_INP9  */
      (uint8_t)(LL_ADC_CHANNEL_10),       /*!< Channel ADCx_INN9  -> ADCx_INP10 */
      (uint8_t)(LL_ADC_CHANNEL_11),       /*!< Channel ADCx_INN10 -> ADCx_INP11 */
      (uint8_t)(LL_ADC_CHANNEL_12),       /*!< Channel ADCx_INN11 -> ADCx_INP12 */
      (uint8_t)(LL_ADC_CHANNEL_14),       /*!< Channel ADCx_INN12 -> ADCx_INP14 */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN13 -> Vref-      */
      (uint8_t)(LL_ADC_CHANNEL_15),       /*!< Channel ADCx_INN14 -> ADCx_INP15 */
      (uint8_t)(LL_ADC_CHANNEL_16),       /*!< Channel ADCx_INN15 -> ADCx_INP16 */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN16 -> Vref-      */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN17 -> Vref-      */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN18 -> VSSA       */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Channel ADCx_INN19 -> Vref-      */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Virtual channel : none           */
      (uint8_t)(LL_ADC_CHANNEL_NONE),     /*!< Virtual channel : all            */
    }
  };

  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(instance, channel);

  return LL_ADC_CHANNEL_DIFF_LUT[LL_ADC_INSTANCE_LUT_INDEX(instance)][(uint8_t)(channel_remapped)];
}

/**
  * @brief  Helper macro to get ADC group regular sequencer length in literal format LL_ADC_REG_SEQ_SCAN_x
  *         from number in decimal format.
  * @param  decimal_nb Value between Min_Data=1 and Max_Data=16 for ADC1 or ADC2
  * @note   Example:
  *           LL_ADC_DECIMAL_NB_TO_REG_SEQ_LENGTH(4)
  *           will return a data equivalent to "LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS".
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS
  */
#define LL_ADC_DECIMAL_NB_TO_REG_SEQ_LENGTH(decimal_nb) \
  (((decimal_nb) - 1UL) << ADC_SQR1_LEN_Pos)

/**
  * @brief  Helper macro to get ADC group regular sequencer length in decimal format
  *         from literal format LL_ADC_REG_SEQ_SCAN_x.
  * @param  seq_length Can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS
  * @note   Example:
  *           LL_ADC_REG_SEQ_LENGTH_TO_DECIMAL_NB(LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS)
  *           will return decimal number "4".
  * @retval Value between Min_Data=1 and Max_Data=16
  */
#define LL_ADC_REG_SEQ_LENGTH_TO_DECIMAL_NB(seq_length) \
  (((seq_length) >> ADC_SQR1_LEN_Pos) + 1UL)

/**
  * @brief  Helper macro to get ADC group injected sequencer length in literal format LL_ADC_INJ_SEQ_SCAN_x
  *         from number in decimal format.
  * @param  decimal_nb Value between Min_Data=1 and Max_Data=4.
  * @note   Example:
  *           LL_ADC_DECIMAL_NB_TO_REG_SEQ_LENGTH(4)
  *           will return a data equivalent to "LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS".
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  */
#define LL_ADC_DECIMAL_NB_TO_INJ_SEQ_LENGTH(decimal_nb) \
  (((decimal_nb) << ADC_JSQR_JLEN_Pos) - 1UL)

/**
  * @brief  Helper macro to get ADC group injected sequencer length in decimal format
  *         from literal format LL_ADC_REG_SEQ_SCAN_x.
  * @param  seq_length value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  * @note   Example:
  *           LL_ADC_REG_SEQ_LENGTH_TO_DECIMAL_NB(LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS)
  *           will return decimal number "4".
  * @retval Value between Min_Data=1 and Max_Data=4.
  */
#define LL_ADC_INJ_SEQ_LENGTH_TO_DECIMAL_NB(seq_length) \
  (((seq_length) >> ADC_JSQR_JLEN_Pos) + 1UL)

/**
  * @brief  Helper macro to get ADC group regular sequencer rank in literal format LL_ADC_REG_RANK_x
  *         from number in decimal format.
  * @param  decimal_nb Value between Min_Data=1 and Max_Data=16
  * @note   Example:
  *           LL_ADC_DECIMAL_NB_TO_REG_SEQ_LENGTH(2)
  *           will return a data equivalent to "LL_ADC_REG_RANK_2".
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_RANK_1
  *         @arg @ref LL_ADC_REG_RANK_2
  *         @arg @ref LL_ADC_REG_RANK_3
  *         @arg @ref LL_ADC_REG_RANK_4
  *         @arg @ref LL_ADC_REG_RANK_5
  *         @arg @ref LL_ADC_REG_RANK_6
  *         @arg @ref LL_ADC_REG_RANK_7
  *         @arg @ref LL_ADC_REG_RANK_8
  *         @arg @ref LL_ADC_REG_RANK_9
  *         @arg @ref LL_ADC_REG_RANK_10
  *         @arg @ref LL_ADC_REG_RANK_11
  *         @arg @ref LL_ADC_REG_RANK_12
  *         @arg @ref LL_ADC_REG_RANK_13
  *         @arg @ref LL_ADC_REG_RANK_14
  *         @arg @ref LL_ADC_REG_RANK_15
  *         @arg @ref LL_ADC_REG_RANK_16
  */
#define LL_ADC_DECIMAL_NB_TO_REG_SEQ_RANK(decimal_nb) \
  ((((decimal_nb) / 5UL) << LL_ADC_SQRX_REGOFFSET_POS) | (((decimal_nb) % 5UL ) * 6UL))

/**
  * @brief  Helper macro to get ADC group regular sequencer rank in decimal format
  *         from literal format LL_ADC_REG_RANK_x.
  * @param  seq_length Can be one of the following values:
  *         @arg @ref LL_ADC_REG_RANK_1
  *         @arg @ref LL_ADC_REG_RANK_2
  *         @arg @ref LL_ADC_REG_RANK_3
  *         @arg @ref LL_ADC_REG_RANK_4
  *         @arg @ref LL_ADC_REG_RANK_5
  *         @arg @ref LL_ADC_REG_RANK_6
  *         @arg @ref LL_ADC_REG_RANK_7
  *         @arg @ref LL_ADC_REG_RANK_8
  *         @arg @ref LL_ADC_REG_RANK_9
  *         @arg @ref LL_ADC_REG_RANK_10
  *         @arg @ref LL_ADC_REG_RANK_11
  *         @arg @ref LL_ADC_REG_RANK_12
  *         @arg @ref LL_ADC_REG_RANK_13
  *         @arg @ref LL_ADC_REG_RANK_14
  *         @arg @ref LL_ADC_REG_RANK_15
  *         @arg @ref LL_ADC_REG_RANK_16
  * @note   Example:
  *           LL_ADC_REG_SEQ_RANK_TO_DECIMAL_NB(LL_ADC_REG_RANK_2)
  *           will return decimal number "2".
  * @retval Value between Min_Data=1 and Max_Data=16
  */
#define LL_ADC_REG_SEQ_RANK_TO_DECIMAL_NB(seq_length) \
  ((((seq_length) >> LL_ADC_SQRX_REGOFFSET_POS) * 5UL) + (((seq_length) & LL_ADC_REG_RANK_ID_SQRX_MASK) / 6UL))

/**
  * @brief  Helper macro to get ADC group injected sequencer rank in literal format LL_ADC_INJ_RANK_x
  *         from number in decimal format.
  * @param  decimal_nb Value between Min_Data=1 and Max_Data=16
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  */
#define LL_ADC_DECIMAL_NB_TO_INJ_SEQ_RANK(decimal_nb) \
  ((((decimal_nb) - 1UL) << (LL_ADC_JDRX_REGOFFSET_POS)) | (((decimal_nb) * 6UL) + 3UL))

/**
  * @brief  Helper macro to get ADC group injected sequencer rank in decimal format
  *         from literal format LL_ADC_INJ_RANK_x.
  * @param  seq_length Can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @note   Example:
  *           LL_ADC_INJ_SEQ_RANK_TO_DECIMAL_NB(LL_ADC_INJ_RANK_2)
  *           will return decimal number "2".
  * @retval Value between Min_Data=1 and Max_Data=16
  */
#define LL_ADC_INJ_SEQ_RANK_TO_DECIMAL_NB(seq_length) \
  ((((seq_length) & LL_ADC_INJ_RANK_ID_JSQR_MASK) - 3UL) / 6UL)

/**
  * @brief  Helper macro to get ADC oversampling right bit shift value in function of ratio to have oversampling data
  *         keeping current resolution (example: to keep data resolution, ratio x8 requires right shift of 3 bits).
  * @param  ovs_ratio_decimal Value power of 2 (1, 2, 4, 8, 16, ...) between Min_Data=1 and Max_Data=1024
  * @note   Example:
  *           LL_ADC_OVS_SHIFT_KEEP_RES(8)
  *           will return decimal number "3".
  * @retval Value between Min_Data=1 and Max_Data=11
  */
#define LL_ADC_OVS_SHIFT_KEEP_RES(ovs_ratio_decimal) \
  (STM32_POSITION_VAL(ovs_ratio_decimal))

/**
  * @brief  Helper macro to set the value of ADC analog watchdog threshold high
  *         or low in function of ADC resolution, when ADC resolution is
  *         different of default resolution (12 bit).
  * @param  resolution This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @param  awd_threshold Analog watchdog threshold value. Value is signed and can exceed ADC resolution
  *         with post-processing computation (offset, oversampling, data shift, ...).
  *         Value between Min_Data=-4194304 (two's complement 0xFFC00000) and Max_Data=+4194303 (0x003FFFFF)
  * @note   To be used with function @ref LL_ADC_SetAnalogWDThresholds().
  *         Example, with a ADC resolution of 8 bits, to set the value of
  *         analog watchdog threshold high (on 8 bits):
  *           LL_ADC_SetAnalogWDThresholds
  *            (< ADCx param >,
  *             LL_ADC_ANALOGWD_SET_THRESHOLD_RES(LL_ADC_RESOLUTION_8B, <threshold_value_8_bits>)
  *            );
  * @retval Value is represented as unsigned for intermediate computation
  *         but is formatted as signed and can exceed ADC resolution with post-processing computation
  *         (offset, oversampling, data shift, ...): to be casted to signed 32 bits.
  */
#define LL_ADC_ANALOGWD_SET_THRESHOLD_RES(resolution, awd_threshold) \
  (uint32_t)(((uint32_t)(awd_threshold)) << ((resolution) >> (ADC_CFGR1_RES_Pos - 1U)))

/**
  * @brief  Helper macro to get the value of ADC analog watchdog threshold high
  *         or low in function of ADC resolution, when ADC resolution is
  *         different of 12 bits.
  * @param  resolution This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @param  awd_threshold Analog watchdog threshold value. Value is signed and can exceed ADC resolution
  *         with post-processing computation (offset, oversampling, data shift, ...).
  *         Value between Min_Data=-4194304 (two's complement 0xFFC00000) and Max_Data=+4194303 (0x003FFFFF)
  * @note   To be used with function @ref LL_ADC_GetAnalogWDThresholds().
  *         Example, with a ADC resolution of 8 bits, to get the value of
  *         analog watchdog threshold high (on 8 bits):
  *           < threshold_value_6_bits > = LL_ADC_ANALOGWD_GET_THRESHOLD_RES
  *            (LL_ADC_RESOLUTION_8B,
  *             LL_ADC_GetAnalogWDThresholds(<ADCx param>, LL_ADC_AWD_THRESHOLD_HIGH)
  *            );
  * @retval Value is represented as unsigned for intermediate computation
  *         but is formatted as signed and can exceed ADC resolution with post-processing computation
  *         (offset, oversampling, data shift, ...): to be casted to signed 32 bits.
  */
#define LL_ADC_ANALOGWD_GET_THRESHOLD_RES(resolution, awd_threshold) \
  (uint32_t)((((uint32_t)(awd_threshold)) >> ((resolution) >> (ADC_CFGR1_RES_Pos - 1U))) \
             | (((uint32_t)(awd_threshold)) & (~ADC_AWD1LTR_LTR)))

/**
  * @brief  Helper macro to set the value of ADC offset level in function of ADC resolution,
  *         when ADC resolution is different of default resolution.
  * @param  resolution This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @param  offset_level Value between Min_Data=0x00000000 and Max_Data=0x003FFFFF
  * @note   To be used with function @ref LL_ADC_SetOffsetLevel().
  *         Example, with a ADC resolution of 8 bits, to set the value of
  *         analog watchdog threshold high (on 8 bits):
  *           LL_ADC_SetOffset
  *            (< ADCx param >,
  *             LL_ADC_OFFSET_SET_LEVEL_RES(LL_ADC_RESOLUTION_8B, <offset_level_8_bits>)
  *            );
  * @retval Value between Min_Data=0x00000000 and Max_Data=0x003FFFFF
  */
#define LL_ADC_OFFSET_SET_LEVEL_RES(resolution, offset_level) \
  ((offset_level) << ((resolution) >> (ADC_CFGR1_RES_Pos - 1U)))

/**
  * @brief  Helper macro to get the value of ADC offset level in function of ADC resolution,
  *         when ADC resolution is different of default resolution.
  * @param  resolution This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @param  offset_level Value between Min_Data=0x00000000 and Max_Data=0x003FFFFF
  * @note   To be used with function LL_ADC_GetOffset().
  *         Example, with a ADC resolution of 8 bits, to set the value of
  *         analog watchdog threshold high (on 8 bits):
  *           LL_ADC_GetOffsetLevel
  *            (< ADCx param >,
  *             LL_ADC_OFFSET_SET_LEVEL_RES(LL_ADC_RESOLUTION_8B, <offset_level_8_bits>)
  *            );
  * @retval Value between Min_Data=0x00000000 and Max_Data=0x003FFFFF
  */
#define LL_ADC_OFFSET_GET_LEVEL_RES(resolution, offset_level) \
  ((offset_level) >> ((resolution) >> (ADC_CFGR1_RES_Pos - 1U)))

/**
  * @brief  Helper macro to set the ADC calibration value with both single ended
  *         and differential modes calibration factors concatenated.
  * @param  calib_factor_single_ended Value between Min_Data=0x00 and Max_Data=0x7F
  * @param  calib_factor_differential Value between Min_Data=0x00 and Max_Data=0x7F
  * @note   To be used with function @ref LL_ADC_SetCalibrationFactor().
  *         Example, to set calibration factors single ended to 0x55
  *         and differential ended to 0x2A:
  *           LL_ADC_SetCalibrationFactor(
  *             ADC1,
  *             LL_ADC_CALIB_FACTOR_SINGLE_DIFF(0x55, 0x2A))
  * @retval Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
#define LL_ADC_CALIB_FACTOR_SINGLE_DIFF(calib_factor_single_ended, calib_factor_differential) \
  (((calib_factor_differential) << ADC_CALFACT_CALFACT_D_Pos) | (calib_factor_single_ended))

#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief  Helper macro to get the ADC multimode conversion data of ADC master
  *         or ADC slave from raw value with both ADC conversion data concatenated
  *         (unpack multimode conversion data).
  * @param  adc_multi_master_slave This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_MASTER
  *         @arg @ref LL_ADC_MULTI_SLAVE
  * @param  adc_multi_conv_data Value between Min_Data=0x0000 and Max_Data=0xFFFF
  * @note   This macro is intended to be used when multimode transfer by DMA
  *         is enabled (refer to function @ref LL_ADC_SetMultiDMATransfer()) and data retrieved from CDR (not CDR2).
  *         In this case the transferred data needs to be processed with this macro
  *         to separate the conversion data of ADC master and ADC slave.
  * @retval Value between Min_Data=0x0000 and Max_Data=0xFFFF
  */
#define LL_ADC_MULTI_CONV_DATA_MASTER_SLAVE(adc_multi_master_slave, adc_multi_conv_data) \
  (((adc_multi_conv_data) >> ((ADCC_CDR_RDATA_SLV_Pos) & ~(adc_multi_master_slave))) & ADCC_CDR_RDATA_MST)
#endif /* ADC_MULTIMODE_SUPPORT */

/**
  * @brief  Helper macro to define the ADC conversion data full-scale digital
  *         maximum value corresponding to the selected ADC resolution.
  * @param  resolution This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @note   ADC conversion data full-scale corresponds to voltage range
  *         determined by analog voltage references Vref+ and Vref- (refer to reference manual).
  * @note   Value returned corresponds to range maximum value without post-processing computation.
  *         With post-processing (offset, gain), conversion data maximum value can exceed this range
  *         (as well as minimum value in negative range).
  * @retval ADC conversion data full-scale digital value (unit: digital value of ADC conversion data)
  */
#define LL_ADC_DIGITAL_SCALE(resolution) \
  (0xFFFUL >> ((resolution) >> (ADC_CFGR1_RES_Pos - 1UL)))

/**
  * @brief  Helper macro to convert the ADC conversion data from
  *         a resolution to another resolution.
  * @param  data ADC conversion data to be converted
  * @param  adc_res_current Resolution of the data to be converted
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @param  adc_res_target Resolution of the data after conversion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @note   Arguments data type converted to signed (int32_t) to handle all possible input values
  *         (conversion data can be negative after post-processing computation: offset feature).
  * @note   Processing of negative values: Computation with numerical values power of two instead of binary shift
  *         for explicit sign management (arithmetic shift instead of logical shift).
  * @retval ADC conversion data to the requested resolution
  */
#define LL_ADC_CONVERT_DATA_RESOLUTION(data, \
                                       adc_res_current, \
                                       adc_res_target) \
((((int32_t)(data)) * (int32_t)64L) \
 / (int32_t)((uint32_t)(1UL << (2U * ((3U + ((adc_res_target) >> ADC_CFGR1_RES_Pos)) \
                                      - ((adc_res_current) >> ADC_CFGR1_RES_Pos))))))

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value).
  * @param  vref_analog_voltage Analog reference voltage Vref+ (unit: mVolt).
  * @param  conv_data ADC conversion data (unit: digital value).
  * @param  resolution ADC resolution at which ADC conversion has been performed.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @note   Arguments data type converted to signed (int32_t) to handle all possible input values
  *         (conversion data can be negative after post-processing computation: offset feature).
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define LL_ADC_CALC_DATA_TO_VOLTAGE(vref_analog_voltage, \
                                    conv_data, \
                                    resolution) \
((int32_t)(conv_data) * (int32_t)(vref_analog_voltage) \
 / (int32_t)(LL_ADC_DIGITAL_SCALE(resolution)))

/**
  * @brief  Helper macro to calculate the ADC conversion data (unit: digital value)
  *         corresponding to a voltage (unit: mVolt).
  * @param  vref_analog_voltage Analog reference voltage Vref+ (unit: mVolt)
  * @param  voltage_mv ADC conversion data voltage value (unit: mVolt)
  * @param  resolution ADC resolution at which ADC conversion has been performed
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @note   Arguments data type converted to signed (int32_t) to handle all possible input values
  *         (conversion data can be negative after post-processing computation: offset feature)
  * @retval ADC conversion data equivalent value (unit: digital value)
  */
#define LL_ADC_CALC_VOLTAGE_TO_DATA(vref_analog_voltage, \
                                    voltage_mv, \
                                    resolution) \
((int32_t)(voltage_mv) * (int32_t)(LL_ADC_DIGITAL_SCALE(resolution)) \
 / (int32_t)(vref_analog_voltage))

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value) in
  *         differential ended mode.
  * @param  vref_analog_voltage Analog reference voltage Vref+ (unit: mVolt)
  * @param  conv_data ADC conversion data (unit: digital value).
  * @param  resolution ADC resolution at which ADC conversion has been performed
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @note   Data sign: Computed differential voltage can be positive or negative depending on
  *         differential input voltages.
  *         By default, without post-processing, ADC conversion data is unsigned
  *         and computed differential voltage is centered around mid range.
  *         With post-processing (offset feature), ADC conversion data can be negative. For these reason,
  *         arguments data type converted to signed (int32_t) to handle all possible input values.
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define LL_ADC_CALC_DIFF_DATA_TO_VOLTAGE(vref_analog_voltage, \
                                         conv_data, \
                                         resolution) \
((((((int32_t)(conv_data)) * (int32_t)2) * (int32_t)(vref_analog_voltage)) \
  / (int32_t)(LL_ADC_DIGITAL_SCALE((resolution)))) - (int32_t)(vref_analog_voltage))

/**
  * @brief  Helper macro to calculate analog reference voltage (Vref+)
  *         (unit: mVolt) from ADC conversion data of internal voltage
  *         reference VrefInt.
  * @param  vrefint_conv_data ADC conversion data
  *         of internal voltage reference VrefInt (unit: digital value).
  * @param  resolution ADC resolution at which ADC conversion has been performed.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @note   Computation is using VrefInt calibration value
  *         stored in system memory for each device during production.
  * @note   This voltage depends on user board environment: voltage level
  *         connected to pin Vref+.
  *         On devices with small package, the pin Vref+ is not present
  *         and internally bonded to pin Vdda.
  * @retval Analog reference voltage Vref+ value (unit: mVolt)
  */
#define LL_ADC_CALC_VREFANALOG_VOLTAGE(vrefint_conv_data, \
                                       resolution) \
((((uint32_t)*LL_ADC_VREFINT_CAL_ADDR) * (uint32_t)LL_ADC_VREFINT_CAL_VREF) \
 / (uint32_t)LL_ADC_CONVERT_DATA_RESOLUTION((vrefint_conv_data), \
                                            (resolution), \
                                            LL_ADC_RESOLUTION_12B))

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  * @param  vref_analog_voltage  Analog reference voltage Vref+ (unit: mVolt)
  * @param  tempsensor_conv_data ADC conversion data of internal
  *                                 temperature sensor (unit: digital value).
  * @param  resolution ADC resolution at which ADC conversion has been performed
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @note   Computation is using temperature sensor calibration values
  *         stored in system memory for each device during production.
  * @note   Calculation formula:
  *           Temperature = ((TS_ADC_DATA - TS_CAL1)
  *                           * (TS_CAL2_TEMP - TS_CAL1_TEMP))
  *                         / (TS_CAL2 - TS_CAL1) + TS_CAL1_TEMP
  *           with TS_ADC_DATA = temperature sensor raw data measured by ADC
  *                Avg_Slope = (TS_CAL2 - TS_CAL1)
  *                            / (TS_CAL2_TEMP - TS_CAL1_TEMP)
  *                TS_CAL1   = equivalent TS_ADC_DATA at temperature
  *                            TEMP_DEGC_CAL1 (calibrated in factory)
  *                TS_CAL2   = equivalent TS_ADC_DATA at temperature
  *                            TEMP_DEGC_CAL2 (calibrated in factory)
  *         Caution: Calculation relevancy under reserve that calibration
  *                  parameters are correct (address and data).
  *                  To calculate temperature using temperature sensor
  *                  datasheet typical values (generic values less, therefore
  *                  less accurate than calibrated values),
  *                  use helper macro @ref LL_ADC_CALC_TEMPERATURE_TYP_PARAMS().
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @retval Temperature (unit: degree Celsius) or error code (value LL_ADC_TEMPERATURE_CALC_ERROR)
  */
__STATIC_INLINE int32_t LL_ADC_CALC_TEMPERATURE(uint32_t vref_analog_voltage,
                                                uint32_t tempsensor_conv_data,
                                                uint32_t resolution)
{
  int32_t temperature_degc;
  int32_t data_res;

  if (((int32_t)*LL_ADC_TEMPSENSOR_CAL2_ADDR - (int32_t)*LL_ADC_TEMPSENSOR_CAL1_ADDR) == 0)
  {
    temperature_degc = (int32_t)LL_ADC_TEMPERATURE_CALC_ERROR;
  }
  else
  {
    /* Scale ADC conversion data to resolution corresponding to temperature sensor calibration parameters */
    data_res = LL_ADC_CONVERT_DATA_RESOLUTION(tempsensor_conv_data,
                                              (uint32_t)resolution,
                                              (uint32_t)LL_ADC_RESOLUTION_12B);

    /* Scale ADC conversion data to reference voltage corresponding to temperature sensor calibration parameters */
    data_res = ((data_res * (int32_t)vref_analog_voltage) / (int32_t)LL_ADC_TEMPSENSOR_CAL_VREF);

    /* Compute temperature */
    temperature_degc = ((((int32_t)data_res - (int32_t)(*LL_ADC_TEMPSENSOR_CAL1_ADDR))
                         * (int32_t)(LL_ADC_TEMPSENSOR_CAL2_TEMP - LL_ADC_TEMPSENSOR_CAL1_TEMP))
                        / (int32_t)((int32_t)(*LL_ADC_TEMPSENSOR_CAL2_ADDR) - (int32_t)(*LL_ADC_TEMPSENSOR_CAL1_ADDR)))
                       + LL_ADC_TEMPSENSOR_CAL1_TEMP;
  }

  return temperature_degc;
}

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  * @param  tempsensor_typ_avg_slope Device datasheet data: Temperature sensor slope typical value
  *                                  (unit: uV/DegCelsius).
  *                                  On this STM32 series, refer to device datasheet parameter "Avg_Slope".
  * @param  tempsensor_typ_calx_v    Device datasheet data: Temperature sensor voltage typical value
  *                                  (at temperature and Vref+ defined in parameters below) (unit: mVolt).
  *                                  On this STM32 series, refer to device datasheet parameter "V30"
  *                                  (corresponding to TS_CAL1).
  * @param  tempsensor_calx_temp     Device datasheet data: Temperature at which temperature sensor voltage
  *                                  see parameter above) is corresponding (unit: mVolt)
  * @param  vref_analog_voltage      Analog reference voltage Vref+ (unit: mVolt)
  * @param  tempsensor_conv_data     ADC conversion data of internal temperature sensor (unit: digital value).
  * @param  resolution               ADC resolution at which ADC conversion has been performed
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @note   Computation is using temperature sensor typical values
  *         (refer to device datasheet).
  * @note   Calculation formula:
  *           Temperature = (TS_TYP_CALx_VOLT(uV) - TS_ADC_DATA * Conversion_uV)
  *                         / Avg_Slope + CALx_TEMP
  *           with TS_ADC_DATA      = temperature sensor raw data measured by ADC
  *                                   (unit: digital value)
  *                Avg_Slope        = temperature sensor slope
  *                                   (unit: uV/Degree Celsius)
  *                TS_TYP_CALx_VOLT = temperature sensor digital value at
  *                                   temperature CALx_TEMP (unit: mVolt)
  *         Caution: Calculation relevancy under reserve the temperature sensor
  *                  of the current device has characteristics in line with
  *                  datasheet typical values.
  *                  If temperature sensor calibration values are available on
  *                  on this device (presence of macro LL_ADC_CALC_TEMPERATURE()),
  *                  temperature calculation will be more accurate using
  *                  helper macro @ref LL_ADC_CALC_TEMPERATURE().
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @retval Temperature (unit: degree Celsius)
  */
__STATIC_INLINE int32_t LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(int32_t tempsensor_typ_avg_slope,
                                                           uint32_t tempsensor_typ_calx_v,
                                                           int32_t tempsensor_calx_temp,
                                                           uint32_t vref_analog_voltage,
                                                           uint32_t tempsensor_conv_data,
                                                           uint32_t resolution)
{
  int32_t temperature_degc;
  uint32_t data_mvolt;

  /* Convert ADC conversion data to voltage */
  data_mvolt = ((tempsensor_conv_data * vref_analog_voltage) / LL_ADC_DIGITAL_SCALE(resolution));

  /* Compute temperature */
  temperature_degc = ((((int32_t)data_mvolt * 1000L) - ((int32_t)tempsensor_typ_calx_v * 1000L))
                      / (int32_t)tempsensor_typ_avg_slope)
                     + (int32_t)tempsensor_calx_temp;

  return temperature_degc;
}

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Functions LL ADC Functions
  * @{
  */

/** @defgroup ADC_LL_EF_DMA_Management ADC DMA management
  * @{
  */
#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief  Function to help to configure DMA transfer from ADC: retrieve the
  *         ADC register address from ADC instance and a list of ADC registers
  *         intended to be used (most commonly) with DMA transfer.
  * @rmtoll
  *  DR       RDATA          LL_ADC_DMA_GetRegAddr\n
  *  CDR      RDATA_MST      LL_ADC_DMA_GetRegAddr\n
  *  CDR      RDATA_SLV      LL_ADC_DMA_GetRegAddr\n
  *  CDR2     RDATA_ALT      LL_ADC_DMA_GetRegAddr
  * @param  p_adc Pointer to ADC instance
  * @param  register_sel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DMA_REG_REGULAR_DATA
  *         @arg @ref LL_ADC_DMA_REG_MM_REGULAR_PACK_DATA (1)
  *         @arg @ref LL_ADC_DMA_REG_MM_REGULAR_UNPACK_DATA (1)
  *
  *         (1) Available on devices featuring ADC multimode
  * @note   These ADC registers are data registers:
  *         when ADC conversion data is available in ADC data registers,
  *         ADC generates a DMA transfer request.
  * @note   This macro is intended to be used with LL DMA driver, refer to
  *         function "LL_DMA_ConfigAddresses()".
  *         Example:
  *           LL_DMA_ConfigAddresses(DMA1,
  *                                  LL_DMA_CHANNEL_1,
  *                                  LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
  *                                  (uint32_t)&< array or variable >,
  *                                  LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  * @note   For devices with several ADC: in multimode, some devices
  *         use a different data register outside of ADC instance scope
  *         (common data register). This macro manages this register difference,
  *         only ADC instance has to be set as parameter.
  * @retval ADC register address
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_GetRegAddr(const ADC_TypeDef *p_adc, uint32_t register_sel)
{
  uint32_t data_reg_addr;

#if defined(ADC_MULTIMODE_SUPPORT)
  if (register_sel == LL_ADC_DMA_REG_REGULAR_DATA)
  {
    /* Retrieve address of register DR */
    data_reg_addr = (uint32_t) &(p_adc->DR);
  }
  else if (register_sel == LL_ADC_DMA_REG_MM_REGULAR_PACK_DATA)
  {
    data_reg_addr = (uint32_t) &((ADC_COMMON_INSTANCE(p_adc))->CDR);
  }
  else /* (register_sel == LL_ADC_DMA_REG_MM_REGULAR_UNPACK_DATA) */
  {
    data_reg_addr = (uint32_t) &((ADC_COMMON_INSTANCE(p_adc))->CDR2);
  }
#else
  data_reg_addr = (uint32_t) &(p_adc->DR);
#endif /* ADC_MULTIMODE_SUPPORT */

  return data_reg_addr;
}
#else
/**
  * @brief  Function to help to configure DMA transfer from ADC: retrieve the
  *         ADC register address from ADC instance and a list of ADC registers
  *         intended to be used (most commonly) with DMA transfer.
  * @rmtoll
  *  DR       RDATA          LL_ADC_DMA_GetRegAddr
  * @param  p_adc Pointer to ADC instance
  * @param  register_sel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DMA_REG_REGULAR_DATA
  * @note   These ADC registers are data registers:
  *         when ADC conversion data is available in ADC data registers,
  *         ADC generates a DMA transfer request.
  * @note   This macro is intended to be used with LL DMA driver, refer to
  *         function "LL_DMA_ConfigAddresses()".
  *         Example:
  *           LL_DMA_ConfigAddresses(DMA1,
  *                                  LL_DMA_CHANNEL_1,
  *                                  LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
  *                                  (uint32_t)&< array or variable >,
  *                                  LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  * @note   For devices with several ADC: in multimode, some devices
  *         use a different data register outside of ADC instance scope
  *         (common data register). This macro manages this register difference,
  *         only ADC instance has to be set as parameter.
  * @retval ADC register address
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_GetRegAddr(const ADC_TypeDef *p_adc, uint32_t register_sel)
{
  /* Prevent unused argument(s) compilation warning */
  (void)(register_sel);

  /* Retrieve address of register DR */
  return (uint32_t) &(p_adc->DR);
}
#endif /* ADC_MULTIMODE_SUPPORT */

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Common Configuration of ADC hierarchical scope:
  *           common to several ADC instances
  * @{
  */
/**
  * @brief  Set parameter common to several ADC: measurement path to
  *         internal channels (VrefInt, temperature sensor, ...).
  *         Add paths to the current configuration.
  * @rmtoll
  *  CCR      VREFEN         LL_ADC_SetCommonPathInternalChAdd\n
  *  CCR      TSEN           LL_ADC_SetCommonPathInternalChAdd
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @param  path_internal This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   Stabilization time of measurement path to internal channel:
  *         After enabling internal paths, before starting ADC conversion,
  *         a delay is required for internal voltage reference and
  *         temperature sensor stabilization time.
  *         Refer to device datasheet.
  *         Refer to literal @ref LL_ADC_DELAY_VREFINT_STAB_US.
  *         Refer to literals @ref LL_ADC_DELAY_TEMPSENSOR_STAB_US,
  * @note   ADC internal channel sampling time constraint:
  *         For ADC conversion of internal channels,
  *         a sampling time minimum value is required.
  *         Refer to device datasheet.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  */
__STATIC_INLINE void LL_ADC_SetCommonPathInternalChAdd(ADC_Common_TypeDef *p_adc_common, uint32_t path_internal)
{
  STM32_SET_BIT(p_adc_common->CCR, path_internal & LL_ADC_COMMON_PATH_INTERNAL_MASK);
}

/**
  * @brief  Set parameter common to several ADC: measurement path to
  *         internal channels (VrefInt, temperature sensor, ...).
  *         Remove paths to the current configuration.
  * @rmtoll
  *  CCR      VREFEN         LL_ADC_SetCommonPathInternalChRem\n
  *  CCR      TSEN           LL_ADC_SetCommonPathInternalChRem
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @param  path_internal This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  */
__STATIC_INLINE void LL_ADC_SetCommonPathInternalChRem(ADC_Common_TypeDef *p_adc_common, uint32_t path_internal)
{
  STM32_CLEAR_BIT(p_adc_common->CCR, path_internal & LL_ADC_COMMON_PATH_INTERNAL_MASK);
}

/**
  * @brief  Set parameter common to several ADC: measurement path to internal
  *         channels (VrefInt, temperature sensor, ...).
  * @rmtoll
  *  CCR      VREFEN         LL_ADC_SetCommonPathInternalCh\n
  *  CCR      TSEN           LL_ADC_SetCommonPathInternalCh
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @param  path_internal This parameter can be one of literal LL_ADC_PATH_INTERNAL_x
  *         or one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   Stabilization time of measurement path to internal channel:
  *         After enabling internal paths, before starting ADC conversion,
  *         a delay is required for internal voltage reference and
  *         temperature sensor stabilization time.
  *         Refer to device datasheet.
  *         Refer to literal @ref LL_ADC_DELAY_VREFINT_STAB_US.
  *         Refer to literal @ref LL_ADC_DELAY_TEMPSENSOR_STAB_US.
  * @note   ADC internal channel sampling time constraint:
  *         For ADC conversion of internal channels,
  *         a sampling time minimum value is required.
  *         Refer to device datasheet.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  */
__STATIC_INLINE void LL_ADC_SetCommonPathInternalCh(ADC_Common_TypeDef *p_adc_common, uint32_t path_internal)
{
  STM32_MODIFY_REG(p_adc_common->CCR,
                   LL_ADC_COMMON_PATH_INTERNAL_MASK,
                   path_internal & LL_ADC_COMMON_PATH_INTERNAL_MASK);
}

/**
  * @brief  Get parameter common to several ADC: measurement path to internal
  *         channels (VrefInt, temperature sensor, ...).
  * @rmtoll
  *  CCR      VREFEN         LL_ADC_GetCommonPathInternalCh\n
  *  CCR      TSEN           LL_ADC_GetCommonPathInternalCh
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT | LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  * @retval Returned value can be a combination of literals LL_ADC_PATH_INTERNAL_x.
  */
__STATIC_INLINE uint32_t LL_ADC_GetCommonPathInternalCh(const ADC_Common_TypeDef *p_adc_common)
{
  return (uint32_t)(STM32_READ_BIT(p_adc_common->CCR, LL_ADC_COMMON_PATH_INTERNAL_MASK));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Instance Configuration of ADC hierarchical scope: ADC instance
  * @{
  */

/**
  * @brief  Set parameter on ADC instance scope: measurement path to
  *         internal channels.
  *         Configure all paths (overwrite current configuration).
  *  OR       OP0            LL_ADC_SetPathInternalCh
  * @param  p_adc Pointer to ADC instance
  * @param  path_internal This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VDDCORE (1)
  *
  *         (1) On STM32G5, parameter available on ADC instance: ADC1, ADC2, ADC3.
  * @note   Stabilization time of measurement path to internal channel:
  *         After enabling internal paths, before starting ADC conversion,
  *         a delay is required required for analog stabilization.
  *         Refer to device datasheet.
  * @note   ADC internal channel sampling time constraint:
  *         For ADC conversion of internal channels,
  *         a sampling time minimum value is required.
  *         Refer to device datasheet.
  */
__STATIC_INLINE void LL_ADC_SetPathInternalCh(ADC_TypeDef *p_adc, uint32_t path_internal)
{
  STM32_MODIFY_REG(p_adc->OR, LL_ADC_PATH_INTERNAL_OR_MASK,
                   ((path_internal & LL_ADC_PATH_INTERNAL_MASK) >> LL_ADC_PATH_INTERNAL_POS));
}

/**
  * @brief  Set parameter on ADC instance scope: measurement path to
  *         internal channels.
  *         Add paths to the current configuration.
  *  OR       OP0            LL_ADC_SetPathInternalChAdd
  * @param  p_adc Pointer to ADC instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VDDCORE (1)
  *
  *         (1) On STM32G5, parameter available on ADC instance: ADC1, ADC2, ADC3.
  * @note   The values not selected are removed from configuration.
  * @note   Stabilization time of measurement path to internal channel:
  *         After enabling internal paths, before starting ADC conversion,
  *         a delay is be required required for analog stabilization.
  *         Refer to device datasheet.
  * @note   ADC internal channel sampling time constraint:
  *         For ADC conversion of internal channels,
  *         a sampling time minimum value is required.
  *         Refer to device datasheet.
  */
__STATIC_INLINE void LL_ADC_SetPathInternalChAdd(ADC_TypeDef *p_adc, uint32_t channel)
{
  STM32_SET_BIT(p_adc->OR, ((channel & LL_ADC_PATH_INTERNAL_MASK) >> LL_ADC_PATH_INTERNAL_POS));
}

/**
  * @brief  Set parameter on ADC instance scope: measurement path to
  *         internal channels.
  *         Remove paths to the current configuration.
  *  OR       OP0            LL_ADC_SetPathInternalChRem
  * @param  p_adc Pointer to ADC instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VDDCORE (1)
  *
  *         (1) On STM32G5, parameter available on ADC instance: ADC1, ADC2, ADC3.
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VDDCORE |
  *                   LL_ADC_PATH_INTERNAL_...)
  *         The values not selected are removed from configuration.
  * @note   Stabilization time of measurement path to internal channel:
  *         After enabling internal paths, before starting ADC conversion,
  *         a delay can be required required for analog stabilization.
  *         Refer to device datasheet.
  * @note   ADC internal channel sampling time constraint:
  *         For ADC conversion of internal channels,
  *         a sampling time minimum value is required.
  *         Refer to device datasheet.
  */
__STATIC_INLINE void LL_ADC_SetPathInternalChRem(ADC_TypeDef *p_adc, uint32_t channel)
{
  STM32_CLEAR_BIT(p_adc->OR, ((channel & LL_ADC_PATH_INTERNAL_MASK) >> LL_ADC_PATH_INTERNAL_POS));
}

/**
  * @brief  Get parameter on ADC instance scope: measurement path to
  *         internal channels.
  *  OR       OP0            LL_ADC_GetPathInternalCh
  * @param  p_adc Pointer to ADC instance
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VDDCORE |
  *                   LL_ADC_PATH_INTERNAL_...)
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VDDCORE (1)
  *
  *         (1) On STM32G5, parameter available on ADC instance: ADC1, ADC2, ADC3.
  */
__STATIC_INLINE uint32_t LL_ADC_GetPathInternalCh(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->OR, LL_ADC_PATH_INTERNAL_OR_MASK) << LL_ADC_PATH_INTERNAL_POS);
}

/**
  * @brief  Set ADC calibration factor in the mode single-ended
  *         or differential (for devices with differential mode available).
  * @rmtoll
  *  CALFACT  CALFACT_S      LL_ADC_SetCalibrationFactor\n
  *  CALFACT  CALFACT_D      LL_ADC_SetCalibrationFactor
  * @param  p_adc Pointer to ADC instance
  * @param  input_mode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_IN_SINGLE_ENDED
  *         @arg @ref LL_ADC_IN_DIFFERENTIAL
  *         @arg @ref LL_ADC_IN_SINGLE_DIFF
  * @param  calibration_factor Value between Min_Data=0x00 and Max_Data=0x7F
  * @note   This function is intended to set calibration parameters
  *         without having to perform a new calibration using
  *         @ref LL_ADC_StartCalibration().
  * @note   In case of setting calibration factors of both modes single ended
  *         and differential (parameter @ref LL_ADC_IN_SINGLE_DIFF):
  *         both calibration factors must be concatenated.
  *         To perform this processing, use helper macro
  *         @ref LL_ADC_CALIB_FACTOR_SINGLE_DIFF().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled, without calibration ongoing, without conversion
  *         ongoing on group regular.
  */
__STATIC_INLINE void LL_ADC_SetCalibrationFactor(ADC_TypeDef *p_adc, uint32_t input_mode, uint32_t calibration_factor)
{
  STM32_MODIFY_REG(p_adc->CALFACT,
                   input_mode & LL_ADC_SGLDIFF_CAL_FACTOR_MASK,
                   (calibration_factor << (LL_ADC_SGLDIFF_CAL_F_BIT_D_POS & ~(input_mode & ADC_CALFACT_CALFACT_S)))
                   & input_mode & LL_ADC_SGLDIFF_CAL_FACTOR_MASK);
}

/**
  * @brief  Get ADC calibration factor in mode single-ended
  *         or differential (for devices with differential mode available).
  * @rmtoll
  *  CALFACT  CALFACT_S      LL_ADC_GetCalibrationFactor\n
  *  CALFACT  CALFACT_D      LL_ADC_GetCalibrationFactor
  * @param  p_adc Pointer to ADC instance
  * @param  input_mode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_IN_SINGLE_ENDED
  *         @arg @ref LL_ADC_IN_DIFFERENTIAL
  * @note   Calibration factors are set by hardware after performing
  *         a calibration run using function @ref LL_ADC_StartCalibration().
  * @note   For devices with differential mode available:
  *         Calibration of offset is specific to each of
  *         single-ended and differential modes
  * @retval Value between Min_Data=0x00 and Max_Data=0x1FF
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibrationFactor(const ADC_TypeDef *p_adc, uint32_t input_mode)
{
  /* Retrieve bits with position in register depending on parameter           */
  /* "input_mode".                                                           */
  /* Parameter used with mask "LL_ADC_SGLDIFF_CAL_FACTOR_MASK" because   */
  /* containing other bits reserved for other purpose.                        */
  return (uint32_t)(STM32_READ_BIT(p_adc->CALFACT,
                                   (input_mode & LL_ADC_SGLDIFF_CAL_FACTOR_MASK))
                    >> ((input_mode & LL_ADC_SGLDIFF_CAL_F_BIT_D_MASK) >>
                        LL_ADC_SGLDIFF_CAL_F_BIT_D_SHIFT4));
}

/**
  * @brief  Set ADC resolution.
  *         Refer to reference manual for alignments formats
  *         dependencies to ADC resolutions.
  * @rmtoll
  *  CFGR1    RES            LL_ADC_SetResolution
  * @param  p_adc Pointer to ADC instance
  * @param  resolution This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetResolution(ADC_TypeDef *p_adc, uint32_t resolution)
{
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_RES, resolution);
}

/**
  * @brief  Get ADC resolution.
  *         Refer to reference manual for alignments formats
  *         dependencies to ADC resolutions.
  * @rmtoll
  *  CFGR1    RES            LL_ADC_GetResolution
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  */
__STATIC_INLINE uint32_t LL_ADC_GetResolution(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_RES));
}

/**
  * @brief  Set ADC conversion data left bit shift for ADC group regular conversions.
  * @rmtoll
  *  CFGR2    LSHIFT         LL_ADC_SetLeftBitShiftReg
  * @param  p_adc Pointer to ADC instance
  * @param  left_bit_shift This parameter can be one of the following values:
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_NONE
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_1
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_2
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_3
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_4
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_5
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_6
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_7
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_8
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_9
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_10
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_11
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_12
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_13
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_14
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_15
  * @note   On this STM32 series, left bit shift applies to ADC group regular only.
  *         For the equivalent post-processing on ADC group injected, refer to @ref LL_ADC_SetLeftBitShiftInj().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_SetLeftBitShiftReg(ADC_TypeDef *p_adc, uint32_t left_bit_shift)
{
  STM32_MODIFY_REG(p_adc->CFGR2, ADC_CFGR2_LSHIFT, left_bit_shift);
}

/**
  * @brief  Get ADC conversion data left bit shift for ADC group regular conversions.
  * @rmtoll
  *  CFGR2    LSHIFT         LL_ADC_GetLeftBitShiftReg
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_NONE
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_1
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_2
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_3
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_4
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_5
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_6
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_7
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_8
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_9
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_10
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_11
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_12
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_13
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_14
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_15
  */
__STATIC_INLINE uint32_t LL_ADC_GetLeftBitShiftReg(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR2, ADC_CFGR2_LSHIFT));
}

/**
  * @brief  Set ADC conversion data left bit shift for ADC group injected conversions.
  * @rmtoll
  *  CFGR3    JLSHIFT        LL_ADC_SetLeftBitShiftInj
  * @param  p_adc Pointer to ADC instance
  * @param  left_bit_shift This parameter can be one of the following values:
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_NONE
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_1
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_2
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_3
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_4
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_5
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_6
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_7
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_8
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_9
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_10
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_11
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_12
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_13
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_14
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_15
  * @note   On this STM32 series, left bit shift applies to ADC group injected only.
  *         For the equivalent post-processing on ADC group regular, regfer to @ref LL_ADC_SetLeftBitShiftReg().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_SetLeftBitShiftInj(ADC_TypeDef *p_adc, uint32_t left_bit_shift)
{
  STM32_MODIFY_REG(p_adc->CFGR3, ADC_CFGR3_JLSHIFT, left_bit_shift);
}

/**
  * @brief  Get ADC conversion data left bit shift for ADC group injected conversions.
  * @rmtoll
  *  CFGR3    JLSHIFT         LL_ADC_GetLeftBitShiftInj
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_NONE
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_1
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_2
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_3
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_4
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_5
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_6
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_7
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_8
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_9
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_10
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_11
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_12
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_13
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_14
  *         @arg @ref LL_ADC_LEFT_BIT_SHIFT_15
  */
__STATIC_INLINE uint32_t LL_ADC_GetLeftBitShiftInj(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR3, ADC_CFGR3_JLSHIFT));
}
/**
  * @brief  Set ADC low power mode auto wait.
  * @rmtoll
  *  CFGR1     AUTDLY       LL_ADC_SetLPModeAutoWait
  * @param  p_adc Pointer to ADC instance
  * @param  low_power_mode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_LP_AUTO_WAIT_DISABLE
  *         @arg @ref LL_ADC_LP_AUTO_WAIT_ENABLE
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_SetLPModeAutoWait(ADC_TypeDef *p_adc, uint32_t low_power_mode)
{
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_AUTDLY, low_power_mode);
}

/**
  * @brief  Get ADC low power mode auto wait.
  * @rmtoll
  *  CFGR1     AUTDLY       LL_ADC_GetLPModeAutoWait
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_LP_AUTO_WAIT_DISABLE
  *         @arg @ref LL_ADC_LP_AUTO_WAIT_ENABLE
  */
__STATIC_INLINE uint32_t LL_ADC_GetLPModeAutoWait(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_AUTDLY));
}

/**
  * @brief  Legacy function of @ref LL_ADC_SetLPModeAutoWait().
  * @rmtoll
  *  CFGR1     AUTDLY       LL_ADC_SetLowPowerMode
  * @param  p_adc Pointer to ADC instance
  * @param  low_power_mode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_LP_AUTO_WAIT_DISABLE
  *         @arg @ref LL_ADC_LP_AUTO_WAIT_ENABLE
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_SetLowPowerMode(ADC_TypeDef *p_adc, uint32_t low_power_mode)
{
  LL_ADC_SetLPModeAutoWait(p_adc, low_power_mode);
}

/**
  * @brief  Legacy function of @ref LL_ADC_GetLPModeAutoWait().
  * @rmtoll
  *  CFGR1     AUTDLY       LL_ADC_GetLowPowerMode
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_LP_AUTO_WAIT_DISABLE
  *         @arg @ref LL_ADC_LP_AUTO_WAIT_ENABLE
  */
__STATIC_INLINE uint32_t LL_ADC_GetLowPowerMode(const ADC_TypeDef *p_adc)
{
  return LL_ADC_GetLPModeAutoWait(p_adc);
}

/**
  * @brief  Set ADC gain compensation applied to raw converted data.
  * @rmtoll
  *  GCOMP    GCOMPCOEFF     LL_ADC_SetGainCompensation\n
  *  CFGR2    GCOMP          LL_ADC_SetGainCompensation
  * @param  p_adc Pointer to ADC instance
  * @param  gain_compensation Gain compensation enable state and value.
  *         Value between Min_Data=0 and Max_Data=16393
  * @note   ADC conversion raw data is computed with gain value using the formula:
  *           DATA = DATA(raw) * (gain compensation coef) / 4096
  *         Therefore, value 4096 corresponds to unitary gain (gain compensation disabled)
  * @note   Gain compensation is applied to all ADC conversions (independently of groups or channels).
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetGainCompensation(ADC_TypeDef *p_adc, uint32_t gain_compensation)
{
  STM32_MODIFY_REG(p_adc->GCOMP, ADC_GCOMP_GCOMPCOEFF, gain_compensation);
  STM32_MODIFY_REG(p_adc->GCOMP, ADC_GCOMP_GCOMP,
                   ((gain_compensation == LL_ADC_GAIN_COMPENSATION_DIV) ? 0UL : 1UL) << ADC_GCOMP_GCOMP_Pos);
}

/**
  * @brief  Get the ADC gain compensation value.
  * @rmtoll
  *  GCOMP    GCOMPCOEFF     LL_ADC_GetGainCompensation\n
  *  CFGR2    GCOMP          LL_ADC_GetGainCompensation
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value between Min_Data=0 and Max_Data=16393
  */
__STATIC_INLINE uint32_t LL_ADC_GetGainCompensation(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->GCOMP, ADC_GCOMP_GCOMP) == ADC_GCOMP_GCOMP) \
          ? STM32_READ_BIT(p_adc->GCOMP, ADC_GCOMP_GCOMPCOEFF) : 4096UL);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Group_Regular Configuration of ADC hierarchical scope: group regular
  * @{
  */

/**
  * @brief  Set ADC group regular conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         EXTI line).
  * @rmtoll
  *  CFGR1    EXTSEL         LL_ADC_REG_SetTriggerSource\n
  *  CFGR1    EXTEN          LL_ADC_REG_SetTriggerSource
  * @param  p_adc Pointer to ADC instance
  * @param  trigger_source This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_SOFTWARE
  *         @arg @ref LL_ADC_REG_TRIG_TIM1_OC3
  *         @arg @ref LL_ADC_REG_TRIG_TIM1_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM1_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_TIM2_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM3_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM4_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM6_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM20_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM20_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_TIM26_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_LPTIM1_OC1
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG1
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG2
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG3
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG4
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG5
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG6
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG7
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG8
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG9
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG10
  *         @arg @ref LL_ADC_REG_TRIG_TIM8_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM8_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_TIM9_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM15_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM20_OC1
  *         @arg @ref LL_ADC_REG_TRIG_TIM20_OC2
  *         @arg @ref LL_ADC_REG_TRIG_EXTI11 (1)
  *         @arg @ref LL_ADC_REG_TRIG_TIM1_OC1    (1)
  *         @arg @ref LL_ADC_REG_TRIG_TIM1_OC2    (1)
  *         @arg @ref LL_ADC_REG_TRIG_TIM2_OC2    (1)
  *         @arg @ref LL_ADC_REG_TRIG_TIM3_OC4    (1)
  *         @arg @ref LL_ADC_REG_TRIG_TIM4_OC4    (1)
  *         @arg @ref LL_ADC_REG_TRIG_PLAY1_OUT11 (1)
  * @if ADC3
  *         @arg @ref LL_ADC_REG_TRIG_EXTI2  (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM2_OC1    (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM2_OC3    (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM3_OC1    (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM3_OC2    (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM4_OC1    (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM8_OC1    (2)
  *         @arg @ref LL_ADC_REG_TRIG_PLAY1_OUT12 (2)
  * @endif
  *
  *         (1) On this STM32 series, parameter available only on ADC instance: ADC1, ADC2\n
  *         (2) On this STM32 series, parameter available only on ADC instance: ADC3.
  * @note   On this STM32 series, setting trigger source to external trigger
  *         also set trigger polarity to rising edge
  *         (default setting for compatibility with some ADC on other
  *         STM32 series having this setting set by HW default value).
  *         In case of need to modify trigger edge, use
  *         function @ref LL_ADC_REG_SetTriggerEdge().
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_REG_SetTriggerSource(ADC_TypeDef *p_adc, uint32_t trigger_source)
{
#if defined(ADC3)
  /* Manage trigger sources diversity across instances with look up table */
  if (((uint32_t)trigger_source) >= LL_ADC_REG_TRIG_SRC_COUNT) /* LL_ADC_REG_TRIG_SOFTWARE */
  {
    STM32_CLEAR_BIT(p_adc->CFGR1, ADC_CFGR1_EXTEN | ADC_CFGR1_EXTSEL);
  }
  else
  {
    uint32_t trig_src_bitfield = LL_ADC_REG_TRIG_SRC_LUT[trigger_source][LL_ADC_TRIG_SRC_LUT_INST_INDEX(p_adc)];

    STM32_MODIFY_REG(p_adc->CFGR1,
                     ADC_CFGR1_EXTEN | ADC_CFGR1_EXTSEL, LL_ADC_REG_TRIG_EDGE_DEFAULT \
                     | ((trig_src_bitfield << ADC_CFGR1_EXTSEL_Pos) & ADC_CFGR1_EXTSEL));

    /* Manage case of trigger requiring additional configuration (option bit) */
    if ((trig_src_bitfield & LL_ADC_TRIG_OP_NB_MASK) != 0UL)
    {
      uint32_t option_bit_nb = ((trig_src_bitfield & LL_ADC_TRIG_OP_NB_MASK) >> LL_ADC_TRIG_OP_NB_POS)
                               + LL_ADC_TRIG_OP_NB_ADD_REG;

      STM32_MODIFY_REG(p_adc->OR,
                       (1UL << option_bit_nb), (((trig_src_bitfield & LL_ADC_TRIG_OP_STATE_MASK) \
                                                 >> LL_ADC_TRIG_OP_STATE_POS) << option_bit_nb));
    }
  }
#else
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_EXTEN | ADC_CFGR1_EXTSEL, trigger_source);

  /* Manage case of trigger requiring additional configuration (option bit) */
  if ((trigger_source & LL_ADC_TRIG_OP_NB_MASK) != 0UL)
  {
    uint32_t option_bit_nb = ((trigger_source & LL_ADC_TRIG_OP_NB_MASK) >> LL_ADC_TRIG_OP_NB_POS);

    STM32_MODIFY_REG(p_adc->OR,
                     (1UL << option_bit_nb),
                     (((trigger_source & LL_ADC_TRIG_OP_STATE_MASK) >> LL_ADC_TRIG_OP_STATE_POS) << option_bit_nb));
  }
#endif /* ADC3 */
}

/**
  * @brief  Get ADC group regular conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         EXTI line).
  * @rmtoll
  *  CFGR1    EXTSEL         LL_ADC_REG_GetTriggerSource\n
  *  CFGR1    EXTEN          LL_ADC_REG_GetTriggerSource
  * @param  p_adc Pointer to ADC instance
  * @note   To determine whether group regular trigger source is
  *         internal (SW start) or external, without detail
  *         of which peripheral is selected as external trigger,
  *         (equivalent to
  *         "if(LL_ADC_REG_GetTriggerSource(ADC1) == LL_ADC_REG_TRIG_SOFTWARE)")
  *         use function @ref LL_ADC_REG_IsTriggerSourceSWStart.
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_SOFTWARE
  *         @arg @ref LL_ADC_REG_TRIG_TIM1_OC3
  *         @arg @ref LL_ADC_REG_TRIG_TIM1_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM1_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_TIM2_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM3_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM4_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM6_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM20_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM20_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_TIM26_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_LPTIM1_OC1
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG1
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG2
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG3
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG4
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG5
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG6
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG7
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG8
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG9
  *         @arg @ref LL_ADC_REG_TRIG_HRTIM1_TRG10
  *         @arg @ref LL_ADC_REG_TRIG_TIM8_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM8_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_TIM9_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM15_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_TIM20_OC1
  *         @arg @ref LL_ADC_REG_TRIG_TIM20_OC2
  *         @arg @ref LL_ADC_REG_TRIG_EXTI11 (1)
  *         @arg @ref LL_ADC_REG_TRIG_TIM1_OC1    (1)
  *         @arg @ref LL_ADC_REG_TRIG_TIM1_OC2    (1)
  *         @arg @ref LL_ADC_REG_TRIG_TIM2_OC2    (1)
  *         @arg @ref LL_ADC_REG_TRIG_TIM3_OC4    (1)
  *         @arg @ref LL_ADC_REG_TRIG_TIM4_OC4    (1)
  *         @arg @ref LL_ADC_REG_TRIG_PLAY1_OUT11 (1)
  * @if ADC3
  *         @arg @ref LL_ADC_REG_TRIG_EXTI2  (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM2_OC1    (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM2_OC3    (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM3_OC1    (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM3_OC2    (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM4_OC1    (2)
  *         @arg @ref LL_ADC_REG_TRIG_TIM8_OC1    (2)
  *         @arg @ref LL_ADC_REG_TRIG_PLAY1_OUT12 (2)
  * @endif
  *
  *         (1) On this STM32 series, parameter available only on ADC instance: ADC1, ADC2\n
  *         (2) On this STM32 series, parameter available only on ADC instance: ADC3.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetTriggerSource(const ADC_TypeDef *p_adc)
{
#if defined(ADC3)
  /* Manage trigger sources diversity across instances with look up table */
  if (STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_EXTEN) == 0UL)
  {
    return LL_ADC_REG_TRIG_SOFTWARE;
  }
  else
  {
    __IO uint32_t trig_src_reg_val = (STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_EXTSEL) >> ADC_CFGR1_EXTSEL_Pos);
    uint32_t instance_index_lut = LL_ADC_TRIG_SRC_LUT_INST_INDEX(p_adc);
    uint32_t index_lut;
    uint32_t trig_src_bitfield = 0U;

    /* Parse look up table until match of register value and ADC instance */
    for (index_lut = 0U; index_lut < LL_ADC_REG_TRIG_SRC_COUNT; index_lut++)
    {
      trig_src_bitfield = LL_ADC_REG_TRIG_SRC_LUT[index_lut][instance_index_lut];
      if (trig_src_reg_val == (trig_src_bitfield & (ADC_CFGR1_EXTSEL >> ADC_CFGR1_EXTSEL_Pos)))
      {
        break;
      }
    }

    /* Manage case of trigger requiring additional configuration (option bit) */
    if ((trig_src_bitfield & LL_ADC_TRIG_OP_NB_MASK) != 0UL)
    {
      uint32_t option_bit_nb = ((trig_src_bitfield & LL_ADC_TRIG_OP_NB_MASK) >> LL_ADC_TRIG_OP_NB_POS)
                               + LL_ADC_TRIG_OP_NB_ADD_REG;
      trig_src_reg_val = (trig_src_bitfield & ~LL_ADC_TRIG_OP_STATE_MASK);
      if (STM32_READ_BIT(p_adc->OR, (1UL << option_bit_nb)) != 0UL)
      {
        trig_src_reg_val |= (1UL << LL_ADC_TRIG_OP_STATE_POS);
      }
      else
      {
        trig_src_reg_val &= ~(1UL << LL_ADC_TRIG_OP_STATE_POS);
      }

      /* Parse look up table with bitfield including option bit */
      for (index_lut = 0U; index_lut < LL_ADC_REG_TRIG_SRC_COUNT; index_lut++)
      {
        trig_src_bitfield = LL_ADC_REG_TRIG_SRC_LUT[index_lut][instance_index_lut];
        if (trig_src_reg_val == trig_src_bitfield)
        {
          break;
        }
      }
    }

    return index_lut;
  }
#else
  __IO uint32_t trigger_source = STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_EXTSEL | ADC_CFGR1_EXTEN);

  /* Value for shift of [0, 4, 8, 12] depending on value of bitfield corresponding to ADC_CFGR_EXTEN [0, 1, 2, 3] */
  uint32_t shift_exten = ((trigger_source & ADC_CFGR1_EXTEN) >> (ADC_CFGR1_EXTEN_Pos - 2UL));

  /* Set bitfield corresponding to ADC_CFGR1_EXTEN and ADC_CFGR1_EXTSEL to match with triggers literals definition */
  return ((trigger_source
           & (LL_ADC_REG_TRIG_SOURCE_MASK >> shift_exten) & ADC_CFGR1_EXTSEL)
          | ((LL_ADC_REG_TRIG_EDGE_MASK >> shift_exten) & ADC_CFGR1_EXTEN)
         );
#endif /* ADC3 */
}

/**
  * @brief  Get ADC group regular conversion trigger source internal (SW start)
  *         or external.
  * @rmtoll
  *  CFGR1    EXTEN          LL_ADC_REG_IsTriggerSourceSWStart
  * @param  p_adc Pointer to ADC instance
  * @note   In case of group regular trigger source set to external trigger,
  *         to determine which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_REG_GetTriggerSource().
  * @retval Value "0" if trigger source external trigger
  *         Value "1" if trigger source SW start.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsTriggerSourceSWStart(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_EXTEN) == 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Set ADC group regular conversion trigger polarity.
  * @rmtoll
  *  CFGR1    EXTEN          LL_ADC_REG_SetTriggerEdge
  * @param  p_adc Pointer to ADC instance
  * @param  external_trigger_edge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_RISING
  *         @arg @ref LL_ADC_REG_TRIG_FALLING
  *         @arg @ref LL_ADC_REG_TRIG_RISING_FALLING
  * @note   Applicable only for trigger source set to external trigger.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_REG_SetTriggerEdge(ADC_TypeDef *p_adc, uint32_t external_trigger_edge)
{
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_EXTEN, external_trigger_edge);
}

/**
  * @brief  Get ADC group regular conversion trigger polarity.
  * @rmtoll
  *  CFGR1    EXTEN          LL_ADC_REG_GetTriggerEdge
  * @param  p_adc Pointer to ADC instance
  * @note   Applicable only for trigger source set to external trigger.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_RISING
  *         @arg @ref LL_ADC_REG_TRIG_FALLING
  *         @arg @ref LL_ADC_REG_TRIG_RISING_FALLING
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetTriggerEdge(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_EXTEN));
}

/**
  * @brief  Set ADC sampling mode.
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  * @rmtoll
  *  CFGR2    BULB           LL_ADC_SetSamplingMode\n
  *  CFGR2    SMPTRIG        LL_ADC_SetSamplingMode
  * @param  p_adc Pointer to ADC instance
  * @param  sampling_mode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLING_MODE_NORMAL
  *         @arg @ref LL_ADC_SAMPLING_MODE_BULB
  *         @arg @ref LL_ADC_SAMPLING_MODE_TRIGGER_CTRL
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_SetSamplingMode(ADC_TypeDef *p_adc, uint32_t sampling_mode)
{
  STM32_MODIFY_REG(p_adc->CFGR2, ADC_CFGR2_BULB | ADC_CFGR2_SMPTRIG, sampling_mode);
}

/**
  * @brief  Get the ADC sampling mode.
  * @rmtoll
  *  CFGR2    BULB           LL_ADC_GetSamplingMode\n
  *  CFGR2    SMPTRIG        LL_ADC_GetSamplingMode
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLING_MODE_NORMAL
  *         @arg @ref LL_ADC_SAMPLING_MODE_BULB
  *         @arg @ref LL_ADC_SAMPLING_MODE_TRIGGER_CTRL
  */
__STATIC_INLINE uint32_t LL_ADC_GetSamplingMode(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR2, ADC_CFGR2_BULB | ADC_CFGR2_SMPTRIG));
}

/**
  * @brief  Set ADC differential input mode pseudo differential.
  * @rmtoll
  *  CFGR2    PDIFF          LL_ADC_SetChannelInPseudoDiff\n
  *  CFGR2    PDIFFREF       LL_ADC_SetChannelInPseudoDiff
  * @param  p_adc Pointer to ADC instance
  * @param  sampling_mode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_IN_PSEUDO_DIFF_DISABLE
  *         @arg @ref LL_ADC_IN_PSEUDO_DIFF_VREFM
  *         @arg @ref LL_ADC_IN_PSEUDO_DIFF_VREFP_2
  * @note   Overrides differential mode for the entire ADC instance. If all channels
            are in single ended mode, this parameters has no effect.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled
  */
__STATIC_INLINE void LL_ADC_SetChannelInPseudoDiff(ADC_TypeDef *p_adc, uint32_t sampling_mode)
{
  STM32_MODIFY_REG(p_adc->CFGR2, ADC_CFGR2_PDIFFREF | ADC_CFGR2_PDIFF, sampling_mode);
}

/**
  * @brief  Get ADC differential input mode pseudo differential.
  * @rmtoll
  *  CFGR2    PDIFF          LL_ADC_GetChannelInPseudoDiff\n
  *  CFGR2    PDIFFREF       LL_ADC_GetChannelInPseudoDiff
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_IN_PSEUDO_DIFF_DISABLE
  *         @arg @ref LL_ADC_IN_PSEUDO_DIFF_VREFM
  *         @arg @ref LL_ADC_IN_PSEUDO_DIFF_VREFP_2
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelInPseudoDiff(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR2, ADC_CFGR2_PDIFFREF | ADC_CFGR2_PDIFF));
}

/**
  * @brief  Start ADC sampling phase for sampling time trigger mode.
  * @rmtoll
  *  CFGR2    SWTRIG         LL_ADC_REG_StartSamplingPhase
  * @param  p_adc Pointer to ADC instance
  * @note   This function is relevant only when
  *         - @ref LL_ADC_SAMPLING_MODE_TRIGGER_CTRL has been set
  *           using @ref LL_ADC_SetSamplingMode
  *         - @ref LL_ADC_REG_TRIG_SOFTWARE is used as trigger source
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion ongoing on group regular,
  *         without conversion stop command ongoing on group regular,
  *         without ADC disable command ongoing.
  */
__STATIC_INLINE void LL_ADC_REG_StartSamplingPhase(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->CFGR2, ADC_CFGR2_SWTRIG);
}

/**
  * @brief  Stop ADC sampling phase for sampling time trigger mode and start conversion.
  * @rmtoll
  *  CFGR2    SWTRIG         LL_ADC_REG_StopSamplingPhase
  * @param  p_adc Pointer to ADC instance
  * @note   This function is relevant only when
  *         - @ref LL_ADC_SAMPLING_MODE_TRIGGER_CTRL has been set
  *           using @ref LL_ADC_SetSamplingMode
  *         - @ref LL_ADC_REG_TRIG_SOFTWARE is used as trigger source
  *         - @ref LL_ADC_REG_StartSamplingPhase has been called to start
  *           the sampling phase
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion ongoing on group regular,
  *         without conversion stop command ongoing on group regular,
  *         without ADC disable command ongoing.
  */
__STATIC_INLINE void LL_ADC_REG_StopSamplingPhase(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->CFGR2, ADC_CFGR2_SWTRIG);
}

/**
  * @brief  Set ADC group regular sequencer length and scan direction.
  * @rmtoll
  *  SQR1     LEN            LL_ADC_REG_SetSequencerLength
  * @param  p_adc Pointer to ADC instance
  * @param  sequencer_nb_ranks This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS
  * @note   Description of ADC group regular sequencer features:
  *         - For devices with sequencer fully configurable
  *           (function "LL_ADC_REG_SetSequencerRanks()" available):
  *           sequencer length and each rank affectation to a channel
  *           are configurable.
  *           This function performs configuration of:
  *           - Sequence length: Number of ranks in the scan sequence.
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerRanks()".
  *         - For devices with sequencer not fully configurable
  *           (function "LL_ADC_REG_SetSequencerChannels()" available):
  *           sequencer length and each rank affectation to a channel
  *           are defined by channel number.
  *           This function performs configuration of:
  *           - Sequence length: Number of ranks in the scan sequence is
  *             defined by number of channels set in the sequence,
  *             rank of each channel is fixed by channel HW number.
  *             (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerLength(ADC_TypeDef *p_adc, uint32_t sequencer_nb_ranks)
{
  STM32_MODIFY_REG(p_adc->SQR1, ADC_SQR1_LEN, sequencer_nb_ranks);
}

/**
  * @brief  Get ADC group regular sequencer length and scan direction.
  * @rmtoll
  *  SQR1     LEN            LL_ADC_REG_GetSequencerLength
  * @param  p_adc Pointer to ADC instance
  * @note   Description of ADC group regular sequencer features:
  *         - For devices with sequencer fully configurable
  *           (function "LL_ADC_REG_SetSequencerRanks()" available):
  *           sequencer length and each rank affectation to a channel
  *           are configurable.
  *           This function retrieves:
  *           - Sequence length: Number of ranks in the scan sequence.
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerRanks()".
  *         - For devices with sequencer not fully configurable
  *           (function "LL_ADC_REG_SetSequencerChannels()" available):
  *           sequencer length and each rank affectation to a channel
  *           are defined by channel number.
  *           This function retrieves:
  *           - Sequence length: Number of ranks in the scan sequence is
  *             defined by number of channels set in the sequence,
  *             rank of each channel is fixed by channel HW number.
  *             (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerChannels()".
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerLength(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->SQR1, ADC_SQR1_LEN));
}

/**
  * @brief  Set ADC group regular sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @rmtoll
  *  CFGR1    DISCEN         LL_ADC_REG_SetSequencerDiscont\n
  *  CFGR1    DISCNUM        LL_ADC_REG_SetSequencerDiscont
  * @param  p_adc Pointer to ADC instance
  * @param  seq_discont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_1RANK
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_8RANKS
  * @note   It is not possible to enable both ADC group regular
  *         continuous mode and sequencer discontinuous mode.
  * @note   It is not possible to enable both ADC auto-injected mode
  *         and ADC group regular sequencer discontinuous mode.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerDiscont(ADC_TypeDef *p_adc, uint32_t seq_discont)
{
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_DISCEN | ADC_CFGR1_DISCNUM, seq_discont);
}

/**
  * @brief  Get ADC group regular sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @rmtoll
  *  CFGR1    DISCEN         LL_ADC_REG_GetSequencerDiscont\n
  *  CFGR1    DISCNUM        LL_ADC_REG_GetSequencerDiscont
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_1RANK
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_8RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerDiscont(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_DISCEN | ADC_CFGR1_DISCNUM));
}

/**
  * @brief  Set ADC group regular sequence: channel on the selected
  *         scan sequence rank.
  * @rmtoll
  *  SQR1     SQ1            LL_ADC_REG_SetSequencerRanks\n
  *  SQR1     SQ2            LL_ADC_REG_SetSequencerRanks\n
  *  SQR1     SQ3            LL_ADC_REG_SetSequencerRanks\n
  *  SQR1     SQ4            LL_ADC_REG_SetSequencerRanks\n
  *  SQR2     SQ5            LL_ADC_REG_SetSequencerRanks\n
  *  SQR2     SQ6            LL_ADC_REG_SetSequencerRanks\n
  *  SQR2     SQ7            LL_ADC_REG_SetSequencerRanks\n
  *  SQR2     SQ8            LL_ADC_REG_SetSequencerRanks\n
  *  SQR2     SQ9            LL_ADC_REG_SetSequencerRanks\n
  *  SQR3     SQ10           LL_ADC_REG_SetSequencerRanks\n
  *  SQR3     SQ11           LL_ADC_REG_SetSequencerRanks\n
  *  SQR3     SQ12           LL_ADC_REG_SetSequencerRanks\n
  *  SQR3     SQ13           LL_ADC_REG_SetSequencerRanks\n
  *  SQR3     SQ14           LL_ADC_REG_SetSequencerRanks\n
  *  SQR4     SQ15           LL_ADC_REG_SetSequencerRanks\n
  *  SQR4     SQ16           LL_ADC_REG_SetSequencerRanks
  * @param  p_adc Pointer to ADC instance
  * @param  rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_RANK_1
  *         @arg @ref LL_ADC_REG_RANK_2
  *         @arg @ref LL_ADC_REG_RANK_3
  *         @arg @ref LL_ADC_REG_RANK_4
  *         @arg @ref LL_ADC_REG_RANK_5
  *         @arg @ref LL_ADC_REG_RANK_6
  *         @arg @ref LL_ADC_REG_RANK_7
  *         @arg @ref LL_ADC_REG_RANK_8
  *         @arg @ref LL_ADC_REG_RANK_9
  *         @arg @ref LL_ADC_REG_RANK_10
  *         @arg @ref LL_ADC_REG_RANK_11
  *         @arg @ref LL_ADC_REG_RANK_12
  *         @arg @ref LL_ADC_REG_RANK_13
  *         @arg @ref LL_ADC_REG_RANK_14
  *         @arg @ref LL_ADC_REG_RANK_15
  *         @arg @ref LL_ADC_REG_RANK_16
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   This function performs configuration of:
  *         - Channels ordering into each rank of scan sequence:
  *           whatever channel can be placed into whatever rank.
  * @note   On this STM32 series, ADC group regular sequencer is
  *         fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels can be not available.
  *         Refer to device datasheet for channels availability.
  * @note   On this STM32 series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerRanks(ADC_TypeDef *p_adc, uint32_t rank, uint32_t channel)
{
  /* Set bits with content of parameter "Channel" with bits position          */
  /* in register and register position depending on parameter "Rank".         */
  /* Parameters "Rank" and "Channel" are used with masks because containing   */
  /* other bits reserved for other purpose.                                   */
  __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->SQR1,
                                              ((rank & LL_ADC_REG_SQRX_REGOFFSET_MASK) >> LL_ADC_SQRX_REGOFFSET_POS));

  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);

  STM32_MODIFY_REG(*preg,
                   LL_ADC_CHANNEL_ID_NB_MASK_POSBIT0 << (rank & LL_ADC_REG_RANK_ID_SQRX_MASK),
                   (channel_remapped & LL_ADC_CH_NUMBER_MASK) << (rank & LL_ADC_REG_RANK_ID_SQRX_MASK));
}

/**
  * @brief  Get ADC group regular sequence: channel on the selected
  *         scan sequence rank.
  * @rmtoll
  *  SQR1     SQ1            LL_ADC_REG_GetSequencerRanks\n
  *  SQR1     SQ2            LL_ADC_REG_GetSequencerRanks\n
  *  SQR1     SQ3            LL_ADC_REG_GetSequencerRanks\n
  *  SQR1     SQ4            LL_ADC_REG_GetSequencerRanks\n
  *  SQR2     SQ5            LL_ADC_REG_GetSequencerRanks\n
  *  SQR2     SQ6            LL_ADC_REG_GetSequencerRanks\n
  *  SQR2     SQ7            LL_ADC_REG_GetSequencerRanks\n
  *  SQR2     SQ8            LL_ADC_REG_GetSequencerRanks\n
  *  SQR2     SQ9            LL_ADC_REG_GetSequencerRanks\n
  *  SQR3     SQ10           LL_ADC_REG_GetSequencerRanks\n
  *  SQR3     SQ11           LL_ADC_REG_GetSequencerRanks\n
  *  SQR3     SQ12           LL_ADC_REG_GetSequencerRanks\n
  *  SQR3     SQ13           LL_ADC_REG_GetSequencerRanks\n
  *  SQR3     SQ14           LL_ADC_REG_GetSequencerRanks\n
  *  SQR4     SQ15           LL_ADC_REG_GetSequencerRanks\n
  *  SQR4     SQ16           LL_ADC_REG_GetSequencerRanks
  * @param  p_adc Pointer to ADC instance
  * @param  rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_RANK_1
  *         @arg @ref LL_ADC_REG_RANK_2
  *         @arg @ref LL_ADC_REG_RANK_3
  *         @arg @ref LL_ADC_REG_RANK_4
  *         @arg @ref LL_ADC_REG_RANK_5
  *         @arg @ref LL_ADC_REG_RANK_6
  *         @arg @ref LL_ADC_REG_RANK_7
  *         @arg @ref LL_ADC_REG_RANK_8
  *         @arg @ref LL_ADC_REG_RANK_9
  *         @arg @ref LL_ADC_REG_RANK_10
  *         @arg @ref LL_ADC_REG_RANK_11
  *         @arg @ref LL_ADC_REG_RANK_12
  *         @arg @ref LL_ADC_REG_RANK_13
  *         @arg @ref LL_ADC_REG_RANK_14
  *         @arg @ref LL_ADC_REG_RANK_15
  *         @arg @ref LL_ADC_REG_RANK_16
  * @note   On this STM32 series, ADC group regular sequencer is
  *         fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels can be not available.
  *         Refer to device datasheet for channels availability.
  * @note   Usage of the returned channel number:
  *         - To reinject this channel into another function LL_ADC_xxx:
  *           the returned channel number is only partly formatted on definition
  *           of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *           with parts of literals LL_ADC_CHANNEL_x or using
  *           helper macro @ref LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Then the selected literal LL_ADC_CHANNEL_x can be used
  *           as parameter for another function.
  *         - To get the channel number in decimal format:
  *           process the returned value with the helper macro
  *           @ref LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.\n
  *         (4) For ADC channel read back from ADC register,
  *             comparison with internal channel parameter to be done
  *             using helper macro @ref LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerRanks(const ADC_TypeDef *p_adc, uint32_t rank)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->SQR1, ((rank & LL_ADC_REG_SQRX_REGOFFSET_MASK)
                                                                  >> LL_ADC_SQRX_REGOFFSET_POS));

  uint32_t channel = ((STM32_READ_BIT(*preg,
                                      LL_ADC_CHANNEL_ID_NB_MASK_POSBIT0 << (rank & LL_ADC_REG_RANK_ID_SQRX_MASK))
                       >> (rank & LL_ADC_REG_RANK_ID_SQRX_MASK))
                     );

  return LL_ADC_REMAP_CHANNEL_GET(p_adc, channel);
}

/**
  * @brief  Set ADC channel preselection.
  * @rmtoll
  *  PCSEL   PCSEL0         LL_ADC_CHANNEL_0\n
  *  PCSEL   PCSEL1         LL_ADC_CHANNEL_1\n
  *  PCSEL   PCSEL2         LL_ADC_CHANNEL_2\n
  *  PCSEL   PCSEL3         LL_ADC_CHANNEL_3\n
  *  PCSEL   PCSEL4         LL_ADC_CHANNEL_4\n
  *  PCSEL   PCSEL5         LL_ADC_CHANNEL_5\n
  *  PCSEL   PCSEL6         LL_ADC_CHANNEL_6\n
  *  PCSEL   PCSEL7         LL_ADC_CHANNEL_7\n
  *  PCSEL   PCSEL8         LL_ADC_CHANNEL_8\n
  *  PCSEL   PCSEL9         LL_ADC_CHANNEL_9\n
  *  PCSEL   PCSEL10        LL_ADC_CHANNEL_10\n
  *  PCSEL   PCSEL11        LL_ADC_CHANNEL_11\n
  *  PCSEL   PCSEL12        LL_ADC_CHANNEL_12\n
  *  PCSEL   PCSEL13        LL_ADC_CHANNEL_13\n
  *  PCSEL   PCSEL14        LL_ADC_CHANNEL_14\n
  *  PCSEL   PCSEL15        LL_ADC_CHANNEL_15\n
  *  PCSEL   PCSEL16        LL_ADC_CHANNEL_16\n
  *  PCSEL   PCSEL17        LL_ADC_CHANNEL_17\n
  *  PCSEL   PCSEL18        LL_ADC_CHANNEL_18\n
  *  PCSEL   PCSEL19        LL_ADC_CHANNEL_19
  * @param  p_adc Pointer to ADC instance.
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  * @note   This function set the the value for the channel preselection register
  *         corresponding to ADC channel to be selected.
  */
__STATIC_INLINE void LL_ADC_SetChannelPreselection(ADC_TypeDef *p_adc, uint32_t channel)
{
  __IO uint32_t channel_preselection = STM32_READ_REG(p_adc->PCSEL);

  STM32_WRITE_REG(p_adc->PCSEL,
                  channel_preselection | (1UL << (LL_ADC_CHANNEL_TO_DECIMAL_NB((uint32_t)channel) & 0x1FUL)));
}

/**
  * @brief  Get ADC channel preselection.
  * @rmtoll
  *  PCSEL   PCSEL0         LL_ADC_CHANNEL_0\n
  *  PCSEL   PCSEL1         LL_ADC_CHANNEL_1\n
  *  PCSEL   PCSEL2         LL_ADC_CHANNEL_2\n
  *  PCSEL   PCSEL3         LL_ADC_CHANNEL_3\n
  *  PCSEL   PCSEL4         LL_ADC_CHANNEL_4\n
  *  PCSEL   PCSEL5         LL_ADC_CHANNEL_5\n
  *  PCSEL   PCSEL6         LL_ADC_CHANNEL_6\n
  *  PCSEL   PCSEL7         LL_ADC_CHANNEL_7\n
  *  PCSEL   PCSEL8         LL_ADC_CHANNEL_8\n
  *  PCSEL   PCSEL9         LL_ADC_CHANNEL_9\n
  *  PCSEL   PCSEL10        LL_ADC_CHANNEL_10\n
  *  PCSEL   PCSEL11        LL_ADC_CHANNEL_11\n
  *  PCSEL   PCSEL12        LL_ADC_CHANNEL_12\n
  *  PCSEL   PCSEL13        LL_ADC_CHANNEL_13\n
  *  PCSEL   PCSEL14        LL_ADC_CHANNEL_14\n
  *  PCSEL   PCSEL15        LL_ADC_CHANNEL_15\n
  *  PCSEL   PCSEL16        LL_ADC_CHANNEL_16\n
  *  PCSEL   PCSEL17        LL_ADC_CHANNEL_17\n
  *  PCSEL   PCSEL18        LL_ADC_CHANNEL_18\n
  *  PCSEL   PCSEL19        LL_ADC_CHANNEL_19
  * @param  p_adc Pointer to ADC instance.
  * @note   This function does not support specific case of multiple channels preselected.
  *         In this case, return value of this function is not relevant
  *         (corresponds to first channel preselected).
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelPreselection(const ADC_TypeDef *p_adc)
{
  uint32_t channel_preselection = STM32_READ_BIT(p_adc->PCSEL, ADC_PCSEL_PCSEL);

  if ((channel_preselection & ADC_PCSEL_PCSEL) == 0UL)
  {
    channel_preselection = LL_ADC_CHANNEL_NONE;
  }
  else if ((channel_preselection & ADC_PCSEL_PCSEL) == ADC_PCSEL_PCSEL)
  {
    /* Case all channels */
    channel_preselection = LL_ADC_CHANNEL_ALL;
  }
  else
  {
    /* In case of multiple channel, return value of first channel preselected */
    channel_preselection = STM32_POSITION_VAL(channel_preselection);
  }

  return LL_ADC_REMAP_CHANNEL_GET(p_adc, channel_preselection);
}

/**
  * @brief  Set ADC continuous conversion mode on ADC group regular.
  * @rmtoll
  *  CFGR1    CONT           LL_ADC_REG_SetContinuousMode
  * @param  p_adc Pointer to ADC instance
  * @param  continuous This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_CONV_SINGLE
  *         @arg @ref LL_ADC_REG_CONV_CONTINUOUS
  * @note   Description of ADC continuous conversion mode:
  *         - single mode: one conversion per trigger
  *         - continuous mode: after the first trigger, following
  *           conversions launched successively automatically.
  * @note   It is not possible to enable both ADC group regular
  *         continuous mode and sequencer discontinuous mode.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_REG_SetContinuousMode(ADC_TypeDef *p_adc, uint32_t continuous)
{
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_CONT, continuous);
}

/**
  * @brief  Get ADC continuous conversion mode on ADC group regular.
  * @rmtoll
  *  CFGR1    CONT           LL_ADC_REG_GetContinuousMode
  * @param  p_adc Pointer to ADC instance
  * @note   Description of ADC continuous conversion mode:
  *         - single mode: one conversion per trigger
  *         - continuous mode: after the first trigger, following
  *           conversions launched successively automatically.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_CONV_SINGLE
  *         @arg @ref LL_ADC_REG_CONV_CONTINUOUS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetContinuousMode(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_CONT));
}

/**
  * @brief  Set ADC data transfer mode for regular group.
  * @rmtoll
  *  CFGR1    DMNGT           LL_ADC_REG_SetDataTransferMode
  * @param  p_adc Pointer to ADC instance
  * @param  data_transfer_mode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRANSFER_DR
  *         @arg @ref LL_ADC_REG_TRANSFER_DMA_LIMITED
  *         @arg @ref LL_ADC_REG_TRANSFER_DMA_UNLIMITED
  * @note   To configure DMA source address (peripheral address),
  *         use function @ref LL_ADC_DMA_GetRegAddr().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_REG_SetDataTransferMode(ADC_TypeDef *p_adc, uint32_t data_transfer_mode)
{
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_DMNGT, data_transfer_mode);
}

/**
  * @brief  Get ADC data transfer mode for regular group.
  * @rmtoll
  *  CFGR1    DMNGT           LL_ADC_REG_GetDataTransferMode
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRANSFER_DR
  *         @arg @ref LL_ADC_REG_TRANSFER_DMA_LIMITED
  *         @arg @ref LL_ADC_REG_TRANSFER_DMA_UNLIMITED
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetDataTransferMode(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_DMNGT));
}

/**
  * @brief  Set ADC group regular behavior in case of overrun:
  *         data preserved or overwritten.
  * @rmtoll
  *  CFGR1    OVRMOD         LL_ADC_REG_SetOverrun
  * @param  p_adc Pointer to ADC instance
  * @param  overrun This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_OVR_DATA_PRESERVED
  *         @arg @ref LL_ADC_REG_OVR_DATA_OVERWRITTEN
  * @note   Compatibility with devices without feature overrun:
  *         other devices without this feature have a behavior
  *         equivalent to data overwritten.
  *         The default setting of overrun is data preserved.
  *         Therefore, for compatibility with all devices, parameter
  *         overrun can be set to data overwritten.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_REG_SetOverrun(ADC_TypeDef *p_adc, uint32_t overrun)
{
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_OVRMOD, overrun);
}

/**
  * @brief  Get ADC group regular behavior in case of overrun:
  *         data preserved or overwritten.
  * @rmtoll
  *  CFGR1    OVRMOD         LL_ADC_REG_GetOverrun
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_OVR_DATA_PRESERVED
  *         @arg @ref LL_ADC_REG_OVR_DATA_OVERWRITTEN
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetOverrun(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_OVRMOD));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Group_Injected Configuration of ADC hierarchical scope: group injected
  * @{
  */

/**
  * @brief  Set ADC group injected conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         EXTI line).
  * @rmtoll
  *  JSQR     JEXTSEL        LL_ADC_INJ_SetTriggerSource\n
  *  JSQR     JEXTEN         LL_ADC_INJ_SetTriggerSource
  * @param  p_adc Pointer to ADC instance
  * @param  trigger_source This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_SOFTWARE
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_OC4
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_TIM2_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM7_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_TIM12_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM15_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM16_OC1
  *         @arg @ref LL_ADC_INJ_TRIG_TIM20_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM20_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_TIM27_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_LPTIM1_OC2
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG1
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG2
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG3
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG4
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG5
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG6
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG7
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG8
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG9
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG10
  *         @arg @ref LL_ADC_INJ_TRIG_EXTI15 (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM2_OC1    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_OC1    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_OC3    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_OC4    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_TRGO   (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM4_TRGO   (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_OC4    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_PLAY1_OUT13 (1)
  * @if ADC3
  *         @arg @ref LL_ADC_INJ_TRIG_EXTI3  (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_OC3    (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_OC2    (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM4_OC3    (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM17_OC1   (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM20_OC2   (2)
  *         @arg @ref LL_ADC_INJ_TRIG_PLAY1_OUT14 (2)
  * @endif
  *
  *         (1) On this STM32 series, parameter available only on ADC instance: ADC1, ADC2\n
  *         (2) On this STM32 series, parameter available only on ADC instance: ADC3.
  * @note   On this STM32 series, setting trigger source to external trigger
  *         also set trigger polarity to rising edge
  *         (default setting for compatibility with some ADC on other
  *         STM32 series having this setting set by HW default value).
  *         In case of need to modify trigger edge, use
  *         function @ref LL_ADC_INJ_SetTriggerEdge().
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group injected.
  */
__STATIC_INLINE void LL_ADC_INJ_SetTriggerSource(ADC_TypeDef *p_adc, uint32_t trigger_source)
{
#if defined(ADC3)
  /* Manage trigger sources diversity across instances with look up table */
  if (((uint32_t)trigger_source) >= LL_ADC_INJ_TRIG_SRC_COUNT) /* LL_ADC_INJ_TRIG_SOFTWARE */
  {
    STM32_CLEAR_BIT(p_adc->JSQR, ADC_JSQR_JEXTEN | ADC_JSQR_JEXTSEL);
  }
  else
  {
    uint32_t trig_src_bitfield = LL_ADC_INJ_TRIG_SRC_LUT[trigger_source][LL_ADC_TRIG_SRC_LUT_INST_INDEX(p_adc)];

    STM32_MODIFY_REG(p_adc->JSQR,
                     ADC_JSQR_JEXTEN | ADC_JSQR_JEXTSEL, LL_ADC_INJ_TRIG_EDGE_DEFAULT    \
                     | ((trig_src_bitfield << ADC_JSQR_JEXTSEL_Pos) & ADC_JSQR_JEXTSEL));

    /* Manage case of trigger requiring additional configuration (option bit) */
    if ((trig_src_bitfield & LL_ADC_TRIG_OP_NB_MASK) != 0UL)
    {
      uint32_t option_bit_nb = ((trig_src_bitfield & LL_ADC_TRIG_OP_NB_MASK) >> LL_ADC_TRIG_OP_NB_POS)
                               + LL_ADC_TRIG_OP_NB_ADD_INJ;

      STM32_MODIFY_REG(p_adc->OR,
                       (1UL << option_bit_nb), (((trig_src_bitfield & LL_ADC_TRIG_OP_STATE_MASK) \
                                                 >> LL_ADC_TRIG_OP_STATE_POS) << option_bit_nb));
    }
  }
#else
  STM32_MODIFY_REG(p_adc->JSQR, ADC_JSQR_JEXTEN | ADC_JSQR_JEXTSEL, trigger_source);

  /* Manage case of trigger requiring additional configuration (option bit) */
  if ((trigger_source & LL_ADC_TRIG_OP_NB_MASK) != 0UL)
  {
    uint32_t option_bit_nb = ((trigger_source & LL_ADC_TRIG_OP_NB_MASK) >> LL_ADC_TRIG_OP_NB_POS);

    STM32_MODIFY_REG(p_adc->OR,
                     (1UL << option_bit_nb),
                     (((trigger_source & LL_ADC_TRIG_OP_STATE_MASK) >> LL_ADC_TRIG_OP_STATE_POS) << option_bit_nb));
  }
#endif /* ADC3 */
}

/**
  * @brief  Get ADC group injected conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         EXTI line).
  * @rmtoll
  *  JSQR     JEXTSEL        LL_ADC_INJ_GetTriggerSource\n
  *  JSQR     JEXTEN         LL_ADC_INJ_GetTriggerSource
  * @param  p_adc Pointer to ADC instance
  * @note   To determine whether group injected trigger source is
  *         internal (SW start) or external, without detail
  *         of which peripheral is selected as external trigger,
  *         (equivalent to
  *         "if(LL_ADC_INJ_GetTriggerSource(ADC1) == LL_ADC_INJ_TRIG_SOFTWARE)")
  *         use function @ref LL_ADC_INJ_IsTriggerSourceSWStart.
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_SOFTWARE
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_OC4
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_TIM2_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM7_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_TIM12_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM15_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM16_OC1
  *         @arg @ref LL_ADC_INJ_TRIG_TIM20_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM20_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_TIM27_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_LPTIM1_OC2
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG1
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG2
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG3
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG4
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG5
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG6
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG7
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG8
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG9
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG10
  *         @arg @ref LL_ADC_INJ_TRIG_EXTI15 (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM2_OC1    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_OC1    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_OC3    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_OC4    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_TRGO   (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM4_TRGO   (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_OC4    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_PLAY1_OUT13 (1)
  * @if ADC3
  *         @arg @ref LL_ADC_INJ_TRIG_EXTI3  (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_OC3    (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_OC2    (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM4_OC3    (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM17_OC1   (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM20_OC2   (2)
  *         @arg @ref LL_ADC_INJ_TRIG_PLAY1_OUT14 (2)
  * @endif
  *
  *         (1) On this STM32 series, parameter available only on ADC instance: ADC1, ADC2\n
  *         (2) On this STM32 series, parameter available only on ADC instance: ADC3.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTriggerSource(const ADC_TypeDef *p_adc)
{
#if defined(ADC3)
  /* Manage trigger sources diversity across instances with look up table */
  if (STM32_READ_BIT(p_adc->JSQR, ADC_JSQR_JEXTEN) == 0UL)
  {
    return LL_ADC_INJ_TRIG_SOFTWARE;
  }
  else
  {
    __IO uint32_t trig_src_reg_val = (STM32_READ_BIT(p_adc->JSQR, ADC_JSQR_JEXTSEL) >> ADC_JSQR_JEXTSEL_Pos);
    uint32_t instance_index_lut = LL_ADC_TRIG_SRC_LUT_INST_INDEX(p_adc);
    uint32_t index_lut;
    uint32_t trig_src_bitfield = 0U;

    /* Parse look up table until match of register value and ADC instance */
    for (index_lut = 0U; index_lut < LL_ADC_INJ_TRIG_SRC_COUNT; index_lut++)
    {
      trig_src_bitfield = LL_ADC_INJ_TRIG_SRC_LUT[index_lut][instance_index_lut];
      if (trig_src_reg_val == (trig_src_bitfield & (ADC_JSQR_JEXTSEL >> ADC_JSQR_JEXTSEL_Pos)))
      {
        break;
      }
    }

    /* Manage case of trigger requiring additional configuration (option bit) */
    if ((trig_src_bitfield & LL_ADC_TRIG_OP_NB_MASK) != 0UL)
    {
      uint32_t option_bit_nb = ((trig_src_bitfield & LL_ADC_TRIG_OP_NB_MASK) >> LL_ADC_TRIG_OP_NB_POS)
                               + LL_ADC_TRIG_OP_NB_ADD_INJ;
      trig_src_reg_val = (trig_src_bitfield & ~LL_ADC_TRIG_OP_STATE_MASK);
      if (STM32_READ_BIT(p_adc->OR, (1UL << option_bit_nb)) != 0UL)
      {
        trig_src_reg_val |= (1UL << LL_ADC_TRIG_OP_STATE_POS);
      }
      else
      {
        trig_src_reg_val &= ~(1UL << LL_ADC_TRIG_OP_STATE_POS);
      }

      /* Parse look up table with bitfield including option bit */
      for (index_lut = 0U; index_lut < LL_ADC_INJ_TRIG_SRC_COUNT; index_lut++)
      {
        trig_src_bitfield = LL_ADC_INJ_TRIG_SRC_LUT[index_lut][instance_index_lut];
        if (trig_src_reg_val == trig_src_bitfield)
        {
          break;
        }
      }
    }

    return index_lut;
  }
#else
  __IO uint32_t trigger_source = STM32_READ_BIT(p_adc->JSQR, ADC_JSQR_JEXTSEL | ADC_JSQR_JEXTEN);

  /* Value for shift of [0, 4, 8, 12] depending on value of bitfield corresponding to ADC_JSQR_JEXTEN [0, 1, 2, 3] */
  uint32_t shift_jexten = ((trigger_source & ADC_JSQR_JEXTEN) >> (ADC_JSQR_JEXTEN_Pos - 2UL));

  /* Set bitfield corresponding to ADC_CFGR1_EXTEN and ADC_CFGR1_EXTSEL to match with triggers literals definition */
  return ((trigger_source
           & (LL_ADC_INJ_TRIG_SOURCE_MASK >> shift_jexten) & ADC_JSQR_JEXTSEL)
          | ((LL_ADC_INJ_TRIG_EDGE_MASK >> shift_jexten) & ADC_JSQR_JEXTEN)
         );
#endif /* ADC3 */
}

/**
  * @brief  Get ADC group injected conversion trigger source internal (SW start)
            or external.
  * @rmtoll
  *  JSQR     JEXTEN         LL_ADC_INJ_IsTriggerSourceSWStart
  * @param  p_adc Pointer to ADC instance
  * @note   In case of group injected trigger source set to external trigger,
  *         to determine which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_INJ_GetTriggerSource.
  * @retval Value "0" if trigger source external trigger
  *         Value "1" if trigger source SW start.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsTriggerSourceSWStart(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->JSQR, ADC_JSQR_JEXTEN) == 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Set ADC group injected conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @rmtoll
  *  JSQR     JEXTEN         LL_ADC_INJ_SetTriggerEdge
  * @param  p_adc Pointer to ADC instance
  * @param  external_trigger_edge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_RISING_FALLING
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         ongoing on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_INJ_SetTriggerEdge(ADC_TypeDef *p_adc, uint32_t external_trigger_edge)
{
  STM32_MODIFY_REG(p_adc->JSQR, ADC_JSQR_JEXTEN, external_trigger_edge);
}

/**
  * @brief  Get ADC group injected conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @rmtoll
  *  JSQR     JEXTEN         LL_ADC_INJ_GetTriggerEdge
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_RISING_FALLING
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTriggerEdge(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->JSQR, ADC_JSQR_JEXTEN));
}

/**
  * @brief  Set ADC group injected sequencer length and scan direction.
  * @rmtoll
  *  JSQR     JLEN           LL_ADC_INJ_SetSequencerLength
  * @param  p_adc Pointer to ADC instance
  * @param  sequencer_nb_ranks This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  * @note   This function performs configuration of:
  *         - Sequence length: Number of ranks in the scan sequence.
  *         - Sequence direction: Unless specified in parameters, sequencer
  *           scan direction is forward (from rank 1 to rank n).
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         ongoing on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerLength(ADC_TypeDef *p_adc, uint32_t sequencer_nb_ranks)
{
  STM32_MODIFY_REG(p_adc->JSQR, ADC_JSQR_JLEN, sequencer_nb_ranks);
}

/**
  * @brief  Get ADC group injected sequencer length and scan direction.
  * @rmtoll
  *  JSQR     JLEN           LL_ADC_INJ_GetSequencerLength
  * @param  p_adc Pointer to ADC instance
  * @note   This function retrieves:
  *         - Sequence length: Number of ranks in the scan sequence.
  *         - Sequence direction: Unless specified in parameters, sequencer
  *           scan direction is forward (from rank 1 to rank n).
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerLength(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->JSQR, ADC_JSQR_JLEN));
}

/**
  * @brief  Set ADC group injected sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @rmtoll
  *  CFGR1    JDISCEN        LL_ADC_INJ_SetSequencerDiscont
  * @param  p_adc Pointer to ADC instance
  * @param  seq_discont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_1RANK
  * @note   It is not possible to enable both ADC group injected
  *         auto-injected mode and sequencer discontinuous mode.
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerDiscont(ADC_TypeDef *p_adc, uint32_t seq_discont)
{
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_JDISCEN, seq_discont);
}

/**
  * @brief  Get ADC group injected sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @rmtoll
  *  CFGR1    JDISCEN        LL_ADC_INJ_GetSequencerDiscont
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_1RANK
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerDiscont(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_JDISCEN));
}

/**
  * @brief  Set ADC group injected sequence: channel on the selected
  *         sequence rank.
  * @rmtoll
  *  JSQR     JSQ1           LL_ADC_INJ_SetSequencerRanks\n
  *  JSQR     JSQ2           LL_ADC_INJ_SetSequencerRanks\n
  *  JSQR     JSQ3           LL_ADC_INJ_SetSequencerRanks\n
  *  JSQR     JSQ4           LL_ADC_INJ_SetSequencerRanks
  * @param  p_adc Pointer to ADC instance
  * @param  rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   Depending on devices and packages, some channels can be not available.
  *         Refer to device datasheet for channels availability.
  * @note   On this STM32 series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         ongoing on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerRanks(ADC_TypeDef *p_adc, uint32_t rank, uint32_t channel)
{
  /* Set bits with content of parameter "Channel" with bits position          */
  /* in register depending on parameter "Rank".                               */
  /* Parameters "Rank" and "Channel" are used with masks because containing   */
  /* other bits reserved for other purpose.                                   */
  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);
  STM32_MODIFY_REG(p_adc->JSQR,
                   (LL_ADC_CH_NUMBER_MASK) << (rank & LL_ADC_INJ_RANK_ID_JSQR_MASK),
                   (channel_remapped & LL_ADC_CH_NUMBER_MASK) << (rank & LL_ADC_INJ_RANK_ID_JSQR_MASK));
}

/**
  * @brief  Get ADC group injected sequence: channel on the selected
  *         sequence rank.
  * @rmtoll
  *  JSQR     JSQ1           LL_ADC_INJ_GetSequencerRanks\n
  *  JSQR     JSQ2           LL_ADC_INJ_GetSequencerRanks\n
  *  JSQR     JSQ3           LL_ADC_INJ_GetSequencerRanks\n
  *  JSQR     JSQ4           LL_ADC_INJ_GetSequencerRanks
  * @param  p_adc Pointer to ADC instance
  * @param  rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @note   Depending on devices and packages, some channels can be not available.
  *         Refer to device datasheet for channels availability.
  * @note   Usage of the returned channel number:
  *         - To reinject this channel into another function LL_ADC_xxx:
  *           the returned channel number is only partly formatted on definition
  *           of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *           with parts of literals LL_ADC_CHANNEL_x or using
  *           helper macro @ref LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Then the selected literal LL_ADC_CHANNEL_x can be used
  *           as parameter for another function.
  *         - To get the channel number in decimal format:
  *           process the returned value with the helper macro
  *           @ref LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.\n
  *         (4) For ADC channel read back from ADC register,
  *             comparison with internal channel parameter to be done
  *             using helper macro @ref LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerRanks(const ADC_TypeDef *p_adc, uint32_t rank)
{
  uint32_t channel = ((STM32_READ_BIT(p_adc->JSQR,
                                      LL_ADC_CH_NUMBER_MASK << (rank & LL_ADC_INJ_RANK_ID_JSQR_MASK))
                       >> (rank & LL_ADC_INJ_RANK_ID_JSQR_MASK))
                     );

  return LL_ADC_REMAP_CHANNEL_GET(p_adc, channel);
}

/**
  * @brief  Set ADC group injected conversion trigger:
  *         independent or from ADC group regular.
  * @rmtoll
  *  CFGR1    JAUTO          LL_ADC_INJ_SetTrigAuto
  * @param  p_adc Pointer to ADC instance
  * @param  trig_auto This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_INDEPENDENT
  *         @arg @ref LL_ADC_INJ_TRIG_FROM_REGULAR
  * @note   This mode can be used to extend number of data registers
  *         updated after one ADC conversion trigger and with data
  *         permanently kept (not erased by successive conversions of scan of
  *         ADC sequencer ranks), up to 5 data registers:
  *         1 data register on ADC group regular, 4 data registers
  *         on ADC group injected.
  * @note   If ADC group injected injected trigger source is set to an
  *         external trigger, this feature must be must be set to
  *         independent trigger.
  *         ADC group injected automatic trigger is compliant only with
  *         group injected trigger source set to SW start, without any
  *         further action on  ADC group injected conversion start or stop:
  *         in this case, ADC group injected is controlled only
  *         from ADC group regular.
  * @note   It is not possible to enable both ADC group injected
  *         auto-injected mode and sequencer discontinuous mode.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_INJ_SetTrigAuto(ADC_TypeDef *p_adc, uint32_t trig_auto)
{
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_JAUTO, trig_auto);
}

/**
  * @brief  Get ADC group injected conversion trigger:
  *         independent or from ADC group regular.
  * @rmtoll
  *  CFGR1    JAUTO          LL_ADC_INJ_GetTrigAuto
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_INDEPENDENT
  *         @arg @ref LL_ADC_INJ_TRIG_FROM_REGULAR
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTrigAuto(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_JAUTO));
}

/**
  * @brief  Set ADC group injected contexts queue mode.
  * @rmtoll
  *  CFGR1    JQM            LL_ADC_INJ_SetQueueMode\n
  *  CFGR1    JQDIS          LL_ADC_INJ_SetQueueMode
  * @param  p_adc Pointer to ADC instance
  * @param  QueueMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_QUEUE_DISABLE
  *         @arg @ref LL_ADC_INJ_QUEUE_CTX_LAST_ACTIVE
  *         @arg @ref LL_ADC_INJ_QUEUE_CTX_END_EMPTY
  * @note   Injected queue allows to set multiple contexts in a FIFO buffer, each context containing injected trigger
  *         and sequence. Contexts can be added while group injected is active (sequence under conversion).
  * @note   The context sequence must be fully configured in one time (one write of register JSQR makes a check-in
  *         of a new context into the FIFO queue).
  *         Therefore functions to set separately injected trigger and sequencer channels cannot be used, specific
  *         function must be used. Refer to @ref LL_ADC_INJ_ConfigQueueContext().
  * @note   This parameter can be modified only when no conversion is ongoing
  *         on either groups regular or injected.
  * @note   A modification of the context mode (bit JQDIS) causes the contexts
  *         queue to be flushed and the register JSQR is cleared.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_INJ_SetQueueMode(ADC_TypeDef *p_adc, uint32_t QueueMode)
{
  STM32_MODIFY_REG(p_adc->CFGR1, ADC_CFGR1_JQM | ADC_CFGR1_JQDIS, QueueMode);
}

/**
  * @brief  Get ADC group injected contexts queue mode.
  * @rmtoll
  *  CFGR1    JQM            LL_ADC_INJ_GetQueueMode\n
  *  CFGR1    JQDIS          LL_ADC_INJ_GetQueueMode
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_QUEUE_DISABLE
  *         @arg @ref LL_ADC_INJ_QUEUE_CTX_LAST_ACTIVE
  *         @arg @ref LL_ADC_INJ_QUEUE_CTX_END_EMPTY
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetQueueMode(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR1, ADC_CFGR1_JQM | ADC_CFGR1_JQDIS));
}

/**
  * @brief  Set one context on ADC group injected that will be added in contexts queue.
  * @rmtoll
  *  JSQR     JEXTSEL        LL_ADC_INJ_ConfigQueueContext\n
  *  JSQR     JEXTEN         LL_ADC_INJ_ConfigQueueContext\n
  *  JSQR     JL             LL_ADC_INJ_ConfigQueueContext\n
  *  JSQR     JSQ1           LL_ADC_INJ_ConfigQueueContext\n
  *  JSQR     JSQ2           LL_ADC_INJ_ConfigQueueContext\n
  *  JSQR     JSQ3           LL_ADC_INJ_ConfigQueueContext\n
  *  JSQR     JSQ4           LL_ADC_INJ_ConfigQueueContext
  * @param  p_adc Pointer to ADC instance
  * @param  trigger_source This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_SOFTWARE
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_OC4
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_TIM2_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM7_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_TIM12_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM15_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM16_OC1
  *         @arg @ref LL_ADC_INJ_TRIG_TIM20_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_TIM20_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_TIM27_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_LPTIM1_OC2
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG1
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG2
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG3
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG4
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG5
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG6
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG7
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG8
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG9
  *         @arg @ref LL_ADC_INJ_TRIG_HRTIM1_TRG10
  *         @arg @ref LL_ADC_INJ_TRIG_EXTI15 (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM2_OC1    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_OC1    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_OC3    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_OC4    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM3_TRGO   (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM4_TRGO   (1)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_OC4    (1)
  *         @arg @ref LL_ADC_INJ_TRIG_PLAY1_OUT13 (1)
  * @if ADC3
  *         @arg @ref LL_ADC_INJ_TRIG_EXTI3  (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM1_OC3    (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM8_OC2    (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM4_OC3    (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM17_OC1   (2)
  *         @arg @ref LL_ADC_INJ_TRIG_TIM20_OC2   (2)
  *         @arg @ref LL_ADC_INJ_TRIG_PLAY1_OUT14 (2)
  * @endif
  *
  *         (1) On this STM32 series, parameter available only on ADC instance: ADC1, ADC2\n
  *         (2) On this STM32 series, parameter available only on ADC instance: ADC3.
  * @param  trigger_edge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_RISING_FALLING
  *
  *         Note: This parameter is discarded in case of SW start:
  *               parameter "trigger_source" set to "LL_ADC_INJ_TRIG_SOFTWARE".
  * @param  sequencer_length This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  * @param  channel_rank_1 This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.\n
  *         (4) For ADC channel read back from ADC register,
  *             comparison with internal channel parameter to be done
  *             using helper macro @ref LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  * @param  channel_rank_2 This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.\n
  *         (4) For ADC channel read back from ADC register,
  *             comparison with internal channel parameter to be done
  *             using helper macro @ref LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  * @param  channel_rank_3 This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.\n
  *         (4) For ADC channel read back from ADC register,
  *             comparison with internal channel parameter to be done
  *             using helper macro @ref LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  * @param  channel_rank_4 This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   Conversion trigger source can be only from a peripheral (not SW start)
  * @note   Read back of contexts queue: only the active context can be read.
  *         Therefore, in case group injected is active (sequence under conversion) and conversion trigger timing
  *         not under control, it is not possible to ensure which context is read vs context change from queue.
  *         If user application manages to control timing, parameters of this function can be read using functions:
  *         @arg @ref LL_ADC_INJ_GetTriggerSource()
  *         @arg @ref LL_ADC_INJ_GetTriggerEdge()
  *         @arg @ref LL_ADC_INJ_GetSequencerRanks()
  * @note   On this STM32 series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled, group injected conversions armed (JADSTART = 1)
  *         (ready to process conversion trigger event)
  */
__STATIC_INLINE void LL_ADC_INJ_ConfigQueueContext(ADC_TypeDef *p_adc,
                                                   uint32_t trigger_source,
                                                   uint32_t trigger_edge,
                                                   uint32_t sequencer_length,
                                                   uint32_t channel_rank_1,
                                                   uint32_t channel_rank_2,
                                                   uint32_t channel_rank_3,
                                                   uint32_t channel_rank_4)
{
  uint32_t channel_rank_1_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel_rank_1);
  uint32_t channel_rank_2_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel_rank_2);
  uint32_t channel_rank_3_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel_rank_3);
  uint32_t channel_rank_4_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel_rank_4);

#if defined(ADC3)
  uint32_t trig_src_tmp;
  /* Manage trigger sources diversity across instances with look up table */
  if (((uint32_t)trigger_source) >= LL_ADC_INJ_TRIG_SRC_COUNT) /* LL_ADC_INJ_TRIG_SOFTWARE */
  {
    trig_src_tmp = 0UL;
  }
  else
  {
    uint32_t trig_src_bitfield = LL_ADC_INJ_TRIG_SRC_LUT[trigger_source][LL_ADC_TRIG_SRC_LUT_INST_INDEX(p_adc)];
    trig_src_tmp = ((trig_src_bitfield << ADC_JSQR_JEXTSEL_Pos) & ADC_JSQR_JEXTSEL);

    /* Manage case of trigger requiring additional configuration (option bit) */
    if ((trig_src_bitfield & LL_ADC_TRIG_OP_NB_MASK) != 0UL)
    {
      uint32_t option_bit_nb = ((trig_src_bitfield & LL_ADC_TRIG_OP_NB_MASK) >> LL_ADC_TRIG_OP_NB_POS)
                               + LL_ADC_TRIG_OP_NB_ADD_INJ;

      STM32_MODIFY_REG(p_adc->OR,
                       (1UL << option_bit_nb),
                       (((trig_src_bitfield & LL_ADC_TRIG_OP_STATE_MASK) >> LL_ADC_TRIG_OP_STATE_POS) \
                        << option_bit_nb));
    }
  }

  uint32_t context = (trig_src_tmp
                      | trigger_edge
                      | ((channel_rank_4_remapped & LL_ADC_CH_NUMBER_MASK)
                         << (LL_ADC_INJ_RANK_4 & LL_ADC_INJ_RANK_ID_JSQR_MASK))
                      | ((channel_rank_3_remapped & LL_ADC_CH_NUMBER_MASK)
                         << (LL_ADC_INJ_RANK_3 & LL_ADC_INJ_RANK_ID_JSQR_MASK))
                      | ((channel_rank_2_remapped & LL_ADC_CH_NUMBER_MASK)
                         << (LL_ADC_INJ_RANK_2 & LL_ADC_INJ_RANK_ID_JSQR_MASK))
                      | ((channel_rank_1_remapped & LL_ADC_CH_NUMBER_MASK)
                         << (LL_ADC_INJ_RANK_1 & LL_ADC_INJ_RANK_ID_JSQR_MASK))
                      | sequencer_length);
#else
  uint32_t context = ((trigger_source & ADC_JSQR_JEXTSEL)
                      | trigger_edge
                      | ((channel_rank_4_remapped & LL_ADC_CH_NUMBER_MASK)
                         << (LL_ADC_INJ_RANK_4 & LL_ADC_INJ_RANK_ID_JSQR_MASK))
                      | ((channel_rank_3_remapped & LL_ADC_CH_NUMBER_MASK)
                         << (LL_ADC_INJ_RANK_3 & LL_ADC_INJ_RANK_ID_JSQR_MASK))
                      | ((channel_rank_2_remapped & LL_ADC_CH_NUMBER_MASK)
                         << (LL_ADC_INJ_RANK_2 & LL_ADC_INJ_RANK_ID_JSQR_MASK))
                      | ((channel_rank_1_remapped & LL_ADC_CH_NUMBER_MASK)
                         << (LL_ADC_INJ_RANK_1 & LL_ADC_INJ_RANK_ID_JSQR_MASK))
                      | sequencer_length);
#endif /* ADC3 */

  /* Set context in one register JSQR write access */
  STM32_WRITE_REG(p_adc->JSQR, context);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_Channels Configuration of ADC hierarchical scope: channels
  * @{
  */

/**
  * @brief  Set sampling time of the selected ADC channel (unit: ADC clock cycles).
  * @rmtoll
  *  SMPR1    SMP0           LL_ADC_SetChannelSamplingTime\n
  *  SMPR1    SMP1           LL_ADC_SetChannelSamplingTime\n
  *  SMPR1    SMP2           LL_ADC_SetChannelSamplingTime\n
  *  SMPR1    SMP3           LL_ADC_SetChannelSamplingTime\n
  *  SMPR1    SMP4           LL_ADC_SetChannelSamplingTime\n
  *  SMPR1    SMP5           LL_ADC_SetChannelSamplingTime\n
  *  SMPR1    SMP6           LL_ADC_SetChannelSamplingTime\n
  *  SMPR1    SMP7           LL_ADC_SetChannelSamplingTime\n
  *  SMPR1    SMP8           LL_ADC_SetChannelSamplingTime\n
  *  SMPR1    SMP9           LL_ADC_SetChannelSamplingTime\n
  *  SMPR2    SMP10          LL_ADC_SetChannelSamplingTime\n
  *  SMPR2    SMP11          LL_ADC_SetChannelSamplingTime\n
  *  SMPR2    SMP12          LL_ADC_SetChannelSamplingTime\n
  *  SMPR2    SMP13          LL_ADC_SetChannelSamplingTime\n
  *  SMPR2    SMP14          LL_ADC_SetChannelSamplingTime\n
  *  SMPR2    SMP15          LL_ADC_SetChannelSamplingTime\n
  *  SMPR2    SMP16          LL_ADC_SetChannelSamplingTime\n
  *  SMPR2    SMP17          LL_ADC_SetChannelSamplingTime\n
  *  SMPR2    SMP18          LL_ADC_SetChannelSamplingTime
  * @param  p_adc Pointer to ADC instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.\n
  *         (4) For ADC channel read back from ADC register,
  *             comparison with internal channel parameter to be done
  *             using helper macro @ref LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  * @param  sampling_time This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLINGTIME_2CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_4CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_7CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_12CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_24CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_47CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_256CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_848CYCLES_5
  * @note   On this device, sampling time is on channel scope: independently
  *         of channel mapped on ADC group regular or injected.
  * @note   In case of internal channel (VrefInt, TempSensor, ...) to be
  *         converted:
  *         sampling time constraints must be respected (sampling time can be
  *         adjusted in function of ADC clock frequency and sampling time
  *         setting).
  *         Refer to device datasheet for timings values (parameters TS_vrefint,
  *         TS_temp, ...).
  * @note   Conversion time is the addition of sampling time and processing time.
  *         On this STM32 series, ADC processing time is:
  *         - 13.5 ADC clock cycles at ADC resolution 12 bits
  *         - 11.5 ADC clock cycles at ADC resolution 10 bits
  *         - 9.5 ADC clock cycles at ADC resolution 8 bits
  *         - 7.5 ADC clock cycles at ADC resolution 6 bits
  * @note   In case of ADC conversion of internal channel (VrefInt,
  *         temperature sensor, ...), a sampling time minimum value
  *         is required.
  *         Refer to device datasheet.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetChannelSamplingTime(ADC_TypeDef *p_adc, uint32_t channel, uint32_t sampling_time)
{
  /* Set bits with content of parameter "sampling_time" with bits position
     in register and register position depending on parameter "Channel".
     Parameter "channel" is used with masks because containing
     other bits reserved for other purpose. */
  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);
  uint32_t ichannel = LL_ADC_CHANNEL_LUT_INDEX(channel_remapped);
  __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->SMPR1,
                                              ((LL_ADC_CHANNEL_LUT[ichannel]
                                                & LL_ADC_CH_SMPRX_REGOFFSET_MASK) >> LL_ADC_CH_SMPRX_REGOFFSET_POS));
  STM32_MODIFY_REG(*preg,
                   ADC_SMPR1_SMP0 << ((LL_ADC_CHANNEL_LUT[ichannel] & LL_ADC_CH_SMPX_BITOFFSET_MASK)
                                      >> LL_ADC_CH_SMPX_BITOFFSET_POS),
                   sampling_time   << ((LL_ADC_CHANNEL_LUT[ichannel] & LL_ADC_CH_SMPX_BITOFFSET_MASK)
                                       >> LL_ADC_CH_SMPX_BITOFFSET_POS));
}

/**
  * @brief  Get sampling time of the selected ADC channel (unit: ADC clock cycles).
  * @rmtoll
  *  SMPR1    SMP0           LL_ADC_GetChannelSamplingTime\n
  *  SMPR1    SMP1           LL_ADC_GetChannelSamplingTime\n
  *  SMPR1    SMP2           LL_ADC_GetChannelSamplingTime\n
  *  SMPR1    SMP3           LL_ADC_GetChannelSamplingTime\n
  *  SMPR1    SMP4           LL_ADC_GetChannelSamplingTime\n
  *  SMPR1    SMP5           LL_ADC_GetChannelSamplingTime\n
  *  SMPR1    SMP6           LL_ADC_GetChannelSamplingTime\n
  *  SMPR1    SMP7           LL_ADC_GetChannelSamplingTime\n
  *  SMPR1    SMP8           LL_ADC_GetChannelSamplingTime\n
  *  SMPR1    SMP9           LL_ADC_GetChannelSamplingTime\n
  *  SMPR2    SMP10          LL_ADC_GetChannelSamplingTime\n
  *  SMPR2    SMP11          LL_ADC_GetChannelSamplingTime\n
  *  SMPR2    SMP12          LL_ADC_GetChannelSamplingTime\n
  *  SMPR2    SMP13          LL_ADC_GetChannelSamplingTime\n
  *  SMPR2    SMP14          LL_ADC_GetChannelSamplingTime\n
  *  SMPR2    SMP15          LL_ADC_GetChannelSamplingTime\n
  *  SMPR2    SMP16          LL_ADC_GetChannelSamplingTime\n
  *  SMPR2    SMP17          LL_ADC_GetChannelSamplingTime\n
  *  SMPR2    SMP18          LL_ADC_GetChannelSamplingTime
  * @param  p_adc Pointer to ADC instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.\n
  *         (4) For ADC channel read back from ADC register,
  *             comparison with internal channel parameter to be done
  *             using helper macro @ref LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLINGTIME_2CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_4CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_7CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_12CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_24CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_47CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_256CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_848CYCLES_5
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSamplingTime(const ADC_TypeDef *p_adc, uint32_t channel)
{
  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);
  uint32_t ichannel = LL_ADC_CHANNEL_LUT_INDEX(channel_remapped);
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->SMPR1,
                                                    ((LL_ADC_CHANNEL_LUT[ichannel] & LL_ADC_CH_SMPRX_REGOFFSET_MASK)
                                                     >> LL_ADC_CH_SMPRX_REGOFFSET_POS));
  return (uint32_t)(STM32_READ_BIT(*preg,
                                   ADC_SMPR1_SMP0
                                   << ((LL_ADC_CHANNEL_LUT[ichannel]
                                        & LL_ADC_CH_SMPX_BITOFFSET_MASK) >> LL_ADC_CH_SMPX_BITOFFSET_POS))
                    >> ((LL_ADC_CHANNEL_LUT[ichannel] & LL_ADC_CH_SMPX_BITOFFSET_MASK)
                        >> LL_ADC_CH_SMPX_BITOFFSET_POS)
                   );
}

/**
  * @brief  Set mode single-ended or differential (availability depending on devices) on input of the selected
  *         ADC channel.
  * @rmtoll
  *  DIFSEL   DIFSEL         LL_ADC_SetChannelSingleDiff
  * @param  p_adc Pointer to ADC instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  * @param  input_mode This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_IN_SINGLE_ENDED
  *         @arg @ref LL_ADC_IN_DIFFERENTIAL
  * @note   In differential mode: to compute voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value)
  *         use helper macro @ref LL_ADC_CALC_DIFF_DATA_TO_VOLTAGE.
  * @note   In differential mode: Differential measurement is carried out
  *         between the selected channel (positive input) and
  *         another channel (negative input). Only selected channel has to be
  *         configured, the other channel is configured automatically
  *         and is not usable separately.
  * @note   Differential mode is not available on all channels.
  *         For compliant channels list, refer to reference manual.
  * @note   For ADC channels configured in differential mode, both inputs
  *         must be biased at (Vref+)/2 +/-200mV.
  *         (Vref+ is the analog voltage reference)
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  */
__STATIC_INLINE void LL_ADC_SetChannelSingleDiff(ADC_TypeDef *p_adc, uint32_t channel, uint32_t input_mode)
{
  /* Bits of channels in single or differential mode are set only for         */
  /* differential mode (for single mode, mask of bits allowed to be set is    */
  /* shifted out of range of bits of channels in single or differential mode. */
  uint32_t ichannel = LL_ADC_CHANNEL_LUT_INDEX(channel);
  STM32_MODIFY_REG(p_adc->DIFSEL,
                   LL_ADC_CHANNEL_LUT[ichannel] & LL_ADC_SGLDIFF_CH_MASK,
                   (LL_ADC_CHANNEL_LUT[ichannel] & LL_ADC_SGLDIFF_CH_MASK)
                   & (ADC_DIFSEL_DIFSEL >> (input_mode & LL_ADC_SGLDIFF_CH_SHIFT_MASK)));
}

/**
  * @brief  Get mode single-ended or differential input of the selected
  *         ADC channel.
  * @rmtoll
  *  DIFSEL   DIFSEL         LL_ADC_GetChannelSingleDiff
  * @param  p_adc Pointer to ADC instance
  * @param  channel This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  * @note   In differential mode: Differential measurement is carried out
  *         between the selected channel (positive input) and
  *         another channel (negative input). Only selected channel has to be
  *         configured, the other channel is configured automatically
  *         and is not usable separately.
  * @note   Differential mode is not available on all channels.
  *         For compliant channels list, refer to reference manual.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_IN_SINGLE_ENDED
  *         @arg @ref LL_ADC_IN_DIFFERENTIAL
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSingleDiff(const ADC_TypeDef *p_adc, uint32_t channel)
{
  uint32_t ichannel = LL_ADC_CHANNEL_LUT_INDEX(channel);
  return ((STM32_READ_BIT(p_adc->DIFSEL, (LL_ADC_CHANNEL_LUT[ichannel] & LL_ADC_SGLDIFF_CH_MASK)) == 0UL)
          ? LL_ADC_IN_SINGLE_ENDED : LL_ADC_IN_DIFFERENTIAL);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_AnalogWatchdog Configuration of ADC transversal scope: analog watchdog
  * @{
  */

/**
  * @brief  Set ADC analog watchdog monitored channels:
  *         ADC group (regular and-or injected) and channel (single, multiple or all channels).
  * @rmtoll
  *  CFGR1    AWD1CH         LL_ADC_SetAnalogWDScope\n
  *  CFGR1    AWD1SGL        LL_ADC_SetAnalogWDScope\n
  *  CFGR1    AWD1EN         LL_ADC_SetAnalogWDScope\n
  *  CFGR1    JAWD1EN        LL_ADC_SetAnalogWDScope\n
  *  AWD2CR   AWDCH          LL_ADC_SetAnalogWDScope\n
  *  AWD3CR   AWDCH          LL_ADC_SetAnalogWDScope
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @param  group This parameter can be one of the following values:
  *         @arg @ref LL_ADC_GROUP_REGULAR
  *         @arg @ref LL_ADC_GROUP_INJECTED
  *         @arg @ref LL_ADC_GROUP_REGULAR_INJECTED
  *         @arg @ref LL_ADC_GROUP_NONE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   Specific configurations:
  *         - to monitor all channels, use following parameters values:
  *             LL_ADC_SetAnalogWDScope(..., ..., group regular and-or injected, LL_ADC_CHANNEL_ALL)
  *         - to disable ADC analog watchdog, use following parameters values:
  *             LL_ADC_SetAnalogWDScope(..., ..., LL_ADC_GROUP_NONE, LL_ADC_CHANNEL_NONE)
  *           (parameters LL_ADC_GROUP_NONE and LL_ADC_CHANNEL_NONE must be used together, not separately)
  *         - specific case (only on analog watchdog instances: AWD2, AWD3), to monitor multiple channels
  *           use following parameters values (channels list with logical or):
  *             LL_ADC_SetAnalogWDScope(..., ..., group regular and-or injected, LL_ADC_CHANNEL_x | LL_ADC_CHANNEL_y)
  * @note   The ADC analog watchdog configuration parameters can be read back using
  *         functions @ref LL_ADC_GetAnalogWDScopeGroup and @ref LL_ADC_GetAnalogWDScopeChannel.
  * @note   Once monitored channels are selected, analog watchdog is enabled.
  * @note   On this STM32 series, there are 2 kinds of analog watchdog
  *         instance:
  *         - AWD standard (instance AWD1):
  *           - channels monitored: can monitor 1 channel or all channels.
  *           - groups monitored: ADC groups regular and-or injected.
  *         - AWD flexible (instances AWD2, AWD3):
  *           - channels monitored: flexible on channels monitored, selection is
  *             channel wise, from from 1 to all channels.
  *             Specificity of this analog watchdog: Multiple channels can
  *             be selected. For example:
  *             (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *           - groups monitored: not selection possible (monitoring on both
  *             groups regular and injected).
  *             Channels selected are monitored on groups regular and injected:
  *             LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *             LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDScope(ADC_TypeDef *p_adc, uint32_t awd_y, uint32_t group, uint32_t channel)
{
  /* Set bits with content of parameter "group" and "channel" with bits position in register and register position
     depending on parameter "awd_y". Parameters are used with masks because containing other bits
     reserved for other purpose. */

  __IO uint32_t *preg;
  uint32_t awd_group_channel_monitored;
  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);
  uint32_t ichannel = LL_ADC_CHANNEL_LUT_INDEX(channel_remapped);

  if (awd_y == LL_ADC_AWD_1)
  {
    /* Set pointer to register of selected analog watchdog */
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->CFGR1, 0UL);

    /* Compute channel monitored as number */
    awd_group_channel_monitored = ((group << ADC_CFGR1_AWD1EN_Pos)
                                   | (LL_ADC_CHANNEL_TO_DECIMAL_NB(channel_remapped) << ADC_CFGR1_AWD1CH_Pos));

    /* Case unitary channel selected (parameter "channel" values except LL_ADC_CHANNEL_ALL and LL_ADC_CHANNEL_NONE) */
    if (LL_ADC_CHANNEL_TO_DECIMAL_NB(channel_remapped) < ADC_CH_NONE_NUMBER)
    {
      awd_group_channel_monitored |= ADC_CFGR1_AWD1SGL;
    }
  }
  else
  {
    /* Set pointer to register of selected analog watchdog */
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD2CR,
                                 (((awd_y & LL_ADC_AWD_CRX_REGOFFSET_MASK)) >> (LL_ADC_AWD_CRX_REGOFFSET_POS)) - 1UL);

    /* Compute channel monitored as bitfield */
    awd_group_channel_monitored = (LL_ADC_CHANNEL_LUT[ichannel] & LL_ADC_CHANNEL_ID_BITFIELD_MASK);
  }

  STM32_MODIFY_REG(*preg, (awd_y & LL_ADC_AWD_CR_ALL_CHANNEL_MASK), awd_group_channel_monitored);
}

/**
  * @brief  Add ADC analog watchdog monitored channels: Channel (single, multiple or all channels).
  * @rmtoll
  *  AWD2CR   AWDCH          LL_ADC_SetAnalogWDChannelAdd\n
  *  AWD3CR   AWDCH          LL_ADC_SetAnalogWDChannelAdd
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   The ADC analog watchdog configuration parameters can be read back using
  *         functions @ref LL_ADC_GetAnalogWDScopeGroup, @ref LL_ADC_GetAnalogWDScopeChannel
  *         and @ref LL_ADC_IsAnalogWDChannelMonitored
  * @note   This function is Specific to AWD2, AWD3.
  *         AWD1 does not support multichannel selection.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDChannelAdd(ADC_TypeDef *p_adc, uint32_t awd_y, uint32_t channel)
{
  /* Set bits with content of parameters "group" and "channel" with bits       */
  /* position in register and register position depending on parameter "awd_y".*/
  /* Parameters are used with masks because containing other bits reserved     */
  /* for other purpose.                                                        */

  __IO uint32_t *preg;
  uint32_t awd_group_channel_monitored;
  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);
  uint32_t ichannel = LL_ADC_CHANNEL_LUT_INDEX(channel_remapped);

  if (awd_y == LL_ADC_AWD_1)
  {
    /* Nothing to do : AWD1 not supported */
  }
  else
  {
    /* Set pointer to register of selected analog watchdog */
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD2CR,
                                 (((awd_y & LL_ADC_AWD_CRX_REGOFFSET_MASK)) >> (LL_ADC_AWD_CRX_REGOFFSET_POS)) - 1UL);

    if (channel_remapped == LL_ADC_CHANNEL_ALL)
    {
      awd_group_channel_monitored = LL_ADC_CHANNEL_ALL_BITFIELD;
    }
    else if (channel_remapped == LL_ADC_CHANNEL_NONE)
    {
      awd_group_channel_monitored = 0;
    }
    else
    {
      /* Compute channel monitored as bitfield */
      awd_group_channel_monitored = (LL_ADC_CHANNEL_LUT[ichannel] & LL_ADC_CHANNEL_ID_BITFIELD_MASK);
    }

    STM32_SET_BIT(*preg, awd_group_channel_monitored);
  }
}

/**
  * @brief  Remove ADC analog watchdog monitored channels: Channel (single, multiple or all channels).
  * @rmtoll
  *  AWD2CR   AWDCH          LL_ADC_SetAnalogWDChannelRem\n
  *  AWD3CR   AWDCH          LL_ADC_SetAnalogWDChannelRem
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   The ADC analog watchdog configuration parameters can be read back using
  *         functions @ref LL_ADC_GetAnalogWDScopeGroup, @ref LL_ADC_GetAnalogWDScopeChannel
  *         and @ref LL_ADC_IsAnalogWDChannelMonitored
  * @note   This function is Specific to AWD2, AWD3.
  *         AWD1 does not support multichannel selection.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDChannelRem(ADC_TypeDef *p_adc, uint32_t awd_y, uint32_t channel)
{
  /* Set bits with content of parameters "group" and "channel" with bits      */
  /* position in register and register position depending on parameter "awd_y".*/
  /* Parameters are used with masks because containing other bits reserved    */
  /* for other purpose.                                                       */

  __IO uint32_t *preg;
  uint32_t awd_group_channel_monitored;
  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);
  uint32_t ichannel = LL_ADC_CHANNEL_LUT_INDEX(channel_remapped);

  if (awd_y == LL_ADC_AWD_1)
  {
    /* Nothing to do : AWD1 not supported */
  }
  else
  {
    /* Set pointer to register of selected analog watchdog */
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD2CR,
                                 (((awd_y & LL_ADC_AWD_CRX_REGOFFSET_MASK)) >> (LL_ADC_AWD_CRX_REGOFFSET_POS)) - 1UL);

    if (channel_remapped == LL_ADC_CHANNEL_ALL)
    {
      awd_group_channel_monitored = LL_ADC_CHANNEL_ALL_BITFIELD;
    }
    else if (channel_remapped == LL_ADC_CHANNEL_NONE)
    {
      awd_group_channel_monitored = 0;
    }
    else
    {
      /* Compute channel monitored as bitfield */
      awd_group_channel_monitored = (LL_ADC_CHANNEL_LUT[ichannel] & LL_ADC_CHANNEL_ID_BITFIELD_MASK);
    }

    STM32_CLEAR_BIT(*preg, awd_group_channel_monitored);
  }
}

/**
  * @brief  Get ADC analog watchdog monitored channels:
  *         ADC group (regular and-or injected).
  * @rmtoll
  *  CFGR1    AWD1CH         LL_ADC_GetAnalogWDScopeGroup\n
  *  CFGR1    AWD1SGL        LL_ADC_GetAnalogWDScopeGroup\n
  *  CFGR1    AWD1EN         LL_ADC_GetAnalogWDScopeGroup\n
  *  CFGR1    JAWD1EN        LL_ADC_GetAnalogWDScopeGroup\n
  *  AWD2CR   AWDCH          LL_ADC_GetAnalogWDScopeGroup\n
  *  AWD3CR   AWDCH          LL_ADC_GetAnalogWDScopeGroup
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @note   Configuration done by @ref LL_ADC_SetAnalogWDScope(), refer to description of this function for more details
  *         on parameters.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_GROUP_REGULAR
  *         @arg @ref LL_ADC_GROUP_INJECTED
  *         @arg @ref LL_ADC_GROUP_REGULAR_INJECTED
  *         @arg @ref LL_ADC_GROUP_NONE
  */
__STATIC_INLINE uint32_t LL_ADC_GetAnalogWDScopeGroup(ADC_TypeDef *p_adc, uint32_t awd_y)
{
  const __IO uint32_t *preg;
  uint32_t awd_group_monitored;

  if (awd_y == LL_ADC_AWD_1)
  {
    /* Set pointer to register of selected analog watchdog */
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->CFGR1, 0UL);
  }
  else
  {
    /* Set pointer to register of selected analog watchdog */
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD2CR,
                                 (((awd_y & LL_ADC_AWD_CRX_REGOFFSET_MASK)) >> (LL_ADC_AWD_CRX_REGOFFSET_POS)) - 1UL);
  }

  awd_group_monitored = STM32_READ_BIT(*preg, awd_y) & awd_y;

  if (awd_y == LL_ADC_AWD_1)
  {
    awd_group_monitored = ((awd_group_monitored & (ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN)) >> ADC_CFGR1_AWD1EN_Pos);
  }
  else
  {
    if (awd_group_monitored != LL_ADC_GROUP_NONE)
    {
      awd_group_monitored = LL_ADC_GROUP_REGULAR_INJECTED;
    }
  }

  return awd_group_monitored;
}

/**
  * @brief  Get ADC analog watchdog monitored channels:
  *         ADC channel (single, multiple or all channels).
  * @rmtoll
  *  CFGR1    AWD1CH         LL_ADC_GetAnalogWDScopeChannel\n
  *  CFGR1    AWD1SGL        LL_ADC_GetAnalogWDScopeChannel\n
  *  CFGR1    AWD1EN         LL_ADC_GetAnalogWDScopeChannel\n
  *  CFGR1    JAWD1EN        LL_ADC_GetAnalogWDScopeChannel\n
  *  AWD2CR   AWDCH          LL_ADC_GetAnalogWDScopeChannel\n
  *  AWD3CR   AWDCH          LL_ADC_GetAnalogWDScopeChannel
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @note   Configuration done by @ref LL_ADC_SetAnalogWDScope(), refer to description of this function for more details
  *         on parameters.
  * @note   This function does not support specific case of multiple channels monitored (only on
  *         analog watchdog instances: AWD2, AWD3).
  *         In case of multiple channels monitored, return value of this function is not relevant,
  *         use @ref LL_ADC_IsAnalogWDChannelMonitored() instead.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.\n
  *         (4) For ADC channel read back from ADC register,
  *             comparison with internal channel parameter to be done
  *             using helper macro @ref LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
__STATIC_INLINE uint32_t LL_ADC_GetAnalogWDScopeChannel(const ADC_TypeDef *p_adc, uint32_t awd_y)
{
  const __IO uint32_t *preg;
  uint32_t awd_channel_monitored;

  if (awd_y == LL_ADC_AWD_1)
  {
    /* Set pointer to register of selected analog watchdog */
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->CFGR1, 0UL);
  }
  else
  {
    /* Set pointer to register of selected analog watchdog */
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD2CR,
                                 (((awd_y & LL_ADC_AWD_CRX_REGOFFSET_MASK)) >> (LL_ADC_AWD_CRX_REGOFFSET_POS)) - 1UL);
  }

  awd_channel_monitored = STM32_READ_BIT(*preg, awd_y) & awd_y;

  if (awd_y == LL_ADC_AWD_1)
  {
    if ((awd_channel_monitored & (ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN)) == 0UL)
    {
      /* Case analog watchdog disabled (no channel) */
      awd_channel_monitored = LL_ADC_CHANNEL_NONE;
    }
    else if ((awd_channel_monitored & ADC_CFGR1_AWD1SGL) == 0UL)
    {
      /* Case all channels */
      awd_channel_monitored = LL_ADC_CHANNEL_ALL;
    }
    else
    {
      /* Case unitary channel */
      awd_channel_monitored = (awd_channel_monitored & ADC_CFGR1_AWD1CH) >> ADC_CFGR1_AWD1CH_Pos;
    }
  }
  else
  {
    if ((awd_channel_monitored & ADC_AWD2CR_AWDCH) == 0UL)
    {
      awd_channel_monitored = LL_ADC_CHANNEL_NONE;
    }
    else if ((awd_channel_monitored & ADC_AWD2CR_AWDCH) == ADC_AWD2CR_AWDCH)
    {
      /* Case all channels */
      awd_channel_monitored = LL_ADC_CHANNEL_ALL;
    }
    else
    {
      /* In case of multiple channel return value of first monitored channel */
      awd_channel_monitored = STM32_POSITION_VAL(awd_channel_monitored);
    }
  }

  return LL_ADC_REMAP_CHANNEL_GET(p_adc, awd_channel_monitored);
}

/**
  * @brief  Check if ADC analog watchdog is monitoring a channel.
  * @rmtoll
  *  CFGR1    AWD1CH         LL_ADC_IsAnalogWDChannelMonitored\n
  *  CFGR1    AWD1SGL        LL_ADC_IsAnalogWDChannelMonitored\n
  *  CFGR1    AWD1EN         LL_ADC_IsAnalogWDChannelMonitored\n
  *  CFGR1    JAWD1EN        LL_ADC_IsAnalogWDChannelMonitored\n
  *  AWD2CR   AWDCH          LL_ADC_IsAnalogWDChannelMonitored\n
  *  AWD3CR   AWDCH          LL_ADC_IsAnalogWDChannelMonitored
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   Configuration done by @ref LL_ADC_SetAnalogWDScope(), refer to description of this function for more details
  *         on parameters.
  * @note   On this STM32 series, AWD features detection of which channel has triggered the out of window flag.
  *         Refer to @ref LL_ADC_IsAnalogWDChannelTriggered().
  * @retval 0: channel is not monitored by analog watchdog, 1: channel is monitored by analog watchdog
  */
__STATIC_INLINE uint32_t LL_ADC_IsAnalogWDChannelMonitored(ADC_TypeDef *p_adc, uint32_t awd_y, uint32_t channel)
{
  const __IO uint32_t *preg;
  uint32_t awd_channel_monitored;
  uint32_t is_monitored;
  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);

  /* Set pointer to register of selected analog watchdog */
  if (awd_y == LL_ADC_AWD_1)
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->CFGR1, 0UL);
  }
  else
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD2CR,
                                 (((awd_y & LL_ADC_AWD_CRX_REGOFFSET_MASK)) >> (LL_ADC_AWD_CRX_REGOFFSET_POS)) - 1UL);
  }

  awd_channel_monitored = STM32_READ_BIT(*preg, awd_y);

  if (awd_y == LL_ADC_AWD_1)
  {
    if (channel_remapped == LL_ADC_CHANNEL_NONE)
    {
      is_monitored = ((awd_channel_monitored & (ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN)) == 0UL) ? 1UL : 0UL;
    }
    else if (channel_remapped == LL_ADC_CHANNEL_ALL)
    {
      is_monitored = ((awd_channel_monitored & ADC_CFGR1_AWD1SGL) == 0UL) ? 1UL : 0UL;
    }
    else
    {
      /* Case of single channel */
      is_monitored = (((awd_channel_monitored & ADC_CFGR1_AWD1CH)
                       == (LL_ADC_CHANNEL_TO_DECIMAL_NB(channel_remapped) << ADC_CFGR1_AWD1CH_Pos))) ? 1UL : 0UL;
    }
  }
  else
  {
    if (channel_remapped == LL_ADC_CHANNEL_NONE)
    {
      is_monitored = (awd_channel_monitored == 0UL) ? 1UL : 0UL;
    }
    else if (channel_remapped == LL_ADC_CHANNEL_ALL)
    {
      is_monitored = ((awd_channel_monitored & ADC_AWD2CR_AWDCH) == ADC_AWD2CR_AWDCH) ? 1UL : 0UL;
    }
    else
    {
      is_monitored = ((awd_channel_monitored & (0x1UL << LL_ADC_CHANNEL_TO_DECIMAL_NB(channel_remapped))) != 0UL)
                     ? 1UL : 0UL;
    }
  }

  return is_monitored;
}

/**
  * @brief  Check which ADC analog watchdog monitored channel has triggered the out of window flag
  *         (analog watchdog source channel).
  * @rmtoll
  *  AWD1SR   AWDS_CH        LL_ADC_IsAnalogWDChannelTriggered\n
  *  AWD2SR   AWDS_CH        LL_ADC_IsAnalogWDChannelTriggered\n
  *  AWD3SR   AWDS_CH        LL_ADC_IsAnalogWDChannelTriggered
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   Channel trig status czan be cleared using @ref LL_ADC_ClearAnalogWDChannelTriggered().
  * @retval 0: channel has not triggered AWD flag, 1: channel has triggered AWD flag
  */
__STATIC_INLINE uint32_t LL_ADC_IsAnalogWDChannelTriggered(ADC_TypeDef *p_adc, uint32_t awd_y, uint32_t channel)
{
  const __IO uint32_t *preg;
  uint32_t is_triggered;
  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);
  uint32_t channel_bitfield = (1UL << (channel_remapped & LL_ADC_CH_NUMBER_MASK));

  preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1SR,
                               ((awd_y & LL_ADC_AWD_TRX_REGOFFSET_MASK) >> LL_ADC_AWD_TRX_REGOFFSET_POS));

  is_triggered = (STM32_READ_BIT(*preg, channel_bitfield) == channel_bitfield) ? 1UL : 0UL;

  return is_triggered;
}

/**
  * @brief  Clear ADC analog watchdog monitored channel status triggered.
  * @rmtoll
  *  AWD1SR   AWDS_CH        LL_ADC_IsAnalogWDChannelTriggered\n
  *  AWD2SR   AWDS_CH        LL_ADC_IsAnalogWDChannelTriggered\n
  *  AWD3SR   AWDS_CH        LL_ADC_IsAnalogWDChannelTriggered
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  */
__STATIC_INLINE void LL_ADC_ClearAnalogWDChannelTriggered(ADC_TypeDef *p_adc, uint32_t awd_y, uint32_t channel)
{
  __IO uint32_t *preg;
  uint32_t channel_bitfield;
  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);

  /* Case unitary channel selected (parameter "channel" values except LL_ADC_CHANNEL_ALL and LL_ADC_CHANNEL_NONE) */
  if (LL_ADC_CHANNEL_TO_DECIMAL_NB(channel_remapped) < ADC_CH_NONE_NUMBER)
  {
    channel_bitfield = (1UL << (channel_remapped & LL_ADC_CH_NUMBER_MASK));
  }
  else
  {
    channel_bitfield = ADC_AWD1SR_AWDS_CH;
  }

  preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1SR,
                               ((awd_y & LL_ADC_AWD_TRX_REGOFFSET_MASK) >> LL_ADC_AWD_TRX_REGOFFSET_POS));

  STM32_WRITE_REG(*preg, channel_bitfield);
}

/**
  * @brief  Set ADC analog watchdog threshold value of threshold
  *         high or low.
  * @rmtoll
  *  AWD1LTR  LTR            LL_ADC_SetAnalogWDThresholds\n
  *  AWD1HTR  HTR            LL_ADC_SetAnalogWDThresholds\n
  *  AWD2LTR  LTR            LL_ADC_SetAnalogWDThresholds\n
  *  AWD2HTR  HTR            LL_ADC_SetAnalogWDThresholds\n
  *  AWD3LTR  LTR            LL_ADC_SetAnalogWDThresholds\n
  *  AWD3HTR  HTR            LL_ADC_SetAnalogWDThresholds
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @param  awd_thresholds_high_low This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref LL_ADC_AWD_THRESHOLD_LOW
  * @param  awd_threshold_value Analog watchdog threshold value. Value is signed and can exceed ADC resolution
  *         with post-processing computation (offset, oversampling, data shift, ...).
  *         Value between Min_Data=-4194304 (two's complement 0xFFC00000) and Max_Data=+4194303 (0x003FFFFF)
  * @note   In case of ADC resolution different of 12 bits,
  *         analog watchdog thresholds data require a specific shift.
  *         Use helper macro @ref LL_ADC_ANALOGWD_SET_THRESHOLD_RES().
  * @note   On this STM32 series, there are 2 kinds of analog watchdog
  *         instance:
  *         - AWD standard (instance AWD1):
  *           - channels monitored: can monitor 1 channel or all channels.
  *           - groups monitored: ADC groups regular and-or injected.
  *         - AWD flexible (instances AWD2, AWD3):
  *           - channels monitored: flexible on channels monitored, selection is
  *             channel wise, from from 1 to all channels.
  *             Specificity of this analog watchdog: Multiple channels can
  *             be selected. For example:
  *             (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *           - groups monitored: not selection possible (monitoring on both
  *             groups regular and injected).
  *             Channels selected are monitored on groups regular and injected:
  *             LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *             LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  * @note   If ADC oversampling is enabled, ADC analog watchdog thresholds are
  *         impacted: the comparison of analog watchdog thresholds is done
  *         on oversampling intermediate computation (after ratio, before shift
  *         application): intermediate register bitfield [32:7]
  *         (26 most significant bits).
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either ADC groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDThresholds(ADC_TypeDef *p_adc, uint32_t awd_y, uint32_t awd_thresholds_high_low,
                                                  int32_t awd_threshold_value)
{
  __IO uint32_t *preg;

  /* Set bits with content of parameter "awd_threshold_value" with bits       */
  /* position in register and register position depending on parameters       */
  /* "awd_thresholds_high_low" and "awd_y".                                   */
  /* Parameters "awd_y" and "awd_threshold_value" are used with masks because */
  /* containing other bits reserved for other purpose.                        */
  if (awd_y == LL_ADC_AWD_1)
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR, (awd_thresholds_high_low));
  }
  else
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR,
                                 (((awd_y & LL_ADC_AWD_TRX_REGOFFSET_MASK) >> LL_ADC_AWD_TRX_REGOFFSET_POS) * 2UL)
                                 + (awd_thresholds_high_low));
  }

  /* Mask with ADC_LTR_LT for case of negative value, to exclude two's complement exceeding "1" left bits */
  STM32_MODIFY_REG(*preg, ADC_AWD1LTR_LTR, ((uint32_t)awd_threshold_value & ADC_AWD1LTR_LTR));
}

/**
  * @brief  Get ADC analog watchdog threshold value of threshold high,
  *         threshold low or raw data with ADC thresholds high and low
  *         concatenated.
  * @rmtoll
  *  AWD1LTR  LTR            LL_ADC_GetAnalogWDThresholds\n
  *  AWD1HTR  HTR            LL_ADC_GetAnalogWDThresholds\n
  *  AWD2LTR  LTR            LL_ADC_GetAnalogWDThresholds\n
  *  AWD2HTR  HTR            LL_ADC_GetAnalogWDThresholds\n
  *  AWD3LTR  LTR            LL_ADC_GetAnalogWDThresholds\n
  *  AWD3HTR  HTR            LL_ADC_GetAnalogWDThresholds
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @param  awd_thresholds_high_low This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref LL_ADC_AWD_THRESHOLD_LOW
  * @note   In case of ADC resolution different of 12 bits,
  *         analog watchdog thresholds data require a specific shift.
  *         Use helper macro @ref LL_ADC_ANALOGWD_GET_THRESHOLD_RES().
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
__STATIC_INLINE int32_t LL_ADC_GetAnalogWDThresholds(const ADC_TypeDef *p_adc,
                                                     uint32_t awd_y, uint32_t awd_thresholds_high_low)
{
  const __IO uint32_t *preg;
  uint32_t threshold_raw;

  if (awd_y == LL_ADC_AWD_1)
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR, (awd_thresholds_high_low));
  }
  else
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR,
                                 (((awd_y & LL_ADC_AWD_TRX_REGOFFSET_MASK) >> LL_ADC_AWD_TRX_REGOFFSET_POS) * 2UL)
                                 + (awd_thresholds_high_low));
  }

  threshold_raw = STM32_READ_BIT(*preg, ADC_AWD1LTR_LTR);
  /* In case of negative number (identified by bitfield MSB (bit 22)): update threshold value to negative
     value on 32 bits */
  if ((threshold_raw & (1UL << 22U)) != 0UL)
  {
    threshold_raw |= ~ADC_AWD1LTR_LTR;
  }

  return (int32_t)threshold_raw;
}

/**
  * @brief  Set ADC analog watchdog thresholds value of both thresholds
  *         high and low.
  * @rmtoll
  *  TR1      HT1            LL_ADC_ConfigAnalogWDThresholds\n
  *  TR2      HT2            LL_ADC_ConfigAnalogWDThresholds\n
  *  TR3      HT3            LL_ADC_ConfigAnalogWDThresholds\n
  *  TR1      LT1            LL_ADC_ConfigAnalogWDThresholds\n
  *  TR2      LT2            LL_ADC_ConfigAnalogWDThresholds\n
  *  TR3      LT3            LL_ADC_ConfigAnalogWDThresholds
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  *         @arg @ref LL_ADC_AWD_2
  *         @arg @ref LL_ADC_AWD_3
  * @param  awd_threshold_high_value Analog watchdog threshold high value. Value is signed and can exceed ADC resolution
  *         with post-processing computation (offset, oversampling, data shift, ...).
  *         Value between Min_Data=-4194304 (two's complement 0xFFC00000) and Max_Data=+4194303 (0x003FFFFF)
  * @param  awd_threshold_low_value Analog watchdog threshold low value. Value is signed and can exceed ADC resolution
  *         with post-processing computation (offset, oversampling, data shift, ...).
  *         Value between Min_Data=-4194304 (two's complement 0xFFC00000) and Max_Data=+4194303 (0x003FFFFF)
  * @note   If value of only one threshold high or low must be set,
  *         use function @ref LL_ADC_SetAnalogWDThresholds().
  * @note   In case of ADC resolution different of 12 bits,
  *         analog watchdog thresholds data require a specific shift.
  *         Use helper macro @ref LL_ADC_ANALOGWD_SET_THRESHOLD_RES().
  * @note   On this STM32 series, there are 2 kinds of analog watchdog
  *         instance:
  *         - AWD standard (instance AWD1):
  *           - channels monitored: can monitor 1 channel or all channels.
  *           - groups monitored: ADC group regular.
  *           - resolution: resolution is not limited (corresponds to
  *             ADC resolution configured).
  *         - AWD flexible (instances AWD2, AWD3):
  *           - channels monitored: flexible on channels monitored, selection is
  *             channel wise, from 1 to all channels.
  *             Specificity of this analog watchdog: Multiple channels can
  *             be selected. For example:
  *             (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *           - groups monitored: not selection possible (monitoring on both
  *             groups regular and injected).
  *             Channels selected are monitored on groups regular and injected:
  *             LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *             LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  *           - resolution: resolution is not limited (corresponds to
  *             ADC resolution configured).
  * @note   If ADC oversampling is enabled, ADC analog watchdog thresholds are
  *         impacted: the comparison of analog watchdog thresholds is done on
  *         oversampling final computation (after ratio and shift application):
  *         ADC data register bitfield [15:4] (12 most significant bits).
  *         Examples:
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 12 bits (ratio 16 and shift 4, or ratio 32 and shift 5, ...):
  *           ADC analog watchdog thresholds must be divided by 16.
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 14 bits (ratio 16 and shift 2, or ratio 32 and shift 3, ...):
  *           ADC analog watchdog thresholds must be divided by 4.
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 16 bits (ratio 16 and shift none, or ratio 32 and shift 1, ...):
  *           ADC analog watchdog thresholds match directly to ADC data register.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_ConfigAnalogWDThresholds(ADC_TypeDef *p_adc, uint32_t awd_y,
                                                     uint32_t awd_threshold_high_value,
                                                     uint32_t awd_threshold_low_value)
{
  __IO uint32_t *preg;
  __IO uint32_t *preg2;
  /* Set bits with content of parameter "AWDThresholdxxxValue" with bits      */
  /* position in register and register position depending on parameter        */
  /* "awd_y".                                                                  */
  /* Parameters "awd_y" and "AWDThresholdxxxValue" are used with masks because */
  /* containing other bits reserved for other purpose.                        */
  if (awd_y == LL_ADC_AWD_1)
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR, (LL_ADC_AWD_THRESHOLD_LOW));
    preg2 = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR, (LL_ADC_AWD_THRESHOLD_HIGH));
  }
  else
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR, (((awd_y & LL_ADC_AWD_TRX_REGOFFSET_MASK) \
                                                   >> (LL_ADC_AWD_TRX_REGOFFSET_POS - 1UL)))
                                 + (LL_ADC_AWD_THRESHOLD_LOW));
    preg2 = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR, (((awd_y & LL_ADC_AWD_TRX_REGOFFSET_MASK) \
                                                    >> (LL_ADC_AWD_TRX_REGOFFSET_POS - 1UL)))
                                  + (LL_ADC_AWD_THRESHOLD_HIGH));
  }

  STM32_MODIFY_REG(*preg,  ADC_AWD1LTR_LTR, awd_threshold_low_value);
  STM32_MODIFY_REG(*preg2, ADC_AWD1HTR_HTR, awd_threshold_high_value);
}

/**
  * @brief  Set ADC analog watchdog filtering configuration.
  * @rmtoll
  *  AWD1HTR  AWDFILT        LL_ADC_SetAnalogWDFiltering
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  * @param  awd_filtering This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_FILTERING_NONE
  *         @arg @ref LL_ADC_AWD_FILTERING_2SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_3SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_4SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_5SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_6SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_7SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_8SAMPLES
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  *  @note  On this STM32 series, this feature is only available on first
  *         analog watchdog (AWD1)
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDFiltering(ADC_TypeDef *p_adc, uint32_t awd_y, uint32_t awd_filtering)
{
  __IO uint32_t *preg;

  /* Set bits with content of parameter "awd_threshold_value" with bits       */
  /* position in register and register position depending on parameters       */
  /* "awd_thresholds_high_low" and "awd_y".                                   */
  /* Parameters "awd_y" and "awd_threshold_value" are used with masks because */
  /* containing other bits reserved for other purpose.                        */
  if (awd_y == LL_ADC_AWD_1)
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR, LL_ADC_AWD_THRESHOLD_HIGH);
  }
  else
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR,
                                 (((awd_y & LL_ADC_AWD_TRX_REGOFFSET_MASK) >> LL_ADC_AWD_TRX_REGOFFSET_POS) * 2UL)
                                 + LL_ADC_AWD_THRESHOLD_HIGH);
  }

  /* Mask with ADC_LTR_LT for case of negative value, to exclude two's complement exceeding "1" left bits */
  STM32_MODIFY_REG(*preg, ADC_AWD1HTR_AWDFILT, awd_filtering);
}

/**
  * @brief  Get ADC analog watchdog filtering configuration.
  * @rmtoll
  *  TR1      AWDFILT        LL_ADC_GetAnalogWDFiltering
  * @param  p_adc Pointer to ADC instance
  * @param  awd_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_1
  * @note   On this STM32 series, this feature is only available on first
  *         analog watchdog (AWD1).
  * @retval Returned value can be:
  *         @arg @ref LL_ADC_AWD_FILTERING_NONE
  *         @arg @ref LL_ADC_AWD_FILTERING_2SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_3SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_4SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_5SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_6SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_7SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_8SAMPLES
  */
__STATIC_INLINE uint32_t LL_ADC_GetAnalogWDFiltering(const ADC_TypeDef *p_adc, uint32_t awd_y)
{
  const __IO uint32_t *preg;

  if (awd_y == LL_ADC_AWD_1)
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR, LL_ADC_AWD_THRESHOLD_HIGH);
  }
  else
  {
    preg = LL_ADC_PTR_REG_OFFSET(p_adc->AWD1LTR,
                                 (((awd_y & LL_ADC_AWD_TRX_REGOFFSET_MASK) >> LL_ADC_AWD_TRX_REGOFFSET_POS) * 2UL)
                                 + LL_ADC_AWD_THRESHOLD_HIGH);
  }

  return (uint32_t)STM32_READ_BIT(*preg, ADC_AWD1HTR_AWDFILT);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_oversampling Configuration of ADC transversal scope: oversampling
  * @{
  */

/**
  * @brief  Set ADC oversampling scope: ADC groups regular and-or injected
  *         (availability of ADC group injected depends on STM32 series).
  * @rmtoll
  *  CFGR2    ROVSE          LL_ADC_SetOverSamplingScope\n
  *  CFGR2    ROVSM          LL_ADC_SetOverSamplingScope\n
  *  CFGR3    JOVSPAR        LL_ADC_SetOverSamplingScope\n
  *  CFGR3    JOVSE          LL_ADC_SetOverSamplingScope
  * @param  p_adc Pointer to ADC instance
  * @param  ovs_scope This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_DISABLE
  *         @arg @ref LL_ADC_OVS_REG_CONTINUED
  *         @arg @ref LL_ADC_OVS_REG_RESUMED
  *         @arg @ref LL_ADC_OVS_INJ
  *         @arg @ref LL_ADC_OVS_INJ_REG_RESUMED
  *         @arg @ref LL_ADC_OVS_INJ_PARALLEL
  *         @arg @ref LL_ADC_OVS_INJ_PARALL_REG_CONT
  *         @arg @ref LL_ADC_OVS_INJ_PARALL_REG_RESUM
  * @note   This device supports parallel injected oversampling, allowing to
  *         perform oversampling on groups regular and injected independently
  *         (different accumulators with their own settings ratio and shift).
  *         Moreover, each injected data register has its own accumulator.
  *         For equivalent function to configure oversampling scope with accumulator explicit selection,
  *         refer to @ref LL_ADC_SetOverSamplingInstScope().
  *         For parallel injected oversampling configuration, refer to parameters LL_ADC_OVS_INJ_PARALLEL_... and
  *         functions LL_ADC_SetOverSamplingInj...().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingScope(ADC_TypeDef *p_adc, uint32_t ovs_scope)
{
  if ((ovs_scope & LL_ADC_OVS_INJ_PARALLEL_SEL) != 0UL)
  {
    STM32_MODIFY_REG(p_adc->CFGR3, ADC_CFGR3_JOVSE | ADC_CFGR3_JOVSPAR,
                     (ovs_scope >> LL_ADC_OVS_INJ_PARALLEL_SEL_POS) & (ADC_CFGR3_JOVSE | ADC_CFGR3_JOVSPAR));
  }

  STM32_MODIFY_REG(p_adc->CFGR2, ADC_CFGR2_ROVSE | ADC_CFGR2_ROVSM, (ovs_scope & (ADC_CFGR2_ROVSE | ADC_CFGR2_ROVSM)));
}

/**
  * @brief  Get ADC oversampling scope: ADC groups regular and-or injected
  *         (availability of ADC group injected depends on STM32 series).
  * @rmtoll
  *  CFGR2    ROVSE          LL_ADC_GetOverSamplingScope\n
  *  CFGR2    ROVSM          LL_ADC_GetOverSamplingScope\n
  *  CFGR3    JOVSPAR        LL_ADC_GetOverSamplingScope\n
  *  CFGR3    JOVSE          LL_ADC_GetOverSamplingScope
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OVS_DISABLE
  *         @arg @ref LL_ADC_OVS_REG_CONTINUED
  *         @arg @ref LL_ADC_OVS_REG_RESUMED
  *         @arg @ref LL_ADC_OVS_INJ
  *         @arg @ref LL_ADC_OVS_INJ_REG_RESUMED
  *         @arg @ref LL_ADC_OVS_INJ_PARALLEL
  *         @arg @ref LL_ADC_OVS_INJ_PARALL_REG_CONT
  *         @arg @ref LL_ADC_OVS_INJ_PARALL_REG_RESUM
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingScope(const ADC_TypeDef *p_adc)
{
  uint32_t ovs_inj_parallel = STM32_READ_BIT(p_adc->CFGR3, ADC_CFGR3_JOVSE | ADC_CFGR3_JOVSPAR)
                              << LL_ADC_OVS_INJ_PARALLEL_SEL_POS;

  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR2, ADC_CFGR2_ROVSE | ADC_CFGR2_ROVSM)
                    | ovs_inj_parallel);
}

/**
  * @brief  Set ADC oversampling scope: ADC groups regular and-or injected in function of oversampling instance
  *         (availability of ADC group injected depends on STM32 series).
  * @rmtoll
  *  CFGR2    ROVSE          LL_ADC_SetOverSamplingInstScope\n
  *  CFGR2    ROVSM          LL_ADC_SetOverSamplingInstScope\n
  *  CFGR3    JOVSPAR        LL_ADC_SetOverSamplingInstScope\n
  *  CFGR3    JOVSE          LL_ADC_SetOverSamplingInstScope
  * @param  p_adc Pointer to ADC instance
  * @param  ovs_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_1
  *         @arg @ref LL_ADC_OVS_INJ_1
  * @param  ovs_scope This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_DISABLE
  *         @arg @ref LL_ADC_OVS_REG_CONTINUED   (1)
  *         @arg @ref LL_ADC_OVS_REG_RESUMED     (1)
  *         @arg @ref LL_ADC_OVS_INJ             (2)
  *         @arg @ref LL_ADC_OVS_INJ_PARALLEL    (2)
  *
  *         (1) Parameter available only with oversampling instance: LL_ADC_OVS_1
  *         (2) Parameter available only with oversampling instance: LL_ADC_OVS_INJ_1
  * @note   This device supports parallel injected oversampling, allowing to
  *         perform oversampling on groups regular and injected independently
  *         (different accumulators with their own settings ratio and shift).
  *         Moreover, each injected data register has its own accumulator.
  *         For parallel injected oversampling configuration, refer to parameters LL_ADC_OVS_INJ_PARALLEL_... and
  *         functions LL_ADC_SetOverSamplingInj...().
  * @note   Differences with series not featuring parallel injected oversampling:
  *         equivalent setting of LL_ADC_OVS_INJ_REG_RESUMED can be done with
  *         successive calls of @ref LL_ADC_SetOverSamplingInstScope():
  *         - oversampling on group regular with LL_ADC_OVS_REG_RESUMED
  *           and oversampling instance LL_ADC_OVS_1.
  *         - oversampling on group injected with LL_ADC_OVS_INJ
  *           and oversampling instance LL_ADC_OVS_INJ_1
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingInstScope(ADC_TypeDef *p_adc, uint32_t ovs_y, uint32_t ovs_scope)
{
  if (ovs_y == LL_ADC_OVS_INJ_1) /* Oversampling instance: parallel injected oversampling */
  {
    STM32_MODIFY_REG(p_adc->CFGR3, ADC_CFGR3_JOVSE | ADC_CFGR3_JOVSPAR, (ovs_scope >> LL_ADC_OVS_INJ_PARALLEL_SEL_POS));
  }
  else /* Oversampling instance: group regular and-or injected (legacy) oversampling */
  {
    STM32_MODIFY_REG(p_adc->CFGR2, ADC_CFGR2_ROVSE | ADC_CFGR2_ROVSM, ovs_scope);
  }
}

/**
  * @brief  Get ADC oversampling scope: ADC groups regular and-or injected in function of oversampling instance
  *         (availability of ADC group injected depends on STM32 series).
  * @rmtoll
  *  CFGR2    ROVSE          LL_ADC_GetOverSamplingInstScope\n
  *  CFGR2    ROVSM          LL_ADC_GetOverSamplingInstScope\n
  *  CFGR3    JOVSPAR        LL_ADC_GetOverSamplingInstScope\n
  *  CFGR3    JOVSE          LL_ADC_GetOverSamplingInstScope
  * @param  p_adc Pointer to ADC instance
  * @param  ovs_y AWD instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_1
  *         @arg @ref LL_ADC_OVS_INJ_1
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OVS_DISABLE
  *         @arg @ref LL_ADC_OVS_REG_CONTINUED   (1)
  *         @arg @ref LL_ADC_OVS_REG_RESUMED     (1)
  *         @arg @ref LL_ADC_OVS_INJ             (2)
  *         @arg @ref LL_ADC_OVS_INJ_PARALLEL    (2)
  *
  *         (1) Parameter available only with oversampling instance: LL_ADC_OVS_1
  *         (2) Parameter available only with oversampling instance: LL_ADC_OVS_INJ_1
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingInstScope(const ADC_TypeDef *p_adc, uint32_t ovs_y)
{
  uint32_t ovs_scope;
  if (ovs_y == LL_ADC_OVS_INJ_1) /* Oversampling instance: parallel injected oversampling */
  {
    ovs_scope = (STM32_READ_BIT(p_adc->CFGR3, ADC_CFGR3_JOVSE | ADC_CFGR3_JOVSPAR) << LL_ADC_OVS_INJ_PARALLEL_SEL_POS);
  }
  else /* Oversampling instance: group regular oversampling */
  {
    ovs_scope = STM32_READ_BIT(p_adc->CFGR2, ADC_CFGR2_ROVSE |  ADC_CFGR2_ROVSM);
  }

  return ovs_scope;
}

/**
  * @brief  Set ADC oversampling discontinuous mode (triggered mode).
  * @rmtoll
  *  CFGR2    TROVS          LL_ADC_SetOverSamplingDiscont
  * @param  p_adc Pointer to ADC instance
  * @param  ovs_discont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_CONT
  *         @arg @ref LL_ADC_OVS_DISCONT
  * @note   The equivalent function is available for parallel injected oversampling,
  *         refer to @ref LL_ADC_SetOverSamplingInjDiscont().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group regular.
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingDiscont(ADC_TypeDef *p_adc, uint32_t ovs_discont)
{
  STM32_MODIFY_REG(p_adc->CFGR2, ADC_CFGR2_TROVS, ovs_discont);
}

/**
  * @brief  Get ADC oversampling discontinuous mode (triggered mode).
  * @rmtoll
  *  CFGR2    TROVS          LL_ADC_GetOverSamplingDiscont
  * @param  p_adc Pointer to ADC instance
  * @note   The equivalent function is available for parallel injected oversampling,
  *         refer to @ref LL_ADC_GetOverSamplingInjDiscont().
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OVS_CONT
  *         @arg @ref LL_ADC_OVS_DISCONT
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingDiscont(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR2, ADC_CFGR2_TROVS));
}

/**
  * @brief  Set ADC oversampling (impacting both ADC groups regular and injected).
  * @rmtoll
  *  CFGR2    OVSS           LL_ADC_ConfigOverSamplingRatioShift\n
  *  CFGR2    OVSR           LL_ADC_ConfigOverSamplingRatioShift
  * @param  p_adc Pointer to ADC instance
  * @param  ratio This parameter can be in the range from 1 to 1024
  * @param  shift This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_SHIFT_NONE
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_1
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_2
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_3
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_4
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_5
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_6
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_7
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_8
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_9
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_10
  *         or numerical value for right shift value in range from 0 to 10 (value "0" for LL_ADC_OVS_SHIFT_NONE)
  * @note   This function set the 2 items of oversampling configuration:
  *         - ratio
  *         - shift
  * @note   The equivalent function is available for parallel injected oversampling,
  *         refer to @ref LL_ADC_ConfigOverSamplingInjRatioShift().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_ConfigOverSamplingRatioShift(ADC_TypeDef *p_adc, uint32_t ratio, uint32_t shift)
{
  STM32_MODIFY_REG(p_adc->CFGR2,
                   (ADC_CFGR2_OVSS | ADC_CFGR2_OVSR),
                   ((shift << ADC_CFGR2_OVSS_Pos) | (((ratio - 1UL) << ADC_CFGR2_OVSR_Pos))));
}

/**
  * @brief  Get ADC oversampling ratio.
  * @rmtoll
  *  CFGR2    OVSR           LL_ADC_GetOverSamplingRatio
  * @param  p_adc Pointer to ADC instance
  * @note   The equivalent function is available for parallel injected oversampling,
  *         refer to @ref LL_ADC_GetOverSamplingInjRatio().
  * @retval ovs_ratio This parameter can be a value from 1 to 1024
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingRatio(const ADC_TypeDef *p_adc)
{
  return (((uint32_t)(STM32_READ_BIT(p_adc->CFGR2, ADC_CFGR2_OVSR)) \
           + (1UL << ADC_CFGR2_OVSR_Pos)) >> ADC_CFGR2_OVSR_Pos);
}

/**
  * @brief  Get ADC oversampling shift.
  * @rmtoll
  *  CFGR2    OVSS           LL_ADC_GetOverSamplingShift
  * @param  p_adc Pointer to ADC instance
  * @note   The equivalent function is available for parallel injected oversampling,
  *         refer to @ref LL_ADC_GetOverSamplingInjShift().
  * @retval shift This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_SHIFT_NONE
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_1
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_2
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_3
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_4
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_5
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_6
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_7
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_8
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_9
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_10
  *         or numerical value for right shift value in range from 0 to 10 (value "0" for LL_ADC_OVS_SHIFT_NONE)
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingShift(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR2, ADC_CFGR2_OVSS) >> ADC_CFGR2_OVSS_Pos);
}

/**
  * @brief  Set ADC oversampling discontinuous mode (triggered mode) for parallel injected oversampling.
  * @rmtoll
  *  CFGR3    TJOVS          LL_ADC_SetOverSamplingInjDiscont
  * @param  p_adc Pointer to ADC instance
  * @param  ovs_discont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_CONT
  *         @arg @ref LL_ADC_OVS_DISCONT
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group injected.
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingInjDiscont(ADC_TypeDef *p_adc, uint32_t ovs_discont)
{
  STM32_MODIFY_REG(p_adc->CFGR3, ADC_CFGR3_TJOVS, ovs_discont);
}

/**
  * @brief  Get ADC oversampling discontinuous mode (triggered mode) for parallel injected oversampling.
  * @rmtoll
  *  CFGR3    TJOVS          LL_ADC_GetOverSamplingInjDiscont
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OVS_CONT
  *         @arg @ref LL_ADC_OVS_DISCONT
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingInjDiscont(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR3, ADC_CFGR3_TJOVS));
}

/**
  * @brief  Set ADC oversampling for parallel injected oversampling.
  * @rmtoll
  *  CFGR3    JOVSS          LL_ADC_ConfigOverSamplingInjRatioShift\n
  *  CFGR3    JOVSR          LL_ADC_ConfigOverSamplingInjRatioShift
  * @param  p_adc Pointer to ADC instance
  * @param  ratio This parameter can be in the range from 1 to 1024
  * @param  shift This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_SHIFT_NONE
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_1
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_2
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_3
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_4
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_5
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_6
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_7
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_8
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_9
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_10
  *         or numerical value for right shift value in range from 0 to 10 (value "0" for LL_ADC_OVS_SHIFT_NONE)
  * @note   This function set the 2 items of oversampling configuration:
  *         - ratio
  *         - shift
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups injected.
  */
__STATIC_INLINE void LL_ADC_ConfigOverSamplingInjRatioShift(ADC_TypeDef *p_adc, uint32_t ratio, uint32_t shift)
{
  STM32_MODIFY_REG(p_adc->CFGR3,
                   (ADC_CFGR3_JOVSS | ADC_CFGR3_JOVSR),
                   ((shift << ADC_CFGR3_JOVSS_Pos) | (((ratio - 1UL) << ADC_CFGR3_JOVSR_Pos))));
}

/**
  * @brief  Get ADC oversampling ratio for parallel injected oversampling.
  * @rmtoll
  *  CFGR3    JOVSR          LL_ADC_GetOverSamplingInjRatio
  * @param  p_adc Pointer to ADC instance
  * @retval ovs_ratio This parameter can be a value from 1 to 1024
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingInjRatio(const ADC_TypeDef *p_adc)
{
  return (((uint32_t)(STM32_READ_BIT(p_adc->CFGR3, ADC_CFGR3_JOVSR)) \
           + (1UL << ADC_CFGR3_JOVSR_Pos)) >> ADC_CFGR3_JOVSR_Pos);
}

/**
  * @brief  Get ADC oversampling shift for parallel injected oversampling.
  * @rmtoll
  *  CFGR3    JOVSS          LL_ADC_GetOverSamplingInjShift
  * @param  p_adc Pointer to ADC instance
  * @retval shift This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_SHIFT_NONE
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_1
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_2
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_3
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_4
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_5
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_6
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_7
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_8
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_9
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_10
  *         or numerical value for right shift value in range from 0 to 10 (value "0" for LL_ADC_OVS_SHIFT_NONE)
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingInjShift(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR3, ADC_CFGR3_JOVSS) >> ADC_CFGR3_JOVSS_Pos);
}

/**
  * @brief  Set ADC oversampling intermediate accumulated values config.
  * @rmtoll
  *  CFGR3    JOVSIVE        LL_ADC_SetOverSamplingInjIntermAcc
  * @param  p_adc Pointer to ADC instance
  * @param  ovs_interm_acc This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_INTERM_ACC_DISABLE
  *         @arg @ref LL_ADC_OVS_INTERM_ACC_ENABLE
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on group injected.
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingInjIntermAcc(ADC_TypeDef *p_adc, uint32_t ovs_interm_acc)
{
  STM32_MODIFY_REG(p_adc->CFGR3, ADC_CFGR3_JOVSIVE, ovs_interm_acc);
}

/**
  * @brief  Get ADC oversampling intermediate accumulated values config.
  * @rmtoll
  *  CFGR3    JOVSIVE        LL_ADC_GetOverSamplingInjIntermAcc
  * @param  p_adc Pointer to ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OVS_INTERM_ACC_DISABLE
  *         @arg @ref LL_ADC_OVS_INTERM_ACC_ENABLE
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingInjIntermAcc(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->CFGR3, ADC_CFGR3_JOVSIVE));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_offset Configuration of ADC transversal scope: offset
  * @{
  */

/**
  * @brief  Set ADC selected offset number 1, 2, 3 or 4.
  * @rmtoll
  *  OFCFGR1     OFFSET_CH      LL_ADC_SetOffsetChannel\n
  *  OFCFGR2     OFFSET_CH      LL_ADC_SetOffsetChannel\n
  *  OFCFGR3     OFFSET_CH      LL_ADC_SetOffsetChannel\n
  *  OFCFGR4     OFFSET_CH      LL_ADC_SetOffsetChannel
  * @param  p_adc Pointer to ADC instance
  * @param  offset_y Offset instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.
  * @note   This function set the item of offset configuration:
  *         ADC channel to which the offset programmed will be applied
  *         (independently of channel mapped on ADC group regular
  *         or group injected)
  *         For the other item of offset level, refer to @ref LL_ADC_SetOffsetLevel().
  * @note   Offset value can be subtracted or added using separate sign configuration,
  *         refer to @ref LL_ADC_SetOffsetSign().
  * @note   In case of ADC resolution different of default resolution,
  *         offset level data requires a specific shift.
  *         Use helper macro @ref LL_ADC_OFFSET_SET_LEVEL_RES().
  * @note   If a channel is mapped on several offsets numbers, only the offset
  *         with the lowest value is considered for the subtraction.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetOffsetChannel(ADC_TypeDef *p_adc, uint32_t offset_y, uint32_t channel)
{
  __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->OFCFGR[0], offset_y);
  uint32_t channel_remapped = LL_ADC_REMAP_CHANNEL_SET(p_adc, channel);

  /* Note: Value shift for correspondence with channel definition using LL_ADC_CH_NUMBER_MASK */
  STM32_MODIFY_REG(*preg,
                   ADC_OFCFGR_OFFSET_CH,
                   LL_ADC_CHANNEL_TO_DECIMAL_NB(channel_remapped) << ADC_OFCFGR_OFFSET_CH_Pos);
}

/**
  * @brief  Get for the ADC selected offset number 1, 2, 3 or 4:
  *         Channel to which the offset programmed will be applied
  *         (independently of channel mapped on ADC group regular
  *         or group injected).
  * @rmtoll
  *  OFCFGR1     OFFSET1_CH     LL_ADC_GetOffsetChannel\n
  *  OFCFGR2     OFFSET2_CH     LL_ADC_GetOffsetChannel\n
  *  OFCFGR3     OFFSET3_CH     LL_ADC_GetOffsetChannel\n
  *  OFCFGR4     OFFSET4_CH     LL_ADC_GetOffsetChannel
  * @param  p_adc Pointer to ADC instance
  * @param  offset_y Offset instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @note   Usage of the returned channel number:
  *         - To reinject this channel into another function LL_ADC_xxx:
  *           the returned channel number is only partly formatted on definition
  *           of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *           with parts of literals LL_ADC_CHANNEL_x or using
  *           helper macro @ref LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Then the selected literal LL_ADC_CHANNEL_x can be used
  *           as parameter for another function.
  *         - To get the channel number in decimal format:
  *           process the returned value with the helper macro
  *           @ref LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR     (1)
  *         @arg @ref LL_ADC_CHANNEL_VDDCORE
  *         @arg @ref LL_ADC_CHANNEL_OPAMP1_OUT     (1)(3)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP2_OUT     (1)(2)
  *         @arg @ref LL_ADC_CHANNEL_OPAMP3_OUT     (2)(3)
  *
  *         (1) On this STM32 series, parameter available on ADC instance: ADC1.\n
  *         (2) On this STM32 series, parameter available on ADC instance: ADC2.\n
  *         (3) On this STM32 series, parameter available on ADC instance: ADC3.\n
  *         (4) For ADC channel read back from ADC register,
  *             comparison with internal channel parameter to be done
  *             using helper macro @ref LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  *         (1, 2) For ADC channel read back from ADC register,
  *                comparison with internal channel parameter to be done
  *                using helper macro @ref LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetChannel(const ADC_TypeDef *p_adc, uint32_t offset_y)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->OFCFGR[0], offset_y);

  uint32_t channel = (uint32_t) LL_ADC_DECIMAL_NB_TO_CHANNEL(STM32_READ_BIT(*preg, ADC_OFCFGR_OFFSET_CH) \
                                                             >> ADC_OFCFGR_OFFSET_CH_Pos);

  return LL_ADC_REMAP_CHANNEL_GET(p_adc, channel);
}

/**
  * @brief  Set for the ADC selected offset number 1, 2, 3 or 4:
  *         Offset level (offset to be subtracted from the raw
  *         converted data).
  * @rmtoll
  *  OFR1     OFFSET1        LL_ADC_SetOffsetLevel\n
  *  OFR2     OFFSET2        LL_ADC_SetOffsetLevel\n
  *  OFR3     OFFSET3        LL_ADC_SetOffsetLevel\n
  *  OFR4     OFFSET4        LL_ADC_SetOffsetLevel
  * @param  p_adc Pointer to ADC instance
  * @param  offset_y Offset instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  offset_level Value between Min_Data=0x000 and Max_Data=0x003FFFFF
  * @note   Offset value can be subtracted or added using separate sign configuration,
  *         refer to @ref LL_ADC_SetOffsetSign().
  * @note   This function set the item of offset configuration:
  *         Offset level (offset to be computed from the raw converted data).
  *         ADC channel to which the offset programmed will be applied
  *         For the other item of ADC channel to which the offset programmed will be applied,
  *         refer to @ref LL_ADC_SetOffsetChannel().
  * @note   Caution: Offset format is dependent to ADC resolution:
  *         offset has to be left-aligned on bit 11, the LSB (right bits)
  *         are set to 0.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetOffsetLevel(ADC_TypeDef *p_adc, uint32_t offset_y, uint32_t offset_level)
{
  __IO uint32_t *preg_offset_val = LL_ADC_PTR_REG_OFFSET(p_adc->OFR[0], offset_y);

  STM32_MODIFY_REG(*preg_offset_val,
                   ADC_OFR_OFFSET,
                   offset_level);
}

/**
  * @brief  Get for the ADC selected offset number 1, 2, 3 or 4:
  *         Offset level (offset to be computed from the raw
  *         converted data).
  * @rmtoll
  *  OFR1     OFFSET1        LL_ADC_GetOffsetLevel\n
  *  OFR2     OFFSET2        LL_ADC_GetOffsetLevel\n
  *  OFR3     OFFSET3        LL_ADC_GetOffsetLevel\n
  *  OFR4     OFFSET4        LL_ADC_GetOffsetLevel
  * @param  p_adc Pointer to ADC instance
  * @param  offset_y Offset instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @note   Offset value can be subtracted or added using separate sign configuration,
  *         refer to @ref LL_ADC_SetOffsetSign().
  * @note   In case of ADC resolution different of default resolution,
  *         offset level data requires a specific shift.
  *         Use helper macro @ref LL_ADC_OFFSET_SET_LEVEL_RES().
  * @retval Value between Min_Data=0x000 and Max_Data=0x003FFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetLevel(const ADC_TypeDef *p_adc, uint32_t offset_y)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->OFR[0], offset_y);

  return (uint32_t) STM32_READ_BIT(*preg, ADC_OFR_OFFSET);
}

/**
  * @brief  Set for the ADC selected offset number 1, 2, 3 or 4:
  *         choose offset sign.
  * @rmtoll
  *  OFCFGR1  OFFSETPOS      LL_ADC_SetOffsetSign\n
  *  OFCFGR2  OFFSETPOS      LL_ADC_SetOffsetSign\n
  *  OFCFGR3  OFFSETPOS      LL_ADC_SetOffsetSign\n
  *  OFCFGR4  OFFSETPOS      LL_ADC_SetOffsetSign
  * @param  p_adc Pointer to ADC instance
  * @param  offset_y Offset instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  offset_sign This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_SIGN_NEGATIVE
  *         @arg @ref LL_ADC_OFFSET_SIGN_POSITIVE
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_SetOffsetSign(ADC_TypeDef *p_adc, uint32_t offset_y, uint32_t offset_sign)
{
  __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->OFCFGR[0], offset_y);

  STM32_MODIFY_REG(*preg, ADC_OFCFGR_POSOFF, offset_sign);
}

/**
  * @brief  Get for the ADC selected offset number 1, 2, 3 or 4:
  *         offset sign if positive or negative.
  * @rmtoll
  *  OFR1     OFFSETPOS      LL_ADC_GetOffsetSign\n
  *  OFR2     OFFSETPOS      LL_ADC_GetOffsetSign\n
  *  OFR3     OFFSETPOS      LL_ADC_GetOffsetSign\n
  *  OFR4     OFFSETPOS      LL_ADC_GetOffsetSign
  * @param  p_adc Pointer to ADC instance
  * @param  offset_y Offset instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_SIGN_NEGATIVE
  *         @arg @ref LL_ADC_OFFSET_SIGN_POSITIVE
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetSign(const ADC_TypeDef *p_adc, uint32_t offset_y)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->OFCFGR[0], offset_y);

  return (uint32_t) STM32_READ_BIT(*preg, ADC_OFCFGR_POSOFF);
}

/**
  * @brief  Set Signed saturation for the ADC selected offset number 1, 2, 3 or 4:
  *         signed offset saturation if enabled or disabled.
  * @rmtoll
  *  OFCFGR1  SSAT          LL_ADC_SetOffsetSignedSaturation\n
  *  OFCFGR2  SSAT          LL_ADC_SetOffsetSignedSaturation\n
  *  OFCFGR3  SSAT          LL_ADC_SetOffsetSignedSaturation\n
  *  OFCFGR4  SSAT          LL_ADC_SetOffsetSignedSaturation
  * @param  p_adc Pointer to ADC instance
  * @param  offset_y Offset instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  offset_signed_saturation This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_SIGNED_SATURATION_ENABLE
  *         @arg @ref LL_ADC_OFFSET_SIGNED_SATURATION_DISABLE
  */
__STATIC_INLINE void LL_ADC_SetOffsetSignedSaturation(ADC_TypeDef *p_adc, uint32_t offset_y,
                                                      uint32_t offset_signed_saturation)
{
  __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->OFCFGR[0], offset_y);
  STM32_MODIFY_REG(*preg, ADC_OFCFGR_SSAT, offset_signed_saturation);
}

/**
  * @brief  Get Signed saturation for the ADC selected offset number 1, 2, 3 or 4:
  *         signed offset saturation if enabled or disabled.
  * @rmtoll
  *  OFCFGR1  SSAT          LL_ADC_GetOffsetSignedSaturation\n
  *  OFCFGR2  SSAT          LL_ADC_GetOffsetSignedSaturation\n
  *  OFCFGR3  SSAT          LL_ADC_GetOffsetSignedSaturation\n
  *  OFCFGR4  SSAT          LL_ADC_GetOffsetSignedSaturation
  * @param  p_adc Pointer to ADC instance
  * @param  offset_y Offset instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_SIGNED_SATURATION_ENABLE
  *         @arg @ref LL_ADC_OFFSET_SIGNED_SATURATION_DISABLE
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetSignedSaturation(const ADC_TypeDef *p_adc, uint32_t offset_y)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->OFCFGR[0], offset_y);
  return (uint32_t) STM32_READ_BIT(*preg, ADC_OFCFGR_SSAT);
}

/**
  * @brief  Set Unsigned saturation for the ADC selected offset instance 1, 2, 3 or 4:
  *         signed offset saturation if enabled or disabled.
  * @rmtoll
  *  OFCFGR1  USAT          LL_ADC_SetOffsetUnsignedSaturation\n
  *  OFCFGR2  USAT          LL_ADC_SetOffsetUnsignedSaturation\n
  *  OFCFGR3  USAT          LL_ADC_SetOffsetUnsignedSaturation\n
  *  OFCFGR4  USAT          LL_ADC_SetOffsetUnsignedSaturation
  * @param  p_adc Pointer to ADC instance
  * @param  offset_y Offset instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  offset_unsigned_saturation This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_UNSIGNED_SATURATION_ENABLE
  *         @arg @ref LL_ADC_OFFSET_UNSIGNED_SATURATION_DISABLE
  */
__STATIC_INLINE void LL_ADC_SetOffsetUnsignedSaturation(ADC_TypeDef *p_adc, uint32_t offset_y,
                                                        uint32_t offset_unsigned_saturation)
{
  __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->OFCFGR[0], offset_y);
  STM32_MODIFY_REG(*preg, ADC_OFCFGR_USAT, offset_unsigned_saturation);
}

/**
  * @brief  Get Unsigned saturation for the ADC selected offset number 1, 2, 3 or 4:
  *         signed offset saturation if enabled or disabled.
  * @rmtoll
  *  OFCFGR1  USAT          LL_ADC_GetOffsetUnsignedSaturation\n
  *  OFCFGR2  USAT          LL_ADC_GetOffsetUnsignedSaturation\n
  *  OFCFGR3  USAT          LL_ADC_GetOffsetUnsignedSaturation\n
  *  OFCFGR4  USAT          LL_ADC_GetOffsetUnsignedSaturation
  * @param  p_adc Pointer to ADC instance
  * @param  offset_y Offset instance. This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_UNSIGNED_SATURATION_ENABLE
  *         @arg @ref LL_ADC_OFFSET_UNSIGNED_SATURATION_DISABLE
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetUnsignedSaturation(const ADC_TypeDef *p_adc, uint32_t offset_y)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->OFCFGR[0], offset_y);
  return (uint32_t) STM32_READ_BIT(*preg, ADC_OFCFGR_USAT);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Multimode Configuration of ADC hierarchical scope: multimode
  * @{
  */

#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief  Set ADC multimode configuration to operate in independent mode
  *         or multimode (for devices with several ADC instances).
  * @rmtoll
  *  CCR      DUAL           LL_ADC_SetMultimode
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @param  Multimode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_INDEPENDENT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIMULT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_INTERL
  *         @arg @ref LL_ADC_MULTI_DUAL_INJ_SIMULT
  *         @arg @ref LL_ADC_MULTI_DUAL_INJ_ALTERN
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_INT_INJ_SIM
  * @note   If multimode configuration: the selected ADC instance is
  *         either master or slave depending on hardware.
  *         Refer to reference manual.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  */
__STATIC_INLINE void LL_ADC_SetMultimode(ADC_Common_TypeDef *p_adc_common, uint32_t Multimode)
{
  STM32_MODIFY_REG(p_adc_common->CCR, ADCC_CCR_DUAL, Multimode);
}

/**
  * @brief  Get ADC multimode configuration to operate in independent mode
  *         or multimode (for devices with several ADC instances).
  * @rmtoll
  *  CCR      DUAL           LL_ADC_GetMultimode
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @note   If multimode configuration: the selected ADC instance is
  *         either master or slave depending on hardware.
  *         Refer to reference manual.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_INDEPENDENT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIMULT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_INTERL
  *         @arg @ref LL_ADC_MULTI_DUAL_INJ_SIMULT
  *         @arg @ref LL_ADC_MULTI_DUAL_INJ_ALTERN
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_INT_INJ_SIM
  */
__STATIC_INLINE uint32_t LL_ADC_GetMultimode(const ADC_Common_TypeDef *p_adc_common)
{
  return (uint32_t)(STM32_READ_BIT(p_adc_common->CCR, ADCC_CCR_DUAL));
}

/**
  * @brief  Set ADC multimode conversion data transfer: no transfer
  *         or transfer by DMA.
  * @rmtoll
  *  CCR      DAMDF          LL_ADC_GetMultiDMATransfer
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @param  MultiDMATransfer This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_REG_DMA_EACH_ADC
  *         @arg @ref LL_ADC_MULTI_REG_DMA_RES_32_16B
  *         @arg @ref LL_ADC_MULTI_REG_DMA_RES_8B
  * @note   If ADC multimode transfer by DMA is not selected:
  *         each ADC uses its own DMA channel, with its individual
  *         DMA transfer settings.
  *         If ADC multimode transfer by DMA is selected:
  *         One DMA channel is used for both ADC (DMA of ADC master)
  *         Specifies the DMA requests mode:
  *         - Limited mode (One shot mode): DMA transfer requests are stopped
  *           when number of DMA data transfers (number of
  *           ADC conversions) is reached.
  *           This ADC mode is intended to be used with DMA mode non-circular.
  *         - Unlimited mode: DMA transfer requests are unlimited,
  *           whatever number of DMA data transfers (number of
  *           ADC conversions).
  *           This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA requests mode is set to unlimited and DMA is set to
  *         mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *         (overrun flag and interruption if enabled).
  * @note   How to retrieve multimode conversion data:
  *         Whatever multimode transfer by DMA setting: using function
  *         @ref LL_ADC_REG_ReadMultiConversionData32().
  *         If ADC multimode transfer by DMA is selected: conversion data
  *         is a raw data with ADC master and slave concatenated.
  *         A macro is available to get the conversion data of
  *         ADC master or ADC slave: see helper macro
  *         @ref LL_ADC_MULTI_CONV_DATA_MASTER_SLAVE().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled
  *         or enabled without conversion ongoing on group regular.
  */
__STATIC_INLINE void LL_ADC_SetMultiDMATransfer(ADC_Common_TypeDef *p_adc_common, uint32_t MultiDMATransfer)
{
  STM32_MODIFY_REG(p_adc_common->CCR, ADCC_CCR_DAMDF, MultiDMATransfer);
}

/**
  * @brief  Get ADC multimode conversion data transfer: no transfer
  *         or transfer by DMA.
  * @rmtoll
  *  CCR      DAMDF          LL_ADC_GetMultiDMATransfer
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @note   If ADC multimode transfer by DMA is not selected:
  *         each ADC uses its own DMA channel, with its individual
  *         DMA transfer settings.
  *         If ADC multimode transfer by DMA is selected:
  *         One DMA channel is used for both ADC (DMA of ADC master)
  *         Specifies the DMA requests mode:
  *         - Limited mode (One shot mode): DMA transfer requests are stopped
  *           when number of DMA data transfers (number of
  *           ADC conversions) is reached.
  *           This ADC mode is intended to be used with DMA mode non-circular.
  *         - Unlimited mode: DMA transfer requests are unlimited,
  *           whatever number of DMA data transfers (number of
  *           ADC conversions).
  *           This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA requests mode is set to unlimited and DMA is set to
  *         mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *         (overrun flag and interruption if enabled).
  * @note   How to retrieve multimode conversion data:
  *         Whatever multimode transfer by DMA setting: using function
  *         @ref LL_ADC_REG_ReadMultiConversionData32().
  *         If ADC multimode transfer by DMA is selected: conversion data
  *         is a raw data with ADC master and slave concatenated.
  *         A macro is available to get the conversion data of
  *         ADC master or ADC slave: see helper macro
  *         @ref LL_ADC_MULTI_CONV_DATA_MASTER_SLAVE().
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_REG_DMA_EACH_ADC
  *         @arg @ref LL_ADC_MULTI_REG_DMA_RES_32_16B
  *         @arg @ref LL_ADC_MULTI_REG_DMA_RES_8B
  */
__STATIC_INLINE uint32_t LL_ADC_GetMultiDMATransfer(const ADC_Common_TypeDef *p_adc_common)
{
  return (uint32_t)(STM32_READ_BIT(p_adc_common->CCR, ADCC_CCR_DAMDF));
}

/**
  * @brief  Set ADC multimode delay between 2 sampling phases.
  * @rmtoll
  *  CCR      DELAY          LL_ADC_SetMultiTwoSamplingDelay
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @param  MultiTwoSamplingDelay This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_2CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_3CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_10CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_11CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_12CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_13CYCLES
  * @note   The sampling delay range depends on ADC resolution:
  *         - ADC resolution 12 bits can have maximum delay of 12 cycles.
  *         - ADC resolution 10 bits can have maximum delay of 10 cycles.
  *         - ADC resolution  8 bits can have maximum delay of  8 cycles.
  *         - ADC resolution  6 bits can have maximum delay of  6 cycles.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  */
__STATIC_INLINE void LL_ADC_SetMultiTwoSamplingDelay(ADC_Common_TypeDef *p_adc_common, uint32_t MultiTwoSamplingDelay)
{
  STM32_MODIFY_REG(p_adc_common->CCR, ADCC_CCR_DELAY, MultiTwoSamplingDelay);
}

/**
  * @brief  Get ADC multimode delay between 2 sampling phases.
  * @rmtoll
  *  CCR      DELAY          LL_ADC_GetMultiTwoSamplingDelay
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_2CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_3CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_10CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_11CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_12CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_13CYCLES
  */
__STATIC_INLINE uint32_t LL_ADC_GetMultiTwoSamplingDelay(const ADC_Common_TypeDef *p_adc_common)
{
  return (uint32_t)(STM32_READ_BIT(p_adc_common->CCR, ADCC_CCR_DELAY));
}
#endif /* ADC_MULTIMODE_SUPPORT */

/**
  * @}
  */
/** @defgroup ADC_LL_EF_Operation_ADC_Instance Operation on ADC hierarchical scope: ADC instance
  * @{
  */

/**
  * @brief  Put ADC instance in deep power down state.
  * @rmtoll
  *  CR       DEEPPWD        LL_ADC_EnableDeepPowerDown
  * @param  p_adc Pointer to ADC instance
  * @note   In case of ADC calibration necessary: When ADC is in deep-power-down
  *         state, the internal analog calibration is lost. After exiting from
  *         deep power down, calibration must be relaunched or calibration factor
  *         (preliminarily saved) must be set back into calibration register.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  */
__STATIC_INLINE void LL_ADC_EnableDeepPowerDown(ADC_TypeDef *p_adc)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  STM32_MODIFY_REG(p_adc->CR, LL_ADC_CR_BITS_PROPERTY_RS, ADC_CR_DEEPPWD);
}

/**
  * @brief  Disable ADC deep power down mode.
  * @rmtoll
  *  CR       DEEPPWD        LL_ADC_DisableDeepPowerDown
  * @param  p_adc Pointer to ADC instance
  * @note   In case of ADC calibration necessary: When ADC is in deep-power-down
  *         state, the internal analog calibration is lost. After exiting from
  *         deep power down, calibration must be relaunched or calibration factor
  *         (preliminarily saved) must be set back into calibration register.
  * @note   ADC disable deep power down is a part of ADC activation.
  *         ADC activation procedure requires several necessary steps:
  *         refer to description of @ref LL_ADC_Enable().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  */
__STATIC_INLINE void LL_ADC_DisableDeepPowerDown(ADC_TypeDef *p_adc)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  STM32_CLEAR_BIT(p_adc->CR, (ADC_CR_DEEPPWD | LL_ADC_CR_BITS_PROPERTY_RS));
}

/**
  * @brief  Get the selected ADC instance deep power down state.
  * @rmtoll
  *  CR       DEEPPWD        LL_ADC_IsDeepPowerDownEnabled
  * @param  p_adc Pointer to ADC instance
  * @retval 0: deep power down is disabled, 1: deep power down is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDeepPowerDownEnabled(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->CR, ADC_CR_DEEPPWD) == (ADC_CR_DEEPPWD)) ? 1UL : 0UL);
}

/**
  * @brief  Enable ADC instance internal voltage regulator.
  * @rmtoll
  *  CR       ADVREGEN       LL_ADC_EnableInternalRegulator
  * @param  p_adc Pointer to ADC instance
  * @note   On this STM32 series, after ADC internal voltage regulator enable,
  *         a delay for ADC internal voltage regulator stabilization
  *         is required before performing a ADC calibration or ADC enable.
  *         Refer to device datasheet, parameter "tADCVREG_STUP".
  *         Refer to literal @ref LL_ADC_DELAY_INTERNAL_REGUL_STAB_US.
  * @note   ADC enable internal voltage regulator is a part of ADC activation.
  *         ADC activation procedure requires several necessary steps:
  *         refer to description of @ref LL_ADC_Enable().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  */
__STATIC_INLINE void LL_ADC_EnableInternalRegulator(ADC_TypeDef *p_adc)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  STM32_MODIFY_REG(p_adc->CR, LL_ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADVREGEN);
}

/**
  * @brief  Disable ADC internal voltage regulator.
  * @rmtoll
  *  CR       ADVREGEN       LL_ADC_DisableInternalRegulator
  * @param  p_adc Pointer to ADC instance
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  */
__STATIC_INLINE void LL_ADC_DisableInternalRegulator(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->CR, (ADC_CR_ADVREGEN | LL_ADC_CR_BITS_PROPERTY_RS));
}

/**
  * @brief  Get the selected ADC instance internal voltage regulator state.
  * @rmtoll
  *  CR       ADVREGEN       LL_ADC_IsInternalRegulatorEnabled
  * @param  p_adc Pointer to ADC instance
  * @retval 0: internal regulator is disabled, 1: internal regulator is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsInternalRegulatorEnabled(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->CR, ADC_CR_ADVREGEN) == (ADC_CR_ADVREGEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the selected ADC instance.
  * @rmtoll
  *  CR       ADEN           LL_ADC_Enable
  * @param  p_adc Pointer to ADC instance
  * @note   On this STM32 series, after ADC enable, a delay for
  *         ADC internal analog stabilization is required before performing a
  *         ADC conversion start.
  *         Refer to device datasheet, parameter tSTAB.
  * @note   ADC enable is a part of ADC activation.
  *         ADC activation procedure requires several necessary steps:
  *         - RCC to provide ADC bus clock (refer to LL bus driver)
  *         - ADC internal voltage regulator enable (refer to @ref LL_ADC_DisableDeepPowerDown(),
  *           LL_ADC_EnableInternalRegulator())
  *         - RCC to provide ADC kernel clock (refer to LL RCC driver). Can be done at any step.
  *         - ADC enable (this function @ref LL_ADC_Enable())
  *         - Check ADC ready flag (refer to @ref LL_ADC_IsActiveFlag_ADRDY())
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled and ADC internal voltage regulator enabled.
  */
__STATIC_INLINE void LL_ADC_Enable(ADC_TypeDef *p_adc)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  STM32_MODIFY_REG(p_adc->CR, LL_ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADEN);
}

/**
  * @brief  Disable the selected ADC instance.
  * @rmtoll
  *  CR       ADDIS          LL_ADC_Disable
  * @param  p_adc Pointer to ADC instance
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be not disabled. Must be enabled without conversion ongoing
  *         on either groups regular or injected.
  */
__STATIC_INLINE void LL_ADC_Disable(ADC_TypeDef *p_adc)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  STM32_MODIFY_REG(p_adc->CR, LL_ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADDIS);
}

/**
  * @brief  Get the selected ADC instance enable state.
  * @rmtoll
  *  CR       ADEN           LL_ADC_IsEnabled
  * @param  p_adc Pointer to ADC instance
  * @note   ADC enable is a part of ADC activation.
  *         ADC activation procedure requires several necessary steps:
  *         refer to description of @ref LL_ADC_Enable().
  * @retval 0: ADC is disabled, 1: ADC is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabled(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->CR, ADC_CR_ADEN) == (ADC_CR_ADEN)) ? 1UL : 0UL);
}

/**
  * @brief  Get the selected ADC instance disable state.
  * @rmtoll
  *  CR       ADDIS          LL_ADC_IsDisableOngoing
  * @param  p_adc Pointer to ADC instance
  * @retval 0: no ADC disable command ongoing.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDisableOngoing(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->CR, ADC_CR_ADDIS) == (ADC_CR_ADDIS)) ? 1UL : 0UL);
}

/**
  * @brief  Start ADC calibration in the mode single-ended
  *         or differential (for devices with differential mode available).
  * @rmtoll
  *  CR       ADCAL          LL_ADC_StartCalibration\n
  *  CR       ADCALDIF       LL_ADC_StartCalibration\n
  *  CR       ADCALDIF       LL_ADC_StartCalibration
  * @param  p_adc Pointer to ADC instance
  * @param  input_mode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_IN_SINGLE_ENDED
  *         @arg @ref LL_ADC_IN_DIFFERENTIAL
  * @note   On this STM32 series, a minimum number of ADC clock cycles
  *         are required between ADC end of calibration and ADC enable.
  *         Refer to literal @ref LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES.
  * @note   For devices with differential mode available:
  *         Calibration of offset is specific to each of
  *         single-ended and differential modes
  *         (calibration run must be performed for each of these
  *         differential modes, if used afterwards and if the application
  *         requires their calibration).
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  */
__STATIC_INLINE void LL_ADC_StartCalibration(ADC_TypeDef *p_adc, uint32_t input_mode)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  STM32_MODIFY_REG(p_adc->CR,
                   ADC_CR_ADCALDIF | LL_ADC_CR_BITS_PROPERTY_RS,
                   ADC_CR_ADCAL | (input_mode & LL_ADC_SGLDIFF_CAL_START_MASK));
}

/**
  * @brief  Get ADC calibration state.
  * @rmtoll
  *  CR       ADCAL          LL_ADC_IsCalibrationOnGoing
  * @param  p_adc Pointer to ADC instance
  * @retval 0: calibration complete, 1: calibration in progress.
  */
__STATIC_INLINE uint32_t LL_ADC_IsCalibrationOnGoing(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->CR, ADC_CR_ADCAL) == (ADC_CR_ADCAL)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Operation_ADC_Group_Regular Operation on ADC hierarchical scope: group regular
  * @{
  */

/**
  * @brief  Start ADC group regular conversion.
  * @rmtoll
  *  CR       ADSTART        LL_ADC_REG_StartConversion
  * @param  p_adc Pointer to ADC instance
  * @note   On this STM32 series, this function is relevant for both
  *         internal trigger (SW start) and external trigger:
  *         - If ADC trigger has been set to software start, ADC conversion
  *           starts immediately.
  *         - If ADC trigger has been set to external trigger, ADC conversion
  *           will start at next trigger event (on the selected trigger edge)
  *           following the ADC start conversion command.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion ongoing on group regular,
  *         without conversion stop command ongoing on group regular,
  *         without ADC disable command ongoing.
  */
__STATIC_INLINE void LL_ADC_REG_StartConversion(ADC_TypeDef *p_adc)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  STM32_MODIFY_REG(p_adc->CR, LL_ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADSTART);
}

/**
  * @brief  Stop ADC group regular conversion.
  * @rmtoll
  *  CR       ADSTP          LL_ADC_REG_StopConversion
  * @param  p_adc Pointer to ADC instance
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled with conversion ongoing on group regular,
  *         without ADC disable command ongoing.
  */
__STATIC_INLINE void LL_ADC_REG_StopConversion(ADC_TypeDef *p_adc)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  STM32_MODIFY_REG(p_adc->CR,
                   LL_ADC_CR_BITS_PROPERTY_RS,
                   ADC_CR_ADSTP);
}

/**
  * @brief  Get ADC group regular conversion state.
  * @rmtoll
  *  CR       ADSTART        LL_ADC_REG_IsConversionOngoing
  * @param  p_adc Pointer to ADC instance
  * @retval 0: no conversion is ongoing on ADC group regular.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsConversionOngoing(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->CR, ADC_CR_ADSTART) == (ADC_CR_ADSTART)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group regular command of conversion stop state.
  * @rmtoll
  *  CR       ADSTP          LL_ADC_REG_IsStopConversionOngoing
  * @param  p_adc Pointer to ADC instance
  * @retval 0: no command of conversion stop is ongoing on ADC group regular.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsStopConversionOngoing(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->CR, ADC_CR_ADSTP) == (ADC_CR_ADSTP)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group regular conversion data, range fit for all ADC configurations:
  *         all ADC resolutions, features extending data width (oversampling, data shift, ...)
  *         and features changing data sign (offset).
  * @rmtoll
  *  DR       RDATA          LL_ADC_REG_ReadConversionData
  * @param  p_adc Pointer to ADC instance
  * @retval Signed value (can be negative after post-processing computation: offset feature)
  *         between Min_Data=-4194304 (two's complement 0xFFC00000) and Max_Data=+4194303 (0x003FFFFF)
  */
__STATIC_INLINE int32_t LL_ADC_REG_ReadConversionData(const ADC_TypeDef *p_adc)
{
  return (int32_t)((uint32_t)STM32_READ_BIT(p_adc->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for ADC configurations with
  *         all ADC resolutions, features extending data width (oversampling, data shift, ...)
  *         but not features changing data sign (offset).
  * @rmtoll
  *  DR       RDATA          LL_ADC_REG_ReadConversionData32
  * @param  p_adc Pointer to ADC instance
  * @note   To get data handling all ADC configurations, use default function @ref LL_ADC_REG_ReadConversionData().
  * @retval Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_REG_ReadConversionData32(const ADC_TypeDef *p_adc)
{
  return (uint32_t)(STM32_READ_BIT(p_adc->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for data width 12 bits and unsigned.
  * @rmtoll
  *  DR       RDATA          LL_ADC_REG_ReadConversionData12
  * @param  p_adc Pointer to ADC instance
  * @note   To get data handling all ADC configurations, use default function @ref LL_ADC_REG_ReadConversionData().
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
__STATIC_INLINE uint16_t LL_ADC_REG_ReadConversionData12(const ADC_TypeDef *p_adc)
{
  return (uint16_t)(STM32_READ_BIT(p_adc->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for data width 10 bits and unsigned.
  * @rmtoll
  *  DR       RDATA          LL_ADC_REG_ReadConversionData10
  * @param  p_adc Pointer to ADC instance
  * @note   To get data handling all ADC configurations, use default function @ref LL_ADC_REG_ReadConversionData().
  * @retval Value between Min_Data=0x000 and Max_Data=0x3FF
  */
__STATIC_INLINE uint16_t LL_ADC_REG_ReadConversionData10(const ADC_TypeDef *p_adc)
{
  return (uint16_t)(STM32_READ_BIT(p_adc->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for data width 8 bits and unsigned.
  * @rmtoll
  *  DR       RDATA          LL_ADC_REG_ReadConversionData8
  * @param  p_adc Pointer to ADC instance
  * @note   To get data handling all ADC configurations, use default function @ref LL_ADC_REG_ReadConversionData().
  * @retval Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t LL_ADC_REG_ReadConversionData8(const ADC_TypeDef *p_adc)
{
  return (uint8_t)(STM32_READ_BIT(p_adc->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for data width 6 bits and unsigned.
  * @rmtoll
  *  DR       RDATA          LL_ADC_REG_ReadConversionData6
  * @param  p_adc Pointer to ADC instance
  * @note   To get data handling all ADC configurations, use default function @ref LL_ADC_REG_ReadConversionData().
  * @retval Value between Min_Data=0x00 and Max_Data=0x3F
  */
__STATIC_INLINE uint8_t LL_ADC_REG_ReadConversionData6(const ADC_TypeDef *p_adc)
{
  return (uint8_t)(STM32_READ_BIT(p_adc->DR, ADC_DR_RDATA));
}

#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief  Get ADC multimode conversion data of ADC master, ADC slave
  *         or raw data with ADC master and slave concatenated.
  * @rmtoll
  *  CDR      RDATA_MST      LL_ADC_REG_ReadMultiConversionData32\n
  *  CDR      RDATA_SLV      LL_ADC_REG_ReadMultiConversionData32
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @param  ConversionData This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_MASTER       (1)
  *         @arg @ref LL_ADC_MULTI_SLAVE        (1)
  *         @arg @ref LL_ADC_MULTI_MASTER_SLAVE
  *
  *         (1) Parameter available only if ADC multimode group regular data format with packing option on 32 bits
  *             (refer to @ref LL_ADC_MULTI_REG_DMA_RES_32_16B).
  * @note   This function is relevant only for ADC multimode group regular data format with packing: each ADC conversion
  *         data concatenated in a single register (refer to @ref LL_ADC_MULTI_REG_DMA_RES_32_16B,
  *         @ref LL_ADC_MULTI_REG_DMA_RES_8B).
  * @note   Each ADC conversion data width is limited to 8 or 16 bits depending on data packing setting.
  *         If expected data width is wider (this can be the case with features extending data width (oversampling,
  *         data shift,...), others services must be used:
  *         - function "LL_ADC_REG_ReadConversionData()" for each ADC instance part of multimode.
  *         - multimode functions with data transfer by DMA.
  * @note   Returned value is unsigned, due to concatenation of multiple data.
  *         In case of signed data expected (with features changing data sign: offset),
  *         use function "LL_ADC_REG_ReadConversionData()" for each ADC instance part of multimode.
  * @note   If raw data with ADC master and slave concatenated is retrieved,
  *         a macro is available to get the conversion data of
  *         ADC master or ADC slave: see helper macro
  *         @ref LL_ADC_MULTI_CONV_DATA_MASTER_SLAVE().
  *         (however this macro is mainly intended for multimode
  *         transfer by DMA, because this function can do the same
  *         by getting multimode conversion data of ADC master or ADC slave
  *         separately).
  * @retval Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_REG_ReadMultiConversionData32(const ADC_Common_TypeDef *p_adc_common,
                                                              uint32_t ConversionData)
{
  return (uint32_t)(STM32_READ_BIT(p_adc_common->CDR, ConversionData) >> (STM32_POSITION_VAL(ConversionData) & 0x1FUL));
}
#endif /* ADC_MULTIMODE_SUPPORT */

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Operation_ADC_Group_Injected Operation on ADC hierarchical scope: group injected
  * @{
  */

/**
  * @brief  Start ADC group injected conversion.
  * @rmtoll
  *  CR       JADSTART       LL_ADC_INJ_StartConversion
  * @param  p_adc Pointer to ADC instance
  * @note   On this STM32 series, this function is relevant for both
  *         internal trigger (SW start) and external trigger:
  *         - If ADC trigger has been set to software start, ADC conversion
  *           starts immediately.
  *         - If ADC trigger has been set to external trigger, ADC conversion
  *           will start at next trigger event (on the selected trigger edge)
  *           following the ADC start conversion command.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion ongoing on group injected,
  *         without conversion stop command ongoing on group injected,
  *         without ADC disable command ongoing.
  */
__STATIC_INLINE void LL_ADC_INJ_StartConversion(ADC_TypeDef *p_adc)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  STM32_MODIFY_REG(p_adc->CR, LL_ADC_CR_BITS_PROPERTY_RS, ADC_CR_JADSTART);
}

/**
  * @brief  Stop ADC group injected conversion.
  * @rmtoll
  *  CR       JADSTP         LL_ADC_INJ_StopConversion
  * @param  p_adc Pointer to ADC instance
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled with conversion ongoing on group injected,
  *         without ADC disable command ongoing.
  */
__STATIC_INLINE void LL_ADC_INJ_StopConversion(ADC_TypeDef *p_adc)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  STM32_MODIFY_REG(p_adc->CR, LL_ADC_CR_BITS_PROPERTY_RS, ADC_CR_JADSTP);
}

/**
  * @brief  Get ADC group injected conversion state.
  * @rmtoll
  *  CR       JADSTART       LL_ADC_INJ_IsConversionOngoing
  * @param  p_adc Pointer to ADC instance
  * @retval 0: no conversion is ongoing on ADC group injected.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsConversionOngoing(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->CR, ADC_CR_JADSTART) == (ADC_CR_JADSTART)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group injected command of conversion stop state.
  * @rmtoll
  *  CR       JADSTP         LL_ADC_INJ_IsStopConversionOngoing
  * @param  p_adc Pointer to ADC instance
  * @retval 0: no command of conversion stop is ongoing on ADC group injected.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsStopConversionOngoing(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->CR, ADC_CR_JADSTP) == (ADC_CR_JADSTP)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group injected conversion data, range fit for all ADC configurations:
  *         all ADC resolutions, features extending data width (oversampling, data shift, ...)
  *         and features changing data sign (offset).
  * @rmtoll
  *  JDR1     JDATA          LL_ADC_INJ_ReadConversionDataRank\n
  *  JDR2     JDATA          LL_ADC_INJ_ReadConversionDataRank\n
  *  JDR3     JDATA          LL_ADC_INJ_ReadConversionDataRank\n
  *  JDR4     JDATA          LL_ADC_INJ_ReadConversionDataRank
  * @param  p_adc Pointer to ADC instance
  * @param  rank ADC group injected sequencer rank.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Signed value (can be negative after post-processing computation: offset feature)
  *         between Min_Data=-2147483648 (two's complement 0x80000000) and Max_Data=+2147483647 (0x7FFFFFFF)
  */
__STATIC_INLINE int32_t LL_ADC_INJ_ReadConversionDataRank(const ADC_TypeDef *p_adc, uint32_t rank)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->JDR[0], ((rank & LL_ADC_INJ_JDRX_REGOFFSET_MASK)
                                                                    >> LL_ADC_JDRX_REGOFFSET_POS));

  return (int32_t)((uint32_t)STM32_READ_BIT(*preg, ADC_JDR_JDATA));
}

/**
  * @brief  Get ADC group injected conversion data, range fit for ADC configurations with
  *         all ADC resolutions, features extending data width (oversampling, data shift, ...)
  *         but not features changing data sign (offset).
  * @rmtoll
  *  JDR1     JDATA          LL_ADC_INJ_ReadConversionData32Rank\n
  *  JDR2     JDATA          LL_ADC_INJ_ReadConversionData32Rank\n
  *  JDR3     JDATA          LL_ADC_INJ_ReadConversionData32Rank\n
  *  JDR4     JDATA          LL_ADC_INJ_ReadConversionData32Rank
  * @param  p_adc Pointer to ADC instance
  * @param  rank ADC group injected sequencer rank.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @note   To get data handling all ADC configurations, use default function @ref LL_ADC_INJ_ReadConversionDataRank().
  * @retval Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_ReadConversionData32Rank(const ADC_TypeDef *p_adc, uint32_t rank)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->JDR[0], ((rank & LL_ADC_INJ_JDRX_REGOFFSET_MASK)
                                                                    >> LL_ADC_JDRX_REGOFFSET_POS));

  return (uint32_t)STM32_READ_BIT(*preg, ADC_JDR_JDATA);
}

/**
  * @brief  Get ADC group injected conversion data, range fit for data width 12 bits and unsigned.
  * @rmtoll
  *  JDR1     JDATA          LL_ADC_INJ_ReadConversionData12Rank\n
  *  JDR2     JDATA          LL_ADC_INJ_ReadConversionData12Rank\n
  *  JDR3     JDATA          LL_ADC_INJ_ReadConversionData12Rank\n
  *  JDR4     JDATA          LL_ADC_INJ_ReadConversionData12Rank
  * @param  p_adc Pointer to ADC instance
  * @param  rank ADC group injected sequencer rank.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @note   To get data handling all ADC configurations, use default function @ref LL_ADC_INJ_ReadConversionDataRank().
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
__STATIC_INLINE uint16_t LL_ADC_INJ_ReadConversionData12Rank(const ADC_TypeDef *p_adc, uint32_t rank)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->JDR[0], ((rank & LL_ADC_INJ_JDRX_REGOFFSET_MASK)
                                                                    >> LL_ADC_JDRX_REGOFFSET_POS));

  return (uint16_t)STM32_READ_BIT(*preg, ADC_JDR_JDATA);
}

/**
  * @brief  Get ADC group injected conversion data, range fit for data width 10 bits and unsigned.
  * @rmtoll
  *  JDR1     JDATA          LL_ADC_INJ_ReadConversionData10Rank\n
  *  JDR2     JDATA          LL_ADC_INJ_ReadConversionData10Rank\n
  *  JDR3     JDATA          LL_ADC_INJ_ReadConversionData10Rank\n
  *  JDR4     JDATA          LL_ADC_INJ_ReadConversionData10Rank
  * @param  p_adc Pointer to ADC instance
  * @param  rank ADC group injected sequencer rank.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @note   To get data handling all ADC configurations, use default function @ref LL_ADC_INJ_ReadConversionDataRank().
  * @retval Value between Min_Data=0x000 and Max_Data=0x3FF
  */
__STATIC_INLINE uint16_t LL_ADC_INJ_ReadConversionData10Rank(const ADC_TypeDef *p_adc, uint32_t rank)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->JDR[0], ((rank & LL_ADC_INJ_JDRX_REGOFFSET_MASK)
                                                                    >> LL_ADC_JDRX_REGOFFSET_POS));

  return (uint16_t)STM32_READ_BIT(*preg, ADC_JDR_JDATA);
}

/**
  * @brief  Get ADC group injected conversion data, range fit for data width 8 bits and unsigned.
  * @rmtoll
  *  JDR1     JDATA          LL_ADC_INJ_ReadConversionData8Rank\n
  *  JDR2     JDATA          LL_ADC_INJ_ReadConversionData8Rank\n
  *  JDR3     JDATA          LL_ADC_INJ_ReadConversionData8Rank\n
  *  JDR4     JDATA          LL_ADC_INJ_ReadConversionData8Rank
  * @param  p_adc Pointer to ADC instance
  * @param  rank ADC group injected sequencer rank.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @note   To get data handling all ADC configurations, use default function @ref LL_ADC_INJ_ReadConversionDataRank().
  * @retval Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t LL_ADC_INJ_ReadConversionData8Rank(const ADC_TypeDef *p_adc, uint32_t rank)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->JDR[0], ((rank & LL_ADC_INJ_JDRX_REGOFFSET_MASK)
                                                                    >> LL_ADC_JDRX_REGOFFSET_POS));

  return (uint8_t)STM32_READ_BIT(*preg, ADC_JDR_JDATA);
}

/**
  * @brief  Get ADC group injected conversion data, range fit for data width 6 bits and unsigned.
  * @rmtoll
  *  JDR1     JDATA          LL_ADC_INJ_ReadConversionData6Rank\n
  *  JDR2     JDATA          LL_ADC_INJ_ReadConversionData6Rank\n
  *  JDR3     JDATA          LL_ADC_INJ_ReadConversionData6Rank\n
  *  JDR4     JDATA          LL_ADC_INJ_ReadConversionData6Rank
  * @param  p_adc Pointer to ADC instance
  * @param  rank ADC group injected sequencer rank.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @note   To get data handling all ADC configurations, use default function @ref LL_ADC_INJ_ReadConversionDataRank().
  * @retval Value between Min_Data=0x00 and Max_Data=0x3F
  */
__STATIC_INLINE uint8_t LL_ADC_INJ_ReadConversionData6Rank(const ADC_TypeDef *p_adc, uint32_t rank)
{
  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->JDR[0], ((rank & LL_ADC_INJ_JDRX_REGOFFSET_MASK)
                                                                    >> LL_ADC_JDRX_REGOFFSET_POS));

  return (uint8_t)STM32_READ_BIT(*preg, ADC_JDR_JDATA);
}

/**
  * @brief  Get ADC group injected oversampling intermediate accumulated data count.
  * @rmtoll
  *  JOVSCR1  JOVSC1         LL_ADC_INJ_ReadOVSIntermAccCount\n
  *  JOVSCR1  JOVSC2         LL_ADC_INJ_ReadOVSIntermAccCount\n
  *  JOVSCR2  JOVSC3         LL_ADC_INJ_ReadOVSIntermAccCount\n
  *  JOVSCR2  JOVSC4         LL_ADC_INJ_ReadOVSIntermAccCount
  * @param  p_adc Pointer to ADC instance
  * @param  rank ADC group injected sequencer rank.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @note   Prerequisite: parallel injected oversampling and oversampling intermediate accumulated
  *         must be enabled, refer to @ref LL_ADC_SetOverSamplingInjIntermAcc().
  * @retval Value between 1 to 1024 (maximum corresponding to oversampling ratio)
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_ReadOVSIntermAccCount(const ADC_TypeDef *p_adc, uint32_t rank)
{
  uint32_t interm_acc_count;

  const __IO uint32_t *preg = LL_ADC_PTR_REG_OFFSET(p_adc->JOVSCR1, ((rank & LL_ADC_INJ_JDRX_REGOFFSET_MASK)
                                                                     >> LL_ADC_JDRX_REGOFFSET_POS) / 2U);

  if (((rank >> LL_ADC_JDRX_REGOFFSET_POS) & 1UL) == 0UL)
  {
    /* LL_ADC_INJ_RANK_1 or LL_ADC_INJ_RANK_3 */
    interm_acc_count = ((uint32_t)STM32_READ_BIT(*preg, ADC_JOVSCR1_JOVSC1)) >> ADC_JOVSCR1_JOVSC1_Pos;
  }
  else
  {
    /* LL_ADC_INJ_RANK_2 or LL_ADC_INJ_RANK_4 */
    interm_acc_count = ((uint32_t)STM32_READ_BIT(*preg, ADC_JOVSCR1_JOVSC2)) >> ADC_JOVSCR1_JOVSC2_Pos;
  }

  return interm_acc_count;
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_FLAG_Management ADC flag management
  * @{
  */

/**
  * @brief  Get ADC flag.
  * @rmtoll
  *  ISR      ADRDY          LL_ADC_IsActiveFlag\n
  *  ISR      EOC            LL_ADC_IsActiveFlag\n
  *  ISR      EOS            LL_ADC_IsActiveFlag\n
  *  ISR      OVR            LL_ADC_IsActiveFlag\n
  *  ISR      EOSMP          LL_ADC_IsActiveFlag\n
  *  ISR      JEOC           LL_ADC_IsActiveFlag\n
  *  ISR      JEOS           LL_ADC_IsActiveFlag\n
  *  ISR      JQOVF          LL_ADC_IsActiveMFlag\n
  *  ISR      AWD1           LL_ADC_IsActiveFlag\n
  *  ISR      AWD2           LL_ADC_IsActiveFlag\n
  *  ISR      AWD3           LL_ADC_IsActiveFlag\n
  *  ISR      LDORDY         LL_ADC_IsActiveFlag
  * @param  p_adc Pointer to ADC instance
  * @param  flag This parameter can one of the following values:
  *         @arg @ref LL_ADC_FLAG_ADRDY
  *         @arg @ref LL_ADC_FLAG_EOC
  *         @arg @ref LL_ADC_FLAG_EOS
  *         @arg @ref LL_ADC_FLAG_OVR
  *         @arg @ref LL_ADC_FLAG_EOSMP
  *         @arg @ref LL_ADC_FLAG_JEOC
  *         @arg @ref LL_ADC_FLAG_JEOS
  *         @arg @ref LL_ADC_FLAG_JQOVF
  *         @arg @ref LL_ADC_FLAG_AWD1
  *         @arg @ref LL_ADC_FLAG_AWD2
  *         @arg @ref LL_ADC_FLAG_AWD3
  *         @arg @ref LL_ADC_FLAG_LDORDY
  * @note   Generic function with flag selected as parameter.
  *         Optimized functions for each flag are available.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag(const ADC_TypeDef *p_adc, uint32_t flag)
{
  return ((STM32_READ_BIT(p_adc->ISR, flag) == (flag)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC ready.
  * @rmtoll
  *  ISR      ADRDY          LL_ADC_IsActiveFlag_ADRDY
  * @param  p_adc Pointer to ADC instance
  * @note   ADC ready flag must be checked to ensure ADC activation is effective.
  *         ADC activation procedure requires several necessary steps:
  *         refer to description of @ref LL_ADC_Enable().
  * @note   ADC ready flag is latched at level 1: in case of ADC activation procedure new
  *         iteration or kernel clock update, it must be cleared before new check.
  *         Refer to @ref LL_ADC_IsActiveFlag_ADRDY().
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_ADRDY(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_ADRDY) == (LL_ADC_FLAG_ADRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular end of unitary conversion.
  * @rmtoll
  *  ISR      EOC            LL_ADC_IsActiveFlag_EOC
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOC(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_EOC) == (LL_ADC_FLAG_EOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular end of sequence conversions.
  * @rmtoll
  *  ISR      EOS            LL_ADC_IsActiveFlag_EOS
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOS(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_EOS) == (LL_ADC_FLAG_EOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular overrun.
  * @rmtoll
  *  ISR      OVR            LL_ADC_IsActiveFlag_OVR
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_OVR(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_OVR) == (LL_ADC_FLAG_OVR)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular end of sampling phase.
  * @rmtoll
  *  ISR      EOSMP          LL_ADC_IsActiveFlag_EOSMP
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOSMP(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_EOSMP) == (LL_ADC_FLAG_EOSMP)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group injected end of unitary conversion.
  * @rmtoll
  *  ISR      JEOC           LL_ADC_IsActiveFlag_JEOC
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JEOC(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_JEOC) == (LL_ADC_FLAG_JEOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group injected end of sequence conversions.
  * @rmtoll
  *  ISR      JEOS           LL_ADC_IsActiveFlag_JEOS
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JEOS(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_JEOS) == (LL_ADC_FLAG_JEOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group injected contexts queue overflow.
  * @rmtoll
  *  ISR      JQOVF          LL_ADC_IsActiveFlag_JQOVF
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JQOVF(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_JQOVF) == (LL_ADC_FLAG_JQOVF)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC analog watchdog 1 flag.
  * @rmtoll
  *  ISR      AWD1           LL_ADC_IsActiveFlag_AWD1
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD1(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_AWD1) == (LL_ADC_FLAG_AWD1)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC analog watchdog 2 flag.
  * @rmtoll
  *  ISR      AWD2           LL_ADC_IsActiveFlag_AWD2
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD2(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_AWD2) == (LL_ADC_FLAG_AWD2)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC analog watchdog 3 flag.
  * @rmtoll
  *  ISR      AWD3           LL_ADC_IsActiveFlag_AWD3
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD3(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_AWD3) == (LL_ADC_FLAG_AWD3)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC internal voltage regulator (LDO) ready.
  * @rmtoll
  *  ISR      LDORDY         LL_ADC_IsActiveFlag_LDORDY
  * @param  p_adc Pointer to ADC instance
  * @note   On this STM32 series, this flag indicates LDO current state (not latched as other flags,
  *         no clear flag function)
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_LDORDY(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->ISR, LL_ADC_FLAG_LDORDY) == (LL_ADC_FLAG_LDORDY)) ? 1UL : 0UL);
}


/**
  * @brief  Clear ADC flag.
  * @rmtoll
  *  ISR      ADRDY          LL_ADC_ClearFlag\n
  *  ISR      EOC            LL_ADC_ClearFlag\n
  *  ISR      EOS            LL_ADC_ClearFlag\n
  *  ISR      OVR            LL_ADC_ClearFlag\n
  *  ISR      EOSMP          LL_ADC_ClearFlag\n
  *  ISR      JEOC           LL_ADC_ClearFlag\n
  *  ISR      JEOS           LL_ADC_ClearFlag\n
  *  ISR      JQOVF          LL_ADC_ClearFlag\n
  *  ISR      AWD1           LL_ADC_ClearFlag\n
  *  ISR      AWD2           LL_ADC_ClearFlag\n
  *  ISR      AWD3           LL_ADC_ClearFlag\n
  *  ISR      LDORDY         LL_ADC_ClearFlag
  * @param  p_adc Pointer to ADC instance
  * @param  flag This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_FLAG_ADRDY
  *         @arg @ref LL_ADC_FLAG_EOC
  *         @arg @ref LL_ADC_FLAG_EOS
  *         @arg @ref LL_ADC_FLAG_OVR
  *         @arg @ref LL_ADC_FLAG_EOSMP
  *         @arg @ref LL_ADC_FLAG_JEOC
  *         @arg @ref LL_ADC_FLAG_JEOS
  *         @arg @ref LL_ADC_FLAG_JQOVF
  *         @arg @ref LL_ADC_FLAG_AWD1
  *         @arg @ref LL_ADC_FLAG_AWD2
  *         @arg @ref LL_ADC_FLAG_AWD3
  *         @arg @ref LL_ADC_FLAG_LDORDY
  *         @arg @ref LL_ADC_FLAG_ALL
  * @note   Generic function with flag selected as parameter.
  *         Optimized functions for each flag are available.
  */
__STATIC_INLINE void LL_ADC_ClearFlag(ADC_TypeDef *p_adc, uint32_t flag)
{
  STM32_WRITE_REG(p_adc->ISR, flag);
}

/**
  * @brief  Clear flag ADC ready.
  * @rmtoll
  *  ISR      ADRDY          LL_ADC_ClearFlag_ADRDY
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_ADRDY(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_ADRDY);
}

/**
  * @brief  Clear flag ADC group regular end of unitary conversion.
  * @rmtoll
  *  ISR      EOC            LL_ADC_ClearFlag_EOC
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOC(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_EOC);
}

/**
  * @brief  Clear flag ADC group regular end of sequence conversions.
  * @rmtoll
  *  ISR      EOS            LL_ADC_ClearFlag_EOS
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOS(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_EOS);
}

/**
  * @brief  Clear flag ADC group regular overrun.
  * @rmtoll
  *  ISR      OVR            LL_ADC_ClearFlag_OVR
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_OVR(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_OVR);
}

/**
  * @brief  Clear flag ADC group regular end of sampling phase.
  * @rmtoll
  *  ISR      EOSMP          LL_ADC_ClearFlag_EOSMP
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOSMP(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_EOSMP);
}

/**
  * @brief  Clear flag ADC group injected end of unitary conversion.
  * @rmtoll
  *  ISR      JEOC           LL_ADC_ClearFlag_JEOC
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JEOC(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_JEOC);
}

/**
  * @brief  Clear flag ADC group injected end of sequence conversions.
  * @rmtoll
  *  ISR      JEOS           LL_ADC_ClearFlag_JEOS
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JEOS(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_JEOS);
}

/**
  * @brief  Clear flag ADC group injected contexts queue overflow.
  * @rmtoll
  *  ISR      JQOVF          LL_ADC_ClearFlag_JQOVF
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JQOVF(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_JQOVF);
}

/**
  * @brief  Clear flag ADC analog watchdog 1.
  * @rmtoll
  *  ISR      AWD1           LL_ADC_ClearFlag_AWD1
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD1(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_AWD1);
}

/**
  * @brief  Clear flag ADC analog watchdog 2 out of window event.
  * @rmtoll
  *  ISR      AWD2           LL_ADC_ClearFlag_AWD2
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD2(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_AWD2);
}

/**
  * @brief  Clear flag ADC analog watchdog 3 out of window event.
  * @rmtoll
  *  ISR      AWD3           LL_ADC_ClearFlag_AWD3
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD3(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_AWD3);
}

/**
  * @brief  Clear flag ADC internal voltage regulator (LDO) ready.
  * @rmtoll
  *  ISR      LDORDY         LL_ADC_ClearFlag_LDORDY
  * @param  p_adc Pointer to ADC instance
  * @note   On this STM32 series, this flag indicates LDO current state (not latched as other flags,
  *         no clear flag function)
  */
__STATIC_INLINE void LL_ADC_ClearFlag_LDORDY(ADC_TypeDef *p_adc)
{
  STM32_WRITE_REG(p_adc->ISR, LL_ADC_FLAG_LDORDY);
}

#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief  Get flag multimode ADC ready of the ADC master.
  * @rmtoll
  *  CSR      ADRDY_MST      LL_ADC_IsActiveFlag_MST_ADRDY
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_ADRDY(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_ADRDY_MST) == (LL_ADC_FLAG_ADRDY_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC ready of the ADC slave.
  * @rmtoll
  *  CSR      ADRDY_SLV      LL_ADC_IsActiveFlag_SLV_ADRDY
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_ADRDY(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_ADRDY_SLV) == (LL_ADC_FLAG_ADRDY_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group regular end of unitary conversion of the ADC master.
  * @rmtoll
  *  CSR      EOC_MST        LL_ADC_IsActiveFlag_MST_EOC
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_EOC(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_EOC_MST) == (LL_ADC_FLAG_EOC_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group regular end of unitary conversion of the ADC slave.
  * @rmtoll
  *  CSR      EOC_SLV        LL_ADC_IsActiveFlag_SLV_EOC
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_EOC(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_EOC_SLV) == (LL_ADC_FLAG_EOC_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group regular end of sequence conversions of the ADC master.
  * @rmtoll
  *  CSR      EOS_MST        LL_ADC_IsActiveFlag_MST_EOS
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_EOS(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_EOS_MST) == (LL_ADC_FLAG_EOS_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group regular end of sequence conversions of the ADC slave.
  * @rmtoll
  *  CSR      EOS_SLV        LL_ADC_IsActiveFlag_SLV_EOS
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_EOS(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_EOS_SLV) == (LL_ADC_FLAG_EOS_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group regular overrun of the ADC master.
  * @rmtoll
  *  CSR      OVR_MST        LL_ADC_IsActiveFlag_MST_OVR
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_OVR(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_OVR_MST) == (LL_ADC_FLAG_OVR_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group regular overrun of the ADC slave.
  * @rmtoll
  *  CSR      OVR_SLV        LL_ADC_IsActiveFlag_SLV_OVR
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_OVR(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_OVR_SLV) == (LL_ADC_FLAG_OVR_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group regular end of sampling of the ADC master.
  * @rmtoll
  *  CSR      EOSMP_MST      LL_ADC_IsActiveFlag_MST_EOSMP
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_EOSMP(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_EOSMP_MST) == (LL_ADC_FLAG_EOSMP_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group regular end of sampling of the ADC slave.
  * @rmtoll
  *  CSR      EOSMP_SLV      LL_ADC_IsActiveFlag_SLV_EOSMP
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_EOSMP(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_EOSMP_SLV) == (LL_ADC_FLAG_EOSMP_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group injected end of unitary conversion of the ADC master.
  * @rmtoll
  *  CSR      JEOC_MST       LL_ADC_IsActiveFlag_MST_JEOC
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_JEOC(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_JEOC_MST) == (LL_ADC_FLAG_JEOC_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group injected end of unitary conversion of the ADC slave.
  * @rmtoll
  *  CSR      JEOC_SLV       LL_ADC_IsActiveFlag_SLV_JEOC
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_JEOC(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_JEOC_SLV) == (LL_ADC_FLAG_JEOC_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group injected end of sequence conversions of the ADC master.
  * @rmtoll
  *  CSR      JEOS_MST       LL_ADC_IsActiveFlag_MST_JEOS
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_JEOS(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_JEOS_MST) == (LL_ADC_FLAG_JEOS_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group injected end of sequence conversions of the ADC slave.
  * @rmtoll
  *  CSR      JEOS_SLV       LL_ADC_IsActiveFlag_SLV_JEOS
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_JEOS(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_JEOS_SLV) == (LL_ADC_FLAG_JEOS_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group injected context queue overflow of the ADC master.
  * @rmtoll
  *  CSR      JQOVF_MST      LL_ADC_IsActiveFlag_MST_JQOVF
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_JQOVF(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_JQOVF_MST) == (LL_ADC_FLAG_JQOVF_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC group injected context queue overflow of the ADC slave.
  * @rmtoll
  *  CSR      JQOVF_SLV      LL_ADC_IsActiveFlag_SLV_JQOVF
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_JQOVF(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_JQOVF_SLV) == (LL_ADC_FLAG_JQOVF_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC analog watchdog 1 of the ADC master.
  * @rmtoll
  *  CSR      AWD1_MST       LL_ADC_IsActiveFlag_MST_AWD1
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_AWD1(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_AWD1_MST) == (LL_ADC_FLAG_AWD1_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode analog watchdog 1 of the ADC slave.
  * @rmtoll
  *  CSR      AWD1_SLV       LL_ADC_IsActiveFlag_SLV_AWD1
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_AWD1(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_AWD1_SLV) == (LL_ADC_FLAG_AWD1_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC analog watchdog 2 of the ADC master.
  * @rmtoll
  *  CSR      AWD2_MST       LL_ADC_IsActiveFlag_MST_AWD2
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_AWD2(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_AWD2_MST) == (LL_ADC_FLAG_AWD2_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC analog watchdog 2 of the ADC slave.
  * @rmtoll
  *  CSR      AWD2_SLV       LL_ADC_IsActiveFlag_SLV_AWD2
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_AWD2(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_AWD2_SLV) == (LL_ADC_FLAG_AWD2_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC analog watchdog 3 of the ADC master.
  * @rmtoll
  *  CSR      AWD3_MST       LL_ADC_IsActiveFlag_MST_AWD3
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_AWD3(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_AWD3_MST) == (LL_ADC_FLAG_AWD3_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC analog watchdog 3 of the ADC slave.
  * @rmtoll
  *  CSR      AWD3_SLV       LL_ADC_IsActiveFlag_SLV_AWD3
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_AWD3(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_AWD3_SLV) == (LL_ADC_FLAG_AWD3_SLV)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC internal voltage regulator (LDO) ready of the ADC master.
  * @rmtoll
  *  CSR      LDORDY_MST     LL_ADC_IsActiveFlag_MST_LDORDY
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_LDORDY(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_LDORDY_MST) == (LL_ADC_FLAG_LDORDY_MST)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag multimode ADC internal voltage regulator (LDO) ready of the ADC slave.
  * @rmtoll
  *  CSR      LDORDY_SLV     LL_ADC_IsActiveFlag_SLV_LDORDY
  * @param  p_adc_common Pointer to ADC common instance
  *         (can be set directly from CMSIS definition ADCxy_COMMON or using macro ADC_COMMON_INSTANCE())
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_LDORDY(const ADC_Common_TypeDef *p_adc_common)
{
  return ((STM32_READ_BIT(p_adc_common->CSR, LL_ADC_FLAG_LDORDY_SLV) == (LL_ADC_FLAG_LDORDY_SLV)) ? 1UL : 0UL);
}
#endif /* ADC_MULTIMODE_SUPPORT */

/**
  * @}
  */

/** @defgroup ADC_LL_EF_IT_Management ADC IT management
  * @{
  */

/**
  * @brief  Enable ADC interruption.
  * @rmtoll
  *  IER      ADRDY          LL_ADC_EnableIT\n
  *  IER      EOC            LL_ADC_EnableIT\n
  *  IER      EOS            LL_ADC_EnableIT\n
  *  IER      OVR            LL_ADC_EnableIT\n
  *  IER      EOSMP          LL_ADC_EnableIT\n
  *  IER      JEOC           LL_ADC_EnableIT\n
  *  IER      JEOS           LL_ADC_EnableIT\n
  *  IER      JQOVF          LL_ADC_EnableIT\n
  *  IER      AWD1           LL_ADC_EnableIT\n
  *  IER      AWD2           LL_ADC_EnableIT\n
  *  IER      AWD3           LL_ADC_EnableIT\n
  *  IER      LDORDY         LL_ADC_EnableIT
  * @param  p_adc Pointer to ADC instance
  * @param  it   This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_IT_ADRDY
  *         @arg @ref LL_ADC_IT_EOC
  *         @arg @ref LL_ADC_IT_EOS
  *         @arg @ref LL_ADC_IT_OVR
  *         @arg @ref LL_ADC_IT_EOSMP
  *         @arg @ref LL_ADC_IT_JEOC
  *         @arg @ref LL_ADC_IT_JEOS
  *         @arg @ref LL_ADC_IT_JQOVF
  *         @arg @ref LL_ADC_IT_AWD1
  *         @arg @ref LL_ADC_IT_AWD2
  *         @arg @ref LL_ADC_IT_AWD3
  *         @arg @ref LL_ADC_IT_LDORDY
  *         @arg @ref LL_ADC_IT_ALL
  * @note   Generic function with flag selected as parameter.
  *         Optimized functions for each flag are available.
  */
__STATIC_INLINE void LL_ADC_EnableIT(ADC_TypeDef *p_adc, uint32_t it)
{
  STM32_SET_BIT(p_adc->IER, it);
}

/**
  * @brief  Enable ADC ready.
  * @rmtoll
  *  IER      ADRDYIE        LL_ADC_EnableIT_ADRDY
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_ADRDY(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_ADRDY);
}

/**
  * @brief  Enable interruption ADC group regular end of unitary conversion.
  * @rmtoll
  *  IER      EOCIE          LL_ADC_EnableIT_EOC
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOC(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_EOC);
}

/**
  * @brief  Enable interruption ADC group regular end of sequence conversions.
  * @rmtoll
  *  IER      EOSIE          LL_ADC_EnableIT_EOS
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOS(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_EOS);
}

/**
  * @brief  Enable ADC group regular interruption overrun.
  * @rmtoll
  *  IER      OVRIE          LL_ADC_EnableIT_OVR
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_OVR(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_OVR);
}

/**
  * @brief  Enable interruption ADC group regular end of sampling.
  * @rmtoll
  *  IER      EOSMPIE        LL_ADC_EnableIT_EOSMP
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOSMP(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_EOSMP);
}

/**
  * @brief  Enable interruption ADC group injected end of unitary conversion.
  * @rmtoll
  *  IER      JEOCIE         LL_ADC_EnableIT_JEOC
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_JEOC(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_JEOC);
}

/**
  * @brief  Enable interruption ADC group injected end of sequence conversions.
  * @rmtoll
  *  IER      JEOSIE         LL_ADC_EnableIT_JEOS
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_JEOS(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_JEOS);
}

/**
  * @brief  Enable interruption ADC group injected context queue overflow.
  * @rmtoll
  *  IER      JQOVFIE        LL_ADC_EnableIT_JQOVF
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_JQOVF(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_JQOVF);
}

/**
  * @brief  Enable interruption ADC analog watchdog 1.
  * @rmtoll
  *  IER      AWD1IE         LL_ADC_EnableIT_AWD1
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD1(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_AWD1);
}

/**
  * @brief  Enable interruption ADC analog watchdog 2.
  * @rmtoll
  *  IER      AWD2IE         LL_ADC_EnableIT_AWD2
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD2(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_AWD2);
}

/**
  * @brief  Enable interruption ADC analog watchdog 3.
  * @rmtoll
  *  IER      AWD3IE         LL_ADC_EnableIT_AWD3
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD3(ADC_TypeDef *p_adc)
{
  STM32_SET_BIT(p_adc->IER, LL_ADC_IT_AWD3);
}

/**
  * @brief  Disable ADC interruption.
  * @rmtoll
  *  IER      ADRDY          LL_ADC_DisableIT\n
  *  IER      EOC            LL_ADC_DisableIT\n
  *  IER      EOS            LL_ADC_DisableIT\n
  *  IER      OVR            LL_ADC_DisableIT\n
  *  IER      EOSMP          LL_ADC_DisableIT\n
  *  IER      JEOC           LL_ADC_DisableIT\n
  *  IER      JEOS           LL_ADC_DisableIT\n
  *  IER      JQOVF          LL_ADC_DisableIT\n
  *  IER      AWD1           LL_ADC_DisableIT\n
  *  IER      AWD2           LL_ADC_DisableIT\n
  *  IER      AWD3           LL_ADC_DisableIT\n
  *  IER      LDORDY         LL_ADC_DisableIT
  * @param  p_adc Pointer to ADC instance
  * @param  it   This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_IT_ADRDY
  *         @arg @ref LL_ADC_IT_EOC
  *         @arg @ref LL_ADC_IT_EOS
  *         @arg @ref LL_ADC_IT_OVR
  *         @arg @ref LL_ADC_IT_EOSMP
  *         @arg @ref LL_ADC_IT_JEOC
  *         @arg @ref LL_ADC_IT_JEOS
  *         @arg @ref LL_ADC_IT_JQOVF
  *         @arg @ref LL_ADC_IT_AWD1
  *         @arg @ref LL_ADC_IT_AWD2
  *         @arg @ref LL_ADC_IT_AWD3
  *         @arg @ref LL_ADC_IT_LDORDY
  *         @arg @ref LL_ADC_IT_ALL
  * @note   Generic function with flag selected as parameter.
  *         Optimized functions for each flag are also available.
  */
__STATIC_INLINE void LL_ADC_DisableIT(ADC_TypeDef *p_adc, uint32_t it)
{
  STM32_CLEAR_BIT(p_adc->IER, it);
}

/**
  * @brief  Disable interruption ADC ready.
  * @rmtoll
  *  IER      ADRDYIE        LL_ADC_DisableIT_ADRDY
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_ADRDY(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_ADRDY);
}

/**
  * @brief  Disable interruption ADC group regular end of unitary conversion.
  * @rmtoll
  *  IER      EOCIE          LL_ADC_DisableIT_EOC
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOC(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_EOC);
}

/**
  * @brief  Disable interruption ADC group regular end of sequence conversions.
  * @rmtoll
  *  IER      EOSIE          LL_ADC_DisableIT_EOS
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOS(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_EOS);
}

/**
  * @brief  Disable interruption ADC group regular overrun.
  * @rmtoll
  *  IER      OVRIE          LL_ADC_DisableIT_OVR
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_OVR(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_OVR);
}

/**
  * @brief  Disable interruption ADC group regular end of sampling.
  * @rmtoll
  *  IER      EOSMPIE        LL_ADC_DisableIT_EOSMP
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOSMP(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_EOSMP);
}

/**
  * @brief  Disable interruption ADC group regular end of unitary conversion.
  * @rmtoll
  *  IER      JEOCIE         LL_ADC_DisableIT_JEOC
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_JEOC(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_JEOC);
}

/**
  * @brief  Disable interruption ADC group injected end of sequence conversions.
  * @rmtoll
  *  IER      JEOSIE         LL_ADC_DisableIT_JEOS
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_JEOS(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_JEOS);
}

/**
  * @brief  Disable interruption ADC group injected context queue overflow.
  * @rmtoll
  *  IER      JQOVFIE        LL_ADC_DisableIT_JQOVF
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_JQOVF(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_JQOVF);
}

/**
  * @brief  Disable interruption ADC analog watchdog 1.
  * @rmtoll
  *  IER      AWD1IE         LL_ADC_DisableIT_AWD1
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD1(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_AWD1);
}

/**
  * @brief  Disable interruption ADC analog watchdog 2.
  * @rmtoll
  *  IER      AWD2IE         LL_ADC_DisableIT_AWD2
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD2(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_AWD2);
}

/**
  * @brief  Disable interruption ADC analog watchdog 3.
  * @rmtoll
  *  IER      AWD3IE         LL_ADC_DisableIT_AWD3
  * @param  p_adc Pointer to ADC instance
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD3(ADC_TypeDef *p_adc)
{
  STM32_CLEAR_BIT(p_adc->IER, LL_ADC_IT_AWD3);
}

/**
  * @brief  Get state of ADC interruption.
  * @rmtoll
  *  IER      ADRDY          LL_ADC_IsEnabledIT\n
  *  IER      EOC            LL_ADC_IsEnabledIT\n
  *  IER      EOS            LL_ADC_IsEnabledIT\n
  *  IER      OVR            LL_ADC_IsEnabledIT\n
  *  IER      EOSMP          LL_ADC_IsEnabledIT\n
  *  IER      JEOC           LL_ADC_IsEnabledIT\n
  *  IER      JEOS           LL_ADC_IsEnabledIT\n
  *  IER      JQOVF          LL_ADC_IsEnabledIT\n
  *  IER      AWD1           LL_ADC_IsEnabledIT\n
  *  IER      AWD2           LL_ADC_IsEnabledIT\n
  *  IER      AWD3           LL_ADC_IsEnabledIT\n
  *  IER      LDORDY         LL_ADC_IsEnabledIT
  * @param  p_adc Pointer to ADC instance
  * @param  it   This parameter can be one of the following values:
  *         @arg @ref LL_ADC_IT_ADRDY
  *         @arg @ref LL_ADC_IT_EOC
  *         @arg @ref LL_ADC_IT_EOS
  *         @arg @ref LL_ADC_IT_OVR
  *         @arg @ref LL_ADC_IT_EOSMP
  *         @arg @ref LL_ADC_IT_JEOC
  *         @arg @ref LL_ADC_IT_JEOS
  *         @arg @ref LL_ADC_IT_JQOVF
  *         @arg @ref LL_ADC_IT_AWD1
  *         @arg @ref LL_ADC_IT_AWD2
  *         @arg @ref LL_ADC_IT_AWD3
  *         @arg @ref LL_ADC_IT_LDORDY
  *         @arg @ref LL_ADC_IT_ALL
  * @note   Generic function with flag selected as parameter.
  *         Optimized functions for each flag are available.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT(ADC_TypeDef *p_adc, uint32_t it)
{
  return ((STM32_READ_BIT(p_adc->IER, it) == (it)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC ready
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      ADRDYIE        LL_ADC_IsEnabledIT_ADRDY
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_ADRDY(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_ADRDY) == (LL_ADC_IT_ADRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular end of unitary conversion
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      EOCIE          LL_ADC_IsEnabledIT_EOC
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOC(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_EOC) == (LL_ADC_IT_EOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular end of sequence conversions
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      EOSIE          LL_ADC_IsEnabledIT_EOS
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOS(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_EOS) == (LL_ADC_IT_EOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular overrun
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      OVRIE          LL_ADC_IsEnabledIT_OVR
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_OVR(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_OVR) == (LL_ADC_IT_OVR)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular end of sampling
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      EOSMPIE        LL_ADC_IsEnabledIT_EOSMP
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOSMP(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_EOSMP) == (LL_ADC_IT_EOSMP)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group injected end of unitary conversion
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      JEOCIE         LL_ADC_IsEnabledIT_JEOC
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JEOC(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_JEOC) == (LL_ADC_IT_JEOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group injected end of sequence conversions
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      JEOSIE         LL_ADC_IsEnabledIT_JEOS
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JEOS(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_JEOS) == (LL_ADC_IT_JEOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group injected context queue overflow interrupt state
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      JQOVFIE        LL_ADC_IsEnabledIT_JQOVF
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JQOVF(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_JQOVF) == (LL_ADC_IT_JQOVF)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC analog watchdog 1 out of window event.
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      AWD1IE         LL_ADC_IsEnabledIT_AWD1
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD1(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_AWD1) == (LL_ADC_IT_AWD1)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC analog watchdog 2 out of window event.
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      AWD2IE         LL_ADC_IsEnabledIT_AWD2
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD2(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_AWD2) == (LL_ADC_IT_AWD2)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC analog watchdog 3 out of window event.
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll
  *  IER      AWD3IE         LL_ADC_IsEnabledIT_AWD3
  * @param  p_adc Pointer to ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD3(const ADC_TypeDef *p_adc)
{
  return ((STM32_READ_BIT(p_adc->IER, LL_ADC_IT_AWD3) == (LL_ADC_IT_AWD3)) ? 1UL : 0UL);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* ADC1 || ADC2 || ADC3 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G5XX_LL_ADC_H */
