/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP2xx_HAL_GPIO_EX_H
#define __STM32MP2xx_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @brief GPIO Extended HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */

/** @defgroup GPIOEx_Alternate_function_selection GPIOEx Alternate function selection
  * @{
  */

/*---------------------STM32MP211C/F STM32MP213C/F STM32MP215C/F ------------------*/
#if defined(STM32MP21xxxx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping for TRACED0-15 et TRACECLK  */
#define GPIO_AF0_DBTRGI        ((uint8_t)0x00)  /* DBTRGI Alternate Function mapping                            */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_HDP           ((uint8_t)0x01)  /* HDP Alternate Function mapping                               */
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01)  /* LPTIM1 Alternate Function mapping IN1 IN2 CH1 CH2 ETR        */
#define GPIO_AF1_LPTIM2        ((uint8_t)0x01)  /* LPTIM2 Alternate Function mapping IN1 IN2 CH1 CH2 ETR        */
#define GPIO_AF1_MCO1          ((uint8_t)0x01)  /* MCO1 Alternate Function mapping                              */
#define GPIO_AF1_MCO2          ((uint8_t)0x01)  /* MCO2 Alternate Function mapping                              */
#define GPIO_AF1_RTC           ((uint8_t)0x01)  /* RTC Alternate Function mapping REFIN OUT2                    */
#define GPIO_AF1_SPI4          ((uint8_t)0x01)  /* SPI4 Alternate Function mapping  SCK RDY NSS MISO MOSI       */
#define GPIO_AF1_SPI6          ((uint8_t)0x01)  /* SPI8 Alternate Function mapping  SCK RDY NSS MISO MOSI       */
#define GPIO_AF1_SPI_I2S1      ((uint8_t)0x01)  /* SPI_I2S1 Alternate Function mapping RDY                      */
#define GPIO_AF1_SPI_I2S3      ((uint8_t)0x01)  /* SPI_I2S3 Alternate Function mapping SCK RDY NSS MISO MOSI    */
#define GPIO_AF1_SAI1          ((uint8_t)0x01)  /* SAI1 Alternate Function mapping MCLK_A SCK_A                 */
#define GPIO_AF1_DBTRGO        ((uint8_t)0x01)  /* DBTRGO Alternate Function mapping                            */


/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_HDP           ((uint8_t)0x02)  /* HDP Alternate Function mapping    */
#define GPIO_AF2_I2S           ((uint8_t)0x02)  /* I2S Alternate Function mapping */
#define GPIO_AF2_LPTIM3        ((uint8_t)0x02)  /* LPTIM3 Alternate Function mapping */
#define GPIO_AF2_LPTIM2        ((uint8_t)0x02)  /* LPTIM2 Alternate Function mapping */
#define GPIO_AF2_SPDIFRX       ((uint8_t)0x02)  /* SPDIFRX Alternate Function mapping */
#define GPIO_AF2_SPI_I2S1      ((uint8_t)0x02)  /* SPI_I2S1 Alternate Function mapping   */
#define GPIO_AF2_SPI_I2S2      ((uint8_t)0x02)  /* SPI_I2S2 Alternate Function mapping   */
#define GPIO_AF2_SPI_I2S3      ((uint8_t)0x02)  /* SPI_I2S3 Alternate Function mapping   */
#define GPIO_AF2_SPI5          ((uint8_t)0x02)  /* SPI5 Alternate Function mapping */
#define GPIO_AF2_SPI6          ((uint8_t)0x02)  /* SPI6 Alternate Function mapping */
#define GPIO_AF2_MCO2          ((uint8_t)0x02)  /* MCO2 Alternate Function mapping */
#define GPIO_AF2_AUDIOCLK      ((uint8_t)0x02)  /* AUDIOCLK Alternate Function mapping */


/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_I3C3          ((uint8_t)0x03)  /* I3C3 Alternate Function mapping */
#define GPIO_AF3_LPTIM1        ((uint8_t)0x03)  /* LPTIM1 Alternate Function mapping  */
#define GPIO_AF3_LPTIM2        ((uint8_t)0x03)  /* LPTIM2 Alternate Function mapping  */
#define GPIO_AF3_SAI1          ((uint8_t)0x03)  /* SAI1 Alternate Function mapping */
#define GPIO_AF3_SAI3          ((uint8_t)0x03)  /* SAI3 Alternate Function mapping */
#define GPIO_AF3_SAI4          ((uint8_t)0x03)  /* SAI4 Alternate Function mapping */
#define GPIO_AF3_SPDIFRX       ((uint8_t)0x03)  /* SPDIFRX Alternate Function mapping */
#define GPIO_AF3_SPI_I2S1      ((uint8_t)0x03)  /* SPI_I2S1 Alternate Function mapping   */
#define GPIO_AF3_SPI_I2S3      ((uint8_t)0x03)  /* SPI_I2S3 Alternate Function mapping   */
#define GPIO_AF3_SPI4          ((uint8_t)0x03)  /* SPI4 Alternate Function mapping */
#define GPIO_AF3_SPI6          ((uint8_t)0x03)  /* SPI6 Alternate Function mapping */
#define GPIO_AF3_UART4         ((uint8_t)0x03)  /* UART4 Alternate Function mapping */
#define GPIO_AF3_USART6        ((uint8_t)0x03)  /* UASRT6 Alternate Function mapping */


