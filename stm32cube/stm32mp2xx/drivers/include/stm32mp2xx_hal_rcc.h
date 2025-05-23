/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL  module.
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
#ifndef STM32MP2xx_HAL_RCC_H
#define STM32MP2xx_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"
#include "stm32mp2xx_ll_rcc.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, MSI, LSE and LSI) configuration structure definition
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a value of @ref RCC_Oscillator_Type                   */

  uint32_t HSEState;             /*!< The new state of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Config                        */

  uint32_t LSEState;             /*!< The new state of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Config                        */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config                        */

  uint32_t HSICalibrationValue;  /*!< The calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7F
                                      on the other devices */

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config                        */

  uint32_t MSIState;             /*!< The new state of the MSI.
                                      This parameter can be a value of @ref RCC_MSI_Config                        */

  uint32_t MSICalibrationValue;  /*!< The calibration trimming value (default is RCC_MSICALIBRATION_DEFAULT).
                                      This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF */

  uint32_t MSIFrequency;         /*!< The MSI frequency can be 4 or 16 MHz. */

  uint32_t LSEDriveValue;        /*!< The LSE drive value (default is RCC_LSEDRIVE_MEDIUMLOW).
                                      This parameter can be a value of @ref RCC_LSEDrive_Config                   */

} RCC_OscInitTypeDef;

/**
  * @brief Flexgen structure definition.
  */
typedef struct
{
  uint32_t      XBAR_Channel; /* crossbar Channel */
  uint32_t      XBAR_ClkSrc;  /* crossbar input Clock */
  uint32_t      Div;
} RCC_FlexgenTypeDef;

/**
  * @brief Bus clock configuration structure definition.
  */
typedef struct
{
  uint32_t                      ClockType;
  RCC_FlexgenTypeDef            ICN_HS_MCU;
  RCC_FlexgenTypeDef            ICN_SDMMC;
  RCC_FlexgenTypeDef            ICN_DDR;
  RCC_FlexgenTypeDef            ICN_DISPLAY;
  RCC_FlexgenTypeDef            ICN_HCL;
  RCC_FlexgenTypeDef            ICN_NIC;
  RCC_FlexgenTypeDef            ICN_VID;
  uint32_t                      ICN_LSMCU_Div;
  uint32_t                      APB1_Div;
  uint32_t                      APB2_Div;
  uint32_t                      APB3_Div;
  uint32_t                      APB4_Div;
#if defined(RCC_APB5DIVR_APB5DIV)
  uint32_t                      APB5_Div;
#endif /* RCC_APB5DIVR_APB5DIV */
  uint32_t                      APBDBG_Div;
  uint32_t                      RTC_Div;
  uint32_t                      RTC_Src;
  uint32_t                      RTCState;
} RCC_ClkInitTypeDef;

/**
  * @brief Mux configuration structure definition.
  */
typedef struct
{
  uint32_t id;
  uint32_t source;
} RCC_MuxCfgTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Clock_Type RCC_Clock_Type
  * @{
  */
#define RCC_CLOCKTYPE_ICN_HS_MCU        0x00000001U
#define RCC_CLOCKTYPE_ICN_LS_MCU        0x00000002U
#define RCC_CLOCKTYPE_ICN_SDMMC         0x00000004U
#define RCC_CLOCKTYPE_ICN_DDR           0x00000008U
#define RCC_CLOCKTYPE_ICN_DISPLAY       0x00000010U
#define RCC_CLOCKTYPE_ICN_HCL           0x00000020U
#define RCC_CLOCKTYPE_ICN_NIC           0x00000040U
#define RCC_CLOCKTYPE_ICN_VID           0x00000080U
#define RCC_CLOCKTYPE_ICN_APB1          0x00000100U
#define RCC_CLOCKTYPE_ICN_APB2          0x00000200U
#define RCC_CLOCKTYPE_ICN_APB3          0x00000400U
#define RCC_CLOCKTYPE_ICN_APB4          0x00000800U
#if defined(RCC_APB5DIVR_APB5DIV)
#define RCC_CLOCKTYPE_ICN_APB5          0x00001000U
#define RCC_CLOCKTYPE_ICN_APBDBG        0x00002000U
#define RCC_CLOCKTYPE_RTC               0x00004000U
#else
#define RCC_CLOCKTYPE_ICN_APBDBG        0x00001000U
#define RCC_CLOCKTYPE_RTC               0x00002000U
#endif /* RCC_APB5DIVR_APB5DIV */

#if defined(RCC_CLOCKTYPE_ICN_APB5)
#define IS_RCC_CLOCKTYPE(CLOCK)    ((((CLOCK) & RCC_CLOCKTYPE_ICN_HS_MCU)  == RCC_CLOCKTYPE_ICN_HS_MCU)    || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_LS_MCU) == RCC_CLOCKTYPE_ICN_LS_MCU)     || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_SDMMC)  == RCC_CLOCKTYPE_ICN_SDMMC)      || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_DDR) == RCC_CLOCKTYPE_ICN_DDR)           || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_DISPLAY) == RCC_CLOCKTYPE_ICN_DISPLAY)   || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_HCL) == RCC_CLOCKTYPE_ICN_HCL)           || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_NIC) == RCC_CLOCKTYPE_ICN_NIC)           || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_VID) == RCC_CLOCKTYPE_ICN_VID)           || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APB1) == RCC_CLOCKTYPE_ICN_APB1)         || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APB2) == RCC_CLOCKTYPE_ICN_APB2)         || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APB3) == RCC_CLOCKTYPE_ICN_APB3)         || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APB4) == RCC_CLOCKTYPE_ICN_APB4)         || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APB5) == RCC_CLOCKTYPE_ICN_APB5)         || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APBDBG) == RCC_CLOCKTYPE_ICN_APBDBG)     || \
                                    (((CLOCK) & RCC_CLOCKTYPE_RTC) == RCC_CLOCKTYPE_RTC))
#else
#define IS_RCC_CLOCKTYPE(CLOCK)    ((((CLOCK) & RCC_CLOCKTYPE_ICN_HS_MCU)  == RCC_CLOCKTYPE_ICN_HS_MCU)    || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_LS_MCU) == RCC_CLOCKTYPE_ICN_LS_MCU)     || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_SDMMC)  == RCC_CLOCKTYPE_ICN_SDMMC)      || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_DDR) == RCC_CLOCKTYPE_ICN_DDR)           || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_DISPLAY) == RCC_CLOCKTYPE_ICN_DISPLAY)   || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_HCL) == RCC_CLOCKTYPE_ICN_HCL)           || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_NIC) == RCC_CLOCKTYPE_ICN_NIC)           || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_VID) == RCC_CLOCKTYPE_ICN_VID)           || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APB1) == RCC_CLOCKTYPE_ICN_APB1)         || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APB2) == RCC_CLOCKTYPE_ICN_APB2)         || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APB3) == RCC_CLOCKTYPE_ICN_APB3)         || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APB4) == RCC_CLOCKTYPE_ICN_APB4)         || \
                                    (((CLOCK) & RCC_CLOCKTYPE_ICN_APBDBG) == RCC_CLOCKTYPE_ICN_APBDBG)     || \
                                    (((CLOCK) & RCC_CLOCKTYPE_RTC) == RCC_CLOCKTYPE_RTC))

#endif /* RCC_CLOCKTYPE_ICN_APB5 */
/**
  * @}
  */


/** @defgroup RCC_Xbar_Source RCC_Xbar_source
  * @{
  */
#define RCC_XBAR_CLKSRC_PLL4    0U
#define RCC_XBAR_CLKSRC_PLL5    1U
#define RCC_XBAR_CLKSRC_PLL6    2U
#define RCC_XBAR_CLKSRC_PLL7    3U
#define RCC_XBAR_CLKSRC_PLL8    4U
#define RCC_XBAR_CLKSRC_HSI     5U
#define RCC_XBAR_CLKSRC_HSE     6U
#define RCC_XBAR_CLKSRC_MSI     7U
#define RCC_XBAR_CLKSRC_HSI_KER 8U
#define RCC_XBAR_CLKSRC_HSE_KER 9U
#define RCC_XBAR_CLKSRC_MSI_KER 10U
#define RCC_XBAR_CLKSRC_SPDIF   11U
#define RCC_XBAR_CLKSRC_I2S     12U
#define RCC_XBAR_CLKSRC_LSI     13U
#define RCC_XBAR_CLKSRC_LSE     14U
/**
  * @}
  */

/** @defgroup RCC_APBx_Dividers RCC_APBx_Dividers
  * @{
  */
#define RCC_APB1_DIV1           0U
#define RCC_APB1_DIV2           1U
#define RCC_APB1_DIV4           2U
#define RCC_APB1_DIV8           3U
#define RCC_APB1_DIV16          4U

#define RCC_APB2_DIV1           0U
#define RCC_APB2_DIV2           1U
#define RCC_APB2_DIV4           2U
#define RCC_APB2_DIV8           3U
#define RCC_APB2_DIV16          4U

#define RCC_APB3_DIV1           0U
#define RCC_APB3_DIV2           1U
#define RCC_APB3_DIV4           2U
#define RCC_APB3_DIV8           3U
#define RCC_APB3_DIV16          4U

#define RCC_APB4_DIV1           0U
#define RCC_APB4_DIV2           1U
#define RCC_APB4_DIV4           2U
#define RCC_APB4_DIV8           3U
#define RCC_APB4_DIV16          4U
#if defined(RCC_APB5DIVR_APB5DIV)
#define RCC_APB5_DIV1           0U
#define RCC_APB5_DIV2           1U
#define RCC_APB5_DIV4           2U
#define RCC_APB5_DIV8           3U
#define RCC_APB5_DIV16          4U
#endif /* RCC_APB5DIVR_APB5DIV */
#define RCC_APBDBG_DIV1         0U
#define RCC_APBDBG_DIV2         1U
#define RCC_APBDBG_DIV4         2U
#define RCC_APBDBG_DIV8         3U
#define RCC_APBDBG_DIV16        4U

#define RCC_LSMCU_DIV1          0U
#define RCC_LSMCU_DIV2          1U
/**
  * @}
  */


#define HSE_TIMEOUT_VALUE          HSE_STARTUP_TIMEOUT
#define HSI_TIMEOUT_VALUE          (2U)    /* 2 ms (minimum Tick + 1) */
#define MSI_TIMEOUT_VALUE          (2U)    /* 2 ms (minimum Tick + 1) */
#define XBAR_TIMEOUT_VALUE         (2U)    /* 2 ms (minimum Tick + 1) */
#define DBP_TIMEOUT_VALUE          ((uint32_t)100U)


/** @defgroup RCC_Timeout_Value Timeout Values
  * @{
  */
#define RCC_LSE_TIMEOUT_VALUE          LSE_STARTUP_TIMEOUT
/**
  * @}
  */

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE        0x0UL    /*!< Oscillator configuration unchanged */
#define RCC_OSCILLATORTYPE_HSI         0x1UL    /*!< HSI to configure */
#define RCC_OSCILLATORTYPE_HSE         0x2UL    /*!< HSE to configure */
#define RCC_OSCILLATORTYPE_MSI         0x4UL    /*!< MSI to configure */
#define RCC_OSCILLATORTYPE_LSE         0x8UL    /*!< LSE to configure */
#define RCC_OSCILLATORTYPE_LSI         0x10UL   /*!< LSI to configure */
#define IS_RCC_HSI(HSI) (((HSI) == RCC_HSI_OFF) || ((HSI) == RCC_HSI_ON))
/**
  * @}
  */

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                    0x00000000U                                                            /*!< HSE clock deactivation */
#define RCC_HSE_ON                     RCC_OCENSETR_HSEON                                                     /*!< HSE clock activation */
#define RCC_HSE_BYPASS                 (RCC_OCENSETR_HSEBYP | RCC_OCENSETR_HSEON)                             /*!< Analog External clock source for HSE clock */
#define RCC_HSE_BYPASS_DIGITAL         (RCC_OCENSETR_HSEDIGBYP | RCC_OCENSETR_HSEBYP | RCC_OCENSETR_HSEON)    /*!< Digital External clock source for HSE clock */

#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_BYPASS) || ((HSE) == RCC_HSE_BYPASS_DIGITAL))
/**
  * @}
  */

/** @defgroup RCC_LSE_Config LSE Config
  * @{
  */
#define RCC_LSE_OFF                    0U                                                              /*!< LSE clock deactivation */
#define RCC_LSE_ON                     RCC_BDCR_LSEON                                                  /*!< LSE clock activation  */
#define RCC_LSE_BYPASS                 (RCC_BDCR_LSEBYP | RCC_BDCR_LSEON)                              /*!< Analog External clock source for LSE clock */
#define RCC_LSE_BYPASS_DIGITAL         (RCC_BDCR_LSEDIGBYP | RCC_BDCR_LSEBYP | RCC_BDCR_LSEON)         /*!< Digital External clock source for LSE clock */

#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_BYPASS) || ((LSE) == RCC_LSE_BYPASS_DIGITAL))
/**
  * @}
  */

/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                    0x00000000U            /*!< HSI clock deactivation */
#define RCC_HSI_ON                     RCC_OCENSETR_HSION     /*!< HSI clock activation */
#define RCC_HSICALIBRATION_DEFAULT     0x00U                  /* Default HSI calibration trimming value */
/**
  * @}
  */

/** @defgroup RCC_LSI_Config LSI Config
  * @{
  */
#define RCC_LSI_OFF                    0x00000000U        /*!< LSI clock deactivation */

#if defined(RCC_BDCR_LSION)
#define RCC_LSI_ON                     RCC_BDCR_LSION     /*!< LSI clock activation */
#else
#define RCC_LSI_ON                     RCC_LSICR_LSION     /*!< LSI clock activation */
#endif /* RCC_BDCR_LSION */
#define IS_RCC_LSI(LSI) (((LSI) == RCC_LSI_OFF) || ((LSI) == RCC_LSI_ON))
/**
  * @}
  */

/** @defgroup RCC_MSI_Config MSI Config
  * @{
  */
#define RCC_MSI_OFF                    0x00000000U             /*!< MSI clock deactivation */
#if defined(RCC_D3DCR_MSION)
#define RCC_MSI_ON                     RCC_D3DCR_MSION         /*!< MSI clock activation */
#else
#define RCC_MSI_ON                     RCC_OCENSETR_MSION         /*!< MSI clock activation */
#endif /* RCC_D3DCR_MSION */
#define IS_RCC_MSI(MSI) (((MSI) == RCC_MSI_OFF) || ((MSI) == RCC_MSI_ON))
#define RCC_MSICALIBRATION_DEFAULT     0x10U                   /*!< Default MSI calibration trimming value */
#define RCC_MSI_4MHZ                   4000000U
#define RCC_MSI_16MHZ                  16000000U
/**
  * @}
  */

/** @defgroup RCC_RTC_State  RCC RTC State
  * @{
  */
#define RCC_RTC_OFF                  0x00000000U
#define RCC_RTC_ON                   0x00000001U
/**
  * @}
  */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */

/* @cond */
/* 32     28      20       16      0
   --------------------------------
   | MCO   | GPIO  | GPIO  | GPIO  |
   | Index |  AF   | Port  |  Pin  |
   -------------------------------*/

#define RCC_MCO_GPIOPORT_POS   16U
#define RCC_MCO_GPIOPORT_MASK  (0xFUL << RCC_MCO_GPIOPORT_POS)
#define RCC_MCO_GPIOAF_POS     20U
#define RCC_MCO_GPIOAF_MASK    (0xFFUL << RCC_MCO_GPIOAF_POS)
#define RCC_MCO_INDEX_POS      28U
#define RCC_MCO_INDEX_MASK     (0x1UL << RCC_MCO_INDEX_POS)

#define RCC_MCO1_INDEX         (0x0UL << RCC_MCO_INDEX_POS)             /*!< MCO1 index */
#define RCC_MCO2_INDEX         (0x1UL << RCC_MCO_INDEX_POS)             /*!< MCO2 index */
/* @endcond */
#define RCC_MCO1_PC9           (RCC_MCO1_INDEX |\
                                (GPIO_AF1_MCO1 << RCC_MCO_GPIOAF_POS) |\
                                (GPIO_GET_INDEX(GPIOC) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_9)
#define RCC_MCO1_PF11          (RCC_MCO1_INDEX |\
                                (GPIO_AF1_MCO1 << RCC_MCO_GPIOAF_POS) |\
                                (GPIO_GET_INDEX(GPIOF) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_11)
#define RCC_MCO1_PI6           (RCC_MCO1_INDEX |\
                                (GPIO_AF1_MCO1 << RCC_MCO_GPIOAF_POS) |\
                                (GPIO_GET_INDEX(GPIOI) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_6)
#define RCC_MCO1_PZ5           (RCC_MCO1_INDEX |\
                                (GPIO_AF1_MCO1 << RCC_MCO_GPIOAF_POS) |\
                                (GPIO_GET_INDEX(GPIOZ) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_5)
#define RCC_MCO1               RCC_MCO1_PC9         /*!< Alias to be compliant with other families with 1 Pin per MCO output */

#define RCC_MCO2_PF10          (RCC_MCO2_INDEX |\
                                (GPIO_AF1_MCO2 << RCC_MCO_GPIOAF_POS) |\
                                (GPIO_GET_INDEX(GPIOF) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_10)
#define RCC_MCO2_PZ4           (RCC_MCO2_INDEX |\
                                (GPIO_AF2_MCO2 << RCC_MCO_GPIOAF_POS) |\
                                (GPIO_GET_INDEX(GPIOZ) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_4)
#define RCC_MCO2_PZ9           (RCC_MCO2_INDEX |\
                                (GPIO_AF1_MCO2 << RCC_MCO_GPIOAF_POS) |\
                                (GPIO_GET_INDEX(GPIOZ) << RCC_MCO_GPIOPORT_POS) | GPIO_PIN_9)
#define RCC_MCO2               RCC_MCO2_PF10        /*!< Alias to be compliant with other families with 1 Pin per MCO output */

#define RCC_MCO                RCC_MCO1             /*!< Alias to be compliant with other families with 1 MCO */

#define IS_RCC_MCO(__MCOX__) (((__MCOX__) == RCC_MCO1_PC9) || \
                              ((__MCOX__) == RCC_MCO1_PF11) || \
                              ((__MCOX__) == RCC_MCO1_PI6) || \
                              ((__MCOX__) == RCC_MCO1_PZ5) || \
                              ((__MCOX__) == RCC_MCO2_PF10) || \
                              ((__MCOX__) == RCC_MCO2_PZ4) || \
                              ((__MCOX__) == RCC_MCO2_PZ9))

/**
  * @}
  */

/** @defgroup RCC_MCO1_Clock_Source MCO1 Clock Source
  * @{
  */
#define RCC_MCO1SOURCE_NOCLOCK         0x00000000U                              /*!< MCO1 output disabled, no clock on MCO1 */
#define RCC_MCO1SOURCE_CLKOBS          0x000000FFU                              /*!< Clock Observer 0 selected as MCO1 Source */
#define RCC_MCO1SOURCE_PLL4            (0x00000100U | RCC_XBAR_CLKSRC_PLL4)     /*!< PLL4 selected as MCO1 Source */
#define RCC_MCO1SOURCE_PLL5            (0x00000100U | RCC_XBAR_CLKSRC_PLL5)     /*!< PLL5 selected as MCO1 Source */
#define RCC_MCO1SOURCE_PLL6            (0x00000100U | RCC_XBAR_CLKSRC_PLL6)     /*!< PLL6 selected as MCO1 Source */
#define RCC_MCO1SOURCE_PLL7            (0x00000100U | RCC_XBAR_CLKSRC_PLL7)     /*!< PLL7 selected as MCO1 Source */
#define RCC_MCO1SOURCE_PLL8            (0x00000100U | RCC_XBAR_CLKSRC_PLL8)     /*!< PLL8 selected as MCO1 Source */
#define RCC_MCO1SOURCE_HSI             (0x00000100U | RCC_XBAR_CLKSRC_HSI)      /*!< HSI selected as MCO1 Source */
#define RCC_MCO1SOURCE_HSE             (0x00000100U | RCC_XBAR_CLKSRC_HSE)      /*!< HSE selected as MCO1 Source */
#define RCC_MCO1SOURCE_MSI             (0x00000100U | RCC_XBAR_CLKSRC_MSI)      /*!< MSI selected as MCO1 Source */
#define RCC_MCO1SOURCE_HSI_KER         (0x00000100U | RCC_XBAR_CLKSRC_HSI_KER)  /*!< HSI_KER selected as MCO1 Source */
#define RCC_MCO1SOURCE_HSE_KER         (0x00000100U | RCC_XBAR_CLKSRC_HSE_KER)  /*!< HSE_KER selected as MCO1 Source */
#define RCC_MCO1SOURCE_MSI_KER         (0x00000100U | RCC_XBAR_CLKSRC_MSI_KER)  /*!< MSI_KER selected as MCO1 Source */
#define RCC_MCO1SOURCE_SPDIF           (0x00000100U | RCC_XBAR_CLKSRC_SPDIF)    /*!< SPDIF selected as MCO1 Source */
#define RCC_MCO1SOURCE_I2S             (0x00000100U | RCC_XBAR_CLKSRC_I2S)      /*!< I2S selected as MCO1 Source */
#define RCC_MCO1SOURCE_LSI             (0x00000100U | RCC_XBAR_CLKSRC_LSI)      /*!< LSI selected as MCO1 Source */
#define RCC_MCO1SOURCE_LSE             (0x00000100U | RCC_XBAR_CLKSRC_LSE)      /*!< LSE selected as MCO1 Source */

#define IS_RCC_MCO1SOURCE(__SOURCE__)  (((__SOURCE__) == RCC_MCO1SOURCE_NOCLOCK) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_CLKOBS) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_PLL4) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_HSE) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_PLL5) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_PLL6) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_PLL7) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_PLL8) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_HSI) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_HSE) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_MSI) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_HSI_KER) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_HSE_KER) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_MSI_KER) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_SPDIF) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_I2S) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_LSI) || \
                                        ((__SOURCE__) == RCC_MCO1SOURCE_LSE))

/**
  * @}
  */

/** @defgroup RCC_MCO2_Clock_Source MCO2 Clock Source
  * @{
  */
#define RCC_MCO2SOURCE_NOCLOCK         0x00000000U                              /*!< MCO2 output disabled, no clock on MCO2 */
#define RCC_MCO2SOURCE_CLKOBS          0x000000FFU                              /*!< Clock Observer 1 selected as MCO2 Source */
#define RCC_MCO2SOURCE_PLL4            (0x00000100U | RCC_XBAR_CLKSRC_PLL4)     /*!< PLL4 selected as MCO2 Source */
#define RCC_MCO2SOURCE_PLL5            (0x00000100U | RCC_XBAR_CLKSRC_PLL5)     /*!< PLL5 selected as MCO2 Source */
#define RCC_MCO2SOURCE_PLL6            (0x00000100U | RCC_XBAR_CLKSRC_PLL6)     /*!< PLL6 selected as MCO2 Source */
#define RCC_MCO2SOURCE_PLL7            (0x00000100U | RCC_XBAR_CLKSRC_PLL7)     /*!< PLL7 selected as MCO2 Source */
#define RCC_MCO2SOURCE_PLL8            (0x00000100U | RCC_XBAR_CLKSRC_PLL8)     /*!< PLL8 selected as MCO2 Source */
#define RCC_MCO2SOURCE_HSI             (0x00000100U | RCC_XBAR_CLKSRC_HSI)      /*!< HSI selected as MCO2 Source */
#define RCC_MCO2SOURCE_HSE             (0x00000100U | RCC_XBAR_CLKSRC_HSE)      /*!< HSE selected as MCO2 Source */
#define RCC_MCO2SOURCE_MSI             (0x00000100U | RCC_XBAR_CLKSRC_MSI)      /*!< MSI selected as MCO2 Source */
#define RCC_MCO2SOURCE_HSI_KER         (0x00000100U | RCC_XBAR_CLKSRC_HSI_KER)  /*!< HSI_KER selected as MCO2 Source */
#define RCC_MCO2SOURCE_HSE_KER         (0x00000100U | RCC_XBAR_CLKSRC_HSE_KER)  /*!< HSE_KER selected as MCO2 Source */
#define RCC_MCO2SOURCE_MSI_KER         (0x00000100U | RCC_XBAR_CLKSRC_MSI_KER)  /*!< MSI_KER selected as MCO2 Source */
#define RCC_MCO2SOURCE_SPDIF           (0x00000100U | RCC_XBAR_CLKSRC_SPDIF)    /*!< SPDIF selected as MCO2 Source */
#define RCC_MCO2SOURCE_I2S             (0x00000100U | RCC_XBAR_CLKSRC_I2S)      /*!< I2S selected as MCO2 Source */
#define RCC_MCO2SOURCE_LSI             (0x00000100U | RCC_XBAR_CLKSRC_LSI)      /*!< LSI selected as MCO2 Source */
#define RCC_MCO2SOURCE_LSE             (0x00000100U | RCC_XBAR_CLKSRC_LSE)      /*!< LSE selected as MCO2 Source */

#define IS_RCC_MCO2SOURCE(__SOURCE__)  (((__SOURCE__) == RCC_MCO2SOURCE_NOCLOCK) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_CLKOBS) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_PLL4) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_HSE) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_PLL5) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_PLL6) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_PLL7) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_PLL8) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_HSI) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_HSE) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_MSI) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_HSI_KER) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_HSE_KER) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_MSI_KER) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_SPDIF) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_I2S) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_LSI) || \
                                        ((__SOURCE__) == RCC_MCO2SOURCE_LSE))

/**
  * @}
  */

/** @defgroup RCC_MCOx_Clock_Prescaler MCO1 Clock Prescaler
  * @{
  */

#define IS_RCC_MCODIV                   IS_RCC_XBARDIV    /* MCO Dividers are actually XBAR dividers */

/**
  * @}
  */

/** @defgroup RCC_Interrupt Interrupts
  * @{
  */
#define RCC_C1IT_LSIRDY       RCC_C1CIFCLRR_LSIRDYF
#define RCC_C1IT_LSERDY       RCC_C1CIFCLRR_LSERDYF
#define RCC_C1IT_HSIRDY       RCC_C1CIFCLRR_HSIRDYF
#define RCC_C1IT_HSERDY       RCC_C1CIFCLRR_HSERDYF
#define RCC_C1IT_MSIRDY       RCC_C1CIFCLRR_MSIRDYF
#define RCC_C1IT_PLL1RDY      RCC_C1CIFCLRR_PLL1RDYF
#define RCC_C1IT_PLL2RDY      RCC_C1CIFCLRR_PLL2RDYF
#if defined(RCC_C1CIFCLRR_PLL3RDYF)
#define RCC_C1IT_PLL3RDY      RCC_C1CIFCLRR_PLL3RDYF
#endif /* RCC_C1CIFCLRR_PLL3RDYF */
#define RCC_C1IT_PLL4RDY      RCC_C1CIFCLRR_PLL4RDYF
#define RCC_C1IT_PLL5RDY      RCC_C1CIFCLRR_PLL5RDYF
#define RCC_C1IT_PLL6RDY      RCC_C1CIFCLRR_PLL6RDYF
#define RCC_C1IT_PLL7RDY      RCC_C1CIFCLRR_PLL7RDYF
#define RCC_C1IT_PLL8RDY      RCC_C1CIFCLRR_PLL8RDYF
#define RCC_C1IT_LSECSS       RCC_C1CIFCLRR_LSECSSF
#define RCC_C1IT_WKUP         RCC_C1CIFCLRR_WKUPF
#define RCC_C2IT_LSIRDY       RCC_C2CIFCLRR_LSIRDYF
#define RCC_C2IT_LSERDY       RCC_C2CIFCLRR_LSERDYF
#define RCC_C2IT_HSIRDY       RCC_C2CIFCLRR_HSIRDYF
#define RCC_C2IT_HSERDY       RCC_C2CIFCLRR_HSERDYF
#define RCC_C2IT_MSIRDY       RCC_C2CIFCLRR_MSIRDYF
#define RCC_C2IT_PLL1RDY      RCC_C2CIFCLRR_PLL1RDYF
#define RCC_C2IT_PLL2RDY      RCC_C2CIFCLRR_PLL2RDYF
#if defined(RCC_C2CIFCLRR_PLL3RDYF)
#define RCC_C2IT_PLL3RDY      RCC_C2CIFCLRR_PLL3RDYF
#endif /* RCC_C2CIFCLRR_PLL3RDYF */
#define RCC_C2IT_PLL4RDY      RCC_C2CIFCLRR_PLL4RDYF
#define RCC_C2IT_PLL5RDY      RCC_C2CIFCLRR_PLL5RDYF
#define RCC_C2IT_PLL6RDY      RCC_C2CIFCLRR_PLL6RDYF
#define RCC_C2IT_PLL7RDY      RCC_C2CIFCLRR_PLL7RDYF
#define RCC_C2IT_PLL8RDY      RCC_C2CIFCLRR_PLL8RDYF
#define RCC_C2IT_LSECSS       RCC_C2CIFCLRR_LSECSSF
#define RCC_C2IT_WKUP         RCC_C2CIFCLRR_WKUPF
/**
  * @}
  */

/** @defgroup RCC_Flag Flags
  *        Elements values convention: XXXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - XXX  : Register index
  *                 - 001: CR register
  *                 - 010: BDCR register
  *                 - 011: CSR register
  *                 - 100: CRRCR register
  * @{
  */
#define RCC_FLAG_MASK                   0x1FUL
#define RCC_HWRSTSCLRR_FLAGS_ID         1UL
#define RCC_C1HWRSTSCLRR_FLAGS_ID       2UL
#define RCC_C2HWRSTSCLRR_FLAGS_ID       3UL
#define RCC_OCRDYR_FLAGS_ID             4UL
#if defined(RCC_D3DCR_MSION)
#define RCC_D3DCR_FLAGS_ID              5UL
#else
#define RCC_LSICR_FLAGS_ID              5UL
#endif /* RCC_D3DCR_MSION */
#define RCC_BDCR_FLAGS_ID               6UL
#define RCC_FLAG_PORRST                 ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_PORRSTF_Pos)
#define RCC_FLAG_BORRST                 ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_BORRSTF_Pos)
#define RCC_FLAG_PADRST                 ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_PADRSTF_Pos)
#define RCC_FLAG_HCSSRST                ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_HCSSRSTF_Pos)
#define RCC_FLAG_VCORERST               ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_VCORERSTF_Pos)
#define RCC_FLAG_VCPURSTF               ((RCC_C1HWRSTSCLRR_FLAGS_ID << 5UL) | RCC_C1HWRSTSCLRR_VCPURSTF_Pos)
#define RCC_FLAG_SYSC1RSTF              ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_SYSC1RSTF_Pos)
#define RCC_FLAG_SYSC2RSTF              ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_SYSC2RSTF_Pos)
#define RCC_FLAG_IWDG1RSTF              ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_IWDG1SYSRSTF_Pos)
#define RCC_FLAG_IWDG2RSTF              ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_IWDG2SYSRSTF_Pos)
#define RCC_FLAG_IWDG3RSTF              ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_IWDG3SYSRSTF_Pos)
#define RCC_FLAG_IWDG4RSTF              ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_IWDG4SYSRSTF_Pos)
#if defined(RCC_HWRSTSCLRR_IWDG5SYSRSTF_Pos)
#define RCC_FLAG_IWDG5RSTF              ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_IWDG5SYSRSTF_Pos)
#endif /* RCC_HWRSTSCLRR_IWDG5SYSRSTF_Pos */
#define RCC_FLAG_C1RSTF                 ((RCC_C1HWRSTSCLRR_FLAGS_ID << 5UL) | RCC_C1HWRSTSCLRR_C1RSTF_Pos)
#define RCC_FLAG_C2RSTF                 ((RCC_C2HWRSTSCLRR_FLAGS_ID << 5UL) | RCC_C2HWRSTSCLRR_C2RSTF_Pos)
#define RCC_FLAG_C1P1RSTF               ((RCC_C1HWRSTSCLRR_FLAGS_ID << 5UL) | RCC_C1HWRSTSCLRR_C1P1RSTF_Pos)
#define RCC_FLAG_RETCRCERRRSTF          ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_RETCRCERRRSTF_Pos)
#define RCC_FLAG_RETECCFAILCRCRSTF      ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_RETECCFAILCRCRSTF_Pos)
#define RCC_FLAG_RETECCFAILRESTRSTF     ((RCC_HWRSTSCLRR_FLAGS_ID   << 5UL) | RCC_HWRSTSCLRR_RETECCFAILRESTRSTF_Pos)

#define RCC_FLAG_HSIRDY                 ((RCC_OCRDYR_FLAGS_ID       << 5UL) | RCC_OCRDYR_HSIRDY_Pos)
#if defined(RCC_D3DCR_FLAGS_ID)
#define RCC_FLAG_MSIRDY                 ((RCC_D3DCR_FLAGS_ID        << 5UL) | RCC_D3DCR_MSIRDY_Pos)
#elif defined(RCC_OCRDYR_FLAGS_ID)
#define RCC_FLAG_MSIRDY                 ((RCC_OCRDYR_FLAGS_ID       << 5UL) | RCC_OCRDYR_MSIRDY_Pos)
#endif /* RCC_OCRDYR_FLAGS_ID */
#define RCC_FLAG_HSERDY                 ((RCC_OCRDYR_FLAGS_ID       << 5UL) | RCC_OCRDYR_HSERDY_Pos)
#define RCC_FLAG_LSERDY                 ((RCC_BDCR_FLAGS_ID         << 5UL) | RCC_BDCR_LSERDY_Pos)
#if defined(RCC_BDCR_LSIRDY_Pos)
#define RCC_FLAG_LSIRDY                 ((RCC_BDCR_FLAGS_ID         << 5UL) | RCC_BDCR_LSIRDY_Pos)
#elif defined(RCC_LSICR_LSIRDY_Pos)
#define RCC_FLAG_LSIRDY                 ((RCC_LSICR_FLAGS_ID        << 5UL) | RCC_LSICR_LSIRDY_Pos)
#endif /* RCC_BDCR_LSIRDY_Pos */
#define RCC_FLAG_CKREST                 ((RCC_OCRDYR_FLAGS_ID       << 5UL) | RCC_OCRDYR_CKREST_Pos)

