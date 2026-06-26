/**
  ******************************************************************************
  * @file    stm32g5xx_ll_rcc.h
  * @brief   Header file of RCC LL module.
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
#ifndef STM32G5XX_LL_RCC_H
#define STM32G5XX_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5XX_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup RCC_LL RCC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_LL_Private_Constants RCC Private Constants
  * @{
  */
/* Constants for LL_CLKSOURCE_xxx() macros
   31           24            16           8             0
   --------------------------------------------------------
   | Register    | Bit         |  Bit       | ClkSource   |
   | Offset      | Position    | Mask       | Config      |
   --------------------------------------------------------*/

/* Clock source register offset Vs CCIPR1 register */
#define RCC_OFFSET_CCIPR1       0x00UL
#define RCC_OFFSET_CCIPR2       0x04UL
#define RCC_OFFSET_CCIPR3       0x08UL
#define RCC_OFFSET_CCIPR4       0x0CUL
#define RCC_OFFSET_CCIPR5       0x10UL

#define LL_RCC_CONFIG_SHIFT 0UL
#define LL_RCC_MASK_SHIFT   8UL
#define LL_RCC_POS_SHIFT    16UL
#define LL_RCC_REG_SHIFT    24UL

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup RCC_LL_Private_Macros RCC Private Macros
  * @{
  */
#if !defined(UNUSED)
#define UNUSED(x) ((void)(x))
#endif /* UNUSED */

#define LL_CLKSOURCE_POS(__clksource__)     (((__clksource__) >> LL_RCC_POS_SHIFT) & 0x1FUL)
#define LL_CLKSOURCE_MASK(__clksource__)    ((((__clksource__) >> LL_RCC_MASK_SHIFT) & 0xFFUL) << \
                                             LL_CLKSOURCE_POS(__clksource__))
#define LL_CLKSOURCE_CONFIG(__clksource__)  ((((__clksource__) >> LL_RCC_CONFIG_SHIFT) & 0xFFUL) << \
                                             LL_CLKSOURCE_POS(__clksource__))
#define LL_CLKSOURCE_REG(__clksource__)     (((__clksource__) >> LL_RCC_REG_SHIFT) & 0xFFUL)