/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I3C2          ((uint8_t)0x04)  /* I3C2 Alternate Function mapping */
#define GPIO_AF4_MDF1          ((uint8_t)0x04)  /* MDF1 Alternate Function mapping */
#define GPIO_AF4_SAI1          ((uint8_t)0x04)  /* SAI1 Alternate Function mapping */
#define GPIO_AF4_SAI2          ((uint8_t)0x04)  /* SAI2 Alternate Function mapping */
#define GPIO_AF4_SAI3          ((uint8_t)0x04)  /* SAI3 Alternate Function mapping */
#define GPIO_AF4_SAI4          ((uint8_t)0x04)  /* SAI4 Alternate Function mapping */
#define GPIO_AF4_SPDIFRX       ((uint8_t)0x04)  /* SPDIFRX Alternate Function mapping */
#define GPIO_AF4_UART4         ((uint8_t)0x04)  /* UART4 Alternate Function mapping */
#define GPIO_AF4_USART6        ((uint8_t)0x04)  /* UASRT6 Alternate Function mapping */
#define GPIO_AF4_SPI_I2S2      ((uint8_t)0x04)  /* SPI2 Alternate Function mapping */
#define GPIO_AF4_TIM8          ((uint8_t)0x04)  /* TIM8 Alternate Function mapping CH1 CH2 CH3 */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_MDF1          ((uint8_t)0x05)  /* MDF1 Alternate Function mapping */
#define GPIO_AF5_SAI2          ((uint8_t)0x05)  /* SAI2 Alternate Function mapping */
#define GPIO_AF5_SAI4          ((uint8_t)0x05)  /* SAI4 Alternate Function mapping */
#define GPIO_AF5_UART5         ((uint8_t)0x05)  /* UART5 Alternate Function mapping */
#define GPIO_AF5_USART1        ((uint8_t)0x05)  /* USART1 Alternate Function mapping */
#define GPIO_AF5_USART6        ((uint8_t)0x05)  /* USART1 Alternate Function mapping */


/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_TIM17         ((uint8_t)0x06)  /* TIM17 Alternate Function mapping  */
#define GPIO_AF6_UART7         ((uint8_t)0x06)  /* UART7 Alternate Function mapping */
#define GPIO_AF6_USART1        ((uint8_t)0x06)  /* USART1 Alternate Function mapping */
#define GPIO_AF6_USART2        ((uint8_t)0x06)  /* USART2 Alternate Function mapping */
#define GPIO_AF6_USART3        ((uint8_t)0x06)  /* USART3 Alternate Function mapping */
#define GPIO_AF6_USART6        ((uint8_t)0x06)  /* USART6 Alternate Function mapping */
#define GPIO_AF6_I2C1          ((uint8_t)0x06)  /* I2C2 Alternate Function mapping */
#define GPIO_AF6_I2C2          ((uint8_t)0x06)  /* I2C2 Alternate Function mapping */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_FDCAN1        ((uint8_t)0x07)  /* FDCAN1 Alternate Function mapping  */
#define GPIO_AF7_FDCAN2        ((uint8_t)0x07)  /* FDCAN2 Alternate Function mapping  */
#define GPIO_AF7_LPTIM4        ((uint8_t)0x07)  /* LPTIM4 Alternate Function mapping  */
#define GPIO_AF7_LPTIM5        ((uint8_t)0x07)  /* LPTIM5 Alternate Function mapping  */
#define GPIO_AF7_TIM2          ((uint8_t)0x07)  /* TIM2 Alternate Function mapping  */
#define GPIO_AF7_TIM3          ((uint8_t)0x07)  /* TIM3 Alternate Function mapping  */
#define GPIO_AF7_TIM4          ((uint8_t)0x07)  /* TIM4 Alternate Function mapping  */
#define GPIO_AF7_TIM12         ((uint8_t)0x07)  /* TIM12 Alternate Function mapping  */
#define GPIO_AF7_TIM13         ((uint8_t)0x07)  /* TIM13 Alternate Function mapping  */
#define GPIO_AF7_TIM15         ((uint8_t)0x07)  /* TIM15 Alternate Function mapping  */
#define GPIO_AF7_TIM16         ((uint8_t)0x07)  /* TIM16 Alternate Function mapping  */
#define GPIO_AF7_TIM17         ((uint8_t)0x07)  /* TIM17 Alternate Function mapping  */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_ETH1          ((uint8_t)0x08)  /* ETH1 Alternate Function mapping  */
#define GPIO_AF8_I2C1          ((uint8_t)0x08)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF8_I2C2          ((uint8_t)0x08)  /* I2C2 Alternate Function mapping  */
#define GPIO_AF8_I2C3          ((uint8_t)0x08)  /* I2C3 Alternate Function mapping  */
#define GPIO_AF8_I3C1          ((uint8_t)0x08)  /* I3C1 Alternate Function mapping  */
#define GPIO_AF8_TIM1          ((uint8_t)0x08)  /* TIM1 Alternate Function mapping  */
#define GPIO_AF8_TIM2          ((uint8_t)0x08)  /* TIM2 Alternate Function mapping  */
#define GPIO_AF8_TIM3          ((uint8_t)0x08)  /* TIM3 Alternate Function mapping  */
#define GPIO_AF8_TIM5          ((uint8_t)0x08)  /* TIM5 Alternate Function mapping  */
#define GPIO_AF8_TIM8          ((uint8_t)0x08)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF8_TIM10         ((uint8_t)0x08)  /* TIM10 Alternate Function mapping */
#define GPIO_AF8_TIM11         ((uint8_t)0x08)  /* TIM11 Alternate Function mapping */
#define GPIO_AF8_TIM12         ((uint8_t)0x08)  /* TIM12 Alternate Function mapping  */
#define GPIO_AF8_UART7         ((uint8_t)0x08)  /* UART7 Alternate Function mapping  */
#define GPIO_AF8_USART2        ((uint8_t)0x08)  /* USART2 Alternate Function mapping  */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_ETH1          ((uint8_t)0x09)  /* ETH1 Alternate Function mapping   */
#define GPIO_AF9_ETH2          ((uint8_t)0x09)  /* ETH2 Alternate Function mapping   */
#define GPIO_AF9_DCMI          ((uint8_t)0x09)  /* DCMI Alternate Function mapping  */
#define GPIO_AF9_DCMIPP        ((uint8_t)0x09)  /* DCMIPP Alternate Function mapping  */
#define GPIO_AF9_PSSI          ((uint8_t)0x09)  /* PSSI Alternate Function mapping  */
#define GPIO_AF9_I2C1          ((uint8_t)0x09)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF9_I2C2          ((uint8_t)0x09)  /* I2C2 Alternate Function mapping  */
#define GPIO_AF9_I2C3          ((uint8_t)0x09)  /* I2C3 Alternate Function mapping  */
#define GPIO_AF9_SDMMC1        ((uint8_t)0x09)  /* SDMMC1 Alternate Function mapping  */
#define GPIO_AF9_SDMMC2        ((uint8_t)0x09)  /* SDMMC2 Alternate Function mapping  */
#define GPIO_AF9_TIM4          ((uint8_t)0x09)  /* TIM4 Alternate Function mapping   */
#define GPIO_AF9_TIM5          ((uint8_t)0x09)  /* TIM5 Alternate Function mapping   */
#define GPIO_AF9_TIM10         ((uint8_t)0x09)  /* TIM10 Alternate Function mapping   */
#define GPIO_AF9_TIM12         ((uint8_t)0x09)  /* TIM12 Alternate Function mapping   */
#define GPIO_AF9_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping   */
#define GPIO_AF9_USBH          ((uint8_t)0x09)  /* USBH Alternate Function mapping   */


