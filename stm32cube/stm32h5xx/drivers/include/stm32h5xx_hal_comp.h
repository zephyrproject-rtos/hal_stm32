/**
  **********************************************************************************************************************
  * @file    stm32h5xx_hal_comp.h
  * @author  MCD Application Team
  * @brief   Header file of COMP HAL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H5xx_HAL_COMP_H
#define STM32H5xx_HAL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h5xx_hal_def.h"
#include "stm32h5xx_ll_exti.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */
#if defined (COMP1) || defined (COMP2)

/** @addtogroup COMP
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup COMP_Exported_Types COMP Exported Types
  * @{
  */

/**
  * @brief  COMP Init structure definition
  */
typedef struct
{
#if defined(COMP_WINDOW_MODE_SUPPORT)
  uint32_t WindowMode;         /*!< Set window mode of a pair of comparators instances
                                    (2 consecutive instances odd and even COMP<x> and COMP<x+1>).
                                    Note: HAL COMP driver allows to set window mode from any COMP
                                    instance of the pair of COMP instances composing window mode.
                                    This parameter can be a value of @ref COMP_WindowMode */
  uint32_t WindowOutput;       /*!< Set window mode output.
                                    This parameter can be a value of @ref COMP_WindowOutput */
#endif /* COMP_WINDOW_MODE_SUPPORT */
  uint32_t Mode;               /*!< Set comparator operating mode to adjust power and speed.
                                    Note: For the characteristics of comparator power modes
                                          (propagation delay and power consumption), refer to device datasheet.
                                    This parameter can be a value of @ref COMP_PowerMode */

  uint32_t InputPlus;          /*!< Set comparator input plus (non-inverting input).
                                    This parameter can be a value of @ref COMP_InputPlus */

  uint32_t InputMinus;         /*!< Set comparator input minus (inverting input).
                                    This parameter can be a value of @ref COMP_InputMinus */

  uint32_t Hysteresis;         /*!< Set comparator hysteresis mode of the input minus.
                                    This parameter can be a value of @ref COMP_Hysteresis */

  uint32_t OutputPol;          /*!< Set comparator output polarity.
                                    This parameter can be a value of @ref COMP_OutputPolarity
                                    Note: Specific to comparator of this STM32 series: comparator output
                                          triggers interruption on high level. HAL_COMP_Start_x functions
                                          can change output polarity depending on initial output level. */

  uint32_t BlankingSrce;       /*!< Set comparator blanking source.
                                    This parameter can be a value of @ref COMP_BlankingSrce */

  uint32_t TriggerMode;        /*!< Set the comparator output triggering External Interrupt Line (EXTI).
                                    This parameter can be a value of @ref COMP_EXTI_TriggerMode */

} COMP_InitTypeDef;

/**
  * @brief  HAL COMP state machine: HAL COMP states definition
  */
#define COMP_STATE_BITFIELD_LOCK  (0x10U)
typedef enum
{
  HAL_COMP_STATE_RESET        = 0x00,                       /*!< COMP not yet initialized                             */
  HAL_COMP_STATE_RESET_LOCKED = (HAL_COMP_STATE_RESET | \
                                 COMP_STATE_BITFIELD_LOCK), /*!< COMP not yet initialized and configuration is locked */
  HAL_COMP_STATE_READY        = 0x01,                       /*!< COMP initialized and ready for use                   */
  HAL_COMP_STATE_READY_LOCKED = (HAL_COMP_STATE_READY | \
                                 COMP_STATE_BITFIELD_LOCK), /*!< COMP initialized but configuration is locked         */
  HAL_COMP_STATE_BUSY         = 0x02,                       /*!< COMP is running                                      */
  HAL_COMP_STATE_BUSY_LOCKED  = (HAL_COMP_STATE_BUSY | \
                                 COMP_STATE_BITFIELD_LOCK)  /*!< COMP is running and configuration is locked          */

} HAL_COMP_StateTypeDef;

/**
  * @brief  COMP Handle Structure definition
  */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
typedef struct __COMP_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
{
  COMP_TypeDef       *Instance;                                   /*!< Register base address    */
  COMP_InitTypeDef   Init;                                        /*!< COMP required parameters */
  HAL_LockTypeDef    Lock;                                        /*!< Locking object           */
  __IO HAL_COMP_StateTypeDef  State;                              /*!< COMP communication state */
  __IO uint32_t      ErrorCode;                                   /*!< COMP error code          */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
  void (* TriggerCallback)(struct __COMP_HandleTypeDef *hcomp);   /*!< COMP trigger callback    */
  void (* MspInitCallback)(struct __COMP_HandleTypeDef *hcomp);   /*!< COMP Msp Init callback   */
  void (* MspDeInitCallback)(struct __COMP_HandleTypeDef *hcomp); /*!< COMP Msp DeInit callback */
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
#if defined(STM32H503xx)
  uint8_t            InterruptAutoRearm;                          /*!< COMP interrupt auto rearm setting */
#endif /* STM32H503xx */
} COMP_HandleTypeDef;

#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
/**
  * @brief  HAL COMP Callback ID enumeration definition
  */
typedef enum
{
  HAL_COMP_TRIGGER_CB_ID   = 0x00U,  /*!< COMP trigger callback ID */
  HAL_COMP_MSPINIT_CB_ID   = 0x01U,  /*!< COMP Msp Init callback ID */
  HAL_COMP_MSPDEINIT_CB_ID = 0x02U   /*!< COMP Msp DeInit callback ID */

} HAL_COMP_CallbackIDTypeDef;

/**
  * @brief  HAL COMP Callback pointer definition
  */
typedef  void (*pCOMP_CallbackTypeDef)(COMP_HandleTypeDef *hcomp); /*!< pointer to a COMP callback function */

