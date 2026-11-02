/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_rcc.h
  * @brief   Header file of RCC HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7PXX_HAL_RCC_H
#define STM32H7PXX_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_rcc.h"
#include "stm32h7pxx_ll_bus.h"
#include "stm32h7pxx_ll_pwr.h"

/** @addtogroup STM32H7PXX_HAL_Driver
  * @{
  */
#if defined (RCC)

/** @addtogroup RCC
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants HAL RCC Constants
  * @{
  *
  * This group contains all exported constants related to the RCC peripheral,
  * including reset flags, PLL clock outputs, and other defines.
  */

/** @defgroup RCC_Reset_Flag Reset Flag
  * @{
  */
#define HAL_RCC_RESET_FLAG_OBL    RCC_RSR_OBLRSTF   /*!< Option byte loading reset flag    */
#define HAL_RCC_RESET_FLAG_BOR    RCC_RSR_BORRSTF   /*!< BOR reset flag                    */
#define HAL_RCC_RESET_FLAG_PIN    RCC_RSR_PINRSTF   /*!< Pin reset flag (NRST)             */
#define HAL_RCC_RESET_FLAG_PWR    RCC_RSR_PORRSTF   /*!< POR/PDR reset flag                */
#define HAL_RCC_RESET_FLAG_SW     RCC_RSR_SFTRSTF   /*!< Software Reset flag               */
#define HAL_RCC_RESET_FLAG_IWDG   RCC_RSR_IWDGRSTF  /*!< independent watchdog reset flag   */
#define HAL_RCC_RESET_FLAG_WWDG   RCC_RSR_WWDGRSTF  /*!< window watchdog reset flag        */
#define HAL_RCC_RESET_FLAG_LPWR   RCC_RSR_LPWRRSTF  /*!< Low power reset flag              */
#define HAL_RCC_RESET_FLAG_ALL    (HAL_RCC_RESET_FLAG_OBL | HAL_RCC_RESET_FLAG_BOR | HAL_RCC_RESET_FLAG_PIN | \
                                   HAL_RCC_RESET_FLAG_PWR | HAL_RCC_RESET_FLAG_SW  | HAL_RCC_RESET_FLAG_IWDG | \
                                   HAL_RCC_RESET_FLAG_WWDG | HAL_RCC_RESET_FLAG_LPWR ) /*!< All RCC reset flags */
/**
  * @}
  */

/** @defgroup RCC_PLL1_Clock_Output RCC PLL1 Clock Output
  * @{
  */
#define HAL_RCC_PLL1_OUTPUT_P     LL_RCC_PLL1_OUTPUT_P    /*!< Output used by the system clock */
#define HAL_RCC_PLL1_OUTPUT_Q     LL_RCC_PLL1_OUTPUT_Q    /*!< Output used by FMC, FDCAN, SPI1, SPI23  */
#define HAL_RCC_PLL1_OUTPUT_S     LL_RCC_PLL1_OUTPUT_S    /*!< Output not used */
#define HAL_RCC_PLL1_OUTPUT_ALL   (LL_RCC_PLL1_OUTPUT_P | LL_RCC_PLL1_OUTPUT_Q |  LL_RCC_PLL1_OUTPUT_S)  /*!< All PLL1 outputs     */
#define HAL_RCC_PLL1_SYSCLK       HAL_RCC_PLL1_OUTPUT_P   /*!< Define used for legacy purpose */
/**
  * @}
  */

/** @defgroup RCC_PLL2_Clock_Output RCC PLL2 Clock Output
  * @{
  */
#define HAL_RCC_PLL2_OUTPUT_P     LL_RCC_PLL2_OUTPUT_P  /*!< Output used by ADC, ADF1, FDCAN, LPTIMx, SPI1, SPI23, DACx */
#define HAL_RCC_PLL2_OUTPUT_Q     LL_RCC_PLL2_OUTPUT_Q  /*!< Output used by UART234578, USART16910, SPI45, SPI6, LPUART1 */
#define HAL_RCC_PLL2_OUTPUT_R     LL_RCC_PLL2_OUTPUT_R  /*!< Output used by FMC */
#define HAL_RCC_PLL2_OUTPUT_S     LL_RCC_PLL2_OUTPUT_S  /*!< Output used by XSPI1, SDMMC1 */
#define HAL_RCC_PLL2_OUTPUT_T     LL_RCC_PLL2_OUTPUT_T  /*!< Output used by XSPI1, SDMMC1 */
#define HAL_RCC_PLL2_OUTPUT_ALL   (LL_RCC_PLL2_OUTPUT_P | LL_RCC_PLL2_OUTPUT_Q | LL_RCC_PLL2_OUTPUT_R | LL_RCC_PLL2_OUTPUT_S | LL_RCC_PLL2_OUTPUT_T) /*!< All PLL2 outputs */
/**
  * @}
  */

/** @defgroup RCC_PLL3_Clock_Output RCC PLL3 Clock Output
  * @{
  */
#define HAL_RCC_PLL3_OUTPUT_P     LL_RCC_PLL3_OUTPUT_P  /*!< Output used by ADF1, SPI1, SPI23  */
#define HAL_RCC_PLL3_OUTPUT_Q     LL_RCC_PLL3_OUTPUT_Q  /*!< Output used by USBOTG, UART234578, USART16910, SPI45, SPI6, LPUART1 */
#define HAL_RCC_PLL3_OUTPUT_R     LL_RCC_PLL3_OUTPUT_R  /*!< Output used by ADC, LPTIMx, I3C1, I2C123, DACx */
#define HAL_RCC_PLL3_OUTPUT_S     LL_RCC_PLL3_OUTPUT_S  /*!< Output not used */
#define HAL_RCC_PLL3_OUTPUT_ALL   (LL_RCC_PLL3_OUTPUT_P | LL_RCC_PLL3_OUTPUT_Q | LL_RCC_PLL3_OUTPUT_R | LL_RCC_PLL3_OUTPUT_S) /*!< All PLL3 outputs */
/**
  * @}
  */

/**
  * @brief Default HSI trimming value
  */
#define HAL_RCC_HSICALIBRATION_DEFAULT LL_RCC_HSICALIBRATION_DEFAULT /*!< Default HSI calibration trimming value */

/**
  * @brief Default CSI trimming value
  */
#define HAL_RCC_CSICALIBRATION_DEFAULT LL_RCC_CSICALIBRATION_DEFAULT /*!< Default CSI calibration trimming value */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief Oscillator enable status
  */
typedef enum
{
  HAL_RCC_OSC_DISABLED = 0U,                     /*!< Oscillator is disabled */
  HAL_RCC_OSC_ENABLED  = ! HAL_RCC_OSC_DISABLED, /*!< Oscillator is enabled  */
} hal_rcc_osc_enable_status_t;

/**
  * @brief Oscillator ready status
  */
typedef enum
{
  HAL_RCC_OSC_NOT_READY = 0U,                      /*!< Oscillator is not ready */
  HAL_RCC_OSC_READY     = ! HAL_RCC_OSC_NOT_READY, /*!< Oscillator is ready     */
} hal_rcc_osc_ready_status_t;

/**
  * @brief Oscillator enable in stop modes status.
  */
typedef enum
{
  HAL_RCC_OSC_DISABLED_IN_STOP_MODE = 0U,                                 /*!< Oscillator is enabled in Run mode only      */
  HAL_RCC_OSC_ENABLED_IN_STOP_MODE  = ! HAL_RCC_OSC_DISABLED_IN_STOP_MODE, /*!< Oscillator is enabled in Run and stop mode */
} hal_rcc_osc_stop_mode_status_t;

/**
  * @brief Peripheral/Bus clock activation status
  */
typedef enum
{
  HAL_RCC_CLK_DISABLED = 0U,                      /*!< Clock is disabled */
  HAL_RCC_CLK_ENABLED = ! HAL_RCC_CLK_DISABLED    /*!< Clock is enabled */
} hal_rcc_clk_status_t;

#if defined(HSE_VALUE)

/**
  * @brief HSE state
  */
typedef enum
{
  HAL_RCC_HSE_ON             = LL_RCC_HSE_ON,             /*!< HSE clock activation                        */
  HAL_RCC_HSE_BYPASS         = LL_RCC_HSE_BYPASS,         /*!< External analog clock source for HSE clock  */
  HAL_RCC_HSE_BYPASS_DIGITAL = LL_RCC_HSE_BYPASS_DIGITAL, /*!< External digital clock source for HSE clock */
} hal_rcc_hse_t;

#endif /* (HSE_VALUE) */

#if defined(LSE_VALUE)

/**
  * @brief LSE state
  */
typedef enum
{
  HAL_RCC_LSE_ON             = LL_RCC_LSE_ON,             /*!< LSE clock activation                        */
  HAL_RCC_LSE_BYPASS         = LL_RCC_LSE_BYPASS,         /*!< External analog clock source for LSE clock  */
  HAL_RCC_LSE_BYPASS_DIGITAL = LL_RCC_LSE_BYPASS_DIGITAL, /*!< External digital clock source for LSE clock */
} hal_rcc_lse_t;

/**
  * @brief LSE drive configuration
  */
typedef enum
{
  HAL_RCC_LSE_DRIVE_LOW        = LL_RCC_LSEDRIVE_LOW,        /*!< Crystal mode low driving capability         */
  HAL_RCC_LSE_DRIVE_MEDIUMLOW  = LL_RCC_LSEDRIVE_MEDIUMLOW,  /*!< Crystal mode medium-low driving capability  */
  HAL_RCC_LSE_DRIVE_MEDIUMHIGH = LL_RCC_LSEDRIVE_MEDIUMHIGH, /*!< Crystal mode medium-high driving capability */
  HAL_RCC_LSE_DRIVE_HIGH       = LL_RCC_LSEDRIVE_HIGH        /*!< Crystal mode high driving capability        */
} hal_rcc_lse_drive_t;

/*! HAL RCC LSE CSS failure detection status enumeration definition */
typedef enum
{
  HAL_RCC_LSE_CSS_FAILURE_NOT_DETECTED  = 0U,  /*!< No Failure detected on LSE */
  HAL_RCC_LSE_CSS_FAILURE_DETECTED      = 1U   /*!< Failure detected on LSE    */
} hal_rcc_lse_css_failure_detection_status_t;
#endif /* (LSE_VALUE) */

/**
  * @brief HSI clock divider
  */
typedef enum
{
  HAL_RCC_HSI_DIV1 = LL_RCC_HSI_DIV_1, /*!< HSI not divided  */
  HAL_RCC_HSI_DIV2 = LL_RCC_HSI_DIV_2, /*!< HSI divided by 2 */
  HAL_RCC_HSI_DIV4 = LL_RCC_HSI_DIV_4, /*!< HSI divided by 4 */
  HAL_RCC_HSI_DIV8 = LL_RCC_HSI_DIV_8  /*!< HSI divided by 8 */
} hal_rcc_hsi_div_t;

/**
  * @brief Wake-Up from STOP Clock
  */
typedef enum
{
  HAL_RCC_STOP_WAKEUPCLOCK_HSI = LL_RCC_STOP_WAKEUPCLOCK_HSI, /*!< HSI selection after wake-up from STOP */
  HAL_RCC_STOP_WAKEUPCLOCK_CSI = LL_RCC_STOP_WAKEUPCLOCK_CSI  /*!< CSI selection after wake-up from STOP */
} hal_rcc_stop_wakeup_clk_t;

/**
  * @brief Wake-Up from STOP Kernel Clock
  */
typedef enum
{
  HAL_RCC_STOP_WAKEUPKERCLOCK_HSI = LL_RCC_STOP_WAKEUPKERCLOCK_HSI, /*!< HSI clock used as kernel clock after wake-up from STOP */
  HAL_RCC_STOP_WAKEUPKERCLOCK_CSI = LL_RCC_STOP_WAKEUPKERCLOCK_CSI  /*!< CSI clock used as kernel clock after wake-up from STOP */
} hal_rcc_stop_wakeup_kerclk_t;

/**
  * @brief System Clock Source
  */
typedef enum
{
  HAL_RCC_SYSCLK_SRC_HSI    = LL_RCC_SYS_CLKSOURCE_HSI,  /*!< HSI selection as system clock   */
  HAL_RCC_SYSCLK_SRC_CSI    = LL_RCC_SYS_CLKSOURCE_CSI,  /*!< CSI selection as system clock   */
  HAL_RCC_SYSCLK_SRC_HSE    = LL_RCC_SYS_CLKSOURCE_HSE,  /*!< HSE selection as system clock   */
  HAL_RCC_SYSCLK_SRC_PLLCLK = LL_RCC_SYS_CLKSOURCE_PLL1  /*!< PLL1P selection as system clock */
} hal_rcc_sysclk_src_t;

/**
  * @brief System Clock Divider.
  * @note  The system clock divider for CPU clock and all bus matrix clocks
  */
typedef enum
{
  HAL_RCC_SYSCLK_PRESCALER1   = LL_RCC_SYSCLK_PRESCALER_1,   /*!< SYSCLK is not divided */
  HAL_RCC_SYSCLK_PRESCALER2   = LL_RCC_SYSCLK_PRESCALER_2,   /*!< SYSCLK divided by 2   */
  HAL_RCC_SYSCLK_PRESCALER4   = LL_RCC_SYSCLK_PRESCALER_4,   /*!< SYSCLK divided by 4   */
  HAL_RCC_SYSCLK_PRESCALER8   = LL_RCC_SYSCLK_PRESCALER_8,   /*!< SYSCLK divided by 8   */
  HAL_RCC_SYSCLK_PRESCALER16  = LL_RCC_SYSCLK_PRESCALER_16,  /*!< SYSCLK divided by 16  */
  HAL_RCC_SYSCLK_PRESCALER64  = LL_RCC_SYSCLK_PRESCALER_64,  /*!< SYSCLK divided by 64  */
  HAL_RCC_SYSCLK_PRESCALER128 = LL_RCC_SYSCLK_PRESCALER_128, /*!< SYSCLK divided by 128 */
  HAL_RCC_SYSCLK_PRESCALER256 = LL_RCC_SYSCLK_PRESCALER_256, /*!< SYSCLK divided by 256 */
  HAL_RCC_SYSCLK_PRESCALER512 = LL_RCC_SYSCLK_PRESCALER_512  /*!< SYSCLK divided by 512 */
} hal_rcc_sysclk_prescaler_t;

/**
  * @brief AXI AHB bus Clock Prescaler
  */
typedef enum
{
  HAL_RCC_ACLK_PRESCALER1 = LL_RCC_BMCLK_PRESCALER_1, /*!< SYSCLK not divided  */
  HAL_RCC_ACLK_PRESCALER2 = LL_RCC_BMCLK_PRESCALER_2  /*!< SYSCLK divided by 2 */
} hal_rcc_aclk_prescaler_t;

/**
  * @brief APB1 APB2 APB4 Clock Source
  */
typedef enum
{
  HAL_RCC_PCLK_PRESCALER1  = LL_RCC_APB1_PRESCALER_1,  /*!< ACLK not divided   */
  HAL_RCC_PCLK_PRESCALER2  = LL_RCC_APB1_PRESCALER_2,  /*!< ACLK divided by 2  */
  HAL_RCC_PCLK_PRESCALER4  = LL_RCC_APB1_PRESCALER_4,  /*!< ACLK divided by 4  */
  HAL_RCC_PCLK_PRESCALER8  = LL_RCC_APB1_PRESCALER_8,  /*!< ACLK divided by 8  */
  HAL_RCC_PCLK_PRESCALER16 = LL_RCC_APB1_PRESCALER_16  /*!< ACLK divided by 16 */
} hal_rcc_pclk_prescaler_t;

/**
  * @brief RTC Clock Source
  */
typedef enum
{
  HAL_RCC_RTC_CLK_SRC_NONE      = LL_RCC_RTC_CLKSOURCE_NONE,    /*!< No clock used as RTC clock  */
  HAL_RCC_RTC_CLK_SRC_LSE       = LL_RCC_RTC_CLKSOURCE_LSE,     /*!< LSE clock used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_LSI       = LL_RCC_RTC_CLKSOURCE_LSI,     /*!< LSI clock used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV   = LL_RCC_RTC_CLKSOURCE_HSE_DIV, /*!< HSE oscillator clock divided by RTC prescaler used as RTC clock */
} hal_rcc_rtc_clk_src_t;

/**
  * @brief MCOx Clock Source
  */
typedef enum
{
  HAL_RCC_MCO1_SRC_HSI    = LL_RCC_MCO1SOURCE_HSI,    /*!< HSI selection as MCO1 source    */
  HAL_RCC_MCO1_SRC_LSE    = LL_RCC_MCO1SOURCE_LSE,    /*!< LSE selection as MCO1 source    */
  HAL_RCC_MCO1_SRC_HSE    = LL_RCC_MCO1SOURCE_HSE,    /*!< HSE selection as MCO1 source    */
  HAL_RCC_MCO1_SRC_PLL1Q  = LL_RCC_MCO1SOURCE_PLL1Q,  /*!< PLL1Q selection as MCO1 source  */
  HAL_RCC_MCO1_SRC_HSI48  = LL_RCC_MCO1SOURCE_HSI48,  /*!< HSI48 selection as MCO1 source  */
  HAL_RCC_MCO2_SRC_SYSCLK = LL_RCC_MCO2SOURCE_SYSCLK, /*!< SYSTEM selection as MCO2 source */
  HAL_RCC_MCO2_SRC_PLL2P  = LL_RCC_MCO2SOURCE_PLL2P,  /*!< PLL2P selection as MCO2 source  */
  HAL_RCC_MCO2_SRC_HSE    = LL_RCC_MCO2SOURCE_HSE,    /*!< HSE selection as MCO2 source    */
  HAL_RCC_MCO2_SRC_PLL1P  = LL_RCC_MCO2SOURCE_PLL1P,  /*!< PLL1P selection as MCO2 source  */
  HAL_RCC_MCO2_SRC_CSI    = LL_RCC_MCO2SOURCE_CSI,    /*!< CSI selection as MCO2 source    */
  HAL_RCC_MCO2_SRC_LSI    = LL_RCC_MCO2SOURCE_LSI,    /*!< LSI selection as MCO2 source    */
} hal_rcc_mco_src_t;

