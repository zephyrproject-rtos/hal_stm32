/**
  ******************************************************************************
  * @file    stm32h5xx_hal_play.h
  * @brief   Header file of PLAY HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H5xx_HAL_PLAY_H
#define STM32H5xx_HAL_PLAY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal_def.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

#if defined(PLAY1)
#include "stm32h5xx_ll_play.h"

/** @defgroup PLAY PLAY
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PLAY_Exported_Constants PLAY Exported Constants
  * @{
  */

/** @defgroup PLAY_Global_definition  PLAY Global definition
  * @{
  */

#define HAL_PLAY_LUT_INPUT_SOURCE_NBR         LL_PLAY_LUT_INPUT_SOURCE_NBR           /*!< Number of input sources per lookup table */
#define HAL_PLAY_LUT_TRUTH_TABLE_VALUE_MAX    (LL_PLAY_LUT_TRUTH_TABLE_VALUE_MAX)    /*!< Maximal Lookup table value               */
#define HAL_PLAY_INPUT_FILTER_WIDTH_VALUE_MAX (LL_PLAY_INPUT_FILTER_WIDTH_VALUE_MAX) /*!< Maximal pulse width value                */

/**
  * @}
  */

/** @defgroup PLAY_Error_Codes  PLAY Error Codes
  * @{
  */

#define HAL_PLAY_ERROR_NONE              (0U)         /*!< No error                              */
#define HAL_PLAY_ERROR_INVALID_PARAM     (1UL << 1U)  /*!< Invalid parameter                     */
#define HAL_PLAY_ERROR_INVALID_CALLBACK  (1UL << 2U)  /*!< Invalid Callback ID                   */

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
#define HAL_PLAY_LUT_ALL_OUT_DIRECT     LL_PLAY_LUT_ALL_OUT_DIRECT     /*!< PLAY direct output of LUTs 0 to 15      */

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
  * Definitions used to encode/decode the @ref HAL_PLAY_IN_SourceTypeDef enumerated values
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

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** @defgroup PLAY_Exported_Types  PLAY Exported Types
  * @{
  */

/** @defgroup PLAY_Exported_Types_Group1  PLAY Global Enumerations
  * @{
  */

/**
  * @brief HAL PLAY instance
  */


/**
  * @brief  PLAY Polling Mode on Lookup Table Output Edge Trigger enumeration
  */
typedef enum
{
  HAL_PLAY_POLLING_FOR_ALL_EDGES, /*!< Polling for all edges */
  HAL_PLAY_POLLING_FOR_ANY_EDGE,  /*!< Polling for any edge  */
} HAL_PLAY_PollingEdgeTriggerTypeDef;

/**
  * @brief  PLAY Software Trigger State enumeration
  */
typedef enum
{
  HAL_PLAY_SW_TRIGGER_RESET = 0U,      /*!< Software Trigger Reset state */
  HAL_PLAY_SW_TRIGGER_SET   = 0xFFFFU, /*!< Software Trigger Set state   */
} HAL_PLAY_SWTriggerStateTypeDef;

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
} HAL_PLAY_INTypeDef;

/**
  * @brief  PLAY Input Multiplexer Edge Detection Mode enumeration
  */
typedef enum
{
  HAL_PLAY_EDGE_DETECTION_BYPASSED       = LL_PLAY_EDGE_DETECTION_MODE_BYPASSED,       /*!< Bypass mode                       */
  HAL_PLAY_EDGE_DETECTION_RISING         = LL_PLAY_EDGE_DETECTION_MODE_RISING,         /*!< Rising edge detection             */
  HAL_PLAY_EDGE_DETECTION_FALLING        = LL_PLAY_EDGE_DETECTION_MODE_FALLING,        /*!< Falling edge detection            */
  HAL_PLAY_EDGE_DETECTION_RISING_FALLING = LL_PLAY_EDGE_DETECTION_MODE_RISING_FALLING, /*!< Rising and falling edge detection */
} HAL_PLAY_EdgeDetectionModeTypeDef;

