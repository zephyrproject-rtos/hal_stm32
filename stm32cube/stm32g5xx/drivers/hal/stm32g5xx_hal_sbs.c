/**
  **********************************************************************************************************************
  * @file    stm32g5xx_hal_sbs.c
  * @brief   SBS HAL module driver.
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

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

#if defined (SBS)
#if defined(USE_HAL_SBS_MODULE) && (USE_HAL_SBS_MODULE == 1)
/** @addtogroup SBS
  * @{
  */

/** @defgroup SBS_Introduction SBS Introduction
  * @{

   The System configuration, Boot and Security (SBS) hardware abstraction layer provides a set of APIs to interface with
   the STM32 SBS.

   The SBS includes the following features:

     - Activate and deactivate the FMP high-drive mode for specific I/Os.
     - Manage the I/O compensation cell.
     - Activate and deactivate the connection to TIM1/8/15/16/17.
     - Activate and deactivate the FPU interrupts.
     - Manage the compensation cells.
     - Manage the debug.
     - Set and get the EPOCH value to be sent to the SAES.
     - Activate and deactivate the NMI generation when a double ECC error occurs on FLASH.
     - Lock the core registers.
     -  Activate and deactivate the SMBUS on I2C instances.
     - Set and get the command to be sent to the RSS executed at the next reset.
     - Get and clear the memory erase flags.
  */
/**
  * @}
  */

/** @defgroup SBS_How_To_Use SBS How To Use
  * @{

# How to use the SBS HAL module driver

## The SBS HAL driver can be used as follows:

After startup, SBS peripheral is not active by default. Use HAL_RCC_SBS_EnableClock() function to enable
SBS AHB4 clock.

This module provides different sets of APIs that allow to :


1. Fast mode plus :
   Several APIs are available to manage the fast mode plus
   - Enable and disable the fast mode plus capability:
     - These functionalities are ensured respectively by HAL_SBS_EnableFastModePlus() and
       HAL_SBS_DisableFastModePlus().
   - Get the fast mode plus capability state:
     - This functionality is ensured by HAL_SBS_IsEnabledFastModePlus() function.

2. I2C SMBUS :
   Several APIs are available to manage the I2C smbus
   - Enable and disable the i2c smbus:
     - These functionalities are ensured respectively by HAL_SBS_EnableI2CSMBUS() and
       HAL_SBS_DisableI2CSMBUS().
   - Check if the i2c smbus is enabled :
     - This functionality is ensured by HAL_SBS_IsEnabledI2CSMBUS() function.

3. Manage floating point unit interrupts :
   Several APIs are available to manage the floating point unit interrupts
   - Enable and disable the floating point unit interrupts:
     - These functionalities are ensured respectively by HAL_SBS_EnableFPUIT() and HAL_SBS_DisableFPUIT().
   - Get the floating point unit interrupts state:
     - This functionality is ensured by HAL_SBS_IsEnabledFPUIT() function.

4. Manage TIM break inputs :
   This feature is used to control the system break interconnect to TIM1/8/15/16/17 break inputs
   - Enable and disable the TIM break inputs:
    - This functionality is ensured respectively by HAL_SBS_EnableTIMBreakInputs() function and
      HAL_SBS_DisableTIMBreakInputs() function.
   - Check the TIM break inputs activation:
     - This functionality is ensured by HAL_SBS_IsEnabledTIMBreakInputs() function.
   - \b Note: Some TIM break inputs disabling can only be done by a hardware reset.

5. Control the compensation cell :
   The SBS can be configured to manage the compensation cell
   - Set the compensation cell code source :
     - This functionality is ensured by HAL_SBS_SetCompensationCellCodeSrc() function.
   - Get the compensation cell code source :
     - This functionality is ensured by HAL_SBS_GetCompensationCellCodeSrc() function.
   - Enable and disable the compensation cell activation :
     - These functionalities are ensured respectively by HAL_SBS_EnableCompensationCell() and
       HAL_SBS_DisableCompensationCell().
   - Get the compensation cell state:
     - This functionality is ensured by HAL_SBS_IsEnabledCompensationCell() function.

6. Manage the compensation code :
   Several APIs are available to manage the compensation code
   - Get the compensation value of PMOS transistor :
     - This functionality is ensured by HAL_SBS_GetPMOSCompensationCellValue() function.
   - Get the compensation value of NMOS transistor :
     - This functionality is ensured by HAL_SBS_GetNMOSCompensationCellValue() function.
   - Set the compensation cell code:
     - This functionality is ensured by HAL_SBS_SetConfigxMOSCompensationCellCode() function.
   - Get the compensation cell code :
     - This functionality is ensured by HAL_SBS_GetConfigxMOSCompensationCellCode() function.

7. NMI double ECC error in FLASH Interface functions:
   Several APIs are available to control NMI double ECC error in FLASH Interface.
   - Enable and disable the NMI in case of double ECC error in FLASH Interface:
     - These functionalities are ensured respectively by HAL_SBS_FLASH_EnableECCNMI() and
       HAL_SBS_FLASH_DisableECCNMI() function.
   - Get if the NMI is Enabled in case of double ECC error in FLASH Interface:
     - This functionality is ensured by HAL_SBS_FLASH_IsEnabledECCNMI() function.

8. HDP levels management functions :
   Several APIs are available to manage HDPL
   - Set the HDPL value :
     - This functionality is ensured by HAL_SBS_SetHDPLevelValue() function.
   - Get the HDPL value :
     - This functionality is ensured by HAL_SBS_GetHDPLevelValue() function.
   - Set OBK HDPL value :
     - This functionality is ensured by HAL_SBS_SetHDPOBKLevelValue() function.
   - Get OBK HDPL value :
     - This functionality is ensured by HAL_SBS_GetHDPOBKLevelValue() function.

9. Hardware secure storage control functions
   - Set the EPOCH Selection value :
     - This functionality is ensured by HAL_SBS_SetEPOCHSelection() function.
   - Get the EPOCH Selection value :
     - This functionality is ensured by HAL_SBS_GetEPOCHSelection() function.


10. Debug control functions
   Several APIs are available to manage the debug control
   - Unlock and lock the APB, AHB access ports :
     - This functionality is ensured by HAL_SBS_UnlockAPBAHBAccessPorts()
       and HAL_SBS_LockAPBAHBAccessPorts() functions.
   - Check if the APB, AHB access ports are locked :
     - This functionality is ensured by HAL_SBS_IsLockedAPBAHBAccessPorts() function.
   - Unlock and lock the debug interface :
     - This functionality is ensured by HAL_SBS_UnlockCoreDebugInterface()
       and HAL_SBS_LockCoreDebugInterface() functions.
   - Check if the debug interface is locked :
     - This functionality is ensured by HAL_SBS_IsLockedCoreDebugInterface() function.
   - Set the HDP level at which the authenticated debug opens :
     - This functionality is ensured by HAL_SBS_SetAuthenticatedDebugHDPLevel() function.
   - Get the HDP level at which the authenticated debug opens :
     - This functionality is ensured by HAL_SBS_GetAuthenticatedDebugHDPLevel() function.
   - Lock the debug configuration :
     - This functionality is ensured by HAL_SBS_LockDebugConfig() function.
   - Check if the debug configuration is locked :
     - This functionality is ensured by HAL_SBS_IsLockedDebugConfig() function.
   - Unlock and lock the secure AHB access port :
     - This functionality is ensured by HAL_SBS_UnlockSecAHBAccessPort()
       and HAL_SBS_LockSecAHBAccessPort() functions.
   - Check if the secure AHB access port is locked :
     - This functionality is ensured by HAL_SBS_IsLockedSecAHBAccessPort() function.
   - Control debug opening secure/non-secure :
     - This functionality is ensured by HAL_SBS_SetAuthenticatedDebugSecAttr() function.
   - Get debug opening secure/non-secure :
     - This functionality is ensured by HAL_SBS_GetAuthenticatedDebugSecAttr() function.

11. Lock functions :
   Several APIs are available to manage the lock mechanism
   - Lock the configuration of the Core registers :
     - This functionality is ensured by HAL_SBS_LockCoreRegisters() function.
   - Check the Core registers lock status :
     - This functionality is ensured by HAL_SBS_IsLockedCoreRegisters() function.
   - Lock the configuration of the non-secure Core registers :
     - This functionality is ensured by HAL_SBS_NS_LockCoreRegisters() function
       only in a secure context.
   - Check the non-secure Core registers lock status :
     - This functionality is ensured by HAL_SBS_NS_IsLockedCoreRegisters() function
       only in a secure context.

12. FLASH bank swap functions :
   Several APIs are available to manage the flash bank swap
   - Set the flash bank swap mode:
     - This functionality is ensured by HAL_SBS_FLASH_SetBankSwapMode() function.
   - Get the flash bank swap mode:
     - This functionality is ensured by HAL_SBS_FLASH_GetBankSwapMode() function.
   - Lock the flash bank swap configuration:
     - This functionality is ensured by HAL_SBS_FLASH_LockBankSwap() function.
   - Check if the flash bank swap configuration is locked :
     - This functionality is ensured by HAL_SBS_FLASH_IsLockedBankSwap() function.

13. Flag management functions :
   Several APIs are available on the header file as "static_inline" functions to manage the memories erase status
   - Check if the memories erase status flags is active or not :
     - This functionality is ensured by HAL_SBS_GetMemoryEraseStatus() function.
   - Clear the memories erase status pending flags :
     - This functionality is ensured by HAL_SBS_CleanMemoryEraseStatus() function.

14. RSS Command selection functions :
   Several APIs are available to manage the RSS command
   - Set a command to the RSS to be executed at next reset :
     - This functionality is ensured by HAL_SBS_SetRSSCommand() function.
   - Get the command sent to the RSS :
     - This functionality is ensured by HAL_SBS_GetRSSCommand() function.
  */
