/**
  **********************************************************************************************************************
  * @file    stm32g5xx_hal_sbs.h
  * @brief   Header file of SBS HAL module driver.
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
#ifndef STM32G5XX_HAL_SBS_H
#define STM32G5XX_HAL_SBS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_sbs.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

#if defined (SBS)
/** @defgroup SBS SBS
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_Exported_Types HAL SBS Types
  * @{
  */

/*! HAL SBS fast mode plus enumeration definition */
typedef enum
{
  HAL_SBS_FAST_MODE_PLUS_DISABLED = 0U, /*!< Fast mode plus is disabled */
  HAL_SBS_FAST_MODE_PLUS_ENABLED  = 1U  /*!< Fast mode plus is enabled  */
} hal_sbs_fast_mode_plus_status_t;

/*! HAL SBS I2C SMBUS enumeration definition */
typedef enum
{
  HAL_SBS_I2C_SMBUS_DISABLED = 0U, /*!< I2C SMBUS is disabled */
  HAL_SBS_I2C_SMBUS_ENABLED  = 1U  /*!< I2C SMBUS is enabled  */
} hal_sbs_i2c_smbus_status_t;

/*! HAL SBS floating point unit interrupts state enumeration definition */
typedef enum
{
  HAL_SBS_IT_FPU_DISABLED = 0U, /*!< Floating point interrupt is disabled */
  HAL_SBS_IT_FPU_ENABLED  = 1U  /*!< Floating point interrupt is enabled  */
} hal_sbs_it_fpu_status_t;

/*! HAL SBS TIM break inputs enumeration definition */
typedef enum
{
  HAL_SBS_TIM_BREAK_INPUT_DISABLED = 0U, /*!< TIM break input is disabled */
  HAL_SBS_TIM_BREAK_INPUT_ENABLED  = 1U  /*!< TIM break input is enabled  */
} hal_sbs_tim_break_input_status_t;

/*! HAL SBS compensation cell code source enumeration definition */
typedef enum
{
  HAL_SBS_CCELL_CODE_DEFAULT = 0U, /*!< Compensation cell code default value */
  HAL_SBS_CCELL_CODE_CUSTOM  = 1U  /*!< Compensation cell code custom value   */
} hal_sbs_ccell_code_src_t;

/*! HAL SBS compensation cell state enumeration definition */
typedef enum
{
  HAL_SBS_CCELL_DISABLED = 0U, /*!< Compensation cell is disabled */
  HAL_SBS_CCELL_ENABLED  = 1U  /*!< Compensation cell is enabled   */
} hal_sbs_ccell_status_t;

/*! HAL SBS Hide protection level enumeration definition */
typedef enum
{
  HAL_SBS_HDP_LEVEL_0 = LL_SBS_HDPL_VALUE_0,  /*!< Hide protection level 0 */
  HAL_SBS_HDP_LEVEL_1 = LL_SBS_HDPL_VALUE_1,  /*!< Hide protection level 1 */
  HAL_SBS_HDP_LEVEL_2 = LL_SBS_HDPL_VALUE_2,  /*!< Hide protection level 2 */
  HAL_SBS_HDP_LEVEL_3 = LL_SBS_HDPL_VALUE_3,  /*!< Hide protection level 3 */
} hal_sbs_hdp_level_value_t;