/**
  * @brief  PLAY Input Multiplexer Source enumeration
  */
typedef enum
{
  /* IO */
  HAL_PLAY1_IN_IN0_MUX0   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN1_MUX1   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN2_MUX2   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN3_MUX3   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN4_MUX4   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN5_MUX5   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN6_MUX6   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN7_MUX7   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN8_MUX8   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN9_MUX9   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN10_MUX10 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN11_MUX11 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN12_MUX12 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN13_MUX13 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN14_MUX14 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 0U),
  HAL_PLAY1_IN_IN15_MUX15 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 0U),

  /* ADC */
  HAL_PLAY1_IN_ADC1_AWD1_MUX3  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_ADC1_AWD1_MUX7  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_ADC1_AWD1_MUX9  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_ADC1_AWD1_MUX15 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_ADC1_AWD2_MUX0  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_ADC1_AWD2_MUX4  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_ADC1_AWD2_MUX8  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_ADC1_AWD2_MUX10 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_ADC2_AWD1_MUX3  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_ADC2_AWD1_MUX7  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_ADC2_AWD1_MUX11 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY1_IN_ADC2_AWD2_MUX4  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_ADC2_AWD2_MUX8  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_ADC2_AWD2_MUX12 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 4U),

  /* COMP */
  HAL_PLAY1_IN_COMP1_OUT_MUX1  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_COMP1_OUT_MUX5  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_COMP1_OUT_MUX7  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_COMP1_OUT_MUX13 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_COMP2_OUT_MUX1  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_COMP2_OUT_MUX5  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_COMP2_OUT_MUX9  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 4U),

  /* EVENT_OUT */
  HAL_PLAY1_IN_EVENTOUT_MUX0   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY1_IN_EVENTOUT_MUX8   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_EVENTOUT_MUX12  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 2U),

  /* LOCKUP */
  HAL_PLAY1_IN_LOCKUP_MUX4     = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_LOCKUP_MUX8     = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_LOCKUP_MUX12    = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_LOCKUP_MUX14    = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 3U),

  /* LPTIM */
  HAL_PLAY1_IN_LPTIM1_CH1_MUX3  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_LPTIM1_CH1_MUX5  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_LPTIM1_CH1_MUX11 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_LPTIM1_CH1_MUX15 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_LPTIM1_CH2_MUX0  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_LPTIM1_CH2_MUX4  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_LPTIM1_CH2_MUX6  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_LPTIM1_CH2_MUX12 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_LPTIM2_CH1_MUX3  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_LPTIM2_CH1_MUX7  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY1_IN_LPTIM2_CH1_MUX15 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_LPTIM2_CH2_MUX0  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_LPTIM2_CH2_MUX4  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_LPTIM2_CH2_MUX8  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 4U),

  /* MCO */
  HAL_PLAY1_IN_RCC_MCO1_MUX2    = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_RCC_MCO1_MUX6    = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_RCC_MCO1_MUX8    = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_RCC_MCO1_MUX14   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_RCC_MCO2_MUX2    = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_RCC_MCO2_MUX6    = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_RCC_MCO2_MUX10   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 4U),

  /* NMI */
  HAL_PLAY1_IN_NMI_MUX3         = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_NMI_MUX7         = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_NMI_MUX11        = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_NMI_MUX13        = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 3U),

  /* SPI */
  HAL_PLAY1_IN_SPI1_MOSI_MUX0  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_SPI1_MOSI_MUX6  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_SPI1_MOSI_MUX10 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_SPI1_MOSI_MUX14 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_SPI1_NSS_MUX5   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_SPI1_NSS_MUX9   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_SPI1_NSS_MUX13  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_SPI1_NSS_MUX15  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_SPI1_SCLK_MUX1  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_SPI1_SCLK_MUX7  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN7  << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_SPI1_SCLK_MUX11 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_SPI1_SCLK_MUX15 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_SPI2_MOSI_MUX2  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY1_IN_SPI2_MOSI_MUX10 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_SPI2_MOSI_MUX14 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_SPI2_NSS_MUX1   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY1_IN_SPI2_NSS_MUX9   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_SPI2_NSS_MUX13  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_SPI2_SCLK_MUX3  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY1_IN_SPI2_SCLK_MUX11 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_SPI2_SCLK_MUX15 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN15 << HAL_PLAY_IN_MUX_POS) | 2U),

  /* TIM */
  HAL_PLAY1_IN_TIM2_OC3_MUX1   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_TIM2_OC3_MUX3   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN3  << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_TIM2_OC3_MUX9   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_TIM2_OC3_MUX13  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_TIM2_OC4_MUX2   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_TIM2_OC4_MUX4   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_TIM2_OC4_MUX10  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_TIM2_OC4_MUX14  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_TIM2_TRGO_MUX0  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_TIM2_TRGO_MUX2  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_TIM2_TRGO_MUX8  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN8  << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_TIM2_TRGO_MUX12 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_TIM3_OC3_MUX1   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_TIM3_OC3_MUX5   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY1_IN_TIM3_OC3_MUX13  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_TIM3_OC4_MUX2   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_TIM3_OC4_MUX6   = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY1_IN_TIM3_OC4_MUX14  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_TIM3_TRGO_MUX0  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN0  << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_TIM3_TRGO_MUX4  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN4  << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY1_IN_TIM3_TRGO_MUX12 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 6U),

  /* USART */
  HAL_PLAY1_IN_USART1_CK_MUX2  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN2  << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_USART1_CK_MUX6  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_USART1_CK_MUX10 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_USART1_CK_MUX12 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN12 << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_USART1_TX_MUX1  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN1  << HAL_PLAY_IN_MUX_POS) | 5U),
  HAL_PLAY1_IN_USART1_TX_MUX5  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 7U),
  HAL_PLAY1_IN_USART1_TX_MUX9  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 1U),
  HAL_PLAY1_IN_USART1_TX_MUX11 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN11 << HAL_PLAY_IN_MUX_POS) | 3U),
  HAL_PLAY1_IN_USART2_CK_MUX6  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN6  << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_USART2_CK_MUX10 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN10 << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_USART2_CK_MUX14 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN14 << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY1_IN_USART2_TX_MUX5  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN5  << HAL_PLAY_IN_MUX_POS) | 6U),
  HAL_PLAY1_IN_USART2_TX_MUX9  = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN9  << HAL_PLAY_IN_MUX_POS) | 2U),
  HAL_PLAY1_IN_USART2_TX_MUX13 = (HAL_PLAY1_INSTANCE_ID | (HAL_PLAY_IN13 << HAL_PLAY_IN_MUX_POS) | 4U),
  HAL_PLAY_IN_SOURCE_INVALID = 0U, /*!< Invalid value */
} HAL_PLAY_IN_SourceTypeDef;

