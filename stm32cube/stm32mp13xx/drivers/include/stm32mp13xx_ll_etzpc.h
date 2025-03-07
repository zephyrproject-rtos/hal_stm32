/**
  ******************************************************************************
  * @file    stm32mp13xx_ll_etzpc.h
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
#ifndef STM32MP13xx_LL_ETZPC_H
#define STM32MP13xx_LL_ETZPC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx.h"
#include <stdint.h>

/** @addtogroup STM32MP13xx_LL_Driver
  * @{
  */

/** @defgroup ETZPC_LL ETZPC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/** @defgroup ETZPC_LL_Private_Macros ETZPC Private Macros
  * @{
  */

#define ETZPC_MODIFY_REG(REG,FIELD,VALUE) MODIFY_REG(ETZPCx->REG, ETZPC_##REG##_##FIELD##_Msk, (((VALUE) &\
                                                     (ETZPC_##REG##_##FIELD##_Msk >> ETZPC_##REG##_##FIELD##_Pos))\
                                                     << ETZPC_##REG##_##FIELD##_Pos))

#define ETZPC_SET_BIT(REG,FIELD) SET_BIT(ETZPCx->REG, ETZPC_##REG##_##FIELD##_Msk)

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup ETZPC_LL_Exported_Constants ETZPC Exported Constants
  * @{
  */

#define  LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_SECURE               0x0 /*!< read and write secure */
#define  LL_ETZPC_PERIPH_PROTECTION_READ_NONSECURE_WRITE_SECURE     0x1 /*!< read non-secure and write secure */
#define  LL_ETZPC_PERIPH_PROTECTION_READ_WRITE_NONSECURE            0x3 /*!< read and write non-secure */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup ETZPC_LL_Exported_Macros ETZPC Exported Macros
  * @{
  */
/** @defgroup ETZPC_EM_WRITE_READ Common Write and read registers macros
  * @{
  */
/**
  * @brief  Write a value in ETZPC register
  * @param  __INSTANCE__ ETZPC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_ETZPC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in ETZPC register
  * @param  __INSTANCE__ ETZPC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_ETZPC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

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
__STATIC_INLINE void LL_ETZPC_SetSecureSysRamSize(ETZPC_TypeDef *ETZPCx, uint32_t size)
{
  ETZPC_MODIFY_REG(TZMA1_SIZE, ROSIZE, size);
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
__STATIC_INLINE void LL_ETZPC_LockSecureSysRamSize(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(TZMA1_SIZE, LOCK);
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
__STATIC_INLINE void LL_ETZPC_Set_All_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  /* Broadcast the protection, if it is a constant the following operations will be optimized out and the result will
     be a constant too */
  uint32_t prtn = protection & 3u;
  prtn = (prtn << 2)  | prtn;
  prtn = (prtn << 4)  | prtn;
  prtn = (prtn << 8)  | prtn;
  prtn = (prtn << 16) | prtn;
  /* Set the protection for all peripherals */
  ETZPCx->DECPROT0 = prtn;
  ETZPCx->DECPROT1 = prtn;
  ETZPCx->DECPROT2 = prtn;
  ETZPCx->DECPROT3 = prtn;
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
__STATIC_INLINE void LL_ETZPC_Set_VREFBUF_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT0, VREFBUF, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_LPTIM2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT0, LPTIM2, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_LPTIM3_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT0, LPTIM3, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_LTDC_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT0, LTDC, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_DCMIPP_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT0, DCMIPP, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_USBPHYC_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT0, USBPHYC, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_DDRCTRL_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT0, DDRCTRL, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_IWDG1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT0, IWDG1, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_STGENC_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT0, STGENC, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_USART1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, USART1, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_USART2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, USART2, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_SPI4_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, SPI4, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_SPI5_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, SPI5, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_I2C3_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, I2C3, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_I2C4_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, I2C4, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_I2C5_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, I2C5, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_TIM12_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, TIM12, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_TIM13_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, TIM13, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_TIM14_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, TIM14, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_TIM15_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, TIM15, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_TIM16_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, TIM16, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_TIM17_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT1, TIM17, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_ADC1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT2, ADC1, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_ADC2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT2, ADC2, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_OTG_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT2, OTG, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_RNG_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT2, RNG, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_HASH_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT2, HASH, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_CRYP_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT2, CRYP, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_SAES_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT2, SAES, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_PKA_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT2, PKA, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_BKPSRAM_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT2, BKPSRAM, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_ETH1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT3, ETH1, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_ETH2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT3, ETH2, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_SDMMC1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT3, SDMMC1, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_SDMMC2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT3, SDMMC2, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_DDRMCE_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT3, DDRMCE, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_FMC_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT3, FMC, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_QSPI_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT3, QSPI, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_SRAM1_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT3, SRAM1, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_SRAM2_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT3, SRAM2, protection);
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
__STATIC_INLINE void LL_ETZPC_Set_SRAM3_PeriphProtection(ETZPC_TypeDef *ETZPCx, uint32_t protection)
{
  ETZPC_MODIFY_REG(DECPROT3, SRAM3, protection);
}

/**
  * @brief  Lock all peripherals (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_All_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPCx->DECPROT_LOCK0 = 0xFFFFFFFFu;
  ETZPCx->DECPROT_LOCK1 = 0xFFFFFFFFu;
}

/**
  * @brief  Lock VREFBUF peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_VREFBUF_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, VREFBUF);
}

/**
  * @brief  Lock LPTIM2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_LPTIM2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, LPTIM2);
}

/**
  * @brief  Lock LPTIM3 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_LPTIM3_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, LPTIM3);
}

/**
  * @brief  Lock LTDC layer 2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_LTDC_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, LTDC);
}

/**
  * @brief  Lock DCMIPP peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_DCMIPP_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, DCMIPP);
}

/**
  * @brief  Lock USBPHYC peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_USBPHYC_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, USBPHYC);
}

/**
  * @brief  Lock DDRCTRL and DDRPHYC peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_DDRCTRL_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, DDRCTRL);
}

/**
  * @brief  Lock Independent Watchdog 1 (IWDG1) peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_IWDG1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, IWDG1);
}

/**
  * @brief  Lock System Timer Generator (STGENC) peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_STGENC_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, STGENC);
}

/**
  * @brief  Lock secure USART1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_USART1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, USART1);
}

/**
  * @brief  Lock secure USART2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_USART2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, USART2);
}

/**
  * @brief  Lock SPI4 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_SPI4_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, SPI4);
}

/**
  * @brief  Lock SPI5 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_SPI5_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, SPI5);
}

/**
  * @brief  Lock I2C3 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_I2C3_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, I2C3);
}

/**
  * @brief  Lock I2C4 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_I2C4_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, I2C4);
}

/**
  * @brief  Lock I2C5 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_I2C5_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, I2C5);
}

/**
  * @brief  Lock TIM12 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_TIM12_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, TIM12);
}

/**
  * @brief  Lock TIM13 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_TIM13_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, TIM13);
}

/**
  * @brief  Lock TIM14 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_TIM14_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, TIM14);
}

/**
  * @brief  Lock TIM15 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_TIM15_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, TIM15);
}

/**
  * @brief  Lock TIM16 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_TIM16_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, TIM16);
}

/**
  * @brief  Lock TIM17 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_TIM17_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK0, TIM17);
}

/**
  * @brief  Lock ADC1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_ADC1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, ADC1);
}

/**
  * @brief  Lock ADC2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_ADC2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, ADC2);
}

/**
  * @brief  Lock OTG peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_OTG_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, OTG);
}

/**
  * @brief  Lock RNG peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_RNG_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, RNG);
}

/**
  * @brief  Lock HASH peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_HASH_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, HASH);
}

/**
  * @brief  Lock CRYP peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_CRYP_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, CRYP);
}

/**
  * @brief  Lock SAES peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_SAES_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, SAES);
}

/**
  * @brief  Lock PKA peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_PKA_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, PKA);
}

/**
  * @brief  Lock Backup RAM (BKPSRAM) peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_BKPSRAM_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, BKPSRAM);
}

/**
  * @brief  Lock ETH1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_ETH1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, ETH1);
}

/**
  * @brief  Lock ETH2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_ETH2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, ETH2);
}

/**
  * @brief  Lock SDMMC1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_SDMMC1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, SDMMC1);
}

/**
  * @brief  Lock SDMMC2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_SDMMC2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, SDMMC2);
}

/**
  * @brief  Lock DDRMCE peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_DDRMCE_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, DDRMCE);
}

/**
  * @brief  Lock FMC peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_FMC_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, FMC);
}

/**
  * @brief  Lock QSPI peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_QSPI_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, QSPI);
}

/**
  * @brief  Lock SRAM1 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_SRAM1_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, SRAM1);
}

/**
  * @brief  Lock SRAM2 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_SRAM2_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, SRAM2);
}

/**
  * @brief  Lock SRAM3 peripheral (ETZPC Securable peripheral) protection.
  *
  * @param  ETZPCx ETZPC Instance
  * @retval None
  */
__STATIC_INLINE void LL_ETZPC_Lock_SRAM3_PeriphProtection(ETZPC_TypeDef *ETZPCx)
{
  ETZPC_SET_BIT(DECPROT_LOCK1, SRAM3);
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

#endif /* STM32MP13xx_LL_ETZPC_H */
