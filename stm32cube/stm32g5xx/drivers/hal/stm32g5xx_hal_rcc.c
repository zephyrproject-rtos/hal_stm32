/**
  ******************************************************************************
  * @file    stm32g5xx_hal_rcc.c
  * @brief   RCC HAL module driver.
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
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32G5XX_HAL_Driver
  * @{
  */
#if defined (RCC)
#if defined(USE_HAL_RCC_MODULE) && (USE_HAL_RCC_MODULE == 1)
/** @defgroup RCC RCC
  * @{
  */
/** @defgroup RCC_Introduction RCC Introduction
  * @{

  - The RCC (Reset and Clock Control) Hardware Abstraction Layer (HAL) provides a comprehensive set of APIs to
    interface with the STM32G5xx RCC peripheral.
  - It simplifies the configuration, initialization, and management of system and peripheral clocks, reset control,
    and security attributes.
  - The driver supports multiple oscillators (HSI, HSI48, HSE, LSE, LSI) and two PLLs with fractional dividers.
  - Key features include configuration of all bus prescalers, flexible peripheral kernel clock control,
    clock security system management (CSS), low-power clock gating and system reset to default states.
  - Peripheral clock management APIs allow enabling, disabling, and resetting clocks on various buses (AHB, APB)
    with fine-grained control.
  - Security and privileged access levels attributes management functions allow configuration of secure, privileged
    access rights to RCC resources, supporting secure execution environments.
  - The HAL RCC driver ensures some degree of portability and consistent behavior across STM32G5xx microcontroller
    series for common features, facilitating robust, secure, and power-efficient clock and reset management in diverse
    embedded applications

  */
/**
  * @}
  */

/** @defgroup RCC_How_To_Use RCC How To Use
  * @{

This file provides firmware functions to manage the following
functionalities of the Reset and Clock Control (RCC) peripheral:

- Configuration and reset functions
- Oscillators and Peripherals Control functions
- Bus configuration functions

Main APIs are not allowed to perform any other actions than their main objective (for instance, it is not allowed to
disable a PLL or an oscillator inside an enable function).

For performance reasons, few functionalities are not supported by the HAL driver but these functionalities are covered
by the LL driver (for instance, interrupt management).

If the system clock is dynamically changed during runtime by the application or example code, it must call
HAL_UpdateCoreClock() (a HAL generic driver function) at the end of the change to update SystemCoreClock and the
systick (used by CMSIS) accordingly. The driver updates the SystemCoreClock variable and systick only in the
HAL_RCC_Reset() and HAL_RCC_ResetSystemClock() functions.

## RCC specific features

After exiting from standby or reset, the device is running from High Speed Internal (HSI) oscillator
(by default to 64MHz).

- There is no prescaler on High speed (AHBs) and Low speed (APBs) buses:
all peripherals mapped on these buses are running at sysclk frequency.
- The clock for all peripherals is switched off, except the SRAM and FLASH.

Once the device started from reset, the application can:

- Configure the clock source to be used to drive the System clock
(if the application needs higher frequency/performance)
- Configure the System clock frequency and Flash settings
- Configure the AHB and APB buses prescalers
- Enable the clock for the peripheral(s) to be used
- Configure the clock source(s) for peripherals whose clocks receive an independent kernel clocks.
- Configure peripherals supporting the low power mode (These peripherals are able to generate a kernel clock request
and a AHB/APB bus clock request when they need, in order to operate and update their status register even in Stop mode).
- Get the clock frequency of peripherals whose clocks receive independent kernel clocks.
 */
/**
  * @}
  */

/** @defgroup RCC_Configuration_Table RCC Configuration Table
  * @{
## Configuration inside the RCC driver

Config defines            | Description               | Default value | Note
------------------------- | ------------------------- | ------------- | ------------------------------------
PRODUCT                   | from IDE                  | Defined       | The selected product (ex STM32G562xx)
PERIPHERAL                | from CMSIS                | Defined       | Periph. available on the selected product
USE_ASSERT_DBG_PARAM      | from IDE                  | None          | When defined, enable the params assert
USE_HAL_CHECK_PARAM       | from hal_conf.h           | 0             | When set, parameters are checked in runtime
USE_HAL_RCC_MODULE        | from hal_conf.h           | 1             | When set, HAL RCC module is enabled
USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT | from hal_conf.h  | 0      | When set, RCC peripherals configuration reset
USE_HAL_RCC_RESET_RTC_DOMAIN              | from hal_conf.h  | 0      | When set, Resources under backup domain reset
USE_EXTERNAL_ENV          | from IDE                  | Defined       | When set, ext. oscillators values are defined
LSE_VALUE                 | from stm32_external_env.h | 32 Khz        | Frequency of LSE oscillator (USE_EXTERNAL_ENV)
HSE_VALUE                 | from stm32_external_env.h | 32 Mhz        | Frequency of HSE oscillator (USE_EXTERNAL_ENV)
AUDIOCLK_VALUE            | from stm32_external_env.h | 48 kHz        | Frequency of AUDIO clock (USE_EXTERNAL_ENV)
CMSE_SECURE_EXECUTION_ENVIRONMENT | Trust Zone                | NA            | Defined in secure context
HSI_VALUE                 | st32g5xxxx.h              | 64 MHz        | Frequency of HSI oscillator
HSI48_VALUE               | st32g5xxxx.h              | 48 MHz        | Frequency of HSI48 oscillator
  *
  */

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/** @defgroup RCC_Private_Typedef RCC Private Type definition
  * @{
  */
typedef  uint32_t (*rcc_cb_timeout_t)(void); /*!< RCC internal Callback pointer definition */
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants and enumerations
  * @{
  */

/**
  * @brief Timeout values
  * @{
  */
#if defined(HSE_VALUE)
#define RCC_HSE_TIMEOUT_VALUE           HSE_STARTUP_TIMEOUT /*!< HSE Timeout value                              */
#endif /* HSE_VALUE */

#if defined(LSE_VALUE)
#define RCC_LSE_TIMEOUT_VALUE           LSE_STARTUP_TIMEOUT /*!< LSE Timeout value                              */
#endif /* LSE_VALUE */

#define RCC_HSI_TIMEOUT_VALUE           2UL      /*!< 2 ms (minimum Tick + 1)                                   */
#define RCC_HSI48_TIMEOUT_VALUE         2UL      /*!< 2 ms (minimum Tick + 1)                                   */
/* LSI maximum timeout is 16 us plus 4 LSI clock cycles when prediv is used                                     */
#define RCC_LSI_TIMEOUT_VALUE           ((10u * 128u * 1000u) / LSI_VALUE) /*!< 40 ms for LSI at 32KHz          */

#define RCC_PLL1_TIMEOUT_VALUE          2UL /*!< 2 ms (minimum Tick + 1)                                         */
#define RCC_PLL2_TIMEOUT_VALUE          2UL /*!< 2 ms (minimum Tick + 1)                                         */
#define RCC_PLL_FRAC_WAIT_VALUE         1UL /*!< PLL Fractional part waiting time before new latch enable : 1 ms */

#define RCC_CLOCKSWITCH_TIMEOUT_VALUE   5000UL   /*!< 5 s                                                       */

/**
  * @}
  */

/**
  * @brief PLL values
  * @{
  */
#define PLL_FRACN_MODULUS 0x2000U
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */

/**
  * @brief Get the ADC kernel clock prescaler
  */

/*! Macro to get the ADC kernel clock prescaler bit field value */
#define RCC_ADCDIV_BIT_VALUE  ((LL_RCC_GetADCPrescaler() >> RCC_CCIPR5_ADCDIV_Pos))

/*! Macro to get the ADC kernel clock prescaler */
#define RCC_GET_ADC_PRESCALER() (((RCC_ADCDIV_BIT_VALUE) == 0x0U) ? 1U :   \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0x1U) ? 2U :   \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0x2U) ? 4U :   \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0x3U) ? 6U :   \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0x4U) ? 8U :   \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0x5U) ? 10U :  \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0x6U) ? 12U :  \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0x7U) ? 16U :  \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0x8U) ? 32U :  \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0x9U) ? 64U :  \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0xAU) ? 128U : \
                                 ((RCC_ADCDIV_BIT_VALUE) == 0xBU) ? 256U : 1U)

/**
  * @brief Get the PLAY1 kernel clock divider
  */

/*! Macro to get the PLAY1 kernel clock divider */
#define RCC_GET_PLAY1_DIVIDER()  ((uint32_t)1U << (LL_RCC_GetPLAY1Divider() >> RCC_CCIPR3_PLAY1DIV_Pos))

/*! Macro to check the HSE clock mode */
#define IS_RCC_HSE_MODE_ENABLE(mode) (((mode) == HAL_RCC_HSE_ON)                \
                                      || ((mode) == HAL_RCC_HSE_BYPASS)         \
                                      || ((mode) == HAL_RCC_HSE_BYPASS_DIGITAL))

/*! Macro to check the LSE clock mode */
#define IS_RCC_LSE_MODE_ENABLE(mode) (((mode) == HAL_RCC_LSE_ON)                \
                                      || ((mode) == HAL_RCC_LSE_BYPASS))

/*! Macro to check the LSE drive capability */
#define IS_RCC_LSE_DRIVE(drive) (((drive) == LL_RCC_LSEDRIVE_MEDIUMLOW)       \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_MEDIUMHIGH) \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_HIGH))

/*! Macro to check the HSI divider */
#define IS_RCC_HSI_DIV(hsi_div) (((hsi_div) == HAL_RCC_HSI_DIV1)    \
                                 || ((hsi_div) == HAL_RCC_HSI_DIV2) \
                                 || ((hsi_div) == HAL_RCC_HSI_DIV4) \
                                 || ((hsi_div) == HAL_RCC_HSI_DIV8))

/*! Macro to check the HSI calibration value */
#define IS_RCC_HSI_CALIBRATION_VALUE(value) ((value) <= 127UL)

/*! Macro to check the system clock source */
#define IS_RCC_SYSCLKSOURCE(source) (((source) == HAL_RCC_SYSCLK_SRC_HSI)     \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_HSE)  \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_PLLCLK))

/*! Macro to check the SysTick clock source */
#define IS_RCC_SYSTICK_CLK(source) (((source) == HAL_RCC_SYSTICK_CLK_SRC_HCLKDIV8) \
                                    || ((source) == HAL_RCC_SYSTICK_CLK_SRC_LSE)  \
                                    || ((source) == HAL_RCC_SYSTICK_CLK_SRC_LSI))

/*! Macro to check the HCLK prescaler */
#define IS_RCC_HCLK(hclk) (((hclk) == HAL_RCC_HCLK_PRESCALER1)      \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER2)   \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER4)   \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER8)   \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER16)  \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER64)  \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER128) \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER256) \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER512))

/*! Macro to check the PCLK prescaler */
#define IS_RCC_PCLK(pclk) (((pclk) == HAL_RCC_PCLK_PRESCALER1)     \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER2)  \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER4)  \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER8)  \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER16))

/*! Macro to check the RTC clock source */
#define IS_RCC_RTC_CLK(source) (((source) == HAL_RCC_RTC_CLK_SRC_NONE)       \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_LSE)       \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_LSI)       \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV))

/*! Macro to check the RTC HSE divider */
#define IS_RCC_RTC_HSEDIV(div)  ((div) <= 63U)

/*! Macro to check the MCO clock source */
#define IS_RCC_MCOSOURCE(source) (((source) == HAL_RCC_MCO1_SRC_HSI)        \
                                  || ((source) == HAL_RCC_MCO1_SRC_LSE)     \
                                  || ((source) == HAL_RCC_MCO1_SRC_HSE)     \
                                  || ((source) == HAL_RCC_MCO1_SRC_PLL1Q)   \
                                  || ((source) == HAL_RCC_MCO1_SRC_HSI48)   \
                                  || ((source) == HAL_RCC_MCO2_SRC_SYSCLK)  \
                                  || ((source) == HAL_RCC_MCO2_SRC_PLL2P)   \
                                  || ((source) == HAL_RCC_MCO2_SRC_HSE)     \
                                  || ((source) == HAL_RCC_MCO2_SRC_PLL1P)    \
                                  || ((source) == HAL_RCC_MCO2_SRC_LSI))

/*! Macro to check the MCO prescaler */
#define IS_RCC_MCOPRE(div) (((div) == HAL_RCC_MCO1_NO_CLK)    \
                            || ((div) == HAL_RCC_MCO1_PRESCALER1)   \
                            || ((div) == HAL_RCC_MCO1_PRESCALER2)   \
                            || ((div) == HAL_RCC_MCO1_PRESCALER3)   \
                            || ((div) == HAL_RCC_MCO1_PRESCALER4)   \
                            || ((div) == HAL_RCC_MCO1_PRESCALER5)   \
                            || ((div) == HAL_RCC_MCO1_PRESCALER6)   \
                            || ((div) == HAL_RCC_MCO1_PRESCALER7)   \
                            || ((div) == HAL_RCC_MCO1_PRESCALER8)   \
                            || ((div) == HAL_RCC_MCO1_PRESCALER9)   \
                            || ((div) == HAL_RCC_MCO1_PRESCALER10)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER11)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER12)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER13)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER14)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER15)  \
                            || ((div) == HAL_RCC_MCO2_NO_CLK) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER1)   \
                            || ((div) == HAL_RCC_MCO2_PRESCALER2)   \
                            || ((div) == HAL_RCC_MCO2_PRESCALER3)   \
                            || ((div) == HAL_RCC_MCO2_PRESCALER4)   \
                            || ((div) == HAL_RCC_MCO2_PRESCALER5)   \
                            || ((div) == HAL_RCC_MCO2_PRESCALER6)   \
                            || ((div) == HAL_RCC_MCO2_PRESCALER7)   \
                            || ((div) == HAL_RCC_MCO2_PRESCALER8)   \
                            || ((div) == HAL_RCC_MCO2_PRESCALER9)   \
                            || ((div) == HAL_RCC_MCO2_PRESCALER10)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER11)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER12)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER13)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER14)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER15))

/*! Macro to check the ICLK source */
#define IS_RCC_ICLK(iclk) (((iclk) == HAL_RCC_ICLK1) \
                           || ((iclk) == HAL_RCC_ICLK2))

/*! Macro to check the ICLK divider value */
#define IS_RCC_ICLK_DIV_VALUE(iclkdiv) (((iclkdiv) == HAL_RCC_ICLK_DIV5) \
                                        || ((iclkdiv) == HAL_RCC_ICLK_DIV3))

/*! Macro to check the PLL source */
#define IS_RCC_PLL_SOURCE(source) (((source) == HAL_RCC_PLL_SRC_NO_CLK)  \
                                   || ((source) == HAL_RCC_PLL_SRC_HSI)  \
                                   || ((source) == HAL_RCC_PLL_SRC_HSE))

/*! Macro to check the PLL fractional value */
#define IS_RCC_PLL_FRACN_VALUE(value) ((value) <= 8191U)

/*! Macro to check the PLLN value */
#define IS_RCC_PLLN_VALUE(value) ((4U <= (value)) && ((value) <= 512U))

/*! Macro to check the PLLM value */
#define IS_RCC_PLLM_VALUE(value) ((value) <= 63U)

/*! Macro to check the PLLP value */
#define IS_RCC_PLLP_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

/*! Macro to check the PLLQ value */
#define IS_RCC_PLLQ_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

/*! Macro to check the PLLR value */
#define IS_RCC_PLLR_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

/*! Macro to check the PLL input frequency range */
#define IS_RCC_PLL_INPUT_RANGE(range) (((range) == HAL_RCC_PLL_INPUT_RANGE_1_2)    \
                                       || ((range) == HAL_RCC_PLL_INPUT_RANGE_2_4)  \
                                       || ((range) == HAL_RCC_PLL_INPUT_RANGE_4_8)  \
                                       || ((range) == HAL_RCC_PLL_INPUT_RANGE_8_16))

/*! Macro to check the PLL VCO frequencyrange */
#define IS_RCC_PLL_VCO_RANGE(range) (((range) == HAL_RCC_PLL_VCO_RANGE_128_560)    \
                                     || ((range) == HAL_RCC_PLL_VCO_RANGE_150_420))

/*! Macro to check the PLL1 output selection */
#define IS_RCC_PLL1_OUTPUT(value) ((((value) & (HAL_RCC_PLL1_OUTPUT_ALL)) != 0x00u) \
                                   && (((value) & ~(HAL_RCC_PLL1_OUTPUT_ALL)) == 0x00u))

/*! Macro to check the PLL2 output selection */
#define IS_RCC_PLL2_OUTPUT(value) ((((value) & (HAL_RCC_PLL2_OUTPUT_ALL)) != 0x00u) \
                                   && (((value) & ~(HAL_RCC_PLL2_OUTPUT_ALL)) == 0x00u))

/*! Macro to check the USART1 kernel clock source */
#define IS_RCC_USART1_CLK(source)  (((source) == HAL_RCC_USART1_CLK_SRC_PCLK2)    \
                                    || ((source) == HAL_RCC_USART1_CLK_SRC_ICLK1) \
                                    || ((source) == HAL_RCC_USART1_CLK_SRC_PLL2Q) \
                                    || ((source) == HAL_RCC_USART1_CLK_SRC_HSE)   \
                                    || ((source) == HAL_RCC_USART1_CLK_SRC_HSI)   \
                                    || ((source) == HAL_RCC_USART1_CLK_SRC_LSE))

/*! Macro to check the USART2 kernel clock source */
#define IS_RCC_USART2_CLK(source)  (((source) == HAL_RCC_USART2_CLK_SRC_PCLK1)    \
                                    || ((source) == HAL_RCC_USART2_CLK_SRC_ICLK1) \
                                    || ((source) == HAL_RCC_USART2_CLK_SRC_PLL2Q) \
                                    || ((source) == HAL_RCC_USART2_CLK_SRC_HSE)   \
                                    || ((source) == HAL_RCC_USART2_CLK_SRC_HSI)   \
                                    || ((source) == HAL_RCC_USART2_CLK_SRC_LSE))

/*! Macro to check the USART3 kernel clock source */
#define IS_RCC_USART3_CLK(source)  (((source) == HAL_RCC_USART3_CLK_SRC_PCLK1)    \
                                    || ((source) == HAL_RCC_USART3_CLK_SRC_ICLK1) \
                                    || ((source) == HAL_RCC_USART3_CLK_SRC_PLL2Q) \
                                    || ((source) == HAL_RCC_USART3_CLK_SRC_HSE)   \
                                    || ((source) == HAL_RCC_USART3_CLK_SRC_HSI)   \
                                    || ((source) == HAL_RCC_USART3_CLK_SRC_LSE))

/*! Macro to check the UART4 kernel clock source */
#define IS_RCC_UART4_CLK(source)  (((source) == HAL_RCC_UART4_CLK_SRC_PCLK1)      \
                                   || ((source) == HAL_RCC_UART4_CLK_SRC_ICLK1)   \
                                   || ((source) == HAL_RCC_UART4_CLK_SRC_PLL2Q)   \
                                   || ((source) == HAL_RCC_UART4_CLK_SRC_HSE)     \
                                   || ((source) == HAL_RCC_UART4_CLK_SRC_HSI)     \
                                   || ((source) == HAL_RCC_UART4_CLK_SRC_LSE))

/*! Macro to check the UART5 kernel clock source */
#define IS_RCC_UART5_CLK(source)  (((source) == HAL_RCC_UART5_CLK_SRC_PCLK1)      \
                                   || ((source) == HAL_RCC_UART5_CLK_SRC_ICLK1)   \
                                   || ((source) == HAL_RCC_UART5_CLK_SRC_PLL2Q)   \
                                   || ((source) == HAL_RCC_UART5_CLK_SRC_HSE)    \
                                   || ((source) == HAL_RCC_UART5_CLK_SRC_HSI)    \
                                   || ((source) == HAL_RCC_UART5_CLK_SRC_LSE))

/*! Macro to check the UART6 kernel clock source */
#define IS_RCC_UART6_CLK(source)  (((source) == HAL_RCC_UART6_CLK_SRC_PCLK1)     \
                                   || ((source) == HAL_RCC_UART6_CLK_SRC_ICLK1)    \
                                   || ((source) == HAL_RCC_UART6_CLK_SRC_PLL2Q) \
                                   || ((source) == HAL_RCC_UART6_CLK_SRC_HSE)    \
                                   || ((source) == HAL_RCC_UART6_CLK_SRC_HSI)    \
                                   || ((source) == HAL_RCC_UART6_CLK_SRC_LSE))

/*! Macro to check the LPUART1 kernel clock source */
#define IS_RCC_LPUART1_CLK(source)  (((source) == HAL_RCC_LPUART1_CLK_SRC_PCLK3)     \
                                     || ((source) == HAL_RCC_LPUART1_CLK_SRC_ICLK1)    \
                                     || ((source) == HAL_RCC_LPUART1_CLK_SRC_PLL2Q) \
                                     || ((source) == HAL_RCC_LPUART1_CLK_SRC_HSE)    \
                                     || ((source) == HAL_RCC_LPUART1_CLK_SRC_HSI)    \
                                     || ((source) == HAL_RCC_LPUART1_CLK_SRC_LSE))

/*! Macro to check the DAC1 kernel clock source */
#define IS_RCC_DAC1_CLK(source)  (((source) == HAL_RCC_DAC1_CLK_SRC_TIM)       \
                                  || ((source) == HAL_RCC_DAC1_CLK_SRC_HRTIM)  \
                                  || ((source) == HAL_RCC_DAC1_CLK_SRC_ADC)    \
                                  || ((source) == HAL_RCC_DAC1_CLK_SRC_HSE)    \
                                  || ((source) == HAL_RCC_DAC1_CLK_SRC_HSI)    \
                                  || ((source) == HAL_RCC_DAC1_CLK_SRC_PLL1Q) \
                                  || ((source) == HAL_RCC_DAC1_CLK_SRC_PLL2Q))

/*! Macro to check the DAC1SH kernel clock source */
#define IS_RCC_DAC1SH_CLK(source)  (((source) == HAL_RCC_DAC1SH_CLK_SRC_LSE) \
                                    || ((source) == HAL_RCC_DAC1SH_CLK_SRC_LSI))

