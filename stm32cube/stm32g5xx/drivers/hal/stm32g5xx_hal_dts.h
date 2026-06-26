/**
  *********************************************************************************************************************
  * @file    stm32g5xx_hal_dts.h
  * @brief   Header file of DTS HAL module.
  *********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *********************************************************************************************************************
  */

/* Define to prevent recursive inclusion ----------------------------------------------------------------------------*/
#ifndef STM32G5XX_HAL_DTS_H
#define STM32G5XX_HAL_DTS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */
#if defined(DTS)

/** @addtogroup DTS
  * @{
  */

/* Exported constants -----------------------------------------------------------------------------------------------*/
/** @defgroup DTS_Exported_Constants HAL DTS Constants
  * @{
  */

/** @defgroup DTS_Optional_Interrupts_Definitions DTS Optional Interrupts Definitions
  * @note     Used by HAL DTS process function. Refer to @ref HAL_DTS_StartSensor_IT_Opt().
  * @{
  */

#define HAL_DTS_OPT_IT_END_OF_MEASURE DTS_ITENR_TS1_ITEEN               /*!< End of measure optional IT on
                                                                             selected temperature sensor */
#define HAL_DTS_OPT_IT_LOW_THRESHOLD  DTS_ITENR_TS1_ITLEN               /*!< Low threshold optional IT on
                                                                             selected temperature sensor */
#define HAL_DTS_OPT_IT_HIGH_THRESHOLD DTS_ITENR_TS1_ITHEN               /*!< High threshold optional IT on
                                                                             selected temperature sensor */
#define HAL_DTS_OPT_IT_ALL            (HAL_DTS_OPT_IT_END_OF_MEASURE  \
                                       | HAL_DTS_OPT_IT_LOW_THRESHOLD \
                                       | HAL_DTS_OPT_IT_HIGH_THRESHOLD) /*!< All optional IT on selected
                                                                             temperature sensor */
/**
  * @}
  */

/** @defgroup DTS_Interrupts_Definitions DTS Interrupts Definitions
  * @note     Used by unitary interrupt management functions.
  *           Refer to @ref HAL_DTS_EnableIT(), @ref HAL_DTS_DisableIT(), @ref HAL_DTS_IsEnabledIT().
  * @{
  */
#define HAL_DTS_IT_TS1_ITE        DTS_ITENR_TS1_ITEEN     /*!< Interrupt enable flag for end of measure
                                                               on temperature sensor 1, synchronized on PCLK  */
#define HAL_DTS_IT_TS1_ITL        DTS_ITENR_TS1_ITLEN     /*!< Interrupt enable flag for low threshold
                                                               on temperature sensor 1, synchronized on PCLK  */
#define HAL_DTS_IT_TS1_ITH        DTS_ITENR_TS1_ITHEN     /*!< Interrupt enable flag for high threshold
                                                               on temperature sensor 1, synchronized on PCLK  */
#define HAL_DTS_IT_TS1_AITE       DTS_ITENR_TS1_AITEEN    /*!< Asynchronous interrupt enable flag for end of measure
                                                               on temperature sensor 1                        */
#define HAL_DTS_IT_TS1_AITL       DTS_ITENR_TS1_AITLEN    /*!< Asynchronous interrupt enable flag for low threshold
                                                               on temperature sensor 1                        */
#define HAL_DTS_IT_TS1_AITH       DTS_ITENR_TS1_AITHEN    /*!< Asynchronous interrupt enable flag for high threshold
                                                               on temperature sensor 1                        */
#define HAL_DTS_IT_TS1_SYNC_ALL  (DTS_ITENR_TS1_ITEEN   \
                                  | DTS_ITENR_TS1_ITLEN \
                                  | DTS_ITENR_TS1_ITHEN)  /*!< Enable all interrupts
                                                               on temperature sensor 1, synchronized on PCLK */
#define HAL_DTS_IT_TS1_ASYNC_ALL (DTS_ITENR_TS1_AITEEN   \
                                  | DTS_ITENR_TS1_AITLEN \
                                  | DTS_ITENR_TS1_AITHEN) /*!< Enable all asynchronous interrupts
                                                               on temperature sensor 1                       */
