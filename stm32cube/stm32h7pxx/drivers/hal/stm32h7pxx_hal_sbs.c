/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_sbs.c
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

/** @addtogroup STM32H7Pxx_HAL_Driver
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

     - Manage the I/O compensation cell.
     - Activate and deactivate the connection to TIM1/8/15/16/17.
     - Activate and deactivate the FPU interrupts.
     - Manage the compensation cells.
     - Manage the debug.
     - Set and get the command to be sent to the RSS executed at the next reset.
     - Get and clear the memory erase flags.
     - Get the boot address.
  */
/**
  * @}
  */

/** @defgroup SBS_How_To_Use SBS How To Use
  * @{

# How to use the SBS HAL module driver

## The SBS HAL driver can be used as follows:

After startup, SBS peripheral is not active by default. Use HAL_RCC_SBS_EnableClock() function to enable
SBS APB3 clock.

This module provides different sets of APIs that allow to :


1. Analog IO switch supply :
   Several APIs are available to manage the analog IO switch supply
   - Configure the I/O analog switches supply:
     - This functionality is ensured by HAL_SBS_SetAnalogIOSwitchSupply() function.
   - Get the I/O analog switches supply configuration:
     - This functionality is ensured by HAL_SBS_GetAnalogIOSwitchSupply() function.

2. Manage floating point unit interrupts :
   Several APIs are available to manage the floating point unit interrupts
   - Enable and disable the floating point unit interrupts:
     - These functionalities are ensured respectively by HAL_SBS_EnableFPUIT() and HAL_SBS_DisableFPUIT().
   - Get the floating point unit interrupts state:
     - This functionality is ensured by HAL_SBS_IsEnabledFPUIT() function.

3. Manage TIM break inputs :
   This feature is used to control the system break interconnect to TIM1/8/15/16/17 break inputs
   - Enable the TIM break inputs:
     - This functionality is ensured by HAL_SBS_EnableTIMBreakInputs() function.
   - Check the TIM break inputs activation:
     - This functionality is ensured by HAL_SBS_IsEnabledTIMBreakInputs() function.
   - \b Note: The TIM break inputs disabling can only be done by a hardware reset.

4. Control the compensation cell :
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

5. Manage the compensation code :
   Several APIs are available to manage the compensation code
   - Get the compensation value of PMOS transistor :
     - This functionality is ensured by HAL_SBS_GetPMOSCompensationCellValue() function.
   - Get the compensation value of NMOS transistor :
     - This functionality is ensured by HAL_SBS_GetNMOSCompensationCellValue() function.
   - Set the compensation cell code:
     - This functionality is ensured by HAL_SBS_SetConfigxMOSCompensationCellCode() function.
   - Get the compensation cell code :
     - This functionality is ensured by HAL_SBS_GetConfigxMOSCompensationCellCode() function.

6. HDP levels management functions :
   Several APIs are available to manage HDPL
   - Set the HDPL value :
     - This functionality is ensured by HAL_SBS_SetHDPLevelValue() function.
   - Get the HDPL value :
     - This functionality is ensured by HAL_SBS_GetHDPLevelValue() function.

7. Debug control functions
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

8. Flag management functions :
   Several APIs are available on the header file as "static_inline" functions to manage the memories erase status
   - Check if the memories erase status flags is active or not :
     - This functionality is ensured by HAL_SBS_GetMemoryEraseStatus() function.

9. RSS Command selection functions :
   Several APIs are available to manage the RSS command
   - Set a command to the RSS to be executed at next reset :
     - This functionality is ensured by HAL_SBS_SetRSSCommand() function.
   - Get the command sent to the RSS :
     - This functionality is ensured by HAL_SBS_GetRSSCommand() function.

10. Boot address functions :
   - Get the boot address :
     - This functionality is ensured by HAL_SBS_GetBootAddress() function.

11. I/O speed optimization functions :
   Several APIs are available to manage the I/O speed optimization features
   - Enable and disable the I/O speed optimization:
    - This functionality is ensured respectively by HAL_SBS_EnableIOSpeedOptimization() function and
      HAL_SBS_DisableIOSpeedOptimization() function.
   - Check the I/O speed optimization status:
     - This functionality is ensured by HAL_SBS_IsEnabledIOSpeedOptimization() function.
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

/*! Analog switch supply check macro */
#define IS_SBS_ANALOG_SWITCH_SUPPLY(analog_switch) \
  (((analog_switch) == HAL_SBS_VDDA_SUPPLY)        \
   || ((analog_switch) == HAL_SBS_BOOSTER_SUPPLY)  \
   || ((analog_switch) == HAL_SBS_VDD_SUPPLY))

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