/**
  * @brief MCOx Clock Prescaler
  */
typedef enum
{
  HAL_RCC_MCO1_NO_CLK       = LL_RCC_MCO1SOURCE_NOCLOCK, /*!< MCO1 prescaler disabled, no clock on MCO1 */
  HAL_RCC_MCO1_PRESCALER1   = LL_RCC_MCO1_PRESCALER_1,   /*!< MCO1 is divided by 1     */
  HAL_RCC_MCO1_PRESCALER2   = LL_RCC_MCO1_PRESCALER_2,   /*!< MCO1 is divided by 2     */
  HAL_RCC_MCO1_PRESCALER3   = LL_RCC_MCO1_PRESCALER_3,   /*!< MCO1 is divided by 3     */
  HAL_RCC_MCO1_PRESCALER4   = LL_RCC_MCO1_PRESCALER_4,   /*!< MCO1 is divided by 4     */
  HAL_RCC_MCO1_PRESCALER5   = LL_RCC_MCO1_PRESCALER_5,   /*!< MCO1 is divided by 5     */
  HAL_RCC_MCO1_PRESCALER6   = LL_RCC_MCO1_PRESCALER_6,   /*!< MCO1 is divided by 6     */
  HAL_RCC_MCO1_PRESCALER7   = LL_RCC_MCO1_PRESCALER_7,   /*!< MCO1 is divided by 7     */
  HAL_RCC_MCO1_PRESCALER8   = LL_RCC_MCO1_PRESCALER_8,   /*!< MCO1 is divided by 8     */
  HAL_RCC_MCO1_PRESCALER9   = LL_RCC_MCO1_PRESCALER_9,   /*!< MCO1 is divided by 9     */
  HAL_RCC_MCO1_PRESCALER10  = LL_RCC_MCO1_PRESCALER_10,  /*!< MCO1 is divided by 10    */
  HAL_RCC_MCO1_PRESCALER11  = LL_RCC_MCO1_PRESCALER_11,  /*!< MCO1 is divided by 11    */
  HAL_RCC_MCO1_PRESCALER12  = LL_RCC_MCO1_PRESCALER_12,  /*!< MCO1 is divided by 12    */
  HAL_RCC_MCO1_PRESCALER13  = LL_RCC_MCO1_PRESCALER_13,  /*!< MCO1 is divided by 13    */
  HAL_RCC_MCO1_PRESCALER14  = LL_RCC_MCO1_PRESCALER_14,  /*!< MCO1 is divided by 14    */
  HAL_RCC_MCO1_PRESCALER15  = LL_RCC_MCO1_PRESCALER_15,  /*!< MCO1 is divided by 15    */
  HAL_RCC_MCO2_NO_CLK       = LL_RCC_MCO2SOURCE_NOCLOCK, /*!< MCO2 prescaler disabled, no clock on MCO2 */
  HAL_RCC_MCO2_PRESCALER1   = LL_RCC_MCO2_PRESCALER_1,   /*!< MCO2 is divided by 1     */
  HAL_RCC_MCO2_PRESCALER2   = LL_RCC_MCO2_PRESCALER_2,   /*!< MCO2 is divided by 2     */
  HAL_RCC_MCO2_PRESCALER3   = LL_RCC_MCO2_PRESCALER_3,   /*!< MCO2 is divided by 3     */
  HAL_RCC_MCO2_PRESCALER4   = LL_RCC_MCO2_PRESCALER_4,   /*!< MCO2 is divided by 4     */
  HAL_RCC_MCO2_PRESCALER5   = LL_RCC_MCO2_PRESCALER_5,   /*!< MCO2 is divided by 5     */
  HAL_RCC_MCO2_PRESCALER6   = LL_RCC_MCO2_PRESCALER_6,   /*!< MCO2 is divided by 6     */
  HAL_RCC_MCO2_PRESCALER7   = LL_RCC_MCO2_PRESCALER_7,   /*!< MCO2 is divided by 7     */
  HAL_RCC_MCO2_PRESCALER8   = LL_RCC_MCO2_PRESCALER_8,   /*!< MCO2 is divided by 8     */
  HAL_RCC_MCO2_PRESCALER9   = LL_RCC_MCO2_PRESCALER_9,   /*!< MCO2 is divided by 9     */
  HAL_RCC_MCO2_PRESCALER10  = LL_RCC_MCO2_PRESCALER_10,  /*!< MCO2 is divided by 10    */
  HAL_RCC_MCO2_PRESCALER11  = LL_RCC_MCO2_PRESCALER_11,  /*!< MCO2 is divided by 11    */
  HAL_RCC_MCO2_PRESCALER12  = LL_RCC_MCO2_PRESCALER_12,  /*!< MCO2 is divided by 12    */
  HAL_RCC_MCO2_PRESCALER13  = LL_RCC_MCO2_PRESCALER_13,  /*!< MCO2 is divided by 13    */
  HAL_RCC_MCO2_PRESCALER14  = LL_RCC_MCO2_PRESCALER_14,  /*!< MCO2 is divided by 14    */
  HAL_RCC_MCO2_PRESCALER15  = LL_RCC_MCO2_PRESCALER_15,  /*!< MCO2 is divided by 15    */
} hal_rcc_mco_prescaler_t;

/**
  * @brief PLL activation status
  */
typedef enum
{
  HAL_RCC_PLL_DISABLED = 0U,                          /*!< PLL is disabled */
  HAL_RCC_PLL_ENABLED = ! HAL_RCC_PLL_DISABLED        /*!< PLL is enabled  */
} hal_rcc_pll_status_t;

/**
  * @brief RCC PLLx Clock Source
  */
typedef enum
{
  HAL_RCC_PLL_SRC_HSI    = LL_RCC_PLLSOURCE_HSI,   /*!< HSI clock selected as PLLx entry clock source  */
  HAL_RCC_PLL_SRC_CSI    = LL_RCC_PLLSOURCE_CSI,   /*!< CSI clock selected as PLLx entry clock source  */
  HAL_RCC_PLL_SRC_HSE    = LL_RCC_PLLSOURCE_HSE,   /*!< HSE clock selected as PLLx entry clock source  */
  HAL_RCC_PLL_SRC_NO_CLK = LL_RCC_PLLSOURCE_NO_CLK /*!< No clock selected as PLLx entry clock source   */
} hal_rcc_pll_src_t;

/**
  * @brief  RCC PLL Spread-spectrum Modulation state
  */
typedef enum
{
  HAL_RCC_PLL_SSCG_DISABLE = 0U, /*!< PLL spread spectrum mode disable  */
  HAL_RCC_PLL_SSCG_ENABLE  = 1U  /*!< PLL spread spectrum mode enable   */
} hal_rcc_pll_sscg_state_t;

/**
  * @brief RCC PLL Spread-spectrum Modulation spread configuration
  */
typedef enum
{
  HAL_RCC_PLL_SSCG_SPREAD_CENTER = LL_RCC_PLL_SPREAD_CENTER, /*!< PLL center spread spectrum selection */
  HAL_RCC_PLL_SSCG_SPREAD_DOWN   = LL_RCC_PLL_SPREAD_DOWN,   /*!< PLL down spread spectrum selection   */
} hal_rcc_pll_sscg_spread_mode_t;

/**
  * @brief RCC PLL Spread-spectrum Dithering configuration
  */
typedef enum
{
  HAL_RCC_PLL_SSCG_DITH_NO        = LL_RCC_PLL_SSCG_DITH_NO,        /*!< Dithering noise control for PLL not enabled         */
  HAL_RCC_PLL_SSCG_DITH_RPDF      = LL_RCC_PLL_SSCG_DITH_RPDF,      /*!< Dithering RPDF noise control for PLL enabled        */
  HAL_RCC_PLL_SSCG_DITH_TPDF      = LL_RCC_PLL_SSCG_DITH_TPDF,      /*!< Dithering TPDF noise control for PLL enabled        */
  HAL_RCC_PLL_SSCG_DITH_RPDF_TPDF = LL_RCC_PLL_SSCG_DITH_RPDF_TPDF, /*!< Dithering RPDF & TPDF noise control for PLL enabled */
} hal_rcc_pll_sscg_dith_ctrl_t;

/**
  * @brief  RCC PLLx Input Range (ref_ck)
  */
typedef enum
{
  HAL_RCC_PLL_INPUT_RANGE_1_2  = LL_RCC_PLL1INPUTRANGE_1_2,  /*!< PLLx input clock range frequency between 1 and 2 MHz  */
  HAL_RCC_PLL_INPUT_RANGE_2_4  = LL_RCC_PLL1INPUTRANGE_2_4,  /*!< PLLx input clock range frequency between 2 and 4 MHz  */
  HAL_RCC_PLL_INPUT_RANGE_4_8  = LL_RCC_PLL1INPUTRANGE_4_8,  /*!< PLLx input clock range frequency between 4 and 8 MHz  */
  HAL_RCC_PLL_INPUT_RANGE_8_16 = LL_RCC_PLL1INPUTRANGE_8_16, /*!< PLLx input clock range frequency between 8 and 16 MHz */
} hal_rcc_pll_input_range_t;

/**
  * @brief  RCC PLLx VCO Range
  */
typedef enum
{
  HAL_RCC_PLL_VCO_RANGE_384_1672 = LL_RCC_PLL1VCORANGE_384_1672, /*!< PLLx VCO clock range frequency between 384 and 1672 MHz */
  HAL_RCC_PLL_VCO_RANGE_150_420  = LL_RCC_PLL1VCORANGE_150_420,  /*!< PLLx VCO clock range frequency between 150 and 420 MHz  */
} hal_rcc_pll_vco_range_t;

/**
  * @brief Common peripheral Clock Source
  */
typedef enum
{
  HAL_RCC_PERCLK_SRC_HSI = LL_RCC_PER_CLKSOURCE_HSI, /*!< HSI selected as PER kernel clock */
  HAL_RCC_PERCLK_SRC_CSI = LL_RCC_PER_CLKSOURCE_CSI, /*!< CSI selected as PER kernel clock */
  HAL_RCC_PERCLK_SRC_HSE = LL_RCC_PER_CLKSOURCE_HSE  /*!< HSE selected as PER kernel clock */
} hal_rcc_perclk_src_t;

/**
  * @brief FMC Clock Source
  */
typedef enum
{
  HAL_RCC_FMC_CLK_SRC_HCLK5 = LL_RCC_FMC_CLKSOURCE_HCLK5, /*!< HCLK5 selected as FMC kernel clock */
  HAL_RCC_FMC_CLK_SRC_PLL1Q = LL_RCC_FMC_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as FMC kernel clock */
  HAL_RCC_FMC_CLK_SRC_PLL2R = LL_RCC_FMC_CLKSOURCE_PLL2R, /*!< PLL2R selected as FMC kernel clock */
  HAL_RCC_FMC_CLK_SRC_HSI   = LL_RCC_FMC_CLKSOURCE_HSI    /*!< HSI selected as FMC kernel clock   */
} hal_rcc_fmc_clk_src_t;

/**
  * @brief SDMMC1 Clock Source
  */
typedef enum
{
  HAL_RCC_SDMMC1_CLK_SRC_PLL2S = LL_RCC_SDMMC1_CLKSOURCE_PLL2S, /*!< PLL2S selected as SDMMC1 kernel clock */
  HAL_RCC_SDMMC1_CLK_SRC_PLL2T = LL_RCC_SDMMC1_CLKSOURCE_PLL2T  /*!< PLL2T selected as SDMMC1 kernel clock */
} hal_rcc_sdmmc1_clk_src_t;

/**
  * @brief XSPI1 Clock Source
  */
typedef enum
{
  HAL_RCC_XSPI1_CLK_SRC_HCLK5 = LL_RCC_XSPI1_CLKSOURCE_HCLK5, /*!< HCLK5 selected as XSPI1 kernel clock */
  HAL_RCC_XSPI1_CLK_SRC_PLL2S = LL_RCC_XSPI1_CLKSOURCE_PLL2S, /*!< PLL2S selected as XSPI1 kernel clock */
  HAL_RCC_XSPI1_CLK_SRC_PLL2T = LL_RCC_XSPI1_CLKSOURCE_PLL2T  /*!< PLL2T selected as XSPI1 kernel clock */
} hal_rcc_xspi1_clk_src_t;

/**
  * @brief USBOTGFS Clock Source
  */
typedef enum
{
  HAL_RCC_USBOTGFS_CLK_SRC_HSI48     = LL_RCC_USBOTGFS_CLKSOURCE_HSI48,     /*!< HSI48 selected as USB OTGFS kernel clock */
  HAL_RCC_USBOTGFS_CLK_SRC_PLL3Q     = LL_RCC_USBOTGFS_CLKSOURCE_PLL3Q,     /*!< PLL3Q selected as USB OTGFS kernel clock */
  HAL_RCC_USBOTGFS_CLK_SRC_HSE       = LL_RCC_USBOTGFS_CLKSOURCE_HSE,       /*!< HSE selected as USB OTGFS kernel clock   */
} hal_rcc_usbotgfs_clk_src_t;

/**
  * @brief ADF1 Clock Source
  */
typedef enum
{
  HAL_RCC_ADF1_CLK_SRC_HCLK1      = LL_RCC_ADF1_CLKSOURCE_HCLK1,    /*!< HCLK1 selected as ADF1 kernel clock    */
  HAL_RCC_ADF1_CLK_SRC_PLL2P      = LL_RCC_ADF1_CLKSOURCE_PLL2P,    /*!< PLL2P selected as ADF1 kernel clock    */
  HAL_RCC_ADF1_CLK_SRC_PLL3P      = LL_RCC_ADF1_CLKSOURCE_PLL3P,    /*!< PLL3P selected as ADF1 kernel clock    */
  HAL_RCC_ADF1_CLK_SRC_AUDIOCLK   = LL_RCC_ADF1_CLKSOURCE_AUDIOCLK, /*!< AUDIOCLK selected as ADF1 kernel clock */
  HAL_RCC_ADF1_CLK_SRC_CSI        = LL_RCC_ADF1_CLKSOURCE_CSI,      /*!< CSI selected as ADF1 kernel clock      */
  HAL_RCC_ADF1_CLK_SRC_HSI        = LL_RCC_ADF1_CLKSOURCE_HSI       /*!< HSI selected as ADF1 kernel clock      */
} hal_rcc_adf1_clk_src_t;

/**
  * @brief ADC Clock Source
  */
typedef enum
{
  HAL_RCC_ADC_CLK_SRC_HCLK3 = LL_RCC_ADC_CLKSOURCE_HCLK3, /*!< HCLK3 selected as ADC kernel clock */
  HAL_RCC_ADC_CLK_SRC_TIM   = LL_RCC_ADC_CLKSOURCE_TIM,   /*!< TIM selected as ADC kernel clock   */
  HAL_RCC_ADC_CLK_SRC_HSI   = LL_RCC_ADC_CLKSOURCE_HSI,   /*!< HSI selected as ADC kernel clock   */
  HAL_RCC_ADC_CLK_SRC_HSE   = LL_RCC_ADC_CLKSOURCE_HSE,   /*!< HSE selected as ADC kernel clock   */
  HAL_RCC_ADC_CLK_SRC_PLL2P = LL_RCC_ADC_CLKSOURCE_PLL2P, /*!< PLL2P selected as ADC kernel clock */
  HAL_RCC_ADC_CLK_SRC_PLL3R = LL_RCC_ADC_CLKSOURCE_PLL3R, /*!< PLL3R selected as ADC kernel clock */
  HAL_RCC_ADC_CLK_SRC_PER   = LL_RCC_ADC_CLKSOURCE_PER    /*!< PER selected as ADC kernel clock   */
} hal_rcc_adc_clk_src_t;

/**
  * @brief ADC Clock Divider
  */
typedef enum
{
  HAL_RCC_ADC_CLK_PRESCALER1   = LL_RCC_ADC_PRESCALER_1,    /*!< ADC kernel clock is not divided    */
  HAL_RCC_ADC_CLK_PRESCALER2   = LL_RCC_ADC_PRESCALER_2,    /*!< ADC kernel clock is divided by 2   */
  HAL_RCC_ADC_CLK_PRESCALER4   = LL_RCC_ADC_PRESCALER_4,    /*!< ADC kernel clock is divided by 4   */
  HAL_RCC_ADC_CLK_PRESCALER6   = LL_RCC_ADC_PRESCALER_6,    /*!< ADC kernel clock is divided by 6   */
  HAL_RCC_ADC_CLK_PRESCALER8   = LL_RCC_ADC_PRESCALER_8,    /*!< ADC kernel clock is divided by 8   */
  HAL_RCC_ADC_CLK_PRESCALER10  = LL_RCC_ADC_PRESCALER_10,   /*!< ADC kernel clock is divided by 10  */
  HAL_RCC_ADC_CLK_PRESCALER12  = LL_RCC_ADC_PRESCALER_12,   /*!< ADC kernel clock is divided by 12  */
  HAL_RCC_ADC_CLK_PRESCALER16  = LL_RCC_ADC_PRESCALER_16,   /*!< ADC kernel clock is divided by 16  */
  HAL_RCC_ADC_CLK_PRESCALER32  = LL_RCC_ADC_PRESCALER_32,   /*!< ADC kernel clock is divided by 32  */
  HAL_RCC_ADC_CLK_PRESCALER64  = LL_RCC_ADC_PRESCALER_64,   /*!< ADC kernel clock is divided by 64  */
  HAL_RCC_ADC_CLK_PRESCALER128 = LL_RCC_ADC_PRESCALER_128,  /*!< ADC kernel clock is divided by 128 */
  HAL_RCC_ADC_CLK_PRESCALER256 = LL_RCC_ADC_PRESCALER_256   /*!< ADC kernel clock is divided by 256 */
} hal_rcc_adc_prescaler_t;