/**
  * @brief  PLAY Input Multiplexer Configuration structure
  */
typedef struct
{
  uint32_t                          min_pulse_width; /*!< Minimum Pulse Width. Value in range 0x00 to 0xFF */
  HAL_PLAY_EdgeDetectionModeTypeDef mode;            /*!< Edge Detection Mode                              */
  HAL_PLAY_IN_SourceTypeDef         source;          /*!< Signal source (premuxsel)                        */
} HAL_PLAY_IN_ConfTypeDef;

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
} HAL_PLAY_LUTTypeDef;

/**
  * @brief  PLAY Lookup table Input enumeration
  */
typedef enum
{
  HAL_PLAY_LUT_INPUT0 = LL_PLAY_LUT_INPUT0,  /*!< PLAY Lookup table input 0 */
  HAL_PLAY_LUT_INPUT1 = LL_PLAY_LUT_INPUT1,  /*!< PLAY Lookup table input 1 */
  HAL_PLAY_LUT_INPUT2 = LL_PLAY_LUT_INPUT2,  /*!< PLAY Lookup table input 2 */
  HAL_PLAY_LUT_INPUT3 = LL_PLAY_LUT_INPUT3,  /*!< PLAY Lookup table input 3 */
} HAL_PLAY_LUT_InputTypeDef;

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

  HAL_PLAY_LUT_INPUT_SWTRIG0              = LL_PLAY_LUT_SOURCE_SWTRIG0,              /*!< PLAY software trigger input 0 selected as input source           */
  HAL_PLAY_LUT_INPUT_SWTRIG1              = LL_PLAY_LUT_SOURCE_SWTRIG1,              /*!< PLAY software trigger input 1 selected as input source           */
  HAL_PLAY_LUT_INPUT_SWTRIG2              = LL_PLAY_LUT_SOURCE_SWTRIG2,              /*!< PLAY software trigger input 2 selected as input source           */
  HAL_PLAY_LUT_INPUT_SWTRIG3              = LL_PLAY_LUT_SOURCE_SWTRIG3,              /*!< PLAY software trigger input 3 selected as input source           */
  HAL_PLAY_LUT_INPUT_SWTRIG4              = LL_PLAY_LUT_SOURCE_SWTRIG4,              /*!< PLAY software trigger input 4 selected as input source           */
  HAL_PLAY_LUT_INPUT_SWTRIG5              = LL_PLAY_LUT_SOURCE_SWTRIG5,              /*!< PLAY software trigger input 5 selected as input source           */
  HAL_PLAY_LUT_INPUT_SWTRIG6              = LL_PLAY_LUT_SOURCE_SWTRIG6,              /*!< PLAY software trigger input 6 selected as input source           */
  HAL_PLAY_LUT_INPUT_SWTRIG7              = LL_PLAY_LUT_SOURCE_SWTRIG7,              /*!< PLAY software trigger input 7 selected as input source           */
  HAL_PLAY_LUT_INPUT_SWTRIG8              = LL_PLAY_LUT_SOURCE_SWTRIG8,              /*!< PLAY software trigger input 8 selected as input source           */
  HAL_PLAY_LUT_INPUT_SWTRIG9              = LL_PLAY_LUT_SOURCE_SWTRIG9,              /*!< PLAY software trigger input 9 selected as input source           */
  HAL_PLAY_LUT_INPUT_SWTRIG10             = LL_PLAY_LUT_SOURCE_SWTRIG10,             /*!< PLAY software trigger input 10 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG11             = LL_PLAY_LUT_SOURCE_SWTRIG11,             /*!< PLAY software trigger input 11 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG12             = LL_PLAY_LUT_SOURCE_SWTRIG12,             /*!< PLAY software trigger input 12 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG13             = LL_PLAY_LUT_SOURCE_SWTRIG13,             /*!< PLAY software trigger input 13 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG14             = LL_PLAY_LUT_SOURCE_SWTRIG14,             /*!< PLAY software trigger input 14 selected as input source          */
  HAL_PLAY_LUT_INPUT_SWTRIG15             = LL_PLAY_LUT_SOURCE_SWTRIG15,             /*!< PLAY software trigger input 15 selected as input source          */

  HAL_PLAY_LUT_INPUT_DEFAULT              = LL_PLAY_LUT_SOURCE_SWTRIG15,             /*!< Default value                                                    */
} HAL_PLAY_LUT_InputSourceTypeDef;

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
} HAL_PLAY_LUT_ClkGateSourceTypeDef;

