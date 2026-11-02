/**
  ******************************************************************************
  * @file    stm32h7pxx_ll_bus.h
  * @brief   Header file of BUS LL module.
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
        (++) AHB , APB peripherals,  1 dummy read is necessary

    [..]
      Workarounds:
      (#) For AHB , APB peripherals, a dummy read to the peripheral register has been
          inserted in each LL_{BUS}_GRP{x}_EnableClock() function.

  @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7PXX_LL_BUS_H
#define STM32H7PXX_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7PXX_LL_Driver
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
/** @defgroup BUS_LL_Exported_Constants LL BUS Constants
  * @{
  */

/** @defgroup BUS_LL_EC_AHB1_GRP1_PERIPH  AHB1 GRP1 PERIPH
  * @{
  */
#define LL_AHB1_GRP1_PERIPH_ALL         0xFFFFFFFFU
#define LL_AHB1_GRP1_PERIPH_HSP1        RCC_AHB1ENR_HSPEN
#define LL_AHB1_GRP1_PERIPH_GPDMA1      RCC_AHB1ENR_GPDMA1EN
#define LL_AHB1_GRP1_PERIPH_OTGFS       RCC_AHB1ENR_OTGFSEN
#define LL_AHB1_GRP1_PERIPH_ADF1        RCC_AHB1ENR_ADF1EN
#define LL_AHB1_GRP1_PERIPH_ALL_EN_MASK (LL_AHB1_GRP1_PERIPH_HSP1 |   \
                                         LL_AHB1_GRP1_PERIPH_GPDMA1 | \
                                         LL_AHB1_GRP1_PERIPH_OTGFS |  \
                                         LL_AHB1_GRP1_PERIPH_ADF1)

#define LL_AHB1_GRP1_PERIPH_ALL_LPEN_MASK (LL_AHB1_GRP1_PERIPH_HSP1 |   \
                                           LL_AHB1_GRP1_PERIPH_GPDMA1 | \
                                           LL_AHB1_GRP1_PERIPH_OTGFS |  \
                                           LL_AHB1_GRP1_PERIPH_ADF1)

#define LL_AHB1_GRP1_PERIPH_ALL_RST_MASK (LL_AHB1_GRP1_PERIPH_HSP1 |   \
                                          LL_AHB1_GRP1_PERIPH_GPDMA1 | \
                                          LL_AHB1_GRP1_PERIPH_OTGFS |  \
                                          LL_AHB1_GRP1_PERIPH_ADF1)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB2_GRP1_PERIPH  AHB2 GRP1 PERIPH
  * @{
  */
#define LL_AHB2_GRP1_PERIPH_ALL         0xFFFFFFFFU
#define LL_AHB2_GRP1_PERIPH_CORDIC      RCC_AHB2ENR_CORDICEN
#define LL_AHB2_GRP1_PERIPH_FMAC1       RCC_AHB2ENR_FMAC1EN
#define LL_AHB2_GRP1_PERIPH_AHBSRAM1    RCC_AHB2ENR_AHBSRAM1EN
#define LL_AHB2_GRP1_PERIPH_AHBSRAM2    RCC_AHB2ENR_AHBSRAM2EN
#define LL_AHB2_GRP1_PERIPH_AHBSRAM3    RCC_AHB2ENR_AHBSRAM3EN
#define LL_AHB2_GRP1_PERIPH_ALL_EN_MASK (LL_AHB2_GRP1_PERIPH_CORDIC |   \
                                         LL_AHB2_GRP1_PERIPH_FMAC1 |    \
                                         LL_AHB2_GRP1_PERIPH_AHBSRAM1 | \
                                         LL_AHB2_GRP1_PERIPH_AHBSRAM2 | \
                                         LL_AHB2_GRP1_PERIPH_AHBSRAM3)

#define LL_AHB2_GRP1_PERIPH_ALL_LPEN_MASK (LL_AHB2_GRP1_PERIPH_CORDIC |   \
                                           LL_AHB2_GRP1_PERIPH_FMAC1 |    \
                                           LL_AHB2_GRP1_PERIPH_AHBSRAM1 | \
                                           LL_AHB2_GRP1_PERIPH_AHBSRAM2 | \
                                           LL_AHB2_GRP1_PERIPH_AHBSRAM3)

#define LL_AHB2_GRP1_PERIPH_ALL_RST_MASK (LL_AHB2_GRP1_PERIPH_CORDIC | \
                                          LL_AHB2_GRP1_PERIPH_FMAC1)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB3_GRP1_PERIPH  AHB3 GRP1 PERIPH
  * @{
  */
#define LL_AHB3_GRP1_PERIPH_ALL         0xFFFFFFFFU
#define LL_AHB3_GRP1_PERIPH_RNG         RCC_AHB3ENR_RNGEN
#define LL_AHB3_GRP1_PERIPH_HASH        RCC_AHB3ENR_HASHEN
#define LL_AHB3_GRP1_PERIPH_ADC12       RCC_AHB3ENR_ADC12EN
#define LL_AHB3_GRP1_PERIPH_ADC34       RCC_AHB3ENR_ADC34EN
#define LL_AHB3_GRP1_PERIPH_DAC1        RCC_AHB3ENR_DAC1EN
#define LL_AHB3_GRP1_PERIPH_DAC2        RCC_AHB3ENR_DAC2EN
#define LL_AHB3_GRP1_PERIPH_DAC3        RCC_AHB3ENR_DAC3EN
#define LL_AHB3_GRP1_PERIPH_DAC4        RCC_AHB3ENR_DAC4EN
#define LL_AHB3_GRP1_PERIPH_ALL_EN_MASK (LL_AHB3_GRP1_PERIPH_RNG |   \
                                         LL_AHB3_GRP1_PERIPH_HASH |  \
                                         LL_AHB3_GRP1_PERIPH_ADC12 | \
                                         LL_AHB3_GRP1_PERIPH_ADC34 | \
                                         LL_AHB3_GRP1_PERIPH_DAC1 |  \
                                         LL_AHB3_GRP1_PERIPH_DAC2 |  \
                                         LL_AHB3_GRP1_PERIPH_DAC3 |  \
                                         LL_AHB3_GRP1_PERIPH_DAC4)

#define LL_AHB3_GRP1_PERIPH_ALL_LPEN_MASK (LL_AHB3_GRP1_PERIPH_RNG |   \
                                           LL_AHB3_GRP1_PERIPH_HASH |  \
                                           LL_AHB3_GRP1_PERIPH_ADC12 | \
                                           LL_AHB3_GRP1_PERIPH_ADC34 | \
                                           LL_AHB3_GRP1_PERIPH_DAC1 |  \
                                           LL_AHB3_GRP1_PERIPH_DAC2 |  \
                                           LL_AHB3_GRP1_PERIPH_DAC3 |  \
                                           LL_AHB3_GRP1_PERIPH_DAC4)

#define LL_AHB3_GRP1_PERIPH_ALL_RST_MASK (LL_AHB3_GRP1_PERIPH_RNG |   \
                                          LL_AHB3_GRP1_PERIPH_HASH |  \
                                          LL_AHB3_GRP1_PERIPH_ADC12 | \
                                          LL_AHB3_GRP1_PERIPH_ADC34 | \
                                          LL_AHB3_GRP1_PERIPH_DAC1 |  \
                                          LL_AHB3_GRP1_PERIPH_DAC2 |  \
                                          LL_AHB3_GRP1_PERIPH_DAC3 |  \
                                          LL_AHB3_GRP1_PERIPH_DAC4)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB4_GRP1_PERIPH  AHB4 GRP1 PERIPH
  * @{
  */
#define LL_AHB4_GRP1_PERIPH_ALL         0xFFFFFFFFU
#define LL_AHB4_GRP1_PERIPH_GPIOA       RCC_AHB4ENR_GPIOAEN
#define LL_AHB4_GRP1_PERIPH_GPIOB       RCC_AHB4ENR_GPIOBEN
#define LL_AHB4_GRP1_PERIPH_GPIOC       RCC_AHB4ENR_GPIOCEN
#define LL_AHB4_GRP1_PERIPH_GPIOD       RCC_AHB4ENR_GPIODEN
#define LL_AHB4_GRP1_PERIPH_GPIOE       RCC_AHB4ENR_GPIOEEN
#define LL_AHB4_GRP1_PERIPH_GPIOF       RCC_AHB4ENR_GPIOFEN
#define LL_AHB4_GRP1_PERIPH_GPIOG       RCC_AHB4ENR_GPIOGEN
#define LL_AHB4_GRP1_PERIPH_GPIOH       RCC_AHB4ENR_GPIOHEN
#define LL_AHB4_GRP1_PERIPH_GPIOI       RCC_AHB4ENR_GPIOIEN
#define LL_AHB4_GRP1_PERIPH_CRC         RCC_AHB4ENR_CRCEN
#define LL_AHB4_GRP1_PERIPH_BKPRAM      RCC_AHB4ENR_BKPRAMEN
#define LL_AHB4_GRP1_PERIPH_ALL_EN_MASK (LL_AHB4_GRP1_PERIPH_GPIOA | \
                                         LL_AHB4_GRP1_PERIPH_GPIOB | \
                                         LL_AHB4_GRP1_PERIPH_GPIOC | \
                                         LL_AHB4_GRP1_PERIPH_GPIOD | \
                                         LL_AHB4_GRP1_PERIPH_GPIOE | \
                                         LL_AHB4_GRP1_PERIPH_GPIOF | \
                                         LL_AHB4_GRP1_PERIPH_GPIOG | \
                                         LL_AHB4_GRP1_PERIPH_GPIOH | \
                                         LL_AHB4_GRP1_PERIPH_GPIOI | \
                                         LL_AHB4_GRP1_PERIPH_CRC |   \
                                         LL_AHB4_GRP1_PERIPH_BKPRAM)

#define LL_AHB4_GRP1_PERIPH_ALL_LPEN_MASK (LL_AHB4_GRP1_PERIPH_GPIOA | \
                                           LL_AHB4_GRP1_PERIPH_GPIOB | \
                                           LL_AHB4_GRP1_PERIPH_GPIOC | \
                                           LL_AHB4_GRP1_PERIPH_GPIOD | \
                                           LL_AHB4_GRP1_PERIPH_GPIOE | \
                                           LL_AHB4_GRP1_PERIPH_GPIOF | \
                                           LL_AHB4_GRP1_PERIPH_GPIOG | \
                                           LL_AHB4_GRP1_PERIPH_GPIOH | \
                                           LL_AHB4_GRP1_PERIPH_GPIOI | \
                                           LL_AHB4_GRP1_PERIPH_CRC |   \
                                           LL_AHB4_GRP1_PERIPH_BKPRAM)

#define LL_AHB4_GRP1_PERIPH_ALL_RST_MASK (LL_AHB4_GRP1_PERIPH_GPIOA | \
                                          LL_AHB4_GRP1_PERIPH_GPIOB | \
                                          LL_AHB4_GRP1_PERIPH_GPIOC | \
                                          LL_AHB4_GRP1_PERIPH_GPIOD | \
                                          LL_AHB4_GRP1_PERIPH_GPIOE | \
                                          LL_AHB4_GRP1_PERIPH_GPIOF | \
                                          LL_AHB4_GRP1_PERIPH_GPIOG | \
                                          LL_AHB4_GRP1_PERIPH_GPIOH | \
                                          LL_AHB4_GRP1_PERIPH_GPIOI | \
                                          LL_AHB4_GRP1_PERIPH_CRC)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_AHB5_GRP1_PERIPH  AHB5 GRP1 PERIPH
  * @{
  */
#define LL_AHB5_GRP1_PERIPH_ALL         0xFFFFFFFFU
#define LL_AHB5_GRP1_PERIPH_HPDMA1      RCC_AHB5ENR_HPDMA1EN
#define LL_AHB5_GRP1_PERIPH_FMC         RCC_AHB5ENR_FMCEN
#define LL_AHB5_GRP1_PERIPH_XSPI1       RCC_AHB5ENR_XSPI1EN
#define LL_AHB5_GRP1_PERIPH_SDMMC1      RCC_AHB5ENR_SDMMC1EN
#if defined(NPU_PRESENT)
#define LL_AHB5_GRP1_PERIPH_NPU         RCC_AHB5ENR_NPUEN
#endif /* NPU_PRESENT */
#define LL_AHB5_GRP1_PERIPH_FLASH       RCC_AHB5LPENR_FLASHLPEN
#define LL_AHB5_GRP1_PERIPH_AXISRAM     RCC_AHB5LPENR_AXISRAMLPEN
#define LL_AHB5_GRP1_PERIPH_DTCM1       RCC_AHB5LPENR_DTCM1LPEN
#define LL_AHB5_GRP1_PERIPH_DTCM2       RCC_AHB5LPENR_DTCM2LPEN
#define LL_AHB5_GRP1_PERIPH_ITCM        RCC_AHB5LPENR_ITCMLPEN
#if defined(NPU_PRESENT)
#define LL_AHB5_GRP1_PERIPH_ALL_EN_MASK (LL_AHB5_GRP1_PERIPH_HPDMA1 | \
                                         LL_AHB5_GRP1_PERIPH_FMC |    \
                                         LL_AHB5_GRP1_PERIPH_XSPI1 |  \
                                         LL_AHB5_GRP1_PERIPH_SDMMC1 | \
                                         LL_AHB5_GRP1_PERIPH_NPU)

