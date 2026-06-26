/**
  **********************************************************************************************************************
  * @file    stm32g5xx_hal_pwr.h
  * @brief   Header file of PWR HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32G5XX_HAL_PWR_H
#define STM32G5XX_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_pwr.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */
#if defined (PWR)
/** @defgroup PWR PWR
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Exported_Types PWR Exported Types
  * @{
  */

/*! HAL PWR wakeup pin polarity enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_POLARITY_LOW  = LL_PWR_WAKEUP_PIN_POLARITY_LOW,  /*!< Wakeup pin low polarity  */
  HAL_PWR_WAKEUP_PIN_POLARITY_HIGH = LL_PWR_WAKEUP_PIN_POLARITY_HIGH  /*!< Wakeup pin high polarity */
} hal_pwr_wakeup_pin_polarity_t;

/*! HAL PWR wakeup pin pull configuration enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_PULL_NO   = LL_PWR_WAKEUP_PIN_PULL_NO,  /*!< Wakeup pin no pull   */
  HAL_PWR_WAKEUP_PIN_PULL_UP   = LL_PWR_WAKEUP_PIN_PULL_UP,  /*!< Wakeup pin pull up   */
  HAL_PWR_WAKEUP_PIN_PULL_DOWN = LL_PWR_WAKEUP_PIN_PULL_DOWN /*!< Wakeup pin pull down */
} hal_pwr_wakeup_pin_pull_t;

/*! HAL PWR wakeup pin status enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_DISABLED = 0U, /*!< Wakeup pin disabled */
  HAL_PWR_WAKEUP_PIN_ENABLED  = 1U  /*!< Wakeup pin enabled  */
} hal_pwr_wakeup_pin_status_t;

/*! HAL PWR wakeup pin configuration structure definition */
typedef struct
{
  hal_pwr_wakeup_pin_polarity_t polarity; /*!< Wakeup pin polarity */
  hal_pwr_wakeup_pin_pull_t     pull;     /*!< Wakeup pin pull     */
} hal_pwr_wakeup_pin_config_t;

/*! HAL PWR RTC domain write protection status enumeration definition */
typedef enum
{
  HAL_PWR_RTC_DOMAIN_WRP_DISABLED = 0U, /*!< RTC domain write protection disabled */
  HAL_PWR_RTC_DOMAIN_WRP_ENABLED  = 1U  /*!< RTC domain write protection enabled  */
} hal_pwr_rtc_domain_wrp_status_t;

/*! HAL PWR voltage scale range enumeration definition */
typedef enum
{
  HAL_PWR_VOLT_SCALE_0 = LL_PWR_REGU_VOLT_SCALE_0, /*!< Voltage scale range 0 */
  HAL_PWR_VOLT_SCALE_1 = LL_PWR_REGU_VOLT_SCALE_1, /*!< Voltage scale range 1 */
  HAL_PWR_VOLT_SCALE_2 = LL_PWR_REGU_VOLT_SCALE_2  /*!< Voltage scale range 2 */
} hal_pwr_volt_scale_range_t;

/*! HAL PWR main regulator source configuration enumeration definition */
typedef enum
{
  HAL_PWR_MAIN_REGULATOR_SUPPLY_NOT_BYPASS  = LL_PWR_MAIN_REGU_SUPPLY_NOT_BYPASSED, /*!< PWR SMPS / LDO regulators
                                                                                           are not bypassed */
  HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASS      = LL_PWR_MAIN_REGU_SUPPLY_BYPASSED      /*!< PWR SMPS / LDO regulators
                                                                                           are bypassed */
} hal_pwr_main_regulator_supply_t;

/*! HAL PWR main regulator source enumeration definition */
typedef enum
{
  HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASSED      = LL_PWR_MAIN_REGU_SUPPLY_BYPASSED,     /*!< PWR SMPS / LDO regulators
                                                                                           are bypassed */
#if defined(PWR_SCCR_SMPSEN)
  HAL_PWR_MAIN_REGULATOR_SUPPLY_SMPS          = LL_PWR_MAIN_REGU_SUPPLY_SMPS_ENABLED, /*!< PWR SMPS is the main
                                                                                           regulator supply */
#endif /* PWR_SCCR_SMPSEN */
  HAL_PWR_MAIN_REGULATOR_SUPPLY_LDO           = LL_PWR_MAIN_REGU_SUPPLY_LDO_ENABLED,  /*!< PWR LDO is the main
                                                                                           regulator supply */
} hal_pwr_main_regulator_supply_status_t;