/**
  * @brief  PLAY Lookup table Configuration structure
  */
typedef struct
{
  HAL_PLAY_LUTTypeDef               lut;                                         /*!< Lookup table               */

  uint32_t                          truth_table;                                 /*!< Truth table value          */
  HAL_PLAY_LUT_InputSourceTypeDef   input_source[HAL_PLAY_LUT_INPUT_SOURCE_NBR]; /*!< Lookup table input sources */
  HAL_PLAY_LUT_ClkGateSourceTypeDef clk_gate_source;                             /*!< Clock gate source          */
} HAL_PLAY_LUT_ConfTypeDef;

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
} HAL_PLAY_EdgeTriggerConfTypeDef;

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
} HAL_PLAY_OUTTypeDef;

/**
  * @brief  PLAY Output Multiplexer Configuration
  */
typedef struct
{
  HAL_PLAY_OUTTypeDef output_mux; /*!< Output multiplexer                                        */
  uint32_t            lut_output; /*!< Lookup table output, one of @ref PLAY_LookUp_Table_Output */
} HAL_PLAY_OUT_ConfTypeDef;

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup PLAY_ACCESS_CONTROL  PLAY Access Control
  * @{
  */

/**
  * @brief  PLAY Access Control TrustZone enumeration
  */
typedef enum
{
  HAL_PLAY_TZ_REG_UNPROTECTED      = 0U, /*!< All registers are unprotected       */
  HAL_PLAY_TZ_CONFIG_REG_PROTECTED = 1U, /*!< Only config registers are protected */
  HAL_PLAY_TZ_ALL_REG_PROTECTED    = 3U, /*!< All registers are protected         */
} HAL_PLAY_TrustZone_AccessControlTypeDef;


typedef struct
{
  HAL_PLAY_TrustZone_AccessControlTypeDef SecureAccess;    /*!< PLAY Secure access configuration    */
  HAL_PLAY_TrustZone_AccessControlTypeDef PrivilegeAccess; /*!< PLAY Privilege access configuration */
} HAL_PLAY_AccessControlConfTypeDef;


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
  HAL_PLAY_STATE_RESET = 0U,           /*!< PLAY not yet initialized                    */
  HAL_PLAY_STATE_INIT  = (1UL << 31U), /*!< PLAY initialized but not yet configured     */
  HAL_PLAY_STATE_READY = (1UL << 30U), /*!< PLAY initialized, configured but not locked */
  HAL_PLAY_STATE_BUSY  = (1UL << 29U), /*!< PLAY configured and locked                  */
} HAL_PLAY_StateTypeDef;

