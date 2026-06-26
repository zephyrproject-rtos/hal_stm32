/**
  ******************************************************************************
  * @file    stm32g5xx_hal_dts.c
  * @brief   DTS HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the DTS peripheral:
  *           + Initialization and de-initialization functions
  *           + Start/Stop operation functions in polling mode.
  *           + Start/Stop operation functions in interrupt mode.
  *           + Peripheral Control functions
  *           + Peripheral State functions.
  *
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

/* Includes ---------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */
#if defined(DTS)
#if defined(USE_HAL_DTS_MODULE) && (USE_HAL_DTS_MODULE == 1)
/** @addtogroup DTS
  * @{
  */
/** @defgroup DTS_Introduction DTS Introduction
  * @{

  - The DTS (Digital Temperature Sensor) hardware abstraction layer provides a set of APIs to interface with the STM32
    on-chip temperature sensor peripheral.
  - It simplifies the initialization, configuration and process of peripheral features.
  - This abstraction layer ensures portability and ease of use across different STM32 series.

  The HAL DTS driver includes the following features:
   - Temperature watchdog with configurable thresholds
   - Interrupt generation on configurable temperature events

  */
/**
  * @}
  */

/** @defgroup DTS_How_To_Use DTS How To Use
  * @{
# How to use the HAL DTS driver

## Caution:
   This is just a description of DTS functionality.
   In order to use the DTS peripheral, it must be calibrated, it means:
    - Calibration value of the ramp coefficient for the chosen temperature sensor (RAMP_COEFF) must not be 0,
      it is measured during tests in factory and stored in DTS_RAMPVALR register. This value is expressed in hertz per
      degree Celsius.
    - Calibration value of the T0 temperature for the chosen temperature sensor must be 30 or 130 degree Celsius
      (0 or 1), it is the temperature used during tests in factory and stored in DTS_T0VALR1 register.

## The HAL DTS driver can be used as follows:

1. Declare a @ref hal_dts_handle_t handle structure and initialize the DTSx driver with a DTSx HW instance by calling
   the HAL_DTS_Init().
   The DTSx clock is enabled inside the HAL_DTS_Init() if USE_HAL_DTS_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.

2. Configure the low level hardware (CLOCK, NVIC, HW trigger...):
  - Enable the DTSx clock if USE_HAL_DTS_CLK_ENABLE_MODEL is not defined or defined to HAL_CLK_ENABLE_NO.
  - NVIC configuration if you need to use interrupt process.
    - Configure the DTSx interrupt priority.
    - Enable the NVIC DTSx IRQ handle.
  - Proceed with the EXTI or LPTIM configuration if you need to use Hardware trigger.
  - LSE clock has to be activated when it is selected as reference clock .

3. Configure the reference clock by calling HAL_DTS_SetConfig().
   this configuration is optional.

4. Configure trigger and sampling time by calling HAL_DTS_SetConfigSensor().
   these configurations are optional.

5. Configure thresholds by calling HAL_DTS_SetSensorThresholds(), trigger by calling HAL_DTS_SetSensorTrigger()
   and sampling time by calling HAL_DTS_SetSensorSamplingTime().
   All these unitary configurations are optional.
   Caution: When using the LSE clock or operating at low PCLK frequencies, it is important to increase the sampling
            value during threshold configuration. This helps reduce quantization errors and enhances the reliability of
            temperature readings.

6. Temperature measurement:
  - Polling mode usage
    - Start measuring temperature by calling HAL_DTS_StartSensor().
      - Caution: Due to DTS end of measure interrupt always enabled in this API,
        Disabling the NVIC DTSx IRQ before calling this function is mandatory.
    - Check if temperature measurement is ready or not by calling HAL_DTS_PollForSensorTemperature().
    - Retrieve the measured temperature by calling HAL_DTS_GetSensorTemperature().
    - Stop measuring temperature by calling HAL_DTS_StopSensor().

  - Interrupt mode usage
    - Start measuring temperature by calling HAL_DTS_StartSensor_IT().
      - Or by HAL_DTS_StartSensor_IT_Opt() to enable specific optional interrupts.
    - Wait for the end of temperaure measurement and/or high threshold or low threshold detection
      (HAL_DTS_CpltCallback() and/or HAL_DTS_HighThresholdCallback() or HAL_DTS_LowThresholdCallback() occurrence).
    - Retrieve the measured temperature by calling HAL_DTS_GetSensorTemperature().
    - Stop measuring temperature by calling HAL_DTS_StopSensor_IT().

### Callbacks definition in interrupt mode:

  When the compilation define USE_HAL_DTS_REGISTER_CALLBACKS is set to 1, the user can configure dynamically the
  driver callbacks, via its own method:

Callback name               | Default value                      | Callback registration function
----------------------------| -----------------------------------| --------------------------------------------
CpltCallback                | HAL_DTS_CpltCallback()             | HAL_DTS_RegisterCpltCallback()
HighThresholdCallback       | HAL_DTS_HighThresholdCallback()    | HAL_DTS_RegisterHighThresholdCallback()
LowThresholdCallback        | HAL_DTS_LowThresholdCallback()     | HAL_DTS_RegisterLowThresholdCallback()

  If one needs to unregister a callback, register the default callback via the registration function.

  By default, after the HAL_DTS_Init() and when the state is @ref HAL_DTS_STATE_CONFIGURED, all callbacks are set
  to the corresponding default weak functions.

  Callbacks can be registered in handle global_state @ref HAL_DTS_STATE_CONFIGURED.

  When the compilation define USE_HAL_DTS_REGISTER_CALLBACKS is set to 0 or not defined, the callback registration
  feature is not available and weak callbacks are used, represented by the default value in the table above.
  */
/**
  * @}
  */

/** @defgroup DTS_Configuration_Table DTS Configuration Table
  * @{

# Configuration inside the HAL DTS driver

Config defines                 | Where            | Default value     | Note
-------------------------------| -----------------| ------------------| -------------------------------------------
PRODUCT                        | PreProcessor env |         NA        | The selected device
USE_HAL_DTS_MODULE             | hal_conf.h       |         1         | Enable the HAL DTS module
USE_HAL_DTS_REGISTER_CALLBACKS | hal_conf.h       |         0         | Allow user to define his own callback
USE_HAL_DTS_CLK_ENABLE_MODEL   | hal_conf.h       | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_DTS_USER_DATA          | hal_conf.h       |         0         | Add an user data inside HAL DTS handle
USE_HAL_CHECK_PARAM            | hal_conf.h       |         0         | Enable checking of vital parameters at runtime
USE_HAL_CHECK_PROCESS_STATE    | hal_conf.h       |         0         | Enable atomic access to process state check
USE_ASSERT_DBG_PARAM           | PreProcessor env |        NONE       | Enable check parameters for HAL
USE_ASSERT_DBG_STATE           | PreProcessor env |        NONE       | Enable check state for HAL
  */
/**
  * @}
  */

/* Private types ----------------------------------------------------------------------------------------------------*/
/* Private constants ------------------------------------------------------------------------------------------------*/
/** @defgroup DTS_Private_Constants DTS Private Constants
  * @{
  */
#define DTS_DELAY_STARTUP (1UL)   /*!< DTS startup time, delay required to get ready in ms */
#define DTS_TIMEOUT_MS    (5UL)   /*!< DTS measure ready flag time out value, Maximal measurement time is when
                                       LSE is selected as ref_clock and maximal sampling time is used, taking
                                       calibration into account this is equivalent to ~620 us.
                                       Use 5 ms as arbitrary timeout                       */