/**
  * @}
  */

/** @defgroup RCC_LSEDrive_Config LSE Drive Config
  * @{
  */
#define RCC_LSEDRIVE_LOW                 LL_RCC_LSEDRIVE_LOW        /*!< LSE low drive capability */
#define RCC_LSEDRIVE_MEDIUMHIGH          LL_RCC_LSEDRIVE_MEDIUMHIGH /*!< LSE medium high drive capability */
#define RCC_LSEDRIVE_MEDIUMLOW           LL_RCC_LSEDRIVE_MEDIUMLOW  /*!< LSE medium low drive capability */
#define RCC_LSEDRIVE_HIGH                LL_RCC_LSEDRIVE_HIGH       /*!< LSE high drive capability */
/**
  * @}
  */

/** @defgroup RCC_Exported_Macros RCC Exported Macros
  * @{
  */
#if defined(RCC_D3DCR_FLAGS_ID)
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5UL) == RCC_HWRSTSCLRR_FLAGS_ID  ) ? RCC->HWRSTSCLRR : \
                                         ((((__FLAG__) >> 5UL) == RCC_C1HWRSTSCLRR_FLAGS_ID) ? RCC->C1HWRSTSCLRR : \
                                          ((((__FLAG__) >> 5UL) == RCC_C2HWRSTSCLRR_FLAGS_ID) ? RCC->C2HWRSTSCLRR : \
                                           ((((__FLAG__) >> 5UL) == RCC_OCRDYR_FLAGS_ID      ) ? RCC->OCRDYR : \
                                            ((((__FLAG__) >> 5UL) == RCC_D3DCR_FLAGS_ID       ) ? RCC->D3DCR : \
                                             ((((__FLAG__) >> 5UL) == RCC_BDCR_FLAGS_ID        ) ? RCC->BDCR : \
                                              0U)))))) & (1UL << ((__FLAG__) & RCC_FLAG_MASK))) != 0U) ? SET : RESET)
#else
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5UL) == RCC_HWRSTSCLRR_FLAGS_ID  ) ? RCC->HWRSTSCLRR : \
                                         ((((__FLAG__) >> 5UL) == RCC_C1HWRSTSCLRR_FLAGS_ID) ? RCC->C1HWRSTSCLRR : \
                                          ((((__FLAG__) >> 5UL) == RCC_C2HWRSTSCLRR_FLAGS_ID) ? RCC->C2HWRSTSCLRR : \
                                           ((((__FLAG__) >> 5UL) == RCC_OCRDYR_FLAGS_ID      ) ? RCC->OCRDYR : \
                                            ((((__FLAG__) >> 5UL) == RCC_LSICR_FLAGS_ID       ) ? RCC->LSICR : \
                                             ((((__FLAG__) >> 5UL) == RCC_BDCR_FLAGS_ID        ) ? RCC->BDCR : \
                                              0U)))))) & (1UL << ((__FLAG__) & RCC_FLAG_MASK))) != 0U) ? SET : RESET)
#endif /* RCC_D3DCR_FLAGS_ID */

#if defined(RCC_LSICR_LSION)
#define __HAL_RCC_LSI_ENABLE()  SET_BIT(RCC->LSICR, RCC_LSICR_LSION)
#define __HAL_RCC_LSI_DISABLE() CLEAR_BIT(RCC->LSICR, RCC_LSICR_LSION)
#elif defined(RCC_BDCR_LSION)
#define __HAL_RCC_LSI_ENABLE()  SET_BIT(RCC->BDCR, RCC_BDCR_LSION)
#define __HAL_RCC_LSI_DISABLE() CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSION)
#endif /* RCC_LSICR_LSION */
#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICalibrationValue__) \
  MODIFY_REG(RCC->HSICFGR, RCC_HSICFGR_HSITRIM, \
             (uint32_t)(__HSICalibrationValue__) << RCC_HSICFGR_HSITRIM_Pos)
#define __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(__MSICalibrationValue__) \
  MODIFY_REG(RCC->MSICFGR, RCC_MSICFGR_MSITRIM, \
             (uint32_t)(__MSICalibrationValue__) << RCC_MSICFGR_MSITRIM_Pos)
/**
  * @}
  */

/** @defgroup RCC_items RCC items
  * @brief RCC items to configure attributes on
  * @{
  */
#define RCC_HSI                        RCC_SECCFGR_HSISEC
#define RCC_HSE                        RCC_SECCFGR_HSESEC
#define RCC_MSI                        RCC_SECCFGR_MSISEC
#define RCC_LSI                        RCC_SECCFGR_LSISEC
#define RCC_LSE                        RCC_SECCFGR_LSESEC
#define RCC_SYSCLK                     RCC_SECCFGR_SYSCLKSEC
#define RCC_PRESC                      RCC_SECCFGR_PRESCSEC
#define RCC_PLL1                       RCC_SECCFGR_PLL1SEC
#define RCC_PLL2                       RCC_SECCFGR_PLL2SEC
#if defined(RCC_PLL3CFGR1_PLLEN)
#define RCC_PLL3                       RCC_SECCFGR_PLL3SEC
#endif /* RCC_PLL3CFGR1_PLLEN */
#define RCC_CLK48M                     RCC_SECCFGR_CLK48MSEC
#define RCC_HSI48                      RCC_SECCFGR_HSI48SEC
#define RCC_RMVF                       RCC_SECCFGR_RMVFSEC
#if defined(RCC_PLL3CFGR1_PLLEN)
#define RCC_ALL                        (RCC_HSI|RCC_HSE|RCC_MSI|RCC_LSI|RCC_LSE|RCC_HSI48| \
                                        RCC_SYSCLK|RCC_PRESC|RCC_PLL1|RCC_PLL2| \
                                        RCC_PLL3|RCC_CLK48M|RCC_RMVF)
#else
#define RCC_ALL                        (RCC_HSI|RCC_HSE|RCC_MSI|RCC_LSI|RCC_LSE|RCC_HSI48| \
                                        RCC_SYSCLK|RCC_PRESC|RCC_PLL1|RCC_PLL2| \
                                        RCC_CLK48M|RCC_RMVF)
#endif /* RCC_PLL3CFGR1_PLLEN */
/**
  * @}
  */

/** @defgroup RCC_HAL_EC_RIF_LOCALRES_ACCESS RCC HAL Filtering of Local Resource Access
  * @{
  */
/****************************************************************************/
/* WARNING about LEGACY constants !                                         */
/* FOR AVOIDING CONFUSION IN SECURITY & PRIVILEGE ACCESS FILTERING          */
/* - "NSEC" stands for "No Security Filtering for Local Resource Access",   */
/*   which means that not only "secure" but also "non-secure" accesses are  */
/*   allowed.                                                               */
/* - "NPRIV" stands for "No Privilege Filtering for Local Resource Access", */
/*   which means that not only "privileged" but also "not-privileged"       */
/*   accesses are allowed.                                                  */
/****************************************************************************/

#define RCC_LOCALRES_PRIV    0x00000E00U   /*!< Privilege attribute for Local Resource Access Filtering */
#define RCC_LOCALRES_NPRIV   0x00000300U   /*!< No Privilege attribute for Local Resource Access Filtering */
#define RCC_LOCALRES_NOPRIV  0x00000300U   /*!< No Privilege attribute for Local Resource Access Filtering */

#define RCC_LOCALRES_SEC     0x00005000U   /*!< Secure attribute for Local Resource Access Filtering */
#define RCC_LOCALRES_NSEC    0x00002000U   /*!< Unsecure/No Security attribute for Local Resource Access Filtering */
#define RCC_LOCALRES_NOSEC   0x00002000U   /*!< Unsecure/No Security attribute for Local Resource Access Filtering */

#define RCC_LOCALRES_LOCKED  0xDD000000U   /*!< Lock attribute for configuration of Local Resource Access Filtering */
/**
  * @}
  */

/** @defgroup RCC_HAL_EC_RIF_LOCALRES_ATTRIBUTES RCC HAL Attributes for Local Resource Access Filtering
  * @{
  */
#define RCC_LOCALRES_ATTR_NONE     0x00000000U   /*!< No Attribute value for Local Resource Access Filtering */
#define RCC_LOCALRES_ATTR_INVALID  0x2200008CU   /*!< Invalid Attribute value for Local Resource Access Filtering */

#define RCC_LOCALRES_ATTR_CID_TYPE_POS      (0U)
#define RCC_LOCALRES_ATTR_CID_TYPE_MSK      (0x3UL << RCC_LOCALRES_ATTR_CID_TYPE_POS)
#define RCC_LOCALRES_ATTR_STATIC_CID_POS    (4U)
#define RCC_LOCALRES_ATTR_STATIC_CID_MSK    (0x7UL << RCC_LOCALRES_ATTR_STATIC_CID_POS)
#define RCC_LOCALRES_ATTR_PRIV_POS          (8U)
#define RCC_LOCALRES_ATTR_PRIV_MSK          (0xFUL << RCC_LOCALRES_ATTR_PRIV_POS)
#define RCC_LOCALRES_ATTR_SEC_POS           (12U)
#define RCC_LOCALRES_ATTR_SEC_MSK           (0xFUL << RCC_LOCALRES_ATTR_SEC_POS)
#define RCC_LOCALRES_ATTR_DYNAMIC_CID_POS   (16U)
#define RCC_LOCALRES_ATTR_DYNAMIC_CID_MSK   (0xFFUL << RCC_LOCALRES_ATTR_DYNAMIC_CID_POS)
#define RCC_LOCALRES_ATTR_LOCK_POS          (24U)
#define RCC_LOCALRES_ATTR_LOCK_MSK          (0xFFUL << RCC_LOCALRES_ATTR_LOCK_POS)
/**
  * @}
  */
/**
  * @}
 */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup RCC_Exported_Macros RCC Exported Macros
  * @{
  */
#if defined(RCC_VDERAMCFGR_VDERAMEN)
#define __HAL_RCC_VDERAM_CLK_ENABLE()             SET_BIT(RCC->VDERAMCFGR, RCC_VDERAMCFGR_VDERAMEN)
#endif /* RCC_VDERAMCFGR_VDERAMEN */

#if defined(RCC_SERCCFGR_SERCEN)
#define __HAL_RCC_SERC_CLK_ENABLE()               SET_BIT(RCC->SERCCFGR, RCC_SERCCFGR_SERCEN)
#endif /* RCC_SERCCFGR_SERCEN */

#if defined(RCC_OSPIIOMCFGR_OSPIIOMEN)
#define __HAL_RCC_OSPIIOM_CLK_ENABLE()            SET_BIT(RCC->OSPIIOMCFGR, RCC_OSPIIOMCFGR_OSPIIOMEN)
#endif /*  */

#if defined(RCC_ETHSWCFGR_ETHSWMACEN)
#define __HAL_RCC_ETHSW_CLK_ENABLE()              SET_BIT(RCC->ETHSWCFGR, RCC_ETHSWCFGR_ETHSWMACEN|\
                                                          RCC_ETHSWCFGR_ETHSWEN|RCC_ETHSWCFGR_ETHSWREFEN)
#endif /* RCC_ETHSWCFGR_ETHSWMACEN */

#if defined(RCC_VDECCFGR_VDECEN)
#define __HAL_RCC_VDEC_CLK_ENABLE()               SET_BIT(RCC->VDECCFGR, RCC_VDECCFGR_VDECEN)
#endif /* RCC_VDECCFGR_VDECEN */

#if defined(RCC_VENCCFGR_VENCEN)
#define __HAL_RCC_VENC_CLK_ENABLE()               SET_BIT(RCC->VENCCFGR, RCC_VENCCFGR_VENCEN)
#endif /* RCC_VENCCFGR_VENCEN */

#if defined(RCC_C3CFGR_C3EN)
#define __HAL_RCC_C3_CLK_ENABLE()                 SET_BIT(RCC->C3CFGR, RCC_C3CFGR_C3EN)
#endif /* RCC_C3CFGR_C3EN */

#if defined(RCC_SYSRAMCFGR_SYSRAMEN)
#define __HAL_RCC_SYSRAM_CLK_ENABLE()             SET_BIT(RCC->SYSRAMCFGR, RCC_SYSRAMCFGR_SYSRAMEN)
#endif /* RCC_SYSRAMCFGR_SYSRAMEN */

#if defined(RCC_SRAM1CFGR_SRAM1EN)
#define __HAL_RCC_SRAM1_CLK_ENABLE()              SET_BIT(RCC->SRAM1CFGR, RCC_SRAM1CFGR_SRAM1EN)
#endif /* RCC_SRAM1CFGR_SRAM1EN */

#if defined(RCC_SRAM2CFGR_SRAM2EN)
#define __HAL_RCC_SRAM2_CLK_ENABLE()              SET_BIT(RCC->SRAM2CFGR, RCC_SRAM2CFGR_SRAM2EN)
#endif /* RCC_SRAM2CFGR_SRAM2EN */

#if defined(RCC_RETRAMCFGR_RETRAMEN)
#define __HAL_RCC_RETRAM_CLK_ENABLE()             SET_BIT(RCC->RETRAMCFGR, RCC_RETRAMCFGR_RETRAMEN)
#endif /* RCC_RETRAMCFGR_RETRAMEN */

#if defined(RCC_BKPSRAMCFGR_BKPSRAMEN)
#define __HAL_RCC_BKPSRAM_CLK_ENABLE()            SET_BIT(RCC->BKPSRAMCFGR, RCC_BKPSRAMCFGR_BKPSRAMEN)
#endif /* RCC_BKPSRAMCFGR_BKPSRAMEN */

#if defined(RCC_LPSRAM1CFGR_LPSRAM1EN)
#define __HAL_RCC_LPSRAM1_CLK_ENABLE()            SET_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1EN)
#endif /* RCC_LPSRAM1CFGR_LPSRAM1EN */

#if defined(RCC_LPSRAM2CFGR_LPSRAM2EN)
#define __HAL_RCC_LPSRAM2_CLK_ENABLE()            SET_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2EN)
#endif /* RCC_LPSRAM2CFGR_LPSRAM2EN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3EN)
#define __HAL_RCC_LPSRAM3_CLK_ENABLE()            SET_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3EN)
#endif /* RCC_LPSRAM3CFGR_LPSRAM3EN */

#if defined(RCC_OSPI1CFGR_OSPI1EN)
#define __HAL_RCC_OSPI1_CLK_ENABLE()              SET_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1EN)
#endif /* RCC_OSPI1CFGR_OSPI1EN */

#if defined(RCC_OSPI2CFGR_OSPI2EN)
#define __HAL_RCC_OSPI2_CLK_ENABLE()              SET_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2EN)
#endif /* RCC_OSPI2CFGR_OSPI2EN */

#if defined(RCC_STMCFGR_STMEN)
#define __HAL_RCC_STM_CLK_ENABLE()             SET_BIT(RCC->STMCFGR, RCC_STMCFGR_STMEN)
#endif /* RCC_STMCFGR_STMEN */

#if defined(RCC_ETRCFGR_ETREN)
#define __HAL_RCC_ETR_CLK_ENABLE()                SET_BIT(RCC->ETRCFGR, RCC_ETRCFGR_ETREN)
#endif /* RCC_ETRCFGR_ETREN */

#if defined(RCC_GPIOACFGR_GPIOxEN)
#define __HAL_RCC_GPIOA_CLK_ENABLE()              SET_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxEN)
#endif /* RCC_GPIOACFGR_GPIOxEN */

#if defined(RCC_GPIOBCFGR_GPIOxEN)
#define __HAL_RCC_GPIOB_CLK_ENABLE()              SET_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxEN)
#endif /* RCC_GPIOBCFGR_GPIOxEN */

#if defined(RCC_GPIOCCFGR_GPIOxEN)
#define __HAL_RCC_GPIOC_CLK_ENABLE()              SET_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxEN)
#endif /* RCC_GPIOCCFGR_GPIOxEN */

#if defined(RCC_GPIODCFGR_GPIOxEN)
#define __HAL_RCC_GPIOD_CLK_ENABLE()              SET_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxEN)
#endif /* RCC_GPIODCFGR_GPIOxEN */

#if defined(RCC_GPIOECFGR_GPIOxEN)
#define __HAL_RCC_GPIOE_CLK_ENABLE()              SET_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxEN)
#endif /* RCC_GPIOECFGR_GPIOxEN */

#if defined(RCC_GPIOFCFGR_GPIOxEN)
#define __HAL_RCC_GPIOF_CLK_ENABLE()              SET_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxEN)
#endif /* RCC_GPIOFCFGR_GPIOxEN */

#if defined(RCC_GPIOGCFGR_GPIOxEN)
#define __HAL_RCC_GPIOG_CLK_ENABLE()              SET_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxEN)
#endif /* RCC_GPIOGCFGR_GPIOxEN */

#if defined(RCC_GPIOHCFGR_GPIOxEN)
#define __HAL_RCC_GPIOH_CLK_ENABLE()              SET_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxEN)
#endif /* RCC_GPIOHCFGR_GPIOxEN */

#if defined(RCC_GPIOICFGR_GPIOxEN)
#define __HAL_RCC_GPIOI_CLK_ENABLE()              SET_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxEN)
#endif /* RCC_GPIOICFGR_GPIOxEN */

#if defined(RCC_GPIOJCFGR_GPIOxEN)
#define __HAL_RCC_GPIOJ_CLK_ENABLE()              SET_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxEN)
#endif /* RCC_GPIOJCFGR_GPIOxEN */

#if defined(RCC_GPIOKCFGR_GPIOxEN)
#define __HAL_RCC_GPIOK_CLK_ENABLE()              SET_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxEN)
#endif /* RCC_GPIOKCFGR_GPIOxEN */

#if defined(RCC_GPIOZCFGR_GPIOZEN)
#define __HAL_RCC_GPIOZ_CLK_ENABLE()              SET_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZEN)
#endif /* RCC_GPIOZCFGR_GPIOZEN */

#if defined(RCC_HPDMA1CFGR_HPDMA1EN)
#define __HAL_RCC_HPDMA1_CLK_ENABLE()             SET_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1EN)
#endif /* RCC_HPDMA1CFGR_HPDMA1EN */

#if defined(RCC_HPDMA2CFGR_HPDMA2EN)
#define __HAL_RCC_HPDMA2_CLK_ENABLE()             SET_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2EN)
#endif /* RCC_HPDMA2CFGR_HPDMA2EN */

#if defined(RCC_HPDMA3CFGR_HPDMA3EN)
#define __HAL_RCC_HPDMA3_CLK_ENABLE()             SET_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3EN)
#endif /* RCC_HPDMA3CFGR_HPDMA3EN */

#if defined(RCC_LPDMACFGR_LPDMAEN)
#define __HAL_RCC_LPDMA_CLK_ENABLE()              SET_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMAEN)
#endif /* RCC_LPDMACFGR_LPDMAEN */

#if defined(RCC_HSEMCFGR_HSEMEN)
#define __HAL_RCC_HSEM_CLK_ENABLE()               SET_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMEN)
#endif /* RCC_HSEMCFGR_HSEMEN */

#if defined(RCC_IPCC1CFGR_IPCC1EN)
#define __HAL_RCC_IPCC1_CLK_ENABLE()              SET_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1EN)
#endif /* RCC_IPCC1CFGR_IPCC1EN */

#if defined(RCC_IPCC2CFGR_IPCC2EN)
#define __HAL_RCC_IPCC2_CLK_ENABLE()              SET_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2EN)
#endif /* RCC_IPCC2CFGR_IPCC2EN */

#if defined(RCC_RTCCFGR_RTCEN)
#define __HAL_RCC_RTC_CLK_ENABLE()                SET_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCEN)
#endif /* RCC_RTCCFGR_RTCEN */

#if defined(RCC_SYSCPU1CFGR_SYSCPU1EN)
#define __HAL_RCC_SYSCPU1_CLK_ENABLE()            SET_BIT(RCC->SYSCPU1CFGR, RCC_SYSCPU1CFGR_SYSCPU1EN)
#endif /* RCC_SYSCPU1CFGR_SYSCPU1EN */

#if defined(RCC_IS2MCFGR_IS2MEN)
#define __HAL_RCC_IS2M_CLK_ENABLE()               SET_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MEN)
#endif /* RCC_IS2MCFGR_IS2MEN */

#if defined(RCC_TIM1CFGR_TIM1EN)
#define __HAL_RCC_TIM1_CLK_ENABLE()               SET_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1EN)
#endif /* RCC_TIM1CFGR_TIM1EN */

#if defined(RCC_TIM2CFGR_TIM2EN)
#define __HAL_RCC_TIM2_CLK_ENABLE()               SET_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2EN)
#endif /* RCC_TIM2CFGR_TIM2EN */

#if defined(RCC_TIM3CFGR_TIM3EN)
#define __HAL_RCC_TIM3_CLK_ENABLE()               SET_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3EN)
#endif /* RCC_TIM3CFGR_TIM3EN */

#if defined(RCC_TIM4CFGR_TIM4EN)
#define __HAL_RCC_TIM4_CLK_ENABLE()               SET_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4EN)
#endif /* RCC_TIM4CFGR_TIM4EN */

#if defined(RCC_TIM5CFGR_TIM5EN)
#define __HAL_RCC_TIM5_CLK_ENABLE()               SET_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5EN)
#endif /* RCC_TIM5CFGR_TIM5EN */

#if defined(RCC_TIM6CFGR_TIM6EN)
#define __HAL_RCC_TIM6_CLK_ENABLE()               SET_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6EN)
#endif /* RCC_TIM6CFGR_TIM6EN */

#if defined(RCC_TIM7CFGR_TIM7EN)
#define __HAL_RCC_TIM7_CLK_ENABLE()               SET_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7EN)
#endif /* RCC_TIM7CFGR_TIM7EN */

#if defined(RCC_TIM8CFGR_TIM8EN)
#define __HAL_RCC_TIM8_CLK_ENABLE()               SET_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8EN)
#endif /* RCC_TIM8CFGR_TIM8EN */

#if defined(RCC_TIM10CFGR_TIM10EN)
#define __HAL_RCC_TIM10_CLK_ENABLE()              SET_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10EN)
#endif /* RCC_TIM10CFGR_TIM10EN */

#if defined(RCC_TIM11CFGR_TIM11EN)
#define __HAL_RCC_TIM11_CLK_ENABLE()              SET_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11EN)
#endif /* RCC_TIM11CFGR_TIM11EN */

#if defined(RCC_TIM12CFGR_TIM12EN)
#define __HAL_RCC_TIM12_CLK_ENABLE()              SET_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12EN)
#endif /* RCC_TIM12CFGR_TIM12EN */

#if defined(RCC_TIM13CFGR_TIM13EN)
#define __HAL_RCC_TIM13_CLK_ENABLE()              SET_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13EN)
#endif /* RCC_TIM13CFGR_TIM13EN */

#if defined(RCC_TIM14CFGR_TIM14EN)
#define __HAL_RCC_TIM14_CLK_ENABLE()              SET_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14EN)
#endif /* RCC_TIM14CFGR_TIM14EN */

#if defined(RCC_TIM15CFGR_TIM15EN)
#define __HAL_RCC_TIM15_CLK_ENABLE()              SET_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15EN)
#endif /* RCC_TIM15CFGR_TIM15EN */

#if defined(RCC_TIM16CFGR_TIM16EN)
#define __HAL_RCC_TIM16_CLK_ENABLE()              SET_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16EN)
#endif /* RCC_TIM16CFGR_TIM16EN */

#if defined(RCC_TIM17CFGR_TIM17EN)
#define __HAL_RCC_TIM17_CLK_ENABLE()              SET_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17EN)
#endif /* RCC_TIM17CFGR_TIM17EN */

#if defined(RCC_TIM20CFGR_TIM20EN)
#define __HAL_RCC_TIM20_CLK_ENABLE()              SET_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20EN)
#endif /* RCC_TIM20CFGR_TIM20EN */

#define __HAL_RCC_LPTIM1_CLK_ENABLE()             SET_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1EN)
#define __HAL_RCC_LPTIM2_CLK_ENABLE()             SET_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2EN)
#define __HAL_RCC_LPTIM3_CLK_ENABLE()             SET_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3EN)
#define __HAL_RCC_LPTIM4_CLK_ENABLE()             SET_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4EN)
#define __HAL_RCC_LPTIM5_CLK_ENABLE()             SET_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5EN)
#define __HAL_RCC_SPI1_CLK_ENABLE()               SET_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1EN)
#define __HAL_RCC_SPI2_CLK_ENABLE()               SET_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2EN)
#define __HAL_RCC_SPI3_CLK_ENABLE()               SET_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3EN)
#define __HAL_RCC_SPI4_CLK_ENABLE()               SET_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4EN)
#define __HAL_RCC_SPI5_CLK_ENABLE()               SET_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5EN)
#define __HAL_RCC_SPI6_CLK_ENABLE()               SET_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6EN)

#if defined(RCC_SPI7CFGR_SPI7EN)
#define __HAL_RCC_SPI7_CLK_ENABLE()               SET_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7EN)
#endif /* RCC_SPI7CFGR_SPI7EN */

#if defined(RCC_SPI8CFGR_SPI8EN)
#define __HAL_RCC_SPI8_CLK_ENABLE()               SET_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8EN)
#endif /* RCC_SPI7CFGR_SPI8EN */

#define __HAL_RCC_SPDIFRX_CLK_ENABLE()            SET_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXEN)
#define __HAL_RCC_USART1_CLK_ENABLE()             SET_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1EN)
#define __HAL_RCC_USART2_CLK_ENABLE()             SET_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2EN)
#define __HAL_RCC_USART3_CLK_ENABLE()             SET_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3EN)
#define __HAL_RCC_UART4_CLK_ENABLE()              SET_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4EN)
#define __HAL_RCC_UART5_CLK_ENABLE()              SET_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5EN)
#define __HAL_RCC_USART6_CLK_ENABLE()             SET_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6EN)
#define __HAL_RCC_UART7_CLK_ENABLE()              SET_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7EN)

#if defined(RCC_UART8CFGR_UART8EN)
#define __HAL_RCC_UART8_CLK_ENABLE()              SET_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8EN)
#endif /* RCC_UART8CFGR_UART8EN  */

#if defined(RCC_UART9CFGR_UART9EN)
#define __HAL_RCC_UART9_CLK_ENABLE()              SET_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9EN)
#endif /*  RCC_UART9CFGR_UART9EN */

#define __HAL_RCC_LPUART1_CLK_ENABLE()            SET_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1EN)
#define __HAL_RCC_I2C1_CLK_ENABLE()               SET_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1EN)
#define __HAL_RCC_I2C2_CLK_ENABLE()               SET_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2EN)
#define __HAL_RCC_I2C3_CLK_ENABLE()               SET_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3EN)

#if defined(RCC_I2C4CFGR_I2C4EN)
#define __HAL_RCC_I2C4_CLK_ENABLE()               SET_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4EN)
#endif /*  RCC_I2C4CFGR_I2C4EN */

#if defined(RCC_I2C5CFGR_I2C5EN)
#define __HAL_RCC_I2C5_CLK_ENABLE()               SET_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5EN)
#endif /* RCC_I2C5CFGR_I2C5EN  */

#if defined(RCC_I2C6CFGR_I2C6EN)
#define __HAL_RCC_I2C6_CLK_ENABLE()               SET_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6EN)
#endif /* RCC_I2C6CFGR_I2C6EN  */

#if defined(RCC_I2C7CFGR_I2C7EN)
#define __HAL_RCC_I2C7_CLK_ENABLE()               SET_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7EN)
#endif /* RCC_I2C7CFGR_I2C7EN  */

#if defined(RCC_I2C8CFGR_I2C8EN)
#define __HAL_RCC_I2C8_CLK_ENABLE()               SET_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8EN)
#endif /* RCC_I2C8CFGR_I2C8EN  */

#define __HAL_RCC_SAI1_CLK_ENABLE()               SET_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1EN)
#define __HAL_RCC_SAI2_CLK_ENABLE()               SET_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2EN)
#define __HAL_RCC_SAI3_CLK_ENABLE()               SET_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3EN)
#define __HAL_RCC_SAI4_CLK_ENABLE()               SET_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4EN)
#define __HAL_RCC_MDF1_CLK_ENABLE()               SET_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1EN)
#define __HAL_RCC_ADF1_CLK_ENABLE()               SET_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1EN)
#define __HAL_RCC_FDCAN_CLK_ENABLE()              SET_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANEN)
#define __HAL_RCC_HDP_CLK_ENABLE()                SET_BIT(RCC->HDPCFGR, RCC_HDPCFGR_HDPEN)

#if defined(RCC_ADC1CFGR_ADC1EN)
#define __HAL_RCC_ADC1_CLK_ENABLE()               SET_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1EN)
#endif /* RCC_ADC1CFGR_ADC1EN */

#if defined(RCC_ADC2CFGR_ADC2EN)
#define __HAL_RCC_ADC2_CLK_ENABLE()               SET_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2EN)
#endif /* RCC_ADC12CFGR_ADC3EN */

#if defined(RCC_ADC12CFGR_ADC12EN)
#define __HAL_RCC_ADC12_CLK_ENABLE()              SET_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12EN)
#endif /* RCC_ADC12CFGR_ADC12EN */

#if defined(RCC_ADC3CFGR_ADC3EN)
#define __HAL_RCC_ADC3_CLK_ENABLE()               SET_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3EN)
#endif /* RCC_ADC3CFGR_ADC3EN */

#define __HAL_RCC_ETH1_CLK_ENABLE()               SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1EN)
#define __HAL_RCC_ETH1MAC_CLK_ENABLE()            SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1MACEN)
#define __HAL_RCC_ETH1TX_CLK_ENABLE()             SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1TXEN)
#define __HAL_RCC_ETH1RX_CLK_ENABLE()             SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1RXEN)
#define __HAL_RCC_ETH2_CLK_ENABLE()               SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2EN)
#define __HAL_RCC_ETH2MAC_CLK_ENABLE()            SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2MACEN)
#define __HAL_RCC_ETH2TX_CLK_ENABLE()             SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2TXEN)
#define __HAL_RCC_ETH2RX_CLK_ENABLE()             SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2RXEN)


#if defined(RCC_USBHCFGR_USBHEN)
#define __HAL_RCC_USBH_CLK_ENABLE()               SET_BIT(RCC->USBHCFGR, RCC_USBHCFGR_USBHEN)
#endif /* RCC_USBHCFGR_USBHEN */

#define __HAL_RCC_USB2PHY1_CLK_ENABLE()           SET_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1EN)
#define __HAL_RCC_USB2PHY2_CLK_ENABLE()           SET_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2EN)

#if defined(RCC_OTGCFGR_OTGEN)
#define __HAL_RCC_OTG_CLK_ENABLE()                SET_BIT(RCC->OTGCFGR, RCC_OTGCFGR_OTGEN)
#endif /* RCC_OTGCFGR_OTGEN */

#if defined(RCC_USB3DRDCFGR_USB3DRDEN)
#define __HAL_RCC_USB3DRD_CLK_ENABLE()            SET_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDEN)
#endif /* RCC_USB3DRDCFGR_USB3DRDEN */

#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN)
#define __HAL_RCC_USB3PCIEPHY_CLK_ENABLE()        SET_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN)
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN */

#if defined(RCC_PCIECFGR_PCIEEN)
#define __HAL_RCC_PCIE_CLK_ENABLE()               SET_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIEEN)
#endif /* RCC_PCIECFGR_PCIEEN */

#if defined(RCC_UCPDCFGR_UCPDEN)
#define __HAL_RCC_UCPD1_CLK_ENABLE()              SET_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDEN)
#endif /* RCC_UCPDCFGR_UCPDEN */

#define __HAL_RCC_FMC_CLK_ENABLE()                SET_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCEN)
#define __HAL_RCC_SDMMC1_CLK_ENABLE()             SET_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1EN)
#define __HAL_RCC_SDMMC2_CLK_ENABLE()             SET_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2EN)
#define __HAL_RCC_SDMMC3_CLK_ENABLE()             SET_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3EN)
#define __HAL_RCC_GPU_CLK_ENABLE()                SET_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPUEN)
#define __HAL_RCC_LTDC_CLK_ENABLE()               SET_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCEN)

#if defined(RCC_DSICFGR_DSIEN)
#define __HAL_RCC_DSI_CLK_ENABLE()                SET_BIT(RCC->DSICFGR, RCC_DSICFGR_DSIEN)
#endif /* RCC_DSICFGR_DSIEN */

#define __HAL_RCC_LVDS_CLK_ENABLE()               SET_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSEN)

#if defined(RCC_CSICFGR_CSIEN)
#define __HAL_RCC_CSI_CLK_ENABLE()                SET_BIT(RCC->CSICFGR, RCC_CSICFGR_CSIEN)
#endif /* RCC_CSICFGR_CSIEN */

#if defined(RCC_CSI2CFGR_CSI2EN)
#define __HAL_RCC_CSI2_CLK_ENABLE()               SET_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2EN)
#endif /* RCC_CSI2CFGR_CSI2EN */

#define __HAL_RCC_DCMIPP_CLK_ENABLE()             SET_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPEN)

#if defined(RCC_DCMIPSSICFGR_DCMIPSSIEN)
#define __HAL_RCC_DCMIPSSI_CLK_ENABLE()           SET_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSIEN)
#endif /* RCC_DCMIPSSICFGR_DCMIPSSIEN */

#if defined(RCC_CCICFGR_CCIEN)
#define __HAL_RCC_CCI_CLK_ENABLE()                SET_BIT(RCC->CCICFGR, RCC_CCICFGR_CCIEN)
#endif /* RCC_CCICFGR_CCIEN */

