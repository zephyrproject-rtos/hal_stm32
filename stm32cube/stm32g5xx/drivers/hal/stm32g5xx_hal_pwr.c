/**
  **********************************************************************************************************************
  * @file    stm32g5xx_hal_pwr.c
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

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */
/** @defgroup PWR_Introduction PWR Introduction
  * @{

  - The PWR peripheral in STM32 manages power modes (sleep, stop, standby), voltage scaling and power supplies.
  - It reduces power consumption, supports multiple wakeup sources, and is essential for battery-powered applications.
  - It manages the power supplies for various internal components.
  - Control is achieved through PWR registers; use HAL functions for simplified configuration.

  */
/**
  * @}
  */

/** @defgroup PWR_How_To_Use PWR How To Use
  * @{
# PWR peripheral overview

The Power control peripheral (PWR) provides an overview of the supply architecture for the different power domains
and of the supply configuration controller.

This file provides firmware functions to manage the following functionalities :
   - Wakeup pins management functions.
   - RTC domain access management functions.
   - Main regulator management functions.
   - Low power mode management functions.
   - Voltage monitoring management functions.
   - Memory retention management functions.
   - Memory low power management functions.
   - USB power supply management functions.
   - UCPD management functions.
   - I/O retention management functions.
   - Privilege attribute management functions.
   - Secure attribute management functions.

# How to use the PWR HAL module driver

## The PWR HAL driver can be used as follows:

This module manages all device power supplies and power modes transitions

This module provides 12 different set of APIs that allows to :

1. Manage the wakeup pin :
   The wakeup pin is used to wakeup the system from low power modes.
   - Configure the wakeup pin polarity and pull independently and without enabling it :
     - This functionality is ensured by HAL_PWR_LP_SetConfigWakeupPin() function. The p_config pointer allows to
       configure wakeup polarity and pull.
       - When p_config is null,this function returns an HAL_INVALID_PARAM.
   - Get the wakeup pin polarity and pull configuration:
     - This functionality is ensured by HAL_PWR_LP_GetConfigWakeupPin() function.
   - Enable, disable and check the wakeup pin status :
     - These functionalities are ensured respectively by HAL_PWR_LP_EnableWakeupPin(), HAL_PWR_LP_DisableWakeupPin()
       and HAL_PWR_LP_IsEnabledWakeupPin() functions.
   - Read the wakeup source flag status :
     - This functionality is ensured by HAL_PWR_LP_GetWakeupSource() function.
   - Clear the wakeup source flags :
     - This functionality is ensured by HAL_PWR_LP_CleanWakeupSource() function.

2. Manage RTC domain write protection :
   After a system reset, the RTC domain is protected against possible unwanted write accesses.
   - Enable, disable and check the write protection status of RTC domain :
     - These functionalities are ensured respectively by HAL_PWR_EnableRTCDomainWriteProtection(),
       HAL_PWR_DisableRTCDomainWriteProtection() and HAL_PWR_IsEnabledRTCDomainWriteProtection() functions.

3. Manage power supply :
   The power supplies can be configured to manage application power consumption and performance.
   - Configure the main regulator voltage scaling range for different power modes :
     - This functionality is ensured by HAL_PWR_SetMainRegulatorVoltageScalingRange() function.
   - Get the voltage scaling range configuration :
     - This functionality is ensured by HAL_PWR_GetMainRegulatorVoltageScalingRange() function.
   - Get the active voltage scaling range :
     - This functionality is ensured by HAL_PWR_GetMainRegulatorActiveVoltageScalingRange() function.
   - Set the Main Regulator supply source configuration:
     - This functionality is ensured by HAL_PWR_SetMainRegulatorSupply() function.
   - Get the Main Regulator supply source configuration:
     - This functionality is ensured by HAL_PWR_GetMainRegulatorSupply() function.
   - Get the Main Regulator supply source status:
     - This functionality is ensured by HAL_PWR_GetMainRegulatorSupplyStatus() function.

4. Manage low power modes:
   Several power modes are available to manage power consumption.
   - Clear Core pending event to clear internal cortex event before entering sleep or stop mode:
     - This functionality is ensured by HAL_PWR_ClearCorePendingEvent() function.
   - Enter the MCU to low power modes:
     - Enter the MCU to sleep mode through WFE or WFI request:
       - This functionality is ensured by HAL_PWR_EnterSleepMode() function.
     - Enter the MCU to stop mode through WFE or WFI request:
       - This functionality is ensured by HAL_PWR_EnterStopMode() function.
     - Enter the MCU to standby mode:
       - This functionality is ensured by HAL_PWR_EnterStandbyMode() function.
   - Configure the core deep sleep mode:
     - This functionality is ensured by HAL_PWR_SetCoreSleepMode() function.
   - Get the core deep sleep mode configuration:
     - This functionality is ensured by HAL_PWR_GetCoreSleepMode() function.
   - Enable, disable and check the core sleep on exit to re-entry in sleep mode after an interruption is over:
     - These functionalities are ensured respectively by HAL_PWR_EnableCoreSleepOnExit(),
        HAL_PWR_DisableCoreSleepOnExit() and HAL_PWR_IsEnabledCoreSleepOnExit() functions.
   - Enable, disable and check the core send event on pending to wakeup after any pending event/ interrupt:
     - these functionalities are ensured respectively by HAL_PWR_EnableCoreSendEventOnPending(),
         HAL_PWR_DisableCoreSendEventOnPending() and HAL_PWR_IsEnabledCoreSendEventOnPending() functions.
   - Get the previous system power mode:
     - This functionality is ensured by HAL_PWR_GetPreviousSystemPowerMode() function.
   - Clean the previous system power mode flag(s) before entering in low power mode:
     - This functionality is ensured by HAL_PWR_CleanPreviousSystemPowerMode() function.

5. Manage monitoring:
   The monitor can be used to manage the power supplies and supply domains.
   - Configure the voltage threshold detector by the programmable voltage detector:
     - This functionality is ensured by HAL_PWR_SetProgrammableVoltageDetectorLevel() function.
   - Get the programmable voltage detector configuration:
     - This functionality is ensured by HAL_PWR_GetProgrammableVoltageDetectorLevel() function.
   - Enable, disable and check the programmable voltage detector status:
     - These functionalities are ensured respectively by HAL_PWR_EnableProgrammableVoltageDetector(),
       HAL_PWR_DisableProgrammableVoltageDetector() and HAL_PWR_IsEnabledProgrammableVoltageDetector() functions.
   - Get the programmable voltage detector output value:
     - This functionality is ensured by HAL_PWR_GetProgrammableVoltageDetectorOutput() function.
   - Configure the voltage threshold detector by the analog voltage detector:
     - This functionality is ensured by HAL_PWR_SetAnalogVoltageDetectorLevel() function.
   - Get the analog voltage detector configuration:
     - This functionality is ensured by HAL_PWR_GetAnalogVoltageDetectorLevel() function.
   - Enable, disable and check the analog voltage detector status:
     - These functionalities are ensured respectively by HAL_PWR_EnableAnalogVoltageDetector(),
       HAL_PWR_DisableAnalogVoltageDetector() and HAL_PWR_IsEnabledAnalogVoltageDetector() functions.
   - Get the analog voltage detector output value:
     - This functionality is ensured by HAL_PWR_GetAnalogVoltageDetectorOutput() function.
   - Enable, disable and check the peripheral voltage monitoring status:
     - These functionalities are ensured respectively by HAL_PWR_EnableTemperatureVddMonitor(),
       HAL_PWR_DisableTemperatureVddMonitor() and HAL_PWR_IsEnabledTemperatureVddMonitor() functions.
   - Get the temperature monitoring output value:
     - This functionality is ensured by HAL_PWR_GetTemperatureLevelStatus() function.
   - Get the VDD voltage monitoring output value:
     - This functionality is ensured by HAL_PWR_GetVddVoltageLevelStatus() function.

6. Manage memory retention:
   After entering low power mode, the memories content retention can be managed.
   - Enable, disable and check the memory retention:
     - These functionalities are ensured by HAL_PWR_LP_EnableMemoryRetention(), HAL_PWR_LP_DisableMemoryRetention() and
       HAL_PWR_LP_IsEnabledMemoryRetention() functions.
   - Enable, disable and check the memory retention per page:
     - These functionalities are ensured by HAL_PWR_LP_EnableMemoryPageRetention(),
       HAL_PWR_LP_DisableMemoryPageRetention() and HAL_PWR_LP_IsEnabledMemoryPageRetention() functions.
   - Enable, disable and check UCPD configuration retention:
     - These functionalities are ensured by HAL_PWR_LP_EnableUCPDRetention(), HAL_PWR_LP_DisableUCPDRetention() and
       HAL_PWR_LP_IsEnabledUCPDRetention() functions.

7. Manage memory power modes:
   After entering low power mode, the Flash memory power mode can be managed.
   - Enable, disable and check the Flash low power mode in Stop modes:
     - These functionalities are ensured by HAL_PWR_LP_EnableFlashLowPWRMode(), HAL_PWR_LP_DisableFlashLowPWRMode() and
       HAL_PWR_LP_IsEnabledFlashLowPWRMode() functions.

8. Manage USB power supply:
   Several API are available to manage the USB power supply:
   - Enable, disable and check the USB independent supply:
     - These functionalities are ensured by HAL_PWR_EnableVddUSBIndependentSupply(),
       HAL_PWR_DisableVddUSBIndependentSupply() and HAL_PWR_IsEnabledVddUSBIndependentSupply() functions.

9. Manage UCPD:
   Several API are available to manage the UCPD dead battery and configuration retention features:
   - Enable, disable and check UCPD dead battery:
     - These functionalities are ensured by HAL_PWR_LP_EnableUCPDDeadBattery(), HAL_PWR_LP_DisableUCPDDeadBattery() and
       HAL_PWR_LP_IsEnabledUCPDDeadBattery() functions.
   - Enable, disable and check UCPD configuration retention:
     - These functionalities are ensured by HAL_PWR_LP_EnableUCPDRetention(), HAL_PWR_LP_DisableUCPDRetention() and
       HAL_PWR_LP_IsEnabledUCPDRetention() functions.

10. Manage the I/O Retention:
   Several API are available to retain or release the output of IOs and/or JTAGIOs.
   - Enable, disable and check IOs/JTAGIOs retention status:
     - These functionalities are ensured by HAL_PWR_LP_EnableIORetention(), HAL_PWR_LP_DisableIORetention() and
       HAL_PWR_LP_IsEnabledIORetention() functions.

11. Manage the privilege attribute of some PWR items:
   Several API are available to manage the privilege attribute of some PWR items.
   - Configure the privilege attribute of some PWR items:
     - This functionality is ensured by HAL_PWR_SetPrivAttr() function.
   - Get the privilege attribute configuration of some PWR items:
     - This functionality is ensured by HAL_PWR_GetPrivAttr() function.

12. Manage the secure attribute of some PWR items:
   Several API are available to manage the secure attribute of some PWR items.
   - Configure the secure attribute of some PWR items:
     - This functionality is ensured by HAL_PWR_SetSecAttr() function.
   - Get the secure attribute configuration of some PWR items:
     - This functionality is ensured by HAL_PWR_GetSecAttr() function.
  */
