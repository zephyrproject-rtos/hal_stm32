/**
  ******************************************************************************
  * @file    stm32g5xx_hal_rcc.h
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
#ifndef STM32G5XX_HAL_RCC_H
#define STM32G5XX_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_rcc.h"
#include "stm32g5xx_ll_bus.h"
#include "stm32g5xx_ll_pwr.h"

/** @addtogroup STM32G5XX_HAL_Driver
  * @{
  */

#if defined (RCC)

/** @addtogroup RCC
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants RCC Exported Constants
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
  * @brief Oscillator Stop mode status
  */
typedef enum
{
  HAL_RCC_OSC_DISABLED_IN_STOP_MODE = 0U,                                  /*!< Oscillator is enabled in Run mode only     */
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
  HAL_RCC_HSE_ON             = RCC_CR_HSEON,                                   /*!< HSE clock activation                        */
  HAL_RCC_HSE_BYPASS         = (RCC_CR_HSEON | RCC_CR_HSEBYP),                 /*!< External Analog clock source for HSE clock  */
  HAL_RCC_HSE_BYPASS_DIGITAL = (RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_HSEEXT), /*!< External Digital clock source for HSE clock */
} hal_rcc_hse_t;

#endif /* (HSE_VALUE) */

#if defined(LSE_VALUE)

/**
  * @brief LSE state
  */
typedef enum
{
  HAL_RCC_LSE_ON     = RCC_RTCCR_LSEON,                      /*!< LSE clock activation                       */
  HAL_RCC_LSE_BYPASS = (RCC_RTCCR_LSEON | RCC_RTCCR_LSEBYP), /*!< External Analog clock source for LSE clock */
} hal_rcc_lse_t;

/**
  * @brief LSE drive config
  */
typedef enum
{
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
  * @brief Default HSI trimming value
  */
#define HAL_RCC_HSICALIBRATION_DEFAULT 0x40U /* Default HSI trimming value */

/**
  * @brief System Clock Source
  */
typedef enum
{
  HAL_RCC_SYSCLK_SRC_HSI    = LL_RCC_SYS_CLKSOURCE_HSI, /*!< HSI selection as system clock  */
  HAL_RCC_SYSCLK_SRC_HSE    = LL_RCC_SYS_CLKSOURCE_HSE, /*!< HSE selection as system clock  */
  HAL_RCC_SYSCLK_SRC_PLLCLK = LL_RCC_SYS_CLKSOURCE_PLL1 /*!< PLL1 selection as system clock */
} hal_rcc_sysclk_src_t;

/**
  * @brief SYSTICK Clock Source
  */
typedef enum
{
  HAL_RCC_SYSTICK_CLK_SRC_HCLKDIV8 = LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8, /*!< HCLK_DIV8 clock used as SYSTICK clock */
  HAL_RCC_SYSTICK_CLK_SRC_LSI      = LL_RCC_SYSTICK_CLKSOURCE_LSI,      /*!< LSI clock used as SYSTICK clock       */
  HAL_RCC_SYSTICK_CLK_SRC_LSE      = LL_RCC_SYSTICK_CLKSOURCE_LSE,      /*!< LSE clock used as SYSTICK clock       */
} hal_rcc_systick_clk_src_t;

/**
  * @brief AHB Clock Prescaler
  */
typedef enum
{
  HAL_RCC_HCLK_PRESCALER1   = LL_RCC_HCLK_PRESCALER_1,   /*!< SYSCLK not divided    */
  HAL_RCC_HCLK_PRESCALER2   = LL_RCC_HCLK_PRESCALER_2,   /*!< SYSCLK divided by 2   */
  HAL_RCC_HCLK_PRESCALER4   = LL_RCC_HCLK_PRESCALER_4,   /*!< SYSCLK divided by 4   */
  HAL_RCC_HCLK_PRESCALER8   = LL_RCC_HCLK_PRESCALER_8,   /*!< SYSCLK divided by 8   */
  HAL_RCC_HCLK_PRESCALER16  = LL_RCC_HCLK_PRESCALER_16,  /*!< SYSCLK divided by 16  */
  HAL_RCC_HCLK_PRESCALER64  = LL_RCC_HCLK_PRESCALER_64,  /*!< SYSCLK divided by 64  */
  HAL_RCC_HCLK_PRESCALER128 = LL_RCC_HCLK_PRESCALER_128, /*!< SYSCLK divided by 128 */
  HAL_RCC_HCLK_PRESCALER256 = LL_RCC_HCLK_PRESCALER_256, /*!< SYSCLK divided by 256 */
  HAL_RCC_HCLK_PRESCALER512 = LL_RCC_HCLK_PRESCALER_512  /*!< SYSCLK divided by 512 */
} hal_rcc_hclk_prescaler_t;

/**
  * @brief APB1 APB2 APB3 Clock Prescaler
  */
typedef enum
{
  HAL_RCC_PCLK_PRESCALER1  = LL_RCC_APB1_PRESCALER_1,  /*!< HCLK not divided   */
  HAL_RCC_PCLK_PRESCALER2  = LL_RCC_APB1_PRESCALER_2,  /*!< HCLK divided by 2  */
  HAL_RCC_PCLK_PRESCALER4  = LL_RCC_APB1_PRESCALER_4,  /*!< HCLK divided by 4  */
  HAL_RCC_PCLK_PRESCALER8  = LL_RCC_APB1_PRESCALER_8,  /*!< HCLK divided by 8  */
  HAL_RCC_PCLK_PRESCALER16 = LL_RCC_APB1_PRESCALER_16  /*!< HCLK divided by 16 */
} hal_rcc_pclk_prescaler_t;

/**
  * @brief RTC Clock Source
  */
typedef enum
{
  HAL_RCC_RTC_CLK_SRC_NONE  = LL_RCC_RTC_CLKSOURCE_NONE,     /*!< No clock used as RTC clock                         */
  HAL_RCC_RTC_CLK_SRC_LSE     = LL_RCC_RTC_CLKSOURCE_LSE,    /*!< LSE clock used as RTC clock                        */
  HAL_RCC_RTC_CLK_SRC_LSI     = LL_RCC_RTC_CLKSOURCE_LSI,    /*!< LSI clock used as RTC clock                        */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV = LL_RCC_RTC_CLKSOURCE_HSE_DIV /*!< HSE oscillator clock divided by RTC prescaler used
                                                                  as RTC clock                                       */
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
  HAL_RCC_MCO2_SRC_SYSCLK = LL_RCC_MCO2SOURCE_SYSCLK, /*!< SYSCLK selection as MCO2 source */
  HAL_RCC_MCO2_SRC_PLL2P  = LL_RCC_MCO2SOURCE_PLL2P,  /*!< PLL2P selection as MCO2 source  */
  HAL_RCC_MCO2_SRC_HSE    = LL_RCC_MCO2SOURCE_HSE,    /*!< HSE selection as MCO2 source    */
  HAL_RCC_MCO2_SRC_PLL1P  = LL_RCC_MCO2SOURCE_PLL1P,  /*!< PLL1P selection as MCO2 source  */
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
  HAL_RCC_PLL_DISABLED = 0,                    /*!< PLL is disabled */
  HAL_RCC_PLL_ENABLED = ! HAL_RCC_PLL_DISABLED /*!< PLL is enabled  */
} hal_rcc_pll_status_t;

/**
  * @brief RCC PLLx Clock Source
  */
typedef enum
{
  HAL_RCC_PLL_SRC_NO_CLK = LL_RCC_PLL1SOURCE_NO_CLK, /*!< No clock selected as PLLx entry clock source  */
  HAL_RCC_PLL_SRC_HSI    = LL_RCC_PLL1SOURCE_HSI,    /*!< HSI clock selected as PLLx entry clock source */
  HAL_RCC_PLL_SRC_HSE    = LL_RCC_PLL1SOURCE_HSE,    /*!< HSE clock selected as PLLx entry clock source */
} hal_rcc_pll_src_t;

/**
  * @brief RCC PLLx input range
  */
typedef enum
{
  HAL_RCC_PLL_INPUT_RANGE_1_2   = LL_RCC_PLLINPUTRANGE_1_2,  /*!< PLLx input clock range frequency between 1 and 2MHz  */
  HAL_RCC_PLL_INPUT_RANGE_2_4   = LL_RCC_PLLINPUTRANGE_2_4,  /*!< PLLx input clock range frequency between 2 and 4MHz  */
  HAL_RCC_PLL_INPUT_RANGE_4_8   = LL_RCC_PLLINPUTRANGE_4_8,  /*!< PLLx input clock range frequency between 4 and 8MHz  */
  HAL_RCC_PLL_INPUT_RANGE_8_16  = LL_RCC_PLLINPUTRANGE_8_16, /*!< PLLx input clock range frequency between 8 and 16MHz */
} hal_rcc_pll_input_range_t;

/**
  * @brief RCC PLLx VCO range
  */
typedef enum
{
  HAL_RCC_PLL_VCO_RANGE_128_560  = LL_RCC_PLLVCORANGE_128_560,  /*!< PLLx wide VCO range: 128 to 560MHz  */
  HAL_RCC_PLL_VCO_RANGE_150_420  = LL_RCC_PLLVCORANGE_150_420,  /*!< PLLx medium VCO range: 150 to 420MHz  */
} hal_rcc_pll_vco_range_t;

/**
  * @brief  RCC ICLKx
  */
typedef enum
{
  HAL_RCC_ICLK1 = LL_RCC_ICLK1,
  HAL_RCC_ICLK2 = LL_RCC_ICLK2,
} hal_rcc_iclk_t;

/**
  * @brief  RCC ICLKx Divider
  */
typedef enum
{
  HAL_RCC_ICLK_DIV5 = LL_RCC_ICLK_DIV_5,
  HAL_RCC_ICLK_DIV3 = LL_RCC_ICLK_DIV_3,
} hal_rcc_iclk_div_t;


/** @defgroup RCC_PLL1_Clock_Output RCC PLL1 Clock Output
  * @{
  */
#define HAL_RCC_PLL1_OUTPUT_P   LL_RCC_PLL1_OUTPUT_P                                                 /*!< Output used System clock and POSENC                                       */
#define HAL_RCC_PLL1_OUTPUT_Q   LL_RCC_PLL1_OUTPUT_Q                                                 /*!< Output used by DAC, LPTIM1, XSPI1, USBFS, ADC, FDCAN and POSENC           */
#define HAL_RCC_PLL1_OUTPUT_R   LL_RCC_PLL1_OUTPUT_R                                                 /*!< Output used by ICLK1 (USART, UART, LPUART, SPI, I3C, I2C, ADC and POSENC) */
#define HAL_RCC_PLL1_OUTPUT_ALL (LL_RCC_PLL1_OUTPUT_P | LL_RCC_PLL1_OUTPUT_Q | LL_RCC_PLL1_OUTPUT_R) /*!< All PLL1 outputs                                                          */
#define HAL_RCC_PLL1_SYSCLK     HAL_RCC_PLL1_OUTPUT_P                                                /*!< Define used for legacy purpose */
/**
  * @}
  */

#if defined(PLL2)
/** @defgroup RCC_PLL2_Clock_Output RCC PLL2 Clock Output
  * @{
  */
#define HAL_RCC_PLL2_OUTPUT_P   LL_RCC_PLL2_OUTPUT_P                                                 /*!< Output used by SPI, PLAY1, LPTIM, ADC and POSENC                     */
#define HAL_RCC_PLL2_OUTPUT_Q   LL_RCC_PLL2_OUTPUT_Q                                                 /*!< Output used by USART, UART, LPUART, DAC, UCPD1, USB, FDCAN and POSENC */
#define HAL_RCC_PLL2_OUTPUT_R   LL_RCC_PLL2_OUTPUT_R                                                 /*!< Output used by ICLK2 (XSPI and POSENC)                               */
#define HAL_RCC_PLL2_OUTPUT_ALL (LL_RCC_PLL2_OUTPUT_P | LL_RCC_PLL2_OUTPUT_Q | LL_RCC_PLL2_OUTPUT_R) /*!< All PLL2 outputs                                                     */
/**
  * @}
  */
#endif /* PLL2 */

/** @defgroup RCC_Reset_Flag Reset Flag
  * @{
  */
#define HAL_RCC_RESET_FLAG_PIN   RCC_RSR_PINRSTF    /*!< Pin reset flag (NRST)           */
#define HAL_RCC_RESET_FLAG_PWR   RCC_RSR_PORRSTF    /*!< BOR or POR/PDR reset flag       */
#define HAL_RCC_RESET_FLAG_SW    RCC_RSR_SFTRSTF    /*!< Software Reset flag             */
#define HAL_RCC_RESET_FLAG_IWDG  RCC_RSR_IWDGRSTF   /*!< Independent Watchdog reset flag */
#define HAL_RCC_RESET_FLAG_WWDG  RCC_RSR_WWDGRSTF   /*!< Window watchdog reset flag      */
#define HAL_RCC_RESET_FLAG_LPWR  RCC_RSR_LPWRRSTF   /*!< Low-power reset flag            */

#define HAL_RCC_RESET_FLAG_ALL   (HAL_RCC_RESET_FLAG_PIN | HAL_RCC_RESET_FLAG_PWR | HAL_RCC_RESET_FLAG_SW | \
                                  HAL_RCC_RESET_FLAG_IWDG | HAL_RCC_RESET_FLAG_WWDG | HAL_RCC_RESET_FLAG_LPWR) /*!< All RCC reset flags */
/**
  * @}
  */

/** @defgroup RCC_Periph_Clock_Source Peripheral clock source
  * @{
  */

/**
  * @brief USART1 Clock Source
  */
typedef enum
{
  HAL_RCC_USART1_CLK_SRC_PCLK2 = LL_RCC_USART1_CLKSOURCE_PCLK2, /*!< PCLK2 selected as USART1 kernel clock */
  HAL_RCC_USART1_CLK_SRC_ICLK1 = LL_RCC_USART1_CLKSOURCE_ICLK1, /*!< ICLK1 selected as USART1 kernel clock */
  HAL_RCC_USART1_CLK_SRC_PLL2Q = LL_RCC_USART1_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as USART1 kernel clock */
  HAL_RCC_USART1_CLK_SRC_HSE   = LL_RCC_USART1_CLKSOURCE_HSE,   /*!< HSE selected as USART1 kernel clock   */
  HAL_RCC_USART1_CLK_SRC_HSI   = LL_RCC_USART1_CLKSOURCE_HSI,   /*!< HSI selected as USART1 kernel clock   */
  HAL_RCC_USART1_CLK_SRC_LSE   = LL_RCC_USART1_CLKSOURCE_LSE,   /*!< LSE selected as USART1 kernel clock   */
} hal_rcc_usart1_clk_src_t;

/**
  * @brief USART2 Clock Source
  */
typedef enum
{
  HAL_RCC_USART2_CLK_SRC_PCLK1 = LL_RCC_USART2_CLKSOURCE_PCLK1, /*!< PCLK1 selected as USART2 kernel clock */
  HAL_RCC_USART2_CLK_SRC_ICLK1 = LL_RCC_USART2_CLKSOURCE_ICLK1, /*!< ICLK1 selected as USART2 kernel clock */
  HAL_RCC_USART2_CLK_SRC_PLL2Q = LL_RCC_USART2_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as USART2 kernel clock */
  HAL_RCC_USART2_CLK_SRC_HSE   = LL_RCC_USART2_CLKSOURCE_HSE,   /*!< HSE selected as USART2 kernel clock   */
  HAL_RCC_USART2_CLK_SRC_HSI   = LL_RCC_USART2_CLKSOURCE_HSI,   /*!< HSI selected as USART2 kernel clock   */
  HAL_RCC_USART2_CLK_SRC_LSE   = LL_RCC_USART2_CLKSOURCE_LSE,   /*!< LSE selected as USART2 kernel clock   */
} hal_rcc_usart2_clk_src_t;

#if defined(USART3)
/**
  * @brief USART3 Clock Source
  */
typedef enum
{
  HAL_RCC_USART3_CLK_SRC_PCLK1 = LL_RCC_USART3_CLKSOURCE_PCLK1, /*!< PCLK1 selected as USART3 kernel clock */
  HAL_RCC_USART3_CLK_SRC_ICLK1 = LL_RCC_USART3_CLKSOURCE_ICLK1, /*!< ICLK1 selected as USART3 kernel clock */
  HAL_RCC_USART3_CLK_SRC_PLL2Q = LL_RCC_USART3_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as USART3 kernel clock */
  HAL_RCC_USART3_CLK_SRC_HSE   = LL_RCC_USART3_CLKSOURCE_HSE,   /*!< HSE selected as USART3 kernel clock   */
  HAL_RCC_USART3_CLK_SRC_HSI   = LL_RCC_USART3_CLKSOURCE_HSI,   /*!< HSI selected as USART3 kernel clock   */
  HAL_RCC_USART3_CLK_SRC_LSE   = LL_RCC_USART3_CLKSOURCE_LSE,   /*!< LSE selected as USART3 kernel clock   */
} hal_rcc_usart3_clk_src_t;
#endif /* USART3 */

/**
  * @brief UART4 Clock Source
  */
typedef enum
{
  HAL_RCC_UART4_CLK_SRC_PCLK1 = LL_RCC_UART4_CLKSOURCE_PCLK1, /*!< PCLK1 selected as UART4 kernel clock */
  HAL_RCC_UART4_CLK_SRC_ICLK1 = LL_RCC_UART4_CLKSOURCE_ICLK1, /*!< ICLK1 selected as UART4 kernel clock */
  HAL_RCC_UART4_CLK_SRC_PLL2Q = LL_RCC_UART4_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as UART4 kernel clock */
  HAL_RCC_UART4_CLK_SRC_HSE   = LL_RCC_UART4_CLKSOURCE_HSE,   /*!< HSE selected as UART4 kernel clock   */
  HAL_RCC_UART4_CLK_SRC_HSI   = LL_RCC_UART4_CLKSOURCE_HSI,   /*!< HSI selected as UART4 kernel clock   */
  HAL_RCC_UART4_CLK_SRC_LSE   = LL_RCC_UART4_CLKSOURCE_LSE,   /*!< LSE selected as UART4 kernel clock   */
} hal_rcc_uart4_clk_src_t;

/**
  * @brief UART5 Clock Source
  */
typedef enum
{
  HAL_RCC_UART5_CLK_SRC_PCLK1 = LL_RCC_UART5_CLKSOURCE_PCLK1, /*!< PCLK1 selected as UART5 kernel clock */
  HAL_RCC_UART5_CLK_SRC_ICLK1 = LL_RCC_UART5_CLKSOURCE_ICLK1, /*!< ICLK1 selected as UART5 kernel clock */
  HAL_RCC_UART5_CLK_SRC_PLL2Q = LL_RCC_UART5_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as UART5 kernel clock */
  HAL_RCC_UART5_CLK_SRC_HSE   = LL_RCC_UART5_CLKSOURCE_HSE,   /*!< HSE selected as UART5 kernel clock   */
  HAL_RCC_UART5_CLK_SRC_HSI   = LL_RCC_UART5_CLKSOURCE_HSI,   /*!< HSI selected as UART5 kernel clock   */
  HAL_RCC_UART5_CLK_SRC_LSE   = LL_RCC_UART5_CLKSOURCE_LSE,   /*!< LSE selected as UART5 kernel clock   */
} hal_rcc_uart5_clk_src_t;

/**
  * @brief UART6 Clock Source
  */