/**
  * @brief  PLAY Handle Structure definition
  */
#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
typedef struct __HAL_PLAY_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
{
  PLAY_TypeDef               *instance;  /*!< Register base address  */

  __IO HAL_PLAY_StateTypeDef global_state;  /*!< PLAY peripheral state  */

  __IO uint32_t last_error_codes;  /*!< Errors limited to the last process.
                                        This parameter can be a combination of @ref PLAY_Error_Codes */

#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
  void (* SWTriggerWriteCpltCallback)(struct __HAL_PLAY_HandleTypeDef *hplay);
  void (* EdgeTriggerWriteCpltCallback)(struct __HAL_PLAY_HandleTypeDef *hplay);
  void (* LUTOutputRisingCallback)(struct __HAL_PLAY_HandleTypeDef *hplay, uint32_t mask_flags);
  void (* LUTOutputFallingCallback)(struct __HAL_PLAY_HandleTypeDef *hplay, uint32_t mask_flags);
  void (* MspInitCallback)(struct __HAL_PLAY_HandleTypeDef *hplay);
  void (* MspDeInitCallback)(struct __HAL_PLAY_HandleTypeDef *hplay);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
} HAL_PLAY_HandleTypeDef;

#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
/**
  * @brief  PLAY callback ID enumeration definition
  */
