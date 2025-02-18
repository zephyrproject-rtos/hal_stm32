/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL Extension module.
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
#ifndef __STM32MP13xx_HAL_GPIO_EX_H
#define __STM32MP13xx_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal_def.h"

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @addtogroup GPIOEx GPIOEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Constants GPIO Exported Constants
  * @{
  */

/** @defgroup GPIO_Alternate_function_selection GPIO Alternate Function Selection
  * @{
  */
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO1          ((uint8_t)0x00)  /* MCO1 Alternate Function mapping                           */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_LCDBIAS       ((uint8_t)0x00)  /* LCDBIAS Alternate Function mapping                        */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */
#define GPIO_AF0_HDP           ((uint8_t)0x00)  /* HDP Alternate Function mapping                            */
#define GPIO_AF0_MCO2          ((uint8_t)0x00)  /* MCO2 Alternate Function mapping                           */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM1          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM2          ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#define GPIO_AF1_TIM16         ((uint8_t)0x01)  /* TIM16 Alternate Function mapping */
#define GPIO_AF1_TIM17         ((uint8_t)0x01)  /* TIM17 Alternate Function mapping */
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01)  /* LPTIM1 Alternate Function mapping */
#define GPIO_AF1_MCO2          ((uint8_t)0x01)  /* MCO2 Alternate Function mapping */
#define GPIO_AF1_RTC           ((uint8_t)0x01)  /* RTC Alternate Function mapping */
#define GPIO_AF1_LPTIM2        ((uint8_t)0x01)  /* LPTIM2 Alternate Function mapping */
#define GPIO_AF1_SPI5          ((uint8_t)0x01)  /* SPI5 Alternate Function mapping */
#define GPIO_AF1_USART2        ((uint8_t)0x01)  /* USART2 Alternate Function mapping */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4          ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM5          ((uint8_t)0x02)  /* TIM5 Alternate Function mapping */
#define GPIO_AF2_TIM12         ((uint8_t)0x02)  /* TIM12 Alternate Function mapping */
#define GPIO_AF2_SAI1          ((uint8_t)0x02)  /* SAI1 Alternate Function mapping */
#define GPIO_AF2_MCO1          ((uint8_t)0x02)  /* MCO1 Alternate Function mapping */
#define GPIO_AF2_MCO2          ((uint8_t)0x02)  /* MCO2 Alternate Function mapping */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping */
#define GPIO_AF2_SAI2          ((uint8_t)0x02)  /* SAI2 Alternate Function mapping */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_USART2        ((uint8_t)0x02)  /* USART2 Alternate Function mapping */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF3_LPTIM2        ((uint8_t)0x03)  /* LPTIM2 Alternate Function mapping  */
#define GPIO_AF3_DFSDM1        ((uint8_t)0x03)  /* DFSDM1 Alternate Function mapping  */
#define GPIO_AF3_LPTIM3        ((uint8_t)0x03)  /* LPTIM3 Alternate Function mapping  */
#define GPIO_AF3_LPTIM4        ((uint8_t)0x03)  /* LPTIM4 Alternate Function mapping  */
#define GPIO_AF3_LPTIM5        ((uint8_t)0x03)  /* LPTIM5 Alternate Function mapping  */
#define GPIO_AF3_SAI2          ((uint8_t)0x03)  /* SAI2 Alternate Function mapping */
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC Alternate Function mapping */
#define GPIO_AF3_USART2        ((uint8_t)0x03)  /* USART2 Alternate Function mapping */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */
#define GPIO_AF4_I2C3          ((uint8_t)0x04)  /* I2C3 Alternate Function mapping */
#define GPIO_AF4_I2C4          ((uint8_t)0x04)  /* I2C4 Alternate Function mapping */
#define GPIO_AF4_I2C5          ((uint8_t)0x04)  /* I2C5 Alternate Function mapping */
#define GPIO_AF4_TIM15         ((uint8_t)0x04)  /* TIM15 Alternate Function mapping */
#define GPIO_AF4_DFSDM1        ((uint8_t)0x04)  /* DFSDM1  Alternate Function mapping   */
#define GPIO_AF4_LPTIM2        ((uint8_t)0x04)  /* LPTIM2 Alternate Function mapping  */
#define GPIO_AF4_USART1        ((uint8_t)0x04)  /* USART1 Alternate Function mapping */
#define GPIO_AF4_SAI1          ((uint8_t)0x04)  /* SAI1 Alternate Function mapping */
#define GPIO_AF4_SAI2          ((uint8_t)0x04)  /* SAI2 Alternate Function mapping */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping   */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2 Alternate Function mapping   */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /* SPI3 Alternate Function mapping   */
#define GPIO_AF5_SPI4          ((uint8_t)0x05)  /* SPI4 Alternate Function mapping   */
#define GPIO_AF5_SPI5          ((uint8_t)0x05)  /* SPI5 Alternate Function mapping   */
#define GPIO_AF5_I2C1          ((uint8_t)0x05)  /* I2C1 Alternate Function mapping */
#define GPIO_AF5_I2C3          ((uint8_t)0x05)  /* I2C1 Alternate Function mapping */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3 Alternate Function mapping  */
#define GPIO_AF6_SAI1          ((uint8_t)0x06)  /* SAI1 Alternate Function mapping  */
#define GPIO_AF6_I2C4          ((uint8_t)0x06)  /* I2C4 Alternate Function mapping  */
#define GPIO_AF6_DFSDM1        ((uint8_t)0x06)  /* DFSDM1 Alternate Function mapping */
#define GPIO_AF6_DCMIPP        ((uint8_t)0x06)  /* DCMIPP Alternate Function mapping  */
#define GPIO_AF6_SAI2          ((uint8_t)0x06)  /* SAI2 Alternate Function mapping  */
#define GPIO_AF6_SPI1          ((uint8_t)0x06)  /* SPI1 Alternate Function mapping  */
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF6_SPI5          ((uint8_t)0x06)  /* SPI5 Alternate Function mapping  */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping     */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping     */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping     */
#define GPIO_AF7_USART6        ((uint8_t)0x07)  /* USART6 Alternate Function mapping     */
#define GPIO_AF7_UART7         ((uint8_t)0x07)  /* UART7 Alternate Function mapping     */
#define GPIO_AF7_UART4         ((uint8_t)0x07)  /* UART4 Alternate Function mapping     */
#define GPIO_AF7_LCD           ((uint8_t)0x07)  /* LCD Alternate Function mapping      */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_USART3       ((uint8_t)0x08)  /* USART3 Alternate Function mapping */
#define GPIO_AF8_UART4        ((uint8_t)0x08)  /* UART4 Alternate Function mapping */
#define GPIO_AF8_UART5        ((uint8_t)0x08)  /* UART5 Alternate Function mapping */
#define GPIO_AF8_UART8        ((uint8_t)0x08)  /* UART8 Alternate Function mapping */
#define GPIO_AF8_SPDIF        ((uint8_t)0x08)  /* SPDIF Alternate Function mapping */
#define GPIO_AF8_SDIO1        ((uint8_t)0x08)  /* SDIO1 Alternate Function mapping */
#define GPIO_AF8_SPI2         ((uint8_t)0x08)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF8_UART7        ((uint8_t)0x08)  /* UART7 Alternate Function mapping */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_QUADSPI       ((uint8_t)0x09)  /* QUADSPI Alternate Function mapping */
#if defined (FDCAN1)
#define GPIO_AF9_FDCAN1        ((uint8_t)0x09)  /* FDCAN1 Alternate Function mapping    */
#endif /* FDCAN1 */
#if defined (FDCAN2)
#define GPIO_AF9_FDCAN2        ((uint8_t)0x09)  /* FDCAN2 Alternate Function mapping    */
#endif /* FDCAN2 */
#define GPIO_AF9_TIM13         ((uint8_t)0x09)  /* TIM13 Alternate Function mapping   */
#define GPIO_AF9_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping   */
#define GPIO_AF9_LCD           ((uint8_t)0x09)  /* LCD Alternate Function mapping   */
#define GPIO_AF9_SPDIF         ((uint8_t)0x09)  /* SPDIF Alternate Function mapping   */
#if defined (SDMMC2)
#define GPIO_AF9_SDIO2         ((uint8_t)0x09)  /* SDIO2 Alternate Function mapping   */
#endif /* SDMMC2 */
#if defined (SDMMC3)
#define GPIO_AF9_SDIO3         ((uint8_t)0x09)  /* SDIO3 Alternate Function mapping   */
#endif /* SDMMC3 */

