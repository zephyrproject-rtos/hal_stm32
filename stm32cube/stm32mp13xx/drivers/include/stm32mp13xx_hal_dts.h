/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_dts.h
  * @author  MCD Application Team
  * @brief   Header file of DTS HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP13xx_HAL_DTS_H
#define __STM32MP13xx_HAL_DTS_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DTS1)
/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal_def.h"

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @addtogroup DTS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup DTS_Exported_Types DTS Exported Types
  * @{
  */

/**
  * @brief  DTS Init structure definition
  */
typedef struct
{
  uint32_t QuickMeasure;  /*!< Specifies the quick measure option selection of the DTS sensor.
                               This parameter can be a value of @ref DTS_Quick_Measurement */

  uint32_t RefClock;      /*!< Specifies the reference clock selection of the DTS sensor.
                               This parameter can be a value of @ref DTS_Reference_Clock_Selection */

  uint32_t TriggerInput;  /*!< Specifies the trigger input of the DTS sensor.
                               This parameter can be a value of @ref DTS_TriggerConfig */

  uint32_t SamplingTime;  /*!< Specifies the sampling time configuration.
                               This parameter can be a value of @ref DTS_Sampling_Time */

  uint32_t Divider;       /*!< Specifies the high speed clock divider ratio.
                               This parameter can be a value from 0 to 127 */

  uint32_t InterruptSource; /*!< Specifies the interrupt source of the DTS sensor.
                                 This parameter can be a value of @ref DTS_InterruptSource_Definitions */

  uint32_t HighInterruptThreshold;  /*!< Specifies the high Interrupt threshold of the DTS sensor */

  uint32_t LowInterruptThreshold; /*!<  Specifies the low Interrupt threshold of the DTS sensor */
#ifdef __STM32MP13xx_H
  uint32_t WakeupTarget;  /*!< Specifies the Wakeup Target.
                               This parameter can be a value of @ref DTS_WakeupTarget_Definitions */
#endif /* __STM32MP13xx_H */
} DTS_InitTypeDef;


/**
  * @brief  DTS Measure structure definition
  */
typedef struct
{
  uint32_t Ts1_Sample;    /*!< Specifies the measured sample number for DTS1
                              (for debug purposes) */
  uint32_t Ts1_Fmt;       /*!< Specifies the measured frequency for DTS1
                              (for debug purposes) */
  uint32_t Ts1_Temp;      /*!< Specifies the measured temperature for DTS1 */
  uint32_t Ts1_Count_R;   /*!< Specifies the number of reads before getting a SW
                               measured temperature for DTS1
                               (for debug purposes)*/
} DTS_MeasureTypeDef;

/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_DTS_STATE_RESET       = 0x00UL,     /*!< DTS not yet initialized or disabled */
  HAL_DTS_STATE_READY       = 0x01UL,     /*!< DTS initialized and ready for use */
  HAL_DTS_STATE_BUSY        = 0x02UL,     /*!< DTS is running                      */
  HAL_DTS_STATE_TIMEOUT     = 0x03UL,     /*!< Timeout state                       */
  HAL_DTS_STATE_ERROR       = 0x04UL      /*!< Internal Process error              */
} HAL_DTS_StateTypeDef;

/**
  * @brief  DTS Handle Structure definition
  */
#if (USE_HAL_DTS_REGISTER_CALLBACKS == 1)
typedef struct __DTS_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */
{
  DTS_TypeDef         *Instance;    /*!< Register base address */
  DTS_InitTypeDef     Init;         /*!< DTS required parameters */
  DTS_MeasureTypeDef  Measure;      /*!< DTS Measured values */
  HAL_LockTypeDef     Lock;         /*!< DTS Locking object */
  __IO HAL_DTS_StateTypeDef  State; /*!< DTS peripheral  state */
#if (USE_HAL_DTS_REGISTER_CALLBACKS == 1)
  void (* MspInitCallback)(struct __DTS_HandleTypeDef *hdts);         /*!< DTS Base Msp Init Callback                   */
  void (* MspDeInitCallback)(struct __DTS_HandleTypeDef *hdts);       /*!< DTS Base Msp DeInit Callback                 */
  void (* EndCallback)(struct __DTS_HandleTypeDef *hdts);         /*!< End measure Callback                         */
  void (* LowCallback)(struct __DTS_HandleTypeDef *hdts);         /*!< low threshold Callback                       */
  void (* HighCallback)(struct __DTS_HandleTypeDef *hdts);        /*!< high threshold Callback                      */
  void (* AsyncEndCallback)(struct __DTS_HandleTypeDef *hdts);    /*!< Asynchronous end of measure Callback         */
  void (* AsyncLowCallback)(struct __DTS_HandleTypeDef *hdts);    /*!< Asynchronous low threshold Callback          */
  void (* AsyncHighCallback)(struct __DTS_HandleTypeDef *hdts);   /*!< Asynchronous high threshold Callback         */
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */
} DTS_HandleTypeDef;

