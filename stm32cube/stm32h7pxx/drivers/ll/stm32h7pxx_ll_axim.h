/**
  **********************************************************************************************************************
  * @file   stm32h7pxx_ll_axim.h
  * @brief  Header file of AXIM LL module.
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
#ifndef STM32H7PXX_LL_AXIM_H
#define STM32H7PXX_LL_AXIM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7PXX_LL_Driver
  * @{
  */
#if defined (AXIM)
/** @addtogroup AXIM_LL AXIM
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup AXIM_LL_Exported_Constants  LL AXIM Constants
  * @{
  */

/** @defgroup AXIM_ASIB AXIM Initiators
  * @{
  */
#define LL_AXIM_ASIB_GPDMA  0x0000U /*!< Initiator 1:  GPDMA  */
#define LL_AXIM_ASIB_SDMMC1 0x0400U /*!< Initiator 2:  SDMMC1 */
#define LL_AXIM_ASIB_HPDMA  0x0800U /*!< Initiator 3:  HPDMA  */
#define LL_AXIM_ASIB_CORE   0x0C00U /*!< Initiator 4:  CORE   */
#define LL_AXIM_ASIB_NPU_1  0x1000U /*!< Initiator 5:  NPU 1  */
#define LL_AXIM_ASIB_NPU_2  0x1400U /*!< Initiator 6:  NPU 2  */
/**
  * @}
  */

/** @defgroup AXIM_AMIB AXIM Targets
  * @{
  */
#define LL_AXIM_AMIB_AHBIC_BRIDGE 0x0000U /*!< Target 1:  AHBIC_BRIDGE */
#define LL_AXIM_AMIB_FMC          0x0400U /*!< Target 2:  FMC          */
#define LL_AXIM_AMIB_XSPI1        0x0800U /*!< Target 3:  XSPI1        */
#define LL_AXIM_AMIB_AXISRAM3     0x0C00U /*!< Target 4:  AXISRAM3     */
#define LL_AXIM_AMIB_AXISRAM2     0x1000U /*!< Target 5:  AXISRAM2     */
#define LL_AXIM_AMIB_AXISRAM1     0x1400U /*!< Target 6:  AXISRAM1     */
#define LL_AXIM_AMIB_FLASH        0x1800U /*!< Target 7:  FLASH        */
#define LL_AXIM_AMIB_AXISRAM4     0x1C00U /*!< Target 8:  AXISRAM4     */
#define LL_AXIM_AMIB_AHBS_BRIDGE  0x2000U /*!< Target 9:  AHBS_BRIDGE  */
/**
  * @}
  */

/** @defgroup AXIM_ISSUING_MODE AXIM Issuing capabilities
  * @{
  */
#define LL_AXIM_ISSUING_NORMAL         0x00UL /*!< AXIM issuing capability no override             */
#define LL_AXIM_ISSUING_OVERRIDE_READ  0x01UL /*!< AXIM issuing capability override read           */
#define LL_AXIM_ISSUING_OVERRIDE_WRITE 0x02UL /*!< AXIM issuing capability override write          */
#define LL_AXIM_ISSUING_OVERRIDE_BOTH  0x03UL /*!< AXIM issuing capability override read and write */
/**
  * @}
  */

/** @defgroup AXIM_INCREMENT_OVERRIDE_MODE AXIM increment override capabilities
  * @{
  */