/*! HAL PWR low power mode entry request enumeration definition */
typedef enum
{
  HAL_PWR_LOW_PWR_MODE_WFE = 0U, /*!< Low power mode wait for event request     */
  HAL_PWR_LOW_PWR_MODE_WFI = 1U  /*!< Low power mode wait for interrupt request */
} hal_pwr_low_pwr_mode_entry_t;

/*! HAL PWR Stop mode enumeration definition */
typedef enum
{
  HAL_PWR_STOP_MODE = LL_PWR_STOP_MODE /*!< Stop mode */
} hal_pwr_stop_mode_t;

/*! HAL PWR system power mode enumeration definition */
typedef enum
{
  HAL_PWR_SYSTEM_RUN_MODE     = 0xFFU,              /*!< System was in Run mode     */
  HAL_PWR_SYSTEM_STOP_MODE    = LL_PWR_STOP_MODE,   /*!< System was in Stop mode    */
  HAL_PWR_SYSTEM_STANDBY_MODE = LL_PWR_STANDBY_MODE /*!< System was in Standby mode */
} hal_pwr_system_mode_t;

/*! HAL PWR core sleep enumeration definition */
typedef enum
{
  HAL_PWR_CORE_SLEEP      = 0U, /*!< Core sleep mode      */
  HAL_PWR_CORE_DEEP_SLEEP = 1U  /*!< Core deep sleep mode */
} hal_pwr_core_sleep_mode_t;

/*! HAL PWR core sleep enumeration definition */
typedef enum
{
  HAL_PWR_CORE_SLEEP_ON_EXIT_DISABLED = 0U, /*!< PWR Core sleep on exit disabled */
  HAL_PWR_CORE_SLEEP_ON_EXIT_ENABLED  = 1U  /*!< PWR Core sleep on exit enabled  */
} hal_pwr_core_sleep_on_exit_status_t;

/*! HAL PWR core send event on pending status enumeration definition */
typedef enum
{
  HAL_PWR_CORE_SEV_ON_PENDING_DISABLED = 0U, /*!< Core send event on pending disabled */
  HAL_PWR_CORE_SEV_ON_PENDING_ENABLED  = 1U  /*!< Core send event on pending enabled  */
} hal_pwr_core_sev_on_pending_status_t;

/*! HAL PWR power voltage detector level enumeration definition */
typedef enum
{
  HAL_PWR_PVD_VDD_LEVEL_0   = LL_PWR_PVD_VDD_LEVEL_0,  /*!< Voltage threshold detected by PVD
                                                              Rising edge typical :   2.85V
                                                              Falling edge typical :  2.75V    */
  HAL_PWR_PVD_VDD_LEVEL_1   = LL_PWR_PVD_VDD_LEVEL_1,  /*!< Voltage threshold detected by PVD
                                                              Rising edge typical :   3.05V
                                                              Falling edge typical :  2.95V    */
  HAL_PWR_PVD_PVDIN_VREFINT = LL_PWR_PVD_PVDIN_VREFINT /*!< External input on PVD_IN pin,
                                                            compared to internal VREFINT level */
} hal_pwr_pvd_level_t;

/*! HAL PWR programmable voltage detector status enumeration definition */
typedef enum
{
  HAL_PWR_PVD_DISABLED = 0U, /*!< PWR PVD disabled */
  HAL_PWR_PVD_ENABLED  = 1U  /*!< PWR PVD enabled  */
} hal_pwr_pvd_status_t;

/*! HAL PWR programmable voltage detector output enumeration definition */
typedef enum
{
  HAL_PWR_PVD_OUT_EQ_HIGH_THR = 0U, /*!< VDD equal to or higher than programmable voltage detector threshold  */
  HAL_PWR_PVD_OUT_LOW_THR     = 1U  /*!< VDD lower than programmable voltage detector threshold               */
} hal_pwr_pvd_out_t;

