/**
  **********************************************************************************************************************
  * @file   stm32g5xx_ll_gtzc.h
  * @brief  Header file of GTZC LL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32G5XX_LL_GTZC_H
#define STM32G5XX_LL_GTZC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5XX_LL_Driver
  * @{
  */

#if defined(GTZC1_TZSC1_PERIPH)

/** @addtogroup GTZC_LL GTZC
  * @{
  */
/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_Private_Constants GTZC maximum register field
  * @{
  */
#define LL_GTZC_REG_MAX_FIELD         32U                    /*!< GTZC maximum register field */
#define LL_GTZC_PERIPH_BIT_POSITION   0x1FU                  /*!< GTZC Bitmask to obtain bit position */
/**
  * @}
  */
/* Private macros ----------------------------------------------------------------------------------------------------*/
/* Exported macros ---------------------------------------------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------------------------------------------*/
/* Exported variables ------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_LL_Exported_Constants GTZC LL Exported Constants
  * @{
  */

/** @defgroup GTZC_LL_EC_RegisterSelection Register Selection
  * @{
  */
#define LL_GTZC_PERIPH_REG1   00U                      /*!< GTZC peripherals register 1 */
#define LL_GTZC_PERIPH_REG2   32U                      /*!< GTZC peripherals register 2 */
#define LL_GTZC_PERIPH_REG3   64U                      /*!< GTZC peripherals register 3 */
#define LL_GTZC_PERIPH_REG4   96U                      /*!< GTZC peripherals register 4 */

/**
  * @}
  */

/** @defgroup GTZC_LL_EC_PeripheralSelection Peripheral Selection
  * @{
  */

/**
  * @brief GTZC (TZIC/SEC/PRIV/LOCK) peripheral selection GP1
  */
#define LL_GTZC_TIM2         (GTZC_CFGR1_TIM2_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM2    */
#if defined(TIM3)
#define LL_GTZC_TIM3         (GTZC_CFGR1_TIM3_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM3    */
#endif /* TIM3 */
#if defined(TIM4)
#define LL_GTZC_TIM4         (GTZC_CFGR1_TIM4_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM4    */
#endif /* TIM4 */
#if defined(TIM5)
#define LL_GTZC_TIM5         (GTZC_CFGR1_TIM5_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM5    */
#endif /* TIM5 */
#define LL_GTZC_TIM6         (GTZC_CFGR1_TIM6_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM6    */
#define LL_GTZC_TIM7         (GTZC_CFGR1_TIM7_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM7    */
#define LL_GTZC_TIM12        (GTZC_CFGR1_TIM12_Pos  + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM12   */
#define LL_GTZC_TIM13        (GTZC_CFGR1_TIM13_Pos  + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM13   */
#define LL_GTZC_TIM14        (GTZC_CFGR1_TIM14_Pos  + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM14   */
#define LL_GTZC_WWDG         (GTZC_CFGR1_WWDG_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral WWDG    */
#define LL_GTZC_IWDG         (GTZC_CFGR1_IWDG_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral IWDG    */
#define LL_GTZC_SPI2         (GTZC_CFGR1_SPI2_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral SPI2    */
#if defined(SPI3)
#define LL_GTZC_SPI3         (GTZC_CFGR1_SPI3_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral SPI3    */
#endif /* SPI3 */
#define LL_GTZC_USART2       (GTZC_CFGR1_USART2_Pos + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral USART2  */
#if defined(USART3)
#define LL_GTZC_USART3       (GTZC_CFGR1_USART3_Pos + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral USART3  */
#endif /* USART3 */
#define LL_GTZC_UART4        (GTZC_CFGR1_UART4_Pos  + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral UART4   */
#define LL_GTZC_UART5        (GTZC_CFGR1_UART5_Pos  + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral UART5   */
#define LL_GTZC_I2C1         (GTZC_CFGR1_I2C1_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral I2C1    */
#define LL_GTZC_I2C2         (GTZC_CFGR1_I2C2_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral I2C2    */
#define LL_GTZC_I3C1         (GTZC_CFGR1_I3C1_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral I3C1    */
#if defined(CRS)
#define LL_GTZC_CRS          (GTZC_CFGR1_CRS_Pos    + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral CRS     */
#endif /* CRS */
#if defined(UART6)
#define LL_GTZC_UART6        (GTZC_CFGR1_UART6_Pos  + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral UART6   */
#endif /* UART6 */
#define LL_GTZC_DAC1         (GTZC_CFGR1_DAC1_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral DAC1    */
#define LL_GTZC_DAC2         (GTZC_CFGR1_DAC2_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral DAC2    */
#define LL_GTZC_TIM9         (GTZC_CFGR1_TIM9_Pos   + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM9    */
#define LL_GTZC_TIM10        (GTZC_CFGR1_TIM10_Pos  + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM10   */
#define LL_GTZC_TIM11        (GTZC_CFGR1_TIM11_Pos  + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral TIM11   */
#define LL_GTZC_DTS          (GTZC_CFGR1_DTS_Pos    + LL_GTZC_PERIPH_REG1)  /*!< LL GTZC1 CFGR1 peripheral DTS     */
#if defined(TIM3)
#define LL_GTZC_GRP1_ALL     0x5F3FFFFFU            /*!< LL GTZC1 CFGR1 ALL peripherals    */
#else
#define LL_GTZC_GRP1_ALL     0x5F2FAFF1U            /*!< LL GTZC1 CFGR1 ALL peripherals    */
#endif /* TIM3 */

/**
  * @brief GTZC (TZIC/SEC/PRIV/LOCK) peripheral selection GP2
  */
#define LL_GTZC_FDCAN1       (GTZC_CFGR2_FDCAN1_Pos  + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral FDCAN1  */
#if defined(FDCAN2)
#define LL_GTZC_FDCAN2       (GTZC_CFGR2_FDCAN2_Pos  + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral FDCAN2  */
#endif /* FDCAN2 */
#if defined(FDCAN3)
#define LL_GTZC_FDCAN3       (GTZC_CFGR2_FDCAN3_Pos  + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral FDCAN3  */
#endif /* FDCAN3 */
#if defined(UCPD1)
#define LL_GTZC_UCPD1        (GTZC_CFGR2_UCPD1_Pos   + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral UCPD1   */
#endif /* UCPD1 */
#define LL_GTZC_TIM1         (GTZC_CFGR2_TIM1_Pos    + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral TIM1    */
#define LL_GTZC_SPI1         (GTZC_CFGR2_SPI1_Pos    + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral SPI1    */
#define LL_GTZC_TIM8         (GTZC_CFGR2_TIM8_Pos    + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral TIM8    */
#define LL_GTZC_USART1       (GTZC_CFGR2_USART1_Pos  + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral USART1  */
#define LL_GTZC_TIM15        (GTZC_CFGR2_TIM15_Pos   + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral TIM15   */
#define LL_GTZC_TIM16        (GTZC_CFGR2_TIM16_Pos   + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral TIM16   */
#define LL_GTZC_TIM17        (GTZC_CFGR2_TIM17_Pos   + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral TIM17   */
#if defined(HRTIM1)
#define LL_GTZC_HRTIM1       (GTZC_CFGR2_HRTIM1_Pos  + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral HRTIM1  */
#endif /* HRTIM1 */
#if defined(USB)
#define LL_GTZC_USB          (GTZC_CFGR2_USB_Pos     + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral USB     */
#endif /* USB */
#if defined(TIM20)
#define LL_GTZC_TIM20        (GTZC_CFGR2_TIM20_Pos   + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral TIM20   */
#endif /* TIM20 */
#if defined(OPAMP1)
#define LL_GTZC_OPAMP1       (GTZC_CFGR2_OPAMP1_Pos  + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral OPAMP1  */
#endif /* OPAMP1 */
#if defined(OPAMP2)
#define LL_GTZC_OPAMP2       (GTZC_CFGR2_OPAMP2_Pos  + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral OPAMP2  */
#endif /* OPAMP2 */
#if defined(OPAMP3)
#define LL_GTZC_OPAMP3       (GTZC_CFGR2_OPAMP3_Pos  + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral OPAMP3  */
#endif /* OPAMP3 */
#define LL_GTZC_TIM26        (GTZC_CFGR2_TIM26_Pos   + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral TIM26   */
#define LL_GTZC_LPUART1      (GTZC_CFGR2_LPUART1_Pos + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral LPUART1 */
#if defined(I2C3)
#define LL_GTZC_I2C3         (GTZC_CFGR2_I2C3_Pos    + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral I2C3    */
#endif /* I2C3 */
#if defined(I2C4)
#define LL_GTZC_I2C4         (GTZC_CFGR2_I2C4_Pos    + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral I2C4    */
#endif /* I2C4 */
#define LL_GTZC_LPTIM1       (GTZC_CFGR2_LPTIM1_Pos  + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral LPTIM1  */
#define LL_GTZC_COMP1        (GTZC_CFGR2_COMP1_Pos   + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral COMP1   */
#define LL_GTZC_COMP2        (GTZC_CFGR2_COMP2_Pos   + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral COMP2   */
#define LL_GTZC_COMP3        (GTZC_CFGR2_COMP3_Pos   + LL_GTZC_PERIPH_REG2) /*!< LL GTZC1 CFGR2 peripheral COMP3   */
#if defined(FDCAN2)
#if defined(HRTIM1)
#define LL_GTZC_GRP2_ALL     0xFFFC7F0FU            /*!< LL GTZC1 CFGR2 ALL peripherals    */
#else
#define LL_GTZC_GRP2_ALL     0xFFF87F0FU            /*!< LL GTZC1 CFGR2 ALL peripherals    */
#endif /* HRTIM1 */
#else
#if defined(HRTIM1)
#define LL_GTZC_GRP2_ALL     0xF3E47F01U            /*!< LL GTZC1 CFGR2 ALL peripherals    */
#else
#define LL_GTZC_GRP2_ALL     0xF3E07F01U            /*!< LL GTZC1 CFGR2 ALL peripherals    */
#endif /* HRTIM1 */
#endif /* FDCAN2 */

/**
  * @brief GTZC (TZIC/SEC/PRIV/LOCK) peripheral selection GP3
  */
#define LL_GTZC_COMP4        (GTZC_CFGR3_COMP4_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral COMP4   */
#define LL_GTZC_COMP5        (GTZC_CFGR3_COMP5_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral COMP5   */
#define LL_GTZC_COMP6        (GTZC_CFGR3_COMP6_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral COMP6   */
#define LL_GTZC_COMP7        (GTZC_CFGR3_COMP7_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral COMP7   */
#define LL_GTZC_COMP8        (GTZC_CFGR3_COMP8_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral COMP8   */
#define LL_GTZC_VREFBUF      (GTZC_CFGR3_VREFBUF_Pos + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral VREFBUF */
#define LL_GTZC_TIM27        (GTZC_CFGR3_TIM27_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral TIM27   */
#if defined(POSENC1)
#define LL_GTZC_POSENC1      (GTZC_CFGR3_POSENC1_Pos + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral POSENC1 */
#endif /* POSENC1 */
#if defined(POSENC2)
#define LL_GTZC_POSENC2      (GTZC_CFGR3_POSENC2_Pos + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral POSENC2 */
#endif /* POSENC2 */
#define LL_GTZC_CRC          (GTZC_CFGR3_CRC_Pos     + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral CRC     */
#define LL_GTZC_CORDIC1      (GTZC_CFGR3_CORDIC1_Pos + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral CORDIC1 */
#define LL_GTZC_FMAC1        (GTZC_CFGR3_FMAC1_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral FMAC1   */
#if defined(FMAC2)
#define LL_GTZC_FMAC2        (GTZC_CFGR3_FMAC2_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral FMAC2   */
#endif /* FMAC2 */
#define LL_GTZC_ICACHE       (GTZC_CFGR3_ICACHE_Pos  + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral ICACHE  */
#if defined(DCACHE)
#define LL_GTZC_DCACHE       (GTZC_CFGR3_DCACHE_Pos  + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral DCACHE  */
#endif /* DCACHE */
#define LL_GTZC_ADC12        (GTZC_CFGR3_ADC12_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral ADC12   */
#if defined(ADC3)
#define LL_GTZC_ADC3         (GTZC_CFGR3_ADC3_Pos    + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral ADC3    */
#endif /* ADC3 */
#if defined(AES)
#define LL_GTZC_AES          (GTZC_CFGR3_AES_Pos     + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral AES     */
#endif /* AES */
#define LL_GTZC_HASH         (GTZC_CFGR3_HASH_Pos    + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral HASH    */
#define LL_GTZC_RNG          (GTZC_CFGR3_RNG_Pos     + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral RNG     */
#if defined(SAES)
#define LL_GTZC_SAES         (GTZC_CFGR3_SAES_Pos    + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral SAES    */
#endif /* SAES */
#define LL_GTZC_PKA          (GTZC_CFGR3_PKA_Pos     + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral PKA     */
#define LL_GTZC_DAC5         (GTZC_CFGR3_DAC5_Pos    + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral DAC5    */
#define LL_GTZC_DAC6         (GTZC_CFGR3_DAC6_Pos    + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral DAC6    */
#define LL_GTZC_DAC7         (GTZC_CFGR3_DAC7_Pos    + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral DAC7    */
#if defined(XSPI1)
#define LL_GTZC_XSPI1        (GTZC_CFGR3_XSPI1_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral XSPI1   */
#endif /* XSPI1 */
#define LL_GTZC_RAMCFG       (GTZC_CFGR3_RAMCFG_Pos  + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral RAMCFG  */
#define LL_GTZC_DAC8         (GTZC_CFGR3_DAC8_Pos    + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral DAC8    */
#define LL_GTZC_DAC9         (GTZC_CFGR3_DAC9_Pos    + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral DAC9    */
#define LL_GTZC_DAC10        (GTZC_CFGR3_DAC10_Pos   + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral DAC10   */
#if defined(CCB)
#define LL_GTZC_CCB          (GTZC_CFGR3_CCB_Pos     + LL_GTZC_PERIPH_REG3) /*!< LL GTZC1 CFGR3 peripheral CCB     */
#endif /* CCB */
#if defined(POSENC1)
#if defined(AES)
#define LL_GTZC_GRP3_ALL     0xFBFFFFFFU            /*!< LL GTZC1 CFGR3 ALL peripherals    */
#else
#define LL_GTZC_GRP3_ALL     0xFBEDFFFFU            /*!< LL GTZC1 CFGR3 ALL peripherals    */
#endif /* AES */
#else
#if defined(AES)
#define LL_GTZC_GRP3_ALL     0xF9FFBE7FU            /*!< LL GTZC1 CFGR3 ALL peripherals    */
#else
#define LL_GTZC_GRP3_ALL     0xF9EDBE7FU            /*!< LL GTZC1 CFGR3 ALL peripherals    */
#endif /* AES */
#endif /* POSENC1 */

/**
  * @brief GTZC (TZIC/SEC/PRIV/LOCK) peripheral selection GP4
  */
#define LL_GTZC_GPDMA1       (GTZC_CFGR4_GPDMA1_Pos     + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral GPDMA1     */
#define LL_GTZC_GPDMA2       (GTZC_CFGR4_GPDMA2_Pos     + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral GPDMA2     */
#define LL_GTZC_FLASH        (GTZC_CFGR4_FLASH_Pos      + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral FLASH      */
#define LL_GTZC_FLASH_REG    (GTZC_CFGR4_FLASH_REG_Pos  + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral FLASH_REG  */
#if defined(OTFDEC1)
#define LL_GTZC_OTFDEC1      (GTZC_CFGR4_OTFDEC1_Pos    + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral OTFDEC1    */
#endif /* OTFDEC1 */
#define LL_GTZC_SBS          (GTZC_CFGR4_SBS_Pos        + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral SBS        */
#define LL_GTZC_RTC          (GTZC_CFGR4_RTC_Pos        + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral RTC        */
#define LL_GTZC_TAMP         (GTZC_CFGR4_TAMP_Pos       + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral TAMP       */
#define LL_GTZC_PWR          (GTZC_CFGR4_PWR_Pos        + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral PWR        */
#define LL_GTZC_RCC          (GTZC_CFGR4_RCC_Pos        + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral RCC        */
#define LL_GTZC_EXTI         (GTZC_CFGR4_EXTI_Pos       + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral EXTI       */
#if defined(PLAY1)
#define LL_GTZC_PLAY1        (GTZC_CFGR4_PLAY1_Pos      + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral PLAY1      */
#endif /* PLAY1 */
#define LL_GTZC_TZSC1        (GTZC_CFGR4_TZSC1_Pos      + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral TZSC1      */
#define LL_GTZC_TZIC1        (GTZC_CFGR4_TZIC1_Pos      + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral TZIC1      */
#if defined(XSPI1)
#define LL_GTZC_XSPI1_MEM    (GTZC_CFGR4_XSPI1_MEM_Pos  + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral XSPI1_MEM  */
#endif /* XSPI1 */
#define LL_GTZC_SRAM1        (GTZC_CFGR4_SRAM1_Pos      + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral SRAM1      */
#define LL_GTZC_MPCBB1_REG   (GTZC_CFGR4_MPCBB1_REG_Pos + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral MPCBB1_REG */
#define LL_GTZC_SRAM2        (GTZC_CFGR4_SRAM2_Pos      + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral SRAM2      */
#define LL_GTZC_MPCBB2_REG   (GTZC_CFGR4_MPCBB2_REG_Pos + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral MPCBB2_REG */
#if defined(SRAM3_BASE)
#define LL_GTZC_SRAM3        (GTZC_CFGR4_SRAM3_Pos      + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral SRAM3      */
#define LL_GTZC_MPCBB3_REG   (GTZC_CFGR4_MPCBB3_REG_Pos + LL_GTZC_PERIPH_REG4) /*!< LL GTZC1 CFGR4 peripheral MPCBB3_REG */
#endif /* SRAM3_BASE */
#if defined(OTFDEC1)
#define LL_GTZC_GRP4_ALL     0x3F071FDFU            /*!< LL GTZC1 CFGR4 ALL peripherals    */
#else
#define LL_GTZC_GRP4_ALL     0x0F030FCFU            /*!< LL GTZC1 CFGR4 ALL peripherals    */
#endif /* OTFDEC1 */

/** @defgroup GTZC_LL_EC_TZSC_MPCWMMemorySelection GTZC TZSC_MPCWM Memory Selection
  * @{
  */
#define LL_GTZC_TZSC_MPCWM_XSPI1    (uint32_t)GTZC1_TZSC1_MPCWM1_BASE /*!< GTZC water mark FMC_NOR memory     */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_MPCBBMemorySelection GTZC MPCBB Memory Selection
  * @{
  */
#define LL_GTZC_MPCBB_SRAM1      ((uint32_t)GTZC1_MPCBB1_BASE)      /*!< LL GTZC MPCBB SRAM1 memory      */
#define LL_GTZC_MPCBB_SRAM2      ((uint32_t)GTZC1_MPCBB2_BASE)      /*!< LL GTZC MPCBB SRAM2 memory      */
#if defined(SRAM3_BASE)
#define LL_GTZC_MPCBB_SRAM3      ((uint32_t)GTZC1_MPCBB3_BASE)      /*!< LL GTZC MPCBB SRAM3 memory      */
#endif /* SRAM3_BASE */
/**
  * @}
  */

/**
  * @}
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/** @defgroup GTZC_LL_EC_TZSC_MPCWMSubRegionSelection TZSC_MPCWM Subregion Selection
  * @{
  */
#define LL_GTZC_TZSC_MPCWM_SUBREGION_A 0U /*!< LL GTZC TZSC_MPCWM subregion A */
#define LL_GTZC_TZSC_MPCWM_SUBREGION_B 1U /*!< LL GTZC TZSC_MPCWM subregion B */
/**
  * @}
  */

#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
/** @defgroup GTZC_LL_EC_PrivilegeAttributesSelection Privilege Attributes Selection
  * @{
  */
#define LL_GTZC_ATTR_NPRIV 0U /*!< LL GTZC Attribute non-privilege */
#define LL_GTZC_ATTR_PRIV  1U /*!< LL GTZC Attribute privilege     */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_SecurityAttributesSelection Security Attributes Selection
  * @{
  */
#define LL_GTZC_ATTR_NSEC 0U /*!< LL GTZC Attribute non-secure    */
#define LL_GTZC_ATTR_SEC  1U /*!< LL GTZC Attribute secure        */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_ClockSecurityInversion Clock Security Inversion
  * @{
  */
#define LL_GTZC_MPCBB_CLK_SEC_NOT_INVERTED 0U /*!< LL GTZC MPCBB Clock security not inverted */
#define LL_GTZC_MPCBB_CLK_SEC_INVERTED     1U /*!< LL GTZC MPCBB Clock security inverted     */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_MPCBB_Super_Block_Selection MPCBB Super Block Lock Selection
  * @{
  */
#define LL_GTZC_MPCBB_SUPERBLOCK_0   GTZC_MPCBB_CFGLOCKR1_SPLCK0_Pos  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 0  */
#define LL_GTZC_MPCBB_SUPERBLOCK_1   GTZC_MPCBB_CFGLOCKR1_SPLCK1_Pos  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 1  */
#define LL_GTZC_MPCBB_SUPERBLOCK_2   GTZC_MPCBB_CFGLOCKR1_SPLCK2_Pos  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 2  */
#define LL_GTZC_MPCBB_SUPERBLOCK_3   GTZC_MPCBB_CFGLOCKR1_SPLCK3_Pos  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 3  */
#if defined (SRAM3_BASE)
#define LL_GTZC_MPCBB_SUPERBLOCK_4   GTZC_MPCBB_CFGLOCKR1_SPLCK4_Pos  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 4  */
#define LL_GTZC_MPCBB_SUPERBLOCK_5   GTZC_MPCBB_CFGLOCKR1_SPLCK5_Pos  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 5  */
#define LL_GTZC_MPCBB_SUPERBLOCK_6   GTZC_MPCBB_CFGLOCKR1_SPLCK6_Pos  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 6  */
#define LL_GTZC_MPCBB_SUPERBLOCK_7   GTZC_MPCBB_CFGLOCKR1_SPLCK7_Pos  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 7  */
#endif /* SRAM3_BASE */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_MPCBB_Super_Block_Lock_Selection MPCBB Super Block Lock Selection
  * @{
  */
#define LL_GTZC_MPCBB_LOCK_SUPERBLOCK_0   GTZC_MPCBB_CFGLOCKR1_SPLCK0_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 0  */
#define LL_GTZC_MPCBB_LOCK_SUPERBLOCK_1   GTZC_MPCBB_CFGLOCKR1_SPLCK1_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 1  */
#define LL_GTZC_MPCBB_LOCK_SUPERBLOCK_2   GTZC_MPCBB_CFGLOCKR1_SPLCK2_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 2  */
#define LL_GTZC_MPCBB_LOCK_SUPERBLOCK_3   GTZC_MPCBB_CFGLOCKR1_SPLCK3_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 3  */
#if defined (SRAM3_BASE)
#define LL_GTZC_MPCBB_LOCK_SUPERBLOCK_4   GTZC_MPCBB_CFGLOCKR1_SPLCK4_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 4  */
#define LL_GTZC_MPCBB_LOCK_SUPERBLOCK_5   GTZC_MPCBB_CFGLOCKR1_SPLCK5_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 5  */
#define LL_GTZC_MPCBB_LOCK_SUPERBLOCK_6   GTZC_MPCBB_CFGLOCKR1_SPLCK6_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 6  */
#define LL_GTZC_MPCBB_LOCK_SUPERBLOCK_7   GTZC_MPCBB_CFGLOCKR1_SPLCK7_Msk  /*!< LL GTZC MPCBB SUPER BLOCK LOCK 7  */
#endif /* SRAM3_BASE */
/**
  * @}
  */

/** @defgroup GTZC_LL_EC_MPCBB_Block_Selection MPCBB Block Selection
  * @{
  */
#define LL_GTZC_MPCBB_BLOCK_0  0x00000001U /*!< LL GTZC MPCBB BLOCK 0  */
#define LL_GTZC_MPCBB_BLOCK_1  0x00000002U /*!< LL GTZC MPCBB BLOCK 1  */
#define LL_GTZC_MPCBB_BLOCK_2  0x00000004U /*!< LL GTZC MPCBB BLOCK 2  */
#define LL_GTZC_MPCBB_BLOCK_3  0x00000008U /*!< LL GTZC MPCBB BLOCK 3  */
#define LL_GTZC_MPCBB_BLOCK_4  0x00000010U /*!< LL GTZC MPCBB BLOCK 4  */
#define LL_GTZC_MPCBB_BLOCK_5  0x00000020U /*!< LL GTZC MPCBB BLOCK 5  */
#define LL_GTZC_MPCBB_BLOCK_6  0x00000040U /*!< LL GTZC MPCBB BLOCK 6  */
#define LL_GTZC_MPCBB_BLOCK_7  0x00000080U /*!< LL GTZC MPCBB BLOCK 7  */
#define LL_GTZC_MPCBB_BLOCK_8  0x00000100U /*!< LL GTZC MPCBB BLOCK 8  */
#define LL_GTZC_MPCBB_BLOCK_9  0x00000200U /*!< LL GTZC MPCBB BLOCK 9  */
#define LL_GTZC_MPCBB_BLOCK_10 0x00000400U /*!< LL GTZC MPCBB BLOCK 10 */
#define LL_GTZC_MPCBB_BLOCK_11 0x00000800U /*!< LL GTZC MPCBB BLOCK 11 */
#define LL_GTZC_MPCBB_BLOCK_12 0x00001000U /*!< LL GTZC MPCBB BLOCK 12 */
#define LL_GTZC_MPCBB_BLOCK_13 0x00002000U /*!< LL GTZC MPCBB BLOCK 13 */
#define LL_GTZC_MPCBB_BLOCK_14 0x00004000U /*!< LL GTZC MPCBB BLOCK 14 */
#define LL_GTZC_MPCBB_BLOCK_15 0x00008000U /*!< LL GTZC MPCBB BLOCK 15 */
#define LL_GTZC_MPCBB_BLOCK_16 0x00010000U /*!< LL GTZC MPCBB BLOCK 16 */
#define LL_GTZC_MPCBB_BLOCK_17 0x00020000U /*!< LL GTZC MPCBB BLOCK 17 */
#define LL_GTZC_MPCBB_BLOCK_18 0x00040000U /*!< LL GTZC MPCBB BLOCK 18 */
#define LL_GTZC_MPCBB_BLOCK_19 0x00080000U /*!< LL GTZC MPCBB BLOCK 19 */
#define LL_GTZC_MPCBB_BLOCK_20 0x00100000U /*!< LL GTZC MPCBB BLOCK 20 */
#define LL_GTZC_MPCBB_BLOCK_21 0x00200000U /*!< LL GTZC MPCBB BLOCK 21 */
#define LL_GTZC_MPCBB_BLOCK_22 0x00400000U /*!< LL GTZC MPCBB BLOCK 22 */
#define LL_GTZC_MPCBB_BLOCK_23 0x00800000U /*!< LL GTZC MPCBB BLOCK 23 */
#define LL_GTZC_MPCBB_BLOCK_24 0x01000000U /*!< LL GTZC MPCBB BLOCK 24 */
#define LL_GTZC_MPCBB_BLOCK_25 0x02000000U /*!< LL GTZC MPCBB BLOCK 25 */
#define LL_GTZC_MPCBB_BLOCK_26 0x04000000U /*!< LL GTZC MPCBB BLOCK 26 */
#define LL_GTZC_MPCBB_BLOCK_27 0x08000000U /*!< LL GTZC MPCBB BLOCK 27 */
#define LL_GTZC_MPCBB_BLOCK_28 0x10000000U /*!< LL GTZC MPCBB BLOCK 28 */
#define LL_GTZC_MPCBB_BLOCK_29 0x20000000U /*!< LL GTZC MPCBB BLOCK 29 */
#define LL_GTZC_MPCBB_BLOCK_30 0x40000000U /*!< LL GTZC MPCBB BLOCK 30 */
#define LL_GTZC_MPCBB_BLOCK_31 0x80000000U /*!< LL GTZC MPCBB BLOCK 31 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_LL_Exported_Macros GTZC Exported Macros
  * @{
  */

/**
  * @brief  Write a value in GTZC register.
  * @param  instance GTZC Instance.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  */
#define LL_GTZC_WRITE_REG(instance, reg, value) STM32_WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in GTZC register.
  * @param  instance GTZC Instance
  * @param  reg      Register to be read
  * @retval Register value
  */
#define LL_GTZC_READ_REG(instance, reg) STM32_READ_REG((instance)->reg)
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_LL_Exported_Functions GTZC Exported Functions
  * @{
  */

/** @defgroup GTZC_LL_EF_Management GTZC TZSC Management
  * @{
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock of peripheral attributes.
  * @rmtoll
  *  CR           LCK         LL_GTZC_TZSC_LockConfig
  * @param  p_tzsc TZSC Instance
  */
__STATIC_INLINE void LL_GTZC_TZSC_LockConfig(GTZC_TZSC_Periph_TypeDef *p_tzsc)
{
  STM32_SET_BIT(p_tzsc->CR, GTZC_TZSC_CR_LCK_Msk);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if peripheral attributes are locked.
  * @rmtoll
  *  CR           LCK         LL_GTZC_TZSC_IsLockedConfig
  * @param  p_tzsc TZSC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_IsLockedConfig(const GTZC_TZSC_Periph_TypeDef *p_tzsc)
{
  return ((STM32_READ_BIT(p_tzsc->CR, GTZC_TZSC_CR_LCK_Msk) == GTZC_TZSC_CR_LCK_Msk) ? 1UL : 0UL);
}

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set SECCFGRx peripheral security attribute.
  * @rmtoll SECCFGRx           SECxxx         LL_GTZC_TZSC_SetPeriphSecAttr
  * @param  p_tzsc TZSC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TIM2
  * @if TIM3
  *         @arg @ref LL_GTZC_TIM3
  * @endif
  * @if TIM4
  *         @arg @ref LL_GTZC_TIM4
  * @endif
  * @if TIM5
  *         @arg @ref LL_GTZC_TIM5
  * @endif
  *         @arg @ref LL_GTZC_TIM6
  *         @arg @ref LL_GTZC_TIM7
  *         @arg @ref LL_GTZC_TIM12
  *         @arg @ref LL_GTZC_TIM13
  *         @arg @ref LL_GTZC_TIM14
  *         @arg @ref LL_GTZC_WWDG
  *         @arg @ref LL_GTZC_IWDG
  *         @arg @ref LL_GTZC_SPI2
  * @if SPI3
  *         @arg @ref LL_GTZC_SPI3
  * @endif
  *         @arg @ref LL_GTZC_USART2
  * @if USART3
  *         @arg @ref LL_GTZC_USART3
  * @endif
  *         @arg @ref LL_GTZC_UART4
  *         @arg @ref LL_GTZC_UART5
  *         @arg @ref LL_GTZC_I2C1
  *         @arg @ref LL_GTZC_I2C2
  *         @arg @ref LL_GTZC_I3C1
  * @if CRS
  *         @arg @ref LL_GTZC_CRS
  * @endif
  * @if UART6
  *         @arg @ref LL_GTZC_UART6
  * @endif
  *         @arg @ref LL_GTZC_DAC1
  *         @arg @ref LL_GTZC_DAC2
  *         @arg @ref LL_GTZC_TIM9
  *         @arg @ref LL_GTZC_TIM10
  *         @arg @ref LL_GTZC_TIM11
  *         @arg @ref LL_GTZC_DTS
  *         @arg @ref LL_GTZC_FDCAN1
  * @if FDCAN2
  *         @arg @ref LL_GTZC_FDCAN2
  * @endif
  * @if FDCAN3
  *         @arg @ref LL_GTZC_FDCAN3
  * @endif
  * @if UCPD1
  *         @arg @ref LL_GTZC_UCPD1
  * @endif
  *         @arg @ref LL_GTZC_TIM1
  *         @arg @ref LL_GTZC_SPI1
  *         @arg @ref LL_GTZC_TIM8
  *         @arg @ref LL_GTZC_USART1
  *         @arg @ref LL_GTZC_TIM15
  *         @arg @ref LL_GTZC_TIM16
  *         @arg @ref LL_GTZC_TIM17
  * @if HRTIM1
  *         @arg @ref LL_GTZC_HRTIM1
  * @endif
  * @if USB
  *         @arg @ref LL_GTZC_USB
  * @endif
  * @if TIM20
  *         @arg @ref LL_GTZC_TIM20
  * @endif
  * @if OPAMP1
  *         @arg @ref LL_GTZC_OPAMP1
  * @endif
  * @if OPAMP2
  *         @arg @ref LL_GTZC_OPAMP2
  * @endif
  * @if OPAMP3
  *         @arg @ref LL_GTZC_OPAMP3
  * @endif
  *         @arg @ref LL_GTZC_TIM26
  *         @arg @ref LL_GTZC_LPUART1
  * @if I2C3
  *         @arg @ref LL_GTZC_I2C3
  * @endif
  * @if I2C4
  *         @arg @ref LL_GTZC_I2C4
  * @endif
  *         @arg @ref LL_GTZC_LPTIM1
  *         @arg @ref LL_GTZC_COMP1
  *         @arg @ref LL_GTZC_COMP2
  *         @arg @ref LL_GTZC_COMP3
  *         @arg @ref LL_GTZC_COMP4
  *         @arg @ref LL_GTZC_COMP5
  *         @arg @ref LL_GTZC_COMP6
  *         @arg @ref LL_GTZC_COMP7
  *         @arg @ref LL_GTZC_COMP8
  *         @arg @ref LL_GTZC_VREFBUF
  *         @arg @ref LL_GTZC_TIM27
  * @if POSENC1
  *         @arg @ref LL_GTZC_POSENC1
  * @endif
  * @if POSENC2
  *         @arg @ref LL_GTZC_POSENC2
  * @endif
  *         @arg @ref LL_GTZC_CRC
  *         @arg @ref LL_GTZC_CORDIC1
  *         @arg @ref LL_GTZC_FMAC1
  * @if FMAC2
  *         @arg @ref LL_GTZC_FMAC2
  * @endif
  *         @arg @ref LL_GTZC_ICACHE
  * @if DCACHE
  *         @arg @ref LL_GTZC_DCACHE
  * @endif
  *         @arg @ref LL_GTZC_ADC12
  * @if ADC3
  *         @arg @ref LL_GTZC_ADC3
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC_AES
  * @endif
  *         @arg @ref LL_GTZC_HASH
  *         @arg @ref LL_GTZC_RNG
  * @if SAES
  *         @arg @ref LL_GTZC_SAES
  * @endif
  *         @arg @ref LL_GTZC_PKA
  *         @arg @ref LL_GTZC_DAC5
  *         @arg @ref LL_GTZC_DAC6
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1
  * @endif
  *         @arg @ref LL_GTZC_RAMCFG
  *         @arg @ref LL_GTZC_DAC8
  *         @arg @ref LL_GTZC_DAC9
  *         @arg @ref LL_GTZC_DAC10
  * @if CCB
  *         @arg @ref LL_GTZC_CCB
  * @endif
  *
  * @param  sec_attr This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_NSEC
  *         @arg @ref LL_GTZC_ATTR_SEC
  */
__STATIC_INLINE void LL_GTZC_TZSC_SetPeriphSecAttr(GTZC_TZSC_Periph_TypeDef *p_tzsc,
                                                   uint32_t periph,
                                                   uint32_t sec_attr)
{
  STM32_MODIFY_REG(p_tzsc->SECCFGR[periph / LL_GTZC_REG_MAX_FIELD], (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD)),
                   (sec_attr * (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD))));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get SECCFGRx peripheral security attribute.
  * @rmtoll SECCFGRx           SECxxx         LL_GTZC_TZSC_GetPeriphSecAttr
  * @param  p_tzsc TZSC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TIM2
  * @if TIM3
  *         @arg @ref LL_GTZC_TIM3
  * @endif
  * @if TIM4
  *         @arg @ref LL_GTZC_TIM4
  * @endif
  * @if TIM5
  *         @arg @ref LL_GTZC_TIM5
  * @endif
  *         @arg @ref LL_GTZC_TIM6
  *         @arg @ref LL_GTZC_TIM7
  *         @arg @ref LL_GTZC_TIM12
  *         @arg @ref LL_GTZC_TIM13
  *         @arg @ref LL_GTZC_TIM14
  *         @arg @ref LL_GTZC_WWDG
  *         @arg @ref LL_GTZC_IWDG
  *         @arg @ref LL_GTZC_SPI2
  * @if SPI3
  *         @arg @ref LL_GTZC_SPI3
  * @endif
  *         @arg @ref LL_GTZC_USART2
  * @if USART3
  *         @arg @ref LL_GTZC_USART3
  * @endif
  *         @arg @ref LL_GTZC_UART4
  *         @arg @ref LL_GTZC_UART5
  *         @arg @ref LL_GTZC_I2C1
  *         @arg @ref LL_GTZC_I2C2
  *         @arg @ref LL_GTZC_I3C1
  * @if CRS
  *         @arg @ref LL_GTZC_CRS
  * @endif
  * @if UART6
  *         @arg @ref LL_GTZC_UART6
  * @endif
  *         @arg @ref LL_GTZC_DAC1
  *         @arg @ref LL_GTZC_DAC2
  *         @arg @ref LL_GTZC_TIM9
  *         @arg @ref LL_GTZC_TIM10
  *         @arg @ref LL_GTZC_TIM11
  *         @arg @ref LL_GTZC_DTS
  *         @arg @ref LL_GTZC_FDCAN1
  * @if FDCAN2
  *         @arg @ref LL_GTZC_FDCAN2
  * @endif
  * @if FDCAN3
  *         @arg @ref LL_GTZC_FDCAN3
  * @endif
  * @if UCPD1
  *         @arg @ref LL_GTZC_UCPD1
  * @endif
  *         @arg @ref LL_GTZC_TIM1
  *         @arg @ref LL_GTZC_SPI1
  *         @arg @ref LL_GTZC_TIM8
  *         @arg @ref LL_GTZC_USART1
  *         @arg @ref LL_GTZC_TIM15
  *         @arg @ref LL_GTZC_TIM16
  *         @arg @ref LL_GTZC_TIM17
  * @if HRTIM1
  *         @arg @ref LL_GTZC_HRTIM1
  * @endif
  * @if USB
  *         @arg @ref LL_GTZC_USB
  * @endif
  * @if TIM20
  *         @arg @ref LL_GTZC_TIM20
  * @endif
  * @if OPAMP1
  *         @arg @ref LL_GTZC_OPAMP1
  * @endif
  * @if OPAMP2
  *         @arg @ref LL_GTZC_OPAMP2
  * @endif
  * @if OPAMP3
  *         @arg @ref LL_GTZC_OPAMP3
  * @endif
  *         @arg @ref LL_GTZC_TIM26
  *         @arg @ref LL_GTZC_LPUART1
  * @if I2C3
  *         @arg @ref LL_GTZC_I2C3
  * @endif
  * @if I2C4
  *         @arg @ref LL_GTZC_I2C4
  * @endif
  *         @arg @ref LL_GTZC_LPTIM1
  *         @arg @ref LL_GTZC_COMP1
  *         @arg @ref LL_GTZC_COMP2
  *         @arg @ref LL_GTZC_COMP3
  *         @arg @ref LL_GTZC_COMP4
  *         @arg @ref LL_GTZC_COMP5
  *         @arg @ref LL_GTZC_COMP6
  *         @arg @ref LL_GTZC_COMP7
  *         @arg @ref LL_GTZC_COMP8
  *         @arg @ref LL_GTZC_VREFBUF
  *         @arg @ref LL_GTZC_TIM27
  * @if POSENC1
  *         @arg @ref LL_GTZC_POSENC1
  * @endif
  * @if POSENC2
  *         @arg @ref LL_GTZC_POSENC2
  * @endif
  *         @arg @ref LL_GTZC_CRC
  *         @arg @ref LL_GTZC_CORDIC1
  *         @arg @ref LL_GTZC_FMAC1
  * @if FMAC2
  *         @arg @ref LL_GTZC_FMAC2
  * @endif
  *         @arg @ref LL_GTZC_ICACHE
  * @if DCACHE
  *         @arg @ref LL_GTZC_DCACHE
  * @endif
  *         @arg @ref LL_GTZC_ADC12
  * @if ADC3
  *         @arg @ref LL_GTZC_ADC3
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC_AES
  * @endif
  *         @arg @ref LL_GTZC_HASH
  *         @arg @ref LL_GTZC_RNG
  * @if SAES
  *         @arg @ref LL_GTZC_SAES
  * @endif
  *         @arg @ref LL_GTZC_PKA
  *         @arg @ref LL_GTZC_DAC5
  *         @arg @ref LL_GTZC_DAC6
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1
  * @endif
  *         @arg @ref LL_GTZC_RAMCFG
  *         @arg @ref LL_GTZC_DAC8
  *         @arg @ref LL_GTZC_DAC9
  *         @arg @ref LL_GTZC_DAC10
  * @if CCB
  *         @arg @ref LL_GTZC_CCB
  * @endif
  *
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_NSEC
  *         @arg @ref LL_GTZC_ATTR_SEC
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_GetPeriphSecAttr(const GTZC_TZSC_Periph_TypeDef *p_tzsc,
                                                       uint32_t periph)
{
  uint32_t periph_msk;

  periph_msk = (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD));

  return ((STM32_READ_BIT(p_tzsc->SECCFGR[periph / LL_GTZC_REG_MAX_FIELD], periph_msk) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Set PRIVCFGRx peripheral privilege attribute.
  * @rmtoll PRIVCFGRx           PRIVxxx         LL_GTZC_TZSC_SetPeriphPrivAttr
  * @param  p_tzsc TZSC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TIM2
  * @if TIM3
  *         @arg @ref LL_GTZC_TIM3
  * @endif
  * @if TIM4
  *         @arg @ref LL_GTZC_TIM4
  * @endif
  * @if TIM5
  *         @arg @ref LL_GTZC_TIM5
  * @endif
  *         @arg @ref LL_GTZC_TIM6
  *         @arg @ref LL_GTZC_TIM7
  *         @arg @ref LL_GTZC_TIM12
  *         @arg @ref LL_GTZC_TIM13
  *         @arg @ref LL_GTZC_TIM14
  *         @arg @ref LL_GTZC_WWDG
  *         @arg @ref LL_GTZC_IWDG
  *         @arg @ref LL_GTZC_SPI2
  * @if SPI3
  *         @arg @ref LL_GTZC_SPI3
  * @endif
  *         @arg @ref LL_GTZC_USART2
  * @if USART3
  *         @arg @ref LL_GTZC_USART3
  * @endif
  *         @arg @ref LL_GTZC_UART4
  *         @arg @ref LL_GTZC_UART5
  *         @arg @ref LL_GTZC_I2C1
  *         @arg @ref LL_GTZC_I2C2
  *         @arg @ref LL_GTZC_I3C1
  * @if CRS
  *         @arg @ref LL_GTZC_CRS
  * @endif
  * @if UART6
  *         @arg @ref LL_GTZC_UART6
  * @endif
  *         @arg @ref LL_GTZC_DAC1
  *         @arg @ref LL_GTZC_DAC2
  *         @arg @ref LL_GTZC_TIM9
  *         @arg @ref LL_GTZC_TIM10
  *         @arg @ref LL_GTZC_TIM11
  *         @arg @ref LL_GTZC_DTS
  *         @arg @ref LL_GTZC_FDCAN1
  * @if FDCAN2
  *         @arg @ref LL_GTZC_FDCAN2
  * @endif
  * @if FDCAN3
  *         @arg @ref LL_GTZC_FDCAN3
  * @endif
  * @if UCPD1
  *         @arg @ref LL_GTZC_UCPD1
  * @endif
  *         @arg @ref LL_GTZC_TIM1
  *         @arg @ref LL_GTZC_SPI1
  *         @arg @ref LL_GTZC_TIM8
  *         @arg @ref LL_GTZC_USART1
  *         @arg @ref LL_GTZC_TIM15
  *         @arg @ref LL_GTZC_TIM16
  *         @arg @ref LL_GTZC_TIM17
  * @if HRTIM1
  *         @arg @ref LL_GTZC_HRTIM1
  * @endif
  * @if USB
  *         @arg @ref LL_GTZC_USB
  * @endif
  * @if TIM20
  *         @arg @ref LL_GTZC_TIM20
  * @endif
  * @if OPAMP1
  *         @arg @ref LL_GTZC_OPAMP1
  * @endif
  * @if OPAMP2
  *         @arg @ref LL_GTZC_OPAMP2
  * @endif
  * @if OPAMP3
  *         @arg @ref LL_GTZC_OPAMP3
  * @endif
  *         @arg @ref LL_GTZC_TIM26
  *         @arg @ref LL_GTZC_LPUART1
  * @if I2C3
  *         @arg @ref LL_GTZC_I2C3
  * @endif
  * @if I2C4
  *         @arg @ref LL_GTZC_I2C4
  * @endif
  *         @arg @ref LL_GTZC_LPTIM1
  *         @arg @ref LL_GTZC_COMP1
  *         @arg @ref LL_GTZC_COMP2
  *         @arg @ref LL_GTZC_COMP3
  *         @arg @ref LL_GTZC_COMP4
  *         @arg @ref LL_GTZC_COMP5
  *         @arg @ref LL_GTZC_COMP6
  *         @arg @ref LL_GTZC_COMP7
  *         @arg @ref LL_GTZC_COMP8
  *         @arg @ref LL_GTZC_VREFBUF
  *         @arg @ref LL_GTZC_TIM27
  * @if POSENC1
  *         @arg @ref LL_GTZC_POSENC1
  * @endif
  * @if POSENC2
  *         @arg @ref LL_GTZC_POSENC2
  * @endif
  *         @arg @ref LL_GTZC_CRC
  *         @arg @ref LL_GTZC_CORDIC1
  *         @arg @ref LL_GTZC_FMAC1
  * @if FMAC2
  *         @arg @ref LL_GTZC_FMAC2
  * @endif
  *         @arg @ref LL_GTZC_ICACHE
  * @if DCACHE
  *         @arg @ref LL_GTZC_DCACHE
  * @endif
  *         @arg @ref LL_GTZC_ADC12
  * @if ADC3
  *         @arg @ref LL_GTZC_ADC3
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC_AES
  * @endif
  *         @arg @ref LL_GTZC_HASH
  *         @arg @ref LL_GTZC_RNG
  * @if SAES
  *         @arg @ref LL_GTZC_SAES
  * @endif
  *         @arg @ref LL_GTZC_PKA
  *         @arg @ref LL_GTZC_DAC5
  *         @arg @ref LL_GTZC_DAC6
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1
  * @endif
  *         @arg @ref LL_GTZC_RAMCFG
  *         @arg @ref LL_GTZC_DAC8
  *         @arg @ref LL_GTZC_DAC9
  *         @arg @ref LL_GTZC_DAC10
  * @if CCB
  *         @arg @ref LL_GTZC_CCB
  * @endif
  *
  * @param  priv_attr This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  *         @arg @ref LL_GTZC_ATTR_PRIV
  */
__STATIC_INLINE void LL_GTZC_TZSC_SetPeriphPrivAttr(GTZC_TZSC_Periph_TypeDef *p_tzsc,
                                                    uint32_t periph,
                                                    uint32_t priv_attr)
{
  STM32_MODIFY_REG(p_tzsc->PRIVCFGR[periph / LL_GTZC_REG_MAX_FIELD], (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD)),
                   (priv_attr * (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD))));
}

/**
  * @brief  Get PRIVCFGRx peripheral privilege attribute.
  * @rmtoll PRIVCFGRx           PRIVxxx         LL_GTZC_TZSC_GetPeriphPrivAttr
  * @param  p_tzsc TZSC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TIM2
  * @if TIM3
  *         @arg @ref LL_GTZC_TIM3
  * @endif
  * @if TIM4
  *         @arg @ref LL_GTZC_TIM4
  * @endif
  * @if TIM5
  *         @arg @ref LL_GTZC_TIM5
  * @endif
  *         @arg @ref LL_GTZC_TIM6
  *         @arg @ref LL_GTZC_TIM7
  *         @arg @ref LL_GTZC_TIM12
  *         @arg @ref LL_GTZC_TIM13
  *         @arg @ref LL_GTZC_TIM14
  *         @arg @ref LL_GTZC_WWDG
  *         @arg @ref LL_GTZC_IWDG
  *         @arg @ref LL_GTZC_SPI2
  * @if SPI3
  *         @arg @ref LL_GTZC_SPI3
  * @endif
  *         @arg @ref LL_GTZC_USART2
  * @if USART3
  *         @arg @ref LL_GTZC_USART3
  * @endif
  *         @arg @ref LL_GTZC_UART4
  *         @arg @ref LL_GTZC_UART5
  *         @arg @ref LL_GTZC_I2C1
  *         @arg @ref LL_GTZC_I2C2
  *         @arg @ref LL_GTZC_I3C1
  * @if CRS
  *         @arg @ref LL_GTZC_CRS
  * @endif
  * @if UART6
  *         @arg @ref LL_GTZC_UART6
  * @endif
  *         @arg @ref LL_GTZC_DAC1
  *         @arg @ref LL_GTZC_DAC2
  *         @arg @ref LL_GTZC_TIM9
  *         @arg @ref LL_GTZC_TIM10
  *         @arg @ref LL_GTZC_TIM11
  *         @arg @ref LL_GTZC_DTS
  *         @arg @ref LL_GTZC_FDCAN1
  * @if FDCAN2
  *         @arg @ref LL_GTZC_FDCAN2
  * @endif
  * @if FDCAN3
  *         @arg @ref LL_GTZC_FDCAN3
  * @endif
  * @if UCPD1
  *         @arg @ref LL_GTZC_UCPD1
  * @endif
  *         @arg @ref LL_GTZC_TIM1
  *         @arg @ref LL_GTZC_SPI1
  *         @arg @ref LL_GTZC_TIM8
  *         @arg @ref LL_GTZC_USART1
  *         @arg @ref LL_GTZC_TIM15
  *         @arg @ref LL_GTZC_TIM16
  *         @arg @ref LL_GTZC_TIM17
  * @if HRTIM1
  *         @arg @ref LL_GTZC_HRTIM1
  * @endif
  * @if USB
  *         @arg @ref LL_GTZC_USB
  * @endif
  * @if TIM20
  *         @arg @ref LL_GTZC_TIM20
  * @endif
  * @if OPAMP1
  *         @arg @ref LL_GTZC_OPAMP1
  * @endif
  * @if OPAMP2
  *         @arg @ref LL_GTZC_OPAMP2
  * @endif
  * @if OPAMP3
  *         @arg @ref LL_GTZC_OPAMP3
  * @endif
  *         @arg @ref LL_GTZC_TIM26
  *         @arg @ref LL_GTZC_LPUART1
  * @if I2C3
  *         @arg @ref LL_GTZC_I2C3
  * @endif
  * @if I2C4
  *         @arg @ref LL_GTZC_I2C4
  * @endif
  *         @arg @ref LL_GTZC_LPTIM1
  *         @arg @ref LL_GTZC_COMP1
  *         @arg @ref LL_GTZC_COMP2
  *         @arg @ref LL_GTZC_COMP3
  *         @arg @ref LL_GTZC_COMP4
  *         @arg @ref LL_GTZC_COMP5
  *         @arg @ref LL_GTZC_COMP6
  *         @arg @ref LL_GTZC_COMP7
  *         @arg @ref LL_GTZC_COMP8
  *         @arg @ref LL_GTZC_VREFBUF
  *         @arg @ref LL_GTZC_TIM27
  * @if POSENC1
  *         @arg @ref LL_GTZC_POSENC1
  * @endif
  * @if POSENC2
  *         @arg @ref LL_GTZC_POSENC2
  * @endif
  *         @arg @ref LL_GTZC_CRC
  *         @arg @ref LL_GTZC_CORDIC1
  *         @arg @ref LL_GTZC_FMAC1
  * @if FMAC2
  *         @arg @ref LL_GTZC_FMAC2
  * @endif
  *         @arg @ref LL_GTZC_ICACHE
  * @if DCACHE
  *         @arg @ref LL_GTZC_DCACHE
  * @endif
  *         @arg @ref LL_GTZC_ADC12
  * @if ADC3
  *         @arg @ref LL_GTZC_ADC3
  * @endif
  * @if AES
  *         @arg @ref LL_GTZC_AES
  * @endif
  *         @arg @ref LL_GTZC_HASH
  *         @arg @ref LL_GTZC_RNG
  * @if SAES
  *         @arg @ref LL_GTZC_SAES
  * @endif
  *         @arg @ref LL_GTZC_PKA
  *         @arg @ref LL_GTZC_DAC5
  *         @arg @ref LL_GTZC_DAC6
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1
  * @endif
  *         @arg @ref LL_GTZC_RAMCFG
  *         @arg @ref LL_GTZC_DAC8
  *         @arg @ref LL_GTZC_DAC9
  *         @arg @ref LL_GTZC_DAC10
  * @if CCB
  *         @arg @ref LL_GTZC_CCB
  * @endif
  *
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  *         @arg @ref LL_GTZC_ATTR_PRIV
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_GetPeriphPrivAttr(const GTZC_TZSC_Periph_TypeDef *p_tzsc,
                                                        uint32_t periph)
{
  uint32_t periph_msk;

  periph_msk = (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD));

  return ((STM32_READ_BIT(p_tzsc->PRIVCFGR[periph / LL_GTZC_REG_MAX_FIELD], periph_msk) != 0UL) ? 1UL : 0UL);
}
/**
  * @}
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/** @defgroup GTZC_LL_EF_MPCWM_Management TZSC_MPCWM Management
  * @{
  */

/**
  * @brief  Lock configuration of subregion of TZSC_MPCWM memory.
  * @rmtoll MPCWMxzCFGR (X= 1 to 7) and (Y= A or B)          RLOCK         LL_GTZC_TZSC_MPCWM_LockSubRegion
  * @param  p_mpcwm TZSC_MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_LockSubRegion(GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                      uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxACFGR);
  STM32_SET_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SRLOCK);
}

/**
  * @brief  Check if configuration subregion of TZSC_MPCWM is locked.
  * @rmtoll MPCWMxzCFGR (X= 1 to 7) and (Y= A or B)          RLOCK         LL_GTZC_TZSC_MPCWM_IsLockedSubRegion
  * @param  p_mpcwm TZSC_MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_IsLockedSubRegion(const GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                              uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxACFGR);
  return ((STM32_READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SRLOCK) ==
           GTZC_TZSC_MPCWM_CFGR_SRLOCK) ? 1UL : 0UL);
}

/**
  * @brief  Set secure attribute of TZSC_MPCWM memory subregion.
  * @rmtoll MPCWMxzCFGR (X= 1 to 7) and (Y= A or B)           SEC         LL_GTZC_TZSC_MPCWM_SetSubRegionSecAttr
  * @param  p_mpcwm TZSC_MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param  sec_attr
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_ATTR_SEC
  *         @arg @ref LL_GTZC_ATTR_NSEC
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_SetSubRegionSecAttr(GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                            uint32_t subregion,
                                                            uint32_t sec_attr)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxACFGR);
  STM32_MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SEC, \
                   ((sec_attr * GTZC_TZSC_MPCWM_CFGR_SEC)));
}

/**
  * @brief  Get secure attribute of TZSC_MPCWM memory subregion.
  * @rmtoll MPCWMxzCFGR (X= 1 to 7) and (Y= A or B)          SEC         LL_GTZC_TZSC_MPCWM_GetSubRegionSecAttr
  * @param  p_mpcwm TZSC_MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_SEC
  *         @arg @ref LL_GTZC_ATTR_NSEC
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_GetSubRegionSecAttr(const GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                                uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxACFGR);
  return ((STM32_READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SEC) ==
           GTZC_TZSC_MPCWM_CFGR_SEC) ? 1UL : 0UL);
}

/**
  * @brief  Set privilege attribute of TZSC_MPCWM memory subregion.
  * @rmtoll MPCWMxzCFGR (X= 1 to 7) and (Y= A or B)          PRIV         LL_GTZC_TZSC_MPCWM_SetSubRegionPrivAttr
  * @param  p_mpcwm TZSC_MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param  priv_attr
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_ATTR_PRIV
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_SetSubRegionPrivAttr(GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                             uint32_t subregion,
                                                             uint32_t priv_attr)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxACFGR);
  STM32_MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_PRIV, \
                   ((priv_attr * GTZC_TZSC_MPCWM_CFGR_PRIV)));
}

/**
  * @brief  Get privilege attribute of TZSC_MPCWM memory subregion.
  * @rmtoll MPCWMxzCFGR (X= 1 to 7) and (Y= A or B)           PRIV         LL_GTZC_TZSC_MPCWM_GetSubRegionPrivAttr
  * @param  p_mpcwm TZSC_MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GTZC_ATTR_PRIV
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_GetSubRegionPrivAttr(const GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                                 uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxACFGR);
  return ((STM32_READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_PRIV) ==
           GTZC_TZSC_MPCWM_CFGR_PRIV) ? 1UL : 0UL);
}


/**
  * @brief  Enable a specific TZSC_MPCWM memory subregion.
  * @rmtoll MPCWMxzCFGR (X= 1 to 7) and (Y= A or B)          SREN         LL_GTZC_TZSC_MPCWM_EnableSubRegion
  * @param  p_mpcwm TZSC_MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_EnableSubRegion(GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                        uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxACFGR);
  STM32_SET_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SREN);
}

/**
  * @brief  Disable a specific TZSC_MPCWM memory subregion.
  * @rmtoll MPCWMxzCFGR (X= 1 to 7) and (Y= A or B)          SREN         LL_GTZC_TZSC_MPCWM_DisableSubRegion
  * @param  p_mpcwm TZSC_MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_DisableSubRegion(GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                         uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxACFGR);
  STM32_CLEAR_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SREN);
}


/**
  * @brief  Check if a specific TZSC_MPCWM memory subregion is enabled.
  * @rmtoll MPCWMxzCFGR (X= 1 to 7) and (Y= A or B)           SREN         LL_GTZC_TZSC_MPCWM_IsEnabledWrSubRegion
  * @param  p_mpcwm TZSC_MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion(const GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                               uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxACFGR);
  return ((STM32_READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWM_CFGR_SREN) ==
           GTZC_TZSC_MPCWM_CFGR_SREN) ? 1UL : 0UL);
}

/**
  * @brief  Set area configuration of mpcwm memory subregion.
  * @rmtoll MPCWMxAR           SUBx_START/SUBx_LENGTH        LL_GTZC_TZSC_MPCWM_ConfigSubRegionArea
  * @param  p_mpcwm MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param start  : address in byte divided by granularity
  * @param length : length in byte divided by granularity
  *
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_ConfigSubRegionArea(GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                            uint32_t subregion,
                                                            uint32_t start,
                                                            uint32_t length)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxAR);
  STM32_MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)),
                   (GTZC_TZSC_MPCWMR_SUBZ_START | GTZC_TZSC_MPCWMR_SUBZ_LENGTH), (start | (length << 16U)));
}

/**
  * @brief  Set start of subregion of mpcwm memory.
  * @rmtoll MPCWMxAR           SUBx_START       LL_GTZC_TZSC_MPCWM_SetSubRegionStartAddr
  * @param  p_mpcwm MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param start  : address in byte divided by granularity
  *
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_SetSubRegionStartAddr(GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                              uint32_t subregion,
                                                              uint32_t start)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxAR);
  STM32_MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWMR_SUBZ_START, start);
}

/**
  * @brief  Get start of subregion of mpcwm memory.
  * @rmtoll MPCWMxAR           SUBx_START          LL_GTZC_TZSC_MPCWM_GetSubRegionStartAddr
  * @param  p_mpcwm MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval Returned start value. Multiply by granularity to get start address in byte.
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_GetSubRegionStartAddr(const GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                                  uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxAR);
  return (STM32_READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWMR_SUBZ_START));
}

/**
  * @brief  Set length of subregion of mpcwm memory.
  * @rmtoll MPCWMxAR           SUBx_LENGTH       LL_GTZC_TZSC_MPCWM_SetSubRegionLength
  * @param  p_mpcwm MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @param length  : length in byte divided by granularity
  *
  */
__STATIC_INLINE void LL_GTZC_TZSC_MPCWM_SetSubRegionLength(GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                           uint32_t subregion,
                                                           uint32_t length)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxAR);
  STM32_MODIFY_REG(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWMR_SUBZ_LENGTH, (length << 16U));
}

/**
  * @brief  Get length of subregion of mpcwm memory.
  * @rmtoll MPCWMxAR           SUBx_LENGTH          LL_GTZC_TZSC_MPCWM_GetSubRegionLength
  * @param  p_mpcwm MPCWM Instance
  * @param  subregion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_A
  *         @arg @ref LL_GTZC_TZSC_MPCWM_SUBREGION_B
  * @retval Returned length value. Multiply by granularity to get length in byte.
  */
__STATIC_INLINE uint32_t LL_GTZC_TZSC_MPCWM_GetSubRegionLength(const GTZC_TZSC_MPCWM_TypeDef *p_mpcwm,
                                                               uint32_t subregion)
{
  uint32_t reg_addr = (uint32_t) &(p_mpcwm->MPCWMxAR);
  return (STM32_READ_BIT(*(__IO uint32_t *)(reg_addr + (8U * subregion)), GTZC_TZSC_MPCWMR_SUBZ_LENGTH)) >> 16U;
}

#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
/**
  * @}
  */
/** @defgroup GTZC_LL_EF_MPCBB_Management MPCBB Management
  * @{
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable secure read/write to non-secure access of MPCBB memory.
  * @rmtoll CR            SRWILADIS         LL_GTZC_MPCBB_EnableSecToNSecRdWrAccess
  * @param  p_mpcbb MPCBB Instance
  */
__STATIC_INLINE void LL_GTZC_MPCBB_EnableSecToNSecRdWrAccess(GTZC_MPCBB_TypeDef *p_mpcbb)
{
  STM32_SET_BIT(p_mpcbb->CR, GTZC_MPCBB_CR_SRWILADIS);
}

/**
  * @brief  Disable secure read/write to non-secure access of MPCBB memory.
  * @rmtoll CR           SRWILADIS         LL_GTZC_MPCBB_DisableSecToNSecRdWrAccess
  * @param  p_mpcbb MPCBB Instance
  */
__STATIC_INLINE void LL_GTZC_MPCBB_DisableSecToNSecRdWrAccess(GTZC_MPCBB_TypeDef *p_mpcbb)
{
  STM32_CLEAR_BIT(p_mpcbb->CR, GTZC_MPCBB_CR_SRWILADIS);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the secure read/write to non-secure access of MPCBB memory is enabled or disabled.
  * @rmtoll CR           SRWILADIS         LL_GTZC_MPCBB_IsEnabledSecToNSecRdWrAccess
  * @param  p_mpcbb MPCBB Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_IsEnabledSecToNSecRdWrAccess(const GTZC_MPCBB_TypeDef *p_mpcbb)
{
  return ((STM32_READ_BIT(p_mpcbb->CR, GTZC_MPCBB_CR_SRWILADIS) == GTZC_MPCBB_CR_SRWILADIS) ? 1UL : 0UL);
}

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set clock security state of block based memory.
  * @rmtoll CR           INVSECSTATE        LL_GTZC_MPCBB_SetClockSecurityState
  * @param  p_mpcbb MPCBB Instance
  * @param  clk_sec_invert_state
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_CLK_SEC_NOT_INVERTED
  *         @arg @ref LL_GTZC_MPCBB_CLK_SEC_INVERTED
  */
__STATIC_INLINE void LL_GTZC_MPCBB_SetClockSecurityState(GTZC_MPCBB_TypeDef *p_mpcbb, uint32_t clk_sec_invert_state)
{
  STM32_MODIFY_REG(p_mpcbb->CR, GTZC_MPCBB_CR_INVSECSTATE_Msk, (GTZC_MPCBB_CR_INVSECSTATE_Msk * clk_sec_invert_state));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get clock security state of block based memory.
  * @rmtoll CR           INVSECSTATE         LL_GTZC_MPCBB_GetClockSecurityState
  * @param  p_mpcbb MPCBB Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GTZC_MPCBB_CLK_SEC_NOT_INVERTED
  *         @arg @ref LL_GTZC_MPCBB_CLK_SEC_INVERTED
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_GetClockSecurityState(const GTZC_MPCBB_TypeDef *p_mpcbb)
{
  return (STM32_READ_BIT(p_mpcbb->CR, GTZC_MPCBB_CR_INVSECSTATE_Msk) >> GTZC_MPCBB_CR_INVSECSTATE_Pos);
}

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set security attribute of MPCBB memory blocks within one super-block.
  * @rmtoll PGy_SECCFGR (y= 0 to 31)     SECx (x= 0 to 7)     LL_GTZC_MPCBB_SetBlockSecAttr
  * @param  p_mpcbb MPCBB Instance
  * @param  super_block
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_0
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_1
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_2
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_3
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_4
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_6
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_7
  * @endif
  * @param  block
  *         This parameter can be a combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_0
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_1
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_2
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_3
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_4
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_6
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_7
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_8
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_10
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_11
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_12
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_13
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_14
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_15
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_16
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_17
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_18
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_19
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_20
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_21
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_22
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_23
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_24
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_25
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_26
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_27
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_28
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_29
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_30
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_31
  * @param sec_attr
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_ATTR_SEC
  *         @arg @ref LL_GTZC_ATTR_NSEC
  */
__STATIC_INLINE void LL_GTZC_MPCBB_SetBlockSecAttr(GTZC_MPCBB_TypeDef *p_mpcbb,
                                                   uint32_t super_block,
                                                   uint32_t block,
                                                   uint32_t sec_attr)
{
  STM32_MODIFY_REG(p_mpcbb->SECCFGR[super_block], block, (block * sec_attr));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get security attribute of super_block MPCBB memory.
  * @rmtoll PGy_SECCFGR (x= 0 to 31)     SECx (x= 0 to 7)     LL_GTZC_MPCBB_GetSuperBlockSecAttr
  * @param  p_mpcbb MPCBB Instance
  * @param  super_block
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_0
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_1
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_2
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_3
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_4
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_6
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_7
  * @endif
  * @retval Returned value can be 0x00000000U or a combination of the following values:
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_0
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_1
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_2
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_3
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_4
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_6
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_7
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_8
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_9
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_10
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_11
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_12
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_13
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_14
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_15
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_16
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_17
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_18
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_19
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_20
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_21
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_22
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_23
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_24
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_25
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_26
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_27
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_28
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_29
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_30
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_31
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_GetSuperBlockSecAttr(const GTZC_MPCBB_TypeDef *p_mpcbb,
                                                            uint32_t super_block)
{
  return (STM32_READ_REG(p_mpcbb->SECCFGR[super_block]));
}

/**
  * @brief  Set privilege attribute of MPCBB memory blocks within one super-block.
  * @rmtoll PGy_PRIVCFGR (y= 0 to 31)     PRIVx (x= 0 to 7)     LL_GTZC_MPCBB_SetBlockPrivAttr
  * @param  p_mpcbb MPCBB Instance
  * @param  super_block
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_0
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_1
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_2
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_3
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_4
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_6
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_7
  * @endif
  * @param  block
  *         This parameter can be a combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_0
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_1
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_2
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_3
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_4
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_6
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_7
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_8
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_9
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_10
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_11
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_12
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_13
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_14
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_15
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_16
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_17
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_18
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_19
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_20
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_21
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_22
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_23
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_24
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_25
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_26
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_27
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_28
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_29
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_30
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_31
  * @param  priv_attr
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_ATTR_PRIV
  *         @arg @ref LL_GTZC_ATTR_NPRIV
  */
__STATIC_INLINE void LL_GTZC_MPCBB_SetBlockPrivAttr(GTZC_MPCBB_TypeDef *p_mpcbb,
                                                    uint32_t super_block,
                                                    uint32_t block,
                                                    uint32_t priv_attr)
{
  STM32_MODIFY_REG(p_mpcbb->PRIVCFGR[super_block], block, (block * priv_attr));
}

/**
  * @brief  Get privilege attribute of super_block MPCBB memory.
  * @rmtoll PGy_PRIVCFGR (y = 0 to 31)     PRIVx (x = 0 to 7)     LL_GTZC_MPCBB_GetSuperBlockPrivAttr
  * @param  p_mpcbb MPCBB Instance
  * @param  super_block
  *         This parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_0
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_1
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_2
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_3
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_4
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_6
  *         @arg @ref LL_GTZC_MPCBB_SUPERBLOCK_7
  * @endif
  * @retval Returned value can be 0x00000000U or a combination of the following values:
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_0
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_1
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_2
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_3
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_4
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_6
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_7
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_8
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_9
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_10
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_11
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_12
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_13
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_14
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_15
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_16
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_17
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_18
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_19
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_20
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_21
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_22
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_23
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_24
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_25
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_26
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_27
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_28
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_29
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_30
  *         @arg @ref LL_GTZC_MPCBB_BLOCK_31
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_GetSuperBlockPrivAttr(const GTZC_MPCBB_TypeDef *p_mpcbb,
                                                             uint32_t super_block)
{
  return (STM32_READ_REG(p_mpcbb->PRIVCFGR[super_block]));
}

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock configuration of MPCBB memory.
  * @rmtoll CR           GLOCK         LL_GTZC_MPCBB_LockConfig
  * @param  p_mpcbb MPCBB Instance
  */
__STATIC_INLINE void LL_GTZC_MPCBB_LockConfig(GTZC_MPCBB_TypeDef *p_mpcbb)
{
  STM32_SET_BIT(p_mpcbb->CR, GTZC_MPCBB_CR_GLOCK);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if MPCBB memory configuration is locked.
  * @rmtoll CR           GLOCK         LL_GTZC_MPCBB_IsLockedConfig
  * @param  p_mpcbb MPCBB Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_IsLockedConfig(const GTZC_MPCBB_TypeDef *p_mpcbb)
{
  return ((STM32_READ_BIT(p_mpcbb->CR, GTZC_MPCBB_CR_GLOCK) == GTZC_MPCBB_CR_GLOCK) ? 1UL : 0UL);
}

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock of super_block 0 to 31 of MPCBB memory.
  * @rmtoll CFGLOCKR1           RLOCKx (x = 0 to 31)         LL_GTZC_MPCBB_LockSuperBlockConfig
  * @param  p_mpcbb MPCBB Instance
  * @param  super_block
  *         The parameter can be a combination of the following values :
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_0
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_1
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_2
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_3
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_4
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_6
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_7
  * @endif
  */
__STATIC_INLINE void LL_GTZC_MPCBB_LockSuperBlockConfig(GTZC_MPCBB_TypeDef *p_mpcbb, uint32_t super_block)
{
  STM32_SET_BIT(p_mpcbb->CFGLOCKR1, super_block);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get lock of super_block 0 to 31 of MPCBB memory.
  * @rmtoll CFGLOCKR1           RLOCKx (x = 0 to 31)         LL_GTZC_MPCBB_IsLockedSuperBlockConfig
  * @param  p_mpcbb MPCBB Instance
  * @param  super_block
  *         The parameter can be one of the following values :
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_0
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_1
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_2
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_3
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_4
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_5
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_6
  *         @arg @ref LL_GTZC_MPCBB_LOCK_SUPERBLOCK_7
  * @endif
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_MPCBB_IsLockedSuperBlockConfig(const GTZC_MPCBB_TypeDef *p_mpcbb, uint32_t super_block)
{
  return ((STM32_READ_BIT(p_mpcbb->CFGLOCKR1, super_block) == super_block) ? 1UL : 0UL);
}

/**
  * @}
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/** @defgroup GTZC_LL_EF_TZIC_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable IERx illegal access interrupt.
  * @rmtoll IERx           IAIExxx         LL_GTZC_TZIC_EnableIT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TIM2
  * @if TIM3
  *         @arg @ref LL_GTZC_TIM3
  * @endif
  * @if TIM4
  *         @arg @ref LL_GTZC_TIM4
  * @endif
  * @if TIM5
  *         @arg @ref LL_GTZC_TIM5
  * @endif
  *         @arg @ref LL_GTZC_TIM6
  *         @arg @ref LL_GTZC_TIM7
  *         @arg @ref LL_GTZC_TIM12
  *         @arg @ref LL_GTZC_TIM13
  *         @arg @ref LL_GTZC_TIM14
  *         @arg @ref LL_GTZC_WWDG
  *         @arg @ref LL_GTZC_IWDG
  *         @arg @ref LL_GTZC_SPI2
  * @if SPI3
  *         @arg @ref LL_GTZC_SPI3
  * @endif
  *         @arg @ref LL_GTZC_USART2
  * @if USART3
  *         @arg @ref LL_GTZC_USART3
  * @endif
  *         @arg @ref LL_GTZC_UART4
  *         @arg @ref LL_GTZC_UART5
  *         @arg @ref LL_GTZC_I2C1
  *         @arg @ref LL_GTZC_I2C2
  *         @arg @ref LL_GTZC_I3C1
  * @if CRS
  *         @arg @ref LL_GTZC_CRS
  * @endif
  * @if UART6
  *         @arg @ref LL_GTZC_UART6
  * @endif
  *         @arg @ref LL_GTZC_DAC1
  *         @arg @ref LL_GTZC_DAC2
  *         @arg @ref LL_GTZC_TIM9
  *         @arg @ref LL_GTZC_TIM10
  *         @arg @ref LL_GTZC_TIM11
  *         @arg @ref LL_GTZC_DTS
  *         @arg @ref LL_GTZC_FDCAN1
  * @if FDCAN2
  *         @arg @ref LL_GTZC_FDCAN2
  * @endif
  * @if FDCAN3
  *         @arg @ref LL_GTZC_FDCAN3
  * @endif
  * @if UCPD1
  *         @arg @ref LL_GTZC_UCPD1
  * @endif
  *         @arg @ref LL_GTZC_TIM1
  *         @arg @ref LL_GTZC_SPI1
  *         @arg @ref LL_GTZC_TIM8
  *         @arg @ref LL_GTZC_USART1
  *         @arg @ref LL_GTZC_TIM15
  *         @arg @ref LL_GTZC_TIM16
  *         @arg @ref LL_GTZC_TIM17
  * @if HRTIM1
  *         @arg @ref LL_GTZC_HRTIM1
  * @endif
  * @if USB
  *         @arg @ref LL_GTZC_USB
  * @endif
  * @if TIM20
  *         @arg @ref LL_GTZC_TIM20
  * @endif
  * @if OPAMP1
  *         @arg @ref LL_GTZC_OPAMP1
  * @endif
  * @if OPAMP2
  *         @arg @ref LL_GTZC_OPAMP2
  * @endif
  * @if OPAMP3
  *         @arg @ref LL_GTZC_OPAMP3
  * @endif
  *         @arg @ref LL_GTZC_TIM26
  *         @arg @ref LL_GTZC_LPUART1
  * @if I2C3
  *         @arg @ref LL_GTZC_I2C3
  * @endif
  * @if I2C4
  *         @arg @ref LL_GTZC_I2C4
  * @endif
  *         @arg @ref LL_GTZC_LPTIM1
  *         @arg @ref LL_GTZC_COMP1
  *         @arg @ref LL_GTZC_COMP2
  *         @arg @ref LL_GTZC_COMP3
  *         @arg @ref LL_GTZC_COMP4
  *         @arg @ref LL_GTZC_COMP5
  *         @arg @ref LL_GTZC_COMP6
  *         @arg @ref LL_GTZC_COMP7
  *         @arg @ref LL_GTZC_COMP8
  *         @arg @ref LL_GTZC_VREFBUF
  *         @arg @ref LL_GTZC_TIM27
  * @if POSENC1
  *         @arg @ref LL_GTZC_POSENC1
  * @endif
  * @if POSENC2
  *         @arg @ref LL_GTZC_POSENC2
  * @endif
  *         @arg @ref LL_GTZC_CRC
  *         @arg @ref LL_GTZC_CORDIC1
  *         @arg @ref LL_GTZC_FMAC1
  * @if FMAC2
  *         @arg @ref LL_GTZC_FMAC2
  * @endif
  *         @arg @ref LL_GTZC_ICACHE
  * @if DCACHE
  *         @arg @ref LL_GTZC_DCACHE
  * @endif
  *         @arg @ref LL_GTZC_ADC12
  * @if ADC3
  *       @arg @ref LL_GTZC_ADC3
  * @endif
  * @if AES
  *       @arg @ref LL_GTZC_AES
  * @endif
  *         @arg @ref LL_GTZC_HASH
  *         @arg @ref LL_GTZC_RNG
  * @if SAES
  *         @arg @ref LL_GTZC_SAES
  * @endif
  *         @arg @ref LL_GTZC_PKA
  *         @arg @ref LL_GTZC_DAC5
  *         @arg @ref LL_GTZC_DAC6
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1
  * @endif
  *         @arg @ref LL_GTZC_RAMCFG
  *         @arg @ref LL_GTZC_DAC8
  *         @arg @ref LL_GTZC_DAC9
  *         @arg @ref LL_GTZC_DAC10
  * @if CCB
  *         @arg @ref LL_GTZC_CCB
  * @endif
  *         @arg @ref LL_GTZC_GPDMA1
  *         @arg @ref LL_GTZC_GPDMA2
  *         @arg @ref LL_GTZC_FLASH
  *         @arg @ref LL_GTZC_FLASH_REG
  * @if OTFDEC1
  *         @arg @ref LL_GTZC_OTFDEC1
  * @endif
  *         @arg @ref LL_GTZC_SBS
  *         @arg @ref LL_GTZC_RTC
  *         @arg @ref LL_GTZC_TAMP
  *         @arg @ref LL_GTZC_PWR
  *         @arg @ref LL_GTZC_RCC
  *         @arg @ref LL_GTZC_EXTI
  * @if PLAY1
  *         @arg @ref LL_GTZC_PLAY1
  * @endif
  *         @arg @ref LL_GTZC_TZSC1
  *         @arg @ref LL_GTZC_TZIC1
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1_MEM
  * @endif
  *         @arg @ref LL_GTZC_SRAM1
  *         @arg @ref LL_GTZC_MPCBB1_REG
  *         @arg @ref LL_GTZC_SRAM2
  *         @arg @ref LL_GTZC_MPCBB2_REG
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_SRAM3
  *         @arg @ref LL_GTZC_MPCBB3_REG
  * @endif
  */
__STATIC_INLINE void LL_GTZC_TZIC_EnableIT(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  STM32_SET_BIT(p_tzic->IER[periph / LL_GTZC_REG_MAX_FIELD], (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD)));
}

/**
  * @brief  Disable IERx illegal access interrupt.
  * @rmtoll IERx           IAIExxx        LL_GTZC_TZIC_DisableIT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TIM2
  * @if TIM3
  *         @arg @ref LL_GTZC_TIM3
  * @endif
  * @if TIM4
  *         @arg @ref LL_GTZC_TIM4
  * @endif
  * @if TIM5
  *         @arg @ref LL_GTZC_TIM5
  * @endif
  *         @arg @ref LL_GTZC_TIM6
  *         @arg @ref LL_GTZC_TIM7
  *         @arg @ref LL_GTZC_TIM12
  *         @arg @ref LL_GTZC_TIM13
  *         @arg @ref LL_GTZC_TIM14
  *         @arg @ref LL_GTZC_WWDG
  *         @arg @ref LL_GTZC_IWDG
  *         @arg @ref LL_GTZC_SPI2
  * @if SPI3
  *         @arg @ref LL_GTZC_SPI3
  * @endif
  *         @arg @ref LL_GTZC_USART2
  * @if USART3
  *         @arg @ref LL_GTZC_USART3
  * @endif
  *         @arg @ref LL_GTZC_UART4
  *         @arg @ref LL_GTZC_UART5
  *         @arg @ref LL_GTZC_I2C1
  *         @arg @ref LL_GTZC_I2C2
  *         @arg @ref LL_GTZC_I3C1
  * @if CRS
  *         @arg @ref LL_GTZC_CRS
  * @endif
  * @if UART6
  *         @arg @ref LL_GTZC_UART6
  * @endif
  *         @arg @ref LL_GTZC_DAC1
  *         @arg @ref LL_GTZC_DAC2
  *         @arg @ref LL_GTZC_TIM9
  *         @arg @ref LL_GTZC_TIM10
  *         @arg @ref LL_GTZC_TIM11
  *         @arg @ref LL_GTZC_DTS
  *         @arg @ref LL_GTZC_FDCAN1
  * @if FDCAN2
  *         @arg @ref LL_GTZC_FDCAN2
  * @endif
  * @if FDCAN3
  *         @arg @ref LL_GTZC_FDCAN3
  * @endif
  * @if UCPD1
  *         @arg @ref LL_GTZC_UCPD1
  * @endif
  *         @arg @ref LL_GTZC_TIM1
  *         @arg @ref LL_GTZC_SPI1
  *         @arg @ref LL_GTZC_TIM8
  *         @arg @ref LL_GTZC_USART1
  *         @arg @ref LL_GTZC_TIM15
  *         @arg @ref LL_GTZC_TIM16
  *         @arg @ref LL_GTZC_TIM17
  * @if HRTIM1
  *         @arg @ref LL_GTZC_HRTIM1
  * @endif
  * @if USB
  *         @arg @ref LL_GTZC_USB
  * @endif
  * @if TIM20
  *         @arg @ref LL_GTZC_TIM20
  * @endif
  * @if OPAMP1
  *         @arg @ref LL_GTZC_OPAMP1
  * @endif
  * @if OPAMP2
  *         @arg @ref LL_GTZC_OPAMP2
  * @endif
  * @if OPAMP3
  *         @arg @ref LL_GTZC_OPAMP3
  * @endif
  *         @arg @ref LL_GTZC_TIM26
  *         @arg @ref LL_GTZC_LPUART1
  * @if I2C3
  *         @arg @ref LL_GTZC_I2C3
  * @endif
  * @if I2C4
  *         @arg @ref LL_GTZC_I2C4
  * @endif
  *         @arg @ref LL_GTZC_LPTIM1
  *         @arg @ref LL_GTZC_COMP1
  *         @arg @ref LL_GTZC_COMP2
  *         @arg @ref LL_GTZC_COMP3
  *         @arg @ref LL_GTZC_COMP4
  *         @arg @ref LL_GTZC_COMP5
  *         @arg @ref LL_GTZC_COMP6
  *         @arg @ref LL_GTZC_COMP7
  *         @arg @ref LL_GTZC_COMP8
  *         @arg @ref LL_GTZC_VREFBUF
  *         @arg @ref LL_GTZC_TIM27
  * @if POSENC1
  *         @arg @ref LL_GTZC_POSENC1
  * @endif
  * @if POSENC2
  *         @arg @ref LL_GTZC_POSENC2
  * @endif
  *         @arg @ref LL_GTZC_CRC
  *         @arg @ref LL_GTZC_CORDIC1
  *         @arg @ref LL_GTZC_FMAC1
  * @if FMAC2
  *         @arg @ref LL_GTZC_FMAC2
  * @endif
  *         @arg @ref LL_GTZC_ICACHE
  * @if DCACHE
  *         @arg @ref LL_GTZC_DCACHE
  * @endif
  *         @arg @ref LL_GTZC_ADC12
  * @if ADC3
  *       @arg @ref LL_GTZC_ADC3
  * @endif
  * @if AES
  *       @arg @ref LL_GTZC_AES
  * @endif
  *         @arg @ref LL_GTZC_HASH
  *         @arg @ref LL_GTZC_RNG
  * @if SAES
  *         @arg @ref LL_GTZC_SAES
  * @endif
  *         @arg @ref LL_GTZC_PKA
  *         @arg @ref LL_GTZC_DAC5
  *         @arg @ref LL_GTZC_DAC6
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1
  * @endif
  *         @arg @ref LL_GTZC_RAMCFG
  *         @arg @ref LL_GTZC_DAC8
  *         @arg @ref LL_GTZC_DAC9
  *         @arg @ref LL_GTZC_DAC10
  * @if CCB
  *         @arg @ref LL_GTZC_CCB
  * @endif
  *         @arg @ref LL_GTZC_GPDMA1
  *         @arg @ref LL_GTZC_GPDMA2
  *         @arg @ref LL_GTZC_FLASH
  *         @arg @ref LL_GTZC_FLASH_REG
  * @if OTFDEC1
  *         @arg @ref LL_GTZC_OTFDEC1
  * @endif
  *         @arg @ref LL_GTZC_SBS
  *         @arg @ref LL_GTZC_RTC
  *         @arg @ref LL_GTZC_TAMP
  *         @arg @ref LL_GTZC_PWR
  *         @arg @ref LL_GTZC_RCC
  *         @arg @ref LL_GTZC_EXTI
  * @if PLAY1
  *         @arg @ref LL_GTZC_PLAY1
  * @endif
  *         @arg @ref LL_GTZC_TZSC1
  *         @arg @ref LL_GTZC_TZIC1
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1_MEM
  * @endif
  *         @arg @ref LL_GTZC_SRAM1
  *         @arg @ref LL_GTZC_MPCBB1_REG
  *         @arg @ref LL_GTZC_SRAM2
  *         @arg @ref LL_GTZC_MPCBB2_REG
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_SRAM3
  *         @arg @ref LL_GTZC_MPCBB3_REG
  * @endif
  */
__STATIC_INLINE void LL_GTZC_TZIC_DisableIT(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  STM32_CLEAR_BIT(p_tzic->IER[periph / LL_GTZC_REG_MAX_FIELD], (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD)));
}

/**
  * @brief  Check if IERx illegal access interrupt is enabled.
  * @rmtoll IERx           IAIExxx         LL_GTZC_TZIC_IsEnabledIT
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TIM2
  * @if TIM3
  *         @arg @ref LL_GTZC_TIM3
  * @endif
  * @if TIM4
  *         @arg @ref LL_GTZC_TIM4
  * @endif
  * @if TIM5
  *         @arg @ref LL_GTZC_TIM5
  * @endif
  *         @arg @ref LL_GTZC_TIM6
  *         @arg @ref LL_GTZC_TIM7
  *         @arg @ref LL_GTZC_TIM12
  *         @arg @ref LL_GTZC_TIM13
  *         @arg @ref LL_GTZC_TIM14
  *         @arg @ref LL_GTZC_WWDG
  *         @arg @ref LL_GTZC_IWDG
  *         @arg @ref LL_GTZC_SPI2
  * @if SPI3
  *         @arg @ref LL_GTZC_SPI3
  * @endif
  *         @arg @ref LL_GTZC_USART2
  * @if USART3
  *         @arg @ref LL_GTZC_USART3
  * @endif
  *         @arg @ref LL_GTZC_UART4
  *         @arg @ref LL_GTZC_UART5
  *         @arg @ref LL_GTZC_I2C1
  *         @arg @ref LL_GTZC_I2C2
  *         @arg @ref LL_GTZC_I3C1
  * @if CRS
  *         @arg @ref LL_GTZC_CRS
  * @endif
  * @if UART6
  *         @arg @ref LL_GTZC_UART6
  * @endif
  *         @arg @ref LL_GTZC_DAC1
  *         @arg @ref LL_GTZC_DAC2
  *         @arg @ref LL_GTZC_TIM9
  *         @arg @ref LL_GTZC_TIM10
  *         @arg @ref LL_GTZC_TIM11
  *         @arg @ref LL_GTZC_DTS
  *         @arg @ref LL_GTZC_FDCAN1
  * @if FDCAN2
  *         @arg @ref LL_GTZC_FDCAN2
  * @endif
  * @if FDCAN3
  *         @arg @ref LL_GTZC_FDCAN3
  * @endif
  * @if UCPD1
  *         @arg @ref LL_GTZC_UCPD1
  * @endif
  *         @arg @ref LL_GTZC_TIM1
  *         @arg @ref LL_GTZC_SPI1
  *         @arg @ref LL_GTZC_TIM8
  *         @arg @ref LL_GTZC_USART1
  *         @arg @ref LL_GTZC_TIM15
  *         @arg @ref LL_GTZC_TIM16
  *         @arg @ref LL_GTZC_TIM17
  * @if HRTIM1
  *         @arg @ref LL_GTZC_HRTIM1
  * @endif
  * @if USB
  *         @arg @ref LL_GTZC_USB
  * @endif
  * @if TIM20
  *         @arg @ref LL_GTZC_TIM20
  * @endif
  * @if OPAMP1
  *         @arg @ref LL_GTZC_OPAMP1
  * @endif
  * @if OPAMP2
  *         @arg @ref LL_GTZC_OPAMP2
  * @endif
  * @if OPAMP3
  *         @arg @ref LL_GTZC_OPAMP3
  * @endif
  *         @arg @ref LL_GTZC_TIM26
  *         @arg @ref LL_GTZC_LPUART1
  * @if I2C3
  *         @arg @ref LL_GTZC_I2C3
  * @endif
  * @if I2C4
  *         @arg @ref LL_GTZC_I2C4
  * @endif
  *         @arg @ref LL_GTZC_LPTIM1
  *         @arg @ref LL_GTZC_COMP1
  *         @arg @ref LL_GTZC_COMP2
  *         @arg @ref LL_GTZC_COMP3
  *         @arg @ref LL_GTZC_COMP4
  *         @arg @ref LL_GTZC_COMP5
  *         @arg @ref LL_GTZC_COMP6
  *         @arg @ref LL_GTZC_COMP7
  *         @arg @ref LL_GTZC_COMP8
  *         @arg @ref LL_GTZC_VREFBUF
  *         @arg @ref LL_GTZC_TIM27
  * @if POSENC1
  *         @arg @ref LL_GTZC_POSENC1
  * @endif
  * @if POSENC2
  *         @arg @ref LL_GTZC_POSENC2
  * @endif
  *         @arg @ref LL_GTZC_CRC
  *         @arg @ref LL_GTZC_CORDIC1
  *         @arg @ref LL_GTZC_FMAC1
  * @if FMAC2
  *         @arg @ref LL_GTZC_FMAC2
  * @endif
  *         @arg @ref LL_GTZC_ICACHE
  * @if DCACHE
  *         @arg @ref LL_GTZC_DCACHE
  * @endif
  *         @arg @ref LL_GTZC_ADC12
  * @if ADC3
  *       @arg @ref LL_GTZC_ADC3
  * @endif
  * @if AES
  *       @arg @ref LL_GTZC_AES
  * @endif
  *         @arg @ref LL_GTZC_HASH
  *         @arg @ref LL_GTZC_RNG
  * @if SAES
  *         @arg @ref LL_GTZC_SAES
  * @endif
  *         @arg @ref LL_GTZC_PKA
  *         @arg @ref LL_GTZC_DAC5
  *         @arg @ref LL_GTZC_DAC6
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1
  * @endif
  *         @arg @ref LL_GTZC_RAMCFG
  *         @arg @ref LL_GTZC_DAC8
  *         @arg @ref LL_GTZC_DAC9
  *         @arg @ref LL_GTZC_DAC10
  * @if CCB
  *         @arg @ref LL_GTZC_CCB
  * @endif
  *         @arg @ref LL_GTZC_GPDMA1
  *         @arg @ref LL_GTZC_GPDMA2
  *         @arg @ref LL_GTZC_FLASH
  *         @arg @ref LL_GTZC_FLASH_REG
  * @if OTFDEC1
  *         @arg @ref LL_GTZC_OTFDEC1
  * @endif
  *         @arg @ref LL_GTZC_SBS
  *         @arg @ref LL_GTZC_RTC
  *         @arg @ref LL_GTZC_TAMP
  *         @arg @ref LL_GTZC_PWR
  *         @arg @ref LL_GTZC_RCC
  *         @arg @ref LL_GTZC_EXTI
  * @if PLAY1
  *         @arg @ref LL_GTZC_PLAY1
  * @endif
  *         @arg @ref LL_GTZC_TZSC1
  *         @arg @ref LL_GTZC_TZIC1
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1_MEM
  * @endif
  *         @arg @ref LL_GTZC_SRAM1
  *         @arg @ref LL_GTZC_MPCBB1_REG
  *         @arg @ref LL_GTZC_SRAM2
  *         @arg @ref LL_GTZC_MPCBB2_REG
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_SRAM3
  *         @arg @ref LL_GTZC_MPCBB3_REG
  * @endif
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZIC_IsEnabledIT(const GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  uint32_t periph_msk;

  periph_msk = (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD));
  return ((STM32_READ_BIT(p_tzic->IER[periph / LL_GTZC_REG_MAX_FIELD], periph_msk) == periph_msk) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup GTZC_LL_EF_TZIC_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get SRx illegal access flag.
  * @rmtoll SRx           IAFxxx         LL_GTZC_TZIC_IsActiveFlag
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TIM2
  * @if TIM3
  *         @arg @ref LL_GTZC_TIM3
  * @endif
  * @if TIM4
  *         @arg @ref LL_GTZC_TIM4
  * @endif
  * @if TIM5
  *         @arg @ref LL_GTZC_TIM5
  * @endif
  *         @arg @ref LL_GTZC_TIM6
  *         @arg @ref LL_GTZC_TIM7
  *         @arg @ref LL_GTZC_TIM12
  *         @arg @ref LL_GTZC_TIM13
  *         @arg @ref LL_GTZC_TIM14
  *         @arg @ref LL_GTZC_WWDG
  *         @arg @ref LL_GTZC_IWDG
  *         @arg @ref LL_GTZC_SPI2
  * @if SPI3
  *         @arg @ref LL_GTZC_SPI3
  * @endif
  *         @arg @ref LL_GTZC_USART2
  * @if USART3
  *         @arg @ref LL_GTZC_USART3
  * @endif
  *         @arg @ref LL_GTZC_UART4
  *         @arg @ref LL_GTZC_UART5
  *         @arg @ref LL_GTZC_I2C1
  *         @arg @ref LL_GTZC_I2C2
  *         @arg @ref LL_GTZC_I3C1
  * @if CRS
  *         @arg @ref LL_GTZC_CRS
  * @endif
  * @if UART6
  *         @arg @ref LL_GTZC_UART6
  * @endif
  *         @arg @ref LL_GTZC_DAC1
  *         @arg @ref LL_GTZC_DAC2
  *         @arg @ref LL_GTZC_TIM9
  *         @arg @ref LL_GTZC_TIM10
  *         @arg @ref LL_GTZC_TIM11
  *         @arg @ref LL_GTZC_DTS
  *         @arg @ref LL_GTZC_FDCAN1
  * @if FDCAN2
  *         @arg @ref LL_GTZC_FDCAN2
  * @endif
  * @if FDCAN3
  *         @arg @ref LL_GTZC_FDCAN3
  * @endif
  * @if UCPD1
  *         @arg @ref LL_GTZC_UCPD1
  * @endif
  *         @arg @ref LL_GTZC_TIM1
  *         @arg @ref LL_GTZC_SPI1
  *         @arg @ref LL_GTZC_TIM8
  *         @arg @ref LL_GTZC_USART1
  *         @arg @ref LL_GTZC_TIM15
  *         @arg @ref LL_GTZC_TIM16
  *         @arg @ref LL_GTZC_TIM17
  * @if HRTIM1
  *         @arg @ref LL_GTZC_HRTIM1
  * @endif
  * @if USB
  *         @arg @ref LL_GTZC_USB
  * @endif
  * @if TIM20
  *         @arg @ref LL_GTZC_TIM20
  * @endif
  * @if OPAMP1
  *         @arg @ref LL_GTZC_OPAMP1
  * @endif
  * @if OPAMP2
  *         @arg @ref LL_GTZC_OPAMP2
  * @endif
  * @if OPAMP3
  *         @arg @ref LL_GTZC_OPAMP3
  * @endif
  *         @arg @ref LL_GTZC_TIM26
  *         @arg @ref LL_GTZC_LPUART1
  * @if I2C3
  *         @arg @ref LL_GTZC_I2C3
  * @endif
  * @if I2C4
  *         @arg @ref LL_GTZC_I2C4
  * @endif
  *         @arg @ref LL_GTZC_LPTIM1
  *         @arg @ref LL_GTZC_COMP1
  *         @arg @ref LL_GTZC_COMP2
  *         @arg @ref LL_GTZC_COMP3
  *         @arg @ref LL_GTZC_COMP4
  *         @arg @ref LL_GTZC_COMP5
  *         @arg @ref LL_GTZC_COMP6
  *         @arg @ref LL_GTZC_COMP7
  *         @arg @ref LL_GTZC_COMP8
  *         @arg @ref LL_GTZC_VREFBUF
  *         @arg @ref LL_GTZC_TIM27
  * @if POSENC1
  *         @arg @ref LL_GTZC_POSENC1
  * @endif
  * @if POSENC2
  *         @arg @ref LL_GTZC_POSENC2
  * @endif
  *         @arg @ref LL_GTZC_CRC
  *         @arg @ref LL_GTZC_CORDIC1
  *         @arg @ref LL_GTZC_FMAC1
  * @if FMAC2
  *         @arg @ref LL_GTZC_FMAC2
  * @endif
  *         @arg @ref LL_GTZC_ICACHE
  * @if DCACHE
  *         @arg @ref LL_GTZC_DCACHE
  * @endif
  *         @arg @ref LL_GTZC_ADC12
  * @if ADC3
  *       @arg @ref LL_GTZC_ADC3
  * @endif
  * @if AES
  *       @arg @ref LL_GTZC_AES
  * @endif
  *         @arg @ref LL_GTZC_HASH
  *         @arg @ref LL_GTZC_RNG
  * @if SAES
  *         @arg @ref LL_GTZC_SAES
  * @endif
  *         @arg @ref LL_GTZC_PKA
  *         @arg @ref LL_GTZC_DAC5
  *         @arg @ref LL_GTZC_DAC6
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1
  * @endif
  *         @arg @ref LL_GTZC_RAMCFG
  *         @arg @ref LL_GTZC_DAC8
  *         @arg @ref LL_GTZC_DAC9
  *         @arg @ref LL_GTZC_DAC10
  * @if CCB
  *         @arg @ref LL_GTZC_CCB
  * @endif
  *         @arg @ref LL_GTZC_GPDMA1
  *         @arg @ref LL_GTZC_GPDMA2
  *         @arg @ref LL_GTZC_FLASH
  *         @arg @ref LL_GTZC_FLASH_REG
  * @if OTFDEC1
  *         @arg @ref LL_GTZC_OTFDEC1
  * @endif
  *         @arg @ref LL_GTZC_SBS
  *         @arg @ref LL_GTZC_RTC
  *         @arg @ref LL_GTZC_TAMP
  *         @arg @ref LL_GTZC_PWR
  *         @arg @ref LL_GTZC_RCC
  *         @arg @ref LL_GTZC_EXTI
  * @if PLAY1
  *         @arg @ref LL_GTZC_PLAY1
  * @endif
  *         @arg @ref LL_GTZC_TZSC1
  *         @arg @ref LL_GTZC_TZIC1
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1_MEM
  * @endif
  *         @arg @ref LL_GTZC_SRAM1
  *         @arg @ref LL_GTZC_MPCBB1_REG
  *         @arg @ref LL_GTZC_SRAM2
  *         @arg @ref LL_GTZC_MPCBB2_REG
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_SRAM3
  *         @arg @ref LL_GTZC_MPCBB3_REG
  * @endif
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GTZC_TZIC_IsActiveFlag(const GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  uint32_t periph_msk;

  periph_msk = (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD));
  return ((STM32_READ_BIT(p_tzic->SR[periph / LL_GTZC_REG_MAX_FIELD], periph_msk) == periph_msk) ? 1UL : 0UL);
}

/**
  * @brief  Clear FCRx illegal access flag.
  * @rmtoll FCRx           IAFxxx         LL_GTZC_TZIC_ClearFlag
  * @param  p_tzic TZIC Instance
  * @param  periph This parameter can be one of the following values:
  *         @arg @ref LL_GTZC_TIM2
  * @if TIM3
  *         @arg @ref LL_GTZC_TIM3
  * @endif
  * @if TIM4
  *         @arg @ref LL_GTZC_TIM4
  * @endif
  * @if TIM5
  *         @arg @ref LL_GTZC_TIM5
  * @endif
  *         @arg @ref LL_GTZC_TIM6
  *         @arg @ref LL_GTZC_TIM7
  *         @arg @ref LL_GTZC_TIM12
  *         @arg @ref LL_GTZC_TIM13
  *         @arg @ref LL_GTZC_TIM14
  *         @arg @ref LL_GTZC_WWDG
  *         @arg @ref LL_GTZC_IWDG
  *         @arg @ref LL_GTZC_SPI2
  * @if SPI3
  *         @arg @ref LL_GTZC_SPI3
  * @endif
  *         @arg @ref LL_GTZC_USART2
  * @if USART3
  *         @arg @ref LL_GTZC_USART3
  * @endif
  *         @arg @ref LL_GTZC_UART4
  *         @arg @ref LL_GTZC_UART5
  *         @arg @ref LL_GTZC_I2C1
  *         @arg @ref LL_GTZC_I2C2
  *         @arg @ref LL_GTZC_I3C1
  * @if CRS
  *         @arg @ref LL_GTZC_CRS
  * @endif
  * @if UART6
  *         @arg @ref LL_GTZC_UART6
  * @endif
  *         @arg @ref LL_GTZC_DAC1
  *         @arg @ref LL_GTZC_DAC2
  *         @arg @ref LL_GTZC_TIM9
  *         @arg @ref LL_GTZC_TIM10
  *         @arg @ref LL_GTZC_TIM11
  *         @arg @ref LL_GTZC_DTS
  *         @arg @ref LL_GTZC_FDCAN1
  * @if FDCAN2
  *         @arg @ref LL_GTZC_FDCAN2
  * @endif
  * @if FDCAN3
  *         @arg @ref LL_GTZC_FDCAN3
  * @endif
  * @if UCPD1
  *         @arg @ref LL_GTZC_UCPD1
  * @endif
  *         @arg @ref LL_GTZC_TIM1
  *         @arg @ref LL_GTZC_SPI1
  *         @arg @ref LL_GTZC_TIM8
  *         @arg @ref LL_GTZC_USART1
  *         @arg @ref LL_GTZC_TIM15
  *         @arg @ref LL_GTZC_TIM16
  *         @arg @ref LL_GTZC_TIM17
  * @if HRTIM1
  *         @arg @ref LL_GTZC_HRTIM1
  * @endif
  * @if USB
  *         @arg @ref LL_GTZC_USB
  * @endif
  * @if TIM20
  *         @arg @ref LL_GTZC_TIM20
  * @endif
  * @if OPAMP1
  *         @arg @ref LL_GTZC_OPAMP1
  * @endif
  * @if OPAMP2
  *         @arg @ref LL_GTZC_OPAMP2
  * @endif
  * @if OPAMP3
  *         @arg @ref LL_GTZC_OPAMP3
  * @endif
  *         @arg @ref LL_GTZC_TIM26
  *         @arg @ref LL_GTZC_LPUART1
  * @if I2C3
  *         @arg @ref LL_GTZC_I2C3
  * @endif
  * @if I2C4
  *         @arg @ref LL_GTZC_I2C4
  * @endif
  *         @arg @ref LL_GTZC_LPTIM1
  *         @arg @ref LL_GTZC_COMP1
  *         @arg @ref LL_GTZC_COMP2
  *         @arg @ref LL_GTZC_COMP3
  *         @arg @ref LL_GTZC_COMP4
  *         @arg @ref LL_GTZC_COMP5
  *         @arg @ref LL_GTZC_COMP6
  *         @arg @ref LL_GTZC_COMP7
  *         @arg @ref LL_GTZC_COMP8
  *         @arg @ref LL_GTZC_VREFBUF
  *         @arg @ref LL_GTZC_TIM27
  * @if POSENC1
  *         @arg @ref LL_GTZC_POSENC1
  * @endif
  * @if POSENC2
  *         @arg @ref LL_GTZC_POSENC2
  * @endif
  *         @arg @ref LL_GTZC_CRC
  *         @arg @ref LL_GTZC_CORDIC1
  *         @arg @ref LL_GTZC_FMAC1
  * @if FMAC2
  *         @arg @ref LL_GTZC_FMAC2
  * @endif
  *         @arg @ref LL_GTZC_ICACHE
  * @if DCACHE
  *         @arg @ref LL_GTZC_DCACHE
  * @endif
  *         @arg @ref LL_GTZC_ADC12
  * @if ADC3
  *       @arg @ref LL_GTZC_ADC3
  * @endif
  * @if AES
  *       @arg @ref LL_GTZC_AES
  * @endif
  *         @arg @ref LL_GTZC_HASH
  *         @arg @ref LL_GTZC_RNG
  * @if SAES
  *         @arg @ref LL_GTZC_SAES
  * @endif
  *         @arg @ref LL_GTZC_PKA
  *         @arg @ref LL_GTZC_DAC5
  *         @arg @ref LL_GTZC_DAC6
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1
  * @endif
  *         @arg @ref LL_GTZC_RAMCFG
  *         @arg @ref LL_GTZC_DAC8
  *         @arg @ref LL_GTZC_DAC9
  *         @arg @ref LL_GTZC_DAC10
  * @if CCB
  *         @arg @ref LL_GTZC_CCB
  * @endif
  *         @arg @ref LL_GTZC_GPDMA1
  *         @arg @ref LL_GTZC_GPDMA2
  *         @arg @ref LL_GTZC_FLASH
  *         @arg @ref LL_GTZC_FLASH_REG
  * @if OTFDEC1
  *         @arg @ref LL_GTZC_OTFDEC1
  * @endif
  *         @arg @ref LL_GTZC_SBS
  *         @arg @ref LL_GTZC_RTC
  *         @arg @ref LL_GTZC_TAMP
  *         @arg @ref LL_GTZC_PWR
  *         @arg @ref LL_GTZC_RCC
  *         @arg @ref LL_GTZC_EXTI
  * @if PLAY1
  *         @arg @ref LL_GTZC_PLAY1
  * @endif
  *         @arg @ref LL_GTZC_TZSC1
  *         @arg @ref LL_GTZC_TZIC1
  * @if XSPI1
  *         @arg @ref LL_GTZC_XSPI1_MEM
  * @endif
  *         @arg @ref LL_GTZC_SRAM1
  *         @arg @ref LL_GTZC_MPCBB1_REG
  *         @arg @ref LL_GTZC_SRAM2
  *         @arg @ref LL_GTZC_MPCBB2_REG
  * @if SRAM3_BASE
  *         @arg @ref LL_GTZC_SRAM3
  *         @arg @ref LL_GTZC_MPCBB3_REG
  * @endif
  */
__STATIC_INLINE void LL_GTZC_TZIC_ClearFlag(GTZC_TZIC_TypeDef *p_tzic, uint32_t periph)
{
  STM32_WRITE_REG(p_tzic->FCR[periph / LL_GTZC_REG_MAX_FIELD], (0x01UL << (periph % LL_GTZC_REG_MAX_FIELD)));
}
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

#endif /* STM32G5XX_LL_GTZC_H */
