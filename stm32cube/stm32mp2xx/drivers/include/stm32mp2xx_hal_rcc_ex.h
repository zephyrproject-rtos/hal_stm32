/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended  module.
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
#ifndef STM32MP2xx_HAL_RCC_EX_H
#define STM32MP2xx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
  */

/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCCEx_RCC_BootCx RCC BootCx
  * @{
  */
#define RCC_BOOT_C1                     RCC_STBYBOOTCR_CPU1_HW_BEN
#define RCC_BOOT_C2                     RCC_STBYBOOTCR_CPU2_HW_BEN

#define IS_RCC_BOOT_CORE(CORE)          (((CORE) == RCC_BOOT_C1)  || \
                                         ((CORE) == RCC_BOOT_C2)  || \
                                         ((CORE) == (RCC_BOOT_C1 | RCC_BOOT_C2) ))

/**
  * @}
  */

/** @defgroup RCCEx_RCC_XBar RCC XBar Div
  * @{
  */
#define RCC_XBAR_DIV_POS1       1UL
#define RCC_XBAR_DIV_POS2       2UL
#define RCC_XBAR_DIV_POS4       4UL
#define RCC_XBAR_DIV_POS64      64UL
#define RCC_XBAR_DIV_POS128     128UL
#define RCC_XBAR_DIV_POS256     256UL
#define RCC_XBAR_DIV_POS1024    1024UL
#define RCC_XBAR_DIV_POS65536   65536UL

#define IS_RCC_XBARDIV(__DIV__) ((((__DIV__) >= RCC_XBAR_DIV_POS1)    && ((__DIV__) <=    RCC_XBAR_DIV_POS64)) || \
                                 (((__DIV__) >= RCC_XBAR_DIV_POS2)    && ((__DIV__) <=   RCC_XBAR_DIV_POS128)  && \
                                  (((__DIV__) %    RCC_XBAR_DIV_POS2) == 0UL)) || \
                                 (((__DIV__) >= RCC_XBAR_DIV_POS4)    && ((__DIV__) <=   RCC_XBAR_DIV_POS256)  && \
                                  (((__DIV__) %    RCC_XBAR_DIV_POS4) == 0UL)) || \
                                 (((__DIV__) >= RCC_XBAR_DIV_POS1024) && ((__DIV__) <= RCC_XBAR_DIV_POS65536) && \
                                  (((__DIV__) % RCC_XBAR_DIV_POS1024) == 0UL)))
#if defined(RCC_D3DCR_D3PERCKSEL)
#define IS_RCC_D3_SOURCE(SOURCE) (((SOURCE) == RCC_D3SOURCE_MSI) || ((SOURCE) == RCC_D3SOURCE_LSI) || \
                                  ((SOURCE) == RCC_D3SOURCE_LSE))
#endif /* RCC_D3DCR_D3PERCKSEL */
/**
  * @}
  */

#if defined(CORE_CA35)
/* CA35SS Clock Lock time outs */
#define PLL1_LOCK_TIMEOUT_VALUE    (2U)    /* 2 ms (minimum Tick + 1) but real lock time is less than one tick */
#define CHGCLK_TIMEOUT_VALUE       (2U)    /* 2 ms (minimum Tick + 1) but real lock time is less than one tick */

#define SSCG_ON                   0x1U
#define FRAC_ON                   0x1U
#define A35_SOURCE_PLL1           0x0U
#define A35_SOURCE_EXT            0x1U
#endif /* CORE_CA35 */

/** @defgroup RCC_PLL_State  RCC PLL State
  * @{
  */
#define RCC_PLL_OFF                  0x00000000U
#define RCC_PLL_ON                   0x00000001U

/**
  * @}
  */

/** @defgroup RCC_PLL_Mode  RCC PLL Mode
  * @{
  */
#define RCC_PLL_SPREAD_SPECTRUM 0x01U
/**
  * @}
  */

/** @defgroup RCC_PLL_Spread_Spectrum_Mode  RCC PLL Spread Spectrum mode
  * @{
  */
#define RCC_PLL_CENTERSPREAD    0x00U
#define RCC_PLL_DOWNSPREAD      0x01U
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source  RCC PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_HSI       0x00000000U
#define RCC_PLLSOURCE_HSE       0x00000001U
#define RCC_PLLSOURCE_MSI       0x00000002U
/**
  * @}
  */
#if defined(RCC_D3DCR_D3PERCKSEL)
/** @defgroup RCC_D3_Clock_Source  RCC D3 Clock Source
  * @{
  */
#define RCC_D3SOURCE_MSI       0x00000000U
#define RCC_D3SOURCE_LSI       RCC_D3DCR_D3PERCKSEL_0
#define RCC_D3SOURCE_LSE       RCC_D3DCR_D3PERCKSEL_1
/**
  * @}
  */