/**
  * @}
  */

/** @defgroup DTS_Flag_Definitions DTS Flag Definitions
  * @{
  */
#define HAL_DTS_FLAG_TS1_ITE   DTS_SR_TS1_ITEF     /*!< Interrupt flag for end of measure
                                                        on temperature sensor 1, synchronized on PCLK */
#define HAL_DTS_FLAG_TS1_ITL   DTS_SR_TS1_ITLF     /*!< Interrupt flag for low threshold
                                                        on temperature sensor 1, synchronized on PCLK */
#define HAL_DTS_FLAG_TS1_ITH   DTS_SR_TS1_ITHF     /*!< Interrupt flag for high threshold
                                                        on temperature sensor 1, synchronized on PCLK */
#define HAL_DTS_FLAG_TS1_AITE  DTS_SR_TS1_AITEF    /*!< Asynchronous interrupt flag for end of measure
                                                        on temperature sensor 1                       */
#define HAL_DTS_FLAG_TS1_AITL  DTS_SR_TS1_AITLF    /*!< Asynchronous interrupt flag for low threshold
                                                        on temperature sensor 1                       */
#define HAL_DTS_FLAG_TS1_AITH  DTS_SR_TS1_AITHF    /*!< Asynchronous interrupt flag for high threshold
                                                        on temperature sensor 1                       */
#define HAL_DTS_FLAG_TS1_ALL  (DTS_SR_TS1_ITEF    \
                               | DTS_SR_TS1_ITLF  \
                               | DTS_SR_TS1_ITHF  \
                               | DTS_SR_TS1_AITEF \
                               | DTS_SR_TS1_AITLF \
                               | DTS_SR_TS1_AITHF) /*!< All interrupt flags on temperature sensor 1   */
#define HAL_DTS_FLAG_TS1_RDY   DTS_SR_TS1_RDY      /*!< Temperature sensor 1 ready flag               */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ---------------------------------------------------------------------------------------------------*/
/** @defgroup DTS_Exported_Types HAL DTS Types
  * @{
  */

/**
  * @brief  HAL global state enumeration definition.
  */
typedef enum
{
  HAL_DTS_STATE_RESET      = 0U,           /*!< DTS not yet initialized or disabled */
  HAL_DTS_STATE_CONFIGURED = (1UL << 31U)  /*!< DTS is configured and ready for use */
} hal_dts_state_t;

/**
  * @brief  Sensor state structures definition.
  */
typedef enum
{
  HAL_DTS_SENSOR_STATE_RESET  = (1UL << 31U), /*!< temperature sensor not yet initialized or disabled */
  HAL_DTS_SENSOR_STATE_IDLE   = (1UL << 30U), /*!< temperature sensor initialized and ready for use   */
  HAL_DTS_SENSOR_STATE_ACTIVE = (1UL << 29U)  /*!< temperature sensor started                         */
} hal_dts_sensor_state_t;

/**
  * @brief Trigger source enumeration.
  */
typedef enum
{
  HAL_DTS_TRIGGER_SOFTWARE   = (0UL),                          /*!< DTS Software trigger detection           */
  HAL_DTS_TRIGGER_LPTIM1_CH1 = DTS_CFGR1_TS1_INTRIG_SEL_0,     /*!< DTS external event trigger is LPTIM1_CH1 */
  HAL_DTS_TRIGGER_TIM26_TRGO = (DTS_CFGR1_TS1_INTRIG_SEL_0 \
                                | DTS_CFGR1_TS1_INTRIG_SEL_1), /*!< DTS external event trigger is TIM26_TRGO */
  HAL_DTS_TRIGGER_EXTI13     = DTS_CFGR1_TS1_INTRIG_SEL_2      /*!< DTS external event trigger is EXTI13     */
} hal_dts_trigger_t;

/**
  * @brief Reference Clock Selection enumeration.
  */
