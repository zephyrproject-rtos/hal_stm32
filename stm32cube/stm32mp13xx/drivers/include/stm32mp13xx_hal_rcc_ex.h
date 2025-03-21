/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extension module.
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
#ifndef __STM32MP13xx_HAL_RCC_EX_H
#define __STM32MP13xx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal_def.h"

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Types RCCEx Exported Types
  * @{
  */
/**
  * @brief  RCC extended clocks structure definition
  */
typedef struct
{
  uint64_t PeriphClockSelection;   /*!< The Extended Clock to be configured.
                                        This parameter can be a value of @ref
                                        RCCEx_Periph_Clock_Selection */

  RCC_PLLInitTypeDef PLL2;         /*!< PLL2 structure parameters.
                                        This parameter will be used only when
                                        PLL2 is selected as Clock Source */

  RCC_PLLInitTypeDef PLL3;         /*!< PLL3 structure parameters.
                                        This parameter will be used only when
                                        PLL3 is selected as Clock Source */

  RCC_PLLInitTypeDef PLL4;         /*!< PLL4 structure parameters.
                                        This parameter will be used only when
                                        PLL3 is selected as Clock Source */

  uint32_t I2c12ClockSelection;    /*!< Specifies I2C12 clock source
                                        This parameter can be a value of
                                        @ref RCCEx_I2C12_Clock_Source */

  uint32_t I2c3ClockSelection;     /*!< Specifies I2C3 clock source
                                        This parameter can be a value of
                                        @ref RCCEx_I2C3_Clock_Source */

  uint32_t I2c4ClockSelection;     /*!< Specifies I2C4 clock source
                                        This parameter can be a value of
                                        @ref RCCEx_I2C4_Clock_Source */

  uint32_t I2c5ClockSelection;     /*!< Specifies I2C5 clock source
                                        This parameter can be a value of
                                        @ref RCCEx_I2C5_Clock_Source */

  uint32_t Spi1ClockSelection;     /*!< Specifies SPI1 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_SPI1_Clock_Source */

  uint32_t Spi23ClockSelection;    /*!< Specifies SPI23 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_SPI23_Clock_Source */

  uint32_t Spi4ClockSelection;     /*!< Specifies SPI4 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_SPI4_Clock_Source */

  uint32_t Spi5ClockSelection;     /*!< Specifies SPI5 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_SPI5_Clock_Source */

  uint32_t Usart1ClockSelection;   /*!< Specifies USART1 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_USART1_Clock_Source */

  uint32_t Usart2ClockSelection;   /*!< Specifies USART2 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_USART2_Clock_Source */

  uint32_t Uart35ClockSelection;   /*!< Specifies UART35 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_UART35_Clock_Source */

  uint32_t Uart4ClockSelection;    /*!< Specifies UART4 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_UART4_Clock_Source */

  uint32_t Usart6ClockSelection;   /*!< Specifies USART6 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_USART6_Clock_Source */

  uint32_t Uart78ClockSelection;   /*!< Specifies UART78 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_UART78_Clock_Source */

  uint32_t Lptim1ClockSelection;   /*!< Specifies LPTIM1 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_LPTIM1_Clock_Source */

  uint32_t Lptim2ClockSelection;   /*!< Specifies LPTIM2 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_LPTIM2_Clock_Source */

  uint32_t Lptim3ClockSelection;   /*!< Specifies LPTIM3 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_LPTIM3_Clock_Source */

  uint32_t Lptim45ClockSelection;  /*!< Specifies LPTIM45 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_LPTIM45_Clock_Source */

  uint32_t Sai1ClockSelection;     /*!< Specifies SAI1 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_SAI1_Clock_Source */

  uint32_t Sai2ClockSelection;     /*!< Specifies SAI2 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_SAI2_Clock_Source */

  uint32_t FdcanClockSelection;    /*!< Specifies FDCAN Clock clock source
                                        This parameter can be a value of @ref
                                        RCCEx_FDCAN_Clock_Source */

  uint32_t SpdifrxClockSelection;  /*!< Specifies SPDIFRX Clock clock source
                                        This parameter can be a value of @ref
                                        RCCEx_SPDIFRX_Clock_Source */

  uint32_t Adc1ClockSelection;     /*!< Specifies ADC1 interface clock source
                                        This parameter can be a value of @ref
                                        RCCEx_ADC1_Clock_Source */

  uint32_t Adc2ClockSelection;     /*!< Specifies ADC2 interface clock source
                                        This parameter can be a value of @ref
                                        RCCEx_ADC2_Clock_Source */

  uint32_t Sdmmc1ClockSelection;   /*!< Specifies SDMMC1 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_SDMMC1_Clock_Source */

  uint32_t Sdmmc2ClockSelection;   /*!< Specifies SDMMC2 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_SDMMC2_Clock_Source */

  uint32_t Eth1ClockSelection;     /*!< Specifies ETH1 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_ETH1_Clock_Source */

  uint32_t Eth2ClockSelection;     /*!< Specifies ETH1 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_ETH1_Clock_Source */

  uint32_t UsbphyClockSelection;   /*!< Specifies USB PHY clock source
                                        This parameter can be a value of @ref
                                        RCCEx_USBPHY_Clock_Source */

  uint32_t UsboClockSelection;     /*!< Specifies USB OTG clock source
                                        This parameter can be a value of @ref
                                        RCCEx_USBO_Clock_Source */

  uint32_t QspiClockSelection;     /*!< Specifies QSPI clock source
                                        This parameter can be a value of @ref
                                        RCCEx_QSPI_Clock_Source */

  uint32_t FmcClockSelection;      /*!< Specifies FMC clock source
                                        This parameter can be a value of @ref
                                        RCCEx_FMC_Clock_Source */

  uint32_t Rng1ClockSelection;     /*!< Specifies RNG1 clock source
                                        This parameter can be a value of @ref
                                        RCCEx_RNG1_Clock_Source */

  uint32_t StgenClockSelection;    /*!< Specifies STGEN clock source
                                        This parameter can be a value of @ref
                                        RCCEx_STGEN_Clock_Source */

  uint32_t DcmippClockSelection;   /*!< Specifies DCMIPP clock source
                                        This parameter can be a value of @ref
                                        RCCEx_DCMIPP_Clock_Source */

  uint32_t SaesClockSelection;     /*!< Specifies SAES clock source
                                        This parameter can be a value of @ref
                                        RCCEx_SAES_Clock_Source */

  uint32_t TIMG1PresSelection;     /*!< Specifies TIM Group 1 Clock Prescalers
                                        Selection.
                                        This parameter can be a value of @ref
                                        RCCEx_TIMG1_Prescaler_Selection */

  uint32_t TIMG2PresSelection;     /*!< Specifies TIM Group 2 Clock Prescalers
                                        Selection.
                                        This parameter can be a value of @ref
                                        RCCEx_TIMG2_Prescaler_Selection */

  uint32_t RTCClockSelection;      /*!< Specifies RTC clock source
                                        This parameter can be a value of @ref
                                        RCC_RTC_Clock_Source */

  uint32_t CkperClockSelection;    /*!< Specifies CKPER clock source
                                        This parameter can be a value of @ref
                                        RCCEx_CKPER_Clock_Source */

} RCC_PeriphCLKInitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCCEx_Periph_Clock_Selection RCCEx_Periph_Clock_Selection
  * @{
  */
#define RCC_PERIPHCLK_I2C12             ((uint64_t)0x00000001)
#define RCC_PERIPHCLK_I2C3              ((uint64_t)0x00000002U)
#define RCC_PERIPHCLK_I2C4              ((uint64_t)0x00000004U)
#define RCC_PERIPHCLK_I2C5              ((uint64_t)0x00000008U)
#define RCC_PERIPHCLK_SPI1              ((uint64_t)0x00000010U)
#define RCC_PERIPHCLK_SPI23             ((uint64_t)0x00000020U)
#define RCC_PERIPHCLK_SPI4              ((uint64_t)0x00000040U)
#define RCC_PERIPHCLK_SPI5              ((uint64_t)0x00000080U)
#define RCC_PERIPHCLK_USART1            ((uint64_t)0x00000100U)
#define RCC_PERIPHCLK_USART2            ((uint64_t)0x00000200U)
#define RCC_PERIPHCLK_UART35            ((uint64_t)0x00000400U)
#define RCC_PERIPHCLK_UART4             ((uint64_t)0x00000800U)
#define RCC_PERIPHCLK_USART6            ((uint64_t)0x00001000U)
#define RCC_PERIPHCLK_UART78            ((uint64_t)0x00002000U)
#define RCC_PERIPHCLK_LPTIM1            ((uint64_t)0x00004000U)
#define RCC_PERIPHCLK_LPTIM2            ((uint64_t)0x00008000U)
#define RCC_PERIPHCLK_LPTIM3            ((uint64_t)0x00010000U)
#define RCC_PERIPHCLK_LPTIM45           ((uint64_t)0x00020000U)
#define RCC_PERIPHCLK_SAI1              ((uint64_t)0x00040000U)
#define RCC_PERIPHCLK_SAI2              ((uint64_t)0x00080000U)
#define RCC_PERIPHCLK_FDCAN             ((uint64_t)0x00100000U)
#define RCC_PERIPHCLK_SPDIFRX           ((uint64_t)0x00200000U)
#define RCC_PERIPHCLK_ADC1              ((uint64_t)0x00400000U)
#define RCC_PERIPHCLK_ADC2              ((uint64_t)0x00800000U)
#define RCC_PERIPHCLK_SDMMC1            ((uint64_t)0x01000000U)
#define RCC_PERIPHCLK_SDMMC2            ((uint64_t)0x02000000U)
#define RCC_PERIPHCLK_ETH1              ((uint64_t)0x04000000U)
#define RCC_PERIPHCLK_ETH2              ((uint64_t)0x08000000U)
#define RCC_PERIPHCLK_USBPHY            ((uint64_t)0x10000000U)
#define RCC_PERIPHCLK_USBO              ((uint64_t)0x20080000U)
#define RCC_PERIPHCLK_QSPI              ((uint64_t)0x40000000U)
#define RCC_PERIPHCLK_FMC               ((uint64_t)0x80000000U)
#define RCC_PERIPHCLK_RNG1              ((uint64_t)0x100000000U)
#define RCC_PERIPHCLK_STGEN             ((uint64_t)0x200000000U)
#define RCC_PERIPHCLK_DCMIPP            ((uint64_t)0x400000000U)
#define RCC_PERIPHCLK_SAES              ((uint64_t)0x800000000U)
#define RCC_PERIPHCLK_TIMG1             ((uint64_t)0x1000000000U)
#define RCC_PERIPHCLK_TIMG2             ((uint64_t)0x2000000000U)
#define RCC_PERIPHCLK_RTC               ((uint64_t)0x4000000000U)
#define RCC_PERIPHCLK_CKPER             ((uint64_t)0x8000000000U)

#define IS_RCC_PERIPHCLOCK(SELECTION) \
  ((((SELECTION) & RCC_PERIPHCLK_I2C12)  == RCC_PERIPHCLK_I2C12)  || \
   (((SELECTION) & RCC_PERIPHCLK_I2C3)   == RCC_PERIPHCLK_I2C3)   || \
   (((SELECTION) & RCC_PERIPHCLK_I2C4)   == RCC_PERIPHCLK_I2C4)   || \
   (((SELECTION) & RCC_PERIPHCLK_I2C5)   == RCC_PERIPHCLK_I2C5)   || \
   (((SELECTION) & RCC_PERIPHCLK_SPI1)   == RCC_PERIPHCLK_SPI1)   || \
   (((SELECTION) & RCC_PERIPHCLK_SPI23)  == RCC_PERIPHCLK_SPI23)  || \
   (((SELECTION) & RCC_PERIPHCLK_SPI4)   == RCC_PERIPHCLK_SPI4)   || \
   (((SELECTION) & RCC_PERIPHCLK_SPI5)   == RCC_PERIPHCLK_SPI5)   || \
   (((SELECTION) & RCC_PERIPHCLK_USART1) == RCC_PERIPHCLK_USART1) || \
   (((SELECTION) & RCC_PERIPHCLK_USART2) == RCC_PERIPHCLK_USART2) || \
   (((SELECTION) & RCC_PERIPHCLK_UART35) == RCC_PERIPHCLK_UART35) || \
   (((SELECTION) & RCC_PERIPHCLK_UART4)  == RCC_PERIPHCLK_UART4)  || \
   (((SELECTION) & RCC_PERIPHCLK_USART6) == RCC_PERIPHCLK_USART6) || \
   (((SELECTION) & RCC_PERIPHCLK_UART78) == RCC_PERIPHCLK_UART78) || \
   (((SELECTION) & RCC_PERIPHCLK_LPTIM1) == RCC_PERIPHCLK_LPTIM1) || \
   (((SELECTION) & RCC_PERIPHCLK_LPTIM2) == RCC_PERIPHCLK_LPTIM2) || \
   (((SELECTION) & RCC_PERIPHCLK_LPTIM3) == RCC_PERIPHCLK_LPTIM3) || \
   (((SELECTION) & RCC_PERIPHCLK_LPTIM45)== RCC_PERIPHCLK_LPTIM45)|| \
   (((SELECTION) & RCC_PERIPHCLK_SAI1)   == RCC_PERIPHCLK_SAI1)   || \
   (((SELECTION) & RCC_PERIPHCLK_SAI2)   == RCC_PERIPHCLK_SAI2)   || \
   (((SELECTION) & RCC_PERIPHCLK_FDCAN)  == RCC_PERIPHCLK_FDCAN)  || \
   (((SELECTION) & RCC_PERIPHCLK_SPDIFRX)== RCC_PERIPHCLK_SPDIFRX)|| \
   (((SELECTION) & RCC_PERIPHCLK_ADC1)   == RCC_PERIPHCLK_ADC1)   || \
   (((SELECTION) & RCC_PERIPHCLK_ADC2)   == RCC_PERIPHCLK_ADC2)   || \
   (((SELECTION) & RCC_PERIPHCLK_SDMMC1) == RCC_PERIPHCLK_SDMMC1) || \
   (((SELECTION) & RCC_PERIPHCLK_SDMMC2) == RCC_PERIPHCLK_SDMMC2) || \
   (((SELECTION) & RCC_PERIPHCLK_ETH1)   == RCC_PERIPHCLK_ETH1)   || \
   (((SELECTION) & RCC_PERIPHCLK_ETH2)   == RCC_PERIPHCLK_ETH2)   || \
   (((SELECTION) & RCC_PERIPHCLK_USBPHY) == RCC_PERIPHCLK_USBPHY) || \
   (((SELECTION) & RCC_PERIPHCLK_USBO)   == RCC_PERIPHCLK_USBO)   || \
   (((SELECTION) & RCC_PERIPHCLK_QSPI)   == RCC_PERIPHCLK_QSPI)   || \
   (((SELECTION) & RCC_PERIPHCLK_FMC)    == RCC_PERIPHCLK_FMC)    || \
   (((SELECTION) & RCC_PERIPHCLK_RNG1)   == RCC_PERIPHCLK_RNG1)   || \
   (((SELECTION) & RCC_PERIPHCLK_STGEN)  == RCC_PERIPHCLK_STGEN)  || \
   (((SELECTION) & RCC_PERIPHCLK_DCMIPP) == RCC_PERIPHCLK_DCMIPP) || \
   (((SELECTION) & RCC_PERIPHCLK_SAES)   == RCC_PERIPHCLK_SAES)   || \
   (((SELECTION) & RCC_PERIPHCLK_TIMG1)  == RCC_PERIPHCLK_TIMG1)  || \
   (((SELECTION) & RCC_PERIPHCLK_TIMG2)  == RCC_PERIPHCLK_TIMG2)  || \
   (((SELECTION) & RCC_PERIPHCLK_RTC)    == RCC_PERIPHCLK_RTC)    || \
   (((SELECTION) & RCC_PERIPHCLK_CKPER)  == RCC_PERIPHCLK_CKPER))

/**
  * @}
  */

/** @defgroup RCCEx_Periph_One_Clock RCCEx_Periph_One_Clock
  * @{
  */
#define RCC_PERIPHCLK_LTDC              ((uint64_t)0x100000000000U)
#define RCC_PERIPHCLK_DFSDM1            ((uint64_t)0x200000000000U)
#define RCC_PERIPHCLK_DTS               ((uint64_t)0x400000000000U)
#define RCC_PERIPHCLK_IWDG1             ((uint64_t)0x800000000000U)
#define RCC_PERIPHCLK_DDRPHYC           ((uint64_t)0x1000000000000U)
#define RCC_PERIPHCLK_IWDG2             ((uint64_t)0x2000000000000U)
#define RCC_PERIPHCLK_TIM2              RCC_PERIPHCLK_TIMG1
#define RCC_PERIPHCLK_TIM3              RCC_PERIPHCLK_TIMG1
#define RCC_PERIPHCLK_TIM4              RCC_PERIPHCLK_TIMG1
#define RCC_PERIPHCLK_TIM5              RCC_PERIPHCLK_TIMG1
#define RCC_PERIPHCLK_TIM6              RCC_PERIPHCLK_TIMG1
#define RCC_PERIPHCLK_TIM7              RCC_PERIPHCLK_TIMG1
#define RCC_PERIPHCLK_TIM12             RCC_PERIPHCLK_TIMG1
#define RCC_PERIPHCLK_TIM13             RCC_PERIPHCLK_TIMG1
#define RCC_PERIPHCLK_TIM14             RCC_PERIPHCLK_TIMG1
#define RCC_PERIPHCLK_TIM1              RCC_PERIPHCLK_TIMG2
#define RCC_PERIPHCLK_TIM8              RCC_PERIPHCLK_TIMG2
#define RCC_PERIPHCLK_TIM15             RCC_PERIPHCLK_TIMG2
#define RCC_PERIPHCLK_TIM16             RCC_PERIPHCLK_TIMG2
#define RCC_PERIPHCLK_TIM17             RCC_PERIPHCLK_TIMG2

#define IS_RCC_PERIPHONECLOCK(PERIPH) \
  ((((PERIPH) & RCC_PERIPHCLK_LTDC)     == RCC_PERIPHCLK_LTDC)    || \
   (((PERIPH) & RCC_PERIPHCLK_DFSDM1)   == RCC_PERIPHCLK_DFSDM1)  || \
   (((PERIPH) & RCC_PERIPHCLK_DTS)      == RCC_PERIPHCLK_DTS)     || \
   (((PERIPH) & RCC_PERIPHCLK_IWDG1)    == RCC_PERIPHCLK_IWDG1)   || \
   (((PERIPH) & RCC_PERIPHCLK_IWDG2)    == RCC_PERIPHCLK_IWDG2)   || \
   (((PERIPH) & RCC_PERIPHCLK_DDRPHYC)  == RCC_PERIPHCLK_DDRPHYC) || \
   (((PERIPH) & RCC_PERIPHCLK_TIMG1)    == RCC_PERIPHCLK_TIMG1)   || \
   (((PERIPH) & RCC_PERIPHCLK_TIMG2)    == RCC_PERIPHCLK_TIMG2))

/**
  * @}
  */

/** @defgroup RCCEx_I2C12_Clock_Source  I2C12 Clock Source
  * @{
  */
#define RCC_I2C12CLKSOURCE_PCLK1        0U
#define RCC_I2C12CLKSOURCE_PLL4         RCC_I2C12CKSELR_I2C12SRC_0
#define RCC_I2C12CLKSOURCE_HSI          RCC_I2C12CKSELR_I2C12SRC_1
#define RCC_I2C12CLKSOURCE_CSI          (RCC_I2C12CKSELR_I2C12SRC_1 | RCC_I2C12CKSELR_I2C12SRC_0)

#define IS_RCC_I2C12CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_I2C12CLKSOURCE_PCLK1)  || \
   ((SOURCE) == RCC_I2C12CLKSOURCE_PLL4)   || \
   ((SOURCE) == RCC_I2C12CLKSOURCE_HSI)    || \
   ((SOURCE) == RCC_I2C12CLKSOURCE_CSI))
/**
  * @}
  */

/** @defgroup RCCEx_I2C3_Clock_Source I2C3 Clock Source
  * @{
  */
#define RCC_I2C3CLKSOURCE_PCLK6         0U
#define RCC_I2C3CLKSOURCE_PLL4          RCC_I2C345CKSELR_I2C3SRC_0
#define RCC_I2C3CLKSOURCE_HSI           RCC_I2C345CKSELR_I2C3SRC_1
#define RCC_I2C3CLKSOURCE_CSI           (RCC_I2C345CKSELR_I2C3SRC_1 | RCC_I2C345CKSELR_I2C3SRC_0)

#define IS_RCC_I2C3CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_I2C3CLKSOURCE_PCLK6)  || \
   ((SOURCE) == RCC_I2C3CLKSOURCE_PLL4)   || \
   ((SOURCE) == RCC_I2C3CLKSOURCE_HSI)    || \
   ((SOURCE) == RCC_I2C3CLKSOURCE_CSI))