#if (USE_HAL_DTS_REGISTER_CALLBACKS == 1U)
/**
  * @brief  DTS callback ID enumeration definition
  */
typedef enum
{
  HAL_DTS_MEAS_COMPLETE_CB_ID        = 0x00U, /*!< Measure complete callback ID */
  HAL_DTS_ASYNC_MEAS_COMPLETE_CB_ID  = 0x01U, /*!< Asynchronous measure complete callback ID */
  HAL_DTS_LOW_THRESHOLD_CB_ID        = 0x02U, /*!< Low threshold detection callback ID */
  HAL_DTS_ASYNC_LOW_THRESHOLD_CB_ID  = 0x03U, /*!< Asynchronous low threshold detection callback ID */
  HAL_DTS_HIGH_THRESHOLD_CB_ID       = 0x04U, /*!< High threshold detection callback ID */
  HAL_DTS_ASYNC_HIGH_THRESHOLD_CB_ID = 0x05U, /*!< Asynchronous high threshold detection callback ID */
  HAL_DTS_MSPINIT_CB_ID              = 0x06U, /*!< MSP init callback ID */
  HAL_DTS_MSPDEINIT_CB_ID            = 0x07U  /*!< MSP de-init callback ID */
} HAL_DTS_CallbackIDTypeDef;

/**
  * @brief  DTS callback pointers definition
  */
