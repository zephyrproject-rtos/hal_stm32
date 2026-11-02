/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_rcc.c
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

/** @addtogroup STM32H7PXX_HAL_Driver
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
    interface with the STM32H7Pxx RCC peripheral.
  - It simplifies the configuration, initialization, and management of system and peripheral clocks, reset control.
  - The driver supports multiple oscillators (HSI, HSI48, HSE, LSE, LSI, CSI) and three PLLs with advanced
    fractional dividers and spread-spectrum clock generation (SSCG) for EMI reduction.
  - Key features include configuration of all bus prescalers, flexible peripheral kernel clock control,
    clock security system management (CSS), low-power clock gating and system reset to default states.
  - Peripheral clock management APIs allow enabling, disabling, and resetting clocks on various buses (AXI, AHB, APB)
    with fine-grained control.
  - The HAL RCC driver ensures some degree of portability and consistent behavior across STM32H7Pxx microcontroller
    series for common features, facilitating robust, secure, and power-efficient clock and reset management in diverse
    embedded applications.

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
(by default at 64MHz).

- There is no prescaler on High speed (AHBs) and Low speed (APBs) buses:
all peripherals mapped on these buses are running at sysclk frequency.
- The clock for all peripherals is switched off, except the SRAM and FLASH.

Once the device started from reset, the user application could:

- Configure the clock source to be used to drive the System clock
(if the application needs higher frequency/performance)
- Configure the System clock frequency and Flash settings
- Configure the AHB and APB buses prescalers
- Enable the clock for the peripheral(s) to be used
- Configure the clock source(s) for peripherals which clocks receive an independent kernel clocks.
- Configure peripherals supporting the autonomous mode (These peripherals are able to generate a kernel clock
request and a AHB/APB bus clock request when they need, in order to operate and update their status register
even in Stop mode).
  */
/**
  * @}
  */

/** @defgroup RCC_Configuration_Table RCC Configuration Table
  * @{
## Configuration inside the RCC driver

Config defines            | Description               | Default value | Note
------------------------- | ------------------------- | ------------- | ------------------------------------
PRODUCT                   | from IDE                  | Defined       | The selected product (ex STM32H7P5IIxx)
PERIPHERAL                | from CMSIS                | Defined       | Periph. available on the selected product
USE_ASSERT_DBG_PARAM      | from IDE                  | None          | When defined, enable the params assert
USE_HAL_CHECK_PARAM       | from hal_conf.h           | 0             | When set, parameters are checked in runtime
USE_HAL_RCC_MODULE        | from hal_conf.h           | 1             | When set, HAL RCC module is enabled
USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT | from hal_conf.h  | 0    | When set, RCC peripherals configuration are reset
USE_HAL_RCC_RESET_RTC_DOMAIN              | from hal_conf.h  | 0    | When set, Resources under backup domain are reset
USE_EXTERNAL_ENV          | from IDE                  | Defined       | When set, ext. oscillators values are defined
LSE_VALUE                 | From stm32_external_env.h | 32.768 kHz    | Frequency of LSE oscillator (USE_EXTERNAL_ENV)
HSE_VALUE                 | From stm32_external_env.h | 16 MHz        | Frequency of HSE oscillator (USE_EXTERNAL_ENV)
AUDIO_CLOCK_VALUE         | From stm32_external_env.h | 4.8 kHz       | Frequency of AUDIO clock (USE_EXTERNAL_ENV)
HSI_VALUE                 | From stm32h7pxxxx.h       | 64 MHz        | Frequency of HSI oscillator
CSI_VALUE                 | From stm32h7pxxxx.h       | 4 MHz         | Frequency of CSI oscillator
HSI48_VALUE               | From stm32h7pxxxx.h       | 48 MHz        | Frequency of HSI48 oscillator
LSI_VALUE                 | From stm32h7pxxxx.h       | 32 kHz        | Frequency of LSI oscillator

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
#define RCC_HSE_TIMEOUT_VALUE   HSE_STARTUP_TIMEOUT                /*!< HSE Timeout value                         */
#endif /* HSE_VALUE */
#if defined(LSE_VALUE)
#define RCC_LSE_TIMEOUT_VALUE   LSE_STARTUP_TIMEOUT                /*!< LSE Timeout value                         */
#endif /* LSE_VALUE */
#define RCC_HSI_TIMEOUT_VALUE   2U                                 /*!< 2 ms (minimum Tick + 1) timeout for HSI   */
#define RCC_HSI48_TIMEOUT_VALUE 2U                                 /*!< 2 ms (minimum Tick + 1) timeout for HSI48 */
#define RCC_CSI_TIMEOUT_VALUE   2U                                 /*!< 2 ms (minimum Tick + 1) timeout for CSI   */
#define RCC_LSI_TIMEOUT_VALUE   ((10u * 128u * 1000u) / LSI_VALUE) /*!< 40 ms for LSI at 32KHz                    */

#define RCC_PLL1_TIMEOUT_VALUE  2UL                                /*!< 2 ms (minimum Tick + 1)                   */
#define RCC_PLL2_TIMEOUT_VALUE  2UL                                /*!< 2 ms (minimum Tick + 1)                   */
#define RCC_PLL3_TIMEOUT_VALUE  2UL                                /*!< 2 ms (minimum Tick + 1)                   */
#define RCC_PLL_FRAC_WAIT_VALUE 1U                                 /*!< PLL Fractional part waiting time before new latch enable : 1 ms */

#define RCC_CLOCKSWITCH_TIMEOUT_VALUE 5000UL                       /*!< 5 s                                       */

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
  * @brief PLL index to define PLL1, PLL2 or PLL3
  * @{
  */
typedef enum
{
  PLL_1 = 0U, /*!< ID on PLL1 */
  PLL_2 = 1U, /*!< ID on PLL2 */
  PLL_3 = 2U, /*!< ID on PLL3 */
} rcc_pll_id_t;
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
#define RCC_ADCPRESC_BIT_VALUE  ((LL_RCC_GetADCPrescaler() >> RCC_CCIPR1_ADCDIV_Pos))

/*! Macro to get the ADC kernel clock prescaler */
#define RCC_GET_ADC_PRESCALER() (((RCC_ADCPRESC_BIT_VALUE) == 0x0U) ? 1U :   \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0x1U) ? 2U :   \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0x2U) ? 4U :   \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0x3U) ? 6U :   \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0x4U) ? 8U :   \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0x5U) ? 10U :  \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0x6U) ? 12U :  \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0x7U) ? 16U :  \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0x8U) ? 32U :  \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0x9U) ? 64U :  \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0xAU) ? 128U : \
                                 ((RCC_ADCPRESC_BIT_VALUE) == 0xBU) ? 256U : 1U)

/*! Macro to check the HSE clock mode */
#define IS_RCC_HSE_MODE_ENABLE(mode) (((mode) == HAL_RCC_HSE_ON)        \
                                      || ((mode) == HAL_RCC_HSE_BYPASS) \
                                      || ((mode) == HAL_RCC_HSE_BYPASS_DIGITAL))

/*! Macro to check the LSE clock mode */
#define IS_RCC_LSE_MODE_ENABLE(mode) (((mode) == HAL_RCC_LSE_ON)        \
                                      || ((mode) == HAL_RCC_LSE_BYPASS) \
                                      || ((mode) == HAL_RCC_LSE_BYPASS_DIGITAL))

/*! Macro to check the LSE drive capability */
#define IS_RCC_LSE_DRIVE(drive) (((drive) == HAL_RCC_LSE_DRIVE_LOW)           \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_MEDIUMLOW)  \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_MEDIUMHIGH) \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_HIGH))

/*! Macro to check the HSI divider */
#define IS_RCC_HSI_DIV(hsi_div) (((hsi_div) == HAL_RCC_HSI_DIV1)     \
                                 || ((hsi_div) == HAL_RCC_HSI_DIV2)  \
                                 || ((hsi_div) == HAL_RCC_HSI_DIV4)  \
                                 || ((hsi_div) == HAL_RCC_HSI_DIV8))

/*! Macro to check the HSI calibration value */
#define IS_RCC_HSI_CALIBRATION_VALUE(value) ((value) <= 127UL)

/*! Macro to check the CSI calibration value */
#define IS_RCC_CSI_CALIBRATION_VALUE(value) ((value) <= 63UL)

/*! Macro to check the STOPWAKEUPCLOCK source */
#define IS_RCC_STOP_WAKEUPCLOCK(source) (((source) == HAL_RCC_STOP_WAKEUPCLOCK_HSI)  \
                                         || ((source) == HAL_RCC_STOP_WAKEUPCLOCK_CSI))

/*! Macro to check the KERWAKEUPCLOCK source */
#define IS_RCC_STOP_KERWAKEUPCLOCK(source) (((source) == HAL_RCC_STOP_WAKEUPKERCLOCK_HSI)  \
                                            || ((source) == HAL_RCC_STOP_WAKEUPKERCLOCK_CSI))

/*! Macro to check the SYSCLK source */
#define IS_RCC_SYSCLKSOURCE(source) (((source) == HAL_RCC_SYSCLK_SRC_HSI)     \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_CSI)  \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_HSE)  \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_PLLCLK))

/*! Macro to check the SYSCLK prescaler */
#define IS_RCC_SYSCLK(sysclk) (((sysclk) == HAL_RCC_SYSCLK_PRESCALER1)      \
                               || ((sysclk) == HAL_RCC_SYSCLK_PRESCALER2)   \
                               || ((sysclk) == HAL_RCC_SYSCLK_PRESCALER4)   \
                               || ((sysclk) == HAL_RCC_SYSCLK_PRESCALER8)   \
                               || ((sysclk) == HAL_RCC_SYSCLK_PRESCALER16)  \
                               || ((sysclk) == HAL_RCC_SYSCLK_PRESCALER64)  \
                               || ((sysclk) == HAL_RCC_SYSCLK_PRESCALER128) \
                               || ((sysclk) == HAL_RCC_SYSCLK_PRESCALER256) \
                               || ((sysclk) == HAL_RCC_SYSCLK_PRESCALER512))

/*! Macro to check the HCLK prescaler */
#define IS_RCC_ACLK(aclk) (((aclk) == HAL_RCC_ACLK_PRESCALER1) \
                           || ((aclk) == HAL_RCC_ACLK_PRESCALER2))

/*! Macro to check the PCLK prescaler */
#define IS_RCC_PCLK(pclk) (((pclk) == HAL_RCC_PCLK_PRESCALER1)     \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER2)  \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER4)  \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER8)  \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER16))

/*! Macro to check the RTC kernel clock source */
#define IS_RCC_RTC_CLK(source)      (((source) == HAL_RCC_RTC_CLK_SRC_NONE)   \
                                     || ((source) == HAL_RCC_RTC_CLK_SRC_LSE) \
                                     || ((source) == HAL_RCC_RTC_CLK_SRC_LSI) \
                                     || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV))

/*! Macro to check the RTC HSE divider */
#define IS_RCC_RTC_HSEDIV(div)      ((div) <= 63U)

/*! Macro to check the MCO clock source */
#define IS_RCC_MCOSOURCE(source) (((source) == HAL_RCC_MCO1_SRC_HSI)       \
                                  || ((source) == HAL_RCC_MCO1_SRC_LSE)    \
                                  || ((source) == HAL_RCC_MCO1_SRC_HSE)    \
                                  || ((source) == HAL_RCC_MCO1_SRC_PLL1Q)   \
                                  || ((source) == HAL_RCC_MCO1_SRC_HSI48)  \
                                  || ((source) == HAL_RCC_MCO2_SRC_SYSCLK) \
                                  || ((source) == HAL_RCC_MCO2_SRC_PLL2P)   \
                                  || ((source) == HAL_RCC_MCO2_SRC_HSE)    \
                                  || ((source) == HAL_RCC_MCO2_SRC_PLL1P)   \
                                  || ((source) == HAL_RCC_MCO2_SRC_CSI)    \
                                  || ((source) == HAL_RCC_MCO2_SRC_LSI))

/*! Macro to check the MCO divider */
#define IS_RCC_MCOPRE(div) (((div) == HAL_RCC_MCO1_NO_CLK)         \
                            || ((div) == HAL_RCC_MCO1_PRESCALER1)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER2)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER3)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER4)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER5)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER6)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER7)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER8)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER9)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER10) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER11) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER12) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER13) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER14) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER15) \
                            || ((div) == HAL_RCC_MCO2_NO_CLK)      \
                            || ((div) == HAL_RCC_MCO2_PRESCALER1)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER2)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER3)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER4)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER5)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER6)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER7)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER8)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER9)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER10) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER11) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER12) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER13) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER14) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER15))

/*! Macro to check the PLLM Value */
#define IS_RCC_PLLM_VALUE(value) ((1U <= (value)) && ((value) <= 63U))

/*! Macro to check the PLLN Value */
#define IS_RCC_PLLN_VALUE(value) ((8U <= (value)) && ((value) <= 420U))

/*! Macro to check the PLLP Value */
#define IS_RCC_PLLP_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

/*! Macro to check the PLL1P Value */
#define IS_RCC_PLL1P_VALUE(value) (((value) != 3U) && (1U <= (value)) && ((value) <= 128U))

/*! Macro to check the PLLQ Value */
#define IS_RCC_PLLQ_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

/*! Macro to check the PLLR Value */
#define IS_RCC_PLLR_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

/*! Macro to check the PLLS Value */
#define IS_RCC_PLLS_VALUE(value) ((1U <= (value)) && ((value) <= 8U))

/*! Macro to check the PLLT Value */
#define IS_RCC_PLLT_VALUE(value) ((1U <= (value)) && ((value) <= 8U))

/*! Macro to check the PLL source */
#define IS_RCC_PLL_SOURCE(source) (((source) == HAL_RCC_PLL_SRC_HSI)    \
                                   || ((source) == HAL_RCC_PLL_SRC_CSI) \
                                   || ((source) == HAL_RCC_PLL_SRC_HSE) \
                                   || ((source) == HAL_RCC_PLL_SRC_NO_CLK))

/*! Macro to check the PLL input clock frequency range */
#define IS_RCC_PLL_INPUT_RANGE(range) (((range) == HAL_RCC_PLL_INPUT_RANGE_1_2)    \
                                       || ((range) == HAL_RCC_PLL_INPUT_RANGE_2_4) \
                                       || ((range) == HAL_RCC_PLL_INPUT_RANGE_4_8) \
                                       || ((range) == HAL_RCC_PLL_INPUT_RANGE_8_16))

/*! Macro to check the PLL VCO frequency range */
#define IS_RCC_PLL_VCO_RANGE(range) (((range) == HAL_RCC_PLL_VCO_RANGE_384_1672)    \
                                     || ((range) == HAL_RCC_PLL_VCO_RANGE_150_420) )

/*! Macro to Calculate the spread spectrum modulation depth (MD), scaled by 1000000ULL */
#define RCC_CALC_PLL_SSCG_MD(mod_per, inc_step, divn) \
  (((uint64_t)(mod_per) * (uint64_t)(inc_step) * 500ULL * 1000000ULL) / \
   ((uint64_t)0x7FFFU * ((uint64_t)(divn) + 1ULL)))

/*! Macro to check the PLLSSCG State */
#define IS_RCC_PLLSSCG_STATE(state) (((state) == HAL_RCC_PLL_SSCG_DISABLE)    \
                                     || ((state) == HAL_RCC_PLL_SSCG_ENABLE))

/*! Macro to check the PLL SSCG Modulation Period value */
#define IS_RCC_PLL_SSCG_MOD_PER_VALUE(value) ((value) <= 8191U)

/*! Macro to check the PLL SSCG Modulation Depth Adjustment value */
#define IS_RCC_PLL_SSCG_MOD_DEPTH_ADJ_VALUE(value) ((value) <= 32767U)

/*! Macro to check the PLL spread-spectrum spread mode selection */
#define IS_RCC_PLL_SSCG_SPREAD_MODE(value) (((value) == HAL_RCC_PLL_SSCG_SPREAD_CENTER)  \
                                            || ((value) == HAL_RCC_PLL_SSCG_SPREAD_DOWN))

/*! Macro to check the PLL spread-spectrum dithering noise selection */
#define IS_RCC_PLL_SSCG_DITH_CTRL_VALUE(value) (((value) == HAL_RCC_PLL_SSCG_DITH_NO)       \
                                                || ((value) == HAL_RCC_PLL_SSCG_DITH_RPDF)  \
                                                || ((value) == HAL_RCC_PLL_SSCG_DITH_TPDF)  \
                                                || ((value) == HAL_RCC_PLL_SSCG_DITH_RPDF_TPDF))

/*! Macro to check the PLL FRACN value */
#define IS_RCC_PLL_FRACN_VALUE(value) ((value) <= 8191U)

/*! Macro to check the PLL1 output selection */
#define IS_RCC_PLL1_OUTPUT(value) ((((value) & (HAL_RCC_PLL1_OUTPUT_ALL)) != 0x00u) \
                                   && (((value) & ~(HAL_RCC_PLL1_OUTPUT_ALL)) == 0x00u))

