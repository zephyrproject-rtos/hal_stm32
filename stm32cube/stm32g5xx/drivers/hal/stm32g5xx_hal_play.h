/**
  ******************************************************************************
  * @file    stm32g5xx_hal_play.h
  * @brief   Header file of PLAY HAL module.
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
#ifndef STM32G5XX_HAL_PLAY_H
#define STM32G5XX_HAL_PLAY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

#if defined(PLAY1)
#include "stm32g5xx_ll_play.h"

/** @defgroup PLAY PLAY
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PLAY_Exported_Constants HAL PLAY Constants
  * @{
  */

/** @defgroup PLAY_Global_definition  PLAY Global definition
  * @{
  */

#define HAL_PLAY_LUT_INPUT_SOURCE_NBR         LL_PLAY_LUT_INPUT_SOURCE_NBR           /*!< Number of input sources per lookup table */
#define HAL_PLAY_LUT_TRUTH_TABLE_VALUE_MAX    (LL_PLAY_LUT_TRUTH_TABLE_VALUE_MAX)    /*!< Maximum Lookup table value               */
#define HAL_PLAY_INPUT_FILTER_WIDTH_VALUE_MAX (LL_PLAY_INPUT_FILTER_WIDTH_VALUE_MAX) /*!< Maximum pulse width value                */

/**
  * @}
  */

/** @defgroup PLAY_Software_Trigger_ID  PLAY Software Trigger
  * @{
  */

#define HAL_PLAY_SWTRIG0    LL_PLAY_SWTRIG0    /*!< PLAY Software trigger 0        */
#define HAL_PLAY_SWTRIG1    LL_PLAY_SWTRIG1    /*!< PLAY Software trigger 1        */
#define HAL_PLAY_SWTRIG2    LL_PLAY_SWTRIG2    /*!< PLAY Software trigger 2        */
#define HAL_PLAY_SWTRIG3    LL_PLAY_SWTRIG3    /*!< PLAY Software trigger 3        */
#define HAL_PLAY_SWTRIG4    LL_PLAY_SWTRIG4    /*!< PLAY Software trigger 4        */
#define HAL_PLAY_SWTRIG5    LL_PLAY_SWTRIG5    /*!< PLAY Software trigger 5        */
#define HAL_PLAY_SWTRIG6    LL_PLAY_SWTRIG6    /*!< PLAY Software trigger 6        */
#define HAL_PLAY_SWTRIG7    LL_PLAY_SWTRIG7    /*!< PLAY Software trigger 7        */
#define HAL_PLAY_SWTRIG8    LL_PLAY_SWTRIG8    /*!< PLAY Software trigger 8        */
#define HAL_PLAY_SWTRIG9    LL_PLAY_SWTRIG9    /*!< PLAY Software trigger 9        */
#define HAL_PLAY_SWTRIG10   LL_PLAY_SWTRIG10   /*!< PLAY Software trigger 10       */
#define HAL_PLAY_SWTRIG11   LL_PLAY_SWTRIG11   /*!< PLAY Software trigger 11       */
#define HAL_PLAY_SWTRIG12   LL_PLAY_SWTRIG12   /*!< PLAY Software trigger 12       */
#define HAL_PLAY_SWTRIG13   LL_PLAY_SWTRIG13   /*!< PLAY Software trigger 13       */
#define HAL_PLAY_SWTRIG14   LL_PLAY_SWTRIG14   /*!< PLAY Software trigger 14       */
#define HAL_PLAY_SWTRIG15   LL_PLAY_SWTRIG15   /*!< PLAY Software trigger 15       */
#define HAL_PLAY_SWTRIG_ALL LL_PLAY_SWTRIG_ALL /*!< PLAY Software triggers 0 to 15 */

/**
  * @}
  */

/** @defgroup PLAY_LookUp_Table_Output  PLAY Lookup table Output Reference
  * @{
  */

#define HAL_PLAY_LUT0_OUT_DIRECT        LL_PLAY_LUT0_OUT_DIRECT        /*!< PLAY direct output of LUT 0             */
#define HAL_PLAY_LUT1_OUT_DIRECT        LL_PLAY_LUT1_OUT_DIRECT        /*!< PLAY direct output of LUT 1             */
#define HAL_PLAY_LUT2_OUT_DIRECT        LL_PLAY_LUT2_OUT_DIRECT        /*!< PLAY direct output of LUT 2             */
#define HAL_PLAY_LUT3_OUT_DIRECT        LL_PLAY_LUT3_OUT_DIRECT        /*!< PLAY direct output of LUT 3             */
#define HAL_PLAY_LUT4_OUT_DIRECT        LL_PLAY_LUT4_OUT_DIRECT        /*!< PLAY direct output of LUT 4             */
#define HAL_PLAY_LUT5_OUT_DIRECT        LL_PLAY_LUT5_OUT_DIRECT        /*!< PLAY direct output of LUT 5             */
#define HAL_PLAY_LUT6_OUT_DIRECT        LL_PLAY_LUT6_OUT_DIRECT        /*!< PLAY direct output of LUT 6             */
#define HAL_PLAY_LUT7_OUT_DIRECT        LL_PLAY_LUT7_OUT_DIRECT        /*!< PLAY direct output of LUT 7             */
#define HAL_PLAY_LUT8_OUT_DIRECT        LL_PLAY_LUT8_OUT_DIRECT        /*!< PLAY direct output of LUT 8             */
#define HAL_PLAY_LUT9_OUT_DIRECT        LL_PLAY_LUT9_OUT_DIRECT        /*!< PLAY direct output of LUT 9             */
#define HAL_PLAY_LUT10_OUT_DIRECT       LL_PLAY_LUT10_OUT_DIRECT       /*!< PLAY direct output of LUT 10            */
#define HAL_PLAY_LUT11_OUT_DIRECT       LL_PLAY_LUT11_OUT_DIRECT       /*!< PLAY direct output of LUT 11            */
#define HAL_PLAY_LUT12_OUT_DIRECT       LL_PLAY_LUT12_OUT_DIRECT       /*!< PLAY direct output of LUT 12            */
#define HAL_PLAY_LUT13_OUT_DIRECT       LL_PLAY_LUT13_OUT_DIRECT       /*!< PLAY direct output of LUT 13            */
#define HAL_PLAY_LUT14_OUT_DIRECT       LL_PLAY_LUT14_OUT_DIRECT       /*!< PLAY direct output of LUT 14            */
#define HAL_PLAY_LUT15_OUT_DIRECT       LL_PLAY_LUT15_OUT_DIRECT       /*!< PLAY direct output of LUT 15            */
#define HAL_PLAY_LUT_ALL_OUT_DIRECT     LL_PLAY_LUT_ALL_OUT_DIRECT     /*!< PLAY direct outputs of LUTs 0 to 15     */

#define HAL_PLAY_LUT0_OUT_REGISTERED    LL_PLAY_LUT0_OUT_REGISTERED    /*!< PLAY registered output of LUT 0         */
#define HAL_PLAY_LUT1_OUT_REGISTERED    LL_PLAY_LUT1_OUT_REGISTERED    /*!< PLAY registered output of LUT 1         */
#define HAL_PLAY_LUT2_OUT_REGISTERED    LL_PLAY_LUT2_OUT_REGISTERED    /*!< PLAY registered output of LUT 2         */
#define HAL_PLAY_LUT3_OUT_REGISTERED    LL_PLAY_LUT3_OUT_REGISTERED    /*!< PLAY registered output of LUT 3         */
#define HAL_PLAY_LUT4_OUT_REGISTERED    LL_PLAY_LUT4_OUT_REGISTERED    /*!< PLAY registered output of LUT 4         */
#define HAL_PLAY_LUT5_OUT_REGISTERED    LL_PLAY_LUT5_OUT_REGISTERED    /*!< PLAY registered output of LUT 5         */
#define HAL_PLAY_LUT6_OUT_REGISTERED    LL_PLAY_LUT6_OUT_REGISTERED    /*!< PLAY registered output of LUT 6         */
#define HAL_PLAY_LUT7_OUT_REGISTERED    LL_PLAY_LUT7_OUT_REGISTERED    /*!< PLAY registered output of LUT 7         */
#define HAL_PLAY_LUT8_OUT_REGISTERED    LL_PLAY_LUT8_OUT_REGISTERED    /*!< PLAY registered output of LUT 8         */
#define HAL_PLAY_LUT9_OUT_REGISTERED    LL_PLAY_LUT9_OUT_REGISTERED    /*!< PLAY registered output of LUT 9         */
#define HAL_PLAY_LUT10_OUT_REGISTERED   LL_PLAY_LUT10_OUT_REGISTERED   /*!< PLAY registered output of LUT 10        */
#define HAL_PLAY_LUT11_OUT_REGISTERED   LL_PLAY_LUT11_OUT_REGISTERED   /*!< PLAY registered output of LUT 11        */
#define HAL_PLAY_LUT12_OUT_REGISTERED   LL_PLAY_LUT12_OUT_REGISTERED   /*!< PLAY registered output of LUT 12        */
#define HAL_PLAY_LUT13_OUT_REGISTERED   LL_PLAY_LUT13_OUT_REGISTERED   /*!< PLAY registered output of LUT 13        */
#define HAL_PLAY_LUT14_OUT_REGISTERED   LL_PLAY_LUT14_OUT_REGISTERED   /*!< PLAY registered output of LUT 14        */
#define HAL_PLAY_LUT15_OUT_REGISTERED   LL_PLAY_LUT15_OUT_REGISTERED   /*!< PLAY registered output of LUT 15        */
#define HAL_PLAY_LUT_ALL_OUT_REGISTERED LL_PLAY_LUT_ALL_OUT_REGISTERED /*!< PLAY registered outputs of LUTs 0 to 15 */