/*! Macro to check the DAC2 kernel clock source */
#define IS_RCC_DAC2_CLK(source)  (((source) == HAL_RCC_DAC2_CLK_SRC_TIM)       \
                                  || ((source) == HAL_RCC_DAC2_CLK_SRC_HRTIM)  \
                                  || ((source) == HAL_RCC_DAC2_CLK_SRC_ADC)    \
                                  || ((source) == HAL_RCC_DAC2_CLK_SRC_HSE)    \
                                  || ((source) == HAL_RCC_DAC2_CLK_SRC_HSI)    \
                                  || ((source) == HAL_RCC_DAC2_CLK_SRC_PLL1Q) \
                                  || ((source) == HAL_RCC_DAC2_CLK_SRC_PLL2Q))

/*! Macro to check the DAC2SH kernel clock source */
#define IS_RCC_DAC2SH_CLK(source)  (((source) == HAL_RCC_DAC2SH_CLK_SRC_LSE) \
                                    || ((source) == HAL_RCC_DAC2SH_CLK_SRC_LSI))

/*! Macro to check the DAC5 kernel clock source */
#define IS_RCC_DAC5_CLK(source)  (((source) == HAL_RCC_DAC5_CLK_SRC_TIM)       \
                                  || ((source) == HAL_RCC_DAC5_CLK_SRC_HRTIM)  \
                                  || ((source) == HAL_RCC_DAC5_CLK_SRC_ADC)    \
                                  || ((source) == HAL_RCC_DAC5_CLK_SRC_HSE)    \
                                  || ((source) == HAL_RCC_DAC5_CLK_SRC_HSI)    \
                                  || ((source) == HAL_RCC_DAC5_CLK_SRC_PLL1Q) \
                                  || ((source) == HAL_RCC_DAC5_CLK_SRC_PLL2Q))

/*! Macro to check the DAC6 kernel clock source */
#define IS_RCC_DAC6_CLK(source)  (((source) == HAL_RCC_DAC6_CLK_SRC_TIM)       \
                                  || ((source) == HAL_RCC_DAC6_CLK_SRC_HRTIM)  \
                                  || ((source) == HAL_RCC_DAC6_CLK_SRC_ADC)    \
                                  || ((source) == HAL_RCC_DAC6_CLK_SRC_HSE)    \
                                  || ((source) == HAL_RCC_DAC6_CLK_SRC_HSI)    \
                                  || ((source) == HAL_RCC_DAC6_CLK_SRC_PLL1Q) \
                                  || ((source) == HAL_RCC_DAC6_CLK_SRC_PLL2Q))

/*! Macro to check the DAC7 kernel clock source */
#define IS_RCC_DAC7_CLK(source)  (((source) == HAL_RCC_DAC7_CLK_SRC_TIM)       \
                                  || ((source) == HAL_RCC_DAC7_CLK_SRC_HRTIM)  \
                                  || ((source) == HAL_RCC_DAC7_CLK_SRC_ADC)    \
                                  || ((source) == HAL_RCC_DAC7_CLK_SRC_HSE)    \
                                  || ((source) == HAL_RCC_DAC7_CLK_SRC_HSI)    \
                                  || ((source) == HAL_RCC_DAC7_CLK_SRC_PLL1Q) \
                                  || ((source) == HAL_RCC_DAC7_CLK_SRC_PLL2Q))

/*! Macro to check the DAC8 kernel clock source */
#define IS_RCC_DAC8_CLK(source)  (((source) == HAL_RCC_DAC8_CLK_SRC_TIM)       \
                                  || ((source) == HAL_RCC_DAC8_CLK_SRC_HRTIM)  \
                                  || ((source) == HAL_RCC_DAC8_CLK_SRC_ADC)    \
                                  || ((source) == HAL_RCC_DAC8_CLK_SRC_HSE)    \
                                  || ((source) == HAL_RCC_DAC8_CLK_SRC_HSI)    \
                                  || ((source) == HAL_RCC_DAC8_CLK_SRC_PLL1Q) \
                                  || ((source) == HAL_RCC_DAC8_CLK_SRC_PLL2Q))

/*! Macro to check the DAC9 kernel clock source */
#define IS_RCC_DAC9_CLK(source)  (((source) == HAL_RCC_DAC9_CLK_SRC_TIM)       \
                                  || ((source) == HAL_RCC_DAC9_CLK_SRC_HRTIM)  \
                                  || ((source) == HAL_RCC_DAC9_CLK_SRC_ADC)    \
                                  || ((source) == HAL_RCC_DAC9_CLK_SRC_HSE)    \
                                  || ((source) == HAL_RCC_DAC9_CLK_SRC_HSI)    \
                                  || ((source) == HAL_RCC_DAC9_CLK_SRC_PLL1Q) \
                                  || ((source) == HAL_RCC_DAC9_CLK_SRC_PLL2Q))

/*! Macro to check the DAC10 kernel clock source */
#define IS_RCC_DAC10_CLK(source)  (((source) == HAL_RCC_DAC10_CLK_SRC_TIM)       \
                                   || ((source) == HAL_RCC_DAC10_CLK_SRC_HRTIM)  \
                                   || ((source) == HAL_RCC_DAC10_CLK_SRC_ADC)    \
                                   || ((source) == HAL_RCC_DAC10_CLK_SRC_HSE)    \
                                   || ((source) == HAL_RCC_DAC10_CLK_SRC_HSI)    \
                                   || ((source) == HAL_RCC_DAC10_CLK_SRC_PLL1Q) \
                                   || ((source) == HAL_RCC_DAC10_CLK_SRC_PLL2Q))

/*! Macro to check the SPI1 kernel clock source */
#define IS_RCC_SPI1_CLK(source)  (((source) == HAL_RCC_SPI1_CLK_SRC_PCLK2)       \
                                  || ((source) == HAL_RCC_SPI1_CLK_SRC_ICLK1)      \
                                  || ((source) == HAL_RCC_SPI1_CLK_SRC_PLL2P)   \
                                  || ((source) == HAL_RCC_SPI1_CLK_SRC_HSE)      \
                                  || ((source) == HAL_RCC_SPI1_CLK_SRC_HSI)      \
                                  || ((source) == HAL_RCC_SPI1_CLK_SRC_AUDIOCLK))

/*! Macro to check the SPI2 kernel clock source */
#define IS_RCC_SPI2_CLK(source)  (((source) == HAL_RCC_SPI2_CLK_SRC_PCLK1)       \
                                  || ((source) == HAL_RCC_SPI2_CLK_SRC_ICLK1)      \
                                  || ((source) == HAL_RCC_SPI2_CLK_SRC_PLL2P)   \
                                  || ((source) == HAL_RCC_SPI2_CLK_SRC_HSE)      \
                                  || ((source) == HAL_RCC_SPI2_CLK_SRC_HSI)      \
                                  || ((source) == HAL_RCC_SPI2_CLK_SRC_AUDIOCLK))

/*! Macro to check the SPI3 kernel clock source */
#define IS_RCC_SPI3_CLK(source)  (((source) == HAL_RCC_SPI3_CLK_SRC_PCLK1)     \
                                  || ((source) == HAL_RCC_SPI3_CLK_SRC_ICLK1)    \
                                  || ((source) == HAL_RCC_SPI3_CLK_SRC_PLL2P) \
                                  || ((source) == HAL_RCC_SPI3_CLK_SRC_HSE)    \
                                  || ((source) == HAL_RCC_SPI3_CLK_SRC_HSI))

/*! Macro to check the PLAY1 kernel clock source */
#define IS_RCC_PLAY1_CLK(source)  (((source) == HAL_RCC_PLAY1_CLK_SRC_LSE)       \
                                   || ((source) == HAL_RCC_PLAY1_CLK_SRC_LSI)    \
                                   || ((source) == HAL_RCC_PLAY1_CLK_SRC_PLL2P) \
                                   || ((source) == HAL_RCC_PLAY1_CLK_SRC_HSE)    \
                                   || ((source) == HAL_RCC_PLAY1_CLK_SRC_HSI)    \
                                   || ((source) == HAL_RCC_PLAY1_CLK_SRC_HSI48))

/*! Macro to check the PLAY1 kernel clock divider */
#define IS_RCC_PLAY1_CLK_DIVIDER(divider)  (((divider) == HAL_RCC_PLAY1_CLK_DIVIDER1)        \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER2)     \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER4)     \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER8)     \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER16)    \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER32)    \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER64)    \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER128)   \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER256)   \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER512)   \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER1024)  \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER2048)  \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER4096)  \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER8192)  \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER16384) \
                                            || ((divider) == HAL_RCC_PLAY1_CLK_DIVIDER32768))

/*! Macro to check the LPTIM1 kernel clock source */
#define IS_RCC_LPTIM1_CLK(source)  (((source) == HAL_RCC_LPTIM1_CLK_SRC_PCLK3)     \
                                    || ((source) == HAL_RCC_LPTIM1_CLK_SRC_PLL1Q) \
                                    || ((source) == HAL_RCC_LPTIM1_CLK_SRC_PLL2P) \
                                    || ((source) == HAL_RCC_LPTIM1_CLK_SRC_HSE)    \
                                    || ((source) == HAL_RCC_LPTIM1_CLK_SRC_HSI)    \
                                    || ((source) == HAL_RCC_LPTIM1_CLK_SRC_LSI)    \
                                    || ((source) == HAL_RCC_LPTIM1_CLK_SRC_LSE))

/*! Macro to check the XSPI1 kernel clock source */
#define IS_RCC_XSPI1_CLK(source)  (((source) == HAL_RCC_XSPI1_CLK_SRC_HCLK4)     \
                                   || ((source) == HAL_RCC_XSPI1_CLK_SRC_PLL1Q) \
                                   || ((source) == HAL_RCC_XSPI1_CLK_SRC_ICLK2)    \
                                   || ((source) == HAL_RCC_XSPI1_CLK_SRC_HSE)    \
                                   || ((source) == HAL_RCC_XSPI1_CLK_SRC_HSI))

/*! Macro to check the UCPD1 kernel clock source */
#define IS_RCC_UCPD1_CLK(source)  (((source) == HAL_RCC_UCPD1_CLK_SRC_HSI)       \
                                   || ((source) == HAL_RCC_UCPD1_CLK_SRC_HSE)    \
                                   || ((source) == HAL_RCC_UCPD1_CLK_SRC_HSI48)  \
                                   || ((source) == HAL_RCC_UCPD1_CLK_SRC_PLL2Q))

/*! Macro to check the USB kernel clock source */
#define IS_RCC_USB_CLK(source)  (((source) == HAL_RCC_USB_CLK_SRC_HSI48)     \
                                 || ((source) == HAL_RCC_USB_CLK_SRC_HSE)    \
                                 || ((source) == HAL_RCC_USB_CLK_SRC_PLL1Q) \
                                 || ((source) == HAL_RCC_USB_CLK_SRC_PLL2Q))

/*! Macro to check the I3C1 kernel clock source */
#define IS_RCC_I3C1_CLK(source)  (((source) == HAL_RCC_I3C1_CLK_SRC_PCLK1)   \
                                  || ((source) == HAL_RCC_I3C1_CLK_SRC_ICLK1)  \
                                  || ((source) == HAL_RCC_I3C1_CLK_SRC_HSI)  \
                                  || ((source) == HAL_RCC_I3C1_CLK_SRC_HSE))

/*! Macro to check the I2C1 kernel clock source */
#define IS_RCC_I2C1_CLK(source)  (((source) == HAL_RCC_I2C1_CLK_SRC_PCLK1)   \
                                  || ((source) == HAL_RCC_I2C1_CLK_SRC_ICLK1)  \
                                  || ((source) == HAL_RCC_I2C1_CLK_SRC_HSI)  \
                                  || ((source) == HAL_RCC_I2C1_CLK_SRC_HSE))

/*! Macro to check the I2C2 kernel clock source */
#define IS_RCC_I2C2_CLK(source)  (((source) == HAL_RCC_I2C2_CLK_SRC_PCLK1)  \
                                  || ((source) == HAL_RCC_I2C2_CLK_SRC_ICLK1) \
                                  || ((source) == HAL_RCC_I2C2_CLK_SRC_HSI) \
                                  || ((source) == HAL_RCC_I2C2_CLK_SRC_HSE))

/*! Macro to check the I2C3 kernel clock source */
#define IS_RCC_I2C3_CLK(source)  (((source) == HAL_RCC_I2C3_CLK_SRC_PCLK3)    \
                                  || ((source) == HAL_RCC_I2C3_CLK_SRC_ICLK1)   \
                                  || ((source) == HAL_RCC_I2C3_CLK_SRC_HSI)   \
                                  || ((source) == HAL_RCC_I2C3_CLK_SRC_HSE)   \
                                  || ((source) == HAL_RCC_I2C3_CLK_SRC_HSI48))

/*! Macro to check the I2C4 kernel clock source */
#define IS_RCC_I2C4_CLK(source)  (((source) == HAL_RCC_I2C4_CLK_SRC_PCLK3)    \
                                  || ((source) == HAL_RCC_I2C4_CLK_SRC_ICLK1)   \
                                  || ((source) == HAL_RCC_I2C4_CLK_SRC_HSI)   \
                                  || ((source) == HAL_RCC_I2C4_CLK_SRC_HSE)   \
                                  || ((source) == HAL_RCC_I2C4_CLK_SRC_HSI48))

/*! Macro to check the ADC kernel clock source */
#define IS_RCC_ADC_CLK(source)  (((source) == HAL_RCC_ADC_CLK_SRC_TIM)       \
                                 || ((source) == HAL_RCC_ADC_CLK_SRC_HRTIM)  \
                                 || ((source) == HAL_RCC_ADC_CLK_SRC_HSI)    \
                                 || ((source) == HAL_RCC_ADC_CLK_SRC_HSE)    \
                                 || ((source) == HAL_RCC_ADC_CLK_SRC_PLL1Q) \
                                 || ((source) == HAL_RCC_ADC_CLK_SRC_ICLK1)    \
                                 || ((source) == HAL_RCC_ADC_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_ADC_CLK_SRC_ICLK2))

/*! Macro to check the ADC kernel clock prescaler */
#define IS_RCC_ADC_PRESCALER(prescaler)  (((prescaler) == HAL_RCC_ADC_PRESCALER1)      \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER2)   \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER4)   \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER6)   \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER8)   \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER10)  \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER12)  \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER16)  \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER32)  \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER64)  \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER128) \
                                          || ((prescaler) == HAL_RCC_ADC_PRESCALER256))

/*! Macro to check the FDCAN kernel clock source */
#define IS_RCC_FDCAN_CLK(source)  (((source) == HAL_RCC_FDCAN_CLK_SRC_HSE)       \
                                   || ((source) == HAL_RCC_FDCAN_CLK_SRC_PLL1Q) \
                                   || ((source) == HAL_RCC_FDCAN_CLK_SRC_PLL2Q))

/*! Macro to check the POSENC1 kernel clock source */
#define IS_RCC_POSENC1_CLK(source)  (((source) == HAL_RCC_POSENC1_CLK_SRC_PLL1P)    \
                                     || ((source) == HAL_RCC_POSENC1_CLK_SRC_PLL1Q) \
                                     || ((source) == HAL_RCC_POSENC1_CLK_SRC_ICLK1)    \
                                     || ((source) == HAL_RCC_POSENC1_CLK_SRC_PLL2P) \
                                     || ((source) == HAL_RCC_POSENC1_CLK_SRC_PLL2Q) \
                                     || ((source) == HAL_RCC_POSENC1_CLK_SRC_ICLK2))

/*! Macro to check the POSENC2 kernel clock source */
#define IS_RCC_POSENC2_CLK(source)  (((source) == HAL_RCC_POSENC2_CLK_SRC_PLL1P)    \
                                     || ((source) == HAL_RCC_POSENC2_CLK_SRC_PLL1Q) \
                                     || ((source) == HAL_RCC_POSENC2_CLK_SRC_ICLK1)    \
                                     || ((source) == HAL_RCC_POSENC2_CLK_SRC_PLL2P) \
                                     || ((source) == HAL_RCC_POSENC2_CLK_SRC_PLL2Q) \
                                     || ((source) == HAL_RCC_POSENC2_CLK_SRC_ICLK2) )


#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/*! Macro to check the RCC security attribute */
#define IS_RCC_SEC_ATTR(attribute) ((attribute == HAL_RCC_SEC  )    \
                                    || (attribute == HAL_RCC_NSEC))
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/*! Macro to check the RCC privilege attribute */
#define IS_RCC_PRIV_ATTR(attribute) ((attribute == HAL_RCC_PRIV  )    \
                                     || (attribute == HAL_RCC_NPRIV))

/*! Macro to check the RCC security items */
#define IS_RCC_SEC_ITEM(item) ((((item) & (HAL_RCC_SEC_ITEM_ALL)) != 0x00U)       \
                               && (((item) & ~(HAL_RCC_SEC_ITEM_ALL)) == 0x00U))

/*! Macro to check the RCC privilege items */
#define IS_RCC_PRIV_ITEM(item) ((((item) & (HAL_RCC_PRIV_ITEM_ALL)) != 0x00U)      \
                                && (((item) & ~(HAL_RCC_PRIV_ITEM_ALL)) == 0x00U))

/*! Macro to check if only one RCC security item is set */
#define IS_RCC_SEC_SINGLE_ITEM(item)    (((item) == HAL_RCC_SEC_ITEM_HSI)          \
                                         || ((item) == HAL_RCC_SEC_ITEM_HSE)        \
                                         || ((item) == HAL_RCC_SEC_ITEM_LSI)        \
                                         || ((item) == HAL_RCC_SEC_ITEM_LSE)        \
                                         || ((item) == HAL_RCC_SEC_ITEM_SYSCLK)     \
                                         || ((item) == HAL_RCC_SEC_ITEM_PRESCALERS) \
                                         || ((item) == HAL_RCC_SEC_ITEM_PLL1)       \
                                         || ((item) == HAL_RCC_SEC_ITEM_PLL2)       \
                                         || ((item) == HAL_RCC_SEC_ITEM_HSI48)      \
                                         || ((item) == HAL_RCC_SEC_ITEM_RESET_FLAGS))

/*! Macro to check if only one RCC privilege item is set */
#define IS_RCC_PRIV_SINGLE_ITEM(item)   (((item) == HAL_RCC_PRIV_ITEM_SPRIV)        \
                                         || ((item) == HAL_RCC_PRIV_ITEM_NSPRIV))

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC Private Functions
  * @{
  */
static hal_status_t RCC_WaitForTimeout(const rcc_cb_timeout_t p_timeout_cb, uint32_t timeout, uint32_t status);
static uint32_t     RCC_HSI_GetClockFreq(void);
static uint32_t     RCC_ICLK_GetClockFreq(hal_rcc_iclk_t  iclkx);
static uint32_t     RCC_ADC_GetKernelClkFreq(void);

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup RCC_Exported_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1_0
  * @{
  */

/**
  * @brief   Reset the RCC clock configuration to the default reset state.
  * @note    SystemCoreClock and HAL timebase are updated in this function.
  * @note    Resources under backup domain reset if USE_HAL_RCC_RESET_RTC_DOMAIN set to 1U
  * @note    Peripherals clock enable and source selection reset if USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT set to 1U
  * @warning Access to RTC domain must be enabled to disable RTC domain source clock.
  */
void HAL_RCC_Reset(void)
{
  uint32_t tickstart;

  /* Disable RCC interrupts */
  LL_RCC_WRITE_REG(IER, RCC_IER_Rst);

#if defined(USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT) && (USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT == 1U)
  /* Enable bus clocks */
  LL_RCC_CLEAR_BIT(CFGR2, (RCC_CFGR2_AHB1DIS | RCC_CFGR2_AHB2DIS | RCC_CFGR2_AHB3DIS | RCC_CFGR2_AHB4DIS |
                           RCC_CFGR2_APB1DIS | RCC_CFGR2_APB2DIS | RCC_CFGR2_APB3DIS));

  /* Disable peripherals bus clocks */
  LL_RCC_WRITE_REG(AHB1ENR, RCC_AHB1ENR_Rst);
  LL_RCC_WRITE_REG(AHB2ENR, RCC_AHB2ENR_Rst);
  LL_RCC_WRITE_REG(AHB3ENR, RCC_AHB3ENR_Rst);
  LL_RCC_WRITE_REG(AHB4ENR, RCC_AHB4ENR_Rst);
  LL_RCC_WRITE_REG(APB1LENR, RCC_APB1LENR_Rst);
  LL_RCC_WRITE_REG(APB1HENR, RCC_APB1HENR_Rst);
  LL_RCC_WRITE_REG(APB2ENR, RCC_APB2ENR_Rst);
  LL_RCC_WRITE_REG(APB3ENR, RCC_APB3ENR_Rst);

  LL_RCC_WRITE_REG(AHB1LPENR, RCC_AHB1LPENR_Rst);
  LL_RCC_WRITE_REG(AHB2LPENR, RCC_AHB2LPENR_Rst);
  LL_RCC_WRITE_REG(AHB3LPENR, RCC_AHB3LPENR_Rst);
  LL_RCC_WRITE_REG(AHB4LPENR, RCC_AHB4LPENR_Rst);
  LL_RCC_WRITE_REG(APB1LLPENR, RCC_APB1LLPENR_Rst);
  LL_RCC_WRITE_REG(APB1HLPENR, RCC_APB1HLPENR_Rst);
  LL_RCC_WRITE_REG(APB2LPENR, RCC_APB2LPENR_Rst);
  LL_RCC_WRITE_REG(APB3LPENR, RCC_APB3LPENR_Rst);

  /* Reset peripheral clock source selection */
  LL_RCC_WRITE_REG(CCIPR1, RCC_CCIPR1_Rst);
  LL_RCC_WRITE_REG(CCIPR2, RCC_CCIPR2_Rst);
  LL_RCC_WRITE_REG(CCIPR3, RCC_CCIPR3_Rst);
  LL_RCC_WRITE_REG(CCIPR4, RCC_CCIPR4_Rst);
  LL_RCC_WRITE_REG(CCIPR5, RCC_CCIPR5_Rst);

#endif /* USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT */

  /* Reset System clock */
  LL_RCC_HSI_SetDivider(LL_RCC_HSI_DIV_1);
  LL_RCC_HSI_Enable();

  (void)RCC_WaitForTimeout(LL_RCC_HSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U);

  tickstart = HAL_GetTick();

  /* HSI is selected as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

  /* Wait till clock switch is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      break;
    }
  }

  /* Reset all bus dividers */
  LL_RCC_ConfigBusClock((uint32_t)LL_RCC_HCLK_PRESCALER_1 | (uint32_t)LL_RCC_APB1_PRESCALER_1 |
                        (uint32_t)LL_RCC_APB2_PRESCALER_1 |
                        (uint32_t)LL_RCC_APB3_PRESCALER_1);

  SystemCoreClock = HSI_VALUE;

  LL_RCC_SetSystickClockSource(LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8);

  /* Adapt Systick interrupt period */
  (void)HAL_InitTick(HAL_TICK_FREQ_DEFAULT, uwTickPrio);

#if defined(USE_HAL_RCC_RESET_RTC_DOMAIN) && (USE_HAL_RCC_RESET_RTC_DOMAIN == 1U)
  /* Reset backup domain */
  LL_RCC_ForceRTCDomainReset();
  LL_RCC_ReleaseRTCDomainReset();
#endif /* USE_HAL_RCC_RESET_RTC_DOMAIN */

  /* Reset all remaining oscillators not in backup domain (excepted the one used for System clock) */
  uint32_t read_value = LL_RCC_READ_REG(CR);
  LL_RCC_WRITE_REG(CR, (RCC_CR_Rst | (read_value & (RCC_CR_HSEBYP | RCC_CR_HSEEXT))));
  LL_RCC_WRITE_REG(CR, RCC_CR_Rst); /* HSE EXT and BYP disabled only when HSE has been disabled */

  LL_RCC_LSI_Disable();

  (void)RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U);
#if defined (PLL2)
  (void)RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U);
#endif /* PLL2 */

  /* Reset MCO, RTC prescaler and wake up system clock */
#if defined(USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT) && (USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT == 1U)
  LL_RCC_WRITE_REG(CFGR1, RCC_CFGR1_Rst);
#else
  read_value = LL_RCC_READ_REG(CFGR1);
  LL_RCC_WRITE_REG(CFGR1, (read_value & RCC_CFGR1_RTCPRE) | (RCC_CFGR1_Rst & ~(RCC_CFGR1_RTCPRE)));
#endif /* USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT */

  /* Reset PLLs */
  LL_RCC_WRITE_REG(PLL1CFGR, RCC_PLL1CFGR_Rst);
  LL_RCC_WRITE_REG(PLL1DIVR, RCC_PLL1DIVR_Rst);
  LL_RCC_WRITE_REG(PLL1FRACR, RCC_PLL1FRACR_Rst);
#if defined (PLL2)
  LL_RCC_WRITE_REG(PLL2CFGR, RCC_PLL2CFGR_Rst);
  LL_RCC_WRITE_REG(PLL2DIVR, RCC_PLL2DIVR_Rst);
  LL_RCC_WRITE_REG(PLL2FRACR, RCC_PLL2FRACR_Rst);
#endif /* PLL2 */

  /* Clear RCC flags */
  LL_RCC_ClearFlag(LL_RCC_IT_LSIRDY | LL_RCC_IT_LSERDY | LL_RCC_IT_HSIRDY | LL_RCC_IT_HSERDY | LL_RCC_IT_HSI48RDY \
                   | LL_RCC_IT_PLL1RDY | LL_RCC_IT_PLL2RDY | LL_RCC_IT_LSECSS | LL_RCC_IT_HSECSS);

  LL_RCC_ClearResetFlags();
}

