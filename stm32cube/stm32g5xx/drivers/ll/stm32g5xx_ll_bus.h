/**
  ******************************************************************************
  * @file    stm32g5xx_ll_bus.h
  * @brief   Header file of LL BUS module.

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
  @verbatim
                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling must be taken into account in order to manage the peripheral read/write
      from/to registers.
      (+) This delay depends on the peripheral mapping.
        (++) AHB, APB peripherals, one dummy read is necessary

    [..]
      Workarounds:
      (#) For AHB, APB peripherals, a dummy read of the peripheral register has been
          inserted in each LL_{BUS}_GRP{x}_EnableClock() function.

  @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G5XX_LL_BUS_H
#define STM32G5XX_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup BUS_LL BUS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Constants LL BUS Constants
  * @{
  */

/** @defgroup BUS_LL_EC_AHB1_GRP1_PERIPH  AHB1 GRP1 PERIPH
  * @{
  */
#define LL_AHB1_GRP1_PERIPH_ALL     0xFFFFFFFFU
#define LL_AHB1_GRP1_PERIPH_GPDMA1  RCC_AHB1ENR_GPDMA1EN
#define LL_AHB1_GRP1_PERIPH_GPDMA2  RCC_AHB1ENR_GPDMA2EN
#define LL_AHB1_GRP1_PERIPH_FLASH   RCC_AHB1ENR_FLASHEN
#define LL_AHB1_GRP1_PERIPH_CRC     RCC_AHB1ENR_CRCEN
#define LL_AHB1_GRP1_PERIPH_CORDIC1 RCC_AHB1ENR_CORDIC1EN
#define LL_AHB1_GRP1_PERIPH_FMAC1   RCC_AHB1ENR_FMAC1EN
#define LL_AHB1_GRP1_PERIPH_RAMCFG  RCC_AHB1ENR_RAMCFGEN
#define LL_AHB1_GRP1_PERIPH_TZSC1   RCC_AHB1ENR_TZSC1EN
#define LL_AHB1_GRP1_PERIPH_SRAM2   RCC_AHB1ENR_SRAM2EN
#if defined(SRAM3_BASE)
#define LL_AHB1_GRP1_PERIPH_SRAM3  RCC_AHB1ENR_SRAM3EN
#else
#define LL_AHB1_GRP1_PERIPH_SRAM3  0
#endif /* SRAM3_BASE */
#define LL_AHB1_GRP1_PERIPH_ICACHE RCC_AHB1LPENR_ICACHELPEN
#if defined(DCACHE)
#define LL_AHB1_GRP1_PERIPH_DCACHE RCC_AHB1ENR_DCACHEEN
#else
#define LL_AHB1_GRP1_PERIPH_DCACHE      0
#endif /* DCACHE */
#define LL_AHB1_GRP1_PERIPH_SRAM1       RCC_AHB1ENR_SRAM1EN
#define LL_AHB1_GRP1_PERIPH_ALL_EN_MASK (LL_AHB1_GRP1_PERIPH_GPDMA1  | \
                                         LL_AHB1_GRP1_PERIPH_GPDMA2  | \
                                         LL_AHB1_GRP1_PERIPH_FLASH   | \
                                         LL_AHB1_GRP1_PERIPH_CRC     | \
                                         LL_AHB1_GRP1_PERIPH_CORDIC1 | \
                                         LL_AHB1_GRP1_PERIPH_FMAC1   | \
                                         LL_AHB1_GRP1_PERIPH_RAMCFG  | \
                                         LL_AHB1_GRP1_PERIPH_TZSC1   | \
                                         LL_AHB1_GRP1_PERIPH_SRAM2   | \
                                         LL_AHB1_GRP1_PERIPH_SRAM3   | \
                                         LL_AHB1_GRP1_PERIPH_DCACHE  | \
                                         LL_AHB1_GRP1_PERIPH_SRAM1)

#define LL_AHB1_GRP1_PERIPH_ALL_LPEN_MASK (LL_AHB1_GRP1_PERIPH_GPDMA1  | \
                                           LL_AHB1_GRP1_PERIPH_GPDMA2  | \
                                           LL_AHB1_GRP1_PERIPH_FLASH   | \
                                           LL_AHB1_GRP1_PERIPH_CRC     | \
                                           LL_AHB1_GRP1_PERIPH_CORDIC1 | \
                                           LL_AHB1_GRP1_PERIPH_FMAC1   | \
                                           LL_AHB1_GRP1_PERIPH_RAMCFG  | \
                                           LL_AHB1_GRP1_PERIPH_TZSC1   | \
                                           LL_AHB1_GRP1_PERIPH_SRAM2   | \
                                           LL_AHB1_GRP1_PERIPH_SRAM3   | \
                                           LL_AHB1_GRP1_PERIPH_ICACHE  | \
                                           LL_AHB1_GRP1_PERIPH_DCACHE  | \
                                           LL_AHB1_GRP1_PERIPH_SRAM1)

#define LL_AHB1_GRP1_PERIPH_ALL_RST_MASK (LL_AHB1_GRP1_PERIPH_GPDMA1  | \
                                          LL_AHB1_GRP1_PERIPH_GPDMA2  | \
                                          LL_AHB1_GRP1_PERIPH_CRC     | \
                                          LL_AHB1_GRP1_PERIPH_CORDIC1 | \
                                          LL_AHB1_GRP1_PERIPH_FMAC1   | \
                                          LL_AHB1_GRP1_PERIPH_RAMCFG)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB2_GRP1_PERIPH  AHB2 GRP1 PERIPH
  * @{
  */
#define LL_AHB2_GRP1_PERIPH_ALL   0xFFFFFFFFU
#define LL_AHB2_GRP1_PERIPH_DAC1  RCC_AHB2ENR_DAC1EN
#define LL_AHB2_GRP1_PERIPH_DAC2  RCC_AHB2ENR_DAC2EN
#define LL_AHB2_GRP1_PERIPH_DAC5  RCC_AHB2ENR_DAC5EN
#define LL_AHB2_GRP1_PERIPH_DAC6  RCC_AHB2ENR_DAC6EN
#define LL_AHB2_GRP1_PERIPH_DAC7  RCC_AHB2ENR_DAC7EN
#define LL_AHB2_GRP1_PERIPH_DAC8  RCC_AHB2ENR_DAC8EN
#define LL_AHB2_GRP1_PERIPH_DAC9  RCC_AHB2ENR_DAC9EN
#define LL_AHB2_GRP1_PERIPH_DAC10 RCC_AHB2ENR_DAC10EN
#if defined(FMAC2)
#define LL_AHB2_GRP1_PERIPH_FMAC2 RCC_AHB2ENR_FMAC2EN
#else
#define LL_AHB2_GRP1_PERIPH_FMAC2 0
#endif /* FMAC2 */
#define LL_AHB2_GRP1_PERIPH_ADC12 RCC_AHB2ENR_ADC12EN
#if defined(ADC3)
#define LL_AHB2_GRP1_PERIPH_ADC3  RCC_AHB2ENR_ADC3EN
#else
#define LL_AHB2_GRP1_PERIPH_ADC3        0
#endif /* ADC3 */
#define LL_AHB2_GRP1_PERIPH_ALL_EN_MASK (LL_AHB2_GRP1_PERIPH_DAC1  | \
                                         LL_AHB2_GRP1_PERIPH_DAC2  | \
                                         LL_AHB2_GRP1_PERIPH_DAC5  | \
                                         LL_AHB2_GRP1_PERIPH_DAC6  | \
                                         LL_AHB2_GRP1_PERIPH_DAC7  | \
                                         LL_AHB2_GRP1_PERIPH_DAC8  | \
                                         LL_AHB2_GRP1_PERIPH_DAC9  | \
                                         LL_AHB2_GRP1_PERIPH_DAC10 | \
                                         LL_AHB2_GRP1_PERIPH_FMAC2 | \
                                         LL_AHB2_GRP1_PERIPH_ADC12 | \
                                         LL_AHB2_GRP1_PERIPH_ADC3)

#define LL_AHB2_GRP1_PERIPH_ALL_LPEN_MASK (LL_AHB2_GRP1_PERIPH_DAC1  | \
                                           LL_AHB2_GRP1_PERIPH_DAC2  | \
                                           LL_AHB2_GRP1_PERIPH_DAC5  | \
                                           LL_AHB2_GRP1_PERIPH_DAC6  | \
                                           LL_AHB2_GRP1_PERIPH_DAC7  | \
                                           LL_AHB2_GRP1_PERIPH_DAC8  | \
                                           LL_AHB2_GRP1_PERIPH_DAC9  | \
                                           LL_AHB2_GRP1_PERIPH_DAC10 | \
                                           LL_AHB2_GRP1_PERIPH_FMAC2 | \
                                           LL_AHB2_GRP1_PERIPH_ADC12 | \
                                           LL_AHB2_GRP1_PERIPH_ADC3)