typedef enum
{
  HAL_DTS_REFERENCE_CLOCK_PCLK = (0UL),               /*!< High speed reference clock (PCLK) */
  HAL_DTS_REFERENCE_CLOCK_LSE  = DTS_CFGR1_REFCLK_SEL /*!< Low speed reference clock (LSE)   */
} hal_dts_reference_clock_t;

/**
  * @brief Quick measurement option enumeration.
  */
typedef enum
{
  HAL_DTS_QUICK_MEASUREMENT_DISABLE = (0UL),               /*!< Quick measurement OFF: Calibrated measurement    */
  HAL_DTS_QUICK_MEASUREMENT_ENABLE  = DTS_CFGR1_Q_MEAS_OPT /*!< Quick measurement ON: Not calibrated measurement */
} hal_dts_quick_measurement_t;

/**
  * @brief Sampling Time enumeration.
  */
typedef enum
{
  HAL_DTS_SAMPLING_TIME_1_CYCLE   =  DTS_CFGR1_TS1_SMP_TIME_0,    /*!< 1 clock cycle for the sampling time   */
  HAL_DTS_SAMPLING_TIME_2_CYCLES  =  DTS_CFGR1_TS1_SMP_TIME_1,    /*!< 2 clock cycles for the sampling time  */
  HAL_DTS_SAMPLING_TIME_3_CYCLES  = (DTS_CFGR1_TS1_SMP_TIME_0 \
                                     | DTS_CFGR1_TS1_SMP_TIME_1), /*!< 3 clock cycles for the sampling time  */
  HAL_DTS_SAMPLING_TIME_4_CYCLES  = (DTS_CFGR1_TS1_SMP_TIME_2),   /*!< 4 clock cycles for the sampling time  */
  HAL_DTS_SAMPLING_TIME_5_CYCLES  = (DTS_CFGR1_TS1_SMP_TIME_0 \
                                     | DTS_CFGR1_TS1_SMP_TIME_2), /*!< 5 clock cycles for the sampling time  */
  HAL_DTS_SAMPLING_TIME_6_CYCLES  = (DTS_CFGR1_TS1_SMP_TIME_1 \
                                     | DTS_CFGR1_TS1_SMP_TIME_2), /*!< 6 clock cycles for the sampling time  */
  HAL_DTS_SAMPLING_TIME_7_CYCLES  = (DTS_CFGR1_TS1_SMP_TIME_0 \
                                     | DTS_CFGR1_TS1_SMP_TIME_1 \
                                     | DTS_CFGR1_TS1_SMP_TIME_2), /*!< 7 clock cycles for the sampling time  */
  HAL_DTS_SAMPLING_TIME_8_CYCLES  = (DTS_CFGR1_TS1_SMP_TIME_3),   /*!< 8 clock cycles for the sampling time  */
  HAL_DTS_SAMPLING_TIME_9_CYCLES  = (DTS_CFGR1_TS1_SMP_TIME_0 \
                                     | DTS_CFGR1_TS1_SMP_TIME_3), /*!< 9 clock cycles for the sampling time  */
  HAL_DTS_SAMPLING_TIME_10_CYCLES = (DTS_CFGR1_TS1_SMP_TIME_1 \
                                     | DTS_CFGR1_TS1_SMP_TIME_3), /*!< 10 clock cycles for the sampling time */
  HAL_DTS_SAMPLING_TIME_11_CYCLES = (DTS_CFGR1_TS1_SMP_TIME_0 \
                                     | DTS_CFGR1_TS1_SMP_TIME_1 \
                                     | DTS_CFGR1_TS1_SMP_TIME_3), /*!< 11 clock cycles for the sampling time */
  HAL_DTS_SAMPLING_TIME_12_CYCLES = (DTS_CFGR1_TS1_SMP_TIME_2 \
                                     | DTS_CFGR1_TS1_SMP_TIME_3), /*!< 12 clock cycles for the sampling time */
  HAL_DTS_SAMPLING_TIME_13_CYCLES = (DTS_CFGR1_TS1_SMP_TIME_0 \
                                     | DTS_CFGR1_TS1_SMP_TIME_2 \
                                     | DTS_CFGR1_TS1_SMP_TIME_3), /*!< 13 clock cycles for the sampling time */
  HAL_DTS_SAMPLING_TIME_14_CYCLES = (DTS_CFGR1_TS1_SMP_TIME_1 \
                                     | DTS_CFGR1_TS1_SMP_TIME_2 \
                                     | DTS_CFGR1_TS1_SMP_TIME_3), /*!< 14 clock cycles for the sampling time */
  HAL_DTS_SAMPLING_TIME_15_CYCLES = (DTS_CFGR1_TS1_SMP_TIME_0 \
                                     | DTS_CFGR1_TS1_SMP_TIME_1 \
                                     | DTS_CFGR1_TS1_SMP_TIME_2 \
                                     | DTS_CFGR1_TS1_SMP_TIME_3)  /*!< 15 clock cycles for the sampling time */
} hal_dts_sampling_time_t;