/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_ETH1         ((uint8_t)0x0A)  /* ETH1 Alternate Function mapping */
#define GPIO_AF10_ETH2         ((uint8_t)0x0A)  /* ETH2 Alternate Function mapping */
#define GPIO_AF10_FMC          ((uint8_t)0x0A)  /* FMC Alternate Function mapping */
#define GPIO_AF10_I2C1         ((uint8_t)0x0A)  /* I2C1 Alternate Function mapping */
#define GPIO_AF10_I2C3         ((uint8_t)0x0A)  /* I2C3 Alternate Function mapping */
#define GPIO_AF10_I3C1         ((uint8_t)0x0A)  /* I3C1 Alternate Function mapping */
#define GPIO_AF10_LCD          ((uint8_t)0x0A)  /* LCD Alternate Function mapping    */
#define GPIO_AF10_LPTIM3       ((uint8_t)0x0A)  /* LPTIM3 Alternate Function mapping */
#define GPIO_AF10_LPTIM4       ((uint8_t)0x0A)  /* LPTIM4 Alternate Function mapping */
#define GPIO_AF10_SDMMC1       ((uint8_t)0x0A)  /* SDMMC1 Alternate Function mapping */
#define GPIO_AF10_SDMMC3       ((uint8_t)0x0A)  /* SDMMC3 Alternate Function mapping */
#define GPIO_AF10_TIM14        ((uint8_t)0x0A)  /* TIM14 Alternate Function mapping */
#define GPIO_AF10_OCTOSPI1     ((uint8_t)0x0A)  /* OCTOSPI1 Alternate Function mapping */


/**
  * @brief   AF 11 selection
  */
#define GPIO_AF11_ETH1         ((uint8_t)0x0B)  /* ETH1 Alternate Function mapping */
#define GPIO_AF11_ETH2         ((uint8_t)0x0B)  /* ETH2 Alternate Function mapping */
#define GPIO_AF11_FMC          ((uint8_t)0x0B)  /* FMC Alternate Function mapping */
#define GPIO_AF11_I2C3         ((uint8_t)0x0B)  /* I2C3 Alternate Function mapping */
#define GPIO_AF11_LCD          ((uint8_t)0x0B)  /* LCD Alternate Function mapping */
#define GPIO_AF11_SDMMC1       ((uint8_t)0x0B)  /* SDMMC1 Alternate Function mapping */
#define GPIO_AF11_DCMI         ((uint8_t)0x0B)  /* DCMI Alternate Function mapping */
#define GPIO_AF11_PSSI         ((uint8_t)0x0B)  /* PSSI Alternate Function mapping */
#define GPIO_AF11_DCMIPP       ((uint8_t)0x0B)  /* DCMIPP Alternate Function mapping */
#define GPIO_AF11_I2C2         ((uint8_t)0x0B)  /* I2C2 Alternate Function mapping */
#define GPIO_AF11_I2C3         ((uint8_t)0x0B)  /* I2C3 Alternate Function mapping */
#define GPIO_AF11_OCTOSPI1     ((uint8_t)0x0B)  /* OCTOSPI1 Alternate Function mapping */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_ETH1         ((uint8_t)0x0C)  /* ETH1 Alternate Function mapping */
#define GPIO_AF12_ETH2         ((uint8_t)0x0C)  /* ETH2 Alternate Function mapping */
#define GPIO_AF12_FMC          ((uint8_t)0x0C)  /* FMC Alternate Function mapping */
#define GPIO_AF12_SDMMC1       ((uint8_t)0x0C)  /* SDMMC1 Alternate Function mapping */
#define GPIO_AF12_SDMMC2       ((uint8_t)0x0C)  /* SDMMC2 Alternate Function mapping */
#define GPIO_AF12_SDMMC3       ((uint8_t)0x0C)  /* SDMMC3 Alternate Function mapping */
#define GPIO_AF12_LCD          ((uint8_t)0x0C)  /* LCD Alternate Function mapping */
#define GPIO_AF12_USBH         ((uint8_t)0x0C)  /* USBH Alternate Function mapping */
#define GPIO_AF12_I2C1         ((uint8_t)0x0C)  /* I2C1 Alternate Function mapping */