typedef void (*pDTS_CallbackTypeDef)(DTS_HandleTypeDef *hdts);
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DTS_Exported_Constants DTS Exported Constants
  * @{
  */

/** @defgroup DTS_TriggerConfig  DTS Trigger Configuration
  * @{
  */

/* @brief No Hardware trigger detection */
#define DTS_TRIGGER_HW_NONE   (0UL)

/* @brief External Interrupt Mode with LPTIMER1 trigger detection */
#define DTS_TRIGGER_LPTIMER1  DTS_CFGR1_TS1_INTRIG_SEL_0

/* @brief External Interrupt Mode with LPTIMER2 trigger detection */
#define DTS_TRIGGER_LPTIMER2  DTS_CFGR1_TS1_INTRIG_SEL_1

/* @brief External Interrupt Mode with LPTIMER3 trigger detection */
#define DTS_TRIGGER_LPTIMER3  (DTS_CFGR1_TS1_INTRIG_SEL_0 | DTS_CFGR1_TS1_INTRIG_SEL_1)

/* @brief External Interrupt Mode with EXTI13 trigger detection */
#define DTS_TRIGGER_SYSCFG_EXTI13 DTS_CFGR1_TS1_INTRIG_SEL_2

/* @brief No Hardware trigger detection on continuous mode */
#define DTS_TRIGGER_HW_NONE_CONT  (DTS_CFGR1_TS1_INTRIG_SEL_0 | DTS_CFGR1_TS1_INTRIG_SEL_1 | DTS_CFGR1_TS1_INTRIG_SEL_2)
/**
  * @}
  */

/** @defgroup DTS_Quick_Measurement  DTS Quick Measurement
  * @{
  */
#define DTS_QUICKMEAS_ENABLE    DTS_CFGR1_Q_MEAS_OPT      /*!< Enable the Quick Measure (Measure without calibration) */
#define DTS_QUICKMEAS_DISABLE   (0x0UL)                   /*!< Disable the Quick Measure (Measure with calibration) */
/**
  * @}
  */

/** @defgroup DTS_Reference_Clock_Selection   DTS Reference Clock Selection
  * @{
  */
#define DTS_REFCLKSEL_LSE  DTS_CFGR1_REFCLK_SEL  /*!< Low speed REF clock (LSE) */
#define DTS_REFCLKSEL_PCLK (0UL) /*!< High speed REF clock (PCLK) */

/**
  * @}
  */

/** @defgroup DTS_Sampling_Time   DTS Sampling Time
  * @{
  */
#define DTS_SMP_TIME_1_CYCLE     DTS_CFGR1_TS1_SMP_TIME_0                                                                                   /*!< 1 clock cycle for the sampling time  */
#define DTS_SMP_TIME_2_CYCLE     DTS_CFGR1_TS1_SMP_TIME_1                                                                                   /*!< 2 clock cycle for the sampling time  */
#define DTS_SMP_TIME_3_CYCLE    (DTS_CFGR1_TS1_SMP_TIME_0 | DTS_CFGR1_TS1_SMP_TIME_1)                                                       /*!< 3 clock cycle for the sampling time  */
#define DTS_SMP_TIME_4_CYCLE    (DTS_CFGR1_TS1_SMP_TIME_2)                                                                                 /*!< 4 clock cycle for the sampling time  */
#define DTS_SMP_TIME_5_CYCLE    (DTS_CFGR1_TS1_SMP_TIME_0 | DTS_CFGR1_TS1_SMP_TIME_2)                                                       /*!< 5 clock cycle for the sampling time  */
#define DTS_SMP_TIME_6_CYCLE    (DTS_CFGR1_TS1_SMP_TIME_1 | DTS_CFGR1_TS1_SMP_TIME_2)                                                       /*!< 6 clock cycle for the sampling time  */
#define DTS_SMP_TIME_7_CYCLE    (DTS_CFGR1_TS1_SMP_TIME_0 | DTS_CFGR1_TS1_SMP_TIME_1 | DTS_CFGR1_TS1_SMP_TIME_2)                            /*!< 7 clock cycle for the sampling time  */
#define DTS_SMP_TIME_8_CYCLE    (DTS_CFGR1_TS1_SMP_TIME_3)                                                                                  /*!< 8 clock cycle for the sampling time  */
#define DTS_SMP_TIME_9_CYCLE    (DTS_CFGR1_TS1_SMP_TIME_0 | DTS_CFGR1_TS1_SMP_TIME_3)                                                       /*!< 9 clock cycle for the sampling time  */
#define DTS_SMP_TIME_10_CYCLE   (DTS_CFGR1_TS1_SMP_TIME_1 | DTS_CFGR1_TS1_SMP_TIME_3)                                                       /*!< 10 clock cycle for the sampling time */
#define DTS_SMP_TIME_11_CYCLE   (DTS_CFGR1_TS1_SMP_TIME_0 | DTS_CFGR1_TS1_SMP_TIME_1 | DTS_CFGR1_TS1_SMP_TIME_3)                            /*!< 11 clock cycle for the sampling time */
#define DTS_SMP_TIME_12_CYCLE   (DTS_CFGR1_TS1_SMP_TIME_2 | DTS_CFGR1_TS1_SMP_TIME_3)                                                       /*!< 12 clock cycle for the sampling time */
#define DTS_SMP_TIME_13_CYCLE   (DTS_CFGR1_TS1_SMP_TIME_0 | DTS_CFGR1_TS1_SMP_TIME_2 | DTS_CFGR1_TS1_SMP_TIME_3)                            /*!< 13 clock cycle for the sampling time */
#define DTS_SMP_TIME_14_CYCLE   (DTS_CFGR1_TS1_SMP_TIME_1 | DTS_CFGR1_TS1_SMP_TIME_2 | DTS_CFGR1_TS1_SMP_TIME_3)                            /*!< 14 clock cycle for the sampling time */
#define DTS_SMP_TIME_15_CYCLE   (DTS_CFGR1_TS1_SMP_TIME_0 | DTS_CFGR1_TS1_SMP_TIME_1 | DTS_CFGR1_TS1_SMP_TIME_2 | DTS_CFGR1_TS1_SMP_TIME_3) /*!< 15 clock cycle for the sampling time */
/**
  * @}
  */
/** @defgroup DTS_InterruptSource_Definitions  DTS Interrupt Source Definitions
  * @{
  */
#define DTS_ITSRC_HIGH      DTS_ITENR_TS1_ITHEN
#define DTS_ITSRC_LOW       DTS_ITENR_TS1_ITLEN
#define DTS_ITSRC_END       DTS_ITENR_TS1_ITEEN
#define DTS_ITSRC_ASYN_HIGH DTS_ITENR_TS1_AITHEN
#define DTS_ITSRC_ASYN_LOW  DTS_ITENR_TS1_AITLEN
#define DTS_ITSRC_ASYN_END  DTS_ITENR_TS1_AITEEN

/**
  * @}
  */

/** @defgroup DTS_WakeupTarget_Definitions DTS Wakeup Target Definitions
  * @{
  */
#define DTS_WAKEUPTARGET_CPU1 (1UL)
#define DTS_WAKEUPTARGET_CPU2 (2UL)
/**
  * @}
  */
/** @defgroup DTS_Flag_Definitions DTS Flag Definitions
  * @{
  */
#define DTS_FLAG_TS1_ITEF   DTS_SR_TS1_ITEF   /*!< Interrupt flag for end of measure for DTS1 */
#define DTS_FLAG_TS1_ITLF   DTS_SR_TS1_ITLF   /*!< Interrupt flag for low threshold for DTS1  */
#define DTS_FLAG_TS1_ITHF   DTS_SR_TS1_ITHF   /*!< Interrupt flag for high threshold for DTS1 */
#define DTS_FLAG_TS1_AITEF  DTS_SR_TS1_AITEF  /*!< Asynchronous Interrupt flag for end of measure for DTS1 */
#define DTS_FLAG_TS1_AITLF  DTS_SR_TS1_AITLF  /*!< Asynchronous Interrupt flag for low threshold for DTS1  */
#define DTS_FLAG_TS1_AITHF  DTS_SR_TS1_AITHF  /*!< Asynchronous Interrupt flag for high threshold for DTS1 */
#define DTS_FLAG_TS1_RDY    DTS_SR_TS1_RDY    /*!< Ready flag for DTS1 */

/**
  * @}
  */
/** @defgroup DTS_IT_CLEAR Flags  DTS Interruption Clear Flags
  * @{
  */
#define DTS_CLEAR_TS1_CITEF   DTS_ICIFR_TS1_CITEF   /*!< Clear Interrupt flag for end of measure for DTS1 */
#define DTS_CLEAR_TS1_CITLF   DTS_ICIFR_TS1_CITLF   /*!< Clear Interrupt flag for low threshold for DTS1  */
#define DTS_CLEAR_TS1_CITHF   DTS_ICIFR_TS1_CITHF   /*!< Clear Interrupt flag for high threshold for DTS1 */
#define DTS_CLEAR_TS1_CAITEF  DTS_ICIFR_TS1_CAITEF  /*!< Clear Asynchronous Interrupt flag for end of measure for DTS1 */
#define DTS_CLEAR_TS1_CAITLF  DTS_ICIFR_TS1_CAITLF  /*!< Clear Asynchronous Interrupt flag for low threshold for DTS1  */
#define DTS_CLEAR_TS1_CAITHF  DTS_ICIFR_TS1_CAITHF  /*!< Clear Asynchronous Interrupt flag for high threshold for DTS1 */

/**
  * @}
  */
/** @defgroup DTS_Interrupts_Definitions DTS Interrupts Definitions
  * @{
  */
#define DTS_IT_TS1_ITEEN  DTS_ITENR_TS1_ITEEN   /*!< Enable interrupt flag for end of measure for DTS1 */
#define DTS_IT_TS1_ITLEN  DTS_ITENR_TS1_ITLEN   /*!< Enable interrupt flag for low threshold for DTS1  */
#define DTS_IT_TS1_ITHEN  DTS_ITENR_TS1_ITHEN   /*!< Enable interrupt flag for high threshold for DTS1 */
#define DTS_IT_TS1_AITEEN DTS_ITENR_TS1_AITEEN  /*!< Enable asynchronous interrupt flag for end of measure for DTS1 */
#define DTS_IT_TS1_AITLEN DTS_ITENR_TS1_AITLEN  /*!< Enable asynchronous interrupt flag for low threshold for DTS1  */
#define DTS_IT_TS1_AITHEN DTS_ITENR_TS1_AITHEN  /*!< Enable asynchronous interrupt flag for high threshold for DTS1 */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macros -----------------------------------------------------------*/
/** @defgroup DTS_Exported_Macros DTS Exported Macros
  * @{
  */

/** @brief  Reset DTS handle state
  * @param  __HANDLE__ DTS handle.
  * @retval None
  */
#if (USE_HAL_DTS_REGISTER_CALLBACKS == 1U)
#define __HAL_DTS_RESET_HANDLE_STATE(__HANDLE__) do{                                             \
                                                      (__HANDLE__)->State = HAL_DTS_STATE_RESET; \
                                                      (__HANDLE__)->MspInitCallback = NULL;      \
                                                      (__HANDLE__)->MspDeInitCallback = NULL;    \
                                                    } while(0)