/**
  * @}
  */

/** @defgroup PLAY_Interco_Matrix_definition  PLAY Interco Matrix definition
  * Definitions used to encode/decode the @ref hal_play_in_source_t enumerated values
  * @{
  */

#define HAL_PLAY_INSTANCE_ID_POS (29U) /*!< Instance number field position          */
#define HAL_PLAY_IN_MUX_POS      (6U)  /*!< Input Multiplexer number field position */

#define HAL_PLAY1_INSTANCE_ID    (0x1UL << HAL_PLAY_INSTANCE_ID_POS) /*!< Value of PLAY1 in enum value */

/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PLAY_Exported_Types  HAL PLAY Types
  * @{
  */

/** @defgroup PLAY_Exported_Types_Group1  PLAY Global Enumerations
  * @{
  */

/**
  * @brief HAL PLAY instance
  */
typedef enum
{
  HAL_PLAY1 = PLAY1_BASE,  /*!< PLAY1 instance */
} hal_play_t;

/**
  * @brief  PLAY Polling Mode on Lookup Table Output Edge Trigger enumeration
  */
typedef enum
{
  HAL_PLAY_POLLING_FOR_ALL_EDGES, /*!< Polling for all edges */
  HAL_PLAY_POLLING_FOR_ANY_EDGE,  /*!< Polling for any edge  */
} hal_play_polling_edge_trigger_t;

/**
  * @brief  PLAY Software Trigger State enumeration
  */
typedef enum
{
  HAL_PLAY_SW_TRIGGER_RESET = 0U,      /*!< Software Trigger Reset state */
  HAL_PLAY_SW_TRIGGER_SET   = 0xFFFFU, /*!< Software Trigger Set state   */
} hal_play_sw_trigger_state_t;

/**
  * @}
  */

/** @defgroup PLAY_Exported_Types_Group2  PLAY Input Configuration Structure
  * @{
  */

/**
  * @brief  PLAY Input Multiplexer enumeration
  */
typedef enum
{
  HAL_PLAY_IN0  = LL_PLAY_IN0,  /*!< PLAY Input 0  */
  HAL_PLAY_IN1  = LL_PLAY_IN1,  /*!< PLAY Input 1  */
  HAL_PLAY_IN2  = LL_PLAY_IN2,  /*!< PLAY Input 2  */
  HAL_PLAY_IN3  = LL_PLAY_IN3,  /*!< PLAY Input 3  */
  HAL_PLAY_IN4  = LL_PLAY_IN4,  /*!< PLAY Input 4  */
  HAL_PLAY_IN5  = LL_PLAY_IN5,  /*!< PLAY Input 5  */
  HAL_PLAY_IN6  = LL_PLAY_IN6,  /*!< PLAY Input 6  */
  HAL_PLAY_IN7  = LL_PLAY_IN7,  /*!< PLAY Input 7  */
  HAL_PLAY_IN8  = LL_PLAY_IN8,  /*!< PLAY Input 8  */
  HAL_PLAY_IN9  = LL_PLAY_IN9,  /*!< PLAY Input 9  */
  HAL_PLAY_IN10 = LL_PLAY_IN10, /*!< PLAY Input 10 */
  HAL_PLAY_IN11 = LL_PLAY_IN11, /*!< PLAY Input 11 */
  HAL_PLAY_IN12 = LL_PLAY_IN12, /*!< PLAY Input 12 */
  HAL_PLAY_IN13 = LL_PLAY_IN13, /*!< PLAY Input 13 */
  HAL_PLAY_IN14 = LL_PLAY_IN14, /*!< PLAY Input 14 */
  HAL_PLAY_IN15 = LL_PLAY_IN15, /*!< PLAY Input 15 */
} hal_play_in_t;

/**
  * @brief  PLAY Input Multiplexer Edge Detection Mode enumeration
  */
typedef enum
{
  HAL_PLAY_EDGE_DETECTION_BYPASSED       = LL_PLAY_EDGE_DETECTION_MODE_BYPASSED,       /*!< Bypass mode                       */
  HAL_PLAY_EDGE_DETECTION_RISING         = LL_PLAY_EDGE_DETECTION_MODE_RISING,         /*!< Rising edge detection             */
  HAL_PLAY_EDGE_DETECTION_FALLING        = LL_PLAY_EDGE_DETECTION_MODE_FALLING,        /*!< Falling edge detection            */
  HAL_PLAY_EDGE_DETECTION_RISING_FALLING = LL_PLAY_EDGE_DETECTION_MODE_RISING_FALLING, /*!< Rising and falling edge detection */
} hal_play_edge_detection_mode_t;

/**
  * @brief  PLAY Input Multiplexer Source enumeration
  */
typedef enum
{
  HAL_PLAY1_IN_ADC1_AWD1_MUX7             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX7  : ADC1 AWD1             */
  HAL_PLAY1_IN_ADC1_AWD1_MUX9             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX9  : ADC1 AWD1             */
  HAL_PLAY1_IN_ADC1_AWD2_MUX8             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX8  : ADC1 AWD2             */
  HAL_PLAY1_IN_ADC2_AWD1_MUX7             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 2U), /*!< MUX7  : ADC2 AWD1             */
  HAL_PLAY1_IN_ADC2_AWD1_MUX11            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX11 : ADC2 AWD1             */
  HAL_PLAY1_IN_COMP1_OUT_MUX0             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX0  : COMP1 OUT             */
  HAL_PLAY1_IN_COMP1_OUT_MUX1             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 7U), /*!< MUX1  : COMP1 OUT             */
  HAL_PLAY1_IN_COMP2_OUT_MUX1             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX1  : COMP2 OUT             */
  HAL_PLAY1_IN_COMP2_OUT_MUX15            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX15 : COMP2 OUT             */
  HAL_PLAY1_IN_COMP3_OUT_MUX3             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 2U), /*!< MUX3  : COMP3 OUT             */
  HAL_PLAY1_IN_COMP3_OUT_MUX5             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 2U), /*!< MUX5  : COMP3 OUT             */
  HAL_PLAY1_IN_COMP4_OUT_MUX5             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX5  : COMP4 OUT             */
  HAL_PLAY1_IN_COMP5_OUT_MUX7             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX7  : COMP5 OUT             */
  HAL_PLAY1_IN_COMP6_OUT_MUX9             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX9  : COMP6 OUT             */
  HAL_PLAY1_IN_COMP7_OUT_MUX11            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 2U), /*!< MUX11 : COMP7 OUT             */
  HAL_PLAY1_IN_COMP8_OUT_MUX13            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX13 : COMP8 OUT             */
  HAL_PLAY1_IN_EVENTOUT_MUX0              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX0  : EVENTOUT              */
  HAL_PLAY1_IN_HRTIM1_ADC_TRG1_MUX1       = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX1  : HRTIM1 ADC TRG1       */
  HAL_PLAY1_IN_HRTIM1_ADC_TRG2_MUX2       = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX2  : HRTIM1 ADC TRG2       */
  HAL_PLAY1_IN_HRTIM1_CHA1_MUX10          = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 7U), /*!< MUX10 : HRTIM1 CHA1           */
  HAL_PLAY1_IN_HRTIM1_CHB1_MUX11          = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 7U), /*!< MUX11 : HRTIM1 CHB1           */
  HAL_PLAY1_IN_HRTIM1_CHC1_MUX12          = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 7U), /*!< MUX12 : HRTIM1 CHC1           */
  HAL_PLAY1_IN_HRTIM1_CHD1_MUX13          = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 7U), /*!< MUX13 : HRTIM1 CHD1           */
  HAL_PLAY1_IN_HRTIM1_CHE1_MUX14          = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 7U), /*!< MUX14 : HRTIM1 CHE1           */
  HAL_PLAY1_IN_HRTIM1_CHF1_MUX15          = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 7U), /*!< MUX15 : HRTIM1 CHF1           */
  HAL_PLAY1_IN_HRTIM1_DAC_RESET_TRG1_MUX0 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX0  : HRTIM1 DAC RESET TRG1 */
  HAL_PLAY1_IN_HRTIM1_DAC_STEP_TRG1_MUX4  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 2U), /*!< MUX4  : HRTIM1 DAC STEP TRG1  */
  HAL_PLAY1_IN_HRTIM1_OUT_SYNC2_MUX5      = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX5  : HRTIM1 OUT SYNC2      */
  HAL_PLAY1_IN_LOCKUP_MUX12               = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX12 : LOCKUP                */
  HAL_PLAY1_IN_LOCKUP_MUX15               = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX15 : LOCKUP                */
  HAL_PLAY1_IN_LPTIM1_CH1_MUX3            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX3  : LPTIM1 CH1            */
  HAL_PLAY1_IN_LPTIM1_CH1_MUX11           = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX11 : LPTIM1 CH1            */
  HAL_PLAY1_IN_LPTIM1_CH2_MUX4            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX4  : LPTIM1 CH2            */
  HAL_PLAY1_IN_LPTIM1_CH2_MUX12           = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX12 : LPTIM1 CH2            */
  HAL_PLAY1_IN_MCO1_MUX6                  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX6  : MCO1                  */
  HAL_PLAY1_IN_MCO2_MUX4                  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX4  : MCO2                  */
  HAL_PLAY1_IN_NMI_MUX11                  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX11 : NMI                   */
  HAL_PLAY1_IN_NMI_MUX13                  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX13 : NMI                   */
  HAL_PLAY1_IN_IN0_MUX0                   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX0  : IN0                   */
  HAL_PLAY1_IN_IN1_MUX1                   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX1  : IN1                   */
  HAL_PLAY1_IN_IN2_MUX2                   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX2  : IN2                   */
  HAL_PLAY1_IN_IN3_MUX3                   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX3  : IN3                   */
  HAL_PLAY1_IN_IN4_MUX4                   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX4  : IN4                   */
  HAL_PLAY1_IN_IN5_MUX5                   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX5  : IN5                   */
  HAL_PLAY1_IN_IN6_MUX6                   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX6  : IN6                   */
  HAL_PLAY1_IN_IN7_MUX7                   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX7  : IN7                   */
  HAL_PLAY1_IN_IN8_MUX8                   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX8  : IN8                   */
  HAL_PLAY1_IN_IN9_MUX9                   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX9  : IN9                   */
  HAL_PLAY1_IN_IN10_MUX10                 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX10 : IN10                  */
  HAL_PLAY1_IN_IN11_MUX11                 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX11 : IN11                  */
  HAL_PLAY1_IN_IN12_MUX12                 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX12 : IN12                  */
  HAL_PLAY1_IN_IN13_MUX13                 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX13 : IN13                  */
  HAL_PLAY1_IN_IN14_MUX14                 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX14 : IN14                  */
  HAL_PLAY1_IN_IN15_MUX15                 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 0U), /*!< MUX15 : IN15                  */
  HAL_PLAY1_IN_SPI1_MOSI_MUX6             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX6  : SPI1 MOSI             */
  HAL_PLAY1_IN_SPI1_MOSI_MUX14            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX14 : SPI1 MOSI             */
  HAL_PLAY1_IN_SPI1_NSS_MUX5              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX5  : SPI1 NSS              */
  HAL_PLAY1_IN_SPI1_NSS_MUX13             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX13 : SPI1 NSS              */
  HAL_PLAY1_IN_SPI1_SCLK_MUX7             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX7  : SPI1 SCLK             */
  HAL_PLAY1_IN_SPI1_SCLK_MUX15            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX15 : SPI1 SCLK             */
  HAL_PLAY1_IN_SPI2_MOSI_MUX2             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX2  : SPI2 MOSI             */
  HAL_PLAY1_IN_SPI2_MOSI_MUX10            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX10 : SPI2 MOSI             */
  HAL_PLAY1_IN_SPI2_NSS_MUX1              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX1  : SPI2 NSS              */
  HAL_PLAY1_IN_SPI2_NSS_MUX9              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX9  : SPI2 NSS              */
  HAL_PLAY1_IN_SPI2_SCLK_MUX3             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX3  : SPI2 SCLK             */
  HAL_PLAY1_IN_SPI2_SCLK_MUX11            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX11 : SPI2 SCLK             */
  HAL_PLAY1_IN_TIM1_OC1_MUX6              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 2U), /*!< MUX6  : TIM1 OC1              */
  HAL_PLAY1_IN_TIM1_OC5_MUX9              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX9  : TIM1 OC5              */
  HAL_PLAY1_IN_TIM1_OC6_MUX10             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX10 : TIM1 OC6              */
  HAL_PLAY1_IN_TIM1_TRGO_CKTIM_MUX8       = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 5U), /*!< MUX8  : TIM1 TRGO CKTIM       */
  HAL_PLAY1_IN_TIM2_OC3_MUX1              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX1  : TIM2 OC3              */
  HAL_PLAY1_IN_TIM2_OC4_MUX2              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX2  : TIM2 OC4              */
  HAL_PLAY1_IN_TIM2_TRGO_CKTIM_MUX0       = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX0  : TIM2 TRGO CKTIM       */
