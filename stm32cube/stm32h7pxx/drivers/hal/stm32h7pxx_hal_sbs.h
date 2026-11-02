/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_sbs.h
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
#ifndef STM32H7PXX_HAL_SBS_H
#define STM32H7PXX_HAL_SBS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_sbs.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
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

/*! HAL SBS I/O analog switch value enumeration definition */
typedef enum
{
  HAL_SBS_VDDA_SUPPLY    = LL_SBS_VDDA_SUPPLY,    /*!< VDDA supply        */
  HAL_SBS_BOOSTER_SUPPLY = LL_SBS_BOOSTER_SUPPLY, /*!< VDD booster supply */
  HAL_SBS_VDD_SUPPLY     = LL_SBS_VDD_SUPPLY      /*!< VDD supply         */
} hal_sbs_analog_switch_t;

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

/*! HAL SBS I/O speed optimization status enumeration definition */
typedef enum
{
  HAL_SBS_IO_SPEED_OPTIMIZATION_DISABLED = 0U, /*!< SBS IO speed optimization is disabled */
  HAL_SBS_IO_SPEED_OPTIMIZATION_ENABLED  = 1U  /*!< SBS IO speed optimization is enabled  */
} hal_sbs_io_speed_optimization_status_t;

/*! HAL SBS memory erase status enumeration definition */
typedef enum
{
  HAL_SBS_MEMORY_NOT_ERASED  = 0U,  /*!< SBS memory not erased */
  HAL_SBS_MEMORY_ERASED      = 1U   /*!< SBS memory erased     */
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
#define HAL_SBS_SRAM1_ECC_DOUBLE_ERROR  LL_SBS_SRAM1_ECC_DOUBLE_ERROR  /*!< SRAM1 ECC double error  */
#define HAL_SBS_SRAM2_ECC_DOUBLE_ERROR  LL_SBS_SRAM2_ECC_DOUBLE_ERROR  /*!< SRAM2 ECC double error  */
#define HAL_SBS_SRAM3_ECC_DOUBLE_ERROR  LL_SBS_SRAM3_ECC_DOUBLE_ERROR  /*!< SRAM3 ECC double error  */
#define HAL_SBS_SRAM4_ECC_DOUBLE_ERROR  LL_SBS_SRAM4_ECC_DOUBLE_ERROR  /*!< SRAM4 ECC double error  */
#define HAL_SBS_ITCM_ECC_DOUBLE_ERROR   LL_SBS_ITCM_ECC_DOUBLE_ERROR   /*!< ITCM ECC double error   */
#define HAL_SBS_DTCM_ECC_DOUBLE_ERROR   LL_SBS_DTCM_ECC_DOUBLE_ERROR   /*!< DTCM ECC double error   */
#define HAL_SBS_BKPRAM_ECC_DOUBLE_ERROR LL_SBS_BKPRAM_ECC_DOUBLE_ERROR /*!< BKPRAM ECC double error */
#define HAL_SBS_LOCKUP_OUT              LL_SBS_LOCKUP_OUT              /*!< Cortex-M7 LOCKUP        */
#define HAL_SBS_FLASH_ECC_DOUBLE_ERROR  LL_SBS_FLASH_ECC_DOUBLE_ERROR  /*!< FLASH ECC double error  */
#define HAL_SBS_PVD                     LL_SBS_PVD                     /*!< PVD connection          */
#define HAL_SBS_TIM_BREAK_INPUTS_ALL    LL_SBS_TIM_BREAK_INPUTS_ALL    /*!< All TIM break inputs    */
/**
  * @}
  */

/** @defgroup SBS_COMPENSATION_CELL Compensation cell
  * @{
  */
#define HAL_SBS_CCELL_VDDIO LL_SBS_CCELL_VDDIO /*!< VDD I/O compensation cell */
/**
  * @}
  */

/** @defgroup SBS_ERASE_STATUS_FLAGS SBS Erase status Flags
  * @{
  */
#define HAL_SBS_BKPRAM_ERASED        LL_SBS_FLAG_BKPMEF  /*!< BKPRAM erase status flag   */
#define HAL_SBS_AXISRAM1_ERASED      LL_SBS_FLAG_AXIRMEF /*!< AXISRAM1 erase status flag */
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

/** @defgroup SBS_Exported_Functions_Group1 Analog IO switch supply functions
  * @{
  */
void HAL_SBS_SetAnalogIOSwitchSupply(hal_sbs_analog_switch_t analog_switch);
hal_sbs_analog_switch_t HAL_SBS_GetAnalogIOSwitchSupply(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group2 Floating point unit interrupts management functions
  * @{
  */
void HAL_SBS_EnableFPUIT(uint32_t floating_point);
void HAL_SBS_DisableFPUIT(uint32_t floating_point);
hal_sbs_it_fpu_status_t HAL_SBS_IsEnabledFPUIT(uint32_t floating_point);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group3 TIM break inputs management functions
  * @{
  */
void HAL_SBS_EnableTIMBreakInputs(uint32_t break_input);
hal_sbs_tim_break_input_status_t HAL_SBS_IsEnabledTIMBreakInputs(uint32_t break_input);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group4 Compensation cell management functions
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

/** @defgroup SBS_Exported_Functions_Group5 Compensation cell code management functions
  * @{
  */
uint32_t HAL_SBS_GetPMOSCompensationCellValue(uint32_t comp_cell);
uint32_t HAL_SBS_GetNMOSCompensationCellValue(uint32_t comp_cell);

void HAL_SBS_SetConfigxMOSCompensationCellCode(uint32_t comp_cell, uint32_t pmos_code, uint32_t nmos_code);
void HAL_SBS_GetConfigxMOSCompensationCellCode(uint32_t comp_cell, uint32_t *p_pmos_code, uint32_t *p_nmos_code);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group6 Hide Protection Level management functions
  * @{
  */
hal_status_t HAL_SBS_SetHDPLevelValue(hal_sbs_hdp_level_value_t value);
hal_sbs_hdp_level_value_t HAL_SBS_GetHDPLevelValue(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group7 Debug control functions
  * @{
  */
void HAL_SBS_LockAPBAHBAccessPorts(void);
void HAL_SBS_UnlockAPBAHBAccessPorts(void);
hal_sbs_access_port_lock_status_t HAL_SBS_IsLockedAPBAHBAccessPorts(void);


void HAL_SBS_LockCoreDebugInterface(void);
void HAL_SBS_UnlockCoreDebugInterface(void);
hal_sbs_core_debug_itf_lock_status_t HAL_SBS_IsLockedCoreDebugInterface(void);

void HAL_SBS_SetAuthenticatedDebugHDPLevel(hal_sbs_hdp_level_value_t level);
hal_sbs_hdp_level_value_t HAL_SBS_GetAuthenticatedDebugHDPLevel(void);

void HAL_SBS_LockDebugConfig(void);
hal_sbs_debug_config_lock_status_t HAL_SBS_IsLockedDebugConfig(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group8 Flag management functions
  * @{
  */
hal_sbs_memory_erase_status_t HAL_SBS_GetMemoryEraseStatus(uint32_t memory);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group9 RSS Command selection functions
  * @{
  */
void     HAL_SBS_SetRSSCommand(uint32_t command);
uint32_t HAL_SBS_GetRSSCommand(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group10 Boot address functions
  * @{
  */
uint32_t HAL_SBS_GetBootAddress(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group11 I/O speed optimization functions
  * @{
  */
void HAL_SBS_EnableIOSpeedOptimization(void);
void HAL_SBS_DisableIOSpeedOptimization(void);
hal_sbs_io_speed_optimization_status_t HAL_SBS_IsEnabledIOSpeedOptimization(void);
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

#endif /* STM32H7PXX_HAL_SBS_H */