/*! HAL PWR analog voltage detector level enumeration definition */
typedef enum
{
  HAL_PWR_AVD_VDDA_LEVEL_0 = LL_PWR_AVD_VDDA_LEVEL_0, /*!< Voltage threshold detected by AVD
                                                             Rising edge typical :   2.80V
                                                             Falling edge typical :  2.74V */
  HAL_PWR_AVD_VDDA_LEVEL_1 = LL_PWR_AVD_VDDA_LEVEL_1, /*!< Voltage threshold detected by AVD
                                                             Rising edge typical :   3.00V
                                                             Falling edge typical :  2.94V */
} hal_pwr_avd_level_t;

/*! HAL PWR analog voltage detector status enumeration definition */
typedef enum
{
  HAL_PWR_AVD_DISABLED = 0U, /*!< PWR AVD disabled */
  HAL_PWR_AVD_ENABLED  = 1U  /*!< PWR AVD enabled  */
} hal_pwr_avd_status_t;

/*! HAL PWR analog voltage detector output enumeration definition */
typedef enum
{
  HAL_PWR_AVD_OUT_EQ_HIGH_THR = 0U, /*!< VDDA equal to or higher than analog voltage detector threshold  */
  HAL_PWR_AVD_OUT_LOW_THR     = 1U  /*!< VDDA lower than analog voltage detector threshold               */
} hal_pwr_avd_out_t;

/*! HAL PWR power voltage monitor status definition */
typedef enum
{
  HAL_PWR_MONITOR_DISABLED = 0U, /*!< Monitoring disabled */
  HAL_PWR_MONITOR_ENABLED  = 1U   /*!< Monitoring enabled  */
} hal_pwr_monitor_status_t;

/*! HAL PWR temperature level definition */
typedef enum
{
  HAL_PWR_TEMP_LEVEL_BETWEEN_THR = 0U, /*!< PWR Temperature between low and high thresholds */
  HAL_PWR_TEMP_LEVEL_EQ_HIGH_THR = 1U, /*!< PWR Temperature equal or above high threshold   */
  HAL_PWR_TEMP_LEVEL_EQ_LOW_THR  = 2U  /*!< PWR Temperature equal or below low threshold    */
} hal_pwr_temp_level_t;

/*! HAL PWR VDD voltage level definition */
typedef enum
{
  HAL_PWR_VDD_LEVEL_LOW_THR = 0U,     /*!< PWR VDD voltage below high thresholds          */
  HAL_PWR_VDD_LEVEL_EQ_HIGH_THR = 1U, /*!< PWR VDD voltage equal or above high threshold  */
} hal_pwr_vdd_level_t;

/*! HAL PWR memory retention enumeration definition */
typedef enum
{
  HAL_PWR_MEMORY_RETENTION_SRAM1_STOP = 0U,  /*!< SRAM1 memory retention in Stop mode  */
  HAL_PWR_MEMORY_RETENTION_SRAM2_STOP = 1U,  /*!< SRAM2 memory retention in Stop mode  */
#if defined(SRAM3_BASE)
  HAL_PWR_MEMORY_RETENTION_SRAM3_STOP = 2U,  /*!< SRAM3 memory retention in Stop mode  */
#endif /* SRAM3_BASE */
} hal_pwr_memory_retention_t;

/*! HAL PWR memory retention status enumeration definition */
typedef enum
{
  HAL_PWR_MEMORY_RETENTION_DISABLED = 0U, /*!< Memory retention in Stop mode disabled */
  HAL_PWR_MEMORY_RETENTION_ENABLED  = 1U  /*!< Memory retention in Stop mode enabled  */
} hal_pwr_memory_retention_status_t;

/*! HAL PWR memory page retention status enumeration definition */
typedef enum
{
  HAL_PWR_MEMORY_PAGE_RETENTION_DISABLED = 0U, /*!< Memory page retention in Stop mode disabled */
  HAL_PWR_MEMORY_PAGE_RETENTION_ENABLED  = 1U  /*!< Memory page retention in Stop mode enabled  */
} hal_pwr_memory_page_retention_status_t;

/*! HAL PWR FLASH memory low power mode status enumeration definition */
typedef enum
{
  HAL_PWR_FLASH_LOW_PWR_MODE_DISABLED = 0U, /*!< PWR FLASH memory low power mode disabled */
  HAL_PWR_FLASH_LOW_PWR_MODE_ENABLED  = 1U  /*!< PWR FLASH memory low power mode enabled  */
} hal_pwr_flash_low_pwr_mode_status_t;

