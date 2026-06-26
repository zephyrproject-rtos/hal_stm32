/**
  **********************************************************************************************************************
  * @file    stm32g5xx_ll_sbs.h
  * @brief   Header file of LL SBS module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software
  * component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32G5XX_LL_SBS_H
#define STM32G5XX_LL_SBS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */

#if defined (SBS)
/** @defgroup LL_SBS LL sbs
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup LL_Private_Constants LL private constants
  * @{
  */
#define LL_SBS_HDPL_INCREMENT_VALUE 0x6AU                                /*!< Define used for the HDPL increment */
#define LL_SBS_DBG_LOCK             0x00U                                /*!< Define used to lock debug */
#define LL_SBS_DBG_UNLOCK           (0xB4UL << SBS_DBGCR_DBG_UNLOCK_Pos) /*!< Define used to unlock debug */
#define LL_SBS_ACCESS_PORT_LOCK     0x00U                                /*!< Define used to lock access port */
#define LL_SBS_ACCESS_PORT_UNLOCK   0xB4U                                /*!< Define used to unlock access port */
#define LL_SBS_DBG_CONFIG_LOCK      0xC3U                                /*!< Define used to lock debug configuration */
#define LL_SBS_DBG_CONFIG_UNLOCK    0xB4U                                /*!< Define used to unlock debug configuration */
#define LL_SBS_AUTHN_DEBUG_SEC_NSEC 0xB4U                                /*!< Define used to open debug for secure and non-secure */
#define LL_SBS_AUTHN_DEBUG_NSEC     0x3CU                                /*!< Define used to open debug for non-secure only */
#define LL_SBS_FLASH_BANK_SWAP_LOCK  0xB4U                               /*!< Define used to lock flash bank swap */
#define LL_SBS_FLASH_BANK_SWAP_UNLOCK 0xC3U                              /*!< Define used to unlock flash bank swap */
#define LL_SBS_FLASH_BANK_NOT_SWAP  0xC3U                                /*!< Define used to disable swap flash bank mode */
#define LL_SBS_FLASH_BANK_SWAP      0xB4U                                /*!< Define used to enable swap flash bank mode */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SBS_LL_Exported_Constants LL SBS Constants
  * @{
  */

/** @defgroup SBS_LL_HDP_Level_Value SBS HDP Level Value
  * @{
  */
#define LL_SBS_HDPL_VALUE_0 0x000000B4U /*!< Hide protection level 0 */
#define LL_SBS_HDPL_VALUE_1 0x00000051U /*!< Hide protection level 1 */
#define LL_SBS_HDPL_VALUE_2 0x0000008AU /*!< Hide protection level 2 */
#define LL_SBS_HDPL_VALUE_3 0x0000006FU /*!< Hide protection level 3 */
/**
  * @}
  */

/** @defgroup SBS_LL_Next_HDP_Level_Selection  SBS Next HDP Level Selection
  * @{
  */
#define LL_SBS_HDP_OBK_0 0x00000000U               /*!< Index to add to the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
#define LL_SBS_HDP_OBK_1 SBS_NEXTHDPLCR_NEXTHDPL_0 /*!< Index to add to the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
#define LL_SBS_HDP_OBK_2 SBS_NEXTHDPLCR_NEXTHDPL_1 /*!< Index to add to the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
#define LL_SBS_HDP_OBK_3 SBS_NEXTHDPLCR_NEXTHDPL   /*!< Index to add to the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
/**
  * @}
  */

/** @defgroup SBS_LL_EPOCH_Selection  SBS EPOCH Selection
  * @{
  */
#define LL_SBS_EPOCH_SEL_NSEC 0x0UL                      /*!< EPOCH non secure selected               */
#define LL_SBS_EPOCH_SEL_SEC  SBS_EPOCHSELCR_EPOCH_SEL_0 /*!< EPOCH secure selected                   */
#define LL_SBS_EPOCH_SEL_CLR  SBS_EPOCHSELCR_EPOCH_SEL_1 /*!< EPOCH all zeros for PUF integrity check */
/**
  * @}
  */

/** @defgroup SBS_LL_EC_SECURE_ATTRIBUTES Secure attributes
  * @note Only available when system implements security (TZEN=1)
  * @{
  */
#define LL_SBS_SEC_ITEM_CLOCK    SBS_SECCFGR_SBSSEC      /*!< SBS clock configuration secure-only access     */
#define LL_SBS_SEC_ITEM_CLASSB   SBS_SECCFGR_CLASSBSEC   /*!< Class B configuration secure-only access       */
#define LL_SBS_SEC_ITEM_FPU      SBS_SECCFGR_FPUSEC      /*!< FPU configuration secure-only access           */
#define LL_SBS_SEC_ITEM_ALL      (SBS_SECCFGR_SBSSEC | SBS_SECCFGR_CLASSBSEC | \
                                  SBS_SECCFGR_FPUSEC) /*!< All security configuration items */

#define LL_SBS_ATTR_NSEC        0UL /*!< SBS non-secure attribute  */
#define LL_SBS_ATTR_SEC         1UL /*!< SBS secure attribute      */
/**
  * @}
  */

/** @defgroup SBS_LL_EC_DRIVE SBS FAST MODE PLUS
  * @{
  */
#define LL_SBS_DRIVE_PB6 SBS_PMCR_PB6_FMP      /*!< Enable Fast Mode Plus on PB6 */
#define LL_SBS_DRIVE_PB7 SBS_PMCR_PB7_FMP      /*!< Enable Fast Mode Plus on PB7 */
#define LL_SBS_DRIVE_PB9 SBS_PMCR_PB9_FMP      /*!< Enable Fast Mode Plus on PB9 */
#define LL_SBS_DRIVE_ALL (SBS_PMCR_PB6_FMP | \
                          SBS_PMCR_PB7_FMP | \
                          SBS_PMCR_PB9_FMP)    /*!< Enable all Fast Mode Plus driving capability */
/**
  * @}
  */

/** @defgroup SBS_LL_I2C_SMBUS  SBS Enable SMBus 3.0 on I2C peripheral
  * @{
  */
#define LL_SBS_I2C1_SMBUS    SBS_PMCR_I2C1SMB3EN /*!< Enable SMBUS 3.0 on I2C1 */
#if defined(I2C3)
#define LL_SBS_I2C3_SMBUS    SBS_PMCR_I2C3SMB3EN /*!< Enable SMBUS 3.0 on I2C3 */
#endif /* I2C3 */
#if defined(I2C4)
#define LL_SBS_I2C4_SMBUS    SBS_PMCR_I2C4SMB3EN /*!< Enable SMBUS 3.0 on I2C4 */
#endif /* I2C4 */
#if defined(I2C3) && defined(I2C4)
#define LL_SBS_I2C_SMBUS_ALL (SBS_PMCR_I2C1SMB3EN | SBS_PMCR_I2C3SMB3EN | \
                              SBS_PMCR_I2C4SMB3EN) /*!< Enable SMBUS 3.0 on all I2C */
#else
#define LL_SBS_I2C_SMBUS_ALL SBS_PMCR_I2C1SMB3EN /*!< Enable SMBUS 3.0 on all I2C */
#endif /* I2C3 */
/**
  * @}
  */

/** @defgroup LL_EC_FLOATING_POINT_UNIT_INTERRUPTs SBS floating point unit interrupts
  * @{
  */
#define LL_SBS_IT_FPU_IOC SBS_FPUIMR_FPU_IE_0                            /*!< Invalid operation interrupt */
#define LL_SBS_IT_FPU_DZC SBS_FPUIMR_FPU_IE_1                            /*!< Divide-by-zero interrupt    */
#define LL_SBS_IT_FPU_UFC SBS_FPUIMR_FPU_IE_2                            /*!< underflow interrupt         */
#define LL_SBS_IT_FPU_OFC SBS_FPUIMR_FPU_IE_3                            /*!< Overflow interrupt          */
#define LL_SBS_IT_FPU_IDC SBS_FPUIMR_FPU_IE_4                            /*!< Input abnormal interrupt    */
#define LL_SBS_IT_FPU_IXC SBS_FPUIMR_FPU_IE_5                            /*!< Inexact interrupt           */
#define LL_SBS_IT_FPU_ALL (SBS_FPUIMR_FPU_IE_0 | SBS_FPUIMR_FPU_IE_1 | \
                           SBS_FPUIMR_FPU_IE_2 | SBS_FPUIMR_FPU_IE_3 | \
                           SBS_FPUIMR_FPU_IE_4 | SBS_FPUIMR_FPU_IE_5)  /*!< All floating point unit interrupts */
/**
  * @}
  */

/** @defgroup SBS_LL_Erase_Status_Flags SBS Erase status Flags
  * @{
  */