/**
  * @brief  DTS Config structure definition.
  */
typedef struct
{
  hal_dts_reference_clock_t   reference_clock;           /*!< Reference clock of the DTS                             */
  hal_dts_quick_measurement_t quick_measurement;         /*!< Quick measurement option for the DTS, it is effective
                                                              only when @ref HAL_DTS_REFERENCE_CLOCK_LSE is selected */
  uint8_t                     high_speed_clock_division; /*!< High speed clock division of the DTS, it is applicable
                                                              only when @ref HAL_DTS_REFERENCE_CLOCK_PCLK is selected,
                                                              it must be a value between 0 and 127                   */
} hal_dts_config_t;

/**
  * @brief  DTS Sensor configuration structure definition.
  */
typedef struct
{
  hal_dts_trigger_t       trigger;       /*!< Specifies the trigger of the DTS sensor       */
  hal_dts_sampling_time_t sampling_time; /*!< Specifies the sampling time of the DTS sensor */
} hal_dts_sensor_config_t;

/**
  * @brief  DTS sensors definition.
  */
typedef enum
{
  HAL_DTS_SENSOR_1 = 0x00U, /*!< DTS sensor 1 */
} hal_dts_sensor_t;

/**
  * @brief HAL DTS instance.
  */
typedef enum
{
  HAL_DTS = DTS_BASE, /*!< DTS Peripheral instance */
} hal_dts_t;

typedef struct hal_dts_handle_s hal_dts_handle_t; /*!< DTS handle structure type */

#if defined(USE_HAL_DTS_REGISTER_CALLBACKS) && (USE_HAL_DTS_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL DTS Callback pointer definition.
  */
typedef void (*hal_dts_cb_t)(hal_dts_handle_t *hdts,
                             hal_dts_sensor_t sensor); /*!< Pointer to a DTS common callback function */

#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */

/**
  * @brief  DTS handle Structure definition.
  */
struct hal_dts_handle_s
{
  hal_dts_t                       instance;                              /*!< HAL DTS instance             */
  volatile hal_dts_state_t        global_state;                          /*!< DTS global state             */
  volatile hal_dts_sensor_state_t sensor_states[DTS_SENSORS_NUMBER];     /*!< DTS temperature sensor state */

#if defined(USE_HAL_DTS_USER_DATA) && (USE_HAL_DTS_USER_DATA == 1)
  const void                      *p_user_data;                          /*!< User Data Pointer            */
#endif /* USE_HAL_DTS_USER_DATA */

#if defined(USE_HAL_DTS_REGISTER_CALLBACKS) && (USE_HAL_DTS_REGISTER_CALLBACKS == 1U)
  hal_dts_cb_t                    p_cplt_cb;                             /*!< Complete measure callback    */
  hal_dts_cb_t                    p_low_threshold_cb;                    /*!< Low threshold callback       */
  hal_dts_cb_t                    p_high_threshold_cb;                   /*!< High threshold callback      */
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */
};

/**
  * @}
  */