#define LL_AHB2_GRP1_PERIPH_ALL_RST_MASK (LL_AHB2_GRP1_PERIPH_DAC1  | \
                                          LL_AHB2_GRP1_PERIPH_DAC2  | \
                                          LL_AHB2_GRP1_PERIPH_DAC5  | \
                                          LL_AHB2_GRP1_PERIPH_DAC6  | \
                                          LL_AHB2_GRP1_PERIPH_DAC7  | \
                                          LL_AHB2_GRP1_PERIPH_DAC8  | \
                                          LL_AHB2_GRP1_PERIPH_DAC9  | \
                                          LL_AHB2_GRP1_PERIPH_DAC10 | \
                                          LL_AHB2_GRP1_PERIPH_FMAC2 | \
                                          LL_AHB2_GRP1_PERIPH_ADC12 | \
                                          LL_AHB2_GRP1_PERIPH_ADC3)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB3_GRP1_PERIPH  AHB3 GRP1 PERIPH
  * @{
  */
#define LL_AHB3_GRP1_PERIPH_ALL         0xFFFFFFFFU
#define LL_AHB3_GRP1_PERIPH_DBG         RCC_AHB3ENR_DBGCKEN
#define LL_AHB3_GRP1_PERIPH_ALL_EN_MASK (LL_AHB3_GRP1_PERIPH_DBG)

#define LL_AHB3_GRP1_PERIPH_ALL_LPEN_MASK (LL_AHB3_GRP1_PERIPH_DBG)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB4_GRP1_PERIPH  AHB4 GRP1 PERIPH
  * @{
  */
#define LL_AHB4_GRP1_PERIPH_ALL         0xFFFFFFFFU
#if defined(AES)
#define LL_AHB4_GRP1_PERIPH_AES         RCC_AHB4ENR_AESEN
#else
#define LL_AHB4_GRP1_PERIPH_AES         0
#endif /* AES */
#define LL_AHB4_GRP1_PERIPH_HASH        RCC_AHB4ENR_HASHEN
#define LL_AHB4_GRP1_PERIPH_RNG         RCC_AHB4ENR_RNGEN
#define LL_AHB4_GRP1_PERIPH_PKA         RCC_AHB4ENR_PKAEN
#if defined(SAES)
#define LL_AHB4_GRP1_PERIPH_SAES        RCC_AHB4ENR_SAESEN
#else
#define LL_AHB4_GRP1_PERIPH_SAES        0
#endif /* SAES */
#if defined(CCB)
#define LL_AHB4_GRP1_PERIPH_CCB         RCC_AHB4ENR_CCBEN
#else
#define LL_AHB4_GRP1_PERIPH_CCB         0
#endif /* CCB */
#if defined(OTFDEC1)
#define LL_AHB4_GRP1_PERIPH_OTFDEC1     RCC_AHB4ENR_OTFDEC1EN
#else
#define LL_AHB4_GRP1_PERIPH_OTFDEC1     0
#endif /* OTFDEC1 */
#define LL_AHB4_GRP1_PERIPH_GPIOA       RCC_AHB4ENR_GPIOAEN
#define LL_AHB4_GRP1_PERIPH_GPIOB       RCC_AHB4ENR_GPIOBEN
#define LL_AHB4_GRP1_PERIPH_GPIOC       RCC_AHB4ENR_GPIOCEN
#define LL_AHB4_GRP1_PERIPH_GPIOD       RCC_AHB4ENR_GPIODEN
#define LL_AHB4_GRP1_PERIPH_GPIOE       RCC_AHB4ENR_GPIOEEN
#define LL_AHB4_GRP1_PERIPH_GPIOF       RCC_AHB4ENR_GPIOFEN
#define LL_AHB4_GRP1_PERIPH_GPIOG       RCC_AHB4ENR_GPIOGEN
#define LL_AHB4_GRP1_PERIPH_GPIOH       RCC_AHB4ENR_GPIOHEN
#if defined(XSPI1)
#define LL_AHB4_GRP1_PERIPH_XSPI1       RCC_AHB4ENR_XSPI1EN
#else
#define LL_AHB4_GRP1_PERIPH_XSPI1       0
#endif /* XSPI1 */
#define LL_AHB4_GRP1_PERIPH_ALL_EN_MASK (LL_AHB4_GRP1_PERIPH_AES     | \
                                         LL_AHB4_GRP1_PERIPH_HASH    | \
                                         LL_AHB4_GRP1_PERIPH_RNG     | \
                                         LL_AHB4_GRP1_PERIPH_PKA     | \
                                         LL_AHB4_GRP1_PERIPH_SAES    | \
                                         LL_AHB4_GRP1_PERIPH_CCB     | \
                                         LL_AHB4_GRP1_PERIPH_OTFDEC1 | \
                                         LL_AHB4_GRP1_PERIPH_GPIOA   | \
                                         LL_AHB4_GRP1_PERIPH_GPIOB   | \
                                         LL_AHB4_GRP1_PERIPH_GPIOC   | \
                                         LL_AHB4_GRP1_PERIPH_GPIOD   | \
                                         LL_AHB4_GRP1_PERIPH_GPIOE   | \
                                         LL_AHB4_GRP1_PERIPH_GPIOF   | \
                                         LL_AHB4_GRP1_PERIPH_GPIOG   | \
                                         LL_AHB4_GRP1_PERIPH_GPIOH   | \
                                         LL_AHB4_GRP1_PERIPH_XSPI1)

#define LL_AHB4_GRP1_PERIPH_ALL_LPEN_MASK (LL_AHB4_GRP1_PERIPH_AES     | \
                                           LL_AHB4_GRP1_PERIPH_HASH    | \
                                           LL_AHB4_GRP1_PERIPH_RNG     | \
                                           LL_AHB4_GRP1_PERIPH_PKA     | \
                                           LL_AHB4_GRP1_PERIPH_SAES    | \
                                           LL_AHB4_GRP1_PERIPH_CCB     | \
                                           LL_AHB4_GRP1_PERIPH_OTFDEC1 | \
                                           LL_AHB4_GRP1_PERIPH_GPIOA   | \
                                           LL_AHB4_GRP1_PERIPH_GPIOB   | \
                                           LL_AHB4_GRP1_PERIPH_GPIOC   | \
                                           LL_AHB4_GRP1_PERIPH_GPIOD   | \
                                           LL_AHB4_GRP1_PERIPH_GPIOE   | \
                                           LL_AHB4_GRP1_PERIPH_GPIOF   | \
                                           LL_AHB4_GRP1_PERIPH_GPIOG   | \
                                           LL_AHB4_GRP1_PERIPH_GPIOH   | \
                                           LL_AHB4_GRP1_PERIPH_XSPI1)

#define LL_AHB4_GRP1_PERIPH_ALL_RST_MASK (LL_AHB4_GRP1_PERIPH_AES     | \
                                          LL_AHB4_GRP1_PERIPH_HASH    | \
                                          LL_AHB4_GRP1_PERIPH_RNG     | \
                                          LL_AHB4_GRP1_PERIPH_PKA     | \
                                          LL_AHB4_GRP1_PERIPH_SAES    | \
                                          LL_AHB4_GRP1_PERIPH_CCB     | \
                                          LL_AHB4_GRP1_PERIPH_OTFDEC1 | \
                                          LL_AHB4_GRP1_PERIPH_GPIOA   | \
                                          LL_AHB4_GRP1_PERIPH_GPIOB   | \
                                          LL_AHB4_GRP1_PERIPH_GPIOC   | \
                                          LL_AHB4_GRP1_PERIPH_GPIOD   | \
                                          LL_AHB4_GRP1_PERIPH_GPIOE   | \
                                          LL_AHB4_GRP1_PERIPH_GPIOF   | \
                                          LL_AHB4_GRP1_PERIPH_GPIOG   | \
                                          LL_AHB4_GRP1_PERIPH_GPIOH   | \
                                          LL_AHB4_GRP1_PERIPH_XSPI1)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_ALL  0xFFFFFFFFU
#define LL_APB1_GRP1_PERIPH_TIM2 RCC_APB1LENR_TIM2EN
#if defined(TIM3)
#define LL_APB1_GRP1_PERIPH_TIM3 RCC_APB1LENR_TIM3EN
#else
#define LL_APB1_GRP1_PERIPH_TIM3  0
#endif /* TIM3 */
#define LL_APB1_GRP1_PERIPH_TIM6  RCC_APB1LENR_TIM6EN
#define LL_APB1_GRP1_PERIPH_TIM7  RCC_APB1LENR_TIM7EN
#define LL_APB1_GRP1_PERIPH_TIM9  RCC_APB1LENR_TIM9EN
#define LL_APB1_GRP1_PERIPH_TIM10 RCC_APB1LENR_TIM10EN
#define LL_APB1_GRP1_PERIPH_TIM11 RCC_APB1LENR_TIM11EN
#define LL_APB1_GRP1_PERIPH_TIM12 RCC_APB1LENR_TIM12EN
#define LL_APB1_GRP1_PERIPH_TIM13 RCC_APB1LENR_TIM13EN
#define LL_APB1_GRP1_PERIPH_TIM14 RCC_APB1LENR_TIM14EN
#define LL_APB1_GRP1_PERIPH_WWDG  RCC_APB1LENR_WWDGEN
#define LL_APB1_GRP1_PERIPH_SPI2  RCC_APB1LENR_SPI2EN
#if defined(SPI3)
#define LL_APB1_GRP1_PERIPH_SPI3  RCC_APB1LENR_SPI3EN
#else
#define LL_APB1_GRP1_PERIPH_SPI3   0
#endif /* SPI3 */
#define LL_APB1_GRP1_PERIPH_USART2 RCC_APB1LENR_USART2EN
#if defined(USART3)
#define LL_APB1_GRP1_PERIPH_USART3 RCC_APB1LENR_USART3EN
#else
#define LL_APB1_GRP1_PERIPH_USART3 0
#endif /* USART3 */
#define LL_APB1_GRP1_PERIPH_UART4  RCC_APB1LENR_UART4EN
#define LL_APB1_GRP1_PERIPH_UART5  RCC_APB1LENR_UART5EN
#define LL_APB1_GRP1_PERIPH_I2C1   RCC_APB1LENR_I2C1EN
#define LL_APB1_GRP1_PERIPH_I2C2   RCC_APB1LENR_I2C2EN
#define LL_APB1_GRP1_PERIPH_I3C1   RCC_APB1LENR_I3C1EN

#if defined(CRS)
#define LL_APB1_GRP1_PERIPH_CRS    RCC_APB1LENR_CRSEN
#else
#define LL_APB1_GRP1_PERIPH_CRS    0
#endif /* CRS */
#define LL_APB1_GRP1_PERIPH_UART6  RCC_APB1LENR_UART6EN
#define LL_APB1_GRP1_PERIPH_ALL_EN_MASK (LL_APB1_GRP1_PERIPH_TIM2   | \
                                         LL_APB1_GRP1_PERIPH_TIM3   | \
                                         LL_APB1_GRP1_PERIPH_TIM6   | \
                                         LL_APB1_GRP1_PERIPH_TIM7   | \
                                         LL_APB1_GRP1_PERIPH_TIM9   | \
                                         LL_APB1_GRP1_PERIPH_TIM10  | \
                                         LL_APB1_GRP1_PERIPH_TIM11  | \
                                         LL_APB1_GRP1_PERIPH_TIM12  | \
                                         LL_APB1_GRP1_PERIPH_TIM13  | \
                                         LL_APB1_GRP1_PERIPH_TIM14  | \
                                         LL_APB1_GRP1_PERIPH_WWDG   | \
                                         LL_APB1_GRP1_PERIPH_SPI2   | \
                                         LL_APB1_GRP1_PERIPH_SPI3   | \
                                         LL_APB1_GRP1_PERIPH_USART2 | \
                                         LL_APB1_GRP1_PERIPH_USART3 | \
                                         LL_APB1_GRP1_PERIPH_UART4  | \
                                         LL_APB1_GRP1_PERIPH_UART5  | \
                                         LL_APB1_GRP1_PERIPH_I2C1   | \
                                         LL_APB1_GRP1_PERIPH_I2C2   | \
                                         LL_APB1_GRP1_PERIPH_I3C1   | \
                                         LL_APB1_GRP1_PERIPH_CRS    | \
                                         LL_APB1_GRP1_PERIPH_UART6)