#define LL_SBS_FLAG_IPMEE SBS_MESR_IPMEE                   /*!< ICACHE and PKA RAM erase status flag                 */
#define LL_SBS_FLAG_MCLR  SBS_MESR_MCLR                    /*!< SRAM1, SRAM2, SRAM3, ICACHE, DCACHE and PKA RAM flag */
#define LL_SBS_FLAG_ALL   (SBS_MESR_IPMEE | SBS_MESR_MCLR) /*!< All erase status flags                               */
/**
  * @}
  */

/** @defgroup LL_EC_CCELL_CODE SBS compensation cell Code source
  * @{
  */
#define LL_SBS_CCELL_VDDIO SBS_CCCSR_EN1 /*!< Compensation cell selection for VDDIO */
#define LL_SBS_CCELL_ALL   SBS_CCCSR_EN1 /*!< Compensation cell selection for ALL   */

#define LL_SBS_CCELL_CODE_DEFAULT 0U /*!< I/Os code from the cell (available in the SBS_CCVALR) */
#define LL_SBS_CCELL_CODE_CUSTOM  1U /*!< I/Os code from the SBS compensation cell code register (SBS_CCSWCR) */
/**
  * @}
  */

/** @defgroup LL_EC_CS1 SBS Vdd compensation cell Code selection
  * @{
  */
#define LL_SBS_CCELL_VDDIO_DEFAULT_CODE 0U            /*!< VDD I/Os code from the cell (available in the SBS_CCVALR) */
#define LL_SBS_CCELL_VDDIO_CUSTOM_CODE  SBS_CCCSR_CS1 /*!< VDD I/Os code from the SBS compensation cell code register (SBS_CCSWCR) */
/**
  * @}
  */

/** @defgroup SBS_LL_EC_TIMBREAK SBS TIMER BREAK
  * @{
  */
#define LL_SBS_DCACHE_ECC_DOUBLE_ERROR SBS_CFGR2_DCECCL  /*!< Enables and locks the DCACHE ECC double error signal with Break Input of TIM1/8/15/16/17                                            */
#define LL_SBS_FLASH_ECC_DOUBLE_ERROR  SBS_CFGR2_ECCL    /*!< Enables and locks the FLASH double ECC error signal with Break Input of TIM1/8/15/16/17                                             */
#define LL_SBS_PVD                     SBS_CFGR2_PVDL    /*!< Enables and locks the PVD connection with TIM1/8/15/16/17 Break Input and also the PVDE and PLS bits of the Power Control Interface */
#define LL_SBS_SRAM_ECC_DOUBLE_ERROR   SBS_CFGR2_SEL     /*!< Enables and locks the SRAM ECC double error signal with Break Input of TIM1/8/15/16/17                                              */
#define LL_SBS_LOCKUP_OUT              SBS_CFGR2_CLL     /*!< Enables and locks the LOCKUP (Hardfault) output of Cortex-M33 with Break Input of TIM1/15/16/17                                     */
#define LL_SBS_TIM_BREAK_INPUTS_ALL    (SBS_CFGR2_DCECCL | SBS_CFGR2_ECCL | \
                                        SBS_CFGR2_PVDL | SBS_CFGR2_SEL | \
                                        SBS_CFGR2_CLL)   /*!< Enables and locks the all with Break Input */
/**
  * @}
  */

/** @defgroup SBS_LL_Lock_Core_Register SBS Lock Core Register
  * @{
  */
#define LL_SBS_CPU_LOCK_VTOR     SBS_CNSLCKR_LOCKNSVTOR    /*!< VTOR register lock   */
#define LL_SBS_CPU_LOCK_AIRCR    SBS_CSLCKR_LOCKSVTAIRCR   /*!< AIRCR register lock */
#define LL_SBS_CPU_LOCK_MPU      SBS_CNSLCKR_LOCKNSMPU     /*!< MPU register lock  */
#define LL_SBS_CPU_LOCK_SAU      SBS_CSLCKR_LOCKSAU        /*!< SAU register lock  */
#define LL_SBS_CPU_LOCK_SEC_ALL  (SBS_CNSLCKR_LOCKNSVTOR | SBS_CNSLCKR_LOCKNSMPU \
                                  | SBS_CSLCKR_LOCKSAU)    /*!< All secure registers lock  */
#define LL_SBS_CPU_LOCK_NSEC_ALL (SBS_CNSLCKR_LOCKNSVTOR \
                                  | SBS_CNSLCKR_LOCKNSMPU) /*!< ALL non-secure registers lock */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SBS_LL_Exported_Macros LL SBS Macros
  * @{
  */

/** @defgroup SBS_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in SBS register.
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_SBS_WRITE_REG(reg, value) STM32_WRITE_REG(SBS->reg, (value))

/**
  * @brief  Read a value in SBS register.
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_SBS_READ_REG(reg) STM32_READ_REG(SBS->reg)
/**
  * @}
  */

/**
  * @}
 */
/* Exported functions --------------------------------------------------------*/

/** @defgroup SBS_LL_Exported_Functions LL SBS Functions
  * @{
  */

/** @defgroup SBS_LL_EF_HDPL_Management HDPL Management
  * @{
  */

/**
  * @brief  Increment by 1 the HDPL value.
  * @rmtoll
  *  HDPLCR     INCR_HDPL      LL_SBS_IncrementHDPLevel
  */
__STATIC_INLINE void LL_SBS_IncrementHDPLevel(void)
{
  STM32_MODIFY_REG(SBS->HDPLCR, SBS_HDPLCR_INCR_HDPL, LL_SBS_HDPL_INCREMENT_VALUE);
}

/**
  * @brief  Get the HDPL Value.
  * @rmtoll
  *  HDPLSR     HDPL      LL_SBS_GetHDPLevel
  * @retval  Returns the HDPL value
  *          This return value can be one of the following values:
  *           @arg @ref LL_SBS_HDPL_VALUE_0
  *           @arg @ref LL_SBS_HDPL_VALUE_1
  *           @arg @ref LL_SBS_HDPL_VALUE_2
  *           @arg @ref LL_SBS_HDPL_VALUE_3
  */
__STATIC_INLINE uint32_t LL_SBS_GetHDPLevel(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->HDPLSR, SBS_HDPLSR_HDPL));
}

/**
  * @brief  Set the OBK-HDPL Value.
  * @rmtoll
  *  NEXTHDPLCR     NEXTHDPL      LL_SBS_SetOBKHDPLevel
  * @param  value Value of increment to add to HDPL value to generate the OBK-HDPL.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_SBS_HDP_OBK_0
  *         @arg @ref LL_SBS_HDP_OBK_1
  *         @arg @ref LL_SBS_HDP_OBK_2
  *         @arg @ref LL_SBS_HDP_OBK_3
  */
__STATIC_INLINE void LL_SBS_SetOBKHDPLevel(uint32_t value)
{
  STM32_MODIFY_REG(SBS->NEXTHDPLCR, SBS_NEXTHDPLCR_NEXTHDPL, (uint32_t)(value));
}

/**
  * @brief  Get the OBK-HDPL Value.
  * @rmtoll
  *  NEXTHDPLCR     NEXTHDPL      LL_SBS_GetOBKHDPLevel
  * @retval  Returns the incremement to add to HDPL value to generate OBK-HDPL
  *          This return value can be one of the following values:
  *          @arg @ref LL_SBS_HDP_OBK_0
  *          @arg @ref LL_SBS_HDP_OBK_1
  *          @arg @ref LL_SBS_HDP_OBK_2
  *          @arg @ref LL_SBS_HDP_OBK_3
  */
__STATIC_INLINE  uint32_t LL_SBS_GetOBKHDPLevel(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->NEXTHDPLCR, SBS_NEXTHDPLCR_NEXTHDPL));
}

/**
  * @}
  */

/** @defgroup SBS_LL_EF_Debug_Control Debug Control
  * @{
  */

/**
  * @brief  Lock the access port.
  * @rmtoll
  *  DBGCR   AP_UNLOCK     LL_SBS_LockAPBAHBAccessPorts
  */
__STATIC_INLINE void LL_SBS_LockAPBAHBAccessPorts(void)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_AP_UNLOCK, LL_SBS_ACCESS_PORT_LOCK);
}

/**
  * @brief  Unlock the access port.
  * @rmtoll
  *  DBGCR   AP_UNLOCK     LL_SBS_UnlockAPBAHBAccessPorts
  */
__STATIC_INLINE void LL_SBS_UnlockAPBAHBAccessPorts(void)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_AP_UNLOCK, LL_SBS_ACCESS_PORT_UNLOCK);
}

/**
  * @brief  Check if the access port is unlocked.
  * @rmtoll
  *  DBGCR AP_UNLOCK     LL_SBS_IsLockedAPBAHBAccessPorts
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedAPBAHBAccessPorts(void)
{
  return ((STM32_READ_BIT(SBS->DBGCR, SBS_DBGCR_AP_UNLOCK) == LL_SBS_ACCESS_PORT_UNLOCK) ? 0UL : 1UL);
}

/**
  * @brief  Lock the debug.
  * @rmtoll
  *  DBGCR DBG_UNLOCK     LL_SBS_LockDebug
  */