/**
  * @brief UART234578 Clock Source
  */
typedef enum
{
  HAL_RCC_UART234578_CLK_SRC_PCLK1 = LL_RCC_UART234578_CLKSOURCE_PCLK1, /*!< PCLK1 selected as UART234578 kernel clock */
  HAL_RCC_UART234578_CLK_SRC_PLL2Q = LL_RCC_UART234578_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as UART234578 kernel clock */
  HAL_RCC_UART234578_CLK_SRC_PLL3Q = LL_RCC_UART234578_CLKSOURCE_PLL3Q, /*!< PLL3Q selected as UART234578 kernel clock */
  HAL_RCC_UART234578_CLK_SRC_HSI   = LL_RCC_UART234578_CLKSOURCE_HSI,   /*!< HSI selected as UART234578 kernel clock   */
  HAL_RCC_UART234578_CLK_SRC_CSI   = LL_RCC_UART234578_CLKSOURCE_CSI,   /*!< CSI selected as UART234578 kernel clock   */
  HAL_RCC_UART234578_CLK_SRC_LSE   = LL_RCC_UART234578_CLKSOURCE_LSE    /*!< LSE selected as UART234578 kernel clock   */
} hal_rcc_uart234578_clk_src_t;

/**
  * @brief SPI23 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI23_CLK_SRC_PLL1Q    = LL_RCC_SPI23_CLKSOURCE_PLL1Q,    /*!< PLL1Q selected as SPI23 kernel clock    */
  HAL_RCC_SPI23_CLK_SRC_PLL2P    = LL_RCC_SPI23_CLKSOURCE_PLL2P,    /*!< PLL2P selected as SPI23 kernel clock    */
  HAL_RCC_SPI23_CLK_SRC_PLL3P    = LL_RCC_SPI23_CLKSOURCE_PLL3P,    /*!< PLL3P selected as SPI23 kernel clock    */
  HAL_RCC_SPI23_CLK_SRC_AUDIOCLK = LL_RCC_SPI23_CLKSOURCE_AUDIOCLK, /*!< AUDIOCLK selected as SPI23 kernel clock */
  HAL_RCC_SPI23_CLK_SRC_PER      = LL_RCC_SPI23_CLKSOURCE_PER       /*!< PER selected as SPI23 kernel clock      */
} hal_rcc_spi23_clk_src_t;

/**
  * @brief I2C123 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C123_CLK_SRC_PCLK1 = LL_RCC_I2C123_CLKSOURCE_PCLK1,  /*!< PCLK1 selected as I2C123 kernel clock */
  HAL_RCC_I2C123_CLK_SRC_PLL3R = LL_RCC_I2C123_CLKSOURCE_PLL3R,  /*!< PLL3R selected as I2C123 kernel clock */
  HAL_RCC_I2C123_CLK_SRC_HSI   = LL_RCC_I2C123_CLKSOURCE_HSI,    /*!< HSI selected as I2C123 kernel clock   */
  HAL_RCC_I2C123_CLK_SRC_CSI   = LL_RCC_I2C123_CLKSOURCE_CSI     /*!< CSI selected as I2C123 kernel clock   */
} hal_rcc_i2c123_clk_src_t;

/**
  * @brief I3C1 Clock Source
  */
typedef enum
{
  HAL_RCC_I3C1_CLK_SRC_PCLK1 = LL_RCC_I3C1_CLKSOURCE_PCLK1, /*!< PCLK1 selected as I3C1 kernel clock */
  HAL_RCC_I3C1_CLK_SRC_PLL3R = LL_RCC_I3C1_CLKSOURCE_PLL3R, /*!< PLL3R selected as I3C1 kernel clock */
  HAL_RCC_I3C1_CLK_SRC_HSI   = LL_RCC_I3C1_CLKSOURCE_HSI,   /*!< HSI selected as I3C1 kernel clock   */
  HAL_RCC_I3C1_CLK_SRC_CSI   = LL_RCC_I3C1_CLKSOURCE_CSI    /*!< CSI selected as I3C1 kernel clock   */
} hal_rcc_i3c1_clk_src_t;

/**
  * @brief LPTIM1 Clock Source
  */
typedef enum
{
  HAL_RCC_LPTIM1_CLK_SRC_PCLK1 = LL_RCC_LPTIM1_CLKSOURCE_PCLK1, /*!< PCLK1 selected as LPTIM1 kernel clock */
  HAL_RCC_LPTIM1_CLK_SRC_PLL2P = LL_RCC_LPTIM1_CLKSOURCE_PLL2P, /*!< PLL2P selected as LPTIM1 kernel clock */
  HAL_RCC_LPTIM1_CLK_SRC_PLL3R = LL_RCC_LPTIM1_CLKSOURCE_PLL3R, /*!< PLL3R selected as LPTIM1 kernel clock */
  HAL_RCC_LPTIM1_CLK_SRC_LSE   = LL_RCC_LPTIM1_CLKSOURCE_LSE,   /*!< LSE selected as LPTIM1 kernel clock   */
  HAL_RCC_LPTIM1_CLK_SRC_LSI   = LL_RCC_LPTIM1_CLKSOURCE_LSI,   /*!< LSI selected as LPTIM1 kernel clock   */
  HAL_RCC_LPTIM1_CLK_SRC_PER   = LL_RCC_LPTIM1_CLKSOURCE_PER    /*!< PER selected as LPTIM1 kernel clock   */
} hal_rcc_lptim1_clk_src_t;

/**
  * @brief FDCAN Clock Source
  */
typedef enum
{
  HAL_RCC_FDCAN_CLK_SRC_HSE   = LL_RCC_FDCAN_CLKSOURCE_HSE,   /*!< HSE selected as FDCAN kernel clock   */
  HAL_RCC_FDCAN_CLK_SRC_PLL1Q = LL_RCC_FDCAN_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as FDCAN kernel clock */
  HAL_RCC_FDCAN_CLK_SRC_PLL2P = LL_RCC_FDCAN_CLKSOURCE_PLL2P, /*!< PLL2P selected as FDCAN kernel clock */
} hal_rcc_fdcan_clk_src_t;

/**
  * @brief USART16910 Clock Source
  */
typedef enum
{
  HAL_RCC_USART16910_CLK_SRC_PCLK2 = LL_RCC_USART16910_CLKSOURCE_PCLK2, /*!< PCLK2 selected as USART16910 kernel clock */
  HAL_RCC_USART16910_CLK_SRC_PLL2Q = LL_RCC_USART16910_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as USART16910 kernel clock */
  HAL_RCC_USART16910_CLK_SRC_PLL3Q = LL_RCC_USART16910_CLKSOURCE_PLL3Q, /*!< PLL3Q selected as USART16910 kernel clock */
  HAL_RCC_USART16910_CLK_SRC_HSI   = LL_RCC_USART16910_CLKSOURCE_HSI,   /*!< HSI selected as USART16910 kernel clock   */
  HAL_RCC_USART16910_CLK_SRC_CSI   = LL_RCC_USART16910_CLKSOURCE_CSI,   /*!< CSI selected as USART16910 kernel clock   */
  HAL_RCC_USART16910_CLK_SRC_LSE   = LL_RCC_USART16910_CLKSOURCE_LSE    /*!< LSE selected as USART16910 kernel clock   */
} hal_rcc_usart16910_clk_src_t;

/**
  * @brief SPI45 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI45_CLK_SRC_PCLK2 = LL_RCC_SPI45_CLKSOURCE_PCLK2, /*!< PCLK2 selected as SPI45 kernel clock */
  HAL_RCC_SPI45_CLK_SRC_PLL2Q = LL_RCC_SPI45_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as SPI45 kernel clock */
  HAL_RCC_SPI45_CLK_SRC_PLL3Q = LL_RCC_SPI45_CLKSOURCE_PLL3Q, /*!< PLL3Q selected as SPI45 kernel clock */
  HAL_RCC_SPI45_CLK_SRC_HSI   = LL_RCC_SPI45_CLKSOURCE_HSI,   /*!< HSI selected as SPI45 kernel clock   */
  HAL_RCC_SPI45_CLK_SRC_CSI   = LL_RCC_SPI45_CLKSOURCE_CSI,   /*!< CSI selected as SPI45 kernel clock   */
  HAL_RCC_SPI45_CLK_SRC_HSE   = LL_RCC_SPI45_CLKSOURCE_HSE    /*!< HSE selected as SPI45 kernel clock   */
} hal_rcc_spi45_clk_src_t;

/**
  * @brief SPI1 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI1_CLK_SRC_PLL1Q    = LL_RCC_SPI1_CLKSOURCE_PLL1Q,    /*!< PLL1Q selected as SPI1 kernel clock    */
  HAL_RCC_SPI1_CLK_SRC_PLL2P    = LL_RCC_SPI1_CLKSOURCE_PLL2P,    /*!< PLL2P selected as SPI1 kernel clock    */
  HAL_RCC_SPI1_CLK_SRC_PLL3P    = LL_RCC_SPI1_CLKSOURCE_PLL3P,    /*!< PLL3P selected as SPI1 kernel clock    */
  HAL_RCC_SPI1_CLK_SRC_AUDIOCLK = LL_RCC_SPI1_CLKSOURCE_AUDIOCLK, /*!< AUDIOCLK selected as SPI1 kernel clock */
  HAL_RCC_SPI1_CLK_SRC_PER      = LL_RCC_SPI1_CLKSOURCE_PER       /*!< PER selected as SPI1 kernel clock      */
} hal_rcc_spi1_clk_src_t;

/**
  * @brief LPUART1 Clock Source
  */
typedef enum
{
  HAL_RCC_LPUART1_CLK_SRC_PCLK4 = LL_RCC_LPUART1_CLKSOURCE_PCLK4, /*!< PCLK4 selected as LPUART1 kernel clock */
  HAL_RCC_LPUART1_CLK_SRC_PLL2Q = LL_RCC_LPUART1_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as LPUART1 kernel clock */
  HAL_RCC_LPUART1_CLK_SRC_PLL3Q = LL_RCC_LPUART1_CLKSOURCE_PLL3Q, /*!< PLL3Q selected as LPUART1 kernel clock */
  HAL_RCC_LPUART1_CLK_SRC_HSI   = LL_RCC_LPUART1_CLKSOURCE_HSI,   /*!< HSI selected as LPUART1 kernel clock   */
  HAL_RCC_LPUART1_CLK_SRC_CSI   = LL_RCC_LPUART1_CLKSOURCE_CSI,   /*!< CSI selected as LPUART1 kernel clock   */
  HAL_RCC_LPUART1_CLK_SRC_LSE   = LL_RCC_LPUART1_CLKSOURCE_LSE    /*!< LSE selected as LPUART1 kernel clock   */
} hal_rcc_lpuart1_clk_src_t;

/**
  * @brief SPI6 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI6_CLK_SRC_PCLK4 = LL_RCC_SPI6_CLKSOURCE_PCLK4, /*!< PCLK4 selected as SPI6 kernel clock */
  HAL_RCC_SPI6_CLK_SRC_PLL2Q = LL_RCC_SPI6_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as SPI6 kernel clock */
  HAL_RCC_SPI6_CLK_SRC_PLL3Q = LL_RCC_SPI6_CLKSOURCE_PLL3Q, /*!< PLL3Q selected as SPI6 kernel clock */
  HAL_RCC_SPI6_CLK_SRC_HSI   = LL_RCC_SPI6_CLKSOURCE_HSI,   /*!< HSI selected as SPI6 kernel clock   */
  HAL_RCC_SPI6_CLK_SRC_CSI   = LL_RCC_SPI6_CLKSOURCE_CSI,   /*!< CSI selected as SPI6 kernel clock   */
  HAL_RCC_SPI6_CLK_SRC_HSE   = LL_RCC_SPI6_CLKSOURCE_HSE    /*!< HSE selected as SPI6 kernel clock   */
} hal_rcc_spi6_clk_src_t;

/**
  * @brief LPTIM23 Clock Source
  */
typedef enum
{
  HAL_RCC_LPTIM23_CLK_SRC_PCLK4 = LL_RCC_LPTIM23_CLKSOURCE_PCLK4, /*!< PCLK4 selected as LPTIM23 kernel clock */
  HAL_RCC_LPTIM23_CLK_SRC_PLL2P = LL_RCC_LPTIM23_CLKSOURCE_PLL2P, /*!< PLL2P selected as LPTIM23 kernel clock */
  HAL_RCC_LPTIM23_CLK_SRC_PLL3R = LL_RCC_LPTIM23_CLKSOURCE_PLL3R, /*!< PLL3R selected as LPTIM23 kernel clock */
  HAL_RCC_LPTIM23_CLK_SRC_LSE   = LL_RCC_LPTIM23_CLKSOURCE_LSE,   /*!< LSE selected as LPTIM23 kernel clock   */
  HAL_RCC_LPTIM23_CLK_SRC_LSI   = LL_RCC_LPTIM23_CLKSOURCE_LSI,   /*!< LSI selected as LPTIM23 kernel clock   */
  HAL_RCC_LPTIM23_CLK_SRC_PER   = LL_RCC_LPTIM23_CLKSOURCE_PER    /*!< PER selected as LPTIM23 kernel clock   */
} hal_rcc_lptim23_clk_src_t;

/**
  * @brief LPTIM45 Clock Source
  */
typedef enum
{
  HAL_RCC_LPTIM45_CLK_SRC_PCLK4 = LL_RCC_LPTIM45_CLKSOURCE_PCLK4, /*!< PCLK4 selected as LPTIM45 kernel clock */
  HAL_RCC_LPTIM45_CLK_SRC_PLL2P = LL_RCC_LPTIM45_CLKSOURCE_PLL2P, /*!< PLL2P selected as LPTIM45 kernel clock */
  HAL_RCC_LPTIM45_CLK_SRC_PLL3R = LL_RCC_LPTIM45_CLKSOURCE_PLL3R, /*!< PLL3R selected as LPTIM45 kernel clock */
  HAL_RCC_LPTIM45_CLK_SRC_LSE   = LL_RCC_LPTIM45_CLKSOURCE_LSE,   /*!< LSE selected as LPTIM45 kernel clock   */
  HAL_RCC_LPTIM45_CLK_SRC_LSI   = LL_RCC_LPTIM45_CLKSOURCE_LSI,   /*!< LSI selected as LPTIM45 kernel clock   */
  HAL_RCC_LPTIM45_CLK_SRC_PER   = LL_RCC_LPTIM45_CLKSOURCE_PER    /*!< PER selected as LPTIM45 kernel clock   */
} hal_rcc_lptim45_clk_src_t;

/**
  * @brief DAC1 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC1_CLK_SRC_HCLK3 = LL_RCC_DAC1_CLKSOURCE_HCLK3, /*!< HCLK3 selected as DAC1 kernel clock */
  HAL_RCC_DAC1_CLK_SRC_TIM   = LL_RCC_DAC1_CLKSOURCE_TIM,   /*!< TIM selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_ADC   = LL_RCC_DAC1_CLKSOURCE_ADC,   /*!< ADC selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_HSI   = LL_RCC_DAC1_CLKSOURCE_HSI,   /*!< HSI selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_HSE   = LL_RCC_DAC1_CLKSOURCE_HSE,   /*!< HSE selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_PLL2P = LL_RCC_DAC1_CLKSOURCE_PLL2P, /*!< PLL2P selected as DAC1 kernel clock */
  HAL_RCC_DAC1_CLK_SRC_PLL3R = LL_RCC_DAC1_CLKSOURCE_PLL3R, /*!< PLL3R selected as DAC1 kernel clock */
  HAL_RCC_DAC1_CLK_SRC_PER   = LL_RCC_DAC1_CLKSOURCE_PER    /*!< PER selected as DAC1 kernel clock   */
} hal_rcc_dac1_clk_src_t;

/**
  * @brief DAC1 sample-and-hold clock source
  */
typedef enum
{
  HAL_RCC_DAC1SH_CLK_SRC_LSE = LL_RCC_DAC1SH_CLKSOURCE_LSE, /*!< LSE selected as DAC1SH kernel clock */
  HAL_RCC_DAC1SH_CLK_SRC_LSI = LL_RCC_DAC1SH_CLKSOURCE_LSI  /*!< LSI selected as DAC1SH kernel clock */
} hal_rcc_dac1sh_clk_src_t;