/**
  * @}
  */

/** @defgroup SBS_Configuration_Table SBS Configuration Table
  * @{
# Configuration inside the SBS driver

Config defines        | Description        | Default value | Note
----------------------| -------------------| ------------- | -----------------------------------------------------------
USE_HAL_SBS_MODULE    | from hal_conf.h    | 1U            | When set to 1, the HAL SBS module is enabled.
USE_ASSERT_DBG_PARAM  | from IDE           | None          | When defined, enable the params assert.
  */
/**
  * @}
  */

/* Private define ----------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_Private_Constants SBS Private Constants
  * @{
  */
#define SBS_CCELL_MAX_DELAY_MS  50U   /*!< Max compensation cell timeout value (unit: milliseconds) */
#define HAL_SBS_CCELL_SIZE      0x0FU /*!< Max size of compensation cell code                       */
/**
  * @}
  */

/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_Private_Macros SBS Private Macros
  * @{
  */

/*! Fast mode plus check macro */
#define IS_SBS_SET_FAST_MODE_PLUS(fast_mode_plus)       \
  ((((fast_mode_plus) & (HAL_SBS_DRIVE_ALL)) != 0U)     \
   && (((fast_mode_plus) & (~HAL_SBS_DRIVE_ALL)) == 0U))

/*! Get fast mode plus check macro */
#define IS_SBS_GET_FAST_MODE_PLUS(fast_mode_plus) \
  (((fast_mode_plus) == (HAL_SBS_DRIVE_PB6))      \
   || ((fast_mode_plus) == (HAL_SBS_DRIVE_PB7))   \
   || ((fast_mode_plus) == (HAL_SBS_DRIVE_PB9)))

/*! Set I2C SMBUS check macro */
#define IS_SBS_SET_I2C_SMBUS(i2c_smbus)                \
  ((((i2c_smbus) & (HAL_SBS_I2C_SMBUS_ALL)) != 0U)     \
   && (((i2c_smbus) & (~HAL_SBS_I2C_SMBUS_ALL)) == 0U))

/*! Get I2C SMBUS check macro */
#if defined(I2C4)
#define IS_SBS_GET_I2C_SMBUS(i2c_smbus) \
  (((i2c_smbus) == (HAL_SBS_I2C1_SMBUS))            \
   || ((i2c_smbus) == (HAL_SBS_I2C3_SMBUS))         \
   || ((i2c_smbus) == (HAL_SBS_I2C4_SMBUS)))
#else
#define IS_SBS_GET_I2C_SMBUS(i2c_smbus) ((i2c_smbus) == (HAL_SBS_I2C1_SMBUS))
#endif /* I2C4 */

/*! Set floating point unit interrupts check macro */
#define IS_SBS_SET_FLOATING_POINT_IT(floating_point)     \
  ((((floating_point) & (HAL_SBS_IT_FPU_ALL)) != 0U)     \
   && (((floating_point) & (~HAL_SBS_IT_FPU_ALL)) == 0U))

/*! Get floating point unit interrupts check macro */
#define IS_SBS_GET_FLOATING_POINT_IT(floating_point) \
  (((floating_point) == (HAL_SBS_IT_FPU_IOC))        \
   || ((floating_point) == (HAL_SBS_IT_FPU_DZC))     \
   || ((floating_point) == (HAL_SBS_IT_FPU_UFC))     \
   || ((floating_point) == (HAL_SBS_IT_FPU_OFC))     \
   || ((floating_point) == (HAL_SBS_IT_FPU_IDC))     \
   || ((floating_point) == (HAL_SBS_IT_FPU_IXC)))

/*! TIM break inputs check macro */
#define IS_SBS_SET_TIM_BREAK_INPUTS(break_input)               \
  ((((break_input) & HAL_SBS_TIM_BREAK_INPUTS_ALL) != 0U)      \
   && (((break_input) & (~HAL_SBS_TIM_BREAK_INPUTS_ALL)) == 0U))

/*! TIM break inputs disable check macro */
#define IS_SBS_DISABLE_TIM_BREAK_INPUTS(break_input)     \
  ((break_input) == (HAL_SBS_FLASH_ECC_DOUBLE_ERROR))

/*! Get TIM break inputs check macro */
#define IS_SBS_GET_TIM_BREAK_INPUTS(break_input)        \
  (((break_input) == HAL_SBS_DCACHE_ECC_DOUBLE_ERROR)   \
   || ((break_input) == HAL_SBS_FLASH_ECC_DOUBLE_ERROR) \
   || ((break_input) == HAL_SBS_PVD)                    \
   || ((break_input) == HAL_SBS_SRAM_ECC_DOUBLE_ERROR)  \
   || ((break_input) == HAL_SBS_LOCKUP_OUT))

/*! Compensation cell check macro */
#define IS_SBS_CCELL(comp_cell) ((comp_cell) == HAL_SBS_CCELL_VDDIO)

/*! Compensation code check macro */
#define IS_SBS_CCELL_CODE(code_select)             \
  (((code_select) == HAL_SBS_CCELL_CODE_DEFAULT)   \
   || ((code_select) == HAL_SBS_CCELL_CODE_CUSTOM))

/*! Get compensation cell check macro */
#define IS_SBS_GET_CCELL(comp_cell)             \
  (((comp_cell) == HAL_SBS_CCELL_VDDIO))

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/*! Macro to check the security attribute */
#define IS_SBS_ITEM_SEC_ATTR(attribute) ((attribute == HAL_SBS_SEC  )  \
                                         || (attribute == HAL_SBS_NSEC))
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/*! Set securable items check macro*/
#define IS_SBS_SET_SEC_ITEM(item)  ((((item) & (HAL_SBS_SEC_ITEM_ALL)) != 0x00U)    \
                                    && (((item) & ~(HAL_SBS_SEC_ITEM_ALL)) == 0x00U))
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/*! Get securable items check macro*/
#define IS_SBS_GET_SEC_ITEM(item)  (((item) == HAL_SBS_SEC_ITEM_CLOCK)     \
                                    || ((item) == HAL_SBS_SEC_ITEM_CLASSB) \
                                    || ((item) == HAL_SBS_SEC_ITEM_FPU))