__STATIC_INLINE void LL_SBS_LockDebug(void)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_UNLOCK, LL_SBS_DBG_LOCK);
}

/**
  * @brief  Unlock the debug.
  * @rmtoll
  *  DBGCR DBG_UNLOCK     LL_SBS_UnlockDebug
  */
__STATIC_INLINE void LL_SBS_UnlockDebug(void)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_UNLOCK, LL_SBS_DBG_UNLOCK);
}

/**
  * @brief  Check if the debug is unlocked.
  * @rmtoll
  *  DBGCR DBG_UNLOCK     LL_SBS_IsLockedDebug
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedDebug(void)
{
  return ((STM32_READ_BIT(SBS->DBGCR, SBS_DBGCR_DBG_UNLOCK) == LL_SBS_DBG_UNLOCK) ? 0UL : 1UL);
}

/**
  * @brief  Set the authenticated debug hide protection level.
  * @rmtoll
  *  DBGCR DBG_AUTH_HDPL     LL_SBS_SetAuthenticatedDbgHDPLevel
  * @param  level This parameter can be one of the following values:
  *         @arg @ref LL_SBS_HDPL_VALUE_1
  *         @arg @ref LL_SBS_HDPL_VALUE_2
  *         @arg @ref LL_SBS_HDPL_VALUE_3
  */
__STATIC_INLINE void LL_SBS_SetAuthenticatedDbgHDPLevel(uint32_t level)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_AUTH_HDPL, (level << SBS_DBGCR_DBG_AUTH_HDPL_Pos));
}

/**
  * @brief  Get current hide protection level.
  * @rmtoll
  *  DBGCR DBG_AUTH_HDPL     LL_SBS_GetAuthenticatedDbgHDPLevel
  * @retval Returned value is the hide protection level where the authenticated debug is opened:
  *         @arg @ref LL_SBS_HDPL_VALUE_1
  *         @arg @ref LL_SBS_HDPL_VALUE_2
  *         @arg @ref LL_SBS_HDPL_VALUE_3
  */
__STATIC_INLINE uint32_t LL_SBS_GetAuthenticatedDbgHDPLevel(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->DBGCR, SBS_DBGCR_DBG_AUTH_HDPL) >> SBS_DBGCR_DBG_AUTH_HDPL_Pos);
}

/**
  * @brief  Configure the authenticated debug security access.
  * @rmtoll
  *  DBGCR DBG_AUTH_SEC     LL_SBS_SetAuthenticatedDebugSecAttr
  * @param  security debug opening secure/non-secure or non-secure only
  *         This parameter can be one of the following values:
  *            @arg @ref LL_SBS_AUTHN_DEBUG_SEC_NSEC   debug opening for secure and non-secure.
  *            @arg @ref LL_SBS_AUTHN_DEBUG_NSEC       debug opening for non-secure only.
  */
__STATIC_INLINE void LL_SBS_SetAuthenticatedDebugSecAttr(uint32_t security)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_AUTH_SEC, (security << SBS_DBGCR_DBG_AUTH_SEC_Pos));
}

/**
  * @brief  Get the current value of the hide protection level.
  * @rmtoll
  *  DBGCR DBG_AUTH_SEC     LL_SBS_GetAuthenticatedDebugSecAttr
  * @note   This function can be only used when device state is Closed.
  * @retval Returned value can be one of the following values:
  *            @arg LL_SBS_AUTHN_DEBUG_SEC_NSEC: debug opening for secure and non-secure.
  *            @arg any other value: debug opening for non-secure only.
  */
__STATIC_INLINE uint32_t LL_SBS_GetAuthenticatedDebugSecAttr(void)
{
  return ((SBS->DBGCR & SBS_DBGCR_DBG_AUTH_SEC) >> SBS_DBGCR_DBG_AUTH_SEC_Pos);
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the secure access port.
  * @rmtoll
  *  DBGCR2 SEC_AP_UNLOCK     LL_SBS_LockSecAHBAccessPort
  */
__STATIC_INLINE void LL_SBS_LockSecAHBAccessPort(void)
{
  STM32_MODIFY_REG(SBS->DBGCR2, SBS_DBGCR2_SEC_AP_UNLOCK, LL_SBS_ACCESS_PORT_LOCK);
}

/**
  * @brief  Unlock the secure access port.
  * @rmtoll
  *  DBGCR2 SEC_AP_UNLOCK     LL_SBS_UnlockSecAHBAccessPort
  */
__STATIC_INLINE void LL_SBS_UnlockSecAHBAccessPort(void)
{
  STM32_MODIFY_REG(SBS->DBGCR2, SBS_DBGCR2_SEC_AP_UNLOCK, LL_SBS_ACCESS_PORT_UNLOCK);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the secure access port is unlocked.
  * @rmtoll
  *  DBGCR2 SEC_AP_UNLOCK     LL_SBS_IsLockedSecAHBAccessPort
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedSecAHBAccessPort(void)
{
  return ((STM32_READ_BIT(SBS->DBGCR2, SBS_DBGCR2_SEC_AP_UNLOCK) == LL_SBS_ACCESS_PORT_UNLOCK) ? 0UL : 1UL);
}

/**
  * @brief  Lock the debug configuration.
  * @rmtoll
  *  DBGLOCKR DBGCFG_LOCK     LL_SBS_LockDebugConfig
  */
__STATIC_INLINE void LL_SBS_LockDebugConfig(void)
{
  STM32_MODIFY_REG(SBS->DBGLOCKR, SBS_DBGLOCKR_DBGCFG_LOCK, LL_SBS_DBG_CONFIG_LOCK);
}

/**
  * @brief  Check if the debug configuration is locked.
  * @rmtoll
  *  DBGLOCKR DBGCFG_LOCK     LL_SBS_IsLockedDebugConfig
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedDebugConfig(void)
{
  return ((STM32_READ_BIT(SBS->DBGLOCKR, SBS_DBGLOCKR_DBGCFG_LOCK) != LL_SBS_DBG_CONFIG_UNLOCK) ? 1UL : 0UL);
}

/**
  * @}
  */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/** @defgroup SBS_LL_EF_RSS_Command RSS Command
  * @{
  */

/**
  * @brief  Set the RSS command.
  * @rmtoll
  *  RSSCMDR     RSSCMD      LL_SBS_SetRSSCommand
  * @param  rss_command
  */
__STATIC_INLINE void LL_SBS_SetRSSCommand(uint32_t rss_command)
{
  STM32_MODIFY_REG(SBS->RSSCMDR, SBS_RSSCMDR_RSSCMD, rss_command);
}

/**
  * @brief  Get the RSS command.
  * @rmtoll
  *  RSSCMDR     RSSCMD      LL_SBS_GetRSSCommand
  * @retval Returned the RSS command
  */
__STATIC_INLINE uint32_t LL_SBS_GetRSSCommand(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->RSSCMDR, SBS_RSSCMDR_RSSCMD));
}

/**
  * @}
  */
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/** @defgroup SBS_LL_EF_EPOCH_Selection_Control EPOCH Selection Control
  * @{
  */

/**
  * @brief  Select EPOCH security sent to SAES IP to encrypt/decrypt keys.
  * @rmtoll
  *  EPOCHSELCR     EPOCH_SEL      LL_SBS_SetEPOCHSelection
  * @param  selection: Select EPOCH security
  *         This parameter can be one of the following values:
  *         @arg @ref LL_SBS_EPOCH_SEL_SECURE
  *         @arg @ref LL_SBS_EPOCH_SEL_NONSECURE
  *         @arg @ref LL_SBS_EPOCH_SEL_CLR
  */
__STATIC_INLINE void LL_SBS_SetEPOCHSelection(uint32_t selection)
{
  STM32_MODIFY_REG(SBS->EPOCHSELCR, SBS_EPOCHSELCR_EPOCH_SEL, (uint32_t)(selection));
}

/**
  * @brief  Get EPOCH security selection.
  * @rmtoll
  *  EPOCHSELCR     EPOCH_SEL      LL_SBS_GetEPOCHSelection
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SBS_EPOCH_SEL_SECURE
  *         @arg @ref LL_SBS_EPOCH_SEL_NONSECURE
  *         @arg @ref LL_SBS_EPOCH_SEL_CLR
  */
__STATIC_INLINE uint32_t LL_SBS_GetEPOCHSelection(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->EPOCHSELCR, SBS_EPOCHSELCR_EPOCH_SEL));
}

/**
  * @}
  */

