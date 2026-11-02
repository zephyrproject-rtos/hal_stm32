/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_pwr.h
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
#ifndef STM32H7PXX_HAL_PWR_H
#define STM32H7PXX_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_pwr.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
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

/*! HAL PWR wake-up pin polarity enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_POLARITY_LOW  = LL_PWR_WAKEUP_PIN_POLARITY_LOW, /*!< Wake-up pin low polarity  */
  HAL_PWR_WAKEUP_PIN_POLARITY_HIGH = LL_PWR_WAKEUP_PIN_POLARITY_HIGH /*!< Wake-up pin high polarity */
} hal_pwr_wakeup_pin_polarity_t;

/*! HAL PWR wake-up pin pull configuration enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_PULL_NO   = LL_PWR_WAKEUP_PIN_PULL_NO,  /*!< Wake-up pin no pull   */
  HAL_PWR_WAKEUP_PIN_PULL_UP   = LL_PWR_WAKEUP_PIN_PULL_UP,  /*!< Wake-up pin pull-up   */
  HAL_PWR_WAKEUP_PIN_PULL_DOWN = LL_PWR_WAKEUP_PIN_PULL_DOWN /*!< Wake-up pin pull-down */
} hal_pwr_wakeup_pin_pull_t;

/*! HAL PWR wake-up pin status enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_DISABLED = 0U, /*!< Wake-up pin disabled */
  HAL_PWR_WAKEUP_PIN_ENABLED  = 1U  /*!< Wake-up pin enabled  */
} hal_pwr_wakeup_pin_status_t;