/**
  * @}
  */

/** @defgroup PWR_Configuration_Table PWR Configuration Table
  * @{
## Configuration inside the PWR driver

Config defines                    | Description       | Default value | Note                                          |
--------------------------------- | ----------------- | ------------- | --------------------------------------------- |
PRODUCT                           | from IDE          | NA            | The selected device product.                  |
USE_HAL_PWR_MODULE                | from hal_conf.h   | 1U            | When set, HAL PWR module is enabled.          |
USE_ASSERT_DBG_PARAM              | from IDE          | None          | When defined, enable the params assert.       |
USE_HAL_CHECK_PARAM               | from hal_conf.h   | 0U            | When set, parameters are checked in runtime.  |
CMSE_SECURE_EXECUTION_ENVIRONMENT | from stm32g5xx.h  | NA            | Defined in secure context.                    |
  */
/**
  * @}
  */
#if defined(PWR)
#if defined(USE_HAL_PWR_MODULE) && (USE_HAL_PWR_MODULE == 1)

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private defines ---------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Constants PWR Private Constants
  * @{
  */
/* Time out value of flags setting */
#define PWR_VOS_SELECT_MAX_DELAY           0x32U   /*!< Max VOS timeout              */
#define PWR_REGULATOR_SELECT_MAX_DELAY     0x32U   /*!< Max regulator select timeout */

#define PWR_SRAM1_RETENTION_PAGES_MAX      0x01U   /*!< SRAM1 max pages number       */
#define PWR_SRAM2_RETENTION_PAGES_MAX      0x02U   /*!< SRAM2 max pages number       */
#if defined(SRAM3_BASE)
#define PWR_SRAM3_RETENTION_PAGES_MAX      0x01U   /*!< SRAM3 max pages number       */
#endif /* SRAM3_BASE */

/*! Number of memory banks */
#define PWR_MEMORY_BANKS_NUMBER (uint32_t)(sizeof(PWR_MemoryFullRetentionMap) / sizeof(PWR_MemoryFullRetentionMap[0]))
/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Variables PWR Private Variables
  * @{
  */
/*! Memory retention mapping table */
static const uint32_t PWR_MemoryFullRetentionMap[] =
{
  LL_PWR_SRAM1_STOP_RETENTION,
  LL_PWR_SRAM2_STOP_RETENTION,
#if defined(SRAM3_BASE)
  LL_PWR_SRAM3_STOP_RETENTION
#endif /* SRAM3_BASE */
};

/*! Memory maximum page retention mapping table */
static const uint32_t PWR_MemoryMaxPagesRetentionMap[PWR_MEMORY_BANKS_NUMBER] =
{
  PWR_SRAM1_RETENTION_PAGES_MAX,
  PWR_SRAM2_RETENTION_PAGES_MAX,
#if defined(SRAM3_BASE)
  PWR_SRAM3_RETENTION_PAGES_MAX
#endif /* SRAM3_BASE */
};
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Macros PWR Private Macros
  * @{
  */

/*! Set wakeup pins check macro */
#define IS_PWR_SET_WAKEUP_PIN(pin) \
  ((((pin) & HAL_PWR_WAKEUP_PIN_ALL) != 0U) && (((pin) & (~HAL_PWR_WAKEUP_PIN_ALL)) == 0U))

/*! Set wakeup sources check macro */
#define IS_PWR_SET_WAKEUP_SOURCE(source) \
  ((((source) & HAL_PWR_WAKEUP_SOURCE_ALL) != 0U) && (((source) & (~HAL_PWR_WAKEUP_SOURCE_ALL)) == 0U))

/*! Wakeup pin polarity check macro */
#define IS_PWR_WAKEUP_PIN_POLARITY(polarity) \
  (((polarity) == HAL_PWR_WAKEUP_PIN_POLARITY_HIGH ) || ((polarity) == HAL_PWR_WAKEUP_PIN_POLARITY_LOW))

/*! Wakeup pin pull check macro */
#define IS_PWR_WAKEUP_PIN_PULL(pull) \
  (((pull) == HAL_PWR_WAKEUP_PIN_PULL_NO ) || ((pull) == HAL_PWR_WAKEUP_PIN_PULL_UP) \
   || ((pull) == HAL_PWR_WAKEUP_PIN_PULL_DOWN))

/*! Get wakeup pins check macro */
#if defined(PWR_WUCR_WUPEN8)
#define IS_PWR_GET_WAKEUP_PIN(pin)    \
  (((pin) == HAL_PWR_WAKEUP_PIN_1)    \
   || ((pin) == HAL_PWR_WAKEUP_PIN_2) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_4) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_5) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_6) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_7) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_8))
#else
#define IS_PWR_GET_WAKEUP_PIN(pin)    \
  (((pin) == HAL_PWR_WAKEUP_PIN_1)    \
   || ((pin) == HAL_PWR_WAKEUP_PIN_2) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_4) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_5) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_6) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_7))
#endif /* PWR_WUCR_WUPEN8 */

/*! Voltage scaling range check macro */
#define IS_PWR_VOLT_SCALE_RANGE(range)  \
  (((range) == HAL_PWR_VOLT_SCALE_0)    \
   || ((range) == HAL_PWR_VOLT_SCALE_1) \
   || ((range) == HAL_PWR_VOLT_SCALE_2))

/*! Main regulator supply check macro */
#define IS_PWR_SET_MAIN_REGULATOR_SUPPLY(regulator) \
  ((regulator) == HAL_PWR_MAIN_REGULATOR_SUPPLY_NOT_BYPASS \
   || ((regulator == HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASS)))

/*! Low power mode entry check macro */
#define IS_PWR_LP_MODE_ENTRY(entry) \
  (((entry) == HAL_PWR_LOW_PWR_MODE_WFE) || ((entry) == HAL_PWR_LOW_PWR_MODE_WFI))

/*! Stop mode check macro */
#define IS_PWR_STOP_MODE(mode)  \
  ((mode) == HAL_PWR_STOP_MODE)

/*! Core sleep mode check macro */
#define IS_PWR_CORE_SLEEP_MODE(mode) \
  (((mode) == HAL_PWR_CORE_SLEEP) || ((mode) == HAL_PWR_CORE_DEEP_SLEEP))

/*! PVD level check macro */
#define IS_PWR_PVD_LEVEL(level)        \
  (((level) == HAL_PWR_PVD_VDD_LEVEL_0)    \
   || ((level) == HAL_PWR_PVD_VDD_LEVEL_1) \
   || ((level) == HAL_PWR_PVD_PVDIN_VREFINT))

/*! AVD level check macro */
#define IS_PWR_AVD_LEVEL(level)        \
  (((level) == HAL_PWR_AVD_VDDA_LEVEL_0)    \
   || ((level) == HAL_PWR_AVD_VDDA_LEVEL_1))

/*! Memory retention check macro */
#define IS_PWR_SINGLE_PAGE_MEMORY_RETENTION(memory) \
  ((((uint32_t)(memory)) < PWR_MEMORY_BANKS_NUMBER) && ((PWR_MemoryMaxPagesRetentionMap[memory]) == 1U))

/*! Memory page retention check macro */
#define IS_PWR_MEMORY_PAGES_RETENTION(memory, page_idx, page_nbr)                     \
  ((((uint32_t)(memory)) < PWR_MEMORY_BANKS_NUMBER)                                               \
   && ((((page_idx) - 1U) + (page_nbr)) <= (PWR_MemoryMaxPagesRetentionMap[memory]))  \
   && ((((PWR_MemoryMaxPagesRetentionMap[memory]) > 1U)))                             \
   && ((((page_idx) - 1U) + (page_nbr)) > 0U))

/*! I/O selection retention check macro */
#define IS_PWR_SET_IO_RETENTION(io)                                     \
  ((((io & HAL_PWR_IO_RETENTION_JTAGIO) == HAL_PWR_IO_RETENTION_JTAGIO) \
    || ((io & HAL_PWR_IO_RETENTION_GPIO) == HAL_PWR_IO_RETENTION_GPIO)) \
   && (io <= HAL_PWR_IO_RETENTION_ALL))

/*! I/O selection retention enabled check macro */
#define IS_PWR_GET_IO_RETENTION(io)         \
  (((io) == HAL_PWR_IO_RETENTION_JTAGIO)    \
   || ((io) == HAL_PWR_IO_RETENTION_GPIO))