/* Exported functions -----------------------------------------------------------------------------------------------*/
/** @defgroup DTS_Exported_Functions HAL DTS Functions
  * @{
  */

/** @defgroup DTS_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_DTS_Init(hal_dts_handle_t *hdts, hal_dts_t instance);
void HAL_DTS_DeInit(hal_dts_handle_t *hdts);
/**
  * @}
  */

/** @defgroup DTS_Exported_Functions_Group2 Configuration functions
  * @{
  */
/* Global configuration */
hal_status_t HAL_DTS_SetConfig(hal_dts_handle_t *hdts, const hal_dts_config_t *p_config);
void HAL_DTS_GetConfig(const hal_dts_handle_t *hdts, hal_dts_config_t *p_config);

/* Sensor configuration */
hal_status_t HAL_DTS_SetConfigSensor(hal_dts_handle_t *hdts,
                                     hal_dts_sensor_t sensor,
                                     const hal_dts_sensor_config_t *p_sensor_config);
void HAL_DTS_GetConfigSensor(const hal_dts_handle_t *hdts,
                             hal_dts_sensor_t sensor,
                             hal_dts_sensor_config_t *p_sensor_config);

/* Trigger */
hal_status_t HAL_DTS_SetSensorTrigger(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor, hal_dts_trigger_t trigger);
hal_dts_trigger_t HAL_DTS_GetSensorTrigger(const hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);

/* Sampling Time */
hal_status_t HAL_DTS_SetSensorSamplingTime(hal_dts_handle_t *hdts,
                                           hal_dts_sensor_t sensor,
                                           hal_dts_sampling_time_t sampling_time);
hal_dts_sampling_time_t HAL_DTS_GetSensorSamplingTime(const hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);

/* High and Low Thresholds */
hal_status_t HAL_DTS_SetSensorThresholds(hal_dts_handle_t *hdts,
                                         hal_dts_sensor_t sensor,
                                         int32_t high_threshold_degc,
                                         int32_t low_threshold_degc);
hal_status_t HAL_DTS_GetSensorThresholds(const hal_dts_handle_t *hdts,
                                         hal_dts_sensor_t sensor,
                                         int32_t *p_high_threshold_degc,
                                         int32_t *p_low_threshold_degc);

/* Clock frequency */
uint32_t HAL_DTS_GetClockFreq(const hal_dts_handle_t *hdts);
/**
  * @}
  */


/** @defgroup DTS_Exported_Functions_Group3 Process functions
  * @{
  */
hal_status_t HAL_DTS_StartSensor(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);
hal_status_t HAL_DTS_StopSensor(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);
hal_status_t HAL_DTS_StartSensor_IT(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);
hal_status_t HAL_DTS_StartSensor_IT_Opt(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor, uint32_t interrupts);
hal_status_t HAL_DTS_StopSensor_IT(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);
hal_status_t HAL_DTS_PollForSensorTemperature(const hal_dts_handle_t *hdts,
                                              hal_dts_sensor_t sensor,
                                              uint32_t timeout_ms);
hal_status_t HAL_DTS_GetSensorTemperature(const hal_dts_handle_t *hdts,
                                          hal_dts_sensor_t sensor,
                                          int32_t *p_temperature_degc);
/**
  * @}
  */

/** @defgroup DTS_Exported_Functions_Group4 IRQHandler and Callbacks functions
  * @{
  */