/*! HAL PWR wake-up pin configuration structure definition */
typedef struct
{
  hal_pwr_wakeup_pin_polarity_t polarity; /*!< Wake-up pin polarity */
  hal_pwr_wakeup_pin_pull_t     pull;     /*!< Wake-up pin pull     */
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

/*! HAL PWR Stop voltage scale range enumeration definition */
typedef enum
{
  HAL_PWR_STOP_VOLT_SCALE_LOW  = LL_PWR_REGU_STOP_VOLT_SCALE_LOW,  /*!< Voltage scale Low (lowest power) when system
                                                                        enters STOP mode */
  HAL_PWR_STOP_VOLT_SCALE_HIGH = LL_PWR_REGU_STOP_VOLT_SCALE_HIGH, /*!< Voltage scale High (highest frequency) when
                                                                        system enters STOP mode */
} hal_pwr_stop_volt_scale_range_t;

/*! HAL PWR main regulator source configuration enumeration definition */
typedef enum
{
  HAL_PWR_MAIN_REGULATOR_SUPPLY_NOT_BYPASS = LL_PWR_MAIN_REGU_SUPPLY_NOT_BYPASSED, /*!< PWR SMPS and LDO regulators
                                                                                        are not bypassed */
  HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASS     = LL_PWR_MAIN_REGU_SUPPLY_BYPASSED      /*!< PWR SMPS and LDO regulators
                                                                                        are bypassed */
} hal_pwr_main_regulator_supply_t;

/*! HAL PWR main regulator source enumeration definition */
typedef enum
{
  HAL_PWR_MAIN_REGULATOR_SUPPLY_BYPASSED = LL_PWR_MAIN_REGU_SUPPLY_BYPASSED,     /*!< PWR SMPS and LDO regulators are
                                                                                      bypassed */
  HAL_PWR_MAIN_REGULATOR_SUPPLY_SMPS     = LL_PWR_MAIN_REGU_SUPPLY_SMPS_ENABLED, /*!< PWR SMPS is the main regulator
                                                                                      supply */
  HAL_PWR_MAIN_REGULATOR_SUPPLY_LDO      = LL_PWR_MAIN_REGU_SUPPLY_LDO_ENABLED,  /*!< PWR LDO is the main regulator
                                                                                      supply */
} hal_pwr_main_regulator_supply_status_t;

/*! HAL PWR analog IO switch enumeration definition */
typedef enum
{
  HAL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY    = LL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY,    /*!< PWR Analog IO switch to VDDA
                                                                                         supply */
  HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY = LL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY  /*!< PWR Analog IO switch to Booster
                                                                                         supply */
} hal_pwr_analog_io_switch_supply_t;

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

/*! HAL PWR core sleep-on-exit status enumeration definition */
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

/*! HAL PWR programmable voltage detector level enumeration definition */
typedef enum
{
  HAL_PWR_PVD_VDD_LEVEL_1   = LL_PWR_PVD_VDD_LEVEL_1,  /*!< Voltage threshold detected by PVD
                                                              Rising edge typical :   1.96V
                                                              Falling edge typical :  1.86V    */
  HAL_PWR_PVD_VDD_LEVEL_2   = LL_PWR_PVD_VDD_LEVEL_2,  /*!< Voltage threshold detected by PVD
                                                              Rising edge typical :   2.10V
                                                              Falling edge typical :  2.01V    */
  HAL_PWR_PVD_VDD_LEVEL_3   = LL_PWR_PVD_VDD_LEVEL_3,  /*!< Voltage threshold detected by PVD
                                                              Rising edge typical :   2.26V
                                                              Falling edge typical :  2.15V    */
  HAL_PWR_PVD_VDD_LEVEL_4   = LL_PWR_PVD_VDD_LEVEL_4,  /*!< Voltage threshold detected by PVD
                                                              Rising edge typical :   2.41V
                                                              Falling edge typical :  2.31V    */
  HAL_PWR_PVD_VDD_LEVEL_5   = LL_PWR_PVD_VDD_LEVEL_5,  /*!< Voltage threshold detected by PVD
                                                              Rising edge typical :   2.56V
                                                              Falling edge typical :  2.45V    */
  HAL_PWR_PVD_VDD_LEVEL_6   = LL_PWR_PVD_VDD_LEVEL_6,  /*!< Voltage threshold detected by PVD
                                                              Rising edge typical :   2.71V
                                                              Falling edge typical :  2.61V    */
  HAL_PWR_PVD_VDD_LEVEL_7   = LL_PWR_PVD_VDD_LEVEL_7,  /*!< Voltage threshold detected by PVD
                                                              Rising edge typical :   2.86V
                                                              Falling edge typical :  2.76V    */
  HAL_PWR_PVD_PVDIN_VREFINT = LL_PWR_PVD_PVDIN_VREFINT /*!< External voltage on PVD_IN pin,
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
  HAL_PWR_PVD_OUT_EQ_HIGH_THR = 0U, /*!< VDD equal to or higher than programmable voltage detector threshold */
  HAL_PWR_PVD_OUT_LOW_THR     = 1U  /*!< VDD lower than programmable voltage detector threshold              */
} hal_pwr_pvd_out_t;

/*! HAL PWR analog voltage detector level enumeration definition */
typedef enum
{
  HAL_PWR_AVD_VDDA_LEVEL_1 = LL_PWR_AVD_VDDA_LEVEL_1, /*!< Voltage threshold detected by AVD
                                                             Rising edge typical :   1.71V
                                                             Falling edge typical :  1.61V   */
  HAL_PWR_AVD_VDDA_LEVEL_2 = LL_PWR_AVD_VDDA_LEVEL_2, /*!< Voltage threshold detected by AVD
                                                             Rising edge typical :   2.12V
                                                             Falling edge typical :  2.02V   */
  HAL_PWR_AVD_VDDA_LEVEL_3 = LL_PWR_AVD_VDDA_LEVEL_3, /*!< Voltage threshold detected by AVD
                                                             Rising edge typical :   2.50V
                                                             Falling edge typical :  2.42V   */
  HAL_PWR_AVD_VDDA_LEVEL_4 = LL_PWR_AVD_VDDA_LEVEL_4, /*!< Voltage threshold detected by AVD
                                                             Rising edge typical :   2.83V
                                                             Falling edge typical :  2.72V   */
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
  HAL_PWR_AVD_OUT_EQ_HIGH_THR = 0U, /*!< VDDA equal to or higher than analog voltage detector threshold */
  HAL_PWR_AVD_OUT_LOW_THR     = 1U  /*!< VDDA lower than analog voltage detector threshold              */
} hal_pwr_avd_out_t;

/*! HAL PWR power voltage monitor status definition */
typedef enum
{
  HAL_PWR_MONITOR_DISABLED = 0U, /*!< Monitoring disabled */
  HAL_PWR_MONITOR_ENABLED  = 1U  /*!< Monitoring enabled  */
} hal_pwr_monitor_status_t;

/*! HAL PWR temperature level definition */
typedef enum
{
  HAL_PWR_TEMP_LEVEL_BETWEEN_THR = 0U, /*!< PWR Temperature between low and high thresholds */
  HAL_PWR_TEMP_LEVEL_EQ_HIGH_THR = 1U, /*!< PWR Temperature equal or above high threshold   */
  HAL_PWR_TEMP_LEVEL_EQ_LOW_THR  = 2U  /*!< PWR Temperature equal or below low threshold    */
} hal_pwr_temp_level_t;

/*! HAL PWR VBAT voltage level definition */
typedef enum
{
  HAL_PWR_VBAT_LEVEL_BETWEEN_THR  = 0U, /*!< PWR VBAT voltage between low and high thresholds */
  HAL_PWR_VBAT_LEVEL_EQ_LOW_THR   = 1U, /*!< PWR VBAT voltage below or equal to low threshold */
  HAL_PWR_VBAT_LEVEL_EQ_HIGH_THR  = 2U, /*!< PWR VBAT voltage equal or above high threshold   */
} hal_pwr_vbat_level_t;

/*! HAL PWR memory retention enumeration definition */
typedef enum
{
  HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT = 0U /*!< Backup RAM memory retention in Standby mode */
} hal_pwr_memory_retention_t;

/*! HAL PWR memory retention status enumeration definition */
typedef enum
{
  HAL_PWR_MEMORY_RETENTION_DISABLED = 0U, /*!< Memory retention in Standby mode disabled */
  HAL_PWR_MEMORY_RETENTION_ENABLED  = 1U  /*!< Memory retention in Standby mode enabled  */
} hal_pwr_memory_retention_status_t;

/*! HAL PWR FLASH memory low power mode status enumeration definition */
typedef enum
{
  HAL_PWR_FLASH_LOW_PWR_MODE_DISABLED = 0U, /*!< PWR FLASH memory low power mode disabled */
  HAL_PWR_FLASH_LOW_PWR_MODE_ENABLED  = 1U  /*!< PWR FLASH memory low power mode enabled  */
} hal_pwr_flash_low_pwr_mode_status_t;

/*! HAL PWR USB Type-C and Power Delivery Standby mode enumeration definition */
typedef enum
{
  HAL_PWR_UCPD_RETENTION_DISABLED = 0U, /*!< UCPD configuration retention in Standby mode disabled */
  HAL_PWR_UCPD_RETENTION_ENABLED  = 1U  /*!< UCPD configuration retention in Standby mode enabled  */
} hal_pwr_ucpd_retention_status_t;

/*! HAL PWR battery charging resistor value enumeration definition */
typedef enum
{
  HAL_PWR_BATTERY_CHARGING_RES_5K   = LL_PWR_BATT_CHARG_RESISTOR_5K,  /*!< Battery charging resistor 5KOhm   */
  HAL_PWR_BATTERY_CHARGING_RES_1_5K = LL_PWR_BATT_CHARG_RESISTOR_1_5K /*!< Battery charging resistor 1.5KOhm */
} hal_pwr_battery_charging_res_value_t;

/*! HAL PWR battery charging status enumeration definition */
typedef enum
{
  HAL_PWR_BATTERY_CHARGING_DISABLED = 0U, /*!< Battery charging disabled */
  HAL_PWR_BATTERY_CHARGING_ENABLED  = 1U  /*!< Battery charging enabled  */
} hal_pwr_battery_charging_status_t;

/*! HAL PWR USB Type-C and Power Delivery dead battery mode status enumeration definition */
typedef enum
{
  HAL_PWR_DEAD_BATTERY_MODE_DISABLED = 0U, /*!< USB Type-C and Power Delivery dead battery mode disabled */
  HAL_PWR_DEAD_BATTERY_MODE_ENABLED  = 1U  /*!< USB Type-C and Power Delivery dead battery mode enabled  */
} hal_pwr_dead_battery_mode_status_t;

/*! HAL PWR GPIO pull enumeration definition */
typedef enum
{
  HAL_PWR_GPIO_PULL_NO   = 0U, /*!< GPIO no pull   */
  HAL_PWR_GPIO_PULL_UP   = 1U, /*!< GPIO pull-up   */
  HAL_PWR_GPIO_PULL_DOWN = 2U  /*!< GPIO pull-down */
} hal_pwr_gpio_pull_t;

/*! HAL PWR peripheral pull configuration selection enumeration definition */
typedef enum
{
  HAL_PWR_PULL_PERIPH_I3C1, /*!< I3C1 selected */
  HAL_PWR_PULL_PERIPH_XSPI1 /*!< XSPI1 selected */
} hal_pwr_pull_periph_t;

/*! HAL PWR GPIO pull configuration status enumeration definition */
typedef enum
{
  HAL_PWR_GPIO_CONFIG_NOT_APPLIED = 0U, /*!< GPIO pull configuration not applied */
  HAL_PWR_GPIO_CONFIG_APPLIED     = 1U  /*!< GPIO pull configuration applied     */
} hal_pwr_gpio_pull_config_status_t;
/**
  * @}
  */

/* Exported constants -----------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_wakeup_pin PWR wake-up pin definition
  * @{
  */
#define HAL_PWR_WAKEUP_PIN_1   LL_PWR_WAKEUP_PIN_1    /*!< Wake-up pin 1 */
#define HAL_PWR_WAKEUP_PIN_2   LL_PWR_WAKEUP_PIN_2    /*!< Wake-up pin 2 */
#define HAL_PWR_WAKEUP_PIN_3   LL_PWR_WAKEUP_PIN_3    /*!< Wake-up pin 3 */
#define HAL_PWR_WAKEUP_PIN_4   LL_PWR_WAKEUP_PIN_4    /*!< Wake-up pin 4 */
#define HAL_PWR_WAKEUP_PIN_5   LL_PWR_WAKEUP_PIN_5    /*!< Wake-up pin 5 */
#define HAL_PWR_WAKEUP_PIN_6   LL_PWR_WAKEUP_PIN_6    /*!< Wake-up pin 6 */
#define HAL_PWR_WAKEUP_PIN_7   LL_PWR_WAKEUP_PIN_7    /*!< Wake-up pin 7 */
#define HAL_PWR_WAKEUP_PIN_8   LL_PWR_WAKEUP_PIN_8    /*!< Wake-up pin 8 */
#define HAL_PWR_WAKEUP_PIN_ALL LL_PWR_WAKEUP_PIN_ALL  /*!< All wake-up pins */
/**
  * @}
  */

/** @defgroup PWR_wakeup_source PWR wake-up source definition
  * @{
  */
#define HAL_PWR_WAKEUP_SOURCE_1   LL_PWR_WAKEUP_PIN_1    /*!< Wake-up source 1 */
#define HAL_PWR_WAKEUP_SOURCE_2   LL_PWR_WAKEUP_PIN_2    /*!< Wake-up source 2 */
#define HAL_PWR_WAKEUP_SOURCE_3   LL_PWR_WAKEUP_PIN_3    /*!< Wake-up source 3 */
#define HAL_PWR_WAKEUP_SOURCE_4   LL_PWR_WAKEUP_PIN_4    /*!< Wake-up source 4 */
#define HAL_PWR_WAKEUP_SOURCE_5   LL_PWR_WAKEUP_PIN_5    /*!< Wake-up source 5 */
#define HAL_PWR_WAKEUP_SOURCE_6   LL_PWR_WAKEUP_PIN_6    /*!< Wake-up source 6 */
#define HAL_PWR_WAKEUP_SOURCE_7   LL_PWR_WAKEUP_PIN_7    /*!< Wake-up source 7 */
#define HAL_PWR_WAKEUP_SOURCE_8   LL_PWR_WAKEUP_PIN_8    /*!< Wake-up source 8 */
#define HAL_PWR_WAKEUP_SOURCE_ALL LL_PWR_WAKEUP_PIN_ALL  /*!< All wake-up sources */
/**
  * @}
  */

/** @defgroup PWR_I3C1_pull PWR I3C1 pin pull definition
  * @{
  */
#define HAL_PWR_I3C1_PULL_PA15    LL_PWR_I3C1_PULL_UP_PA15   /*!< Port PA15 I3C1 bit */
#define HAL_PWR_I3C1_PULL_PB3     LL_PWR_I3C1_PULL_UP_PB3    /*!< Port PB3 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PB4     LL_PWR_I3C1_PULL_UP_PB4    /*!< Port PB4 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PB8     LL_PWR_I3C1_PULL_UP_PB8    /*!< Port PB8 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PB9     LL_PWR_I3C1_PULL_UP_PB9    /*!< Port PB9 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PC8     LL_PWR_I3C1_PULL_UP_PC8    /*!< Port PC8 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PC9     LL_PWR_I3C1_PULL_UP_PC9    /*!< Port PC9 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PD0     LL_PWR_I3C1_PULL_UP_PD0    /*!< Port PD0 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PD1     LL_PWR_I3C1_PULL_UP_PD1    /*!< Port PD1 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PD6     LL_PWR_I3C1_PULL_UP_PD6    /*!< Port PD6 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PD7     LL_PWR_I3C1_PULL_UP_PD7    /*!< Port PD7 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PE5     LL_PWR_I3C1_PULL_UP_PE5    /*!< Port PE5 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PE6     LL_PWR_I3C1_PULL_UP_PE6    /*!< Port PE6 I3C1 bit  */
#define HAL_PWR_I3C1_PULL_PG13    LL_PWR_I3C1_PULL_UP_PG13   /*!< Port PG13 I3C1 bit */
#define HAL_PWR_I3C1_PULL_PG14    LL_PWR_I3C1_PULL_UP_PG14   /*!< Port PG14 I3C1 bit */
#define HAL_PWR_I3C1_PULL_PH11    LL_PWR_I3C1_PULL_UP_PH11   /*!< Port PH11 I3C1 bit */
#define HAL_PWR_I3C1_PULL_PH12    LL_PWR_I3C1_PULL_UP_PH12   /*!< Port PH12 I3C1 bit */
#define HAL_PWR_I3C1_PULL_PI2     LL_PWR_I3C1_PULL_UP_PI2    /*!< Port PI2 I3C1 bit  */
/**
  * @}
  */

/** @defgroup PWR_XSPI1_pull PWR XSPI1 pin pull definition
  * @{
  */
#define HAL_PWR_XSPI1_PULL_PH0      LL_PWR_XSPI1_PULL_UP_PH0   /*!< Port PH0 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PH1      LL_PWR_XSPI1_PULL_UP_PH1   /*!< Port PH1 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PF2      LL_PWR_XSPI1_PULL_UP_PF2   /*!< Port PF2 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PA0      LL_PWR_XSPI1_PULL_UP_PA0   /*!< Port PA0 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PA2      LL_PWR_XSPI1_PULL_UP_PA2   /*!< Port PA2 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PA3      LL_PWR_XSPI1_PULL_UP_PA3   /*!< Port PA3 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PA4      LL_PWR_XSPI1_PULL_UP_PA4   /*!< Port PA4 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PA5      LL_PWR_XSPI1_PULL_UP_PA5   /*!< Port PA5 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PB1      LL_PWR_XSPI1_PULL_UP_PB1   /*!< Port PB1 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PB2      LL_PWR_XSPI1_PULL_UP_PB2   /*!< Port PB2 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PD0      LL_PWR_XSPI1_PULL_UP_PD0   /*!< Port PD0 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PD1      LL_PWR_XSPI1_PULL_UP_PD1   /*!< Port PD1 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PD2      LL_PWR_XSPI1_PULL_UP_PD2   /*!< Port PD2 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PD3      LL_PWR_XSPI1_PULL_UP_PD3   /*!< Port PD3 XSPI1 bit  */
#define HAL_PWR_XSPI1_PULL_PG10     LL_PWR_XSPI1_PULL_UP_PG10  /*!< Port PG10 XSPI1 bit */
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

/** @defgroup PWR_Exported_Functions_Group1 Power supply management functions
  * @{
  */
hal_status_t HAL_PWR_SetMainRegulatorVoltageScalingRange(hal_pwr_volt_scale_range_t range);
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorVoltageScalingRange(void);
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorActiveVoltageScalingRange(void);


void HAL_PWR_LP_SetMainRegulatorStopVoltageScalingRange(hal_pwr_stop_volt_scale_range_t range);
hal_pwr_stop_volt_scale_range_t HAL_PWR_LP_GetMainRegulatorStopVoltageScalingRange(void);

hal_pwr_main_regulator_supply_t HAL_PWR_GetMainRegulatorSupply(void);
hal_pwr_main_regulator_supply_status_t HAL_PWR_GetMainRegulatorSupplyStatus(void);


void HAL_PWR_SetAnalogIOSwitchSupply(hal_pwr_analog_io_switch_supply_t analog_io_switch_supply);
hal_pwr_analog_io_switch_supply_t HAL_PWR_GetAnalogIOSwitchSupply(void);
/**
  * @}
  */


/** @defgroup PWR_Exported_Functions_Group2 Low power mode management functions
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

void HAL_PWR_WakeupPin_IRQHandler(uint32_t wakeup_pin);
void HAL_PWR_WakeupPinCallback(uint32_t wakeup_pin);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group3 Wake-up pins management functions
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

/** @defgroup PWR_Exported_Functions_Group4 RTC domain write protection management functions
  * @{
  */
void HAL_PWR_EnableRTCDomainWriteProtection(void);
void HAL_PWR_DisableRTCDomainWriteProtection(void);
hal_pwr_rtc_domain_wrp_status_t HAL_PWR_IsEnabledRTCDomainWriteProtection(void);
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

void HAL_PWR_EnableTemperatureVbatMonitor(void);
void HAL_PWR_DisableTemperatureVbatMonitor(void);
hal_pwr_monitor_status_t HAL_PWR_IsEnabledTemperatureVbatMonitor(void);
hal_pwr_temp_level_t HAL_PWR_GetTemperatureLevelStatus(void);
hal_pwr_vbat_level_t HAL_PWR_GetVbatVoltageLevelStatus(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group6 Memory retention management functions
  * @{
  */
hal_status_t HAL_PWR_LP_EnableMemoryRetention(hal_pwr_memory_retention_t memory);
hal_status_t HAL_PWR_LP_DisableMemoryRetention(hal_pwr_memory_retention_t memory);
hal_pwr_memory_retention_status_t HAL_PWR_LP_IsEnabledMemoryRetention(hal_pwr_memory_retention_t memory);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group7 Memory low power management functions
  * @{
  */
void HAL_PWR_LP_EnableFlashLowPWRMode(void);
void HAL_PWR_LP_DisableFlashLowPWRMode(void);
hal_pwr_flash_low_pwr_mode_status_t HAL_PWR_LP_IsEnabledFlashLowPWRMode(void);
/**
  * @}
  */


/** @defgroup PWR_Exported_Functions_Group8 Battery management functions
  * @{
  */
void HAL_PWR_SetConfigBatteryCharging(hal_pwr_battery_charging_res_value_t value);
hal_pwr_battery_charging_res_value_t HAL_PWR_GetConfigBatteryCharging(void);
void HAL_PWR_EnableBatteryCharging(void);
void HAL_PWR_DisableBatteryCharging(void);
hal_pwr_battery_charging_status_t HAL_PWR_IsEnabledBatteryCharging(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group9 UCPD management functions
  * @{
  */
void HAL_PWR_LP_EnableUCPDDeadBattery(void);
void HAL_PWR_LP_DisableUCPDDeadBattery(void);
hal_pwr_dead_battery_mode_status_t HAL_PWR_LP_IsEnabledUCPDDeadBattery(void);
void HAL_PWR_LP_EnableUCPDRetention(void);
void HAL_PWR_LP_DisableUCPDRetention(void);
hal_pwr_ucpd_retention_status_t HAL_PWR_LP_IsEnabledUCPDRetention(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group10 Standby I/O pull management functions
  * @{
  */
void HAL_PWR_EnableGPIOPull(void);
void HAL_PWR_DisableGPIOPull(void);
hal_pwr_gpio_pull_config_status_t HAL_PWR_IsEnabledGPIOPull(void);

void HAL_PWR_SetConfigPeriphGPIOPull(hal_pwr_pull_periph_t periph, uint32_t pin, hal_pwr_gpio_pull_t pull);
hal_pwr_gpio_pull_t HAL_PWR_GetConfigPeriphGPIOPull(hal_pwr_pull_periph_t periph, uint32_t pin);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_HAL_PWR_H */