#else /* USE_HAL_DTS_REGISTER_CALLBACKS */
#define __HAL_DTS_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DTS_STATE_RESET)
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */

/**
  * @brief  Enable the specified DTS sensor
  * @param  __HANDLE__ DTS handle.
  * @retval None
  */
#define __HAL_DTS_ENABLE(__HANDLE__) SET_BIT((__HANDLE__)->Instance->CFGR1, DTS_CFGR1_TS1_EN)

/**
  * @brief  Disable the specified DTS sensor
  * @param  __HANDLE__ DTS handle.
  * @retval None
  */
#define __HAL_DTS_DISABLE(__HANDLE__) CLEAR_BIT((__HANDLE__)->Instance->CFGR1, DTS_CFGR1_TS1_EN)

#if defined(CORE_CA7)
/**
  * @brief  Enable the DTS EXTI line in interrupt mode
  * @retval None
  */
#define __HAL_DTS_EXTI_ENABLE_IT() SET_BIT(EXTI_C1->IMR3,DTS_EXTI_LINE_DTS1)

/**
  * @brief  Disable the DTS EXTI line in interrupt mode
  * @retval None
  */
#define __HAL_DTS_EXTI_DISABLE_IT() CLEAR_BIT(EXTI_C1->IMR3,DTS_EXTI_LINE_DTS1)

