/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_rcc.h
  * @author  MCD Application Team
  * @version $VERSION$
  * @date    $DATE$
  * @brief   Header file of RCC LL module.
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    LL RCC RIF driver contains a set of following user APIs :
      (+) API to enable and disable Security access filtering to RCC Local Resources
      (+) API to enable and disable Privilege access filtering to RCC Local Resources
      (+) API to set and get configuration of Static or Dynamic CID access filtering to RCC Local Resources
      (+) API to take, release and get semaphore used for Dynamic CID access to RCC Local Resources

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_LL_RCC_H
#define STM32MP2xx_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx.h"

/** @addtogroup STM32MP2xx_LL_Driver
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

/* Define all reset flags mask */
#define LL_RCC_HWRSTSCLRR_ALL  0x000F7FFFU
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief  RCC Clocks Frequency Structure
  */
typedef struct
{
  uint32_t AXIM_Frequency;   /*!< AXIM clock frequency */
  uint32_t MLAHB_Frequency;  /*!< MLAHB clock frequency */
  uint32_t AHB1_Frequency;   /*!< AHB1 clock frequency */
  uint32_t AHB2_Frequency;   /*!< AHB2 clock frequency */
  uint32_t AHB3_Frequency;   /*!< AHB3 clock frequency */
  uint32_t AHB4_Frequency;   /*!< AHB4 clock frequency */
  uint32_t AHB5_Frequency;   /*!< AHB5 clock frequency */
  uint32_t AHB6_Frequency;   /*!< AHB6 clock frequency */
  uint32_t AHBSR_Frequency;  /*!< AHBSR clock frequency */
  uint32_t APB1_Frequency;   /*!< APB1 clock frequency */
  uint32_t APB2_Frequency;   /*!< APB2 clock frequency */
  uint32_t APB3_Frequency;   /*!< APB3 clock frequency */
  uint32_t APB4_Frequency;   /*!< APB4 clock frequency */
#if defined(RCC_APB5DIVR_APB5DIV)
  uint32_t APB5_Frequency;   /*!< APB5 clock frequency */
#endif /* RCC_APB5DIVR_APB5DIV */
  uint32_t APBSR_Frequency;  /*!< APBSR clock frequency */
  uint32_t APBDBG_Frequency; /*!< APBDBG clock frequency */
} LL_RCC_ClocksTypeDef;


/** @defgroup LL_ES_CLOCK_FREQ Clocks Frequency Structure
  * @{
  */

/**
  * @brief  RCC Clocks Frequency Structure
  */
typedef struct
{
  uint32_t freq;
} LL_PLL_ClocksTypeDef;
/**
  * @}
  */

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

#if defined(CORE_CA35)
#define PLL1_TYPEDEF CA35SSC_TypeDef;
#endif /* CORE_CA35 */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_LL_EC_OSC_VALUES Oscillator Values adaptation
  * @brief    Defines used to adapt values of different oscillators
  * @note     These values could be modified in the user environment according to
  *           HW set-up.
  * @{
  */
#if !defined  (HSE_VALUE)
#define HSE_VALUE    40000000U   /*!< Value of the HSE oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
#define HSI_VALUE    64000000U  /*!< Value of the HSI oscillator in Hz */
#endif /* HSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE    32768U     /*!< Value of the LSE oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE    32000U     /*!< Value of the LSI oscillator in Hz */
#endif /* LSI_VALUE */

#if !defined  (MSI_VALUE)
#define MSI_VALUE    1600000U     /*!< Value of the MSI oscillator in Hz */
#endif /* MSI_VALUE */

#if !defined  (EXTERNAL_CLOCK_VALUE)
#define EXTERNAL_CLOCK_VALUE    12288000U /*!< Value of the I2S_CKIN external oscillator in Hz */
#endif /* EXTERNAL_CLOCK_VALUE */

#if !defined  (USBO_48M_VALUE)
#define USBO_48M_VALUE    48000000U /*!< Value of the rcc_ck_usbo_48m oscillator in Hz */
#endif /* USBO_48M_VALUE */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_CLOCK_SOURCE Clock Sources Defines
  * @brief    Clock Sources defines which can be used with all the clocksource functions
  * @{
  */
#define LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV     (0x0U << RCC_XBARxCFGR_XBARxSEL_Pos) /* PLL4 FOUTPOSTDIV is selected */
#define LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV     (0x1U << RCC_XBARxCFGR_XBARxSEL_Pos) /* PLL5 FOUTPOSTDIV is selected */
#define LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV     (0x2U << RCC_XBARxCFGR_XBARxSEL_Pos) /* PLL6 FOUTPOSTDIV is selected */
#define LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV     (0x3U << RCC_XBARxCFGR_XBARxSEL_Pos) /* PLL7 FOUTPOSTDIV is selected */
#define LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV     (0x4U << RCC_XBARxCFGR_XBARxSEL_Pos) /* PLL8 FOUTPOSTDIV is selected */
#define LL_RCC_XBAR_CLKSRC_HSI                  (0x5U << RCC_XBARxCFGR_XBARxSEL_Pos) /* hsi_ck is selected */
#define LL_RCC_XBAR_CLKSRC_HSE                  (0x6U << RCC_XBARxCFGR_XBARxSEL_Pos) /* hse_ck is selected */
#define LL_RCC_XBAR_CLKSRC_MSI                  (0x7U << RCC_XBARxCFGR_XBARxSEL_Pos) /* msi_ck is selected */
#define LL_RCC_XBAR_CLKSRC_HSIKER               (0x8U << RCC_XBARxCFGR_XBARxSEL_Pos) /* hsi_ker_ck is selected */
#define LL_RCC_XBAR_CLKSRC_HSEKER               (0x9U << RCC_XBARxCFGR_XBARxSEL_Pos) /* hse_ker_ck is selected */
#define LL_RCC_XBAR_CLKSRC_MSIKER               (0xAU << RCC_XBARxCFGR_XBARxSEL_Pos) /* msi_ker_ck is selected */
#define LL_RCC_XBAR_CLKSRC_SPDIF                (0xBU << RCC_XBARxCFGR_XBARxSEL_Pos) /* spdif_ck_symb is selected */
#if !defined(RCC_DERIVATIVE1_CK_IN)
#define LL_RCC_XBAR_CLKSRC_I2S                  (0xCU << RCC_XBARxCFGR_XBARxSEL_Pos) /* i2s_ck is selected */
#else
#define LL_RCC_XBAR_CLKSRC_CK_IN                (0xCU << RCC_XBARxCFGR_XBARxSEL_Pos) /* CK_IN is selected */
#endif /* RCC_DERIVATIVE1_CK_IN */
#define LL_RCC_XBAR_CLKSRC_LSI                  (0xDU << RCC_XBARxCFGR_XBARxSEL_Pos) /* lsi_ck is selected */
#define LL_RCC_XBAR_CLKSRC_LSE                  (0xEU << RCC_XBARxCFGR_XBARxSEL_Pos) /* lse_ck is selected */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PREDIV_VALUE  Pre Divider Configuration Value Defines
  * @brief    Prediv defines which can be used with all the PREDIVxCFGR functions
  * @{
  */
#define LL_RCC_PREDIV_DIV1        (0x0U << RCC_PREDIVxCFGR_PREDIVx_Pos)
#define LL_RCC_PREDIV_DIV2        (0x1U << RCC_PREDIVxCFGR_PREDIVx_Pos)
#define LL_RCC_PREDIV_DIV4        (0x3U << RCC_PREDIVxCFGR_PREDIVx_Pos)
#define LL_RCC_PREDIV_DIV1024     (0x3FFU << RCC_PREDIVxCFGR_PREDIVx_Pos)
/**
  * @}
  */

/** @defgroup RCC_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_WriteReg function
  * @{
  */
#define LL_CIFCLRR_LSIRDYC      RCC_C2CIFCLRR_LSIRDYF /*!< LSI Ready Interrupt Clear */
#define LL_CIFCLRR_LSERDYC      RCC_C2CIFCLRR_LSERDYF /*!< LSE Ready Interrupt Clear */
#define LL_CIFCLRR_HSIRDYC      RCC_C2CIFCLRR_HSIRDYF /*!< HSI Ready Interrupt Clear */
#define LL_CIFCLRR_HSERDYC      RCC_C2CIFCLRR_HSERDYF /*!< HSE Ready Interrupt Clear */
#define LL_CIFCLRR_MSIRDYC      RCC_C2CIFCLRR_MSIRDYF /*!< MSI Ready Interrupt Clear */
#define LL_CIFCLRR_PLL1RDYC     RCC_C2CIFCLRR_PLL1RDYF /*!< PLL1 Ready Interrupt Clear */
#define LL_CIFCLRR_PLL2RDYC     RCC_C2CIFCLRR_PLL2RDYF /*!< PLL2 Ready Interrupt Clear */
#if defined(RCC_C2CIFCLRR_PLL3RDYF)
#define LL_CIFCLRR_PLL3RDYC     RCC_C2CIFCLRR_PLL3RDYF /*!< PLL3 Ready Interrupt Clear */
#endif /* RCC_C2CIFCLRR_PLL3RDYF */
#define LL_CIFCLRR_PLL4RDYC     RCC_C2CIFCLRR_PLL4RDYF /*!< PLL4 Ready Interrupt Clear */
#define LL_CIFCLRR_PLL5RDYC     RCC_C2CIFCLRR_PLL5RDYF /*!< PLL5 Ready Interrupt Clear */
#define LL_CIFCLRR_PLL6RDYC     RCC_C2CIFCLRR_PLL6RDYF /*!< PLL6 Ready Interrupt Clear */
#define LL_CIFCLRR_PLL7RDYC     RCC_C2CIFCLRR_PLL7RDYF /*!< PLL7 Ready Interrupt Clear */
#define LL_CIFCLRR_PLL8RDYC     RCC_C2CIFCLRR_PLL8RDYF /*!< PLL8 Ready Interrupt Clear */
#define LL_CIFCLRR_LSECSSC      RCC_C2CIFCLRR_LSECSSF /*!< LSE Clock Security System Interrupt Clear */
#define LL_CIFCLRR_WKUPC        RCC_C2CIFCLRR_WKUPF   /*!< Wake up from CStop Interrupt Clear */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_RCC_ReadReg function
  * @{
  */
#define LL_CIFCLRR_LSIRDYF      RCC_C2CIFCLRR_LSIRDYF /*!< LSI Ready Interrupt flag */
#define LL_CIFCLRR_LSERDYF      RCC_C2CIFCLRR_LSERDYF /*!< LSE Ready Interrupt flag */
#define LL_CIFCLRR_HSIRDYF      RCC_C2CIFCLRR_HSIRDYF /*!< HSI Ready Interrupt flag */
#define LL_CIFCLRR_HSERDYF      RCC_C2CIFCLRR_HSERDYF /*!< HSE Ready Interrupt flag */
#define LL_CIFCLRR_MSIRDYF      RCC_C2CIFCLRR_MSIRDYF /*!< MSI Ready Interrupt flag */
#define LL_CIFCLRR_PLL1RDYF     RCC_C2CIFCLRR_PLL1RDYF /*!< PLL1 Ready Interrupt flag */
#define LL_CIFCLRR_PLL2RDYF     RCC_C2CIFCLRR_PLL2RDYF /*!< PLL2 Ready Interrupt flag */
#if defined(RCC_C2CIFCLRR_PLL3RDYF)
#define LL_CIFCLRR_PLL3RDYF     RCC_C2CIFCLRR_PLL3RDYF /*!< PLL3 Ready Interrupt flag */
#endif /* RCC_C2CIFCLRR_PLL3RDYF */
#define LL_CIFCLRR_PLL4RDYF     RCC_C2CIFCLRR_PLL4RDYF /*!< PLL4 Ready Interrupt flag */
#define LL_CIFCLRR_PLL5RDYF     RCC_C2CIFCLRR_PLL5RDYF /*!< PLL5 Ready Interrupt Clear */
#define LL_CIFCLRR_PLL6RDYF     RCC_C2CIFCLRR_PLL6RDYF /*!< PLL6 Ready Interrupt Clear */
#define LL_CIFCLRR_PLL7RDYF     RCC_C2CIFCLRR_PLL7RDYF /*!< PLL7 Ready Interrupt Clear */
#define LL_CIFCLRR_PLL8RDYF     RCC_C2CIFCLRR_PLL8RDYF /*!< PLL8 Ready Interrupt Clear */
#define LL_CIFCLRR_LSECSSF      RCC_C2CIFCLRR_LSECSSF /*!< LSE Clock Security System Interrupt flag */
#define LL_CIFCLRR_WKUPF        RCC_C2CIFCLRR_WKUPF   /*!< Wake up from CStop Interrupt flag */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_RCC_ReadReg and  LL_RCC_WriteReg functions
  * @{
  */
#define LL_RCC_CIESETR_LSIRDYIE      RCC_C2CIESETR_LSIRDYIE /*!< LSI Ready Interrupt Enable */
#define LL_RCC_CIESETR_LSERDYIE      RCC_C2CIESETR_LSERDYIE /*!< LSE Ready Interrupt Enable */
#define LL_RCC_CIESETR_HSIRDYIE      RCC_C2CIESETR_HSIRDYIE /*!< HSI Ready Interrupt Enable */
#define LL_RCC_CIESETR_HSERDYIE      RCC_C2CIESETR_HSERDYIE /*!< HSE Ready Interrupt Enable */
#define LL_RCC_CIESETR_MSIRDYIE      RCC_C2CIESETR_MSIRDYIE /*!< MSI Ready Interrupt Enable */
#define LL_RCC_CIESETR_PLL1RDYIE     RCC_C2CIESETR_PLL1DYIE /*!< PLL1 Ready Interrupt Enable */
#define LL_RCC_CIESETR_PLL2RDYIE     RCC_C2CIESETR_PLL2DYIE /*!< PLL2 Ready Interrupt Enable */
#if defined(RCC_C2CIESETR_PLL3DYIE)
#define LL_RCC_CIESETR_PLL3RDYIE     RCC_C2CIESETR_PLL3DYIE /*!< PLL3 Ready Interrupt Enable */
#endif /* RCC_C2CIESETR_PLL3DYIE */
#define LL_RCC_CIESETR_PLL4RDYIE     RCC_C2CIESETR_PLL4DYIE /*!< PLL4 Ready Interrupt Enable */
#define LL_RCC_CIESETR_PLL5RDYIE     RCC_C2CIESETR_PLL5DYIE /*!< PLL5 Ready Interrupt Enable */
#define LL_RCC_CIESETR_PLL6RDYIE     RCC_C2CIESETR_PLL6DYIE /*!< PLL6 Ready Interrupt Enable */
#define LL_RCC_CIESETR_PLL7RDYIE     RCC_C2CIESETR_PLL7DYIE /*!< PLL7 Ready Interrupt Enable */
#define LL_RCC_CIESETR_PLL8RDYIE     RCC_C2CIESETR_PLL8DYIE /*!< PLL8 Ready Interrupt Enable */
#define LL_RCC_CIESETR_LSECSSIE      RCC_C2CIESETR_LSECSSIE /*!< LSE Clock Security System Interrupt Enable */
#define LL_RCC_CIESETR_WKUPIE        RCC_C2CIESETR_WKUPIE   /*!< Wake up from CStop Interrupt Enable */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_HSEDIV  HSE prescaler for RTC clock
  * @{
  */
#define LL_RCC_RTC_HSE_DIV_1                (0x0U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_2                (0x1U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_3                (0x2U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_4                (0x3U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_5                (0x4U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_6                (0x5U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_7                (0x6U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_8                (0x7U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_9                (0x8U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_10               (0x9U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_11               (0xAU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_12               (0xBU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_13               (0xCU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_14               (0xDU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_15               (0xEU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_16               (0xFU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_17               (0x10U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_18               (0x11U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_19               (0x12U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_20               (0x13U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_21               (0x14U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_22               (0x15U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_23               (0x16U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_24               (0x17U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_25               (0x18U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_26               (0x19U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_27               (0x1AU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_28               (0x1BU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_29               (0x1CU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_30               (0x1DU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_31               (0x1EU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_32               (0x1FU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_33               (0x20U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_34               (0x21U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_35               (0x22U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_36               (0x23U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_37               (0x24U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_38               (0x25U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_39               (0x26U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_40               (0x27U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_41               (0x28U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_42               (0x29U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_43               (0x2AU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_44               (0x2BU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_45               (0x2CU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_46               (0x2DU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_47               (0x2EU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_48               (0x2FU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_49               (0x30U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_50               (0x31U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_51               (0x32U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_52               (0x33U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_53               (0x34U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_54               (0x35U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_55               (0x36U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_56               (0x37U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_57               (0x38U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_58               (0x39U << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_59               (0x3AU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_60               (0x3BU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_61               (0x3CU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_62               (0x3DU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_63               (0x3EU << RCC_RTCDIVR_RTCDIV_Pos)
#define LL_RCC_RTC_HSE_DIV_64               (0x3FU << RCC_RTCDIVR_RTCDIV_Pos)
/*
  * @}
  */

/** @defgroup RCC_APB1_DIV  APB1 prescaler
  * @{
  */
#define LL_RCC_APB1_DIV_1                   (0x0U << RCC_APB1DIVR_APB1DIV_Pos)  /*!< apb1clk not divided (default after reset) */
#define LL_RCC_APB1_DIV_2                   (0x1U << RCC_APB1DIVR_APB1DIV_Pos)  /*!< apb1clk divided by 2 */
#define LL_RCC_APB1_DIV_4                   (0x2U << RCC_APB1DIVR_APB1DIV_Pos)  /*!< apb1clk divided by 4 */
#define LL_RCC_APB1_DIV_8                   (0x3U << RCC_APB1DIVR_APB1DIV_Pos)  /*!< apb1clk divided by 8 */
#define LL_RCC_APB1_DIV_16                  (0x4U << RCC_APB1DIVR_APB1DIV_Pos)  /*!< apb1clk divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_APB2_DIV  APB2 prescaler
  * @{
  */
#define LL_RCC_APB2_DIV_1                   (0x0U << RCC_APB2DIVR_APB2DIV_Pos)  /*!< apb2clk not divided (default after reset) */
#define LL_RCC_APB2_DIV_2                   (0x1U << RCC_APB2DIVR_APB2DIV_Pos)  /*!< apb2clk divided by 2 */
#define LL_RCC_APB2_DIV_4                   (0x2U << RCC_APB2DIVR_APB2DIV_Pos)  /*!< apb2clk divided by 4 */
#define LL_RCC_APB2_DIV_8                   (0x3U << RCC_APB2DIVR_APB2DIV_Pos)  /*!< apb2clk divided by 8 */
#define LL_RCC_APB2_DIV_16                  (0x4U << RCC_APB2DIVR_APB2DIV_Pos)  /*!< apb2clk divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_APB3_DIV  APB3 prescaler
  * @{
  */
#define LL_RCC_APB3_DIV_1                   (0x0U << RCC_APB3DIVR_APB3DIV_Pos)  /*!< apb3clk not divided (default after reset) */
#define LL_RCC_APB3_DIV_2                   (0x1U << RCC_APB3DIVR_APB3DIV_Pos)  /*!< apb3clk divided by 2 */
#define LL_RCC_APB3_DIV_4                   (0x2U << RCC_APB3DIVR_APB3DIV_Pos)  /*!< apb3clk divided by 4 */
#define LL_RCC_APB3_DIV_8                   (0x3U << RCC_APB3DIVR_APB3DIV_Pos)  /*!< apb3clk divided by 8 */
#define LL_RCC_APB3_DIV_16                  (0x4U << RCC_APB3DIVR_APB3DIV_Pos)  /*!< apb3clk divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_APB4_DIV  APB4 prescaler
  * @{
  */
#define LL_RCC_APB4_DIV_1                   (0x0U << RCC_APB4DIVR_APB4DIV_Pos)  /*!< apb4clk not divided (default after reset) */
#define LL_RCC_APB4_DIV_2                   (0x1U << RCC_APB4DIVR_APB4DIV_Pos)  /*!< apb4clk divided by 2 */
#define LL_RCC_APB4_DIV_4                   (0x2U << RCC_APB4DIVR_APB4DIV_Pos)  /*!< apb4clk divided by 4 */
#define LL_RCC_APB4_DIV_8                   (0x3U << RCC_APB4DIVR_APB4DIV_Pos)  /*!< apb4clk divided by 8 */
#define LL_RCC_APB4_DIV_16                  (0x4U << RCC_APB4DIVR_APB4DIV_Pos)  /*!< apb4clk divided by 16 */
/**
  * @}
  */
#if defined(RCC_APB5DIVR_APB5DIV)
/** @defgroup RCC_APB5_DIV  APB5 prescaler
  * @{
  */
#define LL_RCC_APB5_DIV_1                   (0x0U << RCC_APB5DIVR_APB5DIV_Pos)  /*!< apb5clk not divided (default after reset) */
#define LL_RCC_APB5_DIV_2                   (0x1U << RCC_APB5DIVR_APB5DIV_Pos)  /*!< apb5clk divided by 2 */
#define LL_RCC_APB5_DIV_4                   (0x2U << RCC_APB5DIVR_APB5DIV_Pos)  /*!< apb5clk divided by 4 */
#define LL_RCC_APB5_DIV_8                   (0x3U << RCC_APB5DIVR_APB5DIV_Pos)  /*!< apb5clk divided by 8 */
#define LL_RCC_APB5_DIV_16                  (0x4U << RCC_APB5DIVR_APB5DIV_Pos)  /*!< apb5clk divided by 16 */
/**
  * @}
  */
#endif /* RCC_APB5DIVR_APB5DIV */
/** @defgroup RCC_APBDBG_DIV  APBDBG prescaler
  * @{
  */
#define LL_RCC_APBDBG_DIV_1                 (0x0U << RCC_APBDBGDIVR_APBDBGDIV_Pos)  /*!< apbdbgclk not divided (default after reset) */
#define LL_RCC_APBDBG_DIV_2                 (0x1U << RCC_APBDBGDIVR_APBDBGDIV_Pos)  /*!< apbdbgclk divided by 2 */
#define LL_RCC_APBDBG_DIV_4                 (0x2U << RCC_APBDBGDIVR_APBDBGDIV_Pos)  /*!< apbdbgclk divided by 4 */
#define LL_RCC_APBDBG_DIV_8                 (0x3U << RCC_APBDBGDIVR_APBDBGDIV_Pos)  /*!< apbdbgclk divided by 8 */
#define LL_RCC_APBDBG_DIV_16                (0x4U << RCC_APBDBGDIVR_APBDBGDIV_Pos)  /*!< apbdbgclk divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LSMCUDIV  LSMCU prescaler
  * @{
  */
#define LL_RCC_LSMCUDIV_1                   (0x0U << RCC_LSMCUDIVR_LSMCUDIV_Pos)  /*!< lsmcu divided by 1 */
#define LL_RCC_LSMCUDIV_2                   (0x1U << RCC_LSMCUDIVR_LSMCUDIV_Pos)  /*!< lsmcu divided by 2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSEDRIVE  LSE oscillator drive capability
  * @{
  */
#define LL_RCC_LSEDRIVE_LOW                     (0x0U << RCC_BDCR_LSEDRV_Pos) /*!< Xtal mode lower driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH              (0x1U << RCC_BDCR_LSEDRV_Pos) /*!< Xtal mode medium high driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMLOW               (0x2U << RCC_BDCR_LSEDRV_Pos) /*!< Xtal mode medium low driving capability */
#define LL_RCC_LSEDRIVE_HIGH                    (0x3U << RCC_BDCR_LSEDRV_Pos) /*!< Xtal mode higher driving capability */
/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EC_PERIPH_FREQUENCY Peripheral clock frequency
  * @{
  */
#define LL_RCC_PERIPH_FREQUENCY_NO              0x00000000U /*!< No clock enabled for the peripheral */
#define LL_RCC_PERIPH_FREQUENCY_NA              0xFFFFFFFFU /*!< Frequency cannot be provided as external clock */
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/** @defgroup RCC_LL_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_NONE           (0x0U << RCC_BDCR_RTCSRC_Pos)  /*!< No clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSE            (0x1U << RCC_BDCR_RTCSRC_Pos)  /*!< LSE oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSI            (0x2U << RCC_BDCR_RTCSRC_Pos)  /*!< LSI oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_HSE_DIV        (0x3U << RCC_BDCR_RTCSRC_Pos)  /*!< HSE oscillator clock divided by RTCDIV used as RTC clock */
/**
  * @}
  */

#if defined(DSI)
/** @defgroup RCC_LL_EC_DSI Peripheral  DSI get clock source
  * @{
  */
#define LL_RCC_DSI_CLKSOURCE          RCC_DSICFGR_DSIBLSEL
/**
  * @}
  */
#endif /*DSI*/

/** @defgroup RCC_LL_EC_PLL1SOURCE  PLL1 entry clock source
  * @{
  */
#define LL_RCC_PLL1SOURCE_HSI         (0x0U << RCC_MUXSELCFGR_MUXSEL5_Pos)  /*!< HSI clock selected as PLL1 entry clock source */
#define LL_RCC_PLL1SOURCE_HSE         (0x1U << RCC_MUXSELCFGR_MUXSEL5_Pos)  /*!< HSE clock selected as PLL1 entry clock source */
#define LL_RCC_PLL1SOURCE_MSI         (0x2U << RCC_MUXSELCFGR_MUXSEL5_Pos)  /*!< MSI clock selected as PLL1 entry clock source */
#define LL_RCC_PLL1SOURCE_NONE        (0x3U << RCC_MUXSELCFGR_MUXSEL5_Pos)  /*!< No clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL2SOURCE  PLL2 entry clock source
  * @{
  */
#define LL_RCC_PLL2SOURCE_HSI         (0x0U << RCC_MUXSELCFGR_MUXSEL6_Pos)  /*!< HSI clock selected as PLL2 entry clock source */
#define LL_RCC_PLL2SOURCE_HSE         (0x1U << RCC_MUXSELCFGR_MUXSEL6_Pos)  /*!< HSE clock selected as PLL2 entry clock source */
#define LL_RCC_PLL2SOURCE_MSI         (0x2U << RCC_MUXSELCFGR_MUXSEL6_Pos)  /*!< MSI clock selected as PLL2 entry clock source */
#define LL_RCC_PLL2SOURCE_NONE        (0x3U << RCC_MUXSELCFGR_MUXSEL6_Pos)  /*!< No clock */
/**
  * @}
  */

#if defined(RCC_MUXSELCFGR_MUXSEL7_Pos)
/** @defgroup RCC_LL_EC_PLL3SOURCE  PLL3 entry clock source
  * @{
  */
#define LL_RCC_PLL3SOURCE_HSI         (0x0U << RCC_MUXSELCFGR_MUXSEL7_Pos)  /*!< HSI clock selected as PLL3 entry clock source */
#define LL_RCC_PLL3SOURCE_HSE         (0x1U << RCC_MUXSELCFGR_MUXSEL7_Pos)  /*!< HSE clock selected as PLL3 entry clock source */
#define LL_RCC_PLL3SOURCE_MSI         (0x2U << RCC_MUXSELCFGR_MUXSEL7_Pos)  /*!< MSI clock selected as PLL3 entry clock source */
#define LL_RCC_PLL3SOURCE_NONE        (0x3U << RCC_MUXSELCFGR_MUXSEL7_Pos)  /*!< No clock */
/**
  * @}
  */
#endif /* RCC_MUXSELCFGR_MUXSEL7_Pos */

/** @defgroup RCC_LL_EC_PLL4SOURCE  PLL4 entry clock source
  * @{
  */
#define LL_RCC_PLL4SOURCE_HSI         (0x0U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< HSI clock selected as PLL4 entry clock source */
#define LL_RCC_PLL4SOURCE_HSE         (0x1U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< HSE clock selected as PLL4 entry clock source */
#define LL_RCC_PLL4SOURCE_MSI         (0x2U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< MSI clock selected as PLL4 entry clock source */
#if defined(LL_RCC_XBAR_CLKSRC_CK_IN)
#define LL_RCC_PLL4SOURCE_CKIN        (0x5U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< CKIN clock selected as PLL4 entry clock source */
#define LL_RCC_PLL4SOURCE_NONE        (0x6U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< No clock */
#else
#define LL_RCC_PLL4SOURCE_NONE        (0x3U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< No clock */
#endif /* LL_RCC_XBAR_CLKSRC_CK_IN */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL5SOURCE  PLL5 entry clock source
  * @{
  */
#define LL_RCC_PLL5SOURCE_HSI         (0x0U << RCC_MUXSELCFGR_MUXSEL1_Pos)  /*!< HSI clock selected as PLL5 entry clock source */
#define LL_RCC_PLL5SOURCE_HSE         (0x1U << RCC_MUXSELCFGR_MUXSEL1_Pos)  /*!< HSE clock selected as PLL5 entry clock source */
#define LL_RCC_PLL5SOURCE_MSI         (0x2U << RCC_MUXSELCFGR_MUXSEL1_Pos)  /*!< MSI clock selected as PLL5 entry clock source */
#if defined(LL_RCC_XBAR_CLKSRC_CK_IN)
#define LL_RCC_PLL5SOURCE_CKIN        (0x5U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< CKIN clock selected as PLL4 entry clock source */
#define LL_RCC_PLL5SOURCE_NONE        (0x6U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< No clock */
#else
#define LL_RCC_PLL5SOURCE_NONE        (0x3U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< No clock */
#endif /* LL_RCC_XBAR_CLKSRC_CK_IN */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL6SOURCE  PLL6 entry clock source
  * @{
  */
#define LL_RCC_PLL6SOURCE_HSI         (0x0U << RCC_MUXSELCFGR_MUXSEL2_Pos)  /*!< HSI clock selected as PLL6 entry clock source */
#define LL_RCC_PLL6SOURCE_HSE         (0x1U << RCC_MUXSELCFGR_MUXSEL2_Pos)  /*!< HSE clock selected as PLL6 entry clock source */
#define LL_RCC_PLL6SOURCE_MSI         (0x2U << RCC_MUXSELCFGR_MUXSEL2_Pos)  /*!< MSI clock selected as PLL6 entry clock source */
#if defined(LL_RCC_XBAR_CLKSRC_CK_IN)
#define LL_RCC_PLL6SOURCE_CKIN        (0x5U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< CKIN clock selected as PLL4 entry clock source */
#define LL_RCC_PLL6SOURCE_NONE        (0x6U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< No clock */
#else
#define LL_RCC_PLL6SOURCE_NONE        (0x3U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< No clock */
#endif /* LL_RCC_XBAR_CLKSRC_CK_IN */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL7SOURCE  PLL7 entry clock source
  * @{
  */
#define LL_RCC_PLL7SOURCE_HSI         (0x0U << RCC_MUXSELCFGR_MUXSEL3_Pos)  /*!< HSI clock selected as PLL7 entry clock source */
#define LL_RCC_PLL7SOURCE_HSE         (0x1U << RCC_MUXSELCFGR_MUXSEL3_Pos)  /*!< HSE clock selected as PLL7 entry clock source */
#define LL_RCC_PLL7SOURCE_MSI         (0x2U << RCC_MUXSELCFGR_MUXSEL3_Pos)  /*!< MSI clock selected as PLL7 entry clock source */
#if defined(LL_RCC_XBAR_CLKSRC_CK_IN)
#define LL_RCC_PLL7SOURCE_CKIN        (0x5U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< CKIN clock selected as PLL4 entry clock source */
#define LL_RCC_PLL7SOURCE_NONE        (0x6U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< No clock */
#else
#define LL_RCC_PLL7SOURCE_NONE        (0x3U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< No clock */
#endif /* LL_RCC_XBAR_CLKSRC_CK_IN */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL8SOURCE  PLL8 entry clock source
  * @{
  */
#define LL_RCC_PLL8SOURCE_HSI         (0x0U << RCC_MUXSELCFGR_MUXSEL4_Pos)  /*!< HSI clock selected as PLL8 entry clock source */
#define LL_RCC_PLL8SOURCE_HSE         (0x1U << RCC_MUXSELCFGR_MUXSEL4_Pos)  /*!< HSE clock selected as PLL8 entry clock source */
#define LL_RCC_PLL8SOURCE_MSI         (0x2U << RCC_MUXSELCFGR_MUXSEL4_Pos)  /*!< MSI clock selected as PLL8 entry clock source */
#if defined(LL_RCC_XBAR_CLKSRC_CK_IN)
#define LL_RCC_PLL8SOURCE_CKIN        (0x5U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< CKIN clock selected as PLL4 entry clock source */
#define LL_RCC_PLL8SOURCE_NONE        (0x6U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< No clock */
#else
#define LL_RCC_PLL8SOURCE_NONE        (0x3U << RCC_MUXSELCFGR_MUXSEL0_Pos)  /*!< No clock */
#endif /* LL_RCC_XBAR_CLKSRC_CK_IN */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL2_SSCG_MODE  PLL2 Spread Spectrum Mode
  * @{
  */
#define LL_RCC_PLL2SSCG_CENTER_SPREAD          0x00000000U              /*!< Center-spread modulation selected (default after reset) */
#define LL_RCC_PLL2SSCG_DOWN_SPREAD            RCC_PLL1CFGR3_DOWNSPREAD /*!< Down-spread modulation selected */
/**
  * @}
  */

#if defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_SPI1_CLKSOURCE                 0x0U
#define  LL_RCC_SPI2_CLKSOURCE                 0x1U
#define  LL_RCC_SPI3_CLKSOURCE                 0x2U
#define  LL_RCC_SPI45_CLKSOURCE                0x3U
#define  LL_RCC_SPI6_CLKSOURCE                 0x4U
#elif defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_SPI1_CLKSOURCE                 0x0U
#define  LL_RCC_SPI23_CLKSOURCE                0x1U
#define  LL_RCC_SPI45_CLKSOURCE                0x2U
#define  LL_RCC_SPI8_CLKSOURCE                 0x3U
#else
#define  LL_RCC_SPI1_CLKSOURCE                 0x0U
#define  LL_RCC_SPI23_CLKSOURCE                0x1U
#define  LL_RCC_SPI45_CLKSOURCE                0x2U
#define  LL_RCC_SPI67_CLKSOURCE                0x3U
#define  LL_RCC_SPI8_CLKSOURCE                 0x4U
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_USART1_CLKSOURCE               0x0U
#define  LL_RCC_UART24_CLKSOURCE               0x1U
#define  LL_RCC_USART35_CLKSOURCE              0x2U
#define  LL_RCC_USART6_CLKSOURCE               0x3U
#define  LL_RCC_UART7_CLKSOURCE                0x4U
#define  LL_RCC_LPUART1_CLKSOURCE              0x5U
#define  LL_RCC_UART78_CLKSOURCE               LL_RCC_UART7_CLKSOURCE    /* backward compatibility */
#elif defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_USART1_CLKSOURCE               0x0U
#define  LL_RCC_UART24_CLKSOURCE               0x1U
#define  LL_RCC_USART35_CLKSOURCE              0x2U
#define  LL_RCC_USART6_CLKSOURCE               0x3U
#define  LL_RCC_UART78_CLKSOURCE               0x4U
#define  LL_RCC_LPUART1_CLKSOURCE              0x5U
#else
#define  LL_RCC_USART1_CLKSOURCE               0x0U
#define  LL_RCC_UART24_CLKSOURCE               0x1U
#define  LL_RCC_USART35_CLKSOURCE              0x2U
#define  LL_RCC_USART6_CLKSOURCE               0x3U
#define  LL_RCC_UART78_CLKSOURCE               0x4U
#define  LL_RCC_UART9_CLKSOURCE                0x5U
#define  LL_RCC_LPUART1_CLKSOURCE              0x6U
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_SAI1_MDF1_CLKSOURCE            0x0U
#else
#define  LL_RCC_SAI1_CLKSOURCE                 0x0U
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
#define  LL_RCC_SAI2_CLKSOURCE                 0x1U
#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_SAI34_CLKSOURCE                0x2U
#else
#define  LL_RCC_SAI3_CLKSOURCE                 0x2U
#define  LL_RCC_SAI4_CLKSOURCE                 0x3U
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_I2C12_CLKSOURCE                0x0U
#define  LL_RCC_I2C3_CLKSOURCE                 0x1U
#define  LL_RCC_I3C12_CLKSOURCE                0x0U
#define  LL_RCC_I3C3_CLKSOURCE                 0x1U
#elif defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_I2C12_I3C12_CLKSOURCE          0x0U
#define  LL_RCC_I2C7_CLKSOURCE                 0x1U
#define  LL_RCC_I3C4_CLKSOURCE                 0x2U
#define  LL_RCC_I2C8_CLKSOURCE                 0x3U
#else
#define  LL_RCC_I2C12_I3C12_CLKSOURCE          0x0U
#define  LL_RCC_I2C46_CLKSOURCE                0x1U
#define  LL_RCC_I2C35_I3C3_CLKSOURCE           0x2U
#define  LL_RCC_I2C7_CLKSOURCE                 0x3U
#define  LL_RCC_I3C4_CLKSOURCE                 0x4U
#define  LL_RCC_I2C8_CLKSOURCE                 0x5U
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#define  LL_RCC_SDMMC1_CLKSOURCE               0x0U
#define  LL_RCC_SDMMC2_CLKSOURCE               0x1U
#define  LL_RCC_SDMMC3_CLKSOURCE               0x2U

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_ETH1_ETHSW_CLKSOURCE           0x0U
#define  LL_RCC_ETH2_CLKSOURCE                 0x1U
#define  LL_RCC_ETH1PTP_ETH2PTP_CLKSOURCE      0x2U
#else
#define  LL_RCC_ETH1_CLKSOURCE                 0x0U
#define  LL_RCC_ETH2_CLKSOURCE                 0x1U
#define  LL_RCC_ETH1PTP_ETH2PTP_CLKSOURCE      0x2U
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#define  LL_RCC_OSPI1_CLKSOURCE                0x0U
#if defined(RCC_OSPI2CFGR_OSPI2EN)
#define  LL_RCC_OSPI2_CLKSOURCE                0x1U
#endif /* RCC_OSPI2CFGR_OSPI2EN */

#define  LL_RCC_FMC_CLKSOURCE                  0x0U

#define  LL_RCC_FDCAN_CLKSOURCE                0x0U

#define  LL_RCC_SPDIFRX_CLKSOURCE              0x0U

#define  LL_RCC_USB2PHY1_CLKSOURCE             0x0U
#define  LL_RCC_USB2PHY2_CLKSOURCE             0x1U
#if defined(USB3PCIEPHY)
#define  LL_RCC_USB3PCIEPHY_CLKSOURCE          0x2U
#endif /* USB3PCIEPHY */

#define  LL_RCC_STGEN_CLKSOURCE                0x0U

#define  LL_RCC_DSIBLANE_CLKSOURCE             0x0U
#define  LL_RCC_DSIPHY_CLKSOURCE               0x1U

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_ADC12_CLKSOURCE                0x0U
#define  LL_RCC_ADC3_CLKSOURCE                 0x1U
#else
#define  LL_RCC_ADC1_CLKSOURCE                 0x0U
#define  LL_RCC_ADC2_CLKSOURCE                 0x1U
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#define  LL_RCC_LPTIM12_CLKSOURCE              0x0U
#define  LL_RCC_LPTIM3_CLKSOURCE               0x1U
#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
#define  LL_RCC_LPTIM45_CLKSOURCE              0x2U
#else
#define  LL_RCC_LPTIM4_CLKSOURCE               0x2U
#define  LL_RCC_LPTIM5_CLKSOURCE               0x3U
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

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
  * @brief  Write a value in RCC register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_RCC_WriteReg(__REG__, __VALUE__) WRITE_REG(RCC->__REG__, (__VALUE__))

/**
  * @brief  Read a value in RCC register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_RCC_ReadReg(__REG__) READ_REG(RCC->__REG__)
/**
  * @}
  */

/** @defgroup RCC_LL_EM_CALC_FREQ Calculate frequencies
  * @{
  */

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
  * @brief  Enable the Clock Security System.
  * @note Once HSE Clock Security System is enabled it cannot be changed anymore unless
  *       a reset occurs or system enter in standby mode.
  * @rmtoll OCENSETR       HSECSSON         LL_RCC_HSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableCSS(void)
{
  SET_BIT(RCC->OCENSETR, RCC_OCENSETR_HSECSSON);
}

/**
  * @brief  Enable HSE external digital oscillator (HSE Digital Bypass)
  * @rmtoll OCENSETR     DIGBYP       LL_RCC_HSE_EnableDigBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableDigBypass(void)
{
  WRITE_REG(RCC->OCENSETR, RCC_OCENSETR_HSEBYP);
  WRITE_REG(RCC->OCENSETR, RCC_OCENSETR_HSEDIGBYP);
}

/**
  * @brief  Disable HSE external digital oscillator (HSE Digital Bypass)
  * @rmtoll OCENCLRR     DIGBYP       LL_RCC_HSE_DisableDigBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_DisableDigBypass(void)
{
  WRITE_REG(RCC->OCENCLRR, RCC_OCENCLRR_HSEBYP);
  WRITE_REG(RCC->OCENCLRR, RCC_OCENSETR_HSEDIGBYP);
}

/**
  * @brief  Enable HSE external oscillator (HSE Bypass)
  * @rmtoll OCENSETR     HSEBYP        LL_RCC_HSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_EnableBypass(void)
{
  WRITE_REG(RCC->OCENSETR, RCC_OCENSETR_HSEBYP);
}

/**
  * @brief  Disable HSE external oscillator (HSE Bypass)
  * @rmtoll OCENCLRR     HSEBYP        LL_RCC_HSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_DisableBypass(void)
{
  WRITE_REG(RCC->OCENCLRR, RCC_OCENCLRR_HSEBYP);
}

/**
  * @brief  Enable HSE crystal oscillator (HSE ON)
  * @rmtoll OCENCLRR      HSEON         LL_RCC_HSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_Enable(void)
{
  WRITE_REG(RCC->OCENSETR, RCC_OCENSETR_HSEON);
}

/**
  * @brief  Disable HSE crystal oscillator (HSE ON)
  * @rmtoll OCENCLRR           HSEON         LL_RCC_HSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSE_Disable(void)
{
  WRITE_REG(RCC->OCENCLRR, RCC_OCENCLRR_HSEON);
}

/**
  * @brief  Check if HSE oscillator is Ready
  * @rmtoll OCRDYR           HSERDY        LL_RCC_HSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsReady(void)
{
  return ((READ_BIT(RCC->OCRDYR, RCC_OCRDYR_HSERDY) == RCC_OCRDYR_HSERDY) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_HSI HSI
  * @{
  */

/**
  * @brief  Enable HSI even in stop mode
  * @note HSI oscillator is forced ON even in Stop mode
  * @rmtoll OCENSETR     HSIKERON      LL_RCC_HSI_EnableInStopMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_EnableInStopMode(void)
{
  WRITE_REG(RCC->OCENSETR, RCC_OCENSETR_HSIKERON);
}

/**
  * @brief  Disable HSI in stop mode
  * @rmtoll OCENCLRR     HSIKERON      LL_RCC_HSI_DisableInStopMode
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_DisableInStopMode(void)
{
  WRITE_REG(RCC->OCENCLRR, RCC_OCENCLRR_HSIKERON);
}

/**
  * @brief  Enable HSI oscillator
  * @rmtoll OCENSETR     HSION         LL_RCC_HSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_Enable(void)
{
  WRITE_REG(RCC->OCENSETR, RCC_OCENSETR_HSION);
}

/**
  * @brief  Disable HSI oscillator
  * @rmtoll OCENCLRR     HSION         LL_RCC_HSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_Disable(void)
{
  WRITE_REG(RCC->OCENCLRR, RCC_OCENCLRR_HSION);
}

/**
  * @brief  Check if HSI clock is ready
  * @rmtoll OCRDYR       HSIRDY        LL_RCC_HSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsReady(void)
{
  return ((READ_BIT(RCC->OCRDYR, RCC_OCRDYR_HSIRDY) == RCC_OCRDYR_HSIRDY) ? 1UL : 0UL);
}

/**
  * @brief  Get HSI Calibration value
  * @note When HSITRIM is written, HSICAL is updated with the sum of
  *       HSITRIM and the factory trim value
  * @rmtoll HSICFGR        HSICAL        LL_RCC_HSI_GetCalibration
  * @retval Between Min_Data = 0x00 and Max_Data = 0xFFF
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->HSICFGR, RCC_HSICFGR_HSICAL) >> RCC_HSICFGR_HSICAL_Pos);
}

/**
  * @brief  Set HSI Calibration trimming
  * @note user-programmable trimming value that is added to the HSICAL
  * @note Default value is 0
  * @rmtoll HSICFGR        HSITRIM       LL_RCC_HSI_SetCalibTrimming
  * @param  Value Between Min_Data = 0x0 and Max_Data = 0x7F
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->HSICFGR, RCC_HSICFGR_HSITRIM, Value << RCC_HSICFGR_HSITRIM_Pos);
}

/**
  * @brief  Get HSI Calibration trimming
  * @rmtoll HSICFGR        HSITRIM       LL_RCC_HSI_GetCalibTrimming
  * @retval Between Min_Data = 0 and Max_Data = 0x7F
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->HSICFGR, RCC_HSICFGR_HSITRIM) >> RCC_HSICFGR_HSITRIM_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_MSI MSI
  * @{
  */

/**
  * @brief  Get MSI Calibration value
  * @note When MSITRIM is written, MSICAL is updated with the sum of
  *       MSITRIM and the factory trim value
  * @rmtoll MSICFGR        MSICAL        LL_RCC_MSI_GetCalibration
  * @retval A value between 0 and 255 (0xFF)
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->MSICFGR, RCC_MSICFGR_MSICAL) >> RCC_MSICFGR_MSICAL_Pos);
}

/**
  * @brief  Set MSI Calibration trimming
  * @note user-programmable trimming value that is added to the MSICAL
  * @note Default value is 16 (0x10) which, when added to the MSICAL value,
  *       should trim the MSI to 4 MHz
  * @rmtoll MSICFGR        MSITRIM       LL_RCC_MSI_SetCalibTrimming
  * @param  Value can be a value between 0 and 31
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MSI_SetCalibTrimming(uint32_t Value)
{
  MODIFY_REG(RCC->MSICFGR, RCC_MSICFGR_MSITRIM, Value << RCC_MSICFGR_MSITRIM_Pos);
}

/**
  * @brief  Get MSI Calibration trimming
  * @rmtoll MSICFGR        MSITRIM       LL_RCC_MSI_GetCalibTrimming
  * @retval A value between 0 and 31
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->MSICFGR, RCC_MSICFGR_MSITRIM) >> RCC_MSICFGR_MSITRIM_Pos);

}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable  Low Speed External (LSE) crystal.
  * @rmtoll BDCR         LSEON         LL_RCC_LSE_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Disable  Low Speed External (LSE) crystal.
  * @rmtoll BDCR         LSEON         LL_RCC_LSE_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Enable external clock source (LSE bypass).
  * @rmtoll BDCR         LSEBYP        LL_RCC_LSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Disable external clock source (LSE bypass).
  * @rmtoll BDCR         LSEBYP        LL_RCC_LSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Enable external digital clock source (LSE Digital Bypass).
  * @rmtoll BDCR         LSEDIGBYP, LSEBYP    LL_RCC_LSE_EnableDigBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableDigBypass(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEDIGBYP);
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Disable external digital clock source (LSE Digital Bypass).
  * @rmtoll BDCR         LSEDIGBYP, LSEBYP     LL_RCC_LSE_DisableDigBypass
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableDigBypass(void)
{
  CLEAR_BIT(RCC->BDCR, (RCC_BDCR_LSEBYP | RCC_BDCR_LSEDIGBYP));
}

/**
  * @brief  Set LSE oscillator drive capability
  * @note The oscillator is in Xtal mode when it is not in bypass mode.
  * @rmtoll BDCR         LSEDRV        LL_RCC_LSE_SetDriveCapability
  * @param  LSEDrive This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_SetDriveCapability(uint32_t LSEDrive)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, LSEDrive);
}

/**
  * @brief  Get LSE oscillator drive capability
  * @rmtoll BDCR         LSEDRV        LL_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetDriveCapability(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_LSEDRV));
}

/**
  * @brief  Enable Clock security system on LSE.
  * @rmtoll BDCR         LSECSSON      LL_RCC_LSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_EnableCSS(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Disable Clock security system on LSE.
  * @note Clock security system can be disabled only after a LSE
  *       failure detection. In that case it MUST be disabled by software.
  * @rmtoll BDCR         LSECSSON      LL_RCC_LSE_DisableCSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Check if LSE oscillator Ready
  * @rmtoll BDCR         LSERDY        LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == RCC_BDCR_LSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if CSS on LSE failure Detection
  * @rmtoll BDCR         LSECSSD       LL_RCC_LSE_IsCSSDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsCSSDetected(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSECSSD) == RCC_BDCR_LSECSSD) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */

/**
  * @brief  Enable LSI Oscillator
  * @rmtoll BDCR          LSION         LL_RCC_LSI_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Enable(void)
{
#if defined(RCC_BDCR_LSION)
  SET_BIT(RCC->BDCR, RCC_BDCR_LSION);
#else
  SET_BIT(RCC->LSICR, RCC_LSICR_LSION);
#endif /* RCC_LSICR_LSION */
}

/**
  * @brief  Disable LSI Oscillator
  * @rmtoll BDCR          LSION         LL_RCC_LSI_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LSI_Disable(void)
{
#if defined(RCC_BDCR_LSION)
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSION);
#else
  CLEAR_BIT(RCC->LSICR, RCC_LSICR_LSION);
#endif /* RCC_LSICR_LSION */
}

/**
  * @brief  Check if LSI is Ready
  * @rmtoll BDCR          LSIRDY        LL_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsReady(void)
{
#if defined(RCC_BDCR_LSIRDY)
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSIRDY) == RCC_BDCR_LSIRDY) ? 1UL : 0UL);
#else
  return ((READ_BIT(RCC->LSICR, RCC_LSICR_LSIRDY) == RCC_LSICR_LSIRDY) ? 1UL : 0UL);
#endif /* RCC_LSICR_LSIRDY */
}

/**
  * @brief  Check if MSI is Ready
  * @rmtoll BDCR          MSIRDY        LL_RCC_MSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_IsReady(void)
{
#if defined(RCC_D3DCR_MSIRDY)
  return ((READ_BIT(RCC->D3DCR, RCC_D3DCR_MSIRDY) == RCC_D3DCR_MSIRDY) ? 1UL : 0UL);
#else
  return ((READ_BIT(RCC->OCRDYR, RCC_OCRDYR_MSIRDY) == RCC_OCRDYR_MSIRDY) ? 1UL : 0UL);
#endif /* RCC_OCRDYR_MSIRDY */
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_System System
  * @{
  */

/**
  * @brief  Set LSMCU divider Value
  * @param  lsmcudiv value of the divider
          Value parameter can be LL_RCC_LSMCUDIV_1 or LL_RCC_LSMCUDIV_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_Set_LSMCUDIVR(uint32_t lsmcudiv)
{
  MODIFY_REG(RCC->LSMCUDIVR, RCC_LSMCUDIVR_LSMCUDIV_Msk, lsmcudiv);
}

/**
  * @brief  Get LSMCU divider Value
  * @retval LL_RCC_LSMCUDIV_1 or LL_RCC_LSMCUDIV_2
  */
__STATIC_INLINE uint32_t LL_RCC_Get_LSMCUDIVR(void)
{
  return (READ_BIT(RCC->LSMCUDIVR, RCC_LSMCUDIVR_LSMCUDIV));
}


/**
  * @brief  Check if LSMCU is Ready
  * @rmtoll LL_RCC_LSMCUDIV_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSMCUDIV_IsReady(void)
{
  return ((READ_BIT(RCC->LSMCUDIVR, RCC_LSMCUDIVR_LSMCUDIVRDY) == RCC_LSMCUDIVR_LSMCUDIVRDY) ? 1UL : 0UL);
}


/**
  * @brief  Set channel pre divider Value
  * @param  flexid number of the channel to be configured (0 to 63)
  * @param  Value  parameter can be 0, 1, 3 or 0x3FF
  * @retval None
  */
__STATIC_INLINE void LL_RCC_Set_PREDIVx(uint32_t flexid, uint32_t Value)
{
  MODIFY_REG(RCC->PREDIVxCFGR[flexid], RCC_PREDIVxCFGR_PREDIVx_Msk, Value);
}

/**
  * @brief  Check PREDIV state (ready or not)
  * @param  flexid number of the channel to be checked (0 to 63)
  * @retval State of divider (0 for ready, 1 if change is on going)
  */
__STATIC_INLINE uint32_t LL_RCC_PREDIVxIsReady(uint32_t flexid)
{
  if (flexid <= 31U)
  {
    return ((READ_BIT(RCC->PREDIVSR1, (1UL << flexid)) == (1UL << flexid)) ? 1UL : 0UL);
  }
  else
  {
    return ((READ_BIT(RCC->PREDIVSR2, (1UL << (flexid % 32U))) == (1UL << (flexid % 32U))) ? 1UL : 0UL);
  }
}

/**
  * @brief  Set channel final divider Value
  * @param  flexid number of the channel to be configured (0 to 63)
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_Set_FINDIVx(uint32_t flexid, uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[flexid], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Check FINDIV state (ready or not)
  * @param  flexid number of the channel to be checked (0 to 63)
  * @retval State of divider (0 for ready, 1 if change is on going)
  */
__STATIC_INLINE uint32_t LL_RCC_FINDIVxIsReady(uint32_t flexid)
{
  if (flexid <= 31U)
  {
    return ((READ_BIT(RCC->FINDIVSR1, (1UL << flexid)) == (1UL << flexid)) ? 1UL : 0UL);
  }
  else
  {
    return ((READ_BIT(RCC->FINDIVSR2, (1UL << (flexid % 32U))) == (1UL << (flexid % 32U))) ? 1UL : 0UL);
  }
}

/**
  * @brief  Set the APB1 prescaler
  * @rmtoll APB1DIVR         APB1            LL_RCC_SetAPB1Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB1Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->APB1DIVR, RCC_APB1DIVR_APB1DIV, Prescaler);
}

/**
  * @brief  Set the APB2 prescaler
  * @rmtoll APB2DIVR         APB2            LL_RCC_SetAPB2Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_DIV_1
  *         @arg @ref LL_RCC_APB2_DIV_2
  *         @arg @ref LL_RCC_APB2_DIV_4
  *         @arg @ref LL_RCC_APB2_DIV_8
  *         @arg @ref LL_RCC_APB2_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB2Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->APB2DIVR, RCC_APB2DIVR_APB2DIV, Prescaler);
}

/**
  * @brief  Set the APB3 prescaler
  * @rmtoll APB3DIVR         APB3            LL_RCC_SetAPB3Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB3_DIV_1
  *         @arg @ref LL_RCC_APB3_DIV_2
  *         @arg @ref LL_RCC_APB3_DIV_4
  *         @arg @ref LL_RCC_APB3_DIV_8
  *         @arg @ref LL_RCC_APB3_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB3Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->APB3DIVR, RCC_APB3DIVR_APB3DIV, Prescaler);
}

/**
  * @brief  Set the APB4 prescaler
  * @rmtoll APB4DIVR         APB4            LL_RCC_SetAPB4Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB4_DIV_1
  *         @arg @ref LL_RCC_APB4_DIV_2
  *         @arg @ref LL_RCC_APB4_DIV_4
  *         @arg @ref LL_RCC_APB4_DIV_8
  *         @arg @ref LL_RCC_APB4_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPB4Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->APB4DIVR, RCC_APB4DIVR_APB4DIV, Prescaler);
}
#if defined(RCC_APB5DIVR_APB5DIV)
/**
  * @brief  Set the APB5 prescaler
  * @rmtoll APB5DIVR         APB5            LL_RCC_SetAPB5Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB5_DIV_1
  *         @arg @ref LL_RCC_APB5_DIV_2
  *         @arg @ref LL_RCC_APB5_DIV_4
  *         @arg @ref LL_RCC_APB5_DIV_8
  *         @arg @ref LL_RCC_APB5_DIV_16
  * @retval None
  */

__STATIC_INLINE void LL_RCC_SetAPB5Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->APB5DIVR, RCC_APB5DIVR_APB5DIV, Prescaler);
}
#endif /* RCC_APB5DIVR_APB5DIV */
/**
  * @brief  Set the APBDBG prescaler
  * @rmtoll APBDBGDIVR         APBDBG            LL_RCC_SetAPB3Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APBDBG_DIV_1
  *         @arg @ref LL_RCC_APBDBG_DIV_2
  *         @arg @ref LL_RCC_APBDBG_DIV_4
  *         @arg @ref LL_RCC_APBDBG_DIV_8
  *         @arg @ref LL_RCC_APBDBG_DIV_16
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetAPBDBGPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->APBDBGDIVR, RCC_APBDBGDIVR_APBDBGDIV, Prescaler);
}

/**
  * @brief  Get the APB1 prescaler
  * @rmtoll APB1DIVR         APB1           LL_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB1_DIV_1
  *         @arg @ref LL_RCC_APB1_DIV_2
  *         @arg @ref LL_RCC_APB1_DIV_4
  *         @arg @ref LL_RCC_APB1_DIV_8
  *         @arg @ref LL_RCC_APB1_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB1Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->APB1DIVR, RCC_APB1DIVR_APB1DIV));
}

/**
  * @brief  Get the APB2 prescaler
  * @rmtoll APB2DIVR         APB2           LL_RCC_GetAPB2Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB2_DIV_1
  *         @arg @ref LL_RCC_APB2_DIV_2
  *         @arg @ref LL_RCC_APB2_DIV_4
  *         @arg @ref LL_RCC_APB2_DIV_8
  *         @arg @ref LL_RCC_APB2_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB2Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->APB2DIVR, RCC_APB2DIVR_APB2DIV));
}

/**
  * @brief  Get the APB3 prescaler
  * @rmtoll APB3DIVR         APB3           LL_RCC_GetAPB3Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB3_DIV_1
  *         @arg @ref LL_RCC_APB3_DIV_2
  *         @arg @ref LL_RCC_APB3_DIV_4
  *         @arg @ref LL_RCC_APB3_DIV_8
  *         @arg @ref LL_RCC_APB3_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB3Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->APB3DIVR, RCC_APB3DIVR_APB3DIV));
}

/**
  * @brief  Get the APB4 prescaler
  * @rmtoll APB4DIVR         APB4           LL_RCC_GetAPB4Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB4_DIV_1
  *         @arg @ref LL_RCC_APB4_DIV_2
  *         @arg @ref LL_RCC_APB4_DIV_4
  *         @arg @ref LL_RCC_APB4_DIV_8
  *         @arg @ref LL_RCC_APB4_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB4Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->APB4DIVR, RCC_APB4DIVR_APB4DIV));
}
#if defined(RCC_APB5DIVR_APB5DIV)
/**
  * @brief  Get the APB5 prescaler
  * @rmtoll APB5DIVR         APB5           LL_RCC_GetAPB5Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB5_DIV_1
  *         @arg @ref LL_RCC_APB5_DIV_2
  *         @arg @ref LL_RCC_APB5_DIV_4
  *         @arg @ref LL_RCC_APB5_DIV_8
  *         @arg @ref LL_RCC_APB5_DIV_16
  */


__STATIC_INLINE uint32_t LL_RCC_GetAPB5Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->APB5DIVR, RCC_APB5DIVR_APB5DIV));
}
#endif /* RCC_APB5DIVR_APB5DIV */

/**
  * @brief  Get the APBDBG prescaler
  * @rmtoll APBDBGDIVR         APBDBG           LL_RCC_GetAPBDBGPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APBDBG_DIV_1
  *         @arg @ref LL_RCC_APBDBG_DIV_2
  *         @arg @ref LL_RCC_APBDBG_DIV_4
  *         @arg @ref LL_RCC_APBDBG_DIV_8
  *         @arg @ref LL_RCC_APBDBG_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPBDBGPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->APBDBGDIVR, RCC_APBDBGDIVR_APBDBGDIV));
}

/** @defgroup RCC_LL_EF_Peripheral_Clock_Source Peripheral Clock Source
  * @{
  */

/**
  * @brief  Set Cross Bar Clock Source
  * @rmtoll XBARxCFGR         XBARxSEL        LL_RCC_SetCrossbarSource
  * @param  xbar_id This parameter value can be between 0-63
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCrossbarSource(uint32_t xbar_id, uint32_t Source)
{
  WRITE_REG(RCC->XBARxCFGR[xbar_id], (Source & RCC_XBARxCFGR_XBARxSEL_Msk) | (1U << 6));
}

/**
  * @brief  Get Cross Bar Clock Source
  * @rmtoll XBARxCFGR         XBARxSEL        LL_RCC_GetCrossbarSource
  * @param  xbar_id This parameter value can be between 0-63
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE uint32_t LL_RCC_GetCrossbarSource(uint32_t xbar_id)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[xbar_id], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Get LPTIM1_2 clock source select
  * @rmtoll XBAR7CFGR      XBAR7SEL      LL_RCC_GetLPTIM1_2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM1_2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[7], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set LPTIM1_2 Clock Source
  * @rmtoll XBAR7CFGR         XBAR7SEL        LL_RCC_SetLPTIM1_2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM1_2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[7], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable LPTIM1_2 kernel clock
  * @rmtoll XBAR7CFGR         XBAR7EN         LL_RCC_EnableLPTIM1_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPTIM1_2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[7], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable LPTIM1_2 kernel clock
  * @rmtoll XBAR7CFGR         XBAR7EN         LL_RCC_DisableLPTIM1_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPTIM1_2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[7], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get USART2_4 clock source select
  * @rmtoll XBAR8CFGR      XBAR8SEL      LL_RCC_GetUSART2_4ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART2_4ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[8], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USART2_4 Clock Source
  * @rmtoll XBAR8CFGR         XBAR8SEL        LL_RCC_SetUSART2_4ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART2_4ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[8], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USART2_4 kernel clock
  * @rmtoll XBAR8CFGR         XBAR8EN         LL_RCC_EnableUSART2_4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART2_4_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[8], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USART2_4 kernel clock
  * @rmtoll XBAR8CFGR         XBAR8EN         LL_RCC_DisableUSART2_4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART2_4_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[8], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get UART3_5 clock source select
  * @rmtoll XBAR9CFGR      XBAR9SEL      LL_RCC_GetUSART3_5ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART3_5ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[9], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USART3_5 Clock Source
  * @rmtoll XBAR9CFGR         XBAR9SEL        LL_RCC_SetUSART3_5ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART3_5ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[9], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USART3_5 kernel clock
  * @rmtoll XBAR9CFGR         XBAR9EN         LL_RCC_EnableUSART3_5
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART3_5_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[9], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USART3_5 kernel clock
  * @rmtoll XBAR9CFGR         XBAR9EN         LL_RCC_DisableUSART3_5
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART3_5_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[9], RCC_XBARxCFGR_XBARxEN);
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get UART7_8 clock source select
  * @rmtoll XBAR21CFGR      XBAR21SEL      LL_RCC_GetUART7_8ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART7_8ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[21], RCC_XBARxCFGR_XBARxSEL_Msk));
}

#else

/**
  * @brief  Get UART7 clock source select
  * @rmtoll XBAR21CFGR      XBAR21SEL      LL_RCC_GetUART7ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART7ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[20], RCC_XBARxCFGR_XBARxSEL_Msk));
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SPI2_3 clock source select
  * @rmtoll XBAR10CFGR      XBAR10SEL      LL_RCC_GetSPI2_3ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI2_3ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[10], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SPI2_3 Clock Source
  * @rmtoll XBAR10CFGR         XBAR10SEL        LL_RCC_SetSPI2_3ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI2_3ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[10], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SPI2_3 kernel clock
  * @rmtoll XBAR10CFGR         XBAR10EN         LL_RCC_EnableSPI2_3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI2_3_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[10], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SPI2_3 kernel clock
  * @rmtoll XBAR10CFGR         XBAR10EN         LL_RCC_DisableSPI2_3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI2_3_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[10], RCC_XBARxCFGR_XBARxEN);
}
#else
/**
  * @brief  Get SPI2 clock source select
  * @rmtoll XBAR10CFGR      XBAR10SEL      LL_RCC_GetSPI2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[10], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SPI Clock Source
  * @rmtoll XBAR10CFGR         XBAR10SEL        LL_RCC_SetSPI2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[10], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SPI2 kernel clock
  * @rmtoll XBAR10CFGR         XBAR10EN         LL_RCC_EnableSPI2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[10], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SPI2 kernel clock
  * @rmtoll XBAR10CFGR         XBAR10EN         LL_RCC_DisableSPI2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[10], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get SPI3 clock source select
  * @rmtoll XBAR11CFGR      XBAR11SEL      LL_RCC_GetSPI3ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI3ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[11], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SPI3 Clock Source
  * @rmtoll XBAR11CFGR         XBAR11SEL        LL_RCC_SetSPI3ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI3ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[11], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SPI3 kernel clock
  * @rmtoll XBAR11CFGR         XBAR11EN         LL_RCC_EnableSPI3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI3_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[11], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SPI3 kernel clock
  * @rmtoll XBAR11CFGR         XBAR11EN         LL_RCC_DisableSPI3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI3_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[11], RCC_XBARxCFGR_XBARxEN);
}
#endif /*RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined (RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SPDIFRX clock source select
  * @rmtoll XBAR11CFGR      XBAR11SEL      LL_RCC_GetSPDIFRXClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPDIFRXClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[11], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SPDIFRX Clock Source
  * @rmtoll XBAR11CFGR         XBAR11SEL        LL_RCC_SetSPDIFRXClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPDIFRXClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[11], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SPDIFRX kernel clock
  * @rmtoll XBAR11CFGR         XBAR11EN         LL_RCC_EnableSPDIFRX
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPDIFRX_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[11], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SPDIFRX kernel clock
  * @rmtoll XBAR11CFGR         XBAR11EN         LL_RCC_DisableSPDIFRX
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPDIFRX_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[11], RCC_XBARxCFGR_XBARxEN);
}
#else
/**
  * @brief  Get SPDIFRX clock source select
  * @rmtoll XBAR12CFGR      XBAR12SEL      LL_RCC_GetSPDIFRXClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPDIFRXClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[12], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SPDIFRX Clock Source
  * @rmtoll XBAR12CFGR         XBAR12SEL        LL_RCC_SetSPDIFRXClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPDIFRXClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[12], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SPDIFRX kernel clock
  * @rmtoll XBAR12CFGR         XBAR12EN         LL_RCC_EnableSPDIFRX
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPDIFRX_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[12], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SPDIFRX kernel clock
  * @rmtoll XBAR12CFGR         XBAR12EN         LL_RCC_DisableSPDIFRX
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPDIFRX_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[12], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get I2C1_2_I3C1_2 clock source select
  * @rmtoll XBAR12CFGR      XBAR12SEL      LL_RCC_GetI2C1_2_I3C1_2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C1_2_I3C1_2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[12], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set I2C1_2_I3C1_2 Clock Source
  * @rmtoll XBAR12CFGR         XBAR12SEL        LL_RCC_SetI2C1_2_I3C1_2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C1_2_I3C1_2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[12], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable I2C1_2_I3C1_2 kernel clock
  * @rmtoll XBAR12CFGR         XBAR12EN         LL_RCC_EnableI2C1_2_I3C1_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C1_2_I3C1_2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[12], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable I2C1_2_I3C1_2 kernel clock
  * @rmtoll XBAR12CFGR         XBAR12EN         LL_RCC_DisableI2C1_2_I3C1_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C1_2_I3C1_2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[12], RCC_XBARxCFGR_XBARxEN);
}

#else

/**
  * @brief  Get I2C1_2 clock source select
  * @rmtoll XBAR13CFGR      XBAR13SEL      LL_RCC_GetI2C1_2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C1_2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[13], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set I2C1_2 Clock Source
  * @rmtoll XBAR13CFGR         XBAR13SEL        LL_RCC_SetI2C1_2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C1_2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[13], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable I2C1_2 kernel clock
  * @rmtoll XBAR13CFGR         XBAR13EN         LL_RCC_EnableI2C1_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C1_2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[13], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable I2C1_2 kernel clock
  * @rmtoll XBAR13CFGR         XBAR13EN         LL_RCC_DisableI2C1_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C1_2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[13], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get I3C1_2 clock source select
  * @rmtoll XBAR14CFGR      XBAR14SEL      LL_RCC_GetI3C1_2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3C1_2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[14], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set I3C1_2 Clock Source
  * @rmtoll XBAR14CFGR         XBAR14SEL        LL_RCC_SetI3C1_2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3C1_2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[14], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable I3C1_2 kernel clock
  * @rmtoll XBAR14CFGR         XBAR14EN         LL_RCC_EnableI3C1_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI3C1_2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[14], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable I3C1_2 kernel clock
  * @rmtoll XBAR14CFGR         XBAR14EN         LL_RCC_DisableI3C1_2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI3C1_2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[14], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)

/**
  * @brief  Get I2C3_5_I3C3 clock source select
  * @rmtoll XBAR13CFGR      XBAR13SEL      LL_RCC_GetI2C3_5_I3C3ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C3_5_I3C3ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[13], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set I2C3_5_I3C3 Clock Source
  * @rmtoll XBAR13CFGR         XBAR13SEL        LL_RCC_SetI2C3_5_I3C3ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C3_5_I3C3ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[13], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable I2C3_5_I3C3 kernel clock
  * @rmtoll XBAR13CFGR         XBAR13EN         LL_RCC_EnableI2C3_5_I3C3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C3_5_I3C3_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[13], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable I2C3_5_I3C3 kernel clock
  * @rmtoll XBAR13CFGR         XBAR13EN         LL_RCC_DisableI2C3_5_I3C3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C3_5_I3C3_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[13], RCC_XBARxCFGR_XBARxEN);
}

#else

/**
  * @brief  Get I2C3 clock source select
  * @rmtoll XBAR38CFGR      XBAR38SEL      LL_RCC_GetI2C3ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C3ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[38], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set I2C3 Clock Source
  * @rmtoll XBAR38CFGR         XBAR38SEL        LL_RCC_SetI2C3ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C3ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[38], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable I2C3 kernel clock
  * @rmtoll XBAR38CFGR         XBAR38EN         LL_RCC_EnableI2C3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C3_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[38], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable I2C3 kernel clock
  * @rmtoll XBAR38CFGR         XBAR38EN         LL_RCC_DisableI2C3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C3_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[38], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get I3C3 clock source select
  * @rmtoll XBAR36CFGR      XBAR36SEL      LL_RCC_GetI3C3ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3C3ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[36], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set I3C3 Clock Source
  * @rmtoll XBAR36CFGR         XBAR36SEL        LL_RCC_SetI3C3ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3C3ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[36], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable I3C3 kernel clock
  * @rmtoll XBAR36CFGR         XBAR36EN         LL_RCC_EnableI3C3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI3C3_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[36], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable I3C3 kernel clock
  * @rmtoll XBAR36CFGR         XBAR36EN         LL_RCC_DisableI3C3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI3C3_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[36], RCC_XBARxCFGR_XBARxEN);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
#endif /* RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
#if !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get I2C4_6 clock source select
  * @rmtoll XBAR14CFGR      XBAR14SEL      LL_RCC_GetI2C4_6ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C4_6ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[14], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set I2C4_6 Clock Source
  * @rmtoll XBAR14CFGR         XBAR14SEL        LL_RCC_SetI2C4_6ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C4_6ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[14], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable I2C4_6 kernel clock
  * @rmtoll XBAR14CFGR         XBAR14EN         LL_RCC_EnableI2C4_6
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C4_6_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[14], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable I2C4_6 kernel clock
  * @rmtoll XBAR14CFGR         XBAR14EN         LL_RCC_DisableI2C4_6
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C4_6_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[14], RCC_XBARxCFGR_XBARxEN);
}

#endif /* RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING */

/**
  * @brief  Get I2C7 clock source select
  * @rmtoll XBAR15CFGR      XBAR15SEL      LL_RCC_GetI2C7ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C7ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[15], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set I2C7 Clock Source
  * @rmtoll XBAR15CFGR         XBAR15SEL        LL_RCC_SetI2C7ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C7ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[15], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable I2C7 kernel clock
  * @rmtoll XBAR15CFGR         XBAR15EN         LL_RCC_EnableI2C7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C7_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[15], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable I2C7 kernel clock
  * @rmtoll XBAR15CFGR         XBAR15EN         LL_RCC_DisableI2C7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C7_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[15], RCC_XBARxCFGR_XBARxEN);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

/**
  * @brief  Get SPI1 clock source select
  * @rmtoll XBAR16CFGR      XBAR16SEL      LL_RCC_GetSPI1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[16], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SPI1 Clock Source
  * @rmtoll XBAR16CFGR         XBAR16SEL        LL_RCC_SetSPI1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[16], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SPI1 kernel clock
  * @rmtoll XBAR16CFGR         XBAR16EN         LL_RCC_EnableSPI1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[16], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SPI1 kernel clock
  * @rmtoll XBAR16CFGR         XBAR16EN         LL_RCC_DisableSPI1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[16], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get SPI4_5 clock source select
  * @rmtoll XBAR17CFGR      XBAR17SEL      LL_RCC_GetSPI4_5ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI4_5ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[17], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SPI4_5 Clock Source
  * @rmtoll XBAR17CFGR         XBAR17SEL        LL_RCC_SetSPI4_5ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI4_5ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[17], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SPI4_5 kernel clock
  * @rmtoll XBAR17CFGR         XBAR17EN         LL_RCC_EnableSPI4_5
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI4_5_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[17], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SPI4_5 kernel clock
  * @rmtoll XBAR17CFGR         XBAR17EN         LL_RCC_DisableSPI4_5
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI4_5_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[17], RCC_XBARxCFGR_XBARxEN);
}

#if !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SPI6_7 clock source select
  * @rmtoll XBAR18CFGR      XBAR18SEL      LL_RCC_GetSPI6_7ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI6_7ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[18], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SPI6_7 Clock Source
  * @rmtoll XBAR18CFGR         XBAR18SEL        LL_RCC_SetSPI6_7ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI6_7ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[18], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SPI6_7 kernel clock
  * @rmtoll XBAR18CFGR         XBAR18EN         LL_RCC_EnableSPI6_7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI6_7_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[18], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SPI6_7 kernel clock
  * @rmtoll XBAR18CFGR         XBAR18EN         LL_RCC_DisableSPI6_7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI6_7_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[18], RCC_XBARxCFGR_XBARxEN);
}
#else
/**
  * @brief  Get SPI6 clock source select
  * @rmtoll XBAR37CFGR      XBAR37SEL      LL_RCC_GetSPI6ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI6ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[37], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SPI6 Clock Source
  * @rmtoll XBAR37CFGR         XBAR37SEL        LL_RCC_SetSPI6ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI6ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[37], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SPI6 kernel clock
  * @rmtoll XBAR37CFGR         XBAR37EN         LL_RCC_EnableSPI6
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI6_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[37], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SPI6 kernel clock
  * @rmtoll XBAR37CFGR         XBAR37EN         LL_RCC_DisableSPI6
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI6_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[37], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
#endif /* RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get USART1 clock source select
  * @rmtoll XBAR19CFGR      XBAR19SEL      LL_RCC_GetUSART1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[19], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USART1 Clock Source
  * @rmtoll XBAR19CFGR         XBAR19SEL        LL_RCC_SetUSART1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[19], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USART1 kernel clock
  * @rmtoll XBAR19CFGR         XBAR19EN         LL_RCC_EnableUSART1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[19], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USART1 kernel clock
  * @rmtoll XBAR19CFGR         XBAR19EN         LL_RCC_DisableUSART1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[19], RCC_XBARxCFGR_XBARxEN);
}
#else
/**
  * @brief  Get USART1 clock source select
  * @rmtoll XBAR18CFGR      XBAR18SEL      LL_RCC_GetUSART1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[18], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USART1 Clock Source
  * @rmtoll XBAR18CFGR         XBAR18SEL        LL_RCC_SetUSART1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[18], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USART1 kernel clock
  * @rmtoll XBAR18CFGR         XBAR18EN         LL_RCC_EnableUSART1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[18], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USART1 kernel clock
  * @rmtoll XBAR18CFGR         XBAR18EN         LL_RCC_DisableUSART1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[18], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
/**
  * @brief  Get UART2_4 clock source select
  * @rmtoll XBAR8CFGR      XBAR8SEL      LL_RCC_GetUART24ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART2_4ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[8], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Get UART3_5 clock source select
  * @rmtoll XBAR9CFGR      XBAR9SEL      LL_RCC_GetUART3_5ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART3_5ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[9], RCC_XBARxCFGR_XBARxSEL_Msk));
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get USART6 clock source select
  * @rmtoll XBAR20CFGR      XBAR20SEL      LL_RCC_GetUSART6ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART6ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[20], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USART6 Clock Source
  * @rmtoll XBAR20CFGR         XBAR20SEL        LL_RCC_SetUSART6ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART6ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[20], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USART6 kernel clock
  * @rmtoll XBAR20CFGR         XBAR20EN         LL_RCC_EnableUSART6
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART6_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[20], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USART6 kernel clock
  * @rmtoll XBAR20CFGR         XBAR20EN         LL_RCC_DisableUSART6
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART6_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[20], RCC_XBARxCFGR_XBARxEN);
}
#else
/**
  * @brief  Get USART6 clock source select
  * @rmtoll XBAR19CFGR      XBAR19SEL      LL_RCC_GetUSART6ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART6ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[19], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USART6 Clock Source
  * @rmtoll XBAR19CFGR         XBAR19SEL        LL_RCC_SetUSART6ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART6ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[19], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USART6 kernel clock
  * @rmtoll XBAR19CFGR         XBAR19EN         LL_RCC_EnableUSART6
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART6_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[19], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USART6 kernel clock
  * @rmtoll XBAR19CFGR         XBAR19EN         LL_RCC_DisableUSART6
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART6_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[19], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get USART7_8 clock source select
  * @rmtoll XBAR21CFGR      XBAR21SEL      LL_RCC_GetUSART7_8ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART7_8ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[21], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USART7_8 Clock Source
  * @rmtoll XBAR21CFGR         XBAR21SEL        LL_RCC_SetUSART7_8ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART7_8ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[21], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USART7_8 kernel clock
  * @rmtoll XBAR21CFGR         XBAR21EN         LL_RCC_EnableUSART7_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART7_8_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[21], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USART7_8 kernel clock
  * @rmtoll XBAR21CFGR         XBAR21EN         LL_RCC_DisableUSART7_8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART7_8_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[21], RCC_XBARxCFGR_XBARxEN);
}

#else

/**
  * @brief  Get USART7 clock source select
  * @rmtoll XBAR20CFGR      XBAR20SEL      LL_RCC_GetUSART7ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART7ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[20], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USART7 Clock Source
  * @rmtoll XBAR20CFGR         XBAR20SEL        LL_RCC_SetUSART7ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART7ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[20], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USART7 kernel clock
  * @rmtoll XBAR20CFGR         XBAR20EN         LL_RCC_EnableUSART7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART7_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[20], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USART7 kernel clock
  * @rmtoll XBAR20CFGR         XBAR20EN         LL_RCC_DisableUSART7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART7_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[20], RCC_XBARxCFGR_XBARxEN);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING) && !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get UART9 clock source select
  * @rmtoll XBAR22CFGR      XBAR22SEL      LL_RCC_GetUART9ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART9ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[22], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set UART9 Clock Source
  * @rmtoll XBAR22CFGR         XBAR22SEL        LL_RCC_SetUART9ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUART9ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[22], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable UART9 kernel clock
  * @rmtoll XBAR22CFGR         XBAR22EN         LL_RCC_EnableUART9
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUART9_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[22], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable UART9 kernel clock
  * @rmtoll XBAR22CFGR         XBAR22EN         LL_RCC_DisableUART9
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUART9_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[22], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */


#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SAI1_MDF1 clock source select
  * @rmtoll XBAR23CFGR      XBAR23SEL      LL_RCC_GetSAI1_MDF1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI1_MDF1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[23], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SAI1_MDF1 Clock Source
  * @rmtoll XBAR23CFGR         XBAR23SEL        LL_RCC_SetSAI1_MDF1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI1_MDF1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[23], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SAI1_MDF1 kernel clock
  * @rmtoll XBAR23CFGR         XBAR23EN         LL_RCC_EnableSAI1_MDF1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI1_MDF1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[23], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SAI1_MDF1 kernel clock
  * @rmtoll XBAR23CFGR         XBAR23EN         LL_RCC_DisableSAI1_MDF1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI1_MDF1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[23], RCC_XBARxCFGR_XBARxEN);
}

#else

/**
  * @brief  Get MDF1 clock source select
  * @rmtoll XBAR21CFGR      XBAR21SEL      LL_RCC_GetMDF1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetMDF1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[21], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set MDF1 Clock Source
  * @rmtoll XBAR21CFGR         XBAR21SEL        LL_RCC_SetMDF1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetMDF1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[21], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable MDF1 kernel clock
  * @rmtoll XBAR21CFGR         XBAR21EN         LL_RCC_EnableMDF1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableMDF1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[21], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable MDF1 kernel clock
  * @rmtoll XBAR21CFGR         XBAR21EN         LL_RCC_DisableMDF1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableMDF1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[21], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get SAI1 clock source select
  * @rmtoll XBAR22CFGR      XBAR22SEL      LL_RCC_GetSAI1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[22], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SAI1 Clock Source
  * @rmtoll XBAR22CFGR         XBAR22SEL        LL_RCC_SetSAI1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[22], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SAI1 kernel clock
  * @rmtoll XBAR22CFGR         XBAR22EN         LL_RCC_EnableSAI1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[22], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SAI1 kernel clock
  * @rmtoll XBAR22CFGR         XBAR22EN         LL_RCC_DisableSAI1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[22], RCC_XBARxCFGR_XBARxEN);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SAI2 clock source select
  * @rmtoll XBAR24CFGR      XBAR24SEL      LL_RCC_GetSAI2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[24], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SAI2 Clock Source
  * @rmtoll XBAR24CFGR         XBAR24SEL        LL_RCC_SetSAI2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[24], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SAI2 kernel clock
  * @rmtoll XBAR24CFGR         XBAR24EN         LL_RCC_EnableSAI2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[24], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SAI2 kernel clock
  * @rmtoll XBAR24CFGR         XBAR24EN         LL_RCC_DisableSAI2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[24], RCC_XBARxCFGR_XBARxEN);
}
#else
/**
  * @brief  Get SAI2 clock source select
  * @rmtoll XBAR23CFGR      XBAR23SEL      LL_RCC_GetSAI2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[23], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SAI2 Clock Source
  * @rmtoll XBAR23CFGR         XBAR23SEL        LL_RCC_SetSAI2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[23], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SAI2 kernel clock
  * @rmtoll XBAR23CFGR         XBAR23EN         LL_RCC_EnableSAI2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[23], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SAI2 kernel clock
  * @rmtoll XBAR23CFGR         XBAR23EN         LL_RCC_DisableSAI2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[23], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SAI3_4 clock source select
  * @rmtoll XBAR25CFGR      XBAR25SEL      LL_RCC_GetSAI3_4ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI3_4ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[25], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SAI3_4 Clock Source
  * @rmtoll XBAR25CFGR         XBAR25SEL        LL_RCC_SetSAI3_4ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI3_4ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[25], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SAI3_4 kernel clock
  * @rmtoll XBAR25CFGR         XBAR25EN         LL_RCC_EnableSAI3_4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI3_4_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[25], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SAI3_4 kernel clock
  * @rmtoll XBAR25CFGR         XBAR25EN         LL_RCC_DisableSAI3_4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI3_4_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[25], RCC_XBARxCFGR_XBARxEN);
}
#else
/**
  * @brief  Get SAI3 clock source select
  * @rmtoll XBAR24CFGR      XBAR24SEL      LL_RCC_GetSAI3ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI3ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[24], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SAI3 Clock Source
  * @rmtoll XBAR24CFGR         XBAR24SEL        LL_RCC_SetSAI3ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI3ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[24], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SAI3 kernel clock
  * @rmtoll XBAR24CFGR         XBAR24EN         LL_RCC_EnableSAI3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI3_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[24], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SAI3 kernel clock
  * @rmtoll XBAR24CFGR         XBAR24EN         LL_RCC_DisableSAI3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI3_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[24], RCC_XBARxCFGR_XBARxEN);
}
/**
  * @brief  Get SAI4 clock source select
  * @rmtoll XBAR25CFGR      XBAR25SEL      LL_RCC_GetSAI4ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI4ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[25], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SAI4 Clock Source
  * @rmtoll XBAR25CFGR         XBAR25SEL        LL_RCC_SetSAI4ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI4ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[25], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SAI4 kernel clock
  * @rmtoll XBAR25CFGR         XBAR25EN         LL_RCC_EnableSAI4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI4_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[25], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SAI4 kernel clock
  * @rmtoll XBAR25CFGR         XBAR25EN         LL_RCC_DisableSAI4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI4_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[25], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
/**
  * @brief  Get FDCAN clock source select
  * @rmtoll XBAR26CFGR      XBAR26SEL      LL_RCC_GetFDCANClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetFDCANClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[26], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set FDCAN Clock Source
  * @rmtoll XBAR26CFGR         XBAR26SEL        LL_RCC_SetFDCANClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetFDCANClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[26], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable FDCAN kernel clock
  * @rmtoll XBAR26CFGR         XBAR26EN         LL_RCC_EnableFDCAN
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableFDCAN_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[26], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable FDCAN kernel clock
  * @rmtoll XBAR26CFGR         XBAR26EN         LL_RCC_DisableFDCAN
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableFDCAN_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[26], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get DSIBLANE clock source select
  * @rmtoll XBAR27CFGR      XBAR27SEL      LL_RCC_GetDSIBLANEClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetDSIBLANEClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[27], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set DSIBLANE Clock Source
  * @rmtoll XBAR27CFGR         XBAR27SEL        LL_RCC_SetDSIBLANEClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetDSIBLANEClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[27], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable DSIBLANE kernel clock
  * @rmtoll XBAR27CFGR         XBAR27EN         LL_RCC_EnableDSIBLANE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableDSIBLANE_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[27], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable DSIBLANE kernel clock
  * @rmtoll XBAR27CFGR         XBAR27EN         LL_RCC_DisableDSIBLANE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableDSIBLANE_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[27], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get DSIPHY clock source select
  * @rmtoll XBAR28CFGR      XBAR28SEL      LL_RCC_GetDSIPHYClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetDSIPHYClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[28], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set DSIPHY Clock Source
  * @rmtoll XBAR28CFGR         XBAR28SEL        LL_RCC_SetDSIPHYClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetDSIPHYClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[28], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable DSIPHY kernel clock
  * @rmtoll XBAR28CFGR         XBAR28EN         LL_RCC_EnableDSIPHY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableDSIPHY_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[28], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable DSIPHY kernel clock
  * @rmtoll XBAR28CFGR         XBAR28EN         LL_RCC_DisableDSIPHY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableDSIPHY_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[28], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get CSI2 clock source select
  * @rmtoll XBAR29CFGR      XBAR29SEL      LL_RCC_GetCSI2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetCSI2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[29], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set CSI2 Clock Source
  * @rmtoll XBAR29CFGR         XBAR29SEL        LL_RCC_SetCSI2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCSI2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[29], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable CSI2 kernel clock
  * @rmtoll XBAR29CFGR         XBAR29EN         LL_RCC_EnableCSI2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableCSI2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[29], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable CSI2 kernel clock
  * @rmtoll XBAR29CFGR         XBAR29EN         LL_RCC_DisableCSI2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableCSI2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[29], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get CSI2TXESC clock source select
  * @rmtoll XBAR30CFGR      XBAR30SEL      LL_RCC_GetCSI2TXESCClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetCSI2TXESCClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[30], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set CSI2TXESC Clock Source
  * @rmtoll XBAR30CFGR         XBAR30SEL        LL_RCC_SetCSI2TXESCClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCSI2TXESCClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[30], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable CSI2TXESC kernel clock
  * @rmtoll XBAR30CFGR         XBAR30EN         LL_RCC_EnableCSI2TXESC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableCSI2TXESC_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[30], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable CSI2TXESC kernel clock
  * @rmtoll XBAR30CFGR         XBAR30EN         LL_RCC_DisableCSI2TXESC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableCSI2TXESC_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[30], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get CSI2PHY clock source select
  * @rmtoll XBAR31CFGR      XBAR31SEL      LL_RCC_GetCSI2PHYClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetCSI2PHYClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[31], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set CSI2PHY Clock Source
  * @rmtoll XBAR31CFGR         XBAR31SEL        LL_RCC_SetCSI2PHYClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCSI2PHYClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[31], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable CSI2PHY kernel clock
  * @rmtoll XBAR31CFGR         XBAR31EN         LL_RCC_EnableCSI2PHY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableCSI2PHY_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[31], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable CSI2PHY kernel clock
  * @rmtoll XBAR31CFGR         XBAR31EN         LL_RCC_DisableCSI2PHY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableCSI2PHY_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[31], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get LVDSPHY clock source select
  * @rmtoll XBAR32CFGR      XBAR32SEL      LL_RCC_GetLVDSPHYClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLVDSPHYClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[32], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set LVDSPHY Clock Source
  * @rmtoll XBAR32CFGR         XBAR32SEL        LL_RCC_SetLVDSPHYClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLVDSPHYClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[32], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable LVDSPHY kernel clock
  * @rmtoll XBAR32CFGR         XBAR32EN         LL_RCC_EnableLVDSPHY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLVDSPHY_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[32], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable LVDSPHY kernel clock
  * @rmtoll XBAR32CFGR         XBAR32EN         LL_RCC_DisableLVDSPHY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLVDSPHY_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[32], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get STGEN clock source select
  * @rmtoll XBAR33CFGR      XBAR33SEL      LL_RCC_GetSTGENClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSTGENClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[33], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set STGEN Clock Source
  * @rmtoll XBAR33CFGR         XBAR33SEL        LL_RCC_SetSTGENClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSTGENClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[33], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable STGEN kernel clock
  * @rmtoll XBAR33CFGR         XBAR33EN         LL_RCC_EnableSTGEN
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSTGEN_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[33], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable STGEN kernel clock
  * @rmtoll XBAR33CFGR         XBAR33EN         LL_RCC_DisableSTGEN
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSTGEN_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[33], RCC_XBARxCFGR_XBARxEN);
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get USB3PCIEPHY clock source select
  * @rmtoll XBAR34CFGR      XBAR34SEL      LL_RCC_GetUSB3PCIEPHYClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSB3PCIEPHYClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[34], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USB3PCIEPHY Clock Source
  * @rmtoll XBAR34CFGR         XBAR34SEL        LL_RCC_SetUSB3PCIEPHYClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSB3PCIEPHYClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[34], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USB3PCIEPHY kernel clock
  * @rmtoll XBAR34CFGR         XBAR34EN         LL_RCC_EnableUSB3PCIEPHY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSB3PCIEPHY_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[34], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USB3PCIEPHY kernel clock
  * @rmtoll XBAR34CFGR         XBAR34EN         LL_RCC_DisableUSB3PCIEPHY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSB3PCIEPHY_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[34], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get UCPD1 clock source select
  * @rmtoll XBAR35CFGR      XBAR35SEL      LL_RCC_GetUCPD1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUCPD1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[35], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set UCPD1 Clock Source
  * @rmtoll XBAR35CFGR         XBAR35SEL        LL_RCC_SetUCPD1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUCPD1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[35], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable UCPD1 kernel clock
  * @rmtoll XBAR35CFGR         XBAR35EN         LL_RCC_EnableUCPD1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUCPD1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[35], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable UCPD1 kernel clock
  * @rmtoll XBAR35CFGR         XBAR35EN         LL_RCC_DisableUCPD1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUCPD1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[35], RCC_XBARxCFGR_XBARxEN);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */


#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get I3C4 clock source select
  * @rmtoll XBAR36CFGR      XBAR36SEL      LL_RCC_GetI3C4ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3C4ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[36], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set I3C4 Clock Source
  * @rmtoll XBAR36CFGR         XBAR36SEL        LL_RCC_SetI3C4ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3C4ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[36], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable I3C4 kernel clock
  * @rmtoll XBAR36CFGR         XBAR36EN         LL_RCC_EnableI3C4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI3C4_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[36], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable I3C4 kernel clock
  * @rmtoll XBAR36CFGR         XBAR36EN         LL_RCC_DisableI3C4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI3C4_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[36], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */


#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SPI8 clock source select
  * @rmtoll XBAR37CFGR      XBAR37SEL      LL_RCC_GetSPI8ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI8ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[37], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SPI8 Clock Source
  * @rmtoll XBAR37CFGR         XBAR37SEL        LL_RCC_SetSPI8ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI8ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[37], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SPI8 kernel clock
  * @rmtoll XBAR37CFGR         XBAR37EN         LL_RCC_EnableSPI8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI8_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[37], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SPI8 kernel clock
  * @rmtoll XBAR37CFGR         XBAR37EN         LL_RCC_DisableSPI8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI8_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[37], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */


#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get I2C8 clock source select
  * @rmtoll XBAR38CFGR      XBAR38SEL      LL_RCC_GetI2C8ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C8ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[38], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set I2C8 Clock Source
  * @rmtoll XBAR38CFGR         XBAR38SEL        LL_RCC_SetI2C8ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C8ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[38], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable I2C8 kernel clock
  * @rmtoll XBAR38CFGR         XBAR38EN         LL_RCC_EnableI2C8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C8_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[38], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable I2C8 kernel clock
  * @rmtoll XBAR38CFGR         XBAR38EN         LL_RCC_DisableI2C8
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C8_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[38], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

/**
  * @brief  Get LPUART1 clock source select
  * @rmtoll XBAR39CFGR      XBAR39SEL      LL_RCC_GetLPUART1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUART1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[39], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set LPUART1 Clock Source
  * @rmtoll XBAR39CFGR         XBAR39SEL        LL_RCC_SetLPUART1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPUART1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[39], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable LPUART1 kernel clock
  * @rmtoll XBAR39CFGR         XBAR39EN         LL_RCC_EnableLPUART1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPUART1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[39], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable LPUART1 kernel clock
  * @rmtoll XBAR39CFGR         XBAR39EN         LL_RCC_DisableLPUART1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPUART1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[39], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get LPTIM3 clock source select
  * @rmtoll XBAR40CFGR      XBAR40SEL      LL_RCC_GetLPTIM3ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM3ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[40], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set LPTIM3 Clock Source
  * @rmtoll XBAR40CFGR         XBAR40SEL        LL_RCC_SetLPTIM3ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM3ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[40], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable LPTIM3 kernel clock
  * @rmtoll XBAR40CFGR         XBAR40EN         LL_RCC_EnableLPTIM3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPTIM3_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[40], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable LPTIM3 kernel clock
  * @rmtoll XBAR40CFGR         XBAR40EN         LL_RCC_DisableLPTIM3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPTIM3_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[40], RCC_XBARxCFGR_XBARxEN);
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)

/**
  * @brief  Get LPTIM4_5 clock source select
  * @rmtoll XBAR41CFGR      XBAR41SEL      LL_RCC_GetLPTIM4_5ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM4_5ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[41], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set LPTIM4_5 Clock Source
  * @rmtoll XBAR41CFGR         XBAR41SEL        LL_RCC_SetLPTIM4_5ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM4_5ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[41], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable LPTIM4_5 kernel clock
  * @rmtoll XBAR41CFGR         XBAR41EN         LL_RCC_EnableLPTIM4_5
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPTIM4_5_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[41], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable LPTIM4_5 kernel clock
  * @rmtoll XBAR41CFGR         XBAR41EN         LL_RCC_DisableLPTIM4_5
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPTIM4_5_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[41], RCC_XBARxCFGR_XBARxEN);
}

#else

/**
  * @brief  Get LPTIM4 clock source select
  * @rmtoll XBAR41CFGR      XBAR41SEL      LL_RCC_GetLPTIM4ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM4ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[41], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set LPTIM4 Clock Source
  * @rmtoll XBAR41CFGR         XBAR41SEL        LL_RCC_SetLPTIM4ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM4ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[41], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable LPTIM4 kernel clock
  * @rmtoll XBAR41CFGR         XBAR41EN         LL_RCC_EnableLPTIM4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPTIM4_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[41], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable LPTIM4 kernel clock
  * @rmtoll XBAR41CFGR         XBAR41EN         LL_RCC_DisableLPTIM4
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPTIM4_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[41], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get LPTIM5 clock source select
  * @rmtoll XBAR42CFGR      XBAR42SEL      LL_RCC_GetLPTIM5ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM5ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[42], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set LPTIM5 Clock Source
  * @rmtoll XBAR42CFGR         XBAR42SEL        LL_RCC_SetLPTIM5ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM5ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[42], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable LPTIM5 kernel clock
  * @rmtoll XBAR42CFGR         XBAR42EN         LL_RCC_EnableLPTIM5
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPTIM5_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[42], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable LPTIM5 kernel clock
  * @rmtoll XBAR42CFGR         XBAR42EN         LL_RCC_DisableLPTIM5
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPTIM5_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[42], RCC_XBARxCFGR_XBARxEN);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING) && !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get ADF1 clock source select
  * @rmtoll XBAR42CFGR      XBAR42SEL      LL_RCC_GetADF1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetADF1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[42], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ADF1 Clock Source
  * @rmtoll XBAR42CFGR         XBAR42SEL        LL_RCC_SetADF1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADF1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[42], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ADF1 kernel clock
  * @rmtoll XBAR42CFGR         XBAR42EN         LL_RCC_EnableADF1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableADF1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[42], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ADF1 kernel clock
  * @rmtoll XBAR42CFGR         XBAR42EN         LL_RCC_DisableADF1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableADF1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[42], RCC_XBARxCFGR_XBARxEN);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

/**
  * @brief  Get TSDBG clock source select
  * @rmtoll XBAR43CFGR      XBAR43SEL      LL_RCC_GetTSDBGClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetTSDBGClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[43], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set TSDBG Clock Source
  * @rmtoll XBAR43CFGR         XBAR43SEL        LL_RCC_SetTSDBGClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetTSDBGClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[43], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable TSDBG kernel clock
  * @rmtoll XBAR43CFGR         XBAR43EN         LL_RCC_EnableTSDBG
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableTSDBG_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[43], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable TSDBG kernel clock
  * @rmtoll XBAR43CFGR         XBAR43EN         LL_RCC_DisableTSDBG
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableTSDBG_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[43], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get TPIU clock source select
  * @rmtoll XBAR44CFGR      XBAR44SEL      LL_RCC_GetTPIUClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetTPIUClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[44], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set TPIU Clock Source
  * @rmtoll XBAR44CFGR         XBAR44SEL        LL_RCC_SetTPIUClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetTPIUClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[44], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable TPIU kernel clock
  * @rmtoll XBAR44CFGR         XBAR44EN         LL_RCC_EnableTPIU
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableTPIU_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[44], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable TPIU kernel clock
  * @rmtoll XBAR44CFGR         XBAR44EN         LL_RCC_DisableTPIU
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableTPIU_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[44], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get ATB_METR clock source select
  * @rmtoll XBAR45CFGR      XBAR45SEL      LL_RCC_GetATB_METRClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetATB_METRClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[45], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ATB_METR Clock Source
  * @rmtoll XBAR45CFGR         XBAR45SEL        LL_RCC_SetATB_METRClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetATB_METRClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[45], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ATB_METR kernel clock
  * @rmtoll XBAR45CFGR         XBAR45EN         LL_RCC_EnableATB_METR
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableATB_METR_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[45], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ATB_METR kernel clock
  * @rmtoll XBAR45CFGR         XBAR45EN         LL_RCC_DisableATB_METR
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableATB_METR_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[45], RCC_XBARxCFGR_XBARxEN);
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get ADC12 clock source select
  * @rmtoll XBAR46CFGR      XBAR46SEL      LL_RCC_GetADC12ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC12ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[46], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ADC12 Clock Source
  * @rmtoll XBAR46CFGR         XBAR46SEL        LL_RCC_SetADC12ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC12ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[46], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ADC12 kernel clock
  * @rmtoll XBAR46CFGR         XBAR46EN         LL_RCC_EnableADC12
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableADC12_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[46], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ADC12 kernel clock
  * @rmtoll XBAR46CFGR         XBAR46EN         LL_RCC_DisableADC12
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableADC12_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[46], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get ADC3 clock source select
  * @rmtoll XBAR47CFGR      XBAR47SEL      LL_RCC_GetADC3ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC3ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[47], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ADC3 Clock Source
  * @rmtoll XBAR47CFGR         XBAR47SEL        LL_RCC_SetADC3ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC3ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[47], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ADC3 kernel clock
  * @rmtoll XBAR47CFGR         XBAR47EN         LL_RCC_EnableADC3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableADC3_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[47], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ADC3 kernel clock
  * @rmtoll XBAR47CFGR         XBAR47EN         LL_RCC_DisableADC3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableADC3_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[47], RCC_XBARxCFGR_XBARxEN);
}

#else

/**
  * @brief  Get ADC1 clock source select
  * @rmtoll XBAR46CFGR      XBAR46SEL      LL_RCC_GetADC1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[46], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ADC1 Clock Source
  * @rmtoll XBAR46CFGR         XBAR46SEL        LL_RCC_SetADC1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[46], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ADC1 kernel clock
  * @rmtoll XBAR46CFGR         XBAR46EN         LL_RCC_EnableADC1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableADC1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[46], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ADC1 kernel clock
  * @rmtoll XBAR46CFGR         XBAR46EN         LL_RCC_DisableADC1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableADC1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[46], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get ADC2 clock source select
  * @rmtoll XBAR47CFGR      XBAR47SEL      LL_RCC_GetADC2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[47], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ADC2 Clock Source
  * @rmtoll XBAR47CFGR         XBAR47SEL        LL_RCC_SetADC2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[47], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ADC2 kernel clock
  * @rmtoll XBAR47CFGR         XBAR47EN         LL_RCC_EnableADC2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableADC2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[47], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ADC2 kernel clock
  * @rmtoll XBAR47CFGR         XBAR47EN         LL_RCC_DisableADC2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableADC2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[47], RCC_XBARxCFGR_XBARxEN);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

/**
  * @brief  Get OSPI1 clock source select
  * @rmtoll XBAR48CFGR      XBAR48SEL      LL_RCC_GetOSPI1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetOSPI1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[48], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set OSPI1 Clock Source
  * @rmtoll XBAR48CFGR         XBAR48SEL        LL_RCC_SetOSPI1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetOSPI1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[48], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable OSPI1 kernel clock
  * @rmtoll XBAR48CFGR         XBAR48EN         LL_RCC_EnableOSPI1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableOSPI1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[48], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable OSPI1 kernel clock
  * @rmtoll XBAR48CFGR         XBAR48EN         LL_RCC_DisableOSPI1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableOSPI1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[48], RCC_XBARxCFGR_XBARxEN);
}

#if defined(LL_RCC_OSPI2_CLKSOURCE)
/**
  * @brief  Get OSPI2 clock source select
  * @rmtoll XBAR49CFGR      XBAR49SEL      LL_RCC_GetOSPI2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetOSPI2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[49], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set OSPI2 Clock Source
  * @rmtoll XBAR49CFGR         XBAR49SEL        LL_RCC_SetOSPI2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetOSPI2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[49], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable OSPI2 kernel clock
  * @rmtoll XBAR49CFGR         XBAR49EN         LL_RCC_EnableOSPI2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableOSPI2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[49], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable OSPI2 kernel clock
  * @rmtoll XBAR49CFGR         XBAR49EN         LL_RCC_DisableOSPI2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableOSPI2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[49], RCC_XBARxCFGR_XBARxEN);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

/**
  * @brief  Get FMC clock source select
  * @rmtoll XBAR50CFGR      XBAR50SEL      LL_RCC_GetFMCClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetFMCClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[50], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set FMC Clock Source
  * @rmtoll XBAR50CFGR         XBAR50SEL        LL_RCC_SetFMCClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetFMCClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[50], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable FMC kernel clock
  * @rmtoll XBAR50CFGR         XBAR50EN         LL_RCC_EnableFMC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableFMC_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[50], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable FMC kernel clock
  * @rmtoll XBAR50CFGR         XBAR50EN         LL_RCC_DisableFMC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableFMC_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[50], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get SDMMC1 clock source select
  * @rmtoll XBAR51CFGR      XBAR51SEL      LL_RCC_GetSDMMC1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMC1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[51], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SDMMC1 Clock Source
  * @rmtoll XBAR51CFGR         XBAR51SEL        LL_RCC_SetSDMMC1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSDMMC1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[51], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SDMMC1 kernel clock
  * @rmtoll XBAR51CFGR         XBAR51EN         LL_RCC_EnableSDMMC1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSDMMC1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[51], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SDMMC1 kernel clock
  * @rmtoll XBAR51CFGR         XBAR51EN         LL_RCC_DisableSDMMC1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSDMMC1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[51], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get SDMMC2 clock source select
  * @rmtoll XBAR52CFGR      XBAR52SEL      LL_RCC_GetSDMMC2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMC2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[52], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SDMMC2 Clock Source
  * @rmtoll XBAR52CFGR         XBAR52SEL        LL_RCC_SetSDMMC2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSDMMC2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[52], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SDMMC2 kernel clock
  * @rmtoll XBAR52CFGR         XBAR52EN         LL_RCC_EnableSDMMC2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSDMMC2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[52], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SDMMC2 kernel clock
  * @rmtoll XBAR52CFGR         XBAR52EN         LL_RCC_DisableSDMMC2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSDMMC2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[52], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get SDMMC3 clock source select
  * @rmtoll XBAR53CFGR      XBAR53SEL      LL_RCC_GetSDMMC3ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMC3ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[53], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set SDMMC3 Clock Source
  * @rmtoll XBAR53CFGR         XBAR53SEL        LL_RCC_SetSDMMC3ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSDMMC3ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[53], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable SDMMC3 kernel clock
  * @rmtoll XBAR53CFGR         XBAR53EN         LL_RCC_EnableSDMMC3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSDMMC3_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[53], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable SDMMC3 kernel clock
  * @rmtoll XBAR53CFGR         XBAR53EN         LL_RCC_DisableSDMMC3
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSDMMC3_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[53], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get ETH1 clock source select
  * @rmtoll XBAR54CFGR      XBAR54SEL      LL_RCC_GetETH1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetETH1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[54], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ETH1 Clock Source
  * @rmtoll XBAR54CFGR         XBAR54SEL        LL_RCC_SetETH1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETH1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[54], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ETH1 kernel clock
  * @rmtoll XBAR54CFGR         XBAR54EN         LL_RCC_EnableETH1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableETH1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[54], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ETH1 kernel clock
  * @rmtoll XBAR54CFGR         XBAR54EN         LL_RCC_DisableETH1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableETH1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[54], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get ETH2 clock source select
  * @rmtoll XBAR55CFGR      XBAR55SEL      LL_RCC_GetETH2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetETH2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[55], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ETH2 Clock Source
  * @rmtoll XBAR55CFGR         XBAR55SEL        LL_RCC_SetETH2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETH2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[55], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ETH2 kernel clock
  * @rmtoll XBAR55CFGR         XBAR55EN         LL_RCC_EnableETH2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableETH2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[55], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ETH2 kernel clock
  * @rmtoll XBAR55CFGR         XBAR55EN         LL_RCC_DisableETH2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableETH2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[55], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get ETH1_2_PTP clock source select
  * @rmtoll XBAR56CFGR      XBAR56SEL      LL_RCC_GetETH1_2_PTPClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetETH1_2_PTPClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[56], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ETH1_2_PTP Clock Source
  * @rmtoll XBAR56CFGR         XBAR56SEL        LL_RCC_SetETH1_2_PTPClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETH1_2_PTPClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[56], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ETH1_2_PTP kernel clock
  * @rmtoll XBAR56CFGR         XBAR56EN         LL_RCC_EnableETH1_2_PTP
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableETH1_2_PTP_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[56], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ETH1_2_PTP kernel clock
  * @rmtoll XBAR56CFGR         XBAR56EN         LL_RCC_DisableETH1_2_PTP
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableETH1_2_PTP_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[56], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get USB2PHY1 clock source select
  * @rmtoll XBAR57CFGR      XBAR57SEL      LL_RCC_GetUSB2PHY1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSB2PHY1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[57], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USB2PHY1 Clock Source
  * @rmtoll XBAR57CFGR         XBAR57SEL        LL_RCC_SetUSB2PHY1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSB2PHY1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[57], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USB2PHY1 kernel clock
  * @rmtoll XBAR57CFGR         XBAR57EN         LL_RCC_EnableUSB2PHY1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSB2PHY1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[57], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USB2PHY1 kernel clock
  * @rmtoll XBAR57CFGR         XBAR57EN         LL_RCC_DisableUSB2PHY1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSB2PHY1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[57], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get USB2PHY2 clock source select
  * @rmtoll XBAR58CFGR      XBAR58SEL      LL_RCC_GetUSB2PHY2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSB2PHY2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[58], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set USB2PHY2 Clock Source
  * @rmtoll XBAR58CFGR         XBAR58SEL        LL_RCC_SetUSB2PHY2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSB2PHY2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[58], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable USB2PHY2 kernel clock
  * @rmtoll XBAR58CFGR         XBAR58EN         LL_RCC_EnableUSB2PHY2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSB2PHY2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[58], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable USB2PHY2 kernel clock
  * @rmtoll XBAR58CFGR         XBAR58EN         LL_RCC_DisableUSB2PHY2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSB2PHY2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[58], RCC_XBARxCFGR_XBARxEN);
}


/**
  * @brief  Get ETHSWCFG clock source select
  * @rmtoll XBAR59CFGR      XBAR59SEL      LL_RCC_GetETHSWCFGClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHSWCFGClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[59], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ETHSWCFG Clock Source
  * @rmtoll XBAR59CFGR         XBAR59SEL        LL_RCC_SetETHSWCFGClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETHSWCFGClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[59], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ETHSWCFG kernel clock
  * @rmtoll XBAR59CFGR         XBAR59EN         LL_RCC_EnableETHSWCFG
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableETHSWCFG_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[59], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ETHSWCFG kernel clock
  * @rmtoll XBAR59CFGR         XBAR59EN         LL_RCC_DisableETHSWCFG
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableETHSWCFG_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[59], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get ETHSWMSG clock source select
  * @rmtoll XBAR60CFGR      XBAR60SEL      LL_RCC_GetETHSWMSGClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHSWMSGClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[60], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set ETHSWMSG Clock Source
  * @rmtoll XBAR60CFGR         XBAR60SEL        LL_RCC_SetETHSWMSGClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETHSWMSGClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[60], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable ETHSWMSG kernel clock
  * @rmtoll XBAR60CFGR         XBAR60EN         LL_RCC_EnableETHSWMSG
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableETHSWMSG_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[60], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable ETHSWMSG kernel clock
  * @rmtoll XBAR60CFGR         XBAR60EN         LL_RCC_DisableETHSWMSG
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableETHSWMSG_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[60], RCC_XBARxCFGR_XBARxEN);
}


/**
  * @brief  Get MCO1 clock source select
  * @rmtoll XBAR61CFGR      XBAR61SEL      LL_RCC_GetMCO1ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetMCO1ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[61], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set MCO1 Clock Source
  * @rmtoll XBAR61CFGR         XBAR61SEL        LL_RCC_SetMCO1ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetMCO1ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[61], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable MCO1 kernel clock
  * @rmtoll XBAR61CFGR         XBAR61EN         LL_RCC_EnableMCO1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableMCO1_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[61], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable MCO1 kernel clock
  * @rmtoll XBAR61CFGR         XBAR61EN         LL_RCC_DisableMCO1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableMCO1_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[61], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get MCO2 clock source select
  * @rmtoll XBAR62CFGR      XBAR62SEL      LL_RCC_GetMCO2ClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetMCO2ClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[62], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set MCO2 Clock Source
  * @rmtoll XBAR62CFGR         XBAR62SEL        LL_RCC_SetMCO2ClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetMCO2ClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[62], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable MCO2 kernel clock
  * @rmtoll XBAR62CFGR         XBAR62EN         LL_RCC_EnableMCO2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableMCO2_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[62], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable MCO2 kernel clock
  * @rmtoll XBAR62CFGR         XBAR62EN         LL_RCC_DisableMCO2
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableMCO2_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[62], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Get CPU1EXT2F clock source select
  * @rmtoll XBAR63CFGR      XBAR63SEL      LL_RCC_GetCPU1EXT2FClockSource
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetCPU1EXT2FClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->XBARxCFGR[63], RCC_XBARxCFGR_XBARxSEL_Msk));
}

/**
  * @brief  Set CPU1EXT2F Clock Source
  * @rmtoll XBAR63CFGR         XBAR63SEL        LL_RCC_SetCPU1EXT2FClockSource
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL4_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL5_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL6_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL7_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_PLL8_FOUTPOSTDIV
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSE
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_HSEKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_MSIKER
  *        @arg @ref LL_RCC_XBAR_CLKSRC_SPDIF
  *        @arg @ref LL_RCC_XBAR_CLKSRC_I2S
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSI
  *        @arg @ref LL_RCC_XBAR_CLKSRC_LSE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCPU1EXT2FClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->XBARxCFGR[63], RCC_XBARxCFGR_XBARxSEL_Msk, Source);
}

/**
  * @brief  Enable CPU1EXT2F kernel clock
  * @rmtoll XBAR63CFGR         XBAR63EN         LL_RCC_EnableCPU1EXT2F
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableCPU1EXT2F_KerClk(void)
{
  SET_BIT(RCC->XBARxCFGR[63], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @brief  Disable CPU1EXT2F kernel clock
  * @rmtoll XBAR63CFGR         XBAR63EN         LL_RCC_DisableCPU1EXT2F
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableCPU1EXT2F_KerClk(void)
{
  CLEAR_BIT(RCC->XBARxCFGR[63], RCC_XBARxCFGR_XBARxEN);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_Divider_Clock_Configuration Peripheral Clock Divider Configuration
  * @{
  */
/**
  * @brief  Get LPTIM1_2 channel pre divided Value
  * @rmtoll PREDIV7CFGR      PREDIV7      LL_RCC_GetLPTIM1_2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM1_2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[7], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set LPTIM1_2 channel pre divided Value
  * @rmtoll PREDIV7CFGR         PREDIV7        LL_RCC_SetLPTIM1_2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM1_2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[7], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get LPTIM1_2 channel pre divided Value
  * @rmtoll FINDIV7CFGR      FINDIV7      LL_RCC_GetLPTIM1_2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM1_2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[7], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set LPTIM1_2 channel pre divided Value
  * @rmtoll FINDIV7CFGR         FINDIV7        LL_RCC_SetLPTIM1_2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM1_2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[7], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable LPTIM1_2 final divider channel
  * @rmtoll FINDIV7CFGR         FINDIV7EN         LL_RCC_EnableLPTIM1_2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPTIM1_2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[7], RCC_FINDIVxCFGR_FINDIVxEN);
}

/**
  * @brief  Disable LPTIM1_2 final divider channel
  * @rmtoll FINDIV7CFGR         FINDIV7EN         LL_RCC_DisableLPTIM1_2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPTIM1_2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[7], RCC_FINDIVxCFGR_FINDIVxEN);
}

/**
  * @brief  Get USART2_4 channel pre divided Value
  * @rmtoll PREDIV8CFGR      PREDIV8      LL_RCC_GetUSART2_4_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART2_4_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[8], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USART2_4 channel pre divided Value
  * @rmtoll PREDIV8CFGR         PREDIV8        LL_RCC_SetUSART2_4_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART2_4_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[8], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USART2_4 channel pre divided Value
  * @rmtoll FINDIV8CFGR      FINDIV8      LL_RCC_GetUSART2_4_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART2_4_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[8], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USART2_4 channel pre divided Value
  * @rmtoll FINDIV8CFGR         FINDIV8        LL_RCC_SetUSART2_4_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART2_4_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[8], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USART2_4 final divider channel
  * @rmtoll FINDIV8CFGR         FINDIV8EN         LL_RCC_EnableUSART2_4_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART2_4_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[8], RCC_FINDIVxCFGR_FINDIVxEN);
}

/**
  * @brief  Disable USART2_4 final divider channel
  * @rmtoll FINDIV8CFGR         FINDIV8EN         LL_RCC_DisableUSART2_4_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART2_4_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[8], RCC_FINDIVxCFGR_FINDIVxEN);
}

/**
  * @brief  Get USART3_5 channel pre divided Value
  * @rmtoll PREDIV9CFGR      PREDIV9      LL_RCC_GetUSART3_5_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART3_5_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[9], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USART3_5 channel pre divided Value
  * @rmtoll PREDIV9CFGR         PREDIV9        LL_RCC_SetUSART3_5_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART3_5_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[9], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USART3_5 channel pre divided Value
  * @rmtoll FINDIV9CFGR      FINDIV9      LL_RCC_GetUSART3_5_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART3_5_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[9], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USART3_5 channel pre divided Value
  * @rmtoll FINDIV9CFGR         FINDIV9        LL_RCC_SetUSART3_5_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART3_5_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[9], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USART3_5 final divider channel
  * @rmtoll FINDIV9CFGR         FINDIV9EN         LL_RCC_EnableUSART3_5_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART3_5_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[9], RCC_FINDIVxCFGR_FINDIVxEN);
}

/**
  * @brief  Disable USART3_5 final divider channel
  * @rmtoll FINDIV9CFGR         FINDIV9EN         LL_RCC_DisableUSART3_5_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART3_5_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[9], RCC_FINDIVxCFGR_FINDIVxEN);
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get UART7_8 channel pre divided Value
  * @rmtoll PREDIV21CFGR      PREDIV21      LL_RCC_GetUART7_8_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART7_8_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[21], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Get UART7_8 channel fin divided Value
  * @rmtoll FINDIV21CFGR      FINDIV21      LL_RCC_GetUSART7_8_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART7_8_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[21], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

#else

/**
  * @brief  Get UART7 channel pre divided Value
  * @rmtoll PREDIV21CFGR      PREDIV21      LL_RCC_GetUART7_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART7_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[21], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Get UART7 channel fin divided Value
  * @rmtoll FINDIV21CFGR      FINDIV21      LL_RCC_GetUSART7_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART7_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[21], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING) && !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get UART9 channel pre divided Value
  * @rmtoll PREDIV22CFGR      PREDIV22      LL_RCC_GetUART9_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART9_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[22], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Get UART9 channel fin divided Value
  * @rmtoll FINDIV22CFGR      FINDIV22      LL_RCC_GetUSART9_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART9_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[22], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SPI2_3 channel pre divided Value
  * @rmtoll PREDIV10CFGR      PREDIV10      LL_RCC_GetSPI2_3_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI2_3_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[10], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SPI2_3 channel pre divided Value
  * @rmtoll PREDIV10CFGR         PREDIV10        LL_RCC_SetSPI2_3_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI2_3_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[10], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SPI2_3 channel pre divided Value
  * @rmtoll FINDIV10CFGR      FINDIV10      LL_RCC_GetSPI2_3_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI2_3_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[10], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SPI2_3 channel pre divided Value
  * @rmtoll FINDIV10CFGR         FINDIV10        LL_RCC_SetSPI2_3_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI2_3_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[10], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SPI2_3 final divider channel
  * @rmtoll FINDIV10CFGR         FINDIV10EN         LL_RCC_EnableSPI2_3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI2_3_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[10], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SPI2_3 final divider channel
  * @rmtoll FINDIV10CFGR         FINDIV10EN         LL_RCC_DisableSPI2_3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI2_3_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[10], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#else
/**
  * @brief  Get SPI2 channel pre divided Value
  * @rmtoll PREDIV10CFGR      PREDIV10      LL_RCC_GetSPI2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[10], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SPI2 channel pre divided Value
  * @rmtoll PREDIV10CFGR         PREDIV10        LL_RCC_SetSPI2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[10], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SPI2 channel pre divided Value
  * @rmtoll FINDIV10CFGR      FINDIV10      LL_RCC_GetSPI2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[10], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SPI2 channel pre divided Value
  * @rmtoll FINDIV10CFGR         FINDIV10        LL_RCC_SetSPI2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[10], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SPI2 final divider channel
  * @rmtoll FINDIV10CFGR         FINDIV10EN         LL_RCC_EnableSPI2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[10], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SPI2 final divider channel
  * @rmtoll FINDIV10CFGR         FINDIV10EN         LL_RCC_DisableSPI2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[10], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get SPI3 channel pre divided Value
  * @rmtoll PREDIV11CFGR      PREDIV11      LL_RCC_GetSPI3_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI3_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[11], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SPI3 channel pre divided Value
  * @rmtoll PREDIV11CFGR         PREDIV11        LL_RCC_SetSPI3_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI3_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[11], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SPI3 channel pre divided Value
  * @rmtoll FINDIV11CFGR      FINDIV11      LL_RCC_GetSPI3_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI3_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[11], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SPI3 channel pre divided Value
  * @rmtoll FINDIV11CFGR         FINDIV11        LL_RCC_SetSPI3_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI3_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[11], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SPI3 final divider channel
  * @rmtoll FINDIV11CFGR         FINDIV11EN         LL_RCC_EnableSPI3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI3_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[11], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SPI3 final divider channel
  * @rmtoll FINDIV11CFGR         FINDIV11EN         LL_RCC_DisableSPI3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI3_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[11], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined (RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SPIDFRX channel pre divided Value
  * @rmtoll PREDIV11CFGR      PREDIV11      LL_RCC_GetSPIDFRX_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPDIFRX_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[11], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SPIDFRX channel pre divided Value
  * @rmtoll PREDIV11CFGR         PREDIV11        LL_RCC_SetSPIDFRX_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPDIFRX_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[11], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SPIDFRX channel pre divided Value
  * @rmtoll FINDIV11CFGR      FINDIV11      LL_RCC_GetSPIDFRX_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPDIFRX_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[11], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SPIDFRX channel pre divided Value
  * @rmtoll FINDIV11CFGR         FINDIV11        LL_RCC_SetSPIDFRX_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPIDFRX_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[11], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SPIDFRX final divider channel
  * @rmtoll FINDIV11CFGR         FINDIV11EN         LL_RCC_EnableSPIDFRX_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPIDFRX_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[11], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SPIDFRX final divider channel
  * @rmtoll FINDIV11CFGR         FINDIV11EN         LL_RCC_DisableSPIDFRX_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPDIFRX_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[11], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#else
/**
  * @brief  Get SPIDFRX channel pre divided Value
  * @rmtoll PREDIV12CFGR      PREDIV12      LL_RCC_GetSPIDFRX_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPDIFRX_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[12], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SPIDFRX channel pre divided Value
  * @rmtoll PREDIV12CFGR         PREDIV12        LL_RCC_SetSPIDFRX_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPDIFRX_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[12], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SPIDFRX channel pre divided Value
  * @rmtoll FINDIV12CFGR      FINDIV12      LL_RCC_GetSPIDFRX_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPDIFRX_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[12], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SPIDFRX channel pre divided Value
  * @rmtoll FINDIV12CFGR         FINDIV12        LL_RCC_SetSPIDFRX_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPIDFRX_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[12], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SPIDFRX final divider channel
  * @rmtoll FINDIV12CFGR         FINDIV12EN         LL_RCC_EnableSPIDFRX_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPIDFRX_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[12], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SPIDFRX final divider channel
  * @rmtoll FINDIV12CFGR         FINDIV12EN         LL_RCC_DisableSPIDFRX_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPDIFRX_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[12], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get I2C1_2_I3C1_2 channel pre divided Value
  * @rmtoll PREDIV12CFGR      PREDIV12      LL_RCC_GetI2C1_2_I3C1_2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C1_2_I3C1_2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[12], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set I2C1_2_I3C1_2 channel pre divided Value
  * @rmtoll PREDIV12CFGR         PREDIV12        LL_RCC_SetI2C1_2_I3C1_2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C1_2_I3C1_2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[12], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get I2C1_2_I3C1_2 channel pre divided Value
  * @rmtoll FINDIV12CFGR      FINDIV12      LL_RCC_GetI2C1_2_I3C1_2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C1_2_I3C1_2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[12], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set I2C1_2_I3C1_2 channel pre divided Value
  * @rmtoll FINDIV12CFGR         FINDIV12        LL_RCC_SetI2C1_2_I3C1_2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C1_2_I3C1_2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[12], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable I2C1_2_I3C1_2 final divider channel
  * @rmtoll FINDIV12CFGR         FINDIV12EN         LL_RCC_EnableI2C1_2_I3C1_2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C1_2_I3C1_2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[12], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable I2C1_2_I3C1_2 final divider channel
  * @rmtoll FINDIV12CFGR         FINDIV12EN         LL_RCC_DisableI2C1_2_I3C1_2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C1_2_I3C1_2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[12], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#else

/**
  * @brief  Get I2C1_2 channel pre divided Value
  * @rmtoll PREDIV13CFGR      PREDIV13      LL_RCC_GetI2C1_2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C1_2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[13], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set I2C1_2 channel pre divided Value
  * @rmtoll PREDIV13CFGR         PREDIV13        LL_RCC_SetI2C1_2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C1_2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[13], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get I2C1_2 channel pre divided Value
  * @rmtoll FINDIV13CFGR      FINDIV13      LL_RCC_GetI2C1_2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C1_2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[13], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set I2C1_2 channel pre divided Value
  * @rmtoll FINDIV13CFGR         FINDIV13        LL_RCC_SetI2C1_2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C1_2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[13], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable I2C1_2 final divider channel
  * @rmtoll FINDIV13CFGR         FINDIV13EN         LL_RCC_EnableI2C1_2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C1_2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[13], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable I2C1_2 final divider channel
  * @rmtoll FINDIV13CFGR         FINDIV13EN         LL_RCC_DisableI2C1_2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C1_2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[13], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get I3C1_2 channel pre divided Value
  * @rmtoll PREDIV14CFGR      PREDIV14      LL_RCC_GetI3C1_2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3C1_2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[14], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set I3C1_2 channel pre divided Value
  * @rmtoll PREDIV14CFGR         PREDIV14        LL_RCC_SetI3C1_2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3C1_2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[14], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get I3C1_2 channel pre divided Value
  * @rmtoll FINDIV14CFGR      FINDIV14      LL_RCC_GetI3C1_2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3C1_2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[14], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set I3C1_2 channel pre divided Value
  * @rmtoll FINDIV14CFGR         FINDIV14        LL_RCC_SetI3C1_2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3C1_2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[14], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable I3C1_2 final divider channel
  * @rmtoll FINDIV14CFGR         FINDIV14EN         LL_RCC_EnableI3C1_2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI3C1_2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[14], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable I3C1_2 final divider channel
  * @rmtoll FINDIV14CFGR         FINDIV14EN         LL_RCC_DisableI3C1_2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI3C1_2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[14], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get I2C3_5_I3C3 channel pre divided Value
  * @rmtoll PREDIV13CFGR      PREDIV13      LL_RCC_GetI2C3_5_I3C3_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C3_5_I3C3_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[13], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set I2C3_5_I3C3 channel pre divided Value
  * @rmtoll PREDIV13CFGR         PREDIV13        LL_RCC_SetI2C3_5_I3C3_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C3_5_I3C3_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[13], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get I2C3_5_I3C3 channel pre divided Value
  * @rmtoll FINDIV13CFGR      FINDIV13      LL_RCC_GetI2C3_5_I3C3_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C3_5_I3C3_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[13], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set I2C3_5_I3C3 channel pre divided Value
  * @rmtoll FINDIV13CFGR         FINDIV13        LL_RCC_SetI2C3_5_I3C3_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C3_5_I3C3_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[13], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable I2C3_5_I3C3 final divider channel
  * @rmtoll FINDIV13CFGR         FINDIV13EN         LL_RCC_EnableI2C3_5_I3C3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C3_5_I3C3_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[13], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable I2C3_5_I3C3 final divider channel
  * @rmtoll FINDIV13CFGR         FINDIV13EN         LL_RCC_DisableI2C3_5_I3C3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C3_5_I3C3_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[13], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#else

/**
  * @brief  Get I2C3 channel pre divided Value
  * @rmtoll PREDIV38CFGR      PREDIV38      LL_RCC_GetI2C3_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C3_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[38], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set I2C3 channel pre divided Value
  * @rmtoll PREDIV38CFGR         PREDIV38        LL_RCC_SetI2C3_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C3_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[38], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get I2C3 channel pre divided Value
  * @rmtoll FINDIV38CFGR      FINDIV38      LL_RCC_GetI2C3_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C3_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[38], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set I2C3 channel pre divided Value
  * @rmtoll FINDIV38CFGR         FINDIV38        LL_RCC_SetI2C3_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C3_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[38], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable I2C3 final divider channel
  * @rmtoll FINDIV38CFGR         FINDIV38EN         LL_RCC_EnableI2C3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C3_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[38], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable I2C3 final divider channel
  * @rmtoll FINDIV38CFGR         FINDIV38EN         LL_RCC_DisableI2C3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C3_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[38], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get I3C3 channel pre divided Value
  * @rmtoll PREDIV36CFGR      PREDIV36      LL_RCC_GetI3C3_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3C3_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[36], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set I3C3 channel pre divided Value
  * @rmtoll PREDIV36CFGR         PREDIV36        LL_RCC_SetI3C3_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3C3_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[36], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get I3C3 channel pre divided Value
  * @rmtoll FINDIV36CFGR      FINDIV36      LL_RCC_GetI3C3_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3C3_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[36], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set I3C3 channel pre divided Value
  * @rmtoll FINDIV36CFGR         FINDIV36        LL_RCC_SetI3C3_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3C3_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[36], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable I3C3 final divider channel
  * @rmtoll FINDIV36CFGR         FINDIV36EN         LL_RCC_EnableI3C3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI3C3_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[36], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable I3C3 final divider channel
  * @rmtoll FINDIV36CFGR         FINDIV36EN         LL_RCC_DisableI3C3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI3C3_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[36], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
#endif /* RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING */


#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING) && !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)

/**
  * @brief  Get I2C4_6 channel pre divided Value
  * @rmtoll PREDIV14CFGR      PREDIV14      LL_RCC_GetI2C4_6_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C4_6_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[14], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set I2C4_6 channel pre divided Value
  * @rmtoll PREDIV14CFGR         PREDIV14        LL_RCC_SetI2C4_6_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C4_6_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[14], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get I2C4_6 channel pre divided Value
  * @rmtoll FINDIV14CFGR      FINDIV14      LL_RCC_GetI2C4_6_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C4_6_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[14], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set I2C4_6 channel pre divided Value
  * @rmtoll FINDIV14CFGR         FINDIV14        LL_RCC_SetI2C4_6_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C4_6_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[14], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable I2C4_6 final divider channel
  * @rmtoll FINDIV14CFGR         FINDIV14EN         LL_RCC_EnableI2C4_6_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C4_6_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[14], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable I2C4_6 final divider channel
  * @rmtoll FINDIV14CFGR         FINDIV14EN         LL_RCC_DisableI2C4_6_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C4_6_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[14], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get I2C7 channel pre divided Value
  * @rmtoll PREDIV15CFGR      PREDIV15      LL_RCC_GetI2C7_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C7_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[15], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set I2C7 channel pre divided Value
  * @rmtoll PREDIV15CFGR         PREDIV15        LL_RCC_SetI2C7_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C7_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[15], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get I2C7 channel pre divided Value
  * @rmtoll FINDIV15CFGR      FINDIV15      LL_RCC_GetI2C7_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C7_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[15], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set I2C7 channel pre divided Value
  * @rmtoll FINDIV15CFGR         FINDIV15        LL_RCC_SetI2C7_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C7_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[15], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable I2C7 final divider channel
  * @rmtoll FINDIV15CFGR         FINDIV15EN         LL_RCC_EnableI2C7_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C7_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[15], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable I2C7 final divider channel
  * @rmtoll FINDIV15CFGR         FINDIV15EN         LL_RCC_DisableI2C7_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C7_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[15], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

/**
  * @brief  Get SPI1 channel pre divided Value
  * @rmtoll PREDIV16CFGR      PREDIV16      LL_RCC_GetSPI1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[16], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SPI1 channel pre divided Value
  * @rmtoll PREDIV16CFGR         PREDIV16        LL_RCC_SetSPI1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[16], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SPI1 channel pre divided Value
  * @rmtoll FINDIV16CFGR      FINDIV16      LL_RCC_GetSPI1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[16], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SPI1 channel pre divided Value
  * @rmtoll FINDIV16CFGR         FINDIV16        LL_RCC_SetSPI1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[16], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SPI1 final divider channel
  * @rmtoll FINDIV16CFGR         FINDIV16EN         LL_RCC_EnableSPI1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[16], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SPI1 final divider channel
  * @rmtoll FINDIV16CFGR         FINDIV16EN         LL_RCC_DisableSPI1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[16], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get SPI4_5 channel pre divided Value
  * @rmtoll PREDIV17CFGR      PREDIV17      LL_RCC_GetSPI4_5_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI4_5_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[17], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SPI4_5 channel pre divided Value
  * @rmtoll PREDIV17CFGR         PREDIV17        LL_RCC_SetSPI4_5_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI4_5_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[17], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SPI4_5 channel pre divided Value
  * @rmtoll FINDIV17CFGR      FINDIV17      LL_RCC_GetSPI4_5_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI4_5_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[17], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SPI4_5 channel pre divided Value
  * @rmtoll FINDIV17CFGR         FINDIV17        LL_RCC_SetSPI4_5_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI4_5_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[17], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SPI4_5 final divider channel
  * @rmtoll FINDIV17CFGR         FINDIV17EN         LL_RCC_EnableSPI4_5_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI4_5_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[17], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SPI4_5 final divider channel
  * @rmtoll FINDIV17CFGR         FINDIV17EN         LL_RCC_DisableSPI4_5_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI4_5_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[17], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#if !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)

/**
  * @brief  Get SPI6_7 channel pre divided Value
  * @rmtoll PREDIV18CFGR      PREDIV18      LL_RCC_GetSPI6_7_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI6_7_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[18], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SPI6_7 channel pre divided Value
  * @rmtoll PREDIV18CFGR         PREDIV18        LL_RCC_SetSPI6_7_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI6_7_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[18], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SPI6_7 channel pre divided Value
  * @rmtoll FINDIV18CFGR      FINDIV18      LL_RCC_GetSPI6_7_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI6_7_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[18], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SPI6_7 channel pre divided Value
  * @rmtoll FINDIV18CFGR         FINDIV18        LL_RCC_SetSPI6_7_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI6_7_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[18], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SPI6_7 final divider channel
  * @rmtoll FINDIV18CFGR         FINDIV18EN         LL_RCC_EnableSPI6_7_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI6_7_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[18], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SPI6_7 final divider channel
  * @rmtoll FINDIV18CFGR         FINDIV18EN         LL_RCC_DisableSPI6_7_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI6_7_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[18], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#else
/**
  * @brief  Get SPI6 channel pre divided Value
  * @rmtoll PREDIV37CFGR      PREDIV37      LL_RCC_GetSPI6_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI6_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[37], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SPI6 channel pre divided Value
  * @rmtoll PREDIV37CFGR         PREDIV37        LL_RCC_SetSPI6_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI6_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[37], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SPI6 channel pre divided Value
  * @rmtoll FINDIV37CFGR      FINDIV37      LL_RCC_GetSPI6_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI6_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[37], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SPI6 channel pre divided Value
  * @rmtoll FINDIV37CFGR         FINDIV37        LL_RCC_SetSPI6_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI6_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[37], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SPI6 final divider channel
  * @rmtoll FINDIV37CFGR         FINDIV37EN         LL_RCC_EnableSPI6_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI6_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[37], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SPI6 final divider channel
  * @rmtoll FINDIV37CFGR         FINDIV37EN         LL_RCC_DisableSPI6_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI6_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[37], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
#endif /* RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get USART1 channel pre divided Value
  * @rmtoll PREDIV19CFGR      PREDIV19      LL_RCC_GetUSART1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[19], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USART1 channel pre divided Value
  * @rmtoll PREDIV19CFGR         PREDIV19        LL_RCC_SetUSART1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[19], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USART1 channel pre divided Value
  * @rmtoll FINDIV19CFGR      FINDIV19      LL_RCC_GetUSART1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[19], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USART1 channel pre divided Value
  * @rmtoll FINDIV19CFGR         FINDIV19        LL_RCC_SetUSART1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[19], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USART1 final divider channel
  * @rmtoll FINDIV19CFGR         FINDIV19EN         LL_RCC_EnableUSART1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[19], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable USART1 final divider channel
  * @rmtoll FINDIV19CFGR         FINDIV19EN         LL_RCC_DisableUSART1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[19], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#else
/**
  * @brief  Get USART1 channel pre divided Value
  * @rmtoll PREDIV18CFGR      PREDIV18      LL_RCC_GetUSART1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[18], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USART1 channel pre divided Value
  * @rmtoll PREDIV18CFGR         PREDIV18        LL_RCC_SetUSART1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[18], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USART1 channel pre divided Value
  * @rmtoll FINDIV18CFGR      FINDIV18      LL_RCC_GetUSART1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[18], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USART1 channel pre divided Value
  * @rmtoll FINDIV18CFGR         FINDIV18        LL_RCC_SetUSART1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[18], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USART1 final divider channel
  * @rmtoll FINDIV18CFGR         FINDIV18EN         LL_RCC_EnableUSART1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[18], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable USART1 final divider channel
  * @rmtoll FINDIV18CFGR         FINDIV18EN         LL_RCC_DisableUSART1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[18], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

/**
  * @brief  Get UART2_4 channel pre divided Value
  * @rmtoll PREDIV8CFGR      PREDIV8      LL_RCC_GetUART2_4_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART2_4_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[8], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Get UART2_4 channel fin divided Value
  * @rmtoll FINDIV8CFGR      FINDIV8      LL_RCC_GetUART2_2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUART2_4_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[8], RCC_FINDIVxCFGR_FINDIVx_Msk));
}
#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get USART6 channel pre divided Value
  * @rmtoll PREDIV20CFGR      PREDIV20      LL_RCC_GetUSART6_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART6_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[20], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USART6 channel pre divided Value
  * @rmtoll PREDIV20CFGR         PREDIV20        LL_RCC_SetUSART6_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART6_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[20], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USART6 channel pre divided Value
  * @rmtoll FINDIV20CFGR      FINDIV20      LL_RCC_GetUSART6_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART6_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[20], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USART6 channel pre divided Value
  * @rmtoll FINDIV20CFGR         FINDIV20        LL_RCC_SetUSART6_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART6_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[20], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USART6 final divider channel
  * @rmtoll FINDIV20CFGR         FINDIV20EN         LL_RCC_EnableUSART6_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART6_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[20], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable USART6 final divider channel
  * @rmtoll FINDIV20CFGR         FINDIV20EN         LL_RCC_DisableUSART6_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART6_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[20], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#else
/**
  * @brief  Get USART6 channel pre divided Value
  * @rmtoll PREDIV19CFGR      PREDIV19      LL_RCC_GetUSART6_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART6_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[19], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USART6 channel pre divided Value
  * @rmtoll PREDIV19CFGR         PREDIV19        LL_RCC_SetUSART6_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART6_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[19], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USART6 channel pre divided Value
  * @rmtoll FINDIV19CFGR      FINDIV19      LL_RCC_GetUSART6_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART6_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[19], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USART6 channel pre divided Value
  * @rmtoll FINDIV19CFGR         FINDIV19        LL_RCC_SetUSART6_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART6_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[19], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USART6 final divider channel
  * @rmtoll FINDIV19CFGR         FINDIV19EN         LL_RCC_EnableUSART6_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART6_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[19], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable USART6 final divider channel
  * @rmtoll FINDIV19CFGR         FINDIV19EN         LL_RCC_DisableUSART6_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART6_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[19], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get USART7_8 channel pre divided Value
  * @rmtoll PREDIV21CFGR      PREDIV21      LL_RCC_GetUSART7_8_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART7_8_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[21], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USART7_8 channel pre divided Value
  * @rmtoll PREDIV21CFGR         PREDIV21        LL_RCC_SetUSART7_8_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART7_8_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[21], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USART7_8 channel pre divided Value
  * @rmtoll FINDIV21CFGR      FINDIV21      LL_RCC_GetUSART7_8_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART7_8_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[21], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USART7_8 channel pre divided Value
  * @rmtoll FINDIV21CFGR         FINDIV21        LL_RCC_SetUSART7_8_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART7_8_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[21], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USART7_8 final divider channel
  * @rmtoll FINDIV21CFGR         FINDIV21EN         LL_RCC_EnableUSART7_8_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART7_8_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[21], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable USART7_8 final divider channel
  * @rmtoll FINDIV21CFGR         FINDIV21EN         LL_RCC_DisableUSART7_8_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART7_8_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[21], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#else

/**
  * @brief  Get USART7 channel pre divided Value
  * @rmtoll PREDIV20CFGR      PREDIV20      LL_RCC_GetUSART7_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART7_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[20], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USART7 channel pre divided Value
  * @rmtoll PREDIV20CFGR         PREDIV20        LL_RCC_SetUSART7_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART7_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[20], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USART7 channel pre divided Value
  * @rmtoll FINDIV20CFGR      FINDIV20      LL_RCC_GetUSART7_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART7_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[20], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USART7 channel pre divided Value
  * @rmtoll FINDIV20CFGR         FINDIV20        LL_RCC_SetUSART7_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART7_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[20], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USART7 final divider channel
  * @rmtoll FINDIV20CFGR         FINDIV20EN         LL_RCC_EnableUSART7_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART7_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[20], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable USART7 final divider channel
  * @rmtoll FINDIV20CFGR         FINDIV20EN         LL_RCC_DisableUSART7_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART7_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[20], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING) && !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get USART9 channel pre divided Value
  * @rmtoll PREDIV22CFGR      PREDIV22      LL_RCC_GetUSART9_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART9_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[22], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USART9 channel pre divided Value
  * @rmtoll PREDIV22CFGR         PREDIV22        LL_RCC_SetUSART9_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART9_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[22], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USART9 channel pre divided Value
  * @rmtoll FINDIV22CFGR      FINDIV22      LL_RCC_GetUSART9_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSART9_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[22], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USART9 channel pre divided Value
  * @rmtoll FINDIV22CFGR         FINDIV22        LL_RCC_SetUSART9_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSART9_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[22], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USART9 final divider channel
  * @rmtoll FINDIV22CFGR         FINDIV22EN         LL_RCC_EnableUSART9_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSART9_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[22], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable USART9 final divider channel
  * @rmtoll FINDIV22CFGR         FINDIV22EN         LL_RCC_DisableUSART9_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSART9_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[22], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */


#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SAI1_MDF1 channel pre divided Value
  * @rmtoll PREDIV23CFGR      PREDIV23      LL_RCC_GetSAI1_MDF1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI1_MDF1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[23], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SAI1_MDF1 channel pre divided Value
  * @rmtoll PREDIV23CFGR         PREDIV23        LL_RCC_SetSAI1_MDF1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI1_MDF1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[23], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SAI1_MDF1 channel pre divided Value
  * @rmtoll FINDIV23CFGR      FINDIV23      LL_RCC_GetSAI1_MDF1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI1_MDF1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[23], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SAI1_MDF1 channel pre divided Value
  * @rmtoll FINDIV23CFGR         FINDIV23        LL_RCC_SetSAI1_MDF1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI1_MDF1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[23], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SAI1_MDF1 final divider channel
  * @rmtoll FINDIV23CFGR         FINDIV23EN         LL_RCC_EnableSAI1_MDF1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI1_MDF1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[23], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SAI1_MDF1 final divider channel
  * @rmtoll FINDIV23CFGR         FINDIV23EN         LL_RCC_DisableSAI1_MDF1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI1_MDF1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[23], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#else

/**
  * @brief  Get MDF1 channel pre divided Value
  * @rmtoll PREDIV21CFGR      PREDIV21      LL_RCC_GetMDF1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetMDF1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[21], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set MDF1 channel pre divided Value
  * @rmtoll PREDIV21CFGR         PREDIV21        LL_RCC_SetMDF1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetMDF1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[21], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get MDF1 channel pre divided Value
  * @rmtoll FINDIV21CFGR      FINDIV21      LL_RCC_GetMDF1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetMDF1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[21], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set MDF1 channel pre divided Value
  * @rmtoll FINDIV21CFGR         FINDIV21        LL_RCC_SetMDF1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetMDF1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[21], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable MDF1 final divider channel
  * @rmtoll FINDIV21CFGR         FINDIV21EN         LL_RCC_EnableMDF1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableMDF1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[21], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable MDF1 final divider channel
  * @rmtoll FINDIV21CFGR         FINDIV21EN         LL_RCC_DisableMDF1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableMDF1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[21], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get SAI1 channel pre divided Value
  * @rmtoll PREDIV22CFGR      PREDIV22      LL_RCC_GetSAI1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[22], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SAI1 channel pre divided Value
  * @rmtoll PREDIV22CFGR         PREDIV22        LL_RCC_SetSAI1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[22], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SAI1 channel pre divided Value
  * @rmtoll FINDIV22CFGR      FINDIV22      LL_RCC_GetSAI1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[22], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SAI1 channel pre divided Value
  * @rmtoll FINDIV22CFGR         FINDIV22        LL_RCC_SetSAI1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[22], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SAI1 final divider channel
  * @rmtoll FINDIV22CFGR         FINDIV22EN         LL_RCC_EnableSAI1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[22], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SAI1 final divider channel
  * @rmtoll FINDIV22CFGR         FINDIV22EN         LL_RCC_DisableSAI1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[22], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SAI2 channel pre divided Value
  * @rmtoll PREDIV24CFGR      PREDIV24      LL_RCC_GetSAI2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[24], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SAI2 channel pre divided Value
  * @rmtoll PREDIV24CFGR         PREDIV24        LL_RCC_SetSAI2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[24], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SAI2 channel pre divided Value
  * @rmtoll FINDIV24CFGR      FINDIV24      LL_RCC_GetSAI2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[24], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SAI2 channel pre divided Value
  * @rmtoll FINDIV24CFGR         FINDIV24        LL_RCC_SetSAI2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[24], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SAI2 final divider channel
  * @rmtoll FINDIV24CFGR         FINDIV24EN         LL_RCC_EnableSAI2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[24], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SAI2 final divider channel
  * @rmtoll FINDIV24CFGR         FINDIV24EN         LL_RCC_DisableSAI2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[24], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#else
/**
  * @brief  Get SAI2 channel pre divided Value
  * @rmtoll PREDIV23CFGR      PREDIV23      LL_RCC_GetSAI2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[23], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SAI2 channel pre divided Value
  * @rmtoll PREDIV23CFGR         PREDIV23        LL_RCC_SetSAI2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[23], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SAI2 channel pre divided Value
  * @rmtoll FINDIV23CFGR      FINDIV23      LL_RCC_GetSAI2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[23], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SAI2 channel pre divided Value
  * @rmtoll FINDIV23CFGR         FINDIV23        LL_RCC_SetSAI2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[23], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SAI2 final divider channel
  * @rmtoll FINDIV23CFGR         FINDIV23EN         LL_RCC_EnableSAI2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[23], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SAI2 final divider channel
  * @rmtoll FINDIV23CFGR         FINDIV23EN         LL_RCC_DisableSAI2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[23], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SAI3_4 channel pre divided Value
  * @rmtoll PREDIV25CFGR      PREDIV25      LL_RCC_GetSAI3_4_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI3_4_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[25], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SAI3_4 channel pre divided Value
  * @rmtoll PREDIV25CFGR         PREDIV25        LL_RCC_SetSAI3_4_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI3_4_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[25], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SAI3_4 channel pre divided Value
  * @rmtoll FINDIV25CFGR      FINDIV25      LL_RCC_GetSAI3_4_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI3_4_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[25], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SAI3_4 channel pre divided Value
  * @rmtoll FINDIV25CFGR         FINDIV25        LL_RCC_SetSAI3_4_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI3_4_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[25], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SAI3_4 final divider channel
  * @rmtoll FINDIV25CFGR         FINDIV25EN         LL_RCC_EnableSAI3_4_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI3_4_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[25], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SAI3_4 final divider channel
  * @rmtoll FINDIV25CFGR         FINDIV25EN         LL_RCC_DisableSAI3_4_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI3_4_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[25], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#else
/**
  * @brief  Get SAI3 channel pre divided Value
  * @rmtoll PREDIV24CFGR      PREDIV24      LL_RCC_GetSAI3_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI3_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[24], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SAI3 channel pre divided Value
  * @rmtoll PREDIV24CFGR         PREDIV24        LL_RCC_SetSAI3_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI3_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[24], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SAI3 channel pre divided Value
  * @rmtoll FINDIV24CFGR      FINDIV24      LL_RCC_GetSAI3_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI3_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[24], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SAI3 channel pre divided Value
  * @rmtoll FINDIV24CFGR         FINDIV24        LL_RCC_SetSAI3_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI3_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[24], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SAI3 final divider channel
  * @rmtoll FINDIV24CFGR         FINDIV24EN         LL_RCC_EnableSAI3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI3_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[24], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SAI3 final divider channel
  * @rmtoll FINDIV24CFGR         FINDIV24EN         LL_RCC_DisableSAI3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI3_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[24], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get SAI4 channel pre divided Value
  * @rmtoll PREDIV25CFGR      PREDIV25      LL_RCC_GetSAI4_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI4_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[25], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SAI4 channel pre divided Value
  * @rmtoll PREDIV25CFGR         PREDIV25        LL_RCC_SetSAI4_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI4_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[25], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SAI4 channel pre divided Value
  * @rmtoll FINDIV25CFGR      FINDIV25      LL_RCC_GetSAI4_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAI4_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[25], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SAI4 channel pre divided Value
  * @rmtoll FINDIV25CFGR         FINDIV25        LL_RCC_SetSAI4_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSAI4_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[25], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SAI4 final divider channel
  * @rmtoll FINDIV25CFGR         FINDIV25EN         LL_RCC_EnableSAI4_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSAI4_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[25], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SAI4 final divider channel
  * @rmtoll FINDIV25CFGR         FINDIV25EN         LL_RCC_DisableSAI4_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSAI4_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[25], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

/**
  * @brief  Get FDCAN channel pre divided Value
  * @rmtoll PREDIV26CFGR      PREDIV26      LL_RCC_GetFDCAN_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetFDCAN_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[26], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set FDCAN channel pre divided Value
  * @rmtoll PREDIV26CFGR         PREDIV26        LL_RCC_SetFDCAN_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetFDCAN_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[26], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get FDCAN channel pre divided Value
  * @rmtoll FINDIV26CFGR      FINDIV26      LL_RCC_GetFDCAN_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetFDCAN_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[26], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set FDCAN channel pre divided Value
  * @rmtoll FINDIV26CFGR         FINDIV26        LL_RCC_SetFDCAN_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetFDCAN_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[26], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable FDCAN final divider channel
  * @rmtoll FINDIV26CFGR         FINDIV26EN         LL_RCC_EnableFDCAN_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableFDCAN_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[26], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable FDCAN final divider channel
  * @rmtoll FINDIV26CFGR         FINDIV26EN         LL_RCC_DisableFDCAN_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableFDCAN_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[26], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get DSIBLANE channel pre divided Value
  * @rmtoll PREDIV27CFGR      PREDIV27      LL_RCC_GetDSIBLANE_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetDSIBLANE_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[27], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set DSIBLANE channel pre divided Value
  * @rmtoll PREDIV27CFGR         PREDIV27        LL_RCC_SetDSIBLANE_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetDSIBLANE_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[27], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get DSIBLANE channel pre divided Value
  * @rmtoll FINDIV27CFGR      FINDIV27      LL_RCC_GetDSIBLANE_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetDSIBLANE_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[27], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set DSIBLANE channel pre divided Value
  * @rmtoll FINDIV27CFGR         FINDIV27        LL_RCC_SetDSIBLANE_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetDSIBLANE_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[27], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable DSIBLANE final divider channel
  * @rmtoll FINDIV27CFGR         FINDIV27EN         LL_RCC_EnableDSIBLANE_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableDSIBLANE_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[27], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable DSIBLANE final divider channel
  * @rmtoll FINDIV27CFGR         FINDIV27EN         LL_RCC_DisableDSIBLANE_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableDSIBLANE_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[27], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get DSIPHY channel pre divided Value
  * @rmtoll PREDIV28CFGR      PREDIV28      LL_RCC_GetDSIPHY_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetDSIPHY_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[28], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set DSIPHY channel pre divided Value
  * @rmtoll PREDIV28CFGR         PREDIV28        LL_RCC_SetDSIPHY_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetDSIPHY_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[28], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get DSIPHY channel pre divided Value
  * @rmtoll FINDIV28CFGR      FINDIV28      LL_RCC_GetDSIPHY_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetDSIPHY_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[28], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set DSIPHY channel pre divided Value
  * @rmtoll FINDIV28CFGR         FINDIV28        LL_RCC_SetDSIPHY_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetDSIPHY_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[28], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable DSIPHY final divider channel
  * @rmtoll FINDIV28CFGR         FINDIV28EN         LL_RCC_EnableDSIPHY_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableDSIPHY_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[28], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable DSIPHY final divider channel
  * @rmtoll FINDIV28CFGR         FINDIV28EN         LL_RCC_DisableDSIPHY_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableDSIPHY_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[28], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get CSI2 channel pre divided Value
  * @rmtoll PREDIV29CFGR      PREDIV29      LL_RCC_GetCSI2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetCSI2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[29], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set CSI2 channel pre divided Value
  * @rmtoll PREDIV29CFGR         PREDIV29        LL_RCC_SetCSI2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCSI2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[29], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get CSI2 channel pre divided Value
  * @rmtoll FINDIV29CFGR      FINDIV29      LL_RCC_GetCSI2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetCSI2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[29], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set CSI2 channel pre divided Value
  * @rmtoll FINDIV29CFGR         FINDIV29        LL_RCC_SetCSI2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCSI2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[29], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable CSI2 final divider channel
  * @rmtoll FINDIV29CFGR         FINDIV29EN         LL_RCC_EnableCSI2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableCSI2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[29], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable CSI2 final divider channel
  * @rmtoll FINDIV29CFGR         FINDIV29EN         LL_RCC_DisableCSI2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableCSI2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[29], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get CSI2TXESC channel pre divided Value
  * @rmtoll PREDIV30CFGR      PREDIV30      LL_RCC_GetCSI2TXESC_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetCSI2TXESC_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[30], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set CSI2TXESC channel pre divided Value
  * @rmtoll PREDIV30CFGR         PREDIV30        LL_RCC_SetCSI2TXESC_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCSI2TXESC_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[30], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get CSI2TXESC channel pre divided Value
  * @rmtoll FINDIV30CFGR      FINDIV30      LL_RCC_GetCSI2TXESC_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetCSI2TXESC_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[30], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set CSI2TXESC channel pre divided Value
  * @rmtoll FINDIV30CFGR         FINDIV30        LL_RCC_SetCSI2TXESC_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCSI2TXESC_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[30], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable CSI2TXESC final divider channel
  * @rmtoll FINDIV30CFGR         FINDIV30EN         LL_RCC_EnableCSI2TXESC_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableCSI2TXESC_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[30], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable CSI2TXESC final divider channel
  * @rmtoll FINDIV30CFGR         FINDIV30EN         LL_RCC_DisableCSI2TXESC_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableCSI2TXESC_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[30], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get CSI2PHY channel pre divided Value
  * @rmtoll PREDIV31CFGR      PREDIV31      LL_RCC_GetCSI2PHY_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetCSI2PHY_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[31], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set CSI2PHY channel pre divided Value
  * @rmtoll PREDIV31CFGR         PREDIV31        LL_RCC_SetCSI2PHY_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCSI2PHY_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[31], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get CSI2PHY channel pre divided Value
  * @rmtoll FINDIV31CFGR      FINDIV31      LL_RCC_GetCSI2PHY_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetCSI2PHY_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[31], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set CSI2PHY channel pre divided Value
  * @rmtoll FINDIV31CFGR         FINDIV31        LL_RCC_SetCSI2PHY_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCSI2PHY_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[31], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable CSI2PHY final divider channel
  * @rmtoll FINDIV31CFGR         FINDIV31EN         LL_RCC_EnableCSI2PHY_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableCSI2PHY_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[31], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable CSI2PHY final divider channel
  * @rmtoll FINDIV31CFGR         FINDIV31EN         LL_RCC_DisableCSI2PHY_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableCSI2PHY_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[31], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get LVDPHY channel pre divided Value
  * @rmtoll PREDIV32CFGR      PREDIV32      LL_RCC_GetLVDPHY_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetLVDPHY_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[32], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set LVDPHY channel pre divided Value
  * @rmtoll PREDIV32CFGR         PREDIV32        LL_RCC_SetLVDPHY_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLVDPHY_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[32], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get LVDPHY channel pre divided Value
  * @rmtoll FINDIV32CFGR      FINDIV32      LL_RCC_GetLVDPHY_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetLVDPHY_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[32], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set LVDPHY channel pre divided Value
  * @rmtoll FINDIV32CFGR         FINDIV32        LL_RCC_SetLVDPHY_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLVDPHY_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[32], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable LVDPHY final divider channel
  * @rmtoll FINDIV32CFGR         FINDIV32EN         LL_RCC_EnableLVDPHY_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLVDPHY_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[32], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable LVDPHY final divider channel
  * @rmtoll FINDIV32CFGR         FINDIV32EN         LL_RCC_DisableLVDPHY_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLVDPHY_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[32], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get STGEN channel pre divided Value
  * @rmtoll PREDIV33CFGR      PREDIV33      LL_RCC_GetSTGEN_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSTGEN_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[33], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set STGEN channel pre divided Value
  * @rmtoll PREDIV33CFGR         PREDIV33        LL_RCC_SetSTGEN_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSTGEN_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[33], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get STGEN channel pre divided Value
  * @rmtoll FINDIV33CFGR      FINDIV33      LL_RCC_GetSTGEN_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSTGEN_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[33], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set STGEN channel pre divided Value
  * @rmtoll FINDIV33CFGR         FINDIV33        LL_RCC_SetSTGEN_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSTGEN_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[33], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable STGEN final divider channel
  * @rmtoll FINDIV33CFGR         FINDIV33EN         LL_RCC_EnableSTGEN_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSTGEN_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[33], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable STGEN final divider channel
  * @rmtoll FINDIV33CFGR         FINDIV33EN         LL_RCC_DisableSTGEN_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSTGEN_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[33], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get USB3PCIEPHY channel pre divided Value
  * @rmtoll PREDIV34CFGR      PREDIV34      LL_RCC_GetUSB3PCIEPHY_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSB3PCIEPHY_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[34], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USB3PCIEPHY channel pre divided Value
  * @rmtoll PREDIV34CFGR         PREDIV34        LL_RCC_SetUSB3PCIEPHY_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSB3PCIEPHY_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[34], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USB3PCIEPHY channel pre divided Value
  * @rmtoll FINDIV34CFGR      FINDIV34      LL_RCC_GetUSB3PCIEPHY_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSB3PCIEPHY_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[34], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USB3PCIEPHY channel pre divided Value
  * @rmtoll FINDIV34CFGR         FINDIV34        LL_RCC_SetUSB3PCIEPHY_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSB3PCIEPHY_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[34], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USB3PCIEPHY final divider channel
  * @rmtoll FINDIV34CFGR         FINDIV34EN         LL_RCC_EnableUSB3PCIEPHY_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSB3PCIEPHY_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[34], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable USB3PCIEPHY final divider channel
  * @rmtoll FINDIV34CFGR         FINDIV34EN         LL_RCC_DisableUSB3PCIEPHY_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSB3PCIEPHY_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[34], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
/**
  * @brief  Get UCPD1 channel pre divided Value
  * @rmtoll PREDIV35CFGR      PREDIV35      LL_RCC_GetUCPD1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUCPD1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[35], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set UCPD1 channel pre divided Value
  * @rmtoll PREDIV35CFGR         PREDIV35        LL_RCC_SetUCPD1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUCPD1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[35], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get UCPD1 channel pre divided Value
  * @rmtoll FINDIV35CFGR      FINDIV35      LL_RCC_GetUCPD1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUCPD1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[35], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set UCPD1 channel pre divided Value
  * @rmtoll FINDIV35CFGR         FINDIV35        LL_RCC_SetUCPD1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUCPD1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[35], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable UCPD1 final divider channel
  * @rmtoll FINDIV35CFGR         FINDIV35EN         LL_RCC_EnableUCPD1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUCPD1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[35], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable UCPD1 final divider channel
  * @rmtoll FINDIV35CFGR         FINDIV35EN         LL_RCC_DisableUCPD1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUCPD1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[35], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get I3C4 channel pre divided Value
  * @rmtoll PREDIV36CFGR      PREDIV36      LL_RCC_GetI3C4_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3C4_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[36], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set I3C4 channel pre divided Value
  * @rmtoll PREDIV36CFGR         PREDIV36        LL_RCC_SetI3C4_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3C4_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[36], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get I3C4 channel pre divided Value
  * @rmtoll FINDIV36CFGR      FINDIV36      LL_RCC_GetI3C4_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3C4_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[36], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set I3C4 channel pre divided Value
  * @rmtoll FINDIV36CFGR         FINDIV36        LL_RCC_SetI3C4_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI3C4_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[36], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable I3C4 final divider channel
  * @rmtoll FINDIV36CFGR         FINDIV36EN         LL_RCC_EnableI3C4_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI3C4_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[36], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable I3C4 final divider channel
  * @rmtoll FINDIV36CFGR         FINDIV36EN         LL_RCC_DisableI3C4_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI3C4_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[36], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get SPI8 channel pre divided Value
  * @rmtoll PREDIV37CFGR      PREDIV37      LL_RCC_GetSPI8_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI8_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[37], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SPI8 channel pre divided Value
  * @rmtoll PREDIV37CFGR         PREDIV37        LL_RCC_SetSPI8_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI8_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[37], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SPI8 channel pre divided Value
  * @rmtoll FINDIV37CFGR      FINDIV37      LL_RCC_GetSPI8_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPI8_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[37], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SPI8 channel pre divided Value
  * @rmtoll FINDIV37CFGR         FINDIV37        LL_RCC_SetSPI8_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSPI8_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[37], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SPI8 final divider channel
  * @rmtoll FINDIV37CFGR         FINDIV37EN         LL_RCC_EnableSPI8_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSPI8_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[37], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SPI8 final divider channel
  * @rmtoll FINDIV37CFGR         FINDIV37EN         LL_RCC_DisableSPI8_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSPI8_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[37], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get I2C8 channel pre divided Value
  * @rmtoll PREDIV38CFGR      PREDIV38      LL_RCC_GetI2C8_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C8_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[38], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set I2C8 channel pre divided Value
  * @rmtoll PREDIV38CFGR         PREDIV38        LL_RCC_SetI2C8_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C8_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[38], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get I2C8 channel pre divided Value
  * @rmtoll FINDIV38CFGR      FINDIV38      LL_RCC_GetI2C8_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2C8_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[38], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set I2C8 channel pre divided Value
  * @rmtoll FINDIV38CFGR         FINDIV38        LL_RCC_SetI2C8_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetI2C8_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[38], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable I2C8 final divider channel
  * @rmtoll FINDIV38CFGR         FINDIV38EN         LL_RCC_EnableI2C8_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableI2C8_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[38], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable I2C8 final divider channel
  * @rmtoll FINDIV38CFGR         FINDIV38EN         LL_RCC_DisableI2C8_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableI2C8_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[38], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */


/**
  * @brief  Get LPUART1 channel pre divided Value
  * @rmtoll PREDIV39CFGR      PREDIV39      LL_RCC_GetLPUART1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUART1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[39], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set LPUART1 channel pre divided Value
  * @rmtoll PREDIV39CFGR         PREDIV39        LL_RCC_SetLPUART1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPUART1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[39], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get LPUART1 channel pre divided Value
  * @rmtoll FINDIV39CFGR      FINDIV39      LL_RCC_GetLPUART1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUART1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[39], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set LPUART1 channel pre divided Value
  * @rmtoll FINDIV39CFGR         FINDIV39        LL_RCC_SetLPUART1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPUART1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[39], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable LPUART1 final divider channel
  * @rmtoll FINDIV39CFGR         FINDIV39EN         LL_RCC_EnableLPUART1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPUART1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[39], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable LPUART1 final divider channel
  * @rmtoll FINDIV39CFGR         FINDIV39EN         LL_RCC_DisableLPUART1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPUART1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[39], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get LPTIM3 channel pre divided Value
  * @rmtoll PREDIV40CFGR      PREDIV40      LL_RCC_GetLPTIM3_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM3_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[40], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set LPTIM3 channel pre divided Value
  * @rmtoll PREDIV40CFGR         PREDIV40        LL_RCC_SetLPTIM3_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM3_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[40], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get LPTIM3 channel pre divided Value
  * @rmtoll FINDIV40CFGR      FINDIV40      LL_RCC_GetLPTIM3_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM3_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[40], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set LPTIM3 channel pre divided Value
  * @rmtoll FINDIV40CFGR         FINDIV40        LL_RCC_SetLPTIM3_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM3_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[40], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable LPTIM3 final divider channel
  * @rmtoll FINDIV40CFGR         FINDIV40EN         LL_RCC_EnableLPTIM3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPTIM3_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[40], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable LPTIM3 final divider channel
  * @rmtoll FINDIV40CFGR         FINDIV40EN         LL_RCC_DisableLPTIM3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPTIM3_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[40], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)

/**
  * @brief  Get LPTIM4_5 channel pre divided Value
  * @rmtoll PREDIV40CFGR      PREDIV40      LL_RCC_GetLPTIM4_5_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM4_5_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[41], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set LPTIM4_5 channel pre divided Value
  * @rmtoll PREDIV40CFGR         PREDIV40        LL_RCC_SetLPTIM4_5_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM4_5_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[41], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get LPTIM4_5 channel pre divided Value
  * @rmtoll FINDIV40CFGR      FINDIV40      LL_RCC_GetLPTIM4_5_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM4_5_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[41], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set LPTIM4_5 channel pre divided Value
  * @rmtoll FINDIV40CFGR         FINDIV40        LL_RCC_SetLPTIM4_5_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM4_5_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[41], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable LPTIM4_5 final divider channel
  * @rmtoll FINDIV40CFGR         FINDIV40EN         LL_RCC_EnableLPTIM4_5_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPTIM4_5_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[41], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable LPTIM4_5 final divider channel
  * @rmtoll FINDIV40CFGR         FINDIV40EN         LL_RCC_DisableLPTIM4_5_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPTIM4_5_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[41], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#else

/**
  * @brief  Get LPTIM4 channel pre divided Value
  * @rmtoll PREDIV41CFGR      PREDIV41      LL_RCC_GetLPTIM4_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM4_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[41], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set LPTIM4 channel pre divided Value
  * @rmtoll PREDIV41CFGR         PREDIV41        LL_RCC_SetLPTIM4_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM4_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[41], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get LPTIM4 channel pre divided Value
  * @rmtoll FINDIV41CFGR      FINDIV41      LL_RCC_GetLPTIM4_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM4_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[41], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set LPTIM4 channel pre divided Value
  * @rmtoll FINDIV41CFGR         FINDIV41        LL_RCC_SetLPTIM4_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM4_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[41], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable LPTIM4 final divider channel
  * @rmtoll FINDIV41CFGR         FINDIV41EN         LL_RCC_EnableLPTIM4_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPTIM4_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[41], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable LPTIM4 final divider channel
  * @rmtoll FINDIV41CFGR         FINDIV41EN         LL_RCC_DisableLPTIM4_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPTIM4_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[41], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get LPTIM5 channel pre divided Value
  * @rmtoll PREDIV42CFGR      PREDIV42      LL_RCC_GetLPTIM5_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM5_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[42], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set LPTIM5 channel pre divided Value
  * @rmtoll PREDIV42CFGR         PREDIV42        LL_RCC_SetLPTIM5_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM5_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[42], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get LPTIM5 channel pre divided Value
  * @rmtoll FINDIV42CFGR      FINDIV42      LL_RCC_GetLPTIM5_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIM5_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[42], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set LPTIM5 channel pre divided Value
  * @rmtoll FINDIV42CFGR         FINDIV42        LL_RCC_SetLPTIM5_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLPTIM5_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[42], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable LPTIM5 final divider channel
  * @rmtoll FINDIV42CFGR         FINDIV42EN         LL_RCC_EnableLPTIM5_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLPTIM5_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[42], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable LPTIM5 final divider channel
  * @rmtoll FINDIV42CFGR         FINDIV42EN         LL_RCC_DisableLPTIM5_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLPTIM5_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[42], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING) && !defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get ADF1 channel pre divided Value
  * @rmtoll PREDIV42CFGR      PREDIV42      LL_RCC_GetADF1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetADF1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[42], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ADF1 channel pre divided Value
  * @rmtoll PREDIV42CFGR         PREDIV42        LL_RCC_SetADF1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADF1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[42], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ADF1 channel pre divided Value
  * @rmtoll FINDIV42CFGR      FINDIV42      LL_RCC_GetADF1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetADF1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[42], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ADF1 channel pre divided Value
  * @rmtoll FINDIV42CFGR         FINDIV42        LL_RCC_SetADF1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADF1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[42], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ADF1 final divider channel
  * @rmtoll FINDIV42CFGR         FINDIV42EN         LL_RCC_EnableADF1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableADF1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[42], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ADF1 final divider channel
  * @rmtoll FINDIV42CFGR         FINDIV42EN         LL_RCC_DisableADF1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableADF1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[42], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */


/**
  * @brief  Get TSDBG channel pre divided Value
  * @rmtoll PREDIV43CFGR      PREDIV43      LL_RCC_GetTSDBG_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetTSDBG_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[43], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set TSDBG channel pre divided Value
  * @rmtoll PREDIV43CFGR         PREDIV43        LL_RCC_SetTSDBG_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetTSDBG_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[43], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get TSDBG channel pre divided Value
  * @rmtoll FINDIV43CFGR      FINDIV43      LL_RCC_GetTSDBG_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetTSDBG_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[43], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set TSDBG channel pre divided Value
  * @rmtoll FINDIV43CFGR         FINDIV43        LL_RCC_SetTSDBG_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetTSDBG_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[43], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable TSDBG final divider channel
  * @rmtoll FINDIV43CFGR         FINDIV43EN         LL_RCC_EnableTSDBG_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableTSDBG_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[43], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable TSDBG final divider channel
  * @rmtoll FINDIV43CFGR         FINDIV43EN         LL_RCC_DisableTSDBG_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableTSDBG_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[43], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get TPIU channel pre divided Value
  * @rmtoll PREDIV44CFGR      PREDIV44      LL_RCC_GetTPIU_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetTPIU_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[44], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set TPIU channel pre divided Value
  * @rmtoll PREDIV44CFGR         PREDIV44        LL_RCC_SetTPIU_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetTPIU_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[44], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get TPIU channel pre divided Value
  * @rmtoll FINDIV44CFGR      FINDIV44      LL_RCC_GetTPIU_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetTPIU_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[44], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set TPIU channel pre divided Value
  * @rmtoll FINDIV44CFGR         FINDIV44        LL_RCC_SetTPIU_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetTPIU_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[44], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable TPIU final divider channel
  * @rmtoll FINDIV44CFGR         FINDIV44EN         LL_RCC_EnableTPIU_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableTPIU_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[44], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable TPIU final divider channel
  * @rmtoll FINDIV44CFGR         FINDIV44EN         LL_RCC_DisableTPIU_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableTPIU_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[44], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get ATB_METR channel pre divided Value
  * @rmtoll PREDIV45CFGR      PREDIV45      LL_RCC_GetATB_METR_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetATB_METR_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[45], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ATB_METR channel pre divided Value
  * @rmtoll PREDIV45CFGR         PREDIV45        LL_RCC_SetATB_METR_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetATB_METR_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[45], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ATB_METR channel pre divided Value
  * @rmtoll FINDIV45CFGR      FINDIV45      LL_RCC_GetATB_METR_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetATB_METR_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[45], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ATB_METR channel pre divided Value
  * @rmtoll FINDIV45CFGR         FINDIV45        LL_RCC_SetATB_METR_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetATB_METR_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[45], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ATB_METR final divider channel
  * @rmtoll FINDIV45CFGR         FINDIV45EN         LL_RCC_EnableATB_METR_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableATB_METR_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[45], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ATB_METR final divider channel
  * @rmtoll FINDIV45CFGR         FINDIV45EN         LL_RCC_DisableATB_METR_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableATB_METR_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[45], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)

/**
  * @brief  Get ADC12 channel pre divided Value
  * @rmtoll PREDIV46CFGR      PREDIV46      LL_RCC_GetADC12_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC12_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[46], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ADC12 channel pre divided Value
  * @rmtoll PREDIV46CFGR         PREDIV46        LL_RCC_SetADC12_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC12_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[46], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ADC12 channel pre divided Value
  * @rmtoll FINDIV46CFGR      FINDIV46      LL_RCC_GetADC12_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC12_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[46], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ADC12 channel pre divided Value
  * @rmtoll FINDIV46CFGR         FINDIV46        LL_RCC_SetADC12_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC12_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[46], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ADC12 final divider channel
  * @rmtoll FINDIV46CFGR         FINDIV46EN         LL_RCC_EnableADC12_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableADC12_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[46], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ADC12 final divider channel
  * @rmtoll FINDIV46CFGR         FINDIV46EN         LL_RCC_DisableADC12_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableADC12_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[46], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get ADC3 channel pre divided Value
  * @rmtoll PREDIV47CFGR      PREDIV47      LL_RCC_GetADC3_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC3_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[47], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ADC3 channel pre divided Value
  * @rmtoll PREDIV47CFGR         PREDIV47        LL_RCC_SetADC3_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC3_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[47], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ADC3 channel pre divided Value
  * @rmtoll FINDIV47CFGR      FINDIV47      LL_RCC_GetADC3_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC3_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[47], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ADC3 channel pre divided Value
  * @rmtoll FINDIV47CFGR         FINDIV47        LL_RCC_SetADC3_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC3_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[47], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ADC3 final divider channel
  * @rmtoll FINDIV47CFGR         FINDIV47EN         LL_RCC_EnableADC3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableADC3_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[47], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ADC3 final divider channel
  * @rmtoll FINDIV47CFGR         FINDIV47EN         LL_RCC_DisableADC3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableADC3_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[47], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#else

/**
  * @brief  Get ADC1 channel pre divided Value
  * @rmtoll PREDIV46CFGR      PREDIV46      LL_RCC_GetADC1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[46], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ADC1 channel pre divided Value
  * @rmtoll PREDIV46CFGR         PREDIV46        LL_RCC_SetADC1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[46], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ADC1 channel pre divided Value
  * @rmtoll FINDIV46CFGR      FINDIV46      LL_RCC_GetADC1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[46], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ADC1 channel pre divided Value
  * @rmtoll FINDIV46CFGR         FINDIV46        LL_RCC_SetADC1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[46], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ADC1 final divider channel
  * @rmtoll FINDIV46CFGR         FINDIV46EN         LL_RCC_EnableADC1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableADC1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[46], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ADC1 final divider channel
  * @rmtoll FINDIV46CFGR         FINDIV46EN         LL_RCC_DisableADC1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableADC1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[46], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get ADC2 channel pre divided Value
  * @rmtoll PREDIV47CFGR      PREDIV47      LL_RCC_GetADC2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[47], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ADC2 channel pre divided Value
  * @rmtoll PREDIV47CFGR         PREDIV47        LL_RCC_SetADC2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[47], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ADC2 channel pre divided Value
  * @rmtoll FINDIV47CFGR      FINDIV47      LL_RCC_GetADC2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetADC2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[47], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ADC2 channel pre divided Value
  * @rmtoll FINDIV47CFGR         FINDIV47        LL_RCC_SetADC2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADC2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[47], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ADC2 final divider channel
  * @rmtoll FINDIV47CFGR         FINDIV47EN         LL_RCC_EnableADC2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableADC2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[47], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ADC2 final divider channel
  * @rmtoll FINDIV47CFGR         FINDIV47EN         LL_RCC_DisableADC2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableADC2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[47], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
/**
  * @brief  Get OSPI1 channel pre divided Value
  * @rmtoll PREDIV48CFGR      PREDIV48      LL_RCC_GetOSPI1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetOSPI1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[48], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set OSPI1 channel pre divided Value
  * @rmtoll PREDIV48CFGR         PREDIV48        LL_RCC_SetOSPI1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetOSPI1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[48], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get OSPI1 channel pre divided Value
  * @rmtoll FINDIV48CFGR      FINDIV48      LL_RCC_GetOSPI1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetOSPI1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[48], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set OSPI1 channel pre divided Value
  * @rmtoll FINDIV48CFGR         FINDIV48        LL_RCC_SetOSPI1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetOSPI1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[48], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable OSPI1 final divider channel
  * @rmtoll FINDIV48CFGR         FINDIV48EN         LL_RCC_EnableOSPI1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableOSPI1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[48], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable OSPI1 final divider channel
  * @rmtoll FINDIV48CFGR         FINDIV48EN         LL_RCC_DisableOSPI1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableOSPI1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[48], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

#if !defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
/**
  * @brief  Get OSPI2 channel pre divided Value
  * @rmtoll PREDIV49CFGR      PREDIV49      LL_RCC_GetOSPI2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetOSPI2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[49], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set OSPI2 channel pre divided Value
  * @rmtoll PREDIV49CFGR         PREDIV49        LL_RCC_SetOSPI2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetOSPI2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[49], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get OSPI2 channel pre divided Value
  * @rmtoll FINDIV49CFGR      FINDIV49      LL_RCC_GetOSPI2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetOSPI2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[49], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set OSPI2 channel pre divided Value
  * @rmtoll FINDIV49CFGR         FINDIV49        LL_RCC_SetOSPI2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetOSPI2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[49], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable OSPI2 final divider channel
  * @rmtoll FINDIV49CFGR         FINDIV49EN         LL_RCC_EnableOSPI2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableOSPI2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[49], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable OSPI2 final divider channel
  * @rmtoll FINDIV49CFGR         FINDIV49EN         LL_RCC_DisableOSPI2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableOSPI2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[49], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
/**
  * @brief  Get FMCCLOCK channel pre divided Value
  * @rmtoll PREDIV50CFGR      PREDIV50      LL_RCC_GetFMCCLOCK_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetFMC_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[50], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set FMCCLOCK channel pre divided Value
  * @rmtoll PREDIV50CFGR         PREDIV50        LL_RCC_SetFMCCLOCK_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetFMC_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[50], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get FMCCLOCK channel pre divided Value
  * @rmtoll FINDIV50CFGR      FINDIV50      LL_RCC_GetFMCCLOCK_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetFMC_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[50], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set FMCCLOCK channel pre divided Value
  * @rmtoll FINDIV50CFGR         FINDIV50        LL_RCC_SetFMCCLOCK_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetFMC_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[50], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable FMCCLOCK final divider channel
  * @rmtoll FINDIV50CFGR         FINDIV50EN         LL_RCC_EnableFMCCLOCK_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableFMC_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[50], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable FMCCLOCK final divider channel
  * @rmtoll FINDIV50CFGR         FINDIV50EN         LL_RCC_DisableFMCCLOCK_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableFMC_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[50], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get SDMMC1 channel pre divided Value
  * @rmtoll PREDIV51CFGR      PREDIV51      LL_RCC_GetSDMMC1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMC1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[51], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SDMMC1 channel pre divided Value
  * @rmtoll PREDIV51CFGR         PREDIV51        LL_RCC_SetSDMMC1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSDMMC1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[51], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SDMMC1 channel pre divided Value
  * @rmtoll FINDIV51CFGR      FINDIV51      LL_RCC_GetSDMMC1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMC1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[51], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SDMMC1 channel pre divided Value
  * @rmtoll FINDIV51CFGR         FINDIV51        LL_RCC_SetSDMMC1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSDMMC1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[51], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SDMMC1 final divider channel
  * @rmtoll FINDIV51CFGR         FINDIV51EN         LL_RCC_EnableSDMMC1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSDMMC1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[51], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SDMMC1 final divider channel
  * @rmtoll FINDIV51CFGR         FINDIV51EN         LL_RCC_DisableSDMMC1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSDMMC1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[51], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get SDMMC2 channel pre divided Value
  * @rmtoll PREDIV52CFGR      PREDIV52      LL_RCC_GetSDMMC2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMC2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[52], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SDMMC2 channel pre divided Value
  * @rmtoll PREDIV52CFGR         PREDIV52        LL_RCC_SetSDMMC2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSDMMC2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[52], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SDMMC2 channel pre divided Value
  * @rmtoll FINDIV52CFGR      FINDIV52      LL_RCC_GetSDMMC2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMC2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[52], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SDMMC2 channel pre divided Value
  * @rmtoll FINDIV52CFGR         FINDIV52        LL_RCC_SetSDMMC2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSDMMC2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[52], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SDMMC2 final divider channel
  * @rmtoll FINDIV52CFGR         FINDIV52EN         LL_RCC_EnableSDMMC2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSDMMC2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[52], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SDMMC2 final divider channel
  * @rmtoll FINDIV52CFGR         FINDIV52EN         LL_RCC_DisableSDMMC2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSDMMC2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[52], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get SDMMC3 channel pre divided Value
  * @rmtoll PREDIV53CFGR      PREDIV53      LL_RCC_GetSDMMC3_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMC3_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[53], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set SDMMC3 channel pre divided Value
  * @rmtoll PREDIV53CFGR         PREDIV53        LL_RCC_SetSDMMC3_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSDMMC3_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[53], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get SDMMC3 channel pre divided Value
  * @rmtoll FINDIV53CFGR      FINDIV53      LL_RCC_GetSDMMC3_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMC3_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[53], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set SDMMC3 channel pre divided Value
  * @rmtoll FINDIV53CFGR         FINDIV53        LL_RCC_SetSDMMC3_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetSDMMC3_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[53], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable SDMMC3 final divider channel
  * @rmtoll FINDIV53CFGR         FINDIV53EN         LL_RCC_EnableSDMMC3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableSDMMC3_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[53], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable SDMMC3 final divider channel
  * @rmtoll FINDIV53CFGR         FINDIV53EN         LL_RCC_DisableSDMMC3_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableSDMMC3_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[53], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get ETH1 channel pre divided Value
  * @rmtoll PREDIV54CFGR      PREDIV54      LL_RCC_GetETH1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetETH1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[54], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ETH1 channel pre divided Value
  * @rmtoll PREDIV54CFGR         PREDIV54        LL_RCC_SetETH1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETH1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[54], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ETH1 channel pre divided Value
  * @rmtoll FINDIV54CFGR      FINDIV54      LL_RCC_GetETH1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetETH1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[54], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ETH1 channel pre divided Value
  * @rmtoll FINDIV54CFGR         FINDIV54        LL_RCC_SetETH1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETH1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[54], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ETH1 final divider channel
  * @rmtoll FINDIV54CFGR         FINDIV54EN         LL_RCC_EnableETH1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableETH1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[54], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ETH1 final divider channel
  * @rmtoll FINDIV54CFGR         FINDIV54EN         LL_RCC_DisableETH1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableETH1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[54], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get ETH2 channel pre divided Value
  * @rmtoll PREDIV55CFGR      PREDIV55      LL_RCC_GetETH2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetETH2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[55], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ETH2 channel pre divided Value
  * @rmtoll PREDIV55CFGR         PREDIV55        LL_RCC_SetETH2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETH2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[55], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ETH2 channel pre divided Value
  * @rmtoll FINDIV55CFGR      FINDIV55      LL_RCC_GetETH2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetETH2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[55], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ETH2 channel pre divided Value
  * @rmtoll FINDIV55CFGR         FINDIV55        LL_RCC_SetETH2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETH2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[55], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ETH2 final divider channel
  * @rmtoll FINDIV55CFGR         FINDIV55EN         LL_RCC_EnableETH2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableETH2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[55], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ETH2 final divider channel
  * @rmtoll FINDIV55CFGR         FINDIV55EN         LL_RCC_DisableETH2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableETH2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[55], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get ETH1_2_PTP channel pre divided Value
  * @rmtoll PREDIV56CFGR      PREDIV56      LL_RCC_GetETH1_2_PTP_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetETH1_2_PTP_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[56], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ETH1_2_PTP channel pre divided Value
  * @rmtoll PREDIV56CFGR         PREDIV56        LL_RCC_SetETH1_2_PTP_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETH1_2_PTP_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[56], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ETH1_2_PTP channel pre divided Value
  * @rmtoll FINDIV56CFGR      FINDIV56      LL_RCC_GetETH1_2_PTP_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetETH1_2_PTP_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[56], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ETH1_2_PTP channel pre divided Value
  * @rmtoll FINDIV56CFGR         FINDIV56        LL_RCC_SetETH1_2_PTP_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETH1_2_PTP_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[56], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ETH1_2_PTP final divider channel
  * @rmtoll FINDIV56CFGR         FINDIV56EN         LL_RCC_EnableETH1_2_PTP_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableETH1_2_PTP_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[56], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ETH1_2_PTP final divider channel
  * @rmtoll FINDIV56CFGR         FINDIV56EN         LL_RCC_DisableETH1_2_PTP_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableETH1_2_PTP_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[56], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get USB2PHY1 channel pre divided Value
  * @rmtoll PREDIV57CFGR      PREDIV57      LL_RCC_GetUSB2PHY1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSB2PHY1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[57], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USB2PHY1 channel pre divided Value
  * @rmtoll PREDIV57CFGR         PREDIV57        LL_RCC_SetUSB2PHY1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSB2PHY1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[57], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USB2PHY1 channel pre divided Value
  * @rmtoll FINDIV57CFGR      FINDIV57      LL_RCC_GetUSB2PHY1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSB2PHY1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[57], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USB2PHY1 channel pre divided Value
  * @rmtoll FINDIV57CFGR         FINDIV57        LL_RCC_SetUSB2PHY1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSB2PHY1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[57], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USB2PHY1 final divider channel
  * @rmtoll FINDIV57CFGR         FINDIV57EN         LL_RCC_EnableUSB2PHY1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSB2PHY1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[57], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable USB2PHY1 final divider channel
  * @rmtoll FINDIV57CFGR         FINDIV57EN         LL_RCC_DisableUSB2PHY1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSB2PHY1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[57], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get USB2PHY2 channel pre divided Value
  * @rmtoll PREDIV58CFGR      PREDIV58      LL_RCC_GetUSB2PHY2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSB2PHY2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[58], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set USB2PHY2 channel pre divided Value
  * @rmtoll PREDIV58CFGR         PREDIV58        LL_RCC_SetUSB2PHY2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSB2PHY2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[58], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get USB2PHY2 channel pre divided Value
  * @rmtoll FINDIV58CFGR      FINDIV58      LL_RCC_GetUSB2PHY2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSB2PHY2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[58], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set USB2PHY2 channel pre divided Value
  * @rmtoll FINDIV58CFGR         FINDIV58        LL_RCC_SetUSB2PHY2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetUSB2PHY2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[58], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable USB2PHY2 final divider channel
  * @rmtoll FINDIV58CFGR         FINDIV58EN         LL_RCC_EnableUSB2PHY2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableUSB2PHY2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[58], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable USB2PHY2 final divider channel
  * @rmtoll FINDIV58CFGR         FINDIV58EN         LL_RCC_DisableUSB2PHY2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableUSB2PHY2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[58], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get ETHSWCFG channel pre divided Value
  * @rmtoll PREDIV59CFGR      PREDIV59      LL_RCC_GetETHSWCFG_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHSWCFG_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[59], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ETHSWCFG channel pre divided Value
  * @rmtoll PREDIV59CFGR         PREDIV59        LL_RCC_SetETHSWCFG_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETHSWCFG_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[59], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ETHSWCFG channel pre divided Value
  * @rmtoll FINDIV59CFGR      FINDIV59      LL_RCC_GetETHSWCFG_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHSWCFG_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[59], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ETHSWCFG channel pre divided Value
  * @rmtoll FINDIV59CFGR         FINDIV59        LL_RCC_SetETHSWCFG_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETHSWCFG_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[59], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ETHSWCFG final divider channel
  * @rmtoll FINDIV59CFGR         FINDIV59EN         LL_RCC_EnableETHSWCFG_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableETHSWCFG_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[59], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ETHSWCFG final divider channel
  * @rmtoll FINDIV59CFGR         FINDIV59EN         LL_RCC_DisableETHSWCFG_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableETHSWCFG_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[59], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}


/**
  * @brief  Get ETHSWMSG channel pre divided Value
  * @rmtoll PREDIV60CFGR      PREDIV60      LL_RCC_GetETHSWMSG_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHSWMSG_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[60], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set ETHSWMSG channel pre divided Value
  * @rmtoll PREDIV60CFGR         PREDIV60        LL_RCC_SetETHSWMSG_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETHSWMSG_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[60], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get ETHSWMSG channel pre divided Value
  * @rmtoll FINDIV60CFGR      FINDIV60      LL_RCC_GetETHSWMSG_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHSWMSG_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[60], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set ETHSWMSG channel pre divided Value
  * @rmtoll FINDIV60CFGR         FINDIV60        LL_RCC_SetETHSWMSG_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetETHSWMSG_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[60], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable ETHSWMSG final divider channel
  * @rmtoll FINDIV60CFGR         FINDIV60EN         LL_RCC_EnableETHSWMSG_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableETHSWMSG_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[60], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable ETHSWMSG final divider channel
  * @rmtoll FINDIV60CFGR         FINDIV60EN         LL_RCC_DisableETHSWMSG_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableETHSWMSG_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[60], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get MCO1 channel pre divided Value
  * @rmtoll PREDIV61CFGR      PREDIV61      LL_RCC_GetMCO1_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetMCO1_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[61], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set MCO1 channel pre divided Value
  * @rmtoll PREDIV61CFGR         PREDIV61        LL_RCC_SetMCO1_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetMCO1_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[61], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get MCO1 channel pre divided Value
  * @rmtoll FINDIV61CFGR      FINDIV61      LL_RCC_GetMCO1_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetMCO1_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[61], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set MCO1 channel pre divided Value
  * @rmtoll FINDIV61CFGR         FINDIV61        LL_RCC_SetMCO1_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetMCO1_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[61], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable MCO1 final divider channel
  * @rmtoll FINDIV61CFGR         FINDIV61EN         LL_RCC_EnableMCO1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableMCO1_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[61], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable MCO1 final divider channel
  * @rmtoll FINDIV61CFGR         FINDIV61EN         LL_RCC_DisableMCO1_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableMCO1_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[61], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get MCO2 channel pre divided Value
  * @rmtoll PREDIV62CFGR      PREDIV62      LL_RCC_GetMCO2_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetMCO2_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[62], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set MCO2 channel pre divided Value
  * @rmtoll PREDIV62CFGR         PREDIV62        LL_RCC_SetMCO2_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetMCO2_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[62], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get MCO2 channel pre divided Value
  * @rmtoll FINDIV62CFGR      FINDIV62      LL_RCC_GetMCO2_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetMCO2_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[62], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set MCO2 channel pre divided Value
  * @rmtoll FINDIV62CFGR         FINDIV62        LL_RCC_SetMCO2_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetMCO2_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[62], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable MCO2 final divider channel
  * @rmtoll FINDIV62CFGR         FINDIV62EN         LL_RCC_EnableMCO2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableMCO2_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[62], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable MCO2 final divider channel
  * @rmtoll FINDIV62CFGR         FINDIV62EN         LL_RCC_DisableMCO2_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableMCO2_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[62], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Get CPU1EXT2F channel pre divided Value
  * @rmtoll PREDIV63CFGR      PREDIV63      LL_RCC_GetCPU1EXT2F_PREDIV
  * @retval Returned value can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetCPU1EXT2F_PREDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PREDIVxCFGR[63], RCC_PREDIVxCFGR_PREDIVx_Msk));
}

/**
  * @brief  Set CPU1EXT2F channel pre divided Value
  * @rmtoll PREDIV63CFGR         PREDIV63        LL_RCC_SetCPU1EXT2F_PREDIV
  * @param  Source This parameter can be one of the following values:
  *        @arg @ref LL_RCC_PREDIV_DIV1
  *        @arg @ref LL_RCC_PREDIV_DIV2
  *        @arg @ref LL_RCC_PREDIV_DIV4
  *        @arg @ref LL_RCC_PREDIV_DIV1024
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCPU1EXT2F_PREDIV(uint32_t Source)
{
  MODIFY_REG(RCC->PREDIVxCFGR[63], RCC_PREDIVxCFGR_PREDIVx_Msk, Source);
}

/* FINDIV part */

/**
  * @brief  Get CPU1EXT2F channel pre divided Value
  * @rmtoll FINDIV63CFGR      FINDIV63      LL_RCC_GetCPU1EXT2F_FINDIV
  * @retval A value between 0 and 63, div1 up to div64 step
  */
__STATIC_INLINE uint32_t LL_RCC_GetCPU1EXT2F_FINDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->FINDIVxCFGR[63], RCC_FINDIVxCFGR_FINDIVx_Msk));
}

/**
  * @brief  Set CPU1EXT2F channel pre divided Value
  * @rmtoll FINDIV63CFGR         FINDIV63        LL_RCC_SetCPU1EXT2F_FINDIV
  * @param  Value parameter can be a value between 0 and 63 to divide from 1 up to 64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetCPU1EXT2F_FINDIV(uint32_t Value)
{
  MODIFY_REG(RCC->FINDIVxCFGR[63], RCC_FINDIVxCFGR_FINDIVx_Msk, Value);
}

/**
  * @brief  Enable CPU1EXT2F final divider channel
  * @rmtoll FINDIV63CFGR         FINDIV63EN         LL_RCC_EnableCPU1EXT2F_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableCPU1EXT2F_FINDIV(void)
{
  SET_BIT(RCC->FINDIVxCFGR[63], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @brief  Disable CPU1EXT2F final divider channel
  * @rmtoll FINDIV63CFGR         FINDIV63EN         LL_RCC_DisableCPU1EXT2F_FINDIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableCPU1EXT2F_FINDIV(void)
{
  CLEAR_BIT(RCC->FINDIVxCFGR[63], RCC_FINDIVxCFGR_FINDIVxEN_Msk);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_RTC RTC
  * @{
  */

/**
  * @brief  Set RTC Clock Source
  * @note   Once the RTC clock source has been selected, it cannot be changed
  *         anymore unless the Backup domain is reset, or unless a failure is
  *         detected on LSE (LSECSS is set). The VSWRST bit can be used to reset
  *         them.
  * @rmtoll BDCR         RTCSRC        LL_RCC_SetRTCClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRTCClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSRC, Source);
}

/**
  * @brief  Get RTC Clock Source
  * @rmtoll BDCR         RTCSRC        LL_RCC_GetRTCClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTCClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_RTCSRC));
}

/**
  * @brief  Enable RTC
  * @rmtoll BDCR         RTCCKEN         LL_RCC_EnableRTC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableRTC(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_RTCCKEN);
}

/**
  * @brief  Disable RTC
  * @rmtoll BDCR         RTCCKEN         LL_RCC_DisableRTC
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableRTC(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCCKEN);
}

/**
  * @brief  Check if RTC has been enabled or not
  * @rmtoll BDCR         RTCEN         LL_RCC_IsEnabledRTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledRTC(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_RTCCKEN) == RCC_BDCR_RTCCKEN) ? 1UL : 0UL);
}

/**
  * @brief  Force the Backup domain reset
  * @rmtoll BDCR         VSWRST         LL_RCC_ForceBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ForceBackupDomainReset(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_VSWRST);
}

/**
  * @brief  Release the Backup domain reset
  * @rmtoll BDCR         VSWRST         LL_RCC_ReleaseBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ReleaseBackupDomainReset(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_VSWRST);
}

/**
  * @brief  Set HSE Prescaler for RTC Clock
  * @rmtoll RTCDIVR         RTCDIV        LL_RCC_SetRTC_HSEPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_HSE_DIV_1
  *         @arg @ref LL_RCC_RTC_HSE_DIV_2
  *         @arg @ref LL_RCC_RTC_HSE_DIV_3
  *         @arg @ref LL_RCC_RTC_HSE_DIV_4
  *         @arg @ref LL_RCC_RTC_HSE_DIV_5
  *         @arg @ref LL_RCC_RTC_HSE_DIV_6
  *         @arg @ref LL_RCC_RTC_HSE_DIV_7
  *         @arg @ref LL_RCC_RTC_HSE_DIV_8
  *         @arg @ref LL_RCC_RTC_HSE_DIV_9
  *         @arg @ref LL_RCC_RTC_HSE_DIV_10
  *         @arg @ref LL_RCC_RTC_HSE_DIV_11
  *         @arg @ref LL_RCC_RTC_HSE_DIV_12
  *         @arg @ref LL_RCC_RTC_HSE_DIV_13
  *         @arg @ref LL_RCC_RTC_HSE_DIV_14
  *         @arg @ref LL_RCC_RTC_HSE_DIV_15
  *         @arg @ref LL_RCC_RTC_HSE_DIV_16
  *         @arg @ref LL_RCC_RTC_HSE_DIV_17
  *         @arg @ref LL_RCC_RTC_HSE_DIV_18
  *         @arg @ref LL_RCC_RTC_HSE_DIV_19
  *         @arg @ref LL_RCC_RTC_HSE_DIV_20
  *         @arg @ref LL_RCC_RTC_HSE_DIV_21
  *         @arg @ref LL_RCC_RTC_HSE_DIV_22
  *         @arg @ref LL_RCC_RTC_HSE_DIV_23
  *         @arg @ref LL_RCC_RTC_HSE_DIV_24
  *         @arg @ref LL_RCC_RTC_HSE_DIV_25
  *         @arg @ref LL_RCC_RTC_HSE_DIV_26
  *         @arg @ref LL_RCC_RTC_HSE_DIV_27
  *         @arg @ref LL_RCC_RTC_HSE_DIV_28
  *         @arg @ref LL_RCC_RTC_HSE_DIV_29
  *         @arg @ref LL_RCC_RTC_HSE_DIV_30
  *         @arg @ref LL_RCC_RTC_HSE_DIV_31
  *         @arg @ref LL_RCC_RTC_HSE_DIV_32
  *         @arg @ref LL_RCC_RTC_HSE_DIV_33
  *         @arg @ref LL_RCC_RTC_HSE_DIV_34
  *         @arg @ref LL_RCC_RTC_HSE_DIV_35
  *         @arg @ref LL_RCC_RTC_HSE_DIV_36
  *         @arg @ref LL_RCC_RTC_HSE_DIV_37
  *         @arg @ref LL_RCC_RTC_HSE_DIV_38
  *         @arg @ref LL_RCC_RTC_HSE_DIV_39
  *         @arg @ref LL_RCC_RTC_HSE_DIV_40
  *         @arg @ref LL_RCC_RTC_HSE_DIV_41
  *         @arg @ref LL_RCC_RTC_HSE_DIV_42
  *         @arg @ref LL_RCC_RTC_HSE_DIV_43
  *         @arg @ref LL_RCC_RTC_HSE_DIV_44
  *         @arg @ref LL_RCC_RTC_HSE_DIV_45
  *         @arg @ref LL_RCC_RTC_HSE_DIV_46
  *         @arg @ref LL_RCC_RTC_HSE_DIV_47
  *         @arg @ref LL_RCC_RTC_HSE_DIV_48
  *         @arg @ref LL_RCC_RTC_HSE_DIV_49
  *         @arg @ref LL_RCC_RTC_HSE_DIV_50
  *         @arg @ref LL_RCC_RTC_HSE_DIV_51
  *         @arg @ref LL_RCC_RTC_HSE_DIV_52
  *         @arg @ref LL_RCC_RTC_HSE_DIV_53
  *         @arg @ref LL_RCC_RTC_HSE_DIV_54
  *         @arg @ref LL_RCC_RTC_HSE_DIV_55
  *         @arg @ref LL_RCC_RTC_HSE_DIV_56
  *         @arg @ref LL_RCC_RTC_HSE_DIV_57
  *         @arg @ref LL_RCC_RTC_HSE_DIV_58
  *         @arg @ref LL_RCC_RTC_HSE_DIV_59
  *         @arg @ref LL_RCC_RTC_HSE_DIV_60
  *         @arg @ref LL_RCC_RTC_HSE_DIV_61
  *         @arg @ref LL_RCC_RTC_HSE_DIV_62
  *         @arg @ref LL_RCC_RTC_HSE_DIV_63
  *         @arg @ref LL_RCC_RTC_HSE_DIV_64
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetRTC_HSEPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->RTCDIVR, RCC_RTCDIVR_RTCDIV, Prescaler);
}

/**
  * @brief  Get HSE Prescalers for RTC Clock
  * @rmtoll RTCDIVR         RTCDIV        LL_RCC_GetRTC_HSEPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_HSE_DIV_1
  *         @arg @ref LL_RCC_RTC_HSE_DIV_2
  *         @arg @ref LL_RCC_RTC_HSE_DIV_3
  *         @arg @ref LL_RCC_RTC_HSE_DIV_4
  *         @arg @ref LL_RCC_RTC_HSE_DIV_5
  *         @arg @ref LL_RCC_RTC_HSE_DIV_6
  *         @arg @ref LL_RCC_RTC_HSE_DIV_7
  *         @arg @ref LL_RCC_RTC_HSE_DIV_8
  *         @arg @ref LL_RCC_RTC_HSE_DIV_9
  *         @arg @ref LL_RCC_RTC_HSE_DIV_10
  *         @arg @ref LL_RCC_RTC_HSE_DIV_11
  *         @arg @ref LL_RCC_RTC_HSE_DIV_12
  *         @arg @ref LL_RCC_RTC_HSE_DIV_13
  *         @arg @ref LL_RCC_RTC_HSE_DIV_14
  *         @arg @ref LL_RCC_RTC_HSE_DIV_15
  *         @arg @ref LL_RCC_RTC_HSE_DIV_16
  *         @arg @ref LL_RCC_RTC_HSE_DIV_17
  *         @arg @ref LL_RCC_RTC_HSE_DIV_18
  *         @arg @ref LL_RCC_RTC_HSE_DIV_19
  *         @arg @ref LL_RCC_RTC_HSE_DIV_20
  *         @arg @ref LL_RCC_RTC_HSE_DIV_21
  *         @arg @ref LL_RCC_RTC_HSE_DIV_22
  *         @arg @ref LL_RCC_RTC_HSE_DIV_23
  *         @arg @ref LL_RCC_RTC_HSE_DIV_24
  *         @arg @ref LL_RCC_RTC_HSE_DIV_25
  *         @arg @ref LL_RCC_RTC_HSE_DIV_26
  *         @arg @ref LL_RCC_RTC_HSE_DIV_27
  *         @arg @ref LL_RCC_RTC_HSE_DIV_28
  *         @arg @ref LL_RCC_RTC_HSE_DIV_29
  *         @arg @ref LL_RCC_RTC_HSE_DIV_30
  *         @arg @ref LL_RCC_RTC_HSE_DIV_31
  *         @arg @ref LL_RCC_RTC_HSE_DIV_32
  *         @arg @ref LL_RCC_RTC_HSE_DIV_33
  *         @arg @ref LL_RCC_RTC_HSE_DIV_34
  *         @arg @ref LL_RCC_RTC_HSE_DIV_35
  *         @arg @ref LL_RCC_RTC_HSE_DIV_36
  *         @arg @ref LL_RCC_RTC_HSE_DIV_37
  *         @arg @ref LL_RCC_RTC_HSE_DIV_38
  *         @arg @ref LL_RCC_RTC_HSE_DIV_39
  *         @arg @ref LL_RCC_RTC_HSE_DIV_40
  *         @arg @ref LL_RCC_RTC_HSE_DIV_41
  *         @arg @ref LL_RCC_RTC_HSE_DIV_42
  *         @arg @ref LL_RCC_RTC_HSE_DIV_43
  *         @arg @ref LL_RCC_RTC_HSE_DIV_44
  *         @arg @ref LL_RCC_RTC_HSE_DIV_45
  *         @arg @ref LL_RCC_RTC_HSE_DIV_46
  *         @arg @ref LL_RCC_RTC_HSE_DIV_47
  *         @arg @ref LL_RCC_RTC_HSE_DIV_48
  *         @arg @ref LL_RCC_RTC_HSE_DIV_49
  *         @arg @ref LL_RCC_RTC_HSE_DIV_50
  *         @arg @ref LL_RCC_RTC_HSE_DIV_51
  *         @arg @ref LL_RCC_RTC_HSE_DIV_52
  *         @arg @ref LL_RCC_RTC_HSE_DIV_53
  *         @arg @ref LL_RCC_RTC_HSE_DIV_54
  *         @arg @ref LL_RCC_RTC_HSE_DIV_55
  *         @arg @ref LL_RCC_RTC_HSE_DIV_56
  *         @arg @ref LL_RCC_RTC_HSE_DIV_57
  *         @arg @ref LL_RCC_RTC_HSE_DIV_58
  *         @arg @ref LL_RCC_RTC_HSE_DIV_59
  *         @arg @ref LL_RCC_RTC_HSE_DIV_60
  *         @arg @ref LL_RCC_RTC_HSE_DIV_61
  *         @arg @ref LL_RCC_RTC_HSE_DIV_62
  *         @arg @ref LL_RCC_RTC_HSE_DIV_63
  *         @arg @ref LL_RCC_RTC_HSE_DIV_64
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTC_HSEPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->RTCDIVR, RCC_RTCDIVR_RTCDIV));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_PLL PLL
  * @{
  */

/**
  * @brief  Set the oscillator used as PLL1 clock source.
  * @note   PLLSRC can be written only when all PLL1 is disabled.
  * @rmtoll MUXSELCFGR      MUXSEL5        LL_RCC_PLL1_SetSource
  * @param  PLLSource parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  *         @arg @ref LL_RCC_PLL1SOURCE_MSI
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL1_SetSource(uint32_t PLLSource)
{
  MODIFY_REG(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL5, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL1 clock source.
  * @rmtoll MUXSELCFGR      MUXSEL5        LL_RCC_PLL1_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  *         @arg @ref LL_RCC_PLL1SOURCE_MSI
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL5));
}

/**
  * @brief  Set the oscillator used as PLL2 clock source.
  * @note   PLLSRC can be written only when all PLL2 is disabled.
  * @rmtoll MUXSELCFGR      MUXSEL6        LL_RCC_PLL2_SetSource
  * @param  PLLSource parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2SOURCE_HSI
  *         @arg @ref LL_RCC_PLL2SOURCE_HSE
  *         @arg @ref LL_RCC_PLL2SOURCE_MSI
  *         @arg @ref LL_RCC_PLL2SOURCE_NONE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_SetSource(uint32_t PLLSource)
{
  MODIFY_REG(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL6, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL2 clock source.
  * @rmtoll MUXSELCFGR      MUXSEL6        LL_RCC_PLL2_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL2SOURCE_HSI
  *         @arg @ref LL_RCC_PLL2SOURCE_HSE
  *         @arg @ref LL_RCC_PLL2SOURCE_MSI
  *         @arg @ref LL_RCC_PLL2SOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL6));
}

/**
  * @brief  Enable PLL2
  * @rmtoll PLL2CFGR1           PLLEN         LL_RCC_PLL2_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_Enable(void)
{
  SET_BIT(RCC->PLL2CFGR1, RCC_PLL2CFGR1_PLLEN);
}

/**
  * @brief  Disable PLL2
  * @note Cannot be disabled if the PLL clock is used as a system clock.
  *       This API shall be called only when PLL2 DIVPEN, DIVQEN and DIVREN are
  *       disabled.
  * @rmtoll PLL2CFGR1           PLLEN         LL_RCC_PLL2_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_Disable(void)
{
  CLEAR_BIT(RCC->PLL2CFGR1, RCC_PLL2CFGR1_PLLEN);
}

/**
  * @brief  assert PLL2 Spread Spectrum Modulator reset
  * @rmtoll PLL2CFGR1           SSMODRST         LL_RCC_PLL2_SSMODRST_Assert
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_SSMODRST_Assert(void)
{
  SET_BIT(RCC->PLL2CFGR1, RCC_PLL2CFGR1_SSMODRST);
}

/**
  * @brief  release PLL2 Spread Spectrum Modulator reset
  * @rmtoll PLL2CFGR1           SSMODRST         LL_RCC_PLL2_SSMODRST_Release
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_SSMODRST_Release(void)
{
  CLEAR_BIT(RCC->PLL2CFGR1, RCC_PLL2CFGR1_SSMODRST);
}

/**
  * @brief  Check if PLL2 Spread Spectrum Modulator reset is asserted
  * @rmtoll PLL2CFGR1           SSMODRST        LL_RCC_PLL2_SSMODRST_IsAssert
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_SSMODRST_IsAssert(void)
{
  return ((READ_BIT(RCC->PLL2CFGR1, RCC_PLL2CFGR1_SSMODRST) == RCC_PLL2CFGR1_SSMODRST) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 Ready
  * @rmtoll PLL2CFGR1           PLL2RDY        LL_RCC_PLL2_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsReady(void)
{
  return ((READ_BIT(RCC->PLL2CFGR1, RCC_PLL2CFGR1_PLLRDY) == RCC_PLL2CFGR1_PLLRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set Fractional part of the PLL2 VCO multiplication factor
  * @rmtoll PLL2CFGR1      CKREFST          LL_RCC_PLL2_SetCKREFST
  * @param  CKREFST parameter can be a value between 0 and 1 (0x1)
  * 0: Reading 0 means that the PLL{x} reference clock is not running, writing 0 resets the
  * reference clock running detector.
  * 1: Reading 1 means that the PLL{x} reference clock is running, writing 1 resets the
  * reference clock running detector.
  */
__STATIC_INLINE void LL_RCC_PLL2_SetCKREFST(uint32_t CKREFST)
{
  MODIFY_REG(RCC->PLL2CFGR1, RCC_PLL2CFGR1_CKREFST, CKREFST << RCC_PLL2CFGR1_CKREFST_Pos);
}

/**
  * @brief  Check if PLL2 reference clock is running
  * @rmtoll PLL2CFGR1           CKREFST        LL_RCC_PLL2_CKREFST_IsRunning
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_CKREFST_IsRunning(void)
{
  return ((READ_BIT(RCC->PLL2CFGR1, RCC_PLL2CFGR1_CKREFST) == RCC_PLL2CFGR1_CKREFST) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL2 VCO multiplication factor
  * @rmtoll PLL2CFGR2      FBDIV          LL_RCC_PLL2_SetFBDIV
  * @param  FBDIV parameter can be a value between 0 and 4095 (0xFFF)
  */
__STATIC_INLINE void LL_RCC_PLL2_SetFBDIV(uint32_t FBDIV)
{
  MODIFY_REG(RCC->PLL2CFGR2, RCC_PLL2CFGR2_FBDIV, FBDIV << RCC_PLL2CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL2 VCO multiplication factor
  * @rmtoll PLL2CFGR2      FBDIV          LL_RCC_PLL2_GetFBDIV
  * @retval A value between 0 and 4095 (0x0FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetFBDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2CFGR2, RCC_PLL2CFGR2_FBDIV) >>  RCC_PLL2CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL2  reference input clock divide frequency ratio
  * @rmtoll PLL2CFGR2      FREFDIV          LL_RCC_PLL2_SetFREFDIV
  * @param  FREFDIV parameter can be a value between 0 and 63 (0x3F)
  */
__STATIC_INLINE void LL_RCC_PLL2_SetFREFDIV(uint32_t FREFDIV)
{
  MODIFY_REG(RCC->PLL2CFGR2, RCC_PLL2CFGR2_FREFDIV, FREFDIV << RCC_PLL2CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Get PLL2  reference input clock divide frequency ratio
  * @rmtoll PLL2CFGR2      FREFDIV          LL_RCC_PLL2_GetFREFDIV
  * @retval A value between 0 and 63 (0x3F)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetFREFDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2CFGR2, RCC_PLL2CFGR2_FREFDIV) >>  RCC_PLL2CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Set Fractional part of the PLL2 VCO multiplication factor
  * @rmtoll PLL2CFGR3      FRACIN          LL_RCC_PLL2_SetFRACIN
  * @param  FRACIN parameter can be a value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE void LL_RCC_PLL2_SetFRACIN(uint32_t FRACIN)
{
  MODIFY_REG(RCC->PLL2CFGR3, RCC_PLL2CFGR3_FRACIN, FRACIN << RCC_PLL2CFGR3_FRACIN_Pos);
}

/**
  * @brief  Get Fractional part of the PLL2 VCO multiplication factor
  * @rmtoll PLL2CFGR3      FRACIN          LL_RCC_PLL2_GetFRACIN
  * @retval A value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetFRACIN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2CFGR3, RCC_PLL2CFGR3_FRACIN) >>  RCC_PLL2CFGR3_FRACIN_Pos);
}

/**
  * @brief  Enable the Spread Spectrum Modulator of PLL2
  * @rmtoll PLL2CFGR3           SSCGDIS         LL_RCC_PLL2_CSG_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_CSG_Enable(void)
{
  CLEAR_BIT(RCC->PLL2CFGR3, RCC_PLL2CFGR3_SSCGDIS);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL2
  * @rmtoll PLL2CFGR3           SSCGDIS         LL_RCC_PLL2_CSG_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_CSG_Disable(void)
{
  SET_BIT(RCC->PLL2CFGR3, RCC_PLL2CFGR3_SSCGDIS);
}

/**
  * @brief  Check if PLL2Spread Spectrum Modulator  is Enabled
  * @rmtoll PLL2CFGR3           SSCGDIS        LL_RCC_PLL2_CSG_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_CSG_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL2CFGR3, RCC_PLL2CFGR3_SSCGDIS) == RCC_PLL2CFGR3_SSCGDIS) ? 0UL : 1UL);
}

/**
  * @brief  Enable the Spread Spectrum Modulator of PLL2
  * @rmtoll PLL2CFGR3           DACEN         LL_RCC_PLL2DAC_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2DAC_Enable(void)
{
  CLEAR_BIT(RCC->PLL2CFGR3, RCC_PLL2CFGR3_DACEN);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL2
  * @rmtoll PLL2CFGR3           DACEN         LL_RCC_PLL2DAC_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2DAC_Disable(void)
{
  SET_BIT(RCC->PLL2CFGR3, RCC_PLL2CFGR3_DACEN);
}

/**
  * @brief  Check if PLL2 DAC is Enabled
  * @rmtoll PLL2CFGR3           DACEN        LL_RCC_PLL2_DAC_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_DAC_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL2CFGR3, RCC_PLL2CFGR3_DACEN) == RCC_PLL2CFGR3_DACEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable Down-spread modulation of PLL2
  * @rmtoll PLL2CFGR3           DOWNSPREAD         LL_RCC_PLL2DOWNSPREAD_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2DOWNSPREAD_Enable(void)
{
  CLEAR_BIT(RCC->PLL2CFGR3, RCC_PLL2CFGR3_DOWNSPREAD);
}

/**
  * @brief  Enable Center-spread modulation of PLL2
  * @rmtoll PLL2CFGR3           DOWNSPREAD         LL_RCC_PLL2DOWNSPREAD_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2DOWNSPREAD_Disable(void)
{
  SET_BIT(RCC->PLL2CFGR3, RCC_PLL2CFGR3_DOWNSPREAD);
}

/**
  * @brief  Check if PLL2 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL2CFGR4           BYPASS        LL_RCC_PLL2_FOUTPOSTDIV_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_FOUTPOSTDIV_FREF_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL2CFGR4, RCC_PLL2CFGR4_BYPASS) == RCC_PLL2CFGR4_BYPASS) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL2
  * @rmtoll PLL2CFGR4           BYPASS         LL_RCC_PLL2_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_FOUTPOSTDIV_FREF_Enable(void)
{
  SET_BIT(RCC->PLL2CFGR4, RCC_PLL2CFGR4_BYPASS);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL2
  * @rmtoll PLL2CFGR4           BYPASS         LL_RCC_PLL2_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_FOUTPOSTDIV_FREF_Disable(void)
{
  CLEAR_BIT(RCC->PLL2CFGR4, RCC_PLL2CFGR4_BYPASS);
}

/**
  * @brief  Check if PLL2  POSTDIV1 and POSTDIV2 dividers are active
  * @rmtoll PLL2CFGR4           FOUTPOSTDIVEN        LL_RCC_PLL2_FOUTPOSTDIVEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_FOUTPOSTDIVEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL2CFGR4, RCC_PLL2CFGR4_FOUTPOSTDIVEN) == RCC_PLL2CFGR4_FOUTPOSTDIVEN) ? 1UL : 0UL);
}

/**
  * @brief   activate POSTDIV1 and POSTDIV2 on PLL2
  * @rmtoll PLL2CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL2_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_FOUTPOSTDIV_Enable(void)
{
  SET_BIT(RCC->PLL2CFGR4, RCC_PLL2CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  disactivate POSTDIV1 and POSTDIV2 on PLL2
  * @rmtoll PLL2CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL2_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_FOUTPOSTDIV_Disable(void)
{
  CLEAR_BIT(RCC->PLL2CFGR4, RCC_PLL2CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  Check if PLL2 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL2CFGR4           DSMEN        LL_RCC_PLL2_DSMEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_PLL2_DSMEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL2CFGR4, RCC_PLL2CFGR4_DSMEN) == RCC_PLL2CFGR4_DSMEN) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL2
  * @rmtoll PLL2CFGR4           DSMEN         LL_RCC_PLL2_DSMEN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_DSMEN_Enable(void)
{
  SET_BIT(RCC->PLL2CFGR4, RCC_PLL2CFGR4_DSMEN);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL2
  * @rmtoll PLL2CFGR4           DSMEN         LL_RCC_PLL2_DSMEN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_DSMEN_Disable(void)
{
  CLEAR_BIT(RCC->PLL2CFGR4, RCC_PLL2CFGR4_DSMEN);
}

/** @brief  Configure the PLL2 Clock Spreading Generator
  * @rmtoll PLL2CSGR    DIVVAL, SPREAD  LL_RCC_PLL2_ConfigCSG
  *
  * @param  ModFreq:  Modulation frequency adjustment for PLL2
  *         This parameter must have a value between 0 and 15
  *
  * @param  IncStep: Modulation Depth Adjustment for PLL2
  *         This parameter must have a value between 0 and 31
  * @note   ModFreq x IncStep shall not exceed (2^4)-1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL2_ConfigCSG(uint32_t ModFreq, uint32_t IncStep)
{
  MODIFY_REG(RCC->PLL2CFGR5, (RCC_PLL2CFGR5_DIVVAL | RCC_PLL2CFGR5_SPREAD), \
             (ModFreq | (IncStep << RCC_PLL2CFGR5_SPREAD_Pos)));
}

/**
  * @brief  Get  PLL2 VCO frequency divide level 1
  * @rmtoll PLL2CFGR6      POSTDIV1          LL_RCC_PLL2_ConfigFREQDIV_L1
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL2_ConfigFREQDIV_L1(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL2CFGR6, RCC_PLL2CFGR6_POSTDIV1, POSTDIV << RCC_PLL2CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get Fractional part of the PLL2 VCO multiplication factor
  * @rmtoll PLL2CFGR6      POSTDIV1          LL_RCC_PLL2_GetFREQDIV_L1
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetFREQDIV_L1(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2CFGR6, RCC_PLL2CFGR6_POSTDIV1) >>  RCC_PLL2CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get PLL2  reference input clock divide frequency ratio
  * @rmtoll PLL2CFGR7      POSTDIV2          LL_RCC_PLL2_ConfigFREQDIV_L2
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL2_ConfigFREQDIV_L2(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL2CFGR7, RCC_PLL2CFGR7_POSTDIV2, POSTDIV << RCC_PLL2CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Get Fractional part of the PLL2 VCO multiplication factor
  * @rmtoll PLL2CFGR7      POSTDIV2          LL_RCC_PLL2_GetFREQDIV_L2
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetFREQDIV_L2(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2CFGR7, RCC_PLL2CFGR7_POSTDIV2) >>  RCC_PLL2CFGR7_POSTDIV2_Pos);
}

#if defined(RCC_PLL3CFGR1_PLLEN)
/**
  * @brief  Set the oscillator used as PLL3 clock source.
  * @note   PLLSRC can be written only when all PLL3 is disabled.
  * @rmtoll MUXSELCFGR      MUXSEL7        LL_RCC_PLL3_SetSource
  * @param  PLLSource parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL3SOURCE_HSI
  *         @arg @ref LL_RCC_PLL3SOURCE_HSE
  *         @arg @ref LL_RCC_PLL3SOURCE_MSI
  *         @arg @ref LL_RCC_PLL3SOURCE_NONE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_SetSource(uint32_t PLLSource)
{
  MODIFY_REG(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL7, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL3 clock source.
  * @rmtoll MUXSELCFGR      MUXSEL7        LL_RCC_PLL3_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL3SOURCE_HSI
  *         @arg @ref LL_RCC_PLL3SOURCE_HSE
  *         @arg @ref LL_RCC_PLL3SOURCE_MSI
  *         @arg @ref LL_RCC_PLL3SOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL7));
}

/**
  * @brief  Enable PLL3
  * @rmtoll PLL3CFGR1           PLLEN         LL_RCC_PLL3_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_Enable(void)
{
  SET_BIT(RCC->PLL3CFGR1, RCC_PLL3CFGR1_PLLEN);
}

/**
  * @brief  Disable PLL3
  * @note Cannot be disabled if the PLL clock is used as a system clock.
  *       This API shall be called only when PLL1 DIVPEN, DIVQEN and DIVREN are
  *       disabled.
  * @rmtoll PLL3CFGR1           PLLEN         LL_RCC_PLL3_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_Disable(void)
{
  CLEAR_BIT(RCC->PLL3CFGR1, RCC_PLL3CFGR1_PLLEN);
}

/**
  * @brief  assert PLL3 Spread Spectrum Modulator reset
  * @rmtoll PLL3CFGR1           SSMODRST         LL_RCC_PLL3_SSMODRST_Assert
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_SSMODRST_Assert(void)
{
  SET_BIT(RCC->PLL3CFGR1, RCC_PLL3CFGR1_SSMODRST);
}

/**
  * @brief  release PLL3 Spread Spectrum Modulator reset
  * @rmtoll PLL3CFGR1           SSMODRST         LL_RCC_PLL3_SSMODRST_Release
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_SSMODRST_Release(void)
{
  CLEAR_BIT(RCC->PLL3CFGR1, RCC_PLL3CFGR1_SSMODRST);
}

/**
  * @brief  Check if PLL3 Spread Spectrum Modulator reset is asserted
  * @rmtoll PLL3CFGR1           SSMODRST        LL_RCC_PLL3_SSMODRST_IsAssert
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_SSMODRST_IsAssert(void)
{
  return ((READ_BIT(RCC->PLL3CFGR1, RCC_PLL3CFGR1_SSMODRST) == RCC_PLL3CFGR1_SSMODRST) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL3 Ready
  * @rmtoll PLL3CFGR1           PLL3RDY        LL_RCC_PLL3_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsReady(void)
{
  return ((READ_BIT(RCC->PLL3CFGR1, RCC_PLL3CFGR1_PLLRDY) == RCC_PLL3CFGR1_PLLRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set Fractional part of the PLL3 VCO multiplication factor
  * @rmtoll PLL3CFGR1      CKREFST          LL_RCC_PLL3_SetCKREFST
  * @param  CKREFST parameter can be a value between 0 and 1 (0x1)
  * 0: Reading 0 means that the PLL{x} reference clock is not running, writing 0 resets the
  * reference clock running detector.
  * 1: Reading 1 means that the PLL{x} reference clock is running, writing 1 resets the
  * reference clock running detector.
  */
__STATIC_INLINE void LL_RCC_PLL3_SetCKREFST(uint32_t CKREFST)
{
  MODIFY_REG(RCC->PLL3CFGR1, RCC_PLL3CFGR1_CKREFST, CKREFST << RCC_PLL3CFGR1_CKREFST_Pos);
}

/**
  * @brief  Check if PLL3 reference clock is running
  * @rmtoll PLL3CFGR1           CKREFST        LL_RCC_PLL3_CKREFST_IsRunning
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_CKREFST_IsRunning(void)
{
  return ((READ_BIT(RCC->PLL3CFGR1, RCC_PLL3CFGR1_CKREFST) == RCC_PLL3CFGR1_CKREFST) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL3 VCO multiplication factor
  * @rmtoll PLL3CFGR2      FBDIV          LL_RCC_PLL3_SetFBDIV
  * @param  FBDIV parameter can be a value between 0 and 4095 (0xFFF)
  */
__STATIC_INLINE void LL_RCC_PLL3_SetFBDIV(uint32_t FBDIV)
{
  MODIFY_REG(RCC->PLL3CFGR2, RCC_PLL3CFGR2_FBDIV, FBDIV << RCC_PLL3CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL3 VCO multiplication factor
  * @rmtoll PLL3CFGR2      FBDIV          LL_RCC_PLL3_GetFBDIV
  * @retval A value between 0 and 4095 (0x0FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetFBDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3CFGR2, RCC_PLL3CFGR2_FBDIV) >>  RCC_PLL3CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL3  reference input clock divide frequency ratio
  * @rmtoll PLL3CFGR2      FREFDIV          LL_RCC_PLL3_SetFREFDIV
  * @param  FREFDIV parameter can be a value between 0 and 63 (0x3F)
  */
__STATIC_INLINE void LL_RCC_PLL3_SetFREFDIV(uint32_t FREFDIV)
{
  MODIFY_REG(RCC->PLL3CFGR2, RCC_PLL3CFGR2_FREFDIV, FREFDIV << RCC_PLL3CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Get PLL3  reference input clock divide frequency ratio
  * @rmtoll PLL3CFGR2      FREFDIV          LL_RCC_PLL3_GetFREFDIV
  * @retval A value between 0 and 63 (0x3F)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetFREFDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3CFGR2, RCC_PLL3CFGR2_FREFDIV) >>  RCC_PLL3CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Set Fractional part of the PLL3 VCO multiplication factor
  * @rmtoll PLL3CFGR3      FRACIN          LL_RCC_PLL3_SetFRACIN
  * @param  FRACIN parameter can be a value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE void LL_RCC_PLL3_SetFRACIN(uint32_t FRACIN)
{
  MODIFY_REG(RCC->PLL3CFGR3, RCC_PLL3CFGR3_FRACIN, FRACIN << RCC_PLL3CFGR3_FRACIN_Pos);
}

/**
  * @brief  Get Fractional part of the PLL3 VCO multiplication factor
  * @rmtoll PLL3CFGR3      FRACIN          LL_RCC_PLL3_GetFRACIN
  * @retval A value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetFRACIN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3CFGR3, RCC_PLL3CFGR3_FRACIN) >>  RCC_PLL3CFGR3_FRACIN_Pos);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL3
  * @rmtoll PLL3CFGR3           SSCGDIS         LL_RCC_PLL3_CSG_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_CSG_Enable(void)
{
  CLEAR_BIT(RCC->PLL3CFGR3, RCC_PLL3CFGR3_SSCGDIS);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL3
  * @rmtoll PLL3CFGR3           SSCGDIS         LL_RCC_PLL3_CSG_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_CSG_Disable(void)
{
  SET_BIT(RCC->PLL3CFGR3, RCC_PLL3CFGR3_SSCGDIS);
}

/**
  * @brief  Check if PLL3Spread Spectrum Modulator  is Enabled
  * @rmtoll PLL3CFGR3           SSCGDIS        LL_RCC_PLL3_CSG_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_CSG_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL3CFGR3, RCC_PLL3CFGR3_SSCGDIS) == RCC_PLL3CFGR3_SSCGDIS) ? 0UL : 1UL);
}

/**
  * @brief  Enable the Spread Spectrum Modulator of PLL3
  * @rmtoll PLL3CFGR3           DACEN         LL_RCC_PLL3DAC_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3DAC_Enable(void)
{
  CLEAR_BIT(RCC->PLL3CFGR3, RCC_PLL3CFGR3_DACEN);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL3
  * @rmtoll PLL3CFGR3           DACEN         LL_RCC_PLL3DAC_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3DAC_Disable(void)
{
  SET_BIT(RCC->PLL3CFGR3, RCC_PLL3CFGR3_DACEN);
}

/**
  * @brief  Check if PLL3 DAC is Enabled
  * @rmtoll PLL3CFGR3           DACEN        LL_RCC_PLL3_DAC_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_DAC_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL3CFGR3, RCC_PLL3CFGR3_DACEN) == RCC_PLL3CFGR3_DACEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable Down-spread modulation of PLL3
  * @rmtoll PLL3CFGR3           DOWNSPREAD         LL_RCC_PLL3DOWNSPREAD_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3DOWNSPREAD_Enable(void)
{
  CLEAR_BIT(RCC->PLL3CFGR3, RCC_PLL3CFGR3_DOWNSPREAD);
}

/**
  * @brief  Enable Center-spread modulation of PLL3
  * @rmtoll PLL3CFGR3           DOWNSPREAD         LL_RCC_PLL3DOWNSPREAD_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3DOWNSPREAD_Disable(void)
{
  SET_BIT(RCC->PLL3CFGR3, RCC_PLL3CFGR3_DOWNSPREAD);
}

/**
  * @brief  Check if PLL3 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL3CFGR4           BYPASS        LL_RCC_PLL3_FOUTPOSTDIV_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_FOUTPOSTDIV_FREF_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL3CFGR4, RCC_PLL3CFGR4_BYPASS) == RCC_PLL3CFGR4_BYPASS) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL3
  * @rmtoll PLL3CFGR4           BYPASS         LL_RCC_PLL3_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_FOUTPOSTDIV_FREF_Enable(void)
{
  SET_BIT(RCC->PLL3CFGR4, RCC_PLL3CFGR4_BYPASS);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL3
  * @rmtoll PLL3CFGR4           BYPASS         LL_RCC_PLL3_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_FOUTPOSTDIV_FREF_Disable(void)
{
  CLEAR_BIT(RCC->PLL3CFGR4, RCC_PLL3CFGR4_BYPASS);
}

/**
  * @brief  Check if PLL3  POSTDIV1 and POSTDIV2 dividers are active
  * @rmtoll PLL3CFGR4           FOUTPOSTDIVEN        LL_RCC_PLL3_FOUTPOSTDIVEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_FOUTPOSTDIVEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL3CFGR4, RCC_PLL3CFGR4_FOUTPOSTDIVEN) == RCC_PLL3CFGR4_FOUTPOSTDIVEN) ? 1UL : 0UL);
}

/**
  * @brief   activate POSTDIV1 and POSTDIV2 on PLL3
  * @rmtoll PLL3CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL3_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_FOUTPOSTDIV_Enable(void)
{
  SET_BIT(RCC->PLL3CFGR4, RCC_PLL3CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  disactivate POSTDIV1 and POSTDIV2 on PLL3
  * @rmtoll PLL3CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL3_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_FOUTPOSTDIV_Disable(void)
{
  CLEAR_BIT(RCC->PLL3CFGR4, RCC_PLL3CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  Check if PLL3 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL3CFGR4           DSMEN        LL_RCC_PLL3_DSMEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_DSMEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL3CFGR4, RCC_PLL3CFGR4_DSMEN) == RCC_PLL3CFGR4_DSMEN) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL3
  * @rmtoll PLL3CFGR4           DSMEN         LL_RCC_PLL3_DSMEN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_DSMEN_Enable(void)
{
  SET_BIT(RCC->PLL3CFGR4, RCC_PLL3CFGR4_DSMEN);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL3
  * @rmtoll PLL3CFGR4           DSMEN         LL_RCC_PLL3_DSMEN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_DSMEN_Disable(void)
{
  CLEAR_BIT(RCC->PLL3CFGR4, RCC_PLL3CFGR4_DSMEN);
}

/** @brief  Configure the PLL3 Clock Spreading Generator
  * @rmtoll PLL3CSGR    DIVVAL, SPREAD  LL_RCC_PLL3_ConfigCSG
  *
  * @param  ModFreq:  Modulation frequency adjustment for PLL3
  *         This parameter must have a value between 0 and 15
  *
  * @param  IncStep: Modulation Depth Adjustment for PLL3
  *         This parameter must have a value between 0 and 31
  * @note   ModFreq x IncStep shall not exceed (2^4)-1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL3_ConfigCSG(uint32_t ModFreq, uint32_t IncStep)
{
  MODIFY_REG(RCC->PLL3CFGR5, (RCC_PLL3CFGR5_DIVVAL | RCC_PLL3CFGR5_SPREAD), \
             (ModFreq | (IncStep << RCC_PLL3CFGR5_SPREAD_Pos)));
}

/**
  * @brief  Get  PLL3 VCO frequency divide level 1
  * @rmtoll PLL3CFGR6      POSTDIV1          LL_RCC_PLL3_ConfigFREQDIV_L1
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL3_ConfigFREQDIV_L1(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL3CFGR6, RCC_PLL3CFGR6_POSTDIV1, POSTDIV << RCC_PLL3CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get Fractional part of the PLL3 VCO multiplication factor
  * @rmtoll PLL3CFGR6      POSTDIV1          LL_RCC_PLL3_GetFREQDIV_L1
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetFREQDIV_L1(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3CFGR6, RCC_PLL3CFGR6_POSTDIV1) >>  RCC_PLL3CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get PLL3  reference input clock divide frequency ratio
  * @rmtoll PLL3CFGR7      POSTDIV2          LL_RCC_PLL3_ConfigFREQDIV_L2
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL3_ConfigFREQDIV_L2(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL3CFGR7, RCC_PLL3CFGR7_POSTDIV2, POSTDIV << RCC_PLL3CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Get Fractional part of the PLL3 VCO multiplication factor
  * @rmtoll PLL3CFGR7      POSTDIV2          LL_RCC_PLL3_GetFREQDIV_L2
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetFREQDIV_L2(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3CFGR7, RCC_PLL3CFGR7_POSTDIV2) >>  RCC_PLL3CFGR7_POSTDIV2_Pos);
}
#endif /* RCC_PLL3CFGR1_PLLEN */

/**
  * @brief  Set the oscillator used as PLL4 clock source.
  * @note   PLLSRC can be written only when all PLL4 is disabled.
  * @rmtoll MUXSELCFGR      MUXSEL0        LL_RCC_PLL4_SetSource
  * @param  PLLSource parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL4SOURCE_HSI
  *         @arg @ref LL_RCC_PLL4SOURCE_HSE
  *         @arg @ref LL_RCC_PLL4SOURCE_MSI
  *         @arg @ref LL_RCC_PLL4SOURCE_NONE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_SetSource(uint32_t PLLSource)
{
  MODIFY_REG(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL0, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL4 clock source.
  * @rmtoll MUXSELCFGR      MUXSEL0        LL_RCC_PLL4_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL4SOURCE_HSI
  *         @arg @ref LL_RCC_PLL4SOURCE_HSE
  *         @arg @ref LL_RCC_PLL4SOURCE_MSI
  *         @arg @ref LL_RCC_PLL4SOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL0));
}

/**
  * @brief  Enable PLL4
  * @rmtoll PLL4CFGR1           PLLEN         LL_RCC_PLL4_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_Enable(void)
{
  SET_BIT(RCC->PLL4CFGR1, RCC_PLL4CFGR1_PLLEN);
}

/**
  * @brief  Disable PLL4
  * @note Cannot be disabled if the PLL clock is used as a system clock.
  *       This API shall be called only when PLL4 DIVPEN, DIVQEN and DIVREN are
  *       disabled.
  * @rmtoll PLL4CFGR1           PLLEN         LL_RCC_PLL4_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_Disable(void)
{
  CLEAR_BIT(RCC->PLL4CFGR1, RCC_PLL4CFGR1_PLLEN);
}

/**
  * @brief  assert PLL4 Spread Spectrum Modulator reset
  * @rmtoll PLL4CFGR1           SSMODRST         LL_RCC_PLL4_SSMODRST_Assert
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_SSMODRST_Assert(void)
{
  SET_BIT(RCC->PLL4CFGR1, RCC_PLL4CFGR1_SSMODRST);
}

/**
  * @brief  release PLL4 Spread Spectrum Modulator reset
  * @rmtoll PLL4CFGR1           SSMODRST         LL_RCC_PLL4_SSMODRST_Release
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_SSMODRST_Release(void)
{
  CLEAR_BIT(RCC->PLL4CFGR1, RCC_PLL4CFGR1_SSMODRST);
}

/**
  * @brief  Check if PLL4 Spread Spectrum Modulator reset is asserted
  * @rmtoll PLL4CFGR1           SSMODRST        LL_RCC_PLL4_SSMODRST_IsAssert
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_SSMODRST_IsAssert(void)
{
  return ((READ_BIT(RCC->PLL4CFGR1, RCC_PLL4CFGR1_SSMODRST) == RCC_PLL4CFGR1_SSMODRST) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL4 Ready
  * @rmtoll PLL4CFGR1           PLL4RDY        LL_RCC_PLL4_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_IsReady(void)
{
  return ((READ_BIT(RCC->PLL4CFGR1, RCC_PLL4CFGR1_PLLRDY) == RCC_PLL4CFGR1_PLLRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set Fractional part of the PLL4 VCO multiplication factor
  * @rmtoll PLL4CFGR1      CKREFST          LL_RCC_PLL4_SetCKREFST
  * @param  CKREFST parameter can be a value between 0 and 1 (0x1)
  * 0: Reading 0 means that the PLL{x} reference clock is not running, writing 0 resets the
  * reference clock running detector.
  * 1: Reading 1 means that the PLL{x} reference clock is running, writing 1 resets the
  * reference clock running detector.
  */
__STATIC_INLINE void LL_RCC_PLL4_SetCKREFST(uint32_t CKREFST)
{
  MODIFY_REG(RCC->PLL4CFGR1, RCC_PLL4CFGR1_CKREFST, CKREFST << RCC_PLL4CFGR1_CKREFST_Pos);
}

/**
  * @brief  Check if PLL4 reference clock is running
  * @rmtoll PLL4CFGR1           CKREFST        LL_RCC_PLL4_CKREFST_IsRunning
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_CKREFST_IsRunning(void)
{
  return ((READ_BIT(RCC->PLL4CFGR1, RCC_PLL4CFGR1_CKREFST) == RCC_PLL4CFGR1_CKREFST) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL4 VCO multiplication factor
  * @rmtoll PLL4CFGR2      FBDIV          LL_RCC_PLL4_SetFBDIV
  * @param  FBDIV parameter can be a value between 0 and 4095 (0xFFF)
  */
__STATIC_INLINE void LL_RCC_PLL4_SetFBDIV(uint32_t FBDIV)
{
  MODIFY_REG(RCC->PLL4CFGR2, RCC_PLL4CFGR2_FBDIV, FBDIV << RCC_PLL4CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL4 VCO multiplication factor
  * @rmtoll PLL4CFGR2      FBDIV          LL_RCC_PLL4_GetFBDIV
  * @retval A value between 0 and 4095 (0x0FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_GetFBDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL4CFGR2, RCC_PLL4CFGR2_FBDIV) >>  RCC_PLL4CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL4  reference input clock divide frequency ratio
  * @rmtoll PLL4CFGR2      FREFDIV          LL_RCC_PLL4_SetFREFDIV
  * @param  FREFDIV parameter can be a value between 0 and 63 (0x3F)
  */
__STATIC_INLINE void LL_RCC_PLL4_SetFREFDIV(uint32_t FREFDIV)
{
  MODIFY_REG(RCC->PLL4CFGR2, RCC_PLL4CFGR2_FREFDIV, FREFDIV << RCC_PLL4CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Get PLL4  reference input clock divide frequency ratio
  * @rmtoll PLL4CFGR2      FREFDIV          LL_RCC_PLL4_GetFREFDIV
  * @retval A value between 0 and 63 (0x3F)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_GetFREFDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL4CFGR2, RCC_PLL4CFGR2_FREFDIV) >>  RCC_PLL4CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Set Fractional part of the PLL4 VCO multiplication factor
  * @rmtoll PLL4CFGR3      FRACIN          LL_RCC_PLL4_SetFRACIN
  * @param  FRACIN parameter can be a value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE void LL_RCC_PLL4_SetFRACIN(uint32_t FRACIN)
{
  MODIFY_REG(RCC->PLL4CFGR3, RCC_PLL4CFGR3_FRACIN, FRACIN << RCC_PLL4CFGR3_FRACIN_Pos);
}

/**
  * @brief  Get Fractional part of the PLL4 VCO multiplication factor
  * @rmtoll PLL4CFGR3      FRACIN          LL_RCC_PLL4_GetFRACIN
  * @retval A value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_GetFRACIN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL4CFGR3, RCC_PLL4CFGR3_FRACIN) >>  RCC_PLL4CFGR3_FRACIN_Pos);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL4
  * @rmtoll PLL4CFGR3           SSCGDIS         LL_RCC_PLL4_CSG_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_CSG_Enable(void)
{
  CLEAR_BIT(RCC->PLL4CFGR3, RCC_PLL4CFGR3_SSCGDIS);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL4
  * @rmtoll PLL4CFGR3           SSCGDIS         LL_RCC_PLL4_CSG_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_CSG_Disable(void)
{
  SET_BIT(RCC->PLL4CFGR3, RCC_PLL4CFGR3_SSCGDIS);
}

/**
  * @brief  Check if PLL4Spread Spectrum Modulator  is Enabled
  * @rmtoll PLL4CFGR3           SSCGDIS        LL_RCC_PLL4_CSG_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_CSG_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL4CFGR3, RCC_PLL4CFGR3_SSCGDIS) == RCC_PLL4CFGR3_SSCGDIS) ? 0UL : 1UL);
}

/**
  * @brief  Enable the Spread Spectrum Modulator of PLL4
  * @rmtoll PLL4CFGR3           DACEN         LL_RCC_PLL4DAC_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4DAC_Enable(void)
{
  CLEAR_BIT(RCC->PLL4CFGR3, RCC_PLL4CFGR3_DACEN);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL4
  * @rmtoll PLL4CFGR3           DACEN         LL_RCC_PLL4DAC_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4DAC_Disable(void)
{
  SET_BIT(RCC->PLL4CFGR3, RCC_PLL4CFGR3_DACEN);
}

/**
  * @brief  Check if PLL4 DAC is Enabled
  * @rmtoll PLL4CFGR3           DACEN        LL_RCC_PLL4_DAC_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_DAC_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL4CFGR3, RCC_PLL4CFGR3_DACEN) == RCC_PLL4CFGR3_DACEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable Down-spread modulation of PLL4
  * @rmtoll PLL4CFGR3           DOWNSPREAD         LL_RCC_PLL4DOWNSPREAD_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4DOWNSPREAD_Enable(void)
{
  CLEAR_BIT(RCC->PLL4CFGR3, RCC_PLL4CFGR3_DOWNSPREAD);
}

/**
  * @brief  Enable Center-spread modulation of PLL4
  * @rmtoll PLL4CFGR3           DOWNSPREAD         LL_RCC_PLL4DOWNSPREAD_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4DOWNSPREAD_Disable(void)
{
  SET_BIT(RCC->PLL4CFGR3, RCC_PLL4CFGR3_DOWNSPREAD);
}

/**
  * @brief  Check if PLL4 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL4CFGR4           BYPASS        LL_RCC_PLL4_FOUTPOSTDIV_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_FOUTPOSTDIV_FREF_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL4CFGR4, RCC_PLL4CFGR4_BYPASS) == RCC_PLL4CFGR4_BYPASS) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL4
  * @rmtoll PLL4CFGR4           BYPASS         LL_RCC_PLL4_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_FOUTPOSTDIV_FREF_Enable(void)
{
  SET_BIT(RCC->PLL4CFGR4, RCC_PLL4CFGR4_BYPASS);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL4
  * @rmtoll PLL4CFGR4           BYPASS         LL_RCC_PLL4_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_FOUTPOSTDIV_FREF_Disable(void)
{
  CLEAR_BIT(RCC->PLL4CFGR4, RCC_PLL4CFGR4_BYPASS);
}

/**
  * @brief  Check if PLL4  POSTDIV1 and POSTDIV2 dividers are active
  * @rmtoll PLL4CFGR4           FOUTPOSTDIVEN        LL_RCC_PLL4_FOUTPOSTDIVEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_FOUTPOSTDIVEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL4CFGR4, RCC_PLL4CFGR4_FOUTPOSTDIVEN) == RCC_PLL4CFGR4_FOUTPOSTDIVEN) ? 1UL : 0UL);
}

/**
  * @brief   activate POSTDIV1 and POSTDIV2 on PLL4
  * @rmtoll PLL4CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL4_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_FOUTPOSTDIV_Enable(void)
{
  SET_BIT(RCC->PLL4CFGR4, RCC_PLL4CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  disactivate POSTDIV1 and POSTDIV2 on PLL4
  * @rmtoll PLL4CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL4_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_FOUTPOSTDIV_Disable(void)
{
  CLEAR_BIT(RCC->PLL4CFGR4, RCC_PLL4CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  Check if PLL4 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL4CFGR4           DSMEN        LL_RCC_PLL4_DSMEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_DSMEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL4CFGR4, RCC_PLL4CFGR4_DSMEN) == RCC_PLL4CFGR4_DSMEN) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL4
  * @rmtoll PLL4CFGR4           DSMEN         LL_RCC_PLL4_DSMEN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_DSMEN_Enable(void)
{
  SET_BIT(RCC->PLL4CFGR4, RCC_PLL4CFGR4_DSMEN);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL4
  * @rmtoll PLL4CFGR4           DSMEN        LL_RCC_PLL4_DSMEN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_DSMEN_Disable(void)
{
  CLEAR_BIT(RCC->PLL4CFGR4, RCC_PLL4CFGR4_DSMEN);
}

/** @brief  Configure the PLL4 Clock Spreading Generator
  * @rmtoll PLL4CSGR    DIVVAL, SPREAD  LL_RCC_PLL4_ConfigCSG
  *
  * @param  ModFreq:  Modulation frequency adjustment for PLL4
  *         This parameter must have a value between 0 and 15
  *
  * @param  IncStep: Modulation Depth Adjustment for PLL4
  *         This parameter must have a value between 0 and 31
  * @note   ModFreq x IncStep shall not exceed (2^4)-1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL4_ConfigCSG(uint32_t ModFreq, uint32_t IncStep)
{
  MODIFY_REG(RCC->PLL4CFGR5, (RCC_PLL4CFGR5_DIVVAL | RCC_PLL4CFGR5_SPREAD), \
             (ModFreq | (IncStep << RCC_PLL4CFGR5_SPREAD_Pos)));
}

/**
  * @brief  Get  PLL4 VCO frequency divide level 1
  * @rmtoll PLL4CFGR6      POSTDIV1          LL_RCC_PLL4_ConfigFREQDIV_L1
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL4_ConfigFREQDIV_L1(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL4CFGR6, RCC_PLL4CFGR6_POSTDIV1, POSTDIV << RCC_PLL4CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get Fractional part of the PLL4 VCO multiplication factor
  * @rmtoll PLL4CFGR6      POSTDIV1          LL_RCC_PLL4_GetFREQDIV_L1
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_GetFREQDIV_L1(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL4CFGR6, RCC_PLL4CFGR6_POSTDIV1) >>  RCC_PLL4CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get PLL4  reference input clock divide frequency ratio
  * @rmtoll PLL4CFGR7      POSTDIV2          LL_RCC_PLL4_ConfigFREQDIV_L2
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL4_ConfigFREQDIV_L2(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL4CFGR7, RCC_PLL4CFGR7_POSTDIV2, POSTDIV << RCC_PLL4CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Get Fractional part of the PLL4 VCO multiplication factor
  * @rmtoll PLL4CFGR7      POSTDIV2          LL_RCC_PLL4_GetFREQDIV_L2
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL4_GetFREQDIV_L2(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL4CFGR7, RCC_PLL4CFGR7_POSTDIV2) >>  RCC_PLL4CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Set the oscillator used as PLL5 clock source.
  * @note   PLLSRC can be written only when all PLL5 is disabled.
  * @rmtoll MUXSELCFGR      MUXSEL1        LL_RCC_PLL5_SetSource
  * @param  PLLSource parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL5SOURCE_HSI
  *         @arg @ref LL_RCC_PLL5SOURCE_HSE
  *         @arg @ref LL_RCC_PLL5SOURCE_MSI
  *         @arg @ref LL_RCC_PLL5SOURCE_NONE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_SetSource(uint32_t PLLSource)
{
  MODIFY_REG(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL1, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL5 clock source.
  * @rmtoll MUXSELCFGR      MUXSEL1        LL_RCC_PLL5_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL5SOURCE_HSI
  *         @arg @ref LL_RCC_PLL5SOURCE_HSE
  *         @arg @ref LL_RCC_PLL5SOURCE_MSI
  *         @arg @ref LL_RCC_PLL5SOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL1));
}

/**
  * @brief  Enable PLL5
  * @rmtoll PLL5CFGR1           PLLEN         LL_RCC_PLL5_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_Enable(void)
{
  SET_BIT(RCC->PLL5CFGR1, RCC_PLL5CFGR1_PLLEN);
}

/**
  * @brief  Disable PLL5
  * @note Cannot be disabled if the PLL clock is used as a system clock.
  *       This API shall be called only when PLL5 DIVPEN, DIVQEN and DIVREN are
  *       disabled.
  * @rmtoll PLL5CFGR1           PLLEN         LL_RCC_PLL5_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_Disable(void)
{
  CLEAR_BIT(RCC->PLL5CFGR1, RCC_PLL5CFGR1_PLLEN);
}

/**
  * @brief  assert PLL5 Spread Spectrum Modulator reset
  * @rmtoll PLL5CFGR1           SSMODRST         LL_RCC_PLL5_SSMODRST_Assert
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_SSMODRST_Assert(void)
{
  SET_BIT(RCC->PLL5CFGR1, RCC_PLL5CFGR1_SSMODRST);
}

/**
  * @brief  release PLL5 Spread Spectrum Modulator reset
  * @rmtoll PLL5CFGR1           SSMODRST         LL_RCC_PLL5_SSMODRST_Release
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_SSMODRST_Release(void)
{
  CLEAR_BIT(RCC->PLL5CFGR1, RCC_PLL5CFGR1_SSMODRST);
}

/**
  * @brief  Check if PLL5 Spread Spectrum Modulator reset is asserted
  * @rmtoll PLL5CFGR1           SSMODRST        LL_RCC_PLL5_SSMODRST_IsAssert
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_SSMODRST_IsAssert(void)
{
  return ((READ_BIT(RCC->PLL5CFGR1, RCC_PLL5CFGR1_SSMODRST) == RCC_PLL5CFGR1_SSMODRST) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL5 Ready
  * @rmtoll PLL5CFGR1           PLL5RDY        LL_RCC_PLL5_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_IsReady(void)
{
  return ((READ_BIT(RCC->PLL5CFGR1, RCC_PLL5CFGR1_PLLRDY) == RCC_PLL5CFGR1_PLLRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set Fractional part of the PLL5 VCO multiplication factor
  * @rmtoll PLL5CFGR1      CKREFST          LL_RCC_PLL5_SetCKREFST
  * @param  CKREFST parameter can be a value between 0 and 1 (0x1)
  * 0: Reading 0 means that the PLL{x} reference clock is not running, writing 0 resets the
  * reference clock running detector.
  * 1: Reading 1 means that the PLL{x} reference clock is running, writing 1 resets the
  * reference clock running detector.
  */
__STATIC_INLINE void LL_RCC_PLL5_SetCKREFST(uint32_t CKREFST)
{
  MODIFY_REG(RCC->PLL5CFGR1, RCC_PLL5CFGR1_CKREFST, CKREFST << RCC_PLL5CFGR1_CKREFST_Pos);
}

/**
  * @brief  Check if PLL5 reference clock is running
  * @rmtoll PLL5CFGR1           CKREFST        LL_RCC_PLL5_CKREFST_IsRunning
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_CKREFST_IsRunning(void)
{
  return ((READ_BIT(RCC->PLL5CFGR1, RCC_PLL5CFGR1_CKREFST) == RCC_PLL5CFGR1_CKREFST) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL5 VCO multiplication factor
  * @rmtoll PLL5CFGR2      FBDIV          LL_RCC_PLL5_SetFBDIV
  * @param  FBDIV parameter can be a value between 0 and 4095 (0xFFF)
  */
__STATIC_INLINE void LL_RCC_PLL5_SetFBDIV(uint32_t FBDIV)
{
  MODIFY_REG(RCC->PLL5CFGR2, RCC_PLL5CFGR2_FBDIV, FBDIV << RCC_PLL5CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL5 VCO multiplication factor
  * @rmtoll PLL5CFGR2      FBDIV          LL_RCC_PLL5_GetFBDIV
  * @retval A value between 0 and 4095 (0x0FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_GetFBDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL5CFGR2, RCC_PLL5CFGR2_FBDIV) >>  RCC_PLL5CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL5  reference input clock divide frequency ratio
  * @rmtoll PLL5CFGR2      FREFDIV          LL_RCC_PLL5_SetFREFDIV
  * @param  FREFDIV parameter can be a value between 0 and 63 (0x3F)
  */
__STATIC_INLINE void LL_RCC_PLL5_SetFREFDIV(uint32_t FREFDIV)
{
  MODIFY_REG(RCC->PLL5CFGR2, RCC_PLL5CFGR2_FREFDIV, FREFDIV << RCC_PLL5CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Get PLL5  reference input clock divide frequency ratio
  * @rmtoll PLL5CFGR2      FREFDIV          LL_RCC_PLL5_GetFREFDIV
  * @retval A value between 0 and 63 (0x3F)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_GetFREFDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL5CFGR2, RCC_PLL5CFGR2_FREFDIV) >>  RCC_PLL5CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Set Fractional part of the PLL5 VCO multiplication factor
  * @rmtoll PLL5CFGR3      FRACIN          LL_RCC_PLL5_SetFRACIN
  * @param  FRACIN parameter can be a value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE void LL_RCC_PLL5_SetFRACIN(uint32_t FRACIN)
{
  MODIFY_REG(RCC->PLL5CFGR3, RCC_PLL5CFGR3_FRACIN, FRACIN << RCC_PLL5CFGR3_FRACIN_Pos);
}

/**
  * @brief  Get Fractional part of the PLL5 VCO multiplication factor
  * @rmtoll PLL5CFGR3      FRACIN          LL_RCC_PLL5_GetFRACIN
  * @retval A value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_GetFRACIN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL5CFGR3, RCC_PLL5CFGR3_FRACIN) >>  RCC_PLL5CFGR3_FRACIN_Pos);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL5
  * @rmtoll PLL5CFGR3           SSCGDIS         LL_RCC_PLL5_CSG_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_CSG_Enable(void)
{
  CLEAR_BIT(RCC->PLL5CFGR3, RCC_PLL5CFGR3_SSCGDIS);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL5
  * @rmtoll PLL5CFGR3           SSCGDIS         LL_RCC_PLL5_CSG_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_CSG_Disable(void)
{
  SET_BIT(RCC->PLL5CFGR3, RCC_PLL5CFGR3_SSCGDIS);
}

/**
  * @brief  Check if PLL5Spread Spectrum Modulator  is Enabled
  * @rmtoll PLL5CFGR3           SSCGDIS        LL_RCC_PLL5_CSG_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_CSG_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL5CFGR3, RCC_PLL5CFGR3_SSCGDIS) == RCC_PLL5CFGR3_SSCGDIS) ? 0UL : 1UL);
}

/**
  * @brief  Enable the Spread Spectrum Modulator of PLL5
  * @rmtoll PLL5CFGR3           DACEN         LL_RCC_PLL5DAC_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5DAC_Enable(void)
{
  CLEAR_BIT(RCC->PLL5CFGR3, RCC_PLL5CFGR3_DACEN);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL5
  * @rmtoll PLL5CFGR3           DACEN         LL_RCC_PLL5DAC_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5DAC_Disable(void)
{
  SET_BIT(RCC->PLL5CFGR3, RCC_PLL5CFGR3_DACEN);
}

/**
  * @brief  Check if PLL5 DAC is Enabled
  * @rmtoll PLL5CFGR3           DACEN        LL_RCC_PLL5_DAC_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_DAC_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL5CFGR3, RCC_PLL5CFGR3_DACEN) == RCC_PLL5CFGR3_DACEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable Down-spread modulation of PLL5
  * @rmtoll PLL5CFGR3           DOWNSPREAD         LL_RCC_PLL5DOWNSPREAD_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5DOWNSPREAD_Enable(void)
{
  CLEAR_BIT(RCC->PLL5CFGR3, RCC_PLL5CFGR3_DOWNSPREAD);
}

/**
  * @brief  Enable Center-spread modulation of PLL5
  * @rmtoll PLL5CFGR3           DOWNSPREAD         LL_RCC_PLL5DOWNSPREAD_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5DOWNSPREAD_Disable(void)
{
  SET_BIT(RCC->PLL5CFGR3, RCC_PLL5CFGR3_DOWNSPREAD);
}

/**
  * @brief  Check if PLL5 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL5CFGR4           BYPASS        LL_RCC_PLL5_FOUTPOSTDIV_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_FOUTPOSTDIV_FREF_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL5CFGR4, RCC_PLL5CFGR4_BYPASS) == RCC_PLL5CFGR4_BYPASS) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL5
  * @rmtoll PLL5CFGR4           BYPASS         LL_RCC_PLL5_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_FOUTPOSTDIV_FREF_Enable(void)
{
  SET_BIT(RCC->PLL5CFGR4, RCC_PLL5CFGR4_BYPASS);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL5
  * @rmtoll PLL5CFGR4           BYPASS         LL_RCC_PLL5_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_FOUTPOSTDIV_FREF_Disable(void)
{
  CLEAR_BIT(RCC->PLL5CFGR4, RCC_PLL5CFGR4_BYPASS);
}

/**
  * @brief  Check if PLL5  POSTDIV1 and POSTDIV2 dividers are active
  * @rmtoll PLL5CFGR4           FOUTPOSTDIVEN        LL_RCC_PLL5_FOUTPOSTDIVEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_FOUTPOSTDIVEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL5CFGR4, RCC_PLL5CFGR4_FOUTPOSTDIVEN) == RCC_PLL5CFGR4_FOUTPOSTDIVEN) ? 1UL : 0UL);
}

/**
  * @brief   activate POSTDIV1 and POSTDIV2 on PLL5
  * @rmtoll PLL5CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL5_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_FOUTPOSTDIV_Enable(void)
{
  SET_BIT(RCC->PLL5CFGR4, RCC_PLL5CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  disactivate POSTDIV1 and POSTDIV2 on PLL5
  * @rmtoll PLL5CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL5_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_FOUTPOSTDIV_Disable(void)
{
  CLEAR_BIT(RCC->PLL5CFGR4, RCC_PLL5CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  Check if PLL5 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL5CFGR4           DSMEN        LL_RCC_PLL5_DSMEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_DSMEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL5CFGR4, RCC_PLL5CFGR4_DSMEN) == RCC_PLL5CFGR4_DSMEN) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL5
  * @rmtoll PLL5CFGR4           DSMEN         LL_RCC_PLL5_DSMEN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_DSMEN_Enable(void)
{
  SET_BIT(RCC->PLL5CFGR4, RCC_PLL5CFGR4_DSMEN);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL5
  * @rmtoll PLL5CFGR4           DSMEN         LL_RCC_PLL5_DSMEN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_DSMEN_Disable(void)
{
  CLEAR_BIT(RCC->PLL5CFGR4, RCC_PLL5CFGR4_DSMEN);
}

/** @brief  Configure the PLL5 Clock Spreading Generator
  * @rmtoll PLL5CSGR    DIVVAL, SPREAD  LL_RCC_PLL5_ConfigCSG
  *
  * @param  ModFreq:  Modulation frequency adjustment for PLL5
  *         This parameter must have a value between 0 and 15
  *
  * @param  IncStep: Modulation Depth Adjustment for PLL5
  *         This parameter must have a value between 0 and 31
  * @note   ModFreq x IncStep shall not exceed (2^4)-1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL5_ConfigCSG(uint32_t ModFreq, uint32_t IncStep)
{
  MODIFY_REG(RCC->PLL5CFGR5, (RCC_PLL5CFGR5_DIVVAL | RCC_PLL5CFGR5_SPREAD), \
             (ModFreq | (IncStep << RCC_PLL5CFGR5_SPREAD_Pos)));
}

/**
  * @brief  Get  PLL5 VCO frequency divide level 1
  * @rmtoll PLL5CFGR6      POSTDIV1          LL_RCC_PLL5_ConfigFREQDIV_L1
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL5_ConfigFREQDIV_L1(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL5CFGR6, RCC_PLL5CFGR6_POSTDIV1, POSTDIV << RCC_PLL5CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get Fractional part of the PLL5 VCO multiplication factor
  * @rmtoll PLL5CFGR6      POSTDIV1          LL_RCC_PLL5_GetFREQDIV_L1
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_GetFREQDIV_L1(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL5CFGR6, RCC_PLL5CFGR6_POSTDIV1) >>  RCC_PLL5CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get PLL5  reference input clock divide frequency ratio
  * @rmtoll PLL5CFGR7      POSTDIV2          LL_RCC_PLL5_ConfigFREQDIV_L2
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL5_ConfigFREQDIV_L2(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL5CFGR7, RCC_PLL5CFGR7_POSTDIV2, POSTDIV << RCC_PLL5CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Get Fractional part of the PLL5 VCO multiplication factor
  * @rmtoll PLL5CFGR7      POSTDIV2          LL_RCC_PLL5_GetFREQDIV_L2
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL5_GetFREQDIV_L2(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL5CFGR7, RCC_PLL5CFGR7_POSTDIV2) >>  RCC_PLL5CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Set the oscillator used as PLL6 clock source.
  * @note   PLLSRC can be written only when all PLL6 is disabled.
  * @rmtoll MUXSELCFGR      MUXSEL2        LL_RCC_PLL6_SetSource
  * @param  PLLSource parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL6SOURCE_HSI
  *         @arg @ref LL_RCC_PLL6SOURCE_HSE
  *         @arg @ref LL_RCC_PLL6SOURCE_MSI
  *         @arg @ref LL_RCC_PLL6SOURCE_NONE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_SetSource(uint32_t PLLSource)
{
  MODIFY_REG(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL2, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL6 clock source.
  * @rmtoll MUXSELCFGR      MUXSEL2        LL_RCC_PLL6_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL6SOURCE_HSI
  *         @arg @ref LL_RCC_PLL6SOURCE_HSE
  *         @arg @ref LL_RCC_PLL6SOURCE_MSI
  *         @arg @ref LL_RCC_PLL6SOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL2));
}

/**
  * @brief  Enable PLL6
  * @rmtoll PLL6CFGR1           PLLEN         LL_RCC_PLL6_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_Enable(void)
{
  SET_BIT(RCC->PLL6CFGR1, RCC_PLL6CFGR1_PLLEN);
}

/**
  * @brief  Disable PLL6
  * @note Cannot be disabled if the PLL clock is used as a system clock.
  *       This API shall be called only when PLL6 DIVPEN, DIVQEN and DIVREN are
  *       disabled.
  * @rmtoll PLL6CFGR1           PLLEN         LL_RCC_PLL6_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_Disable(void)
{
  CLEAR_BIT(RCC->PLL6CFGR1, RCC_PLL6CFGR1_PLLEN);
}

/**
  * @brief  assert PLL6 Spread Spectrum Modulator reset
  * @rmtoll PLL6CFGR1           SSMODRST         LL_RCC_PLL6_SSMODRST_Assert
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_SSMODRST_Assert(void)
{
  SET_BIT(RCC->PLL6CFGR1, RCC_PLL6CFGR1_SSMODRST);
}

/**
  * @brief  release PLL6 Spread Spectrum Modulator reset
  * @rmtoll PLL6CFGR1           SSMODRST         LL_RCC_PLL6_SSMODRST_Release
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_SSMODRST_Release(void)
{
  CLEAR_BIT(RCC->PLL6CFGR1, RCC_PLL6CFGR1_SSMODRST);
}

/**
  * @brief  Check if PLL6 Spread Spectrum Modulator reset is asserted
  * @rmtoll PLL6CFGR1           SSMODRST        LL_RCC_PLL6_SSMODRST_IsAssert
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_SSMODRST_IsAssert(void)
{
  return ((READ_BIT(RCC->PLL6CFGR1, RCC_PLL6CFGR1_SSMODRST) == RCC_PLL6CFGR1_SSMODRST) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL6 Ready
  * @rmtoll PLL6CFGR1           PLL6RDY        LL_RCC_PLL6_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_IsReady(void)
{
  return ((READ_BIT(RCC->PLL6CFGR1, RCC_PLL6CFGR1_PLLRDY) == RCC_PLL6CFGR1_PLLRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set Fractional part of the PLL6 VCO multiplication factor
  * @rmtoll PLL6CFGR1      CKREFST          LL_RCC_PLL6_SetCKREFST
  * @param  CKREFST parameter can be a value between 0 and 1 (0x1)
  * 0: Reading 0 means that the PLL{x} reference clock is not running, writing 0 resets the
  * reference clock running detector.
  * 1: Reading 1 means that the PLL{x} reference clock is running, writing 1 resets the
  * reference clock running detector.
  */
__STATIC_INLINE void LL_RCC_PLL6_SetCKREFST(uint32_t CKREFST)
{
  MODIFY_REG(RCC->PLL6CFGR1, RCC_PLL6CFGR1_CKREFST, CKREFST << RCC_PLL6CFGR1_CKREFST_Pos);
}

/**
  * @brief  Check if PLL6 reference clock is running
  * @rmtoll PLL6CFGR1           CKREFST        LL_RCC_PLL6_CKREFST_IsRunning
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_CKREFST_IsRunning(void)
{
  return ((READ_BIT(RCC->PLL6CFGR1, RCC_PLL6CFGR1_CKREFST) == RCC_PLL6CFGR1_CKREFST) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL6 VCO multiplication factor
  * @rmtoll PLL6CFGR2      FBDIV          LL_RCC_PLL6_SetFBDIV
  * @param  FBDIV parameter can be a value between 0 and 4095 (0xFFF)
  */
__STATIC_INLINE void LL_RCC_PLL6_SetFBDIV(uint32_t FBDIV)
{
  MODIFY_REG(RCC->PLL6CFGR2, RCC_PLL6CFGR2_FBDIV, FBDIV << RCC_PLL6CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL6 VCO multiplication factor
  * @rmtoll PLL6CFGR2      FBDIV          LL_RCC_PLL6_GetFBDIV
  * @retval A value between 0 and 4095 (0x0FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_GetFBDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL6CFGR2, RCC_PLL6CFGR2_FBDIV) >>  RCC_PLL6CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL6  reference input clock divide frequency ratio
  * @rmtoll PLL6CFGR2      FREFDIV          LL_RCC_PLL6_SetFREFDIV
  * @param  FREFDIV parameter can be a value between 0 and 63 (0x3F)
  */
__STATIC_INLINE void LL_RCC_PLL6_SetFREFDIV(uint32_t FREFDIV)
{
  MODIFY_REG(RCC->PLL6CFGR2, RCC_PLL6CFGR2_FREFDIV, FREFDIV << RCC_PLL6CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Get PLL6  reference input clock divide frequency ratio
  * @rmtoll PLL6CFGR2      FREFDIV          LL_RCC_PLL6_GetFREFDIV
  * @retval A value between 0 and 63 (0x3F)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_GetFREFDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL6CFGR2, RCC_PLL6CFGR2_FREFDIV) >>  RCC_PLL6CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Set Fractional part of the PLL6 VCO multiplication factor
  * @rmtoll PLL6CFGR3      FRACIN          LL_RCC_PLL6_SetFRACIN
  * @param  FRACIN parameter can be a value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE void LL_RCC_PLL6_SetFRACIN(uint32_t FRACIN)
{
  MODIFY_REG(RCC->PLL6CFGR3, RCC_PLL6CFGR3_FRACIN, FRACIN << RCC_PLL6CFGR3_FRACIN_Pos);
}

/**
  * @brief  Get Fractional part of the PLL6 VCO multiplication factor
  * @rmtoll PLL6CFGR3      FRACIN          LL_RCC_PLL6_GetFRACIN
  * @retval A value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_GetFRACIN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL6CFGR3, RCC_PLL6CFGR3_FRACIN) >>  RCC_PLL6CFGR3_FRACIN_Pos);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL6
  * @rmtoll PLL6CFGR3           SSCGDIS         LL_RCC_PLL6_CSG_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_CSG_Enable(void)
{
  CLEAR_BIT(RCC->PLL6CFGR3, RCC_PLL6CFGR3_SSCGDIS);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL6
  * @rmtoll PLL6CFGR3           SSCGDIS         LL_RCC_PLL6_CSG_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_CSG_Disable(void)
{
  SET_BIT(RCC->PLL6CFGR3, RCC_PLL6CFGR3_SSCGDIS);
}

/**
  * @brief  Check if PLL6Spread Spectrum Modulator  is Enabled
  * @rmtoll PLL6CFGR3           SSCGDIS        LL_RCC_PLL6_CSG_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_CSG_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL6CFGR3, RCC_PLL6CFGR3_SSCGDIS) == RCC_PLL6CFGR3_SSCGDIS) ? 0UL : 1UL);
}

/**
  * @brief  Enable the Spread Spectrum Modulator of PLL6
  * @rmtoll PLL6CFGR3           DACEN         LL_RCC_PLL6DAC_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6DAC_Enable(void)
{
  CLEAR_BIT(RCC->PLL6CFGR3, RCC_PLL6CFGR3_DACEN);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL6
  * @rmtoll PLL6CFGR3           DACEN         LL_RCC_PLL6DAC_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6DAC_Disable(void)
{
  SET_BIT(RCC->PLL6CFGR3, RCC_PLL6CFGR3_DACEN);
}

/**
  * @brief  Check if PLL6 DAC is Enabled
  * @rmtoll PLL6CFGR3           DACEN        LL_RCC_PLL6_DAC_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_DAC_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL6CFGR3, RCC_PLL6CFGR3_DACEN) == RCC_PLL6CFGR3_DACEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable Down-spread modulation of PLL6
  * @rmtoll PLL6CFGR3           DOWNSPREAD         LL_RCC_PLL6DOWNSPREAD_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6DOWNSPREAD_Enable(void)
{
  CLEAR_BIT(RCC->PLL6CFGR3, RCC_PLL6CFGR3_DOWNSPREAD);
}

/**
  * @brief  Enable Center-spread modulation of PLL6
  * @rmtoll PLL6CFGR3           DOWNSPREAD         LL_RCC_PLL6DOWNSPREAD_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6DOWNSPREAD_Disable(void)
{
  SET_BIT(RCC->PLL6CFGR3, RCC_PLL6CFGR3_DOWNSPREAD);
}

/**
  * @brief  Check if PLL6 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL6CFGR4           BYPASS        LL_RCC_PLL6_FOUTPOSTDIV_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_FOUTPOSTDIV_FREF_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL6CFGR4, RCC_PLL6CFGR4_BYPASS) == RCC_PLL6CFGR4_BYPASS) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL6
  * @rmtoll PLL6CFGR4           BYPASS         LL_RCC_PLL6_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_FOUTPOSTDIV_FREF_Enable(void)
{
  SET_BIT(RCC->PLL6CFGR4, RCC_PLL6CFGR4_BYPASS);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL6
  * @rmtoll PLL6CFGR4           BYPASS         LL_RCC_PLL6_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_FOUTPOSTDIV_FREF_Disable(void)
{
  CLEAR_BIT(RCC->PLL6CFGR4, RCC_PLL6CFGR4_BYPASS);
}

/**
  * @brief  Check if PLL6  POSTDIV1 and POSTDIV2 dividers are active
  * @rmtoll PLL6CFGR4           FOUTPOSTDIVEN        LL_RCC_PLL6_FOUTPOSTDIVEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_FOUTPOSTDIVEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL6CFGR4, RCC_PLL6CFGR4_FOUTPOSTDIVEN) == RCC_PLL6CFGR4_FOUTPOSTDIVEN) ? 1UL : 0UL);
}

/**
  * @brief   activate POSTDIV1 and POSTDIV2 on PLL6
  * @rmtoll PLL6CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL6_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_FOUTPOSTDIV_Enable(void)
{
  SET_BIT(RCC->PLL6CFGR4, RCC_PLL6CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  disactivate POSTDIV1 and POSTDIV2 on PLL6
  * @rmtoll PLL6CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL6_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_FOUTPOSTDIV_Disable(void)
{
  CLEAR_BIT(RCC->PLL6CFGR4, RCC_PLL6CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  Check if PLL6 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL6CFGR4           DSMEN        LL_RCC_PLL6_DSMEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_DSMEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL6CFGR4, RCC_PLL6CFGR4_DSMEN) == RCC_PLL6CFGR4_DSMEN) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL6
  * @rmtoll PLL6CFGR4           DSMEN         LL_RCC_PLL6_DSMEN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_DSMEN_Enable(void)
{
  SET_BIT(RCC->PLL6CFGR4, RCC_PLL6CFGR4_DSMEN);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL6
  * @rmtoll PLL6CFGR4           DSMEN         LL_RCC_PLL6_DSMEN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_DSMEN_Disable(void)
{
  CLEAR_BIT(RCC->PLL6CFGR4, RCC_PLL6CFGR4_DSMEN);
}

/** @brief  Configure the PLL6 Clock Spreading Generator
  * @rmtoll PLL6CSGR    DIVVAL, SPREAD  LL_RCC_PLL6_ConfigCSG
  *
  * @param  ModFreq:  Modulation frequency adjustment for PLL6
  *         This parameter must have a value between 0 and 15
  *
  * @param  IncStep: Modulation Depth Adjustment for PLL6
  *         This parameter must have a value between 0 and 31
  * @note   ModFreq x IncStep shall not exceed (2^4)-1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL6_ConfigCSG(uint32_t ModFreq, uint32_t IncStep)
{
  MODIFY_REG(RCC->PLL6CFGR5, (RCC_PLL6CFGR5_DIVVAL | RCC_PLL6CFGR5_SPREAD), \
             (ModFreq | (IncStep << RCC_PLL6CFGR5_SPREAD_Pos)));
}

/**
  * @brief  Get  PLL6 VCO frequency divide level 1
  * @rmtoll PLL6CFGR6      POSTDIV1          LL_RCC_PLL6_ConfigFREQDIV_L1
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL6_ConfigFREQDIV_L1(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL6CFGR6, RCC_PLL6CFGR6_POSTDIV1, POSTDIV << RCC_PLL6CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get Fractional part of the PLL6 VCO multiplication factor
  * @rmtoll PLL6CFGR6      POSTDIV1          LL_RCC_PLL6_GetFREQDIV_L1
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_GetFREQDIV_L1(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL6CFGR6, RCC_PLL6CFGR6_POSTDIV1) >>  RCC_PLL6CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get PLL6  reference input clock divide frequency ratio
  * @rmtoll PLL6CFGR7      POSTDIV2          LL_RCC_PLL6_ConfigFREQDIV_L2
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL6_ConfigFREQDIV_L2(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL6CFGR7, RCC_PLL6CFGR7_POSTDIV2, POSTDIV << RCC_PLL6CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Get Fractional part of the PLL6 VCO multiplication factor
  * @rmtoll PLL6CFGR7      POSTDIV2          LL_RCC_PLL6_GetFREQDIV_L2
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL6_GetFREQDIV_L2(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL6CFGR7, RCC_PLL6CFGR7_POSTDIV2) >>  RCC_PLL6CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Set the oscillator used as PLL7 clock source.
  * @note   PLLSRC can be written only when all PLL7 is disabled.
  * @rmtoll MUXSELCFGR      MUXSEL3        LL_RCC_PLL7_SetSource
  * @param  PLLSource parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL7SOURCE_HSI
  *         @arg @ref LL_RCC_PLL7SOURCE_HSE
  *         @arg @ref LL_RCC_PLL7SOURCE_MSI
  *         @arg @ref LL_RCC_PLL7SOURCE_NONE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_SetSource(uint32_t PLLSource)
{
  MODIFY_REG(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL3, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL7 clock source.
  * @rmtoll MUXSELCFGR      MUXSEL3        LL_RCC_PLL7_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL7SOURCE_HSI
  *         @arg @ref LL_RCC_PLL7SOURCE_HSE
  *         @arg @ref LL_RCC_PLL7SOURCE_MSI
  *         @arg @ref LL_RCC_PLL7SOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL3));
}

/**
  * @brief  Enable PLL7
  * @rmtoll PLL7CFGR1           PLLEN         LL_RCC_PLL7_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_Enable(void)
{
  SET_BIT(RCC->PLL7CFGR1, RCC_PLL7CFGR1_PLLEN);
}

/**
  * @brief  Disable PLL7
  * @note Cannot be disabled if the PLL clock is used as a system clock.
  *       This API shall be called only when PLL7 DIVPEN, DIVQEN and DIVREN are
  *       disabled.
  * @rmtoll PLL7CFGR1           PLLEN         LL_RCC_PLL7_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_Disable(void)
{
  CLEAR_BIT(RCC->PLL7CFGR1, RCC_PLL7CFGR1_PLLEN);
}

/**
  * @brief  assert PLL7 Spread Spectrum Modulator reset
  * @rmtoll PLL7CFGR1           SSMODRST         LL_RCC_PLL7_SSMODRST_Assert
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_SSMODRST_Assert(void)
{
  SET_BIT(RCC->PLL7CFGR1, RCC_PLL7CFGR1_SSMODRST);
}

/**
  * @brief  release PLL7 Spread Spectrum Modulator reset
  * @rmtoll PLL7CFGR1           SSMODRST         LL_RCC_PLL7_SSMODRST_Release
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_SSMODRST_Release(void)
{
  CLEAR_BIT(RCC->PLL7CFGR1, RCC_PLL7CFGR1_SSMODRST);
}

/**
  * @brief  Check if PLL7 Spread Spectrum Modulator reset is asserted
  * @rmtoll PLL7CFGR1           SSMODRST        LL_RCC_PLL7_SSMODRST_IsAssert
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_SSMODRST_IsAssert(void)
{
  return ((READ_BIT(RCC->PLL7CFGR1, RCC_PLL7CFGR1_SSMODRST) == RCC_PLL7CFGR1_SSMODRST) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL7 Ready
  * @rmtoll PLL7CFGR1           PLL7RDY        LL_RCC_PLL7_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_IsReady(void)
{
  return ((READ_BIT(RCC->PLL7CFGR1, RCC_PLL7CFGR1_PLLRDY) == RCC_PLL7CFGR1_PLLRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set Fractional part of the PLL7 VCO multiplication factor
  * @rmtoll PLL7CFGR1      CKREFST          LL_RCC_PLL7_SetCKREFST
  * @param  CKREFST parameter can be a value between 0 and 1 (0x1)
  * 0: Reading 0 means that the PLL{x} reference clock is not running, writing 0 resets the
  * reference clock running detector.
  * 1: Reading 1 means that the PLL{x} reference clock is running, writing 1 resets the
  * reference clock running detector.
  */
__STATIC_INLINE void LL_RCC_PLL7_SetCKREFST(uint32_t CKREFST)
{
  MODIFY_REG(RCC->PLL7CFGR1, RCC_PLL7CFGR1_CKREFST, CKREFST << RCC_PLL7CFGR1_CKREFST_Pos);
}

/**
  * @brief  Check if PLL7 reference clock is running
  * @rmtoll PLL7CFGR1           CKREFST        LL_RCC_PLL7_CKREFST_IsRunning
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_CKREFST_IsRunning(void)
{
  return ((READ_BIT(RCC->PLL7CFGR1, RCC_PLL7CFGR1_CKREFST) == RCC_PLL7CFGR1_CKREFST) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL7 VCO multiplication factor
  * @rmtoll PLL7CFGR2      FBDIV          LL_RCC_PLL7_SetFBDIV
  * @param  FBDIV parameter can be a value between 0 and 4095 (0xFFF)
  */
__STATIC_INLINE void LL_RCC_PLL7_SetFBDIV(uint32_t FBDIV)
{
  MODIFY_REG(RCC->PLL7CFGR2, RCC_PLL7CFGR2_FBDIV, FBDIV << RCC_PLL7CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL7 VCO multiplication factor
  * @rmtoll PLL7CFGR2      FBDIV          LL_RCC_PLL7_GetFBDIV
  * @retval A value between 0 and 4095 (0x0FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_GetFBDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL7CFGR2, RCC_PLL7CFGR2_FBDIV) >>  RCC_PLL7CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL7  reference input clock divide frequency ratio
  * @rmtoll PLL7CFGR2      FREFDIV          LL_RCC_PLL7_SetFREFDIV
  * @param  FREFDIV parameter can be a value between 0 and 63 (0x3F)
  */
__STATIC_INLINE void LL_RCC_PLL7_SetFREFDIV(uint32_t FREFDIV)
{
  MODIFY_REG(RCC->PLL7CFGR2, RCC_PLL7CFGR2_FREFDIV, FREFDIV << RCC_PLL7CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Get PLL7  reference input clock divide frequency ratio
  * @rmtoll PLL7CFGR2      FREFDIV          LL_RCC_PLL7_GetFREFDIV
  * @retval A value between 0 and 63 (0x3F)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_GetFREFDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL7CFGR2, RCC_PLL7CFGR2_FREFDIV) >>  RCC_PLL7CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Set Fractional part of the PLL7 VCO multiplication factor
  * @rmtoll PLL7CFGR3      FRACIN          LL_RCC_PLL7_SetFRACIN
  * @param  FRACIN parameter can be a value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE void LL_RCC_PLL7_SetFRACIN(uint32_t FRACIN)
{
  MODIFY_REG(RCC->PLL7CFGR3, RCC_PLL7CFGR3_FRACIN, FRACIN << RCC_PLL7CFGR3_FRACIN_Pos);
}

/**
  * @brief  Get Fractional part of the PLL7 VCO multiplication factor
  * @rmtoll PLL7CFGR3      FRACIN          LL_RCC_PLL7_GetFRACIN
  * @retval A value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_GetFRACIN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL7CFGR3, RCC_PLL7CFGR3_FRACIN) >>  RCC_PLL7CFGR3_FRACIN_Pos);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL7
  * @rmtoll PLL7CFGR3           SSCGDIS         LL_RCC_PLL7_CSG_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_CSG_Enable(void)
{
  CLEAR_BIT(RCC->PLL7CFGR3, RCC_PLL7CFGR3_SSCGDIS);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL7
  * @rmtoll PLL7CFGR3           SSCGDIS         LL_RCC_PLL7_CSG_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_CSG_Disable(void)
{
  SET_BIT(RCC->PLL7CFGR3, RCC_PLL7CFGR3_SSCGDIS);
}

/**
  * @brief  Check if PLL7Spread Spectrum Modulator  is Enabled
  * @rmtoll PLL7CFGR3           SSCGDIS        LL_RCC_PLL7_CSG_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_CSG_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL7CFGR3, RCC_PLL7CFGR3_SSCGDIS) == RCC_PLL7CFGR3_SSCGDIS) ? 0UL : 1UL);
}

/**
  * @brief  Enable the Spread Spectrum Modulator of PLL7
  * @rmtoll PLL7CFGR3           DACEN         LL_RCC_PLL7DAC_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7DAC_Enable(void)
{
  CLEAR_BIT(RCC->PLL7CFGR3, RCC_PLL7CFGR3_DACEN);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL7
  * @rmtoll PLL7CFGR3           DACEN         LL_RCC_PLL7DAC_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7DAC_Disable(void)
{
  SET_BIT(RCC->PLL7CFGR3, RCC_PLL7CFGR3_DACEN);
}

/**
  * @brief  Check if PLL7 DAC is Enabled
  * @rmtoll PLL7CFGR3           DACEN        LL_RCC_PLL7_DAC_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_DAC_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL7CFGR3, RCC_PLL7CFGR3_DACEN) == RCC_PLL7CFGR3_DACEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable Down-spread modulation of PLL7
  * @rmtoll PLL7CFGR3           DOWNSPREAD         LL_RCC_PLL7DOWNSPREAD_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7DOWNSPREAD_Enable(void)
{
  CLEAR_BIT(RCC->PLL7CFGR3, RCC_PLL7CFGR3_DOWNSPREAD);
}

/**
  * @brief  Enable Center-spread modulation of PLL7
  * @rmtoll PLL7CFGR3           DOWNSPREAD         LL_RCC_PLL7DOWNSPREAD_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7DOWNSPREAD_Disable(void)
{
  SET_BIT(RCC->PLL7CFGR3, RCC_PLL7CFGR3_DOWNSPREAD);
}

/**
  * @brief  Check if PLL7 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL7CFGR4           BYPASS        LL_RCC_PLL7_FOUTPOSTDIV_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_FOUTPOSTDIV_FREF_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL7CFGR4, RCC_PLL7CFGR4_BYPASS) == RCC_PLL7CFGR4_BYPASS) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL7
  * @rmtoll PLL7CFGR4           BYPASS         LL_RCC_PLL7_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_FOUTPOSTDIV_FREF_Enable(void)
{
  SET_BIT(RCC->PLL7CFGR4, RCC_PLL7CFGR4_BYPASS);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL7
  * @rmtoll PLL7CFGR4           BYPASS         LL_RCC_PLL7_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_FOUTPOSTDIV_FREF_Disable(void)
{
  CLEAR_BIT(RCC->PLL7CFGR4, RCC_PLL7CFGR4_BYPASS);
}

/**
  * @brief  Check if PLL7  POSTDIV1 and POSTDIV2 dividers are active
  * @rmtoll PLL7CFGR4           FOUTPOSTDIVEN        LL_RCC_PLL7_FOUTPOSTDIVEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_FOUTPOSTDIVEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL7CFGR4, RCC_PLL7CFGR4_FOUTPOSTDIVEN) == RCC_PLL7CFGR4_FOUTPOSTDIVEN) ? 1UL : 0UL);
}

/**
  * @brief   activate POSTDIV1 and POSTDIV2 on PLL7
  * @rmtoll PLL7CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL7_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_FOUTPOSTDIV_Enable(void)
{
  SET_BIT(RCC->PLL7CFGR4, RCC_PLL7CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  disactivate POSTDIV1 and POSTDIV2 on PLL7
  * @rmtoll PLL7CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL7_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_FOUTPOSTDIV_Disable(void)
{
  CLEAR_BIT(RCC->PLL7CFGR4, RCC_PLL7CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  Check if PLL7 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL7CFGR4           DSMEN        LL_RCC_PLL7_DSMEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_DSMEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL7CFGR4, RCC_PLL7CFGR4_DSMEN) == RCC_PLL7CFGR4_DSMEN) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL7
  * @rmtoll PLL7CFGR4           DSMEN         LL_RCC_PLL7_DSMEN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_DSMEN_Enable(void)
{
  SET_BIT(RCC->PLL7CFGR4, RCC_PLL7CFGR4_DSMEN);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL7
  * @rmtoll PLL7CFGR4           DSMEN         LL_RCC_PLL7_DSMEN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_DSMEN_Disable(void)
{
  CLEAR_BIT(RCC->PLL7CFGR4, RCC_PLL7CFGR4_DSMEN);
}

/** @brief  Configure the PLL7 Clock Spreading Generator
  * @rmtoll PLL7CSGR    DIVVAL, SPREAD  LL_RCC_PLL7_ConfigCSG
  *
  * @param  ModFreq:  Modulation frequency adjustment for PLL7
  *         This parameter must have a value between 0 and 15
  *
  * @param  IncStep: Modulation Depth Adjustment for PLL7
  *         This parameter must have a value between 0 and 31
  * @note   ModFreq x IncStep shall not exceed (2^4)-1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL7_ConfigCSG(uint32_t ModFreq, uint32_t IncStep)
{
  MODIFY_REG(RCC->PLL7CFGR5, (RCC_PLL7CFGR5_DIVVAL | RCC_PLL7CFGR5_SPREAD), \
             (ModFreq | (IncStep << RCC_PLL7CFGR5_SPREAD_Pos)));
}

/**
  * @brief  Get  PLL7 VCO frequency divide level 1
  * @rmtoll PLL7CFGR6      POSTDIV1          LL_RCC_PLL7_ConfigFREQDIV_L1
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL7_ConfigFREQDIV_L1(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL7CFGR6, RCC_PLL7CFGR6_POSTDIV1, POSTDIV << RCC_PLL7CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get Fractional part of the PLL7 VCO multiplication factor
  * @rmtoll PLL7CFGR6      POSTDIV1          LL_RCC_PLL7_GetFREQDIV_L1
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_GetFREQDIV_L1(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL7CFGR6, RCC_PLL7CFGR6_POSTDIV1) >>  RCC_PLL7CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get PLL7  reference input clock divide frequency ratio
  * @rmtoll PLL7CFGR7      POSTDIV2          LL_RCC_PLL7_ConfigFREQDIV_L2
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL7_ConfigFREQDIV_L2(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL7CFGR7, RCC_PLL7CFGR7_POSTDIV2, POSTDIV << RCC_PLL7CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Get Fractional part of the PLL7 VCO multiplication factor
  * @rmtoll PLL7CFGR7      POSTDIV2          LL_RCC_PLL7_GetFREQDIV_L2
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL7_GetFREQDIV_L2(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL7CFGR7, RCC_PLL7CFGR7_POSTDIV2) >>  RCC_PLL7CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Set the oscillator used as PLL8 clock source.
  * @note   PLLSRC can be written only when all PLL8 is disabled.
  * @rmtoll MUXSELCFGR      MUXSEL4        LL_RCC_PLL8_SetSource
  * @param  PLLSource parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL8SOURCE_HSI
  *         @arg @ref LL_RCC_PLL8SOURCE_HSE
  *         @arg @ref LL_RCC_PLL8SOURCE_MSI
  *         @arg @ref LL_RCC_PLL8SOURCE_NONE
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_SetSource(uint32_t PLLSource)
{
  MODIFY_REG(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL4, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL8 clock source.
  * @rmtoll MUXSELCFGR      MUXSEL4        LL_RCC_PLL8_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL8SOURCE_HSI
  *         @arg @ref LL_RCC_PLL8SOURCE_HSE
  *         @arg @ref LL_RCC_PLL8SOURCE_MSI
  *         @arg @ref LL_RCC_PLL8SOURCE_NONE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->MUXSELCFGR, RCC_MUXSELCFGR_MUXSEL4));
}

/**
  * @brief  Enable PLL8
  * @rmtoll PLL8CFGR1           PLLEN         LL_RCC_PLL8_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_Enable(void)
{
  SET_BIT(RCC->PLL8CFGR1, RCC_PLL8CFGR1_PLLEN);
}

/**
  * @brief  Disable PLL8
  * @note Cannot be disabled if the PLL clock is used as a system clock.
  *       This API shall be called only when PLL8 DIVPEN, DIVQEN and DIVREN are
  *       disabled.
  * @rmtoll PLL8CFGR1           PLLEN         LL_RCC_PLL8_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_Disable(void)
{
  CLEAR_BIT(RCC->PLL8CFGR1, RCC_PLL8CFGR1_PLLEN);
}

/**
  * @brief  assert PLL8 Spread Spectrum Modulator reset
  * @rmtoll PLL8CFGR1           SSMODRST         LL_RCC_PLL8_SSMODRST_Assert
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_SSMODRST_Assert(void)
{
  SET_BIT(RCC->PLL8CFGR1, RCC_PLL8CFGR1_SSMODRST);
}

/**
  * @brief  release PLL8 Spread Spectrum Modulator reset
  * @rmtoll PLL8CFGR1           SSMODRST         LL_RCC_PLL8_SSMODRST_Release
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_SSMODRST_Release(void)
{
  CLEAR_BIT(RCC->PLL8CFGR1, RCC_PLL8CFGR1_SSMODRST);
}

/**
  * @brief  Check if PLL8 Spread Spectrum Modulator reset is asserted
  * @rmtoll PLL8CFGR1           SSMODRST        LL_RCC_PLL8_SSMODRST_IsAssert
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_SSMODRST_IsAssert(void)
{
  return ((READ_BIT(RCC->PLL8CFGR1, RCC_PLL8CFGR1_SSMODRST) == RCC_PLL8CFGR1_SSMODRST) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL8 Ready
  * @rmtoll PLL8CFGR1           PLL8RDY        LL_RCC_PLL8_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_IsReady(void)
{
  return ((READ_BIT(RCC->PLL8CFGR1, RCC_PLL8CFGR1_PLLRDY) == RCC_PLL8CFGR1_PLLRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set Fractional part of the PLL8 VCO multiplication factor
  * @rmtoll PLL8CFGR1      CKREFST          LL_RCC_PLL8_SetCKREFST
  * @param  CKREFST parameter can be a value between 0 and 1 (0x1)
  * 0: Reading 0 means that the PLL{x} reference clock is not running, writing 0 resets the
  * reference clock running detector.
  * 1: Reading 1 means that the PLL{x} reference clock is running, writing 1 resets the
  * reference clock running detector.
  */
__STATIC_INLINE void LL_RCC_PLL8_SetCKREFST(uint32_t CKREFST)
{
  MODIFY_REG(RCC->PLL8CFGR1, RCC_PLL8CFGR1_CKREFST, CKREFST << RCC_PLL8CFGR1_CKREFST_Pos);
}

/**
  * @brief  Check if PLL8 reference clock is running
  * @rmtoll PLL8CFGR1           CKREFST        LL_RCC_PLL8_CKREFST_IsRunning
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_CKREFST_IsRunning(void)
{
  return ((READ_BIT(RCC->PLL8CFGR1, RCC_PLL8CFGR1_CKREFST) == RCC_PLL8CFGR1_CKREFST) ? 1UL : 0UL);
}

/**
  * @brief  Set PLL8 VCO multiplication factor
  * @rmtoll PLL8CFGR2      FBDIV          LL_RCC_PLL8_SetFBDIV
  * @param  FBDIV parameter can be a value between 0 and 4095 (0xFFF)
  */
__STATIC_INLINE void LL_RCC_PLL8_SetFBDIV(uint32_t FBDIV)
{
  MODIFY_REG(RCC->PLL8CFGR2, RCC_PLL8CFGR2_FBDIV, FBDIV << RCC_PLL8CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL8 VCO multiplication factor
  * @rmtoll PLL8CFGR2      FBDIV          LL_RCC_PLL8_GetFBDIV
  * @retval A value between 0 and 4095 (0x0FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_GetFBDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL8CFGR2, RCC_PLL8CFGR2_FBDIV) >>  RCC_PLL8CFGR2_FBDIV_Pos);
}

/**
  * @brief  Get PLL8  reference input clock divide frequency ratio
  * @rmtoll PLL8CFGR2      FREFDIV          LL_RCC_PLL8_SetFREFDIV
  * @param  FREFDIV parameter can be a value between 0 and 63 (0x3F)
  */
__STATIC_INLINE void LL_RCC_PLL8_SetFREFDIV(uint32_t FREFDIV)
{
  MODIFY_REG(RCC->PLL8CFGR2, RCC_PLL8CFGR2_FREFDIV, FREFDIV << RCC_PLL8CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Get PLL8  reference input clock divide frequency ratio
  * @rmtoll PLL8CFGR2      FREFDIV          LL_RCC_PLL8_GetFREFDIV
  * @retval A value between 0 and 63 (0x3F)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_GetFREFDIV(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL8CFGR2, RCC_PLL8CFGR2_FREFDIV) >>  RCC_PLL8CFGR2_FREFDIV_Pos);
}

/**
  * @brief  Set Fractional part of the PLL8 VCO multiplication factor
  * @rmtoll PLL8CFGR3      FRACIN          LL_RCC_PLL8_SetFRACIN
  * @param  FRACIN parameter can be a value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE void LL_RCC_PLL8_SetFRACIN(uint32_t FRACIN)
{
  MODIFY_REG(RCC->PLL8CFGR3, RCC_PLL8CFGR3_FRACIN, FRACIN << RCC_PLL8CFGR3_FRACIN_Pos);
}

/**
  * @brief  Get Fractional part of the PLL8 VCO multiplication factor
  * @rmtoll PLL8CFGR3      FRACIN          LL_RCC_PLL8_GetFRACIN
  * @retval A value between 0 and 8388607 (0x7FFFFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_GetFRACIN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL8CFGR3, RCC_PLL8CFGR3_FRACIN) >>  RCC_PLL8CFGR3_FRACIN_Pos);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL8
  * @rmtoll PLL8CFGR3           SSCGDIS         LL_RCC_PLL8_CSG_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_CSG_Enable(void)
{
  CLEAR_BIT(RCC->PLL8CFGR3, RCC_PLL8CFGR3_SSCGDIS);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL8
  * @rmtoll PLL8CFGR3           SSCGDIS         LL_RCC_PLL8_CSG_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_CSG_Disable(void)
{
  SET_BIT(RCC->PLL8CFGR3, RCC_PLL8CFGR3_SSCGDIS);
}

/**
  * @brief  Check if PLL8Spread Spectrum Modulator  is Enabled
  * @rmtoll PLL8CFGR3           SSCGDIS        LL_RCC_PLL8_CSG_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_CSG_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL8CFGR3, RCC_PLL8CFGR3_SSCGDIS) == RCC_PLL8CFGR3_SSCGDIS) ? 0UL : 1UL);
}

/**
  * @brief  Enable the Spread Spectrum Modulator of PLL8
  * @rmtoll PLL8CFGR3           DACEN         LL_RCC_PLL8DAC_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8DAC_Enable(void)
{
  CLEAR_BIT(RCC->PLL8CFGR3, RCC_PLL8CFGR3_DACEN);
}

/**
  * @brief  Disable the Spread Spectrum Modulator of PLL8
  * @rmtoll PLL8CFGR3           DACEN         LL_RCC_PLL8DAC_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8DAC_Disable(void)
{
  SET_BIT(RCC->PLL8CFGR3, RCC_PLL8CFGR3_DACEN);
}

/**
  * @brief  Check if PLL8 DAC is Enabled
  * @rmtoll PLL8CFGR3           DACEN        LL_RCC_PLL8_DAC_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_DAC_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL8CFGR3, RCC_PLL8CFGR3_DACEN) == RCC_PLL8CFGR3_DACEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable Down-spread modulation of PLL8
  * @rmtoll PLL8CFGR3           DOWNSPREAD         LL_RCC_PLL8DOWNSPREAD_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8DOWNSPREAD_Enable(void)
{
  CLEAR_BIT(RCC->PLL8CFGR3, RCC_PLL8CFGR3_DOWNSPREAD);
}

/**
  * @brief  Enable Center-spread modulation of PLL8
  * @rmtoll PLL8CFGR3           DOWNSPREAD         LL_RCC_PLL8DOWNSPREAD_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8DOWNSPREAD_Disable(void)
{
  SET_BIT(RCC->PLL8CFGR3, RCC_PLL8CFGR3_DOWNSPREAD);
}

/**
  * @brief  Check if PLL8 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL8CFGR4           BYPASS        LL_RCC_PLL8_FOUTPOSTDIV_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_FOUTPOSTDIV_FREF_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL8CFGR4, RCC_PLL8CFGR4_BYPASS) == RCC_PLL8CFGR4_BYPASS) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL8
  * @rmtoll PLL8CFGR4           BYPASS         LL_RCC_PLL8_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_FOUTPOSTDIV_FREF_Enable(void)
{
  SET_BIT(RCC->PLL8CFGR4, RCC_PLL8CFGR4_BYPASS);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL8
  * @rmtoll PLL8CFGR4           BYPASS         LL_RCC_PLL8_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_FOUTPOSTDIV_FREF_Disable(void)
{
  CLEAR_BIT(RCC->PLL8CFGR4, RCC_PLL8CFGR4_BYPASS);
}

/**
  * @brief  Check if PLL8  POSTDIV1 and POSTDIV2 dividers are active
  * @rmtoll PLL8CFGR4           FOUTPOSTDIVEN        LL_RCC_PLL8_FOUTPOSTDIVEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_FOUTPOSTDIVEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL8CFGR4, RCC_PLL8CFGR4_FOUTPOSTDIVEN) == RCC_PLL8CFGR4_FOUTPOSTDIVEN) ? 1UL : 0UL);
}

/**
  * @brief   activate POSTDIV1 and POSTDIV2 on PLL8
  * @rmtoll PLL8CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL8_FOUTPOSTDIV_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_FOUTPOSTDIV_Enable(void)
{
  SET_BIT(RCC->PLL8CFGR4, RCC_PLL8CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  disactivate POSTDIV1 and POSTDIV2 on PLL8
  * @rmtoll PLL8CFGR4           FOUTPOSTDIVEN         LL_RCC_PLL8_FOUTPOSTDIV_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_FOUTPOSTDIV_Disable(void)
{
  CLEAR_BIT(RCC->PLL8CFGR4, RCC_PLL8CFGR4_FOUTPOSTDIVEN);
}

/**
  * @brief  Check if PLL8 FOUTPOSTDIV is driven by FREF
  * @rmtoll PLL8CFGR4           DSMEN        LL_RCC_PLL8_DSMEN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_DSMEN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL8CFGR4, RCC_PLL8CFGR4_DSMEN) == RCC_PLL8CFGR4_DSMEN) ? 1UL : 0UL);
}

/**
  * @brief  FOUTPOSTDIV is driven by FREF on PLL8
  * @rmtoll PLL8CFGR4           DSMEN         LL_RCC_PLL8_DSMEN_Enable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_DSMEN_Enable(void)
{
  SET_BIT(RCC->PLL8CFGR4, RCC_PLL8CFGR4_DSMEN);
}

/**
  * @brief  FOUTPOSTDIV is driven by POSTDIV2 on PLL8
  * @rmtoll PLL8CFGR4           DSMEN         LL_RCC_PLL8_DSMEN_Disable
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_DSMEN_Disable(void)
{
  CLEAR_BIT(RCC->PLL8CFGR4, RCC_PLL8CFGR4_DSMEN);
}

/** @brief  Configure the PLL8 Clock Spreading Generator
  * @rmtoll PLL8CSGR    DIVVAL, SPREAD  LL_RCC_PLL8_ConfigCSG
  *
  * @param  ModFreq:  Modulation frequency adjustment for PLL8
  *         This parameter must have a value between 0 and 15
  *
  * @param  IncStep: Modulation Depth Adjustment for PLL8
  *         This parameter must have a value between 0 and 31
  * @note   ModFreq x IncStep shall not exceed (2^4)-1
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PLL8_ConfigCSG(uint32_t ModFreq, uint32_t IncStep)
{
  MODIFY_REG(RCC->PLL8CFGR5, (RCC_PLL8CFGR5_DIVVAL | RCC_PLL8CFGR5_SPREAD), \
             (ModFreq | (IncStep << RCC_PLL8CFGR5_SPREAD_Pos)));
}

/**
  * @brief  Get  PLL8 VCO frequency divide level 1
  * @rmtoll PLL8CFGR6      POSTDIV1          LL_RCC_PLL8_ConfigFREQDIV_L1
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL8_ConfigFREQDIV_L1(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL8CFGR6, RCC_PLL8CFGR6_POSTDIV1, POSTDIV << RCC_PLL8CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get Fractional part of the PLL8 VCO multiplication factor
  * @rmtoll PLL8CFGR6      POSTDIV1          LL_RCC_PLL8_GetFREQDIV_L1
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_GetFREQDIV_L1(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL8CFGR6, RCC_PLL8CFGR6_POSTDIV1) >>  RCC_PLL8CFGR6_POSTDIV1_Pos);
}

/**
  * @brief  Get PLL8  reference input clock divide frequency ratio
  * @rmtoll PLL8CFGR7      POSTDIV2          LL_RCC_PLL8_ConfigFREQDIV_L2
  * @param  POSTDIV parameter can be a value between 0 and 15 (0xF)
  */
__STATIC_INLINE void LL_RCC_PLL8_ConfigFREQDIV_L2(uint32_t POSTDIV)
{
  MODIFY_REG(RCC->PLL8CFGR7, RCC_PLL8CFGR7_POSTDIV2, POSTDIV << RCC_PLL8CFGR7_POSTDIV2_Pos);
}

/**
  * @brief  Get Fractional part of the PLL8 VCO multiplication factor
  * @rmtoll PLL8CFGR7      POSTDIV2          LL_RCC_PLL8_GetFREQDIV_L2
  * @retval A value between 0 and 15 (0xF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL8_GetFREQDIV_L2(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL8CFGR7, RCC_PLL8CFGR7_POSTDIV2) >>  RCC_PLL8CFGR7_POSTDIV2_Pos);
}


#if defined(CORE_CA35)
__STATIC_INLINE void LL_CA35SS_SetCA35SSClockSourceExt(void)
{
  /* Set A35 source clock to external ck_cpu1_ext2f */
  CA35SSC->CHGCLKREQ_WS1 = CA35SSC_CHGCLKREQ_WS1_ARM_CHGCLKREQ;
}

__STATIC_INLINE void LL_CA35SS_SetCA35SSClockSourcePLL1(void)
{
  /* Set A35 source clock to internal PLL */
  CA35SSC->CHGCLKREQ_WC1 = CA35SSC_CHGCLKREQ_WC1_ARM_CHGCLKREQ;
}

/**
  * @brief  Enable PLL1
  * @rmtoll
  * @retval None
  */
__STATIC_INLINE void LL_CA35SS_PLL1_Enable(void)
{
  CA35SSC->PLL_ENABLE_WS1 = CA35SSC_PLL_ENABLE_WS1_PLL_EN;
}

/**
  * @brief  Disable PLL1
  * @rmtoll
  * @retval None
  */
__STATIC_INLINE void LL_CA35SS_PLL1_Disable(void)
{
  CA35SSC->PLL_ENABLE_WC1 = CA35SSC_PLL_ENABLE_WC1_PLL_EN;
}

/**
  * @brief  Reset PLL1 output path
  * @rmtoll
  * @retval None
  */
__STATIC_INLINE void LL_CA35SS_PLL1_Reset_output(void)
{
  CA35SSC->PLL_ENABLE_WC1 = CA35SSC_PLL_ENABLE_WC1_NRESET_SWPLL;
}

/**
  * @brief  Set PLL1 output path
  * @rmtoll
  * @retval None
  */
__STATIC_INLINE void LL_CA35SS_PLL1_Set_output(void)
{
  CA35SSC->PLL_ENABLE_WS1 = CA35SSC_PLL_ENABLE_WS1_NRESET_SWPLL;
}

/**
  * @brief  Check if PLL1 Ready
  * @rmtoll
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CA35SS_PLL1_IsReady(void)
{
  return ((CA35SSC->PLL_ENABLE_RW & CA35SSC_PLL_ENABLE_RW_LOCKP) != CA35SSC_PLL_ENABLE_RW_LOCKP);
}

/**
  * @brief  Set PLL1 VCO multiplication factor
  * @rmtoll
  * @param
  */
__STATIC_INLINE void LL_CA35SS_PLL1_SetFBDIV(uint32_t FBDIV)
{
  MODIFY_REG(CA35SSC->PLL_FREQ1_RW, CA35SSC_PLL_FREQ1_RW_FBDIV, FBDIV << CA35SSC_PLL_FREQ1_RW_FBDIV_Pos);
}

/**
  * @brief  Set PLL1 reference input clock divide frequency ratio
  * @rmtoll
  * @param
  */
__STATIC_INLINE void LL_CA35SS_PLL1_SetFREFDIV(uint32_t REFDIV)
{
  MODIFY_REG(CA35SSC->PLL_FREQ1_RW, CA35SSC_PLL_FREQ1_RW_REFDIV, REFDIV << CA35SSC_PLL_FREQ1_RW_REFDIV_Pos);
}

/**
  * @brief  Set PLL1 post divider 1
  * @rmtoll
  * @param
  */
__STATIC_INLINE void LL_CA35SS_PLL1_SetPostDiv1(uint32_t POSTDIV1)
{
  MODIFY_REG(CA35SSC->PLL_FREQ2_RW, CA35SSC_PLL_FREQ2_RW_POSTDIV1, POSTDIV1 << CA35SSC_PLL_FREQ2_RW_POSTDIV1_Pos);
}

/**
  * @brief  Set PLL1 post divider 2
  * @rmtoll
  * @param
  */
__STATIC_INLINE void LL_CA35SS_PLL1_SetPostDiv2(uint32_t POSTDIV2)
{
  MODIFY_REG(CA35SSC->PLL_FREQ2_RW, CA35SSC_PLL_FREQ2_RW_POSTDIV2, POSTDIV2 << CA35SSC_PLL_FREQ2_RW_POSTDIV2_Pos);
}
#endif /* CORE_CA35 */

/**
  * @}
  */

/** @defgroup RCC_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Clear LSI ready interrupt flag
  * @rmtoll C2CIFCLRR      LSIRDYF      LL_RCC_ClearFlag_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSIRDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_LSIRDYF);
}

/**
  * @brief  Clear LSE ready interrupt flag
  * @rmtoll C2CIFCLRR      LSERDYF       LL_RCC_ClearFlag_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSERDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_LSERDYF);
}

/**
  * @brief  Clear HSI ready interrupt flag
  * @rmtoll C2CIFCLRR      HSIRDYF       LL_RCC_ClearFlag_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIRDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_HSIRDYF);
}

/**
  * @brief  Clear HSE ready interrupt flag
  * @rmtoll CICR         HSERDYF       LL_RCC_ClearFlag_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSERDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_HSERDYF);
}

/**
  * @brief  Clear MSI ready interrupt flag
  * @rmtoll C2CIFCLRR      MSIRDYF       LL_RCC_ClearFlag_MSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSIRDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_MSIRDYF);
}

/**
  * @brief  Clear PLL1 ready interrupt flag
  * @rmtoll C2CIFCLRR      PLL1DYF       LL_RCC_ClearFlag_PLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL1RDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL1RDYF);
}

/**
  * @brief  Clear PLL2 ready interrupt flag
  * @rmtoll C2CIFCLRR      PLL2DYF       LL_RCC_ClearFlag_PLL2RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL2RDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL2RDYF);
}

#if defined(RCC_C2CIFCLRR_PLL3RDYF)
/**
  * @brief  Clear PLL3 ready interrupt flag
  * @rmtoll C2CIFCLRR      PLL3DYF       LL_RCC_ClearFlag_PLL3RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL3RDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL3RDYF);
}
#endif /* RCC_C2CIFCLRR_PLL3RDYF */

/**
  * @brief  Clear PLL4 ready interrupt flag
  * @rmtoll C2CIFCLRR      PLL4DYF       LL_RCC_ClearFlag_PLL4RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL4RDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL4RDYF);
}

/**
  * @brief  Clear PLL4 ready interrupt flag
  * @rmtoll C2CIFCLRR      PLL5DYF       LL_RCC_ClearFlag_PLL5RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL5RDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL5RDYF);
}

/**
  * @brief  Clear PLL6 ready interrupt flag
  * @rmtoll C2CIFCLRR      PLL6DYF       LL_RCC_ClearFlag_PLL6RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL6RDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL6RDYF);
}

/**
  * @brief  Clear PLL7 ready interrupt flag
  * @rmtoll C2CIFCLRR      PLL7DYF       LL_RCC_ClearFlag_PLL7RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL7RDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL7RDYF);
}

/**
  * @brief  Clear PLL8 ready interrupt flag
  * @rmtoll C2CIFCLRR      PLL8DYF       LL_RCC_ClearFlag_PLL8RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL8RDY(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL8RDYF);
}

/**
  * @brief  Clear LSE Clock security system interrupt flag
  * @rmtoll C2CIFCLRR      LSECSSF       LL_RCC_ClearFlag_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSECSS(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_LSECSSF);
}

/**
  * @brief  Clear WKUP Wake up from CStop interrupt flag
  * @rmtoll C2CIFCLRR      WKUPF       LL_RCC_ClearFlag_WKUP
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearFlag_WKUP(void)
{
  WRITE_REG(RCC->C2CIFCLRR, RCC_C2CIFCLRR_WKUPF);
}

/**
  * @brief  Check if LSI ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      LSIRDYF       LL_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSIRDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_LSIRDYF) == (RCC_C2CIFCLRR_LSIRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      LSERDYF       LL_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSERDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_LSERDYF) == (RCC_C2CIFCLRR_LSERDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      HSIRDYF       LL_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIRDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_HSIRDYF) == (RCC_C2CIFCLRR_HSIRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      HSERDYF       LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_HSERDYF) == (RCC_C2CIFCLRR_HSERDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSI ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      MSIRDYF       LL_RCC_IsActiveFlag_MSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSIRDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_MSIRDYF) == (RCC_C2CIFCLRR_MSIRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL1 ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      PLL1DYF       LL_RCC_IsActiveFlag_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL1RDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL1RDYF) == (RCC_C2CIFCLRR_PLL1RDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      PLL2DYF       LL_RCC_IsActiveFlag_PLL2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL2RDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL2RDYF) == (RCC_C2CIFCLRR_PLL2RDYF)) ? 1UL : 0UL);
}

#if defined(RCC_C2CIFCLRR_PLL3RDYF)
/**
  * @brief  Check if PLL3 ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      PLL3DYF       LL_RCC_IsActiveFlag_PLL3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL3RDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL3RDYF) == (RCC_C2CIFCLRR_PLL3RDYF)) ? 1UL : 0UL);
}
#endif /* RCC_C2CIFCLRR_PLL3RDYF */

/**
  * @brief  Check if PLL4 ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      PLL4DYF       LL_RCC_IsActiveFlag_PLL4RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL4RDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL4RDYF) == (RCC_C2CIFCLRR_PLL4RDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL5 ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      PLL5DYF       LL_RCC_IsActiveFlag_PLL5RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL5RDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL5RDYF) == (RCC_C2CIFCLRR_PLL5RDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL6 ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      PLL6DYF       LL_RCC_IsActiveFlag_PLL6RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL6RDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL6RDYF) == (RCC_C2CIFCLRR_PLL6RDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL7 ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      PLL7DYF       LL_RCC_IsActiveFlag_PLL7RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL7RDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL7RDYF) == (RCC_C2CIFCLRR_PLL7RDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL8 ready interrupt occurred or not
  * @rmtoll C2CIFCLRR      PLL8DYF       LL_RCC_IsActiveFlag_PLL8RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL8RDY(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_PLL8RDYF) == (RCC_C2CIFCLRR_PLL8RDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE Clock security system interrupt occurred or not
  * @rmtoll C2CIFCLRR      LSECSSF       LL_RCC_IsActiveFlag_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSECSS(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_LSECSSF) == (RCC_C2CIFCLRR_LSECSSF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Wake up from CStop interrupt occurred or not
  * @rmtoll C2CIFCLRR      WKUPF       LL_RCC_IsActiveFlag_WKUP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WKUP(void)
{
  return ((READ_BIT(RCC->C2CIFCLRR, RCC_C2CIFCLRR_WKUPF) == (RCC_C2CIFCLRR_WKUPF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Window Watchdog 1 reset is set or not.
  * @rmtoll HWRSTSCLRR          IWDG3SYSRSTF      LL_RCC_IsActiveFlag_IWDG3SYSRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDG3SYSRST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_HWRSTSCLRR_IWDG3SYSRSTF) == (RCC_HWRSTSCLRR_IWDG3SYSRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Independent Watchdog 2 reset is set or not.
  * @rmtoll HWRSTSCLRR   IWDG2SYSRSTF      LL_RCC_IsActiveFlag_IWDG2RST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDG2RST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_HWRSTSCLRR_IWDG2SYSRSTF) == (RCC_HWRSTSCLRR_IWDG2SYSRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Independent Watchdog 1 reset is set or not.
  * @rmtoll HWRSTSCLRR   WDG1SYSRSTF      LL_RCC_IsActiveFlag_IWDG1RST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDG1RST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_HWRSTSCLRR_IWDG1SYSRSTF) == (RCC_HWRSTSCLRR_IWDG1SYSRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag MCU System reset is set or not.
  * @rmtoll HWRSTSCLRR   SYSC2RSTF      LL_RCC_IsActiveFlag_MCSYSRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SYSC2RST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_HWRSTSCLRR_SYSC2RSTF) == (RCC_HWRSTSCLRR_SYSC2RSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag MPU System reset is set or not.
  * @rmtoll HWRSTSCLRR   SYSC1RSTF      LL_RCC_IsActiveFlag_MPSYSRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SYSC1RST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_HWRSTSCLRR_SYSC1RSTF) == (RCC_HWRSTSCLRR_SYSC1RSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag MCU reset is set or not.
  * @rmtoll HWRSTSCLRR   VCPURSTF      LL_RCC_IsActiveFlag_MCURST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MCURST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_C1HWRSTSCLRR_VCPURSTF) == (RCC_C1HWRSTSCLRR_VCPURSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag VDDCORE reset is set or not.
  * @rmtoll HWRSTSCLRR   VCORERSTF      LL_RCC_IsActiveFlag_VCORERST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_VCORERST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_HWRSTSCLRR_VCORERSTF) == (RCC_HWRSTSCLRR_VCORERSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag HSE CSS reset is set or not.
  * @rmtoll HWRSTSCLRR   HCSSRSTF      LL_RCC_IsActiveFlag_HCSSRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HCSSRST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_HWRSTSCLRR_HCSSRSTF) == (RCC_HWRSTSCLRR_HCSSRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag NRST (PAD) reset is set or not.
  * @rmtoll HWRSTSCLRR   PADRSTF      LL_RCC_IsActiveFlag_PADRSTF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PADRST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_HWRSTSCLRR_PADRSTF) == (RCC_HWRSTSCLRR_PADRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag BOR reset is set or not.
  * @rmtoll HWRSTSCLRR   BORRSTF      LL_RCC_IsActiveFlag_BORRSTF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_BORRST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_HWRSTSCLRR_BORRSTF) == (RCC_HWRSTSCLRR_BORRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag POR/PDR reset is set or not.
  * @rmtoll HWRSTSCLRR   PORRSTF      LL_RCC_IsActiveFlag_PORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PORRST(void)
{
  return ((READ_BIT(RCC->HWRSTSCLRR, RCC_HWRSTSCLRR_PORRSTF) == (RCC_HWRSTSCLRR_PORRSTF)) ? 1UL : 0UL);
}

/**
  * @brief  Set HWRSTSCLRR bits to clear the reset flags.
  * @rmtoll HWRSTSCLRR      LL_RCC_HWRSTSCLRR_ALL       LL_RCC_ClearResetFlags
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ClearResetFlags(void)
{
  WRITE_REG(RCC->HWRSTSCLRR, LL_RCC_HWRSTSCLRR_ALL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll C2CIESETR      LSIRDYIE      LL_RCC_EnableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSIRDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_LSIRDYIE);
}

/**
  * @brief  Enable LSE ready interrupt
  * @rmtoll C2CIESETR      LSERDYIE      LL_RCC_EnableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSERDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_LSERDYIE);
}

/**
  * @brief  Enable HSI ready interrupt
  * @rmtoll C2CIESETR      HSIRDYIE      LL_RCC_EnableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSIRDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_HSIRDYIE);
}

/**
  * @brief  Enable HSE ready interrupt
  * @rmtoll C2CIESETR      HSERDYIE      LL_RCC_EnableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSERDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_HSERDYIE);
}

/**
  * @brief  Enable MSI ready interrupt
  * @rmtoll C2CIESETR      MSIRDYIE      LL_RCC_EnableIT_MSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSIRDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_MSIRDYIE);
}

/**
  * @brief  Enable PLL1 ready interrupt
  * @rmtoll C2CIESETR      PLLR1DYIE      LL_RCC_EnableIT_PLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL1RDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL1RDYIE);
}

/**
  * @brief  Enable PLL2 ready interrupt
  * @rmtoll C2CIESETR      PLLR2DYIE      LL_RCC_EnableIT_PLL2RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL2RDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL2RDYIE);
}

#if defined(RCC_C2CIESETR_PLL3RDYIE)
/**
  * @brief  Enable PLL3 ready interrupt
  * @rmtoll C2CIESETR      PLLR3DYIE      LL_RCC_EnableIT_PLL3RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL3RDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL3RDYIE);
}
#endif /* RCC_C2CIESETR_PLL3RDYIE */

/**
  * @brief  Enable PLL4 ready interrupt
  * @rmtoll C2CIESETR      PLLR3DYIE      LL_RCC_EnableIT_PLL4RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL4RDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL4RDYIE);
}

/**
  * @brief  Enable PLL5 ready interrupt
  * @rmtoll C2CIESETR      PLLR5DYIE      LL_RCC_EnableIT_PLL5RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL5RDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL5RDYIE);
}

/**
  * @brief  Enable PLL6 ready interrupt
  * @rmtoll C2CIESETR      PLLR6DYIE      LL_RCC_EnableIT_PLL6RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL6RDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL6RDYIE);
}

/**
  * @brief  Enable PLL7 ready interrupt
  * @rmtoll C2CIESETR      PLLR7DYIE      LL_RCC_EnableIT_PLL7RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL7RDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL7RDYIE);
}

/**
  * @brief  Enable PLL8 ready interrupt
  * @rmtoll C2CIESETR      PLLR8DYIE      LL_RCC_EnableIT_PLL8RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL8RDY(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL8RDYIE);
}

/**
  * @brief  Enable LSE clock security system interrupt
  * @rmtoll C2CIESETR      LSECSSIE      LL_RCC_EnableIT_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSECSS(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_LSECSSIE);
}

/**
  * @brief  Enable Wake up from CStop interrupt
  * @rmtoll C2CIESETR      WKUPIE      LL_RCC_EnableIT_WKUP
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableIT_WKUP(void)
{
  SET_BIT(RCC->C2CIESETR, RCC_C2CIESETR_WKUPIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll C2CIESETR      LSIRDYIE      LL_RCC_DisableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSIRDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_LSIRDYIE);
}

/**
  * @brief  Disable LSE ready interrupt
  * @rmtoll C2CIESETR      LSERDYIE      LL_RCC_DisableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSERDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_LSERDYIE);
}

/**
  * @brief  Disable HSI ready interrupt
  * @rmtoll C2CIESETR      HSIRDYIE      LL_RCC_DisableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIRDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_HSIRDYIE);
}

/**
  * @brief  Disable HSE ready interrupt
  * @rmtoll C2CIESETR      HSERDYIE      LL_RCC_DisableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSERDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_HSERDYIE);
}

/**
  * @brief  Disable MSI ready interrupt
  * @rmtoll C2CIESETR      MSIRDYIE      LL_RCC_DisableIT_MSIRDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSIRDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_MSIRDYIE);
}

/**
  * @brief  Disable PLL1 ready interrupt
  * @rmtoll C2CIESETR      PLLR1DYIE      LL_RCC_DisableIT_PLL1RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL1RDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL1RDYIE);
}

/**
  * @brief  Disable PLL2 ready interrupt
  * @rmtoll C2CIESETR      PLLR2DYIE      LL_RCC_DisableIT_PLL2RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL2RDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL2RDYIE);
}

#if defined(RCC_C2CIESETR_PLL3RDYIE)
/**
  * @brief  Disable PLL3 ready interrupt
  * @rmtoll C2CIESETR      PLLR3DYIE      LL_RCC_DisableIT_PLL3RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL3RDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL3RDYIE);
}
#endif /* RCC_C2CIESETR_PLL3RDYIE */

/**
  * @brief  Disable PLL4 ready interrupt
  * @rmtoll C2CIESETR      PLLR4DYIE      LL_RCC_DisableIT_PLL4RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL4RDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL4RDYIE);
}

/**
  * @brief  Disable PLL5 ready interrupt
  * @rmtoll C2CIESETR      PLLR5DYIE      LL_RCC_DisableIT_PLL5RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL5RDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL5RDYIE);
}

/**
  * @brief  Disable PLL6 ready interrupt
  * @rmtoll C2CIESETR      PLLR6DYIE      LL_RCC_DisableIT_PLL6RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL6RDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL6RDYIE);
}

/**
  * @brief  Disable PLL7 ready interrupt
  * @rmtoll C2CIESETR      PLLR7DYIE      LL_RCC_DisableIT_PLL7RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL7RDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL7RDYIE);
}

/**
  * @brief  Disable PLL8 ready interrupt
  * @rmtoll C2CIESETR      PLLR8DYIE      LL_RCC_DisableIT_PLL8RDY
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL8RDY(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL8RDYIE);
}

/**
  * @brief  Disable LSE clock security system interrupt
  * @rmtoll C2CIESETR      LSECSSIE      LL_RCC_DisableIT_LSECSS
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSECSS(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_LSECSSIE);
}

/**
  * @brief  Disable Wake up from CStop interrupt
  * @rmtoll C2CIESETR      WKUPIE      LL_RCC_DisableIT_WKUP
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableIT_WKUP(void)
{
  CLEAR_BIT(RCC->C2CIESETR, RCC_C2CIESETR_WKUPIE);
}

/**
  * @brief  Checks if LSI ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      LSIRDYIE      LL_RCC_IsEnabledIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSIRDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_LSIRDYIE) == (RCC_C2CIESETR_LSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if LSE ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      LSERDYIE      LL_RCC_IsEnabledIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSERDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_LSERDYIE) == (RCC_C2CIESETR_LSERDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSI ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      HSIRDYIE      LL_RCC_IsEnabledIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIRDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_HSIRDYIE) == (RCC_C2CIESETR_HSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if HSE ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      HSERDYIE      LL_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSERDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_HSERDYIE) == (RCC_C2CIESETR_HSERDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if MSI ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      MSIRDYIE      LL_RCC_IsEnabledIT_MSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSIRDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_MSIRDYIE) == (RCC_C2CIESETR_MSIRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL1 ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      PLL1DYIE      LL_RCC_IsEnabledIT_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL1RDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL1RDYIE) == (RCC_C2CIESETR_PLL1RDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL2 ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      PLL2DYIE      LL_RCC_IsEnabledIT_PLL2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL2RDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL2RDYIE) == (RCC_C2CIESETR_PLL2RDYIE)) ? 1UL : 0UL);
}

#if defined(RCC_C2CIESETR_PLL3RDYIE)
/**
  * @brief  Checks if PLL3 ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      PLL3DYIE      LL_RCC_IsEnabledIT_PLL3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL3RDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL3RDYIE) == (RCC_C2CIESETR_PLL3RDYIE)) ? 1UL : 0UL);
}
#endif /* RCC_C2CIESETR_PLL3RDYIE */

/**
  * @brief  Checks if PLL4 ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      PLL4DYIE      LL_RCC_IsEnabledIT_PLL4RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL4RDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL4RDYIE) == (RCC_C2CIESETR_PLL4RDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL5 ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      PLL5DYIE      LL_RCC_IsEnabledIT_PLL5RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL5RDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL5RDYIE) == (RCC_C2CIESETR_PLL5RDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL6 ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      PLL6DYIE      LL_RCC_IsEnabledIT_PLL6RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL6RDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL6RDYIE) == (RCC_C2CIESETR_PLL6RDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL7 ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      PLL7DYIE      LL_RCC_IsEnabledIT_PLL7RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL7RDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL7RDYIE) == (RCC_C2CIESETR_PLL7RDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if PLL8 ready interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      PLL8DYIE      LL_RCC_IsEnabledIT_PLL8RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL8RDY(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_PLL8RDYIE) == (RCC_C2CIESETR_PLL8RDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if LSECSS interrupt source is enabled or disabled.
  * @rmtoll C2CIESETR      LSECSSIE      LL_RCC_IsEnabledIT_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSECSS(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_LSECSSIE) == (RCC_C2CIESETR_LSECSSIE)) ? 1UL : 0UL);
}

/**
  * @brief  Checks if Wake up from CStop source is enabled or disabled.
  * @rmtoll C2CIESETR      WKUPIE      LL_RCC_IsEnabledIT_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_WKUP(void)
{
  return ((READ_BIT(RCC->C2CIESETR, RCC_C2CIESETR_WKUPIE) == (RCC_C2CIESETR_WKUPIE)) ? 1UL : 0UL);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup RCC_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_RCC_DeInit(void);
/**
  * @}
  */

/** @defgroup RCC_LL_EF_Get_Freq Get system and peripherals clocks frequency functions
  * @{
  */
void        LL_RCC_GetPLL2ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks);
#if defined(RCC_PLL3CFGR1_PLLEN)
void        LL_RCC_GetPLL3ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks);
#endif /* RCC_PLL3CFGR1_PLLEN */
void        LL_RCC_GetPLL4ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks);
void        LL_RCC_GetPLL5ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks);
void        LL_RCC_GetPLL6ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks);
void        LL_RCC_GetPLL7ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks);
void        LL_RCC_GetPLL8ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks);
void        LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks);

uint32_t    LL_RCC_GetI2CClockFreq(uint32_t I2CxSource);
uint32_t    LL_RCC_GetSAIClockFreq(uint32_t SAIxSource);
uint32_t    LL_RCC_GetSPIClockFreq(uint32_t SPIxSource);
uint32_t    LL_RCC_GetUARTClockFreq(uint32_t UARTxSource);
uint32_t    LL_RCC_GetSDMMCClockFreq(uint32_t SDMMCxSource);
uint32_t    LL_RCC_GetETHClockFreq(uint32_t ETHxSource);
uint32_t    LL_RCC_GetOSPIClockFreq(uint32_t OSPIxSource);
uint32_t    LL_RCC_GetFMCClockFreq(uint32_t FMCxSource);
#if defined(FDCAN1)
uint32_t    LL_RCC_GetFDCANClockFreq(uint32_t FDCANxSource);
#endif /*FDCAN1*/
uint32_t    LL_RCC_GetSPDIFRXClockFreq(uint32_t SPDIFRXxSource);
uint32_t    LL_RCC_GetCECClockFreq(uint32_t CECxSource);
uint32_t    LL_RCC_GetUSBPHYClockFreq(uint32_t USBPHYxSource);
uint32_t    LL_RCC_GetUSBOClockFreq(uint32_t USBOxSource);
uint32_t    LL_RCC_GetRNGClockFreq(uint32_t RNGxSource);
uint32_t    LL_RCC_GetCKPERClockFreq(uint32_t CKPERxSource);
uint32_t    LL_RCC_GetSTGENClockFreq(uint32_t STGENxSource);
#if defined(DSI)
uint32_t    LL_RCC_GetDSIClockFreq(uint32_t DSIxSource);
#endif /*DSI*/
uint32_t    LL_RCC_GetADCClockFreq(uint32_t ADCxSource);
uint32_t    LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource);
uint32_t    LL_RCC_GetDFSDMClockFreq(uint32_t DFSDMxSource);
uint32_t    LL_RCC_GetLTDCClockFreq(void);
uint32_t    LL_RCC_GetRTCClockFreq(void);
uint32_t    LL_RCC_GetTIMGClockFreq(uint32_t TIMGxPrescaler);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */
/* End of RCC_LL_Exported_Functions */

#endif /* RCC */

/***** MP2 RIF SPECIFIC : TO BE MERGED TO DIFFERENT "defgroup" HERE ABOVE *****/
/** @defgroup RCC_RIF_LL RCC_RIF
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_LL_RIF_Exported_Constants RCC LL RIF Exported Constants
  * @{
  */

/** @defgroup RCC_LL_EC_RIF_LOCALRES RCC LL RIF Local Resource Index
  * @{
  */
#define RCC_LOCALRES_0       0UL /*!< RIF Local Resource Index   0 */
#define RCC_LOCALRES_1       1UL /*!< RIF Local Resource Index   1 */
#define RCC_LOCALRES_2       2UL /*!< RIF Local Resource Index   2 */
#define RCC_LOCALRES_3       3UL /*!< RIF Local Resource Index   3 */
#define RCC_LOCALRES_4       4UL /*!< RIF Local Resource Index   4 */
#define RCC_LOCALRES_5       5UL /*!< RIF Local Resource Index   5 */
#define RCC_LOCALRES_6       6UL /*!< RIF Local Resource Index   6 */
#define RCC_LOCALRES_7       7UL /*!< RIF Local Resource Index   7 */
#define RCC_LOCALRES_8       8UL /*!< RIF Local Resource Index   8 */
#define RCC_LOCALRES_9       9UL /*!< RIF Local Resource Index   9 */
#define RCC_LOCALRES_10     10UL /*!< RIF Local Resource Index  10 */
#define RCC_LOCALRES_11     11UL /*!< RIF Local Resource Index  11 */
#define RCC_LOCALRES_12     12UL /*!< RIF Local Resource Index  12 */
#define RCC_LOCALRES_13     13UL /*!< RIF Local Resource Index  13 */
#define RCC_LOCALRES_14     14UL /*!< RIF Local Resource Index  14 */
#define RCC_LOCALRES_15     15UL /*!< RIF Local Resource Index  15 */
#define RCC_LOCALRES_16     16UL /*!< RIF Local Resource Index  16 */
#define RCC_LOCALRES_17     17UL /*!< RIF Local Resource Index  17 */
#define RCC_LOCALRES_18     18UL /*!< RIF Local Resource Index  18 */
#define RCC_LOCALRES_19     19UL /*!< RIF Local Resource Index  19 */
#define RCC_LOCALRES_20     20UL /*!< RIF Local Resource Index  20 */
#define RCC_LOCALRES_21     21UL /*!< RIF Local Resource Index  21 */
#define RCC_LOCALRES_22     22UL /*!< RIF Local Resource Index  22 */
#define RCC_LOCALRES_23     23UL /*!< RIF Local Resource Index  23 */
#define RCC_LOCALRES_24     24UL /*!< RIF Local Resource Index  24 */
#define RCC_LOCALRES_25     25UL /*!< RIF Local Resource Index  25 */
#define RCC_LOCALRES_26     26UL /*!< RIF Local Resource Index  26 */
#define RCC_LOCALRES_27     27UL /*!< RIF Local Resource Index  27 */
#define RCC_LOCALRES_28     28UL /*!< RIF Local Resource Index  28 */
#define RCC_LOCALRES_29     29UL /*!< RIF Local Resource Index  29 */
#define RCC_LOCALRES_30     30UL /*!< RIF Local Resource Index  30 */
#define RCC_LOCALRES_31     31UL /*!< RIF Local Resource Index  31 */
#define RCC_LOCALRES_32     32UL /*!< RIF Local Resource Index  32 */
#define RCC_LOCALRES_33     33UL /*!< RIF Local Resource Index  33 */
#define RCC_LOCALRES_34     34UL /*!< RIF Local Resource Index  34 */
#define RCC_LOCALRES_35     35UL /*!< RIF Local Resource Index  35 */
#define RCC_LOCALRES_36     36UL /*!< RIF Local Resource Index  36 */
#define RCC_LOCALRES_37     37UL /*!< RIF Local Resource Index  37 */
#define RCC_LOCALRES_38     38UL /*!< RIF Local Resource Index  38 */
#define RCC_LOCALRES_39     39UL /*!< RIF Local Resource Index  39 */
#define RCC_LOCALRES_40     40UL /*!< RIF Local Resource Index  40 */
#define RCC_LOCALRES_41     41UL /*!< RIF Local Resource Index  41 */
#define RCC_LOCALRES_42     42UL /*!< RIF Local Resource Index  42 */
#define RCC_LOCALRES_43     43UL /*!< RIF Local Resource Index  43 */
#define RCC_LOCALRES_44     44UL /*!< RIF Local Resource Index  44 */
#define RCC_LOCALRES_45     45UL /*!< RIF Local Resource Index  45 */
#define RCC_LOCALRES_46     46UL /*!< RIF Local Resource Index  46 */
#define RCC_LOCALRES_47     47UL /*!< RIF Local Resource Index  47 */
#define RCC_LOCALRES_48     48UL /*!< RIF Local Resource Index  48 */
#define RCC_LOCALRES_49     49UL /*!< RIF Local Resource Index  49 */
#define RCC_LOCALRES_50     50UL /*!< RIF Local Resource Index  50 */
#define RCC_LOCALRES_51     51UL /*!< RIF Local Resource Index  51 */
#define RCC_LOCALRES_52     52UL /*!< RIF Local Resource Index  52 */
#define RCC_LOCALRES_53     53UL /*!< RIF Local Resource Index  53 */
#define RCC_LOCALRES_54     54UL /*!< RIF Local Resource Index  54 */
#define RCC_LOCALRES_55     55UL /*!< RIF Local Resource Index  55 */
#define RCC_LOCALRES_56     56UL /*!< RIF Local Resource Index  56 */
#define RCC_LOCALRES_57     57UL /*!< RIF Local Resource Index  57 */
#define RCC_LOCALRES_58     58UL /*!< RIF Local Resource Index  58 */
#define RCC_LOCALRES_59     59UL /*!< RIF Local Resource Index  59 */
#define RCC_LOCALRES_60     60UL /*!< RIF Local Resource Index  60 */
#define RCC_LOCALRES_61     61UL /*!< RIF Local Resource Index  61 */
#define RCC_LOCALRES_62     62UL /*!< RIF Local Resource Index  62 */
#define RCC_LOCALRES_63     63UL /*!< RIF Local Resource Index  63 */
#define RCC_LOCALRES_64     64UL /*!< RIF Local Resource Index  64 */
#define RCC_LOCALRES_65     65UL /*!< RIF Local Resource Index  65 */
#define RCC_LOCALRES_66     66UL /*!< RIF Local Resource Index  66 */
#define RCC_LOCALRES_67     67UL /*!< RIF Local Resource Index  67 */
#define RCC_LOCALRES_68     68UL /*!< RIF Local Resource Index  68 */
#define RCC_LOCALRES_69     69UL /*!< RIF Local Resource Index  69 */
#define RCC_LOCALRES_70     70UL /*!< RIF Local Resource Index  70 */
#define RCC_LOCALRES_71     71UL /*!< RIF Local Resource Index  71 */
#define RCC_LOCALRES_72     72UL /*!< RIF Local Resource Index  72 */
#define RCC_LOCALRES_73     73UL /*!< RIF Local Resource Index  73 */
#define RCC_LOCALRES_74     74UL /*!< RIF Local Resource Index  74 */
#define RCC_LOCALRES_75     75UL /*!< RIF Local Resource Index  75 */
#define RCC_LOCALRES_76     76UL /*!< RIF Local Resource Index  76 */
#define RCC_LOCALRES_77     77UL /*!< RIF Local Resource Index  77 */
#define RCC_LOCALRES_78     78UL /*!< RIF Local Resource Index  78 */
#define RCC_LOCALRES_79     79UL /*!< RIF Local Resource Index  79 */
#define RCC_LOCALRES_80     80UL /*!< RIF Local Resource Index  80 */
#define RCC_LOCALRES_81     81UL /*!< RIF Local Resource Index  81 */
#define RCC_LOCALRES_82     82UL /*!< RIF Local Resource Index  82 */
#define RCC_LOCALRES_83     83UL /*!< RIF Local Resource Index  83 */
#define RCC_LOCALRES_84     84UL /*!< RIF Local Resource Index  84 */
#define RCC_LOCALRES_85     85UL /*!< RIF Local Resource Index  85 */
#define RCC_LOCALRES_86     86UL /*!< RIF Local Resource Index  86 */
#define RCC_LOCALRES_87     87UL /*!< RIF Local Resource Index  87 */
#define RCC_LOCALRES_88     88UL /*!< RIF Local Resource Index  88 */
#define RCC_LOCALRES_89     89UL /*!< RIF Local Resource Index  89 */
#define RCC_LOCALRES_90     90UL /*!< RIF Local Resource Index  90 */
#define RCC_LOCALRES_91     91UL /*!< RIF Local Resource Index  91 */
#define RCC_LOCALRES_92     92UL /*!< RIF Local Resource Index  92 */
#define RCC_LOCALRES_93     93UL /*!< RIF Local Resource Index  93 */
#define RCC_LOCALRES_94     94UL /*!< RIF Local Resource Index  94 */
#define RCC_LOCALRES_95     95UL /*!< RIF Local Resource Index  95 */
#define RCC_LOCALRES_96     96UL /*!< RIF Local Resource Index  96 */
#define RCC_LOCALRES_97     97UL /*!< RIF Local Resource Index  97 */
#define RCC_LOCALRES_98     98UL /*!< RIF Local Resource Index  98 */
#define RCC_LOCALRES_99     99UL /*!< RIF Local Resource Index  99 */
#define RCC_LOCALRES_100   100UL /*!< RIF Local Resource Index 100 */
#define RCC_LOCALRES_101   101UL /*!< RIF Local Resource Index 101 */
#define RCC_LOCALRES_102   102UL /*!< RIF Local Resource Index 102 */
#define RCC_LOCALRES_103   103UL /*!< RIF Local Resource Index 103 */
#define RCC_LOCALRES_104   104UL /*!< RIF Local Resource Index 104 */
#define RCC_LOCALRES_105   105UL /*!< RIF Local Resource Index 105 */
#define RCC_LOCALRES_106   106UL /*!< RIF Local Resource Index 106 */
#define RCC_LOCALRES_107   107UL /*!< RIF Local Resource Index 107 */
#define RCC_LOCALRES_108   108UL /*!< RIF Local Resource Index 108 */
#define RCC_LOCALRES_109   109UL /*!< RIF Local Resource Index 109 */
#define RCC_LOCALRES_110   110UL /*!< RIF Local Resource Index 110 */
#define RCC_LOCALRES_111   111UL /*!< RIF Local Resource Index 111 */
#define RCC_LOCALRES_112   112UL /*!< RIF Local Resource Index 112 */
#define RCC_LOCALRES_113   113UL /*!< RIF Local Resource Index 113 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RIF_LOCALRES_CID RCC LL RIF Compartment Identification Filtering of Local Resource Access
  * @{
  */
#define RCC_LOCALRES_CID_TYPE_NONE     0x00000000U /*!< RIF Local Resource Access : No CID filtering */
#define RCC_LOCALRES_CID_TYPE_STATIC   0x00000001U /*!< RIF Local Resource Access : Static CID filtering */
#define RCC_LOCALRES_CID_TYPE_DYNAMIC  0x00000003U /*!< RIF Local Resource Access : Dynamic CID filtering */

#define RCC_LOCALRES_CID_STATIC_0      0x00000001U /*!< RIF Local Resource Access : CID0 static filtering */
#define RCC_LOCALRES_CID_STATIC_1      0x00000011U /*!< RIF Local Resource Access : CID1 static filtering */
#define RCC_LOCALRES_CID_STATIC_2      0x00000021U /*!< RIF Local Resource Access : CID2 static filtering */
#define RCC_LOCALRES_CID_STATIC_3      0x00000031U /*!< RIF Local Resource Access : CID3 static filtering */
#define RCC_LOCALRES_CID_STATIC_4      0x00000041U /*!< RIF Local Resource Access : CID4 static filtering */
#define RCC_LOCALRES_CID_STATIC_5      0x00000051U /*!< RIF Local Resource Access : CID5 static filtering */
#define RCC_LOCALRES_CID_STATIC_6      0x00000061U /*!< RIF Local Resource Access : CID6 static filtering */
#define RCC_LOCALRES_CID_STATIC_7      0x00000071U /*!< RIF Local Resource Access : CID7 static filtering */
#define RCC_LOCALRES_CID_STATIC_MSK    RCC_LOCALRES_CID_STATIC_7

#define RCC_LOCALRES_CID_DYNAMIC_NONE  0x00000003U /*!< RIF Local Resource Access : No CID dynamic filtering */
#define RCC_LOCALRES_CID_DYNAMIC_ALL   0x00FF0003U /*!< RIF Local Resource Access : All CID dynamic filtering */
#define RCC_LOCALRES_CID_DYNAMIC_MSK   RCC_LOCALRES_CID_DYNAMIC_ALL
/* Use following values to compose CID whitelist */
#define RCC_LOCALRES_CID_DYNAMIC_0     0x00010003U /*!< RIF Local Resource Access : CID0 dynamic filtering */
#define RCC_LOCALRES_CID_DYNAMIC_1     0x00020003U /*!< RIF Local Resource Access : CID1 dynamic filtering */
#define RCC_LOCALRES_CID_DYNAMIC_2     0x00040003U /*!< RIF Local Resource Access : CID2 dynamic filtering */
#define RCC_LOCALRES_CID_DYNAMIC_3     0x00080003U /*!< RIF Local Resource Access : CID3 dynamic filtering */
#define RCC_LOCALRES_CID_DYNAMIC_4     0x00100003U /*!< RIF Local Resource Access : CID4 dynamic filtering */
#define RCC_LOCALRES_CID_DYNAMIC_5     0x00200003U /*!< RIF Local Resource Access : CID5 dynamic filtering */
#define RCC_LOCALRES_CID_DYNAMIC_6     0x00400003U /*!< RIF Local Resource Access : CID6 dynamic filtering */
#define RCC_LOCALRES_CID_DYNAMIC_7     0x00800003U /*!< RIF Local Resource Access : CID7 dynamic filtering */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RIF_LOCALRES_SEMAPHORE RCC LL RIF Semaphore Handling of Local Resource Access
  * @{
  */
#define RCC_LOCALRES_TAKEN_SEMCID0     0x00000001U /*!< RIF Local Resource Access : Semaphore taken by CID0 */
#define RCC_LOCALRES_TAKEN_SEMCID1     0x00000011U /*!< RIF Local Resource Access : Semaphore taken by CID1 */
#define RCC_LOCALRES_TAKEN_SEMCID2     0x00000021U /*!< RIF Local Resource Access : Semaphore taken by CID2 */
#define RCC_LOCALRES_TAKEN_SEMCID3     0x00000031U /*!< RIF Local Resource Access : Semaphore taken by CID3 */
#define RCC_LOCALRES_TAKEN_SEMCID4     0x00000041U /*!< RIF Local Resource Access : Semaphore taken by CID4 */
#define RCC_LOCALRES_TAKEN_SEMCID5     0x00000051U /*!< RIF Local Resource Access : Semaphore taken by CID5 */
#define RCC_LOCALRES_TAKEN_SEMCID6     0x00000061U /*!< RIF Local Resource Access : Semaphore taken by CID6 */
#define RCC_LOCALRES_TAKEN_SEMCID7     0x00000071U /*!< RIF Local Resource Access : Semaphore taken by CID7 */

#define RCC_LOCALRES_RELEASED_SEMCID0  0x00000000U /*!< RIF Local Resource Access : Semaphore released by CID0 */
#define RCC_LOCALRES_RELEASED_SEMCID1  0x00000010U /*!< RIF Local Resource Access : Semaphore released by CID1 */
#define RCC_LOCALRES_RELEASED_SEMCID2  0x00000020U /*!< RIF Local Resource Access : Semaphore released by CID2 */
#define RCC_LOCALRES_RELEASED_SEMCID3  0x00000030U /*!< RIF Local Resource Access : Semaphore released by CID3 */
#define RCC_LOCALRES_RELEASED_SEMCID4  0x00000040U /*!< RIF Local Resource Access : Semaphore released by CID4 */
#define RCC_LOCALRES_RELEASED_SEMCID5  0x00000050U /*!< RIF Local Resource Access : Semaphore released by CID5 */
#define RCC_LOCALRES_RELEASED_SEMCID6  0x00000060U /*!< RIF Local Resource Access : Semaphore released by CID6 */
#define RCC_LOCALRES_RELEASED_SEMCID7  0x00000070U /*!< RIF Local Resource Access : Semaphore released by CID7 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup RCC_LL_RIF_Exported_Functions RCC LL RIF Exported Functions
  * @{
  */

/** @defgroup RCC_LL_EF_RIF RCC LL RIF
  * @brief RCC LL RIF module driver
  * @{
  */

/* Manage RCC_SECCFGR0 - RCC_SECCFGR3 registers */
#if defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  Enable Security Filtering of RCC Local Resource Access
  * @rmtoll RCC_SECCFGRi       SECx    LL_RCC_EnableLocalResSecure
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @note   SECx bit is in register indexed i = LocalResIndex/32 at bit position j = LocalResIndex%32.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLocalResSecure(uint32_t LocalResIndex)
{
  /* Compute register index i (LocalResIndex / 32) */
  /* Compute bit position j (LocalResIndex % 32) */
  /* Set bit j in register RCC_SECCFGR[i] */
  SET_BIT(RCC->SECCFGR[LocalResIndex >> 5], 1 << (LocalResIndex & 0x1F));
}

/**
  * @brief  Disable Security Filtering of RCC Local Resource Access
  * @rmtoll RCC_SECCFGRi       SECx    LL_RCC_DisableLocalResSecure
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @note   SECx bit is in register indexed i = LocalResIndex/32, at bit position j = LocalResIndex%32.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLocalResSecure(uint32_t LocalResIndex)
{
  /* Compute register index i (LocalResIndex / 32) */
  /* Compute bit position j (LocalResIndex % 32) */
  /* Clear bit j in register RCC_SECCFGR[i] */
  CLEAR_BIT(RCC->SECCFGR[LocalResIndex >> 5], 1 << (LocalResIndex & 0x1F));
}
#endif /* CORTEX_IN_SECURE_STATE */

/**
  * @brief  Check whether Security Filtering of RCC Local Resource Access is enabled or not.
  * @rmtoll RCC_SECCFGRi       SECx    LL_RCC_IsEnabledLocalResSecure
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @note   SECx bit is in register indexed i = LocalResIndex/32, at bit position j = LocalResIndex%32.
  * @retval SECx bit value (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledLocalResSecure(uint32_t LocalResIndex)
{
  /* Compute register index i (LocalResIndex / 32) */
  /* Compute bit position j (LocalResIndex % 32) */
  /* Read bit j in register RCC_SECCFGR[i] */
  /* Return 1 when bit j is set and else 0 */
  return ((READ_BIT(RCC->SECCFGR[LocalResIndex >> 5], 1UL << (LocalResIndex & 0x1FU)) == \
           (1UL << (LocalResIndex & 0x1FU))) ? 1UL : 0UL);
}

/* Manage RCC_PRIVCFGR0 - RCC_PRIVCFGR3 registers */
/**
  * @brief  Enable Privilege Filtering of RCC Local Resource Access
  * @rmtoll RCC_PRIVCFGRi      PRIVx   LL_RCC_EnableLocalResPrivilege
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @note   PRIVx bit is in register indexed i = LocalResIndex/32 at bit position j = LocalResIndex%32.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_EnableLocalResPrivilege(uint32_t LocalResIndex)
{
  /* Compute register index i (LocalResIndex / 32) */
  /* Compute bit position j (LocalResIndex % 32) */
  /* Set bit j in register RCC_PRIVCFGR[i] */
  SET_BIT(RCC->PRIVCFGR[LocalResIndex >> 5], 1UL << (LocalResIndex & 0x1FU));
}

/**
  * @brief  Disable Privilege Filtering of RCC Local Resource Access
  * @rmtoll RCC_PRIVCFGRi      PRIVx   LL_RCC_DisableLocalResPrivilege
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @note   PRIVx bit is in register indexed i = LocalResIndex/32, at bit position j = LocalResIndex%32.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DisableLocalResPrivilege(uint32_t LocalResIndex)
{
  /* Compute register index i (LocalResIndex / 32) */
  /* Compute bit position j (LocalResIndex % 32) */
  /* Clear bit j in register RCC_PRIVCFGR[i] */
  CLEAR_BIT(RCC->PRIVCFGR[LocalResIndex >> 5], 1UL << (LocalResIndex & 0x1FU));
}

/**
  * @brief  Check whether Privilege Filtering of RCC Local Resource Access is enabled or not.
  * @rmtoll RCC_PRIVCFGRi      PRIVx   LL_RCC_IsEnabledLocalResPrivilege
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @note   PRIVx bit is in register indexed i = LocalResIndex/32, at bit position j = LocalResIndex%32.
  * @retval PRIVx bit value (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledLocalResPrivilege(uint32_t LocalResIndex)
{
  /* Compute register index i (LocalResIndex / 32) */
  /* Compute bit position j (LocalResIndex % 32) */
  /* Read bit j in register RCC_PRIVCFGR[i] */
  /* Return 1 when bit j is set and else 0 */
  return ((READ_BIT(RCC->PRIVCFGR[LocalResIndex >> 5], 1UL << (LocalResIndex & 0x1FU)) == \
           (1UL << (LocalResIndex & 0x1FU))) ? 1UL : 0UL);
}

/* Manage RCC_RCFGLOCKR0 - RCC_RCFGLOCKR3 registers */
#if defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  Lock RCC Local Resource RIF configuration
  * @rmtoll RCC_RCFGLOCKRi     RLOCKx  LL_RCC_LockLocalResConfig
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @note   RLOCKx bit is in register indexed i = LocalResIndex/32 at bit position j = LocalResIndex%32.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LockLocalResConfig(uint32_t LocalResIndex)
{
  /* Compute register index i (LocalResIndex / 32) */
  /* Compute bit position j (LocalResIndex % 32) */
  /* Set bit j in register RCC_RCFGLOCKR[i] */
  SET_BIT(RCC->RCFGLOCKR[LocalResIndex >> 5], 1 << (LocalResIndex & 0x1F));
}
#endif /* CORTEX_IN_SECURE_STATE */

/**
  * @brief  Check whether RCC Local Resource RIF configuration is locked or not.
  * @rmtoll RCC_RCFGLOCKRi     RLOCKx  LL_RCC_IsLockedLocalResConfig()
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @note   RLOCKx bit is in register indexed i = LocalResIndex/32, at bit position j = LocalResIndex%32.
  * @retval RLOCKx bit value (1 or 0)
  */
__STATIC_INLINE uint32_t LL_RCC_IsLockedLocalResConfig(uint32_t LocalResIndex)
{
  /* Compute register index i (LocalResIndex / 32) */
  /* Compute bit position j (LocalResIndex % 32) */
  /* Read bit j in register RCC_RCFGLOCKR[i] */
  /* Return 1 when bit j is set and else 0 */
  return ((READ_BIT(RCC->RCFGLOCKR[LocalResIndex >> 5], 1UL << (LocalResIndex & 0x1FU)) == \
           (1UL << (LocalResIndex & 0x1FU))) ? 1UL : 0UL);
}

/* Manage RCC_R0CIDCFGR - RCC_R113CIDCFGR registers */
#if defined(CORTEX_IN_SECURE_STATE)
/**
  * @brief  Configure static CID filtering of RCC Local Resource Access
  * @rmtoll RCC_RxCIDCFGR      SEMWLC  LL_RCC_SetLocalResSCid\n
  * @rmtoll RCC_RxCIDCFGR      SCID    LL_RCC_SetLocalResSCid\n
  * @rmtoll RCC_RxCIDCFGR      SEM_EN  LL_RCC_SetLocalResSCid\n
  * @rmtoll RCC_RxCIDCFGR      CFEN    LL_RCC_SetLocalResSCid
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @param  StaticCid Value shall be one of the following :
  *         @arg @ref RCC_LOCALRES_CID_STATIC_0
  *         @arg @ref RCC_LOCALRES_CID_STATIC_1
  *         @arg @ref RCC_LOCALRES_CID_STATIC_2
  *         @arg @ref RCC_LOCALRES_CID_STATIC_3
  *         @arg @ref RCC_LOCALRES_CID_STATIC_4
  *         @arg @ref RCC_LOCALRES_CID_STATIC_5
  *         @arg @ref RCC_LOCALRES_CID_STATIC_6
  *         @arg @ref RCC_LOCALRES_CID_STATIC_7
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLocalResSCid(uint32_t LocalResIndex, uint32_t StaticCid)
{
  /* In register RCC_RxCIDCFGR, where x is the local resource index : */
  /* - clear SEMWLC[7:0] (set to 0x00) and SEM_EN (set to 0b0) */
  /* - set SCID[2:0] according to input CID */
  /* - set CFEN to 0b1 */
  WRITE_REG(RCC->R[LocalResIndex].CIDCFGR, (StaticCid & RCC_LOCALRES_CID_STATIC_MSK));
}

/**
  * @brief  Configure dynamic CID filtering of RCC Local Resource Access
  * @rmtoll RCC_RxCIDCFGR      SEMWLC  LL_RCC_SetLocalResWLCid\n
  * @rmtoll RCC_RxCIDCFGR      SCID    LL_RCC_SetLocalResWLCid\n
  * @rmtoll RCC_RxCIDCFGR      SEM_EN  LL_RCC_SetLocalResWLCid\n
  * @rmtoll RCC_RxCIDCFGR      CFEN    LL_RCC_SetLocalResWLCid
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @param  DynamicCid Value shall be composed (through "or" operation) of the following :
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_0
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_1
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_2
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_3
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_4
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_5
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_6
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_7
  *         or equal to one of the following values :
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_NONE
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_ALL
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLocalResWLCid(uint32_t LocalResIndex, uint32_t DynamicCid)
{
  /* In register RCC_RxCIDCFGR, where x is the local resource index : */
  /* - set SEMWLC[7:0] according to input CID whitelist */
  /* - clear SCID[2:0] (set to 0b000) */
  /* - set CFEN and SEM_EN to 0b1 */
  WRITE_REG(RCC->R[LocalResIndex].CIDCFGR, (DynamicCid & RCC_LOCALRES_CID_DYNAMIC_MSK));
}

/**
  * @brief  Disable CID filtering of RCC Local Resource Access
  * @rmtoll RCC_RxCIDCFGR      SEMWLC  LL_RCC_SetLocalResNoCid\n
  * @rmtoll RCC_RxCIDCFGR      SCID    LL_RCC_SetLocalResNoCid\n
  * @rmtoll RCC_RxCIDCFGR      SEM_EN  LL_RCC_SetLocalResNoCid\n
  * @rmtoll RCC_RxCIDCFGR      CFEN    LL_RCC_SetLocalResNoCid
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetLocalResNoCid(uint32_t LocalResIndex)
{
  /* In register RCC_RxCIDCFGR, where x is the local resource index : */
  /* - clear SEMWLC[7:0] (set to 0x00) and SEM_EN (set to 0b0) */
  /* - clear SCID[2:0] (set to 0b000) and CFEN (set to 0b0) */
  WRITE_REG(RCC->R[LocalResIndex].CIDCFGR, RCC_LOCALRES_CID_TYPE_NONE);
}
#endif /* CORTEX_IN_SECURE_STATE */

/**
  * @brief  Get CID filtering configuration of RCC Local Resource Access
  * @rmtoll RCC_RxCIDCFGR      SEMWLC  LL_RCC_GetLocalResCid\n
  * @rmtoll RCC_RxCIDCFGR      SCID    LL_RCC_GetLocalResCid\n
  * @rmtoll RCC_RxCIDCFGR      SEM_EN  LL_RCC_GetLocalResCid\n
  * @rmtoll RCC_RxCIDCFGR      CFEN    LL_RCC_GetLocalResCid
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @retval Return value can be one of the following :
  *         @arg @ref RCC_LOCALRES_CID_TYPE_NONE
  *         @arg @ref RCC_LOCALRES_CID_STATIC_0
  *         @arg @ref RCC_LOCALRES_CID_STATIC_1
  *         @arg @ref RCC_LOCALRES_CID_STATIC_2
  *         @arg @ref RCC_LOCALRES_CID_STATIC_3
  *         @arg @ref RCC_LOCALRES_CID_STATIC_4
  *         @arg @ref RCC_LOCALRES_CID_STATIC_5
  *         @arg @ref RCC_LOCALRES_CID_STATIC_6
  *         @arg @ref RCC_LOCALRES_CID_STATIC_7
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_NONE
  *         or a composition (through "or" operation) of the following :
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_0
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_1
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_2
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_3
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_4
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_5
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_6
  *         @arg @ref RCC_LOCALRES_CID_DYNAMIC_7
  */
__STATIC_INLINE uint32_t LL_RCC_GetLocalResCid(uint32_t LocalResIndex)
{
  /* In register RCC_RxCIDCFGR, where x is the local resource index, */
  uint32_t rcc_rxcidcfgr = READ_REG(RCC->R[LocalResIndex].CIDCFGR);
  /* if CID filtering is Static (SEM_EN = 0 and CFEN = 1), */
  /* return static CID filtering configuration (SEMWLC=0x00, SCID, SEM_EN=0, CFEN=1) */
  /* else if CID filtering is Dynamic (SEM_EN = 1 and CFEN = 1), */
  /* return dynamic CID filtering configuration (SEMWLC, SCID=0b000, SEM_EN=1, CFEN=1) */
  /* else return RCC_LOCALRES_CID_TYPE_NONE */
#define SEM_EN_AND_CFEN_MSK (RCC_RxCIDCFGR_CFEN_Msk | RCC_RxCIDCFGR_SEM_EN_Msk)
  return ((READ_BIT(rcc_rxcidcfgr, SEM_EN_AND_CFEN_MSK) == SEM_EN_AND_CFEN_MSK) ? \
          (rcc_rxcidcfgr & RCC_LOCALRES_CID_DYNAMIC_MSK) :
          (READ_BIT(rcc_rxcidcfgr, SEM_EN_AND_CFEN_MSK) == RCC_RxCIDCFGR_CFEN) ? \
          (rcc_rxcidcfgr & RCC_LOCALRES_CID_STATIC_MSK) : RCC_LOCALRES_CID_TYPE_NONE);
}

/* Manage RCC_R0SEMCR - RCC_R113SEMCR registers */
/**
  * @brief  Take semaphore to access RCC Local Resource
  * @rmtoll RCC_RxSEMCR      SEM_MUTEX LL_RCC_TakeLocalResSem
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @note If operation is successful, SEMCID[2:0] will be updated by HW.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TakeLocalResSem(uint32_t LocalResIndex)
{
  /* In register RCC_RxSEMCR, where x is the local resource index, */
  /* set SEM_MUTEX to 0b1 (only writeable bit) */
  WRITE_REG(RCC->R[LocalResIndex].SEMCR, RCC_RxSEMCR_SEM_MUTEX);
}

/**
  * @brief  Release semaphore of RCC Local Resource Access
  * @rmtoll RCC_RxSEMCR      SEM_MUTEX LL_RCC_ReleaseLocalResSem
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @note Operation will be successful, only if current CID is equal to SEMCID[2:0], which has taken it.
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ReleaseLocalResSem(uint32_t LocalResIndex)
{
  /* In register RCC_RxSEMCR, where x is the local resource index, */
  /* clear SEM_MUTEX (set to 0b0) (only writeable bit) */
  WRITE_REG(RCC->R[LocalResIndex].SEMCR, 0x0);
}

/**
  * @brief  Get semaphore status of RCC Local Resource Access
  * @rmtoll RCC_RxSEMCR      SEMCID    LL_RCC_GetLocalResSem\n
  * @rmtoll RCC_RxSEMCR      SEM_MUTEX LL_RCC_GetLocalResSem
  * @param  LocalResIndex Value in @ref RCC_LL_EC_RIF_LOCALRES
  * @retval Return value can be :
  *         @arg @ref RCC_LOCALRES_TAKEN_SEMCID0
  *         @arg @ref RCC_LOCALRES_TAKEN_SEMCID1
  *         @arg @ref RCC_LOCALRES_TAKEN_SEMCID2
  *         @arg @ref RCC_LOCALRES_TAKEN_SEMCID3
  *         @arg @ref RCC_LOCALRES_TAKEN_SEMCID4
  *         @arg @ref RCC_LOCALRES_TAKEN_SEMCID5
  *         @arg @ref RCC_LOCALRES_TAKEN_SEMCID6
  *         @arg @ref RCC_LOCALRES_TAKEN_SEMCID7
  *         @arg @ref RCC_LOCALRES_RELEASED_SEMCID0
  *         @arg @ref RCC_LOCALRES_RELEASED_SEMCID1
  *         @arg @ref RCC_LOCALRES_RELEASED_SEMCID2
  *         @arg @ref RCC_LOCALRES_RELEASED_SEMCID3
  *         @arg @ref RCC_LOCALRES_RELEASED_SEMCID4
  *         @arg @ref RCC_LOCALRES_RELEASED_SEMCID5
  *         @arg @ref RCC_LOCALRES_RELEASED_SEMCID6
  *         @arg @ref RCC_LOCALRES_RELEASED_SEMCID7
  */
__STATIC_INLINE uint32_t LL_RCC_GetLocalResSem(uint32_t LocalResIndex)
{
  /* Return value of register RCC_RxSEMCR, where x is the local resource index */
  return READ_REG(RCC->R[LocalResIndex].SEMCR);
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
/******************************************************************************/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_LL_RCC_H */