#define LL_AHB5_GRP1_PERIPH_ALL_LPEN_MASK (LL_AHB5_GRP1_PERIPH_HPDMA1 |  \
                                           LL_AHB5_GRP1_PERIPH_FLASH |   \
                                           LL_AHB5_GRP1_PERIPH_FMC |     \
                                           LL_AHB5_GRP1_PERIPH_XSPI1 |   \
                                           LL_AHB5_GRP1_PERIPH_SDMMC1 |  \
                                           LL_AHB5_GRP1_PERIPH_AXISRAM | \
                                           LL_AHB5_GRP1_PERIPH_DTCM1 |   \
                                           LL_AHB5_GRP1_PERIPH_DTCM2 |   \
                                           LL_AHB5_GRP1_PERIPH_ITCM |    \
                                           LL_AHB5_GRP1_PERIPH_NPU)

#define LL_AHB5_GRP1_PERIPH_ALL_RST_MASK (LL_AHB5_GRP1_PERIPH_HPDMA1 | \
                                          LL_AHB5_GRP1_PERIPH_FMC |    \
                                          LL_AHB5_GRP1_PERIPH_XSPI1 |  \
                                          LL_AHB5_GRP1_PERIPH_SDMMC1 | \
                                          LL_AHB5_GRP1_PERIPH_NPU)

#else
#define LL_AHB5_GRP1_PERIPH_ALL_EN_MASK (LL_AHB5_GRP1_PERIPH_HPDMA1 | \
                                         LL_AHB5_GRP1_PERIPH_FMC |    \
                                         LL_AHB5_GRP1_PERIPH_XSPI1 |  \
                                         LL_AHB5_GRP1_PERIPH_SDMMC1)

#define LL_AHB5_GRP1_PERIPH_ALL_LPEN_MASK (LL_AHB5_GRP1_PERIPH_HPDMA1 |  \
                                           LL_AHB5_GRP1_PERIPH_FLASH |   \
                                           LL_AHB5_GRP1_PERIPH_FMC |     \
                                           LL_AHB5_GRP1_PERIPH_XSPI1 |   \
                                           LL_AHB5_GRP1_PERIPH_SDMMC1 |  \
                                           LL_AHB5_GRP1_PERIPH_AXISRAM | \
                                           LL_AHB5_GRP1_PERIPH_DTCM1 |   \
                                           LL_AHB5_GRP1_PERIPH_DTCM2 |   \
                                           LL_AHB5_GRP1_PERIPH_ITCM)

#define LL_AHB5_GRP1_PERIPH_ALL_RST_MASK (LL_AHB5_GRP1_PERIPH_HPDMA1 | \
                                          LL_AHB5_GRP1_PERIPH_FMC |    \
                                          LL_AHB5_GRP1_PERIPH_XSPI1 |  \
                                          LL_AHB5_GRP1_PERIPH_SDMMC1)
#endif /* NPU_PRESENT */

/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define LL_APB1_GRP1_PERIPH_ALL         0xFFFFFFFFU
#define LL_APB1_GRP1_PERIPH_TIM2        RCC_APB1ENR1_TIM2EN
#define LL_APB1_GRP1_PERIPH_TIM3        RCC_APB1ENR1_TIM3EN
#define LL_APB1_GRP1_PERIPH_TIM4        RCC_APB1ENR1_TIM4EN
#define LL_APB1_GRP1_PERIPH_TIM5        RCC_APB1ENR1_TIM5EN
#define LL_APB1_GRP1_PERIPH_TIM6        RCC_APB1ENR1_TIM6EN
#define LL_APB1_GRP1_PERIPH_TIM7        RCC_APB1ENR1_TIM7EN
#define LL_APB1_GRP1_PERIPH_TIM12       RCC_APB1ENR1_TIM12EN
#define LL_APB1_GRP1_PERIPH_TIM13       RCC_APB1ENR1_TIM13EN
#define LL_APB1_GRP1_PERIPH_TIM14       RCC_APB1ENR1_TIM14EN
#define LL_APB1_GRP1_PERIPH_LPTIM1      RCC_APB1ENR1_LPTIM1EN
#define LL_APB1_GRP1_PERIPH_WWDG        RCC_APB1ENR1_WWDGEN
#define LL_APB1_GRP1_PERIPH_TIM10       RCC_APB1ENR1_TIM10EN
#define LL_APB1_GRP1_PERIPH_TIM11       RCC_APB1ENR1_TIM11EN
#define LL_APB1_GRP1_PERIPH_SPI2        RCC_APB1ENR1_SPI2EN
#define LL_APB1_GRP1_PERIPH_SPI3        RCC_APB1ENR1_SPI3EN
#define LL_APB1_GRP1_PERIPH_USART2      RCC_APB1ENR1_USART2EN
#define LL_APB1_GRP1_PERIPH_USART3      RCC_APB1ENR1_USART3EN
#define LL_APB1_GRP1_PERIPH_UART4       RCC_APB1ENR1_UART4EN
#define LL_APB1_GRP1_PERIPH_UART5       RCC_APB1ENR1_UART5EN
#define LL_APB1_GRP1_PERIPH_I2C1        RCC_APB1ENR1_I2C1EN
#define LL_APB1_GRP1_PERIPH_I2C2        RCC_APB1ENR1_I2C2EN
#define LL_APB1_GRP1_PERIPH_I2C3        RCC_APB1ENR1_I2C3EN
#define LL_APB1_GRP1_PERIPH_I3C1        RCC_APB1ENR1_I3C1EN
#define LL_APB1_GRP1_PERIPH_UART7       RCC_APB1ENR1_UART7EN
#define LL_APB1_GRP1_PERIPH_UART8       RCC_APB1ENR1_UART8EN
#define LL_APB1_GRP1_PERIPH_ALL_EN_MASK (LL_APB1_GRP1_PERIPH_TIM2 |   \
                                         LL_APB1_GRP1_PERIPH_TIM3 |   \
                                         LL_APB1_GRP1_PERIPH_TIM4 |   \
                                         LL_APB1_GRP1_PERIPH_TIM5 |   \
                                         LL_APB1_GRP1_PERIPH_TIM6 |   \
                                         LL_APB1_GRP1_PERIPH_TIM7 |   \
                                         LL_APB1_GRP1_PERIPH_TIM12 |  \
                                         LL_APB1_GRP1_PERIPH_TIM13 |  \
                                         LL_APB1_GRP1_PERIPH_TIM14 |  \
                                         LL_APB1_GRP1_PERIPH_LPTIM1 | \
                                         LL_APB1_GRP1_PERIPH_WWDG |   \
                                         LL_APB1_GRP1_PERIPH_TIM10 |  \
                                         LL_APB1_GRP1_PERIPH_TIM11 |  \
                                         LL_APB1_GRP1_PERIPH_SPI2 |   \
                                         LL_APB1_GRP1_PERIPH_SPI3 |   \
                                         LL_APB1_GRP1_PERIPH_USART2 | \
                                         LL_APB1_GRP1_PERIPH_USART3 | \
                                         LL_APB1_GRP1_PERIPH_UART4 |  \
                                         LL_APB1_GRP1_PERIPH_UART5 |  \
                                         LL_APB1_GRP1_PERIPH_I2C1 |   \
                                         LL_APB1_GRP1_PERIPH_I2C2 |   \
                                         LL_APB1_GRP1_PERIPH_I2C3 |   \
                                         LL_APB1_GRP1_PERIPH_I3C1 |   \
                                         LL_APB1_GRP1_PERIPH_UART7 |  \
                                         LL_APB1_GRP1_PERIPH_UART8)

#define LL_APB1_GRP1_PERIPH_ALL_LPEN_MASK (LL_APB1_GRP1_PERIPH_TIM2 |   \
                                           LL_APB1_GRP1_PERIPH_TIM3 |   \
                                           LL_APB1_GRP1_PERIPH_TIM4 |   \
                                           LL_APB1_GRP1_PERIPH_TIM5 |   \
                                           LL_APB1_GRP1_PERIPH_TIM6 |   \
                                           LL_APB1_GRP1_PERIPH_TIM7 |   \
                                           LL_APB1_GRP1_PERIPH_TIM12 |  \
                                           LL_APB1_GRP1_PERIPH_TIM13 |  \
                                           LL_APB1_GRP1_PERIPH_TIM14 |  \
                                           LL_APB1_GRP1_PERIPH_LPTIM1 | \
                                           LL_APB1_GRP1_PERIPH_WWDG |   \
                                           LL_APB1_GRP1_PERIPH_TIM10 |  \
                                           LL_APB1_GRP1_PERIPH_TIM11 |  \
                                           LL_APB1_GRP1_PERIPH_SPI2 |   \
                                           LL_APB1_GRP1_PERIPH_SPI3 |   \
                                           LL_APB1_GRP1_PERIPH_USART2 | \
                                           LL_APB1_GRP1_PERIPH_USART3 | \
                                           LL_APB1_GRP1_PERIPH_UART4 |  \
                                           LL_APB1_GRP1_PERIPH_UART5 |  \
                                           LL_APB1_GRP1_PERIPH_I2C1 |   \
                                           LL_APB1_GRP1_PERIPH_I2C2 |   \
                                           LL_APB1_GRP1_PERIPH_I2C3 |   \
                                           LL_APB1_GRP1_PERIPH_I3C1 |   \
                                           LL_APB1_GRP1_PERIPH_UART7 |  \
                                           LL_APB1_GRP1_PERIPH_UART8)

#define LL_APB1_GRP1_PERIPH_ALL_RST_MASK (LL_APB1_GRP1_PERIPH_TIM2 |   \
                                          LL_APB1_GRP1_PERIPH_TIM3 |   \
                                          LL_APB1_GRP1_PERIPH_TIM4 |   \
                                          LL_APB1_GRP1_PERIPH_TIM5 |   \
                                          LL_APB1_GRP1_PERIPH_TIM6 |   \
                                          LL_APB1_GRP1_PERIPH_TIM7 |   \
                                          LL_APB1_GRP1_PERIPH_TIM12 |  \
                                          LL_APB1_GRP1_PERIPH_TIM13 |  \
                                          LL_APB1_GRP1_PERIPH_TIM14 |  \
                                          LL_APB1_GRP1_PERIPH_LPTIM1 | \
                                          LL_APB1_GRP1_PERIPH_TIM10 |  \
                                          LL_APB1_GRP1_PERIPH_TIM11 |  \
                                          LL_APB1_GRP1_PERIPH_SPI2 |   \
                                          LL_APB1_GRP1_PERIPH_SPI3 |   \
                                          LL_APB1_GRP1_PERIPH_USART2 | \
                                          LL_APB1_GRP1_PERIPH_USART3 | \
                                          LL_APB1_GRP1_PERIPH_UART4 |  \
                                          LL_APB1_GRP1_PERIPH_UART5 |  \
                                          LL_APB1_GRP1_PERIPH_I2C1 |   \
                                          LL_APB1_GRP1_PERIPH_I2C2 |   \
                                          LL_APB1_GRP1_PERIPH_I2C3 |   \
                                          LL_APB1_GRP1_PERIPH_I3C1 |   \
                                          LL_APB1_GRP1_PERIPH_UART7 |  \
                                          LL_APB1_GRP1_PERIPH_UART8)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB1_GRP2_PERIPH  APB1 GRP2 PERIPH
  * @{
  */
#define LL_APB1_GRP2_PERIPH_ALL         0xFFFFFFFFU
#define LL_APB1_GRP2_PERIPH_CRS         RCC_APB1ENR2_CRSEN
#define LL_APB1_GRP2_PERIPH_FDCAN       RCC_APB1ENR2_FDCANEN
#define LL_APB1_GRP2_PERIPH_UCPD1       RCC_APB1ENR2_UCPD1EN
#define LL_APB1_GRP2_PERIPH_ALL_EN_MASK (LL_APB1_GRP2_PERIPH_CRS |   \
                                         LL_APB1_GRP2_PERIPH_FDCAN | \
                                         LL_APB1_GRP2_PERIPH_UCPD1)