#define LL_APB1_GRP1_PERIPH_ALL_LPEN_MASK (LL_APB1_GRP1_PERIPH_TIM2   | \
                                           LL_APB1_GRP1_PERIPH_TIM3   | \
                                           LL_APB1_GRP1_PERIPH_TIM6   | \
                                           LL_APB1_GRP1_PERIPH_TIM7   | \
                                           LL_APB1_GRP1_PERIPH_TIM9   | \
                                           LL_APB1_GRP1_PERIPH_TIM10  | \
                                           LL_APB1_GRP1_PERIPH_TIM11  | \
                                           LL_APB1_GRP1_PERIPH_TIM12  | \
                                           LL_APB1_GRP1_PERIPH_TIM13  | \
                                           LL_APB1_GRP1_PERIPH_TIM14  | \
                                           LL_APB1_GRP1_PERIPH_WWDG   | \
                                           LL_APB1_GRP1_PERIPH_SPI2   | \
                                           LL_APB1_GRP1_PERIPH_SPI3   | \
                                           LL_APB1_GRP1_PERIPH_USART2 | \
                                           LL_APB1_GRP1_PERIPH_USART3 | \
                                           LL_APB1_GRP1_PERIPH_UART4  | \
                                           LL_APB1_GRP1_PERIPH_UART5  | \
                                           LL_APB1_GRP1_PERIPH_I2C1   | \
                                           LL_APB1_GRP1_PERIPH_I2C2   | \
                                           LL_APB1_GRP1_PERIPH_I3C1   | \
                                           LL_APB1_GRP1_PERIPH_CRS    | \
                                           LL_APB1_GRP1_PERIPH_UART6)

#define LL_APB1_GRP1_PERIPH_ALL_RST_MASK (LL_APB1_GRP1_PERIPH_TIM2   | \
                                          LL_APB1_GRP1_PERIPH_TIM3   | \
                                          LL_APB1_GRP1_PERIPH_TIM6   | \
                                          LL_APB1_GRP1_PERIPH_TIM7   | \
                                          LL_APB1_GRP1_PERIPH_TIM9   | \
                                          LL_APB1_GRP1_PERIPH_TIM10  | \
                                          LL_APB1_GRP1_PERIPH_TIM11  | \
                                          LL_APB1_GRP1_PERIPH_TIM12  | \
                                          LL_APB1_GRP1_PERIPH_TIM13  | \
                                          LL_APB1_GRP1_PERIPH_TIM14  | \
                                          LL_APB1_GRP1_PERIPH_SPI2   | \
                                          LL_APB1_GRP1_PERIPH_SPI3   | \
                                          LL_APB1_GRP1_PERIPH_USART2 | \
                                          LL_APB1_GRP1_PERIPH_USART3 | \
                                          LL_APB1_GRP1_PERIPH_UART4  | \
                                          LL_APB1_GRP1_PERIPH_UART5  | \
                                          LL_APB1_GRP1_PERIPH_I2C1   | \
                                          LL_APB1_GRP1_PERIPH_I2C2   | \
                                          LL_APB1_GRP1_PERIPH_I3C1   | \
                                          LL_APB1_GRP1_PERIPH_CRS    | \
                                          LL_APB1_GRP1_PERIPH_UART6)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP2_PERIPH  APB1 GRP2 PERIPH
  * @{
  */
#define LL_APB1_GRP2_PERIPH_ALL         0xFFFFFFFFU
#define LL_APB1_GRP2_PERIPH_DTS         RCC_APB1HENR_DTSEN
#define LL_APB1_GRP2_PERIPH_FDCAN       RCC_APB1HENR_FDCANEN
#if defined(UCPD1)
#define LL_APB1_GRP2_PERIPH_UCPD1       RCC_APB1HENR_UCPD1EN
#else
#define LL_APB1_GRP2_PERIPH_UCPD1       0
#endif /* UCPD1 */
#define LL_APB1_GRP2_PERIPH_ALL_EN_MASK (LL_APB1_GRP2_PERIPH_DTS   | \
                                         LL_APB1_GRP2_PERIPH_FDCAN | \
                                         LL_APB1_GRP2_PERIPH_UCPD1)

#define LL_APB1_GRP2_PERIPH_ALL_LPEN_MASK (LL_APB1_GRP2_PERIPH_DTS   | \
                                           LL_APB1_GRP2_PERIPH_FDCAN | \
                                           LL_APB1_GRP2_PERIPH_UCPD1)

#define LL_APB1_GRP2_PERIPH_ALL_RST_MASK (LL_APB1_GRP2_PERIPH_DTS   | \
                                          LL_APB1_GRP2_PERIPH_FDCAN | \
                                          LL_APB1_GRP2_PERIPH_UCPD1)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB2_GRP1_PERIPH  APB2 GRP1 PERIPH
  * @{
  */
#define LL_APB2_GRP1_PERIPH_ALL     0xFFFFFFFFU
#if defined(HRTIM1)
#define LL_APB2_GRP1_PERIPH_HRTIM1   RCC_APB2ENR_HRTIM1EN
#else
#define LL_APB2_GRP1_PERIPH_HRTIM1   0
#endif /* HRTIM1 */
#if defined(PLAY1)
#define LL_APB2_GRP1_PERIPH_PLAY1APB    RCC_APB2ENR_PLAY1APBEN
#define LL_APB2_GRP1_PERIPH_PLAY1       RCC_APB2ENR_PLAY1EN
#define LL_APB2_GRP1_PERIPH_PLAY1APP    RCC_APB2RSTR_PLAY1APPRST
#define LL_APB2_GRP1_PERIPH_PLAY1GLOBAL RCC_APB2RSTR_PLAY1RST
#else
#define LL_APB2_GRP1_PERIPH_PLAY1APB    0
#define LL_APB2_GRP1_PERIPH_PLAY1       0
#define LL_APB2_GRP1_PERIPH_PLAY1APP    0
#define LL_APB2_GRP1_PERIPH_PLAY1GLOBAL 0
#endif /* PLAY1 */
#define LL_APB2_GRP1_PERIPH_TIM1   RCC_APB2ENR_TIM1EN
#define LL_APB2_GRP1_PERIPH_SPI1   RCC_APB2ENR_SPI1EN
#define LL_APB2_GRP1_PERIPH_TIM8   RCC_APB2ENR_TIM8EN
#define LL_APB2_GRP1_PERIPH_USART1 RCC_APB2ENR_USART1EN
#define LL_APB2_GRP1_PERIPH_TIM15  RCC_APB2ENR_TIM15EN
#define LL_APB2_GRP1_PERIPH_TIM16  RCC_APB2ENR_TIM16EN
#define LL_APB2_GRP1_PERIPH_TIM17  RCC_APB2ENR_TIM17EN
#if defined(USB_DRD_FS)
#define LL_APB2_GRP1_PERIPH_USB    RCC_APB2ENR_USBEN
#else
#define LL_APB2_GRP1_PERIPH_USB         0
#endif /* USB_DRD_FS*/
#if defined(TIM4)
#define LL_APB2_GRP1_PERIPH_TIM4        RCC_APB2ENR_TIM4EN
#else
#define LL_APB2_GRP1_PERIPH_TIM4        0
#endif /* TIM4 */
#if defined(TIM5)
#define LL_APB2_GRP1_PERIPH_TIM5        RCC_APB2ENR_TIM5EN
#else
#define LL_APB2_GRP1_PERIPH_TIM5        0
#endif /* TIM5 */
#define LL_APB2_GRP1_PERIPH_ALL_EN_MASK (LL_APB2_GRP1_PERIPH_HRTIM1   | \
                                         LL_APB2_GRP1_PERIPH_PLAY1APB | \
                                         LL_APB2_GRP1_PERIPH_PLAY1    | \
                                         LL_APB2_GRP1_PERIPH_TIM1     | \
                                         LL_APB2_GRP1_PERIPH_SPI1     | \
                                         LL_APB2_GRP1_PERIPH_TIM8     | \
                                         LL_APB2_GRP1_PERIPH_USART1   | \
                                         LL_APB2_GRP1_PERIPH_TIM15    | \
                                         LL_APB2_GRP1_PERIPH_TIM16    | \
                                         LL_APB2_GRP1_PERIPH_TIM17    | \
                                         LL_APB2_GRP1_PERIPH_USB      | \
                                         LL_APB2_GRP1_PERIPH_TIM4     | \
                                         LL_APB2_GRP1_PERIPH_TIM5)

#define LL_APB2_GRP1_PERIPH_ALL_LPEN_MASK (LL_APB2_GRP1_PERIPH_HRTIM1 | \
                                           LL_APB2_GRP1_PERIPH_PLAY1  | \
                                           LL_APB2_GRP1_PERIPH_TIM1   | \
                                           LL_APB2_GRP1_PERIPH_SPI1   | \
                                           LL_APB2_GRP1_PERIPH_TIM8   | \
                                           LL_APB2_GRP1_PERIPH_USART1 | \
                                           LL_APB2_GRP1_PERIPH_TIM15  | \
                                           LL_APB2_GRP1_PERIPH_TIM16  | \
                                           LL_APB2_GRP1_PERIPH_TIM17  | \
                                           LL_APB2_GRP1_PERIPH_USB    | \
                                           LL_APB2_GRP1_PERIPH_TIM4   | \
                                           LL_APB2_GRP1_PERIPH_TIM5)