/*! PWR set privilege item check macro */
#define IS_PWR_SET_PRIV_ITEM(item)  \
  ((((item) & HAL_PWR_PRIV_ITEM_ALL) != 0U) && (((item) & (~HAL_PWR_PRIV_ITEM_ALL)) == 0U))

/*! PWR get privilege item check macro */
#define IS_PWR_GET_PRIV_ITEM(item)      \
  (((item) == HAL_PWR_PRIV_ITEM_SPRIV)  \
   || ((item) == HAL_PWR_PRIV_ITEM_NSPRIV))

/*! PWR set secure item check macro */
#define IS_PWR_SET_SEC_ITEM(item)  \
  ((((item) & HAL_PWR_SEC_ITEM_ALL) != 0U) && (((item) & (~HAL_PWR_SEC_ITEM_ALL)) == 0U))

/*! PWR get secure item check macro */
#if defined(PWR_WUCR_WUPEN8) && defined(PWR_USBSCR_USB33SV)
#define IS_PWR_GET_SEC_ITEM(item)       \
  (((item) == HAL_PWR_SEC_ITEM_WUP1)    \
   || ((item) == HAL_PWR_SEC_ITEM_WUP2) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP4) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP5) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP6) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP7) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP8) \
   || ((item) == HAL_PWR_SEC_ITEM_RET)  \
   || ((item) == HAL_PWR_SEC_ITEM_LPM)  \
   || ((item) == HAL_PWR_SEC_ITEM_SCM)  \
   || ((item) == HAL_PWR_SEC_ITEM_RTC)  \
   || ((item) == HAL_PWR_SEC_ITEM_VUSB))
#elif defined(PWR_WUCR_WUPEN8)
#define IS_PWR_GET_SEC_ITEM(item)       \
  (((item) == HAL_PWR_SEC_ITEM_WUP1)    \
   || ((item) == HAL_PWR_SEC_ITEM_WUP2) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP4) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP5) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP6) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP7) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP8) \
   || ((item) == HAL_PWR_SEC_ITEM_RET)  \
   || ((item) == HAL_PWR_SEC_ITEM_LPM)  \
   || ((item) == HAL_PWR_SEC_ITEM_SCM)  \
   || ((item) == HAL_PWR_SEC_ITEM_RTC))
#elif defined(PWR_USBSCR_USB33SV)
#define IS_PWR_GET_SEC_ITEM(item)       \
  (((item) == HAL_PWR_SEC_ITEM_WUP1)    \
   || ((item) == HAL_PWR_SEC_ITEM_WUP2) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP4) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP5) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP6) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP7) \
   || ((item) == HAL_PWR_SEC_ITEM_RET)  \
   || ((item) == HAL_PWR_SEC_ITEM_LPM)  \
   || ((item) == HAL_PWR_SEC_ITEM_SCM)  \
   || ((item) == HAL_PWR_SEC_ITEM_RTC)  \
   || ((item) == HAL_PWR_SEC_ITEM_VUSB))
#else
#define IS_PWR_GET_SEC_ITEM(item)       \
  (((item) == HAL_PWR_SEC_ITEM_WUP1)    \
   || ((item) == HAL_PWR_SEC_ITEM_WUP2) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP4) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP5) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP6) \
   || ((item) == HAL_PWR_SEC_ITEM_WUP7) \
   || ((item) == HAL_PWR_SEC_ITEM_RET)  \
   || ((item) == HAL_PWR_SEC_ITEM_LPM)  \
   || ((item) == HAL_PWR_SEC_ITEM_SCM)  \
   || ((item) == HAL_PWR_SEC_ITEM_RTC))
#endif /* PWR_USBSCR_USB33SV */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group1 Wakeup pins management functions
  * @{
  This section provides functions allowing to configure the wakeup pins:
  - Call HAL_PWR_LP_SetConfigWakeupPin() function to configure wakeup pin.
  - Call HAL_PWR_LP_GetConfigWakeupPin() function to get wakeup pin configuration.
  - Call HAL_PWR_LP_EnableWakeupPin() function to enable wakeup pin.
  - Call HAL_PWR_LP_DisableWakeupPin() function to disable wakeup pin.
  - Call HAL_PWR_LP_IsEnabledWakeupPin() function to check that wakeup pin is enabled.
  - Call HAL_PWR_LP_GetWakeupSource() function to get the wakeup source.
  - Call HAL_PWR_LP_CleanWakeupSource() function to clean the wakeup source.
  */

/**
  * @brief  Set wakeup pin configuration.
  * @param  wakeup_pin  This parameter can be a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1, 2, 4..8). (*)
  * @param  p_config    Pointer to a @ref hal_pwr_wakeup_pin_config_t structure.
  * @retval HAL_INVALID_PARAM p_config pointer is NULL.
  * @retval HAL_OK      Wakeup pin has been correctly configured.
  * @note (*) The available wakeup pins depend on device used.
  */
hal_status_t HAL_PWR_LP_SetConfigWakeupPin(uint32_t wakeup_pin, const hal_pwr_wakeup_pin_config_t *p_config)
{
  uint32_t temp_pin = wakeup_pin;
  __IO uint32_t register_value = LL_PWR_READ_REG(WUCR);
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

  /* Get wakeup pin information */
  position    = STM32_POSITION_VAL(temp_pin);
  current_pin = 1UL << position;

  while (temp_pin != 0U)
  {
    /* Mask values which will be modified */
    register_value &= ~(uint32_t)((LL_PWR_WAKEUP_PIN_REF << position) \
                                  + (LL_PWR_WAKEUP_PIN_PULL_REF << (position * LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET)));

    /* Compute new value */
    register_value |= (uint32_t)(((uint32_t)p_config->polarity << (LL_PWR_WAKEUP_PIN_REF_POS + position)) \
                                 + ((uint32_t)p_config->pull << (LL_PWR_WAKEUP_PIN_PULL_REF_POS \
                                                                 + (position * LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET))));

    /* Update wakeup pin information */
    temp_pin    &= (~current_pin);
    position    = STM32_POSITION_VAL(temp_pin);
    current_pin = (uint32_t)(1UL << position);
  }

  /* Set new value in one register access */
  LL_PWR_WRITE_REG(WUCR, register_value);

  return HAL_OK;
}

/**
  * @brief  Get wakeup pin configuration.
  * @param  wakeup_pin This parameter can be one of HAL_PWR_WAKEUP_PIN_x where x can be (1, 2, 4..8). (*)
  * @param  p_config   Pointer to a @ref hal_pwr_wakeup_pin_config_t structure.
  * @note (*) The available wakeup pins depend on device used.
  */
void HAL_PWR_LP_GetConfigWakeupPin(uint32_t wakeup_pin, hal_pwr_wakeup_pin_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_PWR_GET_WAKEUP_PIN(wakeup_pin));

  /* Get the configuration */
  p_config->polarity = (hal_pwr_wakeup_pin_polarity_t)LL_PWR_GetWakeUpPinPolarity(wakeup_pin);
  p_config->pull     = (hal_pwr_wakeup_pin_pull_t)LL_PWR_GetWakeUpPinPull(wakeup_pin);
}

/**
  * @brief  Enable the wakeup pin configuration.
  * @param  wakeup_pin This parameter can be a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1, 2, 4..8). (*)
  * @note   Wakeup pins are used to wake up the system from Standby mode.
  * @note (*) The available wakeup pins depend on device used.
  */
void HAL_PWR_LP_EnableWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  LL_PWR_EnableWakeUpPin(wakeup_pin);
}

/**
  * @brief  Disable the wakeup pin configuration.
  * @param  wakeup_pin This parameter can be a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1, 2, 4..8). (*)
  * @note   Wakeup pins are used to wake up the system from Standby mode.
  * @note (*) The available wakeup pins depend on device used.
  */
void HAL_PWR_LP_DisableWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  LL_PWR_DisableWakeUpPin(wakeup_pin);
}

/**
  * @brief  Check that wakeup pin is enabled.
  * @param  wakeup_pin This parameter can be one of HAL_PWR_WAKEUP_PIN_x where x can be (1, 2, 4..8). (*)
  * @retval HAL_PWR_WAKEUP_PIN_DISABLED Wakeup pin disabled
  * @retval HAL_PWR_WAKEUP_PIN_ENABLED  Wakeup pin enabled
  * @note (*) The available wakeup pins depend on device used.
  */
hal_pwr_wakeup_pin_status_t HAL_PWR_LP_IsEnabledWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_GET_WAKEUP_PIN(wakeup_pin));

  return ((hal_pwr_wakeup_pin_status_t)LL_PWR_IsEnabledWakeUpPin(wakeup_pin));
}

/**
  * @brief  Return the wakeup sources.
  * @retval Can be one of or a combination of @ref PWR_wakeup_source.
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_1
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_2
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_4
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_5
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_6
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_7
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_8 (*)
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_ALL
  * @note   (*) : Not available on all devices.
  * @warning This API returns the wakeup source flags which can be a combination of multiple sources.
  */
uint32_t HAL_PWR_LP_GetWakeupSource(void)
{
  return (LL_PWR_READ_REG(WUSR));
}

/**
  * @brief  Clean the selected wakeup source(s) flag(s).
  * @param  wakeup_source  This parameter can be one or a combination of @ref PWR_wakeup_source.
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_1
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_2
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_4
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_5
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_6
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_7
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_8 (*)
  *         @arg @ref HAL_PWR_WAKEUP_SOURCE_ALL
  * @note   (*) : Not available on all devices.
  */
