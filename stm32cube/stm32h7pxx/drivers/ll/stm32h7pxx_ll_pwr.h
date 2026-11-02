/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_ll_pwr.h
  * @brief   Header file of PWR LL module.
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
#ifndef STM32H7Pxx_LL_PWR_H
#define STM32H7Pxx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_LL_Driver
  * @{
  */

#if defined (PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup PWR_LL_WAKEUP_PIN_OFFSET Wake-up pins register offsets definitions
  * @brief    Flag definitions that can be used with LL_PWR_WRITE_REG function.
  * @{
  */
/* Wake-up pins PWR register offsets */
#define LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET    2UL
#define LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK       0x1FU
#define LL_PWR_WAKEUP_PIN_POLARITY_REF          PWR_WKUPEPR_WKUPP1
#define LL_PWR_WAKEUP_PIN_POLARITY_REF_POS      PWR_WKUPEPR_WKUPP1_Pos
#define LL_PWR_WAKEUP_PIN_PULL_REF              PWR_WKUPEPR_WKUPPUPD1
#define LL_PWR_WAKEUP_PIN_PULL_REF_POS          PWR_WKUPEPR_WKUPPUPD1_Pos
/**
  * @}
  */
/**
  * @}
  */
/* Private macros ----------------------------------------------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_LOW_POWER_MODE_SELECTION  Low power mode selection
  * @{
  */
#define LL_PWR_STOP_MODE       0U              /*!< STOP mode    */
#define LL_PWR_STANDBY_MODE    PWR_CSR3_PDDS   /*!< STANDBY mode   */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_VOLTAGE_SCALING_RANGE_SELECTION PWR Voltage scaling range selection
  * @{
  */
#define LL_PWR_REGU_VOLT_SCALE_0    (PWR_CSR4_VOS_0 | PWR_CSR4_VOS_1)   /*!< Voltage scaling range 0 */
#define LL_PWR_REGU_VOLT_SCALE_1    PWR_CSR4_VOS_1                      /*!< Voltage scaling range 1 */
#define LL_PWR_REGU_VOLT_SCALE_2    PWR_CSR4_VOS_0                      /*!< Voltage scaling range 2 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ACTIVE_VOLTAGE_SCALING_RANGE_SELECTION PWR Voltage scaling range selection
  * @{
  */
#define LL_PWR_ACTIVE_VOLT_SCALE_0    (PWR_SR1_ACTVOS_0 | PWR_SR1_ACTVOS_1)   /*!< Voltage scaling range 0 */
#define LL_PWR_ACTIVE_VOLT_SCALE_1    PWR_SR1_ACTVOS_1                        /*!< Voltage scaling range 1 */
#define LL_PWR_ACTIVE_VOLT_SCALE_2    PWR_SR1_ACTVOS_0                        /*!< Voltage scaling range 2 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_STOP_MODE_REGU_VOLTAGE Stop mode regulator voltage scaling
  * @{
  */
#define LL_PWR_REGU_STOP_VOLT_SCALE_HIGH    PWR_CR1_SVOS   /*!< Voltage scaling high (highest frequency) STOP mode */
#define LL_PWR_REGU_STOP_VOLT_SCALE_LOW     0U             /*!< Voltage scaling low (lowest power) STOP mode       */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDLEVEL Power Digital Voltage Level Detector
  * @{
  */
#define LL_PWR_PVD_VDD_LEVEL_1      0U                                /*!< Voltage threshold detected by PVD
                                                                             Rising edge typical :   1.96V
                                                                             Falling edge typical :  1.86V    */
#define LL_PWR_PVD_VDD_LEVEL_2      PWR_CR1_PLS_0                     /*!< Voltage threshold detected by PVD
                                                                             Rising edge typical :   2.10V
                                                                             Falling edge typical :  2.01V    */
#define LL_PWR_PVD_VDD_LEVEL_3      PWR_CR1_PLS_1                     /*!< Voltage threshold detected by PVD
                                                                             Rising edge typical :   2.26V
                                                                             Falling edge typical :  2.15V    */
#define LL_PWR_PVD_VDD_LEVEL_4      (PWR_CR1_PLS_0 | PWR_CR1_PLS_1)   /*!< Voltage threshold detected by PVD
                                                                             Rising edge typical :   2.41V
                                                                             Falling edge typical :  2.31V    */
#define LL_PWR_PVD_VDD_LEVEL_5      (PWR_CR1_PLS_2)                   /*!< Voltage threshold detected by PVD
                                                                             Rising edge typical :   2.56V
                                                                             Falling edge typical :  2.45V    */
#define LL_PWR_PVD_VDD_LEVEL_6      (PWR_CR1_PLS_0 | PWR_CR1_PLS_2)   /*!< Voltage threshold detected by PVD
                                                                             Rising edge typical :   2.71V
                                                                             Falling edge typical :  2.61V    */
#define LL_PWR_PVD_VDD_LEVEL_7      (PWR_CR1_PLS_1 | PWR_CR1_PLS_2)   /*!< Voltage threshold detected by PVD
                                                                             Rising edge typical :   2.86V
                                                                             Falling edge typical :  2.76V    */
#define LL_PWR_PVD_PVDIN_VREFINT    (PWR_CR1_PLS_0 | PWR_CR1_PLS_1 | \
                                     PWR_CR1_PLS_2)                   /*!< External voltage on PVD_IN pin,
                                                                           compared to internal VREFINT level */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_AVDLEVEL Power Analog Voltage Level Detector
  * @{
  */
#define LL_PWR_AVD_VDDA_LEVEL_1    0U                                /*!< Voltage threshold detected by AVD
                                                                            Rising edge typical :   1.71V
                                                                            Falling edge typical :  1.61V */
#define LL_PWR_AVD_VDDA_LEVEL_2    PWR_CR1_ALS_0                     /*!< Voltage threshold detected by AVD
                                                                            Rising edge typical :   2.12V
                                                                            Falling edge typical :  2.02V */
#define LL_PWR_AVD_VDDA_LEVEL_3    PWR_CR1_ALS_1                     /*!< Voltage threshold detected by AVD
                                                                            Rising edge typical :   2.50V
                                                                            Falling edge typical :  2.42V */
#define LL_PWR_AVD_VDDA_LEVEL_4    (PWR_CR1_ALS_0 | PWR_CR1_ALS_1)   /*!< Voltage threshold detected by AVD
                                                                            Rising edge typical :   2.83V
                                                                            Falling edge typical :  2.72V */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_BATT_CHARG_RESISTOR Battery Charge Resistor
  * @{
  */
#define LL_PWR_BATT_CHARG_RESISTOR_5K      0U              /*!< Charge the battery through a 5 kOhm resistor   */
#define LL_PWR_BATT_CHARG_RESISTOR_1_5K    PWR_CSR2_VBRS   /*!< Charge the battery through a 1.5 kOhm resistor */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN Wake-up pins
  * @{
  */
#define LL_PWR_WAKEUP_PIN_1      PWR_WKUPEPR_WKUPEN1   /*!< Wake-up pin 1 : PA0     */
#define LL_PWR_WAKEUP_PIN_2      PWR_WKUPEPR_WKUPEN2   /*!< Wake-up pin 2 : PA2     */
#define LL_PWR_WAKEUP_PIN_3      PWR_WKUPEPR_WKUPEN3   /*!< Wake-up pin 3 : PI8     */
#define LL_PWR_WAKEUP_PIN_4      PWR_WKUPEPR_WKUPEN4   /*!< Wake-up pin 4 : PC13    */
#define LL_PWR_WAKEUP_PIN_5      PWR_WKUPEPR_WKUPEN5   /*!< Wake-up pin 5 : PB9     */
#define LL_PWR_WAKEUP_PIN_6      PWR_WKUPEPR_WKUPEN6   /*!< Wake-up pin 6 : PC1     */
#define LL_PWR_WAKEUP_PIN_7      PWR_WKUPEPR_WKUPEN7   /*!< Wake-up pin 7 : PC0     */
#define LL_PWR_WAKEUP_PIN_8      PWR_WKUPEPR_WKUPEN8   /*!< Wake-up pin 8 : PD2     */
#define LL_PWR_WAKEUP_PIN_ALL    0x000000FFUL          /*!< Enable all wake-up pins */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_PULL  Wake-up pins pull configuration
  * @{
  */
#define LL_PWR_WAKEUP_PIN_PULL_NO      0UL   /*!< Configure wake-up pin in no pull   */
#define LL_PWR_WAKEUP_PIN_PULL_UP      1UL   /*!< Configure wake-up pin in pull-up   */
#define LL_PWR_WAKEUP_PIN_PULL_DOWN    2UL   /*!< Configure wake-up pin in pull-down */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_POLARITY  Wake-up pins polarity
  * @{
  */
#define LL_PWR_WAKEUP_PIN_POLARITY_HIGH    0UL   /*!< Wake-up pin polarity high  */
#define LL_PWR_WAKEUP_PIN_POLARITY_LOW     1UL   /*!< Wake-up pin polarity low   */
/**
  * @}
  */


/** @defgroup PWR_LL_EC_INTERNAL_REGULATORS_BYPASS PWR SMPS and LDO internal regulators bypass in range 0 definition
  * @{
  */
#define LL_PWR_MAIN_REGU_SUPPLY_NOT_BYPASSED  0U              /*!< SMPS and LDO internal regulators bypass in range 0 */
#define LL_PWR_MAIN_REGU_SUPPLY_BYPASSED      PWR_CSR2_BYPASS /*!< SMPS and LDO internal regulators bypass in range 0 */
/**
  * @}
  */


/** @defgroup PWR_LL_EC_INTERNAL_REGULATOR_SUPPLY PWR Regulator supply
  * @{
  */
#define LL_PWR_MAIN_REGU_SUPPLY_LDO_ENABLED     PWR_CSR2_LDOEN  /*!< LDO regulator supply  */
#define LL_PWR_MAIN_REGU_SUPPLY_SMPS_ENABLED    PWR_CSR2_SMPSEN /*!< SMPS regulator supply */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ANALOG_IO_SWITCH_SUPPLY PWR Analog IO switch supply definitions
  * @{
  */
#define LL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY       0U                    /*!< Analog IO switch to VddA supply    */
#define LL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY    (PWR_CR1_AVDREADY | \
                                                   PWR_CR1_BOOSTE)      /*!< Analog IO switch to booster supply */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SUPPLY_PWR Power supply source configuration
  * @{
  */
#define LL_PWR_LDO_SUPPLY                PWR_CSR2_LDOEN    /*!< Core domains are supplied from the LDO  */
#define LL_PWR_DIRECT_SMPS_SUPPLY        PWR_CSR2_SMPSEN   /*!< Core domains are supplied from the SMPS */
#define LL_PWR_EXTERNAL_SOURCE_SUPPLY    PWR_CSR2_BYPASS   /*!< Core supplied from an external source   */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_I3C1_PULL_UP I3C1 Pull-Up Pins
  * @{
  */
#define LL_PWR_I3C1_PULL_UP_PA15         PWR_I3CPUCR_I3CPA15_PU     /*!< Port PA15 I3C1 pull-up bit */
#define LL_PWR_I3C1_PULL_UP_PB3          PWR_I3CPUCR_I3CPB3_PU      /*!< Port PB3 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PB4          PWR_I3CPUCR_I3CPB4_PU      /*!< Port PB4 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PB8          PWR_I3CPUCR_I3CPB8_PU      /*!< Port PB8 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PB9          PWR_I3CPUCR_I3CPB9_PU      /*!< Port PB9 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PC8          PWR_I3CPUCR_I3CPC8_PU      /*!< Port PC8 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PC9          PWR_I3CPUCR_I3CPC9_PU      /*!< Port PC9 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PD0          PWR_I3CPUCR_I3CPD0_PU      /*!< Port PD0 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PD1          PWR_I3CPUCR_I3CPD1_PU      /*!< Port PD1 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PD6          PWR_I3CPUCR_I3CPD6_PU      /*!< Port PD6 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PD7          PWR_I3CPUCR_I3CPD7_PU      /*!< Port PD7 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PE5          PWR_I3CPUCR_I3CPE5_PU      /*!< Port PE5 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PE6          PWR_I3CPUCR_I3CPE6_PU      /*!< Port PE6 I3C1 pull-up bit  */
#define LL_PWR_I3C1_PULL_UP_PG13         PWR_I3CPUCR_I3CPG13_PU     /*!< Port PG13 I3C1 pull-up bit */
#define LL_PWR_I3C1_PULL_UP_PG14         PWR_I3CPUCR_I3CPG14_PU     /*!< Port PG14 I3C1 pull-up bit */
#define LL_PWR_I3C1_PULL_UP_PH11         PWR_I3CPUCR_I3CPH11_PU     /*!< Port PH11 I3C1 pull-up bit */
#define LL_PWR_I3C1_PULL_UP_PH12         PWR_I3CPUCR_I3CPH12_PU     /*!< Port PH12 I3C1 pull-up bit */
#define LL_PWR_I3C1_PULL_UP_PI2          PWR_I3CPUCR_I3CPI2_PU      /*!< Port PI2 I3C1 pull-up bit  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_XSPI1_PULL_UP XSPI1 Pull-Up Pins
  * @{
  */
#define LL_PWR_XSPI1_PULL_UP_PG10        PWR_XSPIPUCR_XSPIPG10_PU   /*!< Port PG10 XSPI1 pull-up bit */
#define LL_PWR_XSPI1_PULL_UP_PD3         PWR_XSPIPUCR_XSPIPD3_PU    /*!< Port PD3 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PD2         PWR_XSPIPUCR_XSPIPD2_PU    /*!< Port PD2 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PD1         PWR_XSPIPUCR_XSPIPD1_PU    /*!< Port PD1 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PD0         PWR_XSPIPUCR_XSPIPD0_PU    /*!< Port PD0 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PB2         PWR_XSPIPUCR_XSPIPB2_PU    /*!< Port PB2 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PB1         PWR_XSPIPUCR_XSPIPB1_PU    /*!< Port PB1 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PA5         PWR_XSPIPUCR_XSPIPA5_PU    /*!< Port PA5 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PA4         PWR_XSPIPUCR_XSPIPA4_PU    /*!< Port PA4 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PA3         PWR_XSPIPUCR_XSPIPA3_PU    /*!< Port PA3 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PA2         PWR_XSPIPUCR_XSPIPA2_PU    /*!< Port PA2 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PA0         PWR_XSPIPUCR_XSPIPA0_PU    /*!< Port PA0 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PF2         PWR_XSPIPUCR_XSPIPF2_PU    /*!< Port PF2 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PH1         PWR_XSPIPUCR_XSPIPH1_PU    /*!< Port PH1 XSPI1 pull-up bit  */
#define LL_PWR_XSPI1_PULL_UP_PH0         PWR_XSPIPUCR_XSPIPH0_PU    /*!< Port PH0 XSPI1 pull-up bit  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_XSPI1_PULL_DOWN XSPI1 Pull-Down Pins
  * @{
  */
#define LL_PWR_XSPI1_PULL_DOWN_PG10      PWR_XSPIPDCR_XSPIPG10_PD   /*!< Port PG10 XSPI1 pull-down bit */
#define LL_PWR_XSPI1_PULL_DOWN_PD3       PWR_XSPIPDCR_XSPIPD3_PD    /*!< Port PD3 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PD2       PWR_XSPIPDCR_XSPIPD2_PD    /*!< Port PD2 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PD1       PWR_XSPIPDCR_XSPIPD1_PD    /*!< Port PD1 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PD0       PWR_XSPIPDCR_XSPIPD0_PD    /*!< Port PD0 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PB2       PWR_XSPIPDCR_XSPIPB2_PD    /*!< Port PB2 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PB1       PWR_XSPIPDCR_XSPIPB1_PD    /*!< Port PB1 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PA5       PWR_XSPIPDCR_XSPIPA5_PD    /*!< Port PA5 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PA4       PWR_XSPIPDCR_XSPIPA4_PD    /*!< Port PA4 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PA3       PWR_XSPIPDCR_XSPIPA3_PD    /*!< Port PA3 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PA2       PWR_XSPIPDCR_XSPIPA2_PD    /*!< Port PA2 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PA0       PWR_XSPIPDCR_XSPIPA0_PD    /*!< Port PA0 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PF2       PWR_XSPIPDCR_XSPIPF2_PD    /*!< Port PF2 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PH1       PWR_XSPIPDCR_XSPIPH1_PD    /*!< Port PH1 XSPI1 pull-down bit  */
#define LL_PWR_XSPI1_PULL_DOWN_PH0       PWR_XSPIPDCR_XSPIPH0_PD    /*!< Port PH0 XSPI1 pull-down bit  */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macro ---------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value to a PWR register.
  * @param  reg      Register to be written.
  * @param  value    Value to be written to the register.
  */
#define LL_PWR_WRITE_REG(reg, value) STM32_WRITE_REG((PWR)->reg, (value))

/**
  * @brief  Read a value from a PWR register.
  * @param  reg      Register to be read.
  * @retval Register value
  */
#define LL_PWR_READ_REG(reg) STM32_READ_REG((PWR)->reg)
/**
  * @}
  */

/**
  * @}
  */
/* Exported functions -----------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_Configuration PWR Configuration
  * @{
  */

/**
  * @brief  Set the internal regulator output voltage in STOP mode.
  * @rmtoll
  *   CR1        SVOS          LL_PWR_SetStopRegulatorVoltageScaling
  * @param  voltagescaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_STOP_VOLT_SCALE_HIGH
  *         @arg @ref LL_PWR_REGU_STOP_VOLT_SCALE_LOW
  */
__STATIC_INLINE void LL_PWR_SetStopRegulatorVoltageScaling(uint32_t voltagescaling)
{
  STM32_MODIFY_REG(PWR->CR1, PWR_CR1_SVOS, voltagescaling);
}

/**
  * @brief  Get the internal regulator output voltage in STOP mode.
  * @rmtoll
  *   CR1        SVOS          LL_PWR_GetStopRegulatorVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_STOP_VOLT_SCALE_HIGH
  *         @arg @ref LL_PWR_REGU_STOP_VOLT_SCALE_LOW
  */
__STATIC_INLINE uint32_t LL_PWR_GetStopRegulatorVoltageScaling(void)
{
  return STM32_READ_BIT(PWR->CR1, PWR_CR1_SVOS);
}

/**
  * @brief  Enable Programmable Voltage Detector.
  * @rmtoll
  *   CR1        PVDE          LL_PWR_EnablePVD
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_PVDE);
}

/**
  * @brief  Disable Programmable Voltage Detector.
  * @rmtoll
  *   CR1        PVDE          LL_PWR_DisablePVD
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_PVDE);
}

/**
  * @brief  Check if Programmable Voltage Detector is enabled.
  * @rmtoll
  *   CR1        PVDE          LL_PWR_IsEnabledPVD
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_PVDE) == (PWR_CR1_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the voltage threshold detected by the Programmable Voltage Detector.
  * @rmtoll
  *   CR1        PLS           LL_PWR_SetPVDLevel
  * @param  pvdlevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_1
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_2
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_3
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_4
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_5
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_6
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_7
  *         @arg @ref LL_PWR_PVD_PVDIN_VREFINT
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t pvdlevel)
{
  STM32_MODIFY_REG(PWR->CR1, PWR_CR1_PLS, pvdlevel);
}

/**
  * @brief  Get the selected Programmable Voltage Detector level.
  * @rmtoll
  *   CR1        PLS           LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_1
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_2
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_3
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_4
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_5
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_6
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_7
  *         @arg @ref LL_PWR_PVD_PVDIN_VREFINT
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return STM32_READ_BIT(PWR->CR1, PWR_CR1_PLS);
}

/**
  * @brief  Disable access to the backup domain.
  * @rmtoll
  *   CR1        DBP           LL_PWR_EnableBackupDomainWriteProtection
  */
__STATIC_INLINE void LL_PWR_EnableBackupDomainWriteProtection(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Enable access to the backup domain.
  * @rmtoll
  *   CR1        DBP           LL_PWR_DisableBackupDomainWriteProtection
  */
__STATIC_INLINE void LL_PWR_DisableBackupDomainWriteProtection(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Check if the backup domain is enabled.
  * @rmtoll
  *   CR1        DBP           LL_PWR_IsEnabledBackupDomainWriteProtection
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBackupDomainWriteProtection(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_DBP) == (PWR_CR1_DBP)) ? 0UL : 1UL);
}

/**
  * @brief  Enable the flash low-power mode in stop mode.
  * @rmtoll
  *   CR1        FLPS          LL_PWR_EnableFlashLowPWRMode
  */
__STATIC_INLINE void LL_PWR_EnableFlashLowPWRMode(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief  Disable the flash low-power mode in stop mode.
  * @rmtoll
  *   CR1        FLPS          LL_PWR_DisableFlashLowPWRMode
  */
__STATIC_INLINE void LL_PWR_DisableFlashLowPWRMode(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief  Check if the flash low-power mode in stop mode is enabled.
  * @rmtoll
  *   CR1        FLPS          LL_PWR_IsEnabledFlashLowPWRMode
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFlashLowPWRMode(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_FLPS) == (PWR_CR1_FLPS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the analog voltage booster.
  * @rmtoll
  *   CR1        BOOSTE        LL_PWR_EnableAnalogBooster
  */
__STATIC_INLINE void LL_PWR_EnableAnalogBooster(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_BOOSTE);
}

/**
  * @brief  Disable the analog voltage booster.
  * @rmtoll
  *   CR1        BOOSTE        LL_PWR_DisableAnalogBooster
  */
__STATIC_INLINE void LL_PWR_DisableAnalogBooster(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_BOOSTE);
}

/**
  * @brief  Check if the analog voltage booster is enabled.
  * @rmtoll
  *   CR1        BOOSTE        LL_PWR_IsEnabledAnalogBooster
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAnalogBooster(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_BOOSTE) == (PWR_CR1_BOOSTE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the analog voltage ready.
  * @rmtoll
  *   CR1        AVDREADY      LL_PWR_EnableAnalogVoltageReady
  */
__STATIC_INLINE void LL_PWR_EnableAnalogVoltageReady(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_AVDREADY);
}

/**
  * @brief  Disable the analog voltage ready.
  * @rmtoll
  *   CR1        AVDREADY      LL_PWR_DisableAnalogVoltageReady
  */
__STATIC_INLINE void LL_PWR_DisableAnalogVoltageReady(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_AVDREADY);
}

/**
  * @brief  Check if the analog voltage ready is enabled.
  * @rmtoll
  *   CR1        AVDREADY      LL_PWR_IsEnabledAnalogVoltageReady
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAnalogVoltageReady(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_AVDREADY) == (PWR_CR1_AVDREADY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Analog Voltage Detector.
  * @rmtoll
  *   CR1        AVDEN         LL_PWR_EnableAVD
  */
__STATIC_INLINE void LL_PWR_EnableAVD(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Disable Analog Voltage Detector.
  * @rmtoll
  *   CR1        AVDEN         LL_PWR_DisableAVD
  */
__STATIC_INLINE void LL_PWR_DisableAVD(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Check if Analog Voltage Detector is enabled.
  * @rmtoll
  *   CR1        AVDEN         LL_PWR_IsEnabledAVD
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAVD(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_AVDEN) == (PWR_CR1_AVDEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Analog Voltage Detector level.
  * @rmtoll
  *   CR1        ALS           LL_PWR_SetAVDLevel
  * @param  avdLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_1
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_2
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_3
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_4
  */
__STATIC_INLINE void LL_PWR_SetAVDLevel(uint32_t avdLevel)
{
  STM32_MODIFY_REG(PWR->CR1, PWR_CR1_ALS, avdLevel);
}

/**
  * @brief  Get the selected Analog Voltage Detector level.
  * @rmtoll
  *   CR1        ALS           LL_PWR_GetAVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_1
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_2
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_3
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_4
  */
__STATIC_INLINE uint32_t LL_PWR_GetAVDLevel(void)
{
  return STM32_READ_BIT(PWR->CR1, PWR_CR1_ALS);
}

/**
  * @brief  Enable backup regulator.
  * @rmtoll
  *   CSR1       BREN          LL_PWR_EnableBackupRegulator
  * @note When set, the backup regulator (used to maintain backup SRAM content in standby and
  *       VBAT modes) is enabled. If BRE is reset, the backup regulator is switched off. The backup
  *       SRAM can still be used but its content will be lost in the standby and VBAT modes. Once set,
  *       the application must wait that the Backup Regulator Ready flag (BRR) is set to indicate that
  *       the data written into the RAM will be maintained in the standby and VBAT modes.
  */
__STATIC_INLINE void LL_PWR_EnableBackupRegulator(void)
{
  STM32_SET_BIT(PWR->CSR1, PWR_CSR1_BREN);
}

/**
  * @brief  Disable backup regulator.
  * @rmtoll
  *   CSR1       BREN          LL_PWR_DisableBackupRegulator
  */
__STATIC_INLINE void LL_PWR_DisableBackupRegulator(void)
{
  STM32_CLEAR_BIT(PWR->CSR1, PWR_CSR1_BREN);
}

/**
  * @brief  Check if the backup regulator is enabled.
  * @rmtoll
  *   CSR1       BREN          LL_PWR_IsEnabledBackupRegulator
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBackupRegulator(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_BREN) == (PWR_CSR1_BREN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable VBAT and temperature monitoring.
  * @rmtoll
  *   CSR1       MONEN         LL_PWR_EnableTemperatureVbatMonitor
  */
__STATIC_INLINE void LL_PWR_EnableTemperatureVbatMonitor(void)
{
  STM32_SET_BIT(PWR->CSR1, PWR_CSR1_MONEN);
}

/**
  * @brief  Disable VBAT and temperature monitoring.
  * @rmtoll
  *   CSR1       MONEN         LL_PWR_DisableTemperatureVbatMonitor
  */
__STATIC_INLINE void LL_PWR_DisableTemperatureVbatMonitor(void)
{
  STM32_CLEAR_BIT(PWR->CSR1, PWR_CSR1_MONEN);
}

/**
  * @brief  Check if the VBAT and temperature monitoring is enabled.
  * @rmtoll
  *   CSR1       MONEN         LL_PWR_IsEnabledTemperatureVbatMonitor
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledTemperatureVbatMonitor(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_MONEN) == (PWR_CSR1_MONEN)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the PWR management unit bypass is enabled or disabled.
  * @rmtoll
  *   CSR2       BYPASS        LL_PWR_IsEnabledBypass
  * @retval 0 if disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBypass(void)
{
  return ((STM32_READ_BIT(PWR->CSR2, PWR_CSR2_BYPASS) == PWR_CSR2_BYPASS) ? 1UL : 0UL);
}

/**
  * @brief  Get the LDO supply status.
  * @rmtoll
  *   CSR2       LDOEN         LL_PWR_IsEnabledLDOSupply
  * @retval 0 if disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledLDOSupply(void)
{
  return ((STM32_READ_BIT(PWR->CSR2, PWR_CSR2_LDOEN) == PWR_CSR2_LDOEN) ? 1UL : 0UL);
}

/**
  * @brief  Get the SMPS supply status.
  * @rmtoll
  *   CSR2       SMPSEN        LL_PWR_IsEnabledSMPSSupply
  * @retval 0 if disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSSupply(void)
{
  return ((STM32_READ_BIT(PWR->CSR2, PWR_CSR2_SMPSEN) == PWR_CSR2_SMPSEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable VBAT battery charging.
  * @rmtoll
  *   CSR2       VBE           LL_PWR_EnableBatteryCharging
  */
__STATIC_INLINE void LL_PWR_EnableBatteryCharging(void)
{
  STM32_SET_BIT(PWR->CSR2, PWR_CSR2_VBE);
}

/**
  * @brief  Disable VBAT battery charging.
  * @rmtoll
  *   CSR2       VBE           LL_PWR_DisableBatteryCharging
  */
__STATIC_INLINE void LL_PWR_DisableBatteryCharging(void)
{
  STM32_CLEAR_BIT(PWR->CSR2, PWR_CSR2_VBE);
}

/**
  * @brief  Check if VBAT battery charging is enabled.
  * @rmtoll
  *   CSR2       VBE           LL_PWR_IsEnabledBatteryCharging
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBatteryCharging(void)
{
  return ((STM32_READ_BIT(PWR->CSR2, PWR_CSR2_VBE) == (PWR_CSR2_VBE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the battery charge resistor impedance.
  * @rmtoll
  *   CSR2       VBRS          LL_PWR_SetBattChargResistor
  * @param  resistor This parameter can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_1_5K
  */
__STATIC_INLINE void LL_PWR_SetBattChargResistor(uint32_t resistor)
{
  STM32_MODIFY_REG(PWR->CSR2, PWR_CSR2_VBRS, resistor);
}

/**
  * @brief  Get the battery charge resistor impedance.
  * @rmtoll
  *   CSR2       VBRS          LL_PWR_GetBattChargResistor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_1_5K
  */
__STATIC_INLINE uint32_t LL_PWR_GetBattChargResistor(void)
{
  return (STM32_READ_BIT(PWR->CSR2, PWR_CSR2_VBRS));
}

/**
  * @brief Enable UCPD configuration memorization in standby.
  * @rmtoll
  *   UCPDR      UCPD_STBY     LL_PWR_EnableUCPDRetentionStandbyMode
  * @note  This function must be called just before entering standby mode when using UCPD.
  */
__STATIC_INLINE void LL_PWR_EnableUCPDRetentionStandbyMode(void)
{
  /* Memorize UCPD configuration when entering standby mode */
  STM32_SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY);
}

/**
  * @brief Disable UCPD configuration memorization in standby.
  * @rmtoll
  *   UCPDR      UCPD_STBY     LL_PWR_DisableUCPDRetentionStandbyMode
  * @note  This function must be called on exiting the standby mode and before any UCPD
  *        configuration update.
  */
__STATIC_INLINE void LL_PWR_DisableUCPDRetentionStandbyMode(void)
{
  STM32_CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY);
}

/**
  * @brief  Check if the UCPD configuration memorization in standby is enabled.
  * @rmtoll
  *   UCPDR      UCPD_STBY     LL_PWR_IsEnabledUCPDRetentionStandbyMode
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUCPDRetentionStandbyMode(void)
{
  return ((STM32_READ_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY) == (PWR_UCPDR_UCPD_STBY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the UCPD dead battery behavior.
  * @rmtoll
  *   UCPDR      UCPD_DBDIS    LL_PWR_EnableUCPDDeadBattery
  */
__STATIC_INLINE void LL_PWR_EnableUCPDDeadBattery(void)
{
  STM32_CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief  Disable the UCPD dead battery behavior.
  * @rmtoll
  *   UCPDR      UCPD_DBDIS    LL_PWR_DisableUCPDDeadBattery
  */
__STATIC_INLINE void LL_PWR_DisableUCPDDeadBattery(void)
{
  STM32_SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief  Check if the UCPD dead battery behavior is enabled.
  * @warning when PWR_UCPDR_UCPD_DBDIS bit is set UCPD dead battery is disabled
  * @rmtoll
  *   UCPDR      UCPD_DBDIS    LL_PWR_IsEnabledUCPDDeadBattery
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUCPDDeadBattery(void)
{
  return ((STM32_READ_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS) == (PWR_UCPDR_UCPD_DBDIS)) ? 0UL : 1UL);
}

/**
  * @brief  Set system power mode.
  * @rmtoll
  *   CSR3       PDDS          LL_PWR_SetPowerMode
  * @param  mode : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STOP_MODE
  *         @arg @ref LL_PWR_STANDBY_MODE
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t mode)
{
  STM32_MODIFY_REG(PWR->CSR3, PWR_CSR3_PDDS, mode);
}

/**
  * @brief  Get system power mode.
  * @rmtoll
  *   CSR3       PDDS          LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STOP_MODE
  *         @arg @ref LL_PWR_STANDBY_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (STM32_READ_BIT(PWR->CSR3, PWR_CSR3_PDDS));
}

/**
  * @brief  Set the main internal regulator output voltage.
  * @rmtoll
  *   CSR4       VOS           LL_PWR_SetRegulatorVoltageScaling
  * @param  voltagescaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_0
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_1
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_2
  */
__STATIC_INLINE void LL_PWR_SetRegulatorVoltageScaling(uint32_t voltagescaling)
{
  STM32_MODIFY_REG(PWR->CSR4, PWR_CSR4_VOS, voltagescaling);
}

/**
  * @brief  Get the main internal regulator output voltage.
  * @rmtoll
  *   CSR4       VOS           LL_PWR_GetRegulatorVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_0
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_1
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_2
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulatorVoltageScaling(void)
{
  return (uint32_t)(STM32_READ_BIT(PWR->CSR4, PWR_CSR4_VOS));
}

/**
  * @brief  Get current voltage scaling applied to VCORE.
  * @rmtoll
  *   SR1        ACTVOS[1:0]   LL_PWR_GetActiveRegulatorVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_ACTIVE_VOLT_SCALE_0
  *         @arg @ref LL_PWR_ACTIVE_VOLT_SCALE_1
  *         @arg @ref LL_PWR_ACTIVE_VOLT_SCALE_2
  */
__STATIC_INLINE uint32_t LL_PWR_GetActiveRegulatorVoltageScaling(void)
{
  return (STM32_READ_BIT(PWR->SR1, PWR_SR1_ACTVOS));
}

/**
  * @brief  Enable the wake-up pin(s).
  * @rmtoll
  *   WKUPEPR    WKUPEN1       LL_PWR_EnableWakeUpPin \n
  *   WKUPEPR    WKUPEN2       LL_PWR_EnableWakeUpPin \n
  *   WKUPEPR    WKUPEN3       LL_PWR_EnableWakeUpPin \n
  *   WKUPEPR    WKUPEN4       LL_PWR_EnableWakeUpPin \n
  *   WKUPEPR    WKUPEN5       LL_PWR_EnableWakeUpPin \n
  *   WKUPEPR    WKUPEN6       LL_PWR_EnableWakeUpPin \n
  *   WKUPEPR    WKUPEN7       LL_PWR_EnableWakeUpPin \n
  *   WKUPEPR    WKUPEN8       LL_PWR_EnableWakeUpPin
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t wakeup_pin)
{
  STM32_SET_BIT(PWR->WKUPEPR, wakeup_pin);
}

/**
  * @brief  Disable the wake-up pin(s).
  * @rmtoll
  *   WKUPEPR    WKUPEN1       LL_PWR_DisableWakeUpPin \n
  *   WKUPEPR    WKUPEN2       LL_PWR_DisableWakeUpPin \n
  *   WKUPEPR    WKUPEN3       LL_PWR_DisableWakeUpPin \n
  *   WKUPEPR    WKUPEN4       LL_PWR_DisableWakeUpPin \n
  *   WKUPEPR    WKUPEN5       LL_PWR_DisableWakeUpPin \n
  *   WKUPEPR    WKUPEN6       LL_PWR_DisableWakeUpPin \n
  *   WKUPEPR    WKUPEN7       LL_PWR_DisableWakeUpPin \n
  *   WKUPEPR    WKUPEN8       LL_PWR_DisableWakeUpPin
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t wakeup_pin)
{
  STM32_CLEAR_BIT(PWR->WKUPEPR, wakeup_pin);
}

/**
  * @brief  Check if the wake-up pin x is enabled.
  * @rmtoll
  *   WKUPEPR    WKUPEN1       LL_PWR_IsEnabledWakeUpPin \n
  *   WKUPEPR    WKUPEN2       LL_PWR_IsEnabledWakeUpPin \n
  *   WKUPEPR    WKUPEN3       LL_PWR_IsEnabledWakeUpPin \n
  *   WKUPEPR    WKUPEN4       LL_PWR_IsEnabledWakeUpPin \n
  *   WKUPEPR    WKUPEN5       LL_PWR_IsEnabledWakeUpPin \n
  *   WKUPEPR    WKUPEN6       LL_PWR_IsEnabledWakeUpPin \n
  *   WKUPEPR    WKUPEN7       LL_PWR_IsEnabledWakeUpPin \n
  *   WKUPEPR    WKUPEN8       LL_PWR_IsEnabledWakeUpPin
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t wakeup_pin)
{
  return ((STM32_READ_BIT(PWR->WKUPEPR, wakeup_pin) == (wakeup_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Set the wake-up pin polarity for the event detection.
  * @rmtoll
  *   WKUPEPR    WKUPP1        LL_PWR_SetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP2        LL_PWR_SetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP3        LL_PWR_SetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP4        LL_PWR_SetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP5        LL_PWR_SetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP6        LL_PWR_SetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP7        LL_PWR_SetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP8        LL_PWR_SetWakeUpPinPolarity
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_HIGH
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_LOW
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarity(uint32_t wakeup_pin, uint32_t polarity)
{
  STM32_MODIFY_REG(PWR->WKUPEPR, (uint32_t)(PWR_WKUPEPR_WKUPP1 << STM32_POSITION_VAL(wakeup_pin)), \
                   (uint32_t)(polarity << (PWR_WKUPEPR_WKUPP1_Pos + STM32_POSITION_VAL(wakeup_pin))));
}

/**
  * @brief  Get the wake-up pin polarity for the event detection.
  * @rmtoll
  *   WKUPEPR    WKUPP1        LL_PWR_GetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP2        LL_PWR_GetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP3        LL_PWR_GetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP4        LL_PWR_GetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP5        LL_PWR_GetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP6        LL_PWR_GetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP7        LL_PWR_GetWakeUpPinPolarity \n
  *   WKUPEPR    WKUPP8        LL_PWR_GetWakeUpPinPolarity
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_HIGH
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_LOW
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPolarity(uint32_t wakeup_pin)
{
  return ((STM32_READ_BIT(PWR->WKUPEPR, (uint32_t)(PWR_WKUPEPR_WKUPP1 << STM32_POSITION_VAL(wakeup_pin))) != 0UL) \
          ? 1UL : 0UL);
}

/**
  * @brief  Set the wake-up pin pull.
  * @rmtoll
  *   WKUPEPR    WKUPPUPD1     LL_PWR_SetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD2     LL_PWR_SetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD3     LL_PWR_SetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD4     LL_PWR_SetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD5     LL_PWR_SetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD6     LL_PWR_SetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD7     LL_PWR_SetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD8     LL_PWR_SetWakeUpPinPull
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @param  pull This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_NO
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_UP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_DOWN
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPull(uint32_t wakeup_pin, uint32_t pull)
{
  uint32_t clear = (PWR_WKUPEPR_WKUPPUPD1 << (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * (STM32_POSITION_VAL(wakeup_pin))));

  uint32_t set = (pull << (PWR_WKUPEPR_WKUPPUPD1_Pos + \
                           (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * (STM32_POSITION_VAL(wakeup_pin)))));

  STM32_MODIFY_REG(PWR->WKUPEPR, clear, set);
}

/**
  * @brief  Get the wake-up pin pull.
  * @rmtoll
  *   WKUPEPR    WKUPPUPD1     LL_PWR_GetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD2     LL_PWR_GetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD3     LL_PWR_GetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD4     LL_PWR_GetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD5     LL_PWR_GetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD6     LL_PWR_GetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD7     LL_PWR_GetWakeUpPinPull \n
  *   WKUPEPR    WKUPPUPD8     LL_PWR_GetWakeUpPinPull
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_NO
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_UP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_DOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPull(uint32_t wakeup_pin)
{
  uint32_t regValue = STM32_READ_BIT(PWR->WKUPEPR,                                                            \
                                     (PWR_WKUPEPR_WKUPPUPD1 <<                                                 \
                                      ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * STM32_POSITION_VAL(wakeup_pin)) & \
                                       LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));

  return (uint32_t)(regValue >> ((PWR_WKUPEPR_WKUPPUPD1_Pos + ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * \
                                                                STM32_POSITION_VAL(wakeup_pin)))) &    \
                                 LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));
}

/**
  * @brief  Enable the pull-up and pull-down configuration.
  * @rmtoll
  *   APCR       APC           LL_PWR_EnablePUPDConfig
  */
__STATIC_INLINE void LL_PWR_EnablePUPDConfig(void)
{
  STM32_SET_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Disable the pull-up and pull-down configuration.
  * @rmtoll
  *   APCR       APC           LL_PWR_DisablePUPDConfig
  */
__STATIC_INLINE void LL_PWR_DisablePUPDConfig(void)
{
  STM32_CLEAR_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Check if the pull-up and pull-down configuration is enabled.
  * @rmtoll
  *   APCR       APC           LL_PWR_IsEnabledPUPDConfig
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPUPDConfig(void)
{
  return ((STM32_READ_BIT(PWR->APCR, PWR_APCR_APC) == (PWR_APCR_APC)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the I3C pull-up functionality for the specified pin(s).
  * @rmtoll
  *   I3CPUCR    I3CPA15_PU    LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPB3_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPB4_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPB8_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPB9_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPC8_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPC9_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPD0_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPD1_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPD6_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPD7_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPE5_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPE6_PU     LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPG13_PU    LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPG14_PU    LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPH11_PU    LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPH12_PU    LL_PWR_EnableI3CPullUp \n
  *   I3CPUCR    I3CPI2_PU     LL_PWR_EnableI3CPullUp
  * @param  i3cpullup_pin This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PA15
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB3
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB4
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB8
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB9
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PC8
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PC9
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD0
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD1
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD6
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD7
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PE5
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PE6
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PG13
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PG14
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PH11
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PH12
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PI2
  */
__STATIC_INLINE void LL_PWR_EnableI3CPullUp(uint32_t i3cpullup_pin)
{
  STM32_SET_BIT(PWR->I3CPUCR, i3cpullup_pin);
}

/**
  * @brief  Disable the I3C pull-up functionality for the specified pin(s).
  * @rmtoll
  *   I3CPUCR    I3CPA15_PU    LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPB3_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPB4_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPB8_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPB9_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPC8_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPC9_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPD0_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPD1_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPD6_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPD7_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPE5_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPE6_PU     LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPG13_PU    LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPG14_PU    LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPH11_PU    LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPH12_PU    LL_PWR_DisableI3CPullUp \n
  *   I3CPUCR    I3CPI2_PU     LL_PWR_DisableI3CPullUp
  * @param  i3cpullup_pin This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PA15
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB3
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB4
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB8
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB9
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PC8
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PC9
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD0
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD1
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD6
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD7
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PE5
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PE6
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PG13
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PG14
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PH11
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PH12
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PI2
  */
__STATIC_INLINE void LL_PWR_DisableI3CPullUp(uint32_t i3cpullup_pin)
{
  STM32_CLEAR_BIT(PWR->I3CPUCR, i3cpullup_pin);
}

/**
  * @brief  Check if the I3C pull-up functionality is enabled for the specified pin.
  * @rmtoll
  *   I3CPUCR    I3CPA15_PU    LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPB3_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPB4_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPB8_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPB9_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPC8_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPC9_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPD0_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPD1_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPD6_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPD7_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPE5_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPE6_PU     LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPG13_PU    LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPG14_PU    LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPH11_PU    LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPH12_PU    LL_PWR_IsEnabledI3CPullUp \n
  *   I3CPUCR    I3CPI2_PU     LL_PWR_IsEnabledI3CPullUp
  * @param  i3cpullup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PA15
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB3
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB4
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB8
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PB9
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PC8
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PC9
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD0
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD1
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD6
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PD7
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PE5
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PE6
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PG13
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PG14
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PH11
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PH12
  *         @arg @ref LL_PWR_I3C1_PULL_UP_PI2
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledI3CPullUp(uint32_t i3cpullup_pin)
{
  return ((STM32_READ_BIT(PWR->I3CPUCR, i3cpullup_pin) == (i3cpullup_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the XSPI pull-up functionality for the specified pin(s).
  * @rmtoll
  *   XSPIPUCR   XSPIPG10_PU   LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPD3_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPD2_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPD1_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPD0_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPB2_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPB1_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPA5_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPA4_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPA3_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPA2_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPA0_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPF2_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPH1_PU    LL_PWR_EnableXSPIPullUp \n
  *   XSPIPUCR   XSPIPH0_PU    LL_PWR_EnableXSPIPullUp
  * @param  xspipullup_pin This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PG10
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD3
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD1
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD0
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PB2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PB1
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA5
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA4
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA3
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA0
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PF2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PH1
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PH0
  */
__STATIC_INLINE void LL_PWR_EnableXSPIPullUp(uint32_t xspipullup_pin)
{
  STM32_SET_BIT(PWR->XSPIPUCR, xspipullup_pin);
}

/**
  * @brief  Disable the XSPI pull-up functionality for the specified pin(s).
  * @rmtoll
  *   XSPIPUCR   XSPIPG10_PU   LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPD3_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPD2_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPD1_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPD0_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPB2_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPB1_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPA5_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPA4_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPA3_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPA2_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPA0_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPF2_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPH1_PU    LL_PWR_DisableXSPIPullUp \n
  *   XSPIPUCR   XSPIPH0_PU    LL_PWR_DisableXSPIPullUp
  * @param  xspipullup_pin This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PG10
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD3
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD1
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD0
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PB2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PB1
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA5
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA4
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA3
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA0
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PF2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PH1
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PH0
  */
__STATIC_INLINE void LL_PWR_DisableXSPIPullUp(uint32_t xspipullup_pin)
{
  STM32_CLEAR_BIT(PWR->XSPIPUCR, xspipullup_pin);
}

/**
  * @brief  Check if the XSPI pull-up functionality is enabled for the specified pin.
  * @rmtoll
  *   XSPIPUCR   XSPIPG10_PU   LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPD3_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPD2_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPD1_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPD0_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPB2_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPB1_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPA5_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPA4_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPA3_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPA2_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPA0_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPF2_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPH1_PU    LL_PWR_IsEnabledXSPIPullUp \n
  *   XSPIPUCR   XSPIPH0_PU    LL_PWR_IsEnabledXSPIPullUp
  * @param  xspipullup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PG10
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD3
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD1
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PD0
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PB2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PB1
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA5
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA4
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA3
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PA0
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PF2
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PH1
  *         @arg @ref LL_PWR_XSPI1_PULL_UP_PH0
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledXSPIPullUp(uint32_t xspipullup_pin)
{
  return ((STM32_READ_BIT(PWR->XSPIPUCR, xspipullup_pin) == (xspipullup_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the XSPI pull-down functionality for the specified pin(s).
  * @rmtoll
  *   XSPIPDCR   XSPIPG10_PD   LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPD3_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPD2_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPD1_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPD0_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPB2_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPB1_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPA5_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPA4_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPA3_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPA2_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPA0_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPF2_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPH1_PD    LL_PWR_EnableXSPIPullDown \n
  *   XSPIPDCR   XSPIPH0_PD    LL_PWR_EnableXSPIPullDown
  * @param  xspipulldown_pin This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PG10
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD3
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD1
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD0
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PB2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PB1
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA5
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA4
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA3
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA0
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PF2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PH1
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PH0
  */
__STATIC_INLINE void LL_PWR_EnableXSPIPullDown(uint32_t xspipulldown_pin)
{
  STM32_SET_BIT(PWR->XSPIPDCR, xspipulldown_pin);
}

/**
  * @brief  Disable the XSPI pull-down functionality for the specified pin(s).
  * @rmtoll
  *   XSPIPDCR   XSPIPG10_PD   LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPD3_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPD2_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPD1_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPD0_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPB2_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPB1_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPA5_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPA4_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPA3_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPA2_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPA0_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPF2_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPH1_PD    LL_PWR_DisableXSPIPullDown \n
  *   XSPIPDCR   XSPIPH0_PD    LL_PWR_DisableXSPIPullDown
  * @param  xspipulldown_pin This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PG10
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD3
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD1
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD0
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PB2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PB1
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA5
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA4
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA3
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA0
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PF2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PH1
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PH0
  */
__STATIC_INLINE void LL_PWR_DisableXSPIPullDown(uint32_t xspipulldown_pin)
{
  STM32_CLEAR_BIT(PWR->XSPIPDCR, xspipulldown_pin);
}

/**
  * @brief  Check if the XSPI pull-down functionality is enabled for the specified pin.
  * @rmtoll
  *   XSPIPDCR   XSPIPG10_PD   LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPD3_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPD2_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPD1_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPD0_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPB2_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPB1_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPA5_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPA4_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPA3_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPA2_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPA0_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPF2_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPH1_PD    LL_PWR_IsEnabledXSPIPullDown \n
  *   XSPIPDCR   XSPIPH0_PD    LL_PWR_IsEnabledXSPIPullDown
  * @param  xspipulldown_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PG10
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD3
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD1
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PD0
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PB2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PB1
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA5
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA4
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA3
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PA0
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PF2
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PH1
  *         @arg @ref LL_PWR_XSPI1_PULL_DOWN_PH0
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledXSPIPullDown(uint32_t xspipulldown_pin)
{
  return ((STM32_READ_BIT(PWR->XSPIPDCR, xspipulldown_pin) == (xspipulldown_pin)) ? 1UL : 0UL);
}

/** @defgroup PWR_LL_EF_FLAG_MANAGEMENT PWR Flag management
  * @{
  */

/**
  * @brief  Indicate whether the voltage level is ready for current actual used VOS.
  * @rmtoll
  *   SR1        ACTVOSRDY     LL_PWR_IsActiveFlag_ACTVOS
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_ACTVOS(void)
{
  return ((STM32_READ_BIT(PWR->SR1, PWR_SR1_ACTVOSRDY) == (PWR_SR1_ACTVOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether VDD voltage is below the selected PVD threshold.
  * @rmtoll
  *   SR1        PVDO          LL_PWR_IsActiveFlag_PVDO
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((STM32_READ_BIT(PWR->SR1, PWR_SR1_PVDO) == (PWR_SR1_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether VDDA voltage is below the selected AVD threshold.
  * @rmtoll
  *   SR1        AVDO          LL_PWR_IsActiveFlag_AVDO
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_AVDO(void)
{
  return ((STM32_READ_BIT(PWR->SR1, PWR_SR1_AVDO) == (PWR_SR1_AVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Get backup regulator ready flag.
  * @rmtoll
  *   CSR1       BRRDY         LL_PWR_IsActiveFlag_BRRDY
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_BRRDY(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_BRRDY) == (PWR_CSR1_BRRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VBAT level is above or below low threshold.
  * @rmtoll
  *   CSR1       VBATL         LL_PWR_IsActiveFlag_VBATL
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATL(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_VBATL) == (PWR_CSR1_VBATL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VBAT level is above or below high threshold.
  * @rmtoll
  *   CSR1       VBATH         LL_PWR_IsActiveFlag_VBATH
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATH(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_VBATH) == (PWR_CSR1_VBATH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the core temperature level is above or below low threshold.
  * @rmtoll
  *   CSR1       TEMPL         LL_PWR_IsActiveFlag_TEMPL
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPL(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_TEMPL) == (PWR_CSR1_TEMPL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the core temperature level is above or below high threshold.
  * @rmtoll
  *   CSR1       TEMPH         LL_PWR_IsActiveFlag_TEMPH
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPH(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_TEMPH) == (PWR_CSR1_TEMPH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the SMPS step-down converter supply is ready.
  * @rmtoll
  *   CSR2        SDRDY        LL_PWR_IsActiveFlag_SDRDY
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SDRDY(void)
{
  return ((STM32_READ_BIT(PWR->CSR2, PWR_CSR2_SDRDY) == (PWR_CSR2_SDRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get system stop flag.
  * @rmtoll
  *   CSR3       STOPF         LL_PWR_IsActiveFlag_STOP
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_STOP(void)
{
  return ((STM32_READ_BIT(PWR->CSR3, PWR_CSR3_STOPF) == (PWR_CSR3_STOPF)) ? 1UL : 0UL);
}

/**
  * @brief  Get system standby flag.
  * @rmtoll
  *   CSR3       SBF           LL_PWR_IsActiveFlag_SB
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return ((STM32_READ_BIT(PWR->CSR3, PWR_CSR3_SBF) == (PWR_CSR3_SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the regulator is ready in the selected voltage range.
  *         or if its output voltage is still changing to the required voltage level
  * @rmtoll
  *   CSR4       VOSRDY        LL_PWR_IsActiveFlag_VOS
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VOS(void)
{
  return ((STM32_READ_BIT(PWR->CSR4, PWR_CSR4_VOSRDY) == (PWR_CSR4_VOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get wake-up flag 1.
  * @rmtoll
  *   WKUPFR     WKUPF1        LL_PWR_IsActiveFlag_WU1
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF1) == (PWR_WKUPFR_WKUPF1)) ? 1UL : 0UL);
}

/**
  * @brief  Get wake-up flag 2.
  * @rmtoll
  *   WKUPFR     WKUPF2        LL_PWR_IsActiveFlag_WU2
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF2) == (PWR_WKUPFR_WKUPF2)) ? 1UL : 0UL);
}

/**
  * @brief  Get wake-up flag 3.
  * @rmtoll
  *   WKUPFR     WKUPF3        LL_PWR_IsActiveFlag_WU3
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF3) == (PWR_WKUPFR_WKUPF3)) ? 1UL : 0UL);
}

/**
  * @brief  Get wake-up flag 4.
  * @rmtoll
  *   WKUPFR     WKUPF4        LL_PWR_IsActiveFlag_WU4
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF4) == (PWR_WKUPFR_WKUPF4)) ? 1UL : 0UL);
}

/**
  * @brief  Get wake-up flag 5.
  * @rmtoll
  *   WKUPFR     WKUPF5        LL_PWR_IsActiveFlag_WU5
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU5(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF5) == (PWR_WKUPFR_WKUPF5)) ? 1UL : 0UL);
}

/**
  * @brief  Get wake-up flag 6.
  * @rmtoll
  *   WKUPFR     WKUPF6        LL_PWR_IsActiveFlag_WU6
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU6(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF6) == (PWR_WKUPFR_WKUPF6)) ? 1UL : 0UL);
}

/**
  * @brief  Get wake-up flag 7.
  * @rmtoll
  *   WKUPFR     WKUPF7        LL_PWR_IsActiveFlag_WU7
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU7(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF7) == (PWR_WKUPFR_WKUPF7)) ? 1UL : 0UL);
}

/**
  * @brief  Get wake-up flag 8.
  * @rmtoll
  *   WKUPFR     WKUPF8        LL_PWR_IsActiveFlag_WU8
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU8(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF8) == (PWR_WKUPFR_WKUPF8)) ? 1UL : 0UL);
}

/**
  * @brief  Check if a wake-up event is detected on a selected wake-up pin.
  * @rmtoll
  *   WKUPFR     WKUPFx[1:8]   LL_PWR_IsActiveFlag_WU
  * @param  wakeup_pin
  *         This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @retval 1 if enabled, 0 if disabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU(uint32_t wakeup_pin)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, wakeup_pin) == (wakeup_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Clear stop flag.
  * @rmtoll
  *   CSR3       CSSF          LL_PWR_ClearFlag_STOP
  */
__STATIC_INLINE void LL_PWR_ClearFlag_STOP(void)
{
  STM32_SET_BIT(PWR->CSR3, PWR_CSR3_CSSF);
}

/**
  * @brief  Clear standby flag.
  * @rmtoll
  *   CSR3       CSSF          LL_PWR_ClearFlag_SB
  */
__STATIC_INLINE void LL_PWR_ClearFlag_SB(void)
{
  STM32_SET_BIT(PWR->CSR3, PWR_CSR3_CSSF);
}

/**
  * @brief  Clear wake-up flag 1.
  * @rmtoll
  *   WKUPCR     WKUPC1        LL_PWR_ClearFlag_WU1
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1(void)
{
  STM32_WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC1);
}

/**
  * @brief  Clear wake-up flag 2.
  * @rmtoll
  *   WKUPCR     WKUPC2        LL_PWR_ClearFlag_WU2
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2(void)
{
  STM32_WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC2);
}

/**
  * @brief  Clear wake-up flag 3.
  * @rmtoll
  *   WKUPCR     WKUPC3        LL_PWR_ClearFlag_WU3
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU3(void)
{
  STM32_WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC3);
}

/**
  * @brief  Clear wake-up flag 4.
  * @rmtoll
  *   WKUPCR     WKUPC4        LL_PWR_ClearFlag_WU4
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU4(void)
{
  STM32_WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC4);
}

/**
  * @brief  Clear wake-up flag 5.
  * @rmtoll
  *   WKUPCR     WKUPC5        LL_PWR_ClearFlag_WU5
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU5(void)
{
  STM32_WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC5);
}

/**
  * @brief  Clear wake-up flag 6.
  * @rmtoll
  *   WKUPCR     WKUPC6        LL_PWR_ClearFlag_WU6
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU6(void)
{
  STM32_WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC6);
}

/**
  * @brief  Clear wake-up flag 7.
  * @rmtoll
  *   WKUPCR     WKUPC7        LL_PWR_ClearFlag_WU7
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU7(void)
{
  STM32_WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC7);
}

/**
  * @brief  Clear wake-up flag 8.
  * @rmtoll
  *   WKUPCR     WKUPC8        LL_PWR_ClearFlag_WU8
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU8(void)
{
  STM32_WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC8);
}

/**
  * @brief  Clear the selected wake-up pin flag(s).
  * @rmtoll
  *   WKUPCR     WKUPCx        LL_PWR_ClearFlag_WU
  * @param  wakeup_pin This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(uint32_t wakeup_pin)
{
  STM32_WRITE_REG(PWR->WKUPCR, wakeup_pin);
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

/**
  * @}
  */

#endif /* defined (PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7Pxx_LL_PWR_H */