#define LL_CLKSOURCE(__reg__, __pos__, __msk__, __clk__) ((uint32_t)((((__msk__) >> (__pos__)) << LL_RCC_MASK_SHIFT) | \
                                                                     (( __pos__              ) << LL_RCC_POS_SHIFT)  | \
                                                                     (( __reg__              ) << LL_RCC_REG_SHIFT)  | \
                                                                     (((__clk__) >> (__pos__)) << LL_RCC_CONFIG_SHIFT)))
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_LL_Exported_Constants LL RCC Constants
  * @{
  */

/** @defgroup RCC_LL_EC_HSE External HSE clock Type
  * @{
  */
#define LL_RCC_HSE_ANALOG_TYPE  0U            /*!< Analog selected as HSE external clock type  */
#define LL_RCC_HSE_DIGITAL_TYPE RCC_CR_HSEEXT /*!< Digital selected as HSE external clock type */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSE LSE oscillator driving capability
  * @{
  */
#define LL_RCC_LSEDRIVE_MEDIUMLOW  0U                 /*!< Crystal mode medium-low driving capability  */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH RCC_RTCCR_LSEDRV_1 /*!< Crystal mode medium-high driving capability */
#define LL_RCC_LSEDRIVE_HIGH       RCC_RTCCR_LSEDRV   /*!< Crystal mode high driving capability        */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_HSI HSI clock divider
  * @{
  */
#define LL_RCC_HSI_DIV_1 0U              /*!< HSI not divided  */
#define LL_RCC_HSI_DIV_2 RCC_CR_HSIDIV_0 /*!< HSI divided by 2 */
#define LL_RCC_HSI_DIV_4 RCC_CR_HSIDIV_1 /*!< HSI divided by 4 */
#define LL_RCC_HSI_DIV_8 RCC_CR_HSIDIV   /*!< HSI divided by 8 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE System clock switch
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_HSI  0U                /*!< HSI clock used as system clock  */
#define LL_RCC_SYS_CLKSOURCE_HSE  RCC_CFGR1_SYSSW_0 /*!< HSE clock used as system clock  */
#define LL_RCC_SYS_CLKSOURCE_PLL1 RCC_CFGR1_SYSSW_1 /*!< PLL1 clock used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE_STATUS System clock switch status
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSI  0U                 /*!< HSI clock used as system clock   */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSE  RCC_CFGR1_SYSSWS_0 /*!< HSE clock used as system clock   */
#define LL_RCC_SYS_CLKSOURCE_STATUS_PLL1 RCC_CFGR1_SYSSWS_1 /*!< PLL1P clock used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSTICK_CLKSOURCE SYSTICK clock source selection
  * @{
  */
#define LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8  0U                      /*!< HCLK_DIV8 clock used as SYSTICK clock */
#define LL_RCC_SYSTICK_CLKSOURCE_LSI       RCC_CCIPR3_SYSTICKSEL_0 /*!< LSI clock used as SYSTICK clock       */
#define LL_RCC_SYSTICK_CLKSOURCE_LSE       RCC_CCIPR3_SYSTICKSEL_1 /*!< LSE clock used as SYSTICK clock       */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_SYSCLK_DIV AHB prescaler
  * @{
  */
#define LL_RCC_HCLK_PRESCALER_1   0U                                                       /*!< SYSCLK not divided    */
#define LL_RCC_HCLK_PRESCALER_2   RCC_CFGR2_HPRE_3                                         /*!< SYSCLK divided by 2   */
#define LL_RCC_HCLK_PRESCALER_4   (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_0)                    /*!< SYSCLK divided by 4   */
#define LL_RCC_HCLK_PRESCALER_8   (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_1)                    /*!< SYSCLK divided by 8   */
#define LL_RCC_HCLK_PRESCALER_16  (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_1 | RCC_CFGR2_HPRE_0) /*!< SYSCLK divided by 16  */
#define LL_RCC_HCLK_PRESCALER_64  (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2)                    /*!< SYSCLK divided by 64  */
#define LL_RCC_HCLK_PRESCALER_128 (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_0) /*!< SYSCLK divided by 128 */
#define LL_RCC_HCLK_PRESCALER_256 (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1) /*!< SYSCLK divided by 256 */
#define LL_RCC_HCLK_PRESCALER_512 RCC_CFGR2_HPRE                                           /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB1_DIV APB low-speed prescaler (APB1)
  * @{
  */
#define LL_RCC_APB1_PRESCALER_1  0U                                      /*!< HCLK not divided   */
#define LL_RCC_APB1_PRESCALER_2  RCC_CFGR2_PPRE1_2                       /*!< HCLK divided by 2  */
#define LL_RCC_APB1_PRESCALER_4  (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_0) /*!< HCLK divided by 4  */
#define LL_RCC_APB1_PRESCALER_8  (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1) /*!< HCLK divided by 8  */
#define LL_RCC_APB1_PRESCALER_16 RCC_CFGR2_PPRE1                         /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB2_DIV APB low-speed prescaler (APB2)
  * @{
  */
#define LL_RCC_APB2_PRESCALER_1  0U                                      /*!< HCLK not divided   */
#define LL_RCC_APB2_PRESCALER_2  RCC_CFGR2_PPRE2_2                       /*!< HCLK divided by 2  */
#define LL_RCC_APB2_PRESCALER_4  (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_0) /*!< HCLK divided by 4  */
#define LL_RCC_APB2_PRESCALER_8  (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_1) /*!< HCLK divided by 8  */
#define LL_RCC_APB2_PRESCALER_16 RCC_CFGR2_PPRE2                         /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB3_DIV APB low-speed prescaler (APB3)
  * @{
  */
#define LL_RCC_APB3_PRESCALER_1  0U                                      /*!< HCLK not divided   */
#define LL_RCC_APB3_PRESCALER_2  RCC_CFGR2_PPRE3_2                       /*!< HCLK divided by 2  */
#define LL_RCC_APB3_PRESCALER_4  (RCC_CFGR2_PPRE3_2 | RCC_CFGR2_PPRE3_0) /*!< HCLK divided by 4  */
#define LL_RCC_APB3_PRESCALER_8  (RCC_CFGR2_PPRE3_2 | RCC_CFGR2_PPRE3_1) /*!< HCLK divided by 8  */
#define LL_RCC_APB3_PRESCALER_16 RCC_CFGR2_PPRE3                         /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ICLK Iclk
  * @{
  */
#define LL_RCC_ICLK1   0x00000000U            /*!< ICLK 1 */
#define LL_RCC_ICLK2   0x00000001U            /*!< ICLK 2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ICLK_DIV Intermediate clock division
  * @{
  */
#define LL_RCC_ICLK_DIV_5  0U                    /*!< ICLK divided by 5 */
#define LL_RCC_ICLK_DIV_3  RCC_PLL1CFGR_ICLK1DIV /*!< ICLK divided by 3 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1SOURCE MCO1 SOURCE selection
  * @{
  */
#define LL_RCC_MCO1SOURCE_HSI   (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | 0U)                                          /*!< HSI selection as MCO1 source   */
#define LL_RCC_MCO1SOURCE_LSE   (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | RCC_CFGR1_MCO1SEL_0)                         /*!< LSE selection as MCO1 source   */
#define LL_RCC_MCO1SOURCE_HSE   (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | RCC_CFGR1_MCO1SEL_1)                         /*!< HSE selection as MCO1 source   */
#define LL_RCC_MCO1SOURCE_PLL1Q (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | (RCC_CFGR1_MCO1SEL_1 | RCC_CFGR1_MCO1SEL_0)) /*!< PLL1Q selection as MCO1 source  */
#define LL_RCC_MCO1SOURCE_HSI48 (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | RCC_CFGR1_MCO1SEL_2)                         /*!< HSI48 selection as MCO1 source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2SOURCE MCO2 SOURCE selection
  * @{
  */
#define LL_RCC_MCO2SOURCE_SYSCLK (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | 0U)                                          /*!< SYSTEM selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_PLL2P  (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | RCC_CFGR1_MCO2SEL_0)                         /*!< PLL2P selection as MCO2 source   */
#define LL_RCC_MCO2SOURCE_HSE    (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | RCC_CFGR1_MCO2SEL_1)                         /*!< HSE selection as MCO2 source    */
#define LL_RCC_MCO2SOURCE_PLL1P  (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | (RCC_CFGR1_MCO2SEL_1 | RCC_CFGR1_MCO2SEL_0)) /*!< PLL1P selection as MCO2 source   */
#define LL_RCC_MCO2SOURCE_LSI    (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | RCC_CFGR1_MCO2SEL_2)                         /*!< LSI selection as MCO2 source    */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1_DIV MCO1 prescaler
  * @{
  */
#define LL_RCC_MCO1SOURCE_NOCLOCK (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | 0U)                                                                /*!< MCO1 output disabled, no clock on MCO1 */
#define LL_RCC_MCO1_PRESCALER_1   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_0)                                               /*!< MCO1 not divided                       */
#define LL_RCC_MCO1_PRESCALER_2   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_1)                                               /*!< MCO1 divided by 2                      */
#define LL_RCC_MCO1_PRESCALER_3   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | (RCC_CFGR1_MCO1PRE_1 | RCC_CFGR1_MCO1PRE_0))                       /*!< MCO1 divided by 3                      */
#define LL_RCC_MCO1_PRESCALER_4   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_2)                                               /*!< MCO1 divided by 4                      */
#define LL_RCC_MCO1_PRESCALER_5   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | (RCC_CFGR1_MCO1PRE_2 | RCC_CFGR1_MCO1PRE_0))                       /*!< MCO1 divided by 5                      */
#define LL_RCC_MCO1_PRESCALER_6   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | (RCC_CFGR1_MCO1PRE_2 | RCC_CFGR1_MCO1PRE_1))                       /*!< MCO1 divided by 6                      */
#define LL_RCC_MCO1_PRESCALER_7   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | (RCC_CFGR1_MCO1PRE_2 | RCC_CFGR1_MCO1PRE_1 | RCC_CFGR1_MCO1PRE_0)) /*!< MCO1 divided by 7                      */
#define LL_RCC_MCO1_PRESCALER_8   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_3)                                               /*!< MCO1 divided by 8                      */
#define LL_RCC_MCO1_PRESCALER_9   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | (RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_0))                       /*!< MCO1 divided by 9                      */
#define LL_RCC_MCO1_PRESCALER_10  (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | (RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_1))                       /*!< MCO1 divided by 10                     */
#define LL_RCC_MCO1_PRESCALER_11  (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | (RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_1 | RCC_CFGR1_MCO1PRE_0)) /*!< MCO1 divided by 11                     */
#define LL_RCC_MCO1_PRESCALER_12  (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | (RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_2))                       /*!< MCO1 divided by 12                     */
#define LL_RCC_MCO1_PRESCALER_13  (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | (RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_2 | RCC_CFGR1_MCO1PRE_0)) /*!< MCO1 divided by 13                     */
#define LL_RCC_MCO1_PRESCALER_14  (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | (RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_2 | RCC_CFGR1_MCO1PRE_1)) /*!< MCO1 divided by 14                     */
#define LL_RCC_MCO1_PRESCALER_15  (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE)                                                 /*!< MCO1 divided by 15                     */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2_DIV MCO2 prescaler
  * @{
  */
#define LL_RCC_MCO2SOURCE_NOCLOCK (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | 0U)                                                                /*!< MCO2 output disabled, no clock on MCO2 */
#define LL_RCC_MCO2_PRESCALER_1   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_0)                                               /*!< MCO2 not divided                       */
#define LL_RCC_MCO2_PRESCALER_2   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_1)                                               /*!< MCO2 divided by 2                      */
#define LL_RCC_MCO2_PRESCALER_3   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | (RCC_CFGR1_MCO2PRE_1 | RCC_CFGR1_MCO2PRE_0))                       /*!< MCO2 divided by 3                      */
#define LL_RCC_MCO2_PRESCALER_4   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_2)                                               /*!< MCO2 divided by 4                      */
#define LL_RCC_MCO2_PRESCALER_5   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | (RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_0))                       /*!< MCO2 divided by 5                      */
#define LL_RCC_MCO2_PRESCALER_6   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | (RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_1))                       /*!< MCO2 divided by 6                      */
#define LL_RCC_MCO2_PRESCALER_7   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | (RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_1 | RCC_CFGR1_MCO2PRE_0)) /*!< MCO2 divided by 7                      */
#define LL_RCC_MCO2_PRESCALER_8   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_3)                                               /*!< MCO2 divided by 8                      */
#define LL_RCC_MCO2_PRESCALER_9   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | (RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_0))                       /*!< MCO2 divided by 9                      */
#define LL_RCC_MCO2_PRESCALER_10  (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | (RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_1))                       /*!< MCO2 divided by 10                     */
#define LL_RCC_MCO2_PRESCALER_11  (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | (RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_1 | RCC_CFGR1_MCO2PRE_0)) /*!< MCO2 divided by 11                     */
#define LL_RCC_MCO2_PRESCALER_12  (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | (RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_2))                       /*!< MCO2 divided by 12                     */
#define LL_RCC_MCO2_PRESCALER_13  (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | (RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_0)) /*!< MCO2 divided by 13                     */
#define LL_RCC_MCO2_PRESCALER_14  (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | (RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_1)) /*!< MCO2 divided by 14                     */
#define LL_RCC_MCO2_PRESCALER_15  (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE)                                                 /*!< MCO2 divided by 15                     */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_CLKSOURCE RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_NONE    0U                 /*!< No clock used as RTC clock                 */
#define LL_RCC_RTC_CLKSOURCE_LSE     RCC_RTCCR_RTCSEL_0 /*!< LSE oscillator clock used as RTC clock     */
#define LL_RCC_RTC_CLKSOURCE_LSI     RCC_RTCCR_RTCSEL_1 /*!< LSI oscillator clock used as RTC clock     */
#define LL_RCC_RTC_CLKSOURCE_HSE_DIV RCC_RTCCR_RTCSEL   /*!< HSE oscillator clock divided by RTCPRE used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLAY1_DIVIDER  PLAY1 Divider
  * @{
  */
#define LL_RCC_PLAY1_DIVIDER_1      0U                                                                      /*!< PLAY kernel clock not divided      */
#define LL_RCC_PLAY1_DIVIDER_2      RCC_CCIPR3_PLAY1DIV_0                                                   /*!< PLAY kernel clock divided by 2     */
#define LL_RCC_PLAY1_DIVIDER_4      RCC_CCIPR3_PLAY1DIV_1                                                   /*!< PLAY kernel clock divided by 4     */
#define LL_RCC_PLAY1_DIVIDER_8      (RCC_CCIPR3_PLAY1DIV_1 | RCC_CCIPR3_PLAY1DIV_0)                         /*!< PLAY kernel clock divided by 8     */
#define LL_RCC_PLAY1_DIVIDER_16      RCC_CCIPR3_PLAY1DIV_2                                                  /*!< PLAY kernel clock divided by 16    */
#define LL_RCC_PLAY1_DIVIDER_32     (RCC_CCIPR3_PLAY1DIV_2 | RCC_CCIPR3_PLAY1DIV_0)                         /*!< PLAY kernel clock divided by 32    */
#define LL_RCC_PLAY1_DIVIDER_64     (RCC_CCIPR3_PLAY1DIV_2 | RCC_CCIPR3_PLAY1DIV_1)                         /*!< PLAY kernel clock divided by 64    */
#define LL_RCC_PLAY1_DIVIDER_128    (RCC_CCIPR3_PLAY1DIV_2 | RCC_CCIPR3_PLAY1DIV_1 | RCC_CCIPR3_PLAY1DIV_0) /*!< PLAY kernel clock divided by 128   */
#define LL_RCC_PLAY1_DIVIDER_256    RCC_CCIPR3_PLAY1DIV_3                                                   /*!< PLAY kernel clock divided by 256   */
#define LL_RCC_PLAY1_DIVIDER_512    (RCC_CCIPR3_PLAY1DIV_3 | RCC_CCIPR3_PLAY1DIV_0)                         /*!< PLAY kernel clock divided by 512   */
#define LL_RCC_PLAY1_DIVIDER_1024   (RCC_CCIPR3_PLAY1DIV_3 | RCC_CCIPR3_PLAY1DIV_1)                         /*!< PLAY kernel clock divided by 1024  */
#define LL_RCC_PLAY1_DIVIDER_2048   (RCC_CCIPR3_PLAY1DIV_3 | RCC_CCIPR3_PLAY1DIV_1 | RCC_CCIPR3_PLAY1DIV_0) /*!< PLAY kernel clock divided by 2048  */
#define LL_RCC_PLAY1_DIVIDER_4096   (RCC_CCIPR3_PLAY1DIV_3 | RCC_CCIPR3_PLAY1DIV_2)                         /*!< PLAY kernel clock divided by 4096  */
#define LL_RCC_PLAY1_DIVIDER_8192   (RCC_CCIPR3_PLAY1DIV_3 | RCC_CCIPR3_PLAY1DIV_2 | RCC_CCIPR3_PLAY1DIV_0) /*!< PLAY kernel clock divided by 8192  */
#define LL_RCC_PLAY1_DIVIDER_16384  (RCC_CCIPR3_PLAY1DIV_3 | RCC_CCIPR3_PLAY1DIV_2 | RCC_CCIPR3_PLAY1DIV_1) /*!< PLAY kernel clock divided by 16384 */
#define LL_RCC_PLAY1_DIVIDER_32768  (RCC_CCIPR3_PLAY1DIV_3 |\
                                     RCC_CCIPR3_PLAY1DIV_2 | RCC_CCIPR3_PLAY1DIV_1 | RCC_CCIPR3_PLAY1DIV_0) /*!< PLAY kernel clock divided by 32768 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC_PRESCALER  ADC Prescaler
  * @{
  */
#define LL_RCC_ADC_PRESCALER_1    0U
#define LL_RCC_ADC_PRESCALER_2    RCC_CCIPR5_ADCDIV_0
#define LL_RCC_ADC_PRESCALER_4    RCC_CCIPR5_ADCDIV_1
#define LL_RCC_ADC_PRESCALER_6    (RCC_CCIPR5_ADCDIV_1 | RCC_CCIPR5_ADCDIV_0)
#define LL_RCC_ADC_PRESCALER_8    RCC_CCIPR5_ADCDIV_2
#define LL_RCC_ADC_PRESCALER_10   (RCC_CCIPR5_ADCDIV_2 | RCC_CCIPR5_ADCDIV_0)
#define LL_RCC_ADC_PRESCALER_12   (RCC_CCIPR5_ADCDIV_2 | RCC_CCIPR5_ADCDIV_1)
#define LL_RCC_ADC_PRESCALER_16   (RCC_CCIPR5_ADCDIV_2 | RCC_CCIPR5_ADCDIV_1 | RCC_CCIPR5_ADCDIV_0)
#define LL_RCC_ADC_PRESCALER_32   RCC_CCIPR5_ADCDIV_3
#define LL_RCC_ADC_PRESCALER_64   (RCC_CCIPR5_ADCDIV_3 | RCC_CCIPR5_ADCDIV_0)
#define LL_RCC_ADC_PRESCALER_128  (RCC_CCIPR5_ADCDIV_3 | RCC_CCIPR5_ADCDIV_1)
#define LL_RCC_ADC_PRESCALER_256  (RCC_CCIPR5_ADCDIV_3 | RCC_CCIPR5_ADCDIV_1 | RCC_CCIPR5_ADCDIV_0)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USARTx_CLKSOURCE Peripheral USARTx clock source selection
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE_PCLK2  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, 0UL)                                             /*!< PCLK2 clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, RCC_CCIPR1_USART1SEL_0)                          /*!< ICLK1 clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, RCC_CCIPR1_USART1SEL_1)                          /*!< PLL2Q clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, RCC_CCIPR1_USART1SEL_1 | RCC_CCIPR1_USART1SEL_0) /*!< HSE clock used as USART1 clock source   */
#define LL_RCC_USART1_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, RCC_CCIPR1_USART1SEL_2)                          /*!< HSI clock used as USART1 clock source   */
#define LL_RCC_USART1_CLKSOURCE_LSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, RCC_CCIPR1_USART1SEL_2 | RCC_CCIPR1_USART1SEL_0) /*!< LSE clock used as USART1 clock source   */
#define LL_RCC_USART1_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, RCC_CCIPR1_USART1SEL)                            /*!< USART1 kernel clock is disabled         */

#define LL_RCC_USART2_CLKSOURCE_PCLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, 0UL)                                             /*!< PCLK1 clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, RCC_CCIPR1_USART2SEL_0)                          /*!< ICLK1 clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, RCC_CCIPR1_USART2SEL_1)                          /*!< PLL2Q clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, RCC_CCIPR1_USART2SEL_1 | RCC_CCIPR1_USART2SEL_0) /*!< HSE clock used as USART2 clock source   */
#define LL_RCC_USART2_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, RCC_CCIPR1_USART2SEL_2)                          /*!< HSI clock used as USART2 clock source   */
#define LL_RCC_USART2_CLKSOURCE_LSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, RCC_CCIPR1_USART2SEL_2 | RCC_CCIPR1_USART2SEL_0) /*!< LSE clock used as USART2 clock source   */
#define LL_RCC_USART2_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, RCC_CCIPR1_USART2SEL)                            /*!< USART2 kernel clock is disabled         */

#if defined(USART3)
#define LL_RCC_USART3_CLKSOURCE_PCLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, 0UL)                                             /*!< PCLK1 clock used as USART3 clock source */
#define LL_RCC_USART3_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, RCC_CCIPR1_USART3SEL_0)                          /*!< ICLK1 clock used as USART3 clock source */
#define LL_RCC_USART3_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, RCC_CCIPR1_USART3SEL_1)                          /*!< PLL2Q clock used as USART3 clock source */
#define LL_RCC_USART3_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, RCC_CCIPR1_USART3SEL_1 | RCC_CCIPR1_USART3SEL_0) /*!< HSE clock used as USART3 clock source   */
#define LL_RCC_USART3_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, RCC_CCIPR1_USART3SEL_2)                          /*!< HSI clock used as USART3 clock source   */
#define LL_RCC_USART3_CLKSOURCE_LSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, RCC_CCIPR1_USART3SEL_2 | RCC_CCIPR1_USART3SEL_0) /*!< LSE clock used as USART3 clock source   */
#define LL_RCC_USART3_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, RCC_CCIPR1_USART3SEL)                            /*!< USART3 kernel clock is disabled         */
#endif /* USART3 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_UARTx_CLKSOURCE Peripheral UARTx clock source selection
  * @{
  */
#define LL_RCC_UART4_CLKSOURCE_PCLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, 0UL)                                           /*!< PCLK1 clock used as UART4 clock source */
#define LL_RCC_UART4_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, RCC_CCIPR1_UART4SEL_0)                         /*!< ICLK1 clock used as UART4 clock source */
#define LL_RCC_UART4_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, RCC_CCIPR1_UART4SEL_1)                         /*!< PLL2Q clock used as UART4 clock source */
#define LL_RCC_UART4_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, RCC_CCIPR1_UART4SEL_1 | RCC_CCIPR1_UART4SEL_0) /*!< HSE clock used as UART4 clock source   */
#define LL_RCC_UART4_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, RCC_CCIPR1_UART4SEL_2)                         /*!< HSI clock used as UART4 clock source   */
#define LL_RCC_UART4_CLKSOURCE_LSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, RCC_CCIPR1_UART4SEL_2 | RCC_CCIPR1_UART4SEL_0) /*!< LSE clock used as UART4 clock source   */
#define LL_RCC_UART4_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, RCC_CCIPR1_UART4SEL)                           /*!< UART4 kernel clock is disabled         */

#define LL_RCC_UART5_CLKSOURCE_PCLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, 0UL)                                           /*!< PCLK1 clock used as UART5 clock source */
#define LL_RCC_UART5_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, RCC_CCIPR1_UART5SEL_0)                         /*!< ICLK1 clock used as UART5 clock source */
#define LL_RCC_UART5_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, RCC_CCIPR1_UART5SEL_1)                         /*!< PLL2Q clock used as UART5 clock source */
#define LL_RCC_UART5_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, RCC_CCIPR1_UART5SEL_1 | RCC_CCIPR1_UART5SEL_0) /*!< HSE clock used as UART5 clock source   */
#define LL_RCC_UART5_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, RCC_CCIPR1_UART5SEL_2)                         /*!< HSI clock used as UART5 clock source   */
#define LL_RCC_UART5_CLKSOURCE_LSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, RCC_CCIPR1_UART5SEL_2 | RCC_CCIPR1_UART5SEL_0) /*!< LSE clock used as UART5 clock source   */
#define LL_RCC_UART5_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, RCC_CCIPR1_UART5SEL)                           /*!< UART5 kernel clock is disabled         */

#define LL_RCC_UART6_CLKSOURCE_PCLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART6SEL_Pos, RCC_CCIPR1_UART6SEL, 0UL)                                           /*!< PCLK1 clock used as UART6 clock source */
#define LL_RCC_UART6_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART6SEL_Pos, RCC_CCIPR1_UART6SEL, RCC_CCIPR1_UART6SEL_0)                         /*!< ICLK1 clock used as UART6 clock source */
#define LL_RCC_UART6_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART6SEL_Pos, RCC_CCIPR1_UART6SEL, RCC_CCIPR1_UART6SEL_1)                         /*!< PLL2Q clock used as UART6 clock source */
#define LL_RCC_UART6_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART6SEL_Pos, RCC_CCIPR1_UART6SEL, RCC_CCIPR1_UART6SEL_1 | RCC_CCIPR1_UART6SEL_0) /*!< HSE clock used as UART6 clock source   */
#define LL_RCC_UART6_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART6SEL_Pos, RCC_CCIPR1_UART6SEL, RCC_CCIPR1_UART6SEL_2)                         /*!< HSI clock used as UART6 clock source   */
#define LL_RCC_UART6_CLKSOURCE_LSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART6SEL_Pos, RCC_CCIPR1_UART6SEL, RCC_CCIPR1_UART6SEL_2 | RCC_CCIPR1_UART6SEL_0) /*!< LSE clock used as UART6 clock source   */
#define LL_RCC_UART6_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART6SEL_Pos, RCC_CCIPR1_UART6SEL, RCC_CCIPR1_UART6SEL)                           /*!< UART6 kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART_CLKSOURCE Peripheral LPUART clock source selection
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE_PCLK3  0U                                                  /*!< PCLK3 clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_ICLK1  RCC_CCIPR1_LPUART1SEL_0                             /*!< ICLK1 clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_PLL2Q  RCC_CCIPR1_LPUART1SEL_1                             /*!< PLL2Q clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_HSE    (RCC_CCIPR1_LPUART1SEL_1 | RCC_CCIPR1_LPUART1SEL_0) /*!< HSE clock used as LPUART1 clock source   */
#define LL_RCC_LPUART1_CLKSOURCE_HSI    RCC_CCIPR1_LPUART1SEL_2                             /*!< HSI clock used as LPUART1 clock source   */
#define LL_RCC_LPUART1_CLKSOURCE_LSE    (RCC_CCIPR1_LPUART1SEL_2 | RCC_CCIPR1_LPUART1SEL_0) /*!< LSE clock used as LPUART1 clock source   */
#define LL_RCC_LPUART1_CLKSOURCE_NONE   RCC_CCIPR1_LPUART1SEL                               /*!< LPUART1 kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DACx_CLKSOURCE Peripheral DACx clock source selection
  * @{
  */
#define LL_RCC_DAC1_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SEL_Pos, RCC_CCIPR2_DAC1SEL, 0UL)                                         /*!< TIM clock used as DAC1 clock source   */
#define LL_RCC_DAC1_CLKSOURCE_HRTIM  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SEL_Pos, RCC_CCIPR2_DAC1SEL, RCC_CCIPR2_DAC1SEL_0)                        /*!< HRTIM clock used as DAC1 clock source */
#define LL_RCC_DAC1_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SEL_Pos, RCC_CCIPR2_DAC1SEL, RCC_CCIPR2_DAC1SEL_1)                        /*!< ADC clock used as DAC1 clock source   */
#define LL_RCC_DAC1_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SEL_Pos, RCC_CCIPR2_DAC1SEL, RCC_CCIPR2_DAC1SEL_1 | RCC_CCIPR2_DAC1SEL_0) /*!< HSE clock used as DAC1 clock source   */
#define LL_RCC_DAC1_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SEL_Pos, RCC_CCIPR2_DAC1SEL, RCC_CCIPR2_DAC1SEL_2)                        /*!< HSI clock used as DAC1 clock source   */
#define LL_RCC_DAC1_CLKSOURCE_PLL1Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SEL_Pos, RCC_CCIPR2_DAC1SEL, RCC_CCIPR2_DAC1SEL_2 | RCC_CCIPR2_DAC1SEL_0) /*!< PLL1Q clock used as DAC1 clock source */
#define LL_RCC_DAC1_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SEL_Pos, RCC_CCIPR2_DAC1SEL, RCC_CCIPR2_DAC1SEL_2 | RCC_CCIPR2_DAC1SEL_1) /*!< PLL2Q clock used as DAC1 clock source */
#define LL_RCC_DAC1_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SEL_Pos, RCC_CCIPR2_DAC1SEL, RCC_CCIPR2_DAC1SEL)                          /*!< DAC1 kernel clock is disabled         */

#define LL_RCC_DAC2_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SEL_Pos, RCC_CCIPR2_DAC2SEL, 0UL)                                         /*!< TIM clock used as DAC2 clock source   */
#define LL_RCC_DAC2_CLKSOURCE_HRTIM  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SEL_Pos, RCC_CCIPR2_DAC2SEL, RCC_CCIPR2_DAC2SEL_0)                        /*!< HRTIM clock used as DAC2 clock source */
#define LL_RCC_DAC2_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SEL_Pos, RCC_CCIPR2_DAC2SEL, RCC_CCIPR2_DAC2SEL_1)                        /*!< ADC clock used as DAC2 clock source   */
#define LL_RCC_DAC2_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SEL_Pos, RCC_CCIPR2_DAC2SEL, RCC_CCIPR2_DAC2SEL_1 | RCC_CCIPR2_DAC2SEL_0) /*!< HSE clock used as DAC2 clock source   */
#define LL_RCC_DAC2_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SEL_Pos, RCC_CCIPR2_DAC2SEL, RCC_CCIPR2_DAC2SEL_2)                        /*!< HSI clock used as DAC2 clock source   */
#define LL_RCC_DAC2_CLKSOURCE_PLL1Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SEL_Pos, RCC_CCIPR2_DAC2SEL, RCC_CCIPR2_DAC2SEL_2 | RCC_CCIPR2_DAC2SEL_0) /*!< PLL1Q clock used as DAC2 clock source */
#define LL_RCC_DAC2_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SEL_Pos, RCC_CCIPR2_DAC2SEL, RCC_CCIPR2_DAC2SEL_2 | RCC_CCIPR2_DAC2SEL_1) /*!< PLL2Q clock used as DAC2 clock source */
#define LL_RCC_DAC2_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SEL_Pos, RCC_CCIPR2_DAC2SEL, RCC_CCIPR2_DAC2SEL)                          /*!< DAC2 kernel clock is disabled         */

#define LL_RCC_DAC5_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC5SEL_Pos, RCC_CCIPR2_DAC5SEL, 0UL)                                         /*!< TIM clock used as DAC5 clock source   */
#define LL_RCC_DAC5_CLKSOURCE_HRTIM  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC5SEL_Pos, RCC_CCIPR2_DAC5SEL, RCC_CCIPR2_DAC5SEL_0)                        /*!< HRTIM clock used as DAC5 clock source */
#define LL_RCC_DAC5_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC5SEL_Pos, RCC_CCIPR2_DAC5SEL, RCC_CCIPR2_DAC5SEL_1)                        /*!< ADC clock used as DAC5 clock source   */
#define LL_RCC_DAC5_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC5SEL_Pos, RCC_CCIPR2_DAC5SEL, RCC_CCIPR2_DAC5SEL_1 | RCC_CCIPR2_DAC5SEL_0) /*!< HSE clock used as DAC5 clock source   */
#define LL_RCC_DAC5_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC5SEL_Pos, RCC_CCIPR2_DAC5SEL, RCC_CCIPR2_DAC5SEL_2)                        /*!< HSI clock used as DAC5 clock source   */
#define LL_RCC_DAC5_CLKSOURCE_PLL1Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC5SEL_Pos, RCC_CCIPR2_DAC5SEL, RCC_CCIPR2_DAC5SEL_2 | RCC_CCIPR2_DAC5SEL_0) /*!< PLL1Q clock used as DAC5 clock source */
#define LL_RCC_DAC5_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC5SEL_Pos, RCC_CCIPR2_DAC5SEL, RCC_CCIPR2_DAC5SEL_2 | RCC_CCIPR2_DAC5SEL_1) /*!< PLL2Q clock used as DAC5 clock source */
#define LL_RCC_DAC5_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC5SEL_Pos, RCC_CCIPR2_DAC5SEL, RCC_CCIPR2_DAC5SEL)                          /*!< DAC5 kernel clock is disabled         */

#define LL_RCC_DAC6_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC6SEL_Pos, RCC_CCIPR2_DAC6SEL, 0UL)                                         /*!< TIM clock used as DAC6 clock source   */
#define LL_RCC_DAC6_CLKSOURCE_HRTIM  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC6SEL_Pos, RCC_CCIPR2_DAC6SEL, RCC_CCIPR2_DAC6SEL_0)                        /*!< HRTIM clock used as DAC6 clock source */
#define LL_RCC_DAC6_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC6SEL_Pos, RCC_CCIPR2_DAC6SEL, RCC_CCIPR2_DAC6SEL_1)                        /*!< ADC clock used as DAC6 clock source   */
#define LL_RCC_DAC6_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC6SEL_Pos, RCC_CCIPR2_DAC6SEL, RCC_CCIPR2_DAC6SEL_1 | RCC_CCIPR2_DAC6SEL_0) /*!< HSE clock used as DAC6 clock source   */
#define LL_RCC_DAC6_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC6SEL_Pos, RCC_CCIPR2_DAC6SEL, RCC_CCIPR2_DAC6SEL_2)                        /*!< HSI clock used as DAC6 clock source   */
#define LL_RCC_DAC6_CLKSOURCE_PLL1Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC6SEL_Pos, RCC_CCIPR2_DAC6SEL, RCC_CCIPR2_DAC6SEL_2 | RCC_CCIPR2_DAC6SEL_0) /*!< PLL1Q clock used as DAC6 clock source */
#define LL_RCC_DAC6_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC6SEL_Pos, RCC_CCIPR2_DAC6SEL, RCC_CCIPR2_DAC6SEL_2 | RCC_CCIPR2_DAC6SEL_1) /*!< PLL2Q clock used as DAC6 clock source */
#define LL_RCC_DAC6_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC6SEL_Pos, RCC_CCIPR2_DAC6SEL, RCC_CCIPR2_DAC6SEL)                          /*!< DAC6 kernel clock is disabled         */

#define LL_RCC_DAC7_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC7SEL_Pos, RCC_CCIPR2_DAC7SEL, 0UL)                                         /*!< TIM clock used as DAC7 clock source   */
#define LL_RCC_DAC7_CLKSOURCE_HRTIM  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC7SEL_Pos, RCC_CCIPR2_DAC7SEL, RCC_CCIPR2_DAC7SEL_0)                        /*!< HRTIM clock used as DAC7 clock source */
#define LL_RCC_DAC7_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC7SEL_Pos, RCC_CCIPR2_DAC7SEL, RCC_CCIPR2_DAC7SEL_1)                        /*!< ADC clock used as DAC7 clock source   */
#define LL_RCC_DAC7_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC7SEL_Pos, RCC_CCIPR2_DAC7SEL, RCC_CCIPR2_DAC7SEL_1 | RCC_CCIPR2_DAC7SEL_0) /*!< HSE clock used as DAC7 clock source   */
#define LL_RCC_DAC7_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC7SEL_Pos, RCC_CCIPR2_DAC7SEL, RCC_CCIPR2_DAC7SEL_2)                        /*!< HSI clock used as DAC7 clock source   */
#define LL_RCC_DAC7_CLKSOURCE_PLL1Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC7SEL_Pos, RCC_CCIPR2_DAC7SEL, RCC_CCIPR2_DAC7SEL_2 | RCC_CCIPR2_DAC7SEL_0) /*!< PLL1Q clock used as DAC7 clock source */
#define LL_RCC_DAC7_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC7SEL_Pos, RCC_CCIPR2_DAC7SEL, RCC_CCIPR2_DAC7SEL_2 | RCC_CCIPR2_DAC7SEL_1) /*!< PLL2Q clock used as DAC7 clock source */
#define LL_RCC_DAC7_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC7SEL_Pos, RCC_CCIPR2_DAC7SEL, RCC_CCIPR2_DAC7SEL)                          /*!< DAC7 kernel clock is disabled         */

#define LL_RCC_DAC8_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC8SEL_Pos, RCC_CCIPR2_DAC8SEL, 0UL)                                         /*!< TIM clock used as DAC8 clock source   */
#define LL_RCC_DAC8_CLKSOURCE_HRTIM  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC8SEL_Pos, RCC_CCIPR2_DAC8SEL, RCC_CCIPR2_DAC8SEL_0)                        /*!< HRTIM clock used as DAC8 clock source */
#define LL_RCC_DAC8_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC8SEL_Pos, RCC_CCIPR2_DAC8SEL, RCC_CCIPR2_DAC8SEL_1)                        /*!< ADC clock used as DAC8 clock source   */
#define LL_RCC_DAC8_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC8SEL_Pos, RCC_CCIPR2_DAC8SEL, RCC_CCIPR2_DAC8SEL_1 | RCC_CCIPR2_DAC8SEL_0) /*!< HSE clock used as DAC8 clock source   */
#define LL_RCC_DAC8_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC8SEL_Pos, RCC_CCIPR2_DAC8SEL, RCC_CCIPR2_DAC8SEL_2)                        /*!< HSI clock used as DAC8 clock source   */
#define LL_RCC_DAC8_CLKSOURCE_PLL1Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC8SEL_Pos, RCC_CCIPR2_DAC8SEL, RCC_CCIPR2_DAC8SEL_2 | RCC_CCIPR2_DAC8SEL_0) /*!< PLL1Q clock used as DAC8 clock source */
#define LL_RCC_DAC8_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC8SEL_Pos, RCC_CCIPR2_DAC8SEL, RCC_CCIPR2_DAC8SEL_2 | RCC_CCIPR2_DAC8SEL_1) /*!< PLL2Q clock used as DAC8 clock source */
#define LL_RCC_DAC8_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC8SEL_Pos, RCC_CCIPR2_DAC8SEL, RCC_CCIPR2_DAC8SEL)                          /*!< DAC8 kernel clock is disabled         */

#define LL_RCC_DAC9_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC9SEL_Pos, RCC_CCIPR2_DAC9SEL, 0UL)                                         /*!< TIM clock used as DAC9 clock source   */
#define LL_RCC_DAC9_CLKSOURCE_HRTIM  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC9SEL_Pos, RCC_CCIPR2_DAC9SEL, RCC_CCIPR2_DAC9SEL_0)                        /*!< HRTIM clock used as DAC9 clock source */
#define LL_RCC_DAC9_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC9SEL_Pos, RCC_CCIPR2_DAC9SEL, RCC_CCIPR2_DAC9SEL_1)                        /*!< ADC clock used as DAC9 clock source   */
#define LL_RCC_DAC9_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC9SEL_Pos, RCC_CCIPR2_DAC9SEL, RCC_CCIPR2_DAC9SEL_1 | RCC_CCIPR2_DAC9SEL_0) /*!< HSE clock used as DAC9 clock source   */
#define LL_RCC_DAC9_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC9SEL_Pos, RCC_CCIPR2_DAC9SEL, RCC_CCIPR2_DAC9SEL_2)                        /*!< HSI clock used as DAC9 clock source   */
#define LL_RCC_DAC9_CLKSOURCE_PLL1Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC9SEL_Pos, RCC_CCIPR2_DAC9SEL, RCC_CCIPR2_DAC9SEL_2 | RCC_CCIPR2_DAC9SEL_0) /*!< PLL1Q clock used as DAC9 clock source */
#define LL_RCC_DAC9_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC9SEL_Pos, RCC_CCIPR2_DAC9SEL, RCC_CCIPR2_DAC9SEL_2 | RCC_CCIPR2_DAC9SEL_1) /*!< PLL2Q clock used as DAC9 clock source */
#define LL_RCC_DAC9_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC9SEL_Pos, RCC_CCIPR2_DAC9SEL, RCC_CCIPR2_DAC9SEL)                          /*!< DAC9 kernel clock is disabled         */

#define LL_RCC_DAC10_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC10SEL_Pos, RCC_CCIPR2_DAC10SEL, 0UL)                                           /*!< TIM clock used as DAC10 clock source   */
#define LL_RCC_DAC10_CLKSOURCE_HRTIM  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC10SEL_Pos, RCC_CCIPR2_DAC10SEL, RCC_CCIPR2_DAC10SEL_0)                         /*!< HRTIM clock used as DAC10 clock source */
#define LL_RCC_DAC10_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC10SEL_Pos, RCC_CCIPR2_DAC10SEL, RCC_CCIPR2_DAC10SEL_1)                         /*!< ADC clock used as DAC10 clock source   */
#define LL_RCC_DAC10_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC10SEL_Pos, RCC_CCIPR2_DAC10SEL, RCC_CCIPR2_DAC10SEL_1 | RCC_CCIPR2_DAC10SEL_0) /*!< HSE clock used as DAC10 clock source   */
#define LL_RCC_DAC10_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC10SEL_Pos, RCC_CCIPR2_DAC10SEL, RCC_CCIPR2_DAC10SEL_2)                         /*!< HSI clock used as DAC10 clock source   */
#define LL_RCC_DAC10_CLKSOURCE_PLL1Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC10SEL_Pos, RCC_CCIPR2_DAC10SEL, RCC_CCIPR2_DAC10SEL_2 | RCC_CCIPR2_DAC10SEL_0) /*!< PLL1Q clock used as DAC10 clock source */
#define LL_RCC_DAC10_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC10SEL_Pos, RCC_CCIPR2_DAC10SEL, RCC_CCIPR2_DAC10SEL_2 | RCC_CCIPR2_DAC10SEL_1) /*!< PLL2Q clock used as DAC10 clock source */
#define LL_RCC_DAC10_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC10SEL_Pos, RCC_CCIPR2_DAC10SEL, RCC_CCIPR2_DAC10SEL)                           /*!< DAC10 kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DACSHx_CLKSOURCE Peripheral DACSHx clock source selection
  * @{
  */
#define LL_RCC_DAC1SH_CLKSOURCE_LSE LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SHSEL_Pos, RCC_CCIPR2_DAC1SHSEL, 0UL)                  /*!< LSE clock used as DAC1SH clock source */
#define LL_RCC_DAC1SH_CLKSOURCE_LSI LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SHSEL_Pos, RCC_CCIPR2_DAC1SHSEL, RCC_CCIPR2_DAC1SHSEL) /*!< LSI clock used as DAC1SH clock source */

#define LL_RCC_DAC2SH_CLKSOURCE_LSE LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SHSEL_Pos, RCC_CCIPR2_DAC2SHSEL, 0UL)                  /*!< LSE clock used as DAC2SH clock source */
#define LL_RCC_DAC2SH_CLKSOURCE_LSI LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SHSEL_Pos, RCC_CCIPR2_DAC2SHSEL, RCC_CCIPR2_DAC2SHSEL) /*!< LSI clock used as DAC2SH clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPIx_CLKSOURCE Peripheral SPIx clock source selection
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE_PCLK2     LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, 0UL)                                         /*!< PCLK2 clock used as SPI1 clock source    */
#define LL_RCC_SPI1_CLKSOURCE_ICLK1     LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_0)                        /*!< ICLK1 clock used as SPI1 clock source    */
#define LL_RCC_SPI1_CLKSOURCE_PLL2P     LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_1)                        /*!< PLL2P clock used as SPI1 clock source    */
#define LL_RCC_SPI1_CLKSOURCE_HSE       LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_1 | RCC_CCIPR3_SPI1SEL_0) /*!< HSE clock used as SPI1 clock source      */
#define LL_RCC_SPI1_CLKSOURCE_HSI       LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_2)                        /*!< HSI clock used as SPI1 clock source      */
#define LL_RCC_SPI1_CLKSOURCE_AUDIOCLK  LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_2 | RCC_CCIPR3_SPI1SEL_0) /*!< AUDIOCLK clock used as SPI1 clock source */
#define LL_RCC_SPI1_CLKSOURCE_NONE      LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL)                          /*!< SPI1 kernel clock is disabled            */

#define LL_RCC_SPI2_CLKSOURCE_PCLK1     LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI2SEL_Pos, RCC_CCIPR3_SPI2SEL, 0UL)                                         /*!< PCLK1 clock used as SPI2 clock source    */
#define LL_RCC_SPI2_CLKSOURCE_ICLK1     LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI2SEL_Pos, RCC_CCIPR3_SPI2SEL, RCC_CCIPR3_SPI2SEL_0)                        /*!< ICLK1 clock used as SPI2 clock source    */
#define LL_RCC_SPI2_CLKSOURCE_PLL2P     LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI2SEL_Pos, RCC_CCIPR3_SPI2SEL, RCC_CCIPR3_SPI2SEL_1)                        /*!< PLL2P clock used as SPI2 clock source    */
#define LL_RCC_SPI2_CLKSOURCE_HSE       LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI2SEL_Pos, RCC_CCIPR3_SPI2SEL, RCC_CCIPR3_SPI2SEL_1 | RCC_CCIPR3_SPI2SEL_0) /*!< HSE clock used as SPI2 clock source      */
#define LL_RCC_SPI2_CLKSOURCE_HSI       LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI2SEL_Pos, RCC_CCIPR3_SPI2SEL, RCC_CCIPR3_SPI2SEL_2)                        /*!< HSI clock used as SPI2 clock source      */
#define LL_RCC_SPI2_CLKSOURCE_AUDIOCLK  LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI2SEL_Pos, RCC_CCIPR3_SPI2SEL, RCC_CCIPR3_SPI2SEL_2 | RCC_CCIPR3_SPI2SEL_0) /*!< AUDIOCLK clock used as SPI2 clock source */
#define LL_RCC_SPI2_CLKSOURCE_NONE      LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI2SEL_Pos, RCC_CCIPR3_SPI2SEL, RCC_CCIPR3_SPI2SEL)                          /*!< SPI2 kernel clock is disabled            */

#if defined(SPI3)
#define LL_RCC_SPI3_CLKSOURCE_PCLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI3SEL_Pos, RCC_CCIPR3_SPI3SEL, 0UL)                                         /*!< PCLK1 clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI3SEL_Pos, RCC_CCIPR3_SPI3SEL, RCC_CCIPR3_SPI3SEL_0)                        /*!< ICLK1 clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_PLL2P  LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI3SEL_Pos, RCC_CCIPR3_SPI3SEL, RCC_CCIPR3_SPI3SEL_1)                        /*!< PLL2P clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI3SEL_Pos, RCC_CCIPR3_SPI3SEL, RCC_CCIPR3_SPI3SEL_1 | RCC_CCIPR3_SPI3SEL_0) /*!< HSE clock used as SPI3 clock source   */
#define LL_RCC_SPI3_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI3SEL_Pos, RCC_CCIPR3_SPI3SEL, RCC_CCIPR3_SPI3SEL_2)                        /*!< HSI clock used as SPI3 clock source   */
#define LL_RCC_SPI3_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI3SEL_Pos, RCC_CCIPR3_SPI3SEL, RCC_CCIPR3_SPI3SEL)                          /*!< SPI3 kernel clock is disabled         */
#endif /* SPI3 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLAY_CLKSOURCE Peripheral PLAY clock source selection
  * @{
  */
#if defined(PLAY1)
#define LL_RCC_PLAY1_CLKSOURCE_LSE    0U                                              /*!< LSE clock used as PLAY1 clock source   */
#define LL_RCC_PLAY1_CLKSOURCE_LSI    RCC_CCIPR3_PLAY1SEL_0                           /*!< LSI clock used as PLAY1 clock source   */
#define LL_RCC_PLAY1_CLKSOURCE_PLL2P  RCC_CCIPR3_PLAY1SEL_1                           /*!< PLL2P clock used as PLAY1 clock source */
#define LL_RCC_PLAY1_CLKSOURCE_HSE    (RCC_CCIPR3_PLAY1SEL_1 | RCC_CCIPR3_PLAY1SEL_0) /*!< HSE clock used as PLAY1 clock source   */
#define LL_RCC_PLAY1_CLKSOURCE_HSI    RCC_CCIPR3_PLAY1SEL_2                           /*!< HSI clock used as PLAY1 clock source   */
#define LL_RCC_PLAY1_CLKSOURCE_HSI48  (RCC_CCIPR3_PLAY1SEL_2 | RCC_CCIPR3_PLAY1SEL_0) /*!< HSI48 clock used as PLAY1 clock source */
#define LL_RCC_PLAY1_CLKSOURCE_NONE   RCC_CCIPR3_PLAY1SEL                             /*!< PLAY1 kernel clock is disabled         */
#endif /* PLAY1 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIM_CLKSOURCE Peripheral LPTIM clock source selection
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE_PCLK3  0U                                                /*!< PCLK3 clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_PLL1Q  RCC_CCIPR3_LPTIM1SEL_0                            /*!< PLL1Q clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_PLL2P  RCC_CCIPR3_LPTIM1SEL_1                            /*!< PLL2P clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_HSE    (RCC_CCIPR3_LPTIM1SEL_1 | RCC_CCIPR3_LPTIM1SEL_0) /*!< HSE clock used as LPTIM1 clock source   */
#define LL_RCC_LPTIM1_CLKSOURCE_HSI    RCC_CCIPR3_LPTIM1SEL_2                            /*!< HSI clock used as LPTIM1 clock source   */
#define LL_RCC_LPTIM1_CLKSOURCE_LSI    (RCC_CCIPR3_LPTIM1SEL_2 | RCC_CCIPR3_LPTIM1SEL_0) /*!< LSI clock used as LPTIM1 clock source   */
#define LL_RCC_LPTIM1_CLKSOURCE_LSE    (RCC_CCIPR3_LPTIM1SEL_2 | RCC_CCIPR3_LPTIM1SEL_1) /*!< LSE clock used as LPTIM1 clock source   */
#define LL_RCC_LPTIM1_CLKSOURCE_NONE   RCC_CCIPR3_LPTIM1SEL                              /*!< LPTIM1 kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_XSPI_CLKSOURCE Peripheral XSPI clock source selection
  * @{
  */
#if defined(XSPI1)
#define LL_RCC_XSPI1_CLKSOURCE_HCLK4  0U                                              /*!< HCLK4 clock used as XSPI1 clock source */
#define LL_RCC_XSPI1_CLKSOURCE_PLL1Q  RCC_CCIPR4_XSPI1SEL_0                           /*!< PLL1Q clock used as XSPI1 clock source */
#define LL_RCC_XSPI1_CLKSOURCE_ICLK2  RCC_CCIPR4_XSPI1SEL_1                           /*!< ICLK2 clock used as XSPI1 clock source */
#define LL_RCC_XSPI1_CLKSOURCE_HSE    (RCC_CCIPR4_XSPI1SEL_1 | RCC_CCIPR4_XSPI1SEL_0) /*!< HSE clock used as XSPI1 clock source   */
#define LL_RCC_XSPI1_CLKSOURCE_HSI    RCC_CCIPR4_XSPI1SEL_2                           /*!< HSI clock used as XSPI1 clock source   */
#define LL_RCC_XSPI1_CLKSOURCE_NONE   RCC_CCIPR4_XSPI1SEL                             /*!< XSPI1 kernel clock is disabled         */
#endif /* XSPI1 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_UCPD_CLKSOURCE Peripheral UCPD clock source selection
  * @{
  */
#if defined(UCPD1)
#define LL_RCC_UCPD1_CLKSOURCE_HSI   0U                    /*!< HSI clock used as UCPD1 clock source   */
#define LL_RCC_UCPD1_CLKSOURCE_HSE   RCC_CCIPR4_UCPD1SEL_0 /*!< HSE clock used as UCPD1 clock source   */
#define LL_RCC_UCPD1_CLKSOURCE_HSI48 RCC_CCIPR4_UCPD1SEL_1 /*!< HSI48 clock used as UCPD1 clock source */
#define LL_RCC_UCPD1_CLKSOURCE_PLL2Q RCC_CCIPR4_UCPD1SEL   /*!< PLL2Q clock used as UCPD1 clock source */
#endif /* UCPD1 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USB_CLKSOURCE Peripheral USB clock source selection
  * @{
  */
#if defined(USB_DRD_FS)
#define LL_RCC_USB_CLKSOURCE_HSI48 0U                  /*!< HSI48 clock used as USB clock source */
#define LL_RCC_USB_CLKSOURCE_HSE   RCC_CCIPR4_USBSEL_0 /*!< HSE clock used as USB clock source   */
#define LL_RCC_USB_CLKSOURCE_PLL1Q RCC_CCIPR4_USBSEL_1 /*!< PLL1Q clock used as USB clock source */
#define LL_RCC_USB_CLKSOURCE_PLL2Q RCC_CCIPR4_USBSEL   /*!< PLL2Q clock used as USB clock source */
#endif /* USB_DRD_FS */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I3C_CLKSOURCE Peripheral I3C clock source selection
  * @{
  */
#define LL_RCC_I3C1_CLKSOURCE_PCLK1  0U                                            /*!< PCLK1 clock used as I3C1 clock source */
#define LL_RCC_I3C1_CLKSOURCE_ICLK1  RCC_CCIPR4_I3C1SEL_0                          /*!< ICLK1 clock used as I3C1 clock source */
#define LL_RCC_I3C1_CLKSOURCE_HSI    RCC_CCIPR4_I3C1SEL_1                          /*!< HSI clock used as I3C1 clock source   */
#define LL_RCC_I3C1_CLKSOURCE_HSE    (RCC_CCIPR4_I3C1SEL_1 | RCC_CCIPR4_I3C1SEL_0) /*!< HSE clock used as I3C1 clock source   */
#define LL_RCC_I3C1_CLKSOURCE_NONE   RCC_CCIPR4_I3C1SEL                            /*!< I3C1 kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2Cx_CLKSOURCE Peripheral I2Cx clock source selection
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE_PCLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C1SEL_Pos, RCC_CCIPR4_I2C1SEL, 0UL)                                         /*!< PCLK1 clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C1SEL_Pos, RCC_CCIPR4_I2C1SEL, RCC_CCIPR4_I2C1SEL_0)                        /*!< ICLK1 clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C1SEL_Pos, RCC_CCIPR4_I2C1SEL, RCC_CCIPR4_I2C1SEL_1)                        /*!< HSI clock used as I2C1 clock source   */
#define LL_RCC_I2C1_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C1SEL_Pos, RCC_CCIPR4_I2C1SEL, RCC_CCIPR4_I2C1SEL_1 | RCC_CCIPR4_I2C1SEL_0) /*!< HSE clock used as I2C1 clock source   */
#define LL_RCC_I2C1_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C1SEL_Pos, RCC_CCIPR4_I2C1SEL, RCC_CCIPR4_I2C1SEL)                          /*!< I2C1 kernel clock is disabled */

#define LL_RCC_I2C2_CLKSOURCE_PCLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C2SEL_Pos, RCC_CCIPR4_I2C2SEL, 0UL)                                         /*!< PCLK1 clock used as I2C2 clock source */
#define LL_RCC_I2C2_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C2SEL_Pos, RCC_CCIPR4_I2C2SEL, RCC_CCIPR4_I2C2SEL_0)                        /*!< ICLK1 clock used as I2C2 clock source */
#define LL_RCC_I2C2_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C2SEL_Pos, RCC_CCIPR4_I2C2SEL, RCC_CCIPR4_I2C2SEL_1)                        /*!< HSI clock used as I2C2 clock source   */
#define LL_RCC_I2C2_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C2SEL_Pos, RCC_CCIPR4_I2C2SEL, RCC_CCIPR4_I2C2SEL_1 | RCC_CCIPR4_I2C2SEL_0) /*!< HSE clock used as I2C2 clock source   */
#define LL_RCC_I2C2_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C2SEL_Pos, RCC_CCIPR4_I2C2SEL, RCC_CCIPR4_I2C2SEL)                          /*!< I2C2 kernel clock is disabled */

#if defined(I2C3)
#define LL_RCC_I2C3_CLKSOURCE_PCLK3  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C3SEL_Pos, RCC_CCIPR4_I2C3SEL, 0UL)                                         /*!< PCLK3 clock used as I2C3 clock source */
#define LL_RCC_I2C3_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C3SEL_Pos, RCC_CCIPR4_I2C3SEL, RCC_CCIPR4_I2C3SEL_0)                        /*!< ICLK1 clock used as I2C3 clock source */
#define LL_RCC_I2C3_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C3SEL_Pos, RCC_CCIPR4_I2C3SEL, RCC_CCIPR4_I2C3SEL_1)                        /*!< HSI clock used as I2C3 clock source   */
#define LL_RCC_I2C3_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C3SEL_Pos, RCC_CCIPR4_I2C3SEL, RCC_CCIPR4_I2C3SEL_1 | RCC_CCIPR4_I2C3SEL_0) /*!< HSE clock used as I2C3 clock source   */
#define LL_RCC_I2C3_CLKSOURCE_HSI48  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C3SEL_Pos, RCC_CCIPR4_I2C3SEL, RCC_CCIPR4_I2C3SEL_2)                        /*!< HSI48 clock used as I2C3 clock source */
#define LL_RCC_I2C3_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C3SEL_Pos, RCC_CCIPR4_I2C3SEL, RCC_CCIPR4_I2C3SEL)                          /*!< I2C3 kernel clock is disabled */

#endif /* I2C3 */
#if defined(I2C4)
#define LL_RCC_I2C4_CLKSOURCE_PCLK3  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C4SEL_Pos, RCC_CCIPR4_I2C4SEL, 0UL)                                         /*!< PCLK3 clock used as I2C4 clock source */
#define LL_RCC_I2C4_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C4SEL_Pos, RCC_CCIPR4_I2C4SEL, RCC_CCIPR4_I2C4SEL_0)                        /*!< ICLK1 clock used as I2C4 clock source */
#define LL_RCC_I2C4_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C4SEL_Pos, RCC_CCIPR4_I2C4SEL, RCC_CCIPR4_I2C4SEL_1)                        /*!< HSI clock used as I2C4 clock source   */
#define LL_RCC_I2C4_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C4SEL_Pos, RCC_CCIPR4_I2C4SEL, RCC_CCIPR4_I2C4SEL_1 | RCC_CCIPR4_I2C4SEL_0) /*!< HSE clock used as I2C4 clock source   */
#define LL_RCC_I2C4_CLKSOURCE_HSI48  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C4SEL_Pos, RCC_CCIPR4_I2C4SEL, RCC_CCIPR4_I2C4SEL_2)                        /*!< HSI48 clock used as I2C4 clock source */
#define LL_RCC_I2C4_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C4SEL_Pos, RCC_CCIPR4_I2C4SEL, RCC_CCIPR4_I2C4SEL)                          /*!< I2C4 kernel clock is disabled */
#endif /* I2C4 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC_CLKSOURCE Peripheral ADC clock source selection
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE_TIM   0U                                          /*!< TIM clock used as ADC clock source   */
#define LL_RCC_ADC_CLKSOURCE_HRTIM RCC_CCIPR5_ADCSEL_0                         /*!< HRTIM clock used as ADC clock source */
#define LL_RCC_ADC_CLKSOURCE_HSI   RCC_CCIPR5_ADCSEL_1                         /*!< HSI clock used as ADC clock source   */
#define LL_RCC_ADC_CLKSOURCE_HSE   (RCC_CCIPR5_ADCSEL_1 | RCC_CCIPR5_ADCSEL_0) /*!< HSE clock used as ADC clock source   */
#define LL_RCC_ADC_CLKSOURCE_PLL1Q RCC_CCIPR5_ADCSEL_2                         /*!< PLL1Q clock used as ADC clock source */
#define LL_RCC_ADC_CLKSOURCE_ICLK1 (RCC_CCIPR5_ADCSEL_2 | RCC_CCIPR5_ADCSEL_0) /*!< ICLK1 clock used as ADC clock source */
#define LL_RCC_ADC_CLKSOURCE_PLL2P (RCC_CCIPR5_ADCSEL_2 | RCC_CCIPR5_ADCSEL_1) /*!< PLL2P clock used as ADC clock source */
#define LL_RCC_ADC_CLKSOURCE_ICLK2 RCC_CCIPR5_ADCSEL                           /*!< ICLK2 clock used as ADC clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FDCAN_CLKSOURCE Peripheral FDCAN clock source selection
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE_HSE    0U                    /*!< HSE clock used as FDCAN clock source   */
#define LL_RCC_FDCAN_CLKSOURCE_PLL1Q  RCC_CCIPR5_FDCANSEL_0 /*!< PLL1Q clock used as FDCAN clock source */
#define LL_RCC_FDCAN_CLKSOURCE_PLL2Q  RCC_CCIPR5_FDCANSEL_1 /*!< PLL2Q clock used as FDCAN clock source */
#define LL_RCC_FDCAN_CLKSOURCE_NONE   RCC_CCIPR5_FDCANSEL   /*!< FDCAN kernel clock is disabled */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_POSENCx_CLKSOURCE Peripheral POSENCx clock source selection
  * @{
  */
#if defined(POSENC1)
#define LL_RCC_POSENC1_CLKSOURCE_PLL1P  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC1SEL_Pos, RCC_CCIPR5_POSENC1SEL, 0UL)                                               /*!< PLL1P clock used as POSENC1 clock source */
#define LL_RCC_POSENC1_CLKSOURCE_PLL1Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC1SEL_Pos, RCC_CCIPR5_POSENC1SEL, RCC_CCIPR5_POSENC1SEL_0)                           /*!< PLL1Q clock used as POSENC1 clock source */
#define LL_RCC_POSENC1_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC1SEL_Pos, RCC_CCIPR5_POSENC1SEL, RCC_CCIPR5_POSENC1SEL_1)                           /*!< ICLK1 clock used as POSENC1 clock source */
#define LL_RCC_POSENC1_CLKSOURCE_PLL2P  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC1SEL_Pos, RCC_CCIPR5_POSENC1SEL, RCC_CCIPR5_POSENC1SEL_1 | RCC_CCIPR5_POSENC1SEL_0) /*!< PLL2P clock used as POSENC1 clock source */
#define LL_RCC_POSENC1_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC1SEL_Pos, RCC_CCIPR5_POSENC1SEL, RCC_CCIPR5_POSENC1SEL_2)                           /*!< PLL2Q clock used as POSENC1 clock source */
#define LL_RCC_POSENC1_CLKSOURCE_ICLK2  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC1SEL_Pos, RCC_CCIPR5_POSENC1SEL, RCC_CCIPR5_POSENC1SEL_2 | RCC_CCIPR5_POSENC1SEL_0) /*!< ICLK2 clock used as POSENC1 clock source */
#define LL_RCC_POSENC1_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC1SEL_Pos, RCC_CCIPR5_POSENC1SEL, RCC_CCIPR5_POSENC1SEL)                            /*!< POSENC1 kernel clock is disabled         */
#endif /* POSENC1 */

#if defined(POSENC2)
#define LL_RCC_POSENC2_CLKSOURCE_PLL1P  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC2SEL_Pos, RCC_CCIPR5_POSENC2SEL, 0UL)                                               /*!< PLL1P clock used as POSENC2 clock source */
#define LL_RCC_POSENC2_CLKSOURCE_PLL1Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC2SEL_Pos, RCC_CCIPR5_POSENC2SEL, RCC_CCIPR5_POSENC2SEL_0)                           /*!< PLL1Q clock used as POSENC2 clock source */
#define LL_RCC_POSENC2_CLKSOURCE_ICLK1  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC2SEL_Pos, RCC_CCIPR5_POSENC2SEL, RCC_CCIPR5_POSENC2SEL_1)                           /*!< ICLK1 clock used as POSENC2 clock source */
#define LL_RCC_POSENC2_CLKSOURCE_PLL2P  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC2SEL_Pos, RCC_CCIPR5_POSENC2SEL, RCC_CCIPR5_POSENC2SEL_1 | RCC_CCIPR5_POSENC2SEL_0) /*!< PLL2P clock used as POSENC2 clock source */
#define LL_RCC_POSENC2_CLKSOURCE_PLL2Q  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC2SEL_Pos, RCC_CCIPR5_POSENC2SEL, RCC_CCIPR5_POSENC2SEL_2)                           /*!< PLL2Q clock used as POSENC2 clock source */
#define LL_RCC_POSENC2_CLKSOURCE_ICLK2  LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC2SEL_Pos, RCC_CCIPR5_POSENC2SEL, RCC_CCIPR5_POSENC2SEL_2 | RCC_CCIPR5_POSENC2SEL_0) /*!< ICLK2 clock used as POSENC2 clock source */
#define LL_RCC_POSENC2_CLKSOURCE_NONE   LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC2SEL_Pos, RCC_CCIPR5_POSENC2SEL, RCC_CCIPR5_POSENC2SEL)                             /*!< POSENC2 kernel clock is disabled         */
#endif /* POSENC2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USARTx Peripheral USARTx get clock source
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, 0UL) /*!< USART1 Clock source selection */
#define LL_RCC_USART2_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, 0UL) /*!< USART2 Clock source selection */
#if defined(USART3)
#define LL_RCC_USART3_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, 0UL) /*!< USART3 Clock source selection */
#endif /* USART3 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_UARTx Peripheral UARTx get clock source
  * @{
  */
#define LL_RCC_UART4_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, 0UL) /*!< UART4 Clock source selection */
#define LL_RCC_UART5_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, 0UL) /*!< UART5 Clock source selection */
#define LL_RCC_UART6_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR1, (uint32_t)RCC_CCIPR1_UART6SEL_Pos, RCC_CCIPR1_UART6SEL, 0UL) /*!< UART6 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART Peripheral LPUART get clock source
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE RCC_CCIPR1_LPUART1SEL /*!< LPUART1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DACx Peripheral DACx get clock source
  * @{
  */
#define LL_RCC_DAC1_CLKSOURCE  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SEL_Pos, RCC_CCIPR2_DAC1SEL, 0UL)   /*!< DAC1 Clock source selection  */
#define LL_RCC_DAC2_CLKSOURCE  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SEL_Pos, RCC_CCIPR2_DAC2SEL, 0UL)   /*!< DAC2 Clock source selection  */
#define LL_RCC_DAC5_CLKSOURCE  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC5SEL_Pos, RCC_CCIPR2_DAC5SEL, 0UL)   /*!< DAC5 Clock source selection  */
#define LL_RCC_DAC6_CLKSOURCE  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC6SEL_Pos, RCC_CCIPR2_DAC6SEL, 0UL)   /*!< DAC6 Clock source selection  */
#define LL_RCC_DAC7_CLKSOURCE  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC7SEL_Pos, RCC_CCIPR2_DAC7SEL, 0UL)   /*!< DAC7 Clock source selection  */
#define LL_RCC_DAC8_CLKSOURCE  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC8SEL_Pos, RCC_CCIPR2_DAC8SEL, 0UL)   /*!< DAC8 Clock source selection  */
#define LL_RCC_DAC9_CLKSOURCE  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC9SEL_Pos, RCC_CCIPR2_DAC9SEL, 0UL)   /*!< DAC9 Clock source selection  */
#define LL_RCC_DAC10_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC10SEL_Pos, RCC_CCIPR2_DAC10SEL, 0UL) /*!< DAC10 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DACSHx Peripheral DACSHx get clock source
  * @{
  */
#define LL_RCC_DAC1SH_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC1SHSEL_Pos, RCC_CCIPR2_DAC1SHSEL, 0UL) /*!< DAC1SH Clock source selection */
#define LL_RCC_DAC2SH_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_DAC2SHSEL_Pos, RCC_CCIPR2_DAC2SHSEL, 0UL) /*!< DAC2SH Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPIx Peripheral SPIx get clock source
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, 0UL) /*!< SPI1 Clock source selection */
#define LL_RCC_SPI2_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI2SEL_Pos, RCC_CCIPR3_SPI2SEL, 0UL) /*!< SPI2 Clock source selection */
#if defined(SPI3)
#define LL_RCC_SPI3_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI3SEL_Pos, RCC_CCIPR3_SPI3SEL, 0UL) /*!< SPI3 Clock source selection */
#endif /* SPI3 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLAY Peripheral PLAY get clock source
  * @{
  */
#if defined(PLAY1)
#define LL_RCC_PLAY1_CLKSOURCE RCC_CCIPR3_PLAY1SEL /*!< PLAY1 Clock source selection */
#endif /* PLAY1 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIM Peripheral LPTIM get clock source
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE RCC_CCIPR3_LPTIM1SEL /*!< LPTIM1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_XSPI Peripheral XSPI get clock source
  * @{
  */
#if defined(XSPI1)
#define LL_RCC_XSPI1_CLKSOURCE RCC_CCIPR4_XSPI1SEL /*!< XSPI1 Clock source selection */
#endif /* XSPI1 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_UCPD Peripheral UCPD get clock source
  * @{
  */
#if defined(UCPD1)
#define LL_RCC_UCPD1_CLKSOURCE RCC_CCIPR4_UCPD1SEL /*!< UCPD1 Clock source selection */
#endif /* UCPD1 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USB Peripheral USB get clock source
  * @{
  */
#if defined(USB_DRD_FS)
#define LL_RCC_USB_CLKSOURCE RCC_CCIPR4_USBSEL /*!< USB Clock source selection */
#endif /* USB_DRD_FS */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I3C Peripheral I3C get clock source
  * @{
  */
#define LL_RCC_I3C1_CLKSOURCE RCC_CCIPR4_I3C1SEL /*!< I3C1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2Cx Peripheral I2Cx get clock source
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C1SEL_Pos, RCC_CCIPR4_I2C1SEL, 0UL) /*!< I2C1 Clock source selection */
#define LL_RCC_I2C2_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C2SEL_Pos, RCC_CCIPR4_I2C2SEL, 0UL) /*!< I2C2 Clock source selection */
#if defined(I2C3)
#define LL_RCC_I2C3_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C3SEL_Pos, RCC_CCIPR4_I2C3SEL, 0UL) /*!< I2C3 Clock source selection */
#endif /* I2C3 */
#if defined(I2C4)
#define LL_RCC_I2C4_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_I2C4SEL_Pos, RCC_CCIPR4_I2C4SEL, 0UL) /*!< I2C4 Clock source selection */
#endif /* I2C4 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC Peripheral ADC get clock source
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE RCC_CCIPR5_ADCSEL /*!< ADC Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FDCAN Peripheral FDCAN get clock source
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE RCC_CCIPR5_FDCANSEL /*!< FDCAN Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_POSENCx Peripheral POSENCx get clock source
  * @{
  */
#if defined(POSENC1)
#define LL_RCC_POSENC1_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC1SEL_Pos, RCC_CCIPR5_POSENC1SEL, 0UL) /*!< POSENC1 Clock source selection */
#endif /* POSENC1 */
#if defined(POSENC2)
#define LL_RCC_POSENC2_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR5, (uint32_t)RCC_CCIPR5_POSENC2SEL_Pos, RCC_CCIPR5_POSENC2SEL, 0UL) /*!< POSENC2 Clock source selection */
#endif /* POSENC2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLINPUTRANGE All PLLs input ranges
  * @{
  */
#define LL_RCC_PLLINPUTRANGE_1_2  0U                     /*!< PLLx input clock range frequency between 1 and 2 MHz (default after reset) */
#define LL_RCC_PLLINPUTRANGE_2_4  RCC_PLL1CFGR_PLL1RGE_0 /*!< PLLx input clock range frequency between 2 and 4 MHz                       */
#define LL_RCC_PLLINPUTRANGE_4_8  RCC_PLL1CFGR_PLL1RGE_1 /*!< PLLx input clock range frequency between 4 and 8 MHz                       */
#define LL_RCC_PLLINPUTRANGE_8_16 RCC_PLL1CFGR_PLL1RGE   /*!< PLLx input clock range frequency between 8 and 16 MHz                      */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLVCORANGE All PLLs vco ranges
  * @{
  */
#define LL_RCC_PLLVCORANGE_128_560 0U                      /*!< wide VCO range: 128 to 560 MHz   */
#define LL_RCC_PLLVCORANGE_150_420 RCC_PLL1CFGR_PLL1VCOSEL /*!< medium VCO range: 150 to 420 MHz */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL1SOURCE PLL1 entry clock source
  * @{
  */
#define LL_RCC_PLL1SOURCE_NO_CLK 0U                     /*!< No clock selected as main PLL1 entry clock source   */
#define LL_RCC_PLL1SOURCE_HSI    RCC_PLL1CFGR_PLL1SRC_0 /*!< HSI clock selected as main PLL1 entry clock source  */
#define LL_RCC_PLL1SOURCE_HSE    RCC_PLL1CFGR_PLL1SRC_1 /*!< HSE clock selected as main PLL1 entry clock source  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL1_OUTPUT PLL1 Clock Output
  * @{
  */
#define LL_RCC_PLL1_OUTPUT_P RCC_PLL1CFGR_PLL1PEN /*!< PLL1 DIVP divider output enable            */
#define LL_RCC_PLL1_OUTPUT_Q RCC_PLL1CFGR_PLL1QEN /*!< PLL1 DIVQ divider output enable            */
#define LL_RCC_PLL1_OUTPUT_R RCC_PLL1CFGR_PLL1REN /*!< PLL1 DIVR and ICLK1 divider output enable  */
/**
  * @}
  */

#if defined (PLL2)
/** @defgroup RCC_LL_EC_PLL2SOURCE PLL2 entry clock source
  * @{
  */
#define LL_RCC_PLL2SOURCE_NO_CLK 0U                     /*!< No clock selected as main PLL2 entry clock source   */
#define LL_RCC_PLL2SOURCE_HSI  RCC_PLL2CFGR_PLL2SRC_0   /*!< HSI clock selected as main PLL2 entry clock source  */
#define LL_RCC_PLL2SOURCE_HSE  RCC_PLL2CFGR_PLL2SRC_1   /*!< HSE clock selected as main PLL2 entry clock source  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL2_OUTPUT PLL2 Clock Output
  * @{
  */
#define LL_RCC_PLL2_OUTPUT_P RCC_PLL2CFGR_PLL2PEN /*!< PLL2 DIVP divider output enable            */
#define LL_RCC_PLL2_OUTPUT_Q RCC_PLL2CFGR_PLL2QEN /*!< PLL2 DIVQ divider output enable            */
#define LL_RCC_PLL2_OUTPUT_R RCC_PLL2CFGR_PLL2REN /*!< PLL2 DIVR and ICLK2 divider output enable  */
/**
  * @}
  */
#endif /* #if defined (PLL2) */


/** @defgroup RCC_LL_FLAGS RCC Flags
  * @{
  */
#define LL_RCC_IT_LSIRDY   RCC_IFR_LSIRDYF   /*!< LSI ready interrupt flag                 */
#define LL_RCC_IT_LSERDY   RCC_IFR_LSERDYF   /*!< LSE ready interrupt flag                 */
#define LL_RCC_IT_HSIRDY   RCC_IFR_HSIRDYF   /*!< HSI ready interrupt flag                 */
#define LL_RCC_IT_HSERDY   RCC_IFR_HSERDYF   /*!< HSE ready interrupt flag                 */
#if defined (HSI48)
#define LL_RCC_IT_HSI48RDY RCC_IFR_HSI48RDYF /*!< HSI48 ready interrupt flag               */
#else
#define LL_RCC_IT_HSI48RDY 0U
#endif /* HSI48 */
#define LL_RCC_IT_PLL1RDY  RCC_IFR_PLL1RDYF  /*!< PLL1 ready interrupt flag                */
#if defined (PLL2)
#define LL_RCC_IT_PLL2RDY  RCC_IFR_PLL2RDYF  /*!< PLL2 ready interrupt flag                */
#else
#define LL_RCC_IT_PLL2RDY  0U
#endif /* PLL2 */
#define LL_RCC_IT_LSECSS   RCC_IFR_LSECSSF   /*!< LSE clock security system interrupt flag */
#define LL_RCC_IT_HSECSS   RCC_IFR_HSECSSF   /*!< HSE clock security system interrupt flag */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ATTRIBUTES RCC Secure/Privilege attributes
  * @{
  */
#define LL_RCC_ATTR_NSEC                    0UL                  /*!< Non-secure attribute            */
#define LL_RCC_ATTR_SEC                     1UL                  /*!< secure attribute                */

#define LL_RCC_ATTR_NPRIV                   0UL                  /*!< Non-privileged attribute        */
#define LL_RCC_ATTR_PRIV                    1UL                  /*!< Privileged attribute            */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ITEMS RCC Secure/Privilege Items
  * @{
  */
#define LL_RCC_SEC_ITEM_HSI         RCC_SECCFGR_HSISEC              /*!< HSI clock secure configuration item          */
#define LL_RCC_SEC_ITEM_HSE         RCC_SECCFGR_HSESEC              /*!< HSE clock secure configuration item          */
#define LL_RCC_SEC_ITEM_LSI         RCC_SECCFGR_LSISEC              /*!< LSI clock secure configuration item          */
#define LL_RCC_SEC_ITEM_LSE         RCC_SECCFGR_LSESEC              /*!< LSE clock secure configuration item          */
#define LL_RCC_SEC_ITEM_SYSCLK      RCC_SECCFGR_SYSCLKSEC           /*!< SYSCLK clock secure configuration item       */
#define LL_RCC_SEC_ITEM_PRESCALERS  RCC_SECCFGR_PRESCSEC            /*!< PRESCALERS secure configuration item         */
#define LL_RCC_SEC_ITEM_PLL1        RCC_SECCFGR_PLL1SEC             /*!< PLL1 clock secure configuration item         */
#if defined (PLL2)
#define LL_RCC_SEC_ITEM_PLL2        RCC_SECCFGR_PLL2SEC             /*!< PLL2 clock secure configuration item         */
#else
#define LL_RCC_SEC_ITEM_PLL2        0U
#endif /* PLL2 */
#if defined (HSI48)
#define LL_RCC_SEC_ITEM_HSI48       RCC_SECCFGR_HSI48SEC            /*!< HSI48 clock secure configuration item        */
#else
#define LL_RCC_SEC_ITEM_HSI48       0U
#endif /* HSI48 */
#define LL_RCC_SEC_ITEM_RESET_FLAGS RCC_SECCFGR_RMVFSEC             /*!< Remove reset flags secure configuration item */
#define LL_RCC_SEC_ITEM_ALL         (LL_RCC_SEC_ITEM_HSI | LL_RCC_SEC_ITEM_HSE |  LL_RCC_SEC_ITEM_LSI | \
                                     LL_RCC_SEC_ITEM_LSE | LL_RCC_SEC_ITEM_SYSCLK | LL_RCC_SEC_ITEM_PRESCALERS | \
                                     LL_RCC_SEC_ITEM_PLL1 | LL_RCC_SEC_ITEM_PLL2 | LL_RCC_SEC_ITEM_HSI48 | \
                                     LL_RCC_SEC_ITEM_RESET_FLAGS)   /*!< All RCC resources secure configuration item  */

#define LL_RCC_PRIV_ITEM_SPRIV      RCC_PRIVCFGR_SPRIV                                  /*!< All RCC secure resources privilege configuration item                */
#define LL_RCC_PRIV_ITEM_NSPRIV     RCC_PRIVCFGR_NSPRIV                                 /*!< All RCC non-secure resources privilege configuration item            */
#define LL_RCC_PRIV_ITEM_ALL        (LL_RCC_PRIV_ITEM_SPRIV | LL_RCC_PRIV_ITEM_NSPRIV)  /*!< All RCC secure and non-secure resources privilege configuration item */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Macros LL RCC Macros
  * @{
  */

/** @defgroup RCC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in RCC register.
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_RCC_WRITE_REG(reg, value) STM32_WRITE_REG(RCC->reg, (value))

/**
  * @brief  Read a value in RCC register.
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_RCC_READ_REG(reg) STM32_READ_REG(RCC->reg)

/**
  * @brief  Clear a field value in RCC register.
  * @param  reg Register to be written
  * @param  mask to be cleared
  */
#define LL_RCC_CLEAR_BIT(reg, bit) STM32_CLEAR_BIT(RCC->reg, bit)
/**
  * @}
  */

/** @defgroup RCC_LL_EM_CALC_FREQ Calculate frequencies
  * @{
  */

/**
  * @brief  Helper macro to calculate the PLL1CLK frequency on system domain.
  * @param  input_freq PLL1 Input frequency (based on HSI/HSE)
  * @param  pll1m parameter can be a value between 1 and 64
  * @param  pll1n parameter can be a value between 4 and 512
  * @param  pll1p parameter can be a value between 2 and 128 (Only even division are allowed)
  * @note   ex: @ref LL_RCC_CALC_PLL1CLK_FREQ (HSE_VALUE,@ref LL_RCC_PLL1_GetM (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetP ()).
  * @retval PLL1 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL1CLK_FREQ(input_freq, pll1m, pll1n, pll1p) ((((input_freq) /(pll1m)) * (pll1n)) / (pll1p))

/**
  * @brief  Helper macro to calculate the PLL1PCLK frequency.
  * @param  input_freq PLL1 Input frequency (based on HSI/HSE)
  * @param  pll1m parameter can be a value between 1 and 64
  * @param  pll1n parameter can be a value between 4 and 512
  * @param  pll1p parameter can be a value between 2 and 128 (Only even division are allowed)
  * @note   ex: @ref LL_RCC_CALC_PLL1CLK_P_FREQ (HSE_VALUE,@ref LL_RCC_PLL1_GetM (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetP ()).
  * @retval PLL1P clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL1CLK_P_FREQ(input_freq, pll1m, pll1n, pll1p) ((((input_freq) /(pll1m)) * (pll1n)) / (pll1p))

/**
  * @brief  Helper macro to calculate the PLL1QCLK frequency.
  * @param  input_freq PLL1 Input frequency (based on HSI/HSE)
  * @param  pll1m parameter can be a value between 1 and 64
  * @param  pll1n parameter can be a value between 4 and 512
  * @param  pll1q parameter can be a value between 1 and 128 (Only division by 1 and even division are allowed)
  * @note   ex: @ref LL_RCC_CALC_PLL1CLK_Q_FREQ (HSE_VALUE,@ref LL_RCC_PLL1_GetM (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetQ ()).
  * @retval PLL1Q clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL1CLK_Q_FREQ(input_freq, pll1m, pll1n, pll1q) ((((input_freq) /(pll1m)) * (pll1n)) / (pll1q))

/**
  * @brief  Helper macro to calculate the PLL1RCLK frequency.
  * @param  input_freq PLL1 Input frequency (based on HSI/HSE)
  * @param  pll1m parameter can be a value between 1 and 64
  * @param  pll1n parameter can be a value between 4 and 512
  * @param  pll1r parameter can be a value between 1 and 128 (Only division by 1 and even division are allowed)
  * @note   ex: @ref LL_RCC_CALC_PLL1CLK_R_FREQ (HSE_VALUE,@ref LL_RCC_PLL1_GetM (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetR ()).
  * @retval PLL1R clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL1CLK_R_FREQ(input_freq, pll1m, pll1n, pll1r) ((((input_freq) /(pll1m)) * (pll1n)) / (pll1r))

#if defined (PLL2)
/**
  * @brief  Helper macro to calculate the PLL2PCLK frequency.
  * @param  input_freq PLL2 Input frequency (based on HSI/HSE)
  * @param  pll2m parameter can be a value between 1 and 64
  * @param  pll2n parameter can be a value between 4 and 512
  * @param  pll2p parameter can be a value between 1 and 128
  * @note   ex: @ref LL_RCC_CALC_PLL2CLK_P_FREQ (HSE_VALUE,@ref LL_RCC_PLL2_GetM (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetP ()).
  * @retval PLL2P clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_P_FREQ(input_freq, pll2m, pll2n, pll2p) ((((input_freq) /(pll2m)) * (pll2n)) / (pll2p))

/**
  * @brief  Helper macro to calculate the PLL2QCLK frequency.
  * @param  input_freq PLL2 Input frequency (based on HSI/HSE)
  * @param  pll2m parameter can be a value between 1 and 64
  * @param  pll2n parameter can be a value between 4 and 512
  * @param  pll2q parameter can be a value between 1 and 128
  * @note   ex: @ref LL_RCC_CALC_PLL2CLK_Q_FREQ (HSE_VALUE,@ref LL_RCC_PLL2_GetM (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetQ ()).
  * @retval PLL2Q clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_Q_FREQ(input_freq, pll2m, pll2n, pll2q) ((((input_freq) /(pll2m)) * (pll2n)) / (pll2q))

/**
  * @brief  Helper macro to calculate the PLL2RCLK frequency.
  * @param  input_freq PLL2 Input frequency (based on HSI/HSE)
  * @param  pll2m parameter can be a value between 1 and 64
  * @param  pll2n parameter can be a value between 4 and 512
  * @param  pll2r parameter can be a value between 1 and 128
  * @note   ex: @ref LL_RCC_CALC_PLL2CLK_R_FREQ (HSE_VALUE,@ref LL_RCC_PLL2_GetM (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetR ()).
  * @retval PLL2R clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_R_FREQ(input_freq, pll2m, pll2n, pll2r) ((((input_freq) /(pll2m)) * (pll2n)) / (pll2r))
#endif /* PLL2 */
/**
  * @brief  Helper macro to calculate the HCLK frequency.
  * @param  sysclk_freq SYSCLK frequency (based on HSI/HSE/PLL1)
  * @param  ahb_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  * @retval HCLK clock frequency (in Hz)
  */
#define LL_RCC_CALC_HCLK_FREQ(sysclk_freq, ahb_prescaler) ((sysclk_freq) >> \
                                                           AHBPrescTable[((ahb_prescaler)& RCC_CFGR2_HPRE) \
                                                                         >>  RCC_CFGR2_HPRE_Pos])

/**
  * @brief  Helper macro to calculate the PCLK1 frequency (APB1).
  * @param  hclk_freq HCLK frequency
  * @param  apb1_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK1_FREQ(hclk_freq, apb1_prescaler) ((hclk_freq) >> \
                                                           (APBPrescTable[((apb1_prescaler)& \
                                                                           RCC_CFGR2_PPRE1) >>  RCC_CFGR2_PPRE1_Pos]))

/**
  * @brief  Helper macro to calculate the PCLK2 frequency (APB2).
  * @param  hclk_freq HCLK frequency
  * @param  apb2_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  * @retval PCLK2 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK2_FREQ(hclk_freq, apb2_prescaler) ((hclk_freq) >> \
                                                           (APBPrescTable[((apb2_prescaler)& \
                                                                           RCC_CFGR2_PPRE2) >>  RCC_CFGR2_PPRE2_Pos]))

/**
  * @brief  Helper macro to calculate the PCLK3 frequency (APB3).
  * @param  hclk_freq HCLK frequency
  * @param  apb3_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  * @retval PCLK3 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK3_FREQ(hclk_freq, apb3_prescaler) ((hclk_freq) >> \
                                                           (APBPrescTable[((apb3_prescaler)& \
                                                                           RCC_CFGR2_PPRE3) >>  RCC_CFGR2_PPRE3_Pos]))

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Functions LL RCC Functions
  * @{
  */

/** @defgroup RCC_LL_EF_HSE HSE
  * @{
  */

/**
  * @brief  Enable HSE oscillator.
  * @rmtoll
  *  CR         HSEON         LL_RCC_HSE_Enable
  */
__STATIC_INLINE void LL_RCC_HSE_Enable(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Disable HSE oscillator.
  * @rmtoll
  *  CR         HSEON         LL_RCC_HSE_Disable
  */
__STATIC_INLINE void LL_RCC_HSE_Disable(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Check if HSE oscillator is enabled.
  * @rmtoll
  *  CR         HSEON         LL_RCC_HSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsEnabled(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_HSEON) == RCC_CR_HSEON) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE oscillator is ready.
  * @rmtoll
  *  CR         HSERDY         LL_RCC_HSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_HSERDY) == RCC_CR_HSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSE external clock source (HSE bypass).
  * @rmtoll
  *  CR         HSEBYP         LL_RCC_HSE_EnableBypass
  */
__STATIC_INLINE void LL_RCC_HSE_EnableBypass(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Disable HSE external clock source (HSE bypass).
  * @rmtoll
  *  CR         HSEBYP         LL_RCC_HSE_DisableBypass
  */
__STATIC_INLINE void LL_RCC_HSE_DisableBypass(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Check if HSE oscillator is bypassed.
  * @rmtoll
  *  CR         HSEBYP         LL_RCC_HSE_IsBypassed
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsBypassed(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_HSEBYP) == RCC_CR_HSEBYP) ? 1UL : 0UL);
}

/**
  * @brief  Set external HSE clock type in Bypass mode.
  * @rmtoll
  *  CR         HSEEXT         LL_RCC_HSE_SetExternalClockType
  * @param  hse_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_TYPE
  *         @arg @ref LL_RCC_HSE_DIGITAL_TYPE
  * @note   This bit can be written only if the HSE oscillator is disabled.
  */
__STATIC_INLINE void LL_RCC_HSE_SetExternalClockType(uint32_t hse_mode)
{
  STM32_MODIFY_REG(RCC->CR, RCC_CR_HSEEXT, hse_mode);
}

/**
  * @brief  Get external HSE clock type in Bypass mode.
  * @rmtoll
  *  CR         HSEEXT         LL_RCC_HSE_GetExternalClockType
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_TYPE
  *         @arg @ref LL_RCC_HSE_DIGITAL_TYPE
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_GetExternalClockType(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CR, RCC_CR_HSEEXT));
}

/**
  * @brief  Configure HSE oscillator in bypass.
  * @rmtoll
  *  CR         HSEBYP         LL_RCC_HSE_ConfigBypass \n
  *  CR         HSEEXT         LL_RCC_HSE_ConfigBypass
  * @param  hse_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_TYPE
  *         @arg @ref LL_RCC_HSE_DIGITAL_TYPE
  */
__STATIC_INLINE void LL_RCC_HSE_ConfigBypass(uint32_t hse_mode)
{
  STM32_MODIFY_REG(RCC->CR, RCC_CR_HSEBYP | RCC_CR_HSEEXT, RCC_CR_HSEBYP | hse_mode);
}

/**
  * @brief  Enable HSE clock security system (HSE CSSON).
  * @rmtoll
  *  CR         HSECSSON         LL_RCC_HSE_EnableCSS
  * @note   Once HSE Clock Security System is enabled it cannot be changed anymore unless.
  *         a reset occurs or system enter in standby mode.
  */
__STATIC_INLINE void LL_RCC_HSE_EnableCSS(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_HSECSSON);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable LSE oscillator.
  * @rmtoll
  *  RTCCR         LSEON         LL_RCC_LSE_Enable
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  STM32_SET_BIT(RCC->RTCCR, RCC_RTCCR_LSEON);
}

/**
  * @brief  Disable LSE oscillator.
  * @rmtoll
  *  RTCCR         LSEON         LL_RCC_LSE_Disable
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  STM32_CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_LSEON);
}

/**
  * @brief  Check if LSE oscillator is enabled.
  * @rmtoll
  *  RTCCR         LSEON         LL_RCC_LSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabled(void)
{
  return ((STM32_READ_BIT(RCC->RTCCR, RCC_RTCCR_LSEON) == RCC_RTCCR_LSEON) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE oscillator is ready.
  * @rmtoll
  *  RTCCR         LSERDY         LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->RTCCR, RCC_RTCCR_LSERDY) == RCC_RTCCR_LSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable LSE external clock source (LSE bypass).
  * @rmtoll
  *  RTCCR         LSEBYP         LL_RCC_LSE_EnableBypass
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  STM32_SET_BIT(RCC->RTCCR, RCC_RTCCR_LSEBYP);
}

/**
  * @brief  Disable LSE external clock source (LSE bypass).
  * @rmtoll
  *  RTCCR         LSEBYP         LL_RCC_LSE_DisableBypass
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  STM32_CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_LSEBYP);
}

/**
  * @brief  Check if LSE oscillator is bypassed.
  * @rmtoll
  *  RTCCR         LSEBYP         LL_RCC_LSE_IsBypassed
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsBypassed(void)
{
  return ((STM32_READ_BIT(RCC->RTCCR, RCC_RTCCR_LSEBYP) == RCC_RTCCR_LSEBYP) ? 1UL : 0UL);
}

/**
  * @brief  Set LSE oscillator drive capability.
  * @rmtoll
  *  RTCCR         LSEDRV         LL_RCC_LSE_SetDriveCapability
  * @param  lse_drive This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  * @note   The oscillator is in crystal mode when it is not in bypass mode.
  */
__STATIC_INLINE void LL_RCC_LSE_SetDriveCapability(uint32_t lse_drive)
{
  STM32_MODIFY_REG(RCC->RTCCR, RCC_RTCCR_LSEDRV, lse_drive);
}

/**
  * @brief  Get LSE oscillator drive capability.
  * @rmtoll
  *  RTCCR         LSEDRV         LL_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
   */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetDriveCapability(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->RTCCR, RCC_RTCCR_LSEDRV));
}

/**
  * @brief  Enable LSE clock security system (LSE CSSON).
  * @rmtoll
  *  RTCCR         LSECSSON         LL_RCC_LSE_EnableCSS
  * @note   Once LSE Clock Security System is enabled it cannot be changed anymore unless
  *         a reset occurs or system enter in standby mode.
  */
__STATIC_INLINE void LL_RCC_LSE_EnableCSS(void)
{
  STM32_SET_BIT(RCC->RTCCR, RCC_RTCCR_LSECSSON);
}

/**
  * @brief  Disable LSE clock security system (LSE CSSON).
  * @rmtoll
  *  RTCCR         LSECSSON         LL_RCC_LSE_DisableCSS
  * @note   Clock security system can be disabled only after a LSE
  *         failure detection. In that case it must be disabled by software.
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  STM32_CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_LSECSSON);
}

/**
  * @brief  Check if CSS on LSE failure Detection.
  * @rmtoll
  *  RTCCR         LSECSSD         LL_RCC_LSE_IsCSSDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsCSSDetected(void)
{
  return ((STM32_READ_BIT(RCC->RTCCR, RCC_RTCCR_LSECSSD) == RCC_RTCCR_LSECSSD) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_HSI HSI
  * @{
  */

/**
  * @brief  Enable HSI oscillator.
  * @rmtoll
  *  CR         HSION         LL_RCC_HSI_Enable
  */
__STATIC_INLINE void LL_RCC_HSI_Enable(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @brief  Disable HSI oscillator.
  * @rmtoll
  *  CR         HSION         LL_RCC_HSI_Disable
  */
__STATIC_INLINE void LL_RCC_HSI_Disable(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @brief  Check if HSI oscillator is enabled.
  * @rmtoll
  *  CR         HSION         LL_RCC_HSI_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabled(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_HSION) == RCC_CR_HSION) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI oscillator is ready.
  * @rmtoll
  *  CR         HSIRDY         LL_RCC_HSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RCC_CR_HSIRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set HSI clock divider (HSI DIV).
  * @rmtoll
  *  CR         HSIDIV         LL_RCC_HSI_SetDivider
  * @param  value This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSI_DIV_1
  *         @arg @ref LL_RCC_HSI_DIV_2
  *         @arg @ref LL_RCC_HSI_DIV_4
  *         @arg @ref LL_RCC_HSI_DIV_8
  */
__STATIC_INLINE void LL_RCC_HSI_SetDivider(uint32_t value)
{
  STM32_MODIFY_REG(RCC->CR, RCC_CR_HSIDIV, value);
}

/**
  * @brief  Get HSI clock divider (HSI DIV).
  * @rmtoll
  *  CR         HSIDIV         LL_RCC_HSI_GetDivider
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HSI_DIV_1
  *         @arg @ref LL_RCC_HSI_DIV_2
  *         @arg @ref LL_RCC_HSI_DIV_4
  *         @arg @ref LL_RCC_HSI_DIV_8
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetDivider(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CR, RCC_CR_HSIDIV));
}

/**
  * @brief  Check if HSI divider flag is set (HSI DIVF).
  * @rmtoll
  *  CR         HSIDIVF         LL_RCC_HSI_IsDividerReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsDividerReady(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_HSIDIVF) == RCC_CR_HSIDIVF) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSI oscillator in Stop Mode.
  * @rmtoll
  *  CR         HSIKERON         LL_RCC_HSI_EnableInStopMode
  * @note   HSI oscillator is forced ON even in Stop mode.
  */
__STATIC_INLINE void LL_RCC_HSI_EnableInStopMode(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_HSIKERON);
}

/**
  * @brief  Disable HSI oscillator in Stop Mode.
  * @rmtoll
  *  CR         HSIKERON         LL_RCC_HSI_DisableInStopMode
  */
__STATIC_INLINE void LL_RCC_HSI_DisableInStopMode(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON);
}

/**
  * @brief  Check if HSI is enabled in Stop Mode.
  * @rmtoll
  *  CR         HSIKERON         LL_RCC_HSI_IsEnabledInStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabledInStopMode(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_HSIKERON) == RCC_CR_HSIKERON) ? 1UL : 0UL);
}

/**
  * @brief  Get HSI calibration value.
  * @rmtoll
  *  HSICFGR         HSICAL         LL_RCC_HSI_GetCalibration
  * @note   When HSITRIM is written, HSICAL is updated with the sum of HSITRIM and the factory trim value.
  * @retval Between Min_Data = 0 and Max_Data = 4095
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibration(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->HSICFGR, RCC_HSICFGR_HSICAL) >> RCC_HSICFGR_HSICAL_Pos);
}

/**
  * @brief  Set HSI calibration trimming.
  * @rmtoll
  *  HSICFGR         HSITRIM         LL_RCC_HSI_SetCalibTrimming
  * @param  value Between Min_Data = 0 and Max_Data = 127
  * @note   user-programmable trimming value that is added to the HSICAL.
  * @note   Default value is 64, which, when added to the HSICAL value, trim the HSI to 64 MHz +/- 1 %.
  */
__STATIC_INLINE void LL_RCC_HSI_SetCalibTrimming(uint32_t value)
{
  STM32_MODIFY_REG(RCC->HSICFGR, RCC_HSICFGR_HSITRIM, value << RCC_HSICFGR_HSITRIM_Pos);
}

/**
  * @brief  Get HSI calibration trimming.
  * @rmtoll
  *  HSICFGR         HSITRIM         LL_RCC_HSI_GetCalibTrimming
  * @retval Between Min_Data = 0 and Max_Data = 127
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibTrimming(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->HSICFGR, RCC_HSICFGR_HSITRIM) >> RCC_HSICFGR_HSITRIM_Pos);
}
/**
  * @}
  */

#if defined(HSI48)
/** @defgroup RCC_LL_EF_HSI48 HSI48
  * @{
  */

/**
  * @brief  Enable HSI48 oscillator.
  * @rmtoll
  *  CR         HSI48ON         LL_RCC_HSI48_Enable
  */
__STATIC_INLINE void LL_RCC_HSI48_Enable(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_HSI48ON);
}

/**
  * @brief  Disable HSI48 oscillator.
  * @rmtoll
  *  CR         HSI48ON         LL_RCC_HSI48_Disable
  */
__STATIC_INLINE void LL_RCC_HSI48_Disable(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_HSI48ON);
}

/**
  * @brief  Check if HSI48 oscillator is enabled.
  * @rmtoll
  *  CR         HSI48ON         LL_RCC_HSI48_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_IsEnabled(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_HSI48ON) == RCC_CR_HSI48ON) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI48 oscillator is ready.
  * @rmtoll
  *  CR         HSI48RDY         LL_RCC_HSI48_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_HSI48RDY) == RCC_CR_HSI48RDY) ? 1UL : 0UL);
}

/**
  * @brief  Get HSI48 calibration value.
  * @rmtoll
  *  CRRCR         HSI48CAL         LL_RCC_HSI48_GetCalibration
  * @note   When HSI48TRIM is written, HSI48CAL is updated with the sum of HSI48TRIM and the factory trim value.
  * @retval Between Min_Data = 0 and Max_Data = 1023
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_GetCalibration(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CRRCR, RCC_CRRCR_HSI48CAL) >> RCC_CRRCR_HSI48CAL_Pos);
}
/**
  * @}
  */
#endif /* HSI48 */

/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */

/**
  * @brief  Enable LSI oscillator.
  * @rmtoll
  *  RTCCR         LSION         LL_RCC_LSI_Enable
  */
__STATIC_INLINE void LL_RCC_LSI_Enable(void)
{
  STM32_SET_BIT(RCC->RTCCR, RCC_RTCCR_LSION);
}

/**
  * @brief  Disable LSI oscillator.
  * @rmtoll
  *  RTCCR         LSION         LL_RCC_LSI_Disable
  */
__STATIC_INLINE void LL_RCC_LSI_Disable(void)
{
  STM32_CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_LSION);
}

/**
  * @brief  Check if LSI oscillator is enabled.
  * @rmtoll
  *  RTCCR         LSION         LL_RCC_LSI_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsEnabled(void)
{
  return ((STM32_READ_BIT(RCC->RTCCR, RCC_RTCCR_LSION) == RCC_RTCCR_LSION) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI oscillator is ready.
  * @rmtoll
  *  RTCCR         LSIRDY         LL_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->RTCCR, RCC_RTCCR_LSIRDY) == RCC_RTCCR_LSIRDY) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_System System
  * @{
  */

/**
  * @brief  Configure the system clock source.
  * @rmtoll
  *  CFGR1         SYSSW         LL_RCC_SetSysClkSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_PLL1
  */
__STATIC_INLINE void LL_RCC_SetSysClkSource(uint32_t source)
{
  STM32_MODIFY_REG(RCC->CFGR1, RCC_CFGR1_SYSSW, source);
}

/**
  * @brief  Get the system clock source.
  * @rmtoll
  *  CFGR1         SYSSWS         LL_RCC_GetSysClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_PLL1
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CFGR1, RCC_CFGR1_SYSSWS));
}

/**
  * @brief  Set Systick clock source.
  * @rmtoll
  *  CCIPR3         SYSTICKSEL         LL_RCC_SetSystickClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSE
  */
__STATIC_INLINE void LL_RCC_SetSystickClockSource(uint32_t source)
{
  STM32_MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_SYSTICKSEL, source);
}

/**
  * @brief  Get Systick clock source.
  * @rmtoll
  *  CCIPR3         SYSTICKSEL         LL_RCC_GetSystickClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSystickClockSource(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR3, RCC_CCIPR3_SYSTICKSEL));
}

/**
  * @brief  Set AHB prescaler.
  * @rmtoll
  *  CFGR2         HPRE         LL_RCC_SetAHBPrescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  */
__STATIC_INLINE void LL_RCC_SetAHBPrescaler(uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->CFGR2, RCC_CFGR2_HPRE, prescaler);
}

/**
  * @brief  Get AHB prescaler.
  * @rmtoll
  *  CFGR2         HPRE         LL_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHBPrescaler(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_HPRE));
}

/**
  * @brief  Set APB1 prescaler.
  * @rmtoll
  *  CFGR2         PPRE1         LL_RCC_SetAPB1Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB1Prescaler(uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE1, prescaler);
}

/**
  * @brief  Get APB1 prescaler.
  * @rmtoll
  *  CFGR2         PPRE1         LL_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB1Prescaler(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE1));
}

/**
  * @brief  Set APB2 prescaler.
  * @rmtoll
  *  CFGR2         PPRE2         LL_RCC_SetAPB2Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB2Prescaler(uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE2, prescaler);
}

/**
  * @brief  Get APB2 prescaler.
  * @rmtoll
  *  CFGR2         PPRE2         LL_RCC_GetAPB2Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB2Prescaler(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE2));
}

/**
  * @brief  Set APB3 prescaler.
  * @rmtoll
  *  CFGR2         PPRE3         LL_RCC_SetAPB3Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB3Prescaler(uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE3, prescaler);
}

/**
  * @brief  Get APB3 prescaler.
  * @rmtoll
  *  CFGR2         PPRE3         LL_RCC_GetAPB3Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB3Prescaler(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE3));
}

/**
  * @brief  Configure buses prescalers (AHB, APB1, APB2 and APB3).
  * @rmtoll
  *  CFGR2         HPRE          LL_RCC_ConfigBusClock \n
  *  CFGR2         PPRE1         LL_RCC_ConfigBusClock \n
  *  CFGR2         PPRE2         LL_RCC_ConfigBusClock \n
  *  CFGR2         PPRE3         LL_RCC_ConfigBusClock
  * @param  ahb_apb1_apb2_apb3_pres Bus prescaler value of AHB, APB1, APB2 and APB3
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_ConfigBusClock(uint32_t ahb_apb1_apb2_apb3_pres)
{
  STM32_MODIFY_REG(RCC->CFGR2, (RCC_CFGR2_HPRE | RCC_CFGR2_PPRE1 | RCC_CFGR2_PPRE2 | RCC_CFGR2_PPRE3), \
                   ahb_apb1_apb2_apb3_pres);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_MCO MCO
  * @{
  */

/**
  * @brief  Configure MCOx.
  * @rmtoll
  *  CFGR1         MCO1SEL         LL_RCC_ConfigMCO \n
  *  CFGR1         MCO2SEL         LL_RCC_ConfigMCO \n
  *  CFGR1         MCO1PRE         LL_RCC_ConfigMCO \n
  *  CFGR1         MCO2PRE         LL_RCC_ConfigMCO
  * @param  mcox_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI
  *         @arg @ref LL_RCC_MCO1SOURCE_LSE
  *         @arg @ref LL_RCC_MCO1SOURCE_HSE
  *         @arg @ref LL_RCC_MCO1SOURCE_PLL1Q
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI48
  *         @arg @ref LL_RCC_MCO2SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO2SOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_MCO2SOURCE_HSE
  *         @arg @ref LL_RCC_MCO2SOURCE_PLL1P
  *         @arg @ref LL_RCC_MCO2SOURCE_LSI
  * @param  mcox_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1SOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCO1_PRESCALER_1
  *         @arg @ref LL_RCC_MCO1_PRESCALER_2
  *         @arg @ref LL_RCC_MCO1_PRESCALER_3
  *         @arg @ref LL_RCC_MCO1_PRESCALER_4
  *         @arg @ref LL_RCC_MCO1_PRESCALER_5
  *         @arg @ref LL_RCC_MCO1_PRESCALER_6
  *         @arg @ref LL_RCC_MCO1_PRESCALER_7
  *         @arg @ref LL_RCC_MCO1_PRESCALER_8
  *         @arg @ref LL_RCC_MCO1_PRESCALER_9
  *         @arg @ref LL_RCC_MCO1_PRESCALER_10
  *         @arg @ref LL_RCC_MCO1_PRESCALER_11
  *         @arg @ref LL_RCC_MCO1_PRESCALER_12
  *         @arg @ref LL_RCC_MCO1_PRESCALER_13
  *         @arg @ref LL_RCC_MCO1_PRESCALER_14
  *         @arg @ref LL_RCC_MCO1_PRESCALER_15
  *         @arg @ref LL_RCC_MCO2SOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCO2_PRESCALER_1
  *         @arg @ref LL_RCC_MCO2_PRESCALER_2
  *         @arg @ref LL_RCC_MCO2_PRESCALER_3
  *         @arg @ref LL_RCC_MCO2_PRESCALER_4
  *         @arg @ref LL_RCC_MCO2_PRESCALER_5
  *         @arg @ref LL_RCC_MCO2_PRESCALER_6
  *         @arg @ref LL_RCC_MCO2_PRESCALER_7
  *         @arg @ref LL_RCC_MCO2_PRESCALER_8
  *         @arg @ref LL_RCC_MCO2_PRESCALER_9
  *         @arg @ref LL_RCC_MCO2_PRESCALER_10
  *         @arg @ref LL_RCC_MCO2_PRESCALER_11
  *         @arg @ref LL_RCC_MCO2_PRESCALER_12
  *         @arg @ref LL_RCC_MCO2_PRESCALER_13
  *         @arg @ref LL_RCC_MCO2_PRESCALER_14
  *         @arg @ref LL_RCC_MCO2_PRESCALER_15
  * @note   The clock provided to the MCOx outputs must not exceed the maximum IO speed,
  *         refer to the product datasheet for information about the supported IO speed.
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_ConfigMCO(uint32_t mcox_source, uint32_t mcox_prescaler)
{
  STM32_MODIFY_REG(RCC->CFGR1, ((mcox_source | mcox_prescaler) << 16U), \
                   (mcox_source & (RCC_CFGR1_MCO1SEL | RCC_CFGR1_MCO2SEL)) | \
                   (mcox_prescaler & (RCC_CFGR1_MCO1PRE | RCC_CFGR1_MCO2PRE)));
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_Peripheral_Clock_Source Peripheral Clock Source
  * @{
  */

/**
  * @brief  Configure peripheral clock source.
  * @rmtoll
  *  CCIPR1         *         LL_RCC_SetClockSource \n
  *  CCIPR2         *         LL_RCC_SetClockSource \n
  *  CCIPR3         *         LL_RCC_SetClockSource \n
  *  CCIPR4         *         LL_RCC_SetClockSource \n
  *  CCIPR5         *         LL_RCC_SetClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_LSE (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_DAC2SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC2SH_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_NONE   (*)
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK3 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI48 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_NONE   (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_PCLK3 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSI48 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_NONE   (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL1P (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL1Q (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_ICLK2 (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_NONE   (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL1P (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL1Q (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_ICLK2 (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_NONE   (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetClockSource(uint32_t clk_src)
{
  volatile uint32_t *pReg = (uint32_t *)((uint32_t)&RCC->CCIPR1 + LL_CLKSOURCE_REG(clk_src));
  STM32_MODIFY_REG(*pReg, LL_CLKSOURCE_MASK(clk_src), LL_CLKSOURCE_CONFIG(clk_src));
}

/**
  * @brief  Configure USARTx clock source.
  * @rmtoll
  *  CCIPR1         USART1SEL         LL_RCC_SetUSARTClockSource \n
  *  CCIPR1         USART2SEL         LL_RCC_SetUSARTClockSource \n
  *  CCIPR1         USART3SEL         LL_RCC_SetUSARTClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_LSE (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_NONE   (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetUSARTClockSource(uint32_t clk_src)
{
  LL_RCC_SetClockSource(clk_src);
}

/**
  * @brief  Configure UARTx clock source.
  * @rmtoll
  *  CCIPR1         UART4SEL         LL_RCC_SetUARTClockSource \n
  *  CCIPR1         UART5SEL         LL_RCC_SetUARTClockSource \n
  *  CCIPR1         UART6SEL         LL_RCC_SetUARTClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_NONE
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetUARTClockSource(uint32_t clk_src)
{
  LL_RCC_SetClockSource(clk_src);
}

/**
  * @brief  Configure LPUARTx clock source.
  * @rmtoll
  *  CCIPR1         LPUART1SEL         LL_RCC_SetLPUARTClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetLPUARTClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_LPUART1SEL, clk_src);
}

/**
  * @brief  Configure DACx clock source.
  * @rmtoll
  *  CCIPR2         DAC1SEL          LL_RCC_SetDACClockSource \n
  *  CCIPR2         DAC2SEL          LL_RCC_SetDACClockSource \n
  *  CCIPR2         DAC5SEL          LL_RCC_SetDACClockSource \n
  *  CCIPR2         DAC6SEL          LL_RCC_SetDACClockSource \n
  *  CCIPR2         DAC7SEL          LL_RCC_SetDACClockSource \n
  *  CCIPR2         DAC8SEL          LL_RCC_SetDACClockSource \n
  *  CCIPR2         DAC9SEL          LL_RCC_SetDACClockSource \n
  *  CCIPR2         DAC10SEL         LL_RCC_SetDACClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_NONE
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetDACClockSource(uint32_t clk_src)
{
  LL_RCC_SetClockSource(clk_src);
}

/**
  * @brief  Configure DACSHx clock source.
  * @rmtoll
  *  CCIPR2         DAC1SHSEL         LL_RCC_SetDACSHClockSource \n
  *  CCIPR2         DAC2SHSEL         LL_RCC_SetDACSHClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_DAC2SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC2SH_CLKSOURCE_LSI
  */
__STATIC_INLINE void LL_RCC_SetDACSHClockSource(uint32_t clk_src)
{
  LL_RCC_SetClockSource(clk_src);
}

/**
  * @brief  Configure SPIx clock source.
  * @rmtoll
  *  CCIPR3         SPI1SEL         LL_RCC_SetSPIClockSource \n
  *  CCIPR3         SPI2SEL         LL_RCC_SetSPIClockSource \n
  *  CCIPR3         SPI3SEL         LL_RCC_SetSPIClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_NONE   (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetSPIClockSource(uint32_t clk_src)
{
  LL_RCC_SetClockSource(clk_src);
}

#if defined(PLAY1)
/**
  * @brief  Configure PLAYx clock source.
  * @rmtoll
  *  CCIPR3         PLAY1SEL         LL_RCC_SetPLAYClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetPLAYClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_PLAY1SEL, clk_src);
}
#endif /* PLAY1 */

/**
  * @brief  Configure LPTIMx clock source.
  * @rmtoll
  *  CCIPR3         LPTIM1SEL         LL_RCC_SetLPTIMClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_NONE
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetLPTIMClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPTIM1SEL, clk_src);
}

#if defined(XSPI1)
/**
  * @brief  Configure XSPIx clock source.
  * @rmtoll
  *  CCIPR4         XSPI1SEL         LL_RCC_SetXSPIClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HCLK4
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_ICLK2
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetXSPIClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_XSPI1SEL, clk_src);
}
#endif /* XSPI1 */

#if defined(UCPD1)
/**
  * @brief  Configure UCPDx clock source.
  * @rmtoll
  *  CCIPR4         UCPD1SEL         LL_RCC_SetUCPDClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UCPD1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UCPD1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UCPD1_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_UCPD1_CLKSOURCE_PLL2Q
  */
__STATIC_INLINE void LL_RCC_SetUCPDClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_UCPD1SEL, clk_src);
}
#endif /* UCPD1 */

#if defined(USB_DRD_FS)
/**
  * @brief  Configure USBx clock source.
  * @rmtoll
  *  CCIPR4         USBSEL         LL_RCC_SetUSBClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USB_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_USB_CLKSOURCE_PLL2Q
  */
__STATIC_INLINE void LL_RCC_SetUSBClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_USBSEL, clk_src);
}
#endif /* USB_DRD_FS*/
/**
  * @brief  Configure I3Cx clock source.
  * @rmtoll
  *  CCIPR4         I3C1SEL         LL_RCC_SetI3CClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetI3CClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_I3C1SEL, clk_src);
}

/**
  * @brief  Configure I2Cx clock source.
  * @rmtoll
  *  CCIPR4         I2C1SEL         LL_RCC_SetI2CClockSource \n
  *  CCIPR4         I2C2SEL         LL_RCC_SetI2CClockSource \n
  *  CCIPR4         I2C3SEL         LL_RCC_SetI2CClockSource \n
  *  CCIPR4         I2C4SEL         LL_RCC_SetI2CClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK3 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI48 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_PCLK3 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSI48 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_NONE (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetI2CClockSource(uint32_t clk_src)
{
  LL_RCC_SetClockSource(clk_src);
}

/**
  * @brief  Configure ADCx clock source.
  * @rmtoll
  *  CCIPR5         ADCSEL         LL_RCC_SetADCClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_ICLK2
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetADCClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR5, RCC_CCIPR5_ADCSEL, clk_src);
}

/**
  * @brief  Configure FDCANx clock source.
  * @rmtoll
  *  CCIPR5         FDCANSEL         LL_RCC_SetFDCANClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_NONE
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetFDCANClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR5, RCC_CCIPR5_FDCANSEL, clk_src);
}

#if defined(POSENC1) || defined(POSENC2)
/**
  * @brief  Configure POSENCx clock source.
  * @rmtoll
  *  CCIPR5         POSENC1SEL         LL_RCC_SetPOSENCClockSource \n
  *  CCIPR5         POSENC2SEL         LL_RCC_SetPOSENCClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL1P (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL1Q (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_ICLK2 (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL1P (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL1Q (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_ICLK2 (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_NONE (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetPOSENCClockSource(uint32_t clk_src)
{
  LL_RCC_SetClockSource(clk_src);
}
#endif /* POSENC1 || POSENC2 */

/**
  * @brief  Get periph clock source.
  * @rmtoll
  *  CCIPR1         *         LL_RCC_GetClockSource \n
  *  CCIPR2         *         LL_RCC_GetClockSource \n
  *  CCIPR3         *         LL_RCC_GetClockSource \n
  *  CCIPR4         *         LL_RCC_GetClockSource \n
  *  CCIPR5         *         LL_RCC_GetClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  *         @arg @ref LL_RCC_USART3_CLKSOURCE (*)
  *         @arg @ref LL_RCC_UART4_CLKSOURCE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE
  *         @arg @ref LL_RCC_DAC2SH_CLKSOURCE
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE (*)
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE (*)
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_LSE (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_DAC2SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC2SH_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK3 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI48 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_PCLK3 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSI48 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL1P (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL1Q (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_ICLK2 (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL1P (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL1Q (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_ICLK2 (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_NONE (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetClockSource(uint32_t periph)
{
  const volatile uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&RCC->CCIPR1) + LL_CLKSOURCE_REG(periph)));
  return (uint32_t)(periph | (((STM32_READ_BIT(*pReg, LL_CLKSOURCE_MASK(periph))) >> LL_CLKSOURCE_POS(periph)) \
                              << LL_RCC_CONFIG_SHIFT));
}
/**
  * @brief  Get USARTx clock source.
  * @rmtoll
  *  CCIPR1         USART1SEL         LL_RCC_GetUSARTClockSource \n
  *  CCIPR1         USART2SEL         LL_RCC_GetUSARTClockSource \n
  *  CCIPR1         USART3SEL         LL_RCC_GetUSARTClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  *         @arg @ref LL_RCC_USART3_CLKSOURCE (*)
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_LSE (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_NONE (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSARTClockSource(uint32_t periph)
{
  return LL_RCC_GetClockSource(periph);
}
/**
  * @brief  Get UARTx clock source.
  * @rmtoll
  *  CCIPR1         UART4SEL         LL_RCC_GetUARTClockSource \n
  *  CCIPR1         UART5SEL         LL_RCC_GetUARTClockSource \n
  *  CCIPR1         UART6SEL         LL_RCC_GetUARTClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART6_CLKSOURCE_NONE
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetUARTClockSource(uint32_t periph)
{
  return LL_RCC_GetClockSource(periph);
}
/**
  * @brief  Get LPUARTx clock source.
  * @rmtoll
  *  CCIPR1         LPUART1SEL         LL_RCC_GetLPUARTClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_NONE
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUARTClockSource(uint32_t periph)
{
  UNUSED(periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR1, RCC_CCIPR1_LPUART1SEL));
}
/**
  * @brief  Get DACx clock source.
  * @rmtoll
  *  CCIPR2         DAC1SEL          LL_RCC_GetDACClockSource \n
  *  CCIPR2         DAC2SEL          LL_RCC_GetDACClockSource \n
  *  CCIPR2         DAC5SEL          LL_RCC_GetDACClockSource \n
  *  CCIPR2         DAC6SEL          LL_RCC_GetDACClockSource \n
  *  CCIPR2         DAC7SEL          LL_RCC_GetDACClockSource \n
  *  CCIPR2         DAC8SEL          LL_RCC_GetDACClockSource \n
  *  CCIPR2         DAC9SEL          LL_RCC_GetDACClockSource \n
  *  CCIPR2         DAC10SEL         LL_RCC_GetDACClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC5_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC6_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC7_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC8_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC9_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_DAC10_CLKSOURCE_NONE
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetDACClockSource(uint32_t periph)
{
  return LL_RCC_GetClockSource(periph);
}
/**
  * @brief  Get DACSHx clock source.
  * @rmtoll
  *  CCIPR2         DAC1SHSEL         LL_RCC_GetDACSHClockSource \n
  *  CCIPR2         DAC2SHSEL         LL_RCC_GetDACSHClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE
  *         @arg @ref LL_RCC_DAC2SH_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_DAC2SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC2SH_CLKSOURCE_LSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetDACSHClockSource(uint32_t periph)
{
  return LL_RCC_GetClockSource(periph);
}
/**
  * @brief  Get SPIx clock source.
  * @rmtoll
  *  CCIPR3         SPI1SEL         LL_RCC_GetSPIClockSource \n
  *  CCIPR3         SPI2SEL         LL_RCC_GetSPIClockSource \n
  *  CCIPR3         SPI3SEL         LL_RCC_GetSPIClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE (*)
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_NONE (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPIClockSource(uint32_t periph)
{
  return LL_RCC_GetClockSource(periph);
}

#if defined(PLAY1)
/**
  * @brief  Get PLAYx clock source.
  * @rmtoll
  *  CCIPR3         PLAY1SEL         LL_RCC_GetPLAYClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_NONE
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetPLAYClockSource(uint32_t periph)
{
  UNUSED(periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR3, RCC_CCIPR3_PLAY1SEL));
}
#endif /* PLAY1 */
/**
  * @brief  Get LPTIMx clock source.
  * @rmtoll
  *  CCIPR3         LPTIM1SEL         LL_RCC_GetLPTIMClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_NONE
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIMClockSource(uint32_t periph)
{
  UNUSED(periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR3, RCC_CCIPR3_LPTIM1SEL));
}

#if defined(XSPI1)
/**
  * @brief  Get XSPIx clock source.
  * @rmtoll
  *  CCIPR4         XSPI1SEL         LL_RCC_GetXSPIClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HCLK4
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_ICLK2
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetXSPIClockSource(uint32_t periph)
{
  UNUSED(periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR4, RCC_CCIPR4_XSPI1SEL));
}
#endif /* XSPI1 */

#if defined(UCPD1)
/**
  * @brief  Get UCPDx clock source.
  * @rmtoll
  *  CCIPR4         UCPD1SEL         LL_RCC_GetUCPDClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UCPD1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_UCPD1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UCPD1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_UCPD1_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_UCPD1_CLKSOURCE_PLL2Q
  */
__STATIC_INLINE uint32_t LL_RCC_GetUCPDClockSource(uint32_t periph)
{
  UNUSED(periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR4, RCC_CCIPR4_UCPD1SEL));
}
#endif /* UCPD1 */

#if defined(USB_DRD_FS)
/**
  * @brief  Get USBx clock source.
  * @rmtoll
  *  CCIPR4         USBSEL         LL_RCC_GetUSBClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USB_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_USB_CLKSOURCE_PLL2Q
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSBClockSource(uint32_t periph)
{
  UNUSED(periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR4, RCC_CCIPR4_USBSEL));
}
#endif /* USB_DRD_FS */
/**
  * @brief  Get I3Cx clock source.
  * @rmtoll
  *  CCIPR4         I3C1SEL         LL_RCC_GetI3CClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3CClockSource(uint32_t periph)
{
  UNUSED(periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR4, RCC_CCIPR4_I3C1SEL));
}
/**
  * @brief  Get I2Cx clock source.
  * @rmtoll
  *  CCIPR4         I2C1SEL         LL_RCC_GetI2CClockSource \n
  *  CCIPR4         I2C2SEL         LL_RCC_GetI2CClockSource \n
  *  CCIPR4         I2C3SEL         LL_RCC_GetI2CClockSource \n
  *  CCIPR4         I2C4SEL         LL_RCC_GetI2CClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE (*)
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK3 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI48 (*)
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_PCLK3 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSE (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSI48 (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_NONE (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2CClockSource(uint32_t periph)
{
  return LL_RCC_GetClockSource(periph);
}
/**
  * @brief  Get ADCx clock source.
  * @rmtoll
  *  CCIPR5         ADCSEL         LL_RCC_GetADCClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_ICLK2
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCClockSource(uint32_t periph)
{
  UNUSED(periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR5, RCC_CCIPR5_ADCSEL));
}

/**
  * @brief  Get FDCANx clock source.
  * @rmtoll
  *  CCIPR5         FDCANSEL         LL_RCC_GetFDCANClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_NONE
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetFDCANClockSource(uint32_t periph)
{
  UNUSED(periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR5, RCC_CCIPR5_FDCANSEL));
}

#if defined(POSENC1) || defined(POSENC2)
/**
  * @brief  Get POSENCx clock source.
  * @rmtoll
  *  CCIPR5         POSENC1SEL         LL_RCC_GetPOSENCClockSource \n
  *  CCIPR5         POSENC2SEL         LL_RCC_GetPOSENCClockSource
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE (*)
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL1P (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL1Q (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_ICLK2 (*)
  *         @arg @ref LL_RCC_POSENC1_CLKSOURCE_NONE (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL1P (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL1Q (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_ICLK1 (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_PLL2Q (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_ICLK2 (*)
  *         @arg @ref LL_RCC_POSENC2_CLKSOURCE_NONE (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetPOSENCClockSource(uint32_t periph)
{
  return LL_RCC_GetClockSource(periph);
}
#endif /* POSENC1 || POSENC2 */

/**
  * @}
  */

/** @defgroup RCC_LL_EF_RTC RTC
  * @{
  */

/**
  * @brief  Set RTC Clock Source.
  * @rmtoll
  *  RTCCR         RTCSEL         LL_RCC_SetRTCClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV
  * @note   Once the RTC clock source has been selected, it cannot be changed anymore unless the Backup domain is reset,
  *         or unless a failure is detected on LSE (LSECSSD is set).
  */
__STATIC_INLINE void LL_RCC_SetRTCClockSource(uint32_t source)
{
  STM32_MODIFY_REG(RCC->RTCCR, RCC_RTCCR_RTCSEL, source);
}

/**
  * @brief  Get RTC Clock Source.
  * @rmtoll
  *  RTCCR         RTCSEL         LL_RCC_GetRTCClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTCClockSource(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->RTCCR, RCC_RTCCR_RTCSEL));
}

/**
  * @brief  Enable RTC.
  * @rmtoll
  *  RTCCR         RTCEN         LL_RCC_EnableRTC
  */
__STATIC_INLINE void LL_RCC_EnableRTC(void)
{
  STM32_SET_BIT(RCC->RTCCR, RCC_RTCCR_RTCEN);
}

/**
  * @brief  Disable RTC.
  * @rmtoll
  *  RTCCR         RTCEN         LL_RCC_DisableRTC
  */
__STATIC_INLINE void LL_RCC_DisableRTC(void)
{
  STM32_CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_RTCEN);
}

/**
  * @brief  Check if RTC has been enabled or not.
  * @rmtoll
  *  RTCCR         RTCEN         LL_RCC_IsEnabledRTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledRTC(void)
{
  return ((STM32_READ_BIT(RCC->RTCCR, RCC_RTCCR_RTCEN) == RCC_RTCCR_RTCEN) ? 1UL : 0UL);
}

/**
  * @brief  Force the RTC domain reset.
  * @rmtoll
  *  RTCCR         RTCDRST         LL_RCC_ForceRTCDomainReset
  */
__STATIC_INLINE void LL_RCC_ForceRTCDomainReset(void)
{
  STM32_SET_BIT(RCC->RTCCR, RCC_RTCCR_RTCDRST);
}

/**
  * @brief  Release the RTC domain reset.
  * @rmtoll
  *  RTCCR         RTCDRST         LL_RCC_ReleaseRTCDomainReset
  */
__STATIC_INLINE void LL_RCC_ReleaseRTCDomainReset(void)
{
  STM32_CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_RTCDRST);
}

/**
  * @brief  Set HSE Prescaler for RTC Clock.
  * @rmtoll
  *  CFGR1         RTCPRE         LL_RCC_SetRTC_HSEPrescaler
  * @param  Prescaler This parameter can be between 0 and 63
  * @note   Values 0 and 1 mean no clock.
  */
__STATIC_INLINE void LL_RCC_SetRTC_HSEPrescaler(uint32_t Prescaler)
{
  STM32_MODIFY_REG(RCC->CFGR1, RCC_CFGR1_RTCPRE, Prescaler << RCC_CFGR1_RTCPRE_Pos);
}

/**
  * @brief  Get HSE Prescaler for RTC Clock.
  * @rmtoll
  *  CFGR1         RTCPRE         LL_RCC_GetRTC_HSEPrescaler
  * @retval Returned value can be a value between 0 and 63.
  * @note   Values 0 and 1 mean no clock.
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTC_HSEPrescaler(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->CFGR1, RCC_CFGR1_RTCPRE) >>  RCC_CFGR1_RTCPRE_Pos));
}

/**
  * @}
  */

#if defined(PLAY1)
/** @defgroup RCC_LL_EF_PLAY1_CLOCK PLAY1
  * @{
  */

/**
  * @brief  Set PLAY1 Clock Divider.
  * @rmtoll
  *  CCIPR3          PLAY1DIV        LL_RCC_SetPLAY1Divider
  * @param  divider This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_1
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_2
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_4
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_8
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_16
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_32
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_64
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_128
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_256
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_512
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_1024
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_2048
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_4096
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_8192
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_16384
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_32768
  */
__STATIC_INLINE void LL_RCC_SetPLAY1Divider(uint32_t divider)
{
  STM32_MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_PLAY1DIV, divider);
}

/**
  * @brief  Get PLAY1 Clock Divider.
  * @rmtoll
  *  CCIPR3          PLAY1DIV        LL_RCC_GetPLAY1Divider
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_1
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_2
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_4
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_8
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_16
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_32
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_64
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_128
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_256
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_512
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_1024
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_2048
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_4096
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_8192
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_16384
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_32768
  */
__STATIC_INLINE uint32_t LL_RCC_GetPLAY1Divider(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR3, RCC_CCIPR3_PLAY1DIV));
}

/**
  * @brief  Configure PLAY1 Clock.
  * @rmtoll
  *  CCIPR3         PLAY1SEL        LL_RCC_ConfigPLAY1
  * @rmtoll
  *  CCIPR3         PLAY1DIV        LL_RCC_ConfigPLAY1
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_PLAY1_CLKSOURCE_HSI48
  * @param  divider This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_1
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_2
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_4
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_8
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_16
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_32
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_64
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_128
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_256
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_512
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_1024
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_2048
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_4096
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_8192
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_16384
  *         @arg @ref LL_RCC_PLAY1_DIVIDER_32768
  */
__STATIC_INLINE void LL_RCC_ConfigPLAY1(uint32_t clk_src, uint32_t divider)
{
  STM32_MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_PLAY1SEL | RCC_CCIPR3_PLAY1DIV, clk_src | divider);
}
/**
  * @}
  */
#endif /* PLAY1 */

/** @defgroup RCC_LL_EF_ADC_CLOCK ADC
  * @{
  */

/**
  * @brief  Set ADC Clock Prescaler.
  * @rmtoll
  *  CCIPR5          ADCDIV        LL_RCC_SetADCPrescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_PRESCALER_1
  *         @arg @ref LL_RCC_ADC_PRESCALER_2
  *         @arg @ref LL_RCC_ADC_PRESCALER_4
  *         @arg @ref LL_RCC_ADC_PRESCALER_6
  *         @arg @ref LL_RCC_ADC_PRESCALER_8
  *         @arg @ref LL_RCC_ADC_PRESCALER_10
  *         @arg @ref LL_RCC_ADC_PRESCALER_12
  *         @arg @ref LL_RCC_ADC_PRESCALER_16
  *         @arg @ref LL_RCC_ADC_PRESCALER_32
  *         @arg @ref LL_RCC_ADC_PRESCALER_64
  *         @arg @ref LL_RCC_ADC_PRESCALER_128
  *         @arg @ref LL_RCC_ADC_PRESCALER_256
  */
__STATIC_INLINE void LL_RCC_SetADCPrescaler(uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->CCIPR5, RCC_CCIPR5_ADCDIV, prescaler);
}

/**
  * @brief  Get ADC Clock Prescaler.
  * @rmtoll
  *  CCIPR5          ADCDIV        LL_RCC_GetADCPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADC_PRESCALER_1
  *         @arg @ref LL_RCC_ADC_PRESCALER_2
  *         @arg @ref LL_RCC_ADC_PRESCALER_4
  *         @arg @ref LL_RCC_ADC_PRESCALER_6
  *         @arg @ref LL_RCC_ADC_PRESCALER_8
  *         @arg @ref LL_RCC_ADC_PRESCALER_10
  *         @arg @ref LL_RCC_ADC_PRESCALER_12
  *         @arg @ref LL_RCC_ADC_PRESCALER_16
  *         @arg @ref LL_RCC_ADC_PRESCALER_32
  *         @arg @ref LL_RCC_ADC_PRESCALER_64
  *         @arg @ref LL_RCC_ADC_PRESCALER_128
  *         @arg @ref LL_RCC_ADC_PRESCALER_256
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCPrescaler(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR5, RCC_CCIPR5_ADCDIV));
}

/**
  * @brief  Configure ADC Clock.
  * @rmtoll
  *  CCIPR5          ADCDIV        LL_RCC_ConfigADC
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HRTIM
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_ICLK1
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL2P (*)
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_ICLK2 (*)
  *
  *        (*) value not defined in all devices.
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_PRESCALER_1
  *         @arg @ref LL_RCC_ADC_PRESCALER_2
  *         @arg @ref LL_RCC_ADC_PRESCALER_4
  *         @arg @ref LL_RCC_ADC_PRESCALER_6
  *         @arg @ref LL_RCC_ADC_PRESCALER_8
  *         @arg @ref LL_RCC_ADC_PRESCALER_10
  *         @arg @ref LL_RCC_ADC_PRESCALER_12
  *         @arg @ref LL_RCC_ADC_PRESCALER_16
  *         @arg @ref LL_RCC_ADC_PRESCALER_32
  *         @arg @ref LL_RCC_ADC_PRESCALER_64
  *         @arg @ref LL_RCC_ADC_PRESCALER_128
  *         @arg @ref LL_RCC_ADC_PRESCALER_256
  */
__STATIC_INLINE void LL_RCC_ConfigADC(uint32_t clk_src, uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->CCIPR5, RCC_CCIPR5_ADCSEL | RCC_CCIPR5_ADCDIV, clk_src | prescaler);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_ICLK_CLOCK_DIVIDER ICLK
  * @{
  */

/**
  * @brief Set Intermediate clock x (ICLKx) divider.
  * @rmtoll
  *  PLLxCFGR         ICLKxDIV         LL_RCC_ICLK_SetDivider
  * @param  iclkx parameter can be one of the following values:
  *         @arg @ref LL_RCC_ICLK1
  *         @arg @ref LL_RCC_ICLK2 (*)
  * @param  iclk_divider parameter can be one of the following values:
  *         @arg @ref LL_RCC_ICLK_DIV_5
  *         @arg @ref LL_RCC_ICLK_DIV_3
  * @note   There is no need to disable ICLK1 to change the division ratio.
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_ICLK_SetDivider(uint32_t iclkx, uint32_t iclk_divider)
{
  STM32_MODIFY_REG(*(__IO uint32_t *)(&RCC->PLL1CFGR + iclkx), RCC_PLL1CFGR_ICLK1DIV, iclk_divider);
}

/**
  * @brief Get Intermediate clock x (ICLKx) divider.
  * @rmtoll
  *  PLLxCFGR         ICLKxDIV         LL_RCC_ICLK_GetDivider
  * @param  iclkx parameter can be one of the following values:
  *         @arg @ref LL_RCC_ICLK1
  *         @arg @ref LL_RCC_ICLK2 (*)
  * @retval can be one of the following values:
  *         @arg @ref LL_RCC_ICLK_DIV_5
  *         @arg @ref LL_RCC_ICLK_DIV_3
  *
  *        (*) value not defined in all devices.
 */
__STATIC_INLINE uint32_t LL_RCC_ICLK_GetDivider(uint32_t iclkx)
{
  return (STM32_READ_BIT(*(__IO uint32_t *)(&RCC->PLL1CFGR + iclkx), RCC_PLL1CFGR_ICLK1DIV));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_PLL1 PLL1
  * @{
  */

/**
  * @brief  Enable PLL1.
  * @rmtoll
  *  CR         PLL1ON         LL_RCC_PLL1_Enable
  */
__STATIC_INLINE void LL_RCC_PLL1_Enable(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_PLL1ON);
}

/**
  * @brief  Disable PLL1.
  * @rmtoll
  *  CR         PLL1ON         LL_RCC_PLL1_Disable
  * @note   Cannot be disabled if the PLL1 clock is used as the system clock.
  */
__STATIC_INLINE void LL_RCC_PLL1_Disable(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_PLL1ON);
}

/**
  * @brief  Check if PLL1 is ready.
  * @rmtoll
  *  CR         PLL1RDY         LL_RCC_PLL1_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_PLL1RDY) == RCC_CR_PLL1RDY) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL clock source.
  * @rmtoll
  *  PLL1CFGR         PLL1SRC         LL_RCC_PLL1_SetSource
  * @param  pll1_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NO_CLK
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  */
__STATIC_INLINE void LL_RCC_PLL1_SetSource(uint32_t pll1_source)
{
  STM32_MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC, pll1_source);
}

/**
  * @brief  Get the oscillator used as PLL1 clock source.
  * @rmtoll
  *  PLL1CFGR         PLL1SRC         LL_RCC_PLL1_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NO_CLK
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetSource(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC));
}

/**
  * @brief  Configure PLL1 used as SYSCLK.
  * @rmtoll
  *  PLL1CFGR         PLL1SRC         LL_RCC_PLL1_ConfigDomain_SYS \n
  *  PLL1CFGR         PLL1M           LL_RCC_PLL1_ConfigDomain_SYS \n
  *  PLL1DIVR         PLL1N           LL_RCC_PLL1_ConfigDomain_SYS \n
  *  PLL1DIVR         PLL1P           LL_RCC_PLL1_ConfigDomain_SYS
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NO_CLK
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  * @param pll1m parameter can be a value between 1 and 64
  * @param pll1n parameter can be a value between 4 and 512
  * @param pll1p parameter can be a value between 2 and 128 (Only even division are allowed)
  * @note PLL1 Source, PLL1M, PLL1N and PLL1P can be written only when PLL1 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_ConfigDomain_SYS(uint32_t source, uint32_t pll1m, uint32_t pll1n, uint32_t pll1p)
{
  STM32_MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M,
                   source | (pll1m << RCC_PLL1CFGR_PLL1M_Pos));
  STM32_MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N | RCC_PLL1DIVR_PLL1P,
                   ((pll1n - 1UL) << RCC_PLL1DIVR_PLL1N_Pos) | ((pll1p - 1UL) << RCC_PLL1DIVR_PLL1P_Pos));
}

/**
  * @brief  Enable PLL1 output mapped on SYSCLK.
  * @note   This API must be called only when PLL1 is disabled.
  * @rmtoll
  *  RCC_PLL1CFGR         PLL1PEN         LL_RCC_PLL1_EnableOutput_SYS
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutput_SYS(void)
{
  STM32_SET_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_P);
}

/**
  * @brief  Disable PLL1 output mapped on SYSCLK.
  * @note   Cannot be disabled if the PLL1 clock is used as the system clock.
  * @rmtoll
  *  RCC_PLL1CFGR         PLL1PEN         LL_RCC_PLL1_DisableOutput_SYS
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutput_SYS(void)
{
  STM32_CLEAR_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_P);
}

/**
  * @brief  Check if PLL1 output mapped on SYSCLK is enabled.
  * @rmtoll
  *  RCC_PLL1CFGR         PLL1PEN         LL_RCC_PLL1_IsEnabledOutput_SYS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledOutput_SYS(void)
{
  return ((STM32_READ_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_P) == (LL_RCC_PLL1_OUTPUT_P)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1P output.
  * @rmtoll
  *  PLL1CFGR         PLL1PEN         LL_RCC_PLL1_EnableOutputP
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutputP(void)
{
  STM32_SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1PEN);
}

/**
  * @brief  Disable PLL1P output.
  * @rmtoll
  *  PLL1CFGR         PLL1PEN         LL_RCC_PLL1_DisableOutputP
  * @note   Cannot be disabled if the PLL1P clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutputP(void)
{
  STM32_CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1PEN);
}

/**
  * @brief  Check if PLL1P output is enabled.
  * @rmtoll
  *  PLL1CFGR         PLL1PEN         LL_RCC_PLL1_IsEnabledOutputP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledOutputP(void)
{
  return ((STM32_READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1PEN) == RCC_PLL1CFGR_PLL1PEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1Q output.
  * @rmtoll
  *  PLL1CFGR         PLL1QEN         LL_RCC_PLL1_EnableOutputQ
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutputQ(void)
{
  STM32_SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1QEN);
}

/**
  * @brief  Disable PLL1Q output.
  * @rmtoll
  *  PLL1CFGR         PLL1QEN         LL_RCC_PLL1_DisableOutputQ
  * @note   Cannot be disabled if the PLL1Q clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutputQ(void)
{
  STM32_CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1QEN);
}

/**
  * @brief  Check if PLL1Q output is enabled.
  * @rmtoll
  *  PLL1CFGR         PLL1QEN         LL_RCC_PLL1_IsEnabledOutputQ
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledOutputQ(void)
{
  return ((STM32_READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1QEN) == RCC_PLL1CFGR_PLL1QEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1R output.
  * @rmtoll
  *  PLL1CFGR         PLL1REN         LL_RCC_PLL1_EnableOutputR
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutputR(void)
{
  STM32_SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1REN);
}

/**
  * @brief  Disable PLL1R output.
  * @rmtoll
  *  PLL1CFGR         PLL1REN         LL_RCC_PLL1_DisableOutputR
  * @note   Cannot be disabled if the PLL1R clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutputR(void)
{
  STM32_CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1REN);
}

/**
  * @brief  Check if PLL1R output is enabled.
  * @rmtoll
  *  PLL1CFGR         PLL1REN         LL_RCC_PLL1_IsEnabledOutputR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledOutputR(void)
{
  return ((STM32_READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1REN) == RCC_PLL1CFGR_PLL1REN) ? 1UL : 0UL);
}
/**
  * @brief  Enable 1 or several PLL1 outputs.
  * @rmtoll
  *  PLL1CFGR         PLL1PEN         LL_RCC_PLL1_EnableOutput \n
  *  PLL1CFGR         PLL1QEN         LL_RCC_PLL1_EnableOutput \n
  *  PLL1CFGR         PLL1REN         LL_RCC_PLL1_EnableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_R
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutput(uint32_t outputs)
{
  STM32_SET_BIT(RCC->PLL1CFGR, outputs);
}

/**
  * @brief  Disable 1 or several PLL1 outputs.
  * @rmtoll
  *  PLL1CFGR         PLL1PEN         LL_RCC_PLL1_DisableOutput \n
  *  PLL1CFGR         PLL1QEN         LL_RCC_PLL1_DisableOutput \n
  *  PLL1CFGR         PLL1REN         LL_RCC_PLL1_DisableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_R
  * @note   Cannot be disabled if the PLL1XXX output is used as the system clock.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutput(uint32_t outputs)
{
  STM32_CLEAR_BIT(RCC->PLL1CFGR, outputs);
}

/**
  * @brief  Get the list of the outputs activated for PLL1.
  * @rmtoll
  *  PLL1CFGR         PLL1PEN         LL_RCC_PLL1_GetOutput \n
  *  PLL1CFGR         PLL1QEN         LL_RCC_PLL1_GetOutput \n
  *  PLL1CFGR         PLL1REN         LL_RCC_PLL1_GetOutput
  * @retval outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_R
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetOutput(void)
{
  return STM32_READ_BIT(RCC->PLL1CFGR, (LL_RCC_PLL1_OUTPUT_P | LL_RCC_PLL1_OUTPUT_Q | LL_RCC_PLL1_OUTPUT_R));
}

/**
  * @brief  Check if 1 or several PLL1 outputs are enabled.
  * @rmtoll
  *  PLL1CFGR         PLL1PEN         LL_RCC_PLL1_IsOutputEnabled \n
  *  PLL1CFGR         PLL1QEN         LL_RCC_PLL1_IsOutputEnabled \n
  *  PLL1CFGR         PLL1REN         LL_RCC_PLL1_IsOutputEnabled
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_R
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsOutputEnabled(uint32_t outputs)
{
  return ((STM32_READ_BIT(RCC->PLL1CFGR, outputs) == (outputs)) ? 1UL : 0UL);
}

/**
  * @brief  Set Main PLL1 multiplication factor for VCO.
  * @rmtoll
  *  PLL1DIVR         PLL1N         LL_RCC_PLL1_SetN
  * @param pll1n parameter can be a value between 4 and 512
  */
__STATIC_INLINE void LL_RCC_PLL1_SetN(uint32_t pll1n)
{
  STM32_MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N, (pll1n - 1UL) << RCC_PLL1DIVR_PLL1N_Pos);
}

/**
  * @brief  Get Main PLL1 multiplication factor for VCO.
  * @rmtoll
  *  PLL1DIVR         PLL1N         LL_RCC_PLL1_GetN
  * @retval Between 4 and 512
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetN(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N) >>  RCC_PLL1DIVR_PLL1N_Pos) + 1UL);
}

/**
  * @brief  Set Main division factor for PLL1.
  * @rmtoll
  *  PLL1CFGR         PLL1M         LL_RCC_PLL1_SetM
  * @param  pll1m parameter can be a value between 0 and 63 (0 for prescaler disabled)
  */
__STATIC_INLINE void LL_RCC_PLL1_SetM(uint32_t pll1m)
{
  STM32_MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1M, (pll1m) << RCC_PLL1CFGR_PLL1M_Pos);
}

/**
  * @brief  Get Main division factor for PLL1.
  * @rmtoll
  *  PLL1CFGR         PLL1M         LL_RCC_PLL1_GetM
  * @retval Between 0 and 63 (0 for prescaler disabled)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetM(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1M) >>  RCC_PLL1CFGR_PLL1M_Pos));
}

/**
  * @brief  Set Division factor for PLL1P.
  * @rmtoll
  *  PLL1DIVR         PLL1P         LL_RCC_PLL1_SetP
  * @param  pll1p parameter can be a value between 2 and 128 (Only even division are allowed)
  * @note   Used for PLL1PCLK selected for System clock and POSENC.
  */
__STATIC_INLINE void LL_RCC_PLL1_SetP(uint32_t pll1p)
{
  STM32_MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1P, (pll1p - 1UL) << RCC_PLL1DIVR_PLL1P_Pos);
}

/**
  * @brief  Get Division factor for PLL1P.
  * @rmtoll
  *  PLL1DIVR         PLL1P         LL_RCC_PLL1_GetP
  * @note   Used for PLL1PCLK selected for System clock and POSENC.
  * @retval Between 2 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetP(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1P) >>  RCC_PLL1DIVR_PLL1P_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL1Q.
  * @rmtoll
  *  PLL1DIVR         PLL1Q         LL_RCC_PLL1_SetQ
  * @param  pll1q parameter can be a value between 1 and 128
  * @note   Used for PLL1QCLK selected for DAC, LPTIM1, XSPI1, USBFS, ADC, FDCAN and POSENC.
  */
__STATIC_INLINE void LL_RCC_PLL1_SetQ(uint32_t pll1q)
{
  STM32_MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1Q, (pll1q - 1UL) << RCC_PLL1DIVR_PLL1Q_Pos);
}

/**
  * @brief  Get Division factor for PLL1Q.
  * @rmtoll
  *  PLL1DIVR         PLL1Q         LL_RCC_PLL1_GetQ
  * @note   Used for PLL1QCLK selected for DAC, LPTIM1, XSPI1, USBFS, ADC, FDCAN and POSENC.
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetQ(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1Q) >>  RCC_PLL1DIVR_PLL1Q_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL1R.
  * @rmtoll
  *  PLL1DIVR         PLL1R         LL_RCC_PLL1_SetR
  * @param  pll1r parameter can be a value between 1 and 128
  * @note   Used for PLL1RCLK selected for ICLK1 (USART, UART, LPUART, SPI, I3C, I2C, ADC and POSENC).
  */
__STATIC_INLINE void LL_RCC_PLL1_SetR(uint32_t pll1r)
{
  STM32_MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1R, (pll1r - 1UL) << RCC_PLL1DIVR_PLL1R_Pos);
}

/**
  * @brief  Get Division factor for PLL1R.
  * @rmtoll
  *  PLL1DIVR         PLL1R         LL_RCC_PLL1_GetR
  * @note   Used for PLL1RCLK selected for ICLK1 (USART, UART, LPUART, SPI, I3C, I2C, ADC and POSENC).
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetR(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1R) >>  RCC_PLL1DIVR_PLL1R_Pos) + 1UL);
}

/**
  * @brief  Enable PLL1 FRACN.
  * @rmtoll
  *  PLL1CFGR         PLL1FRACEN         LL_RCC_PLL1_EnableFRACN
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableFRACN(void)
{
  STM32_SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN);
}

/**
  * @brief  Disable PLL1 FRACN.
  * @rmtoll
  *  PLL1CFGR         PLL1FRACEN         LL_RCC_PLL1_DisableFRACN
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableFRACN(void)
{
  STM32_CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN);
}

/**
  * @brief  Check if PLL1 FRACN is enabled.
  * @rmtoll
  *  PLL1CFGR         PLL1FRACEN         LL_RCC_PLL1_IsEnabledFRACN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledFRACN(void)
{
  return ((STM32_READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN) == RCC_PLL1CFGR_PLL1FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL1 FRACN Coefficient.
  * @rmtoll
  *  PLL1FRACR         PLL1FRACN         LL_RCC_PLL1_SetFRACN
  * @param  fracn parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL1_SetFRACN(uint32_t fracn)
{
  STM32_MODIFY_REG(RCC->PLL1FRACR, RCC_PLL1FRACR_PLL1FRACN, fracn << RCC_PLL1FRACR_PLL1FRACN_Pos);
}

/**
  * @brief  Get PLL1 FRACN Coefficient.
  * @rmtoll
  *  PLL1FRACR         PLL1FRACN         LL_RCC_PLL1_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetFRACN(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL1FRACR, RCC_PLL1FRACR_PLL1FRACN) >>  RCC_PLL1FRACR_PLL1FRACN_Pos);
}

/**
  * @brief  Set PLL1 Input Range.
  * @rmtoll
  *  PLL1CFGR         PLL1RGE         LL_RCC_PLL1_SetInputRange
  * @param  input_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLLINPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  * @note   This API must be called only when PLL1 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_SetInputRange(uint32_t input_range)
{
  STM32_MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RGE, input_range);
}

/**
  * @brief  Get PLL1 Input Range.
  * @rmtoll
  *  PLL1CFGR         PLL1RGE         LL_RCC_PLL1_GetInputRange
  * @retval  The Input range. This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLLINPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetInputRange(void)
{
  return (STM32_READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RGE));
}

/**
  * @brief  Set PLL1 VCO Range.
  * @rmtoll
  *  PLL1CFGR         PLL1VCOSEL         LL_RCC_PLL1_SetVCORange
  * @param  vco_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLVCORANGE_128_560
  *         @arg @ref LL_RCC_PLLVCORANGE_150_420
  * @note   This API must be called only when PLL1 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_SetVCORange(uint32_t vco_range)
{
  STM32_MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1VCOSEL, vco_range);
}

/**
  * @brief  Get PLL1 VCO Range.
  * @rmtoll
  *  PLL1CFGR         PLL1VCOSEL         LL_RCC_PLL1_GetVCORange
  * @retval  The VCO range. This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLVCORANGE_128_560
  *         @arg @ref LL_RCC_PLLVCORANGE_150_420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetVCORange(void)
{
  return (STM32_READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1VCOSEL));
}
/**
  * @}
  */
#if defined(PLL2)
/** @defgroup RCC_LL_EF_PLL2 PLL2
  * @{
  */

/**
  * @brief  Enable PLL2.
  * @rmtoll
  *  CR         PLL2ON         LL_RCC_PLL2_Enable
  */
__STATIC_INLINE void LL_RCC_PLL2_Enable(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_PLL2ON);
}

/**
  * @brief  Disable PLL2.
  * @rmtoll
  *  CR         PLL2ON         LL_RCC_PLL2_Disable
  * @note   Cannot be disabled if the PLL2 clock is used as the system clock.
  */
__STATIC_INLINE void LL_RCC_PLL2_Disable(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_PLL2ON);
}