/**
  * @brief  Enable the DTS EXTI Line in event mode
  * @retval None
  */
#define __HAL_DTS_EXTI_ENABLE_EVENT() SET_BIT(EXTI_C1->EMR3,DTS_EXTI_LINE_DTS1)

/**
  * @brief  Disable the DTS EXTI Line in event mode
  * @retval None
  */
#define __HAL_DTS_EXTI_DISABLE_EVENT() CLEAR_BIT(EXTI_C1->EMR3, DTS_EXTI_LINE_DTS1)

#endif /* CORE_CA7 */

/** @brief  Checks whether the specified DTS flag is set or not.
  * @param  __HANDLE__ specifies the DTS Handle.
  * @param  __FLAG__ specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg DTS_FLAG_TS1_ITEF:  Interrupt flag for end of measure for DTS1
  *            @arg DTS_FLAG_TS1_ITLF:  Interrupt flag for low threshold for DTS1
  *            @arg DTS_FLAG_TS1_ITHF:  Interrupt flag for high threshold for DTS1
  *            @arg DTS_FLAG_TS1_AITEF: Asynchronous Interrupt flag for end of measure for DTS1
  *            @arg DTS_FLAG_TS1_AITLF: Asynchronous Interrupt flag for low threshold for DTS1
  *            @arg DTS_FLAG_TS1_AITHF: Asynchronous Interrupt flag for high threshold for DTS1
  *            @arg DTS_FLAG_TS1_RDY:   Ready flag for DTS1
  *            @retval The new state of __FLAG__ (1 or 0).
  */
