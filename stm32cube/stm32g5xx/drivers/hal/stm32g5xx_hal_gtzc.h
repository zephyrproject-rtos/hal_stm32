/**
  ********************************************************************************************************************
  * @file    stm32g5xx_hal_gtzc.h
  * @brief   Header file of GTZC HAL module.
  ********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ********************************************************************************************************************
  */

/* Define to prevent recursive inclusion ---------------------------------------------------------------------------*/
#ifndef STM32G5XX_HAL_GTZC_H
#define STM32G5XX_HAL_GTZC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes --------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_gtzc.h"

/** @addtogroup STM32G5XX_HAL_Driver
  * @{
  */

#if defined(GTZC1_TZSC1_PERIPH)

/** @addtogroup GTZC
  * @{
  */

/* Exported types --------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_Exported_Types GTZC Exported Types
  * @{
  */

/** @defgroup GTZC_Exported_Types_Group1 Enumerations
  * @{
  */

/**
  * @brief GTZC TZSC peripheral identifiers
  */
typedef enum
{
  HAL_GTZC_TZSC_ADC12              = LL_GTZC_ADC12,             /*!< GTZC TZSC peripheral ADC12   */
#if defined(ADC3)
  HAL_GTZC_TZSC_ADC3               = LL_GTZC_ADC3,              /*!< GTZC TZSC peripheral ADC3    */
#endif /* ADC3 */
#if defined(AES)
  HAL_GTZC_TZSC_AES                = LL_GTZC_AES,               /*!< GTZC TZSC peripheral AES     */
#endif /* AES */
#if defined(CCB)
  HAL_GTZC_TZSC_CCB                = LL_GTZC_CCB,               /*!< GTZC TZSC peripheral CCB     */
#endif /* CCB */
  HAL_GTZC_TZSC_COMP1              = LL_GTZC_COMP1,             /*!< GTZC TZSC peripheral COMP1   */
  HAL_GTZC_TZSC_COMP2              = LL_GTZC_COMP2,             /*!< GTZC TZSC peripheral COMP2   */
  HAL_GTZC_TZSC_COMP3              = LL_GTZC_COMP3,             /*!< GTZC TZSC peripheral COMP3   */
  HAL_GTZC_TZSC_COMP4              = LL_GTZC_COMP4,             /*!< GTZC TZSC peripheral COMP4   */
  HAL_GTZC_TZSC_COMP5              = LL_GTZC_COMP5,             /*!< GTZC TZSC peripheral COMP5   */
  HAL_GTZC_TZSC_COMP6              = LL_GTZC_COMP6,             /*!< GTZC TZSC peripheral COMP6   */
  HAL_GTZC_TZSC_COMP7              = LL_GTZC_COMP7,             /*!< GTZC TZSC peripheral COMP7   */
  HAL_GTZC_TZSC_COMP8              = LL_GTZC_COMP8,             /*!< GTZC TZSC peripheral COMP8   */
  HAL_GTZC_TZSC_CORDIC1            = LL_GTZC_CORDIC1,           /*!< GTZC TZSC peripheral CORDIC1 */
  HAL_GTZC_TZSC_CRC                = LL_GTZC_CRC,               /*!< GTZC TZSC peripheral CRC     */
#if defined(CRS)
  HAL_GTZC_TZSC_CRS                = LL_GTZC_CRS,               /*!< GTZC TZSC peripheral CRS     */
#endif /* CRS */
  HAL_GTZC_TZSC_DAC1               = LL_GTZC_DAC1,              /*!< GTZC TZSC peripheral DAC1    */
  HAL_GTZC_TZSC_DAC10              = LL_GTZC_DAC10,             /*!< GTZC TZSC peripheral DAC10   */
  HAL_GTZC_TZSC_DAC2               = LL_GTZC_DAC2,              /*!< GTZC TZSC peripheral DAC2    */
  HAL_GTZC_TZSC_DAC5               = LL_GTZC_DAC5,              /*!< GTZC TZSC peripheral DAC5    */
  HAL_GTZC_TZSC_DAC6               = LL_GTZC_DAC6,              /*!< GTZC TZSC peripheral DAC6    */
  HAL_GTZC_TZSC_DAC7               = LL_GTZC_DAC7,              /*!< GTZC TZSC peripheral DAC7    */
  HAL_GTZC_TZSC_DAC8               = LL_GTZC_DAC8,              /*!< GTZC TZSC peripheral DAC8    */
  HAL_GTZC_TZSC_DAC9               = LL_GTZC_DAC9,              /*!< GTZC TZSC peripheral DAC9    */
#if defined(DCACHE)
  HAL_GTZC_TZSC_DCACHE             = LL_GTZC_DCACHE,            /*!< GTZC TZSC peripheral DCACHE  */
#endif /* DCACHE */
  HAL_GTZC_TZSC_DTS                = LL_GTZC_DTS,               /*!< GTZC TZSC peripheral DTS     */
  HAL_GTZC_TZSC_FDCAN1             = LL_GTZC_FDCAN1,            /*!< GTZC TZSC peripheral FDCAN1  */
#if defined(FDCAN2)
  HAL_GTZC_TZSC_FDCAN2             = LL_GTZC_FDCAN2,            /*!< GTZC TZSC peripheral FDCAN2  */
#endif /* FDCAN2 */
#if defined(FDCAN3)
  HAL_GTZC_TZSC_FDCAN3             = LL_GTZC_FDCAN3,            /*!< GTZC TZSC peripheral FDCAN3  */
#endif /* FDCAN3 */
  HAL_GTZC_TZSC_FMAC1              = LL_GTZC_FMAC1,             /*!< GTZC TZSC peripheral FMAC1   */
#if defined(FMAC2)
  HAL_GTZC_TZSC_FMAC2              = LL_GTZC_FMAC2,             /*!< GTZC TZSC peripheral FMAC2   */
#endif /* FMAC2 */
  HAL_GTZC_TZSC_HASH               = LL_GTZC_HASH,              /*!< GTZC TZSC peripheral HASH    */
#if defined(HRTIM1)
  HAL_GTZC_TZSC_HRTIM1             = LL_GTZC_HRTIM1,            /*!< GTZC TZSC peripheral HRTIM1  */
#endif /* HRTIM1 */
  HAL_GTZC_TZSC_I2C1               = LL_GTZC_I2C1,              /*!< GTZC TZSC peripheral I2C1    */
  HAL_GTZC_TZSC_I2C2               = LL_GTZC_I2C2,              /*!< GTZC TZSC peripheral I2C2    */
#if defined(I2C3)
  HAL_GTZC_TZSC_I2C3               = LL_GTZC_I2C3,              /*!< GTZC TZSC peripheral I2C3    */
#endif /* I2C3 */
#if defined(I2C4)
  HAL_GTZC_TZSC_I2C4               = LL_GTZC_I2C4,              /*!< GTZC TZSC peripheral I2C4    */
#endif /* I2C4 */
  HAL_GTZC_TZSC_I3C1               = LL_GTZC_I3C1,              /*!< GTZC TZSC peripheral I3C1    */
  HAL_GTZC_TZSC_ICACHE             = LL_GTZC_ICACHE,            /*!< GTZC TZSC peripheral ICACHE  */
  HAL_GTZC_TZSC_IWDG               = LL_GTZC_IWDG,              /*!< GTZC TZSC peripheral IWDG    */
  HAL_GTZC_TZSC_LPTIM1             = LL_GTZC_LPTIM1,            /*!< GTZC TZSC peripheral LPTIM1  */
  HAL_GTZC_TZSC_LPUART1            = LL_GTZC_LPUART1,           /*!< GTZC TZSC peripheral LPUART1 */
#if defined(OPAMP1)
  HAL_GTZC_TZSC_OPAMP1             = LL_GTZC_OPAMP1,            /*!< GTZC TZSC peripheral OPAMP1  */
#endif /* OPAMP1 */
#if defined(OPAMP2)
  HAL_GTZC_TZSC_OPAMP2             = LL_GTZC_OPAMP2,            /*!< GTZC TZSC peripheral OPAMP2  */
#endif /* OPAMP2 */
#if defined(OPAMP3)
  HAL_GTZC_TZSC_OPAMP3             = LL_GTZC_OPAMP3,            /*!< GTZC TZSC peripheral OPAMP3  */
#endif /* OPAMP3 */
  HAL_GTZC_TZSC_PKA                = LL_GTZC_PKA,               /*!< GTZC TZSC peripheral PKA      */
#if defined(POSENC1)
  HAL_GTZC_TZSC_POSENC1            = LL_GTZC_POSENC1,           /*!< GTZC TZSC peripheral POSENC1   */
#endif /* POSENC1 */
#if defined(POSENC2)
  HAL_GTZC_TZSC_POSENC2            = LL_GTZC_POSENC2,           /*!< GTZC TZSC peripheral POSENC2   */
#endif /* POSENC2 */
  HAL_GTZC_TZSC_RAMCFG             = LL_GTZC_RAMCFG,            /*!< GTZC TZSC peripheral RAMCFG    */
  HAL_GTZC_TZSC_RNG                = LL_GTZC_RNG,               /*!< GTZC TZSC peripheral RNG       */
#if defined(SAES)
  HAL_GTZC_TZSC_SAES               = LL_GTZC_SAES,              /*!< GTZC TZSC peripheral SAES      */
#endif /* SAES */
  HAL_GTZC_TZSC_SPI1               = LL_GTZC_SPI1,              /*!< GTZC TZSC peripheral SPI1      */
  HAL_GTZC_TZSC_SPI2               = LL_GTZC_SPI2,              /*!< GTZC TZSC peripheral SPI2      */
#if defined(SPI3)
  HAL_GTZC_TZSC_SPI3               = LL_GTZC_SPI3,              /*!< GTZC TZSC peripheral SPI3      */
#endif /* SPI3 */
  HAL_GTZC_TZSC_TIM1               = LL_GTZC_TIM1,              /*!< GTZC TZSC peripheral TIM1      */
  HAL_GTZC_TZSC_TIM2               = LL_GTZC_TIM2,              /*!< GTZC TZSC peripheral TIM2      */
#if defined(TIM3)
  HAL_GTZC_TZSC_TIM3               = LL_GTZC_TIM3,              /*!< GTZC TZSC peripheral TIM3      */
#endif /* TIM3 */
#if defined(TIM4)
  HAL_GTZC_TZSC_TIM4               = LL_GTZC_TIM4,              /*!< GTZC TZSC peripheral TIM4      */
#endif /* TIM4 */
#if defined(TIM5)
  HAL_GTZC_TZSC_TIM5               = LL_GTZC_TIM5,              /*!< GTZC TZSC peripheral TIM5      */
#endif /* TIM5 */
  HAL_GTZC_TZSC_TIM6               = LL_GTZC_TIM6,              /*!< GTZC TZSC peripheral TIM6      */
  HAL_GTZC_TZSC_TIM7               = LL_GTZC_TIM7,              /*!< GTZC TZSC peripheral TIM7      */
  HAL_GTZC_TZSC_TIM8               = LL_GTZC_TIM8,              /*!< GTZC TZSC peripheral TIM8      */
  HAL_GTZC_TZSC_TIM9               = LL_GTZC_TIM9,              /*!< GTZC TZSC peripheral TIM9      */
  HAL_GTZC_TZSC_TIM10              = LL_GTZC_TIM10,             /*!< GTZC TZSC peripheral TIM10     */
  HAL_GTZC_TZSC_TIM11              = LL_GTZC_TIM11,             /*!< GTZC TZSC peripheral TIM11     */
  HAL_GTZC_TZSC_TIM12              = LL_GTZC_TIM12,             /*!< GTZC TZSC peripheral TIM12     */
  HAL_GTZC_TZSC_TIM13              = LL_GTZC_TIM13,             /*!< GTZC TZSC peripheral TIM13     */
  HAL_GTZC_TZSC_TIM14              = LL_GTZC_TIM14,             /*!< GTZC TZSC peripheral TIM14     */
  HAL_GTZC_TZSC_TIM15              = LL_GTZC_TIM15,             /*!< GTZC TZSC peripheral TIM15     */
  HAL_GTZC_TZSC_TIM16              = LL_GTZC_TIM16,             /*!< GTZC TZSC peripheral TIM16     */
  HAL_GTZC_TZSC_TIM17              = LL_GTZC_TIM17,             /*!< GTZC TZSC peripheral TIM17     */
#if defined(TIM20)
  HAL_GTZC_TZSC_TIM20              = LL_GTZC_TIM20,             /*!< GTZC TZSC peripheral TIM20     */
#endif /* TIM20 */
  HAL_GTZC_TZSC_TIM26              = LL_GTZC_TIM26,             /*!< GTZC TZSC peripheral TIM26     */
  HAL_GTZC_TZSC_TIM27              = LL_GTZC_TIM27,             /*!< GTZC TZSC peripheral TIM27     */
  HAL_GTZC_TZSC_UART4              = LL_GTZC_UART4,             /*!< GTZC TZSC peripheral UART4     */
  HAL_GTZC_TZSC_UART5              = LL_GTZC_UART5,             /*!< GTZC TZSC peripheral UART5     */
#if defined(UART6)
  HAL_GTZC_TZSC_UART6              = LL_GTZC_UART6,             /*!< GTZC TZSC peripheral UART6     */
#endif /* UART6 */
#if defined(UCPD1)
  HAL_GTZC_TZSC_UCPD1              = LL_GTZC_UCPD1,             /*!< GTZC TZSC peripheral UCPD1     */
#endif /* UCPD1 */
  HAL_GTZC_TZSC_USART1             = LL_GTZC_USART1,            /*!< GTZC TZSC peripheral USART1    */
  HAL_GTZC_TZSC_USART2             = LL_GTZC_USART2,            /*!< GTZC TZSC peripheral USART2    */
#if defined(USART3)
  HAL_GTZC_TZSC_USART3             = LL_GTZC_USART3,            /*!< GTZC TZSC peripheral USART3    */
#endif /* USART3 */
#if defined(USB)
  HAL_GTZC_TZSC_USB                = LL_GTZC_USB,               /*!< GTZC TZSC peripheral USB     */
#endif /* USB */
  HAL_GTZC_TZSC_VREFBUF            = LL_GTZC_VREFBUF,           /*!< GTZC TZSC peripheral VREFBUF */
  HAL_GTZC_TZSC_WWDG               = LL_GTZC_WWDG,              /*!< GTZC TZSC peripheral WWDG    */
#if defined(XSPI1)
  HAL_GTZC_TZSC_XSPI1              = LL_GTZC_XSPI1,             /*!< GTZC TZSC peripheral XSPI1   */
  HAL_GTZC_TZSC_XSPI1_MEM          = LL_GTZC_XSPI1_MEM,         /*!< GTZC TZSC peripheral XSPI1_MEM  */
#endif /* XSPI1 */
  HAL_GTZC_TZSC_PERIPH_ALL         = 0xFFFFFFFFU                /*!< GTZC TZSC peripheral ALL     */
} hal_gtzc_tzsc_periph_t;