/**
  * @brief  Reset the RCC clock configuration to the default system clock (HSI at 64 Mhz).
  * @note   SystemCoreClock and Systick are updated in this function.
  * @retval HAL_OK    System clock switched to HSI (64Mhz)
  * @retval HAL_ERROR Timeout issue to enable the HSI oscillator\n
  *                   Switch to HSI as source clock failed\n
  *                   Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_ResetSystemClock(void)
{
  uint32_t tickstart;

  LL_RCC_HSI_SetDivider(LL_RCC_HSI_DIV_1);
  LL_RCC_HSI_Enable();
  if (RCC_WaitForTimeout(LL_RCC_HSI_IsDividerReady, RCC_HSI_TIMEOUT_VALUE, 1U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (RCC_WaitForTimeout(LL_RCC_HSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

  /* Wait till clock switch is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
      {
        return HAL_ERROR;
      }
    }
  }
  LL_RCC_SetAHBPrescaler(LL_RCC_HCLK_PRESCALER_1);
  SystemCoreClock = HSI_VALUE;

  /* Adapt Systick interrupt period */
  return (HAL_InitTick(HAL_TICK_FREQ_DEFAULT, HAL_TICK_INT_LOWEST_PRIORITY));
}
/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_1
  * @{
  */

#if defined(HSE_VALUE)
/**
  * @brief  Enable the HSE oscillator in the selected mode.
  * @param  mode        HSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_HSE_ON
  *         @arg @ref HAL_RCC_HSE_BYPASS
  *         @arg @ref HAL_RCC_HSE_BYPASS_DIGITAL
  * @note   Transitions HSE Bypass to HSE On and HSE On to HSE Bypass are not supported by this function.
  * @retval HAL_OK      HSE oscillator has been successfully activated and configured
  * @retval HAL_ERROR   Timeout linked to HSE ready flag not set
  */
hal_status_t HAL_RCC_HSE_Enable(hal_rcc_hse_t mode)
{
  ASSERT_DBG_PARAM(IS_RCC_HSE_MODE_ENABLE(mode));

  /* Set the new HSE configuration */
  if (((uint32_t)mode & RCC_CR_HSEBYP) == RCC_CR_HSEBYP)
  {
    LL_RCC_HSE_ConfigBypass((uint32_t)mode & RCC_CR_HSEEXT);
  }

  LL_RCC_HSE_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSE_IsReady, RCC_HSE_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Enable the HSE oscillator in interrupt mode in the selected mode.
  * @param  mode        HSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_HSE_ON
  *         @arg @ref HAL_RCC_HSE_BYPASS
  *         @arg @ref HAL_RCC_HSE_BYPASS_DIGITAL
  * @note   Transitions HSE Bypass to HSE On and HSE On to HSE Bypass are not supported by this function.
  * @note   This function only enables the HSE and the corresponding ready interrupt.
  *         When HSE is ready, the callback HAL_RCC_HSE_ReadyCallback() is invoked.
  * @retval HAL_OK      HSE oscillator has been started
  */
hal_status_t HAL_RCC_HSE_Enable_IT(hal_rcc_hse_t mode)
{
  ASSERT_DBG_PARAM(IS_RCC_HSE_MODE_ENABLE(mode));

  /* Set the new HSE configuration */
  if (((uint32_t)mode & RCC_CR_HSEBYP) == RCC_CR_HSEBYP)
  {
    LL_RCC_HSE_ConfigBypass((uint32_t)mode & RCC_CR_HSEEXT);
  }

  LL_RCC_EnableIT(LL_RCC_IT_HSERDY);
  LL_RCC_HSE_Enable();

  return HAL_OK;
}

/**
  * @brief  Disable the HSE oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral using it.
  * @retval HAL_OK      HSE oscillator has been successfully deactivated
  * @retval HAL_ERROR   HSE is used as system clock or source clock of the main PLL used as system clock\n
  *                     Timeout linked to HSE ready flag not reset
  */
hal_status_t HAL_RCC_HSE_Disable(void)
{
  hal_status_t status;
  uint32_t pll_config;
  uint32_t sysclk_source;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_config    = LL_RCC_PLL1_GetSource();

  /* When the HSE is used as system clock or clock source for PLL in these cases it is not allowed to be disabled */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_config == LL_RCC_PLL1SOURCE_HSE)))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_HSE_Disable();
    LL_RCC_HSE_DisableBypass();
    LL_RCC_HSE_SetExternalClockType(LL_RCC_HSE_ANALOG_TYPE);
    LL_RCC_DisableIT(LL_RCC_IT_HSERDY);
    status = RCC_WaitForTimeout(LL_RCC_HSE_IsReady, RCC_HSE_TIMEOUT_VALUE, 0U);
  }

  return status;
}

/**
  * @brief  Check if HSE is enabled.
  * @retval hal_rcc_osc_enable_status_t HSE enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_HSE_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_HSE_IsEnabled();
}

/**
  * @brief  Check if HSE is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       HSE is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   HSE can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_HSE_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_HSE_IsReady();
}

/**
  * @brief  RCC HSE ready interrupt callback.
  */
__WEAK void HAL_RCC_HSE_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_HSE_ReadyCallback must be implemented in the user file
   */
}

#endif /* HSE_VALUE */

#if defined(LSE_VALUE)
/**
  * @brief  Enable the LSE oscillator in the selected mode with a oscillator drive capability.
  * @param  mode        LSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_LSE_ON
  *         @arg @ref HAL_RCC_LSE_BYPASS
  * @param  drive         LSE drive capability
  * @warning Access to backup domain must be enabled.
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not supported by this function.
  * @note   Drive capability is relevant only in Xtal mode (means not in bypass mode)
  * @note   Transitions between drive capability are not supported.
  * @retval HAL_OK      LSE oscillator enable sequence has been started
  * @retval HAL_ERROR   Backup domain is not enabled\n
  *                     Timeout linked to LSE ready flag not set\n
  */
hal_status_t HAL_RCC_LSE_Enable(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive)
{

  ASSERT_DBG_PARAM(IS_RCC_LSE_MODE_ENABLE(mode));
  ASSERT_DBG_PARAM(IS_RCC_LSE_DRIVE(drive));

  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  /* Set the new LSE configuration ---------------------------------------*/
  if (mode  == HAL_RCC_LSE_BYPASS)
  {
    LL_RCC_LSE_EnableBypass();
  }
  else
  {
    LL_RCC_LSE_SetDriveCapability((uint32_t)drive);
  }

  LL_RCC_LSE_Enable();

  return RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Enable the LSE oscillator in interrupt mode, in the selected mode with a oscillator drive capability.
  * @param  mode        LSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_LSE_ON
  *         @arg @ref HAL_RCC_LSE_BYPASS
  * @param  drive         LSE drive capability
  * @warning Access to backup domain must be enabled.
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not supported by this function.
  * @note   Drive capability is relevant only in Xtal mode (means not in bypass mode)
  * @note   Transitions between drive capability are not supported.
  * @note   This function only enables the LSE and the corresponding ready interrupt.
  *         When LSE is ready, the callback HAL_RCC_LSE_ReadyCallback() is invoked.
  * @retval HAL_OK      LSE oscillator has been successfully configured
  * @retval HAL_ERROR   Backup domain is not enabled\n
  *                     Timeout linked to LSE ready flag not set\n
  */
hal_status_t HAL_RCC_LSE_Enable_IT(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive)
{

  ASSERT_DBG_PARAM(IS_RCC_LSE_MODE_ENABLE(mode));
  ASSERT_DBG_PARAM(IS_RCC_LSE_DRIVE(drive));

  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  /* Set the new LSE configuration ---------------------------------------*/
  if (mode  == HAL_RCC_LSE_BYPASS)
  {
    LL_RCC_LSE_EnableBypass();
  }
  else
  {
    LL_RCC_LSE_SetDriveCapability((uint32_t)drive);
  }
  LL_RCC_EnableIT(LL_RCC_IT_LSERDY);
  LL_RCC_LSE_Enable();

  return HAL_OK;
}

/**
  * @brief  Disable the LSE oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral using it.
  * @warning Access to backup domain must be enabled.
  * @retval HAL_OK      LSE oscillator has been configured successfully
  * @retval HAL_ERROR   Backup domain is not enabled\n
  *                     Timeout linked to LSE ready flag not reset\n
  */
hal_status_t HAL_RCC_LSE_Disable(void)
{
  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_LSE_Disable();
  LL_RCC_LSE_DisableBypass();
  LL_RCC_DisableIT(LL_RCC_IT_LSERDY);
  if (RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 0U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Set LSE drive to medium-low (default value) */
  LL_RCC_LSE_SetDriveCapability(HAL_RCC_LSE_DRIVE_MEDIUMLOW);

  return HAL_OK;
}

/**
  * @brief  Check if LSE is enabled.
  * @retval hal_rcc_osc_enable_status_t LSE enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_LSE_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_LSE_IsEnabled();
}

/**
  * @brief  Check if LSE is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       LSE is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   LSE can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_LSE_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_LSE_IsReady();
}

/**
  * @brief  RCC LSE ready interrupt callback.
  */
__WEAK void HAL_RCC_LSE_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_LSE_ReadyCallback must be implemented in the user file
   */
}
#endif /* LSE_VALUE */

/**
  * @brief  Enable the HSI oscillator.
  * @param  divider  Divider value
  * @retval HAL_OK      HSI oscillator is already well configured or has been successfully activated
  * @retval HAL_ERROR   HSI divider change request while HSI is used as source of any active PLL\n
  *                     Timeout linked to HSI Divider ready flag not set\n
  *                     Timeout linked to HSI ready flag not set
  */
hal_status_t HAL_RCC_HSI_Enable(hal_rcc_hsi_div_t divider)
{
  uint32_t current_divider;
  uint32_t hsi_is_ready;
  uint32_t divider_change;
  uint32_t pll1_source;
  uint32_t pll1_ready;
#if defined(PLL2)
  uint32_t pll2_source;
  uint32_t pll2_ready;
#endif /* PLL2 */

  ASSERT_DBG_PARAM(IS_RCC_HSI_DIV(divider));

  current_divider = LL_RCC_HSI_GetDivider();
  hsi_is_ready = LL_RCC_HSI_IsReady();
  divider_change = ((current_divider != (uint32_t)divider) ? 1UL : 0UL);

  /* Check if HSI already has the correct configuration */
  if ((hsi_is_ready != 0U) && (divider_change == 0U))
  {
    return HAL_OK;
  }

  pll1_source = LL_RCC_PLL1_GetSource();
  pll1_ready = LL_RCC_PLL1_IsReady();
#if defined(PLL2)
  pll2_source = LL_RCC_PLL2_GetSource();
  pll2_ready = LL_RCC_PLL2_IsReady();
#endif /* PLL2 */

  /* Check if HSI divider change is requested while HSI is used as source of any active PLL */
  if ((divider_change != 0U)
      && (((pll1_source == LL_RCC_PLL1SOURCE_HSI) && (pll1_ready == 1U))
#if defined(PLL2)
          || ((pll2_source == LL_RCC_PLL2SOURCE_HSI) && (pll2_ready == 1U))
#endif /* PLL2 */
         ))
  {
    return HAL_ERROR;
  }

  if (divider_change != 0U)
  {
    LL_RCC_HSI_SetDivider((uint32_t)divider);
  }

  if (hsi_is_ready == 0U)
  {
    LL_RCC_HSI_Enable();
  }

  if (RCC_WaitForTimeout(LL_RCC_HSI_IsDividerReady, RCC_HSI_TIMEOUT_VALUE, 1U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return RCC_WaitForTimeout(LL_RCC_HSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Enable the HSI oscillator in interrupt mode.
  * @param  divider  Divider value
  * @note   This function only configure and enables the HSI and the corresponding ready interrupt.
  *         When HSI is ready, the callback HAL_RCC_HSI_ReadyCallback() is invoked.
  * @retval HAL_OK      HSI oscillator enable sequence has been started
  * @retval HAL_ERROR   HSI divider change request while HSI is used as source of any active PLL\n
  */
hal_status_t HAL_RCC_HSI_Enable_IT(hal_rcc_hsi_div_t divider)
{
  uint32_t current_divider;
  uint32_t hsi_is_ready;
  uint32_t divider_change;
  uint32_t pll1_source;
  uint32_t pll1_ready;
#if defined(PLL2)
  uint32_t pll2_source;
  uint32_t pll2_ready;
#endif /* PLL2 */

  ASSERT_DBG_PARAM(IS_RCC_HSI_DIV(divider));

  current_divider = LL_RCC_HSI_GetDivider();
  hsi_is_ready = LL_RCC_HSI_IsReady();
  divider_change = ((current_divider != (uint32_t)divider) ? 1UL : 0UL);

  LL_RCC_EnableIT(LL_RCC_IT_HSIRDY);

  /* Check if HSI already has the correct configuration */
  if ((hsi_is_ready != 0U) && (divider_change == 0U))
  {
    return HAL_OK;
  }

  pll1_source = LL_RCC_PLL1_GetSource();
  pll1_ready = LL_RCC_PLL1_IsReady();
#if defined(PLL2)
  pll2_source = LL_RCC_PLL2_GetSource();
  pll2_ready = LL_RCC_PLL2_IsReady();
#endif /* PLL2 */

  /* Check if HSI divider change is requested while HSI is used as source of any active PLL */
  if ((divider_change != 0U)
      && (((pll1_source == LL_RCC_PLL1SOURCE_HSI) && (pll1_ready == 1U))
#if defined(PLL2)
          || ((pll2_source == LL_RCC_PLL2SOURCE_HSI) && (pll2_ready == 1U))
#endif /* PLL2 */
         ))
  {
    return HAL_ERROR;
  }

  if (divider_change != 0U)
  {
    LL_RCC_HSI_SetDivider((uint32_t)divider);
  }

  if (hsi_is_ready == 0U)
  {
    LL_RCC_HSI_Enable();
  }

  return HAL_OK;
}

/**
  * @brief  Disable the HSI oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral using it.
  * @retval HAL_OK      HSI oscillator has been successfully deactivated
  * @retval HAL_ERROR   HSI is used as system clock or source clock of the main PLL used as system clock\n
  *                     Timeout linked to HSI ready flag not reset
  */
hal_status_t HAL_RCC_HSI_Disable(void)
{
  hal_status_t status;
  uint32_t pll_config;
  uint32_t sysclk_source;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_config    = LL_RCC_PLL1_GetSource();

  /* Check that HSI is not used as system clock or as PLL source when PLL is selected as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_config == LL_RCC_PLL1SOURCE_HSI)))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_HSI_Disable();
    LL_RCC_DisableIT(LL_RCC_IT_HSIRDY);
    status = RCC_WaitForTimeout(LL_RCC_HSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 0U);
  }

  return status;
}

/**
  * @brief  Check if HSI is enabled.
  * @retval hal_rcc_osc_enable_status_t HSI enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_HSI_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_HSI_IsEnabled();
}

/**
  * @brief  Check if HSI is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       HSI is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   HSI can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_HSI_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_HSI_IsReady();
}

/**
  * @brief  RCC HSI ready interrupt callback.
  */
__WEAK void HAL_RCC_HSI_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_HSI_ReadyCallback must be implemented in the user file
   */
}

/**
  * @brief  Enable the HSI oscillator in Stop mode.
  * @retval HAL_OK HSI oscillator is forced ON even in Stop mode.
  */
hal_status_t HAL_RCC_HSI_EnableInStopMode(void)
{
  LL_RCC_HSI_EnableInStopMode();
  return HAL_OK;
}

/**
  * @brief  Disable the HSI oscillator in Stop mode.
  * @retval HAL_OK      HSI oscillator is disable in Stop mode.
  */
hal_status_t HAL_RCC_HSI_DisableInStopMode(void)
{
  LL_RCC_HSI_DisableInStopMode();
  return HAL_OK;
}

/**
  * @brief  Check if HSI in stop mode is enabled.
  * @retval status based on @ref hal_rcc_osc_stop_mode_status_t
  * @retval HAL_RCC_OSC_DISABLED_IN_STOP_MODE   HSI is disabled in stop mode
  * @retval HAL_RCC_OSC_ENABLED_IN_STOP_MODE    HSI is enabled in stop mode
  */
hal_rcc_osc_stop_mode_status_t HAL_RCC_HSI_IsEnabledInStopMode(void)
{
  return (hal_rcc_osc_stop_mode_status_t)LL_RCC_HSI_IsEnabledInStopMode();
}

/**
  * @brief  Configure the HSI oscillator trimming value.
  * @param  value  Trimming value (default is @ref HAL_RCC_HSICALIBRATION_DEFAULT).
  *                This parameter must be a number between 0 and 127.
  * @note   The trimming is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @note   The trimming value might be updated while the HSI oscillator is enabled.
  */
void HAL_RCC_HSI_SetTrimming(uint32_t value)
{
  ASSERT_DBG_PARAM(IS_RCC_HSI_CALIBRATION_VALUE(value));

  LL_RCC_HSI_SetCalibTrimming(value);
}

/**
  * @brief  Get the HSI oscillator trimming value.
  * @retval Trimming value between 0 and 127.
  */
uint32_t HAL_RCC_HSI_GetTrimming(void)
{
  return LL_RCC_HSI_GetCalibTrimming();
}

/**
  * @brief  Get the HSI oscillator calibration value.
  * @retval Calibration value between 0 and 4095.
  */
uint32_t  HAL_RCC_HSI_GetCalibration(void)
{
  return LL_RCC_HSI_GetCalibration();
}

#if defined(HSI48)
/**
  * @brief  Enable the HSI48 oscillator.
  * @retval HAL_OK      HSI48 oscillator has been successfully activated
  * @retval HAL_ERROR   Timeout linked to HSI48 ready flag not set
  */
hal_status_t HAL_RCC_HSI48_Enable(void)
{
  LL_RCC_HSI48_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSI48_IsReady, RCC_HSI48_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Enable the HSI48 oscillator in interrupt mode.
  * @note   This function only enables the HSI48 and the corresponding ready interrupt.
  *         When HSI48 is ready, the callback HAL_RCC_HSI48_ReadyCallback() is invoked.
  * @retval HAL_OK      HSI48 oscillator enable sequence has been started
  */
hal_status_t HAL_RCC_HSI48_Enable_IT(void)
{
  LL_RCC_EnableIT(LL_RCC_IT_HSI48RDY);
  LL_RCC_HSI48_Enable();

  return HAL_OK;
}

/**
  * @brief  Disable the HSI48 oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral using it.
  * @retval HAL_OK      HSI48 oscillator has been successfully deactivated
  * @retval HAL_ERROR   Timeout linked to HSI48 ready flag not reset
  */
hal_status_t HAL_RCC_HSI48_Disable(void)
{
  LL_RCC_HSI48_Disable();
  LL_RCC_DisableIT(LL_RCC_IT_HSI48RDY);

  return RCC_WaitForTimeout(LL_RCC_HSI48_IsReady, RCC_HSI48_TIMEOUT_VALUE, 0U);
}

/**
  * @brief  Check if HSI48 is enabled.
  * @retval hal_rcc_osc_enable_status_t HSI48 enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_HSI48_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_HSI48_IsEnabled();
}

/**
  * @brief  Check if HSI48 is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       HSI48 is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   HSI48 can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_HSI48_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_HSI48_IsReady();
}

/**
  * @brief  RCC HSI48 ready interrupt callback.
  */
__WEAK void HAL_RCC_HSI48_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_HSI48_ReadyCallback must be implemented in the user file
   */
}

/**
  * @brief  Get the HSI48 oscillator calibration value.
  * @retval Calibration Number between 0 and 1023.
  */
uint32_t  HAL_RCC_HSI48_GetCalibration(void)
{
  return LL_RCC_HSI48_GetCalibration();
}
#endif /* HSI48 */

/**
  * @brief  Enable the Internal Low Speed oscillator (LSI).
  * @retval HAL_OK      LSI oscillator has been configured successfully
  * @retval HAL_ERROR   Timeout linked to LSI ready flag not set\n
  */
hal_status_t HAL_RCC_LSI_Enable(void)
{
  LL_RCC_LSI_Enable();

  return RCC_WaitForTimeout(LL_RCC_LSI_IsReady, RCC_LSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Enable the Internal Low Speed oscillator (LSI) in interrupt mode.
  * @note   This function only enables the LSI and the corresponding ready interrupt.
  *         When LSI is ready, the callback HAL_RCC_LSI_ReadyCallback() is invoked.
  * @retval HAL_OK      LSI oscillator enable sequence has been started
  */
hal_status_t HAL_RCC_LSI_Enable_IT(void)
{
  LL_RCC_EnableIT(LL_RCC_IT_LSIRDY);
  LL_RCC_LSI_Enable();

  return HAL_OK;
}

/**
  * @brief  Disable the LSI oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral using it.
  * @retval HAL_OK      LSI oscillator has been successfully deactivated
  * @retval HAL_ERROR   Timeout linked to LSI ready flag not reset\n
  */
hal_status_t HAL_RCC_LSI_Disable(void)
{
  LL_RCC_LSI_Disable();
  LL_RCC_DisableIT(LL_RCC_IT_LSIRDY);

  return RCC_WaitForTimeout(LL_RCC_LSI_IsReady, RCC_LSI_TIMEOUT_VALUE, 0U);
}

/**
  * @brief  Check if LSI is enabled.
  * @retval hal_rcc_osc_enable_status_t LSI enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_LSI_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_LSI_IsEnabled();
}

/**
  * @brief  Check if LSI is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       LSI is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   LSI can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_LSI_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_LSI_IsReady();
}

/**
  * @brief  RCC LSI ready interrupt callback.
  */
__WEAK void HAL_RCC_LSI_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_LSI_ReadyCallback must be implemented in the user file
   */
}

/**
  * @brief  Handle the RCC general interrupt request.
  * @note   This API handles the ready interrupts generated by RCC Enable_IT services.
  * @warning This API must be called under the RCC_IRQHandler() and/or RCC_S_IRQHandler().
  */
void HAL_RCC_IRQHandler(void)
{
  uint32_t it_flags_sources;

  /* Get current IT flags values */
  it_flags_sources = LL_RCC_READ_REG(IFR);
  it_flags_sources &= LL_RCC_READ_REG(IER);

#if defined(HSE_VALUE)
  if ((it_flags_sources & LL_RCC_IT_HSERDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_HSERDY);
    HAL_RCC_HSE_ReadyCallback();
  }
#endif /* HSE_VALUE */

#if defined(LSE_VALUE)
  if ((it_flags_sources & LL_RCC_IT_LSERDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_LSERDY);
    HAL_RCC_LSE_ReadyCallback();
  }
  if ((it_flags_sources & LL_RCC_IT_LSECSS) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_LSECSS);
    HAL_RCC_LSE_CSSCallback();
  }
#endif /* LSE_VALUE */

  if ((it_flags_sources & LL_RCC_IT_HSIRDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_HSIRDY);
    HAL_RCC_HSI_ReadyCallback();
  }

#if defined(HSI48)
  if ((it_flags_sources & LL_RCC_IT_HSI48RDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_HSI48RDY);
    HAL_RCC_HSI48_ReadyCallback();
  }
#endif /* HSI48 */

  if ((it_flags_sources & LL_RCC_IT_LSIRDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_LSIRDY);
    HAL_RCC_LSI_ReadyCallback();
  }

  if ((it_flags_sources & LL_RCC_IT_PLL1RDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_PLL1RDY);
    HAL_RCC_PLL1_ReadyCallback();
  }

#if defined(PLL2)
  if ((it_flags_sources & LL_RCC_IT_PLL2RDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_PLL2RDY);
    HAL_RCC_PLL2_ReadyCallback();
  }
#endif /* PLL2 */
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_2
  * @{
  */

/**
  * @brief  Set the system clock source (SYSCLK).
  * @param  source  System clock source based on @ref hal_rcc_sysclk_src_t
  * @retval HAL_OK    Success\n
  * @retval HAL_ERROR System clock source has not been applied\n
  *                   HSI not enabled or not ready to switch to HSI as system clock\n
  *                   HSE not enabled or not ready to switch to HSE as system clock\n
  *                   PLL1 and PLL1P output not enabled or not ready to switch to PLLCLK\n
  */
hal_status_t HAL_RCC_SetSYSCLKSource(hal_rcc_sysclk_src_t source)
{
  uint32_t tickstart;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_RCC_SYSCLKSOURCE(source));

  LL_RCC_SetSysClkSource((uint32_t)source);

  tickstart = HAL_GetTick();

  while (HAL_RCC_GetSYSCLKSource() != source)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (HAL_RCC_GetSYSCLKSource() != source)
      {
        status = HAL_ERROR;
        break;
      }
    }
  }

  return status;
}

/**
  * @brief   Get the system clock source (SYSCLK).
  * @retval  hal_rcc_sysclk_src_t System Clock source
  */
hal_rcc_sysclk_src_t HAL_RCC_GetSYSCLKSource(void)
{
  return (hal_rcc_sysclk_src_t)(uint32_t)((LL_RCC_GetSysClkSource() >> RCC_CFGR1_SYSSWS_Pos) << RCC_CFGR1_SYSSW_Pos);
}

/**
  * @brief  Set the AHB clock (HCLK) prescaler.
  * @param  prescaler  Prescaler value
  */
void HAL_RCC_SetHCLKPrescaler(hal_rcc_hclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_HCLK(prescaler));

  LL_RCC_SetAHBPrescaler((uint32_t)prescaler);
}

/**
  * @brief  Set the APB1 clock (PCLK1) prescaler.
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK1Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB1Prescaler((uint32_t)prescaler);
}

/**
  * @brief  Set the APB2 clock (PCLK2) prescaler.
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK2Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB2Prescaler(((uint32_t)prescaler) << (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos));
}

/**
  * @brief  Set the APB3 clock (PCLK3) prescaler.
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK3Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB3Prescaler(((uint32_t)prescaler) << (RCC_CFGR2_PPRE3_Pos - RCC_CFGR2_PPRE1_Pos));
}

/**
  * @brief  Get the AHB bus clock prescaler (HCLK).
  * @retval hal_rcc_hclk_prescaler_t Prescaler value
  */
hal_rcc_hclk_prescaler_t HAL_RCC_GetHCLKPrescaler(void)
{
  return (hal_rcc_hclk_prescaler_t)LL_RCC_GetAHBPrescaler();
}

/**
  * @brief  Get the APB1 bus clock prescaler (PCLK1).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK1Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)LL_RCC_GetAPB1Prescaler();
}

/**
  * @brief  Get the APB2 bus clock prescaler (PCLK2).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK2Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB2Prescaler() >> (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos));
}

/**
  * @brief  Get the APB3 bus clock prescaler (PCLK3).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK3Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB3Prescaler() >> (RCC_CFGR2_PPRE3_Pos - RCC_CFGR2_PPRE1_Pos));
}

/**
  * @brief  Configure the bus dividers.
  * @param  p_config Pointer based on @ref hal_rcc_bus_clk_config_t structure
  * @warning FLASH latency must be adjusted according to the targeted system clock
  *          frequency and voltage scaling.
  * @retval HAL_OK            Success
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  */
hal_status_t HAL_RCC_SetBusClockConfig(const hal_rcc_bus_clk_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_HCLK(p_config->hclk_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk1_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk2_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk3_prescaler));

  /* Configure prescalers for the available Bus */
  LL_RCC_ConfigBusClock((uint32_t)p_config->hclk_prescaler  |
                        (uint32_t)p_config->pclk1_prescaler |
                        (uint32_t)((uint32_t)p_config->pclk2_prescaler <<
                                   (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos)) |
                        (uint32_t)((uint32_t)p_config->pclk3_prescaler <<
                                   (RCC_CFGR2_PPRE3_Pos - RCC_CFGR2_PPRE1_Pos)));

  return HAL_OK;
}

/**
  * @brief Retrieve the bus dividers.
  * @param p_config Pointer on @ref hal_rcc_bus_clk_config_t structure
  */
void HAL_RCC_GetBusClockConfig(hal_rcc_bus_clk_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  /* Get Bus prescalers */
  p_config->hclk_prescaler = (hal_rcc_hclk_prescaler_t)LL_RCC_GetAHBPrescaler();
  p_config->pclk1_prescaler = (hal_rcc_pclk_prescaler_t)LL_RCC_GetAPB1Prescaler();
  p_config->pclk2_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB2Prescaler()
                                                                   >> (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos));
  p_config->pclk3_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB3Prescaler()
                                                                   >> (RCC_CFGR2_PPRE3_Pos - RCC_CFGR2_PPRE1_Pos));
}