#if defined(TIM3)
  HAL_PLAY1_IN_TIM3_OC3_MUX1              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 2U), /*!< MUX1  : TIM3 OC3              */
  HAL_PLAY1_IN_TIM3_OC3_MUX5              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX5  : TIM3 OC3              */
  HAL_PLAY1_IN_TIM3_OC4_MUX2              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 2U), /*!< MUX2  : TIM3 OC4              */
  HAL_PLAY1_IN_TIM3_OC4_MUX6              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX6  : TIM3 OC4              */
  HAL_PLAY1_IN_TIM3_TRGO_CKTIM_MUX0       = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 2U), /*!< MUX0  : TIM3 TRGO CKTIM       */
  HAL_PLAY1_IN_TIM3_TRGO_CKTIM_MUX4       = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX4  : TIM3 TRGO CKTIM       */
#endif /* TIM3 */
#if defined(TIM4)
  HAL_PLAY1_IN_TIM4_OC4_MUX8              = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX8  : TIM4 OC4              */
  HAL_PLAY1_IN_TIM4_TRGO_CKTIM_MUX7       = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX7  : TIM4 TRGO CKTIM       */
#endif /* TIM4 */
  HAL_PLAY1_IN_TIM6_TRGO_CKTIM_MUX7       = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX7  : TIM6 TRGO CKTIM       */
  HAL_PLAY1_IN_TIM8_OC1_MUX10             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX10 : TIM8 OC1              */
  HAL_PLAY1_IN_TIM8_OC5_MUX13             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX13 : TIM8 OC5              */
  HAL_PLAY1_IN_TIM8_OC6_MUX14             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX14 : TIM8 OC6              */
  HAL_PLAY1_IN_TIM8_TRGO_CKTIM_MUX12      = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX12 : TIM8 TRGO CKTIM       */
  HAL_PLAY1_IN_TIM9_TRGO_CKTIM_MUX0       = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 7U), /*!< MUX0  : TIM9 TRGO CKTIM       */
  HAL_PLAY1_IN_TIM10_OC1_MUX12            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX12 : TIM10 OC1             */
  HAL_PLAY1_IN_TIM12_TRGO_CKTIM_MUX10     = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX10 : TIM12 TRGO CKTIM      */
  HAL_PLAY1_IN_TIM15_OC2_MUX6             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX6  : TIM15 OC2             */
  HAL_PLAY1_IN_TIM15_TRGO_CKTIM_MUX15     = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 6U), /*!< MUX15 : TIM15 TRGO CKTIM      */
#if defined(TIM20)
  HAL_PLAY1_IN_TIM20_OC1_MUX8             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX8  : TIM20 OC1             */
  HAL_PLAY1_IN_TIM20_OC5_MUX3             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX3  : TIM20 OC5             */
  HAL_PLAY1_IN_TIM20_OC6_MUX4             = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX4  : TIM20 OC6             */
  HAL_PLAY1_IN_TIM20_TRGO_CKTIM_MUX2      = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX2  : TIM20 TRGO CKTIM      */
#endif /* TIM20 */
  HAL_PLAY1_IN_USART1_CK_MUX10            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX10 : USART1 CK             */
  HAL_PLAY1_IN_USART1_CK_MUX12            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX12 : USART1 CK             */
  HAL_PLAY1_IN_USART1_TX_OUT_MUX9         = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 1U), /*!< MUX9  : USART1 TX OUT         */
  HAL_PLAY1_IN_USART1_TX_OUT_MUX11        = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 3U), /*!< MUX11 : USART1 TX OUT         */
  HAL_PLAY1_IN_USART2_CK_MUX14            = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX14 : USART2 CK             */
  HAL_PLAY1_IN_USART2_TX_OUT_MUX13        = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 4U), /*!< MUX13 : USART2 TX OUT         */
  HAL_PLAY_IN_SOURCE_INVALID = 0U, /*!< Invalid value */
} hal_play_in_source_t;