/**
  * @brief  Check if PLL2 is ready.
  * @rmtoll
  *  CR         PLL2RDY         LL_RCC_PLL2_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_PLL2RDY) == RCC_CR_PLL2RDY) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL clock source.
  * @rmtoll
  *  PLL2CFGR         PLL2SRC         LL_RCC_PLL2_SetSource
  * @param  pll2_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2SOURCE_NO_CLK
  *         @arg @ref LL_RCC_PLL2SOURCE_HSI
  *         @arg @ref LL_RCC_PLL2SOURCE_HSE
  */
__STATIC_INLINE void LL_RCC_PLL2_SetSource(uint32_t pll2_source)
{
  STM32_MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2SRC, pll2_source);
}

/**
  * @brief  Get the oscillator used as PLL2 clock source.
  * @rmtoll
  *  PLL2CFGR         PLL2SRC         LL_RCC_PLL2_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL2SOURCE_NO_CLK
  *         @arg @ref LL_RCC_PLL2SOURCE_HSI
  *         @arg @ref LL_RCC_PLL2SOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetSource(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2SRC));
}

/**
  * @brief  Enable PLL2P output.
  * @rmtoll
  *  PLL2CFGR         PLL2PEN         LL_RCC_PLL2_EnableOutputP
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutputP(void)
{
  STM32_SET_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2PEN);
}

/**
  * @brief  Disable PLL2P output.
  * @rmtoll
  *  PLL2CFGR         PLL2PEN         LL_RCC_PLL2_DisableOutputP
  * @note   Cannot be disabled if the PLL2P clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutputP(void)
{
  STM32_CLEAR_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2PEN);
}

/**
  * @brief  Check if PLL2P output is enabled.
  * @rmtoll
  *  PLL2CFGR         PLL2PEN         LL_RCC_PLL2_IsEnabledOutputP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledOutputP(void)
{
  return ((STM32_READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2PEN) == RCC_PLL2CFGR_PLL2PEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2Q output.
  * @rmtoll
  *  PLL2CFGR         PLL2QEN         LL_RCC_PLL2_EnableOutputQ
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutputQ(void)
{
  STM32_SET_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2QEN);
}

/**
  * @brief  Disable PLL2Q output.
  * @rmtoll
  *  PLL2CFGR         PLL2QEN         LL_RCC_PLL2_DisableOutputQ
  * @note   Cannot be disabled if the PLL2Q clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutputQ(void)
{
  STM32_CLEAR_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2QEN);
}

/**
  * @brief  Check if PLL2Q output is enabled.
  * @rmtoll
  *  PLL2CFGR         PLL2QEN         LL_RCC_PLL2_IsEnabledOutputQ
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledOutputQ(void)
{
  return ((STM32_READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2QEN) == RCC_PLL2CFGR_PLL2QEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2R output.
  * @rmtoll
  *  PLL2CFGR         PLL2REN         LL_RCC_PLL2_EnableOutputR
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutputR(void)
{
  STM32_SET_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2REN);
}

/**
  * @brief  Disable PLL2R output.
  * @rmtoll
  *  PLL2CFGR         PLL2REN         LL_RCC_PLL2_DisableOutputR
  * @note   Cannot be disabled if the PLL2R clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutputR(void)
{
  STM32_CLEAR_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2REN);
}

/**
  * @brief  Check if PLL2R output is enabled.
  * @rmtoll
  *  PLL2CFGR         PLL2REN         LL_RCC_PLL2_IsEnabledOutputR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledOutputR(void)
{
  return ((STM32_READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2REN) == RCC_PLL2CFGR_PLL2REN) ? 1UL : 0UL);
}
/**
  * @brief  Enable 1 or several PLL2 outputs.
  * @rmtoll
  *  PLL2CFGR         PLL2PEN         LL_RCC_PLL2_EnableOutput \n
  *  PLL2CFGR         PLL2QEN         LL_RCC_PLL2_EnableOutput \n
  *  PLL2CFGR         PLL2REN         LL_RCC_PLL2_EnableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutput(uint32_t outputs)
{
  STM32_SET_BIT(RCC->PLL2CFGR, outputs);
}

/**
  * @brief  Disable 1 or several PLL2 outputs.
  * @rmtoll
  *  PLL2CFGR         PLL2PEN         LL_RCC_PLL2_DisableOutput \n
  *  PLL2CFGR         PLL2QEN         LL_RCC_PLL2_DisableOutput \n
  *  PLL2CFGR         PLL2REN         LL_RCC_PLL2_DisableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutput(uint32_t outputs)
{
  STM32_CLEAR_BIT(RCC->PLL2CFGR, outputs);
}

/**
  * @brief  Get the list of the outputs activated for PLL2.
  * @rmtoll
  *  PLL2CFGR         PLL2PEN         LL_RCC_PLL2_GetOutput \n
  *  PLL2CFGR         PLL2QEN         LL_RCC_PLL2_GetOutput \n
  *  PLL2CFGR         PLL2REN         LL_RCC_PLL2_GetOutput
  * @retval outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetOutput(void)
{
  return STM32_READ_BIT(RCC->PLL2CFGR, (LL_RCC_PLL2_OUTPUT_P | LL_RCC_PLL2_OUTPUT_Q | LL_RCC_PLL2_OUTPUT_R));
}

/**
  * @brief  Check if 1 or several PLL2 outputs are enabled.
  * @rmtoll
  *  PLL2CFGR         PLL2PEN         LL_RCC_PLL2_IsOutputEnabled \n
  *  PLL2CFGR         PLL2QEN         LL_RCC_PLL2_IsOutputEnabled \n
  *  PLL2CFGR         PLL2REN         LL_RCC_PLL2_IsOutputEnabled
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsOutputEnabled(uint32_t outputs)
{
  return ((STM32_READ_BIT(RCC->PLL2CFGR, outputs) == (outputs)) ? 1UL : 0UL);
}

/**
  * @brief  Set Main PLL2 multiplication factor for VCO.
  * @rmtoll
  *  PLL2DIVR         PLL2N         LL_RCC_PLL2_SetN
  * @param pll2n parameter can be a value between 4 and 512
  */