/*! Get TIM break inputs check macro */
#define IS_SBS_GET_TIM_BREAK_INPUTS(break_input)         \
  (((break_input) == HAL_SBS_SRAM1_ECC_DOUBLE_ERROR)     \
   || ((break_input) == HAL_SBS_SRAM2_ECC_DOUBLE_ERROR)  \
   || ((break_input) == HAL_SBS_SRAM3_ECC_DOUBLE_ERROR)  \
   || ((break_input) == HAL_SBS_SRAM4_ECC_DOUBLE_ERROR)  \
   || ((break_input) == HAL_SBS_ITCM_ECC_DOUBLE_ERROR)   \
   || ((break_input) == HAL_SBS_DTCM_ECC_DOUBLE_ERROR)   \
   || ((break_input) == HAL_SBS_BKPRAM_ECC_DOUBLE_ERROR) \
   || ((break_input) == HAL_SBS_LOCKUP_OUT)              \
   || ((break_input) == HAL_SBS_FLASH_ECC_DOUBLE_ERROR)  \
   || ((break_input) == HAL_SBS_PVD))

/*! Compensation cell check macro */
#define IS_SBS_CCELL(comp_cell) ((comp_cell) == HAL_SBS_CCELL_VDDIO)

/*! Compensation code check macro */
#define IS_SBS_CCELL_CODE(code_select)             \
  (((code_select) == HAL_SBS_CCELL_CODE_DEFAULT)   \
   || ((code_select) == HAL_SBS_CCELL_CODE_CUSTOM))

/*! Get compensation cell check macro */
#define IS_SBS_GET_CCELL(comp_cell)             \
  (((comp_cell) == HAL_SBS_CCELL_VDDIO))

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

/*! Get memory erase check macro */
#define IS_SBS_GET_MEMORY_ERASE(memory)      \
  (((memory) == HAL_SBS_BKPRAM_ERASED)       \
   || ((memory) == HAL_SBS_AXISRAM1_ERASED))

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
  This section provides functions to manage I/O capabilities :
  - Call HAL_SBS_SetAnalogIOSwitchSupply() function to set the I/O analog switches supply.
  - Call HAL_SBS_GetAnalogIOSwitchSupply() function to get the I/O analog switches supply.
  */

/**
  * @brief  Set the I/O analog switch supply.
  * @param  analog_switch This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_VDDA_SUPPLY
  *         @arg @ref HAL_SBS_BOOSTER_SUPPLY
  *         @arg @ref HAL_SBS_VDD_SUPPLY
  */
void HAL_SBS_SetAnalogIOSwitchSupply(hal_sbs_analog_switch_t analog_switch)
{
  ASSERT_DBG_PARAM(IS_SBS_ANALOG_SWITCH_SUPPLY(analog_switch));

  LL_SBS_SetAnalogIOSwitchSupply((uint32_t)analog_switch);
}

/**
  * @brief  Get the I/O analog switch supply.
  * @retval hal_sbs_analog_switch_t I/O Analog switch supply.
  */