#define LL_APB1_GRP2_PERIPH_ALL_LPEN_MASK (LL_APB1_GRP2_PERIPH_CRS |   \
                                           LL_APB1_GRP2_PERIPH_FDCAN | \
                                           LL_APB1_GRP2_PERIPH_UCPD1)

#define LL_APB1_GRP2_PERIPH_ALL_RST_MASK (LL_APB1_GRP2_PERIPH_CRS |   \
                                          LL_APB1_GRP2_PERIPH_FDCAN | \
                                          LL_APB1_GRP2_PERIPH_UCPD1)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB2_GRP1_PERIPH  APB2 GRP1 PERIPH
  * @{
  */
#define LL_APB2_GRP1_PERIPH_ALL         0xFFFFFFFFU
#define LL_APB2_GRP1_PERIPH_TIM1        RCC_APB2ENR_TIM1EN
#define LL_APB2_GRP1_PERIPH_TIM8        RCC_APB2ENR_TIM8EN
#define LL_APB2_GRP1_PERIPH_TIM20       RCC_APB2ENR_TIM20EN
#define LL_APB2_GRP1_PERIPH_USART1      RCC_APB2ENR_USART1EN
#define LL_APB2_GRP1_PERIPH_USART6      RCC_APB2ENR_USART6EN
#define LL_APB2_GRP1_PERIPH_UART9       RCC_APB2ENR_USART9EN
#define LL_APB2_GRP1_PERIPH_USART10     RCC_APB2ENR_USART10EN
#define LL_APB2_GRP1_PERIPH_SPI1        RCC_APB2ENR_SPI1EN
#define LL_APB2_GRP1_PERIPH_SPI4        RCC_APB2ENR_SPI4EN
#define LL_APB2_GRP1_PERIPH_TIM15       RCC_APB2ENR_TIM15EN
#define LL_APB2_GRP1_PERIPH_TIM16       RCC_APB2ENR_TIM16EN
#define LL_APB2_GRP1_PERIPH_TIM17       RCC_APB2ENR_TIM17EN
#define LL_APB2_GRP1_PERIPH_TIM9        RCC_APB2ENR_TIM9EN
#define LL_APB2_GRP1_PERIPH_SPI5        RCC_APB2ENR_SPI5EN
#define LL_APB2_GRP1_PERIPH_HRTIM1      RCC_APB2ENR_HRTIM1EN
#define LL_APB2_GRP1_PERIPH_HRTIM2      RCC_APB2ENR_HRTIM2EN
#define LL_APB2_GRP1_PERIPH_ALL_EN_MASK (LL_APB2_GRP1_PERIPH_TIM1 |    \
                                         LL_APB2_GRP1_PERIPH_TIM8 |    \
                                         LL_APB2_GRP1_PERIPH_TIM20 |   \
                                         LL_APB2_GRP1_PERIPH_USART1 |  \
                                         LL_APB2_GRP1_PERIPH_USART6 |  \
                                         LL_APB2_GRP1_PERIPH_UART9 |   \
                                         LL_APB2_GRP1_PERIPH_USART10 | \
                                         LL_APB2_GRP1_PERIPH_SPI1 |    \
                                         LL_APB2_GRP1_PERIPH_SPI4 |    \
                                         LL_APB2_GRP1_PERIPH_TIM15 |   \
                                         LL_APB2_GRP1_PERIPH_TIM16 |   \
                                         LL_APB2_GRP1_PERIPH_TIM17 |   \
                                         LL_APB2_GRP1_PERIPH_TIM9 |    \
                                         LL_APB2_GRP1_PERIPH_SPI5 |    \
                                         LL_APB2_GRP1_PERIPH_HRTIM1 |  \
                                         LL_APB2_GRP1_PERIPH_HRTIM2)

#define LL_APB2_GRP1_PERIPH_ALL_LPEN_MASK (LL_APB2_GRP1_PERIPH_TIM1 |    \
                                           LL_APB2_GRP1_PERIPH_TIM8 |    \
                                           LL_APB2_GRP1_PERIPH_TIM20 |   \
                                           LL_APB2_GRP1_PERIPH_USART1 |  \
                                           LL_APB2_GRP1_PERIPH_USART6 |  \
                                           LL_APB2_GRP1_PERIPH_UART9 |   \
                                           LL_APB2_GRP1_PERIPH_USART10 | \
                                           LL_APB2_GRP1_PERIPH_SPI1 |    \
                                           LL_APB2_GRP1_PERIPH_SPI4 |    \
                                           LL_APB2_GRP1_PERIPH_TIM15 |   \
                                           LL_APB2_GRP1_PERIPH_TIM16 |   \
                                           LL_APB2_GRP1_PERIPH_TIM17 |   \
                                           LL_APB2_GRP1_PERIPH_TIM9 |    \
                                           LL_APB2_GRP1_PERIPH_SPI5 |    \
                                           LL_APB2_GRP1_PERIPH_HRTIM1 |  \
                                           LL_APB2_GRP1_PERIPH_HRTIM2)

#define LL_APB2_GRP1_PERIPH_ALL_RST_MASK (LL_APB2_GRP1_PERIPH_TIM1 |    \
                                          LL_APB2_GRP1_PERIPH_TIM8 |    \
                                          LL_APB2_GRP1_PERIPH_TIM20 |   \
                                          LL_APB2_GRP1_PERIPH_USART1 |  \
                                          LL_APB2_GRP1_PERIPH_USART6 |  \
                                          LL_APB2_GRP1_PERIPH_UART9 |   \
                                          LL_APB2_GRP1_PERIPH_USART10 | \
                                          LL_APB2_GRP1_PERIPH_SPI1 |    \
                                          LL_APB2_GRP1_PERIPH_SPI4 |    \
                                          LL_APB2_GRP1_PERIPH_TIM15 |   \
                                          LL_APB2_GRP1_PERIPH_TIM16 |   \
                                          LL_APB2_GRP1_PERIPH_TIM17 |   \
                                          LL_APB2_GRP1_PERIPH_TIM9 |    \
                                          LL_APB2_GRP1_PERIPH_SPI5 |    \
                                          LL_APB2_GRP1_PERIPH_HRTIM1 |  \
                                          LL_APB2_GRP1_PERIPH_HRTIM2)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_APB4_GRP1_PERIPH  APB4 GRP1 PERIPH
  * @{
  */
#define LL_APB4_GRP1_PERIPH_ALL         0xFFFFFFFFU
#define LL_APB4_GRP1_PERIPH_SBS         RCC_APB4ENR_SBSEN
#define LL_APB4_GRP1_PERIPH_LPUART1     RCC_APB4ENR_LPUART1EN
#define LL_APB4_GRP1_PERIPH_SPI6        RCC_APB4ENR_SPI6EN
#define LL_APB4_GRP1_PERIPH_LPTIM2      RCC_APB4ENR_LPTIM2EN
#define LL_APB4_GRP1_PERIPH_LPTIM3      RCC_APB4ENR_LPTIM3EN
#define LL_APB4_GRP1_PERIPH_LPTIM4      RCC_APB4ENR_LPTIM4EN
#define LL_APB4_GRP1_PERIPH_LPTIM5      RCC_APB4ENR_LPTIM5EN
#define LL_APB4_GRP1_PERIPH_VREFBUF     RCC_APB4ENR_VREFEN
#define LL_APB4_GRP1_PERIPH_RTCAPB      RCC_APB4ENR_RTCAPBEN
#define LL_APB4_GRP1_PERIPH_DTS         RCC_APB4ENR_DTSEN
#define LL_APB4_GRP1_PERIPH_COMP12      RCC_APB4ENR_COMP12EN
#define LL_APB4_GRP1_PERIPH_COMP34      RCC_APB4ENR_COMP34EN
#define LL_APB4_GRP1_PERIPH_COMP56      RCC_APB4ENR_COMP56EN
#define LL_APB4_GRP1_PERIPH_COMP78      RCC_APB4ENR_COMP78EN
#define LL_APB4_GRP1_PERIPH_ALL_EN_MASK (LL_APB4_GRP1_PERIPH_SBS     | \
                                         LL_APB4_GRP1_PERIPH_LPUART1 | \
                                         LL_APB4_GRP1_PERIPH_SPI6    | \
                                         LL_APB4_GRP1_PERIPH_LPTIM2  | \
                                         LL_APB4_GRP1_PERIPH_LPTIM3  | \
                                         LL_APB4_GRP1_PERIPH_LPTIM4  | \
                                         LL_APB4_GRP1_PERIPH_LPTIM5  | \
                                         LL_APB4_GRP1_PERIPH_VREFBUF | \
                                         LL_APB4_GRP1_PERIPH_RTCAPB  | \
                                         LL_APB4_GRP1_PERIPH_DTS     | \
                                         LL_APB4_GRP1_PERIPH_COMP12  | \
                                         LL_APB4_GRP1_PERIPH_COMP34  | \
                                         LL_APB4_GRP1_PERIPH_COMP56  | \
                                         LL_APB4_GRP1_PERIPH_COMP78)

#define LL_APB4_GRP1_PERIPH_ALL_LPEN_MASK (LL_APB4_GRP1_PERIPH_SBS |     \
                                           LL_APB4_GRP1_PERIPH_LPUART1 | \
                                           LL_APB4_GRP1_PERIPH_SPI6    | \
                                           LL_APB4_GRP1_PERIPH_LPTIM2  | \
                                           LL_APB4_GRP1_PERIPH_LPTIM3  | \
                                           LL_APB4_GRP1_PERIPH_LPTIM4  | \
                                           LL_APB4_GRP1_PERIPH_LPTIM5  | \
                                           LL_APB4_GRP1_PERIPH_VREFBUF | \
                                           LL_APB4_GRP1_PERIPH_RTCAPB  | \
                                           LL_APB4_GRP1_PERIPH_DTS     | \
                                           LL_APB4_GRP1_PERIPH_COMP12  | \
                                           LL_APB4_GRP1_PERIPH_COMP34  | \
                                           LL_APB4_GRP1_PERIPH_COMP56  | \
                                           LL_APB4_GRP1_PERIPH_COMP78)

#define LL_APB4_GRP1_PERIPH_ALL_RST_MASK (LL_APB4_GRP1_PERIPH_SBS |     \
                                          LL_APB4_GRP1_PERIPH_LPUART1 | \
                                          LL_APB4_GRP1_PERIPH_SPI6    | \
                                          LL_APB4_GRP1_PERIPH_LPTIM2  | \
                                          LL_APB4_GRP1_PERIPH_LPTIM3  | \
                                          LL_APB4_GRP1_PERIPH_LPTIM4  | \
                                          LL_APB4_GRP1_PERIPH_LPTIM5  | \
                                          LL_APB4_GRP1_PERIPH_VREFBUF | \
                                          LL_APB4_GRP1_PERIPH_DTS     | \
                                          LL_APB4_GRP1_PERIPH_COMP12  | \
                                          LL_APB4_GRP1_PERIPH_COMP34  | \
                                          LL_APB4_GRP1_PERIPH_COMP56  | \
                                          LL_APB4_GRP1_PERIPH_COMP78)

/**
  * @}
  */

/** @defgroup BUS_LL_EC_CKG_PERIPH  CKGPERIPH
  * @{
  */