/**
  * @brief DAC2 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC2_CLK_SRC_HCLK3 = LL_RCC_DAC2_CLKSOURCE_HCLK3, /*!< HCLK3 selected as DAC2 kernel clock */
  HAL_RCC_DAC2_CLK_SRC_TIM   = LL_RCC_DAC2_CLKSOURCE_TIM,   /*!< TIM selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_ADC   = LL_RCC_DAC2_CLKSOURCE_ADC,   /*!< ADC selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_HSI   = LL_RCC_DAC2_CLKSOURCE_HSI,   /*!< HSI selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_HSE   = LL_RCC_DAC2_CLKSOURCE_HSE,   /*!< HSE selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_PLL2P = LL_RCC_DAC2_CLKSOURCE_PLL2P, /*!< PLL2P selected as DAC2 kernel clock */
  HAL_RCC_DAC2_CLK_SRC_PLL3R = LL_RCC_DAC2_CLKSOURCE_PLL3R, /*!< PLL3R selected as DAC2 kernel clock */
  HAL_RCC_DAC2_CLK_SRC_PER   = LL_RCC_DAC2_CLKSOURCE_PER    /*!< PER selected as DAC2 kernel clock   */
} hal_rcc_dac2_clk_src_t;

/**
  * @brief DAC3 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC3_CLK_SRC_HCLK3 = LL_RCC_DAC3_CLKSOURCE_HCLK3, /*!< HCLK3 selected as DAC3 kernel clock */
  HAL_RCC_DAC3_CLK_SRC_TIM   = LL_RCC_DAC3_CLKSOURCE_TIM,   /*!< TIM selected as DAC3 kernel clock   */
  HAL_RCC_DAC3_CLK_SRC_ADC   = LL_RCC_DAC3_CLKSOURCE_ADC,   /*!< ADC selected as DAC3 kernel clock   */
  HAL_RCC_DAC3_CLK_SRC_HSI   = LL_RCC_DAC3_CLKSOURCE_HSI,   /*!< HSI selected as DAC3 kernel clock   */
  HAL_RCC_DAC3_CLK_SRC_HSE   = LL_RCC_DAC3_CLKSOURCE_HSE,   /*!< HSE selected as DAC3 kernel clock   */
  HAL_RCC_DAC3_CLK_SRC_PLL2P = LL_RCC_DAC3_CLKSOURCE_PLL2P, /*!< PLL2P selected as DAC3 kernel clock */
  HAL_RCC_DAC3_CLK_SRC_PLL3R = LL_RCC_DAC3_CLKSOURCE_PLL3R, /*!< PLL3R selected as DAC3 kernel clock */
  HAL_RCC_DAC3_CLK_SRC_PER   = LL_RCC_DAC3_CLKSOURCE_PER    /*!< PER selected as DAC3 kernel clock   */
} hal_rcc_dac3_clk_src_t;

/**
  * @brief DAC4 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC4_CLK_SRC_HCLK3 = LL_RCC_DAC4_CLKSOURCE_HCLK3, /*!< HCLK3 selected as DAC4 kernel clock */
  HAL_RCC_DAC4_CLK_SRC_TIM   = LL_RCC_DAC4_CLKSOURCE_TIM,   /*!< TIM selected as DAC4 kernel clock   */
  HAL_RCC_DAC4_CLK_SRC_ADC   = LL_RCC_DAC4_CLKSOURCE_ADC,   /*!< ADC selected as DAC4 kernel clock   */
  HAL_RCC_DAC4_CLK_SRC_HSI   = LL_RCC_DAC4_CLKSOURCE_HSI,   /*!< HSI selected as DAC4 kernel clock   */
  HAL_RCC_DAC4_CLK_SRC_HSE   = LL_RCC_DAC4_CLKSOURCE_HSE,   /*!< HSE selected as DAC4 kernel clock   */
  HAL_RCC_DAC4_CLK_SRC_PLL2P = LL_RCC_DAC4_CLKSOURCE_PLL2P, /*!< PLL2P selected as DAC4 kernel clock */
  HAL_RCC_DAC4_CLK_SRC_PLL3R = LL_RCC_DAC4_CLKSOURCE_PLL3R, /*!< PLL3R selected as DAC4 kernel clock */
  HAL_RCC_DAC4_CLK_SRC_PER   = LL_RCC_DAC4_CLKSOURCE_PER    /*!< PER selected as DAC4 kernel clock   */
} hal_rcc_dac4_clk_src_t;

/**
  * @brief FMC kernel clock switch position
  */
typedef enum
{
  HAL_RCC_FMC_CLK_SRC_SWP_NEUTRAL    = LL_RCC_FMC_CLKSOURCE_SWP_NEUTRAL,   /*!< Neutral mode and clock is gated                      */
  HAL_RCC_FMC_CLK_SRC_SWP_HCLK5      = LL_RCC_FMC_CLKSOURCE_SWP_HCLK5,     /*!< HCLK5 clock switch selected as FMC clock source      */
  HAL_RCC_FMC_CLK_SRC_SWP_PLL1Q      = LL_RCC_FMC_CLKSOURCE_SWP_PLL1Q,     /*!< PLL1Q clock switch selected as FMC clock source      */
  HAL_RCC_FMC_CLK_SRC_SWP_PLL2R      = LL_RCC_FMC_CLKSOURCE_SWP_PLL2R,     /*!< PLL2R clock switch selected as FMC clock source      */
  HAL_RCC_FMC_CLK_SRC_SWP_HSI        = LL_RCC_FMC_CLKSOURCE_SWP_HSI,       /*!< HSI clock switch selected as FMC clock source        */
  HAL_RCC_FMC_CLK_SRC_SWP_HCLK5_DIV4 = LL_RCC_FMC_CLKSOURCE_SWP_HCLK5_DIV4 /*!< HCLK5 DIV4 clock switch selected as FMC clock source */
} hal_rcc_fmc_clk_src_switch_position_t;

/**
  * @brief XSPI kernel clock switch position
  */
typedef enum
{
  HAL_RCC_XSPI_CLK_SRC_SWP_NEUTRAL    = LL_RCC_XSPI_CLKSOURCE_SWP_NEUTRAL,   /*!< Neutral mode and clock is gated                       */
  HAL_RCC_XSPI_CLK_SRC_SWP_HCLK5      = LL_RCC_XSPI_CLKSOURCE_SWP_HCLK5,     /*!< HCLK5 clock switch selected as XSPI clock source      */
  HAL_RCC_XSPI_CLK_SRC_SWP_PLL2S      = LL_RCC_XSPI_CLKSOURCE_SWP_PLL2S,     /*!< PLL2S clock switch selected as XSPI clock source      */
  HAL_RCC_XSPI_CLK_SRC_SWP_PLL2T      = LL_RCC_XSPI_CLKSOURCE_SWP_PLL2T,     /*!< PLL2T clock switch selected as XSPI clock source      */
  HAL_RCC_XSPI_CLK_SRC_SWP_HCLK5_DIV4 = LL_RCC_XSPI_CLKSOURCE_SWP_HCLK5_DIV4 /*!< HCLK5 DIV4 clock switch selected as XSPI clock source */
} hal_rcc_xspi_clk_src_switch_position_t;

/**
  * @brief RCC PLL Spread-Spectrum Modulation configuration structure definition
  */
typedef struct
{
  uint32_t    mod_period;    /*!< MOD_PER: PLL SSCG Modulation period. This parameter is calculated
                                  based on Fref clock and frequency modulation (FMOD). The value
                                  multiplied by mod_depth_adj (INC_STEP) must be lower than (2^15-1). */

  uint32_t    mod_depth_adj; /*!< INC_STEP: PLL SSCG Modulation depth adjustment. This parameter is
                                  calculated based on DIVN, modulation depth (MD) and MOD_PER.
                                  The value multiplied by mod_period (MOD_PER) must be lower than (2^15-1). */

  hal_rcc_pll_sscg_spread_mode_t spread_mode;  /*!< DWNSPREAD: PLL SSCG Modulation spread mode, this can be one of
                                                    the values defined in hal_rcc_pll_sscg_spread_mode_t */

  hal_rcc_pll_sscg_dith_ctrl_t   dith_control;  /*!< PLL SSCG dithering noise control configuration, this can be one of
                                                    the values defined in hal_rcc_pll_sscg_dith_ctrl_t */

} hal_rcc_pll_sscg_config_t;

/**
  * @brief RCC PLL configuration structure definition.
  * @note  VCO range is being calculated automatically in PLL configurations functions.
  */
typedef struct
{
  uint16_t pll_n;       /*!< PLLN: Multiplication factor for PLL VCO output clock.
                             This parameter must be a number between Min_Data = 8 and Max_Data = 420 */

  uint16_t pll_fracn;   /*!< PLLFRACN: Specifies Fractional Part Of The Multiplication Factor for
                             PLL1 VCO It must be a value between 0 and 8191                          */

  uint8_t pll_m;        /*!< PLLM: Division factor for PLL VCO input clock.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 63  */

  uint8_t pll_p;        /*!< PLLP: Division factor for peripheral clocks.
                             This parameter must be an even number between Min_Data = 1 and Max_Data = 128
                             - For PLL1, value 3 is not allowed. */

  uint8_t pll_q;        /*!< PLLQ: Division factor for peripheral clocks.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 128  */

  uint8_t pll_s;        /*!< PLLS: Division factor for peripheral clocks.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 8    */

  uint8_t pll_r;        /*!< PLLR: Division factor for peripheral clocks.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 128  */

  uint8_t pll_t;        /*!< PLLT: Division factor for peripheral clocks.
                              This parameter must be a number between Min_Data = 1 and Max_Data = 8   */

  hal_rcc_pll_src_t pll_source; /*!< RCC_PLLSource: PLL entry clock source                            */

  hal_rcc_pll_input_range_t pll_input_range; /*!< PLLVCI: PLL Input clock (ref_ck) range frequency (pll_source / pll_m).
                                                  This parameter must be a value of @ref hal_rcc_pll_input_range_t  */

  hal_rcc_pll_vco_range_t pll_vco_range;   /*!< PLLVCO: PLL VCO clock range frequency (2 * ref_ck * pll_n).
                                                This parameter must be a value of @ref hal_rcc_pll_vco_range_t  */

  hal_rcc_pll_sscg_state_t  pll_sscg_state;  /*!< RCC_PLLSSCG: PLL spread-spectrum mode status. This can be
                                                  one of the values defined in hal_rcc_pll_sscg_state_t    */

  hal_rcc_pll_sscg_config_t pll_sscg_config;    /*!< RCC_SSCG: PLL Spread-Spectrum Modulation configuration  */

} hal_rcc_pll_config_t;

/**
  * @brief  RCC System, AXI, AHB and APB buses clock configuration structure definition
  */
typedef struct
{
  hal_rcc_sysclk_prescaler_t sysclk_prescaler; /*!< The system CPU clock prescaler.
                                                    This clock is derived from the system clock (SYSCLK). */
  hal_rcc_aclk_prescaler_t aclk_prescaler; /*!< The ACLK (AXI clock) and HCLK (AHB clock) prescaler.
                                                This clock is derived from the BMCLK (Bus matrix clock). */
  hal_rcc_pclk_prescaler_t pclk1_prescaler; /*!< The APB1 clock (PCLK1) prescaler.
                                                 This clock is derived from the HCLK (AHB clock).     */
  hal_rcc_pclk_prescaler_t pclk2_prescaler; /*!< The APB2 clock (PCLK2) prescaler.
                                                 This clock is derived from the HCLK (AHB clock).     */
  hal_rcc_pclk_prescaler_t pclk4_prescaler; /*!< The APB4 clock (PCLK4) prescaler.
                                                 This clock is derived from the HCLK (AHB clock).     */
} hal_rcc_bus_clk_config_t;

/**
  * @brief  RCC PLL Clocks structure definition
  */