/*! Macro to check the PLL2 output selection */
#define IS_RCC_PLL2_OUTPUT(value) ((((value) & (HAL_RCC_PLL2_OUTPUT_ALL)) != 0x00u) \
                                   && (((value) & ~(HAL_RCC_PLL2_OUTPUT_ALL)) == 0x00u))

/*! Macro to check the PLL3 output selection */
#define IS_RCC_PLL3_OUTPUT(value) ((((value) & (HAL_RCC_PLL3_OUTPUT_ALL)) != 0x00u) \
                                   && (((value) & ~(HAL_RCC_PLL3_OUTPUT_ALL)) == 0x00u))

/*! Macro to check the FMC kernel clock source */
#define IS_RCC_FMC_CLK(source) (((source) == HAL_RCC_FMC_CLK_SRC_HCLK5)    \
                                || ((source) == HAL_RCC_FMC_CLK_SRC_PLL1Q) \
                                || ((source) == HAL_RCC_FMC_CLK_SRC_PLL2R) \
                                || ((source) == HAL_RCC_FMC_CLK_SRC_HSI))

/*! Macro to check the SDMMC1 kernel clock source */
#define IS_RCC_SDMMC1_CLK(source) (((source) == HAL_RCC_SDMMC1_CLK_SRC_PLL2S) \
                                   || ((source) == HAL_RCC_SDMMC1_CLK_SRC_PLL2T))

/*! Macro to check the XSPI1 kernel clock source */
#define IS_RCC_XSPI1_CLK(source) (((source) == HAL_RCC_XSPI1_CLK_SRC_HCLK5)     \
                                  || ((source) == HAL_RCC_XSPI1_CLK_SRC_PLL2S)  \
                                  || ((source) == HAL_RCC_XSPI1_CLK_SRC_PLL2T)) \

/*! Macro to check the USB OTG FS kernel clock source */
#define IS_RCC_USBOTGFS_CLK(source) (((source) == HAL_RCC_USBOTGFS_CLK_SRC_HSI48)    \
                                     || ((source) == HAL_RCC_USBOTGFS_CLK_SRC_PLL3Q) \
                                     || ((source) == HAL_RCC_USBOTGFS_CLK_SRC_HSE))

/*! Macro to check the ADF1 kernel clock source */
#define IS_RCC_ADF1_CLK(source) (((source) == HAL_RCC_ADF1_CLK_SRC_HCLK1)       \
                                 || ((source) == HAL_RCC_ADF1_CLK_SRC_PLL2P)    \
                                 || ((source) == HAL_RCC_ADF1_CLK_SRC_PLL3P)    \
                                 || ((source) == HAL_RCC_ADF1_CLK_SRC_AUDIOCLK) \
                                 || ((source) == HAL_RCC_ADF1_CLK_SRC_CSI)      \
                                 || ((source) == HAL_RCC_ADF1_CLK_SRC_HSI))

/*! Macro to check the ADC kernel clock source */
#define IS_RCC_ADC_CLK(source) (((source) == HAL_RCC_ADC_CLK_SRC_HCLK3)    \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_TIM)   \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_HSI)   \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_HSE)   \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_PLL2P) \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_PLL3R) \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_PER))

/*! Macro to check the ADC kernel clock prescaler */
#define IS_RCC_ADC_PRESCALER(prescaler)  (((prescaler) == HAL_RCC_ADC_CLK_PRESCALER1)      \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER2)   \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER4)   \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER6)   \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER8)   \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER10)  \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER12)  \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER16)  \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER32)  \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER64)  \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER128) \
                                          || ((prescaler) == HAL_RCC_ADC_CLK_PRESCALER256))

/*! Macro to check the Peripheral kernel clock source */
#define IS_RCC_PERCLK(source) (((source) == HAL_RCC_PERCLK_SRC_HSI)    \
                               || ((source) == HAL_RCC_PERCLK_SRC_CSI) \
                               || ((source) == HAL_RCC_PERCLK_SRC_HSE))

/*! Macro to check the UART234578 kernel clock source */
#define IS_RCC_UART234578_CLK(source) (((source) == HAL_RCC_UART234578_CLK_SRC_PCLK1)    \
                                       || ((source) == HAL_RCC_UART234578_CLK_SRC_PLL2Q) \
                                       || ((source) == HAL_RCC_UART234578_CLK_SRC_PLL3Q) \
                                       || ((source) == HAL_RCC_UART234578_CLK_SRC_HSI)   \
                                       || ((source) == HAL_RCC_UART234578_CLK_SRC_CSI)   \
                                       || ((source) == HAL_RCC_UART234578_CLK_SRC_LSE))

/*! Macro to check the SPI23 kernel clock source */
#define IS_RCC_SPI23_CLK(source) (((source) == HAL_RCC_SPI23_CLK_SRC_PLL1Q)       \
                                  || ((source) == HAL_RCC_SPI23_CLK_SRC_PLL2P)    \
                                  || ((source) == HAL_RCC_SPI23_CLK_SRC_PLL3P)    \
                                  || ((source) == HAL_RCC_SPI23_CLK_SRC_AUDIOCLK) \
                                  || ((source) == HAL_RCC_SPI23_CLK_SRC_PER))

/*! Macro to check the I2C123 kernel clock source */
#define IS_RCC_I2C123_CLK(source) (((source) == HAL_RCC_I2C123_CLK_SRC_PCLK1)    \
                                   || ((source) == HAL_RCC_I2C123_CLK_SRC_PLL3R) \
                                   || ((source) == HAL_RCC_I2C123_CLK_SRC_HSI)   \
                                   || ((source) == HAL_RCC_I2C123_CLK_SRC_CSI))

/*! Macro to check the I3C1 kernel clock source */
#define IS_RCC_I3C1_CLK(source) (((source) == HAL_RCC_I3C1_CLK_SRC_PCLK1)    \
                                 || ((source) == HAL_RCC_I3C1_CLK_SRC_PLL3R) \
                                 || ((source) == HAL_RCC_I3C1_CLK_SRC_HSI)   \
                                 || ((source) == HAL_RCC_I3C1_CLK_SRC_CSI))

/*! Macro to check the LPTIM1 kernel clock source */
#define IS_RCC_LPTIM1_CLK(source) (((source) == HAL_RCC_LPTIM1_CLK_SRC_PCLK1)    \
                                   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_PLL2P) \
                                   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_PLL3R) \
                                   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_LSE)   \
                                   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_LSI)   \
                                   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_PER))

/*! Macro to check the FDCAN kernel clock source */
#define IS_RCC_FDCAN_CLK(source) (((source) == HAL_RCC_FDCAN_CLK_SRC_HSE)      \
                                  || ((source) == HAL_RCC_FDCAN_CLK_SRC_PLL1Q) \
                                  || ((source) == HAL_RCC_FDCAN_CLK_SRC_PLL2P))

/*! Macro to check the USART16910 kernel clock source */
#define IS_RCC_USART16910_CLK(source) (((source) == HAL_RCC_USART16910_CLK_SRC_PCLK2)    \
                                       || ((source) == HAL_RCC_USART16910_CLK_SRC_PLL2Q) \
                                       || ((source) == HAL_RCC_USART16910_CLK_SRC_PLL3Q) \
                                       || ((source) == HAL_RCC_USART16910_CLK_SRC_HSI)   \
                                       || ((source) == HAL_RCC_USART16910_CLK_SRC_CSI)   \
                                       || ((source) == HAL_RCC_USART16910_CLK_SRC_LSE))

/*! Macro to check the SPI45 kernel clock source */
#define IS_RCC_SPI45_CLK(source) (((source) == HAL_RCC_SPI45_CLK_SRC_PCLK2)    \
                                  || ((source) == HAL_RCC_SPI45_CLK_SRC_PLL2Q) \
                                  || ((source) == HAL_RCC_SPI45_CLK_SRC_PLL3Q) \
                                  || ((source) == HAL_RCC_SPI45_CLK_SRC_HSI)   \
                                  || ((source) == HAL_RCC_SPI45_CLK_SRC_CSI)   \
                                  || ((source) == HAL_RCC_SPI45_CLK_SRC_HSE))

/*! Macro to check the SPI1 kernel clock source */
#define IS_RCC_SPI1_CLK(source) (((source) == HAL_RCC_SPI1_CLK_SRC_PLL1Q)       \
                                 || ((source) == HAL_RCC_SPI1_CLK_SRC_PLL2P)    \
                                 || ((source) == HAL_RCC_SPI1_CLK_SRC_PLL3P)    \
                                 || ((source) == HAL_RCC_SPI1_CLK_SRC_AUDIOCLK) \
                                 || ((source) == HAL_RCC_SPI1_CLK_SRC_PER))

/*! Macro to check the LPUART1 kernel clock source */
#define IS_RCC_LPUART1_CLK(source) (((source) == HAL_RCC_LPUART1_CLK_SRC_PCLK4)    \
                                    || ((source) == HAL_RCC_LPUART1_CLK_SRC_PLL2Q) \
                                    || ((source) == HAL_RCC_LPUART1_CLK_SRC_PLL3Q) \
                                    || ((source) == HAL_RCC_LPUART1_CLK_SRC_HSI)   \
                                    || ((source) == HAL_RCC_LPUART1_CLK_SRC_CSI)   \
                                    || ((source) == HAL_RCC_LPUART1_CLK_SRC_LSE))

/*! Macro to check the SPI6 kernel clock source */
#define IS_RCC_SPI6_CLK(source) (((source) == HAL_RCC_SPI6_CLK_SRC_PCLK4)    \
                                 || ((source) == HAL_RCC_SPI6_CLK_SRC_PLL2Q) \
                                 || ((source) == HAL_RCC_SPI6_CLK_SRC_PLL3Q) \
                                 || ((source) == HAL_RCC_SPI6_CLK_SRC_HSI)   \
                                 || ((source) == HAL_RCC_SPI6_CLK_SRC_CSI)   \
                                 || ((source) == HAL_RCC_SPI6_CLK_SRC_HSE))

/*! Macro to check the LPTIM23 kernel clock source */
#define IS_RCC_LPTIM23_CLK(source) (((source) == HAL_RCC_LPTIM23_CLK_SRC_PCLK4)    \
                                    || ((source) == HAL_RCC_LPTIM23_CLK_SRC_PLL2P) \
                                    || ((source) == HAL_RCC_LPTIM23_CLK_SRC_PLL3R) \
                                    || ((source) == HAL_RCC_LPTIM23_CLK_SRC_LSE)   \
                                    || ((source) == HAL_RCC_LPTIM23_CLK_SRC_LSI)   \
                                    || ((source) == HAL_RCC_LPTIM23_CLK_SRC_PER))

/*! Macro to check the LPTIM45 kernel clock source */
#define IS_RCC_LPTIM45_CLK(source) (((source) == HAL_RCC_LPTIM45_CLK_SRC_PCLK4)    \
                                    || ((source) == HAL_RCC_LPTIM45_CLK_SRC_PLL2P) \
                                    || ((source) == HAL_RCC_LPTIM45_CLK_SRC_PLL3R) \
                                    || ((source) == HAL_RCC_LPTIM45_CLK_SRC_LSE)   \
                                    || ((source) == HAL_RCC_LPTIM45_CLK_SRC_LSI)   \
                                    || ((source) == HAL_RCC_LPTIM45_CLK_SRC_PER))

/*! Macro to check the DAC1 kernel clock source */
#define IS_RCC_DAC1_CLK(source) (((source) == HAL_RCC_DAC1_CLK_SRC_HCLK3)    \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_TIM)   \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_ADC)   \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_HSI)   \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_HSE)   \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_PLL3R) \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_PER))

/*! Macro to check the DAC1SH kernel clock source */
#define IS_RCC_DAC1SH_CLK(source) (((source) == HAL_RCC_DAC1SH_CLK_SRC_LSE) \
                                   || ((source) == HAL_RCC_DAC1SH_CLK_SRC_LSI))

/*! Macro to check the DAC2 kernel clock source */
#define IS_RCC_DAC2_CLK(source) (((source) == HAL_RCC_DAC2_CLK_SRC_HCLK3)    \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_TIM)   \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_ADC)   \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_HSI)   \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_HSE)   \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_PLL3R) \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_PER))

/*! Macro to check the DAC3 kernel clock source */
#define IS_RCC_DAC3_CLK(source) (((source) == HAL_RCC_DAC3_CLK_SRC_HCLK3)    \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_TIM)   \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_ADC)   \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_HSI)   \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_HSE)   \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_PLL3R) \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_PER))

/*! Macro to check the DAC4 kernel clock source */
#define IS_RCC_DAC4_CLK(source) (((source) == HAL_RCC_DAC4_CLK_SRC_HCLK3)    \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_TIM)   \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_ADC)   \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_HSI)   \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_HSE)   \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_PLL3R) \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_PER))

/**
  * @}
  */


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC Private Functions
  * @{
  */
static hal_status_t RCC_WaitForTimeout(const rcc_cb_timeout_t p_timeout_cb, uint32_t timeout, uint32_t status);
static hal_status_t RCC_PLL_SetConfig(rcc_pll_id_t pll_id, const hal_rcc_pll_config_t *p_config);
static void         RCC_PLL_GetConfig(rcc_pll_id_t pll_id, hal_rcc_pll_config_t *p_config);
static void         RCC_PLL_GetClockFreq(rcc_pll_id_t pll_id, hal_rcc_pll_output_freq_t *p_clk);
static uint32_t     RCC_PLL_GetOutputFreq(rcc_pll_id_t pll_id, uint32_t output_en, uint32_t divider,
                                          uint64_t pll_vco_num, uint64_t pll_vco_den);
static uint32_t     RCC_HSI_GetClockFreq(void);
static uint32_t     RCC_PERCLK_GetClockFreq(void);
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
  LL_RCC_DisableIT(LL_RCC_IT_LSIRDY | LL_RCC_IT_LSERDY | LL_RCC_IT_HSIRDY | LL_RCC_IT_HSERDY | \
                   LL_RCC_IT_CSIRDY | LL_RCC_IT_HSI48RDY | LL_RCC_IT_PLL1RDY | LL_RCC_IT_PLL2RDY | \
                   LL_RCC_IT_PLL3RDY | LL_RCC_IT_LSECSS);

#if defined(USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT) && (USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT == 1U)
  /* Reset peripheral clock enable */
  LL_CKG_Enable(LL_CKG_PERIPH_ALL);

  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_ALL);
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_ALL & (~(LL_AHB2_GRP1_PERIPH_AHBSRAM1 | LL_AHB2_GRP1_PERIPH_AHBSRAM2 |
                                                         LL_AHB2_GRP1_PERIPH_AHBSRAM3)));
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_ALL);
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_ALL);
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_ALL);

  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_ALL);
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_ALL);
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_ALL);
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_ALL);

  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_ALL);
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_ALL);
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_ALL);
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_ALL);
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_ALL);
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_ALL);
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_ALL);
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_ALL);
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_ALL);

  /* Reset peripheral clock source selection */

  LL_RCC_WRITE_REG(CCIPR1, RCC_CCIPR1_Rst);
  LL_RCC_WRITE_REG(CCIPR2, RCC_CCIPR2_Rst);
  LL_RCC_WRITE_REG(CCIPR3, RCC_CCIPR3_Rst);
  LL_RCC_WRITE_REG(CCIPR4, RCC_CCIPR4_Rst);

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
  LL_RCC_SetSysPrescaler(LL_RCC_SYSCLK_PRESCALER_1);
  LL_RCC_ConfigBusClock(LL_RCC_BMCLK_PRESCALER_1, LL_RCC_APB1_PRESCALER_1 |
                        LL_RCC_APB2_PRESCALER_1 | LL_RCC_APB4_PRESCALER_1);

  SystemCoreClock = HSI_VALUE;

  (void)HAL_InitTick(HAL_TICK_FREQ_DEFAULT, uwTickPrio);

#if defined(USE_HAL_RCC_RESET_RTC_DOMAIN) && (USE_HAL_RCC_RESET_RTC_DOMAIN == 1U)
  /* Reset backup domain */
  LL_RCC_ForceBackupDomainReset();
  LL_RCC_ReleaseBackupDomainReset();
#endif /* USE_HAL_RCC_RESET_RTC_DOMAIN */

  /* Reset all remaining oscillators not in backup domain (excepted the one used for System clock) */
  uint32_t read_value = LL_RCC_READ_REG(CR);

  LL_RCC_WRITE_REG(CR, (RCC_CR_Rst | (read_value & (RCC_CR_HSEBYP | RCC_CR_HSEEXT))));
  LL_RCC_WRITE_REG(CR, RCC_CR_Rst); /* HSE EXT and BYP disabled only when HSE has been disabled */


  LL_RCC_LSI_Disable();

  (void)RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U);
  (void)RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 0U);
  (void)RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 0U);

  /* Reset MCO, RTC prescaler and wake up system clock */
#if defined(USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT) && (USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT == 1U)
  /* Reset MCOx and RTC prescaler */
  LL_RCC_WRITE_REG(CFGR, RCC_CFGR_Rst);
