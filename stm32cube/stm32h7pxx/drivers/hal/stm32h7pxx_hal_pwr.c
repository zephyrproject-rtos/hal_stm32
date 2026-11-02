/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_pwr.c
  * @brief   PWR HAL module driver.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software
  * component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

#if defined(PWR)
#if defined(USE_HAL_PWR_MODULE) && (USE_HAL_PWR_MODULE == 1)
/** @addtogroup PWR
  * @{
  */
/** @defgroup PWR_Introduction PWR Introduction
  * @{

  - The PWR peripheral in STM32 manages power modes (sleep, stop, standby), voltage scaling and power supplies.
  - It reduces power consumption, supports multiple wake-up sources, and is essential for battery-powered applications.
  - Control is achieved through PWR registers; use HAL functions for simplified configuration.

  */
/**
  * @}
  */

/** @defgroup PWR_How_To_Use PWR How To Use
  * @{

# PWR peripheral overview

This section provides an overview of the supply architecture for the different power domains and of the supply
configuration controller.

This file provides firmware functions to manage the following features:
   - Power supply management functions.
   - Low power mode management functions.
   - Wake-up pins management functions.
   - RTC domain access management functions.
   - Voltage monitoring management functions.
   - Memory retention management functions.
   - Memory low power management functions.
   - Battery management functions.
   - UCPD management functions.
   - Standby I/O pull management functions.

# How to use the PWR HAL module driver

This module provides different sets of APIs that allow:

1. Manage power supplies:
   The power supplies can be configured to manage application power consumption and performance.
   - Configure the main regulator voltage scaling range for different power modes:
     - Call HAL_PWR_SetMainRegulatorVoltageScalingRange() to configure the voltage scaling range.
   - Get the voltage scaling range configuration:
     - Call HAL_PWR_GetMainRegulatorVoltageScalingRange() to get the voltage scaling range configuration.
   - Get the active voltage scaling range:
     - Call HAL_PWR_GetMainRegulatorActiveVoltageScalingRange() to get the active voltage scaling range.
   - Configure the main regulator voltage scaling range during stop mode:
     - Call HAL_PWR_LP_SetMainRegulatorStopVoltageScalingRange() to configure the voltage scaling range
       during stop mode.
   - Get the voltage scaling range configuration during stop mode:
     - Call HAL_PWR_LP_GetMainRegulatorStopVoltageScalingRange() to get the voltage scaling range configuration
       during stop mode.
   - Get the configured main regulator supply source:
     - Call HAL_PWR_GetMainRegulatorSupply() to get the configured main regulator supply source.
   - Get the main regulator supply source status:
     - Call HAL_PWR_GetMainRegulatorSupplyStatus() to get the main regulator supply source status.
   - Set the analog IO switch supply source:
     - Call HAL_PWR_SetAnalogIOSwitchSupply() to set the analog IO switch supply source.
   - Get the analog IO switch supply source:
     - Call HAL_PWR_GetAnalogIOSwitchSupply() to get the analog IO switch supply source.

2. Manage low power modes:
   Use available power modes to reduce power consumption.
   - Clear the core pending event to clear internal Cortex event before entering sleep or stop mode:
     - Call HAL_PWR_ClearCorePendingEvent() to clear the core pending event.
   - Enter the MCU into low power modes:
     - Enter the MCU into sleep mode through a WFE or WFI request:
       - Call HAL_PWR_EnterSleepMode() to enter sleep mode.
     - Enter the MCU into stop mode through a WFE or WFI request:
       - Call HAL_PWR_EnterStopMode() to enter stop mode.
     - Enter the MCU into standby mode:
       - Call HAL_PWR_EnterStandbyMode() to enter standby mode.
   - Configure the core deep sleep mode:
     - Call HAL_PWR_SetCoreSleepMode() to configure the core deep sleep mode.
   - Get the core deep sleep mode configuration:
     - Call HAL_PWR_GetCoreSleepMode() to get the core deep sleep mode configuration.
   - Enable, disable, and check core sleep on exit. This feature allows the core to enter sleep mode immediately
     after interrupt handling completes without returning to the main program.
     - Call HAL_PWR_EnableCoreSleepOnExit(), HAL_PWR_DisableCoreSleepOnExit(), and
       HAL_PWR_IsEnabledCoreSleepOnExit() to enable, disable, and check core sleep on exit.
   - Enable, disable, and check core send event on pending. This feature allows the Cortex to generate an event
     signal whenever there is a pending interrupt or exception. Use this event signal to wake up the processor from
     a low-power state and ensure that the system responds promptly to interrupts.
     - Call HAL_PWR_EnableCoreSendEventOnPending(), HAL_PWR_DisableCoreSendEventOnPending(), and
       HAL_PWR_IsEnabledCoreSendEventOnPending() to enable, disable, and check core send event on pending.
   - Get and clean the previous system power mode:
     - Call HAL_PWR_GetPreviousSystemPowerMode() to get the previous system power mode.
     - Call HAL_PWR_CleanPreviousSystemPowerMode() to clean the previous system power mode flag(s)
       before entering a low power mode.
   - Handle the PWR wake-up interrupt from Stop low power mode:
     - This functionality is ensured by HAL_PWR_WakeupPin_IRQHandler().

3. Manage the wake-up pins:
   Use a wake-up pin to wake up the system from low power modes.
   - Configure the wake-up pin polarity and pull without enabling it:
     - Call HAL_PWR_LP_SetConfigWakeupPin() to configure wake-up polarity and pull.
       Use the p_config pointer to provide the configuration.
       - When p_config is null, this function returns an HAL_INVALID_PARAM.
   - Get the wake-up pin polarity and pull configuration:
     - Call HAL_PWR_LP_GetConfigWakeupPin() to get the wake-up pin polarity and pull configuration.
   - Enable, disable and check the wake-up pin:
     - Call HAL_PWR_LP_EnableWakeupPin(), HAL_PWR_LP_DisableWakeupPin(), and
       HAL_PWR_LP_IsEnabledWakeupPin() to enable, disable and check the wake-up pin.
   - Get and clean the wake-up sources:
     - Call HAL_PWR_LP_GetWakeupSource() and HAL_PWR_LP_CleanWakeupSource() to read and clear wake-up sources.

4. Manage RTC domain write protection:
   After a system reset, the RTC domain is protected against possible unwanted write accesses.
   - Enable, disable and check the write protection for the RTC domain:
     - Call HAL_PWR_EnableRTCDomainWriteProtection(), HAL_PWR_DisableRTCDomainWriteProtection(), and
       HAL_PWR_IsEnabledRTCDomainWriteProtection() to enable, disable, and check write protection.

5. Manage voltage monitoring:
   The monitor can be used to manage the power supplies and supply domains.
   - Configure the voltage threshold detector by the programmable voltage detector:
     - Call HAL_PWR_SetProgrammableVoltageDetectorLevel() to configure the programmable voltage detector level.
   - Get the programmable voltage detector configuration:
     - Call HAL_PWR_GetProgrammableVoltageDetectorLevel() to get the programmable voltage detector configuration.
   - Enable, disable and check the programmable voltage detector status:
     - Call HAL_PWR_EnableProgrammableVoltageDetector(), HAL_PWR_DisableProgrammableVoltageDetector(), and
       HAL_PWR_IsEnabledProgrammableVoltageDetector() to enable, disable, and check the programmable voltage detector
       status.
   - Get the programmable voltage detector output:
     - Call HAL_PWR_GetProgrammableVoltageDetectorOutput() to get the programmable voltage detector output.
   - Configure the voltage threshold detector by the analog voltage detector:
     - Call HAL_PWR_SetAnalogVoltageDetectorLevel() to configure the analog voltage detector level.
   - Get the analog voltage detector configuration:
     - Call HAL_PWR_GetAnalogVoltageDetectorLevel() to get the analog voltage detector configuration.
   - Enable, disable and check the analog voltage detector status:
     - Call HAL_PWR_EnableAnalogVoltageDetector(), HAL_PWR_DisableAnalogVoltageDetector(), and
       HAL_PWR_IsEnabledAnalogVoltageDetector() to enable, disable, and check the analog voltage detector status.
   - Get the analog voltage detector output:
     - Call HAL_PWR_GetAnalogVoltageDetectorOutput() to get the analog voltage detector output.
   - Enable, disable and check the peripheral voltage monitoring status:
     - Call HAL_PWR_EnableTemperatureVbatMonitor(), HAL_PWR_DisableTemperatureVbatMonitor(), and
       HAL_PWR_IsEnabledTemperatureVbatMonitor() to enable, disable, and check the peripheral voltage monitoring status.
   - Get the temperature level status:
     - Call HAL_PWR_GetTemperatureLevelStatus() to get the temperature level status.
   - Get the VBAT voltage level status:
     - Call HAL_PWR_GetVbatVoltageLevelStatus() to get the VBAT voltage level status.

6. Manage memory retention:
   After entering low power mode, the volatile memory content can be retained or not according to application needs.
   - Enable, disable, and check memory retention:
     - Call HAL_PWR_LP_EnableMemoryRetention(), HAL_PWR_LP_DisableMemoryRetention(), and
       HAL_PWR_LP_IsEnabledMemoryRetention() to enable, disable, and check memory retention.

7. Manage memory power modes:
   The flash memory can be configured to enter low power mode when the MCU enters a low power mode.
   - Enable, disable, and check the flash low power mode in stop mode:
     - Call HAL_PWR_LP_EnableFlashLowPWRMode(), HAL_PWR_LP_DisableFlashLowPWRMode(), and
       HAL_PWR_LP_IsEnabledFlashLowPWRMode() to enable, disable, and check the flash low power mode.

8. Manage battery charging:
   Several APIs are available to manage the battery charging:
   - Set and get battery charging resistor configuration:
     - Call HAL_PWR_SetConfigBatteryCharging() and HAL_PWR_GetConfigBatteryCharging()
       to set and get the battery charging resistor configuration.
   - Enable, disable, and check the battery charging:
     - Call HAL_PWR_EnableBatteryCharging(), HAL_PWR_DisableBatteryCharging(), and
       HAL_PWR_IsEnabledBatteryCharging() to enable, disable, and check the battery charging.

9. Manage UCPD:
   Several APIs are available to enable or disable the UCPD dead battery feature:
   - Enable, disable, and check UCPD dead battery: (*)
     - Call HAL_PWR_LP_EnableUCPDDeadBattery(), HAL_PWR_LP_DisableUCPDDeadBattery(), and
       HAL_PWR_LP_IsEnabledUCPDDeadBattery() to enable, disable, and check the UCPD dead battery feature.
   - Enable, disable, and check UCPD configuration retention: (*)
     - Call HAL_PWR_LP_EnableUCPDRetention(), HAL_PWR_LP_DisableUCPDRetention(), and
       HAL_PWR_LP_IsEnabledUCPDRetention() to enable, disable, and check the UCPD configuration retention.

10. Manage Standby I/O pull configuration:
   Several APIs are available to manage pull-up or pull-down I/O for I3C1 and XSPI1 during standby.
   - Enable, disable, and check pull status:
     - Call HAL_PWR_EnableGPIOPull(), HAL_PWR_DisableGPIOPull(), and HAL_PWR_IsEnabledGPIOPull() to enable, disable,
       and check the pull status.
   - Set and get pull configuration for I3C1 and XSPI1:
     - Call HAL_PWR_SetConfigPeriphGPIOPull() and HAL_PWR_GetConfigPeriphGPIOPull() to set and get the peripheral pull
       configuration.

(*) This feature is not available on all devices.
  */