/**
  * @brief   Return the SYSCLK frequency.
  * @note    The system frequency computed by this function is calculated based on the predefined constant and
  *          the selected clock source. Its value can slightly differ from the real frequency in the chip.
  * @note    If SYSCLK source is HSI, function returns values based on HSI_VALUE(*).
  * @note    If SYSCLK source is HSE, function returns values based on HSE_VALUE(**).
  * @note    If SYSCLK source is PLL, function returns values based on HSE_VALUE(**) or HSI_VALUE(*)
  *          multiplied/divided by the PLL factors.
  * @note    This function can be used by the user application to compute the baudrate for the communication
  *          peripherals or configure other parameters.
  * @warning Each time SYSCLK changes, this function must be called to update the right SYSCLK value.
  *          Otherwise, any configuration based on this function will be incorrect.
  * @retval  uint32_t SYSCLK frequency in Hz
  */
uint32_t HAL_RCC_GetSYSCLKFreq(void)
{
  uint32_t sysclockfreq;
  uint32_t sysclk_source = LL_RCC_GetSysClkSource();

  if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
    sysclockfreq = RCC_HSI_GetClockFreq();
  }
#if defined(HSE_VALUE)
  else if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
  {
    sysclockfreq = HSE_VALUE;
  }
#endif /* HSE_VALUE */
  else
  {
    hal_rcc_pll_output_freq_t pll_clocks;
    HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
    sysclockfreq = pll_clocks.pll_p_freq;
  }

  return sysclockfreq;
}

/**
  * @brief  Return the HCLK frequency.
  * @warning Each time HCLK changes, this function must be called to update the
  *          right HCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t HCLK frequency in Hz
  */
uint32_t HAL_RCC_GetHCLKFreq(void)
{
  return HAL_RCC_GetSYSCLKFreq() >> AHBPrescTable[LL_RCC_GetAHBPrescaler()];
}

/**
  * @brief  Return the PCLK1 frequency.
  * @warning Each time PCLK1 changes, this function must be called to update the
  *          right PCLK1 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK1 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK1Freq(void)
{
  /* Get HCLK source and Compute PCLK1 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB1Prescaler() >> RCC_CFGR2_PPRE1_Pos]);
}

/**
  * @brief  Return the PCLK2 frequency.
  * @warning Each time PCLK2 changes, this function must be called to update the
  *          right PCLK2 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK2 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK2Freq(void)
{
  /* Get HCLK source and Compute PCLK2 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB2Prescaler() >> RCC_CFGR2_PPRE2_Pos]);
}

/**
  * @brief  Return the PCLK3 frequency.
  * @warning Each time PCLK3 changes, this function must be called to update the
  *          right PCLK3 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK3 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK3Freq(void)
{
  /* Get HCLK source and Compute PCLK3 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB3Prescaler() >> RCC_CFGR2_PPRE3_Pos]);
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_3
  * @{
  */

/**
  * @brief  Set the Systick external clock source.
  * @param  clk_src Systick external clock source selection based on @ref hal_rcc_systick_clk_src_t
  */
void HAL_RCC_SetSysTickExternalClkSource(hal_rcc_systick_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SYSTICK_CLK(clk_src));

  LL_RCC_SetSystickClockSource((uint32_t)clk_src);
}

/**
  * @brief  Get the Systick external clock source.
  * @retval Systick external clock source based on @ref hal_rcc_systick_clk_src_t
  */
hal_rcc_systick_clk_src_t HAL_RCC_GetSysTickExternalClkSource(void)
{
  return (hal_rcc_systick_clk_src_t)LL_RCC_GetSystickClockSource();
}

/**
  * @brief  Return the systick external clock frequency.
  * @retval uint32_t Frequency in Hz.
  */
uint32_t HAL_RCC_GetSysTickExternalClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSystickClockSource();

  switch (srcclk)
  {
    case LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8:
      frequency = (HAL_RCC_GetHCLKFreq() >> 3);
      break;
    case LL_RCC_SYSTICK_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;
    case LL_RCC_SYSTICK_CLKSOURCE_LSE:
#if defined(LSE_VALUE)
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
#endif /* LSE_VALUE */
      break;
    default:
      break;
  }
  return frequency;
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_4
  * @{
  */

/**
  * @brief Set the Intermediate clock x (ICLKx) divider.
  * @param iclkx  the intermediate clock Id based on @ref hal_rcc_iclk_t
  * @param iclk_divider the intermediate clock divider based on @ref hal_rcc_iclk_div_t
  * @note  ICLKx divider can be changed on-the-fly
  */
void HAL_RCC_ICLK_SetDivider(hal_rcc_iclk_t iclkx, hal_rcc_iclk_div_t iclk_divider)
{
  ASSERT_DBG_PARAM(IS_RCC_ICLK(iclkx));
  ASSERT_DBG_PARAM(IS_RCC_ICLK_DIV_VALUE(iclk_divider));

  LL_RCC_ICLK_SetDivider((uint32_t)iclkx, (uint32_t)iclk_divider);
}

/**
  * @brief  Get the Intermediate clock x (ICLKx) divider.
  * @param  iclkx  the intermediate clock Id based on @ref hal_rcc_iclk_t
  * @retval hal_rcc_iclk_div_t the intermediate clock x divider value
  */
hal_rcc_iclk_div_t HAL_RCC_ICLK_GetDivider(hal_rcc_iclk_t iclkx)
{
  ASSERT_DBG_PARAM(IS_RCC_ICLK(iclkx));

  return (hal_rcc_iclk_div_t)LL_RCC_ICLK_GetDivider((uint32_t)iclkx);
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_5
  * @{
  */

/**
  * @brief   Configure PLL1 without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLL1 is well deactivated (if enabled exit from this function)
  *           - Configure the PLL1 with full list of parameters
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL1
  * @retval HAL_OK            PLL1 has been correctly configured
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR         PLL1 is already enabled and can not be modified.
  * @note   FracN value can be modified on-the-fly (with PLL running) using HAL_RCC_PLL1_SetFRACN() function.
  */
hal_status_t HAL_RCC_PLL1_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  uint32_t pll_ready;

  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLL_SOURCE(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));
  ASSERT_DBG_PARAM(IS_RCC_PLLP_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLR_VALUE(p_config->pll_r));
  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));
  ASSERT_DBG_PARAM(IS_RCC_PLL_INPUT_RANGE(p_config->pll_input_range));
  ASSERT_DBG_PARAM(IS_RCC_PLL_VCO_RANGE(p_config->pll_vco_range));

  /*
     The config function will perform the following actions:
     - Check in PLLx is well deactivated (if enabled exit from this function)
     - Configure the PLLx with full list of parameters
   */
  pll_ready = LL_RCC_PLL1_IsReady();

  if (pll_ready == 0U)
  {
    LL_RCC_PLL1_SetSource((uint32_t)p_config->pll_source);
    LL_RCC_PLL1_SetM(p_config->pll_m);
    LL_RCC_PLL1_DisableFRACN();
    LL_RCC_PLL1_SetFRACN(p_config->pll_fracn);

    LL_RCC_PLL1_SetN(p_config->pll_n);
    LL_RCC_PLL1_EnableFRACN();

    LL_RCC_PLL1_SetP(p_config->pll_p);
    LL_RCC_PLL1_SetQ(p_config->pll_q);
    LL_RCC_PLL1_SetR(p_config->pll_r);

    LL_RCC_PLL1_SetInputRange((uint32_t)p_config->pll_input_range);
    LL_RCC_PLL1_SetVCORange((uint32_t)p_config->pll_vco_range);

    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief Return the configuration of PLL1.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL1
  */
void HAL_RCC_PLL1_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  p_config->pll_source      = (hal_rcc_pll_src_t)LL_RCC_PLL1_GetSource();
  p_config->pll_m           = (uint8_t)LL_RCC_PLL1_GetM();
  p_config->pll_input_range = (hal_rcc_pll_input_range_t)LL_RCC_PLL1_GetInputRange();
  p_config->pll_vco_range   = (hal_rcc_pll_vco_range_t)LL_RCC_PLL1_GetVCORange();

  p_config->pll_n     = (uint16_t)LL_RCC_PLL1_GetN();
  p_config->pll_p     = (uint8_t)LL_RCC_PLL1_GetP();
  p_config->pll_q     = (uint8_t)LL_RCC_PLL1_GetQ();
  p_config->pll_r     = (uint8_t)LL_RCC_PLL1_GetR();

  p_config->pll_fracn = (uint16_t)LL_RCC_PLL1_GetFRACN();

}

/**
  * @brief  Set the fractional part (FRACN) of the multiplication factor of PLL1 on-the-fly.
  * @param  fracn The new fractional value to be set for PLL1.
  * @retval HAL_OK     The FRACN value has been correctly set.
  * @retval HAL_ERROR  The FRACN value update has failed.
  */
hal_status_t HAL_RCC_PLL1_SetFRACN(uint16_t fracn)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(fracn));

  /* FRACN1 on-the-fly value update */
  if (LL_RCC_PLL1_GetFRACN() != fracn)
  {
    LL_RCC_PLL1_DisableFRACN();

    tickstart = HAL_GetTick();
    /* Wait at least 3 refx_ck (PLL1 input source divided by M) period to make sure next latched value will be taken
      into account. */
    while ((HAL_GetTick() - tickstart) < RCC_PLL_FRAC_WAIT_VALUE)
    {
    }

    LL_RCC_PLL1_SetFRACN(fracn);

    /* Enable PLL1FRACN to latch the new value. */
    LL_RCC_PLL1_EnableFRACN();
  }

  return HAL_OK;
}

/**
  * @brief  Get the current fractional part (FRACN) of the multiplication factor of PLL1.
  * @retval The current fractional value of PLL1.
  */
uint16_t HAL_RCC_PLL1_GetFRACN(void)
{
  return (uint16_t)LL_RCC_PLL1_GetFRACN();
}

/**
  * @brief  Enable PLL1.
  * @note   If PLL is not enabled, enable it and wait for RDY state.
  * @retval HAL_OK    PLL1 correctly enabled or already enabled.
  * @retval HAL_ERROR Timeout detected during enabling of the PLL1
  */
hal_status_t HAL_RCC_PLL1_Enable(void)
{
  hal_status_t status = HAL_OK;
  /*
    - If PLL not enabled => enable it and wait for RDY state (error only if problem to enable)
  */
  if (LL_RCC_PLL1_IsReady() == 0U)
  {
    LL_RCC_PLL1_Enable();
    status = RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 1U);
  }

  return status;
}

/**
  * @brief  Enable PLL1 in interrupt mode.
  * @note   This function only enables the PLL1 and the corresponding ready interrupt.
  *         When PLL1 is ready, the callback HAL_RCC_PLL1_ReadyCallback() is invoked.
  * @retval HAL_OK    PLL1 enable sequence has been started.
  */
hal_status_t HAL_RCC_PLL1_Enable_IT(void)
{
  LL_RCC_EnableIT(LL_RCC_IT_PLL1RDY);

  if (LL_RCC_PLL1_IsReady() == 0U)
  {
    LL_RCC_PLL1_Enable();
  }

  return HAL_OK;
}

/**
  * @brief   Disable PLL1.
  * @details PLL1 cannot be disabled if used as system level
  *           - If PLL1 Output is as used as system level => return an error
  *           - If PLL1 enabled => disable PLL1 and wait for deactivation (error only if problem to disable)
  * @retval HAL_OK    PLL1 correctly deactivated or already deactivated.
  * @retval HAL_ERROR PLL1 is used as system level and cannot be deactivated\n
  *                   Timeout detected during disabling of the PLL1
  */
hal_status_t HAL_RCC_PLL1_Disable(void)
{
  hal_status_t status = HAL_ERROR;
  /*
    - If PLL1 is as used as system level => return an error
    - Else disable PLL1 and wait for deactivation (error only if problem to disable)
  */
  if (HAL_RCC_GetSYSCLKSource() != HAL_RCC_SYSCLK_SRC_PLLCLK)
  {
    LL_RCC_PLL1_Disable();
    LL_RCC_DisableIT(LL_RCC_IT_PLL1RDY);
    status = RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U);
  }
  return status;
}