/**
  * @brief GTZC TZIC peripheral identifiers
  */
typedef enum
{
  HAL_GTZC_TZIC_ADC12              = LL_GTZC_ADC12,             /*!< GTZC TZIC peripheral ADC12   */
#if defined(ADC3)
  HAL_GTZC_TZIC_ADC3               = LL_GTZC_ADC3,              /*!< GTZC TZIC peripheral ADC3    */
#endif /* ADC3 */
#if defined(AES)
  HAL_GTZC_TZIC_AES                = LL_GTZC_AES,               /*!< GTZC TZIC peripheral AES     */
#endif /* AES */
#if defined(CCB)
  HAL_GTZC_TZIC_CCB                = LL_GTZC_CCB,               /*!< GTZC TZIC peripheral CCB     */
#endif /* CCB */
  HAL_GTZC_TZIC_COMP1              = LL_GTZC_COMP1,             /*!< GTZC TZIC peripheral COMP1   */
  HAL_GTZC_TZIC_COMP2              = LL_GTZC_COMP2,             /*!< GTZC TZIC peripheral COMP2   */
  HAL_GTZC_TZIC_COMP3              = LL_GTZC_COMP3,             /*!< GTZC TZIC peripheral COMP3   */
  HAL_GTZC_TZIC_COMP4              = LL_GTZC_COMP4,             /*!< GTZC TZIC peripheral COMP4   */
  HAL_GTZC_TZIC_COMP5              = LL_GTZC_COMP5,             /*!< GTZC TZIC peripheral COMP5   */
  HAL_GTZC_TZIC_COMP6              = LL_GTZC_COMP6,             /*!< GTZC TZIC peripheral COMP6   */
  HAL_GTZC_TZIC_COMP7              = LL_GTZC_COMP7,             /*!< GTZC TZIC peripheral COMP7   */
  HAL_GTZC_TZIC_COMP8              = LL_GTZC_COMP8,             /*!< GTZC TZIC peripheral COMP8   */
  HAL_GTZC_TZIC_CORDIC1            = LL_GTZC_CORDIC1,           /*!< GTZC TZIC peripheral CORDIC1 */
  HAL_GTZC_TZIC_CRC                = LL_GTZC_CRC,               /*!< GTZC TZIC peripheral CRC     */
#if defined(CRS)
  HAL_GTZC_TZIC_CRS                = LL_GTZC_CRS,               /*!< GTZC TZIC peripheral CRS     */
#endif /* CRS */
  HAL_GTZC_TZIC_DAC1               = LL_GTZC_DAC1,              /*!< GTZC TZIC peripheral DAC1    */
  HAL_GTZC_TZIC_DAC10              = LL_GTZC_DAC10,             /*!< GTZC TZIC peripheral DAC10   */
  HAL_GTZC_TZIC_DAC2               = LL_GTZC_DAC2,              /*!< GTZC TZIC peripheral DAC2    */
  HAL_GTZC_TZIC_DAC5               = LL_GTZC_DAC5,              /*!< GTZC TZIC peripheral DAC5    */
  HAL_GTZC_TZIC_DAC6               = LL_GTZC_DAC6,              /*!< GTZC TZIC peripheral DAC6    */
  HAL_GTZC_TZIC_DAC7               = LL_GTZC_DAC7,              /*!< GTZC TZIC peripheral DAC7    */
  HAL_GTZC_TZIC_DAC8               = LL_GTZC_DAC8,              /*!< GTZC TZIC peripheral DAC8    */
  HAL_GTZC_TZIC_DAC9               = LL_GTZC_DAC9,              /*!< GTZC TZIC peripheral DAC9    */
#if defined(DCACHE)
  HAL_GTZC_TZIC_DCACHE             = LL_GTZC_DCACHE,            /*!< GTZC TZIC peripheral DCACHE  */
#endif /* DCACHE */
  HAL_GTZC_TZIC_DTS                = LL_GTZC_DTS,               /*!< GTZC TZIC peripheral DTS     */
  HAL_GTZC_TZIC_EXTI               = LL_GTZC_EXTI,              /*!< GTZC TZIC peripheral EXTI    */
  HAL_GTZC_TZIC_FDCAN1             = LL_GTZC_FDCAN1,            /*!< GTZC TZIC peripheral FDCAN1  */
#if defined(FDCAN2)
  HAL_GTZC_TZIC_FDCAN2             = LL_GTZC_FDCAN2,            /*!< GTZC TZIC peripheral FDCAN2  */
#endif /* FDCAN2 */
#if defined(FDCAN3)
  HAL_GTZC_TZIC_FDCAN3             = LL_GTZC_FDCAN3,            /*!< GTZC TZIC peripheral FDCAN3  */
#endif /* FDCAN3 */
  HAL_GTZC_TZIC_FLASH              = LL_GTZC_FLASH_REG,         /*!< GTZC TZIC peripheral FLASH   */
  HAL_GTZC_TZIC_FLASH_MEM          = LL_GTZC_FLASH,             /*!< GTZC TZIC peripheral FLASH_MEM */
  HAL_GTZC_TZIC_FMAC1              = LL_GTZC_FMAC1,             /*!< GTZC TZIC peripheral FMAC1   */
#if defined(FMAC2)
  HAL_GTZC_TZIC_FMAC2              = LL_GTZC_FMAC2,             /*!< GTZC TZIC peripheral FMAC2   */
#endif /* FMAC2 */
  HAL_GTZC_TZIC_GPDMA1             = LL_GTZC_GPDMA1,            /*!< GTZC TZIC peripheral GPDMA1  */
  HAL_GTZC_TZIC_GPDMA2             = LL_GTZC_GPDMA2,            /*!< GTZC TZIC peripheral GPDMA2  */
  HAL_GTZC_TZIC_HASH               = LL_GTZC_HASH,              /*!< GTZC TZIC peripheral HASH    */
#if defined(HRTIM1)
  HAL_GTZC_TZIC_HRTIM1             = LL_GTZC_HRTIM1,            /*!< GTZC TZIC peripheral HRTIM1  */
#endif /* HRTIM1 */
  HAL_GTZC_TZIC_I2C1               = LL_GTZC_I2C1,              /*!< GTZC TZIC peripheral I2C1    */
  HAL_GTZC_TZIC_I2C2               = LL_GTZC_I2C2,              /*!< GTZC TZIC peripheral I2C2    */
#if defined(I2C3)
  HAL_GTZC_TZIC_I2C3               = LL_GTZC_I2C3,              /*!< GTZC TZIC peripheral I2C3    */
#endif /* I2C3 */
#if defined(I2C4)
  HAL_GTZC_TZIC_I2C4               = LL_GTZC_I2C4,              /*!< GTZC TZIC peripheral I2C4    */
#endif /* I2C4 */
  HAL_GTZC_TZIC_I3C1               = LL_GTZC_I3C1,              /*!< GTZC TZIC peripheral I3C1    */
  HAL_GTZC_TZIC_ICACHE             = LL_GTZC_ICACHE,            /*!< GTZC TZIC peripheral ICACHE  */
  HAL_GTZC_TZIC_IWDG               = LL_GTZC_IWDG,              /*!< GTZC TZIC peripheral IWDG    */
  HAL_GTZC_TZIC_LPTIM1             = LL_GTZC_LPTIM1,            /*!< GTZC TZIC peripheral LPTIM1  */
  HAL_GTZC_TZIC_LPUART1            = LL_GTZC_LPUART1,           /*!< GTZC TZIC peripheral LPUART1 */
  HAL_GTZC_TZIC_MPCBB1             = LL_GTZC_MPCBB1_REG,        /*!< GTZC TZIC peripheral MPCBB1  */
  HAL_GTZC_TZIC_MPCBB2             = LL_GTZC_MPCBB2_REG,        /*!< GTZC TZIC peripheral MPCBB2  */
#if defined(SRAM3_BASE)
  HAL_GTZC_TZIC_MPCBB3             = LL_GTZC_MPCBB3_REG,        /*!< GTZC TZIC peripheral MPCBB3  */
#endif /* SRAM3_BASE */
#if defined(OPAMP1)
  HAL_GTZC_TZIC_OPAMP1             = LL_GTZC_OPAMP1,            /*!< GTZC TZIC peripheral OPAMP1  */
#endif /* OPAMP1 */
#if defined(OPAMP2)
  HAL_GTZC_TZIC_OPAMP2             = LL_GTZC_OPAMP2,            /*!< GTZC TZIC peripheral OPAMP2  */
#endif /* OPAMP2 */
#if defined(OPAMP3)
  HAL_GTZC_TZIC_OPAMP3             = LL_GTZC_OPAMP3,            /*!< GTZC TZIC peripheral OPAMP3  */
#endif /* OPAMP3 */
#if defined(OTFDEC1)
  HAL_GTZC_TZIC_OTFDEC1            = LL_GTZC_OTFDEC1,           /*!< GTZC TZIC peripheral OTFDEC1  */
#endif /* OTFDEC1 */
  HAL_GTZC_TZIC_PKA                = LL_GTZC_PKA,               /*!< GTZC TZIC peripheral PKA      */
#if defined(PLAY1)
  HAL_GTZC_TZIC_PLAY1              = LL_GTZC_PLAY1,             /*!< GTZC TZIC peripheral PLAY1     */
#endif /* PLAY1 */
#if defined(POSENC1)
  HAL_GTZC_TZIC_POSENC1            = LL_GTZC_POSENC1,           /*!< GTZC TZIC peripheral POSENC1   */
#endif /* POSENC1 */
#if defined(POSENC2)
  HAL_GTZC_TZIC_POSENC2            = LL_GTZC_POSENC2,           /*!< GTZC TZIC peripheral POSENC2   */
#endif /* POSENC2 */
  HAL_GTZC_TZIC_PWR                = LL_GTZC_PWR,               /*!< GTZC TZIC peripheral PWR       */
  HAL_GTZC_TZIC_RAMCFG             = LL_GTZC_RAMCFG,            /*!< GTZC TZIC peripheral RAMCFG    */
  HAL_GTZC_TZIC_RCC                = LL_GTZC_RCC,               /*!< GTZC TZIC peripheral RCC       */
  HAL_GTZC_TZIC_RNG                = LL_GTZC_RNG,               /*!< GTZC TZIC peripheral RNG       */
  HAL_GTZC_TZIC_RTC                = LL_GTZC_RTC,               /*!< GTZC TZIC peripheral RTC       */
#if defined(SAES)
  HAL_GTZC_TZIC_SAES               = LL_GTZC_SAES,              /*!< GTZC TZIC peripheral SAES      */
#endif /* SAES */
  HAL_GTZC_TZIC_SBS                = LL_GTZC_SBS,               /*!< GTZC TZIC peripheral SBS       */
  HAL_GTZC_TZIC_SPI1               = LL_GTZC_SPI1,              /*!< GTZC TZIC peripheral SPI1      */
  HAL_GTZC_TZIC_SPI2               = LL_GTZC_SPI2,              /*!< GTZC TZIC peripheral SPI2      */
#if defined(SPI3)
  HAL_GTZC_TZIC_SPI3               = LL_GTZC_SPI3,              /*!< GTZC TZIC peripheral SPI3      */
#endif /* SPI3 */
  HAL_GTZC_TZIC_SRAM1              = LL_GTZC_SRAM1,             /*!< GTZC TZIC peripheral SRAM1     */
  HAL_GTZC_TZIC_SRAM2              = LL_GTZC_SRAM2,             /*!< GTZC TZIC peripheral SRAM2     */
#if defined(SRAM3_BASE)
  HAL_GTZC_TZIC_SRAM3              = LL_GTZC_SRAM3,             /*!< GTZC TZIC peripheral SRAM3     */
#endif /* SRAM3_BASE */
  HAL_GTZC_TZIC_TAMP               = LL_GTZC_TAMP,              /*!< GTZC TZIC peripheral TAMP      */
  HAL_GTZC_TZIC_TIM1               = LL_GTZC_TIM1,              /*!< GTZC TZIC peripheral TIM1      */
  HAL_GTZC_TZIC_TIM10              = LL_GTZC_TIM10,             /*!< GTZC TZIC peripheral TIM10     */
  HAL_GTZC_TZIC_TIM11              = LL_GTZC_TIM11,             /*!< GTZC TZIC peripheral TIM11     */
  HAL_GTZC_TZIC_TIM12              = LL_GTZC_TIM12,             /*!< GTZC TZIC peripheral TIM12     */
  HAL_GTZC_TZIC_TIM13              = LL_GTZC_TIM13,             /*!< GTZC TZIC peripheral TIM13     */
  HAL_GTZC_TZIC_TIM14              = LL_GTZC_TIM14,             /*!< GTZC TZIC peripheral TIM14     */
  HAL_GTZC_TZIC_TIM15              = LL_GTZC_TIM15,             /*!< GTZC TZIC peripheral TIM15     */
  HAL_GTZC_TZIC_TIM16              = LL_GTZC_TIM16,             /*!< GTZC TZIC peripheral TIM16     */
  HAL_GTZC_TZIC_TIM17              = LL_GTZC_TIM17,             /*!< GTZC TZIC peripheral TIM17     */
  HAL_GTZC_TZIC_TIM2               = LL_GTZC_TIM2,              /*!< GTZC TZIC peripheral TIM2      */
#if defined(TIM20)
  HAL_GTZC_TZIC_TIM20              = LL_GTZC_TIM20,             /*!< GTZC TZIC peripheral TIM20     */
#endif /* TIM20 */
  HAL_GTZC_TZIC_TIM26              = LL_GTZC_TIM26,             /*!< GTZC TZIC peripheral TIM26     */
  HAL_GTZC_TZIC_TIM27              = LL_GTZC_TIM27,             /*!< GTZC TZIC peripheral TIM27     */
#if defined(TIM3)
  HAL_GTZC_TZIC_TIM3               = LL_GTZC_TIM3,              /*!< GTZC TZIC peripheral TIM3      */
#endif /* TIM3 */
#if defined(TIM4)
  HAL_GTZC_TZIC_TIM4               = LL_GTZC_TIM4,              /*!< GTZC TZIC peripheral TIM4      */
#endif /* TIM4 */
#if defined(TIM5)
  HAL_GTZC_TZIC_TIM5               = LL_GTZC_TIM5,              /*!< GTZC TZIC peripheral TIM5      */
#endif /* TIM5 */
  HAL_GTZC_TZIC_TIM6               = LL_GTZC_TIM6,              /*!< GTZC TZIC peripheral TIM6      */
  HAL_GTZC_TZIC_TIM7               = LL_GTZC_TIM7,              /*!< GTZC TZIC peripheral TIM7      */
  HAL_GTZC_TZIC_TIM8               = LL_GTZC_TIM8,              /*!< GTZC TZIC peripheral TIM8      */
  HAL_GTZC_TZIC_TIM9               = LL_GTZC_TIM9,              /*!< GTZC TZIC peripheral TIM9      */
  HAL_GTZC_TZIC_TZIC1              = LL_GTZC_TZIC1,             /*!< GTZC TZIC peripheral TZIC1     */
  HAL_GTZC_TZIC_TZSC1              = LL_GTZC_TZSC1,             /*!< GTZC TZIC peripheral TZSC1     */
  HAL_GTZC_TZIC_UART4              = LL_GTZC_UART4,             /*!< GTZC TZIC peripheral UART4     */
  HAL_GTZC_TZIC_UART5              = LL_GTZC_UART5,             /*!< GTZC TZIC peripheral UART5     */
#if defined(UART6)
  HAL_GTZC_TZIC_UART6              = LL_GTZC_UART6,             /*!< GTZC TZIC peripheral UART6     */
#endif /* UART6 */
#if defined(UCPD1)
  HAL_GTZC_TZIC_UCPD1              = LL_GTZC_UCPD1,             /*!< GTZC TZIC peripheral UCPD1     */
#endif /* UCPD1 */
  HAL_GTZC_TZIC_USART1             = LL_GTZC_USART1,            /*!< GTZC TZIC peripheral USART1    */
  HAL_GTZC_TZIC_USART2             = LL_GTZC_USART2,            /*!< GTZC TZIC peripheral USART2    */
#if defined(USART3)
  HAL_GTZC_TZIC_USART3             = LL_GTZC_USART3,            /*!< GTZC TZIC peripheral USART3    */
#endif /* USART3 */
#if defined(USB)
  HAL_GTZC_TZIC_USB                = LL_GTZC_USB,               /*!< GTZC TZIC peripheral USB     */
#endif /* USB */
  HAL_GTZC_TZIC_VREFBUF            = LL_GTZC_VREFBUF,           /*!< GTZC TZIC peripheral VREFBUF */
  HAL_GTZC_TZIC_WWDG               = LL_GTZC_WWDG,              /*!< GTZC TZIC peripheral WWDG    */
#if defined(XSPI1)
  HAL_GTZC_TZIC_XSPI1              = LL_GTZC_XSPI1,             /*!< GTZC TZIC peripheral XSPI1   */
  HAL_GTZC_TZIC_XSPI1_MEM          = LL_GTZC_XSPI1_MEM,         /*!< GTZC TZIC peripheral XSPI1_MEM  */
#endif /* XSPI1 */
  HAL_GTZC_TZIC_PERIPH_ALL         = 0xFFFFFFFFU                /*!< GTZC TZIC peripheral ALL     */

} hal_gtzc_tzic_periph_t;

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief GTZC TZSC_MPCWM memories
  */