/**
  * @brief   AF 13 selection
  */
#define GPIO_AF13_DCMI         ((uint8_t)0x0D)   /* DCMI Alternate Function mapping */
#define GPIO_AF13_DCMIPP       ((uint8_t)0x0D)   /* DCMIPP Alternate Function mapping */
#define GPIO_AF13_PSSI         ((uint8_t)0x0D)   /* PSSI Alternate Function mapping */
#define GPIO_AF13_ETH1         ((uint8_t)0x0D)   /* ETH1 Alternate Function mapping */
#define GPIO_AF13_ETH2         ((uint8_t)0x0D)   /* ETH2 Alternate Function mapping */
#define GPIO_AF13_LCD          ((uint8_t)0x0D)   /* LCD Alternate Function mapping */
#define GPIO_AF13_OCTOSPI1     ((uint8_t)0x0D)   /* OCTOSPI1 Alternate Function mapping */
#define GPIO_AF13_SDMMC2       ((uint8_t)0x0D)   /* SDMMC2 Alternate Function mapping */
#define GPIO_AF13_SDMMC3       ((uint8_t)0x0D)   /* SDMMC3 Alternate Function mapping */
#define GPIO_AF13_I3C2         ((uint8_t)0x0D)   /* I3C2 Alternate Function mapping */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_DCMI         ((uint8_t)0x0E)   /* DCMI Alternate Function mapping */
#define GPIO_AF14_DCMIPP       ((uint8_t)0x0E)   /* DCMIPP Alternate Function mapping */
#define GPIO_AF14_PSSI         ((uint8_t)0x0E)   /* PSSI Alternate Function mapping */
#define GPIO_AF14_SDMMC2       ((uint8_t)0x0E)   /* SDMMC2 Alternate Function mapping */
#define GPIO_AF14_SDMMC3       ((uint8_t)0x0E)   /* SDMMC3 Alternate Function mapping */
#define GPIO_AF14_LCD          ((uint8_t)0x0E)   /* LCD Alternate Function mapping */

#endif

/*-------------------- STM32MP235A/C/D/F STM32MP233A/C/D/F STM32MP231A/C/D/F -------------------*/
/*---------------------STM32MP251C/F STM32MP253C/F STM32MP255C/F STM32MP257C/F------------------*/
#if defined(STM32MP23xxxx) || defined(STM32MP25xxxx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping for TRACED0-15 et TRACECLK  */
#define GPIO_AF0_DBTRGI        ((uint8_t)0x00)  /* DBTRGI Alternate Function mapping                            */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_HDP           ((uint8_t)0x01)  /* HDP Alternate Function mapping                               */
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01)  /* LPTIM1 Alternate Function mapping IN1 IN2 CH1 CH2 ETR        */
#define GPIO_AF1_LPTIM2        ((uint8_t)0x01)  /* LPTIM2 Alternate Function mapping IN1 IN2 CH1 CH2 ETR        */
#define GPIO_AF1_MCO1          ((uint8_t)0x01)  /* MCO1 Alternate Function mapping                              */
#define GPIO_AF1_MCO2          ((uint8_t)0x01)  /* MCO2 Alternate Function mapping                              */
#define GPIO_AF1_RTC           ((uint8_t)0x01)  /* RTC Alternate Function mapping REFIN OUT2                    */
#define GPIO_AF1_SPI4          ((uint8_t)0x01)  /* SPI4 Alternate Function mapping  SCK RDY NSS MISO MOSI       */
#define GPIO_AF1_SPI7          ((uint8_t)0x01)  /* SPI7 Alternate Function mapping  SCK RDY NSS MISO MOSI       */
#define GPIO_AF1_SPI8          ((uint8_t)0x01)  /* SPI8 Alternate Function mapping  SCK RDY NSS MISO MOSI       */
#define GPIO_AF1_SPI_I2S1      ((uint8_t)0x01)  /* SPI_I2S1 Alternate Function mapping RDY                      */
#define GPIO_AF1_SPI_I2S3      ((uint8_t)0x01)  /* SPI_I2S3 Alternate Function mapping SCK RDY NSS MISO MOSI    */
#define GPIO_AF1_SAI1          ((uint8_t)0x01)  /* SAI1 Alternate Function mapping MCLK_A SCK_A                 */
#define GPIO_AF1_DBTRGO        ((uint8_t)0x01)  /* DBTRGO Alternate Function mapping                            */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_HDP           ((uint8_t)0x02)  /* HDP Alternate Function mapping    */
#define GPIO_AF2_I2S           ((uint8_t)0x02)  /* I2S Alternate Function mapping */
#define GPIO_AF2_LPTIM3        ((uint8_t)0x02)  /* LPTIM3 Alternate Function mapping */
#define GPIO_AF2_LPTIM2        ((uint8_t)0x02)  /* LPTIM2 Alternate Function mapping */
#define GPIO_AF2_SPDIFRX       ((uint8_t)0x02)  /* SPDIFRX Alternate Function mapping */
#define GPIO_AF2_SPI_I2S1      ((uint8_t)0x02)  /* SPI_I2S1 Alternate Function mapping   */
#define GPIO_AF2_SPI_I2S2      ((uint8_t)0x02)  /* SPI_I2S2 Alternate Function mapping   */
#define GPIO_AF2_SPI_I2S3      ((uint8_t)0x02)  /* SPI_I2S3 Alternate Function mapping   */
#define GPIO_AF2_SPI4          ((uint8_t)0x02)  /* SPI4 Alternate Function mapping */
#define GPIO_AF2_SPI5          ((uint8_t)0x02)  /* SPI5 Alternate Function mapping */
#define GPIO_AF2_SPI6          ((uint8_t)0x02)  /* SPI6 Alternate Function mapping */
#define GPIO_AF2_SPI7          ((uint8_t)0x02)  /* SPI7 Alternate Function mapping */
#define GPIO_AF2_MCO2          ((uint8_t)0x02)  /* MCO2 Alternate Function mapping */
#define GPIO_AF2_AUDIOCLK      ((uint8_t)0x02)  /* AUDIOCLK Alternate Function mapping */