/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_QUADSPI       ((uint8_t)0xA)  /* QUADSPI Alternate Function mapping */
#define GPIO_AF10_SAI2          ((uint8_t)0xA)  /* SAI2 Alternate Function mapping */
#if defined (SDMMC2)
#define GPIO_AF10_SDIO2         ((uint8_t)0xA)  /* SDIO2 Alternate Function mapping */
#endif /* SDMMC2 */
#define GPIO_AF10_OTG2_HS       ((uint8_t)0xA)  /* OTG2_HS Alternate Function mapping */
#define GPIO_AF10_SDIO1         ((uint8_t)0xA)  /* SDIO1 Alternate Function mapping */
#define GPIO_AF10_SAI1          ((uint8_t)0xA)  /* SAI1 Alternate Function mapping */
#if defined (ETH)
#define GPIO_AF10_ETH           ((uint8_t)0xA)  /* ETH Alternate Function mapping */
#endif /* ETH */
#if defined (ETH2)
#define GPIO_AF10_ETH2          ((uint8_t)0xA)  /* ETH2 Alternate Function mapping */
#endif /* ETH2 */
#if defined (TSC)
#define GPIO_AF10_TSC           ((uint8_t)0xA)  /* TSC Alternate Function mapping  */
#endif /* TSC */
#define GPIO_AF10_FMC           ((uint8_t)0xA)  /* FMC Alternate Function mapping */