#if defined(RCC_RNGCFGR_RNGEN)
#define __HAL_RCC_RNG_CLK_ENABLE()                SET_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGEN)
#endif /* RCC_RNGCFGR_RNGEN */

#if defined(RCC_RNG1CFGR_RNG1EN)
#define __HAL_RCC_RNG1_CLK_ENABLE()               SET_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1EN)
#endif /* RCC_RNG1CFGR_RNG1EN */

#if defined(RCC_RNG2CFGR_RNG2EN)
#define __HAL_RCC_RNG2_CLK_ENABLE()               SET_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2EN)
#endif /* RCC_RNG2CFGR_RNG2EN */

#define __HAL_RCC_PKA_CLK_ENABLE()                SET_BIT(RCC->PKACFGR, RCC_PKACFGR_PKAEN)
#define __HAL_RCC_SAES_CLK_ENABLE()               SET_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESEN)

#if defined(RCC_HASHCFGR_HASHEN)
#define __HAL_RCC_HASH_CLK_ENABLE()               SET_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHEN)
#endif /* RCC_HASHCFGR_HASHEN */

#if defined(RCC_HASH1CFGR_HASH1EN)
#define __HAL_RCC_HASH1_CLK_ENABLE()              SET_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1EN)
#endif /* RCC_HASH1CFGR_HASH1EN */

#if defined (RCC_HASH2CFGR_HASH2EN)
#define __HAL_RCC_HASH2_CLK_ENABLE()              SET_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2EN)
#endif /* RCC_HASH2CFGR_HASH2EN */

#define __HAL_RCC_CRYP1_CLK_ENABLE()              SET_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1EN)
#define __HAL_RCC_CRYP2_CLK_ENABLE()              SET_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2EN)
#define __HAL_RCC_IWDG1_CLK_ENABLE()              SET_BIT(RCC->IWDG1CFGR, RCC_IWDG1CFGR_IWDG1EN)
#define __HAL_RCC_IWDG2_CLK_ENABLE()              SET_BIT(RCC->IWDG2CFGR, RCC_IWDG2CFGR_IWDG2EN)
#define __HAL_RCC_IWDG3_CLK_ENABLE()              SET_BIT(RCC->IWDG3CFGR, RCC_IWDG3CFGR_IWDG3EN)
#define __HAL_RCC_IWDG4_CLK_ENABLE()              SET_BIT(RCC->IWDG4CFGR, RCC_IWDG4CFGR_IWDG4EN)

#if defined(RCC_IWDG5CFGR_IWDG5EN)
#define __HAL_RCC_IWDG5_CLK_ENABLE()              SET_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5EN)
#endif /* RCC_IWDG5CFGR_IWDG5EN */

#define __HAL_RCC_WWDG1_CLK_ENABLE()              SET_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1EN)

#if defined(RCC_WWDG2CFGR_WWDG2EN)
#define __HAL_RCC_WWDG2_CLK_ENABLE()              SET_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2EN)
#endif /* RCC_WWDG2CFGR_WWDG2EN */

#if defined(RCC_BUSPERFMCFGR_BUSPERFMEN)
#define __HAL_RCC_BUSPERFM_CLK_ENABLE()           SET_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMEN)
#endif /* RCC_BUSPERFMCFGR_BUSPERFMEN */

#define __HAL_RCC_VREF_CLK_ENABLE()               SET_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFEN)

#if defined (RCC_TMPSENSCFGR_TMPSENSEN)
#define __HAL_RCC_TMPSENS_CLK_ENABLE()            SET_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSEN)
#endif /* RCC_TMPSENSCFGR_TMPSENSEN */

#define __HAL_RCC_CRC_CLK_ENABLE()                SET_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCEN)
#define __HAL_RCC_BSEC_CLK_ENABLE()               SET_BIT(RCC->BSECCFGR, RCC_BSECCFGR_BSECEN)

#if defined(RCC_GICV2MCFGR_GICV2MEN)
#define __HAL_RCC_GICV2M_CLK_ENABLE()             SET_BIT(RCC->GICV2MCFGR, RCC_GICV2MCFGR_GICV2MEN)
#endif /* RCC_GICV2MCFGR_GICV2MEN */

#define __HAL_RCC_I3C1_CLK_ENABLE()               SET_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1EN)
#define __HAL_RCC_I3C2_CLK_ENABLE()               SET_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2EN)
#define __HAL_RCC_I3C3_CLK_ENABLE()               SET_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3EN)

#if defined(RCC_I3C4CFGR_I3C4EN)
#define __HAL_RCC_I3C4_CLK_ENABLE()               SET_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4EN)
#endif /* RCC_I3C4CFGR_I3C4EN */

#define __HAL_RCC_HSE_KER_CLK_ENABLE()            SET_BIT(RCC->OCENSETR, RCC_OCENSETR_HSEKERON)
#define __HAL_RCC_HSI_KER_CLK_ENABLE()            SET_BIT(RCC->OCENSETR, RCC_OCENSETR_HSIKERON)

#if defined(RCC_D3DCR_MSIKERON)
#define __HAL_RCC_MSI_KER_CLK_ENABLE()            SET_BIT(RCC->D3DCR, RCC_D3DCR_MSIKERON)
#elif defined(RCC_OCENCLRR_MSIKERON)
#define __HAL_RCC_MSI_KER_CLK_ENABLE()            SET_BIT(RCC->OCENSETR, RCC_OCENCLRR_MSIKERON)
#endif /* RCC_OCENCLRR_MSIKERON */

/* for API backward compatibility */
#if defined(RCC_DCMIPSSICFGR_DCMIPSSIEN)
#define __HAL_RCC_DCMI_CLK_ENABLE()               __HAL_RCC_DCMIPSSI_CLK_ENABLE()
#define __HAL_RCC_PSSI_CLK_ENABLE()               __HAL_RCC_DCMIPSSI_CLK_ENABLE()
#endif /* (RCC_DCMIPSSICFGR_DCMIPSSIEN) */

#if defined(RCC_CCICFGR_CCIEN)
#define __HAL_RCC_DCMI_CLK_ENABLE()               __HAL_RCC_CCI_CLK_ENABLE()
#define __HAL_RCC_PSSI_CLK_ENABLE()               __HAL_RCC_CCI_CLK_ENABLE()
#endif /* RCC_CCICFGR_CCIEN */

#if defined(RCC_OSPI1CFGR_OSPI1EN)
#define __HAL_RCC_OTFDEC1_CLK_ENABLE()            __HAL_RCC_OSPI1_CLK_ENABLE()
#endif /* RCC_OSPI1CFGR_OSPI1EN */

#if defined(RCC_OSPI2CFGR_OSPI2EN)
#define __HAL_RCC_OTFDEC2_CLK_ENABLE()            __HAL_RCC_OSPI2_CLK_ENABLE()
#endif /* RCC_OSPI2CFGR_OSPI2EN */

/* Clock disable macros */
#if defined(RCC_VDERAMCFGR_VDERAMEN)
#define __HAL_RCC_VDERAM_CLK_DISABLE()            CLEAR_BIT(RCC->VDERAMCFGR, RCC_VDERAMCFGR_VDERAMEN)
#endif /* RCC_VDERAMCFGR_VDERAMEN */

#define __HAL_RCC_SERC_CLK_DISABLE()              CLEAR_BIT(RCC->SERCCFGR, RCC_SERCCFGR_SERCEN)
#define __HAL_RCC_OSPIIOM_CLK_DISABLE()           CLEAR_BIT(RCC->OSPIIOMCFGR, RCC_OSPIIOMCFGR_OSPIIOMEN)
#define __HAL_RCC_ETHSW_CLK_DISABLE()             CLEAR_BIT(RCC->ETHSWCFGR, RCC_ETHSWCFGR_ETHSWMACEN|\
                                                            RCC_ETHSWCFGR_ETHSWEN|RCC_ETHSWCFGR_ETHSWREFEN)
#define __HAL_RCC_VDEC_CLK_DISABLE()              CLEAR_BIT(RCC->VDECCFGR, RCC_VDECCFGR_VDECEN)

#if defined(RCC_VENCCFGR_VENCEN)
#define __HAL_RCC_VENC_CLK_DISABLE()              CLEAR_BIT(RCC->VENCCFGR, RCC_VENCCFGR_VENCEN)
#endif /* RCC_VENCCFGR_VENCEN */

#if defined(RCC_C3CFGR_C3EN)
#define __HAL_RCC_C3_CLK_DISABLE()                CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_C3EN)
#endif /* RCC_C3CFGR_C3EN */

#define __HAL_RCC_SYSRAM_CLK_DISABLE()            CLEAR_BIT(RCC->SYSRAMCFGR, RCC_SYSRAMCFGR_SYSRAMEN)
#define __HAL_RCC_SRAM1_CLK_DISABLE()             CLEAR_BIT(RCC->SRAM1CFGR, RCC_SRAM1CFGR_SRAM1EN)

#if defined(RCC_SRAM2CFGR_SRAM2EN)
#define __HAL_RCC_SRAM2_CLK_DISABLE()             CLEAR_BIT(RCC->SRAM2CFGR, RCC_SRAM2CFGR_SRAM2EN)
#endif /* RCC_SRAM2CFGR_SRAM2EN */

#define __HAL_RCC_RETRAM_CLK_DISABLE()            CLEAR_BIT(RCC->RETRAMCFGR, RCC_RETRAMCFGR_RETRAMEN)
#define __HAL_RCC_BKPSRAM_CLK_DISABLE()           CLEAR_BIT(RCC->BKPSRAMCFGR, RCC_BKPSRAMCFGR_BKPSRAMEN)

#if defined(RCC_LPSRAM1CFGR_LPSRAM1EN)
#define __HAL_RCC_LPSRAM1_CLK_DISABLE()           CLEAR_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1EN)
#endif /* RCC_LPSRAM1CFGR_LPSRAM1EN */

#if defined(RCC_LPSRAM2CFGR_LPSRAM2EN)
#define __HAL_RCC_LPSRAM2_CLK_DISABLE()           CLEAR_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2EN)
#endif /* RCC_LPSRAM2CFGR_LPSRAM2EN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3EN)
#define __HAL_RCC_LPSRAM3_CLK_DISABLE()           CLEAR_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3EN)
#endif /* RCC_LPSRAM3CFGR_LPSRAM3EN */

#define __HAL_RCC_OSPI1_CLK_DISABLE()             CLEAR_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1EN)

#if defined(RCC_OSPI2CFGR_OSPI2EN)
#define __HAL_RCC_OSPI2_CLK_DISABLE()             CLEAR_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2EN)
#endif /* RCC_OSPI2CFGR_OSPI2EN */

#if defined(RCC_STMCFGR_STMEN)
#define __HAL_RCC_STM_CLK_DISABLE()            CLEAR_BIT(RCC->STMCFGR, RCC_STMCFGR_STMEN)
#endif /* RCC_STMCFGR_STMEN */

#define __HAL_RCC_ETR_CLK_DISABLE()               CLEAR_BIT(RCC->ETRCFGR, RCC_ETRCFGR_ETREN)
#define __HAL_RCC_GPIOA_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxEN)
#define __HAL_RCC_GPIOB_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxEN)
#define __HAL_RCC_GPIOC_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxEN)
#define __HAL_RCC_GPIOD_CLK_DISABLE()             CLEAR_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxEN)
#define __HAL_RCC_GPIOE_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxEN)
#define __HAL_RCC_GPIOF_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxEN)
#define __HAL_RCC_GPIOG_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxEN)
#define __HAL_RCC_GPIOH_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxEN)
#define __HAL_RCC_GPIOI_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxEN)

#if defined(RCC_GPIOJCFGR_GPIOxEN)
#define __HAL_RCC_GPIOJ_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxEN)
#endif /* RCC_GPIOJCFGR_GPIOxEN */

#if defined(RCC_GPIOKCFGR_GPIOxEN)
#define __HAL_RCC_GPIOK_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxEN)
#endif /* RCC_GPIOKCFGR_GPIOxEN */

#define __HAL_RCC_GPIOZ_CLK_DISABLE()             CLEAR_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZEN)
#define __HAL_RCC_HPDMA1_CLK_DISABLE()            CLEAR_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1EN)
#define __HAL_RCC_HPDMA2_CLK_DISABLE()            CLEAR_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2EN)
#define __HAL_RCC_HPDMA3_CLK_DISABLE()            CLEAR_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3EN)

#if defined(RCC_LPDMACFGR_LPDMAEN)
#define __HAL_RCC_LPDMA_CLK_DISABLE()             CLEAR_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMAEN)
#endif /* RCC_LPDMACFGR_LPDMAEN */

#if defined(RCC_HSEMCFGR_HSEMEN)
#define __HAL_RCC_HSEM_CLK_DISABLE()              CLEAR_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMEN)
#endif /* RCC_HSEMCFGR_HSEMEN */

#define __HAL_RCC_IPCC1_CLK_DISABLE()             CLEAR_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1EN)

#if defined(RCC_IPCC2CFGR_IPCC2EN)
#define __HAL_RCC_IPCC2_CLK_DISABLE()             CLEAR_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2EN)
#endif /* RCC_IPCC2CFGR_IPCC2EN */

#define __HAL_RCC_RTC_CLK_DISABLE()               CLEAR_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCEN)
#define __HAL_RCC_SYSCPU1_CLK_DISABLE()           CLEAR_BIT(RCC->SYSCPU1CFGR, RCC_SYSCPU1CFGR_SYSCPU1EN)
#define __HAL_RCC_IS2M_CLK_DISABLE()              CLEAR_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MEN)
#define __HAL_RCC_TIM1_CLK_DISABLE()              CLEAR_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1EN)
#define __HAL_RCC_TIM2_CLK_DISABLE()              CLEAR_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2EN)
#define __HAL_RCC_TIM3_CLK_DISABLE()              CLEAR_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3EN)
#define __HAL_RCC_TIM4_CLK_DISABLE()              CLEAR_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4EN)
#define __HAL_RCC_TIM5_CLK_DISABLE()              CLEAR_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5EN)
#define __HAL_RCC_TIM6_CLK_DISABLE()              CLEAR_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6EN)
#define __HAL_RCC_TIM7_CLK_DISABLE()              CLEAR_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7EN)
#define __HAL_RCC_TIM8_CLK_DISABLE()              CLEAR_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8EN)
#define __HAL_RCC_TIM10_CLK_DISABLE()             CLEAR_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10EN)
#define __HAL_RCC_TIM11_CLK_DISABLE()             CLEAR_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11EN)
#define __HAL_RCC_TIM12_CLK_DISABLE()             CLEAR_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12EN)
#define __HAL_RCC_TIM13_CLK_DISABLE()             CLEAR_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13EN)
#define __HAL_RCC_TIM14_CLK_DISABLE()             CLEAR_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14EN)
#define __HAL_RCC_TIM15_CLK_DISABLE()             CLEAR_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15EN)
#define __HAL_RCC_TIM16_CLK_DISABLE()             CLEAR_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16EN)
#define __HAL_RCC_TIM17_CLK_DISABLE()             CLEAR_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17EN)

#if defined(RCC_TIM20CFGR_TIM20EN)
#define __HAL_RCC_TIM20_CLK_DISABLE()             CLEAR_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20EN)
#endif /* RCC_TIM20CFGR_TIM20EN */

#define __HAL_RCC_LPTIM1_CLK_DISABLE()            CLEAR_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1EN)
#define __HAL_RCC_LPTIM2_CLK_DISABLE()            CLEAR_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2EN)
#define __HAL_RCC_LPTIM3_CLK_DISABLE()            CLEAR_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3EN)
#define __HAL_RCC_LPTIM4_CLK_DISABLE()            CLEAR_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4EN)
#define __HAL_RCC_LPTIM5_CLK_DISABLE()            CLEAR_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5EN)
#define __HAL_RCC_SPI1_CLK_DISABLE()              CLEAR_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1EN)
#define __HAL_RCC_SPI2_CLK_DISABLE()              CLEAR_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2EN)
#define __HAL_RCC_SPI3_CLK_DISABLE()              CLEAR_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3EN)
#define __HAL_RCC_SPI4_CLK_DISABLE()              CLEAR_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4EN)
#define __HAL_RCC_SPI5_CLK_DISABLE()              CLEAR_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5EN)
#define __HAL_RCC_SPI6_CLK_DISABLE()              CLEAR_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6EN)

#if defined(RCC_SPI7CFGR_SPI7EN)
#define __HAL_RCC_SPI7_CLK_DISABLE()              CLEAR_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7EN)
#endif /* RCC_SPI7CFGR_SPI7EN */

#if defined(RCC_SPI8CFGR_SPI8EN)
#define __HAL_RCC_SPI8_CLK_DISABLE()              CLEAR_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8EN)
#endif /* RCC_SPI8CFGR_SPI8EN */

#define __HAL_RCC_SPDIFRX_CLK_DISABLE()           CLEAR_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXEN)
#define __HAL_RCC_USART1_CLK_DISABLE()            CLEAR_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1EN)
#define __HAL_RCC_USART2_CLK_DISABLE()            CLEAR_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2EN)
#define __HAL_RCC_USART3_CLK_DISABLE()            CLEAR_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3EN)
#define __HAL_RCC_UART4_CLK_DISABLE()             CLEAR_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4EN)
#define __HAL_RCC_UART5_CLK_DISABLE()             CLEAR_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5EN)
#define __HAL_RCC_USART6_CLK_DISABLE()            CLEAR_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6EN)
#define __HAL_RCC_UART7_CLK_DISABLE()             CLEAR_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7EN)

#if defined(RCC_UART8CFGR_UART8EN)
#define __HAL_RCC_UART8_CLK_DISABLE()             CLEAR_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8EN)
#endif /* RCC_UART8CFGR_UART8EN */

#if defined(RCC_UART9CFGR_UART9EN)
#define __HAL_RCC_UART9_CLK_DISABLE()             CLEAR_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9EN)
#endif /* RCC_UART9CFGR_UART9EN */

#define __HAL_RCC_LPUART1_CLK_DISABLE()           CLEAR_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1EN)
#define __HAL_RCC_I2C1_CLK_DISABLE()              CLEAR_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1EN)
#define __HAL_RCC_I2C2_CLK_DISABLE()              CLEAR_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2EN)
#define __HAL_RCC_I2C3_CLK_DISABLE()              CLEAR_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3EN)

#if defined(RCC_I2C4CFGR_I2C4EN)
#define __HAL_RCC_I2C4_CLK_DISABLE()              CLEAR_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4EN)
#endif /* RCC_I2C4CFGR_I2C4EN */

#if defined(RCC_I2C5CFGR_I2C5EN)
#define __HAL_RCC_I2C5_CLK_DISABLE()              CLEAR_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5EN)
#endif /* RCC_I2C5CFGR_I2C5EN */

#if defined(RCC_I2C6CFGR_I2C6EN)
#define __HAL_RCC_I2C6_CLK_DISABLE()              CLEAR_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6EN)
#endif /* RCC_I2C6CFGR_I2C6EN */

#if defined(RCC_I2C7CFGR_I2C7EN)
#define __HAL_RCC_I2C7_CLK_DISABLE()              CLEAR_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7EN)
#endif /* RCC_I2C7CFGR_I2C7EN */

#if defined(RCC_I2C8CFGR_I2C8EN)
#define __HAL_RCC_I2C8_CLK_DISABLE()              CLEAR_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8EN)
#endif /* RCC_I2C8CFGR_I2C8EN */

#define __HAL_RCC_SAI1_CLK_DISABLE()              CLEAR_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1EN)
#define __HAL_RCC_SAI2_CLK_DISABLE()              CLEAR_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2EN)
#define __HAL_RCC_SAI3_CLK_DISABLE()              CLEAR_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3EN)
#define __HAL_RCC_SAI4_CLK_DISABLE()              CLEAR_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4EN)
#define __HAL_RCC_MDF1_CLK_DISABLE()              CLEAR_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1EN)
#define __HAL_RCC_ADF1_CLK_DISABLE()              CLEAR_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1EN)
#define __HAL_RCC_FDCAN_CLK_DISABLE()             CLEAR_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANEN)
#define __HAL_RCC_HDP_CLK_DISABLE()               CLEAR_BIT(RCC->HDPCFGR, RCC_HDPCFGR_HDPEN)

#if defined(RCC_ADC1CFGR_ADC1EN)
#define __HAL_RCC_ADC1_CLK_DISABLE()              CLEAR_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1EN)
#endif /*  RCC_ADC1CFGR_ADC1EN */

#if defined(RCC_ADC2CFGR_ADC2EN)
#define __HAL_RCC_ADC2_CLK_DISABLE()              CLEAR_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2EN)
#endif /*  RCC_ADC2CFGR_ADC2EN */

#if defined(RCC_ADC12CFGR_ADC12EN)
#define __HAL_RCC_ADC12_CLK_DISABLE()             CLEAR_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12EN)
#endif /*  RCC_ADC12CFGR_ADC12EN */

#if defined(RCC_ADC3CFGR_ADC3EN)
#define __HAL_RCC_ADC3_CLK_DISABLE()              CLEAR_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3EN)
#endif /* RCC_ADC3CFGR_ADC3EN */

#define __HAL_RCC_ETH1_CLK_DISABLE()              CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1EN)
#define __HAL_RCC_ETH1MAC_CLK_DISABLE()           CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1MACEN)
#define __HAL_RCC_ETH1TX_CLK_DISABLE()            CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1TXEN)
#define __HAL_RCC_ETH1RX_CLK_DISABLE()            CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1RXEN)
#define __HAL_RCC_ETH2_CLK_DISABLE()              CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2EN)
#define __HAL_RCC_ETH2MAC_CLK_DISABLE()           CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2MACEN)
#define __HAL_RCC_ETH2TX_CLK_DISABLE()            CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2TXEN)
#define __HAL_RCC_ETH2RX_CLK_DISABLE()            CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2RXEN)

#if defined(RCC_USBHCFGR_USBHEN)
#define __HAL_RCC_USBH_CLK_DISABLE()              CLEAR_BIT(RCC->USBHCFGR, RCC_USBHCFGR_USB2EN)
#endif /* RCC_USBHCFGR_USBHEN */

#define __HAL_RCC_USB2PHY1_CLK_DISABLE()          CLEAR_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1EN)
#define __HAL_RCC_USB2PHY2_CLK_DISABLE()          CLEAR_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2EN)

#if defined(RCC_OTGCFGR_OTGEN)
#define __HAL_RCC_OTG_CLK_DISABLE()               CLEAR_BIT(RCC->OTGCFGR, RCC_OTGCFGR_OTGEN)
#endif /* RCC_OTGCFGR_OTGEN */

#if defined(RCC_USB3DRDCFGR_USB3DRDEN)
#define __HAL_RCC_USB3DRD_CLK_DISABLE()           CLEAR_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDEN)
#endif /* RCC_USB3DRDCFGR_USB3DRDEN */

#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN)
#define __HAL_RCC_USB3PCIEPHY_CLK_DISABLE()       CLEAR_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN)
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN */

#if defined(RCC_PCIECFGR_PCIEEN)
#define __HAL_RCC_PCIE_CLK_DISABLE()              CLEAR_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIEEN)
#endif /* RCC_PCIECFGR_PCIEEN */

#if defined(RCC_UCPDCFGR_UCPDEN)
#define __HAL_RCC_UCPD1_CLK_DISABLE()             CLEAR_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDEN)
#endif /* RCC_UCPDCFGR_UCPDEN */

#define __HAL_RCC_FMC_CLK_DISABLE()               CLEAR_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCEN)
#define __HAL_RCC_SDMMC1_CLK_DISABLE()            CLEAR_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1EN)
#define __HAL_RCC_SDMMC2_CLK_DISABLE()            CLEAR_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2EN)
#define __HAL_RCC_SDMMC3_CLK_DISABLE()            CLEAR_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3EN)
#define __HAL_RCC_GPU_CLK_DISABLE()               CLEAR_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPUEN)
#define __HAL_RCC_LTDC_CLK_DISABLE()              CLEAR_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCEN)

#if defined(RCC_DSICFGR_DSIEN)
#define __HAL_RCC_DSI_CLK_DISABLE()               CLEAR_BIT(RCC->DSICFGR, RCC_DSICFGR_DSIEN)
#endif /* RCC_DSICFGR_DSIEN */

#define __HAL_RCC_LVDS_CLK_DISABLE()              CLEAR_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSEN)
#define __HAL_RCC_CSI2_CLK_DISABLE()              CLEAR_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2EN)
#define __HAL_RCC_DCMIPP_CLK_DISABLE()            CLEAR_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPEN)

#if defined(RCC_DCMIPSSICFGR_DCMIPSSIEN)
#define __HAL_RCC_DCMIPSSI_CLK_DISABLE()          CLEAR_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSIEN)
#endif /* RCC_DCMIPSSICFGR_DCMIPSSIEN */

#if defined(RCC_CCICFGR_CCIEN)
#define __HAL_RCC_CCI_CLK_DISABLE()               CLEAR_BIT(RCC->CCICFGR, RCC_CCICFGR_CCIEN)
#endif /* RCC_CCICFGR_CCIEN */

#if defined(RCC_RNGCFGR_RNGEN)
#define __HAL_RCC_RNG_CLK_DISABLE()               CLEAR_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGEN)
#endif /* RCC_RNGCFGR_RNGEN */


#if defined(RCC_RNG1CFGR_RNG1EN)
#define __HAL_RCC_RNG1_CLK_DISABLE()              CLEAR_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1EN)
#endif /* RCC_RNG1CFGR_RNG1EN */

#if defined(RCC_RNG2CFGR_RNG2EN)
#define __HAL_RCC_RNG2_CLK_DISABLE()              CLEAR_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2EN)
#endif /* RCC_RNG2CFGR_RNG2EN */

#define __HAL_RCC_PKA_CLK_DISABLE()               CLEAR_BIT(RCC->PKACFGR, RCC_PKACFGR_PKAEN)
#define __HAL_RCC_SAES_CLK_DISABLE()              CLEAR_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESEN)

#if defined(RCC_HASHCFGR_HASHEN)
#define __HAL_RCC_HASH_CLK_DISABLE()              CLEAR_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHEN)
#endif /* RCC_HASHCFGR_HASHEN */

#if defined(RCC_HASH1CFGR_HASH1EN)
#define __HAL_RCC_HASH1_CLK_DISABLE()             CLEAR_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1EN)
#endif /* RCC_HASH1CFGR_HASH1EN */

#if defined (RCC_HASH2CFGR_HASH2EN)
#define __HAL_RCC_HASH2_CLK_DISABLE()             CLEAR_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2EN)
#endif /* RCC_HASH2CFGR_HASH2EN */

#define __HAL_RCC_CRYP1_CLK_DISABLE()             CLEAR_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1EN)
#define __HAL_RCC_CRYP2_CLK_DISABLE()             CLEAR_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2EN)
#define __HAL_RCC_IWDG1_CLK_DISABLE()             CLEAR_BIT(RCC->IWDG1CFGR, RCC_IWDG1CFGR_IWDG1EN)
#define __HAL_RCC_IWDG2_CLK_DISABLE()             CLEAR_BIT(RCC->IWDG2CFGR, RCC_IWDG2CFGR_IWDG2EN)
#define __HAL_RCC_IWDG3_CLK_DISABLE()             CLEAR_BIT(RCC->IWDG3CFGR, RCC_IWDG3CFGR_IWDG3EN)
#define __HAL_RCC_IWDG4_CLK_DISABLE()             CLEAR_BIT(RCC->IWDG4CFGR, RCC_IWDG4CFGR_IWDG4EN)

#if defined(RCC_IWDG5CFGR_IWDG5EN)
#define __HAL_RCC_IWDG5_CLK_DISABLE()             CLEAR_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5EN)
#endif /* RCC_IWDG5CFGR_IWDG5EN */

#define __HAL_RCC_WWDG1_CLK_DISABLE()             CLEAR_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1EN)

#if defined(RCC_WWDG2CFGR_WWDG2EN)
#define __HAL_RCC_WWDG2_CLK_DISABLE()             CLEAR_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2EN)
#endif /* RCC_WWDG2CFGR_WWDG2EN */

#define __HAL_RCC_BUSPERFM_CLK_DISABLE()          CLEAR_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMEN)
#define __HAL_RCC_VREF_CLK_DISABLE()              CLEAR_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFEN)

#if defined(RCC_TMPSENSCFGR_TMPSENSEN)
#define __HAL_RCC_TMPSENS_CLK_DISABLE()           CLEAR_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSEN)
#endif /* RCC_TMPSENSCFGR_TMPSENSEN */

#define __HAL_RCC_CRC_CLK_DISABLE()               CLEAR_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCEN)
#define __HAL_RCC_BSEC_CLK_DISABLE()              CLEAR_BIT(RCC->BSECCFGR, RCC_BSECCFGR_BSECEN)

#if defined(RCC_GICV2MCFGR_GICV2MEN)
#define __HAL_RCC_GICV2M_CLK_DISABLE()            CLEAR_BIT(RCC->GICV2MCFGR, RCC_GICV2MCFGR_GICV2MEN)
#endif /* RCC_GICV2MCFGR_GICV2MEN*/

#define __HAL_RCC_I3C1_CLK_DISABLE()              CLEAR_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1EN)
#define __HAL_RCC_I3C2_CLK_DISABLE()              CLEAR_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2EN)
#define __HAL_RCC_I3C3_CLK_DISABLE()              CLEAR_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3EN)

#if defined(RCC_I3C4CFGR_I3C4EN)
#define __HAL_RCC_I3C4_CLK_DISABLE()              CLEAR_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4EN)
#endif /* RCC_I3C4CFGR_I3C4EN */

#define __HAL_RCC_HSE_KER_CLK_DISABLE()           SET_BIT(RCC->OCENCLRR, RCC_OCENSETR_HSEKERON)
#define __HAL_RCC_HSI_KER_CLK_DISABLE()           SET_BIT(RCC->OCENCLKR, RCC_OCENSETR_HSIKERON)

#if defined(RCC_D3DCR_MSIKERON)
#define __HAL_RCC_MSI_KER_CLK_DISABLE()           CLEAR_BIT(RCC->D3DCR, RCC_D3DCR_MSIKERON)
#endif /* RCC_D3DCR_MSIKERON */

/* for API backward compatibility */
#if defined(RCC_DCMIPSSICFGR_DCMIPSSIEN)
#define __HAL_RCC_DCMI_CLK_DISABLE()              __HAL_RCC_DCMIPSSI_CLK_DISABLE()
#define __HAL_RCC_PSSI_CLK_DISABLE()              __HAL_RCC_DCMIPSSI_CLK_DISABLE()
#endif /* (RCC_DCMIPSSICFGR_DCMIPSSIEN) */

#if defined(RCC_CCICFGR_CCIEN)
#define __HAL_RCC_DCMI_CLK_DISABLE()              __HAL_RCC_CCI_CLK_DISABLE()
#define __HAL_RCC_PSSI_CLK_DISABLE()              __HAL_RCC_CCI_CLK_DISABLE()
#endif /* RCC_CCICFGR_CCIEN */

#if defined(RCC_OSPI1CFGR_OSPI1EN)
#define __HAL_RCC_OTFDEC1_CLK_DISABLE()           __HAL_RCC_OSPI1_CLK_DISABLE()
#endif /* RCC_OSPI1CFGR_OSPI1EN */

#if defined(RCC_OSPI2CFGR_OSPI2EN)
#define __HAL_RCC_OTFDEC2_CLK_DISABLE()           __HAL_RCC_OSPI2_CLK_DISABLE()
#endif /* RCC_OSPI2CFGR_OSPI2EN */

/* Clock sleep enable macros */
#if defined(RCC_VDERAMCFGR_VDERAMLPEN)
#define __HAL_RCC_VDERAM_CLK_SLEEP_ENABLE()       SET_BIT(RCC->VDERAMCFGR, RCC_VDERAMCFGR_VDERAMLPEN)
#endif /* RCC_VDERAMCFGR_VDERAMLPEN */

#define __HAL_RCC_SERC_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SERCCFGR, RCC_SERCCFGR_SERCLPEN)
#define __HAL_RCC_OSPIIOM_CLK_SLEEP_ENABLE()      SET_BIT(RCC->OSPIIOMCFGR, RCC_OSPIIOMCFGR_OSPIIOMLPEN)
#define __HAL_RCC_ETHSW_CLK_SLEEP_ENABLE()        SET_BIT(RCC->ETHSWCFGR, RCC_ETHSWCFGR_ETHSWMACLPEN|\
                                                          RCC_ETHSWCFGR_ETHSWLPEN|RCC_ETHSWCFGR_ETHSWREFLPEN)
#define __HAL_RCC_VDEC_CLK_SLEEP_ENABLE()         SET_BIT(RCC->VDECCFGR, RCC_VDECCFGR_VDECLPEN)

#if defined(RCC_VENCCFGR_VENCLPEN)
#define __HAL_RCC_VENC_CLK_SLEEP_ENABLE()         SET_BIT(RCC->VENCCFGR, RCC_VENCCFGR_VENCLPEN)
#endif /* RCC_VENCCFGR_VENCLPEN */

#if defined(RCC_C3CFGR_C3LPEN)
#define __HAL_RCC_C3_CLK_SLEEP_ENABLE()           SET_BIT(RCC->C3CFGR, RCC_C3CFGR_C3LPEN)
#endif /* RCC_C3CFGR_C3LPEN */

#define __HAL_RCC_SYSRAM_CLK_SLEEP_ENABLE()       SET_BIT(RCC->SYSRAMCFGR, RCC_SYSRAMCFGR_SYSRAMLPEN)
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->SRAM1CFGR, RCC_SRAM1CFGR_SRAM1LPEN)

#if defined(RCC_SRAM2CFGR_SRAM2LPEN)
#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()        SET_BIT(RCC->SRAM2CFGR, RCC_SRAM2CFGR_SRAM2LPEN)
#endif /* RCC_SRAM2CFGR_SRAM2LPEN */