/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_I3C3          ((uint8_t)0x03)  /* I3C3 Alternate Function mapping */
#define GPIO_AF3_LPTIM1        ((uint8_t)0x03)  /* LPTIM1 Alternate Function mapping  */
#define GPIO_AF3_LPTIM2        ((uint8_t)0x03)  /* LPTIM2 Alternate Function mapping  */
#define GPIO_AF3_SAI1          ((uint8_t)0x03)  /* SAI1 Alternate Function mapping */
#define GPIO_AF3_SAI2          ((uint8_t)0x03)  /* SAI2 Alternate Function mapping */
#define GPIO_AF3_SAI3          ((uint8_t)0x03)  /* SAI3 Alternate Function mapping */
#define GPIO_AF3_SAI4          ((uint8_t)0x03)  /* SAI4 Alternate Function mapping */
#define GPIO_AF3_SPDIFRX       ((uint8_t)0x03)  /* SPDIFRX Alternate Function mapping */
#define GPIO_AF3_SPI_I2S1      ((uint8_t)0x03)  /* SPI_I2S1 Alternate Function mapping   */
#define GPIO_AF3_SPI_I2S3      ((uint8_t)0x03)  /* SPI_I2S3 Alternate Function mapping   */
#define GPIO_AF3_SPI4          ((uint8_t)0x03)  /* SPI4 Alternate Function mapping */
#define GPIO_AF3_SPI6          ((uint8_t)0x03)  /* SPI6 Alternate Function mapping */
#define GPIO_AF3_SPI8          ((uint8_t)0x03)  /* SPI8 Alternate Function mapping */
#define GPIO_AF3_UART4         ((uint8_t)0x03)  /* UART4 Alternate Function mapping */
#define GPIO_AF3_UART8         ((uint8_t)0x03)  /* UART8 Alternate Function mapping */
#define GPIO_AF3_USART6        ((uint8_t)0x03)  /* UASRT6 Alternate Function mapping */


/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_MDF1          ((uint8_t)0x04)  /* MDF1 Alternate Function mapping */
#define GPIO_AF4_SAI1          ((uint8_t)0x04)  /* SAI1 Alternate Function mapping */
#define GPIO_AF4_SAI2          ((uint8_t)0x04)  /* SAI2 Alternate Function mapping */
#define GPIO_AF4_SAI3          ((uint8_t)0x04)  /* SAI3 Alternate Function mapping */
#define GPIO_AF4_SAI4          ((uint8_t)0x04)  /* SAI4 Alternate Function mapping */
#define GPIO_AF4_SPDIFRX       ((uint8_t)0x04)  /* SPDIFRX Alternate Function mapping */
#define GPIO_AF4_UART4         ((uint8_t)0x04)  /* UART4 Alternate Function mapping */
#define GPIO_AF4_PCIE          ((uint8_t)0x04)  /* PCIE Alternate Function mapping */
#define GPIO_AF4_FDCAN2        ((uint8_t)0x04)  /* FDCAN2    Alternate Function mapping */
#define GPIO_AF4_USART6        ((uint8_t)0x04)  /* UASRT6 Alternate Function mapping */
#define GPIO_AF4_SPI_I2S2      ((uint8_t)0x04)  /* SPI2 Alternate Function mapping */
#define GPIO_AF4_TIM8          ((uint8_t)0x04)  /* TIM8 Alternate Function mapping CH1 CH2 CH3 */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_I3C3          ((uint8_t)0x05)  /* I3C3 Alternate Function mapping */
#define GPIO_AF5_MDF1          ((uint8_t)0x05)  /* MDF1 Alternate Function mapping */
#define GPIO_AF5_ADF1          ((uint8_t)0x05)  /* ADF1 Alternate Function mapping */
#define GPIO_AF5_SAI2          ((uint8_t)0x05)  /* SAI2 Alternate Function mapping */
#define GPIO_AF5_SAI4          ((uint8_t)0x05)  /* SAI4 Alternate Function mapping */
#define GPIO_AF5_UART5         ((uint8_t)0x05)  /* UART5 Alternate Function mapping */
#define GPIO_AF5_UART8         ((uint8_t)0x05)  /* UART8 Alternate Function mapping */
#define GPIO_AF5_USART1        ((uint8_t)0x05)  /* USART1 Alternate Function mapping */
#define GPIO_AF5_USART6        ((uint8_t)0x05)  /* USART1 Alternate Function mapping */
#define GPIO_AF5_DSI           ((uint8_t)0x05)  /* DSI Alternate Function mapping TE */