/*! HAL SBS Next Hide Protection Level Selection enumeration definition */
typedef enum
{
  HAL_SBS_HDP_OBK_LEVEL_0 = LL_SBS_HDP_OBK_0,  /*!< Increment the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
  HAL_SBS_HDP_OBK_LEVEL_1 = LL_SBS_HDP_OBK_1,  /*!< Increment the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
  HAL_SBS_HDP_OBK_LEVEL_2 = LL_SBS_HDP_OBK_2,  /*!< Increment the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
  HAL_SBS_HDP_OBK_LEVEL_3 = LL_SBS_HDP_OBK_3,  /*!< Increment the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
} hal_sbs_hdp_obk_level_value_t;

/*! HAL SBS EPOCH selection enumeration definition */
typedef enum
{
  HAL_SBS_EPOCH_NSEC  = LL_SBS_EPOCH_SEL_NSEC, /*!< EPOCH non-secure selected */
  HAL_SBS_EPOCH_SEC   = LL_SBS_EPOCH_SEL_SEC,  /*!< EPOCH secure selected     */
  HAL_SBS_EPOCH_CLEAR = LL_SBS_EPOCH_SEL_CLR,  /*!< EPOCH forced to zero      */
} hal_sbs_epoch_selection_t;

/*! HAL SBS Lock access port enumeration definition */
typedef enum
{
  HAL_SBS_ACCESS_PORT_LOCKED   = 1U, /*!< Device access port locked   */
  HAL_SBS_ACCESS_PORT_UNLOCKED = 0U  /*!< Device access port unlocked */
} hal_sbs_access_port_lock_status_t;

/*! HAL SBS Lock debug interface enumeration definition */
typedef enum
{
  HAL_SBS_CORE_DEBUG_ITF_LOCKED   = 1U, /*!< Debug locked (HPDL not authorized or HPDL is authorized and no unlock is performed) */
  HAL_SBS_CORE_DEBUG_ITF_UNLOCKED = 0U  /*!< Debug unlocked when the hide protection level is authorized                         */
} hal_sbs_core_debug_itf_lock_status_t;

/*! HAL SBS Lock Debug configuration register enumeration definition */
typedef enum
{
  HAL_SBS_DEBUG_CONFIG_LOCKED   = 1U, /*!< Debug configuration register is locked   */
  HAL_SBS_DEBUG_CONFIG_UNLOCKED = 0U  /*!< Debug configuration register is unlocked */
} hal_sbs_debug_config_lock_status_t;

/*! HAL SBS Authenticated debug security enumeration definition */
typedef enum
{
  HAL_SBS_AUTHENTICATED_DEBUG_SEC_NSEC = LL_SBS_AUTHN_DEBUG_SEC_NSEC, /*!< Open debug for secure and non-secure */
  HAL_SBS_AUTHENTICATED_DEBUG_NSEC     = LL_SBS_AUTHN_DEBUG_NSEC      /*!< Open debug for non-secure only       */
} hal_sbs_authenticated_debug_sec_attr_t;

/*! HAL SBS Core register lock status enumeration definition */
typedef enum
{
  HAL_SBS_CORE_REG_UNLOCKED = 0U, /*!< SBS Core register unlocked */
  HAL_SBS_CORE_REG_LOCKED   = 1U  /*!< SBS Core register locked   */
} hal_sbs_core_reg_lock_status_t;

/*! HAL SBS security access level attribute enumeration definition */
typedef enum
{
  HAL_SBS_NSEC = LL_SBS_ATTR_NSEC, /*!< Non-secure access level attribute */
  HAL_SBS_SEC  = LL_SBS_ATTR_SEC   /*!< Secure access level attribute     */
} hal_sbs_sec_attr_t;

/*! HAL SBS flash swapping bank enumeration definition */
typedef enum
{
  HAL_SBS_FLASH_BANK_NOT_SWAPPED = LL_SBS_FLASH_BANK_NOT_SWAP, /*!< SBS flash Bank not swapped */
  HAL_SBS_FLASH_BANK_SWAPPED     = LL_SBS_FLASH_BANK_SWAP      /*!< SBS flash Bank swapped     */
} hal_sbs_flash_bank_swap_status_t;

/*! HAL SBS flash swapping bank lock status enumeration definition */
typedef enum
{
  HAL_SBS_FLASH_BANK_SWAP_UNLOCKED = 0U, /*!< SBS flash Bank swap unlocked */
  HAL_SBS_FLASH_BANK_SWAP_LOCKED   = 1U  /*!< SBS flash Bank swap locked   */
} hal_sbs_flash_bank_swap_lock_status_t;

/*! HAL SBS icache/dcache/memory erase status enumeration definition */
typedef enum
{
  HAL_SBS_MEMORY_NOT_ERASED  = 0U,  /*!< SBS icache/dcache/memory not erased */
  HAL_SBS_MEMORY_ERASED      = 1U   /*!< SBS icache/dcache/memory erased     */
} hal_sbs_memory_erase_status_t;
/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_Exported_Constants HAL SBS Constants
  * @{
  */

/** @defgroup SBS_FLOATING_POINT_UNIT_INTERRUPTS Floating point unit interrupts
  * @{
  */
#define HAL_SBS_IT_FPU_IOC LL_SBS_IT_FPU_IOC /*!< Invalid operation interrupt        */
#define HAL_SBS_IT_FPU_DZC LL_SBS_IT_FPU_DZC /*!< Divide-by-zero interrupt           */
#define HAL_SBS_IT_FPU_UFC LL_SBS_IT_FPU_UFC /*!< underflow interrupt                */
#define HAL_SBS_IT_FPU_OFC LL_SBS_IT_FPU_OFC /*!< Overflow interrupt                 */
#define HAL_SBS_IT_FPU_IDC LL_SBS_IT_FPU_IDC /*!< Input abnormal interrupt           */
#define HAL_SBS_IT_FPU_IXC LL_SBS_IT_FPU_IXC /*!< Inexact interrupt                  */
#define HAL_SBS_IT_FPU_ALL LL_SBS_IT_FPU_ALL /*!< All floating point unit interrupts */
/**
  * @}
  */

/** @defgroup SBS_TIM_BREAK_INPUTS TIM break inputs
  * @{
  */
#define HAL_SBS_DCACHE_ECC_DOUBLE_ERROR LL_SBS_DCACHE_ECC_DOUBLE_ERROR /*!< Dcache ECC double error */
#define HAL_SBS_FLASH_ECC_DOUBLE_ERROR  LL_SBS_FLASH_ECC_DOUBLE_ERROR  /*!< FLASH ECC double error  */
#define HAL_SBS_PVD                     LL_SBS_PVD                     /*!< PVD connection          */
#define HAL_SBS_SRAM_ECC_DOUBLE_ERROR   LL_SBS_SRAM_ECC_DOUBLE_ERROR   /*!< SRAM ECC double error   */
#define HAL_SBS_LOCKUP_OUT              LL_SBS_LOCKUP_OUT              /*!< Cortex-M33 LOCKUP       */
#define HAL_SBS_TIM_BREAK_INPUTS_ALL    LL_SBS_TIM_BREAK_INPUTS_ALL    /*!< All TIM break inputs    */
/**
  * @}
  */

/** @defgroup SBS_FAST_MODE_PLUS_DRIVE Fast mode plus drive
  * @{
  */
#define HAL_SBS_DRIVE_PB6               LL_SBS_DRIVE_PB6               /*!< Fast mode plus driving capability activation on PB6 */
#define HAL_SBS_DRIVE_PB7               LL_SBS_DRIVE_PB7               /*!< Fast mode plus driving capability activation on PB7 */
#define HAL_SBS_DRIVE_PB9               LL_SBS_DRIVE_PB9               /*!< Fast mode plus driving capability activation on PB9 */
#define HAL_SBS_DRIVE_ALL               LL_SBS_DRIVE_ALL               /*!< ALL Fast mode plus driving capability activation    */
/**
  * @}
  */

/** @defgroup SBS_I2C_SMBUS I2C smbus 3.0
  * @{
  */
#define HAL_SBS_I2C1_SMBUS    LL_SBS_I2C1_SMBUS    /*!< Enable SMBUS 3.0 on I2C1    */
#if defined(I2C3)
#define HAL_SBS_I2C3_SMBUS    LL_SBS_I2C3_SMBUS    /*!< Enable SMBUS 3.0 on I2C3    */
#endif /* I2C3 */
#if defined(I2C4)
#define HAL_SBS_I2C4_SMBUS    LL_SBS_I2C4_SMBUS    /*!< Enable SMBUS 3.0 on I2C4    */
#endif /* I2C4 */
#define HAL_SBS_I2C_SMBUS_ALL LL_SBS_I2C_SMBUS_ALL /*!< Enable SMBUS 3.0 on all I2C */
/**
  * @}
  */

/** @defgroup SBS_COMPENSATION_CELL Compensation cell
  * @{
  */
#define HAL_SBS_CCELL_VDDIO LL_SBS_CCELL_VDDIO /*!< VDD I/O compensation cell */
#define HAL_SBS_CCELL_ALL   LL_SBS_CCELL_ALL   /*!< All compensation cell     */
/**
  * @}
  */

/** @defgroup SBS_CORE_LOCK_REGISTERS Core lock registers
  * @{
  */
#define HAL_SBS_CORE_VTOR_REG      LL_SBS_CPU_LOCK_VTOR     /*!< VTOR_S/ VTOR_NS register lock */
#define HAL_SBS_CORE_AIRCR_REG     LL_SBS_CPU_LOCK_AIRCR    /*!< AIRCR register lock           */
#define HAL_SBS_CORE_MPU_REG       LL_SBS_CPU_LOCK_MPU      /*!< MPU_S/ MPU_NS registers lock  */
#define HAL_SBS_CORE_SAU_REG       LL_SBS_CPU_LOCK_SAU      /*!< SAU registers lock            */
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
#define HAL_SBS_CORE_ALL_REGS      LL_SBS_CPU_LOCK_SEC_ALL  /*!< All secure registers lock     */
#else
#define HAL_SBS_CORE_ALL_REGS      LL_SBS_CPU_LOCK_NSEC_ALL /*!< All non-secure registers lock */
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
#define HAL_SBS_CORE_NSEC_ALL_REGS LL_SBS_CPU_LOCK_NSEC_ALL /*!< All non-secure registers lock */
/**
  * @}
  */

/** @defgroup SBS_ERASE_STATUS_FLAGS SBS Erase status Flags
  * @{
  */
#define HAL_SBS_ICACHE_PKARAM_ERASED               LL_SBS_FLAG_IPMEE /*!< ICACHE and PKA RAM erase status flag                 */
#define HAL_SBS_ICACHE_DCACHE_SRAMS_PKARAM_ERASED  LL_SBS_FLAG_MCLR  /*!< SRAMx (x = 1 to 5), ICACHE, DCACHE and PKA RAM flag  */
#define HAL_SBS_ALL_MEMORIES_ERASED                LL_SBS_FLAG_ALL   /*!< All erase status flags                               */
/**
  * @}
  */

/** @defgroup SBS_SECURITY_ATTRIBUTES Security Attributes configuration items
  * @{
  */
#define HAL_SBS_SEC_ITEM_ALL        LL_SBS_SEC_ITEM_ALL     /*!< All security configuration items      */
#define HAL_SBS_SEC_ITEM_CLOCK      LL_SBS_SEC_ITEM_CLOCK   /*!< SBS clock security configuration item */
#define HAL_SBS_SEC_ITEM_CLASSB     LL_SBS_SEC_ITEM_CLASSB  /*!< Class B security configuration item   */
#define HAL_SBS_SEC_ITEM_FPU        LL_SBS_SEC_ITEM_FPU     /*!< FPU security configuration item       */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_Exported_Functions HAL SBS Functions
  * @{
  */

/** @defgroup SBS_Exported_Functions_Group1 Fast mode plus functions
  * @{
  */
void HAL_SBS_EnableFastModePlus(uint32_t fast_mode_plus);
void HAL_SBS_DisableFastModePlus(uint32_t fast_mode_plus);
hal_sbs_fast_mode_plus_status_t HAL_SBS_IsEnabledFastModePlus(uint32_t fast_mode_plus);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group2 I2C SMBUS functions
  * @{
  */
void HAL_SBS_EnableI2CSMBUS(uint32_t i2c_smbus);
void HAL_SBS_DisableI2CSMBUS(uint32_t i2c_smbus);
hal_sbs_i2c_smbus_status_t HAL_SBS_IsEnabledI2CSMBUS(uint32_t i2c_smbus);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group3 Floating point unit interrupts management functions
  * @{
  */
void HAL_SBS_EnableFPUIT(uint32_t floating_point);
void HAL_SBS_DisableFPUIT(uint32_t floating_point);
hal_sbs_it_fpu_status_t HAL_SBS_IsEnabledFPUIT(uint32_t floating_point);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group4 TIM break inputs management functions
  * @{
  */
void HAL_SBS_EnableTIMBreakInputs(uint32_t break_input);
void HAL_SBS_DisableTIMBreakInputs(uint32_t break_input);
hal_sbs_tim_break_input_status_t HAL_SBS_IsEnabledTIMBreakInputs(uint32_t break_input);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group5 Compensation cell management functions
  * @{
  */
void HAL_SBS_SetCompensationCellCodeSrc(uint32_t comp_cell, hal_sbs_ccell_code_src_t code_select);
hal_sbs_ccell_code_src_t HAL_SBS_GetCompensationCellCodeSrc(uint32_t comp_cell);

hal_status_t HAL_SBS_EnableCompensationCell(uint32_t comp_cell);
void HAL_SBS_DisableCompensationCell(uint32_t comp_cell);
hal_sbs_ccell_status_t HAL_SBS_IsEnabledCompensationCell(uint32_t comp_cell);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group6 Compensation cell code management functions
  * @{
  */
uint32_t HAL_SBS_GetPMOSCompensationCellValue(uint32_t comp_cell);
uint32_t HAL_SBS_GetNMOSCompensationCellValue(uint32_t comp_cell);

void HAL_SBS_SetConfigxMOSCompensationCellCode(uint32_t comp_cell, uint32_t pmos_code, uint32_t nmos_code);
void HAL_SBS_GetConfigxMOSCompensationCellCode(uint32_t comp_cell, uint32_t *p_pmos_code, uint32_t *p_nmos_code);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group7 NMI double ECC error in FLASH Interface functions
  * @{
  */
void HAL_SBS_FLASH_EnableECCNMI(void);
void HAL_SBS_FLASH_DisableECCNMI(void);
uint32_t HAL_SBS_FLASH_IsEnabledECCNMI(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group8 Hide Protection Level management functions
  * @{
  */
hal_status_t HAL_SBS_SetHDPLevelValue(hal_sbs_hdp_level_value_t value);
hal_sbs_hdp_level_value_t HAL_SBS_GetHDPLevelValue(void);

void HAL_SBS_SetHDPOBKLevelValue(hal_sbs_hdp_obk_level_value_t value);
hal_sbs_hdp_obk_level_value_t HAL_SBS_GetHDPOBKLevelValue(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group9 Hardware secure storage control functions
  * @{
  */
void HAL_SBS_SetEPOCHSelection(hal_sbs_epoch_selection_t epoch_selection);
hal_sbs_epoch_selection_t HAL_SBS_GetEPOCHSelection(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group10 Debug control functions
  * @{
  */
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
void HAL_SBS_LockAPBAHBAccessPorts(void);
void HAL_SBS_UnlockAPBAHBAccessPorts(void);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_sbs_access_port_lock_status_t HAL_SBS_IsLockedAPBAHBAccessPorts(void);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
void HAL_SBS_LockSecAHBAccessPort(void);
void HAL_SBS_UnlockSecAHBAccessPort(void);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_sbs_access_port_lock_status_t HAL_SBS_IsLockedSecAHBAccessPort(void);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
void HAL_SBS_LockCoreDebugInterface(void);
void HAL_SBS_UnlockCoreDebugInterface(void);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_sbs_core_debug_itf_lock_status_t HAL_SBS_IsLockedCoreDebugInterface(void);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
void HAL_SBS_SetAuthenticatedDebugHDPLevel(hal_sbs_hdp_level_value_t level);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_sbs_hdp_level_value_t HAL_SBS_GetAuthenticatedDebugHDPLevel(void);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
void HAL_SBS_LockDebugConfig(void);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_sbs_debug_config_lock_status_t HAL_SBS_IsLockedDebugConfig(void);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
void HAL_SBS_SetAuthenticatedDebugSecAttr(hal_sbs_authenticated_debug_sec_attr_t security);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_sbs_authenticated_debug_sec_attr_t HAL_SBS_GetAuthenticatedDebugSecAttr(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group11 Core lock registers functions
  * @{
  */
void HAL_SBS_LockCoreRegisters(uint32_t core_regs);
hal_sbs_core_reg_lock_status_t HAL_SBS_IsLockedCoreRegisters(uint32_t core_regs);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
void HAL_SBS_NS_LockCoreRegisters(uint32_t core_regs);
hal_sbs_core_reg_lock_status_t HAL_SBS_NS_IsLockedCoreRegisters(uint32_t core_regs);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group12 FLASH bank swap functions
  * @{
  */
hal_status_t HAL_SBS_FLASH_SetBankSwapMode(hal_sbs_flash_bank_swap_status_t bank_swap);
hal_sbs_flash_bank_swap_status_t HAL_SBS_FLASH_GetBankSwapMode(void);

void HAL_SBS_FLASH_LockBankSwap(void);
hal_sbs_flash_bank_swap_lock_status_t HAL_SBS_FLASH_IsLockedBankSwap(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group13 Flag management functions
  * @{
  */
hal_sbs_memory_erase_status_t HAL_SBS_GetMemoryEraseStatus(uint32_t memory);
void HAL_SBS_CleanMemoryEraseStatus(uint32_t memory);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group14 RSS Command selection functions
  * @{
  */
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
void     HAL_SBS_SetRSSCommand(uint32_t command);
uint32_t HAL_SBS_GetRSSCommand(void);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group15 Security access level attribute management.
  * @{
  */
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_SBS_SetSecAttr(uint32_t item, hal_sbs_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_sbs_sec_attr_t HAL_SBS_GetSecAttr(uint32_t item);
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

#endif /* STM32G5XX_HAL_SBS_H */