/**
  * @}
  */

/** @defgroup RCCEx_I2C4_Clock_Source I2C4 Clock Source
  * @{
  */
#define RCC_I2C4CLKSOURCE_PCLK6         0U
#define RCC_I2C4CLKSOURCE_PLL4          RCC_I2C345CKSELR_I2C4SRC_0
#define RCC_I2C4CLKSOURCE_HSI           RCC_I2C345CKSELR_I2C4SRC_1
#define RCC_I2C4CLKSOURCE_CSI           (RCC_I2C345CKSELR_I2C4SRC_1 | RCC_I2C345CKSELR_I2C4SRC_0)

#define IS_RCC_I2C4CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_I2C4CLKSOURCE_PCLK6)  || \
   ((SOURCE) == RCC_I2C4CLKSOURCE_PLL4)   || \
   ((SOURCE) == RCC_I2C4CLKSOURCE_HSI)    || \
   ((SOURCE) == RCC_I2C4CLKSOURCE_CSI))
/**
  * @}
  */

/** @defgroup RCCEx_I2C5_Clock_Source I2C5 Clock Source
  * @{
  */
#define RCC_I2C5CLKSOURCE_PCLK6         0U
#define RCC_I2C5CLKSOURCE_PLL4          RCC_I2C345CKSELR_I2C5SRC_0
#define RCC_I2C5CLKSOURCE_HSI           RCC_I2C345CKSELR_I2C5SRC_1
#define RCC_I2C5CLKSOURCE_CSI           (RCC_I2C345CKSELR_I2C5SRC_1 | RCC_I2C345CKSELR_I2C5SRC_0)

#define IS_RCC_I2C5CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_I2C5CLKSOURCE_PCLK6)  || \
   ((SOURCE) == RCC_I2C5CLKSOURCE_PLL4)   || \
   ((SOURCE) == RCC_I2C5CLKSOURCE_HSI)    || \
   ((SOURCE) == RCC_I2C5CLKSOURCE_CSI))
/**
  * @}
  */

/** @defgroup RCCEx_SAI1_Clock_Source SAI1 Clock Source
  * @{
  */
#define RCC_SAI1CLKSOURCE_PLL4         0U
#define RCC_SAI1CLKSOURCE_PLL3_Q       RCC_SAI1CKSELR_SAI1SRC_0
#define RCC_SAI1CLKSOURCE_I2SCKIN      RCC_SAI1CKSELR_SAI1SRC_1
#define RCC_SAI1CLKSOURCE_PER          (RCC_SAI1CKSELR_SAI1SRC_1 | RCC_SAI1CKSELR_SAI1SRC_0)
#define RCC_SAI1CLKSOURCE_PLL3_R       RCC_SAI1CKSELR_SAI1SRC_2

#define IS_RCC_SAI1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL4)    || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL3_Q)   || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_I2SCKIN)  || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PER)      || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL3_R))
/**
  * @}
  */


/** @defgroup RCCEx_SAI2_Clock_Source SAI2 Clock Source
  * @{
  */
#define RCC_SAI2CLKSOURCE_PLL4          0U
#define RCC_SAI2CLKSOURCE_PLL3_Q        RCC_SAI2CKSELR_SAI2SRC_0
#define RCC_SAI2CLKSOURCE_I2SCKIN       RCC_SAI2CKSELR_SAI2SRC_1
#define RCC_SAI2CLKSOURCE_PER           (RCC_SAI2CKSELR_SAI2SRC_1 | RCC_SAI2CKSELR_SAI2SRC_0)
#define RCC_SAI2CLKSOURCE_SPDIF         RCC_SAI2CKSELR_SAI2SRC_2
#define RCC_SAI2CLKSOURCE_PLL3_R        (RCC_SAI2CKSELR_SAI2SRC_2 | RCC_SAI2CKSELR_SAI2SRC_0)


#define IS_RCC_SAI2CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SAI2CLKSOURCE_PLL4)    || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_PLL3_Q)  || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_I2SCKIN) || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_PER)     || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_SPDIF)   || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_PLL3_R))
/**
  * @}
  */


/** @defgroup RCCEx_SPI1_Clock_Source SPI/I2S1 Clock Source
  * @{
  */
#define RCC_SPI1CLKSOURCE_PLL4        0U
#define RCC_SPI1CLKSOURCE_PLL3_Q      RCC_SPI2S1CKSELR_SPI1SRC_0
#define RCC_SPI1CLKSOURCE_I2SCKIN     RCC_SPI2S1CKSELR_SPI1SRC_1
#define RCC_SPI1CLKSOURCE_PER         (RCC_SPI2S1CKSELR_SPI1SRC_1 | RCC_SPI2S1CKSELR_SPI1SRC_0)
#define RCC_SPI1CLKSOURCE_PLL3_R      RCC_SPI2S1CKSELR_SPI1SRC_2

#define IS_RCC_SPI1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI1CLKSOURCE_PLL4)    || \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_PLL3_Q)  || \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_I2SCKIN) || \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_PER)     || \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_PLL3_R))
/**
  * @}
  */

/** @defgroup RCCEx_SPI23_Clock_Source SPI/I2S2,3 Clock Source
  * @{
  */
#define RCC_SPI23CLKSOURCE_PLL4       0U
#define RCC_SPI23CLKSOURCE_PLL3_Q     RCC_SPI2S23CKSELR_SPI23SRC_0
#define RCC_SPI23CLKSOURCE_I2SCKIN    RCC_SPI2S23CKSELR_SPI23SRC_1
#define RCC_SPI23CLKSOURCE_PER        (RCC_SPI2S23CKSELR_SPI23SRC_1 | RCC_SPI2S23CKSELR_SPI23SRC_0)
#define RCC_SPI23CLKSOURCE_PLL3_R     RCC_SPI2S23CKSELR_SPI23SRC_2

#define IS_RCC_SPI23CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI23CLKSOURCE_PLL4)    || \
   ((__SOURCE__) == RCC_SPI23CLKSOURCE_PLL3_Q)  || \
   ((__SOURCE__) == RCC_SPI23CLKSOURCE_I2SCKIN) || \
   ((__SOURCE__) == RCC_SPI23CLKSOURCE_PER)     || \
   ((__SOURCE__) == RCC_SPI23CLKSOURCE_PLL3_R))
/**
  * @}
  */


/** @defgroup RCCEx_SPI4_Clock_Source SPI4 Clock Source
  * @{
  */
#define RCC_SPI4CLKSOURCE_PCLK6        0U
#define RCC_SPI4CLKSOURCE_PLL4         RCC_SPI45CKSELR_SPI4SRC_0
#define RCC_SPI4CLKSOURCE_HSI          RCC_SPI45CKSELR_SPI4SRC_1
#define RCC_SPI4CLKSOURCE_CSI          (RCC_SPI45CKSELR_SPI4SRC_1 | RCC_SPI45CKSELR_SPI4SRC_0)
#define RCC_SPI4CLKSOURCE_HSE          RCC_SPI45CKSELR_SPI4SRC_2
#define RCC_SPI4CLKSOURCE_I2SCKIN      (RCC_SPI45CKSELR_SPI4SRC_2 | RCC_SPI45CKSELR_SPI4SRC_0)

#define IS_RCC_SPI4CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI4CLKSOURCE_PCLK6) || \
   ((__SOURCE__) == RCC_SPI4CLKSOURCE_PLL4)  || \
   ((__SOURCE__) == RCC_SPI4CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_SPI4CLKSOURCE_CSI)   || \
   ((__SOURCE__) == RCC_SPI4CLKSOURCE_HSE)   || \
   ((__SOURCE__) == RCC_SPI4CLKSOURCE_I2SCKIN))
/**
  * @}
  */

/** @defgroup RCCEx_SPI5_Clock_Source SPI5 Clock Source
  * @{
  */
#define RCC_SPI5CLKSOURCE_PCLK6        0U
#define RCC_SPI5CLKSOURCE_PLL4         RCC_SPI45CKSELR_SPI5SRC_0
#define RCC_SPI5CLKSOURCE_HSI          RCC_SPI45CKSELR_SPI5SRC_1
#define RCC_SPI5CLKSOURCE_CSI          (RCC_SPI45CKSELR_SPI5SRC_1 | RCC_SPI45CKSELR_SPI5SRC_0)
#define RCC_SPI5CLKSOURCE_HSE          RCC_SPI45CKSELR_SPI5SRC_2

#define IS_RCC_SPI5CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI5CLKSOURCE_PCLK6) || \
   ((__SOURCE__) == RCC_SPI5CLKSOURCE_PLL4)  || \
   ((__SOURCE__) == RCC_SPI5CLKSOURCE_HSI)   || \
   ((__SOURCE__) == RCC_SPI5CLKSOURCE_CSI)   || \
   ((__SOURCE__) == RCC_SPI5CLKSOURCE_HSE))
/**
  * @}
  */

/** @defgroup RCCEx_USART1_Clock_Source USART1 Clock Source
  * @{
  */
#define RCC_USART1CLKSOURCE_PCLK6       0U
#define RCC_USART1CLKSOURCE_PLL3        RCC_UART12CKSELR_UART1SRC_0
#define RCC_USART1CLKSOURCE_HSI         RCC_UART12CKSELR_UART1SRC_1
#define RCC_USART1CLKSOURCE_CSI         (RCC_UART12CKSELR_UART1SRC_1 | RCC_UART12CKSELR_UART1SRC_0)
#define RCC_USART1CLKSOURCE_PLL4        RCC_UART12CKSELR_UART1SRC_2
#define RCC_USART1CLKSOURCE_HSE         (RCC_UART12CKSELR_UART1SRC_2 | RCC_UART12CKSELR_UART1SRC_0)


#define IS_RCC_USART1CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_USART1CLKSOURCE_PCLK6) || \
   ((SOURCE) == RCC_USART1CLKSOURCE_PLL3)  || \
   ((SOURCE) == RCC_USART1CLKSOURCE_HSI)   || \
   ((SOURCE) == RCC_USART1CLKSOURCE_CSI)   || \
   ((SOURCE) == RCC_USART1CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_USART1CLKSOURCE_HSE))

/**
  * @}
  */

/** @defgroup RCCEx_USART2_Clock_Source USART2 Clock Source
  * @{
  */
#define RCC_USART2CLKSOURCE_PCLK6       0U
#define RCC_USART2CLKSOURCE_PLL3        RCC_UART12CKSELR_UART2SRC_0
#define RCC_USART2CLKSOURCE_HSI         RCC_UART12CKSELR_UART2SRC_1
#define RCC_USART2CLKSOURCE_CSI         (RCC_UART12CKSELR_UART2SRC_1 | RCC_UART12CKSELR_UART2SRC_0)
#define RCC_USART2CLKSOURCE_PLL4        RCC_UART12CKSELR_UART2SRC_2
#define RCC_USART2CLKSOURCE_HSE         (RCC_UART12CKSELR_UART2SRC_2 | RCC_UART12CKSELR_UART2SRC_0)


#define IS_RCC_USART2CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_USART2CLKSOURCE_PCLK6) || \
   ((SOURCE) == RCC_USART2CLKSOURCE_PLL3)  || \
   ((SOURCE) == RCC_USART2CLKSOURCE_HSI)   || \
   ((SOURCE) == RCC_USART2CLKSOURCE_CSI)   || \
   ((SOURCE) == RCC_USART2CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_USART2CLKSOURCE_HSE))
/**
  * @}
  */

/** @defgroup RCCEx_UART4_Clock_Source UART4 Clock Source
  * @{
  */
#define RCC_UART4CLKSOURCE_PCLK1       0U
#define RCC_UART4CLKSOURCE_PLL4        RCC_UART4CKSELR_UART4SRC_0
#define RCC_UART4CLKSOURCE_HSI         RCC_UART4CKSELR_UART4SRC_1
#define RCC_UART4CLKSOURCE_CSI         (RCC_UART4CKSELR_UART4SRC_1 | RCC_UART4CKSELR_UART4SRC_0)
#define RCC_UART4CLKSOURCE_HSE         RCC_UART4CKSELR_UART4SRC_2


#define IS_RCC_UART4CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_UART4CLKSOURCE_PCLK1) || \
   ((SOURCE) == RCC_UART4CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_UART4CLKSOURCE_HSI)   || \
   ((SOURCE) == RCC_UART4CLKSOURCE_CSI)   || \
   ((SOURCE) == RCC_UART4CLKSOURCE_HSE))
/**
  * @}
  */

/** @defgroup RCCEx_UART35_Clock_Source UART35 Clock Source
  * @{
  */
#define RCC_UART35CLKSOURCE_PCLK1        0U
#define RCC_UART35CLKSOURCE_PLL4         RCC_UART35CKSELR_UART35SRC_0
#define RCC_UART35CLKSOURCE_HSI          RCC_UART35CKSELR_UART35SRC_1
#define RCC_UART35CLKSOURCE_CSI          (RCC_UART35CKSELR_UART35SRC_1 | RCC_UART35CKSELR_UART35SRC_0)
#define RCC_UART35CLKSOURCE_HSE          RCC_UART35CKSELR_UART35SRC_2

#define IS_RCC_UART35CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_UART35CLKSOURCE_PCLK1) || \
   ((SOURCE) == RCC_UART35CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_UART35CLKSOURCE_HSI)   || \
   ((SOURCE) == RCC_UART35CLKSOURCE_CSI)   || \
   ((SOURCE) == RCC_UART35CLKSOURCE_HSE))
/**
  * @}
  */

/** @defgroup RCCEx_USART6_Clock_Source USART6 Clock Source
  * @{
  */