#define DTS_FACTORY_TEMPERATURE_CALIBRATION1 (0UL)                           /*!< DTS factory temperature value 0 */
#define DTS_FACTORY_TEMPERATURE_CALIBRATION2 (1UL << DTS_T0VALR1_TS1_T0_Pos) /*!< DTS factory temperature value 1 */

#define DTS_FACTORY_TEMPERATURE1 ((int32_t)30)  /*!< DTS factory temperature in degree Celsius */
#define DTS_FACTORY_TEMPERATURE2 ((int32_t)130) /*!< DTS factory temperature in degree Celsius */

#define DTS_MIN_TEMPERATURE (-40)  /*!< Minimum temperature possible degree Celsius */
#define DTS_MAX_TEMPERATURE (140)  /*!< Maximum temperature possible degree Celsius */

/**
  * @}
  */

/* Private macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup DTS_Private_Macros DTS Private Macros
  * @{
  */

/*! Get DTS instance from the selected HAL DTS handle */
#define DTS_GET_INSTANCE(hdts) ((DTS_TypeDef *)((uint32_t)(hdts)->instance))

/**
  * @brief DTS Reference clock.
  */
#define IS_DTS_REFERENCE_CLOCK(refclock) (((refclock) == HAL_DTS_REFERENCE_CLOCK_PCLK) \
                                          || ((refclock) == HAL_DTS_REFERENCE_CLOCK_LSE))

/**
  * @brief DTS Quick measurement.
  */
#define IS_DTS_QUICK_MEASUREMENT(quickmeasurement) (((quickmeasurement) == HAL_DTS_QUICK_MEASUREMENT_DISABLE) \
                                                    || ((quickmeasurement) == HAL_DTS_QUICK_MEASUREMENT_ENABLE))

/**
  * @brief DTS clock division.
  */
#define IS_DTS_CLOCK_DIVISION(divider) ((divider) <= 127U)

/**
  * @brief DTS Sensors.
  */
#define IS_DTS_SENSOR(sensor) (((sensor) == HAL_DTS_SENSOR_1))

/**
  * @brief DTS Sensor Trigger.
  */
#define IS_DTS_SENSOR_TRIGGER(trigger) (((trigger) == HAL_DTS_TRIGGER_SOFTWARE)      \
                                        || ((trigger) == HAL_DTS_TRIGGER_LPTIM1_CH1) \
                                        || ((trigger) == HAL_DTS_TRIGGER_TIM26_TRGO) \
                                        || ((trigger) == HAL_DTS_TRIGGER_EXTI13))

/**
  * @brief DTS Sensor Sampling Time.
  */
#define IS_DTS_SENSOR_SAMPLING_TIME(samplingtime) (((samplingtime) == HAL_DTS_SAMPLING_TIME_1_CYCLE)      \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_2_CYCLES)  \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_3_CYCLES)  \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_4_CYCLES)  \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_5_CYCLES)  \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_6_CYCLES)  \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_7_CYCLES)  \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_8_CYCLES)  \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_9_CYCLES)  \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_10_CYCLES) \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_11_CYCLES) \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_12_CYCLES) \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_13_CYCLES) \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_14_CYCLES) \
                                                   || ((samplingtime) == HAL_DTS_SAMPLING_TIME_15_CYCLES))

/**
  * @brief DTS Sensor Threshold.
  */
#define IS_DTS_SENSOR_THRESHOLD(threshold) (((threshold) >= (DTS_MIN_TEMPERATURE)) \
                                            && ((threshold) <= (DTS_MAX_TEMPERATURE)))

/**
  * @brief DTS interrupts.
  */
#define IS_DTS_INTERRUPTS(interrupts) (((interrupts) & ~(HAL_DTS_OPT_IT_ALL)) == 0x0UL)

/**
  * @}
  */

/* Private functions ------------------------------------------------------------------------------------------------*/
/** @defgroup DTS_Private_Functions DTS Private Functions
  * @{
  */
/* Private function to handle ready flag */
static hal_status_t DTS_WaitOnStatusUntilTimeout(const hal_dts_handle_t *hdts, uint32_t flag, uint32_t timeout_ms);

/* Private function to start temperature measurement */
static hal_status_t DTS_StartSensor(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor, uint32_t interrupts);

/* Private function to stop temperature measurement */
static void DTS_StopSensor(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor);

/* Private function to retrieve configured sampling time and calibration values */
static hal_status_t DTS_GetSamplingTimeAndCalibrationValues(const hal_dts_handle_t *hdts, int32_t *ramp_coefficient, \
                                                            int32_t  *calibration_temperature, \
                                                            int32_t *calibration_frequency, uint8_t  *sampling_time);

/* Private function to Convert DR and ITR1 Registers Data to Temperature in degree celsius */
static hal_status_t DTS_DataToTemperature(const hal_dts_handle_t *hdts, uint32_t data_to_calculate, \
                                          int32_t *p_temperature_degc);

/**
  * @}
  */

/* Private variables ------------------------------------------------------------------------------------------------*/
/* Exported functions -----------------------------------------------------------------------------------------------*/
/** @addtogroup DTS_Exported_Functions
  * @{
  */

/** @addtogroup DTS_Exported_Functions_Group1
  * @{
This section provides a set of functions allowing to initialize and deinitialize the DTS peripheral:
  - Call the function HAL_DTS_Init() to initialize the selected DTS handle.
  - Call the function HAL_DTS_DeInit() to deinitialize the DTS.
  */

/**
  * @brief  Initialize the HAL DTS handle and associate it to an instance of the DTS peripheral.
  * @param  hdts              Pointer to a @ref hal_dts_handle_t.
  * @param  instance          HAL DTS instance.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to HAL DTS handle is NULL.
  */
hal_status_t HAL_DTS_Init(hal_dts_handle_t *hdts, hal_dts_t instance)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_ALL_INSTANCE((DTS_TypeDef *)(uint32_t)instance));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdts == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdts->instance = instance;

#if defined(USE_HAL_DTS_CLK_ENABLE_MODEL) && (USE_HAL_DTS_CLK_ENABLE_MODEL >= HAL_CLK_ENABLE_PERIPH_ONLY)
  HAL_RCC_DTS_EnableClock();
#endif /* USE_HAL_DTS_CLK_ENABLE_MODEL */

#if defined (USE_HAL_DTS_USER_DATA) && (USE_HAL_DTS_USER_DATA == 1)
  hdts->p_user_data = (void *) NULL;
#endif /* USE_HAL_DTS_USER_DATA */

#if defined(USE_HAL_DTS_REGISTER_CALLBACKS) && (USE_HAL_DTS_REGISTER_CALLBACKS == 1)
  /* Initialize HAL DTS callbacks */
  hdts->p_cplt_cb           = HAL_DTS_CpltCallback;
  hdts->p_low_threshold_cb  = HAL_DTS_LowThresholdCallback;
  hdts->p_high_threshold_cb = HAL_DTS_HighThresholdCallback;
#endif  /* USE_HAL_DTS_REGISTER_CALLBACKS */

  hdts->sensor_states[HAL_DTS_SENSOR_1] = HAL_DTS_SENSOR_STATE_IDLE;

  hdts->global_state = HAL_DTS_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief De-initialize the DTS.
  * @param hdts Pointer to a @ref hal_dts_handle_t.
  */