/** @defgroup SBS_LL_EF_Secure_Management Secure Management
  * @{
  */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the security access level attribute for item(s).
  * @rmtoll
  *  SECCFGR     SBSSEC         LL_SBS_SetSecAttr \n
  *  SECCFGR     CLASSBSEC      LL_SBS_SetSecAttr \n
  *  SECCFGR     FPUSEC         LL_SBS_SetSecAttr
  * @param  item This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_SEC_ITEM_CLOCK
  *         @arg @ref LL_SBS_SEC_ITEM_CLASSB
  *         @arg @ref LL_SBS_SEC_ITEM_FPU
  *         @arg @ref LL_SBS_SEC_ITEM_ALL
  * @param sec_attr This parameter can be one of the following values:
  *        @arg @ref LL_SBS_ATTR_SEC
  *        @arg @ref LL_SBS_ATTR_NSEC
  * @note Only available from secure and privileged state.
  */
__STATIC_INLINE void LL_SBS_SetSecAttr(uint32_t item, uint32_t sec_attr)
{
  STM32_MODIFY_REG(SBS->SECCFGR, item, (item & ((~sec_attr) + 1UL)));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the security access level attribute of an item.
  * @rmtoll
  *  SECCFGR     SBSSEC         LL_SBS_GetSecAttr \n
  *  SECCFGR     CLASSBSEC      LL_SBS_GetSecAttr \n
  *  SECCFGR     FPUSEC         LL_SBS_GetSecAttr
  * @param  item This parameter can be one of the following values:
  *         @arg @ref LL_SBS_SEC_ITEM_CLOCK
  *         @arg @ref LL_SBS_SEC_ITEM_CLASSB
  *         @arg @ref LL_SBS_SEC_ITEM_FPU
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SBS_ATTR_SEC
  *         @arg @ref LL_SBS_ATTR_NSEC
  */
__STATIC_INLINE uint32_t LL_SBS_GetSecAttr(uint32_t item)
{
  return ((STM32_READ_BIT(SBS->SECCFGR, item) == (item)) ? LL_SBS_ATTR_SEC : LL_SBS_ATTR_NSEC);
}

/**
  * @}
  */

/** @defgroup SBS_LL_EF_FPM_Management FPM Management
  * @{
  */

/**
  * @brief  Enable the fast mode plus driving capability.
  * @rmtoll
  *  PMCR     PBx_FMP   LL_SBS_EnableFastModePlus
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_DRIVE_PB6
  *         @arg @ref LL_SBS_DRIVE_PB7
  *         @arg @ref LL_SBS_DRIVE_PB9
  *         @arg @ref LL_SBS_DRIVE_ALL
  */
__STATIC_INLINE void LL_SBS_EnableFastModePlus(uint32_t fast_mode_plus)
{
  STM32_SET_BIT(SBS->PMCR, fast_mode_plus);
}

/**
  * @brief  Disable the fast mode plus driving capability.
  * @rmtoll
  *  PMCR     PBx_FMP   LL_SBS_DisableFastModePlus
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_DRIVE_PB6
  *         @arg @ref LL_SBS_DRIVE_PB7
  *         @arg @ref LL_SBS_DRIVE_PB9
  *         @arg @ref LL_SBS_DRIVE_ALL
  */
__STATIC_INLINE void LL_SBS_DisableFastModePlus(uint32_t fast_mode_plus)
{
  STM32_CLEAR_BIT(SBS->PMCR, fast_mode_plus);
}

/**
  * @brief  Check if fast mode plus is enabled or disabled.
  * @rmtoll
  *  PMCR   PBx_FMP   LL_SBS_IsEnabledFastModePlus
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_DRIVE_PB6
  *         @arg @ref LL_SBS_DRIVE_PB7
  *         @arg @ref LL_SBS_DRIVE_PB9
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledFastModePlus(uint32_t fast_mode_plus)
{
  return ((STM32_READ_BIT(SBS->PMCR, fast_mode_plus) == fast_mode_plus) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_LL_EF_SMBUS_Management SMBUS Management
  * @{
  */

/**
  * @brief Enable SMBUS on I2Cx.
  * @rmtoll
  *  PMCR     I2CxSMB3EN      LL_SBS_EnableI2CSMBUS
  * @param  index: I2C peripheral instance
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_I2C1_SMBUS
  *         @arg @ref LL_SBS_I2C3_SMBUS (*)
  *         @arg @ref LL_SBS_I2C4_SMBUS (*)
  *         @arg @ref LL_SBS_I2C_SMBUS_ALL
  * @note   (*) Availability depends on devices.
  */
__STATIC_INLINE  void LL_SBS_EnableI2CSMBUS(uint32_t index)
{
  STM32_SET_BIT(SBS->PMCR, index);
}

/**
  * @brief  Disable SMBUS on I2Cx.
  * @rmtoll
  *  PMCR     I2CxSMB3EN      LL_SBS_DisableI2CSMBUS
  * @param  index: I2C peripheral instance
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_I2C1_SMBUS
  *         @arg @ref LL_SBS_I2C3_SMBUS (*)
  *         @arg @ref LL_SBS_I2C4_SMBUS (*)
  *         @arg @ref LL_SBS_I2C_SMBUS_ALL
  * @note   (*) Availability depends on devices.

  */
__STATIC_INLINE  void LL_SBS_DisableI2CSMBUS(uint32_t index)
{
  STM32_CLEAR_BIT(SBS->PMCR, index);
}

/**
  * @brief  Check if the SMBUS on I2Cx. is enabled.
  * @rmtoll
  *  PMCR     I2CxSMB3EN      LL_SBS_IsEnabledI2CSMBUS
  * @param  index: I2C peripheral instance
  *         This parameter can be one of the following values:
  *         @arg @ref LL_SBS_I2C1_SMBUS
  *         @arg @ref LL_SBS_I2C3_SMBUS (*)
  *         @arg @ref LL_SBS_I2C4_SMBUS (*)
  * @note   (*) Availability depends on devices.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE  uint32_t LL_SBS_IsEnabledI2CSMBUS(uint32_t index)
{
  return ((STM32_READ_BIT(SBS->PMCR, index) == index) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_LL_EF_FPUIT_Management FPUIT Management
  * @{
  */

/**
  * @brief  Enable floating point unit interrupts bits.
  * @rmtoll
  *  FPUIMR FPU_IE_0   LL_SBS_EnableFPUIT \n
  *  FPUIMR FPU_IE_1   LL_SBS_EnableFPUIT \n
  *  FPUIMR FPU_IE_2   LL_SBS_EnableFPUIT \n
  *  FPUIMR FPU_IE_3   LL_SBS_EnableFPUIT \n
  *  FPUIMR FPU_IE_4   LL_SBS_EnableFPUIT \n
  *  FPUIMR FPU_IE_5   LL_SBS_EnableFPUIT
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_IT_FPU_IOC
  *         @arg @ref LL_SBS_IT_FPU_DZC
  *         @arg @ref LL_SBS_IT_FPU_UFC
  *         @arg @ref LL_SBS_IT_FPU_OFC
  *         @arg @ref LL_SBS_IT_FPU_IDC
  *         @arg @ref LL_SBS_IT_FPU_IXC
  *         @arg @ref LL_SBS_IT_FPU_ALL
  */
__STATIC_INLINE void LL_SBS_EnableFPUIT(uint32_t floating_point)
{
  STM32_SET_BIT(SBS->FPUIMR, floating_point);
}

/**
  * @brief  Disable floating point unit interrupts bits.
  * @rmtoll
  *  FPUIMR FPU_IE_0   LL_SBS_DisableFPUIT \n
  *  FPUIMR FPU_IE_1   LL_SBS_DisableFPUIT \n
  *  FPUIMR FPU_IE_2   LL_SBS_DisableFPUIT \n
  *  FPUIMR FPU_IE_3   LL_SBS_DisableFPUIT \n
  *  FPUIMR FPU_IE_4   LL_SBS_DisableFPUIT \n
  *  FPUIMR FPU_IE_5   LL_SBS_DisableFPUIT
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_IT_FPU_IOC
  *         @arg @ref LL_SBS_IT_FPU_DZC
  *         @arg @ref LL_SBS_IT_FPU_UFC
  *         @arg @ref LL_SBS_IT_FPU_OFC
  *         @arg @ref LL_SBS_IT_FPU_IDC
  *         @arg @ref LL_SBS_IT_FPU_IXC
  *         @arg @ref LL_SBS_IT_FPU_ALL
  */
__STATIC_INLINE void LL_SBS_DisableFPUIT(uint32_t floating_point)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, floating_point);
}