typedef enum
{
  HAL_GTZC_TZSC_MPCWM_XSPI1    = LL_GTZC_TZSC_MPCWM_XSPI1 /*!< GTZC water mark XSPI1 memory    */
} hal_gtzc_tzsc_mpcwm_memory_t;
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief GTZC MPCBB memories
  */
typedef enum
{
  HAL_GTZC_MPCBB_SRAM1 = LL_GTZC_MPCBB_SRAM1,   /*!< GTZC MPCBB SRAM1 memory */
  HAL_GTZC_MPCBB_SRAM2 = LL_GTZC_MPCBB_SRAM2,   /*!< GTZC MPCBB SRAM2 memory */
#if defined (SRAM3_BASE)
  HAL_GTZC_MPCBB_SRAM3 = LL_GTZC_MPCBB_SRAM3,   /*!< GTZC MPCBB SRAM3 memory */
#endif /* SRAM3_BASE */
} hal_gtzc_mpcbb_memory_t;

/**
  * @brief GTZC Securable peripherals groups
  */
typedef enum
{
  HAL_GTZC1_PERIPH_ALL = (uint32_t)GTZC1_TZSC1_PERIPH_BASE, /*!< GTZC1 lock peripheral attribute */
} hal_gtzc_lock_periph_t;

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief GTZC TZSC_MPCWM subregions
  */