/**
  * @brief  PLAY Input Multiplexer Configuration structure
  */
typedef struct
{
  uint32_t                       min_pulse_width; /*!< Minimum Pulse Width. Value in range 0x00 to 0xFF */
  hal_play_edge_detection_mode_t mode;            /*!< Edge Detection Mode                              */
  hal_play_in_source_t           source;          /*!< Signal source (premuxsel)                        */
} hal_play_in_config_t;

/**
  * @}
  */

/** @defgroup PLAY_Exported_Types_Group3 PLAY Lookup table Configuration Structure
  * @{
  */

/**
  * @brief  PLAY Lookup table enumeration
  */
typedef enum
{
  HAL_PLAY_LUT0  = LL_PLAY_LUT0,  /*!< PLAY Lookup table 0  */
  HAL_PLAY_LUT1  = LL_PLAY_LUT1,  /*!< PLAY Lookup table 1  */
  HAL_PLAY_LUT2  = LL_PLAY_LUT2,  /*!< PLAY Lookup table 2  */
  HAL_PLAY_LUT3  = LL_PLAY_LUT3,  /*!< PLAY Lookup table 3  */
  HAL_PLAY_LUT4  = LL_PLAY_LUT4,  /*!< PLAY Lookup table 4  */
  HAL_PLAY_LUT5  = LL_PLAY_LUT5,  /*!< PLAY Lookup table 5  */
  HAL_PLAY_LUT6  = LL_PLAY_LUT6,  /*!< PLAY Lookup table 6  */
  HAL_PLAY_LUT7  = LL_PLAY_LUT7,  /*!< PLAY Lookup table 7  */
  HAL_PLAY_LUT8  = LL_PLAY_LUT8,  /*!< PLAY Lookup table 8  */
  HAL_PLAY_LUT9  = LL_PLAY_LUT9,  /*!< PLAY Lookup table 9  */
  HAL_PLAY_LUT10 = LL_PLAY_LUT10, /*!< PLAY Lookup table 10 */
  HAL_PLAY_LUT11 = LL_PLAY_LUT11, /*!< PLAY Lookup table 11 */
  HAL_PLAY_LUT12 = LL_PLAY_LUT12, /*!< PLAY Lookup table 12 */
  HAL_PLAY_LUT13 = LL_PLAY_LUT13, /*!< PLAY Lookup table 13 */
  HAL_PLAY_LUT14 = LL_PLAY_LUT14, /*!< PLAY Lookup table 14 */
  HAL_PLAY_LUT15 = LL_PLAY_LUT15, /*!< PLAY Lookup table 15 */
} hal_play_lut_t;

/**
  * @brief  PLAY Lookup table Input enumeration
  */
typedef enum
{
  HAL_PLAY_LUT_INPUT0 = LL_PLAY_LUT_INPUT0,  /*!< PLAY Lookup table input 0 */
  HAL_PLAY_LUT_INPUT1 = LL_PLAY_LUT_INPUT1,  /*!< PLAY Lookup table input 1 */
  HAL_PLAY_LUT_INPUT2 = LL_PLAY_LUT_INPUT2,  /*!< PLAY Lookup table input 2 */
  HAL_PLAY_LUT_INPUT3 = LL_PLAY_LUT_INPUT3,  /*!< PLAY Lookup table input 3 */
} hal_play_lut_input_t;

/**
  * @brief  PLAY Lookup table Input Source enumeration
  */