void HAL_DTS_DeInit(hal_dts_handle_t *hdts)
{

  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_ALL_INSTANCE(DTS_GET_INSTANCE(hdts)));

  /* Disable sensor */
  STM32_CLEAR_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_EN);

  /* Stop continuous measures */
  STM32_CLEAR_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_START);

  /* Disable sensor interrupts */
  STM32_CLEAR_REG(DTS_GET_INSTANCE(hdts)->ITENR);

  /* Clear sensor pending flags */
  STM32_SET_BIT(DTS_GET_INSTANCE(hdts)->ICIFR, (DTS_ICIFR_TS1_CITEF | DTS_ICIFR_TS1_CITLF | DTS_ICIFR_TS1_CITHF \
                                                | DTS_ICIFR_TS1_CAITEF | DTS_ICIFR_TS1_CAITLF | DTS_ICIFR_TS1_CAITHF));

  hdts->sensor_states[HAL_DTS_SENSOR_1] = HAL_DTS_SENSOR_STATE_RESET;

  hdts->global_state = HAL_DTS_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup DTS_Exported_Functions_Group2
  * @{
This section provides a set of functions allowing to configure DTS:
  - Call the function HAL_DTS_SetConfig() to configure the DTS reference clock.
  - Call the function HAL_DTS_GetConfig() to retrieve the current DTS reference clock.
  - Call the function HAL_DTS_SetConfigSensor() to configure the DTS sensor trigger and sampling time.
  - Call the function HAL_DTS_GetConfigSensor() to retrieve the current DTS sensor trigger and sampling time.
  - Call the function HAL_DTS_SetSensorTrigger() to configure the DTS sensor trigger.
  - Call the function HAL_DTS_GetSensorTrigger() to retrieve the current DTS sensor trigger.
  - Call the function HAL_DTS_SetSensorSamplingTime() to configure the DTS sensor sampling time.
  - Call the function HAL_DTS_GetSensorSamplingTime() to retrieve the current DTS sensor sampling time.
  - Call the function HAL_DTS_SetSensorThresholds() to configure the DTS sensor thresholds.
  - Call the function HAL_DTS_GetSensorThresholds() to retrieve the current DTS sensor thresholds.
  - Call the function HAL_DTS_GetClockFreq() to get the current DTS kernel (LSE) clock frequency.
  */

/* Configuration functions */
/**
  * @brief  Configure the DTS reference clock.
  * @param  hdts              Pointer to a @ref hal_dts_handle_t.
  * @param  p_config          Pointer to a @ref hal_dts_config_t.
  * @note   When LSE is selected as reference clock, the high speed clock division config has no effect.
  *         When PCLK is selected as reference clock, the Quick measurement option config has no effect.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to hal_dts_config_t is NULL.
  * @retval HAL_ERROR         LSE clock is unavailable.
  */
hal_status_t HAL_DTS_SetConfig(hal_dts_handle_t *hdts, const hal_dts_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_DTS_REFERENCE_CLOCK((p_config->reference_clock)));

  ASSERT_DBG_STATE(hdts->sensor_states[HAL_DTS_SENSOR_1], HAL_DTS_SENSOR_STATE_IDLE);

  if (p_config->reference_clock == HAL_DTS_REFERENCE_CLOCK_LSE)
  {
#if !defined(LSE_VALUE)
    return HAL_ERROR;
#else
    ASSERT_DBG_PARAM(IS_DTS_QUICK_MEASUREMENT((p_config->quick_measurement)));

    STM32_MODIFY_REG(DTS_GET_INSTANCE(hdts)->CFGR1,
                     (DTS_CFGR1_REFCLK_SEL | DTS_CFGR1_Q_MEAS_OPT | DTS_CFGR1_HSREF_CLK_DIV),
                     ((uint32_t)p_config->reference_clock | (uint32_t)p_config->quick_measurement));
#endif /* LSE_VALUE */
  }
  else
  {
    ASSERT_DBG_PARAM(IS_DTS_CLOCK_DIVISION((p_config->high_speed_clock_division)));

    STM32_MODIFY_REG(DTS_GET_INSTANCE(hdts)->CFGR1,
                     (DTS_CFGR1_REFCLK_SEL | DTS_CFGR1_Q_MEAS_OPT | DTS_CFGR1_HSREF_CLK_DIV),
                     ((uint32_t)p_config->reference_clock
                      | (DTS_CFGR1_HSREF_CLK_DIV & ((uint32_t)p_config->high_speed_clock_division
                                                    << DTS_CFGR1_HSREF_CLK_DIV_Pos))));
  }

  return HAL_OK;
}

/**
  * @brief Get the current DTS reference clock.
  * @param hdts     Pointer to a @ref hal_dts_handle_t.
  * @param p_config Pointer to a @ref hal_dts_config_t.
  */
void HAL_DTS_GetConfig(const hal_dts_handle_t *hdts, hal_dts_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hdts->global_state, HAL_DTS_STATE_CONFIGURED);

  p_config->reference_clock = (hal_dts_reference_clock_t)(uint32_t)STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1,
                                                                                  DTS_CFGR1_REFCLK_SEL);
  p_config->quick_measurement = (hal_dts_quick_measurement_t)(uint32_t)STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1,
                                DTS_CFGR1_Q_MEAS_OPT);
  p_config->high_speed_clock_division = (uint8_t)(STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_HSREF_CLK_DIV)
                                                  >> DTS_CFGR1_HSREF_CLK_DIV_Pos);
}

/**
  * @brief  Configure the DTS sensor trigger and sampling time.
  * @param  hdts              Pointer to a @ref hal_dts_handle_t.
  * @param  sensor            DTS sensor.
  * @param  p_sensor_config   Pointer to a hal_dts_sensor_config_t.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to hal_dts_sensor_config_t is NULL.
  */
hal_status_t HAL_DTS_SetConfigSensor(hal_dts_handle_t *hdts,
                                     hal_dts_sensor_t sensor,
                                     const hal_dts_sensor_config_t *p_sensor_config)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(p_sensor_config != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_sensor_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_DTS_SENSOR_SAMPLING_TIME(p_sensor_config->sampling_time));
  ASSERT_DBG_PARAM(IS_DTS_SENSOR_TRIGGER(p_sensor_config->trigger));

  ASSERT_DBG_STATE(hdts->sensor_states[sensor], HAL_DTS_SENSOR_STATE_IDLE);

#if !defined(USE_ASSERT_DBG_PARAM) && !defined(USE_ASSERT_DBG_STATE)
  STM32_UNUSED(sensor);
#endif /* USE_ASSERT_DBG_PARAM */

  STM32_MODIFY_REG(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_INTRIG_SEL | DTS_CFGR1_TS1_SMP_TIME, \
                   (uint32_t)p_sensor_config->trigger | (uint32_t)p_sensor_config->sampling_time);

  return HAL_OK;
}

/**
  * @brief Retrieve the current DTS sensor trigger and sampling time.
  * @param  hdts            Pointer to a @ref hal_dts_handle_t.
  * @param  sensor          DTS sensor.
  * @param  p_sensor_config Pointer to a hal_dts_sensor_config_t.
  */
void HAL_DTS_GetConfigSensor(const hal_dts_handle_t *hdts,
                             hal_dts_sensor_t sensor,
                             hal_dts_sensor_config_t *p_sensor_config)
{
  uint32_t temp_cfgr;

  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(p_sensor_config != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));

  ASSERT_DBG_STATE(hdts->global_state, HAL_DTS_STATE_CONFIGURED);

#if !defined(USE_ASSERT_DBG_PARAM)
  STM32_UNUSED(sensor);