/**
  * @brief  Check if floating point unit interrupts bits is enabled.
  * @rmtoll
  *  FPUIMR FPU_IE_0   LL_SBS_IsEnabledFPUIT \n
  *  FPUIMR FPU_IE_1   LL_SBS_IsEnabledFPUIT \n
  *  FPUIMR FPU_IE_2   LL_SBS_IsEnabledFPUIT \n
  *  FPUIMR FPU_IE_3   LL_SBS_IsEnabledFPUIT \n
  *  FPUIMR FPU_IE_4   LL_SBS_IsEnabledFPUIT \n
  *  FPUIMR FPU_IE_5   LL_SBS_IsEnabledFPUIT
  * @param  floating_point This parameter can be one of the following values:
  *         @arg @ref LL_SBS_IT_FPU_IOC
  *         @arg @ref LL_SBS_IT_FPU_DZC
  *         @arg @ref LL_SBS_IT_FPU_UFC
  *         @arg @ref LL_SBS_IT_FPU_OFC
  *         @arg @ref LL_SBS_IT_FPU_IDC
  *         @arg @ref LL_SBS_IT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledFPUIT(uint32_t floating_point)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, floating_point) == floating_point) ? 1UL : 0UL);
}

/**
  * @brief  Enable Floating Point Unit Invalid operation Interrupt.
  * @rmtoll
  *  FPUIMR   FPU_IE_0      LL_SBS_EnableIT_FPU_IOC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IOC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Enable Floating Point Unit Divide-by-zero Interrupt.
  * @rmtoll
  *  FPUIMR   FPU_IE_1      LL_SBS_EnableIT_FPU_DZC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_DZC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Enable Floating Point Unit Underflow Interrupt.
  * @rmtoll
  *  FPUIMR   FPU_IE_2      LL_SBS_EnableIT_FPU_UFC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_UFC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Enable Floating Point Unit Overflow Interrupt.
  * @rmtoll
  *  FPUIMR   FPU_IE_3      LL_SBS_EnableIT_FPU_OFC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_OFC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Enable Floating Point Unit Input denormal Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_4      LL_SBS_EnableIT_FPU_IDC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IDC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Enable Floating Point Unit Inexact Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_5      LL_SBS_EnableIT_FPU_IXC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IXC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Disable Floating Point Unit Invalid operation Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_0      LL_SBS_DisableIT_FPU_IOC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IOC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Disable Floating Point Unit Divide-by-zero Interrupt.
  * @rmtoll
  *  FPUIMR      FPU_IE_1      LL_SBS_DisableIT_FPU_DZC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_DZC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Disable Floating Point Unit Underflow Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_2      LL_SBS_DisableIT_FPU_UFC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_UFC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Disable Floating Point Unit Overflow Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_3      LL_SBS_DisableIT_FPU_OFC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_OFC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Disable Floating Point Unit Input denormal Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_4      LL_SBS_DisableIT_FPU_IDC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IDC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Disable Floating Point Unit Inexact Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_5      LL_SBS_DisableIT_FPU_IXC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IXC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Check if Floating Point Unit Invalid operation Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_0      LL_SBS_IsEnabledIT_FPU_IOC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IOC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0) == SBS_FPUIMR_FPU_IE_0) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Divide-by-zero Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_1      LL_SBS_IsEnabledIT_FPU_DZC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_DZC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1) == SBS_FPUIMR_FPU_IE_1) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Underflow Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_2      LL_SBS_IsEnabledIT_FPU_UFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_UFC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2) == SBS_FPUIMR_FPU_IE_2) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Overflow Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_3      LL_SBS_IsEnabledIT_FPU_OFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_OFC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3) == SBS_FPUIMR_FPU_IE_3) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Input abnormal Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_4      LL_SBS_IsEnabledIT_FPU_IDC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IDC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4) == SBS_FPUIMR_FPU_IE_4) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Inexact Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_5      LL_SBS_IsEnabledIT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IXC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5) == SBS_FPUIMR_FPU_IE_5) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_LL_EF_ERASE_MEMORIE_STATUS SBS ERASE MEMORIE STATUS
  * @{
  */

/**
  * @brief  Clear Status of End of Erase for ICACHE and PKA RAMs.
  * @rmtoll
  *  MESR   IPMEE    LL_SBS_ClearFlag_IPMEE
  */
__STATIC_INLINE void LL_SBS_ClearFlag_IPMEE(void)
{
  STM32_SET_BIT(SBS->MESR, SBS_MESR_IPMEE);
}

/**
  * @brief  Get Status of End of Erase for ICACHE and PKA RAMs.
  * @rmtoll
  *  MESR   IPMEE    LL_SBS_IsActiveFlag_IPMEE
  * @retval retrieve the state of the IPMEE flag (1U or 0U).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag_IPMEE(void)
{
  return ((STM32_READ_BIT(SBS->MESR, SBS_MESR_IPMEE) == SBS_MESR_IPMEE) ? 1UL : 0UL);
}

/**
  * @brief  Clear Status of End of Erase after reset  for SRAM2, BKPRAM, ICACHE, DCACHE,PKA rams.
  * @rmtoll
  *  MESR   MCLR    LL_SBS_ClearFlag_MCLR
  */
__STATIC_INLINE void LL_SBS_ClearFlag_MCLR(void)
{
  STM32_SET_BIT(SBS->MESR, SBS_MESR_MCLR);
}

/**
  * @brief  Get Status of End of Erase after reset  for SRAM2, BKPRAM, ICACHE, DCACHE,PKA rams.
  * @rmtoll
  *  MESR   MCLR    LL_SBS_IsActiveFlag_MCLR
  * @retval retrieve the state of the MCLR flag (1U or 0U).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag_MCLR(void)
{
  return ((STM32_READ_BIT(SBS->MESR, SBS_MESR_MCLR) == SBS_MESR_MCLR) ? 1UL : 0UL);
}

/**
  * @brief Clear the SBS memories erase status pending flag(s).
  * @rmtoll
  *  MESR   IPMEE    LL_SBS_ClearFlag \n
  *  MESR   MCLR     LL_SBS_ClearFlag
  * @param flag This parameter can be one or a combination of the following values:
  *        @arg @ref LL_SBS_FLAG_IPMEE
  *        @arg @ref LL_SBS_FLAG_MCLR
  *        @arg @ref LL_SBS_FLAG_ALL
  */
__STATIC_INLINE void LL_SBS_ClearFlag(uint32_t flag)
{
  STM32_SET_BIT(SBS->MESR, flag);
}

/**
  * @brief Check if an SBS memories erase status flag is active or not.
  * @rmtoll
  *  MESR   IPMEE    LL_SBS_IsActiveFlag \n
  *  MESR   MCLR     LL_SBS_IsActiveFlag
  * @param flag This parameter can be one of the following values:
  *        @arg @ref LL_SBS_FLAG_IPMEE
  *        @arg @ref LL_SBS_FLAG_MCLR
  * @retval retrieve the state of the selected memory flag (1U or 0U).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag(uint32_t flag)
{
  return ((STM32_READ_BIT(SBS->MESR, flag) == flag) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup SBS_LL_EF_COMPENSATION Compensation Cell Control
  * @{
  */

/**
  * @brief  Set the compensation cell code.
  * @rmtoll
  *  CCCSR    CSx  LL_SBS_SetCompensationCellCodeSrc
  * @param  comp_cell This parameter can be one of the following value:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @param  code_source: This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_CODE_DEFAULT
  *         @arg @ref LL_SBS_CCELL_CODE_CUSTOM
  */
__STATIC_INLINE void LL_SBS_SetCompensationCellCodeSrc(uint32_t comp_cell, uint32_t code_source)
{
  STM32_ATOMIC_MODIFY_REG_32(SBS->CCCSR, (comp_cell << 1U), (code_source * (comp_cell << 1U)));
}

/**
  * @brief  Get the compensation cell code.
  * @rmtoll
  *  CCCSR    CSx    LL_SBS_GetCompensationCellCodeSrc
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval Returned value can be one of the following values:
  *   @arg LL_SBS_CCELL_CODE_DEFAULT : Selected Code is from the cell (available in the SBS_CCVALR)
  *   @arg LL_SBS_CCELL_CODE_CUSTOM  : Selected Code is from the SBS compensation
  *                                           cell code register (SBS_CCSWCR)
  */
__STATIC_INLINE uint32_t LL_SBS_GetCompensationCellCodeSrc(uint32_t comp_cell)
{
  return (STM32_READ_BIT(SBS->CCCSR,
                         (SBS_CCCSR_CS1 << STM32_POSITION_VAL(comp_cell))) >> STM32_POSITION_VAL(comp_cell << 1U));
}

/**
  * @brief  Set the compensation cell code selection of GPIO supplied by VDD.
  * @rmtoll
  *  CCCSR   CS1    LL_SBS_SetVddIOCompensationCellCodeSource
  * @param  code_source: Select the code to be applied for the Vdd compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SBS_CCELL_VDDIO_DEFAULT_CODE : Select Code from the cell (available in the SBS_CCVALR)
  *   @arg LL_SBS_CCELL_VDDIO_CUSTOM_CODE  : Select Code from the SBS compensation cell code
  *                                                  register (SBS_CCSWCR)
  */