typedef enum
{
  HAL_RCC_UART6_CLK_SRC_PCLK1 = LL_RCC_UART6_CLKSOURCE_PCLK1, /*!< PCLK1 selected as UART6 kernel clock */
  HAL_RCC_UART6_CLK_SRC_ICLK1 = LL_RCC_UART6_CLKSOURCE_ICLK1, /*!< ICLK1 selected as UART6 kernel clock */
  HAL_RCC_UART6_CLK_SRC_PLL2Q = LL_RCC_UART6_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as UART6 kernel clock */
  HAL_RCC_UART6_CLK_SRC_HSE   = LL_RCC_UART6_CLKSOURCE_HSE,   /*!< HSE selected as UART6 kernel clock   */
  HAL_RCC_UART6_CLK_SRC_HSI   = LL_RCC_UART6_CLKSOURCE_HSI,   /*!< HSI selected as UART6 kernel clock   */
  HAL_RCC_UART6_CLK_SRC_LSE   = LL_RCC_UART6_CLKSOURCE_LSE,   /*!< LSE selected as UART6 kernel clock   */
} hal_rcc_uart6_clk_src_t;

/**
  * @brief LPUART1 Clock Source
  */
typedef enum
{
  HAL_RCC_LPUART1_CLK_SRC_PCLK3 = LL_RCC_LPUART1_CLKSOURCE_PCLK3, /*!< PCLK3 selected as LPUART1 kernel clock */
  HAL_RCC_LPUART1_CLK_SRC_ICLK1 = LL_RCC_LPUART1_CLKSOURCE_ICLK1, /*!< ICLK1 selected as LPUART1 kernel clock */
  HAL_RCC_LPUART1_CLK_SRC_PLL2Q = LL_RCC_LPUART1_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as LPUART1 kernel clock */
  HAL_RCC_LPUART1_CLK_SRC_HSE   = LL_RCC_LPUART1_CLKSOURCE_HSE,   /*!< HSE selected as LPUART1 kernel clock   */
  HAL_RCC_LPUART1_CLK_SRC_HSI   = LL_RCC_LPUART1_CLKSOURCE_HSI,   /*!< HSI selected as LPUART1 kernel clock   */
  HAL_RCC_LPUART1_CLK_SRC_LSE   = LL_RCC_LPUART1_CLKSOURCE_LSE,   /*!< LSE selected as LPUART1 kernel clock   */
} hal_rcc_lpuart1_clk_src_t;

/**
  * @brief DAC1 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC1_CLK_SRC_TIM   = LL_RCC_DAC1_CLKSOURCE_TIM,   /*!< TIM selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_HRTIM = LL_RCC_DAC1_CLKSOURCE_HRTIM, /*!< HRTIM selected as DAC1 kernel clock */
  HAL_RCC_DAC1_CLK_SRC_ADC   = LL_RCC_DAC1_CLKSOURCE_ADC,   /*!< ADC selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_HSE   = LL_RCC_DAC1_CLKSOURCE_HSE,   /*!< HSE selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_HSI   = LL_RCC_DAC1_CLKSOURCE_HSI,   /*!< HSI selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_PLL1Q = LL_RCC_DAC1_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as DAC1 kernel clock */
  HAL_RCC_DAC1_CLK_SRC_PLL2Q = LL_RCC_DAC1_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as DAC1 kernel clock */
} hal_rcc_dac1_clk_src_t;

/**
  * @brief DAC1SH Clock Source
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
  HAL_RCC_DAC2_CLK_SRC_TIM   = LL_RCC_DAC2_CLKSOURCE_TIM,   /*!< TIM selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_HRTIM = LL_RCC_DAC2_CLKSOURCE_HRTIM, /*!< HRTIM selected as DAC2 kernel clock */
  HAL_RCC_DAC2_CLK_SRC_ADC   = LL_RCC_DAC2_CLKSOURCE_ADC,   /*!< ADC selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_HSE   = LL_RCC_DAC2_CLKSOURCE_HSE,   /*!< HSE selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_HSI   = LL_RCC_DAC2_CLKSOURCE_HSI,   /*!< HSI selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_PLL1Q = LL_RCC_DAC2_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as DAC2 kernel clock */
  HAL_RCC_DAC2_CLK_SRC_PLL2Q = LL_RCC_DAC2_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as DAC2 kernel clock */
} hal_rcc_dac2_clk_src_t;

/**
  * @brief DAC2SH Clock Source
  */
typedef enum
{
  HAL_RCC_DAC2SH_CLK_SRC_LSE = LL_RCC_DAC2SH_CLKSOURCE_LSE, /*!< LSE selected as DAC2SH kernel clock */
  HAL_RCC_DAC2SH_CLK_SRC_LSI = LL_RCC_DAC2SH_CLKSOURCE_LSI  /*!< LSI selected as DAC2SH kernel clock */
} hal_rcc_dac2sh_clk_src_t;

/**
  * @brief DAC5 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC5_CLK_SRC_TIM   = LL_RCC_DAC5_CLKSOURCE_TIM,   /*!< TIM selected as DAC5 kernel clock   */
  HAL_RCC_DAC5_CLK_SRC_HRTIM = LL_RCC_DAC5_CLKSOURCE_HRTIM, /*!< HRTIM selected as DAC5 kernel clock */
  HAL_RCC_DAC5_CLK_SRC_ADC   = LL_RCC_DAC5_CLKSOURCE_ADC,   /*!< ADC selected as DAC5 kernel clock   */
  HAL_RCC_DAC5_CLK_SRC_HSE   = LL_RCC_DAC5_CLKSOURCE_HSE,   /*!< HSE selected as DAC5 kernel clock   */
  HAL_RCC_DAC5_CLK_SRC_HSI   = LL_RCC_DAC5_CLKSOURCE_HSI,   /*!< HSI selected as DAC5 kernel clock   */
  HAL_RCC_DAC5_CLK_SRC_PLL1Q = LL_RCC_DAC5_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as DAC5 kernel clock */
  HAL_RCC_DAC5_CLK_SRC_PLL2Q = LL_RCC_DAC5_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as DAC5 kernel clock */
} hal_rcc_dac5_clk_src_t;

/**
  * @brief DAC6 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC6_CLK_SRC_TIM   = LL_RCC_DAC6_CLKSOURCE_TIM,   /*!< TIM selected as DAC6 kernel clock   */
  HAL_RCC_DAC6_CLK_SRC_HRTIM = LL_RCC_DAC6_CLKSOURCE_HRTIM, /*!< HRTIM selected as DAC6 kernel clock */
  HAL_RCC_DAC6_CLK_SRC_ADC   = LL_RCC_DAC6_CLKSOURCE_ADC,   /*!< ADC selected as DAC6 kernel clock   */
  HAL_RCC_DAC6_CLK_SRC_HSE   = LL_RCC_DAC6_CLKSOURCE_HSE,   /*!< HSE selected as DAC6 kernel clock   */
  HAL_RCC_DAC6_CLK_SRC_HSI   = LL_RCC_DAC6_CLKSOURCE_HSI,   /*!< HSI selected as DAC6 kernel clock   */
  HAL_RCC_DAC6_CLK_SRC_PLL1Q = LL_RCC_DAC6_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as DAC6 kernel clock */
  HAL_RCC_DAC6_CLK_SRC_PLL2Q = LL_RCC_DAC6_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as DAC6 kernel clock */
} hal_rcc_dac6_clk_src_t;

/**
  * @brief DAC7 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC7_CLK_SRC_TIM   = LL_RCC_DAC7_CLKSOURCE_TIM,   /*!< TIM selected as DAC7 kernel clock   */
  HAL_RCC_DAC7_CLK_SRC_HRTIM = LL_RCC_DAC7_CLKSOURCE_HRTIM, /*!< HRTIM selected as DAC7 kernel clock */
  HAL_RCC_DAC7_CLK_SRC_ADC   = LL_RCC_DAC7_CLKSOURCE_ADC,   /*!< ADC selected as DAC7 kernel clock   */
  HAL_RCC_DAC7_CLK_SRC_HSE   = LL_RCC_DAC7_CLKSOURCE_HSE,   /*!< HSE selected as DAC7 kernel clock   */
  HAL_RCC_DAC7_CLK_SRC_HSI   = LL_RCC_DAC7_CLKSOURCE_HSI,   /*!< HSI selected as DAC7 kernel clock   */
  HAL_RCC_DAC7_CLK_SRC_PLL1Q = LL_RCC_DAC7_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as DAC7 kernel clock */
  HAL_RCC_DAC7_CLK_SRC_PLL2Q = LL_RCC_DAC7_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as DAC7 kernel clock */
} hal_rcc_dac7_clk_src_t;

/**
  * @brief DAC8 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC8_CLK_SRC_TIM   = LL_RCC_DAC8_CLKSOURCE_TIM,   /*!< TIM selected as DAC8 kernel clock   */
  HAL_RCC_DAC8_CLK_SRC_HRTIM = LL_RCC_DAC8_CLKSOURCE_HRTIM, /*!< HRTIM selected as DAC8 kernel clock */
  HAL_RCC_DAC8_CLK_SRC_ADC   = LL_RCC_DAC8_CLKSOURCE_ADC,   /*!< ADC selected as DAC8 kernel clock   */
  HAL_RCC_DAC8_CLK_SRC_HSE   = LL_RCC_DAC8_CLKSOURCE_HSE,   /*!< HSE selected as DAC8 kernel clock   */
  HAL_RCC_DAC8_CLK_SRC_HSI   = LL_RCC_DAC8_CLKSOURCE_HSI,   /*!< HSI selected as DAC8 kernel clock   */
  HAL_RCC_DAC8_CLK_SRC_PLL1Q = LL_RCC_DAC8_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as DAC8 kernel clock */
  HAL_RCC_DAC8_CLK_SRC_PLL2Q = LL_RCC_DAC8_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as DAC8 kernel clock */
} hal_rcc_dac8_clk_src_t;

/**
  * @brief DAC9 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC9_CLK_SRC_TIM   = LL_RCC_DAC9_CLKSOURCE_TIM,   /*!< TIM selected as DAC9 kernel clock   */
  HAL_RCC_DAC9_CLK_SRC_HRTIM = LL_RCC_DAC9_CLKSOURCE_HRTIM, /*!< HRTIM selected as DAC9 kernel clock */
  HAL_RCC_DAC9_CLK_SRC_ADC   = LL_RCC_DAC9_CLKSOURCE_ADC,   /*!< ADC selected as DAC9 kernel clock   */
  HAL_RCC_DAC9_CLK_SRC_HSE   = LL_RCC_DAC9_CLKSOURCE_HSE,   /*!< HSE selected as DAC9 kernel clock   */
  HAL_RCC_DAC9_CLK_SRC_HSI   = LL_RCC_DAC9_CLKSOURCE_HSI,   /*!< HSI selected as DAC9 kernel clock   */
  HAL_RCC_DAC9_CLK_SRC_PLL1Q = LL_RCC_DAC9_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as DAC9 kernel clock */
  HAL_RCC_DAC9_CLK_SRC_PLL2Q = LL_RCC_DAC9_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as DAC9 kernel clock */
} hal_rcc_dac9_clk_src_t;

/**
  * @brief DAC10 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC10_CLK_SRC_TIM   = LL_RCC_DAC10_CLKSOURCE_TIM,   /*!< TIM selected as DAC10 kernel clock   */
  HAL_RCC_DAC10_CLK_SRC_HRTIM = LL_RCC_DAC10_CLKSOURCE_HRTIM, /*!< HRTIM selected as DAC10 kernel clock */
  HAL_RCC_DAC10_CLK_SRC_ADC   = LL_RCC_DAC10_CLKSOURCE_ADC,   /*!< ADC selected as DAC10 kernel clock   */
  HAL_RCC_DAC10_CLK_SRC_HSE   = LL_RCC_DAC10_CLKSOURCE_HSE,   /*!< HSE selected as DAC10 kernel clock   */
  HAL_RCC_DAC10_CLK_SRC_HSI   = LL_RCC_DAC10_CLKSOURCE_HSI,   /*!< HSI selected as DAC10 kernel clock   */
  HAL_RCC_DAC10_CLK_SRC_PLL1Q = LL_RCC_DAC10_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as DAC10 kernel clock */
  HAL_RCC_DAC10_CLK_SRC_PLL2Q = LL_RCC_DAC10_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as DAC10 kernel clock */
} hal_rcc_dac10_clk_src_t;

/**
  * @brief SPI1 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI1_CLK_SRC_PCLK2    = LL_RCC_SPI1_CLKSOURCE_PCLK2,    /*!< PCLK2 selected as SPI1 kernel clock    */
  HAL_RCC_SPI1_CLK_SRC_ICLK1    = LL_RCC_SPI1_CLKSOURCE_ICLK1,    /*!< ICLK1 selected as SPI1 kernel clock    */
  HAL_RCC_SPI1_CLK_SRC_PLL2P    = LL_RCC_SPI1_CLKSOURCE_PLL2P,    /*!< PLL2P selected as SPI1 kernel clock    */
  HAL_RCC_SPI1_CLK_SRC_HSE      = LL_RCC_SPI1_CLKSOURCE_HSE,      /*!< HSE selected as SPI1 kernel clock      */
  HAL_RCC_SPI1_CLK_SRC_HSI      = LL_RCC_SPI1_CLKSOURCE_HSI,      /*!< HSI selected as SPI1 kernel clock      */
  HAL_RCC_SPI1_CLK_SRC_AUDIOCLK = LL_RCC_SPI1_CLKSOURCE_AUDIOCLK, /*!< AUDIOCLK selected as SPI1 kernel clock */
} hal_rcc_spi1_clk_src_t;

/**
  * @brief SPI2 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI2_CLK_SRC_PCLK1    = LL_RCC_SPI2_CLKSOURCE_PCLK1,    /*!< PCLK1 selected as SPI2 kernel clock    */
  HAL_RCC_SPI2_CLK_SRC_ICLK1    = LL_RCC_SPI2_CLKSOURCE_ICLK1,    /*!< ICLK1 selected as SPI2 kernel clock    */
  HAL_RCC_SPI2_CLK_SRC_PLL2P    = LL_RCC_SPI2_CLKSOURCE_PLL2P,    /*!< PLL2P selected as SPI2 kernel clock    */
  HAL_RCC_SPI2_CLK_SRC_HSE      = LL_RCC_SPI2_CLKSOURCE_HSE,      /*!< HSE selected as SPI2 kernel clock      */
  HAL_RCC_SPI2_CLK_SRC_HSI      = LL_RCC_SPI2_CLKSOURCE_HSI,      /*!< HSI selected as SPI2 kernel clock      */
  HAL_RCC_SPI2_CLK_SRC_AUDIOCLK = LL_RCC_SPI2_CLKSOURCE_AUDIOCLK, /*!< AUDIOCLK selected as SPI2 kernel clock */
} hal_rcc_spi2_clk_src_t;

#if defined(SPI3)
/**
  * @brief SPI3 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI3_CLK_SRC_PCLK1 = LL_RCC_SPI3_CLKSOURCE_PCLK1, /*!< PCLK1 selected as SPI3 kernel clock */
  HAL_RCC_SPI3_CLK_SRC_ICLK1 = LL_RCC_SPI3_CLKSOURCE_ICLK1, /*!< ICLK1 selected as SPI3 kernel clock */
  HAL_RCC_SPI3_CLK_SRC_PLL2P = LL_RCC_SPI3_CLKSOURCE_PLL2P, /*!< PLL2P selected as SPI3 kernel clock */
  HAL_RCC_SPI3_CLK_SRC_HSE   = LL_RCC_SPI3_CLKSOURCE_HSE,   /*!< HSE selected as SPI3 kernel clock   */
  HAL_RCC_SPI3_CLK_SRC_HSI   = LL_RCC_SPI3_CLKSOURCE_HSI,   /*!< HSI selected as SPI3 kernel clock   */
} hal_rcc_spi3_clk_src_t;
#endif /* SPI3 */

#if defined(PLAY1)
/**
  * @brief PLAY1 Clock Source
  */
typedef enum
{
  HAL_RCC_PLAY1_CLK_SRC_LSE   = LL_RCC_PLAY1_CLKSOURCE_LSE,   /*!< LSE selected as PLAY1 kernel clock   */
  HAL_RCC_PLAY1_CLK_SRC_LSI   = LL_RCC_PLAY1_CLKSOURCE_LSI,   /*!< LSI selected as PLAY1 kernel clock   */
  HAL_RCC_PLAY1_CLK_SRC_PLL2P = LL_RCC_PLAY1_CLKSOURCE_PLL2P, /*!< PLL2P selected as PLAY1 kernel clock */
  HAL_RCC_PLAY1_CLK_SRC_HSE   = LL_RCC_PLAY1_CLKSOURCE_HSE,   /*!< HSE selected as PLAY1 kernel clock   */
  HAL_RCC_PLAY1_CLK_SRC_HSI   = LL_RCC_PLAY1_CLKSOURCE_HSI,   /*!< HSI selected as PLAY1 kernel clock   */
  HAL_RCC_PLAY1_CLK_SRC_HSI48 = LL_RCC_PLAY1_CLKSOURCE_HSI48, /*!< HSI48 selected as PLAY1 kernel clock */
} hal_rcc_play1_clk_src_t;

/**
  * @brief PLAY1 Clock divider
  */
typedef enum
{
  HAL_RCC_PLAY1_CLK_DIVIDER1     = LL_RCC_PLAY1_DIVIDER_1,     /*!< PLAY1 kernel clock source is not divided      */
  HAL_RCC_PLAY1_CLK_DIVIDER2     = LL_RCC_PLAY1_DIVIDER_2,     /*!< PLAY1 kernel clock source is divided by 2     */
  HAL_RCC_PLAY1_CLK_DIVIDER4     = LL_RCC_PLAY1_DIVIDER_4,     /*!< PLAY1 kernel clock source is divided by 4     */
  HAL_RCC_PLAY1_CLK_DIVIDER8     = LL_RCC_PLAY1_DIVIDER_8,     /*!< PLAY1 kernel clock source is divided by 8     */
  HAL_RCC_PLAY1_CLK_DIVIDER16    = LL_RCC_PLAY1_DIVIDER_16,    /*!< PLAY1 kernel clock source is divided by 16    */
  HAL_RCC_PLAY1_CLK_DIVIDER32    = LL_RCC_PLAY1_DIVIDER_32,    /*!< PLAY1 kernel clock source is divided by 32    */
  HAL_RCC_PLAY1_CLK_DIVIDER64    = LL_RCC_PLAY1_DIVIDER_64,    /*!< PLAY1 kernel clock source is divided by 64    */
  HAL_RCC_PLAY1_CLK_DIVIDER128   = LL_RCC_PLAY1_DIVIDER_128,   /*!< PLAY1 kernel clock source is divided by 128   */
  HAL_RCC_PLAY1_CLK_DIVIDER256   = LL_RCC_PLAY1_DIVIDER_256,   /*!< PLAY1 kernel clock source is divided by 256   */
  HAL_RCC_PLAY1_CLK_DIVIDER512   = LL_RCC_PLAY1_DIVIDER_512,   /*!< PLAY1 kernel clock source is divided by 512   */
  HAL_RCC_PLAY1_CLK_DIVIDER1024  = LL_RCC_PLAY1_DIVIDER_1024,  /*!< PLAY1 kernel clock source is divided by 1024  */
  HAL_RCC_PLAY1_CLK_DIVIDER2048  = LL_RCC_PLAY1_DIVIDER_2048,  /*!< PLAY1 kernel clock source is divided by 2048  */
  HAL_RCC_PLAY1_CLK_DIVIDER4096  = LL_RCC_PLAY1_DIVIDER_4096,  /*!< PLAY1 kernel clock source is divided by 4096  */
  HAL_RCC_PLAY1_CLK_DIVIDER8192  = LL_RCC_PLAY1_DIVIDER_8192,  /*!< PLAY1 kernel clock source is divided by 8192  */
  HAL_RCC_PLAY1_CLK_DIVIDER16384 = LL_RCC_PLAY1_DIVIDER_16384, /*!< PLAY1 kernel clock source is divided by 16384 */
  HAL_RCC_PLAY1_CLK_DIVIDER32768 = LL_RCC_PLAY1_DIVIDER_32768  /*!< PLAY1 kernel clock source is divided by 32768 */
} hal_rcc_play1_clk_divider_t;