/*! XMOS compensation cell check macro */
#define IS_SBS_XMOS_CCELL_CODE(pmos_code,nmos_code) \
  (((pmos_code) <= HAL_SBS_CCELL_SIZE)              \
   && ((nmos_code) <= HAL_SBS_CCELL_SIZE))

/*! Hide protection level check macro */
#define IS_SBS_HDP_LEVEL(level)        \
  (((level) == HAL_SBS_HDP_LEVEL_0)    \
   || ((level) == HAL_SBS_HDP_LEVEL_1) \
   || ((level) == HAL_SBS_HDP_LEVEL_2) \
   || ((level) == HAL_SBS_HDP_LEVEL_3))

/*! Hide protection level at which the authenticated debug opens check macro */
#define IS_SBS_AUTHENTICATED_HDP_LEVEL(level)   \
  (((level) == HAL_SBS_HDP_LEVEL_1)    \
   || ((level) == HAL_SBS_HDP_LEVEL_2) \
   || ((level) == HAL_SBS_HDP_LEVEL_3))

/*! Next Hide Protection Level Selection check macro */
#define IS_SBS_HDPOBK_SELECTION(hdp_obk_select)      \
  (((hdp_obk_select)   == HAL_SBS_HDP_OBK_LEVEL_0)   \
   || ((hdp_obk_select) == HAL_SBS_HDP_OBK_LEVEL_1)  \
   || ((hdp_obk_select) == HAL_SBS_HDP_OBK_LEVEL_2)  \
   || ((hdp_obk_select) == HAL_SBS_HDP_OBK_LEVEL_3))

/*! Get icache/dcache/memory erase check macro */
#define IS_SBS_GET_MEMORY_ERASE(memory)          \
  (((memory) == HAL_SBS_ICACHE_PKARAM_ERASED)    \
   || ((memory) == HAL_SBS_ICACHE_DCACHE_SRAMS_PKARAM_ERASED))

/*! Clean icache/dcache/memory erase check macro */
#define IS_SBS_CLEAN_MEMORY_ERASE(memory)               \
  ((((memory) & (HAL_SBS_ALL_MEMORIES_ERASED)) != 0U)   \
   && (((memory) & ~(HAL_SBS_ALL_MEMORIES_ERASED)) == 0U))

/*! EPOCH Selection check macro */
#define IS_SBS_EPOCH_SELECTION(epoch_select) \
  (((epoch_select)   == HAL_SBS_EPOCH_NSEC)  \
   || ((epoch_select) == HAL_SBS_EPOCH_SEC)  \
   || ((epoch_select) == HAL_SBS_EPOCH_CLEAR))

/*! Authenticated debug security access check macro */
#define IS_SBS_AUTHENTICATED_DEBUG_SEC(security)  \
  (((security) == HAL_SBS_AUTHENTICATED_DEBUG_SEC_NSEC) \
   || ((security) == HAL_SBS_AUTHENTICATED_DEBUG_NSEC))

/*! Macro to check the Core lock registers */
#define IS_SBS_LOCK_CORE_REGS(core_regs) ((((core_regs) & (HAL_SBS_CORE_ALL_REGS)) != 0U) \
                                          && (((core_regs) & (~HAL_SBS_CORE_ALL_REGS)) == 0U))

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/*! Macro to check the Core locked registers */
#define IS_SBS_LOCKED_CORE_REGS(core_regs) (((core_regs) == HAL_SBS_CORE_VTOR_REG)   \
                                            || ((core_regs) == HAL_SBS_CORE_MPU_REG) \
                                            || ((core_regs) == HAL_SBS_CORE_SAU_REG))

/*! Macro to check the non-secure Core lock registers */
#define IS_SBS_NS_LOCK_CORE_REGS(core_regs) ((((core_regs) & (HAL_SBS_CORE_NSEC_ALL_REGS)) != 0U) \
                                             && (((core_regs) & (~HAL_SBS_CORE_NSEC_ALL_REGS)) == 0U))

/*! Macro to check the non-secure Core locked registers */
#define IS_SBS_NS_LOCKED_CORE_REGS(core_regs) (((core_regs) == HAL_SBS_CORE_VTOR_REG) \
                                               || ((core_regs) == HAL_SBS_CORE_MPU_REG))
#else
/*! Macro to check the Core locked registers */
#define IS_SBS_LOCKED_CORE_REGS(core_regs) (((core_regs) == HAL_SBS_CORE_VTOR_REG) \
                                            || ((core_regs) == HAL_SBS_CORE_MPU_REG))
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/*! Macro to check the FLASH bank swap mode */
#define IS_SBS_FLASH_BANK_MODE(bank_swap)  \
  (((bank_swap) == HAL_SBS_FLASH_BANK_NOT_SWAPPED) \
   || ((bank_swap) == HAL_SBS_FLASH_BANK_SWAPPED))