#define RCC_USART6CLKSOURCE_PCLK2       0U
#define RCC_USART6CLKSOURCE_PLL4        RCC_UART6CKSELR_UART6SRC_0
#define RCC_USART6CLKSOURCE_HSI         RCC_UART6CKSELR_UART6SRC_1
#define RCC_USART6CLKSOURCE_CSI         (RCC_UART6CKSELR_UART6SRC_1 | RCC_UART6CKSELR_UART6SRC_0)
#define RCC_USART6CLKSOURCE_HSE         RCC_UART6CKSELR_UART6SRC_2

#define IS_RCC_USART6CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_USART6CLKSOURCE_PCLK2) || \
   ((SOURCE) == RCC_USART6CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_USART6CLKSOURCE_HSI)   || \
   ((SOURCE) == RCC_USART6CLKSOURCE_CSI)   || \
   ((SOURCE) == RCC_USART6CLKSOURCE_HSE))
/**
  * @}
  */

/** @defgroup RCCEx_UART78_Clock_Source UART78 Clock Source
  * @{
  */
#define RCC_UART78CLKSOURCE_PCLK1        0U
#define RCC_UART78CLKSOURCE_PLL4         RCC_UART78CKSELR_UART78SRC_0
#define RCC_UART78CLKSOURCE_HSI          RCC_UART78CKSELR_UART78SRC_1
#define RCC_UART78CLKSOURCE_CSI          (RCC_UART78CKSELR_UART78SRC_1 | RCC_UART78CKSELR_UART78SRC_0)
#define RCC_UART78CLKSOURCE_HSE          RCC_UART78CKSELR_UART78SRC_2

#define IS_RCC_UART78CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_UART78CLKSOURCE_PCLK1) || \
   ((SOURCE) == RCC_UART78CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_UART78CLKSOURCE_HSI)   || \
   ((SOURCE) == RCC_UART78CLKSOURCE_CSI)   || \
   ((SOURCE) == RCC_UART78CLKSOURCE_HSE))
/**
  * @}
  */

/** @defgroup RCCEx_SDMMC1_Clock_Source SDMMC1 Clock Source
  * @{
  */
#define RCC_SDMMC1CLKSOURCE_HCLK6       0U
#define RCC_SDMMC1CLKSOURCE_PLL3        RCC_SDMMC12CKSELR_SDMMC1SRC_0
#define RCC_SDMMC1CLKSOURCE_PLL4        RCC_SDMMC12CKSELR_SDMMC1SRC_1
#define RCC_SDMMC1CLKSOURCE_HSI         (RCC_SDMMC12CKSELR_SDMMC1SRC_1 | RCC_SDMMC12CKSELR_SDMMC1SRC_0)

#define IS_RCC_SDMMC1CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_SDMMC1CLKSOURCE_HCLK6) || \
   ((SOURCE) == RCC_SDMMC1CLKSOURCE_PLL3)  || \
   ((SOURCE) == RCC_SDMMC1CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_SDMMC1CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCCEx_SDMMC2_Clock_Source SDMMC2 Clock Source
  * @{
  */
#define RCC_SDMMC2CLKSOURCE_HCLK6       0U
#define RCC_SDMMC2CLKSOURCE_PLL3        RCC_SDMMC12CKSELR_SDMMC2SRC_0
#define RCC_SDMMC2CLKSOURCE_PLL4        RCC_SDMMC12CKSELR_SDMMC2SRC_1
#define RCC_SDMMC2CLKSOURCE_HSI         (RCC_SDMMC12CKSELR_SDMMC2SRC_1 | RCC_SDMMC12CKSELR_SDMMC2SRC_0)

#define IS_RCC_SDMMC2CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_SDMMC2CLKSOURCE_HCLK6) || \
   ((SOURCE) == RCC_SDMMC2CLKSOURCE_PLL3)  || \
   ((SOURCE) == RCC_SDMMC2CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_SDMMC2CLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCCEx_ETH1_Clock_Source ETH1 Clock Source
  * @{
  */
#define RCC_ETH1CLKSOURCE_PLL4       0U
#define RCC_ETH1CLKSOURCE_PLL3       RCC_ETH12CKSELR_ETH1SRC_0
#define RCC_ETH1CLKSOURCE_OFF        RCC_ETH12CKSELR_ETH1SRC_1


#define IS_RCC_ETH1CLKSOURCE(SOURCE) (((SOURCE) == RCC_ETH1CLKSOURCE_PLL4)  || \
                                      ((SOURCE) == RCC_ETH1CLKSOURCE_PLL3)  || \
                                      ((SOURCE) == RCC_ETH1CLKSOURCE_OFF))
/**
  * @}
  */

/** @defgroup RCCEx_ETH2_Clock_Source ETH2 Clock Source
  * @{
  */
#define RCC_ETH2CLKSOURCE_PLL4       0U
#define RCC_ETH2CLKSOURCE_PLL3       RCC_ETH12CKSELR_ETH2SRC_0
#define RCC_ETH2CLKSOURCE_OFF        RCC_ETH12CKSELR_ETH2SRC_1


#define IS_RCC_ETH2CLKSOURCE(SOURCE) (((SOURCE) == RCC_ETH2CLKSOURCE_PLL4)  || \
                                      ((SOURCE) == RCC_ETH2CLKSOURCE_PLL3)  || \
                                      ((SOURCE) == RCC_ETH2CLKSOURCE_OFF))
/**
  * @}
  */

/** @defgroup RCCEx_ETH1_PrecisionTimeProtocol_Divider ETH1 PrecisionTimeProtocol Divider
  * @{
  */
#define RCC_ETH1PTPDIV_1   0U                                                 /*Bypass (default after reset*/
#define RCC_ETH1PTPDIV_2   RCC_ETH12CKSELR_ETH1PTPDIV_0                                     /*Division by 2*/
#define RCC_ETH1PTPDIV_3   RCC_ETH12CKSELR_ETH1PTPDIV_1                                     /*Division by 3*/
#define RCC_ETH1PTPDIV_4   (RCC_ETH12CKSELR_ETH1PTPDIV_1 | RCC_ETH12CKSELR_ETH1PTPDIV_0)    /*Division by 4*/
#define RCC_ETH1PTPDIV_5   RCC_ETH12CKSELR_ETH1PTPDIV_2                                     /*Division by 5*/
#define RCC_ETH1PTPDIV_6   (RCC_ETH12CKSELR_ETH1PTPDIV_2 | RCC_ETH12CKSELR_ETH1PTPDIV_0)    /*Division by 6*/
#define RCC_ETH1PTPDIV_7   (RCC_ETH12CKSELR_ETH1PTPDIV_2 | RCC_ETH12CKSELR_ETH1PTPDIV_1)    /*Division by 7*/
#define RCC_ETH1PTPDIV_8   (RCC_ETH12CKSELR_ETH1PTPDIV_2 | RCC_ETH12CKSELR_ETH1PTPDIV_1 | \
                            RCC_ETH12CKSELR_ETH1PTPDIV_0)  /*Division by 8*/
#define RCC_ETH1PTPDIV_9   RCC_ETH12CKSELR_ETH1PTPDIV_3                                     /*Division by 9*/
#define RCC_ETH1PTPDIV_10  (RCC_ETH12CKSELR_ETH1PTPDIV_3 | RCC_ETH12CKSELR_ETH1PTPDIV_0)    /*Division by 10*/
#define RCC_ETH1PTPDIV_11  (RCC_ETH12CKSELR_ETH1PTPDIV_3 | RCC_ETH12CKSELR_ETH1PTPDIV_1)    /*Division by 11*/
#define RCC_ETH1PTPDIV_12  (RCC_ETH12CKSELR_ETH1PTPDIV_3 | RCC_ETH12CKSELR_ETH1PTPDIV_1 | \
                            RCC_ETH12CKSELR_ETH1PTPDIV_0)  /*Division by 12*/
#define RCC_ETH1PTPDIV_13  (RCC_ETH12CKSELR_ETH1PTPDIV_3 | RCC_ETH12CKSELR_ETH1PTPDIV_2)    /*Division by 13*/
#define RCC_ETH1PTPDIV_14  (RCC_ETH12CKSELR_ETH1PTPDIV_3 | RCC_ETH12CKSELR_ETH1PTPDIV_2 | \
                            RCC_ETH12CKSELR_ETH1PTPDIV_0)  /*Division by 14*/
#define RCC_ETH1PTPDIV_15  (RCC_ETH12CKSELR_ETH1PTPDIV_3 | RCC_ETH12CKSELR_ETH1PTPDIV_2 | \
                            RCC_ETH12CKSELR_ETH1PTPDIV_1)  /*Division by 15*/
#define RCC_ETH1PTPDIV_16  (RCC_ETH12CKSELR_ETH1PTPDIV_3 | RCC_ETH12CKSELR_ETH1PTPDIV_2 | \
                            RCC_ETH12CKSELR_ETH1PTPDIV_1 | RCC_ETH12CKSELR_ETH1PTPDIV_0)  /*Division by 16*/


#define IS_RCC_ETH1PTPDIV(SOURCE)       (((SOURCE) == RCC_ETH1PTPDIV_1)  || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_2)  || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_3)  || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_4)  || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_5)  || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_6)  || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_7)  || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_8)  || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_9)  || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_10) || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_11) || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_12) || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_13) || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_14) || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_15) || \
                                         ((SOURCE) == RCC_ETH1PTPDIV_16))
/**
  * @}
  */

/** @defgroup RCCEx_ETH2_PrecisionTimeProtocol_Divider ETH2 PrecisionTimeProtocol Divider
  * @{
  */
#define RCC_ETH2PTPDIV_1   0U                                                 /*Bypass (default after reset*/
#define RCC_ETH2PTPDIV_2   RCC_ETH12CKSELR_ETH2PTPDIV_0                                     /*Division by 2*/
#define RCC_ETH2PTPDIV_3   RCC_ETH12CKSELR_ETH2PTPDIV_1                                     /*Division by 3*/
#define RCC_ETH2PTPDIV_4   (RCC_ETH12CKSELR_ETH2PTPDIV_1 | RCC_ETH12CKSELR_ETH2PTPDIV_0)    /*Division by 4*/
#define RCC_ETH2PTPDIV_5   RCC_ETH12CKSELR_ETH2PTPDIV_2                                     /*Division by 5*/
#define RCC_ETH2PTPDIV_6   (RCC_ETH12CKSELR_ETH2PTPDIV_2 | RCC_ETH12CKSELR_ETH2PTPDIV_0)    /*Division by 6*/
#define RCC_ETH2PTPDIV_7   (RCC_ETH12CKSELR_ETH2PTPDIV_2 | RCC_ETH12CKSELR_ETH2PTPDIV_1)    /*Division by 7*/
#define RCC_ETH2PTPDIV_8   (RCC_ETH12CKSELR_ETH2PTPDIV_2 | RCC_ETH12CKSELR_ETH2PTPDIV_1 | \
                            RCC_ETH12CKSELR_ETH2PTPDIV_0)  /*Division by 8*/
#define RCC_ETH2PTPDIV_9   RCC_ETH12CKSELR_ETH2PTPDIV_3                                     /*Division by 9*/
#define RCC_ETH2PTPDIV_10  (RCC_ETH12CKSELR_ETH2PTPDIV_3 | RCC_ETH12CKSELR_ETH2PTPDIV_0)    /*Division by 10*/
#define RCC_ETH2PTPDIV_11  (RCC_ETH12CKSELR_ETH2PTPDIV_3 | RCC_ETH12CKSELR_ETH2PTPDIV_1)    /*Division by 11*/
#define RCC_ETH2PTPDIV_12  (RCC_ETH12CKSELR_ETH2PTPDIV_3 | RCC_ETH12CKSELR_ETH2PTPDIV_1 | \
                            RCC_ETH12CKSELR_ETH2PTPDIV_0)  /*Division by 12*/
#define RCC_ETH2PTPDIV_13  (RCC_ETH12CKSELR_ETH2PTPDIV_3 | RCC_ETH12CKSELR_ETH2PTPDIV_2)    /*Division by 13*/
#define RCC_ETH2PTPDIV_14  (RCC_ETH12CKSELR_ETH2PTPDIV_3 | RCC_ETH12CKSELR_ETH2PTPDIV_2 | \
                            RCC_ETH12CKSELR_ETH2PTPDIV_0)  /*Division by 14*/
#define RCC_ETH2PTPDIV_15  (RCC_ETH12CKSELR_ETH2PTPDIV_3 | RCC_ETH12CKSELR_ETH2PTPDIV_2 | \
                            RCC_ETH12CKSELR_ETH2PTPDIV_1)  /*Division by 15*/
#define RCC_ETH2PTPDIV_16  (RCC_ETH12CKSELR_ETH2PTPDIV_3 | RCC_ETH12CKSELR_ETH2PTPDIV_2 | \
                            RCC_ETH12CKSELR_ETH2PTPDIV_1 | RCC_ETH12CKSELR_ETH2PTPDIV_0)  /*Division by 16*/


#define IS_RCC_ETH2PTPDIV(SOURCE)       (((SOURCE) == RCC_ETH2PTPDIV_1)  || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_2)  || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_3)  || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_4)  || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_5)  || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_6)  || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_7)  || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_8)  || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_9)  || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_10) || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_11) || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_12) || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_13) || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_14) || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_15) || \
                                         ((SOURCE) == RCC_ETH2PTPDIV_16))
/**
  * @}
  */


/** @defgroup RCCEx_QSPI_Clock_Source QSPI Clock Source
  * @{
  */
#define RCC_QSPICLKSOURCE_ACLK  0U
#define RCC_QSPICLKSOURCE_PLL3  RCC_QSPICKSELR_QSPISRC_0
#define RCC_QSPICLKSOURCE_PLL4  RCC_QSPICKSELR_QSPISRC_1
#define RCC_QSPICLKSOURCE_PER   (RCC_QSPICKSELR_QSPISRC_1 | RCC_QSPICKSELR_QSPISRC_0)

#define IS_RCC_QSPICLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_QSPICLKSOURCE_ACLK) || \
   ((SOURCE) == RCC_QSPICLKSOURCE_PLL3) || \
   ((SOURCE) == RCC_QSPICLKSOURCE_PLL4) || \
   ((SOURCE) == RCC_QSPICLKSOURCE_PER))
/**
  * @}
  */

/** @defgroup RCCEx_FMC_Clock_Source FMC Clock Source
  * @{
  */
#define RCC_FMCCLKSOURCE_ACLK       0U
#define RCC_FMCCLKSOURCE_PLL3       RCC_FMCCKSELR_FMCSRC_0
#define RCC_FMCCLKSOURCE_PLL4       RCC_FMCCKSELR_FMCSRC_1
#define RCC_FMCCLKSOURCE_PER        (RCC_FMCCKSELR_FMCSRC_1 | RCC_FMCCKSELR_FMCSRC_0)

#define IS_RCC_FMCCLKSOURCE(SOURCE) (((SOURCE) == RCC_FMCCLKSOURCE_ACLK)  || \
                                     ((SOURCE) == RCC_FMCCLKSOURCE_PLL3)  || \
                                     ((SOURCE) == RCC_FMCCLKSOURCE_PLL4)  || \
                                     ((SOURCE) == RCC_FMCCLKSOURCE_PER))
/**
  * @}
  */

#if defined(RCC_PERIPHCLK_FDCAN)
/** @defgroup RCCEx_FDCAN_Clock_Source FDCAN Clock Source
  * @{
  */
#define RCC_FDCANCLKSOURCE_HSE          0U
#define RCC_FDCANCLKSOURCE_PLL3         RCC_FDCANCKSELR_FDCANSRC_0
#define RCC_FDCANCLKSOURCE_PLL4_Q       RCC_FDCANCKSELR_FDCANSRC_1
#define RCC_FDCANCLKSOURCE_PLL4_R       (RCC_FDCANCKSELR_FDCANSRC_1 | RCC_FDCANCKSELR_FDCANSRC_0)



#define IS_RCC_FDCANCLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_FDCANCLKSOURCE_HSE)     || \
   ((SOURCE) == RCC_FDCANCLKSOURCE_PLL3)    || \
   ((SOURCE) == RCC_FDCANCLKSOURCE_PLL4_Q)  || \
   ((SOURCE) == RCC_FDCANCLKSOURCE_PLL4_R))
/**
  * @}
  */
#endif /* RCC_PERIPHCLK_FDCAN */

/** @defgroup RCCEx_SPDIFRX_Clock_Source SPDIFRX Clock Source
  * @{
  */
#define RCC_SPDIFRXCLKSOURCE_PLL4         0U
#define RCC_SPDIFRXCLKSOURCE_PLL3         RCC_SPDIFCKSELR_SPDIFSRC_0
#define RCC_SPDIFRXCLKSOURCE_HSI          RCC_SPDIFCKSELR_SPDIFSRC_1

#define IS_RCC_SPDIFRXCLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_SPDIFRXCLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_SPDIFRXCLKSOURCE_PLL3)  || \
   ((SOURCE) == RCC_SPDIFRXCLKSOURCE_HSI))
/**
  * @}
  */

/** @defgroup RCCEx_USBPHY_Clock_Source USBPHY Clock Source
  * @{
  */
#define RCC_USBPHYCLKSOURCE_HSE         0U
#define RCC_USBPHYCLKSOURCE_PLL4        RCC_USBCKSELR_USBPHYSRC_0
#define RCC_USBPHYCLKSOURCE_HSE2        RCC_USBCKSELR_USBPHYSRC_1