/*! HAL PWR USB supply status enumeration definition */
typedef enum
{
  HAL_PWR_USB_SUPPLY_DISABLED = 0U, /*!< USB power supply disabled */
  HAL_PWR_USB_SUPPLY_ENABLED  = 1U  /*!< USB power supply enabled  */
} hal_pwr_usb_supply_status_t;

/*! HAL PWR USB Type-c and Power delivery Standby mode enumeration definition */
typedef enum
{
  HAL_PWR_UCPD_RETENTION_DISABLED = 0U, /*!< UCPD configuration retention in Standby mode disabled */
  HAL_PWR_UCPD_RETENTION_ENABLED  = 1U  /*!< UCPD configuration retention in Standby mode enabled  */
} hal_pwr_ucpd_retention_status_t;

/*! HAL PWR USB Type-C and power delivery dead battery mode status enumeration definition */
typedef enum
{
  HAL_PWR_DEAD_BATTERY_MODE_DISABLED = 0U, /*!< USB Type-c and Power delivery dead battery mode disabled */
  HAL_PWR_DEAD_BATTERY_MODE_ENABLED  = 1U  /*!< USB Type-c and Power delivery dead battery mode enabled  */
} hal_pwr_dead_battery_mode_status_t;

/*! HAL PWR IO retention selection enumeration definition */
typedef enum
{
  HAL_PWR_IO_RETENTION_JTAGIO = 1U, /*!< PWR JTAGIO retention enabled               */
  HAL_PWR_IO_RETENTION_GPIO   = 2U, /*!< PWR GPIO retention enabled                 */
  HAL_PWR_IO_RETENTION_ALL    = 3U  /*!< PWR both JTAGIO and GPIO retention enabled */
} hal_pwr_io_retention_t;

/*! HAL PWR IO retention configuration status enumeration definition */
typedef enum
{
  HAL_PWR_IO_RETENTION_DISABLED = 0U, /*!< IO retention mode disabled */
  HAL_PWR_IO_RETENTION_ENABLED  = 1U  /*!< IO retention mode enabled  */
} hal_pwr_io_retention_status_t;
/**
  * @}
  */

/*! HAL PWR privilege attribute enumeration definition  */
typedef enum
{
  HAL_PWR_NPRIV = LL_PWR_ATTR_NPRIV,  /*!< Non-privileged attribute */
  HAL_PWR_PRIV  = LL_PWR_ATTR_PRIV    /*!< Privileged attribute     */
} hal_pwr_priv_attr_t;

/*! HAL PWR secure attribute enumeration definition */
typedef enum
{
  HAL_PWR_NSEC = LL_PWR_ATTR_NSEC,  /*!< Non-secure attribute */
  HAL_PWR_SEC  = LL_PWR_ATTR_SEC    /*!< Privileged attribute */
} hal_pwr_sec_attr_t;

/* Exported constants -----------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_wakeup_pin PWR wakeup pin definition
  * @{
  */

#define HAL_PWR_WAKEUP_PIN_1   LL_PWR_WAKEUP_PIN_1   /*!< Wakeup pin 1   */
#define HAL_PWR_WAKEUP_PIN_2   LL_PWR_WAKEUP_PIN_2   /*!< Wakeup pin 2   */
#define HAL_PWR_WAKEUP_PIN_4   LL_PWR_WAKEUP_PIN_4   /*!< Wakeup pin 4   */
#define HAL_PWR_WAKEUP_PIN_5   LL_PWR_WAKEUP_PIN_5   /*!< Wakeup pin 5   */
#define HAL_PWR_WAKEUP_PIN_6   LL_PWR_WAKEUP_PIN_6   /*!< Wakeup pin 6   */
#define HAL_PWR_WAKEUP_PIN_7   LL_PWR_WAKEUP_PIN_7   /*!< Wakeup pin 7   */
#if defined(PWR_WUCR_WUPEN8)
#define HAL_PWR_WAKEUP_PIN_8   LL_PWR_WAKEUP_PIN_8   /*!< Wakeup pin 8   */
#endif /* defined(PWR_WUCR_WUPEN8) */
#define HAL_PWR_WAKEUP_PIN_ALL LL_PWR_WAKEUP_PIN_ALL /*!< Wakeup pin all */
/**
  * @}
  */

/** @defgroup PWR_wakeup_source PWR wakeup source definition
  * @{
  */