#endif /* PLAY1 */

/**
  * @brief LPTIM1 Clock Source
  */
typedef enum
{
  HAL_RCC_LPTIM1_CLK_SRC_PCLK3 = LL_RCC_LPTIM1_CLKSOURCE_PCLK3, /*!< PCLK3 selected as LPTIM1 kernel clock */
  HAL_RCC_LPTIM1_CLK_SRC_PLL1Q = LL_RCC_LPTIM1_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as LPTIM1 kernel clock */
  HAL_RCC_LPTIM1_CLK_SRC_PLL2P = LL_RCC_LPTIM1_CLKSOURCE_PLL2P, /*!< PLL2P selected as LPTIM1 kernel clock */
  HAL_RCC_LPTIM1_CLK_SRC_HSE   = LL_RCC_LPTIM1_CLKSOURCE_HSE,   /*!< HSE selected as LPTIM1 kernel clock   */
  HAL_RCC_LPTIM1_CLK_SRC_HSI   = LL_RCC_LPTIM1_CLKSOURCE_HSI,   /*!< HSI selected as LPTIM1 kernel clock   */
  HAL_RCC_LPTIM1_CLK_SRC_LSI   = LL_RCC_LPTIM1_CLKSOURCE_LSI,   /*!< LSI selected as LPTIM1 kernel clock   */
  HAL_RCC_LPTIM1_CLK_SRC_LSE   = LL_RCC_LPTIM1_CLKSOURCE_LSE,   /*!< LSE selected as LPTIM1 kernel clock   */
} hal_rcc_lptim1_clk_src_t;

#if defined(XSPI1)
/**
  * @brief XSPI1 Clock Source
  */
typedef enum
{
  HAL_RCC_XSPI1_CLK_SRC_HCLK4 = LL_RCC_XSPI1_CLKSOURCE_HCLK4, /*!< HCLK4 selected as XSPI1 kernel clock */
  HAL_RCC_XSPI1_CLK_SRC_PLL1Q = LL_RCC_XSPI1_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as XSPI1 kernel clock */
  HAL_RCC_XSPI1_CLK_SRC_ICLK2 = LL_RCC_XSPI1_CLKSOURCE_ICLK2, /*!< ICLK2 selected as XSPI1 kernel clock */
  HAL_RCC_XSPI1_CLK_SRC_HSE   = LL_RCC_XSPI1_CLKSOURCE_HSE,   /*!< HSE selected as XSPI1 kernel clock   */
  HAL_RCC_XSPI1_CLK_SRC_HSI   = LL_RCC_XSPI1_CLKSOURCE_HSI,   /*!< HSI selected as XSPI1 kernel clock   */
} hal_rcc_xspi1_clk_src_t;
#endif /* XSPI1 */

#if defined(UCPD1)
/**
  * @brief UCPD1 Clock Source
  */
typedef enum
{
  HAL_RCC_UCPD1_CLK_SRC_HSI   = LL_RCC_UCPD1_CLKSOURCE_HSI,   /*!< HSI selected as UCPD1 kernel clock   */
  HAL_RCC_UCPD1_CLK_SRC_HSE   = LL_RCC_UCPD1_CLKSOURCE_HSE,   /*!< HSE selected as UCPD1 kernel clock   */
  HAL_RCC_UCPD1_CLK_SRC_HSI48 = LL_RCC_UCPD1_CLKSOURCE_HSI48, /*!< HSI48 selected as UCPD1 kernel clock */
  HAL_RCC_UCPD1_CLK_SRC_PLL2Q = LL_RCC_UCPD1_CLKSOURCE_PLL2Q  /*!< PLL2Q selected as UCPD1 kernel clock */
} hal_rcc_ucpd1_clk_src_t;
#endif /* UCPD1 */

#if defined(USB_DRD_FS)
/**
  * @brief USB Clock Source
  */
typedef enum
{
  HAL_RCC_USB_CLK_SRC_HSI48 = LL_RCC_USB_CLKSOURCE_HSI48, /*!< HSI48 selected as USB kernel clock */
  HAL_RCC_USB_CLK_SRC_HSE   = LL_RCC_USB_CLKSOURCE_HSE,   /*!< HSE selected as USB kernel clock   */
  HAL_RCC_USB_CLK_SRC_PLL1Q = LL_RCC_USB_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as USB kernel clock */
  HAL_RCC_USB_CLK_SRC_PLL2Q = LL_RCC_USB_CLKSOURCE_PLL2Q  /*!< PLL2Q selected as USB kernel clock */
} hal_rcc_usb_clk_src_t;
#endif /* USB_DRD_FS */

/**
  * @brief I3C1 Clock Source
  */
typedef enum
{
  HAL_RCC_I3C1_CLK_SRC_PCLK1 = LL_RCC_I3C1_CLKSOURCE_PCLK1, /*!< PCLK1 selected as I3C1 kernel clock */
  HAL_RCC_I3C1_CLK_SRC_ICLK1 = LL_RCC_I3C1_CLKSOURCE_ICLK1, /*!< ICLK1 selected as I3C1 kernel clock */
  HAL_RCC_I3C1_CLK_SRC_HSI   = LL_RCC_I3C1_CLKSOURCE_HSI,   /*!< HSI selected as I3C1 kernel clock   */
  HAL_RCC_I3C1_CLK_SRC_HSE   = LL_RCC_I3C1_CLKSOURCE_HSE,   /*!< HSE selected as I3C1 kernel clock   */
} hal_rcc_i3c1_clk_src_t;

/**
  * @brief I2C1 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C1_CLK_SRC_PCLK1 = LL_RCC_I2C1_CLKSOURCE_PCLK1, /*!< PCLK1 selected as I2C1 kernel clock */
  HAL_RCC_I2C1_CLK_SRC_ICLK1 = LL_RCC_I2C1_CLKSOURCE_ICLK1, /*!< ICLK1 selected as I2C1 kernel clock */
  HAL_RCC_I2C1_CLK_SRC_HSI   = LL_RCC_I2C1_CLKSOURCE_HSI,   /*!< HSI selected as I2C1 kernel clock   */
  HAL_RCC_I2C1_CLK_SRC_HSE   = LL_RCC_I2C1_CLKSOURCE_HSE,   /*!< HSE selected as I2C1 kernel clock   */
} hal_rcc_i2c1_clk_src_t;

/**
  * @brief I2C2 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C2_CLK_SRC_PCLK1 = LL_RCC_I2C2_CLKSOURCE_PCLK1, /*!< PCLK1 selected as I2C2 kernel clock */
  HAL_RCC_I2C2_CLK_SRC_ICLK1 = LL_RCC_I2C2_CLKSOURCE_ICLK1, /*!< ICLK1 selected as I2C2 kernel clock */
  HAL_RCC_I2C2_CLK_SRC_HSI   = LL_RCC_I2C2_CLKSOURCE_HSI,   /*!< HSI selected as I2C2 kernel clock   */
  HAL_RCC_I2C2_CLK_SRC_HSE   = LL_RCC_I2C2_CLKSOURCE_HSE,   /*!< HSE selected as I2C2 kernel clock   */
} hal_rcc_i2c2_clk_src_t;

#if defined(I2C3)
/**
  * @brief I2C3 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C3_CLK_SRC_PCLK3 = LL_RCC_I2C3_CLKSOURCE_PCLK3, /*!< PCLK3 selected as I2C3 kernel clock */
  HAL_RCC_I2C3_CLK_SRC_ICLK1 = LL_RCC_I2C3_CLKSOURCE_ICLK1, /*!< ICLK1 selected as I2C3 kernel clock */
  HAL_RCC_I2C3_CLK_SRC_HSI   = LL_RCC_I2C3_CLKSOURCE_HSI,   /*!< HSI selected as I2C3 kernel clock   */
  HAL_RCC_I2C3_CLK_SRC_HSE   = LL_RCC_I2C3_CLKSOURCE_HSE,   /*!< HSE selected as I2C3 kernel clock   */
  HAL_RCC_I2C3_CLK_SRC_HSI48 = LL_RCC_I2C3_CLKSOURCE_HSI48, /*!< HSI48 selected as I2C3 kernel clock */
} hal_rcc_i2c3_clk_src_t;
#endif /* I2C3 */

#if defined(I2C4)
/**
  * @brief I2C4 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C4_CLK_SRC_PCLK3 = LL_RCC_I2C4_CLKSOURCE_PCLK3, /*!< PCLK3 selected as I2C4 kernel clock */
  HAL_RCC_I2C4_CLK_SRC_ICLK1 = LL_RCC_I2C4_CLKSOURCE_ICLK1, /*!< ICLK1 selected as I2C4 kernel clock */
  HAL_RCC_I2C4_CLK_SRC_HSI   = LL_RCC_I2C4_CLKSOURCE_HSI,   /*!< HSI selected as I2C4 kernel clock   */
  HAL_RCC_I2C4_CLK_SRC_HSE   = LL_RCC_I2C4_CLKSOURCE_HSE,   /*!< HSE selected as I2C4 kernel clock   */
  HAL_RCC_I2C4_CLK_SRC_HSI48 = LL_RCC_I2C4_CLKSOURCE_HSI48, /*!< HSI48 selected as I2C4 kernel clock */
} hal_rcc_i2c4_clk_src_t;
#endif /* I2C4 */

/**
  * @brief ADC Clock Source
  */
typedef enum
{
  HAL_RCC_ADC_CLK_SRC_TIM   = LL_RCC_ADC_CLKSOURCE_TIM,   /*!< TIM selected as ADC kernel clock   */
  HAL_RCC_ADC_CLK_SRC_HRTIM = LL_RCC_ADC_CLKSOURCE_HRTIM, /*!< HRTIM selected as ADC kernel clock */
  HAL_RCC_ADC_CLK_SRC_HSI   = LL_RCC_ADC_CLKSOURCE_HSI,   /*!< HSI selected as ADC kernel clock   */
  HAL_RCC_ADC_CLK_SRC_HSE   = LL_RCC_ADC_CLKSOURCE_HSE,   /*!< HSE selected as ADC kernel clock   */
  HAL_RCC_ADC_CLK_SRC_PLL1Q = LL_RCC_ADC_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as ADC kernel clock */
  HAL_RCC_ADC_CLK_SRC_ICLK1 = LL_RCC_ADC_CLKSOURCE_ICLK1, /*!< ICLK1 selected as ADC kernel clock */
  HAL_RCC_ADC_CLK_SRC_PLL2P = LL_RCC_ADC_CLKSOURCE_PLL2P, /*!< PLL2P selected as ADC kernel clock */
  HAL_RCC_ADC_CLK_SRC_ICLK2 = LL_RCC_ADC_CLKSOURCE_ICLK2  /*!< ICLK2 selected as ADC kernel clock */
} hal_rcc_adc_clk_src_t;

/**
  * @brief ADC Clock Divider
  */
typedef enum
{
  HAL_RCC_ADC_PRESCALER1   = LL_RCC_ADC_PRESCALER_1,    /*!< ADC kernel clock is not divided    */
  HAL_RCC_ADC_PRESCALER2   = LL_RCC_ADC_PRESCALER_2,    /*!< ADC kernel clock is divided by 2   */
  HAL_RCC_ADC_PRESCALER4   = LL_RCC_ADC_PRESCALER_4,    /*!< ADC kernel clock is divided by 4   */
  HAL_RCC_ADC_PRESCALER6   = LL_RCC_ADC_PRESCALER_6,    /*!< ADC kernel clock is divided by 6   */
  HAL_RCC_ADC_PRESCALER8   = LL_RCC_ADC_PRESCALER_8,    /*!< ADC kernel clock is divided by 8   */
  HAL_RCC_ADC_PRESCALER10  = LL_RCC_ADC_PRESCALER_10,   /*!< ADC kernel clock is divided by 10  */
  HAL_RCC_ADC_PRESCALER12  = LL_RCC_ADC_PRESCALER_12,   /*!< ADC kernel clock is divided by 12  */
  HAL_RCC_ADC_PRESCALER16  = LL_RCC_ADC_PRESCALER_16,   /*!< ADC kernel clock is divided by 16  */
  HAL_RCC_ADC_PRESCALER32  = LL_RCC_ADC_PRESCALER_32,   /*!< ADC kernel clock is divided by 32  */
  HAL_RCC_ADC_PRESCALER64  = LL_RCC_ADC_PRESCALER_64,   /*!< ADC kernel clock is divided by 64  */
  HAL_RCC_ADC_PRESCALER128 = LL_RCC_ADC_PRESCALER_128,  /*!< ADC kernel clock is divided by 128 */
  HAL_RCC_ADC_PRESCALER256 = LL_RCC_ADC_PRESCALER_256   /*!< ADC kernel clock is divided by 256 */
} hal_rcc_adc_prescaler_t;

/**
  * @brief FDCAN Clock Source
  */
typedef enum
{
  HAL_RCC_FDCAN_CLK_SRC_HSE   = LL_RCC_FDCAN_CLKSOURCE_HSE,   /*!< HSE selected as FDCAN kernel clock   */
  HAL_RCC_FDCAN_CLK_SRC_PLL1Q = LL_RCC_FDCAN_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as FDCAN kernel clock */
  HAL_RCC_FDCAN_CLK_SRC_PLL2Q = LL_RCC_FDCAN_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as FDCAN kernel clock */
} hal_rcc_fdcan_clk_src_t;

#if defined(POSENC1)
/**
  * @brief POSENC1 Clock Source
  */
typedef enum
{
  HAL_RCC_POSENC1_CLK_SRC_PLL1P = LL_RCC_POSENC1_CLKSOURCE_PLL1P, /*!< PLL1P selected as POSENC1 kernel clock */
  HAL_RCC_POSENC1_CLK_SRC_PLL1Q = LL_RCC_POSENC1_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as POSENC1 kernel clock */
  HAL_RCC_POSENC1_CLK_SRC_ICLK1 = LL_RCC_POSENC1_CLKSOURCE_ICLK1, /*!< ICLK1 selected as POSENC1 kernel clock */
  HAL_RCC_POSENC1_CLK_SRC_PLL2P = LL_RCC_POSENC1_CLKSOURCE_PLL2P, /*!< PLL2P selected as POSENC1 kernel clock */
  HAL_RCC_POSENC1_CLK_SRC_PLL2Q = LL_RCC_POSENC1_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as POSENC1 kernel clock */
  HAL_RCC_POSENC1_CLK_SRC_ICLK2 = LL_RCC_POSENC1_CLKSOURCE_ICLK2, /*!< ICLK2 selected as POSENC1 kernel clock */
} hal_rcc_posenc1_clk_src_t;
#endif /* POSENC1 */

#if defined(POSENC2)
/**
  * @brief POSENC2 Clock Source
  */
typedef enum
{
  HAL_RCC_POSENC2_CLK_SRC_PLL1P = LL_RCC_POSENC2_CLKSOURCE_PLL1P, /*!< PLL1P selected as POSENC2 kernel clock */
  HAL_RCC_POSENC2_CLK_SRC_PLL1Q = LL_RCC_POSENC2_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as POSENC2 kernel clock */
  HAL_RCC_POSENC2_CLK_SRC_ICLK1 = LL_RCC_POSENC2_CLKSOURCE_ICLK1, /*!< ICLK1 selected as POSENC2 kernel clock */
  HAL_RCC_POSENC2_CLK_SRC_PLL2P = LL_RCC_POSENC2_CLKSOURCE_PLL2P, /*!< PLL2P selected as POSENC2 kernel clock */
  HAL_RCC_POSENC2_CLK_SRC_PLL2Q = LL_RCC_POSENC2_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as POSENC2 kernel clock */
  HAL_RCC_POSENC2_CLK_SRC_ICLK2 = LL_RCC_POSENC2_CLKSOURCE_ICLK2, /*!< ICLK2 selected as POSENC2 kernel clock */
} hal_rcc_posenc2_clk_src_t;
#endif /* POSENC2 */

/**
  * @}
  */


/** @defgroup RCC_Attributes RCC Attributes
  * @{
  */

/**
  * @brief Security access level attribute
  */
typedef enum
{
  HAL_RCC_NSEC = LL_RCC_ATTR_NSEC, /*!< Non-secure access level attribute */
  HAL_RCC_SEC  = LL_RCC_ATTR_SEC   /*!< Secure access level attribute     */
} hal_rcc_sec_attr_t;

/**
  * @brief Privileged access level attribute
  */
typedef enum
{
  HAL_RCC_NPRIV = LL_RCC_ATTR_NPRIV, /*!< Non-privileged access level attribute */
  HAL_RCC_PRIV  = LL_RCC_ATTR_PRIV   /*!< Privileged access level attribute     */
} hal_rcc_priv_attr_t;

/**
  * @brief RCC attributes configuration items
  */
#define HAL_RCC_SEC_ITEM_ALL               LL_RCC_SEC_ITEM_ALL            /*!< All RCC resources secure configuration item   */
#define HAL_RCC_SEC_ITEM_HSI               LL_RCC_SEC_ITEM_HSI            /*!< HSI clock secure configuration item           */
#define HAL_RCC_SEC_ITEM_HSE               LL_RCC_SEC_ITEM_HSE            /*!< HSE clock secure configuration item           */
#define HAL_RCC_SEC_ITEM_LSI               LL_RCC_SEC_ITEM_LSI            /*!< LSI clock secure configuration item           */
#define HAL_RCC_SEC_ITEM_LSE               LL_RCC_SEC_ITEM_LSE            /*!< LSE clock secure configuration item           */
#define HAL_RCC_SEC_ITEM_SYSCLK            LL_RCC_SEC_ITEM_SYSCLK         /*!< SYSCLK clock secure configuration item        */
#define HAL_RCC_SEC_ITEM_PRESCALERS        LL_RCC_SEC_ITEM_PRESCALERS     /*!< Prescalers secure configuration item          */
#define HAL_RCC_SEC_ITEM_PLL1              LL_RCC_SEC_ITEM_PLL1           /*!< PLL1 clock secure configuration item          */
#define HAL_RCC_SEC_ITEM_PLL2              LL_RCC_SEC_ITEM_PLL2           /*!< PLL2 clock secure configuration item          */
#define HAL_RCC_SEC_ITEM_HSI48             LL_RCC_SEC_ITEM_HSI48          /*!< HSI48 clock secure configuration item         */
#define HAL_RCC_SEC_ITEM_RESET_FLAGS       LL_RCC_SEC_ITEM_RESET_FLAGS    /*!< Remove reset flags secure configuration item  */

#define HAL_RCC_PRIV_ITEM_ALL              LL_RCC_PRIV_ITEM_ALL           /*!< All RCC secure and non-secure resources privilege configuration item */
#define HAL_RCC_PRIV_ITEM_SPRIV            LL_RCC_PRIV_ITEM_SPRIV         /*!< All RCC secure resources privilege configuration item                */
#define HAL_RCC_PRIV_ITEM_NSPRIV           LL_RCC_PRIV_ITEM_NSPRIV        /*!< All RCC non-secure resources privilege configuration item            */

/**
  * @}
  */


/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief RCC PLL configuration structure definition.
  * @note  VCO range is being calculated automatically in PLL configurations functions.
  */
