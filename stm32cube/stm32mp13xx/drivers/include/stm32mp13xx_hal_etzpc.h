/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_etzpc.h
  * @author  MCD Application Team
  * @brief   Header file for ETZPC utility functions.
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
#ifndef STM32MP13xx_HAL_ETZPC_H
#define STM32MP13xx_HAL_ETZPC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "assert.h"
#include "stm32mp13xx_ll_etzpc.h"

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @defgroup ETZPC_HAL ETZPC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/** @defgroup ETZPC_HAL_Private_Macros ETZPC Private Macros
  * @{
  */

#define ETZPC_CHECK_PROTECTION(p) assert( \
                                          p == LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE || \
                                          p == LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE || \
                                          p == LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE)

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup ETZPC_LL_Exported_Functions ETZPC Exported Functions
  * @{
  */

/** @defgroup ETZPC_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Set Secure SYSRAM size.
  *         Define the size of the secure SYSRAM at low address and non-secure at high
  *
  *         This function can be called from startup, and as such respect following rules:
  *           - it must have less than four arguments
  *           - it must not call another function
  *
  * @param  ETZPCx ETZPC Instance
  * @param  size  Size of secure zone
  *               0x000: all SYSRAM is non-secure
  *               0x001: 4K Byte SYSRAM secure
  *               0x002: 8K Byte SYSRAM secure
  *               ....
  *               0x040 to 0x3FF: 256K Byte SYSRAM secure (e.g all SYSRAM secure) <-- reset value in ETZPC/TZMA1
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_SetSecureSysRamSize(ETZPC_TypeDef *ETZPCx, uint32_t size)
{
  assert(size <= 0x3FFU);
  LL_ETZPC_SetSecureSysRamSize(ETZPCx, size);
}

/**
  * @brief  Lock Secure RAM size.
  *
  *         Lock the size of the secure RAM until next reset.
  *
  *         This function can be called from startup, and as such respect following rules:
  *           - it must have less than four arguments
  *           - it must not call another function
  *
  * @param  ETZPCx ETZPC Instance
  *
  * @retval None
  *
 */
__STATIC_INLINE void HAL_ETZPC_LockSecureSysRamSize(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_LockSecureSysRamSize(ETZPCx);
}

/**
  * @brief  Set all peripherals (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_All_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_All_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set VREFBUF peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_VREFBUF_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_VREFBUF_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set LPTIM2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_LPTIM2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_LPTIM2_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set LPTIM3 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_LPTIM3_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_LPTIM3_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set LTDC layer 2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_LTDC_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_LTDC_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set DCMIPP peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_DCMIPP_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_DCMIPP_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set USBPHYC peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_USBPHYC_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_USBPHYC_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set DDRCTRL and DDRPHYC peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_DDRCTRL_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_DDRCTRL_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set Independent Watchdog 1 (IWDG1) peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_IWDG1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_IWDG1_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set System Timer Generator (STGENC) peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_STGENC_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_STGENC_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set secure USART1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_USART1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_USART1_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set secure USART2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_USART2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_USART2_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set SPI4 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_SPI4_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_SPI4_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set SPI5 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_SPI5_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_SPI5_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set I2C3 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_I2C3_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_I2C3_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set I2C4 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_I2C4_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_I2C4_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set I2C5 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_I2C5_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_I2C5_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set TIM12 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_TIM12_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_TIM12_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set TIM13 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_TIM13_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_TIM13_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set TIM14 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_TIM14_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_TIM14_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set TIM15 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_TIM15_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_TIM15_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set TIM16 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_TIM16_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_TIM16_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set TIM17 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_TIM17_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_TIM17_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set ADC1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_ADC1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_ADC1_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set ADC2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_ADC2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_ADC2_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set OTG peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_OTG_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_OTG_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set RNG peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_RNG_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_RNG_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set HASH peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_HASH_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_HASH_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set CRYP peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_CRYP_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_CRYP_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set SAES peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_SAES_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_SAES_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set PKA peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_PKA_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_PKA_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set Backup RAM (BKPSRAM) peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_BKPSRAM_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_BKPSRAM_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set ETH1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_ETH1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_ETH1_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set ETH2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_ETH2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_ETH2_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set SDMMC1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_SDMMC1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_SDMMC1_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set SDMMC2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_SDMMC2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_SDMMC2_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set DDRMCE peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_DDRMCE_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_DDRMCE_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set FMC peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_FMC_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_FMC_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set QSPI peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_QSPI_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_QSPI_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set SRAM1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_SRAM1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_SRAM1_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set SRAM2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_SRAM2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_SRAM2_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Set SRAM3 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @param  protection  : protection level of the peripheral : possible values are
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE
  *                      - LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Set_SRAM3_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_CHECK_PROTECTION(protection);
  LL_ETZPC_Set_SRAM3_PeriphProtection(ETZPCx, protection);
}

/**
  * @brief  Lock all peripherals (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_All_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_All_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock VREFBUF peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_VREFBUF_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_VREFBUF_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock LPTIM2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_LPTIM2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_LPTIM2_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock LPTIM3 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_LPTIM3_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_LPTIM3_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock LTDC layer 2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_LTDC_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_LTDC_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock DCMIPP peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_DCMIPP_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_DCMIPP_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock USBPHYC peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_USBPHYC_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_USBPHYC_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock DDRCTRL and DDRPHYC peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_DDRCTRL_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_DDRCTRL_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock Independent Watchdog 1 (IWDG1) peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_IWDG1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_IWDG1_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock System Timer Generator (STGENC) peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_STGENC_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_STGENC_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock secure USART1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_USART1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_USART1_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock secure USART2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_USART2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_USART2_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock SPI4 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_SPI4_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_SPI4_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock SPI5 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_SPI5_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_SPI5_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock I2C3 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_I2C3_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_I2C3_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock I2C4 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_I2C4_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_I2C4_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock I2C5 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_I2C5_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_I2C5_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock TIM12 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_TIM12_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_TIM12_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock TIM13 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_TIM13_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_TIM13_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock TIM14 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_TIM14_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_TIM14_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock TIM15 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_TIM15_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_TIM15_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock TIM16 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_TIM16_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_TIM16_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock TIM17 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_TIM17_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_TIM17_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock ADC1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_ADC1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_ADC1_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock ADC2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_ADC2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_ADC2_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock OTG peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_OTG_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_OTG_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock RNG peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_RNG_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_RNG_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock HASH peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_HASH_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_HASH_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock CRYP peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_CRYP_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_CRYP_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock SAES peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_SAES_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_SAES_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock PKA peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_PKA_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_PKA_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock Backup RAM (BKPSRAM) peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_BKPSRAM_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_BKPSRAM_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock ETH1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_ETH1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_ETH1_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock ETH2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_ETH2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_ETH2_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock SDMMC1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_SDMMC1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_SDMMC1_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock SDMMC2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_SDMMC2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_SDMMC2_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock DDRMCE peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_DDRMCE_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_DDRMCE_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock FMC peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_FMC_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_FMC_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock QSPI peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_QSPI_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_QSPI_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock SRAM1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_SRAM1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_SRAM1_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock SRAM2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_SRAM2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_SRAM2_PeriphProtection(ETZPCx);
}

/**
  * @brief  Lock SRAM3 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void HAL_ETZPC_Lock_SRAM3_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  LL_ETZPC_Lock_SRAM3_PeriphProtection(ETZPCx);
}

/**
  * @}
  */

/**
  * @}
  */

/* ---------------------------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP13xx_HAL_ETZPC_H */