#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup COMP_Exported_Constants COMP Exported Constants
  * @{
  */

/** @defgroup COMP_Error_Code COMP Error Code
  * @{
  */
#define HAL_COMP_ERROR_NONE             (0x00UL)   /*!< No error */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
#define HAL_COMP_ERROR_INVALID_CALLBACK (0x01U)   /*!< Invalid Callback error */
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
/**
  * @}
  */

#if defined(COMP_WINDOW_MODE_SUPPORT)
/** @defgroup COMP_WindowMode COMP Window Mode
  * @{
  */
#define COMP_WINDOWMODE_DISABLE                 (0x00000000UL)            /*!< Window mode disable: Comparators
                                                                               instances pair COMP1 and COMP2 are
                                                                               independent */
#define COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON (COMP_CFGR1_WINMODE)      /*!< Window mode enable: Comparators instances
                                                                               pair COMP1 and COMP2 have their input
                                                                               plus connected together.
                                                                               The common input is COMP1 input plus
                                                                               (COMP2 input plus is no more accessible).
                                                                               */
#define COMP_WINDOWMODE_COMP2_INPUT_PLUS_COMMON (COMP_CFGR1_WINMODE \
                                                 | COMP_WINDOWMODE_COMP2) /*!< Window mode enable: Comparators instances
                                                                               pair COMP1 and COMP2 have their input
                                                                               plus connected together.
                                                                               The common input is COMP2 input plus
                                                                               (COMP1 input plus is no more accessible).
                                                                               */
/**
  * @}
  */

/** @defgroup COMP_WindowOutput COMP Window output
  * @{
  */
#define COMP_WINDOWOUTPUT_EACH_COMP (0x00000000UL)            /*!< Window output default mode: Comparators output are
                                                                   indicating each their own state.
                                                                   To know window mode state: each comparator output
                                                                   must be read, if "((COMPx exclusive or COMPy) == 1)"
                                                                   then monitored signal is within comparators window.*/
#define COMP_WINDOWOUTPUT_COMP1     (COMP_CFGR1_WINOUT)        /*!< Window output synthesized on COMP1 output:
                                                                   COMP1 output is no more indicating its own state, but
                                                                   global window mode state (logical high means
                                                                   monitored signal is within comparators window).
                                                                   Note: impacts only comparator output signal level
                                                                   (COMPx_OUT propagated to GPIO, EXTI lines,
                                                                   timers, ...), does not impact output digital state
                                                                   of comparator (COMPx_VALUE) always reflecting each
                                                                   comparator output state.*/
#define COMP_WINDOWOUTPUT_COMP2     (COMP_CFGR1_WINOUT \
                                     | COMP_WINDOWMODE_COMP2) /*!< Window output synthesized on COMP2 output:
                                                                   COMP2 output is no more indicating its own state, but
                                                                   global window mode state (logical high means
                                                                   monitored signal is within comparators window).
                                                                   Note: impacts only comparator output signal level
                                                                   (COMPx_OUT propagated to GPIO, EXTI lines,
                                                                   timers, ...), does not impact output digital state
                                                                   of comparator (COMPx_VALUE) always reflecting each
                                                                   comparator output state.*/
#define COMP_WINDOWOUTPUT_BOTH      (0x00000001UL)            /*!< Window output synthesized on both comparators output
                                                                   of pair of comparator selected (COMP1 and COMP2:
                                                                   both comparators outputs are no more indicating their
                                                                   own state, but global window mode state (logical high
                                                                   means monitored signal is within comparators window).
                                                                   This is a specific configuration (technically
                                                                   possible but not relevant from application
                                                                   point of view:
                                                                   2 comparators output used for the same signal level),
                                                                   standard configuration for window mode is one of the
                                                                   settings above. */
/**
  * @}
  */
#endif /* COMP_WINDOW_MODE_SUPPORT */

/** @defgroup COMP_PowerMode COMP power mode
  * @{
  */
/* Note: For the characteristics of comparator power modes                    */
/*       (propagation delay and power consumption),                           */
/*       refer to device datasheet.                                           */
#define COMP_POWERMODE_HIGHSPEED       (0x00000000UL)         /*!< High Speed */
#define COMP_POWERMODE_MEDIUMSPEED     (COMP_CFGR1_PWRMODE_0) /*!< Medium Speed */
#define COMP_POWERMODE_ULTRALOWPOWER   (COMP_CFGR1_PWRMODE)   /*!< Ultra-low power mode */
/**
  * @}
  */

/** @defgroup COMP_InputPlus COMP input plus (non-inverting input)
  * @{
  */
#if defined(STM32H503xx)
#define COMP_INPUT_PLUS_IO1            (0x00000000UL)         /*!< Comparator input plus connected to IO1 (pin PB0) */
#define COMP_INPUT_PLUS_IO2            (COMP_CFGR2_INPSEL0)   /*!< Comparator input plus connected to IO2 (pin PA0) */
#define COMP_INPUT_PLUS_IO3            (COMP_CFGR1_INPSEL1)   /*!< Comparator input plus connected to IO3 (pin PB2) */
#define COMP_INPUT_PLUS_DAC1_CH1       (COMP_CFGR1_INPSEL2)   /*!< Comparator input plus connected to (DAC1_CH1) */
#else
#define COMP_INPUT_PLUS_IO1            (0x00000000UL)         /*!< Comparator input plus connected to IO1
                                                                   (COMP1 pin PA7, COMP2 pin PB0) */
#define COMP_INPUT_PLUS_IO2            (COMP_CFGR1_INPSEL0)   /*!< Comparator input plus connected to IO2
                                                                   (COMP1 pin PB2, COMP2 pin PE7) */
#define COMP_INPUT_PLUS_DAC1_CH1       (COMP_CFGR1_INPSEL1)   /*!< Comparator input plus connected to DAC1 channel 1
                                                                   (specific to instance: COMP1) */
#define COMP_INPUT_PLUS_DAC1_CH2       (COMP_CFGR1_INPSEL1)   /*!< Comparator input plus connected to DAC1 channel 2
                                                                   (specific to instance: COMP2) */
#endif /* STM32H503xx */
/**
  * @}
  */

/** @defgroup COMP_InputMinus COMP input minus (inverting input)
  * @{
  */
#define COMP_INPUT_MINUS_1_4VREFINT  (COMP_CFGR1_SCALEN |\
                                      COMP_CFGR1_BRGEN)       /*!< Comparator input minus connected to 1/4 VrefInt    */