#else
  /* Reset MCOx prescaler */
  read_value = LL_RCC_READ_REG(CFGR);

  LL_RCC_WRITE_REG(CFGR, (RCC_CFGR_Rst | (read_value & RCC_CFGR_RTCPRE)));
#endif /* USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT */

  /* Reset PLLs */
  LL_RCC_WRITE_REG(PLLCKSELR, RCC_PLLCKSELR_Rst);
  LL_RCC_WRITE_REG(PLLCFGR, RCC_PLLCFGR_Rst);

  LL_RCC_WRITE_REG(PLL1DIVR1, RCC_PLL1DIVR1_Rst);
  LL_RCC_WRITE_REG(PLL1DIVR2, RCC_PLL1DIVR2_Rst);
  LL_RCC_WRITE_REG(PLL1FRACR, RCC_PLL1FRACR_Rst);
  LL_RCC_WRITE_REG(PLL1SSCGR, RCC_PLL1SSCGR_Rst);

  LL_RCC_WRITE_REG(PLL2DIVR1, RCC_PLL2DIVR1_Rst);
  LL_RCC_WRITE_REG(PLL2DIVR2, RCC_PLL2DIVR2_Rst);
  LL_RCC_WRITE_REG(PLL2FRACR, RCC_PLL2FRACR_Rst);
  LL_RCC_WRITE_REG(PLL2SSCGR, RCC_PLL2SSCGR_Rst);

  LL_RCC_WRITE_REG(PLL3DIVR1, RCC_PLL3DIVR1_Rst);
  LL_RCC_WRITE_REG(PLL3DIVR2, RCC_PLL3DIVR2_Rst);
  LL_RCC_WRITE_REG(PLL3FRACR, RCC_PLL3FRACR_Rst);
  LL_RCC_WRITE_REG(PLL3SSCGR, RCC_PLL3SSCGR_Rst);


  /* Clear RCC flags */
  LL_RCC_ClearFlag(LL_RCC_IT_LSIRDY | LL_RCC_IT_LSERDY | LL_RCC_IT_HSIRDY | LL_RCC_IT_HSERDY | \
                   LL_RCC_IT_CSIRDY | LL_RCC_IT_HSI48RDY | LL_RCC_IT_PLL1RDY | LL_RCC_IT_PLL2RDY | \
                   LL_RCC_IT_PLL3RDY | LL_RCC_IT_HSECSS | LL_RCC_IT_LSECSS);

  LL_RCC_ClearResetFlags();
}

/**
  * @brief  Reset the RCC clock configuration to the default system clock (HSI at 64Mhz).
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
  LL_RCC_SetSysPrescaler(LL_RCC_SYSCLK_PRESCALER_1);
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
  * @brief  Enable the HSE oscillator in the selected mode in interrupt mode.
  * @param  mode        HSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_HSE_ON
  *         @arg @ref HAL_RCC_HSE_BYPASS
  *         @arg @ref HAL_RCC_HSE_BYPASS_DIGITAL
  * @note   Transitions HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this function.
  * @note   This function only enables the HSE and the corresponding ready interrupt.
  *         When HSE is ready, the callback HAL_RCC_HSE_ReadyCallback() is invoked.
  * @retval HAL_OK HSE oscillator enable sequence has been started
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
  * @brief   Disable the HSE oscillator.
  * @warning This oscillator might be used as peripheral clock source. Calling this function will stop
  *          the operation of any peripheral relying on HSE.
  * @retval  HAL_OK      HSE oscillator has been deactivated successfully
  * @retval  HAL_ERROR   HSE is used as system clock or source clock of the main PLL used as system clock\n
  *                      Timeout linked to HSE ready flag not reset
  */
hal_status_t HAL_RCC_HSE_Disable(void)
{
  hal_status_t status;
  uint32_t sysclk_source;
  uint32_t pll_source;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_source    = LL_RCC_PLL_GetSource();

  /*  When the HSE is used as system clock or clock source for PLL, it is not allowed to be disabled */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_source == LL_RCC_PLLSOURCE_HSE))
      || (LL_RCC_IsEnabledXSPIClockProtection() == 1U)
      || (LL_RCC_IsEnabledFMCClockProtection() == 1U))
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
  * @retval None
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
  *         @arg @ref HAL_RCC_LSE_BYPASS_DIGITAL
  * @param  drive       LSE drive capability selection
  * @warning Access to backup domain must be enabled.
  * @note   Drive capability is relevant only in Xtal mode (means not in bypass mode)
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this function.
  * @retval HAL_OK      LSE oscillator has been configured successfully
  * @retval HAL_ERROR   Backup domain is not enabled\n
  *                     Timeout linked to LSE ready flag not set
  */
hal_status_t HAL_RCC_LSE_Enable(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive)
{
  ASSERT_DBG_PARAM(IS_RCC_LSE_MODE_ENABLE(mode));
  ASSERT_DBG_PARAM(IS_RCC_LSE_DRIVE(drive));

  if (LL_PWR_IsEnabledBackupDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  /* Set the new LSE configuration ---------------------------------------*/
  if (((uint32_t)mode & RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP)
  {
    LL_RCC_LSE_ConfigBypass((uint32_t)mode & RCC_BDCR_LSEEXT);
  }
  else
  {
    LL_RCC_LSE_SetDriveCapability((uint32_t)drive);
  }

  /* Enable LSE and wait for activation */
  LL_RCC_LSE_Enable();

  return RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Enable the LSE oscillator in interrupt mode with an oscillator load range capability.
  * @param  mode        LSE mode. This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_LSE_ON
  *         @arg @ref HAL_RCC_LSE_BYPASS
  *         @arg @ref HAL_RCC_LSE_BYPASS_DIGITAL
  * @param  drive       LSE drive capability selection
  * @warning Access to backup domain must already be enabled.
  * @note   This function only enables the LSE and the corresponding ready interrupt.
  *         When LSE is ready, the callback HAL_RCC_LSE_ReadyCallback() is invoked.
  * @retval HAL_OK      LSE oscillator enable sequence has been started
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_LSE_Enable_IT(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive)
{
  ASSERT_DBG_PARAM(IS_RCC_LSE_MODE_ENABLE(mode));
  ASSERT_DBG_PARAM(IS_RCC_LSE_DRIVE(drive));

  if (LL_PWR_IsEnabledBackupDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  /* Set the new LSE configuration ---------------------------------------*/
  if (((uint32_t)mode & RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP)
  {
    LL_RCC_LSE_ConfigBypass((uint32_t)mode & RCC_BDCR_LSEEXT);
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
  if (LL_PWR_IsEnabledBackupDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_LSE_Disable();
  LL_RCC_LSE_DisableBypass();
  LL_RCC_LSE_SetExternalClockType(LL_RCC_LSE_ANALOG_TYPE);
  LL_RCC_DisableIT(LL_RCC_IT_LSERDY);
  if (RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 0U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Set LSE drive to low (default value) */
  LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_LOW);

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
  * @brief  Check if an LSE CSS failure is detected.
  * @retval hal_rcc_lse_css_failure_detection_status_t LSE CSS failure detection status
  */
hal_rcc_lse_css_failure_detection_status_t HAL_RCC_LSE_IsCSSDetected(void)
{
  return (hal_rcc_lse_css_failure_detection_status_t)LL_RCC_LSE_IsCSSDetected();
}

/**
  * @brief  RCC LSE ready interrupt callback.
  * @retval None
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
  * @retval HAL_OK      HSI oscillator enable sequence has been started
  *                     HSI oscillator is already well configured
  * @retval HAL_ERROR   HSI is used as source clock of any active PLL\n
  *                     Timeout linked to HSI Divider ready flag not set\n
  *                     Timeout linked to HSI ready flag not set
  */
hal_status_t HAL_RCC_HSI_Enable(hal_rcc_hsi_div_t divider)
{
  uint32_t current_divider;
  uint32_t hsi_is_ready;
  uint32_t divider_change;
  uint32_t pll_source = LL_RCC_PLL_GetSource();

  ASSERT_DBG_PARAM(IS_RCC_HSI_DIV(divider));

  current_divider = LL_RCC_HSI_GetDivider();
  hsi_is_ready = LL_RCC_HSI_IsReady();
  divider_change = ((current_divider != (uint32_t)divider) ? 1UL : 0UL);

  /* Check if HSI already has the correct configuration */
  if ((hsi_is_ready != 0U) && (divider_change == 0U))
  {
    return HAL_OK;
  }

  /* Check if HSI divider change is requested while HSI is used as source of any active PLL */
  if ((divider_change != 0U)
      && ((pll_source == LL_RCC_PLLSOURCE_HSI)
          && (((LL_RCC_PLL1_IsReady() == 1U)) || (LL_RCC_PLL2_IsReady() == 1U) || (LL_RCC_PLL3_IsReady() == 1U))))
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
  * @retval HAL_OK      HSI oscillator enable sequence has been started
  *                     HSI oscillator is already well configured
  * @retval HAL_ERROR   HSI is used as source clock of any active PLL.
  */
hal_status_t HAL_RCC_HSI_Enable_IT(hal_rcc_hsi_div_t divider)
{
  uint32_t current_divider;
  uint32_t hsi_is_ready;
  uint32_t divider_change;
  uint32_t pll_source = LL_RCC_PLL_GetSource();

  ASSERT_DBG_PARAM(IS_RCC_HSI_DIV(divider));

  current_divider = LL_RCC_HSI_GetDivider();
  hsi_is_ready = LL_RCC_HSI_IsReady();
  divider_change = ((current_divider != (uint32_t)divider) ? 1UL : 0UL);

  /* Check if HSI already has the correct configuration */
  if ((hsi_is_ready != 0U) && (divider_change == 0U))
  {
    return HAL_OK;
  }

  /* Check if HSI divider change is requested while HSI is used as source of any active PLL */
  if ((divider_change != 0U)
      && ((pll_source == LL_RCC_PLLSOURCE_HSI)
          && (((LL_RCC_PLL1_IsReady() == 1U)) || (LL_RCC_PLL2_IsReady() == 1U) || (LL_RCC_PLL3_IsReady() == 1U))))
  {
    return HAL_ERROR;
  }

  if (divider_change != 0U)
  {
    LL_RCC_HSI_SetDivider((uint32_t)divider);
  }

  if (hsi_is_ready == 0U)
  {
    LL_RCC_EnableIT(LL_RCC_IT_HSIRDY);
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
  *                     FMC or XSPI clock protection is enabled.
  *                     Timeout linked to HSI ready flag not reset
  */
hal_status_t HAL_RCC_HSI_Disable(void)
{
  hal_status_t status;
  uint32_t sysclk_source;
  uint32_t pll_source;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_source    = LL_RCC_PLL_GetSource();

  /* Check that HSI is not used as system clock or as PLL source when PLL is selected as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_source == LL_RCC_PLLSOURCE_HSI))
      || (LL_RCC_IsEnabledXSPIClockProtection() == 1U)
      || (LL_RCC_IsEnabledFMCClockProtection() == 1U))
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
  * @retval HAL_OK      HSI oscillator is disabled in Stop mode.
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

/**
  * @brief  RCC HSI ready interrupt callback.
  * @retval None
  */
__WEAK void HAL_RCC_HSI_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_HSI_ReadyCallback must be implemented in the user file
   */
}

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
  * @brief  Enable the HSI48 in interrupt mode.
  * @note   This function only enables the HSI48 and the corresponding ready interrupt.
  *         When HSI48 is ready, the callback HAL_RCC_HSI48_ReadyCallback() is invoked.
  * @retval HAL_OK HSI48 oscillator enable sequence has been started
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
  * @brief  RCC HSI48 ready interrupt callback.
  * @retval None
  */
__WEAK void HAL_RCC_HSI48_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_HSI48_ReadyCallback must be implemented in the user file
   */
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
  * @brief  Get the HSI48 oscillator calibration value.
  * @retval Calibration value between 0 and 1023.
  */
uint32_t  HAL_RCC_HSI48_GetCalibration(void)
{
  return LL_RCC_HSI48_GetCalibration();
}


/**
  * @brief  Enable the CSI oscillator.
  * @retval HAL_OK      CSI oscillator has been activated successfully
  * @retval HAL_ERROR   Timeout linked to CSI ready flag not set
  */
hal_status_t HAL_RCC_CSI_Enable(void)
{
  LL_RCC_CSI_Enable();

  return RCC_WaitForTimeout(LL_RCC_CSI_IsReady, RCC_CSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Enable the Internal Low-Power oscillator (CSI) in interrupt mode.
  * @note   This function only enables the CSI and the corresponding ready interrupt.
  *         When CSI is ready, the callback HAL_RCC_CSI_ReadyCallback() is invoked.
  * @retval HAL_OK CSI oscillator enable sequence has been started
  */
hal_status_t HAL_RCC_CSI_Enable_IT(void)
{
  LL_RCC_EnableIT(LL_RCC_IT_CSIRDY);
  LL_RCC_CSI_Enable();

  return HAL_OK;
}

/**
  * @brief  Disable the CSI oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      CSI oscillator has been deactivated successfully
  * @retval HAL_ERROR   CSI is used as system clock or source clock of the main PLL used as system clock\n
  *                     FMC or XSPI clock protection is enabled.
  *                     Timeout linked to CSI ready flag not reset
  */
hal_status_t HAL_RCC_CSI_Disable(void)
{
  hal_status_t status;
  uint32_t sysclk_source;
  uint32_t pll_source;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_source    = LL_RCC_PLL_GetSource();

  /* Check that CSI is not used as system clock or as PLL source when PLL is selected as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_CSI)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_source == LL_RCC_PLLSOURCE_CSI))
      || (LL_RCC_IsEnabledXSPIClockProtection() == 1U)
      || (LL_RCC_IsEnabledFMCClockProtection() == 1U))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_CSI_Disable();
    LL_RCC_DisableIT(LL_RCC_IT_CSIRDY);
    status = RCC_WaitForTimeout(LL_RCC_CSI_IsReady, RCC_CSI_TIMEOUT_VALUE, 0U);
  }

  return status;
}

/**
  * @brief  Check if CSI is enabled.
  * @retval hal_rcc_osc_enable_status_t CSI enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_CSI_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_CSI_IsEnabled();
}

/**
  * @brief  Check if CSI is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       CSI is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   CSI can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_CSI_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_CSI_IsReady();
}

/**
  * @brief  Enable the CSI oscillator in Stop mode.
  * @retval HAL_OK CSI oscillator is forced ON even in Stop mode.
  */
hal_status_t HAL_RCC_CSI_EnableInStopMode(void)
{
  LL_RCC_CSI_EnableInStopMode();
  return HAL_OK;
}

/**
  * @brief  Disable the CSI oscillator in Stop mode.
  * @retval HAL_OK      CSI oscillator is disabled in Stop mode.
  */
hal_status_t HAL_RCC_CSI_DisableInStopMode(void)
{
  LL_RCC_CSI_DisableInStopMode();
  return HAL_OK;
}

/**
  * @brief  Check if CSI in stop mode is enabled.
  * @retval status based on @ref hal_rcc_osc_stop_mode_status_t
  * @retval HAL_RCC_OSC_DISABLED_IN_STOP_MODE   CSI is disabled in stop mode
  * @retval HAL_RCC_OSC_ENABLED_IN_STOP_MODE    CSI is enabled in stop mode
  */
hal_rcc_osc_stop_mode_status_t HAL_RCC_CSI_IsEnabledInStopMode(void)
{
  return (hal_rcc_osc_stop_mode_status_t)LL_RCC_CSI_IsEnabledInStopMode();
}

/**
  * @brief  Configure the CSI oscillator trimming value.
  * @param  value  Trimming value (default is @ref HAL_RCC_CSICALIBRATION_DEFAULT).
  *                This parameter must be a number between 0 and 63.
  * @note   The trimming is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal CSI RC.
  * @note   The trimming value might be updated while the CSI oscillator is enabled.
  */
void HAL_RCC_CSI_SetTrimming(uint32_t value)
{
  ASSERT_DBG_PARAM(IS_RCC_CSI_CALIBRATION_VALUE(value));

  LL_RCC_CSI_SetCalibTrimming(value);
}

/**
  * @brief  Get the CSI oscillator trimming value.
  * @retval Trimming Number between 0 and 63.
  */
uint32_t HAL_RCC_CSI_GetTrimming(void)
{
  return LL_RCC_CSI_GetCalibTrimming();
}

/**
  * @brief  Get the CSI oscillator calibration value.
  * @retval Calibration Number between 0 and 255.
  */
uint32_t  HAL_RCC_CSI_GetCalibration(void)
{
  return LL_RCC_CSI_GetCalibration();
}

/**
  * @brief  RCC CSI ready interrupt callback.
  * @retval None
  */
__WEAK void HAL_RCC_CSI_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_CSI_ReadyCallback must be implemented in the user file
   */
}

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
  * @retval HAL_OK LSI oscillator enable sequence has been started
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
  * @retval None
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
  * @warning This API must be called under the RCC_IRQHandler().
  * @retval None
  */
void HAL_RCC_IRQHandler(void)
{
  uint32_t it_flags_sources;

  /* Get current IT flags values */
  it_flags_sources = LL_RCC_READ_REG(CIFR);
  it_flags_sources &= LL_RCC_READ_REG(CIER);

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
#endif /* LSE_VALUE */

  if ((it_flags_sources & LL_RCC_IT_HSIRDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_HSIRDY);
    HAL_RCC_HSI_ReadyCallback();
  }

  if ((it_flags_sources & LL_RCC_IT_HSI48RDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_HSI48RDY);
    HAL_RCC_HSI48_ReadyCallback();
  }

  if ((it_flags_sources & LL_RCC_IT_CSIRDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_CSIRDY);
    HAL_RCC_CSI_ReadyCallback();
  }

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

  if ((it_flags_sources & LL_RCC_IT_PLL2RDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_PLL2RDY);
    HAL_RCC_PLL2_ReadyCallback();
  }

  if ((it_flags_sources & LL_RCC_IT_PLL3RDY) != 0U)
  {
    LL_RCC_ClearFlag(LL_RCC_IT_PLL3RDY);
    HAL_RCC_PLL3_ReadyCallback();
  }
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
  *                   Source is not enabled
  *                   Output PLL1P not enabled to switch to PLLCLK\n
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
  return (hal_rcc_sysclk_src_t)(uint32_t)((LL_RCC_GetSysClkSource() >> RCC_CFGR_SWS_Pos) << RCC_CFGR_SW_Pos);
}

/**
  * @brief  Set the system clock (CPRE) divider.
  * @param  prescaler  Prescaler value based on @ref hal_rcc_sysclk_prescaler_t
  */
void HAL_RCC_SetSysClkPrescaler(hal_rcc_sysclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_SYSCLK(prescaler));

  LL_RCC_SetSysPrescaler((uint32_t)prescaler);
}

/**
  * @brief  Set the ACLK (AXI Clock) and HCLK (AHB clock) prescaler.
  * @param  prescaler  Prescaler value based on @ref hal_rcc_aclk_prescaler_t
  */
void HAL_RCC_SetACLKPrescaler(hal_rcc_aclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_ACLK(prescaler));

  LL_RCC_SetBMPrescaler((uint32_t)prescaler);
}

/**
  * @brief  Set the PCLK1 (APB1 clock) prescaler.
  * @param prescaler  Prescaler value based on @ref hal_rcc_pclk_prescaler_t
  */
void HAL_RCC_SetPCLK1Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB1Prescaler(((uint32_t)prescaler) << RCC_APBCFGR_PPRE1_Pos);
}

/**
  * @brief  Set the PCLK2 (APB2 clock) prescaler.
  * @param prescaler  Prescaler value based on @ref hal_rcc_pclk_prescaler_t
  */
void HAL_RCC_SetPCLK2Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB2Prescaler(((uint32_t)prescaler) << RCC_APBCFGR_PPRE2_Pos);
}

/**
  * @brief  Set the PCLK4 (APB4 clock) prescaler.
  * @param prescaler  Prescaler value based on @ref hal_rcc_pclk_prescaler_t
  */
void HAL_RCC_SetPCLK4Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB4Prescaler(((uint32_t)prescaler) << RCC_APBCFGR_PPRE4_Pos);
}

/**
  * @brief  Get the system clock prescaler (CPRE).
  * @retval hal_rcc_sysclk_prescaler_t Prescaler value
  */
hal_rcc_sysclk_prescaler_t HAL_RCC_GetSysClkPrescaler(void)
{
  return (hal_rcc_sysclk_prescaler_t)LL_RCC_GetSysPrescaler();
}

/**
  * @brief  Get the ACLK (AXI bus clock), AHB (HCLK bus) clock prescaler.
  * @retval hal_rcc_aclk_prescaler_t Prescaler value
  */
hal_rcc_aclk_prescaler_t HAL_RCC_GetACLKPrescaler(void)
{
  return (hal_rcc_aclk_prescaler_t)LL_RCC_GetBMPrescaler();
}

/**
  * @brief  Get the APB1 bus clock prescaler (PCLK1).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK1Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB1Prescaler() >> RCC_APBCFGR_PPRE1_Pos);
}

/**
  * @brief  Get the APB2 bus clock prescaler (PCLK2).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK2Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB2Prescaler() >> RCC_APBCFGR_PPRE2_Pos);
}

/**
  * @brief  Get the APB4 bus clock prescaler (PCLK4).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK4Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB4Prescaler() >> RCC_APBCFGR_PPRE4_Pos);
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
  ASSERT_DBG_PARAM(IS_RCC_SYSCLK(p_config->sysclk_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_ACLK(p_config->aclk_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk1_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk2_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk4_prescaler));

  /* Configure prescalers for the available Bus */
  LL_RCC_SetSysPrescaler((uint32_t)p_config->sysclk_prescaler);

  LL_RCC_ConfigBusClock((uint32_t)p_config->aclk_prescaler,
                        ((uint32_t)p_config->pclk1_prescaler |
                         (uint32_t)((uint32_t)p_config->pclk2_prescaler << (RCC_APBCFGR_PPRE2_Pos)) |
                         (uint32_t)((uint32_t)p_config->pclk4_prescaler << (RCC_APBCFGR_PPRE4_Pos))));

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
  p_config->sysclk_prescaler = (hal_rcc_sysclk_prescaler_t)LL_RCC_GetSysPrescaler();
  p_config->aclk_prescaler = (hal_rcc_aclk_prescaler_t)LL_RCC_GetBMPrescaler();
  p_config->pclk1_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB1Prescaler() >> RCC_APBCFGR_PPRE1_Pos);
  p_config->pclk2_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB2Prescaler() >> RCC_APBCFGR_PPRE2_Pos);
  p_config->pclk4_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB4Prescaler() >> RCC_APBCFGR_PPRE4_Pos);
}

/**
  * @brief   Return the SYSCLK frequency.
  * @note    The system frequency computed by this function is calculated based on the predefined constant and
  *          the selected clock source. Its value can slightly differ from the real frequency in the chip.
  * @note    If SYSCLK source is HSI, function returns values based on HSI_VALUE.
  * @note    If SYSCLK source is CSI, function returns values based on CSI_VALUE.
  * @note    If SYSCLK source is HSE, function returns values based on HSE_VALUE.
  * @note    If SYSCLK source is PLL1, function returns values based on HSI_VALUE, \
  *          CSI_VALUE or HSE_VALUE multiplied/divided by the PLL factors.
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
  hal_rcc_pll_output_freq_t pll_clocks;

  if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
    sysclockfreq = RCC_HSI_GetClockFreq();
  }

  else if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_CSI)
  {
    sysclockfreq = CSI_VALUE;
  }
#if defined(HSE_VALUE)

  else if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
  {
    sysclockfreq = HSE_VALUE;
  }
#endif /* HSE_VALUE */

  else
  {
    HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
    sysclockfreq = pll_clocks.pll_p_freq;
  }
  sysclockfreq = sysclockfreq >> CPUPrescTable[LL_RCC_GetSysPrescaler()];

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
  return HAL_RCC_GetSYSCLKFreq() >> AHBPrescTable[LL_RCC_GetBMPrescaler()];
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
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB1Prescaler() >> RCC_APBCFGR_PPRE1_Pos]);
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
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB2Prescaler() >> RCC_APBCFGR_PPRE2_Pos]);
}