/**
  * @brief Check if the PLL1 is ready.
  * @retval HAL_RCC_PLL_ENABLED  PLL1 is ready
  * @retval HAL_RCC_PLL_DISABLED PLL1 is not ready
  */
hal_rcc_pll_status_t HAL_RCC_PLL1_IsReady(void)
{
  return (hal_rcc_pll_status_t)LL_RCC_PLL1_IsReady();
}

/**
  * @brief  RCC PLL1 ready interrupt callback.
  */
__WEAK void HAL_RCC_PLL1_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_PLL1_ReadyCallback must be implemented in the user file
   */
}

/**
  * @brief Enable output(s) of PLL1.
  * @param output Output to enable for PLL1
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_P or @ref HAL_RCC_PLL1_SYSCLK
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_R
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been activated
  */
hal_status_t HAL_RCC_PLL1_EnableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL1_OUTPUT(output));

  LL_RCC_PLL1_EnableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Disable output(s) of PLL1.
  * @param  output Output to disable for PLL1
  *                It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_P or @ref HAL_RCC_PLL1_SYSCLK
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_R
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been deactivated
  * @retval HAL_ERROR Output is used as system clock and cannot be deactivated
  */
hal_status_t HAL_RCC_PLL1_DisableOutput(uint32_t output)
{
  hal_rcc_sysclk_src_t src_clk;
  hal_status_t status = HAL_ERROR;
  ASSERT_DBG_PARAM(IS_RCC_PLL1_OUTPUT(output));
  /*
    - If output is used as system clock => return an error
    - else disable output(s) of the PLL1
  */
  src_clk = HAL_RCC_GetSYSCLKSource();
  if ((src_clk != HAL_RCC_SYSCLK_SRC_PLLCLK)
      || ((src_clk == HAL_RCC_SYSCLK_SRC_PLLCLK)
          && ((output & HAL_RCC_PLL1_OUTPUT_P) != HAL_RCC_PLL1_OUTPUT_P)))
  {
    LL_RCC_PLL1_DisableOutput(output);
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Return the enabled output(s) of PLL1.
  * @retval output PLL1 outputs.
  *         It can be a combination of the following values:
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_P or @ref HAL_RCC_PLL1_SYSCLK
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_Q
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_R
  */
uint32_t HAL_RCC_PLL1_GetOutput(void)
{
  return LL_RCC_PLL1_GetOutput();
}

/**
  * @brief    Disable PLL1 for power consumption perspective.
  * @warning  To enable again PLL1, a new configuration must be applied.
  * @details  This function allow to reset all the parameters which might impact power
  *           like PLLSRC, outputs...
  * @retval HAL_OK    PLL1 is correctly disabled\n
  * @retval HAL_ERROR Output is used as system level and cannot be disabled\n
  *                   Timeout to disable PLL1
  */
hal_status_t HAL_RCC_PLL1_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  if (HAL_RCC_GetSYSCLKSource() != HAL_RCC_SYSCLK_SRC_PLLCLK)
  {
    LL_RCC_PLL1_DisableOutput(LL_RCC_PLL1_OUTPUT_P | LL_RCC_PLL1_OUTPUT_Q | LL_RCC_PLL1_OUTPUT_R);
    LL_RCC_PLL1_Disable();
    if (RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U) == HAL_OK)
    {
      /* To save power disable the PLL1 SRC, PLLM and divider factors */
      LL_RCC_CLEAR_BIT(PLL1CFGR, RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M);
      LL_RCC_CLEAR_BIT(PLL1DIVR, RCC_PLL1DIVR_PLL1P | RCC_PLL1DIVR_PLL1Q | RCC_PLL1DIVR_PLL1R);
      status = HAL_OK;
    }
  }
  return status;
}

/**
  * @brief  Returns the PLL1 clock frequencies: pll_p_freq, pll_q_freq and pll_r_freq.
  * @param  p_clk Contains the frequency for each PLL1 output (in Hz).
  * @note   The PLL1 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE or HSI_VALUE multiplied/divided by the PLL factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL1CLK changes, this function must be called to update the
  *          right PLL1CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL1_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  uint32_t pll_source;
  uint32_t pll_m;
  uint32_t pll_n;
  uint32_t pll_fracen;
  uint32_t fracn;
  uint64_t pll_vco_num;
  uint64_t pll_vco_den;

  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;

  /* If PLL1 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL1_IsReady() == 0U)
  {
    return;
  }

  /* Fixed-point computation:
  * PLL_VCO = Fsrc * (N + FRACN / PLL_FRACN_MODULUS) / M
  * pll_vco_num = Fsrc * (N * PLL_FRACN_MODULUS + FRACN)
  * pll_vco_den = M * PLL_FRACN_MODULUS
  * Then:
  * PLLx = pll_vco_num / (pll_vco_den * divider_x) (P, Q or R)
  */
  pll_m = LL_RCC_PLL1_GetM();

  if (pll_m == 0U)
  {
    return;
  }

  pll_source = LL_RCC_PLL1_GetSource();
  pll_fracen = LL_RCC_PLL1_IsEnabledFRACN();
  pll_n = LL_RCC_PLL1_GetN();
  fracn = (uint32_t)(pll_fracen * LL_RCC_PLL1_GetFRACN());
  switch (pll_source)
  {
    case LL_RCC_PLL1SOURCE_HSI:  /* HSI used as PLL clock source */
      pll_vco_num = (uint64_t)RCC_HSI_GetClockFreq();
      break;
#if defined(HSE_VALUE)
    case LL_RCC_PLL1SOURCE_HSE:  /* HSE used as PLL clock source */
      pll_vco_num = (uint64_t)HSE_VALUE;
      break;
#endif /* HSE_VALUE */
    default:
      pll_vco_num = 0;
      break;
  }
  pll_vco_num = pll_vco_num * (((uint64_t)pll_n * PLL_FRACN_MODULUS) + fracn);
  pll_vco_den = (uint64_t)pll_m * (uint64_t)PLL_FRACN_MODULUS;

  if (LL_RCC_PLL1_IsOutputEnabled(LL_RCC_PLL1_OUTPUT_P) == 1U)
  {
    p_clk->pll_p_freq = (uint32_t)(pll_vco_num / (pll_vco_den * (uint64_t)LL_RCC_PLL1_GetP()));
  }

  if (LL_RCC_PLL1_IsOutputEnabled(LL_RCC_PLL1_OUTPUT_Q) == 1U)
  {
    p_clk->pll_q_freq = (uint32_t)(pll_vco_num / (pll_vco_den * (uint64_t)LL_RCC_PLL1_GetQ()));
  }

  if (LL_RCC_PLL1_IsOutputEnabled(LL_RCC_PLL1_OUTPUT_R) == 1U)
  {
    p_clk->pll_r_freq = (uint32_t)(pll_vco_num / (pll_vco_den * (uint64_t)LL_RCC_PLL1_GetR()));
  }
}

/**
  * @}
  */

#if defined(PLL2)
/** @addtogroup RCC_Exported_Functions_Group1_6
  * @{
  */

/**
  * @brief   Configure PLL2 without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLL2 is well deactivated (if enabled exit from this function)
  *           - Configure the PLL2 with full list of parameters
  * @param  p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *         contains the configuration information for the PLL2
  * @retval HAL_OK    PLL2 has been correctly configured
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR PLL2 is already enabled and can not be modified.
  * @note   FracN value can be modified on-the-fly (with PLL running) using HAL_RCC_PLL2_SetFRACN() function.
  */
hal_status_t HAL_RCC_PLL2_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  uint32_t pll_ready;

  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLL_SOURCE(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));
  ASSERT_DBG_PARAM(IS_RCC_PLLP_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLR_VALUE(p_config->pll_r));
  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));
  ASSERT_DBG_PARAM(IS_RCC_PLL_INPUT_RANGE(p_config->pll_input_range));
  ASSERT_DBG_PARAM(IS_RCC_PLL_VCO_RANGE(p_config->pll_vco_range));

  /*
     The config function will perform the following actions:
     - Check in PLLx is well deactivated (if enabled exit from this function)
     - Configure the PLLx with full list of parameters
   */
  pll_ready = LL_RCC_PLL2_IsReady();

  if (pll_ready == 0U)
  {
    LL_RCC_PLL2_SetSource((uint32_t)p_config->pll_source);
    LL_RCC_PLL2_SetM(p_config->pll_m);
    LL_RCC_PLL2_DisableFRACN();
    LL_RCC_PLL2_SetFRACN(p_config->pll_fracn);

    LL_RCC_PLL2_SetN(p_config->pll_n);
    LL_RCC_PLL2_EnableFRACN();

    LL_RCC_PLL2_SetP(p_config->pll_p);
    LL_RCC_PLL2_SetQ(p_config->pll_q);
    LL_RCC_PLL2_SetR(p_config->pll_r);

    LL_RCC_PLL2_SetInputRange((uint32_t)p_config->pll_input_range);
    LL_RCC_PLL2_SetVCORange((uint32_t)p_config->pll_vco_range);

    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief Return the configuration of PLL2.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL2
  */
void HAL_RCC_PLL2_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  p_config->pll_source      = (hal_rcc_pll_src_t)LL_RCC_PLL2_GetSource();
  p_config->pll_m           = (uint8_t)LL_RCC_PLL2_GetM();
  p_config->pll_input_range = (hal_rcc_pll_input_range_t)LL_RCC_PLL2_GetInputRange();
  p_config->pll_vco_range   = (hal_rcc_pll_vco_range_t)LL_RCC_PLL2_GetVCORange();

  p_config->pll_n     = (uint16_t)LL_RCC_PLL2_GetN();
  p_config->pll_p     = (uint8_t)LL_RCC_PLL2_GetP();
  p_config->pll_q     = (uint8_t)LL_RCC_PLL2_GetQ();
  p_config->pll_r     = (uint8_t)LL_RCC_PLL2_GetR();

  p_config->pll_fracn = (uint16_t)LL_RCC_PLL2_GetFRACN();
}

/**
  * @brief  Set the fractional part (FRACN) of the multiplication factor of PLL2 on-the-fly.
  * @param  fracn The new fractional value to be set for PLL2.
  * @retval HAL_OK     The FRACN value has been correctly set.
  * @retval HAL_ERROR  The FRACN value update has failed.
  */
hal_status_t HAL_RCC_PLL2_SetFRACN(uint16_t fracn)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(fracn));

  /* FRACN1 on-the-fly value update */
  if (LL_RCC_PLL2_GetFRACN() != fracn)
  {
    LL_RCC_PLL2_DisableFRACN();

    tickstart = HAL_GetTick();
    /* Wait at least 2 CK_REF (PLL2 input source divided by M) period to make sure next latched value will be taken
      into account. */
    while ((HAL_GetTick() - tickstart) < RCC_PLL_FRAC_WAIT_VALUE)
    {
    }

    LL_RCC_PLL2_SetFRACN(fracn);

    /* Enable PLL2FRACN to latch the new value. */
    LL_RCC_PLL2_EnableFRACN();
  }

  return HAL_OK;
}

/**
  * @brief  Get the current fractional part (FRACN) of the multiplication factor of PLL2.
  * @retval The current fractional value of PLL2.
  */
uint16_t HAL_RCC_PLL2_GetFRACN(void)
{
  return (uint16_t)LL_RCC_PLL2_GetFRACN();
}

/**
  * @brief  Enable PLL2.
  * @note   If PLL is not enabled, enable it and wait for RDY state.
  * @retval HAL_OK    PLL2 correctly enabled or already enabled.
  * @retval HAL_ERROR Timeout detected during enabling of the PLL2
  */
hal_status_t HAL_RCC_PLL2_Enable(void)
{
  hal_status_t status = HAL_OK;
  /* If PLL not enabled => enable it and wait for RDY state (error only if problem to enable) */
  if (LL_RCC_PLL2_IsReady() == 0U)
  {
    LL_RCC_PLL2_Enable();
    status = RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 1U);
  }

  return status;
}

/**
  * @brief  Enable PLL2 in interrupt mode.
  * @note   This function only enables the PLL2 and the corresponding ready interrupt.
  *         When PLL2 is ready, the callback HAL_RCC_PLL2_ReadyCallback() is invoked.
  * @retval HAL_OK    PLL2 enable sequence has been started
  */
hal_status_t HAL_RCC_PLL2_Enable_IT(void)
{
  LL_RCC_EnableIT(LL_RCC_IT_PLL2RDY);
  if (LL_RCC_PLL2_IsReady() == 0U)
  {
    LL_RCC_PLL2_Enable();
  }

  return HAL_OK;
}

/**
  * @brief  Disable PLL2.
  * @details If PLL2 enabled => disable PLL2 and wait for deactivation (error only if problem to disable)
  * @warning To ensure a correct behavior of the PLL2, all PLL2 outputs must be disabled before disabling the PLL2.
  *          This is done by calling HAL_RCC_PLL2_DisableOutput()
  * @retval HAL_OK    PLL2 correctly deactivated or PLL2 was already disabled.
  * @retval HAL_ERROR Timeout detected during disabling of the PLL2
  */
hal_status_t HAL_RCC_PLL2_Disable(void)
{
  LL_RCC_PLL2_Disable();
  LL_RCC_DisableIT(LL_RCC_IT_PLL2RDY);
  return RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 0U);
}

/**
  * @brief Check if the PLL2 is ready.
  * @retval HAL_RCC_PLL_ENABLED  PLL2 is ready
  * @retval HAL_RCC_PLL_DISABLED PLL2 is not ready
  */
hal_rcc_pll_status_t HAL_RCC_PLL2_IsReady(void)
{
  return (hal_rcc_pll_status_t)LL_RCC_PLL2_IsReady();
}

/**
  * @brief  RCC PLL2 ready interrupt callback.
  */
__WEAK void HAL_RCC_PLL2_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_PLL2_ReadyCallback must be implemented in the user file
   */
}

/**
  * @brief Enable output(s) of PLL2.
  * @param output Output to enable for PLL2
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_R
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been activated
  */
hal_status_t HAL_RCC_PLL2_EnableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL2_OUTPUT(output));

  LL_RCC_PLL2_EnableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Disable output(s) of PLL2.
  * @param  output Output to disable for PLL2
  *                It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_R
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been deactivated
  */
hal_status_t HAL_RCC_PLL2_DisableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL2_OUTPUT(output));

  LL_RCC_PLL2_DisableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Return the enabled output(s) of PLL2.
  * @retval output PLL2 outputs.
  *         It can be a combination of the following values:
  *            @arg @ref HAL_RCC_PLL2_OUTPUT_P
  *            @arg @ref HAL_RCC_PLL2_OUTPUT_Q
  *            @arg @ref HAL_RCC_PLL2_OUTPUT_R
  */
uint32_t HAL_RCC_PLL2_GetOutput(void)
{
  return LL_RCC_PLL2_GetOutput();
}

/**
  * @brief    Disable PLL2 for power consumption perspective.
  * @warning  To enable again PLL2, a new configuration must be applied.
  * @details  This function allow to reset all the parameters which might impact power like PLLSRC, outputs...
  * @retval   HAL_OK    PLL2 is correctly disabled
  * @retval   HAL_ERROR PLL2 not disabled
  */
hal_status_t HAL_RCC_PLL2_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  LL_RCC_PLL2_DisableOutput(LL_RCC_PLL2_OUTPUT_P | LL_RCC_PLL2_OUTPUT_Q | LL_RCC_PLL2_OUTPUT_R);
  LL_RCC_PLL2_Disable();
  if (RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 0U) == HAL_OK)
  {
    /* To save power disable the PLL2 SRC, PLLM and divider factors */
    LL_RCC_CLEAR_BIT(PLL2CFGR, RCC_PLL2CFGR_PLL2SRC | RCC_PLL2CFGR_PLL2M);
    LL_RCC_CLEAR_BIT(PLL2DIVR, RCC_PLL2DIVR_PLL2P | RCC_PLL2DIVR_PLL2Q | RCC_PLL2DIVR_PLL2R);
    status = HAL_OK;
  }
  return status;
}

/**
  * @brief  Returns the PLL2 clock frequencies: pll_p_freq, pll_q_freq and pll_r_freq.
  * @param  p_clk Contains the frequency for each PLL2 output (in Hz).
  * @note   The PLL2 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE or HSI_VALUE multiplied/divided by the PLL factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL2CLK changes, this function must be called to update the
  *          right PLL2CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL2_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  /* Fixed-point computation:
  * PLL_VCO = Fsrc * (N + FRACN / PLL_FRACN_MODULUS) / M
  * pll_vco_num = Fsrc * (N * PLL_FRACN_MODULUS + FRACN)
  * pll_vco_den = M * PLL_FRACN_MODULUS
  * Then:
  * PLLx = pll_vco_num / (pll_vco_den * divider_x) (P, Q or R)
  */

  uint32_t pll_source;
  uint32_t pll_m;
  uint32_t pll_n;
  uint32_t pll_fracen;
  uint32_t pll_fracn;
  uint64_t pll_vco_num;
  uint64_t pll_vco_den;

  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;

  /* If PLL2 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL2_IsReady() == 0U)
  {
    return;
  }


  pll_m = LL_RCC_PLL2_GetM();

  if (pll_m == 0U)
  {
    return;
  }

  pll_source = LL_RCC_PLL2_GetSource();
  pll_fracen = LL_RCC_PLL2_IsEnabledFRACN();
  pll_n = LL_RCC_PLL2_GetN();
  pll_fracn = (uint32_t)(pll_fracen * LL_RCC_PLL2_GetFRACN());
  switch (pll_source)
  {
    case LL_RCC_PLL2SOURCE_HSI:  /* HSI used as PLL clock source */
      pll_vco_num = (uint64_t)RCC_HSI_GetClockFreq();
      break;
#if defined(HSE_VALUE)
    case LL_RCC_PLL2SOURCE_HSE:  /* HSE used as PLL clock source */
      pll_vco_num = (uint64_t)HSE_VALUE;
      break;
#endif /* HSE_VALUE */
    default:
      pll_vco_num = 0;
      break;
  }
  pll_vco_num = pll_vco_num * (((uint64_t)pll_n * PLL_FRACN_MODULUS) + pll_fracn);
  pll_vco_den = (uint64_t)pll_m * (uint64_t)PLL_FRACN_MODULUS;

  if (LL_RCC_PLL2_IsOutputEnabled(LL_RCC_PLL2_OUTPUT_P) == 1U)
  {
    p_clk->pll_p_freq = (uint32_t)(pll_vco_num / (pll_vco_den * (uint64_t)LL_RCC_PLL2_GetP()));
  }

  if (LL_RCC_PLL2_IsOutputEnabled(LL_RCC_PLL2_OUTPUT_Q) == 1U)
  {
    p_clk->pll_q_freq = (uint32_t)(pll_vco_num / (pll_vco_den * (uint64_t)LL_RCC_PLL2_GetQ()));
  }

  if (LL_RCC_PLL2_IsOutputEnabled(LL_RCC_PLL2_OUTPUT_R) == 1U)
  {
    p_clk->pll_r_freq = (uint32_t)(pll_vco_num / (pll_vco_den * (uint64_t)LL_RCC_PLL2_GetR()));
  }
}

/**
  * @}
  */
#endif /* PLL2 */

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group3
  * @{
  */

/**
  * @brief  Select the clock source to output on MCOx pin.
  * @param  mcox_src  specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg HAL_RCC_MCO1_SRC_HSI
  *            @arg HAL_RCC_MCO1_SRC_LSE
  *            @arg HAL_RCC_MCO1_SRC_HSE
  *            @arg HAL_RCC_MCO1_SRC_PLL1Q
  *            @arg HAL_RCC_MCO1_SRC_HSI48
  *            @arg HAL_RCC_MCO2_SRC_SYSCLK
  *            @arg HAL_RCC_MCO2_SRC_PLL2P (*)
  *            @arg HAL_RCC_MCO2_SRC_HSE
  *            @arg HAL_RCC_MCO2_SRC_PLL1P
  *            @arg HAL_RCC_MCO2_SRC_LSI
  * @param  mcox_prescaler  specifies the MCOx prescaler. This parameter can be one of the following
  *         values depending on which MCOx source was selected (MCO1 or MCO2):
  *            @arg HAL_RCC_MCO1_NO_CLK
  *            @arg HAL_RCC_MCO1_PRESCALER1
  *            @arg HAL_RCC_MCO1_PRESCALER2
  *            @arg HAL_RCC_MCO1_PRESCALER3
  *            @arg HAL_RCC_MCO1_PRESCALER4
  *            @arg HAL_RCC_MCO1_PRESCALER5
  *            @arg HAL_RCC_MCO1_PRESCALER6
  *            @arg HAL_RCC_MCO1_PRESCALER7
  *            @arg HAL_RCC_MCO1_PRESCALER8
  *            @arg HAL_RCC_MCO1_PRESCALER9
  *            @arg HAL_RCC_MCO1_PRESCALER10
  *            @arg HAL_RCC_MCO1_PRESCALER11
  *            @arg HAL_RCC_MCO1_PRESCALER12
  *            @arg HAL_RCC_MCO1_PRESCALER13
  *            @arg HAL_RCC_MCO1_PRESCALER14
  *            @arg HAL_RCC_MCO1_PRESCALER15
  *            @arg HAL_RCC_MCO2_NO_CLK
  *            @arg HAL_RCC_MCO2_PRESCALER1
  *            @arg HAL_RCC_MCO2_PRESCALER2
  *            @arg HAL_RCC_MCO2_PRESCALER3
  *            @arg HAL_RCC_MCO2_PRESCALER4
  *            @arg HAL_RCC_MCO2_PRESCALER5
  *            @arg HAL_RCC_MCO2_PRESCALER6
  *            @arg HAL_RCC_MCO2_PRESCALER7
  *            @arg HAL_RCC_MCO2_PRESCALER8
  *            @arg HAL_RCC_MCO2_PRESCALER9
  *            @arg HAL_RCC_MCO2_PRESCALER10
  *            @arg HAL_RCC_MCO2_PRESCALER11
  *            @arg HAL_RCC_MCO2_PRESCALER12
  *            @arg HAL_RCC_MCO2_PRESCALER13
  *            @arg HAL_RCC_MCO2_PRESCALER14
  *            @arg HAL_RCC_MCO2_PRESCALER15
  * @warning MCO selected pin must be configured in alternate function mode.
  *
  *        (*) value not defined in all devices.
  */
void HAL_RCC_SetConfigMCO(hal_rcc_mco_src_t mcox_src, hal_rcc_mco_prescaler_t mcox_prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_MCOSOURCE(mcox_src));
  ASSERT_DBG_PARAM(IS_RCC_MCOPRE(mcox_prescaler));

  LL_RCC_ConfigMCO((uint32_t)mcox_src, (uint32_t)mcox_prescaler);

}