#define HAL_PWR_WAKEUP_SOURCE_1   LL_PWR_WAKEUP_PIN_1   /*!< Wakeup source 1   */
#define HAL_PWR_WAKEUP_SOURCE_2   LL_PWR_WAKEUP_PIN_2   /*!< Wakeup source 2   */
#define HAL_PWR_WAKEUP_SOURCE_4   LL_PWR_WAKEUP_PIN_4   /*!< Wakeup source 4   */
#define HAL_PWR_WAKEUP_SOURCE_5   LL_PWR_WAKEUP_PIN_5   /*!< Wakeup source 5   */
#define HAL_PWR_WAKEUP_SOURCE_6   LL_PWR_WAKEUP_PIN_6   /*!< Wakeup source 6   */
#define HAL_PWR_WAKEUP_SOURCE_7   LL_PWR_WAKEUP_PIN_7   /*!< Wakeup source 7   */
#if defined(PWR_WUCR_WUPEN8)
#define HAL_PWR_WAKEUP_SOURCE_8   LL_PWR_WAKEUP_PIN_8   /*!< Wakeup source 8   */
#endif /* defined(PWR_WUCR_WUPEN8) */
#define HAL_PWR_WAKEUP_SOURCE_ALL LL_PWR_WAKEUP_PIN_ALL /*!< Wakeup source all */
/**
  * @}
  */

/** @defgroup PWR_privilege_items PWR privilege items definition
  * @{
  */
#define HAL_PWR_PRIV_ITEM_SPRIV   LL_PWR_PRIV_ITEM_SPRIV  /*!< Secure privilege item      */
#define HAL_PWR_PRIV_ITEM_NSPRIV  LL_PWR_PRIV_ITEM_NSPRIV /*!< Non-Secure privilege items */
#define HAL_PWR_PRIV_ITEM_ALL     LL_PWR_PRIV_ITEM_ALL    /*!< All privilege items        */
/**
  * @}
  */

/** @defgroup PWR_secure_items PWR secure items definition
  * @{
  */
