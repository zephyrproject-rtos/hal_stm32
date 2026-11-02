/**
  ******************************************************************************
  * @file    stm32h7pxx_ll_rcc.h
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
#ifndef STM32H7PXX_LL_RCC_H
#define STM32H7PXX_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7PXX_LL_Driver
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

#define LL_RCC_CONFIG_SHIFT     0U
#define LL_RCC_MASK_SHIFT       8U
#define LL_RCC_POS_SHIFT        16U
#define LL_RCC_REG_SHIFT        24U

/* Defines used for HSI default trimming value */
#define LL_RCC_HSICALIBRATION_DEFAULT     0x40U  /*!< Default HSI trimming value */

/* Defines used for CSI default trimming value */
#define LL_RCC_CSICALIBRATION_DEFAULT     0x20U  /*!< Default CSI trimming value */

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

/** @defgroup RCC_LL_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup LL_RCC_HSE_Config HSE Config
  * @{
  */
#define LL_RCC_HSE_ON             RCC_CR_HSEON                                   /*!< HSE clock activation                       */
#define LL_RCC_HSE_BYPASS         (RCC_CR_HSEON | RCC_CR_HSEBYP)                 /*!< External analog clock source for HSE clock */
#define LL_RCC_HSE_BYPASS_DIGITAL (RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_HSEEXT) /*!< External clock source for HSE clock        */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_HSE External HSE mode
  * @{
  */
#define LL_RCC_HSE_ANALOG_TYPE  0U            /*!< ANALOG clock used as HSE external clock source  */
#define LL_RCC_HSE_DIGITAL_TYPE RCC_CR_HSEEXT /*!< DIGITAL clock used as HSE external clock source */
/**
  * @}
  */

/** @defgroup LL_RCC_LSE_Config LSE Config
  * @{
  */
#define LL_RCC_LSE_ON               RCC_BDCR_LSEON                                        /*!< LSE clock activation                        */
#define LL_RCC_LSE_BYPASS           (RCC_BDCR_LSEON | RCC_BDCR_LSEBYP)                    /*!< External analog clock source for LSE clock  */
#define LL_RCC_LSE_BYPASS_DIGITAL   (RCC_BDCR_LSEON | RCC_BDCR_LSEBYP | RCC_BDCR_LSEEXT)  /*!< External digital clock source for LSE clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSE External LSE mode
  * @{
  */
#define LL_RCC_LSE_ANALOG_TYPE  0U              /*!< ANALOG clock used as LSE external clock source  */
#define LL_RCC_LSE_DIGITAL_TYPE RCC_BDCR_LSEEXT /*!< DIGITAL clock used as LSE external clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSE LSE oscillator driving capability
  * @{
  */
#define LL_RCC_LSEDRIVE_LOW        0U                /*!< Crystal mode low driving capability         */
#define LL_RCC_LSEDRIVE_MEDIUMLOW  RCC_BDCR_LSEDRV_0 /*!< Crystal mode medium-low driving capability  */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH RCC_BDCR_LSEDRV_1 /*!< Crystal mode medium-high driving capability */
#define LL_RCC_LSEDRIVE_HIGH       RCC_BDCR_LSEDRV   /*!< Crystal mode high driving capability        */
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
#define LL_RCC_SYS_CLKSOURCE_HSI  0U                              /*!< HSI clock used as system clock  */
#define LL_RCC_SYS_CLKSOURCE_CSI  RCC_CFGR_SW_0                   /*!< CSI clock used as system clock  */
#define LL_RCC_SYS_CLKSOURCE_HSE  RCC_CFGR_SW_1                   /*!< HSE clock used as system clock  */
#define LL_RCC_SYS_CLKSOURCE_PLL1 (RCC_CFGR_SW_1 | RCC_CFGR_SW_0) /*!< PLL1 clock used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE_STATUS System clock switch status
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSI  0U                                /*!< HSI clock used as system clock   */
#define LL_RCC_SYS_CLKSOURCE_STATUS_CSI  RCC_CFGR_SWS_0                    /*!< CSI clock used as system clock   */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSE  RCC_CFGR_SWS_1                    /*!< HSE clock used as system clock   */
#define LL_RCC_SYS_CLKSOURCE_STATUS_PLL1 (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0) /*!< PLL1P clock used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_STOP_WAKEUPCLOCK System clock selection after a wakeup from system Stop
  * @{
  */
#define LL_RCC_STOP_WAKEUPCLOCK_HSI 0U                /*!< HSI clock used as system clock after wake-up from STOP */
#define LL_RCC_STOP_WAKEUPCLOCK_CSI RCC_CFGR_STOPWUCK /*!< CSI clock used as system clock after wake-up from STOP */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_STOP_WAKEUPKERCLOCK System kernel clock selection after a wakeup from system Stop
  * @{
  */
#define LL_RCC_STOP_WAKEUPKERCLOCK_HSI 0U                   /*!< HSI clock used as kernel clock after wake-up from STOP */
#define LL_RCC_STOP_WAKEUPKERCLOCK_CSI RCC_CFGR_STOPKERWUCK /*!< CSI clock used as kernel clock after wake-up from STOP */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_DIV System prescaler
  * @{
  */
#define LL_RCC_SYSCLK_PRESCALER_1   0U                                                          /*!< SYSCLK not divided    */
#define LL_RCC_SYSCLK_PRESCALER_2   RCC_CDCFGR_CPRE_3                                           /*!< SYSCLK divided by 2   */
#define LL_RCC_SYSCLK_PRESCALER_4   (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_0)                     /*!< SYSCLK divided by 4   */
#define LL_RCC_SYSCLK_PRESCALER_8   (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_1)                     /*!< SYSCLK divided by 8   */
#define LL_RCC_SYSCLK_PRESCALER_16  (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_1 | RCC_CDCFGR_CPRE_0) /*!< SYSCLK divided by 16  */
#define LL_RCC_SYSCLK_PRESCALER_64  (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_2)                     /*!< SYSCLK divided by 64  */
#define LL_RCC_SYSCLK_PRESCALER_128 (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_2 | RCC_CDCFGR_CPRE_0) /*!< SYSCLK divided by 128 */
#define LL_RCC_SYSCLK_PRESCALER_256 (RCC_CDCFGR_CPRE_3 | RCC_CDCFGR_CPRE_2 | RCC_CDCFGR_CPRE_1) /*!< SYSCLK divided by 256 */
#define LL_RCC_SYSCLK_PRESCALER_512 RCC_CDCFGR_CPRE                                             /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_BMCLK_DIV  Bus Matrix prescaler (AXI Bus, AHBx)
  * @{
  */
#define LL_RCC_BMCLK_PRESCALER_1   0U                    /*!< SYSCLK not divided  */
#define LL_RCC_BMCLK_PRESCALER_2   RCC_BMCFGR_BMPRE_3    /*!< SYSCLK divided by 2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB1_DIV APB low-speed prescaler (APB1)
  * @{
  */
#define LL_RCC_APB1_PRESCALER_1  0U                                          /*!< ACLK not divided   */
#define LL_RCC_APB1_PRESCALER_2  RCC_APBCFGR_PPRE1_2                         /*!< ACLK divided by 2  */
#define LL_RCC_APB1_PRESCALER_4  (RCC_APBCFGR_PPRE1_2 | RCC_APBCFGR_PPRE1_0) /*!< ACLK divided by 4  */
#define LL_RCC_APB1_PRESCALER_8  (RCC_APBCFGR_PPRE1_2 | RCC_APBCFGR_PPRE1_1) /*!< ACLK divided by 8  */
#define LL_RCC_APB1_PRESCALER_16 RCC_APBCFGR_PPRE1                           /*!< ACLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB2_DIV APB low-speed prescaler (APB2)
  * @{
  */
#define LL_RCC_APB2_PRESCALER_1  0U                                          /*!< ACLK not divided   */
#define LL_RCC_APB2_PRESCALER_2  RCC_APBCFGR_PPRE2_2                         /*!< ACLK divided by 2  */
#define LL_RCC_APB2_PRESCALER_4  (RCC_APBCFGR_PPRE2_2 | RCC_APBCFGR_PPRE2_0) /*!< ACLK divided by 4  */
#define LL_RCC_APB2_PRESCALER_8  (RCC_APBCFGR_PPRE2_2 | RCC_APBCFGR_PPRE2_1) /*!< ACLK divided by 8  */
#define LL_RCC_APB2_PRESCALER_16 RCC_APBCFGR_PPRE2                           /*!< ACLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB4_DIV APB low-speed prescaler (APB4)
  * @{
  */
#define LL_RCC_APB4_PRESCALER_1  0U                                          /*!< ACLK not divided   */
#define LL_RCC_APB4_PRESCALER_2  RCC_APBCFGR_PPRE4_2                         /*!< ACLK divided by 2  */
#define LL_RCC_APB4_PRESCALER_4  (RCC_APBCFGR_PPRE4_2 | RCC_APBCFGR_PPRE4_0) /*!< ACLK divided by 4  */
#define LL_RCC_APB4_PRESCALER_8  (RCC_APBCFGR_PPRE4_2 | RCC_APBCFGR_PPRE4_1) /*!< ACLK divided by 8  */
#define LL_RCC_APB4_PRESCALER_16 RCC_APBCFGR_PPRE4                           /*!< ACLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1SOURCE MCO1 SOURCE selection
  * @{
  */
#define LL_RCC_MCO1SOURCE_HSI   (((uint32_t)RCC_CFGR_MCO1SEL>>16U) | 0x00000000U)                                /*!< HSI selection as MCO1 source   */
#define LL_RCC_MCO1SOURCE_LSE   (((uint32_t)RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_0)                         /*!< LSE selection as MCO1 source   */
#define LL_RCC_MCO1SOURCE_HSE   (((uint32_t)RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_1)                         /*!< HSE selection as MCO1 source   */
#define LL_RCC_MCO1SOURCE_PLL1Q (((uint32_t)RCC_CFGR_MCO1SEL>>16U) | (RCC_CFGR_MCO1SEL_1 | RCC_CFGR_MCO1SEL_0))  /*!< PLL1Q selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSI48 (((uint32_t)RCC_CFGR_MCO1SEL>>16U) | RCC_CFGR_MCO1SEL_2)                         /*!< HSI48 selection as MCO1 source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2SOURCE MCO2 SOURCE selection
  * @{
  */
#define LL_RCC_MCO2SOURCE_SYSCLK (((uint32_t)RCC_CFGR_MCO2SEL>>16U) | 0x00000000U)                               /*!< SYSTEM selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_PLL2P  (((uint32_t)RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_0)                        /*!< PLL2P selection as MCO2 source  */
#define LL_RCC_MCO2SOURCE_HSE    (((uint32_t)RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_1)                        /*!< HSE selection as MCO2 source    */
#define LL_RCC_MCO2SOURCE_PLL1P  (((uint32_t)RCC_CFGR_MCO2SEL>>16U) | (RCC_CFGR_MCO2SEL_1 | RCC_CFGR_MCO2SEL_0)) /*!< PLL1P selection as MCO2 source  */
#define LL_RCC_MCO2SOURCE_CSI    (((uint32_t)RCC_CFGR_MCO2SEL>>16U) | RCC_CFGR_MCO2SEL_2)                        /*!< CSI selection as MCO2 source    */
#define LL_RCC_MCO2SOURCE_LSI    (((uint32_t)RCC_CFGR_MCO2SEL>>16U) | (RCC_CFGR_MCO2SEL_2 | RCC_CFGR_MCO2SEL_0)) /*!< LSI selection as MCO2 source    */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1_DIV MCO1 prescaler
  * @{
  */
#define LL_RCC_MCO1SOURCE_NOCLOCK (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | 0x00000000U)                                                          /*!< MCO1 output disabled, no clock on MCO1 */
#define LL_RCC_MCO1_PRESCALER_1   (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_0)                                                   /*!< MCO1 is not divided      */
#define LL_RCC_MCO1_PRESCALER_2   (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_1)                                                   /*!< MCO1 is divided by 2     */
#define LL_RCC_MCO1_PRESCALER_3   (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | (RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_0))                            /*!< MCO1 is divided by 3     */
#define LL_RCC_MCO1_PRESCALER_4   (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_2)                                                   /*!< MCO1 is divided by 4     */
#define LL_RCC_MCO1_PRESCALER_5   (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | (RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_0))                            /*!< MCO1 is divided by 5     */
#define LL_RCC_MCO1_PRESCALER_6   (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | (RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1))                            /*!< MCO1 is divided by 6     */
#define LL_RCC_MCO1_PRESCALER_7   (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | (RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_0))       /*!< MCO1 is divided by 7     */
#define LL_RCC_MCO1_PRESCALER_8   (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE_3)                                                   /*!< MCO1 is divided by 8     */
#define LL_RCC_MCO1_PRESCALER_9   (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_0))                            /*!< MCO1 is divided by 9     */
#define LL_RCC_MCO1_PRESCALER_10  (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_1))                            /*!< MCO1 is divided by 10    */
#define LL_RCC_MCO1_PRESCALER_11  (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_0))       /*!< MCO1 is divided by 11    */
#define LL_RCC_MCO1_PRESCALER_12  (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_2))                            /*!< MCO1 is divided by 12    */
#define LL_RCC_MCO1_PRESCALER_13  (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_0))       /*!< MCO1 is divided by 13    */
#define LL_RCC_MCO1_PRESCALER_14  (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | (RCC_CFGR_MCO1PRE_3 | RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1))       /*!< MCO1 is divided by 14    */
#define LL_RCC_MCO1_PRESCALER_15  (((uint32_t)RCC_CFGR_MCO1PRE>>16U) | RCC_CFGR_MCO1PRE)                                                     /*!< MCO1 is divided by 15    */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2_DIV MCO2 prescaler
  * @{
  */
#define LL_RCC_MCO2SOURCE_NOCLOCK (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | 0x00000000U)                                                          /*!< MCO2 output disabled, no clock on MCO2 */
#define LL_RCC_MCO2_PRESCALER_1   (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_0)                                                   /*!< MCO2 is not divided      */
#define LL_RCC_MCO2_PRESCALER_2   (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_1)                                                   /*!< MCO2 is divided by 2     */
#define LL_RCC_MCO2_PRESCALER_3   (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | (RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_0))                            /*!< MCO2 is divided by 3     */
#define LL_RCC_MCO2_PRESCALER_4   (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_2)                                                   /*!< MCO2 is divided by 4     */
#define LL_RCC_MCO2_PRESCALER_5   (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_0))                            /*!< MCO2 is divided by 5     */
#define LL_RCC_MCO2_PRESCALER_6   (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1))                            /*!< MCO2 is divided by 6     */
#define LL_RCC_MCO2_PRESCALER_7   (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | (RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_0))       /*!< MCO2 is divided by 7     */
#define LL_RCC_MCO2_PRESCALER_8   (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE_3)                                                   /*!< MCO2 is divided by 8     */
#define LL_RCC_MCO2_PRESCALER_9   (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_0))                            /*!< MCO2 is divided by 9     */
#define LL_RCC_MCO2_PRESCALER_10  (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_1))                            /*!< MCO2 is divided by 10    */
#define LL_RCC_MCO2_PRESCALER_11  (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_0))       /*!< MCO2 is divided by 11    */
#define LL_RCC_MCO2_PRESCALER_12  (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_2))                            /*!< MCO2 is divided by 12    */
#define LL_RCC_MCO2_PRESCALER_13  (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_0))       /*!< MCO2 is divided by 13    */
#define LL_RCC_MCO2_PRESCALER_14  (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | (RCC_CFGR_MCO2PRE_3 | RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1))       /*!< MCO2 is divided by 14    */
#define LL_RCC_MCO2_PRESCALER_15  (((uint32_t)RCC_CFGR_MCO2PRE>>16U) | RCC_CFGR_MCO2PRE)                                                     /*!< MCO2 is divided by 15    */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_CLKSOURCE RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_NONE     0U                /*!< No clock used as RTC clock             */
#define LL_RCC_RTC_CLKSOURCE_LSE      RCC_BDCR_RTCSEL_0 /*!< LSE oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSI      RCC_BDCR_RTCSEL_1 /*!< LSI oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_HSE_DIV  RCC_BDCR_RTCSEL   /*!< HSE oscillator clock divided by RTCPRE used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC_PRESCALER  ADC Prescaler
  * @{
  */
#define LL_RCC_ADC_PRESCALER_1    0U                                                                  /*!< ADC kernel clock not divided    */
#define LL_RCC_ADC_PRESCALER_2    RCC_CCIPR1_ADCDIV_0                                                 /*!< ADC kernel clock divided by 2   */
#define LL_RCC_ADC_PRESCALER_4    RCC_CCIPR1_ADCDIV_1                                                 /*!< ADC kernel clock divided by 4   */
#define LL_RCC_ADC_PRESCALER_6    (RCC_CCIPR1_ADCDIV_1 | RCC_CCIPR1_ADCDIV_0)                         /*!< ADC kernel clock divided by 6   */
#define LL_RCC_ADC_PRESCALER_8    RCC_CCIPR1_ADCDIV_2                                                 /*!< ADC kernel clock divided by 8   */
#define LL_RCC_ADC_PRESCALER_10   (RCC_CCIPR1_ADCDIV_2 | RCC_CCIPR1_ADCDIV_0)                         /*!< ADC kernel clock divided by 10  */
#define LL_RCC_ADC_PRESCALER_12   (RCC_CCIPR1_ADCDIV_2 | RCC_CCIPR1_ADCDIV_1)                         /*!< ADC kernel clock divided by 12  */
#define LL_RCC_ADC_PRESCALER_16   (RCC_CCIPR1_ADCDIV_2 | RCC_CCIPR1_ADCDIV_1 | RCC_CCIPR1_ADCDIV_0)   /*!< ADC kernel clock divided by 16  */
#define LL_RCC_ADC_PRESCALER_32   RCC_CCIPR1_ADCDIV_3                                                 /*!< ADC kernel clock divided by 32  */
#define LL_RCC_ADC_PRESCALER_64   (RCC_CCIPR1_ADCDIV_3 | RCC_CCIPR1_ADCDIV_0)                         /*!< ADC kernel clock divided by 64  */
#define LL_RCC_ADC_PRESCALER_128  (RCC_CCIPR1_ADCDIV_3 | RCC_CCIPR1_ADCDIV_1)                         /*!< ADC kernel clock divided by 128 */
#define LL_RCC_ADC_PRESCALER_256  (RCC_CCIPR1_ADCDIV_3 | RCC_CCIPR1_ADCDIV_1 | RCC_CCIPR1_ADCDIV_0)   /*!< ADC kernel clock divided by 256 */
/**
  * @}
  */

/** @defgroup LL_RCC_EC_XSPISWP XSPI kernel clock switch position
  * @{
  */
#define LL_RCC_XSPI_CLKSOURCE_SWP_NEUTRAL    0U                                              /*!< Neutral switch used as XSPI clock source */
#define LL_RCC_XSPI_CLKSOURCE_SWP_HCLK5      RCC_CKPROTR_XSPISWP_0                           /*!< HCLK5 switch used as XSPI clock source   */
#define LL_RCC_XSPI_CLKSOURCE_SWP_PLL2S      RCC_CKPROTR_XSPISWP_1                           /*!< PLL2S switch used as XSPI clock source   */
#define LL_RCC_XSPI_CLKSOURCE_SWP_PLL2T      (RCC_CKPROTR_XSPISWP_1 | RCC_CKPROTR_XSPISWP_0) /*!< PLL2T switch used as XSPI clock source   */
#define LL_RCC_XSPI_CLKSOURCE_SWP_HCLK5_DIV4 RCC_CKPROTR_XSPISWP_2                           /*!< HCLK5 DIV4 switch used as XSPI clock source */
/**
  * @}
  */

/** @defgroup LL_RCC_EC_FMCSWP FMC kernel clock switch position
  * @{
  */
#define LL_RCC_FMC_CLKSOURCE_SWP_NEUTRAL    0U                                            /*!< Neutral switch used as FMC clock source */
#define LL_RCC_FMC_CLKSOURCE_SWP_HCLK5      RCC_CKPROTR_FMCSWP_0                          /*!< HCLK5 switch used as FMC clock source   */
#define LL_RCC_FMC_CLKSOURCE_SWP_PLL1Q      RCC_CKPROTR_FMCSWP_1                          /*!< PLL1Q switch used as FMC clock source   */
#define LL_RCC_FMC_CLKSOURCE_SWP_PLL2R      (RCC_CKPROTR_FMCSWP_1 | RCC_CKPROTR_FMCSWP_0) /*!< PLL2R switch used as FMC clock source   */
#define LL_RCC_FMC_CLKSOURCE_SWP_HSI        RCC_CKPROTR_FMCSWP_2                          /*!< HSI switch used as FMC clock source     */
#define LL_RCC_FMC_CLKSOURCE_SWP_HCLK5_DIV4 (RCC_CKPROTR_FMCSWP_2 | RCC_CKPROTR_FMCSWP_0) /*!< HCLK5 DIV4 switch used as FMC clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FMC_CLKSOURCE Peripheral FMC clock source selection
  * @{
  */
#define LL_RCC_FMC_CLKSOURCE_HCLK5  0U                    /*!< HCLK5 clock used as FMC clock source */
#define LL_RCC_FMC_CLKSOURCE_PLL1Q  RCC_CCIPR1_FMCSEL_0   /*!< PLL1Q clock used as FMC clock source */
#define LL_RCC_FMC_CLKSOURCE_PLL2R  RCC_CCIPR1_FMCSEL_1   /*!< PLL2R clock used as FMC clock source */
#define LL_RCC_FMC_CLKSOURCE_HSI    RCC_CCIPR1_FMCSEL     /*!< HSI clock used as FMC clock source   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SDMMC_CLKSOURCE Peripheral SDMMC clock source selection
  * @{
  */
#define LL_RCC_SDMMC1_CLKSOURCE_PLL2S   0U                    /*!< PLL2S clock used as SDMMC1 clock source */
#define LL_RCC_SDMMC1_CLKSOURCE_PLL2T   RCC_CCIPR1_SDMMC1SEL  /*!< PLL2T clock used as SDMMC1 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_XSPI_CLKSOURCE Peripheral XSPI clock source selection
  * @{
  */
#define LL_RCC_XSPI1_CLKSOURCE_HCLK5   0U                      /*!< HCLK5 clock used as XSPI1 clock source */
#define LL_RCC_XSPI1_CLKSOURCE_PLL2S   RCC_CCIPR1_XSPI1SEL_0   /*!< PLL2S clock used as XSPI1 clock source */
#define LL_RCC_XSPI1_CLKSOURCE_PLL2T   RCC_CCIPR1_XSPI1SEL_1   /*!< PLL2T clock used as XSPI1 clock source */
#define LL_RCC_XSPI1_CLKSOURCE_NONE    RCC_CCIPR1_XSPI1SEL     /*!< XSPI1 kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USBOTGFS_CLKSOURCE  Peripheral USBOTGFSx clock source selection
  * @{
  */
#define LL_RCC_USBOTGFS_CLKSOURCE_HSI48     0U                     /*!< HSI48 clock used as USBOTGFS clock source */
#define LL_RCC_USBOTGFS_CLKSOURCE_PLL3Q     RCC_CCIPR1_OTGFSSEL_0  /*!< PLL3Q clock used as USBOTGFS clock source */
#define LL_RCC_USBOTGFS_CLKSOURCE_HSE       RCC_CCIPR1_OTGFSSEL_1  /*!< HSE clock used as USBOTGFS clock source   */
#define LL_RCC_USBOTGFS_CLKSOURCE_NONE      RCC_CCIPR1_OTGFSSEL    /*!< USBOTGFS kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADF_CLKSOURCE Peripheral ADF clock source selection
  * @{
  */
#define LL_RCC_ADF1_CLKSOURCE_HCLK1     0U                                              /*!< HCLK1 clock used as ADF1 clock source    */
#define LL_RCC_ADF1_CLKSOURCE_PLL2P     RCC_CCIPR1_ADF1SEL_0                            /*!< PLL2P clock used as ADF1 clock source    */
#define LL_RCC_ADF1_CLKSOURCE_PLL3P     RCC_CCIPR1_ADF1SEL_1                            /*!< PLL3P clock used as ADF1 clock source    */
#define LL_RCC_ADF1_CLKSOURCE_AUDIOCLK  (RCC_CCIPR1_ADF1SEL_1 | RCC_CCIPR1_ADF1SEL_0)   /*!< AUDIOCLK clock used as ADF1 clock source */
#define LL_RCC_ADF1_CLKSOURCE_CSI       RCC_CCIPR1_ADF1SEL_2                            /*!< CSI clock used as ADF1 clock source      */
#define LL_RCC_ADF1_CLKSOURCE_HSI       (RCC_CCIPR1_ADF1SEL_2 | RCC_CCIPR1_ADF1SEL_0)   /*!< HSI clock used as ADF1 clock source      */
#define LL_RCC_ADF1_CLKSOURCE_NONE      RCC_CCIPR1_ADF1SEL                              /*!< ADF1 kernel clock is disabled            */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC_CLKSOURCE Peripheral ADC clock source selection
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE_HCLK3    0U                                            /*!< HCLK3 clock used as ADC clock source */
#define LL_RCC_ADC_CLKSOURCE_TIM      RCC_CCIPR1_ADCSEL_0                           /*!< TIM clock used as ADC clock source   */
#define LL_RCC_ADC_CLKSOURCE_HSI      RCC_CCIPR1_ADCSEL_1                           /*!< HSI clock used as ADC clock source   */
#define LL_RCC_ADC_CLKSOURCE_HSE      (RCC_CCIPR1_ADCSEL_1 | RCC_CCIPR1_ADCSEL_0)   /*!< HSE clock used as ADC clock source   */
#define LL_RCC_ADC_CLKSOURCE_PLL2P    RCC_CCIPR1_ADCSEL_2                           /*!< PLL2P clock used as ADC clock source */
#define LL_RCC_ADC_CLKSOURCE_PLL3R    (RCC_CCIPR1_ADCSEL_2 | RCC_CCIPR1_ADCSEL_0)   /*!< PLL3R clock used as ADC clock source */
#define LL_RCC_ADC_CLKSOURCE_PER      (RCC_CCIPR1_ADCSEL_2 | RCC_CCIPR1_ADCSEL_1)   /*!< PER clock used as ADC clock source   */
#define LL_RCC_ADC_CLKSOURCE_NONE   RCC_CCIPR1_ADCSEL                             /*!< ADC kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PER_CLKSOURCE Peripheral PER clock source selection
  * @{
  */
#define LL_RCC_PER_CLKSOURCE_HSI      0U                      /*!< HSI clock used as PER clock source */
#define LL_RCC_PER_CLKSOURCE_CSI      RCC_CCIPR1_CKPERSEL_0   /*!< CSI clock used as PER clock source */
#define LL_RCC_PER_CLKSOURCE_HSE      RCC_CCIPR1_CKPERSEL_1   /*!< HSE clock used as PER clock source */
#define LL_RCC_PER_CLKSOURCE_NONE   RCC_CCIPR1_CKPERSEL     /*!< PER kernel clock is disabled       */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_UART_CLKSOURCE Peripheral UART 4, 5, 6, 7, 8 and USART 2, 3 clock source selection
  * @{
  */
#define LL_RCC_UART234578_CLKSOURCE_PCLK1   0U                                                          /*!< PCLK1 clock used as UART234578 clock source */
#define LL_RCC_UART234578_CLKSOURCE_PLL2Q   RCC_CCIPR2_UART234578SEL_0                                  /*!< PLL2Q clock used as UART234578 clock source */
#define LL_RCC_UART234578_CLKSOURCE_PLL3Q   RCC_CCIPR2_UART234578SEL_1                                  /*!< PLL3Q clock used as UART234578 clock source */
#define LL_RCC_UART234578_CLKSOURCE_HSI     (RCC_CCIPR2_UART234578SEL_1 | RCC_CCIPR2_UART234578SEL_0)   /*!< HSI clock used as UART234578 clock source   */
#define LL_RCC_UART234578_CLKSOURCE_CSI     RCC_CCIPR2_UART234578SEL_2                                  /*!< CSI clock used as UART234578 clock source   */
#define LL_RCC_UART234578_CLKSOURCE_LSE     (RCC_CCIPR2_UART234578SEL_2 | RCC_CCIPR2_UART234578SEL_0)   /*!< LSE clock used as UART234578 clock source   */
#define LL_RCC_UART234578_CLKSOURCE_NONE  RCC_CCIPR2_UART234578SEL                                    /*!< UART234578 kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPIx_CLKSOURCE Peripheral SPIx clock source selection
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE_PLL1Q     LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, 0UL)                                          /*!< PLL1Q clock used as SPI1 clock source    */
#define LL_RCC_SPI1_CLKSOURCE_PLL2P     LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_0)                         /*!< PLL2P clock used as SPI1 clock source    */
#define LL_RCC_SPI1_CLKSOURCE_PLL3P     LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_1)                         /*!< PLL3P clock used as SPI1 clock source    */
#define LL_RCC_SPI1_CLKSOURCE_AUDIOCLK  LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_1 | RCC_CCIPR3_SPI1SEL_0)  /*!< AUDIOCLK clock used as SPI1 clock source */
#define LL_RCC_SPI1_CLKSOURCE_PER       LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL_2)                         /*!< PER clock used as SPI1 clock source      */
#define LL_RCC_SPI1_CLKSOURCE_NONE      LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, RCC_CCIPR3_SPI1SEL)                           /*!< SPI1 clock is disabled                   */

#define LL_RCC_SPI6_CLKSOURCE_PCLK4     LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL, 0UL)                                          /*!< PCLK4 clock used as SPI6 clock source */
#define LL_RCC_SPI6_CLKSOURCE_PLL2Q     LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_0)                         /*!< PLL2Q clock used as SPI6 clock source */
#define LL_RCC_SPI6_CLKSOURCE_PLL3Q     LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_1)                         /*!< PLL3Q clock used as SPI6 clock source */
#define LL_RCC_SPI6_CLKSOURCE_HSI       LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_1 | RCC_CCIPR4_SPI6SEL_0)  /*!< HSI clock used as SPI6 clock source   */
#define LL_RCC_SPI6_CLKSOURCE_CSI       LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_2)                         /*!< CSI clock used as SPI6 clock source   */
#define LL_RCC_SPI6_CLKSOURCE_HSE       LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL_2 | RCC_CCIPR4_SPI6SEL_0)  /*!< HSE clock used as SPI6 clock source   */
#define LL_RCC_SPI6_CLKSOURCE_NONE      LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL, RCC_CCIPR4_SPI6SEL)                           /*!< SPI6 clock is disabled                */

#define LL_RCC_SPI23_CLKSOURCE_PLL1Q    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL, 0UL)                                            /*!< PLL1Q clock used as SPI23 clock source    */
#define LL_RCC_SPI23_CLKSOURCE_PLL2P    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL_0)                          /*!< PLL2P clock used as SPI23 clock source    */
#define LL_RCC_SPI23_CLKSOURCE_PLL3P    LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL_1)                          /*!< PLL3P clock used as SPI23 clock source    */
#define LL_RCC_SPI23_CLKSOURCE_AUDIOCLK LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL_1 | RCC_CCIPR2_SPI23SEL_0)  /*!< AUDIOCLK clock used as SPI23 clock source */
#define LL_RCC_SPI23_CLKSOURCE_PER      LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL_2)                          /*!< PER clock used as SPI23 clock source      */
#define LL_RCC_SPI23_CLKSOURCE_NONE     LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL, RCC_CCIPR2_SPI23SEL)                            /*!< SPI23 clock is disabled                   */

#define LL_RCC_SPI45_CLKSOURCE_PCLK2    LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL, 0UL)                                            /*!< PCLK2 clock used as SPI45 clock source */
#define LL_RCC_SPI45_CLKSOURCE_PLL2Q    LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_0)                          /*!< PLL2Q clock used as SPI45 clock source */
#define LL_RCC_SPI45_CLKSOURCE_PLL3Q    LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_1)                          /*!< PLL3Q clock used as SPI45 clock source */
#define LL_RCC_SPI45_CLKSOURCE_HSI      LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_1 | RCC_CCIPR3_SPI45SEL_0)  /*!< HSI clock used as SPI45 clock source   */
#define LL_RCC_SPI45_CLKSOURCE_CSI      LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_2)                          /*!< CSI clock used as SPI45 clock source   */
#define LL_RCC_SPI45_CLKSOURCE_HSE      LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL_2 | RCC_CCIPR3_SPI45SEL_0)  /*!< HSE clock used as SPI45 clock source   */
#define LL_RCC_SPI45_CLKSOURCE_NONE     LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL, RCC_CCIPR3_SPI45SEL)                            /*!< SPI45 clock is disabled                */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2C_CLKSOURCE Peripheral I2C clock source selection
  * @{
  */
#define LL_RCC_I2C123_CLKSOURCE_PCLK1   0U                      /*!< PCLK1 clock used as I2C123 clock source */
#define LL_RCC_I2C123_CLKSOURCE_PLL3R   RCC_CCIPR2_I2C123SEL_0  /*!< PLL3R clock used as I2C123 clock source */
#define LL_RCC_I2C123_CLKSOURCE_HSI     RCC_CCIPR2_I2C123SEL_1  /*!< HSI clock used as I2C123 clock source   */
#define LL_RCC_I2C123_CLKSOURCE_CSI     RCC_CCIPR2_I2C123SEL    /*!< CSI clock used as I2C123 clock source   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I3C_CLKSOURCE Peripheral I3C clock source selection
  * @{
  */
#define LL_RCC_I3C1_CLKSOURCE_PCLK1   0U                    /*!< PCLK1 clock used as I3C1 clock source */
#define LL_RCC_I3C1_CLKSOURCE_PLL3R   RCC_CCIPR2_I3C1SEL_0  /*!< PLL3R clock used as I3C1 clock source */
#define LL_RCC_I3C1_CLKSOURCE_HSI     RCC_CCIPR2_I3C1SEL_1  /*!< HSI clock used as I3C1 clock source   */
#define LL_RCC_I3C1_CLKSOURCE_CSI     RCC_CCIPR2_I3C1SEL    /*!< CSI clock used as I3C1 clock source   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIMx_CLKSOURCE Peripheral LPTIMx clock source selection
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE_PCLK1     LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_LPTIM1SEL_Pos, RCC_CCIPR2_LPTIM1SEL, 0UL)                                             /*!< PCLK1 clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_PLL2P     LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_LPTIM1SEL_Pos, RCC_CCIPR2_LPTIM1SEL, RCC_CCIPR2_LPTIM1SEL_0)                          /*!< PLL2P clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_PLL3R     LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_LPTIM1SEL_Pos, RCC_CCIPR2_LPTIM1SEL, RCC_CCIPR2_LPTIM1SEL_1)                          /*!< PLL3R clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_LSE       LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_LPTIM1SEL_Pos, RCC_CCIPR2_LPTIM1SEL, RCC_CCIPR2_LPTIM1SEL_1 | RCC_CCIPR2_LPTIM1SEL_0) /*!< LSE clock used as LPTIM1 clock source   */
#define LL_RCC_LPTIM1_CLKSOURCE_LSI       LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_LPTIM1SEL_Pos, RCC_CCIPR2_LPTIM1SEL, RCC_CCIPR2_LPTIM1SEL_2)                          /*!< LSI clock used as LPTIM1 clock source   */
#define LL_RCC_LPTIM1_CLKSOURCE_PER       LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_LPTIM1SEL_Pos, RCC_CCIPR2_LPTIM1SEL, RCC_CCIPR2_LPTIM1SEL_2 | RCC_CCIPR2_LPTIM1SEL_0) /*!< PER clock used as LPTIM1 clock source   */
#define LL_RCC_LPTIM1_CLKSOURCE_NONE      LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_LPTIM1SEL_Pos, RCC_CCIPR2_LPTIM1SEL, RCC_CCIPR2_LPTIM1SEL)                            /*!< LPTIM1 clock is disabled                */

#define LL_RCC_LPTIM23_CLKSOURCE_PCLK4    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM23SEL_Pos, RCC_CCIPR4_LPTIM23SEL, 0UL)                                                /*!< PCLK4 clock used as LPTIM23 clock source */
#define LL_RCC_LPTIM23_CLKSOURCE_PLL2P    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM23SEL_Pos, RCC_CCIPR4_LPTIM23SEL, RCC_CCIPR4_LPTIM23SEL_0)                            /*!< PLL2P clock used as LPTIM23 clock source */
#define LL_RCC_LPTIM23_CLKSOURCE_PLL3R    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM23SEL_Pos, RCC_CCIPR4_LPTIM23SEL, RCC_CCIPR4_LPTIM23SEL_1)                            /*!< PLL3R clock used as LPTIM23 clock source */
#define LL_RCC_LPTIM23_CLKSOURCE_LSE      LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM23SEL_Pos, RCC_CCIPR4_LPTIM23SEL, RCC_CCIPR4_LPTIM23SEL_1 | RCC_CCIPR4_LPTIM23SEL_0)  /*!< LSE clock used as LPTIM23 clock source   */
#define LL_RCC_LPTIM23_CLKSOURCE_LSI      LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM23SEL_Pos, RCC_CCIPR4_LPTIM23SEL, RCC_CCIPR4_LPTIM23SEL_2)                            /*!< LSI clock used as LPTIM23 clock source   */
#define LL_RCC_LPTIM23_CLKSOURCE_PER      LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM23SEL_Pos, RCC_CCIPR4_LPTIM23SEL, RCC_CCIPR4_LPTIM23SEL_2 | RCC_CCIPR4_LPTIM23SEL_0)  /*!< PER clock used as LPTIM23 clock source   */
#define LL_RCC_LPTIM23_CLKSOURCE_NONE     LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM23SEL_Pos, RCC_CCIPR4_LPTIM23SEL, RCC_CCIPR4_LPTIM23SEL)                              /*!< LPTIM23 clock is disabled                */

#define LL_RCC_LPTIM45_CLKSOURCE_PCLK4    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL, 0UL)                                                /*!< PCLK4 clock used as LPTIM45 clock source */
#define LL_RCC_LPTIM45_CLKSOURCE_PLL2P    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_0)                            /*!< PLL2P clock used as LPTIM45 clock source */
#define LL_RCC_LPTIM45_CLKSOURCE_PLL3R    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_1)                            /*!< PLL3R clock used as LPTIM45 clock source */
#define LL_RCC_LPTIM45_CLKSOURCE_LSE      LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_1 | RCC_CCIPR4_LPTIM45SEL_0)  /*!< LSE clock used as LPTIM45 clock source   */
#define LL_RCC_LPTIM45_CLKSOURCE_LSI      LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_2)                            /*!< LSI clock used as LPTIM45 clock source   */
#define LL_RCC_LPTIM45_CLKSOURCE_PER      LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL_2 | RCC_CCIPR4_LPTIM45SEL_0)  /*!< PER clock used as LPTIM45 clock source   */
#define LL_RCC_LPTIM45_CLKSOURCE_NONE     LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL, RCC_CCIPR4_LPTIM45SEL)                              /*!< LPTIM45 clock is disabled                */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FDCAN_CLKSOURCE Peripheral FDCAN clock source selection
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE_HSE      0U                      /*!< HSE clock used as FDCAN clock source   */
#define LL_RCC_FDCAN_CLKSOURCE_PLL1Q    RCC_CCIPR2_FDCANSEL_0   /*!< PLL1Q clock used as FDCAN clock source */
#define LL_RCC_FDCAN_CLKSOURCE_PLL2P    RCC_CCIPR2_FDCANSEL_1   /*!< PLL2P clock used as FDCAN clock source */
#define LL_RCC_FDCAN_CLKSOURCE_NONE     RCC_CCIPR2_FDCANSEL     /*!< FDCAN kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USART16910_CLKSOURCE Peripheral UART9 and USART 1, 6, 10 clock source selection
  * @{
  */
#define LL_RCC_USART16910_CLKSOURCE_PCLK2   0U                                                         /*!< PCLK2 clock used as USART16910 clock source */
#define LL_RCC_USART16910_CLKSOURCE_PLL2Q   RCC_CCIPR3_USART16910SEL_0                                 /*!< PLL2Q clock used as USART16910 clock source */
#define LL_RCC_USART16910_CLKSOURCE_PLL3Q   RCC_CCIPR3_USART16910SEL_1                                 /*!< PLL3Q clock used as USART16910 clock source */
#define LL_RCC_USART16910_CLKSOURCE_HSI     (RCC_CCIPR3_USART16910SEL_1 | RCC_CCIPR3_USART16910SEL_0)  /*!< HSI clock used as USART16910 clock source   */
#define LL_RCC_USART16910_CLKSOURCE_CSI     RCC_CCIPR3_USART16910SEL_2                                 /*!< CSI clock used as USART16910 clock source   */
#define LL_RCC_USART16910_CLKSOURCE_LSE     (RCC_CCIPR3_USART16910SEL_2 | RCC_CCIPR3_USART16910SEL_0)  /*!< LSE clock used as USART16910 clock source   */
#define LL_RCC_USART16910_CLKSOURCE_NONE    RCC_CCIPR3_USART16910SEL                                   /*!< USART16910 kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART_CLKSOURCE Peripheral LPUART clock source selection
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE_PCLK4    0U                                                   /*!< PCLK4 clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_PLL2Q    RCC_CCIPR4_LPUART1SEL_0                              /*!< PLL2Q clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_PLL3Q    RCC_CCIPR4_LPUART1SEL_1                              /*!< PLL3Q clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_HSI      (RCC_CCIPR4_LPUART1SEL_1 | RCC_CCIPR4_LPUART1SEL_0)  /*!< HSI clock used as LPUART1 clock source   */
#define LL_RCC_LPUART1_CLKSOURCE_CSI      RCC_CCIPR4_LPUART1SEL_2                              /*!< CSI clock used as LPUART1 clock source   */
#define LL_RCC_LPUART1_CLKSOURCE_LSE      (RCC_CCIPR4_LPUART1SEL_2 | RCC_CCIPR4_LPUART1SEL_0)  /*!< LSE clock used as LPUART1 clock source   */
#define LL_RCC_LPUART1_CLKSOURCE_NONE     RCC_CCIPR4_LPUART1SEL                                /*!< LPUART1 kernel clock is disabled         */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DACx_CLKSOURCE Peripheral DACx clock source selection
  * @{
  */
#define LL_RCC_DAC1_CLKSOURCE_HCLK3  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC1SEL_Pos, RCC_CCIPR4_DAC1SEL, 0UL)                                         /*!< HCLK3 clock used as DAC1 clock source */
#define LL_RCC_DAC1_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC1SEL_Pos, RCC_CCIPR4_DAC1SEL, RCC_CCIPR4_DAC1SEL_0)                        /*!< TIM clock used as DAC1 clock source   */
#define LL_RCC_DAC1_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC1SEL_Pos, RCC_CCIPR4_DAC1SEL, RCC_CCIPR4_DAC1SEL_1)                        /*!< ADC clock used as DAC1 clock source   */
#define LL_RCC_DAC1_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC1SEL_Pos, RCC_CCIPR4_DAC1SEL, RCC_CCIPR4_DAC1SEL_1 | RCC_CCIPR4_DAC1SEL_0) /*!< HSI clock used as DAC1 clock source   */
#define LL_RCC_DAC1_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC1SEL_Pos, RCC_CCIPR4_DAC1SEL, RCC_CCIPR4_DAC1SEL_2)                        /*!< HSE clock used as DAC1 clock source   */
#define LL_RCC_DAC1_CLKSOURCE_PLL2P  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC1SEL_Pos, RCC_CCIPR4_DAC1SEL, RCC_CCIPR4_DAC1SEL_2 | RCC_CCIPR4_DAC1SEL_0) /*!< PLL2P clock used as DAC1 clock source */
#define LL_RCC_DAC1_CLKSOURCE_PLL3R  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC1SEL_Pos, RCC_CCIPR4_DAC1SEL, RCC_CCIPR4_DAC1SEL_2 | RCC_CCIPR4_DAC1SEL_1) /*!< PLL3R clock used as DAC1 clock source */
#define LL_RCC_DAC1_CLKSOURCE_PER    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC1SEL_Pos, RCC_CCIPR4_DAC1SEL, RCC_CCIPR4_DAC1SEL)                          /*!< PER clock used as DAC1 clock source   */

#define LL_RCC_DAC2_CLKSOURCE_HCLK3  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC2SEL_Pos, RCC_CCIPR4_DAC2SEL, 0UL)                                         /*!< HCLK3 clock used as DAC2 clock source */
#define LL_RCC_DAC2_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC2SEL_Pos, RCC_CCIPR4_DAC2SEL, RCC_CCIPR4_DAC2SEL_0)                        /*!< TIM clock used as DAC2 clock source   */
#define LL_RCC_DAC2_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC2SEL_Pos, RCC_CCIPR4_DAC2SEL, RCC_CCIPR4_DAC2SEL_1)                        /*!< ADC clock used as DAC2 clock source   */
#define LL_RCC_DAC2_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC2SEL_Pos, RCC_CCIPR4_DAC2SEL, RCC_CCIPR4_DAC2SEL_1 | RCC_CCIPR4_DAC2SEL_0) /*!< HSI clock used as DAC2 clock source   */
#define LL_RCC_DAC2_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC2SEL_Pos, RCC_CCIPR4_DAC2SEL, RCC_CCIPR4_DAC2SEL_2)                        /*!< HSE clock used as DAC2 clock source   */
#define LL_RCC_DAC2_CLKSOURCE_PLL2P  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC2SEL_Pos, RCC_CCIPR4_DAC2SEL, RCC_CCIPR4_DAC2SEL_2 | RCC_CCIPR4_DAC2SEL_0) /*!< PLL2P clock used as DAC2 clock source */
#define LL_RCC_DAC2_CLKSOURCE_PLL3R  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC2SEL_Pos, RCC_CCIPR4_DAC2SEL, RCC_CCIPR4_DAC2SEL_2 | RCC_CCIPR4_DAC2SEL_1) /*!< PLL3R clock used as DAC2 clock source */
#define LL_RCC_DAC2_CLKSOURCE_PER    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC2SEL_Pos, RCC_CCIPR4_DAC2SEL, RCC_CCIPR4_DAC2SEL)                          /*!< PER clock used as DAC2 clock source   */

#define LL_RCC_DAC3_CLKSOURCE_HCLK3  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC3SEL_Pos, RCC_CCIPR4_DAC3SEL, 0UL)                                         /*!< HCLK3 clock used as DAC3 clock source */
#define LL_RCC_DAC3_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC3SEL_Pos, RCC_CCIPR4_DAC3SEL, RCC_CCIPR4_DAC3SEL_0)                        /*!< TIM clock used as DAC3 clock source   */
#define LL_RCC_DAC3_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC3SEL_Pos, RCC_CCIPR4_DAC3SEL, RCC_CCIPR4_DAC3SEL_1)                        /*!< ADC clock used as DAC3 clock source   */
#define LL_RCC_DAC3_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC3SEL_Pos, RCC_CCIPR4_DAC3SEL, RCC_CCIPR4_DAC3SEL_1 | RCC_CCIPR4_DAC3SEL_0) /*!< HSI clock used as DAC3 clock source   */
#define LL_RCC_DAC3_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC3SEL_Pos, RCC_CCIPR4_DAC3SEL, RCC_CCIPR4_DAC3SEL_2)                        /*!< HSE clock used as DAC3 clock source   */
#define LL_RCC_DAC3_CLKSOURCE_PLL2P  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC3SEL_Pos, RCC_CCIPR4_DAC3SEL, RCC_CCIPR4_DAC3SEL_2 | RCC_CCIPR4_DAC3SEL_0) /*!< PLL2P clock used as DAC3 clock source */
#define LL_RCC_DAC3_CLKSOURCE_PLL3R  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC3SEL_Pos, RCC_CCIPR4_DAC3SEL, RCC_CCIPR4_DAC3SEL_2 | RCC_CCIPR4_DAC3SEL_1) /*!< PLL3R clock used as DAC3 clock source */
#define LL_RCC_DAC3_CLKSOURCE_PER    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC3SEL_Pos, RCC_CCIPR4_DAC3SEL, RCC_CCIPR4_DAC3SEL)                          /*!< PER clock used as DAC3 clock source   */

#define LL_RCC_DAC4_CLKSOURCE_HCLK3  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC4SEL_Pos, RCC_CCIPR4_DAC4SEL, 0UL)                                         /*!< HCLK3 clock used as DAC4 clock source */
#define LL_RCC_DAC4_CLKSOURCE_TIM    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC4SEL_Pos, RCC_CCIPR4_DAC4SEL, RCC_CCIPR4_DAC4SEL_0)                        /*!< TIM clock used as DAC4 clock source   */
#define LL_RCC_DAC4_CLKSOURCE_ADC    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC4SEL_Pos, RCC_CCIPR4_DAC4SEL, RCC_CCIPR4_DAC4SEL_1)                        /*!< ADC clock used as DAC4 clock source   */
#define LL_RCC_DAC4_CLKSOURCE_HSI    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC4SEL_Pos, RCC_CCIPR4_DAC4SEL, RCC_CCIPR4_DAC4SEL_1 | RCC_CCIPR4_DAC4SEL_0) /*!< HSI clock used as DAC4 clock source   */
#define LL_RCC_DAC4_CLKSOURCE_HSE    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC4SEL_Pos, RCC_CCIPR4_DAC4SEL, RCC_CCIPR4_DAC4SEL_2)                        /*!< HSE clock used as DAC4 clock source   */
#define LL_RCC_DAC4_CLKSOURCE_PLL2P  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC4SEL_Pos, RCC_CCIPR4_DAC4SEL, RCC_CCIPR4_DAC4SEL_2 | RCC_CCIPR4_DAC4SEL_0) /*!< PLL2P clock used as DAC4 clock source */
#define LL_RCC_DAC4_CLKSOURCE_PLL3R  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC4SEL_Pos, RCC_CCIPR4_DAC4SEL, RCC_CCIPR4_DAC4SEL_2 | RCC_CCIPR4_DAC4SEL_1) /*!< PLL3R clock used as DAC4 clock source */
#define LL_RCC_DAC4_CLKSOURCE_PER    LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC4SEL_Pos, RCC_CCIPR4_DAC4SEL, RCC_CCIPR4_DAC4SEL)                          /*!< PER clock used as DAC4 clock source   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DACSH_CLKSOURCE Peripheral DACSH clock source selection
  * @{
  */
#define LL_RCC_DAC1SH_CLKSOURCE_LSE 0U                   /*!< LSE clock used as DAC1SH clock source */
#define LL_RCC_DAC1SH_CLKSOURCE_LSI RCC_CCIPR4_DAC1SHSEL /*!< LSI clock used as DAC1SH clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FMC Peripheral FMC get clock source
  * @{
  */
#define LL_RCC_FMC_CLKSOURCE RCC_CCIPR1_FMCSEL /*!< FMC Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SDMMC Peripheral SDMMC get clock source
  * @{
  */
#define LL_RCC_SDMMC1_CLKSOURCE RCC_CCIPR1_SDMMC1SEL /*!< SDMMC1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_XSPI Peripheral XSPI get clock source
  * @{
  */
#define LL_RCC_XSPI1_CLKSOURCE RCC_CCIPR1_XSPI1SEL /*!< XSPI1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USB  Peripheral USBOTGFS get clock source
  * @{
  */
#define LL_RCC_USBOTGFS_CLKSOURCE   RCC_CCIPR1_OTGFSSEL /*!< USB OTG FS Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADF Peripheral ADF get clock source
  * @{
  */
#define LL_RCC_ADF1_CLKSOURCE       RCC_CCIPR1_ADF1SEL /*!< ADF1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADC Peripheral ADC get clock source
  * @{
  */
#define LL_RCC_ADC_CLKSOURCE        RCC_CCIPR1_ADCSEL /*!< ADC Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PER Peripheral CKPER get clock source
  * @{
  */
#define LL_RCC_PER_CLKSOURCE      RCC_CCIPR1_CKPERSEL /*!< PER Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_UART Peripheral UART get clock source
  * @{
  */
#define LL_RCC_UART234578_CLKSOURCE RCC_CCIPR2_UART234578SEL /*!< UART234578 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPIx Peripheral SPIx get clock source
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE  LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI1SEL_Pos, RCC_CCIPR3_SPI1SEL, 0UL)   /*!< SPI1 Clock source selection  */
#define LL_RCC_SPI6_CLKSOURCE  LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_SPI6SEL_Pos, RCC_CCIPR4_SPI6SEL, 0UL)   /*!< SPI6 Clock source selection  */
#define LL_RCC_SPI23_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_SPI23SEL_Pos, RCC_CCIPR2_SPI23SEL, 0UL) /*!< SPI23 Clock source selection */
#define LL_RCC_SPI45_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR3, (uint32_t)RCC_CCIPR3_SPI45SEL_Pos, RCC_CCIPR3_SPI45SEL, 0UL) /*!< SPI45 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2C Peripheral I2C get clock source
  * @{
  */
#define LL_RCC_I2C123_CLKSOURCE RCC_CCIPR2_I2C123SEL /*!< I2C123 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I3C Peripheral I3C get clock source
  * @{
  */
#define LL_RCC_I3C1_CLKSOURCE RCC_CCIPR2_I3C1SEL /*!< I3C1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIMx Peripheral LPTIMx get clock source
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE  LL_CLKSOURCE(RCC_OFFSET_CCIPR2, (uint32_t)RCC_CCIPR2_LPTIM1SEL_Pos, RCC_CCIPR2_LPTIM1SEL, 0UL)   /*!< LPTIM1 Clock source selection  */
#define LL_RCC_LPTIM23_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM23SEL_Pos, RCC_CCIPR4_LPTIM23SEL, 0UL) /*!< LPTIM23 Clock source selection */
#define LL_RCC_LPTIM45_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_LPTIM45SEL_Pos, RCC_CCIPR4_LPTIM45SEL, 0UL) /*!< LPTIM45 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FDCAN Peripheral FDCAN get clock source
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE RCC_CCIPR2_FDCANSEL /*!< FDCAN Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USART Peripheral USART get clock source
  * @{
  */
#define LL_RCC_USART16910_CLKSOURCE RCC_CCIPR3_USART16910SEL /*!< USART16910 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART Peripheral LPUART get clock source
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE RCC_CCIPR4_LPUART1SEL /*!< LPUART1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DACx Peripheral DACx get clock source
  * @{
  */
#define LL_RCC_DAC1_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC1SEL_Pos, RCC_CCIPR4_DAC1SEL, 0UL) /*!< DAC1 Clock source selection */
#define LL_RCC_DAC2_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC2SEL_Pos, RCC_CCIPR4_DAC2SEL, 0UL) /*!< DAC2 Clock source selection */
#define LL_RCC_DAC3_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC3SEL_Pos, RCC_CCIPR4_DAC3SEL, 0UL) /*!< DAC3 Clock source selection */
#define LL_RCC_DAC4_CLKSOURCE LL_CLKSOURCE(RCC_OFFSET_CCIPR4, (uint32_t)RCC_CCIPR4_DAC4SEL_Pos, RCC_CCIPR4_DAC4SEL, 0UL) /*!< DAC4 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DACSH Peripheral DACSH get clock source
  * @{
  */
#define LL_RCC_DAC1SH_CLKSOURCE RCC_CCIPR4_DAC1SHSEL /*!< DAC1SH Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLSOURCE PLLs entry clock source
  * @{
  */
#define LL_RCC_PLLSOURCE_HSI    0U                     /*!< HSI clock selected as PLLs entry clock source */
#define LL_RCC_PLLSOURCE_CSI    RCC_PLLCKSELR_PLLSRC_0 /*!< CSI clock selected as PLLs entry clock source */
#define LL_RCC_PLLSOURCE_HSE    RCC_PLLCKSELR_PLLSRC_1 /*!< HSE clock selected as PLLs entry clock source */
#define LL_RCC_PLLSOURCE_NO_CLK RCC_PLLCKSELR_PLLSRC   /*!< No clock selected as PLLs entry clock source  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL_SPREAD_SEL All PLLs Spread spectrum clock generator mode
  * @{
  */
#define LL_RCC_PLL_SPREAD_CENTER 0U
#define LL_RCC_PLL_SPREAD_DOWN   RCC_PLL1SSCGR_SPREADSEL
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL_SSCG_DITH  PLL Spread Spectrum Dithering Control
  * @{
  */
#define LL_RCC_PLL_SSCG_DITH_NO              (RCC_PLL1SSCGR_RPDFNDIS | RCC_PLL1SSCGR_TPDFNDIS)  /*!< RPDF and TPDF dithering both disabled */
#define LL_RCC_PLL_SSCG_DITH_RPDF            RCC_PLL1SSCGR_TPDFNDIS                             /*!< Only RPDF dithering enabled (TPDF dithering disabled) */
#define LL_RCC_PLL_SSCG_DITH_TPDF            RCC_PLL1SSCGR_RPDFNDIS                             /*!< Only TPDF dithering enabled (RPDF dithering disabled) */
#define LL_RCC_PLL_SSCG_DITH_RPDF_TPDF       0x00000000U                                        /*!< RPDF and TPDF dithering both enabled  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL1_OUTPUT PLL1 Clock Output
  * @{
  */
#define LL_RCC_PLL1_OUTPUT_P RCC_PLLCFGR_PLL1PEN /*!< PLL1P divider output enable  */
#define LL_RCC_PLL1_OUTPUT_Q RCC_PLLCFGR_PLL1QEN /*!< PLL1Q divider output enable  */
#define LL_RCC_PLL1_OUTPUT_S RCC_PLLCFGR_PLL1SEN /*!< PLL1S divider output enable  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL1VCORANGE All PLL1 output ranges
  * @{
  */
#define LL_RCC_PLL1VCORANGE_384_1672 0U                     /*!< PLL1 VCO output range: 384 to 1672 MHz */
#define LL_RCC_PLL1VCORANGE_150_420  RCC_PLLCFGR_PLL1VCOSEL /*!< PLL1 VCO output range: 150 to 420 MHz  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL1INPUTRANGE All PLL1 input ranges
  * @{
  */
#define LL_RCC_PLL1INPUTRANGE_1_2  0U                    /*!< PLL1 input clock range frequency between 1 and 2 MHz (default after reset) */
#define LL_RCC_PLL1INPUTRANGE_2_4  RCC_PLLCFGR_PLL1RGE_0 /*!< PLL1 input clock range frequency between 2 and 4 MHz  */
#define LL_RCC_PLL1INPUTRANGE_4_8  RCC_PLLCFGR_PLL1RGE_1 /*!< PLL1 input clock range frequency between 4 and 8 MHz  */
#define LL_RCC_PLL1INPUTRANGE_8_16 RCC_PLLCFGR_PLL1RGE   /*!< PLL1 input clock range frequency between 8 and 16 MHz */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL2_OUTPUT PLL2 Clock Output
  * @{
  */
#define LL_RCC_PLL2_OUTPUT_P RCC_PLLCFGR_PLL2PEN /*!< PLL2P divider output enable  */
#define LL_RCC_PLL2_OUTPUT_Q RCC_PLLCFGR_PLL2QEN /*!< PLL2Q divider output enable  */
#define LL_RCC_PLL2_OUTPUT_R RCC_PLLCFGR_PLL2REN /*!< PLL2R divider output enable  */
#define LL_RCC_PLL2_OUTPUT_S RCC_PLLCFGR_PLL2SEN /*!< PLL2S divider output enable  */
#define LL_RCC_PLL2_OUTPUT_T RCC_PLLCFGR_PLL2TEN /*!< PLL2T divider output enable  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL2VCORANGE All PLL2 output ranges
  * @{
  */
#define LL_RCC_PLL2VCORANGE_384_1672 0U                     /*!< PLL2 VCO output range: 384 to 1672 MHz */
#define LL_RCC_PLL2VCORANGE_150_420  RCC_PLLCFGR_PLL2VCOSEL /*!< PLL2 VCO output range: 150 to 420 MHz  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL2INPUTRANGE All PLL2 input ranges
  * @{
  */
#define LL_RCC_PLL2INPUTRANGE_1_2  0U                    /*!< PLL2 input clock range frequency between 1 and 2 MHz (default after reset) */
#define LL_RCC_PLL2INPUTRANGE_2_4  RCC_PLLCFGR_PLL2RGE_0 /*!< PLL2 input clock range frequency between 2 and 4 MHz  */
#define LL_RCC_PLL2INPUTRANGE_4_8  RCC_PLLCFGR_PLL2RGE_1 /*!< PLL2 input clock range frequency between 4 and 8 MHz  */
#define LL_RCC_PLL2INPUTRANGE_8_16 RCC_PLLCFGR_PLL2RGE   /*!< PLL2 input clock range frequency between 8 and 16 MHz */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL3_OUTPUT PLL3 Clock Output
  * @{
  */
#define LL_RCC_PLL3_OUTPUT_P RCC_PLLCFGR_PLL3PEN /*!< PLL3P divider output enable  */
#define LL_RCC_PLL3_OUTPUT_Q RCC_PLLCFGR_PLL3QEN /*!< PLL3Q divider output enable  */
#define LL_RCC_PLL3_OUTPUT_R RCC_PLLCFGR_PLL3REN /*!< PLL3R divider output enable  */
#define LL_RCC_PLL3_OUTPUT_S RCC_PLLCFGR_PLL3SEN /*!< PLL3S divider output enable  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL3VCORANGE All PLL3 output ranges
  * @{
  */
#define LL_RCC_PLL3VCORANGE_384_1672 0U                     /*!< PLL3 VCO output range: 384 to 1672 MHz */
#define LL_RCC_PLL3VCORANGE_150_420  RCC_PLLCFGR_PLL3VCOSEL /*!< PLL3 VCO output range: 150 to 420 MHz  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL3INPUTRANGE All PLL3 input ranges
  * @{
  */
#define LL_RCC_PLL3INPUTRANGE_1_2  0U                    /*!< PLL3 input clock range frequency between 1 and 2 MHz (default after reset) */
#define LL_RCC_PLL3INPUTRANGE_2_4  RCC_PLLCFGR_PLL3RGE_0 /*!< PLL3 input clock range frequency between 2 and 4 MHz  */
#define LL_RCC_PLL3INPUTRANGE_4_8  RCC_PLLCFGR_PLL3RGE_1 /*!< PLL3 input clock range frequency between 4 and 8 MHz  */
#define LL_RCC_PLL3INPUTRANGE_8_16 RCC_PLLCFGR_PLL3RGE   /*!< PLL3 input clock range frequency between 8 and 16 MHz */
/**
  * @}
  */

/** @defgroup RCC_LL_FLAGS RCC Flags
  * @{
  */
#define LL_RCC_IT_LSIRDY   RCC_CIFR_LSIRDYF   /*!< LSI ready interrupt flag   */
#define LL_RCC_IT_LSERDY   RCC_CIFR_LSERDYF   /*!< LSE ready interrupt flag   */
#define LL_RCC_IT_HSIRDY   RCC_CIFR_HSIRDYF   /*!< HSI ready interrupt flag   */
#define LL_RCC_IT_HSERDY   RCC_CIFR_HSERDYF   /*!< HSE ready interrupt flag   */
#define LL_RCC_IT_CSIRDY   RCC_CIFR_CSIRDYF   /*!< CSI ready interrupt flag   */
#define LL_RCC_IT_HSI48RDY RCC_CIFR_HSI48RDYF /*!< HSI48 ready interrupt flag */
#define LL_RCC_IT_PLL1RDY  RCC_CIFR_PLL1RDYF  /*!< PLL1 ready interrupt flag  */
#define LL_RCC_IT_PLL2RDY  RCC_CIFR_PLL2RDYF  /*!< PLL2 ready interrupt flag  */
#define LL_RCC_IT_PLL3RDY  RCC_CIFR_PLL3RDYF  /*!< PLL3 ready interrupt flag  */
#define LL_RCC_IT_LSECSS   RCC_CIFR_LSECSSF   /*!< LSE clock security system interrupt flag */
#define LL_RCC_IT_HSECSS   RCC_CIFR_HSECSSF   /*!< HSE clock security system interrupt flag */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup RCC_LL_Exported_Macros RCC Exported Macros
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
  * @brief  Helper macro to calculate the PLL1P frequency.
  * @param  input_freq PLL1 Input frequency (based on HSI/CSI/HSE)
  * @param  pll1m parameter can be a value between 1 and 64
  * @param  pll1n parameter can be a value between 8 and 420
  * @param  pll1p parameter can be a value between 1 and 128
  * @note   ex: @ref LL_RCC_CALC_PLL1CLK_P_FREQ (HSE_VALUE, @ref LL_RCC_PLL1_GetDivider(),
  *             @ref LL_RCC_PLL1_GetN(), @ref LL_RCC_PLL1_GetP()).
  * @retval PLL1P clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL1CLK_P_FREQ(input_freq, pll1m, pll1n, pll1p) ((((input_freq) /(pll1m)) * (pll1n)) / (pll1p))

/**
  * @brief  Helper macro to calculate the PLL1Q frequency.
  * @param  input_freq PLL1 Input frequency (based on HSI/CSI/HSE)
  * @param  pll1m parameter can be a value between 1 and 64
  * @param  pll1n parameter can be a value between 8 and 420
  * @param  pll1q parameter can be a value between 1 and 128
  * @note   ex: @ref LL_RCC_CALC_PLL1CLK_Q_FREQ (HSE_VALUE, @ref LL_RCC_PLL1_GetDivider (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetQ ()).
  * @retval PLL1Q clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL1CLK_Q_FREQ(input_freq, pll1m, pll1n, pll1q) ((((input_freq) /(pll1m)) * (pll1n)) / (pll1q))

/**
  * @brief  Helper macro to calculate the PLL1S frequency.
  * @param  input_freq PLL1 Input frequency (based on HSI/CSI/HSE)
  * @param  pll1m parameter can be a value between 1 and 64
  * @param  pll1n parameter can be a value between 8 and 420
  * @param  pll1s parameter can be a value between 1 and 8
  * @note   ex: @ref LL_RCC_CALC_PLL1CLK_S_FREQ (HSE_VALUE, @ref LL_RCC_PLL1_GetDivider (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetS ()).
  * @retval PLL1S clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL1CLK_S_FREQ(input_freq, pll1m, pll1n, pll1s) ((((input_freq) /(pll1m)) * (pll1n)) / (pll1s))

/**
  * @brief  Helper macro to calculate the PLL2P frequency.
  * @param  input_freq PLL2 Input frequency (based on HSI/CSI/HSE)
  * @param  pll2m parameter can be a value between 1 and 64
  * @param  pll2n parameter can be a value between 8 and 420
  * @param  pll2p parameter can be a value between 1 and 8
  * @note   ex: @ref LL_RCC_CALC_PLL2CLK_P_FREQ (HSE_VALUE, @ref LL_RCC_PLL2_GetDivider (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetP ()).
  * @retval PLL2P clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_P_FREQ(input_freq, pll2m, pll2n, pll2p) ((((input_freq) /(pll2m)) * (pll2n)) / (pll2p))

/**
  * @brief  Helper macro to calculate the PLL2Q frequency.
  * @param  input_freq PLL2 Input frequency (based on HSI/CSI/HSE)
  * @param  pll2m parameter can be a value between 1 and 64
  * @param  pll2n parameter can be a value between 8 and 420
  * @param  pll2q parameter can be a value between 1 and 128
  * @note   ex: @ref LL_RCC_CALC_PLL2CLK_Q_FREQ (HSE_VALUE, @ref LL_RCC_PLL2_GetDivider (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetQ ()).
  * @retval PLL2Q clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_Q_FREQ(input_freq, pll2m, pll2n, pll2q) ((((input_freq) /(pll2m)) * (pll2n)) / (pll2q))

/**
  * @brief  Helper macro to calculate the PLL2R frequency.
  * @param  input_freq PLL2 Input frequency (based on HSI/CSI/HSE)
  * @param  pll2m parameter can be a value between 1 and 64
  * @param  pll2n parameter can be a value between 8 and 420
  * @param  pll2r parameter can be a value between 1 and 128
  * @note   ex: @ref LL_RCC_CALC_PLL2CLK_R_FREQ (HSE_VALUE, @ref LL_RCC_PLL2_GetDivider (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetR ()).
  * @retval PLL2R clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_R_FREQ(input_freq, pll2m, pll2n, pll2r) ((((input_freq) /(pll2m)) * (pll2n)) / (pll2r))

/**
  * @brief  Helper macro to calculate the PLL2S frequency.
  * @param  input_freq PLL2 Input frequency (based on HSI/CSI/HSE)
  * @param  pll2m parameter can be a value between 1 and 64
  * @param  pll2n parameter can be a value between 8 and 420
  * @param  pll2s parameter can be a value between 1 and 8
  * @note   ex: @ref LL_RCC_CALC_PLL2CLK_S_FREQ (HSE_VALUE, @ref LL_RCC_PLL2_GetDivider (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetS ()).
  * @retval PLL2S clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_S_FREQ(input_freq, pll2m, pll2n, pll2s) ((((input_freq) /(pll2m)) * (pll2n)) / (pll2s))

/**
  * @brief  Helper macro to calculate the PLL2T frequency.
  * @param  input_freq PLL2 Input frequency (based on HSI/CSI/HSE)
  * @param  pll2m parameter can be a value between 1 and 64
  * @param  pll2n parameter can be a value between 8 and 420
  * @param  pll2t parameter can be a value between 1 and 8
  * @note   ex: @ref LL_RCC_CALC_PLL2CLK_T_FREQ (HSE_VALUE, @ref LL_RCC_PLL2_GetDivider (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetT ()).
  * @retval PLL2T clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_T_FREQ(input_freq, pll2m, pll2n, pll2t) ((((input_freq) /(pll2m)) * (pll2n)) / (pll2t))

/**
  * @brief  Helper macro to calculate the PLL3P frequency.
  * @param  input_freq PLL3 Input frequency (based on HSI/CSI/HSE)
  * @param  pll3m parameter can be a value between 1 and 64
  * @param  pll3n parameter can be a value between 8 and 420
  * @param  pll3p parameter can be a value between 1 and 128
  * @note   ex: @ref LL_RCC_CALC_PLL3CLK_P_FREQ (HSE_VALUE, @ref LL_RCC_PLL3_GetDivider (),
  *             @ref LL_RCC_PLL3_GetN (), @ref LL_RCC_PLL3_GetP ()).
  * @retval PLL3P clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL3CLK_P_FREQ(input_freq, pll3m, pll3n, pll3p) ((((input_freq) /(pll3m)) * (pll3n)) / (pll3p))

/**
  * @brief  Helper macro to calculate the PLL3Q frequency.
  * @param  input_freq PLL3 Input frequency (based on HSI/CSI/HSE)
  * @param  pll3m parameter can be a value between 1 and 64
  * @param  pll3n parameter can be a value between 8 and 420
  * @param  pll3q parameter can be a value between 1 and 128
  * @note   ex: @ref LL_RCC_CALC_PLL3CLK_Q_FREQ (HSE_VALUE, @ref LL_RCC_PLL3_GetDivider (),
  *             @ref LL_RCC_PLL3_GetN (), @ref LL_RCC_PLL3_GetQ ()).
  * @retval PLL3Q clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL3CLK_Q_FREQ(input_freq, pll3m, pll3n, pll3q) ((((input_freq) /(pll3m)) * (pll3n)) / (pll3q))

/**
  * @brief  Helper macro to calculate the PLL3R frequency.
  * @param  input_freq PLL3 Input frequency (based on HSI/CSI/HSE)
  * @param  pll3m parameter can be a value between 1 and 64
  * @param  pll3n parameter can be a value between 8 and 420
  * @param  pll3r parameter can be a value between 1 and 128
  * @note   ex: @ref LL_RCC_CALC_PLL3CLK_R_FREQ (HSE_VALUE, @ref LL_RCC_PLL3_GetDivider (),
  *             @ref LL_RCC_PLL3_GetN (), @ref LL_RCC_PLL3_GetR ()).
  * @retval PLL3R clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL3CLK_R_FREQ(input_freq, pll3m, pll3n, pll3r) ((((input_freq) /(pll3m)) * (pll3n)) / (pll3r))

/**
  * @brief  Helper macro to calculate the PLL3S frequency.
  * @param  input_freq PLL3 Input frequency (based on HSI/CSI/HSE)
  * @param  pll3m parameter can be a value between 1 and 64
  * @param  pll3n parameter can be a value between 8 and 420
  * @param  pll3s parameter can be a value between 1 and 8
  * @note   ex: @ref LL_RCC_CALC_PLL3CLK_S_FREQ (HSE_VALUE, @ref LL_RCC_PLL3_GetDivider (),
  *             @ref LL_RCC_PLL3_GetN (), @ref LL_RCC_PLL3_GetS ()).
  * @retval PLL3S clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL3CLK_S_FREQ(input_freq, pll3m, pll3n, pll3s) ((((input_freq) /(pll3m)) * (pll3n)) / (pll3s))

/**
  * @brief  Helper macro to calculate the BMCLK frequency (AXI Bus, AHBx bus).
  * @param  sysclk_freq  SYSCLK frequency  (based on HSI/CSI/HSE/PLL1P)
  * @param  bm_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_BMCLK_PRESCALER_1
  *         @arg @ref LL_RCC_BMCLK_PRESCALER_2
  * @retval BMCLK clock frequency (in Hz)
  */
#define LL_RCC_CALC_BMCLK_FREQ(sysclk_freq, bm_prescaler) \
  ((sysclk_freq) >> (uint32_t)(((bm_prescaler) & RCC_BMCFGR_BMPRE) >>  RCC_BMCFGR_BMPRE_Pos))

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
#define LL_RCC_CALC_PCLK1_FREQ(hclk_freq, apb1_prescaler) \
  ((hclk_freq) >> (APBPrescTable[((apb1_prescaler) & RCC_APBCFGR_PPRE1) >> RCC_APBCFGR_PPRE1_Pos]))

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
#define LL_RCC_CALC_PCLK2_FREQ(hclk_freq, apb2_prescaler) \
  ((hclk_freq) >> (APBPrescTable[((apb2_prescaler) & RCC_APBCFGR_PPRE2) >> RCC_APBCFGR_PPRE2_Pos]))

/**
  * @brief  Helper macro to calculate the PCLK4 frequency (APB4).
  * @param  hclk_freq HCLK frequency
  * @param  apb4_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB4_PRESCALER_1
  *         @arg @ref LL_RCC_APB4_PRESCALER_2
  *         @arg @ref LL_RCC_APB4_PRESCALER_4
  *         @arg @ref LL_RCC_APB4_PRESCALER_8
  *         @arg @ref LL_RCC_APB4_PRESCALER_16
  * @retval PCLK4 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK4_FREQ(hclk_freq, apb4_prescaler) \
  ((hclk_freq) >> (APBPrescTable[((apb4_prescaler) & RCC_APBCFGR_PPRE4) >> RCC_APBCFGR_PPRE4_Pos]))

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup RCC_LL_Exported_Functions RCC Exported Functions
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
  * @brief  Disable HSE oscillator.
  * @rmtoll
  *  CR         HSEON         LL_RCC_HSE_Disable
  */
__STATIC_INLINE void LL_RCC_HSE_Disable(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
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
  * @brief  Set external HSE clock type.
  * @rmtoll
  *  CR         HSEEXT         LL_RCC_HSE_SetExternalClockType
  * @param  hse_type This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_TYPE
  *         @arg @ref LL_RCC_HSE_DIGITAL_TYPE
  * @note   This bit can be written only if the HSE oscillator is disabled.
  */
__STATIC_INLINE void LL_RCC_HSE_SetExternalClockType(uint32_t hse_type)
{
  STM32_MODIFY_REG(RCC->CR, RCC_CR_HSEEXT, hse_type);
}

/**
  * @brief  Get External HSE clock type.
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
  * @brief  Configure HSE external oscillator in bypass.
  * @rmtoll
  *  CR         HSEBYP         LL_RCC_HSE_ConfigBypass \n
  *  CR         HSEEXT         LL_RCC_HSE_ConfigBypass
  * @param  hse_type This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_TYPE
  *         @arg @ref LL_RCC_HSE_DIGITAL_TYPE
  */
__STATIC_INLINE void LL_RCC_HSE_ConfigBypass(uint32_t hse_type)
{
  STM32_MODIFY_REG(RCC->CR, RCC_CR_HSEBYP | RCC_CR_HSEEXT, RCC_CR_HSEBYP | hse_type);
}

/**
  * @brief  Enable HSE clock security system (HSE CSSON).
  * @rmtoll
  *  CR         HSECSSON         LL_RCC_HSE_EnableCSS
  * @note   Once HSE Clock Security System is enabled it cannot be changed anymore unless
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
  *  BDCR         LSEON         LL_RCC_LSE_Enable
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  STM32_SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Disable LSE oscillator.
  * @rmtoll
  *  BDCR         LSEON         LL_RCC_LSE_Disable
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  STM32_CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Check if LSE oscillator is enabled.
  * @rmtoll
  *  BDCR         LSEON         LL_RCC_LSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabled(void)
{
  return ((STM32_READ_BIT(RCC->BDCR, RCC_BDCR_LSEON) == RCC_BDCR_LSEON) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE oscillator is ready.
  * @rmtoll
  *  BDCR         LSERDY         LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == RCC_BDCR_LSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable LSE external clock source (LSE bypass).
  * @rmtoll
  *  BDCR         LSEBYP         LL_RCC_LSE_EnableBypass
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  STM32_SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Disable LSE external clock source (LSE bypass).
  * @rmtoll
  *  BDCR         LSEBYP         LL_RCC_LSE_DisableBypass
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  STM32_CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Check if LSE oscillator is bypassed.
  * @rmtoll
  *  BDCR         LSEBYP         LL_RCC_LSE_IsBypassed
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsBypassed(void)
{
  return ((STM32_READ_BIT(RCC->BDCR, RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP) ? 1UL : 0UL);
}

/**
  * @brief  Set external LSE clock type.
  * @rmtoll
  *  BDCR         LSEEXT         LL_RCC_LSE_SetExternalClockType
  * @param  lse_type This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSE_ANALOG_TYPE
  *         @arg @ref LL_RCC_LSE_DIGITAL_TYPE
  * @note   This bit can be written only if the LSE oscillator is disabled.
  */
__STATIC_INLINE void LL_RCC_LSE_SetExternalClockType(uint32_t lse_type)
{
  STM32_MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEEXT, lse_type);
}

/**
  * @brief  Get External LSE clock type.
  * @rmtoll
  *  BDCR         LSEEXT         LL_RCC_LSE_GetExternalClockType
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSE_ANALOG_TYPE
  *         @arg @ref LL_RCC_LSE_DIGITAL_TYPE
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetExternalClockType(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->BDCR, RCC_BDCR_LSEEXT));
}

/**
  * @brief  Configure LSE external oscillator in bypass.
  * @rmtoll
  *  BDCR         LSEBYP         LL_RCC_LSE_ConfigBypass \n
  *  BDCR         LSEEXT         LL_RCC_LSE_ConfigBypass
  * @param  lse_type This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSE_ANALOG_TYPE
  *         @arg @ref LL_RCC_LSE_DIGITAL_TYPE
  */
__STATIC_INLINE void LL_RCC_LSE_ConfigBypass(uint32_t lse_type)
{
  STM32_MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEBYP | RCC_BDCR_LSEEXT, RCC_BDCR_LSEBYP | lse_type);
}

/**
  * @brief  Set LSE oscillator drive capability.
  * @rmtoll
  *  BDCR         LSEDRV         LL_RCC_LSE_SetDriveCapability
  * @param  lse_drive This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  * @note   The oscillator is in crystal mode when it is not in bypass mode.
  */
__STATIC_INLINE void LL_RCC_LSE_SetDriveCapability(uint32_t lse_drive)
{
  STM32_MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, lse_drive);
}

/**
  * @brief  Get LSE oscillator drive capability.
  * @rmtoll
  *  BDCR         LSEDRV         LL_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetDriveCapability(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->BDCR, RCC_BDCR_LSEDRV));
}

/**
  * @brief  Enable LSE clock security system (LSE CSSON).
  * @rmtoll
  *  BDCR         LSECSSON         LL_RCC_LSE_EnableCSS
  */
__STATIC_INLINE void LL_RCC_LSE_EnableCSS(void)
{
  STM32_SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Disable LSE clock security system (LSE CSSON).
  * @rmtoll
  *  BDCR         LSECSSON         LL_RCC_LSE_DisableCSS
  * @note   Clock security system can be disabled only after a LSE
  *         failure detection. In that case it must be disabled by software.
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  STM32_CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Set Rearm Clock Security System on LSE.
  * @rmtoll
  *  BDCR         LSECSSRA         LL_RCC_LSE_SetRearmCSS
  * @note   LSE Clock security system can be re-enabled after a LSE failure detection.
  *         Before re-enabling it, LSECSSON must be set to 0.
  */
__STATIC_INLINE void LL_RCC_LSE_SetRearmCSS(void)
{
  STM32_SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSRA);
}

/**
  * @brief  Reset Rearm Clock Security System on LSE.
  * @rmtoll
  *  BDCR         LSECSSRA         LL_RCC_LSE_ResetRearmCSS
  * @note   Clock security system can be re-enabled after an LSE failure detection.
  *         Before re-enabling it, LSECSSON must be set to 0.
  */
__STATIC_INLINE void LL_RCC_LSE_ResetRearmCSS(void)
{
  STM32_CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSRA);
}

/**
  * @brief  Check if CSS on LSE failure Detection.
  * @rmtoll
  *  BDCR         LSECSSD         LL_RCC_LSE_IsCSSDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsCSSDetected(void)
{
  return ((STM32_READ_BIT(RCC->BDCR, RCC_BDCR_LSECSSD) == RCC_BDCR_LSECSSD) ? 1UL : 0UL);
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
  * @note   When HSITRIM is written, HSICAL is updated with the sum of
  *         HSITRIM and the factory trim value.
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
  * @retval Between Min_Data = 0 and Max_Data = 1023
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_GetCalibration(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CRRCR, RCC_CRRCR_HSI48CAL) >> RCC_CRRCR_HSI48CAL_Pos);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_CSI CSI
  * @{
  */

/**
  * @brief  Enable CSI oscillator.
  * @rmtoll
  *  CR         CSION         LL_RCC_CSI_Enable
  */
__STATIC_INLINE void LL_RCC_CSI_Enable(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_CSION);
}

/**
  * @brief  Disable CSI oscillator.
  * @rmtoll
  *  CR         CSION         LL_RCC_CSI_Disable
  */
__STATIC_INLINE void LL_RCC_CSI_Disable(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_CSION);
}

/**
  * @brief  Check if CSI oscillator is enabled.
  * @rmtoll
  *  CR         CSION         LL_RCC_CSI_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_CSI_IsEnabled(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_CSION) == RCC_CR_CSION) ? 1UL : 0UL);
}

/**
  * @brief  Check if CSI oscillator is ready.
  * @rmtoll
  *  CR         CSIRDY         LL_RCC_CSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_CSI_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_CSIRDY) == RCC_CR_CSIRDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable CSI oscillator in Stop Mode.
  * @rmtoll
  *  CR         CSIKERON         LL_RCC_CSI_EnableInStopMode
  * @note   CSI oscillator is forced ON even in Stop mode.
  */
__STATIC_INLINE void LL_RCC_CSI_EnableInStopMode(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_CSIKERON);
}

/**
  * @brief  Disable CSI oscillator in Stop Mode.
  * @rmtoll
  *  CR         CSIKERON         LL_RCC_CSI_DisableInStopMode
  */
__STATIC_INLINE void LL_RCC_CSI_DisableInStopMode(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_CSIKERON);
}

/**
  * @brief  Check if CSI is enabled in Stop Mode.
  * @rmtoll
  *  CR         CSIKERON         LL_RCC_CSI_IsEnabledInStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_CSI_IsEnabledInStopMode(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_CSIKERON) == RCC_CR_CSIKERON) ? 1UL : 0UL);
}

/**
  * @brief  Get CSI calibration value.
  * @rmtoll
  *  CSICFGR         CSICAL         LL_RCC_CSI_GetCalibration
  * @note   When CSITRIM is written, CSICAL is updated with the sum of
  *         CSITRIM and the factory trim value.
  * @retval Between Min_Data = 0 and Max_Data = 255
  */
__STATIC_INLINE uint32_t LL_RCC_CSI_GetCalibration(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CSICFGR, RCC_CSICFGR_CSICAL) >> RCC_CSICFGR_CSICAL_Pos);
}

/**
  * @brief  Set CSI calibration trimming.
  * @rmtoll
  *  CSICFGR         CSITRIM         LL_RCC_CSI_SetCalibTrimming
  * @param  value Between Min_Data = 0 and Max_Data = 63
  * @note   user-programmable trimming value that is added to the CSICAL.
  * @note   Default value is 32, which, when added to the CSICAL value, trim the CSI to 48 MHz +/- 1 %.
  */
__STATIC_INLINE void LL_RCC_CSI_SetCalibTrimming(uint32_t value)
{
  STM32_MODIFY_REG(RCC->CSICFGR, RCC_CSICFGR_CSITRIM, value << RCC_CSICFGR_CSITRIM_Pos);
}

/**
  * @brief  Get CSI calibration trimming.
  * @rmtoll
  *  CSICFGR         CSITRIM         LL_RCC_CSI_GetCalibTrimming
  * @retval Between Min_Data = 0 and Max_Data = 63
  */
__STATIC_INLINE uint32_t LL_RCC_CSI_GetCalibTrimming(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CSICFGR, RCC_CSICFGR_CSITRIM) >> RCC_CSICFGR_CSITRIM_Pos);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */

/**
  * @brief  Enable LSI oscillator.
  * @rmtoll
  *  CSR         LSION         LL_RCC_LSI_Enable
  */
__STATIC_INLINE void LL_RCC_LSI_Enable(void)
{
  STM32_SET_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @brief  Disable LSI oscillator.
  * @rmtoll
  *  CSR         LSION         LL_RCC_LSI_Disable
  */
__STATIC_INLINE void LL_RCC_LSI_Disable(void)
{
  STM32_CLEAR_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @brief  Check if LSI oscillator is enabled.
  * @rmtoll
  *  CSR         LSION         LL_RCC_LSI_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsEnabled(void)
{
  return ((STM32_READ_BIT(RCC->CSR, RCC_CSR_LSION) == RCC_CSR_LSION) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI oscillator is ready.
  * @rmtoll
  *  CSR         LSIRDY         LL_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == RCC_CSR_LSIRDY) ? 1UL : 0UL);
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
  *  CFGR         SW         LL_RCC_SetSysClkSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_PLL1
  */
__STATIC_INLINE void LL_RCC_SetSysClkSource(uint32_t source)
{
  STM32_MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, source);
}

/**
  * @brief  Get the system clock source.
  * @rmtoll
  *  CFGR         SWS         LL_RCC_GetSysClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_CSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_PLL1
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
}

/**
  * @brief  Set Clock After Wake-Up From Stop mode.
  * @rmtoll
  *  CFGR         STOPWUCK         LL_RCC_SetClkAfterWakeFromStop
  * @param  clock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSI
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_CSI
  */
__STATIC_INLINE void LL_RCC_SetClkAfterWakeFromStop(uint32_t clock)
{
  STM32_MODIFY_REG(RCC->CFGR, RCC_CFGR_STOPWUCK, clock);
}

/**
  * @brief  Get Clock After Wake-Up From Stop mode.
  * @rmtoll
  *  CFGR         STOPWUCK         LL_RCC_GetClkAfterWakeFromStop
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSI
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_CSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetClkAfterWakeFromStop(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CFGR, RCC_CFGR_STOPWUCK));
}

/**
  * @brief  Set Kernel Clock After Wake-Up From Stop mode.
  * @rmtoll
  *  CFGR         STOPKERWUCK         LL_RCC_SetKerClkAfterWakeFromStop
  * @param  clock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPKERCLOCK_HSI
  *         @arg @ref LL_RCC_STOP_WAKEUPKERCLOCK_CSI
  */
__STATIC_INLINE void LL_RCC_SetKerClkAfterWakeFromStop(uint32_t clock)
{
  STM32_MODIFY_REG(RCC->CFGR, RCC_CFGR_STOPKERWUCK, clock);
}

/**
  * @brief  Get Kernel Clock After Wake-Up From Stop mode.
  * @rmtoll
  *  CFGR         STOPKERWUCK         LL_RCC_GetKerClkAfterWakeFromStop
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPKERCLOCK_HSI
  *         @arg @ref LL_RCC_STOP_WAKEUPKERCLOCK_CSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetKerClkAfterWakeFromStop(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CFGR, RCC_CFGR_STOPKERWUCK));
}

/**
  * @brief  Set System prescaler.
  * @rmtoll
  *  CDCFGR         CPRE         LL_RCC_SetSysPrescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_1
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_2
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_4
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_8
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_16
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_64
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_128
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_256
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_512
  */
__STATIC_INLINE void LL_RCC_SetSysPrescaler(uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->CDCFGR, RCC_CDCFGR_CPRE, prescaler);
}

/**
  * @brief  Get System prescaler.
  * @rmtoll
  *  CDCFGR         CPRE         LL_RCC_GetSysPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_1
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_2
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_4
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_8
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_16
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_64
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_128
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_256
  *         @arg @ref LL_RCC_SYSCLK_PRESCALER_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysPrescaler(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CDCFGR, RCC_CDCFGR_CPRE));
}

/**
  * @brief  Set AHB prescaler.
  * @rmtoll
  *  BMCFGR         BMPRE         LL_RCC_SetBMPrescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_BMCLK_PRESCALER_1
  *         @arg @ref LL_RCC_BMCLK_PRESCALER_2
  */
__STATIC_INLINE void LL_RCC_SetBMPrescaler(uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->BMCFGR, RCC_BMCFGR_BMPRE, prescaler);
}

/**
  * @brief  Get AHB prescaler.
  * @rmtoll
  *  BMCFGR         BMPRE         LL_RCC_GetBMPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_BMCLK_PRESCALER_1
  *         @arg @ref LL_RCC_BMCLK_PRESCALER_2
  */
__STATIC_INLINE uint32_t LL_RCC_GetBMPrescaler(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->BMCFGR, RCC_BMCFGR_BMPRE));
}

/**
  * @brief  Set APB1 prescaler.
  * @rmtoll
  *  APBCFGR         PPRE1         LL_RCC_SetAPB1Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB1Prescaler(uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE1, prescaler);
}

/**
  * @brief  Get APB1 prescaler.
  * @rmtoll
  *  APBCFGR         PPRE1         LL_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB1Prescaler(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE1));
}

/**
  * @brief  Set APB2 prescaler.
  * @rmtoll
  *  APBCFGR         PPRE2         LL_RCC_SetAPB2Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB2Prescaler(uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE2, prescaler);
}

/**
  * @brief  Get APB2 prescaler.
  * @rmtoll
  *  APBCFGR         PPRE2         LL_RCC_GetAPB2Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB2Prescaler(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE2));
}

/**
  * @brief  Set APB4 prescaler.
  * @rmtoll
  *  APBCFGR         PPRE4         LL_RCC_SetAPB4Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB4_PRESCALER_1
  *         @arg @ref LL_RCC_APB4_PRESCALER_2
  *         @arg @ref LL_RCC_APB4_PRESCALER_4
  *         @arg @ref LL_RCC_APB4_PRESCALER_8
  *         @arg @ref LL_RCC_APB4_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB4Prescaler(uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE4, prescaler);
}

/**
  * @brief  Get APB4 prescaler.
  * @rmtoll
  *  APBCFGR         PPRE4         LL_RCC_GetAPB4Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB4_PRESCALER_1
  *         @arg @ref LL_RCC_APB4_PRESCALER_2
  *         @arg @ref LL_RCC_APB4_PRESCALER_4
  *         @arg @ref LL_RCC_APB4_PRESCALER_8
  *         @arg @ref LL_RCC_APB4_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB4Prescaler(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE4));
}

/**
  * @brief  Configure buses prescalers (AHB, APB1, APB2, APB4 and ).
  * @rmtoll
  *  BMCFGR         BMPRE         LL_RCC_ConfigBusClock \n
  *  APBCFGR        PPRE1         LL_RCC_ConfigBusClock \n
  *  APBCFGR        PPRE2         LL_RCC_ConfigBusClock \n
  *  APBCFGR        PPRE4         LL_RCC_ConfigBusClock
  * @param  ahb_pres Bus prescaler value of AHB
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_BMCLK_PRESCALER_1
  *         @arg @ref LL_RCC_BMCLK_PRESCALER_2
  * @param  apb1_apb2_apb4_pres Bus prescaler value of APB1, APB2 and APB4
  *         This parameter can be one or a combination of the following values:
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
  *         @arg @ref LL_RCC_APB4_PRESCALER_1
  *         @arg @ref LL_RCC_APB4_PRESCALER_2
  *         @arg @ref LL_RCC_APB4_PRESCALER_4
  *         @arg @ref LL_RCC_APB4_PRESCALER_8
  *         @arg @ref LL_RCC_APB4_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_ConfigBusClock(uint32_t ahb_pres, uint32_t apb1_apb2_apb4_pres)
{
  STM32_MODIFY_REG(RCC->BMCFGR, (RCC_BMCFGR_BMPRE), ahb_pres);
  STM32_MODIFY_REG(RCC->APBCFGR, (RCC_APBCFGR_PPRE1 | RCC_APBCFGR_PPRE2 | RCC_APBCFGR_PPRE4), apb1_apb2_apb4_pres);
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
  *  CFGR         MCO1SEL         LL_RCC_ConfigMCO \n
  *  CFGR         MCO2SEL         LL_RCC_ConfigMCO \n
  *  CFGR         MCO1PRE         LL_RCC_ConfigMCO \n
  *  CFGR         MCO2PRE         LL_RCC_ConfigMCO
  * @param  mcox_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI
  *         @arg @ref LL_RCC_MCO1SOURCE_LSE
  *         @arg @ref LL_RCC_MCO1SOURCE_HSE
  *         @arg @ref LL_RCC_MCO1SOURCE_PLL1Q
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI48
  *         @arg @ref LL_RCC_MCO2SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO2SOURCE_PLL2P
  *         @arg @ref LL_RCC_MCO2SOURCE_HSE
  *         @arg @ref LL_RCC_MCO2SOURCE_PLL1P
  *         @arg @ref LL_RCC_MCO2SOURCE_CSI
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
  *         @arg @ref LL_RCC_MCO1SOURCE_NOCLOCK
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
  */
__STATIC_INLINE void LL_RCC_ConfigMCO(uint32_t mcox_source, uint32_t mcox_prescaler)
{
  STM32_MODIFY_REG(RCC->CFGR, ((uint32_t)(mcox_source | mcox_prescaler) << 16U), \
                   (mcox_source & (RCC_CFGR_MCO1SEL | RCC_CFGR_MCO2SEL)) | \
                   (mcox_prescaler & (RCC_CFGR_MCO1PRE | RCC_CFGR_MCO2PRE)));
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
  *  CCIPR2         *         LL_RCC_SetClockSource\n
  *  CCIPR3         *         LL_RCC_SetClockSource\n
  *  CCIPR4         *         LL_RCC_SetClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PER
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PER
  */
__STATIC_INLINE void LL_RCC_SetClockSource(uint32_t clk_src)
{
  volatile uint32_t *pReg = (uint32_t *)((uint32_t)&RCC->CCIPR1 + LL_CLKSOURCE_REG(clk_src));
  STM32_MODIFY_REG(*pReg, LL_CLKSOURCE_MASK(clk_src), LL_CLKSOURCE_CONFIG(clk_src));
}

/**
  * @brief  Configure FMCx clock source.
  * @rmtoll
  * CCIPR1         FMCSEL         LL_RCC_SetFMCClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_HCLK5
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_PLL2R
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_HSI
  */
__STATIC_INLINE void LL_RCC_SetFMCClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_FMCSEL, clk_src);
}

/**
  * @brief  Configure SDMMCx clock source.
  * @rmtoll
  * CCIPR1         SDMMC1SEL         LL_RCC_SetSDMMCClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC1_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_SDMMC1_CLKSOURCE_PLL2T
  */
__STATIC_INLINE void LL_RCC_SetSDMMCClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SDMMC1SEL, clk_src);
}

/**
  * @brief  Configure XSPIx clock source.
  * @rmtoll
  * CCIPR1         XSPI1SEL         LL_RCC_SetXSPIClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HCLK5
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2T
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetXSPIClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_XSPI1SEL, clk_src);
}

/**
  * @brief  Configure OTGFSx clock source.
  * @rmtoll
  * CCIPR1         OTGFSSEL         LL_RCC_SetUSBOTGFSClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USBOTGFS_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_USBOTGFS_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USBOTGFS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USBOTGFS_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetUSBOTGFSClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_OTGFSSEL, clk_src);
}

/**
  * @brief  Configure ADFx clock source.
  * @rmtoll
  * CCIPR1         ADF1SEL         LL_RCC_SetADFClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_HCLK1
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetADFClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ADF1SEL, clk_src);
}

/**
  * @brief  Configure ADCx clock source.
  * @rmtoll
  * CCIPR1         ADCSEL         LL_RCC_SetADCClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PER
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetADCClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ADCSEL, clk_src);
}

/**
  * @brief  Configure PERx clock source.
  * @rmtoll
  * CCIPR1         CKPERSEL         LL_RCC_PERCLK_SetSource
  * @param  cpx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PER_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_PER_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_PER_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_PER_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_PERCLK_SetSource(uint32_t cpx_source)
{
  STM32_MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_CKPERSEL, cpx_source);
}

/**
  * @brief  Get PERx clock source.
  * @rmtoll
  * CCIPR1         CKPERSEL         LL_RCC_PERCLK_GetSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PER_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PER_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_PER_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_PER_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_PER_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_PERCLK_GetSource(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR1, RCC_CCIPR1_CKPERSEL));
}

/**
  * @brief  Configure UART4, 5, 6, 7, 8 and USART 2, 3 clock source.
  * @rmtoll
  *  CCIPR2         UART234578SEL         LL_RCC_SetUARTClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetUARTClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_UART234578SEL, clk_src);
}

/**
  * @brief  Configure SPIx clock source.
  * @rmtoll
  *  CCIPR3         SPI1SEL          LL_RCC_SetSPIClockSource \n
  *  CCIPR4         SPI6SEL          LL_RCC_SetSPIClockSource \n
  *  CCIPR2         SPI23SEL         LL_RCC_SetSPIClockSource \n
  *  CCIPR3         SPI45SEL         LL_RCC_SetSPIClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PER
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetSPIClockSource(uint32_t clk_src)
{
  LL_RCC_SetClockSource(clk_src);
}

/**
  * @brief  Configure I2Cx clock source.
  * @rmtoll
  *  CCIPR2         I2C123SEL         LL_RCC_SetI2CClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C123_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C123_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I2C123_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C123_CLKSOURCE_CSI
  */
__STATIC_INLINE void LL_RCC_SetI2CClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I2C123SEL, clk_src);
}

/**
  * @brief  Configure I3Cx clock source.
  * @rmtoll
  *  CCIPR2         I3C1SEL         LL_RCC_SetI3CClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_CSI
  */
__STATIC_INLINE void LL_RCC_SetI3CClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I3C1SEL, clk_src);
}

/**
  * @brief  Configure LPTIMx clock source.
  * @rmtoll
  *  CCIPR2         LPTIM1SEL          LL_RCC_SetLPTIMClockSource \n
  *  CCIPR4         LPTIM23SEL         LL_RCC_SetLPTIMClockSource \n
  *  CCIPR4         LPTIM45SEL         LL_RCC_SetLPTIMClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetLPTIMClockSource(uint32_t clk_src)
{
  LL_RCC_SetClockSource(clk_src);
}

/**
  * @brief  Configure FDCANx clock source.
  * @rmtoll
  *  CCIPR2         FDCANSEL         LL_RCC_SetFDCANClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetFDCANClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_FDCANSEL, clk_src);
}

/**
  * @brief  Configure USART1, 6, 10 and UART9 clock source.
  * @rmtoll
  *  CCIPR3         USART16910SEL         LL_RCC_SetUSARTClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetUSARTClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_USART16910SEL, clk_src);
}

/**
  * @brief  Configure LPUARTx clock source.
  * @rmtoll
  *  CCIPR4         LPUART1SEL         LL_RCC_SetLPUARTClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_NONE
  */
__STATIC_INLINE void LL_RCC_SetLPUARTClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_LPUART1SEL, clk_src);
}

/**
  * @brief  Configure DACx clock source.
  * @rmtoll
  *  CCIPR4         DAC1SEL         LL_RCC_SetDACClockSource \n
  *  CCIPR4         DAC2SEL         LL_RCC_SetDACClockSource \n
  *  CCIPR4         DAC3SEL         LL_RCC_SetDACClockSource \n
  *  CCIPR4         DAC4SEL         LL_RCC_SetDACClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PER
  */
__STATIC_INLINE void LL_RCC_SetDACClockSource(uint32_t clk_src)
{
  LL_RCC_SetClockSource(clk_src);
}

/**
  * @brief  Configure DACSHx clock source.
  * @rmtoll
  *  CCIPR4         DAC1SHSEL         LL_RCC_SetDACSHClockSource
  * @param  clk_src This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSI
  */
__STATIC_INLINE void LL_RCC_SetDACSHClockSource(uint32_t clk_src)
{
  STM32_MODIFY_REG(RCC->CCIPR4, RCC_CCIPR4_DAC1SHSEL, clk_src);
}

/**
  * @brief  Get periph clock source.
  * @rmtoll
  *  CCIPR2         *         LL_RCC_GetClockSource \n
  *  CCIPR3         *         LL_RCC_GetClockSource \n
  *  CCIPR4         *         LL_RCC_GetClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PER
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PER
  */
__STATIC_INLINE uint32_t LL_RCC_GetClockSource(uint32_t Periph)
{
  const volatile uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&RCC->CCIPR1) + LL_CLKSOURCE_REG(Periph)));
  return (uint32_t)(Periph | (((STM32_READ_BIT(*pReg, LL_CLKSOURCE_MASK(Periph))) >> \
                               LL_CLKSOURCE_POS(Periph)) << LL_RCC_CONFIG_SHIFT));
}

/**
  * @brief  Get FMCx clock source.
  * @rmtoll
  *  CCIPR1         FMCSEL         LL_RCC_GetFMCClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FMC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_HCLK5
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_PLL2R
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetFMCClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR1, RCC_CCIPR1_FMCSEL));
}

/**
  * @brief  Get SDMMCx clock source.
  * @rmtoll
  *  CCIPR1         SDMMC1SEL         LL_RCC_GetSDMMCClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC1_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_SDMMC1_CLKSOURCE_PLL2T
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMCClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SDMMC1SEL));
}

/**
  * @brief  Get XSPIx clock source.
  * @rmtoll
  *  CCIPR1         XSPI1SEL         LL_RCC_GetXSPIClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HCLK5
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2S
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PLL2T
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetXSPIClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR1, RCC_CCIPR1_XSPI1SEL));
}

/**
  * @brief  Get OTGFSx clock source.
  * @rmtoll
  *  CCIPR1         OTGFSSEL         LL_RCC_GetUSBOTGFSClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USBOTGFS_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USBOTGFS_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_USBOTGFS_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USBOTGFS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_USBOTGFS_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSBOTGFSClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR1, RCC_CCIPR1_OTGFSSEL));
}

/**
  * @brief  Get ADFx clock source.
  * @rmtoll
  *  CCIPR1         ADF1SEL         LL_RCC_GetADFClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_HCLK1
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetADFClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ADF1SEL));
}

/**
  * @brief  Get ADCx clock source.
  * @rmtoll
  *  CCIPR1         ADCSEL         LL_RCC_GetADCClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PER
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ADCSEL));
}

/**
  * @brief  Get UART4, 5, 6, 7, 8 and USART 2, 3 clock source.
  * @rmtoll
  *  CCIPR2         UART234578SEL         LL_RCC_GetUARTClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART234578_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUARTClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR2, RCC_CCIPR2_UART234578SEL));
}

/**
  * @brief  Get SPIx clock source.
  * @rmtoll
  *  CCIPR3         SPI1SEL          LL_RCC_GetSPIClockSource \n
  *  CCIPR4         SPI6SEL          LL_RCC_GetSPIClockSource \n
  *  CCIPR2         SPI23SEL         LL_RCC_GetSPIClockSource \n
  *  CCIPR3         SPI45SEL         LL_RCC_GetSPIClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PLL3P
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_PER
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPIClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}

/**
  * @brief  Get I2Cx clock source.
  * @rmtoll
  *  CCIPR2         I2C123SEL         LL_RCC_GetI2CClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C123_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C123_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C123_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I2C123_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C123_CLKSOURCE_CSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2CClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I2C123SEL));
}

/**
  * @brief  Get I3Cx clock source.
  * @rmtoll
  *  CCIPR2         I3C1SEL         LL_RCC_GetI3CClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_CSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3CClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I3C1SEL));
}

/**
  * @brief  Get LPTIMx clock source.
  * @rmtoll
  *  CCIPR2         LPTIM1SEL          LL_RCC_GetLPTIMClockSource \n
  *  CCIPR4         LPTIM23SEL         LL_RCC_GetLPTIMClockSource \n
  *  CCIPR4         LPTIM45SEL         LL_RCC_GetLPTIMClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_PER
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIMClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}

/**
  * @brief  Get FDCANx clock source.
  * @rmtoll
  *  CCIPR2         FDCANSEL         LL_RCC_GetFDCANClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL1Q
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetFDCANClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR2, RCC_CCIPR2_FDCANSEL));
}

/**
  * @brief  Get USART1, 6, 10 and UART9 clock source.
  * @rmtoll
  *  CCIPR3         USART16910SEL         LL_RCC_GetUSARTClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART16910_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSARTClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR3, RCC_CCIPR3_USART16910SEL));
}

/**
  * @brief  Get LPUARTx clock source.
  * @rmtoll
  *  CCIPR4         LPUART1SEL         LL_RCC_GetLPUARTClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK4
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PLL2Q
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PLL3Q
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_CSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUARTClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR4, RCC_CCIPR4_LPUART1SEL));
}

/**
  * @brief  Get DACx clock source.
  * @rmtoll
  *  CCIPR4         DAC1SEL         LL_RCC_GetDACClockSource \n
  *  CCIPR4         DAC2SEL         LL_RCC_GetDACClockSource \n
  *  CCIPR4         DAC3SEL         LL_RCC_GetDACClockSource \n
  *  CCIPR4         DAC4SEL         LL_RCC_GetDACClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC2_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC3_CLKSOURCE_PER
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_ADC
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_DAC4_CLKSOURCE_PER
  */
__STATIC_INLINE uint32_t LL_RCC_GetDACClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}

/**
  * @brief  Get DACSHx clock source.
  * @rmtoll
  *  CCIPR4         DAC1SHSEL         LL_RCC_GetDACSHClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetDACSHClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR4, RCC_CCIPR4_DAC1SHSEL));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_RTC RTC
  * @{
  */

/**
  * @brief  Set RTC Clock Source.
  * @rmtoll
  *  BDCR         RTCSEL         LL_RCC_SetRTCClockSource
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
  STM32_MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, source);
}

/**
  * @brief  Get RTC Clock Source.
  * @rmtoll
  *  BDCR         RTCSEL         LL_RCC_GetRTCClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTCClockSource(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL));
}

/**
  * @brief  Enable RTC.
  * @rmtoll
  *  BDCR         RTCEN         LL_RCC_EnableRTC
  */
__STATIC_INLINE void LL_RCC_EnableRTC(void)
{
  STM32_SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Disable RTC.
  * @rmtoll
  *  BDCR         RTCEN         LL_RCC_DisableRTC
  */
__STATIC_INLINE void LL_RCC_DisableRTC(void)
{
  STM32_CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Check if RTC has been enabled or not.
  * @rmtoll
  *  BDCR         RTCEN         LL_RCC_IsEnabledRTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledRTC(void)
{
  return ((STM32_READ_BIT(RCC->BDCR, RCC_BDCR_RTCEN) == RCC_BDCR_RTCEN) ? 1UL : 0UL);
}

/**
  * @brief  Force the Backup domain reset.
  * @rmtoll
  *  BDCR         VSWRST         LL_RCC_ForceBackupDomainReset
  */
__STATIC_INLINE void LL_RCC_ForceBackupDomainReset(void)
{
  STM32_SET_BIT(RCC->BDCR, RCC_BDCR_VSWRST);
}

/**
  * @brief  Release the Backup domain reset.
  * @rmtoll
  *  BDCR         VSWRST         LL_RCC_ReleaseBackupDomainReset
  */
__STATIC_INLINE void LL_RCC_ReleaseBackupDomainReset(void)
{
  STM32_CLEAR_BIT(RCC->BDCR, RCC_BDCR_VSWRST);
}

/**
  * @brief  Set HSE Prescaler for RTC Clock.
  * @rmtoll
  *  CFGR         RTCPRE         LL_RCC_SetRTC_HSEPrescaler
  * @param prescaler parameter can be a value between 0 and 63 with 0 and 1 values meaning no clock output
  * @note   prescaler must be correctly set to ensure that the clock supplied to the
  *         RTC is lower than 1MHz.
  */
__STATIC_INLINE void LL_RCC_SetRTC_HSEPrescaler(uint32_t Prescaler)
{
  STM32_MODIFY_REG(RCC->CFGR, RCC_CFGR_RTCPRE, ((uint32_t)Prescaler << RCC_CFGR_RTCPRE_Pos));
}

/**
  * @brief  Get HSE Prescaler for RTC Clock.
  * @rmtoll
  *  CFGR         RTCPRE         LL_RCC_GetRTC_HSEPrescaler
  * @retval Returned value can be a value between 1 and 63
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTC_HSEPrescaler(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->CFGR, RCC_CFGR_RTCPRE)) >> RCC_CFGR_RTCPRE_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_ADC_CLOCK ADC
  * @{
  */

/**
  * @brief  Set ADC Clock Prescaler.
  * @rmtoll
  *  CCIPR1          ADCDIV        LL_RCC_SetADCPrescaler
  * @param  divider This parameter can be one of the following values:
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
  STM32_MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ADCDIV, prescaler);
}

/**
  * @brief  Get ADC Clock Prescaler.
  * @rmtoll
  *  CCIPR1          ADCDIV        LL_RCC_GetADCPrescaler
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
  return (uint32_t)(STM32_READ_BIT(RCC->CCIPR1, RCC_CCIPR1_ADCDIV));
}

/**
  * @brief  Configure ADC Clock.
  * @rmtoll
  *  CCIPR5          ADCDIV        LL_RCC_ConfigADC
  * @param  clk_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HCLK3
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_TIM
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL2P
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PLL3R
  *         @arg @ref LL_RCC_ADC_CLKSOURCE_PER
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
__STATIC_INLINE void LL_RCC_ConfigADC(uint32_t clk_source, uint32_t prescaler)
{
  STM32_MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ADCSEL | RCC_CCIPR1_ADCDIV, clk_source | prescaler);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_CKPROT Clock protection
  * @{
  */

/**
  * @brief  Enable XSPI clock protection.
  * @rmtoll
  *  CKPROTR         XSPICKP         LL_RCC_EnableXSPIClockProtection
  */
__STATIC_INLINE void LL_RCC_EnableXSPIClockProtection(void)
{
  STM32_SET_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPICKP);
}

/**
  * @brief  Disable XSPI clock protection.
  * @rmtoll
  *  CKPROTR         XSPICKP         LL_RCC_DisableXSPIClockProtection
  */
__STATIC_INLINE void LL_RCC_DisableXSPIClockProtection(void)
{
  STM32_CLEAR_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPICKP);
}

/**
  * @brief  Check if XSPI clock protection has been enabled or not.
  * @rmtoll
  *  CKPROTR         XSPICKP         LL_RCC_IsEnabledXSPIClockProtection
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledXSPIClockProtection(void)
{
  return ((STM32_READ_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPICKP) == RCC_CKPROTR_XSPICKP) ? 1UL : 0UL);
}

/**
  * @brief  Enable FMC clock protection.
  * @rmtoll
  *  CKPROTR         FMCCKP         LL_RCC_EnableFMCClockProtection
  */
__STATIC_INLINE void LL_RCC_EnableFMCClockProtection(void)
{
  STM32_SET_BIT(RCC->CKPROTR, RCC_CKPROTR_FMCCKP);
}

/**
  * @brief  Disable FMC clock protection.
  * @rmtoll
  *  CKPROTR         FMCCKP         LL_RCC_DisableFMCClockProtection
  */
__STATIC_INLINE void LL_RCC_DisableFMCClockProtection(void)
{
  STM32_CLEAR_BIT(RCC->CKPROTR, RCC_CKPROTR_FMCCKP);
}

/**
  * @brief  Check if FMC clock protection has been enabled or not.
  * @rmtoll
  *  CKPROTR         FMCCKP         LL_RCC_IsEnabledFMCClockProtection
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledFMCClockProtection(void)
{
  return ((STM32_READ_BIT(RCC->CKPROTR, RCC_CKPROTR_FMCCKP) == RCC_CKPROTR_FMCCKP) ? 1UL : 0UL);
}

/**
  * @brief  Get XSPI kernel clock switch position.
  * @rmtoll
  *  CKPROTR         XSPISWP         LL_RCC_GetXSPISwitchPosition
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_XSPI_CLKSOURCE_SWP_NEUTRAL
  *         @arg @ref LL_RCC_XSPI_CLKSOURCE_SWP_HCLK5
  *         @arg @ref LL_RCC_XSPI_CLKSOURCE_SWP_PLL2S
  *         @arg @ref LL_RCC_XSPI_CLKSOURCE_SWP_PLL2T
  *         @arg @ref LL_RCC_XSPI_CLKSOURCE_SWP_HCLK5_DIV4
  */
__STATIC_INLINE uint32_t LL_RCC_GetXSPISwitchPosition(void)
{
  return (STM32_READ_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPISWP));
}

/**
  * @brief  Get FMC kernel clock switch position.
  * @rmtoll
  *  CKPROTR         FMCSWP         LL_RCC_GetFMCSwitchPosition
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_SWP_NEUTRAL
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_SWP_HCLK5
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_SWP_PLL1Q
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_SWP_PLL2R
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_SWP_HSI
  *         @arg @ref LL_RCC_FMC_CLKSOURCE_SWP_HCLK5_DIV4
  */
__STATIC_INLINE uint32_t LL_RCC_GetFMCSwitchPosition(void)
{
  return (STM32_READ_BIT(RCC->CKPROTR, RCC_CKPROTR_FMCSWP));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_PLL PLL
  * @{
  */

/**
  * @brief  Set the oscillator used as PLL clock source.
  * @rmtoll
  *  PLLCKSELR         PLLSRC         LL_RCC_PLL_SetSource
  * @param  pll_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_CSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  *         @arg @ref LL_RCC_PLLSOURCE_NO_CLK
  * @note   PLL clock source is common to all PLLs.
  * @note   PLLSRC can be written only when all PLLs are disabled.
  */
__STATIC_INLINE void LL_RCC_PLL_SetSource(uint32_t pll_source)
{
  STM32_MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_PLLSRC, pll_source);
}

/**
  * @brief  Get the oscillator used as PLL clock source.
  * @rmtoll
  *  PLLCKSELR         PLLSRC         LL_RCC_PLL_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_CSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  *         @arg @ref LL_RCC_PLLSOURCE_NO_CLK
  */
__STATIC_INLINE uint32_t LL_RCC_PLL_GetSource(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLLCKSELR, RCC_PLLCKSELR_PLLSRC));
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
  * @brief  Configure PLL1 used as SYSCLK Domain.
  * @rmtoll
  *  PLLCKSELR         PLLSRC         LL_RCC_PLL1_ConfigDomain_SYS \n
  *  PLLCKSELR         DIVM1          LL_RCC_PLL1_ConfigDomain_SYS \n
  *  PLL1DIVR1         DIVN           LL_RCC_PLL1_ConfigDomain_SYS \n
  *  PLL1DIVR1         DIVP           LL_RCC_PLL1_ConfigDomain_SYS
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLSOURCE_HSI
  *         @arg @ref LL_RCC_PLLSOURCE_CSI
  *         @arg @ref LL_RCC_PLLSOURCE_HSE
  *         @arg @ref LL_RCC_PLLSOURCE_NO_CLK
  * @param  pll1m parameter can be a value between 0 and 63
  * @param  pll1n parameter can be a value between 8 and 420
  * @param  pll1p parameter can be a value between 1 and 128 (Only division by 1 and even division are allowed)
  * @note   PLL1 Source can be written only when all PLLs are disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_ConfigDomain_SYS(uint32_t source, uint32_t pll1m, uint32_t pll1n, uint32_t pll1p)
{
  STM32_MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_PLLSRC | RCC_PLLCKSELR_DIVM1, source | \
                   (pll1m << RCC_PLLCKSELR_DIVM1_Pos));
  STM32_MODIFY_REG(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVN | RCC_PLL1DIVR1_DIVP,
                   ((pll1n - 1UL) << RCC_PLL1DIVR1_DIVN_Pos) | ((pll1p - 1UL) << RCC_PLL1DIVR1_DIVP_Pos));
}

/**
  * @brief  Enable PLL1 output mapped on SYSCLK Domain.
  * @rmtoll
  *  RCC_PLLCFGR         PLL1PEN         LL_RCC_PLL1_EnableOutput_SYS
  * @note   This API must be called only when PLL1 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutput_SYS(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, LL_RCC_PLL1_OUTPUT_P);
}

/**
  * @brief  Disable PLL1 output mapped on SYSCLK Domain.
  * @rmtoll
  *  RCC_PLLCFGR         PLL1PEN         LL_RCC_PLL1_DisableOutput_SYS
  * @note   Cannot be disabled if the PLL1 clock is used as the system clock
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutput_SYS(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, LL_RCC_PLL1_OUTPUT_P);
}

/**
  * @brief  Check if PLL1 output mapped on SYSCLK Domain is enabled.
  * @rmtoll
  *  RCC_PLLCFGR         PLL1PEN         LL_RCC_PLL1_IsEnabledOutput_SYS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledOutput_SYS(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, LL_RCC_PLL1_OUTPUT_P) == (LL_RCC_PLL1_OUTPUT_P)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1P output.
  * @rmtoll
  *  PLLCFGR         PLL1PEN         LL_RCC_PLL1_EnableOutputP
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutputP(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1PEN);
}

/**
  * @brief  Disable PLL1P output.
  * @rmtoll
  *  PLLCFGR         PLL1PEN         LL_RCC_PLL1_DisableOutputP
  * @note   Cannot be disabled if the PLL1P clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutputP(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1PEN);
}

/**
  * @brief  Check if PLL1P output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL1PEN         LL_RCC_PLL1_IsEnabledOutputP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledOutputP(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1PEN) == RCC_PLLCFGR_PLL1PEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1Q output.
  * @rmtoll
  *  PLLCFGR         PLL1QEN         LL_RCC_PLL1_EnableOutputQ
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutputQ(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1QEN);
}

/**
  * @brief  Disable PLL1Q output.
  * @rmtoll
  *  PLLCFGR         PLL1QEN         LL_RCC_PLL1_DisableOutputQ
  * @note   Cannot be disabled if the PLL1Q clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutputQ(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1QEN);
}

/**
  * @brief  Check if PLL1Q output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL1QEN         LL_RCC_PLL1_IsEnabledOutputQ
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledOutputQ(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1QEN) == RCC_PLLCFGR_PLL1QEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1S output.
  * @rmtoll
  *  PLLCFGR         PLL1SEN         LL_RCC_PLL1_EnableOutputS
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutputS(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SEN);
}

/**
  * @brief  Disable PLL1S output.
  * @rmtoll
  *  PLLCFGR         PLL1SEN         LL_RCC_PLL1_DisableOutputS
  * @note   Cannot be disabled if the PLL1S clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutputS(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SEN);
}

/**
  * @brief  Check if PLL1S output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL1SEN         LL_RCC_PLL1_IsEnabledOutputS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledOutputS(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SEN) == RCC_PLLCFGR_PLL1SEN) ? 1UL : 0UL);
}
/**
  * @brief  Enable 1 or several PLL1 outputs.
  * @rmtoll
  *  PLLCFGR         PLL1PEN         LL_RCC_PLL1_EnableOutput \n
  *  PLLCFGR         PLL1QEN         LL_RCC_PLL1_EnableOutput \n
  *  PLLCFGR         PLL1SEN         LL_RCC_PLL1_EnableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_S
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutput(uint32_t outputs)
{
  STM32_SET_BIT(RCC->PLLCFGR, outputs);
}

/**
  * @brief  Disable 1 or several PLL1 outputs.
  * @rmtoll
  *  PLLCFGR         PLL1PEN         LL_RCC_PLL1_DisableOutput \n
  *  PLLCFGR         PLL1QEN         LL_RCC_PLL1_DisableOutput \n
  *  PLLCFGR         PLL1SEN         LL_RCC_PLL1_DisableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_S
  * @note   Cannot be disabled if the PLL1 P output is used as the system clock.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutput(uint32_t outputs)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, outputs);
}

/**
  * @brief Get the list of the outputs activated for PLL1.
  * @rmtoll
  *  PLLCFGR         PLL1PEN         LL_RCC_PLL1_GetOutput \n
  *  PLLCFGR         PLL1QEN         LL_RCC_PLL1_GetOutput \n
  *  PLLCFGR         PLL1SEN         LL_RCC_PLL1_GetOutput
  * @retval  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_S
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetOutput(void)
{
  return STM32_READ_BIT(RCC->PLLCFGR, (LL_RCC_PLL1_OUTPUT_P | LL_RCC_PLL1_OUTPUT_Q | LL_RCC_PLL1_OUTPUT_S));
}

/**
  * @brief  Check if 1 or several PLL1 outputs are enabled.
  * @rmtoll
  *  PLLCFGR         PLL1PEN         LL_RCC_PLL1_IsOutputEnabled \n
  *  PLLCFGR         PLL1QEN         LL_RCC_PLL1_IsOutputEnabled \n
  *  PLLCFGR         PLL1SEN         LL_RCC_PLL1_IsOutputEnabled
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_S
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsOutputEnabled(uint32_t outputs)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, outputs) == (outputs)) ? 1UL : 0UL);
}

/**
  * @brief  Set Main PLL1 multiplication factor for VCO.
  * @rmtoll
  *  PLL1DIVR1         DIVN         LL_RCC_PLL1_SetN
  * @param  divn parameter can be a value between 8 and 420
  */
__STATIC_INLINE void LL_RCC_PLL1_SetN(uint32_t divn)
{
  STM32_MODIFY_REG(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVN, (divn - 1UL) << RCC_PLL1DIVR1_DIVN_Pos);
}

/**
  * @brief  Get Main PLL1 multiplication factor for VCO.
  * @rmtoll
  *  PLL1DIVR1         DIVN         LL_RCC_PLL1_GetN
  * @retval Between 8 and 420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetN(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVN) >>  RCC_PLL1DIVR1_DIVN_Pos) + 1UL);
}

/**
  * @brief  Set Main division factor for PLL1.
  * @rmtoll
  *  PLLCKSELR         DIVM1         LL_RCC_PLL1_SetM
  * @param  divm1 parameter can be a value between 0 and 63. 0 disables the prescaler
  */
__STATIC_INLINE void LL_RCC_PLL1_SetM(uint32_t divm1)
{
  STM32_MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM1, (divm1) << RCC_PLLCKSELR_DIVM1_Pos);
}

/**
  * @brief  Get Main division factor for PLL1.
  * @rmtoll
  *  PLLCKSELR         DIVM1         LL_RCC_PLL1_GetM
  * @retval Between 0 and 63
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetM(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM1) >>  RCC_PLLCKSELR_DIVM1_Pos));
}

/**
  * @brief  Set Division factor for PLL1P.
  * @rmtoll
  *  PLL1DIVR1         DIVP         LL_RCC_PLL1_SetP
  * @param  pll1p parameter can be a value between 1 and 128 (Only division by 1 and even division are allowed)
  * @note Used for System clock
  */
__STATIC_INLINE void LL_RCC_PLL1_SetP(uint32_t pll1p)
{
  STM32_MODIFY_REG(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVP, (pll1p - 1UL) << RCC_PLL1DIVR1_DIVP_Pos);
}

/**
  * @brief  Get Division factor for PLL1P.
  * @rmtoll
  *  PLL1DIVR1         DIVP         LL_RCC_PLL1_GetP
  * @note Used for System clock
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetP(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVP) >>  RCC_PLL1DIVR1_DIVP_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL1Q.
  * @rmtoll
  *  PLL1DIVR1         DIVQ         LL_RCC_PLL1_SetQ
  * @param  pll1q parameter can be a value between 1 and 128
  * @note   Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL1_SetQ(uint32_t pll1q)
{
  STM32_MODIFY_REG(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVQ, (pll1q - 1UL) << RCC_PLL1DIVR1_DIVQ_Pos);
}

/**
  * @brief  Get Division factor for PLL1Q.
  * @rmtoll
  *  PLL1DIVR1         DIVQ         LL_RCC_PLL1_GetQ
  * @note   Used for peripherals clocks
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetQ(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL1DIVR1, RCC_PLL1DIVR1_DIVQ) >>  RCC_PLL1DIVR1_DIVQ_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL1S.
  * @rmtoll
  *  PLL1DIVR2         DIVS         LL_RCC_PLL1_SetS
  * @param  pll1s parameter can be a value between 1 and 8
  * @note   Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL1_SetS(uint32_t pll1s)
{
  STM32_MODIFY_REG(RCC->PLL1DIVR2, RCC_PLL1DIVR2_DIVS, (pll1s - 1UL) << RCC_PLL1DIVR2_DIVS_Pos);
}

/**
  * @brief  Get Division factor for PLL1S.
  * @rmtoll
  *  PLL1DIVR2         DIVS         LL_RCC_PLL1_GetS
  * @note   Used for peripherals clocks
  * @retval Between 1 and 8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetS(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL1DIVR2, RCC_PLL1DIVR2_DIVS) >>  RCC_PLL1DIVR2_DIVS_Pos) + 1UL);
}

/**
  * @brief  Enable PLL1 FRACN.
  * @rmtoll
  *  PLLCFGR         PLL1FRACEN         LL_RCC_PLL1_EnableFRACN
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableFRACN(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN);
}

/**
  * @brief  Disable PLL1 FRACN.
  * @rmtoll
  *  PLLCFGR         PLL1FRACEN         LL_RCC_PLL1_DisableFRACN
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableFRACN(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN);
}

/**
  * @brief  Check if PLL1 FRACN is enabled.
  * @rmtoll
  *  PLLCFGR         PLL1FRACEN         LL_RCC_PLL1_IsEnabledFRACN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledFRACN(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN) == RCC_PLLCFGR_PLL1FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL1 FRACN Coefficient.
  * @rmtoll PLL1FRACR         FRACN         LL_RCC_PLL1_SetFRACN
  * @param  fracn parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL1_SetFRACN(uint32_t fracn)
{
  STM32_MODIFY_REG(RCC->PLL1FRACR, RCC_PLL1FRACR_FRACN, fracn << RCC_PLL1FRACR_FRACN_Pos);
}

/**
  * @brief  Get PLL1 FRACN Coefficient.
  * @rmtoll
  *  PLL1FRACR         FRACN         LL_RCC_PLL1_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetFRACN(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL1FRACR, RCC_PLL1FRACR_FRACN) >>  RCC_PLL1FRACR_FRACN_Pos);
}

/**
  * @brief  Set PLL1 VCO Output Range.
  * @rmtoll
  *  PLLCFGR         PLL1VCOSEL         LL_RCC_PLL1_SetVCORange
  * @param  input_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1VCORANGE_384_1672
  *         @arg @ref LL_RCC_PLL1VCORANGE_150_420
  * @note   This API must be called only when PLL1 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_SetVCORange(uint32_t output_range)
{
  STM32_MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL1VCOSEL, output_range);
}

/**
  * @brief  Get PLL1 VCO Output Range.
  * @rmtoll
  *  PLLCFGR         PLL1VCOSEL         LL_RCC_PLL1_GetVCORange
  * @retval  The VCO range. This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1VCORANGE_384_1672
  *         @arg @ref LL_RCC_PLL1VCORANGE_150_420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetVCORange(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1VCOSEL));
}

/**
  * @brief  Set PLL1 VCO Input Range.
  * @rmtoll
  *  PLLCFGR         PLL1RGE         LL_RCC_PLL1_SetInputRange
  * @param  input_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1INPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLL1INPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLL1INPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLL1INPUTRANGE_8_16
  * @note   This API must be called only when PLL1 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_SetInputRange(uint32_t input_range)
{
  STM32_MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL1RGE, input_range);
}

/**
  * @brief  Get PLL1 VCO Input Range.
  * @rmtoll
  *  PLLCFGR         PLL1RGE         LL_RCC_PLL1_GetInputRange
  * @retval  The VCO range. This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1INPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLL1INPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLL1INPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLL1INPUTRANGE_8_16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetInputRange(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1RGE));
}

/**
  * @brief  Enable PLL1 Spread-spectrum clock generator (SSCG).
  * @rmtoll
  *  PLLCFGR         PLL1SSCGEN         LL_RCC_PLL1_EnableSSCG
  * @note   This API must be called only when PLL1 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableSSCG(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SSCGEN);
}

/**
  * @brief  Disable PLL1 Spread-spectrum clock generator (SSCG).
  * @rmtoll
  *  PLLCFGR         PLL1SSCGEN         LL_RCC_PLL1_DisableSSCG
  * @note   This API must be called only when PLL1 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableSSCG(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SSCGEN);
}

/**
  * @brief  Check if PLL1 Spread-spectrum clock generator (SSCG) is enabled.
  * @rmtoll
  *  PLLCFGR         PLL1SSCGEN         LL_RCC_PLL1_IsEnabledSSCG
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledSSCG(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1SSCGEN) == RCC_PLLCFGR_PLL1SSCGEN) ? 1UL : 0UL);
}

/**
  * @brief  Set Spread-spectrum Modulation Period for PLL1.
  * @rmtoll
  *  PLL1SSCGR         MODPER         LL_RCC_PLL1_SetSSCGModulationPeriod
  * @param  period This parameter can be between Min_Data=0 and Max_Data=8191
  */
__STATIC_INLINE void LL_RCC_PLL1_SetSSCGModulationPeriod(uint32_t period)
{
  STM32_MODIFY_REG(RCC->PLL1SSCGR, RCC_PLL1SSCGR_MODPER, period);
}

/**
  * @brief  Get Spread-spectrum Modulation Period for PLL1.
  * @rmtoll
  *  PLL1SSCGR         MODPER         LL_RCC_PLL1_GetSSCGModulationPeriod
  * @retval Between Min_Data=0 and Max_Data=8191
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetSSCGModulationPeriod(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_MODPER));
}

/**
  * @brief  Set Spread Spectrum Increment Step for PLL1.
  * @rmtoll
  *  PLL1SSCGR         INCSTEP         LL_RCC_PLL1_SetSSCGIncrementStep
  * @param  step This parameter can be between Min_Data=0 and Max_Data=32767
  */
__STATIC_INLINE void LL_RCC_PLL1_SetSSCGIncrementStep(uint32_t step)
{
  STM32_MODIFY_REG(RCC->PLL1SSCGR, RCC_PLL1SSCGR_INCSTEP, step << RCC_PLL1SSCGR_INCSTEP_Pos);
}

/**
  * @brief  Get Spread Spectrum Increment Step for PLL1.
  * @rmtoll
  *  PLL1SSCGR         INCSTEP         LL_RCC_PLL1_GetSSCGIncrementStep
  * @retval Between Min_Data=0 and Max_Data=32767
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetSSCGIncrementStep(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_INCSTEP) >> RCC_PLL1SSCGR_INCSTEP_Pos);
}

/**
  * @brief  Set Spread Spectrum Modulation Selection for PLL1.
  * @rmtoll
  *  PLL1SSCGR         SPREADSEL         LL_RCC_PLL1_SetSSCGSpreadSelection
  * @param  spread_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  */
__STATIC_INLINE void LL_RCC_PLL1_SetSSCGSpreadSelection(uint32_t spread_mode)
{
  STM32_MODIFY_REG(RCC->PLL1SSCGR, RCC_PLL1SSCGR_SPREADSEL, spread_mode);
}

/**
  * @brief  Get Spread Spectrum Selection for PLL1.
  * @rmtoll
  *  PLL1SSCGR         SPREADSEL         LL_RCC_PLL1_GetSSCGSpreadSelection
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetSSCGSpreadSelection(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_SPREADSEL));
}

/**
  * @brief  Enable Dithering RPDF Noise for PLL1.
  * @rmtoll
  *  PLL1SSCGR         RPDFNDIS         LL_RCC_PLL1_EnableSSCGRPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableSSCGRPDFNDithering(void)
{
  STM32_CLEAR_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_RPDFNDIS);
}

/**
  * @brief  Disable Dithering RPDF Noise for PLL1.
  * @rmtoll
  *  PLL1SSCGR         RPDFNDIS         LL_RCC_PLL1_DisableSSCGRPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableSSCGRPDFNDithering(void)
{
  STM32_SET_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_RPDFNDIS);
}

/**
  * @brief  Check if Dithering RPDF Noise for PLL1 is enabled.
  * @rmtoll
  *  PLL1SSCGR         RPDFNDIS         LL_RCC_PLL1_IsEnabledSSCGRPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledSSCGRPDFNDithering(void)
{
  return ((STM32_READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_RPDFNDIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Enable Dithering TPDF Noise for PLL1.
  * @rmtoll
  *  PLL1SSCGR         TPDFNDIS         LL_RCC_PLL1_EnableSSCGTPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableSSCGTPDFNDithering(void)
{
  STM32_CLEAR_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_TPDFNDIS);
}

/**
  * @brief  Disable Dithering TPDF Noise for PLL1.
  * @rmtoll
  *  PLL1SSCGR         TPDFNDIS         LL_RCC_PLL1_DisableSSCGTPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableSSCGTPDFNDithering(void)
{
  STM32_SET_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_TPDFNDIS);
}

/**
  * @brief  Check if Dithering TPDF Noise for PLL1 is enabled.
  * @rmtoll
  *  PLL1SSCGR         TPDFNDIS         LL_RCC_PLL1_IsEnabledSSCGTPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledSSCGTPDFNDithering(void)
{
  return ((STM32_READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_TPDFNDIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL1 Spread-Spectrum Modulation (SSCG) in a single atomic register write.
  * @rmtoll
  *  PLL1SSCGR   MODPER      LL_RCC_PLL1_ConfigSSCG \n
  *  PLL1SSCGR   INCSTEP     LL_RCC_PLL1_ConfigSSCG \n
  *  PLL1SSCGR   SPREADSEL   LL_RCC_PLL1_ConfigSSCG \n
  *  PLL1SSCGR   RPDFNDIS    LL_RCC_PLL1_ConfigSSCG \n
  *  PLL1SSCGR   TPDFNDIS    LL_RCC_PLL1_ConfigSSCG
  * @param mod_period   Modulation period, value between 0 and 0x1FFF
  * @param inc_step     Modulation depth increment step, value between 0 and 0x7FFF
  * @param spread_mode  This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  * @param dith_control This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_NO
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_TPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF_TPDF
  */
__STATIC_INLINE void LL_RCC_PLL1_ConfigSSCG(uint32_t mod_period, uint32_t inc_step, uint32_t spread_mode,
                                            uint32_t dith_control)
{
  STM32_MODIFY_REG(RCC->PLL1SSCGR,
                   RCC_PLL1SSCGR_MODPER | RCC_PLL1SSCGR_INCSTEP | RCC_PLL1SSCGR_SPREADSEL |
                   RCC_PLL1SSCGR_RPDFNDIS | RCC_PLL1SSCGR_TPDFNDIS,
                   ((mod_period << RCC_PLL1SSCGR_MODPER_Pos) & RCC_PLL1SSCGR_MODPER) |
                   ((inc_step << RCC_PLL1SSCGR_INCSTEP_Pos) & RCC_PLL1SSCGR_INCSTEP) |
                   spread_mode | dith_control);
}

/**
  * @brief  Get PLL1 SSCG dithering control.
  * @rmtoll
  *  PLL1SSCGR   RPDFNDIS      LL_RCC_PLL1_GetSSCGDithering \n
  *  PLL1SSCGR   TPDFNDIS      LL_RCC_PLL1_GetSSCGDithering
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_NO
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_TPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF_TPDF
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetSSCGDithering(void)
{
  return (uint32_t)STM32_READ_BIT(RCC->PLL1SSCGR, RCC_PLL1SSCGR_RPDFNDIS | RCC_PLL1SSCGR_TPDFNDIS);
}

/**
  * @}
  */

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
  * @brief  Enable PLL2P output.
  * @rmtoll
  *  PLLCFGR         PLL2PEN         LL_RCC_PLL2_EnableOutputP
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutputP(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2PEN);
}

/**
  * @brief  Disable PLL2P output.
  * @rmtoll
  *  PLLCFGR         PLL2PEN         LL_RCC_PLL2_DisableOutputP
  * @note   Cannot be disabled if the PLL2P clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutputP(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2PEN);
}

/**
  * @brief  Check if PLL2P output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL2PEN         LL_RCC_PLL2_IsEnabledOutputP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledOutputP(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2PEN) == RCC_PLLCFGR_PLL2PEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2Q output.
  * @rmtoll
  *  PLLCFGR         PLL2QEN         LL_RCC_PLL2_EnableOutputQ
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutputQ(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2QEN);
}

/**
  * @brief  Disable PLL2Q output.
  * @rmtoll
  *  PLLCFGR         PLL2QEN         LL_RCC_PLL2_DisableOutputQ
  * @note   Cannot be disabled if the PLL2Q clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutputQ(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2QEN);
}

/**
  * @brief  Check if PLL2Q output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL2QEN         LL_RCC_PLL2_IsEnabledOutputQ
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledOutputQ(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2QEN) == RCC_PLLCFGR_PLL2QEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2R output.
  * @rmtoll
  *  PLLCFGR         PLL2REN         LL_RCC_PLL2_EnableOutputR
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutputR(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2REN);
}

/**
  * @brief  Disable PLL2R output.
  * @rmtoll
  *  PLLCFGR         PLL2REN         LL_RCC_PLL2_DisableOutputR
  * @note   Cannot be disabled if the PLL2R clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutputR(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2REN);
}

/**
  * @brief  Check if PLL2R output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL2REN         LL_RCC_PLL2_IsEnabledOutputR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledOutputR(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2REN) == RCC_PLLCFGR_PLL2REN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2S output.
  * @rmtoll
  *  PLLCFGR         PLL2SEN         LL_RCC_PLL2_EnableOutputS
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutputS(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SEN);
}

/**
  * @brief  Disable PLL2S output.
  * @rmtoll
  *  PLLCFGR         PLL2SEN         LL_RCC_PLL2_DisableOutputS
  * @note   Cannot be disabled if the PLL2S clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutputS(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SEN);
}

/**
  * @brief  Check if PLL2S output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL2SEN         LL_RCC_PLL2_IsEnabledOutputS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledOutputS(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SEN) == RCC_PLLCFGR_PLL2SEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2T output.
  * @rmtoll
  *  PLLCFGR         PLL2TEN         LL_RCC_PLL2_EnableOutputT
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutputT(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2TEN);
}

/**
  * @brief  Disable PLL2T output.
  * @rmtoll
  *  PLLCFGR         PLL2TEN         LL_RCC_PLL2_DisableOutputT
  * @note   Cannot be disabled if the PLL2T clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutputT(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2TEN);
}

/**
  * @brief  Check if PLL2T output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL2TEN         LL_RCC_PLL2_IsEnabledOutputT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledOutputT(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2TEN) == RCC_PLLCFGR_PLL2TEN) ? 1UL : 0UL);
}
/**
  * @brief  Enable 1 or several PLL2 outputs.
  * @rmtoll
  *  PLLCFGR         PLL2PEN         LL_RCC_PLL2_EnableOutput \n
  *  PLLCFGR         PLL2QEN         LL_RCC_PLL2_EnableOutput \n
  *  PLLCFGR         PLL2REN         LL_RCC_PLL2_EnableOutput \n
  *  PLLCFGR         PLL2SEN         LL_RCC_PLL2_EnableOutput \n
  *  PLLCFGR         PLL2TEN         LL_RCC_PLL2_EnableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  *         @arg @ref LL_RCC_PLL2_OUTPUT_S
  *         @arg @ref LL_RCC_PLL2_OUTPUT_T
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutput(uint32_t outputs)
{
  STM32_SET_BIT(RCC->PLLCFGR, outputs);
}

/**
  * @brief  Disable 1 or several PLL2 outputs.
  * @rmtoll
  *  PLLCFGR         PLL2PEN         LL_RCC_PLL2_DisableOutput \n
  *  PLLCFGR         PLL2QEN         LL_RCC_PLL2_DisableOutput \n
  *  PLLCFGR         PLL2REN         LL_RCC_PLL2_DisableOutput \n
  *  PLLCFGR         PLL2SEN         LL_RCC_PLL2_DisableOutput \n
  *  PLLCFGR         PLL2TEN         LL_RCC_PLL2_DisableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  *         @arg @ref LL_RCC_PLL2_OUTPUT_S
  *         @arg @ref LL_RCC_PLL2_OUTPUT_T
  * @note   Cannot be disabled if the PLL2XXX output is used as the system clock.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutput(uint32_t outputs)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, outputs);
}

/**
  * @brief Get the list of the outputs activated for PLL2.
  * @rmtoll
  *  PLLCFGR         PLL2PEN         LL_RCC_PLL2_GetOutput \n
  *  PLLCFGR         PLL2QEN         LL_RCC_PLL2_GetOutput \n
  *  PLLCFGR         PLL2REN         LL_RCC_PLL2_GetOutput \n
  *  PLLCFGR         PLL2SEN         LL_RCC_PLL2_GetOutput \n
  *  PLLCFGR         PLL2TEN         LL_RCC_PLL2_GetOutput
  * @retval  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  *         @arg @ref LL_RCC_PLL2_OUTPUT_S
  *         @arg @ref LL_RCC_PLL2_OUTPUT_T
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetOutput(void)
{
  return STM32_READ_BIT(RCC->PLLCFGR, (LL_RCC_PLL2_OUTPUT_P | LL_RCC_PLL2_OUTPUT_Q | LL_RCC_PLL2_OUTPUT_R | \
                                       LL_RCC_PLL2_OUTPUT_S | LL_RCC_PLL2_OUTPUT_T));
}

/**
  * @brief  Check if 1 or several PLL2 outputs are enabled.
  * @rmtoll
  *  PLLCFGR         PLL2PEN         LL_RCC_PLL2_IsOutputEnabled \n
  *  PLLCFGR         PLL2QEN         LL_RCC_PLL2_IsOutputEnabled \n
  *  PLLCFGR         PLL2REN         LL_RCC_PLL2_IsOutputEnabled \n
  *  PLLCFGR         PLL2SEN         LL_RCC_PLL2_IsOutputEnabled \n
  *  PLLCFGR         PLL2TEN         LL_RCC_PLL2_IsOutputEnabled
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  *         @arg @ref LL_RCC_PLL2_OUTPUT_S
  *         @arg @ref LL_RCC_PLL2_OUTPUT_T
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsOutputEnabled(uint32_t outputs)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, outputs) == (outputs)) ? 1UL : 0UL);
}

/**
  * @brief  Set Main PLL2 multiplication factor for VCO.
  * @rmtoll
  *  PLL2DIVR1         DIVN         LL_RCC_PLL2_SetN
  * @param  pll2n parameter can be a value between 8 and 420
  */
__STATIC_INLINE void LL_RCC_PLL2_SetN(uint32_t pll2n)
{
  STM32_MODIFY_REG(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVN, (pll2n - 1UL) << RCC_PLL2DIVR1_DIVN_Pos);
}

/**
  * @brief  Get Main PLL2 multiplication factor for VCO.
  * @rmtoll
  *  PLL2DIVR1         DIVN         LL_RCC_PLL2_GetN
  * @retval Between 8 and 420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetN(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVN) >>  RCC_PLL2DIVR1_DIVN_Pos) + 1UL);
}

/**
  * @brief  Set Main division factor for PLL2M.
  * @rmtoll
  *  PLLCKSELR         DIVM2         LL_RCC_PLL2_SetM
  * @param  pll2m parameter can be a value between 0 and 63. 0 disables the prescaler
  */
__STATIC_INLINE void LL_RCC_PLL2_SetM(uint32_t pll2m)
{
  STM32_MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM2, (pll2m) << RCC_PLLCKSELR_DIVM2_Pos);
}

/**
  * @brief  Get Main division factor for PLL2.
  * @rmtoll
  *  PLLCKSELR         DIVM2         LL_RCC_PLL2_GetM
  * @retval Between 0 and 63
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetM(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM2) >>  RCC_PLLCKSELR_DIVM2_Pos));
}

/**
  * @brief  Set Division factor for PLL2P.
  * @rmtoll
  *  PLL2DIVR1         DIVP         LL_RCC_PLL2_SetP
  * @param  pll2p parameter can be a value between 1 and 128
  * @note Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL2_SetP(uint32_t pll2p)
{
  STM32_MODIFY_REG(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVP, (pll2p - 1UL) << RCC_PLL2DIVR1_DIVP_Pos);
}

/**
  * @brief  Get Division factor for PLL2P.
  * @rmtoll
  *  PLL2DIVR1         DIVP         LL_RCC_PLL2_GetP
  * @note Used for peripherals clocks
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetP(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVP) >>  RCC_PLL2DIVR1_DIVP_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL2Q.
  * @rmtoll
  *  PLL2DIVR1         DIVQ         LL_RCC_PLL2_SetQ
  * @param  pll2q parameter can be a value between 1 and 128
  * @note Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL2_SetQ(uint32_t pll2q)
{
  STM32_MODIFY_REG(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVQ, (pll2q - 1UL) << RCC_PLL2DIVR1_DIVQ_Pos);
}

/**
  * @brief  Get Division factor for PLL2Q.
  * @rmtoll
  *  PLL2DIVR1         DIVQ         LL_RCC_PLL2_GetQ
  * @note Used for peripherals clocks
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetQ(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVQ) >>  RCC_PLL2DIVR1_DIVQ_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL2R.
  * @rmtoll
  *  PLL2DIVR1         DIVR         LL_RCC_PLL2_SetR
  * @param  pll2r parameter can be a value between 1 and 128
  * @note   Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL2_SetR(uint32_t pll2r)
{
  STM32_MODIFY_REG(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVR, (pll2r - 1UL) << RCC_PLL2DIVR1_DIVR_Pos);
}

/**
  * @brief  Get Division factor for PLL2R.
  * @rmtoll
  *  PLL2DIVR1         DIVR         LL_RCC_PLL2_GetR
  * @note   Used for peripherals clocks
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetR(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2DIVR1, RCC_PLL2DIVR1_DIVR) >>  RCC_PLL2DIVR1_DIVR_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL2S.
  * @rmtoll
  *  PLL2DIVR2         DIVS         LL_RCC_PLL2_SetS
  * @param  pll2s parameter can be a value between 1 and 8
  * @note   Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL2_SetS(uint32_t pll2s)
{
  STM32_MODIFY_REG(RCC->PLL2DIVR2, RCC_PLL2DIVR2_DIVS, (pll2s - 1UL) << RCC_PLL2DIVR2_DIVS_Pos);
}

/**
  * @brief  Get Division factor for PLL2S.
  * @rmtoll
  *  PLL2DIVR2         DIVS         LL_RCC_PLL2_GetS
  * @note   Used for peripherals clocks
  * @retval Between 1 and 8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetS(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2DIVR2, RCC_PLL2DIVR2_DIVS) >>  RCC_PLL2DIVR2_DIVS_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL2T.
  * @rmtoll
  *  PLL2DIVR2         DIVT         LL_RCC_PLL2_SetT
  * @param  pll2t parameter can be a value between 1 and 8
  * @note   Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL2_SetT(uint32_t pll2t)
{
  STM32_MODIFY_REG(RCC->PLL2DIVR2, RCC_PLL2DIVR2_DIVT, (pll2t - 1UL) << RCC_PLL2DIVR2_DIVT_Pos);
}

/**
  * @brief  Get Division factor for PLL2T.
  * @rmtoll
  *  PLL2DIVR2         DIVT         LL_RCC_PLL2_GetT
  * @note Used for peripherals clocks
  * @retval Between 1 and 8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetT(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL2DIVR2, RCC_PLL2DIVR2_DIVT) >>  RCC_PLL2DIVR2_DIVT_Pos) + 1UL);
}

/**
  * @brief  Enable PLL2 FRACN.
  * @rmtoll
  *  PLLCFGR         PLL2FRACLEN         LL_RCC_PLL2_EnableFRACN
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableFRACN(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACLEN);
}

/**
  * @brief  Disable PLL2 FRACN.
  * @rmtoll
  *  PLLCFGR         PLL2FRACLEN         LL_RCC_PLL2_DisableFRACN
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableFRACN(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACLEN);
}

/**
  * @brief  Check if PLL2 FRACN is enabled.
  * @rmtoll
  *  PLLCFGR         PLL2FRACLEN         LL_RCC_PLL2_IsEnabledFRACN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledFRACN(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACLEN) == RCC_PLLCFGR_PLL2FRACLEN) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL2 FRACN Coefficient.
  * @rmtoll
  *  PLL2FRACR         FRACN         LL_RCC_PLL2_SetFRACN
  * @param  fracn parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL2_SetFRACN(uint32_t fracn)
{
  STM32_MODIFY_REG(RCC->PLL2FRACR, RCC_PLL2FRACR_FRACN, fracn << RCC_PLL2FRACR_FRACN_Pos);
}

/**
  * @brief  Get PLL2 FRACN Coefficient.
  * @rmtoll
  *  PLL2FRACR         FRACN         LL_RCC_PLL2_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetFRACN(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL2FRACR, RCC_PLL2FRACR_FRACN) >>  RCC_PLL2FRACR_FRACN_Pos);
}

/**
  * @brief  Set PLL2 VCO Output Range.
  * @rmtoll
  *  PLLCFGR         PLL2VCOSEL         LL_RCC_PLL2_SetVCORange
  * @param  output_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2VCORANGE_384_1672
  *         @arg @ref LL_RCC_PLL2VCORANGE_150_420
  * @note   This API must be called only when PLL2 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL2_SetVCORange(uint32_t output_range)
{
  STM32_MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL2VCOSEL, output_range);
}

/**
  * @brief  Get PLL2 VCO Output Range.
  * @rmtoll
  *  PLLCFGR         PLL2VCOSEL         LL_RCC_PLL2_GetVCORange
  * @retval  The VCO range. This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2VCORANGE_384_1672
  *         @arg @ref LL_RCC_PLL2VCORANGE_150_420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetVCORange(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2VCOSEL));
}

/**
  * @brief  Set PLL2 VCO Input Range.
  * @rmtoll
  *  PLLCFGR         PLL2RGE         LL_RCC_PLL2_SetInputRange
  * @param  input_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2INPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLL2INPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLL2INPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLL2INPUTRANGE_8_16
  * @note   This API must be called only when PLL2 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL2_SetInputRange(uint32_t input_range)
{
  STM32_MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL2RGE, input_range);
}

/**
  * @brief  Get PLL2 VCO Input Range.
  * @rmtoll
  *  PLLCFGR         PLL2RGE         LL_RCC_PLL2_GetInputRange
  * @retval  The VCO range. This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2INPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLL2INPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLL2INPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLL2INPUTRANGE_8_16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetInputRange(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2RGE));
}

/**
  * @brief  Enable PLL2 Spread-spectrum clock generator (SSCG).
  * @rmtoll
  *  PLLCFGR         PLL2SSCGEN         LL_RCC_PLL2_EnableSSCG
  * @note   This API must be called only when PLL2 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableSSCG(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SSCGEN);
}

/**
  * @brief  Disable PLL2 Spread-spectrum clock generator (SSCG).
  * @rmtoll
  *  PLLCFGR         PLL2SSCGEN         LL_RCC_PLL2_DisableSSCG
  * @note   This API must be called only when PLL2 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableSSCG(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SSCGEN);
}

/**
  * @brief  Check if PLL2 Spread-spectrum clock generator (SSCG) is enabled.
  * @rmtoll
  *  PLLCFGR         PLL2SSCGEN         LL_RCC_PLL2_IsEnabledSSCG
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledSSCG(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2SSCGEN) == RCC_PLLCFGR_PLL2SSCGEN) ? 1UL : 0UL);
}

/**
  * @brief  Set Spread-spectrum Modulation Period for PLL2.
  * @rmtoll
  *  PLL2SSCGR         MODPER         LL_RCC_PLL2_SetSSCGModulationPeriod
  * @param  period This parameter can be between Min_Data=0 and Max_Data=8191
  */
__STATIC_INLINE void LL_RCC_PLL2_SetSSCGModulationPeriod(uint32_t period)
{
  STM32_MODIFY_REG(RCC->PLL2SSCGR, RCC_PLL2SSCGR_MODPER, period);
}

/**
  * @brief  Get Spread-spectrum Modulation Period for PLL2.
  * @rmtoll
  *  PLL2SSCGR         MODPER         LL_RCC_PLL2_GetSSCGModulationPeriod
  * @retval Between Min_Data=0 and Max_Data=8191
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetSSCGModulationPeriod(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_MODPER));
}

/**
  * @brief  Set Spread Spectrum Increment Step for PLL2.
  * @rmtoll
  *  PLL2SSCGR         INCSTEP         LL_RCC_PLL2_SetSSCGIncrementStep
  * @param  step This parameter can be between Min_Data=0 and Max_Data=32767
  */
__STATIC_INLINE void LL_RCC_PLL2_SetSSCGIncrementStep(uint32_t step)
{
  STM32_MODIFY_REG(RCC->PLL2SSCGR, RCC_PLL2SSCGR_INCSTEP, step << RCC_PLL2SSCGR_INCSTEP_Pos);
}

/**
  * @brief  Get Spread Spectrum Increment Step for PLL2.
  * @rmtoll
  *  PLL2SSCGR         INCSTEP         LL_RCC_PLL2_GetSSCGIncrementStep
  * @retval Between Min_Data=0 and Max_Data=32767
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetSSCGIncrementStep(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_INCSTEP) >> RCC_PLL2SSCGR_INCSTEP_Pos);
}

/**
  * @brief  Set Spread Spectrum Modulation Selection for PLL2.
  * @rmtoll
  *  PLL2SSCGR         SPREADSEL         LL_RCC_PLL2_SetSSCGSpreadSelection
  * @param  spread_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  */
__STATIC_INLINE void LL_RCC_PLL2_SetSSCGSpreadSelection(uint32_t spread_mode)
{
  STM32_MODIFY_REG(RCC->PLL2SSCGR, RCC_PLL2SSCGR_SPREADSEL, spread_mode);
}

/**
  * @brief  Get Spread Spectrum Selection for PLL2.
  * @rmtoll
  *  PLL2SSCGR         SPREADSEL         LL_RCC_PLL2_GetSSCGSpreadSelection
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetSSCGSpreadSelection(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_SPREADSEL));
}

/**
  * @brief  Enable Dithering RPDF Noise for PLL2.
  * @rmtoll
  *  PLL2SSCGR         RPDFNDIS         LL_RCC_PLL2_EnableSSCGRPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableSSCGRPDFNDithering(void)
{
  STM32_CLEAR_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_RPDFNDIS);
}

/**
  * @brief  Disable Dithering RPDF Noise for PLL2.
  * @rmtoll
  *  PLL2SSCGR         RPDFNDIS         LL_RCC_PLL2_DisableSSCGRPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableSSCGRPDFNDithering(void)
{
  STM32_SET_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_RPDFNDIS);
}

/**
  * @brief  Check if Dithering RPDF Noise for PLL2 is enabled.
  * @rmtoll
  *  PLL2SSCGR         RPDFNDIS         LL_RCC_PLL2_IsEnabledSSCGRPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledSSCGRPDFNDithering(void)
{
  return ((STM32_READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_RPDFNDIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Enable Dithering TPDF Noise for PLL2.
  * @rmtoll
  *  PLL2SSCGR         TPDFNDIS         LL_RCC_PLL2_EnableSSCGTPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableSSCGTPDFNDithering(void)
{
  STM32_CLEAR_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_TPDFNDIS);
}

/**
  * @brief  Disable Dithering TPDF Noise for PLL2.
  * @rmtoll
  *  PLL2SSCGR         TPDFNDIS         LL_RCC_PLL2_DisableSSCGTPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableSSCGTPDFNDithering(void)
{
  STM32_SET_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_TPDFNDIS);
}

/**
  * @brief  Check if Dithering TPDF Noise for PLL2 is enabled.
  * @rmtoll
  *  PLL2SSCGR         TPDFNDIS         LL_RCC_PLL2_IsEnabledSSCGTPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledSSCGTPDFNDithering(void)
{
  return ((STM32_READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_TPDFNDIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL2 Spread-Spectrum Modulation (SSCG) in a single atomic register write.
  * @rmtoll
  *  PLL2SSCGR   MODPER      LL_RCC_PLL2_ConfigSSCG \n
  *  PLL2SSCGR   INCSTEP     LL_RCC_PLL2_ConfigSSCG \n
  *  PLL2SSCGR   SPREADSEL   LL_RCC_PLL2_ConfigSSCG \n
  *  PLL2SSCGR   RPDFNDIS    LL_RCC_PLL2_ConfigSSCG \n
  *  PLL2SSCGR   TPDFNDIS    LL_RCC_PLL2_ConfigSSCG
  * @param mod_period   Modulation period, value between 0 and 0x1FFF
  * @param inc_step     Modulation depth increment step, value between 0 and 0x7FFF
  * @param spread_mode  This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  * @param dith_control This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_NO
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_TPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF_TPDF
  */
__STATIC_INLINE void LL_RCC_PLL2_ConfigSSCG(uint32_t mod_period, uint32_t inc_step, uint32_t spread_mode,
                                            uint32_t dith_control)
{
  STM32_MODIFY_REG(RCC->PLL2SSCGR,
                   RCC_PLL2SSCGR_MODPER | RCC_PLL2SSCGR_INCSTEP | RCC_PLL2SSCGR_SPREADSEL |
                   RCC_PLL2SSCGR_RPDFNDIS | RCC_PLL2SSCGR_TPDFNDIS,
                   ((mod_period << RCC_PLL2SSCGR_MODPER_Pos) & RCC_PLL2SSCGR_MODPER) |
                   ((inc_step << RCC_PLL2SSCGR_INCSTEP_Pos) & RCC_PLL2SSCGR_INCSTEP) |
                   spread_mode | dith_control);
}

/**
  * @brief  Get PLL2 SSCG dithering control.
  * @rmtoll
  *  PLL2SSCGR   RPDFNDIS      LL_RCC_PLL2_GetSSCGDithering \n
  *  PLL2SSCGR   TPDFNDIS      LL_RCC_PLL2_GetSSCGDithering
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_NO
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_TPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF_TPDF
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetSSCGDithering(void)
{
  return (uint32_t)STM32_READ_BIT(RCC->PLL2SSCGR, RCC_PLL2SSCGR_RPDFNDIS | RCC_PLL2SSCGR_TPDFNDIS);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_PLL3 PLL3
  * @{
  */

/**
  * @brief  Enable PLL3.
  * @rmtoll
  *  CR         PLL3ON         LL_RCC_PLL3_Enable
  */
__STATIC_INLINE void LL_RCC_PLL3_Enable(void)
{
  STM32_SET_BIT(RCC->CR, RCC_CR_PLL3ON);
}

/**
  * @brief  Disable PLL3.
  * @rmtoll
  *  CR         PLL3ON         LL_RCC_PLL3_Disable
  * @note   Cannot be disabled if the PLL3 clock is used as the system clock.
  */
__STATIC_INLINE void LL_RCC_PLL3_Disable(void)
{
  STM32_CLEAR_BIT(RCC->CR, RCC_CR_PLL3ON);
}

/**
  * @brief  Check if PLL3 is ready.
  * @rmtoll
  *  CR         PLL3RDY         LL_RCC_PLL3_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsReady(void)
{
  return ((STM32_READ_BIT(RCC->CR, RCC_CR_PLL3RDY) == RCC_CR_PLL3RDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL3P output.
  * @rmtoll
  *  PLLCFGR         PLL3PEN         LL_RCC_PLL3_EnableOutputP
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableOutputP(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3PEN);
}

/**
  * @brief  Disable PLL3P output.
  * @rmtoll
  *  PLLCFGR         PLL3PEN         LL_RCC_PLL3_DisableOutputP
  * @note   Cannot be disabled if the PLL3P clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableOutputP(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3PEN);
}

/**
  * @brief  Check if PLL3P output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL3PEN         LL_RCC_PLL3_IsEnabledOutputP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledOutputP(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3PEN) == RCC_PLLCFGR_PLL3PEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL3Q output.
  * @rmtoll
  *  PLLCFGR         PLL3QEN         LL_RCC_PLL3_EnableOutputQ
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableOutputQ(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3QEN);
}

/**
  * @brief  Disable PLL3Q output.
  * @rmtoll
  *  PLLCFGR         PLL3QEN         LL_RCC_PLL3_DisableOutputQ
  * @note   Cannot be disabled if the PLL3Q clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableOutputQ(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3QEN);
}

/**
  * @brief  Check if PLL3Q output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL3QEN         LL_RCC_PLL3_IsEnabledOutputQ
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledOutputQ(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3QEN) == RCC_PLLCFGR_PLL3QEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL3R output.
  * @rmtoll
  *  PLLCFGR         PLL3REN         LL_RCC_PLL3_EnableOutputR
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableOutputR(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3REN);
}

/**
  * @brief  Disable PLL3R output.
  * @rmtoll
  *  PLLCFGR         PLL3REN         LL_RCC_PLL3_DisableOutputR
  * @note   Cannot be disabled if the PLL3R clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableOutputR(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3REN);
}

/**
  * @brief  Check if PLL3R output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL3REN         LL_RCC_PLL3_IsEnabledOutputR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledOutputR(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3REN) == RCC_PLLCFGR_PLL3REN) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL3S output.
  * @rmtoll
  *  PLLCFGR         PLL3SEN         LL_RCC_PLL3_EnableOutputS
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableOutputS(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SEN);
}

/**
  * @brief  Disable PLL3S output.
  * @rmtoll
  *  PLLCFGR         PLL3SEN         LL_RCC_PLL3_DisableOutputS
  * @note   Cannot be disabled if the PLL3S clock is used.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableOutputS(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SEN);
}

/**
  * @brief  Check if PLL3S output is enabled.
  * @rmtoll
  *  PLLCFGR         PLL3SEN         LL_RCC_PLL3_IsEnabledOutputS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledOutputS(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SEN) == RCC_PLLCFGR_PLL3SEN) ? 1UL : 0UL);
}
/**
  * @brief  Enable 1 or several PLL3 outputs.
  * @rmtoll
  *  PLLCFGR         PLL3PEN         LL_RCC_PLL3_EnableOutput \n
  *  PLLCFGR         PLL3QEN         LL_RCC_PLL3_EnableOutput \n
  *  PLLCFGR         PLL3REN         LL_RCC_PLL3_EnableOutput \n
  *  PLLCFGR         PLL3SEN         LL_RCC_PLL3_EnableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL3_OUTPUT_P
  *         @arg @ref LL_RCC_PLL3_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL3_OUTPUT_R
  *         @arg @ref LL_RCC_PLL3_OUTPUT_S
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableOutput(uint32_t outputs)
{
  STM32_SET_BIT(RCC->PLLCFGR, outputs);
}

/**
  * @brief  Disable 1 or several PLL3 outputs.
  * @rmtoll
  *  PLLCFGR         PLL3PEN         LL_RCC_PLL3_DisableOutput \n
  *  PLLCFGR         PLL3QEN         LL_RCC_PLL3_DisableOutput \n
  *  PLLCFGR         PLL3REN         LL_RCC_PLL3_DisableOutput \n
  *  PLLCFGR         PLL3SEN         LL_RCC_PLL3_DisableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL3_OUTPUT_P
  *         @arg @ref LL_RCC_PLL3_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL3_OUTPUT_R
  *         @arg @ref LL_RCC_PLL3_OUTPUT_S
  * @note   Cannot be disabled if the PLL3XXX output is used as the system clock.
  * @note   When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableOutput(uint32_t outputs)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, outputs);
}

/**
  * @brief Get the list of the outputs activated for PLL3.
  * @rmtoll
  *  PLLCFGR         PLL3PEN         LL_RCC_PLL3_GetOutput \n
  *  PLLCFGR         PLL3QEN         LL_RCC_PLL3_GetOutput \n
  *  PLLCFGR         PLL3REN         LL_RCC_PLL3_GetOutput \n
  *  PLLCFGR         PLL3SEN         LL_RCC_PLL3_GetOutput
  * @retval  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL3_OUTPUT_P
  *         @arg @ref LL_RCC_PLL3_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL3_OUTPUT_R
  *         @arg @ref LL_RCC_PLL3_OUTPUT_S
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetOutput(void)
{
  return STM32_READ_BIT(RCC->PLLCFGR, (LL_RCC_PLL3_OUTPUT_P | LL_RCC_PLL3_OUTPUT_Q | LL_RCC_PLL3_OUTPUT_R | \
                                       LL_RCC_PLL3_OUTPUT_S));
}

/**
  * @brief  Check if 1 or several PLL3 outputs are enabled.
  * @rmtoll
  *  PLLCFGR         PLL3PEN         LL_RCC_PLL3_IsOutputEnabled \n
  *  PLLCFGR         PLL3QEN         LL_RCC_PLL3_IsOutputEnabled \n
  *  PLLCFGR         PLL3REN         LL_RCC_PLL3_IsOutputEnabled \n
  *  PLLCFGR         PLL3SEN         LL_RCC_PLL3_IsOutputEnabled
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL3_OUTPUT_P
  *         @arg @ref LL_RCC_PLL3_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL3_OUTPUT_R
  *         @arg @ref LL_RCC_PLL3_OUTPUT_S
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsOutputEnabled(uint32_t outputs)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, outputs) == (outputs)) ? 1UL : 0UL);
}

/**
  * @brief  Set Main PLL3 multiplication factor for VCO.
  * @rmtoll
  *  PLL3DIVR1         DIVN         LL_RCC_PLL3_SetN
  * @param  divn parameter can be a value between 8 and 420
  */
__STATIC_INLINE void LL_RCC_PLL3_SetN(uint32_t divn)
{
  STM32_MODIFY_REG(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVN, (divn - 1UL) << RCC_PLL3DIVR1_DIVN_Pos);
}

/**
  * @brief  Get Main PLL3 multiplication factor for VCO.
  * @rmtoll
  *  PLL3DIVR1         DIVN         LL_RCC_PLL3_GetN
  * @retval Between 8 and 420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetN(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVN) >>  RCC_PLL3DIVR1_DIVN_Pos) + 1UL);
}

/**
  * @brief  Set Main division factor for PLL3.
  * @rmtoll
  *  PLLCKSELR         DIVM3         LL_RCC_PLL3_SetM
  * @param  divm3 parameter can be a value between 0 and 63. 0 disables the prescaler
  */
__STATIC_INLINE void LL_RCC_PLL3_SetM(uint32_t divm3)
{
  STM32_MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM3, (divm3) << RCC_PLLCKSELR_DIVM3_Pos);
}

/**
  * @brief  Get Main division factor for PLL3.
  * @rmtoll
  *  PLLCKSELR         DIVM3         LL_RCC_PLL3_GetM
  * @retval Between 0 and 63
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetM(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM3) >>  RCC_PLLCKSELR_DIVM3_Pos));
}

/**
  * @brief  Set Division factor for PLL3P.
  * @rmtoll
  *  PLL3DIVR1         DIVP         LL_RCC_PLL3_SetP
  * @param  pll3p parameter can be a value between 1 and 128
  * @note Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL3_SetP(uint32_t pll3p)
{
  STM32_MODIFY_REG(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVP, (pll3p - 1UL) << RCC_PLL3DIVR1_DIVP_Pos);
}

/**
  * @brief  Get Division factor for PLL3P.
  * @rmtoll
  *  PLL3DIVR1         DIVP         LL_RCC_PLL3_GetP
  * @note Used for peripherals clocks
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetP(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVP) >>  RCC_PLL3DIVR1_DIVP_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL3Q.
  * @rmtoll
  *  PLL3DIVR1         DIVQ         LL_RCC_PLL3_SetQ
  * @param  pll3q parameter can be a value between 1 and 128
  * @note Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL3_SetQ(uint32_t pll3q)
{
  STM32_MODIFY_REG(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVQ, (pll3q - 1UL) << RCC_PLL3DIVR1_DIVQ_Pos);
}

/**
  * @brief  Get Division factor for PLL3Q.
  * @rmtoll
  *  PLL3DIVR1         DIVQ         LL_RCC_PLL3_GetQ
  * @note Used for peripherals clocks
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetQ(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVQ) >>  RCC_PLL3DIVR1_DIVQ_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL3R.
  * @rmtoll
  *  PLL3DIVR1         DIVR         LL_RCC_PLL3_SetR
  * @param  pll3r parameter can be a value between 1 and 128
  * @note Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL3_SetR(uint32_t pll3r)
{
  STM32_MODIFY_REG(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVR, (pll3r - 1UL) << RCC_PLL3DIVR1_DIVR_Pos);
}

/**
  * @brief  Get Division factor for PLL3R.
  * @rmtoll
  *  PLL3DIVR1         DIVR         LL_RCC_PLL3_GetR
  * @note Used for peripherals clocks
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetR(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL3DIVR1, RCC_PLL3DIVR1_DIVR) >>  RCC_PLL3DIVR1_DIVR_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for PLL3S.
  * @rmtoll
  *  PLL3DIVR2         DIVS         LL_RCC_PLL3_SetS
  * @param  pll3s parameter can be a value between 1 and 8
  * @note Used for peripherals clocks
  */
__STATIC_INLINE void LL_RCC_PLL3_SetS(uint32_t pll3s)
{
  STM32_MODIFY_REG(RCC->PLL3DIVR2, RCC_PLL3DIVR2_DIVS, (pll3s - 1UL) << RCC_PLL3DIVR2_DIVS_Pos);
}

/**
  * @brief  Get Division factor for PLL3S.
  * @rmtoll
  *  PLL3DIVR2         DIVS         LL_RCC_PLL3_GetS
  * @note Used for peripherals clocks
  * @retval Between 1 and 8
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetS(void)
{
  return (uint32_t)((STM32_READ_BIT(RCC->PLL3DIVR2, RCC_PLL3DIVR2_DIVS) >>  RCC_PLL3DIVR2_DIVS_Pos) + 1UL);
}

/**
  * @brief  Enable PLL3 FRACN.
  * @rmtoll
  * PLLCFGR         PLL3FRACEN         LL_RCC_PLL3_EnableFRACN
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableFRACN(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3FRACEN);
}

/**
  * @brief  Disable PLL3 FRACN.
  * @rmtoll
  *  PLLCFGR         PLL3FRACEN         LL_RCC_PLL3_DisableFRACN
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableFRACN(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3FRACEN);
}

/**
  * @brief  Check if PLL3 FRACN is enabled.
  * @rmtoll
  *  PLLCFGR         PLL3FRACEN         LL_RCC_PLL3_IsEnabledFRACN
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledFRACN(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3FRACEN) == RCC_PLLCFGR_PLL3FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL3 FRACN Coefficient.
  * @rmtoll
  *  PLL3FRACR         FRACN         LL_RCC_PLL3_SetFRACN
  * @param  fracn parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL3_SetFRACN(uint32_t fracn)
{
  STM32_MODIFY_REG(RCC->PLL3FRACR, RCC_PLL3FRACR_FRACN, fracn << RCC_PLL3FRACR_FRACN_Pos);
}

/**
  * @brief  Get PLL3 FRACN Coefficient.
  * @rmtoll
  *  PLL3FRACR         FRACN         LL_RCC_PLL3_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetFRACN(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL3FRACR, RCC_PLL3FRACR_FRACN) >>  RCC_PLL3FRACR_FRACN_Pos);
}

/**
  * @brief  Set PLL3 VCO Output Range.
  * @rmtoll
  *  PLLCFGR         PLL3VCOSEL         LL_RCC_PLL3_SetVCORange
  * @param  output_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL3VCORANGE_384_1672
  *         @arg @ref LL_RCC_PLL3VCORANGE_150_420
  * @note   This API must be called only when PLL3 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL3_SetVCORange(uint32_t output_range)
{
  STM32_MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL3VCOSEL, output_range);
}

/**
  * @brief  Get PLL3 VCO Output Range.
  * @rmtoll
  *  PLLCFGR         PLL3VCOSEL         LL_RCC_PLL3_GetVCORange
  * @retval  The VCO range. This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL3VCORANGE_384_1672
  *         @arg @ref LL_RCC_PLL3VCORANGE_150_420
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetVCORange(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3VCOSEL));
}

/**
  * @brief  Set PLL3 VCO Input Range.
  * @rmtoll
  *  PLLCFGR         PLL3RGE         LL_RCC_PLL3_SetInputRange
  * @param  input_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL3INPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLL3INPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLL3INPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLL3INPUTRANGE_8_16
  * @note   This API must be called only when PLL3 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL3_SetInputRange(uint32_t input_range)
{
  STM32_MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL3RGE, input_range);
}

/**
  * @brief  Get PLL3 VCO Input Range.
  * @rmtoll
  *  PLLCFGR         PLL3RGE         LL_RCC_PLL3_GetInputRange
  * @retval  The VCO range. This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL3INPUTRANGE_1_2
  *         @arg @ref LL_RCC_PLL3INPUTRANGE_2_4
  *         @arg @ref LL_RCC_PLL3INPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLL3INPUTRANGE_8_16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetInputRange(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3RGE));
}

/**
  * @brief  Enable PLL3 Spread-spectrum clock generator (SSCG).
  * @rmtoll
  *  PLLCFGR         PLL3SSCGEN         LL_RCC_PLL3_EnableSSCG
  * @note   This API must be called only when PLL3 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableSSCG(void)
{
  STM32_SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SSCGEN);
}

/**
  * @brief  Disable PLL3 Spread-spectrum clock generator (SSCG).
  * @rmtoll
  *  PLLCFGR         PLL3SSCGEN         LL_RCC_PLL3_DisableSSCG
  * @note   This API must be called only when PLL3 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableSSCG(void)
{
  STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SSCGEN);
}

/**
  * @brief  Check if PLL3 Spread-spectrum clock generator (SSCG) is enabled.
  * @rmtoll
  *  PLLCFGR         PLL3SSCGEN         LL_RCC_PLL3_IsEnabledSSCG
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledSSCG(void)
{
  return ((STM32_READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3SSCGEN) == RCC_PLLCFGR_PLL3SSCGEN) ? 1UL : 0UL);
}

/**
  * @brief  Set Spread-spectrum Modulation Period for PLL3.
  * @rmtoll
  *  PLL3SSCGR         MODPER         LL_RCC_PLL3_SetSSCGModulationPeriod
  * @param  period This parameter can be between Min_Data=0 and Max_Data=8191
  */
__STATIC_INLINE void LL_RCC_PLL3_SetSSCGModulationPeriod(uint32_t period)
{
  STM32_MODIFY_REG(RCC->PLL3SSCGR, RCC_PLL3SSCGR_MODPER, period);
}

/**
  * @brief  Get Spread-spectrum Modulation Period for PLL3.
  * @rmtoll
  *  PLL3SSCGR         MODPER         LL_RCC_PLL3_GetSSCGModulationPeriod
  * @retval Between Min_Data=0 and Max_Data=8191
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetSSCGModulationPeriod(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_MODPER));
}

/**
  * @brief  Set Spread Spectrum Increment Step for PLL3.
  * @rmtoll
  *  PLL3SSCGR         INCSTEP         LL_RCC_PLL3_SetSSCGIncrementStep
  * @param  step This parameter can be between Min_Data=0 and Max_Data=32767
  */
__STATIC_INLINE void LL_RCC_PLL3_SetSSCGIncrementStep(uint32_t step)
{
  STM32_MODIFY_REG(RCC->PLL3SSCGR, RCC_PLL3SSCGR_INCSTEP, step << RCC_PLL3SSCGR_INCSTEP_Pos);
}

/**
  * @brief  Get Spread Spectrum Increment Step for PLL3.
  * @rmtoll
  *  PLL3SSCGR         INCSTEP         LL_RCC_PLL3_GetSSCGIncrementStep
  * @retval Between Min_Data=0 and Max_Data=32767
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetSSCGIncrementStep(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_INCSTEP) >> RCC_PLL3SSCGR_INCSTEP_Pos);
}

/**
  * @brief  Set Spread Spectrum Modulation Selection for PLL3.
  * @rmtoll
  *  PLL3SSCGR         SPREADSEL         LL_RCC_PLL3_SetSSCGSpreadSelection
  * @param  spread_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  */
__STATIC_INLINE void LL_RCC_PLL3_SetSSCGSpreadSelection(uint32_t spread_mode)
{
  STM32_MODIFY_REG(RCC->PLL3SSCGR, RCC_PLL3SSCGR_SPREADSEL, spread_mode);
}

/**
  * @brief  Get Spread Spectrum Selection for PLL3.
  * @rmtoll
  *  PLL3SSCGR         SPREADSEL         LL_RCC_PLL3_GetSSCGSpreadSelection
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetSSCGSpreadSelection(void)
{
  return (uint32_t)(STM32_READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_SPREADSEL));
}

/**
  * @brief  Enable Dithering RPDF Noise for PLL3.
  * @rmtoll
  *  PLL3SSCGR         RPDFNDIS         LL_RCC_PLL3_EnableSSCGRPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableSSCGRPDFNDithering(void)
{
  STM32_CLEAR_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_RPDFNDIS);
}

/**
  * @brief  Disable Dithering RPDF Noise for PLL3.
  * @rmtoll
  *  PLL3SSCGR         RPDFNDIS         LL_RCC_PLL3_DisableSSCGRPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableSSCGRPDFNDithering(void)
{
  STM32_SET_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_RPDFNDIS);
}

/**
  * @brief  Check if Dithering RPDF Noise for PLL3 is enabled.
  * @rmtoll
  *  PLL3SSCGR         RPDFNDIS         LL_RCC_PLL3_IsEnabledSSCGRPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledSSCGRPDFNDithering(void)
{
  return ((STM32_READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_RPDFNDIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Enable Dithering TPDF Noise for PLL3.
  * @rmtoll
  *  PLL3SSCGR         TPDFNDIS         LL_RCC_PLL3_EnableSSCGTPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableSSCGTPDFNDithering(void)
{
  STM32_CLEAR_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_TPDFNDIS);
}

/**
  * @brief  Disable Dithering TPDF Noise for PLL3.
  * @rmtoll
  *  PLL3SSCGR         TPDFNDIS         LL_RCC_PLL3_DisableSSCGTPDFNDithering
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableSSCGTPDFNDithering(void)
{
  STM32_SET_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_TPDFNDIS);
}

/**
  * @brief  Check if Dithering TPDF Noise for PLL3 is enabled.
  * @rmtoll
  *  PLL3SSCGR         TPDFNDIS         LL_RCC_PLL3_IsEnabledSSCGTPDFNDithering
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledSSCGTPDFNDithering(void)
{
  return ((STM32_READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_TPDFNDIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL2 Spread-Spectrum Modulation (SSCG) in a single atomic register write.
  * @rmtoll
  *  PLL3SSCGR   MODPER      LL_RCC_PLL3_ConfigSSCG \n
  *  PLL3SSCGR   INCSTEP     LL_RCC_PLL3_ConfigSSCG \n
  *  PLL3SSCGR   SPREADSEL   LL_RCC_PLL3_ConfigSSCG \n
  *  PLL3SSCGR   RPDFNDIS    LL_RCC_PLL3_ConfigSSCG \n
  *  PLL3SSCGR   TPDFNDIS    LL_RCC_PLL3_ConfigSSCG
  * @param mod_period   Modulation period, value between 0 and 0x1FFF
  * @param inc_step     Modulation depth increment step, value between 0 and 0x7FFF
  * @param spread_mode  This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SPREAD_CENTER
  *         @arg @ref LL_RCC_PLL_SPREAD_DOWN
  * @param dith_control This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_NO
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_TPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF_TPDF
  */
__STATIC_INLINE void LL_RCC_PLL3_ConfigSSCG(uint32_t mod_period, uint32_t inc_step, uint32_t spread_mode,
                                            uint32_t dith_control)
{
  STM32_MODIFY_REG(RCC->PLL3SSCGR,
                   RCC_PLL3SSCGR_MODPER | RCC_PLL3SSCGR_INCSTEP | RCC_PLL3SSCGR_SPREADSEL |
                   RCC_PLL3SSCGR_RPDFNDIS | RCC_PLL3SSCGR_TPDFNDIS,
                   ((mod_period << RCC_PLL3SSCGR_MODPER_Pos) & RCC_PLL3SSCGR_MODPER) |
                   ((inc_step << RCC_PLL3SSCGR_INCSTEP_Pos) & RCC_PLL3SSCGR_INCSTEP) |
                   spread_mode | dith_control);
}

/**
  * @brief  Get PLL2 SSCG dithering control.
  * @rmtoll
  *  PLL3SSCGR   RPDFNDIS      LL_RCC_PLL3_GetSSCGDithering \n
  *  PLL3SSCGR   TPDFNDIS      LL_RCC_PLL3_GetSSCGDithering
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_NO
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_TPDF
  *         @arg @ref LL_RCC_PLL_SSCG_DITH_RPDF_TPDF
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetSSCGDithering(void)
{
  return (uint32_t)STM32_READ_BIT(RCC->PLL3SSCGR, RCC_PLL3SSCGR_RPDFNDIS | RCC_PLL3SSCGR_TPDFNDIS);
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable RCC interrupts.
  * @rmtoll
  *  CIER         LSIRDYIE           LL_RCC_EnableIT \n
  *  CIER         LSERDYIE           LL_RCC_EnableIT \n
  *  CIER         HSIRDYIE           LL_RCC_EnableIT \n
  *  CIER         HSERDYIE           LL_RCC_EnableIT \n
  *  CIER         CSIRDYIE           LL_RCC_EnableIT \n
  *  CIER         HSI48RDYIE         LL_RCC_EnableIT \n
  *  CIER         PLL1RDYIE          LL_RCC_EnableIT \n
  *  CIER         PLL2RDYIE          LL_RCC_EnableIT \n
  *  CIER         PLL3RDYIE          LL_RCC_EnableIT \n
  *  CIER         LSECSSIE           LL_RCC_EnableIT
  * @param  mask specifies the RCC IT to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_CSIRDY
  *            @arg @ref LL_RCC_IT_HSI48RDY
  *            @arg @ref LL_RCC_IT_PLL1RDY
  *            @arg @ref LL_RCC_IT_PLL2RDY
  *            @arg @ref LL_RCC_IT_PLL3RDY
  *            @arg @ref LL_RCC_IT_LSECSS
  */
__STATIC_INLINE void LL_RCC_EnableIT(uint32_t mask)
{
  STM32_SET_BIT(RCC->CIER, mask);
}

/**
  * @brief  Enable LSI ready interrupt.
  * @rmtoll
  *  CIER         LSIRDYIE         LL_RCC_EnableIT_LSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSIRDY(void)
{
  STM32_SET_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Enable LSE ready interrupt.
  * @rmtoll
  *  CIER         LSERDYIE         LL_RCC_EnableIT_LSERDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSERDY(void)
{
  STM32_SET_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Enable HSI ready interrupt.
  * @rmtoll
  *  CIER         HSIRDYIE         LL_RCC_EnableIT_HSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSIRDY(void)
{
  STM32_SET_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
}

/**
  * @brief  Enable HSE ready interrupt.
  * @rmtoll
  *  CIER         HSERDYIE         LL_RCC_EnableIT_HSERDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSERDY(void)
{
  STM32_SET_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Enable CSI ready interrupt.
  * @rmtoll
  *  CIER         CSIRDYIE         LL_RCC_EnableIT_CSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_CSIRDY(void)
{
  STM32_SET_BIT(RCC->CIER, RCC_CIER_CSIRDYIE);
}

/**
  * @brief  Enable HSI48 ready interrupt.
  * @rmtoll
  *  CIER         HSI48RDYIE         LL_RCC_EnableIT_HSI48RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSI48RDY(void)
{
  STM32_SET_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE);
}

/**
  * @brief  Enable PLL1 ready interrupt.
  * @rmtoll
  *  CIER         PLL1RDYIE         LL_RCC_EnableIT_PLL1RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL1RDY(void)
{
  STM32_SET_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE);
}

/**
  * @brief  Enable PLL2 ready interrupt.
  * @rmtoll
  *  CIER         PLL2RDYIE         LL_RCC_EnableIT_PLL2RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL2RDY(void)
{
  STM32_SET_BIT(RCC->CIER, RCC_CIER_PLL2RDYIE);
}

/**
  * @brief  Enable PLL3 ready interrupt.
  * @rmtoll
  *  CIER         PLL3RDYIE         LL_RCC_EnableIT_PLL3RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL3RDY(void)
{
  STM32_SET_BIT(RCC->CIER, RCC_CIER_PLL3RDYIE);
}

/**
  * @brief  Enable LSECSS interrupt.
  * @rmtoll
  *  CIER         LSECSSIE         LL_RCC_EnableIT_LSECSS
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSECSS(void)
{
  STM32_SET_BIT(RCC->CIER, RCC_CIER_LSECSSIE);
}


/**
  * @brief  Disable RCC interrupts.
  * @rmtoll
  *  CIER         LSIRDYIE           LL_RCC_DisableIT \n
  *  CIER         LSERDYIE           LL_RCC_DisableIT \n
  *  CIER         HSIRDYIE           LL_RCC_DisableIT \n
  *  CIER         HSERDYIE           LL_RCC_DisableIT \n
  *  CIER         CSIRDYIE           LL_RCC_DisableIT \n
  *  CIER         HSI48RDYIE         LL_RCC_DisableIT \n
  *  CIER         PLL1RDYIE          LL_RCC_DisableIT \n
  *  CIER         PLL2RDYIE          LL_RCC_DisableIT \n
  *  CIER         PLL3RDYIE          LL_RCC_DisableIT \n
  *  CIER         LSECSSIE           LL_RCC_DisableIT
  * @param  mask specifies the RCC IT to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_CSIRDY
  *            @arg @ref LL_RCC_IT_HSI48RDY
  *            @arg @ref LL_RCC_IT_PLL1RDY
  *            @arg @ref LL_RCC_IT_PLL2RDY
  *            @arg @ref LL_RCC_IT_PLL3RDY
  *            @arg @ref LL_RCC_IT_LSECSS
  */
__STATIC_INLINE void LL_RCC_DisableIT(uint32_t mask)
{
  STM32_CLEAR_BIT(RCC->CIER, mask);
}

/**
  * @brief  Disable LSI ready interrupt.
  * @rmtoll
  *  CIER         LSIRDYIE         LL_RCC_DisableIT_LSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSIRDY(void)
{
  STM32_CLEAR_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Disable LSE ready interrupt.
  * @rmtoll
  *  CIER         LSERDYIE         LL_RCC_DisableIT_LSERDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSERDY(void)
{
  STM32_CLEAR_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Disable HSI ready interrupt.
  * @rmtoll
  *  CIER         HSIRDYIE         LL_RCC_DisableIT_HSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIRDY(void)
{
  STM32_CLEAR_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
}

/**
  * @brief  Disable HSE ready interrupt.
  * @rmtoll
  *  CIER         HSERDYIE         LL_RCC_DisableIT_HSERDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSERDY(void)
{
  STM32_CLEAR_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Disable CSI ready interrupt.
  * @rmtoll
  *  CIER         CSIRDYIE         LL_RCC_DisableIT_CSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_CSIRDY(void)
{
  STM32_CLEAR_BIT(RCC->CIER, RCC_CIER_CSIRDYIE);
}

/**
  * @brief  Disable HSI48 ready interrupt.
  * @rmtoll
  *  CIER         HSI48RDYIE         LL_RCC_DisableIT_HSI48RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSI48RDY(void)
{
  STM32_CLEAR_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE);
}

/**
  * @brief  Disable PLL1 ready interrupt.
  * @rmtoll
  *  CIER         PLL1RDYIE         LL_RCC_DisableIT_PLL1RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL1RDY(void)
{
  STM32_CLEAR_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE);
}

/**
  * @brief  Disable PLL2 ready interrupt.
  * @rmtoll
  *  CIER         PLL2RDYIE         LL_RCC_DisableIT_PLL2RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL2RDY(void)
{
  STM32_CLEAR_BIT(RCC->CIER, RCC_CIER_PLL2RDYIE);
}

/**
  * @brief  Disable PLL3 ready interrupt.
  * @rmtoll
  *  CIER         PLL3RDYIE         LL_RCC_DisableIT_PLL3RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL3RDY(void)
{
  STM32_CLEAR_BIT(RCC->CIER, RCC_CIER_PLL3RDYIE);
}

/**
  * @brief  Disable LSECSS interrupt.
  * @rmtoll
  *  CIER         LSECSSIE         LL_RCC_DisableIT_LSECSS
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSECSS(void)
{
  STM32_CLEAR_BIT(RCC->CIER, RCC_CIER_LSECSSIE);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         LSIRDYIE         LL_RCC_IsEnabledIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSIRDY(void)
{
  return ((STM32_READ_BIT(RCC->CIER, RCC_CIER_LSIRDYIE) == RCC_CIER_LSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         LSERDYIE         LL_RCC_IsEnabledIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSERDY(void)
{
  return ((STM32_READ_BIT(RCC->CIER, RCC_CIER_LSERDYIE) == RCC_CIER_LSERDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         HSIRDYIE         LL_RCC_IsEnabledIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIRDY(void)
{
  return ((STM32_READ_BIT(RCC->CIER, RCC_CIER_HSIRDYIE) == RCC_CIER_HSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         HSERDYIE         LL_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSERDY(void)
{
  return ((STM32_READ_BIT(RCC->CIER, RCC_CIER_HSERDYIE) == RCC_CIER_HSERDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if CSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         CSIRDYIE         LL_RCC_IsEnabledIT_CSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_CSIRDY(void)
{
  return ((STM32_READ_BIT(RCC->CIER, RCC_CIER_CSIRDYIE) == RCC_CIER_CSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI48 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         HSI48RDYIE         LL_RCC_IsEnabledIT_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSI48RDY(void)
{
  return ((STM32_READ_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE) == RCC_CIER_HSI48RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL1 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         PLL1RDYIE         LL_RCC_IsEnabledIT_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL1RDY(void)
{
  return ((STM32_READ_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE) == RCC_CIER_PLL1RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         PLL2RDYIE         LL_RCC_IsEnabledIT_PLL2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL2RDY(void)
{
  return ((STM32_READ_BIT(RCC->CIER, RCC_CIER_PLL2RDYIE) == RCC_CIER_PLL2RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL3 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         PLL3RDYIE         LL_RCC_IsEnabledIT_PLL3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL3RDY(void)
{
  return ((STM32_READ_BIT(RCC->CIER, RCC_CIER_PLL3RDYIE) == RCC_CIER_PLL3RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSECSS interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         LSECSSIE         LL_RCC_IsEnabledIT_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSECSS(void)
{
  return ((STM32_READ_BIT(RCC->CIER, RCC_CIER_LSECSSIE) == RCC_CIER_LSECSSIE) ? 1UL : 0UL);
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
  *  CICR         LSIRDYC           LL_RCC_ClearFlag \n
  *  CICR         LSERDYC           LL_RCC_ClearFlag \n
  *  CICR         HSIRDYC           LL_RCC_ClearFlag \n
  *  CICR         HSERDYC           LL_RCC_ClearFlag \n
  *  CICR         CSIRDYC           LL_RCC_ClearFlag \n
  *  CICR         HSI48RDYC         LL_RCC_ClearFlag \n
  *  CICR         PLL1RDYC          LL_RCC_ClearFlag \n
  *  CICR         PLL2RDYC          LL_RCC_ClearFlag \n
  *  CICR         PLL3RDYC          LL_RCC_ClearFlag \n
  *  CICR         LSECSSC           LL_RCC_ClearFlag \n
  *  CICR         HSECSSC           LL_RCC_ClearFlag
  * @param  mask specifies the RCC flags to be cleared.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_CSIRDY
  *            @arg @ref LL_RCC_IT_HSI48RDY
  *            @arg @ref LL_RCC_IT_PLL1RDY
  *            @arg @ref LL_RCC_IT_PLL2RDY
  *            @arg @ref LL_RCC_IT_PLL3RDY
  *            @arg @ref LL_RCC_IT_LSECSS
  *            @arg @ref LL_RCC_IT_HSECSS
  */
__STATIC_INLINE void LL_RCC_ClearFlag(uint32_t mask)
{
  STM32_WRITE_REG(RCC->CICR, mask);
}

/**
  * @brief  Clear LSI ready interrupt flag.
  * @rmtoll
  *  CICR         LSIRDYC         LL_RCC_ClearFlag_LSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSIRDY(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_LSIRDYC);
}

/**
  * @brief  Clear LSE ready interrupt flag.
  * @rmtoll
  *  CICR         LSERDYC         LL_RCC_ClearFlag_LSERDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSERDY(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_LSERDYC);
}

/**
  * @brief  Clear HSI ready interrupt flag.
  * @rmtoll
  *  CICR         HSIRDYC         LL_RCC_ClearFlag_HSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIRDY(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_HSIRDYC);
}

/**
  * @brief  Clear HSE ready interrupt flag.
  * @rmtoll
  *  CICR         HSERDYC         LL_RCC_ClearFlag_HSERDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSERDY(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_HSERDYC);
}

/**
  * @brief  Clear CSI ready interrupt flag.
  * @rmtoll
  *  CICR         CSIRDYC         LL_RCC_ClearFlag_CSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_CSIRDY(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_CSIRDYC);
}

/**
  * @brief  Clear HSI48 ready interrupt flag.
  * @rmtoll
  *  CICR         HSI48RDYC         LL_RCC_ClearFlag_HSI48RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSI48RDY(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_HSI48RDYC);
}

/**
  * @brief  Clear PLL1 ready interrupt flag.
  * @rmtoll
  *  CICR         PLL1RDYC         LL_RCC_ClearFlag_PLL1RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL1RDY(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_PLL1RDYC);
}

/**
  * @brief  Clear PLL2 ready interrupt flag.
  * @rmtoll
  *  CICR         PLL2RDYC         LL_RCC_ClearFlag_PLL2RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL2RDY(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_PLL2RDYC);
}

/**
  * @brief  Clear PLL3 ready interrupt flag.
  * @rmtoll
  *  CICR         PLL3RDYC         LL_RCC_ClearFlag_PLL3RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL3RDY(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_PLL3RDYC);
}

/**
  * @brief  Clear LSECSS interrupt flag.
  * @rmtoll
  *  CICR         LSECSSC         LL_RCC_ClearFlag_LSECSS
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSECSS(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_LSECSSC);
}

/**
  * @brief  Clear HSECSS interrupt flag.
  * @rmtoll
  *  CICR         HSECSSC         LL_RCC_ClearFlag_HSECSS
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSECSS(void)
{
  STM32_SET_BIT(RCC->CICR, RCC_CICR_HSECSSC);
}

/**
  * @brief  Check if RCC ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         LSIRDYF           LL_RCC_IsActiveFlag \n
  *  CIFR         LSERDYF           LL_RCC_IsActiveFlag \n
  *  CIFR         HSIRDYF           LL_RCC_IsActiveFlag \n
  *  CIFR         HSERDYF           LL_RCC_IsActiveFlag \n
  *  CIFR         CSIRDYF           LL_RCC_IsActiveFlag \n
  *  CIFR         HSI48RDYF         LL_RCC_IsActiveFlag \n
  *  CIFR         PLL1RDYF          LL_RCC_IsActiveFlag \n
  *  CIFR         PLL2RDYF          LL_RCC_IsActiveFlag \n
  *  CIFR         PLL3RDYF          LL_RCC_IsActiveFlag \n
  *  CIFR         LSECSSF           LL_RCC_IsActiveFlag \n
  *  CIFR         HSECSSF           LL_RCC_IsActiveFlag
  * @param  mask specifies the RCC flags to be cleared.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_CSIRDY
  *            @arg @ref LL_RCC_IT_HSI48RDY
  *            @arg @ref LL_RCC_IT_PLL1RDY
  *            @arg @ref LL_RCC_IT_PLL2RDY
  *            @arg @ref LL_RCC_IT_PLL3RDY
  *            @arg @ref LL_RCC_IT_LSECSS
  *            @arg @ref LL_RCC_IT_HSECSS
  * @retval State of flags (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag(uint32_t mask)
{
  return ((STM32_READ_BIT(RCC->CIFR, mask) == mask) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSIRDY ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         LSIRDYF         LL_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSIRDY(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_LSIRDYF) == RCC_CIFR_LSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSERDY ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         LSERDYF         LL_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSERDY(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_LSERDYF) == RCC_CIFR_LSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSIRDY ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         HSIRDYF         LL_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIRDY(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_HSIRDYF) == RCC_CIFR_HSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSERDY ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         HSERDYF         LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_HSERDYF) == RCC_CIFR_HSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if CSIRDY ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         CSIRDYF         LL_RCC_IsActiveFlag_CSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_CSIRDY(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_CSIRDYF) == RCC_CIFR_CSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI48RDY ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         HSI48RDYF         LL_RCC_IsActiveFlag_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSI48RDY(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_HSI48RDYF) == RCC_CIFR_HSI48RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL1RDY ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         PLL1RDYF         LL_RCC_IsActiveFlag_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL1RDY(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_PLL1RDYF) == RCC_CIFR_PLL1RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2RDY ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         PLL2RDYF         LL_RCC_IsActiveFlag_PLL2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL2RDY(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_PLL2RDYF) == RCC_CIFR_PLL2RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL3RDY ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         PLL3RDYF         LL_RCC_IsActiveFlag_PLL3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL3RDY(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_PLL3RDYF) == RCC_CIFR_PLL3RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSECSS ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         LSECSSF         LL_RCC_IsActiveFlag_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSECSS(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_LSECSSF) == RCC_CIFR_LSECSSF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSECSS ready interrupt occurred or not.
  * @rmtoll
  *  CIFR         HSECSSF         LL_RCC_IsActiveFlag_HSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSECSS(void)
{
  return ((STM32_READ_BIT(RCC->CIFR, RCC_CIFR_HSECSSF) == RCC_CIFR_HSECSSF) ? 1UL : 0UL);
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
  * @brief  Check if RCC Option byte loading reset flag is set or not.
  * @rmtoll
  *  RSR         OBLRSTF         LL_RCC_IsActiveFlag_OBLRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_OBLRST(void)
{
  return ((STM32_READ_BIT(RCC->RSR, RCC_RSR_OBLRSTF) == RCC_RSR_OBLRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC BOR reset flag is set or not.
  * @rmtoll
  *  RSR         BORRSTF         LL_RCC_IsActiveFlag_BORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_BORRST(void)
{
  return ((STM32_READ_BIT(RCC->RSR, RCC_RSR_BORRSTF) == RCC_RSR_BORRSTF) ? 1UL : 0UL);
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
  * @brief  Check if RCC POR/PDR reset flag is set or not.
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
  * @brief  Check if RCC reset due to illegal Stop or Standby flag is set or not.
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

#endif /* STM32H7PXX_LL_RCC_H */