/**
  * @}
  */

/** @defgroup PWR_Configuration_Table PWR Configuration Table
  * @{
## Configuration inside the PWR driver

Config defines       | Description        | Default value | Note
---------------------| ---------------    | ------------- | ------------------------------------------------------------
PRODUCT              | from IDE           | NA            | The selected device
USE_HAL_PWR_MODULE   | from hal_conf.h    | 1U            | When set, HAL PWR module is enabled.
USE_ASSERT_DBG_PARAM | from IDE           | None          | When defined, enable parameter assertions.
USE_HAL_CHECK_PARAM  | from hal_conf.h    | 0U            | When set, parameters are checked at runtime.
  */
/**
  * @}
  */

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Constants PWR Private Constants
  * @{
  */
/* Time out value of flags setting */
#define PWR_VOS_SELECT_MAX_DELAY          0x32U   /*!< Max VOS timeout       */
#define PWR_BACKUPRAM_ENABLE_MAX_DELAY    0x32U   /*!< Max BACKUPRAM timeout */
/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Variables PWR Private Variables
  * @{
  */

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Macros PWR Private Macros
  * @{
  */

/*! Set wake-up pins check macro */
#define IS_PWR_SET_WAKEUP_PIN(pin) \
  ((((pin) & HAL_PWR_WAKEUP_PIN_ALL) != 0U) && (((pin) & (~HAL_PWR_WAKEUP_PIN_ALL)) == 0U))

/*! Set wake-up sources check macro */
#define IS_PWR_SET_WAKEUP_SOURCE(source) \
  ((((source) & HAL_PWR_WAKEUP_SOURCE_ALL) != 0U) && (((source) & (~HAL_PWR_WAKEUP_SOURCE_ALL)) == 0U))

/*! Wake-up pin polarity check macro */
#define IS_PWR_WAKEUP_PIN_POLARITY(polarity) \
  (((polarity) == HAL_PWR_WAKEUP_PIN_POLARITY_HIGH ) || ((polarity) == HAL_PWR_WAKEUP_PIN_POLARITY_LOW))

/*! Wake-up pin pull check macro */
#define IS_PWR_WAKEUP_PIN_PULL(pull)                                                 \
  (((pull) == HAL_PWR_WAKEUP_PIN_PULL_NO ) || ((pull) == HAL_PWR_WAKEUP_PIN_PULL_UP) \
   || ((pull) == HAL_PWR_WAKEUP_PIN_PULL_DOWN))

/*! Get wake-up pins check macro */
#define IS_PWR_GET_WAKEUP_PIN(pin)    \
  (((pin) == HAL_PWR_WAKEUP_PIN_1)    \
   || ((pin) == HAL_PWR_WAKEUP_PIN_2) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_3) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_4) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_5) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_6) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_7) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_8))

/*! Voltage scaling range check macro */
#define IS_PWR_VOLT_SCALE_RANGE(range)  \
  (((range) == HAL_PWR_VOLT_SCALE_0)    \
   || ((range) == HAL_PWR_VOLT_SCALE_1) \
   || ((range) == HAL_PWR_VOLT_SCALE_2))

/*! Stop voltage scaling range check macro */
#define IS_PWR_STOP_VOLT_SCALE_RANGE(range)     \
  (((range) == LL_PWR_REGU_STOP_VOLT_SCALE_LOW) \
   || ((range) == LL_PWR_REGU_STOP_VOLT_SCALE_HIGH))

/*! Main regulator supply check macro */
#define IS_PWR_SET_MAIN_REGULATOR_SUPPLY(regulator)          \
  (((regulator) == HAL_PWR_MAIN_REGULATOR_SUPPLY_NOT_BYPASS) \
   || ((regulator) == HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASS))

/*! Analog IO switch supply check macro */
#define IS_PWR_ANALOG_IO_SWITCH_SUPPLY(analog_io_switch_supply)        \
  (((analog_io_switch_supply) == HAL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY) \
   || ((analog_io_switch_supply) == HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY))

/*! Low power mode entry check macro */
#define IS_PWR_LP_MODE_ENTRY(entry) \
  (((entry) == HAL_PWR_LOW_PWR_MODE_WFE) || ((entry) == HAL_PWR_LOW_PWR_MODE_WFI))

/*! Stop mode check macro */
#define IS_PWR_STOP_MODE(mode) \
  ((mode) == HAL_PWR_STOP_MODE)

/*! Core sleep mode check macro */
#define IS_PWR_CORE_SLEEP_MODE(mode) \
  (((mode) == HAL_PWR_CORE_SLEEP) || ((mode) == HAL_PWR_CORE_DEEP_SLEEP))

/*! PVD level check macro */
#define IS_PWR_PVD_LEVEL(level)        \
  (((level) == HAL_PWR_PVD_VDD_LEVEL_1)    \
   || ((level) == HAL_PWR_PVD_VDD_LEVEL_2) \
   || ((level) == HAL_PWR_PVD_VDD_LEVEL_3) \
   || ((level) == HAL_PWR_PVD_VDD_LEVEL_4) \
   || ((level) == HAL_PWR_PVD_VDD_LEVEL_5) \
   || ((level) == HAL_PWR_PVD_VDD_LEVEL_6) \
   || ((level) == HAL_PWR_PVD_VDD_LEVEL_7) \
   || ((level) == HAL_PWR_PVD_PVDIN_VREFINT))

/*! AVD level check macro */
#define IS_PWR_AVD_LEVEL(level)        \
  (((level) == HAL_PWR_AVD_VDDA_LEVEL_1)    \
   || ((level) == HAL_PWR_AVD_VDDA_LEVEL_2) \
   || ((level) == HAL_PWR_AVD_VDDA_LEVEL_3) \
   || ((level) == HAL_PWR_AVD_VDDA_LEVEL_4))

/*! Memory retention check macro */
#define IS_PWR_MEMORY_RETENTION(memory) \
  ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)

/*! Battery charging resistor selection check macro */
#define IS_PWR_BATTERY_RESISTOR_SELECT(resistor) \
  (((resistor) == HAL_PWR_BATTERY_CHARGING_RES_5K) || ((resistor) == HAL_PWR_BATTERY_CHARGING_RES_1_5K))

/*! I3C standby pull set config check macro */
#define IS_PWR_I3C_GPIO_PULL_SET_CONFIG(gpio, pull)          \
  (((gpio >= HAL_PWR_I3C1_PULL_PA15)&&(gpio <= HAL_PWR_I3C1_PULL_PI2)) \
   && (((pull) == HAL_PWR_GPIO_PULL_NO) || ((pull) == HAL_PWR_GPIO_PULL_UP)))

/*! xSPI standby pull set config check macro */
#define IS_PWR_XSPI_GPIO_PULL_SET_CONFIG(gpio, pull)           \
  (((gpio >= HAL_PWR_XSPI1_PULL_PG10)&&(gpio <= HAL_PWR_XSPI1_PULL_PH0)) \
   && (((pull) == HAL_PWR_GPIO_PULL_NO) || ((pull) == HAL_PWR_GPIO_PULL_UP) || ((pull) == HAL_PWR_GPIO_PULL_DOWN)))

/*! Peripherals standby pull set config check macro */
#define IS_PWR_PERIPH_GPIO_PULL_SET_CONFIG(periph, gpio, pull)                             \
  (((periph == HAL_PWR_PULL_PERIPH_XSPI1)&&(IS_PWR_XSPI_GPIO_PULL_SET_CONFIG(gpio, pull))) \
   || ((periph == HAL_PWR_PULL_PERIPH_I3C1)&&(IS_PWR_I3C_GPIO_PULL_SET_CONFIG(gpio, pull))))