/*! RSS command check macro */
#define IS_RSS_COMMAND(command) ((command) <= 0xFFFFU)
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup SBS_Exported_Functions
  * @{
  */

/** @addtogroup SBS_Exported_Functions_Group1
  * @{
  This section provides functions to manage the fast mode plus functions :
  - Call HAL_SBS_EnableFastModePlus() function to enable the fast mode plus capability.
  - Call HAL_SBS_DisableFastModePlus() function to disable the fast mode plus capability.
  - Call HAL_SBS_IsEnabledFastModePlus() function to check if the fast mode plus capability is enabled.
  */

/**
  * @brief  Enable the fast mode plus driving capability.
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SBS_DRIVE_PB6
  *         @arg @ref HAL_SBS_DRIVE_PB7
  *         @arg @ref HAL_SBS_DRIVE_PB9
  *         @arg @ref HAL_SBS_DRIVE_ALL
  */
void HAL_SBS_EnableFastModePlus(uint32_t fast_mode_plus)
{
  ASSERT_DBG_PARAM(IS_SBS_SET_FAST_MODE_PLUS(fast_mode_plus));

  LL_SBS_EnableFastModePlus(fast_mode_plus);
}

/**
  * @brief  Disable the fast mode plus driving capability.
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SBS_DRIVE_PB6
  *         @arg @ref HAL_SBS_DRIVE_PB7
  *         @arg @ref HAL_SBS_DRIVE_PB9
  *         @arg @ref HAL_SBS_DRIVE_ALL
  */
void HAL_SBS_DisableFastModePlus(uint32_t fast_mode_plus)
{
  ASSERT_DBG_PARAM(IS_SBS_SET_FAST_MODE_PLUS(fast_mode_plus));

  LL_SBS_DisableFastModePlus(fast_mode_plus);
}

/**
  * @brief  Check if the fast mode plus driving capability is enabled.
  * @param  fast_mode_plus This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_DRIVE_PB6
  *         @arg @ref HAL_SBS_DRIVE_PB7
  *         @arg @ref HAL_SBS_DRIVE_PB9
  * @retval hal_sbs_fast_mode_plus_status_t Fast mode plus status.
  */
hal_sbs_fast_mode_plus_status_t HAL_SBS_IsEnabledFastModePlus(uint32_t fast_mode_plus)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_FAST_MODE_PLUS(fast_mode_plus));

  return (hal_sbs_fast_mode_plus_status_t)LL_SBS_IsEnabledFastModePlus(fast_mode_plus);
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group2
  * @{
  This section provides functions to manage the I2C SMBUS functions :
  - Call HAL_SBS_EnableI2CSMBUS() function to enable the I2Cx SMBUS.
  - Call HAL_SBS_DisableI2CSMBUS() function to disable the I2Cx SMBUS.
  - Call HAL_SBS_IsEnabledI2CSMBUS() function to check if the I2Cx SMBUS is enabled.
  */

/**
  * @brief Enable the SMBUS on the I2Cx.
  * @param i2c_smbus This parameter can be one or a combination of the following values:
  *        @arg @ref HAL_SBS_I2C1_SMBUS
  *        @arg @ref HAL_SBS_I2C3_SMBUS (*)
  *        @arg @ref HAL_SBS_I2C4_SMBUS (*)
  *        @arg @ref HAL_SBS_I2C_SMBUS_ALL
  * @note  (*) value not defined in all devices
  */
void HAL_SBS_EnableI2CSMBUS(uint32_t i2c_smbus)
{
  ASSERT_DBG_PARAM(IS_SBS_SET_I2C_SMBUS(i2c_smbus));

  LL_SBS_EnableI2CSMBUS(i2c_smbus);
}

/**
  * @brief Disable the SMBUS on the I2Cx.
  * @param i2c_smbus This parameter can be one or a combination of the following values:
  *        @arg @ref HAL_SBS_I2C1_SMBUS
  *        @arg @ref HAL_SBS_I2C3_SMBUS (*)
  *        @arg @ref HAL_SBS_I2C4_SMBUS (*)
  *        @arg @ref HAL_SBS_I2C_SMBUS_ALL
  * @note  (*) value not defined in all devices
  */
void HAL_SBS_DisableI2CSMBUS(uint32_t i2c_smbus)
{
  ASSERT_DBG_PARAM(IS_SBS_SET_I2C_SMBUS(i2c_smbus));

  LL_SBS_DisableI2CSMBUS(i2c_smbus);
}

/**
  * @brief  Check if the SMBUS I2C is enabled.
  * @param  i2c_smbus This parameter can be one of the following values:
  *        @arg @ref HAL_SBS_I2C1_SMBUS
  *        @arg @ref HAL_SBS_I2C3_SMBUS (*)
  *        @arg @ref HAL_SBS_I2C4_SMBUS (*)
  * @note   (*) value not defined in all devices
  * @retval hal_sbs_i2c_smbus_status_t SMBUS I2C status.
  */
hal_sbs_i2c_smbus_status_t HAL_SBS_IsEnabledI2CSMBUS(uint32_t i2c_smbus)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_I2C_SMBUS(i2c_smbus));

  return (hal_sbs_i2c_smbus_status_t)LL_SBS_IsEnabledI2CSMBUS(i2c_smbus);
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group3
  * @{
  This section provides functions to manage the floating point interrupts:
  - Call HAL_SBS_EnableFPUIT() to enable the floating point unit interrupt(s).
  - Call HAL_SBS_DisableFPUIT() to disable the floating point unit interrupt(s).
  - Call HAL_SBS_IsEnabledFPUIT() to check if the floating point unit interrupt is enabled.
  */

/**
  * @brief  Enable the floating point unit interrupt(s).
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SBS_IT_FPU_IOC
  *         @arg @ref HAL_SBS_IT_FPU_DZC
  *         @arg @ref HAL_SBS_IT_FPU_UFC
  *         @arg @ref HAL_SBS_IT_FPU_OFC
  *         @arg @ref HAL_SBS_IT_FPU_IDC
  *         @arg @ref HAL_SBS_IT_FPU_IXC
  *         @arg @ref HAL_SBS_IT_FPU_ALL
  */
void HAL_SBS_EnableFPUIT(uint32_t floating_point)
{
  ASSERT_DBG_PARAM(IS_SBS_SET_FLOATING_POINT_IT(floating_point));

  LL_SBS_EnableFPUIT(floating_point);
}

/**
  * @brief  Disable the floating point unit interrupt(s).
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SBS_IT_FPU_IOC
  *         @arg @ref HAL_SBS_IT_FPU_DZC
  *         @arg @ref HAL_SBS_IT_FPU_UFC
  *         @arg @ref HAL_SBS_IT_FPU_OFC
  *         @arg @ref HAL_SBS_IT_FPU_IDC
  *         @arg @ref HAL_SBS_IT_FPU_IXC
  *         @arg @ref HAL_SBS_IT_FPU_ALL
  */
void HAL_SBS_DisableFPUIT(uint32_t floating_point)
{
  ASSERT_DBG_PARAM(IS_SBS_SET_FLOATING_POINT_IT(floating_point));

  LL_SBS_DisableFPUIT(floating_point);
}

/**
  * @brief  Check if the floating point unit interrupt is enabled.
  * @param  floating_point This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_IT_FPU_IOC
  *         @arg @ref HAL_SBS_IT_FPU_DZC
  *         @arg @ref HAL_SBS_IT_FPU_UFC
  *         @arg @ref HAL_SBS_IT_FPU_OFC
  *         @arg @ref HAL_SBS_IT_FPU_IDC
  *         @arg @ref HAL_SBS_IT_FPU_IXC
  * @retval hal_sbs_it_fpu_status_t Floating point interrupt status.
  */
hal_sbs_it_fpu_status_t HAL_SBS_IsEnabledFPUIT(uint32_t floating_point)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_FLOATING_POINT_IT(floating_point));

  return (hal_sbs_it_fpu_status_t)LL_SBS_IsEnabledFPUIT(floating_point);
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group4
  * @{
  This section provides functions to manage the TIM break inputs:
  - Call HAL_SBS_EnableTIMBreakInputs() to enable the TIM break inputs.
  - Call HAL_SBS_DisableTIMBreakInputs() to disable the TIM break inputs.
  - Call HAL_SBS_IsEnabledTIMBreakInputs() to check if the TIM break inputs is enabled.
  */

/**
  * @brief  Enable the TIM break inputs.
  * @param  break_input This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SBS_DCACHE_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_PVD
  *         @arg @ref HAL_SBS_SRAM_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_LOCKUP_OUT
  * @note   (*) TIM break inputs disabling can only be done by a hardware reset.
  */
void HAL_SBS_EnableTIMBreakInputs(uint32_t break_input)
{
  ASSERT_DBG_PARAM(IS_SBS_SET_TIM_BREAK_INPUTS(break_input));

  LL_SBS_EnableTIMBreakInputs(break_input);
}

/**
  * @brief  Disable the TIM break inputs.
  * @param  break_input This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SBS_FLASH_ECC_DOUBLE_ERROR
  */
void HAL_SBS_DisableTIMBreakInputs(uint32_t break_input)
{
  ASSERT_DBG_PARAM(IS_SBS_DISABLE_TIM_BREAK_INPUTS(break_input));

  LL_SBS_DisableTIMBreakInputs(break_input);
}

/**
  * @brief  Check if the TIM break inputs is enabled.
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_DCACHE_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_PVD
  *         @arg @ref HAL_SBS_SRAM_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_LOCKUP_OUT
  * @retval hal_sbs_tim_break_input_status_t TIM break inputs status.
  */
hal_sbs_tim_break_input_status_t HAL_SBS_IsEnabledTIMBreakInputs(uint32_t break_input)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_TIM_BREAK_INPUTS(break_input));

  return (hal_sbs_tim_break_input_status_t)LL_SBS_IsEnabledTIMBreakInputs(break_input);
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group5
  * @{
  This section provides functions to control the compensation cell:
  - Call HAL_SBS_SetCompensationCellCodeSrc() to set the compensation cell code source.
  - Call HAL_SBS_GetCompensationCellCodeSrc() to get the compensation cell code source.
  - Call HAL_SBS_EnableCompensationCell() to enable the I/O compensation cell.
  - Call HAL_SBS_DisableCompensationCell() to disable the I/O compensation cell.
  - Call HAL_SBS_IsEnabledCompensationCell() to check if the I/O compensation cell is enabled.
  */

/**
  * @brief  Set the compensation cell code source.
  * @param  comp_cell This parameter can have the following value:
  *         @arg @ref HAL_SBS_CCELL_VDDIO
  * @param  code_select This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_CCELL_CODE_DEFAULT
  *         @arg @ref HAL_SBS_CCELL_CODE_CUSTOM
  */
void HAL_SBS_SetCompensationCellCodeSrc(uint32_t comp_cell, hal_sbs_ccell_code_src_t code_select)
{
  ASSERT_DBG_PARAM(IS_SBS_CCELL_CODE(code_select));
  ASSERT_DBG_PARAM(IS_SBS_CCELL(comp_cell));

  LL_SBS_SetCompensationCellCodeSrc(comp_cell, (uint32_t)code_select);
}

/**
  * @brief  Get the compensation cell code source.
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_CCELL_VDDIO
  * @retval hal_sbs_ccell_code_src_t Compensation cell code source.
  */
hal_sbs_ccell_code_src_t HAL_SBS_GetCompensationCellCodeSrc(uint32_t comp_cell)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_CCELL(comp_cell));

  return (hal_sbs_ccell_code_src_t)LL_SBS_GetCompensationCellCodeSrc(comp_cell);
}