#define __HAL_DTS_GET_FLAG(__HANDLE__, __FLAG__) \
  (((((__HANDLE__)->Instance->SR &(__FLAG__)) == (__FLAG__)))? 1U : 0U)


/** @brief  Clears the specified DTS pending flag.
  * @param  __HANDLE__ specifies the DTS Handle.
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg DTS_CLEAR_TS1_CITEF: Clear Interrupt flag for end of measure for DTS1
  *            @arg DTS_CLEAR_TS1_CITLF: Clear Interrupt flag for low threshold for DTS1
  *            @arg DTS_CLEAR_TS1_CITHF: Clear Interrupt flag for high threshold for DTS1
  *            @arg DTS_CLEAR_TS1_CAITEF: Clear Asynchronous Interrupt flag for end of measure for DTS1
  *            @arg DTS_CLEAR_TS1_CAITLF: Clear Asynchronous Interrupt flag for low threshold for DTS1
  *            @arg DTS_CLEAR_TS1_CAITHF: Clear Asynchronous Interrupt flag for high threshold for DTS1
  * @retval None
  */
#define __HAL_DTS_CLEAR_FLAG(__HANDLE__, __FLAG__) \
  ((__HANDLE__)->Instance->ICIFR  = (__FLAG__))


/** @brief  Enable the specified DTS interrupt.
  * @param  __HANDLE__ specifies the DTS Handle.
  * @param  __INTERRUPT__ specifies the DTS interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg DTS_IT_TS1_ITEEN : interrupt flag for end of measure for DTS1
  *            @arg DTS_IT_TS1_ITLEN : interrupt flag for low of measure for DTS1
  *            @arg DTS_IT_TS1_ITHEN : interrupt flag for high of measure for DTS1
  *            @arg DTS_IT_TS1_AITEEN : asynchronous interrupt flag for end of measure for DTS1
  *            @arg DTS_IT_TS1_AITLEN : asynchronous interrupt flag for low of measure for DTS1
  *            @arg DTS_IT_TS1_AITHEN : asynchronous interrupt flag for high of measure for DTS1
  * @retval None
  */
#define __HAL_DTS_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
  SET_BIT((__HANDLE__)->Instance->ITENR, __INTERRUPT__)


/** @brief  Disable the specified DTS interrupt.
  * @param  __HANDLE__ specifies the DTS Handle.
  * @param  __INTERRUPT__ specifies the DTS interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg DTS_IT_TS1_ITEEN : interrupt flag for end of measure for DTS1
  *            @arg DTS_IT_TS1_ITLEN : interrupt flag for low of measure for DTS1
  *            @arg DTS_IT_TS1_ITHEN : interrupt flag for high of measure for DTS1
  *            @arg DTS_IT_TS1_AITEEN : asynchronous interrupt flag for end of measure for DTS1
  *            @arg DTS_IT_TS1_AITLEN : asynchronous interrupt flag for low of measure for DTS1
  *            @arg DTS_IT_TS1_AITHEN : asynchronous interrupt flag for high of measure for DTS1
  * @retval None
  */
#define __HAL_DTS_DISABLE_IT(__HANDLE__,__INTERRUPT__) \
  CLEAR_BIT((__HANDLE__)->Instance->ITENR, __INTERRUPT__)


/** @brief  Check whether the specified DTS interrupt source is enabled or not.
  * @param __HANDLE__ DTS handle.
  * @param __INTERRUPT__ DTS interrupt source to check
  *          This parameter can be one of the following values:
  *            @arg DTS_IT_TS1_ITEEN : interrupt flag for end of measure for DTS1
  *            @arg DTS_IT_TS1_ITLEN : interrupt flag for low of measure for DTS1
  *            @arg DTS_IT_TS1_ITHEN : interrupt flag for high of measure for DTS1
  *            @arg DTS_IT_TS1_AITEEN : asynchronous interrupt flag for end of measure for DTS1
  *            @arg DTS_IT_TS1_AITLEN : asynchronous interrupt flag for low of measure for DTS1
  *            @arg DTS_IT_TS1_AITHEN : asynchronous interrupt flag for high of measure for DTS1
  * @retval State of interruption (1 or 0)
  */
