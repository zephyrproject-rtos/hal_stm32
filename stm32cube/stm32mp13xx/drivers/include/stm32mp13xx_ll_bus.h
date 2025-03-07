/**
  ******************************************************************************
  * @file    stm32mp13xx_ll_bus.h
  * @author  MCD Application Team
  * @version $VERSION$
  * @date    $DATE$
  * @brief   Header file of BUS LL module.

  @verbatim
                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling should be taken into account in order to manage the peripheral read/write
      from/to registers.
      (+) This delay depends on the peripheral mapping.
        (++) AHB & APB peripherals, 1 dummy read is necessary

    [..]
      Workarounds:
      (#) For AHB & APB peripherals, a dummy read to the peripheral register has been
          inserted in each LL_{BUS}_GRP{x}_EnableClock() function.

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
#ifndef STM32MP13xx_LL_BUS_H
#define STM32MP13xx_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx.h"

/** @addtogroup STM32MP13xx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup BUS_LL BUS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Constants BUS Exported Constants
  * @{
  */

/** @defgroup BUS_LL_EC_AHB2_GRP1_PERIPH  AHB2 GRP1 PERIPH
  * @{
  */
#define LL_AHB2_GRP1_PERIPH_ALL            0x0001017FU
#define LL_AHB2_GRP1_PERIPH_DMA1           RCC_MP_AHB2ENSETR_DMA1EN
#define LL_AHB2_GRP1_PERIPH_DMA2           RCC_MP_AHB2ENSETR_DMA2EN
#define LL_AHB2_GRP1_PERIPH_DMAMUX1        RCC_MP_AHB2ENSETR_DMAMUX1EN
#define LL_AHB2_GRP1_PERIPH_DMA3           RCC_MP_AHB2ENSETR_DMA3EN
#define LL_AHB2_GRP1_PERIPH_DMAMUX2        RCC_MP_AHB2ENSETR_DMAMUX2EN
#define LL_AHB2_GRP1_PERIPH_ADC1           RCC_MP_AHB2ENSETR_ADC1EN
#define LL_AHB2_GRP1_PERIPH_ADC2           RCC_MP_AHB2ENSETR_ADC2EN
#define LL_AHB2_GRP1_PERIPH_USBO           RCC_MP_AHB2ENSETR_USBOEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB4_GRP1_PERIPH  AHB4 GRP1 PERIPH
  * @{
  */
#define LL_AHB4_GRP1_PERIPH_ALL            0x000000FFU
#define LL_AHB4_GRP1_PERIPH_GPIOA          RCC_AHB4RSTSETR_GPIOARST
#define LL_AHB4_GRP1_PERIPH_GPIOB          RCC_AHB4RSTSETR_GPIOBRST
#define LL_AHB4_GRP1_PERIPH_GPIOC          RCC_AHB4RSTSETR_GPIOCRST
#define LL_AHB4_GRP1_PERIPH_GPIOD          RCC_AHB4RSTSETR_GPIODRST
#define LL_AHB4_GRP1_PERIPH_GPIOE          RCC_AHB4RSTSETR_GPIOERST
#define LL_AHB4_GRP1_PERIPH_GPIOF          RCC_AHB4RSTSETR_GPIOFRST
#define LL_AHB4_GRP1_PERIPH_GPIOG          RCC_AHB4RSTSETR_GPIOGRST
#define LL_AHB4_GRP1_PERIPH_GPIOH          RCC_AHB4RSTSETR_GPIOHRST
#define LL_AHB4_GRP1_PERIPH_GPIOI          RCC_AHB4RSTSETR_GPIOIRST
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB4_S_GRP1_PERIPH  AHB4_S GRP1 PERIPH
  * @{
  */
#define LL_AHB4_S_GRP1_PERIPH_ALL          0x000000FFU
#define LL_AHB4_S_GRP1_PERIPH_GPIOA        RCC_MP_S_AHB4ENSETR_GPIOAEN
#define LL_AHB4_S_GRP1_PERIPH_GPIOB        RCC_MP_S_AHB4ENSETR_GPIOBEN
#define LL_AHB4_S_GRP1_PERIPH_GPIOC        RCC_MP_S_AHB4ENSETR_GPIOCEN
#define LL_AHB4_S_GRP1_PERIPH_GPIOD        RCC_MP_S_AHB4ENSETR_GPIODEN
#define LL_AHB4_S_GRP1_PERIPH_GPIOE        RCC_MP_S_AHB4ENSETR_GPIOEEN
#define LL_AHB4_S_GRP1_PERIPH_GPIOF        RCC_MP_S_AHB4ENSETR_GPIOFEN
#define LL_AHB4_S_GRP1_PERIPH_GPIOG        RCC_MP_S_AHB4ENSETR_GPIOGEN
#define LL_AHB4_S_GRP1_PERIPH_GPIOH        RCC_MP_S_AHB4ENSETR_GPIOHEN
#define LL_AHB4_S_GRP1_PERIPH_GPIOI        RCC_MP_S_AHB4ENSETR_GPIOIEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB4_NS_GRP1_PERIPH  AHB4_NS GRP1 PERIPH
  * @{
  */
#define LL_AHB4_NS_GRP1_PERIPH_ALL         0x000000FFU
#define LL_AHB4_NS_GRP1_PERIPH_GPIOA       RCC_MP_NS_AHB4ENSETR_GPIOAEN
#define LL_AHB4_NS_GRP1_PERIPH_GPIOB       RCC_MP_NS_AHB4ENSETR_GPIOBEN
#define LL_AHB4_NS_GRP1_PERIPH_GPIOC       RCC_MP_NS_AHB4ENSETR_GPIOCEN
#define LL_AHB4_NS_GRP1_PERIPH_GPIOD       RCC_MP_NS_AHB4ENSETR_GPIODEN
#define LL_AHB4_NS_GRP1_PERIPH_GPIOE       RCC_MP_NS_AHB4ENSETR_GPIOEEN
#define LL_AHB4_NS_GRP1_PERIPH_GPIOF       RCC_MP_NS_AHB4ENSETR_GPIOFEN
#define LL_AHB4_NS_GRP1_PERIPH_GPIOG       RCC_MP_NS_AHB4ENSETR_GPIOGEN
#define LL_AHB4_NS_GRP1_PERIPH_GPIOH       RCC_MP_NS_AHB4ENSETR_GPIOHEN
#define LL_AHB4_NS_GRP1_PERIPH_GPIOI       RCC_MP_NS_AHB4ENSETR_GPIOIEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB5_GRP1_PERIPH  AHB5 GRP1 PERIPH
  * @{
  */
/**
  * @note LL_AHB5_GRP1_PERIPH_ALL only contains reset values (not enable)
  */
#define LL_AHB5_GRP1_PERIPH_ALL            0x0001007CU
#define LL_AHB5_GRP1_PERIPH_PKA            RCC_MP_AHB5ENSETR_PKAEN
#define LL_AHB5_GRP1_PERIPH_SAES           RCC_MP_AHB5ENSETR_SAESEN
#define LL_AHB5_GRP1_PERIPH_CRYP1          RCC_MP_AHB5ENSETR_CRYP1EN
#define LL_AHB5_GRP1_PERIPH_HASH1          RCC_MP_AHB5ENSETR_HASH1EN
#define LL_AHB5_GRP1_PERIPH_RNG1           RCC_MP_AHB5ENSETR_RNG1EN
#define LL_AHB5_GRP1_PERIPH_BKPSRAM        RCC_MP_AHB5ENSETR_BKPSRAMEN
#define LL_AHB5_GRP1_PERIPH_AXIMC          RCC_MP_AHB5ENSETR_AXIMCEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB6_GRP1_PERIPH  AHB6 GRP1 PERIPH
  * @{
  */
#define LL_AHB6_GRP1_PERIPH_ALL            0xF9135F82U
#define LL_AHB6_GRP1_PERIPH_MCE            RCC_MP_AHB6ENSETR_MCEEN
#define LL_AHB6_GRP1_PERIPH_ETH1CK         RCC_MP_AHB6ENSETR_ETH1CKEN
#define LL_AHB6_GRP1_PERIPH_ETH1TX         RCC_MP_AHB6ENSETR_ETH1TXEN
#define LL_AHB6_GRP1_PERIPH_ETH1RX         RCC_MP_AHB6ENSETR_ETH1RXEN
#define LL_AHB6_GRP1_PERIPH_ETH1MAC        RCC_MP_AHB6ENSETR_ETH1MACEN
#define LL_AHB6_GRP1_PERIPH_ETH1STP        RCC_MP_AHB6LPENSETR_ETH1STPEN
#define LL_AHB6_GRP1_PERIPH_FMC            RCC_MP_AHB6ENSETR_FMCEN
#define LL_AHB6_GRP1_PERIPH_QSPI           RCC_MP_AHB6ENSETR_QSPIEN
#define LL_AHB6_GRP1_PERIPH_SDMMC1         RCC_MP_AHB6ENSETR_SDMMC1EN
#define LL_AHB6_GRP1_PERIPH_SDMMC2         RCC_MP_AHB6ENSETR_SDMMC2EN
#define LL_AHB6_GRP1_PERIPH_CRC1           RCC_MP_AHB6ENSETR_CRC1EN
#define LL_AHB6_GRP1_PERIPH_USBH           RCC_MP_AHB6ENSETR_USBHEN
#define LL_AHB6_GRP1_PERIPH_ETH2CK         RCC_MP_AHB6ENSETR_ETH2CKEN
#define LL_AHB6_GRP1_PERIPH_ETH2TX         RCC_MP_AHB6ENSETR_ETH2TXEN
#define LL_AHB6_GRP1_PERIPH_ETH2RX         RCC_MP_AHB6ENSETR_ETH2RXEN
#define LL_AHB6_GRP1_PERIPH_ETH2MAC        RCC_MP_AHB6ENSETR_ETH2MACEN
#define LL_AHB6_GRP1_PERIPH_ETH2STP        RCC_MP_AHB6LPENSETR_ETH2STPEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB6_S_GRP1_PERIPH  AHB6_S GRP1 PERIPH
  * @{
  */

#define LL_AHB6_S_GRP1_PERIPH_MDMA         RCC_MP_S_AHB6ENSETR_MDMAEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB6_NS_GRP1_PERIPH  AHB6_NS GRP1 PERIPH
  * @{
  */

#define LL_AHB6_NS_GRP1_PERIPH_MDMA        RCC_MP_S_AHB6ENSETR_MDMAEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_AXI_GRP1_PERIPH  AXI GRP1 PERIPH
  * @{
  */
#define LL_AXI_GRP1_PERIPH_ALL             0x00000001U
#define LL_AXI_S_GRP1_PERIPH_SYSRAMLPEN    RCC_MP_S_AXIMLPENSETR_SYSRAMLPEN
#define LL_AXI_NS_GRP1_PERIPH_SYSRAMLPEN   RCC_MP_NS_AXIMLPENSETR_SYSRAMLPEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_MLAHB_GRP1_PERIPH  MLAHB GRP1 PERIPH
  * @{
  */
#define LL_MLAHB_GRP1_PERIPH_ALL           0x00000010U
#define LL_MLAHB_GRP1_PERIPH_SRAM1LPEN     RCC_MP_MLAHBLPENSETR_SRAM1LPEN
#define LL_MLAHB_GRP1_PERIPH_SRAM2LPEN     RCC_MP_MLAHBLPENSETR_SRAM2LPEN
#define LL_MLAHB_GRP1_PERIPH_SRAM3LPEN     RCC_MP_MLAHBLPENSETR_SRAM3LPEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_ALL            0x046F9A3FU
#define LL_APB1_GRP1_PERIPH_TIM2           RCC_MP_APB1ENSETR_TIM2EN
#define LL_APB1_GRP1_PERIPH_TIM3           RCC_MP_APB1ENSETR_TIM3EN
#define LL_APB1_GRP1_PERIPH_TIM4           RCC_MP_APB1ENSETR_TIM4EN
#define LL_APB1_GRP1_PERIPH_TIM5           RCC_MP_APB1ENSETR_TIM5EN
#define LL_APB1_GRP1_PERIPH_TIM6           RCC_MP_APB1ENSETR_TIM6EN
#define LL_APB1_GRP1_PERIPH_TIM7           RCC_MP_APB1ENSETR_TIM7EN
#define LL_APB1_GRP1_PERIPH_LPTIM1         RCC_MP_APB1ENSETR_LPTIM1EN
#define LL_APB1_GRP1_PERIPH_SPI2           RCC_MP_APB1ENSETR_SPI2EN
#define LL_APB1_GRP1_PERIPH_SPI3           RCC_MP_APB1ENSETR_SPI3EN
#define LL_APB1_GRP1_PERIPH_USART3         RCC_MP_APB1ENSETR_USART3EN
#define LL_APB1_GRP1_PERIPH_UART4          RCC_MP_APB1ENSETR_UART4EN
#define LL_APB1_GRP1_PERIPH_UART5          RCC_MP_APB1ENSETR_UART5EN
#define LL_APB1_GRP1_PERIPH_UART7          RCC_MP_APB1ENSETR_UART7EN
#define LL_APB1_GRP1_PERIPH_UART8          RCC_MP_APB1ENSETR_UART8EN
#define LL_APB1_GRP1_PERIPH_I2C1           RCC_MP_APB1ENSETR_I2C1EN
#define LL_APB1_GRP1_PERIPH_I2C2           RCC_MP_APB1ENSETR_I2C2EN
#define LL_APB1_GRP1_PERIPH_SPDIF          RCC_MP_APB1ENSETR_SPDIFEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB2_GRP1_PERIPH  APB2 GRP1 PERIPH
  * @{
  */
/**
  * @note LL_APB2_GRP1_PERIPH_ALL only contains reset values (not enable)
  */
#define LL_APB2_GRP1_PERIPH_ALL            0x01132103U
#define LL_APB2_GRP1_PERIPH_TIM1           RCC_MP_APB2ENSETR_TIM1EN
#define LL_APB2_GRP1_PERIPH_TIM8           RCC_MP_APB2ENSETR_TIM8EN
#define LL_APB2_GRP1_PERIPH_SPI1           RCC_MP_APB2ENSETR_SPI1EN
#define LL_APB2_GRP1_PERIPH_USART6         RCC_MP_APB2ENSETR_USART6EN
#define LL_APB2_GRP1_PERIPH_SAI1           RCC_MP_APB2ENSETR_SAI1EN
#define LL_APB2_GRP1_PERIPH_SAI2           RCC_MP_APB2ENSETR_SAI2EN
#define LL_APB2_GRP1_PERIPH_DFSDM1         RCC_MP_APB2ENSETR_DFSDMEN
#define LL_APB2_GRP1_PERIPH_ADFSDM1        RCC_MP_APB2ENSETR_ADFSDMEN
#define LL_APB2_GRP1_PERIPH_FDCAN          RCC_MP_APB2ENSETR_FDCANEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB3_GRP1_PERIPH  APB3 GRP1 PERIPH
  * @{
  */
/**
  * @note LL_APB3_GRP1_PERIPH_ALL only contains reset values (not enable)
  */
#define LL_APB3_GRP1_PERIPH_ALL            0x0001280FU
#define LL_APB3_GRP1_PERIPH_LPTIM2         RCC_MP_APB3ENSETR_LPTIM2EN
#define LL_APB3_GRP1_PERIPH_LPTIM3         RCC_MP_APB3ENSETR_LPTIM3EN
#define LL_APB3_GRP1_PERIPH_LPTIM4         RCC_MP_APB3ENSETR_LPTIM4EN
#define LL_APB3_GRP1_PERIPH_LPTIM5         RCC_MP_APB3ENSETR_LPTIM5EN
#define LL_APB3_GRP1_PERIPH_SYSCFG         RCC_APB3RSTCLRR_SYSCFGRST
#define LL_APB3_GRP1_PERIPH_VREF           RCC_MP_APB3ENSETR_VREFEN
#define LL_APB3_GRP1_PERIPH_TMPSENS        RCC_MP_APB3ENSETR_DTSEN
#define LL_APB3_GRP1_PERIPH_HDP            RCC_MP_APB3ENSETR_HDPEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB3_S_GRP1_PERIPH  APB3_S GRP1 PERIPH
  * @{
  */
/**
  * @note LL_APB3_S_GRP1_PERIPH_ALL only contains reset values (not enable)
  */
#define LL_APB3_S_GRP1_PERIPH_ALL          0x00000001U
#define LL_APB3_S_GRP1_PERIPH_SYSCFG       RCC_MP_S_APB3ENSETR_SYSCFGEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB3_NS_GRP1_PERIPH  APB3_NS GRP1 PERIPH
  * @{
  */
/**
  * @note LL_APB3_NS_GRP1_PERIPH_ALL only contains reset values (not enable)
  */
#define LL_APB3_NS_GRP1_PERIPH_ALL         0x00000001U
#define LL_APB3_NS_GRP1_PERIPH_SYSCFG      RCC_MP_NS_APB3ENSETR_SYSCFGEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB4_GRP1_PERIPH  APB4 GRP1 PERIPH
  * @{
  */
/**
  * @note LL_APB4_GRP1_PERIPH_ALL only contains reset values (not enable)
  */
#define LL_APB4_GRP1_PERIPH_ALL            0x00010103U
#define LL_APB4_GRP1_PERIPH_DCMIPP         RCC_MP_APB4ENSETR_DCMIPPEN
#define LL_APB4_GRP1_PERIPH_DDRPERFM       RCC_MP_APB4ENSETR_DDRPERFMEN
#define LL_APB4_GRP1_PERIPH_IWDG2          RCC_MP_APB4ENSETR_IWDG2APBEN
#define LL_APB4_GRP1_PERIPH_USBPHY         RCC_MP_APB4ENSETR_USBPHYEN
#define LL_APB4_GRP1_PERIPH_STGENRO        RCC_MP_APB4ENSETR_STGENROEN
#define LL_APB4_GRP1_PERIPH_STGENROSTP     RCC_MP_APB4LPENSETR_STGENROSTPEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB4_S_GRP1_PERIPH  APB4_S GRP1 PERIPH
  * @{
  */
/**
  * @note LL_APB4_S_GRP1_PERIPH_ALL only contains reset values (not enable)
  */
#define LL_APB4_S_GRP1_PERIPH_ALL          0x00000001U
#define LL_APB4_S_GRP1_PERIPH_LTDC         RCC_MP_S_APB4ENSETR_LTDCEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB4_NS_GRP1_PERIPH  APB4_NS GRP1 PERIPH
  * @{
  */
/**
  * @note LL_APB4_NS_GRP1_PERIPH_ALL only contains reset values (not enable)
  */
#define LL_APB4_NS_GRP1_PERIPH_ALL         0x00000001U
#define LL_APB4_NS_GRP1_PERIPH_LTDC        RCC_MP_NS_APB4ENSETR_LTDCEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB5_GRP1_PERIPH  APB5 GRP1 PERIPH
  * @{
  */
/**
  * @note LL_APB5_GRP1_PERIPH_ALL only contains reset values (not enable)
  */
#define LL_APB5_GRP1_PERIPH_ALL            0x0031A900U
#define LL_APB5_GRP1_PERIPH_RTCAPB         RCC_MP_APB5ENSETR_RTCAPBEN
#define LL_APB5_GRP1_PERIPH_TZC            RCC_MP_APB5ENSETR_TZCEN
#define LL_APB5_GRP1_PERIPH_ETZPC          RCC_MP_APB5ENSETR_ETZPCEN
#define LL_APB5_GRP1_PERIPH_IWDG1          RCC_MP_APB5ENSETR_IWDG1APBEN
#define LL_APB5_GRP1_PERIPH_BSEC           RCC_MP_APB5ENSETR_BSECEN
#define LL_APB5_GRP1_PERIPH_STGEN          RCC_MP_APB5ENSETR_STGENCEN
#define LL_APB5_GRP1_PERIPH_STGENSTP       RCC_MP_APB5LPENSETR_STGENCSTPEN
/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB6_GRP1_PERIPH  APB6 GRP1 PERIPH
  * @{
  */
/**
  * @note LL_APB6_GRP1_PERIPH_ALL only contains reset values (not enable)
  */
#define LL_APB6_GRP1_PERIPH_ALL            0x00001FFFU
#define LL_APB6_GRP1_PERIPH_USART1         RCC_MP_APB6ENSETR_USART1EN
#define LL_APB6_GRP1_PERIPH_USART2         RCC_MP_APB6ENSETR_USART2EN
#define LL_APB6_GRP1_PERIPH_SPI4           RCC_MP_APB6ENSETR_SPI4EN
#define LL_APB6_GRP1_PERIPH_SPI5           RCC_MP_APB6ENSETR_SPI5EN
#define LL_APB6_GRP1_PERIPH_I2C3           RCC_MP_APB6ENSETR_I2C3EN
#define LL_APB6_GRP1_PERIPH_I2C4           RCC_MP_APB6ENSETR_I2C4EN
#define LL_APB6_GRP1_PERIPH_I2C5           RCC_MP_APB6ENSETR_I2C5EN
#define LL_APB6_GRP1_PERIPH_TIM12          RCC_MP_APB6ENSETR_TIM12EN
#define LL_APB6_GRP1_PERIPH_TIM13          RCC_MP_APB6ENSETR_TIM13EN
#define LL_APB6_GRP1_PERIPH_TIM14          RCC_MP_APB6ENSETR_TIM14EN
#define LL_APB6_GRP1_PERIPH_TIM15          RCC_MP_APB6ENSETR_TIM15EN
#define LL_APB6_GRP1_PERIPH_TIM16          RCC_MP_APB6ENSETR_TIM16EN
#define LL_APB6_GRP1_PERIPH_TIM17          RCC_MP_APB6ENSETR_TIM17EN
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Functions BUS Exported Functions
  * @{
  */

/** @defgroup BUS_LL_EF_AHB2 AHB2
  * @{
  */

/**
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll MP_AHB2ENSETR      DMA1          LL_AHB2_GRP1_EnableClock\n
  *         MP_AHB2ENSETR      DMA2          LL_AHB2_GRP1_EnableClock\n
  *         MP_AHB2ENSETR      DMAMUX1       LL_AHB2_GRP1_EnableClock\n
  *         MP_AHB2ENSETR      DMA3          LL_AHB2_GRP1_EnableClock\n
  *         MP_AHB2ENSETR      DMAMUX2       LL_AHB2_GRP1_EnableClock\n
  *         MP_AHB2ENSETR      ADC1          LL_AHB2_GRP1_EnableClock\n
  *         MP_AHB2ENSETR      ADC2          LL_AHB2_GRP1_EnableClock\n
  *         MP_AHB2ENSETR      USBO          LL_AHB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA3
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBO
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_AHB2ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_AHB2ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clock is enabled or not
  * @rmtoll MP_AHB2ENSETR      DMA1          LL_AHB2_GRP1_IsEnabledClock\n
  *         MP_AHB2ENSETR      DMA2          LL_AHB2_GRP1_IsEnabledClock\n
  *         MP_AHB2ENSETR      DMAMUX1       LL_AHB2_GRP1_IsEnabledClock\n
  *         MP_AHB2ENSETR      DMA3          LL_AHB2_GRP1_IsEnabledClock\n
  *         MP_AHB2ENSETR      DMAMUX2       LL_AHB2_GRP1_IsEnabledClock\n
  *         MP_AHB2ENSETR      ADC1          LL_AHB2_GRP1_IsEnabledClock\n
  *         MP_AHB2ENSETR      ADC2          LL_AHB2_GRP1_IsEnabledClock\n
  *         MP_AHB2ENSETR      USBO          LL_AHB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA3
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBO
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_AHB2ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable AHB2 peripherals clock.
  * @rmtoll MP_AHB2ENCLRR      DMA1          LL_AHB2_GRP1_DisableClock\n
  *         MP_AHB2ENCLRR      DMA2          LL_AHB2_GRP1_DisableClock\n
  *         MP_AHB2ENCLRR      DMAMUX1       LL_AHB2_GRP1_DisableClock\n
  *         MP_AHB2ENCLRR      DMA3          LL_AHB2_GRP1_DisableClock\n
  *         MP_AHB2ENCLRR      DMAMUX2       LL_AHB2_GRP1_DisableClock\n
  *         MP_AHB2ENCLRR      ADC1          LL_AHB2_GRP1_DisableClock\n
  *         MP_AHB2ENCLRR      ADC2          LL_AHB2_GRP1_DisableClock\n
  *         MP_AHB2ENCLRR      USBO          LL_AHB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA3
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBO
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_AHB2ENCLRR, Periphs);
}

/**
  * @brief  Force AHB2 peripherals reset.
  * @rmtoll AHB2RSTSETR      DMA1          LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTSETR      DMA2          LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTSETR      DMAMUX1       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTSETR      DMA3          LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTSETR      DMAMUX2       LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTSETR      ADC1          LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTSETR      ADC2          LL_AHB2_GRP1_ForceReset\n
  *         AHB2RSTSETR      USBO          LL_AHB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA3
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBO
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ForceReset(uint32_t Periphs)
{
  WRITE_REG(RCC->AHB2RSTSETR, Periphs);
}

/**
  * @brief  Release AHB2 peripherals reset.
  * @rmtoll AHB2RSTCLRR      DMA1          LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTCLRR      DMA2          LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTCLRR      DMAMUX1       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTCLRR      DMA3          LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTCLRR      DMAMUX2       LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTCLRR      ADC1          LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTCLRR      ADC2          LL_AHB2_GRP1_ReleaseReset\n
  *         AHB2RSTCLRR      USBO          LL_AHB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA3
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBO
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  WRITE_REG(RCC->AHB2RSTCLRR, Periphs);
}

/**
  * @brief  Enable AHB2 peripheral clocks in Sleep mode
  * @rmtoll MP_AHB2LPENSETR      DMA1          LL_AHB2_GRP1_EnableClockSleep\n
  *         MP_AHB2LPENSETR      DMA2          LL_AHB2_GRP1_EnableClockSleep\n
  *         MP_AHB2LPENSETR      DMAMUX1       LL_AHB2_GRP1_EnableClockSleep\n
  *         MP_AHB2LPENSETR      DMA3          LL_AHB2_GRP1_EnableClockSleep\n
  *         MP_AHB2LPENSETR      DMAMUX2       LL_AHB2_GRP1_EnableClockSleep\n
  *         MP_AHB2LPENSETR      ADC1          LL_AHB2_GRP1_EnableClockSleep\n
  *         MP_AHB2LPENSETR      ADC2          LL_AHB2_GRP1_EnableClockSleep\n
  *         MP_AHB2LPENSETR      USBO          LL_AHB2_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA3
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBO
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_AHB2LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_AHB2LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB2 peripheral clocks in Sleep mode
  * @rmtoll MP_AHB2LPENCLRR      DMA1          LL_AHB2_GRP1_DisableClockSleep\n
  *         MP_AHB2LPENCLRR      DMA2          LL_AHB2_GRP1_DisableClockSleep\n
  *         MP_AHB2LPENCLRR      DMAMUX1       LL_AHB2_GRP1_DisableClockSleep\n
  *         MP_AHB2LPENCLRR      DMA3          LL_AHB2_GRP1_DisableClockSleep\n
  *         MP_AHB2LPENCLRR      DMAMUX2       LL_AHB2_GRP1_DisableClockSleep\n
  *         MP_AHB2LPENCLRR      ADC1          LL_AHB2_GRP1_DisableClockSleep\n
  *         MP_AHB2LPENCLRR      ADC2          LL_AHB2_GRP1_DisableClockSleep\n
  *         MP_AHB2LPENCLRR      USBO          LL_AHB2_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMA3
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DMAMUX2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_USBO
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_AHB2LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB4 AHB4
  * @{
  */

/**
  * @brief  Force AHB4 peripherals reset.
  * @rmtoll AHB4RSTSETR     GPIOA       LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTSETR     GPIOB       LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTSETR     GPIOC       LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTSETR     GPIOD       LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTSETR     GPIOE       LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTSETR     GPIOF       LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTSETR     GPIOG       LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTSETR     GPIOH       LL_AHB4_GRP1_ForceReset\n
  *         AHB4RSTSETR     GPIOI       LL_AHB4_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOI
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_ForceReset(uint32_t Periphs)
{
  WRITE_REG(RCC->AHB4RSTSETR, Periphs);
}

/**
  * @brief  Release AHB4 peripherals reset.
  * @rmtoll AHB4RSTCLRR     GPIOA       LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTCLRR     GPIOB       LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTCLRR     GPIOC       LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTCLRR     GPIOD       LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTCLRR     GPIOE       LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTCLRR     GPIOF       LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTCLRR     GPIOG       LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTCLRR     GPIOH       LL_AHB4_GRP1_ReleaseReset\n
  *         AHB4RSTCLRR     GPIOI       LL_AHB4_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOI
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_ReleaseReset(uint32_t Periphs)
{
  WRITE_REG(RCC->AHB4RSTCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB4_S AHB4_S
  * @{
  */

/**
  * @brief  Enable secure AHB4 peripherals clock.
  * @rmtoll MP_S_AHB4ENSETR      GPIOA       LL_AHB4_S_GRP1_EnableClock\n
  *         MP_S_AHB4ENSETR      GPIOB       LL_AHB4_S_GRP1_EnableClock\n
  *         MP_S_AHB4ENSETR      GPIOC       LL_AHB4_S_GRP1_EnableClock\n
  *         MP_S_AHB4ENSETR      GPIOD       LL_AHB4_S_GRP1_EnableClock\n
  *         MP_S_AHB4ENSETR      GPIOE       LL_AHB4_S_GRP1_EnableClock\n
  *         MP_S_AHB4ENSETR      GPIOF       LL_AHB4_S_GRP1_EnableClock\n
  *         MP_S_AHB4ENSETR      GPIOG       LL_AHB4_S_GRP1_EnableClock\n
  *         MP_S_AHB4ENSETR      GPIOH       LL_AHB4_S_GRP1_EnableClock\n
  *         MP_S_AHB4ENSETR      GPIOI       LL_AHB4_S_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOI
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_S_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_S_AHB4ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_S_AHB4ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if secure AHB4 peripheral clock is enabled or not
  * @rmtoll MP_S_AHB4ENSETR      GPIOA       LL_AHB4_S_GRP1_IsEnabledClock\n
  *         MP_S_AHB4ENSETR      GPIOB       LL_AHB4_S_GRP1_IsEnabledClock\n
  *         MP_S_AHB4ENSETR      GPIOC       LL_AHB4_S_GRP1_IsEnabledClock\n
  *         MP_S_AHB4ENSETR      GPIOD       LL_AHB4_S_GRP1_IsEnabledClock\n
  *         MP_S_AHB4ENSETR      GPIOE       LL_AHB4_S_GRP1_IsEnabledClock\n
  *         MP_S_AHB4ENSETR      GPIOF       LL_AHB4_S_GRP1_IsEnabledClock\n
  *         MP_S_AHB4ENSETR      GPIOG       LL_AHB4_S_GRP1_IsEnabledClock\n
  *         MP_S_AHB4ENSETR      GPIOH       LL_AHB4_S_GRP1_IsEnabledClock\n
  *         MP_S_AHB4ENSETR      GPIOI       LL_AHB4_S_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOI
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB4_S_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_S_AHB4ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable secure AHB4 peripherals clock.
  * @rmtoll MP_S_AHB4ENCLRR      GPIOA       LL_AHB4_S_GRP1_DisableClock\n
  *         MP_S_AHB4ENCLRR      GPIOB       LL_AHB4_S_GRP1_DisableClock\n
  *         MP_S_AHB4ENCLRR      GPIOC       LL_AHB4_S_GRP1_DisableClock\n
  *         MP_S_AHB4ENCLRR      GPIOD       LL_AHB4_S_GRP1_DisableClock\n
  *         MP_S_AHB4ENCLRR      GPIOE       LL_AHB4_S_GRP1_DisableClock\n
  *         MP_S_AHB4ENCLRR      GPIOF       LL_AHB4_S_GRP1_DisableClock\n
  *         MP_S_AHB4ENCLRR      GPIOG       LL_AHB4_S_GRP1_DisableClock\n
  *         MP_S_AHB4ENCLRR      GPIOH       LL_AHB4_S_GRP1_DisableClock\n
  *         MP_S_AHB4ENCLRR      GPIOI       LL_AHB4_S_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOI
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_S_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_S_AHB4ENCLRR, Periphs);
}

/**
  * @brief  Enable secure AHB4 peripheral clocks in Sleep mode
  * @rmtoll MP_S_AHB4LPENSETR    GPIOA       LL_AHB4_S_GRP1_EnableClockSleep\n
  *         MP_S_AHB4LPENSETR    GPIOB       LL_AHB4_S_GRP1_EnableClockSleep\n
  *         MP_S_AHB4LPENSETR    GPIOC       LL_AHB4_S_GRP1_EnableClockSleep\n
  *         MP_S_AHB4LPENSETR    GPIOD       LL_AHB4_S_GRP1_EnableClockSleep\n
  *         MP_S_AHB4LPENSETR    GPIOE       LL_AHB4_S_GRP1_EnableClockSleep\n
  *         MP_S_AHB4LPENSETR    GPIOF       LL_AHB4_S_GRP1_EnableClockSleep\n
  *         MP_S_AHB4LPENSETR    GPIOG       LL_AHB4_S_GRP1_EnableClockSleep\n
  *         MP_S_AHB4LPENSETR    GPIOH       LL_AHB4_S_GRP1_EnableClockSleep\n
  *         MP_S_AHB4LPENSETR    GPIOI       LL_AHB4_S_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOI
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_S_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_S_AHB4LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_S_AHB4LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable secure AHB4 peripheral clocks in Sleep mode
  * @rmtoll MP_S_AHB4LPENCLRR    GPIOA       LL_AHB4_S_GRP1_DisableClockSleep\n
  *         MP_S_AHB4LPENCLRR    GPIOB       LL_AHB4_S_GRP1_DisableClockSleep\n
  *         MP_S_AHB4LPENCLRR    GPIOC       LL_AHB4_S_GRP1_DisableClockSleep\n
  *         MP_S_AHB4LPENCLRR    GPIOD       LL_AHB4_S_GRP1_DisableClockSleep\n
  *         MP_S_AHB4LPENCLRR    GPIOE       LL_AHB4_S_GRP1_DisableClockSleep\n
  *         MP_S_AHB4LPENCLRR    GPIOF       LL_AHB4_S_GRP1_DisableClockSleep\n
  *         MP_S_AHB4LPENCLRR    GPIOG       LL_AHB4_S_GRP1_DisableClockSleep\n
  *         MP_S_AHB4LPENCLRR    GPIOH       LL_AHB4_S_GRP1_DisableClockSleep\n
  *         MP_S_AHB4LPENCLRR    GPIOI       LL_AHB4_S_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_S_GRP1_PERIPH_GPIOI
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_S_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_S_AHB4LPENCLRR, Periphs);
}
/**
  * @}
  */


/** @defgroup BUS_LL_EF_AHB4_NS AHB4_NS
  * @{
  */

/**
  * @brief  Enable non secure AHB4 peripherals clock.
  * @rmtoll MP_NS_AHB4ENSETR      GPIOA       LL_AHB4_NS_GRP1_EnableClock\n
  *         MP_NS_AHB4ENSETR      GPIOB       LL_AHB4_NS_GRP1_EnableClock\n
  *         MP_NS_AHB4ENSETR      GPIOC       LL_AHB4_NS_GRP1_EnableClock\n
  *         MP_NS_AHB4ENSETR      GPIOD       LL_AHB4_NS_GRP1_EnableClock\n
  *         MP_NS_AHB4ENSETR      GPIOE       LL_AHB4_NS_GRP1_EnableClock\n
  *         MP_NS_AHB4ENSETR      GPIOF       LL_AHB4_NS_GRP1_EnableClock\n
  *         MP_NS_AHB4ENSETR      GPIOG       LL_AHB4_NS_GRP1_EnableClock\n
  *         MP_NS_AHB4ENSETR      GPIOH       LL_AHB4_NS_GRP1_EnableClock\n
  *         MP_NS_AHB4ENSETR      GPIOI       LL_AHB4_NS_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOI
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_NS_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_NS_AHB4ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_NS_AHB4ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if non secure AHB4 peripheral clock is enabled or not
  * @rmtoll MP_NS_AHB4ENSETR      GPIOA       LL_AHB4_NS_GRP1_IsEnabledClock\n
  *         MP_NS_AHB4ENSETR      GPIOB       LL_AHB4_NS_GRP1_IsEnabledClock\n
  *         MP_NS_AHB4ENSETR      GPIOC       LL_AHB4_NS_GRP1_IsEnabledClock\n
  *         MP_NS_AHB4ENSETR      GPIOD       LL_AHB4_NS_GRP1_IsEnabledClock\n
  *         MP_NS_AHB4ENSETR      GPIOE       LL_AHB4_NS_GRP1_IsEnabledClock\n
  *         MP_NS_AHB4ENSETR      GPIOF       LL_AHB4_NS_GRP1_IsEnabledClock\n
  *         MP_NS_AHB4ENSETR      GPIOG       LL_AHB4_NS_GRP1_IsEnabledClock\n
  *         MP_NS_AHB4ENSETR      GPIOH       LL_AHB4_NS_GRP1_IsEnabledClock\n
  *         MP_NS_AHB4ENSETR      GPIOI       LL_AHB4_NS_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOI
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB4_NS_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_NS_AHB4ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable non secure AHB4 peripherals clock.
  * @rmtoll MP_NS_AHB4ENCLRR      GPIOA       LL_AHB4_NS_GRP1_DisableClock\n
  *         MP_NS_AHB4ENCLRR      GPIOB       LL_AHB4_NS_GRP1_DisableClock\n
  *         MP_NS_AHB4ENCLRR      GPIOC       LL_AHB4_NS_GRP1_DisableClock\n
  *         MP_NS_AHB4ENCLRR      GPIOD       LL_AHB4_NS_GRP1_DisableClock\n
  *         MP_NS_AHB4ENCLRR      GPIOE       LL_AHB4_NS_GRP1_DisableClock\n
  *         MP_NS_AHB4ENCLRR      GPIOF       LL_AHB4_NS_GRP1_DisableClock\n
  *         MP_NS_AHB4ENCLRR      GPIOG       LL_AHB4_NS_GRP1_DisableClock\n
  *         MP_NS_AHB4ENCLRR      GPIOH       LL_AHB4_NS_GRP1_DisableClock\n
  *         MP_NS_AHB4ENCLRR      GPIOI       LL_AHB4_NS_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOI
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_NS_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_NS_AHB4ENCLRR, Periphs);
}

/**
  * @brief  Enable non secure AHB4 peripheral clocks in Sleep mode
  * @rmtoll MP_NS_AHB4LPENSETR    GPIOA       LL_AHB4_NS_GRP1_EnableClockSleep\n
  *         MP_NS_AHB4LPENSETR    GPIOB       LL_AHB4_NS_GRP1_EnableClockSleep\n
  *         MP_NS_AHB4LPENSETR    GPIOC       LL_AHB4_NS_GRP1_EnableClockSleep\n
  *         MP_NS_AHB4LPENSETR    GPIOD       LL_AHB4_NS_GRP1_EnableClockSleep\n
  *         MP_NS_AHB4LPENSETR    GPIOE       LL_AHB4_NS_GRP1_EnableClockSleep\n
  *         MP_NS_AHB4LPENSETR    GPIOF       LL_AHB4_NS_GRP1_EnableClockSleep\n
  *         MP_NS_AHB4LPENSETR    GPIOG       LL_AHB4_NS_GRP1_EnableClockSleep\n
  *         MP_NS_AHB4LPENSETR    GPIOH       LL_AHB4_NS_GRP1_EnableClockSleep\n
  *         MP_NS_AHB4LPENSETR    GPIOI       LL_AHB4_NS_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOI
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_NS_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_NS_AHB4LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_NS_AHB4LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable non secure AHB4 peripheral clocks in Sleep mode
  * @rmtoll MP_NS_AHB4LPENCLRR    GPIOA       LL_AHB4_NS_GRP1_DisableClockSleep\n
  *         MP_NS_AHB4LPENCLRR    GPIOB       LL_AHB4_NS_GRP1_DisableClockSleep\n
  *         MP_NS_AHB4LPENCLRR    GPIOC       LL_AHB4_NS_GRP1_DisableClockSleep\n
  *         MP_NS_AHB4LPENCLRR    GPIOD       LL_AHB4_NS_GRP1_DisableClockSleep\n
  *         MP_NS_AHB4LPENCLRR    GPIOE       LL_AHB4_NS_GRP1_DisableClockSleep\n
  *         MP_NS_AHB4LPENCLRR    GPIOF       LL_AHB4_NS_GRP1_DisableClockSleep\n
  *         MP_NS_AHB4LPENCLRR    GPIOG       LL_AHB4_NS_GRP1_DisableClockSleep\n
  *         MP_NS_AHB4LPENCLRR    GPIOH       LL_AHB4_NS_GRP1_DisableClockSleep\n
  *         MP_NS_AHB4LPENCLRR    GPIOI       LL_AHB4_NS_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_NS_GRP1_PERIPH_GPIOI
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_NS_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_NS_AHB4LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB5 AHB5
  * @{
  */

/**
  * @brief  Enable AHB5 peripherals clock.
  * @rmtoll MP_AHB5ENSETR      PKA          LL_AHB5_GRP1_EnableClock\n
  *         MP_AHB5ENSETR      SAES         LL_AHB5_GRP1_EnableClock\n
  *         MP_AHB5ENSETR      CRYP1        LL_AHB5_GRP1_EnableClock\n
  *         MP_AHB5ENSETR      HASH1        LL_AHB5_GRP1_EnableClock\n
  *         MP_AHB5ENSETR      RNG1         LL_AHB5_GRP1_EnableClock\n
  *         MP_AHB5ENSETR      BKPSRAM      LL_AHB5_GRP1_EnableClock\n
  *         MP_AHB5ENSETR      AXIMC        LL_AHB5_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB5_GRP1_PERIPH_CRYP1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HASH1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RNG1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_BKPSRAM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_AXIMC
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_AHB5ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_AHB5ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB5 peripheral clock is enabled or not
  * @rmtoll MP_AHB5ENSETR      PKA          LL_AHB5_GRP1_IsEnabledClock\n
  *         MP_AHB5ENSETR      SAES         LL_AHB5_GRP1_IsEnabledClock\n
  *         MP_AHB5ENSETR      CRYP1        LL_AHB5_GRP1_IsEnabledClock\n
  *         MP_AHB5ENSETR      HASH1        LL_AHB5_GRP1_IsEnabledClock\n
  *         MP_AHB5ENSETR      RNG1         LL_AHB5_GRP1_IsEnabledClock\n
  *         MP_AHB5ENSETR      BKPSRAM      LL_AHB5_GRP1_IsEnabledClock\n
  *         MP_AHB5ENSETR      AXIMC        LL_AHB5_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB5_GRP1_PERIPH_CRYP1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HASH1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RNG1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_BKPSRAM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_AXIMC
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB5_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_AHB5ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable AHB5 peripherals clock.
  * @rmtoll MP_AHB5ENCLRR      PKA          LL_AHB5_GRP1_DisableClock\n
  *         MP_AHB5ENCLRR      SAES         LL_AHB5_GRP1_DisableClock\n
  *         MP_AHB5ENCLRR      CRYP1        LL_AHB5_GRP1_DisableClock\n
  *         MP_AHB5ENCLRR      HASH1        LL_AHB5_GRP1_DisableClock\n
  *         MP_AHB5ENCLRR      RNG1         LL_AHB5_GRP1_DisableClock\n
  *         MP_AHB5ENCLRR      BKPSRAM      LL_AHB5_GRP1_DisableClock\n
  *         MP_AHB5ENCLRR      AXIMC        LL_AHB5_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB5_GRP1_PERIPH_CRYP1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HASH1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RNG1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_BKPSRAM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_AXIMC
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_AHB5ENCLRR, Periphs);
}

/**
  * @brief  Force AHB5 peripherals reset.
  * @rmtoll AHB5RSTSETR      PKA          LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTSETR      SAES         LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTSETR      CRYP1        LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTSETR      HASH1        LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTSETR      RNG1         LL_AHB5_GRP1_ForceReset\n
  *         AHB5RSTSETR      AXIMC        LL_AHB5_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB5_GRP1_PERIPH_CRYP1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HASH1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RNG1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_AXIMC
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_ForceReset(uint32_t Periphs)
{
  WRITE_REG(RCC->AHB5RSTSETR, Periphs);
}

/**
  * @brief  Release AHB5 peripherals reset.
  * @rmtoll AHB5RSTCLRR      PKA          LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTCLRR      SAES         LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTCLRR      CRYP1        LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTCLRR      HASH1        LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTCLRR      RNG1         LL_AHB5_GRP1_ReleaseReset\n
  *         AHB5RSTCLRR      AXIMC        LL_AHB5_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB5_GRP1_PERIPH_CRYP1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HASH1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RNG1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_AXIMC
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_ReleaseReset(uint32_t Periphs)
{
  WRITE_REG(RCC->AHB5RSTCLRR, Periphs);
}

/**
  * @brief  Enable AHB5 peripheral clocks in Sleep mode
  * @rmtoll MP_AHB5LPENSETR      PKA          LL_AHB5_GRP1_EnableClockSleep\n
  *         MP_AHB5LPENSETR      SAES         LL_AHB5_GRP1_EnableClockSleep\n
  *         MP_AHB5LPENSETR      CRYP1        LL_AHB5_GRP1_EnableClockSleep\n
  *         MP_AHB5LPENSETR      HASH1        LL_AHB5_GRP1_EnableClockSleep\n
  *         MP_AHB5LPENSETR      RNG1         LL_AHB5_GRP1_EnableClockSleep\n
  *         MP_AHB5LPENSETR      BKPSRAM      LL_AHB5_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB5_GRP1_PERIPH_CRYP1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HASH1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RNG1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_BKPSRAM
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_AHB5LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_AHB5LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB5 peripheral clocks in Sleep mode
  * @rmtoll MP_AHB5LPENCLRR      PKA          LL_AHB5_GRP1_DisableClockSleep\n
  *         MP_AHB5LPENCLRR      SAES         LL_AHB5_GRP1_DisableClockSleep\n
  *         MP_AHB5LPENCLRR      CRYP1        LL_AHB5_GRP1_DisableClockSleep\n
  *         MP_AHB5LPENCLRR      HASH1        LL_AHB5_GRP1_DisableClockSleep\n
  *         MP_AHB5LPENCLRR      RNG1         LL_AHB5_GRP1_DisableClockSleep\n
  *         MP_AHB5LPENCLRR      BKPSRAM      LL_AHB5_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SAES
  *         @arg @ref LL_AHB5_GRP1_PERIPH_CRYP1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HASH1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_RNG1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_BKPSRAM
  * @retval None
  */
__STATIC_INLINE void LL_AHB5_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_AHB5LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB6 AHB6
  * @{
  */

/**
  * @brief  Enable AHB6 peripherals clock.
  * @rmtoll MP_AHB6ENSETR      MCE         LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH1CK      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH1TX      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH1RX      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH1MAC     LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      FMC         LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      QSPI        LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      SDMMC1      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      SDMMC2      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      CRC1        LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      USBH        LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH2CK      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH2TX      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH2RX      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH2MAC     LL_AHB6_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_GRP1_PERIPH_MCE
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1CK
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB6_GRP1_PERIPH_CRC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_USBH
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2CK
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2TX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2RX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2MAC
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_AHB6ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_AHB6ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB6 peripheral clock is enabled or not
  * @rmtoll MP_AHB6ENSETR      MCE         LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH1CK      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH1TX      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH1RX      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH1MAC     LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      FMC         LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      QSPI        LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      SDMMC1      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      SDMMC2      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      CRC1        LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      USBH        LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH2CK      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH2TX      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH2RX      LL_AHB6_GRP1_EnableClock\n
  *         MP_AHB6ENSETR      ETH2MAC     LL_AHB6_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_GRP1_PERIPH_MCE
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1CK
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB6_GRP1_PERIPH_CRC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_USBH
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2CK
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2TX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2RX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2MAC
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB6_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_AHB6ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable AHB6 peripherals clock.
  * @rmtoll MP_AHB6ENCLRR      MCE         LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      ETH1CK      LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      ETH1TX      LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      ETH1RX      LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      ETH1MAC     LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      FMC         LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      QSPI        LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      SDMMC1      LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      SDMMC2      LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      CRC1        LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      USBH        LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      ETH2CK      LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      ETH2TX      LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      ETH2RX      LL_AHB6_GRP1_DisableClock\n
  *         MP_AHB6ENCLRR      ETH2MAC     LL_AHB6_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_GRP1_PERIPH_MCE
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1CK
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB6_GRP1_PERIPH_CRC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_USBH
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2CK
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2TX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2RX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2MAC
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_AHB6ENCLRR, Periphs);
}

/**
  * @brief  Force AHB6 peripherals reset.
  * @rmtoll AHB6RSTSETR      MDMA        LL_AHB6_GRP1_ForceReset\n
  *         AHB6RSTSETR      MCE         LL_AHB6_GRP1_ForceReset\n
  *         AHB6RSTSETR      ETH1MAC     LL_AHB6_GRP1_ForceReset\n
  *         AHB6RSTSETR      FMC         LL_AHB6_GRP1_ForceReset\n
  *         AHB6RSTSETR      QSPI        LL_AHB6_GRP1_ForceReset\n
  *         AHB6RSTSETR      SDMMC1      LL_AHB6_GRP1_ForceReset\n
  *         AHB6RSTSETR      SDMMC2      LL_AHB6_GRP1_ForceReset\n
  *         AHB6RSTSETR      CRC1        LL_AHB6_GRP1_ForceReset\n
  *         AHB6RSTSETR      USBH        LL_AHB6_GRP1_ForceReset\n
  *         AHB6RSTSETR      ETH2MAC     LL_AHB6_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB6_S_GRP1_PERIPH_MDMA
  *         @arg @ref LL_AHB6_GRP1_PERIPH_MCE
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB6_GRP1_PERIPH_CRC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_USBH
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2MAC
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_GRP1_ForceReset(uint32_t Periphs)
{
  WRITE_REG(RCC->AHB6RSTSETR, Periphs);
}

/**
  * @brief  Release AHB6 peripherals reset.
  * @rmtoll AHB6RSTCLRR      MDMA        LL_AHB6_GRP1_ReleaseReset\n
  *         AHB6RSTCLRR      MCE         LL_AHB6_GRP1_ReleaseReset\n
  *         AHB6RSTCLRR      ETH1MAC     LL_AHB6_GRP1_ReleaseReset\n
  *         AHB6RSTCLRR      FMC         LL_AHB6_GRP1_ReleaseReset\n
  *         AHB6RSTCLRR      QSPI        LL_AHB6_GRP1_ReleaseReset\n
  *         AHB6RSTCLRR      SDMMC1      LL_AHB6_GRP1_ReleaseReset\n
  *         AHB6RSTCLRR      SDMMC2      LL_AHB6_GRP1_ReleaseReset\n
  *         AHB6RSTCLRR      CRC1        LL_AHB6_GRP1_ReleaseReset\n
  *         AHB6RSTCLRR      USBH        LL_AHB6_GRP1_ReleaseReset\n
  *         AHB6RSTCLRR      ETH2MAC     LL_AHB6_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB6_S_GRP1_PERIPH_MDMA
  *         @arg @ref LL_AHB6_GRP1_PERIPH_MCE
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB6_GRP1_PERIPH_CRC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_USBH
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2MAC
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_GRP1_ReleaseReset(uint32_t Periphs)
{
  WRITE_REG(RCC->AHB6RSTCLRR, Periphs);
}

/**
  * @brief  Enable AHB6 peripheral clocks in Sleep mode
  * @rmtoll MP_AHB6LPENSETR      MCE         LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      ETH1CK      LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      ETH1TX      LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      ETH1RX      LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      ETH1MAC     LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      FMC         LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      QSPI        LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      SDMMC1      LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      SDMMC2      LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      CRC1        LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      USBH        LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      ETH2CK      LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      ETH2TX      LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      ETH2RX      LL_AHB6_GRP1_EnableClockSleep\n
  *         MP_AHB6LPENSETR      ETH2MAC     LL_AHB6_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_GRP1_PERIPH_MCE
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1CK
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB6_GRP1_PERIPH_CRC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_USBH
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2CK
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2TX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2RX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2MAC
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_AHB6LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_AHB6LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB6 peripheral clocks in Sleep mode
  * @rmtoll MP_AHB6LPENCLRR      MCE         LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      ETH1CK      LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      ETH1TX      LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      ETH1RX      LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      ETH1MAC     LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      FMC         LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      QSPI        LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      SDMMC1      LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      SDMMC2      LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      CRC1        LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      USBH        LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      ETH2CK      LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      ETH2TX      LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      ETH2RX      LL_AHB6_GRP1_DisableClockSleep\n
  *         MP_AHB6LPENCLRR      ETH2MAC     LL_AHB6_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_GRP1_PERIPH_MCE
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1CK
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1TX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1RX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1MAC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB6_GRP1_PERIPH_QSPI
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_SDMMC2
  *         @arg @ref LL_AHB6_GRP1_PERIPH_CRC1
  *         @arg @ref LL_AHB6_GRP1_PERIPH_USBH
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2CK
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2TX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2RX
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2MAC
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_AHB6LPENCLRR, Periphs);
}

/**
  * @brief  Enable AHB6 peripheral clocks in Stop mode
  * @rmtoll MP_AHB6LPENSETR    ETH1STP       LL_AHB6_GRP1_EnableClockStop\n
  *         MP_AHB6LPENSETR    ETH2STP       LL_AHB6_GRP1_EnableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1STP
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2STP
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_GRP1_EnableClockStop(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_AHB6LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_AHB6LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable AHB6 peripheral clocks in Sleep mode
  * @rmtoll MP_AHB6LPENCLRR    ETH1STP       LL_AHB6_GRP1_DisableClockStop\n
  *         MP_AHB6LPENCLRR    ETH2STP       LL_AHB6_GRP1_DisableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH1STP
  *         @arg @ref LL_AHB6_GRP1_PERIPH_ETH2STP
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_GRP1_DisableClockStop(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_AHB6LPENCLRR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB6_S AHB6_S
  * @{
  */

/**
  * @brief  Enable secure AHB6 peripherals clock.
  * @rmtoll MP_S_AHB6ENSETR      MDMA         LL_AHB6_S_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_S_GRP1_PERIPH_MDMA
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_S_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_S_AHB6ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_S_AHB6ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if secure AHB6 peripheral clock is enabled or not
  * @rmtoll MP_S_AHB6ENSETR      MDMA         LL_AHB6_S_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_S_GRP1_PERIPH_MDMA
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB6_S_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_S_AHB6ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable secure AHB6 peripherals clock.
  * @rmtoll MP_S_AHB6ENCLRR      MDMA         LL_AHB6_S_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_S_GRP1_PERIPH_MDMA
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_S_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_S_AHB6ENCLRR, Periphs);
}

/**
  * @brief  Enable secure AHB6 peripheral clocks in Sleep mode
  * @rmtoll MP_S_AHB6LPENSETR      MDMA         LL_AHB6_S_GRP1_EnableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_S_GRP1_PERIPH_MDMA
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_S_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_S_AHB6LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_S_AHB6LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable secure AHB6 peripheral clocks in Sleep mode
  * @rmtoll MP_S_AHB6LPENCLRR      MDMA         LL_AHB6_S_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_S_GRP1_PERIPH_MDMA
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_S_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_S_AHB6LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB6_NS AHB6_NS
  * @{
  */

/**
  * @brief  Enable non secure AHB6 peripherals clock.
  * @rmtoll MP_NS_AHB6ENSETR      MDMA         LL_AHB6_NS_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_NS_GRP1_PERIPH_MDMA
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_NS_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_NS_AHB6ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_NS_AHB6ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if non secure AHB6 peripheral clock is enabled or not
  * @rmtoll MP_NS_AHB6ENSETR      MDMA         LL_AHB6_NS_GRP1_EnableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_NS_GRP1_PERIPH_MDMA
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB6_NS_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_NS_AHB6ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable non secure AHB6 peripherals clock.
  * @rmtoll MP_NS_AHB6ENCLRR      MDMA         LL_AHB6_NS_GRP1_DisableClock\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_NS_GRP1_PERIPH_MDMA
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_NS_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_NS_AHB6ENCLRR, Periphs);
}

/**
  * @brief  Enable non secure AHB6 peripheral clocks in Sleep mode
  * @rmtoll MP_NS_AHB6LPENSETR      MDMA         LL_AHB6_NS_GRP1_EnableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_NS_GRP1_PERIPH_MDMA
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_NS_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_NS_AHB6LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_NS_AHB6LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable non secure AHB6 peripheral clocks in Sleep mode
  * @rmtoll MP_NS_AHB6LPENCLRR      MDMA         LL_AHB6_NS_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB6_NS_GRP1_PERIPH_MDMA
  * @retval None
  */
__STATIC_INLINE void LL_AHB6_NS_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_NS_AHB6LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_AXI AXI
  * @{
  */

/**
  * @brief  Enable secure AXI peripheral clocks in Sleep mode
  * @rmtoll MP_S_AXIMLPENSETR    SYSRAMLPEN      LL_AXI_S_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AXI_S_GRP1_PERIPH_SYSRAMLPEN
  * @retval None
  */
__STATIC_INLINE void LL_AXI_S_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_S_AXIMLPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_S_AXIMLPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if secure AXI peripheral clock is enabled or not
  * @rmtoll MP_S_AXIMLPENSETR      SYSRAMLPEN      LL_AXI_S_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AXI_S_GRP1_PERIPH_SYSRAMLPEN
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AXI_S_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_S_AXIMLPENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable secure AXI peripheral clocks in Sleep mode
  * @rmtoll MP_S_AXIMLPENCLRR    SYSRAMLPEN      LL_AXI_S_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AXI_S_GRP1_PERIPH_SYSRAMLPEN
  * @retval None
  */
__STATIC_INLINE void LL_AXI_S_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_S_AXIMLPENCLRR, Periphs);
}

/**
  * @brief  Enable non secure AXI peripheral clocks in Sleep mode
  * @rmtoll MP_NS_AXIMLPENSETR    SYSRAMLPEN      LL_AXI_NS_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AXI_NS_GRP1_PERIPH_SYSRAMLPEN
  * @retval None
  */
__STATIC_INLINE void LL_AXI_NS_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_NS_AXIMLPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_S_AXIMLPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if non secure AXI peripheral clock in Sleep mode is enabled or not
  * @rmtoll MP_NS_AXIMLPENSETR      SYSRAMLPEN      LL_AXI_NS_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AXI_NS_GRP1_PERIPH_SYSRAMLPEN
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AXI_NS_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_NS_AXIMLPENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable non secure AXI peripheral clocks in Sleep mode
  * @rmtoll MP_NS_AXIMLPENCLRR    SYSRAMLPEN      LL_AXI_NS_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AXI_NS_GRP1_PERIPH_SYSRAMLPEN
  * @retval None
  */
__STATIC_INLINE void LL_AXI_NS_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_NS_AXIMLPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_MLAHB MLAHB
  * @{
  */

/**
  * @brief  Enable MLAHB peripheral clocks in Sleep mode
  * @rmtoll MP_MLAHBLPENSETR    SRAM1LPEN         LL_MLAHB_GRP1_EnableClockSleep\n
  *         MP_MLAHBLPENSETR    SRAM2LPEN         LL_MLAHB_GRP1_EnableClockSleep\n
  *         MP_MLAHBLPENSETR    SRAM3LPEN         LL_MLAHB_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_MLAHB_GRP1_PERIPH_SRAM1LPEN
  *         @arg @ref LL_MLAHB_GRP1_PERIPH_SRAM2LPEN
  *         @arg @ref LL_MLAHB_GRP1_PERIPH_SRAM3LPEN
  * @retval None
  */
__STATIC_INLINE void LL_MLAHB_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_MLAHBLPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_MLAHBLPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if MLAHB peripheral clock in Sleep mode is enabled or not
  * @rmtoll MP_MLAHBLPENSETR    SRAM1LPEN         LL_MLAHB_GRP1_IsEnabledClockSleep\n
  *         MP_MLAHBLPENSETR    SRAM2LPEN         LL_MLAHB_GRP1_IsEnabledClockSleep\n
  *         MP_MLAHBLPENSETR    SRAM3LPEN         LL_MLAHB_GRP1_IsEnabledClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_MLAHB_GRP1_PERIPH_SRAM1LPEN
  *         @arg @ref LL_MLAHB_GRP1_PERIPH_SRAM2LPEN
  *         @arg @ref LL_MLAHB_GRP1_PERIPH_SRAM3LPEN
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MLAHB_GRP1_IsEnabledClockSleep(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_MLAHBLPENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable MLAHB peripheral clocks in Sleep mode
  * @rmtoll MP_MLAHBLPENCLRR    SRAM1LPEN         LL_MLAHB_GRP1_DisableClockSleep\n
  *         MP_MLAHBLPENCLRR    SRAM2LPEN         LL_MLAHB_GRP1_DisableClockSleep\n
  *         MP_MLAHBLPENCLRR    SRAM3LPEN         LL_MLAHB_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_MLAHB_GRP1_PERIPH_SRAM1LPEN
  *         @arg @ref LL_MLAHB_GRP1_PERIPH_SRAM2LPEN
  *         @arg @ref LL_MLAHB_GRP1_PERIPH_SRAM3LPEN
  * @retval None
  */
__STATIC_INLINE void LL_MLAHB_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_MLAHBLPENCLRR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1 APB1
  * @{
  */

/**
  * @brief  Enable APB1 peripherals clock.
  * @rmtoll MP_APB1ENSETR      TIM2       LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      TIM3       LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      TIM4       LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      TIM5       LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      TIM6       LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      TIM7       LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      LPTIM1     LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      SPI2       LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      SPI3       LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      USART3     LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      UART4      LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      UART5      LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      UART7      LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      UART8      LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      I2C1       LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      I2C2       LL_APB1_GRP1_EnableClock\n
  *         MP_APB1ENSETR      SPDIF      LL_APB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIF
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB1ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB1ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not
  * @rmtoll MP_APB1ENSETR      TIM2       LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      TIM3       LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      TIM4       LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      TIM5       LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      TIM6       LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      TIM7       LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      LPTIM1     LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      SPI2       LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      SPI3       LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      USART3     LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      UART4      LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      UART5      LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      UART7      LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      UART8      LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      I2C1       LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      I2C2       LL_APB1_GRP1_IsEnabledClock\n
  *         MP_APB1ENSETR      SPDIF      LL_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIF
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_APB1ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB1 peripherals clock.
  * @rmtoll MP_APB1ENCLRR      TIM2       LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      TIM3       LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      TIM4       LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      TIM5       LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      TIM6       LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      TIM7       LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      LPTIM1     LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      SPI2       LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      SPI3       LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      USART3     LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      UART4      LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      UART5      LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      UART7      LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      UART8      LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      I2C1       LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      I2C2       LL_APB1_GRP1_DisableClock\n
  *         MP_APB1ENCLRR      SPDIF      LL_APB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIF
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB1ENCLRR, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset.
  * @rmtoll APB1RSTSETR     TIM2       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     TIM3       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     TIM4       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     TIM5       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     TIM6       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     TIM7       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     LPTIM1     LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     SPI2       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     SPI3       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     USART3     LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     UART4      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     UART5      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     UART7      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     UART8      LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     I2C1       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     I2C2       LL_APB1_GRP1_ForceReset\n
  *         APB1RSTSETR     SPDIF      LL_APB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIF
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB1RSTSETR, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset.
  * @rmtoll APB1RSTCLRR     TIM2       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     TIM3       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     TIM4       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     TIM5       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     TIM6       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     TIM7       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     LPTIM1     LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     SPI2       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     SPI3       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     USART3     LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     UART4      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     UART5      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     UART7      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     UART8      LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     I2C1       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     I2C2       LL_APB1_GRP1_ReleaseReset\n
  *         APB1RSTCLRR     SPDIF      LL_APB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIF
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB1RSTCLRR, Periphs);
}

/**
  * @brief  Enable APB1 peripheral clocks in Sleep mode
  * @rmtoll MP_APB1LPENSETR    TIM2       LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    TIM3       LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    TIM4       LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    TIM5       LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    TIM6       LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    TIM7       LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    LPTIM1     LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    SPI2       LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    SPI3       LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    USART3     LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    UART4      LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    UART5      LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    UART7      LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    UART8      LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    I2C1       LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    I2C2       LL_APB1_GRP1_EnableClockSleep\n
  *         MP_APB1LPENSETR    SPDIF      LL_APB1_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIF
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB1LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB1LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB1 peripheral clocks in Sleep mode
  * @rmtoll MP_APB1LPENCLRR    TIM2       LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    TIM3       LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    TIM4       LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    TIM5       LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    TIM6       LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    TIM7       LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    LPTIM1     LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    SPI2       LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    SPI3       LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    USART3     LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    UART4      LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    UART5      LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    UART7      LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    UART8      LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    I2C1       LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    I2C2       LL_APB1_GRP1_DisableClockSleep\n
  *         MP_APB1LPENCLRR    SPDIF      LL_APB1_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPDIF
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB1LPENCLRR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB2 APB2
  * @{
  */

/**
  * @brief  Enable APB2 peripherals clock.
  * @rmtoll MP_APB2ENSETR      TIM1       LL_APB2_GRP1_EnableClock\n
  *         MP_APB2ENSETR      TIM8       LL_APB2_GRP1_EnableClock\n
  *         MP_APB2ENSETR      SPI1       LL_APB2_GRP1_EnableClock\n
  *         MP_APB2ENSETR      USART6     LL_APB2_GRP1_EnableClock\n
  *         MP_APB2ENSETR      SAI1       LL_APB2_GRP1_EnableClock\n
  *         MP_APB2ENSETR      SAI2       LL_APB2_GRP1_EnableClock\n
  *         MP_APB2ENSETR      DFSDM1     LL_APB2_GRP1_EnableClock\n
  *         MP_APB2ENSETR      ADFSDM1    LL_APB2_GRP1_EnableClock\n
  *         MP_APB2ENSETR      FDCAN      LL_APB2_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_FDCAN
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB2ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB2ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB2 peripheral clock is enabled or not
  * @rmtoll MP_APB2ENSETR      TIM1       LL_APB2_GRP1_IsEnabledClock\n
  *         MP_APB2ENSETR      TIM8       LL_APB2_GRP1_IsEnabledClock\n
  *         MP_APB2ENSETR      SPI1       LL_APB2_GRP1_IsEnabledClock\n
  *         MP_APB2ENSETR      USART6     LL_APB2_GRP1_IsEnabledClock\n
  *         MP_APB2ENSETR      SAI1       LL_APB2_GRP1_IsEnabledClock\n
  *         MP_APB2ENSETR      SAI2       LL_APB2_GRP1_IsEnabledClock\n
  *         MP_APB2ENSETR      DFSDM1     LL_APB2_GRP1_IsEnabledClock\n
  *         MP_APB2ENSETR      ADFSDM1    LL_APB2_GRP1_IsEnabledClock\n
  *         MP_APB2ENSETR      FDCAN      LL_APB2_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_FDCAN
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_APB2ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll MP_APB2ENCLRR      TIM1       LL_APB2_GRP1_DisableClock\n
  *         MP_APB2ENCLRR      TIM8       LL_APB2_GRP1_DisableClock\n
  *         MP_APB2ENCLRR      SPI1       LL_APB2_GRP1_DisableClock\n
  *         MP_APB2ENCLRR      USART6     LL_APB2_GRP1_DisableClock\n
  *         MP_APB2ENCLRR      SAI1       LL_APB2_GRP1_DisableClock\n
  *         MP_APB2ENCLRR      SAI2       LL_APB2_GRP1_DisableClock\n
  *         MP_APB2ENCLRR      DFSDM1     LL_APB2_GRP1_DisableClock\n
  *         MP_APB2ENCLRR      ADFSDM1    LL_APB2_GRP1_DisableClock\n
  *         MP_APB2ENCLRR      FDCAN      LL_APB2_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_FDCAN
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB2ENCLRR, Periphs);
}

/**
  * @brief  Force APB2 peripherals reset.
  * @rmtoll APB2RSTSETR     TIM1       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTSETR     TIM8       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTSETR     SPI1       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTSETR     USART6     LL_APB2_GRP1_ForceReset\n
  *         APB2RSTSETR     SAI1       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTSETR     SAI2       LL_APB2_GRP1_ForceReset\n
  *         APB2RSTSETR     DFSDM1     LL_APB2_GRP1_ForceReset\n
  *         APB2RSTSETR     FDCAN      LL_APB2_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_FDCAN
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ForceReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB2RSTSETR, Periphs);
}

/**
  * @brief  Release APB2 peripherals reset.
  * @rmtoll APB2RSTCLRR     TIM1       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTCLRR     TIM8       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTCLRR     SPI1       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTCLRR     USART6     LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTCLRR     SAI1       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTCLRR     SAI2       LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTSETR     DFSDM1     LL_APB2_GRP1_ReleaseReset\n
  *         APB2RSTCLRR     FDCAN      LL_APB2_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_FDCAN
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB2RSTCLRR, Periphs);
}

/**
  * @brief  Enable APB2 peripheral clocks in Sleep mode
  * @rmtoll MP_APB2LPENSETR    TIM1       LL_APB2_GRP1_EnableClockSleep\n
  *         MP_APB2LPENSETR    TIM8       LL_APB2_GRP1_EnableClockSleep\n
  *         MP_APB2LPENSETR    SPI1       LL_APB2_GRP1_EnableClockSleep\n
  *         MP_APB2LPENSETR    USART6     LL_APB2_GRP1_EnableClockSleep\n
  *         MP_APB2LPENSETR    SAI1       LL_APB2_GRP1_EnableClockSleep\n
  *         MP_APB2LPENSETR    SAI2       LL_APB2_GRP1_EnableClockSleep\n
  *         MP_APB2LPENSETR    DFSDM1     LL_APB2_GRP1_EnableClockSleep\n
  *         MP_APB2LPENSETR    ADFSDM1    LL_APB2_GRP1_EnableClockSleep\n
  *         MP_APB2LPENSETR    FDCAN      LL_APB2_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_FDCAN
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB2LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB2LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB2 peripheral clocks in Sleep mode
  * @rmtoll MP_APB2LPENCLRR    TIM1       LL_APB2_GRP1_DisableClockSleep\n
  *         MP_APB2LPENCLRR    TIM8       LL_APB2_GRP1_DisableClockSleep\n
  *         MP_APB2LPENCLRR    SPI1       LL_APB2_GRP1_DisableClockSleep\n
  *         MP_APB2LPENCLRR    USART6     LL_APB2_GRP1_DisableClockSleep\n
  *         MP_APB2LPENCLRR    SAI1       LL_APB2_GRP1_DisableClockSleep\n
  *         MP_APB2LPENCLRR    SAI2       LL_APB2_GRP1_DisableClockSleep\n
  *         MP_APB2LPENCLRR    DFSDM1     LL_APB2_GRP1_DisableClockSleep\n
  *         MP_APB2LPENCLRR    ADFSDM1    LL_APB2_GRP1_DisableClockSleep\n
  *         MP_APB2LPENCLRR    FDCAN      LL_APB2_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SAI2
  *         @arg @ref LL_APB2_GRP1_PERIPH_DFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_ADFSDM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_FDCAN
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB2LPENCLRR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB3 APB3
  * @{
  */

/**
  * @brief  Enable APB3 peripherals clock.
  * @rmtoll MP_APB3ENSETR      LPTIM2     LL_APB3_GRP1_EnableClock\n
  *         MP_APB3ENSETR      LPTIM3     LL_APB3_GRP1_EnableClock\n
  *         MP_APB3ENSETR      LPTIM4     LL_APB3_GRP1_EnableClock\n
  *         MP_APB3ENSETR      LPTIM5     LL_APB3_GRP1_EnableClock\n
  *         MP_APB3ENSETR      VREF       LL_APB3_GRP1_EnableClock\n
  *         MP_APB3ENSETR      TMPSENS    LL_APB3_GRP1_EnableClock\n
  *         MP_APB3ENSETR      HDP        LL_APB3_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_TMPSENS
  *         @arg @ref LL_APB3_GRP1_PERIPH_HDP
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB3ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB3ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB3 peripheral clock is enabled or not
  * @rmtoll MP_APB3ENSETR      LPTIM2      LL_APB3_GRP1_IsEnabledClock\n
  *         MP_APB3ENSETR      LPTIM3      LL_APB3_GRP1_IsEnabledClock\n
  *         MP_APB3ENSETR      LPTIM4      LL_APB3_GRP1_IsEnabledClock\n
  *         MP_APB3ENSETR      LPTIM5      LL_APB3_GRP1_IsEnabledClock\n
  *         MP_APB3ENSETR      VREF        LL_APB3_GRP1_IsEnabledClock\n
  *         MP_APB3ENSETR      TMPSENS     LL_APB3_GRP1_IsEnabledClock\n
  *         MP_APB3ENSETR      HDP         LL_APB3_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_TMPSENS
  *         @arg @ref LL_APB3_GRP1_PERIPH_HDP
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_APB3ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB3 peripherals clock.
  * @rmtoll MP_APB3ENCLRR      LPTIM2      LL_APB3_GRP1_DisableClock\n
  *         MP_APB3ENCLRR      LPTIM3      LL_APB3_GRP1_DisableClock\n
  *         MP_APB3ENCLRR      LPTIM4      LL_APB3_GRP1_DisableClock\n
  *         MP_APB3ENCLRR      LPTIM5      LL_APB3_GRP1_DisableClock\n
  *         MP_APB3ENCLRR      VREF        LL_APB3_GRP1_DisableClock\n
  *         MP_APB3ENCLRR      TMPSENS     LL_APB3_GRP1_DisableClock\n
  *         MP_APB3ENCLRR      HDP         LL_APB3_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_TMPSENS
  *         @arg @ref LL_APB3_GRP1_PERIPH_HDP
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB3ENCLRR, Periphs);
}

/**
  * @brief  Force APB3 peripherals reset.
  * @rmtoll APB3RSTSETR     LPTIM2      LL_APB3_GRP1_ForceReset\n
  *         APB3RSTSETR     LPTIM3      LL_APB3_GRP1_ForceReset\n
  *         APB3RSTSETR     LPTIM4      LL_APB3_GRP1_ForceReset\n
  *         APB3RSTSETR     LPTIM5      LL_APB3_GRP1_ForceReset\n
  *         APB3RSTSETR     SYSCFG      LL_APB3_GRP1_ForceReset\n
  *         APB3RSTSETR     VREF        LL_APB3_GRP1_ForceReset\n
  *         APB3RSTSETR     TMPSENS     LL_APB3_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_TMPSENS
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_ForceReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB3RSTSETR, Periphs);
}

/**
  * @brief  Release APB3 peripherals reset.
  * @rmtoll APB3RSTCLRR     LPTIM2       LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTCLRR     LPTIM3       LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTCLRR     LPTIM4       LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTCLRR     LPTIM5       LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTCLRR     SYSCFG       LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTCLRR     VREF         LL_APB3_GRP1_ReleaseReset\n
  *         APB3RSTCLRR     TMPSENS      LL_APB3_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB3_GRP1_PERIPH_SYSCFG
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_TMPSENS
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB3RSTCLRR, Periphs);
}

/**
  * @brief  Enable APB3 peripheral clocks in Sleep mode
  * @rmtoll MP_APB3LPENSETR    LPTIM2       LL_APB3_GRP1_EnableClockSleep\n
  *         MP_APB3LPENSETR    LPTIM3       LL_APB3_GRP1_EnableClockSleep\n
  *         MP_APB3LPENSETR    LPTIM4       LL_APB3_GRP1_EnableClockSleep\n
  *         MP_APB3LPENSETR    LPTIM5       LL_APB3_GRP1_EnableClockSleep\n
  *         MP_APB3LPENSETR    VREF         LL_APB3_GRP1_EnableClockSleep\n
  *         MP_APB3LPENSETR    TMPSENS      LL_APB3_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_TMPSENS
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB3LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB3LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB3 peripheral clocks in Sleep mode
  * @rmtoll MP_APB3LPENCLRR    LPTIM2      LL_APB3_GRP1_DisableClockSleep\n
  *         MP_APB3LPENCLRR    LPTIM3      LL_APB3_GRP1_DisableClockSleep\n
  *         MP_APB3LPENCLRR    LPTIM4      LL_APB3_GRP1_DisableClockSleep\n
  *         MP_APB3LPENCLRR    LPTIM5      LL_APB3_GRP1_DisableClockSleep\n
  *         MP_APB3LPENCLRR    VREF        LL_APB3_GRP1_DisableClockSleep\n
  *         MP_APB3LPENCLRR    TMPSENS     LL_APB3_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREF
  *         @arg @ref LL_APB3_GRP1_PERIPH_TMPSENS
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB3LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB3_S APB3_S
  * @{
  */

/**
  * @brief  Enable secure APB3 peripherals clock.
  * @rmtoll MP_S_APB3ENSETR      SYSCFG     LL_APB3_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_S_GRP1_PERIPH_SYSCFG
  * @retval None
  */
__STATIC_INLINE void LL_APB3_S_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_S_APB3ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_S_APB3ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if secure APB3 peripheral clock is enabled or not
  * @rmtoll MP_S_APB3ENSETR      SYSCFG      LL_APB3_S_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_S_GRP1_PERIPH_SYSCFG
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_S_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_S_APB3ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable secure APB3 peripherals clock.
  * @rmtoll MP_S_APB3ENCLRR      SYSCFG      LL_APB3_S_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_S_GRP1_PERIPH_SYSCFG
  * @retval None
  */
__STATIC_INLINE void LL_APB3_S_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_S_APB3ENCLRR, Periphs);
}

/**
  * @brief  Enable secure APB3 peripheral clocks in Sleep mode
  * @rmtoll MP_S_APB3LPENSETR    SYSCFG       LL_APB3_S_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_S_GRP1_PERIPH_SYSCFG
  * @retval None
  */
__STATIC_INLINE void LL_APB3_S_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_S_APB3LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_S_APB3LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable secure APB3 peripheral clocks in Sleep mode
  * @rmtoll MP_S_APB3LPENCLRR    SYSCFG      LL_APB3_S_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_S_GRP1_PERIPH_SYSCFG
  * @retval None
  */
__STATIC_INLINE void LL_APB3_S_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_S_APB3LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB3_NS APB3_NS
  * @{
  */

/**
  * @brief  Enable non secure APB3 peripherals clock.
  * @rmtoll MP_NS_APB3ENSETR      SYSCFG     LL_APB3_NS_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_S_GRP1_PERIPH_SYSCFG
  * @retval None
  */
__STATIC_INLINE void LL_APB3_NS_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_NS_APB3ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_NS_APB3ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if non secure APB3 peripheral clock is enabled or not
  * @rmtoll MP_NS_APB3ENSETR      SYSCFG      LL_APB3_NS_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_S_GRP1_PERIPH_SYSCFG
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_NS_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_NS_APB3ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable non secure APB3 peripherals clock.
  * @rmtoll MP_NS_APB3ENCLRR      SYSCFG      LL_APB3_NS_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_S_GRP1_PERIPH_SYSCFG
  * @retval None
  */
__STATIC_INLINE void LL_APB3_NS_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_NS_APB3ENCLRR, Periphs);
}

/**
  * @brief  Enable non secure APB3 peripheral clocks in Sleep mode
  * @rmtoll MP_NS_APB3LPENSETR    SYSCFG       LL_APB3_NS_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_S_GRP1_PERIPH_SYSCFG
  * @retval None
  */
__STATIC_INLINE void LL_APB3_NS_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_NS_APB3LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_NS_APB3LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable non secure APB3 peripheral clocks in Sleep mode
  * @rmtoll MP_NS_APB3LPENCLRR    SYSCFG      LL_APB3_NS_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_S_GRP1_PERIPH_SYSCFG
  * @retval None
  */
__STATIC_INLINE void LL_APB3_NS_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_NS_APB3LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB4 APB4
  * @{
  */

/**
  * @brief  Enable APB4 peripherals clock.
  * @rmtoll MP_APB4ENSETR      DCMIPP       LL_APB4_GRP1_EnableClock\n
  *         MP_APB4ENSETR      DDRPERFM     LL_APB4_GRP1_EnableClock\n
  *         MP_APB4ENSETR      IWDG2        LL_APB4_GRP1_EnableClock\n
  *         MP_APB4ENSETR      USBPHY       LL_APB4_GRP1_EnableClock\n
  *         MP_APB4ENSETR      STGENRO      LL_APB4_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB4_GRP1_PERIPH_DDRPERFM
  *         @arg @ref LL_APB4_GRP1_PERIPH_IWDG2
  *         @arg @ref LL_APB4_GRP1_PERIPH_USBPHY
  *         @arg @ref LL_APB4_GRP1_PERIPH_STGENRO
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB4ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB4ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB4 peripheral clock is enabled or not
  * @rmtoll MP_APB4ENSETR      DCMIPP        LL_APB4_GRP1_IsEnabledClock\n
  *         MP_APB4ENSETR      DDRPERFM      LL_APB4_GRP1_IsEnabledClock\n
  *         MP_APB4ENSETR      IWDG2         LL_APB4_GRP1_IsEnabledClock\n
  *         MP_APB4ENSETR      USBPHY        LL_APB4_GRP1_IsEnabledClock\n
  *         MP_APB4ENSETR      STGENRO       LL_APB4_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB4_GRP1_PERIPH_DDRPERFM
  *         @arg @ref LL_APB4_GRP1_PERIPH_IWDG2
  *         @arg @ref LL_APB4_GRP1_PERIPH_USBPHY
  *         @arg @ref LL_APB4_GRP1_PERIPH_STGENRO
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB4_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_APB4ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB4 peripherals clock.
  * @rmtoll MP_APB4ENCLRR      DCMIPP        LL_APB4_GRP1_DisableClock\n
  *         MP_APB4ENCLRR      DDRPERFM      LL_APB4_GRP1_DisableClock\n
  *         MP_APB4ENCLRR      IWDG2         LL_APB4_GRP1_DisableClock\n
  *         MP_APB4ENCLRR      USBPHY        LL_APB4_GRP1_DisableClock\n
  *         MP_APB4ENCLRR      STGENRO       LL_APB4_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB4_GRP1_PERIPH_DDRPERFM
  *         @arg @ref LL_APB4_GRP1_PERIPH_IWDG2
  *         @arg @ref LL_APB4_GRP1_PERIPH_USBPHY
  *         @arg @ref LL_APB4_GRP1_PERIPH_STGENRO
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB4ENCLRR, Periphs);
}

/**
  * @brief  Force APB4 peripherals reset.
  * @rmtoll APB4RSTSETR     LTDC           LL_APB4_GRP1_ForceReset\n
  *         APB4RSTSETR     DCMIPP         LL_APB4_GRP1_ForceReset\n
  *         APB4RSTSETR     DDRPERFM       LL_APB4_GRP1_ForceReset\n
  *         APB4RSTSETR     USBPHY         LL_APB4_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB4_S_GRP1_PERIPH_LTDC
  *         @arg @ref LL_APB4_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB4_GRP1_PERIPH_DDRPERFM
  *         @arg @ref LL_APB4_GRP1_PERIPH_USBPHY
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_ForceReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB4RSTSETR, Periphs);
}

/**
  * @brief  Release APB4 peripherals reset.
  * @rmtoll APB4RSTCLRR     LTDC           LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTCLRR     DCMIPP         LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTCLRR     DDRPERFM       LL_APB4_GRP1_ReleaseReset\n
  *         APB4RSTCLRR     USBPHY         LL_APB4_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB4_S_GRP1_PERIPH_LTDC
  *         @arg @ref LL_APB4_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB4_GRP1_PERIPH_DDRPERFM
  *         @arg @ref LL_APB4_GRP1_PERIPH_USBPHY
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_ReleaseReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB4RSTCLRR, Periphs);
}

/**
  * @brief  Enable APB4 peripheral clocks in Sleep mode
  * @rmtoll MP_APB4LPENSETR    DCMIPP         LL_APB4_GRP1_EnableClockSleep\n
  *         MP_APB4LPENSETR    DDRPERFM       LL_APB4_GRP1_EnableClockSleep\n
  *         MP_APB4LPENSETR    IWDG2          LL_APB4_GRP1_EnableClockSleep\n
  *         MP_APB4LPENSETR    USBPHY         LL_APB4_GRP1_EnableClockSleep\n
  *         MP_APB4LPENSETR    STGENRO        LL_APB4_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB4_GRP1_PERIPH_DDRPERFM
  *         @arg @ref LL_APB4_GRP1_PERIPH_IWDG2
  *         @arg @ref LL_APB4_GRP1_PERIPH_USBPHY
  *         @arg @ref LL_APB4_GRP1_PERIPH_STGENRO
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB4LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB4LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB4 peripheral clocks in Sleep mode
  * @rmtoll MP_APB4LPENCLRR    DCMIPP        LL_APB4_GRP1_DisableClockSleep\n
  *         MP_APB4LPENCLRR    DDRPERFM      LL_APB4_GRP1_DisableClockSleep\n
  *         MP_APB4LPENCLRR    IWDG2         LL_APB4_GRP1_DisableClockSleep\n
  *         MP_APB4LPENCLRR    USBPHY        LL_APB4_GRP1_DisableClockSleep\n
  *         MP_APB4LPENCLRR    STGENRO       LL_APB4_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_DCMIPP
  *         @arg @ref LL_APB4_GRP1_PERIPH_DDRPERFM
  *         @arg @ref LL_APB4_GRP1_PERIPH_IWDG2
  *         @arg @ref LL_APB4_GRP1_PERIPH_USBPHY
  *         @arg @ref LL_APB4_GRP1_PERIPH_STGENRO
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB4LPENCLRR, Periphs);
}

/**
  * @brief  Enable APB4 peripheral clocks in Stop mode
  * @rmtoll MP_APB4LPENSETR    STGENROSTPEN           LL_APB4_GRP1_EnableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_STGENROSTP
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_EnableClockStop(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB4LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB4LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB4 peripheral clocks in Stop modes
  * @rmtoll MP_APB4LPENCLRR    STGENROSTPEN          LL_APB4_GRP1_DisableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_STGENROSTP
  * @retval None
  */
__STATIC_INLINE void LL_APB4_GRP1_DisableClockStop(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB4LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB4_S APB4_S
  * @{
  */

/**
  * @brief  Enable secure APB4 peripherals clock.
  * @rmtoll MP_S_APB4ENSETR      LTDC         LL_APB4_S_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_S_GRP1_PERIPH_LTDC
  * @retval None
  */
__STATIC_INLINE void LL_APB4_S_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_S_APB4ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_S_APB4ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if secure APB4 peripheral clock is enabled or not
  * @rmtoll MP_S_APB4ENSETR      LTDC          LL_APB4_S_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB4_S_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_S_APB4ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable secure APB4 peripherals clock.
  * @rmtoll MP_S_APB4ENCLRR      LTDC          LL_APB4_S_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_S_GRP1_PERIPH_LTDC
  * @retval None
  */
__STATIC_INLINE void LL_APB4_S_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_S_APB4ENCLRR, Periphs);
}

/**
  * @brief  Enable secure APB4 peripheral clocks in Sleep mode
  * @rmtoll MP_S_APB4LPENSETR    LTDC           LL_APB4_S_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_S_GRP1_PERIPH_LTDC
  * @retval None
  */
__STATIC_INLINE void LL_APB4_S_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_S_APB4LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_S_APB4LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable secure APB4 peripheral clocks in Sleep mode
  * @rmtoll MP_S_APB4LPENCLRR    LTDC          LL_APB4_S_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_S_GRP1_PERIPH_LTDC
  * @retval None
  */
__STATIC_INLINE void LL_APB4_S_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_S_APB4LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB4_NS APB4_NS
  * @{
  */

/**
  * @brief  Enable non secure APB4 peripherals clock.
  * @rmtoll MP_NS_APB4ENSETR      LTDC         LL_APB4_NS_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_NS_GRP1_PERIPH_LTDC
  * @retval None
  */
__STATIC_INLINE void LL_APB4_NS_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_NS_APB4ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_NS_APB4ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if non secure APB4 peripheral clock is enabled or not
  * @rmtoll MP_NS_APB4ENSETR      LTDC          LL_APB4_NS_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB4_NS_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_NS_APB4ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable non secure APB4 peripherals clock.
  * @rmtoll MP_NS_APB4ENCLRR      LTDC          LL_APB4_NS_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_NS_GRP1_PERIPH_LTDC
  * @retval None
  */
__STATIC_INLINE void LL_APB4_NS_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_NS_APB4ENCLRR, Periphs);
}

/**
  * @brief  Enable non secure APB4 peripheral clocks in Sleep mode
  * @rmtoll MP_NS_APB4LPENSETR    LTDC           LL_APB4_NS_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_NS_GRP1_PERIPH_LTDC
  * @retval None
  */
__STATIC_INLINE void LL_APB4_NS_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_NS_APB4LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_NS_APB4LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable non secure APB4 peripheral clocks in Sleep mode
  * @rmtoll MP_NS_APB4LPENCLRR    LTDC          LL_APB4_NS_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_NS_GRP1_PERIPH_LTDC
  * @retval None
  */
__STATIC_INLINE void LL_APB4_NS_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_NS_APB4LPENCLRR, Periphs);
}
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB5 APB5
  * @{
  */

/**
  * @brief  Enable APB5 peripherals clock.
  * @rmtoll MP_APB5ENSETR      RTCAPB       LL_APB5_GRP1_EnableClock\n
  *         MP_APB5ENSETR      TZC          LL_APB5_GRP1_EnableClock\n
  *         MP_APB5ENSETR      ETZC         LL_APB5_GRP1_EnableClock\n
  *         MP_APB5ENSETR      IWDG1        LL_APB5_GRP1_EnableClock\n
  *         MP_APB5ENSETR      BSEC         LL_APB5_GRP1_EnableClock\n
  *         MP_APB5ENSETR      STGENC       LL_APB5_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB5_GRP1_PERIPH_TZC
  *         @arg @ref LL_APB5_GRP1_PERIPH_ETZPC
  *         @arg @ref LL_APB5_GRP1_PERIPH_IWDG1
  *         @arg @ref LL_APB5_GRP1_PERIPH_BSEC
  *         @arg @ref LL_APB5_GRP1_PERIPH_STGEN
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB5ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB5ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB5 peripheral clock is enabled or not
  * @rmtoll MP_APB5ENSETR      RTCAPB       LL_APB5_GRP1_IsEnabledClock\n
  *         MP_APB5ENSETR      TZC          LL_APB5_GRP1_IsEnabledClock\n
  *         MP_APB5ENSETR      ETZC         LL_APB5_GRP1_IsEnabledClock\n
  *         MP_APB5ENSETR      IWDG1        LL_APB5_GRP1_IsEnabledClock\n
  *         MP_APB5ENSETR      BSEC         LL_APB5_GRP1_IsEnabledClock\n
  *         MP_APB5ENSETR      STGENC       LL_APB5_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB5_GRP1_PERIPH_TZC
  *         @arg @ref LL_APB5_GRP1_PERIPH_ETZPC
  *         @arg @ref LL_APB5_GRP1_PERIPH_IWDG1
  *         @arg @ref LL_APB5_GRP1_PERIPH_BSEC
  *         @arg @ref LL_APB5_GRP1_PERIPH_STGEN
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB5_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_APB5ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB5 peripherals clock.
  * @rmtoll MP_APB5ENSETR      RTCAPB       LL_APB5_GRP1_DisableClock\n
  *         MP_APB5ENSETR      TZC          LL_APB5_GRP1_DisableClock\n
  *         MP_APB5ENSETR      ETZC         LL_APB5_GRP1_DisableClock\n
  *         MP_APB5ENSETR      IWDG1        LL_APB5_GRP1_DisableClock\n
  *         MP_APB5ENSETR      BSEC         LL_APB5_GRP1_DisableClock\n
  *         MP_APB5ENSETR      STGENC       LL_APB5_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB5_GRP1_PERIPH_TZC
  *         @arg @ref LL_APB5_GRP1_PERIPH_ETZPC
  *         @arg @ref LL_APB5_GRP1_PERIPH_IWDG1
  *         @arg @ref LL_APB5_GRP1_PERIPH_BSEC
  *         @arg @ref LL_APB5_GRP1_PERIPH_STGEN
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB5ENCLRR, Periphs);
}

/**
  * @brief  Force APB5 peripherals reset.
  * @rmtoll MP_APB5LPENSETR    STGENC       LL_APB5_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB5_GRP1_PERIPH_STGEN
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_ForceReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB5RSTSETR, Periphs);
}

/**
  * @brief  Release APB5 peripherals reset.
  * @rmtoll MP_APB5LPENSETR    STGENC       LL_APB5_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB5_GRP1_PERIPH_STGEN
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_ReleaseReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB5RSTCLRR, Periphs);
}

/**
  * @brief  Enable APB5 peripheral clocks in Sleep mode
  * @rmtoll MP_APB5ENSETR      RTCAPB       LL_APB5_GRP1_EnableClockSleep\n
  *         MP_APB5ENSETR      TZC          LL_APB5_GRP1_EnableClockSleep\n
  *         MP_APB5ENSETR      ETZC         LL_APB5_GRP1_EnableClockSleep\n
  *         MP_APB5ENSETR      IWDG1        LL_APB5_GRP1_EnableClockSleep\n
  *         MP_APB5ENSETR      BSEC         LL_APB5_GRP1_EnableClockSleep\n
  *         MP_APB5ENSETR      STGENC       LL_APB5_GRP1_EnableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB5_GRP1_PERIPH_TZC
  *         @arg @ref LL_APB5_GRP1_PERIPH_ETZPC
  *         @arg @ref LL_APB5_GRP1_PERIPH_IWDG1
  *         @arg @ref LL_APB5_GRP1_PERIPH_BSEC
  *         @arg @ref LL_APB5_GRP1_PERIPH_STGEN
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB5LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB5LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB5 peripheral clocks in Sleep mode
  * @rmtoll MP_APB5ENSETR      RTCAPB       LL_APB5_GRP1_DisableClockSleep\n
  *         MP_APB5ENSETR      TZC          LL_APB5_GRP1_DisableClockSleep\n
  *         MP_APB5ENSETR      ETZC         LL_APB5_GRP1_DisableClockSleep\n
  *         MP_APB5ENSETR      IWDG1        LL_APB5_GRP1_DisableClockSleep\n
  *         MP_APB5ENSETR      BSEC         LL_APB5_GRP1_DisableClockSleep\n
  *         MP_APB5ENSETR      STGENC       LL_APB5_GRP1_DisableClockSleep\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB5_GRP1_PERIPH_TZC
  *         @arg @ref LL_APB5_GRP1_PERIPH_ETZPC
  *         @arg @ref LL_APB5_GRP1_PERIPH_IWDG1
  *         @arg @ref LL_APB5_GRP1_PERIPH_BSEC
  *         @arg @ref LL_APB5_GRP1_PERIPH_STGEN
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB5LPENCLRR, Periphs);
}

/**
  * @brief  Enable APB5 peripheral clocks in Stop mode
  * @rmtoll MP_APB5LPENSETR    STGENCSTPEN           LL_APB5_GRP1_EnableClockStop
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_STGENSTP
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_EnableClockStop(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB5LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB5LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB5 peripheral clocks in Stop modes
  * @rmtoll MP_APB5LPENCLRR    STGENCSTPEN          LL_APB5_GRP1_DisableClockStop\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB5_GRP1_PERIPH_STGENSTP
  * @retval None
  */
__STATIC_INLINE void LL_APB5_GRP1_DisableClockStop(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB5LPENCLRR, Periphs);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB6 APB6
  * @{
  */

/**
  * @brief  Enable APB6 peripherals clock.
  * @rmtoll MP_APB6ENSETR      USART1        LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      USART2        LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      SPI4          LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      SPI5          LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      I2C3          LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      I2C4          LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      I2C5          LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      TIM12         LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      TIM13         LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      TIM14         LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      TIM15         LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      TIM16         LL_APB6_GRP1_EnableClock\n
  *         MP_APB6ENSETR      TIM17         LL_APB6_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C5
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB6_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB6ENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB6ENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB6 peripheral clock is enabled or not
  * @rmtoll MP_APB6ENSETR      USART1        LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      USART2        LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      SPI4          LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      SPI5          LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      I2C3          LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      I2C4          LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      I2C5          LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      TIM12         LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      TIM13         LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      TIM14         LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      TIM15         LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      TIM16         LL_APB6_GRP1_IsEnabledClock\n
  *         MP_APB6ENSETR      TIM17         LL_APB6_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C5
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM17
  * @retval State of Periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB6_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return ((READ_BIT(RCC->MP_APB6ENSETR, Periphs) == Periphs) ? 1U : 0U);
}

/**
  * @brief  Disable APB6 peripherals clock.
  * @rmtoll MP_APB6ENCLRR      USART1        LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      USART2        LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      SPI4          LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      SPI5          LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      I2C3          LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      I2C4          LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      I2C5          LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      TIM12         LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      TIM13         LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      TIM14         LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      TIM15         LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      TIM16         LL_APB6_GRP1_DisableClock\n
  *         MP_APB6ENCLRR      TIM17         LL_APB6_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C5
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB6_GRP1_DisableClock(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB6ENCLRR, Periphs);
}

/**
  * @brief  Force APB6 peripherals reset.
  * @rmtoll APB6RSTSETR      USART1        LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      USART2        LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      SPI4          LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      SPI5          LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      I2C3          LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      I2C4          LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      I2C5          LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      TIM12         LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      TIM13         LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      TIM14         LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      TIM15         LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      TIM16         LL_APB6_GRP1_ForceReset\n
  *         APB6RSTSETR      TIM17         LL_APB6_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB6_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C5
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB6_GRP1_ForceReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB6RSTSETR, Periphs);
}

/**
  * @brief  Release APB6 peripherals reset.
  * @rmtoll APB6RSTCLRR      USART1        LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      USART2        LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      SPI4          LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      SPI5          LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      I2C3          LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      I2C4          LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      I2C5          LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      TIM12         LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      TIM13         LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      TIM14         LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      TIM15         LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      TIM16         LL_APB6_GRP1_ReleaseReset\n
  *         APB6RSTCLRR      TIM17         LL_APB6_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB6_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C5
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB6_GRP1_ReleaseReset(uint32_t Periphs)
{
  WRITE_REG(RCC->APB6RSTCLRR, Periphs);
}

/**
  * @brief  Enable APB6 peripheral clocks in Sleep mode
  * @rmtoll MP_APB6LPENSETR      USART1        LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      USART2        LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      SPI4          LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      SPI5          LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      I2C3          LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      I2C4          LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      I2C5          LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      TIM12         LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      TIM13         LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      TIM14         LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      TIM15         LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      TIM16         LL_APB6_GRP1_EnableClockSleep\n
  *         MP_APB6LPENSETR      TIM17         LL_APB6_GRP1_EnableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C5
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB6_GRP1_EnableClockSleep(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  WRITE_REG(RCC->MP_APB6LPENSETR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->MP_APB6LPENSETR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Disable APB6 peripheral clocks in Sleep mode
  * @rmtoll MP_APB6LPENCLRR      USART1        LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      USART2        LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      SPI4          LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      SPI5          LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      I2C3          LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      I2C4          LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      I2C5          LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      TIM12         LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      TIM13         LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      TIM14         LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      TIM15         LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      TIM16         LL_APB6_GRP1_DisableClockSleep\n
  *         MP_APB6LPENCLRR      TIM17         LL_APB6_GRP1_DisableClockSleep
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB6_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB6_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C4
  *         @arg @ref LL_APB6_GRP1_PERIPH_I2C5
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB6_GRP1_PERIPH_TIM17
  * @retval None
  */
__STATIC_INLINE void LL_APB6_GRP1_DisableClockSleep(uint32_t Periphs)
{
  WRITE_REG(RCC->MP_APB6LPENCLRR, Periphs);
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

#endif /* defined(RCC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP13xx_LL_BUS_H */