#endif /* USE_ASSERT_DBG_PARAM */

  temp_cfgr = STM32_READ_REG(DTS_GET_INSTANCE(hdts)->CFGR1);

  p_sensor_config->trigger       = (hal_dts_trigger_t)(uint32_t)STM32_READ_BIT(temp_cfgr, DTS_CFGR1_TS1_INTRIG_SEL);
  p_sensor_config->sampling_time = (hal_dts_sampling_time_t)(uint32_t)STM32_READ_BIT(temp_cfgr, DTS_CFGR1_TS1_SMP_TIME);
}

/**
  * @brief  Configure the DTS sensor trigger.
  * @param  hdts     Pointer to a @ref hal_dts_handle_t.
  * @param  sensor   DTS sensor.
  * @param  trigger  DTS sensor trigger.
  * @retval HAL_OK   Operation completed successfully.
  */
hal_status_t HAL_DTS_SetSensorTrigger(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor, hal_dts_trigger_t trigger)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));
  ASSERT_DBG_PARAM(IS_DTS_SENSOR_TRIGGER(trigger));

  ASSERT_DBG_STATE(hdts->sensor_states[sensor], HAL_DTS_SENSOR_STATE_IDLE);

#if !defined(USE_ASSERT_DBG_PARAM) && !defined(USE_ASSERT_DBG_STATE)
  STM32_UNUSED(sensor);
#endif /* USE_ASSERT_DBG_PARAM */

  STM32_MODIFY_REG(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_INTRIG_SEL, (uint32_t)trigger);

  return HAL_OK;
}

/**
  * @brief Retrieve the current DTS sensor trigger.
  * @param  hdts              Pointer to a @ref hal_dts_handle_t.
  * @param  sensor            DTS sensor.
  * @retval hal_dts_trigger_t DTS sensor trigger.
  */
hal_dts_trigger_t HAL_DTS_GetSensorTrigger(const hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));

  ASSERT_DBG_STATE(hdts->global_state, HAL_DTS_STATE_CONFIGURED);

#if !defined(USE_ASSERT_DBG_PARAM)
  STM32_UNUSED(sensor);
#endif /* USE_ASSERT_DBG_PARAM */

  return (hal_dts_trigger_t)(uint32_t)STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_INTRIG_SEL);
}

/**
  * @brief  Configure the DTS sensor sampling time.
  * @param  hdts          Pointer to a @ref hal_dts_handle_t.
  * @param  sensor        DTS sensor.
  * @param  sampling_time DTS sensor sampling time.
  * @retval HAL_OK        Operation completed successfully.
  */
hal_status_t HAL_DTS_SetSensorSamplingTime(hal_dts_handle_t *hdts,
                                           hal_dts_sensor_t sensor,
                                           hal_dts_sampling_time_t sampling_time)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));
  ASSERT_DBG_PARAM(IS_DTS_SENSOR_SAMPLING_TIME(sampling_time));

  ASSERT_DBG_STATE(hdts->sensor_states[sensor], HAL_DTS_SENSOR_STATE_IDLE);

#if !defined(USE_ASSERT_DBG_PARAM) && !defined(USE_ASSERT_DBG_STATE)
  STM32_UNUSED(sensor);
#endif /* USE_ASSERT_DBG_PARAM */

  STM32_MODIFY_REG(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_SMP_TIME, (uint32_t)sampling_time);

  return HAL_OK;
}

/**
  * @brief Retrieve the current DTS sensor sampling time.
  * @param  hdts                    Pointer to a @ref hal_dts_handle_t.
  * @param  sensor                  DTS sensor.
  * @retval hal_dts_sampling_time_t DTS sensor sampling time.
  */
hal_dts_sampling_time_t HAL_DTS_GetSensorSamplingTime(const hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));

  ASSERT_DBG_STATE(hdts->global_state, HAL_DTS_STATE_CONFIGURED);

#if !defined(USE_ASSERT_DBG_PARAM)
  STM32_UNUSED(sensor);
#endif /* USE_ASSERT_DBG_PARAM */

  return (hal_dts_sampling_time_t)(uint32_t)STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1,  DTS_CFGR1_TS1_SMP_TIME);
}

/**
  * @brief  Configure the DTS sensor high and low thresholds.
  * @param  hdts                Pointer to a @ref hal_dts_handle_t.
  * @param  sensor              DTS sensor.
  * @param  high_threshold_degc DTS sensor high threshold in degree celsius.
  * @param  low_threshold_degc  DTS sensor low threshold in degree celsius.
  * @note   Low clock frequency and sampling value increase the impact of quantization errors on temperature accuracy.
  * @retval HAL_OK              Operation completed successfully.
  * @retval HAL_ERROR               DTS is not calibrated or invalid config.
  */
hal_status_t HAL_DTS_SetSensorThresholds(hal_dts_handle_t *hdts,
                                         hal_dts_sensor_t sensor,
                                         int32_t high_threshold_degc,
                                         int32_t low_threshold_degc)
{
  uint32_t high_threshold;
  uint32_t low_threshold;
  int32_t  ramp_coeff;
  int32_t  calibration_temperature;
  int32_t  calibration_frequency;
  uint8_t  sampling_time;

  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));
  ASSERT_DBG_PARAM(IS_DTS_SENSOR_THRESHOLD(high_threshold_degc));
  ASSERT_DBG_PARAM(IS_DTS_SENSOR_THRESHOLD(low_threshold_degc));

  ASSERT_DBG_STATE(hdts->sensor_states[sensor], HAL_DTS_SENSOR_STATE_IDLE);

#if !defined(USE_ASSERT_DBG_PARAM) && !defined(USE_ASSERT_DBG_STATE)
  STM32_UNUSED(sensor);
#endif /* USE_ASSERT_DBG_PARAM */

  if (DTS_GetSamplingTimeAndCalibrationValues(hdts, &ramp_coeff, &calibration_temperature, &calibration_frequency, \
                                              &sampling_time) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Calculate the high and low thresholds values in hertz */
  high_threshold = (uint32_t)(int32_t)((ramp_coeff * (high_threshold_degc - calibration_temperature)) \
                                       + calibration_frequency);
  low_threshold  = (uint32_t)(int32_t)((ramp_coeff * (low_threshold_degc  - calibration_temperature)) \
                                       + calibration_frequency);

  if ((low_threshold == 0U) || (high_threshold == 0U))
  {
    return HAL_ERROR; /* Invalid config */
  }

  /* Correct the retrieved sampling time value for the current temperature sensor */
  if (sampling_time == 0U)
  {
    sampling_time = 1U;
  }

  /* Calculate the high and low thresholds in a register compatible writable value */
#if defined(LSE_VALUE)
  if (STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_REFCLK_SEL) == (uint32_t)HAL_DTS_REFERENCE_CLOCK_LSE)
  {
    /* Apply rounding by adding half of the divisor before division to minimize quantization error */
    high_threshold = ((high_threshold * sampling_time) + (LSE_VALUE / 2U)) / LSE_VALUE;
    low_threshold = ((low_threshold * sampling_time) + (LSE_VALUE / 2U)) / LSE_VALUE;
  }
  else
#endif /* LSE_VALUE */
  {
    uint32_t pclk_frequency = HAL_RCC_GetPCLK1Freq();
    uint32_t tmp_val;
    /* In pclk mode, the high and low thresholds in degree celsius are inverted when converted to a register compatible
       writable values. High threshold refers to low temperature and low threshold refers to high temperature.
       Apply rounding by adding half of the divisor before division to minimize quantization error */
    tmp_val = high_threshold;
    high_threshold = ((pclk_frequency * sampling_time) + (low_threshold / 2U)) / low_threshold;
    low_threshold = ((pclk_frequency * sampling_time) + (tmp_val / 2U)) / tmp_val;
  }

  /* Configure sensor thresholds */
  STM32_WRITE_REG(DTS_GET_INSTANCE(hdts)->ITR1, low_threshold | (high_threshold << 16U));

  return HAL_OK;
}