__STATIC_INLINE void LL_RCC_PLL2_SetN(uint32_t pll2n)
{
  STM32_MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2N, (pll2n - 1UL) << RCC_PLL2DIVR_PLL2N_Pos);
}

/**
  * @brief  Get Main PLL2 multiplication factor for VCO.
  * @rmtoll
  *  PLL2DIVR         PLL2N         LL_RCC_PLL2_GetN
  * @retval Between 4 and 512
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetN(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2N) >>  RCC_PLL2DIVR_PLL2N_Pos) + 1UL);
}

/**
  * @brief  Set Main division factor for PLL2.
  * @rmtoll
  *  PLL2CFGR         PLL2M         LL_RCC_PLL2_SetM
  * @param pll2m parameter can be a value between 0 and 63
  */
__STATIC_INLINE void LL_RCC_PLL2_SetM(uint32_t pll2m)
{
  STM32_MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2M, (pll2m) << RCC_PLL2CFGR_PLL2M_Pos);
}

/**
  * @brief  Get Main division factor for PLL2.
  * @rmtoll
  *  PLL2CFGR         PLL2M         LL_RCC_PLL2_GetM
  * @retval Between 0 and 63
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetM(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2M) >>  RCC_PLL2CFGR_PLL2M_Pos));
}

/**
  * @brief  Set Division factor for PLL2P.
  * @rmtoll
  *  PLL2DIVR         PLL2P         LL_RCC_PLL2_SetP
  * @param pll2p parameter can be a value between 1 and 128
  * @note   Used for PLL2PCLK selected for SPI, PLAY1, LPTIM, ADC and POSENC.
  */