#define LL_APB2_GRP1_PERIPH_ALL_RST_MASK (LL_APB2_GRP1_PERIPH_HRTIM1      | \
                                          LL_APB2_GRP1_PERIPH_PLAY1APP    | \
                                          LL_APB2_GRP1_PERIPH_PLAY1GLOBAL | \
                                          LL_APB2_GRP1_PERIPH_TIM1        | \
                                          LL_APB2_GRP1_PERIPH_SPI1        | \
                                          LL_APB2_GRP1_PERIPH_TIM8        | \
                                          LL_APB2_GRP1_PERIPH_USART1      | \
                                          LL_APB2_GRP1_PERIPH_TIM15       | \
                                          LL_APB2_GRP1_PERIPH_TIM16       | \
                                          LL_APB2_GRP1_PERIPH_TIM17       | \
                                          LL_APB2_GRP1_PERIPH_USB         | \
                                          LL_APB2_GRP1_PERIPH_TIM4        | \
                                          LL_APB2_GRP1_PERIPH_TIM5)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB3_GRP1_PERIPH  APB3 GRP1 PERIPH
  * @{
  */
#define LL_APB3_GRP1_PERIPH_ALL   0xFFFFFFFFU
#define LL_APB3_GRP1_PERIPH_SBS   RCC_APB3ENR_SBSEN
#if defined(TIM20)
#define LL_APB3_GRP1_PERIPH_TIM20 RCC_APB3ENR_TIM20EN
#else
#define LL_APB3_GRP1_PERIPH_TIM20   0
#endif /* TIM20 */
#define LL_APB3_GRP1_PERIPH_TIM26   RCC_APB3ENR_TIM26EN
#define LL_APB3_GRP1_PERIPH_TIM27   RCC_APB3ENR_TIM27EN
#define LL_APB3_GRP1_PERIPH_LPUART1 RCC_APB3ENR_LPUART1EN
#if defined(I2C3)
#define LL_APB3_GRP1_PERIPH_I2C3    RCC_APB3ENR_I2C3EN
#else
#define LL_APB3_GRP1_PERIPH_I2C3 0
#endif /* I2C3 */
#if defined(I2C4)
#define LL_APB3_GRP1_PERIPH_I2C4 RCC_APB3ENR_I2C4EN
#else
#define LL_APB3_GRP1_PERIPH_I2C4    0
#endif /* I2C4 */
#define LL_APB3_GRP1_PERIPH_LPTIM1  RCC_APB3ENR_LPTIM1EN
#if defined(POSENC1)
#define LL_APB3_GRP1_PERIPH_POSENC1 RCC_APB3ENR_POSENC1EN
#else
#define LL_APB3_GRP1_PERIPH_POSENC1 0
#endif /* POSENC1 */
#if defined(POSENC2)
#define LL_APB3_GRP1_PERIPH_POSENC2 RCC_APB3ENR_POSENC2EN
#else
#define LL_APB3_GRP1_PERIPH_POSENC2 0
#endif /* POSENC2 */
#if defined(OPAMP1)
#define LL_APB3_GRP1_PERIPH_OPAMP1  RCC_APB3ENR_OPAMP1EN
#else
#define LL_APB3_GRP1_PERIPH_OPAMP1 0
#endif /* OPAMP1 */
#if defined(OPAMP2)
#define LL_APB3_GRP1_PERIPH_OPAMP2 RCC_APB3ENR_OPAMP2EN
#else
#define LL_APB3_GRP1_PERIPH_OPAMP2 0
#endif /* OPAMP2 */
#if defined(OPAMP3)
#define LL_APB3_GRP1_PERIPH_OPAMP3 RCC_APB3ENR_OPAMP3EN
#else
#define LL_APB3_GRP1_PERIPH_OPAMP3      0
#endif /* OPAMP3 */
#define LL_APB3_GRP1_PERIPH_VREFBUF     RCC_APB3ENR_VREFEN
#define LL_APB3_GRP1_PERIPH_RTCAPB      RCC_APB3ENR_RTCAPBEN
#define LL_APB3_GRP1_PERIPH_COMP1       RCC_APB3ENR_COMP1EN
#define LL_APB3_GRP1_PERIPH_COMP2       RCC_APB3ENR_COMP2EN
#define LL_APB3_GRP1_PERIPH_COMP3       RCC_APB3ENR_COMP3EN
#define LL_APB3_GRP1_PERIPH_COMP4       RCC_APB3ENR_COMP4EN
#define LL_APB3_GRP1_PERIPH_COMP5       RCC_APB3ENR_COMP5EN
#define LL_APB3_GRP1_PERIPH_COMP6       RCC_APB3ENR_COMP6EN
#define LL_APB3_GRP1_PERIPH_COMP7       RCC_APB3ENR_COMP7EN
#define LL_APB3_GRP1_PERIPH_COMP8       RCC_APB3ENR_COMP8EN
#define LL_APB3_GRP1_PERIPH_ALL_EN_MASK (LL_APB3_GRP1_PERIPH_SBS     | \
                                         LL_APB3_GRP1_PERIPH_TIM20   | \
                                         LL_APB3_GRP1_PERIPH_TIM26   | \
                                         LL_APB3_GRP1_PERIPH_TIM27   | \
                                         LL_APB3_GRP1_PERIPH_LPUART1 | \
                                         LL_APB3_GRP1_PERIPH_I2C3    | \
                                         LL_APB3_GRP1_PERIPH_I2C4    | \
                                         LL_APB3_GRP1_PERIPH_LPTIM1  | \
                                         LL_APB3_GRP1_PERIPH_POSENC1 | \
                                         LL_APB3_GRP1_PERIPH_POSENC2 | \
                                         LL_APB3_GRP1_PERIPH_OPAMP1  | \
                                         LL_APB3_GRP1_PERIPH_OPAMP2  | \
                                         LL_APB3_GRP1_PERIPH_OPAMP3  | \
                                         LL_APB3_GRP1_PERIPH_VREFBUF | \
                                         LL_APB3_GRP1_PERIPH_RTCAPB  | \
                                         LL_APB3_GRP1_PERIPH_COMP1   | \
                                         LL_APB3_GRP1_PERIPH_COMP2   | \
                                         LL_APB3_GRP1_PERIPH_COMP3   | \
                                         LL_APB3_GRP1_PERIPH_COMP4   | \
                                         LL_APB3_GRP1_PERIPH_COMP5   | \
                                         LL_APB3_GRP1_PERIPH_COMP6   | \
                                         LL_APB3_GRP1_PERIPH_COMP7   | \
                                         LL_APB3_GRP1_PERIPH_COMP8)

#define LL_APB3_GRP1_PERIPH_ALL_LPEN_MASK (LL_APB3_GRP1_PERIPH_SBS     | \
                                           LL_APB3_GRP1_PERIPH_TIM20   | \
                                           LL_APB3_GRP1_PERIPH_TIM26   | \
                                           LL_APB3_GRP1_PERIPH_TIM27   | \
                                           LL_APB3_GRP1_PERIPH_LPUART1 | \
                                           LL_APB3_GRP1_PERIPH_I2C3    | \
                                           LL_APB3_GRP1_PERIPH_I2C4    | \
                                           LL_APB3_GRP1_PERIPH_LPTIM1  | \
                                           LL_APB3_GRP1_PERIPH_POSENC1 | \
                                           LL_APB3_GRP1_PERIPH_POSENC2 | \
                                           LL_APB3_GRP1_PERIPH_OPAMP1  | \
                                           LL_APB3_GRP1_PERIPH_OPAMP2  | \
                                           LL_APB3_GRP1_PERIPH_OPAMP3  | \
                                           LL_APB3_GRP1_PERIPH_VREFBUF | \
                                           LL_APB3_GRP1_PERIPH_RTCAPB  | \
                                           LL_APB3_GRP1_PERIPH_COMP1   | \
                                           LL_APB3_GRP1_PERIPH_COMP2   | \
                                           LL_APB3_GRP1_PERIPH_COMP3   | \
                                           LL_APB3_GRP1_PERIPH_COMP4   | \
                                           LL_APB3_GRP1_PERIPH_COMP5   | \
                                           LL_APB3_GRP1_PERIPH_COMP6   | \
                                           LL_APB3_GRP1_PERIPH_COMP7   | \
                                           LL_APB3_GRP1_PERIPH_COMP8)