/**
  * @brief  Enable the I/O compensation cell.
  * @param  comp_cell This parameter can have the following value:
  *         @arg @ref HAL_SBS_CCELL_VDDIO

  * @retval HAL_ERROR The compensation cell was not enabled within the allowed timeout period.
  * @retval HAL_OK    Compensation cell is enabled.
  */
hal_status_t HAL_SBS_EnableCompensationCell(uint32_t comp_cell)
{
  uint32_t timeout = (SBS_CCELL_MAX_DELAY_MS * (SystemCoreClock / 1000U)) + 1U;
  uint32_t comp_rdy;

  ASSERT_DBG_PARAM(IS_SBS_CCELL(comp_cell));

  LL_SBS_EnableCompensationCell(comp_cell);

  while (timeout > 0U)
  {
    comp_rdy = LL_SBS_IsActiveFlag_RDY1() << SBS_CCCSR_EN1_Pos;

    if ((comp_rdy & comp_cell) == comp_cell)
    {
      return HAL_OK;
    }

    timeout--;
  }

  return HAL_ERROR;
}

/**
  * @brief  Disable the I/O compensation cell.
  * @param  comp_cell This parameter can have the following value:
  *         @arg @ref HAL_SBS_CCELL_VDDIO
  */
void HAL_SBS_DisableCompensationCell(uint32_t comp_cell)
{
  ASSERT_DBG_PARAM(IS_SBS_CCELL(comp_cell));

  LL_SBS_DisableCompensationCell(comp_cell);
}

/**
  * @brief  Check if the I/O compensation cell is enabled.
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_CCELL_VDDIO
  * @retval hal_sbs_ccell_status_t I/O Compensation cell status.
  */
hal_sbs_ccell_status_t HAL_SBS_IsEnabledCompensationCell(uint32_t comp_cell)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_CCELL(comp_cell));

  return ((hal_sbs_ccell_status_t)LL_SBS_IsEnabledCompensationCell(comp_cell));
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group6
  * @{
  This section provides functions to manage the compensation cell:
  - Call HAL_SBS_GetPMOSCompensationCellValue() to get the PMOS compensation value of selected compensation cell.
  - Call HAL_SBS_GetNMOSCompensationCellValue() to get the NMOS compensation value of selected compensation cell.
  - Call HAL_SBS_SetConfigxMOSCompensationCellCode() to set the compensation cell code.
  - Call HAL_SBS_GetConfigxMOSCompensationCellCode() to get the compensation cell code.
  */

/**
  * @brief  Get the PMOS compensation value of the selected compensation cell.
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_CCELL_VDDIO
  * @retval uint32_t Value of the PMOS compensation cell.
  */
uint32_t HAL_SBS_GetPMOSCompensationCellValue(uint32_t comp_cell)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_CCELL(comp_cell));

  return (LL_SBS_GetPMOSCompensationCellValue(comp_cell));
}

/**
  * @brief  Get the NMOS compensation value of the selected compensation cell.
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_CCELL_VDDIO
  * @retval uint32_t Value of the NMOS compensation cell.
  */
uint32_t HAL_SBS_GetNMOSCompensationCellValue(uint32_t comp_cell)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_CCELL(comp_cell));

  return (LL_SBS_GetNMOSCompensationCellValue(comp_cell));
}

/**
  * @brief  Set the compensation cell code.
  * @param  comp_cell This parameter can have the following value:
  *         @arg @ref HAL_SBS_CCELL_VDDIO
  * @param  pmos_code PMOS value to be applied to the compensation cell
  * @param  nmos_code NMOS value to be applied to the compensation cell
  */
void HAL_SBS_SetConfigxMOSCompensationCellCode(uint32_t comp_cell, uint32_t pmos_code, uint32_t nmos_code)
{
  ASSERT_DBG_PARAM(IS_SBS_CCELL(comp_cell));
  ASSERT_DBG_PARAM(IS_SBS_XMOS_CCELL_CODE(pmos_code, nmos_code));

  if ((comp_cell & HAL_SBS_CCELL_VDDIO) != 0U)
  {
    LL_SBS_SetxMOSVddIOCompensationCellCode(pmos_code, nmos_code);
  }
}

/**
  * @brief  Get the compensation cell code.
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_CCELL_VDDIO
  * @param  p_pmos_code Pointer to PMOS register of the selected compensation cell
  * @param  p_nmos_code Pointer to NMOS register of the selected compensation cell
  */