/**
  * @brief   AF 11 selection
  */
#define GPIO_AF11_QUADSPI       ((uint8_t)0x0B)  /* QUADSPI Alternate Function mapping */
#if defined (ETH)
#define GPIO_AF11_ETH           ((uint8_t)0x0B)  /* ETH Alternate Function mapping */
#endif /* ETH */
#define GPIO_AF11_SDIO1         ((uint8_t)0x0B)  /* SDIO1 Alternate Function mapping */
#if defined (ETH2)
#define GPIO_AF11_ETH2          ((uint8_t)0x0B)  /* ETH2 Alternate Function mapping */
#endif /* ETH2 */
#if defined (TSC)
#define GPIO_AF11_TSC           ((uint8_t)0x0B)  /* TSC Alternate Function mapping  */
#endif /* TSC */
#if defined (LCD)
#define GPIO_AF11_LCD           ((uint8_t)0x0B)  /* LCD Alternate Function mapping */
#endif /* LCD */
#define GPIO_AF11_UART5         ((uint8_t)0x0B)  /* UART5 Alternate Function mapping */


/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_FMC           ((uint8_t)0xC)  /* FMC Alternate Function mapping     */
#define GPIO_AF12_SDIO1         ((uint8_t)0xC)  /* SDIO1 Alternate Function mapping  */
#if defined (ETH2)
#define GPIO_AF12_ETH2          ((uint8_t)0xC)  /* ETH2 Alternate Function mapping */
#endif /*ETH2*/
#define GPIO_AF12_SAI2          ((uint8_t)0xC)  /* SAI2 Alternate Function mapping */

/**
  * @brief   AF 13 selection
  */
#define GPIO_AF13_UART7         ((uint8_t)0x0D)   /* UART7 Alternate Function mapping */
#define GPIO_AF13_LCD           ((uint8_t)0x0D)   /* LCD Alternate Function mapping */
#define GPIO_AF13_DCMIPP        ((uint8_t)0x0D)   /* DCMI Alternate Function mapping */
#if defined (ETH2)
#define GPIO_AF13_ETH2          ((uint8_t)0x0D)   /* ETH2 Alternate Function mapping */
#endif /*ETH2*/
#define GPIO_AF13_QUADSPI       ((uint8_t)0x0D)   /* QUADSPI Alternate Function mapping */


/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_LCD           ((uint8_t)0x0E)   /* LCD Alternate Function mapping */
#define GPIO_AF14_DCMIPP        ((uint8_t)0x0E)   /* DCMI Alternate Function mapping */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_HDP           ((uint8_t)0x0F)  /* HDP Alternate Function mapping */

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

#define GPIO_GET_INDEX(__GPIOx__)            (((__GPIOx__) == (GPIOA))? 0UL :\
                                              ((__GPIOx__) == (GPIOB))? 1UL :\
                                              ((__GPIOx__) == (GPIOC))? 2UL :\
                                              ((__GPIOx__) == (GPIOD))? 3UL :\
                                              ((__GPIOx__) == (GPIOE))? 4UL :\
                                              ((__GPIOx__) == (GPIOF))? 5UL :\
                                              ((__GPIOx__) == (GPIOG))? 6UL :\
                                              ((__GPIOx__) == (GPIOH))? 7UL :\
                                              ((__GPIOx__) == (GPIOI))? 8UL : 25UL)
/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup GPIOEx_Exported_Functions GPIO Extended Exported Functions
  * @{
  */

/** @addtogroup GPIOEx_Exported_Functions_Group1 Extended Peripheral Control functions
  * @{
  */

void                HAL_GPIOEx_SecurePin(GPIO_TypeDef  *GPIOx, uint16_t GPIO_Pin);
void                HAL_GPIOEx_NonSecurePin(GPIO_TypeDef  *GPIOx, uint16_t GPIO_Pin);


GPIO_PinState       HAL_GPIOEx_IsPinSecured(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

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

#endif /* __STM32MP13xx_HAL_GPIO_EX_H */