#define LL_APB3_GRP1_PERIPH_ALL_RST_MASK (LL_APB3_GRP1_PERIPH_TIM20   | \
                                          LL_APB3_GRP1_PERIPH_TIM26   | \
                                          LL_APB3_GRP1_PERIPH_TIM27   | \
                                          LL_APB3_GRP1_PERIPH_LPUART1 | \
                                          LL_APB3_GRP1_PERIPH_I2C3    | \
                                          LL_APB3_GRP1_PERIPH_I2C4    | \
                                          LL_APB3_GRP1_PERIPH_LPTIM1  | \
                                          LL_APB3_GRP1_PERIPH_POSENC1 | \
                                          LL_APB3_GRP1_PERIPH_POSENC2 | \
                                          LL_APB3_GRP1_PERIPH_OPAMP1  | \
                                          LL_APB3_GRP1_PERIPH_OPAMP2  | \
                                          LL_APB3_GRP1_PERIPH_OPAMP3  | \
                                          LL_APB3_GRP1_PERIPH_VREFBUF | \
                                          LL_APB3_GRP1_PERIPH_COMP1   | \
                                          LL_APB3_GRP1_PERIPH_COMP2   | \
                                          LL_APB3_GRP1_PERIPH_COMP3   | \
                                          LL_APB3_GRP1_PERIPH_COMP4   | \
                                          LL_APB3_GRP1_PERIPH_COMP5   | \
                                          LL_APB3_GRP1_PERIPH_COMP6   | \
                                          LL_APB3_GRP1_PERIPH_COMP7   | \
                                          LL_APB3_GRP1_PERIPH_COMP8)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Functions LL BUS Functions
  * @{
  */

/** @defgroup BUS_LL_EF_AHB1 AHB1
  * @{
  */
/**
  * @brief  Enable AHB1 bus clock.
  * @rmtoll
  *  CFGR2         AHB1DIS         LL_AHB1_EnableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_EnableBusClock(void)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_CLEAR_BIT_32(RCC->CFGR2, RCC_CFGR2_AHB1DIS);
  tmpreg = STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_AHB1DIS);
  (void)(tmpreg);
}

/**
  * @brief  Check if AHB1 bus clock is enabled.
  * @rmtoll
  *  CFGR2         AHB1DIS         LL_AHB1_IsEnabledBusClock
  * @retval State (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_IsEnabledBusClock(void)
{
  return ((STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_AHB1DIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 bus clock.
  * @note   except for FLASH, ICACHE, DCACHE, SRAM1.
  * @rmtoll
  *  CFGR2         AHB1DIS         LL_AHB1_DisableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_DisableBusClock(void)
{
  STM32_ATOMIC_SET_BIT_32(RCC->CFGR2, RCC_CFGR2_AHB1DIS);
}

/**
  * @brief  Enable AHB1 peripherals clock.
  * @rmtoll
  *  AHB1ENR         GPDMA1EN         LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         GPDMA2EN         LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         FLASHEN          LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         CRCEN            LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         CORDIC1EN        LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         FMAC1EN          LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         RAMCFGEN         LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         TZSC1EN          LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         SRAM2EN          LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         SRAM3EN          LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         DCACHEEN         LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR         SRAM1EN          LL_AHB1_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TZSC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM3 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->AHB1ENR, periphs & LL_AHB1_GRP1_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->AHB1ENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clock is enabled.
  * @rmtoll
  *  AHB1ENR         GPDMA1EN         LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         GPDMA2EN         LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         FLASHEN          LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         CRCEN            LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         CORDIC1EN        LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         FMAC1EN          LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         RAMCFGEN         LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         TZSC1EN          LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         SRAM2EN          LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         SRAM3EN          LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         DCACHEEN         LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR         SRAM1EN          LL_AHB1_GRP1_IsEnabledClock
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TZSC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM3 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB1ENR, periphs & LL_AHB1_GRP1_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_AHB1_GRP1_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripherals clock.
  * @rmtoll
  *  AHB1ENR         GPDMA1EN         LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         GPDMA2EN         LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         FLASHEN          LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         CRCEN            LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         CORDIC1EN        LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         FMAC1EN          LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         RAMCFGEN         LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         TZSC1EN          LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         SRAM2EN          LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         SRAM3EN          LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         DCACHEEN         LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR         SRAM1EN          LL_AHB1_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TZSC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM3 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB1ENR, periphs & LL_AHB1_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force AHB1 peripherals reset.
  * @rmtoll
  *  AHB1RSTR         GPDMA1RST         LL_AHB1_GRP1_ForceReset \n
  *  AHB1RSTR         GPDMA2RST         LL_AHB1_GRP1_ForceReset \n
  *  AHB1RSTR         CRCRST            LL_AHB1_GRP1_ForceReset \n
  *  AHB1RSTR         CORDIC1RST        LL_AHB1_GRP1_ForceReset \n
  *  AHB1RSTR         FMAC1RST          LL_AHB1_GRP1_ForceReset \n
  *  AHB1RSTR         RAMCFGRST         LL_AHB1_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->AHB1RSTR, periphs & LL_AHB1_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release AHB1 peripherals reset.
  * @rmtoll
  *  AHB1RSTR         GPDMA1RST         LL_AHB1_GRP1_ReleaseReset \n
  *  AHB1RSTR         GPDMA2RST         LL_AHB1_GRP1_ReleaseReset \n
  *  AHB1RSTR         CRCRST            LL_AHB1_GRP1_ReleaseReset \n
  *  AHB1RSTR         CORDIC1RST        LL_AHB1_GRP1_ReleaseReset \n
  *  AHB1RSTR         FMAC1RST          LL_AHB1_GRP1_ReleaseReset \n
  *  AHB1RSTR         RAMCFGRST         LL_AHB1_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->AHB1RSTR, periphs & LL_AHB1_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable AHB1 peripheral clocks in low_power mode.
  * @rmtoll
  *  AHB1LPENR         GPDMA1LPEN         LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         GPDMA2LPEN         LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         FLASHLPEN          LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         CRCLPEN            LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         CORDIC1LPEN        LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         FMAC1LPEN          LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         RAMCFGLPEN         LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         TZSC1LPEN          LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         SRAM2LPEN          LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         SRAM3LPEN          LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         ICACHELPEN         LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         DCACHELPEN         LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR         SRAM1LPEN          LL_AHB1_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TZSC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM3 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ICACHE
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->AHB1LPENR, periphs & LL_AHB1_GRP1_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->AHB1LPENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clocks in low-power mode are enabled.
  * @rmtoll
  *  AHB1LPENR         GPDMA1LPEN         LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         GPDMA2LPEN         LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         FLASHLPEN          LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         CRCLPEN            LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         CORDIC1LPEN        LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         FMAC1LPEN          LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         RAMCFGLPEN         LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         TZSC1LPEN          LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         SRAM2LPEN          LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         SRAM3LPEN          LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         ICACHELPEN         LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         DCACHELPEN         LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR         SRAM1LPEN          LL_AHB1_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TZSC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM3 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ICACHE
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB1LPENR, periphs & LL_AHB1_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_AHB1_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripheral clocks in low_power mode.
  * @rmtoll
  *  AHB1LPENR         GPDMA1LPEN         LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         GPDMA2LPEN         LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         FLASHLPEN          LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         CRCLPEN            LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         CORDIC1LPEN        LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         FMAC1LPEN          LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         RAMCFGLPEN         LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         TZSC1LPEN          LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         SRAM2LPEN          LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         SRAM3LPEN          LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         ICACHELPEN         LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         DCACHELPEN         LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR         SRAM1LPEN          LL_AHB1_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB1_GRP1_PERIPH_CORDIC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_RAMCFG
  *         @arg @ref LL_AHB1_GRP1_PERIPH_TZSC1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM2
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM3 (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ICACHE
  *         @arg @ref LL_AHB1_GRP1_PERIPH_DCACHE (*)
  *         @arg @ref LL_AHB1_GRP1_PERIPH_SRAM1
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB1LPENR, periphs & LL_AHB1_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB2 AHB2
  * @{
  */
/**
  * @brief  Enable AHB2 bus clock.
  * @rmtoll
  *  CFGR2         AHB2DIS         LL_AHB2_EnableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_EnableBusClock(void)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_CLEAR_BIT_32(RCC->CFGR2, RCC_CFGR2_AHB2DIS);
  tmpreg = STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_AHB2DIS);
  (void)(tmpreg);
}
/**
  * @brief  Check if AHB2 bus clock is enabled.
  * @rmtoll
  *  CFGR2         AHB2DIS         LL_AHB2_IsEnabledBusClock
  * @retval State (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_IsEnabledBusClock(void)
{
  return ((STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_AHB2DIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 bus clock.
  * @note   except for SRAM2 and SRAM3.
  * @rmtoll
  *  CFGR2         AHB2DIS         LL_AHB2_DisableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_DisableBusClock(void)
{
  STM32_ATOMIC_SET_BIT_32(RCC->CFGR2, RCC_CFGR2_AHB2DIS);
}

/**
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll
  *  AHB2ENR         DAC1EN          LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR         DAC2EN          LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR         DAC5EN          LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR         DAC6EN          LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR         DAC7EN          LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR         DAC8EN          LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR         DAC9EN          LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR         DAC10EN         LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR         FMAC2EN         LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR         ADC12EN         LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR         ADC3EN          LL_AHB2_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC5
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC6
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC7
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC8
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC9
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC10
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC2 (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC3 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->AHB2ENR, periphs & LL_AHB2_GRP1_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->AHB2ENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clock is enabled.
  * @rmtoll
  *  AHB2ENR         DAC1EN          LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR         DAC2EN          LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR         DAC5EN          LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR         DAC6EN          LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR         DAC7EN          LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR         DAC8EN          LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR         DAC9EN          LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR         DAC10EN         LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR         FMAC2EN         LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR         ADC12EN         LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR         ADC3EN          LL_AHB2_GRP1_IsEnabledClock
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC5
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC6
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC7
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC8
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC9
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC10
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC2 (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC3 (*)
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB2ENR, periphs & LL_AHB2_GRP1_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_AHB2_GRP1_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripherals clock.
  * @rmtoll
  *  AHB2ENR         DAC1EN          LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR         DAC2EN          LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR         DAC5EN          LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR         DAC6EN          LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR         DAC7EN          LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR         DAC8EN          LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR         DAC9EN          LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR         DAC10EN         LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR         FMAC2EN         LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR         ADC12EN         LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR         ADC3EN          LL_AHB2_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC5
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC6
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC7
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC8
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC9
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC10
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC2 (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC3 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB2ENR, periphs & LL_AHB2_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force AHB2 peripherals reset.
  * @rmtoll
  *  AHB2RSTR         DAC1RST          LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR         DAC2RST          LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR         DAC5RST          LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR         DAC6RST          LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR         DAC7RST          LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR         DAC8RST          LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR         DAC9RST          LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR         DAC10RST         LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR         FMAC2RST         LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR         ADC12RST         LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR         ADC3RST          LL_AHB2_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC5
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC6
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC7
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC8
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC9
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC10
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC2 (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC3 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->AHB2RSTR, periphs & LL_AHB2_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release AHB2 peripherals reset.
  * @rmtoll
  *  AHB2RSTR         DAC1RST          LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR         DAC2RST          LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR         DAC5RST          LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR         DAC6RST          LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR         DAC7RST          LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR         DAC8RST          LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR         DAC9RST          LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR         DAC10RST         LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR         FMAC2RST         LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR         ADC12RST         LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR         ADC3RST          LL_AHB2_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC5
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC6
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC7
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC8
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC9
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC10
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC2 (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC3 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->AHB2RSTR, periphs & LL_AHB2_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable AHB2 peripheral clocks in low_power mode.
  * @rmtoll
  *  AHB2LPENR         DAC1LPEN          LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR         DAC2LPEN          LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR         DAC5LPEN          LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR         DAC6LPEN          LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR         DAC7LPEN          LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR         DAC8LPEN          LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR         DAC9LPEN          LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR         DAC10LPEN         LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR         FMAC2LPEN         LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR         ADC12LPEN         LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR         ADC3LPEN          LL_AHB2_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC5
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC6
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC7
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC8
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC9
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC10
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC2 (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC3 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->AHB2LPENR, periphs & LL_AHB2_GRP1_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->AHB2LPENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB2 peripheral clocks in low-power mode are enabled.
  * @rmtoll
  *  AHB2LPENR         DAC1LPEN          LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR         DAC2LPEN          LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR         DAC5LPEN          LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR         DAC6LPEN          LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR         DAC7LPEN          LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR         DAC8LPEN          LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR         DAC9LPEN          LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR         DAC10LPEN         LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR         FMAC2LPEN         LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR         ADC12LPEN         LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR         ADC3LPEN          LL_AHB2_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC5
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC6
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC7
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC8
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC9
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC10
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC2 (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC3 (*)
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB2LPENR, periphs & LL_AHB2_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_AHB2_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripheral clocks in low_power mode.
  * @rmtoll
  *  AHB2LPENR         DAC1LPEN          LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR         DAC2LPEN          LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR         DAC5LPEN          LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR         DAC6LPEN          LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR         DAC7LPEN          LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR         DAC8LPEN          LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR         DAC9LPEN          LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR         DAC10LPEN         LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR         FMAC2LPEN         LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR         ADC12LPEN         LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR         ADC3LPEN          LL_AHB2_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC5
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC6
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC7
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC8
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC9
  *         @arg @ref LL_AHB2_GRP1_PERIPH_DAC10
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC2 (*)
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ADC3 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB2LPENR, periphs & LL_AHB2_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB3 AHB3
  * @{
  */

/**
  * @brief  Enable AHB3 bus clock.
  * @rmtoll
  *  CFGR2         AHB3DIS         LL_AHB3_EnableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_EnableBusClock(void)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_CLEAR_BIT_32(RCC->CFGR2, RCC_CFGR2_AHB3DIS);
  tmpreg = STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_AHB3DIS);
  (void)(tmpreg);
}
/**
  * @brief  Check if AHB3 bus clock is enabled.
  * @rmtoll
  *  CFGR2         AHB3DIS         LL_AHB3_IsEnabledBusClock
  * @retval State (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB3_IsEnabledBusClock(void)
{
  return ((STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_AHB3DIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB3 bus clock.
  * @rmtoll
  *  CFGR2         AHB3DIS         LL_AHB3_DisableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_DisableBusClock(void)
{
  STM32_ATOMIC_SET_BIT_32(RCC->CFGR2, RCC_CFGR2_AHB3DIS);
}

/**
  * @brief  Enable AHB3 peripherals clock.
  * @rmtoll
  *  AHB3ENR         DBGCKEN         LL_AHB3_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DBG
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->AHB3ENR, periphs & LL_AHB3_GRP1_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->AHB3ENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB3 peripheral clock is enabled.
  * @rmtoll
  *  AHB3ENR         DBGCKEN         LL_AHB3_GRP1_IsEnabledClock
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DBG
  *
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB3_GRP1_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB3ENR, periphs & LL_AHB3_GRP1_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_AHB3_GRP1_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB3 peripherals clock.
  * @rmtoll
  *  AHB3ENR         DBGCKEN         LL_AHB3_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DBG
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB3ENR, periphs & LL_AHB3_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Enable AHB3 peripheral clocks in low_power mode.
  * @rmtoll
  *  AHB3LPENR         DBGCKLPEN         LL_AHB3_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DBG
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->AHB3LPENR, periphs & LL_AHB3_GRP1_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->AHB3LPENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB3 peripheral clocks in low-power mode are enabled.
  * @rmtoll
  *  AHB3LPENR         DBGCKLPEN         LL_AHB3_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DBG
  *
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB3_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB3LPENR, periphs & LL_AHB3_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_AHB3_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB3 peripheral clocks in low_power mode.
  * @rmtoll
  *  AHB3LPENR         DBGCKLPEN         LL_AHB3_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DBG
  *
  * @retval None
  */
__STATIC_INLINE void LL_AHB3_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB3LPENR, periphs & LL_AHB3_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB4 AHB4
  * @{
  */
/**
  * @brief  Enable AHB4 bus clock.
  * @rmtoll
  *  CFGR2         AHB4DIS         LL_AHB4_EnableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_EnableBusClock(void)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_CLEAR_BIT_32(RCC->CFGR2, RCC_CFGR2_AHB4DIS);
  tmpreg = STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_AHB4DIS);
  (void)(tmpreg);
}
/**
  * @brief  Check if AHB4 bus clock is enabled.
  * @rmtoll
  *  CFGR2         AHB4DIS         LL_AHB4_IsEnabledBusClock
  * @retval State (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB4_IsEnabledBusClock(void)
{
  return ((STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_AHB4DIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB4 bus clock.
  * @rmtoll
  *  CFGR2         AHB4DIS         LL_AHB4_DisableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_DisableBusClock(void)
{
  STM32_ATOMIC_SET_BIT_32(RCC->CFGR2, RCC_CFGR2_AHB4DIS);
}

/**
  * @brief  Enable AHB4 peripherals clock.
  * @rmtoll
  *  AHB4ENR         AESEN             LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         HASHEN            LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         RNGEN             LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         PKAEN             LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         SAESEN            LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         CCBEN             LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         OTFDEC1EN         LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         GPIOAEN           LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         GPIOBEN           LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         GPIOCEN           LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         GPIODEN           LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         GPIOEEN           LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         GPIOFEN           LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         GPIOGEN           LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         GPIOHEN           LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR         XSPI1EN           LL_AHB4_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_OTFDEC1 (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_XSPI1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->AHB4ENR, periphs & LL_AHB4_GRP1_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->AHB4ENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB4 peripheral clock is enabled.
  * @rmtoll
  *  AHB4ENR         AESEN             LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         HASHEN            LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         RNGEN             LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         PKAEN             LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         SAESEN            LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         CCBEN             LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         OTFDEC1EN         LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         GPIOAEN           LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         GPIOBEN           LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         GPIOCEN           LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         GPIODEN           LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         GPIOEEN           LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         GPIOFEN           LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         GPIOGEN           LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         GPIOHEN           LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR         XSPI1EN           LL_AHB4_GRP1_IsEnabledClock
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_OTFDEC1 (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_XSPI1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB4_GRP1_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB4ENR, periphs & LL_AHB4_GRP1_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_AHB4_GRP1_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB4 peripherals clock.
  * @rmtoll
  *  AHB4ENR         AESEN             LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         HASHEN            LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         RNGEN             LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         PKAEN             LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         SAESEN            LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         CCBEN             LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         OTFDEC1EN         LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         GPIOAEN           LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         GPIOBEN           LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         GPIOCEN           LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         GPIODEN           LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         GPIOEEN           LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         GPIOFEN           LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         GPIOGEN           LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         GPIOHEN           LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR         XSPI1EN           LL_AHB4_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_OTFDEC1 (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_XSPI1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB4ENR, periphs & LL_AHB4_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force AHB4 peripherals reset.
  * @rmtoll
  *  AHB4RSTR         AESRST             LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         HASHRST            LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         RNGRST             LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         PKARST             LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         SAESRST            LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         CCBRST             LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         OTFDEC1RST         LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         GPIOARST           LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         GPIOBRST           LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         GPIOCRST           LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         GPIODRST           LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         GPIOERST           LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         GPIOFRST           LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         GPIOGRST           LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         GPIOHRST           LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR         XSPI1RST           LL_AHB4_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_OTFDEC1 (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_XSPI1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->AHB4RSTR, periphs & LL_AHB4_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release AHB4 peripherals reset.
  * @rmtoll
  *  AHB4RSTR         AESRST             LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         HASHRST            LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         RNGRST             LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         PKARST             LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         SAESRST            LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         CCBRST             LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         OTFDEC1RST         LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         GPIOARST           LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         GPIOBRST           LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         GPIOCRST           LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         GPIODRST           LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         GPIOERST           LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         GPIOFRST           LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         GPIOGRST           LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         GPIOHRST           LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR         XSPI1RST           LL_AHB4_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_OTFDEC1 (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_XSPI1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->AHB4RSTR, periphs & LL_AHB4_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable AHB4 peripheral clocks in low_power mode.
  * @rmtoll
  *  AHB4LPENR         AESLPEN             LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         HASHLPEN            LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         RNGLPEN             LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         PKALPEN             LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         SAESLPEN            LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         CCBLPEN             LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         OTFDEC1LPEN         LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         GPIOALPEN           LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         GPIOBLPEN           LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         GPIOCLPEN           LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         GPIODLPEN           LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         GPIOELPEN           LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         GPIOFLPEN           LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         GPIOGLPEN           LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         GPIOHLPEN           LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR         XSPI1LPEN           LL_AHB4_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_OTFDEC1 (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_XSPI1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->AHB4LPENR, periphs & LL_AHB4_GRP1_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->AHB4LPENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB4 peripheral clocks in low-power mode are enabled.
  * @rmtoll
  *  AHB4LPENR         AESLPEN             LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         HASHLPEN            LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         RNGLPEN             LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         PKALPEN             LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         SAESLPEN            LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         CCBLPEN             LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         OTFDEC1LPEN         LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         GPIOALPEN           LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         GPIOBLPEN           LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         GPIOCLPEN           LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         GPIODLPEN           LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         GPIOELPEN           LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         GPIOFLPEN           LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         GPIOGLPEN           LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         GPIOHLPEN           LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR         XSPI1LPEN           LL_AHB4_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_OTFDEC1 (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_XSPI1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB4_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB4LPENR, periphs & LL_AHB4_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_AHB4_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB4 peripheral clocks in low_power mode.
  * @rmtoll
  *  AHB4LPENR         AESLPEN             LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         HASHLPEN            LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         RNGLPEN             LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         PKALPEN             LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         SAESLPEN            LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         CCBLPEN             LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         OTFDEC1LPEN         LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         GPIOALPEN           LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         GPIOBLPEN           LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         GPIOCLPEN           LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         GPIODLPEN           LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         GPIOELPEN           LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         GPIOFLPEN           LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         GPIOGLPEN           LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         GPIOHLPEN           LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR         XSPI1LPEN           LL_AHB4_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB4_GRP1_PERIPH_AES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_PKA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_SAES (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CCB (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_OTFDEC1 (*)
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOA
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOB
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOD
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOE
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOF
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOG
  *         @arg @ref LL_AHB4_GRP1_PERIPH_GPIOH
  *         @arg @ref LL_AHB4_GRP1_PERIPH_XSPI1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_AHB4_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB4LPENR, periphs & LL_AHB4_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1 APB1
  * @{
  */
/**
  * @brief  Enable APB1 bus clock.
  * @rmtoll
  *  CFGR2         APB1DIS         LL_APB1_EnableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_APB1_EnableBusClock(void)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_CLEAR_BIT_32(RCC->CFGR2, RCC_CFGR2_APB1DIS);
  tmpreg = STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_APB1DIS);
  (void)(tmpreg);
}
/**
  * @brief  Check if APB1 bus clock is enabled.
  * @rmtoll
  *  CFGR2         APB1DIS         LL_APB1_IsEnabledBusClock
  * @retval State (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_IsEnabledBusClock(void)
{
  return ((STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_APB1DIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1 bus clock.
  * @note   except for IWDG.
  * @rmtoll
  *  CFGR2         APB1DIS         LL_APB1_DisableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_APB1_DisableBusClock(void)
{
  STM32_ATOMIC_SET_BIT_32(RCC->CFGR2, RCC_CFGR2_APB1DIS);
}

/**
  * @brief  Enable APB1_1 peripherals clock.
  * @rmtoll
  *  APB1LENR         TIM2EN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         TIM3EN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         TIM6EN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         TIM7EN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         TIM9EN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         TIM10EN          LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         TIM11EN          LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         TIM12EN          LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         TIM13EN          LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         TIM14EN          LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         WWDGEN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         SPI2EN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         SPI3EN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         USART2EN         LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         USART3EN         LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         UART4EN          LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         UART5EN          LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         I2C1EN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         I2C2EN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         I3C1EN           LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         CRSEN            LL_APB1_GRP1_EnableClock \n
  *  APB1LENR         UART6EN          LL_APB1_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART6
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB1LENR, periphs & LL_APB1_GRP1_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB1LENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1_1 peripheral clock is enabled.
  * @rmtoll
  *  APB1LENR         TIM2EN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         TIM3EN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         TIM6EN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         TIM7EN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         TIM9EN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         TIM10EN          LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         TIM11EN          LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         TIM12EN          LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         TIM13EN          LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         TIM14EN          LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         WWDGEN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         SPI2EN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         SPI3EN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         USART2EN         LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         USART3EN         LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         UART4EN          LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         UART5EN          LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         I2C1EN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         I2C2EN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         I3C1EN           LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         CRSEN            LL_APB1_GRP1_IsEnabledClock \n
  *  APB1LENR         UART6EN          LL_APB1_GRP1_IsEnabledClock
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART6
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB1LENR, periphs & LL_APB1_GRP1_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_APB1_GRP1_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1_1 peripherals clock.
  * @rmtoll
  *  APB1LENR         TIM2EN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         TIM3EN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         TIM6EN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         TIM7EN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         TIM9EN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         TIM10EN          LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         TIM11EN          LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         TIM12EN          LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         TIM13EN          LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         TIM14EN          LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         WWDGEN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         SPI2EN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         SPI3EN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         USART2EN         LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         USART3EN         LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         UART4EN          LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         UART5EN          LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         I2C1EN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         I2C2EN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         I3C1EN           LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         CRSEN            LL_APB1_GRP1_DisableClock \n
  *  APB1LENR         UART6EN          LL_APB1_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART6
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB1LENR, periphs & LL_APB1_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force APB1_1 peripherals reset.
  * @rmtoll
  *  APB1LRSTR         TIM2RST           LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         TIM3RST           LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         TIM6RST           LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         TIM7RST           LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         TIM9RST           LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         TIM10RST          LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         TIM11RST          LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         TIM12RST          LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         TIM13RST          LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         TIM14RST          LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         SPI2RST           LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         SPI3RST           LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         USART2RST         LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         USART3RST         LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         UART4RST          LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         UART5RST          LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         I2C1RST           LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         I2C2RST           LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         I3C1RST           LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         CRSRST            LL_APB1_GRP1_ForceReset \n
  *  APB1LRSTR         UART6RST          LL_APB1_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART6
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->APB1LRSTR, periphs & LL_APB1_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release APB1_1 peripherals reset.
  * @rmtoll
  *  APB1LRSTR         TIM2RST           LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         TIM3RST           LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         TIM6RST           LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         TIM7RST           LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         TIM9RST           LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         TIM10RST          LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         TIM11RST          LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         TIM12RST          LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         TIM13RST          LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         TIM14RST          LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         SPI2RST           LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         SPI3RST           LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         USART2RST         LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         USART3RST         LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         UART4RST          LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         UART5RST          LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         I2C1RST           LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         I2C2RST           LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         I3C1RST           LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         CRSRST            LL_APB1_GRP1_ReleaseReset \n
  *  APB1LRSTR         UART6RST          LL_APB1_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART6
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->APB1LRSTR, periphs & LL_APB1_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable APB1_1 peripheral clocks in low_power mode.
  * @rmtoll
  *  APB1LLPENR         TIM2LPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         TIM3LPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         TIM6LPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         TIM7LPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         TIM9LPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         TIM10LPEN          LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         TIM11LPEN          LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         TIM12LPEN          LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         TIM13LPEN          LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         TIM14LPEN          LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         WWDGLPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         SPI2LPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         SPI3LPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         USART2LPEN         LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         USART3LPEN         LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         UART4LPEN          LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         UART5LPEN          LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         I2C1LPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         I2C2LPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         I3C1LPEN           LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         CRSLPEN            LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LLPENR         UART6LPEN          LL_APB1_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART6
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB1LLPENR, periphs & LL_APB1_GRP1_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB1LLPENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1_1 peripheral clocks in low-power mode are enabled.
  * @rmtoll
  *  APB1LLPENR         TIM2LPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         TIM3LPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         TIM6LPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         TIM7LPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         TIM9LPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         TIM10LPEN          LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         TIM11LPEN          LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         TIM12LPEN          LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         TIM13LPEN          LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         TIM14LPEN          LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         WWDGLPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         SPI2LPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         SPI3LPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         USART2LPEN         LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         USART3LPEN         LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         UART4LPEN          LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         UART5LPEN          LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         I2C1LPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         I2C2LPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         I3C1LPEN           LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         CRSLPEN            LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LLPENR         UART6LPEN          LL_APB1_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART6
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB1LLPENR, periphs & LL_APB1_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_APB1_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1_1 peripheral clocks in low_power mode.
  * @rmtoll
  *  APB1LLPENR         TIM2LPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         TIM3LPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         TIM6LPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         TIM7LPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         TIM9LPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         TIM10LPEN          LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         TIM11LPEN          LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         TIM12LPEN          LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         TIM13LPEN          LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         TIM14LPEN          LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         WWDGLPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         SPI2LPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         SPI3LPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         USART2LPEN         LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         USART3LPEN         LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         UART4LPEN          LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         UART5LPEN          LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         I2C1LPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         I2C2LPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         I3C1LPEN           LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         CRSLPEN            LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LLPENR         UART6LPEN          LL_APB1_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3 (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_CRS (*)
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART6
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB1LLPENR, periphs & LL_APB1_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @brief  Enable APB1_2 peripherals clock.
  * @rmtoll
  *  APB1HENR         DTSEN           LL_APB1_GRP2_EnableClock \n
  *  APB1HENR         FDCANEN         LL_APB1_GRP2_EnableClock \n
  *  APB1HENR         UCPD1EN         LL_APB1_GRP2_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_DTS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB1HENR, periphs & LL_APB1_GRP2_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB1HENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1_2 peripheral clock is enabled.
  * @rmtoll
  *  APB1HENR         DTSEN           LL_APB1_GRP2_IsEnabledClock \n
  *  APB1HENR         FDCANEN         LL_APB1_GRP2_IsEnabledClock \n
  *  APB1HENR         UCPD1EN         LL_APB1_GRP2_IsEnabledClock
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_DTS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB1HENR, periphs & LL_APB1_GRP2_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_APB1_GRP2_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1_2 peripherals clock.
  * @rmtoll
  *  APB1HENR         DTSEN           LL_APB1_GRP2_DisableClock \n
  *  APB1HENR         FDCANEN         LL_APB1_GRP2_DisableClock \n
  *  APB1HENR         UCPD1EN         LL_APB1_GRP2_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_DTS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB1HENR, periphs & LL_APB1_GRP2_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force APB1_2 peripherals reset.
  * @rmtoll
  *  APB1HRSTR         DTSRST           LL_APB1_GRP2_ForceReset \n
  *  APB1HRSTR         FDCANRST         LL_APB1_GRP2_ForceReset \n
  *  APB1HRSTR         UCPD1RST         LL_APB1_GRP2_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_DTS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->APB1HRSTR, periphs & LL_APB1_GRP2_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release APB1_2 peripherals reset.
  * @rmtoll
  *  APB1HRSTR         DTSRST           LL_APB1_GRP2_ReleaseReset \n
  *  APB1HRSTR         FDCANRST         LL_APB1_GRP2_ReleaseReset \n
  *  APB1HRSTR         UCPD1RST         LL_APB1_GRP2_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_DTS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->APB1HRSTR, periphs & LL_APB1_GRP2_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable APB1_2 peripheral clocks in low_power mode.
  * @rmtoll
  *  APB1HLPENR         DTSLPEN           LL_APB1_GRP2_EnableClockLowPower \n
  *  APB1HLPENR         FDCANLPEN         LL_APB1_GRP2_EnableClockLowPower \n
  *  APB1HLPENR         UCPD1LPEN         LL_APB1_GRP2_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_DTS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB1HLPENR, periphs & LL_APB1_GRP2_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB1HLPENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1_2 peripheral clocks in low_power mode is enabled.
  * @rmtoll
  *  APB1HLPENR         DTSLPEN           LL_APB1_GRP2_IsEnabledClockLowPower \n
  *  APB1HLPENR         FDCANLPEN         LL_APB1_GRP2_IsEnabledClockLowPower \n
  *  APB1HLPENR         UCPD1LPEN         LL_APB1_GRP2_IsEnabledClockLowPower
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_DTS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB1HLPENR, periphs & LL_APB1_GRP2_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_APB1_GRP2_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1_2 peripheral clocks in low_power mode.
  * @rmtoll
  *  APB1HLPENR         DTSLPEN           LL_APB1_GRP2_DisableClockLowPower \n
  *  APB1HLPENR         FDCANLPEN         LL_APB1_GRP2_DisableClockLowPower \n
  *  APB1HLPENR         UCPD1LPEN         LL_APB1_GRP2_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_DTS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB1HLPENR, periphs & LL_APB1_GRP2_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB2 APB2
  * @{
  */
/**
  * @brief  Enable APB2 bus clock.
  * @rmtoll
  *  CFGR2         APB2DIS         LL_APB2_EnableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_APB2_EnableBusClock(void)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_CLEAR_BIT_32(RCC->CFGR2, RCC_CFGR2_APB2DIS);
  tmpreg = STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_APB2DIS);
  (void)(tmpreg);
}
/**
  * @brief  Check if APB2 bus clock is enabled.
  * @rmtoll
  *  CFGR2         APB2DIS         LL_APB2_IsEnabledBusClock
  * @retval State (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_IsEnabledBusClock(void)
{
  return ((STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_APB2DIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 bus clock.
  * @rmtoll
  *  CFGR2         APB2DIS         LL_APB2_DisableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_APB2_DisableBusClock(void)
{
  STM32_ATOMIC_SET_BIT_32(RCC->CFGR2, RCC_CFGR2_APB2DIS);
}

/**
  * @brief  Enable APB2 peripherals clock.
  * @rmtoll
  *  APB2ENR         HRTIM1EN           LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         PLAY1APBEN         LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         PLAY1EN            LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         TIM1EN             LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         SPI1EN             LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         TIM8EN             LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         USART1EN           LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         TIM15EN            LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         TIM16EN            LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         TIM17EN            LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         USBEN              LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         TIM4EN             LL_APB2_GRP1_EnableClock \n
  *  APB2ENR         TIM5EN             LL_APB2_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1APB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM4 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM5 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB2ENR, periphs & LL_APB2_GRP1_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB2ENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB2 peripheral clock is enabled.
  * @rmtoll
  *  APB2ENR         HRTIM1EN           LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         PLAY1APBEN         LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         PLAY1EN            LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         TIM1EN             LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         SPI1EN             LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         TIM8EN             LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         USART1EN           LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         TIM15EN            LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         TIM16EN            LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         TIM17EN            LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         USBEN              LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         TIM4EN             LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR         TIM5EN             LL_APB2_GRP1_IsEnabledClock
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1APB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM4 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM5 (*)
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB2ENR, periphs & LL_APB2_GRP1_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_APB2_GRP1_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripherals clock.
  * @rmtoll
  *  APB2ENR         HRTIM1EN           LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         PLAY1APBEN         LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         PLAY1EN            LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         TIM1EN             LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         SPI1EN             LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         TIM8EN             LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         USART1EN           LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         TIM15EN            LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         TIM16EN            LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         TIM17EN            LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         USBEN              LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         TIM4EN             LL_APB2_GRP1_DisableClock \n
  *  APB2ENR         TIM5EN             LL_APB2_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1APB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM4 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM5 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB2ENR, periphs & LL_APB2_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force APB2 peripherals reset.
  * @rmtoll
  *  APB2RSTR         HRTIM1RST           LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         PLAY1RST            LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         PLAY1APPRST         LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         TIM1RST             LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         SPI1RST             LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         TIM8RST             LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         USART1RST           LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         TIM15RST            LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         TIM16RST            LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         TIM17RST            LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         USBRST              LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         TIM4RST             LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR         TIM5RST             LL_APB2_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1APP (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1GLOBAL (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM4 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM5 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->APB2RSTR, periphs & LL_APB2_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release APB2 peripherals reset.
  * @rmtoll
  *  APB2RSTR         HRTIM1RST           LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         PLAY1RST            LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         PLAY1APPRST         LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         TIM1RST             LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         SPI1RST             LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         TIM8RST             LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         USART1RST           LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         TIM15RST            LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         TIM16RST            LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         TIM17RST            LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         USBRST              LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         TIM4RST             LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR         TIM5RST             LL_APB2_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1APP (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1GLOBAL (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM4 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM5 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->APB2RSTR, periphs & LL_APB2_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable APB2 peripheral clocks in low_power mode.
  * @rmtoll
  *  APB2LPENR         HRTIM1LPEN         LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         PLAY1LPEN          LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         TIM1LPEN           LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         SPI1LPEN           LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         TIM8LPEN           LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         USART1LPEN         LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         TIM15LPEN          LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         TIM16LPEN          LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         TIM17LPEN          LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         USBLPEN            LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         TIM4LPEN           LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR         TIM5LPEN           LL_APB2_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM4 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM5 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB2LPENR, periphs & LL_APB2_GRP1_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB2LPENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB2 peripheral clocks in low-power mode are enabled.
  * @rmtoll
  *  APB2LPENR         HRTIM1LPEN         LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         PLAY1LPEN          LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         TIM1LPEN           LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         SPI1LPEN           LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         TIM8LPEN           LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         USART1LPEN         LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         TIM15LPEN          LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         TIM16LPEN          LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         TIM17LPEN          LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         USBLPEN            LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         TIM4LPEN           LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR         TIM5LPEN           LL_APB2_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM4 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM5 (*)
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB2LPENR, periphs & LL_APB2_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_APB2_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripheral clocks in low_power mode.
  * @rmtoll
  *  APB2LPENR         HRTIM1LPEN         LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         PLAY1LPEN          LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         TIM1LPEN           LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         SPI1LPEN           LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         TIM8LPEN           LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         USART1LPEN         LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         TIM15LPEN          LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         TIM16LPEN          LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         TIM17LPEN          LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         USBLPEN            LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         TIM4LPEN           LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR         TIM5LPEN           LL_APB2_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_PLAY1 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_USB (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM4 (*)
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM5 (*)
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB2LPENR, periphs & LL_APB2_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB3 APB3
  * @{
  */
/**
  * @brief  Enable APB3 bus clock.
  * @rmtoll
  *  CFGR2         APB3DIS         LL_APB3_EnableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_APB3_EnableBusClock(void)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_CLEAR_BIT_32(RCC->CFGR2, RCC_CFGR2_APB3DIS);
  tmpreg = STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_APB3DIS);
  (void)(tmpreg);
}
/**
  * @brief  Check if APB3 bus clock is enabled.
  * @rmtoll
  *  CFGR2         APB3DIS         LL_APB3_IsEnabledBusClock
  * @retval State (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_IsEnabledBusClock(void)
{
  return ((STM32_READ_BIT(RCC->CFGR2, RCC_CFGR2_APB3DIS) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB3 bus clock.
  * @rmtoll
  *  CFGR2         APB3DIS         LL_APB3_DisableBusClock
  * @retval None
  */
__STATIC_INLINE void LL_APB3_DisableBusClock(void)
{
  STM32_ATOMIC_SET_BIT_32(RCC->CFGR2, RCC_CFGR2_APB3DIS);
}

/**
  * @brief  Enable APB3 peripherals clock.
  * @rmtoll
  *  APB3ENR         SBSEN             LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         TIM20EN           LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         TIM26EN           LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         TIM27EN           LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         LPUART1EN         LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         I2C3EN            LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         I2C4EN            LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         LPTIM1EN          LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         POSENC1EN         LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         POSENC2EN         LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         OPAMP1EN          LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         OPAMP2EN          LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         OPAMP3EN          LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         VREFEN            LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         RTCAPBEN          LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         COMP1EN           LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         COMP2EN           LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         COMP3EN           LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         COMP4EN           LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         COMP5EN           LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         COMP6EN           LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         COMP7EN           LL_APB3_GRP1_EnableClock \n
  *  APB3ENR         COMP8EN           LL_APB3_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM20 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM26
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM27
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP1
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP2
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP3
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP5
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP6
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP7
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP8
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB3ENR, periphs & LL_APB3_GRP1_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB3ENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB3 peripheral clock is enabled.
  * @rmtoll
  *  APB3ENR         SBSEN             LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         TIM20EN           LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         TIM26EN           LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         TIM27EN           LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         LPUART1EN         LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         I2C3EN            LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         I2C4EN            LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         LPTIM1EN          LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         POSENC1EN         LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         POSENC2EN         LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         OPAMP1EN          LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         OPAMP2EN          LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         OPAMP3EN          LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         VREFEN            LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         RTCAPBEN          LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         COMP1EN           LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         COMP2EN           LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         COMP3EN           LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         COMP4EN           LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         COMP5EN           LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         COMP6EN           LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         COMP7EN           LL_APB3_GRP1_IsEnabledClock \n
  *  APB3ENR         COMP8EN           LL_APB3_GRP1_IsEnabledClock
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM20 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM26
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM27
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP1
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP2
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP3
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP5
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP6
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP7
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP8
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB3ENR, periphs & LL_APB3_GRP1_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_APB3_GRP1_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB3 peripherals clock.
  * @rmtoll
  *  APB3ENR         SBSEN             LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         TIM20EN           LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         TIM26EN           LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         TIM27EN           LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         LPUART1EN         LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         I2C3EN            LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         I2C4EN            LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         LPTIM1EN          LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         POSENC1EN         LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         POSENC2EN         LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         OPAMP1EN          LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         OPAMP2EN          LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         OPAMP3EN          LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         VREFEN            LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         RTCAPBEN          LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         COMP1EN           LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         COMP2EN           LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         COMP3EN           LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         COMP4EN           LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         COMP5EN           LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         COMP6EN           LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         COMP7EN           LL_APB3_GRP1_DisableClock \n
  *  APB3ENR         COMP8EN           LL_APB3_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM20 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM26
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM27
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP1
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP2
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP3
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP5
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP6
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP7
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP8
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB3ENR, periphs & LL_APB3_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force APB3 peripherals reset.
  * @rmtoll
  *  APB3RSTR         TIM20RST           LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         TIM26RST           LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         TIM27RST           LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         LPUART1RST         LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         I2C3RST            LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         I2C4RST            LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         LPTIM1RST          LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         POSENC1RST         LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         POSENC2RST         LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         OPAMP1RST          LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         OPAMP2RST          LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         OPAMP3RST          LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         VREFRST            LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         COMP1RST           LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         COMP2RST           LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         COMP3RST           LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         COMP4RST           LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         COMP5RST           LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         COMP6RST           LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         COMP7RST           LL_APB3_GRP1_ForceReset \n
  *  APB3RSTR         COMP8RST           LL_APB3_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM20 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM26
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM27
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP1
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP2
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP3
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP5
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP6
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP7
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP8
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->APB3RSTR, periphs & LL_APB3_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release APB3 peripherals reset.
  * @rmtoll
  *  APB3RSTR         TIM20RST           LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         TIM26RST           LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         TIM27RST           LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         LPUART1RST         LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         I2C3RST            LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         I2C4RST            LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         LPTIM1RST          LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         POSENC1RST         LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         POSENC2RST         LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         OPAMP1RST          LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         OPAMP2RST          LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         OPAMP3RST          LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         VREFRST            LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         COMP1RST           LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         COMP2RST           LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         COMP3RST           LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         COMP4RST           LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         COMP5RST           LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         COMP6RST           LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         COMP7RST           LL_APB3_GRP1_ReleaseReset \n
  *  APB3RSTR         COMP8RST           LL_APB3_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM20 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM26
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM27
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP1
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP2
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP3
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP5
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP6
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP7
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP8
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->APB3RSTR, periphs & LL_APB3_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable APB3 peripheral clocks in low_power mode.
  * @rmtoll
  *  APB3LPENR         SBSLPEN             LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         TIM20LPEN           LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         TIM26LPEN           LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         TIM27LPEN           LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         LPUART1LPEN         LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         I2C3LPEN            LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         I2C4LPEN            LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         LPTIM1LPEN          LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         POSENC1LPEN         LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         POSENC2LPEN         LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         OPAMP1LPEN          LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         OPAMP2LPEN          LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         OPAMP3LPEN          LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         VREFLPEN            LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         RTCAPBLPEN          LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         COMP1LPEN           LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         COMP2LPEN           LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         COMP3LPEN           LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         COMP4LPEN           LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         COMP5LPEN           LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         COMP6LPEN           LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         COMP7LPEN           LL_APB3_GRP1_EnableClockLowPower \n
  *  APB3LPENR         COMP8LPEN           LL_APB3_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM20 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM26
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM27
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP1
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP2
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP3
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP5
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP6
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP7
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP8
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB3LPENR, periphs & LL_APB3_GRP1_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB3LPENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB3 peripheral clocks in low-power mode are enabled.
  * @rmtoll
  *  APB3LPENR         SBSLPEN             LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         TIM20LPEN           LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         TIM26LPEN           LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         TIM27LPEN           LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         LPUART1LPEN         LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         I2C3LPEN            LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         I2C4LPEN            LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         LPTIM1LPEN          LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         POSENC1LPEN         LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         POSENC2LPEN         LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         OPAMP1LPEN          LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         OPAMP2LPEN          LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         OPAMP3LPEN          LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         VREFLPEN            LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         RTCAPBLPEN          LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         COMP1LPEN           LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         COMP2LPEN           LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         COMP3LPEN           LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         COMP4LPEN           LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         COMP5LPEN           LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         COMP6LPEN           LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         COMP7LPEN           LL_APB3_GRP1_IsEnabledClockLowPower \n
  *  APB3LPENR         COMP8LPEN           LL_APB3_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be one of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM20 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM26
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM27
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP1
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP2
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP3
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP5
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP6
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP7
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP8
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB3_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB3LPENR, periphs & LL_APB3_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_APB3_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB3 peripheral clocks in low_power mode.
  * @rmtoll
  *  APB3LPENR         SBSLPEN             LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         TIM20LPEN           LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         TIM26LPEN           LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         TIM27LPEN           LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         LPUART1LPEN         LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         I2C3LPEN            LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         I2C4LPEN            LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         LPTIM1LPEN          LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         POSENC1LPEN         LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         POSENC2LPEN         LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         OPAMP1LPEN          LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         OPAMP2LPEN          LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         OPAMP3LPEN          LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         VREFLPEN            LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         RTCAPBLPEN          LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         COMP1LPEN           LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         COMP2LPEN           LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         COMP3LPEN           LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         COMP4LPEN           LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         COMP5LPEN           LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         COMP6LPEN           LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         COMP7LPEN           LL_APB3_GRP1_DisableClockLowPower \n
  *  APB3LPENR         COMP8LPEN           LL_APB3_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB3_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM20 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM26
  *         @arg @ref LL_APB3_GRP1_PERIPH_TIM27
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_I2C4 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_POSENC2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP1 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP2 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_OPAMP3 (*)
  *         @arg @ref LL_APB3_GRP1_PERIPH_BUF
  *         @arg @ref LL_APB3_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP1
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP2
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP3
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP4
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP5
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP6
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP7
  *         @arg @ref LL_APB3_GRP1_PERIPH_COMP8
  *
  *        (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void LL_APB3_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB3LPENR, periphs & LL_APB3_GRP1_PERIPH_ALL_LPEN_MASK);
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

#endif /* STM32G5XX_LL_BUS_H */