/**
  * @brief Retrieve the current DTS sensor high and low thresholds.
  * @param  hdts                  Pointer to a @ref hal_dts_handle_t.
  * @param  sensor                DTS sensor.
  * @param  p_high_threshold_degc Pointer to a DTS sensor high threshold value in degree celsius.
  * @param  p_low_threshold_degc  Pointer to a DTS sensor low threshold value in degree celsius.
  * @retval HAL_OK             Operation completed successfully.
  * @retval HAL_ERROR          DTS is not calibrated, ramp coefficient error or there's no measurement.
  */
hal_status_t HAL_DTS_GetSensorThresholds(const hal_dts_handle_t *hdts,
                                         hal_dts_sensor_t sensor,
                                         int32_t *p_high_threshold_degc,
                                         int32_t *p_low_threshold_degc)
{
  hal_status_t status;
  uint32_t     temp_reg;

  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));
  ASSERT_DBG_PARAM(p_high_threshold_degc != NULL);
  ASSERT_DBG_PARAM(p_low_threshold_degc != NULL);

  ASSERT_DBG_STATE(hdts->global_state, HAL_DTS_STATE_CONFIGURED);

#if !defined(USE_ASSERT_DBG_PARAM)
  STM32_UNUSED(sensor);
#endif /* USE_ASSERT_DBG_PARAM */

  /* Retrieve sensor thresholds */

  temp_reg = STM32_READ_REG(DTS_GET_INSTANCE(hdts)->ITR1);

  /* Calculate the high and low thresholds values in degree celsius */
#if defined(LSE_VALUE)
  if (STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_REFCLK_SEL) == (uint32_t)HAL_DTS_REFERENCE_CLOCK_LSE)
  {
    status = DTS_DataToTemperature(hdts, ((temp_reg & DTS_ITR1_TS1_HITTHD) >> DTS_ITR1_TS1_HITTHD_Pos), \
                                   p_high_threshold_degc);
    if (status != HAL_ERROR)
    {
      status = DTS_DataToTemperature(hdts, (temp_reg & DTS_ITR1_TS1_LITTHD), p_low_threshold_degc);
    }
  }
  else
#endif /* LSE_VALUE */
  {
    status = DTS_DataToTemperature(hdts, (temp_reg & DTS_ITR1_TS1_LITTHD), p_high_threshold_degc);

    if (status != HAL_ERROR)
    {
      status = DTS_DataToTemperature(hdts, ((temp_reg & DTS_ITR1_TS1_HITTHD) >> DTS_ITR1_TS1_HITTHD_Pos), \
                                     p_low_threshold_degc);
    }
  }

  return status;
}

/**
  * @brief  Get the current DTS kernel clock frequency.
  * @param  hdts     Pointer to a @ref hal_dts_handle_t.
  * @retval uint32_t DTS kernel clock frequency in Hz.
  * @retval 0        Source clock is LSE which is not configured or not ready.
  */
uint32_t HAL_DTS_GetClockFreq(const hal_dts_handle_t *hdts)
{
  uint32_t refclk_frequency;

  ASSERT_DBG_PARAM(hdts != NULL);

  ASSERT_DBG_STATE(hdts->global_state, HAL_DTS_STATE_CONFIGURED);

#if defined(LSE_VALUE)
  if (STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_REFCLK_SEL) == (uint32_t)HAL_DTS_REFERENCE_CLOCK_LSE)
  {
    refclk_frequency = LSE_VALUE;
  }
  else
#endif /* LSE_VALUE */
  {
    refclk_frequency = HAL_RCC_GetPCLK1Freq();
  }

#if !defined(USE_ASSERT_DBG_PARAM) && !defined(USE_ASSERT_DBG_STATE) && !defined(LSE_VALUE)
  STM32_UNUSED(hdts);
#endif /* USE_ASSERT_DBG_PARAM */

  return refclk_frequency;
}

/**
  * @}
  */

/** @addtogroup DTS_Exported_Functions_Group3
  * @{
This section provides a set of functions allowing to configure DTS:
  - Call the function HAL_DTS_StartSensor() to start sensor temperature measurement in blocking mode.
  - Call the function HAL_DTS_StopSensor() to stop sensor temperature measurement in blocking mode.
  - Call the function HAL_DTS_StartSensor_IT() to start sensor temperature measurement in non-blocking mode.
  - Call the function HAL_DTS_StartSensor_IT_Opt() to start sensor temperature measurement in non-blocking mode with
    optional interrupts.
  - Call the function HAL_DTS_StopSensor_IT() to stop sensor temperature measurement in non-blocking mode.
  - Call the function HAL_DTS_PollForSensorTemperature() to Poll for DTS sensor temperature measurement
    in blocking mode.
  - Call the function HAL_DTS_GetSensorTemperature() to retrieve the sensor measured temperature.
  */

/**
  * @brief   Start sensor temperature measurement in blocking mode.
  * @param   hdts      Pointer to a @ref hal_dts_handle_t.
  * @param   sensor    DTS sensor.
  * @warning Disabling the NVIC DTSx IRQ before calling this function is mandatory.
  * @retval  HAL_OK    Operation completed successfully.
  * @retval  HAL_BUSY  The sensor state is not IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  * @retval  HAL_ERROR Factory calibration or ramp coefficient error or the sensor is not ready for measurement.
  */
hal_status_t HAL_DTS_StartSensor(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));

  ASSERT_DBG_STATE(hdts->sensor_states[sensor], HAL_DTS_SENSOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hdts, sensor_states[sensor], HAL_DTS_SENSOR_STATE_IDLE, HAL_DTS_SENSOR_STATE_ACTIVE);

  if (DTS_StartSensor(hdts, sensor, HAL_DTS_OPT_IT_END_OF_MEASURE) != HAL_OK)
  {
    hdts->sensor_states[sensor] = HAL_DTS_SENSOR_STATE_IDLE;

    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

/**
  * @brief  Stop sensor temperature measurement in blocking mode.
  * @param  hdts     Pointer to a @ref hal_dts_handle_t.
  * @param  sensor   DTS sensor.
  * @retval HAL_OK   Operation completed successfully.
  */
hal_status_t HAL_DTS_StopSensor(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));

  ASSERT_DBG_STATE(hdts->sensor_states[sensor], HAL_DTS_SENSOR_STATE_ACTIVE);

  DTS_StopSensor(hdts, sensor);

  hdts->sensor_states[sensor] = HAL_DTS_SENSOR_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Start sensor temperature measurement in non-blocking mode.
  * @param  hdts      Pointer to a @ref hal_dts_handle_t.
  * @param  sensor    DTS sensor.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_BUSY  The sensor state is not IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  * @retval HAL_ERROR Factory calibration or ramp coefficient error or the sensor is not ready for measurement.
  */