/**
  * @brief  Return the PCLK4 frequency.
  * @warning Each time PCLK4 changes, this function must be called to update the
  *          right PCLK4 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK4 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK4Freq(void)
{
  /* Get HCLK source and Compute PCLK4 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB4Prescaler() >> RCC_APBCFGR_PPRE4_Pos]);
}

/**
  * @brief  Return the SysTick clock frequency.
  * @retval uint32_t  SysTick frequency in Hz
  * @note   This function returns the RCC systick clock frequency. Depending on the cortex systick clock source
  *         selection, the systick core frequency is equal to this frequency or to the system frequency.
  */
uint32_t HAL_RCC_GetSysTickExternalClkFreq(void)
{
  return (HAL_RCC_GetSYSCLKFreq() >> 3);
}

/**
  * @}
  */


/** @addtogroup RCC_Exported_Functions_Group1_3
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
  * @note FracN value can be modified on-the-fly (with PLL running) using HAL_RCC_PLL1_SetFRACN() function.
  */
hal_status_t HAL_RCC_PLL1_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLL_SOURCE(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLSSCG_STATE(p_config->pll_sscg_state));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));
  ASSERT_DBG_PARAM(IS_RCC_PLL1P_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLS_VALUE(p_config->pll_s));
  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));
  ASSERT_DBG_PARAM(IS_RCC_PLL_INPUT_RANGE(p_config->pll_input_range));
  ASSERT_DBG_PARAM(IS_RCC_PLL_VCO_RANGE(p_config->pll_vco_range));

  if ((p_config->pll_sscg_state) == HAL_RCC_PLL_SSCG_ENABLE)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_PER_VALUE(p_config->pll_sscg_config.mod_period));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_DEPTH_ADJ_VALUE(p_config->pll_sscg_config.mod_depth_adj));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_SPREAD_MODE(p_config->pll_sscg_config.spread_mode));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_DITH_CTRL_VALUE(p_config->pll_sscg_config.dith_control));
  }

  if (LL_RCC_PLL1_IsReady() == 0U)
  {
    status = RCC_PLL_SetConfig(PLL_1, p_config);
  }

  return status;
}

/**
  * @brief Return the configuration of PLL1.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL1
  */
void HAL_RCC_PLL1_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  RCC_PLL_GetConfig(PLL_1, p_config);
}

/**
  * @brief  Set the fractional part (FRACN) of the multiplication factor of PLL1 on-the-fly.
  * @param  fracn The new fractional value to be set for PLL1.
  * @retval HAL_OK     The FRACN value has been correctly set.
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
    /* Wait at least 2 refx_ck (PLL1 input source divided by M) period to make sure next latched value will be taken
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
  * @brief Enable output(s) of PLL1.
  * @param output Output to enable for PLL1
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_S
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
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_S
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
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_P
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_Q
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_S
  */
uint32_t HAL_RCC_PLL1_GetOutput(void)
{
  return LL_RCC_PLL1_GetOutput();
}

/**
  * @brief  Enable PLL1.
  * @note   If PLL1 is not enabled, enable it and wait for RDY state.
  * @retval HAL_OK    PLL1 correctly enabled or already enabled.
  * @retval HAL_ERROR Timeout detected during enabling of the PLL1
  */
hal_status_t HAL_RCC_PLL1_Enable(void)
{
  hal_status_t status = HAL_OK;
  /* If PLL not enabled => enable it and wait for RDY state (error only if problem to enable) */
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
  * @retval HAL_OK PLL1 enable sequence has been started
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
  * @warning To ensure a correct behavior of the PLL1, all PLL1 outputs must be disabled before disabling the PLL1.
  *          This is done by calling HAL_RCC_PLL1_DisableOutput().
  * @retval HAL_OK    PLL1 correctly disabled or already disabled.
  * @retval HAL_ERROR PLL1 is used as system level and cannot be disabled\n
  *                   Timeout detected during disabling of the PLL1
  */
hal_status_t HAL_RCC_PLL1_Disable(void)
{
  hal_status_t status = HAL_ERROR;

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
  * @retval None
  */
__WEAK void HAL_RCC_PLL1_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_PLL1_ReadyCallback must be implemented in the user file
   */
}

/**
  * @brief    Disable PLL1 for power consumption perspective.
  * @warning  To enable again PLL1, a new configuration must be applied.
  * @details  This function resets all the parameters which might impact power like divm, outputs...
  * @note     As the source is shared with other PLLs, it is not reset
  * @retval HAL_OK    PLL1 is correctly disabled.
  * @retval HAL_ERROR Output is used as system level and cannot be disabled\n
  *                   Timeout to disable PLL1
  */
hal_status_t HAL_RCC_PLL1_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  if (HAL_RCC_GetSYSCLKSource() != HAL_RCC_SYSCLK_SRC_PLLCLK)
  {
    LL_RCC_PLL1_DisableOutput(LL_RCC_PLL1_OUTPUT_P | LL_RCC_PLL1_OUTPUT_Q | LL_RCC_PLL1_OUTPUT_S);

    LL_RCC_PLL1_Disable();
    if (RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U) == HAL_OK)
    {
      /* To save power disable the PLL1 DIVM */
      LL_RCC_CLEAR_BIT(PLLCKSELR, RCC_PLLCKSELR_DIVM1);

      status = HAL_OK;
    }
  }

  return status;
}
/**
  * @brief  Returns the PLL1 clock frequencies: pll_p_freq, pll_q_freq, pll_r_freq and pll_s_freq.
  * @param  p_clk Contains the frequency for each PLL1 output (in Hz).
  * @note   The PLL1 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or CSI_VALUE multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL1CLK changes, this function must be called to update the
  *          right PLL1CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL1_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;
  p_clk->pll_s_freq = 0U;
  p_clk->pll_t_freq = 0U;

  /* If PLL1 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL1_IsReady() == 1U)
  {
    RCC_PLL_GetClockFreq(PLL_1, p_clk);
  }
}

/**
  * @}
  */


/** @addtogroup RCC_Exported_Functions_Group1_4
  * @{
  */

/**
  * @brief   Configure PLL2 without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLL2 is well deactivated (if enabled exit from this function)
  *           - Configure the PLL2 with full list of parameters
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL2
  * @retval HAL_OK            PLL2 has been correctly configured
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR         PLL2 is already enabled and can not be modified.
  * @note FracN value can be modified on-the-fly (with PLL running) using HAL_RCC_PLL2_SetFRACN() function.
  */
hal_status_t HAL_RCC_PLL2_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLL_SOURCE(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLSSCG_STATE(p_config->pll_sscg_state));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));
  ASSERT_DBG_PARAM(IS_RCC_PLLP_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLR_VALUE(p_config->pll_r));
  ASSERT_DBG_PARAM(IS_RCC_PLLS_VALUE(p_config->pll_s));
  ASSERT_DBG_PARAM(IS_RCC_PLLT_VALUE(p_config->pll_t));
  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));
  ASSERT_DBG_PARAM(IS_RCC_PLL_INPUT_RANGE(p_config->pll_input_range));
  ASSERT_DBG_PARAM(IS_RCC_PLL_VCO_RANGE(p_config->pll_vco_range));

  if ((p_config->pll_sscg_state) == HAL_RCC_PLL_SSCG_ENABLE)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_PER_VALUE(p_config->pll_sscg_config.mod_period));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_DEPTH_ADJ_VALUE(p_config->pll_sscg_config.mod_depth_adj));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_SPREAD_MODE(p_config->pll_sscg_config.spread_mode));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_DITH_CTRL_VALUE(p_config->pll_sscg_config.dith_control));
  }

  if (LL_RCC_PLL2_IsReady() == 0U)
  {
    status = RCC_PLL_SetConfig(PLL_2, p_config);
  }

  return status;
}

/**
  * @brief Return the configuration of PLL2.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL2
  */
void HAL_RCC_PLL2_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  RCC_PLL_GetConfig(PLL_2, p_config);
}

/**
  * @brief  Set the fractional part (FRACN) of the multiplication factor of PLL2 on-the-fly.
  * @param  fracn The new fractional value to be set for PLL2.
  * @retval HAL_OK     The FRACN value has been correctly set.
  */
hal_status_t HAL_RCC_PLL2_SetFRACN(uint16_t fracn)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(fracn));

  /* FRACN2 on-the-fly value update */
  if (LL_RCC_PLL2_GetFRACN() != fracn)
  {
    LL_RCC_PLL2_DisableFRACN();

    tickstart = HAL_GetTick();
    /* Wait at least 2 refx_ck (PLL2 input source divided by M) period to make sure next latched value will be taken
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
  * @brief Enable output(s) of PLL2.
  * @param output Output to enable for PLL2
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_R
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_S
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_T
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
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_S
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_T
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
  *            @arg @ref HAL_RCC_PLL2_OUTPUT_S
  *            @arg @ref HAL_RCC_PLL2_OUTPUT_T
  */
uint32_t HAL_RCC_PLL2_GetOutput(void)
{
  return LL_RCC_PLL2_GetOutput();
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
  * @brief   Disable PLL2.
  * @warning To ensure a correct behavior of the PLL2, all PLL2 outputs must be disabled before disabling the PLL2.
  *          This is done by calling HAL_RCC_PLL2_DisableOutput()
  * @retval HAL_OK    PLL2 correctly disabled or already disabled.
  * @retval HAL_ERROR Timeout detected during disabling of the PLL2
  */
hal_status_t HAL_RCC_PLL2_Disable(void)
{
  LL_RCC_PLL2_Disable();
  LL_RCC_DisableIT(LL_RCC_IT_PLL2RDY);

  return RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 0U);
}

/**
  * @brief  Enable PLL2 in interrupt mode.
  * @note   This function only enables the PLL2 and the corresponding ready interrupt.
  *         When PLL2 is ready, the callback HAL_RCC_PLL2_ReadyCallback() is invoked.
  * @retval HAL_OK PLL2 enable sequence has been started
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
  * @retval None
  */
__WEAK void HAL_RCC_PLL2_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_PLL2_ReadyCallback must be implemented in the user file
   */
}