typedef struct
{
  uint16_t pll_n;       /*!< PLLN: Multiplication factor for PLL VCO output clock.
                            This parameter must be a number between Min_Data = 4 and Max_Data = 512  */

  uint16_t pll_fracn;   /*!< PLLFRACN: Specifies Fractional Part Of The Multiplication Factor for
                            PLL1 VCO It must be a value between 0 and 8191                          */

  uint8_t pll_m;        /*!< PLLM: Division factor for PLL VCO input clock.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 63  */

  uint8_t pll_p;       /*!< PLLP: Division factor for peripheral clocks.
                            This parameter must be an even number between Min_Data = 2 and Max_Data = 128  */

  uint8_t pll_q;       /*!< PLLQ: Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 128  */

  uint8_t pll_r;       /*!< PLLR: Division factor for peripheral clock.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 128
                            For PLL1R, only division by 1 and even division factors are allowed.
                            (no such restriction in PLL2R and PLL3R)                                 */

  hal_rcc_pll_src_t pll_source; /*!< PLLSRC: PLL entry clock source                           */

  hal_rcc_pll_input_range_t pll_input_range; /*!< PLLRGE: PLL Input clock (ref_ck) range frequency (pll_source / pll_m).
                                                  This parameter must be a value of @ref hal_rcc_pll_input_range_t  */
  hal_rcc_pll_vco_range_t pll_vco_range ;    /*!< PLLVCO: PLL VCO clock range frequency (ref_ck * (pll_n + pll_fracn/8192)).
                                                This parameter must be a value of @ref hal_rcc_pll_vco_range_t  */

} hal_rcc_pll_config_t;

/**
  * @brief  RCC PLL Clocks structure definition
  */
typedef struct
{
  uint32_t pll_p_freq; /*!< PLLx outputP frequency */
  uint32_t pll_q_freq; /*!< PLLx outputQ frequency */
  uint32_t pll_r_freq; /*!< PLLx outputR frequency */
} hal_rcc_pll_output_freq_t;


/**
  * @brief  RCC System, AHB and APB buses clock configuration structure definition
  */
typedef struct
{
  hal_rcc_hclk_prescaler_t hclk_prescaler;  /*!< The HCLK (AHB clock) prescaler.
                                                 This clock is derived from the system clock (SYSCLK). */
  hal_rcc_pclk_prescaler_t pclk1_prescaler; /*!< The PCLK1 (APB1 clock) prescaler.
                                                 This clock is derived from the AHB clock (HCLK).      */
  hal_rcc_pclk_prescaler_t pclk2_prescaler; /*!< The PCLK2 (APB2 clock) prescaler.
                                                 This clock is derived from the AHB clock (HCLK).      */
  hal_rcc_pclk_prescaler_t pclk3_prescaler; /*!< The PCLK3 (APB3 clock) prescaler.
                                                 This clock is derived from the AHB clock (HCLK).      */
} hal_rcc_bus_clk_config_t;
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1 Oscillators, PLLs, Intermediate Clocks (ICLK), buses and reset functions
  This section provides functions allowing to configure the internal and external oscillators
  (HSE, HSI, HSI48, LSE, LSI), CSS, MCO and the System buses clocks (SYSCLK, AHB, APB1, APB2 and APB3).

  - Internal/external clock, PLL and Intermediate Clock (ICLK) configuration:
    - HSE (High-Speed External): crystal or clock, from 4 to 50 MHz, used as System clock source, as PLL input and as
    peripherals kernel clock. Optionally, it can also be used as RTC clock source.

    - HSI (High-Speed Internal): 64 MHz factory calibrated RC used as System clock source, as PLL input and as
    peripherals kernel clock. A predivider enables the application to select an output frequency of 8, 16, 32 or 64MHz.
    HSI is trimmable by application.

    - HSI48 (48 MHz Internal): 48 MHz factory calibrated RC used as peripherals kernel clock, in particular RNG and USB.
    HSI48 is trimmable by application through CRS.

    - LSE (Low-Speed External): 32.768 kHz oscillator used as peripherals kernel clock, in particular RTC, and for
    other timing functions.

    - LSI (Low-Speed Internal): 32 kHz very low-consumption RC oscillator mainly used as IWDG and/or RTC kernel clock.
    It can be also be selected for some peripherals as kernel clock.

    - PLL1 providing up to three independent output clocks (P, Q, R) used as main PLL (PLL1P) and as peripherals kernel
    clock (PLL1Q and PLL1R).

    - PLL2 providing up to three independent output clocks (P, Q, R) used as peripherals kernel clock.

    - ICLK1 and ICLK2 intermediate clocks, connected to PLL1R and PLL2R outputs though configurable dividers (3 or 5),
    used as peripherals kernel clock.

  - System, AHB and APB buses clocks configuration:
    - Several clock sources can be used to drive the System clock (SYSCLK): HSI, HSE or PLL1.
    The AHB clock (HCLK) is derived from System clock through configurable prescaler and is used to clock the CPU,
    memories and peripherals mapped on the AHB buses (e.g. DMA, GPIO...).
    The APB1 (PCLK1), APB2 (PCLK2) and APB3 (PCLK3) clocks are derived from the AHB clock through configurable
    prescalers and are used to clock the peripherals mapped on their respective buses.

    - All the peripheral default kernel clocks are derived from the System clock (SYSCLK) except for:

      - DACSH: kernel clock is either LSE (default) or LSI.
      - DTS: kernel clock is always the LSE clock.
      - FDCAN: kernel clock is derived from HSE (default) or PLLs.
      - IWDG: kernel clock is always the LSI clock.
      - PLAY: kernel clock is from LSE (default), LSI, PLL2P, HSE, HSI or HSI48.
      - POSENC: kernel clock is derived from PLL1P (default), PLL2P, PLLxQ or ICLKx.
      - RNG: it requires a frequency equal or lower than 48 MHz to work correctly. Kernel clock is derived
      from HSI48 (default) or from HSI divided by 2.
      - RTC and TAMP: kernel clock options are no clock (default), LSI, LSE or HSE clock divided by 2 to 63.
      - UCPD1: kernel clock is derived from HSI (default), HSE, HSI48 or PLL2Q.
      - USB: it requires a frequency equal to 48 MHz to work correctly. Kernel clock is derived from HSI48 (default),
      HSE or PLLxQ.

      For these peripherals, the kernel clock source must be activated.

    - The maximum frequency of the SYSCLK and HCLK is 280 MHz.
    - The maximum frequency of the PCLK1, PCLK2, PCLK3 is 140 MHz.

  - To correctly read data from Flash memory, the number of wait states (latency) must be correctly programmed
    in the FLASH register according to the frequency of the CPU clock (HCLK) and the internal voltage range
    of the device VCORE.

    When changing the CPU frequency, a software sequence must be applied in order to tune the number of wait states
    needed to access the FLASH memory:
    - FLASH latency must be increased before increasing the HCLK frequency
    - FLASH latency can be decreased only after decreasing the HCLK frequency

    The table below shows the correspondence between wait states and CPU clock frequency.

    Table 1. HCLK clock frequency (MHz) for devices depending on FLASH latency and voltage range  (VOS).

    |   Latency         |  VOS2 1.05V-1.15V  |  VOS1 1.15V-1.26V  |  VOS0 1.30V-1.40   |
    |-------------------|--------------------|--------------------|--------------------|
    | 0WS(1 CPU cycles) |   0 < HCLK <= 30   |   0 < HCLK <= 34   |   0 < HCLK <= 42   |
    | 1WS(2 CPU cycles) |  30 < HCLK <= 60   |  34 < HCLK <= 68   |  42 < HCLK <= 84   |
    | 2WS(3 CPU cycles) |  60 < HCLK <= 90   |  68 < HCLK <= 102  |  84 < HCLK <= 126  |
    | 3WS(4 CPU cycles) |  90 < HCLK <= 120  | 102 < HCLK <= 136  | 126 < HCLK <= 168  |
    | 4WS(5 CPU cycles) | 120 < HCLK <= 150  | 136 < HCLK <= 170  | 168 < HCLK <= 210  |
    | 5WS(6 CPU cycles) |        NA          | 170 < HCLK <= 204  | 210 < HCLK <= 255  |
    | 6WS(7 CPU cycles) |        NA          | 204 < HCLK <= 220  | 255 < HCLK <= 280  |

  - Reset functions:

    - Reset the RCC clock configuration to the default system clock (HSI at 64Mhz).
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1_0 Reset System clock to default function
  * @brief    Functions to reset the system clock to HSI (64Mhz)
  * @{
  */

void         HAL_RCC_Reset(void);
hal_status_t HAL_RCC_ResetSystemClock(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_1 RCC oscillators config service
  * @brief    Functions to configure the different oscillators and the main PLL.
  * @note     The following functions configure and activate the different oscillators.
  *           Configuration can be done:
  *           - using the atomic functions defined for each oscillators and PLL
  *             -# like HAL_RCC_{OSC}_Enable: {OSC} is HSE/LSE/HSI/HSI48/LSI
  *           - atomic function used for main PLL is described in the @ref RCC_Exported_Functions_Group1_5
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
hal_status_t                HAL_RCC_HSE_Enable(hal_rcc_hse_t mode);
hal_status_t                HAL_RCC_HSE_Enable_IT(hal_rcc_hse_t mode);
hal_status_t                HAL_RCC_HSE_Disable(void);
hal_rcc_osc_enable_status_t HAL_RCC_HSE_IsEnabled(void);
hal_rcc_osc_ready_status_t  HAL_RCC_HSE_IsReady(void);
void                        HAL_RCC_HSE_ReadyCallback(void);
#endif /* HSE_VALUE */

#if defined(LSE_VALUE)
/* LSE oscillator configuration and activation    ******************************/
hal_status_t                HAL_RCC_LSE_Enable(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive);
hal_status_t                HAL_RCC_LSE_Enable_IT(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive);
hal_status_t                HAL_RCC_LSE_Disable(void);
hal_rcc_osc_enable_status_t HAL_RCC_LSE_IsEnabled(void);
hal_rcc_osc_ready_status_t  HAL_RCC_LSE_IsReady(void);
void                        HAL_RCC_LSE_ReadyCallback(void);
#endif /* LSE_VALUE */

/* HSI oscillator configuration and activation    ******************************/
hal_status_t                   HAL_RCC_HSI_Enable(hal_rcc_hsi_div_t divider);
hal_status_t                   HAL_RCC_HSI_Enable_IT(hal_rcc_hsi_div_t divider);
hal_status_t                   HAL_RCC_HSI_Disable(void);
hal_rcc_osc_enable_status_t    HAL_RCC_HSI_IsEnabled(void);
hal_rcc_osc_ready_status_t     HAL_RCC_HSI_IsReady(void);
void                           HAL_RCC_HSI_ReadyCallback(void);
hal_status_t                   HAL_RCC_HSI_EnableInStopMode(void);
hal_status_t                   HAL_RCC_HSI_DisableInStopMode(void);
hal_rcc_osc_stop_mode_status_t HAL_RCC_HSI_IsEnabledInStopMode(void);
void                           HAL_RCC_HSI_SetTrimming(uint32_t value);
uint32_t                       HAL_RCC_HSI_GetTrimming(void);
uint32_t                       HAL_RCC_HSI_GetCalibration(void);

#if defined(HSI48)
/* HSI48 oscillator configuration and activation    ******************************/
hal_status_t                HAL_RCC_HSI48_Enable(void);
hal_status_t                HAL_RCC_HSI48_Enable_IT(void);
hal_status_t                HAL_RCC_HSI48_Disable(void);
hal_rcc_osc_enable_status_t HAL_RCC_HSI48_IsEnabled(void);
hal_rcc_osc_ready_status_t  HAL_RCC_HSI48_IsReady(void);
void                        HAL_RCC_HSI48_ReadyCallback(void);
uint32_t                    HAL_RCC_HSI48_GetCalibration(void);
#endif /* HSI48 */

/* LSI oscillator configuration and activation    ******************************/
hal_status_t                HAL_RCC_LSI_Enable(void);
hal_status_t                HAL_RCC_LSI_Enable_IT(void);
hal_status_t                HAL_RCC_LSI_Disable(void);
hal_rcc_osc_enable_status_t HAL_RCC_LSI_IsEnabled(void);
hal_rcc_osc_ready_status_t  HAL_RCC_LSI_IsReady(void);
void                        HAL_RCC_LSI_ReadyCallback(void);

/* RCC general interrupt request handler    ***********************************/
void            HAL_RCC_IRQHandler(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_2 RCC clock config service
  * @brief    Functions to configure the bus prescalers and retrieve bus clock frequencies (SYSCLK, HCLK and PCLKx).
  * @note     Unitary functions can be used to configure independently each bus.
  *
  *           example: all the BUS prescalers are set
  *
  *           - Call the global @ref HAL_RCC_SetBusClockConfig
  *             @code
  *               LL_FLASH_SetLatency(LL_FLASH_LATENCY_4WS);
  *               HAL_RCC_SetSYSCLKSource(HAL_RCC_SYSCLK_SRC_HSE);
  *               hal_rcc_bus_clk_config_t config_bus;
  *               config_bus.hclk_prescaler  = HAL_RCC_HCLK_PRESCALER1;
  *               config_bus.pclk1_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               config_bus.pclk2_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               config_bus.pclk3_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               HAL_RCC_SetBusClockConfig(&config_bus);
  *             @endcode
  * @{
  */
hal_status_t          HAL_RCC_SetSYSCLKSource(hal_rcc_sysclk_src_t source);
hal_rcc_sysclk_src_t  HAL_RCC_GetSYSCLKSource(void);
void                  HAL_RCC_SetHCLKPrescaler(hal_rcc_hclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK1Prescaler(hal_rcc_pclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK2Prescaler(hal_rcc_pclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK3Prescaler(hal_rcc_pclk_prescaler_t prescaler);
hal_rcc_hclk_prescaler_t    HAL_RCC_GetHCLKPrescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK1Prescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK2Prescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK3Prescaler(void);

hal_status_t          HAL_RCC_SetBusClockConfig(const hal_rcc_bus_clk_config_t *p_config);
void                  HAL_RCC_GetBusClockConfig(hal_rcc_bus_clk_config_t *p_config);
uint32_t              HAL_RCC_GetSYSCLKFreq(void);
uint32_t              HAL_RCC_GetHCLKFreq(void);
uint32_t              HAL_RCC_GetPCLK1Freq(void);
uint32_t              HAL_RCC_GetPCLK2Freq(void);
uint32_t              HAL_RCC_GetPCLK3Freq(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_3 RCC management of Systick external clock source
  * @brief    Functions to Set, Get the Systick external clock source and frequency.
  * @{
  */
void                       HAL_RCC_SetSysTickExternalClkSource(hal_rcc_systick_clk_src_t clk_src);
hal_rcc_systick_clk_src_t  HAL_RCC_GetSysTickExternalClkSource(void);
uint32_t                   HAL_RCC_GetSysTickExternalClkFreq(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_4 ICLK configuration
  * This subsection provides a set of functions:
  - to configure any Intermediate Clock (ICLKx) divider.
  - to get the configuration of any ICLKx
  * @{
  */
void                  HAL_RCC_ICLK_SetDivider(hal_rcc_iclk_t iclkx, hal_rcc_iclk_div_t iclk_divider);
hal_rcc_iclk_div_t    HAL_RCC_ICLK_GetDivider(hal_rcc_iclk_t iclkx);
/**
  * @}
  */


/** @defgroup RCC_Exported_Functions_Group1_5 RCC management of PLL1
  * @brief    Functions to configure the different PLL1.
  * @details  PLL1 (main PLL) might be used for system clock.
  *           PLL1 is configured and enabled respectively with HAL_RCC_PLL1_SetConfig() and HAL_RCC_PLL1_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL1.
  *
  *           example1: activation main PLL
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_HSI_Enable(HAL_RCC_HSI_DIV2);
  *               HAL_RCC_HSI_SetTrimming(HAL_RCC_HSICALIBRATION_DEFAULT);
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_HSI;
  *               config_pll.pll_m = 8;
  *               config_pll.pll_n = 125;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2;
  *               config_pll.pll_input_range = HAL_RCC_PLL_INPUT_RANGE_2_4;
  *               config_pll.pll_vco_range = HAL_RCC_PLL_VCO_RANGE_128_560;
  *               HAL_RCC_PLL1_SetConfig(&config_pll);
  *               HAL_RCC_PLL1_Enable();
  *               HAL_RCC_PLL1_EnableOutput(HAL_RCC_PLL1_SYSCLK);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL1_SetConfig(const hal_rcc_pll_config_t *p_config);
void                  HAL_RCC_PLL1_GetConfig(hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL1_SetFRACN(uint16_t fracn);
uint16_t              HAL_RCC_PLL1_GetFRACN(void);
hal_status_t          HAL_RCC_PLL1_Enable(void);
hal_status_t          HAL_RCC_PLL1_Enable_IT(void);
hal_status_t          HAL_RCC_PLL1_Disable(void);
hal_rcc_pll_status_t  HAL_RCC_PLL1_IsReady(void);
void                  HAL_RCC_PLL1_ReadyCallback(void);
hal_status_t          HAL_RCC_PLL1_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL1_DisableOutput(uint32_t output);
uint32_t              HAL_RCC_PLL1_GetOutput(void);
hal_status_t          HAL_RCC_PLL1_Reset(void);
void                  HAL_RCC_PLL1_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);

/**
  * @}
  */

#if defined(PLL2)
/** @defgroup RCC_Exported_Functions_Group1_6 RCC management of PLL2
  * @brief    Functions to configure the different PLL2
  * @details  PLL2 is configured and enabled respectively with HAL_RCC_PLL2_SetConfig() and HAL_RCC_PLL2_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL2.
  *
  *           example1: activation PLL2 only
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_HSE_Enable(HAL_RCC_HSE_ON);
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_HSE;
  *               config_pll.pll_m = 4;
  *               config_pll.pll_n = 75;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2;
  *               config_pll.pll_input_range = HAL_RCC_PLL_INPUT_RANGE_2_4;
  *               config_pll.pll_vco_range = HAL_RCC_PLL_VCO_RANGE_128_560;
  *               HAL_RCC_PLL2_SetConfig(&config_pll);
  *               HAL_RCC_PLL2_Enable();
  *               HAL_RCC_PLL2_EnableOutput(HAL_RCC_PLL2_OUTPUT_P);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL2_SetConfig(const hal_rcc_pll_config_t *p_config);
void                  HAL_RCC_PLL2_GetConfig(hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL2_SetFRACN(uint16_t fracn);
uint16_t              HAL_RCC_PLL2_GetFRACN(void);
hal_status_t          HAL_RCC_PLL2_Enable(void);
hal_status_t          HAL_RCC_PLL2_Enable_IT(void);
hal_status_t          HAL_RCC_PLL2_Disable(void);
hal_rcc_pll_status_t  HAL_RCC_PLL2_IsReady(void);
void                  HAL_RCC_PLL2_ReadyCallback(void);
hal_status_t          HAL_RCC_PLL2_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL2_DisableOutput(uint32_t output);
uint32_t              HAL_RCC_PLL2_GetOutput(void);
hal_status_t          HAL_RCC_PLL2_Reset(void);
void                  HAL_RCC_PLL2_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);

/**
  * @}
  */
#endif /* PLL2 */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group2 Peripheral Clock management on buses
  This subsection provides a set of functions (on AHB1, AHB2, AHB3, AHB4, APB1, APB1, APB2 or APB3 buses) allowing to:

  - Enable and disable bus clocks.
  - Enable or disable the peripherals bus clock.
  - Reset of peripherals clock.
  - Enable or disable the peripherals clock in low power mode.
  * @{
  */

/** @defgroup RCC_Bus_Clock_Enable_Disable Bus Clock Enable Disable
  * @brief  Enable or disable the Bus peripheral clocks.
  * @{
  */

/**
  * @details This function enables the AHB1 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_AHB1_EnableBusClock(void)
{
  LL_AHB1_EnableBusClock();
}

/**
  * @details This function checks if AHB1 bus clock is enabled.
  * @retval  HAL_RCC_CLK_DISABLED AHB1 bus clock is disabled
  * @retval  HAL_RCC_CLK_ENABLED AHB1 bus clock is enabled
  */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AHB1_IsEnabledBusClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_IsEnabledBusClock();
}

/**
  * @details This function disables the AHB1 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_AHB1_DisableBusClock(void)
{
  LL_AHB1_DisableBusClock();
}

/**
  * @details This function enables the AHB2 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_AHB2_EnableBusClock(void)
{
  LL_AHB2_EnableBusClock();
}

/**
  * @details This function checks if AHB2 bus clock is enabled.
  * @retval  HAL_RCC_CLK_DISABLED AHB2 bus clock is disabled
  * @retval  HAL_RCC_CLK_ENABLED AHB2 bus clock is enabled
  */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AHB2_IsEnabledBusClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_IsEnabledBusClock();
}

/**
  * @details This function disables the AHB2 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_AHB2_DisableBusClock(void)
{
  LL_AHB2_DisableBusClock();
}

/**
  * @details This function enables the AHB3 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_AHB3_EnableBusClock(void)
{
  LL_AHB3_EnableBusClock();
}

/**
  * @details This function checks if AHB3 bus clock is enabled.
  * @retval  HAL_RCC_CLK_DISABLED AHB3 bus clock is disabled
  * @retval  HAL_RCC_CLK_ENABLED AHB3 bus clock is enabled
  */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AHB3_IsEnabledBusClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_IsEnabledBusClock();
}

/**
  * @details This function disables the AHB3 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_AHB3_DisableBusClock(void)
{
  LL_AHB3_DisableBusClock();
}

/**
  * @details This function enables the AHB4 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_AHB4_EnableBusClock(void)
{
  LL_AHB4_EnableBusClock();
}

/**
  * @details This function checks if AHB4 bus clock is enabled.
  * @retval  HAL_RCC_CLK_DISABLED AHB4 bus clock is disabled
  * @retval  HAL_RCC_CLK_ENABLED AHB4 bus clock is enabled
  */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AHB4_IsEnabledBusClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_IsEnabledBusClock();
}

/**
  * @details This function disables the AHB4 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_AHB4_DisableBusClock(void)
{
  LL_AHB4_DisableBusClock();
}

/**
  * @details This function enables the APB1 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_APB1_EnableBusClock(void)
{
  LL_APB1_EnableBusClock();
}

/**
  * @details This function checks if APB1 bus clock is enabled.
  * @retval  HAL_RCC_CLK_DISABLED APB1 bus clock is disabled
  * @retval  HAL_RCC_CLK_ENABLED APB1 bus clock is enabled
  */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_APB1_IsEnabledBusClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_IsEnabledBusClock();
}

/**
  * @details This function disables the APB1 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_APB1_DisableBusClock(void)
{
  LL_APB1_DisableBusClock();
}

/**
  * @details This function enables the APB2 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_APB2_EnableBusClock(void)
{
  LL_APB2_EnableBusClock();
}

/**
  * @details This function checks if APB2 bus clock is enabled.
  * @retval  HAL_RCC_CLK_DISABLED APB2 bus clock is disabled
  * @retval  HAL_RCC_CLK_ENABLED APB2 bus clock is enabled
  */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_APB2_IsEnabledBusClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_IsEnabledBusClock();
}

/**
  * @details This function disables the APB2 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_APB2_DisableBusClock(void)
{
  LL_APB2_DisableBusClock();
}

/**
  * @details This function enables the APB3 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_APB3_EnableBusClock(void)
{
  LL_APB3_EnableBusClock();
}

/**
  * @details This function checks if APB3 bus clock is enabled.
  * @retval  HAL_RCC_CLK_DISABLED APB3 bus clock is disabled
  * @retval  HAL_RCC_CLK_ENABLED APB3 bus clock is enabled
  */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_APB3_IsEnabledBusClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_IsEnabledBusClock();
}

/**
  * @details This function disables the APB3 Bus clock.
  */
__STATIC_INLINE void HAL_RCC_APB3_DisableBusClock(void)
{
  LL_APB3_DisableBusClock();
}
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Disable AHB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the GPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the GPDMA2 clock.
  */
__STATIC_INLINE void HAL_RCC_GPDMA2_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPDMA2);
}

/**
  * @details This function enables the FLASH clock.
  */
__STATIC_INLINE void HAL_RCC_FLASH_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_FLASH);
}

/**
  * @details This function enables the CRC clock.
  */
__STATIC_INLINE void HAL_RCC_CRC_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_CRC);
}