typedef enum
{
  HAL_PLAY_SW_TRIGGER_WRITE_CPLT_CB_ID   = 0x00U, /*!< SW Trigger Write Complete callback ID   */
  HAL_PLAY_EDGE_TRIGGER_WRITE_CPLT_CB_ID = 0x01U, /*!< Edge Trigger Write Complete callback ID */
  HAL_PLAY_LUT_OUTPUT_RISING_CB_ID       = 0x02U, /*!< LUT Output Rising callback ID           */
  HAL_PLAY_LUT_OUTPUT_FALLING_CB_ID      = 0x03U, /*!< LUT Output Falling callback ID          */

  HAL_PLAY_MSPINIT_CB_ID                 = 0xFEU, /*!< MSP init callback ID                    */
  HAL_PLAY_MSPDEINIT_CB_ID               = 0xFFU, /*!< MSP de-init callback ID                 */
} HAL_PLAY_CallbackIDTypeDef;

/**
  * @brief  PLAY callback pointers definition
  */
typedef void (*pPLAY_CallbackTypeDef)(HAL_PLAY_HandleTypeDef *hplay); /*!< Pointer to a PLAY callback function */
typedef void (*pPLAY_LUTOutputCallbackTypeDef)(HAL_PLAY_HandleTypeDef *hplay, uint32_t mask_flags); /*!< Pointer to a PLAY LUT output callback function */