/**
  * @brief    Disable PLL2 for power consumption perspective.
  * @warning  To enable again PLL2, a new configuration must be applied.
  * @details  This function allow to reset all the parameters which might impact power
  *           like PLLSRC, outputs...
  * @retval HAL_OK    PLL2 is correctly disabled\n
  * @retval HAL_ERROR Timeout to disable PLL2.
  */
hal_status_t HAL_RCC_PLL2_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  LL_RCC_PLL2_DisableOutput(LL_RCC_PLL2_OUTPUT_P | LL_RCC_PLL2_OUTPUT_Q | LL_RCC_PLL2_OUTPUT_R | \
                            LL_RCC_PLL2_OUTPUT_S | LL_RCC_PLL2_OUTPUT_T);

  LL_RCC_PLL2_Disable();

  if (RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 0U) == HAL_OK)
  {
    /* To save power disable the PLL2 DIVM */
    LL_RCC_CLEAR_BIT(PLLCKSELR, RCC_PLLCKSELR_DIVM2);

    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Returns the PLL2 clock frequencies: pll_p_freq, pll_q_freq, pll_r_freq, pll_s_freq and pll_t_freq.
  * @param  p_clk Contains the frequency for each PLL2 output (in Hz).
  * @note   The PLL2 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or CSI_VALUE multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL2CLK changes, this function must be called to update the
  *          right PLL2CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL2_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;
  p_clk->pll_s_freq = 0U;
  p_clk->pll_t_freq = 0U;

  /* If PLL2 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL2_IsReady() == 1U)
  {
    RCC_PLL_GetClockFreq(PLL_2, p_clk);
  }
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_5
  * @{
  */

/**
  * @brief   Configure PLL3 without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLL3 is well deactivated (if enabled exit from this function)
  *           - Configure the PLL3 with full list of parameters
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL3
  * @retval HAL_OK            PLL3 has been correctly configured
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR         PLL3 is already enabled and can not be modified.
  * @note FracN value can be modified on-the-fly (with PLL running) using HAL_RCC_PLL3_SetFRACN() function.
  */
hal_status_t HAL_RCC_PLL3_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLL_SOURCE(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLSSCG_STATE(p_config->pll_sscg_state));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));
  ASSERT_DBG_PARAM(IS_RCC_PLLP_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLR_VALUE(p_config->pll_r));
  ASSERT_DBG_PARAM(IS_RCC_PLLS_VALUE(p_config->pll_s));
  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));
  ASSERT_DBG_PARAM(IS_RCC_PLL_INPUT_RANGE(p_config->pll_input_range));
  ASSERT_DBG_PARAM(IS_RCC_PLL_VCO_RANGE(p_config->pll_vco_range));

  if ((p_config->pll_sscg_state) == HAL_RCC_PLL_SSCG_ENABLE)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_PER_VALUE(p_config->pll_sscg_config.mod_period));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_DEPTH_ADJ_VALUE(p_config->pll_sscg_config.mod_depth_adj));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_SPREAD_MODE(p_config->pll_sscg_config.spread_mode));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_DITH_CTRL_VALUE(p_config->pll_sscg_config.dith_control));
  }

  if (LL_RCC_PLL3_IsReady() == 0U)
  {
    status = RCC_PLL_SetConfig(PLL_3, p_config);
  }

  return status;
}

/**
  * @brief Return the configuration of PLL3.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL3
  */
void HAL_RCC_PLL3_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  RCC_PLL_GetConfig(PLL_3, p_config);
}

/**
  * @brief  Set the fractional part (FRACN) of the multiplication factor of PLL3 on-the-fly.
  * @param  fracn The new fractional value to be set for PLL3.
  * @retval HAL_OK     The FRACN value has been correctly set.
  */
hal_status_t HAL_RCC_PLL3_SetFRACN(uint16_t fracn)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(fracn));

  /* FRACN3 on-the-fly value update */
  if (LL_RCC_PLL3_GetFRACN() != fracn)
  {
    LL_RCC_PLL3_DisableFRACN();

    tickstart = HAL_GetTick();
    /* Wait at least 2 refx_ck (PLL3 input source divided by M) period to make sure next latched value will be taken
      into account. */
    while ((HAL_GetTick() - tickstart) < RCC_PLL_FRAC_WAIT_VALUE)
    {
    }

    LL_RCC_PLL3_SetFRACN(fracn);

    /* Enable PLL3FRACN to latch the new value. */
    LL_RCC_PLL3_EnableFRACN();
  }

  return HAL_OK;
}

/**
  * @brief  Get the current fractional part (FRACN) of the multiplication factor of PLL3.
  * @retval The current fractional value of PLL3.
  */
uint16_t HAL_RCC_PLL3_GetFRACN(void)
{
  return (uint16_t)LL_RCC_PLL3_GetFRACN();
}

/**
  * @brief Enable output(s) of PLL3.
  * @param output Output to enable for PLL3
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_R
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_S
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been activated
  */
hal_status_t HAL_RCC_PLL3_EnableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL3_OUTPUT(output));

  LL_RCC_PLL3_EnableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Disable output(s) of PLL3.
  * @param  output Output to disable for PLL3
  *                It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_R
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_S
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been deactivated
  */
hal_status_t HAL_RCC_PLL3_DisableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL3_OUTPUT(output));

  LL_RCC_PLL3_DisableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Return the enabled output(s) of PLL3.
  * @retval output PLL3 outputs.
  *         It can be a combination of the following values:
  *            @arg @ref HAL_RCC_PLL3_OUTPUT_P
  *            @arg @ref HAL_RCC_PLL3_OUTPUT_Q
  *            @arg @ref HAL_RCC_PLL3_OUTPUT_R
  *            @arg @ref HAL_RCC_PLL3_OUTPUT_S
  */
uint32_t HAL_RCC_PLL3_GetOutput(void)
{
  return LL_RCC_PLL3_GetOutput();
}

/**
  * @brief  Enable PLL3.
  * @note   If PLL is not enabled, enable it and wait for RDY state.
  * @retval HAL_OK    PLL3 correctly enabled or already enabled.
  * @retval HAL_ERROR Timeout detected during enabling of the PLL3
  */
hal_status_t HAL_RCC_PLL3_Enable(void)
{
  hal_status_t status = HAL_OK;
  /* If PLL not enabled => enable it and wait for RDY state (error only if pb to enable) */
  if (LL_RCC_PLL3_IsReady() == 0U)
  {
    LL_RCC_PLL3_Enable();
    status = RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 1U);
  }

  return status;
}


/**
  * @brief  Enable PLL3 in interrupt mode.
  * @note   This function only enables the PLL3 and the corresponding ready interrupt.
  *         When PLL3 is ready, the callback HAL_RCC_PLL3_ReadyCallback() is invoked.
  * @retval HAL_OK PLL3 enable sequence has been started
  */
hal_status_t HAL_RCC_PLL3_Enable_IT(void)
{
  LL_RCC_EnableIT(LL_RCC_IT_PLL3RDY);

  if (LL_RCC_PLL3_IsReady() == 0U)
  {
    LL_RCC_PLL3_Enable();
  }

  return HAL_OK;
}


/**
  * @brief   Disable PLL3.
  * @warning To ensure a correct behavior of the PLL3, all PLL3 outputs must be disabled before disabling the PLL3.
  *          This is done by calling HAL_RCC_PLL3_DisableOutput()
  * @retval HAL_OK    PLL3 correctly disabled or already disabled.
  * @retval HAL_ERROR Timeout detected during disabling of the PLL3
  */
hal_status_t HAL_RCC_PLL3_Disable(void)
{
  LL_RCC_PLL3_Disable();
  LL_RCC_DisableIT(LL_RCC_IT_PLL3RDY);

  return RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 0U);
}

/**
  * @brief Check if the PLL3 is ready.
  * @retval HAL_RCC_PLL_ENABLED  PLL3 is ready
  * @retval HAL_RCC_PLL_DISABLED PLL3 is not ready
  */
hal_rcc_pll_status_t HAL_RCC_PLL3_IsReady(void)
{
  return (hal_rcc_pll_status_t)LL_RCC_PLL3_IsReady();
}

/**
  * @brief  RCC PLL3 ready interrupt callback.
  * @retval None
  */
__WEAK void HAL_RCC_PLL3_ReadyCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_PLL3_ReadyCallback must be implemented in the user file
   */
}

/**
  * @brief    Disable PLL3 for power consumption perspective.
  * @warning  To enable again PLL3, a new configuration must be applied.
  * @details  This function allow to reset all the parameters which might impact power
  *           like PLLSRC, outputs...
  * @retval HAL_OK    PLL3 is correctly disabled\n
  * @retval HAL_ERROR Timeout to disable PLL3.
  */
hal_status_t HAL_RCC_PLL3_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  LL_RCC_PLL3_DisableOutput(LL_RCC_PLL3_OUTPUT_P | LL_RCC_PLL3_OUTPUT_Q | LL_RCC_PLL3_OUTPUT_R | \
                            LL_RCC_PLL3_OUTPUT_S);

  LL_RCC_PLL3_Disable();

  if (RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 0U) == HAL_OK)
  {
    /* To save power disable the PLL3 DIVM */
    LL_RCC_CLEAR_BIT(PLLCKSELR, RCC_PLLCKSELR_DIVM3);

    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Returns the PLL3 clock frequencies: pll_p_freq, pll_q_freq, pll_r_freq and pll_s_freq.
  * @param  p_clk Contains the frequency for each PLL3 output (in Hz).
  * @note   The PLL3 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or CSI_VALUE multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL3CLK changes, this function must be called to update the
  *          right PLL3CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL3_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;
  p_clk->pll_s_freq = 0U;
  p_clk->pll_t_freq = 0U;

  /* If PLL3 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL3_IsReady() == 1U)
  {
    RCC_PLL_GetClockFreq(PLL_3, p_clk);
  }
}

/**
  * @}
  */

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
  *            @arg HAL_RCC_MCO2_SRC_PLL2P
  *            @arg HAL_RCC_MCO2_SRC_HSE
  *            @arg HAL_RCC_MCO2_SRC_PLL1P
  *            @arg HAL_RCC_MCO2_SRC_CSI
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
  * @note   Prior to enabling the HSE Clock Security System, HSE oscillator must be enabled.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (HSE Clock Security System Interrupt, HSECSSI),
  *         allowing the MCU to perform rescue operations. The HSECSS interrupt is linked to
  *         the Cortex-M7 NMI (Non-Maskable Interrupt) exception vector.
  * @note   The HSE Clock Security System can only be cleared by reset.
  */
void HAL_RCC_HSE_EnableCSS(void)
{
  LL_RCC_HSE_EnableCSS();
}

/**
  * @brief Handle the RCC HSE Clock Security System interrupt request.
  * @warning This API must be called under the NMI_Handler().
  * @retval HAL_OK    NMI has been managed and NMI_Handler() might exit
  * @retval HAL_ERROR NMI has not been managed and NMI_Handler() might exit
  */
hal_status_t  HAL_RCC_NMI_IRQHandler(void)
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
  * @brief  RCC HSE Clock Security System interrupt callback.
  * @retval HAL_OK    HSE CSS interrupt has been correctly managed
  * @retval HAL_ERROR HSE CSS interrupt has not been correctly managed
  */
__WEAK hal_status_t HAL_RCC_HSE_CSSCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_HSE_CSSCallback must be implemented in the user file
   */
  /* Status to be updated to HAL_OK when the user callback managed the HSECSS error */
  return HAL_ERROR;
}

#endif /* HSE_VALUE */

/**
  * @brief   Configure the oscillator clock source for wakeup from Stop and CSS backup clock.
  * @param   wakeup_clk  Wakeup clock
  *          This parameter can be one of the following values:
  *            @arg @ref HAL_RCC_STOP_WAKEUPCLOCK_HSI  HSI oscillator selection
  *            @arg @ref HAL_RCC_STOP_WAKEUPCLOCK_CSI  CSI oscillator selection
  * @warning This function must not be called after the Clock Security System on HSE has been enabled.
  */
void HAL_RCC_SetClockAfterWakeFromStop(hal_rcc_stop_wakeup_clk_t wakeup_clk)
{
  ASSERT_DBG_PARAM(IS_RCC_STOP_WAKEUPCLOCK(wakeup_clk));

  LL_RCC_SetClkAfterWakeFromStop((uint32_t)wakeup_clk);
}

/**
  * @brief   Get the oscillator clock source for wakeup from Stop and CSS backup clock.
  * @retval  hal_rcc_stop_wakeup_clk_t  Wakeup clock source
  */
hal_rcc_stop_wakeup_clk_t HAL_RCC_GetClockAfterWakeFromStop(void)
{
  return (hal_rcc_stop_wakeup_clk_t)LL_RCC_GetClkAfterWakeFromStop();
}

/**
  * @brief  Configure the oscillator Kernel clock source for wakeup from Stop.
  * @param  wakeup_clk Kernel Wakeup clock
  */
void HAL_RCC_SetKernelClkAfterWakeFromStop(hal_rcc_stop_wakeup_kerclk_t wakeup_clk)
{
  ASSERT_DBG_PARAM(IS_RCC_STOP_KERWAKEUPCLOCK(wakeup_clk));

  LL_RCC_SetKerClkAfterWakeFromStop((uint32_t)wakeup_clk);
}

/**
  * @brief  Get the oscillator Kernel clock source for wakeup from Stop.
  * @retval hal_rcc_stop_wakeup_kerclk_t Kernel Wakeup clock
  */
hal_rcc_stop_wakeup_kerclk_t HAL_RCC_GetKernelClkAfterWakeFromStop(void)
{
  return (hal_rcc_stop_wakeup_kerclk_t)LL_RCC_GetKerClkAfterWakeFromStop();
}

#if defined(LSE_VALUE)
/**
  * @brief  Enable the LSE Clock Security System.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator is to be enabled
  *         with HAL_RCC_LSE_Enable() and the LSE oscillator clock is to be selected as RTC
  *         clock with HAL_RCC_RTC_SetKernelClkSource().
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
  * @brief  Rearm Clock Security System on LSE.
  * @note   Clock security system can be re-enabled after an LSE failure detection.
  *         Before re-enabling it, LSECSSON must be set to 0.
  */
void HAL_RCC_LSE_RearmCSS(void)
{
  LL_RCC_LSE_SetRearmCSS();
  LL_RCC_LSE_ResetRearmCSS();
}

/**
  * @brief   Handle the RCC LSE Clock Security System interrupt request.
  * @warning This API must be called under the RCC_LSECSS_IRQHandler().
  * @warning LSECSS NVIC interrupt line must be previously configured and enabled to detect this interruption.
  * @warning LSECSS EXTI interrupt line must be previously configured and enabled to wake-up the system
  */
void HAL_RCC_LSECSS_IRQHandler(void)
{
  if (LL_RCC_IsActiveFlag(LL_RCC_IT_LSECSS) != 0U)
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
  if (LL_PWR_IsEnabledBackupDomainWriteProtection() != 0U)
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
  if (LL_PWR_IsEnabledBackupDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_DisableRTC();

  return HAL_OK;
}

/**
  * @brief Set HSE Prescalers for RTC Clock.
  * @param prescaler parameter can be a value between 0 and 63 with 0 an 1 values meaning no clock output
  * @note  Prescaler must be correctly set to ensure that the clock supplied to the
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

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group4
  * @{
  */

/**
  * @brief  Configure Common Peripheral kernel clock source.
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_PERCLK_SRC_HSI
  *         @arg @ref HAL_RCC_PERCLK_SRC_CSI
  *         @arg @ref HAL_RCC_PERCLK_SRC_HSE
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_PERCLK_SetSource(hal_rcc_perclk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_PERCLK(clk_src));

  LL_RCC_PERCLK_SetSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Get Common Peripheral kernel clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_perclk_src_t
  */
hal_rcc_perclk_src_t HAL_RCC_PERCLK_GetSource(void)
{
  return (hal_rcc_perclk_src_t)LL_RCC_PERCLK_GetSource();
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group5
  * @{
  */

/**
  * @brief  Disable all kernel clocks.
  * @note   This function is used to disable all kernel clocks to reduce power consumption.
  * @note   FMC, SDMMC, I2C, I3C1 and DAC kernel clocks can not be disabled.
  * @retval HAL_OK    All kernel clocks have been disabled
  */
hal_status_t HAL_RCC_DisableAllKernelClocks(void)
{
  LL_RCC_SetXSPIClockSource(LL_RCC_XSPI1_CLKSOURCE_NONE);
  LL_RCC_SetUSBOTGFSClockSource(LL_RCC_USBOTGFS_CLKSOURCE_NONE);
  LL_RCC_SetADFClockSource(LL_RCC_ADF1_CLKSOURCE_NONE);
  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_NONE);
  LL_RCC_SetUARTClockSource(LL_RCC_UART234578_CLKSOURCE_NONE);
  LL_RCC_SetSPIClockSource(LL_RCC_SPI1_CLKSOURCE_NONE);
  LL_RCC_SetSPIClockSource(LL_RCC_SPI6_CLKSOURCE_NONE);
  LL_RCC_SetSPIClockSource(LL_RCC_SPI23_CLKSOURCE_NONE);
  LL_RCC_SetSPIClockSource(LL_RCC_SPI45_CLKSOURCE_NONE);
  LL_RCC_SetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE_NONE);
  LL_RCC_SetLPTIMClockSource(LL_RCC_LPTIM23_CLKSOURCE_NONE);
  LL_RCC_SetLPTIMClockSource(LL_RCC_LPTIM45_CLKSOURCE_NONE);
  LL_RCC_SetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE_NONE);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART16910_CLKSOURCE_NONE);
  LL_RCC_SetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE_NONE);
  LL_RCC_PERCLK_SetSource(LL_RCC_PER_CLKSOURCE_NONE);

  return HAL_OK;
}