#define COMP_INPUT_MINUS_1_2VREFINT  (COMP_CFGR1_INMSEL_0 |\
                                      COMP_CFGR1_SCALEN |\
                                      COMP_CFGR1_BRGEN)       /*!< Comparator input minus connected to 1/2 VrefInt    */
#define COMP_INPUT_MINUS_3_4VREFINT  (COMP_CFGR1_INMSEL_1 |\
                                      COMP_CFGR1_SCALEN |\
                                      COMP_CFGR1_BRGEN)       /*!< Comparator input minus connected to 3/4 VrefInt    */
#define COMP_INPUT_MINUS_VREFINT     (COMP_CFGR1_INMSEL_1 |\
                                      COMP_CFGR1_INMSEL_0 |\
                                      COMP_CFGR1_SCALEN)      /*!< Comparator input minus connected to VrefInt        */
#if defined(STM32H503xx)
#define COMP_INPUT_MINUS_DAC1_CH1    (COMP_CFGR1_INMSEL_2)   /*!< Comparator input minus connected to DAC1
                                     channel 1 (DAC_OUT1) */
#define COMP_INPUT_MINUS_IO1         (COMP_CFGR1_INMSEL_2 |\
                                      COMP_CFGR1_INMSEL_0)   /*!< Comparator input minus connected to pin PC4 */
#define COMP_INPUT_MINUS_IO2         (COMP_CFGR1_INMSEL_2 |\
                                      COMP_CFGR1_INMSEL_1)   /*!< Comparator input minus connected to pin PB1 */
#define COMP_INPUT_MINUS_IO3         (COMP_CFGR1_INMSEL_2 |\
                                      COMP_CFGR1_INMSEL_1 |\
                                      COMP_CFGR1_INMSEL_0)   /*!< Comparator input minus connected to pin PA5 */
#define COMP_INPUT_MINUS_TEMPSENSOR  (COMP_CFGR1_INMSEL_3)   /*!< Comparator input minus connected to internal
                                     temperature sensor (also accessible through ADC peripheral) */
#define COMP_INPUT_MINUS_VBAT        (COMP_CFGR1_INMSEL_3 |\
                                      COMP_CFGR1_INMSEL_0)   /*!< Comparator input minus connected to Vbat/4:
                                     Vbat voltage through a divider ladder of factor 1/4 to have input voltage
                                     always below Vdda. */
#else
#define COMP_INPUT_MINUS_DAC1_CH1    (COMP_CFGR1_INMSEL_2 |\
                                      COMP_CFGR1_INMSEL_0)   /*!< Comparator input minus connected to DAC1
                                     channel 1 (DAC_OUT1) */
#define COMP_INPUT_MINUS_DAC1_CH2    (COMP_CFGR1_INMSEL_2)   /*!< Comparator input minus connected to DAC1
                                     channel 2 (DAC_OUT2) */
#define COMP_INPUT_MINUS_IO1         (COMP_CFGR1_INMSEL_2 |\
                                      COMP_CFGR1_INMSEL_1)   /*!< Comparator input minus connected to IO1
                                     (COMP1 pin PA6, COMP2 pin PB1).
                                     Note: value for COMP2 different, updated in function using this define. */
#define COMP_INPUT_MINUS_IO2         (COMP_CFGR1_INMSEL_2 |\
                                      COMP_CFGR1_INMSEL_1 |\
                                      COMP_CFGR1_INMSEL_0)   /*!< Comparator input minus connected to IO2
                                     (COMP1 pin PE10, COMP2 pin PE9).
                                     Note: value for COMP2 different, updated in function using this define. */
#define COMP_INPUT_MINUS_IO3         (COMP_CFGR1_INMSEL_3)   /*!< Comparator input minus connected to IO3
                                     (COMP1 not applicable, COMP2 pin PE14).
                                     Note: value for COMP2 different, updated in function using this define. */
#define COMP_INPUT_MINUS_TEMPSENSOR  (COMP_CFGR1_INMSEL_3)   /*!< Comparator input minus connected to internal
                                     temperature sensor (also accessible through ADC peripheral)
                                     (specific to instance: COMP1) */
#define COMP_INPUT_MINUS_VBAT        (COMP_CFGR1_INMSEL_3 |\
                                      COMP_CFGR1_INMSEL_0)   /*!< Comparator input minus connected to Vbat/4:
                                     Vbat voltage through a divider ladder of factor 1/4 to have input voltage
                                     always below Vdda.
                                     (specific to instance: COMP1) */
#define COMP_INPUT_MINUS_VDDCORE     (COMP_CFGR1_INMSEL_2 |\
                                      COMP_CFGR1_INMSEL_1)   /*!< Comparator input minus connected to VddCore.
                                     (specific to instance: COMP2) */
#endif /* STM32H503xx */
/**
  * @}
  */

/** @defgroup COMP_Hysteresis COMP hysteresis
  * @{
  */
#define COMP_HYSTERESIS_NONE           (0x00000000UL)                       /*!< No hysteresis */
#define COMP_HYSTERESIS_LOW            (COMP_CFGR1_HYST_0)                  /*!< Hysteresis level low */
#define COMP_HYSTERESIS_MEDIUM         (COMP_CFGR1_HYST_1)                  /*!< Hysteresis level medium */
#define COMP_HYSTERESIS_HIGH           (COMP_CFGR1_HYST_0 | COMP_CFGR1_HYST_1) /*!< Hysteresis level high */
/**
  * @}
  */