__STATIC_INLINE void LL_RCC_PLL2_SetP(uint32_t pll2p)
{
  STM32_MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2P, (pll2p - 1UL) << RCC_PLL2DIVR_PLL2P_Pos);
}

/**
  * @brief  Get Division factor for PLL2P.
  * @rmtoll
  *  PLL2DIVR         PLL2P         LL_RCC_PLL2_GetP
  * @note   Used for PLL2PCLK selected for SPI, PLAY1, LPTIM, ADC and POSENC.
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetP(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2P) >>  RCC_PLL2DIVR_PLL2P_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL2Q.
  * @rmtoll
  *  PLL2DIVR         PLL2Q         LL_RCC_PLL2_SetQ
  * @param pll2q parameter can be a value between 1 and 128
  * @note   Used for PLL2QCLK selected for USART, UART, LPUART, DAC, UCPD, USB, FDCAN and POSENC.
  */
__STATIC_INLINE void LL_RCC_PLL2_SetQ(uint32_t pll2q)
{
  STM32_MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2Q, (pll2q - 1UL) << RCC_PLL2DIVR_PLL2Q_Pos);
}

/**
  * @brief  Get Division factor for PLL2Q.
  * @rmtoll
  *  PLL2DIVR         PLL2Q         LL_RCC_PLL2_GetQ
  * @note   Used for PLL2QCLK selected for USART, UART, LPUART, DAC, UCPD, USB, FDCAN and POSENC.
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetQ(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2Q) >>  RCC_PLL2DIVR_PLL2Q_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL2R.
  * @rmtoll
  *  PLL2DIVR         PLL2R         LL_RCC_PLL2_SetR
  * @param pll2r parameter can be a value between 1 and 128
  * @note   Used for PLL2RCLK selected for ICLK2 (XSPI and POSENC).
  */