void HAL_DTS_IRQHandler(hal_dts_handle_t *hdts);
void HAL_DTS_CpltCallback(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);
void HAL_DTS_LowThresholdCallback(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);
void HAL_DTS_HighThresholdCallback(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);
#if defined(USE_HAL_DTS_REGISTER_CALLBACKS) && (USE_HAL_DTS_REGISTER_CALLBACKS == 1)
hal_status_t HAL_DTS_RegisterCpltCallback(hal_dts_handle_t *hdts, hal_dts_cb_t p_callback);
hal_status_t HAL_DTS_RegisterLowThresholdCallback(hal_dts_handle_t *hdts, hal_dts_cb_t p_callback);
hal_status_t HAL_DTS_RegisterHighThresholdCallback(hal_dts_handle_t *hdts, hal_dts_cb_t p_callback);
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup DTS_Exported_Functions_Group5 Peripheral State function
  * @{
  */
hal_dts_state_t HAL_DTS_GetState(const hal_dts_handle_t *hdts);
hal_dts_sensor_state_t HAL_DTS_GetSensorState(const hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);
/**
  * @}
  */

/** @defgroup DTS_Exported_Functions_Group6 User data and retrieve HAL instance functions
  * @{
  */
#if defined(USE_HAL_DTS_USER_DATA) && (USE_HAL_DTS_USER_DATA == 1)
void HAL_DTS_SetUserData(hal_dts_handle_t *hdts, const void *p_user_data);
const void *HAL_DTS_GetUserData(const hal_dts_handle_t *hdts);
#endif /* USE_HAL_DTS_USER_DATA */

hal_dts_t HAL_DTS_GetInstance(const hal_dts_handle_t *hdts);
/**
  * @}
  */

/** @defgroup DTS_Exported_Functions_Group7 Interrupt and Flag management
  * @{
 - HAL_DTS_IsActiveFlag() : Check whether or not the specified DTS flag is set.
 - HAL_DTS_ClearFlag()    : Clear the specified DTS flags.
 - HAL_DTS_EnableIT()     : Enable the specified DTS interrupts.
 - HAL_DTS_DisableIT()    : Disable the specified DTS interrupts.
 - HAL_DTS_IsEnabledIT()  : Check whether or not the specified DTS interrupt is set.
  */

/**
  * @brief  Check whether or not the specified DTS flag is set.
  * @param  hdts  Pointer to a hal_dts_handle_t structure
  * @param  flag   Specify the DTS flag to check
  *                This parameter can be only one of the following values:
  *                @arg @ref HAL_DTS_FLAG_TS1_ITE  : Synchronous interrupt flag for end of measure for DTS
  *                @arg @ref HAL_DTS_FLAG_TS1_ITL  : Synchronous interrupt flag for low threshold for DTS
  *                @arg @ref HAL_DTS_FLAG_TS1_ITH  : Synchronous interrupt flag for high threshold for DTS
  *                @arg @ref HAL_DTS_FLAG_TS1_AITE : Asynchronous interrupt flag for end of measure for DTS
  *                @arg @ref HAL_DTS_FLAG_TS1_AITL : Asynchronous interrupt flag for low threshold for DTS
  *                @arg @ref HAL_DTS_FLAG_TS1_AITH : Asynchronous interrupt flag for high threshold for DTS
  *                @arg @ref HAL_DTS_FLAG_TS1_RDY  : Ready flag for DTS
  * @retval The state of DTS flag (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_DTS_IsActiveFlag(const hal_dts_handle_t *hdts, uint32_t flag)
{
  return ((uint32_t)(STM32_READ_BIT(((DTS_TypeDef *)(uint32_t)(hdts->instance))->SR, flag) == flag));
}

/**
  * @brief Clear the specified DTS flags.
  * @param hdts Pointer to a hal_dts_handle_t structure
  * @param flag Specify the DTS flag to clear
  *             This parameter can be any combination of the following values:
  *             @arg @ref HAL_DTS_FLAG_TS1_ITE  : Synchronous interrupt flag for end of measure for DTS
  *             @arg @ref HAL_DTS_FLAG_TS1_ITL  : Synchronous interrupt flag for low threshold for DTS
  *             @arg @ref HAL_DTS_FLAG_TS1_ITH  : Synchronous interrupt flag for high threshold for DTS
  *             @arg @ref HAL_DTS_FLAG_TS1_AITE : Asynchronous interrupt flag for end of measure for DTS
  *             @arg @ref HAL_DTS_FLAG_TS1_AITL : Asynchronous interrupt flag for low threshold for DTS
  *             @arg @ref HAL_DTS_FLAG_TS1_AITH : Asynchronous interrupt flag for high threshold for DTS
  *             @arg @ref HAL_DTS_FLAG_TS1_ALL  : All flags within raw interrupt status register (DTS_SR)
  */
__STATIC_INLINE void HAL_DTS_ClearFlag(hal_dts_handle_t *hdts, uint32_t flag)
{
  STM32_SET_BIT(((DTS_TypeDef *)(uint32_t)(hdts->instance))->ICIFR, flag);
}

/**
  * @brief Enable the specified DTS interrupts.
  * @param hdts      Pointer to a hal_dts_handle_t structure
  * @param interrupt Specify the DTS interrupt to enable
  *                  This parameter can be any combination of the following values:
  *                  @arg @ref HAL_DTS_IT_TS1_ITE       : Synchronous interrupt flag for end of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_ITL       : Synchronous interrupt flag for low of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_ITH       : Synchronous interrupt flag for high of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_AITE      : Asynchronous interrupt flag for end of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_AITL      : Asynchronous interrupt flag for low of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_AITH      : Asynchronous interrupt flag for high of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_SYNC_ALL  : All synchronous interrupt flags for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_ASYNC_ALL : All asynchronous interrupt flags for DTS
  */
__STATIC_INLINE void HAL_DTS_EnableIT(hal_dts_handle_t *hdts, uint32_t interrupt)
{
  STM32_SET_BIT(((DTS_TypeDef *)(uint32_t)(hdts->instance))->ITENR, interrupt);
}

/**
  * @brief Disable the specified DTS interrupts.
  * @param hdts      Pointer to a hal_dts_handle_t structure
  * @param interrupt Specify the DTS interrupt to disable
  *                  This parameter can be any combination of the following values:
  *                  @arg @ref HAL_DTS_IT_TS1_ITE       : Synchronous interrupt flag for end of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_ITL       : Synchronous interrupt flag for low of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_ITH       : Synchronous interrupt flag for high of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_AITE      : Asynchronous interrupt flag for end of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_AITL      : Asynchronous interrupt flag for low of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_AITH      : Asynchronous interrupt flag for high of measure for DTS
  *                  @arg @ref HAL_DTS_IT_TS1_SYNC_ALL  : All synchronous interrupt flags
  *                  @arg @ref HAL_DTS_IT_TS1_ASYNC_ALL : All asynchronous interrupt flags
  */
__STATIC_INLINE void HAL_DTS_DisableIT(hal_dts_handle_t *hdts, uint32_t interrupt)
{
  STM32_CLEAR_BIT(((DTS_TypeDef *)(uint32_t)(hdts->instance))->ITENR, interrupt);
}

/**
  * @brief  Check whether or not the specified DTS interrupt is enabled.
  * @param  hdts      Pointer to a hal_dts_handle_t structure
  * @param  interrupt Specify the DTS interrupt to check
  *                   This parameter can be only one of the following values:
  *                   @arg @ref HAL_DTS_IT_TS1_ITE  : Synchronous interrupt flag for end of measure for DTS
  *                   @arg @ref HAL_DTS_IT_TS1_ITL  : Synchronous interrupt flag for low of measure for DTS
  *                   @arg @ref HAL_DTS_IT_TS1_ITH  : Synchronous interrupt flag for high of measure for DTS
  *                   @arg @ref HAL_DTS_IT_TS1_AITE : Asynchronous interrupt flag for end of measure for DTS
  *                   @arg @ref HAL_DTS_IT_TS1_AITL : Asynchronous interrupt flag for low of measure for DTS
  *                   @arg @ref HAL_DTS_IT_TS1_AITH : Asynchronous interrupt flag for high of measure for DTS
  * @retval The state of DTS flag (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_DTS_IsEnabledIT(const hal_dts_handle_t *hdts, uint32_t interrupt)
{
  return ((uint32_t)(STM32_READ_BIT(((DTS_TypeDef *)(uint32_t)(hdts->instance))->ITENR, interrupt) == interrupt));
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
#endif /* DTS */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5xx_HAL_DTS_H */