/** @defgroup COMP_OutputPolarity COMP output Polarity
  * @{
  */
#define COMP_OUTPUTPOL_NONINVERTED     (0x00000000UL)          /*!< COMP output level is not inverted (comparator output
                                                                    is high when the input plus is at a higher voltage
                                                                    than the input minus) */
#define COMP_OUTPUTPOL_INVERTED        (COMP_CFGR1_POLARITY)   /*!< COMP output level is inverted (comparator output is
                                                                    low when the input plus is at a higher voltage than
                                                                    the input minus) */
/**
  * @}
  */

/** @defgroup COMP_BlankingSrce  COMP blanking source
  * @{
  */
#define COMP_BLANKINGSRC_NONE         ((uint32_t)0x00000000)    /*!<Comparator output without blanking */
#if defined(STM32H503xx)
#define COMP_BLANKINGSRC_TIM1_OC5     (COMP_CFGR1_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5 */
#define COMP_BLANKINGSRC_TIM2_OC3     (COMP_CFGR1_BLANKING_1)   /*!< Comparator output blanking source TIM2 OC3 */
#define COMP_BLANKINGSRC_TIM3_OC3     (COMP_CFGR1_BLANKING_0 |\
                                       COMP_CFGR1_BLANKING_1)   /*!< Comparator output blanking source TIM3 OC3 */
#define COMP_BLANKINGSRC_TIM3_OC4     (COMP_CFGR1_BLANKING_2)   /*!< Comparator output blanking source TIM3 OC4 */
#define COMP_BLANKINGSRC_LPTIM1_OC2   (COMP_CFGR1_BLANKING_2 |\
                                       COMP_CFGR1_BLANKING_0)   /*!< Comparator output blanking source LPTIM1 OC2 */
#define COMP_BLANKINGSRC_LPTIM2_OC2   (COMP_CFGR1_BLANKING_2 |\
                                       COMP_CFGR1_BLANKING_1)   /*!< Comparator output blanking source LPTIM2 OC2 */
#else
#define COMP_BLANKINGSRC_TIM1_OC5     (COMP_CFGR1_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5
                                                                     (specific to instance: COMP1) */
#define COMP_BLANKINGSRC_TIM1_OC6     (COMP_CFGR1_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC6
                                                                     (specific to instance: COMP2) */
#define COMP_BLANKINGSRC_TIM2_OC3     (COMP_CFGR1_BLANKING_1)   /*!< Comparator output blanking source TIM2 OC3 */
#define COMP_BLANKINGSRC_TIM3_OC3     (COMP_CFGR1_BLANKING_0 |\
                                       COMP_CFGR1_BLANKING_1)   /*!< Comparator output blanking source TIM3 OC3 */
#define COMP_BLANKINGSRC_TIM3_OC4     (COMP_CFGR1_BLANKING_2)   /*!< Comparator output blanking source TIM3 OC4 */
#define COMP_BLANKINGSRC_LPTIM1_OC2   (COMP_CFGR1_BLANKING_2 |\
                                       COMP_CFGR1_BLANKING_0)   /*!< Comparator output blanking source LPTIM1 OC2
                                                                     (specific to instance: COMP1) */
#define COMP_BLANKINGSRC_LPTIM2_OC2   (COMP_CFGR1_BLANKING_2 |\
                                       COMP_CFGR1_BLANKING_1)   /*!< Comparator output blanking source LPTIM2 OC2
                                                                     (specific to instance: COMP1) */
#define COMP_BLANKINGSRC_TIM8_OC5     (COMP_CFGR1_BLANKING_2 |\
                                       COMP_CFGR1_BLANKING_0)   /*!< Comparator output blanking source TIM8 OC5
                                                                     (specific to instance: COMP2) */
#define COMP_BLANKINGSRC_TIM15_OC2    (COMP_CFGR1_BLANKING_2 |\
                                       COMP_CFGR1_BLANKING_1)   /*!< Comparator output blanking source TIM15 OC2
                                                                     (specific to instance: COMP2) */
#endif /* STM32H503xx */
/**
  * @}
  */

/** @defgroup COMP_OutputLevel COMP Output Level
  * @{
  */
/* Note: Comparator output level values are fixed to "0" and "1",             */
/* corresponding COMP register bit is managed by HAL function to match        */
/* with these values (independently of bit position in register).             */

/* When output polarity is not inverted, comparator output is low when
   the input plus is at a lower voltage than the input minus */
#define COMP_OUTPUT_LEVEL_LOW              (0x00000000UL)
/* When output polarity is not inverted, comparator output is high when
   the input plus is at a higher voltage than the input minus */
#define COMP_OUTPUT_LEVEL_HIGH             (0x00000001UL)
/**
  * @}
  */

/** @defgroup COMP_EXTI_TriggerMode COMP output to EXTI
  * @{
  */
#define COMP_TRIGGERMODE_NONE                 (0x00000000UL)          /*!< Comparator output triggering no External
                                                                           Interrupt Line */
#if defined(STM32H503xx)
#define COMP_TRIGGERMODE_IT_RISING_FALLING    (COMP_EXTI_IT |\
                                               COMP_EXTI_RISING | COMP_EXTI_FALLING) /*!< Comparator output triggering
                                              interrupt on rising and falling edges.
                                              Note: Specific to comparator of this STM32 series: comparator output
                                                    triggers interruption on high level. HAL_COMP_Start_x functions
                                                    can change output polarity depending on initial output level. */
#else
#define COMP_TRIGGERMODE_IT_RISING            (COMP_EXTI_IT | COMP_EXTI_RISING)      /*!< Comparator output triggering
                                              interrupt on rising edge */