typedef struct
{
  uint32_t pll_p_freq;  /*!< PLLx outputP frequency */
  uint32_t pll_q_freq;  /*!< PLLx outputQ frequency */
  uint32_t pll_s_freq;  /*!< PLLx outputS frequency */
  uint32_t pll_r_freq;  /*!< PLLx outputR frequency */
  uint32_t pll_t_freq;  /*!< PLLx outputT frequency */
} hal_rcc_pll_output_freq_t;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1 Oscillators, PLLs, bus configurations and system clock reset functions
  This section provides functions allowing to configure the internal and external oscillators
  (HSE, LSE, HSI, HSI48, CSI, LSI, PLL), CSS, MCO and the System buses clocks (SYSCLK, AHB, APB1, APB2 and APB4).

  - Internal/external clock and PLL configuration:

    - HSI (High-Speed Internal): 64 MHz factory calibrated RC used as System clock source, as PLL input and as
    peripherals kernel clock. A predivider enables the application to select an output frequency of 8, 16, 32 or 64MHz.
    HSI is trimmable by application.

    - HSI48 (48 MHz Internal): 48 MHz factory calibrated RC used as peripherals kernel clock, in particular RNG and USB.
    HSI48 is trimmable by application through CRS.

    - LSI (Low-Speed Internal): 32 kHz very low-consumption RC oscillator mainly used as IWDG and/or RTC kernel clock.
    It can be also be selected for some peripherals as kernel clock.

    - CSI (Low-Power Internal): 4 MHz factory-trimmed RC used directly or through
      the PLL as System clock source and also used for peripherals as kernel clock.

    - HSE (High-Speed External): crystal or clock, from 4 to 50 MHz, used directly or
    through the PLL as System clock source. Can be used also optionally as RTC clock source.

    - LSE (Low-Speed External): 32.768 kHz oscillator used optionally as RTC clock source.

    - PLL1 providing up to three independent output clocks:

      - as main PLL, PLL1, that is generally used to provide clocks to the CPU and to some
      peripherals

    - PLL2 providing up to five independent output clocks, and PLL3 providing up to four independent output clocks:

      - to generate the kernel clock for peripherals.

  - System, AHB and APB buses clocks configuration:

    - Several clock sources can be used to drive the System clock (SYSCLK):

    The AHB clock (HCLK) is derived from System clock through configurable
    prescaler and used to clock the CPU, memory and peripherals mapped
    on AHB bus (DMA, GPIO...). APB1 (PCLK1), APB2 (PCLK2) and APB4 (PCLK4) clocks are derived
    from AHB clock through configurable prescalers and used to clock
    the peripherals mapped on these buses.

    - All the peripheral default kernel clocks are derived from the System clock (SYSCLK) except for:

      - DACSH: kernel clock is either LSE (default) or LSI.
      - DTS: kernel clock is always the LSE clock.
      - RNG: it requires a frequency equal or lower than 48 MHz to work correctly. Kernel clock is derived
      from HSI48 (default) or from HSI divided by 2.
      - FDCAN: kernel clock is derived from HSE (default), PLL1Q or PLL1P.
      - IWDG: clock which is always the LSI clock.
      - RTC and TAMP: kernel clock is derived from the LSI, LSE or HSE clock divided by 2 to 63.
      - USB: it requires a frequency equal to 48 MHz to work correctly. Kernel clock is derived from HSI48 (default),
      HSE or PLL3Q.
      - SDMMC1: kernel clock is derived from PLL2S (default) or PLL2T.

    - For these peripherals, the kernel clock source must be activated.

    - The maximum frequency of the SYSCLK is 520MHz
    - The maximum frequency of the ACLK and HCLK is 260MHz.
    - The maximum frequency of the PCLK1, PCLK2 and PCLK4 is 137.5MHz.

    To correctly read data from Flash memory, the number of wait states (latency) must be
    correctly programmed in the FLASH register according to the
    frequency of the AXI bus clock and the internal voltage range of the device VCORE.

    The table below shows the correspondence between wait states and interface clock (AXI Bus clock).

    Table 1. ACLK clock frequency (MHz) for devices depending on FLASH latency and voltage range  (VOS).

    |   Latency         |  VOS2 1.05V-1.15V  |  VOS1 1.15V-1.26V  |  VOS0 1.30V-1.40   |
    |-------------------|--------------------|--------------------|--------------------|
    | 0WS(1 CPU cycles) |        40          |        40          |        40          |
    | 1WS(2 CPU cycles) |        80          |        80          |        80          |
    | 2WS(3 CPU cycles) |        120         |        120         |        120         |
    | 3WS(4 CPU cycles) |        150         |        160         |        160         |
    | 4WS(5 CPU cycles) |        -           |        200         |        200         |
    | 5WS(6 CPU cycles) |        -           |        217         |        240         |
    | 6WS(7 CPU cycles) |        -           |         -          |        260         |

  - Reset functions:

    - Reset the RCC clock configuration to the default values (HSI at 64MHz).
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1_0 Reset System clock to default function
  * @brief    Functions to reset the system clock to HSI (64MHz)
  * @{
  */

void         HAL_RCC_Reset(void);
hal_status_t HAL_RCC_ResetSystemClock(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_1 RCC oscillators configuration service
  * @brief    Functions to configure the different oscillators and the main PLL.
  * @note     The following functions configure and activate the different oscillators.
  *           Configuration can be done:
  *           - using the atomic functions defined for each oscillators and PLL
  *             -# like HAL_RCC_{OSC}_Enable: {OSC} is HSE/LSE/HSI/HSI48/CSI/LSI
  *           - atomic function used for main PLL is described in the @ref RCC_Exported_Functions_Group1_3
  *
  *           example: enable HSE oscillator
  *           - using atomic function (footprint optimisation):
  *             @code
  *             HAL_RCC_HSE_Enable(HAL_RCC_HSE_ON);
  *             @endcode
  * @{
  */

#if defined(HSE_VALUE)
/* HSE oscillator configuration and activation    ******************************/
hal_status_t    HAL_RCC_HSE_Enable(hal_rcc_hse_t mode);
hal_status_t    HAL_RCC_HSE_Disable(void);
hal_status_t    HAL_RCC_HSE_Enable_IT(hal_rcc_hse_t mode);
hal_rcc_osc_enable_status_t     HAL_RCC_HSE_IsEnabled(void);
hal_rcc_osc_ready_status_t      HAL_RCC_HSE_IsReady(void);
void            HAL_RCC_HSE_ReadyCallback(void);
#endif /* HSE_VALUE */

#if defined(LSE_VALUE)
/* LSE oscillator configuration and activation    ******************************/
hal_status_t    HAL_RCC_LSE_Enable(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive);
hal_status_t    HAL_RCC_LSE_Disable(void);
hal_status_t    HAL_RCC_LSE_Enable_IT(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive);
hal_rcc_osc_enable_status_t     HAL_RCC_LSE_IsEnabled(void);
hal_rcc_osc_ready_status_t      HAL_RCC_LSE_IsReady(void);
void            HAL_RCC_LSE_ReadyCallback(void);
#endif /* LSE_VALUE */

/* HSI oscillator configuration and activation    *****************************/
hal_status_t    HAL_RCC_HSI_Enable(hal_rcc_hsi_div_t divider);
hal_status_t    HAL_RCC_HSI_Disable(void);
hal_status_t    HAL_RCC_HSI_Enable_IT(hal_rcc_hsi_div_t divider);
hal_rcc_osc_enable_status_t     HAL_RCC_HSI_IsEnabled(void);
hal_rcc_osc_ready_status_t      HAL_RCC_HSI_IsReady(void);
hal_status_t    HAL_RCC_HSI_EnableInStopMode(void);
hal_status_t    HAL_RCC_HSI_DisableInStopMode(void);
hal_rcc_osc_stop_mode_status_t  HAL_RCC_HSI_IsEnabledInStopMode(void);
void            HAL_RCC_HSI_SetTrimming(uint32_t value);
uint32_t        HAL_RCC_HSI_GetTrimming(void);
uint32_t        HAL_RCC_HSI_GetCalibration(void);
void            HAL_RCC_HSI_ReadyCallback(void);

/* HSI48 oscillator configuration and activation    ***************************/
hal_status_t    HAL_RCC_HSI48_Enable(void);
hal_status_t    HAL_RCC_HSI48_Disable(void);
hal_status_t    HAL_RCC_HSI48_Enable_IT(void);
hal_rcc_osc_enable_status_t     HAL_RCC_HSI48_IsEnabled(void);
hal_rcc_osc_ready_status_t      HAL_RCC_HSI48_IsReady(void);
uint32_t        HAL_RCC_HSI48_GetCalibration(void);
void            HAL_RCC_HSI48_ReadyCallback(void);

/* CSI oscillator configuration and activation    ******************************/
hal_status_t    HAL_RCC_CSI_Enable(void);
hal_status_t    HAL_RCC_CSI_Disable(void);
hal_status_t    HAL_RCC_CSI_Enable_IT(void);
hal_rcc_osc_enable_status_t     HAL_RCC_CSI_IsEnabled(void);
hal_rcc_osc_ready_status_t      HAL_RCC_CSI_IsReady(void);
hal_status_t    HAL_RCC_CSI_EnableInStopMode(void);
hal_status_t    HAL_RCC_CSI_DisableInStopMode(void);
hal_rcc_osc_stop_mode_status_t  HAL_RCC_CSI_IsEnabledInStopMode(void);
void            HAL_RCC_CSI_SetTrimming(uint32_t value);
uint32_t        HAL_RCC_CSI_GetTrimming(void);
uint32_t        HAL_RCC_CSI_GetCalibration(void);
void            HAL_RCC_CSI_ReadyCallback(void);

/* LSI oscillator configuration and activation    ******************************/
hal_status_t    HAL_RCC_LSI_Enable(void);
hal_status_t    HAL_RCC_LSI_Disable(void);
hal_status_t    HAL_RCC_LSI_Enable_IT(void);
hal_rcc_osc_enable_status_t     HAL_RCC_LSI_IsEnabled(void);
hal_rcc_osc_ready_status_t      HAL_RCC_LSI_IsReady(void);
void            HAL_RCC_LSI_ReadyCallback(void);

/* RCC general interrupt request handler    ***********************************/
void            HAL_RCC_IRQHandler(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_2 RCC clock configuration service
  * @brief    Functions to configure the bus prescalers and retrieve bus clock frequencies (SYSCLK, HCLK and PCLKx).
  * @note     Unitary functions can be used to configure independently each bus.
  *
  *           example: all the BUS prescalers are set
  *
  *           - Call the global @ref HAL_RCC_SetBusClockConfig
  *             @code
  *               LL_FLASH_SetLatency(LL_FLASH_LATENCY_4WS);
  *               HAL_RCC_SetSYSCLKSource(HAL_RCC_SYSCLKSOURCE_PLLCLK);
  *               hal_rcc_bus_clk_config_t config_bus;
  *               config_bus.sysclk_prescaler = HAL_RCC_SYSCLK_PRESCALER1;
  *               config_bus.aclk_prescaler = HAL_RCC_ACLK_PRESCALER1;
  *               config_bus.pclk1_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               config_bus.pclk2_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               config_bus.pclk4_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               HAL_RCC_SetBusClockConfig(&config_bus);
  *             @endcode
  * @{
  */
hal_status_t          HAL_RCC_SetSYSCLKSource(hal_rcc_sysclk_src_t source);
hal_rcc_sysclk_src_t  HAL_RCC_GetSYSCLKSource(void);
void                  HAL_RCC_SetSysClkPrescaler(hal_rcc_sysclk_prescaler_t prescaler);
void                  HAL_RCC_SetACLKPrescaler(hal_rcc_aclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK1Prescaler(hal_rcc_pclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK2Prescaler(hal_rcc_pclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK4Prescaler(hal_rcc_pclk_prescaler_t prescaler);
hal_rcc_sysclk_prescaler_t  HAL_RCC_GetSysClkPrescaler(void);
hal_rcc_aclk_prescaler_t    HAL_RCC_GetACLKPrescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK1Prescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK2Prescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK4Prescaler(void);

hal_status_t          HAL_RCC_SetBusClockConfig(const hal_rcc_bus_clk_config_t *p_config);
void                  HAL_RCC_GetBusClockConfig(hal_rcc_bus_clk_config_t *p_config);
uint32_t              HAL_RCC_GetSYSCLKFreq(void);
uint32_t              HAL_RCC_GetHCLKFreq(void);
uint32_t              HAL_RCC_GetPCLK1Freq(void);
uint32_t              HAL_RCC_GetPCLK2Freq(void);
uint32_t              HAL_RCC_GetPCLK4Freq(void);
uint32_t              HAL_RCC_GetSysTickExternalClkFreq(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_3 RCC management of PLL1
  * @brief    Functions to configure the different PLL1
  * @details  PLL1 (main PLL) might be used for system clock.
  *           PLL1 is configured and enabled respectively with HAL_RCC_PLL1_SetConfig() and HAL_RCC_PLL1_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL1.
  *
  *           example1: activation main PLL
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_HSI_Enable(HAL_RCC_HSI_DIV1);
  *               HAL_RCC_HSI_SetTrimming(HAL_RCC_HSICALIBRATION_DEFAULT);
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_HSI;
  *               config_pll.pll_m = 4;
  *               config_pll.pll_n = 75;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2
  *               config_pll.pll_s = 2
  *               config_pll.pll_t = 2
  *               HAL_RCC_PLL1_SetConfig(&config_pll);
  *               HAL_RCC_PLL1_Enable();
  *               HAL_RCC_PLL1_EnableOutput(HAL_RCC_PLL1_SYSCLK);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL1_SetConfig(const hal_rcc_pll_config_t *p_config);
void                  HAL_RCC_PLL1_GetConfig(hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL1_Enable(void);
hal_status_t          HAL_RCC_PLL1_Enable_IT(void);
hal_status_t          HAL_RCC_PLL1_Disable(void);
hal_rcc_pll_status_t  HAL_RCC_PLL1_IsReady(void);
hal_status_t          HAL_RCC_PLL1_SetFRACN(uint16_t fracn);
uint16_t              HAL_RCC_PLL1_GetFRACN(void);
hal_status_t          HAL_RCC_PLL1_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL1_DisableOutput(uint32_t output);
uint32_t              HAL_RCC_PLL1_GetOutput(void);
hal_status_t          HAL_RCC_PLL1_Reset(void);
void                  HAL_RCC_PLL1_ReadyCallback(void);
void                  HAL_RCC_PLL1_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_4 RCC management of PLL2
  * @brief    Functions to configure the different PLL2
  * @details  PLL2 is configured and enabled respectively with HAL_RCC_PLL2_SetConfig() and HAL_RCC_PLL2_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL2.
  *
  *           example1: activation PLL2 only
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_HSI_Enable(HAL_RCC_HSI_DIV1);
  *               HAL_RCC_HSI_SetTrimming(HAL_RCC_HSICALIBRATION_DEFAULT);
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_HSI;
  *               config_pll.pll_m = 4;
  *               config_pll.pll_n = 75;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2
  *               config_pll.pll_s = 2
  *               config_pll.pll_t = 2
  *               HAL_RCC_PLL2_SetConfig(&config_pll);
  *               HAL_RCC_PLL2_Enable();
  *               HAL_RCC_PLL2_EnableOutput(HAL_RCC_PLL2_OUTPUT_P);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL2_SetConfig(const hal_rcc_pll_config_t *p_config);
void                  HAL_RCC_PLL2_GetConfig(hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL2_Enable(void);
hal_status_t          HAL_RCC_PLL2_Enable_IT(void);
hal_status_t          HAL_RCC_PLL2_Disable(void);
hal_rcc_pll_status_t  HAL_RCC_PLL2_IsReady(void);
hal_status_t          HAL_RCC_PLL2_SetFRACN(uint16_t fracn);
uint16_t              HAL_RCC_PLL2_GetFRACN(void);
hal_status_t          HAL_RCC_PLL2_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL2_DisableOutput(uint32_t output);
uint32_t              HAL_RCC_PLL2_GetOutput(void);
hal_status_t          HAL_RCC_PLL2_Reset(void);
void                  HAL_RCC_PLL2_ReadyCallback(void);
void                  HAL_RCC_PLL2_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_5 RCC management of PLL3
  * @brief    Functions to configure the different PLL3
  * @details  PLL3 is configured and enabled respectively with HAL_RCC_PLL3_SetConfig() and HAL_RCC_PLL3_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL3.
  *
  *           example1: activation PLL3 only
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_HSI_Enable(HAL_RCC_HSI_DIV1);
  *               HAL_RCC_HSI_SetTrimming(HAL_RCC_HSICALIBRATION_DEFAULT);
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_HSI;
  *               config_pll.pll_m = 4;
  *               config_pll.pll_n = 75;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2
  *               config_pll.pll_s = 2
  *               config_pll.pll_t = 2
  *               HAL_RCC_PLL3_SetConfig(&config_pll);
  *               HAL_RCC_PLL3_Enable();
  *               HAL_RCC_PLL3_EnableOutput(HAL_RCC_PLL3_OUTPUT_P);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL3_SetConfig(const hal_rcc_pll_config_t *p_config);
void                  HAL_RCC_PLL3_GetConfig(hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL3_Enable(void);
hal_status_t          HAL_RCC_PLL3_Disable(void);
hal_status_t          HAL_RCC_PLL3_Enable_IT(void);
hal_rcc_pll_status_t  HAL_RCC_PLL3_IsReady(void);
hal_status_t          HAL_RCC_PLL3_SetFRACN(uint16_t fracn);
uint16_t              HAL_RCC_PLL3_GetFRACN(void);
hal_status_t          HAL_RCC_PLL3_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL3_DisableOutput(uint32_t output);
uint32_t              HAL_RCC_PLL3_GetOutput(void);
hal_status_t          HAL_RCC_PLL3_Reset(void);
void                  HAL_RCC_PLL3_ReadyCallback(void);
void                  HAL_RCC_PLL3_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group2 Peripheral Clock management on buses
  This subsection provides a set of functions (on AHB1, AHB2, AHB3, AHB4, AHB5, APB1, APB2, APB4 buses)
  allowing to:

  - Enable or disable the peripherals clock.
  - Reset of peripherals clock.
  - Enable or disable the peripherals clock in low power mode.
  * @{
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Disable AHB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the HSP1 clock.
  */
__STATIC_INLINE void HAL_RCC_HSP1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_HSP1);
}

/**
  * @details This function enables the GPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the USB OTG FS clock.
  */
__STATIC_INLINE void HAL_RCC_USBOTGFS_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function enables the ADF1 clock.
  */
__STATIC_INLINE void HAL_RCC_ADF1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @details This function disables the HSP1 clock.
  */
__STATIC_INLINE void HAL_RCC_HSP1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_HSP1);
}

/**
  * @details This function disables the GPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function disables the USB OTG FS clock.
  */
__STATIC_INLINE void HAL_RCC_USBOTGFS_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function disables the ADF1 clock.
  */
__STATIC_INLINE void HAL_RCC_ADF1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Enable_Disable AHB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the CORDIC clock.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function enables the FMAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_FMAC1_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function enables the AHBSRAM1 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM1_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function enables the AHBSRAM2 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM2_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function enables the AHBSRAM3 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM3_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @details This function disables the CORDIC clock.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function disables the FMAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_FMAC1_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function disables the AHBSRAM1 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM1_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function disables the AHBSRAM2 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM2_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function disables the AHBSRAM3 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM3_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @}
  */

/** @defgroup RCC_AHB3_Peripheral_Clock_Enable_Disable AHB3 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB3 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the RNG clock.
  */
__STATIC_INLINE void HAL_RCC_RNG_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function enables the HASH clock.
  */
__STATIC_INLINE void HAL_RCC_HASH_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function enables the ADC12 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC12_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function enables the ADC34 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC34_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function enables the DAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC1_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the DAC2 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC2_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function enables the DAC3 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC3_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function enables the DAC4 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC4_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @details This function disables the RNG clock.
  */
__STATIC_INLINE void HAL_RCC_RNG_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function disables the HASH clock.
  */
__STATIC_INLINE void HAL_RCC_HASH_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function disables the ADC12 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC12_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function disables the ADC34 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC34_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function disables the DAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC1_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the DAC2 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC2_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function disables the DAC3 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC3_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function disables the DAC4 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC4_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @}
  */

/** @defgroup RCC_AHB4_Peripheral_Clock_Enable_Disable AHB4 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB4 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the GPIOA clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function enables the GPIOB clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function enables the GPIOC clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function enables the GPIOD clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function enables the GPIOE clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function enables the GPIOF clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function enables the GPIOG clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function enables the GPIOH clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function enables the GPIOI clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function enables the CRC clock.
  */
__STATIC_INLINE void HAL_RCC_CRC_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function enables the BKPRAM clock.
  */
__STATIC_INLINE void HAL_RCC_BKPRAM_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @details This function disables the GPIOA clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function disables the GPIOB clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function disables the GPIOC clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function disables the GPIOD clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function disables the GPIOE clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function disables the GPIOF clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function disables the GPIOG clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function disables the GPIOH clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function disables the GPIOI clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function disables the CRC clock.
  */
__STATIC_INLINE void HAL_RCC_CRC_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function disables the BKPRAM clock.
  */
__STATIC_INLINE void HAL_RCC_BKPRAM_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @}
  */

/** @defgroup RCC_AHB5_Peripheral_Clock_Enable_Disable AHB5 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB5 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the HPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_EnableClock(void)
{
  LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function enables the FMC clock.
  */
__STATIC_INLINE void HAL_RCC_FMC_EnableClock(void)
{
  LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function enables the XSPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_EnableClock(void)
{
  LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function enables the SDMMC1 clock.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_EnableClock(void)
{
  LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

#if defined (NPU_PRESENT)
/**
  * @details This function enables the NPU clock.
  */
__STATIC_INLINE void HAL_RCC_NPU_EnableClock(void)
{
  LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_NPU);
}
#endif /* NPU_PRESENT */

/**
  * @details This function disables the HPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_DisableClock(void)
{
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function disables the FMC clock.
  */
__STATIC_INLINE void HAL_RCC_FMC_DisableClock(void)
{
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function disables the XSPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_DisableClock(void)
{
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function disables the SDMMC1 clock.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_DisableClock(void)
{
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

#if defined (NPU_PRESENT)
/**
  * @details This function disables the NPU clock.
  */
__STATIC_INLINE void HAL_RCC_NPU_DisableClock(void)
{
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_NPU);
}
#endif /* NPU_PRESENT */

/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the TIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function enables the TIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function enables the TIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM4_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function enables the TIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM5_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function enables the TIM6 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM6_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function enables the TIM7 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM7_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function enables the TIM12 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM12_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function enables the TIM13 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM13_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function enables the TIM14 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM14_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function enables the LPTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function enables the WWDG clock.
  */
__STATIC_INLINE void HAL_RCC_WWDG_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function enables the TIM10 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM10_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function enables the TIM11 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM11_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function enables the SPI2 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function enables the SPI3 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function enables the USART2 clock.
  */
__STATIC_INLINE void HAL_RCC_USART2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function enables the USART3 clock.
  */
__STATIC_INLINE void HAL_RCC_USART3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function enables the UART4 clock.
  */
__STATIC_INLINE void HAL_RCC_UART4_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function enables the UART5 clock.
  */
__STATIC_INLINE void HAL_RCC_UART5_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function enables the I2C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C1_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function enables the I2C2 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function enables the I2C3 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function enables the I3C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I3C1_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function enables the UART7 clock.
  */
__STATIC_INLINE void HAL_RCC_UART7_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function enables the UART8 clock.
  */
__STATIC_INLINE void HAL_RCC_UART8_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @details This function disables the TIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function disables the TIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function disables the TIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM4_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function disables the TIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM5_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function disables the TIM6 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM6_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function disables the TIM7 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM7_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function disables the TIM12 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM12_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function disables the TIM13 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM13_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function disables the TIM14 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM14_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function disables the LPTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function disables the WWDG clock.
  */
__STATIC_INLINE void HAL_RCC_WWDG_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function disables the TIM10 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM10_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function disables the TIM11 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM11_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function disables the SPI2 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function disables the SPI3 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function disables the USART2 clock.
  */
__STATIC_INLINE void HAL_RCC_USART2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function disables the USART3 clock.
  */
__STATIC_INLINE void HAL_RCC_USART3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function disables the UART4 clock.
  */
__STATIC_INLINE void HAL_RCC_UART4_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function disables the UART5 clock.
  */
__STATIC_INLINE void HAL_RCC_UART5_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function disables the I2C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C1_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function disables the I2C2 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function disables the I2C3 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function disables the I3C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I3C1_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function disables the UART7 clock.
  */
__STATIC_INLINE void HAL_RCC_UART7_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function disables the UART8 clock.
  */
__STATIC_INLINE void HAL_RCC_UART8_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the CRS clock.
  */
__STATIC_INLINE void HAL_RCC_CRS_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function enables the FDCAN clock.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function enables the UCPD1 clock.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @details This function disables the CRS clock.
  */
__STATIC_INLINE void HAL_RCC_CRS_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function disables the FDCAN clock.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function disables the UCPD1 clock.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Enable_Disable APB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the TIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function enables the TIM8 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM8_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function enables the TIM20 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM20_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function enables the USART1 clock.
  */
__STATIC_INLINE void HAL_RCC_USART1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function enables the USART6 clock.
  */
__STATIC_INLINE void HAL_RCC_USART6_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function enables the UART9 clock.
  */
__STATIC_INLINE void HAL_RCC_UART9_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function enables the USART10 clock.
  */
__STATIC_INLINE void HAL_RCC_USART10_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function enables the SPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function enables the SPI4 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI4_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function enables the TIM15 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM15_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function enables the TIM16 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM16_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function enables the TIM17 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM17_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function enables the TIM9 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM9_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function enables the SPI5 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI5_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function enables the HRTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function enables the HRTIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_HRTIM2_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @details This function disables the TIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function disables the TIM8 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM8_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function disables the TIM20 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM20_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function disables the USART1 clock.
  */
__STATIC_INLINE void HAL_RCC_USART1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function disables the USART6 clock.
  */
__STATIC_INLINE void HAL_RCC_USART6_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function disables the UART9 clock.
  */
__STATIC_INLINE void HAL_RCC_UART9_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function disables the USART10 clock.
  */
__STATIC_INLINE void HAL_RCC_USART10_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function disables the SPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function disables the SPI4 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI4_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function disables the TIM15 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM15_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function disables the TIM16 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM16_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function disables the TIM17 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM17_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function disables the TIM9 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM9_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function disables the SPI5 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI5_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function disables the HRTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function disables the HRTIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_HRTIM2_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @}
  */

/** @defgroup RCC_APB4_Peripheral_Clock_Enable_Disable APB4 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB4 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the SBS clock.
  */
__STATIC_INLINE void HAL_RCC_SBS_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function enables the LPUART1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function enables the SPI6 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI6_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function enables the LPTIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function enables the LPTIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function enables the LPTIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function enables the LPTIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM5_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function enables the VREFBUF clock.
  */
__STATIC_INLINE void HAL_RCC_VREFBUF_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function enables the RTCAPB clock.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function enables the DTS clock.
  */
__STATIC_INLINE void HAL_RCC_DTS_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function enables the COMP12 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP12_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function enables the COMP34 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP34_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function enables the COMP56 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP56_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function enables the COMP78 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP78_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @details This function disables the SBS clock.
  */
__STATIC_INLINE void HAL_RCC_SBS_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function disables the LPUART1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function disables the SPI6 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI6_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function disables the LPTIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function disables the LPTIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function disables the LPTIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function disables the LPTIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM5_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function disables the VREFBUF clock.
  */
__STATIC_INLINE void HAL_RCC_VREFBUF_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function disables the RTCAPB clock.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the DTS clock.
  */
__STATIC_INLINE void HAL_RCC_DTS_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function disables the COMP12 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP12_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function disables the COMP34 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP34_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function disables the COMP56 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP56_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function disables the COMP78 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP78_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Status AHB1 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the HSP1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HSP1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HSP1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HSP1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_HSP1);
}

/**
  * @details This function checks if the GPDMA1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPDMA1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPDMA1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPDMA1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function checks if the OTGFS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OTGFS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USB OTG FS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USBOTGFS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function checks if the ADF1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADF1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADF1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADF1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Enable_Status AHB2 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the CORDIC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CORDIC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CORDIC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CORDIC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function checks if the FMAC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FMAC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FMAC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FMAC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function checks if the AHBSRAM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED AHBSRAM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  AHBSRAM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AHBSRAM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function checks if the AHBSRAM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED AHBSRAM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  AHBSRAM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AHBSRAM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function checks if the AHBSRAM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED AHBSRAM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  AHBSRAM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AHBSRAM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @}
  */

/** @defgroup RCC_AHB3_Peripheral_Clock_Enable_Status AHB3 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB3 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the RNG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED RNG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  RNG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_RNG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function checks if the HASH clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HASH clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HASH clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HASH_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function checks if the ADC12 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADC12 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADC12 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADC12_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function checks if the ADC34 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADC34 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADC34 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADC34_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function checks if the DAC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function checks if the DAC2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function checks if the DAC3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function checks if the DAC4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @}
  */

/** @defgroup RCC_AHB4_Peripheral_Clock_Enable_Status AHB4 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB4 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the GPIOA clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOA clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOA clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOA_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function checks if the GPIOB clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOB clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOB clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOB_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function checks if the GPIOC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function checks if the GPIOD clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOD clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOD clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOD_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function checks if the GPIOE clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOE clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOE clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOE_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function checks if the GPIOF clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOF clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOF clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOF_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function checks if the GPIOG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function checks if the GPIOH clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOH clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOH clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOH_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function checks if the GPIOI clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOI clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOI clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOI_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function checks if the CRC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CRC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CRC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CRC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function checks if the BKPRAM clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED BKPRAM clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  BKPRAM clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_BKPRAM_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @}
  */

/** @defgroup RCC_AHB5_Peripheral_Clock_Enable_Status AHB5 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB5 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the HPDMA1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HPDMA1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HPDMA1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HPDMA1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB5_GRP1_IsEnabledClock(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function checks if the FMC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FMC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FMC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FMC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB5_GRP1_IsEnabledClock(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function checks if the XSPI1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED XSPI1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  XSPI1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_XSPI1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB5_GRP1_IsEnabledClock(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function checks if the SDMMC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SDMMC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SDMMC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SDMMC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB5_GRP1_IsEnabledClock(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

#if defined (NPU_PRESENT)
/**
  * @details This function checks if the NPU clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED NPU clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  NPU clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_NPU_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB5_GRP1_IsEnabledClock(LL_AHB5_GRP1_PERIPH_NPU);
}
#endif /* NPU_PRESENT */

/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Status APB1 Peripheral Clock Enabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the TIM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function checks if the TIM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function checks if the TIM4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function checks if the TIM5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function checks if the TIM6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function checks if the TIM7 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM7 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM7 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM7_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function checks if the TIM12 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM12 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM12 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM12_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function checks if the TIM13 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM13 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM13 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM13_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function checks if the TIM14 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM14 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM14 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM14_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function checks if the LPTIM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function checks if the WWDG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED WWDG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  WWDG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_WWDG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function checks if the TIM10 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM10 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM10 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM10_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function checks if the TIM11 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM11 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM11 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM11_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function checks if the SPI2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function checks if the SPI3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function checks if the USART2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function checks if the USART3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function checks if the UART4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function checks if the UART5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function checks if the I2C1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function checks if the I2C2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function checks if the I2C3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function checks if the I3C1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I3C1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I3C1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I3C1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function checks if the UART7 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART7 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART7 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART7_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function checks if the UART8 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART8 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART8 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART8_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Status APB1 Peripheral Clock Enabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the CRS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CRS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CRS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CRS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function checks if the FDCAN clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FDCAN clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FDCAN clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FDCAN_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function checks if the UCPD1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UCPD1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UCPD1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UCPD1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Enable_Status APB2 Peripheral Clock Enabled Status
  * @brief  Check whether the APB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the TIM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function checks if the TIM8 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM8 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM8 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM8_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function checks if the TIM20 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM20 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM20 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM20_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function checks if the USART1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function checks if the USART6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function checks if the UART9 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART9 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART9 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART9_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function checks if the USART10 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART10 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART10 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART10_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function checks if the SPI1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function checks if the SPI4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function checks if the TIM15 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM15 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM15 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM15_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function checks if the TIM16 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM16 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM16 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM16_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function checks if the TIM17 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM17 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM17 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM17_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function checks if the TIM9 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM9 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM9 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM9_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function checks if the SPI5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function checks if the HRTIM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HRTIM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HRTIM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HRTIM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function checks if the HRTIM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HRTIM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HRTIM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HRTIM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @}
  */

/** @defgroup RCC_APB4_Peripheral_Clock_Enable_Status APB4 Peripheral Clock Enabled Status
  * @brief  Check whether the APB4 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the SBS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SBS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SBS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SBS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function checks if the LPUART1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPUART1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPUART1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPUART1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function checks if the SPI6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function checks if the LPTIM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function checks if the LPTIM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function checks if the LPTIM4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function checks if the LPTIM5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function checks if the VREFBUF clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED VREFBUF clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  VREFBUF clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_VREFBUF_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function checks if the RTCAPB clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED RTCAPB clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  RTCAPB clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_RTCAPB_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function checks if the DTS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DTS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DTS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DTS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function checks if the COMP12 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP12 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP12 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP12_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function checks if the COMP34 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP34 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP34 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP34_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function checks if the COMP56 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP56 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP56 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP56_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function checks if the COMP78 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP78 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP78 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP78_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @}
  */

/** @defgroup RCC_AHB1_Reset AHB1 PeripheralReset
  * @brief  AHB1 peripheral reset.
  * @{
  */

/**
  * @details This function resets the HSP1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_HSP1_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_HSP1);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_HSP1);
}

/**
  * @details This function resets the GPDMA1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPDMA1);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function resets the USB OTG FS peripheral.
  */
__STATIC_INLINE void HAL_RCC_USBOTGFS_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_OTGFS);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function resets the ADF1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADF1_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_ADF1);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @}
  */

/** @defgroup RCC_AHB2_Reset AHB2 PeripheralReset
  * @brief  AHB2 peripheral reset.
  * @{
  */

/**
  * @details This function resets the CORDIC peripheral.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_CORDIC);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function resets the FMAC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_FMAC1_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_FMAC1);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @}
  */

/** @defgroup RCC_AHB3_Reset AHB3 PeripheralReset
  * @brief  AHB3 peripheral reset.
  * @{
  */

/**
  * @details This function resets the RNG peripheral.
  */
__STATIC_INLINE void HAL_RCC_RNG_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_RNG);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function resets the HASH peripheral.
  */
__STATIC_INLINE void HAL_RCC_HASH_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_HASH);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function resets the ADC12 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADC12_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_ADC12);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function resets the ADC34 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADC34_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_ADC34);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function resets the DAC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC1_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_DAC1);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function resets the DAC2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC2_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_DAC2);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function resets the DAC3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC3_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_DAC3);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function resets the DAC4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC4_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_DAC4);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @}
  */