/**
  * @brief  Set the FMC clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_fmc_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_FMC_SetKernelClkSource(hal_rcc_fmc_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_FMC_CLK(clk_src));

  LL_RCC_SetFMCClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SDMMC1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_sdmmc1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SDMMC1_SetKernelClkSource(hal_rcc_sdmmc1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SDMMC1_CLK(clk_src));

  LL_RCC_SetSDMMCClockSource((uint32_t)clk_src);
  return HAL_OK;
}

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

/**
  * @brief  Set the USB OTG FS clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_usbotgfs_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USBOTGFS_SetKernelClkSource(hal_rcc_usbotgfs_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USBOTGFS_CLK(clk_src));

  LL_RCC_SetUSBOTGFSClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the ADF1 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_adf1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_ADF1_SetKernelClkSource(hal_rcc_adf1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ADF1_CLK(clk_src));

  LL_RCC_SetADFClockSource((uint32_t)clk_src);
  return HAL_OK;
}

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
  * @brief  Set the ADC clock divider.
  * @param  prescaler Clock source selection based on @ref hal_rcc_adc_prescaler_t
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
  * @param  prescaler Clock source selection based on @ref hal_rcc_adc_prescaler_t
  * @retval HAL_OK   Clock divider has been set
  */
hal_status_t HAL_RCC_ADC_SetConfigKernelClk(hal_rcc_adc_clk_src_t clk_src, hal_rcc_adc_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_ADC_CLK(clk_src));
  ASSERT_DBG_PARAM(IS_RCC_ADC_PRESCALER(prescaler));

  LL_RCC_ConfigADC((uint32_t)clk_src, (uint32_t)prescaler);
  return HAL_OK;
}

/**
  * @brief  Set the UART4, 5, 7, 8 and USART2, 3 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_uart234578_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_UART234578_SetKernelClkSource(hal_rcc_uart234578_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_UART234578_CLK(clk_src));

  LL_RCC_SetUARTClockSource((uint32_t)clk_src);
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
  * @brief  Set the SPI6 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi6_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI6_SetKernelClkSource(hal_rcc_spi6_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI6_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI23 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi23_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI23_SetKernelClkSource(hal_rcc_spi23_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI23_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI45 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi45_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI45_SetKernelClkSource(hal_rcc_spi45_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI45_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the I2C123 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c123_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C123_SetKernelClkSource(hal_rcc_i2c123_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C123_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

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

/**
  * @brief  Set the LPTIM23 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_lptim23_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPTIM23_SetKernelClkSource(hal_rcc_lptim23_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPTIM23_CLK(clk_src));

  LL_RCC_SetLPTIMClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the LPTIM45 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_lptim45_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPTIM45_SetKernelClkSource(hal_rcc_lptim45_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPTIM45_CLK(clk_src));

  LL_RCC_SetLPTIMClockSource((uint32_t)clk_src);
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

/**
  * @brief  Set the USART1, 6, 10 and UART9 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart16910_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART16910_SetKernelClkSource(hal_rcc_usart16910_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART16910_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
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
  * @brief  Set the DAC3 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac3_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC3_SetKernelClkSource(hal_rcc_dac3_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC3_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC4 clock source.
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac4_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC4_SetKernelClkSource(hal_rcc_dac4_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC4_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC1SH clock source.
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
  * @brief  Get the FMC clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_fmc_clk_src_t
  */
hal_rcc_fmc_clk_src_t HAL_RCC_FMC_GetKernelClkSource(void)
{
  return (hal_rcc_fmc_clk_src_t)LL_RCC_GetFMCClockSource(LL_RCC_FMC_CLKSOURCE);
}

/**
  * @brief  Get the SDMMC1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_sdmmc1_clk_src_t
  */
hal_rcc_sdmmc1_clk_src_t HAL_RCC_SDMMC1_GetKernelClkSource(void)
{
  return (hal_rcc_sdmmc1_clk_src_t)LL_RCC_GetSDMMCClockSource(LL_RCC_SDMMC1_CLKSOURCE);
}

/**
  * @brief  Get the XSPI1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_xspi1_clk_src_t
  */
hal_rcc_xspi1_clk_src_t HAL_RCC_XSPI1_GetKernelClkSource(void)
{
  return (hal_rcc_xspi1_clk_src_t)LL_RCC_GetXSPIClockSource(LL_RCC_XSPI1_CLKSOURCE);
}

/**
  * @brief  Get the USB FS clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_usbotgfs_clk_src_t
  */
hal_rcc_usbotgfs_clk_src_t HAL_RCC_USBOTGFS_GetKernelClkSource(void)
{
  return (hal_rcc_usbotgfs_clk_src_t)LL_RCC_GetUSBOTGFSClockSource(LL_RCC_USBOTGFS_CLKSOURCE);
}

/**
  * @brief  Get the ADF1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_adf1_clk_src_t
  */
hal_rcc_adf1_clk_src_t HAL_RCC_ADF1_GetKernelClkSource(void)
{
  return (hal_rcc_adf1_clk_src_t)LL_RCC_GetADFClockSource(LL_RCC_ADF1_CLKSOURCE);
}

/**
  * @brief  Get the ADC clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_adc_clk_src_t
  */
hal_rcc_adc_clk_src_t HAL_RCC_ADC_GetKernelClkSource(void)
{
  return (hal_rcc_adc_clk_src_t)LL_RCC_GetADCClockSource(LL_RCC_ADC_CLKSOURCE);
}

/**
  * @brief  Get the ADC clock prescaler.
  * @retval clk_src Clock prescaler based on @ref hal_rcc_adc_prescaler_t
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
  * @brief  Get the UART4, 5, 7, 8 and USART2, 3 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_uart234578_clk_src_t
  */
hal_rcc_uart234578_clk_src_t HAL_RCC_UART234578_GetKernelClkSource(void)
{
  return (hal_rcc_uart234578_clk_src_t)LL_RCC_GetUARTClockSource(LL_RCC_UART234578_CLKSOURCE);
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
  * @brief  Get the SPI6 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_spi6_clk_src_t
  */
hal_rcc_spi6_clk_src_t HAL_RCC_SPI6_GetKernelClkSource(void)
{
  return (hal_rcc_spi6_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI6_CLKSOURCE);
}

/**
  * @brief  Get the SPI23 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_spi23_clk_src_t
  */
hal_rcc_spi23_clk_src_t HAL_RCC_SPI23_GetKernelClkSource(void)
{
  return (hal_rcc_spi23_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI23_CLKSOURCE);
}

/**
  * @brief  Get the SPI45 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_spi45_clk_src_t
  */
hal_rcc_spi45_clk_src_t HAL_RCC_SPI45_GetKernelClkSource(void)
{
  return (hal_rcc_spi45_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI45_CLKSOURCE);
}

/**
  * @brief  Get the I2C123 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_i2c123_clk_src_t
  */
hal_rcc_i2c123_clk_src_t HAL_RCC_I2C123_GetKernelClkSource(void)
{
  return (hal_rcc_i2c123_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C123_CLKSOURCE);
}

/**
  * @brief  Get the I3C1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_i3c1_clk_src_t
  */
hal_rcc_i3c1_clk_src_t HAL_RCC_I3C1_GetKernelClkSource(void)
{
  return (hal_rcc_i3c1_clk_src_t)LL_RCC_GetI3CClockSource(LL_RCC_I3C1_CLKSOURCE);
}

/**
  * @brief  Get the LPTIM1 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_lptim1_clk_src_t
  */
hal_rcc_lptim1_clk_src_t HAL_RCC_LPTIM1_GetKernelClkSource(void)
{
  return (hal_rcc_lptim1_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE);
}

/**
  * @brief  Get the LPTIM23 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_lptim23_clk_src_t
  */
hal_rcc_lptim23_clk_src_t HAL_RCC_LPTIM23_GetKernelClkSource(void)
{
  return (hal_rcc_lptim23_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM23_CLKSOURCE);
}

/**
  * @brief  Get the LPTIM45 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_lptim45_clk_src_t
  */
hal_rcc_lptim45_clk_src_t HAL_RCC_LPTIM45_GetKernelClkSource(void)
{
  return (hal_rcc_lptim45_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM45_CLKSOURCE);
}

/**
  * @brief  Get the FDCAN clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_fdcan_clk_src_t
  */
hal_rcc_fdcan_clk_src_t HAL_RCC_FDCAN_GetKernelClkSource(void)
{
  return (hal_rcc_fdcan_clk_src_t)LL_RCC_GetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE);
}

/**
  * @brief  Get the USART1, 6, 10 and UART9 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_usart16910_clk_src_t
  */