#define COMP_TRIGGERMODE_IT_FALLING           (COMP_EXTI_IT | COMP_EXTI_FALLING)     /*!< Comparator output triggering
                                              interrupt on falling edge */
#define COMP_TRIGGERMODE_IT_RISING_FALLING    (COMP_EXTI_IT |\
                                               COMP_EXTI_RISING | COMP_EXTI_FALLING) /*!< Comparator output triggering
                                              interrupt on both rising and falling edges */
#define COMP_TRIGGERMODE_EVENT_RISING         (COMP_EXTI_EVENT | COMP_EXTI_RISING)   /*!< Comparator output triggering
                                              interrupt on rising edge */
#define COMP_TRIGGERMODE_EVENT_FALLING        (COMP_EXTI_EVENT | COMP_EXTI_FALLING)  /*!< Comparator output triggering
                                              interrupt on falling edge */
#define COMP_TRIGGERMODE_EVENT_RISING_FALLING (COMP_EXTI_EVENT |\
                                               COMP_EXTI_RISING | COMP_EXTI_FALLING) /*!< Comparator output triggering
                                              interrupt on both rising and falling edges */
#endif /* STM32H503xx */

/**
  * @}
  */

/** @defgroup COMP_Flag COMP Flag
  * @{
  */
#define COMP_FLAG_C1I           COMP_SR_C1IF           /*!< Comparator 1 Interrupt Flag */
#if !defined(STM32H503xx)
#define COMP_FLAG_C2I           COMP_SR_C2IF           /*!< Comparator 2 Interrupt Flag */
#endif /* STM32H503xx */
#define COMP_FLAG_LOCK          COMP_CFGR1_LOCK        /*!< Lock flag                   */
/**
  * @}
  */

/** @defgroup COMP_IT_CLEAR_Flags  COMP Interruption Flags
  * @{
  */
#define COMP_CLEAR_C1IF          COMP_ICFR_CC1IF     /*!< Clear Comparator 1 Interrupt Clear Flag */
#if !defined(STM32H503xx)
#define COMP_CLEAR_C2IF          COMP_ICFR_CC2IF     /*!< Clear Comparator 2 Interrupt Clear Flag */
#endif /* STM32H503xx */
/**
  * @}
  */

/** @defgroup COMP_Interrupts_Definitions COMP Interrupts Definitions
  * @{
  */
#define COMP_IT_EN               COMP_CFGR1_ITEN
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup COMP_Exported_Macros COMP Exported Macros
  * @{
  */

/** @defgroup COMP_Handle_Management  COMP Handle Management
  * @{
  */

/** @brief  Reset COMP handle state.
  * @param  __HANDLE__  COMP handle
  * @retval None
  */
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
#define __HAL_COMP_RESET_HANDLE_STATE(__HANDLE__) do{                                                  \
                                                      (__HANDLE__)->State = HAL_COMP_STATE_RESET;      \
                                                      (__HANDLE__)->MspInitCallback = NULL;            \
                                                      (__HANDLE__)->MspDeInitCallback = NULL;          \
                                                    } while(0)
#else
#define __HAL_COMP_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_COMP_STATE_RESET)
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

/**
  * @brief Clear COMP error code (set it to no error code "HAL_COMP_ERROR_NONE").
  * @param __HANDLE__ COMP handle
  * @retval None
  */
#define COMP_CLEAR_ERRORCODE(__HANDLE__) ((__HANDLE__)->ErrorCode = HAL_COMP_ERROR_NONE)

/**
  * @brief  Enable the specified comparator.
  * @param  __HANDLE__ COMP handle
  * @retval None
  */
#define __HAL_COMP_ENABLE(__HANDLE__)        SET_BIT((__HANDLE__)->Instance->CFGR1, COMP_CFGR1_EN)

/**
  * @brief  Disable the specified comparator.
  * @param  __HANDLE__ COMP handle
  * @retval None
  */
#define __HAL_COMP_DISABLE(__HANDLE__)       CLEAR_BIT((__HANDLE__)->Instance->CFGR1, COMP_CFGR1_EN)

/**
  * @brief  Lock the specified comparator configuration.
  * @note   Using this macro induce HAL COMP handle state machine being no
  *         more in line with COMP instance state.
  *         To keep HAL COMP handle state machine updated, it is recommended
  *         to use function "HAL_COMP_Lock')".
  * @param  __HANDLE__ COMP handle
  * @retval None
  */
#define __HAL_COMP_LOCK(__HANDLE__)         SET_BIT((__HANDLE__)->Instance->CFGR1, COMP_CFGR1_LOCK)

/**
  * @brief  Check whether the specified comparator is locked.
  * @param  __HANDLE__  COMP handle
  * @retval Value 0 if COMP instance is not locked, value 1 if COMP instance is locked
  */
#define __HAL_COMP_IS_LOCKED(__HANDLE__)   (READ_BIT((__HANDLE__)->Instance->CFGR1, COMP_CFGR1_LOCK) == COMP_CFGR1_LOCK)

/**
  * @}
  */

/** @defgroup COMP_Exti_Management  COMP external interrupt line management
  * @{
  */

/** @brief  Checks if the specified COMP interrupt source is enabled or disabled.
  * @param  __HANDLE__ specifies the COMP Handle.
  *         This parameter can be COMP1.
  * @param  __INTERRUPT__ specifies the COMP interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg COMP_IT_EN Comparator interrupt enable
  *
  * @retval State of interruption (TRUE or FALSE)
  */