#define __HAL_DTS_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  \
  ((((__HANDLE__)->Instance->ITENR & (__INTERRUPT__)) == (__INTERRUPT__))? 1U : 0U)


/** @brief  Check whether the specified DTS REFCLK is selected
  * @param __HANDLE__ DTS handle.
  * @param __REFCLK__ DTS reference clock to check
  *          This parameter can be one of the following values:
  * @arg DTS_REFCLKSEL_LSE:   Low speed REF clock
  * @arg DTS_REFCLKSEL_PCLK:  High speed REF clock
  * @retval State of the REF clock tested (1 or 0)
  */
#define __HAL_DTS_GET_REFCLK(__HANDLE__, __REFCLK__) \
  ((((__HANDLE__)->Instance->CFGR1 & (__REFCLK__)) == (__REFCLK__))? 1U : 0U)

/** @brief  Get Trigger
  * @param __HANDLE__ DTS handle.
  * @retval One of the following trigger
  *     DTS_TRIGGER_HW_NONE : No HW trigger (SW trigger)
  *     DTS_TRIGGER_LPTIMER1: LPTIMER1 trigger
  *     DTS_TRIGGER_LPTIMER2: LPTIMER2 trigger
  *     DTS_TRIGGER_LPTIMER3: LPTIMER3 trigger
  *     DTS_TRIGGER_SYSCFG_EXTI13: EXTI13 trigger
  */
#define __HAL_DTS_GET_TRIGGER(__HANDLE__)  ((__HANDLE__)->Instance->CFGR1 & (DTS_CFGR1_TS1_INTRIG_SEL))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DTS_Exported_Functions
  * @{
  */

/** @addtogroup DTS_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_DTS_Init(DTS_HandleTypeDef *hdts);
HAL_StatusTypeDef HAL_DTS_DeInit(DTS_HandleTypeDef *hdts);
void              HAL_DTS_MspInit(DTS_HandleTypeDef *hdts);
void              HAL_DTS_MspDeInit(DTS_HandleTypeDef *hdts);
#if (USE_HAL_DTS_REGISTER_CALLBACKS == 1U)
HAL_StatusTypeDef HAL_DTS_RegisterCallback(DTS_HandleTypeDef        *hdts,
                                           HAL_DTS_CallbackIDTypeDef CallbackID,
                                           pDTS_CallbackTypeDef      pCallback);
HAL_StatusTypeDef HAL_DTS_UnRegisterCallback(DTS_HandleTypeDef        *hdts,
                                             HAL_DTS_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */
/**
  * @}
  */

/* IO operation functions  *****************************************************/
/** @addtogroup DTS_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_DTS_Start(DTS_HandleTypeDef *hdts);
HAL_StatusTypeDef HAL_DTS_Stop(DTS_HandleTypeDef *hdts);
HAL_StatusTypeDef HAL_DTS_GetTemperature(DTS_HandleTypeDef *hdts, int32_t *Temperature);
HAL_StatusTypeDef HAL_DTS_Start_IT(DTS_HandleTypeDef *hdts);
HAL_StatusTypeDef HAL_DTS_Stop_IT(DTS_HandleTypeDef *hdts);
void              HAL_DTS_IRQHandler(DTS_HandleTypeDef *hdts);
HAL_DTS_StateTypeDef HAL_DTS_GetState(const DTS_HandleTypeDef *hdts);
/* Callback in Interrupt mode */
void              HAL_DTS_EndCallback(DTS_HandleTypeDef *hdts);
void              HAL_DTS_LowCallback(DTS_HandleTypeDef *hdts);
void              HAL_DTS_HighCallback(DTS_HandleTypeDef *hdts);
void              HAL_DTS_AsyncEndCallback(DTS_HandleTypeDef *hdts);
void              HAL_DTS_AsyncLowCallback(DTS_HandleTypeDef *hdts);
void              HAL_DTS_AsyncHighCallback(DTS_HandleTypeDef *hdts);
/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup DTS_Private_Constants DTS Private Constants
  * @{
  */
/** @defgroup DTS_ExtiLine DTS EXTI Lines
  * @{
  */
#define DTS_EXTI_LINE_DTS1           (EXTI_IMR3_IM72)  /*!< EXTI line 72 connected to DTS1 output */
/**
  * @}
  */

/** @defgroup DTS_IT_Type DTS IT Type
  * @{
  */
#define DTS_IT_ASYNC  (DTS_IT_TS1_AITEEN | DTS_IT_TS1_AITLEN | DTS_IT_TS1_AITHEN) /*!< DTS ASYNC IT */
#define DTS_IT_SYNC   (DTS_IT_TS1_ITEEN | DTS_IT_TS1_ITLEN | DTS_IT_TS1_ITHEN)    /*!< DTS SYNC IT */
/**
  * @}
  */


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DTS_Private_Macros DTS Private Macros
  * @{
  */

/** @defgroup DTS_IS_DTS_Definitions  DTS Private macros to check input parameters
  * @{
  */
#define IS_DTS_QUICKMEAS(__SEL__)   (((__SEL__) == DTS_QUICKMEAS_DISABLE) || \
                                     ((__SEL__) == DTS_QUICKMEAS_ENABLE))

#define IS_DTS_REFCLK(__SEL__)      (((__SEL__) == DTS_REFCLKSEL_LSE) || \
                                     ((__SEL__) == DTS_REFCLKSEL_PCLK))


#define IS_DTS_TRIGGERINPUT(__INPUT__)  (((__INPUT__) == DTS_TRIGGER_HW_NONE)   || \
                                         ((__INPUT__) == DTS_TRIGGER_LPTIMER1)  || \
                                         ((__INPUT__) == DTS_TRIGGER_LPTIMER2)  || \
                                         ((__INPUT__) == DTS_TRIGGER_LPTIMER3)  || \
                                         ((__INPUT__) == DTS_TRIGGER_SYSCFG_EXTI13) || \
                                         ((__INPUT__) == DTS_TRIGGER_HW_NONE_CONT))