/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_FDCAN3        ((uint8_t)0x06)  /* FDCAN3 Alternate Function mapping  */
#define GPIO_AF6_I2C4          ((uint8_t)0x06)  /* I2C4 Alternate Function mapping  */
#define GPIO_AF6_I2C5          ((uint8_t)0x06)  /* I2C5 Alternate Function mapping  */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_TIM14         ((uint8_t)0x06)  /* TIM14 Alternate Function mapping  */
#define GPIO_AF6_TIM17         ((uint8_t)0x06)  /* TIM17 Alternate Function mapping  */
#define GPIO_AF6_UART7         ((uint8_t)0x06)  /* UART7 Alternate Function mapping */
#define GPIO_AF6_UART8         ((uint8_t)0x06)  /* UART8 Alternate Function mapping */
#define GPIO_AF6_UART9         ((uint8_t)0x06)  /* UART9 Alternate Function mapping */
#define GPIO_AF6_USART1        ((uint8_t)0x06)  /* USART1 Alternate Function mapping */
#define GPIO_AF6_USART2        ((uint8_t)0x06)  /* USART2 Alternate Function mapping */
#define GPIO_AF6_USART3        ((uint8_t)0x06)  /* USART3 Alternate Function mapping */
#define GPIO_AF6_USART6        ((uint8_t)0x06)  /* USART6 Alternate Function mapping */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_FDCAN1        ((uint8_t)0x07)  /* FDCAN1 Alternate Function mapping  */
#define GPIO_AF7_FDCAN2        ((uint8_t)0x07)  /* FDCAN2 Alternate Function mapping  */
#define GPIO_AF7_FDCAN3        ((uint8_t)0x07)  /* FDCAN3 Alternate Function mapping  */
#define GPIO_AF7_LPTIM4        ((uint8_t)0x07)  /* LPTIM4 Alternate Function mapping  */
#define GPIO_AF7_LPTIM5        ((uint8_t)0x07)  /* LPTIM5 Alternate Function mapping  */
#define GPIO_AF7_TIM2          ((uint8_t)0x07)  /* TIM2 Alternate Function mapping  */
#define GPIO_AF7_TIM3          ((uint8_t)0x07)  /* TIM3 Alternate Function mapping  */
#define GPIO_AF7_TIM4          ((uint8_t)0x07)  /* TIM4 Alternate Function mapping  */
#define GPIO_AF7_TIM12         ((uint8_t)0x07)  /* TIM12 Alternate Function mapping  */
#define GPIO_AF7_TIM13         ((uint8_t)0x07)  /* TIM13 Alternate Function mapping  */
#define GPIO_AF7_TIM15         ((uint8_t)0x07)  /* TIM15 Alternate Function mapping  */
#define GPIO_AF7_TIM16         ((uint8_t)0x07)  /* TIM16 Alternate Function mapping  */
#define GPIO_AF7_TIM17         ((uint8_t)0x07)  /* TIM17 Alternate Function mapping  */
#define GPIO_AF7_TIM20         ((uint8_t)0x07)  /* TIM20 Alternate Function mapping  */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_ETH1          ((uint8_t)0x08)  /* ETH1 Alternate Function mapping  */
#define GPIO_AF8_I2C2          ((uint8_t)0x08)  /* I2C2 Alternate Function mapping  */
#define GPIO_AF8_I2C4          ((uint8_t)0x08)  /* I2C4 Alternate Function mapping  */
#define GPIO_AF8_I2C5          ((uint8_t)0x08)  /* I2C5 Alternate Function mapping  */
#define GPIO_AF8_I2C8          ((uint8_t)0x08)  /* I2C8 Alternate Function mapping  */
#define GPIO_AF8_I3C1          ((uint8_t)0x08)  /* I3C1 Alternate Function mapping  */
#define GPIO_AF8_TIM1          ((uint8_t)0x08)  /* TIM1 Alternate Function mapping  */
#define GPIO_AF8_TIM2          ((uint8_t)0x08)  /* TIM2 Alternate Function mapping  */
#define GPIO_AF8_TIM3          ((uint8_t)0x08)  /* TIM3 Alternate Function mapping  */
#define GPIO_AF8_TIM4          ((uint8_t)0x08)  /* TIM4 Alternate Function mapping  */
#define GPIO_AF8_TIM5          ((uint8_t)0x08)  /* TIM5 Alternate Function mapping  */
#define GPIO_AF8_TIM8          ((uint8_t)0x08)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF8_TIM10         ((uint8_t)0x08)  /* TIM10 Alternate Function mapping */
#define GPIO_AF8_TIM11         ((uint8_t)0x08)  /* TIM11 Alternate Function mapping */
#define GPIO_AF8_TIM12         ((uint8_t)0x08)  /* TIM12 Alternate Function mapping  */
#define GPIO_AF8_TIM16         ((uint8_t)0x08)  /* TIM16 Alternate Function mapping  */
#define GPIO_AF8_TIM20         ((uint8_t)0x08)  /* TIM20 Alternate Function mapping  */
#define GPIO_AF8_UART7         ((uint8_t)0x08)  /* UART7 Alternate Function mapping  */
#define GPIO_AF8_USART2        ((uint8_t)0x08)  /* USART2 Alternate Function mapping  */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_FDCAN3        ((uint8_t)0x09)  /* FDCAN3 Alternate Function mapping   */
#define GPIO_AF9_ETH1          ((uint8_t)0x09)  /* ETH1 Alternate Function mapping   */
#define GPIO_AF9_ETH2          ((uint8_t)0x09)  /* ETH2 Alternate Function mapping   */
#define GPIO_AF9_DCMI          ((uint8_t)0x09)  /* DCMI Alternate Function mapping  */
#define GPIO_AF9_DCMIPP        ((uint8_t)0x09)  /* DCMIPP Alternate Function mapping  */
#define GPIO_AF9_PSSI          ((uint8_t)0x09)  /* PSSI Alternate Function mapping  */
#define GPIO_AF9_I2C1          ((uint8_t)0x09)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF9_I2C2          ((uint8_t)0x09)  /* I2C2 Alternate Function mapping  */
#define GPIO_AF9_I2C3          ((uint8_t)0x09)  /* I2C3 Alternate Function mapping  */
#define GPIO_AF9_I2C4          ((uint8_t)0x09)  /* I2C4 Alternate Function mapping  */
#define GPIO_AF9_I2C5          ((uint8_t)0x09)  /* I2C5 Alternate Function mapping  */
#define GPIO_AF9_I2C6          ((uint8_t)0x09)  /* I2C6 Alternate Function mapping  */
#define GPIO_AF9_I2C7          ((uint8_t)0x09)  /* I2C7 Alternate Function mapping  */
#define GPIO_AF9_I2C8          ((uint8_t)0x09)  /* I2C8 Alternate Function mapping  */
#define GPIO_AF9_LPTIM5        ((uint8_t)0x09)  /* LPTIM5 Alternate Function mapping  */
#define GPIO_AF9_SDMMC1        ((uint8_t)0x09)  /* SDMMC1 Alternate Function mapping  */
#define GPIO_AF9_SDMMC2        ((uint8_t)0x09)  /* SDMMC2 Alternate Function mapping  */
#define GPIO_AF9_TIM4          ((uint8_t)0x09)  /* TIM4 Alternate Function mapping   */
#define GPIO_AF9_TIM5          ((uint8_t)0x09)  /* TIM5 Alternate Function mapping   */
#define GPIO_AF9_TIM10         ((uint8_t)0x09)  /* TIM10 Alternate Function mapping   */
#define GPIO_AF9_TIM12         ((uint8_t)0x09)  /* TIM12 Alternate Function mapping   */
#define GPIO_AF9_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping   */
#define GPIO_AF9_DSI           ((uint8_t)0x09)  /* DSI Alternate Function mapping   */
#define GPIO_AF9_USBH          ((uint8_t)0x09)  /* USBH Alternate Function mapping   */


