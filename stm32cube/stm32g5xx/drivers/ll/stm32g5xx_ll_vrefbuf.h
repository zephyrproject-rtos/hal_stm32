/**
  ******************************************************************************
  * @file    stm32g5xx_ll_vrefbuf.h
  * @brief   Header file of VREFBUF LL module.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G5XX_LL_VREFBUF_H
#define STM32G5XX_LL_VREFBUF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */

#if defined (VREFBUF)

/** @defgroup VREFBUF_LL VREFBUF
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup VREFBUF_LL_Exported_Constants LL VREFBUF Constants
  * @{
  */

/** @defgroup  VREFBUF_LL_VOLTAGE VREFBUF Voltage levels.
  * @{
  */
#define LL_VREFBUF_VOLTAGE_SCALE0    (0UL)                                   /*!< Voltage reference scale 0     */
#define LL_VREFBUF_VOLTAGE_SCALE1    (VREFBUF_CSR_VRS_0)                     /*!< Voltage reference scale 1     */
#define LL_VREFBUF_VOLTAGE_SCALE2    (VREFBUF_CSR_VRS_1)                     /*!< Voltage reference scale 2     */
#define LL_VREFBUF_VOLTAGE_SCALE3    (VREFBUF_CSR_VRS_1 | VREFBUF_CSR_VRS_0) /*!< Voltage reference scale 3     */
/**
  * @}
  */

/** @defgroup  VREFBUF_LL_MODE VREFBUF Mode Configuration.
  * @{
  */
#define LL_VREFBUF_MODE_PULL_DOWN         (0UL)                                 /* Pull down mode                    */
#define LL_VREFBUF_MODE_EXT_VOLTAGE_REF   (VREFBUF_CSR_HIZ)                     /* External voltage reference mode   */
#define LL_VREFBUF_MODE_INT_VOLTAGE_REF   (VREFBUF_CSR_ENVR)                    /* Internal voltage reference mode   */
#define LL_VREFBUF_MODE_HOLD              (VREFBUF_CSR_HIZ | VREFBUF_CSR_ENVR)  /* Hold mode                         */

/**
  * @brief  Write a value in VREFBUF register.
  * @param  instance VREFBUF Instance
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_VREFBUF_WRITE_REG(instance, reg, value) STM32_WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in VREFBUF register.
  * @param  instance VREFBUF Instance
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_VREFBUF_READ_REG(instance, reg) STM32_READ_REG((instance)->reg)
/**
  * @}
  */