#define IS_RCC_USBPHYCLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_USBPHYCLKSOURCE_HSE) || \
   ((SOURCE) ==RCC_USBPHYCLKSOURCE_PLL4) || \
   ((SOURCE) ==RCC_USBPHYCLKSOURCE_HSE2))
/**
  * @}
  */

/** @defgroup RCCEx_USBO_Clock_Source USBO Clock Source
  * @{
  */
#define RCC_USBOCLKSOURCE_PLL4            0U
#define RCC_USBOCLKSOURCE_PHY             RCC_USBCKSELR_USBOSRC

#define IS_RCC_USBOCLKSOURCE(SOURCE)  (((SOURCE) == RCC_USBOCLKSOURCE_PLL4) || \
                                       ((SOURCE) == RCC_USBOCLKSOURCE_PHY))
/**
  * @}
  */


/** @defgroup RCCEx_RNG1_Clock_Source RNG1 Clock Source
  * @{
  */
#define RCC_RNG1CLKSOURCE_CSI         0U
#define RCC_RNG1CLKSOURCE_PLL4        RCC_RNG1CKSELR_RNG1SRC_0
#define RCC_RNG1CLKSOURCE_LSI         (RCC_RNG1CKSELR_RNG1SRC_1 | RCC_RNG1CKSELR_RNG1SRC_0)

#define IS_RCC_RNG1CLKSOURCE(SOURCE)  (((SOURCE) == RCC_RNG1CLKSOURCE_CSI)  || \
                                       ((SOURCE) == RCC_RNG1CLKSOURCE_PLL4) || \
                                       ((SOURCE) == RCC_RNG1CLKSOURCE_LSI))

/**
  * @}
  */

/** @defgroup RCCEx_CKPER_Clock_Source CKPER Clock Source
  * @{
  */
#define RCC_CKPERCLKSOURCE_HSI          0U
#define RCC_CKPERCLKSOURCE_CSI          RCC_CPERCKSELR_CKPERSRC_0
#define RCC_CKPERCLKSOURCE_HSE          RCC_CPERCKSELR_CKPERSRC_1
#define RCC_CKPERCLKSOURCE_OFF          (RCC_CPERCKSELR_CKPERSRC_1 | RCC_CPERCKSELR_CKPERSRC_0) /*Clock disabled*/

#define IS_RCC_CKPERCLKSOURCE(SOURCE) (((SOURCE) == RCC_CKPERCLKSOURCE_HSI) || \
                                       ((SOURCE) == RCC_CKPERCLKSOURCE_CSI) || \
                                       ((SOURCE) == RCC_CKPERCLKSOURCE_HSE) || \
                                       ((SOURCE) == RCC_CKPERCLKSOURCE_OFF))
/**
  * @}
  */


/** @defgroup RCCEx_STGEN_Clock_Source STGEN Clock Source
  * @{
  */
#define RCC_STGENCLKSOURCE_HSI          0U
#define RCC_STGENCLKSOURCE_HSE          RCC_STGENCKSELR_STGENSRC_0
#define RCC_STGENCLKSOURCE_OFF          RCC_STGENCKSELR_STGENSRC_1

#define IS_RCC_STGENCLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_STGENCLKSOURCE_HSI) || \
   ((SOURCE) == RCC_STGENCLKSOURCE_HSE) || \
   ((SOURCE) == RCC_STGENCLKSOURCE_OFF))
/**
  * @}
  */

#if defined(RCC_PERIPHCLK_DCMIPP)
/** @defgroup RCCEx_DCMIPP_Clock_Source DCMIPP Clock Source
  * @{
  */
#define RCC_DCMIPPCLKSOURCE_ACLK         0U
#define RCC_DCMIPPCLKSOURCE_PLL2         RCC_DCMIPPCKSELR_DCMIPPSRC_0
#define RCC_DCMIPPCLKSOURCE_PLL4         RCC_DCMIPPCKSELR_DCMIPPSRC_1
#define RCC_DCMIPPCLKSOURCE_PER          (RCC_DCMIPPCKSELR_DCMIPPSRC_1 | RCC_DCMIPPCKSELR_DCMIPPSRC_0)

#define IS_RCC_DCMIPPCLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_DCMIPPCLKSOURCE_ACLK) || \
   ((SOURCE) == RCC_DCMIPPCLKSOURCE_PLL2) || \
   ((SOURCE) == RCC_DCMIPPCLKSOURCE_PLL4) || \
   ((SOURCE) == RCC_DCMIPPCLKSOURCE_PER))
/**
  * @}
  */
#endif /* RCC_PERIPHCLK_DCMIPP */

#if defined(RCC_PERIPHCLK_SAES)
/** @defgroup RCCEx_SAES_Clock_Source SAES Clock Source
  * @{
  */
#define RCC_SAESCLKSOURCE_ACLK           0U
#define RCC_SAESCLKSOURCE_PER            RCC_SAESCKSELR_SAESSRC_0
#define RCC_SAESCLKSOURCE_PLL4           RCC_SAESCKSELR_SAESSRC_1
#define RCC_SAESCLKSOURCE_LSI            (RCC_SAESCKSELR_SAESSRC_1 | RCC_SAESCKSELR_SAESSRC_0)

#define IS_RCC_SAESCLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_SAESCLKSOURCE_ACLK) || \
   ((SOURCE) == RCC_SAESCLKSOURCE_PER)  || \
   ((SOURCE) == RCC_SAESCLKSOURCE_PLL4) || \
   ((SOURCE) == RCC_SAESCLKSOURCE_LSI))
/**
  * @}
  */
#endif /* RCC_PERIPHCLK_SAES */

/** @defgroup RCCEx_ADC1_Clock_Source ADC1 Clock Source
  * @{
  */
#define RCC_ADC1CLKSOURCE_PLL4           0U
#define RCC_ADC1CLKSOURCE_PER            RCC_ADC12CKSELR_ADC1SRC_0
#define RCC_ADC1CLKSOURCE_PLL3           RCC_ADC12CKSELR_ADC1SRC_1

#define IS_RCC_ADC1CLKSOURCE(SOURCE) (((SOURCE) == RCC_ADC1CLKSOURCE_PLL4)  || \
                                      ((SOURCE) == RCC_ADC1CLKSOURCE_PER)   || \
                                      ((SOURCE) == RCC_ADC1CLKSOURCE_PLL3))
/**
  * @}
  */

/** @defgroup RCCEx_ADC2_Clock_Source ADC2 Clock Source
  * @{
  */
#define RCC_ADC2CLKSOURCE_PLL4           0U
#define RCC_ADC2CLKSOURCE_PER            RCC_ADC12CKSELR_ADC2SRC_0
#define RCC_ADC2CLKSOURCE_PLL3           RCC_ADC12CKSELR_ADC2SRC_1

#define IS_RCC_ADC2CLKSOURCE(SOURCE) (((SOURCE) == RCC_ADC2CLKSOURCE_PLL4)  || \
                                      ((SOURCE) == RCC_ADC2CLKSOURCE_PER)   || \
                                      ((SOURCE) == RCC_ADC2CLKSOURCE_PLL3))
/**
  * @}
  */

/** @defgroup RCCEx_LPTIM1_Clock_Source LPTIM1 Clock Source
  * @{
  */
#define RCC_LPTIM1CLKSOURCE_PCLK1       0U
#define RCC_LPTIM1CLKSOURCE_PLL4        RCC_LPTIM1CKSELR_LPTIM1SRC_0
#define RCC_LPTIM1CLKSOURCE_PLL3        RCC_LPTIM1CKSELR_LPTIM1SRC_1
#define RCC_LPTIM1CLKSOURCE_LSE         (RCC_LPTIM1CKSELR_LPTIM1SRC_1 | RCC_LPTIM1CKSELR_LPTIM1SRC_0)
#define RCC_LPTIM1CLKSOURCE_LSI         RCC_LPTIM1CKSELR_LPTIM1SRC_2
#define RCC_LPTIM1CLKSOURCE_PER         (RCC_LPTIM1CKSELR_LPTIM1SRC_2 | RCC_LPTIM1CKSELR_LPTIM1SRC_0)
#define RCC_LPTIM1CLKSOURCE_OFF         (RCC_LPTIM1CKSELR_LPTIM1SRC_2 | RCC_LPTIM1CKSELR_LPTIM1SRC_1)

#define IS_RCC_LPTIM1CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_LPTIM1CLKSOURCE_PCLK1) || \
   ((SOURCE) == RCC_LPTIM1CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_LPTIM1CLKSOURCE_PLL3)  || \
   ((SOURCE) == RCC_LPTIM1CLKSOURCE_LSE)   || \
   ((SOURCE) == RCC_LPTIM1CLKSOURCE_LSI)   || \
   ((SOURCE) == RCC_LPTIM1CLKSOURCE_PER)   || \
   ((SOURCE) == RCC_LPTIM1CLKSOURCE_OFF))
/**
  * @}
  */

#if defined(RCC_LPTIM23CKSELR_LPTIM23SRC)
/** @defgroup RCCEx_LPTIM23_Clock_Source LPTIM23 Clock Source
  * @{
  */
#define RCC_LPTIM23CLKSOURCE_PCLK3       0U
#define RCC_LPTIM23CLKSOURCE_PLL4        RCC_LPTIM23CKSELR_LPTIM23SRC_0
#define RCC_LPTIM23CLKSOURCE_PER         RCC_LPTIM23CKSELR_LPTIM23SRC_1
#define RCC_LPTIM23CLKSOURCE_LSE         (RCC_LPTIM23CKSELR_LPTIM23SRC_1 | RCC_LPTIM23CKSELR_LPTIM23SRC_0)
#define RCC_LPTIM23CLKSOURCE_LSI         RCC_LPTIM23CKSELR_LPTIM23SRC_2
#define RCC_LPTIM23CLKSOURCE_OFF         (RCC_LPTIM23CKSELR_LPTIM23SRC_2 | RCC_LPTIM23CKSELR_LPTIM23SRC_0)


#define IS_RCC_LPTIM23CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_LPTIM23CLKSOURCE_PCLK3) || \
   ((SOURCE) == RCC_LPTIM23CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_LPTIM23CLKSOURCE_PER)   || \
   ((SOURCE) == RCC_LPTIM23CLKSOURCE_LSE)   || \
   ((SOURCE) == RCC_LPTIM23CLKSOURCE_LSI)   || \
   ((SOURCE) == RCC_LPTIM23CLKSOURCE_OFF))
/**
  * @}
  */
#endif /* RCC_LPTIM23CKSELR_LPTIM23SRC */

#if defined(RCC_LPTIM23CKSELR_LPTIM2SRC)
/** @defgroup RCCEx_LPTIM2_Clock_Source LPTIM2 Clock Source
  * @{
  */
#define RCC_LPTIM2CLKSOURCE_PCLK3       0U
#define RCC_LPTIM2CLKSOURCE_PLL4        RCC_LPTIM23CKSELR_LPTIM2SRC_0
#define RCC_LPTIM2CLKSOURCE_PER         RCC_LPTIM23CKSELR_LPTIM2SRC_1
#define RCC_LPTIM2CLKSOURCE_LSE         (RCC_LPTIM23CKSELR_LPTIM2SRC_1 | RCC_LPTIM23CKSELR_LPTIM2SRC_0)
#define RCC_LPTIM2CLKSOURCE_LSI         RCC_LPTIM23CKSELR_LPTIM2SRC_2
#define RCC_LPTIM2CLKSOURCE_OFF         (RCC_LPTIM23CKSELR_LPTIM2SRC_2 | RCC_LPTIM23CKSELR_LPTIM2SRC_0)


#define IS_RCC_LPTIM2CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_LPTIM2CLKSOURCE_PCLK3) || \
   ((SOURCE) == RCC_LPTIM2CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_LPTIM2CLKSOURCE_PER)   || \
   ((SOURCE) == RCC_LPTIM2CLKSOURCE_LSE)   || \
   ((SOURCE) == RCC_LPTIM2CLKSOURCE_LSI)   || \
   ((SOURCE) == RCC_LPTIM2CLKSOURCE_OFF))
/**
  * @}
  */
#endif /* RCC_LPTIM23CKSELR_LPTIM2SRC */

#if defined(RCC_LPTIM23CKSELR_LPTIM3SRC)
/** @defgroup RCCEx_LPTIM3_Clock_Source LPTIM3 Clock Source
  * @{
  */
#define RCC_LPTIM3CLKSOURCE_PCLK3       0U
#define RCC_LPTIM3CLKSOURCE_PLL4        RCC_LPTIM23CKSELR_LPTIM3SRC_0
#define RCC_LPTIM3CLKSOURCE_PER         RCC_LPTIM23CKSELR_LPTIM3SRC_1
#define RCC_LPTIM3CLKSOURCE_LSE         (RCC_LPTIM23CKSELR_LPTIM3SRC_1 | RCC_LPTIM23CKSELR_LPTIM3SRC_0)
#define RCC_LPTIM3CLKSOURCE_LSI         RCC_LPTIM23CKSELR_LPTIM3SRC_2
#define RCC_LPTIM3CLKSOURCE_OFF         (RCC_LPTIM23CKSELR_LPTIM3SRC_2 | RCC_LPTIM23CKSELR_LPTIM3SRC_0)


#define IS_RCC_LPTIM3CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_LPTIM3CLKSOURCE_PCLK3) || \
   ((SOURCE) == RCC_LPTIM3CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_LPTIM3CLKSOURCE_PER)   || \
   ((SOURCE) == RCC_LPTIM3CLKSOURCE_LSE)   || \
   ((SOURCE) == RCC_LPTIM3CLKSOURCE_LSI)   || \
   ((SOURCE) == RCC_LPTIM3CLKSOURCE_OFF))
/**
  * @}
  */
#endif /* RCC_LPTIM23CKSELR_LPTIM3SRC */

/** @defgroup RCCEx_LPTIM45_Clock_Source LPTIM45 Clock Source
  * @{
  */
#define RCC_LPTIM45CLKSOURCE_PCLK3      0U
#define RCC_LPTIM45CLKSOURCE_PLL4       RCC_LPTIM45CKSELR_LPTIM45SRC_0
#define RCC_LPTIM45CLKSOURCE_PLL3       RCC_LPTIM45CKSELR_LPTIM45SRC_1
#define RCC_LPTIM45CLKSOURCE_LSE        (RCC_LPTIM45CKSELR_LPTIM45SRC_1 | RCC_LPTIM45CKSELR_LPTIM45SRC_0)
#define RCC_LPTIM45CLKSOURCE_LSI        RCC_LPTIM45CKSELR_LPTIM45SRC_2
#define RCC_LPTIM45CLKSOURCE_PER        (RCC_LPTIM45CKSELR_LPTIM45SRC_2 | RCC_LPTIM45CKSELR_LPTIM45SRC_0)
#define RCC_LPTIM45CLKSOURCE_OFF        (RCC_LPTIM45CKSELR_LPTIM45SRC_2 | RCC_LPTIM45CKSELR_LPTIM45SRC_1)



#define IS_RCC_LPTIM45CLKSOURCE(SOURCE) \
  (((SOURCE) == RCC_LPTIM45CLKSOURCE_PCLK3) || \
   ((SOURCE) == RCC_LPTIM45CLKSOURCE_PLL4)  || \
   ((SOURCE) == RCC_LPTIM45CLKSOURCE_PLL3)  || \
   ((SOURCE) == RCC_LPTIM45CLKSOURCE_LSE)   || \
   ((SOURCE) == RCC_LPTIM45CLKSOURCE_LSI)   || \
   ((SOURCE) == RCC_LPTIM45CLKSOURCE_PER)   || \
   ((SOURCE) == RCC_LPTIM45CLKSOURCE_OFF))
/**
  * @}
  */


/** @defgroup RCCEx_TIMG1_Prescaler_Selection TIMG1 Prescaler Selection
  * @{
  */
#define RCC_TIMG1PRES_DEACTIVATED                0U
#define RCC_TIMG1PRES_ACTIVATED                  RCC_TIMG1PRER_TIMG1PRE

#define IS_RCC_TIMG1PRES(PRES)  (((PRES) == RCC_TIMG1PRES_DEACTIVATED)    || \
                                 ((PRES) == RCC_TIMG1PRES_ACTIVATED))
/**
  * @}
  */


/** @defgroup RCCEx_TIMG2_Prescaler_Selection TIMG2 Prescaler Selection
  * @{
  */
#define RCC_TIMG2PRES_DEACTIVATED                0U
#define RCC_TIMG2PRES_ACTIVATED                  RCC_TIMG2PRER_TIMG2PRE

#define IS_RCC_TIMG2PRES(PRES)  (((PRES) == RCC_TIMG2PRES_DEACTIVATED)    || \
                                 ((PRES) == RCC_TIMG2PRES_ACTIVATED))
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
/** @brief macro to configure the I2C12 clock (I2C12CLK).
  *
  * @param  __I2C12CLKSource__: specifies the I2C12 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_I2C12CLKSOURCE_PCLK1:  PCLK1 selected as I2C12 clock (default after reset)
  *            @arg RCC_I2C12CLKSOURCE_PLL4:   PLL4_R selected as I2C12 clock
  *            @arg RCC_I2C12CLKSOURCE_HSI:    HSI selected as I2C12 clock
  *            @arg RCC_I2C12CLKSOURCE_CSI:    CSI selected as I2C12 clock
  * @retval None
  */