/**
  * @details This function enables the CORDIC1 clock.
  */
__STATIC_INLINE void HAL_RCC_CORDIC1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_CORDIC1);
}

/**
  * @details This function enables the FMAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_FMAC1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function enables the RAMCFG clock.
  */
__STATIC_INLINE void HAL_RCC_RAMCFG_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

/**
  * @details This function enables the TZSC1 clock.
  */
__STATIC_INLINE void HAL_RCC_TZSC1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_TZSC1);
}

/**
  * @details This function enables the SRAM2 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM2_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_SRAM2);
}

#if defined(SRAM3_BASE)
/**
  * @details This function enables the SRAM3 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM3_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_SRAM3);
}
#endif /* SRAM3_BASE */

#if defined(DCACHE)
/**
  * @details This function enables the DCACHE clock.
  */
__STATIC_INLINE void HAL_RCC_DCACHE_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DCACHE);
}
#endif /* DCACHE */

/**
  * @details This function enables the SRAM1 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_SRAM1);
}

/**
  * @details This function disables the GPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function disables the GPDMA2 clock.
  */
__STATIC_INLINE void HAL_RCC_GPDMA2_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPDMA2);
}

/**
  * @details This function disables the FLASH clock.
  */
__STATIC_INLINE void HAL_RCC_FLASH_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_FLASH);
}

/**
  * @details This function disables the CRC clock.
  */
__STATIC_INLINE void HAL_RCC_CRC_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_CRC);
}

/**
  * @details This function disables the CORDIC1 clock.
  */
__STATIC_INLINE void HAL_RCC_CORDIC1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_CORDIC1);
}

/**
  * @details This function disables the FMAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_FMAC1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function disables the RAMCFG clock.
  */
__STATIC_INLINE void HAL_RCC_RAMCFG_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

/**
  * @details This function disables the TZSC1 clock.
  */
__STATIC_INLINE void HAL_RCC_TZSC1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_TZSC1);
}

/**
  * @details This function disables the SRAM2 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM2_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_SRAM2);
}

#if defined(SRAM3_BASE)
/**
  * @details This function disables the SRAM3 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM3_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_SRAM3);
}
#endif /* SRAM3_BASE */

#if defined(DCACHE)
/**
  * @details This function disables the DCACHE clock.
  */
__STATIC_INLINE void HAL_RCC_DCACHE_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DCACHE);
}
#endif /* DCACHE */

/**
  * @details This function disables the SRAM1 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_SRAM1);
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
  * @details This function enables the DAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC1_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the DAC2 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC2_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC2);
}

/**
  * @details This function enables the DAC5 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC5_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC5);
}

/**
  * @details This function enables the DAC6 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC6_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC6);
}

/**
  * @details This function enables the DAC7 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC7_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC7);
}

/**
  * @details This function enables the DAC8 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC8_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC8);
}

/**
  * @details This function enables the DAC9 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC9_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC9);
}

/**
  * @details This function enables the DAC10 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC10_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC10);
}

#if defined(FMAC2)
/**
  * @details This function enables the FMAC2 clock.
  */
__STATIC_INLINE void HAL_RCC_FMAC2_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_FMAC2);
}
#endif /* FMAC2 */

/**
  * @details This function enables the ADC12 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC12_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC12);
}

#if defined(ADC3)
/**
  * @details This function enables the ADC3 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC3_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC3);
}
#endif /* ADC3 */

/**
  * @details This function disables the DAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC1_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the DAC2 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC2_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_DAC2);
}

/**
  * @details This function disables the DAC5 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC5_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_DAC5);
}

/**
  * @details This function disables the DAC6 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC6_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_DAC6);
}

/**
  * @details This function disables the DAC7 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC7_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_DAC7);
}

/**
  * @details This function disables the DAC8 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC8_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_DAC8);
}

/**
  * @details This function disables the DAC9 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC9_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_DAC9);
}

/**
  * @details This function disables the DAC10 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC10_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_DAC10);
}

#if defined(FMAC2)
/**
  * @details This function disables the FMAC2 clock.
  */
__STATIC_INLINE void HAL_RCC_FMAC2_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_FMAC2);
}
#endif /* FMAC2 */

/**
  * @details This function disables the ADC12 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC12_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_ADC12);
}

#if defined(ADC3)
/**
  * @details This function disables the ADC3 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC3_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_ADC3);
}
#endif /* ADC3 */

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
  * @details This function enables the DBG clock.
  */
__STATIC_INLINE void HAL_RCC_DBG_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_DBG);
}

/**
  * @details This function disables the DBG clock.
  */
__STATIC_INLINE void HAL_RCC_DBG_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_DBG);
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

#if defined(AES)
/**
  * @details This function enables the AES clock.
  */
__STATIC_INLINE void HAL_RCC_AES_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_AES);
}
#endif /* AES */

/**
  * @details This function enables the HASH clock.
  */
__STATIC_INLINE void HAL_RCC_HASH_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_HASH);
}

/**
  * @details This function enables the RNG clock.
  */
__STATIC_INLINE void HAL_RCC_RNG_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_RNG);
}

/**
  * @details This function enables the PKA clock.
  */
__STATIC_INLINE void HAL_RCC_PKA_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_PKA);
}

#if defined(SAES)
/**
  * @details This function enables the SAES clock.
  */
__STATIC_INLINE void HAL_RCC_SAES_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined(CCB)
/**
  * @details This function enables the CCB clock.
  */
__STATIC_INLINE void HAL_RCC_CCB_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_CCB);
}
#endif /* CCB */

#if defined(OTFDEC1)
/**
  * @details This function enables the OTFDEC1 clock.
  */
__STATIC_INLINE void HAL_RCC_OTFDEC1_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

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

#if defined(XSPI1)
/**
  * @details This function enables the XSPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_XSPI1);
}
#endif /* XSPI1 */

#if defined(AES)
/**
  * @details This function disables the AES clock.
  */
__STATIC_INLINE void HAL_RCC_AES_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_AES);
}
#endif /* AES */

/**
  * @details This function disables the HASH clock.
  */
__STATIC_INLINE void HAL_RCC_HASH_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_HASH);
}

/**
  * @details This function disables the RNG clock.
  */
__STATIC_INLINE void HAL_RCC_RNG_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_RNG);
}

/**
  * @details This function disables the PKA clock.
  */
__STATIC_INLINE void HAL_RCC_PKA_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_PKA);
}

#if defined(SAES)
/**
  * @details This function disables the SAES clock.
  */
__STATIC_INLINE void HAL_RCC_SAES_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined(CCB)
/**
  * @details This function disables the CCB clock.
  */
__STATIC_INLINE void HAL_RCC_CCB_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_CCB);
}
#endif /* CCB */

#if defined(OTFDEC1)
/**
  * @details This function disables the OTFDEC1 clock.
  */
__STATIC_INLINE void HAL_RCC_OTFDEC1_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

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

#if defined(XSPI1)
/**
  * @details This function disables the XSPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_XSPI1);
}
#endif /* XSPI1 */

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

#if defined(TIM3)
/**
  * @details This function enables the TIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
}
#endif /* TIM3 */

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
  * @details This function enables the TIM9 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM9_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM9);
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
  * @details This function enables the WWDG clock.
  */
__STATIC_INLINE void HAL_RCC_WWDG_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function enables the SPI2 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
}

#if defined(SPI3)
/**
  * @details This function enables the SPI3 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
}
#endif /* SPI3 */

/**
  * @details This function enables the USART2 clock.
  */
__STATIC_INLINE void HAL_RCC_USART2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
}

#if defined(USART3)
/**
  * @details This function enables the USART3 clock.
  */
__STATIC_INLINE void HAL_RCC_USART3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
}
#endif /* USART3 */

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
  * @details This function enables the I3C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I3C1_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I3C1);
}

#if defined(CRS)
/**
  * @details This function enables the CRS clock.
  */
__STATIC_INLINE void HAL_RCC_CRS_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_CRS);
}
#endif /* CRS */

/**
  * @details This function enables the UART6 clock.
  */
__STATIC_INLINE void HAL_RCC_UART6_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART6);
}

/**
  * @details This function disables the TIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2);
}

#if defined(TIM3)
/**
  * @details This function disables the TIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM3);
}
#endif /* TIM3 */

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
  * @details This function disables the TIM9 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM9_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM9);
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
  * @details This function disables the SPI2 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2);
}

#if defined(SPI3)
/**
  * @details This function disables the SPI3 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI3);
}
#endif /* SPI3 */

/**
  * @details This function disables the USART2 clock.
  */
__STATIC_INLINE void HAL_RCC_USART2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
}

#if defined(USART3)
/**
  * @details This function disables the USART3 clock.
  */
__STATIC_INLINE void HAL_RCC_USART3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
}
#endif /* USART3 */

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
  * @details This function disables the I3C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I3C1_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I3C1);
}

#if defined(CRS)
/**
  * @details This function disables the CRS clock.
  */
__STATIC_INLINE void HAL_RCC_CRS_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_CRS);
}
#endif /* CRS */

/**
  * @details This function disables the UART6 clock.
  */
__STATIC_INLINE void HAL_RCC_UART6_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART6);
}

/**
  * @details This function enables the DTS clock.
  */
__STATIC_INLINE void HAL_RCC_DTS_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_DTS);
}

/**
  * @details This function enables the FDCAN clock.
  * @note    The FDCAN clock is common for all FDCAN instances
  */
__STATIC_INLINE void HAL_RCC_FDCAN_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_FDCAN);
}

#if defined(UCPD1)
/**
  * @details This function enables the UCPD1 clock.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_UCPD1);
}
#endif /* UCPD1 */

/**
  * @details This function disables the DTS clock.
  */
__STATIC_INLINE void HAL_RCC_DTS_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_DTS);
}

/**
  * @details This function disables the FDCAN clock.
  * @note    The FDCAN clock is common for all FDCAN instances
  */
__STATIC_INLINE void HAL_RCC_FDCAN_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_FDCAN);
}

#if defined(UCPD1)
/**
  * @details This function disables the UCPD1 clock.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_UCPD1);
}
#endif /* UCPD1 */

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Enable_Disable APB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

#if defined(HRTIM1)
/**
  * @details This function enables the HRTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_HRTIM1);
}
#endif /* HRTIM1 */

#if defined(PLAY1)
/**
  * @details This function enables the PLAY1APB clock.
  */
__STATIC_INLINE void HAL_RCC_PLAY1APB_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_PLAY1APB);
}

/**
  * @details This function enables the PLAY1 clock.
  */
__STATIC_INLINE void HAL_RCC_PLAY1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_PLAY1);
}
#endif /* PLAY1 */

/**
  * @details This function enables the TIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function enables the SPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function enables the TIM8 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM8_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function enables the USART1 clock.
  */
__STATIC_INLINE void HAL_RCC_USART1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
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

#if defined(USB_DRD_FS)
/**
  * @details This function enables the USB clock.
  */
__STATIC_INLINE void HAL_RCC_USB_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USB);
}
#endif /* USB_DRD_FS */

#if defined(TIM4)
/**
  * @details This function enables the TIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM4_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM4);
}
#endif /* TIM4 */

#if defined(TIM5)
/**
  * @details This function enables the TIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM5_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM5);
}
#endif /* TIM5 */

#if defined(HRTIM1)
/**
  * @details This function disables the HRTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_HRTIM1);
}
#endif /* HRTIM1 */

#if defined(PLAY1)
/**
  * @details This function disables the PLAY1APB clock.
  */
__STATIC_INLINE void HAL_RCC_PLAY1APB_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_PLAY1APB);
}

/**
  * @details This function disables the PLAY1 clock.
  */
__STATIC_INLINE void HAL_RCC_PLAY1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_PLAY1);
}
#endif /* PLAY1 */

/**
  * @details This function disables the TIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function disables the SPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function disables the TIM8 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM8_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function disables the USART1 clock.
  */
__STATIC_INLINE void HAL_RCC_USART1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
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

#if defined(USB_DRD_FS)
/**
  * @details This function disables the USB clock.
  */
__STATIC_INLINE void HAL_RCC_USB_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USB);
}
#endif /* USB_DRD_FS */

#if defined(TIM4)
/**
  * @details This function disables the TIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM4_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM4);
}
#endif /* TIM4 */

#if defined(TIM5)
/**
  * @details This function disables the TIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM5_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM5);
}
#endif /* TIM5 */

/**
  * @}
  */

/** @defgroup RCC_APB3_Peripheral_Clock_Enable_Disable APB3 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB3 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the SBS clock.
  */
__STATIC_INLINE void HAL_RCC_SBS_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_SBS);
}

#if defined(TIM20)
/**
  * @details This function enables the TIM20 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM20_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_TIM20);
}
#endif /* TIM20 */

/**
  * @details This function enables the TIM26 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM26_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_TIM26);
}

/**
  * @details This function enables the TIM27 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM27_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_TIM27);
}

/**
  * @details This function enables the LPUART1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_LPUART1);
}

#if defined(I2C3)
/**
  * @details This function enables the I2C3 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C3_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_I2C3);
}
#endif /* I2C3 */

#if defined(I2C4)
/**
  * @details This function enables the I2C4 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C4_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_I2C4);
}
#endif /* I2C4 */

/**
  * @details This function enables the LPTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_LPTIM1);
}

#if defined(POSENC1)
/**
  * @details This function enables the POSENC1 clock.
  */
__STATIC_INLINE void HAL_RCC_POSENC1_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_POSENC1);
}
#endif /* POSENC1 */

#if defined(POSENC2)
/**
  * @details This function enables the POSENC2 clock.
  */
__STATIC_INLINE void HAL_RCC_POSENC2_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_POSENC2);
}
#endif /* POSENC2 */

#if defined(OPAMP1)
/**
  * @details This function enables the OPAMP1 clock.
  */
__STATIC_INLINE void HAL_RCC_OPAMP1_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_OPAMP1);
}
#endif /* OPAMP1 */

#if defined(OPAMP2)
/**
  * @details This function enables the OPAMP2 clock.
  */
__STATIC_INLINE void HAL_RCC_OPAMP2_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_OPAMP2);
}
#endif /* OPAMP2 */

#if defined(OPAMP3)
/**
  * @details This function enables the OPAMP3 clock.
  */
__STATIC_INLINE void HAL_RCC_OPAMP3_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_OPAMP3);
}
#endif /* OPAMP3 */

/**
  * @details This function enables the VREFBUF clock.
  */
__STATIC_INLINE void HAL_RCC_VREFBUF_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function enables the RTCAPB clock.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function enables the COMP1 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP1_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_COMP1);
}

/**
  * @details This function enables the COMP2 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP2_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_COMP2);
}

/**
  * @details This function enables the COMP3 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP3_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_COMP3);
}

/**
  * @details This function enables the COMP4 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP4_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_COMP4);
}

/**
  * @details This function enables the COMP5 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP5_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_COMP5);
}

/**
  * @details This function enables the COMP6 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP6_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_COMP6);
}

/**
  * @details This function enables the COMP7 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP7_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_COMP7);
}

/**
  * @details This function enables the COMP8 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP8_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_COMP8);
}

/**
  * @details This function disables the SBS clock.
  */
__STATIC_INLINE void HAL_RCC_SBS_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_SBS);
}

#if defined(TIM20)
/**
  * @details This function disables the TIM20 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM20_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_TIM20);
}
#endif /* TIM20 */