typedef enum
{
  HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT      = LL_PLAY_LUT_SOURCE_LUT0_OUT_DIRECT,      /*!< PLAY Lookup table 0 direct output selected as input source      */
  HAL_PLAY_LUT_INPUT_LUT1_OUT_DIRECT      = LL_PLAY_LUT_SOURCE_LUT1_OUT_DIRECT,      /*!< PLAY Lookup table 1 direct output selected as input source      */
  HAL_PLAY_LUT_INPUT_LUT2_OUT_DIRECT      = LL_PLAY_LUT_SOURCE_LUT2_OUT_DIRECT,      /*!< PLAY Lookup table 2 direct output selected as input source      */
  HAL_PLAY_LUT_INPUT_LUT3_OUT_DIRECT      = LL_PLAY_LUT_SOURCE_LUT3_OUT_DIRECT,      /*!< PLAY Lookup table 3 direct output selected as input source      */
  HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT      = LL_PLAY_LUT_SOURCE_LUT4_OUT_DIRECT,      /*!< PLAY Lookup table 4 direct output selected as input source      */
  HAL_PLAY_LUT_INPUT_LUT5_OUT_DIRECT      = LL_PLAY_LUT_SOURCE_LUT5_OUT_DIRECT,      /*!< PLAY Lookup table 5 direct output selected as input source      */
  HAL_PLAY_LUT_INPUT_LUT6_OUT_DIRECT      = LL_PLAY_LUT_SOURCE_LUT6_OUT_DIRECT,      /*!< PLAY Lookup table 6 direct output selected as input source      */
  HAL_PLAY_LUT_INPUT_LUT7_OUT_DIRECT      = LL_PLAY_LUT_SOURCE_LUT7_OUT_DIRECT,      /*!< PLAY Lookup table 7 direct output selected as input source      */
  HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT      = LL_PLAY_LUT_SOURCE_LUT8_OUT_DIRECT,      /*!< PLAY Lookup table 8 direct output selected as input source      */
  HAL_PLAY_LUT_INPUT_LUT9_OUT_DIRECT      = LL_PLAY_LUT_SOURCE_LUT9_OUT_DIRECT,      /*!< PLAY Lookup table 9 direct output selected as input source      */
  HAL_PLAY_LUT_INPUT_LUT10_OUT_DIRECT     = LL_PLAY_LUT_SOURCE_LUT10_OUT_DIRECT,     /*!< PLAY Lookup table 10 direct output selected as input source     */
  HAL_PLAY_LUT_INPUT_LUT11_OUT_DIRECT     = LL_PLAY_LUT_SOURCE_LUT11_OUT_DIRECT,     /*!< PLAY Lookup table 11 direct output selected as input source     */
  HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT     = LL_PLAY_LUT_SOURCE_LUT12_OUT_DIRECT,     /*!< PLAY Lookup table 12 direct output selected as input source     */
  HAL_PLAY_LUT_INPUT_LUT13_OUT_DIRECT     = LL_PLAY_LUT_SOURCE_LUT13_OUT_DIRECT,     /*!< PLAY Lookup table 13 direct output selected as input source     */
  HAL_PLAY_LUT_INPUT_LUT14_OUT_DIRECT     = LL_PLAY_LUT_SOURCE_LUT14_OUT_DIRECT,     /*!< PLAY Lookup table 14 direct output selected as input source     */
  HAL_PLAY_LUT_INPUT_LUT15_OUT_DIRECT     = LL_PLAY_LUT_SOURCE_LUT15_OUT_DIRECT,     /*!< PLAY Lookup table 15 direct output selected as input source     */

  HAL_PLAY_LUT_INPUT_LUT0_OUT_REGISTERED  = LL_PLAY_LUT_SOURCE_LUT0_OUT_REGISTERED,  /*!< PLAY Lookup table 0 registered output selected as input source  */
  HAL_PLAY_LUT_INPUT_LUT1_OUT_REGISTERED  = LL_PLAY_LUT_SOURCE_LUT1_OUT_REGISTERED,  /*!< PLAY Lookup table 1 registered output selected as input source  */
  HAL_PLAY_LUT_INPUT_LUT2_OUT_REGISTERED  = LL_PLAY_LUT_SOURCE_LUT2_OUT_REGISTERED,  /*!< PLAY Lookup table 2 registered output selected as input source  */
  HAL_PLAY_LUT_INPUT_LUT3_OUT_REGISTERED  = LL_PLAY_LUT_SOURCE_LUT3_OUT_REGISTERED,  /*!< PLAY Lookup table 3 registered output selected as input source  */
  HAL_PLAY_LUT_INPUT_LUT4_OUT_REGISTERED  = LL_PLAY_LUT_SOURCE_LUT4_OUT_REGISTERED,  /*!< PLAY Lookup table 4 registered output selected as input source  */
  HAL_PLAY_LUT_INPUT_LUT5_OUT_REGISTERED  = LL_PLAY_LUT_SOURCE_LUT5_OUT_REGISTERED,  /*!< PLAY Lookup table 5 registered output selected as input source  */
  HAL_PLAY_LUT_INPUT_LUT6_OUT_REGISTERED  = LL_PLAY_LUT_SOURCE_LUT6_OUT_REGISTERED,  /*!< PLAY Lookup table 6 registered output selected as input source  */
  HAL_PLAY_LUT_INPUT_LUT7_OUT_REGISTERED  = LL_PLAY_LUT_SOURCE_LUT7_OUT_REGISTERED,  /*!< PLAY Lookup table 7 registered output selected as input source  */
  HAL_PLAY_LUT_INPUT_LUT8_OUT_REGISTERED  = LL_PLAY_LUT_SOURCE_LUT8_OUT_REGISTERED,  /*!< PLAY Lookup table 8 registered output selected as input source  */
  HAL_PLAY_LUT_INPUT_LUT9_OUT_REGISTERED  = LL_PLAY_LUT_SOURCE_LUT9_OUT_REGISTERED,  /*!< PLAY Lookup table 9 registered output selected as input source  */
  HAL_PLAY_LUT_INPUT_LUT10_OUT_REGISTERED = LL_PLAY_LUT_SOURCE_LUT10_OUT_REGISTERED, /*!< PLAY Lookup table 10 registered output selected as input source */
  HAL_PLAY_LUT_INPUT_LUT11_OUT_REGISTERED = LL_PLAY_LUT_SOURCE_LUT11_OUT_REGISTERED, /*!< PLAY Lookup table 11 registered output selected as input source */
  HAL_PLAY_LUT_INPUT_LUT12_OUT_REGISTERED = LL_PLAY_LUT_SOURCE_LUT12_OUT_REGISTERED, /*!< PLAY Lookup table 12 registered output selected as input source */
  HAL_PLAY_LUT_INPUT_LUT13_OUT_REGISTERED = LL_PLAY_LUT_SOURCE_LUT13_OUT_REGISTERED, /*!< PLAY Lookup table 13 registered output selected as input source */
  HAL_PLAY_LUT_INPUT_LUT14_OUT_REGISTERED = LL_PLAY_LUT_SOURCE_LUT14_OUT_REGISTERED, /*!< PLAY Lookup table 14 registered output selected as input source */
  HAL_PLAY_LUT_INPUT_LUT15_OUT_REGISTERED = LL_PLAY_LUT_SOURCE_LUT15_OUT_REGISTERED, /*!< PLAY Lookup table 15 registered output selected as input source */

  HAL_PLAY_LUT_INPUT_FILTER0              = LL_PLAY_LUT_SOURCE_FILTER0,              /*!< PLAY input signal IN0 selected as input source                  */
  HAL_PLAY_LUT_INPUT_FILTER1              = LL_PLAY_LUT_SOURCE_FILTER1,              /*!< PLAY input signal IN1 selected as input source                  */
  HAL_PLAY_LUT_INPUT_FILTER2              = LL_PLAY_LUT_SOURCE_FILTER2,              /*!< PLAY input signal IN2 selected as input source                  */
  HAL_PLAY_LUT_INPUT_FILTER3              = LL_PLAY_LUT_SOURCE_FILTER3,              /*!< PLAY input signal IN3 selected as input source                  */
  HAL_PLAY_LUT_INPUT_FILTER4              = LL_PLAY_LUT_SOURCE_FILTER4,              /*!< PLAY input signal IN4 selected as input source                  */
  HAL_PLAY_LUT_INPUT_FILTER5              = LL_PLAY_LUT_SOURCE_FILTER5,              /*!< PLAY input signal IN5 selected as input source                  */
  HAL_PLAY_LUT_INPUT_FILTER6              = LL_PLAY_LUT_SOURCE_FILTER6,              /*!< PLAY input signal IN6 selected as input source                  */
  HAL_PLAY_LUT_INPUT_FILTER7              = LL_PLAY_LUT_SOURCE_FILTER7,              /*!< PLAY input signal IN7 selected as input source                  */
  HAL_PLAY_LUT_INPUT_FILTER8              = LL_PLAY_LUT_SOURCE_FILTER8,              /*!< PLAY input signal IN8 selected as input source                  */
  HAL_PLAY_LUT_INPUT_FILTER9              = LL_PLAY_LUT_SOURCE_FILTER9,              /*!< PLAY input signal IN9 selected as input source                  */
  HAL_PLAY_LUT_INPUT_FILTER10             = LL_PLAY_LUT_SOURCE_FILTER10,             /*!< PLAY input signal IN10 selected as input source                 */
  HAL_PLAY_LUT_INPUT_FILTER11             = LL_PLAY_LUT_SOURCE_FILTER11,             /*!< PLAY input signal IN11 selected as input source                 */
  HAL_PLAY_LUT_INPUT_FILTER12             = LL_PLAY_LUT_SOURCE_FILTER12,             /*!< PLAY input signal IN12 selected as input source                 */
  HAL_PLAY_LUT_INPUT_FILTER13             = LL_PLAY_LUT_SOURCE_FILTER13,             /*!< PLAY input signal IN13 selected as input source                 */
  HAL_PLAY_LUT_INPUT_FILTER14             = LL_PLAY_LUT_SOURCE_FILTER14,             /*!< PLAY input signal IN14 selected as input source                 */
  HAL_PLAY_LUT_INPUT_FILTER15             = LL_PLAY_LUT_SOURCE_FILTER15,             /*!< PLAY input signal IN15 selected as input source                 */

  HAL_PLAY_LUT_INPUT_SWTRIG0              = LL_PLAY_LUT_SOURCE_SWTRIG0,              /*!< PLAY software trigger input 0 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG1              = LL_PLAY_LUT_SOURCE_SWTRIG1,              /*!< PLAY software trigger input 1 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG2              = LL_PLAY_LUT_SOURCE_SWTRIG2,              /*!< PLAY software trigger input 2 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG3              = LL_PLAY_LUT_SOURCE_SWTRIG3,              /*!< PLAY software trigger input 3 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG4              = LL_PLAY_LUT_SOURCE_SWTRIG4,              /*!< PLAY software trigger input 4 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG5              = LL_PLAY_LUT_SOURCE_SWTRIG5,              /*!< PLAY software trigger input 5 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG6              = LL_PLAY_LUT_SOURCE_SWTRIG6,              /*!< PLAY software trigger input 6 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG7              = LL_PLAY_LUT_SOURCE_SWTRIG7,              /*!< PLAY software trigger input 7 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG8              = LL_PLAY_LUT_SOURCE_SWTRIG8,              /*!< PLAY software trigger input 8 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG9              = LL_PLAY_LUT_SOURCE_SWTRIG9,              /*!< PLAY software trigger input 9 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG10             = LL_PLAY_LUT_SOURCE_SWTRIG10,             /*!< PLAY software trigger input 10 selected as input source         */
  HAL_PLAY_LUT_INPUT_SWTRIG11             = LL_PLAY_LUT_SOURCE_SWTRIG11,             /*!< PLAY software trigger input 11 selected as input source         */
  HAL_PLAY_LUT_INPUT_SWTRIG12             = LL_PLAY_LUT_SOURCE_SWTRIG12,             /*!< PLAY software trigger input 12 selected as input source         */
  HAL_PLAY_LUT_INPUT_SWTRIG13             = LL_PLAY_LUT_SOURCE_SWTRIG13,             /*!< PLAY software trigger input 13 selected as input source         */
  HAL_PLAY_LUT_INPUT_SWTRIG14             = LL_PLAY_LUT_SOURCE_SWTRIG14,             /*!< PLAY software trigger input 14 selected as input source         */
  HAL_PLAY_LUT_INPUT_SWTRIG15             = LL_PLAY_LUT_SOURCE_SWTRIG15,             /*!< PLAY software trigger input 15 selected as input source         */

  HAL_PLAY_LUT_INPUT_DEFAULT              = LL_PLAY_LUT_SOURCE_SWTRIG15,             /*!< Default value                                                   */
} hal_play_lut_input_source_t;

/**
  * @brief  PLAY Lookup table Clock Gate Source enumeration
  */