#define __HAL_RCC_I2C12_CONFIG(__I2C12CLKSource__) \
  MODIFY_REG(RCC->I2C12CKSELR, RCC_I2C12CKSELR_I2C12SRC, (uint32_t)(__I2C12CLKSource__))

/** @brief  macro to get the I2C12 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C12CLKSOURCE_PCLK1:  PCLK1 selected as I2C12 clock
  *            @arg RCC_I2C12CLKSOURCE_PLL4:   PLL4_R selected as I2C12 clock
  *            @arg RCC_I2C12CLKSOURCE_HSI:    HSI selected as I2C12 clock
  *            @arg RCC_I2C12CLKSOURCE_CSI:    CSI selected as I2C12 clock
  */
#define __HAL_RCC_GET_I2C12_SOURCE() ((uint32_t)(READ_BIT(RCC->I2C12CKSELR, RCC_I2C12CKSELR_I2C12SRC)))

#if defined(RCC_I2C35CKSELR_I2C35SRC)
/** @brief macro to configure the I2C35 clock (I2C35CLK).
  *
  * @param  __I2C35CLKSource__: specifies the I2C35 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_I2C35CLKSOURCE_PCLK1:  PCLK1 selected as I2C35 clock (default after reset)
  *            @arg RCC_I2C35CLKSOURCE_PLL4:   PLL4_R selected as I2C35 clock
  *            @arg RCC_I2C35CLKSOURCE_HSI:    HSI selected as I2C35 clock
  *            @arg RCC_I2C35CLKSOURCE_CSI:    CSI selected as I2C35 clock
  * @retval None
  */
#define __HAL_RCC_I2C35_CONFIG(__I2C35CLKSource__) \
  MODIFY_REG(RCC->I2C35CKSELR, RCC_I2C35CKSELR_I2C35SRC, (uint32_t)(__I2C35CLKSource__))

/** @brief  macro to get the I2C35 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C35CLKSOURCE_PCLK1:  PCLK1 selected as I2C35 clock
  *            @arg RCC_I2C35CLKSOURCE_PLL4:   PLL4_R selected as I2C35 clock
  *            @arg RCC_I2C35CLKSOURCE_HSI:    HSI selected as I2C35 clock
  *            @arg RCC_I2C35CLKSOURCE_CSI:    CSI selected as I2C35 clock
  */
#define __HAL_RCC_GET_I2C35_SOURCE() ((uint32_t)(READ_BIT(RCC->I2C35CKSELR, RCC_I2C35CKSELR_I2C35SRC)))
#endif /* RCC_I2C35CKSELR_I2C35SRC */

#if defined(RCC_I2C46CKSELR_I2C46SRC)
/** @brief macro to configure the I2C46 clock (I2C46CLK).
  *
  * @param  __I2C46CLKSource__: specifies the I2C46 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_I2C46CLKSOURCE_PCLK5:  PCLK5 selected as I2C46 clock (default after reset)
  *            @arg RCC_I2C46CLKSOURCE_PLL3:   PLL3_Q selected as I2C46 clock
  *            @arg RCC_I2C46CLKSOURCE_HSI:    HSI selected as I2C46 clock
  *            @arg RCC_I2C46CLKSOURCE_CSI:    CSI selected as I2C46 clock
  * @retval None
  */
#define __HAL_RCC_I2C46_CONFIG(__I2C46CLKSource__) \
  MODIFY_REG(RCC->I2C46CKSELR, RCC_I2C46CKSELR_I2C46SRC, (uint32_t)(__I2C46CLKSource__))

/** @brief  macro to get the I2C46 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C46CLKSOURCE_PCLK5:  PCLK5 selected as I2C46 clock
  *            @arg RCC_I2C46CLKSOURCE_PLL3:   PLL3_Q selected as I2C46 clock
  *            @arg RCC_I2C46CLKSOURCE_HSI:    HSI selected as I2C46 clock
  *            @arg RCC_I2C46CLKSOURCE_CSI:    CSI selected as I2C46 clock
  */
#define __HAL_RCC_GET_I2C46_SOURCE() ((uint32_t)(READ_BIT(RCC->I2C46CKSELR, RCC_I2C46CKSELR_I2C46SRC)))
#endif /* RCC_I2C46CKSELR_I2C46SRC */

/** @brief macro to configure the I2C3 clock (I2C3CLK).
  *
  * @param  __I2C3CLKSource__: specifies the I2C3 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_I2C3CLKSOURCE_PCLK6:  PCLK6 selected as I2C3 clock (default after reset)
  *            @arg RCC_I2C3CLKSOURCE_PLL4:   PLL4_R selected as I2C3 clock
  *            @arg RCC_I2C3CLKSOURCE_HSI:    HSI selected as I2C3 clock
  *            @arg RCC_I2C3CLKSOURCE_CSI:    CSI selected as I2C3 clock
  * @retval None
  */
#define __HAL_RCC_I2C3_CONFIG(__I2C3CLKSource__) \
  MODIFY_REG(RCC->I2C345CKSELR, RCC_I2C345CKSELR_I2C3SRC, (uint32_t)(__I2C3CLKSource__))

/** @brief  macro to get the I2C3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C3CLKSOURCE_PCLK6:  PCLK6 selected as I2C3 clock
  *            @arg RCC_I2C3CLKSOURCE_PLL4:   PLL4_R selected as I2C3 clock
  *            @arg RCC_I2C3CLKSOURCE_HSI:    HSI selected as I2C3 clock
  *            @arg RCC_I2C3CLKSOURCE_CSI:    CSI selected as I2C3 clock
  */
#define __HAL_RCC_GET_I2C3_SOURCE() ((uint32_t)(READ_BIT(RCC->I2C345CKSELR, RCC_I2C345CKSELR_I2C3SRC)))

/** @brief macro to configure the I2C4 clock (I2C4CLK).
  *
  * @param  __I2C4CLKSource__: specifies the I2C4 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_I2C4CLKSOURCE_PCLK6:  PCLK6 selected as I2C4 clock (default after reset)
  *            @arg RCC_I2C4CLKSOURCE_PLL4:   PLL4_R selected as I2C4 clock
  *            @arg RCC_I2C4CLKSOURCE_HSI:    HSI selected as I2C4 clock
  *            @arg RCC_I2C4CLKSOURCE_CSI:    CSI selected as I2C4 clock
  * @retval None
  */
#define __HAL_RCC_I2C4_CONFIG(__I2C4CLKSource__) \
  MODIFY_REG(RCC->I2C345CKSELR, RCC_I2C345CKSELR_I2C4SRC, (uint32_t)(__I2C4CLKSource__))

/** @brief  macro to get the I2C4 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C4CLKSOURCE_PCLK6:  PCLK6 selected as I2C4 clock
  *            @arg RCC_I2C4CLKSOURCE_PLL4:   PLL4_R selected as I2C4 clock
  *            @arg RCC_I2C4CLKSOURCE_HSI:    HSI selected as I2C4 clock
  *            @arg RCC_I2C4CLKSOURCE_CSI:    CSI selected as I2C4 clock
  */
#define __HAL_RCC_GET_I2C4_SOURCE() ((uint32_t)(READ_BIT(RCC->I2C345CKSELR, RCC_I2C345CKSELR_I2C4SRC)))

/** @brief macro to configure the I2C5 clock (I2C5CLK).
  *
  * @param  __I2C5CLKSource__: specifies the I2C5 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_I2C5CLKSOURCE_PCLK6:  PCLK6 selected as I2C5 clock (default after reset)
  *            @arg RCC_I2C5CLKSOURCE_PLL4:   PLL4_R selected as I2C5 clock
  *            @arg RCC_I2C5CLKSOURCE_HSI:    HSI selected as I2C5 clock
  *            @arg RCC_I2C5CLKSOURCE_CSI:    CSI selected as I2C5 clock
  * @retval None
  */
#define __HAL_RCC_I2C5_CONFIG(__I2C5CLKSource__) \
  MODIFY_REG(RCC->I2C345CKSELR, RCC_I2C345CKSELR_I2C5SRC, (uint32_t)(__I2C5CLKSource__))

/** @brief  macro to get the I2C5 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_I2C5CLKSOURCE_PCLK6:  PCLK6 selected as I2C5 clock
  *            @arg RCC_I2C5CLKSOURCE_PLL4:   PLL4_R selected as I2C5 clock
  *            @arg RCC_I2C5CLKSOURCE_HSI:    HSI selected as I2C5 clock
  *            @arg RCC_I2C5CLKSOURCE_CSI:    CSI selected as I2C5 clock
  */
#define __HAL_RCC_GET_I2C5_SOURCE() ((uint32_t)(READ_BIT(RCC->I2C345CKSELR, RCC_I2C345CKSELR_I2C5SRC)))

/**
  * @brief  Macro to Configure the SAI1 clock source.
  * @param  __RCC_SAI1CLKSource__: defines the SAI1 clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_SAI1CLKSOURCE_PLL4:    SAI1 clock = PLL4Q
  *             @arg RCC_SAI1CLKSOURCE_PLL3_Q:  SAI1 clock = PLL3Q
  *             @arg RCC_SAI1CLKSOURCE_I2SCKIN: SAI1 clock = I2SCKIN
  *             @arg RCC_SAI1CLKSOURCE_PER:     SAI1 clock = PER
  *             @arg RCC_SAI1CLKSOURCE_PLL3_R:  SAI1 clock = PLL3R
  * @retval None
  */
#define __HAL_RCC_SAI1_CONFIG(__RCC_SAI1CLKSource__ ) \
  MODIFY_REG(RCC->SAI1CKSELR, RCC_SAI1CKSELR_SAI1SRC, (uint32_t)(__RCC_SAI1CLKSource__))

/** @brief  Macro to get the SAI1 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SAI1CLKSOURCE_PLL4:    SAI1 clock = PLL4Q
  *             @arg RCC_SAI1CLKSOURCE_PLL3_Q:  SAI1 clock = PLL3Q
  *             @arg RCC_SAI1CLKSOURCE_I2SCKIN: SAI1 clock = I2SCKIN
  *             @arg RCC_SAI1CLKSOURCE_PER:     SAI1 clock = PER
  *             @arg RCC_SAI1CLKSOURCE_PLL3_R:  SAI1 clock = PLL3R
  */
#define __HAL_RCC_GET_SAI1_SOURCE() ((uint32_t)(READ_BIT(RCC->SAI1CKSELR, RCC_SAI1CKSELR_SAI1SRC)))


/**
  * @brief  Macro to Configure the SAI2 clock source.
  * @param  __RCC_SAI2CLKSource__: defines the SAI2 clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_SAI2CLKSOURCE_PLL4:    SAI2 clock = PLL4Q
  *             @arg RCC_SAI2CLKSOURCE_PLL3_Q:  SAI2 clock = PLL3Q
  *             @arg RCC_SAI2CLKSOURCE_I2SCKIN: SAI2 clock = I2SCKIN
  *             @arg RCC_SAI2CLKSOURCE_PER:     SAI2 clock = PER
  *             @arg RCC_SAI2CLKSOURCE_SPDIF:   SAI2 clock = SPDIF_CK_SYMB
  *             @arg RCC_SAI2CLKSOURCE_PLL3_R:  SAI2 clock = PLL3R
  * @retval None
  */
#define __HAL_RCC_SAI2_CONFIG(__RCC_SAI2CLKSource__ ) \
  MODIFY_REG(RCC->SAI2CKSELR, RCC_SAI2CKSELR_SAI2SRC, (uint32_t)(__RCC_SAI2CLKSource__))

/** @brief  Macro to get the SAI2 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SAI2CLKSOURCE_PLL4:    SAI2 clock = PLL4Q
  *             @arg RCC_SAI2CLKSOURCE_PLL3_Q:  SAI2 clock = PLL3Q
  *             @arg RCC_SAI2CLKSOURCE_I2SCKIN: SAI2 clock = I2SCKIN
  *             @arg RCC_SAI2CLKSOURCE_PER:     SAI2 clock = PER
  *             @arg RCC_SAI2CLKSOURCE_SPDIF:   SAI2 clock = SPDIF_CK_SYMB
  *             @arg RCC_SAI2CLKSOURCE_PLL3_R:  SAI2 clock = PLL3R
  */
#define __HAL_RCC_GET_SAI2_SOURCE() ((uint32_t)(READ_BIT(RCC->SAI2CKSELR, RCC_SAI2CKSELR_SAI2SRC)))

/**
  * @brief  Macro to Configure the SPI/I2S1 clock source.
  * @param  __RCC_SPI1CLKSource__: defines the SPI/I2S1 clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_SPI1CLKSOURCE_PLL4:    SPI1 clock = PLL4P
  *             @arg RCC_SPI1CLKSOURCE_PLL3_Q:  SPI1 clock = PLL3Q
  *             @arg RCC_SPI1CLKSOURCE_I2SCKIN: SPI1 clock = I2SCKIN
  *             @arg RCC_SPI1CLKSOURCE_PER:     SPI1 clock = PER
  *             @arg RCC_SPI1CLKSOURCE_PLL3_R:  SPI1 clock = PLL3R
  * @retval None
  */
#define __HAL_RCC_SPI1_CONFIG(__RCC_SPI1CLKSource__) \
  MODIFY_REG(RCC->SPI2S1CKSELR, RCC_SPI2S1CKSELR_SPI1SRC, (uint32_t)(__RCC_SPI1CLKSource__))

/** @brief  Macro to get the SPI/I2S1 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SPI1CLKSOURCE_PLL4:    SPI1 clock = PLL4P
  *             @arg RCC_SPI1CLKSOURCE_PLL3_Q:  SPI1 clock = PLL3Q
  *             @arg RCC_SPI1CLKSOURCE_I2SCKIN: SPI1 clock = I2SCKIN
  *             @arg RCC_SPI1CLKSOURCE_PER:     SPI1 clock = PER
  *             @arg RCC_SPI1CLKSOURCE_PLL3_R:  SPI1 clock = PLL3R
  */
#define __HAL_RCC_GET_SPI1_SOURCE() ((uint32_t)(READ_BIT(RCC->SPI2S1CKSELR, RCC_SPI2S1CKSELR_SPI1SRC)))


/**
  * @brief  Macro to Configure the SPI/I2S2,3 clock source.
  * @param  __RCC_SPI23CLKSource__: defines the SPI/I2S2,3 clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_SPI23CLKSOURCE_PLL4:    SPI23 clock = PLL4P
  *             @arg RCC_SPI23CLKSOURCE_PLL3_Q:  SPI23 clock = PLL3Q
  *             @arg RCC_SPI23CLKSOURCE_I2SCKIN: SPI23 clock = I2SCKIN
  *             @arg RCC_SPI23CLKSOURCE_PER:     SPI23 clock = PER
  *             @arg RCC_SPI23CLKSOURCE_PLL3_R:  SPI23 clock = PLL3R
  * @retval None
  */
#define __HAL_RCC_SPI23_CONFIG(__RCC_SPI23CLKSource__ ) \
  MODIFY_REG(RCC->SPI2S23CKSELR, RCC_SPI2S23CKSELR_SPI23SRC, (uint32_t)(__RCC_SPI23CLKSource__))

/** @brief  Macro to get the SPI/I2S2,3 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SPI23CLKSOURCE_PLL4:    SPI23 clock = PLL4P
  *             @arg RCC_SPI23CLKSOURCE_PLL3_Q:  SPI23 clock = PLL3Q
  *             @arg RCC_SPI23CLKSOURCE_I2SCKIN: SPI23 clock = I2SCKIN
  *             @arg RCC_SPI23CLKSOURCE_PER:     SPI23 clock = PER
  *             @arg RCC_SPI23CLKSOURCE_PLL3_R:  SPI23 clock = PLL3R
  */
#define __HAL_RCC_GET_SPI23_SOURCE() ((uint32_t)(READ_BIT(RCC->SPI2S23CKSELR, RCC_SPI2S23CKSELR_SPI23SRC)))

/**
  * @brief  Macro to Configure the SPI4 clock source.
  * @param  __RCC_SPI4CLKSource__: defines the SPI4 clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_SPI4CLKSOURCE_PCLK6:   SPI4 clock = PCLK6
  *             @arg RCC_SPI4CLKSOURCE_PLL4:    SPI4 clock = PLL4Q
  *             @arg RCC_SPI4CLKSOURCE_HSI:     SPI4 clock = HSI
  *             @arg RCC_SPI4CLKSOURCE_CSI:     SPI4 clock = CSI
  *             @arg RCC_SPI4CLKSOURCE_HSE:     SPI4 clock = HSE
  *             @arg RCC_SPI4CLKSOURCE_I2SCKIN: SPI4 clock = I2SCKIN
  * @retval None
  */
#define __HAL_RCC_SPI4_CONFIG(__RCC_SPI4CLKSource__ ) \
  MODIFY_REG(RCC->SPI45CKSELR, RCC_SPI45CKSELR_SPI4SRC, (uint32_t)(__RCC_SPI4CLKSource__))