#define __HAL_RCC_RETRAM_CLK_SLEEP_ENABLE()       SET_BIT(RCC->RETRAMCFGR, RCC_RETRAMCFGR_RETRAMLPEN)
#define __HAL_RCC_BKPSRAM_CLK_SLEEP_ENABLE()      SET_BIT(RCC->BKPSRAMCFGR, RCC_BKPSRAMCFGR_BKPSRAMLPEN)

#if defined(RCC_LPSRAM1CFGR_LPSRAM1LPEN)
#define __HAL_RCC_LPSRAM1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1LPEN)
#endif /* RCC_LPSRAM1CFGR_LPSRAM1LPEN */

#if defined(RCC_SRAM2CFGR_SRAM2LPEN)
#define __HAL_RCC_LPSRAM2_CLK_SLEEP_ENABLE()      SET_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2LPEN)
#endif /* RCC_LPSRAM2CFGR_LPSRAM2LPEN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3LPEN)
#define __HAL_RCC_LPSRAM3_CLK_SLEEP_ENABLE()      SET_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3LPEN)
#endif /* RCC_LPSRAM3CFGR_LPSRAM3LPEN */

#define __HAL_RCC_OSPI1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1LPEN)

#if defined(RCC_OSPI2CFGR_OSPI2LPEN)
#define __HAL_RCC_OSPI2_CLK_SLEEP_ENABLE()        SET_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2LPEN)
#endif /* RCC_OSPI2CFGR_OSPI2LPEN */

#if defined(RCC_STMCFGR_STMLPEN)
#define __HAL_RCC_STM_CLK_SLEEP_ENABLE()       SET_BIT(RCC->STMCFGR, RCC_STMCFGR_STMLPEN)
#endif /* RCC_STMCFGR_STMLPEN */

#define __HAL_RCC_ETR_CLK_SLEEP_ENABLE()          SET_BIT(RCC->ETRCFGR, RCC_ETRCFGR_ETRLPEN)
#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOG_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOH_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOI_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxLPEN)

#if defined(RCC_GPIOJCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOJ_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxLPEN)
#endif /* RCC_GPIOJCFGR_GPIOxLPEN */

#if defined(RCC_GPIOKCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOK_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxLPEN)
#endif /* RCC_GPIOKCFGR_GPIOxLPEN */

#define __HAL_RCC_GPIOZ_CLK_SLEEP_ENABLE()        SET_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZLPEN)
#define __HAL_RCC_HPDMA1_CLK_SLEEP_ENABLE()       SET_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1LPEN)
#define __HAL_RCC_HPDMA2_CLK_SLEEP_ENABLE()       SET_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2LPEN)
#define __HAL_RCC_HPDMA3_CLK_SLEEP_ENABLE()       SET_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3LPEN)

#if defined(RCC_LPDMACFGR_LPDMALPEN)
#define __HAL_RCC_LPDMA_CLK_SLEEP_ENABLE()        SET_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMALPEN)
#endif /* RCC_LPDMACFGR_LPDMALPEN */

#if defined(RCC_HSEMCFGR_HSEMLPEN)
#define __HAL_RCC_HSEM_CLK_SLEEP_ENABLE()         SET_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMLPEN)
#endif /* RCC_HSEMCFGR_HSEMLPEN */

#define __HAL_RCC_IPCC1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1LPEN)

#if defined(RCC_IPCC2CFGR_IPCC2LPEN)
#define __HAL_RCC_IPCC2_CLK_SLEEP_ENABLE()        SET_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2LPEN)
#endif /* RCC_IPCC2CFGR_IPCC2LPEN */

#define __HAL_RCC_RTC_CLK_SLEEP_ENABLE()          SET_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCLPEN)
#define __HAL_RCC_SYSCPU1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->SYSCPU1CFGR, RCC_SYSCPU1CFGR_SYSCPU1LPEN)
#define __HAL_RCC_IS2M_CLK_SLEEP_ENABLE()         SET_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MLPEN)
#define __HAL_RCC_TIM1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1LPEN)
#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2LPEN)
#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3LPEN)
#define __HAL_RCC_TIM4_CLK_SLEEP_ENABLE()         SET_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4LPEN)
#define __HAL_RCC_TIM5_CLK_SLEEP_ENABLE()         SET_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5LPEN)
#define __HAL_RCC_TIM6_CLK_SLEEP_ENABLE()         SET_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6LPEN)
#define __HAL_RCC_TIM7_CLK_SLEEP_ENABLE()         SET_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7LPEN)
#define __HAL_RCC_TIM8_CLK_SLEEP_ENABLE()         SET_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8LPEN)
#define __HAL_RCC_TIM10_CLK_SLEEP_ENABLE()        SET_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10LPEN)
#define __HAL_RCC_TIM11_CLK_SLEEP_ENABLE()        SET_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11LPEN)
#define __HAL_RCC_TIM12_CLK_SLEEP_ENABLE()        SET_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12LPEN)
#define __HAL_RCC_TIM13_CLK_SLEEP_ENABLE()        SET_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13LPEN)
#define __HAL_RCC_TIM14_CLK_SLEEP_ENABLE()        SET_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14LPEN)
#define __HAL_RCC_TIM15_CLK_SLEEP_ENABLE()        SET_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15LPEN)
#define __HAL_RCC_TIM16_CLK_SLEEP_ENABLE()        SET_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16LPEN)
#define __HAL_RCC_TIM17_CLK_SLEEP_ENABLE()        SET_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17LPEN)

#if defined(RCC_TIM20CFGR_TIM20LPEN)
#define __HAL_RCC_TIM20_CLK_SLEEP_ENABLE()        SET_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20LPEN)
#endif /* RCC_TIM20CFGR_TIM20LPEN */

#define __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE()       SET_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1LPEN)
#define __HAL_RCC_LPTIM2_CLK_SLEEP_ENABLE()       SET_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2LPEN)
#define __HAL_RCC_LPTIM3_CLK_SLEEP_ENABLE()       SET_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3LPEN)
#define __HAL_RCC_LPTIM4_CLK_SLEEP_ENABLE()       SET_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4LPEN)
#define __HAL_RCC_LPTIM5_CLK_SLEEP_ENABLE()       SET_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5LPEN)
#define __HAL_RCC_SPI1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1LPEN)
#define __HAL_RCC_SPI2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2LPEN)
#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3LPEN)
#define __HAL_RCC_SPI4_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4LPEN)
#define __HAL_RCC_SPI5_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5LPEN)
#define __HAL_RCC_SPI6_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6LPEN)

#if defined(RCC_SPI7CFGR_SPI7LPEN)
#define __HAL_RCC_SPI7_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7LPEN)
#endif /* RCC_SPI7CFGR_SPI7LPEN */

#if defined(RCC_SPI8CFGR_SPI8LPEN)
#define __HAL_RCC_SPI8_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8LPEN)
#endif /* RCC_SPI8CFGR_SPI8LPEN */

#define __HAL_RCC_SPDIFRX_CLK_SLEEP_ENABLE()      SET_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXLPEN)
#define __HAL_RCC_USART1_CLK_SLEEP_ENABLE()       SET_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1LPEN)
#define __HAL_RCC_USART2_CLK_SLEEP_ENABLE()       SET_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2LPEN)
#define __HAL_RCC_USART3_CLK_SLEEP_ENABLE()       SET_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3LPEN)
#define __HAL_RCC_UART4_CLK_SLEEP_ENABLE()        SET_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4LPEN)
#define __HAL_RCC_UART5_CLK_SLEEP_ENABLE()        SET_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5LPEN)
#define __HAL_RCC_USART6_CLK_SLEEP_ENABLE()       SET_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6LPEN)
#define __HAL_RCC_UART7_CLK_SLEEP_ENABLE()        SET_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7LPEN)

#if defined (RCC_UART8CFGR_UART8LPEN)
#define __HAL_RCC_UART8_CLK_SLEEP_ENABLE()        SET_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8LPEN)
#endif /* RCC_UART8CFGR_UART8LPEN */

#if defined (RCC_UART9CFGR_UART9LPEN)
#define __HAL_RCC_UART9_CLK_SLEEP_ENABLE()        SET_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9LPEN)
#endif /* RCC_UART9CFGR_UART9LPEN */

#define __HAL_RCC_LPUART1_CLK_SLEEP_ENABLE()      SET_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1LPEN)
#define __HAL_RCC_I2C1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1LPEN)
#define __HAL_RCC_I2C2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2LPEN)
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3LPEN)

#if defined (RCC_I2C4CFGR_I2C4LPEN)
#define __HAL_RCC_I2C4_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4LPEN)
#endif /*  RCC_I2C4CFGR_I2C4LPEN */

#if defined (RCC_I2C5CFGR_I2C5LPEN)
#define __HAL_RCC_I2C5_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5LPEN)
#endif /*  RCC_I2C5CFGR_I2C5LPEN */

#if defined (RCC_I2C6CFGR_I2C6LPEN)
#define __HAL_RCC_I2C6_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6LPEN)
#endif /*  RCC_I2C6CFGR_I2C6LPEN */

#if defined (RCC_I2C7CFGR_I2C7LPEN)
#define __HAL_RCC_I2C7_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7LPEN)
#endif /* RCC_I2C7CFGR_I2C7LPEN  */

#if defined (RCC_I2C8CFGR_I2C8LPEN)
#define __HAL_RCC_I2C8_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8LPEN)
#endif /*  RCC_I2C8CFGR_I2C8LPEN */

#define __HAL_RCC_SAI1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1LPEN)
#define __HAL_RCC_SAI2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2LPEN)
#define __HAL_RCC_SAI3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3LPEN)
#define __HAL_RCC_SAI4_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4LPEN)
#define __HAL_RCC_MDF1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1LPEN)
#define __HAL_RCC_ADF1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1LPEN)
#define __HAL_RCC_FDCAN_CLK_SLEEP_ENABLE()        SET_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANLPEN)

#if defined(RCC_ADC12CFGR_ADC12LPEN)
#define __HAL_RCC_ADC12_CLK_SLEEP_ENABLE()        SET_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12LPEN)
#endif /* RCC_ADC12CFGR_ADC12LPEN */

#if defined(RCC_ADC1CFGR_ADC1LPEN)
#define __HAL_RCC_ADC1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1LPEN)
#endif /* RCC_ADC1CFGR_ADC1LPEN */

#if defined(RCC_ADC2CFGR_ADC2LPEN)
#define __HAL_RCC_ADC2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2LPEN)
#endif /* RCC_ADC2CFGR_ADC2LPEN */

#if defined(RCC_ADC3CFGR_ADC3LPEN)
#define __HAL_RCC_ADC3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3LPEN)
#endif /* RCC_ADC3CFGR_ADC3LPEN */

#define __HAL_RCC_ETH1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1LPEN)
#define __HAL_RCC_ETH1MAC_CLK_SLEEP_ENABLE()      SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1MACLPEN)
#define __HAL_RCC_ETH1TX_CLK_SLEEP_ENABLE()       SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1TXLPEN)
#define __HAL_RCC_ETH1RX_CLK_SLEEP_ENABLE()       SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1RXLPEN)
#define __HAL_RCC_ETH2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2LPEN)
#define __HAL_RCC_ETH2MAC_CLK_SLEEP_ENABLE()      SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2MACLPEN)
#define __HAL_RCC_ETH2TX_CLK_SLEEP_ENABLE()       SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2TXLPEN)
#define __HAL_RCC_ETH2RX_CLK_SLEEP_ENABLE()       SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2RXLPEN)


#define __HAL_RCC_USB2PHY1_CLK_SLEEP_ENABLE()     SET_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1LPEN)
#define __HAL_RCC_USB2PHY2_CLK_SLEEP_ENABLE()     SET_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2LPEN)

#if defined(RCC_USB3DRDCFGR_USB3DRDLPEN)
#define __HAL_RCC_USB3DRD_CLK_SLEEP_ENABLE()      SET_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDLPEN)
#endif /* RCC_USB3DRDCFGR_USB3DRDLPEN */

#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN)
#define __HAL_RCC_USB3PCIEPHY_CLK_SLEEP_ENABLE()  SET_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN)
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN */

#if defined(RCC_PCIECFGR_PCIELPEN)
#define __HAL_RCC_PCIE_CLK_SLEEP_ENABLE()         SET_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIELPEN)
#endif /*RCC_PCIECFGR_PCIELPEN */

#if defined(RCC_UCPDCFGR_UCPDLPEN)
#define __HAL_RCC_UCPD1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDLPEN)
#endif /* RCC_UCPDCFGR_UCPDLPEN */

#define __HAL_RCC_FMC_CLK_SLEEP_ENABLE()          SET_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCLPEN)
#define __HAL_RCC_SDMMC1_CLK_SLEEP_ENABLE()       SET_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1LPEN)
#define __HAL_RCC_SDMMC2_CLK_SLEEP_ENABLE()       SET_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2LPEN)
#define __HAL_RCC_SDMMC3_CLK_SLEEP_ENABLE()       SET_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3LPEN)
#define __HAL_RCC_GPU_CLK_SLEEP_ENABLE()          SET_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPULPEN)
#define __HAL_RCC_LTDC_CLK_SLEEP_ENABLE()         SET_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCLPEN)

#if defined(RCC_DSICFGR_DSILPEN)
#define __HAL_RCC_DSI_CLK_SLEEP_ENABLE()          SET_BIT(RCC->DSICFGR, RCC_DSICFGR_DSILPEN)
#endif /* RCC_DSICFGR_DSILPEN */

#define __HAL_RCC_LVDS_CLK_SLEEP_ENABLE()         SET_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSLPEN)

#if defined(RCC_CSICFGR_CSILPEN)
#define __HAL_RCC_CSI_CLK_SLEEP_ENABLE()          SET_BIT(RCC->CSICFGR, RCC_CSICFGR_CSILPEN)
#endif /* RCC_CSICFGR_CSILPEN */

#if defined(RCC_CSI2CFGR_CSI2LPEN)
#define __HAL_RCC_CSI2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2LPEN)
#endif /* RCC_CSI2CFGR_CSI2LPEN */

#define __HAL_RCC_DCMIPP_CLK_SLEEP_ENABLE()       SET_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPLPEN)

#if defined(RCC_DCMIPSSICFGR_DCMIPSSILPEN)
#define __HAL_RCC_DCMIPSSI_CLK_SLEEP_ENABLE()          SET_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSILPEN)
#endif /* RCC_DCMIPSSICFGR_DCMIPSSILPEN */

#if defined(RCC_CCICFGR_CCILPEN)
#define __HAL_RCC_CCI_CLK_SLEEP_ENABLE()          SET_BIT(RCC->CCICFGR, RCC_CCICFGR_CCILPEN)
#endif /* RCC_CCICFGR_CCILPEN */

#if defined(RCC_RNGCFGR_RNGLPEN)
#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()          SET_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGLPEN)
#endif /* RCC_RNGCFGR_RNGLPEN */


#if defined(RCC_RNG1CFGR_RNG1LPEN)
#define __HAL_RCC_RNG1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1LPEN)
#endif /* RCC_RNG1CFGR_RNG1LPEN */

#if defined(RCC_RNG2CFGR_RNG2LPEN)
#define __HAL_RCC_RNG2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2LPEN)
#endif /* RCC_RNG2CFGR_RNG2LPEN */

#define __HAL_RCC_PKA_CLK_SLEEP_ENABLE()          SET_BIT(RCC->PKACFGR, RCC_PKACFGR_PKALPEN)
#define __HAL_RCC_SAES_CLK_SLEEP_ENABLE()         SET_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESLPEN)

#if defined(RCC_HASHCFGR_HASHLPEN)
#define __HAL_RCC_HASH_CLK_SLEEP_ENABLE()         SET_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHLPEN)
#endif /* RCC_HASHCFGR_HASHLPEN */

#if defined(RCC_HASH1CFGR_HASH1LPEN)
#define __HAL_RCC_HASH1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1LPEN)
#endif /* RCC_HASH1CFGR_HASH1LPEN */

#if defined(RCC_HASH2CFGR_HASH2LPEN)
#define __HAL_RCC_HASH2_CLK_SLEEP_ENABLE()        SET_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2LPEN)
#endif /* RCC_HASH2CFGR_HASH2LPEN */

#define __HAL_RCC_CRYP1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1LPEN)
#define __HAL_RCC_CRYP2_CLK_SLEEP_ENABLE()        SET_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2LPEN)
#define __HAL_RCC_IWDG1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->IWDG1CFGR, RCC_IWDG1CFGR_IWDG1LPEN)
#define __HAL_RCC_IWDG2_CLK_SLEEP_ENABLE()        SET_BIT(RCC->IWDG2CFGR, RCC_IWDG2CFGR_IWDG2LPEN)
#define __HAL_RCC_IWDG3_CLK_SLEEP_ENABLE()        SET_BIT(RCC->IWDG3CFGR, RCC_IWDG3CFGR_IWDG3LPEN)
#define __HAL_RCC_IWDG4_CLK_SLEEP_ENABLE()        SET_BIT(RCC->IWDG4CFGR, RCC_IWDG4CFGR_IWDG4LPEN)

#if defined(RCC_IWDG5CFGR_IWDG5LPEN)
#define __HAL_RCC_IWDG5_CLK_SLEEP_ENABLE()        SET_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5LPEN)
#endif /* RCC_IWDG5CFGR_IWDG5LPEN */

#define __HAL_RCC_WWDG1_CLK_SLEEP_ENABLE()        SET_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1LPEN)

#if defined(RCC_WWDG2CFGR_WWDG2LPEN)
#define __HAL_RCC_WWDG2_CLK_SLEEP_ENABLE()        SET_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2LPEN)
#endif /*RCC_WWDG2CFGR_WWDG2LPEN*/

#define __HAL_RCC_BUSPERFM_CLK_SLEEP_ENABLE()     SET_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMLPEN)
#define __HAL_RCC_VREF_CLK_SLEEP_ENABLE()         SET_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFLPEN)

#if defined(RCC_TMPSENSCFGR_TMPSENSLPEN)
#define __HAL_RCC_TMPSENS_CLK_SLEEP_ENABLE()      SET_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSLPEN)
#endif /* RCC_TMPSENSCFGR_TMPSENSLPEN */

#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()          SET_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCLPEN)
#define __HAL_RCC_BSEC_CLK_SLEEP_ENABLE()         SET_BIT(RCC->BSECCFGR, RCC_BSECCFGR_BSECLPEN)

#if defined(RCC_GICV2MCFGR_GICV2MLPEN)
#define __HAL_RCC_GICV2M_CLK_SLEEP_ENABLE()       SET_BIT(RCC->GICV2MCFGR, RCC_GICV2MCFGR_GICV2MLPEN)
#endif /* RCC_GICV2MCFGR_GICV2MLPEN */

#define __HAL_RCC_I3C1_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1LPEN)
#define __HAL_RCC_I3C2_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2LPEN)
#define __HAL_RCC_I3C3_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3LPEN)

#if defined(RCC_I3C4CFGR_I3C4LPEN)
#define __HAL_RCC_I3C4_CLK_SLEEP_ENABLE()         SET_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4LPEN)
#endif /* RCC_I3C4CFGR_I3C4LPEN */

/* for API backward compatibility */
#if defined(RCC_DCMIPSSICFGR_DCMIPSSILPEN)
#define __HAL_RCC_DCMI_CLK_SLEEP_ENABLE()         __HAL_RCC_DCMIPSSI_CLK_SLEEP_ENABLE()
#define __HAL_RCC_PSSI_CLK_SLEEP_ENABLE()         __HAL_RCC_DCMIPSSI_CLK_SLEEP_ENABLE()
#endif /* RCC_DCMIPSSICFGR_DCMIPSSILPEN */

#if defined(RCC_CCICFGR_CCILPEN)
#define __HAL_RCC_DCMI_CLK_SLEEP_ENABLE()         __HAL_RCC_CCI_CLK_SLEEP_ENABLE()
#define __HAL_RCC_PSSI_CLK_SLEEP_ENABLE()         __HAL_RCC_CCI_CLK_SLEEP_ENABLE()
#endif /* RCC_CCICFGR_CCILPEN */

#define __HAL_RCC_OTFDEC1_CLK_SLEEP_ENABLE()      __HAL_RCC_OSPI1_CLK_SLEEP_ENABLE()

#if defined(RCC_OSPI2CFGR_OSPI2LPEN)
#define __HAL_RCC_OTFDEC2_CLK_SLEEP_ENABLE()      __HAL_RCC_OSPI2_CLK_SLEEP_ENABLE()
#endif /* RCC_OSPI2CFGR_OSPI2LPEN */

/* Clock sleep disable macros */
#if defined(RCC_VDERAMCFGR_VDERAMLPEN)
#define __HAL_RCC_VDERAM_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->VDERAMCFGR, RCC_VDERAMCFGR_VDERAMLPEN)
#endif /* RCC_VDERAMCFGR_VDERAMLPEN */

#define __HAL_RCC_SERC_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SERCCFGR, RCC_SERCCFGR_SERCLPEN)
#define __HAL_RCC_OSPIIOM_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->OSPIIOMCFGR, RCC_OSPIIOMCFGR_OSPIIOMLPEN)
#define __HAL_RCC_ETHSW_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->ETHSWCFGR, RCC_ETHSWCFGR_ETHSWMACLPEN|\
                                                            RCC_ETHSWCFGR_ETHSWLPEN|RCC_ETHSWCFGR_ETHSWREFLPEN)
#define __HAL_RCC_VDEC_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->VDECCFGR, RCC_VDECCFGR_VDECLPEN)

#if defined(RCC_VENCCFGR_VENCLPEN)
#define __HAL_RCC_VENC_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->VENCCFGR, RCC_VENCCFGR_VENCLPEN)
#endif /* RCC_VENCCFGR_VENCLPEN */

#if defined(RCC_C3CFGR_C3LPEN)
#define __HAL_RCC_C3_CLK_SLEEP_DISABLE()          CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_C3LPEN)
#endif /* RCC_C3CFGR_C3LPEN */

#define __HAL_RCC_SYSRAM_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->SYSRAMCFGR, RCC_SYSRAMCFGR_SYSRAMLPEN)
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->SRAM1CFGR, RCC_SRAM1CFGR_SRAM1LPEN)

#if defined(RCC_SRAM2CFGR_SRAM2LPEN)
#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->SRAM2CFGR, RCC_SRAM2CFGR_SRAM2LPEN)
#endif /* RCC_SRAM2CFGR_SRAM2LPEN */

#define __HAL_RCC_RETRAM_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->RETRAMCFGR, RCC_RETRAMCFGR_RETRAMLPEN)
#define __HAL_RCC_BKPSRAM_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->BKPSRAMCFGR, RCC_BKPSRAMCFGR_BKPSRAMLPEN)

#if defined(RCC_LPSRAM1CFGR_LPSRAM1LPEN)
#define __HAL_RCC_LPSRAM1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1LPEN)
#endif /* RCC_LPSRAM1CFGR_LPSRAM1LPEN */

#if defined(RCC_LPSRAM2CFGR_LPSRAM2LPEN)
#define __HAL_RCC_LPSRAM2_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2LPEN)
#endif /* RCC_LPSRAM2CFGR_LPSRAM2LPEN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3LPEN)
#define __HAL_RCC_LPSRAM3_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3LPEN)
#endif /* RCC_LPSRAM3CFGR_LPSRAM3LPEN */

#define __HAL_RCC_OSPI1_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1LPEN)

#if defined(RCC_OSPI2CFGR_OSPI2LPEN)
#define __HAL_RCC_OSPI2_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2LPEN)
#endif /* RCC_OSPI2CFGR_OSPI2LPEN */

#if defined(RCC_STMCFGR_STMLPEN)
#define __HAL_RCC_STM_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->STMCFGR, RCC_STMCFGR_STMLPEN)
#endif /* RCC_STMCFGR_STMLPEN */

#define __HAL_RCC_ETR_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->ETRCFGR, RCC_ETRCFGR_ETRLPEN)
#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOG_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOH_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOI_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxLPEN)

#if defined(RCC_GPIOJCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOJ_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxLPEN)
#endif /* RCC_GPIOJCFGR_GPIOxLPEN */

#if defined(RCC_GPIOKCFGR_GPIOxLPEN)
#define __HAL_RCC_GPIOK_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxLPEN)
#endif /* RCC_GPIOKCFGR_GPIOxLPEN */

#define __HAL_RCC_GPIOZ_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZLPEN)
#define __HAL_RCC_HPDMA1_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1LPEN)
#define __HAL_RCC_HPDMA2_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2LPEN)
#define __HAL_RCC_HPDMA3_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3LPEN)

#if defined(RCC_LPDMACFGR_LPDMALPEN)
#define __HAL_RCC_LPDMA_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMALPEN)
#endif /* RCC_LPDMACFGR_LPDMALPEN */

#if defined(RCC_HSEMCFGR_HSEMLPEN)
#define __HAL_RCC_HSEM_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMLPEN)
#endif /* RCC_HSEMCFGR_HSEMLPEN */

#define __HAL_RCC_IPCC1_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1LPEN)

#if defined(RCC_IPCC2CFGR_IPCC2LPEN)
#define __HAL_RCC_IPCC2_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2LPEN)
#endif /* RCC_IPCC2CFGR_IPCC2LPEN */

#define __HAL_RCC_RTC_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCLPEN)
#define __HAL_RCC_SYSCPU1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->SYSCPU1CFGR, RCC_SYSCPU1CFGR_SYSCPU1LPEN)

#define __HAL_RCC_IS2M_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MLPEN)
#define __HAL_RCC_TIM1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1LPEN)
#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2LPEN)
#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3LPEN)
#define __HAL_RCC_TIM4_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4LPEN)
#define __HAL_RCC_TIM5_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5LPEN)
#define __HAL_RCC_TIM6_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6LPEN)
#define __HAL_RCC_TIM7_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7LPEN)
#define __HAL_RCC_TIM8_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8LPEN)
#define __HAL_RCC_TIM10_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10LPEN)
#define __HAL_RCC_TIM11_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11LPEN)
#define __HAL_RCC_TIM12_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12LPEN)
#define __HAL_RCC_TIM13_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13LPEN)
#define __HAL_RCC_TIM14_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14LPEN)
#define __HAL_RCC_TIM15_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15LPEN)
#define __HAL_RCC_TIM16_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16LPEN)
#define __HAL_RCC_TIM17_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17LPEN)

#if defined(RCC_TIM20CFGR_TIM20LPEN)
#define __HAL_RCC_TIM20_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20LPEN)
#endif /* RCC_TIM20CFGR_TIM20LPEN */

#define __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1LPEN)
#define __HAL_RCC_LPTIM2_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2LPEN)
#define __HAL_RCC_LPTIM3_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3LPEN)
#define __HAL_RCC_LPTIM4_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4LPEN)
#define __HAL_RCC_LPTIM5_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5LPEN)
#define __HAL_RCC_SPI1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1LPEN)
#define __HAL_RCC_SPI2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2LPEN)
#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3LPEN)
#define __HAL_RCC_SPI4_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4LPEN)
#define __HAL_RCC_SPI5_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5LPEN)
#define __HAL_RCC_SPI6_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6LPEN)

#if defined(RCC_SPI7CFGR_SPI7LPEN)
#define __HAL_RCC_SPI7_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7LPEN)
#endif /* RCC_SPI7CFGR_SPI7LPEN */

#if defined(RCC_SPI8CFGR_SPI8LPEN)
#define __HAL_RCC_SPI8_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8LPEN)
#endif /* RCC_SPI8CFGR_SPI8LPEN */

#define __HAL_RCC_SPDIFRX_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXLPEN)
#define __HAL_RCC_USART1_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1LPEN)
#define __HAL_RCC_USART2_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2LPEN)
#define __HAL_RCC_USART3_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3LPEN)
#define __HAL_RCC_UART4_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4LPEN)
#define __HAL_RCC_UART5_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5LPEN)
#define __HAL_RCC_USART6_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6LPEN)
#define __HAL_RCC_UART7_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7LPEN)

#if defined(RCC_UART8CFGR_UART8LPEN)
#define __HAL_RCC_UART8_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8LPEN)
#endif /* RCC_UART8CFGR_UART8LPEN */

#if defined(RCC_UART9CFGR_UART9LPEN)
#define __HAL_RCC_UART9_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9LPEN)
#endif /* RCC_UART9CFGR_UART9LPEN */

#define __HAL_RCC_LPUART1_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1LPEN)
#define __HAL_RCC_I2C1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1LPEN)
#define __HAL_RCC_I2C2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2LPEN)
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3LPEN)

#if defined(RCC_I2C4CFGR_I2C4LPEN)
#define __HAL_RCC_I2C4_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4LPEN)
#endif /* RCC_I2C4CFGR_I2C4LPEN */

#if defined(RCC_I2C5CFGR_I2C5LPEN)
#define __HAL_RCC_I2C5_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5LPEN)
#endif /* RCC_I2C5CFGR_I2C5LPEN */

#if defined(RCC_I2C6CFGR_I2C6LPEN)
#define __HAL_RCC_I2C6_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6LPEN)
#endif /* RCC_I2C6CFGR_I2C6LPEN */

#if defined(RCC_I2C7CFGR_I2C7LPEN)
#define __HAL_RCC_I2C7_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7LPEN)
#endif /* RCC_I2C7CFGR_I2C7LPEN */

#if defined(RCC_I2C8CFGR_I2C8LPEN)
#define __HAL_RCC_I2C8_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8LPEN)
#endif /* RCC_I2C8CFGR_I2C8LPEN */

#define __HAL_RCC_SAI1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1LPEN)
#define __HAL_RCC_SAI2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2LPEN)
#define __HAL_RCC_SAI3_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3LPEN)
#define __HAL_RCC_SAI4_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4LPEN)
#define __HAL_RCC_MDF1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1LPEN)
#define __HAL_RCC_ADF1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1LPEN)
#define __HAL_RCC_FDCAN_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANLPEN)

#if defined(RCC_ADC1CFGR_ADC1LPEN)
#define __HAL_RCC_ADC1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1LPEN)
#endif /* RCC_ADC1CFGR_ADC1LPEN */

#if defined(RCC_ADC2CFGR_ADC2LPEN)
#define __HAL_RCC_ADC2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2LPEN)
#endif /* RCC_ADC2CFGR_ADC2LPEN  */

#if defined(RCC_ADC12CFGR_ADC12LPEN)
#define __HAL_RCC_ADC12_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12LPEN)
#endif /* RCC_ADC12CFGR_ADC12LPEN  */

#if defined(RCC_ADC3CFGR_ADC3LPEN)
#define __HAL_RCC_ADC3_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3LPEN)
#endif /* RCC_ADC3CFGR_ADC3LPEN  */

#define __HAL_RCC_ETH1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1LPEN)
#define __HAL_RCC_ETH1MAC_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1MACLPEN)
#define __HAL_RCC_ETH1TX_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1TXLPEN)
#define __HAL_RCC_ETH1RX_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1RXLPEN)
#define __HAL_RCC_ETH2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2LPEN)
#define __HAL_RCC_ETH2MAC_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2MACLPEN)
#define __HAL_RCC_ETH2TX_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2TXLPEN)
#define __HAL_RCC_ETH2RX_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2RXLPEN)


#define __HAL_RCC_USB2PHY1_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1LPEN)
#define __HAL_RCC_USB2PHY2_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2LPEN)

#if defined(RCC_USB3DRDCFGR_USB3DRDLPEN)
#define __HAL_RCC_USB3DRD_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDLPEN)
#endif /* RCC_USB3DRDCFGR_USB3DRDLPEN  */

#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN)
#define __HAL_RCC_USB3PCIEPHY_CLK_SLEEP_DISABLE() CLEAR_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN)
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN  */

#if defined(RCC_PCIECFGR_PCIELPEN)
#define __HAL_RCC_PCIE_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIELPEN)
#endif /* RCC_PCIECFGR_PCIELPEN  */

#if defined(RCC_UCPDCFGR_UCPDLPEN)
#define __HAL_RCC_UCPD1_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDLPEN)
#endif /* RCC_UCPDCFGR_UCPDLPEN  */

#define __HAL_RCC_FMC_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCLPEN)
#define __HAL_RCC_SDMMC1_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1LPEN)
#define __HAL_RCC_SDMMC2_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2LPEN)
#define __HAL_RCC_SDMMC3_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3LPEN)
#define __HAL_RCC_GPU_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPULPEN)
#define __HAL_RCC_LTDC_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCLPEN)

#if defined(RCC_DSICFGR_DSILPEN)
#define __HAL_RCC_DSI_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->DSICFGR, RCC_DSICFGR_DSILPEN)
#endif /* RCC_DSICFGR_DSILPEN */

#define __HAL_RCC_LVDS_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSLPEN)

#if defined(RCC_CSICFGR_CSILPEN)
#define __HAL_RCC_CSI_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->CSICFGR, RCC_CSICFGR_CSILPEN)
#endif /*RCC_CSICFGR_CSILPEN */

#if defined(RCC_CSI2CFGR_CSI2LPEN)
#define __HAL_RCC_CSI2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2LPEN)
#endif /*RCC_CSI2CFGR_CSI2LPEN */

#define __HAL_RCC_DCMIPP_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPLPEN)

#if defined(RCC_DCMIPSSICFGR_DCMIPSSILPEN)
#define __HAL_RCC_DCMIPSSI_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSILPEN)
#endif /* RCC_DCMIPSSICFGR_DCMIPSSILPEN */

#if defined(RCC_CCICFGR_CCILPEN)
#define __HAL_RCC_CCI_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->CCICFGR, RCC_CCICFGR_CCILPEN)
#endif /* RCC_CCICFGR_CCILPEN */

#if defined(RCC_RNGCFGR_RNGLPEN)
#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGLPEN)
#endif /* RCC_RNGCFGR_RNGLPEN*/