__STATIC_INLINE void LL_RCC_PLL2_SetR(uint32_t pll2r)
{
  STM32_MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2R, (pll2r - 1UL) << RCC_PLL2DIVR_PLL2R_Pos);
}

/**
  * @brief  Get Division factor for PLL2R.
  * @rmtoll
  *  PLL2DIVR         PLL2R         LL_RCC_PLL2_GetR
  * @note   Used for PLL2RCLK selected for ICLK2 (XSPI and POSENC).
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetR(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2R) >>  RCC_PLL2DIVR_PLL2R_Pos) + 1UL);
}

/**
  * @brief  Enable PLL2 FRACN.
  * @rmtoll
  *  PLL2CFGR         PLL2FRACEN         LL_RCC_PLL2_EnableFRACN
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableFRACN(void)
{
  STM32_SET_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2FRACEN);
}

/**
  * @brief  Disable PLL2 FRACN.
  * @rmtoll
  *  PLL2CFGR         PLL2FRACEN         LL_RCC_PLL2_DisableFRACN
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableFRACN(void)
{
  STM32_CLEAR_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2FRACEN);
}

/**
  * @brief  Check if PLL2 FRACN is enabled.
  * @rmtoll
  *  PLL2CFGR         PLL2FRACEN         LL_RCC_PLL2_IsEnabledFRACN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledFRACN(void)
{
  return ((STM32_READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2FRACEN) == RCC_PLL2CFGR_PLL2FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL2 FRACN Coefficient.
  * @rmtoll
  *  PLL2FRACR         PLL2FRACN         LL_RCC_PLL2_SetFRACN
  * @param  fracn parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL2_SetFRACN(uint32_t fracn)
{
  STM32_MODIFY_REG(RCC->PLL2FRACR, RCC_PLL2FRACR_PLL2FRACN, fracn << RCC_PLL2FRACR_PLL2FRACN_Pos);
}

/**
  * @brief  Get PLL2 FRACN Coefficient.
  * @rmtoll
  *  PLL2FRACR         PLL2FRACN         LL_RCC_PLL2_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetFRACN(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL2FRACR, RCC_PLL2FRACR_PLL2FRACN) >>  RCC_PLL2FRACR_PLL2FRACN_Pos);
}

/**
  * @brief  Set PLL2 Input Range.
  * @rmtoll
  *  PLL2CFGR         PLL2RGE         LL_RCC_PLL2_SetInputRange
  * @param  input_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLLINPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  * @note   This API must be called only when PLL2 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL2_SetInputRange(uint32_t input_range)
{
  STM32_MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2RGE, input_range);
}

/**
  * @brief  Get PLL2 Input Range.
  * @rmtoll
  *  PLL2CFGR         PLL2RGE         LL_RCC_PLL2_GetInputRange
  * @retval  The Input range. This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLLINPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetInputRange(void)
{
  return (STM32_READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2RGE));
}

/**
  * @brief  Set PLL2 VCO Range.
  * @rmtoll
  *  PLL2CFGR         PLL2VCOSEL         LL_RCC_PLL2_SetVCORange
  * @param  vco_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLVCORANGE_128_560
  *         @arg @ref LL_RCC_PLLVCORANGE_150_420
  * @note   This API must be called only when PLL2 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL2_SetVCORange(uint32_t vco_range)
{
  STM32_MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2VCOSEL, vco_range);
}

/**
  * @brief  Get PLL2 VCO Range.
  * @rmtoll
  *  PLL2CFGR         PLL2VCOSEL         LL_RCC_PLL2_GetVCORange
  * @retval  The VCO range. This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLVCORANGE_128_560
  *         @arg @ref LL_RCC_PLLVCORANGE_150_420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetVCORange(void)
{
  return (STM32_READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2VCOSEL));
}
/**
  * @}
  */