/** @brief  Macro to get the SPI4 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SPI4CLKSOURCE_PCLK6:   SPI4 clock = PCLK6
  *             @arg RCC_SPI4CLKSOURCE_PLL4:    SPI4 clock = PLL4Q
  *             @arg RCC_SPI4CLKSOURCE_HSI:     SPI4 clock = HSI
  *             @arg RCC_SPI4CLKSOURCE_CSI:     SPI4 clock = CSI
  *             @arg RCC_SPI4CLKSOURCE_HSE:     SPI4 clock = HSE
  *             @arg RCC_SPI4CLKSOURCE_I2SCKIN: SPI4 clock = I2SCKIN
  */
#define __HAL_RCC_GET_SPI4_SOURCE() ((uint32_t)(READ_BIT(RCC->SPI45CKSELR, RCC_SPI45CKSELR_SPI4SRC)))

/**
  * @brief  Macro to Configure the SPI5 clock source.
  * @param  __RCC_SPI5CLKSource__: defines the SPI5 clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_SPI5CLKSOURCE_PCLK6:   SPI5 clock = PCLK6
  *             @arg RCC_SPI5CLKSOURCE_PLL4:    SPI5 clock = PLL4Q
  *             @arg RCC_SPI5CLKSOURCE_HSI:     SPI5 clock = HSI
  *             @arg RCC_SPI5CLKSOURCE_CSI:     SPI5 clock = CSI
  *             @arg RCC_SPI5CLKSOURCE_HSE:     SPI5 clock = HSE
  * @retval None
  */
#define __HAL_RCC_SPI5_CONFIG(__RCC_SPI5CLKSource__ ) \
  MODIFY_REG(RCC->SPI45CKSELR, RCC_SPI45CKSELR_SPI5SRC, (uint32_t)(__RCC_SPI5CLKSource__))

/** @brief  Macro to get the SPI5 clock source.
  * @retval The clock source can be one of the following values:
  *             @arg RCC_SPI5CLKSOURCE_PCLK6:   SPI5 clock = PCLK6
  *             @arg RCC_SPI5CLKSOURCE_PLL4:    SPI5 clock = PLL4Q
  *             @arg RCC_SPI5CLKSOURCE_HSI:     SPI5 clock = HSI
  *             @arg RCC_SPI5CLKSOURCE_CSI:     SPI5 clock = CSI
  *             @arg RCC_SPI5CLKSOURCE_HSE:     SPI5 clock = HSE
  */
#define __HAL_RCC_GET_SPI5_SOURCE() ((uint32_t)(READ_BIT(RCC->SPI45CKSELR, RCC_SPI45CKSELR_SPI5SRC)))


/** @brief macro to configure the USART1 clock (USART1CLK).
  *
  * @param  __USART1CLKSource__: specifies the USART1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USART1CLKSOURCE_PCLK6:  PCLK6 Clock selected as USART1 clock (default after reset)
  *            @arg RCC_USART1CLKSOURCE_PLL3:   PLL3_Q Clock selected as USART1 clock USART1
  *            @arg RCC_USART1CLKSOURCE_HSI:    HSI Clock selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_CSI:    CSI Clock selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_PLL4:   PLL4_Q Clock selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_HSE:    HSE Clock selected as USART1 clock
  * @retval None
  */
#define __HAL_RCC_USART1_CONFIG(__USART1CLKSource__) \
  MODIFY_REG(RCC->UART12CKSELR, RCC_UART12CKSELR_UART1SRC, (uint32_t)(__USART1CLKSource__))

/** @brief  macro to get the USART1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USART1CLKSOURCE_PCLK6:  PCLK6 Clock selected as USART1 clock (default after reset)
  *            @arg RCC_USART1CLKSOURCE_PLL3:   PLL3_Q Clock selected as USART1
  *            @arg RCC_USART1CLKSOURCE_HSI:    HSI Clock selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_CSI:    CSI Clock selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_PLL4:   PLL4_Q Clock selected as USART1 clock
  *            @arg RCC_USART1CLKSOURCE_HSE:    HSE Clock selected as USART1 clock
  */
#define __HAL_RCC_GET_USART1_SOURCE() ((uint32_t)(READ_BIT(RCC->UART12CKSELR, RCC_UART12CKSELR_UART1SRC)))


/** @brief macro to configure the USART2 clock (USART2CLK).
  *
  * @param  __USART2CLKSource__: specifies the USART2 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USART2CLKSOURCE_PCLK6:  PCLK6 Clock selected as USART2 clock (default after reset)
  *            @arg RCC_USART2CLKSOURCE_PLL3:   PLL3_Q Clock selected as USART2 clock USART2
  *            @arg RCC_USART2CLKSOURCE_HSI:    HSI Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_CSI:    CSI Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_PLL4:   PLL4_Q Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_HSE:    HSE Clock selected as USART2 clock
  * @retval None
  */
#define __HAL_RCC_USART2_CONFIG(__USART2CLKSource__) \
  MODIFY_REG(RCC->UART12CKSELR, RCC_UART12CKSELR_UART2SRC, (uint32_t)(__USART2CLKSource__))

/** @brief  macro to get the USART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USART2CLKSOURCE_PCLK6:  PCLK6 Clock selected as USART2 clock (default after reset)
  *            @arg RCC_USART2CLKSOURCE_PLL3:   PLL3_Q Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_HSI:    HSI Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_CSI:    CSI Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_PLL4:   PLL4_Q Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_HSE:    HSE Clock selected as USART2 clock
  */
#define __HAL_RCC_GET_USART2_SOURCE() ((uint32_t)(READ_BIT(RCC->UART12CKSELR, RCC_UART12CKSELR_UART2SRC)))

/** @brief macro to configure the UART4 clock (UART4CLK).
  *
  * @param  __UART4CLKSource__: specifies the UART4 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_UART4CLKSOURCE_PCLK1:  PCLK1 Clock selected as UART4 clock (default after reset)
  *            @arg RCC_UART4CLKSOURCE_PLL4:   PLL4_Q Clock selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_HSI:    HSI Clock selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_CSI:    CSI Clock selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_HSE:    HSE Clock selected as UART4 clock
  * @retval None
  */
#define __HAL_RCC_UART4_CONFIG(__UART4CLKSource__) \
  MODIFY_REG(RCC->UART4CKSELR, RCC_UART4CKSELR_UART4SRC, (uint32_t)(__UART4CLKSource__))

/** @brief  macro to get the UART4 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_UART4CLKSOURCE_PCLK1:  PCLK1 Clock selected as UART4 clock (default after reset)
  *            @arg RCC_UART4CLKSOURCE_PLL4:   PLL4_Q Clock selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_HSI:    HSI Clock selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_CSI:    CSI Clock selected as UART4 clock
  *            @arg RCC_UART4CLKSOURCE_HSE:    HSE Clock selected as UART4 clock
  */
#define __HAL_RCC_GET_UART4_SOURCE() ((uint32_t)(READ_BIT(RCC->UART4CKSELR, RCC_UART4CKSELR_UART4SRC)))

/** @brief macro to configure the UART35 clock (UART35CLK).
  *
  * @param  __UART35CLKSource__: specifies the UART35 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_UART35CLKSOURCE_PCLK1: PCLK1 Clock selected as UART35
  *                                            clock (default after reset)
  *            @arg RCC_UART35CLKSOURCE_PLL4:  PLL4_Q Clock selected as UART35 clock
  *            @arg RCC_UART35CLKSOURCE_HSI:   HSI selected as UART35 clock
  *            @arg RCC_UART35CLKSOURCE_CSI:   CSI Clock selected as UART35 clock
  *            @arg RCC_UART35CLKSOURCE_HSE:   HSE selected as UART35 clock
  * @retval None
  */
#define __HAL_RCC_UART35_CONFIG(__UART35CLKSource__) \
  MODIFY_REG(RCC->UART35CKSELR, RCC_UART35CKSELR_UART35SRC, (uint32_t)(__UART35CLKSource__))

/** @brief  macro to get the UART35 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_UART35CLKSOURCE_PCLK1:  PCLK1 Clock selected as UART35 clock
  *            @arg RCC_UART35CLKSOURCE_PLL4:   PLL4_Q Clock selected as UART35 clock
  *            @arg RCC_UART35CLKSOURCE_HSI:    HSI selected as UART35 clock
  *            @arg RCC_UART35CLKSOURCE_CSI:    CSI Clock selected as UART35 clock
  *            @arg RCC_UART35CLKSOURCE_HSE:    HSE selected as UART35 clock
  */
#define __HAL_RCC_GET_UART35_SOURCE() ((uint32_t)(READ_BIT(RCC->UART35CKSELR, RCC_UART35CKSELR_UART35SRC)))


/** @brief macro to configure the USART6 clock (USART6CLK).
  *
  * @param  __USART6CLKSource__: specifies the USART6 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USART6CLKSOURCE_PCLK2: PCLK2 Clock selected as USART6 clock (default after reset)
  *            @arg RCC_USART6CLKSOURCE_PLL4:  PLL4_Q Clock selected as USART6 clock
  *            @arg RCC_USART6CLKSOURCE_HSI:   HSI selected as USART6 clock
  *            @arg RCC_USART6CLKSOURCE_CSI:   CSI Clock selected as USART6 clock
  *            @arg RCC_USART6CLKSOURCE_HSE:   HSE selected as USART6 clock
  * @retval None
  */
#define __HAL_RCC_USART6_CONFIG(__USART6CLKSource__) \
  MODIFY_REG(RCC->UART6CKSELR, RCC_UART6CKSELR_UART6SRC, (uint32_t)(__USART6CLKSource__))

/** @brief  macro to get the USART6 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USART6CLKSOURCE_PCLK2: PCLK2 Clock selected as USART6 clock
  *            @arg RCC_USART6CLKSOURCE_PLL4:  PLL4_Q Clock selected as USART6 clock
  *            @arg RCC_USART6CLKSOURCE_HSI:   HSI selected as USART6 clock
  *            @arg RCC_USART6CLKSOURCE_CSI:   CSI Clock selected as USART6 clock
  *            @arg RCC_USART6CLKSOURCE_HSE:   HSE selected as USART6 clock
  */
#define __HAL_RCC_GET_USART6_SOURCE() ((uint32_t)(READ_BIT(RCC->UART6CKSELR, RCC_UART6CKSELR_UART6SRC)))

/** @brief macro to configure the UART78clock (UART78CLK).
  *
  * @param  __UART78CLKSource__: specifies the UART78 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_UART78CLKSOURCE_PCLK1: PCLK1 Clock selected as UART78 clock (default after reset)
  *            @arg RCC_UART78CLKSOURCE_PLL4:  PLL4_Q Clock selected as UART78 clock
  *            @arg RCC_UART78CLKSOURCE_HSI:   HSI selected as UART78 clock
  *            @arg RCC_UART78CLKSOURCE_CSI:   CSI Clock selected as UART78 clock
  *            @arg RCC_UART78CLKSOURCE_HSE:   HSE selected as UART78 clock
  * @retval None
  */
#define __HAL_RCC_UART78_CONFIG(__UART78CLKSource__) \
  MODIFY_REG(RCC->UART78CKSELR, RCC_UART78CKSELR_UART78SRC, (uint32_t)(__UART78CLKSource__))

/** @brief  macro to get the UART78 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_UART78CLKSOURCE_PCLK1: PCLK1 Clock selected as UART78 clock
  *            @arg RCC_UART78CLKSOURCE_PLL4:  PLL4_Q Clock selected as UART78 clock
  *            @arg RCC_UART78CLKSOURCE_HSI:   HSI selected as UART78 clock
  *            @arg RCC_UART78CLKSOURCE_CSI:   CSI Clock selected as UART78 clock
  *            @arg RCC_UART78CLKSOURCE_HSE:   HSE selected as UART78 clock
  */
#define __HAL_RCC_GET_UART78_SOURCE() ((uint32_t)(READ_BIT(RCC->UART78CKSELR, RCC_UART78CKSELR_UART78SRC)))

/** @brief macro to configure the SDMMC1 clock (SDMMC1CLK).
  *
  * @param  __SDMMC12CLKSource__: specifies the SDMMC12 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_SDMMC1CLKSOURCE_HCLK6: HCLK6 Clock selected as SDMMC12 clock (default after reset)
  *            @arg RCC_SDMMC1CLKSOURCE_PLL3:  PLL3_R Clock selected as SDMMC12 clock
  *            @arg RCC_SDMMC1CLKSOURCE_PLL4:  PLL4_P selected as SDMMC12 clock
  *            @arg RCC_SDMMC1CLKSOURCE_HSI:   HSI selected as SDMMC12 clock
  * @retval None
  */
#define __HAL_RCC_SDMMC1_CONFIG(__SDMMC12CLKSource__) \
  MODIFY_REG(RCC->SDMMC12CKSELR, RCC_SDMMC12CKSELR_SDMMC1SRC, (uint32_t)(__SDMMC12CLKSource__))

/** @brief  macro to get the SDMMC1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SDMMC1CLKSOURCE_HCLK6: HCLK6 Clock selected as SDMMC12 clock (default after reset)
  *            @arg RCC_SDMMC1CLKSOURCE_PLL3:  PLL3_R Clock selected as SDMMC12 clock
  *            @arg RCC_SDMMC1CLKSOURCE_PLL4:  PLL4_P selected as SDMMC12 clock
  *            @arg RCC_SDMMC1CLKSOURCE_HSI:   HSI selected as SDMMC12 clock
  */
#define __HAL_RCC_GET_SDMMC1_SOURCE() ((uint32_t)(READ_BIT(RCC->SDMMC12CKSELR, RCC_SDMMC12CKSELR_SDMMC1SRC)))

/** @brief macro to configure the SDMMC2 clock (SDMMC2CLK).
  *
  * @param  __SDMMC2CLKSource__: specifies the SDMMC2 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_SDMMC2CLKSOURCE_HCLK6: HCLK6 Clock selected as SDMMC2 clock (default after reset)
  *            @arg RCC_SDMMC2CLKSOURCE_PLL3:  PLL3_R Clock selected as SDMMC2 clock
  *            @arg RCC_SDMMC2CLKSOURCE_PLL4:  PLL4_P selected as SDMMC2 clock
  *            @arg RCC_SDMMC2CLKSOURCE_HSI:   HSI selected as SDMMC2 clock
  * @retval None
  */
#define __HAL_RCC_SDMMC2_CONFIG(__SDMMC2CLKSource__) \
  MODIFY_REG(RCC->SDMMC12CKSELR, RCC_SDMMC12CKSELR_SDMMC2SRC, (uint32_t)(__SDMMC2CLKSource__))

/** @brief  macro to get the SDMMC2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SDMMC2CLKSOURCE_HCLK6: HCLK6 Clock selected as SDMMC2 clock (default after reset)
  *            @arg RCC_SDMMC2CLKSOURCE_PLL3:  PLL3_R Clock selected as SDMMC2 clock
  *            @arg RCC_SDMMC2CLKSOURCE_PLL4:  PLL4_P selected as SDMMC2 clock
  *            @arg RCC_SDMMC2CLKSOURCE_HSI:   HSI selected as SDMMC2 clock
  */
#define __HAL_RCC_GET_SDMMC2_SOURCE() ((uint32_t)(READ_BIT(RCC->SDMMC12CKSELR, RCC_SDMMC12CKSELR_SDMMC2SRC)))

/** @brief macro to configure the ETH1 clock (ETH1CLK).
  *
  * @param  __ETH1CLKSource__: specifies the ETH1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_ETH1CLKSOURCE_PLL4:  PLL4_P selected as ETH1 clock (default after reset)
  *            @arg RCC_ETH1CLKSOURCE_PLL3:  PLL3_Q Clock selected as ETH1 clock
  *            @arg RCC_ETH1CLKSOURCE_OFF:   the kernel clock is disabled
  * @retval None
  */
#define __HAL_RCC_ETH1_CONFIG(__ETH1CLKSource__) \
  MODIFY_REG(RCC->ETH12CKSELR, RCC_ETH12CKSELR_ETH1SRC, (uint32_t)(__ETH1CLKSource__))

/** @brief  macro to get the ETH1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ETH1CLKSOURCE_PLL4: PLL4_P selected as ETH1 clock (default after reset)
  *            @arg RCC_ETH1CLKSOURCE_PLL3: PLL3_Q Clock selected as ETH1 clock
  *            @arg RCC_ETH1CLKSOURCE_OFF:  the kernel clock is disabled
  */
#define __HAL_RCC_GET_ETH1_SOURCE() ((uint32_t)(READ_BIT(RCC->ETH12CKSELR, RCC_ETH12CKSELR_ETH1SRC)))

/** @brief macro to configure the ETH2 clock (ETH2CLK).
  *
  * @param  __ETH2CLKSource__: specifies the ETH2 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_ETH2CLKSOURCE_PLL4:  PLL4_P selected as ETH2 clock (default after reset)
  *            @arg RCC_ETH2CLKSOURCE_PLL3:  PLL3_Q Clock selected as ETH2 clock
  *            @arg RCC_ETH2CLKSOURCE_OFF:   the kernel clock is disabled
  * @retval None
  */
#define __HAL_RCC_ETH2_CONFIG(__ETH2CLKSource__) \
  MODIFY_REG(RCC->ETH12CKSELR, RCC_ETH12CKSELR_ETH2SRC, (uint32_t)(__ETH2CLKSource__))

/** @brief  macro to get the ETH2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ETH2CLKSOURCE_PLL4: PLL4_P selected as ETH2 clock (default after reset)
  *            @arg RCC_ETH2CLKSOURCE_PLL3: PLL3_Q Clock selected as ETH2 clock
  *            @arg RCC_ETH2CLKSOURCE_OFF:  the kernel clock is disabled
  */