#if defined(RCC_RNG1CFGR_RNG1LPEN)
#define __HAL_RCC_RNG1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1LPEN)
#endif /* RCC_RNG1CFGR_RNG1LPEN */

#if defined(RCC_RNG2CFGR_RNG2LPEN)
#define __HAL_RCC_RNG2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2LPEN)
#endif /* RCC_RNG2CFGR_RNG2LPEN */

#define __HAL_RCC_PKA_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->PKACFGR, RCC_PKACFGR_PKALPEN)
#define __HAL_RCC_SAES_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESLPEN)

#if defined(RCC_HASHCFGR_HASHLPEN)
#define __HAL_RCC_HASH_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHLPEN)
#endif /* RCC_HASHCFGR_HASHLPEN */

#if defined(RCC_HASH1CFGR_HASH1LPEN)
#define __HAL_RCC_HASH1_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1LPEN)
#endif /* RCC_HASHCFGR_HASHLPEN */

#if defined(RCC_HASH2CFGR_HASH2LPEN)
#define __HAL_RCC_HASH2_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2LPEN)
#endif /* RCC_HASH2CFGR_HASH2LPEN */

#define __HAL_RCC_CRYP1_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1LPEN)
#define __HAL_RCC_CRYP2_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2LPEN)
#define __HAL_RCC_IWDG1_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->IWDG1CFGR, RCC_IWDG1CFGR_IWDG1LPEN)
#define __HAL_RCC_IWDG2_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->IWDG2CFGR, RCC_IWDG2CFGR_IWDG2LPEN)
#define __HAL_RCC_IWDG3_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->IWDG3CFGR, RCC_IWDG3CFGR_IWDG3LPEN)
#define __HAL_RCC_IWDG4_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->IWDG4CFGR, RCC_IWDG4CFGR_IWDG4LPEN)

#if defined(RCC_IWDG5CFGR_IWDG5LPEN)
#define __HAL_RCC_IWDG5_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5LPEN)
#endif /* RCC_IWDG5CFGR_IWDG5LPEN */

#define __HAL_RCC_WWDG1_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1LPEN)

#if defined(RCC_WWDG2CFGR_WWDG2LPEN)
#define __HAL_RCC_WWDG2_CLK_SLEEP_DISABLE()       CLEAR_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2LPEN)
#endif /* RCC_WWDG2CFGR_WWDG2LPEN */

#define __HAL_RCC_BUSPERFM_CLK_SLEEP_DISABLE()    CLEAR_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMLPEN)
#define __HAL_RCC_VREF_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFLPEN)
#define __HAL_RCC_TMPSENS_CLK_SLEEP_DISABLE()     CLEAR_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSLPEN)
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()         CLEAR_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCLPEN)
#define __HAL_RCC_BSEC_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->BSECCFGR, RCC_BSECCFGR_BSECLPEN)

#if defined(RCC_GICV2MCFGR_GICV2MLPEN)
#define __HAL_RCC_GICV2M_CLK_SLEEP_DISABLE()      CLEAR_BIT(RCC->GICV2MCFGR, RCC_GICV2MCFGR_GICV2MLPEN)
#endif /* RCC_GICV2MCFGR_GICV2MLPEN */

#define __HAL_RCC_I3C1_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1LPEN)
#define __HAL_RCC_I3C2_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2LPEN)
#define __HAL_RCC_I3C3_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3LPEN)

#if defined(RCC_I3C4CFGR_I3C4LPEN)
#define __HAL_RCC_I3C4_CLK_SLEEP_DISABLE()        CLEAR_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4LPEN)
#endif /* RCC_I3C4CFGR_I3C4LPEN */

/* for API backward compatibility */
#if defined(RCC_CCICFGR_CCILPEN)
#define __HAL_RCC_DCMI_CLK_SLEEP_DISABLE()        __HAL_RCC_CCI_CLK_SLEEP_DISABLE()
#define __HAL_RCC_PSSI_CLK_SLEEP_DISABLE()        __HAL_RCC_CCI_CLK_SLEEP_DISABLE()
#endif /* RCC_CCICFGR_CCILPEN */

#if defined(RCC_DCMIPSSICFGR_DCMIPSSILPEN )
#define __HAL_RCC_DCMI_CLK_SLEEP_DISABLE()        __HAL_RCC_DCMIPSSI_CLK_SLEEP_DISABLE()
#define __HAL_RCC_PSSI_CLK_SLEEP_DISABLE()        __HAL_RCC_DCMIPSSI_CLK_SLEEP_DISABLE()
#endif /* RCC_DCMIPSSICFGR_DCMIPSSILPEN  */

#define __HAL_RCC_OTFDEC1_CLK_SLEEP_DISABLE()     __HAL_RCC_OSPI1_CLK_SLEEP_DISABLE()

#if defined(RCC_OSPI2CFGR_OSPI2LPEN)
#define __HAL_RCC_OTFDEC2_CLK_SLEEP_DISABLE()     __HAL_RCC_OSPI2_CLK_SLEEP_DISABLE()
#endif /* RCC_OSPI2CFGR_OSPI2LPEN */

/* Clock autonomous mode enable macros */
#if defined(RCC_C3CFGR_C3AMEN)
#define __HAL_RCC_C3_CLKAM_ENABLE()               SET_BIT(RCC->C3CFGR, RCC_C3CFGR_C3AMEN)
#endif /* RCC_C3CFGR_C3AMEN */

#if defined(RCC_LPSRAM1CFGR_LPSRAM1AMEN)
#define __HAL_RCC_LPSRAM1_CLKAM_ENABLE()          SET_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1AMEN)
#endif /* RCC_LPSRAM1CFGR_LPSRAM1AMEN */

#if defined(RCC_LPSRAM2CFGR_LPSRAM2AMEN)
#define __HAL_RCC_LPSRAM2_CLKAM_ENABLE()          SET_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2AMEN)
#endif /* RCC_LPSRAM2CFGR_LPSRAM2AMEN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3AMEN)
#define __HAL_RCC_LPSRAM3_CLKAM_ENABLE()          SET_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3AMEN)
#endif /* RCC_LPSRAM3CFGR_LPSRAM3AMEN */

#if defined(RCC_GPIOZCFGR_GPIOZAMEN)
#define __HAL_RCC_GPIOZ_CLKAM_ENABLE()            SET_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZAMEN)
#endif /* RCC_GPIOZCFGR_GPIOZAMEN */

#if defined(RCC_LPDMACFGR_LPDMAAMEN)
#define __HAL_RCC_LPDMA_CLKAM_ENABLE()            SET_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMAAMEN)
#endif /* RCC_LPDMACFGR_LPDMAAMEN */

#if defined(RCC_HSEMCFGR_HSEMAMEN)
#define __HAL_RCC_HSEM_CLKAM_ENABLE()             SET_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMAMEN)
#endif /* RCC_HSEMCFGR_HSEMAMEN */

#if defined(RCC_IPCC2CFGR_IPCC2AMEN)
#define __HAL_RCC_IPCC2_CLKAM_ENABLE()            SET_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2AMEN)
#endif /* RCC_IPCC2CFGR_IPCC2AMEN */

#if defined(RCC_RTCCFGR_RTCAMEN)
#define __HAL_RCC_RTC_CLKAM_ENABLE()              SET_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCAMEN)
#endif /* RCC_RTCCFGR_RTCAMEN */

#if defined(RCC_LPTIM3CFGR_LPTIM3AMEN)
#define __HAL_RCC_LPTIM3_CLKAM_ENABLE()           SET_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3AMEN)
#endif /* RCC_LPTIM3CFGR_LPTIM3AMEN */

#if defined(RCC_LPTIM4CFGR_LPTIM4AMEN)
#define __HAL_RCC_LPTIM4_CLKAM_ENABLE()           SET_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4AMEN)
#endif /* RCC_LPTIM4CFGR_LPTIM4AMEN */

#if defined(RCC_LPTIM5CFGR_LPTIM5AMEN)
#define __HAL_RCC_LPTIM5_CLKAM_ENABLE()           SET_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5AMEN)
#endif /* RCC_LPTIM5CFGR_LPTIM5AMEN */

#if defined(RCC_SPI8CFGR_SPI8AMEN)
#define __HAL_RCC_SPI8_CLKAM_ENABLE()             SET_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8AMEN)
#endif /* RCC_SPI8CFGR_SPI8AMEN */

#if defined(RCC_LPUART1CFGR_LPUART1AMEN)
#define __HAL_RCC_LPUART1_CLKAM_ENABLE()          SET_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1AMEN)
#endif /* RCC_LPUART1CFGR_LPUART1AMEN */

#if defined(RCC_I2C8CFGR_I2C8AMEN)
#define __HAL_RCC_I2C8_CLKAM_ENABLE()             SET_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8AMEN)
#endif /* RCC_I2C8CFGR_I2C8AMEN */

#if defined(RCC_ADF1CFGR_ADF1AMEN)
#define __HAL_RCC_ADF1_CLKAM_ENABLE()             SET_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1AMEN)
#endif /* RCC_ADF1CFGR_ADF1AMEN */

#if defined(RCC_IWDG5CFGR_IWDG5AMEN)
#define __HAL_RCC_IWDG5_CLKAM_ENABLE()            SET_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5AMEN)
#endif /* RCC_IWDG5CFGR_IWDG5AMEN */

#if defined(RCC_WWDG2CFGR_WWDG2AMEN)
#define __HAL_RCC_WWDG2_CLKAM_ENABLE()            SET_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2AMEN)
#endif /* RCC_WWDG2CFGR_WWDG2AMEN */

#if defined(RCC_I3C4CFGR_I3C4AMEN)
#define __HAL_RCC_I3C4_CLKAM_ENABLE()             SET_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4AMEN)
#endif /* RCC_I3C4CFGR_I3C4AMEN */

/* Clock autonomous mode disable macros */
#if defined(RCC_C3CFGR_C3AMEN)
#define __HAL_RCC_C3_CLKAM_DISABLE()              CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_C3AMEN)
#endif /* RCC_C3CFGR_C3AMEN */

#if defined(RCC_LPSRAM1CFGR_LPSRAM1AMEN)
#define __HAL_RCC_LPSRAM1_CLKAM_DISABLE()         CLEAR_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1AMEN)
#endif /* RCC_LPSRAM1CFGR_LPSRAM1AMEN */

#if defined(RCC_LPSRAM2CFGR_LPSRAM2AMEN)
#define __HAL_RCC_LPSRAM2_CLKAM_DISABLE()         CLEAR_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2AMEN)
#endif /* RCC_LPSRAM2CFGR_LPSRAM2AMEN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3AMEN)
#define __HAL_RCC_LPSRAM3_CLKAM_DISABLE()         CLEAR_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3AMEN)
#endif /* RCC_LPSRAM3CFGR_LPSRAM3AMEN */

#if defined(RCC_GPIOZCFGR_GPIOZAMEN)
#define __HAL_RCC_GPIOZ_CLKAM_DISABLE()           CLEAR_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZAMEN)
#endif /* RCC_GPIOZCFGR_GPIOZAMEN */

#if defined(RCC_LPDMACFGR_LPDMAAMEN)
#define __HAL_RCC_LPDMA_CLKAM_DISABLE()           CLEAR_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMAAMEN)
#endif /* RCC_LPDMACFGR_LPDMAAMEN */

#if defined(RCC_HSEMCFGR_HSEMAMEN)
#define __HAL_RCC_HSEM_CLKAM_DISABLE()            CLEAR_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMAMEN)
#endif /* RCC_HSEMCFGR_HSEMAMEN */

#if defined(RCC_IPCC2CFGR_IPCC2AMEN)
#define __HAL_RCC_IPCC2_CLKAM_DISABLE()           CLEAR_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2AMEN)
#endif /* RCC_IPCC2CFGR_IPCC2AMEN */

#if defined(RCC_RTCCFGR_RTCAMEN)
#define __HAL_RCC_RTC_CLKAM_DISABLE()             CLEAR_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCAMEN)
#endif /* RCC_RTCCFGR_RTCAMEN */

#if defined(RCC_LPTIM3CFGR_LPTIM3AMEN)
#define __HAL_RCC_LPTIM3_CLKAM_DISABLE()          CLEAR_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3AMEN)
#endif /* RCC_LPTIM3CFGR_LPTIM3AMEN */

#if defined(RCC_LPTIM4CFGR_LPTIM4AMEN)
#define __HAL_RCC_LPTIM4_CLKAM_DISABLE()          CLEAR_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4AMEN)
#endif /* RCC_LPTIM4CFGR_LPTIM4AMEN */

#if defined(RCC_LPTIM5CFGR_LPTIM5AMEN)
#define __HAL_RCC_LPTIM5_CLKAM_DISABLE()          CLEAR_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5AMEN)
#endif /* RCC_LPTIM5CFGR_LPTIM5AMEN */

#if defined(RCC_SPI8CFGR_SPI8AMEN)
#define __HAL_RCC_SPI8_CLKAM_DISABLE()            CLEAR_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8AMEN)
#endif /* RCC_SPI8CFGR_SPI8AMEN */

#if defined(RCC_LPUART1CFGR_LPUART1AMEN)
#define __HAL_RCC_LPUART1_CLKAM_DISABLE()         CLEAR_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1AMEN)
#endif /* RCC_LPUART1CFGR_LPUART1AMEN */

#if defined(RCC_I2C8CFGR_I2C8AMEN)
#define __HAL_RCC_I2C8_CLKAM_DISABLE()            CLEAR_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8AMEN)
#endif /* RCC_I2C8CFGR_I2C8AMEN */

#if defined(RCC_ADF1CFGR_ADF1AMEN)
#define __HAL_RCC_ADF1_CLKAM_DISABLE()            CLEAR_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1AMEN)
#endif /* RCC_ADF1CFGR_ADF1AMEN */

#if defined(RCC_IWDG5CFGR_IWDG5AMEN)
#define __HAL_RCC_IWDG5_CLKAM_DISABLE()           CLEAR_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5AMEN)
#endif /* RCC_IWDG5CFGR_IWDG5AMEN */

#if defined(RCC_WWDG2CFGR_WWDG2AMEN)
#define __HAL_RCC_WWDG2_CLKAM_DISABLE()           CLEAR_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2AMEN)
#endif /*RCC_WWDG2CFGR_WWDG2AMEN*/

#if defined(RCC_I3C4CFGR_I3C4AMEN)
#define __HAL_RCC_I3C4_CLKAM_DISABLE()            CLEAR_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4AMEN)
#endif /* RCC_I3C4CFGR_I3C4AMEN */

/* Peripheral clock status macros */
#if defined(RCC_VDERAMCFGR_VDERAMEN)
#define __HAL_RCC_VDERAM_IS_CLK_ENABLED()         (READ_BIT(RCC->VDERAMCFGR, RCC_VDERAMCFGR_VDERAMEN) != 0U)
#endif /* RCC_VDERAMCFGR_VDERAMEN */

#define __HAL_RCC_SERC_IS_CLK_ENABLED()           (READ_BIT(RCC->SERCCFGR, RCC_SERCCFGR_SERCEN) != 0U)
#define __HAL_RCC_OSPIIOM_IS_CLK_ENABLED()        (READ_BIT(RCC->OSPIIOMCFGR, RCC_OSPIIOMCFGR_OSPIIOMEN) != 0U)
#define __HAL_RCC_VDEC_IS_CLK_ENABLED()           (READ_BIT(RCC->VDECCFGR, RCC_VDECCFGR_VDECEN) != 0U)

#if defined(RCC_VENCCFGR_VENCEN)
#define __HAL_RCC_VENC_IS_CLK_ENABLED()           (READ_BIT(RCC->VENCCFGR, RCC_VENCCFGR_VENCEN) != 0U)
#endif /* RCC_VENCCFGR_VENCEN */

#if defined(RCC_C3CFGR_C3EN)
#define __HAL_RCC_C3_IS_CLK_ENABLED()             (READ_BIT(RCC->C3CFGR, RCC_C3CFGR_C3EN) != 0U)
#endif /* RCC_C3CFGR_C3EN */

#define __HAL_RCC_SYSRAM_IS_CLK_ENABLED()         (READ_BIT(RCC->SYSRAMCFGR, RCC_SYSRAMEN) != 0U)
#define __HAL_RCC_SRAM1_IS_CLK_ENABLED()          (READ_BIT(RCC->SRAM1CFGR, RCC_SRAM1CFGR_SRAM1EN) != 0U)

#if defined(RCC_SRAM2CFGR_SRAM2EN)
#define __HAL_RCC_SRAM2_IS_CLK_ENABLED()          (READ_BIT(RCC->SRAM2CFGR, RCC_SRAM2CFGR_SRAM2EN) != 0U)
#endif /* RCC_SRAM2CFGR_SRAM2EN */

#define __HAL_RCC_RETRAM_IS_CLK_ENABLED()         (READ_BIT(RCC->RETRAMCFGR, RCC_RETRAMCFGR_RETRAMEN) != 0U)
#define __HAL_RCC_BKPSRAM_IS_CLK_ENABLED()        (READ_BIT(RCC->BKPSRAM, RCC_BKPSRAMCFGR_BKPSRAMEN) != 0U)

#if defined(RCC_LPSRAM1CFGR_LPSRAM1EN)
#define __HAL_RCC_LPSRAM1_IS_CLK_ENABLED()        (READ_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1EN) != 0U)
#endif /* RCC_LPSRAM1CFGR_LPSRAM1EN */

#if defined(RCC_LPSRAM2CFGR_LPSRAM12EN)
#define __HAL_RCC_LPSRAM2_IS_CLK_ENABLED()        (READ_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2EN) != 0U)
#endif /* RCC_LPSRAM2CFGR_LPSRAM2EN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3EN)
#define __HAL_RCC_LPSRAM3_IS_CLK_ENABLED()        (READ_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3EN) != 0U)
#endif /* RCC_LPSRAM3CFGR_LPSRAM3EN */

#define __HAL_RCC_OSPI1_IS_CLK_ENABLED()          (READ_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1EN) != 0U)

#if defined(RCC_OSPI2CFGR_OSPI2EN)
#define __HAL_RCC_OSPI2_IS_CLK_ENABLED()          (READ_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2EN) != 0U)
#endif /* RCC_OSPI2CFGR_OSPI2EN */

#if defined(RCC_STMCFGR_STMLPEN)
#define __HAL_RCC_STM_IS_CLK_ENABLED()         (READ_BIT(RCC->STMCFGR, RCC_STMCFGR_STMEN) != 0U)
#endif /* RCC_STMCFGR_STMEN */

#define __HAL_RCC_ETR_IS_CLK_ENABLED()            (READ_BIT(RCC->ETRCFGR, RCC_ETRCFGR_ETREN) != 0U)
#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxEN) != 0U)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxEN) != 0U)
#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxEN) != 0U)
#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxEN) != 0U)
#define __HAL_RCC_GPIOE_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxEN) != 0U)
#define __HAL_RCC_GPIOF_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxEN) != 0U)
#define __HAL_RCC_GPIOG_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxEN) != 0U)
#define __HAL_RCC_GPIOH_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxEN) != 0U)
#define __HAL_RCC_GPIOI_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxEN) != 0U)

#if defined(RCC_GPIOJCFGR_GPIOxEN)
#define __HAL_RCC_GPIOJ_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxEN) != 0U)
#endif /* RCC_GPIOJCFGR_GPIOxEN */

#if defined(RCC_GPIOKCFGR_GPIOxEN)
#define __HAL_RCC_GPIOK_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxEN) != 0U)
#endif /* RCC_GPIOKCFGR_GPIOxEN */

#define __HAL_RCC_GPIOZ_IS_CLK_ENABLED()          (READ_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZEN) != 0U)
#define __HAL_RCC_HPDMA1_IS_CLK_ENABLED()         (READ_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1EN) != 0U)
#define __HAL_RCC_HPDMA2_IS_CLK_ENABLED()         (READ_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2EN) != 0U)
#define __HAL_RCC_HPDMA3_IS_CLK_ENABLED()         (READ_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3EN) != 0U)

#if defined(RCC_LPDMACFGR_LPDMAEN)
#define __HAL_RCC_LPDMA_IS_CLK_ENABLED()          (READ_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMAEN) != 0U)
#endif /* RCC_LPDMACFGR_LPDMAEN */

#if defined(RCC_HSEMCFGR_HSEMEN)
#define __HAL_RCC_HSEM_IS_CLK_ENABLED()           (READ_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMEN) != 0U)
#endif /* RCC_HSEMCFGR_HSEMEN */

#define __HAL_RCC_IPCC1_IS_CLK_ENABLED()          (READ_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1EN) != 0U)

#if defined(RCC_IPCC2CFGR_IPCC2EN)
#define __HAL_RCC_IPCC2_IS_CLK_ENABLED()          (READ_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2EN) != 0U)
#endif /* RCC_IPCC2CFGR_IPCC2LPEN */

#define __HAL_RCC_RTC_IS_CLK_ENABLED()            (READ_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCEN) != 0U)
#define __HAL_RCC_SYSCPU1_IS_CLK_ENABLED()        (READ_BIT(RCC->SYSCPU1CFGR, RCC_SYSCPU1CFGR_SYSCPU1EN) != 0U)
#define __HAL_RCC_IS2M_IS_CLK_ENABLED()           (READ_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MEN) != 0U)
#define __HAL_RCC_TIM1_IS_CLK_ENABLED()           (READ_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1EN) != 0U)
#define __HAL_RCC_TIM2_IS_CLK_ENABLED()           (READ_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2EN) != 0U)
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()           (READ_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3EN) != 0U)
#define __HAL_RCC_TIM4_IS_CLK_ENABLED()           (READ_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4EN) != 0U)
#define __HAL_RCC_TIM5_IS_CLK_ENABLED()           (READ_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5EN) != 0U)
#define __HAL_RCC_TIM6_IS_CLK_ENABLED()           (READ_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6EN) != 0U)
#define __HAL_RCC_TIM7_IS_CLK_ENABLED()           (READ_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7EN) != 0U)
#define __HAL_RCC_TIM8_IS_CLK_ENABLED()           (READ_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8EN) != 0U)
#define __HAL_RCC_TIM10_IS_CLK_ENABLED()          (READ_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10EN) != 0U)
#define __HAL_RCC_TIM11_IS_CLK_ENABLED()          (READ_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11EN) != 0U)
#define __HAL_RCC_TIM12_IS_CLK_ENABLED()          (READ_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12EN) != 0U)
#define __HAL_RCC_TIM13_IS_CLK_ENABLED()          (READ_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13EN) != 0U)
#define __HAL_RCC_TIM14_IS_CLK_ENABLED()          (READ_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14EN) != 0U)
#define __HAL_RCC_TIM15_IS_CLK_ENABLED()          (READ_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15EN) != 0U)
#define __HAL_RCC_TIM16_IS_CLK_ENABLED()          (READ_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16EN) != 0U)
#define __HAL_RCC_TIM17_IS_CLK_ENABLED()          (READ_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17EN) != 0U)

#if defined(RCC_TIM20CFGR_TIM20EN)
#define __HAL_RCC_TIM20_IS_CLK_ENABLED()          (READ_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20EN) != 0U)
#endif /* RCC_TIM20CFGR_TIM20EN */

#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()         (READ_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1EN) != 0U)
#define __HAL_RCC_LPTIM2_IS_CLK_ENABLED()         (READ_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2EN) != 0U)
#define __HAL_RCC_LPTIM3_IS_CLK_ENABLED()         (READ_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3EN) != 0U)
#define __HAL_RCC_LPTIM4_IS_CLK_ENABLED()         (READ_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4EN) != 0U)
#define __HAL_RCC_LPTIM5_IS_CLK_ENABLED()         (READ_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5EN) != 0U)
#define __HAL_RCC_SPI1_IS_CLK_ENABLED()           (READ_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1EN) != 0U)
#define __HAL_RCC_SPI2_IS_CLK_ENABLED()           (READ_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2EN) != 0U)
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()           (READ_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3EN) != 0U)
#define __HAL_RCC_SPI4_IS_CLK_ENABLED()           (READ_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4EN) != 0U)
#define __HAL_RCC_SPI5_IS_CLK_ENABLED()           (READ_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5EN) != 0U)
#define __HAL_RCC_SPI6_IS_CLK_ENABLED()           (READ_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6EN) != 0U)

#if defined(RCC_SPI7CFGR_SPI7EN)
#define __HAL_RCC_SPI7_IS_CLK_ENABLED()           (READ_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7EN) != 0U)
#endif /* RCC_SPI7CFGR_SPI7EN */

#if defined(RCC_SPI8CFGR_SPI8EN)
#define __HAL_RCC_SPI8_IS_CLK_ENABLED()           (READ_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8EN) != 0U)
#endif /* RCC_SPI8CFGR_SPI8EN */

#define __HAL_RCC_SPDIFRX_IS_CLK_ENABLED()        (READ_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXEN) != 0U)
#define __HAL_RCC_USART1_IS_CLK_ENABLED()         (READ_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1EN) != 0U)
#define __HAL_RCC_USART2_IS_CLK_ENABLED()         (READ_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2EN) != 0U)
#define __HAL_RCC_USART3_IS_CLK_ENABLED()         (READ_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3EN) != 0U)
#define __HAL_RCC_UART4_IS_CLK_ENABLED()          (READ_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4EN) != 0U)
#define __HAL_RCC_UART5_IS_CLK_ENABLED()          (READ_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5EN) != 0U)
#define __HAL_RCC_USART6_IS_CLK_ENABLED()         (READ_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6EN) != 0U)
#define __HAL_RCC_UART7_IS_CLK_ENABLED()          (READ_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7EN) != 0U)

#if defined(RCC_UART8CFGR_UART8EN)
#define __HAL_RCC_UART8_IS_CLK_ENABLED()          (READ_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8EN) != 0U)
#endif /* RCC_UART8CFGR_UART8EN */

#if defined(RCC_UART9CFGR_UART9EN)
#define __HAL_RCC_UART9_IS_CLK_ENABLED()          (READ_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9EN) != 0U)
#endif /* RCC_UART9CFGR_UART9EN */

#define __HAL_RCC_LPUART1_IS_CLK_ENABLED()        (READ_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1EN) != 0U)
#define __HAL_RCC_I2C1_IS_CLK_ENABLED()           (READ_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1EN) != 0U)
#define __HAL_RCC_I2C2_IS_CLK_ENABLED()           (READ_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2EN) != 0U)
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()           (READ_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3EN) != 0U)

#if defined(RCC_I2C4CFGR_I2C4EN)
#define __HAL_RCC_I2C4_IS_CLK_ENABLED()           (READ_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4EN) != 0U)
#endif /* RCC_I2C4CFGR_I2C4EN */

#if defined(RCC_I2C5CFGR_I2C5EN)
#define __HAL_RCC_I2C5_IS_CLK_ENABLED()           (READ_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5EN) != 0U)
#endif /* RCC_I2C5CFGR_I2C5EN */

#if defined(RCC_I2C6CFGR_I2C6EN)
#define __HAL_RCC_I2C6_IS_CLK_ENABLED()           (READ_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6EN) != 0U)
#endif /* RCC_I2C6CFGR_I2C6EN */

#if defined(RCC_I2C7CFGR_I2C7EN)
#define __HAL_RCC_I2C7_IS_CLK_ENABLED()           (READ_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7EN) != 0U)
#endif /* RCC_I2C7CFGR_I2C7EN */

#if defined(RCC_I2C8CFGR_I2C8EN)
#define __HAL_RCC_I2C8_IS_CLK_ENABLED()           (READ_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8EN) != 0U)
#endif /* RCC_I2C8CFGR_I2C8EN */

#define __HAL_RCC_SAI1_IS_CLK_ENABLED()           (READ_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1EN) != 0U)
#define __HAL_RCC_SAI2_IS_CLK_ENABLED()           (READ_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2EN) != 0U)
#define __HAL_RCC_SAI3_IS_CLK_ENABLED()           (READ_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3EN) != 0U)
#define __HAL_RCC_SAI4_IS_CLK_ENABLED()           (READ_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4EN) != 0U)
#define __HAL_RCC_MDF1_IS_CLK_ENABLED()           (READ_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1EN) != 0U)
#define __HAL_RCC_ADF1_IS_CLK_ENABLED()           (READ_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1EN) != 0U)
#define __HAL_RCC_FDCAN_IS_CLK_ENABLED()          (READ_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANEN) != 0U)
#define __HAL_RCC_HDP_IS_CLK_ENABLED()            (READ_BIT(RCC->HDPCFGR, RCC_HDPCFGR_HDPEN) != 0U)

#if defined(RCC_ADC1CFGR_ADC1EN)
#define __HAL_RCC_ADC1_IS_CLK_ENABLED()           (READ_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1EN) != 0U)
#endif /* RCC_ADC1CFGR_ADC1EN */

#if defined(RCC_ADC2CFGR_ADC2EN)
#define __HAL_RCC_ADC2_IS_CLK_ENABLED()           (READ_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2EN) != 0U)
#endif /* RCC_ADC2CFGR_ADC2EN */

#if defined(RCC_ADC12CFGR_ADC12EN)
#define __HAL_RCC_ADC12_IS_CLK_ENABLED()          (READ_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12EN) != 0U)
#endif /* RCC_ADC12CFGR_ADC12EN */

#if defined(RCC_ADC3CFGR_ADC3EN)
#define __HAL_RCC_ADC3_IS_CLK_ENABLED()           (READ_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3EN) != 0U)
#endif /*RCC_ADC3CFGR_ADC3EN */

#define __HAL_RCC_ETH1_IS_CLK_ENABLED()           (READ_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1EN) != 0U)
#define __HAL_RCC_ETH1MAC_IS_CLK_ENABLED()        (READ_BIT(RCC->ETH1MACCFGR, RCC_ETH1MACCFGR_ETH1MACEN) != 0U)
#define __HAL_RCC_ETH1TX_IS_CLK_ENABLED()         (READ_BIT(RCC->ETH1TXCFGR, RCC_ETH1TXCFGR_ETH1TXEN) != 0U)
#define __HAL_RCC_ETH1RX_IS_CLK_ENABLED()         (READ_BIT(RCC->ETH1RXCFGR, RCC_ETH1RXCFGR_ETH1RXEN) != 0U)
#define __HAL_RCC_ETH2_IS_CLK_ENABLED()           (READ_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2EN) != 0U)
#define __HAL_RCC_ETH2MAC_IS_CLK_ENABLED()        (READ_BIT(RCC->ETH2MACCFGR, RCC_ETH2MACCFGR_ETH2MACEN) != 0U)
#define __HAL_RCC_ETH2TX_IS_CLK_ENABLED()         (READ_BIT(RCC->ETH2TXCFGR, RCC_ETH2TXCFGR_ETH2TXEN) != 0U)
#define __HAL_RCC_ETH2RX_IS_CLK_ENABLED()         (READ_BIT(RCC->ETH2RXCFGR, RCC_ETH2RXCFGR_ETH2RXEN) != 0U)


#define __HAL_RCC_USB2PHY1_IS_CLK_ENABLED()       (READ_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1EN) != 0U)
#define __HAL_RCC_USB2PHY2_IS_CLK_ENABLED()       (READ_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2EN) != 0U)

#if defined(RCC_USB3DRDCFGR_USB3DRDEN)
#define __HAL_RCC_USB3DRD_IS_CLK_ENABLED()        (READ_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDEN) != 0U)
#endif /* RCC_USB3DRDCFGR_USB3DRDEN */

#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN)
#define __HAL_RCC_USB3PCIEPHY_IS_CLK_ENABLED()    (READ_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN) \
                                                   != 0U)
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN */

#if defined(RCC_PCIECFGR_PCIEEN)
#define __HAL_RCC_PCIE_IS_CLK_ENABLED()           (READ_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIEEN) != 0U)
#endif /* RCC_PCIECFGR_PCIEEN */

#if defined(RCC_UCPDCFGR_UCPDEN)
#define __HAL_RCC_UCPD1_IS_CLK_ENABLED()          (READ_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDEN) != 0U)
#endif /* RCC_UCPDCFGR_UCPDEN */

#define __HAL_RCC_FMC_IS_CLK_ENABLED()            (READ_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCEN) != 0U)
#define __HAL_RCC_SDMMC1_IS_CLK_ENABLED()         (READ_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1EN) != 0U)
#define __HAL_RCC_SDMMC2_IS_CLK_ENABLED()         (READ_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2EN) != 0U)
#define __HAL_RCC_SDMMC3_IS_CLK_ENABLED()         (READ_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3EN) != 0U)
#define __HAL_RCC_GPU_IS_CLK_ENABLED()            (READ_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPUEN) != 0U)
#define __HAL_RCC_LTDC_IS_CLK_ENABLED()           (READ_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCEN) != 0U)

#if defined(RCC_DSICFGR_DSIEN)
#define __HAL_RCC_DSI_IS_CLK_ENABLED()            (READ_BIT(RCC->DSICFGR, RCC_DSICFGR_DSIEN) != 0U)
#endif /* RCC_DSICFGR_DSIEN */

#define __HAL_RCC_LVDS_IS_CLK_ENABLED()           (READ_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSEN) != 0U)

#if defined(RCC_CSICFGR_CSIEN)
#define __HAL_RCC_CSI_IS_CLK_ENABLED()            (READ_BIT(RCC->CSICFGR, RCC_CSICFGR_CSIEN) != 0U)
#endif /* RCC_CSICFGR_CSIEN */

#if defined(RCC_CSI2CFGR_CSI2EN)
#define __HAL_RCC_CSI2_IS_CLK_ENABLED()           (READ_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2EN) != 0U)
#endif /* RCC_CSI2CFGR_CSI2EN */

#define __HAL_RCC_DCMIPP_IS_CLK_ENABLED()         (READ_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPEN) != 0U)

#if defined(RCC_DCMIPSSICFGR_DCMIPSSIEN)
#define __HAL_RCC_DCMIPSSI_IS_CLK_ENABLED()       (READ_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSIEN) != 0U)
#endif /*RCC_DCMIPSSICFGR_DCMIPSSIEN*/