typedef enum
{
  HAL_PLAY_LUT_CLK_GATE_OFF                  = LL_PLAY_LUT_CLK_GATE_OFF,                  /*!< PLAY LUT clock gate is OFF                            */
  HAL_PLAY_LUT_CLK_GATE_ON                   = LL_PLAY_LUT_CLK_GATE_ON,                   /*!< PLAY LUT clock gate is always enabled                 */
  HAL_PLAY_LUT_CLK_GATE_SW_ACK               = LL_PLAY_LUT_CLK_GATE_SW_ACK,               /*!< PLAY LUT clock gate source is SWIN_WE signal          */

  HAL_PLAY_LUT_CLK_GATE_LUT0_OUT_REGISTERED  = LL_PLAY_LUT_CLK_GATE_LUT0_OUT_REGISTERED,  /*!< PLAY LUT clock gate source is LUT0 registered output  */
  HAL_PLAY_LUT_CLK_GATE_LUT1_OUT_REGISTERED  = LL_PLAY_LUT_CLK_GATE_LUT1_OUT_REGISTERED,  /*!< PLAY LUT clock gate source is LUT1 registered output  */
  HAL_PLAY_LUT_CLK_GATE_LUT2_OUT_REGISTERED  = LL_PLAY_LUT_CLK_GATE_LUT2_OUT_REGISTERED,  /*!< PLAY LUT clock gate source is LUT2 registered output  */
  HAL_PLAY_LUT_CLK_GATE_LUT3_OUT_REGISTERED  = LL_PLAY_LUT_CLK_GATE_LUT3_OUT_REGISTERED,  /*!< PLAY LUT clock gate source is LUT3 registered output  */
  HAL_PLAY_LUT_CLK_GATE_LUT4_OUT_REGISTERED  = LL_PLAY_LUT_CLK_GATE_LUT4_OUT_REGISTERED,  /*!< PLAY LUT clock gate source is LUT4 registered output  */
  HAL_PLAY_LUT_CLK_GATE_LUT5_OUT_REGISTERED  = LL_PLAY_LUT_CLK_GATE_LUT5_OUT_REGISTERED,  /*!< PLAY LUT clock gate source is LUT5 registered output  */
  HAL_PLAY_LUT_CLK_GATE_LUT6_OUT_REGISTERED  = LL_PLAY_LUT_CLK_GATE_LUT6_OUT_REGISTERED,  /*!< PLAY LUT clock gate source is LUT6 registered output  */
  HAL_PLAY_LUT_CLK_GATE_LUT7_OUT_REGISTERED  = LL_PLAY_LUT_CLK_GATE_LUT7_OUT_REGISTERED,  /*!< PLAY LUT clock gate source is LUT7 registered output  */
  HAL_PLAY_LUT_CLK_GATE_LUT8_OUT_REGISTERED  = LL_PLAY_LUT_CLK_GATE_LUT8_OUT_REGISTERED,  /*!< PLAY LUT clock gate source is LUT8 registered output  */
  HAL_PLAY_LUT_CLK_GATE_LUT9_OUT_REGISTERED  = LL_PLAY_LUT_CLK_GATE_LUT9_OUT_REGISTERED,  /*!< PLAY LUT clock gate source is LUT9 registered output  */
  HAL_PLAY_LUT_CLK_GATE_LUT10_OUT_REGISTERED = LL_PLAY_LUT_CLK_GATE_LUT10_OUT_REGISTERED, /*!< PLAY LUT clock gate source is LUT10 registered output */
  HAL_PLAY_LUT_CLK_GATE_LUT11_OUT_REGISTERED = LL_PLAY_LUT_CLK_GATE_LUT11_OUT_REGISTERED, /*!< PLAY LUT clock gate source is LUT11 registered output */
  HAL_PLAY_LUT_CLK_GATE_LUT12_OUT_REGISTERED = LL_PLAY_LUT_CLK_GATE_LUT12_OUT_REGISTERED, /*!< PLAY LUT clock gate source is LUT12 registered output */
  HAL_PLAY_LUT_CLK_GATE_LUT13_OUT_REGISTERED = LL_PLAY_LUT_CLK_GATE_LUT13_OUT_REGISTERED, /*!< PLAY LUT clock gate source is LUT13 registered output */
  HAL_PLAY_LUT_CLK_GATE_LUT14_OUT_REGISTERED = LL_PLAY_LUT_CLK_GATE_LUT14_OUT_REGISTERED, /*!< PLAY LUT clock gate source is LUT14 registered output */
  HAL_PLAY_LUT_CLK_GATE_LUT15_OUT_REGISTERED = LL_PLAY_LUT_CLK_GATE_LUT15_OUT_REGISTERED, /*!< PLAY LUT clock gate source is LUT15 registered output */

  HAL_PLAY_LUT_CLK_GATE_FILTER0              = LL_PLAY_LUT_CLK_GATE_FILTER0,              /*!< PLAY LUT clock gate source is input signal IN0        */
  HAL_PLAY_LUT_CLK_GATE_FILTER1              = LL_PLAY_LUT_CLK_GATE_FILTER1,              /*!< PLAY LUT clock gate source is input signal IN1        */
  HAL_PLAY_LUT_CLK_GATE_FILTER2              = LL_PLAY_LUT_CLK_GATE_FILTER2,              /*!< PLAY LUT clock gate source is input signal IN2        */
  HAL_PLAY_LUT_CLK_GATE_FILTER3              = LL_PLAY_LUT_CLK_GATE_FILTER3,              /*!< PLAY LUT clock gate source is input signal IN3        */
  HAL_PLAY_LUT_CLK_GATE_FILTER4              = LL_PLAY_LUT_CLK_GATE_FILTER4,              /*!< PLAY LUT clock gate source is input signal IN4        */
  HAL_PLAY_LUT_CLK_GATE_FILTER5              = LL_PLAY_LUT_CLK_GATE_FILTER5,              /*!< PLAY LUT clock gate source is input signal IN5        */
  HAL_PLAY_LUT_CLK_GATE_FILTER6              = LL_PLAY_LUT_CLK_GATE_FILTER6,              /*!< PLAY LUT clock gate source is input signal IN6        */
  HAL_PLAY_LUT_CLK_GATE_FILTER7              = LL_PLAY_LUT_CLK_GATE_FILTER7,              /*!< PLAY LUT clock gate source is input signal IN7        */
  HAL_PLAY_LUT_CLK_GATE_FILTER8              = LL_PLAY_LUT_CLK_GATE_FILTER8,              /*!< PLAY LUT clock gate source is input signal IN8        */
  HAL_PLAY_LUT_CLK_GATE_FILTER9              = LL_PLAY_LUT_CLK_GATE_FILTER9,              /*!< PLAY LUT clock gate source is input signal IN9        */
  HAL_PLAY_LUT_CLK_GATE_FILTER10             = LL_PLAY_LUT_CLK_GATE_FILTER10,             /*!< PLAY LUT clock gate source is input signal IN10       */
  HAL_PLAY_LUT_CLK_GATE_FILTER11             = LL_PLAY_LUT_CLK_GATE_FILTER11,             /*!< PLAY LUT clock gate source is input signal IN11       */
  HAL_PLAY_LUT_CLK_GATE_FILTER12             = LL_PLAY_LUT_CLK_GATE_FILTER12,             /*!< PLAY LUT clock gate source is input signal IN12       */
  HAL_PLAY_LUT_CLK_GATE_FILTER13             = LL_PLAY_LUT_CLK_GATE_FILTER13,             /*!< PLAY LUT clock gate source is input signal IN13       */
  HAL_PLAY_LUT_CLK_GATE_FILTER14             = LL_PLAY_LUT_CLK_GATE_FILTER14,             /*!< PLAY LUT clock gate source is input signal IN14       */
  HAL_PLAY_LUT_CLK_GATE_FILTER15             = LL_PLAY_LUT_CLK_GATE_FILTER15,             /*!< PLAY LUT clock gate source is input signal IN15       */

  HAL_PLAY_LUT_CLK_GATE_SWTRIG0              = LL_PLAY_LUT_CLK_GATE_SWTRIG0,              /*!< PLAY LUT clock gate source is software trigger 0      */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG1              = LL_PLAY_LUT_CLK_GATE_SWTRIG1,              /*!< PLAY LUT clock gate source is software trigger 1      */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG2              = LL_PLAY_LUT_CLK_GATE_SWTRIG2,              /*!< PLAY LUT clock gate source is software trigger 2      */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG3              = LL_PLAY_LUT_CLK_GATE_SWTRIG3,              /*!< PLAY LUT clock gate source is software trigger 3      */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG4              = LL_PLAY_LUT_CLK_GATE_SWTRIG4,              /*!< PLAY LUT clock gate source is software trigger 4      */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG5              = LL_PLAY_LUT_CLK_GATE_SWTRIG5,              /*!< PLAY LUT clock gate source is software trigger 5      */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG6              = LL_PLAY_LUT_CLK_GATE_SWTRIG6,              /*!< PLAY LUT clock gate source is software trigger 6      */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG7              = LL_PLAY_LUT_CLK_GATE_SWTRIG7,              /*!< PLAY LUT clock gate source is software trigger 7      */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG8              = LL_PLAY_LUT_CLK_GATE_SWTRIG8,              /*!< PLAY LUT clock gate source is software trigger 8      */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG9              = LL_PLAY_LUT_CLK_GATE_SWTRIG9,              /*!< PLAY LUT clock gate source is software trigger 9      */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG10             = LL_PLAY_LUT_CLK_GATE_SWTRIG10,             /*!< PLAY LUT clock gate source is software trigger 10     */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG11             = LL_PLAY_LUT_CLK_GATE_SWTRIG11,             /*!< PLAY LUT clock gate source is software trigger 11     */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG12             = LL_PLAY_LUT_CLK_GATE_SWTRIG12,             /*!< PLAY LUT clock gate source is software trigger 12     */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG13             = LL_PLAY_LUT_CLK_GATE_SWTRIG13,             /*!< PLAY LUT clock gate source is software trigger 13     */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG14             = LL_PLAY_LUT_CLK_GATE_SWTRIG14,             /*!< PLAY LUT clock gate source is software trigger 14     */
  HAL_PLAY_LUT_CLK_GATE_SWTRIG15             = LL_PLAY_LUT_CLK_GATE_SWTRIG15,             /*!< PLAY LUT clock gate source is software trigger 15     */
} hal_play_lut_clk_gate_source_t;