/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_ETH1         ((uint8_t)0x0A)  /* ETH1 Alternate Function mapping */
#define GPIO_AF10_ETH2         ((uint8_t)0x0A)  /* ETH2 Alternate Function mapping */
#define GPIO_AF10_FMC          ((uint8_t)0x0A)  /* FMC Alternate Function mapping */
#define GPIO_AF10_I2C1         ((uint8_t)0x0A)  /* I2C1 Alternate Function mapping */
#define GPIO_AF10_I2C3         ((uint8_t)0x0A)  /* I2C3 Alternate Function mapping */
#define GPIO_AF10_I2C5         ((uint8_t)0x0A)  /* I2C5 Alternate Function mapping */
#define GPIO_AF10_I2C7         ((uint8_t)0x0A)  /* I2C7 Alternate Function mapping */
#define GPIO_AF10_I3C1         ((uint8_t)0x0A)  /* I3C1 Alternate Function mapping */
#define GPIO_AF10_I3C2         ((uint8_t)0x0A)  /* I3C2 Alternate Function mapping */
#define GPIO_AF10_OCTOSPIM_P1  ((uint8_t)0x0A)  /* OCTOSPIM_P1 Alternate Function mapping */
#define GPIO_AF10_OCTOSPIM_P2  ((uint8_t)0x0A)  /* OCTOSPIM_P2 Alternate Function mapping */
#define GPIO_AF10_SDMMC1       ((uint8_t)0x0A)  /* SDMMC1 Alternate Function mapping */
#define GPIO_AF10_SDMMC3       ((uint8_t)0x0A)  /* SDMMC3 Alternate Function mapping */
#define GPIO_AF10_TIM14        ((uint8_t)0x0A)  /* TIM14 Alternate Function mapping */
#define GPIO_AF10_LPTIM3       ((uint8_t)0x0A)  /* LPTIM3 Alternate Function mapping */
#define GPIO_AF10_LPTIM4       ((uint8_t)0x0A)  /* LPTIM4 Alternate Function mapping */
#define GPIO_AF10_LCD          ((uint8_t)0x0A)  /* LCD Alternate Function mapping    */


/**
  * @brief   AF 11 selection
  */
#define GPIO_AF11_ETH1         ((uint8_t)0x0B)  /* ETH1 Alternate Function mapping */
#define GPIO_AF11_ETH2         ((uint8_t)0x0B)  /* ETH2 Alternate Function mapping */
#define GPIO_AF11_FMC          ((uint8_t)0x0B)  /* FMC Alternate Function mapping */
#define GPIO_AF11_I2C3         ((uint8_t)0x0B)  /* I2C3 Alternate Function mapping */
#define GPIO_AF11_I2C5         ((uint8_t)0x0B)  /* I2C5 Alternate Function mapping */
#define GPIO_AF11_I3C4         ((uint8_t)0x0B)  /* I3C4 Alternate Function mapping */
#define GPIO_AF11_OCTOSPIM_P1  ((uint8_t)0x0B)  /* OCTOSPIM_P1 Alternate Function mapping */
#define GPIO_AF11_OCTOSPIM_P2  ((uint8_t)0x0B)  /* OCTOSPIM_P2 Alternate Function mapping */
#define GPIO_AF11_SDMMC1       ((uint8_t)0x0B)  /* SDMMC1 Alternate Function mapping */
#define GPIO_AF11_LCD          ((uint8_t)0x0B)  /* LCD Alternate Function mapping */
#define GPIO_AF11_USB3DR       ((uint8_t)0x0B)  /* USB3DR Alternate Function mapping */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_ETH1         ((uint8_t)0x0C)  /* ETH1 Alternate Function mapping */
#define GPIO_AF12_ETH2         ((uint8_t)0x0C)  /* ETH2 Alternate Function mapping */
#define GPIO_AF12_FMC          ((uint8_t)0x0C)  /* FMC Alternate Function mapping */
#define GPIO_AF12_I2C4         ((uint8_t)0x0C)  /* I2C4 Alternate Function mapping */
#define GPIO_AF12_OCTOSPIM_P2  ((uint8_t)0x0C)  /* OCTOSPIM_P2 Alternate Function mapping */
#define GPIO_AF12_SDMMC1       ((uint8_t)0x0C)  /* SDMMC1 Alternate Function mapping */
#define GPIO_AF12_SDMMC2       ((uint8_t)0x0C)  /* SDMMC2 Alternate Function mapping */
#define GPIO_AF12_SDMMC3       ((uint8_t)0x0C)  /* SDMMC3 Alternate Function mapping */
#define GPIO_AF12_LCD          ((uint8_t)0x0C)  /* LCD Alternate Function mapping */
#define GPIO_AF12_USBH         ((uint8_t)0x0C)  /* USBH Alternate Function mapping */
#define GPIO_AF12_DSI          ((uint8_t)0x0C)  /* DSI Alternate Function mapping */


