/**
  ******************************************************************************
  * @file    stm32h7pxx_ll_comp.h
  * @brief   Header file of COMP LL module.
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
#ifndef STM32H7PXX_LL_COMP_H
#define STM32H7PXX_LL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_LL_Driver
  * @{
  */

#if defined (COMP1) || defined (COMP2) || defined (COMP3) || defined (COMP4) || defined (COMP5) || defined (COMP6) \
|| defined (COMP7) || defined (COMP8)

/** @defgroup COMP_LL COMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
typedef struct
{
  uint8_t reg_val; /*!< Blanking source register value */
  uint8_t inst;    /*!< Blanking source availability depending on comparator instance
                        (values as bitfields: "0" for not available, "1" for available on each bit position
                        corresponding to comparator instance) */
} ll_comp_blanking_src_lut_t;

/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup COMP_LL_Private_Constants COMP Private Constants
  * @{
  */

/* Internal masks and bitfields for pair of comparators instances window mode
To select into literals LL_COMP_WINDOW_x the relevant bits for (concatenation of multiple bits used in different
registers):
- Comparator instance selected as master for window mode : register offset
- Window mode enable or disable: bit value */
#define LL_COMP_WINDOW_COMP_ODD_REGOFFSET_MASK  (0x00000000UL) /* Register of COMP instance odd (COMP1_CSR, ...)
                                        defined as reference register */
#define LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK (0x00000001UL) /* Register of COMP instance even (COMP2_CSR, ...)
                                        offset vs register of COMP instance odd */
#define LL_COMP_WINDOW_COMP_REG_GAP             (7UL) /* Registers addresses gap between pair of comparator
                                        instances (unit: words) */
#define LL_COMP_WINDOW_COMP_REGOFFSET_MASK (LL_COMP_WINDOW_COMP_ODD_REGOFFSET_MASK \
                                            | LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK)
#define LL_COMP_WINDOW_COMP_X_SETTING_MASK (COMP_CFGR_INPSEL) /* Bitfield to select window mode */
#define LL_COMP_WINDOW_OUT_SETTING_MASK (COMP_CFGR_WINOUT) /* Bitfield to select window output */
#define LL_COMP_WINDOW_OUT_XOR_BOTH_MASK (COMP_CFGR_WINOUT << 1UL) /* Differentiator of window output settings */
#define LL_COMP_WINDOW_OUT_XOR_BOTH_POS_VS_WINDOW (1UL) /* Bitfields position differences between
                                        LL_COMP_WINDOW_OUT_XOR_BOTH_MASK and LL_COMP_WINDOW_COMP_X_SETTING_MASK */

/* COMP instances relative position in COMP common instance */
#define LL_COMP_WINDOW_COMP_ODD         (LL_COMP_WINDOW_COMP_ODD_REGOFFSET_MASK)  /* Comparator instance odd
                                        (COMP1, ...) */
#define LL_COMP_WINDOW_COMP_EVEN        (LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK) /* Comparator instance even
                                        (COMP2, ...) */
/* Definition for specific input minus vs comparator instance */
#define LL_COMP_INPUT_MINUS_DAC_OFFSET (24U) /* Input minus bitfield value: range offset for DAC selection */
#define LL_COMP_INPUT_MINUS_DAC_MASK (0xFUL << 24U) /* Input minus bitfield value: range for DAC selection */
#define LL_COMP_INPUT_MINUS_DAC_BF_START (4U) /* Input minus bitfield value: start of range for DAC selection */
#define LL_COMP_INPUT_MINUS_DAC_BF_END   (6U) /* Input minus bitfield value: end of range for DAC selection */
#define LL_COMP_INPUT_MINUS_DAC_BF_MASK 0x3U  /* Input minus bitfield value: mask */
#define LL_COMP_INM_NA 0b11U /* COMP input minus not available */

/* Private macro to adapt input minus look up table size in function of instances available on each device
   (COMP instances not available on this device are ignored) */
#define LL_COMP_INPUT_MINUS_DAC_INST(comp8, comp7, comp6, comp5, comp4, comp3, comp2, comp1) \
  (((comp8) << 14U) | ((comp7) << 12U) | ((comp6) << 10U) | ((comp5) << 8U) | \
   ((comp4) << 6U) | ((comp3) << 4U) | ((comp2) << 2U) | ((comp1) << 0U))

/* Definition for specific blanking source bitfield value and availability vs comparator instance */
static const uint16_t LL_COMP_OUTPUT_INPUT_MINUS_DAC_LUT[] =
{
  LL_COMP_INPUT_MINUS_DAC_INST(LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA,
                               2U, 2U, LL_COMP_INM_NA, 0U), /* Index 0: DAC1_CH1,
                                        specific to COMP instance: COMP1, COMP3, COMP4 */
  LL_COMP_INPUT_MINUS_DAC_INST(LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA, 1U,
                               LL_COMP_INM_NA, LL_COMP_INM_NA, 0U, LL_COMP_INM_NA), /* Index 1: DAC1_CH2,
                                        specific to COMP instance: COMP2, COMP5 */
  LL_COMP_INPUT_MINUS_DAC_INST(2U, LL_COMP_INM_NA, LL_COMP_INM_NA, 0U,
                               LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA), /* Index 2: DAC2_CH1,
                                        specific to COMP instance: COMP5, COMP8 */
  LL_COMP_INPUT_MINUS_DAC_INST(LL_COMP_INM_NA, 2U, 0U, LL_COMP_INM_NA,
                               LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA), /* Index 3: DAC2_CH2,
                                        specific to COMP instance: COMP6, COMP7 */
  LL_COMP_INPUT_MINUS_DAC_INST(LL_COMP_INM_NA, 0U, LL_COMP_INM_NA, LL_COMP_INM_NA,
                               LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA), /* Index 4: DAC3_CH1,
                                        specific to COMP instance: COMP7 */
  LL_COMP_INPUT_MINUS_DAC_INST(0U, LL_COMP_INM_NA, 2U, LL_COMP_INM_NA,
                               LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA, 1U), /* Index 5: DAC3_CH2,
                                        specific to COMP instance: COMP1, COMP6, COMP8 */
  LL_COMP_INPUT_MINUS_DAC_INST(LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA,
                               LL_COMP_INM_NA, 1U, 1U, LL_COMP_INM_NA), /* Index 6: DAC4_CH1,
                                        specific to COMP instance: COMP2, COMP3 */
  LL_COMP_INPUT_MINUS_DAC_INST(LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA, 2U,
                               1U, LL_COMP_INM_NA, LL_COMP_INM_NA, LL_COMP_INM_NA), /* Index 7: DAC4_CH2,
                                        specific to COMP instance: COMP4, COMP5 */
};
#define LL_COMP_OUTPUT_INPUT_MINUS_DAC_LUT_COUNT (sizeof(LL_COMP_OUTPUT_INPUT_MINUS_DAC_LUT) \
                                                  / sizeof(*(LL_COMP_OUTPUT_INPUT_MINUS_DAC_LUT)))

/* Definition for specific blanking source bitfield value and availability vs comparator instance */
static const ll_comp_blanking_src_lut_t LL_COMP_OUTPUT_BLANK_INST_LUT[] =
{
  {.reg_val = 0U, .inst = 0b11111111U}, /* Index 0: No blanking source, common to all COMP instances */
  {.reg_val = 1U, .inst = 0b11111111U}, /* Index 1: TIM1_OC5, common to all COMP instances */
  {.reg_val = 2U, .inst = 0b11001100U}, /* Index 2: TIM1_OC6, specific to COMP instance: COMP3, COMP4, COMP7, COMP8 */
  {.reg_val = 2U, .inst = 0b00110011U}, /* Index 3: TIM1_OC7, specific to COMP instance: COMP1, COMP2, COMP5, COMP6 */
  {.reg_val = 3U, .inst = 0b00001111U}, /* Index 4: TIM2_OC3, specific to COMP instance: COMP1, COMP2, COMP3, COMP4 */
  {.reg_val = 3U, .inst = 0b00110000U}, /* Index 5: TIM2_OC4, specific to COMP instance: COMP5, COMP6 */
  {.reg_val = 3U, .inst = 0b11000011U}, /* Index 6: TIM9_OC1, specific to COMP instance: COMP1, COMP2, COMP7, COMP8.
                                            For COMP1/COMP2 and COMP7,COMP8: different register value, managed in
                                            functions configuring blanking src. */
  {.reg_val = 4U, .inst = 0b00111111U}, /* Index 7: TIM3_OC3, specific to COMP instance: COMP1, COMP2, COMP3,
                                            COMP4, COMP5, COMP6 */
  {.reg_val = 4U, .inst = 0b11000000U}, /* Index 8: TIM3_OC4, specific to COMP instance: COMP7, COMP8 */
  {.reg_val = 5U, .inst = 0b11111111U}, /* Index 9: TIM4_OC3, common to all COMP instances */
  {.reg_val = 6U, .inst = 0b11111111U}, /* Index 10: TIM8_OC5, common to all COMP instances */
  {.reg_val = 7U, .inst = 0b00110011U}, /* Index 11: TIM8_OC7, specific to COMP instance: COMP1, COMP2, COMP5, COMP6 */
  {.reg_val = 7U, .inst = 0b11001100U}, /* Index 12: TIM8_OC6, specific to COMP instance: COMP3, COMP4, COMP7, COMP8 */
  {.reg_val = 8U, .inst = 0b11111111U}, /* Index 13: TIM12_OC1, common to all COMP instances */
  {.reg_val = 9U, .inst = 0b11111111U}, /* Index 14: TIM20_OC5, common to all COMP instances */
  {.reg_val = 10U, .inst = 0b00110011U}, /* Index 15: TIM20_OC7, specific to COMP instance: COMP1, COMP2, COMP5, COMP6*/
  {.reg_val = 10U, .inst = 0b11001100U}, /* Index 16: TIM20_OC6, specific to COMP instance: COMP3, COMP4, COMP7, COMP8*/
  {.reg_val = 11U, .inst = 0b11111111U}, /* Index 17: TIM15_OC1, common to all COMP instances */
  {.reg_val = 12U, .inst = 0b11111111U}  /* Index 18: TIM15_OC2, common to all COMP instances */
};