typedef enum
{
  HAL_GTZC_TZSC_MPCWM_SUBREGION_A = LL_GTZC_TZSC_MPCWM_SUBREGION_A, /*!< GTZC TZSC_MPCWM subregion A */
  HAL_GTZC_TZSC_MPCWM_SUBREGION_B = LL_GTZC_TZSC_MPCWM_SUBREGION_B  /*!< GTZC TZSC_MPCWM subregion B */
} hal_gtzc_tzsc_mpcwm_subregion_t;

/**
  * @brief GTZC TZSC_MPCWM subregion status
  */
typedef enum
{
  HAL_GTZC_TZSC_MPCWM_SUBREGION_DISABLED = 0U, /*!< GTZC TZSC_MPCWM subregion disabled */
  HAL_GTZC_TZSC_MPCWM_SUBREGION_ENABLED  = 1U  /*!< GTZC TZSC_MPCWM subregion enabled  */
} hal_gtzc_tzsc_mpcwm_subregion_status_t;

/**
  * @brief GTZC Memory security access state
  */
typedef enum
{
  HAL_GTZC_MPCBB_SEC_TO_NSEC_DISABLED = 0U, /*!< GTZC MPCBB secure read/write data accesses to non-secure block and
                                                 pages disabled */
  HAL_GTZC_MPCBB_SEC_TO_NSEC_ENABLED  = 1U  /*!< GTZC MPCBB secure read/write data accesses to non-secure block and
                                                 pages enabled */
} hal_gtzc_mpcbb_sec_to_nsec_access_status_t;