/**
  * @brief  Get reset flags.
  * @retval uint32_t Reset flags based on a combination of @ref RCC_Reset_Flag
  */
uint32_t HAL_RCC_GetResetSource(void)
{
  return (RCC->RSR & HAL_RCC_RESET_FLAG_ALL);
}

/**
  * @brief  Clear reset flags.
  */
void HAL_RCC_ClearResetFlags(void)
{
  LL_RCC_ClearResetFlags();
}

#if defined(HSE_VALUE)
/**
  * @brief  Enable the HSE Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator is automatically disabled and an
  *         interrupt is generated to inform the software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to the Cortex-M33 NMI (Non-Maskable
  *         Interrupt) exception vector.
  * @note   The Clock Security System can only be cleared by reset.
  */
void HAL_RCC_HSE_EnableCSS(void)
{
  LL_RCC_HSE_EnableCSS();
}

/**
  * @brief   Handle the RCC Clock Security System interrupt request.
  * @warning This API must be called under the NMI_Handler().
  * @retval  HAL_OK    NMI has been managed and NMI_Handler() might exit
  * @retval  HAL_ERROR NMI has not been managed and NMI_Handler() must not exit
  */
hal_status_t HAL_RCC_NMI_IRQHandler(void)
{
  hal_status_t cb_status = HAL_ERROR;

  if (LL_RCC_IsActiveFlag(LL_RCC_IT_HSECSS) != 0U)
  {
    if (HAL_RCC_HSE_CSSCallback() == HAL_OK)
    {
      LL_RCC_ClearFlag(LL_RCC_IT_HSECSS);
      cb_status = HAL_OK;
    }
  }
  return cb_status;
}

/**
  * @brief  RCC Clock Security System interrupt callback.
  * @retval HAL_OK    CSS error has been managed
  * @retval HAL_ERROR CSS error has not been managed
  */
__WEAK hal_status_t HAL_RCC_HSE_CSSCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_HSE_CSSCallback must be implemented in the user file
   */
  /* Status to be updated to HAL_OK when the user callback managed the CSS error */
  return HAL_ERROR;
}

/**
  * @brief  Set HSE Prescalers for RTC Clock.
  * @param prescaler parameter can be a value between 0 and 63 with 0 an 1 values meaning no division
  * note   prescaler must be correctly set to ensure that the clock supplied to the
  *        RTC is lower than 1 MHz.
  */
void  HAL_RCC_RTC_SetHSEPrescaler(uint32_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_RTC_HSEDIV(prescaler));

  LL_RCC_SetRTC_HSEPrescaler(prescaler);
}

/**
  * @brief  Get the RTC HSE prescaler.
  * @retval uint32_t Prescaler value
  */
uint32_t HAL_RCC_RTC_GetHSEPrescaler(void)
{
  return LL_RCC_GetRTC_HSEPrescaler();
}

#endif /* HSE_VALUE */


#if defined(LSE_VALUE)
/**
  * @brief  Enable the LSE Clock Security System.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator is to be enabled with HAL_RCC_LSE_Enable()
  *         and the LSE oscillator clock is to be selected as RTC clock with HAL_RCC_RTC_SetKernelClkSource().
  */
void HAL_RCC_LSE_EnableCSS(void)
{
  LL_RCC_LSE_EnableCSS();
}

/**
  * @brief  Disable the LSE Clock Security System.
  * @note   LSE Clock Security System can only be disabled after a LSE failure detection.
  */
void HAL_RCC_LSE_DisableCSS(void)
{
  LL_RCC_LSE_DisableCSS();
}

/**
  * @brief  Check if an LSE CSS failure is detected.
  * @retval hal_rcc_lse_css_failure_detection_status_t LSE CSS failure detection status
  */
hal_rcc_lse_css_failure_detection_status_t HAL_RCC_LSE_IsCSSDetected(void)
{
  return (hal_rcc_lse_css_failure_detection_status_t)LL_RCC_LSE_IsCSSDetected();
}

/**
  * @brief   Handle the RCC LSE Clock Security System interrupt request.
  * @warning TAMP3 interruption line must be previously configured and enabled to detect this interruption.
  * @note    LSECSS EXTI interrupt line available in G5 except STM32G575/585 rev. X and STM32G59x/5Ax rev. B/Y devices.
  */
void HAL_RCC_LSECSS_IRQHandler(void)
{
  if (LL_RCC_LSE_IsCSSDetected() != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_LSECSS);
    HAL_RCC_LSE_CSSCallback();
  }
}

/**
  * @brief  RCC LSE Clock Security System interrupt callback.
  */
__WEAK void HAL_RCC_LSE_CSSCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the @ref HAL_RCC_LSE_CSSCallback must be implemented in the user file
   */
}
#endif /* LSE_VALUE */

/**
  * @brief Enable RTC and TAMP kernel clock.
  * @note  PWR and backup domain are to enabled before calling this function.
  * @retval HAL_OK      RTC and TAMP kernel clock enabled
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_RTC_EnableKernelClock(void)
{
  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_EnableRTC();

  return HAL_OK;
}

/**
  * @brief Disable RTC and TAMP kernel clock.
  * @note  PWR and backup domain are to enabled before calling this function.
  * @retval HAL_OK      RTC and TAMP kernel clock disabled
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_RTC_DisableKernelClock(void)
{
  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_DisableRTC();

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group4
  * @{
  */

/**
  * @brief  Disable all kernel clocks.
  * @note   This function is used to disable all kernel clocks to reduce power consumption.
  * @note   ADC, USB and UCPD kernel clocks can not be disabled.
  * @retval HAL_OK    All kernel clocks have been disabled
  */
hal_status_t HAL_RCC_DisableAllKernelClocks(void)
{
  LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_NONE);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_NONE);
#if defined(USART3)
  LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_NONE);
#endif /* USART3 */
  LL_RCC_SetUARTClockSource(LL_RCC_UART4_CLKSOURCE_NONE);
  LL_RCC_SetUARTClockSource(LL_RCC_UART5_CLKSOURCE_NONE);
  LL_RCC_SetUARTClockSource(LL_RCC_UART6_CLKSOURCE_NONE);
  LL_RCC_SetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE_NONE);
  LL_RCC_SetDACClockSource(LL_RCC_DAC1_CLKSOURCE_NONE);
  LL_RCC_SetDACClockSource(LL_RCC_DAC2_CLKSOURCE_NONE);
  LL_RCC_SetDACClockSource(LL_RCC_DAC5_CLKSOURCE_NONE);
  LL_RCC_SetDACClockSource(LL_RCC_DAC6_CLKSOURCE_NONE);
  LL_RCC_SetDACClockSource(LL_RCC_DAC7_CLKSOURCE_NONE);
  LL_RCC_SetDACClockSource(LL_RCC_DAC8_CLKSOURCE_NONE);
  LL_RCC_SetDACClockSource(LL_RCC_DAC9_CLKSOURCE_NONE);
  LL_RCC_SetDACClockSource(LL_RCC_DAC10_CLKSOURCE_NONE);
  LL_RCC_SetSPIClockSource(LL_RCC_SPI1_CLKSOURCE_NONE);
  LL_RCC_SetSPIClockSource(LL_RCC_SPI2_CLKSOURCE_NONE);
#if defined(SPI3)
  LL_RCC_SetSPIClockSource(LL_RCC_SPI3_CLKSOURCE_NONE);
#endif /* SPI3 */
#if defined(PLAY1)
  LL_RCC_SetPLAYClockSource(LL_RCC_PLAY1_CLKSOURCE_NONE);
#endif /* PLAY1 */
  LL_RCC_SetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE_NONE);
#if defined(XSPI1)
  LL_RCC_SetXSPIClockSource(LL_RCC_XSPI1_CLKSOURCE_NONE);
#endif /* XSPI1 */
  LL_RCC_SetI3CClockSource(LL_RCC_I3C1_CLKSOURCE_NONE);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_NONE);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C2_CLKSOURCE_NONE);
#if defined(I2C3)
  LL_RCC_SetI2CClockSource(LL_RCC_I2C3_CLKSOURCE_NONE);
#endif /* I2C3 */
#if defined(I2C4)
  LL_RCC_SetI2CClockSource(LL_RCC_I2C4_CLKSOURCE_NONE);
#endif /* I2C4 */
  LL_RCC_SetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE_NONE);
#if defined(POSENC1)
  LL_RCC_SetPOSENCClockSource(LL_RCC_POSENC1_CLKSOURCE_NONE);
#endif /* POSENC1 */
#if defined(POSENC2)
  LL_RCC_SetPOSENCClockSource(LL_RCC_POSENC2_CLKSOURCE_NONE);
#endif /* POSENC2 */
  return HAL_OK;
}

/**
  * @brief  Set the USART1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART1_SetKernelClkSource(hal_rcc_usart1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART1_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the USART2 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART2_SetKernelClkSource(hal_rcc_usart2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART2_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(USART3)
/**
  * @brief  Set the USART3 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart3_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART3_SetKernelClkSource(hal_rcc_usart3_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART3_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* USART3 */

/**
  * @brief  Set the UART4 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_uart4_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_UART4_SetKernelClkSource(hal_rcc_uart4_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_UART4_CLK(clk_src));

  LL_RCC_SetUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the UART5 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_uart5_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_UART5_SetKernelClkSource(hal_rcc_uart5_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_UART5_CLK(clk_src));

  LL_RCC_SetUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the UART6 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_uart6_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_UART6_SetKernelClkSource(hal_rcc_uart6_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_UART6_CLK(clk_src));

  LL_RCC_SetUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the LPUART1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_lpuart1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPUART1_SetKernelClkSource(hal_rcc_lpuart1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPUART1_CLK(clk_src));

  LL_RCC_SetLPUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC1_SetKernelClkSource(hal_rcc_dac1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC1_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC2 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC2_SetKernelClkSource(hal_rcc_dac2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC2_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC5 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac5_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC5_SetKernelClkSource(hal_rcc_dac5_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC5_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC6 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac6_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC6_SetKernelClkSource(hal_rcc_dac6_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC6_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC7 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac7_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC7_SetKernelClkSource(hal_rcc_dac7_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC7_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC8 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac8_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC8_SetKernelClkSource(hal_rcc_dac8_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC8_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC9 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac9_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC9_SetKernelClkSource(hal_rcc_dac9_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC9_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC10 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac10_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC10_SetKernelClkSource(hal_rcc_dac10_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC10_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC1 sample and hold clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac1sh_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC1_SetSampleHoldClkSource(hal_rcc_dac1sh_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC1SH_CLK(clk_src));

  LL_RCC_SetDACSHClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC2 sample and hold clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac2sh_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC2_SetSampleHoldClkSource(hal_rcc_dac2sh_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC2SH_CLK(clk_src));

  LL_RCC_SetDACSHClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI1_SetKernelClkSource(hal_rcc_spi1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI1_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI2 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI2_SetKernelClkSource(hal_rcc_spi2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI2_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(SPI3)
/**
  * @brief  Set the SPI3 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi3_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI3_SetKernelClkSource(hal_rcc_spi3_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI3_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* SPI3 */

#if defined(PLAY1)
/**
  * @brief  Set the PLAY1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_play1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_PLAY1_SetKernelClkSource(hal_rcc_play1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_PLAY1_CLK(clk_src));

  LL_RCC_SetPLAYClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the PLAY1 clock divider.
  * @param  divider Divider selection based on @ref hal_rcc_play1_clk_divider_t
  * @retval HAL_OK   Clock divider has been set
  */
hal_status_t HAL_RCC_PLAY1_SetKernelClkDivider(hal_rcc_play1_clk_divider_t divider)
{
  ASSERT_DBG_PARAM(IS_RCC_PLAY1_CLK_DIVIDER(divider));

  LL_RCC_SetPLAY1Divider((uint32_t)divider);
  return HAL_OK;
}

/**
  * @brief  Configure the PLAY1 clock.
  * @param  clk_src Clock source selection based on @ref hal_rcc_play1_clk_src_t
  * @param  divider Divider selection based on @ref hal_rcc_play1_clk_divider_t
  * @retval HAL_OK   Clock source and divider have been set
  */
hal_status_t HAL_RCC_PLAY1_SetConfigKernelClk(hal_rcc_play1_clk_src_t clk_src, hal_rcc_play1_clk_divider_t divider)
{
  ASSERT_DBG_PARAM(IS_RCC_PLAY1_CLK(clk_src));
  ASSERT_DBG_PARAM(IS_RCC_PLAY1_CLK_DIVIDER(divider));

  LL_RCC_ConfigPLAY1((uint32_t)clk_src, (uint32_t)divider);
  return HAL_OK;
}

#endif /* PLAY1 */

/**
  * @brief  Set the LPTIM1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_lptim1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPTIM1_SetKernelClkSource(hal_rcc_lptim1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPTIM1_CLK(clk_src));

  LL_RCC_SetLPTIMClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(XSPI1)
/**
  * @brief  Set the XSPI1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_xspi1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_XSPI1_SetKernelClkSource(hal_rcc_xspi1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_XSPI1_CLK(clk_src));

  LL_RCC_SetXSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* XSPI1 */

#if defined(UCPD1)
/**
  * @brief  Set the UCPD1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_ucpd1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_UCPD1_SetKernelClkSource(hal_rcc_ucpd1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_UCPD1_CLK(clk_src));

  LL_RCC_SetUCPDClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* UCPD1 */

#if defined(USB_DRD_FS)
/**
  * @brief  Set the USB clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_usb_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USB_SetKernelClkSource(hal_rcc_usb_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USB_CLK(clk_src));

  LL_RCC_SetUSBClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* USB_DRD_FS */

#if defined(I3C1)
/**
  * @brief  Set the I3C1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_i3c1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I3C1_SetKernelClkSource(hal_rcc_i3c1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I3C1_CLK(clk_src));

  LL_RCC_SetI3CClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* I3C1 */

/**
  * @brief  Set the I2C1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C1_SetKernelClkSource(hal_rcc_i2c1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C1_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the I2C2 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C2_SetKernelClkSource(hal_rcc_i2c2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C2_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(I2C3)
/**
  * @brief  Set the I2C3 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c3_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C3_SetKernelClkSource(hal_rcc_i2c3_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C3_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* I2C3 */

#if defined(I2C4)
/**
  * @brief  Set the I2C4 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c4_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C4_SetKernelClkSource(hal_rcc_i2c4_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C4_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* I2C4 */

/**
  * @brief  Set the ADC clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_adc_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_ADC_SetKernelClkSource(hal_rcc_adc_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ADC_CLK(clk_src));

  LL_RCC_SetADCClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the ADC clock prescaler.
  * @param  prescaler Prescaler selection based on @ref hal_rcc_adc_prescaler_t
  * @retval HAL_OK   Clock prescaler has been set
  */
hal_status_t HAL_RCC_ADC_SetKernelClkPrescaler(hal_rcc_adc_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_ADC_PRESCALER(prescaler));

  LL_RCC_SetADCPrescaler((uint32_t)prescaler);
  return HAL_OK;
}

/**
  * @brief  Configure the ADC clock.
  * @param  clk_src Clock source selection based on @ref hal_rcc_adc_clk_src_t
  * @param  prescaler Prescaler selection based on @ref hal_rcc_adc_prescaler_t
  * @retval HAL_OK   Clock prescaler has been set
  */
hal_status_t HAL_RCC_ADC_SetConfigKernelClk(hal_rcc_adc_clk_src_t clk_src, hal_rcc_adc_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_ADC_CLK(clk_src));
  ASSERT_DBG_PARAM(IS_RCC_ADC_PRESCALER(prescaler));

  LL_RCC_ConfigADC((uint32_t)clk_src, (uint32_t)prescaler);
  return HAL_OK;
}

/**
  * @brief  Set the FDCAN clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_fdcan_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_FDCAN_SetKernelClkSource(hal_rcc_fdcan_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_FDCAN_CLK(clk_src));

  LL_RCC_SetFDCANClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(POSENC1)
/**
  * @brief  Set the POSENC1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_posenc1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_POSENC1_SetKernelClkSource(hal_rcc_posenc1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_POSENC1_CLK(clk_src));

  LL_RCC_SetPOSENCClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* POSENC1 */

#if defined(POSENC2)
/**
  * @brief  Set the POSENC2 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_posenc2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_POSENC2_SetKernelClkSource(hal_rcc_posenc2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_POSENC2_CLK(clk_src));

  LL_RCC_SetPOSENCClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* POSENC2 */

/**
  * @brief  Set the RTC clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_rtc_clk_src_t
  * @warning Backup domain write access must be enabled before calling this function.
  * @warning Modifying the RTC clock source after it has been configured requires performing an RTC domain reset first.
  * @retval HAL_OK    RTC source clock has been selected
  */
hal_status_t HAL_RCC_RTC_SetKernelClkSource(hal_rcc_rtc_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_RTC_CLK(clk_src));

  /* Apply new RTC clock source selection */
  LL_RCC_SetRTCClockSource((uint32_t)clk_src);

  return HAL_OK;
}

/**
  * @brief  Get the USART1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_usart1_clk_src_t
  */
hal_rcc_usart1_clk_src_t HAL_RCC_USART1_GetKernelClkSource(void)
{
  return (hal_rcc_usart1_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART1_CLKSOURCE);
}

/**
  * @brief  Get the USART2 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_usart2_clk_src_t
  */
hal_rcc_usart2_clk_src_t HAL_RCC_USART2_GetKernelClkSource(void)
{
  return (hal_rcc_usart2_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART2_CLKSOURCE);
}

#if defined(USART3)
/**
  * @brief  Get the USART3 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_usart3_clk_src_t
  */
hal_rcc_usart3_clk_src_t HAL_RCC_USART3_GetKernelClkSource(void)
{
  return (hal_rcc_usart3_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART3_CLKSOURCE);
}
#endif /* USART3 */

/**
  * @brief  Get the UART4 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_uart4_clk_src_t
  */
hal_rcc_uart4_clk_src_t HAL_RCC_UART4_GetKernelClkSource(void)
{
  return (hal_rcc_uart4_clk_src_t)LL_RCC_GetUARTClockSource(LL_RCC_UART4_CLKSOURCE);
}

/**
  * @brief  Get the UART5 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_uart5_clk_src_t
  */
hal_rcc_uart5_clk_src_t HAL_RCC_UART5_GetKernelClkSource(void)
{
  return (hal_rcc_uart5_clk_src_t)LL_RCC_GetUARTClockSource(LL_RCC_UART5_CLKSOURCE);
}

/**
  * @brief  Get the UART6 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_uart6_clk_src_t
  */
hal_rcc_uart6_clk_src_t HAL_RCC_UART6_GetKernelClkSource(void)
{
  return (hal_rcc_uart6_clk_src_t)LL_RCC_GetUARTClockSource(LL_RCC_UART6_CLKSOURCE);
}

/**
  * @brief  Get the LPUART1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_lpuart1_clk_src_t
  */
hal_rcc_lpuart1_clk_src_t HAL_RCC_LPUART1_GetKernelClkSource(void)
{
  return (hal_rcc_lpuart1_clk_src_t)LL_RCC_GetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE);
}

/**
  * @brief  Get the DAC1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac1_clk_src_t
  */
hal_rcc_dac1_clk_src_t HAL_RCC_DAC1_GetKernelClkSource(void)
{
  return (hal_rcc_dac1_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC1_CLKSOURCE);
}

/**
  * @brief  Get the DAC2 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac2_clk_src_t
  */
hal_rcc_dac2_clk_src_t HAL_RCC_DAC2_GetKernelClkSource(void)
{
  return (hal_rcc_dac2_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC2_CLKSOURCE);
}

/**
  * @brief  Get the DAC5 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac5_clk_src_t
  */
hal_rcc_dac5_clk_src_t HAL_RCC_DAC5_GetKernelClkSource(void)
{
  return (hal_rcc_dac5_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC5_CLKSOURCE);
}

/**
  * @brief  Get the DAC6 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac6_clk_src_t
  */
hal_rcc_dac6_clk_src_t HAL_RCC_DAC6_GetKernelClkSource(void)
{
  return (hal_rcc_dac6_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC6_CLKSOURCE);
}

/**
  * @brief  Get the DAC7 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac7_clk_src_t
  */
hal_rcc_dac7_clk_src_t HAL_RCC_DAC7_GetKernelClkSource(void)
{
  return (hal_rcc_dac7_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC7_CLKSOURCE);
}

/**
  * @brief  Get the DAC8 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac8_clk_src_t
  */
hal_rcc_dac8_clk_src_t HAL_RCC_DAC8_GetKernelClkSource(void)
{
  return (hal_rcc_dac8_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC8_CLKSOURCE);
}

/**
  * @brief  Get the DAC9 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac9_clk_src_t
  */
hal_rcc_dac9_clk_src_t HAL_RCC_DAC9_GetKernelClkSource(void)
{
  return (hal_rcc_dac9_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC9_CLKSOURCE);
}

/**
  * @brief  Get the DAC10 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac10_clk_src_t
  */
hal_rcc_dac10_clk_src_t HAL_RCC_DAC10_GetKernelClkSource(void)
{
  return (hal_rcc_dac10_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC10_CLKSOURCE);
}

/**
  * @brief  Get the DAC1 sample and hold clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac1sh_clk_src_t
  */
hal_rcc_dac1sh_clk_src_t HAL_RCC_DAC1_GetSampleHoldClkSource(void)
{
  return (hal_rcc_dac1sh_clk_src_t)LL_RCC_GetDACSHClockSource(LL_RCC_DAC1SH_CLKSOURCE);
}