/**
  * @brief  PLAY Lookup table Configuration structure
  */
typedef struct
{
  hal_play_lut_t                 lut;                                         /*!< Lookup table               */

  uint32_t                       truth_table;                                 /*!< Truth table value          */
  hal_play_lut_input_source_t    input_source[HAL_PLAY_LUT_INPUT_SOURCE_NBR]; /*!< Lookup table input sources */
  hal_play_lut_clk_gate_source_t clk_gate_source;                             /*!< Clock gate source          */
} hal_play_lut_config_t;

/**
  * @}
  */

/** @defgroup PLAY_Exported_Types_Group4 PLAY Output Multiplexer Configuration Structure
  * @{
  */

/**
  * @brief  PLAY Edge Trigger Configuration for Lookup Table Outputs
  */
typedef struct
{
  uint32_t lut_out_falling_mask; /*!< LUT Outputs mask to set in falling edge.
                                      Value can be a combination of @ref PLAY_LookUp_Table_Output */
  uint32_t lut_out_rising_mask;  /*!< LUT Outputs mask to set in rising edge.
                                      Value can be a combination of @ref PLAY_LookUp_Table_Output */
} hal_play_edge_trigger_config_t;

/**
  * @brief  PLAY Output Multiplexer enumeration
  */
typedef enum
{
  HAL_PLAY_OUT0  = LL_PLAY_OUT0,  /*!< PLAY Output 0  */
  HAL_PLAY_OUT1  = LL_PLAY_OUT1,  /*!< PLAY Output 1  */
  HAL_PLAY_OUT2  = LL_PLAY_OUT2,  /*!< PLAY Output 2  */
  HAL_PLAY_OUT3  = LL_PLAY_OUT3,  /*!< PLAY Output 3  */
  HAL_PLAY_OUT4  = LL_PLAY_OUT4,  /*!< PLAY Output 4  */
  HAL_PLAY_OUT5  = LL_PLAY_OUT5,  /*!< PLAY Output 5  */
  HAL_PLAY_OUT6  = LL_PLAY_OUT6,  /*!< PLAY Output 6  */
  HAL_PLAY_OUT7  = LL_PLAY_OUT7,  /*!< PLAY Output 7  */
  HAL_PLAY_OUT8  = LL_PLAY_OUT8,  /*!< PLAY Output 8  */
  HAL_PLAY_OUT9  = LL_PLAY_OUT9,  /*!< PLAY Output 9  */
  HAL_PLAY_OUT10 = LL_PLAY_OUT10, /*!< PLAY Output 10 */
  HAL_PLAY_OUT11 = LL_PLAY_OUT11, /*!< PLAY Output 11 */
  HAL_PLAY_OUT12 = LL_PLAY_OUT12, /*!< PLAY Output 12 */
  HAL_PLAY_OUT13 = LL_PLAY_OUT13, /*!< PLAY Output 13 */
  HAL_PLAY_OUT14 = LL_PLAY_OUT14, /*!< PLAY Output 14 */
  HAL_PLAY_OUT15 = LL_PLAY_OUT15, /*!< PLAY Output 15 */
} hal_play_out_t;

/**
  * @brief  PLAY Output Multiplexer Configuration
  */