void HAL_SBS_GetConfigxMOSCompensationCellCode(uint32_t comp_cell, uint32_t *p_pmos_code, uint32_t *p_nmos_code)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_CCELL(comp_cell));
  ASSERT_DBG_PARAM(p_pmos_code != NULL);
  ASSERT_DBG_PARAM(p_nmos_code != NULL);

  *p_pmos_code = (LL_SBS_GetPMOSCompensationCellCode(comp_cell) >> (STM32_POSITION_VAL(comp_cell << 1U) * 4U));
  *p_nmos_code = (LL_SBS_GetNMOSCompensationCellCode(comp_cell) >> (STM32_POSITION_VAL(comp_cell) * 4U));
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group7
  * @{
  This section provides functions to enable/disable the NMI in case of double ECC error in FLASH Interface:
  - Call HAL_SBS_FLASH_EnableECCNMI() to enable the NMI in case of double ECC error in FLASH Interface.
  - Call HAL_SBS_FLASH_DisableECCNMI() to disable the NMI in case of double ECC error in FLASH Interface.
  - Call HAL_SBS_FLASH_IsEnabledECCNMI() to Check if the NMI is Enabled in case of double ECC error in
    FLASH Interface.
  */

/**
  * @brief  Enable the NMI in case of double ECC error in FLASH Interface.
  */
void HAL_SBS_FLASH_EnableECCNMI(void)
{
  LL_SBS_FLASH_EnableECCNMI();
}

/**
  * @brief  Disable the NMI in case of double ECC error in FLASH Interface.
  */
void HAL_SBS_FLASH_DisableECCNMI(void)
{
  LL_SBS_FLASH_DisableECCNMI();
}

/**
  * @brief  Check if the NMI is Enabled in case of double ECC error in FLASH Interface.
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_SBS_FLASH_IsEnabledECCNMI(void)
{
  return (LL_SBS_FLASH_IsEnabledECCNMI());
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group8
  * @{
  This section provides functions to set and get the HDP level value :
  - Call HAL_SBS_SetHDPLevelValue() to set the HDP level value.
  - Call HAL_SBS_GetHDPLevelValue() to get the HDP level value.
  - Call HAL_SBS_SetHDPOBKLevelValue() to set the OBK-HDP level value.
  - Call HAL_SBS_GetHDPOBKLevelValue() to get the OBK-HDP level value.
  */

/**
  * @brief  Set the HDP level value.
  * @param  value Value of the HDP level.
  *         This parameter can be one of the following values:
  *         @arg @ref  HAL_SBS_HDP_LEVEL_0
  *         @arg @ref  HAL_SBS_HDP_LEVEL_1
  *         @arg @ref  HAL_SBS_HDP_LEVEL_2
  *         @arg @ref  HAL_SBS_HDP_LEVEL_3
  * @retval HAL_ERROR Invalid HDP level value not set.
  * @retval HAL_OK    Valid HDP level value set correctly.
  */
hal_status_t HAL_SBS_SetHDPLevelValue(hal_sbs_hdp_level_value_t value)
{
  hal_sbs_hdp_level_value_t prev_hdp_level_value;

  ASSERT_DBG_PARAM(IS_SBS_HDP_LEVEL(value));

  prev_hdp_level_value = (hal_sbs_hdp_level_value_t)LL_SBS_GetHDPLevel();

  if (((value == HAL_SBS_HDP_LEVEL_1) && (prev_hdp_level_value == HAL_SBS_HDP_LEVEL_0))    \
      || ((value == HAL_SBS_HDP_LEVEL_2) && (prev_hdp_level_value == HAL_SBS_HDP_LEVEL_1)) \
      || ((value == HAL_SBS_HDP_LEVEL_3) && (prev_hdp_level_value == HAL_SBS_HDP_LEVEL_2)))
  {
    LL_SBS_IncrementHDPLevel();

    return HAL_OK;
  }

  return HAL_ERROR;
}

/**
  * @brief  Get the HDP level value.
  * @retval hal_sbs_hdp_level_value_t HDPL value.
  */
hal_sbs_hdp_level_value_t HAL_SBS_GetHDPLevelValue(void)
{
  return ((hal_sbs_hdp_level_value_t)LL_SBS_GetHDPLevel());
}

/**
  * @brief  Set the OBK-HDP level value.
  * @param  value Value of the increment to be added to HDPL value to generate the OBK-HDPL.
  *         This parameter can be one of the following values:
  *         @arg @ref  HAL_SBS_HDP_OBK_LEVEL_0 : HDPL (default value)
  *         @arg @ref  HAL_SBS_HDP_OBK_LEVEL_1 : HDPL + 1
  *         @arg @ref  HAL_SBS_HDP_OBK_LEVEL_2 : HDPL + 2
  *         @arg @ref  HAL_SBS_HDP_OBK_LEVEL_3 : HDPL + 3
  */
void HAL_SBS_SetHDPOBKLevelValue(hal_sbs_hdp_obk_level_value_t value)
{
  ASSERT_DBG_PARAM(IS_SBS_HDPOBK_SELECTION(value));

  LL_SBS_SetOBKHDPLevel((uint32_t)value);
}

/**
  * @brief  Get the OBK-HDP level value.
  * @retval hal_sbs_hdp_obk_level_value_t  OBK-HDP level value.
  */
hal_sbs_hdp_obk_level_value_t HAL_SBS_GetHDPOBKLevelValue(void)
{
  return ((hal_sbs_hdp_obk_level_value_t)LL_SBS_GetOBKHDPLevel());
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group9
  * @{
  This section provides functions to set and get the EPOCH selection to be sent to SAES IP:
  - Call HAL_SBS_SetEPOCHSelection() to set EPOCH selection to be sent to SAES IP to encrypt/decrypt keys.
  - Call HAL_SBS_GetEPOCHSelection() to get the EPOCH selection sent to SAES IP to encrypt/decrypt keys.
  */

/**
  * @brief  Set EPOCH selection to be sent to SAES IP to encrypt/decrypt keys.
  * @param  epoch_selection: This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_EPOCH_NSEC  : EPOCH non-secure selected.
  *         @arg @ref HAL_SBS_EPOCH_SEC   : EPOCH secure selected.
  *         @arg @ref HAL_SBS_EPOCH_CLEAR : EPOCH all zeros.
  */
void HAL_SBS_SetEPOCHSelection(hal_sbs_epoch_selection_t epoch_selection)
{
  ASSERT_DBG_PARAM(IS_SBS_EPOCH_SELECTION(epoch_selection));

  LL_SBS_SetEPOCHSelection((uint32_t) epoch_selection);
}

/**
  * @brief  Get EPOCH selection sent to SAES IP to encrypt/decrypt keys.
  * @retval hal_sbs_epoch_selection_t  EPOCH selection selection.
  */
hal_sbs_epoch_selection_t HAL_SBS_GetEPOCHSelection(void)
{
  return ((hal_sbs_epoch_selection_t)LL_SBS_GetEPOCHSelection());
}
/**
  * @}
 */

/** @addtogroup SBS_Exported_Functions_Group10
  * @{
  This section provides functions to control the debug :
  - Call HAL_SBS_LockAPBAHBAccessPorts() to lock the APB, AHB access ports.
  - Call HAL_SBS_UnlockAPBAHBAccessPorts() to unlock the APB, AHB access ports.
  - Call HAL_SBS_IsLockedAPBAHBAccessPorts() to check the APB, AHB access ports lock status.
  - Call HAL_SBS_LockCoreDebugInterface() to lock the debug interface.
  - Call HAL_SBS_UnlockCoreDebugInterface() to unlock the debug interface.
  - Call HAL_SBS_IsLockedCoreDebugInterface() to check the debug interface lock status.
  - Call HAL_SBS_SetAuthenticatedDebugHDPLevel() to set the HDP level at which the authenticated debug opens.
  - Call HAL_SBS_GetAuthenticatedDebugHDPLevel() to get the HDP level at which the authenticated debug opens.
  - Call HAL_SBS_LockDebugConfig() to lock the access to the debug configuration.
  - Call HAL_SBS_IsLockedDebugConfig() to check the debug configuration lock status.
  - Call HAL_SBS_LockSecAHBAccessPort() to lock the secure AHB access port.
  - Call HAL_SBS_UnlockSecAHBAccessPort() to unlock the secure AHB access port.
  - Call HAL_SBS_IsLockedSecAHBAccessPort() to check if the secure AHB access port is locked.
  - Call HAL_SBS_SetAuthenticatedDebugSecAttr() to set the authenticated debug security access.
  - Call HAL_SBS_GetAuthenticatedDebugSecAttr() to get the authenticated debug security access.
  */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the device APB/AHB access ports.
  */
void HAL_SBS_LockAPBAHBAccessPorts(void)
{
  LL_SBS_LockAPBAHBAccessPorts();
}

/**
  * @brief  Unlock the device APB/AHB access ports.
  */
void HAL_SBS_UnlockAPBAHBAccessPorts(void)
{
  LL_SBS_UnlockAPBAHBAccessPorts();
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the device APB, AHB access ports are locked.
  * @retval hal_sbs_access_port_lock_status_t lock access port status.
  */
hal_sbs_access_port_lock_status_t HAL_SBS_IsLockedAPBAHBAccessPorts(void)
{
  return ((hal_sbs_access_port_lock_status_t)LL_SBS_IsLockedAPBAHBAccessPorts());
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the debug interface when the hide protection level is authorized.
  */
void HAL_SBS_LockCoreDebugInterface(void)
{
  LL_SBS_LockDebug();
}

/**
  * @brief  Unlock the debug interface when the hide protection level is authorized.
  */
void HAL_SBS_UnlockCoreDebugInterface(void)
{
  LL_SBS_UnlockDebug();
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the debug interface is locked.
  * @retval hal_sbs_core_debug_itf_lock_status_t debug interface status.
  */
hal_sbs_core_debug_itf_lock_status_t HAL_SBS_IsLockedCoreDebugInterface(void)
{
  return ((hal_sbs_core_debug_itf_lock_status_t)LL_SBS_IsLockedDebug());
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the HDP level at which the authenticated debug opens.
  * @param  level Hide protection level at which the authenticated debug opens
  *         This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_HDP_LEVEL_1
  *         @arg @ref HAL_SBS_HDP_LEVEL_2
  *         @arg @ref HAL_SBS_HDP_LEVEL_3
  */
void HAL_SBS_SetAuthenticatedDebugHDPLevel(hal_sbs_hdp_level_value_t level)
{
  ASSERT_DBG_PARAM(IS_SBS_AUTHENTICATED_HDP_LEVEL(level));

  LL_SBS_SetAuthenticatedDbgHDPLevel((uint32_t)level);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the HDP level at which the authenticated debug opens.
  * @retval hal_sbs_hdp_level_value_t Hide protection level at which the authenticated debug opens.
  */
hal_sbs_hdp_level_value_t HAL_SBS_GetAuthenticatedDebugHDPLevel(void)
{
  return ((hal_sbs_hdp_level_value_t)LL_SBS_GetAuthenticatedDbgHDPLevel());
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the access to the debug configuration.
  * @note   Lock debug configuration is released only by a reset.
  */
void HAL_SBS_LockDebugConfig(void)
{
  LL_SBS_LockDebugConfig();
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the debug configuration is locked.
  * @retval hal_sbs_debug_config_lock_status_t Lock debug configuration register status.
  */
hal_sbs_debug_config_lock_status_t HAL_SBS_IsLockedDebugConfig(void)
{
  return ((hal_sbs_debug_config_lock_status_t)LL_SBS_IsLockedDebugConfig());
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the authenticated debug security access.
  * @param  security Debug opening for secure/non-secure or non-secure only
  *         This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_AUTHENTICATED_DEBUG_SEC_NSEC : Debug opening for secure and non-secure.
  *         @arg @ref HAL_SBS_AUTHENTICATED_DEBUG_NSEC     : Debug opening for non-secure only.
  */
void HAL_SBS_SetAuthenticatedDebugSecAttr(hal_sbs_authenticated_debug_sec_attr_t  security)
{
  ASSERT_DBG_PARAM(IS_SBS_AUTHENTICATED_DEBUG_SEC(security));

  LL_SBS_SetAuthenticatedDebugSecAttr((uint32_t)security);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the authenticated debug security access.
  * @retval hal_sbs_authenticated_debug_sec_attr_t  The authenticated debug security access.
  */
hal_sbs_authenticated_debug_sec_attr_t  HAL_SBS_GetAuthenticatedDebugSecAttr(void)
{
  return ((hal_sbs_authenticated_debug_sec_attr_t)LL_SBS_GetAuthenticatedDebugSecAttr());
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the secure AHB access port.
  */
void HAL_SBS_LockSecAHBAccessPort(void)
{
  LL_SBS_LockSecAHBAccessPort();
}

/**
  * @brief  Unlock the secure AHB access port.
  */
void HAL_SBS_UnlockSecAHBAccessPort(void)
{
  LL_SBS_UnlockSecAHBAccessPort();
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the secure AHB access port is locked.
  * @retval hal_sbs_access_port_lock_status_t Secure AHB access port lock status.
  */
hal_sbs_access_port_lock_status_t HAL_SBS_IsLockedSecAHBAccessPort(void)
{
  return ((hal_sbs_access_port_lock_status_t)LL_SBS_IsLockedSecAHBAccessPort());
}

/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group11
  * @{
  This section provides functions to manage the lock feature :
  - Call HAL_SBS_LockCoreRegisters() to lock the Core registers.
  - Call HAL_SBS_IsLockedCoreRegisters() to check if the Core registers are locked.
  - Call HAL_SBS_NS_LockCoreRegisters() to lock the non-secure Core registers.
  - Call HAL_SBS_NS_IsLockedCoreRegisters() to check if the non-secure Core registers are locked.
  */

/**
  * @brief Lock the Core registers.
  * @param core_regs This parameter can be one or a combination of the following values:
  *        @arg @ref HAL_SBS_CORE_VTOR_REG
  *        @arg @ref HAL_SBS_CORE_AIRCR_REG (*)
  *        @arg @ref HAL_SBS_CORE_MPU_REG
  *        @arg @ref HAL_SBS_CORE_SAU_REG (*)
  *        @arg @ref HAL_SBS_CORE_ALL_REGS
  * @note (*) Only available in secure context
  * @note The unlock can only be done with a system reset
  */
void HAL_SBS_LockCoreRegisters(uint32_t core_regs)
{
  ASSERT_DBG_PARAM(IS_SBS_LOCK_CORE_REGS(core_regs));

  LL_SBS_CPU_LockRegisters(core_regs);
}

/**
  * @brief  Check if the Core registers are locked.
  * @param  core_regs This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_CORE_VTOR_REG
  *         @arg @ref HAL_SBS_CORE_AIRCR_REG
  *         @arg @ref HAL_SBS_CORE_MPU_REG
  *         @arg @ref HAL_SBS_CORE_SAU_REG
  * @retval hal_sbs_core_reg_lock_status_t SBS Core registers lock status.
  */
hal_sbs_core_reg_lock_status_t HAL_SBS_IsLockedCoreRegisters(uint32_t core_regs)
{
  ASSERT_DBG_PARAM(IS_SBS_LOCKED_CORE_REGS(core_regs));

  return (hal_sbs_core_reg_lock_status_t)LL_SBS_CPU_IsLockedRegisters(core_regs);
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief Lock the non-secure Core registers.
  * @param core_regs This parameter can be one or a combination of the following values:
  *        @arg @ref HAL_SBS_CORE_VTOR_REG
  *        @arg @ref HAL_SBS_CORE_MPU_REG
  *        @arg @ref HAL_SBS_CORE_NSEC_ALL_REGS
  * @note The unlock can only be done with a system reset
  */
void HAL_SBS_NS_LockCoreRegisters(uint32_t core_regs)
{
  ASSERT_DBG_PARAM(IS_SBS_NS_LOCK_CORE_REGS(core_regs));

  LL_SBS_CPUNS_LockRegisters(core_regs);
}

/**
  * @brief  Check if the non-secure Core registers are locked.
  * @param  core_regs This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_CORE_VTOR_REG
  *         @arg @ref HAL_SBS_CORE_MPU_REG
  * @retval hal_sbs_core_reg_lock_status_t SBS non-secure Core registers lock status.
  */
hal_sbs_core_reg_lock_status_t HAL_SBS_NS_IsLockedCoreRegisters(uint32_t core_regs)
{
  ASSERT_DBG_PARAM(IS_SBS_NS_LOCKED_CORE_REGS(core_regs));

  return (hal_sbs_core_reg_lock_status_t)LL_SBS_CPUNS_IsLockedRegisters(core_regs);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group12
  * @{
  This section provides functions to manage the flash bank swap feature :
  - Call HAL_SBS_FLASH_SetBankSwapMode() to select the SBS flash bank swapping.
  - Call HAL_SBS_FLASH_GetBankSwapMode() to get the SBS flash bank swapping.
  - Call HAL_SBS_FLASH_LockBankSwap() to lock the SBS flash bank swapping configuration.
  - Call HAL_SBS_FLASH_IsLockedBankSwap() to check the SBS flash bank swapping configuration is locked.
  */

/**
  * @brief Set the SBS flash bank swapping.
  * @param  bank_swap This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_FLASH_BANK_NOT_SWAPPED
  *         @arg @ref HAL_SBS_FLASH_BANK_SWAPPED
  * @retval HAL_OK Bank swap has been set successfully.
  */
hal_status_t HAL_SBS_FLASH_SetBankSwapMode(hal_sbs_flash_bank_swap_status_t bank_swap)
{
  ASSERT_DBG_PARAM(IS_SBS_FLASH_BANK_MODE(bank_swap));

  LL_SBS_FLASH_SetBankSwapMode((uint32_t)bank_swap);

  return HAL_OK;
}

/**
  * @brief Get the SBS flash bank swapping.
  * @retval hal_sbs_flash_bank_swap_status_t SBS flash bank swapping selection.
  */
hal_sbs_flash_bank_swap_status_t HAL_SBS_FLASH_GetBankSwapMode(void)
{
  return (hal_sbs_flash_bank_swap_status_t)LL_SBS_FLASH_GetBankSwapMode();
}

/**
  * @brief Lock the SBS flash bank swapping configuration.
  */
void HAL_SBS_FLASH_LockBankSwap(void)
{
  LL_SBS_FLASH_LockBankSwap();
}

/**
  * @brief  Check if the SBS flash bank swapping configuration is locked.
  * @retval hal_sbs_flash_bank_swap_lock_status_t SBS flash bank swapping configuration lock status.
  */
hal_sbs_flash_bank_swap_lock_status_t HAL_SBS_FLASH_IsLockedBankSwap(void)
{
  return (hal_sbs_flash_bank_swap_lock_status_t)LL_SBS_FLASH_IsLockedBankSwap();
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group13
  * @{
  This section provides functions to manage the memories erase status feature :
  - Call HAL_SBS_GetMemoryEraseStatus() to check the memories erase status flags.
  - Call HAL_SBS_CleanMemoryEraseStatus() to get clear the memories erase status pending flags.
  */

/**
  * @brief Check if an SBS memories erase status flag is active or not.
  * @param memory This parameter can be one of the following values:
  *        @arg @ref HAL_SBS_ICACHE_PKARAM_ERASED
  *        @arg @ref HAL_SBS_ICACHE_DCACHE_SRAMS_PKARAM_ERASED
  * @retval hal_sbs_memory_erase_status_t Memory erase status.
  */
hal_sbs_memory_erase_status_t HAL_SBS_GetMemoryEraseStatus(uint32_t memory)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_MEMORY_ERASE(memory));

  return (hal_sbs_memory_erase_status_t)LL_SBS_IsActiveFlag(memory);
}

/**
  * @brief Clear the SBS memories erase status pending flag(s).
  * @param memory This parameter can be one or a combination of the following values:
  *        @arg @ref HAL_SBS_ICACHE_PKARAM_ERASED
  *        @arg @ref HAL_SBS_ICACHE_DCACHE_SRAMS_PKARAM_ERASED
  *        @arg @ref HAL_SBS_ALL_MEMORIES_ERASED
  */
void HAL_SBS_CleanMemoryEraseStatus(uint32_t memory)
{
  ASSERT_DBG_PARAM(IS_SBS_CLEAN_MEMORY_ERASE(memory));

  LL_SBS_ClearFlag(memory);
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group14
  * @{
  This section provides functions to manage the RSS Command :
  - Call HAL_SBS_SetRSSCommand() to set a command to the RSS to be executed at next reset.
  - Call HAL_SBS_GetRSSCommand() to get the command sent to the RSS.
  */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the command passed to the RSS for execution at next reset.
  * @param  command Command passed to the RSS for execution at next reset
  *         This value is between 0 and 0xFFFF
  */
void HAL_SBS_SetRSSCommand(uint32_t command)
{
  ASSERT_DBG_PARAM(IS_RSS_COMMAND(command));

  LL_SBS_SetRSSCommand(command);
}

/**
  * @brief  Get the command passed to the RSS for execution at next reset.
  * @retval Command passed to the RSS for execution at next reset
  */
uint32_t HAL_SBS_GetRSSCommand(void)
{
  return (uint32_t)LL_SBS_GetRSSCommand();
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group15
  * @{
  This subsection contains SBS security attributes management:
  - Call HAL_SBS_SetSecAttr() to set the security access level attribute for item(s).
  - Call HAL_SBS_GetSecAttr() to get the security access level attribute of an item.
  */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the SBS security access level attribute for item(s).
  * @param  item This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SBS_SEC_ITEM_CLOCK
  *         @arg @ref HAL_SBS_SEC_ITEM_CLASSB
  *         @arg @ref HAL_SBS_SEC_ITEM_FPU
  *         @arg @ref HAL_SBS_SEC_ITEM_ALL
  * @param  sec_attr This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_SEC
  *         @arg @ref HAL_SBS_NSEC
  * @note   Only available from secure state.
  * @retval HAL_OK Security attribute has been set successfully.
  */
hal_status_t HAL_SBS_SetSecAttr(uint32_t item, hal_sbs_sec_attr_t sec_attr)
{
  ASSERT_DBG_PARAM(IS_SBS_SET_SEC_ITEM(item));
  ASSERT_DBG_PARAM(IS_SBS_ITEM_SEC_ATTR(sec_attr));

  LL_SBS_SetSecAttr(item, (uint32_t)sec_attr);

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the SBS security access level attribute of an item.
  * @param  item This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_SEC_ITEM_CLOCK
  *         @arg @ref HAL_SBS_SEC_ITEM_CLASSB
  *         @arg @ref HAL_SBS_SEC_ITEM_FPU
  * @retval The returned value can be one of the following values:
  *         @arg @ref HAL_SBS_SEC
  *         @arg @ref HAL_SBS_NSEC
  */
hal_sbs_sec_attr_t HAL_SBS_GetSecAttr(uint32_t item)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_SEC_ITEM(item));

  return ((hal_sbs_sec_attr_t)LL_SBS_GetSecAttr(item));
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
#endif /* USE_HAL_SBS_MODULE */
#endif /* SBS */

/**
  * @}
  */