/**
  * @brief GTZC Memory clock security state
  */
typedef enum
{
  HAL_GTZC_TZSC_CLK_SEC_NOT_INVERTED = LL_GTZC_MPCBB_CLK_SEC_NOT_INVERTED, /*!< GTZC clock security not inverted */
  HAL_GTZC_TZSC_CLK_SEC_INVERTED     = LL_GTZC_MPCBB_CLK_SEC_INVERTED      /*!< GTZC clock security inverted     */
} hal_gtzc_mpcbb_clk_sec_invert_state_t;

#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief GTZC configuration lock status
  */
typedef enum
{
  HAL_GTZC_UNLOCKED = 0U, /*!< GTZC configuration unlocked */
  HAL_GTZC_LOCKED   = 1U  /*!< GTZC configuration locked   */
} hal_gtzc_lock_status_t;

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief GTZC Illegal access interrupt status
  */
typedef enum
{
  HAL_GTZC_TZIC_IT_DISABLED = 0U, /*!< GTZC Illegal access interrupt disabled */
  HAL_GTZC_TZIC_IT_ENABLED  = 1U  /*!< GTZC Illegal access interrupt enabled  */
} hal_gtzc_tzic_it_status_t;
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief Security access level attribute.
  */
typedef enum
{
  HAL_GTZC_NSEC = LL_GTZC_ATTR_NSEC, /*!< Non-secure access level attribute */
  HAL_GTZC_SEC  = LL_GTZC_ATTR_SEC   /*!< Secure access level attribute     */
} hal_gtzc_sec_attr_t;