#define __HAL_COMP_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) \
  ((((__HANDLE__)->Instance->CFGR1 & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks whether the specified COMP flag is set or not.
  * @param  __FLAG__ specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg COMP_FLAG_C1I Comparator 1 Interrupt Flag
  *            @retval State of flag (TRUE or FALSE)
  */
#if defined(STM32H503xx)
#define __HAL_COMP_GET_FLAG(__FLAG__)     ((COMP1->SR & (__FLAG__)) == (__FLAG__))
#else
#define __HAL_COMP_GET_FLAG(__FLAG__)     ((COMP12->SR & (__FLAG__)) == (__FLAG__))
#endif /* STM32H503xx */

/** @brief  Clears the specified COMP pending flag.
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg COMP_CLEAR_C1IF Clear Comparator 1 Interrupt Flag
  * @retval None
  */
#if defined(STM32H503xx)
#define __HAL_COMP_CLEAR_FLAG(__FLAG__)   (COMP1->ICFR = (__FLAG__))
#else
#define __HAL_COMP_CLEAR_FLAG(__FLAG__)   (COMP12->ICFR = (__FLAG__))
#endif /* STM32H503xx */

/** @brief  Clear the COMP C1I  flag.
  * @retval None
  */
#define __HAL_COMP_CLEAR_C1IFLAG()   __HAL_COMP_CLEAR_FLAG( COMP_CLEAR_C1IF)

/** @brief  Enable the specified COMP interrupt.
  * @param  __HANDLE__ specifies the COMP Handle.
  * @param  __INTERRUPT__ specifies the COMP interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg COMP_CFGR1_ITEN Comparator  interrupt
  * @retval None
  */
#define __HAL_COMP_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (((__HANDLE__)->Instance->CFGR1) |= (__INTERRUPT__) )

/** @brief  Disable the specified COMP interrupt.
  * @param  __HANDLE__ specifies the COMP Handle.
  * @param  __INTERRUPT__ specifies the COMP interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg COMP_CFGR1_ITEN Comparator  interrupt
  * @retval None
  */
#define __HAL_COMP_DISABLE_IT(__HANDLE__,__INTERRUPT__) (((__HANDLE__)->Instance->CFGR1) &= ~(__INTERRUPT__))

#if !defined(STM32H503xx)
/**
  * @brief  Enable the COMP1 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_RISING_EDGE()      SET_BIT(EXTI->RTSR1, COMP_EXTI_LINE_COMP1)


/**
  * @brief  Disable the COMP1 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_RISING_EDGE()     CLEAR_BIT(EXTI->RTSR1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP1 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_FALLING_EDGE()     SET_BIT(EXTI->FTSR1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_FALLING_EDGE()    CLEAR_BIT(EXTI->FTSR1, COMP_EXTI_LINE_COMP1)


/**
  * @brief  Enable the COMP1 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_RISING_FALLING_EDGE()   do { \
                                                                  __HAL_COMP_COMP1_EXTI_ENABLE_RISING_EDGE(); \
                                                                  __HAL_COMP_COMP1_EXTI_ENABLE_FALLING_EDGE(); \
                                                                } while(0)

/**
  * @brief  Disable the COMP1 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_RISING_FALLING_EDGE()  do { \
                                                                  __HAL_COMP_COMP1_EXTI_DISABLE_RISING_EDGE(); \
                                                                  __HAL_COMP_COMP1_EXTI_DISABLE_FALLING_EDGE(); \
                                                                } while(0)

/**
  * @brief  Enable the COMP1 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_IT()                SET_BIT(EXTI->IMR1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_IT()               CLEAR_BIT(EXTI->IMR1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Generate a software interrupt on the COMP1 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_GENERATE_SWIT()            SET_BIT(EXTI->SWIER1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP1 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_ENABLE_EVENT()             SET_BIT(EXTI->EMR1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Disable the COMP1 EXTI line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_DISABLE_EVENT()            CLEAR_BIT(EXTI->EMR1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Check whether the COMP1 EXTI line rising flag is set or not.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP1_EXTI_GET_RISING_FLAG()          READ_BIT(EXTI->RPR1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Check whether the COMP1 EXTI line falling flag is set or not.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP1_EXTI_GET_FALLING_FLAG()         READ_BIT(EXTI->FPR1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Clear the COMP1 EXTI raising flag.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_CLEAR_RISING_FLAG()        WRITE_REG(EXTI->RPR1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Clear the COMP1 EXTI falling flag.
  * @retval None
  */
#define __HAL_COMP_COMP1_EXTI_CLEAR_FALLING_FLAG()       WRITE_REG(EXTI->FPR1, COMP_EXTI_LINE_COMP1)

/**
  * @brief  Enable the COMP2 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_RISING_EDGE()    SET_BIT(EXTI->RTSR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI line rising edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_RISING_EDGE()   CLEAR_BIT(EXTI->RTSR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Enable the COMP2 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI line falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Enable the COMP2 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_RISING_FALLING_EDGE() do {                                                        \
                                                                __HAL_COMP_COMP2_EXTI_ENABLE_RISING_EDGE();            \
                                                                __HAL_COMP_COMP2_EXTI_ENABLE_FALLING_EDGE();           \
                                                              } while(0)

/**
  * @brief  Disable the COMP2 EXTI line rising & falling edge trigger.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_RISING_FALLING_EDGE()   do { \
                                                                   __HAL_COMP_COMP2_EXTI_DISABLE_RISING_EDGE(); \
                                                                   __HAL_COMP_COMP2_EXTI_DISABLE_FALLING_EDGE(); \
                                                                 } while(0)
/**
  * @brief  Enable the COMP2 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_IT()                SET_BIT(EXTI->IMR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI line in interrupt mode.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_IT()               CLEAR_BIT(EXTI->IMR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Enable the COMP2 EXTI Line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_ENABLE_EVENT()             SET_BIT(EXTI->EMR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Disable the COMP2 EXTI Line in event mode.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_DISABLE_EVENT()            CLEAR_BIT(EXTI->EMR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Check whether the COMP2 EXTI line raising flag is set or not.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP2_EXTI_GET_RISING_FLAG()          READ_BIT(EXTI->RPR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Check whether the COMP2 EXTI line falling flag is set or not.
  * @retval RESET or SET
  */
#define __HAL_COMP_COMP2_EXTI_GET_FALLING_FLAG()         READ_BIT(EXTI->FPR1, COMP_EXTI_LINE_COMP2)


/**
  * @brief  Clear the the COMP2 EXTI raising flag.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_CLEAR_RISING_FLAG()        WRITE_REG(EXTI->RPR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Clear the the COMP2 EXTI falling flag.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_CLEAR_FALLING_FLAG()       WRITE_REG(EXTI->FPR1, COMP_EXTI_LINE_COMP2)

/**
  * @brief  Generate a software interrupt on the COMP2 EXTI line.
  * @retval None
  */
#define __HAL_COMP_COMP2_EXTI_GENERATE_SWIT()            SET_BIT(EXTI->SWIER1, COMP_EXTI_LINE_COMP2)

#endif /* STM32H503xx */
/**
  * @}
  */

/**
  * @}
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup COMP_Private_Constants COMP Private Constants
  * @{
  */

#if defined(COMP_WINDOW_MODE_SUPPORT)
/** @defgroup COMP_WindowMode_Instance_Differentiator COMP window mode instance differentiator
  * @{
  */
#define COMP_WINDOWMODE_COMP2          0x00001000U       /*!< COMP window mode using common input of COMP instance: COMP2 */
/**
  * @}
  */
#endif /* COMP_WINDOW_MODE_SUPPORT */

/** @defgroup COMP_ExtiLine COMP EXTI Lines
  * @{
  */
#if defined(STM32H503xx)
#define COMP_EXTI_LINE_COMP1           (LL_EXTI_LINE_29)  /*!< EXTI line 29 connected to COMP1 output */
#else
#define COMP_EXTI_LINE_COMP1           (LL_EXTI_LINE_58)  /*!< EXTI line 58 connected to COMP1 output */
#define COMP_EXTI_LINE_COMP2           (LL_EXTI_LINE_59)  /*!< EXTI line 59 connected to COMP2 output */
#endif /* STM32H503xx */
/**
  * @}
  */

/** @defgroup COMP_ExtiLine COMP EXTI Lines
  * @{
  */
#define COMP_EXTI_IT                        (0x00000001UL)  /*!< EXTI line event with interruption */
#define COMP_EXTI_EVENT                     (0x00000002UL)  /*!< EXTI line event only (without interruption) */
#define COMP_EXTI_RISING                    (0x00000010UL)  /*!< EXTI line event on rising edge */
#define COMP_EXTI_FALLING                   (0x00000020UL)  /*!< EXTI line event on falling edge */
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup COMP_Private_Macros COMP Private Macros
  * @{
  */

/** @defgroup COMP_GET_EXTI_LINE COMP private macros to get EXTI line associated with comparators
  * @{
  */
/**
  * @brief  Get the specified EXTI line for a comparator instance.
  * @param  __INSTANCE__  specifies the COMP instance.
  * @retval value of @ref COMP_ExtiLine
  */
#if defined(STM32H503xx)
#define COMP_GET_EXTI_LINE(__INSTANCE__)    (COMP_EXTI_LINE_COMP1)
#else
#define COMP_GET_EXTI_LINE(__INSTANCE__)    (((__INSTANCE__) == COMP1) ? COMP_EXTI_LINE_COMP1  \
                                             : COMP_EXTI_LINE_COMP2)
#endif /* STM32H503xx */
/**
  * @}
  */

/** @defgroup COMP_IS_COMP_Private_Definitions COMP private macros to check input parameters
  * @{
  */
#if defined(COMP_WINDOW_MODE_SUPPORT)
#define IS_COMP_WINDOWMODE(__WINDOWMODE__) \
  (((__WINDOWMODE__) == COMP_WINDOWMODE_DISABLE)                || \
   ((__WINDOWMODE__) == COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON)|| \
   ((__WINDOWMODE__) == COMP_WINDOWMODE_COMP2_INPUT_PLUS_COMMON)  )

#define IS_COMP_WINDOWOUTPUT(__WINDOWOUTPUT__) (((__WINDOWOUTPUT__) == COMP_WINDOWOUTPUT_EACH_COMP) || \
                                                ((__WINDOWOUTPUT__) == COMP_WINDOWOUTPUT_COMP1)     || \
                                                ((__WINDOWOUTPUT__) == COMP_WINDOWOUTPUT_COMP2)     || \
                                                ((__WINDOWOUTPUT__) == COMP_WINDOWOUTPUT_BOTH)        )
#endif /* COMP_WINDOW_MODE_SUPPORT */

#define IS_COMP_POWERMODE(__POWERMODE__)    (((__POWERMODE__) == COMP_POWERMODE_HIGHSPEED)    || \
                                             ((__POWERMODE__) == COMP_POWERMODE_MEDIUMSPEED)  || \
                                             ((__POWERMODE__) == COMP_POWERMODE_ULTRALOWPOWER)  )

#if defined(STM32H503xx)
#define IS_COMP_INPUT_PLUS(__COMP_INSTANCE__, __INPUT_PLUS__) (((__INPUT_PLUS__) == COMP_INPUT_PLUS_IO1) || \
                                                               ((__INPUT_PLUS__) == COMP_INPUT_PLUS_IO2) || \
                                                               ((__INPUT_PLUS__) == COMP_INPUT_PLUS_IO3) || \
                                                               ((__INPUT_PLUS__) == COMP_INPUT_PLUS_DAC1_CH1))