hal_sbs_analog_switch_t HAL_SBS_GetAnalogIOSwitchSupply(void)
{
  return (hal_sbs_analog_switch_t) LL_SBS_GetAnalogIOSwitchSupply();
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group2
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

/** @addtogroup SBS_Exported_Functions_Group3
  * @{
  This section provides functions to manage the TIM break inputs:
  - Call HAL_SBS_EnableTIMBreakInputs() to enable the TIM break inputs.
  - Call HAL_SBS_IsEnabledTIMBreakInputs() to check if the TIM break inputs is enabled.
  - \b Note: The TIM break inputs disabling can only be done by a hardware reset.
  */

/**
  * @brief  Enable the TIM break inputs.
  * @param  break_input This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SBS_SRAM1_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_SRAM2_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_SRAM3_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_SRAM4_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_ITCM_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_DTCM_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_BKPRAM_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_LOCKUP_OUT
  *         @arg @ref HAL_SBS_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_PVD
  * @note   The TIM break input disabling can only be done by a hardware reset.
  */
void HAL_SBS_EnableTIMBreakInputs(uint32_t break_input)
{
  ASSERT_DBG_PARAM(IS_SBS_SET_TIM_BREAK_INPUTS(break_input));

  LL_SBS_EnableTIMBreakInputs(break_input);
}

/**
  * @brief  Check if the TIM break inputs is enabled.
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref HAL_SBS_SRAM1_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_SRAM2_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_SRAM3_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_SRAM4_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_ITCM_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_DTCM_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_BKPRAM_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_LOCKUP_OUT
  *         @arg @ref HAL_SBS_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SBS_PVD
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

/** @addtogroup SBS_Exported_Functions_Group4
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
    comp_rdy = LL_SBS_IsActiveFlag_RDY1() << SBS_CCCSR_COMP_EN_Pos;

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

/** @addtogroup SBS_Exported_Functions_Group5
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

/** @addtogroup SBS_Exported_Functions_Group6
  * @{
  This section provides functions to set and get the HDP level value :
  - Call HAL_SBS_SetHDPLevelValue() to set the HDP level value.
  - Call HAL_SBS_GetHDPLevelValue() to get the HDP level value.
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
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group7
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
  */

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

/**
  * @brief  Check if the device APB, AHB access ports are locked.
  * @retval hal_sbs_access_port_lock_status_t lock access port status.
  */
hal_sbs_access_port_lock_status_t HAL_SBS_IsLockedAPBAHBAccessPorts(void)
{
  return ((hal_sbs_access_port_lock_status_t)LL_SBS_IsLockedAPBAHBAccessPorts());
}

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

/**
  * @brief  Check if the debug interface is locked.
  * @retval hal_sbs_core_debug_itf_lock_status_t debug interface status.
  */
hal_sbs_core_debug_itf_lock_status_t HAL_SBS_IsLockedCoreDebugInterface(void)
{
  return ((hal_sbs_core_debug_itf_lock_status_t)LL_SBS_IsLockedDebug());
}

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

/**
  * @brief  Get the HDP level at which the authenticated debug opens.
  * @retval hal_sbs_hdp_level_value_t Hide protection level at which the authenticated debug opens.
  */
hal_sbs_hdp_level_value_t HAL_SBS_GetAuthenticatedDebugHDPLevel(void)
{
  return ((hal_sbs_hdp_level_value_t)LL_SBS_GetAuthenticatedDbgHDPLevel());
}

/**
  * @brief  Lock the access to the debug configuration.
  * @note   Lock debug configuration is released only by a reset.
  */
void HAL_SBS_LockDebugConfig(void)
{
  LL_SBS_LockDebugConfig();
}

/**
  * @brief  Check if the debug configuration is locked.
  * @retval hal_sbs_debug_config_lock_status_t Lock debug configuration register status.
  */
hal_sbs_debug_config_lock_status_t HAL_SBS_IsLockedDebugConfig(void)
{
  return ((hal_sbs_debug_config_lock_status_t)LL_SBS_IsLockedDebugConfig());
}

/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group8
  * @{
  This section provides functions to manage the memories erase status feature :
  - Call HAL_SBS_GetMemoryEraseStatus() to check the memories erase status flags.
  */

/**
  * @brief Check if an SBS memories erase status flag is active or not.
  * @param memory This parameter can be one of the following values:
  *        @arg @ref HAL_SBS_BKPRAM_ERASED
  *        @arg @ref HAL_SBS_AXISRAM1_ERASED
  * @retval hal_sbs_memory_erase_status_t Memory erase status.
  */
hal_sbs_memory_erase_status_t HAL_SBS_GetMemoryEraseStatus(uint32_t memory)
{
  ASSERT_DBG_PARAM(IS_SBS_GET_MEMORY_ERASE(memory));

  return (hal_sbs_memory_erase_status_t)LL_SBS_IsActiveFlag(memory);
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group9
  * @{
  This section provides functions to manage the RSS Command :
  - Call HAL_SBS_SetRSSCommand() to set a command to the RSS to be executed at next reset.
  - Call HAL_SBS_GetRSSCommand() to get the command sent to the RSS.
  */

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
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group10
  * @{
  This section provides functions to get the boot address:
  - Call HAL_SBS_GetBootAddress() to get the boot address.
  */

/**
  * @brief  Get the physical boot address used by the Cortex-M7 out of reset.
  * @retval uint32_t Boot address used by the Cortex-M7.
  */
uint32_t HAL_SBS_GetBootAddress(void)
{
  return LL_SBS_GetBootAddress();
}
/**
  * @}
  */

/** @addtogroup SBS_Exported_Functions_Group11
  * @{
  This section provides functions to enable/disable the IO speed optimization:
  - Call HAL_SBS_EnableIOSpeedOptimization() to enable the IO speed optimization.
  - Call HAL_SBS_DisableIOSpeedOptimization() to disable the IO speed optimization.
  - Call HAL_SBS_IsEnabledIOSpeedOptimization() to Check if the IO speed optimization is enabled.
  */

/**
  * @brief  Enable the IO speed optimization.
  */
void HAL_SBS_EnableIOSpeedOptimization(void)
{
  LL_SBS_EnableIOSpeedOptimization();
}

/**
  * @brief  Disable the IO speed optimization.
  */
void HAL_SBS_DisableIOSpeedOptimization(void)
{
  LL_SBS_DisableIOSpeedOptimization();
}

/**
  * @brief  Check if the IO speed optimization is enabled.
  * @retval State of bit (1 or 0).
  */
hal_sbs_io_speed_optimization_status_t HAL_SBS_IsEnabledIOSpeedOptimization(void)
{
  return (hal_sbs_io_speed_optimization_status_t)LL_SBS_IsEnabledIOSpeedOptimization();
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