hal_status_t HAL_DTS_StartSensor_IT(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));

  ASSERT_DBG_STATE(hdts->sensor_states[sensor], HAL_DTS_SENSOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hdts, sensor_states[sensor], HAL_DTS_SENSOR_STATE_IDLE, HAL_DTS_SENSOR_STATE_ACTIVE);

  if (DTS_StartSensor(hdts, sensor, HAL_DTS_OPT_IT_END_OF_MEASURE) != HAL_OK)
  {
    hdts->sensor_states[sensor] = HAL_DTS_SENSOR_STATE_IDLE;

    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

/**
  * @brief  Start sensor temperature measurement in non-blocking mode with optional interrupts.
  * @param  hdts       Pointer to a @ref hal_dts_handle_t.
  * @param  sensor     DTS sensor.
  * @param  interrupts DTS optional interrupts
  *                    This parameter can be any combination of @ref DTS_Optional_Interrupts_Definitions.
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_BUSY   The sensor state is not IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  * @retval HAL_ERROR  Factory calibration or ramp coefficient error or the sensor is not ready for measurement.
  */
hal_status_t HAL_DTS_StartSensor_IT_Opt(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor, uint32_t interrupts)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));
  ASSERT_DBG_PARAM(IS_DTS_INTERRUPTS(interrupts));

  ASSERT_DBG_STATE(hdts->sensor_states[sensor], HAL_DTS_SENSOR_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hdts, sensor_states[sensor], HAL_DTS_SENSOR_STATE_IDLE, HAL_DTS_SENSOR_STATE_ACTIVE);

  if (DTS_StartSensor(hdts, sensor, interrupts) != HAL_OK)
  {
    hdts->sensor_states[sensor] = HAL_DTS_SENSOR_STATE_IDLE;

    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

/**
  * @brief  Stop sensor temperature measurement in non-blocking mode.
  * @param  hdts     Pointer to a @ref hal_dts_handle_t.
  * @param  sensor   DTS sensor.
  * @retval HAL_OK   Operation completed successfully.
  */
hal_status_t HAL_DTS_StopSensor_IT(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));

  ASSERT_DBG_STATE(hdts->sensor_states[sensor], HAL_DTS_SENSOR_STATE_ACTIVE);

  DTS_StopSensor(hdts, sensor);

  hdts->sensor_states[sensor] = HAL_DTS_SENSOR_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Poll for DTS sensor temperature measurement in blocking mode.
  * @param  hdts        Pointer to a @ref hal_dts_handle_t.
  * @param  sensor      DTS sensor.
  * @param  timeout_ms  Timeout duration in millisecond.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_TIMEOUT Operation exceeds user timeout.
  */
hal_status_t HAL_DTS_PollForSensorTemperature(const hal_dts_handle_t *hdts,
                                              hal_dts_sensor_t sensor,
                                              uint32_t timeout_ms)
{
  hal_status_t status;
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));

  ASSERT_DBG_STATE(hdts->sensor_states[sensor], HAL_DTS_SENSOR_STATE_ACTIVE);

#if !defined(USE_ASSERT_DBG_PARAM) && !defined(USE_ASSERT_DBG_STATE)
  STM32_UNUSED(sensor);
#endif /* USE_ASSERT_DBG_PARAM */

#if defined(LSE_VALUE)
  if (STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_REFCLK_SEL) == (uint32_t)HAL_DTS_REFERENCE_CLOCK_LSE)
  {
    status = DTS_WaitOnStatusUntilTimeout(hdts, DTS_SR_TS1_AITEF, timeout_ms);
  }
  else
#endif /* LSE_VALUE */
  {
    status = DTS_WaitOnStatusUntilTimeout(hdts, DTS_SR_TS1_ITEF, timeout_ms);
  }

  return status;
}

/**
  * @brief  Retrieve the sensor measured temperature.
  * @param  hdts               Pointer to a @ref hal_dts_handle_t.
  * @param  sensor             DTS sensor.
  * @param  p_temperature_degc Pointer to the measured temperature in degree celsius.
  * @retval HAL_OK             Operation completed successfully.
  * @retval HAL_ERROR          DTS is not calibrated, ramp coefficient error or there's no measurement.
  * @retval HAL_INVALID_PARAM  Sampling time is not configured and reference clock is LSE.
  */
hal_status_t HAL_DTS_GetSensorTemperature(const hal_dts_handle_t *hdts,
                                          hal_dts_sensor_t sensor,
                                          int32_t *p_temperature_degc)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));
  ASSERT_DBG_PARAM(p_temperature_degc != NULL);

#if !defined(USE_ASSERT_DBG_PARAM)
  STM32_UNUSED(sensor);
#endif /* USE_ASSERT_DBG_PARAM */

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_temperature_degc == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hdts->global_state, HAL_DTS_STATE_CONFIGURED);

  return DTS_DataToTemperature(hdts, (STM32_READ_REG(DTS_GET_INSTANCE(hdts)->DR) & DTS_DR_TS1_MFREQ),
                               p_temperature_degc);
}

/**
  * @}
  */

/** @addtogroup DTS_Exported_Functions_Group4
  * @{
This section provides function allowing to handle the DTS interrupt request, HAL_DTS_IRQHandler().

This section provides also a set of functions allowing to handle callbacks:
  - Call the function HAL_DTS_CpltCallback() is called when measurement complete occurs on a specified sensor.
  - Call the function HAL_DTS_LowThresholdCallback() is called when low threshold occurs on a specified sensor.
  - Call the function HAL_DTS_HighThresholdCallback() is called when high threshold occurs on a specified sensor.

This section provides also a set of functions allowing to register callbacks:
  - Call the function HAL_DTS_RegisterCpltCallback() to register measurement complete callback.g mode.
  - Call the function HAL_DTS_RegisterLowThresholdCallback() to register low thresholdcallback.t.
  - Call the function HAL_DTS_RegisterHighThresholdCallback() to register high threshold callback.
  */

/**
  * @brief  Handle the DTS interrupt request.
  * @param  hdts Pointer to a @ref hal_dts_handle_t.
  */
void HAL_DTS_IRQHandler(hal_dts_handle_t *hdts)
{
  ASSERT_DBG_PARAM(hdts != NULL);

  uint32_t it_flag = STM32_READ_REG(DTS_GET_INSTANCE(hdts)->SR);

  /* DTS sensor measurement complete interrupt------------------------------------------*/
  if ((it_flag & (HAL_DTS_IT_TS1_AITE | HAL_DTS_IT_TS1_ITE)) != 0UL)
  {
    /* Clear the measurement complete flag */
    HAL_DTS_ClearFlag(hdts, (HAL_DTS_IT_TS1_AITE | HAL_DTS_IT_TS1_ITE));

    /* Call the measurement complete callback */
#if defined(USE_HAL_DTS_REGISTER_CALLBACKS) && (USE_HAL_DTS_REGISTER_CALLBACKS == 1)
    hdts->p_cplt_cb(hdts, HAL_DTS_SENSOR_1);
#else
    HAL_DTS_CpltCallback(hdts, HAL_DTS_SENSOR_1);
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */
  }

  /* DTS sensor Low threshold detection interrupt---------------------------------------*/
  if ((it_flag & (HAL_DTS_IT_TS1_AITL | HAL_DTS_IT_TS1_ITL)) != 0UL)
  {
    /* Clear the Low threshold detection flag */
    HAL_DTS_ClearFlag(hdts, (HAL_DTS_IT_TS1_AITL | HAL_DTS_IT_TS1_ITL));

    /* Call the Low threshold detection callback */
#if defined(USE_HAL_DTS_REGISTER_CALLBACKS) && (USE_HAL_DTS_REGISTER_CALLBACKS == 1)
    hdts->p_low_threshold_cb(hdts, HAL_DTS_SENSOR_1);
#else
    HAL_DTS_LowThresholdCallback(hdts, HAL_DTS_SENSOR_1);
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */
  }

  /* DTS sensor High threshold detection interrupt---------------------------------------*/
  if ((it_flag & (HAL_DTS_IT_TS1_AITH | HAL_DTS_IT_TS1_ITH)) != 0UL)
  {
    /* Clear the High threshold detection flag */
    HAL_DTS_ClearFlag(hdts, (HAL_DTS_IT_TS1_AITH | HAL_DTS_IT_TS1_ITH));

    /* Call the High threshold detection callback */
#if defined(USE_HAL_DTS_REGISTER_CALLBACKS) && (USE_HAL_DTS_REGISTER_CALLBACKS == 1)
    hdts->p_high_threshold_cb(hdts, HAL_DTS_SENSOR_1);
#else
    HAL_DTS_HighThresholdCallback(hdts, HAL_DTS_SENSOR_1);
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */
  }

  return;
}