#define HAL_PWR_SEC_ITEM_WUP1   LL_PWR_SEC_ITEM_WUP1SEC /*!< Wake up pin 1 secure mode                  */
#define HAL_PWR_SEC_ITEM_WUP2   LL_PWR_SEC_ITEM_WUP2SEC /*!< Wake up pin 2 secure mode                  */
#define HAL_PWR_SEC_ITEM_WUP4   LL_PWR_SEC_ITEM_WUP4SEC /*!< Wake up pin 4 secure mode                  */
#define HAL_PWR_SEC_ITEM_WUP5   LL_PWR_SEC_ITEM_WUP5SEC /*!< Wake up pin 5 secure mode                  */
#define HAL_PWR_SEC_ITEM_WUP6   LL_PWR_SEC_ITEM_WUP6SEC /*!< Wake up pin 6 secure mode                  */
#define HAL_PWR_SEC_ITEM_WUP7   LL_PWR_SEC_ITEM_WUP7SEC /*!< Wake up pin 7 secure mode                  */
#if defined(PWR_WUCR_WUPEN8)
#define HAL_PWR_SEC_ITEM_WUP8   LL_PWR_SEC_ITEM_WUP8SEC /*!< Wake up pin 8 secure mode                  */
#endif /* defined(PWR_WUCR_WUPEN8) */
#define HAL_PWR_SEC_ITEM_RET    LL_PWR_SEC_ITEM_RETSEC  /*!< Retention secure mode                      */
#define HAL_PWR_SEC_ITEM_LPM    LL_PWR_SEC_ITEM_LPMSEC  /*!< Low-power modes secure mode                */
#define HAL_PWR_SEC_ITEM_SCM    LL_PWR_SEC_ITEM_SCMSEC  /*!< Supply configuration and monitoring secure */
#define HAL_PWR_SEC_ITEM_RTC    LL_PWR_SEC_ITEM_RTCSEC  /*!< RTC domain secure mode                     */
#if defined(PWR_USBSCR_USB33SV)
#define HAL_PWR_SEC_ITEM_VUSB   LL_PWR_SEC_ITEM_VUSBSEC /*!< Voltage USB secure mode                    */
#endif /* defined(PWR_USBSCR_USB33SV) */
#define HAL_PWR_SEC_ITEM_ALL    LL_PWR_SEC_ITEM_ALL     /*!< All secure items                           */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1 Wakeup pins management functions
  * @{
  */
hal_status_t HAL_PWR_LP_SetConfigWakeupPin(uint32_t wakeup_pin, const hal_pwr_wakeup_pin_config_t *p_config);
void HAL_PWR_LP_GetConfigWakeupPin(uint32_t wakeup_pin, hal_pwr_wakeup_pin_config_t *p_config);
void HAL_PWR_LP_EnableWakeupPin(uint32_t wakeup_pin);
void HAL_PWR_LP_DisableWakeupPin(uint32_t wakeup_pin);
hal_pwr_wakeup_pin_status_t HAL_PWR_LP_IsEnabledWakeupPin(uint32_t wakeup_pin);
uint32_t HAL_PWR_LP_GetWakeupSource(void);
void HAL_PWR_LP_CleanWakeupSource(uint32_t wakeup_source);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group2 RTC domain write protection management functions
  * @{
  */
void HAL_PWR_EnableRTCDomainWriteProtection(void);
void HAL_PWR_DisableRTCDomainWriteProtection(void);
hal_pwr_rtc_domain_wrp_status_t HAL_PWR_IsEnabledRTCDomainWriteProtection(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group3 Main regulator management functions
  * @{
  */
hal_status_t HAL_PWR_SetMainRegulatorVoltageScalingRange(hal_pwr_volt_scale_range_t range);
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorVoltageScalingRange(void);
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorActiveVoltageScalingRange(void);

hal_status_t HAL_PWR_SetMainRegulatorSupply(hal_pwr_main_regulator_supply_t regulator);
hal_pwr_main_regulator_supply_t HAL_PWR_GetMainRegulatorSupply(void);
hal_pwr_main_regulator_supply_status_t HAL_PWR_GetMainRegulatorSupplyStatus(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group4 Low power mode management functions
  * @{
  */
void HAL_PWR_ClearCorePendingEvent(void);
void HAL_PWR_EnterSleepMode(hal_pwr_low_pwr_mode_entry_t sleep_entry);
void HAL_PWR_EnterStopMode(hal_pwr_low_pwr_mode_entry_t stop_entry, hal_pwr_stop_mode_t stop_mode);
void HAL_PWR_EnterStandbyMode(void);
void HAL_PWR_SetCoreSleepMode(hal_pwr_core_sleep_mode_t sleep_mode);
hal_pwr_core_sleep_mode_t HAL_PWR_GetCoreSleepMode(void);

void HAL_PWR_EnableCoreSleepOnExit(void);
void HAL_PWR_DisableCoreSleepOnExit(void);
hal_pwr_core_sleep_on_exit_status_t HAL_PWR_IsEnabledCoreSleepOnExit(void);
void HAL_PWR_EnableCoreSendEventOnPending(void);
void HAL_PWR_DisableCoreSendEventOnPending(void);
hal_pwr_core_sev_on_pending_status_t HAL_PWR_IsEnabledCoreSendEventOnPending(void);

hal_pwr_system_mode_t HAL_PWR_GetPreviousSystemPowerMode(void);
void HAL_PWR_CleanPreviousSystemPowerMode(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group5 Voltage monitoring management functions
  * @{
  */
void HAL_PWR_SetProgrammableVoltageDetectorLevel(hal_pwr_pvd_level_t level);
hal_pwr_pvd_level_t HAL_PWR_GetProgrammableVoltageDetectorLevel(void);
void HAL_PWR_EnableProgrammableVoltageDetector(void);
void HAL_PWR_DisableProgrammableVoltageDetector(void);
hal_pwr_pvd_status_t HAL_PWR_IsEnabledProgrammableVoltageDetector(void);
hal_pwr_pvd_out_t HAL_PWR_GetProgrammableVoltageDetectorOutput(void);

void HAL_PWR_SetAnalogVoltageDetectorLevel(hal_pwr_avd_level_t level);
hal_pwr_avd_level_t HAL_PWR_GetAnalogVoltageDetectorLevel(void);
void HAL_PWR_EnableAnalogVoltageDetector(void);
void HAL_PWR_DisableAnalogVoltageDetector(void);
hal_pwr_avd_status_t HAL_PWR_IsEnabledAnalogVoltageDetector(void);
hal_pwr_avd_out_t HAL_PWR_GetAnalogVoltageDetectorOutput(void);

void HAL_PWR_EnableTemperatureVddMonitor(void);
void HAL_PWR_DisableTemperatureVddMonitor(void);
hal_pwr_monitor_status_t HAL_PWR_IsEnabledTemperatureVddMonitor(void);
hal_pwr_temp_level_t HAL_PWR_GetTemperatureLevelStatus(void);
hal_pwr_vdd_level_t HAL_PWR_GetVddVoltageLevelStatus(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group6 Memory Retention management functions
  * @{
  */
hal_status_t HAL_PWR_LP_EnableMemoryRetention(hal_pwr_memory_retention_t memory);
hal_status_t HAL_PWR_LP_DisableMemoryRetention(hal_pwr_memory_retention_t memory);
hal_pwr_memory_retention_status_t HAL_PWR_LP_IsEnabledMemoryRetention(hal_pwr_memory_retention_t memory);
hal_status_t HAL_PWR_LP_EnableMemoryPageRetention(hal_pwr_memory_retention_t memory,
                                                  uint32_t page_idx,
                                                  uint32_t page_nbr);
hal_status_t HAL_PWR_LP_DisableMemoryPageRetention(hal_pwr_memory_retention_t memory,
                                                   uint32_t page_idx,
                                                   uint32_t page_nbr);
hal_pwr_memory_page_retention_status_t HAL_PWR_LP_IsEnabledMemoryPageRetention(hal_pwr_memory_retention_t memory,
                                                                               uint32_t page_idx);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group7 Memory management functions
  * @{
  */
void HAL_PWR_LP_EnableFlashLowPWRMode(void);
void HAL_PWR_LP_DisableFlashLowPWRMode(void);
hal_pwr_flash_low_pwr_mode_status_t HAL_PWR_LP_IsEnabledFlashLowPWRMode(void);
/**
  * @}
  */

#if defined(PWR_USBSCR_USB33SV)
/** @defgroup PWR_Exported_Functions_Group8 USB power supply management functions
  * @{
  */
hal_status_t HAL_PWR_EnableVddUSBIndependentSupply(void);
void HAL_PWR_DisableVddUSBIndependentSupply(void);
hal_pwr_usb_supply_status_t HAL_PWR_IsEnabledVddUSBIndependentSupply(void);
/**
  * @}
  */
#endif /* defined(PWR_USBSCR_USB33SV) */

#if defined(PWR_UCPDR_UCPD_DBDIS) || defined(PWR_UCPDR_UCPD_STBY)
/** @defgroup PWR_Exported_Functions_Group9 UCPD management functions
  * @{
  */
#if defined(PWR_UCPDR_UCPD_DBDIS)
void HAL_PWR_LP_EnableUCPDDeadBattery(void);
void HAL_PWR_LP_DisableUCPDDeadBattery(void);
hal_pwr_dead_battery_mode_status_t HAL_PWR_LP_IsEnabledUCPDDeadBattery(void);
#endif /* defined(PWR_UCPDR_UCPD_DBDIS) */
#if defined(PWR_UCPDR_UCPD_STBY)
void HAL_PWR_LP_EnableUCPDRetention(void);
void HAL_PWR_LP_DisableUCPDRetention(void);
hal_pwr_ucpd_retention_status_t HAL_PWR_LP_IsEnabledUCPDRetention(void);
#endif /* defined(PWR_UCPDR_UCPD_STBY) */
/**
  * @}
  */
#endif /* defined(PWR_UCPDR_UCPD_DBDIS) || defined(PWR_UCPDR_UCPD_STBY) */

/** @defgroup PWR_Exported_Functions_Group10 I/O Retention management functions
  * @{
  */
void HAL_PWR_LP_EnableIORetention(hal_pwr_io_retention_t io);
void HAL_PWR_LP_DisableIORetention(hal_pwr_io_retention_t io);
hal_pwr_io_retention_status_t HAL_PWR_LP_IsEnabledIORetention(hal_pwr_io_retention_t io);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group11 Privilege management functions
  * @{
  */
hal_status_t HAL_PWR_SetPrivAttr(uint32_t item, hal_pwr_priv_attr_t priv_attr);
hal_pwr_priv_attr_t HAL_PWR_GetPrivAttr(uint32_t item);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group12 Secure management functions
  * @{
  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_PWR_SetSecAttr(uint32_t item, hal_pwr_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_pwr_sec_attr_t HAL_PWR_GetSecAttr(uint32_t item);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* PWR */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_HAL_PWR_H */