__STATIC_INLINE void LL_SBS_SetVddIOCompensationCellCodeSource(uint32_t code_source)
{
  STM32_ATOMIC_SET_BIT_32(SBS->CCCSR, code_source);
}

/**
  * @brief  Get the compensation cell code selection of GPIO supplied by VDD.
  * @rmtoll
  *  CCCSR   CS1    LL_SBS_GetVddIOCompensationCellCodeSource
  * @retval Returned value can be one of the following values:
  *   @arg LL_SBS_CCELL_VDDIO_DEFAULT_CODE : Select Code from the cell (available in the SBS_CCVALR)
  *   @arg LL_SBS_CCELL_VDDIO_CUSTOM_CODE  : Select Code from the SBS compensation cell code
  *                                                  register (SBS_CCSWCR)
  */
__STATIC_INLINE uint32_t LL_SBS_GetVddIOCompensationCellCodeSource(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->CCCSR, SBS_CCCSR_CS1));
}

/**
  * @brief  Enable the Compensation Cell.
  * @rmtoll
  *  CCCSR   ENX      LL_SBS_EnableCompensationCell
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  */
__STATIC_INLINE void LL_SBS_EnableCompensationCell(uint32_t comp_cell)
{
  STM32_ATOMIC_SET_BIT_32(SBS->CCCSR, comp_cell);
}

/**
  * @brief  Disable the Compensation Cell.
  * @rmtoll
  *  CCCSR   ENX       LL_SBS_DisableCompensationCell
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  */
__STATIC_INLINE void LL_SBS_DisableCompensationCell(uint32_t comp_cell)
{
  STM32_ATOMIC_CLEAR_BIT_32(SBS->CCCSR, comp_cell);
}

/**
  * @brief  Check if the Compensation Cell is enable.
  * @rmtoll
  *  CCCSR   ENx     LL_SBS_IsEnabledCompensationCell
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledCompensationCell(uint32_t comp_cell)
{
  return ((STM32_READ_BIT(SBS->CCCSR, comp_cell) == comp_cell) ? 1U : 0U);
}

/**
  * @brief  Enable the Compensation Cell of GPIO supplied by VDD.
  * @rmtoll
  *  CCCSR   EN1    LL_SBS_EnableVddIOCompensationCell
  * @note   The vdd compensation cell can be used only when the device supply
  *         voltage ranges from 1.71 to 3.6 V
  */
__STATIC_INLINE void LL_SBS_EnableVddIOCompensationCell(void)
{
  STM32_ATOMIC_SET_BIT_32(SBS->CCCSR, SBS_CCCSR_EN1);
}

/**
  * @brief  Disable the Compensation Cell of GPIO supplied by VDD.
  * @rmtoll
  *  CCCSR   EN1    LL_SBS_DisableVddIOCompensationCell
  * @note   The Vdd compensation cell can be used only when the device supply
  *         voltage ranges from 1.71 to 3.6 V
  */
__STATIC_INLINE void LL_SBS_DisableVddIOCompensationCell(void)
{
  STM32_ATOMIC_CLEAR_BIT_32(SBS->CCCSR, SBS_CCCSR_EN1);
}

/**
  * @brief  Check if the Compensation Cell of GPIO supplied by VDD is enabled.
  * @rmtoll
  *  CCCSR   EN1    LL_SBS_IsEnabledVddIOCompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledVddIOCompensationCell(void)
{
  return ((STM32_READ_BIT(SBS->CCCSR, SBS_CCCSR_EN1) == SBS_CCCSR_EN1) ? 1UL : 0UL);
}

/**
  * @brief  Get the PMOS transistor of the compensation cell value.
  * @rmtoll
  *  CCVALR    APSRCx    LL_SBS_GetPMOSCompensationCellValue
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval Returned value of the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSCompensationCellValue(uint32_t comp_cell)
{
  return STM32_READ_BIT(SBS->CCVALR, SBS_CCVALR_APSRC1) >> (STM32_POSITION_VAL(comp_cell << 1U) * 4U);
}

/**
  * @brief  Get the NMOS transistor of the compensation cell value.
  * @rmtoll
  *  CCVALR    ANSRC1x    LL_SBS_GetNMOSCompensationCellValue
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval Returned value of the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSCompensationCellValue(uint32_t comp_cell)
{
  return STM32_READ_BIT(SBS->CCVALR, SBS_CCVALR_ANSRC1) >> (STM32_POSITION_VAL(comp_cell) * 4U);
}

/**
  * @brief  Get the compensation cell value of the GPIO PMOS transistor supplied by VDD.
  * @rmtoll
  *  CCVALR    APSRC1   LL_SBS_GetPMOSVddIOCompensationCellValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSVddIOCompensationCellValue(void)
{
  return STM32_READ_BIT(SBS->CCVALR, SBS_CCVALR_APSRC1);
}

/**
  * @brief  Get the compensation cell value of the GPIO NMOS transistor supplied by VDD.
  * @rmtoll
  *  CCVALR    ANSRC1   LL_SBS_GetNMOSVddIOCompensationCellValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSVddIOCompensationCellValue(void)
{
  return STM32_READ_BIT(SBS->CCVALR, SBS_CCVALR_ANSRC1);
}

/**
  * @brief  Set the compensation cell code of PMOS transistor.
  * @rmtoll
  *  CCSWCR     APSRC1     LL_SBS_SetPMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @param  pmos_code PMOS compensation code
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  */
__STATIC_INLINE void LL_SBS_SetPMOSCompensationCellCode(uint32_t comp_cell, uint32_t pmos_code)
{
  STM32_ATOMIC_MODIFY_REG_32(SBS->CCSWCR, SBS_CCSWCR_SW_APSRC1,
                             (pmos_code << (STM32_POSITION_VAL(comp_cell << 1U) * 4U)));
}

/**
  * @brief  Get the compensation cell code of PMOS transistor.
  * @rmtoll
  *  CCSWCR     APSRC1     LL_SBS_GetPMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  * @retval Returned value of the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSCompensationCellCode(uint32_t comp_cell)
{
  return (STM32_READ_BIT(SBS->CCSWCR, (SBS_CCSWCR_SW_APSRC1 << (STM32_POSITION_VAL(comp_cell) * 4U))));
}

/**
  * @brief  Set the compensation cell code of NMOS transistor.
  * @rmtoll
  *  CCSWCR     ANSRC1     LL_SBS_SetNMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @param  nmos_code PMOS compensation code
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  */
__STATIC_INLINE void LL_SBS_SetNMOSCompensationCellCode(uint32_t comp_cell, uint32_t nmos_code)
{
  STM32_ATOMIC_MODIFY_REG_32(SBS->CCSWCR, SBS_CCSWCR_SW_ANSRC1, (nmos_code << (STM32_POSITION_VAL(comp_cell) * 4U)));
}

/**
  * @brief  Get the NMOS transistor of the compensation cell value.
  * @rmtoll
  *  CCSWCR     ANSRC1     LL_SBS_GetNMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @note   This code is applied to the NMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  * @retval Returned value of the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSCompensationCellCode(uint32_t comp_cell)
{
  return (STM32_READ_BIT(SBS->CCSWCR, (SBS_CCSWCR_SW_ANSRC1 << (STM32_POSITION_VAL(comp_cell) * 4U))));
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS and NMOS transistor supplied by VDD.
  * @rmtoll
  *  CCSWCR     ANSRC1     LL_SBS_SetxMOSVddIOCompensationCellCode \n
  *  CCSWCR     APSRC1     LL_SBS_SetxMOSVddIOCompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set (value between 0x0 and 0xFU)
  * @param  nmos_code NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set (value between 0x0 and 0xFU)
  */