#define __HAL_RCC_GET_ETH2_SOURCE() ((uint32_t)(READ_BIT(RCC->ETH12CKSELR, RCC_ETH12CKSELR_ETH2SRC)))

/** @brief macro to configure the QSPI clock (QSPICLK).
  *
  * @param  __QSPICLKSource__: specifies the QSPI clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_QSPICLKSOURCE_ACLK:  ACLK Clock selected as QSPI clock (default after reset)
  *            @arg RCC_QSPICLKSOURCE_PLL3:  PLL3_R Clock selected as QSPI clock
  *            @arg RCC_QSPICLKSOURCE_PLL4:  PLL4_P selected as QSPI clock
  *            @arg RCC_QSPICLKSOURCE_PER:   PER selected as QSPI clock
  * @retval None
  */
#define __HAL_RCC_QSPI_CONFIG(__QSPICLKSource__) \
  MODIFY_REG(RCC->QSPICKSELR, RCC_QSPICKSELR_QSPISRC, (uint32_t)(__QSPICLKSource__))

/** @brief  macro to get the QSPI clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_QSPICLKSOURCE_ACLK:  ACLK Clock selected as QSPI clock (default after reset)
  *            @arg RCC_QSPICLKSOURCE_PLL3:  PLL3_R Clock selected as QSPI clock
  *            @arg RCC_QSPICLKSOURCE_PLL4:  PLL4_P selected as QSPI clock
  *            @arg RCC_QSPICLKSOURCE_PER:   PER selected as QSPI clock
  */
#define __HAL_RCC_GET_QSPI_SOURCE() ((uint32_t)(READ_BIT(RCC->QSPICKSELR, RCC_QSPICKSELR_QSPISRC)))


/** @brief macro to configure the FMC clock (FMCCLK).
  *
  * @param  __FMCCLKSource__: specifies the FMC clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_FMCCLKSOURCE_ACLK:  ACLK Clock selected as FMC clock (default after reset)
  *            @arg RCC_FMCCLKSOURCE_PLL3:  PLL3_R Clock selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_PLL4:  PLL4_P selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_PER:   PER selected as FMC clock
  * @retval None
  */
#define __HAL_RCC_FMC_CONFIG(__FMCCLKSource__) \
  MODIFY_REG(RCC->FMCCKSELR, RCC_FMCCKSELR_FMCSRC, (uint32_t)(__FMCCLKSource__))

/** @brief  macro to get the FMC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_FMCCLKSOURCE_ACLK:  ACLK Clock selected as FMC clock (default after reset)
  *            @arg RCC_FMCCLKSOURCE_PLL3:  PLL3_R Clock selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_PLL4:  PLL4_P selected as FMC clock
  *            @arg RCC_FMCCLKSOURCE_PER:   PER selected as FMC clock
  */
#define __HAL_RCC_GET_FMC_SOURCE() ((uint32_t)(READ_BIT(RCC->FMCCKSELR, RCC_FMCCKSELR_FMCSRC)))

#if defined(RCC_PERIPHCLK_FDCAN)
/** @brief macro to configure the FDCAN clock (FDCANCLK).
  *
  * @param  __FDCANCLKSource__: specifies the FDCAN clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_FDCANCLKSOURCE_HSE:    HSE Clock selected as FDCAN clock (default after reset)
  *            @arg RCC_FDCANCLKSOURCE_PLL3:   PLL3_Q Clock selected as FDCAN clock
  *            @arg RCC_FDCANCLKSOURCE_PLL4_Q: PLL4_Q selected as FDCAN clock
  *            @arg RCC_FDCANCLKSOURCE_PLL4_R: PLL4_R selected as FDCAN clock
  * @retval None
  */
#define __HAL_RCC_FDCAN_CONFIG(__FDCANCLKSource__) \
  MODIFY_REG(RCC->FDCANCKSELR, RCC_FDCANCKSELR_FDCANSRC, (uint32_t)(__FDCANCLKSource__))

/** @brief  macro to get the FDCAN clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_FDCANCLKSOURCE_HSE:   HSE Clock selected as FDCAN clock (default after reset)
  *            @arg RCC_FDCANCLKSOURCE_PLL3:  PLL3_Q Clock selected as FDCAN clock
  *            @arg RCC_FDCANCLKSOURCE_PLL4_Q: PLL4_Q selected as FDCAN clock
  *            @arg RCC_FDCANCLKSOURCE_PLL4_R: PLL4_R selected as FDCAN clock
  */
#define __HAL_RCC_GET_FDCAN_SOURCE() ((uint32_t)(READ_BIT(RCC->FDCANCKSELR, RCC_FDCANCKSELR_FDCANSRC)))
#endif /* RCC_PERIPHCLK_FDCAN */

/** @brief macro to configure the SPDIFRX clock (SPDIFCLK).
  *
  * @param  __SPDIFCLKSource__: specifies the SPDIF clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_SPDIFRXCLKSOURCE_PLL4:  PLL4_P Clock selected as SPDIF clock (default after reset)
  *            @arg RCC_SPDIFRXCLKSOURCE_PLL3:  PLL3_Q Clock selected as SPDIF clock
  *            @arg RCC_SPDIFRXCLKSOURCE_HSI:   HSI selected as SPDIF clock
  * @retval None
  */
#define __HAL_RCC_SPDIFRX_CONFIG(__SPDIFCLKSource__) \
  MODIFY_REG(RCC->SPDIFCKSELR, RCC_SPDIFCKSELR_SPDIFSRC, (uint32_t)(__SPDIFCLKSource__))

/** @brief  macro to get the SPDIFRX clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SPDIFRXCLKSOURCE_PLL4:  PLL4_P Clock selected as SPDIF clock (default after reset)
  *            @arg RCC_SPDIFRXCLKSOURCE_PLL3:  PLL3_Q Clock selected as SPDIF clock
  *            @arg RCC_SPDIFRXCLKSOURCE_HSI:   HSI selected as SPDIF clock
  */
#define __HAL_RCC_GET_SPDIFRX_SOURCE() ((uint32_t)(READ_BIT(RCC->SPDIFCKSELR, RCC_SPDIFCKSELR_SPDIFSRC)))

/** @brief macro to configure the USB PHY clock (USBPHYCLK).
  *
  * @param  __USBPHYCLKSource__: specifies the USB PHY clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USBPHYCLKSOURCE_HSE:   HSE_KER   Clock selected as USB PHY clock (default after reset)
  *            @arg RCC_USBPHYCLKSOURCE_PLL4:  PLL4_R    Clock selected as USB PHY clock
  *            @arg RCC_USBPHYCLKSOURCE_HSE2:  HSE_KER/2 Clock selected as USB PHY clock
  * @retval None
  */
#define __HAL_RCC_USBPHY_CONFIG(__USBPHYCLKSource__) \
  MODIFY_REG(RCC->USBCKSELR, RCC_USBCKSELR_USBPHYSRC, (uint32_t)(__USBPHYCLKSource__))

/** @brief  macro to get the USB PHY PLL clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USBPHYCLKSOURCE_HSE:   HSE_KER   Clock selected as USB PHY clock (default after reset)
  *            @arg RCC_USBPHYCLKSOURCE_PLL4:  PLL4_R    Clock selected as USB PHY clock
  *            @arg RCC_USBPHYCLKSOURCE_HSE2:  HSE_KER/2 Clock selected as USB PHY clock
  */
#define __HAL_RCC_GET_USBPHY_SOURCE() ((uint32_t)(READ_BIT(RCC->USBCKSELR, RCC_USBCKSELR_USBPHYSRC)))


/** @brief macro to configure the USB OTG clock (USBOCLK).
  *
  * @param  __USBOCLKSource__: specifies the USB OTG clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_USBOCLKSOURCE_PLL4: PLL4_R Clock selected as USB OTG clock (default after reset)
  *            @arg RCC_USBOCLKSOURCE_PHY:  USB PHY Clock selected as USB OTG clock
  * @retval None
  */
#define __HAL_RCC_USBO_CONFIG(__USBOCLKSource__) \
  MODIFY_REG(RCC->USBCKSELR, RCC_USBCKSELR_USBOSRC, (uint32_t)(__USBOCLKSource__))

/** @brief  macro to get the USB OTG PLL clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USBOCLKSOURCE_PLL4: PLL4_R Clock selected as USB OTG clock (default after reset)
  *            @arg RCC_USBOCLKSOURCE_PHY:  USB PHY Clock selected as USB OTG clock
  */
#define __HAL_RCC_GET_USBO_SOURCE() ((uint32_t)(READ_BIT(RCC->USBCKSELR, RCC_USBCKSELR_USBOSRC)))


/** @brief macro to configure the RNG1 clock (RNG1CLK).
  *
  * @param  __RNG1CLKSource__: specifies the RNG1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_RNG1CLKSOURCE_CSI:   CSI Clock selected as RNG1 clock (default after reset)
  *            @arg RCC_RNG1CLKSOURCE_PLL4:  PLL4_R Clock selected as RNG1 clock
  *            @arg RCC_RNG1CLKSOURCE_LSI:   LSI Clock selected as RNG1 clock
  * @retval None
  */
#define __HAL_RCC_RNG1_CONFIG(__RNG1CLKSource__) \
  MODIFY_REG(RCC->RNG1CKSELR, RCC_RNG1CKSELR_RNG1SRC, (uint32_t)(__RNG1CLKSource__))

/** @brief  macro to get the RNG1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_RNG1CLKSOURCE_CSI:   CSI Clock selected as RNG1 clock (default after reset)
  *            @arg RCC_RNG1CLKSOURCE_PLL4:  PLL4_R Clock selected as RNG1 clock
  *            @arg RCC_RNG1CLKSOURCE_LSI:   LSI Clock selected as RNG1 clock
  */
#define __HAL_RCC_GET_RNG1_SOURCE() ((uint32_t)(READ_BIT(RCC->RNG1CKSELR, RCC_RNG1CKSELR_RNG1SRC)))

/** @brief macro to configure the CK_PER clock (CK_PERCLK).
  *
  * @param  __CKPERCLKSource__: specifies the CPER clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_CKPERCLKSOURCE_HSI:   HSI Clock selected as CK_PER clock (default after reset)
  *            @arg RCC_CKPERCLKSOURCE_CSI:   CSI Clock selected as CK_PER clock
  *            @arg RCC_CKPERCLKSOURCE_HSE:   HSE Clock selected as CK_PER clock
  *            @arg RCC_CKPERCLKSOURCE_OFF:   Clock disabled for CK_PER
  * @retval None
  */
#define __HAL_RCC_CKPER_CONFIG(__CKPERCLKSource__) \
  MODIFY_REG(RCC->CPERCKSELR, RCC_CPERCKSELR_CKPERSRC, (uint32_t)(__CKPERCLKSource__))

/** @brief  macro to get the CPER clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_CKPERCLKSOURCE_HSI:   HSI Clock selected as CK_PER clock (default after reset)
  *            @arg RCC_CKPERCLKSOURCE_CSI:   CSI Clock selected as CK_PER clock
  *            @arg RCC_CKPERCLKSOURCE_HSE:   HSE Clock selected as CK_PER clock
  *            @arg RCC_CKPERCLKSOURCE_OFF:   Clock disabled for CK_PER
  */
#define __HAL_RCC_GET_CKPER_SOURCE() ((uint32_t)(READ_BIT(RCC->CPERCKSELR, RCC_CPERCKSELR_CKPERSRC)))


/** @brief macro to configure the STGEN clock (STGENCLK).
  *
  * @param  __STGENCLKSource__: specifies the STGEN clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_STGENCLKSOURCE_HSI:   HSI Clock selected as STGEN clock (default after reset)
  *            @arg RCC_STGENCLKSOURCE_HSE:   HSE Clock selected as STGEN clock
  *            @arg RCC_STGENCLKSOURCE_OFF:   Clock disabled
  *
  * @retval None
  */
#define __HAL_RCC_STGEN_CONFIG(__STGENCLKSource__) \
  MODIFY_REG(RCC->STGENCKSELR, RCC_STGENCKSELR_STGENSRC, (uint32_t)(__STGENCLKSource__))

/** @brief  macro to get the STGEN clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_STGENCLKSOURCE_HSI:   HSI Clock selected as STGEN clock (default after reset)
  *            @arg RCC_STGENCLKSOURCE_HSE:   HSE Clock selected as STGEN clock
  *            @arg RCC_STGENCLKSOURCE_OFF:   Clock disabled
  */
#define __HAL_RCC_GET_STGEN_SOURCE() ((uint32_t)(READ_BIT(RCC->STGENCKSELR, RCC_STGENCKSELR_STGENSRC)))

#if defined(RCC_PERIPHCLK_DCMIPP)
/** @brief macro to configure the DCMIPP clock (DCMIPPCLK).
  *
  * @param  __DCMIPPCLKSource__: specifies the DCMIPP clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_DCMIPPCLKSOURCE_ACLK:  ACLK Clock selected as DCMIPP clock (default after reset)
  *            @arg RCC_DCMIPPCLKSOURCE_PLL2:  PLL2 Clock selected as DCMIPP clock
  *            @arg RCC_DCMIPPCLKSOURCE_PLL4:  PLL4 Clock selected as DCMIPP clock
  *            @arg RCC_DCMIPPCLKSOURCE_PER:   PER Clock selected as DCMIPP clock
  *
  * @retval None
  */
#define __HAL_RCC_DCMIPP_CONFIG(__DCMIPPCLKSource__) \
  MODIFY_REG(RCC->DCMIPPCKSELR, RCC_DCMIPPCKSELR_DCMIPPSRC, (uint32_t)(__DCMIPPCLKSource__))

/** @brief  macro to get the DCMIPP clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_DCMIPPCLKSOURCE_ACLK:  ACLK Clock selected as DCMIPP clock (default after reset)
  *            @arg RCC_DCMIPPCLKSOURCE_PLL2:  PLL2 Clock selected as DCMIPP clock
  *            @arg RCC_DCMIPPCLKSOURCE_PLL4:  PLL4 Clock selected as DCMIPP clock
  *            @arg RCC_DCMIPPCLKSOURCE_PER:   PER Clock selected as DCMIPP clock
  */
#define __HAL_RCC_GET_DCMIPP_SOURCE() ((uint32_t)(READ_BIT(RCC->DCMIPPCKSELR, RCC_DCMIPPCKSELR_DCMIPPSRC)))
#endif /* RCC_PERIPHCLK_DCMIPP */

#if defined(RCC_PERIPHCLK_SAES)
/** @brief macro to configure the SAES clock (SAESCLK).
  *
  * @param  __SAESCLKSource__: specifies the SAES clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_SAESCLKSOURCE_ACLK:  ACLK Clock selected as SAES clock (default after reset)
  *            @arg RCC_SAESCLKSOURCE_PER:   PER Clock selected as SAES clock
  *            @arg RCC_SAESCLKSOURCE_PLL4:  PLL4 Clock selected as SAES clock
  *            @arg RCC_SAESCLKSOURCE_LSI:   LSI Clock selected as SAES clock
  *
  * @retval None
  */
#define __HAL_RCC_SAES_CONFIG(__SAESCLKSource__) \
  MODIFY_REG(RCC->SAESCKSELR, RCC_SAESCKSELR_SAESSRC, (uint32_t)(__SAESCLKSource__))

/** @brief  macro to get the SAES clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_SAESCLKSOURCE_ACLK:  ACLK Clock selected as SAES clock (default after reset)
  *            @arg RCC_SAESCLKSOURCE_PER:   PER Clock selected as SAES clock
  *            @arg RCC_SAESCLKSOURCE_PLL4:  PLL4 Clock selected as SAES clock
  *            @arg RCC_SAESCLKSOURCE_LSI:   LSI Clock selected as SAES clock
  */
#define __HAL_RCC_GET_SAES_SOURCE() ((uint32_t)(READ_BIT(RCC->SAESCKSELR, RCC_SAESCKSELR_SAESSRC)))
#endif /* RCC_PERIPHCLK_SAES */

/** @brief macro to configure the ADC1 clock (ADC1CLK).
  *
  * @param  __ADC1CLKSource__: specifies the ADC1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_ADC1CLKSOURCE_PLL4:    PLL4_R Clock selected as ADC1 clock (default after reset)
  *            @arg RCC_ADC1CLKSOURCE_PER:     PER Clock selected as ADC1 clock
  *            @arg RCC_ADC1CLKSOURCE_PLL3:    PLL3_Q Clock selected as ADC1 clock
  * @retval None
  */
#define __HAL_RCC_ADC1_CONFIG(__ADC1CLKSource__) \
  MODIFY_REG(RCC->ADC12CKSELR, RCC_ADC12CKSELR_ADC1SRC, (uint32_t)(__ADC1CLKSource__))

/** @brief  macro to get the ADC1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADC1CLKSOURCE_PLL4:    PLL4_R Clock selected as ADC1 clock (default after reset)
  *            @arg RCC_ADC1CLKSOURCE_PER:     PER Clock selected as ADC1 clock
  *            @arg RCC_ADC1CLKSOURCE_PLL3:    PLL3_Q Clock selected as ADC1 clock
  */