/**
  * @details This function disables the TIM26 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM26_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_TIM26);
}

/**
  * @details This function disables the TIM27 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM27_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_TIM27);
}

/**
  * @details This function disables the LPUART1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_LPUART1);
}

#if defined(I2C3)
/**
  * @details This function disables the I2C3 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C3_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_I2C3);
}
#endif /* I2C3 */

#if defined(I2C4)
/**
  * @details This function disables the I2C4 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C4_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_I2C4);
}
#endif /* I2C4 */

/**
  * @details This function disables the LPTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_LPTIM1);
}

#if defined(POSENC1)
/**
  * @details This function disables the POSENC1 clock.
  */
__STATIC_INLINE void HAL_RCC_POSENC1_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_POSENC1);
}
#endif /* POSENC1 */

#if defined(POSENC2)
/**
  * @details This function disables the POSENC2 clock.
  */
__STATIC_INLINE void HAL_RCC_POSENC2_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_POSENC2);
}
#endif /* POSENC2 */

#if defined(OPAMP1)
/**
  * @details This function disables the OPAMP1 clock.
  */
__STATIC_INLINE void HAL_RCC_OPAMP1_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_OPAMP1);
}
#endif /* OPAMP1 */

#if defined(OPAMP2)
/**
  * @details This function disables the OPAMP2 clock.
  */
__STATIC_INLINE void HAL_RCC_OPAMP2_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_OPAMP2);
}
#endif /* OPAMP2 */

#if defined(OPAMP3)
/**
  * @details This function disables the OPAMP3 clock.
  */
__STATIC_INLINE void HAL_RCC_OPAMP3_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_OPAMP3);
}
#endif /* OPAMP3 */

/**
  * @details This function disables the VREFBUF clock.
  */
__STATIC_INLINE void HAL_RCC_VREFBUF_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function disables the RTCAPB clock.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the COMP1 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP1_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_COMP1);
}

/**
  * @details This function disables the COMP2 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP2_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_COMP2);
}

/**
  * @details This function disables the COMP3 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP3_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_COMP3);
}

/**
  * @details This function disables the COMP4 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP4_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_COMP4);
}

/**
  * @details This function disables the COMP5 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP5_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_COMP5);
}

/**
  * @details This function disables the COMP6 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP6_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_COMP6);
}

/**
  * @details This function disables the COMP7 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP7_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_COMP7);
}

/**
  * @details This function disables the COMP8 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP8_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_COMP8);
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
  * @details This function checks if the GPDMA1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPDMA1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPDMA1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPDMA1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function checks if the GPDMA2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPDMA2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPDMA2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPDMA2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPDMA2);
}

/**
  * @details This function checks if the FLASH clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FLASH clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FLASH clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FLASH_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_FLASH);
}

/**
  * @details This function checks if the CRC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CRC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CRC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CRC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_CRC);
}

/**
  * @details This function checks if the CORDIC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CORDIC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CORDIC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CORDIC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_CORDIC1);
}

/**
  * @details This function checks if the FMAC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FMAC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FMAC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FMAC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function checks if the RAMCFG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED RAMCFG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  RAMCFG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_RAMCFG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

/**
  * @details This function checks if the TZSC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TZSC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TZSC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TZSC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_TZSC1);
}

/**
  * @details This function checks if the SRAM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SRAM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SRAM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SRAM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_SRAM2);
}
#if defined(SRAM3_BASE)
/**
  * @details This function checks if the SRAM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SRAM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SRAM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SRAM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_SRAM3);
}
#endif /* SRAM3_BASE */
#if defined(DCACHE)
/**
  * @details This function checks if the DCACHE clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DCACHE clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DCACHE clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DCACHE_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DCACHE);
}
#endif /* DCACHE */

/**
  * @details This function checks if the SRAM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SRAM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SRAM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SRAM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_SRAM1);
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
  * @details This function checks if the DAC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_DAC1);
}

/**
  * @details This function checks if the DAC2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_DAC2);
}

/**
  * @details This function checks if the DAC5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_DAC5);
}

/**
  * @details This function checks if the DAC6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_DAC6);
}

/**
  * @details This function checks if the DAC7 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC7 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC7 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC7_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_DAC7);
}

/**
  * @details This function checks if the DAC8 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC8 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC8 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC8_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_DAC8);
}

/**
  * @details This function checks if the DAC9 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC9 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC9 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC9_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_DAC9);
}

/**
  * @details This function checks if the DAC10 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC10 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC10 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC10_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_DAC10);
}
#if defined(FMAC2)
/**
  * @details This function checks if the FMAC2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FMAC2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FMAC2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FMAC2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_FMAC2);
}
#endif /* FMAC2 */

/**
  * @details This function checks if the ADC12 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADC12 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADC12 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADC12_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_ADC12);
}
#if defined(ADC3)
/**
  * @details This function checks if the ADC3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADC3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADC3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADC3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_ADC3);
}
#endif /* ADC3 */

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
  * @details This function checks if the DBG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DBG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DBG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DBG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_DBG);
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
#if defined(AES)
/**
  * @details This function checks if the AES clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED AES clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  AES clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AES_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_AES);
}
#endif /* AES */

/**
  * @details This function checks if the HASH clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HASH clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HASH clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HASH_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_HASH);
}

/**
  * @details This function checks if the RNG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED RNG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  RNG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_RNG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_RNG);
}

/**
  * @details This function checks if the PKA clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED PKA clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  PKA clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_PKA_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_PKA);
}
#if defined(SAES)
/**
  * @details This function checks if the SAES clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SAES clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SAES clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SAES_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_SAES);
}
#endif /* SAES */
#if defined(CCB)
/**
  * @details This function checks if the CCB clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CCB clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CCB clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CCB_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_CCB);
}
#endif /* CCB */
#if defined(OTFDEC1)
/**
  * @details This function checks if the OTFDEC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OTFDEC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OTFDEC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OTFDEC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

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
#if defined(XSPI1)
/**
  * @details This function checks if the XSPI1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED XSPI1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  XSPI1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_XSPI1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_XSPI1);
}
#endif /* XSPI1 */

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
#if defined(TIM3)
/**
  * @details This function checks if the TIM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM3);
}
#endif /* TIM3 */

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
  * @details This function checks if the TIM9 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM9 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM9 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM9_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM9);
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
  * @details This function checks if the WWDG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED WWDG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  WWDG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_WWDG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_WWDG);
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
#if defined(SPI3)
/**
  * @details This function checks if the SPI3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI3);
}
#endif /* SPI3 */

/**
  * @details This function checks if the USART2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART2);
}
#if defined(USART3)
/**
  * @details This function checks if the USART3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART3);
}
#endif /* USART3 */

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
  * @details This function checks if the I3C1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I3C1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I3C1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I3C1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I3C1);
}
#if defined(CRS)
/**
  * @details This function checks if the CRS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CRS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CRS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CRS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_CRS);
}
#endif /* CRS */

/**
  * @details This function checks if the UART6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART6);
}

/**
  * @details This function checks if the DTS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DTS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DTS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DTS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_DTS);
}

/**
  * @details This function checks if the FDCAN clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FDCAN clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FDCAN clock is enabled
  * @note The FDCAN clock is common for all FDCAN instances
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FDCAN_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_FDCAN);
}
#if defined(UCPD1)
/**
  * @details This function checks if the UCPD1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UCPD1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UCPD1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UCPD1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_UCPD1);
}
#endif /* UCPD1 */

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Enable_Status APB2 Peripheral Clock Enabled Status
  * @brief  Check whether the APB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */
#if defined(HRTIM1)
/**
  * @details This function checks if the HRTIM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HRTIM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HRTIM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HRTIM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_HRTIM1);
}
#endif /* HRTIM1 */

#if defined(PLAY1)
/**
  * @details This function checks if the PLAY1APB clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED PLAY1APB clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  PLAY1APB clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_PLAY1APB_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_PLAY1APB);
}

/**
  * @details This function checks if the PLAY1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED PLAY1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  PLAY1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_PLAY1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_PLAY1);
}
#endif /* PLAY1 */

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
  * @details This function checks if the SPI1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SPI1);
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
  * @details This function checks if the USART1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART1);
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
#if defined(USB_DRD_FS)
/**
  * @details This function checks if the USB clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USB clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USB clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USB_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USB);
}
#endif /* USB_DRD_FS */
#if defined(TIM4)
/**
  * @details This function checks if the TIM4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM4);
}
#endif /* TIM4 */
#if defined(TIM5)
/**
  * @details This function checks if the TIM5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM5);
}
#endif /* TIM5 */

/**
  * @}
  */

/** @defgroup RCC_APB3_Peripheral_Clock_Enable_Status APB3 Peripheral Clock Enabled Status
  * @brief  Check whether the APB3 peripheral clock is enabled or not.
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
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_SBS);
}
#if defined(TIM20)
/**
  * @details This function checks if the TIM20 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM20 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM20 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM20_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_TIM20);
}
#endif /* TIM20 */

/**
  * @details This function checks if the TIM26 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM26 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM26 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM26_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_TIM26);
}

/**
  * @details This function checks if the TIM27 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM27 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM27 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM27_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_TIM27);
}

/**
  * @details This function checks if the LPUART1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPUART1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPUART1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPUART1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_LPUART1);
}
#if defined(I2C3)
/**
  * @details This function checks if the I2C3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_I2C3);
}
#endif /* I2C3 */
#if defined(I2C4)
/**
  * @details This function checks if the I2C4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_I2C4);
}
#endif /* I2C4 */

/**
  * @details This function checks if the LPTIM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_LPTIM1);
}
#if defined(POSENC1)
/**
  * @details This function checks if the POSENC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED POSENC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  POSENC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_POSENC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_POSENC1);
}
#endif /* POSENC1 */
#if defined(POSENC2)
/**
  * @details This function checks if the POSENC2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED POSENC2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  POSENC2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_POSENC2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_POSENC2);
}
#endif /* POSENC2 */
#if defined(OPAMP1)
/**
  * @details This function checks if the OPAMP1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OPAMP1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OPAMP1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OPAMP1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_OPAMP1);
}
#endif /* OPAMP1 */
#if defined(OPAMP2)
/**
  * @details This function checks if the OPAMP2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OPAMP2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OPAMP2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OPAMP2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_OPAMP2);
}
#endif /* OPAMP2 */
#if defined(OPAMP3)
/**
  * @details This function checks if the OPAMP3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OPAMP3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OPAMP3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OPAMP3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_OPAMP3);
}
#endif /* OPAMP3 */

/**
  * @details This function checks if the VREFBUF clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED VREFBUF clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  VREFBUF clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_VREFBUF_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function checks if the RTCAPB clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED RTCAPB clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  RTCAPB clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_RTCAPB_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function checks if the COMP1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_COMP1);
}

/**
  * @details This function checks if the COMP2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_COMP2);
}

/**
  * @details This function checks if the COMP3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_COMP3);
}

/**
  * @details This function checks if the COMP4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_COMP4);
}

/**
  * @details This function checks if the COMP5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_COMP5);
}

/**
  * @details This function checks if the COMP6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_COMP6);
}

/**
  * @details This function checks if the COMP7 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP7 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP7 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP7_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_COMP7);
}

/**
  * @details This function checks if the COMP8 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP8 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP8 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP8_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_COMP8);
}

/**
  * @}
  */

/** @defgroup RCC_AHB1_Reset AHB1 PeripheralReset
  * @brief  AHB1 peripheral reset.
  * @{
  */

/**
  * @details This function resets the GPDMA1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPDMA1);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function resets the GPDMA2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPDMA2_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPDMA2);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPDMA2);
}

/**
  * @details This function resets the CRC peripheral.
  */
__STATIC_INLINE void HAL_RCC_CRC_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_CRC);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_CRC);
}

/**
  * @details This function resets the CORDIC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_CORDIC1_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_CORDIC1);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_CORDIC1);
}

/**
  * @details This function resets the FMAC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_FMAC1_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_FMAC1);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function resets the RAMCFG peripheral.
  */
__STATIC_INLINE void HAL_RCC_RAMCFG_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_RAMCFG);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

/**
  * @}
  */

/** @defgroup RCC_AHB2_Reset AHB2 PeripheralReset
  * @brief  AHB2 peripheral reset.
  * @{
  */

/**
  * @details This function resets the DAC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC1_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_DAC1);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_DAC1);
}

/**
  * @details This function resets the DAC2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC2_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_DAC2);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_DAC2);
}

/**
  * @details This function resets the DAC5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC5_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_DAC5);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_DAC5);
}

/**
  * @details This function resets the DAC6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC6_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_DAC6);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_DAC6);
}

/**
  * @details This function resets the DAC7 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC7_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_DAC7);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_DAC7);
}

/**
  * @details This function resets the DAC8 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC8_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_DAC8);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_DAC8);
}

/**
  * @details This function resets the DAC9 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC9_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_DAC9);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_DAC9);
}

/**
  * @details This function resets the DAC10 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC10_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_DAC10);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_DAC10);
}

#if defined(FMAC2)
/**
  * @details This function resets the FMAC2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_FMAC2_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_FMAC2);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_FMAC2);
}
#endif /* FMAC2 */

/**
  * @details This function resets the ADC12 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADC12_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_ADC12);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_ADC12);
}

#if defined(ADC3)
/**
  * @details This function resets the ADC3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADC3_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_ADC3);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_ADC3);
}
#endif /* ADC3 */

/**
  * @}
  */

/** @defgroup RCC_AHB4_Reset AHB4 PeripheralReset
  * @brief  AHB4 peripheral reset.
  * @{
  */

#if defined(AES)
/**
  * @details This function resets the AES peripheral.
  */
__STATIC_INLINE void HAL_RCC_AES_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_AES);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_AES);
}
#endif /* AES */

/**
  * @details This function resets the HASH peripheral.
  */
__STATIC_INLINE void HAL_RCC_HASH_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_HASH);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_HASH);
}

/**
  * @details This function resets the RNG peripheral.
  */
__STATIC_INLINE void HAL_RCC_RNG_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_RNG);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_RNG);
}

/**
  * @details This function resets the PKA peripheral.
  */
__STATIC_INLINE void HAL_RCC_PKA_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_PKA);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_PKA);
}

#if defined(SAES)
/**
  * @details This function resets the SAES peripheral.
  */
__STATIC_INLINE void HAL_RCC_SAES_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_SAES);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined(CCB)
/**
  * @details This function resets the CCB peripheral.
  */
__STATIC_INLINE void HAL_RCC_CCB_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_CCB);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_CCB);
}
#endif /* CCB */

#if defined(OTFDEC1)
/**
  * @details This function resets the OTFDEC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_OTFDEC1_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_OTFDEC1);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

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

#if defined(XSPI1)
/**
  * @details This function resets the XSPI1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_XSPI1);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_XSPI1);
}
#endif /* XSPI1 */

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

#if defined(TIM3)
/**
  * @details This function resets the TIM3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM3);
}
#endif /* TIM3 */

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
  * @details This function resets the TIM9 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM9_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM9);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM9);
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
  * @details This function resets the SPI2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI2);
}

#if defined(SPI3)
/**
  * @details This function resets the SPI3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI3);
}
#endif /* SPI3 */

/**
  * @details This function resets the USART2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART2);
}

#if defined(USART3)
/**
  * @details This function resets the USART3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART3);
}
#endif /* USART3 */

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
  * @details This function resets the I3C1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I3C1_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I3C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I3C1);
}

#if defined(CRS)
/**
  * @details This function resets the CRS peripheral.
  */
__STATIC_INLINE void HAL_RCC_CRS_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_CRS);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_CRS);
}
#endif /* CRS */

/**
  * @details This function resets the UART6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART6_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART6);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART6);
}

/**
  * @details This function resets the DTS peripheral.
  */
__STATIC_INLINE void HAL_RCC_DTS_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_DTS);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_DTS);
}

/**
  * @details This function resets the FDCAN peripheral.
  * @note    The FDCAN clock is common for all FDCAN instances
  */
__STATIC_INLINE void HAL_RCC_FDCAN_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_FDCAN);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_FDCAN);
}

#if defined(UCPD1)
/**
  * @details This function resets the UCPD1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_UCPD1);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_UCPD1);
}
#endif /* UCPD1 */

/**
  * @}
  */

/** @defgroup RCC_APB2_Reset APB2 PeripheralReset
  * @brief  APB2 peripheral reset.
  * @{
  */

#if defined(HRTIM1)
/**
  * @details This function resets the HRTIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_HRTIM1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_HRTIM1);
}
#endif /* HRTIM1 */

#if defined(PLAY1)
/**
  * @details This function resets the PLAY1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_PLAY1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_PLAY1GLOBAL);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_PLAY1GLOBAL);
}

/**
  * @details This function resets the PLAY1 application block.
  */
__STATIC_INLINE void HAL_RCC_PLAY1APP_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_PLAY1APP);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_PLAY1APP);
}
#endif /* PLAY1 */

/**
  * @details This function resets the TIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM1);
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
  * @details This function resets the TIM8 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM8_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM8);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM8);
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

#if defined(USB_DRD_FS)
/**
  * @details This function resets the USB peripheral.
  */
__STATIC_INLINE void HAL_RCC_USB_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USB);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USB);
}
#endif /* USB_DRD_FS */

#if defined(TIM4)
/**
  * @details This function resets the TIM4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM4_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM4);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM4);
}
#endif /* TIM4 */

#if defined(TIM5)
/**
  * @details This function resets the TIM5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM5_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM5);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM5);
}
#endif /* TIM5 */

/**
  * @}
  */

/** @defgroup RCC_APB3_Reset APB3 PeripheralReset
  * @brief  APB3 peripheral reset.
  * @{
  */

#if defined(TIM20)
/**
  * @details This function resets the TIM20 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM20_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_TIM20);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_TIM20);
}
#endif /* TIM20 */

/**
  * @details This function resets the TIM26 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM26_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_TIM26);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_TIM26);
}

/**
  * @details This function resets the TIM27 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM27_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_TIM27);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_TIM27);
}

/**
  * @details This function resets the LPUART1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_LPUART1);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_LPUART1);
}

#if defined(I2C3)
/**
  * @details This function resets the I2C3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C3_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_I2C3);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_I2C3);
}
#endif /* I2C3 */

#if defined(I2C4)
/**
  * @details This function resets the I2C4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C4_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_I2C4);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_I2C4);
}
#endif /* I2C4 */

/**
  * @details This function resets the LPTIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_LPTIM1);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_LPTIM1);
}

#if defined(POSENC1)
/**
  * @details This function resets the POSENC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_POSENC1_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_POSENC1);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_POSENC1);
}
#endif /* POSENC1 */

#if defined(POSENC2)
/**
  * @details This function resets the POSENC2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_POSENC2_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_POSENC2);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_POSENC2);
}
#endif /* POSENC2 */

#if defined(OPAMP1)
/**
  * @details This function resets the OPAMP1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_OPAMP1_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_OPAMP1);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_OPAMP1);
}
#endif /* OPAMP1 */

#if defined(OPAMP2)
/**
  * @details This function resets the OPAMP2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_OPAMP2_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_OPAMP2);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_OPAMP2);
}
#endif /* OPAMP2 */

#if defined(OPAMP3)
/**
  * @details This function resets the OPAMP3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_OPAMP3_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_OPAMP3);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_OPAMP3);
}
#endif /* OPAMP3 */

/**
  * @details This function resets the VREFBUF peripheral.
  */
__STATIC_INLINE void HAL_RCC_VREFBUF_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_VREFBUF);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function resets the COMP1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP1_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_COMP1);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_COMP1);
}