/**
  * @brief   Measurement complete callback.
  * @param   hdts   Pointer to a @ref hal_dts_handle_t.
  * @param   sensor DTS sensor.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_DTS_CpltCallback(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  STM32_UNUSED(hdts);
  STM32_UNUSED(sensor);
}

/**
  * @brief   Low threshold callback.
  * @param   hdts   Pointer to a @ref hal_dts_handle_t.
  * @param   sensor DTS sensor.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_DTS_LowThresholdCallback(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  STM32_UNUSED(hdts);
  STM32_UNUSED(sensor);
}

/**
  * @brief   High threshold callback.
  * @param   hdts   Pointer to a @ref hal_dts_handle_t.
  * @param   sensor DTS sensor.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_DTS_HighThresholdCallback(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  STM32_UNUSED(hdts);
  STM32_UNUSED(sensor);
}

#if defined(USE_HAL_DTS_REGISTER_CALLBACKS) && (USE_HAL_DTS_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a user measurement complete callback.
  * @param  hdts              Pointer to a @ref hal_dts_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_DTS_RegisterCpltCallback(hal_dts_handle_t *hdts, hal_dts_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hdts != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hdts->global_state, HAL_DTS_STATE_CONFIGURED);

  hdts->p_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user low threshold callback.
  * @param  hdts              Pointer to a @ref hal_dts_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_DTS_RegisterLowThresholdCallback(hal_dts_handle_t *hdts, hal_dts_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hdts != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hdts->global_state, HAL_DTS_STATE_CONFIGURED);

  hdts->p_low_threshold_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user high threshold callback.
  * @param  hdts              Pointer to a @ref hal_dts_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_DTS_RegisterHighThresholdCallback(hal_dts_handle_t *hdts, hal_dts_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hdts != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hdts->global_state, HAL_DTS_STATE_CONFIGURED);

  hdts->p_high_threshold_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_DTS_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup DTS_Exported_Functions_Group5
  * @{
This section provides a set of functions allowing to get all current states:
  - Call the function HAL_DTS_GetState() to get the current global state.
  - Call the function HAL_DTS_GetSensorState() to get the current state of a specified sensor.
  */

/**
  * @brief  Get the current global state.
  * @param  hdts            Pointer to a @ref hal_dts_handle_t.
  * @retval hal_dts_state_t Global state.
  */
hal_dts_state_t HAL_DTS_GetState(const hal_dts_handle_t *hdts)
{
  ASSERT_DBG_PARAM(hdts != NULL);

  return hdts->global_state;
}

/**
  * @brief  Get the current global state.
  * @param  hdts            Pointer to a @ref hal_dts_handle_t.
  * @param  sensor          DTS sensor.
  * @retval hal_dts_state_t Global state.
  */
hal_dts_sensor_state_t HAL_DTS_GetSensorState(const hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_SENSOR(sensor));

  return hdts->sensor_states[sensor];
}

/**
  * @}
  */

/** @addtogroup DTS_Exported_Functions_Group6
  * @{
This section provides a set of functions allowing to set/get user data:
  - Call the function HAL_DTS_SetUserData() to set user data in DTS handle.
  - Call the function HAL_DTS_GetUserData() to get user data from DTS handle.
  - Call the function HAL_DTS_GetInstance() to get the HAL DTS instance.
  */
#if defined(USE_HAL_DTS_USER_DATA) && (USE_HAL_DTS_USER_DATA == 1)
/**
  * @brief  Get the current global state.
  * @param  hdts            Pointer to a @ref hal_dts_handle_t.
  * @param  p_user_data     Pointer to a user data structure.
  */
void HAL_DTS_SetUserData(hal_dts_handle_t *hdts, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hdts != NULL);

  hdts->p_user_data = p_user_data;
}

/**
  * @brief  Get the current global state.
  * @param  hdts Pointer to a @ref hal_dts_handle_t.
  * @retval void Pointer to user data structure.
  */
const void *HAL_DTS_GetUserData(const hal_dts_handle_t *hdts)
{
  ASSERT_DBG_PARAM(hdts != NULL);

  return  hdts->p_user_data;
}
#endif /* USE_HAL_DTS_USER_DATA */

/**
  * @brief  Get the DTS instance.
  * @param  hdts Pointer to a @ref hal_dts_handle_t structure.
  * @retval HAL_DTS The HAL DTS instance.
  */
hal_dts_t HAL_DTS_GetInstance(const hal_dts_handle_t *hdts)
{
  ASSERT_DBG_PARAM(hdts != NULL);
  ASSERT_DBG_PARAM(IS_DTS_ALL_INSTANCE((DTS_TypeDef *)((uint32_t)hdts->instance)));

  return hdts->instance;
}
/**
  * @}
  */
/**
  * @}
  */

/** @addtogroup DTS_Private_Functions
  * @{
  */

/**
  * @brief  This function handles DTS Communication Timeout.
  * @param  hdts Pointer to a hal_dts_handle_t structure.
  * @param  flag Specifies the DTS flag to check.
  * @param  timeout_ms Timeout duration
  * @retval HAL_TIMEOUT Timeout exceeded
  * @retval HAL_OK Operation completed successfully
  */
static hal_status_t DTS_WaitOnStatusUntilTimeout(const hal_dts_handle_t *hdts, uint32_t flag, uint32_t timeout_ms)
{
  /* Init tickstart for timeout management*/
  uint32_t tickstart = HAL_GetTick();

  hal_status_t status_tmp = HAL_OK;

  while (HAL_DTS_IsActiveFlag(hdts, flag) == 0U)
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        if (HAL_DTS_IsActiveFlag(hdts, flag) == 0U)
        {
          status_tmp = HAL_TIMEOUT;
        }
        break;
      }
    }
  }
  return status_tmp;
}

/**
  * @brief  Start sensor temperature measurement in blocking/non-blocking mode with optional interrupts.
  * @param  hdts       Pointer to a @ref hal_dts_handle_t.
  * @param  sensor     DTS sensor.
  * @param  interrupts DTS optional interrupts
  *                    This parameter can be any combination of @ref DTS_Optional_Interrupts_Definitions.
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_ERROR  Factory calibration or ramp coefficient error or the sensor is not ready for measurement.
  */