#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup PLAY_Exported_Macros PLAY Exported Macros
  * @{
  */

/** @brief Reset PLAY handle state.
  * @param  __HANDLE__  specifies the PLAY Handle.
  * @retval None
  */
#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
#define __HAL_PLAY_RESET_HANDLE_STATE(__HANDLE__)       \
  do {                                                  \
    (__HANDLE__)->global_state = HAL_PLAY_STATE_RESET;  \
    (__HANDLE__)->MspInitCallback = NULL;               \
    (__HANDLE__)->MspDeInitCallback = NULL;             \
  } while (0U)
#else
#define __HAL_PLAY_RESET_HANDLE_STATE(__HANDLE__)  ((__HANDLE__)->global_state = HAL_PLAY_STATE_RESET)
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PLAY_Exported_Functions PLAY Exported Functions
  * @{
  */

/** @defgroup PLAY_Exported_Functions_Group1  Initialization and de-initialization functions
  * @{
  */

HAL_StatusTypeDef HAL_PLAY_Init(HAL_PLAY_HandleTypeDef *hplay);
HAL_StatusTypeDef HAL_PLAY_DeInit(HAL_PLAY_HandleTypeDef *hplay);
void HAL_PLAY_MspInit(HAL_PLAY_HandleTypeDef *hplay);
void HAL_PLAY_MspDeInit(HAL_PLAY_HandleTypeDef *hplay);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group2  Configuration functions
  * @{
  */

/* PLAY Configuration functions ***********************************************/
HAL_StatusTypeDef HAL_PLAY_INPUT_SetConfig(HAL_PLAY_HandleTypeDef *hplay, const HAL_PLAY_IN_ConfTypeDef *p_config,
                                           uint32_t size_array);
HAL_StatusTypeDef HAL_PLAY_INPUT_GetConfig(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_IN_ConfTypeDef *p_config,
                                           uint32_t size_array);

HAL_StatusTypeDef HAL_PLAY_LUT_SetConfig(HAL_PLAY_HandleTypeDef *hplay, const HAL_PLAY_LUT_ConfTypeDef *p_config,
                                         uint32_t size_array);
HAL_StatusTypeDef HAL_PLAY_LUT_GetConfig(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUT_ConfTypeDef *p_config,
                                         uint32_t size_array);

HAL_StatusTypeDef HAL_PLAY_OUTPUT_SetConfig(HAL_PLAY_HandleTypeDef *hplay, const HAL_PLAY_OUT_ConfTypeDef *p_config,
                                            uint32_t size_array);
HAL_StatusTypeDef HAL_PLAY_OUTPUT_GetConfig(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_OUT_ConfTypeDef *p_config,
                                            uint32_t size_array);

/* PLAY Configuration unitary functions for Input *****************************/
HAL_StatusTypeDef HAL_PLAY_INPUT_SetSource(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_IN_SourceTypeDef source);
HAL_PLAY_IN_SourceTypeDef HAL_PLAY_INPUT_GetSource(const HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_INTypeDef mux_id);
HAL_StatusTypeDef HAL_PLAY_INPUT_SetMinPulseWidth(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_INTypeDef mux_id,
                                                  uint32_t width);
uint32_t HAL_PLAY_INPUT_GetMinPulseWidth(const HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_INTypeDef mux_id);
HAL_StatusTypeDef HAL_PLAY_INPUT_SetEdgeDetectionMode(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_INTypeDef mux_id,
                                                      HAL_PLAY_EdgeDetectionModeTypeDef mode);
HAL_PLAY_EdgeDetectionModeTypeDef HAL_PLAY_INPUT_GetEdgeDetectionMode(const HAL_PLAY_HandleTypeDef *hplay,
                                                                      HAL_PLAY_INTypeDef mux_id);

/* PLAY Configuration unitary functions for Lookup table *********************/
HAL_StatusTypeDef HAL_PLAY_LUT_SetTruthTable(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUTTypeDef lut,
                                             uint32_t truth_table_value);
uint32_t HAL_PLAY_LUT_GetTruthTable(const HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUTTypeDef lut);
HAL_StatusTypeDef HAL_PLAY_LUT_SetSource(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUTTypeDef lut,
                                         HAL_PLAY_LUT_InputTypeDef lut_input,
                                         HAL_PLAY_LUT_InputSourceTypeDef source);
HAL_PLAY_LUT_InputSourceTypeDef HAL_PLAY_LUT_GetSource(const HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUTTypeDef lut,
                                                       HAL_PLAY_LUT_InputTypeDef lut_input);
HAL_StatusTypeDef HAL_PLAY_LUT_SetClockGateSource(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUTTypeDef lut,
                                                  HAL_PLAY_LUT_ClkGateSourceTypeDef source);
HAL_PLAY_LUT_ClkGateSourceTypeDef HAL_PLAY_LUT_GetClockGateSource(const HAL_PLAY_HandleTypeDef *hplay,
                                                                  HAL_PLAY_LUTTypeDef lut_id);

/* PLAY Configuration unitary functions for Output ****************************/
HAL_StatusTypeDef HAL_PLAY_OUTPUT_SetSource(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_OUTTypeDef mux_id, uint32_t source);
uint32_t HAL_PLAY_OUTPUT_GetSource(const HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_OUTTypeDef mux_id);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group3  Peripheral control functions
  * @{
  */

HAL_StatusTypeDef HAL_PLAY_Start(HAL_PLAY_HandleTypeDef *hplay, const HAL_PLAY_EdgeTriggerConfTypeDef *p_config);
HAL_StatusTypeDef HAL_PLAY_Stop(HAL_PLAY_HandleTypeDef *hplay);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group4  Interrupts and Edge Trigger control functions
  * @{
  */

/* PLAY APIs to manage Edge Trigger Transition of each LUT Output during the runtime */
HAL_StatusTypeDef HAL_PLAY_LUT_SetEdgeTrigger(HAL_PLAY_HandleTypeDef *hplay,
                                              const HAL_PLAY_EdgeTriggerConfTypeDef *p_config,
                                              uint32_t timeout_ms);
HAL_StatusTypeDef HAL_PLAY_LUT_SetEdgeTrigger_IT(HAL_PLAY_HandleTypeDef *hplay,
                                                 const HAL_PLAY_EdgeTriggerConfTypeDef *p_config);
HAL_StatusTypeDef HAL_PLAY_LUT_GetEdgeTrigger(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_EdgeTriggerConfTypeDef *p_config);

HAL_StatusTypeDef HAL_PLAY_LUT_PollForEdgeTrigger(HAL_PLAY_HandleTypeDef *hplay,
                                                  HAL_PLAY_PollingEdgeTriggerTypeDef poll_mode,
                                                  uint32_t edge_trig_mask, uint32_t *p_edge_trig_mask_status,
                                                  uint32_t timeout_ms);

/* PLAY APIs to manage interrupts on lookup table output */
HAL_StatusTypeDef HAL_PLAY_LUT_EnableIT(HAL_PLAY_HandleTypeDef *hplay, uint32_t its_mask);
HAL_StatusTypeDef HAL_PLAY_LUT_DisableIT(HAL_PLAY_HandleTypeDef *hplay, uint32_t its_mask);
uint32_t HAL_PLAY_LUT_GetIT(const HAL_PLAY_HandleTypeDef *hplay);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group5  Software Trigger control functions
  * @{
  */

HAL_StatusTypeDef HAL_PLAY_WriteSWTrigger(HAL_PLAY_HandleTypeDef *hplay, uint32_t sw_triggers,
                                          HAL_PLAY_SWTriggerStateTypeDef state, uint32_t timeout_ms);
HAL_StatusTypeDef HAL_PLAY_WriteSWTrigger_IT(HAL_PLAY_HandleTypeDef *hplay, uint32_t sw_triggers,
                                             HAL_PLAY_SWTriggerStateTypeDef state);
HAL_StatusTypeDef HAL_PLAY_ToggleSWTrigger(HAL_PLAY_HandleTypeDef *hplay, uint32_t sw_triggers, uint32_t timeout_ms);
HAL_StatusTypeDef HAL_PLAY_ToggleSWTrigger_IT(HAL_PLAY_HandleTypeDef *hplay, uint32_t sw_triggers);
HAL_PLAY_SWTriggerStateTypeDef HAL_PLAY_ReadSWTrigger(const HAL_PLAY_HandleTypeDef *hplay, uint32_t sw_trig);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group6  IRQ Handler and callbacks functions
  * @{
  */

void HAL_PLAY_IRQHandler(HAL_PLAY_HandleTypeDef *hplay);

void HAL_PLAY_SWTriggerWriteCpltCallback(HAL_PLAY_HandleTypeDef *hplay);
void HAL_PLAY_EdgeTriggerWriteCpltCallback(HAL_PLAY_HandleTypeDef *hplay);
void HAL_PLAY_LUTOutputRisingCallback(HAL_PLAY_HandleTypeDef *hplay, uint32_t edge_trig_mask_status);
void HAL_PLAY_LUTOutputFallingCallback(HAL_PLAY_HandleTypeDef *hplay, uint32_t edge_trig_mask_status);

#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions ************************************/
HAL_StatusTypeDef HAL_PLAY_RegisterCallback(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_CallbackIDTypeDef CallbackID,
                                            pPLAY_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_PLAY_RegisterLUTOutputCallback(HAL_PLAY_HandleTypeDef *hplay,
                                                     HAL_PLAY_CallbackIDTypeDef CallbackID,
                                                     pPLAY_LUTOutputCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_PLAY_UnRegisterCallback(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_CallbackIDTypeDef CallbackID);
HAL_StatusTypeDef HAL_PLAY_UnRegisterLUTOutputCallback(HAL_PLAY_HandleTypeDef *hplay,
                                                       HAL_PLAY_CallbackIDTypeDef CallbackID);

#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group7  Handle control functions
  * @{
  */

HAL_PLAY_StateTypeDef HAL_PLAY_GetState(const HAL_PLAY_HandleTypeDef *hplay);
uint32_t HAL_PLAY_GetError(const HAL_PLAY_HandleTypeDef *hplay);

/**
  * @}
  */

/** @defgroup PLAY_Exported_Functions_Group8  Access control functions
  * @{
  */

HAL_StatusTypeDef HAL_PLAY_ConfigAttributes(HAL_PLAY_HandleTypeDef *hplay,
                                            const HAL_PLAY_AccessControlConfTypeDef *p_config);
HAL_StatusTypeDef HAL_PLAY_GetConfigAttributes(HAL_PLAY_HandleTypeDef *hplay,
                                               HAL_PLAY_AccessControlConfTypeDef *p_config);

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

#endif /* STM32H5xx_HAL_PLAY_H */