/** @defgroup RCC_AHB4_Reset AHB4 PeripheralReset
  * @brief  AHB4 peripheral reset.
  * @{
  */

/**
  * @details This function resets the GPIOA peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOA);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function resets the GPIOB peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOB);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function resets the GPIOC peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOC);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function resets the GPIOD peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOD);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function resets the GPIOE peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOE);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function resets the GPIOF peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOF);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function resets the GPIOG peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOG);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function resets the GPIOH peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOH);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function resets the GPIOI peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOI);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function resets the CRC peripheral.
  */
__STATIC_INLINE void HAL_RCC_CRC_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_CRC);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @}
  */

/** @defgroup RCC_AHB5_Reset AHB5 PeripheralReset
  * @brief  AHB5 peripheral reset.
  * @{
  */

/**
  * @details This function resets the HPDMA1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_Reset(void)
{
  LL_AHB5_GRP1_ForceReset(LL_AHB5_GRP1_PERIPH_HPDMA1);
  LL_AHB5_GRP1_ReleaseReset(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function resets the FMC peripheral.
  */
__STATIC_INLINE void HAL_RCC_FMC_Reset(void)
{
  LL_AHB5_GRP1_ForceReset(LL_AHB5_GRP1_PERIPH_FMC);
  LL_AHB5_GRP1_ReleaseReset(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function resets the XSPI1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_Reset(void)
{
  LL_AHB5_GRP1_ForceReset(LL_AHB5_GRP1_PERIPH_XSPI1);
  LL_AHB5_GRP1_ReleaseReset(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function resets the SDMMC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_Reset(void)
{
  LL_AHB5_GRP1_ForceReset(LL_AHB5_GRP1_PERIPH_SDMMC1);
  LL_AHB5_GRP1_ReleaseReset(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

#if defined (NPU_PRESENT)
/**
  * @details This function resets the NPU peripheral.
  */
__STATIC_INLINE void HAL_RCC_NPU_Reset(void)
{
  LL_AHB5_GRP1_ForceReset(LL_AHB5_GRP1_PERIPH_NPU);
  LL_AHB5_GRP1_ReleaseReset(LL_AHB5_GRP1_PERIPH_NPU);
}
#endif /* NPU_PRESENT */

/**
  * @}
  */

/** @defgroup RCC_APB1_Reset APB1 PeripheralReset
  * @brief  APB1 peripheral reset.
  * @{
  */

/**
  * @details This function resets the TIM2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function resets the TIM3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function resets the TIM4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM4_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM4);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function resets the TIM5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM5_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM5);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function resets the TIM6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM6_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM6);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function resets the TIM7 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM7_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM7);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function resets the TIM12 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM12_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM12);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function resets the TIM13 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM13_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM13);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function resets the TIM14 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM14_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM14);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function resets the LPTIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_LPTIM1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function resets the TIM10 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM10_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM10);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function resets the TIM11 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM11_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM11);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function resets the SPI2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function resets the SPI3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function resets the USART2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function resets the USART3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function resets the UART4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART4_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART4);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function resets the UART5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART5_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART5);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function resets the I2C1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C1_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function resets the I2C2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function resets the I2C3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function resets the I3C1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I3C1_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I3C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function resets the UART7 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART7_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART7);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function resets the UART8 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART8_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART8);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @}
  */

/** @defgroup RCC_APB1_Reset APB1 PeripheralReset
  * @brief  APB1 peripheral reset.
  * @{
  */

/**
  * @details This function resets the CRS peripheral.
  */
__STATIC_INLINE void HAL_RCC_CRS_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_CRS);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function resets the FDCAN peripheral.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_FDCAN);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function resets the UCPD1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_UCPD1);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @}
  */

/** @defgroup RCC_APB2_Reset APB2 PeripheralReset
  * @brief  APB2 peripheral reset.
  * @{
  */

/**
  * @details This function resets the TIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function resets the TIM8 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM8_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM8);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function resets the TIM20 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM20_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM20);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function resets the USART1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function resets the USART6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART6_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART6);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function resets the UART9 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART9_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_UART9);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function resets the USART10 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART10_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART10);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function resets the SPI1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function resets the SPI4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI4_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI4);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function resets the TIM15 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM15_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM15);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function resets the TIM16 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM16_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM16);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function resets the TIM17 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM17_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM17);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function resets the TIM9 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM9_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM9);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function resets the SPI5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI5_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI5);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function resets the HRTIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_HRTIM1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function resets the HRTIM2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_HRTIM2_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_HRTIM2);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @}
  */

/** @defgroup RCC_APB4_Reset APB4 PeripheralReset
  * @brief  APB4 peripheral reset.
  * @{
  */

/**
  * @details This function resets the SBS peripheral.
  */
__STATIC_INLINE void HAL_RCC_SBS_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_SBS);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function resets the LPUART1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPUART1);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function resets the SPI6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI6_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_SPI6);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function resets the LPTIM2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPTIM2);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function resets the LPTIM3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPTIM3);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function resets the LPTIM4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPTIM4);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function resets the LPTIM5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM5_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPTIM5);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function resets the VREFBUF peripheral.
  */
__STATIC_INLINE void HAL_RCC_VREFBUF_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_VREFBUF);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function resets the DTS peripheral.
  */
__STATIC_INLINE void HAL_RCC_DTS_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_DTS);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function resets the COMP12 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP12_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_COMP12);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function resets the COMP34 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP34_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_COMP34);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function resets the COMP56 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP56_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_COMP56);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function resets the COMP78 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP78_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_COMP78);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Sleep_Enable_Disable AHB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the HSP1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HSP1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_HSP1);
}