/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @defgroup VREFBUF_LL_Exported_Functions LL VREFBUF Functions
  * @{
  */

/**
  * @brief  Set the functional mode.
  * @rmtoll
  *  CSR  HIZ              LL_VREFBUF_SetMode \n
  *  CSR  ENVR             LL_VREFBUF_SetMode
  * @param  vrefbufx Pointer to VREFBUF instance
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_VREFBUF_MODE_PULL_DOWN
  *         @arg @ref LL_VREFBUF_MODE_EXT_VOLTAGE_REF
  *         @arg @ref LL_VREFBUF_MODE_INT_VOLTAGE_REF
  *         @arg @ref LL_VREFBUF_MODE_HOLD
  */
__STATIC_INLINE void LL_VREFBUF_SetMode(VREFBUF_TypeDef *vrefbufx, uint32_t mode)
{
  STM32_MODIFY_REG(vrefbufx->CSR, VREFBUF_CSR_HIZ | VREFBUF_CSR_ENVR, mode);
}

/**
  * @brief  Get the functional mode.
  * @rmtoll
  *  CSR  HIZ              LL_VREFBUF_GetMode \n
  *  CSR  ENVR             LL_VREFBUF_GetMode
  * @param  vrefbufx Pointer to VREFBUF instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_VREFBUF_MODE_PULL_DOWN
  *         @arg @ref LL_VREFBUF_MODE_EXT_VOLTAGE_REF
  *         @arg @ref LL_VREFBUF_MODE_INT_VOLTAGE_REF
  *         @arg @ref LL_VREFBUF_MODE_HOLD
  */
__STATIC_INLINE uint32_t LL_VREFBUF_GetMode(const VREFBUF_TypeDef *vrefbufx)
{
  return (uint32_t)(STM32_READ_BIT(vrefbufx->CSR, (VREFBUF_CSR_HIZ | VREFBUF_CSR_ENVR)));
}

/**
  * @brief  Set the Voltage reference scale.
  * @rmtoll
  *  VREFBUF_CSR  VRS           LL_VREFBUF_SetVoltageScale
  * @param  vrefbufx Pointer to VREFBUF instance
  * @param  voltage_scale This parameter can be one of the following values:
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE0
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE1
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE2
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE3
  */
__STATIC_INLINE void LL_VREFBUF_SetVoltageScale(VREFBUF_TypeDef *vrefbufx, uint32_t voltage_scale)
{
  STM32_MODIFY_REG(vrefbufx->CSR, VREFBUF_CSR_VRS, voltage_scale);
}

/**
  * @brief  Get the Voltage reference scale.
  * @rmtoll
  *  VREFBUF_CSR  VRS           LL_VREFBUF_GetVoltageScale
  * @param  vrefbufx Pointer to VREFBUF instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE0
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE1
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE2
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE3
  */
__STATIC_INLINE uint32_t LL_VREFBUF_GetVoltageScale(const VREFBUF_TypeDef *vrefbufx)
{
  return (uint32_t)(STM32_READ_BIT(vrefbufx->CSR, VREFBUF_CSR_VRS));
}

/**
  * @brief  Get the trimming code for VREFBUF calibration.
  * @rmtoll
  *  VREFBUF_CCR  TRIM          LL_VREFBUF_GetTrimming
  * @param  vrefbufx Pointer to VREFBUF instance
  * @retval Between 0 and 0x3F
  */
__STATIC_INLINE uint32_t LL_VREFBUF_GetTrimming(const VREFBUF_TypeDef *vrefbufx)
{
  return (uint32_t)(STM32_READ_BIT(vrefbufx->CCR, VREFBUF_CCR_TRIM));
}

/**
  * @brief  Set the trimming code for VREFBUF calibration (Tune the internal reference buffer voltage).
  * @rmtoll
  *  VREFBUF_CCR  TRIM          LL_VREFBUF_SetTrimming
  * @param  vrefbufx Pointer to VREFBUF instance
  * @param  trimming_value Between 0 and 0x3F
  */
__STATIC_INLINE void LL_VREFBUF_SetTrimming(VREFBUF_TypeDef *vrefbufx, uint32_t trimming_value)
{
  STM32_MODIFY_REG(vrefbufx->CCR, VREFBUF_CCR_TRIM, trimming_value);
}

/**
  * @brief  Enable Internal voltage reference.
  * @rmtoll
  *  VREFBUF_CSR  ENVR          LL_VREFBUF_Enable
  * @param  vrefbufx Pointer to VREFBUF instance
  */
__STATIC_INLINE void LL_VREFBUF_Enable(VREFBUF_TypeDef *vrefbufx)
{
  STM32_SET_BIT(vrefbufx->CSR, VREFBUF_CSR_ENVR);
}

/**
  * @brief  Disable Internal voltage reference.
  * @rmtoll
  *  VREFBUF_CSR  ENVR          LL_VREFBUF_Disable
  * @param  vrefbufx Pointer to VREFBUF instance
  */
__STATIC_INLINE void LL_VREFBUF_Disable(VREFBUF_TypeDef *vrefbufx)
{
  STM32_CLEAR_BIT(vrefbufx->CSR, VREFBUF_CSR_ENVR);
}

/**
  * @brief  Enable high impedance (VREF+ pin is high impedance).
  * @rmtoll
  *  VREFBUF_CSR  HIZ           LL_VREFBUF_EnableHIZ
  * @param  vrefbufx Pointer to VREFBUF instance
  */
__STATIC_INLINE void LL_VREFBUF_EnableHIZ(VREFBUF_TypeDef *vrefbufx)
{
  STM32_SET_BIT(vrefbufx->CSR, VREFBUF_CSR_HIZ);
}

/**
  * @brief  Disable high impedance (VREF+pin is internally connected to the voltage reference buffer output).
  * @rmtoll
  *  VREFBUF_CSR  HIZ           LL_VREFBUF_DisableHIZ
  * @param  vrefbufx Pointer to VREFBUF instance
  */
__STATIC_INLINE void LL_VREFBUF_DisableHIZ(VREFBUF_TypeDef *vrefbufx)
{
  STM32_CLEAR_BIT(vrefbufx->CSR, VREFBUF_CSR_HIZ);
}

/**
  * @brief  Check if high impedance is enable.
  * @rmtoll
  *  VREFBUF_CSR  HIZ           LL_VREFBUF_IsEnabledHIZ
  * @param  vrefbufx Pointer to VREFBUF instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_VREFBUF_IsEnabledHIZ(const VREFBUF_TypeDef *vrefbufx)
{
  return ((STM32_READ_BIT(vrefbufx->CSR, VREFBUF_CSR_HIZ) == (VREFBUF_CSR_HIZ)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Voltage reference buffer is ready.
  * @rmtoll
  *  VREFBUF_CSR  VRR           LL_VREFBUF_IsVREFReady
  * @param  vrefbufx Pointer to VREFBUF instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_VREFBUF_IsVREFReady(const VREFBUF_TypeDef *vrefbufx)
{
  return ((STM32_READ_BIT(vrefbufx->CSR, VREFBUF_CSR_VRR) == VREFBUF_CSR_VRR) ? 1UL : 0UL);
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* VREFBUF */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_LL_VREFBUF_H */