/**
  * @brief  Get the DAC2 sample and hold clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac2sh_clk_src_t
  */
hal_rcc_dac2sh_clk_src_t HAL_RCC_DAC2_GetSampleHoldClkSource(void)
{
  return (hal_rcc_dac2sh_clk_src_t)LL_RCC_GetDACSHClockSource(LL_RCC_DAC2SH_CLKSOURCE);
}

/**
  * @brief  Get the SPI1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_spi1_clk_src_t
  */
hal_rcc_spi1_clk_src_t HAL_RCC_SPI1_GetKernelClkSource(void)
{
  return (hal_rcc_spi1_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI1_CLKSOURCE);
}

/**
  * @brief  Get the SPI2 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_spi2_clk_src_t
  */
hal_rcc_spi2_clk_src_t HAL_RCC_SPI2_GetKernelClkSource(void)
{
  return (hal_rcc_spi2_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI2_CLKSOURCE);
}

#if defined(SPI3)
/**
  * @brief  Get the SPI3 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_spi3_clk_src_t
  */
hal_rcc_spi3_clk_src_t HAL_RCC_SPI3_GetKernelClkSource(void)
{
  return (hal_rcc_spi3_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI3_CLKSOURCE);
}
#endif /* SPI3 */

#if defined(PLAY1)
/**
  * @brief  Get the PLAY1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_play1_clk_src_t
  */
hal_rcc_play1_clk_src_t HAL_RCC_PLAY1_GetKernelClkSource(void)
{
  return (hal_rcc_play1_clk_src_t)LL_RCC_GetPLAYClockSource(LL_RCC_PLAY1_CLKSOURCE);
}

/**
  * @brief  Get the PLAY1 clock divider.
  * @retval clk_src Clock divider based on @ref hal_rcc_play1_clk_divider_t
  */
hal_rcc_play1_clk_divider_t HAL_RCC_PLAY1_GetKernelClkDivider(void)
{
  return (hal_rcc_play1_clk_divider_t)LL_RCC_GetPLAY1Divider();
}

/**
  * @brief Get the PLAY1 clock configuration.
  * @param p_clk_src Pointer on @ref hal_rcc_play1_clk_src_t
  * @param p_divider Pointer on @ref hal_rcc_play1_clk_divider_t
  */
void HAL_RCC_PLAY1_GetConfigKernelClk(hal_rcc_play1_clk_src_t *p_clk_src, hal_rcc_play1_clk_divider_t *p_divider)
{
  ASSERT_DBG_PARAM(p_clk_src != (void *)NULL);
  ASSERT_DBG_PARAM(p_divider != (void *)NULL);

  *p_clk_src = (hal_rcc_play1_clk_src_t)LL_RCC_GetPLAYClockSource(LL_RCC_PLAY1_CLKSOURCE);
  *p_divider = (hal_rcc_play1_clk_divider_t)LL_RCC_GetPLAY1Divider();
}
#endif /* PLAY1 */

/**
  * @brief  Get the LPTIM1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_lptim1_clk_src_t
  */
hal_rcc_lptim1_clk_src_t HAL_RCC_LPTIM1_GetKernelClkSource(void)
{
  return (hal_rcc_lptim1_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE);
}

#if defined(XSPI1)
/**
  * @brief  Get the XSPI1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_xspi1_clk_src_t
  */
hal_rcc_xspi1_clk_src_t HAL_RCC_XSPI1_GetKernelClkSource(void)
{
  return (hal_rcc_xspi1_clk_src_t)LL_RCC_GetXSPIClockSource(LL_RCC_XSPI1_CLKSOURCE);
}
#endif /* XSPI1 */

#if defined(UCPD1)
/**
  * @brief  Get the UCPD1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_ucpd1_clk_src_t
  */
hal_rcc_ucpd1_clk_src_t HAL_RCC_UCPD1_GetKernelClkSource(void)
{
  return (hal_rcc_ucpd1_clk_src_t)LL_RCC_GetUCPDClockSource(LL_RCC_UCPD1_CLKSOURCE);
}
#endif /* UCPD1 */

#if defined(USB_DRD_FS)
/**
  * @brief  Get the USB clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_usb_clk_src_t
  */
hal_rcc_usb_clk_src_t HAL_RCC_USB_GetKernelClkSource(void)
{
  return (hal_rcc_usb_clk_src_t)LL_RCC_GetUSBClockSource(LL_RCC_USB_CLKSOURCE);
}
#endif /* USB_DRD_FS */

#if defined(I3C1)
/**
  * @brief  Get the I3C1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_i3c1_clk_src_t
  */
hal_rcc_i3c1_clk_src_t HAL_RCC_I3C1_GetKernelClkSource(void)
{
  return (hal_rcc_i3c1_clk_src_t)LL_RCC_GetI3CClockSource(LL_RCC_I3C1_CLKSOURCE);
}
#endif /* I3C1 */

/**
  * @brief  Get the I2C1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_i2c1_clk_src_t
  */
hal_rcc_i2c1_clk_src_t HAL_RCC_I2C1_GetKernelClkSource(void)
{
  return (hal_rcc_i2c1_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C1_CLKSOURCE);
}

/**
  * @brief  Get the I2C2 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_i2c2_clk_src_t
  */
hal_rcc_i2c2_clk_src_t HAL_RCC_I2C2_GetKernelClkSource(void)
{
  return (hal_rcc_i2c2_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C2_CLKSOURCE);
}

#if defined(I2C3)
/**
  * @brief  Get the I2C3 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_i2c3_clk_src_t
  */
hal_rcc_i2c3_clk_src_t HAL_RCC_I2C3_GetKernelClkSource(void)
{
  return (hal_rcc_i2c3_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C3_CLKSOURCE);
}
#endif /* I2C3 */

#if defined(I2C4)
/**
  * @brief  Get the I2C4 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_i2c4_clk_src_t
  */
hal_rcc_i2c4_clk_src_t HAL_RCC_I2C4_GetKernelClkSource(void)
{
  return (hal_rcc_i2c4_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C4_CLKSOURCE);
}
#endif /* I2C4 */

/**
  * @brief  Get the ADC clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_adc_clk_src_t
  */
hal_rcc_adc_clk_src_t HAL_RCC_ADC_GetKernelClkSource(void)
{
  return (hal_rcc_adc_clk_src_t)LL_RCC_GetADCClockSource(LL_RCC_ADC_CLKSOURCE);
}

/**
  * @brief  Get the ADC prescaler.
  * @retval clk_src Clock source based on @ref hal_rcc_adc_prescaler_t
  */
hal_rcc_adc_prescaler_t HAL_RCC_ADC_GetKernelClkPrescaler(void)
{
  return (hal_rcc_adc_prescaler_t)LL_RCC_GetADCPrescaler();
}

/**
  * @brief Get the ADC clock configuration.
  * @param p_clk_src Pointer on @ref hal_rcc_adc_clk_src_t
  * @param p_prescaler Pointer on @ref hal_rcc_adc_prescaler_t
  */
void HAL_RCC_ADC_GetConfigKernelClk(hal_rcc_adc_clk_src_t *p_clk_src, hal_rcc_adc_prescaler_t *p_prescaler)
{
  ASSERT_DBG_PARAM(p_clk_src != (void *)NULL);
  ASSERT_DBG_PARAM(p_prescaler != (void *)NULL);

  *p_clk_src = (hal_rcc_adc_clk_src_t)LL_RCC_GetADCClockSource(LL_RCC_ADC_CLKSOURCE);
  *p_prescaler = (hal_rcc_adc_prescaler_t)LL_RCC_GetADCPrescaler();
}

/**
  * @brief  Get the FDCAN clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_fdcan_clk_src_t
  */
hal_rcc_fdcan_clk_src_t HAL_RCC_FDCAN_GetKernelClkSource(void)
{
  return (hal_rcc_fdcan_clk_src_t)LL_RCC_GetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE);
}

#if defined(POSENC1)
/**
  * @brief  Get the POSENC1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_posenc1_clk_src_t
  */
hal_rcc_posenc1_clk_src_t HAL_RCC_POSENC1_GetKernelClkSource(void)
{
  return (hal_rcc_posenc1_clk_src_t)LL_RCC_GetPOSENCClockSource(LL_RCC_POSENC1_CLKSOURCE);
}
#endif /* POSENC1 */

#if defined(POSENC2)
/**
  * @brief  Get the POSENC2 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_posenc2_clk_src_t
  */
hal_rcc_posenc2_clk_src_t HAL_RCC_POSENC2_GetKernelClkSource(void)
{
  return (hal_rcc_posenc2_clk_src_t)LL_RCC_GetPOSENCClockSource(LL_RCC_POSENC2_CLKSOURCE);
}
#endif /* POSENC2 */

/**
  * @brief  Get the RTC clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_rtc_clk_src_t
  */
hal_rcc_rtc_clk_src_t HAL_RCC_RTC_GetKernelClkSource(void)
{
  return (hal_rcc_rtc_clk_src_t)LL_RCC_GetRTCClockSource();
}

#if defined(HRTIM1)
/**
  * @brief  Return the peripheral clock frequency for HRTIM.
  * @param  hrtimx HRTIM instance
  * @retval uint32_t Frequency in Hz
  */
uint32_t HAL_RCC_HRTIM_GetKernelClkFreq(const HRTIM_TypeDef *hrtimx)
{
  STM32_UNUSED(hrtimx);
  return HAL_RCC_HRTIM1_GetKernelClkFreq();
}
#endif /* HRTIM1 */

/**
  * @brief  Return the peripheral clock frequency for HRTIM1.
  * @retval uint32_t Frequency in Hz
  */
uint32_t HAL_RCC_HRTIM1_GetKernelClkFreq(void)
{
  uint32_t frequency = HAL_RCC_GetPCLK2Freq();
  uint32_t mult_ratio = (uint32_t)APBPrescTable[LL_RCC_GetAPB2Prescaler() >> RCC_CFGR2_PPRE2_Pos]
                        + (uint32_t)AHBPrescTable[LL_RCC_GetAHBPrescaler()];
  if (mult_ratio > 5U)
  {
    mult_ratio = 5U;
  }

  frequency = frequency << mult_ratio;

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USART.
  * @param  usartx USART instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_USART_GetKernelClkFreq(const USART_TypeDef *usartx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)usartx)
  {
    case (uint32_t)USART1:
      frequency = HAL_RCC_USART1_GetKernelClkFreq();
      break;
    case (uint32_t)USART2:
      frequency = HAL_RCC_USART2_GetKernelClkFreq();
      break;
#if defined(USART3)
    case (uint32_t)USART3:
      frequency = HAL_RCC_USART3_GetKernelClkFreq();
      break;
#endif /* (USART3 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USART1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART1_CLKSOURCE);
#if defined(PLL2)
  hal_rcc_pll_output_freq_t pll_clocks;
#endif /* PLL2 */

  switch (srcclk)
  {
    case LL_RCC_USART1_CLKSOURCE_PCLK2:
      frequency = HAL_RCC_GetPCLK2Freq();
      break;
    case LL_RCC_USART1_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
#if defined(PLL2)
    case LL_RCC_USART1_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
#if defined(HSE_VALUE)
    case LL_RCC_USART1_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_USART1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(LSE_VALUE)
    case LL_RCC_USART1_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USART2.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART2_CLKSOURCE);
#if defined(PLL2)
  hal_rcc_pll_output_freq_t pll_clocks;
#endif /* PLL2 */

  switch (srcclk)
  {
    case LL_RCC_USART2_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;
    case LL_RCC_USART2_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
#if defined(PLL2)
    case LL_RCC_USART2_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
#if defined(HSE_VALUE)
    case LL_RCC_USART2_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_USART2_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(LSE_VALUE)
    case LL_RCC_USART2_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    default:
      break;
  }
  return frequency;
}

#if defined(USART3)
/**
  * @brief  Return the peripheral clock frequency for USART3.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART3_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART3_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_USART3_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;
    case LL_RCC_USART3_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
    case LL_RCC_USART3_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(HSE_VALUE)
    case LL_RCC_USART3_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_USART3_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(LSE_VALUE)
    case LL_RCC_USART3_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    default:
      break;
  }
  return frequency;
}
#endif /* USART3 */

/**
  * @brief  Return the peripheral clock frequency for UART.
  * @param  uartx UART instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_UART_GetKernelClkFreq(const USART_TypeDef *uartx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)uartx)
  {
    case (uint32_t)USART1:
      frequency = HAL_RCC_USART1_GetKernelClkFreq();
      break;
    case (uint32_t)USART2:
      frequency = HAL_RCC_USART2_GetKernelClkFreq();
      break;
#if defined(USART3)
    case (uint32_t)USART3:
      frequency = HAL_RCC_USART3_GetKernelClkFreq();
      break;
#endif /* USART3 */
    case (uint32_t)UART4:
      frequency = HAL_RCC_UART4_GetKernelClkFreq();
      break;
    case (uint32_t)UART5:
      frequency = HAL_RCC_UART5_GetKernelClkFreq();
      break;
    case (uint32_t)UART6:
      frequency = HAL_RCC_UART6_GetKernelClkFreq();
      break;
    case (uint32_t)LPUART1:
      frequency = HAL_RCC_LPUART1_GetKernelClkFreq();
      break;
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for UART4.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART4_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_UART4_CLKSOURCE);
#if defined(PLL2)
  hal_rcc_pll_output_freq_t pll_clocks;
#endif /* PLL2 */

  switch (srcclk)
  {
    case LL_RCC_UART4_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;
    case LL_RCC_UART4_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
#if defined(PLL2)
    case LL_RCC_UART4_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
#if defined(HSE_VALUE)
    case LL_RCC_UART4_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_UART4_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(LSE_VALUE)
    case LL_RCC_UART4_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for UART5.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART5_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_UART5_CLKSOURCE);
#if defined(PLL2)
  hal_rcc_pll_output_freq_t pll_clocks;
#endif /* PLL2 */

  switch (srcclk)
  {
    case LL_RCC_UART5_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;
    case LL_RCC_UART5_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
#if defined(PLL2)
    case LL_RCC_UART5_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
#if defined(HSE_VALUE)
    case LL_RCC_UART5_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_UART5_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(LSE_VALUE)
    case LL_RCC_UART5_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for UART6.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART6_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_UART6_CLKSOURCE);
#if defined(PLL2)
  hal_rcc_pll_output_freq_t pll_clocks;
#endif /* PLL2 */

  switch (srcclk)
  {
    case LL_RCC_UART6_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;
    case LL_RCC_UART6_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
#if defined(PLL2)
    case LL_RCC_UART6_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
#if defined(HSE_VALUE)
    case LL_RCC_UART6_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_UART6_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(LSE_VALUE)
    case LL_RCC_UART6_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPUART1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPUART1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE);
#if defined(PLL2)
  hal_rcc_pll_output_freq_t pll_clocks;
#endif /* PLL2 */

  switch (srcclk)
  {
    case LL_RCC_LPUART1_CLKSOURCE_PCLK3:
      frequency = HAL_RCC_GetPCLK3Freq();
      break;
    case LL_RCC_LPUART1_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
#if defined(PLL2)
    case LL_RCC_LPUART1_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
#if defined(HSE_VALUE)
    case LL_RCC_LPUART1_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_LPUART1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(LSE_VALUE)
    case LL_RCC_LPUART1_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC.
  * @param  dacx DAC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_DAC_GetKernelClkFreq(const DAC_TypeDef *dacx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)dacx)
  {
    case (uint32_t)DAC1:
      frequency = HAL_RCC_DAC1_GetKernelClkFreq();
      break;
    case (uint32_t)DAC2:
      frequency = HAL_RCC_DAC2_GetKernelClkFreq();
      break;
    case (uint32_t)DAC5:
      frequency = HAL_RCC_DAC5_GetKernelClkFreq();
      break;
    case (uint32_t)DAC6:
      frequency = HAL_RCC_DAC6_GetKernelClkFreq();
      break;
    case (uint32_t)DAC7:
      frequency = HAL_RCC_DAC7_GetKernelClkFreq();
      break;
    case (uint32_t)DAC8:
      frequency = HAL_RCC_DAC8_GetKernelClkFreq();
      break;
    case (uint32_t)DAC9:
      frequency = HAL_RCC_DAC9_GetKernelClkFreq();
      break;
    case (uint32_t)DAC10:
      frequency = HAL_RCC_DAC10_GetKernelClkFreq();
      break;
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC1_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_DAC1_CLKSOURCE_TIM:
      frequency = HAL_RCC_GetHCLKFreq();
      break;
    case LL_RCC_DAC1_CLKSOURCE_HRTIM:
      frequency = HAL_RCC_HRTIM1_GetKernelClkFreq();
      break;
    case LL_RCC_DAC1_CLKSOURCE_ADC:
      frequency = RCC_ADC_GetKernelClkFreq();
      break;
#if defined(HSE_VALUE)
    case LL_RCC_DAC1_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_DAC1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    case LL_RCC_DAC1_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_DAC1_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC2.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC2_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_DAC2_CLKSOURCE_TIM:
      frequency = HAL_RCC_GetHCLKFreq();
      break;
    case LL_RCC_DAC2_CLKSOURCE_HRTIM:
      frequency = HAL_RCC_HRTIM1_GetKernelClkFreq();
      break;
    case LL_RCC_DAC2_CLKSOURCE_ADC:
      frequency = RCC_ADC_GetKernelClkFreq();
      break;
#if defined(HSE_VALUE)
    case LL_RCC_DAC2_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_DAC2_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    case LL_RCC_DAC2_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_DAC2_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC5.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC5_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC5_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_DAC5_CLKSOURCE_TIM:
      frequency = HAL_RCC_GetHCLKFreq();
      break;
    case LL_RCC_DAC5_CLKSOURCE_HRTIM:
      frequency = HAL_RCC_HRTIM1_GetKernelClkFreq();
      break;
    case LL_RCC_DAC5_CLKSOURCE_ADC:
      frequency = RCC_ADC_GetKernelClkFreq();
      break;
#if defined(HSE_VALUE)
    case LL_RCC_DAC5_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_DAC5_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    case LL_RCC_DAC5_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_DAC5_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC6.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC6_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC6_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_DAC6_CLKSOURCE_TIM:
      frequency = HAL_RCC_GetHCLKFreq();
      break;
    case LL_RCC_DAC6_CLKSOURCE_HRTIM:
      frequency = HAL_RCC_HRTIM1_GetKernelClkFreq();
      break;
    case LL_RCC_DAC6_CLKSOURCE_ADC:
      frequency = RCC_ADC_GetKernelClkFreq();
      break;
#if defined(HSE_VALUE)
    case LL_RCC_DAC6_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_DAC6_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    case LL_RCC_DAC6_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_DAC6_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC7.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC7_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC7_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_DAC7_CLKSOURCE_TIM:
      frequency = HAL_RCC_GetHCLKFreq();
      break;
    case LL_RCC_DAC7_CLKSOURCE_HRTIM:
      frequency = HAL_RCC_HRTIM1_GetKernelClkFreq();
      break;
    case LL_RCC_DAC7_CLKSOURCE_ADC:
      frequency = RCC_ADC_GetKernelClkFreq();
      break;
#if defined(HSE_VALUE)
    case LL_RCC_DAC7_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_DAC7_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    case LL_RCC_DAC7_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_DAC7_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC8.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC8_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC8_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_DAC8_CLKSOURCE_TIM:
      frequency = HAL_RCC_GetHCLKFreq();
      break;
    case LL_RCC_DAC8_CLKSOURCE_HRTIM:
      frequency = HAL_RCC_HRTIM1_GetKernelClkFreq();
      break;
    case LL_RCC_DAC8_CLKSOURCE_ADC:
      frequency = RCC_ADC_GetKernelClkFreq();
      break;
#if defined(HSE_VALUE)
    case LL_RCC_DAC8_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_DAC8_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    case LL_RCC_DAC8_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_DAC8_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC9.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC9_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC9_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_DAC9_CLKSOURCE_TIM:
      frequency = HAL_RCC_GetHCLKFreq();
      break;
    case LL_RCC_DAC9_CLKSOURCE_HRTIM:
      frequency = HAL_RCC_HRTIM1_GetKernelClkFreq();
      break;
    case LL_RCC_DAC9_CLKSOURCE_ADC:
      frequency = RCC_ADC_GetKernelClkFreq();
      break;
#if defined(HSE_VALUE)
    case LL_RCC_DAC9_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_DAC9_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    case LL_RCC_DAC9_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_DAC9_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC10.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC10_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC10_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_DAC10_CLKSOURCE_TIM:
      frequency = HAL_RCC_GetHCLKFreq();
      break;
    case LL_RCC_DAC10_CLKSOURCE_HRTIM:
      frequency = HAL_RCC_HRTIM1_GetKernelClkFreq();
      break;
    case LL_RCC_DAC10_CLKSOURCE_ADC:
      frequency = RCC_ADC_GetKernelClkFreq();
      break;
#if defined(HSE_VALUE)
    case LL_RCC_DAC10_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_DAC10_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    case LL_RCC_DAC10_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_DAC10_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DACSH.
  * @param  dacshx DACSH instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_DAC_GetSampleHoldClkFreq(const DAC_TypeDef *dacshx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)dacshx)
  {
    case (uint32_t)DAC1:
      frequency = HAL_RCC_DAC1_GetSampleHoldClkFreq();
      break;
    case (uint32_t)DAC2:
      frequency = HAL_RCC_DAC2_GetSampleHoldClkFreq();
      break;
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC1 sample and hold.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC1_GetSampleHoldClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACSHClockSource(LL_RCC_DAC1SH_CLKSOURCE);

  switch (srcclk)
  {
#if defined(LSE_VALUE)
    case LL_RCC_DAC1SH_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    case LL_RCC_DAC1SH_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC2 sample and hold.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC2_GetSampleHoldClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACSHClockSource(LL_RCC_DAC2SH_CLKSOURCE);

  switch (srcclk)
  {
#if defined(LSE_VALUE)
    case LL_RCC_DAC2SH_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    case LL_RCC_DAC2SH_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI.
  * @param  spix SPI instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_SPI_GetKernelClkFreq(const SPI_TypeDef *spix)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)spix)
  {
    case (uint32_t)SPI1:
      frequency = HAL_RCC_SPI1_GetKernelClkFreq();
      break;
    case (uint32_t)SPI2:
      frequency = HAL_RCC_SPI2_GetKernelClkFreq();
      break;
#if defined(SPI3)
    case (uint32_t)SPI3:
      frequency = HAL_RCC_SPI3_GetKernelClkFreq();
      break;
#endif /* SPI3 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI1_CLKSOURCE);
#if defined(PLL2)
  hal_rcc_pll_output_freq_t pll_clocks;
#endif /* PLL2 */

  switch (srcclk)
  {
    case LL_RCC_SPI1_CLKSOURCE_PCLK2:
      frequency = HAL_RCC_GetPCLK2Freq();
      break;
    case LL_RCC_SPI1_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
#if defined(PLL2)
    case LL_RCC_SPI1_CLKSOURCE_PLL2P:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;
#endif /* PLL2 */
#if defined(HSE_VALUE)
    case LL_RCC_SPI1_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_SPI1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(AUDIO_CLOCK_VALUE)
    case LL_RCC_SPI1_CLKSOURCE_AUDIOCLK:
      frequency = AUDIO_CLOCK_VALUE;
      break;
#endif /* AUDIO_CLOCK_VALUE */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI2.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI2_CLKSOURCE);
#if defined(PLL2)
  hal_rcc_pll_output_freq_t pll_clocks;
#endif /* PLL2 */

  switch (srcclk)
  {
    case LL_RCC_SPI2_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;
    case LL_RCC_SPI2_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
#if defined(PLL2)
    case LL_RCC_SPI2_CLKSOURCE_PLL2P:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;
#endif /* PLL2 */
#if defined(HSE_VALUE)
    case LL_RCC_SPI2_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_SPI2_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(AUDIO_CLOCK_VALUE)
    case LL_RCC_SPI2_CLKSOURCE_AUDIOCLK:
      frequency = AUDIO_CLOCK_VALUE;
      break;
#endif /* AUDIO_CLOCK_VALUE */
    default:
      break;
  }
  return frequency;
}

#if defined(SPI3)
/**
  * @brief  Return the peripheral clock frequency for SPI3.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI3_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI3_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_SPI3_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;
    case LL_RCC_SPI3_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
    case LL_RCC_SPI3_CLKSOURCE_PLL2P:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;
#if defined(HSE_VALUE)
    case LL_RCC_SPI3_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_SPI3_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    default:
      break;
  }
  return frequency;
}
#endif /* SPI3 */

#if defined(PLAY1)
/**
  * @brief  Return the peripheral clock frequency for PLAY.
  * @param  playx PLAY instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_PLAY_GetKernelClkFreq(const PLAY_TypeDef *playx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)playx)
  {
    case (uint32_t)PLAY1:
      frequency = HAL_RCC_PLAY1_GetKernelClkFreq();
      break;
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for PLAY1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_PLAY1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetPLAYClockSource(LL_RCC_PLAY1_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
#if defined(LSE_VALUE)
    case LL_RCC_PLAY1_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    case LL_RCC_PLAY1_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;
    case LL_RCC_PLAY1_CLKSOURCE_PLL2P:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;
#if defined(HSE_VALUE)
    case LL_RCC_PLAY1_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_PLAY1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    case LL_RCC_PLAY1_CLKSOURCE_HSI48:
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        frequency = HSI48_VALUE;
      }
      break;
    default:
      break;
  }

  frequency = frequency / (uint32_t)RCC_GET_PLAY1_DIVIDER();

  return frequency;
}
#endif /* PLAY1 */

/**
  * @brief  Return the peripheral clock frequency for TIM.
  * @param  timx TIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_TIM_GetKernelClkFreq(const TIM_TypeDef *timx)
{
  STM32_UNUSED(timx);
  return  HAL_RCC_GetHCLKFreq();
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM.
  * @param  lptimx LPTIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPTIM_GetKernelClkFreq(const LPTIM_TypeDef *lptimx)
{
  uint32_t frequency = 0;

  switch ((uint32_t)lptimx)
  {
    case (uint32_t)LPTIM1:
      frequency = HAL_RCC_LPTIM1_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPTIM1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_LPTIM1_CLKSOURCE_PCLK3:
      frequency = HAL_RCC_GetPCLK3Freq();
      break;
    case LL_RCC_LPTIM1_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_LPTIM1_CLKSOURCE_PLL2P:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;
#endif /* PLL2 */
#if defined(HSE_VALUE)
    case LL_RCC_LPTIM1_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_LPTIM1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    case LL_RCC_LPTIM1_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;
#if defined(LSE_VALUE)
    case LL_RCC_LPTIM1_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    default:
      break;
  }
  return frequency;
}