__STATIC_INLINE void LL_SBS_SetxMOSVddIOCompensationCellCode(uint32_t pmos_code, uint32_t nmos_code)
{
  STM32_MODIFY_REG(SBS->CCSWCR, (SBS_CCSWCR_SW_APSRC1 | SBS_CCSWCR_SW_ANSRC1),
                   ((pmos_code << SBS_CCSWCR_SW_APSRC1_Pos) | (nmos_code << SBS_CCSWCR_SW_ANSRC1_Pos)));
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS transistor supplied by VDD.
  * @rmtoll
  *  CCSWCR     APSRC1     LL_SBS_SetPMOSVddIOCompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set (value between 0x0 and 0xFU)
  */
__STATIC_INLINE void LL_SBS_SetPMOSVddIOCompensationCellCode(uint32_t pmos_code)
{
  STM32_MODIFY_REG(SBS->CCSWCR, SBS_CCSWCR_SW_APSRC1, pmos_code << SBS_CCSWCR_SW_APSRC1_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO PMOS transistor supplied by VDD.
  * @rmtoll
  *  CCSWCR     APSRC1     LL_SBS_GetPMOSVddIOCompensationCellCode
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSVddIOCompensationCellCode(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->CCSWCR, SBS_CCSWCR_SW_APSRC1));
}

/**
  * @brief  Set the compensation cell code of the GPIO NMOS transistor supplied by VDD.
  * @rmtoll
  *  CCSWCR     APSRC1     LL_SBS_SetNMOSVddIOCompensationCellCode
  * @param  nmos_code NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set (value between 0x0 and 0xFU)
  */
__STATIC_INLINE void LL_SBS_SetNMOSVddIOCompensationCellCode(uint32_t nmos_code)
{
  STM32_MODIFY_REG(SBS->CCSWCR, SBS_CCSWCR_SW_ANSRC1, nmos_code << SBS_CCSWCR_SW_ANSRC1_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO NMOS transistor supplied by VDD.
  * @rmtoll
  *  CCSWCR     ANSRC1     LL_SBS_GetNMOSVddIOCompensationCellCode
  * @retval Returned value is the Vdd compensation cell code for NMOS transistors
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSVddIOCompensationCellCode(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->CCSWCR, SBS_CCSWCR_SW_ANSRC1));
}

/**
  * @brief  Get Compensation Cell ready Flag of GPIO supplied by VDD.
  * @rmtoll
  *  CCCSR     RDY1     LL_SBS_IsActiveFlag_RDY1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag_RDY1(void)
{
  return ((STM32_READ_BIT(SBS->CCCSR, SBS_CCCSR_RDY1) == (SBS_CCCSR_RDY1)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_LL_EF_TIM_Break_Management TIM Break Management
  * @{
  */

/**
  * @brief  Set connections to TIM1/8/15/16/17 break inputs.
  * @rmtoll
  *  CFGR2     DCECCL     LL_SBS_EnableTIMBreakInputs \n
  *  CFGR2     CLL        LL_SBS_EnableTIMBreakInputs \n
  *  CFGR2     SEL        LL_SBS_EnableTIMBreakInputs \n
  *  CFGR2     PVDL       LL_SBS_EnableTIMBreakInputs \n
  *  CFGR2     ECCL       LL_SBS_EnableTIMBreakInputs
  * @param  break_input This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_DCACHE_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_PVD
  *         @arg @ref LL_SBS_SRAM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_LOCKUP_OUT
  */
__STATIC_INLINE void LL_SBS_EnableTIMBreakInputs(uint32_t break_input)
{
  STM32_SET_BIT(SBS->CFGR2, break_input);
}

/**
  * @brief  Clear connections to TIM1/8/15/16/17 break inputs.
  * @rmtoll
  *  CFGR2     ECCL     LL_SBS_DisableTIMBreakInputs
  * @param  break_input This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_FLASH_ECC_DOUBLE_ERROR
  */
__STATIC_INLINE void LL_SBS_DisableTIMBreakInputs(uint32_t break_input)
{
  STM32_CLEAR_BIT(SBS->CFGR2, break_input);
}

/**
  * @brief  Get connections to TIM1/8/15/16/17 break inputs.
  * @rmtoll
  *  CFGR2     DCECCL     LL_SBS_IsEnabledTIMBreakInputs \n
  *  CFGR2     CLL        LL_SBS_IsEnabledTIMBreakInputs \n
  *  CFGR2     SPL        LL_SBS_IsEnabledTIMBreakInputs \n
  *  CFGR2     PVDL       LL_SBS_IsEnabledTIMBreakInputs \n
  *  CFGR2     ECCL       LL_SBS_IsEnabledTIMBreakInputs
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_SBS_DCACHE_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_PVD
  *         @arg @ref LL_SBS_SRAM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_LOCKUP_OUT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledTIMBreakInputs(uint32_t break_input)
{
  return ((STM32_READ_BIT(SBS->CFGR2, break_input) == (break_input)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_LL_EF_Lock_Management Lock Management
  * @{
  */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the AIRCR registers.
  * @rmtoll
  *  CSLCKR        LOCKSVTAIRCR       LL_SBS_LockAIRCR
  */
__STATIC_INLINE void LL_SBS_LockAIRCR(void)
{
  STM32_SET_BIT(SBS->CSLCKR, SBS_CSLCKR_LOCKSVTAIRCR);
}

/**
  * @brief  Check if the AIRCR registers are locked.
  * @rmtoll
  *  CSLCKR        LOCKSVTAIRCR       LL_SBS_IsLockedAIRCR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedAIRCR(void)
{
  return ((STM32_READ_BIT(SBS->CSLCKR, SBS_CSLCKR_LOCKSVTAIRCR) == SBS_CSLCKR_LOCKSVTAIRCR) ? 1UL : 0UL);
}

/**
  * @brief  Lock the SAU registers.
  * @rmtoll
  *  CSLCKR        LOCKSAU        LL_SBS_LockSAU
  */
__STATIC_INLINE void LL_SBS_LockSAU(void)
{
  STM32_SET_BIT(SBS->CSLCKR, SBS_CSLCKR_LOCKSAU);
}

/**
  * @brief  Check if the SAU registers are locked.
  * @rmtoll
  *  CSLCKR        LOCKSAU        LL_SBS_IsLockedSAU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedSAU(void)
{
  return ((STM32_READ_BIT(SBS->CSLCKR, SBS_CSLCKR_LOCKSAU) == SBS_CSLCKR_LOCKSAU) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Lock the MPU registers.
  * @rmtoll
  *  CNSLCKR       LOCKNSMPU          LL_SBS_LockMPU \n
  *  CSLCKR        LOCKSMPU           LL_SBS_LockMPU
  * @note   Setting lock secure MPU depends on the privilege mode in secure/non-secure code.
  */
__STATIC_INLINE void LL_SBS_LockMPU(void)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(SBS->CSLCKR, SBS_CSLCKR_LOCKSMPU);
#else
  STM32_SET_BIT(SBS->CNSLCKR, SBS_CNSLCKR_LOCKNSMPU);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Check if the MPU registers are locked.
  * @rmtoll
  *  CNSLCKR       LOCKNSMPU          LL_SBS_IsLockedMPU \n
  *  CSLCKR        LOCKSMPU           LL_SBS_IsLockedMPU
  * @note   Setting lock MPU depends on privilege mode in secure/non-secure code.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedMPU(void)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(SBS->CSLCKR, SBS_CSLCKR_LOCKSMPU) == SBS_CSLCKR_LOCKSMPU) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(SBS->CNSLCKR, SBS_CNSLCKR_LOCKNSMPU) == SBS_CNSLCKR_LOCKNSMPU) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the non-secure MPU registers.
  * @rmtoll
  *  CNSLCKR       LOCKNSMPU          LL_SBS_NS_LockMPU
  * @note   Setting lock non-secure MPU depends on privilege mode in secure/non-secure code
  */
__STATIC_INLINE void LL_SBS_NS_LockMPU(void)
{
  STM32_SET_BIT(SBS->CNSLCKR, SBS_CNSLCKR_LOCKNSMPU);
}

/**
  * @brief  Check if the non-secure MPU registers are locked.
  * @rmtoll
  *  CNSLCKR       LOCKNSMPU          LL_SBS_NS_IsLockedMPU
  * @note   Setting lock non-secure MPU depends on privilege mode in secure/non-secure code
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_NS_IsLockedMPU(void)
{
  return ((STM32_READ_BIT(SBS->CNSLCKR, SBS_CNSLCKR_LOCKNSMPU) == SBS_CNSLCKR_LOCKNSMPU) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Lock  the secure/non-secure VTOR register.
  * @rmtoll
  *  CNSLCKR       LOCKNSVTOR         LL_SBS_LockVTOR \n
  *  CSLCKR        LOCKSVTAIRCR       LL_SBS_LockVTOR
  * @note   Setting lock secure VTOR depends on privilege mode in secure/non-secure code.
  */
__STATIC_INLINE void LL_SBS_LockVTOR(void)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(SBS->CSLCKR, SBS_CSLCKR_LOCKSVTAIRCR);
#else
  STM32_SET_BIT(SBS->CNSLCKR, SBS_CNSLCKR_LOCKNSVTOR);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Check if the VTOR register is locked.
  * @rmtoll
  *  CNSLCKR       LOCKNSVTOR         LL_SBS_IsLockedVTOR \n
  *  CSLCKR        LOCKSVTAIRCR       LL_SBS_IsLockedVTOR
  * @note   Setting lock VTOR depends on privilege mode in secure/non-secure code.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedVTOR(void)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(SBS->CSLCKR, SBS_CSLCKR_LOCKSVTAIRCR) == SBS_CSLCKR_LOCKSVTAIRCR) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(SBS->CNSLCKR, SBS_CNSLCKR_LOCKNSVTOR) == SBS_CNSLCKR_LOCKNSVTOR) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the non-secure VTOR register.
  * @rmtoll
  *  CNSLCKR       LOCKNSVTOR         LL_SBS_NS_LockVTOR
  * @note   Setting lock VTOR non-secure depends on privilege mode in secure/non-secure code.
  */