/**
  * @brief   AF 13 selection
  */
#define GPIO_AF13_DCMI         ((uint8_t)0x0D)   /* DCMI Alternate Function mapping */
#define GPIO_AF13_DCMIPP       ((uint8_t)0x0D)   /* DCMIPP Alternate Function mapping */
#define GPIO_AF13_PSSI         ((uint8_t)0x0D)   /* PSSI Alternate Function mapping */
#define GPIO_AF13_DSI          ((uint8_t)0x0D)   /* DSI Alternate Function mapping */
#define GPIO_AF13_ETH1         ((uint8_t)0x0D)   /* ETH1 Alternate Function mapping */
#define GPIO_AF13_ETH2         ((uint8_t)0x0D)   /* ETH2 Alternate Function mapping */
#define GPIO_AF13_ETH3         ((uint8_t)0x0D)   /* ETH3 Alternate Function mapping */
#define GPIO_AF13_I3C2         ((uint8_t)0x0D)   /* I3C2 Alternate Function mapping */
#define GPIO_AF13_LCD          ((uint8_t)0x0D)   /* LCD Alternate Function mapping */
#define GPIO_AF13_OCTOSPIM_P1  ((uint8_t)0x0D)   /* OCTOSPIM_P1 Alternate Function mapping */
#define GPIO_AF13_SDMMC2       ((uint8_t)0x0D)   /* SDMMC2 Alternate Function mapping */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_DCMI         ((uint8_t)0x0E)   /* DCMI Alternate Function mapping */
#define GPIO_AF14_DCMIPP       ((uint8_t)0x0E)   /* DCMIPP Alternate Function mapping */
#define GPIO_AF14_PSSI         ((uint8_t)0x0E)   /* PSSI Alternate Function mapping */
#define GPIO_AF14_FMC          ((uint8_t)0x0E)   /* FMC Alternate Function mapping */
#define GPIO_AF14_SDMMC3       ((uint8_t)0x0E)   /* SDMMC3 Alternate Function mapping */
#define GPIO_AF14_ETH3         ((uint8_t)0x0E)   /* ETH3 Alternate Function mapping */
#define GPIO_AF14_LCD          ((uint8_t)0x0E)   /* LCD Alternate Function mapping */

#endif

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT     ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

/**
   * @brief   check if AF is valid
   */
#define IS_GPIO_AF(AF)   ((AF) <= (uint8_t)0x0F)


/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup GPIOEx_Private_Macros GPIO Private Macros
  * @{
  */
/** @defgroup GPIOEx_Get_Port_Index GPIO Get Port Index
  * @{
  */
#if defined(CORE_CM0PLUS)
#define GPIO_GET_INDEX(__GPIOx__)   (uint8_t)(((__GPIOx__) == (GPIOZ))? 11U :25U)
#else /* CORE_CM0PLUS */
#if defined(GPIOJ) && defined(GPIOK)
#define GPIO_GET_INDEX(__GPIOx__)   (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                              ((__GPIOx__) == (GPIOB))? 1U :\
                                              ((__GPIOx__) == (GPIOC))? 2U :\
                                              ((__GPIOx__) == (GPIOD))? 3U :\
                                              ((__GPIOx__) == (GPIOE))? 4U :\
                                              ((__GPIOx__) == (GPIOF))? 5U :\
                                              ((__GPIOx__) == (GPIOG))? 6U :\
                                              ((__GPIOx__) == (GPIOH))? 7U :\
                                              ((__GPIOx__) == (GPIOI))? 8U :\
                                              ((__GPIOx__) == (GPIOJ))? 9U :\
                                              ((__GPIOx__) == (GPIOK))? 10U :\
                                              ((__GPIOx__) == (GPIOZ))? 11U : 25U)
#else /* GPIOJ && GPIOK */
#define GPIO_GET_INDEX(__GPIOx__)   (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                              ((__GPIOx__) == (GPIOB))? 1U :\
                                              ((__GPIOx__) == (GPIOC))? 2U :\
                                              ((__GPIOx__) == (GPIOD))? 3U :\
                                              ((__GPIOx__) == (GPIOE))? 4U :\
                                              ((__GPIOx__) == (GPIOF))? 5U :\
                                              ((__GPIOx__) == (GPIOG))? 6U :\
                                              ((__GPIOx__) == (GPIOH))? 7U :\
                                              ((__GPIOx__) == (GPIOI))? 8U :\
                                              ((__GPIOx__) == (GPIOZ))? 9U : 25U)
#endif /* GPIOJ && GPIOK */
#endif  /* CORE_CM0PLUS */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Macros GPIOEx Exported Macros
  * @{
  */

/** @addtogroup GPIOEx_Exported_Functions_Group1 Extended Peripheral Control functions
  * @{
  */


/**
  * @}
 */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP2xx_HAL_GPIO_EX_H */