void HAL_PWR_LP_CleanWakeupSource(uint32_t wakeup_source)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_SOURCE(wakeup_source));

  LL_PWR_ClearFlag_WU(wakeup_source);
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group2 RTC domain write protection management functions
  * @{
  This section provides functions allowing to manage RTC domain access:
  - Call HAL_PWR_EnableRTCDomainWriteProtection() to enable RTC domain write protection.
  - Call HAL_PWR_DisableRTCDomainWriteProtection() to disable RTC domain write protection.
  - Call HAL_PWR_IsEnabledRTCDomainWriteProtection() to check that RTC domain write protection is enabled.
  */

/**
  * @brief  Enable the RTC domain write protection (RCC RTC domain control register RCC_RTCCR, RTC registers,
  *         TAMP registers, backup registers and backup SRAM).
  */
void HAL_PWR_EnableRTCDomainWriteProtection(void)
{
  LL_PWR_EnableRTCDomainWriteProtection();
}

/**
  * @brief  Disable the RTC domain write protection (RCC RTC domain control register RCC_RTCCR, RTC registers,
  *         TAMP registers, backup registers and backup SRAM).
  * @note   After a system reset, the RTC domain is protected against possible unwanted write accesses.
  */
void HAL_PWR_DisableRTCDomainWriteProtection(void)
{
  LL_PWR_DisableRTCDomainWriteProtection();
}

/**
  * @brief  Check that RTC domain access is enabled.
  * @retval HAL_PWR_RTC_DOMAIN_WRP_DISABLED RTC domain write protection disabled.
  * @retval HAL_PWR_RTC_DOMAIN_WRP_ENABLED  RTC domain write protection enabled.
  */
hal_pwr_rtc_domain_wrp_status_t HAL_PWR_IsEnabledRTCDomainWriteProtection(void)
{
  return ((hal_pwr_rtc_domain_wrp_status_t)LL_PWR_IsEnabledRTCDomainWriteProtection());
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group3 Main regulator management functions
  * @{
  This section provides functions allowing to control power supply.
  - Call HAL_PWR_SetMainRegulatorSupply() function to configure the main regulator supply.
  - Call HAL_PWR_GetMainRegulatorSupply() function to get the main regulator supply configuration.
  - Call HAL_PWR_GetMainRegulatorSupplyStatus() function to get the main regulator supply status.
  - Call HAL_PWR_SetMainRegulatorVoltageScalingRange() function to configure voltage scaling range.
  - Call HAL_PWR_GetMainRegulatorVoltageScalingRange() function to get voltage scaling range configuration.
  - Call HAL_PWR_GetMainRegulatorActiveVoltageScalingRange() function to get active voltage scaling range.
  */

/**
  * @brief   Set the regulator voltage scaling range.
  * @param   range     This parameter is an element of @ref hal_pwr_volt_scale_range_t enumeration.
  * @note After reset, the system starts from HSI with VOS2.
  * @note When using the voltage scaling range 2, the system frequency can go up to 170 MHz
  * @note When using the voltage scaling range 1, the system frequency can go up to 240 MHz.
  * @note When using the voltage scaling range 0, the system frequency can go up to 280 MHz.
  * @warning To increase the frequency, first increase the VOS to a higher level (VOS0 > VOS1 > VOS2).
  * @warning To decrease the frequency, first decrease the system frequency, then set the VOS to a lower level.
  * @warning When bypassing the internal regulator, we must ensure that SRAM operation speed has correctly adjusted.
  * @retval  HAL_ERROR VOS setting timeout.
  * @retval  HAL_OK    Regulator voltage scaling range has been correctly configured.
  */
hal_status_t HAL_PWR_SetMainRegulatorVoltageScalingRange(hal_pwr_volt_scale_range_t range)
{
  uint32_t timeout = ((PWR_VOS_SELECT_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
  uint32_t vos = 0U;
  uint32_t actvos = 0U;
  uint32_t sramls = 0U;
  uint32_t sramspeed = LL_PWR_SRAM_HIGH_SPEED;

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
    /* Compute final expected SRAM Operation speed */
    if ((uint32_t)range == LL_PWR_REGU_VOLT_SCALE_2)
    {
      sramspeed = LL_PWR_SRAM_LOW_SPEED;
    }

    /* Polling on SRAMLS flag */
    do
    {
      sramls = LL_PWR_GetSRAMOperationSpeed();
      timeout--;
    } while ((sramls != sramspeed) && (timeout != 0U));
  }

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief   Get the configured voltage scaling range.
  * @retval  Returns hal_pwr_volt_scale_range_t enumeration value.
  *          @arg @ref HAL_PWR_VOLT_SCALE_0
  *          @arg @ref HAL_PWR_VOLT_SCALE_1
  *          @arg @ref HAL_PWR_VOLT_SCALE_2
  */
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorVoltageScalingRange(void)
{
  return ((hal_pwr_volt_scale_range_t)LL_PWR_GetRegulatorVoltageScaling());
}

/**
  * @brief   Get the active regulator voltage scaling range.
  * @warning When bypassing the internal regulator, VOS and ACTVOS are not functional. Instead, SRAMLS gives us the
  *          SRAM operation speed information, which can be used to determine the effective VOS. If the SRAM is in Low
  *          Speed mode, VOS is VOS2. If the SRAM is in High Speed mode, the VOS is either equal to VOS0 or VOS1.
  * @retval  Returns hal_pwr_volt_scale_range_t enumeration value.
  *          @arg @ref HAL_PWR_VOLT_SCALE_0
  *          @arg @ref HAL_PWR_VOLT_SCALE_1
  *          @arg @ref HAL_PWR_VOLT_SCALE_2
  * @warning When bypassing the internal regulator, the API returns exclusively HAL_PWR_VOLT_SCALE_0 or
  *          HAL_PWR_VOLT_SCALE_2.
  */
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorActiveVoltageScalingRange(void)
{
  uint32_t actvos = 0U;

  if (LL_PWR_IsEnabledBypass() == LL_PWR_MAIN_REGU_SUPPLY_NOT_BYPASSED)
  {
    /* get ACTVOS register content */
    actvos = LL_PWR_GetActiveRegulatorVoltageScaling();

    /* Convert it in hal_pwr_volt_scale_range_t value */
    actvos = ((actvos >> LL_PWR_ACTIVE_VOLT_SCALE_POS) << LL_PWR_REGU_VOLT_SCALE_POS);
  }
  else
  {
    /* Check SRAM operation speed */
    if (LL_PWR_GetSRAMOperationSpeed() == LL_PWR_SRAM_LOW_SPEED)
    {
      /* In Low Speed mode, VOS is always equal to VOS2 */
      actvos = (uint32_t)HAL_PWR_VOLT_SCALE_2;
    }
    else
    {
      /* In High Speed mode, VOS either is equal to VOS0 or VOS1 */
      actvos = (uint32_t)HAL_PWR_VOLT_SCALE_0;
    }
  }

  return (hal_pwr_volt_scale_range_t)actvos;
}

/**
  * @brief  Set the system supply regulator configuration.
  * @param  regulator This parameter is an element of @ref hal_pwr_main_regulator_supply_t enumeration.
  * @note   When bypassing the internal regulator, the VOS and ACTVOS flags are not functional. Instead, SRAMLS gives us
  *         the SRAM operation speed information, which can be used to determine the effective VOS.
  * @warning This API is only compatible with non-SMPS packages.
  * @retval HAL_OK    System supply regulator has been correctly configured.
  */
hal_status_t HAL_PWR_SetMainRegulatorSupply(hal_pwr_main_regulator_supply_t regulator)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_MAIN_REGULATOR_SUPPLY(regulator));

  if (regulator == HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASS)
  {
    LL_PWR_EnableBypass();
  }

  return HAL_OK;
}

/**
  * @brief  Get the system supply regulator configuration.
  * @retval Element of @ref hal_pwr_main_regulator_supply_t enumeration.
  */
hal_pwr_main_regulator_supply_t HAL_PWR_GetMainRegulatorSupply(void)
{
  return (hal_pwr_main_regulator_supply_t)LL_PWR_IsEnabledBypass();
}

/**
  * @brief  Get the system supply regulator currently used.
  * @retval Element of @ref hal_pwr_main_regulator_supply_status_t enumeration.
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
#if defined(PWR_SCCR_SMPSEN)
    /* Check if the SMPS is enabled, otherwise return LDO */
    if (LL_PWR_IsEnabledSMPSSupply() == 1U)
    {
      regulator = HAL_PWR_MAIN_REGULATOR_SUPPLY_SMPS;
    }
    else
#endif /* PWR_SCCR_SMPSEN */
    {
      regulator = HAL_PWR_MAIN_REGULATOR_SUPPLY_LDO;
    }
  }

  return regulator;
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group4 Low power mode management functions
  * @{
  This section provides functions allowing to manage low power modes:
  - Call HAL_PWR_ClearCorePendingEvent() function to clear the internal cortex event before entering low power mode.
  - Call HAL_PWR_EnterSleepMode() function to enter the Core in sleep mode.
  - Call HAL_PWR_EnterStopMode() function to enter the MCU in stop x mode
  - Call HAL_PWR_EnterStandbyMode() function to enter the MCU in standby mode.
  - Call HAL_PWR_SetCoreSleepMode() function to configure the Core in sleep or deep sleep mode.
  - Call HAL_PWR_GetCoreSleepMode() function to get Core sleep mode configuration.
  - Call HAL_PWR_EnableCoreSleepOnExit() function to enable Core to re-entry in sleep mode after an interrupt is over.
  - Call HAL_PWR_DisableCoreSleepOnExit() function to disable Core to re-entry in sleep mode after an interrupt is over.
  - Call HAL_PWR_IsEnabledCoreSleepOnExit() function to check Core to re-entry in sleep mode after an interrupt status.
  - Call HAL_PWR_EnableCoreSendEventOnPending() function to enable Core to wakeup after any pending event/ interrupt.
  - Call HAL_PWR_DisableCoreSendEventOnPending() function to disable Core to wakeup after any pending event/ interrupt.
  - Call HAL_PWR_IsEnabledCoreSendEventOnPending() function to check that core send event on pending is enabled.
  - Call HAL_PWR_GetPreviousSystemPowerMode() function to get the previous system power mode.
  - Call HAL_PWR_CleanPreviousSystemPowerMode() function to clean the previous system power mode.
  */

/**
  * @brief   Clear core pending event.
  * @note    This API clears the pending event in order to enter a given core to Sleep or Stop mode with WFE entry.
  * @warning It must be called just before APIs performing enter Sleep and Stop mode using Wait For Event request
  */
void HAL_PWR_ClearCorePendingEvent(void)
{
  __SEV();
  __WFE();
}

/**
  * @brief  Enter the core in Sleep mode.
  * @param  sleep_entry Parameter to @ref hal_pwr_low_pwr_mode_entry_t enumeration.
  */
void HAL_PWR_EnterSleepMode(hal_pwr_low_pwr_mode_entry_t sleep_entry)
{
  ASSERT_DBG_PARAM(IS_PWR_LP_MODE_ENTRY(sleep_entry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  SCB_DisableDeepSleep();

  /* DSB to ensure there are no outstanding memory transactions prior to executing WFI/WFE and going to sleep. */
  __DSB();

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
  * @brief  Enter the MCU in Stop mode.
  * @param  stop_entry This parameter is an element of @ref hal_pwr_low_pwr_mode_entry_t enumeration.
  * @param  stop_mode  This parameter is an element of @ref hal_pwr_stop_mode_t enumeration.
  * @warning The system clock when exiting from Stop mode is HSI up to 64 MHz, depending on software configuration.
  */
void HAL_PWR_EnterStopMode(hal_pwr_low_pwr_mode_entry_t stop_entry, hal_pwr_stop_mode_t stop_mode)
{
  ASSERT_DBG_PARAM(IS_PWR_LP_MODE_ENTRY(stop_entry));
  ASSERT_DBG_PARAM(IS_PWR_STOP_MODE(stop_mode));

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB_EnableDeepSleep();

  LL_PWR_SetPowerMode((uint32_t)stop_mode);

  /* DSB to ensure there are no outstanding memory transactions prior to executing WFI/WFE and going to stop. */
  __DSB();

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
  * @warning The system clock after wake-up is HSI at 64 MHz.
  */
void HAL_PWR_EnterStandbyMode(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB_EnableDeepSleep();

  LL_PWR_SetPowerMode(LL_PWR_STANDBY_MODE);

  /* DSB to ensure there are no outstanding memory transactions prior to executing WFI/WFE and going to standby. */
  __DSB();

  /* Wait For Interrupt Request */
  __WFI();
}

/**
  * @brief  Set the core sleep mode configuration.
  * @param  sleep_mode This parameter is an element of @ref hal_pwr_core_sleep_mode_t enumeration.
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
  * @retval HAL_PWR_CORE_SLEEP      Core sleep mode.
  * @retval HAL_PWR_CORE_DEEP_SLEEP Core deep sleep mode.
  */
hal_pwr_core_sleep_mode_t HAL_PWR_GetCoreSleepMode(void)
{
  return ((hal_pwr_core_sleep_mode_t)(SCB_IsEnabledDeepSleep()));
}

/**
  * @brief  Enable SLEEP-ON-EXIT feature when returning from handler mode to thread mode.
  */
void HAL_PWR_EnableCoreSleepOnExit(void)
{
  SCB_EnableSleepOnExit();
}

/**
  * @brief  Disable SLEEP-ON-EXIT feature when returning from handler mode to thread mode.
  */
void HAL_PWR_DisableCoreSleepOnExit(void)
{
  SCB_DisableSleepOnExit();
}

/**
  * @brief  Check if the Core SLEEP-ON-EXIT is enabled or disabled.
  * @retval hal_pwr_core_sleep_on_exit_status_t Core sleep on exit status.
  */
hal_pwr_core_sleep_on_exit_status_t HAL_PWR_IsEnabledCoreSleepOnExit(void)
{
  return ((hal_pwr_core_sleep_on_exit_status_t)(SCB_IsEnabledSleepOnExit()));
}

/**
  * @brief  Enable core Send Event On Pending feature.
  */
void HAL_PWR_EnableCoreSendEventOnPending(void)
{
  SCB_EnableEventOnPend();
}

/**
  * @brief  Disable core Send Event On Pending.
  */
void HAL_PWR_DisableCoreSendEventOnPending(void)
{
  SCB_DisableEventOnPend();
}

/**
  * @brief  Get core Send Event On Pending.
  * @retval HAL_PWR_CORE_SEV_ON_PENDING_DISABLED Core send event on pending disabled.
  * @retval HAL_PWR_CORE_SEV_ON_PENDING_ENABLED  Core send event on pending enabled.
  */
hal_pwr_core_sev_on_pending_status_t HAL_PWR_IsEnabledCoreSendEventOnPending(void)
{
  return ((hal_pwr_core_sev_on_pending_status_t)(SCB_IsEnabledEventOnPend()));
}

/**
  * @brief  Get the previous system power mode.
  * @retval hal_pwr_system_mode_t Previous power mode.
  * @note   Sleep mode is an ARM core mode and not a system power mode as it does not affect system clock on return
  *          from sleep, so it is not reported by this function.
  * @warning This function is expected to be called on return from low power mode so to take the necessary actions
  *           such as re-enabling clocks automatically disabled during low power mode.
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
  *           HAL_PWR_GetPreviousSystemPowerMode() will return the right information on return from low power mode.
  * @warning This function clears both standby and stop flags.
  */
void HAL_PWR_CleanPreviousSystemPowerMode(void)
{
  LL_PWR_ClearFlag_SB();
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group5 Voltage monitoring management functions
  * @{
  This section provides functions allowing to configure voltage monitoring.
  - Call HAL_PWR_SetProgrammableVoltageDetectorLevel() function to configure the programmable voltage detector.
  - Call HAL_PWR_GetProgrammableVoltageDetectorLevel() function to get the programmable voltage detector configuration.
  - Call HAL_PWR_EnableProgrammableVoltageDetector() function to enable the Programmable Voltage Detector.
  - Call HAL_PWR_DisableProgrammableVoltageDetector() function to disable the programmable voltage detector.
  - Call HAL_PWR_IsEnabledProgrammableVoltageDetector() function to check the programmable voltage detector status.
  - Call HAL_PWR_GetProgrammableVoltageDetectorOutput() function to get the programmable voltage detector output.
  - Call HAL_PWR_SetAnalogVoltageDetectorLevel() function to configure the analog voltage detector.
  - Call HAL_PWR_GetAnalogVoltageDetectorLevel() function to get the analog voltage detector configuration
  - Call HAL_PWR_EnableAnalogVoltageDetector() function to enable the analog voltage detector.
  - Call HAL_PWR_DisableAnalogVoltageDetector() function to disable the analog voltage detector.
  - Call HAL_PWR_IsEnabledAnalogVoltageDetector() function to check the analog voltage detector status.
  - Call HAL_PWR_GetAnalogVoltageDetectorOutput() function to get the analog voltage detector output
  - Call HAL_PWR_EnableTemperatureVddMonitor() function to enable the voltage monitor by the Peripheral Voltage
    Monitoring.
  - Call HAL_PWR_DisableTemperatureVddMonitor() function to disable the voltage monitor by the Peripheral Voltage
    Monitoring.
  - Call HAL_PWR_IsEnabledTemperatureVddMonitor() function to check the voltage monitor status.
  - Call HAL_PWR_GetTemperatureLevelStatus() function to get the temperature monitor output.
  - Call HAL_PWR_GetVddVoltageLevelStatus() function to get the Vdd voltage monitor output.
  */

/**
  * @brief  Set the voltage threshold detection by the Programmable Voltage Detector (PVD).
  * @param  level This parameter is an element of @ref hal_pwr_pvd_level_t enumeration.
  */
void HAL_PWR_SetProgrammableVoltageDetectorLevel(hal_pwr_pvd_level_t level)
{
  ASSERT_DBG_PARAM(IS_PWR_PVD_LEVEL(level));

  LL_PWR_SetPVDLevel((uint32_t)level);
}

/**
  * @brief  Get the voltage threshold detection by the Programmable Voltage Detector (PVD).
  * @retval The currently configured PVD level.
  */
hal_pwr_pvd_level_t HAL_PWR_GetProgrammableVoltageDetectorLevel(void)
{
  return ((hal_pwr_pvd_level_t)LL_PWR_GetPVDLevel());
}

/**
  * @brief  Enable the voltage threshold detection by the Programmable Voltage Detector (PVD).
  */
void HAL_PWR_EnableProgrammableVoltageDetector(void)
{
  LL_PWR_EnablePVD();
}

/**
  * @brief  Disable the voltage threshold detection by the Programmable Voltage Detector (PVD).
  */
void HAL_PWR_DisableProgrammableVoltageDetector(void)
{
  LL_PWR_DisablePVD();
}

/**
  * @brief  Check if the programmable voltage detection is enabled.
  * @retval HAL_PWR_PVD_DISABLED Programmable voltage detection disabled.
  * @retval HAL_PWR_PVD_ENABLED  Programmable voltage detection enabled.
  */
hal_pwr_pvd_status_t HAL_PWR_IsEnabledProgrammableVoltageDetector(void)
{
  return ((hal_pwr_pvd_status_t)LL_PWR_IsEnabledPVD());
}

/**
  * @brief  Provide the current PVD output.
  * @retval HAL_PWR_PVD_OUT_EQ_HIGH_THR VDD is equal or higher than programmable voltage detector threshold.
  * @retval HAL_PWR_PVD_OUT_LOW_THR  VDD is lower than programmable voltage detector threshold.
  */
hal_pwr_pvd_out_t HAL_PWR_GetProgrammableVoltageDetectorOutput(void)
{
  return (hal_pwr_pvd_out_t)LL_PWR_IsActiveFlag_PVDO();
}

/**
  * @brief  Set the voltage threshold detection by the Analog Voltage Detector (AVD).
  * @param  level This parameter is an element of @ref hal_pwr_avd_level_t enumeration.
  */
void HAL_PWR_SetAnalogVoltageDetectorLevel(hal_pwr_avd_level_t level)
{
  ASSERT_DBG_PARAM(IS_PWR_AVD_LEVEL(level));

  LL_PWR_SetAVDLevel((uint32_t)level);
}

/**
  * @brief  Get the voltage threshold detection by the Analog Voltage Detector (AVD).
  * @retval The currently configured AVD level.
  */
hal_pwr_avd_level_t HAL_PWR_GetAnalogVoltageDetectorLevel(void)
{
  return ((hal_pwr_avd_level_t)LL_PWR_GetAVDLevel());
}

/**
  * @brief  Enable the voltage threshold detection by the Analog Voltage Detector (AVD).
  */
void HAL_PWR_EnableAnalogVoltageDetector(void)
{
  LL_PWR_EnableAVD();
}

/**
  * @brief  Disable the voltage threshold detection by the Analog Voltage Detector (AVD).
  */
void HAL_PWR_DisableAnalogVoltageDetector(void)
{
  LL_PWR_DisableAVD();
}

/**
  * @brief  Check if the Analog voltage detection is enabled.
  * @retval HAL_PWR_AVD_DISABLED Analog voltage detection disabled.
  * @retval HAL_PWR_AVD_ENABLED  Analog voltage detection enabled.
  */
hal_pwr_avd_status_t HAL_PWR_IsEnabledAnalogVoltageDetector(void)
{
  return ((hal_pwr_avd_status_t)LL_PWR_IsEnabledAVD());
}

/**
  * @brief  Provide the current AVD output.
  * @retval HAL_PWR_AVD_OUT_EQ_HIGH_THR VDD is equal or higher than analog voltage detector threshold.
  * @retval HAL_PWR_AVD_OUT_LOW_THR  VDD is lower than analog voltage detector threshold.
  */
hal_pwr_avd_out_t HAL_PWR_GetAnalogVoltageDetectorOutput(void)
{
  return (hal_pwr_avd_out_t)LL_PWR_IsActiveFlag_AVDO();
}

/**
  * @brief  Enable the voltage monitor by the Peripheral Voltage Monitoring (PVM).
  */
void HAL_PWR_EnableTemperatureVddMonitor(void)
{
  LL_PWR_EnableTemperatureVddMonitor();
}

/**
  * @brief  Disable the voltage monitor by the Peripheral Voltage Monitoring (PVM).
  */
void HAL_PWR_DisableTemperatureVddMonitor(void)
{
  LL_PWR_DisableTemperatureVddMonitor();
}

/**
  * @brief  Check if the voltage monitoring is enabled.
  * @retval HAL_PWR_MONITOR_DISABLED Voltage monitoring disabled.
  * @retval HAL_PWR_MONITOR_ENABLED  Voltage monitoring enabled.
  */
hal_pwr_monitor_status_t HAL_PWR_IsEnabledTemperatureVddMonitor(void)
{
  return ((hal_pwr_monitor_status_t)LL_PWR_IsEnabledTemperatureVddMonitor());
}

/**
  * @brief  Get the temperature level monitoring.
  * @retval Returned value is an element of @ref hal_pwr_temp_level_t enumeration.
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
  * @brief  Get the VDD voltage level monitoring.
  * @retval Returned value is an element of @ref hal_pwr_vdd_level_t enumeration.
  */
hal_pwr_vdd_level_t HAL_PWR_GetVddVoltageLevelStatus(void)
{
  if (LL_PWR_IsActiveFlag_VDDH() != 0U)
  {
    return HAL_PWR_VDD_LEVEL_EQ_HIGH_THR;
  }
  else
  {
    return HAL_PWR_VDD_LEVEL_LOW_THR;
  }
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group6 Memory Retention management functions
  * @{
 This section provides functions allowing to manage memory content retention.
 - Call HAL_PWR_LP_EnableMemoryRetention() function to enable memory Retention.
 - Call HAL_PWR_LP_DisableMemoryRetention() function to disable memory Retention.
 - Call HAL_PWR_LP_IsEnabledMemoryRetention() to check the selected memory retention status.
 - Call HAL_PWR_LP_EnableMemoryPageRetention() function to enable memory retention for selected pages.
 - Call HAL_PWR_LP_DisableMemoryPageRetention() function to disable memory retention for selected pages.
 - Call HAL_PWR_LP_IsEnabledMemoryPageRetention() function to get the selected memory page retention status.
  */

/**
  * @brief  Enable memory retention in stop mode.
  * @param  memory This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @retval HAL_OK Memory retention has been correctly enabled.
  * @retval HAL_INVALID_PARAM The selected memory does not exist.
  * @retval HAL_ERROR Memory retention could not be enabled, the selected memory is paginated.
  */
hal_status_t HAL_PWR_LP_EnableMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_SINGLE_PAGE_MEMORY_RETENTION(memory));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check if the selected memory exists */
  if ((uint32_t)memory >= PWR_MEMORY_BANKS_NUMBER)
  {
    /* Selected memory does not exist */
    return HAL_INVALID_PARAM;
  }
  else
#endif /* USE_HAL_CHECK_PARAM */
  {
    /* Check if the selected memory is paginated or not */
    if (PWR_MemoryMaxPagesRetentionMap[memory] == 1U)
    {
      /* Enable Memory Retention */
      LL_PWR_EnableMemoryStopRetention(PWR_MemoryFullRetentionMap[memory]);
      return HAL_OK;
    }
    else
    {
      /* Paginated SRAM are managed by HAL_PWR_LP_EnableMemoryPageRetention() */
      return HAL_ERROR;
    }
  }
}

/**
  * @brief  Disable memory retention in stop mode.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @retval HAL_OK  Memory retention has been correctly disabled.
  * @retval HAL_INVALID_PARAM The selected memory does not exist.
  * @retval HAL_ERROR Memory retention could not be disabled, the selected memory is paginated.
  */
hal_status_t HAL_PWR_LP_DisableMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_SINGLE_PAGE_MEMORY_RETENTION(memory));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check if the selected memory exists */
  if ((uint32_t)memory >= PWR_MEMORY_BANKS_NUMBER)
  {
    /* Selected memory does not exist */
    return HAL_INVALID_PARAM;
  }
  else
#endif /* USE_HAL_CHECK_PARAM */
  {
    /* Check if the selected memory is paginated or not */
    if (PWR_MemoryMaxPagesRetentionMap[memory] == 1U)
    {
      /* Disable Memory Retention */
      LL_PWR_DisableMemoryStopRetention(PWR_MemoryFullRetentionMap[memory]);
      return HAL_OK;
    }
    else
    {
      /* Paginated SRAM are managed by HAL_PWR_LP_DisableMemoryPageRetention() */
      return HAL_ERROR;
    }
  }
}

/**
  * @brief  Get memory retention status.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @retval HAL_PWR_MEMORY_RETENTION_DISABLED if the selected memory is not retained in stop mode.
  * @retval HAL_PWR_MEMORY_RETENTION_ENABLED  if the selected memory is retained in stop mode.
  * @note   If the ASSERT are disabled, HAL_PWR_MEMORY_RETENTION_DISABLED is returned for paginated memories.
  */
hal_pwr_memory_retention_status_t HAL_PWR_LP_IsEnabledMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_SINGLE_PAGE_MEMORY_RETENTION(memory));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check if the selected memory exists */
  if ((uint32_t)memory >= PWR_MEMORY_BANKS_NUMBER)
  {
    /* Selected memory does not exist */
    return HAL_PWR_MEMORY_RETENTION_DISABLED;
  }
  else
#endif /* USE_HAL_CHECK_PARAM */
  {
    if (PWR_MemoryMaxPagesRetentionMap[memory] == 1U)
    {
      /* Return the selected memory retention status */
      return ((hal_pwr_memory_retention_status_t)
              LL_PWR_IsEnabledMemoryStopRetention(PWR_MemoryFullRetentionMap[memory]));
    }
    else
    {
      /* Paginated SRAM are managed by HAL_PWR_LP_IsEnabledMemoryPageRetention() */
      return HAL_PWR_MEMORY_RETENTION_DISABLED;
    }
  }
}

/**
  * @brief  Enable memory page retention in stop mode.
  * @param  memory    This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @param  page_idx  the index of memory page.
  * @param  page_nbr  The memory pages number.
  * @retval HAL_OK    Memory pages retention has been correctly enabled.
  * @retval HAL_INVALID_PARAM The selected memory does not exist, the page index is out of range or the selected number
  *         of pages does not fit the memory.
  * @retval HAL_ERROR Memory page retention could not be enabled, the selected memory is not paginated.
  */
hal_status_t HAL_PWR_LP_EnableMemoryPageRetention(hal_pwr_memory_retention_t memory,
                                                  uint32_t page_idx,
                                                  uint32_t page_nbr)
{
  uint32_t pages = 0;
  uint32_t logical_idx = 0;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_PWR_MEMORY_PAGES_RETENTION((uint32_t)memory, page_idx, page_nbr));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check if the selected memory exists, the page index is valid and if the selected number of pages fits the memory */
  if (((uint32_t)memory >= PWR_MEMORY_BANKS_NUMBER)
      || (page_idx > PWR_MemoryMaxPagesRetentionMap[memory])
      || (((page_idx - 1U) + page_nbr) > PWR_MemoryMaxPagesRetentionMap[memory]))
  {
    status = HAL_INVALID_PARAM;
  }
  else
#endif /* USE_HAL_CHECK_PARAM */
  {
    if (PWR_MemoryMaxPagesRetentionMap[memory] != 1U)
    {
      for (uint32_t i = 0; i < page_nbr; ++i)
      {
        logical_idx = page_idx + i;
        switch (logical_idx)
        {
          /* SRAM2 Page 1 */
          case 1:
          {
            pages |= LL_PWR_SRAM2_PAGE1_STOP_RETENTION;
            break;
          }

          /* SRAM2 Page 2 */
          case 2:
          {
            pages |= LL_PWR_SRAM2_PAGE2_STOP_RETENTION;
            break;
          }

          default:
          {
            /* Out-of-range cases */
            status = HAL_ERROR;
            break;
          }
        }
      }

      /* If no error occurred, enable the pages stop retention */
      if (status == HAL_OK)
      {
        /* Pages stop retention enabling */
        LL_PWR_EnableSRAM2PagesStopRetention(pages);
      }
    }
    else
    {
      /* Non paginated SRAM are managed by HAL_PWR_LP_EnableMemoryRetention() */
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Disable memory page retention in stop mode.
  * @param  memory    This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @param  page_idx  the index of memory page.
  * @param  page_nbr  The memory pages number.
  * @retval HAL_OK    Memory pages retention has been correctly disabled.
  * @retval HAL_INVALID_PARAM The selected memory does not exist, the page index is out of range or the selected number
  *         of pages does not fit the memory.
  * @retval HAL_ERROR Memory page retention could not be disabled, the selected memory is not paginated.
  */
hal_status_t HAL_PWR_LP_DisableMemoryPageRetention(hal_pwr_memory_retention_t memory,
                                                   uint32_t page_idx,
                                                   uint32_t page_nbr)
{
  uint32_t pages = 0;
  uint32_t logical_idx = 0;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_PWR_MEMORY_PAGES_RETENTION((uint32_t)memory, page_idx, page_nbr));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check if the selected memory exists, the page index is valid and if the selected number of pages fits the memory */
  if (((uint32_t)memory >= PWR_MEMORY_BANKS_NUMBER)
      || (page_idx > PWR_MemoryMaxPagesRetentionMap[memory])
      || (((page_idx - 1U) + page_nbr) > PWR_MemoryMaxPagesRetentionMap[memory]))
  {
    status = HAL_INVALID_PARAM;
  }
  else
#endif /* USE_HAL_CHECK_PARAM */
  {
    if (PWR_MemoryMaxPagesRetentionMap[memory] != 1U)
    {
      for (uint32_t i = 0; i < page_nbr; ++i)
      {
        logical_idx = page_idx + i;
        switch (logical_idx)
        {
          /* SRAM2 Page 1 */
          case 1:
          {
            pages |= LL_PWR_SRAM2_PAGE1_STOP_RETENTION;
            break;
          }

          /* SRAM2 Page 2 */
          case 2:
          {
            pages |= LL_PWR_SRAM2_PAGE2_STOP_RETENTION;
            break;
          }

          default:
          {
            /* Out-of-range cases */
            status = HAL_ERROR;
            break;
          }
        }
      }

      /* If no error occurred, disable the pages stop retention */
      if (status == HAL_OK)
      {
        /* Pages stop retention disabling */
        LL_PWR_DisableSRAM2PagesStopRetention(pages);
      }
    }
    else
    {
      /* Non paginated SRAM are managed by HAL_PWR_LP_DisableMemoryRetention() */
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Check the selected memory page retention in stop mode status.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @param  page_idx  the index of memory page.
  * @retval HAL_PWR_MEMORY_PAGE_RETENTION_DISABLED if the selected memory page is not retained in stop mode.
  * @retval HAL_PWR_MEMORY_PAGE_RETENTION_ENABLED  if the selected memory page is retained in stop mode.
  */
hal_pwr_memory_page_retention_status_t HAL_PWR_LP_IsEnabledMemoryPageRetention(hal_pwr_memory_retention_t memory,
                                                                               uint32_t page_idx)
{
  hal_pwr_memory_page_retention_status_t status = HAL_PWR_MEMORY_PAGE_RETENTION_DISABLED;
  uint32_t page = 0;

  ASSERT_DBG_PARAM(IS_PWR_MEMORY_PAGES_RETENTION((uint32_t)memory, page_idx, 1U));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check if the selected memory exists, the page index is valid and if the selected number of pages fits the memory */
  if (((uint32_t)memory >= PWR_MEMORY_BANKS_NUMBER)
      || (page_idx > PWR_MemoryMaxPagesRetentionMap[memory]))
  {
    /* Selected SRAM bank is not valid */
    status = HAL_PWR_MEMORY_PAGE_RETENTION_DISABLED;
  }
  else
#endif /* USE_HAL_CHECK_PARAM */
  {
    if (PWR_MemoryMaxPagesRetentionMap[memory] != 1U)
    {
      switch (page_idx)
      {
        /* SRAM2 Page 1 */
        case 1:
        {
          page = LL_PWR_SRAM2_PAGE1_STOP_RETENTION;
          break;
        }

        /* SRAM2 Page 2 */
        case 2:
        {
          page = LL_PWR_SRAM2_PAGE2_STOP_RETENTION;
          break;
        }

        default:
        {
          /* Ignore out-of-range cases */
          break;
        }
      }

      /* Get memory page retention status */
      if ((LL_PWR_IsEnabledSRAM2PagesStopRetention(page) != 0UL) && (page != 0UL))
      {
        status = HAL_PWR_MEMORY_PAGE_RETENTION_ENABLED;
      }
    }
  }

  return status;
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group7 Memory management functions
  * @{
 This section provides functions allowing to manage Flash memory low power modes.
 - Call HAL_PWR_LP_EnableFlashLowPWRMode() function to enable Flash memory power down in Stop 0/1 Mode.
 - Call HAL_PWR_LP_DisableFlashLowPWRMode() function to disable Flash memory power down in Stop 0/1 Mode.
 - Call HAL_PWR_LP_IsEnabledFlashLowPWRMode() function to check the Flash memory power down in Stop 0/1 Mode status.
  */
/**
  * @brief  Enable the Flash low power mode.
  */
void HAL_PWR_LP_EnableFlashLowPWRMode(void)
{
  LL_PWR_EnableFlashLowPWRMode();
}

/**
  * @brief  Disable the Flash low power mode.
  */
void HAL_PWR_LP_DisableFlashLowPWRMode(void)
{
  LL_PWR_DisableFlashLowPWRMode();
}

/**
  * @brief  Check if the Flash low power mode is enabled or disabled.
  * @retval hal_pwr_Flash_low_pwr_mode_status_t Flash low power mode status.
  */
hal_pwr_flash_low_pwr_mode_status_t HAL_PWR_LP_IsEnabledFlashLowPWRMode(void)
{
  return (hal_pwr_flash_low_pwr_mode_status_t)LL_PWR_IsEnabledFlashLowPWRMode();
}
/**
  * @}
  */

#if defined(PWR_USBSCR_USB33SV)
/** @addtogroup PWR_Exported_Functions_Group8 USB power supply management functions
  * @{
  This section provides functions allowing to manage USB power supply.
  - Call HAL_PWR_EnableVddUSBIndependentSupply() function to enable the USB power supply
    and disable electrical isolation.
  - Call HAL_PWR_DisableVddUSBIndependentSupply() function to disable the USB power supply
    and enable electrical isolation.
  - Call HAL_PWR_IsEnabledVddUSBIndependentSupply() function to check if the USB power supply
    is enabled.

  */

/**
  * @brief  Enable the USB power supply and disable logical and electrical isolation.
  * @retval HAL_OK    System supply regulator has been correctly configured.
  */
hal_status_t  HAL_PWR_EnableVddUSBIndependentSupply(void)
{
  LL_PWR_EnableUSBSupply();

  return HAL_OK;
}

/**
  * @brief  Disable the USB power supply and enable logical and electrical isolation.
  */
void HAL_PWR_DisableVddUSBIndependentSupply(void)
{
  LL_PWR_DisableUSBSupply();
}

/**
  * @brief  Get the USB power supply status.
  * @retval hal_pwr_usb_supply_status_t enumeration value
  */
hal_pwr_usb_supply_status_t HAL_PWR_IsEnabledVddUSBIndependentSupply(void)
{
  return ((hal_pwr_usb_supply_status_t)LL_PWR_IsEnabledUSBSupply());
}
/**
  * @}
  */
#endif /* PWR_USBSCR_USB33SV */

#if defined(PWR_UCPDR_UCPD_DBDIS) || defined(PWR_UCPDR_UCPD_STBY)
/** @addtogroup PWR_Exported_Functions_Group9 UCPD management functions
  * @{
  This section provides functions allowing to manage battery charging and configuration retention..
  - Call HAL_PWR_LP_EnableUCPDDeadBattery() function to enable the UCPD dead battery behavior.
  - Call HAL_PWR_LP_DisableUCPDDeadBattery() function to disable the UCPD dead battery behavior.
  - Call HAL_PWR_LP_IsEnabledUCPDDeadBattery() function to check the UCPD dead battery behavior status.
  - Call HAL_PWR_LP_EnableUCPDRetention() function to enable the UCPD configuration retention in Standby mode.
  - Call HAL_PWR_LP_DisableUCPDRetention() function to disable the UCPD configuration retention in Standby mode.
  - Call HAL_PWR_LP_IsEnabledUCPDRetention() function to check the UCPD configuration retention in Standby mode status.
  */

#if defined(PWR_UCPDR_UCPD_DBDIS)
/**
  * @brief  Enable dead battery behavior.
  * @note   After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *         on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *         handover control to the UCPD (the UCPD must be initialized before doing the disable).
  */
void HAL_PWR_LP_EnableUCPDDeadBattery(void)
{
  LL_PWR_EnableUCPDDeadBattery();
}

/**
  * @brief  Disable dead battery behavior.
  * @note   After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *         on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *         handover control to the UCPD (the UCPD must be initialized before doing the disable).
  */
void HAL_PWR_LP_DisableUCPDDeadBattery(void)
{
  LL_PWR_DisableUCPDDeadBattery();
}

/**
  * @brief  Check dead battery behavior.
  * @note   After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *         on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *         handover control to the UCPD (the UCPD must be initialized before doing the disable).
  * @retval HAL_PWR_DEAD_BATTERY_MODE_DISABLED  Disable USB Type-C dead battery pull-down behavior
  * @retval HAL_PWR_DEAD_BATTERY_MODE_ENABLED   Enable USB Type-C dead battery pull-down behavior
  */
hal_pwr_dead_battery_mode_status_t HAL_PWR_LP_IsEnabledUCPDDeadBattery(void)
{
  return (hal_pwr_dead_battery_mode_status_t)(LL_PWR_IsEnabledUCPDDeadBattery());
}
#endif /* PWR_UCPDR_UCPD_DBDIS */

#if defined(PWR_UCPDR_UCPD_STBY)
/**
  * @brief  Enable UCPD configuration memorization in Standby mode.
  * @note   This function must be called on exiting the Standby mode and before any UCPD configuration update.
  */
void HAL_PWR_LP_EnableUCPDRetention(void)
{
  LL_PWR_EnableUCPDRetentionStandbyMode();
}

/**
  * @brief  Disable UCPD configuration memorization in Standby mode.
  * @note   This function must be called on exiting the Standby mode and before any UCPD configuration update.
  */
void HAL_PWR_LP_DisableUCPDRetention(void)
{
  LL_PWR_DisableUCPDRetentionStandbyMode();
}

/**
  * @brief  Check the UCPD configuration memorization in Standby mode.
  * @note   This function must be called on exiting the Standby mode and before any UCPD configuration update.
  * @retval HAL_PWR_UCPD_RETENTION_ENABLED
  * @retval HAL_PWR_UCPD_RETENTION_DISABLED
  */
hal_pwr_ucpd_retention_status_t HAL_PWR_LP_IsEnabledUCPDRetention(void)
{
  return ((hal_pwr_ucpd_retention_status_t)LL_PWR_IsEnabledUCPDRetentionStandbyMode());
}
#endif /* PWR_UCPDR_UCPD_STBY */
/**
  * @}
  */
#endif /* PWR_UCPDR_UCPD_DBDIS || PWR_UCPDR_UCPD_STBY */

/** @addtogroup PWR_Exported_Functions_Group10 I/O Retention management functions
  * @{
  This section provides functions allowing to manage power IO retention in low power mode.
  - Call HAL_PWR_LP_EnableIORetention() function to enable the IO (GPIO and/or JTAGIO) retention in Standby mode.
  - Call HAL_PWR_LP_DisableIORetention() function to disable the IO (GPIO and/or JTAGIO) retention in Standby mode.
  - Call HAL_PWR_LP_IsEnabledIORetention() function to check if the IO (GPIO or JTAGIO) retention in Standby mode
    is enabled or disabled.
  */

/**
  * @brief  Enable the IO retention in Standby mode.
  * @param  io This parameter is an element or combination of elements of @ref hal_pwr_io_retention_t enumeration.
  * @note   The output is sampled, and apply to the output IO during the Standby mode.
  */
void HAL_PWR_LP_EnableIORetention(hal_pwr_io_retention_t io)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_IO_RETENTION(io));

  if (((uint32_t)io & (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO) == (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO)
  {
    LL_PWR_EnableJTAGIORetentionStandbyMode();
  }

  if (((uint32_t)io & (uint32_t)HAL_PWR_IO_RETENTION_GPIO) == (uint32_t)HAL_PWR_IO_RETENTION_GPIO)
  {
    LL_PWR_EnableIORetentionStandbyMode();
  }
}

/**
  * @brief  Disable the IO retention in Standby mode.
  * @param  io This parameter is an element or combination of elements of @ref hal_pwr_io_retention_t enumeration.
  *       @arg @ref HAL_PWR_IO_RETENTION_JTAGIO IO Retention mode is enabled for JTAG I/Os (PA13, PA14, PA15, and PB4).
  *       @arg @ref HAL_PWR_IO_RETENTION_GPIO   IO Retention mode is enabled for all I/Os except the I/Os supporting.
  */
void HAL_PWR_LP_DisableIORetention(hal_pwr_io_retention_t io)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_IO_RETENTION(io));

  if (((uint32_t)io & (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO) == (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO)
  {
    LL_PWR_DisableJTAGIORetentionStandbyMode();
  }

  if (((uint32_t)io & (uint32_t)HAL_PWR_IO_RETENTION_GPIO) == (uint32_t)HAL_PWR_IO_RETENTION_GPIO)
  {
    LL_PWR_DisableIORetentionStandbyMode();
  }
}

/**
  * @brief  Check if the IO retention in Standby mode is enabled or disabled.
  * @param  io This parameter is an element of @ref hal_pwr_io_retention_t enumeration.
  *       @arg @ref HAL_PWR_IO_RETENTION_JTAGIO IO Retention mode is enabled for JTAG I/Os (PA13, PA14, PA15, and PB4).
  *       @arg @ref HAL_PWR_IO_RETENTION_GPIO   IO Retention mode is enabled for all I/Os except the I/Os supporting.
  * @return @ref hal_pwr_io_retention_status_t  The IO retention status.
  */
hal_pwr_io_retention_status_t HAL_PWR_LP_IsEnabledIORetention(hal_pwr_io_retention_t io)
{
  hal_pwr_io_retention_status_t status = HAL_PWR_IO_RETENTION_DISABLED;

  ASSERT_DBG_PARAM(IS_PWR_GET_IO_RETENTION(io));

  if (io == HAL_PWR_IO_RETENTION_JTAGIO)
  {
    status = (hal_pwr_io_retention_status_t)LL_PWR_IsEnabledJTAGIORetentionStandbyMode();
  }

  if (io == HAL_PWR_IO_RETENTION_GPIO)
  {
    status = (hal_pwr_io_retention_status_t)LL_PWR_IsEnabledIORetentionStandbyMode();
  }

  return status;
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group11 Privilege management functions
  * @{
  This section provides functions allowing to manage privilege mode.
  - Call HAL_PWR_SetPrivAttr() function to configure the privilege mode for the selected item.
  - Call HAL_PWR_GetPrivAttr() function to get the privilege mode for the selected item
  */
/**
  * @brief  Set privilege attribute.
  * @param  item The item attribute to be configured.
  * @param  priv_attr This parameter is an element of @ref hal_pwr_priv_attr_t enumeration:
  *         @arg @ref HAL_PWR_PRIV   Privileged attribute.
  *         @arg @ref HAL_PWR_NPRIV  Unprivileged attribute.
  * @retval HAL_ERROR  The function is called in unprivileged mode.
  * @retval HAL_OK     Privilege attribute has been correctly set.
  */
hal_status_t HAL_PWR_SetPrivAttr(uint32_t item, hal_pwr_priv_attr_t priv_attr)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_PRIV_ITEM(item));

  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }

  LL_PWR_SetPrivAttr(item, (uint32_t)priv_attr);

  return HAL_OK;
}

/**
  * @brief  Get privilege attribute.
  * @param  item The item attribute to be queried.
  * @retval hal_pwr_priv_attr_t This parameter is an element of @ref hal_pwr_priv_attr_t enumeration.
  */
hal_pwr_priv_attr_t HAL_PWR_GetPrivAttr(uint32_t item)
{
  ASSERT_DBG_PARAM(IS_PWR_GET_PRIV_ITEM(item));

  return ((hal_pwr_priv_attr_t)LL_PWR_GetPrivAttr(item));
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group12 Secure management functions
  * @{
  This section provides functions allowing to manage secure mode.
  - Call HAL_PWR_SetSecAttr() function to configure the secure mode for the selected item
  - Call HAL_PWR_GetSecAttr() function to get the secure mode for the selected item
  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set secure attribute for the selected item.
  * @param  item The item attribute to be configured.
  * @param  sec_attr This parameter is an element of @ref hal_pwr_sec_attr_t enumeration:
  *         @arg @ref HAL_PWR_SEC   Secure attribute.
  *         @arg @ref HAL_PWR_NSEC  Non-Secure attribute.
  * @note   The register is write-protected against unprivileged write accesses when SPRIV = 1 in the PWR_PRIVCFGR.
  * @retval HAL_ERROR  The function is called in unprivileged mode while the register is write-protected on Non-secure
  *                    write access.
  * @retval HAL_OK     Privilege attribute has been correctly set.
  */
hal_status_t HAL_PWR_SetSecAttr(uint32_t item, hal_pwr_sec_attr_t sec_attr)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_SEC_ITEM(item));

  uint32_t priv_attr = LL_PWR_GetPrivAttr(LL_PWR_PRIV_ITEM_SPRIV);

  if ((STM32_IS_PRIVILEGED_EXECUTION() == 0U) && (priv_attr == LL_PWR_ATTR_PRIV))
  {
    return HAL_ERROR;
  }

  LL_PWR_SetSecAttr(item, (uint32_t)sec_attr);

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get secure attribute for the selected item.
  * @param  item The item attribute to be queried.
  * @retval hal_pwr_sec_attr_t This parameter is an element of @ref hal_pwr_sec_attr_t enumeration.
  */
hal_pwr_sec_attr_t HAL_PWR_GetSecAttr(uint32_t item)
{
  ASSERT_DBG_PARAM(IS_PWR_GET_SEC_ITEM(item));

  return ((hal_pwr_sec_attr_t)LL_PWR_GetSecAttr(item));
}
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

/**
  * @}
  */