#define IS_DTS_INTERRUPTTHRESHOLD(__THRESHOLD__)  ((__THRESHOLD__) <= 0xFFFFUL)

#define IS_DTS_DIVIDER_RATIO_NUMBER(__NUMBER__) ((__NUMBER__) <= 127UL)

#define IS_DTS_SAMPLINGTIME(__CYCLE__)  (((__CYCLE__) == DTS_SMP_TIME_1_CYCLE)  || \
                                         ((__CYCLE__) == DTS_SMP_TIME_2_CYCLE)    || \
                                         ((__CYCLE__) == DTS_SMP_TIME_3_CYCLE)    || \
                                         ((__CYCLE__) == DTS_SMP_TIME_4_CYCLE)    || \
                                         ((__CYCLE__) == DTS_SMP_TIME_5_CYCLE)    || \
                                         ((__CYCLE__) == DTS_SMP_TIME_6_CYCLE)    || \
                                         ((__CYCLE__) == DTS_SMP_TIME_7_CYCLE)    || \
                                         ((__CYCLE__) == DTS_SMP_TIME_8_CYCLE)    || \
                                         ((__CYCLE__) == DTS_SMP_TIME_9_CYCLE)    || \
                                         ((__CYCLE__) == DTS_SMP_TIME_10_CYCLE)   || \
                                         ((__CYCLE__) == DTS_SMP_TIME_11_CYCLE)   || \
                                         ((__CYCLE__) == DTS_SMP_TIME_12_CYCLE)   || \
                                         ((__CYCLE__) == DTS_SMP_TIME_13_CYCLE)   || \
                                         ((__CYCLE__) == DTS_SMP_TIME_14_CYCLE)   || \
                                         ((__CYCLE__) == DTS_SMP_TIME_15_CYCLE))
/* All combinations of interrupts are allowed */
#define IS_DTS_INTERRUPTSOURCE(__SOURCE__)  ((((__SOURCE__) & ~(DTS_IT_ASYNC | DTS_IT_SYNC)) == 0U) && \
                                             (((__SOURCE__) & (DTS_IT_ASYNC | DTS_IT_SYNC)) != 0U))
/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#endif /* DTS1 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP13xx_HAL_DTS_H */