/*! Peripherals standby pull get config check macro */
#define IS_PWR_PERIPH_GPIO_PULL_GET_CONFIG(periph, gpio)                            \
  (((periph == HAL_PWR_PULL_PERIPH_XSPI1)&&((gpio >= HAL_PWR_XSPI1_PULL_PG10)    \
                                            &&(gpio <= HAL_PWR_XSPI1_PULL_PH0))) \
   ||((periph == HAL_PWR_PULL_PERIPH_I3C1)&&((gpio >= HAL_PWR_I3C1_PULL_PA15)    \
                                             &&(gpio <= HAL_PWR_I3C1_PULL_PI2))))
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group1 Power supply management functions
  * @{
  This section provides functions to manage power supply.
  - Call HAL_PWR_GetMainRegulatorSupply() to get the main regulator supply configuration.
  - Call HAL_PWR_GetMainRegulatorSupplyStatus() to get the main regulator supply status.
  - Call HAL_PWR_SetMainRegulatorVoltageScalingRange() to configure voltage scaling range.
  - Call HAL_PWR_GetMainRegulatorVoltageScalingRange() to get voltage scaling range configuration.
  - Call HAL_PWR_GetMainRegulatorActiveVoltageScalingRange() to get the active voltage scaling range.
  - Call HAL_PWR_LP_SetMainRegulatorStopVoltageScalingRange() to set the regulator voltage scaling
range during stop mode.
  - Call HAL_PWR_LP_GetMainRegulatorStopVoltageScalingRange() to get the regulator voltage scaling
range during stop mode.
  - Call HAL_PWR_SetAnalogIOSwitchSupply() to set the analog IO switch supply.
  - Call HAL_PWR_GetAnalogIOSwitchSupply() to get the analog IO switch supply.
  */

/**
  * @brief   Set the regulator voltage scaling range.
  * @param   range This parameter is an element of @ref hal_pwr_volt_scale_range_t enumeration.
  *          @arg @ref HAL_PWR_VOLT_SCALE_0
  *          @arg @ref HAL_PWR_VOLT_SCALE_1
  *          @arg @ref HAL_PWR_VOLT_SCALE_2
  * @warning After reset, the system starts from HSI with VOS1.
  * @warning To increase the frequency, first increase the VOS to a higher level (VOS0 > VOS1 > VOS2).
  * @warning To decrease the frequency, first decrease the system frequency, then set the VOS to a lower level.
  * @warning When ECC is disabled the following maximum frequency are allowed:
  * @warning When using the voltage scaling range 2, the system frequency can go up to 350 MHz.
  * @warning When using the voltage scaling range 1, the system frequency can go up to 435 MHz.
  * @warning When using the voltage scaling range 0, the system frequency can go up to 520 MHz.
  * @warning When ECC is enabled the following maximum frequency are allowed:
  * @warning When using the voltage scaling range 2, the system frequency can go up to 300 MHz.
  * @warning When using the voltage scaling range 1, the system frequency can go up to 370 MHz.
  * @warning When using the voltage scaling range 0, the system frequency can go up to 465 MHz.
  * @warning When bypassing the internal regulator, we must ensure that SRAM operation speed has correctly adjusted.
  * @retval  HAL_ERROR Bypass enabled or VOS setting timeout.
  * @retval  HAL_OK    Regulator voltage scaling range has been correctly configured.
  */
hal_status_t HAL_PWR_SetMainRegulatorVoltageScalingRange(hal_pwr_volt_scale_range_t range)
{
  uint32_t timeout = ((PWR_VOS_SELECT_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
  uint32_t vos = 0U;
  uint32_t actvos = 0U;

  ASSERT_DBG_PARAM(IS_PWR_VOLT_SCALE_RANGE(range));

  LL_PWR_SetRegulatorVoltageScaling((uint32_t)range);

  /* Check if the internal regulator is bypassed */
  if (LL_PWR_IsEnabledBypass() == LL_PWR_MAIN_REGU_SUPPLY_NOT_BYPASSED)
  {
    /* Polling on vos and actvos flags */
    do
    {
      vos = LL_PWR_IsActiveFlag_VOS();
      actvos = LL_PWR_IsActiveFlag_ACTVOS();
      timeout--;
    } while (((vos == 0U) || (actvos == 0U)) && (timeout != 0U));
  }
  else
  {
    /* In bypass, voltage scaling cannot be set */
    return HAL_ERROR;
  }

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Get the regulator voltage scaling range.
  * @retval Returned value is an element of @ref hal_pwr_volt_scale_range_t enumeration.
  *         @arg @ref HAL_PWR_VOLT_SCALE_0
  *         @arg @ref HAL_PWR_VOLT_SCALE_1
  *         @arg @ref HAL_PWR_VOLT_SCALE_2
  */
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorVoltageScalingRange(void)
{
  return ((hal_pwr_volt_scale_range_t)LL_PWR_GetRegulatorVoltageScaling());
}

/**
  * @brief  Get the active regulator voltage scaling range.
  * @retval Returned value is an element of @ref hal_pwr_volt_scale_range_t enumeration.
  *         @arg @ref HAL_PWR_VOLT_SCALE_0
  *         @arg @ref HAL_PWR_VOLT_SCALE_1
  *         @arg @ref HAL_PWR_VOLT_SCALE_2
  */
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorActiveVoltageScalingRange(void)
{
  return (hal_pwr_volt_scale_range_t)LL_PWR_GetActiveRegulatorVoltageScaling();
}

/**
  * @brief   Set the regulator voltage scaling range during stop mode.
  * @param   range     This parameter is an element of @ref hal_pwr_stop_volt_scale_range_t enumeration.
  *          @arg @ref HAL_PWR_STOP_VOLT_SCALE_LOW
  *          @arg @ref HAL_PWR_STOP_VOLT_SCALE_HIGH
  * @warning By default the system stop mode regulator voltage scale is HAL_PWR_STOP_VOLT_SCALE_HIGH.
  * @warning HAL_PWR_STOP_VOLT_SCALE_LOW lowest power consumption in stop but add some latency in exit from stop mode.
  * @warning HAL_PWR_STOP_VOLT_SCALE_HIGH lowest latency in exit from stop mode but higher consumption
  */
void HAL_PWR_LP_SetMainRegulatorStopVoltageScalingRange(hal_pwr_stop_volt_scale_range_t range)
{
  ASSERT_DBG_PARAM(IS_PWR_STOP_VOLT_SCALE_RANGE(range));

  LL_PWR_SetStopRegulatorVoltageScaling((uint32_t)range);
}

/**
  * @brief  Get the stop regulator voltage scaling range.
  * @retval Returned value is an element of @ref hal_pwr_stop_volt_scale_range_t enumeration.
  *         @arg @ref HAL_PWR_STOP_VOLT_SCALE_LOW
  *         @arg @ref HAL_PWR_STOP_VOLT_SCALE_HIGH
  */
hal_pwr_stop_volt_scale_range_t HAL_PWR_LP_GetMainRegulatorStopVoltageScalingRange(void)
{
  return (hal_pwr_stop_volt_scale_range_t)LL_PWR_GetStopRegulatorVoltageScaling();
}

/**
  * @brief  Get the system supply regulator configuration.
  * @retval Returned value is an element of @ref hal_pwr_main_regulator_supply_t enumeration.
  *         @arg @ref HAL_PWR_MAIN_REGULATOR_SUPPLY_NOT_BYPASS
  *         @arg @ref HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASS
  */
hal_pwr_main_regulator_supply_t HAL_PWR_GetMainRegulatorSupply(void)
{
  hal_pwr_main_regulator_supply_t regulator;

  /* Check if the internal regulators are bypassed */
  if (LL_PWR_IsEnabledBypass() == LL_PWR_MAIN_REGU_SUPPLY_BYPASSED)
  {
    regulator = HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASS;
  }
  else
  {
    regulator = HAL_PWR_MAIN_REGULATOR_SUPPLY_NOT_BYPASS;
  }

  return regulator;
}

/**
  * @brief  Get the system supply regulator status.
  * @retval Returned value is an element of @ref hal_pwr_main_regulator_supply_status_t enumeration.
  *         @arg @ref HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASSED
  *         @arg @ref HAL_PWR_MAIN_REGULATOR_SUPPLY_SMPS
  *         @arg @ref HAL_PWR_MAIN_REGULATOR_SUPPLY_LDO
  */
hal_pwr_main_regulator_supply_status_t HAL_PWR_GetMainRegulatorSupplyStatus(void)
{
  hal_pwr_main_regulator_supply_status_t regulator;

  /* Check if the internal regulators are bypassed */
  if (LL_PWR_IsEnabledBypass() == LL_PWR_MAIN_REGU_SUPPLY_BYPASSED)
  {
    regulator = HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASSED;
  }
  else
  {
    /* Check if the SMPS is enabled, otherwise return LDO */
    if (LL_PWR_IsEnabledSMPSSupply() == 1UL)
    {
      regulator = HAL_PWR_MAIN_REGULATOR_SUPPLY_SMPS;
    }
    else
    {
      regulator = HAL_PWR_MAIN_REGULATOR_SUPPLY_LDO;
    }
  }

  return regulator;
}

/**
  * @brief Set the analog IO switch supply.
  * @param analog_io_switch_supply This parameter is an element of @ref hal_pwr_analog_io_switch_supply_t enumeration.
  *        @arg @ref HAL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY
  *        @arg @ref HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY
  * @note  The correct analog supply level is indicated by the AVD output after enabling the AVD and selecting the
  *        supply level to be monitored.
  * @note  The booster guarantees the analog switch AC performance when the VDD supply voltage is below 2.7 V
  *        (reduction of the total harmonic distortion to have the same switch performance over the full supply
  *        voltage range).
  */
void HAL_PWR_SetAnalogIOSwitchSupply(hal_pwr_analog_io_switch_supply_t analog_io_switch_supply)
{
  ASSERT_DBG_PARAM(IS_PWR_ANALOG_IO_SWITCH_SUPPLY(analog_io_switch_supply));

  /* If the selected supply is the Booster supply, check the state of Analog Voltage supply */
  if (analog_io_switch_supply == HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY)
  {
    /* If Analog Voltage is not ready, enable it */
    if (LL_PWR_IsEnabledAnalogVoltageReady() == 0UL)
    {
      LL_PWR_EnableAnalogVoltageReady();
    }

    /* Enable Analog Booster */
    LL_PWR_EnableAnalogBooster();
  }
  else
  {
    /* Disable Analog Booster */
    LL_PWR_DisableAnalogBooster();
  }
}

/**
  * @brief  Get the analog IO switch supply.
  * @retval Returned value is an element of @ref hal_pwr_analog_io_switch_supply_t enumeration.
  *         @arg @ref HAL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY
  *         @arg @ref HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY
  */
hal_pwr_analog_io_switch_supply_t HAL_PWR_GetAnalogIOSwitchSupply(void)
{
  uint32_t booster_enabled = LL_PWR_IsEnabledAnalogBooster();
  uint32_t voltage_ready = LL_PWR_IsEnabledAnalogVoltageReady();

  /* Check if both booster and analog voltage are enabled */
  if ((booster_enabled == 1U) && (voltage_ready == 1U))
  {
    return HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY;
  }
  else
  {
    return HAL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY;
  }
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group2 Low power mode management functions
  * @{
  This section provides functions to manage low power modes:
  - Call HAL_PWR_ClearCorePendingEvent() to clear the internal cortex event before entering low power mode.
  - Call HAL_PWR_EnterSleepMode() to enter the Core in sleep mode.
  - Call HAL_PWR_EnterStopMode() to enter the MCU in Stop mode.
  - Call HAL_PWR_EnterStandbyMode() to enter the MCU in standby mode.
  - Call HAL_PWR_SetCoreSleepMode() to configure the Core in sleep or deep sleep mode.
  - Call HAL_PWR_GetCoreSleepMode() to get Core sleep mode configuration.
  - Call HAL_PWR_EnableCoreSleepOnExit() to enable Core to re-enter sleep mode after an interrupt is handled.
  - Call HAL_PWR_DisableCoreSleepOnExit() to disable Core to re-enter sleep mode after an interrupt is handled.
  - Call HAL_PWR_IsEnabledCoreSleepOnExit() to check Core to re-enter in sleep mode after an interrupt status.
  - Call HAL_PWR_EnableCoreSendEventOnPending()  to enable Core to wake up after any pending event/interrupt.
  - Call HAL_PWR_DisableCoreSendEventOnPending() to disable Core to wake up after any pending event/interrupt.
  - Call HAL_PWR_IsEnabledCoreSendEventOnPending() to check that core send event on pending is enabled.
  - Call HAL_PWR_GetPreviousSystemPowerMode() to get the system previous power mode.
  - Call HAL_PWR_CleanPreviousSystemPowerMode() to clean the system previous power mode.
  - Call HAL_PWR_WakeupPin_IRQHandler() to handle the PWR wake-up from low power interrupt request.
  - Call HAL_PWR_WakeupPinCallback() to wake-up from low power interrupt. This function must be redefined
    within the application for the wake-up callback.
  */

/**
  * @brief   Clear core pending event.
  * @note    This API clears the pending event in order to enter a given core to Sleep or Stop mode with WFE entry.
  * @warning Call this function just before APIs that enter Sleep and Stop modes using a Wait For Event request.
  */
void HAL_PWR_ClearCorePendingEvent(void)
{
  /* ARMV7m specificity: Use DSB to ensure outstanding memory transactions complete before calling WFE/WFI. */
  __DSB();
  __ISB();
  __SEV();
  __WFE();
}

/**
  * @brief Enter the core in Sleep mode.
  * @param sleep_entry Parameter to @ref hal_pwr_low_pwr_mode_entry_t enumeration.
  *        @arg @ref HAL_PWR_LOW_PWR_MODE_WFE
  *        @arg @ref HAL_PWR_LOW_PWR_MODE_WFI
  */
void HAL_PWR_EnterSleepMode(hal_pwr_low_pwr_mode_entry_t sleep_entry)
{
  ASSERT_DBG_PARAM(IS_PWR_LP_MODE_ENTRY(sleep_entry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  SCB_DisableDeepSleep();

  /* ARMV7m specificity: Use DSB to ensure outstanding memory transactions complete before entering sleep mode. */
  __DSB();
  __ISB();

  if (sleep_entry == HAL_PWR_LOW_PWR_MODE_WFE)
  {
    /* Wait For Event Request */
    __WFE();
  }
  else
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
}

/**
  * @brief Enter the MCU in Stop mode.
  * @param stop_entry This parameter is an element of @ref hal_pwr_low_pwr_mode_entry_t enumeration.
  *        @arg @ref HAL_PWR_LOW_PWR_MODE_WFE
  *        @arg @ref HAL_PWR_LOW_PWR_MODE_WFI
  * @param stop_mode  This parameter is an element of @ref hal_pwr_stop_mode_t enumeration.
  *        @arg @ref HAL_PWR_STOP_MODE
  */
void HAL_PWR_EnterStopMode(hal_pwr_low_pwr_mode_entry_t stop_entry, hal_pwr_stop_mode_t stop_mode)
{
  ASSERT_DBG_PARAM(IS_PWR_LP_MODE_ENTRY(stop_entry));
  ASSERT_DBG_PARAM(IS_PWR_STOP_MODE(stop_mode));

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB_EnableDeepSleep();

  LL_PWR_SetPowerMode((uint32_t)stop_mode);

  /* ARMV7m specificity: Use DSB to ensure outstanding memory transactions complete before entering stop mode. */
  __DSB();
  __ISB();

  if (stop_entry == HAL_PWR_LOW_PWR_MODE_WFE)
  {
    /* Wait For Event Request */
    __WFE();
  }
  else
  {
    /* Wait For Interrupt Request */
    __WFI();
  }

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  SCB_DisableDeepSleep();
}

/**
  * @brief   Enter the MCU in Standby mode.
  * @warning The Standby mode must not be used if VCORE is provided from an external supply.
  */
void HAL_PWR_EnterStandbyMode(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB_EnableDeepSleep();

  LL_PWR_SetPowerMode(LL_PWR_STANDBY_MODE);

  /* ARMV7m specificity: Use DSB to ensure outstanding memory transactions complete before entering standby mode. */
  __DSB();
  __ISB();

  /* Wait For Interrupt Request */
  __WFI();
}

/**
  * @brief Set the core sleep mode configuration.
  * @param sleep_mode This parameter is an element of @ref hal_pwr_core_sleep_mode_t enumeration.
  *        @arg @ref HAL_PWR_CORE_SLEEP
  *        @arg @ref HAL_PWR_CORE_DEEP_SLEEP
  */
void HAL_PWR_SetCoreSleepMode(hal_pwr_core_sleep_mode_t sleep_mode)
{
  ASSERT_DBG_PARAM(IS_PWR_CORE_SLEEP_MODE(sleep_mode));

  if (sleep_mode == HAL_PWR_CORE_DEEP_SLEEP)
  {
    SCB_EnableDeepSleep();
  }
  else
  {
    SCB_DisableDeepSleep();
  }
}

/**
  * @brief  Get the core sleep mode configuration.
  * @retval Returned value is an element of @ref hal_pwr_core_sleep_mode_t enumeration.
  *         @arg @ref HAL_PWR_CORE_SLEEP
  *         @arg @ref HAL_PWR_CORE_DEEP_SLEEP
  */
hal_pwr_core_sleep_mode_t HAL_PWR_GetCoreSleepMode(void)
{
  return ((hal_pwr_core_sleep_mode_t)(SCB_IsEnabledDeepSleep()));
}

/**
  * @brief Enable sleep-on-exit feature when returning from handler mode to thread mode.
  */
void HAL_PWR_EnableCoreSleepOnExit(void)
{
  SCB_EnableSleepOnExit();
}

/**
  * @brief Disable sleep-on-exit feature when returning from handler mode to thread mode.
  */
void HAL_PWR_DisableCoreSleepOnExit(void)
{
  SCB_DisableSleepOnExit();
}

/**
  * @brief  Check if the core sleep-on-exit is enabled.
  * @retval Returned value is an element of @ref hal_pwr_core_sleep_on_exit_status_t enumeration.
  *         @arg @ref HAL_PWR_CORE_SLEEP_ON_EXIT_DISABLED
  *         @arg @ref HAL_PWR_CORE_SLEEP_ON_EXIT_ENABLED
  */
hal_pwr_core_sleep_on_exit_status_t HAL_PWR_IsEnabledCoreSleepOnExit(void)
{
  return ((hal_pwr_core_sleep_on_exit_status_t)(SCB_IsEnabledSleepOnExit()));
}

/**
  * @brief Enable core Send Event On Pending.
  */
void HAL_PWR_EnableCoreSendEventOnPending(void)
{
  SCB_EnableEventOnPend();
}

/**
  * @brief Disable core Send Event On Pending.
  */
void HAL_PWR_DisableCoreSendEventOnPending(void)
{
  SCB_DisableEventOnPend();
}

/**
  * @brief  Get core Send Event On Pending.
  * @retval Returned value is an element of @ref hal_pwr_core_sev_on_pending_status_t enumeration.
  *         @arg @ref HAL_PWR_CORE_SEV_ON_PENDING_DISABLED
  *         @arg @ref HAL_PWR_CORE_SEV_ON_PENDING_ENABLED
  */
hal_pwr_core_sev_on_pending_status_t HAL_PWR_IsEnabledCoreSendEventOnPending(void)
{
  return ((hal_pwr_core_sev_on_pending_status_t)(SCB_IsEnabledEventOnPend()));
}

/**
  * @brief   Get the previous system power mode.
  * @retval  Returned value is an element of @ref hal_pwr_system_mode_t enumeration.
  *          @arg @ref HAL_PWR_SYSTEM_RUN_MODE
  *          @arg @ref HAL_PWR_SYSTEM_STOP_MODE
  *          @arg @ref HAL_PWR_SYSTEM_STANDBY_MODE
  * @note    Sleep mode is an ARM core mode and not a system power mode as it does not affect system clock on return
  *          from sleep, so it is not reported by this function.
  * @warning This function is expected to be called on return from low power mode so to take the necessary actions
  *          such as re-enabling clocks automatically disabled during low power mode.
  */
hal_pwr_system_mode_t HAL_PWR_GetPreviousSystemPowerMode(void)
{
  hal_pwr_system_mode_t previous_mode = HAL_PWR_SYSTEM_RUN_MODE;

  /* Check Standby flag */
  if (LL_PWR_IsActiveFlag_SB() != 0U)
  {
    previous_mode = HAL_PWR_SYSTEM_STANDBY_MODE;
  }
  else
  {
    /* Check Stop flag */
    if (LL_PWR_IsActiveFlag_STOP() != 0U)
    {
      previous_mode = HAL_PWR_SYSTEM_STOP_MODE;
    }
  }

  return previous_mode;
}

/**
  * @brief   Clean the previous system power mode flags.
  * @note    This function must be called before entering in low power mode to ensure that
  *          HAL_PWR_GetPreviousSystemPowerMode() will return the right information on return from low power mode.
  * @warning This function clears both standby and stop flags.
  */
void HAL_PWR_CleanPreviousSystemPowerMode(void)
{
  LL_PWR_ClearFlag_SB();
}

/**
  * @brief Handle the PWR wake-up pin interrupt request.
  * @param wakeup_pin This parameter can be one or a combination of @ref PWR_wakeup_pin values:
  *        @arg @ref HAL_PWR_WAKEUP_PIN_1
  *        @arg @ref HAL_PWR_WAKEUP_PIN_2
  *        @arg @ref HAL_PWR_WAKEUP_PIN_3
  *        @arg @ref HAL_PWR_WAKEUP_PIN_4
  *        @arg @ref HAL_PWR_WAKEUP_PIN_5
  *        @arg @ref HAL_PWR_WAKEUP_PIN_6
  *        @arg @ref HAL_PWR_WAKEUP_PIN_7
  *        @arg @ref HAL_PWR_WAKEUP_PIN_8
  *        @arg @ref HAL_PWR_WAKEUP_PIN_ALL
  */
void HAL_PWR_WakeupPin_IRQHandler(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  uint32_t wakeup_active = LL_PWR_READ_REG(WKUPFR);
  uint32_t wakeup_source = LL_PWR_READ_REG(WKUPEPR) & wakeup_active;
  wakeup_source &= wakeup_pin;

  /* Check wake-up pin */
  if (wakeup_source != 0U)
  {
    /* Clear wake-up pin flag */
    LL_PWR_ClearFlag_WU(wakeup_source);

    HAL_PWR_WakeupPinCallback(wakeup_source);
  }
}

/**
  * @brief PWR wake-up pin interrupt request callback.
  * @param wakeup_pin This parameter can be one or a combination of @ref PWR_wakeup_pin values:
  *        @arg @ref HAL_PWR_WAKEUP_PIN_1
  *        @arg @ref HAL_PWR_WAKEUP_PIN_2
  *        @arg @ref HAL_PWR_WAKEUP_PIN_3
  *        @arg @ref HAL_PWR_WAKEUP_PIN_4
  *        @arg @ref HAL_PWR_WAKEUP_PIN_5
  *        @arg @ref HAL_PWR_WAKEUP_PIN_6
  *        @arg @ref HAL_PWR_WAKEUP_PIN_7
  *        @arg @ref HAL_PWR_WAKEUP_PIN_8
  *        @arg @ref HAL_PWR_WAKEUP_PIN_ALL
  */
__WEAK void HAL_PWR_WakeupPinCallback(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(wakeup_pin);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed, the
                      HAL_PWR_WakeupPinCallback() could be implemented in the user application */
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group3 Wake-up pins management functions
  * @{
  This section provides functions to configure the wake-up pins:
  - Call HAL_PWR_LP_SetConfigWakeupPin() to configure wake-up pin.
  - Call HAL_PWR_LP_GetConfigWakeupPin() to get wake-up pin configuration.
  - Call HAL_PWR_LP_EnableWakeupPin() to enable wake-up pin.
  - Call HAL_PWR_LP_DisableWakeupPin() to disable wake-up pin.
  - Call HAL_PWR_LP_IsEnabledWakeupPin() to check that wake-up pin is enabled.
  - Call HAL_PWR_LP_GetWakeupSource() to get the wake-up sources.
  - Call HAL_PWR_LP_CleanWakeupSource() to clean the wake-up sources.
  */

/**
  * @brief  Set wake-up pin configuration.
  * @param  wakeup_pin This parameter can be one or a combination of @ref PWR_wakeup_pin.
  *         @arg @ref HAL_PWR_WAKEUP_PIN_1
  *         @arg @ref HAL_PWR_WAKEUP_PIN_2
  *         @arg @ref HAL_PWR_WAKEUP_PIN_3
  *         @arg @ref HAL_PWR_WAKEUP_PIN_4
  *         @arg @ref HAL_PWR_WAKEUP_PIN_5
  *         @arg @ref HAL_PWR_WAKEUP_PIN_6
  *         @arg @ref HAL_PWR_WAKEUP_PIN_7
  *         @arg @ref HAL_PWR_WAKEUP_PIN_8
  *         @arg @ref HAL_PWR_WAKEUP_PIN_ALL
  * @param  p_config          Pointer to a @ref hal_pwr_wakeup_pin_config_t structure.
  * @retval HAL_INVALID_PARAM p_config pointer is NULL.
  * @retval HAL_OK            Wake-up pin has been correctly configured.
  */
hal_status_t HAL_PWR_LP_SetConfigWakeupPin(uint32_t wakeup_pin, const hal_pwr_wakeup_pin_config_t *p_config)
{
  uint32_t temp_pin = wakeup_pin;
  __IO uint32_t register_value = LL_PWR_READ_REG(WKUPEPR);
  uint32_t position;
  uint32_t current_pin;

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));
  ASSERT_DBG_PARAM(IS_PWR_WAKEUP_PIN_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_PWR_WAKEUP_PIN_PULL(p_config->pull));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get wake-up pin information */
  position    = STM32_POSITION_VAL(temp_pin);
  current_pin = 1UL << position;

  while (temp_pin != 0U)
  {
    /* Mask values which will be modified */
    register_value &= ~(uint32_t)((LL_PWR_WAKEUP_PIN_POLARITY_REF << position) \
                                  + (LL_PWR_WAKEUP_PIN_PULL_REF << (position * LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET)));

    /* Compute new value */
    register_value |= (uint32_t)(((uint32_t)(p_config->polarity) << (LL_PWR_WAKEUP_PIN_POLARITY_REF_POS + position)) \
                                 + ((uint32_t)(p_config->pull) << (LL_PWR_WAKEUP_PIN_PULL_REF_POS \
                                                                   + (position \
                                                                      * LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET))));

    /* Update wake-up pin information */
    temp_pin    &= (~current_pin);
    position    = STM32_POSITION_VAL(temp_pin);
    current_pin = (uint32_t)(1UL << position);
  }

  /* Set new value in one register access */
  LL_PWR_WRITE_REG(WKUPEPR, register_value);

  return HAL_OK;
}

/**
  * @brief Get wake-up pin configuration.
  * @param wakeup_pin This parameter can be one of @ref PWR_wakeup_pin.
  *        @arg @ref HAL_PWR_WAKEUP_PIN_1
  *        @arg @ref HAL_PWR_WAKEUP_PIN_2
  *        @arg @ref HAL_PWR_WAKEUP_PIN_3
  *        @arg @ref HAL_PWR_WAKEUP_PIN_4
  *        @arg @ref HAL_PWR_WAKEUP_PIN_5
  *        @arg @ref HAL_PWR_WAKEUP_PIN_6
  *        @arg @ref HAL_PWR_WAKEUP_PIN_7
  *        @arg @ref HAL_PWR_WAKEUP_PIN_8
  * @param p_config  Pointer to a @ref hal_pwr_wakeup_pin_config_t structure.
  */
void HAL_PWR_LP_GetConfigWakeupPin(uint32_t wakeup_pin, hal_pwr_wakeup_pin_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_PWR_GET_WAKEUP_PIN(wakeup_pin));

  p_config->polarity = (hal_pwr_wakeup_pin_polarity_t)LL_PWR_GetWakeUpPinPolarity(wakeup_pin);
  p_config->pull     = (hal_pwr_wakeup_pin_pull_t)LL_PWR_GetWakeUpPinPull(wakeup_pin);
}

/**
  * @brief Enable the wake-up pin configuration.
  * @param wakeup_pin This parameter can be one or a combination of @ref PWR_wakeup_pin.
  *        @arg @ref HAL_PWR_WAKEUP_PIN_1
  *        @arg @ref HAL_PWR_WAKEUP_PIN_2
  *        @arg @ref HAL_PWR_WAKEUP_PIN_3
  *        @arg @ref HAL_PWR_WAKEUP_PIN_4
  *        @arg @ref HAL_PWR_WAKEUP_PIN_5
  *        @arg @ref HAL_PWR_WAKEUP_PIN_6
  *        @arg @ref HAL_PWR_WAKEUP_PIN_7
  *        @arg @ref HAL_PWR_WAKEUP_PIN_8
  *        @arg @ref HAL_PWR_WAKEUP_PIN_ALL
  * @note  Wake-up pins are used to wake up the system from Standby mode.
  */
void HAL_PWR_LP_EnableWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  LL_PWR_EnableWakeUpPin(wakeup_pin);
}

/**
  * @brief Disable the wake-up pin configuration.
  * @param wakeup_pin This parameter can be one or a combination of @ref PWR_wakeup_pin.
  *        @arg @ref HAL_PWR_WAKEUP_PIN_1
  *        @arg @ref HAL_PWR_WAKEUP_PIN_2
  *        @arg @ref HAL_PWR_WAKEUP_PIN_3
  *        @arg @ref HAL_PWR_WAKEUP_PIN_4
  *        @arg @ref HAL_PWR_WAKEUP_PIN_5
  *        @arg @ref HAL_PWR_WAKEUP_PIN_6
  *        @arg @ref HAL_PWR_WAKEUP_PIN_7
  *        @arg @ref HAL_PWR_WAKEUP_PIN_8
  *        @arg @ref HAL_PWR_WAKEUP_PIN_ALL
  * @note  Wake-up pins are used to wake up the system from Standby mode.
  */
void HAL_PWR_LP_DisableWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  LL_PWR_DisableWakeUpPin(wakeup_pin);
}

/**
  * @brief  Check that wake-up pin is enabled.
  * @param  wakeup_pin This parameter can be one of @ref PWR_wakeup_pin.
  *         @arg @ref HAL_PWR_WAKEUP_PIN_1
  *         @arg @ref HAL_PWR_WAKEUP_PIN_2
  *         @arg @ref HAL_PWR_WAKEUP_PIN_3
  *         @arg @ref HAL_PWR_WAKEUP_PIN_4
  *         @arg @ref HAL_PWR_WAKEUP_PIN_5
  *         @arg @ref HAL_PWR_WAKEUP_PIN_6
  *         @arg @ref HAL_PWR_WAKEUP_PIN_7
  *         @arg @ref HAL_PWR_WAKEUP_PIN_8
  * @retval Returned value is an element of @ref hal_pwr_wakeup_pin_status_t enumeration.
  *         @arg @ref HAL_PWR_WAKEUP_PIN_DISABLED
  *         @arg @ref HAL_PWR_WAKEUP_PIN_ENABLED
  */
hal_pwr_wakeup_pin_status_t HAL_PWR_LP_IsEnabledWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_GET_WAKEUP_PIN(wakeup_pin));

  return ((hal_pwr_wakeup_pin_status_t)LL_PWR_IsEnabledWakeUpPin(wakeup_pin));
}

/**
  * @brief  Return the wake-up sources.
  * @retval Can be one of or a combination of @ref PWR_wakeup_source.
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_1
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_2
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_3
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_4
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_5
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_6
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_7
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_8
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_ALL
  * @warning This API returns the wake-up source flags which can be a combination of multiple sources.
  */
uint32_t HAL_PWR_LP_GetWakeupSource(void)
{
  return (LL_PWR_READ_REG(WKUPFR));
}

/**
  * @brief Clean the selected wake-up source(s) flag(s).
  * @param wakeup_source This parameter can be one or a combination of @ref PWR_wakeup_source.
  *        @arg @ref HAL_PWR_WAKEUP_SOURCE_1
  *        @arg @ref HAL_PWR_WAKEUP_SOURCE_2
  *        @arg @ref HAL_PWR_WAKEUP_SOURCE_3
  *        @arg @ref HAL_PWR_WAKEUP_SOURCE_4
  *        @arg @ref HAL_PWR_WAKEUP_SOURCE_5
  *        @arg @ref HAL_PWR_WAKEUP_SOURCE_6
  *        @arg @ref HAL_PWR_WAKEUP_SOURCE_7
  *        @arg @ref HAL_PWR_WAKEUP_SOURCE_8
  *        @arg @ref HAL_PWR_WAKEUP_SOURCE_ALL
  */
void HAL_PWR_LP_CleanWakeupSource(uint32_t wakeup_source)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_SOURCE(wakeup_source));

  LL_PWR_ClearFlag_WU(wakeup_source);
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group4 RTC domain write protection management functions
  * @{
  This section provides functions to manage RTC domain access:
  - Call HAL_PWR_EnableRTCDomainWriteProtection() to enable RTC domain write protection.
  - Call HAL_PWR_DisableRTCDomainWriteProtection() to disable RTC domain write protection.
  - Call HAL_PWR_IsEnabledRTCDomainWriteProtection() to check that RTC domain write protection is enabled.
  */

/**
  * @brief Enable the RTC domain write protection (RCC RTC domain control register RCC_RTCCR, RTC registers,
  *        TAMP registers, backup registers and backup SRAM).
  */
void HAL_PWR_EnableRTCDomainWriteProtection(void)
{
  LL_PWR_EnableBackupDomainWriteProtection();
}

/**
  * @brief Disable the RTC domain write protection (RCC RTC domain control register RCC_RTCCR, RTC registers,
  *        TAMP registers, backup registers and backup SRAM).
  * @note  After a system reset, the RTC domain is protected against possible unwanted write accesses.
  */
void HAL_PWR_DisableRTCDomainWriteProtection(void)
{
  LL_PWR_DisableBackupDomainWriteProtection();
}

/**
  * @brief  Check that RTC domain access is enabled.
  * @retval Returned value is an element of @ref hal_pwr_rtc_domain_wrp_status_t enumeration.
  *         @arg @ref HAL_PWR_RTC_DOMAIN_WRP_DISABLED
  *         @arg @ref HAL_PWR_RTC_DOMAIN_WRP_ENABLED
  */
hal_pwr_rtc_domain_wrp_status_t HAL_PWR_IsEnabledRTCDomainWriteProtection(void)
{
  return ((hal_pwr_rtc_domain_wrp_status_t)LL_PWR_IsEnabledBackupDomainWriteProtection());
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group5 Voltage monitoring management functions
  * @{
  This section provides functions to configure voltage monitoring.
  - Call HAL_PWR_SetProgrammableVoltageDetectorLevel() to configure the programmable voltage detector.
  - Call HAL_PWR_GetProgrammableVoltageDetectorLevel() to get the programmable voltage detector configuration.
  - Call HAL_PWR_EnableProgrammableVoltageDetector() to enable the Programmable Voltage Detector.
  - Call HAL_PWR_DisableProgrammableVoltageDetector() to disable the Programmable Voltage Detector.
  - Call HAL_PWR_IsEnabledProgrammableVoltageDetector() to check the Programmable Voltage Detector status.
  - Call HAL_PWR_GetProgrammableVoltageDetectorOutput() to get the programmable voltage detector output.
  - Call HAL_PWR_SetAnalogVoltageDetectorLevel() to configure the analog voltage detector.
  - Call HAL_PWR_GetAnalogVoltageDetectorLevel() to get the analog voltage detector configuration.
  - Call HAL_PWR_EnableAnalogVoltageDetector() to enable the Analog Voltage Detector.
  - Call HAL_PWR_DisableAnalogVoltageDetector() to disable the Analog Voltage Detector.
  - Call HAL_PWR_IsEnabledAnalogVoltageDetector() to check the Analog Voltage Detector status
  - Call HAL_PWR_GetAnalogVoltageDetectorOutput() to get the analog voltage detector output.
  - Call HAL_PWR_EnableTemperatureVbatMonitor() to enable the temperature and VBAT monitor.
  - Call HAL_PWR_DisableTemperatureVbatMonitor() to disable the temperature and VBAT monitor.
  - Call HAL_PWR_IsEnabledTemperatureVbatMonitor() to check the temperature and VBAT monitor status.
  - Call HAL_PWR_GetTemperatureLevelStatus() to get the temperature level status.
  - Call HAL_PWR_GetVbatVoltageLevelStatus() to get the VBAT level status.
  */

/**
  * @brief Set the voltage threshold detection by the Programmable Voltage Detector (PVD).
  * @param level This parameter is an element of @ref hal_pwr_pvd_level_t enumeration.
  *        @arg @ref HAL_PWR_PVD_VDD_LEVEL_1
  *        @arg @ref HAL_PWR_PVD_VDD_LEVEL_2
  *        @arg @ref HAL_PWR_PVD_VDD_LEVEL_3
  *        @arg @ref HAL_PWR_PVD_VDD_LEVEL_4
  *        @arg @ref HAL_PWR_PVD_VDD_LEVEL_5
  *        @arg @ref HAL_PWR_PVD_VDD_LEVEL_6
  *        @arg @ref HAL_PWR_PVD_VDD_LEVEL_7
  *        @arg @ref HAL_PWR_PVD_PVDIN_VREFINT
  */
void HAL_PWR_SetProgrammableVoltageDetectorLevel(hal_pwr_pvd_level_t level)
{
  ASSERT_DBG_PARAM(IS_PWR_PVD_LEVEL(level));

  LL_PWR_SetPVDLevel((uint32_t)level);
}

/**
  * @brief  Get the voltage threshold detection by the Programmable Voltage Detector (PVD).
  * @retval Returned value is an element of @ref hal_pwr_pvd_level_t enumeration.
  *         @arg @ref HAL_PWR_PVD_VDD_LEVEL_1
  *         @arg @ref HAL_PWR_PVD_VDD_LEVEL_2
  *         @arg @ref HAL_PWR_PVD_VDD_LEVEL_3
  *         @arg @ref HAL_PWR_PVD_VDD_LEVEL_4
  *         @arg @ref HAL_PWR_PVD_VDD_LEVEL_5
  *         @arg @ref HAL_PWR_PVD_VDD_LEVEL_6
  *         @arg @ref HAL_PWR_PVD_VDD_LEVEL_7
  *         @arg @ref HAL_PWR_PVD_PVDIN_VREFINT
  */
hal_pwr_pvd_level_t HAL_PWR_GetProgrammableVoltageDetectorLevel(void)
{
  return ((hal_pwr_pvd_level_t)LL_PWR_GetPVDLevel());
}

/**
  * @brief Enable the voltage threshold detection by the Programmable Voltage Detector (PVD).
  */
void HAL_PWR_EnableProgrammableVoltageDetector(void)
{
  LL_PWR_EnablePVD();
}

/**
  * @brief Disable the voltage threshold detection by the Programmable Voltage Detector (PVD).
  */
void HAL_PWR_DisableProgrammableVoltageDetector(void)
{
  LL_PWR_DisablePVD();
}

/**
  * @brief  Check if the programmable voltage detection is enabled.
  * @retval Returned value is an element of @ref hal_pwr_pvd_status_t enumeration.
  *         @arg @ref HAL_PWR_PVD_DISABLED
  *         @arg @ref HAL_PWR_PVD_ENABLED
  */
hal_pwr_pvd_status_t HAL_PWR_IsEnabledProgrammableVoltageDetector(void)
{
  return ((hal_pwr_pvd_status_t)LL_PWR_IsEnabledPVD());
}

/**
  * @brief  Provide the current PVD output.
  * @retval Returned value is an element of @ref hal_pwr_pvd_out_t enumeration
  *         @arg @ref HAL_PWR_PVD_OUT_EQ_HIGH_THR
  *         @arg @ref HAL_PWR_PVD_OUT_LOW_THR
  */
hal_pwr_pvd_out_t HAL_PWR_GetProgrammableVoltageDetectorOutput(void)
{
  return (hal_pwr_pvd_out_t)LL_PWR_IsActiveFlag_PVDO();
}

/**
  * @brief Set the voltage threshold detection by the Analog Voltage Detector (AVD).
  * @param level This parameter is an element of @ref hal_pwr_avd_level_t enumeration.
  *        @arg @ref HAL_PWR_AVD_VDDA_LEVEL_1
  *        @arg @ref HAL_PWR_AVD_VDDA_LEVEL_2
  *        @arg @ref HAL_PWR_AVD_VDDA_LEVEL_3
  *        @arg @ref HAL_PWR_AVD_VDDA_LEVEL_4
  */
void HAL_PWR_SetAnalogVoltageDetectorLevel(hal_pwr_avd_level_t level)
{
  ASSERT_DBG_PARAM(IS_PWR_AVD_LEVEL(level));

  LL_PWR_SetAVDLevel((uint32_t)level);
}

/**
  * @brief  Get the voltage threshold detection by the Analog Voltage Detector (AVD).
  * @retval Returned value is an element of @ref hal_pwr_avd_level_t enumeration.
  *         @arg @ref HAL_PWR_AVD_VDDA_LEVEL_1
  *         @arg @ref HAL_PWR_AVD_VDDA_LEVEL_2
  *         @arg @ref HAL_PWR_AVD_VDDA_LEVEL_3
  *         @arg @ref HAL_PWR_AVD_VDDA_LEVEL_4
  */
hal_pwr_avd_level_t HAL_PWR_GetAnalogVoltageDetectorLevel(void)
{
  return ((hal_pwr_avd_level_t)LL_PWR_GetAVDLevel());
}

/**
  * @brief Enable the voltage threshold detection by the Analog Voltage Detector (AVD).
  */
void HAL_PWR_EnableAnalogVoltageDetector(void)
{
  LL_PWR_EnableAVD();
}

/**
  * @brief Disable the voltage threshold detection by the Analog Voltage Detector (AVD).
  */
void HAL_PWR_DisableAnalogVoltageDetector(void)
{
  LL_PWR_DisableAVD();
}

/**
  * @brief  Check if the Analog voltage detection is enabled.
  * @retval Returned value is an element of @ref hal_pwr_avd_status_t enumeration.
  *         @arg @ref HAL_PWR_AVD_DISABLED
  *         @arg @ref HAL_PWR_AVD_ENABLED
  */
hal_pwr_avd_status_t HAL_PWR_IsEnabledAnalogVoltageDetector(void)
{
  return ((hal_pwr_avd_status_t)LL_PWR_IsEnabledAVD());
}

/**
  * @brief  Provide the current AVD output.
  * @retval Returned value is an element of @ref hal_pwr_avd_out_t enumeration
  *         @arg @ref HAL_PWR_AVD_OUT_EQ_HIGH_THR
  *         @arg @ref HAL_PWR_AVD_OUT_LOW_THR
  */
hal_pwr_avd_out_t HAL_PWR_GetAnalogVoltageDetectorOutput(void)
{
  return (hal_pwr_avd_out_t)LL_PWR_IsActiveFlag_AVDO();
}

/**
  * @brief   Enable the temperature and VBAT monitor.
  * @warning RTC domain write protection must be disabled to enable temperature and VBAT monitoring.
  * @warning Temperature VBAT monitor is available only when Backup regulator is enabled.
  */
void HAL_PWR_EnableTemperatureVbatMonitor(void)
{
  LL_PWR_EnableTemperatureVbatMonitor();
}

/**
  * @brief   Disable the temperature and VBAT monitor.
  * @warning RTC domain write protection must be disabled to disable temperature and VBAT monitoring.
  */
void HAL_PWR_DisableTemperatureVbatMonitor(void)
{
  LL_PWR_DisableTemperatureVbatMonitor();
}

/**
  * @brief  Check if the temperature and VBAT monitor is enabled.
  * @retval Returned value is an element of @ref hal_pwr_monitor_status_t enumeration
  *         @arg @ref HAL_PWR_MONITOR_DISABLED
  *         @arg @ref HAL_PWR_MONITOR_ENABLED
  */
hal_pwr_monitor_status_t HAL_PWR_IsEnabledTemperatureVbatMonitor(void)
{
  return ((hal_pwr_monitor_status_t)LL_PWR_IsEnabledTemperatureVbatMonitor());
}

/**
  * @brief  Get the temperature level monitoring.
  * @retval Returned value is an element of @ref hal_pwr_temp_level_t enumeration.
  *         @arg @ref HAL_PWR_TEMP_LEVEL_BETWEEN_THR
  *         @arg @ref HAL_PWR_TEMP_LEVEL_EQ_HIGH_THR
  *         @arg @ref HAL_PWR_TEMP_LEVEL_EQ_LOW_THR
  */
hal_pwr_temp_level_t HAL_PWR_GetTemperatureLevelStatus(void)
{
  if (LL_PWR_IsActiveFlag_TEMPH() != 0U)
  {
    return HAL_PWR_TEMP_LEVEL_EQ_HIGH_THR;
  }
  else if (LL_PWR_IsActiveFlag_TEMPL() != 0U)
  {
    return HAL_PWR_TEMP_LEVEL_EQ_LOW_THR;
  }
  else
  {
    return HAL_PWR_TEMP_LEVEL_BETWEEN_THR;
  }
}

/**
  * @brief  Get the VBAT voltage level monitoring.
  * @retval Returned value is an element of @ref hal_pwr_vbat_level_t enumeration.
  *         @arg @ref HAL_PWR_VBAT_LEVEL_BETWEEN_THR
  *         @arg @ref HAL_PWR_VBAT_LEVEL_EQ_LOW_THR
  *         @arg @ref HAL_PWR_VBAT_LEVEL_EQ_HIGH_THR
  */
hal_pwr_vbat_level_t HAL_PWR_GetVbatVoltageLevelStatus(void)
{
  if (LL_PWR_IsActiveFlag_VBATH() != 0U)
  {
    return HAL_PWR_VBAT_LEVEL_EQ_HIGH_THR;
  }
  else if (LL_PWR_IsActiveFlag_VBATL() != 0U)
  {
    return HAL_PWR_VBAT_LEVEL_EQ_LOW_THR;
  }
  else
  {
    return HAL_PWR_VBAT_LEVEL_BETWEEN_THR;
  }
}

/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group6 Memory retention management functions
  * @{
 This section provides functions to manage memory content retention.
 - Call HAL_PWR_LP_EnableMemoryRetention() to enable memory retention.
 - Call HAL_PWR_LP_DisableMemoryRetention() to disable memory retention.
 - Call HAL_PWR_LP_IsEnabledMemoryRetention() to check the selected memory retention status.
  */

/**
  * @brief   Enable memory retention in low power mode.
  * @param   memory This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  *          @arg @ref HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT
  * @warning RTC domain write protection must be disabled to enable memory retention if not HAL_ERROR.
  * @retval  HAL_OK    Memory retention has been correctly enabled.
  * @retval  HAL_ERROR RTC domain write protection is enabled.
  */
hal_status_t HAL_PWR_LP_EnableMemoryRetention(hal_pwr_memory_retention_t memory)
{
  uint32_t timeout = ((PWR_BACKUPRAM_ENABLE_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
  uint32_t brrdy = 0;
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION(memory));

  STM32_UNUSED(memory);

  /* Enabling backup regulator needs backup access */
  if (LL_PWR_IsEnabledBackupDomainWriteProtection() == 1UL)
  {
    return HAL_ERROR;
  }

  /* Enable backup RAM retention in standby */
  LL_PWR_EnableBackupRegulator();

  /* Polling on BRRDY flags */
  do
  {
    brrdy = LL_PWR_IsActiveFlag_BRRDY();
    timeout--;
  } while ((brrdy == 0U) && (timeout != 0U));

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief   Disable memory retention in low power mode.
  * @param   memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  *          @arg @ref HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT
  * @warning RTC domain write protection must be disabled to disable memory retention.
  * @retval  HAL_OK   Memory retention has been correctly disabled.
  * @retval  HAL_ERROR RTC domain write protection is enabled.
  */
hal_status_t HAL_PWR_LP_DisableMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION(memory));

  STM32_UNUSED(memory);

  /* Enabling backup regulator needs backup access */
  if (LL_PWR_IsEnabledBackupDomainWriteProtection() == 1UL)
  {
    return HAL_ERROR;
  }

  /* Disable backup RAM retention in standby */
  LL_PWR_DisableBackupRegulator();

  return HAL_OK;
}

/**
  * @brief  Get memory retention status.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  *         @arg @ref HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT
  * @retval Returned value is an element of @ref hal_pwr_memory_retention_status_t enumeration.
  *         @arg @ref HAL_PWR_MEMORY_RETENTION_DISABLED
  *         @arg @ref HAL_PWR_MEMORY_RETENTION_ENABLED
  */
hal_pwr_memory_retention_status_t HAL_PWR_LP_IsEnabledMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION(memory));

  STM32_UNUSED(memory);

  /* Backup RAM retention in standby mode is ready when PWR_CSR1_BRRDY is set */
  return ((hal_pwr_memory_retention_status_t)LL_PWR_IsActiveFlag_BRRDY());
}

/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group7 Memory low power management functions
  * @{
 This section provides functions to manage Flash memory low power modes.
 - Call HAL_PWR_LP_EnableFlashLowPWRMode() to enable Flash memory power down in Stop mode.
 - Call HAL_PWR_LP_DisableFlashLowPWRMode() to disable Flash memory power down in Stop mode.
 - Call HAL_PWR_LP_IsEnabledFlashLowPWRMode() to check the Flash memory power down in Stop mode status.
  */

/**
  * @brief Enable the Flash low power mode.
  */
void HAL_PWR_LP_EnableFlashLowPWRMode(void)
{
  LL_PWR_EnableFlashLowPWRMode();
}

/**
  * @brief Disable the Flash low power mode.
  */
void HAL_PWR_LP_DisableFlashLowPWRMode(void)
{
  LL_PWR_DisableFlashLowPWRMode();
}

/**
  * @brief  Check if the Flash low power mode is enabled.
  * @retval Returned value is an element of @ref hal_pwr_flash_low_pwr_mode_status_t enumeration.
  *         @arg @ref HAL_PWR_FLASH_LOW_PWR_MODE_DISABLED
  *         @arg @ref HAL_PWR_FLASH_LOW_PWR_MODE_ENABLED
  */
hal_pwr_flash_low_pwr_mode_status_t HAL_PWR_LP_IsEnabledFlashLowPWRMode(void)
{
  return (hal_pwr_flash_low_pwr_mode_status_t)LL_PWR_IsEnabledFlashLowPWRMode();
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group8 Battery management functions
  * @{
  This section provides functions to manage battery charging.
  - Call HAL_PWR_SetConfigBatteryCharging() to set the battery charging resistor.
  - Call HAL_PWR_GetConfigBatteryCharging() to get the battery charging resistor.
  - Call HAL_PWR_EnableBatteryCharging() to enable the battery charging.
  - Call HAL_PWR_DisableBatteryCharging() to disable the battery charging.
  - Call HAL_PWR_IsEnabledBatteryCharging() to check that battery charging is enabled.
  */

/**
  * @brief Set the battery charging resistor.
  * @param value Specifies the charging resistor. This parameter can be one of the following values:
  *        @arg HAL_PWR_BATTERY_CHARGING_RES_5K
  *        @arg HAL_PWR_BATTERY_CHARGING_RES_1_5K
  * @note  When VDD is present, charge the external battery through an internal resistor.
  */
void HAL_PWR_SetConfigBatteryCharging(hal_pwr_battery_charging_res_value_t value)
{
  ASSERT_DBG_PARAM(IS_PWR_BATTERY_RESISTOR_SELECT(value));

  LL_PWR_SetBattChargResistor((uint32_t)value);
}

/**
  * @brief  Get the battery charging resistor.
  * @note   When VDD is present, charge the external battery through an internal resistor.
  * @retval Returned value is an element of @ref hal_pwr_battery_charging_res_value_t enumeration.
  *         @arg @ref HAL_PWR_BATTERY_CHARGING_RES_5K
  *         @arg @ref HAL_PWR_BATTERY_CHARGING_RES_1_5K
  */
hal_pwr_battery_charging_res_value_t HAL_PWR_GetConfigBatteryCharging(void)
{
  return ((hal_pwr_battery_charging_res_value_t)LL_PWR_GetBattChargResistor());
}

/**
  * @brief Enable the battery charging.
  */
void HAL_PWR_EnableBatteryCharging(void)
{
  LL_PWR_EnableBatteryCharging();
}

/**
  * @brief Disable the battery charging.
  */
void HAL_PWR_DisableBatteryCharging(void)
{
  LL_PWR_DisableBatteryCharging();
}

/**
  * @brief  Check that battery charging is enabled.
  * @retval Returned value is an element of @ref hal_pwr_battery_charging_status_t enumeration.
  *         @arg @ref HAL_PWR_BATTERY_CHARGING_DISABLED
  *         @arg @ref HAL_PWR_BATTERY_CHARGING_ENABLED
  */
hal_pwr_battery_charging_status_t HAL_PWR_IsEnabledBatteryCharging(void)
{
  return ((hal_pwr_battery_charging_status_t)LL_PWR_IsEnabledBatteryCharging());
}

/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group9 UCPD management functions
  * @{
  This section provides functions to manage UCPD battery charging and configuration retention.
  - Call HAL_PWR_LP_EnableUCPDDeadBattery() to enable the UCPD dead battery behavior.
  - Call HAL_PWR_LP_DisableUCPDDeadBattery() to disable the UCPD dead battery behavior.
  - Call HAL_PWR_LP_IsEnabledUCPDDeadBattery() to check the UCPD dead battery behavior status.
  - Call HAL_PWR_LP_EnableUCPDRetention() to enable the UCPD configuration retention in Standby mode.
  - Call HAL_PWR_LP_DisableUCPDRetention() to disable the UCPD configuration retention in Standby mode.
  - Call HAL_PWR_LP_IsEnabledUCPDRetention() to check the UCPD configuration retention in Standby mode status.
  */

/**
  * @brief Enable dead battery behavior.
  * @note  After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *        on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *        hand over control to the UCPD (the UCPD must be initialized before doing the disable).
  */
void HAL_PWR_LP_EnableUCPDDeadBattery(void)
{
  LL_PWR_EnableUCPDDeadBattery();
}

/**
  * @brief Disable dead battery behavior.
  * @note  After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *        on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *        hand over control to the UCPD (the UCPD must be initialized before doing the disable).
  */
void HAL_PWR_LP_DisableUCPDDeadBattery(void)
{
  LL_PWR_DisableUCPDDeadBattery();
}

/**
  * @brief  Check that UCPD dead battery is enabled.
  * @note   After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *         on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *         hand over control to the UCPD (the UCPD must be initialized before doing the disable).
  * @retval Returned value is an element of @ref hal_pwr_dead_battery_mode_status_t enumeration.
  *         @arg @ref HAL_PWR_DEAD_BATTERY_MODE_DISABLED
  *         @arg @ref HAL_PWR_DEAD_BATTERY_MODE_ENABLED
  */
hal_pwr_dead_battery_mode_status_t HAL_PWR_LP_IsEnabledUCPDDeadBattery(void)
{
  return (hal_pwr_dead_battery_mode_status_t)(LL_PWR_IsEnabledUCPDDeadBattery());
}

/**
  * @brief Enable UCPD configuration memorization in Standby mode.
  * @note  This function must be called on exiting the Standby mode and before any UCPD configuration update.
  */
void HAL_PWR_LP_EnableUCPDRetention(void)
{
  LL_PWR_EnableUCPDRetentionStandbyMode();
}

/**
  * @brief Disable UCPD configuration memorization in Standby mode.
  * @note  This function must be called on exiting the Standby mode and before any UCPD configuration update.
  */
void HAL_PWR_LP_DisableUCPDRetention(void)
{
  LL_PWR_DisableUCPDRetentionStandbyMode();
}

/**
  * @brief  Check the UCPD configuration memorization in Standby mode.
  * @note   This function must be called on exiting the Standby mode and before any UCPD configuration update.
  * @retval Returned value is an element of @ref hal_pwr_ucpd_retention_status_t enumeration.
  *         @arg @ref HAL_PWR_UCPD_RETENTION_DISABLED
  *         @arg @ref HAL_PWR_UCPD_RETENTION_ENABLED
  */
hal_pwr_ucpd_retention_status_t HAL_PWR_LP_IsEnabledUCPDRetention(void)
{
  return ((hal_pwr_ucpd_retention_status_t)LL_PWR_IsEnabledUCPDRetentionStandbyMode());
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group10 Standby I/O pull management functions
  * @{
  This section provides functions to manage standby mode pull.
  - Call HAL_PWR_EnableGPIOPull() to enable GPIO pull configuration.
  - Call HAL_PWR_DisableGPIOPull() to disable GPIO pull configuration.
  - Call HAL_PWR_IsEnabledGPIOPull() to check that GPIO pull is enabled.
  - Call HAL_PWR_SetConfigPeriphGPIOPull() to set I3C1 or XSPI1 GPIO pull configuration during standby.
  - Call HAL_PWR_GetConfigPeriphGPIOPull() to get I3C1 or XSPI1 GPIO pull configuration during standby.
  */

/**
  * @brief   Enable GPIO pull configuration.
  * @warning When APC bit is set, the I/O pull-up and pull-down configurations defined in PWR_I3CPUCR and PWR_XSPIPxCR
  *          registers are applied.
  * @note    Pull-up set by XSPIxxx_PU bit of PWR_XSPIPUCR register is not activated if the corresponding XSPIxxx_PD
  *          bit of PWR_XSPIPDCR register is also set (pull-down configuration priority is higher).
  *          HAL_PWR_SetConfigPeriphGPIOPull() API ensures there is no conflict when setting XSPIxxx_PU or XSPIxxx_PD
  *          bit.
  */
void HAL_PWR_EnableGPIOPull(void)
{
  LL_PWR_EnablePUPDConfig();
}

/**
  * @brief   Disable GPIO pull configuration.
  * @warning When APC bit is cleared, the I/O pull-up and pull-down configurations defined in PWR_I3CPUCR and
  *          PWR_XSPIPxCR registers are not applied.
  */
void HAL_PWR_DisableGPIOPull(void)
{
  LL_PWR_DisablePUPDConfig();
}

/**
  * @brief   Check that GPIO pull is enabled.
  * @warning When APC bit is cleared, the I/O pull-up and pull-down configurations defined in PWR_I3CPUCR and
  *          PWR_XSPIPxCR registers are not applied.
  * @retval Returned value is an element of @ref hal_pwr_gpio_pull_config_status_t enumeration.
  *         @arg @ref HAL_PWR_GPIO_CONFIG_NOT_APPLIED
  *         @arg @ref HAL_PWR_GPIO_CONFIG_APPLIED
  */
hal_pwr_gpio_pull_config_status_t HAL_PWR_IsEnabledGPIOPull(void)
{
  return (hal_pwr_gpio_pull_config_status_t)LL_PWR_IsEnabledPUPDConfig();
}

/**
  * @brief   Set peripheral (I3C1 or XSPI1) GPIO pull configuration during standby.
  * @param   periph This parameter is an element of @ref hal_pwr_pull_periph_t enumeration.
  *          @arg @ref HAL_PWR_PULL_PERIPH_I3C1
  *          @arg @ref HAL_PWR_PULL_PERIPH_XSPI1
  * @param   pin This parameter is an element of @ref PWR_XSPI1_pull or @ref PWR_I3C1_pull.
  *          @arg @ref HAL_PWR_XSPI1_PULL_PH0
  *          @arg @ref HAL_PWR_XSPI1_PULL_PH1
  *          @arg @ref HAL_PWR_XSPI1_PULL_PF2
  *          @arg @ref HAL_PWR_XSPI1_PULL_PA0
  *          @arg @ref HAL_PWR_XSPI1_PULL_PA2
  *          @arg @ref HAL_PWR_XSPI1_PULL_PA3
  *          @arg @ref HAL_PWR_XSPI1_PULL_PA4
  *          @arg @ref HAL_PWR_XSPI1_PULL_PA5
  *          @arg @ref HAL_PWR_XSPI1_PULL_PB1
  *          @arg @ref HAL_PWR_XSPI1_PULL_PB2
  *          @arg @ref HAL_PWR_XSPI1_PULL_PD0
  *          @arg @ref HAL_PWR_XSPI1_PULL_PD1
  *          @arg @ref HAL_PWR_XSPI1_PULL_PD2
  *          @arg @ref HAL_PWR_XSPI1_PULL_PD3
  *          @arg @ref HAL_PWR_XSPI1_PULL_PG10
  *          @arg @ref HAL_PWR_I3C1_PULL_PA15
  *          @arg @ref HAL_PWR_I3C1_PULL_PB3
  *          @arg @ref HAL_PWR_I3C1_PULL_PB4
  *          @arg @ref HAL_PWR_I3C1_PULL_PB8
  *          @arg @ref HAL_PWR_I3C1_PULL_PB9
  *          @arg @ref HAL_PWR_I3C1_PULL_PC8
  *          @arg @ref HAL_PWR_I3C1_PULL_PC9
  *          @arg @ref HAL_PWR_I3C1_PULL_PD0
  *          @arg @ref HAL_PWR_I3C1_PULL_PD1
  *          @arg @ref HAL_PWR_I3C1_PULL_PD6
  *          @arg @ref HAL_PWR_I3C1_PULL_PD7
  *          @arg @ref HAL_PWR_I3C1_PULL_PE5
  *          @arg @ref HAL_PWR_I3C1_PULL_PE6
  *          @arg @ref HAL_PWR_I3C1_PULL_PG13
  *          @arg @ref HAL_PWR_I3C1_PULL_PG14
  *          @arg @ref HAL_PWR_I3C1_PULL_PH11
  *          @arg @ref HAL_PWR_I3C1_PULL_PH12
  *          @arg @ref HAL_PWR_I3C1_PULL_PI2
  * @param   pull This parameter is an element of @ref hal_pwr_gpio_pull_t enumeration.
  *          @arg @ref HAL_PWR_GPIO_PULL_NO
  *          @arg @ref HAL_PWR_GPIO_PULL_UP
  *          @arg @ref HAL_PWR_GPIO_PULL_DOWN
  * @warning Configuration is applied on hardware system only if APC bit is set with HAL_PWR_EnableGPIOPull().
  */
void HAL_PWR_SetConfigPeriphGPIOPull(hal_pwr_pull_periph_t periph, uint32_t pin, hal_pwr_gpio_pull_t pull)
{
  ASSERT_DBG_PARAM(IS_PWR_PERIPH_GPIO_PULL_SET_CONFIG(periph, pin, pull));

  if (periph == HAL_PWR_PULL_PERIPH_I3C1)
  {
    if (pull == HAL_PWR_GPIO_PULL_UP)
    {
      LL_PWR_EnableI3CPullUp(pin);
    }
    else if (pull == HAL_PWR_GPIO_PULL_NO)
    {
      LL_PWR_DisableI3CPullUp(pin);
    }
    else
    {
      /* Do nothing, I3C pin cannot be configured in pull-down */
    }
  }
  else
  {
    if (pull == HAL_PWR_GPIO_PULL_NO)
    {
      LL_PWR_DisableXSPIPullUp(pin);
      LL_PWR_DisableXSPIPullDown(pin);
    }
    else if (pull == HAL_PWR_GPIO_PULL_UP)
    {
      LL_PWR_EnableXSPIPullUp(pin);
      /* Disable XSPI pull-down. GPIO cannot be in pull-down and pull-up */
      LL_PWR_DisableXSPIPullDown(pin);
    }
    else
    {
      LL_PWR_EnableXSPIPullDown(pin);
      /* Disable XSPI pull-up. GPIO cannot be in pull-down and pull-up */
      LL_PWR_DisableXSPIPullUp(pin);
    }
  }
}

/**
  * @brief  Get peripheral (I3C1 or XSPI1) GPIO pull configuration during standby.
  * @param  periph This parameter is an element of @ref hal_pwr_pull_periph_t enumeration.
  *         @arg @ref HAL_PWR_PULL_PERIPH_I3C1
  *         @arg @ref HAL_PWR_PULL_PERIPH_XSPI1
  * @param  pin This parameter is an element of @ref PWR_XSPI1_pull or @ref PWR_I3C1_pull.
  *         @arg @ref HAL_PWR_XSPI1_PULL_PH0
  *         @arg @ref HAL_PWR_XSPI1_PULL_PH1
  *         @arg @ref HAL_PWR_XSPI1_PULL_PF2
  *         @arg @ref HAL_PWR_XSPI1_PULL_PA0
  *         @arg @ref HAL_PWR_XSPI1_PULL_PA2
  *         @arg @ref HAL_PWR_XSPI1_PULL_PA3
  *         @arg @ref HAL_PWR_XSPI1_PULL_PA4
  *         @arg @ref HAL_PWR_XSPI1_PULL_PA5
  *         @arg @ref HAL_PWR_XSPI1_PULL_PB1
  *         @arg @ref HAL_PWR_XSPI1_PULL_PB2
  *         @arg @ref HAL_PWR_XSPI1_PULL_PD0
  *         @arg @ref HAL_PWR_XSPI1_PULL_PD1
  *         @arg @ref HAL_PWR_XSPI1_PULL_PD2
  *         @arg @ref HAL_PWR_XSPI1_PULL_PD3
  *         @arg @ref HAL_PWR_XSPI1_PULL_PG10
  *         @arg @ref HAL_PWR_I3C1_PULL_PA15
  *         @arg @ref HAL_PWR_I3C1_PULL_PB3
  *         @arg @ref HAL_PWR_I3C1_PULL_PB4
  *         @arg @ref HAL_PWR_I3C1_PULL_PB8
  *         @arg @ref HAL_PWR_I3C1_PULL_PB9
  *         @arg @ref HAL_PWR_I3C1_PULL_PC8
  *         @arg @ref HAL_PWR_I3C1_PULL_PC9
  *         @arg @ref HAL_PWR_I3C1_PULL_PD0
  *         @arg @ref HAL_PWR_I3C1_PULL_PD1
  *         @arg @ref HAL_PWR_I3C1_PULL_PD6
  *         @arg @ref HAL_PWR_I3C1_PULL_PD7
  *         @arg @ref HAL_PWR_I3C1_PULL_PE5
  *         @arg @ref HAL_PWR_I3C1_PULL_PE6
  *         @arg @ref HAL_PWR_I3C1_PULL_PG13
  *         @arg @ref HAL_PWR_I3C1_PULL_PG14
  *         @arg @ref HAL_PWR_I3C1_PULL_PH11
  *         @arg @ref HAL_PWR_I3C1_PULL_PH12
  *         @arg @ref HAL_PWR_I3C1_PULL_PI2
  * @retval Returned value is an element of @ref hal_pwr_gpio_pull_t enumeration.
  *         @arg @ref HAL_PWR_GPIO_PULL_NO
  *         @arg @ref HAL_PWR_GPIO_PULL_UP
  *         @arg @ref HAL_PWR_GPIO_PULL_DOWN
  */
hal_pwr_gpio_pull_t HAL_PWR_GetConfigPeriphGPIOPull(hal_pwr_pull_periph_t periph, uint32_t pin)
{
  hal_pwr_gpio_pull_t pull = HAL_PWR_GPIO_PULL_NO;

  ASSERT_DBG_PARAM(IS_PWR_PERIPH_GPIO_PULL_GET_CONFIG(periph, pin));

  if (periph == HAL_PWR_PULL_PERIPH_I3C1)
  {
    pull = (hal_pwr_gpio_pull_t)LL_PWR_IsEnabledI3CPullUp(pin);
  }
  else
  {
    const uint32_t xspi_pull_up = LL_PWR_IsEnabledXSPIPullUp(pin);
    const uint32_t xspi_pull_down = LL_PWR_IsEnabledXSPIPullDown(pin);

    if ((xspi_pull_up == 0UL) && (xspi_pull_down == 0UL))
    {
      pull = HAL_PWR_GPIO_PULL_NO;
    }
    else if ((xspi_pull_up == 1UL) && (xspi_pull_down == 0UL))
    {
      pull = HAL_PWR_GPIO_PULL_UP;
    }
    else
    {
      pull = HAL_PWR_GPIO_PULL_DOWN;
    }
  }

  return pull;
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

#endif /* USE_HAL_PWR_MODULE */
#endif /* PWR */
/**
  * @}
  */