/**
  * @details This function enables the HSP1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HSP1_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_HSP1);
}

/**
  * @details This function enables the GPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the GPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA1_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the OTGFS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OTGFS_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function enables the OTGFS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OTGFS_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function enables the ADF1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADF1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @details This function enables the ADF1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADF1_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @details This function disables the HSP1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HSP1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_HSP1);
}

/**
  * @details This function disables the HSP1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HSP1_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_HSP1);
}

/**
  * @details This function disables the GPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function disables the GPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA1_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function disables the OTGFS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OTGFS_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function disables the OTGFS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OTGFS_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function disables the ADF1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADF1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @details This function disables the ADF1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADF1_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Sleep_Enable_Disable AHB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the CORDIC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CORDIC_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function enables the CORDIC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CORDIC_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function enables the FMAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMAC1_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function enables the FMAC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMAC1_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function enables the AHBSRAM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM1_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function enables the AHBSRAM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM1_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function enables the AHBSRAM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM2_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function enables the AHBSRAM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM2_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function enables the AHBSRAM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM3_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @details This function enables the AHBSRAM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM3_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @details This function disables the CORDIC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CORDIC_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function disables the CORDIC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CORDIC_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function disables the FMAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMAC1_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function disables the FMAC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMAC1_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function disables the AHBSRAM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM1_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function disables the AHBSRAM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM1_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function disables the AHBSRAM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM2_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function disables the AHBSRAM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM2_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function disables the AHBSRAM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM3_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @details This function disables the AHBSRAM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AHBSRAM3_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @}
  */

/** @defgroup RCC_AHB3_Peripheral_Clock_Sleep_Enable_Disable AHB3 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB3 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the RNG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RNG_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function enables the RNG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RNG_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function enables the HASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HASH_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function enables the HASH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HASH_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function enables the ADC12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC12_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function enables the ADC12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC12_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function enables the ADC34 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC34_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function enables the ADC34 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC34_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function enables the DAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the DAC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the DAC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC2_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function enables the DAC2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC2_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function enables the DAC3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC3_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function enables the DAC3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC3_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function enables the DAC4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC4_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @details This function enables the DAC4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC4_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @details This function disables the RNG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RNG_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function disables the RNG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RNG_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function disables the HASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HASH_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function disables the HASH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HASH_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function disables the ADC12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC12_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function disables the ADC12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC12_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function disables the ADC34 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC34_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function disables the ADC34 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC34_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function disables the DAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the DAC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the DAC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC2_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function disables the DAC2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC2_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function disables the DAC3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC3_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function disables the DAC3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC3_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function disables the DAC4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC4_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @details This function disables the DAC4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC4_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @}
  */

/** @defgroup RCC_AHB4_Peripheral_Clock_Sleep_Enable_Disable AHB4 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB4 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the GPIOA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOA_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function enables the GPIOA clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOA_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function enables the GPIOB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOB_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function enables the GPIOB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOB_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function enables the GPIOC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOC_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function enables the GPIOC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOC_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function enables the GPIOD clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOD_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function enables the GPIOD clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOD_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function enables the GPIOE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOE_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function enables the GPIOE clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOE_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function enables the GPIOF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOF_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function enables the GPIOF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOF_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function enables the GPIOG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOG_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function enables the GPIOG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOG_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function enables the GPIOH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOH_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function enables the GPIOH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOH_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function enables the GPIOI clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOI_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function enables the GPIOI clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOI_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function enables the CRC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRC_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function enables the CRC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRC_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function enables the BKPRAM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_BKPRAM_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @details This function enables the BKPRAM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_BKPRAM_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @details This function disables the GPIOA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOA_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function disables the GPIOA clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOA_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function disables the GPIOB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOB_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function disables the GPIOB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOB_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function disables the GPIOC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOC_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function disables the GPIOC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOC_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function disables the GPIOD clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOD_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function disables the GPIOD clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOD_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function disables the GPIOE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOE_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function disables the GPIOE clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOE_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function disables the GPIOF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOF_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function disables the GPIOF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOF_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function disables the GPIOG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOG_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function disables the GPIOG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOG_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function disables the GPIOH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOH_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function disables the GPIOH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOH_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function disables the GPIOI clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOI_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function disables the GPIOI clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOI_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function disables the CRC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRC_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function disables the CRC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRC_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function disables the BKPRAM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_BKPRAM_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @details This function disables the BKPRAM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_BKPRAM_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @}
  */

/** @defgroup RCC_AHB5_Peripheral_Clock_Sleep_Enable_Disable AHB5 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB5 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the HPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HPDMA1_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function enables the HPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HPDMA1_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function enables the FLASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FLASH_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_FLASH);
}

/**
  * @details This function enables the FLASH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FLASH_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_FLASH);
}

/**
  * @details This function enables the FMC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMC_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function enables the FMC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMC_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function enables the XSPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_XSPI1_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function enables the XSPI1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_XSPI1_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function enables the SDMMC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SDMMC1_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function enables the SDMMC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SDMMC1_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function enables the AXISRAM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AXISRAM_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_AXISRAM);
}

/**
  * @details This function enables the AXISRAM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AXISRAM_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_AXISRAM);
}

/**
  * @details This function enables the DTCM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTCM1_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM1);
}

/**
  * @details This function enables the DTCM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTCM1_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM1);
}

/**
  * @details This function enables the DTCM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTCM2_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM2);
}

/**
  * @details This function enables the DTCM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTCM2_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM2);
}

/**
  * @details This function enables the ITCM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ITCM_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_ITCM);
}

/**
  * @details This function enables the ITCM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ITCM_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_ITCM);
}

#if defined (NPU_PRESENT)
/**
  * @details This function enables the NPU clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_NPU_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_NPU);
}

/**
  * @details This function enables the NPU clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_NPU_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_NPU);
}
#endif /* NPU_PRESENT */

/**
  * @details This function disables the HPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HPDMA1_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function disables the HPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HPDMA1_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function disables the FLASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FLASH_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_FLASH);
}

/**
  * @details This function disables the FLASH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FLASH_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_FLASH);
}

/**
  * @details This function disables the FMC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMC_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function disables the FMC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMC_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function disables the XSPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_XSPI1_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function disables the XSPI1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_XSPI1_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function disables the SDMMC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SDMMC1_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function disables the SDMMC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SDMMC1_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function disables the AXISRAM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AXISRAM_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_AXISRAM);
}

/**
  * @details This function disables the AXISRAM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AXISRAM_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_AXISRAM);
}

/**
  * @details This function disables the DTCM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTCM1_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM1);
}

/**
  * @details This function disables the DTCM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTCM1_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM1);
}

/**
  * @details This function disables the DTCM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTCM2_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM2);
}

/**
  * @details This function disables the DTCM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTCM2_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM2);
}

/**
  * @details This function disables the ITCM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ITCM_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_ITCM);
}

/**
  * @details This function disables the ITCM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ITCM_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_ITCM);
}

#if defined (NPU_PRESENT)
/**
  * @details This function disables the NPU clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_NPU_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_NPU);
}

/**
  * @details This function disables the NPU clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_NPU_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_NPU);
}
#endif /* NPU_PRESENT */

/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Sleep_Enable_Disable APB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the TIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function enables the TIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM2_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function enables the TIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function enables the TIM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM3_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function enables the TIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM4_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function enables the TIM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM4_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function enables the TIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM5_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function enables the TIM5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM5_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function enables the TIM6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM6_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function enables the TIM6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM6_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function enables the TIM7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM7_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function enables the TIM7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM7_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function enables the TIM12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM12_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function enables the TIM12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM12_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function enables the TIM13 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM13_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function enables the TIM13 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM13_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function enables the TIM14 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM14_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function enables the TIM14 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM14_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function enables the LPTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function enables the LPTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function enables the WWDG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_WWDG_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function enables the WWDG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_WWDG_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function enables the TIM10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM10_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function enables the TIM10 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM10_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function enables the TIM11 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM11_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function enables the TIM11 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM11_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function enables the SPI2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function enables the SPI2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI2_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function enables the SPI3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function enables the SPI3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI3_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function enables the USART2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function enables the USART2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART2_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function enables the USART3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function enables the USART3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART3_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function enables the UART4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART4_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function enables the UART4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART4_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function enables the UART5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART5_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function enables the UART5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART5_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function enables the I2C1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C1_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function enables the I2C1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C1_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function enables the I2C2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function enables the I2C2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C2_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function enables the I2C3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function enables the I2C3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function enables the I3C1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I3C1_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function enables the I3C1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I3C1_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function enables the UART7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART7_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function enables the UART7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART7_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function enables the UART8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART8_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @details This function enables the UART8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART8_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @details This function disables the TIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function disables the TIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function disables the TIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function disables the TIM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM3_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function disables the TIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM4_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function disables the TIM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM4_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function disables the TIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM5_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function disables the TIM5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM5_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function disables the TIM6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM6_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function disables the TIM6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM6_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function disables the TIM7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM7_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function disables the TIM7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM7_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function disables the TIM12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM12_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function disables the TIM12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM12_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function disables the TIM13 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM13_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function disables the TIM13 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM13_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function disables the TIM14 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM14_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function disables the TIM14 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM14_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function disables the LPTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function disables the LPTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function disables the WWDG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_WWDG_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function disables the WWDG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_WWDG_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function disables the TIM10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM10_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function disables the TIM10 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM10_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function disables the TIM11 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM11_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function disables the TIM11 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM11_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function disables the SPI2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function disables the SPI2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function disables the SPI3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function disables the SPI3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI3_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function disables the USART2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function disables the USART2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function disables the USART3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function disables the USART3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART3_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function disables the UART4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART4_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function disables the UART4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART4_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function disables the UART5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART5_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function disables the UART5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART5_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function disables the I2C1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C1_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function disables the I2C1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C1_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function disables the I2C2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function disables the I2C2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function disables the I2C3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function disables the I2C3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function disables the I3C1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I3C1_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function disables the I3C1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I3C1_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function disables the UART7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART7_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function disables the UART7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART7_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function disables the UART8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART8_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @details This function disables the UART8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART8_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Sleep_Enable_Disable APB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the CRS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRS_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function enables the CRS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRS_EnableClockInStopMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function enables the FDCAN clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FDCAN_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function enables the FDCAN clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FDCAN_EnableClockInStopMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function enables the UCPD1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UCPD1_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @details This function enables the UCPD1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UCPD1_EnableClockInStopMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @details This function disables the CRS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRS_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function disables the CRS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRS_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function disables the FDCAN clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FDCAN_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function disables the FDCAN clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FDCAN_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function disables the UCPD1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UCPD1_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @details This function disables the UCPD1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UCPD1_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Sleep_Enable_Disable APB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the TIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function enables the TIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM1_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function enables the TIM8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM8_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function enables the TIM8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM8_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function enables the TIM20 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM20_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function enables the TIM20 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM20_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function enables the USART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function enables the USART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART1_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function enables the USART6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART6_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function enables the USART6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART6_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function enables the UART9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART9_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function enables the UART9 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART9_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function enables the USART10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART10_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function enables the USART10 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART10_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function enables the SPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function enables the SPI1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI1_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function enables the SPI4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI4_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function enables the SPI4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI4_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function enables the TIM15 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM15_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function enables the TIM15 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM15_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function enables the TIM16 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM16_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function enables the TIM16 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM16_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function enables the TIM17 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM17_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function enables the TIM17 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM17_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function enables the TIM9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM9_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function enables the TIM9 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM9_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function enables the SPI5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI5_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function enables the SPI5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI5_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function enables the HRTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HRTIM1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function enables the HRTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HRTIM1_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function enables the HRTIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HRTIM2_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @details This function enables the HRTIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HRTIM2_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @details This function disables the TIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function disables the TIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function disables the TIM8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM8_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function disables the TIM8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM8_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function disables the TIM20 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM20_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function disables the TIM20 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM20_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function disables the USART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function disables the USART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function disables the USART6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART6_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function disables the USART6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART6_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function disables the UART9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART9_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function disables the UART9 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART9_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function disables the USART10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART10_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function disables the USART10 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART10_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function disables the SPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function disables the SPI1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function disables the SPI4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI4_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function disables the SPI4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI4_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function disables the TIM15 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM15_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function disables the TIM15 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM15_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function disables the TIM16 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM16_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function disables the TIM16 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM16_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function disables the TIM17 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM17_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function disables the TIM17 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM17_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function disables the TIM9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM9_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function disables the TIM9 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM9_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function disables the SPI5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI5_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function disables the SPI5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI5_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function disables the HRTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HRTIM1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function disables the HRTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HRTIM1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function disables the HRTIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HRTIM2_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @details This function disables the HRTIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HRTIM2_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @}
  */

/** @defgroup RCC_APB4_Peripheral_Clock_Sleep_Enable_Disable APB4 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB4 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the SBS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SBS_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function enables the SBS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SBS_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function enables the LPUART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function enables the LPUART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function enables the SPI6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI6_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function enables the SPI6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI6_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function enables the LPTIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM2_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function enables the LPTIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM2_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function enables the LPTIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM3_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function enables the LPTIM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM3_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function enables the LPTIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM4_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function enables the LPTIM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM4_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function enables the LPTIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM5_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function enables the LPTIM5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM5_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function enables the VREFBUF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREFBUF_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function enables the VREFBUF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREFBUF_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function enables the RTCAPB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function enables the RTCAPB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function enables the DTS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTS_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function enables the DTS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTS_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function enables the COMP12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP12_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function enables the COMP12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP12_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function enables the COMP34 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP34_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function enables the COMP34 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP34_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function enables the COMP56 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP56_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function enables the COMP56 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP56_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function enables the COMP78 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP78_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @details This function enables the COMP78 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP78_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @details This function disables the SBS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SBS_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function disables the SBS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SBS_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function disables the LPUART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function disables the LPUART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function disables the SPI6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI6_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function disables the SPI6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI6_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function disables the LPTIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM2_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function disables the LPTIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM2_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function disables the LPTIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM3_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function disables the LPTIM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM3_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function disables the LPTIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM4_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function disables the LPTIM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM4_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function disables the LPTIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM5_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function disables the LPTIM5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM5_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function disables the VREFBUF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREFBUF_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function disables the VREFBUF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREFBUF_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function disables the RTCAPB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the RTCAPB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the DTS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTS_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function disables the DTS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTS_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function disables the COMP12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP12_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function disables the COMP12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP12_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function disables the COMP34 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP34_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function disables the COMP34 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP34_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function disables the COMP56 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP56_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function disables the COMP56 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP56_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function disables the COMP78 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP78_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @details This function disables the COMP78 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP78_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @}
  */

/** @defgroup RCC_AXI_Clock_Gating_Enable_Disable AXI Clocks gating Enable Disable
  * @brief    Enable or disable the clock gating.
  * @note     The dynamic power consumption can be optimized by enabling the functional clock gating.
  *           After reset, the clock gating is enabled (except for JTAG if a JTAG connection has been detected).
  * @{
  */

/**
  * @details This function enables the AXI clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXI_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AXI);
}

/**
  * @details This function disables the AXI clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXI_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AXI);
}

/**
  * @details This function enables the AHBM clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBM_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AHBM);
}

/**
  * @details This function disables the AHBM clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBM_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AHBM);
}

/**
  * @details This function enables the SDMMC1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_SDMMC1);
}

/**
  * @details This function disables the SDMMC1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_SDMMC1);
}

/**
  * @details This function enables the HPDMA1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_HPDMA1);
}

/**
  * @details This function disables the HPDMA1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_HPDMA1);
}

/**
  * @details This function enables the CPU clock gating.
  */
__STATIC_INLINE void HAL_RCC_CPU_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_CPU);
}

/**
  * @details This function disables the CPU clock gating.
  */
__STATIC_INLINE void HAL_RCC_CPU_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_CPU);
}

/**
  * @details This function enables the AHBS clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBS_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AHBS);
}

/**
  * @details This function disables the AHBS clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBS_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AHBS);
}

/**
  * @details This function enables the AHBIC clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBIC_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AHBIC);
}

/**
  * @details This function disables the AHBIC clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBIC_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AHBIC);
}

/**
  * @details This function enables the FMC clock gating.
  */
__STATIC_INLINE void HAL_RCC_FMC_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_FMC);
}

/**
  * @details This function disables the FMC clock gating.
  */
__STATIC_INLINE void HAL_RCC_FMC_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_FMC);
}

/**
  * @details This function enables the XSPI1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_XSPI1);
}

/**
  * @details This function disables the XSPI1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_XSPI1);
}

/**
  * @details This function enables the AXISRAM4 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM4_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AXISRAM4);
}

/**
  * @details This function disables the AXISRAM4 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM4_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AXISRAM4);
}

/**
  * @details This function enables the AXISRAM3 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM3_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AXISRAM3);
}

/**
  * @details This function disables the AXISRAM3 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM3_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AXISRAM3);
}

/**
  * @details This function enables the AXISRAM2 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM2_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AXISRAM2);
}

/**
  * @details This function disables the AXISRAM2 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM2_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AXISRAM2);
}

/**
  * @details This function enables the AXISRAM1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM1_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AXISRAM1);
}

/**
  * @details This function disables the AXISRAM1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM1_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AXISRAM1);
}

/**
  * @details This function enables the FLASH clock gating.
  */
__STATIC_INLINE void HAL_RCC_FLASH_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_FLASH);
}

/**
  * @details This function disables the FLASH clock gating.
  */