__STATIC_INLINE void LL_SBS_NS_LockVTOR(void)
{
  STM32_SET_BIT(SBS->CNSLCKR, SBS_CNSLCKR_LOCKNSVTOR);
}

/**
  * @brief  Check if the non-secure VTOR is locked.
  * @rmtoll
  *  CNSLCKR       LOCKNSVTOR         LL_SBS_NS_IsLockedVTOR
  * @note   Setting lock non-secure VTOR depends on privilege mode in secure/non-secure code.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_NS_IsLockedVTOR(void)
{
  return ((STM32_READ_BIT(SBS->CNSLCKR, SBS_CNSLCKR_LOCKNSVTOR) == SBS_CNSLCKR_LOCKNSVTOR) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Lock of SBS CPU registers.
  *         Lock(s) cleared only at system reset
  * @rmtoll
  *  CNSLCKR       LOCKNSVTOR         LL_SBS_CPU_LockRegisters \n
  *  CSLCKR        LOCKSVTAIRCR       LL_SBS_CPU_LockRegisters \n
  *  CNSLCKR       LOCKNSMPU          LL_SBS_CPU_LockRegisters \n
  *  CSLCKR        LOCKSMPU           LL_SBS_CPU_LockRegisters \n
  *  CSLCKR        LOCKSAU            LL_SBS_CPU_LockRegisters
  * @param  core_regs
  *         This parameter can be one of the following values :
  *          @arg @ref LL_SBS_CPU_LOCK_VTOR
  *          @arg @ref LL_SBS_CPU_LOCK_AIRCR
  *          @arg @ref LL_SBS_CPU_LOCK_MPU
  *          @arg @ref LL_SBS_CPU_LOCK_SAU
  *          @arg @ref LL_SBS_CPU_LOCK_S_ALL
  *          @arg @ref LL_SBS_CPU_LOCK_NS_ALL
  */
__STATIC_INLINE void LL_SBS_CPU_LockRegisters(uint32_t core_regs)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  SBS->CSLCKR = core_regs;
#else
  SBS->CNSLCKR = core_regs;
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Check if the SBS CPU register is locked.
  * @rmtoll
  *  CNSLCKR       LOCKNSVTOR         LL_SBS_CPU_IsLockedRegisters \n
  *  CSLCKR        LOCKSVTAIRCR       LL_SBS_CPU_IsLockedRegisters \n
  *  CNSLCKR       LOCKNSMPU          LL_SBS_CPU_IsLockedRegisters \n
  *  CSLCKR        LOCKSMPU           LL_SBS_CPU_IsLockedRegisters \n
  *  CSLCKR        LOCKSAU            LL_SBS_CPU_IsLockedRegisters
  * @retval the return value can be one of the following values :
  *          @arg @ref LL_SBS_CPU_LOCK_VTOR
  *          @arg @ref LL_SBS_CPU_LOCK_AIRCR
  *          @arg @ref LL_SBS_CPU_LOCK_MPU
  *          @arg @ref LL_SBS_CPU_LOCK_SAU
  */
__STATIC_INLINE uint32_t LL_SBS_CPU_IsLockedRegisters(uint32_t core_regs)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(SBS->CSLCKR, core_regs) == (core_regs)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(SBS->CNSLCKR, core_regs) == (core_regs)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock of SBS CPU registers.
  *         Lock(s) cleared only at system reset
  * @rmtoll
  *  CNSLCKR       LOCKNSVTOR         LL_SBS_CPUNS_LockRegisters \n
  *  CNSLCKR       LOCKNSMPU          LL_SBS_CPUNS_LockRegisters
  * @param  core_regs
  *         This parameter can be one of the following values :
  *          @arg @ref LL_SBS_CPU_LOCK_VTOR
  *          @arg @ref LL_SBS_CPU_LOCK_MPU
  *          @arg @ref LL_SBS_CPU_LOCK_NS_ALL
  */
__STATIC_INLINE void LL_SBS_CPUNS_LockRegisters(uint32_t core_regs)
{
  SBS->CNSLCKR = core_regs;
}

/**
  * @brief  Check if the SBS CPU register is locked.
  * @rmtoll
  *  CNSLCKR       LOCKNSVTOR         LL_SBS_CPUNS_IsLockedRegisters \n
  *  CNSLCKR       LOCKNSMPU          LL_SBS_CPUNS_IsLockedRegisters
  * @retval the return value can be one of the following values :
  *          @arg @ref LL_SBS_CPU_LOCK_VTOR
  *          @arg @ref LL_SBS_CPU_LOCK_MPU
  */
__STATIC_INLINE uint32_t LL_SBS_CPUNS_IsLockedRegisters(uint32_t core_regs)
{
  return ((STM32_READ_BIT(SBS->CNSLCKR, core_regs) == (core_regs)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @}
  */

/** @defgroup SBS_LL_EF_FLASH_Management FLASH Management
  * @{
  */

/**
  * @brief  Enable the NMI in case of double ECC error in FLASH Interface.
  * @rmtoll
  *  ECCNMIR     ECCNMI_MASK_EN     LL_SBS_FLASH_EnableECCNMI
  */
__STATIC_INLINE  void LL_SBS_FLASH_EnableECCNMI(void)
{
  STM32_CLEAR_BIT(SBS->ECCNMIR, SBS_ECCNMIR_ECCNMI_MASK_EN);
}

/**
  * @brief  Disable the NMI in case of double ECC error in FLASH Interface.
  * @rmtoll
  *  ECCNMIR     ECCNMI_MASK_EN     LL_SBS_FLASH_DisableECCNMI
  */
__STATIC_INLINE  void LL_SBS_FLASH_DisableECCNMI(void)
{
  STM32_SET_BIT(SBS->ECCNMIR, SBS_ECCNMIR_ECCNMI_MASK_EN);
}

/**
  * @brief  Check if the NMI is Disabled in case of double ECC error in FLASH Interface.
  * @rmtoll
  *  ECCNMIR     ECCNMI_MASK_EN     LL_SBS_FLASH_IsEnabledECCNMI
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE  uint32_t LL_SBS_FLASH_IsEnabledECCNMI(void)
{
  return ((STM32_READ_BIT(SBS->ECCNMIR, SBS_ECCNMIR_ECCNMI_MASK_EN) == SBS_ECCNMIR_ECCNMI_MASK_EN) ? 0UL : 1UL);
}

/**
  * @brief  Set the SBS flash bank swapping.
  * @rmtoll
  *  FBMODER     FB_MODE     LL_SBS_FLASH_SetBankSwapMode
  * @param  bank_swap
  *         This parameter can be one of the following values:
  *         @arg @ref LL_SBS_FLASH_BANK_NOT_SWAP
  *         @arg @ref LL_SBS_FLASH_BANK_SWAP
  */
__STATIC_INLINE void LL_SBS_FLASH_SetBankSwapMode(uint32_t bank_swap)
{
  STM32_MODIFY_REG(SBS->FBMODER, SBS_FBMODER_FB_MODE, bank_swap);
}

/**
  * @brief  Get the SBS flash bank swapping.
  * @rmtoll
  *  FBMODER     FB_MODE     LL_SBS_FLASH_GetBankSwapMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SBS_FLASH_BANK_NOT_SWAP
  *         @arg @ref LL_SBS_FLASH_BANK_SWAP
  */
__STATIC_INLINE uint32_t LL_SBS_FLASH_GetBankSwapMode(void)
{
  return (STM32_READ_BIT(SBS->FBMODER, SBS_FBMODER_FB_MODE));
}

/**
  * @brief  Lock flash bank swap.
  * @rmtoll
  *  SWAPLOCKR     SWAP_LOCK     LL_SBS_FLASH_LockBankSwap
  */
__STATIC_INLINE void LL_SBS_FLASH_LockBankSwap(void)
{
  STM32_MODIFY_REG(SBS->SWAPLOCKR, SBS_SWAPLOCKR_SWAP_LOCK, LL_SBS_FLASH_BANK_SWAP_LOCK);
}

/**
  * @brief  Check if the flash bank swap is locked.
  * @rmtoll
  *  SWAPLOCKR     SWAP_LOCK     LL_SBS_FLASH_IsLockedBankSwap
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_FLASH_IsLockedBankSwap(void)
{
  return ((STM32_READ_BIT(SBS->SWAPLOCKR, SBS_SWAPLOCKR_SWAP_LOCK) == LL_SBS_FLASH_BANK_SWAP_LOCK) ? 1UL : 0UL);
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
#endif /* SBS */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_LL_SBS_H */