#endif /* PLL2 */

/** @defgroup RCC_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable RCC interrupts.
  * @rmtoll
  *  IER         LSIRDYIE           LL_RCC_EnableIT \n
  *  IER         LSERDYIE           LL_RCC_EnableIT \n
  *  IER         HSIRDYIE           LL_RCC_EnableIT \n
  *  IER         HSERDYIE           LL_RCC_EnableIT \n
  *  IER         HSI48RDYIE         LL_RCC_EnableIT \n
  *  IER         PLL1RDYIE          LL_RCC_EnableIT \n
  *  IER         PLL2RDYIE          LL_RCC_EnableIT \n
  *  IER         LSECSSIE           LL_RCC_EnableIT
  * @param  mask specifies the RCC IT to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_HSI48RDY
  *            @arg @ref LL_RCC_IT_PLL1RDY
  *            @arg @ref LL_RCC_IT_PLL2RDY
  *            @arg @ref LL_RCC_IT_LSECSS
  */
__STATIC_INLINE void LL_RCC_EnableIT(uint32_t mask)
{
  STM32_SET_BIT(RCC->IER, mask);
}

/**
  * @brief  Enable LSI ready interrupt.
  * @rmtoll
  *  IER         LSIRDYIE         LL_RCC_EnableIT_LSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSIRDY(void)
{
  STM32_SET_BIT(RCC->IER, RCC_IER_LSIRDYIE);
}

/**
  * @brief  Enable LSE ready interrupt.
  * @rmtoll
  *  IER         LSERDYIE         LL_RCC_EnableIT_LSERDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSERDY(void)
{
  STM32_SET_BIT(RCC->IER, RCC_IER_LSERDYIE);
}

/**
  * @brief  Enable HSI ready interrupt.
  * @rmtoll
  *  IER         HSIRDYIE         LL_RCC_EnableIT_HSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSIRDY(void)
{
  STM32_SET_BIT(RCC->IER, RCC_IER_HSIRDYIE);
}

/**
  * @brief  Enable HSE ready interrupt.
  * @rmtoll
  *  IER         HSERDYIE         LL_RCC_EnableIT_HSERDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSERDY(void)
{
  STM32_SET_BIT(RCC->IER, RCC_IER_HSERDYIE);
}

#if defined(HSI48)
/**
  * @brief  Enable HSI48 ready interrupt.
  * @rmtoll
  *  IER         HSI48RDYIE         LL_RCC_EnableIT_HSI48RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSI48RDY(void)
{
  STM32_SET_BIT(RCC->IER, RCC_IER_HSI48RDYIE);
}
#endif /* HSI48 */