#if defined(RCC_CCICFGR_CCIEN)
#define __HAL_RCC_CCI_IS_CLK_ENABLED()            (READ_BIT(RCC->CCICFGR, RCC_CCICFGR_CCIEN) != 0U)
#endif /* RCC_CCICFGR_CCIEN */

#if defined(RCC_RNGCFGR_RNGEN)
#define __HAL_RCC_RNG_IS_CLK_ENABLED()            (READ_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGEN) != 0U)
#endif /* RCC_RNGCFGR_RNGEN */

#if defined(RCC_RNG1CFGR_RNG1EN)
#define __HAL_RCC_RNG1_IS_CLK_ENABLED()           (READ_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1EN) != 0U)
#endif /* RCC_RNG1CFGR_RNG1EN */

#if defined(RCC_RNG2CFGR_RNG2EN)
#define __HAL_RCC_RNG2_IS_CLK_ENABLED()           (READ_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2EN) != 0U)
#endif /* RCC_RNG2CFGR_RNG2EN */

#define __HAL_RCC_PKA_IS_CLK_ENABLED()            (READ_BIT(RCC->PKACFGR, RCC_PKACFGR_PKAEN) != 0U)
#define __HAL_RCC_SAES_IS_CLK_ENABLED()           (READ_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESEN) != 0U)

#if defined(RCC_HASHCFGR_HASHEN)
#define __HAL_RCC_HASH_IS_CLK_ENABLED()           (READ_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHEN) != 0U)
#endif /* RCC_HASHCFGR_HASHEN */

#if defined(RCC_HASH1CFGR_HASH1EN)
#define __HAL_RCC_HASH1_IS_CLK_ENABLED()          (READ_BIT(RCC->HASH1CFGR, RCC_HASHCFGR_HASHEN) != 0U)
#endif /* RCC_HASH1CFGR_HASH1EN */

#if defined(RCC_HASH2CFGR_HASH2EN)
#define __HAL_RCC_HASH2_IS_CLK_ENABLED()          (READ_BIT(RCC->HASH2CFGR, RCC_HASHCFGR_HASHEN) != 0U)
#endif /* RCC_HASH2CFGR_HASH2EN */

#define __HAL_RCC_CRYP1_IS_CLK_ENABLED()          (READ_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1EN) != 0U)
#define __HAL_RCC_CRYP2_IS_CLK_ENABLED()          (READ_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2EN) != 0U)
#define __HAL_RCC_IWDG1_IS_CLK_ENABLED()          (READ_BIT(RCC->IWDG1CFGR, RCC_IWDG1CFGR_IWDG1EN) != 0U)
#define __HAL_RCC_IWDG2_IS_CLK_ENABLED()          (READ_BIT(RCC->IWDG2CFGR, RCC_IWDG2CFGR_IWDG2EN) != 0U)
#define __HAL_RCC_IWDG3_IS_CLK_ENABLED()          (READ_BIT(RCC->IWDG3CFGR, RCC_IWDG3CFGR_IWDG3EN) != 0U)
#define __HAL_RCC_IWDG4_IS_CLK_ENABLED()          (READ_BIT(RCC->IWDG4CFGR, RCC_IWDG4CFGR_IWDG4EN) != 0U)

#if defined(RCC_IWDG5CFGR_IWDG5EN)
#define __HAL_RCC_IWDG5_IS_CLK_ENABLED()          (READ_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5EN) != 0U)
#endif /* RCC_IWDG5CFGR_IWDG5EN */

#define __HAL_RCC_WWDG1_IS_CLK_ENABLED()          (READ_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1EN) != 0U)

#if defined(RCC_WWDG2CFGR_WWDG2EN)
#define __HAL_RCC_WWDG2_IS_CLK_ENABLED()          (READ_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2EN) != 0U)
#endif /* RCC_WWDG2CFGR_WWDG2EN */

#define __HAL_RCC_BUSPERFM_IS_CLK_ENABLED()       (READ_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFM) != 0U)
#define __HAL_RCC_VREF_IS_CLK_ENABLED()           (READ_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFEN) != 0U)
#define __HAL_RCC_TMPSENS_IS_CLK_ENABLED()        (READ_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSEN) != 0U)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()            (READ_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCEN) != 0U)
#define __HAL_RCC_BSEC_IS_CLK_ENABLED()           (READ_BIT(RCC->BSECCFGR, RCC_BSECCFGR_BSECEN) != 0U)
#define __HAL_RCC_GICV2_IS_CLK_ENABLED()          (READ_BIT(RCC->GICV2CFGR, RCC_GICV2CFGR_GICV2EN) != 0U)
#define __HAL_RCC_I3C1_IS_CLK_ENABLED()           (READ_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1EN) != 0U)
#define __HAL_RCC_I3C2_IS_CLK_ENABLED()           (READ_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2EN) != 0U)
#define __HAL_RCC_I3C3_IS_CLK_ENABLED()           (READ_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3EN) != 0U)

#if defined(RCC_I3C4CFGR_I3C4EN)
#define __HAL_RCC_I3C4_IS_CLK_ENABLED()           (READ_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4EN) != 0U)
#endif /* RCC_I3C4CFGR_I3C4EN */

/* for API backward compatibility */
#if defined(RCC_DCMIPSSICFGR_DCMIPSSIEN)
#define __HAL_RCC_DCMI_IS_CLK_ENABLED()           __HAL_RCC_DCMIPSSI_IS_CLK_ENABLED()
#define __HAL_RCC_PSSI_IS_CLK_ENABLED()           __HAL_RCC_DCMIPSSI_IS_CLK_ENABLED()
#endif /* RCC_DCMIPSSICFGR_DCMIPSSIEN */

#if defined(RCC_CCICFGR_CCIEN)
#define __HAL_RCC_DCMI_IS_CLK_ENABLED()           __HAL_RCC_CCI_IS_CLK_ENABLED()
#define __HAL_RCC_PSSI_IS_CLK_ENABLED()           __HAL_RCC_CCI_IS_CLK_ENABLED()
#endif /* RCC_CCICFGR_CCIEN */

#define __HAL_RCC_OTFDEC1_IS_CLK_ENABLED()        __HAL_RCC_OSPI1_IS_CLK_ENABLED()

#if defined(RCC_OSPI2CFGR_OSPI2EN)
#define __HAL_RCC_OTFDEC2_IS_CLK_ENABLED()        __HAL_RCC_OSPI2_IS_CLK_ENABLED()
#endif /* RCC_OSPI2CFGR_OSPI2EN */

/* Reset force macros */

#define __HAL_RCC_SERC_FORCE_RESET()              SET_BIT(RCC->SERCCFGR, RCC_SERCCFGR_SERCRST)
#define __HAL_RCC_OSPIIOM_FORCE_RESET()           SET_BIT(RCC->OSPIIOMCFGR, RCC_OSPIIOMCFGR_OSPIIOMRST)
#define __HAL_RCC_ETHSW_FORCE_RESET()             SET_BIT(RCC->ETHSWCFGR, RCC_ETHSWCFGR_ETHSWRST)
#define __HAL_RCC_VDEC_FORCE_RESET()              SET_BIT(RCC->VDECCFGR, RCC_VDECCFGR_VDECRST)

#if defined(RCC_VENCCFGR_VENCRST)
#define __HAL_RCC_VENC_FORCE_RESET()              SET_BIT(RCC->VENCCFGR, RCC_VENCCFGR_VENCRST)
#endif /* RCC_VENCCFGR_VENCRST */

#if defined(RCC_C3CFGR_C3RST)
#define __HAL_RCC_C3_FORCE_RESET()                SET_BIT(RCC->C3CFGR, RCC_C3CFGR_C3RST)
#endif /* RCC_C3CFGR_C3RST */

#define __HAL_RCC_OSPI1_FORCE_RESET()             SET_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1RST)

#if defined(RCC_OSPI2CFGR_OSPI2RST)
#define __HAL_RCC_OSPI2_FORCE_RESET()             SET_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2RST)
#endif /* RCC_OSPI2CFGR_OSPI2RST */

#define __HAL_RCC_OTFDEC1_FORCE_RESET()           SET_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OTFDEC1RST)

#if defined(RCC_OSPI2CFGR_OSPI2RST)
#define __HAL_RCC_OTFDEC2_FORCE_RESET()           SET_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OTFDEC2RST)
#endif /* RCC_OSPI2CFGR_OSPI2RST */

#define __HAL_RCC_GPIOA_FORCE_RESET()             SET_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxRST)
#define __HAL_RCC_GPIOB_FORCE_RESET()             SET_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxRST)
#define __HAL_RCC_GPIOC_FORCE_RESET()             SET_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxRST)
#define __HAL_RCC_GPIOD_FORCE_RESET()             SET_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxRST)
#define __HAL_RCC_GPIOE_FORCE_RESET()             SET_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxRST)
#define __HAL_RCC_GPIOF_FORCE_RESET()             SET_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxRST)
#define __HAL_RCC_GPIOG_FORCE_RESET()             SET_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxRST)
#define __HAL_RCC_GPIOH_FORCE_RESET()             SET_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxRST)
#define __HAL_RCC_GPIOI_FORCE_RESET()             SET_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxRST)

#if defined(RCC_GPIOJCFGR_GPIOxRST)
#define __HAL_RCC_GPIOJ_FORCE_RESET()             SET_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxRST)
#endif /* RCC_GPIOJCFGR_GPIOxRST */

#if defined(RCC_GPIOKCFGR_GPIOxRST)
#define __HAL_RCC_GPIOK_FORCE_RESET()             SET_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxRST)
#endif /* RCC_GPIOKCFGR_GPIOxRST */

#define __HAL_RCC_GPIOZ_FORCE_RESET()             SET_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZRST)
#define __HAL_RCC_HPDMA1_FORCE_RESET()            SET_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1RST)
#define __HAL_RCC_HPDMA2_FORCE_RESET()            SET_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2RST)
#define __HAL_RCC_HPDMA3_FORCE_RESET()            SET_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3RST)

#if defined(RCC_LPDMACFGR_LPDMARST)
#define __HAL_RCC_LPDMA_FORCE_RESET()             SET_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMARST)
#endif /* RCC_LPDMACFGR_LPDMARST */

#if defined(RCC_HSEMCFGR_HSEMRST)
#define __HAL_RCC_HSEM_FORCE_RESET()              SET_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMRST)
#endif /* RCC_HSEMCFGR_HSEMRST */

#define __HAL_RCC_IPCC1_FORCE_RESET()             SET_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1RST)

#if defined(RCC_IPCC2CFGR_IPCC2RST)
#define __HAL_RCC_IPCC2_FORCE_RESET()             SET_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2RST)
#endif /* RCC_IPCC2CFGR_IPCC2RST */

#define __HAL_RCC_IS2M_FORCE_RESET()              SET_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MRST)
#define __HAL_RCC_TIM1_FORCE_RESET()              SET_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1RST)
#define __HAL_RCC_TIM2_FORCE_RESET()              SET_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2RST)
#define __HAL_RCC_TIM3_FORCE_RESET()              SET_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3RST)
#define __HAL_RCC_TIM4_FORCE_RESET()              SET_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4RST)
#define __HAL_RCC_TIM5_FORCE_RESET()              SET_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5RST)
#define __HAL_RCC_TIM6_FORCE_RESET()              SET_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6RST)
#define __HAL_RCC_TIM7_FORCE_RESET()              SET_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7RST)
#define __HAL_RCC_TIM8_FORCE_RESET()              SET_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8RST)
#define __HAL_RCC_TIM10_FORCE_RESET()             SET_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10RST)
#define __HAL_RCC_TIM11_FORCE_RESET()             SET_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11RST)
#define __HAL_RCC_TIM12_FORCE_RESET()             SET_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12RST)
#define __HAL_RCC_TIM13_FORCE_RESET()             SET_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13RST)
#define __HAL_RCC_TIM14_FORCE_RESET()             SET_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14RST)
#define __HAL_RCC_TIM15_FORCE_RESET()             SET_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15RST)
#define __HAL_RCC_TIM16_FORCE_RESET()             SET_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16RST)
#define __HAL_RCC_TIM17_FORCE_RESET()             SET_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17RST)

#if defined(RCC_TIM20CFGR_TIM20RST)
#define __HAL_RCC_TIM20_FORCE_RESET()             SET_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20RST)
#endif /* RCC_TIM20CFGR_TIM20RST */

#define __HAL_RCC_LPTIM1_FORCE_RESET()            SET_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1RST)
#define __HAL_RCC_LPTIM2_FORCE_RESET()            SET_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2RST)
#define __HAL_RCC_LPTIM3_FORCE_RESET()            SET_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3RST)
#define __HAL_RCC_LPTIM4_FORCE_RESET()            SET_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4RST)
#define __HAL_RCC_LPTIM5_FORCE_RESET()            SET_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5RST)
#define __HAL_RCC_SPI1_FORCE_RESET()              SET_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1RST)
#define __HAL_RCC_SPI2_FORCE_RESET()              SET_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2RST)
#define __HAL_RCC_SPI3_FORCE_RESET()              SET_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3RST)
#define __HAL_RCC_SPI4_FORCE_RESET()              SET_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4RST)
#define __HAL_RCC_SPI5_FORCE_RESET()              SET_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5RST)
#define __HAL_RCC_SPI6_FORCE_RESET()              SET_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6RST)

#if defined(RCC_SPI7CFGR_SPI7RST)
#define __HAL_RCC_SPI7_FORCE_RESET()              SET_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7RST)
#endif /* RCC_SPI7CFGR_SPI7RST */

#if defined(RCC_SPI8CFGR_SPI8RST)
#define __HAL_RCC_SPI8_FORCE_RESET()              SET_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8RST)
#endif /* RCC_SPI8CFGR_SPI8RST */

#define __HAL_RCC_SPDIFRX_FORCE_RESET()           SET_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXRST)
#define __HAL_RCC_USART1_FORCE_RESET()            SET_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1RST)
#define __HAL_RCC_USART2_FORCE_RESET()            SET_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2RST)
#define __HAL_RCC_USART3_FORCE_RESET()            SET_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3RST)
#define __HAL_RCC_UART4_FORCE_RESET()             SET_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4RST)
#define __HAL_RCC_UART5_FORCE_RESET()             SET_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5RST)
#define __HAL_RCC_USART6_FORCE_RESET()            SET_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6RST)
#define __HAL_RCC_UART7_FORCE_RESET()             SET_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7RST)

#if defined(RCC_UART8CFGR_UART8RST)
#define __HAL_RCC_UART8_FORCE_RESET()             SET_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8RST)
#endif /* RCC_UART8CFGR_UART8RST */

#if defined(RCC_UART9CFGR_UART9RST)
#define __HAL_RCC_UART9_FORCE_RESET()             SET_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9RST)
#endif /* RCC_UART9CFGR_UART9RST */

#define __HAL_RCC_LPUART1_FORCE_RESET()           SET_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1RST)
#define __HAL_RCC_I2C1_FORCE_RESET()              SET_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1RST)
#define __HAL_RCC_I2C2_FORCE_RESET()              SET_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2RST)
#define __HAL_RCC_I2C3_FORCE_RESET()              SET_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3RST)

#if defined(RCC_I2C4CFGR_I2C4RST)
#define __HAL_RCC_I2C4_FORCE_RESET()              SET_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4RST)
#endif /* RCC_I2C4CFGR_I2C4RST */

#if defined(RCC_I2C5CFGR_I2C5RST)
#define __HAL_RCC_I2C5_FORCE_RESET()              SET_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5RST)
#endif /* RCC_I2C5CFGR_I2C5RST */

#if defined(RCC_I2C6CFGR_I2C6RST)
#define __HAL_RCC_I2C6_FORCE_RESET()              SET_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6RST)
#endif /* RCC_I2C6CFGR_I2C6RST */

#if defined(RCC_I2C7CFGR_I2C7RST)
#define __HAL_RCC_I2C7_FORCE_RESET()              SET_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7RST)
#endif /* RCC_I2C7CFGR_I2C7RST */

#if defined(RCC_I2C8CFGR_I2C8RST)
#define __HAL_RCC_I2C8_FORCE_RESET()              SET_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8RST)
#endif /* RCC_I2C8CFGR_I2C8RST */

#define __HAL_RCC_SAI1_FORCE_RESET()              SET_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1RST)
#define __HAL_RCC_SAI2_FORCE_RESET()              SET_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2RST)
#define __HAL_RCC_SAI3_FORCE_RESET()              SET_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3RST)
#define __HAL_RCC_SAI4_FORCE_RESET()              SET_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4RST)
#define __HAL_RCC_MDF1_FORCE_RESET()              SET_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1RST)
#define __HAL_RCC_ADF1_FORCE_RESET()              SET_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1RST)
#define __HAL_RCC_FDCAN_FORCE_RESET()             SET_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANRST)
#define __HAL_RCC_HDP_FORCE_RESET()               SET_BIT(RCC->HDPCFGR, RCC_HDPCFGR_HDPRST)

#if defined(RCC_ADC1CFGR_ADC1RST)
#define __HAL_RCC_ADC1_FORCE_RESET()              SET_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1RST)
#endif /* RCC_ADC1CFGR_ADC1RST */

#if defined(RCC_ADC2CFGR_ADC2RST)
#define __HAL_RCC_ADC2_FORCE_RESET()              SET_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2RST)
#endif /* RCC_ADC2CFGR_ADC2RST */

#if defined(RCC_ADC12CFGR_ADC12RST)
#define __HAL_RCC_ADC12_FORCE_RESET()             SET_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12RST)
#endif /* RCC_ADC12CFGR_ADC12RST */

#if defined(RCC_ADC3CFGR_ADC3RST)
#define __HAL_RCC_ADC3_FORCE_RESET()              SET_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3RST)
#endif /*RCC_ADC3CFGR_ADC3RST*/

#define __HAL_RCC_ETH1_FORCE_RESET()              SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1RST)
#define __HAL_RCC_ETH2_FORCE_RESET()              SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2RST)
#define __HAL_RCC_USBH_FORCE_RESET()              SET_BIT(RCC->USBHCFGR, RCC_USBHCFGR_USBHRST)
#define __HAL_RCC_USB2PHY1_FORCE_RESET()          SET_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1RST)
#define __HAL_RCC_USB2PHY2_FORCE_RESET()          SET_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2RST)
#define __HAL_RCC_USB3DRD_FORCE_RESET()           SET_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDRST)
#define __HAL_RCC_OTG_FORCE_RESET()               SET_BIT(RCC->OTGCFGR, RCC_OTGCFGR_OTGRST)
#define __HAL_RCC_USB3PCIEPHY_FORCE_RESET()       SET_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYRST)
#define __HAL_RCC_PCIE_FORCE_RESET()              SET_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIERST)
#define __HAL_RCC_UCPD1_FORCE_RESET()             SET_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDRST)
#define __HAL_RCC_FMC_FORCE_RESET()               SET_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCRST)
#define __HAL_RCC_SDMMC1_FORCE_RESET()            SET_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1RST)
#define __HAL_RCC_SDMMC2_FORCE_RESET()            SET_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2RST)
#define __HAL_RCC_SDMMC3_FORCE_RESET()            SET_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3RST)
#define __HAL_RCC_GPU_FORCE_RESET()               SET_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPURST)
#define __HAL_RCC_LTDC_FORCE_RESET()              SET_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCRST)

#if defined(RCC_DSICFGR_DSIRST)
#define __HAL_RCC_DSI_FORCE_RESET()               SET_BIT(RCC->DSICFGR, RCC_DSICFGR_DSIRST)
#endif /* RCC_DSICFGR_DSIRST */

#define __HAL_RCC_LVDS_FORCE_RESET()              SET_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSRST)

#if defined(RCC_CSICFGR_CSIRST)
#define __HAL_RCC_CSI_FORCE_RESET()               SET_BIT(RCC->CSICFGR, RCC_CSICFGR_CSIRST)
#endif /* RCC_CSICFGR_CSIRST */

#if defined(RCC_CSI2CFGR_CSI2RST)
#define __HAL_RCC_CSI2_FORCE_RESET()              SET_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2RST)
#endif /* RCC_CSI2CFGR_CSI2RST */

#define __HAL_RCC_DCMIPP_FORCE_RESET()            SET_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPRST)

#if defined(RCC_DCMIPSSICFGR_DCMIPSSIRST)
#define __HAL_RCC_DCMIPSSI_FORCE_RESET()          SET_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSIRST)
#endif /* RCC_DCMIPSSICFGR_DCMIPSSIRST */

#if defined(RCC_CCICFGR_CCIRST)
#define __HAL_RCC_CCI_FORCE_RESET()               SET_BIT(RCC->CCICFGR, RCC_CCICFGR_CCIRST)
#endif /* RCC_CCICFGR_CCIRST */

#if defined(RCC_RNGCFGR_RNGRST)
#define __HAL_RCC_RNG_FORCE_RESET()               SET_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGRST)
#endif /* RCC_RNGCFGR_RNGRST */

#if defined(RCC_RNG1CFGR_RNG1RST)
#define __HAL_RCC_RNG1_FORCE_RESET()              SET_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1RST)
#endif /* RCC_RNG1CFGR_RNG1RST */

#if defined(RCC_RNG2CFGR_RNG2RST)
#define __HAL_RCC_RNG2_FORCE_RESET()              SET_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2RST)
#endif /* RCC_RNG2CFGR_RNG2RST */

#define __HAL_RCC_PKA_FORCE_RESET()               SET_BIT(RCC->PKACFGR, RCC_PKACFGR_PKARST)
#define __HAL_RCC_SAES_FORCE_RESET()              SET_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESRST)

#if defined(RCC_HASH1CFGR_HASH1RST)
#define __HAL_RCC_HASH1_FORCE_RESET()             SET_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1RST)
#endif /* RCC_HASH1CFGR_HASH1RST */

#if defined(RCC_HASH2CFGR_HASH2RST)
#define __HAL_RCC_HASH2_FORCE_RESET()             SET_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2RST)
#endif /* RCC_HASH2CFGR_HASH2RST */

#if defined(RCC_HASHCFGR_HASHRST)
#define __HAL_RCC_HASH_FORCE_RESET()              SET_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHRST)
#endif /* RCC_HASHCFGR_HASHRST */

#define __HAL_RCC_CRYP1_FORCE_RESET()             SET_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1RST)
#define __HAL_RCC_CRYP2_FORCE_RESET()             SET_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2RST)
#define __HAL_RCC_WWDG1_FORCE_RESET()             SET_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1RST)
#define __HAL_RCC_WWDG2_FORCE_RESET()             SET_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2RST)
#define __HAL_RCC_BUSPERFM_FORCE_RESET()          SET_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMRST)
#define __HAL_RCC_VREF_FORCE_RESET()              SET_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFRST)
#define __HAL_RCC_TMPSENS_FORCE_RESET()           SET_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSRST)
#define __HAL_RCC_CRC_FORCE_RESET()               SET_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCRST)
#define __HAL_RCC_I3C1_FORCE_RESET()              SET_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1RST)
#define __HAL_RCC_I3C2_FORCE_RESET()              SET_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2RST)
#define __HAL_RCC_I3C3_FORCE_RESET()              SET_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3RST)

#if defined(RCC_I3C4CFGR_I3C4RST)
#define __HAL_RCC_I3C4_FORCE_RESET()              SET_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4RST)
#endif /* RCC_I3C4CFGR_I3C4RST */

/* for API backward compatibility */
#if defined(RCC_DCMIPSSICFGR_DCMIPSSIRST)
#define __HAL_RCC_DCMI_FORCE_RESET()              __HAL_RCC_DCMIPSSI_FORCE_RESET()
#define __HAL_RCC_PSSI_FORCE_RESET()              __HAL_RCC_DCMIPSSI_FORCE_RESET()
#endif /* RCC_DCMIPSSICFGR_DCMIPSSIRST */

#if defined(RCC_CCICFGR_CSIRST)
#define __HAL_RCC_DCMI_FORCE_RESET()              __HAL_RCC_CCI_FORCE_RESET()
#define __HAL_RCC_PSSI_FORCE_RESET()              __HAL_RCC_CCI_FORCE_RESET()
#endif /* RCC_CCICFGR_CSIRST */

/* Reset release macros */
#define __HAL_RCC_SERC_RELEASE_RESET()            CLEAR_BIT(RCC->SERCCFGR, RCC_SERCCFGR_SERCRST)
#define __HAL_RCC_OSPIIOM_RELEASE_RESET()         CLEAR_BIT(RCC->OSPIIOMCFGR, RCC_OSPIIOMCFGR_OSPIIOMRST)
#define __HAL_RCC_ETHSW_RELEASE_RESET()           CLEAR_BIT(RCC->ETHSWCFGR, RCC_ETHSWCFGR_ETHSWRST)
#define __HAL_RCC_VDEC_RELEASE_RESET()            CLEAR_BIT(RCC->VDECCFGR, RCC_VDECCFGR_VDECRST)

#if defined(RCC_VENCCFGR_VENCRST)
#define __HAL_RCC_VENC_RELEASE_RESET()            CLEAR_BIT(RCC->VENCCFGR, RCC_VENCCFGR_VENCRST)
#endif /* RCC_VENCCFGR_VENCRST */

#if defined(RCC_C3CFGR_C3RST)
#define __HAL_RCC_C3_RELEASE_RESET()              CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_C3RST)
#endif /* RCC_C3CFGR_C3RST */

#define __HAL_RCC_OSPI1_RELEASE_RESET()           CLEAR_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1RST)

#if defined(RCC_OSPI2CFGR_OSPI2RST)
#define __HAL_RCC_OSPI2_RELEASE_RESET()           CLEAR_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2RST)
#endif /* RCC_OSPI2CFGR_OSPI2RST */

#define __HAL_RCC_OTFDEC1_RELEASE_RESET()         CLEAR_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OTFDEC1RST)

#if defined(RCC_OSPI2CFGR_OSPI2RST)
#define __HAL_RCC_OTFDEC2_RELEASE_RESET()         CLEAR_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OTFDEC2RST)
#endif /* RCC_OSPI2CFGR_OSPI2RST */

#define __HAL_RCC_GPIOA_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxRST)
#define __HAL_RCC_GPIOB_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxRST)
#define __HAL_RCC_GPIOC_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxRST)
#define __HAL_RCC_GPIOD_RELEASE_RESET()           CLEAR_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxRST)
#define __HAL_RCC_GPIOE_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxRST)
#define __HAL_RCC_GPIOF_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxRST)
#define __HAL_RCC_GPIOG_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxRST)
#define __HAL_RCC_GPIOH_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxRST)
#define __HAL_RCC_GPIOI_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxRST)

#if defined(RCC_GPIOJCFGR_GPIOxRST)
#define __HAL_RCC_GPIOJ_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxRST)
#endif /* RCC_GPIOJCFGR_GPIOxRST */

#if defined(RCC_GPIOKCFGR_GPIOxRST)
#define __HAL_RCC_GPIOK_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxRST)
#endif /* RCC_GPIOKCFGR_GPIOxRST */

#define __HAL_RCC_GPIOZ_RELEASE_RESET()           CLEAR_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZRST)
#define __HAL_RCC_HPDMA1_RELEASE_RESET()          CLEAR_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1RST)
#define __HAL_RCC_HPDMA2_RELEASE_RESET()          CLEAR_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2RST)
#define __HAL_RCC_HPDMA3_RELEASE_RESET()          CLEAR_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3RST)

#if defined(RCC_LPDMACFGR_LPDMARST)
#define __HAL_RCC_LPDMA_RELEASE_RESET()           CLEAR_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMARST)
#endif /* RCC_LPDMACFGR_LPDMARST */

#if defined(RCC_HSEMCFGR_HSEMRST)
#define __HAL_RCC_HSEM_RELEASE_RESET()            CLEAR_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMRST)
#endif /* RCC_HSEMCFGR_HSEMRST */

#define __HAL_RCC_IPCC1_RELEASE_RESET()           CLEAR_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1RST)

#if defined(RCC_IPCC2CFGR_IPCC2RST)
#define __HAL_RCC_IPCC2_RELEASE_RESET()           CLEAR_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2RST)
#endif /* RCC_IPCC2CFGR_IPCC2RST */

#define __HAL_RCC_IS2M_RELEASE_RESET()            CLEAR_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MRST)
#define __HAL_RCC_TIM1_RELEASE_RESET()            CLEAR_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1RST)
#define __HAL_RCC_TIM2_RELEASE_RESET()            CLEAR_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2RST)
#define __HAL_RCC_TIM3_RELEASE_RESET()            CLEAR_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3RST)
#define __HAL_RCC_TIM4_RELEASE_RESET()            CLEAR_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4RST)
#define __HAL_RCC_TIM5_RELEASE_RESET()            CLEAR_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5RST)
#define __HAL_RCC_TIM6_RELEASE_RESET()            CLEAR_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6RST)
#define __HAL_RCC_TIM7_RELEASE_RESET()            CLEAR_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7RST)
#define __HAL_RCC_TIM8_RELEASE_RESET()            CLEAR_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8RST)
#define __HAL_RCC_TIM10_RELEASE_RESET()           CLEAR_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10RST)
#define __HAL_RCC_TIM11_RELEASE_RESET()           CLEAR_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11RST)
#define __HAL_RCC_TIM12_RELEASE_RESET()           CLEAR_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12RST)
#define __HAL_RCC_TIM13_RELEASE_RESET()           CLEAR_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13RST)
#define __HAL_RCC_TIM14_RELEASE_RESET()           CLEAR_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14RST)
#define __HAL_RCC_TIM15_RELEASE_RESET()           CLEAR_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15RST)
#define __HAL_RCC_TIM16_RELEASE_RESET()           CLEAR_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16RST)
#define __HAL_RCC_TIM17_RELEASE_RESET()           CLEAR_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17RST)

#if defined(RCC_TIM20CFGR_TIM20RST)
#define __HAL_RCC_TIM20_RELEASE_RESET()           CLEAR_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20RST)
#endif /* RCC_TIM20CFGR_TIM20RST */

#define __HAL_RCC_LPTIM1_RELEASE_RESET()          CLEAR_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1RST)
#define __HAL_RCC_LPTIM2_RELEASE_RESET()          CLEAR_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2RST)
#define __HAL_RCC_LPTIM3_RELEASE_RESET()          CLEAR_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3RST)
#define __HAL_RCC_LPTIM4_RELEASE_RESET()          CLEAR_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4RST)
#define __HAL_RCC_LPTIM5_RELEASE_RESET()          CLEAR_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5RST)
#define __HAL_RCC_SPI1_RELEASE_RESET()            CLEAR_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1RST)
#define __HAL_RCC_SPI2_RELEASE_RESET()            CLEAR_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2RST)
#define __HAL_RCC_SPI3_RELEASE_RESET()            CLEAR_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3RST)
#define __HAL_RCC_SPI4_RELEASE_RESET()            CLEAR_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4RST)
#define __HAL_RCC_SPI5_RELEASE_RESET()            CLEAR_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5RST)
#define __HAL_RCC_SPI6_RELEASE_RESET()            CLEAR_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6RST)

#if defined(RCC_SPI7CFGR_SPI7RST)
#define __HAL_RCC_SPI7_RELEASE_RESET()            CLEAR_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7RST)
#endif /* RCC_SPI7CFGR_SPI7RST */

#if defined(RCC_SPI8CFGR_SPI8RST)
#define __HAL_RCC_SPI8_RELEASE_RESET()            CLEAR_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8RST)
#endif /* RCC_SPI8CFGR_SPI8RST */

#define __HAL_RCC_SPDIFRX_RELEASE_RESET()         CLEAR_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXRST)
#define __HAL_RCC_USART1_RELEASE_RESET()          CLEAR_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1RST)
#define __HAL_RCC_USART2_RELEASE_RESET()          CLEAR_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2RST)
#define __HAL_RCC_USART3_RELEASE_RESET()          CLEAR_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3RST)
#define __HAL_RCC_UART4_RELEASE_RESET()           CLEAR_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4RST)
#define __HAL_RCC_UART5_RELEASE_RESET()           CLEAR_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5RST)
#define __HAL_RCC_USART6_RELEASE_RESET()          CLEAR_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6RST)
#define __HAL_RCC_UART7_RELEASE_RESET()           CLEAR_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7RST)

#if defined(RCC_UART8CFGR_UART8RST)
#define __HAL_RCC_UART8_RELEASE_RESET()           CLEAR_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8RST)
#endif /* RCC_UART8CFGR_UART8RST */

#if defined(RCC_UART9CFGR_UART9RST)
#define __HAL_RCC_UART9_RELEASE_RESET()           CLEAR_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9RST)
#endif /* RCC_UART9CFGR_UART9RST */

#define __HAL_RCC_LPUART1_RELEASE_RESET()         CLEAR_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1RST)
#define __HAL_RCC_I2C1_RELEASE_RESET()            CLEAR_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1RST)
#define __HAL_RCC_I2C2_RELEASE_RESET()            CLEAR_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2RST)
#define __HAL_RCC_I2C3_RELEASE_RESET()            CLEAR_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3RST)

#if defined(RCC_I2C4CFGR_I2C4RST)
#define __HAL_RCC_I2C4_RELEASE_RESET()            CLEAR_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4RST)
#endif /* RCC_I2C4CFGR_I2C4RST */

#if defined(RCC_I2C5CFGR_I2C5RST)
#define __HAL_RCC_I2C5_RELEASE_RESET()            CLEAR_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5RST)
#endif /* RCC_I2C5CFGR_I2C5RST */

#if defined(RCC_I2C6CFGR_I2C6RST)
#define __HAL_RCC_I2C6_RELEASE_RESET()            CLEAR_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6RST)
#endif /* RCC_I2C6CFGR_I2C6RST */

#if defined(RCC_I2C7CFGR_I2C7RST)
#define __HAL_RCC_I2C7_RELEASE_RESET()            CLEAR_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7RST)
#endif /* RCC_I2C7CFGR_I2C7RST */