#define LL_CKG_PERIPH_ALL          0xFFFFFFFFU
#define LL_CKG_PERIPH_AXI          RCC_CKGDISR_AXICKG
#define LL_CKG_PERIPH_AHBM         RCC_CKGDISR_AHBMCKG
#define LL_CKG_PERIPH_SDMMC1       RCC_CKGDISR_SDMMC1CKG
#define LL_CKG_PERIPH_HPDMA1       RCC_CKGDISR_HPDMA1CKG
#define LL_CKG_PERIPH_CPU          RCC_CKGDISR_CPUCKG
#if defined(NPU_PRESENT)
#define LL_CKG_PERIPH_NPU0         RCC_CKGDISR_NPU0CKG
#define LL_CKG_PERIPH_NPU1         RCC_CKGDISR_NPU1CKG
#else
#define LL_CKG_PERIPH_NPU0         0
#define LL_CKG_PERIPH_NPU1         0
#endif /* NPU_PRESENT */
#define LL_CKG_PERIPH_AHBS         RCC_CKGDISR_AHBSCKG
#define LL_CKG_PERIPH_AHBIC        RCC_CKGDISR_AHBICCKG
#define LL_CKG_PERIPH_FMC          RCC_CKGDISR_FMCCKG
#define LL_CKG_PERIPH_XSPI1        RCC_CKGDISR_XSPI1CKG
#define LL_CKG_PERIPH_AXISRAM4     RCC_CKGDISR_AXISRAM4CKG
#define LL_CKG_PERIPH_AXISRAM3     RCC_CKGDISR_AXISRAM3CKG
#define LL_CKG_PERIPH_AXISRAM2     RCC_CKGDISR_AXISRAM2CKG
#define LL_CKG_PERIPH_AXISRAM1     RCC_CKGDISR_AXISRAM1CKG
#define LL_CKG_PERIPH_FLASH        RCC_CKGDISR_FLASHCKG
#define LL_CKG_PERIPH_EXTI         RCC_CKGDISR_EXTICKG
#define LL_CKG_PERIPH_JTAG         RCC_CKGDISR_JTAGCKG
#define LL_CKG_PERIPH_ALL_DIS_MASK (LL_CKG_PERIPH_AXI |      \
                                    LL_CKG_PERIPH_AHBM |     \
                                    LL_CKG_PERIPH_SDMMC1 |   \
                                    LL_CKG_PERIPH_HPDMA1 |   \
                                    LL_CKG_PERIPH_CPU |      \
                                    LL_CKG_PERIPH_NPU0 |     \
                                    LL_CKG_PERIPH_NPU1 |     \
                                    LL_CKG_PERIPH_AHBS |     \
                                    LL_CKG_PERIPH_AHBIC |    \
                                    LL_CKG_PERIPH_FMC |      \
                                    LL_CKG_PERIPH_XSPI1 |    \
                                    LL_CKG_PERIPH_AXISRAM4 | \
                                    LL_CKG_PERIPH_AXISRAM3 | \
                                    LL_CKG_PERIPH_AXISRAM2 | \
                                    LL_CKG_PERIPH_AXISRAM1 | \
                                    LL_CKG_PERIPH_FLASH |    \
                                    LL_CKG_PERIPH_EXTI |     \
                                    LL_CKG_PERIPH_JTAG)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Functions BUS Exported Functions
  * @{
  */

/** @defgroup BUS_LL_EF_AHB1 AHB1
  * @{
  */

/**
  * @brief  Enable AHB1 peripherals clock.
  * @rmtoll
  *  AHB1ENR   HSPEN       LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR   GPDMA1EN    LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR   OTGFSEN     LL_AHB1_GRP1_EnableClock \n
  *  AHB1ENR   ADF1EN      LL_AHB1_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_OTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
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
  * @brief  Check if AHB1 peripheral clock is enabled or not.
  * @rmtoll
  *  AHB1ENR   HSPEN       LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR   GPDMA1EN    LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR   OTGFSEN     LL_AHB1_GRP1_IsEnabledClock \n
  *  AHB1ENR   ADF1EN      LL_AHB1_GRP1_IsEnabledClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_OTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
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
  *  AHB1ENR   HSPEN       LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR   GPDMA1EN    LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR   OTGFSEN     LL_AHB1_GRP1_DisableClock \n
  *  AHB1ENR   ADF1EN      LL_AHB1_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_OTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  */
__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB1ENR, periphs & LL_AHB1_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force AHB1 peripherals reset.
  * @rmtoll
  *  AHB1RSTR    HSPRST      LL_AHB1_GRP1_ForceReset \n
  *  AHB1RSTR    GPDMA1RST   LL_AHB1_GRP1_ForceReset \n
  *  AHB1RSTR    OTGFSRST    LL_AHB1_GRP1_ForceReset \n
  *  AHB1RSTR    ADF1RST     LL_AHB1_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_OTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  */
__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->AHB1RSTR, periphs & LL_AHB1_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release AHB1 peripherals reset.
  * @rmtoll
  *  AHB1RSTR    HSPRST      LL_AHB1_GRP1_ReleaseReset \n
  *  AHB1RSTR    GPDMA1RST   LL_AHB1_GRP1_ReleaseReset \n
  *  AHB1RSTR    OTGFSRST    LL_AHB1_GRP1_ReleaseReset \n
  *  AHB1RSTR    ADF1RST     LL_AHB1_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_OTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  */
__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->AHB1RSTR, periphs & LL_AHB1_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable AHB1 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  AHB1LPENR   HSPLPEN       LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR   GPDMA1LPEN    LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR   OTGFSLPEN     LL_AHB1_GRP1_EnableClockLowPower \n
  *  AHB1LPENR   ADF1LPEN      LL_AHB1_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_OTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
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
  * @brief  Check if AHB1 peripheral clocks in Sleep and Stop modes is enabled or not.
  * @rmtoll
  *  AHB1LPENR   HSPLPEN       LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR   GPDMA1LPEN    LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR   OTGFSLPEN     LL_AHB1_GRP1_IsEnabledClockLowPower \n
  *  AHB1LPENR   ADF1LPEN      LL_AHB1_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_OTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB1LPENR, periphs & LL_AHB1_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_AHB1_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB1 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  AHB1LPENR   HSPLPEN       LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR   GPDMA1LPEN    LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR   OTGFSLPEN     LL_AHB1_GRP1_DisableClockLowPower \n
  *  AHB1LPENR   ADF1LPEN      LL_AHB1_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB1_GRP1_PERIPH_HSP1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_GPDMA1
  *         @arg @ref LL_AHB1_GRP1_PERIPH_OTGFS
  *         @arg @ref LL_AHB1_GRP1_PERIPH_ADF1
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
  * @brief  Enable AHB2 peripherals clock.
  * @rmtoll
  *  AHB2ENR   CORDICEN      LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR   FMAC1EN       LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR   AHBSRAM1EN    LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR   AHBSRAM2EN    LL_AHB2_GRP1_EnableClock \n
  *  AHB2ENR   AHBSRAM3EN    LL_AHB2_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM3
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
  * @brief  Check if AHB2 peripheral clock is enabled or not.
  * @rmtoll
  *  AHB2ENR   CORDICEN      LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR   FMAC1EN       LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR   AHBSRAM1EN    LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR   AHBSRAM2EN    LL_AHB2_GRP1_IsEnabledClock \n
  *  AHB2ENR   AHBSRAM3EN    LL_AHB2_GRP1_IsEnabledClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM3
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
  *  AHB2ENR   CORDICEN      LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR   FMAC1EN       LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR   AHBSRAM1EN    LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR   AHBSRAM2EN    LL_AHB2_GRP1_DisableClock \n
  *  AHB2ENR   AHBSRAM3EN    LL_AHB2_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM3
  */
__STATIC_INLINE void LL_AHB2_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB2ENR, periphs & LL_AHB2_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force AHB2 peripherals reset.
  * @rmtoll
  *  AHB2RSTR    CORDICRST   LL_AHB2_GRP1_ForceReset \n
  *  AHB2RSTR    FMAC1RST    LL_AHB2_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC1
  */
__STATIC_INLINE void LL_AHB2_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->AHB2RSTR, periphs & LL_AHB2_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release AHB2 peripherals reset.
  * @rmtoll
  *  AHB2RSTR    CORDICRST   LL_AHB2_GRP1_ReleaseReset \n
  *  AHB2RSTR    FMAC1RST    LL_AHB2_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC1
  */
__STATIC_INLINE void LL_AHB2_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->AHB2RSTR, periphs & LL_AHB2_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable AHB2 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  AHB2LPENR   CORDICLPEN      LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR   FMAC1LPEN       LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR   AHBSRAM1LPEN    LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR   AHBSRAM2LPEN    LL_AHB2_GRP1_EnableClockLowPower \n
  *  AHB2LPENR   AHBSRAM3LPEN    LL_AHB2_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM3
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
  * @brief  Check if AHB2 peripheral clocks in Sleep and Stop modes is enabled or not.
  * @rmtoll
  *  AHB2LPENR   CORDICLPEN      LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR   FMAC1LPEN       LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR   AHBSRAM1LPEN    LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR   AHBSRAM2LPEN    LL_AHB2_GRP1_IsEnabledClockLowPower \n
  *  AHB2LPENR   AHBSRAM3LPEN    LL_AHB2_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM3
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB2LPENR, periphs & LL_AHB2_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_AHB2_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB2 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  AHB2LPENR   CORDICLPEN      LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR   FMAC1LPEN       LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR   AHBSRAM1LPEN    LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR   AHBSRAM2LPEN    LL_AHB2_GRP1_DisableClockLowPower \n
  *  AHB2LPENR   AHBSRAM3LPEN    LL_AHB2_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB2_GRP1_PERIPH_CORDIC
  *         @arg @ref LL_AHB2_GRP1_PERIPH_FMAC1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM1
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM2
  *         @arg @ref LL_AHB2_GRP1_PERIPH_AHBSRAM3
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
  * @brief  Enable AHB3 peripherals clock.
  * @rmtoll
  *  AHB3ENR   RNGEN     LL_AHB3_GRP1_EnableClock \n
  *  AHB3ENR   HASHEN    LL_AHB3_GRP1_EnableClock \n
  *  AHB3ENR   ADC12EN   LL_AHB3_GRP1_EnableClock \n
  *  AHB3ENR   ADC34EN   LL_AHB3_GRP1_EnableClock \n
  *  AHB3ENR   DAC1EN    LL_AHB3_GRP1_EnableClock \n
  *  AHB3ENR   DAC2EN    LL_AHB3_GRP1_EnableClock \n
  *  AHB3ENR   DAC3EN    LL_AHB3_GRP1_EnableClock \n
  *  AHB3ENR   DAC4EN    LL_AHB3_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC34
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC3
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC4
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
  * @brief  Check if AHB3 peripheral clock is enabled or not.
  * @rmtoll
  *  AHB3ENR   RNGEN     LL_AHB3_GRP1_IsEnabledClock \n
  *  AHB3ENR   HASHEN    LL_AHB3_GRP1_IsEnabledClock \n
  *  AHB3ENR   ADC12EN   LL_AHB3_GRP1_IsEnabledClock \n
  *  AHB3ENR   ADC34EN   LL_AHB3_GRP1_IsEnabledClock \n
  *  AHB3ENR   DAC1EN    LL_AHB3_GRP1_IsEnabledClock \n
  *  AHB3ENR   DAC2EN    LL_AHB3_GRP1_IsEnabledClock \n
  *  AHB3ENR   DAC3EN    LL_AHB3_GRP1_IsEnabledClock \n
  *  AHB3ENR   DAC4EN    LL_AHB3_GRP1_IsEnabledClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC34
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC3
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC4
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
  *  AHB3ENR   RNGEN     LL_AHB3_GRP1_DisableClock \n
  *  AHB3ENR   HASHEN    LL_AHB3_GRP1_DisableClock \n
  *  AHB3ENR   ADC12EN   LL_AHB3_GRP1_DisableClock \n
  *  AHB3ENR   ADC34EN   LL_AHB3_GRP1_DisableClock \n
  *  AHB3ENR   DAC1EN    LL_AHB3_GRP1_DisableClock \n
  *  AHB3ENR   DAC2EN    LL_AHB3_GRP1_DisableClock \n
  *  AHB3ENR   DAC3EN    LL_AHB3_GRP1_DisableClock \n
  *  AHB3ENR   DAC4EN    LL_AHB3_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC34
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC3
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC4
  */
__STATIC_INLINE void LL_AHB3_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB3ENR, periphs & LL_AHB3_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force AHB3 peripherals reset.
  * @rmtoll
  *  AHB3RSTR    RNGRST      LL_AHB3_GRP1_ForceReset \n
  *  AHB3RSTR    HASHRST     LL_AHB3_GRP1_ForceReset \n
  *  AHB3RSTR    ADC12RST    LL_AHB3_GRP1_ForceReset \n
  *  AHB3RSTR    ADC34RST    LL_AHB3_GRP1_ForceReset \n
  *  AHB3RSTR    DAC1RST     LL_AHB3_GRP1_ForceReset \n
  *  AHB3RSTR    DAC2RST     LL_AHB3_GRP1_ForceReset \n
  *  AHB3RSTR    DAC3RST     LL_AHB3_GRP1_ForceReset \n
  *  AHB3RSTR    DAC4RST     LL_AHB3_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC34
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC3
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC4
  */
__STATIC_INLINE void LL_AHB3_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->AHB3RSTR, periphs & LL_AHB3_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release AHB3 peripherals reset.
  * @rmtoll
  *  AHB3RSTR    RNGRST      LL_AHB3_GRP1_ReleaseReset \n
  *  AHB3RSTR    HASHRST     LL_AHB3_GRP1_ReleaseReset \n
  *  AHB3RSTR    ADC12RST    LL_AHB3_GRP1_ReleaseReset \n
  *  AHB3RSTR    ADC34RST    LL_AHB3_GRP1_ReleaseReset \n
  *  AHB3RSTR    DAC1RST     LL_AHB3_GRP1_ReleaseReset \n
  *  AHB3RSTR    DAC2RST     LL_AHB3_GRP1_ReleaseReset \n
  *  AHB3RSTR    DAC3RST     LL_AHB3_GRP1_ReleaseReset \n
  *  AHB3RSTR    DAC4RST     LL_AHB3_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC34
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC3
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC4
  */
__STATIC_INLINE void LL_AHB3_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->AHB3RSTR, periphs & LL_AHB3_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable AHB3 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  AHB3LPENR   RNGLPEN     LL_AHB3_GRP1_EnableClockLowPower \n
  *  AHB3LPENR   HASHLPEN    LL_AHB3_GRP1_EnableClockLowPower \n
  *  AHB3LPENR   ADC12LPEN   LL_AHB3_GRP1_EnableClockLowPower \n
  *  AHB3LPENR   ADC34LPEN   LL_AHB3_GRP1_EnableClockLowPower \n
  *  AHB3LPENR   DAC1LPEN    LL_AHB3_GRP1_EnableClockLowPower \n
  *  AHB3LPENR   DAC2LPEN    LL_AHB3_GRP1_EnableClockLowPower \n
  *  AHB3LPENR   DAC3LPEN    LL_AHB3_GRP1_EnableClockLowPower \n
  *  AHB3LPENR   DAC4LPEN    LL_AHB3_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC34
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC3
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC4
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
  * @brief  Check if AHB3 peripheral clocks in Sleep and Stop modes is enabled or not.
  * @rmtoll
  *  AHB3LPENR   RNGLPEN     LL_AHB3_GRP1_IsEnabledClockLowPower \n
  *  AHB3LPENR   HASHLPEN    LL_AHB3_GRP1_IsEnabledClockLowPower \n
  *  AHB3LPENR   ADC12LPEN   LL_AHB3_GRP1_IsEnabledClockLowPower \n
  *  AHB3LPENR   ADC34LPEN   LL_AHB3_GRP1_IsEnabledClockLowPower \n
  *  AHB3LPENR   DAC1LPEN    LL_AHB3_GRP1_IsEnabledClockLowPower \n
  *  AHB3LPENR   DAC2LPEN    LL_AHB3_GRP1_IsEnabledClockLowPower \n
  *  AHB3LPENR   DAC3LPEN    LL_AHB3_GRP1_IsEnabledClockLowPower \n
  *  AHB3LPENR   DAC4LPEN    LL_AHB3_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC34
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC3
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC4
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB3_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB3LPENR, periphs & LL_AHB3_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_AHB3_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB3 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  AHB3LPENR   RNGLPEN     LL_AHB3_GRP1_DisableClockLowPower \n
  *  AHB3LPENR   HASHLPEN    LL_AHB3_GRP1_DisableClockLowPower \n
  *  AHB3LPENR   ADC12LPEN   LL_AHB3_GRP1_DisableClockLowPower \n
  *  AHB3LPENR   ADC34LPEN   LL_AHB3_GRP1_DisableClockLowPower \n
  *  AHB3LPENR   DAC1LPEN    LL_AHB3_GRP1_DisableClockLowPower \n
  *  AHB3LPENR   DAC2LPEN    LL_AHB3_GRP1_DisableClockLowPower \n
  *  AHB3LPENR   DAC3LPEN    LL_AHB3_GRP1_DisableClockLowPower \n
  *  AHB3LPENR   DAC4LPEN    LL_AHB3_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB3_GRP1_PERIPH_RNG
  *         @arg @ref LL_AHB3_GRP1_PERIPH_HASH
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC12
  *         @arg @ref LL_AHB3_GRP1_PERIPH_ADC34
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC1
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC2
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC3
  *         @arg @ref LL_AHB3_GRP1_PERIPH_DAC4
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
  * @brief  Enable AHB4 peripherals clock.
  * @rmtoll
  *  AHB4ENR   GPIOAEN   LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR   GPIOBEN   LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR   GPIOCEN   LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR   GPIODEN   LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR   GPIOEEN   LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR   GPIOFEN   LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR   GPIOGEN   LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR   GPIOHEN   LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR   GPIOIEN   LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR   CRCEN     LL_AHB4_GRP1_EnableClock \n
  *  AHB4ENR   BKPRAMEN  LL_AHB4_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
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
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
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
  * @brief  Check if AHB4 peripheral clock is enabled or not.
  * @rmtoll
  *  AHB4ENR   GPIOAEN   LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR   GPIOBEN   LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR   GPIOCEN   LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR   GPIODEN   LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR   GPIOEEN   LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR   GPIOFEN   LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR   GPIOGEN   LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR   GPIOHEN   LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR   GPIOIEN   LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR   CRCEN     LL_AHB4_GRP1_IsEnabledClock \n
  *  AHB4ENR   BKPRAMEN  LL_AHB4_GRP1_IsEnabledClock
  * @param  periphs This parameter can be a combination of the following values:
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
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
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
  *  AHB4ENR   GPIOAEN   LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR   GPIOBEN   LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR   GPIOCEN   LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR   GPIODEN   LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR   GPIOEEN   LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR   GPIOFEN   LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR   GPIOGEN   LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR   GPIOHEN   LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR   GPIOIEN   LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR   CRCEN     LL_AHB4_GRP1_DisableClock \n
  *  AHB4ENR   BKPRAMEN  LL_AHB4_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
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
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  */
__STATIC_INLINE void LL_AHB4_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB4ENR, periphs & LL_AHB4_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force AHB4 peripherals reset.
  * @rmtoll
  *  AHB4RSTR    GPIOARST    LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR    GPIOBRST    LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR    GPIOCRST    LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR    GPIODRST    LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR    GPIOERST    LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR    GPIOFRST    LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR    GPIOGRST    LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR    GPIOHRST    LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR    GPIOIRST    LL_AHB4_GRP1_ForceReset \n
  *  AHB4RSTR    CRCRST      LL_AHB4_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
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
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  */
__STATIC_INLINE void LL_AHB4_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->AHB4RSTR, periphs & LL_AHB4_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release AHB4 peripherals reset.
  * @rmtoll
  *  AHB4RSTR    GPIOARST    LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR    GPIOBRST    LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR    GPIOCRST    LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR    GPIODRST    LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR    GPIOERST    LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR    GPIOFRST    LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR    GPIOGRST    LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR    GPIOHRST    LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR    GPIOIRST    LL_AHB4_GRP1_ReleaseReset \n
  *  AHB4RSTR    CRCRST      LL_AHB4_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
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
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  */
__STATIC_INLINE void LL_AHB4_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->AHB4RSTR, periphs & LL_AHB4_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable AHB4 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  AHB4LPENR    GPIOALPEN     LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR    GPIOBLPEN     LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR    GPIOCLPEN     LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR    GPIODLPEN     LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR    GPIOELPEN     LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR    GPIOFLPEN     LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR    GPIOGLPEN     LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR    GPIOHLPEN     LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR    GPIOILPEN     LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR    CRCLPEN       LL_AHB4_GRP1_EnableClockLowPower \n
  *  AHB4LPENR    BKPRAMLPEN    LL_AHB4_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
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
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
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
  * @brief  Check if AHB4 peripheral clocks in Sleep and Stop modes is enabled or not.
  * @rmtoll
  *  AHB4LPENR   GPIOALPEN      LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR   GPIOBLPEN      LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR   GPIOCLPEN      LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR   GPIODLPEN      LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR   GPIOELPEN      LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR   GPIOFLPEN      LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR   GPIOGLPEN      LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR   GPIOHLPEN      LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR   GPIOILPEN      LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR   CRCLPEN        LL_AHB4_GRP1_IsEnabledClockLowPower \n
  *  AHB4LPENR   BKPRAMLPEN     LL_AHB4_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
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
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB4_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB4LPENR, periphs & LL_AHB4_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_AHB4_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB4 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  AHB4LPENR    GPIOALPEN    LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR    GPIOBLPEN    LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR    GPIOCLPEN    LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR    GPIODLPEN    LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR    GPIOELPEN    LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR    GPIOFLPEN    LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR    GPIOGLPEN    LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR    GPIOHLPEN    LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR    GPIOILPEN    LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR    CRCLPEN      LL_AHB4_GRP1_DisableClockLowPower \n
  *  AHB4LPENR    BKPRAMLPEN   LL_AHB4_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
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
  *         @arg @ref LL_AHB4_GRP1_PERIPH_CRC
  *         @arg @ref LL_AHB4_GRP1_PERIPH_BKPRAM
  */
__STATIC_INLINE void LL_AHB4_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB4LPENR, periphs & LL_AHB4_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB5 AHB5
  * @{
  */

/**
  * @brief  Enable AHB5 peripherals clock.
  * @rmtoll
  *  AHB5ENR    HPDMA1EN    LL_AHB5_GRP1_EnableClock \n
  *  AHB5ENR    FMCEN       LL_AHB5_GRP1_EnableClock \n
  *  AHB5ENR    XSPI1EN     LL_AHB5_GRP1_EnableClock \n
  *  AHB5ENR    SDMMC1EN    LL_AHB5_GRP1_EnableClock \n
  *  AHB5ENR    NPUEN       LL_AHB5_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_NPU (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_AHB5_GRP1_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->AHB5ENR, periphs & LL_AHB5_GRP1_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->AHB5ENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB5 peripheral clock is enabled or not.
  * @rmtoll
  *  AHB5ENR    HPDMA1EN      LL_AHB5_GRP1_IsEnabledClock \n
  *  AHB5ENR    FMCEN         LL_AHB5_GRP1_IsEnabledClock \n
  *  AHB5ENR    XSPI1EN       LL_AHB5_GRP1_IsEnabledClock \n
  *  AHB5ENR    SDMMC1EN      LL_AHB5_GRP1_IsEnabledClock \n
  *  AHB5ENR    NPUEN         LL_AHB5_GRP1_IsEnabledClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_NPU (*)
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB5_GRP1_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB5ENR, periphs & LL_AHB5_GRP1_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_AHB5_GRP1_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB5 peripherals clock.
  * @rmtoll
  *  AHB5ENR    HPDMA1EN      LL_AHB5_GRP1_DisableClock \n
  *  AHB5ENR    FMCEN         LL_AHB5_GRP1_DisableClock \n
  *  AHB5ENR    XSPI1EN       LL_AHB5_GRP1_DisableClock \n
  *  AHB5ENR    SDMMC1EN      LL_AHB5_GRP1_DisableClock \n
  *  AHB5ENR    NPUEN         LL_AHB5_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_NPU (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_AHB5_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB5ENR, periphs & LL_AHB5_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force AHB5 peripherals reset.
  * @rmtoll
  *  AHB5RSTR   HPDMA1RST     LL_AHB5_GRP1_ForceReset \n
  *  AHB5RSTR   FMCRST        LL_AHB5_GRP1_ForceReset \n
  *  AHB5RSTR   XSPI1RST      LL_AHB5_GRP1_ForceReset \n
  *  AHB5RSTR   SDMMC1RST     LL_AHB5_GRP1_ForceReset \n
  *  AHB5RSTR   NPURST        LL_AHB5_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_NPU (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_AHB5_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->AHB5RSTR, periphs & LL_AHB5_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release AHB5 peripherals reset.
  * @rmtoll
  *  AHB5RSTR   HPDMA1RST     LL_AHB5_GRP1_ReleaseReset \n
  *  AHB5RSTR   FMCRST        LL_AHB5_GRP1_ReleaseReset \n
  *  AHB5RSTR   XSPI1RST      LL_AHB5_GRP1_ReleaseReset \n
  *  AHB5RSTR   SDMMC1RST     LL_AHB5_GRP1_ReleaseReset \n
  *  AHB5RSTR   NPURST        LL_AHB5_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_NPU (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_AHB5_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->AHB5RSTR, periphs & LL_AHB5_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable AHB5 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  AHB5LPENR    HPDMA1LPEN      LL_AHB5_GRP1_EnableClockLowPower \n
  *  AHB5LPENR    FLASHLPEN       LL_AHB5_GRP1_EnableClockLowPower \n
  *  AHB5LPENR    FMCLPEN         LL_AHB5_GRP1_EnableClockLowPower \n
  *  AHB5LPENR    XSPI1LPEN       LL_AHB5_GRP1_EnableClockLowPower \n
  *  AHB5LPENR    SDMMC1LPEN      LL_AHB5_GRP1_EnableClockLowPower \n
  *  AHB5LPENR    AXISRAMLPEN     LL_AHB5_GRP1_EnableClockLowPower \n
  *  AHB5LPENR    DTCM1LPEN       LL_AHB5_GRP1_EnableClockLowPower \n
  *  AHB5LPENR    DTCM2LPEN       LL_AHB5_GRP1_EnableClockLowPower \n
  *  AHB5LPENR    ITCMLPEN        LL_AHB5_GRP1_EnableClockLowPower \n
  *  AHB5LPENR    NPULPEN         LL_AHB5_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_AXISRAM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DTCM1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DTCM2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ITCM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_NPU (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_AHB5_GRP1_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->AHB5LPENR, periphs & LL_AHB5_GRP1_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->AHB5LPENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB5 peripheral clocks in Sleep and Stop modes is enabled or not.
  * @rmtoll
  *  AHB5LPENR    HPDMA1LPEN    LL_AHB5_GRP1_IsEnabledClockLowPower \n
  *  AHB5LPENR    FLASHLPEN     LL_AHB5_GRP1_IsEnabledClockLowPower \n
  *  AHB5LPENR    FMCLPEN       LL_AHB5_GRP1_IsEnabledClockLowPower \n
  *  AHB5LPENR    XSPI1LPEN     LL_AHB5_GRP1_IsEnabledClockLowPower \n
  *  AHB5LPENR    SDMMC1LPEN    LL_AHB5_GRP1_IsEnabledClockLowPower \n
  *  AHB5LPENR    AXISRAMLPEN   LL_AHB5_GRP1_IsEnabledClockLowPower \n
  *  AHB5LPENR    DTCM1LPEN     LL_AHB5_GRP1_IsEnabledClockLowPower \n
  *  AHB5LPENR    DTCM2LPEN     LL_AHB5_GRP1_IsEnabledClockLowPower \n
  *  AHB5LPENR    ITCMLPEN      LL_AHB5_GRP1_IsEnabledClockLowPower \n
  *  AHB5LPENR    NPULPEN       LL_AHB5_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_AXISRAM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DTCM1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DTCM2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ITCM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_NPU (*)
  *
  *        (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_AHB5_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->AHB5LPENR, periphs & LL_AHB5_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_AHB5_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable AHB5 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  AHB5LPENR    HPDMA1LPEN      LL_AHB5_GRP1_DisableClockLowPower \n
  *  AHB5LPENR    FLASHLPEN       LL_AHB5_GRP1_DisableClockLowPower \n
  *  AHB5LPENR    FMCLPEN         LL_AHB5_GRP1_DisableClockLowPower \n
  *  AHB5LPENR    XSPI1LPEN       LL_AHB5_GRP1_DisableClockLowPower \n
  *  AHB5LPENR    SDMMC1LPEN      LL_AHB5_GRP1_DisableClockLowPower \n
  *  AHB5LPENR    AXISRAMLPEN     LL_AHB5_GRP1_DisableClockLowPower \n
  *  AHB5LPENR    DTCM1LPEN       LL_AHB5_GRP1_DisableClockLowPower \n
  *  AHB5LPENR    DTCM2LPEN       LL_AHB5_GRP1_DisableClockLowPower \n
  *  AHB5LPENR    ITCMLPEN        LL_AHB5_GRP1_DisableClockLowPower \n
  *  AHB5LPENR    NPULPEN         LL_AHB5_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ALL
  *         @arg @ref LL_AHB5_GRP1_PERIPH_HPDMA1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FLASH
  *         @arg @ref LL_AHB5_GRP1_PERIPH_FMC
  *         @arg @ref LL_AHB5_GRP1_PERIPH_XSPI1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_SDMMC1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_AXISRAM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DTCM1
  *         @arg @ref LL_AHB5_GRP1_PERIPH_DTCM2
  *         @arg @ref LL_AHB5_GRP1_PERIPH_ITCM
  *         @arg @ref LL_AHB5_GRP1_PERIPH_NPU (*)
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_AHB5_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->AHB5LPENR, periphs & LL_AHB5_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1_1 APB1_1
  * @{
  */

/**
  * @brief  Enable APB1_1 peripherals clock.
  * @rmtoll
  *  APB1ENR1   TIM2EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   TIM3EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   TIM4EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   TIM5EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   TIM6EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   TIM7EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   TIM12EN     LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   TIM13EN     LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   TIM14EN     LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   LPTIM1EN    LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   WWDGEN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   TIM10EN     LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   TIM11EN     LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   SPI2EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   SPI3EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   USART2EN    LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   USART3EN    LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   UART4EN     LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   UART5EN     LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   I2C1EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   I2C2EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   I2C3EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   I3C1EN      LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   UART7EN     LL_APB1_GRP1_EnableClock \n
  *  APB1ENR1   UART8EN     LL_APB1_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB1ENR1, periphs & LL_APB1_GRP1_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB1ENR1, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1_1 peripheral clock is enabled or not.
  * @rmtoll
  *  APB1ENR1   TIM2EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   TIM3EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   TIM4EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   TIM5EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   TIM6EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   TIM7EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   TIM12EN     LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   TIM13EN     LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   TIM14EN     LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   LPTIM1EN    LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   WWDGEN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   TIM10EN     LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   TIM11EN     LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   SPI2EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   SPI3EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   USART2EN    LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   USART3EN    LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   UART4EN     LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   UART5EN     LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   I2C1EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   I2C2EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   I2C3EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   I3C1EN      LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   UART7EN     LL_APB1_GRP1_IsEnabledClock \n
  *  APB1ENR1   UART8EN     LL_APB1_GRP1_IsEnabledClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB1ENR1, periphs & LL_APB1_GRP1_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_APB1_GRP1_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1_1 peripherals clock.
  * @rmtoll
  *  APB1ENR1   TIM2EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   TIM3EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   TIM4EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   TIM5EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   TIM6EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   TIM7EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   TIM12EN     LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   TIM13EN     LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   TIM14EN     LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   LPTIM1EN    LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   WWDGEN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   TIM10EN     LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   TIM11EN     LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   SPI2EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   SPI3EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   USART2EN    LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   USART3EN    LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   UART4EN     LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   UART5EN     LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   I2C1EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   I2C2EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   I2C3EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   I3C1EN      LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   UART7EN     LL_APB1_GRP1_DisableClock \n
  *  APB1ENR1   UART8EN     LL_APB1_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB1ENR1, periphs & LL_APB1_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force APB1_1 peripherals reset.
  * @rmtoll
  *  APB1RSTR1    TIM2RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    TIM3RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    TIM4RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    TIM5RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    TIM6RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    TIM7RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    TIM12RST    LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    TIM13RST    LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    TIM14RST    LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    LPTIM1RST   LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    TIM10RST    LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    TIM11RST    LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    SPI2RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    SPI3RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    USART2RST   LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    USART3RST   LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    UART4RST    LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    UART5RST    LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    I2C1RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    I2C2RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    I2C3RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    I3C1RST     LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    UART7RST    LL_APB1_GRP1_ForceReset \n
  *  APB1RSTR1    UART8RST    LL_APB1_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  */
__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->APB1RSTR1, periphs & LL_APB1_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release APB1_1 peripherals reset.
  * @rmtoll
  *  APB1RSTR1    TIM2RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    TIM3RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    TIM4RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    TIM5RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    TIM6RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    TIM7RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    TIM12RST    LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    TIM13RST    LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    TIM14RST    LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    LPTIM1RST   LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    TIM10RST    LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    TIM11RST    LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    SPI2RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    SPI3RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    USART2RST   LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    USART3RST   LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    UART4RST    LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    UART5RST    LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    I2C1RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    I2C2RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    I2C3RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    I3C1RST     LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    UART7RST    LL_APB1_GRP1_ReleaseReset \n
  *  APB1RSTR1    UART8RST    LL_APB1_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  */
__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->APB1RSTR1, periphs & LL_APB1_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable APB1_1 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  APB1LPENR1   TIM2LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   TIM3LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   TIM4LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   TIM5LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   TIM6LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   TIM7LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   TIM12LPEN     LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   TIM13LPEN     LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   TIM14LPEN     LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   LPTIM1LPEN    LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   WWDGLPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   TIM10LPEN     LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   TIM11LPEN     LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   SPI2LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   SPI3LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   USART2LPEN    LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   USART3LPEN    LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   UART4LPEN     LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   UART5LPEN     LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   I2C1LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   I2C2LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   I2C3LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   I3C1LPEN      LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   UART7LPEN     LL_APB1_GRP1_EnableClockLowPower \n
  *  APB1LPENR1   UART8LPEN     LL_APB1_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  */
__STATIC_INLINE void LL_APB1_GRP1_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB1LPENR1, periphs & LL_APB1_GRP1_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB1LPENR1, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1_1 peripheral clocks in Sleep and Stop modes is enabled or not.
  * @rmtoll
  *  APB1LPENR1   TIM2LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   TIM3LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   TIM4LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   TIM5LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   TIM6LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   TIM7LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   TIM12LPEN     LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   TIM13LPEN     LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   TIM14LPEN     LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   LPTIM1LPEN    LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   WWDGLPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   TIM10LPEN     LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   TIM11LPEN     LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   SPI2LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   SPI3LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   USART2LPEN    LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   USART3LPEN    LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   UART4LPEN     LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   UART5LPEN     LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   I2C1LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   I2C2LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   I2C3LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   I3C1LPEN      LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   UART7LPEN     LL_APB1_GRP1_IsEnabledClockLowPower \n
  *  APB1LPENR1   UART8LPEN     LL_APB1_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB1LPENR1, periphs & LL_APB1_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_APB1_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1_1 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  APB1LPENR1   TIM2LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   TIM3LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   TIM4LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   TIM5LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   TIM6LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   TIM7LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   TIM12LPEN     LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   TIM13LPEN     LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   TIM14LPEN     LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   LPTIM1LPEN    LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   WWDGLPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   TIM10LPEN     LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   TIM11LPEN     LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   SPI2LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   SPI3LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   USART2LPEN    LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   USART3LPEN    LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   UART4LPEN     LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   UART5LPEN     LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   I2C1LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   I2C2LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   I2C3LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   I3C1LPEN      LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   UART7LPEN     LL_APB1_GRP1_DisableClockLowPower \n
  *  APB1LPENR1   UART8LPEN     LL_APB1_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM4
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM5
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM6
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM7
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM12
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM13
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref LL_APB1_GRP1_PERIPH_LPTIM1
  *         @arg @ref LL_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM10
  *         @arg @ref LL_APB1_GRP1_PERIPH_TIM11
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI2
  *         @arg @ref LL_APB1_GRP1_PERIPH_SPI3
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART2
  *         @arg @ref LL_APB1_GRP1_PERIPH_USART3
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART4
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART5
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C2
  *         @arg @ref LL_APB1_GRP1_PERIPH_I2C3
  *         @arg @ref LL_APB1_GRP1_PERIPH_I3C1
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART7
  *         @arg @ref LL_APB1_GRP1_PERIPH_UART8
  */
__STATIC_INLINE void LL_APB1_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB1LPENR1, periphs & LL_APB1_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1_2 APB1_2
  * @{
  */

/**
  * @brief  Enable APB1_2 peripherals clock.
  * @rmtoll
  *  APB1ENR2   CRSEN     LL_APB1_GRP2_EnableClock \n
  *  APB1ENR2   FDCANEN   LL_APB1_GRP2_EnableClock \n
  *  APB1ENR2   UCPD1EN   LL_APB1_GRP2_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB1ENR2, periphs & LL_APB1_GRP2_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB1ENR2, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1_2 peripheral clock is enabled or not.
  * @rmtoll
  *  APB1ENR2   CRSEN       LL_APB1_GRP2_IsEnabledClock \n
  *  APB1ENR2   FDCANEN     LL_APB1_GRP2_IsEnabledClock \n
  *  APB1ENR2   UCPD1EN     LL_APB1_GRP2_IsEnabledClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB1ENR2, periphs & LL_APB1_GRP2_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_APB1_GRP2_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1_2 peripherals clock.
  * @rmtoll
  *  APB1ENR2   CRSEN       LL_APB1_GRP2_DisableClock \n
  *  APB1ENR2   FDCANEN     LL_APB1_GRP2_DisableClock \n
  *  APB1ENR2   UCPD1EN     LL_APB1_GRP2_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB1ENR2, periphs & LL_APB1_GRP2_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force APB1_2 peripherals reset.
  * @rmtoll
  *  APB1RSTR2    CRSRST      LL_APB1_GRP2_ForceReset \n
  *  APB1RSTR2    FDCANRST    LL_APB1_GRP2_ForceReset \n
  *  APB1RSTR2    UCPD1RST    LL_APB1_GRP2_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  */
__STATIC_INLINE void LL_APB1_GRP2_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->APB1RSTR2, periphs & LL_APB1_GRP2_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release APB1_2 peripherals reset.
  * @rmtoll
  *  APB1RSTR2    CRSRST      LL_APB1_GRP2_ReleaseReset \n
  *  APB1RSTR2    FDCANRST    LL_APB1_GRP2_ReleaseReset \n
  *  APB1RSTR2    UCPD1RST    LL_APB1_GRP2_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  */
__STATIC_INLINE void LL_APB1_GRP2_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->APB1RSTR2, periphs & LL_APB1_GRP2_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable APB1_2 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  APB1LPENR2   CRSLPEN       LL_APB1_GRP2_EnableClockLowPower \n
  *  APB1LPENR2   FDCANLPEN     LL_APB1_GRP2_EnableClockLowPower \n
  *  APB1LPENR2   UCPD1LPEN     LL_APB1_GRP2_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  */
__STATIC_INLINE void LL_APB1_GRP2_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB1LPENR2, periphs & LL_APB1_GRP2_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB1LPENR2, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1_2 peripheral clocks in Sleep and Stop modes is enabled or not.
  * @rmtoll
  *  APB1LPENR2   CRSLPEN       LL_APB1_GRP2_IsEnabledClockLowPower \n
  *  APB1LPENR2   FDCANLPEN     LL_APB1_GRP2_IsEnabledClockLowPower \n
  *  APB1LPENR2   UCPD1LPEN     LL_APB1_GRP2_IsEnabledClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB1_GRP2_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB1LPENR2, periphs & LL_APB1_GRP2_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_APB1_GRP2_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB1_2 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  APB1LPENR2   CRSLPEN       LL_APB1_GRP2_DisableClockLowPower \n
  *  APB1LPENR2   FDCANLPEN     LL_APB1_GRP2_DisableClockLowPower \n
  *  APB1LPENR2   UCPD1LPEN     LL_APB1_GRP2_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB1_GRP2_PERIPH_ALL
  *         @arg @ref LL_APB1_GRP2_PERIPH_CRS
  *         @arg @ref LL_APB1_GRP2_PERIPH_FDCAN
  *         @arg @ref LL_APB1_GRP2_PERIPH_UCPD1
  */
__STATIC_INLINE void LL_APB1_GRP2_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB1LPENR2, periphs & LL_APB1_GRP2_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB2 APB2
  * @{
  */

/**
  * @brief  Enable APB2 peripherals clock.
  * @rmtoll
  *  APB2ENR    TIM1EN        LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    TIM8EN        LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    TIM20EN       LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    USART1EN      LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    USART6EN      LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    UART9EN       LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    USART10EN     LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    SPI1EN        LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    SPI4EN        LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    TIM15EN       LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    TIM16EN       LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    TIM17EN       LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    TIM9EN        LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    SPI5EN        LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    HRTIM1EN      LL_APB2_GRP1_EnableClock \n
  *  APB2ENR    HRTIM2EN      LL_APB2_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM20
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_UART9
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART10
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM2
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
  * @brief  Check if APB2 peripheral clock is enabled or not.
  * @rmtoll
  *  APB2ENR    TIM1EN        LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    TIM8EN        LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    TIM20EN       LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    USART1EN      LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    USART6EN      LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    UART9EN       LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    USART10EN     LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    SPI1EN        LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    SPI4EN        LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    TIM15EN       LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    TIM16EN       LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    TIM17EN       LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    TIM9EN        LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    SPI5EN        LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    HRTIM1EN      LL_APB2_GRP1_IsEnabledClock \n
  *  APB2ENR    HRTIM2EN      LL_APB2_GRP1_IsEnabledClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM20
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_UART9
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART10
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM2
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
  *  APB2ENR    TIM1EN        LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    TIM8EN        LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    TIM20EN       LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    USART1EN      LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    USART6EN      LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    UART9EN       LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    USART10EN     LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    SPI1EN        LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    SPI4EN        LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    TIM15EN       LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    TIM16EN       LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    TIM17EN       LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    TIM9EN        LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    SPI5EN        LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    HRTIM1EN      LL_APB2_GRP1_DisableClock \n
  *  APB2ENR    HRTIM2EN      LL_APB2_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM20
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_UART9
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART10
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM2
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB2ENR, periphs & LL_APB2_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force APB2 peripherals reset.
  * @rmtoll
  *  APB2RSTR   TIM1RST         LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   TIM8RST         LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   TIM20RST        LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   USART1RST       LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   USART6RST       LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   UART9RST        LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   USART10RST      LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   SPI1RST         LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   SPI4RST         LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   TIM15RST        LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   TIM16RST        LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   TIM17RST        LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   TIM9RST         LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   SPI5RST         LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   HRTIM1RST       LL_APB2_GRP1_ForceReset \n
  *  APB2RSTR   HRTIM2RST       LL_APB2_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM20
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_UART9
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART10
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM2
  */
__STATIC_INLINE void LL_APB2_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->APB2RSTR, periphs & LL_APB2_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release APB2 peripherals reset.
  * @rmtoll
  *  APB2RSTR   TIM1RST         LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   TIM8RST         LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   TIM20RST        LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   USART1RST       LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   USART6RST       LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   UART9RST        LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   USART10RST      LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   SPI1RST         LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   SPI4RST         LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   TIM15RST        LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   TIM16RST        LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   TIM17RST        LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   TIM9RST         LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   SPI5RST         LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   HRTIM1RST       LL_APB2_GRP1_ReleaseReset \n
  *  APB2RSTR   HRTIM2RST       LL_APB2_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM20
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_UART9
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART10
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM2
  */
__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->APB2RSTR, periphs & LL_APB2_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable APB2 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  APB2LPENR    TIM1LPEN      LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    TIM8LPEN      LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    TIM20LPEN     LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    USART1LPEN    LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    USART6LPEN    LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    UART9LPEN     LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    USART10LPEN   LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    SPI1LPEN      LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    SPI4LPEN      LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    TIM15LPEN     LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    TIM16LPEN     LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    TIM17LPEN     LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    TIM9LPEN      LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    SPI5LPEN      LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    HRTIM1LPEN    LL_APB2_GRP1_EnableClockLowPower \n
  *  APB2LPENR    HRTIM2LPEN    LL_APB2_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM20
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_UART9
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART10
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM2
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
  * @brief  Check if APB2 peripheral clocks in Sleep and Stop modes is enabled or not.
  * @rmtoll
  *  APB2LPENR    TIM1LPEN      LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    TIM8LPEN      LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    TIM20LPEN     LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    USART1LPEN    LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    USART6LPEN    LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    UART9LPEN     LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    USART10LPEN   LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    SPI1LPEN      LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    SPI4LPEN      LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    TIM15LPEN     LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    TIM16LPEN     LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    TIM17LPEN     LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    TIM9LPEN      LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    SPI5LPEN      LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    HRTIM1LPEN    LL_APB2_GRP1_IsEnabledClockLowPower \n
  *  APB2LPENR    HRTIM2LPEN    LL_APB2_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM20
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_UART9
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART10
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM2
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB2LPENR, periphs & LL_APB2_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_APB2_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB2 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  APB2LPENR    TIM1LPEN      LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    TIM8LPEN      LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    TIM20LPEN     LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    USART1LPEN    LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    USART6LPEN    LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    UART9LPEN     LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    USART10LPEN   LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    SPI1LPEN      LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    SPI4LPEN      LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    TIM15LPEN     LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    TIM16LPEN     LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    TIM17LPEN     LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    TIM9LPEN      LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    SPI5LPEN      LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    HRTIM1LPEN    LL_APB2_GRP1_DisableClockLowPower \n
  *  APB2LPENR    HRTIM2LPEN    LL_APB2_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB2_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM8
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM20
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART1
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART6
  *         @arg @ref LL_APB2_GRP1_PERIPH_UART9
  *         @arg @ref LL_APB2_GRP1_PERIPH_USART10
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI1
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI4
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM15
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM16
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM17
  *         @arg @ref LL_APB2_GRP1_PERIPH_TIM9
  *         @arg @ref LL_APB2_GRP1_PERIPH_SPI5
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM1
  *         @arg @ref LL_APB2_GRP1_PERIPH_HRTIM2
  */
__STATIC_INLINE void LL_APB2_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB2LPENR, periphs & LL_APB2_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB4 APB4
  * @{
  */

/**
  * @brief  Enable APB4 peripherals clock.
  * @rmtoll
  *  APB4ENR    SBSEN       LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    LPUART1EN   LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    SPI6EN      LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    LPTIM2EN    LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    LPTIM3EN    LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    LPTIM4EN    LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    LPTIM5EN    LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    VREFEN      LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    RTCAPBEN    LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    DTSEN       LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    COMP12EN    LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    COMP34EN    LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    COMP56EN    LL_APB4_GRP1_EnableClock \n
  *  APB4ENR    COMP78EN    LL_APB4_GRP1_EnableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP34
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP56
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP78
  */
__STATIC_INLINE void LL_APB4_GRP1_EnableClock(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB4ENR, periphs & LL_APB4_GRP1_PERIPH_ALL_EN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB4ENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB4 peripheral clock is enabled or not.
  * @rmtoll
  *  APB4ENR    SBSEN       LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    LPUART1EN   LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    SPI6EN      LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    LPTIM2EN    LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    LPTIM3EN    LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    LPTIM4EN    LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    LPTIM5EN    LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    VREFEN      LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    RTCAPBEN    LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    DTSEN       LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    COMP12EN    LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    COMP34EN    LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    COMP56EN    LL_APB4_GRP1_IsEnabledClock \n
  *  APB4ENR    COMP78EN    LL_APB4_GRP1_IsEnabledClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP34
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP56
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP78
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB4_GRP1_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB4ENR, periphs & LL_APB4_GRP1_PERIPH_ALL_EN_MASK) == \
           (periphs & LL_APB4_GRP1_PERIPH_ALL_EN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB4 peripherals clock.
  * @rmtoll
  *  APB4ENR    SBSEN       LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    LPUART1EN   LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    SPI6EN      LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    LPTIM2EN    LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    LPTIM3EN    LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    LPTIM4EN    LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    LPTIM5EN    LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    VREFEN      LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    RTCAPBEN    LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    DTSEN       LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    COMP12EN    LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    COMP34EN    LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    COMP56EN    LL_APB4_GRP1_DisableClock \n
  *  APB4ENR    COMP78EN    LL_APB4_GRP1_DisableClock
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP34
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP56
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP78
  */
__STATIC_INLINE void LL_APB4_GRP1_DisableClock(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB4ENR, periphs & LL_APB4_GRP1_PERIPH_ALL_EN_MASK);
}

/**
  * @brief  Force APB4 peripherals reset.
  * @rmtoll
  *  APB4RSTR   SBSRST        LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   LPUART1RST    LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   SPI6RST       LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   LPTIM2RST     LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   LPTIM3RST     LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   LPTIM4RST     LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   LPTIM5RST     LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   VREFRST       LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   DTSRST        LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   COMP12RST     LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   COMP34RST     LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   COMP56RST     LL_APB4_GRP1_ForceReset \n
  *  APB4RSTR   COMP78RST     LL_APB4_GRP1_ForceReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP34
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP56
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP78
  */
__STATIC_INLINE void LL_APB4_GRP1_ForceReset(uint32_t periphs)
{
  STM32_SET_BIT(RCC->APB4RSTR, periphs & LL_APB4_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Release APB4 peripherals reset.
  * @rmtoll
  *  APB4RSTR   SBSRST        LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   LPUART1RST    LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   SPI6RST       LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   LPTIM2RST     LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   LPTIM3RST     LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   LPTIM4RST     LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   LPTIM5RST     LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   VREFRST       LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   DTSRST        LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   COMP12RST     LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   COMP34RST     LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   COMP56RST     LL_APB4_GRP1_ReleaseReset \n
  *  APB4RSTR   COMP78RST     LL_APB4_GRP1_ReleaseReset
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP34
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP56
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP78
  */
__STATIC_INLINE void LL_APB4_GRP1_ReleaseReset(uint32_t periphs)
{
  STM32_CLEAR_BIT(RCC->APB4RSTR, periphs & LL_APB4_GRP1_PERIPH_ALL_RST_MASK);
}

/**
  * @brief  Enable APB4 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  APB4LPENR    SBSLPEN       LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    LPUART1LPEN   LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    SPI6LPEN      LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    LPTIM2LPEN    LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    LPTIM3LPEN    LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    LPTIM4LPEN    LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    LPTIM5LPEN    LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    VREFLPEN      LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    RTCAPBLPEN    LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    DTSLPEN       LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    COMP12LPEN    LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    COMP34LPEN    LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    COMP56LPEN    LL_APB4_GRP1_EnableClockLowPower \n
  *  APB4LPENR    COMP78LPEN    LL_APB4_GRP1_EnableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP34
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP56
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP78
  */
__STATIC_INLINE void LL_APB4_GRP1_EnableClockLowPower(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->APB4LPENR, periphs & LL_APB4_GRP1_PERIPH_ALL_LPEN_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->APB4LPENR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB4 peripheral clocks in Sleep and Stop modes is enabled or not.
  * @rmtoll
  *  APB4LPENR    SBSLPEN       LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    LPUART1LPEN   LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    SPI6LPEN      LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    LPTIM2LPEN    LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    LPTIM3LPEN    LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    LPTIM4LPEN    LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    LPTIM5LPEN    LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    VREFLPEN      LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    RTCAPBLPEN    LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    DTSLPEN       LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    COMP12LPEN    LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    COMP34LPEN    LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    COMP56LPEN    LL_APB4_GRP1_IsEnabledClockLowPower \n
  *  APB4LPENR    COMP78LPEN    LL_APB4_GRP1_IsEnabledClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP34
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP56
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP78
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_APB4_GRP1_IsEnabledClockLowPower(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->APB4LPENR, periphs & LL_APB4_GRP1_PERIPH_ALL_LPEN_MASK) == \
           (periphs & LL_APB4_GRP1_PERIPH_ALL_LPEN_MASK)) ? 1UL : 0UL);
}

/**
  * @brief  Disable APB4 peripheral clocks in Sleep and Stop modes.
  * @rmtoll
  *  APB4LPENR    SBSLPEN         LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    LPUART1LPEN     LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    SPI6LPEN        LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    LPTIM2LPEN      LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    LPTIM3LPEN      LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    LPTIM4LPEN      LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    LPTIM5LPEN      LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    VREFLPEN        LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    RTCAPBLPEN      LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    DTSLPEN         LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    COMP12LPEN      LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    COMP34LPEN      LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    COMP56LPEN      LL_APB4_GRP1_DisableClockLowPower \n
  *  APB4LPENR    COMP78LPEN      LL_APB4_GRP1_DisableClockLowPower
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_APB4_GRP1_PERIPH_ALL
  *         @arg @ref LL_APB4_GRP1_PERIPH_SBS
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPUART1
  *         @arg @ref LL_APB4_GRP1_PERIPH_SPI6
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM2
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM3
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM4
  *         @arg @ref LL_APB4_GRP1_PERIPH_LPTIM5
  *         @arg @ref LL_APB4_GRP1_PERIPH_VREFBUF
  *         @arg @ref LL_APB4_GRP1_PERIPH_RTCAPB
  *         @arg @ref LL_APB4_GRP1_PERIPH_DTS
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP12
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP34
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP56
  *         @arg @ref LL_APB4_GRP1_PERIPH_COMP78
  */
__STATIC_INLINE void LL_APB4_GRP1_DisableClockLowPower(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(RCC->APB4LPENR, periphs & LL_APB4_GRP1_PERIPH_ALL_LPEN_MASK);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_CKG CKG
  * @{
  */

/**
  * @brief  Enable clock gating for AXI bus peripherals.
  * @rmtoll
  *  CKGDISR    AXICKG          LL_CKG_Enable \n
  *  CKGDISR    AHBMCKG         LL_CKG_Enable \n
  *  CKGDISR    SDMMC1CKG       LL_CKG_Enable \n
  *  CKGDISR    HPDMA1CKG       LL_CKG_Enable \n
  *  CKGDISR    CPUCKG          LL_CKG_Enable \n
  *  CKGDISR    NPU0CKG         LL_CKG_Enable \n
  *  CKGDISR    NPU1CKG         LL_CKG_Enable \n
  *  CKGDISR    AHBSCKG         LL_CKG_Enable \n
  *  CKGDISR    AHBICCKG        LL_CKG_Enable \n
  *  CKGDISR    FMCCKG          LL_CKG_Enable \n
  *  CKGDISR    XSPI1CKG        LL_CKG_Enable \n
  *  CKGDISR    AXISRAM4CKG     LL_CKG_Enable \n
  *  CKGDISR    AXISRAM3CKG     LL_CKG_Enable \n
  *  CKGDISR    AXISRAM2CKG     LL_CKG_Enable \n
  *  CKGDISR    AXISRAM1CKG     LL_CKG_Enable \n
  *  CKGDISR    FLASHCKG        LL_CKG_Enable \n
  *  CKGDISR    EXTICKG         LL_CKG_Enable \n
  *  CKGDISR    JTAGCKG         LL_CKG_Enable
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_CKG_PERIPH_ALL
  *         @arg @ref LL_CKG_PERIPH_AXI
  *         @arg @ref LL_CKG_PERIPH_AHBM
  *         @arg @ref LL_CKG_PERIPH_SDMMC1
  *         @arg @ref LL_CKG_PERIPH_HPDMA1
  *         @arg @ref LL_CKG_PERIPH_CPU
  *         @arg @ref LL_CKG_PERIPH_NPU0 (*)
  *         @arg @ref LL_CKG_PERIPH_NPU1 (*)
  *         @arg @ref LL_CKG_PERIPH_AHBS
  *         @arg @ref LL_CKG_PERIPH_AHBIC
  *         @arg @ref LL_CKG_PERIPH_FMC
  *         @arg @ref LL_CKG_PERIPH_XSPI1
  *         @arg @ref LL_CKG_PERIPH_AXISRAM4
  *         @arg @ref LL_CKG_PERIPH_AXISRAM3
  *         @arg @ref LL_CKG_PERIPH_AXISRAM2
  *         @arg @ref LL_CKG_PERIPH_AXISRAM1
  *         @arg @ref LL_CKG_PERIPH_FLASH
  *         @arg @ref LL_CKG_PERIPH_EXTI
  *         @arg @ref LL_CKG_PERIPH_JTAG
  *
  *        (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_CKG_Enable(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_CLEAR_BIT_32(RCC->CKGDISR, periphs & LL_CKG_PERIPH_ALL_DIS_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->CKGDISR, periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AXI bus peripherals clock gating is enabled or not.
  * @rmtoll
  *  CKGDISR    AXICKG          LL_CKG_IsEnabled \n
  *  CKGDISR    AHBMCKG         LL_CKG_IsEnabled \n
  *  CKGDISR    SDMMC1CKG       LL_CKG_IsEnabled \n
  *  CKGDISR    HPDMA1CKG       LL_CKG_IsEnabled \n
  *  CKGDISR    CPUCKG          LL_CKG_IsEnabled \n
  *  CKGDISR    NPU0CKG         LL_CKG_IsEnabled \n
  *  CKGDISR    NPU1CKG         LL_CKG_IsEnabled \n
  *  CKGDISR    AHBSCKG         LL_CKG_IsEnabled \n
  *  CKGDISR    AHBICCKG        LL_CKG_IsEnabled \n
  *  CKGDISR    FMCCKG          LL_CKG_IsEnabled \n
  *  CKGDISR    XSPI1CKG        LL_CKG_IsEnabled \n
  *  CKGDISR    AXISRAM4CKG     LL_CKG_IsEnabled \n
  *  CKGDISR    AXISRAM3CKG     LL_CKG_IsEnabled \n
  *  CKGDISR    AXISRAM2CKG     LL_CKG_IsEnabled \n
  *  CKGDISR    AXISRAM1CKG     LL_CKG_IsEnabled \n
  *  CKGDISR    FLASHCKG        LL_CKG_IsEnabled \n
  *  CKGDISR    EXTICKG         LL_CKG_IsEnabled \n
  *  CKGDISR    JTAGCKG         LL_CKG_IsEnabled
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_CKG_PERIPH_ALL
  *         @arg @ref LL_CKG_PERIPH_AXI
  *         @arg @ref LL_CKG_PERIPH_AHBM
  *         @arg @ref LL_CKG_PERIPH_SDMMC1
  *         @arg @ref LL_CKG_PERIPH_HPDMA1
  *         @arg @ref LL_CKG_PERIPH_CPU
  *         @arg @ref LL_CKG_PERIPH_NPU0 (*)
  *         @arg @ref LL_CKG_PERIPH_NPU1 (*)
  *         @arg @ref LL_CKG_PERIPH_AHBS
  *         @arg @ref LL_CKG_PERIPH_AHBIC
  *         @arg @ref LL_CKG_PERIPH_FMC
  *         @arg @ref LL_CKG_PERIPH_XSPI1
  *         @arg @ref LL_CKG_PERIPH_AXISRAM4
  *         @arg @ref LL_CKG_PERIPH_AXISRAM3
  *         @arg @ref LL_CKG_PERIPH_AXISRAM2
  *         @arg @ref LL_CKG_PERIPH_AXISRAM1
  *         @arg @ref LL_CKG_PERIPH_FLASH
  *         @arg @ref LL_CKG_PERIPH_EXTI
  *         @arg @ref LL_CKG_PERIPH_JTAG
  *
  *       (*) value not defined in all devices.
  * @retval State of periphs (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CKG_IsEnabledClock(uint32_t periphs)
{
  return ((STM32_READ_BIT(RCC->CKGDISR, periphs & LL_CKG_PERIPH_ALL_DIS_MASK) == 0U) ? 1UL : 0UL);
}

/**
  * @brief  Disable clock gating for AXI bus peripherals.
  * @rmtoll
  *  CKGDISR    AXICKG        LL_CKG_Disable \n
  *  CKGDISR    AHBMCKG       LL_CKG_Disable \n
  *  CKGDISR    SDMMC1CKG     LL_CKG_Disable \n
  *  CKGDISR    HPDMA1CKG     LL_CKG_Disable \n
  *  CKGDISR    CPUCKG        LL_CKG_Disable \n
  *  CKGDISR    NPU0CKG       LL_CKG_Disable \n
  *  CKGDISR    NPU1CKG       LL_CKG_Disable \n
  *  CKGDISR    AHBSCKG       LL_CKG_Disable \n
  *  CKGDISR    AHBICCKG      LL_CKG_Disable \n
  *  CKGDISR    FMCCKG        LL_CKG_Disable \n
  *  CKGDISR    XSPI1CKG      LL_CKG_Disable \n
  *  CKGDISR    AXISRAM4CKG   LL_CKG_Disable \n
  *  CKGDISR    AXISRAM3CKG   LL_CKG_Disable \n
  *  CKGDISR    AXISRAM2CKG   LL_CKG_Disable \n
  *  CKGDISR    AXISRAM1CKG   LL_CKG_Disable \n
  *  CKGDISR    FLASHCKG      LL_CKG_Disable \n
  *  CKGDISR    EXTICKG       LL_CKG_Disable \n
  *  CKGDISR    JTAGCKG       LL_CKG_Disable
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_CKG_PERIPH_ALL
  *         @arg @ref LL_CKG_PERIPH_AXI
  *         @arg @ref LL_CKG_PERIPH_AHBM
  *         @arg @ref LL_CKG_PERIPH_SDMMC1
  *         @arg @ref LL_CKG_PERIPH_HPDMA1
  *         @arg @ref LL_CKG_PERIPH_CPU
  *         @arg @ref LL_CKG_PERIPH_NPU0 (*)
  *         @arg @ref LL_CKG_PERIPH_NPU1 (*)
  *         @arg @ref LL_CKG_PERIPH_AHBS
  *         @arg @ref LL_CKG_PERIPH_AHBIC
  *         @arg @ref LL_CKG_PERIPH_FMC
  *         @arg @ref LL_CKG_PERIPH_XSPI1
  *         @arg @ref LL_CKG_PERIPH_AXISRAM4
  *         @arg @ref LL_CKG_PERIPH_AXISRAM3
  *         @arg @ref LL_CKG_PERIPH_AXISRAM2
  *         @arg @ref LL_CKG_PERIPH_AXISRAM1
  *         @arg @ref LL_CKG_PERIPH_FLASH
  *         @arg @ref LL_CKG_PERIPH_EXTI
  *         @arg @ref LL_CKG_PERIPH_JTAG
  *
  *         (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_CKG_Disable(uint32_t periphs)
{
  __IO uint32_t tmpreg;
  STM32_ATOMIC_SET_BIT_32(RCC->CKGDISR, periphs & LL_CKG_PERIPH_ALL_DIS_MASK);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = STM32_READ_BIT(RCC->CKGDISR, periphs);
  (void)tmpreg;
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

#endif /* STM32H7PXX_LL_BUS_H */