/**
  * @brief  Enable PLL1 ready interrupt.
  * @rmtoll
  *  IER         PLL1RDYIE         LL_RCC_EnableIT_PLL1RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL1RDY(void)
{
  STM32_SET_BIT(RCC->IER, RCC_IER_PLL1RDYIE);
}

#if defined(PLL2)
/**
  * @brief  Enable PLL2 ready interrupt.
  * @rmtoll
  *  IER         PLL2RDYIE         LL_RCC_EnableIT_PLL2RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL2RDY(void)
{
  STM32_SET_BIT(RCC->IER, RCC_IER_PLL2RDYIE);
}
#endif /* PLL2 */

/**
  * @brief  Enable LSECSS interrupt.
  * @rmtoll
  *  IER         LSECSSIE         LL_RCC_EnableIT_LSECSS
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSECSS(void)
{
  STM32_SET_BIT(RCC->IER, RCC_IER_LSECSSIE);
}


/**
  * @brief  Disable RCC interrupts.
  * @rmtoll
  *  IER         LSIRDYIE           LL_RCC_DisableIT \n
  *  IER         LSERDYIE           LL_RCC_DisableIT \n
  *  IER         HSIRDYIE           LL_RCC_DisableIT \n
  *  IER         HSERDYIE           LL_RCC_DisableIT \n
  *  IER         HSI48RDYIE         LL_RCC_DisableIT \n
  *  IER         PLL1RDYIE          LL_RCC_DisableIT \n
  *  IER         PLL2RDYIE          LL_RCC_DisableIT \n
  *  IER         LSECSSIE           LL_RCC_DisableIT
  * @param  mask specifies the RCC IT to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_HSI48RDY (*)
  *            @arg @ref LL_RCC_IT_PLL1RDY
  *            @arg @ref LL_RCC_IT_PLL2RDY (*)
  *            @arg @ref LL_RCC_IT_LSECSS
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_DisableIT(uint32_t mask)
{
  STM32_CLEAR_BIT(RCC->IER, mask);
}

/**
  * @brief  Disable LSI ready interrupt.
  * @rmtoll
  *  IER         LSIRDYIE         LL_RCC_DisableIT_LSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSIRDY(void)
{
  STM32_CLEAR_BIT(RCC->IER, RCC_IER_LSIRDYIE);
}

/**
  * @brief  Disable LSE ready interrupt.
  * @rmtoll
  *  IER         LSERDYIE         LL_RCC_DisableIT_LSERDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSERDY(void)
{
  STM32_CLEAR_BIT(RCC->IER, RCC_IER_LSERDYIE);
}

/**
  * @brief  Disable HSI ready interrupt.
  * @rmtoll
  *  IER         HSIRDYIE         LL_RCC_DisableIT_HSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIRDY(void)
{
  STM32_CLEAR_BIT(RCC->IER, RCC_IER_HSIRDYIE);
}

/**
  * @brief  Disable HSE ready interrupt.
  * @rmtoll
  *  IER         HSERDYIE         LL_RCC_DisableIT_HSERDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSERDY(void)
{
  STM32_CLEAR_BIT(RCC->IER, RCC_IER_HSERDYIE);
}

#if defined(HSI48)
/**
  * @brief  Disable HSI48 ready interrupt.
  * @rmtoll
  *  IER         HSI48RDYIE         LL_RCC_DisableIT_HSI48RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSI48RDY(void)
{
  STM32_CLEAR_BIT(RCC->IER, RCC_IER_HSI48RDYIE);
}
#endif /* HSI48 */

/**
  * @brief  Disable PLL1 ready interrupt.
  * @rmtoll
  *  IER         PLL1RDYIE         LL_RCC_DisableIT_PLL1RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL1RDY(void)
{
  STM32_CLEAR_BIT(RCC->IER, RCC_IER_PLL1RDYIE);
}

#if defined(PLL2)
/**
  * @brief  Disable PLL2 ready interrupt.
  * @rmtoll
  *  IER         PLL2RDYIE         LL_RCC_DisableIT_PLL2RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL2RDY(void)
{
  STM32_CLEAR_BIT(RCC->IER, RCC_IER_PLL2RDYIE);
}
#endif /* PLL2 */

/**
  * @brief  Disable LSECSS interrupt.
  * @rmtoll
  *  IER         LSECSSIE         LL_RCC_DisableIT_LSECSS
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSECSS(void)
{
  STM32_CLEAR_BIT(RCC->IER, RCC_IER_LSECSSIE);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  IER         LSIRDYIE         LL_RCC_IsEnabledIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSIRDY(void)
{
  return ((STM32_READ_BIT(RCC->IER, RCC_IER_LSIRDYIE) == RCC_IER_LSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE ready interrupt source is enabled or disabled.
  * @rmtoll
  *  IER         LSERDYIE         LL_RCC_IsEnabledIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSERDY(void)
{
  return ((STM32_READ_BIT(RCC->IER, RCC_IER_LSERDYIE) == RCC_IER_LSERDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  IER         HSIRDYIE         LL_RCC_IsEnabledIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIRDY(void)
{
  return ((STM32_READ_BIT(RCC->IER, RCC_IER_HSIRDYIE) == RCC_IER_HSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE ready interrupt source is enabled or disabled.
  * @rmtoll
  *  IER         HSERDYIE         LL_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSERDY(void)
{
  return ((STM32_READ_BIT(RCC->IER, RCC_IER_HSERDYIE) == RCC_IER_HSERDYIE) ? 1UL : 0UL);
}
#if defined(HSI48)
/**
  * @brief  Check if HSI48 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  IER         HSI48RDYIE         LL_RCC_IsEnabledIT_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSI48RDY(void)
{
  return ((STM32_READ_BIT(RCC->IER, RCC_IER_HSI48RDYIE) == RCC_IER_HSI48RDYIE) ? 1UL : 0UL);
}
#endif /* HSI48 */

/**
  * @brief  Check if PLL1 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  IER         PLL1RDYIE         LL_RCC_IsEnabledIT_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL1RDY(void)
{
  return ((STM32_READ_BIT(RCC->IER, RCC_IER_PLL1RDYIE) == RCC_IER_PLL1RDYIE) ? 1UL : 0UL);
}

#if defined(PLL2)
/**
  * @brief  Check if PLL2 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  IER         PLL2RDYIE         LL_RCC_IsEnabledIT_PLL2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL2RDY(void)
{
  return ((STM32_READ_BIT(RCC->IER, RCC_IER_PLL2RDYIE) == RCC_IER_PLL2RDYIE) ? 1UL : 0UL);
}
#endif /* PLL2 */

/**
  * @brief  Check if LSECSS interrupt source is enabled or disabled.
  * @rmtoll
  *  IER         LSECSSIE         LL_RCC_IsEnabledIT_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSECSS(void)
{
  return ((STM32_READ_BIT(RCC->IER, RCC_IER_LSECSSIE) == RCC_IER_LSECSSIE) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_FLAG_Management FLAG Management
  * @{
  */
/**
  * @brief  Clear RCC interrupt flags.
  * @rmtoll
  *  ICR         LSIRDYC           LL_RCC_ClearFlag \n
  *  ICR         LSERDYC           LL_RCC_ClearFlag \n
  *  ICR         HSIRDYC           LL_RCC_ClearFlag \n
  *  ICR         HSERDYC           LL_RCC_ClearFlag \n
  *  ICR         HSI48RDYC         LL_RCC_ClearFlag \n
  *  ICR         PLL1RDYC          LL_RCC_ClearFlag \n
  *  ICR         PLL2RDYC          LL_RCC_ClearFlag \n
  *  ICR         LSECSSC           LL_RCC_ClearFlag \n
  *  ICR         HSECSSC           LL_RCC_ClearFlag
  * @param  mask specifies the RCC flags to be cleared.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_HSI48RDY (*)
  *            @arg @ref LL_RCC_IT_PLL1RDY
  *            @arg @ref LL_RCC_IT_PLL2RDY (*)
  *            @arg @ref LL_RCC_IT_LSECSS
  *            @arg @ref LL_RCC_IT_HSECSS
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_ClearFlag(uint32_t mask)
{
  STM32_WRITE_REG(RCC->ICR, mask);
}

/**
  * @brief  Clear LSI ready interrupt flag.
  * @rmtoll
  *  ICR         LSIRDYC         LL_RCC_ClearFlag_LSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSIRDY(void)
{
  STM32_SET_BIT(RCC->ICR, RCC_ICR_LSIRDYC);
}

/**
  * @brief  Clear LSE ready interrupt flag.
  * @rmtoll
  *  ICR         LSERDYC         LL_RCC_ClearFlag_LSERDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSERDY(void)
{
  STM32_SET_BIT(RCC->ICR, RCC_ICR_LSERDYC);
}

/**
  * @brief  Clear HSI ready interrupt flag.
  * @rmtoll
  *  ICR         HSIRDYC         LL_RCC_ClearFlag_HSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIRDY(void)
{
  STM32_SET_BIT(RCC->ICR, RCC_ICR_HSIRDYC);
}

/**
  * @brief  Clear HSE ready interrupt flag.
  * @rmtoll
  *  ICR         HSERDYC         LL_RCC_ClearFlag_HSERDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSERDY(void)
{
  STM32_SET_BIT(RCC->ICR, RCC_ICR_HSERDYC);
}
#if defined(HSI48)
/**
  * @brief  Clear HSI48 ready interrupt flag.
  * @rmtoll
  *  ICR         HSI48RDYC         LL_RCC_ClearFlag_HSI48RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSI48RDY(void)
{
  STM32_SET_BIT(RCC->ICR, RCC_ICR_HSI48RDYC);
}
#endif /* HSI48 */
/**
  * @brief  Clear PLL1 ready interrupt flag.
  * @rmtoll
  *  ICR         PLL1RDYC         LL_RCC_ClearFlag_PLL1RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL1RDY(void)
{
  STM32_SET_BIT(RCC->ICR, RCC_ICR_PLL1RDYC);
}

#if defined(PLL2)
/**
  * @brief  Clear PLL2 ready interrupt flag.
  * @rmtoll
  *  ICR         PLL2RDYC         LL_RCC_ClearFlag_PLL2RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL2RDY(void)
{
  STM32_SET_BIT(RCC->ICR, RCC_ICR_PLL2RDYC);
}
#endif /* PLL2 */
/**
  * @brief  Clear LSECSS interrupt flag.
  * @rmtoll
  *  ICR         LSECSSC         LL_RCC_ClearFlag_LSECSS
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSECSS(void)
{
  STM32_SET_BIT(RCC->ICR, RCC_ICR_LSECSSC);
}

/**
  * @brief  Clear HSECSS interrupt flag.
  * @rmtoll
  *  ICR         HSECSSC         LL_RCC_ClearFlag_HSECSS
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSECSS(void)
{
  STM32_SET_BIT(RCC->ICR, RCC_ICR_HSECSSC);
}


/**
  * @brief  Check if RCC ready interrupt occurred or not.
  * @rmtoll
  *  IFR         LSIRDYF           LL_RCC_IsActiveFlag \n
  *  IFR         LSERDYF           LL_RCC_IsActiveFlag \n
  *  IFR         HSIRDYF           LL_RCC_IsActiveFlag \n
  *  IFR         HSERDYF           LL_RCC_IsActiveFlag \n
  *  IFR         HSI48RDYF         LL_RCC_IsActiveFlag \n
  *  IFR         PLL1RDYF          LL_RCC_IsActiveFlag \n
  *  IFR         PLL2RDYF          LL_RCC_IsActiveFlag \n
  *  IFR         LSECSSF           LL_RCC_IsActiveFlag \n
  *  IFR         HSECSSF           LL_RCC_IsActiveFlag
  * @param  mask specifies the RCC flags to be cleared.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_HSI48RDY (*)
  *            @arg @ref LL_RCC_IT_PLL1RDY
  *            @arg @ref LL_RCC_IT_PLL2RDY (*)
  *            @arg @ref LL_RCC_IT_LSECSS
  *            @arg @ref LL_RCC_IT_HSECSS
  * @retval State of flags (1 or 0).
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag(uint32_t mask)
{
  return ((STM32_READ_BIT(RCC->IFR, mask) == mask) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSIRDY ready interrupt occurred or not.
  * @rmtoll
  *  IFR         LSIRDYF         LL_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSIRDY(void)
{
  return ((STM32_READ_BIT(RCC->IFR, RCC_IFR_LSIRDYF) == RCC_IFR_LSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSERDY ready interrupt occurred or not.
  * @rmtoll
  *  IFR         LSERDYF         LL_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSERDY(void)
{
  return ((STM32_READ_BIT(RCC->IFR, RCC_IFR_LSERDYF) == RCC_IFR_LSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSIRDY ready interrupt occurred or not.
  * @rmtoll
  *  IFR         HSIRDYF         LL_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIRDY(void)
{
  return ((STM32_READ_BIT(RCC->IFR, RCC_IFR_HSIRDYF) == RCC_IFR_HSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSERDY ready interrupt occurred or not.
  * @rmtoll
  *  IFR         HSERDYF         LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((STM32_READ_BIT(RCC->IFR, RCC_IFR_HSERDYF) == RCC_IFR_HSERDYF) ? 1UL : 0UL);
}

#if defined(HSI48)
/**
  * @brief  Check if HSI48RDY ready interrupt occurred or not.
  * @rmtoll
  *  IFR         HSI48RDYF         LL_RCC_IsActiveFlag_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSI48RDY(void)
{
  return ((STM32_READ_BIT(RCC->IFR, RCC_IFR_HSI48RDYF) == RCC_IFR_HSI48RDYF) ? 1UL : 0UL);
}
#endif /* HSI48 */

/**
  * @brief  Check if PLL1RDY ready interrupt occurred or not.
  * @rmtoll
  *  IFR         PLL1RDYF         LL_RCC_IsActiveFlag_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL1RDY(void)
{
  return ((STM32_READ_BIT(RCC->IFR, RCC_IFR_PLL1RDYF) == RCC_IFR_PLL1RDYF) ? 1UL : 0UL);
}

#if defined(PLL2)
/**
  * @brief  Check if PLL2RDY ready interrupt occurred or not.
  * @rmtoll
  *  IFR         PLL2RDYF         LL_RCC_IsActiveFlag_PLL2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL2RDY(void)
{
  return ((STM32_READ_BIT(RCC->IFR, RCC_IFR_PLL2RDYF) == RCC_IFR_PLL2RDYF) ? 1UL : 0UL);
}
#endif /* PLL2 */

/**
  * @brief  Check if LSECSS ready interrupt occurred or not.
  * @rmtoll
  *  IFR         LSECSSF         LL_RCC_IsActiveFlag_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSECSS(void)
{
  return ((STM32_READ_BIT(RCC->IFR, RCC_IFR_LSECSSF) == RCC_IFR_LSECSSF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSECSS ready interrupt occurred or not.
  * @rmtoll
  *  IFR         HSECSSF         LL_RCC_IsActiveFlag_HSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSECSS(void)
{
  return ((STM32_READ_BIT(RCC->IFR, RCC_IFR_HSECSSF) == RCC_IFR_HSECSSF) ? 1UL : 0UL);
}

/**
  * @brief  Set RMVF bit to clear the reset flags.
  * @rmtoll
  *  RSR         RMVF         LL_RCC_ClearResetFlags
  */
__STATIC_INLINE void LL_RCC_ClearResetFlags(void)
{
  STM32_SET_BIT(RCC->RSR, RCC_RSR_RMVF);
}

/**
  * @brief  Check if RCC pin reset flag (NRST) is set or not.
  * @rmtoll
  *  RSR         PINRSTF         LL_RCC_IsActiveFlag_PINRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PINRST(void)
{
  return ((STM32_READ_BIT(RCC->RSR, RCC_RSR_PINRSTF) == RCC_RSR_PINRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC POR reset flag is set or not.
  * @rmtoll
  *  RSR         PORRSTF         LL_RCC_IsActiveFlag_PORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PORRST(void)
{
  return ((STM32_READ_BIT(RCC->RSR, RCC_RSR_PORRSTF) == RCC_RSR_PORRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC system reset from CPU reset flag is set or not.
  * @rmtoll
  *  RSR         SFTRSTF         LL_RCC_IsActiveFlag_SFTRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SFTRST(void)
{
  return ((STM32_READ_BIT(RCC->RSR, RCC_RSR_SFTRSTF) == RCC_RSR_SFTRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC independent watchdog reset flag is set or not.
  * @rmtoll
  *  RSR         IWDGRSTF         LL_RCC_IsActiveFlag_IWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDGRST(void)
{
  return ((STM32_READ_BIT(RCC->RSR, RCC_RSR_IWDGRSTF) == RCC_RSR_IWDGRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC window watchdog reset flag is set or not.
  * @rmtoll
  *  RSR         WWDGRSTF         LL_RCC_IsActiveFlag_WWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WWDGRST(void)
{
  return ((STM32_READ_BIT(RCC->RSR, RCC_RSR_WWDGRSTF) == RCC_RSR_WWDGRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC Low-power reset flag is set or not.
  * @rmtoll
  *  RSR         LPWRRSTF         LL_RCC_IsActiveFlag_LPWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LPWRRST(void)
{
  return ((STM32_READ_BIT(RCC->RSR, RCC_RSR_LPWRRSTF) == RCC_RSR_LPWRRSTF) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_Privilege_Services Privilege Services
  * @{
  */

/**
  * @brief  Set the privileged access level attribute for item(s).
  * @rmtoll
  *  PRIVCFGR     SPRIV         LL_RCC_SetPrivAttr \n
  *  PRIVCFGR     NSPRIV        LL_RCC_SetPrivAttr
  * @param  item This parameter can be a combination of the following values:
  *         @arg @ref LL_RCC_PRIV_ITEM_SPRIV
  *         @arg @ref LL_RCC_PRIV_ITEM_NSPRIV
  *         @arg @ref LL_RCC_PRIV_ITEM_ALL
  * @param priv_attr This parameter can be one of the following values:
  *        @arg @ref LL_RCC_ATTR_PRIV
  *        @arg @ref LL_RCC_ATTR_NPRIV
  * @note If an item is secured, its privilege attribute can be configured by secure and privileged accesses.
  *       If an item is not secured, its privilege attribute can be configured by privileged, secure,
  *       or nonsecure access.
  */
__STATIC_INLINE void LL_RCC_SetPrivAttr(uint32_t item, uint32_t priv_attr)
{
  STM32_MODIFY_REG(RCC->PRIVCFGR, item, (item * priv_attr));
}

/**
  * @brief  Get the privileged access level attribute of an item.
  * @rmtoll
  *  PRIVCFGR     SPRIV         LL_RCC_GetPrivAttr \n
  *  PRIVCFGR     NSPRIV        LL_RCC_GetPrivAttr
  * @param  item This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PRIV_ITEM_SPRIV
  *         @arg @ref LL_RCC_PRIV_ITEM_NSPRIV
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ATTR_PRIV
  *         @arg @ref LL_RCC_ATTR_NPRIV
  */
__STATIC_INLINE uint32_t LL_RCC_GetPrivAttr(uint32_t item)
{
  return ((STM32_READ_BIT(RCC->PRIVCFGR, item) == (item)) ? LL_RCC_ATTR_PRIV : LL_RCC_ATTR_NPRIV);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_Security_Services Security Services
  * @{
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the security access level attribute for item(s).
  * @rmtoll
  *  SECCFGR     HSISEC        LL_RCC_SetSecAttr \n
  *  SECCFGR     HSESEC        LL_RCC_SetSecAttr \n
  *  SECCFGR     LSISEC        LL_RCC_SetSecAttr \n
  *  SECCFGR     LSESEC        LL_RCC_SetSecAttr \n
  *  SECCFGR     SYSCLKSEC     LL_RCC_SetSecAttr \n
  *  SECCFGR     PRESCSEC      LL_RCC_SetSecAttr \n
  *  SECCFGR     PLL1SEC       LL_RCC_SetSecAttr \n
  *  SECCFGR     PLL2SEC       LL_RCC_SetSecAttr \n
  *  SECCFGR     HSI48SEC      LL_RCC_SetSecAttr \n
  *  SECCFGR     RMVFSEC       LL_RCC_SetSecAttr
  * @param  item This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_SEC_ITEM_HSI
  *         @arg @ref LL_RCC_SEC_ITEM_HSE
  *         @arg @ref LL_RCC_SEC_ITEM_LSI
  *         @arg @ref LL_RCC_SEC_ITEM_LSE
  *         @arg @ref LL_RCC_SEC_ITEM_SYSCLK
  *         @arg @ref LL_RCC_SEC_ITEM_PRESCALERS
  *         @arg @ref LL_RCC_SEC_ITEM_PLL1
  *         @arg @ref LL_RCC_SEC_ITEM_PLL2 (*)
  *         @arg @ref LL_RCC_SEC_ITEM_HSI48 (*)
  *         @arg @ref LL_RCC_SEC_ITEM_RESET_FLAGS
  *         @arg @ref LL_RCC_SEC_ITEM_ALL
  *
  *        (*) value not defined in all devices.
  * @param sec_attr This parameter can be one of the following values:
  *        @arg @ref LL_RCC_ATTR_SEC
  *        @arg @ref LL_RCC_ATTR_NSEC
  * @note Only available from secure and privileged state.
  */
__STATIC_INLINE void LL_RCC_SetSecAttr(uint32_t item, uint32_t sec_attr)
{
  STM32_MODIFY_REG(RCC->SECCFGR, item, (item * sec_attr));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the security access level attribute of an item.
  * @rmtoll
  *  SECCFGR     HSISEC        LL_RCC_GetSecAttr \n
  *  SECCFGR     HSESEC        LL_RCC_GetSecAttr \n
  *  SECCFGR     LSISEC        LL_RCC_GetSecAttr \n
  *  SECCFGR     LSESEC        LL_RCC_GetSecAttr \n
  *  SECCFGR     SYSCLKSEC     LL_RCC_GetSecAttr \n
  *  SECCFGR     PRESCSEC      LL_RCC_GetSecAttr \n
  *  SECCFGR     PLL1SEC       LL_RCC_GetSecAttr \n
  *  SECCFGR     PLL2SEC       LL_RCC_GetSecAttr \n
  *  SECCFGR     HSI48SEC      LL_RCC_GetSecAttr \n
  *  SECCFGR     RMVFSEC       LL_RCC_GetSecAttr
  * @param  item This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SEC_ITEM_HSI
  *         @arg @ref LL_RCC_SEC_ITEM_HSE
  *         @arg @ref LL_RCC_SEC_ITEM_LSI
  *         @arg @ref LL_RCC_SEC_ITEM_LSE
  *         @arg @ref LL_RCC_SEC_ITEM_SYSCLK
  *         @arg @ref LL_RCC_SEC_ITEM_PRESCALERS
  *         @arg @ref LL_RCC_SEC_ITEM_PLL1
  *         @arg @ref LL_RCC_SEC_ITEM_PLL2 (*)
  *         @arg @ref LL_RCC_SEC_ITEM_HSI48 (*)
  *         @arg @ref LL_RCC_SEC_ITEM_RESET_FLAGS
  *
  *        (*) value not defined in all devices.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ATTR_SEC
  *         @arg @ref LL_RCC_ATTR_NSEC
  */
__STATIC_INLINE uint32_t LL_RCC_GetSecAttr(uint32_t item)
{
  return ((STM32_READ_BIT(RCC->SECCFGR, item) == (item)) ? LL_RCC_ATTR_SEC : LL_RCC_ATTR_NSEC);
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

#endif /* RCC */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G5XX_LL_RCC_H */