/**
  * @details This function resets the COMP2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP2_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_COMP2);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_COMP2);
}

/**
  * @details This function resets the COMP3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP3_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_COMP3);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_COMP3);
}

/**
  * @details This function resets the COMP4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP4_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_COMP4);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_COMP4);
}

/**
  * @details This function resets the COMP5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP5_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_COMP5);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_COMP5);
}

/**
  * @details This function resets the COMP6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP6_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_COMP6);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_COMP6);
}

/**
  * @details This function resets the COMP7 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP7_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_COMP7);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_COMP7);
}

/**
  * @details This function resets the COMP8 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP8_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_COMP8);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_COMP8);
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
  * @details This function enables the GPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the GPDMA2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA2_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA2);
}

/**
  * @details This function enables the FLASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FLASH_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_FLASH);
}

/**
  * @details This function enables the CRC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRC_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_CRC);
}

/**
  * @details This function enables the CORDIC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CORDIC1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_CORDIC1);
}

/**
  * @details This function enables the FMAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMAC1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function enables the RAMCFG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RAMCFG_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

/**
  * @details This function enables the TZSC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TZSC1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_TZSC1);
}

/**
  * @details This function enables the SRAM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM2_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM2);
}

/**
  * @details This function enables the SRAM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM2_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM2);
}

#if defined(SRAM3_BASE)
/**
  * @details This function enables the SRAM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM3_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM3);
}

/**
  * @details This function enables the SRAM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM3_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM3);
}
#endif /* SRAM3_BASE */

/**
  * @details This function enables the ICACHE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ICACHE_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_ICACHE);
}

#if defined(DCACHE)
/**
  * @details This function enables the DCACHE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DCACHE_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_DCACHE);
}
#endif /* DCACHE */

/**
  * @details This function enables the SRAM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM1);
}

/**
  * @details This function enables the SRAM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM1_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM1);
}

/**
  * @details This function disables the GPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function disables the GPDMA2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA2_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA2);
}

/**
  * @details This function disables the FLASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FLASH_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_FLASH);
}

/**
  * @details This function disables the CRC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRC_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_CRC);
}

/**
  * @details This function disables the CORDIC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CORDIC1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_CORDIC1);
}

/**
  * @details This function disables the FMAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMAC1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function disables the RAMCFG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RAMCFG_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

/**
  * @details This function disables the TZSC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TZSC1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_TZSC1);
}

/**
  * @details This function disables the SRAM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM2_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM2);
}

/**
  * @details This function disables the SRAM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM2_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM2);
}

#if defined(SRAM3_BASE)
/**
  * @details This function disables the SRAM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM3_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM3);
}

/**
  * @details This function disables the SRAM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM3_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM3);
}
#endif /* SRAM3_BASE */

/**
  * @details This function disables the ICACHE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ICACHE_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_ICACHE);
}

#if defined(DCACHE)
/**
  * @details This function disables the DCACHE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DCACHE_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_DCACHE);
}

#endif /* DCACHE */

/**
  * @details This function disables the SRAM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM1);
}

/**
  * @details This function disables the SRAM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM1_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_SRAM1);
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
  * @details This function enables the DAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the DAC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the DAC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC2_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC2);
}

/**
  * @details This function enables the DAC2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC2_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC2);
}

/**
  * @details This function enables the DAC5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC5_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC5);
}

/**
  * @details This function enables the DAC5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC5_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC5);
}

/**
  * @details This function enables the DAC6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC6_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC6);
}

/**
  * @details This function enables the DAC6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC6_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC6);
}

/**
  * @details This function enables the DAC7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC7_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC7);
}

/**
  * @details This function enables the DAC7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC7_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC7);
}

/**
  * @details This function enables the DAC8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC8_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC8);
}

/**
  * @details This function enables the DAC8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC8_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC8);
}

/**
  * @details This function enables the DAC9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC9_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC9);
}

/**
  * @details This function enables the DAC9 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC9_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC9);
}

/**
  * @details This function enables the DAC10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC10_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC10);
}

/**
  * @details This function enables the DAC10 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC10_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC10);
}

#if defined(FMAC2)
/**
  * @details This function enables the FMAC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMAC2_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_FMAC2);
}
#endif /* FMAC2 */

/**
  * @details This function enables the ADC12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC12_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_ADC12);
}

#if defined(ADC3)
/**
  * @details This function enables the ADC3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC3_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_ADC3);
}
#endif /* ADC3 */

/**
  * @details This function disables the DAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the DAC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the DAC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC2_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC2);
}

/**
  * @details This function disables the DAC2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC2_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC2);
}

/**
  * @details This function disables the DAC5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC5_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC5);
}

/**
  * @details This function disables the DAC5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC5_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC5);
}

/**
  * @details This function disables the DAC6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC6_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC6);
}

/**
  * @details This function disables the DAC6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC6_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC6);
}

/**
  * @details This function disables the DAC7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC7_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC7);
}

/**
  * @details This function disables the DAC7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC7_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC7);
}

/**
  * @details This function disables the DAC8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC8_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC8);
}

/**
  * @details This function disables the DAC8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC8_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC8);
}

/**
  * @details This function disables the DAC9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC9_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC9);
}

/**
  * @details This function disables the DAC9 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC9_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC9);
}

/**
  * @details This function disables the DAC10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC10_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC10);
}

/**
  * @details This function disables the DAC10 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC10_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_DAC10);
}

#if defined(FMAC2)
/**
  * @details This function disables the FMAC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMAC2_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_FMAC2);
}
#endif /* FMAC2 */

/**
  * @details This function disables the ADC12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC12_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_ADC12);
}

#if defined(ADC3)
/**
  * @details This function disables the ADC3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC3_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_ADC3);
}

#endif /* ADC3 */

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
  * @details This function enables the DBG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DBG_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DBG);
}

/**
  * @details This function disables the DBG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DBG_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DBG);
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

#if defined(AES)
/**
  * @details This function enables the AES clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AES_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_AES);
}
#endif /* AES */

/**
  * @details This function enables the HASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HASH_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_HASH);
}

/**
  * @details This function enables the RNG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RNG_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_RNG);
}

/**
  * @details This function enables the PKA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_PKA_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_PKA);
}

#if defined(SAES)
/**
  * @details This function enables the SAES clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SAES_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined(CCB)
/**
  * @details This function enables the CCB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CCB_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_CCB);
}

#endif /* CCB */

#if defined(OTFDEC1)
/**
  * @details This function enables the OTFDEC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OTFDEC1_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

/**
  * @details This function enables the GPIOA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOA_EnableClockInSleepMode(void)
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
  * @details This function enables the GPIOC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOC_EnableClockInSleepMode(void)
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
  * @details This function enables the GPIOE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOE_EnableClockInSleepMode(void)
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
  * @details This function enables the GPIOG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOG_EnableClockInSleepMode(void)
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

#if defined(XSPI1)
/**
  * @details This function enables the XSPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_XSPI1_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_XSPI1);
}
#endif /* XSPI1 */

#if defined(AES)
/**
  * @details This function disables the AES clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AES_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_AES);
}
#endif /* AES */

/**
  * @details This function disables the HASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HASH_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_HASH);
}

/**
  * @details This function disables the RNG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RNG_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_RNG);
}

/**
  * @details This function disables the PKA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_PKA_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_PKA);
}

#if defined(SAES)
/**
  * @details This function disables the SAES clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SAES_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined(CCB)
/**
  * @details This function disables the CCB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CCB_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_CCB);
}

#endif /* CCB */

#if defined(OTFDEC1)
/**
  * @details This function disables the OTFDEC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OTFDEC1_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

/**
  * @details This function disables the GPIOA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOA_DisableClockInSleepMode(void)
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
  * @details This function disables the GPIOC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOC_DisableClockInSleepMode(void)
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
  * @details This function disables the GPIOE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOE_DisableClockInSleepMode(void)
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
  * @details This function disables the GPIOG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOG_DisableClockInSleepMode(void)
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

#if defined(XSPI1)
/**
  * @details This function disables the XSPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_XSPI1_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_XSPI1);
}
#endif /* XSPI1 */

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

#if defined(TIM3)
/**
  * @details This function enables the TIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM3);
}
#endif /* TIM3 */

/**
  * @details This function enables the TIM6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM6_EnableClockInSleepMode(void)
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
  * @details This function enables the TIM9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM9_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM9);
}

/**
  * @details This function enables the TIM10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM10_EnableClockInSleepMode(void)
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
  * @details This function enables the TIM12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM12_EnableClockInSleepMode(void)
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
  * @details This function enables the TIM14 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM14_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function enables the WWDG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_WWDG_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_WWDG);
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

#if defined(SPI3)
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
#endif /* SPI3 */

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

#if defined(USART3)
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
#endif /* USART3 */

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

#if defined(CRS)
/**
  * @details This function enables the CRS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRS_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_CRS);
}
#endif /* CRS */

/**
  * @details This function enables the UART6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART6_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART6);
}

/**
  * @details This function enables the UART6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART6_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART6);
}

/**
  * @details This function disables the TIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM2);
}

#if defined(TIM3)
/**
  * @details This function disables the TIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM3);
}
#endif /* TIM3 */

/**
  * @details This function disables the TIM6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM6_DisableClockInSleepMode(void)
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
  * @details This function disables the TIM9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM9_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM9);
}

/**
  * @details This function disables the TIM10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM10_DisableClockInSleepMode(void)
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
  * @details This function disables the TIM12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM12_DisableClockInSleepMode(void)
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
  * @details This function disables the TIM14 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM14_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function disables the WWDG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_WWDG_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_WWDG);
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

#if defined(SPI3)
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
#endif /* SPI3 */

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

#if defined(USART3)
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
#endif /* USART3 */

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

#if defined(CRS)
/**
  * @details This function disables the CRS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRS_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_CRS);
}
#endif /* CRS */

/**
  * @details This function disables the UART6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART6_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART6);
}

/**
  * @details This function disables the UART6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART6_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART6);
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
  * @details This function enables the DTS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTS_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_DTS);
}

/**
  * @details This function enables the DTS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTS_EnableClockInStopMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_DTS);
}

/**
  * @details This function enables the FDCAN clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FDCAN_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_FDCAN);
}

#if defined(UCPD1)
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
#endif /* UCPD1 */

/**
  * @details This function disables the DTS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTS_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_DTS);
}

/**
  * @details This function disables the DTS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DTS_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_DTS);
}

/**
  * @details This function disables the FDCAN clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FDCAN_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_FDCAN);
}

#if defined(UCPD1)
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
#endif /* UCPD1 */

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

#if defined(HRTIM1)
/**
  * @details This function enables the HRTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HRTIM1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM1);
}
#endif /* HRTIM1 */

#if defined(PLAY1)
/**
  * @details This function enables the PLAY1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_PLAY1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_PLAY1);
}

/**
  * @details This function enables the PLAY1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_PLAY1_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_PLAY1);
}
#endif /* PLAY1 */

/**
  * @details This function enables the TIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM1);
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
  * @details This function enables the TIM8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM8_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM8);
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
  * @details This function enables the TIM15 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM15_EnableClockInSleepMode(void)
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
  * @details This function enables the TIM17 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM17_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM17);
}

#if defined(USB_DRD_FS)
/**
  * @details This function enables the USB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USB_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USB);
}

/**
  * @details This function enables the USB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USB_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USB);
}
#endif /* USB_DRD_FS */

#if defined(TIM4)
/**
  * @details This function enables the TIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM4_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM4);
}
#endif /* TIM4 */

#if defined(TIM5)
/**
  * @details This function enables the TIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM5_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM5);
}
#endif /* TIM5 */

#if defined(HRTIM1)
/**
  * @details This function disables the HRTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HRTIM1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM1);
}
#endif /* HRTIM1 */

#if defined(PLAY1)
/**
  * @details This function disables the PLAY1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_PLAY1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_PLAY1);
}

/**
  * @details This function disables the PLAY1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_PLAY1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_PLAY1);
}
#endif /* PLAY1 */

/**
  * @details This function disables the TIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM1);
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
  * @details This function disables the TIM8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM8_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM8);
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
  * @details This function disables the TIM15 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM15_DisableClockInSleepMode(void)
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
  * @details This function disables the TIM17 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM17_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM17);
}

#if defined(USB_DRD_FS)
/**
  * @details This function disables the USB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USB_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USB);
}

/**
  * @details This function disables the USB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USB_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USB);
}
#endif /* USB_DRD_FS */

#if defined(TIM4)
/**
  * @details This function disables the TIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM4_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM4);
}
#endif /* TIM4 */

#if defined(TIM5)
/**
  * @details This function disables the TIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM5_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM5);
}
#endif /* TIM5 */

/**
  * @}
  */

/** @defgroup RCC_APB3_Peripheral_Clock_Sleep_Enable_Disable APB3 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB3 peripheral clock during Low Power (Sleep and Stop) mode.
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
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_SBS);
}

#if defined(TIM20)
/**
  * @details This function enables the TIM20 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM20_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_TIM20);
}
#endif /* TIM20 */

/**
  * @details This function enables the TIM26 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM26_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_TIM26);
}

/**
  * @details This function enables the TIM27 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM27_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_TIM27);
}

/**
  * @details This function enables the LPUART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function enables the LPUART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_LPUART1);
}

#if defined(I2C3)
/**
  * @details This function enables the I2C3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_I2C3);
}

/**
  * @details This function enables the I2C3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_I2C3);
}
#endif /* I2C3 */

#if defined(I2C4)
/**
  * @details This function enables the I2C4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C4_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_I2C4);
}

/**
  * @details This function enables the I2C4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C4_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_I2C4);
}
#endif /* I2C4 */

/**
  * @details This function enables the LPTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function enables the LPTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_LPTIM1);
}

#if defined(POSENC1)
/**
  * @details This function enables the POSENC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_POSENC1_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_POSENC1);
}
#endif /* POSENC1 */

#if defined(POSENC2)
/**
  * @details This function enables the POSENC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_POSENC2_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_POSENC2);
}
#endif /* POSENC2 */

#if defined(OPAMP1)
/**
  * @details This function enables the OPAMP1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP1_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP1);
}

/**
  * @details This function enables the OPAMP1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP1_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP1);
}
#endif /* OPAMP1 */

#if defined(OPAMP2)
/**
  * @details This function enables the OPAMP2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP2_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP2);
}

/**
  * @details This function enables the OPAMP2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP2_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP2);
}
#endif /* OPAMP2 */

#if defined(OPAMP3)
/**
  * @details This function enables the OPAMP3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP3_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP3);
}

/**
  * @details This function enables the OPAMP3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP3_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP3);
}
#endif /* OPAMP3 */

/**
  * @details This function enables the VREFBUF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREFBUF_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function enables the VREFBUF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREFBUF_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function enables the RTCAPB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function enables the RTCAPB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function enables the COMP1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP1_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP1);
}

/**
  * @details This function enables the COMP1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP1_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP1);
}

/**
  * @details This function enables the COMP2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP2_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP2);
}

/**
  * @details This function enables the COMP2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP2_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP2);
}

/**
  * @details This function enables the COMP3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP3_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP3);
}

/**
  * @details This function enables the COMP3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP3_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP3);
}

/**
  * @details This function enables the COMP4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP4_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP4);
}

/**
  * @details This function enables the COMP4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP4_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP4);
}

/**
  * @details This function enables the COMP5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP5_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP5);
}

/**
  * @details This function enables the COMP5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP5_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP5);
}

/**
  * @details This function enables the COMP6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP6_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP6);
}

/**
  * @details This function enables the COMP6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP6_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP6);
}

/**
  * @details This function enables the COMP7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP7_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP7);
}

/**
  * @details This function enables the COMP7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP7_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP7);
}

/**
  * @details This function enables the COMP8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP8_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP8);
}

/**
  * @details This function enables the COMP8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP8_EnableClockInStopMode(void)
{
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_COMP8);
}

/**
  * @details This function disables the SBS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SBS_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_SBS);
}

#if defined(TIM20)
/**
  * @details This function disables the TIM20 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM20_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_TIM20);
}
#endif /* TIM20 */

/**
  * @details This function disables the TIM26 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM26_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_TIM26);
}

/**
  * @details This function disables the TIM27 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM27_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_TIM27);
}

/**
  * @details This function disables the LPUART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function disables the LPUART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_LPUART1);
}

#if defined(I2C3)
/**
  * @details This function disables the I2C3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_I2C3);
}

/**
  * @details This function disables the I2C3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_I2C3);
}
#endif /* I2C3 */

#if defined(I2C4)
/**
  * @details This function disables the I2C4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C4_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_I2C4);
}

/**
  * @details This function disables the I2C4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C4_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_I2C4);
}
#endif /* I2C4 */

/**
  * @details This function disables the LPTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function disables the LPTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_LPTIM1);
}

#if defined(POSENC1)
/**
  * @details This function disables the POSENC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_POSENC1_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_POSENC1);
}
#endif /* POSENC1 */

#if defined(POSENC2)
/**
  * @details This function disables the POSENC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_POSENC2_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_POSENC2);
}
#endif /* POSENC2 */

#if defined(OPAMP1)
/**
  * @details This function disables the OPAMP1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP1_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP1);
}

/**
  * @details This function disables the OPAMP1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP1_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP1);
}
#endif /* OPAMP1 */

#if defined(OPAMP2)
/**
  * @details This function disables the OPAMP2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP2_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP2);
}

/**
  * @details This function disables the OPAMP2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP2_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP2);
}
#endif /* OPAMP2 */

#if defined(OPAMP3)
/**
  * @details This function disables the OPAMP3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP3_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP3);
}

/**
  * @details This function disables the OPAMP3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP3_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_OPAMP3);
}
#endif /* OPAMP3 */

/**
  * @details This function disables the VREFBUF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREFBUF_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function disables the VREFBUF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREFBUF_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_VREFBUF);
}

/**
  * @details This function disables the RTCAPB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the RTCAPB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the COMP1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP1_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP1);
}

/**
  * @details This function disables the COMP1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP1_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP1);
}

/**
  * @details This function disables the COMP2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP2_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP2);
}

/**
  * @details This function disables the COMP2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP2_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP2);
}

/**
  * @details This function disables the COMP3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP3_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP3);
}

/**
  * @details This function disables the COMP3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP3_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP3);
}

/**
  * @details This function disables the COMP4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP4_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP4);
}

/**
  * @details This function disables the COMP4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP4_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP4);
}

/**
  * @details This function disables the COMP5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP5_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP5);
}

/**
  * @details This function disables the COMP5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP5_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP5);
}

/**
  * @details This function disables the COMP6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP6_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP6);
}

/**
  * @details This function disables the COMP6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP6_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP6);
}

/**
  * @details This function disables the COMP7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP7_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP7);
}

/**
  * @details This function disables the COMP7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP7_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP7);
}

/**
  * @details This function disables the COMP8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP8_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP8);
}

/**
  * @details This function disables the COMP8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP8_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockLowPower(LL_APB3_GRP1_PERIPH_COMP8);
}

/**
  * @}
  */

/** @defgroup RCC_RTC_Domain_Reset RCC RTC Domain Reset
  * @{
  */

/** @brief    Function to force and release the RTC domain.
  * @details  When a RTC domain reset occurs, the following domains are impacted:
  *           - the RTC is stopped and all the RTC registers are set to their reset values
  *             (including the backup registers)
  *           - all TAMP registers can be read or written in both secure and non-secure modes.
  *             The secure boot code can change this security setup, making some registers secure
  *             or not as needed, using TAMP_SECCFGR register.
  *           - LSE crystal 32kHz crystal oscillator
  *           - RCC_RTCCR register
  */