#else
/* Note: check of COMP_INPUT_PLUS_DAC1_CH2 done through other literals with same value */
#define IS_COMP_INPUT_PLUS(__COMP_INSTANCE__, __INPUT_PLUS__) (((__INPUT_PLUS__) == COMP_INPUT_PLUS_IO1) || \
                                                               ((__INPUT_PLUS__) == COMP_INPUT_PLUS_IO2) || \
                                                               ((__INPUT_PLUS__) == COMP_INPUT_PLUS_DAC1_CH1))
#endif /* STM32H503xx */

#if defined(STM32H503xx)
#define IS_COMP_INPUT_MINUS(__COMP_INSTANCE__, __INPUT_MINUS__) (((__INPUT_MINUS__) == COMP_INPUT_MINUS_1_4VREFINT) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_1_2VREFINT) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_3_4VREFINT) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_VREFINT)    || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH1)   || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO1)        || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO2)        || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO3)        || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_TEMPSENSOR) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_VBAT))
#else
/* Note: check of COMP_INPUT_MINUS_VDDCORE,COMP_INPUT_MINUS_IO3 done through other literals with same value */
#define IS_COMP_INPUT_MINUS(__COMP_INSTANCE__, __INPUT_MINUS__) (((__INPUT_MINUS__) == COMP_INPUT_MINUS_1_4VREFINT) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_1_2VREFINT) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_3_4VREFINT) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_VREFINT)    || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH1)   || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_DAC1_CH2)   || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO1)        || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_IO2)        || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_TEMPSENSOR) || \
                                                                 ((__INPUT_MINUS__) == COMP_INPUT_MINUS_VBAT))