/**
  * @brief Privileged access level attribute.
  */
typedef enum
{
  HAL_GTZC_NPRIV = LL_GTZC_ATTR_NPRIV, /*!< Non-privileged access level attribute */
  HAL_GTZC_PRIV  = LL_GTZC_ATTR_PRIV   /*!< Privileged access level attribute     */
} hal_gtzc_priv_attr_t;

/**
  * @}
  */

/**
  * @}
  */

/* Exported constants ----------------------------------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_Exported_Functions HAL GTZC Functions
  * @{
  */

/** @defgroup GTZC_Exported_Functions_Group1 TZSC peripherals security and privilege configuration functions
  * @{
  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t         HAL_GTZC_TZSC_SetPeriphSecAttr(hal_gtzc_tzsc_periph_t periph, hal_gtzc_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_status_t         HAL_GTZC_TZSC_SetPeriphPrivAttr(hal_gtzc_tzsc_periph_t periph, hal_gtzc_priv_attr_t priv_attr);
hal_gtzc_sec_attr_t  HAL_GTZC_TZSC_GetPeriphSecAttr(hal_gtzc_tzsc_periph_t periph);
hal_gtzc_priv_attr_t HAL_GTZC_TZSC_GetPeriphPrivAttr(hal_gtzc_tzsc_periph_t periph);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group2 TZSC configuration lock functions
  * @{
  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t           HAL_GTZC_TZSC_LockConfig(hal_gtzc_lock_periph_t periph);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_gtzc_lock_status_t HAL_GTZC_TZSC_IsLockedConfig(hal_gtzc_lock_periph_t periph);
/**
  * @}
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/** @defgroup GTZC_Exported_Functions_Group3 TZSC_MPCWM configuration functions
  * @{
  */