__STATIC_INLINE void HAL_RCC_ResetRTCDomain(void)
{
  LL_RCC_ForceRTCDomainReset();
  LL_RCC_ReleaseRTCDomainReset();
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group3 RCC services functions
  This subsection provides a set of functions allowing to:

  - Configure the MCO. MCO (Microcontroller Clock Output) is used to output HSI, LSE, HSE, PLL1Q, HSI48, SYSCLK, PLL2P,
    HSE, LSI or main PLL clock, through a configurable prescaler, on a pin.

  - Get and clear reset flags

  - Enable the CSS (Clock Security System). Once CSS is enabled, if a HSE clock failure occurs (HSE used directly or
  through PLL as System clock source), the System clock source is automatically switched to HSI.
  The HSECSS interrupt is linked to the Cortex-M33 NMI (non-maskable interrupt) exception vector.
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
hal_status_t                 HAL_RCC_NMI_IRQHandler(void);
hal_status_t                 HAL_RCC_HSE_CSSCallback(void);
void                         HAL_RCC_RTC_SetHSEPrescaler(uint32_t prescaler);
uint32_t                     HAL_RCC_RTC_GetHSEPrescaler(void);
#endif /* HSE_VALUE */
#if defined(LSE_VALUE)
void                                       HAL_RCC_LSE_EnableCSS(void);
void                                       HAL_RCC_LSE_DisableCSS(void);
hal_rcc_lse_css_failure_detection_status_t HAL_RCC_LSE_IsCSSDetected(void);
void                                       HAL_RCC_LSECSS_IRQHandler(void);
void                                       HAL_RCC_LSE_CSSCallback(void);
#endif /* LSE_VALUE */
hal_status_t                 HAL_RCC_RTC_EnableKernelClock(void);
hal_status_t                 HAL_RCC_RTC_DisableKernelClock(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group4 Kernel clock source configuration for peripherals
  This subsection provides a set of functions:
  - to disable all peripherals Kernel clocks
  - to control Kernel clock source configuration for peripherals
  - to control specific Kernel clock prescaler for peripherals if available
  - to get peripheral clock frequency
    - The peripheral clock is selected through HAL_RCC_{PERIPHx}_SetKernelClkSource(hal_rcc_{periph}_clk_src_t clk_src)

    example: @ref HAL_RCC_USART1_SetKernelClkSource(hal_rcc_usart1_clk_src_t clk_src) to select HSE as clock source
    of USART1

    @code HAL_RCC_USART1_SetKernelClkSource(HAL_RCC_USART1_CLK_SRC_HSE);    @endcode

    - The peripheral Clocks source is retrieved thanks to
    hal_rcc_{periph}_clk_src_t HAL_RCC_{PERIPHx}_GetKernelClkSource(void)

    - The peripheral clock can be divided by a specific value:
      - API HAL_RCC_{PERIPHx}_SetKernelClkPrescaler(hal_rcc_{periphx}_prescaler_t clk_prescaler)
      example: @ref HAL_RCC_ADC_SetKernelClkPrescaler(hal_rcc_adc_prescaler_t clk_prescaler)
      - API HAL_RCC_{PERIPHx}_prescaler_t HAL_RCC_{PERIPHx}_GetKernelClkPrescaler(void)
      example: @ref hal_rcc_adc_prescaler_t HAL_RCC_ADC_GetKernelClkPrescaler(void)

    - The functionalities of the two previous functions are grouped into one common function:
      - API HAL_RCC_{PERIPHx}_SetConfigKernelClk(hal_rcc_{periphx}_clk_src_t clk_src,
                                            hal_rcc_{periphx}_prescaler_t clk_prescaler)
      example: @ref HAL_RCC_ADC_SetConfigKernelClk(hal_rcc_adc_clk_src_t clk_src,
                                                    hal_rcc_adc_prescaler_t clk_prescaler)
      - API HAL_RCC_{PERIPHx}_GetConfigKernelClk(hal_rcc_{periphx}_clk_src_t clk_src,
                                            hal_rcc_{periphx}_prescaler_t clk_prescaler)
      example: @ref HAL_RCC_ADC_GetConfigKernelClk(hal_rcc_adc_clk_src_t *p_clk_src,
                                                    hal_rcc_adc_prescaler_t *p_prescaler)

    - All peripherals can get their peripheral clock frequency
      - API uint32_t HAL_RCC_{PERIPHx}_GetKernelClkFreq(void)
      example: @ref HAL_RCC_USART1_GetKernelClkFreq(void)

  * @{
  */

hal_status_t HAL_RCC_DisableAllKernelClocks(void);
hal_status_t HAL_RCC_USART1_SetKernelClkSource(hal_rcc_usart1_clk_src_t clk_src);
hal_status_t HAL_RCC_USART2_SetKernelClkSource(hal_rcc_usart2_clk_src_t clk_src);
#if defined(USART3)
hal_status_t HAL_RCC_USART3_SetKernelClkSource(hal_rcc_usart3_clk_src_t clk_src);
#endif /* USART3 */
hal_status_t HAL_RCC_UART4_SetKernelClkSource(hal_rcc_uart4_clk_src_t clk_src);
hal_status_t HAL_RCC_UART5_SetKernelClkSource(hal_rcc_uart5_clk_src_t clk_src);
hal_status_t HAL_RCC_UART6_SetKernelClkSource(hal_rcc_uart6_clk_src_t clk_src);
hal_status_t HAL_RCC_LPUART1_SetKernelClkSource(hal_rcc_lpuart1_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC1_SetKernelClkSource(hal_rcc_dac1_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC2_SetKernelClkSource(hal_rcc_dac2_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC5_SetKernelClkSource(hal_rcc_dac5_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC6_SetKernelClkSource(hal_rcc_dac6_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC7_SetKernelClkSource(hal_rcc_dac7_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC8_SetKernelClkSource(hal_rcc_dac8_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC9_SetKernelClkSource(hal_rcc_dac9_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC10_SetKernelClkSource(hal_rcc_dac10_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC1_SetSampleHoldClkSource(hal_rcc_dac1sh_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC2_SetSampleHoldClkSource(hal_rcc_dac2sh_clk_src_t clk_src);
hal_status_t HAL_RCC_SPI1_SetKernelClkSource(hal_rcc_spi1_clk_src_t clk_src);
hal_status_t HAL_RCC_SPI2_SetKernelClkSource(hal_rcc_spi2_clk_src_t clk_src);
#if defined(SPI3)
hal_status_t HAL_RCC_SPI3_SetKernelClkSource(hal_rcc_spi3_clk_src_t clk_src);
#endif /* SPI3 */
#if defined(PLAY1)
hal_status_t HAL_RCC_PLAY1_SetKernelClkSource(hal_rcc_play1_clk_src_t clk_src);
hal_status_t HAL_RCC_PLAY1_SetKernelClkDivider(hal_rcc_play1_clk_divider_t divider);
hal_status_t HAL_RCC_PLAY1_SetConfigKernelClk(hal_rcc_play1_clk_src_t clk_src, hal_rcc_play1_clk_divider_t divider);
#endif /* PLAY1 */
hal_status_t HAL_RCC_LPTIM1_SetKernelClkSource(hal_rcc_lptim1_clk_src_t clk_src);
#if defined(XSPI1)
hal_status_t HAL_RCC_XSPI1_SetKernelClkSource(hal_rcc_xspi1_clk_src_t clk_src);
#endif /* XSPI1 */
#if defined(UCPD1)
hal_status_t HAL_RCC_UCPD1_SetKernelClkSource(hal_rcc_ucpd1_clk_src_t clk_src);
#endif /* UCPD1 */
#if defined(USB_DRD_FS)
hal_status_t HAL_RCC_USB_SetKernelClkSource(hal_rcc_usb_clk_src_t clk_src);
#endif /* USB_DRD_FS */
#if defined(I3C1)
hal_status_t HAL_RCC_I3C1_SetKernelClkSource(hal_rcc_i3c1_clk_src_t clk_src);
#endif /* I3C1 */
hal_status_t HAL_RCC_I2C1_SetKernelClkSource(hal_rcc_i2c1_clk_src_t clk_src);
hal_status_t HAL_RCC_I2C2_SetKernelClkSource(hal_rcc_i2c2_clk_src_t clk_src);
#if defined(I2C3)
hal_status_t HAL_RCC_I2C3_SetKernelClkSource(hal_rcc_i2c3_clk_src_t clk_src);
#endif /* I2C3 */
#if defined(I2C4)
hal_status_t HAL_RCC_I2C4_SetKernelClkSource(hal_rcc_i2c4_clk_src_t clk_src);
#endif /* I2C4 */
hal_status_t HAL_RCC_ADC_SetKernelClkSource(hal_rcc_adc_clk_src_t clk_src);
hal_status_t HAL_RCC_ADC_SetKernelClkPrescaler(hal_rcc_adc_prescaler_t prescaler);
hal_status_t HAL_RCC_ADC_SetConfigKernelClk(hal_rcc_adc_clk_src_t clk_src, hal_rcc_adc_prescaler_t prescaler);
hal_status_t HAL_RCC_FDCAN_SetKernelClkSource(hal_rcc_fdcan_clk_src_t clk_src);
#if defined(POSENC1)
hal_status_t HAL_RCC_POSENC1_SetKernelClkSource(hal_rcc_posenc1_clk_src_t clk_src);
#endif /* POSENC1 */
#if defined(POSENC2)
hal_status_t HAL_RCC_POSENC2_SetKernelClkSource(hal_rcc_posenc2_clk_src_t clk_src);
#endif /* POSENC2 */
hal_status_t HAL_RCC_RTC_SetKernelClkSource(hal_rcc_rtc_clk_src_t clk_src);

hal_rcc_usart1_clk_src_t HAL_RCC_USART1_GetKernelClkSource(void);
hal_rcc_usart2_clk_src_t HAL_RCC_USART2_GetKernelClkSource(void);
#if defined(USART3)
hal_rcc_usart3_clk_src_t HAL_RCC_USART3_GetKernelClkSource(void);
#endif /* USART3 */
hal_rcc_uart4_clk_src_t HAL_RCC_UART4_GetKernelClkSource(void);
hal_rcc_uart5_clk_src_t HAL_RCC_UART5_GetKernelClkSource(void);
hal_rcc_uart6_clk_src_t HAL_RCC_UART6_GetKernelClkSource(void);
hal_rcc_lpuart1_clk_src_t HAL_RCC_LPUART1_GetKernelClkSource(void);
hal_rcc_dac1_clk_src_t HAL_RCC_DAC1_GetKernelClkSource(void);
hal_rcc_dac2_clk_src_t HAL_RCC_DAC2_GetKernelClkSource(void);
hal_rcc_dac5_clk_src_t HAL_RCC_DAC5_GetKernelClkSource(void);
hal_rcc_dac6_clk_src_t HAL_RCC_DAC6_GetKernelClkSource(void);
hal_rcc_dac7_clk_src_t HAL_RCC_DAC7_GetKernelClkSource(void);
hal_rcc_dac8_clk_src_t HAL_RCC_DAC8_GetKernelClkSource(void);
hal_rcc_dac9_clk_src_t HAL_RCC_DAC9_GetKernelClkSource(void);
hal_rcc_dac10_clk_src_t HAL_RCC_DAC10_GetKernelClkSource(void);
hal_rcc_dac1sh_clk_src_t HAL_RCC_DAC1_GetSampleHoldClkSource(void);
hal_rcc_dac2sh_clk_src_t HAL_RCC_DAC2_GetSampleHoldClkSource(void);
hal_rcc_spi1_clk_src_t HAL_RCC_SPI1_GetKernelClkSource(void);
hal_rcc_spi2_clk_src_t HAL_RCC_SPI2_GetKernelClkSource(void);
#if defined(SPI3)
hal_rcc_spi3_clk_src_t HAL_RCC_SPI3_GetKernelClkSource(void);
#endif /* SPI3 */
#if defined(PLAY1)
hal_rcc_play1_clk_src_t HAL_RCC_PLAY1_GetKernelClkSource(void);
hal_rcc_play1_clk_divider_t HAL_RCC_PLAY1_GetKernelClkDivider(void);
void HAL_RCC_PLAY1_GetConfigKernelClk(hal_rcc_play1_clk_src_t *p_clk_src, hal_rcc_play1_clk_divider_t *p_divider);
#endif /* PLAY1 */
hal_rcc_lptim1_clk_src_t HAL_RCC_LPTIM1_GetKernelClkSource(void);
#if defined(XSPI1)
hal_rcc_xspi1_clk_src_t HAL_RCC_XSPI1_GetKernelClkSource(void);
#endif /* XSPI1 */
#if defined(UCPD1)
hal_rcc_ucpd1_clk_src_t HAL_RCC_UCPD1_GetKernelClkSource(void);
#endif /* UCPD1 */
#if defined(USB_DRD_FS)
hal_rcc_usb_clk_src_t HAL_RCC_USB_GetKernelClkSource(void);
#endif /* USB_DRD_FS*/
#if defined(I3C1)
hal_rcc_i3c1_clk_src_t HAL_RCC_I3C1_GetKernelClkSource(void);
#endif /* I3C1 */
hal_rcc_i2c1_clk_src_t HAL_RCC_I2C1_GetKernelClkSource(void);
hal_rcc_i2c2_clk_src_t HAL_RCC_I2C2_GetKernelClkSource(void);
#if defined(I2C3)
hal_rcc_i2c3_clk_src_t HAL_RCC_I2C3_GetKernelClkSource(void);
#endif /* I2C3 */
#if defined(I2C4)
hal_rcc_i2c4_clk_src_t HAL_RCC_I2C4_GetKernelClkSource(void);
#endif /* I2C4 */
hal_rcc_adc_clk_src_t HAL_RCC_ADC_GetKernelClkSource(void);
hal_rcc_adc_prescaler_t HAL_RCC_ADC_GetKernelClkPrescaler(void);
void HAL_RCC_ADC_GetConfigKernelClk(hal_rcc_adc_clk_src_t *p_clk_src, hal_rcc_adc_prescaler_t *p_prescaler);
hal_rcc_fdcan_clk_src_t HAL_RCC_FDCAN_GetKernelClkSource(void);
#if defined(POSENC1)
hal_rcc_posenc1_clk_src_t HAL_RCC_POSENC1_GetKernelClkSource(void);
#endif /* POSENC1 */
#if defined(POSENC2)
hal_rcc_posenc2_clk_src_t HAL_RCC_POSENC2_GetKernelClkSource(void);
#endif /* POSENC2 */
hal_rcc_rtc_clk_src_t HAL_RCC_RTC_GetKernelClkSource(void);

#if defined(HRTIM1)
uint32_t HAL_RCC_HRTIM_GetKernelClkFreq(const HRTIM_TypeDef *hrtimx);
#endif /* HRTIM1 */
uint32_t HAL_RCC_HRTIM1_GetKernelClkFreq(void);
uint32_t HAL_RCC_USART_GetKernelClkFreq(const USART_TypeDef *usartx);
uint32_t HAL_RCC_USART1_GetKernelClkFreq(void);
uint32_t HAL_RCC_USART2_GetKernelClkFreq(void);
#if defined(USART3)
uint32_t HAL_RCC_USART3_GetKernelClkFreq(void);
#endif /* USART3 */
uint32_t HAL_RCC_UART_GetKernelClkFreq(const USART_TypeDef *uartx);
uint32_t HAL_RCC_UART4_GetKernelClkFreq(void);
uint32_t HAL_RCC_UART5_GetKernelClkFreq(void);
uint32_t HAL_RCC_UART6_GetKernelClkFreq(void);
uint32_t HAL_RCC_LPUART1_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC_GetKernelClkFreq(const DAC_TypeDef *dacx);
uint32_t HAL_RCC_DAC1_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC2_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC5_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC6_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC7_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC8_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC9_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC10_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC_GetSampleHoldClkFreq(const DAC_TypeDef *dacshx);
uint32_t HAL_RCC_DAC1_GetSampleHoldClkFreq(void);
uint32_t HAL_RCC_DAC2_GetSampleHoldClkFreq(void);
uint32_t HAL_RCC_SPI_GetKernelClkFreq(const SPI_TypeDef *spix);
uint32_t HAL_RCC_SPI1_GetKernelClkFreq(void);
uint32_t HAL_RCC_SPI2_GetKernelClkFreq(void);
#if defined(SPI3)
uint32_t HAL_RCC_SPI3_GetKernelClkFreq(void);
#endif /* SPI3 */
#if defined(PLAY1)
uint32_t HAL_RCC_PLAY_GetKernelClkFreq(const PLAY_TypeDef *playx);
uint32_t HAL_RCC_PLAY1_GetKernelClkFreq(void);
#endif /* PLAY1 */
uint32_t HAL_RCC_TIM_GetKernelClkFreq(const TIM_TypeDef *timx);
uint32_t HAL_RCC_LPTIM_GetKernelClkFreq(const LPTIM_TypeDef *lptimx);
uint32_t HAL_RCC_LPTIM1_GetKernelClkFreq(void);
#if defined(XSPI1)
uint32_t HAL_RCC_XSPI_GetKernelClkFreq(const XSPI_TypeDef *xspix);
uint32_t HAL_RCC_XSPI1_GetKernelClkFreq(void);
#endif /* XSPI1 */
#if defined(UCPD1)
uint32_t HAL_RCC_UCPD_GetKernelClkFreq(const UCPD_TypeDef *ucpdx);
uint32_t HAL_RCC_UCPD1_GetKernelClkFreq(void);
#endif /* UCPD1 */
#if defined(USB_DRD_FS)
uint32_t HAL_RCC_USB_GetKernelClkFreq(void);
#endif /* USB_DRD_FS */
#if defined(I3C1)
uint32_t HAL_RCC_I3C_GetKernelClkFreq(const I3C_TypeDef *i3cx);
uint32_t HAL_RCC_I3C1_GetKernelClkFreq(void);
#endif /* I3C1 */
uint32_t HAL_RCC_I2C_GetKernelClkFreq(const I2C_TypeDef *i2cx);
uint32_t HAL_RCC_I2C1_GetKernelClkFreq(void);
uint32_t HAL_RCC_I2C2_GetKernelClkFreq(void);
#if defined(I2C3)
uint32_t HAL_RCC_I2C3_GetKernelClkFreq(void);
#endif /* I2C3 */
#if defined(I2C4)
uint32_t HAL_RCC_I2C4_GetKernelClkFreq(void);
#endif /* I2C4 */
uint32_t HAL_RCC_ADC_GetKernelClkFreq(const ADC_TypeDef *adcx);
uint32_t HAL_RCC_ADC12_GetKernelClkFreq(void);
#if defined(ADC3)
uint32_t HAL_RCC_ADC3_GetKernelClkFreq(void);
#endif /* ADC3 */
uint32_t HAL_RCC_FDCAN_GetKernelClkFreq(void);
#if defined(POSENC1) || defined(POSENC1)
uint32_t HAL_RCC_POSENC_GetKernelClkFreq(const POSENC_TypeDef *posencx);
#endif /* POSENC1 || POSENC1 */
#if defined(POSENC1)
uint32_t HAL_RCC_POSENC1_GetKernelClkFreq(void);
#endif /* POSENC1 */
#if defined(POSENC2)
uint32_t HAL_RCC_POSENC2_GetKernelClkFreq(void);
#endif /* POSENC2 */
uint32_t HAL_RCC_COMP_GetKernelClkFreq(const COMP_TypeDef *compx);
uint32_t HAL_RCC_RTC_GetKernelClkFreq(void);
/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group5 RCC security and privileged access levels attributes management
  * This subsection provides a set of functions:
  - to set and get the security access level attribute for item(s).
  - to set and get the privileged access level attribute for item(s).
  * @{
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_RCC_SetSecAttr(uint32_t item, hal_rcc_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_rcc_sec_attr_t HAL_RCC_GetSecAttr(uint32_t item);

hal_status_t  HAL_RCC_SetPrivAttr(uint32_t item, hal_rcc_priv_attr_t priv_attr);
hal_rcc_priv_attr_t HAL_RCC_GetPrivAttr(uint32_t item);

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

#endif /* STM32G5XX_HAL_RCC_H */