#if defined(RCC_I2C8CFGR_I2C8RST)
#define __HAL_RCC_I2C8_RELEASE_RESET()            CLEAR_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8RST)
#endif /* RCC_I2C8CFGR_I2C8RST */

#define __HAL_RCC_SAI1_RELEASE_RESET()            CLEAR_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1RST)
#define __HAL_RCC_SAI2_RELEASE_RESET()            CLEAR_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2RST)
#define __HAL_RCC_SAI3_RELEASE_RESET()            CLEAR_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3RST)
#define __HAL_RCC_SAI4_RELEASE_RESET()            CLEAR_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4RST)
#define __HAL_RCC_MDF1_RELEASE_RESET()            CLEAR_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1RST)
#define __HAL_RCC_ADF1_RELEASE_RESET()            CLEAR_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1RST)
#define __HAL_RCC_FDCAN_RELEASE_RESET()           CLEAR_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANRST)
#define __HAL_RCC_HDP_RELEASE_RESET()             CLEAR_BIT(RCC->HDPCFGR, RCC_HDPCFGR_HDPRST)

#if defined(RCC_ADC1CFGR_ADC1RST)
#define __HAL_RCC_ADC1_RELEASE_RESET()            CLEAR_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1RST)
#endif /* RCC_ADC1CFGR_ADC1RST */

#if defined(RCC_ADC2CFGR_ADC2RST)
#define __HAL_RCC_ADC2_RELEASE_RESET()            CLEAR_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2RST)
#endif /* RCC_ADC2CFGR_ADC2RST */

#if defined(RCC_ADC12CFGR_ADC12RST)
#define __HAL_RCC_ADC12_RELEASE_RESET()           CLEAR_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12RST)
#endif /* RCC_ADC12CFGR_ADC12RST */

#if defined(RCC_ADC3CFGR_ADC3RST)
#define __HAL_RCC_ADC3_RELEASE_RESET()            CLEAR_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3RST)
#endif /* RCC_ADC3CFGR_ADC3RST */

#define __HAL_RCC_ETH1_RELEASE_RESET()            CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1RST)
#define __HAL_RCC_ETH2_RELEASE_RESET()            CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2RST)

#if defined(RCC_USBHCFGR_USBHRST)
#define __HAL_RCC_USBH_RELEASE_RESET()            CLEAR_BIT(RCC->USBHCFGR, RCC_USBHCFGR_USBHRST)
#endif /* RCC_USBHCFGR_USBHRST */

#define __HAL_RCC_USB2PHY1_RELEASE_RESET()        CLEAR_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1RST)
#define __HAL_RCC_USB2PHY2_RELEASE_RESET()        CLEAR_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2RST)

#if defined(RCC_OTGCFGR_OTGRST)
#define __HAL_RCC_OTG_RELEASE_RESET()             CLEAR_BIT(RCC->OTGCFGR, RCC_OTGCFGR_OTGRST)
#endif /* RCC_OTGCFGR_OTGRST */

#if defined(RCC_USB3DRDCFGR_USB3DRDRST)
#define __HAL_RCC_USB3DRD_RELEASE_RESET()         CLEAR_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDRST)
#endif /* RCC_USB3DRDCFGR_USB3DRDRST */

#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYRST)
#define __HAL_RCC_USB3PCIEPHY_RELEASE_RESET()     CLEAR_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYRST)
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYRST */

#if defined(RCC_PCIECFGR_PCIERST)
#define __HAL_RCC_PCIE_RELEASE_RESET()            CLEAR_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIERST)
#endif /* RCC_PCIECFGR_PCIERST */

#if defined(RCC_UCPDCFGR_UCPDRST)
#define __HAL_RCC_UCPD1_RELEASE_RESET()           CLEAR_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDRST)
#endif /* RCC_UCPDCFGR_UCPDRST */

#define __HAL_RCC_FMC_RELEASE_RESET()             CLEAR_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCRST)
#define __HAL_RCC_SDMMC1_RELEASE_RESET()          CLEAR_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1RST)
#define __HAL_RCC_SDMMC2_RELEASE_RESET()          CLEAR_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2RST)
#define __HAL_RCC_SDMMC3_RELEASE_RESET()          CLEAR_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3RST)
#define __HAL_RCC_GPU_RELEASE_RESET()             CLEAR_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPURST)
#define __HAL_RCC_LTDC_RELEASE_RESET()            CLEAR_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCRST)

#if defined(RCC_DSICFGR_DSIRST)
#define __HAL_RCC_DSI_RELEASE_RESET()             CLEAR_BIT(RCC->DSICFGR, RCC_DSICFGR_DSIRST)
#endif /* RCC_DSICFGR_DSIRST */

#define __HAL_RCC_LVDS_RELEASE_RESET()            CLEAR_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSRST)

#if defined(RCC_CSICFGR_CSIRST)
#define __HAL_RCC_CSI_RELEASE_RESET()             CLEAR_BIT(RCC->CSICFGR, RCC_CSICFGR_CSIRST)
#endif /* RCC_CSICFGR_CSIRST */

#if defined(RCC_CSI2CFGR_CSI2RST)
#define __HAL_RCC_CSI2_RELEASE_RESET()            CLEAR_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2RST)
#endif /* RCC_CSI2CFGR_CSI2RST */

#define __HAL_RCC_DCMIPP_RELEASE_RESET()          CLEAR_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPRST)

#if defined(RCC_DCMIPSSICFGR_DCMIPSSIRST)
#define __HAL_RCC_DCMIPSSI_RELEASE_RESET()        CLEAR_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSIRST)
#endif /*RCC_DCMIPSSICFGR_DCMIPSSIRST*/

#if defined(RCC_CCICFGR_CCIRST)
#define __HAL_RCC_CCI_RELEASE_RESET()             CLEAR_BIT(RCC->CCICFGR, RCC_CCICFGR_CCIRST)
#endif /* RCC_CCICFGR_CCIRST */

#if defined(RCC_RNGCFGR_RNGRST)
#define __HAL_RCC_RNG_RELEASE_RESET()             CLEAR_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGRST)
#endif /* RCC_RNGCFGR_RNGRST */

#if defined(RCC_RNG1CFGR_RNG1RST)
#define __HAL_RCC_RNG1_RELEASE_RESET()            CLEAR_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1RST)
#endif /* RCC_RNG1CFGR_RNG1RST */

#if defined(RCC_RNG2CFGR_RNG2RST)
#define __HAL_RCC_RNG2_RELEASE_RESET()            CLEAR_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2RST)
#endif /* RCC_RNG2CFGR_RNG2RST */

#define __HAL_RCC_PKA_RELEASE_RESET()             CLEAR_BIT(RCC->PKACFGR, RCC_PKACFGR_PKARST)
#define __HAL_RCC_SAES_RELEASE_RESET()            CLEAR_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESRST)

#if defined(RCC_HASHCFGR_HASHRST)
#define __HAL_RCC_HASH_RELEASE_RESET()            CLEAR_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHRST)
#endif /* RCC_HASHCFGR_HASHRST */

#if defined(RCC_HASH1CFGR_HASH1RST)
#define __HAL_RCC_HASH1_RELEASE_RESET()           CLEAR_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1RST)
#endif /* RCC_HASH1CFGR_HASH1RST */

#if defined(RCC_HASH2CFGR_HASH2RST)
#define __HAL_RCC_HASH2_RELEASE_RESET()           CLEAR_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2RST)
#endif /* RCC_HASH2CFGR_HASH2RST */

#define __HAL_RCC_CRYP1_RELEASE_RESET()           CLEAR_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1RST)
#define __HAL_RCC_CRYP2_RELEASE_RESET()           CLEAR_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2RST)
#define __HAL_RCC_WWDG1_RELEASE_RESET()           CLEAR_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1RST)

#if defined(RCC_WWDG2CFGR_WWDG2RST)
#define __HAL_RCC_WWDG2_RELEASE_RESET()           CLEAR_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2RST)
#endif /* RCC_WWDG2CFGR_WWDG2RST */

#define __HAL_RCC_BUSPERFM_RELEASE_RESET()        CLEAR_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMRST)
#define __HAL_RCC_VREF_RELEASE_RESET()            CLEAR_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFRST)

#if defined (RCC_TMPSENSCFGR_TMPSENSRST)
#define __HAL_RCC_TMPSENS_RELEASE_RESET()         CLEAR_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSRST)
#endif /* RCC_TMPSENSCFGR_TMPSENSRST */

#define __HAL_RCC_CRC_RELEASE_RESET()             CLEAR_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCRST)
#define __HAL_RCC_I3C1_RELEASE_RESET()            CLEAR_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1RST)
#define __HAL_RCC_I3C2_RELEASE_RESET()            CLEAR_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2RST)
#define __HAL_RCC_I3C3_RELEASE_RESET()            CLEAR_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3RST)

#if defined(RCC_I3C4CFGR_I3C4RST)
#define __HAL_RCC_I3C4_RELEASE_RESET()            CLEAR_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4RST)
#endif /* RCC_I3C4CFGR_I3C4RST */

/* for API backward compatibility */
#if defined(RCC_DCMIPSSICFGR_DCMIPSSIRST)
#define __HAL_RCC_DCMI_RELEASE_RESET()            __HAL_RCC_DCMIPSSI_RELEASE_RESET()
#define __HAL_RCC_PSSI_RELEASE_RESET()            __HAL_RCC_DCMIPSSI_RELEASE_RESET()
#endif /* RCC_DCMIPSSICFGR_DCMIPSSIRST */

#if defined(RCC_CCICFGR_CSIRST)
#define __HAL_RCC_DCMI_RELEASE_RESET()            __HAL_RCC_CCI_RELEASE_RESET()
#define __HAL_RCC_PSSI_RELEASE_RESET()            __HAL_RCC_CCI_RELEASE_RESET()
#endif /* RCC_CCICFGR_CSIRST */

#if defined(RCC_C3CFGR_C3EN)
/* C3 allocation macros */
#define __HAL_RCC_LPTIM3_C3_ALLOCATE()            SET_BIT(RCC->C3CFGR, RCC_C3CFGR_LPTIM3C3EN)
#define __HAL_RCC_LPTIM4_C3_ALLOCATE()            SET_BIT(RCC->C3CFGR, RCC_C3CFGR_LPTIM4C3EN)
#define __HAL_RCC_LPTIM5_C3_ALLOCATE()            SET_BIT(RCC->C3CFGR, RCC_C3CFGR_LPTIM5C3EN)
#define __HAL_RCC_SPI8_C3_ALLOCATE()              SET_BIT(RCC->C3CFGR, RCC_C3CFGR_SPI8C3EN)
#define __HAL_RCC_LPUART1_C3_ALLOCATE()           SET_BIT(RCC->C3CFGR, RCC_C3CFGR_LPUART1C3EN)
#define __HAL_RCC_I2C8_C3_ALLOCATE()              SET_BIT(RCC->C3CFGR, RCC_C3CFGR_I2C8C3EN)
#define __HAL_RCC_ADF1_C3_ALLOCATE()              SET_BIT(RCC->C3CFGR, RCC_C3CFGR_ADF1C3EN)
#define __HAL_RCC_GPIOZ_C3_ALLOCATE()             SET_BIT(RCC->C3CFGR, RCC_C3CFGR_GPIOZC3EN)
#define __HAL_RCC_LPDMA_C3_ALLOCATE()             SET_BIT(RCC->C3CFGR, RCC_C3CFGR_LPDMAC3EN)
#define __HAL_RCC_RTC_C3_ALLOCATE()               SET_BIT(RCC->C3CFGR, RCC_C3CFGR_RTCC3EN)
#define __HAL_RCC_I3C4_C3_ALLOCATE()              SET_BIT(RCC->C3CFGR, RCC_C3CFGR_I3C4C3EN)

/* C3 deallocation macros */
#define __HAL_RCC_LPTIM3_C3_DEALLOCATE()          CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_LPTIM3C3EN)
#define __HAL_RCC_LPTIM4_C3_DEALLOCATE()          CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_LPTIM4C3EN)
#define __HAL_RCC_LPTIM5_C3_DEALLOCATE()          CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_LPTIM5C3EN)
#define __HAL_RCC_SPI8_C3_DEALLOCATE()            CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_SPI8C3EN)
#define __HAL_RCC_LPUART1_C3_DEALLOCATE()         CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_LPUART1C3EN)
#define __HAL_RCC_I2C8_C3_DEALLOCATE()            CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_I2C8C3EN)
#define __HAL_RCC_ADF1_C3_DEALLOCATE()            CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_ADF1C3EN)
#define __HAL_RCC_GPIOZ_C3_DEALLOCATE()           CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_GPIOZC3EN)
#define __HAL_RCC_LPDMA_C3_DEALLOCATE()           CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_LPDMAC3EN)
#define __HAL_RCC_RTC_C3_DEALLOCATE()             CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_RTCC3EN)
#define __HAL_RCC_I3C4_C3_DEALLOCATE()            CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_I3C4C3EN)
#endif /* RCC_C3CFGR_C3EN */

/* Allows/Prevents CStop & Enhanced CSleep modes for all A35_* cores */
#ifdef CORE_CA35
#if defined(RCC_C1SREQCLRR_STPREQ_P1)
#define __HAL_RCC_ALLOW_CSTOP()                   SET_BIT(RCC->C1SREQSETR, RCC_C1SREQSETR_STPREQ_P1 |\
                                                          RCC_C1SREQSETR_STPREQ_P0)
#define __HAL_RCC_PREVENT_CSTOP()                 WRITE_REG(RCC->C1SREQCLRR, RCC_C1SREQCLRR_STPREQ_P1 |\
                                                            RCC_C1SREQCLRR_STPREQ_P0)
#else
#define __HAL_RCC_ALLOW_CSTOP()                   SET_BIT(RCC->C1SREQSETR, RCC_C1SREQSETR_STPREQ_P0)
#define __HAL_RCC_PREVENT_CSTOP()                 WRITE_REG(RCC->C1SREQCLRR, RCC_C1SREQCLRR_STPREQ_P0)
#endif
#define __HAL_RCC_ALLOW_ENHANCED_CSLEEP()         SET_BIT(RCC->C1SREQSETR, RCC_C1SREQSETR_ESLPREQ)
#define __HAL_RCC_PREVENT_ENHANCED_CSLEEP()       WRITE_REG(RCC->C1SREQCLRR, RCC_C1SREQCLRR_ESLPREQ)
#endif /* CORE_CA35 */

#if defined(RCC_ADC1CFGR_ADC1KERSEL)
/** @defgroup RCC_ADC1_Kernel_Clock_Source RCC_ADC1_Kernel_Clock_Source
  * @{
  */
#define RCC_ADC1KERCLKSOURCE_CK_KER_ADC1     (0x0U << RCC_ADC1CFGR_ADC1KERSEL_Pos)
#define RCC_ADC1KERCLKSOURCE_CK_ICN_LS_MCU   (0x1U << RCC_ADC1CFGR_ADC1KERSEL_Pos)

#define IS_RCC_ADC1KERCLKSOURCE(SOURCE) (((SOURCE) == RCC_ADC1KERCLKSOURCE_CK_KER_ADC1) || \
                                         ((SOURCE) == RCC_ADC1KERCLKSOURCE_CK_ICN_LS_MCU))

/**
  * @brief  Macro to select ADC1 kernel source clock
  *
  * @param  __RCC_ADC1KERSOURCE__: specifies the ADC1 entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_ADC1KERCLKSOURCE_CK_KER_ADC1:  "ck_ker_adc1"  Flexiclockgen output 46
  *            @arg RCC_ADC1KERCLKSOURCE_CK_ICN_LS_MCU: "ck_icn_ls_mcu" Flexiclockgen output 0
  *
  * @retval None
  */
#define __HAL_RCC_ADC1KERCLK_SETSOURCE(__RCC_ADC1KERSOURCE__) \
  MODIFY_REG( RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1KERSEL,(__RCC_ADC1KERSOURCE__)  )

/** @brief  Macro to get the clock source used as ADC1 kernel source clock.
  * @retval The clock source used as ADC1 kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_ADC1KERCLKSOURCE_CK_KER_ADC1:  "ck_ker_adc1"  Flexiclockgen output 46
  *            @arg RCC_ADC1KERCLKSOURCE_CK_ICN_LS_MCU: "ck_icn_ls_mcu" Flexiclockgen output 0
  */
#define __HAL_RCC_ADC1KERCLK_GETSOURCE()  (RCC->ADC1CFGR & RCC_ADC1CFGR_ADC1KERSEL_Msk)
/**
  * @}
  */
#endif /* RCC_ADC1CFGR_ADC1KERSEL */

#if defined(RCC_ADC2CFGR_ADC2KERSEL)
/** @defgroup RCC_ADC2_Kernel_Clock_Source RCC_ADC2_Kernel_Clock_Source
  * @{
  */
#define RCC_ADC2KERCLKSOURCE_CK_KER_ADC2      (0x0U << RCC_ADC2CFGR_ADC2KERSEL_Pos)
#define RCC_ADC2KERCLKSOURCE_CK_ICN_LS_MCU    (0x1U << RCC_ADC2CFGR_ADC2KERSEL_Pos)

#define IS_RCC_ADC2KERCLKSOURCE(SOURCE) (((SOURCE) == RCC_ADC2KERCLKSOURCE_CK_KER_ADC2) || \
                                         ((SOURCE) == RCC_ADC2KERCLKSOURCE_CK_ICN_LS_MCU))

/**
  * @brief  Macro to select ADC2 kernel source clock
  *
  * @param  __RCC_ADC2KERSOURCE__: specifies the ADC2 entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_ADC2KERCLKSOURCE_CK_KER_ADC2:  "ck_ker_adc2"  Flexiclockgen output 47
  *            @arg RCC_ADC2KERCLKSOURCE_CK_ICN_LS_MCU: "ck_icn_ls_mcu" Flexiclockgen output 0
  *
  * @retval None
  */
#define __HAL_RCC_ADC2KERCLK_SETSOURCE(__RCC_ADC2KERSOURCE__) \
  MODIFY_REG( RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2KERSEL,(__RCC_ADC2KERSOURCE__)  )

/** @brief  Macro to get the clock source used as ADC2 kernel source clock.
  * @retval The clock source used as ADC2 kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_ADC2KERCLKSOURCE_CK_KER_ADC2:  "ck_ker_adc2"  Flexiclockgen output 47
  *            @arg RCC_ADC2KERCLKSOURCE_CK_ICN_LS_MCU: "ck_icn_ls_mcu" Flexiclockgen output 0
  */
#define __HAL_RCC_ADC2KERCLK_GETSOURCE()  (RCC->ADC2CFGR & RCC_ADC2CFGR_ADC2KERSEL_Msk)
/**
  * @}
  */
#endif /* RCC_ADC2CFGR_ADC2KERSEL */


#if defined(RCC_ADC12CFGR_ADC12KERSEL)
/** @defgroup RCC_ADC12_Kernel_Clock_Source RCC_ADC12_Kernel_Clock_Source
  * @{
  */
#define RCC_ADC12KERCLKSOURCE_CK_KER_ADC12     (0x0U << RCC_ADC12CFGR_ADC12KERSEL_Pos)
#define RCC_ADC12KERCLKSOURCE_CK_ICN_LS_MCU    (0x1U << RCC_ADC12CFGR_ADC12KERSEL_Pos)

#define IS_RCC_ADC12KERCLKSOURCE(SOURCE) (((SOURCE) == RCC_ADC12KERCLKSOURCE_CK_KER_ADC12) || \
                                          ((SOURCE) == RCC_ADC12KERCLKSOURCE_CK_ICN_LS_MCU))

/**
  * @brief  Macro to select ADC12 kernel source clock
  *
  * @param  __RCC_ADC12KERSOURCE__: specifies the ADC12 entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_ADC12KERCLKSOURCE_CK_KER_ADC12:  "ck_ker_adc12"  Flexiclockgen output 46
  *            @arg RCC_ADC12KERCLKSOURCE_CK_ICN_LS_MCU: "ck_icn_ls_mcu" Flexiclockgen output 0
  *
  * @retval None
  */
#define __HAL_RCC_ADC12KERCLK_SETSOURCE(__RCC_ADC12KERSOURCE__) \
  MODIFY_REG( RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12KERSEL,(__RCC_ADC12KERSOURCE__)  )

/** @brief  Macro to get the clock source used as ADC12 kernel source clock.
  * @retval The clock source used as ADC12 kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_ADC12KERCLKSOURCE_CK_KER_ADC12:  "ck_ker_adc12"  Flexiclockgen output 46
  *            @arg RCC_ADC12KERCLKSOURCE_CK_ICN_LS_MCU: "ck_icn_ls_mcu" Flexiclockgen output 0
  */
#define __HAL_RCC_ADC12KERCLK_GETSOURCE()  (RCC->ADC12CFGR & RCC_ADC12CFGR_ADC12KERSEL_Msk)
/**
  * @}
  */
#endif /* RCC_ADC12CFGR_ADC12KERSEL */

#if defined(RCC_ADC3CFGR_ADC3KERSEL)
/** @defgroup RCC_ADC3_Kernel_Clock_Source RCC_ADC3_Kernel_Clock_Source
  * @{
  */
#define RCC_ADC3KERCLKSOURCE_CK_KER_ADC3      (0x0U << RCC_ADC3CFGR_ADC3KERSEL_Pos)
#define RCC_ADC3KERCLKSOURCE_CK_ICN_LS_MCU    (0x1U << RCC_ADC3CFGR_ADC3KERSEL_Pos)
#define RCC_ADC3KERCLKSOURCE_CK_KER_ADC12     (0x2U << RCC_ADC3CFGR_ADC3KERSEL_Pos)

#define IS_RCC_ADC3KERCLKSOURCE(SOURCE) (((SOURCE) == RCC_ADC3KERCLKSOURCE_CK_KER_ADC3) || \
                                         ((SOURCE) == RCC_ADC3KERCLKSOURCE_CK_ICN_LS_MCU) || \
                                         ((SOURCE) == RCC_ADC3KERCLKSOURCE_CK_KER_ADC12))

/**
  * @brief  Macro to select ADC3 kernel source clock
  *
  * @param  __RCC_ADC3KERSOURCE__: specifies the ADC3 entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_ADC3KERCLKSOURCE_CK_KER_ADC3:   "ck_ker_adc3"   Flexiclockgen output 47
  *            @arg RCC_ADC3KERCLKSOURCE_CK_ICN_LS_MCU: "ck_icn_ls_mcu" Flexiclockgen output 0
  *            @arg RCC_ADC3KERCLKSOURCE_CK_KER_ADC12:  "ck_ker_adc12"  Flexiclockgen output 46
  *
  * @retval None
  */
#define __HAL_RCC_ADC3KERCLK_SETSOURCE(__RCC_ADC3KERSOURCE__) \
  MODIFY_REG( RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3KERSEL, (__RCC_ADC3KERSOURCE__)  )

/** @brief  Macro to get the clock source used as ADC3 kernel source clock.
  * @retval The clock source used as ADC3 kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_ADC3KERCLKSOURCE_CK_KER_ADC3:   "ck_ker_adc3"   Flexiclockgen output 47
  *            @arg RCC_ADC3KERCLKSOURCE_CK_ICN_LS_MCU: "ck_icn_ls_mcu" Flexiclockgen output 0
  *            @arg RCC_ADC3KERCLKSOURCE_CK_KER_ADC12:  "ck_ker_adc12"  Flexiclockgen output 46
  */
#define __HAL_RCC_ADC3KERCLK_GETSOURCE()  (RCC->ADC3CFGR & RCC_ADC3CFGR_ADC3KERSEL_Msk)
/**
  * @}
  */
#endif /* RCC_ADC3CFGR_ADC3KERSEL */

/** @defgroup RCC_USB2PHY1_Kernel_Clock_Source RCC_USB2PHY1_Kernel_Clock_Source
  * @{
  */
#define RCC_USB2PHY1KERCLKSOURCE_CK_KER_USB2PHY1    (0x0U << RCC_USB2PHY1CFGR_USB2PHY1CKREFSEL_Pos)
#define RCC_USB2PHY1KERCLKSOURCE_HSE_KER_CLK        (0x1U << RCC_USB2PHY1CFGR_USB2PHY1CKREFSEL_Pos)

#define IS_RCC_USB2PHY1KERCLKSOURCE(SOURCE) (((SOURCE) == RCC_USB2PHY1KERCLKSOURCE_CK_KER_USB2PHY1) || \
                                             ((SOURCE) == RCC_USB2PHY1KERCLKSOURCE_HSE_KER_CLK))

/**
  * @brief  Macro to select USB2PHY1 kernel source clock
  *
  * @param  __RCC_USB2PHY1KERSOURCE__: specifies the USB2PHY1 entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USB2PHY1KERCLKSOURCE_CK_KER_USB2PHY1: "ck_ker_USB2PHY1"   Flexiclockgen output 57
  *            @arg RCC_USB2PHY1KERCLKSOURCE_HSE_KER_CLK:     "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  *
  * @retval None
  */
#define __HAL_RCC_USB2PHY1KERCLK_SETSOURCE(__RCC_USB2PHY1KERSOURCE__) \
  MODIFY_REG( RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1CKREFSEL, (__RCC_USB2PHY1KERSOURCE__)  )

/** @brief  Macro to get the clock source used as USB2PHY1 kernel source clock.
  * @retval The clock source used as USB2PHY1 kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_USB2PHY1KERCLKSOURCE_CK_KER_USB2PHY1: "ck_ker_USB2PHY1"   Flexiclockgen output 57
  *            @arg RCC_USB2PHY1KERCLKSOURCE_HSE_KER_CLK:     "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  */
#define __HAL_RCC_USB2PHY1KERCLK_GETSOURCE()  (RCC->USB2PHY1CFGR & RCC_USB2PHY1CFGR_USB2PHY1CKREFSEL_Msk)
/**
  * @}
  */

/** @defgroup RCC_USB2PHY2_Kernel_Clock_Source RCC_USB2PHY2_Kernel_Clock_Source
  * @{
  */
#define RCC_USB2PHY2KERCLKSOURCE_CK_KER_USB2PHY2    (0x0U << RCC_USB2PHY2CFGR_USB2PHY2CKREFSEL_Pos)
#define RCC_USB2PHY2KERCLKSOURCE_HSE_KER_CLK        (0x1U << RCC_USB2PHY2CFGR_USB2PHY2CKREFSEL_Pos)

#define IS_RCC_USB2PHY2KERCLKSOURCE(SOURCE) (((SOURCE) == RCC_USB2PHY2KERCLKSOURCE_CK_KER_USB2PHY2) || \
                                             ((SOURCE) == RCC_USB2PHY2KERCLKSOURCE_HSE_KER_CLK))

/**
  * @brief  Macro to select USB2PHY2 kernel source clock
  *
  * @param  __RCC_USB2PHY2KERSOURCE__: specifies the USB2PHY2 entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USB2PHY2KERCLKSOURCE_CK_KER_USB2PHY2: "ck_ker_USB2PHY2"   Flexiclockgen output 58
  *            @arg RCC_USB2PHY2KERCLKSOURCE_HSE_KER_CLK:     "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  *
  * @retval None
  */
#define __HAL_RCC_USB2PHY2KERCLK_SETSOURCE(__RCC_USB2PHY2KERSOURCE__) \
  MODIFY_REG( RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2CKREFSEL, (__RCC_USB2PHY2KERSOURCE__)  )

/** @brief  Macro to get the clock source used as USB2PHY2 kernel source clock.
  * @retval The clock source used as USB2PHY2 kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_USB2PHY2KERCLKSOURCE_CK_KER_USB2PHY2: "ck_ker_USB2PHY2"   Flexiclockgen output 58
  *            @arg RCC_USB2PHY2KERCLKSOURCE_HSE_KER_CLK:     "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  */
#define __HAL_RCC_USB2PHY2KERCLK_GETSOURCE()  (RCC->USB2PHY2CFGR & RCC_USB2PHY2CFGR_USB2PHY2CKREFSEL_Msk)
/**
  * @}
  */

/** @defgroup RCC_USB3PCIEPHY_Kernel_Clock_Source RCC_USB3PCIEPHY_Kernel_Clock_Source
  * @{
  */
#define RCC_USB3PCIEPHYKERCLKSOURCE_CK_KER_USB3PCIEPHY    (0x0U << RCC_USB3PCIEPHYCFGR_USB3PCIEPHYCKREFSEL_Pos)
#define RCC_USB3PCIEPHYKERCLKSOURCE_HSE_KER_CLK           (0x1U << RCC_USB3PCIEPHYCFGR_USB3PCIEPHYCKREFSEL_Pos)

#define IS_RCC_USB3PCIEPHYKERCLKSOURCE(SOURCE) (((SOURCE) == RCC_USB3PCIEPHYKERCLKSOURCE_CK_KER_USB3PCIEPHY) || \
                                                ((SOURCE) == RCC_USB3PCIEPHYKERCLKSOURCE_HSE_KER_CLK))

/**
  * @brief  Macro to select USB3PCIEPHY kernel source clock
  *
  * @param  __RCC_USB3PCIEPHYKERSOURCE__: specifies the USB3PCIEPHY entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USB3PCIEPHYKERCLKSOURCE_CK_KER_USB3PCIEPHY: "ck_ker_USB3PCIEPHY"   Flexiclockgen output 34
  *            @arg RCC_USB3PCIEPHYKERCLKSOURCE_HSE_KER_CLK:     "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  *
  * @retval None
  */
#define __HAL_RCC_USB3PCIEPHYKERCLK_SETSOURCE(__RCC_USB3PCIEPHYKERSOURCE__) \
  MODIFY_REG( RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYCKREFSEL, (__RCC_USB3PCIEPHYKERSOURCE__)  )

/** @brief  Macro to get the clock source used as USB3PCIEPHY kernel source clock.
  * @retval The clock source used as USB3PCIEPHY kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_USB3PCIEPHYKERCLKSOURCE_CK_KER_USB3PCIEPHY: "ck_ker_USB3PCIEPHY"   Flexiclockgen output 34
  *            @arg RCC_USB3PCIEPHYKERCLKSOURCE_HSE_KER_CLK:     "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  */
#define __HAL_RCC_USB3PCIEPHYKERCLK_GETSOURCE()  (RCC->USB3PCIEPHYCFGR & RCC_USB3PCIEPHYCFGR_USB3PCIEPHYCKREFSEL_Msk)
/**
  * @}
  */

#if defined(DSI)
/** @defgroup RCC_DSIPHY_Kernel_Clock_Source RCC_DSIPHY_Kernel_Clock_Source
  * @{
  */
#define RCC_DSIPHYKERCLKSOURCE_CK_KER_DSIPHY    (0x0U << RCC_DSICFGR_DSIPHYCKREFSEL_Pos)
#define RCC_DSIPHYKERCLKSOURCE_HSE_KER_CLK      (0x1U << RCC_DSICFGR_DSIPHYCKREFSEL_Pos)

#define IS_RCC_DSIPHYKERCLKSOURCE(SOURCE) (((SOURCE) == RCC_DSIPHYKERCLKSOURCE_CK_KER_DSIPHY) || \
                                           ((SOURCE) == RCC_DSIPHYKERCLKSOURCE_HSE_KER_CLK))

/**
  * @brief  Macro to select DSIPHY kernel source clock
  *
  * @param  __RCC_DSIPHYKERSOURCE__: specifies the DSIPHY entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_DSIPHYKERCLKSOURCE_CK_KER_DSIPHY: "ck_ker_DSIPHY"   Flexiclockgen output 28
  *            @arg RCC_DSIPHYKERCLKSOURCE_HSE_KER_CLK:   "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  *
  * @retval None
  */
#define __HAL_RCC_DSIPHYKERCLK_SETSOURCE(__RCC_DSIPHYKERSOURCE__) \
  MODIFY_REG( RCC->DSICFGR, RCC_DSICFGR_DSIPHYCKREFSEL, (__RCC_DSIPHYKERSOURCE__)  )

/** @brief  Macro to get the clock source used as DSIPHY kernel source clock.
  * @retval The clock source used as DSIPHY kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_DSIPHYKERCLKSOURCE_CK_KER_DSIPHY: "ck_ker_DSIPHY"   Flexiclockgen output 28
  *            @arg RCC_DSIPHYKERCLKSOURCE_HSE_KER_CLK:   "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  */
#define __HAL_RCC_DSIPHYKERCLK_GETSOURCE()  (RCC->DSICFGR & RCC_DSICFGR_DSIPHYCKREFSEL_Msk)
/**
  * @}
  */

/** @defgroup RCC_DSIBL_Kernel_Clock_Source RCC_DSIBL_Kernel_Clock_Source
  * @{
  */
#define RCC_DSIBLKERCLKSOURCE_CK_DSIPHY_SEL    (0x0U << RCC_DSICFGR_DSIBLSEL_Pos)
#define RCC_DSIBLKERCLKSOURCE_CK_KER_LTDC      (0x1U << RCC_DSICFGR_DSIBLSEL_Pos)

#define IS_RCC_DSIBLKERCLKSOURCE(SOURCE) (((SOURCE) == RCC_DSIBLKERCLKSOURCE_CK_DSIPHY_SEL) || \
                                          ((SOURCE) == RCC_DSIBLKERCLKSOURCE_CK_KER_LTDC))

/**
  * @brief  Macro to select DSIBL kernel source clock
  *
  * @param  __RCC_DSIBLKERSOURCE__: specifies the DSIBL entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_DSIBLKERCLKSOURCE_CK_DSIPHY_SEL: DSIPHY clock is selected
  *            @arg RCC_DSIBLKERCLKSOURCE_CK_KER_LTDC:  "ck_ker_LTDC"   Flexiclockgen output 27
  *
  * @retval None
  */
#define __HAL_RCC_DSIBLKERCLK_SETSOURCE(__RCC_DSIBLKERSOURCE__) \
  MODIFY_REG( RCC->DSICFGR, RCC_DSICFGR_DSIBLSEL, (__RCC_DSIBLKERSOURCE__)  )