#define LL_AXIM_INCREMENT_NORMAL         0UL /*!< AXIM increment override capability no override             */
#define LL_AXIM_INCREMENT_OVERRIDE_READ  1UL /*!< AXIM increment override capability override read           */
#define LL_AXIM_INCREMENT_OVERRIDE_WRITE 2UL /*!< AXIM increment override capability override write          */
#define LL_AXIM_INCREMENT_OVERRIDE_BOTH  3UL /*!< AXIM increment override capability override read and write */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup AXIM_LL_Exported_Functions LL AXIM Functions
  * @{
  */

/** @defgroup AXIM_LL_Exported_Functions_Group1 AXIM initiator functions.
  * @{
  */

/**
  * @brief  Set AXIM initiator read quality of service.
  * @rmtoll
  *  INIx_READ_QOS          RQOS           LL_AXIM_ASIB_SetReadQoS
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  *         @arg @ref LL_AXIM_ASIB_HPDMA
  *         @arg @ref LL_AXIM_ASIB_CORE
  *         @arg @ref LL_AXIM_ASIB_NPU_1
  *         @arg @ref LL_AXIM_ASIB_NPU_2
  * @param  read_qos can be a value between 0 and 15.
  */
__STATIC_INLINE void LL_AXIM_ASIB_SetReadQoS(uint32_t asib, uint32_t read_qos)
{
  __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_READ_QOS + asib;

  STM32_MODIFY_REG(*reg_addr, AXIM_INI0_READ_QOS_RQOS, read_qos);
}

/**
  * @brief  Get AXIM initiator read quality of service.
  * @rmtoll
  *  INIx_READ_QOS          RQOS           LL_AXIM_ASIB_GetReadQoS
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  *         @arg @ref LL_AXIM_ASIB_HPDMA
  *         @arg @ref LL_AXIM_ASIB_CORE
  *         @arg @ref LL_AXIM_ASIB_NPU_1
  *         @arg @ref LL_AXIM_ASIB_NPU_2
  * @retval Read quality of service value can be between 0 and 15.
  */
__STATIC_INLINE uint32_t LL_AXIM_ASIB_GetReadQoS(uint32_t asib)
{
  const __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_READ_QOS + asib;

  return (STM32_READ_BIT(*reg_addr, AXIM_INI0_READ_QOS_RQOS));
}

/**
  * @brief  Set AXIM initiator write quality of service.
  * @rmtoll
  *  INIx_WRITE_QOS          WQOS           LL_AXIM_ASIB_SetWriteQoS
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  *         @arg @ref LL_AXIM_ASIB_HPDMA
  *         @arg @ref LL_AXIM_ASIB_CORE
  *         @arg @ref LL_AXIM_ASIB_NPU_1
  *         @arg @ref LL_AXIM_ASIB_NPU_2
  * @param  write_qos can be a value between 0 and 15.
  */
__STATIC_INLINE void LL_AXIM_ASIB_SetWriteQoS(uint32_t asib, uint32_t write_qos)
{
  __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_WRITE_QOS + asib;

  STM32_MODIFY_REG(*reg_addr, AXIM_INI0_WRITE_QOS_WQOS, write_qos);
}

/**
  * @brief  Get AXIM initiator write quality of service.
  * @rmtoll
  *  INIx_WRITE_QOS          WQOS           LL_AXIM_ASIB_GetWriteQoS
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  *         @arg @ref LL_AXIM_ASIB_HPDMA
  *         @arg @ref LL_AXIM_ASIB_CORE
  *         @arg @ref LL_AXIM_ASIB_NPU_1
  *         @arg @ref LL_AXIM_ASIB_NPU_2
  * @retval Write quality of service value can be between 0 and 15.
  */
__STATIC_INLINE uint32_t LL_AXIM_ASIB_GetWriteQoS(uint32_t asib)
{
  const __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_WRITE_QOS + asib;

  return (STM32_READ_BIT(*reg_addr, AXIM_INI0_WRITE_QOS_WQOS));
}

/**
  * @brief  Set AXIM initiator read/write issuing capability.
  * @rmtoll
  *  INIx_FN_MOD          READ_ISS_OVERRIDE           LL_AXIM_ASIB_SetIssuingCapability \n
  *  INIx_FN_MOD          WRITE_ISS_OVERRIDE          LL_AXIM_ASIB_SetIssuingCapability
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  *         @arg @ref LL_AXIM_ASIB_HPDMA
  *         @arg @ref LL_AXIM_ASIB_CORE
  *         @arg @ref LL_AXIM_ASIB_NPU_1
  *         @arg @ref LL_AXIM_ASIB_NPU_2
  * @param  issuing_capability can be one of the following values:
  *         @arg @ref LL_AXIM_ISSUING_NORMAL
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_READ
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_WRITE
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_BOTH
  */
__STATIC_INLINE void LL_AXIM_ASIB_SetIssuingCapability(uint32_t asib, uint32_t issuing_capability)
{
  __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_FN_MOD + asib;

  STM32_MODIFY_REG(*reg_addr,
                   (AXIM_INI0_FN_MOD_READ_ISS_OVERRIDE | AXIM_INI0_FN_MOD_WRITE_ISS_OVERRIDE), issuing_capability);
}

/**
  * @brief  Get AXIM initiator read/write issuing capability.
  * @rmtoll
  *  INIx_FN_MOD          READ_ISS_OVERRIDE           LL_AXIM_ASIB_GetIssuingCapability \n
  *  INIx_FN_MOD          WRITE_ISS_OVERRIDE          LL_AXIM_ASIB_GetIssuingCapability
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  *         @arg @ref LL_AXIM_ASIB_HPDMA
  *         @arg @ref LL_AXIM_ASIB_CORE
  *         @arg @ref LL_AXIM_ASIB_NPU_1
  *         @arg @ref LL_AXIM_ASIB_NPU_2
  * @retval issuing_capability can be one of the following values:
  *         @arg @ref LL_AXIM_ISSUING_NORMAL
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_READ
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_WRITE
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_BOTH
  */
__STATIC_INLINE uint32_t LL_AXIM_ASIB_GetIssuingCapability(uint32_t asib)
{
  const __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_FN_MOD + asib;

  return (STM32_READ_BIT(*reg_addr, (AXIM_INI0_FN_MOD_READ_ISS_OVERRIDE | AXIM_INI0_FN_MOD_WRITE_ISS_OVERRIDE)));
}

/**
  * @brief  Enable packing for AXIM initiator.
  * @rmtoll
  *  INIx_FN_MOD2          BYPASS_MERGE           LL_AXIM_ASIB_EnablePacking
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  */
__STATIC_INLINE void LL_AXIM_ASIB_EnablePacking(uint32_t asib)
{
  __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_FN_MOD2 + asib;

  STM32_CLEAR_BIT(*reg_addr, AXIM_INI0_FN_MOD2_BYPASS_MERGE);
}

/**
  * @brief  Disable packing for AXIM initiator.
  * @rmtoll
  *  INIx_FN_MOD2          BYPASS_MERGE           LL_AXIM_ASIB_DisablePacking
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  */
__STATIC_INLINE void LL_AXIM_ASIB_DisablePacking(uint32_t asib)
{
  __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_FN_MOD2 + asib;

  STM32_SET_BIT(*reg_addr, AXIM_INI0_FN_MOD2_BYPASS_MERGE);
}

/**
  * @brief  Check if packing is enabled or disabled for AXIM initiator.
  * @rmtoll
  *  INIx_FN_MOD2          BYPASS_MERGE           LL_AXIM_ASIB_IsEnabledPacking
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  * @retval packing state (0U or 1U).
  */
__STATIC_INLINE uint32_t LL_AXIM_ASIB_IsEnabledPacking(uint32_t asib)
{
  const __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_FN_MOD2 + asib;

  return ((STM32_READ_BIT(*reg_addr, AXIM_INI0_FN_MOD2_BYPASS_MERGE) == 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Set AXIM initiator read/write increment override.
  * @rmtoll
  *  INIx_FN_MOD_AHB          RD_INCR_OVERRIDE           LL_AXIM_ASIB_SetIncrementOverride \n
  *  INIx_FN_MOD_AHB          WR_INCR_OVERRIDE           LL_AXIM_ASIB_SetIncrementOverride
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  * @param  increment_override can be one of the following values:
  *         @arg @ref LL_AXIM_INCREMENT_NORMAL
  *         @arg @ref LL_AXIM_INCREMENT_OVERRIDE_READ
  *         @arg @ref LL_AXIM_INCREMENT_OVERRIDE_WRITE
  *         @arg @ref LL_AXIM_INCREMENT_OVERRIDE_BOTH
  */
__STATIC_INLINE void LL_AXIM_ASIB_SetIncrementOverride(uint32_t asib, uint32_t increment_override)
{
  __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_FN_MOD_AHB + asib;

  STM32_MODIFY_REG(*reg_addr,
                   (AXIM_INI0_FN_MOD_AHB_RD_INCR_OVERRIDE | AXIM_INI0_FN_MOD_AHB_WR_INCR_OVERRIDE), increment_override);
}

/**
  * @brief  Get AXIM initiator read/write increment override.
  * @rmtoll
  *  INIx_FN_MOD_AHB          RD_INCR_OVERRIDE           LL_AXIM_ASIB_GetIncrementOverride \n
  *  INIx_FN_MOD_AHB          WR_INCR_OVERRIDE           LL_AXIM_ASIB_GetIncrementOverride
  * @param  asib can be one of the following values:
  *         @arg @ref LL_AXIM_ASIB_GPDMA
  *         @arg @ref LL_AXIM_ASIB_SDMMC1
  * @retval increment override can be one of the following values:
  *         @arg @ref LL_AXIM_INCREMENT_NORMAL
  *         @arg @ref LL_AXIM_INCREMENT_OVERRIDE_READ
  *         @arg @ref LL_AXIM_INCREMENT_OVERRIDE_WRITE
  *         @arg @ref LL_AXIM_INCREMENT_OVERRIDE_BOTH
  */
__STATIC_INLINE uint32_t LL_AXIM_ASIB_GetIncrementOverride(uint32_t asib)
{
  const __IO uint32_t *reg_addr = &AXIM->ASIB.INI0_FN_MOD_AHB + asib;

  return (STM32_READ_BIT(*reg_addr, (AXIM_INI0_FN_MOD_AHB_RD_INCR_OVERRIDE | AXIM_INI0_FN_MOD_AHB_WR_INCR_OVERRIDE)));
}

/**
  * @}
  */

/** @defgroup AXIM_LL_Exported_Functions_Group2 AXIM Target functions.
  * @{
  */

/**
  * @brief  Set AXIM target bus matrix read/write issuing capability.
  * @rmtoll
  *  TARGx_FN_MOD_BM_ISS      WRITE_ISS_OVERRIDE      LL_AXIM_AMIB_SetBusMatrixIssuingCapability \n
  *  TARGx_FN_MOD_BM_ISS      READ_ISS_OVERRIDE       LL_AXIM_AMIB_SetBusMatrixIssuingCapability
  * @param  amib can be one of the following values:
  *         @arg @ref LL_AXIM_AMIB_AHBIC_BRIDGE
  *         @arg @ref LL_AXIM_AMIB_FMC
  *         @arg @ref LL_AXIM_AMIB_XSPI1
  *         @arg @ref LL_AXIM_AMIB_AXISRAM3
  *         @arg @ref LL_AXIM_AMIB_AXISRAM2
  *         @arg @ref LL_AXIM_AMIB_AXISRAM1
  *         @arg @ref LL_AXIM_AMIB_FLASH
  *         @arg @ref LL_AXIM_AMIB_AXISRAM4
  *         @arg @ref LL_AXIM_AMIB_AHBS_BRIDGE
  * @param  issuing_capability can be one of the following values:
  *         @arg @ref LL_AXIM_ISSUING_NORMAL
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_READ
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_WRITE
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_BOTH
  */
__STATIC_INLINE void LL_AXIM_AMIB_SetBusMatrixIssuingCapability(uint32_t amib, uint32_t issuing_capability)
{
  __IO uint32_t *reg_addr = &AXIM->AMIB.TARG0_FN_MOD_BM_ISS + amib;

  STM32_MODIFY_REG(*reg_addr,
                   (AXIM_TARG0_FN_MOD_BM_ISS_READ_ISS_OVERRIDE | AXIM_TARG0_FN_MOD_BM_ISS_WRITE_ISS_OVERRIDE),
                   issuing_capability);
}

/**
  * @brief  Get AXIM target bus matrix read/write issuing capability.
  * @rmtoll
  *  TARGx_FN_MOD_BM_ISS      WRITE_ISS_OVERRIDE      LL_AXIM_AMIB_GetBusMatrixIssuingCapability \n
  *  TARGx_FN_MOD_BM_ISS      READ_ISS_OVERRIDE       LL_AXIM_AMIB_GetBusMatrixIssuingCapability
  * @param  amib can be one of the following values:
  *         @arg @ref LL_AXIM_AMIB_AHBIC_BRIDGE
  *         @arg @ref LL_AXIM_AMIB_FMC
  *         @arg @ref LL_AXIM_AMIB_XSPI1
  *         @arg @ref LL_AXIM_AMIB_AXISRAM3
  *         @arg @ref LL_AXIM_AMIB_AXISRAM2
  *         @arg @ref LL_AXIM_AMIB_AXISRAM1
  *         @arg @ref LL_AXIM_AMIB_FLASH
  *         @arg @ref LL_AXIM_AMIB_AXISRAM4
  *         @arg @ref LL_AXIM_AMIB_AHBS_BRIDGE
  * @retval issuing capability can be one of the following values:
  *         @arg @ref LL_AXIM_ISSUING_NORMAL
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_READ
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_WRITE
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_BOTH
  */
__STATIC_INLINE uint32_t LL_AXIM_AMIB_GetBusMatrixIssuingCapability(uint32_t amib)
{
  const __IO uint32_t *reg_addr = &AXIM->AMIB.TARG0_FN_MOD_BM_ISS + amib;

  return (STM32_READ_BIT(*reg_addr,
                         (AXIM_TARG0_FN_MOD_BM_ISS_READ_ISS_OVERRIDE | AXIM_TARG0_FN_MOD_BM_ISS_WRITE_ISS_OVERRIDE)));
}

/**
  * @brief  Set AXIM target read/write issuing capability.
  * @rmtoll
  *  TARGx_FN_MOD      WRITE_ISS_OVERRIDE      LL_AXIM_AMIB_SetIssuingCapability \n
  *  TARGx_FN_MOD      READ_ISS_OVERRIDE       LL_AXIM_AMIB_SetIssuingCapability
  * @param  amib can be one of the following values:
  *         @arg @ref LL_AXIM_AMIB_AHBIC_BRIDGE
  *         @arg @ref LL_AXIM_AMIB_FMC
  *         @arg @ref LL_AXIM_AMIB_XSPI1
  *         @arg @ref LL_AXIM_AMIB_AXISRAM3
  *         @arg @ref LL_AXIM_AMIB_AXISRAM2
  *         @arg @ref LL_AXIM_AMIB_AXISRAM1
  *         @arg @ref LL_AXIM_AMIB_FLASH
  *         @arg @ref LL_AXIM_AMIB_AXISRAM4
  *         @arg @ref LL_AXIM_AMIB_AHBS_BRIDGE
  * @param  issuing_capability can be one of the following values:
  *         @arg @ref LL_AXIM_ISSUING_NORMAL
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_READ
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_WRITE
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_BOTH
  */
__STATIC_INLINE void LL_AXIM_AMIB_SetIssuingCapability(uint32_t amib, uint32_t issuing_capability)
{
  __IO uint32_t *reg_addr = &AXIM->AMIB.TARG0_FN_MOD + amib;

  STM32_MODIFY_REG(*reg_addr,
                   (AXIM_TARG0_FN_MOD_READ_ISS_OVERRIDE | AXIM_TARG0_FN_MOD_WRITE_ISS_OVERRIDE),
                   issuing_capability);
}

/**
  * @brief  Get AXIM target read/write issuing capability.
  * @rmtoll
  *  TARGx_FN_MOD      WRITE_ISS_OVERRIDE      LL_AXIM_AMIB_GetIssuingCapability \n
  *  TARGx_FN_MOD      READ_ISS_OVERRIDE       LL_AXIM_AMIB_GetIssuingCapability
  * @param  amib can be one of the following values:
  *         @arg @ref LL_AXIM_AMIB_AHBIC_BRIDGE
  *         @arg @ref LL_AXIM_AMIB_FMC
  *         @arg @ref LL_AXIM_AMIB_XSPI1
  *         @arg @ref LL_AXIM_AMIB_AXISRAM3
  *         @arg @ref LL_AXIM_AMIB_AXISRAM2
  *         @arg @ref LL_AXIM_AMIB_AXISRAM1
  *         @arg @ref LL_AXIM_AMIB_FLASH
  *         @arg @ref LL_AXIM_AMIB_AXISRAM4
  *         @arg @ref LL_AXIM_AMIB_AHBS_BRIDGE
  * @retval issuing capability can be one of the following values:
  *         @arg @ref LL_AXIM_ISSUING_NORMAL
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_READ
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_WRITE
  *         @arg @ref LL_AXIM_ISSUING_OVERRIDE_BOTH
  */
__STATIC_INLINE uint32_t LL_AXIM_AMIB_GetIssuingCapability(uint32_t amib)
{
  const __IO uint32_t *reg_addr = &AXIM->AMIB.TARG0_FN_MOD + amib;

  return (STM32_READ_BIT(*reg_addr, (AXIM_TARG0_FN_MOD_READ_ISS_OVERRIDE | AXIM_TARG0_FN_MOD_WRITE_ISS_OVERRIDE)));
}

/**
  * @brief  Enable packing for AXIM Target.
  * @rmtoll
  *  TARGx_FN_MOD2          BYPASS_MERGE           LL_AXIM_AMIB_EnablePacking
  * @param  amib can be one of the following values:
  *         @arg @ref LL_AXIM_AMIB_AHBIC_BRIDGE
  *         @arg @ref LL_AXIM_AMIB_AHBS_BRIDGE
  */
__STATIC_INLINE void LL_AXIM_AMIB_EnablePacking(uint32_t amib)
{
  __IO uint32_t *reg_addr = &AXIM->AMIB.TARG0_FN_MOD2 + amib;

  STM32_CLEAR_BIT(*reg_addr, AXIM_TARG0_FN_MOD2_BYPASS_MERGE);
}

/**
  * @brief  Disable packing for AXIM Target.
  * @rmtoll
  *  TARGx_FN_MOD2          BYPASS_MERGE           LL_AXIM_AMIB_DisablePacking
  * @param  amib can be one of the following values:
  *         @arg @ref LL_AXIM_AMIB_AHBIC_BRIDGE
  *         @arg @ref LL_AXIM_AMIB_AHBS_BRIDGE
  */
__STATIC_INLINE void LL_AXIM_AMIB_DisablePacking(uint32_t amib)
{
  __IO uint32_t *reg_addr = &AXIM->AMIB.TARG0_FN_MOD2 + amib;

  STM32_SET_BIT(*reg_addr, AXIM_TARG0_FN_MOD2_BYPASS_MERGE);
}

/**
  * @brief  Check if packing is enabled or disabled for AXIM Target.
  * @rmtoll
  *  TARGx_FN_MOD2          BYPASS_MERGE           LL_AXIM_AMIB_IsEnabledPacking
  * @param  amib can be one of the following values:
  *         @arg @ref LL_AXIM_AMIB_AHBIC_BRIDGE
  *         @arg @ref LL_AXIM_AMIB_AHBS_BRIDGE
  * @retval packing state (0UL or 1UL)
  */
__STATIC_INLINE uint32_t LL_AXIM_AMIB_IsEnabledPacking(uint32_t amib)
{
  const __IO uint32_t *reg_addr = &AXIM->AMIB.TARG0_FN_MOD2 + amib;

  return ((STM32_READ_BIT(*reg_addr, AXIM_TARG0_FN_MOD2_BYPASS_MERGE) == 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Enable long burst generation for AXIM Target.
  * @rmtoll
  *  TARGx_FN_MOD_LB          FN_MOD_LB           LL_AXIM_AMIB_EnableLongBurst
  * @param  amib can be one of the following values:
  *         @arg @ref LL_AXIM_AMIB_AHBIC_BRIDGE
  *         @arg @ref LL_AXIM_AMIB_AHBS_BRIDGE
  */
__STATIC_INLINE void LL_AXIM_AMIB_EnableLongBurst(uint32_t amib)
{
  __IO uint32_t *reg_addr = &AXIM->AMIB.TARG0_FN_MOD_LB + (amib - LL_AXIM_AMIB_AHBIC_BRIDGE);

  STM32_SET_BIT(*reg_addr, AXIM_TARG0_FN_MOD_LB_FN_MOD_LB);
}

/**
  * @brief  Disable long burst generation for AXIM Target.
  * @rmtoll
  *  TARGx_FN_MOD_LB          FN_MOD_LB           LL_AXIM_AMIB_DisableLongBurst
  * @param  amib can be one of the following values:
  *         @arg @ref LL_AXIM_AMIB_AHBIC_BRIDGE
  *         @arg @ref LL_AXIM_AMIB_AHBS_BRIDGE
  */
__STATIC_INLINE void LL_AXIM_AMIB_DisableLongBurst(uint32_t amib)
{
  __IO uint32_t *reg_addr = &AXIM->AMIB.TARG0_FN_MOD_LB + (amib - LL_AXIM_AMIB_AHBIC_BRIDGE);

  STM32_CLEAR_BIT(*reg_addr, AXIM_TARG0_FN_MOD_LB_FN_MOD_LB);
}

/**
  * @brief  Check if long burst generation is enabled or disabled for AXIM Target.
  * @rmtoll
  *  TARGx_FN_MOD_LB          FN_MOD_LB           LL_AXIM_AMIB_IsEnabledLongBurst
  * @param  amib can be one of the following values:
  *         @arg @ref LL_AXIM_AMIB_AHBIC_BRIDGE
  *         @arg @ref LL_AXIM_AMIB_AHBS_BRIDGE
  * @retval Long burst generation enable status (0UL or 1UL).
  */
__STATIC_INLINE uint32_t LL_AXIM_AMIB_IsEnabledLongBurst(uint32_t amib)
{
  const __IO uint32_t *reg_addr = &AXIM->AMIB.TARG0_FN_MOD_LB + amib;

  return ((STM32_READ_BIT(*reg_addr, AXIM_TARG0_FN_MOD_LB_FN_MOD_LB) != 0UL) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup AXIM_LL_Exported_Functions_Group3 AXIM Information functions.
  * @{
  */

/**
  * @brief  Get AXIM File Size in 4KB units.
  * @rmtoll
  *  PERIPH_ID4          COUNT4K           LL_AXIM_GetFileSize
  * @retval AXIM File Size in 4KB units
  */
__STATIC_INLINE uint32_t LL_AXIM_GetFileSize(void)
{
  return (STM32_READ_BIT(AXIM->PERIPH_ID_4, AXIM_PERIPH_ID_4_COUNT4K) >> AXIM_PERIPH_ID_4_COUNT4K_Pos);
}

/**
  * @brief  Get AXIM JEP-106 Continuation Code.
  * @rmtoll
  *  PERIPH_ID4          JEP106CON           LL_AXIM_GetRevisionContinuationCode
  * @retval AXIM JEP-106 Continuation Code
  */
__STATIC_INLINE uint32_t LL_AXIM_GetRevisionContinuationCode(void)
{
  return (STM32_READ_BIT(AXIM->PERIPH_ID_4, AXIM_PERIPH_ID_4_JEP106CON) >> AXIM_PERIPH_ID_4_JEP106CON_Pos);
}

/**
  * @brief  Get AXIM Part Number.
  * @rmtoll
  *  PERIPH_ID0          PARTNUM           LL_AXIM_GetPartNumber \n
  *  PERIPH_ID1          PARTNUM           LL_AXIM_GetPartNumber
  * @retval AXIM Part Number
  */
__STATIC_INLINE uint32_t LL_AXIM_GetPartNumber(void)
{
  uint32_t part_num = 0U;
  part_num = STM32_READ_BIT(AXIM->PERIPH_ID_0, AXIM_PERIPH_ID_0_PARTNUM);
  part_num |= (STM32_READ_BIT(AXIM->PERIPH_ID_1, AXIM_PERIPH_ID_1_PARTNUM) << 8U);
  return part_num;
}

/**
  * @brief  Get AXIM JEP-106 Identification.
  * @rmtoll
  *  PERIPH_ID1          JEP106ID           LL_AXIM_GetJEPID \n
  *  PERIPH_ID2          JEP106ID           LL_AXIM_GetJEPID
  * @retval AXIM JEP-106 Identification
  */
__STATIC_INLINE uint32_t LL_AXIM_GetJEPID(void)
{
  uint32_t jep_id = 0U;
  jep_id = STM32_READ_BIT(AXIM->PERIPH_ID_1, AXIM_PERIPH_ID_1_JEP106ID) >> AXIM_PERIPH_ID_1_JEP106ID_Pos;
  jep_id |= (STM32_READ_BIT(AXIM->PERIPH_ID_2, AXIM_PERIPH_ID_2_JEP106ID) << (AXIM_PERIPH_ID_1_JEP106ID_Pos));
  return jep_id;
}

/**
  * @brief  Get AXIM JEP Code Flag.
  * @rmtoll
  *  PERIPH_ID2          JEDEC           LL_AXIM_GetJEPCodeFlag
  * @retval AXIM JEP Code Flag
  */
__STATIC_INLINE uint32_t LL_AXIM_GetJEPCodeFlag(void)
{
  return (STM32_READ_BIT(AXIM->PERIPH_ID_2, AXIM_PERIPH_ID_2_JEDEC) >> AXIM_PERIPH_ID_2_JEDEC_Pos);
}

/**
  * @brief  Get AXIM Revision.
  * @rmtoll
  *  PERIPH_ID2          REVISION           LL_AXIM_GetRevision
  * @retval AXIM Revision
  */
__STATIC_INLINE uint32_t LL_AXIM_GetRevision(void)
{
  return (STM32_READ_BIT(AXIM->PERIPH_ID_2, AXIM_PERIPH_ID_2_REVISION) >> AXIM_PERIPH_ID_2_REVISION_Pos);
}

/**
  * @brief  Get AXIM Preamble bits.
  * @rmtoll
  *  COMP_ID0          PREAMBLE           LL_AXIM_GetPreamble \n
  *  COMP_ID1          PREAMBLE           LL_AXIM_GetPreamble \n
  *  COMP_ID2          PREAMBLE           LL_AXIM_GetPreamble \n
  *  COMP_ID3          PREAMBLE           LL_AXIM_GetPreamble
  * @retval AXIM Preamble
  */
__STATIC_INLINE uint32_t LL_AXIM_GetPreamble(void)
{
  uint32_t preamble;
  preamble = STM32_READ_BIT(AXIM->COMP_ID_0, AXIM_COMP_ID_0_PREAMBLE);
  preamble |= (STM32_READ_BIT(AXIM->COMP_ID_1, AXIM_COMP_ID_1_PREAMBLE) << 8U);
  preamble |= (STM32_READ_BIT(AXIM->COMP_ID_2, AXIM_COMP_ID_2_PREAMBLE) << 12U);
  preamble |= (STM32_READ_BIT(AXIM->COMP_ID_3, AXIM_COMP_ID_3_PREAMBLE) << 20U);
  return preamble;
}

/**
  * @brief  Get AXIM Component Class.
  * @rmtoll
  *  COMP_ID1          CLASS           LL_AXIM_GetComponentClass
  * @retval AXIM Class
  */
__STATIC_INLINE uint32_t LL_AXIM_GetComponentClass(void)
{
  return (STM32_READ_BIT(AXIM->COMP_ID_1, AXIM_COMP_ID_1_CLASS) >> AXIM_COMP_ID_1_CLASS_Pos);
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
#endif /* AXIM */
/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* STM32H7PXX_LL_AXIM_H */