typedef struct
{
  hal_play_out_t output_mux; /*!< Output multiplexer                                        */
  uint32_t       lut_output; /*!< Lookup table output, one of @ref PLAY_LookUp_Table_Output */
} hal_play_out_config_t;

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup PLAY_Exported_Types_Group5  PLAY Handle
  * @{
  */

/**
  * @brief  PLAY HAL Handle State enumeration
  */
typedef enum
{
  HAL_PLAY_STATE_RESET  = 0U,           /*!< PLAY not yet initialized                    */
  HAL_PLAY_STATE_INIT   = (1UL << 31U), /*!< PLAY initialized but not yet configured     */
  HAL_PLAY_STATE_IDLE   = (1UL << 30U), /*!< PLAY initialized, configured but not locked */
  HAL_PLAY_STATE_ACTIVE = (1UL << 29U), /*!< PLAY configured and locked                  */
} hal_play_state_t;

/**
  * @brief  PLAY Handle Structure definition
  */
typedef struct hal_play_handle_s hal_play_handle_t; /*!< PLAY handle structure type */

#if defined (USE_HAL_PLAY_REGISTER_CALLBACKS) && (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
/**
  * @brief pointer to a PLAY callback function.
  */
typedef void (*hal_play_cb_t)(hal_play_handle_t *hplay);

/**
  * @brief Pointer to a PLAY callback function with a mask of edge triggers as input parameter.
  */
typedef void (*hal_play_lut_output_cb_t)(hal_play_handle_t *hplay, uint32_t edge_trig_mask_status);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */

/**
  * @brief PLAY handle structure definition
  */
struct hal_play_handle_s
{
  hal_play_t instance; /*!< Peripheral instance */

  volatile hal_play_state_t global_state; /*!< PLAY peripheral state */

#if defined (USE_HAL_PLAY_REGISTER_CALLBACKS) && (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
  hal_play_cb_t p_sw_trigger_write_cplt_cb;         /*!< Software Trigger write complete callback */
  hal_play_cb_t p_edge_trigger_write_cplt_cb;       /*!< Edge Trigger write complete callback     */
  hal_play_lut_output_cb_t p_lut_output_rising_cb;  /*!< Lookup table output rising callback      */
  hal_play_lut_output_cb_t p_lut_output_falling_cb; /*!< Lookup table output falling callback     */
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */

#if defined (USE_HAL_PLAY_USER_DATA) && (USE_HAL_PLAY_USER_DATA == 1)
  const void *p_user_data; /*!< User data pointer */
#endif /* USE_HAL_PLAY_USER_DATA */
};

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup PLAY_Attributes PLAY security/privilege attributes
  * @{
  */

/**
  * @brief Security access level attribute
  */
typedef enum
{
  HAL_PLAY_NSEC = LL_PLAY_ATTR_NSEC, /*!< Non-secure access level attribute */
  HAL_PLAY_SEC  = LL_PLAY_ATTR_SEC   /*!< Secure access level attribute     */
} hal_play_sec_attr_t;

/**
  * @brief Privileged access level attribute
  */
typedef enum
{
  HAL_PLAY_NPRIV = LL_PLAY_ATTR_NPRIV, /*!< Non-privileged access level attribute */
  HAL_PLAY_PRIV  = LL_PLAY_ATTR_PRIV   /*!< Privileged access level attribute     */
} hal_play_priv_attr_t;

/**
  * @brief PLAY attributes configuration items
  */

#define HAL_PLAY_SEC_ITEM_CONFIG  LL_PLAY_SEC_ITEM_CONFIG  /*!< PLAY configuration registers items */
#define HAL_PLAY_SEC_ITEM_ALL     LL_PLAY_SEC_ITEM_ALL     /*!< All PLAY registers items           */

#define HAL_PLAY_PRIV_ITEM_CONFIG LL_PLAY_PRIV_ITEM_CONFIG /*!< PLAY configuration registers items */
#define HAL_PLAY_PRIV_ITEM_ALL    LL_PLAY_PRIV_ITEM_ALL    /*!< All PLAY registers items           */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup PLAY_Exported_Functions HAL PLAY Functions
  * @{
  */

/** @defgroup PLAY_Exported_Functions_Group1  Initialization and de-initialization functions
  * @{
  */

hal_status_t HAL_PLAY_Init(hal_play_handle_t *hplay, hal_play_t instance);
void HAL_PLAY_DeInit(hal_play_handle_t *hplay);
hal_play_t HAL_PLAY_GetInstance(const hal_play_handle_t *hplay);
PLAY_TypeDef *HAL_PLAY_GetLLInstance(const hal_play_handle_t *hplay);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group2  Configuration functions
  * @{
  */

/* PLAY Configuration functions ***********************************************/
hal_status_t HAL_PLAY_INPUT_SetConfig(const hal_play_handle_t *hplay, const hal_play_in_config_t *p_config,
                                      uint32_t array_size);
void HAL_PLAY_INPUT_GetConfig(const hal_play_handle_t *hplay, hal_play_in_config_t *p_config, uint32_t array_size);

hal_status_t HAL_PLAY_LUT_SetConfig(const hal_play_handle_t *hplay, const hal_play_lut_config_t *p_config,
                                    uint32_t array_size);
void HAL_PLAY_LUT_GetConfig(const hal_play_handle_t *hplay, hal_play_lut_config_t *p_config, uint32_t array_size);
hal_status_t HAL_PLAY_OUTPUT_SetConfig(hal_play_handle_t *hplay, const hal_play_out_config_t *p_config,
                                       uint32_t array_size);
void HAL_PLAY_OUTPUT_GetConfig(const hal_play_handle_t *hplay, hal_play_out_config_t *p_config, uint32_t array_size);

/* PLAY Configuration unitary functions for Input *****************************/
hal_status_t HAL_PLAY_INPUT_SetSource(const hal_play_handle_t *hplay, hal_play_in_source_t source);
hal_play_in_source_t HAL_PLAY_INPUT_GetSource(const hal_play_handle_t *hplay, hal_play_in_t input_mux);
hal_status_t HAL_PLAY_INPUT_SetMinPulseWidth(const hal_play_handle_t *hplay, hal_play_in_t input_mux, uint32_t width);
uint32_t HAL_PLAY_INPUT_GetMinPulseWidth(const hal_play_handle_t *hplay, hal_play_in_t input_mux);
hal_status_t HAL_PLAY_INPUT_SetEdgeDetectionMode(const hal_play_handle_t *hplay, hal_play_in_t input_mux,
                                                 hal_play_edge_detection_mode_t mode);
hal_play_edge_detection_mode_t HAL_PLAY_INPUT_GetEdgeDetectionMode(const hal_play_handle_t *hplay,
                                                                   hal_play_in_t input_mux);

/* PLAY Configuration unitary functions for Lookup table *********************/
hal_status_t HAL_PLAY_LUT_SetTruthTable(const hal_play_handle_t *hplay, hal_play_lut_t lut,
                                        uint32_t truth_table_value);
uint32_t HAL_PLAY_LUT_GetTruthTable(const hal_play_handle_t *hplay, hal_play_lut_t lut);
hal_status_t HAL_PLAY_LUT_SetSource(const hal_play_handle_t *hplay, hal_play_lut_t lut,
                                    hal_play_lut_input_t lut_input, hal_play_lut_input_source_t input_source);
hal_play_lut_input_source_t HAL_PLAY_LUT_GetSource(const hal_play_handle_t *hplay, hal_play_lut_t lut,
                                                   hal_play_lut_input_t lut_input);
hal_status_t HAL_PLAY_LUT_SetClockGateSource(const hal_play_handle_t *hplay, hal_play_lut_t lut,
                                             hal_play_lut_clk_gate_source_t source);
hal_play_lut_clk_gate_source_t HAL_PLAY_LUT_GetClockGateSource(const hal_play_handle_t *hplay, hal_play_lut_t lut);

/* PLAY Configuration unitary functions for Output ****************************/
hal_status_t HAL_PLAY_OUTPUT_SetSource(const hal_play_handle_t *hplay, hal_play_out_t output_mux, uint32_t source);
uint32_t HAL_PLAY_OUTPUT_GetSource(const hal_play_handle_t *hplay, hal_play_out_t output_mux);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group3  Peripheral control functions
  * @{
  */

hal_status_t HAL_PLAY_Start(hal_play_handle_t *hplay, const hal_play_edge_trigger_config_t *p_config);
hal_status_t HAL_PLAY_Stop(hal_play_handle_t *hplay);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group4  Interrupts and Edge Trigger control functions
  * @{
  */

/* PLAY APIs to manage Edge Trigger Transition of each LUT Output during the runtime */
hal_status_t HAL_PLAY_LUT_SetEdgeTrigger(const hal_play_handle_t *hplay, const hal_play_edge_trigger_config_t *p_config,
                                         uint32_t timeout_ms);
hal_status_t HAL_PLAY_LUT_SetEdgeTrigger_IT(const hal_play_handle_t *hplay,
                                            const hal_play_edge_trigger_config_t *p_config);
void HAL_PLAY_LUT_GetEdgeTrigger(const hal_play_handle_t *hplay, hal_play_edge_trigger_config_t *p_config);

hal_status_t HAL_PLAY_LUT_PollForEdgeTrigger(const hal_play_handle_t *hplay, hal_play_polling_edge_trigger_t poll_mode,
                                             uint32_t edge_trig_mask, uint32_t *p_edge_trig_mask_status,
                                             uint32_t timeout_ms);

/* PLAY APIs to manage interrupts on lookup table output */
hal_status_t HAL_PLAY_LUT_EnableIT(const hal_play_handle_t *hplay, uint32_t its_mask);
hal_status_t HAL_PLAY_LUT_DisableIT(const hal_play_handle_t *hplay, uint32_t its_mask);
uint32_t HAL_PLAY_LUT_GetIT(const hal_play_handle_t *hplay);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group5  Software Trigger control functions
  * @{
  */

hal_status_t HAL_PLAY_WriteSWTrigger(const hal_play_handle_t *hplay, uint32_t sw_triggers,
                                     hal_play_sw_trigger_state_t state, uint32_t timeout_ms);
hal_status_t HAL_PLAY_WriteSWTrigger_IT(const hal_play_handle_t *hplay, uint32_t sw_triggers,
                                        hal_play_sw_trigger_state_t state);
hal_status_t HAL_PLAY_ToggleSWTrigger(const hal_play_handle_t *hplay, uint32_t sw_triggers, uint32_t timeout_ms);
hal_status_t HAL_PLAY_ToggleSWTrigger_IT(const hal_play_handle_t *hplay, uint32_t sw_triggers);
hal_play_sw_trigger_state_t HAL_PLAY_ReadSWTrigger(const hal_play_handle_t *hplay, uint32_t sw_trig);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group6  IRQ Handler and callbacks functions
  * @{
  */

void HAL_PLAY_IRQHandler(hal_play_handle_t *hplay);

void HAL_PLAY_SWTriggerWriteCpltCallback(hal_play_handle_t *hplay);
void HAL_PLAY_EdgeTriggerWriteCpltCallback(hal_play_handle_t *hplay);
void HAL_PLAY_LUTOutputRisingCallback(hal_play_handle_t *hplay, uint32_t edge_trig_mask_status);
void HAL_PLAY_LUTOutputFallingCallback(hal_play_handle_t *hplay, uint32_t edge_trig_mask_status);

#if defined(USE_HAL_PLAY_REGISTER_CALLBACKS) && (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
/* Callbacks Registering functions */
hal_status_t HAL_PLAY_RegisterSWTriggerWriteCpltCallback(hal_play_handle_t *hplay, hal_play_cb_t p_callback);
hal_status_t HAL_PLAY_RegisterEdgeTriggerWriteCpltCallback(hal_play_handle_t *hplay, hal_play_cb_t p_callback);
hal_status_t HAL_PLAY_RegisterLUTOutputRisingCallback(hal_play_handle_t *hplay, hal_play_lut_output_cb_t p_callback);
hal_status_t HAL_PLAY_RegisterLUTOutputFallingCallback(hal_play_handle_t *hplay, hal_play_lut_output_cb_t p_callback);

#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group7  State and clock functions
  * @{
  */

hal_play_state_t HAL_PLAY_GetState(const hal_play_handle_t *hplay);

uint32_t HAL_PLAY_GetClockFreq(const hal_play_handle_t *hplay);

/**
  * @}
  */

#if defined (USE_HAL_PLAY_USER_DATA) && (USE_HAL_PLAY_USER_DATA == 1)
/** @defgroup PLAY_Exported_Functions_Group8  User Data functions
  * @{
  */

void HAL_PLAY_SetUserData(hal_play_handle_t *hplay, const void *p_user_data);
const void *HAL_PLAY_GetUserData(const hal_play_handle_t *hplay);

/**
  * @}
  */

#endif /* USE_HAL_PLAY_USER_DATA */

/** @defgroup PLAY_Exported_Functions_Group9  Security and privileged access levels attributes management
  * @{
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_PLAY_SetSecAttr(hal_play_t instance, uint32_t item, hal_play_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_play_sec_attr_t HAL_PLAY_GetSecAttr(hal_play_t instance, uint32_t item);

hal_status_t  HAL_PLAY_SetPrivAttr(hal_play_t instance, uint32_t item, hal_play_priv_attr_t priv_attr);
hal_play_priv_attr_t HAL_PLAY_GetPrivAttr(hal_play_t instance, uint32_t item);

/**
  * @}
  */

/**
  * @}
  */

#endif /* PLAY1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_HAL_PLAY_H */