hal_status_t HAL_GTZC_TZSC_MPCWM_EnableSubRegion(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                 hal_gtzc_tzsc_mpcwm_subregion_t subregion);
hal_status_t HAL_GTZC_TZSC_MPCWM_DisableSubRegion(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                  hal_gtzc_tzsc_mpcwm_subregion_t subregion);
hal_gtzc_tzsc_mpcwm_subregion_status_t HAL_GTZC_TZSC_MPCWM_IsEnabledSubRegion(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                                              hal_gtzc_tzsc_mpcwm_subregion_t
                                                                              subregion);

hal_status_t HAL_GTZC_TZSC_MPCWM_SetSubRegionBoundaries(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                        hal_gtzc_tzsc_mpcwm_subregion_t subregion,
                                                        uint32_t offset_byte,
                                                        uint32_t size_byte);

void HAL_GTZC_TZSC_MPCWM_GetSubRegionBoundaries(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                hal_gtzc_tzsc_mpcwm_subregion_t subregion,
                                                uint32_t *offset_byte,
                                                uint32_t *size_byte);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group4 TZSC_MPCWM subregion security and privilege configuration functions
  * @{
  */
hal_status_t HAL_GTZC_TZSC_MPCWM_SetSubRegionSecAttr(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                     hal_gtzc_tzsc_mpcwm_subregion_t subregion,
                                                     hal_gtzc_sec_attr_t sec_attr);

hal_status_t HAL_GTZC_TZSC_MPCWM_SetSubRegionPrivAttr(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                      hal_gtzc_tzsc_mpcwm_subregion_t subregion,
                                                      hal_gtzc_priv_attr_t priv_attr);

hal_gtzc_sec_attr_t HAL_GTZC_TZSC_MPCWM_GetSubRegionSecAttr(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                            hal_gtzc_tzsc_mpcwm_subregion_t subregion);

hal_gtzc_priv_attr_t HAL_GTZC_TZSC_MPCWM_GetSubRegionPrivAttr(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                              hal_gtzc_tzsc_mpcwm_subregion_t subregion);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group5 TZSC_MPCWM subregion lock configuration functions
  * @{
  */
hal_status_t           HAL_GTZC_TZSC_MPCWM_LockSubRegionConfig(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                               hal_gtzc_tzsc_mpcwm_subregion_t subregion);

hal_gtzc_lock_status_t HAL_GTZC_TZSC_MPCWM_IsLockedSubRegionConfig(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                                   hal_gtzc_tzsc_mpcwm_subregion_t subregion);
/**
  * @}
  */
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/** @defgroup GTZC_Exported_Functions_Group6 MPCBB security and privilege configuration block functions
  * @{
  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_GTZC_MPCBB_SetSecAttrByBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t start_block, uint32_t block_nbr,
                                              hal_gtzc_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

hal_status_t HAL_GTZC_MPCBB_SetPrivAttrByBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t start_block,
                                               uint32_t block_nbr, hal_gtzc_priv_attr_t priv_attr);

hal_gtzc_sec_attr_t  HAL_GTZC_MPCBB_GetSecAttrByBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t block);
hal_gtzc_priv_attr_t HAL_GTZC_MPCBB_GetPrivAttrByBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t block);
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_GTZC_MPCBB_SetSecAttrByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte, uint32_t size_byte,
                                             hal_gtzc_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

hal_status_t HAL_GTZC_MPCBB_SetPrivAttrByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte, uint32_t size_byte,
                                              hal_gtzc_priv_attr_t priv_attr);

hal_gtzc_sec_attr_t HAL_GTZC_MPCBB_GetSecAttrByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte);
hal_gtzc_priv_attr_t HAL_GTZC_MPCBB_GetPrivAttrByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group7 MPCBB security access configuration functions
  * @{
  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_GTZC_MPCBB_EnableSecToNSecRdWrAccess(hal_gtzc_mpcbb_memory_t memory);
hal_status_t HAL_GTZC_MPCBB_DisableSecToNSecRdWrAccess(hal_gtzc_mpcbb_memory_t memory);
hal_gtzc_mpcbb_sec_to_nsec_access_status_t HAL_GTZC_MPCBB_IsEnabledSecToNSecRdWrAccess(hal_gtzc_mpcbb_memory_t memory);

hal_status_t HAL_GTZC_MPCBB_SetClkSecStateInvertion(hal_gtzc_mpcbb_memory_t memory,
                                                    hal_gtzc_mpcbb_clk_sec_invert_state_t clk_sec_invert_state);

hal_gtzc_mpcbb_clk_sec_invert_state_t HAL_GTZC_MPCBB_GetClkSecStateInvertion(hal_gtzc_mpcbb_memory_t memory);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group8 MPCBB lock configuration functions
  * @{
  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_GTZC_MPCBB_LockConfigBySuperBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t start_super_block,
                                                   uint32_t super_block_nbr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_gtzc_lock_status_t HAL_GTZC_MPCBB_IsLockedConfigBySuperBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t super_block);

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_GTZC_MPCBB_LockConfigByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte, uint32_t size_byte);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_gtzc_lock_status_t HAL_GTZC_MPCBB_IsLockedConfigByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte);

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_GTZC_MPCBB_LockConfig(hal_gtzc_mpcbb_memory_t memory);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_gtzc_lock_status_t HAL_GTZC_MPCBB_IsLockedConfig(hal_gtzc_mpcbb_memory_t memory);
/**
  * @}
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/** @defgroup GTZC_Exported_Functions_Group9 TZIC illegal access interrupt configuration functions
  * @{
  */
hal_status_t HAL_GTZC_TZIC_EnableIT(hal_gtzc_tzic_periph_t periph);
hal_status_t HAL_GTZC_TZIC_DisableIT(hal_gtzc_tzic_periph_t periph);
hal_gtzc_tzic_it_status_t HAL_GTZC_TZIC_IsEnabledIT(hal_gtzc_tzic_periph_t periph);
/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group10 TZIC illegal access interrupt functions
  * @{
  */
void HAL_GTZC_TZIC_IRQHandler(void);
void HAL_GTZC_TZIC_Callback(hal_gtzc_tzic_periph_t periph);
/**
  * @}
  */

#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @}
  */

/**
  * @}
  */

#endif /* GTZC1_TZSC1_PERIPH */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G5XX_HAL_GTZC_H */