#endif /* RCC_D3DCR_D3PERCKSEL */
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Types RCCEx Exported Types
  * @{
  */

/**
  * @brief  RCC PLL configuration structure definition
  */
typedef struct
{
  uint32_t id;          /*!< The PLL id from 2 to 8       */
  uint32_t PLLSource;   /*!< The new source of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Clock_Source                */
  uint8_t  PLLState;    /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_State                       */
  uint8_t  PLLMode;     /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Mode                        */
  uint8_t  FREFDIV;
  uint16_t FBDIV;
  uint32_t FRACIN;
  uint32_t POSTDIV1;
  uint32_t POSTDIV2;
  uint32_t SSM_Mode;     /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Spread_Spectrum_Mode        */

  uint32_t SSM_SPREAD;
  uint32_t SSM_DIVVAL;
} RCC_PLLInitTypeDef;

#define RCC_PeriphCLKInitTypeDef        RCC_FlexgenTypeDef


/**
  * @brief Clock observer structure definition.
  */
typedef struct
{
  uint32_t      Enable;         /*!< To enable or disable the observer */
  uint32_t      RCC_MCOx;       /*!< To select the MCO instance */
  uint32_t      RCC_MCOSource;  /*!< To select the MCO source */
  uint32_t      RCC_MCODiv;     /*!< To select the MCO division factor */
  uint32_t      ObsDiv;         /*!< To select the observer division factor */
  uint32_t      ObsInv;         /*!< To select the observer inversion */
  uint32_t      ObsType;        /*!< To select oscillator or flexgen observation */
  uint32_t      ClockType;      /*!< To select the internal or external clock */
} RCC_ObserverTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCCEx_ConfigureClockObserver  RCCEx Configure Clock Observer
  * @{
  */
#define RCC_FLEXGEN0                    0U
#define RCC_FLEXGEN1                    1U
#define RCC_FLEXGEN2                    2U
#define RCC_FLEXGEN3                    3U
#define RCC_FLEXGEN4                    4U
#define RCC_FLEXGEN5                    5U
#define RCC_FLEXGEN6                    6U
#define RCC_HSICK                       0U
#define RCC_HSECK                       1U
#define RCC_MSICK                       2U
#if defined(RCC_PLL3CFGR1_PLLEN)
#define RCC_PLL4REF                     5U
#define RCC_PLL5REF                     6U
#define RCC_PLL6REF                     7U
#define RCC_PLL7REF                     8U
#define RCC_PLL8REF                     9U
#define RCC_PLL1REF                     10U
#define RCC_PLL2REF                     11U
#define RCC_PLL3REF                     12U
#else
#define RCC_PLL4REF                     6U
#define RCC_PLL5REF                     7U
#define RCC_PLL6REF                     8U
#define RCC_PLL7REF                     9U
#define RCC_PLL8REF                     10U
#define RCC_PLL1REF                     11U
#define RCC_PLL2REF                     12U
#endif /* RCC_PLL3CFGR1_PLLEN */
#define RCC_PLL4OUT                     64U
#define RCC_PLL5OUT                     65U
#define RCC_PLL6OUT                     66U
#define RCC_PLL7OUT                     67U
#define RCC_PLL8OUT                     68U
#define RCC_HSIKER                      128U
#define RCC_HSEKER                      129U
#define RCC_MSIKER                      130U
#define RCC_SPDIF                       131U
#define RCC_I2S                         132U
#define RCC_LSICK                       133U
#define RCC_LSECK                       134U
#define RCC_XBARFSM                     135U
#define RCC_ICN_P_RCC                   136U

#define RCC_PLL1DIV42                   0U
#define RCC_PLL2DIV4                    1U
#if defined(RCC_PLL3CFGR1_PLLEN)
#define RCC_PLL3DIV2                    2U
#endif /* RCC_PLL3CFGR1_PLLEN */
#define RCC_USB2PHY1                    3U
#define RCC_USB2PHY2                    4U
#define RCC_USB3PCIEPHY                 5U
#define RCC_LVDSPHY                     6U
#define RCC_DSIPHY                      7U

#define RCC_FLEXGEN_OBS         0x00000000U
#define RCC_OSC_OBS             0x00000001U
#define RCC_INTERNAL_OBS        0x00000001U
#define RCC_EXTERNAL_OBS        0x00000002U
#define RCC_CLOCKOBS_OFF        0x00000000U
#define RCC_CLOCKOBS_ON         0x00000001U
#define RCC_CLOCKOBS_NOT_INV    0x00000000U
#define RCC_CLOCKOBS_INV        0x00000001U

#define RCC_OBS_DIV1           0x00000000U
#define RCC_OBS_DIV2           0x00000001U
#define RCC_OBS_DIV4           0x00000002U
#define RCC_OBS_DIV8           0x00000003U
#define RCC_OBS_DIV16          0x00000004U
#define RCC_OBS_DIV32          0x00000005U
#define RCC_OBS_DIV64          0x00000006U
#define RCC_OBS_DIV128         0x00000007U
/**
  * @}
  */

/** @defgroup RCCEx_Periph_Clock_Selection  RCCEx Periph Clock Selection
  * @{
  */
#if defined(RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING)
#define RCC_PERIPHCLK_LPTIM1_2          7U
#define RCC_PERIPHCLK_UART2_4           8U
#define RCC_PERIPHCLK_UART3_5           9U
#define RCC_PERIPHCLK_SPI2              10U
#define RCC_PERIPHCLK_SPI3              11U
#define RCC_PERIPHCLK_SPDIFRX           12U
#define RCC_PERIPHCLK_I2C1_2            13U
#define RCC_PERIPHCLK_I3C1_2            14U
#define RCC_RESERVED0                   15U
#define RCC_PERIPHCLK_SPI1              16U
#define RCC_PERIPHCLK_SPI4_5            17U
#define RCC_PERIPHCLK_USART1            18U
#define RCC_PERIPHCLK_USART6            19U
#define RCC_PERIPHCLK_UART7             20U
#define RCC_PERIPHCLK_MDF1              21U
#define RCC_PERIPHCLK_SAI1              22U
#define RCC_PERIPHCLK_SAI2              23U
#define RCC_PERIPHCLK_SAI3              24U
#define RCC_PERIPHCLK_SAI4              25U
#define RCC_PERIPHCLK_FDCAN             26U
#define RCC_PERIPHCLK_LTDC              27U
#define RCC_RESERVED1                   28U
#define RCC_PERIPHCLK_DCMIPP            29U
#define RCC_PERIPHCLK_CSITXESC          30U
#define RCC_PERIPHCLK_CSIPHY            31U
#define RCC_RESERVED2                   32U
#define RCC_PERIPHCLK_STGEN             33U
#define RCC_RESERVED3                   34U
#define RCC_RESERVED4                   35U
#define RCC_PERIPHCLK_I3C3              36U
#define RCC_PERIPHCLK_SPI6              37U
#define RCC_PERIPHCLK_I2C3              38U
#define RCC_PERIPHCLK_LPUART1           39U
#define RCC_PERIPHCLK_LPTIM3            40U
#define RCC_PERIPHCLK_LPTIM4            41U
#define RCC_PERIPHCLK_LPTIM5            42U
#define RCC_PERIPHCLK_TSDBG             43U
#define RCC_PERIPHCLK_TPIU              44U
#define RCC_PERIPHCLK_ATB               45U
#define RCC_PERIPHCLK_ADC1              46U
#define RCC_PERIPHCLK_ADC2              47U
#define RCC_PERIPHCLK_OSPI1             48U
#define RCC_RESERVED5                   49U
#define RCC_PERIPHCLK_FMC               50U
#define RCC_PERIPHCLK_SDMMC1            51U
#define RCC_PERIPHCLK_SDMMC2            52U
#define RCC_PERIPHCLK_SDMMC3            53U
#define RCC_PERIPHCLK_ETH1              54U
#define RCC_PERIPHCLK_ETH2              55U
#define RCC_PERIPHCLK_ETH1PTP_ETH2PTP   56U
#define RCC_PERIPHCLK_USB2PHY1          57U
#define RCC_PERIPHCLK_USB2PHY2          58U
#define RCC_RESERVED6                   59U
#define RCC_RESERVED7                   60U
#define RCC_PERIPHCLK_MCO1              61U
#define RCC_PERIPHCLK_MCO2              62U
#define RCC_PERIPHCLK_CPU1_EXT2F        63U
#define RCC_PERIPHCLK_TIM1              64U
#define RCC_PERIPHCLK_TIM2              65U
#define RCC_PERIPHCLK_TIM3              66U
#define RCC_PERIPHCLK_TIM4              67U
#define RCC_PERIPHCLK_TIM5              68U
#define RCC_PERIPHCLK_TIM6              69U
#define RCC_PERIPHCLK_TIM7              70U
#define RCC_PERIPHCLK_TIM8              71U
#define RCC_PERIPHCLK_TIM10             72U
#define RCC_PERIPHCLK_TIM11             73U
#define RCC_PERIPHCLK_TIM12             74U
#define RCC_PERIPHCLK_TIM13             75U
#define RCC_PERIPHCLK_TIM14             76U
#define RCC_PERIPHCLK_TIM15             77U
#define RCC_PERIPHCLK_TIM16             78U
#define RCC_PERIPHCLK_TIM17             79U
#define RCC_RESERVED8                   80U
#elif defined(RCC_DERIVATIVE2_FLEXGEN_CHANNEL_MAPPING)
#define RCC_PERIPHCLK_LPTIM1_2          7U
#define RCC_PERIPHCLK_UART2_4           8U
#define RCC_PERIPHCLK_UART3_5           9U
#define RCC_PERIPHCLK_SPI2_3            10U
#define RCC_PERIPHCLK_SPDIFRX           11U
#define RCC_PERIPHCLK_I2C1_2            12U
#define RCC_PERIPHCLK_I3C1_2            12U
#define RCC_RESERVED0                   13U
#define RCC_RESERVED1                   13U
#define RCC_RESERVED2                   14U
#define RCC_PERIPHCLK_I2C7              15U
#define RCC_PERIPHCLK_SPI1              16U
#define RCC_PERIPHCLK_SPI4_5            17U
#define RCC_RESERVED3                   18U
#define RCC_PERIPHCLK_USART1            19U
#define RCC_PERIPHCLK_USART6            20U
#define RCC_PERIPHCLK_UART7             21U
#define RCC_RESERVED4                   22U
#define RCC_PERIPHCLK_SAI1_MDF1         23U
#define RCC_PERIPHCLK_SAI2              24U
#define RCC_PERIPHCLK_SAI3_4            25U
#define RCC_PERIPHCLK_FDCAN             26U
#define RCC_PERIPHCLK_LTDC              27U
#define RCC_PERIPHCLK_DSIPHY            28U
#define RCC_PERIPHCLK_DCMIPP            29U
#define RCC_PERIPHCLK_CSITXESC          30U
#define RCC_PERIPHCLK_CSIPHY            31U
#define RCC_PERIPHCLK_LVDSPHY           32U
#define RCC_PERIPHCLK_STGEN             33U
#define RCC_PERIPHCLK_USB3PCIEPHY       34U
#define RCC_PERIPHCLK_USBTC             35U
#define RCC_PERIPHCLK_I3C4              36U
#define RCC_PERIPHCLK_SPI8              37U
#define RCC_PERIPHCLK_I2C8              38U
#define RCC_PERIPHCLK_LPUART1           39U
#define RCC_PERIPHCLK_LPTIM3            40U
#define RCC_PERIPHCLK_LPTIM4_5          41U
#define RCC_RESERVED5                   42U
#define RCC_PERIPHCLK_TSDBG             43U
#define RCC_PERIPHCLK_TPIU              44U
#define RCC_PERIPHCLK_ATB               45U
#define RCC_PERIPHCLK_ADC12             46U
#define RCC_PERIPHCLK_ADC3              47U
#define RCC_PERIPHCLK_OSPI1             48U
#define RCC_PERIPHCLK_OSPI2             49U
#define RCC_PERIPHCLK_FMC               50U
#define RCC_PERIPHCLK_SDMMC1            51U
#define RCC_PERIPHCLK_SDMMC2            52U
#define RCC_PERIPHCLK_SDMMC3            53U
#define RCC_PERIPHCLK_ETH1_ETHSW        54U
#define RCC_PERIPHCLK_ETH2              55U
#define RCC_PERIPHCLK_ETH1PTP_ETH2PTP   56U
#define RCC_PERIPHCLK_USB2PHY1          57U
#define RCC_PERIPHCLK_USB2PHY2          58U
#define RCC_PERIPHCLK_ICN_M_GPU         59U
#define RCC_PERIPHCLK_ETHSWREF          60U
#define RCC_PERIPHCLK_MCO1              61U
#define RCC_PERIPHCLK_MCO2              62U
#define RCC_PERIPHCLK_CPU1_EXT2F        63U
#define RCC_PERIPHCLK_TIM1              64U
#define RCC_PERIPHCLK_TIM2              65U
#define RCC_PERIPHCLK_TIM3              66U
#define RCC_PERIPHCLK_TIM4              67U
#define RCC_PERIPHCLK_TIM5              68U
#define RCC_PERIPHCLK_TIM6              69U
#define RCC_PERIPHCLK_TIM7              70U
#define RCC_PERIPHCLK_TIM8              71U
#define RCC_PERIPHCLK_TIM10             72U
#define RCC_PERIPHCLK_TIM11             73U
#define RCC_PERIPHCLK_TIM12             74U
#define RCC_PERIPHCLK_TIM13             75U
#define RCC_PERIPHCLK_TIM14             76U
#define RCC_PERIPHCLK_TIM15             77U
#define RCC_PERIPHCLK_TIM16             78U
#define RCC_PERIPHCLK_TIM17             79U
#define RCC_RESERVED6                   80U
#else
#define RCC_PERIPHCLK_LPTIM1_2          7U
#define RCC_PERIPHCLK_UART2_4           8U
#define RCC_PERIPHCLK_UART3_5           9U
#define RCC_PERIPHCLK_SPI2_3            10U
#define RCC_PERIPHCLK_SPDIFRX           11U
#define RCC_PERIPHCLK_I2C1_2            12U
#define RCC_PERIPHCLK_I3C1_2            12U
#define RCC_PERIPHCLK_I2C3_5            13U
#define RCC_PERIPHCLK_I3C3              13U
#define RCC_PERIPHCLK_I2C4_6            14U
#define RCC_PERIPHCLK_I2C7              15U
#define RCC_PERIPHCLK_SPI1              16U
#define RCC_PERIPHCLK_SPI4_5            17U
#define RCC_PERIPHCLK_SPI6_7            18U
#define RCC_PERIPHCLK_USART1            19U
#define RCC_PERIPHCLK_USART6            20U
#define RCC_PERIPHCLK_UART7_8           21U
#define RCC_PERIPHCLK_UART9             22U
#define RCC_PERIPHCLK_SAI1_MDF1         23U
#define RCC_PERIPHCLK_SAI2              24U
#define RCC_PERIPHCLK_SAI3_4            25U
#define RCC_PERIPHCLK_FDCAN             26U
#define RCC_PERIPHCLK_LTDC              27U
#define RCC_PERIPHCLK_DSIPHY            28U
#define RCC_PERIPHCLK_DCMIPP            29U
#define RCC_PERIPHCLK_CSITXESC          30U
#define RCC_PERIPHCLK_CSIPHY            31U
#define RCC_PERIPHCLK_LVDSPHY           32U
#define RCC_PERIPHCLK_STGEN             33U
#define RCC_PERIPHCLK_USB3PCIEPHY       34U
#define RCC_PERIPHCLK_USBTC             35U
#define RCC_PERIPHCLK_I3C4              36U
#define RCC_PERIPHCLK_SPI8              37U
#define RCC_PERIPHCLK_I2C8              38U
#define RCC_PERIPHCLK_LPUART1           39U
#define RCC_PERIPHCLK_LPTIM3            40U
#define RCC_PERIPHCLK_LPTIM4_5          41U
#define RCC_PERIPHCLK_ADF1              42U
#define RCC_PERIPHCLK_TSDBG             43U
#define RCC_PERIPHCLK_TPIU              44U
#define RCC_PERIPHCLK_ATB               45U
#define RCC_PERIPHCLK_ADC12             46U
#define RCC_PERIPHCLK_ADC3              47U
#define RCC_PERIPHCLK_OSPI1             48U
#define RCC_PERIPHCLK_OSPI2             49U
#define RCC_PERIPHCLK_FMC               50U
#define RCC_PERIPHCLK_SDMMC1            51U
#define RCC_PERIPHCLK_SDMMC2            52U
#define RCC_PERIPHCLK_SDMMC3            53U
#define RCC_PERIPHCLK_ETH1_ETHSW        54U
#define RCC_PERIPHCLK_ETH2              55U
#define RCC_PERIPHCLK_ETH1PTP_ETH2PTP   56U
#define RCC_PERIPHCLK_USB2PHY1          57U
#define RCC_PERIPHCLK_USB2PHY2          58U
#define RCC_PERIPHCLK_ICN_M_GPU         59U
#define RCC_PERIPHCLK_ETHSWREF          60U
#define RCC_PERIPHCLK_MCO1              61U
#define RCC_PERIPHCLK_MCO2              62U
#define RCC_PERIPHCLK_CPU1_EXT2F        63U
#define RCC_PERIPHCLK_TIM1              64U
#define RCC_PERIPHCLK_TIM2              65U
#define RCC_PERIPHCLK_TIM3              66U
#define RCC_PERIPHCLK_TIM4              67U
#define RCC_PERIPHCLK_TIM5              68U
#define RCC_PERIPHCLK_TIM6              69U
#define RCC_PERIPHCLK_TIM7              70U
#define RCC_PERIPHCLK_TIM8              71U
#define RCC_PERIPHCLK_TIM10             72U
#define RCC_PERIPHCLK_TIM11             73U
#define RCC_PERIPHCLK_TIM12             74U
#define RCC_PERIPHCLK_TIM13             75U
#define RCC_PERIPHCLK_TIM14             76U
#define RCC_PERIPHCLK_TIM15             77U
#define RCC_PERIPHCLK_TIM16             78U
#define RCC_PERIPHCLK_TIM17             79U
#define RCC_PERIPHCLK_TIM20             80U
#endif /* RCC_DERIVATIVE1_FLEXGEN_CHANNEL_MAPPING */
/**
  * @}
  */

/** @defgroup RCCEx_FrequencyCalculator_ReferenceClockSelection  RCCEx FCALC Reference Clock Selection
  * @{
  */
#define RCC_FCALC_PLL4REFCLOCK       0U
#define RCC_FCALC_PLL5REFCLOCK       1U
#define RCC_FCALC_PLL6REFCLOCK       2U
#define RCC_FCALC_PLL7REFCLOCK       3U
#define RCC_FCALC_PLL8REFCLOCK       4U
/**
  * @}
  */

/** @defgroup RCCEx_FrequencyCalculator_ObservationClockSelection  RCCEx FCALC Observation Clock Selection
  * @{
  */
#define RCC_FCALC_INTOBSCLK_HSI_CK          0x000U
#define RCC_FCALC_INTOBSCLK_HSE_CK          0x001U
#define RCC_FCALC_INTOBSCLK_MSI_CK          0x002U

#if defined(RCC_PLL3CFGR1_PLLEN)
#define RCC_FCALC_INTOBSCLK_PLL4REF_CK      0x005U
#define RCC_FCALC_INTOBSCLK_PLL5REF_CK      0x006U
#define RCC_FCALC_INTOBSCLK_PLL6REF_CK      0x007U
#define RCC_FCALC_INTOBSCLK_PLL7REF_CK      0x008U
#define RCC_FCALC_INTOBSCLK_PLL8REF_CK      0x009U
#define RCC_FCALC_INTOBSCLK_PLL1REF_CK      0x00AU
#define RCC_FCALC_INTOBSCLK_PLL2REF_CK      0x00BU
#define RCC_FCALC_INTOBSCLK_PLL3REF_CK      0x00CU
#else
#define RCC_FCALC_INTOBSCLK_PLL4REF_CK      0x006U
#define RCC_FCALC_INTOBSCLK_PLL5REF_CK      0x007U
#define RCC_FCALC_INTOBSCLK_PLL6REF_CK      0x008U
#define RCC_FCALC_INTOBSCLK_PLL7REF_CK      0x009U
#define RCC_FCALC_INTOBSCLK_PLL8REF_CK      0x00AU
#define RCC_FCALC_INTOBSCLK_PLL1REF_CK      0x00BU
#define RCC_FCALC_INTOBSCLK_PLL2REF_CK      0x00CU
#endif /* RCC_PLL3CFGR1_PLLEN */

#define RCC_FCALC_INTOBSCLK_PLL4OUT_CK      0x040U
#define RCC_FCALC_INTOBSCLK_PLL5OUT_CK      0x041U
#define RCC_FCALC_INTOBSCLK_PLL6OUT_CK      0x042U
#define RCC_FCALC_INTOBSCLK_PLL7OUT_CK      0x043U
#define RCC_FCALC_INTOBSCLK_PLL8OUT_CK      0x044U

#define RCC_FCALC_INTOBSCLK_HSI_KER_CK      0x080U
#define RCC_FCALC_INTOBSCLK_HSE_KER_CK      0x081U
#define RCC_FCALC_INTOBSCLK_MSI_KER_CK      0x082U
#define RCC_FCALC_INTOBSCLK_SPDIF_SYMB_CK   0x083U
#define RCC_FCALC_INTOBSCLK_I2S_CK          0x084U
#define RCC_FCALC_INTOBSCLK_LSI_CK          0x085U
#define RCC_FCALC_INTOBSCLK_LSE_CK          0x086U
#define RCC_FCALC_INTOBSCLK_CK_XBAR_FSM     0x087U
#define RCC_FCALC_INTOBSCLK_CK_ICN_P_RCC    0x088U

#define RCC_FCALC_INTOBSCLK_FINDDIV0        0x0C0U
#define RCC_FCALC_INTOBSCLK_FINDDIV1        0x0C1U
#define RCC_FCALC_INTOBSCLK_FINDDIV2        0x0C2U
#define RCC_FCALC_INTOBSCLK_FINDDIV3        0x0C3U
#define RCC_FCALC_INTOBSCLK_FINDDIV4        0x0C4U
#define RCC_FCALC_INTOBSCLK_FINDDIV5        0x0C5U
#define RCC_FCALC_INTOBSCLK_FINDDIV6        0x0C6U
#define RCC_FCALC_INTOBSCLK_FINDDIV7        0x0C7U
#define RCC_FCALC_INTOBSCLK_FINDDIV8        0x0C8U
#define RCC_FCALC_INTOBSCLK_FINDDIV9        0x0C9U
#define RCC_FCALC_INTOBSCLK_FINDDIV10       0x0CAU
#define RCC_FCALC_INTOBSCLK_FINDDIV11       0x0CBU
#define RCC_FCALC_INTOBSCLK_FINDDIV12       0x0CCU
#define RCC_FCALC_INTOBSCLK_FINDDIV13       0x0CDU
#define RCC_FCALC_INTOBSCLK_FINDDIV14       0x0CEU
#define RCC_FCALC_INTOBSCLK_FINDDIV15       0x0CFU
#define RCC_FCALC_INTOBSCLK_FINDDIV16       0x0D0U
#define RCC_FCALC_INTOBSCLK_FINDDIV17       0x0D1U
#define RCC_FCALC_INTOBSCLK_FINDDIV18       0x0D2U
#define RCC_FCALC_INTOBSCLK_FINDDIV19       0x0D3U
#define RCC_FCALC_INTOBSCLK_FINDDIV20       0x0D4U
#define RCC_FCALC_INTOBSCLK_FINDDIV21       0x0D5U
#define RCC_FCALC_INTOBSCLK_FINDDIV22       0x0D6U
#define RCC_FCALC_INTOBSCLK_FINDDIV23       0x0D7U
#define RCC_FCALC_INTOBSCLK_FINDDIV24       0x0D8U
#define RCC_FCALC_INTOBSCLK_FINDDIV25       0x0D9U
#define RCC_FCALC_INTOBSCLK_FINDDIV26       0x0DAU
#define RCC_FCALC_INTOBSCLK_FINDDIV27       0x0DBU
#define RCC_FCALC_INTOBSCLK_FINDDIV28       0x0DCU
#define RCC_FCALC_INTOBSCLK_FINDDIV29       0x0DDU
#define RCC_FCALC_INTOBSCLK_FINDDIV30       0x0DEU
#define RCC_FCALC_INTOBSCLK_FINDDIV31       0x0DFU
#define RCC_FCALC_INTOBSCLK_FINDDIV32       0x0E0U
#define RCC_FCALC_INTOBSCLK_FINDDIV33       0x0E1U
#define RCC_FCALC_INTOBSCLK_FINDDIV34       0x0E2U
#define RCC_FCALC_INTOBSCLK_FINDDIV35       0x0E3U
#define RCC_FCALC_INTOBSCLK_FINDDIV36       0x0E4U
#define RCC_FCALC_INTOBSCLK_FINDDIV37       0x0E5U
#define RCC_FCALC_INTOBSCLK_FINDDIV38       0x0E6U
#define RCC_FCALC_INTOBSCLK_FINDDIV39       0x0E7U
#define RCC_FCALC_INTOBSCLK_FINDDIV40       0x0E8U
#define RCC_FCALC_INTOBSCLK_FINDDIV41       0x0E9U
#define RCC_FCALC_INTOBSCLK_FINDDIV42       0x0EAU
#define RCC_FCALC_INTOBSCLK_FINDDIV43       0x0EBU
#define RCC_FCALC_INTOBSCLK_FINDDIV44       0x0ECU
#define RCC_FCALC_INTOBSCLK_FINDDIV45       0x0EDU
#define RCC_FCALC_INTOBSCLK_FINDDIV46       0x0EEU
#define RCC_FCALC_INTOBSCLK_FINDDIV47       0x0EFU
#define RCC_FCALC_INTOBSCLK_FINDDIV48       0x0F0U
#define RCC_FCALC_INTOBSCLK_FINDDIV49       0x0F1U
#define RCC_FCALC_INTOBSCLK_FINDDIV50       0x0F2U
#define RCC_FCALC_INTOBSCLK_FINDDIV51       0x0F3U
#define RCC_FCALC_INTOBSCLK_FINDDIV52       0x0F4U
#define RCC_FCALC_INTOBSCLK_FINDDIV53       0x0F5U
#define RCC_FCALC_INTOBSCLK_FINDDIV54       0x0F6U
#define RCC_FCALC_INTOBSCLK_FINDDIV55       0x0F7U
#define RCC_FCALC_INTOBSCLK_FINDDIV56       0x0F8U
#define RCC_FCALC_INTOBSCLK_FINDDIV57       0x0F9U
#define RCC_FCALC_INTOBSCLK_FINDDIV58       0x0FAU
#define RCC_FCALC_INTOBSCLK_FINDDIV59       0x0FBU
#define RCC_FCALC_INTOBSCLK_FINDDIV60       0x0FCU
#define RCC_FCALC_INTOBSCLK_FINDDIV61       0x0FDU
#define RCC_FCALC_INTOBSCLK_FINDDIV62       0x0FEU
#define RCC_FCALC_INTOBSCLK_FINDDIV63       0x0FFU

#define RCC_FCALC_EXTOBSCLK_PLL1DIV42       0x100U
#define RCC_FCALC_EXTOBSCLK_PLL2DIV4        0x101U
#if defined(RCC_PLL3CFGR1_PLLEN)
#define RCC_FCALC_EXTOBSCLK_PLL3DIV2        0x102U
#endif /* RCC_PLL3CFGR1_PLLEN */
#define RCC_FCALC_EXTOBSCLK_USB2PHY1PLL     0x103U
#define RCC_FCALC_EXTOBSCLK_USB2PHY2PLL     0x104U
#define RCC_FCALC_EXTOBSCLK_USB3PCIEPHYPLL  0x105U
#define RCC_FCALC_EXTOBSCLK_LVDSPHYPLL      0x106U
#define RCC_FCALC_EXTOBSCLK_DSIPHYPLL       0x107U
/**
  * @}
  */
/**
  * @}
  */
/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
  * @{
  */
/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCCEx_Exported_Functions RCCEx Exported Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(const RCC_PeriphCLKInitTypeDef  *pPeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *pPeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);
uint32_t          HAL_RCCEx_GetTimerCLKFreq(uint32_t TimerId);

#if defined(CORE_CA35)
HAL_StatusTypeDef HAL_RCCEx_CA35SS_SetCA35SSClockSource(uint32_t source);
HAL_StatusTypeDef HAL_RCCEx_CA35SS_GetCA35SSClockSource(uint32_t *source);
#endif /* CORE_CA35 */

HAL_StatusTypeDef HAL_RCCEx_SetD3ClockSource(uint32_t source);
uint32_t HAL_RCCEx_GetD3ClockSource(void);

#if defined(CORE_CA35)
HAL_StatusTypeDef HAL_RCCEx_CA35SS_PLL1Config(const RCC_PLLInitTypeDef *pll_config);
#endif /* CORE_CA35 */
HAL_StatusTypeDef HAL_RCCEx_PLL2Config(RCC_PLLInitTypeDef *pll_config);
#if defined(RCC_PLL3CFGR1_PLLEN)
HAL_StatusTypeDef HAL_RCCEx_PLL3Config(RCC_PLLInitTypeDef *pll_config);
#endif /* RCC_PLL3CFGR1_PLLEN */
HAL_StatusTypeDef HAL_RCCEx_PLL4Config(RCC_PLLInitTypeDef *pll_config);
HAL_StatusTypeDef HAL_RCCEx_PLL5Config(RCC_PLLInitTypeDef *pll_config);
HAL_StatusTypeDef HAL_RCCEx_PLL6Config(RCC_PLLInitTypeDef *pll_config);
HAL_StatusTypeDef HAL_RCCEx_PLL7Config(RCC_PLLInitTypeDef *pll_config);
HAL_StatusTypeDef HAL_RCCEx_PLL8Config(RCC_PLLInitTypeDef *pll_config);

#if defined(CORE_CA35)
void              HAL_RCCEx_CA35SS_GetPLL1Config(RCC_PLLInitTypeDef *pll_config);
#endif /* CORE_CA35 */
void              HAL_RCCEx_GetPLL2Config(RCC_PLLInitTypeDef  *pll_config);
#if defined(RCC_PLL3CFGR1_PLLEN)
void              HAL_RCCEx_GetPLL3Config(RCC_PLLInitTypeDef  *pll_config);
#endif /* RCC_PLL3CFGR1_PLLEN */
void              HAL_RCCEx_GetPLL4Config(RCC_PLLInitTypeDef  *pll_config);
void              HAL_RCCEx_GetPLL5Config(RCC_PLLInitTypeDef  *pll_config);
void              HAL_RCCEx_GetPLL6Config(RCC_PLLInitTypeDef  *pll_config);
void              HAL_RCCEx_GetPLL7Config(RCC_PLLInitTypeDef  *pll_config);
void              HAL_RCCEx_GetPLL8Config(RCC_PLLInitTypeDef  *pll_config);

#if defined(CORE_CA35)
uint32_t          HAL_RCCEx_CA35SS_GetPLL1ClockFreq(void);
#endif /* CORE_CA35 */
uint32_t          HAL_RCCEx_GetPLL2ClockFreq(void);
#if defined(RCC_PLL3CFGR1_PLLEN)
uint32_t          HAL_RCCEx_GetPLL3ClockFreq(void);
#endif /* RCC_PLL3CFGR1_PLLEN */
uint32_t          HAL_RCCEx_GetPLL4ClockFreq(void);
uint32_t          HAL_RCCEx_GetPLL5ClockFreq(void);
uint32_t          HAL_RCCEx_GetPLL6ClockFreq(void);
uint32_t          HAL_RCCEx_GetPLL7ClockFreq(void);
uint32_t          HAL_RCCEx_GetPLL8ClockFreq(void);

int32_t HAL_RCCEx_MeasureClockFreq(uint32_t clk_id, uint32_t ref_id, uint32_t *freq);

#if defined(CORE_CA35)
void HAL_RCCEx_EnableBootCore(uint32_t RCC_BootCx);
void HAL_RCCEx_DisableBootCore(uint32_t RCC_BootCx);
void HAL_RCCEx_HoldBootMCU(void);
void HAL_RCCEx_BootMCU(void);
#endif /* CORE_CA35 */
/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_EnableLSECSS(void);
HAL_StatusTypeDef HAL_RCCEx_DisableLSECSS(void);
void              HAL_RCCEx_EnableHSECSS(void);
void              HAL_RCCEx_DisableHSECSS(void);
void              HAL_RCCEx_LSECSS_IRQHandler(void);
void              HAL_RCCEx_LSECSS_Callback(void);
void              HAL_RCCEx_ConfigureClockObserver(uint32_t PeriphClk, RCC_ObserverTypeDef *OBSConf);

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

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_HAL_RCC_EX_H */