#define __HAL_RCC_GET_ADC1_SOURCE() ((uint32_t)(READ_BIT(RCC->ADC12CKSELR, RCC_ADC12CKSELR_ADC1SRC)))

/** @brief macro to configure the ADC2 clock (ADC2CLK).
  *
  * @param  __ADC2CLKSource__: specifies the ADC2 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_ADC2CLKSOURCE_PLL4:    PLL4_R Clock selected as ADC2 clock (default after reset)
  *            @arg RCC_ADC2CLKSOURCE_PER:     PER Clock selected as ADC2 clock
  *            @arg RCC_ADC2CLKSOURCE_PLL3:    PLL3_Q Clock selected as ADC2 clock
  * @retval None
  */
#define __HAL_RCC_ADC2_CONFIG(__ADC2CLKSource__) \
  MODIFY_REG(RCC->ADC12CKSELR, RCC_ADC12CKSELR_ADC2SRC, (uint32_t)(__ADC2CLKSource__))

/** @brief  macro to get the ADC2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_ADC2CLKSOURCE_PLL4:    PLL4_R Clock selected as ADC2 clock (default after reset)
  *            @arg RCC_ADC2CLKSOURCE_PER:     PER Clock selected as ADC2 clock
  *            @arg RCC_ADC2CLKSOURCE_PLL3:    PLL3_Q Clock selected as ADC2 clock
  */
#define __HAL_RCC_GET_ADC2_SOURCE() ((uint32_t)(READ_BIT(RCC->ADC12CKSELR, RCC_ADC12CKSELR_ADC2SRC)))

/** @brief macro to configure the LPTIM1 clock (LPTIM1CLK).
  *
  * @param  __LPTIM1CLKSource__: specifies the LPTIM1 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LPTIM1CLKSOURCE_PCLK1:   PCLK1 Clock selected as LPTIM1 clock (default after reset)
  *            @arg RCC_LPTIM1CLKSOURCE_PLL4:    PLL4_P Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_PLL3:    PLL3_Q Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_LSE:     LSE Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_LSI:     LSI Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_PER:     PER Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_OFF:     The kernel clock is disabled
  *
  * @retval None
  */
#define __HAL_RCC_LPTIM1_CONFIG(__LPTIM1CLKSource__) \
  MODIFY_REG(RCC->LPTIM1CKSELR, RCC_LPTIM1CKSELR_LPTIM1SRC, (uint32_t)(__LPTIM1CLKSource__))

/** @brief  macro to get the LPTIM1 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_LPTIM1CLKSOURCE_PCLK1:   PCLK1 Clock selected as LPTIM1 clock (default after reset)
  *            @arg RCC_LPTIM1CLKSOURCE_PLL4:    PLL4_P Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_PLL3:    PLL3_Q Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_LSE:     LSE Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_LSI:     LSI Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_PER:     PER Clock selected as LPTIM1 clock
  *            @arg RCC_LPTIM1CLKSOURCE_OFF:     The kernel clock is disabled
  */
#define __HAL_RCC_GET_LPTIM1_SOURCE() ((uint32_t)(READ_BIT(RCC->LPTIM1CKSELR, RCC_LPTIM1CKSELR_LPTIM1SRC)))

#if defined(RCC_LPTIM23CKSELR_LPTIM23SRC)
/** @brief macro to configure the LPTIM23 clock (LPTIM23CLK).
  *
  * @param  __LPTIM23CLKSource__: specifies the LPTIM23 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LPTIM23CLKSOURCE_PCLK3:   PCLK3 Clock selected as LPTIM23 clock (default after reset)
  *            @arg RCC_LPTIM23CLKSOURCE_PLL4:    PLL4_Q Clock selected as LPTIM23 clock
  *            @arg RCC_LPTIM23CLKSOURCE_PER:     PER Clock selected as LPTIM23 clock
  *            @arg RCC_LPTIM23CLKSOURCE_LSE:     LSE Clock selected as LPTIM23 clock
  *            @arg RCC_LPTIM23CLKSOURCE_LSI:     LSI Clock selected as LPTIM23 clock
  *            @arg RCC_LPTIM23CLKSOURCE_OFF:     The kernel clock is disabled
  * @retval None
  */
#define __HAL_RCC_LPTIM23_CONFIG(__LPTIM23CLKSource__) \
  MODIFY_REG(RCC->LPTIM23CKSELR, RCC_LPTIM23CKSELR_LPTIM23SRC, (uint32_t)(__LPTIM23CLKSource__))

/** @brief  macro to get the LPTIM23 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_LPTIM23CLKSOURCE_PCLK3:   PCLK3 Clock selected as LPTIM23 clock (default after reset)
  *            @arg RCC_LPTIM23CLKSOURCE_PLL4:    PLL4_Q Clock selected as LPTIM23 clock
  *            @arg RCC_LPTIM23CLKSOURCE_PER:     PER Clock selected as LPTIM23 clock
  *            @arg RCC_LPTIM23CLKSOURCE_LSE:     LSE Clock selected as LPTIM23 clock
  *            @arg RCC_LPTIM23CLKSOURCE_LSI:     LSI Clock selected as LPTIM23 clock
  *            @arg RCC_LPTIM23CLKSOURCE_OFF:     The kernel clock is disabled
  */
#define __HAL_RCC_GET_LPTIM23_SOURCE() ((uint32_t)(READ_BIT(RCC->LPTIM23CKSELR, RCC_LPTIM23CKSELR_LPTIM23SRC)))
#endif /* RCC_LPTIM23CKSELR_LPTIM23SRC */

#if defined(RCC_LPTIM23CKSELR_LPTIM2SRC)
/** @brief macro to configure the LPTIM2 clock (LPTIM2CLK).
  *
  * @param  __LPTIM2CLKSource__: specifies the LPTIM2 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LPTIM2CLKSOURCE_PCLK3:   PCLK3 Clock selected as LPTIM2 clock (default after reset)
  *            @arg RCC_LPTIM2CLKSOURCE_PLL4:    PLL4_Q Clock selected as LPTIM2 clock
  *            @arg RCC_LPTIM2CLKSOURCE_PER:     PER Clock selected as LPTIM2 clock
  *            @arg RCC_LPTIM2CLKSOURCE_LSE:     LSE Clock selected as LPTIM2 clock
  *            @arg RCC_LPTIM2CLKSOURCE_LSI:     LSI Clock selected as LPTIM2 clock
  *            @arg RCC_LPTIM2CLKSOURCE_OFF:     The kernel clock is disabled
  * @retval None
  */
#define __HAL_RCC_LPTIM2_CONFIG(__LPTIM2CLKSource__) \
  MODIFY_REG(RCC->LPTIM23CKSELR, RCC_LPTIM23CKSELR_LPTIM2SRC, (uint32_t)(__LPTIM2CLKSource__))

/** @brief  macro to get the LPTIM2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_LPTIM2CLKSOURCE_PCLK3:   PCLK3 Clock selected as LPTIM2 clock (default after reset)
  *            @arg RCC_LPTIM2CLKSOURCE_PLL4:    PLL4_Q Clock selected as LPTIM2 clock
  *            @arg RCC_LPTIM2CLKSOURCE_PER:     PER Clock selected as LPTIM2 clock
  *            @arg RCC_LPTIM2CLKSOURCE_LSE:     LSE Clock selected as LPTIM2 clock
  *            @arg RCC_LPTIM2CLKSOURCE_LSI:     LSI Clock selected as LPTIM2 clock
  *            @arg RCC_LPTIM2CLKSOURCE_OFF:     The kernel clock is disabled
  */
#define __HAL_RCC_GET_LPTIM2_SOURCE() ((uint32_t)(READ_BIT(RCC->LPTIM23CKSELR, RCC_LPTIM23CKSELR_LPTIM2SRC)))
#endif /* RCC_LPTIM23CKSELR_LPTIM2SRC */

#if defined(RCC_LPTIM23CKSELR_LPTIM3SRC)
/** @brief macro to configure the LPTIM3 clock (LPTIM3CLK).
  *
  * @param  __LPTIM3CLKSource__: specifies the LPTIM3 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LPTIM3CLKSOURCE_PCLK3:   PCLK3 Clock selected as LPTIM3 clock (default after reset)
  *            @arg RCC_LPTIM3CLKSOURCE_PLL4:    PLL4_Q Clock selected as LPTIM3 clock
  *            @arg RCC_LPTIM3CLKSOURCE_PER:     PER Clock selected as LPTIM3 clock
  *            @arg RCC_LPTIM3CLKSOURCE_LSE:     LSE Clock selected as LPTIM3 clock
  *            @arg RCC_LPTIM3CLKSOURCE_LSI:     LSI Clock selected as LPTIM3 clock
  *            @arg RCC_LPTIM3CLKSOURCE_OFF:     The kernel clock is disabled
  * @retval None
  */
#define __HAL_RCC_LPTIM3_CONFIG(__LPTIM3CLKSource__) \
  MODIFY_REG(RCC->LPTIM23CKSELR, RCC_LPTIM23CKSELR_LPTIM3SRC, (uint32_t)(__LPTIM3CLKSource__))

/** @brief  macro to get the LPTIM3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_LPTIM3CLKSOURCE_PCLK3:   PCLK3 Clock selected as LPTIM3 clock (default after reset)
  *            @arg RCC_LPTIM3CLKSOURCE_PLL4:    PLL4_Q Clock selected as LPTIM3 clock
  *            @arg RCC_LPTIM3CLKSOURCE_PER:     PER Clock selected as LPTIM3 clock
  *            @arg RCC_LPTIM3CLKSOURCE_LSE:     LSE Clock selected as LPTIM3 clock
  *            @arg RCC_LPTIM3CLKSOURCE_LSI:     LSI Clock selected as LPTIM3 clock
  *            @arg RCC_LPTIM3CLKSOURCE_OFF:     The kernel clock is disabled
  */
#define __HAL_RCC_GET_LPTIM3_SOURCE() ((uint32_t)(READ_BIT(RCC->LPTIM23CKSELR, RCC_LPTIM23CKSELR_LPTIM3SRC)))
#endif /* RCC_LPTIM23CKSELR_LPTIM3SRC */

/** @brief macro to configure the LPTIM45 clock (LPTIM45CLK).
  *
  * @param  __LPTIM45CLKSource__: specifies the LPTIM45 clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LPTIM45CLKSOURCE_PCLK3:   PCLK3 Clock selected as LPTIM45 clock (default after reset)
  *            @arg RCC_LPTIM45CLKSOURCE_PLL4:    PLL4_P Clock selected as LPTIM45 clock
  *            @arg RCC_LPTIM45CLKSOURCE_PLL3:    PLL3_Q Clock selected as LPTIM45 clock
  *            @arg RCC_LPTIM45CLKSOURCE_LSE:     LSE Clock selected as LPTIM45 clock
  *            @arg RCC_LPTIM45CLKSOURCE_LSI:     LSI Clock selected as LPTIM45 clock
  *            @arg RCC_LPTIM45CLKSOURCE_PER:     PER Clock selected as LPTIM45 clock
  *            @arg RCC_LPTIM45CLKSOURCE_OFF:     The kernel clock is disabled
  * @retval None
  */
#define __HAL_RCC_LPTIM45_CONFIG(__LPTIM45CLKSource__) \
  MODIFY_REG(RCC->LPTIM45CKSELR, RCC_LPTIM45CKSELR_LPTIM45SRC, (uint32_t)(__LPTIM45CLKSource__))

/** @brief  macro to get the LPTIM45 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_LPTIM45CLKSOURCE_PCLK3:   PCLK3 Clock selected as LPTIM45 clock (default after reset)
  *            @arg RCC_LPTIM45CLKSOURCE_PLL4:    PLL4_P Clock selected as LPTIM45 clock
  *            @arg RCC_LPTIM45CLKSOURCE_PLL3:    PLL3_Q Clock selected as LPTIM45 clock
  *            @arg RCC_LPTIM45CLKSOURCE_LSE:     LSE Clock selected as LPTIM45 clock
  *            @arg RCC_LPTIM45CLKSOURCE_LSI:     LSI Clock selected as LPTIM45 clock
  *            @arg RCC_LPTIM45CLKSOURCE_PER:     PER Clock selected as LPTIM45 clock
  *            @arg RCC_LPTIM45CLKSOURCE_OFF:     The kernel clock is disabled
  */
#define __HAL_RCC_GET_LPTIM45_SOURCE() ((uint32_t)(READ_BIT(RCC->LPTIM45CKSELR, RCC_LPTIM45CKSELR_LPTIM45SRC)))



/**
  * @brief  Macro to set the APB1 timer clock prescaler
  * @note   Set and reset by software to control the clock frequency of all the timers connected to APB1 domain.
  *         It concerns TIM2, TIM3, TIM4, TIM5, TIM6, TIM7, TIM12, TIM13 and TIM14.
  * @param  __RCC_TIMG1PRES__: specifies the Timers clocks prescaler selection
  *          This parameter can be one of the following values:
  *              @arg RCC_TIMG1PRES_DEACTIVATED:  The Timers kernel clock is equal to ck_hclk
  *                                               if APB1DIV is corresponding
  *                                               to a division by 1 or 2, else it is equal to
  *                                               2 x Fck_pclk1 (default after reset)
  *              @arg RCC_TIMG1PRES_ACTIVATED:    The Timers kernel clock is equal to ck_hclk
  *                                               if APB1DIV is corresponding
  *                                               to division by 1, 2 or 4, else it is equal to 4 x Fck_pclk1
  */
#define __HAL_RCC_TIMG1PRES(__RCC_TIMG1PRES__) \
  do{  MODIFY_REG( RCC->TIMG1PRER, RCC_TIMG1PRER_TIMG1PRE , __RCC_TIMG1PRES__ );\
  } while(0)

/** @brief  Macro to get the APB1 timer clock prescaler.
  * @retval The APB1 timer clock prescaler. The returned value can be one
  *         of the following:
  *             - RCC_TIMG1PRES_DEACTIVATED: The Timers kernel clock is equal to ck_hclk if APB1DIV is corresponding
  *                                           to a division by 1 or 2, else it is equal to 2 x Fck_pclk1
  *                                           (default after reset)
  *             - RCC_TIMG1PRES_ACTIVATED:   The Timers kernel clock is equal to ck_hclk if APB1DIV is corresponding
  *                                          to division by 1, 2 or 4, else it is equal to 4 x Fck_pclk1
  */
#define __HAL_RCC_GET_TIMG1PRES() ((uint32_t)(RCC->TIMG1PRER & RCC_TIMG1PRER_TIMG1PRE))

/**
  * @brief  Macro to set the APB2 timers clocks prescaler
  * @note   Set and reset by software to control the clock frequency of all the timers connected to APB2 domain.
  *         It concerns TIM1, TIM8, TIM15, TIM16, and TIM17.
  * @param  __RCC_TIMG2PRES__: specifies the timers clocks prescaler selection
  *          This parameter can be one of the following values:
  *              @arg RCC_TIMG2PRES_DEACTIVATED:  The Timers kernel clock is equal to ck_hclk if
  *                                               APB2DIV is corresponding to a division by 1 or 2, else
  *                                               it is equal to 2 x Fck_pclk2 (default after reset)
  *              @arg RCC_TIMG2PRES_ACTIVATED:    The Timers kernel clock is equal to ck_hclk if APB2DIV is
  *                                               correspondingto division by 1, 2 or 4, else
  *                                               it is equal to 4 x Fck_pclk1
  */
#define __HAL_RCC_TIMG2PRES(__RCC_TIMG2PRES__) \
  do{  MODIFY_REG( RCC->TIMG2PRER, RCC_TIMG2PRER_TIMG2PRE , __RCC_TIMG2PRES__ );\
  } while(0)

/** @brief  Macro to get the APB2 timer clock prescaler.
  * @retval The APB2 timer clock prescaler. The returned value can be one
  *         of the following:
  *             - RCC_TIMG2PRES_DEACTIVATED: The Timers kernel clock is equal to ck_hclk if APB2DIV is corresponding
  *                                           to a division by 1 or 2, else it is equal to
  *                                           2 x Fck_pclk1 (default after reset)
  *             - RCC_TIMG2PRES_ACTIVATED:   The Timers kernel clock is equal to ck_hclk if APB2DIV is corresponding
  *                                          to division by 1, 2 or 4, else it is equal to 4 x Fck_pclk1
  */
#define __HAL_RCC_GET_TIMG2PRES() ((uint32_t)(RCC->TIMG2PRER & RCC_TIMG2PRER_TIMG2PRE))



#define USB_PHY_VALUE    ((uint32_t)48000000U) /*!< Value of the USB_PHY_VALUE signal in Hz
                                                   It is equal to rcc_hsphy_CLK_48M which is
                                                   a constant value */
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Functions RCCEx Exported Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
  * @{
  */

uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint64_t PeriphClk);
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(const RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
HAL_StatusTypeDef RCCEx_PLL2_Config(const RCC_PLLInitTypeDef *pll2);
HAL_StatusTypeDef RCCEx_PLL3_Config(const RCC_PLLInitTypeDef *pll3);
HAL_StatusTypeDef RCCEx_PLL4_Config(const RCC_PLLInitTypeDef *pll4);

/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */

void HAL_RCCEx_EnableLSECSS(void);
void HAL_RCCEx_DisableLSECSS(void);

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

#endif /* __STM32MP13xx_HAL_RCC_EX_H */