static hal_status_t DTS_StartSensor(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor, uint32_t interrupts)
{
  STM32_UNUSED(sensor);

  {
    /* Get the calibration value of the ramp coefficient for the temperature sensor in Hertz per degree celsius */
    uint16_t ramp_coeff = (uint16_t)(STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->RAMPVALR, DTS_RAMPVALR_TS1_RAMP_COEFF));

    if (((STM32_READ_REG(DTS_GET_INSTANCE(hdts)->T0VALR1) & DTS_T0VALR1_TS1_T0) > 1UL) || (ramp_coeff == 0U))
    {
      /* Factory calibration or ramp coefficient error */
      return HAL_ERROR;
    }
  }

  /* Disable all interrupts */
  HAL_DTS_DisableIT(hdts, (HAL_DTS_IT_TS1_SYNC_ALL | HAL_DTS_IT_TS1_ASYNC_ALL));

  /* Clear continuous measures bit in case that the user re_initialize the HAL DTS during continuous measurement */
  STM32_CLEAR_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_START);

  /* Enable interrupts */
  if (STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_REFCLK_SEL) == (uint32_t)HAL_DTS_REFERENCE_CLOCK_LSE)
  {
    /* Enable synchronous NVIC sources and their asynchronous wake-up counterparts. */
    HAL_DTS_EnableIT(hdts, interrupts | (interrupts << DTS_ITENR_TS1_AITEEN_Pos));
  }
  else
  {
    HAL_DTS_EnableIT(hdts, interrupts);
  }

  /* Enable DTS sensor */
  STM32_SET_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_EN);

  if (DTS_WaitOnStatusUntilTimeout(hdts, DTS_SR_TS1_RDY, DTS_DELAY_STARTUP) != HAL_OK)
  {
    /* Disable DTS sensor and associated interrupt */
    STM32_CLEAR_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_EN);
    HAL_DTS_DisableIT(hdts, HAL_DTS_IT_TS1_SYNC_ALL | HAL_DTS_IT_TS1_ASYNC_ALL);

    return HAL_ERROR;
  }

  if (STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_INTRIG_SEL) == (uint32_t)HAL_DTS_TRIGGER_SOFTWARE)
  {
    /* Start continuous measures */
    STM32_SET_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_START);

    /* Ensure that start is taken into account */
    HAL_Delay(DTS_TIMEOUT_MS);
  }

  return HAL_OK;
}

/**
  * @brief  Stop sensor temperature measurement in blocking mode.
  * @param  hdts     Pointer to a @ref hal_dts_handle_t.
  * @param  sensor   DTS sensor.
  */
static void DTS_StopSensor(hal_dts_handle_t *hdts, hal_dts_sensor_t sensor)
{
  STM32_UNUSED(sensor);

  /* Disable all interrupts*/
  HAL_DTS_DisableIT(hdts, (HAL_DTS_IT_TS1_SYNC_ALL | HAL_DTS_IT_TS1_ASYNC_ALL));

  if (STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_INTRIG_SEL) == (uint32_t)HAL_DTS_TRIGGER_SOFTWARE)
  {
    /* Stop continuous measures */
    STM32_CLEAR_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_START);

    /* Ensure that stop is taken into account */
    HAL_Delay(DTS_TIMEOUT_MS);
  }

  /* Disable DTS sensor */
  STM32_CLEAR_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_TS1_EN);
}

/**
  * @brief  Retrieve configured sampling time and calibration values.
  * @param  hdts     Pointer to a @ref hal_dts_handle_t.
  * @param  ramp_coefficient        Pointer to calibration value of the ramp coefficient.
  * @param  calibration_temperature Pointer to calibration value of the temperature in degree cesius.
  * @param  calibration_frequency   Pointer to calibration value of the frequency in hertz.
  * @param  sampling_time           Pointer to the configured sampling time.
  * @retval HAL_OK                  Operation completed successfully.
  * @retval HAL_ERROR               DTS is not calibrated.
  */
static hal_status_t DTS_GetSamplingTimeAndCalibrationValues(const hal_dts_handle_t *hdts, int32_t *ramp_coefficient, \
                                                            int32_t  *calibration_temperature, \
                                                            int32_t *calibration_frequency, uint8_t  *sampling_time)
{
  uint32_t temp_reg;
  /* Get the T0 value register of the current temperature sensor */
  temp_reg = STM32_READ_REG(DTS_GET_INSTANCE(hdts)->T0VALR1);

  /* Get the calibration value of the T0 temperature for the current temperature sensor in degree celsius */
  if ((temp_reg & DTS_T0VALR1_TS1_T0) == DTS_FACTORY_TEMPERATURE_CALIBRATION1)
  {
    *calibration_temperature = DTS_FACTORY_TEMPERATURE1;
  }
  else if ((temp_reg & DTS_T0VALR1_TS1_T0) == DTS_FACTORY_TEMPERATURE_CALIBRATION2)
  {
    *calibration_temperature = DTS_FACTORY_TEMPERATURE2;
  }
  else
  {
    return HAL_ERROR;
  }

  /* Get the calibration value of the frequency measured at T0 for the current temperature sensor in Hertz */
  /* Register value is in 0.1 kHz */
  *calibration_frequency = (int32_t)(uint32_t)((temp_reg & DTS_T0VALR1_TS1_FMT0) * 100UL);

  temp_reg = STM32_READ_REG(DTS_GET_INSTANCE(hdts)->CFGR1);

  /* Get the sampling time for the current temperature sensor */
  *sampling_time = (uint8_t)(STM32_READ_BIT(temp_reg, DTS_CFGR1_TS1_SMP_TIME) >> DTS_CFGR1_TS1_SMP_TIME_Pos);

  /* Get the calibration value of the ramp coefficient for the temperature sensor in Hertz per degree celsius */
  *ramp_coefficient = (int32_t)(uint32_t)(STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->RAMPVALR,
                                                         DTS_RAMPVALR_TS1_RAMP_COEFF));

  return HAL_OK;
}

/**
  * @brief  Convert DR and ITR1 Registers Data to Temperature in degree celsius.
  * @param  hdts               Pointer to a @ref hal_dts_handle_t.
  * @param  data_to_calculate  Data to be converted into temperature.
  * @param  p_temperature_degc Pointer to the measured temperature in degree celsius.
  * @retval HAL_OK             Operation completed successfully.
  * @retval HAL_ERROR          DTS is not calibrated, ramp coefficient error or there's no measurement.
  */
static hal_status_t DTS_DataToTemperature(const hal_dts_handle_t *hdts, uint32_t data_to_calculate, \
                                          int32_t *p_temperature_degc)
{
  int32_t  temperature;
  int32_t  ramp_coeff;
  int32_t  calibration_temperature;
  int32_t  calibration_frequency;
  uint32_t pclk_frequency = 0;
  uint32_t lse_frequency = 0;
  uint8_t  sampling_time;

  if (DTS_GetSamplingTimeAndCalibrationValues(hdts, &ramp_coeff, &calibration_temperature, &calibration_frequency, \
                                              &sampling_time) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((ramp_coeff == (int32_t)0) || (data_to_calculate == 0UL))
  {
    /* DTS temperature sensor is not calibrated or there's no measurement */
    return HAL_ERROR;
  }

#if defined(LSE_VALUE)
  if (STM32_READ_BIT(DTS_GET_INSTANCE(hdts)->CFGR1, DTS_CFGR1_REFCLK_SEL) == (uint32_t)HAL_DTS_REFERENCE_CLOCK_LSE)
  {
    lse_frequency = LSE_VALUE;
  }
  else
#endif /* LSE_VALUE */
  {
    pclk_frequency = HAL_RCC_GetPCLK1Freq();
  }

  /* Correct the retrieved sampling time value for the current temperature sensor */
  if (sampling_time == 0U)
  {
    sampling_time = 1U;
  }

  /* Calculate the temperature value in Hertz */
  temperature = (int32_t)(uint32_t)(((pclk_frequency * (uint32_t)sampling_time) / data_to_calculate) \
                                    + ((data_to_calculate * lse_frequency) / (uint32_t)sampling_time));

  /* Calculate the temperature value in degree celsius */
  *p_temperature_degc = ((temperature - calibration_frequency) / ramp_coeff) + calibration_temperature;

  return HAL_OK;
}
/**
  * @}
  */

/**
  * @}
  */
#endif /* USE_HAL_DTS_MODULE */
#endif /* DTS */

/**
  * @}
  */