#define LL_COMP_OUTPUT_BLANK_INST_LUT_COUNT (sizeof(LL_COMP_OUTPUT_BLANK_INST_LUT) \
                                             / sizeof(*(LL_COMP_OUTPUT_BLANK_INST_LUT)))

/* Definition for specific blanking source vs comparator instance */
#define LL_COMP_BLANKINGSRC_TIM9_OC1_COMP78 (3U) /* Comp. output blanking source TIM9 OC1 (register bitfield value),
                                                    specific to COMP instance: COMP78. */
#define LL_COMP_BLANKINGSRC_TIM9_OC1_COMP12 (14U) /* Comp. output blanking source TIM9 OC1 (register bitfield value),
                                                     specific to COMP instance: COMP12. */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup COMP_LL_Private_Macros COMP Private Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address.
  */
#define LL_COMP_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__) \
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2UL))))

/**
  * @brief Helper macro to access the COMP instance corresponding index in
  *        look up tables LL_COMP_x_LUT[].
  * @param  p_comp Comparator instance
  * @retval look-up table index
  */
__STATIC_INLINE uint8_t LL_COMP_INSTANCE_LUT_INDEX(const COMP_TypeDef *p_comp) \
{
  uint32_t p_comp_addr = (uint32_t)p_comp;
  return (uint8_t)((p_comp_addr - (uint32_t)(COMP1)) >> 9U);
}

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Constants LL COMP Constants
  * @{
  */

#if defined(COMP_WINDOW_MODE_SUPPORT)
/** @defgroup COMP_LL_EC_COMMON_WINDOWMODE Comparator common modes - Window mode
  * @{
  */
#define LL_COMP_WINDOW_DISABLE          (0x00000000UL) /*!< Window mode disable: comparators pair are independent */
#define LL_COMP_WINDOW_INPUT_PLUS_ODD   (COMP_CFGR_INPSEL_0 | COMP_CFGR_INPSEL_1 | \
                                         LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK) /*!< Window mode
                                        enable: comparators instances pair have their input plus connected together.
                                        The common input is the one of instance index odd (COMP1, ...).
                                        Input plus of the other comparator is no more accessible. */
#define LL_COMP_WINDOW_INPUT_PLUS_EVEN  (COMP_CFGR_INPSEL_0 | COMP_CFGR_INPSEL_1 | \
                                         LL_COMP_WINDOW_COMP_ODD_REGOFFSET_MASK) /*!< Window mode
                                        enable: comparators instances pair have their input plus connected together.
                                        The common input is the one of instance index even (COMP2, ...).
                                        Input plus of the other comparator is no more accessible. */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_COMMON_WINDOWOUTPUT Comparator common modes - Window output
  * @{
  */
#define LL_COMP_WINDOW_OUTPUT_INDEPT    (0x00000000UL)/*!< Comparators window output default mode:
                                        both comparators output are independent, indicating each their own state.
                                        Note: To know signal state versus window thresholds, read each comparator
                                              output and perform a logical "exclusive or" operation. */
#define LL_COMP_WINDOW_OUTPUT_XOR_ODD   (COMP_CFGR_WINOUT | LL_COMP_WINDOW_COMP_ODD_REGOFFSET_MASK) /*!< Window output
                                        synthesized on instance index odd (COMP1, ...) output: no more indicating its
                                        own state but global window mode state. Logical high means monitored signal is
                                        within comparators window.
                                        Note: impacts only comparator output signal level (propagated to GPIO, EXTI
                                              lines, timers, ...), does not impact output digital state
                                              (@ref LL_COMP_ReadOutputLevel()) always reflecting each comparator
                                              output state.*/
#define LL_COMP_WINDOW_OUTPUT_XOR_EVEN  (COMP_CFGR_WINOUT | LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK) /*!< Window output
                                        synthesized on instance index even (COMP2, ...) output: no more indicating its
                                        own state but global window mode state. Logical high means monitored signal is
                                        within comparators window.
                                        Note: impacts only comparator output signal level (propagated to GPIO, EXTI
                                              lines, timers, ...), does not impact output digital state
                                              (@ref LL_COMP_ReadOutputLevel()) always reflecting each comparator
                                              output state.*/
#define LL_COMP_WINDOW_OUTPUT_XOR_BOTH  (COMP_CFGR_WINOUT | LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK \
                                         | LL_COMP_WINDOW_OUT_XOR_BOTH_MASK) /*!< Window output synthesized on both
                                        comparators output of pair of comparator selected:
                                        both comparators outputs are no more indicating their own state, but global
                                        window mode state (XOR: logical "exclusive or"). Logical high means monitored
                                        signal is within comparators window thresholds).
                                        This is a specific configuration (technically possible but not relevant from
                                        application point of view: 2 comparators output used for the same signal level),
                                        standard configuration for window mode is one of the settings above.
                                        Note: impacts only comparator output signal level (propagated to GPIO, EXTI
                                              lines, timers, ...), does not impact output digital state
                                              (@ref LL_COMP_ReadOutputLevel()) always reflecting each comparator
                                              output state.*/
/**
  * @}
  */

#endif /* COMP_WINDOW_MODE_SUPPORT */
/** @defgroup COMP_LL_EC_INPUT_PLUS Comparator inputs - Input plus (input non-inverting) selection
  * @note     Inputs connected to another comparator instance for window mode are managed by window mode functions.
  * @{
  */