hal_rcc_usart16910_clk_src_t HAL_RCC_USART16910_GetKernelClkSource(void)
{
  return (hal_rcc_usart16910_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART16910_CLKSOURCE);
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
  * @brief  Get the DAC3 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac3_clk_src_t
  */
hal_rcc_dac3_clk_src_t HAL_RCC_DAC3_GetKernelClkSource(void)
{
  return (hal_rcc_dac3_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC3_CLKSOURCE);
}

/**
  * @brief  Get the DAC4 clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac4_clk_src_t
  */
hal_rcc_dac4_clk_src_t HAL_RCC_DAC4_GetKernelClkSource(void)
{
  return (hal_rcc_dac4_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC4_CLKSOURCE);
}

/**
  * @brief  Get the DAC1SH clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_dac1sh_clk_src_t
  */
hal_rcc_dac1sh_clk_src_t HAL_RCC_DAC1_GetSampleHoldClkSource(void)
{
  return (hal_rcc_dac1sh_clk_src_t)LL_RCC_GetDACSHClockSource(LL_RCC_DAC1SH_CLKSOURCE);
}

/**
  * @brief  Get the RTC clock source.
  * @retval clk_src Clock source based on @ref hal_rcc_rtc_clk_src_t
  */
hal_rcc_rtc_clk_src_t HAL_RCC_RTC_GetKernelClkSource(void)
{
  return (hal_rcc_rtc_clk_src_t)LL_RCC_GetRTCClockSource();
}

/**
  * @brief  Return the peripheral clock frequency for FMC.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_FMC_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetFMCClockSource(LL_RCC_FMC_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_FMC_CLKSOURCE_HCLK5:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_FMC_CLKSOURCE_PLL1Q:

      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_FMC_CLKSOURCE_PLL2R:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_FMC_CLKSOURCE_HSI:

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

/**
  * @brief  Return the peripheral clock frequency for SDMMC.
  * @param  sdmmcx SDMMC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_SDMMC_GetKernelClkFreq(const SDMMC_TypeDef *sdmmcx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)sdmmcx)
  {
    case (uint32_t)SDMMC1:
      frequency = HAL_RCC_SDMMC1_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SDMMC1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SDMMC1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetSDMMCClockSource(LL_RCC_SDMMC1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_SDMMC1_CLKSOURCE_PLL2S:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_s_freq;
      break;

    case LL_RCC_SDMMC1_CLKSOURCE_PLL2T:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_t_freq;
      break;

    default :
      break;
  }

  return frequency;
}

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
    case LL_RCC_XSPI1_CLKSOURCE_HCLK5:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_XSPI1_CLKSOURCE_PLL2S:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_s_freq;
      break;

    case LL_RCC_XSPI1_CLKSOURCE_PLL2T:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_t_freq;
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USBOTGFS.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_USBOTGFS_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSBOTGFSClockSource(LL_RCC_USBOTGFS_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_USBOTGFS_CLKSOURCE_HSI48:

      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        frequency = HSI48_VALUE;
      }
      break;

    case LL_RCC_USBOTGFS_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

#if defined(HSE_VALUE)
    case LL_RCC_USBOTGFS_CLKSOURCE_HSE:

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
  * @brief  Return the peripheral clock frequency for ADF1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ADF1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetADFClockSource(LL_RCC_ADF1_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_ADF1_CLKSOURCE_HCLK1:
      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_ADF1_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_ADF1_CLKSOURCE_PLL3P:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

#if defined(AUDIO_CLOCK_VALUE)
    case LL_RCC_ADF1_CLKSOURCE_AUDIOCLK:

      frequency = AUDIO_CLOCK_VALUE;
      break;
#endif /* AUDIO_CLOCK_VALUE */

    case LL_RCC_ADF1_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

    case LL_RCC_ADF1_CLKSOURCE_HSI:

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

/**
  * @brief  Return the peripheral clock frequency for ADC.
  * @param  adcx ADC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ADC_GetKernelClkFreq(const ADC_TypeDef *adcx)
{
  STM32_UNUSED(adcx);

  return HAL_RCC_ADC1234_GetKernelClkFreq();
}

/**
  * @brief  Return the peripheral clock frequency for ADC.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ADC1234_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetADCClockSource(LL_RCC_ADC_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_ADC_CLKSOURCE_HCLK3:
      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_ADC_CLKSOURCE_TIM:
      frequency = HAL_RCC_TIM_GetKernelClkFreq(NULL);
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

    case LL_RCC_ADC_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_ADC_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_ADC_CLKSOURCE_PER:

      frequency = RCC_PERCLK_GetClockFreq();
      break;

    default:
      break;
  }

  frequency = frequency / RCC_GET_ADC_PRESCALER();

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for UART.
  * @param  uartx USART instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_UART_GetKernelClkFreq(const USART_TypeDef *uartx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)uartx)
  {
    case (uint32_t)USART1:
      frequency = HAL_RCC_USART16910_GetKernelClkFreq();
      break;

    case (uint32_t)USART2:
      frequency = HAL_RCC_UART234578_GetKernelClkFreq();
      break;

    case (uint32_t)USART3:
      frequency = HAL_RCC_UART234578_GetKernelClkFreq();
      break;

    case (uint32_t)UART4:
      frequency = HAL_RCC_UART234578_GetKernelClkFreq();
      break;

    case (uint32_t)UART5:
      frequency = HAL_RCC_UART234578_GetKernelClkFreq();
      break;

    case (uint32_t)USART6:
      frequency = HAL_RCC_USART16910_GetKernelClkFreq();
      break;

    case (uint32_t)UART7:
      frequency = HAL_RCC_UART234578_GetKernelClkFreq();
      break;

    case (uint32_t)UART8:
      frequency = HAL_RCC_UART234578_GetKernelClkFreq();
      break;

    case (uint32_t)UART9:
      frequency = HAL_RCC_USART16910_GetKernelClkFreq();
      break;

    case (uint32_t)USART10:
      frequency = HAL_RCC_USART16910_GetKernelClkFreq();
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
      frequency = HAL_RCC_USART16910_GetKernelClkFreq();
      break;

    case (uint32_t)USART2:
      frequency = HAL_RCC_UART234578_GetKernelClkFreq();
      break;

    case (uint32_t)USART3:
      frequency = HAL_RCC_UART234578_GetKernelClkFreq();
      break;

    case (uint32_t)USART6:
      frequency = HAL_RCC_USART16910_GetKernelClkFreq();
      break;

    case (uint32_t)USART10:
      frequency = HAL_RCC_USART16910_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for UART4, 5, 6, 7, 8 and USART2, 3.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART234578_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_UART234578_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_UART234578_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_UART234578_CLKSOURCE_PLL2Q:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_UART234578_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_UART234578_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;

    case LL_RCC_UART234578_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_UART234578_CLKSOURCE_LSE:

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
  * @brief  Return the peripheral clock frequency for USART1, 6, 10 and UART9.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART16910_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART16910_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_USART16910_CLKSOURCE_PCLK2:

      frequency = HAL_RCC_GetPCLK2Freq();
      break;

    case LL_RCC_USART16910_CLKSOURCE_PLL2Q:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_USART16910_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_USART16910_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;

    case LL_RCC_USART16910_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_USART16910_CLKSOURCE_LSE:

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
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_LPUART1_CLKSOURCE_PCLK4:

      frequency = HAL_RCC_GetPCLK4Freq();
      break;

    case LL_RCC_LPUART1_CLKSOURCE_PLL2Q:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_LPUART1_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_LPUART1_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
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
      frequency = HAL_RCC_SPI23_GetKernelClkFreq();
      break;

    case (uint32_t)SPI3:
      frequency = HAL_RCC_SPI23_GetKernelClkFreq();
      break;

    case (uint32_t)SPI4:
      frequency = HAL_RCC_SPI45_GetKernelClkFreq();
      break;

    case (uint32_t)SPI5:
      frequency = HAL_RCC_SPI45_GetKernelClkFreq();
      break;

    case (uint32_t)SPI6:
      frequency = HAL_RCC_SPI6_GetKernelClkFreq();
      break;

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
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_SPI1_CLKSOURCE_PLL1Q:

      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI1_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_SPI1_CLKSOURCE_PLL3P:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

#if defined(AUDIO_CLOCK_VALUE)
    case LL_RCC_SPI1_CLKSOURCE_AUDIOCLK:

      frequency = AUDIO_CLOCK_VALUE;
      break;
#endif /* AUDIO_CLOCK_VALUE */

    case LL_RCC_SPI1_CLKSOURCE_PER:

      frequency = RCC_PERCLK_GetClockFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI6.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI6_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI6_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_SPI6_CLKSOURCE_PCLK4:

      frequency = HAL_RCC_GetPCLK4Freq();
      break;

    case LL_RCC_SPI6_CLKSOURCE_PLL2Q:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI6_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI6_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;

    case LL_RCC_SPI6_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(HSE_VALUE)
    case LL_RCC_SPI6_CLKSOURCE_HSE:

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
  * @brief  Return the peripheral clock frequency for SPI23.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI23_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI23_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_SPI23_CLKSOURCE_PLL1Q:

      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI23_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_SPI23_CLKSOURCE_PLL3P:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

#if defined(AUDIO_CLOCK_VALUE)
    case LL_RCC_SPI23_CLKSOURCE_AUDIOCLK:

      frequency = AUDIO_CLOCK_VALUE;
      break;
#endif /* AUDIO_CLOCK_VALUE */

    case LL_RCC_SPI23_CLKSOURCE_PER:

      frequency = RCC_PERCLK_GetClockFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI45.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI45_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI45_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_SPI45_CLKSOURCE_PCLK2:

      frequency = HAL_RCC_GetPCLK2Freq();
      break;

    case LL_RCC_SPI45_CLKSOURCE_PLL2Q:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI45_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI45_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;

    case LL_RCC_SPI45_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(HSE_VALUE)
    case LL_RCC_SPI45_CLKSOURCE_HSE:

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
  * @brief  Return the peripheral clock frequency for I2C.
  * @param  i2cx I2C instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I2C_GetKernelClkFreq(const I2C_TypeDef *i2cx)
{
  STM32_UNUSED(i2cx);
  return HAL_RCC_I2C123_GetKernelClkFreq();
}

/**
  * @brief  Return the peripheral clock frequency for I2C123.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I2C123_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C123_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_I2C123_CLKSOURCE_PCLK1:

      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_I2C123_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_I2C123_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;

    case LL_RCC_I2C123_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

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
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_I3C1_CLKSOURCE_PCLK1:

      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_I3C1_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_I3C1_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;

    case LL_RCC_I3C1_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

    default :
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for HRTIM.
  * @param  hrtimx HRTIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_HRTIM_GetKernelClkFreq(const HRTIM_TypeDef *hrtimx)
{
  STM32_UNUSED(hrtimx);
  return HAL_RCC_GetSYSCLKFreq();
}

/**
  * @brief  Return the peripheral clock frequency for HRTIM1.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_HRTIM1_GetKernelClkFreq(void)
{
  return HAL_RCC_GetSYSCLKFreq();
}

/**
  * @brief  Return the peripheral clock frequency for HRTIM2.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_HRTIM2_GetKernelClkFreq(void)
{
  return HAL_RCC_GetSYSCLKFreq();
}

/**
  * @brief  Return the peripheral clock frequency for TIM.
  * @param  timx TIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_TIM_GetKernelClkFreq(const TIM_TypeDef *timx)
{
  STM32_UNUSED(timx);
  return HAL_RCC_GetSYSCLKFreq();
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM.
  * @param  lptimx LPTIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_LPTIM_GetKernelClkFreq(const LPTIM_TypeDef *lptimx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)lptimx)
  {
    case (uint32_t)LPTIM1:
      frequency = HAL_RCC_LPTIM1_GetKernelClkFreq();
      break;

    case (uint32_t)LPTIM2:
      frequency = HAL_RCC_LPTIM23_GetKernelClkFreq();
      break;

    case (uint32_t)LPTIM3:
      frequency = HAL_RCC_LPTIM23_GetKernelClkFreq();
      break;

    case (uint32_t)LPTIM4:
      frequency = HAL_RCC_LPTIM45_GetKernelClkFreq();
      break;

    case (uint32_t)LPTIM5:
      frequency = HAL_RCC_LPTIM45_GetKernelClkFreq();
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
    case LL_RCC_LPTIM1_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

#if defined(LSE_VALUE)
    case LL_RCC_LPTIM1_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_LPTIM1_CLKSOURCE_LSI:

      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_PER:

      frequency = RCC_PERCLK_GetClockFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM23.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPTIM23_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM23_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_LPTIM23_CLKSOURCE_PCLK4:

      frequency = HAL_RCC_GetPCLK4Freq();
      break;

    case LL_RCC_LPTIM23_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_LPTIM23_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

#if defined(LSE_VALUE)
    case LL_RCC_LPTIM23_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_LPTIM23_CLKSOURCE_LSI:

      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_LPTIM23_CLKSOURCE_PER:

      frequency = RCC_PERCLK_GetClockFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM45.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPTIM45_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM45_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_LPTIM45_CLKSOURCE_PCLK4:

      frequency = HAL_RCC_GetPCLK4Freq();
      break;

    case LL_RCC_LPTIM45_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_LPTIM45_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

#if defined(LSE_VALUE)

    case LL_RCC_LPTIM45_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_LPTIM45_CLKSOURCE_LSI:

      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_LPTIM45_CLKSOURCE_PER:

      frequency = RCC_PERCLK_GetClockFreq();
      break;

    default:
      break;
  }

  return frequency;
}

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

    case LL_RCC_FDCAN_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

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

    case (uint32_t)DAC3:
      frequency = HAL_RCC_DAC3_GetKernelClkFreq();
      break;

    case (uint32_t)DAC4:
      frequency = HAL_RCC_DAC4_GetKernelClkFreq();
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
    case LL_RCC_DAC1_CLKSOURCE_HCLK3:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_DAC1_CLKSOURCE_TIM:

      frequency = HAL_RCC_TIM_GetKernelClkFreq(NULL);
      break;

    case LL_RCC_DAC1_CLKSOURCE_ADC:

      frequency = HAL_RCC_ADC1234_GetKernelClkFreq();
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

    case LL_RCC_DAC1_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_DAC1_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_DAC1_CLKSOURCE_PER:

      frequency = RCC_PERCLK_GetClockFreq();
      break;

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
    case LL_RCC_DAC2_CLKSOURCE_HCLK3:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_DAC2_CLKSOURCE_TIM:

      frequency = HAL_RCC_TIM_GetKernelClkFreq(NULL);
      break;

    case LL_RCC_DAC2_CLKSOURCE_ADC:

      frequency = HAL_RCC_ADC1234_GetKernelClkFreq();
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

    case LL_RCC_DAC2_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_DAC2_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_DAC2_CLKSOURCE_PER:

      frequency = RCC_PERCLK_GetClockFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC3.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC3_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC3_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_DAC3_CLKSOURCE_HCLK3:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_DAC3_CLKSOURCE_TIM:

      frequency = HAL_RCC_TIM_GetKernelClkFreq(NULL);
      break;

    case LL_RCC_DAC3_CLKSOURCE_ADC:

      frequency = HAL_RCC_ADC1234_GetKernelClkFreq();
      break;

#if defined(HSE_VALUE)
    case LL_RCC_DAC3_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_DAC3_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;

    case LL_RCC_DAC3_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_DAC3_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_DAC3_CLKSOURCE_PER:

      frequency = RCC_PERCLK_GetClockFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC4.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC4_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC4_CLKSOURCE);
  hal_rcc_pll_output_freq_t pll_clocks;

  switch (srcclk)
  {
    case LL_RCC_DAC4_CLKSOURCE_HCLK3:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_DAC4_CLKSOURCE_TIM:

      frequency = HAL_RCC_TIM_GetKernelClkFreq(NULL);
      break;

    case LL_RCC_DAC4_CLKSOURCE_ADC:

      frequency = HAL_RCC_ADC1234_GetKernelClkFreq();
      break;

#if defined(HSE_VALUE)
    case LL_RCC_DAC4_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_DAC4_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;

    case LL_RCC_DAC4_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_DAC4_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_DAC4_CLKSOURCE_PER:

      frequency = RCC_PERCLK_GetClockFreq();
      break;

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
    default:
      break;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC1SH.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC1_GetSampleHoldClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDACSHClockSource(LL_RCC_DAC1SH_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_DAC1SH_CLKSOURCE_LSI:

      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_DAC1SH_CLKSOURCE_LSE:

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
  * @brief  Return the peripheral clock frequency for COMP.
  * @param  compx COMP instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_COMP_GetKernelClkFreq(const COMP_TypeDef *compx)
{
  STM32_UNUSED(compx);
  return HAL_RCC_GetPCLK4Freq();
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
    case LL_RCC_RTC_CLKSOURCE_LSI:

      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_RTC_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

#if defined(HSE_VALUE)
    case LL_RCC_RTC_CLKSOURCE_HSE_DIV:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        uint32_t Prescaler = LL_RCC_GetRTC_HSEPrescaler();
        if (Prescaler >= 0x2U)
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

/** @addtogroup RCC_Exported_Functions_Group6
  * @{
  */

/**
  * @brief This function enables the FMC clock protection.
  */
void HAL_RCC_FMC_EnableClockProtection(void)
{
  LL_RCC_EnableFMCClockProtection();
}

/**
  * @brief This function disables the FMC clock protection.
  */
void HAL_RCC_FMC_DisableClockProtection(void)
{
  LL_RCC_DisableFMCClockProtection();
}

/**
  * @brief  Get the FMC kernel clock switch position.
  * @retval kerclk kernel Clock switch position based on @ref hal_rcc_fmc_clk_src_switch_position_t
  */
hal_rcc_fmc_clk_src_switch_position_t HAL_RCC_FMC_GetKernelClkSwitchPosition(void)
{
  return (hal_rcc_fmc_clk_src_switch_position_t)LL_RCC_GetFMCSwitchPosition();
}

/**
  * @brief This function checks if FMC clock protection is enabled.
  * @retval HAL_RCC_CLK_DISABLED FMC clock protection is disabled
  * @retval HAL_RCC_CLK_ENABLED  FMC clock protection is enabled
  */
hal_rcc_clk_status_t HAL_RCC_FMC_IsEnabledClockProtection(void)
{
  return (hal_rcc_clk_status_t)LL_RCC_IsEnabledFMCClockProtection();
}

/**
  * @brief This function enables the XSPI clock protection.
  */
void HAL_RCC_XSPI_EnableClockProtection(void)
{
  LL_RCC_EnableXSPIClockProtection();
}

/**
  * @brief This function disables the XSPI clock protection.
  */
void HAL_RCC_XSPI_DisableClockProtection(void)
{
  LL_RCC_DisableXSPIClockProtection();
}

/**
  * @brief This function checks if XSPI clock protection is enabled.
  * @retval HAL_RCC_CLK_DISABLED XSPI clock protection is disabled
  * @retval HAL_RCC_CLK_ENABLED  XSPI clock protection is enabled
  */
hal_rcc_clk_status_t HAL_RCC_XSPI_IsEnabledClockProtection(void)
{
  return (hal_rcc_clk_status_t)LL_RCC_IsEnabledXSPIClockProtection();
}

/**
  * @brief  Get the XSPI kernel clock switch position.
  * @retval kerclk kernel Clock switch position based on @ref hal_rcc_xspi_clk_src_switch_position_t
  */
hal_rcc_xspi_clk_src_switch_position_t HAL_RCC_XSPI_GetKernelClkSwitchPosition(void)
{
  return (hal_rcc_xspi_clk_src_switch_position_t)LL_RCC_GetXSPISwitchPosition();
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
  * @param  p_timeout_cb Callback on the timeout function.
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
  * @brief   Configure PLLx without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLLx is well deactivated (if enabled exit from this function)
  *           - Configure the PLLx with full list of parameters
  * @param pll_id   ID on the targeted PLLx (PLL1, PLL2 or PLL3)
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLLx
  * @retval HAL_OK            PLLx has been correctly configured\n
  * @retval HAL_ERROR         PLLx is already enabled and can not be modified.
  */
static hal_status_t RCC_PLL_SetConfig(rcc_pll_id_t pll_id, const hal_rcc_pll_config_t *p_config)
{
  /*
    The config function will perform the following actions:
    - Check in PLLs is well deactivated (if enabled exit from this function)
    - Configure the PLLx with full list of parameters
  */

  /* Configure the PLL clock source */
  if (LL_RCC_PLL_GetSource() != (uint32_t)(p_config->pll_source))
  {
    if ((LL_RCC_PLL1_IsReady() == 0U) && (LL_RCC_PLL2_IsReady() == 0U) && (LL_RCC_PLL3_IsReady() == 0U))
    {
      LL_RCC_PLL_SetSource((uint32_t)p_config->pll_source);
    }
    else
    {
      return HAL_ERROR;
    }
  }

  if (pll_id == PLL_1)
  {
    LL_RCC_PLL1_SetM(p_config->pll_m);
    LL_RCC_PLL1_DisableFRACN();

    if (p_config->pll_sscg_state == HAL_RCC_PLL_SSCG_ENABLE)
    {
      LL_RCC_PLL1_SetFRACN(0U);
    }
    else
    {
      LL_RCC_PLL1_SetFRACN(p_config->pll_fracn);
    }
    LL_RCC_PLL1_EnableFRACN();

    LL_RCC_PLL1_SetN(p_config->pll_n);
    LL_RCC_PLL1_SetP(p_config->pll_p);
    LL_RCC_PLL1_SetQ(p_config->pll_q);
    LL_RCC_PLL1_SetS(p_config->pll_s);

    LL_RCC_PLL1_SetInputRange((uint32_t)p_config->pll_input_range);
    LL_RCC_PLL1_SetVCORange((uint32_t)p_config->pll_vco_range);

    if (p_config->pll_sscg_state == HAL_RCC_PLL_SSCG_ENABLE)
    {
      LL_RCC_PLL1_ConfigSSCG(p_config->pll_sscg_config.mod_period,
                             p_config->pll_sscg_config.mod_depth_adj,
                             (uint32_t)p_config->pll_sscg_config.spread_mode,
                             (uint32_t)p_config->pll_sscg_config.dith_control);
      LL_RCC_PLL1_EnableSSCG();
    }
    else
    {
      LL_RCC_PLL1_DisableSSCG();
    }
  }
  else if (pll_id == PLL_2)
  {
    LL_RCC_PLL2_SetM(p_config->pll_m);
    LL_RCC_PLL2_DisableFRACN();

    if (p_config->pll_sscg_state == HAL_RCC_PLL_SSCG_ENABLE)
    {
      LL_RCC_PLL2_SetFRACN(0U);
    }
    else
    {
      LL_RCC_PLL2_SetFRACN(p_config->pll_fracn);
    }
    LL_RCC_PLL2_EnableFRACN();

    LL_RCC_PLL2_SetN(p_config->pll_n);
    LL_RCC_PLL2_SetP(p_config->pll_p);
    LL_RCC_PLL2_SetQ(p_config->pll_q);
    LL_RCC_PLL2_SetR(p_config->pll_r);
    LL_RCC_PLL2_SetS(p_config->pll_s);
    LL_RCC_PLL2_SetT(p_config->pll_t);

    LL_RCC_PLL2_SetInputRange((uint32_t)(p_config->pll_input_range) << ((uint32_t)pll_id * (uint32_t)11U));
    LL_RCC_PLL2_SetVCORange((uint32_t)(p_config->pll_vco_range) << ((uint32_t)pll_id * (uint32_t)11U));

    if (p_config->pll_sscg_state == HAL_RCC_PLL_SSCG_ENABLE)
    {
      LL_RCC_PLL2_ConfigSSCG(p_config->pll_sscg_config.mod_period,
                             p_config->pll_sscg_config.mod_depth_adj,
                             (uint32_t)p_config->pll_sscg_config.spread_mode,
                             (uint32_t)p_config->pll_sscg_config.dith_control);
      LL_RCC_PLL2_EnableSSCG();
    }
    else
    {
      LL_RCC_PLL2_DisableSSCG();
    }
  }
  else /* pll_id == PLL_3 */
  {
    LL_RCC_PLL3_SetM(p_config->pll_m);
    LL_RCC_PLL3_DisableFRACN();

    if (p_config->pll_sscg_state == HAL_RCC_PLL_SSCG_ENABLE)
    {
      LL_RCC_PLL3_SetFRACN(0U);
    }
    else
    {
      LL_RCC_PLL3_SetFRACN(p_config->pll_fracn);
    }
    LL_RCC_PLL3_EnableFRACN();

    LL_RCC_PLL3_SetN(p_config->pll_n);
    LL_RCC_PLL3_SetP(p_config->pll_p);
    LL_RCC_PLL3_SetQ(p_config->pll_q);
    LL_RCC_PLL3_SetR(p_config->pll_r);
    LL_RCC_PLL3_SetS(p_config->pll_s);

    LL_RCC_PLL3_SetInputRange((uint32_t)(p_config->pll_input_range) << ((uint32_t)pll_id * (uint32_t)11U));
    LL_RCC_PLL3_SetVCORange((uint32_t)(p_config->pll_vco_range) << ((uint32_t)pll_id * (uint32_t)11U));

    if (p_config->pll_sscg_state == HAL_RCC_PLL_SSCG_ENABLE)
    {
      LL_RCC_PLL3_ConfigSSCG(p_config->pll_sscg_config.mod_period,
                             p_config->pll_sscg_config.mod_depth_adj,
                             (uint32_t)p_config->pll_sscg_config.spread_mode,
                             (uint32_t)p_config->pll_sscg_config.dith_control);
      LL_RCC_PLL3_EnableSSCG();
    }
    else
    {
      LL_RCC_PLL3_DisableSSCG();
    }
  }

  return HAL_OK;
}

/**
  * @brief Return the configuration of PLLx.
  * @param pll_id    ID on the targeted PLLx (PLL1, PLL2 or PLL3)
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLLx
  */
static void RCC_PLL_GetConfig(rcc_pll_id_t pll_id, hal_rcc_pll_config_t *p_config)
{
  p_config->pll_source = (hal_rcc_pll_src_t)LL_RCC_PLL_GetSource();

  if (pll_id == PLL_1)
  {
    p_config->pll_input_range = (hal_rcc_pll_input_range_t)LL_RCC_PLL1_GetInputRange();
    p_config->pll_vco_range   = (hal_rcc_pll_vco_range_t)LL_RCC_PLL1_GetVCORange();
    p_config->pll_sscg_state  = (hal_rcc_pll_sscg_state_t)LL_RCC_PLL1_IsEnabledSSCG();
    p_config->pll_m     = (uint8_t)LL_RCC_PLL1_GetM();
    p_config->pll_n     = (uint16_t)LL_RCC_PLL1_GetN();
    p_config->pll_fracn = (uint16_t)LL_RCC_PLL1_GetFRACN();

    p_config->pll_p     = (uint8_t)LL_RCC_PLL1_GetP();
    p_config->pll_q     = (uint8_t)LL_RCC_PLL1_GetQ();
    p_config->pll_r     = 0U;
    p_config->pll_s     = (uint8_t)LL_RCC_PLL1_GetS();
    p_config->pll_t     = 0U;

    p_config->pll_sscg_config.mod_period    = LL_RCC_PLL1_GetSSCGModulationPeriod();
    p_config->pll_sscg_config.mod_depth_adj = LL_RCC_PLL1_GetSSCGIncrementStep();
    p_config->pll_sscg_config.spread_mode   =
      (hal_rcc_pll_sscg_spread_mode_t)LL_RCC_PLL1_GetSSCGSpreadSelection();
    p_config->pll_sscg_config.dith_control  =
      (hal_rcc_pll_sscg_dith_ctrl_t)LL_RCC_PLL1_GetSSCGDithering();
  }
  else if (pll_id == PLL_2)
  {
    p_config->pll_input_range = (hal_rcc_pll_input_range_t)(LL_RCC_PLL2_GetInputRange() >> ((uint32_t)pll_id * 11U));
    p_config->pll_vco_range   = (hal_rcc_pll_vco_range_t)(LL_RCC_PLL2_GetVCORange() >> ((uint32_t)pll_id * 11U));
    p_config->pll_sscg_state  = (hal_rcc_pll_sscg_state_t)LL_RCC_PLL2_IsEnabledSSCG();
    p_config->pll_m     = (uint8_t)LL_RCC_PLL2_GetM();
    p_config->pll_n     = (uint16_t)LL_RCC_PLL2_GetN();
    p_config->pll_fracn = (uint16_t)LL_RCC_PLL2_GetFRACN();

    p_config->pll_p     = (uint8_t)LL_RCC_PLL2_GetP();
    p_config->pll_q     = (uint8_t)LL_RCC_PLL2_GetQ();
    p_config->pll_r     = (uint8_t)LL_RCC_PLL2_GetR();
    p_config->pll_s     = (uint8_t)LL_RCC_PLL2_GetS();
    p_config->pll_t     = (uint8_t)LL_RCC_PLL2_GetT();

    p_config->pll_sscg_config.mod_period    = LL_RCC_PLL2_GetSSCGModulationPeriod();
    p_config->pll_sscg_config.mod_depth_adj = LL_RCC_PLL2_GetSSCGIncrementStep();
    p_config->pll_sscg_config.spread_mode   =
      (hal_rcc_pll_sscg_spread_mode_t)LL_RCC_PLL2_GetSSCGSpreadSelection();
    p_config->pll_sscg_config.dith_control  =
      (hal_rcc_pll_sscg_dith_ctrl_t)LL_RCC_PLL2_GetSSCGDithering();
  }
  else /* pll_id == PLL_3 */
  {
    p_config->pll_input_range = (hal_rcc_pll_input_range_t)(LL_RCC_PLL3_GetInputRange() >> ((uint32_t)pll_id * 11U));
    p_config->pll_vco_range   = (hal_rcc_pll_vco_range_t)(LL_RCC_PLL3_GetVCORange() >> ((uint32_t)pll_id * 11U));
    p_config->pll_sscg_state  = (hal_rcc_pll_sscg_state_t)LL_RCC_PLL3_IsEnabledSSCG();
    p_config->pll_m     = (uint8_t)LL_RCC_PLL3_GetM();
    p_config->pll_n     = (uint16_t)LL_RCC_PLL3_GetN();
    p_config->pll_fracn = (uint16_t)LL_RCC_PLL3_GetFRACN();

    p_config->pll_p     = (uint8_t)LL_RCC_PLL3_GetP();
    p_config->pll_q     = (uint8_t)LL_RCC_PLL3_GetQ();
    p_config->pll_r     = (uint8_t)LL_RCC_PLL3_GetR();
    p_config->pll_s     = (uint8_t)LL_RCC_PLL3_GetS();
    p_config->pll_t     = 0U;

    p_config->pll_sscg_config.mod_period    = LL_RCC_PLL3_GetSSCGModulationPeriod();
    p_config->pll_sscg_config.mod_depth_adj = LL_RCC_PLL3_GetSSCGIncrementStep();
    p_config->pll_sscg_config.spread_mode   =
      (hal_rcc_pll_sscg_spread_mode_t)LL_RCC_PLL3_GetSSCGSpreadSelection();
    p_config->pll_sscg_config.dith_control  =
      (hal_rcc_pll_sscg_dith_ctrl_t)LL_RCC_PLL3_GetSSCGDithering();
  }
}

/**
  * @brief Return the output frequency of PLLx.
  * @param pll_id    ID on the targeted PLLx (PLL1, PLL2 or PLL3)
  * @param p_clk     pointer to a @ref hal_rcc_pll_output_freq_t structure that
  *          contains the frequency output information for the PLLx
  */
static void RCC_PLL_GetClockFreq(rcc_pll_id_t pll_id, hal_rcc_pll_output_freq_t *p_clk)
{
  uint32_t pll_src;
  uint32_t pll_m;
  uint32_t pll_n;
  uint32_t pll_p;
  uint32_t pll_q;
  uint32_t pll_r;
  uint32_t pll_s;
  uint32_t pll_t;
  uint32_t pll_fracen;
  uint32_t pll_fracn;
  uint32_t pll_output_p_en;
  uint32_t pll_output_q_en;
  uint32_t pll_output_r_en;
  uint32_t pll_output_s_en;
  uint32_t pll_output_t_en;
  uint64_t fracn;
  uint64_t pll_vco_num;
  uint64_t pll_vco_den;

  pll_src = LL_RCC_PLL_GetSource();

  if (pll_id == PLL_1)
  {
    pll_m            = LL_RCC_PLL1_GetM();
    pll_n            = LL_RCC_PLL1_GetN();
    pll_fracen       = LL_RCC_PLL1_IsEnabledFRACN();
    pll_fracn        = LL_RCC_PLL1_GetFRACN();
    pll_output_p_en  = LL_RCC_PLL1_IsEnabledOutputP();
    pll_output_q_en  = LL_RCC_PLL1_IsEnabledOutputQ();
    pll_output_r_en  = 0U;
    pll_output_s_en  = LL_RCC_PLL1_IsEnabledOutputS();
    pll_output_t_en  = 0U;
    pll_p            = LL_RCC_PLL1_GetP();
    pll_q            = LL_RCC_PLL1_GetQ();
    pll_r            = 0U;
    pll_s            = LL_RCC_PLL1_GetS();
    pll_t            = 0U;
  }
  else if (pll_id == PLL_2)
  {
    pll_m            = LL_RCC_PLL2_GetM();
    pll_n            = LL_RCC_PLL2_GetN();
    pll_fracen       = LL_RCC_PLL2_IsEnabledFRACN();
    pll_fracn        = LL_RCC_PLL2_GetFRACN();
    pll_output_p_en  = LL_RCC_PLL2_IsEnabledOutputP();
    pll_output_q_en  = LL_RCC_PLL2_IsEnabledOutputQ();
    pll_output_r_en  = LL_RCC_PLL2_IsEnabledOutputR();
    pll_output_s_en  = LL_RCC_PLL2_IsEnabledOutputS();
    pll_output_t_en  = LL_RCC_PLL2_IsEnabledOutputT();
    pll_p            = LL_RCC_PLL2_GetP();
    pll_q            = LL_RCC_PLL2_GetQ();
    pll_r            = LL_RCC_PLL2_GetR();
    pll_s            = LL_RCC_PLL2_GetS();
    pll_t            = LL_RCC_PLL2_GetT();
  }
  else /* pll_id == PLL_3 */
  {
    pll_m            = LL_RCC_PLL3_GetM();
    pll_n            = LL_RCC_PLL3_GetN();
    pll_fracen       = LL_RCC_PLL3_IsEnabledFRACN();
    pll_fracn        = LL_RCC_PLL3_GetFRACN();
    pll_output_p_en  = LL_RCC_PLL3_IsEnabledOutputP();
    pll_output_q_en  = LL_RCC_PLL3_IsEnabledOutputQ();
    pll_output_r_en  = LL_RCC_PLL3_IsEnabledOutputR();
    pll_output_s_en  = LL_RCC_PLL3_IsEnabledOutputS();
    pll_output_t_en  = 0U;
    pll_p            = LL_RCC_PLL3_GetP();
    pll_q            = LL_RCC_PLL3_GetQ();
    pll_r            = LL_RCC_PLL3_GetR();
    pll_s            = LL_RCC_PLL3_GetS();
    pll_t            = 0U;
  }

  /* Fixed-point computation:
   * PLL_VCO = Fsrc * (N + FRACN / PLL_FRACN_MODULUS) / M
   * pll_vco_num = Fsrc * (N * PLL_FRACN_MODULUS + FRACN)
   * pll_vco_den = M * PLL_FRACN_MODULUS
   * PLLx = pll_vco_num / (pll_vco_den * divider_x) (P, Q, R, S or T)
   * If SSCG down-spread is enabled:
   * PLLx = PLLx * (100000000 - mod_depth) / 100000000
   */
  if (pll_m == 0U)
  {
    return;
  }

  switch (pll_src)
  {
    case HAL_RCC_PLL_SRC_HSI:
      pll_vco_num = (uint64_t)RCC_HSI_GetClockFreq();
      break;
    case HAL_RCC_PLL_SRC_CSI:
      pll_vco_num = (uint64_t)CSI_VALUE;
      break;
#if defined(HSE_VALUE)
    case HAL_RCC_PLL_SRC_HSE:
      pll_vco_num = (uint64_t)HSE_VALUE;
      break;
#endif /* HSE_VALUE */
    default:
      pll_vco_num = 0ULL;
      break;
  }

  fracn = ((uint64_t)pll_fracen) * (uint64_t)pll_fracn;
  pll_vco_num = pll_vco_num * (((uint64_t)pll_n * PLL_FRACN_MODULUS) + fracn);
  pll_vco_den = (uint64_t)pll_m * (uint64_t)PLL_FRACN_MODULUS;

  p_clk->pll_p_freq = RCC_PLL_GetOutputFreq(pll_id, pll_output_p_en, pll_p, pll_vco_num, pll_vco_den);
  p_clk->pll_q_freq = RCC_PLL_GetOutputFreq(pll_id, pll_output_q_en, pll_q, pll_vco_num, pll_vco_den);
  p_clk->pll_r_freq = RCC_PLL_GetOutputFreq(pll_id, pll_output_r_en, pll_r, pll_vco_num, pll_vco_den);
  p_clk->pll_s_freq = RCC_PLL_GetOutputFreq(pll_id, pll_output_s_en, pll_s, pll_vco_num, pll_vco_den);
  p_clk->pll_t_freq = RCC_PLL_GetOutputFreq(pll_id, pll_output_t_en, pll_t, pll_vco_num, pll_vco_den);
}

/**
  * @brief Compute a single PLLx output frequency (P, Q, R, S or T), applying SSCG down-spread if enabled.
  * @param pll_id ID on the targeted PLLx (PLL1, PLL2 or PLL3)
  * @param output_en  Output enable flag for the targeted divider
  * @param divider  Divider value applied to the PLL VCO frequency
  * @param pll_vco_num  PLL VCO frequency numerator
  * @param pll_vco_den  PLL VCO frequency denominator
  * @retval uint32_t Output frequency in Hz, or 0 if the output is disabled or the divider is 0
  */
static uint32_t RCC_PLL_GetOutputFreq(rcc_pll_id_t pll_id, uint32_t output_en, uint32_t divider,
                                      uint64_t pll_vco_num, uint64_t pll_vco_den)
{
  uint32_t freq = 0U;
  uint32_t pll_n = 0U;
  uint32_t sscg_enabled = 0U;
  uint32_t sscg_spread_down = 0U;
  uint32_t sscg_mod_period = 0U;
  uint32_t sscg_inc_step = 0U;
  uint64_t mod_depth = 0ULL;

  if ((output_en != 0U) && (divider != 0U))
  {
    if (pll_id == PLL_1)
    {
      pll_n            = LL_RCC_PLL1_GetN();
      sscg_enabled     = LL_RCC_PLL1_IsEnabledSSCG();
      sscg_spread_down = (LL_RCC_PLL1_GetSSCGSpreadSelection() == LL_RCC_PLL_SPREAD_DOWN) ? 1U : 0U;
      sscg_mod_period  = LL_RCC_PLL1_GetSSCGModulationPeriod();
      sscg_inc_step    = LL_RCC_PLL1_GetSSCGIncrementStep();
    }
    else if (pll_id == PLL_2)
    {
      pll_n            = LL_RCC_PLL2_GetN();
      sscg_enabled     = LL_RCC_PLL2_IsEnabledSSCG();
      sscg_spread_down = (LL_RCC_PLL2_GetSSCGSpreadSelection() == LL_RCC_PLL_SPREAD_DOWN) ? 1U : 0U;
      sscg_mod_period  = LL_RCC_PLL2_GetSSCGModulationPeriod();
      sscg_inc_step    = LL_RCC_PLL2_GetSSCGIncrementStep();
    }
    else /* pll_id == PLL_3 */
    {
      pll_n            = LL_RCC_PLL3_GetN();
      sscg_enabled     = LL_RCC_PLL3_IsEnabledSSCG();
      sscg_spread_down = (LL_RCC_PLL3_GetSSCGSpreadSelection() == LL_RCC_PLL_SPREAD_DOWN) ? 1U : 0U;
      sscg_mod_period  = LL_RCC_PLL3_GetSSCGModulationPeriod();
      sscg_inc_step    = LL_RCC_PLL3_GetSSCGIncrementStep();
    }

    freq = (uint32_t)(pll_vco_num / (pll_vco_den * (uint64_t)divider));

    if ((sscg_enabled != 0U) && (sscg_spread_down != 0U))
    {
      mod_depth = RCC_CALC_PLL_SSCG_MD(sscg_mod_period, sscg_inc_step, (pll_n - 1U));
      uint64_t temp_freq = ((uint64_t)freq) * (100000000ULL - mod_depth);
      freq = (uint32_t)(temp_freq / 100000000ULL);
    }
  }

  return freq;
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

/** @brief  Get peripheral clock (PERCLK) frequency.
  * @retval uint32_t peripheral clock frequency in Hz
  */
static uint32_t RCC_PERCLK_GetClockFreq(void)
{
  uint32_t frequency = 0;
  uint32_t srcclk = LL_RCC_PERCLK_GetSource();

  switch (srcclk)
  {
    case LL_RCC_PER_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetClockFreq();
      }
      break;

    case LL_RCC_PER_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(HSE_VALUE)
    case LL_RCC_PER_CLKSOURCE_HSE:

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
  * @}
  */

#endif /* USE_HAL_RCC_MODULE */
#endif /* RCC */

/**
  * @}
  */

/**
  * @}
  */