/** @brief  Macro to get the clock source used as DSIBL kernel source clock.
  * @retval The clock source used as DSIBL kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_DSIBLKERCLKSOURCE_CK_DSIPHY_SEL: DSIPHY clock is selected
  *            @arg RCC_DSIBLKERCLKSOURCE_CK_KER_LTDC:  "ck_ker_LTDC"   Flexiclockgen output 27
  */
#define __HAL_RCC_DSIBLKERCLK_GETSOURCE() (RCC->DSICFGR & RCC_DSICFGR_DSIBLSEL_Msk)
#endif /* DSI */
/**
  * @}
  */

/** @defgroup RCC_LVDSPHY_Kernel_Clock_Source RCC_LVDSPHY_Kernel_Clock_Source
  *  @{
  */
#define RCC_LVDSPHYKERCLKSOURCE_CK_KER_LVDSPHY    (0x0U << RCC_LVDSCFGR_LVDSPHYCKREFSEL_Pos)
#define RCC_LVDSPHYKERCLKSOURCE_HSE_KER_CLK       (0x1U << RCC_LVDSCFGR_LVDSPHYCKREFSEL_Pos)

#define IS_RCC_LVDSPHYKERCLKSOURCE(SOURCE) (((SOURCE) == RCC_LVDSPHYKERCLKSOURCE_CK_KER_LVDSPHY) || \
                                            ((SOURCE) == RCC_LVDSPHYKERCLKSOURCE_HSE_KER_CLK))

/**
  * @brief  Macro to select LVDSPHY kernel source clock
  *
  * @param  __RCC_LVDSPHYKERSOURCE__: specifies the LVDSPHY entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LVDSPHYKERCLKSOURCE_CK_KER_LVDSPHY: "ck_ker_LVDSPHY"   Flexiclockgen output 32
  *            @arg RCC_LVDSPHYKERCLKSOURCE_HSE_KER_CLK:     "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  *
  * @retval None
  */
#define __HAL_RCC_LVDSPHYKERCLK_SETSOURCE(__RCC_LVDSPHYKERSOURCE__) \
  MODIFY_REG( RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSPHYCKREFSEL, (__RCC_LVDSPHYKERSOURCE__)  )

/** @brief  Macro to get the clock source used as LVDSPHY kernel source clock.
  * @retval The clock source used as LVDSPHY kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_LVDSPHYKERCLKSOURCE_CK_KER_LVDSPHY: "ck_ker_LVDSPHY"   Flexiclockgen output 32
  *            @arg RCC_LVDSPHYKERCLKSOURCE_HSE_KER_CLK:     "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  */
#define __HAL_RCC_LVDSPHYKERCLK_GETSOURCE() (RCC->LVDSCFGR & RCC_LVDSCFGR_LVDSPHYCKREFSEL_Msk)
/**
  * @}
  */

/** @defgroup RCC_DTS_Kernel_Clock_Source RCC_DTS_Kernel_Clock_Source
  *  @{
  */

#define RCC_DTSKERCLKSOURCE_HSI_KER_CLK    (0x0U << RCC_DTSCFGR_DTSKERSEL_Pos)
#define RCC_DTSKERCLKSOURCE_HSE_KER_CLK    (0x1U << RCC_DTSCFGR_DTSKERSEL_Pos)
#define RCC_DTSKERCLKSOURCE_MSI_KER_CLK    (0x2U << RCC_DTSCFGR_DTSKERSEL_Pos)

#define IS_RCC_DTSKERCLKSOURCE(SOURCE) (((SOURCE) == RCC_DTSKERCLKSOURCE_HSI_KER_CLK) || \
                                        ((SOURCE) == RCC_DTSKERCLKSOURCE_HSE_KER_CLK) ||\
                                        ((SOURCE) == RCC_DTSKERCLKSOURCE_MSI_KER_CLK))

/**
  * @brief  Macro to select DTS kernel source clock
  *
  * @param  __RCC_DTSKERSOURCE__: specifies the DTS entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_DTSKERCLKSOURCE_HSI_KER_CLK:     "RCC_XBAR_CLKSRC_HSI_KER" RCC_Xbar_sourc
  *            @arg RCC_DTSKERCLKSOURCE_HSE_KER_CLK:     "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  *            @arg RCC_DTSKERCLKSOURCE_MSI_KER_CLK:     "RCC_XBAR_CLKSRC_MSI_KER" RCC_Xbar_sourc
  *
  * @retval None
  */
#define __HAL_RCC_DTSKERCLK_SETSOURCE(__RCC_DTSKERSOURCE__) \
  MODIFY_REG( RCC->TMPSENSCFGR, RCC_DTSCFGR_DTSKERSEL, (__RCC_DTSKERSOURCE__)  )

/** @brief  Macro to get the clock source used as DTS kernel source clock.
  * @retval The clock source used as DTS kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_DTSKERCLKSOURCE_HSI_KER_CLK:     "RCC_XBAR_CLKSRC_HSI_KER" RCC_Xbar_sourc
  *            @arg RCC_DTSKERCLKSOURCE_HSE_KER_CLK:     "RCC_XBAR_CLKSRC_HSE_KER" RCC_Xbar_source
  *            @arg RCC_DTSKERCLKSOURCE_MSI_KER_CLK:     "RCC_XBAR_CLKSRC_MSI_KER" RCC_Xbar_sourc
  */
#define __HAL_RCC_DTSKERCLK_GETSOURCE() (RCC->TMPSENSCFGR & RCC_DTSCFGR_DTSKERSEL_Msk)
/**
  * @}
  */

/** @defgroup RCC_RTC_Kernel_Clock_Source RCC_RTC_Kernel_Clock_Source
  *  @{
  */

#define RCC_RTCKERCLKSOURCE_CLK_NONE       (0x0U << RCC_BDCR_RTCSRC_Pos)
#define RCC_RTCKERCLKSOURCE_LSE_KER_CLK    (0x1U << RCC_BDCR_RTCSRC_Pos)
#define RCC_RTCKERCLKSOURCE_LSI_KER_CLK    (0x2U << RCC_BDCR_RTCSRC_Pos)
#define RCC_RTCKERCLKSOURCE_HSE_RTCDIV     (0x3U << RCC_BDCR_RTCSRC_Pos)

#define IS_RCC_RTCKERCLKSOURCE(SOURCE) (((SOURCE) == RCC_RTCKERCLKSOURCE_CLK_NONE)    || \
                                        ((SOURCE) == RCC_RTCKERCLKSOURCE_LSE_KER_CLK) || \
                                        ((SOURCE) == RCC_RTCKERCLKSOURCE_LSI_KER_CLK) || \
                                        ((SOURCE) == RCC_RTCKERCLKSOURCE_HSE_RTCDIV))

/**
  * @brief  Macro to select RTC kernel source clock
  *
  * @param  __RCC_RTCKERSOURCE__: specifies the RTC entry kernel clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_RTCKERCLKSOURCE_CLK_NONE:         No clock source
  *            @arg RCC_RTCKERCLKSOURCE_LSE_KER_CLK:     "RCC_XBAR_CLKSRC_LSE" RCC_Xbar_sourc
  *            @arg RCC_RTCKERCLKSOURCE_LSI_KER_CLK:     "RCC_XBAR_CLKSRC_LSI" RCC_Xbar_source
  *            @arg RCC_RTCKERCLKSOURCE_HSE_RTCDIV:       RTC HSE PRESCALER
  *
  * @retval None
  */
#define __HAL_RCC_RTCKERCLK_SETSOURCE(__RCC_RTCKERSOURCE__) \
  MODIFY_REG( RCC->BDCR, RCC_BDCR_RTCSRC, (__RCC_RTCKERSOURCE__)  )

/** @brief  Macro to get the clock source used as RTC kernel source clock.
  * @retval The clock source used as RTC kernel source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_RTCKERCLKSOURCE_CLK_NONE:         No clock source
  *            @arg RCC_RTCKERCLKSOURCE_LSE_KER_CLK:     "RCC_XBAR_CLKSRC_LSE" RCC_Xbar_sourc
  *            @arg RCC_RTCKERCLKSOURCE_LSI_KER_CLK:     "RCC_XBAR_CLKSRC_LSI" RCC_Xbar_source
  *            @arg RCC_RTCKERCLKSOURCE_HSE_RTCDIV:       RTC HSE PRESCALER
  */
#define __HAL_RCC_RTCKERCLK_GETSOURCE() (RCC->BDCR & RCC_BDCR_RTCSRC_Msk)

/**
  * @brief  Macro to select HSE Prescaler for RTC Clock
  *
  * @param  __RCC_RTCPRESCALER__: specifies the RTC prescaler value
  *          This parameter can be one of the following values:
  *         @arg  RCC_RTC_HSE_DIV_1
  *         @arg  RCC_RTC_HSE_DIV_2
  *         @arg  RCC_RTC_HSE_DIV_3
  *         @arg  RCC_RTC_HSE_DIV_4
  *         @arg  RCC_RTC_HSE_DIV_5
  *         @arg  RCC_RTC_HSE_DIV_6
  *         @arg  RCC_RTC_HSE_DIV_7
  *         @arg  RCC_RTC_HSE_DIV_8
  *         @arg  RCC_RTC_HSE_DIV_9
  *         @arg  RCC_RTC_HSE_DIV_10
  *         @arg  RCC_RTC_HSE_DIV_11
  *         @arg  RCC_RTC_HSE_DIV_12
  *         @arg  RCC_RTC_HSE_DIV_13
  *         @arg  RCC_RTC_HSE_DIV_14
  *         @arg  RCC_RTC_HSE_DIV_15
  *         @arg  RCC_RTC_HSE_DIV_16
  *         @arg  RCC_RTC_HSE_DIV_17
  *         @arg  RCC_RTC_HSE_DIV_18
  *         @arg  RCC_RTC_HSE_DIV_19
  *         @arg  RCC_RTC_HSE_DIV_20
  *         @arg  RCC_RTC_HSE_DIV_21
  *         @arg  RCC_RTC_HSE_DIV_22
  *         @arg  RCC_RTC_HSE_DIV_23
  *         @arg  RCC_RTC_HSE_DIV_24
  *         @arg  RCC_RTC_HSE_DIV_25
  *         @arg  RCC_RTC_HSE_DIV_26
  *         @arg  RCC_RTC_HSE_DIV_27
  *         @arg  RCC_RTC_HSE_DIV_28
  *         @arg  RCC_RTC_HSE_DIV_29
  *         @arg  RCC_RTC_HSE_DIV_30
  *         @arg  RCC_RTC_HSE_DIV_31
  *         @arg  RCC_RTC_HSE_DIV_32
  *         @arg  RCC_RTC_HSE_DIV_33
  *         @arg  RCC_RTC_HSE_DIV_34
  *         @arg  RCC_RTC_HSE_DIV_35
  *         @arg  RCC_RTC_HSE_DIV_36
  *         @arg  RCC_RTC_HSE_DIV_37
  *         @arg  RCC_RTC_HSE_DIV_38
  *         @arg  RCC_RTC_HSE_DIV_39
  *         @arg  RCC_RTC_HSE_DIV_40
  *         @arg  RCC_RTC_HSE_DIV_41
  *         @arg  RCC_RTC_HSE_DIV_42
  *         @arg  RCC_RTC_HSE_DIV_43
  *         @arg  RCC_RTC_HSE_DIV_44
  *         @arg  RCC_RTC_HSE_DIV_45
  *         @arg  RCC_RTC_HSE_DIV_46
  *         @arg  RCC_RTC_HSE_DIV_47
  *         @arg  RCC_RTC_HSE_DIV_48
  *         @arg  RCC_RTC_HSE_DIV_49
  *         @arg  RCC_RTC_HSE_DIV_50
  *         @arg  RCC_RTC_HSE_DIV_51
  *         @arg  RCC_RTC_HSE_DIV_52
  *         @arg  RCC_RTC_HSE_DIV_53
  *         @arg  RCC_RTC_HSE_DIV_54
  *         @arg  RCC_RTC_HSE_DIV_55
  *         @arg  RCC_RTC_HSE_DIV_56
  *         @arg  RCC_RTC_HSE_DIV_57
  *         @arg  RCC_RTC_HSE_DIV_58
  *         @arg  RCC_RTC_HSE_DIV_59
  *         @arg  RCC_RTC_HSE_DIV_60
  *         @arg  RCC_RTC_HSE_DIV_61
  *         @arg  RCC_RTC_HSE_DIV_62
  *         @arg  RCC_RTC_HSE_DIV_63
  *         @arg  RCC_RTC_HSE_DIV_64
  * @retval None
  */
#define __HAL_RCC_RTC_SETPRESCALER(__RCC_RTCPRESCALER__) \
  MODIFY_REG( RCC->RTCDIVR, RCC_RTCDIVR_RTCDIV, (__RCC_RTCPRESCALER__) )

/**
  * @brief  Macro to Get HSE Prescaler for RTC Clock
  *
  * @retval  This parameter can be one of the following values:
  *         @arg  RCC_RTC_HSE_DIV_1
  *         @arg  RCC_RTC_HSE_DIV_2
  *         @arg  RCC_RTC_HSE_DIV_3
  *         @arg  RCC_RTC_HSE_DIV_4
  *         @arg  RCC_RTC_HSE_DIV_5
  *         @arg  RCC_RTC_HSE_DIV_6
  *         @arg  RCC_RTC_HSE_DIV_7
  *         @arg  RCC_RTC_HSE_DIV_8
  *         @arg  RCC_RTC_HSE_DIV_9
  *         @arg  RCC_RTC_HSE_DIV_10
  *         @arg  RCC_RTC_HSE_DIV_11
  *         @arg  RCC_RTC_HSE_DIV_12
  *         @arg  RCC_RTC_HSE_DIV_13
  *         @arg  RCC_RTC_HSE_DIV_14
  *         @arg  RCC_RTC_HSE_DIV_15
  *         @arg  RCC_RTC_HSE_DIV_16
  *         @arg  RCC_RTC_HSE_DIV_17
  *         @arg  RCC_RTC_HSE_DIV_18
  *         @arg  RCC_RTC_HSE_DIV_19
  *         @arg  RCC_RTC_HSE_DIV_20
  *         @arg  RCC_RTC_HSE_DIV_21
  *         @arg  RCC_RTC_HSE_DIV_22
  *         @arg  RCC_RTC_HSE_DIV_23
  *         @arg  RCC_RTC_HSE_DIV_24
  *         @arg  RCC_RTC_HSE_DIV_25
  *         @arg  RCC_RTC_HSE_DIV_26
  *         @arg  RCC_RTC_HSE_DIV_27
  *         @arg  RCC_RTC_HSE_DIV_28
  *         @arg  RCC_RTC_HSE_DIV_29
  *         @arg  RCC_RTC_HSE_DIV_30
  *         @arg  RCC_RTC_HSE_DIV_31
  *         @arg  RCC_RTC_HSE_DIV_32
  *         @arg  RCC_RTC_HSE_DIV_33
  *         @arg  RCC_RTC_HSE_DIV_34
  *         @arg  RCC_RTC_HSE_DIV_35
  *         @arg  RCC_RTC_HSE_DIV_36
  *         @arg  RCC_RTC_HSE_DIV_37
  *         @arg  RCC_RTC_HSE_DIV_38
  *         @arg  RCC_RTC_HSE_DIV_39
  *         @arg  RCC_RTC_HSE_DIV_40
  *         @arg  RCC_RTC_HSE_DIV_41
  *         @arg  RCC_RTC_HSE_DIV_42
  *         @arg  RCC_RTC_HSE_DIV_43
  *         @arg  RCC_RTC_HSE_DIV_44
  *         @arg  RCC_RTC_HSE_DIV_45
  *         @arg  RCC_RTC_HSE_DIV_46
  *         @arg  RCC_RTC_HSE_DIV_47
  *         @arg  RCC_RTC_HSE_DIV_48
  *         @arg  RCC_RTC_HSE_DIV_49
  *         @arg  RCC_RTC_HSE_DIV_50
  *         @arg  RCC_RTC_HSE_DIV_51
  *         @arg  RCC_RTC_HSE_DIV_52
  *         @arg  RCC_RTC_HSE_DIV_53
  *         @arg  RCC_RTC_HSE_DIV_54
  *         @arg  RCC_RTC_HSE_DIV_55
  *         @arg  RCC_RTC_HSE_DIV_56
  *         @arg  RCC_RTC_HSE_DIV_57
  *         @arg  RCC_RTC_HSE_DIV_58
  *         @arg  RCC_RTC_HSE_DIV_59
  *         @arg  RCC_RTC_HSE_DIV_60
  *         @arg  RCC_RTC_HSE_DIV_61
  *         @arg  RCC_RTC_HSE_DIV_62
  *         @arg  RCC_RTC_HSE_DIV_63
  *         @arg  RCC_RTC_HSE_DIV_64
  */
#define __HAL_RCC_RTC_GETPRESCALER() (RCC->RTCDIVR & RCC_BDCR_RTCSRC_Msk)
/**
  * @}
  */

/** @defgroup RCC_MCO1_Clock_Output_Source RCC_MCO1_Kernel_Clock_Output_Source
  *  @{
  */

#define RCC_MCO1CLKOUTPUTSOURCE_CLK_MCO1       (0x0U << RCC_MCO1CFGR_MCO1SEL_Pos)
#define RCC_MCO1CLKOUTPUTSOURCE_CLK_CKOBS0     (0x1U << RCC_MCO1CFGR_MCO1SEL_Pos)

#define IS_RCC_MCO1CLKOUTPUTSOURCE(SOURCE) (((SOURCE) == RCC_MCO1CLKOUTPUTSOURCE_CLK_MCO1) || \
                                            ((SOURCE) == RCC_MCO1CLKOUTPUTSOURCE_CLK_CKOBS0) )

/**
  * @brief  Macro to select MCO1 output source clock
  *
  * @param  __RCC_MCO1OUTPUTSOURCE__: specifies the MCO1 output clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCO1CLKOUTPUTSOURCE_CLK_MCO1:     "ck_mco1"   Flexiclockgen output 61
  *            @arg RCC_MCO1CLKOUTPUTSOURCE_CLK_CKOBS0:   "ck_obs0"   Flexiclockgen channel 0
  *
  * @retval None
  */
#define __HAL_RCC_MCO1KERCLK_SETSOURCE(__RCC_MCO1OUTPUTSOURCE__) \
  MODIFY_REG( RCC->MCO1CFGR, RCC_MCO1CFGR_MCO1SEL, (__RCC_MCO1OUTPUTSOURCE__)  )

/** @brief  Macro to get the clock source used as MCO1 output source clock.
  * @retval The clock source used as MCO1 output source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_MCO1CLKOUTPUTSOURCE_CLK_MCO1:     "ck_mco1"   Flexiclockgen output 61
  *            @arg RCC_MCO1CLKOUTPUTSOURCE_CLK_CKOBS0:   "ck_obs0"   Flexiclockgen channel 0
  */
#define __HAL_RCC_MCO1KERCLK_GETSOURCE()  (RCC->MCO1CFGR & RCC_MCO1CFGR_MCO1SEL_Msk)
/**
  * @}
  */

/** @defgroup RCC_MCO2_Clock_Output_Source RCC_MCO2_Kernel_Clock_Output_Source
  *  @{
  */

#define RCC_MCO2CLKOUTPUTSOURCE_CLK_MCO2       (0x0U << RCC_MCO2CFGR_MCO2SEL_Pos)
#define RCC_MCO2CLKOUTPUTSOURCE_CLK_CKOBS1     (0x1U << RCC_MCO2CFGR_MCO2SEL_Pos)

#define IS_RCC_MCO2CLKOUTPUTSOURCE(SOURCE) (((SOURCE) == RCC_MCO2CLKOUTPUTSOURCE_CLK_MCO2) || \
                                            ((SOURCE) == RCC_MCO2CLKOUTPUTSOURCE_CLK_CKOBS1) )

/**
  * @brief  Macro to select MCO2 output source clock
  *
  * @param  __RCC_MCO2OUTPUTSOURCE__: specifies the MCO2 output clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCO2CLKOUTPUTSOURCE_CLK_MCO2:     "ck_MCO2"   Flexiclockgen output 62
  *            @arg RCC_MCO2CLKOUTPUTSOURCE_CLK_CKOBS1:   "ck_obs0"   Flexiclockgen channel 1
  *
  * @retval None
  */
#define __HAL_RCC_MCO2KERCLK_SETSOURCE(__RCC_MCO2OUTPUTSOURCE__) \
  MODIFY_REG( RCC->MCO2CFGR, RCC_MCO2CFGR_MCO2SEL, (__RCC_MCO2OUTPUTSOURCE__)  )

/** @brief  Macro to get the clock source used as MCO2 output source clock.
  * @retval The clock source used as MCO2 output source clock. The returned value can be one
  *         of the following:
  *            @arg RCC_MCO2CLKOUTPUTSOURCE_CLK_MCO2:     "ck_MCO2"   Flexiclockgen output 62
  *            @arg RCC_MCO2CLKOUTPUTSOURCE_CLK_CKOBS1:   "ck_obs0"   Flexiclockgen channel 1
  */
#define __HAL_RCC_MCO2KERCLK_GETSOURCE()  (RCC->MCO2CFGR & RCC_MCO2CFGR_MCO2SEL_Msk)
/**
  * @}
  */

/** @brief Enable RCC interrupt (Perform Byte access to RCC_CIR[14:8] bits to enable
  *        the selected interrupts).
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to enabled.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY:  LSI ready interrupt
  *            @arg RCC_IT_LSERDY:  LSE ready interrupt
  *            @arg RCC_IT_HSIRDY:  HSI ready interrupt
  *            @arg RCC_IT_HSERDY:  HSE ready interrupt
  *            @arg RCC_IT_MSIRDY:  MSI ready interrupt
  *            @arg RCC_IT_PLL1RDY: PLL1RDY ready interrupt
  *            @arg RCC_IT_PLL2RDY: PLL2RDY ready interrupt
  *            @arg RCC_IT_PLL3RDY: PLL3RDY ready interrupt
  *            @arg RCC_IT_PLL4RDY: PLL4RDY ready interrupt
  *            @arg RCC_IT_PLL5RDY: PLL5RDY ready interrupt
  *            @arg RCC_IT_PLL6RDY: PLL2RDY ready interrupt
  *            @arg RCC_IT_PLL7RDY: PLL3RDY ready interrupt
  *            @arg RCC_IT_PLL8RDY: PLL4RDY ready interrupt
  *            @arg RCC_IT_LSECSS:  LSE Clock security system interrupt
  *            @arg RCC_IT_WKUP:    Wake-up from CSTOP Interrupt
  */
#ifdef CORE_CM33
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->C2CIESETR, (__INTERRUPT__))
#endif /* CORE_CM33 */
#ifdef CORE_CA35
#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) SET_BIT(RCC->C1CIESETR, (__INTERRUPT__))
#endif /* CORE_CA35 */

/** @brief Disable RCC interrupt (Perform Byte access to RCC_CIR[14:8] bits to disable
  *        the selected interrupts).
  * @param  __INTERRUPT__: specifies the RCC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *           @arg RCC_IT_LSIRDY:  LSI ready interrupt
  *           @arg RCC_IT_LSERDY:  LSE ready interrupt
  *           @arg RCC_IT_HSIRDY:  HSI ready interrupt
  *           @arg RCC_IT_HSERDY:  HSE ready interrupt
  *           @arg RCC_IT_MSIRDY:  MSI ready interrupt
  *           @arg RCC_IT_PLL1RDY: PLL1RDY ready interrupt
  *           @arg RCC_IT_PLL2RDY: PLL2RDY ready interrupt
  *           @arg RCC_IT_PLL3RDY: PLL3RDY ready interrupt
  *           @arg RCC_IT_PLL4RDY: PLL4RDY ready interrupt
  *           @arg RCC_IT_PLL5RDY: PLL5RDY ready interrupt
  *           @arg RCC_IT_PLL6RDY: PLL2RDY ready interrupt
  *           @arg RCC_IT_PLL7RDY: PLL3RDY ready interrupt
  *           @arg RCC_IT_PLL8RDY: PLL4RDY ready interrupt
  *           @arg RCC_IT_LSECSS:  LSE Clock security system interrupt
  *           @arg RCC_IT_WKUP:    Wake-up from CSTOP Interrupt
  */
#ifdef CORE_CM33
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->C2CIESETR, (__INTERRUPT__))
#endif /* CORE_CM33 */
#ifdef CORE_CA35
#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) CLEAR_BIT(RCC->C1CIESETR, (__INTERRUPT__))
#endif /* CORE_CA35 */

/** @brief  Clear the RCC's interrupt pending bits (Perform Byte access to RCC_CIR[23:16]
  *         bits to clear the selected interrupt pending bits.
  * @param  __INTERRUPT__: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *           @arg RCC_IT_LSIRDY:  LSI ready interrupt
  *           @arg RCC_IT_LSERDY:  LSE ready interrupt
  *           @arg RCC_IT_HSIRDY:  HSI ready interrupt
  *           @arg RCC_IT_HSERDY:  HSE ready interrupt
  *           @arg RCC_IT_MSIRDY:  MSI ready interrupt
  *           @arg RCC_IT_PLL1RDY: PLL1RDY ready interrupt
  *           @arg RCC_IT_PLL2RDY: PLL2RDY ready interrupt
  *           @arg RCC_IT_PLL3RDY: PLL3RDY ready interrupt
  *           @arg RCC_IT_PLL4RDY: PLL4RDY ready interrupt
  *           @arg RCC_IT_PLL5RDY: PLL5RDY ready interrupt
  *           @arg RCC_IT_PLL6RDY: PLL2RDY ready interrupt
  *           @arg RCC_IT_PLL7RDY: PLL3RDY ready interrupt
  *           @arg RCC_IT_PLL8RDY: PLL4RDY ready interrupt
  *           @arg RCC_IT_LSECSS:  LSE Clock security system interrupt
  *           @arg RCC_IT_WKUP:    Wake-up from CSTOP Interrupt
  */
#ifdef CORE_CM33
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (RCC->C2CIFCLRR = (__INTERRUPT__))
#endif /* CORE_CM33 */
#ifdef CORE_CA35
#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (RCC->C1CIFCLRR = (__INTERRUPT__))
#endif /* CORE_CA35 */

/** @brief  Check the RCC's interrupt has occurred or not.
  * @param  __INTERRUPT__: specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *           @arg RCC_IT_LSIRDY:  LSI ready interrupt
  *           @arg RCC_IT_LSERDY:  LSE ready interrupt
  *           @arg RCC_IT_HSIRDY:  HSI ready interrupt
  *           @arg RCC_IT_HSERDY:  HSE ready interrupt
  *           @arg RCC_IT_MSIRDY:  MSI ready interrupt
  *           @arg RCC_IT_PLL1RDY: PLL1RDY ready interrupt
  *           @arg RCC_IT_PLL2RDY: PLL2RDY ready interrupt
  *           @arg RCC_IT_PLL3RDY: PLL3RDY ready interrupt
  *           @arg RCC_IT_PLL4RDY: PLL4RDY ready interrupt
  *           @arg RCC_IT_PLL5RDY: PLL5RDY ready interrupt
  *           @arg RCC_IT_PLL6RDY: PLL2RDY ready interrupt
  *           @arg RCC_IT_PLL7RDY: PLL3RDY ready interrupt
  *           @arg RCC_IT_PLL8RDY: PLL4RDY ready interrupt
  *           @arg RCC_IT_LSECSS:  LSE Clock security system interrupt
  *           @arg RCC_IT_WKUP:    Wake-up from CSTOP Interrupt
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#ifdef CORE_CM33
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->C2CIFCLRR & (__INTERRUPT__)) == (__INTERRUPT__))
#endif /* CORE_CM33 */
#ifdef CORE_CA35
#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->C1CIFCLRR & (__INTERRUPT__)) == (__INTERRUPT__))
#endif /* CORE_CA35 */


/* RCC_Calibration limits */
#define IS_RCC_HSICALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1FFU)
#define IS_RCC_MSICALIBRATION_VALUE(VALUE) ((VALUE) <= 0xFFU)

/* MCO1 clock output control */
#define __HAL_RCC_MCO1_ENABLE()   SET_BIT(RCC->MCO1CFGR, RCC_MCO1CFGR_MCO1ON)
#define __HAL_RCC_MCO1_DISABLE()  CLEAR_BIT(RCC->MCO1CFGR, RCC_MCO1CFGR_MCO1ON)

/* MCO2 clock output control */
#define __HAL_RCC_MCO2_ENABLE()   SET_BIT(RCC->MCO2CFGR, RCC_MCO2CFGR_MCO2ON)
#define __HAL_RCC_MCO2_DISABLE()  CLEAR_BIT(RCC->MCO2CFGR, RCC_MCO2CFGR_MCO2ON)

/** @defgroup RCC_HAL_RIF_Exported_Macros RCC HAL RIF Exported Macros
  * @{
  */
#if !defined(RCC_DERIVATIVE1_LOCAL_RESOURCES_MAPPING)
#define IS_LOCALRES_INDEX(INDEX) (((INDEX) >= RCC_LOCALRES_0) && \
                                  ((INDEX) <= RCC_LOCALRES_113))
#else
#define IS_LOCALRES_INDEX(INDEX) ((((INDEX) >= RCC_LOCALRES_0)    && \
                                   ((INDEX) <= RCC_LOCALRES_113)) && \
                                  (((INDEX) != RCC_LOCALRES_72)   &&\
                                   ((INDEX) != RCC_LOCALRES_80)  &&\
                                   ((INDEX) != RCC_LOCALRES_81)  &&\
                                   ((INDEX) != RCC_LOCALRES_82)  &&\
                                   ((INDEX) != RCC_LOCALRES_89)  &&\
                                   ((INDEX) != RCC_LOCALRES_99)  &&\
                                   ((INDEX) != RCC_LOCALRES_100) &&\
                                   ((INDEX) != RCC_LOCALRES_107)))
#endif /* RCC_DERIVATIVE1_LOCAL_RESOURCES_MAPPING */

/* On secure Cortex core only : */
#if defined(CORTEX_IN_SECURE_STATE)
#define IS_PRIV_ATTRIBUTE(ATTRIBUTE) (((ATTRIBUTE) == RCC_LOCALRES_PRIV)   || \
                                      ((ATTRIBUTE) == RCC_LOCALRES_NOPRIV) || \
                                      ((ATTRIBUTE) == RCC_LOCALRES_ATTR_NONE))

#define IS_LOCK_ATTRIBUTE(ATTRIBUTE) (((ATTRIBUTE) == RCC_LOCALRES_LOCKED) || \
                                      ((ATTRIBUTE) == RCC_LOCALRES_ATTR_NONE))

#define IS_SEC_ATTRIBUTE(ATTRIBUTE) (((ATTRIBUTE) == RCC_LOCALRES_SEC)   || \
                                     ((ATTRIBUTE) == RCC_LOCALRES_NOSEC) || \
                                     ((ATTRIBUTE) == RCC_LOCALRES_ATTR_NONE))

#define IS_CID_ATTRIBUTE(ATTRIBUTE) (((ATTRIBUTE) == RCC_LOCALRES_CID_TYPE_NONE) || \
                                     ((((ATTRIBUTE) & RCC_LOCALRES_ATTR_CID_TYPE_MSK) == \
                                       RCC_LOCALRES_CID_TYPE_STATIC) && \
                                      ((~(ATTRIBUTE) & ~RCC_LOCALRES_CID_STATIC_MSK) == \
                                       ~RCC_LOCALRES_CID_STATIC_MSK)) || \
                                     ((((ATTRIBUTE) & RCC_LOCALRES_ATTR_CID_TYPE_MSK) == \
                                       RCC_LOCALRES_CID_TYPE_DYNAMIC) && \
                                      ((~(ATTRIBUTE) & ~RCC_LOCALRES_CID_DYNAMIC_MSK) == \
                                       ~RCC_LOCALRES_CID_DYNAMIC_MSK )))
#endif /* CORTEX_IN_SECURE_STATE */
/**
  * @}
  */

/**
  * @}
  */
/* Include RCC HAL Extended module */
#include "stm32mp2xx_hal_rcc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */

uint32_t HAL_RCC_GetFreq(uint32_t clk);
uint32_t HAL_RCC_GetSource(uint32_t clk_id);
uint32_t HAL_RCC_GetCM33Freq(void);
#if defined(CORE_CA35)
uint32_t HAL_RCC_GetCA35Freq(void);
#endif /* CORE_CA35 */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef *pRCC_OscInitStruct);
void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *pRCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef *const pRCC_ClkInitStruct, uint32_t FLatency);
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *pRCC_ClkInitStruct, const uint32_t *pFLatency);
void HAL_RCC_IRQHandler(void);
void HAL_RCC_WAKEUP_IRQHandler(void);
void HAL_RCC_HSIMON_Callback(uint32_t Flags);
void HAL_RCC_WAKEUP_Callback(uint32_t Flags);
void HAL_RCC_Callback(uint32_t Flags);
/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  **********************************************/
void HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);

/**
  * @}
  */

/* Attributes management functions ********************************************/
#if defined(CORTEX_IN_SECURE_STATE)
HAL_StatusTypeDef HAL_RCC_ConfigAttributes(uint32_t LocalResIndex, uint32_t LocalResAttributes);
#endif /* CORTEX_IN_SECURE_STATE */

HAL_StatusTypeDef HAL_RCC_GetConfigAttributes(uint32_t LocalResIndex, uint32_t *pLocalResAttributes);
HAL_StatusTypeDef HAL_RCC_TakeLocalResSemaphore(uint32_t LocalResIndex);
HAL_StatusTypeDef HAL_RCC_ReleaseLocalResSemaphore(uint32_t LocalResIndex);

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

#endif /* STM32MP2xx_HAL_RCC_H */