__STATIC_INLINE void HAL_RCC_FLASH_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_FLASH);
}

/**
  * @details This function enables the EXTI clock gating.
  */
__STATIC_INLINE void HAL_RCC_EXTI_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_EXTI);
}

/**
  * @details This function disables the EXTI clock gating.
  */
__STATIC_INLINE void HAL_RCC_EXTI_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_EXTI);
}

/**
  * @details This function enables the JTAG clock gating.
  */
__STATIC_INLINE void HAL_RCC_JTAG_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_JTAG);
}

/**
  * @details This function disables the JTAG clock gating.
  */
__STATIC_INLINE void HAL_RCC_JTAG_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_JTAG);
}

/**
  * @}
  */


/** @defgroup RCC_Backup_Domain_Reset RCC Backup Domain Reset
  * @{
  */

/** @brief    Function to force and release the Backup domain.
  * @details  When a Backup domain reset occurs, the following domains are impacted:
  *           - the RTC is stopped and all the RTC registers are set to their reset values
  *             (including the backup registers)
  *           - all TAMP registers can be read or written in both secure and non-secure modes.
  *             The secure boot code can change this security setup, making some registers secure
  *             or not as needed, using TAMP_SECCFGR register.
  *           - The SRAM2 and BKPSRAM are affected by this reset.
  *           - LSE crystal 32kHz oscillator
  *           - RCC_BDCR register
  */
__STATIC_INLINE void HAL_RCC_ResetRTCDomain(void)
{
  LL_RCC_ForceBackupDomainReset();
  LL_RCC_ReleaseBackupDomainReset();
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group3 RCC services functions
  This subsection provides a set of functions allowing to:

  - Configure the MCO.
    - MCO (Microcontroller Clock Output): used to output HSI, LSE, HSE, HSI48, CSI, LSI,
    SYSCLK, PLL1P, PLL1Q, PLL2P (through a configurable prescaler) on a pin.

  - Get and clear reset flags

  - Enable the CSS (Clock Security System). Once CSS is enabled, if a HSE clock failure occurs (HSE used directly or
  through PLL as System clock source), the System clock source is automatically switched to HSI.
  The HSECSS interrupt is linked to the Cortex-M7 NMI (non-maskable interrupt) exception vector.
  The NMI is executed indefinitely unless the HSECSS interrupt flag (HSECSSF) is cleared. As a consequence, in the
  NMI ISR, the user must clear the HSECSSF by setting the HSECSSC bit.

  - Enable Clock security system on LSE (LSECSS).

  - Enable RTC and TAMP clock.

  *
  * @{
  */

void                         HAL_RCC_SetConfigMCO(hal_rcc_mco_src_t mcox_src, hal_rcc_mco_prescaler_t mcox_prescaler);
uint32_t                     HAL_RCC_GetResetSource(void);
void                         HAL_RCC_ClearResetFlags(void);
#if defined(HSE_VALUE)
void                         HAL_RCC_HSE_EnableCSS(void);
hal_status_t                 HAL_RCC_HSE_CSSCallback(void);
hal_status_t                 HAL_RCC_NMI_IRQHandler(void);
#endif /* HSE_VALUE */
void                         HAL_RCC_SetClockAfterWakeFromStop(hal_rcc_stop_wakeup_clk_t wakeup_clk);
hal_rcc_stop_wakeup_clk_t    HAL_RCC_GetClockAfterWakeFromStop(void);
void                         HAL_RCC_SetKernelClkAfterWakeFromStop(hal_rcc_stop_wakeup_kerclk_t wakeup_clk);
hal_rcc_stop_wakeup_kerclk_t HAL_RCC_GetKernelClkAfterWakeFromStop(void);
#if defined(LSE_VALUE)
void                                        HAL_RCC_LSE_EnableCSS(void);
void                                        HAL_RCC_LSE_DisableCSS(void);
hal_rcc_lse_css_failure_detection_status_t  HAL_RCC_LSE_IsCSSDetected(void);
void                                        HAL_RCC_LSE_RearmCSS(void);
void                                        HAL_RCC_LSECSS_IRQHandler(void);
void                                        HAL_RCC_LSE_CSSCallback(void);
#endif /* LSE_VALUE */
hal_status_t                 HAL_RCC_RTC_EnableKernelClock(void);
hal_status_t                 HAL_RCC_RTC_DisableKernelClock(void);
void                         HAL_RCC_RTC_SetHSEPrescaler(uint32_t prescaler);
uint32_t                     HAL_RCC_RTC_GetHSEPrescaler(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group4 Peripheral Clock configurations
  * This subsection provides a set of functions:

  - Set Peripheral Clock (PERCLK) clock source.
  - Get Peripheral Clock (PERCLK) clock source.

  * @{
  */

hal_status_t                 HAL_RCC_PERCLK_SetSource(hal_rcc_perclk_src_t clk_src);
hal_rcc_perclk_src_t         HAL_RCC_PERCLK_GetSource(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group5 Kernel clock source configuration for peripherals
  This subsection provides a set of functions:
  - to disable all peripherals Kernel clocks
  - to control Kernel clock source configuration for peripherals
  - to control specific Kernel clock prescaler for peripherals if available
  - to get peripheral clock frequency

  Only functions having a kernel clock are handled by these functions.


    example: @ref HAL_RCC_USART16910_SetKernelClkSource(hal_rcc_usart16910_clk_src_t clk_src) to select
    HSI as clock source of USART1

    @code HAL_RCC_USART16910_SetKernelClkSource(HAL_RCC_USART16910_CLK_SRC_HSI);    @endcode

    - The peripheral Clocks source is retrieved thanks to
    hal_rcc_{periph}_clk_src_t HAL_RCC_{PERIPHx}_GetKernelClkSource(void)

    - The peripheral clock can be divided by a specific value:
      - API HAL_RCC_{PERIPHx}_SetKernelClkPrescaler(hal_rcc_{periphx}_prescaler_t clk_prescaler)
      example: @ref HAL_RCC_ADC_SetKernelClkPrescaler(hal_rcc_adc_prescaler_t clk_prescaler)
      - API hal_rcc_{periphx}_prescaler_t HAL_RCC_{PERIPHx}_GetKernelClkPrescaler(void)
      example: @ref hal_rcc_adc_prescaler_t HAL_RCC_ADC_GetKernelClkPrescaler(void)

    - The functionalities of the two previous functions are grouped into one common function:
      - API HAL_RCC_{PERIPHx}_SetConfigKernelClk(hal_rcc_{periphx}_clk_src_t clk_src,
                                            hal_rcc_{periphx}_prescaler_t prescaler)
      example: @ref HAL_RCC_ADC_SetConfigKernelClk(hal_rcc_adc_clk_src_t clk_src,
                                                    hal_rcc_adc_prescaler_t prescaler)
      - API HAL_RCC_{PERIPHx}_GetConfigKernelClk(hal_rcc_{periphx}_clk_src_t *p_clk_src,
                                            hal_rcc_{periphx}_prescaler_t *p_prescaler)
      example: @ref HAL_RCC_ADC_GetConfigKernelClk(hal_rcc_adc_clk_src_t *p_clk_src,
                                                    hal_rcc_adc_prescaler_t *p_prescaler)

    - All peripherals can get their peripheral clock frequency
      - API uint32_t HAL_RCC_{PERIPHx}_GetKernelClkFreq(void)
      example: @ref HAL_RCC_USART16910_GetKernelClkFreq(void)
  * @{
  */
hal_status_t                  HAL_RCC_DisableAllKernelClocks(void);
hal_status_t                  HAL_RCC_FMC_SetKernelClkSource(hal_rcc_fmc_clk_src_t clk_src);
hal_status_t                  HAL_RCC_SDMMC1_SetKernelClkSource(hal_rcc_sdmmc1_clk_src_t clk_src);
hal_status_t                  HAL_RCC_XSPI1_SetKernelClkSource(hal_rcc_xspi1_clk_src_t clk_src);
hal_status_t                  HAL_RCC_USBOTGFS_SetKernelClkSource(hal_rcc_usbotgfs_clk_src_t clk_src);
hal_status_t                  HAL_RCC_ADF1_SetKernelClkSource(hal_rcc_adf1_clk_src_t clk_src);
hal_status_t                  HAL_RCC_ADC_SetKernelClkSource(hal_rcc_adc_clk_src_t clk_src);
hal_status_t                  HAL_RCC_ADC_SetKernelClkPrescaler(hal_rcc_adc_prescaler_t  prescaler);
hal_status_t                  HAL_RCC_ADC_SetConfigKernelClk(hal_rcc_adc_clk_src_t clk_src,
                                                             hal_rcc_adc_prescaler_t prescaler);
hal_status_t                  HAL_RCC_UART234578_SetKernelClkSource(hal_rcc_uart234578_clk_src_t clk_src);
hal_status_t                  HAL_RCC_SPI1_SetKernelClkSource(hal_rcc_spi1_clk_src_t clk_src);
hal_status_t                  HAL_RCC_SPI6_SetKernelClkSource(hal_rcc_spi6_clk_src_t clk_src);
hal_status_t                  HAL_RCC_SPI23_SetKernelClkSource(hal_rcc_spi23_clk_src_t clk_src);
hal_status_t                  HAL_RCC_SPI45_SetKernelClkSource(hal_rcc_spi45_clk_src_t clk_src);
hal_status_t                  HAL_RCC_I2C123_SetKernelClkSource(hal_rcc_i2c123_clk_src_t clk_src);
hal_status_t                  HAL_RCC_I3C1_SetKernelClkSource(hal_rcc_i3c1_clk_src_t clk_src);
hal_status_t                  HAL_RCC_LPTIM1_SetKernelClkSource(hal_rcc_lptim1_clk_src_t clk_src);
hal_status_t                  HAL_RCC_LPTIM23_SetKernelClkSource(hal_rcc_lptim23_clk_src_t clk_src);
hal_status_t                  HAL_RCC_LPTIM45_SetKernelClkSource(hal_rcc_lptim45_clk_src_t clk_src);
hal_status_t                  HAL_RCC_FDCAN_SetKernelClkSource(hal_rcc_fdcan_clk_src_t clk_src);
hal_status_t                  HAL_RCC_USART16910_SetKernelClkSource(hal_rcc_usart16910_clk_src_t clk_src);
hal_status_t                  HAL_RCC_LPUART1_SetKernelClkSource(hal_rcc_lpuart1_clk_src_t clk_src);
hal_status_t                  HAL_RCC_DAC1_SetKernelClkSource(hal_rcc_dac1_clk_src_t clk_src);
hal_status_t                  HAL_RCC_DAC2_SetKernelClkSource(hal_rcc_dac2_clk_src_t clk_src);
hal_status_t                  HAL_RCC_DAC3_SetKernelClkSource(hal_rcc_dac3_clk_src_t clk_src);
hal_status_t                  HAL_RCC_DAC4_SetKernelClkSource(hal_rcc_dac4_clk_src_t clk_src);
hal_status_t                  HAL_RCC_DAC1_SetSampleHoldClkSource(hal_rcc_dac1sh_clk_src_t clk_src);
hal_status_t                  HAL_RCC_RTC_SetKernelClkSource(hal_rcc_rtc_clk_src_t clk_src);

hal_rcc_fmc_clk_src_t         HAL_RCC_FMC_GetKernelClkSource(void);
hal_rcc_sdmmc1_clk_src_t      HAL_RCC_SDMMC1_GetKernelClkSource(void);
hal_rcc_xspi1_clk_src_t       HAL_RCC_XSPI1_GetKernelClkSource(void);
hal_rcc_usbotgfs_clk_src_t    HAL_RCC_USBOTGFS_GetKernelClkSource(void);
hal_rcc_adf1_clk_src_t        HAL_RCC_ADF1_GetKernelClkSource(void);
hal_rcc_adc_clk_src_t         HAL_RCC_ADC_GetKernelClkSource(void);
hal_rcc_adc_prescaler_t       HAL_RCC_ADC_GetKernelClkPrescaler(void);
void                          HAL_RCC_ADC_GetConfigKernelClk(hal_rcc_adc_clk_src_t *p_clk_src,
                                                             hal_rcc_adc_prescaler_t *p_prescaler);
hal_rcc_uart234578_clk_src_t  HAL_RCC_UART234578_GetKernelClkSource(void);
hal_rcc_spi1_clk_src_t        HAL_RCC_SPI1_GetKernelClkSource(void);
hal_rcc_spi6_clk_src_t        HAL_RCC_SPI6_GetKernelClkSource(void);
hal_rcc_spi23_clk_src_t       HAL_RCC_SPI23_GetKernelClkSource(void);
hal_rcc_spi45_clk_src_t       HAL_RCC_SPI45_GetKernelClkSource(void);
hal_rcc_i2c123_clk_src_t      HAL_RCC_I2C123_GetKernelClkSource(void);
hal_rcc_i3c1_clk_src_t        HAL_RCC_I3C1_GetKernelClkSource(void);
hal_rcc_lptim1_clk_src_t      HAL_RCC_LPTIM1_GetKernelClkSource(void);
hal_rcc_lptim23_clk_src_t     HAL_RCC_LPTIM23_GetKernelClkSource(void);
hal_rcc_lptim45_clk_src_t     HAL_RCC_LPTIM45_GetKernelClkSource(void);
hal_rcc_fdcan_clk_src_t       HAL_RCC_FDCAN_GetKernelClkSource(void);
hal_rcc_usart16910_clk_src_t  HAL_RCC_USART16910_GetKernelClkSource(void);
hal_rcc_lpuart1_clk_src_t     HAL_RCC_LPUART1_GetKernelClkSource(void);
hal_rcc_dac1_clk_src_t        HAL_RCC_DAC1_GetKernelClkSource(void);
hal_rcc_dac2_clk_src_t        HAL_RCC_DAC2_GetKernelClkSource(void);
hal_rcc_dac3_clk_src_t        HAL_RCC_DAC3_GetKernelClkSource(void);
hal_rcc_dac4_clk_src_t        HAL_RCC_DAC4_GetKernelClkSource(void);
hal_rcc_dac1sh_clk_src_t      HAL_RCC_DAC1_GetSampleHoldClkSource(void);
hal_rcc_rtc_clk_src_t         HAL_RCC_RTC_GetKernelClkSource(void);

uint32_t                      HAL_RCC_FMC_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_SDMMC_GetKernelClkFreq(const SDMMC_TypeDef *sdmmcx);
uint32_t                      HAL_RCC_SDMMC1_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_XSPI_GetKernelClkFreq(const XSPI_TypeDef *xspix);
uint32_t                      HAL_RCC_XSPI1_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_USBOTGFS_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_ADF1_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_ADC_GetKernelClkFreq(const ADC_TypeDef *adcx);
uint32_t                      HAL_RCC_ADC1234_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_UART_GetKernelClkFreq(const USART_TypeDef *uartx);
uint32_t                      HAL_RCC_USART_GetKernelClkFreq(const USART_TypeDef *usartx);
uint32_t                      HAL_RCC_UART234578_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_USART16910_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_LPUART1_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_SPI_GetKernelClkFreq(const SPI_TypeDef *spix);
uint32_t                      HAL_RCC_SPI1_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_SPI6_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_SPI23_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_SPI45_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_I2C_GetKernelClkFreq(const I2C_TypeDef *i2cx);
uint32_t                      HAL_RCC_I2C123_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_I3C_GetKernelClkFreq(const I3C_TypeDef *i3cx);
uint32_t                      HAL_RCC_I3C1_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_HRTIM_GetKernelClkFreq(const HRTIM_TypeDef *hrtimx);
uint32_t                      HAL_RCC_HRTIM1_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_HRTIM2_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_TIM_GetKernelClkFreq(const TIM_TypeDef *timx);
uint32_t                      HAL_RCC_LPTIM_GetKernelClkFreq(const LPTIM_TypeDef *lptimx);
uint32_t                      HAL_RCC_LPTIM1_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_LPTIM23_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_LPTIM45_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_FDCAN_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_DAC_GetKernelClkFreq(const DAC_TypeDef *dacx);
uint32_t                      HAL_RCC_DAC1_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_DAC2_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_DAC3_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_DAC4_GetKernelClkFreq(void);
uint32_t                      HAL_RCC_DAC_GetSampleHoldClkFreq(const DAC_TypeDef *dacshx);
uint32_t                      HAL_RCC_DAC1_GetSampleHoldClkFreq(void);
uint32_t                      HAL_RCC_COMP_GetKernelClkFreq(const COMP_TypeDef *compx);
uint32_t                      HAL_RCC_RTC_GetKernelClkFreq(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group6 FMC and XSPI clock protection
  * This subsection provides a set of functions:

  - Enable, disable, and check FMC and XSPI clock protection state,
  - Get the current kernel clock source switch position for FMC and XSPI.

   * @{
  */
void                                    HAL_RCC_FMC_EnableClockProtection(void);
void                                    HAL_RCC_FMC_DisableClockProtection(void);
hal_rcc_clk_status_t                    HAL_RCC_FMC_IsEnabledClockProtection(void);
hal_rcc_fmc_clk_src_switch_position_t   HAL_RCC_FMC_GetKernelClkSwitchPosition(void);

void                                    HAL_RCC_XSPI_EnableClockProtection(void);
void                                    HAL_RCC_XSPI_DisableClockProtection(void);
hal_rcc_clk_status_t                    HAL_RCC_XSPI_IsEnabledClockProtection(void);
hal_rcc_xspi_clk_src_switch_position_t  HAL_RCC_XSPI_GetKernelClkSwitchPosition(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* RCC */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7PXX_HAL_RCC_H */