#if defined(XSPI1)
/**
  * @brief  Return the peripheral clock frequency for XSPI.
  * @param  xspix XSPI instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_XSPI_GetKernelClkFreq(const XSPI_TypeDef *xspix)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)xspix)
  {
    case (uint32_t)XSPI1:
      frequency = HAL_RCC_XSPI1_GetKernelClkFreq();
      break;
    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for XSPI1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_XSPI1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetXSPIClockSource(LL_RCC_XSPI1_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_XSPI1_CLKSOURCE_HCLK4:
      frequency = HAL_RCC_GetHCLKFreq();
      break;
    case LL_RCC_XSPI1_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
    case LL_RCC_XSPI1_CLKSOURCE_ICLK2:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK2);
      break;
#if defined(HSE_VALUE)
    case LL_RCC_XSPI1_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_XSPI1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
    default:
      break;
  }
  return frequency;
}
#endif /* XSPI1 */

#if defined(UCPD1)
/**
  * @brief  Return the peripheral clock frequency for UCPD.
  * @param  ucpdx UCPD instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_UCPD_GetKernelClkFreq(const UCPD_TypeDef *ucpdx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)ucpdx)
  {
    case (uint32_t)UCPD1:
      frequency = HAL_RCC_UCPD1_GetKernelClkFreq();
      break;
    default:
      break;
  }

  return frequency;
}


/**
  * @brief  Return the peripheral clock frequency for UCPD1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UCPD1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUCPDClockSource(LL_RCC_UCPD1_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_UCPD1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(HSE_VALUE)
    case LL_RCC_UCPD1_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_UCPD1_CLKSOURCE_HSI48:
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        frequency = HSI48_VALUE;
      }
      break;
    case LL_RCC_UCPD1_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
    default:
      break;
  }
  return frequency;
}
#endif /* UCPD1 */

#if defined(USB_DRD_FS)
/**
  * @brief  Return the peripheral clock frequency for USBFS.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USB_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSBClockSource(LL_RCC_USB_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_USB_CLKSOURCE_HSI48:
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        frequency = HSI48_VALUE;
      }
      break;
#if defined(HSE_VALUE)
    case LL_RCC_USB_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_USB_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_USB_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
    default:
      break;
  }
  return frequency;
}
#endif /* USB_DRD_FS */

#if defined(I3C1)
/**
  * @brief  Return the peripheral clock frequency for I3C.
  * @param  i3cx I3C instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I3C_GetKernelClkFreq(const I3C_TypeDef *i3cx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)i3cx)
  {
    case (uint32_t)I3C1:
      frequency = HAL_RCC_I3C1_GetKernelClkFreq();
      break;
    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I3C1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I3C1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI3CClockSource(LL_RCC_I3C1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I3C1_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;
    case LL_RCC_I3C1_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
    case LL_RCC_I3C1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(HSE_VALUE)
    case LL_RCC_I3C1_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    default:
      break;
  }
  return frequency;
}
#endif /* I3C1 */

/**
  * @brief  Return the peripheral clock frequency for I2C.
  * @param  i2cx I2C instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I2C_GetKernelClkFreq(const I2C_TypeDef *i2cx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)i2cx)
  {
    case (uint32_t)I2C1:
      frequency = HAL_RCC_I2C1_GetKernelClkFreq();
      break;
    case (uint32_t)I2C2:
      frequency = HAL_RCC_I2C2_GetKernelClkFreq();
      break;
#if defined(I2C3)
    case (uint32_t)I2C3:
      frequency = HAL_RCC_I2C3_GetKernelClkFreq();
      break;
#endif /* I2C3 */
#if defined(I2C4)
    case (uint32_t)I2C4:
      frequency = HAL_RCC_I2C4_GetKernelClkFreq();
      break;
#endif /* I2C4 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I2C1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I2C1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C1_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;
    case LL_RCC_I2C1_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
    case LL_RCC_I2C1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(HSE_VALUE)
    case LL_RCC_I2C1_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I2C2.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I2C2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C2_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C2_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;
    case LL_RCC_I2C2_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
    case LL_RCC_I2C2_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(HSE_VALUE)
    case LL_RCC_I2C2_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    default:
      break;
  }
  return frequency;
}

#if defined(I2C3)
/**
  * @brief  Return the peripheral clock frequency for I2C3.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I2C3_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C3_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C3_CLKSOURCE_PCLK3:
      frequency = HAL_RCC_GetPCLK3Freq();
      break;
    case LL_RCC_I2C3_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
    case LL_RCC_I2C3_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(HSE_VALUE)
    case LL_RCC_I2C3_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_I2C3_CLKSOURCE_HSI48:
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        frequency = HSI48_VALUE;
      }
      break;
    default:
      break;
  }
  return frequency;
}
#endif /* I2C3 */

#if defined(I2C4)
/**
  * @brief  Return the peripheral clock frequency for I2C4.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I2C4_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C4_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C4_CLKSOURCE_PCLK3:
      frequency = HAL_RCC_GetPCLK3Freq();
      break;
    case LL_RCC_I2C4_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
    case LL_RCC_I2C4_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(HSE_VALUE)
    case LL_RCC_I2C4_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_I2C4_CLKSOURCE_HSI48:
      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        frequency = HSI48_VALUE;
      }
      break;
    default:
      break;
  }
  return frequency;
}
#endif /* I2C4 */

/**
  * @brief  Return the peripheral clock frequency for ADC.
  * @param  adcx ADC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ADC_GetKernelClkFreq(const ADC_TypeDef *adcx)
{
  uint32_t frequency = 0U;
  switch ((uint32_t)adcx)
  {
    case (uint32_t)ADC1:
      frequency = HAL_RCC_ADC12_GetKernelClkFreq();
      break;
    case (uint32_t)ADC2:
      frequency = HAL_RCC_ADC12_GetKernelClkFreq();
      break;
#if defined(ADC3)
    case (uint32_t)ADC3:
      frequency = HAL_RCC_ADC3_GetKernelClkFreq();
      break;
#endif /* ADC3 */
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for ADC12.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ADC12_GetKernelClkFreq(void)
{
  return RCC_ADC_GetKernelClkFreq();
}

#if defined(ADC3)
/**
  * @brief  Return the peripheral clock frequency for ADC3.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ADC3_GetKernelClkFreq(void)
{
  return RCC_ADC_GetKernelClkFreq();
}
#endif /* ADC3 */

/**
  * @brief  Return the peripheral clock frequency for FDCAN.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_FDCAN_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
#if defined(HSE_VALUE)
    case LL_RCC_FDCAN_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_FDCAN_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#if defined(PLL2)
    case LL_RCC_FDCAN_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
#endif /* PLL2 */
    default:
      break;
  }
  return frequency;
}

#if defined(POSENC1) || defined(POSENC2)
/**
  * @brief  Return the peripheral clock frequency for POSENC.
  * @param  posencx POSENC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_POSENC_GetKernelClkFreq(const POSENC_TypeDef *posencx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)posencx)
  {
#if defined(POSENC1)
    case (uint32_t)POSENC1:
      frequency = HAL_RCC_POSENC1_GetKernelClkFreq();
      break;
#endif /* POSENC1 */
#if defined(POSENC2)
    case (uint32_t)POSENC2:
      frequency = HAL_RCC_POSENC2_GetKernelClkFreq();
      break;
#endif /* POSENC2 */
    default:
      break;
  }
  return frequency;
}
#endif /* POSENC1 || POSENC2 */

#if defined(POSENC1)
/**
  * @brief  Return the peripheral clock frequency for POSENC1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_POSENC1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetPOSENCClockSource(LL_RCC_POSENC1_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_POSENC1_CLKSOURCE_PLL1P:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;
    case LL_RCC_POSENC1_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
    case LL_RCC_POSENC1_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
    case LL_RCC_POSENC1_CLKSOURCE_PLL2P:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;
    case LL_RCC_POSENC1_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
    case LL_RCC_POSENC1_CLKSOURCE_ICLK2:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK2);
      break;
    default:
      break;
  }
  return frequency;
}
#endif /* POSENC1 */

#if defined(POSENC2)
/**
  * @brief  Return the peripheral clock frequency for POSENC2.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_POSENC2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetPOSENCClockSource(LL_RCC_POSENC2_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_POSENC2_CLKSOURCE_PLL1P:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;
    case LL_RCC_POSENC2_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
    case LL_RCC_POSENC2_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
    case LL_RCC_POSENC2_CLKSOURCE_PLL2P:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;
    case LL_RCC_POSENC2_CLKSOURCE_PLL2Q:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
    case LL_RCC_POSENC2_CLKSOURCE_ICLK2:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK2);
      break;
    default:
      break;
  }
  return frequency;
}
#endif /* POSENC2 */

/**
  * @brief  Return the peripheral clock frequency for COMP.
  * @param  compx COMP instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_COMP_GetKernelClkFreq(const COMP_TypeDef *compx)
{
  STM32_UNUSED(compx);
  return HAL_RCC_GetPCLK3Freq();
}

/**
  * @brief  Return the peripheral clock frequency for RTC.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_RTC_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetRTCClockSource();

  switch (srcclk)
  {
#if defined(LSE_VALUE)
    case LL_RCC_RTC_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */
    case LL_RCC_RTC_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;
#if defined(HSE_VALUE)
    case LL_RCC_RTC_CLKSOURCE_HSE_DIV:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        uint32_t Prescaler = LL_RCC_GetRTC_HSEPrescaler();
        if (Prescaler > 1U)
        {
          frequency = HSE_VALUE / Prescaler;
        }
      }
      break;
#endif /* HSE_VALUE */
    default:
      break;
  }

  return frequency;
}

/**
  * @}
  */


/** @addtogroup RCC_Exported_Functions_Group5 RCC security and privileged access levels attributes management
  * This subsection provides a set of functions:
  * @{
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the security access level attribute for item(s).
  * @param  item This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_RCC_SEC_ITEM_HSI
  *         @arg @ref HAL_RCC_SEC_ITEM_HSE
  *         @arg @ref HAL_RCC_SEC_ITEM_LSI
  *         @arg @ref HAL_RCC_SEC_ITEM_LSE
  *         @arg @ref HAL_RCC_SEC_ITEM_SYSCLK
  *         @arg @ref HAL_RCC_SEC_ITEM_PRESCALERS
  *         @arg @ref HAL_RCC_SEC_ITEM_PLL1
  *         @arg @ref HAL_RCC_SEC_ITEM_PLL2 (*)
  *         @arg @ref HAL_RCC_SEC_ITEM_HSI48 (*)
  *         @arg @ref HAL_RCC_SEC_ITEM_RESET_FLAGS
  *         @arg @ref HAL_RCC_SEC_ITEM_ALL
  *
  *        (*) value not defined in all devices.
  * @param  sec_attr This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_SEC
  *         @arg @ref HAL_RCC_NSEC
  * @note   Only available from secure and privileged state.
  * @retval HAL_OK      Security attribute has been set successfully
  * @retval HAL_ERROR   Non-privileged write to a privileged-only register
  */
hal_status_t HAL_RCC_SetSecAttr(uint32_t item, hal_rcc_sec_attr_t sec_attr)
{
  ASSERT_DBG_PARAM(IS_RCC_SEC_ITEM(item));
  ASSERT_DBG_PARAM(IS_RCC_SEC_ATTR(sec_attr));

  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_SetSecAttr(item, (uint32_t)sec_attr);

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the security access level attribute of an item.
  * @param  item This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_SEC_ITEM_HSI
  *         @arg @ref HAL_RCC_SEC_ITEM_HSE
  *         @arg @ref HAL_RCC_SEC_ITEM_LSI
  *         @arg @ref HAL_RCC_SEC_ITEM_LSE
  *         @arg @ref HAL_RCC_SEC_ITEM_SYSCLK
  *         @arg @ref HAL_RCC_SEC_ITEM_PRESCALERS
  *         @arg @ref HAL_RCC_SEC_ITEM_PLL1
  *         @arg @ref HAL_RCC_SEC_ITEM_PLL2 (*)
  *         @arg @ref HAL_RCC_SEC_ITEM_HSI48 (*)
  *         @arg @ref HAL_RCC_SEC_ITEM_RESET_FLAGS
  *
  *        (*) value not defined in all devices.
  * @retval The returned value can be one of the following values:
  *         @arg @ref HAL_RCC_SEC
  *         @arg @ref HAL_RCC_NSEC
  */
hal_rcc_sec_attr_t HAL_RCC_GetSecAttr(uint32_t item)
{
  ASSERT_DBG_PARAM(IS_RCC_SEC_SINGLE_ITEM(item));

  return ((hal_rcc_sec_attr_t)LL_RCC_GetSecAttr(item));
}

/**
  * @brief  Set the privileged access level attribute for item(s).
  * @param  item This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_RCC_PRIV_ITEM_SPRIV
  *         @arg @ref HAL_RCC_PRIV_ITEM_NSPRIV
  *         @arg @ref HAL_RCC_PRIV_ITEM_ALL
  * @param  priv_attr This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_PRIV
  *         @arg @ref HAL_RCC_NPRIV
  * @note   If an item is secured, its privilege attribute can be configured by secure and privileged accesses.
  *         If an item is not secured, its privilege attribute can be configured by privileged, secure
  *         or nonsecure access.
  * @retval HAL_OK      Privileged attribute has been set successfully
  * @retval HAL_ERROR   Non-privileged write to a privileged-only register
  */
hal_status_t HAL_RCC_SetPrivAttr(uint32_t item, hal_rcc_priv_attr_t priv_attr)
{
  ASSERT_DBG_PARAM(IS_RCC_PRIV_ITEM(item));
  ASSERT_DBG_PARAM(IS_RCC_PRIV_ATTR(priv_attr));

  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_SetPrivAttr(item, (uint32_t) priv_attr);

  return HAL_OK;
}

/**
  * @brief  Get the privileged access level attribute of an item.
  * @param  item This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_PRIV_ITEM_SPRIV
  *         @arg @ref HAL_RCC_PRIV_ITEM_NSPRIV
  * @retval The returned value can be one of the following values:
  *         @arg @ref HAL_RCC_PRIV
  *         @arg @ref HAL_RCC_NPRIV
  */
hal_rcc_priv_attr_t HAL_RCC_GetPrivAttr(uint32_t item)
{
  ASSERT_DBG_PARAM(IS_RCC_PRIV_SINGLE_ITEM(item));

  return ((hal_rcc_priv_attr_t)LL_RCC_GetPrivAttr(item));
}

/**
  * @}
  */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @addtogroup RCC_Private_Functions
  * @{
  */
/** @brief  Wait for clock timeout.
  * @param  p_timeout_cb Callback on the timeout function
  * @param  timeout      Timeout value
  * @param  status       Status to be checked
  * @retval HAL_OK       Not timeout detected
  * @retval HAL_ERROR    Timeout detected during clock activation or deactivation
  */
static hal_status_t RCC_WaitForTimeout(const rcc_cb_timeout_t p_timeout_cb, uint32_t timeout, uint32_t status)
{
  uint32_t tickstart;
  hal_status_t hal_status = HAL_OK;
  tickstart = HAL_GetTick();

  while (p_timeout_cb() != status)
  {
    if ((HAL_GetTick() - tickstart) > timeout)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (p_timeout_cb() != status)
      {
        hal_status = HAL_ERROR;
        break;
      }
    }
  }

  return hal_status;
}

/**
  * @brief Return the HSI clock Frequency.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
static uint32_t RCC_HSI_GetClockFreq(void)
{
  return (HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos));
}

/**
  * @brief  Return the iclkx clock frequency.
  * @param  iclkx  iclk instance, can be one of the values defined in hal_rcc_iclk_t
  * @retval uint32_t Frequency in Hz
  */
static uint32_t RCC_ICLK_GetClockFreq(hal_rcc_iclk_t  iclkx)
{
  uint32_t frequency = 0U;
  hal_rcc_pll_output_freq_t pll_clocks;
  switch (iclkx)
  {
    case HAL_RCC_ICLK1:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      break;
#if defined(PLL2)
    case HAL_RCC_ICLK2:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      break;
#endif /* PLL2 */
    default:
      pll_clocks.pll_r_freq = 0U;
      break;
  }

  if (LL_RCC_ICLK_GetDivider((uint32_t)iclkx) == LL_RCC_ICLK_DIV_3)
  {
    frequency = pll_clocks.pll_r_freq / 3U;
  }
  else
  {
    frequency = pll_clocks.pll_r_freq / 5U;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for ADC.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
static uint32_t RCC_ADC_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetADCClockSource(LL_RCC_ADC_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_ADC_CLKSOURCE_TIM:
      frequency = HAL_RCC_GetHCLKFreq();
      break;
    case LL_RCC_ADC_CLKSOURCE_HRTIM:
      frequency = HAL_RCC_HRTIM1_GetKernelClkFreq();
      break;
    case LL_RCC_ADC_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;
#if defined(HSE_VALUE)
    case LL_RCC_ADC_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */
    case LL_RCC_ADC_CLKSOURCE_PLL1Q:
      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;
    case LL_RCC_ADC_CLKSOURCE_ICLK1:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK1);
      break;
#if defined(PLL2)
    case LL_RCC_ADC_CLKSOURCE_PLL2P:
      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;
    case LL_RCC_ADC_CLKSOURCE_ICLK2:
      frequency = RCC_ICLK_GetClockFreq(HAL_RCC_ICLK2);
      break;
#endif /* PLL2 */
    default:
      break;
  }
  frequency = frequency / RCC_GET_ADC_PRESCALER();

  return frequency;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_RCC_MODULE */
#endif /* RCC */
/**
  * @}
  */