#endif /* STM32H503xx */

#define IS_COMP_HYSTERESIS(__HYSTERESIS__)  (((__HYSTERESIS__) == COMP_HYSTERESIS_NONE)   || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_LOW)    || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_MEDIUM) || \
                                             ((__HYSTERESIS__) == COMP_HYSTERESIS_HIGH))

#define IS_COMP_OUTPUTPOL(__POL__)          (((__POL__) == COMP_OUTPUTPOL_NONINVERTED) || \
                                             ((__POL__) == COMP_OUTPUTPOL_INVERTED))

/* Note: For STM32H5Ex/Fx, check of literals specific to COMP2 done through other literals of COMP1 with same value */
#define IS_COMP_BLANKINGSRCE(__SOURCE__)    (((__SOURCE__) == COMP_BLANKINGSRC_NONE)       || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_TIM1_OC5)   || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_TIM2_OC3)   || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_TIM3_OC3)   || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_TIM3_OC4)   || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_LPTIM1_OC2) || \
                                             ((__SOURCE__) == COMP_BLANKINGSRC_LPTIM2_OC2))

#if defined(STM32H503xx)
#define IS_COMP_TRIGGERMODE(__MODE__)       (((__MODE__) == COMP_TRIGGERMODE_NONE)                 || \
                                             ((__MODE__) == COMP_TRIGGERMODE_IT_RISING_FALLING))
#else
#define IS_COMP_TRIGGERMODE(__MODE__)       (((__MODE__) == COMP_TRIGGERMODE_NONE)                 || \
                                             ((__MODE__) == COMP_TRIGGERMODE_IT_RISING)            || \
                                             ((__MODE__) == COMP_TRIGGERMODE_IT_FALLING)           || \
                                             ((__MODE__) == COMP_TRIGGERMODE_IT_RISING_FALLING)    || \
                                             ((__MODE__) == COMP_TRIGGERMODE_EVENT_RISING)         || \
                                             ((__MODE__) == COMP_TRIGGERMODE_EVENT_FALLING)        || \
                                             ((__MODE__) == COMP_TRIGGERMODE_EVENT_RISING_FALLING))
#endif /* STM32H503xx */

#define IS_COMP_OUTPUT_LEVEL(__OUTPUT_LEVEL__) (((__OUTPUT_LEVEL__) == COMP_OUTPUT_LEVEL_LOW)     || \
                                                ((__OUTPUT_LEVEL__) == COMP_OUTPUT_LEVEL_HIGH))

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup COMP_Exported_Functions
  * @{
  */

/** @addtogroup COMP_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions */
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_DeInit(COMP_HandleTypeDef *hcomp);
void              HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp);
void              HAL_COMP_MspDeInit(COMP_HandleTypeDef *hcomp);
#if (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
/* Callbacks Register/UnRegister functions */
HAL_StatusTypeDef HAL_COMP_RegisterCallback(COMP_HandleTypeDef *hcomp, HAL_COMP_CallbackIDTypeDef CallbackID,
                                            pCOMP_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_COMP_UnRegisterCallback(COMP_HandleTypeDef *hcomp, HAL_COMP_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
/**
  * @}
  */

/* IO operation functions */
/** @addtogroup COMP_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp);
#if defined(STM32H503xx)
HAL_StatusTypeDef HAL_COMP_Start_IT_OneShot(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Start_IT_AutoRearm(COMP_HandleTypeDef *hcomp);
#else
HAL_StatusTypeDef HAL_COMP_Start_IT(COMP_HandleTypeDef *hcomp);
#endif /* STM32H503xx */

HAL_StatusTypeDef HAL_COMP_Stop_IT(COMP_HandleTypeDef *hcomp);
void              HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp);

/**
  * @}
  */

/* Peripheral Control functions */
/** @addtogroup COMP_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef *hcomp);
uint32_t          HAL_COMP_GetOutputLevel(const COMP_HandleTypeDef *hcomp);
/* Callback in interrupt mode */
void              HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/* Peripheral State functions */
/** @addtogroup COMP_Exported_Functions_Group4
  * @{
  */
HAL_COMP_StateTypeDef HAL_COMP_GetState(const COMP_HandleTypeDef *hcomp);
uint32_t              HAL_COMP_GetError(const COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* COMP1 || COMP2 */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H5xx_HAL_COMP_H */