#define LL_COMP_INPUT_PLUS_IO1          (0x00000000UL)       /*!< Comparator input plus connected to IO1
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP1") */
#define LL_COMP_INPUT_PLUS_IO2          (COMP_CFGR_INPSEL_0)  /*!< Comparator input plus connected to IO2
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP2") */
#define LL_COMP_INPUT_PLUS_IO3          (COMP_CFGR_INPSEL_1)  /*!< Comparator input plus connected to IO3
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP3") */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_MINUS Comparator inputs - Input minus (input inverting) selection
  * @{
  */
#define LL_COMP_INPUT_MINUS_VREFINT     (COMP_CFGR_INMSEL_1 | COMP_CFGR_INMSEL_0 | COMP_CFGR_SCALEN) /*!< Comparator
                                        input minus connected to VrefInt (for VrefInt voltage value, refer to
                                        datasheet). */
#define LL_COMP_INPUT_MINUS_1_4VREFINT  (COMP_CFGR_SCALEN | COMP_CFGR_BRGEN) /*!< Comparator input minus connected
                                        to 1/4 VrefInt (for VrefInt voltage value, refer to datasheet). */
#define LL_COMP_INPUT_MINUS_1_2VREFINT  (COMP_CFGR_INMSEL_0 | COMP_CFGR_SCALEN | COMP_CFGR_BRGEN) /*!< Comparator
                                        input minus connected to 1/2 VrefInt (for VrefInt voltage value, refer to
                                        datasheet). */
#define LL_COMP_INPUT_MINUS_3_4VREFINT  (COMP_CFGR_INMSEL_1 | COMP_CFGR_SCALEN | COMP_CFGR_BRGEN) /*!< Comparator
                                        input minus connected to 3/4 VrefInt (for VrefInt voltage value, refer to
                                        datasheet). */
#define LL_COMP_INPUT_MINUS_IO1         (COMP_CFGR_INMSEL_2 | COMP_CFGR_INMSEL_1 | COMP_CFGR_INMSEL_0) /*!< Comparator
                                        input plus connected to IO1 (for GPIO mapping, refer to datasheet
                                        parameters "COMPx_INM1") */
#define LL_COMP_INPUT_MINUS_IO2         (COMP_CFGR_INMSEL_3) /*!< Comparator input plus connected
                                        to IO2 (for GPIO mapping, refer to datasheet parameters "COMPx_INM2") */
#define LL_COMP_INPUT_MINUS_DAC1_CH1    (0UL << LL_COMP_INPUT_MINUS_DAC_OFFSET) /*!< Comparator input minus connected
                                        to DAC1 channel 1 (specific to COMP instances: COMP1, COMP3, COMP4).
                                        Note: Value corresponding to look up table index, managed in config function. */
#define LL_COMP_INPUT_MINUS_DAC1_CH2    (1UL << LL_COMP_INPUT_MINUS_DAC_OFFSET) /*!< Comparator input minus connected
                                        to DAC1 channel 2 (specific to COMP instances: COMP2, COMP5).
                                        Note: Value corresponding to look up table index, managed in config function. */
#define LL_COMP_INPUT_MINUS_DAC2_CH1    (2UL << LL_COMP_INPUT_MINUS_DAC_OFFSET) /*!< Comparator input minus connected
                                        to DAC2 channel 1 (specific to COMP instances: COMP5, COMP8).
                                        Note: Value corresponding to look up table index, managed in config function. */
#define LL_COMP_INPUT_MINUS_DAC2_CH2    (3UL << LL_COMP_INPUT_MINUS_DAC_OFFSET) /*!< Comparator input minus connected
                                        to DAC2 channel 2 (specific to COMP instances: COMP6, COMP7).
                                        Note: Value corresponding to look up table index, managed in config function. */
#define LL_COMP_INPUT_MINUS_DAC3_CH1    (4UL << LL_COMP_INPUT_MINUS_DAC_OFFSET) /*!< Comparator input minus connected
                                        to DAC3 channel 1 (specific to COMP instances: COMP7).
                                        Note: Value corresponding to look up table index, managed in config function. */
#define LL_COMP_INPUT_MINUS_DAC3_CH2    (5UL << LL_COMP_INPUT_MINUS_DAC_OFFSET) /*!< Comparator input minus connected
                                        to DAC3 channel 2 (specific to COMP instances: COMP1, COMP6, COMP8).
                                        Note: Value corresponding to look up table index, managed in config function. */
#define LL_COMP_INPUT_MINUS_DAC4_CH1    (6UL << LL_COMP_INPUT_MINUS_DAC_OFFSET) /*!< Comparator input minus connected
                                        to DAC4 channel 1 (specific to COMP instances: COMP2, COMP3).
                                        Note: Value corresponding to look up table index, managed in config function. */
#define LL_COMP_INPUT_MINUS_DAC4_CH2    (7UL << LL_COMP_INPUT_MINUS_DAC_OFFSET) /*!< Comparator input minus connected
                                        to DAC4 channel 2 (specific to COMP instances: COMP4, COMP5).
                                        Note: Value corresponding to look up table index, managed in config function. */
#define LL_COMP_INPUT_MINUS_COMP_PAIR   (COMP_CFGR_INMSEL_3 | COMP_CFGR_INMSEL_0) /*!< Comparator input minus connected
                                        to the other comparator instance input minus of the common pair
                                        (for comparator common instances, refer to reference manual
                                        or helper macro LL_COMP_COMMON_INSTANCE).
                                        This connection can be used to mutualize a connection to GPIO. */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_HYSTERESIS Comparator input - Hysteresis
  * @{
  */
#define LL_COMP_HYSTERESIS_NONE         (0x00000000UL)                        /*!< No hysteresis */
#define LL_COMP_HYSTERESIS_LOW          (COMP_CFGR_HYST_0)                    /*!< Hysteresis level low */
#define LL_COMP_HYSTERESIS_MEDIUM       (COMP_CFGR_HYST_1)                    /*!< Hysteresis level medium */
#define LL_COMP_HYSTERESIS_HIGH         (COMP_CFGR_HYST_1 | COMP_CFGR_HYST_0) /*!< Hysteresis level high */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_FILTERING_ANALOG Comparator filtering - Analog filter (deglitcher)
  * @note  Deglitcher increases propagation delay of the comparator with few nanoseconds (refer to device datasheet),
  *        reducing potential output oscillations. It can be combined with comparator input hysteresis.
  * @{
  */
#define LL_COMP_FILT_ANA_DISABLE        (0x00000000UL)    /*!< Comparator analog filtering (deglitcher) disable. */
#define LL_COMP_FILT_ANA_ENABLE         (COMP_CFGR_DGLT) /*!< Comparator analog filtering (deglitcher) enable. */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_FILTERING_DIGITAL Comparator filtering - Digital filter
  * @note  Digital filter can filter low frequency noise on comparator inputs, based on a clock and count number
  *        of successive samples with stable state.
  * @{
  */
#define LL_COMP_FILT_DIG_DISABLE        (0x00000000UL)  /*!< Comparator digital filtering disable */
#define LL_COMP_FILT_DIG_DIV1_SMP2      ((1UL << COMP_FLTR_FSEL_Pos) | (0UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 1, samples with stable state: 2. */
#define LL_COMP_FILT_DIG_DIV1_SMP4      ((2UL << COMP_FLTR_FSEL_Pos) | (0UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 1, samples with stable state: 4. */
#define LL_COMP_FILT_DIG_DIV1_SMP8      ((3UL << COMP_FLTR_FSEL_Pos) | (0UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 1, samples with stable state: 8. */

#define LL_COMP_FILT_DIG_DIV2_SMP2      ((1UL << COMP_FLTR_FSEL_Pos) | (1UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 2, samples with stable state: 2. */
#define LL_COMP_FILT_DIG_DIV2_SMP4      ((2UL << COMP_FLTR_FSEL_Pos) | (1UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 2, samples with stable state: 4. */
#define LL_COMP_FILT_DIG_DIV2_SMP6      ((4UL << COMP_FLTR_FSEL_Pos) | (0UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 2, samples with stable state: 6. */
#define LL_COMP_FILT_DIG_DIV2_SMP8      ((3UL << COMP_FLTR_FSEL_Pos) | (1UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 2, samples with stable state: 8. */

#define LL_COMP_FILT_DIG_DIV4_SMP2      ((1UL << COMP_FLTR_FSEL_Pos) | (2UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 4, samples with stable state: 2. */
#define LL_COMP_FILT_DIG_DIV4_SMP4      ((2UL << COMP_FLTR_FSEL_Pos) | (2UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 4, samples with stable state: 4. */
#define LL_COMP_FILT_DIG_DIV4_SMP6      ((4UL << COMP_FLTR_FSEL_Pos) | (1UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 4, samples with stable state: 6. */
#define LL_COMP_FILT_DIG_DIV4_SMP8      ((3UL << COMP_FLTR_FSEL_Pos) | (2UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 4, samples with stable state: 8. */

#define LL_COMP_FILT_DIG_DIV8_SMP2      ((1UL << COMP_FLTR_FSEL_Pos) | (3UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 8, samples with stable state: 2. */
#define LL_COMP_FILT_DIG_DIV8_SMP4      ((2UL << COMP_FLTR_FSEL_Pos) | (3UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 8, samples with stable state: 4. */
#define LL_COMP_FILT_DIG_DIV8_SMP6      ((4UL << COMP_FLTR_FSEL_Pos) | (2UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 8, samples with stable state: 6. */
#define LL_COMP_FILT_DIG_DIV8_SMP8      ((3UL << COMP_FLTR_FSEL_Pos) | (3UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 8, samples with stable state: 8. */

#define LL_COMP_FILT_DIG_DIV16_SMP5     ((10UL << COMP_FLTR_FSEL_Pos) | (0UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 16, samples with stable state: 5. */
#define LL_COMP_FILT_DIG_DIV16_SMP6     ((4UL << COMP_FLTR_FSEL_Pos) | (3UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 16, samples with stable state: 6. */
#define LL_COMP_FILT_DIG_DIV16_SMP8     ((12UL << COMP_FLTR_FSEL_Pos) | (0UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 16, samples with stable state: 8. */

#define LL_COMP_FILT_DIG_DIV32_SMP5     ((10UL << COMP_FLTR_FSEL_Pos) | (1UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 32, samples with stable state: 5. */
#define LL_COMP_FILT_DIG_DIV32_SMP6     ((14UL << COMP_FLTR_FSEL_Pos) | (0UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 32, samples with stable state: 6. */
#define LL_COMP_FILT_DIG_DIV32_SMP8     ((12UL << COMP_FLTR_FSEL_Pos) | (1UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 32, samples with stable state: 8. */

#define LL_COMP_FILT_DIG_DIV64_SMP5     ((10UL << COMP_FLTR_FSEL_Pos) | (2UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 64, samples with stable state: 5. */
#define LL_COMP_FILT_DIG_DIV64_SMP6     ((14UL << COMP_FLTR_FSEL_Pos) | (1UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 64, samples with stable state: 6. */
#define LL_COMP_FILT_DIG_DIV64_SMP8     ((12UL << COMP_FLTR_FSEL_Pos) | (2UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 64, samples with stable state: 8. */

#define LL_COMP_FILT_DIG_DIV128_SMP5    ((10UL << COMP_FLTR_FSEL_Pos) | (3UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 128, samples with stable state: 5. */
#define LL_COMP_FILT_DIG_DIV128_SMP6    ((14UL << COMP_FLTR_FSEL_Pos) | (2UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 128, samples with stable state: 6. */
#define LL_COMP_FILT_DIG_DIV128_SMP8    ((12UL << COMP_FLTR_FSEL_Pos) | (3UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 128, samples with stable state: 8. */

#define LL_COMP_FILT_DIG_DIV256_SMP5    ((13UL << COMP_FLTR_FSEL_Pos) | (3UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 256, samples with stable state: 5. */
#define LL_COMP_FILT_DIG_DIV256_SMP6    ((14UL << COMP_FLTR_FSEL_Pos) | (3UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 256, samples with stable state: 6. */
#define LL_COMP_FILT_DIG_DIV256_SMP8    ((15UL << COMP_FLTR_FSEL_Pos) | (3UL << COMP_FLTR_FPSC_Pos)) /*!< Comparator
                                        digital filtering: kernel clock prescaler 256, samples with stable state: 8. */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_POLARITY Comparator output - Output polarity
  * @{
  */
#define LL_COMP_OUTPUTPOL_NONINVERTED   (0x00000000UL) /*!< Comparator output polarity not inverted:
                                        comparator output at high level when input voltages: plus higher than minus */
#define LL_COMP_OUTPUTPOL_INVERTED      (COMP_CFGR_POLARITY)   /*!< Comparator output polarity not inverted:
                                        comparator output at low level when input voltages: plus higher than minus */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_BLANKING_SOURCE Comparator output - Blanking source
  * @{
  */
#define LL_COMP_BLANKINGSRC_NONE        (0U) /*!< COMP output without blanking */
#define LL_COMP_BLANKINGSRC_TIM1_OC5    (1U) /*!< COMP output blanking source TIM1 OC5,
                                        common to all COMP instances. */
#define LL_COMP_BLANKINGSRC_TIM1_OC6    (2U) /*!< COMP output blanking source TIM1 OC6,
                                        specific to COMP instance: COMP3, COMP4, COMP7, COMP8. */
#define LL_COMP_BLANKINGSRC_TIM1_OC7    (3U) /*!< COMP output blanking source TIM1 OC7,
                                        specific to COMP instance: COMP1, COMP2, COMP5, COMP6. */
#define LL_COMP_BLANKINGSRC_TIM2_OC3    (4U) /*!< COMP output blanking source TIM2 OC3,
                                        specific to COMP instance: COMP1, COMP2, COMP3, COMP4. */
#define LL_COMP_BLANKINGSRC_TIM2_OC4    (5U) /*!< COMP output blanking source TIM2 OC4,
                                        specific to COMP instance: COMP5, COMP6. */
#define LL_COMP_BLANKINGSRC_TIM9_OC1    (6U) /*!< COMP output blanking source TIM9 OC1,
                                        specific to COMP instance: COMP1, COMP2, COMP7, COMP8. */
#define LL_COMP_BLANKINGSRC_TIM3_OC3    (7U) /*!< COMP output blanking source TIM3 OC3,
                                        specific to COMP instance: COMP1, COMP2, COMP3, COMP4, COMP5, COMP6. */
#define LL_COMP_BLANKINGSRC_TIM3_OC4    (8U) /*!< COMP output blanking source TIM3 OC4,
                                        specific to COMP instance: COMP7, COMP8. */
#define LL_COMP_BLANKINGSRC_TIM4_OC3    (9U) /*!< COMP output blanking source TIM4 OC3,
                                        common to all COMP instances. */
#define LL_COMP_BLANKINGSRC_TIM8_OC5    (10U) /*!< COMP output blanking source TIM8 OC5,
                                        common to all COMP instances. */
#define LL_COMP_BLANKINGSRC_TIM8_OC7    (11U) /*!< COMP output blanking source TIM8 OC7,
                                        specific to COMP instance: COMP1, COMP2, COMP5, COMP6. */
#define LL_COMP_BLANKINGSRC_TIM8_OC6    (12U) /*!< COMP output blanking source TIM8 OC6,
                                        specific to COMP instance: COMP3, COMP4, COMP7, COMP8. */
#define LL_COMP_BLANKINGSRC_TIM12_OC1   (13U) /*!< COMP output blanking source TIM12 OC1,
                                        common to all COMP instances. */
#define LL_COMP_BLANKINGSRC_TIM20_OC5   (14U) /*!< COMP output blanking source TIM20 OC5,
                                        common to all COMP instances. */
#define LL_COMP_BLANKINGSRC_TIM20_OC7   (15U) /*!< COMP output blanking source TIM20 OC7,
                                        specific to COMP instance: COMP1, COMP2, COMP5, COMP6. */
#define LL_COMP_BLANKINGSRC_TIM20_OC6   (16U) /*!< COMP output blanking source TIM20 OC6,
                                        specific to COMP instance: COMP3, COMP4, COMP7, COMP8. */
#define LL_COMP_BLANKINGSRC_TIM15_OC1   (17U) /*!< COMP output blanking source TIM15 OC1,
                                        common to all COMP instances. */
#define LL_COMP_BLANKINGSRC_TIM15_OC2   (18U) /*!< COMP output blanking source TIM15 OC2,
                                        common to all COMP instances. */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_LEVEL Comparator output - Output level
  * @{
  */
#define LL_COMP_OUTPUT_LEVEL_LOW        (0x00000000UL) /*!< Comparator output level low (with polarity not inverted) */
#define LL_COMP_OUTPUT_LEVEL_HIGH       (0x00000001UL) /*!< Comparator output level high (with polarity not inverted) */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_HW_DELAYS  Definitions of COMP hardware constraints delays
  * @note   Only COMP peripheral HW delays are defined in COMP LL driver driver, not timeout values.
  * @{
  */

/* Delay for comparator startup time.                                         */
/* Note: Delay required to reach propagation delay specification.             */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART").                                                       */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_STARTUP_US        (80UL) /*!< Delay for comparator startup time.
                                        Delay set to maximum value (refer to device datasheet, parameter "tSTART").
                                        Unit: us.
                                        Note: At comparator enable, delay required to reach propagation delay
                                              specification. */

/* Delay for comparator voltage scaler stabilization time.                    */
/* Note: Voltage scaler is used when selecting comparator input               */
/*       based on VrefInt (VrefInt or subdivision of VrefInt).                */
/* Note: To get scaler bridge configuration,                                  */
/*       refer to @ref LL_COMP_IsInputScalerEnabled().                        */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART_SCALER").                                                */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US (220UL) /*!< Delay for comparator voltage scaler stabilization time
                                        Delay set to maximum value (refer to device datasheet,
                                        parameter "tSTART_SCALER").
                                        Unit: us.
                                        Note: Voltage scaler is used when selecting comparator input
                                              based on VrefInt (VrefInt or subdivision of VrefInt).
                                        Note: To get scaler bridge configuration,
                                              refer to @ref LL_COMP_IsInputScalerEnabled().
                                        */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Macros LL COMP Macros
  * @{
  */
/** @defgroup COMP_LL_EM_WRITE_READ Common write and read registers macro
  * @{
  */

/**
  * @brief  Write a value in COMP register.
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  */
#define LL_COMP_WRITE_REG(__INSTANCE__, __REG__, __VALUE__) STM32_WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

/**
  * @brief  Read a value in COMP register.
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_COMP_READ_REG(__INSTANCE__, __REG__) STM32_READ_REG((__INSTANCE__)->__REG__)
/**
  * @}
  */

/** @defgroup COMP_LL_EM_HELPER_MACRO COMP helper macro
  * @{
  */

/**
  * @brief  Helper macro to select the COMP common instance
  *         to which is belonging the selected COMP instance.
  * @param  instance COMP instance
  * @note   COMP common register instance can be used to
  *         set parameters common to several COMP instances.
  *         Refer to functions having argument "p_comp_common" as parameter.
  * @retval COMP common instance or value "0" if there is no COMP common instance.
  */
#define LL_COMP_COMMON_INSTANCE(instance)                                      \
  ((((instance) == COMP1) || ((instance) == COMP2))                            \
   ? (COMP12_COMMON)                                                           \
   :                                                                           \
   ((((instance) == COMP3) || ((instance) == COMP4))                           \
    ? (COMP34_COMMON)                                                          \
    :                                                                          \
    ((((instance) == COMP5) || ((instance) == COMP6))                          \
     ? (COMP56_COMMON)                                                         \
     :                                                                         \
     (COMP78_COMMON)                                                           \
    )                                                                          \
   )                                                                           \
  )

/**
  * @brief  Helper macro to define comparator instance position generic identification (odd or even)
  *         from comparator instance.
  * @param  instance Comparator instance.
  * @retval Comparator common instance or value "0" if there is no COMP common instance.
  */
#define LL_COMP_WINDOW_INST_POS_ID(instance)                                   \
  ((((instance) == COMP1) || ((instance) == COMP3)                             \
    || ((instance) == COMP5) || ((instance) == COMP7))                         \
   ? ((LL_COMP_WINDOW_COMP_ODD))                                               \
   :                                                                           \
   ((LL_COMP_WINDOW_COMP_EVEN))                                                \
  )

/**
  * @brief  Helper macro to select literal LL_COMP_WINDOW_INPUT_PLUS_x with suffix odd or even
  *         from comparator instance.
  * @param  instance COMP instance.
  * @note   Helper macro intended to be used with function LL_COMP_SetCommonWindowMode()
  * @retval COMP common instance or value "0" if there is no COMP common instance.
  */
#define LL_COMP_WINDOW_INST_TO_INPUT_PLUS(instance)                           \
  (((LL_COMP_WINDOW_INST_POS_ID(instance) == LL_COMP_WINDOW_COMP_ODD))        \
   ? ((LL_COMP_WINDOW_INPUT_PLUS_ODD))                                        \
   :                                                                          \
   ((LL_COMP_WINDOW_INPUT_PLUS_EVEN))                                         \
  )

/**
  * @brief  Helper macro to select literal LL_COMP_WINDOW_OUTPUT_x with suffix odd or even
  *         from comparator instance.
  * @param  instance COMP instance.
  * @note   Helper macro intended to be used with function LL_COMP_SetCommonWindowOutput()
  * @retval COMP common instance or value "0" if there is no COMP common instance.
  */
#define LL_COMP_WINDOW_INST_TO_OUTPUT(instance)                               \
  (((LL_COMP_WINDOW_INST_POS_ID(instance) == LL_COMP_WINDOW_COMP_ODD))        \
   ? ((LL_COMP_WINDOW_OUTPUT_XOR_ODD))                                        \
   :                                                                          \
   ((LL_COMP_WINDOW_OUTPUT_XOR_EVEN))                                         \
  )
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Functions LL COMP Functions
  * @{
  */

#if defined(COMP_WINDOW_MODE_SUPPORT)
/** @defgroup COMP_LL_EF_Configuration_comparator_common Configuration of COMP hierarchical scope:
  *           common to several COMP instances
  * @{
  */

/**
  * @brief  Set window mode of a pair of comparators instances
  *         (2 consecutive COMP instances COMP<x> and COMP<x+1>).
  * @rmtoll
  *  CFGR     WINMODE        LL_COMP_SetCommonWindowMode
  * @param  p_comp_common Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref LL_COMP_COMMON_INSTANCE() )
  * @param  window_mode This parameter can be one of the following values:
  *         @arg @ref LL_COMP_WINDOW_DISABLE
  *         @arg @ref LL_COMP_WINDOW_INPUT_PLUS_ODD
  *         @arg @ref LL_COMP_WINDOW_INPUT_PLUS_EVEN
  *         Note: Parameters values with suffix odd or even can also be selected from comparator instance
  *               using helper macro LL_COMP_WINDOW_INST_TO_INPUT_PLUS.
  * @note   Configuration of window mode must be done before configuration of inputs
  *         (reset configuration of input plus).
  */
__STATIC_INLINE void LL_COMP_SetCommonWindowMode(COMP_Common_TypeDef *p_comp_common, uint32_t window_mode)
{
  /* Note: On this STM32 series, window mode can be set from any instance     */
  /*       of the pair of comparator instances.                               */

  __IO uint32_t *preg = LL_COMP_PTR_REG_OFFSET(p_comp_common->CFGR_ODD,
                                               (window_mode & LL_COMP_WINDOW_COMP_REGOFFSET_MASK)
                                               << LL_COMP_WINDOW_COMP_REG_GAP);

  /* Set window mode */
  STM32_MODIFY_REG(*preg, COMP_CFGR_INPSEL, (window_mode & LL_COMP_WINDOW_COMP_X_SETTING_MASK));
}

/**
  * @brief  Get window mode of a pair of comparators instances
  *         (2 consecutive COMP instances COMP<x> and COMP<x+1>).
  * @rmtoll
  *  CFGR     WINMODE        LL_COMP_GetCommonWindowMode
  * @param  p_comp_common Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref LL_COMP_COMMON_INSTANCE() ).
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_WINDOW_DISABLE
  *         @arg @ref LL_COMP_WINDOW_INPUT_PLUS_ODD
  *         @arg @ref LL_COMP_WINDOW_INPUT_PLUS_EVEN
  */
__STATIC_INLINE uint32_t LL_COMP_GetCommonWindowMode(const COMP_Common_TypeDef *p_comp_common)
{
  /* Note: On this STM32 series, window mode can be set from any instance     */
  /*       of the pair of comparator instances.                               */
  const uint32_t window_mode_comp_odd = (uint32_t)STM32_READ_BIT(p_comp_common->CFGR_ODD, COMP_CFGR_INPSEL);
  const uint32_t window_mode_comp_even = (uint32_t)STM32_READ_BIT(p_comp_common->CFGR_EVEN, COMP_CFGR_INPSEL);

  return (uint32_t)(window_mode_comp_odd
                    | window_mode_comp_even
                    | ((window_mode_comp_even >> COMP_CFGR_INPSEL_Pos) & LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK)
                   );
}

/**
  * @brief  Set window output of a pair of comparators instances
  *         (2 consecutive COMP instances COMP<x> and COMP<x+1>).
  * @rmtoll
  *  CFGR     WINOUT         LL_COMP_SetCommonWindowOutput
  * @param  p_comp_common Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref LL_COMP_COMMON_INSTANCE() ).
  * @param  window_output This parameter can be one of the following values:
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_INDEPT
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_ODD
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_EVEN
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_BOTH
  *         Note: Parameters values with suffix odd or even can also be selected from comparator instance
  *               using helper LL_COMP_WINDOW_INST_TO_OUTPUT.
  */
__STATIC_INLINE void LL_COMP_SetCommonWindowOutput(COMP_Common_TypeDef *p_comp_common, uint32_t window_output)
{
  /* Note: On this STM32 series, window mode can be set from any instance     */
  /*       of the pair of comparator instances.                               */

  __IO uint32_t *preg = LL_COMP_PTR_REG_OFFSET(p_comp_common->CFGR_ODD,
                                               (window_output & LL_COMP_WINDOW_COMP_REGOFFSET_MASK)
                                               << LL_COMP_WINDOW_COMP_REG_GAP);

  /* Clear the potential previous setting of window output on the relevant comparator instance */
  /* (clear bit of window output unless specific case of setting of comparator both output selected) */
  __IO uint32_t *preg_clear = LL_COMP_PTR_REG_OFFSET(p_comp_common->CFGR_ODD,
                                                     ((~(window_output & LL_COMP_WINDOW_COMP_REGOFFSET_MASK) & 0x1UL)
                                                      << LL_COMP_WINDOW_COMP_REG_GAP));
  STM32_MODIFY_REG(*preg_clear,
                   COMP_CFGR_WINOUT,
                   ((window_output & LL_COMP_WINDOW_OUT_XOR_BOTH_MASK)
                    >> LL_COMP_WINDOW_OUT_XOR_BOTH_POS_VS_WINDOW)
                  );

  /* Set window output */
  STM32_MODIFY_REG(*preg,
                   COMP_CFGR_WINOUT,
                   (window_output & LL_COMP_WINDOW_OUT_SETTING_MASK)
                  );
}

/**
  * @brief  Get window output of a pair of comparators instances
  *         (2 consecutive COMP instances COMP<x> and COMP<x+1>).
  * @rmtoll
  *  CFGR     WINOUT         LL_COMP_GetCommonWindowOutput
  * @param  p_comp_common Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref LL_COMP_COMMON_INSTANCE() ).
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_INDEPT
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_ODD
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_EVEN
  *         @arg @ref LL_COMP_WINDOW_OUTPUT_XOR_BOTH
  */
__STATIC_INLINE uint32_t LL_COMP_GetCommonWindowOutput(const COMP_Common_TypeDef *p_comp_common)
{
  const uint32_t window_output_comp_odd = (uint32_t)STM32_READ_BIT(p_comp_common->CFGR_ODD, COMP_CFGR_WINOUT);
  const uint32_t window_output_comp_even = (uint32_t)STM32_READ_BIT(p_comp_common->CFGR_EVEN, COMP_CFGR_WINOUT);

  /* Construct value corresponding to LL_COMP_WINDOWOUTPUT_xxx */
  return (uint32_t)(window_output_comp_odd
                    | window_output_comp_even
                    | ((window_output_comp_even >> COMP_CFGR_WINOUT_Pos) * LL_COMP_WINDOW_COMP_EVEN_REGOFFSET_MASK)
                    | (window_output_comp_odd + window_output_comp_even));
}
/**
  * @}
  */

#endif /* COMP_WINDOW_MODE_SUPPORT */

/** @defgroup COMP_LL_EF_Configuration_comparator_inputs Configuration of comparator inputs
  * @{
  */

/**
  * @brief  Set comparator inputs minus (inverting) and plus (non-inverting).
  * @rmtoll
  *  CFGR     INPSEL         LL_COMP_ConfigInputs \n
  *  CFGR     INMSEL         LL_COMP_ConfigInputs \n
  *  CFGR     BRGEN          LL_COMP_ConfigInputs \n
  *  CFGR     SCALEN         LL_COMP_ConfigInputs
  * @param  p_comp Comparator instance
  * @param  input_minus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1      (1)(3)(4)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2      (2)(5)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC2_CH1      (5)(8)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC2_CH2      (6)(7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH1      (7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH2      (1)(6)(8)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH1      (2)(3)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH2      (4)(5)
  *         @arg @ref LL_COMP_INPUT_MINUS_COMP_PAIR
  *
  *         (1, ..., 8) On STM32H7P, parameter available on COMP instance corresponding to this number.
  * @param  input_plus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  * @note   On this STM32 series, a voltage scaler is used
  *         when COMP input is based on VrefInt (VrefInt or subdivision
  *         of VrefInt):
  *         Voltage scaler requires a delay for voltage stabilization.
  *         Refer to device datasheet, parameter "tSTART_SCALER".
  */
__STATIC_INLINE void LL_COMP_ConfigInputs(COMP_TypeDef *p_comp, uint32_t input_minus, uint32_t input_plus)
{
  uint32_t input_minus_reg_val;

  if ((input_minus & (COMP_CFGR_INMSEL | COMP_CFGR_SCALEN | COMP_CFGR_BRGEN)) == 0UL) /* Specific case: input to DAC */
  {
    input_minus_reg_val = (((((uint32_t)LL_COMP_OUTPUT_INPUT_MINUS_DAC_LUT[((input_minus & LL_COMP_INPUT_MINUS_DAC_MASK)
                                                                            >> LL_COMP_INPUT_MINUS_DAC_OFFSET) & 0x7U]
                              >> (LL_COMP_INSTANCE_LUT_INDEX(p_comp) * 2U))
                             & LL_COMP_INPUT_MINUS_DAC_BF_MASK) + LL_COMP_INPUT_MINUS_DAC_BF_START)
                           << COMP_CFGR_INMSEL_Pos);
  }
  else /* Generic case: COMP input minus to GPIO */
  {
    input_minus_reg_val = input_minus; /* Keep parameter value */
  }

  STM32_MODIFY_REG(p_comp->CFGR,
                   COMP_CFGR_INMSEL | COMP_CFGR_INPSEL | COMP_CFGR_SCALEN | COMP_CFGR_BRGEN,
                   input_minus_reg_val | input_plus);
}

/**
  * @brief  Set comparator input plus.
  * @rmtoll
  *  CFGR     INPSEL         LL_COMP_SetInputPlus
  * @param  p_comp Comparator instance
  * @param  input_plus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  */
__STATIC_INLINE void LL_COMP_SetInputPlus(COMP_TypeDef *p_comp, uint32_t input_plus)
{
  STM32_MODIFY_REG(p_comp->CFGR, COMP_CFGR_INPSEL, input_plus);
}

/**
  * @brief  Get comparator input plus.
  * @rmtoll
  *  CSR      INPSEL         LL_COMP_GetInputPlus
  * @param  p_comp Comparator instance
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputPlus(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(STM32_READ_BIT(p_comp->CFGR, COMP_CFGR_INPSEL));
}

/**
  * @brief  Set comparator input minus.
  * @rmtoll
  *  CFGR     INMSEL         LL_COMP_SetInputMinus \n
  *  CFGR     BRGEN          LL_COMP_SetInputMinus \n
  *  CFGR     SCALEN         LL_COMP_SetInputMinus
  * @param  p_comp Comparator instance
  * @param  input_minus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1      (1)(3)(4)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2      (2)(5)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC2_CH1      (5)(8)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC2_CH2      (6)(7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH1      (7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH2      (1)(6)(8)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH1      (2)(3)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH2      (4)(5)
  *         @arg @ref LL_COMP_INPUT_MINUS_COMP_PAIR
  *
  *         (1, ..., 8) On STM32H7P, parameter available on COMP instance corresponding to this number.
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  */
__STATIC_INLINE void LL_COMP_SetInputMinus(COMP_TypeDef *p_comp, uint32_t input_minus)
{
  uint32_t input_minus_reg_val;

  if ((input_minus & (COMP_CFGR_INMSEL | COMP_CFGR_SCALEN | COMP_CFGR_BRGEN)) == 0UL) /* Specific case: input to DAC */
  {
    input_minus_reg_val = (((((uint32_t)LL_COMP_OUTPUT_INPUT_MINUS_DAC_LUT[((input_minus & LL_COMP_INPUT_MINUS_DAC_MASK)
                                                                            >> LL_COMP_INPUT_MINUS_DAC_OFFSET) & 0x7U]
                              >> (LL_COMP_INSTANCE_LUT_INDEX(p_comp) * 2U))
                             & LL_COMP_INPUT_MINUS_DAC_BF_MASK) + LL_COMP_INPUT_MINUS_DAC_BF_START)
                           << COMP_CFGR_INMSEL_Pos);
  }
  else /* Generic case: COMP input minus to GPIO */
  {
    input_minus_reg_val = input_minus; /* Keep parameter value */
  }

  STM32_MODIFY_REG(p_comp->CFGR, COMP_CFGR_INMSEL | COMP_CFGR_SCALEN | COMP_CFGR_BRGEN, input_minus_reg_val);
}

/**
  * @brief  Get comparator input minus.
  * @rmtoll
  *  CFGR     INMSEL         LL_COMP_GetInputMinus \n
  *  CFGR     BRGEN          LL_COMP_GetInputMinus \n
  *  CFGR     SCALEN         LL_COMP_GetInputMinus
  * @param  p_comp Comparator instance
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1      (1)(3)(4)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2      (2)(5)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC2_CH1      (5)(8)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC2_CH2      (6)(7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH1      (7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH2      (1)(6)(8)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH1      (2)(3)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH2      (4)(5)
  *         @arg @ref LL_COMP_INPUT_MINUS_COMP_PAIR
  *
  *         (1, ..., 8) On STM32H7P, parameter available on COMP instance corresponding to this number.
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputMinus(const COMP_TypeDef *p_comp)
{
  uint32_t input_minus_reg_val = STM32_READ_BIT(p_comp->CFGR, COMP_CFGR_INMSEL | COMP_CFGR_SCALEN | COMP_CFGR_BRGEN);
  uint32_t bitfield_inmsel = ((input_minus_reg_val & COMP_CFGR_INMSEL) >> COMP_CFGR_INMSEL_Pos);
  uint32_t index_lut;

  /* Specific case: COMP input minus to DAC */
  if ((bitfield_inmsel >= LL_COMP_INPUT_MINUS_DAC_BF_START)
      && (bitfield_inmsel <= LL_COMP_INPUT_MINUS_DAC_BF_END))
  {
    /* Parse look up table until match of register value and COMP instance */
    for (index_lut = 0; index_lut < LL_COMP_OUTPUT_INPUT_MINUS_DAC_LUT_COUNT; index_lut++)
    {
      if ((((uint32_t)LL_COMP_OUTPUT_INPUT_MINUS_DAC_LUT[index_lut] >> (LL_COMP_INSTANCE_LUT_INDEX(p_comp) * 2U))
           & LL_COMP_INPUT_MINUS_DAC_BF_MASK) == (bitfield_inmsel - LL_COMP_INPUT_MINUS_DAC_BF_START))
      {
        input_minus_reg_val = (index_lut << LL_COMP_INPUT_MINUS_DAC_OFFSET);
        break;
      }
    }
  }

  return input_minus_reg_val;
}

/**
  * @brief  Get comparator input voltage scaler bridge configuration.
  * @rmtoll
  *  CFGR     BRGEN          LL_COMP_IsInputScalerEnabled \n
  *  CFGR     SCALEN         LL_COMP_IsInputScalerEnabled
  * @param  p_comp Comparator instance
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  * @retval State of scaler bridge configuration (value "1" for enabled, value "0" for disabled).
  */
__STATIC_INLINE uint32_t LL_COMP_IsInputScalerEnabled(const COMP_TypeDef *p_comp)
{
  return ((STM32_READ_BIT(p_comp->CFGR, (COMP_CFGR_SCALEN | COMP_CFGR_BRGEN)) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Set comparator input hysteresis.
  * @rmtoll
  *  CFGR     HYST           LL_COMP_SetInputHysteresis
  * @param  p_comp Comparator instance
  * @param  input_hysteresis This parameter can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_NONE
  *         @arg @ref LL_COMP_HYSTERESIS_LOW
  *         @arg @ref LL_COMP_HYSTERESIS_MEDIUM
  *         @arg @ref LL_COMP_HYSTERESIS_HIGH
  * @note   Hysteresys applied on comparator input minus.
  */
__STATIC_INLINE void LL_COMP_SetInputHysteresis(COMP_TypeDef *p_comp, uint32_t input_hysteresis)
{
  STM32_MODIFY_REG(p_comp->CFGR, COMP_CFGR_HYST, input_hysteresis);
}

/**
  * @brief  Get comparator instance hysteresis mode of the minus (inverting) input.
  * @rmtoll
  *  CFGR     HYST           LL_COMP_GetInputHysteresis
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_NONE
  *         @arg @ref LL_COMP_HYSTERESIS_LOW
  *         @arg @ref LL_COMP_HYSTERESIS_MEDIUM
  *         @arg @ref LL_COMP_HYSTERESIS_HIGH
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputHysteresis(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(STM32_READ_BIT(p_comp->CFGR, COMP_CFGR_HYST));
}

/**
  * @brief  Set comparator analog filtering (deglitcher).
  * @rmtoll
  *  CFGR     DGLT           LL_COMP_SetFilteringAnalog
  * @param  p_comp Comparator instance
  * @param  filt_deglitch This parameter can be one of the following values:
  *         @arg @ref LL_COMP_FILT_ANA_DISABLE
  *         @arg @ref LL_COMP_FILT_ANA_ENABLE
  * @note   Deglitcher increases propagation delay of the comparator with few nanoseconds (refer to device datasheet),
  *         reducing potential output oscillations.
  */
__STATIC_INLINE void LL_COMP_SetFilteringAnalog(COMP_TypeDef *p_comp, uint32_t filt_analog)
{
  STM32_MODIFY_REG(p_comp->CFGR, COMP_CFGR_DGLT, filt_analog);
}

/**
  * @brief  Get comparator analog filtering (deglitcher).
  * @rmtoll
  *  CFGR     DGLT           LL_COMP_GetFilteringAnalog
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_FILT_ANA_DISABLE
  *         @arg @ref LL_COMP_FILT_ANA_ENABLE
  */
__STATIC_INLINE uint32_t LL_COMP_GetFilteringAnalog(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(STM32_READ_BIT(p_comp->CFGR, COMP_CFGR_DGLT));
}

/**
  * @brief  Set comparator digital filtering parameters (kernel clock prescaler, samples).
  * @rmtoll
  *  FLTR     FSEL           LL_COMP_SetFilteringDigital \n
  *  FLTR     DGLT           LL_COMP_SetFilteringDigital
  * @param  p_comp Comparator instance
  * @param  filt_dig_params This parameter can be one of the following values:
  *         @arg @ref LL_COMP_FILT_DIG_DISABLE
  *         @arg @ref LL_COMP_FILT_DIG_DIV1_SMP2
  *         @arg @ref LL_COMP_FILT_DIG_DIV1_SMP4
  *         @arg @ref LL_COMP_FILT_DIG_DIV1_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV2_SMP2
  *         @arg @ref LL_COMP_FILT_DIG_DIV2_SMP4
  *         @arg @ref LL_COMP_FILT_DIG_DIV2_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV2_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV4_SMP2
  *         @arg @ref LL_COMP_FILT_DIG_DIV4_SMP4
  *         @arg @ref LL_COMP_FILT_DIG_DIV4_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV4_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV8_SMP2
  *         @arg @ref LL_COMP_FILT_DIG_DIV8_SMP4
  *         @arg @ref LL_COMP_FILT_DIG_DIV8_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV8_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV16_SMP5
  *         @arg @ref LL_COMP_FILT_DIG_DIV16_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV16_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV32_SMP5
  *         @arg @ref LL_COMP_FILT_DIG_DIV32_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV32_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV64_SMP5
  *         @arg @ref LL_COMP_FILT_DIG_DIV64_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV64_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV128_SMP5
  *         @arg @ref LL_COMP_FILT_DIG_DIV128_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV128_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV256_SMP5
  *         @arg @ref LL_COMP_FILT_DIG_DIV256_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV256_SMP8
  * @note   Digital filter can filter low frequency noise on comparator inputs, based on a clock and count number
  *         of successive samples with stable state.
  */
__STATIC_INLINE void LL_COMP_SetFilteringDigital(COMP_TypeDef *p_comp, uint32_t filt_dig_params)
{
  STM32_MODIFY_REG(p_comp->FLTR, (COMP_FLTR_FSEL | COMP_FLTR_FPSC), filt_dig_params);
}

/**
  * @brief  Get comparator digital filtering parameters (kernel clock prescaler, samples).
  *  FLTR     FSEL           LL_COMP_SetFilteringDigital \n
  *  FLTR     DGLT           LL_COMP_SetFilteringDigital
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_FILT_DIG_DISABLE
  *         @arg @ref LL_COMP_FILT_DIG_DIV1_SMP2
  *         @arg @ref LL_COMP_FILT_DIG_DIV1_SMP4
  *         @arg @ref LL_COMP_FILT_DIG_DIV1_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV2_SMP2
  *         @arg @ref LL_COMP_FILT_DIG_DIV2_SMP4
  *         @arg @ref LL_COMP_FILT_DIG_DIV2_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV2_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV4_SMP2
  *         @arg @ref LL_COMP_FILT_DIG_DIV4_SMP4
  *         @arg @ref LL_COMP_FILT_DIG_DIV4_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV4_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV8_SMP2
  *         @arg @ref LL_COMP_FILT_DIG_DIV8_SMP4
  *         @arg @ref LL_COMP_FILT_DIG_DIV8_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV8_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV16_SMP5
  *         @arg @ref LL_COMP_FILT_DIG_DIV16_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV16_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV32_SMP5
  *         @arg @ref LL_COMP_FILT_DIG_DIV32_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV32_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV64_SMP5
  *         @arg @ref LL_COMP_FILT_DIG_DIV64_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV64_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV128_SMP5
  *         @arg @ref LL_COMP_FILT_DIG_DIV128_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV128_SMP8
  *         @arg @ref LL_COMP_FILT_DIG_DIV256_SMP5
  *         @arg @ref LL_COMP_FILT_DIG_DIV256_SMP6
  *         @arg @ref LL_COMP_FILT_DIG_DIV256_SMP8
  */
__STATIC_INLINE uint32_t LL_COMP_GetFilteringDigital(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(STM32_READ_BIT(p_comp->FLTR, (COMP_FLTR_FSEL | COMP_FLTR_FPSC)));
}

/** @defgroup COMP_LL_EF_Configuration_comparator_output Configuration of comparator output
  * @{
  */

/**
  * @brief  Set comparator instance output polarity.
  * @rmtoll
  *  CFGR     POLARITY       LL_COMP_SetOutputPolarity
  * @param  p_comp Comparator instance
  * @param  output_polarity This parameter can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  */
__STATIC_INLINE void LL_COMP_SetOutputPolarity(COMP_TypeDef *p_comp, uint32_t output_polarity)
{
  STM32_MODIFY_REG(p_comp->CFGR, COMP_CFGR_POLARITY, output_polarity);
}

/**
  * @brief  Get comparator instance output polarity.
  * @rmtoll
  *  CFGR     POLARITY       LL_COMP_GetOutputPolarity
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputPolarity(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(STM32_READ_BIT(p_comp->CFGR, COMP_CFGR_POLARITY));
}

/**
  * @brief  Set comparator instance blanking source.
  * @rmtoll
  *  CFGR     BLANKING       LL_COMP_SetOutputBlankingSource
  * @param  p_comp Comparator instance
  * @param  blanking_source This parameter can be one of the following values:
  *         LL_COMP_BLANKINGSRC_NONE
  *         LL_COMP_BLANKINGSRC_TIM1_OC5
  *         LL_COMP_BLANKINGSRC_TIM1_OC6 (3)(4)(5)(7)
  *         LL_COMP_BLANKINGSRC_TIM1_OC7 (1)(2)(5)(6)
  *         LL_COMP_BLANKINGSRC_TIM2_OC3 (1)(2)(3)(4)
  *         LL_COMP_BLANKINGSRC_TIM2_OC4 (5)(6)
  *         LL_COMP_BLANKINGSRC_TIM9_OC1 (1)(2)(7)(8)
  *         LL_COMP_BLANKINGSRC_TIM3_OC3 (1)(2)(3)(4)(5)(6)
  *         LL_COMP_BLANKINGSRC_TIM3_OC4 (7)(8)
  *         LL_COMP_BLANKINGSRC_TIM4_OC3
  *         LL_COMP_BLANKINGSRC_TIM8_OC5
  *         LL_COMP_BLANKINGSRC_TIM8_OC7 (1)(2)(5)(6)
  *         LL_COMP_BLANKINGSRC_TIM8_OC6 (3)(4)(7)(8)
  *         LL_COMP_BLANKINGSRC_TIM12_OC1
  *         LL_COMP_BLANKINGSRC_TIM20_OC5
  *         LL_COMP_BLANKINGSRC_TIM20_OC7 (1)(2)(5)(6)
  *         LL_COMP_BLANKINGSRC_TIM20_OC6 (3)(4)(7)(8)
  *         LL_COMP_BLANKINGSRC_TIM15_OC1
  *         LL_COMP_BLANKINGSRC_TIM15_OC2
  *
  *         (1, ..., 8) On STM32H7P, parameter available on COMP instance corresponding to this number.
  * @note   Availability of parameters of blanking source from peripherals
  *         depends on their availability on the selected device.
  * @note   Blanking source can be specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  */
__STATIC_INLINE void LL_COMP_SetOutputBlankingSource(COMP_TypeDef *p_comp, uint32_t blanking_source)
{
  /* Check parameter value to ensure table address compliance */
  if (blanking_source < LL_COMP_OUTPUT_BLANK_INST_LUT_COUNT)
  {
    uint32_t blk_src_reg_val = LL_COMP_OUTPUT_BLANK_INST_LUT[blanking_source].reg_val;

    /* Update specific blanking source vs comparator instance */
    if (blanking_source == LL_COMP_BLANKINGSRC_TIM9_OC1)
    {
      if ((p_comp == COMP1) || (p_comp == COMP2))
      {
        blk_src_reg_val = LL_COMP_BLANKINGSRC_TIM9_OC1_COMP12;
      }
      else if ((p_comp == COMP7) || (p_comp == COMP8))
      {
        blk_src_reg_val = LL_COMP_BLANKINGSRC_TIM9_OC1_COMP78;
      }
      else
      {
        /* No update */
      }
    }

    STM32_MODIFY_REG(p_comp->CFGR, COMP_CFGR_BLANKING, blk_src_reg_val << COMP_CFGR_BLANKING_Pos);
  }
}

/**
  * @brief  Get comparator instance blanking source.
  * @rmtoll
  *  CSR      BLANKSEL       LL_COMP_GetOutputBlankingSource
  * @param  p_comp Comparator instance
  * @note   Availability of parameters of blanking source from peripherals
  *         depends on their availability on the selected device.
  * @note   Blanking source can be specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @retval Returned value can be one of the following values:
  *         LL_COMP_BLANKINGSRC_NONE
  *         LL_COMP_BLANKINGSRC_TIM1_OC5
  *         LL_COMP_BLANKINGSRC_TIM1_OC6 (3)(4)(5)(7)
  *         LL_COMP_BLANKINGSRC_TIM1_OC7 (1)(2)(5)(6)
  *         LL_COMP_BLANKINGSRC_TIM2_OC3 (1)(2)(3)(4)
  *         LL_COMP_BLANKINGSRC_TIM2_OC4 (5)(6)
  *         LL_COMP_BLANKINGSRC_TIM9_OC1 (1)(2)(7)(8)
  *         LL_COMP_BLANKINGSRC_TIM3_OC3 (1)(2)(3)(4)(5)(6)
  *         LL_COMP_BLANKINGSRC_TIM3_OC4 (7)(8)
  *         LL_COMP_BLANKINGSRC_TIM4_OC3
  *         LL_COMP_BLANKINGSRC_TIM8_OC5
  *         LL_COMP_BLANKINGSRC_TIM8_OC7 (1)(2)(5)(6)
  *         LL_COMP_BLANKINGSRC_TIM8_OC6 (3)(4)(7)(8)
  *         LL_COMP_BLANKINGSRC_TIM12_OC1
  *         LL_COMP_BLANKINGSRC_TIM20_OC5
  *         LL_COMP_BLANKINGSRC_TIM20_OC7 (1)(2)(5)(6)
  *         LL_COMP_BLANKINGSRC_TIM20_OC6 (3)(4)(7)(8)
  *         LL_COMP_BLANKINGSRC_TIM15_OC1
  *         LL_COMP_BLANKINGSRC_TIM15_OC2
  *
  *         (1, ..., 8) On STM32H7P, parameter available on COMP instance corresponding to this number.
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputBlankingSource(const COMP_TypeDef *p_comp)
{
  uint32_t blk_src_reg_val = (STM32_READ_BIT(p_comp->CFGR, COMP_CFGR_BLANKING) >> COMP_CFGR_BLANKING_Pos);
  uint32_t instance_bitfield_mask = (1UL << LL_COMP_INSTANCE_LUT_INDEX(p_comp));
  uint32_t index_lut = 0UL;

  /* Manage specific blanking source vs comparator instance */
  if ((blk_src_reg_val == LL_COMP_BLANKINGSRC_TIM9_OC1_COMP12)
      || (blk_src_reg_val == LL_COMP_BLANKINGSRC_TIM9_OC1_COMP78))
  {
    if ((p_comp == COMP1) || (p_comp == COMP2))
    {
      index_lut = LL_COMP_BLANKINGSRC_TIM9_OC1;
    }
    else if ((p_comp == COMP7) || (p_comp == COMP8))
    {
      index_lut = LL_COMP_BLANKINGSRC_TIM9_OC1;
    }
    else
    {
      /* No update */
    }
  }

  if (index_lut == 0UL)
  {
    /* Parse look up table until match of register value and COMP instance */
    for (index_lut = 0; index_lut < LL_COMP_OUTPUT_BLANK_INST_LUT_COUNT; index_lut++)
    {
      if (blk_src_reg_val == LL_COMP_OUTPUT_BLANK_INST_LUT[index_lut].reg_val)
      {
        if (((uint32_t)LL_COMP_OUTPUT_BLANK_INST_LUT[index_lut].inst & instance_bitfield_mask) != 0UL)
        {
          break;
        }
      }
    }
  }

  return index_lut;
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Operation Operation on comparator instance
  * @{
  */

/**
  * @brief  Enable comparator instance.
  * @rmtoll
  *  CFGR     EN             LL_COMP_Enable
  * @param  p_comp Comparator instance
  * @note   After enable, comparator requires a delay to reach reach propagation delay specification,
  *         refer to LL_COMP_DELAY_STARTUP_US.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  *         To get scaler bridge configuration, refer to @ref LL_COMP_IsInputScalerEnabled().
  */
__STATIC_INLINE void LL_COMP_Enable(COMP_TypeDef *p_comp)
{
  STM32_SET_BIT(p_comp->CFGR, COMP_CFGR_EN);
}

/**
  * @brief  Disable comparator instance.
  * @rmtoll
  *  CFGR     EN             LL_COMP_Disable
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_Disable(COMP_TypeDef *p_comp)
{
  STM32_CLEAR_BIT(p_comp->CFGR, COMP_CFGR_EN);
}

/**
  * @brief  Get comparator enable state.
  * @rmtoll
  *  CSR      EN             LL_COMP_IsEnabled
  * @param  p_comp Comparator instance
  * @retval Value "0" for comparator disabled, value "1" for comparator enabled.
  */
__STATIC_INLINE uint32_t LL_COMP_IsEnabled(const COMP_TypeDef *p_comp)
{
  return ((STM32_READ_BIT(p_comp->CFGR, COMP_CFGR_EN) == (COMP_CFGR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Lock comparator instance.
  * @rmtoll
  *  CFGR     LOCK           LL_COMP_Lock
  * @param  p_comp Comparator instance
  * @note   Once locked, comparator configuration can be accessed in read-only.
  * @note   The only way to unlock the comparator is a device system reset.
  */
__STATIC_INLINE void LL_COMP_Lock(COMP_TypeDef *p_comp)
{
  STM32_SET_BIT(p_comp->CFGR, COMP_CFGR_LOCK);
}

/**
  * @brief  Get comparator lock state.
  * @rmtoll
  *  CFGR     LOCK           LL_COMP_IsLocked
  * @param  p_comp Comparator instance
  * @note   Once locked, comparator configuration can be accessed in read-only.
  * @note   The only way to unlock the comparator is a device system reset.
  * @retval Value "0" for comparator unlocked, value "1" for comparator locked.
  */
__STATIC_INLINE uint32_t LL_COMP_IsLocked(const COMP_TypeDef *p_comp)
{
  return ((STM32_READ_BIT(p_comp->CFGR, COMP_CFGR_LOCK) == (COMP_CFGR_LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Read comparator instance output level.
  * @rmtoll
  *  SR       CVAL           LL_COMP_ReadOutputLevel
  * @param  p_comp Comparator instance
  * @note   The comparator output level depends on the selected polarity
  *         (Refer to function @ref LL_COMP_SetOutputPolarity()).
  *         If the comparator polarity is not inverted:
  *          - Comparator output is low when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is high when the input plus
  *            is at a higher voltage than the input minus
  *         If the comparator polarity is inverted:
  *          - Comparator output is high when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is low when the input plus
  *            is at a higher voltage than the input minus
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_LOW
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_HIGH
  */
__STATIC_INLINE uint32_t LL_COMP_ReadOutputLevel(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(STM32_READ_BIT(p_comp->SR, COMP_SR_CVAL) >> COMP_SR_CVAL_Pos);
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_FLAG_Management Comparator flag Management
  * @{
  */

/**
  * @brief  Get comparator output trigger flag (latched).
  * @rmtoll
  *  SR       CIF            LL_COMP_IsActiveFlag_OutputTrig
  * @param  p_comp Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsActiveFlag_OutputTrig(const COMP_TypeDef *p_comp)
{
  return ((STM32_READ_BIT(p_comp->SR, COMP_SR_CIF) == (COMP_SR_CIF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear comparator comparator output trigger flag (latched).
  * @rmtoll
  *  ICFR     CCIF           LL_COMP_ClearFlag_OutputTrig
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_ClearFlag_OutputTrig(COMP_TypeDef *p_comp)
{
  STM32_SET_BIT(p_comp->ICFR, COMP_ICFR_CCIF);
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_IT_Management Comparator IT management
  * @{
  */

/**
  * @brief  Enable comparator output trigger interrupt.
  * @rmtoll
  *  CFGR     ITEN           LL_COMP_EnableIT_OutputTrig
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_EnableIT_OutputTrig(COMP_TypeDef *p_comp)
{
  STM32_SET_BIT(p_comp->CFGR, COMP_CFGR_ITEN);
}

/**
  * @brief  Disable comparator output trigger interrupt.
  * @rmtoll
  *  CFGR     ITEN           LL_COMP_DisableIT_OutputTrig
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_DisableIT_OutputTrig(COMP_TypeDef *p_comp)
{
  STM32_CLEAR_BIT(p_comp->CFGR, COMP_CFGR_ITEN);
}

/**
  * @brief  Get comparator output trigger interrupt state.
  * @rmtoll
  *  CFGR     ITEN           LL_COMP_IsEnabledIT_OutputTrig
  * @param  p_comp Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsEnabledIT_OutputTrig(const COMP_TypeDef *p_comp)
{
  return ((STM32_READ_BIT(p_comp->CFGR, COMP_CFGR_ITEN) == (COMP_CFGR_ITEN)) ? 1UL : 0UL);
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

#endif /* STM32H7PXX_LL_COMP_H */
