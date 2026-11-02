/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_flash_itf.c
  * @brief   This file provides FLASH peripheral services.
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

#if defined (FLASH)
#if defined (USE_HAL_FLASH_MODULE) && (USE_HAL_FLASH_MODULE == 1)

/** @addtogroup FLASH_ITF
  * @{
  */

/** @defgroup FLASH_ITF_Introduction FLASH_ITF Introduction
  * @{

  The FLASH ITF Hardware Abstraction Layer (HAL) provides high-level, user-friendly interface APIs for managing
  non-volatile memory (FLASH) configuration and control on STM32 microcontrollers.

  This layer offers firmware functions to support key FLASH interface functionalities, including:

   - Lock and unlock management.
   - Control operations.
   - Option byte configuration.
   - Option byte process interrupt handling.

  The abstraction provided by this layer ensures portability and simplifies application development
  across various STM32 microcontroller series.

  */
/**
  * @}
  */

/** @defgroup FLASH_ITF_How_To_Use FLASH ITF How To Use
  * @{
This file provides firmware functions to manage the following functionalities of FLASH option bytes peripheral:

- Control functions
- Lock and Unlock functions
- Configuration functions
- IRQHandler and Callback functions

# FLASH option bytes main features

- The Flash Option Bytes, often referred to as "Option Bytes" or "OB" in the context of microcontrollers, are a set of
  configuration settings that can be programmed to customize the Behavior of the flash memory and other features of a
  microcontroller. These Option Bytes are typically stored in a special area of the flash memory and are used to control
  various aspects of the device's operation.

## Lock mechanism :

  - After reset, the FLASH option bytes are write-protected.
    Use the unlock sequence to run any operation on the FLASH option bytes.

## Option bytes :

  - Lock mechanism : After reset, the FLASH option bytes are write-protected.
                     The Unlock sequence is necessary to run any operation on the FLASH option bytes.

  - Write protection area : The user area in flash memory can be protected against unwanted write operations.

  - Hide protection area: A part of the main flash memory area.

  - Boot lock: Several option bytes cannot be modified when the boot lock mechanism is enabled.

  - User option bytes : There are option bytes to include additional option to customize the behavior.
                        - Non-volatile state, BOR level, reset generation in low power mode, Independent watchdog
                          selection, Independent watchdog counter freeze, Bank swapping, Memories ECC, Boot0,
                          High speed Low VDD

# How to use the FLASH_ITF HAL module driver

## Lock and Unclock functions :

- Use the HAL_FLASH_ITF_Lock() and HAL_FLASH_ITF_Unlock() functions to lock and unlock the access to the FLASH control
  register for both banks.
- Use the HAL_FLASH_ITF_IsLocked() function to check the lock access state to the FLASH control register for both banks.
- Use the HAL_FLASH_ITF_LockBank() and HAL_FLASH_ITF_UnlockBank() functions to lock and unlock the access to the FLASH
  control register for specific bank.
- Use the HAL_FLASH_ITF_IsLockedBank() function to check the lock access state to the FLASH control register for
  specific banks.

## Configuration functions :

- Use the HAL_FLASH_ITF_SetLatency() function to set the FLASH latency.
- Use the HAL_FLASH_ITF_GetLatency() function to get the FLASH latency.
- Use the HAL_FLASH_ITF_SetProgrammingDelay() function to set the FLASH programming delay.
- Use the HAL_FLASH_ITF_GetProgrammingDelay() function to get the FLASH programming delay.
- Use the HAL_FLASH_ITF_ECC_EnableIT() function to enable the FLASH ECC interrupt.
- Use the HAL_FLASH_ITF_ECC_DisableIT() function to disable the FLASH ECC interrupt.
- Use the HAL_FLASH_ITF_ECC_IsEnabledIT() function to check if the FLASH ECC interrupt is enabled or disabled.
- Use the HAL_FLASH_ITF_OBK_EnableErrorIT() function to enable the OBK error interrupt.

## Option bytes lock and unlock functions:

- Use the HAL_FLASH_ITF_OB_Lock() function to lock the access to the FLASH option bytes registers.
- Use the HAL_FLASH_ITF_OB_Unlock() function to unlock the access to the FLASH option bytes registers.
- Use the HAL_FLASH_ITF_OB_IsLocked() function to check the lock state of the access to the FLASH option bytes
  registers.

## Write protection area configuration:

- Use the HAL_FLASH_ITF_OB_EnablePageWRP() function to enable the FLASH ITF OB pagewise write protection area
  configuration.
- Use the HAL_FLASH_ITF_OB_DisablePageWRP() function to disable the FLASH ITF OB pagewise write protection area
  configuration.
- Use the HAL_FLASH_ITF_OB_IsEnabledPageWRP() function to check if the FLASH ITF OB pagewise write protection area
  configuration is enabled or disabled.

## Hide protection configuration:

- Use the HAL_FLASH_ITF_SetHDPExtArea() function to set the HDP extended area.
- Use the HAL_FLASH_ITF_GetHDPExtArea() function to get the HDP extended area.
- Use the HAL_FLASH_ITF_SetHDPExtAccessProtection() function to set the HDP extended area access protection.
- Use the HAL_FLASH_ITF_GetHDPExtAccessProtection() function to get the HDP extended area access protection.
- Use the HAL_FLASH_ITF_OB_SetHDPArea() function to set the FLASH ITF OB hide protection area configuration.
- Use the HAL_FLASH_ITF_OB_GetHDPArea() function to get the FLASH ITF OB hide protection area configuration.

## Option bytes OTP lock and unlock functions:

- Use the HAL_FLASH_ITF_OB_LockOTPBlock() function to lock the selected OTP blocks.
- Use the HAL_FLASH_ITF_OB_IsLockedOTPBlock() function to check whether a selected OTP block is locked.

## Non-volatile state configuration:

- Use the HAL_FLASH_ITF_OB_SetNVState() function to set the FLASH ITF OB non-volatile state.
- Use the HAL_FLASH_ITF_OB_GetNVState() function to get the FLASH ITF OB non-volatile state.

## Lock and unlock boot configuration functions:

- Use the function HAL_FLASH_ITF_OB_LockBootConfig() to lock the FLASH ITF OB secure boot address configuration.

- Use the function HAL_FLASH_ITF_OB_UnlockBootConfig() to unlock the FLASH ITF OB secure boot address configuration.

- Use the function HAL_FLASH_ITF_OB_IsLockedBootConfig() to Check if the FLASH ITF OB secure boot address
  configuration is locked or unlocked.

## Debug authentication method function:

- Use the HAL_FLASH_ITF_OB_GetDebugAuthenticationMethod() function to Get the debug authentication method.

## OEM provisioning function:

- Use the HAL_FLASH_ITF_OB_GetOEMProvisioning() function to Get the OEM provisioning.

## BOR level configuration:

- Use the HAL_FLASH_ITF_OB_SetBORLevel() function to set the FLASH ITF OB BOR level.
- Use the HAL_FLASH_ITF_OB_GetBORLevel() function to get the FLASH ITF OB BOR level.

## Enter low power modes by reset generation configuration:

- Use the HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration() function to set the FLASH ITF OB enter stop mode,
  or standby mode reset generation configuration.
- Use the HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration() function to get the FLASH ITF OB enter stop mode,
  or standby mode reset generation configuration.

## IWDG Mode configuration:

- Use the HAL_FLASH_ITF_OB_SetIWDGMode() function to set the FLASH ITF OB IWDG mode configuration.
- Use the HAL_FLASH_ITF_OB_GetIWDGMode() function to get the FLASH ITF OB IWDG mode configuration.

## WDG counter freeze configuration:

- Use the HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode() function to freeze the FLASH ITF OB IWDG for stop and standby
  counter configuration.
- Use the HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode() function to unfreeze the FLASH ITF OB IWDG stop and standby
  counter configuration.
- Use the HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode() function to check the FLASH ITF OB IWDG stop and standby
  counter configuration is enabled.

## Bank swapping configuration:

- Use the HAL_FLASH_ITF_OB_SetBankSwap() function to set the FLASH ITF OB swap bank configuration.
- Use the HAL_FLASH_ITF_OB_GetBankSwap() function to get the FLASH ITF OB swap bank configuration.
- Use the HAL_FLASH_ITF_OB_IsBankSwapped() function to check the FLASH ITF OB swap bank.

## SRAM ECC configuration:

- Use the HAL_FLASH_ITF_OB_EnableSRAMECC() function to enable the FLASH ITF OB for SRAM ECC configuration.
- Use the HAL_FLASH_ITF_OB_DisableSRAMECC() function to disable the FLASH ITF OB for SRAM ECC configuration.
- Use the HAL_FLASH_ITF_OB_IsEnabledSRAMECC() function to check the FLASH ITF OB for SRAM ECC configuration is enabled.

## High speed low VDDIO configuration:

- Use the HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage() function to enable the High speed low VDDIO configuration.
- Use the HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage() function to disable the High speed low VDDIO configuration.
- Use the HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage() function to check the High speed low VDDIO configuration
  is enabled.

## Option byte key configuration:

- Use the HAL_FLASH_ITF_OB_ProgramKey() function to program the option byte key.
- Use the HAL_FLASH_ITF_OB_ReadKey() function to read the programmed option byte key.
- Use the HAL_FLASH_ITF_OB_EraseKey() function to erase the option byte key.

## Option bytes programming function:

- Use the HAL_FLASH_ITF_OB_Program() function to program the option bytes in polling mode.
- Use the HAL_FLASH_ITF_OB_Program_IT() function to program the option bytes in interrupt mode.

## IRQHandler and Callback functions:

- Use the HAL_FLASH_ITF_IRQHandler() function to handle OB write/error operations.
- Use the HAL_FLASH_ITF_OB_ProgramCpltCallback() function to be redefined within application for the OB complete write
  operations callback.
- Use the HAL_FLASH_ITF_OB_ErrorCallback() function to be redefined within application for the OB write operation error
  callback.
- Use the HAL_FLASH_ITF_OBK_ErrorCallback() function to be redefined within application for the OBK operation error
  callback.
  */
/**
  * @}
  */

/** @defgroup FLASH_ITF_Configuration_Table FLASH ITF Configuration Table
  * @{
# Configuration inside the FLASH ITF driver

Configuration defines         | Description     | Default value   | Note                                               |
------------------------------|-----------------|-----------------|----------------------------------------------------|
PRODUCT                       | from IDE        |        NA       | The selected device (ex STM32H7P75xx)              |
USE_HAL_FLASH_MODULE          | from hal_conf.h |        1        | Allows to use HAL FLASH ITF module.                |
USE_ASSERT_DBG_PARAM          | from IDE        |      None       | Allows to use the assert check parameters.         |
USE_HAL_CHECK_PARAM           | from hal_conf.h |        0        | Allows to use the run-time checks parameters.      |
USE_HAL_FLASH_ECC             | from hal_conf.h |        1        | Allows to use ECC errors features APIs.            |
  */
/**
  * @}
  */

/* Private Constants -------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Private_Constants FLASH ITF Private Constants
  * @{
  */
#define FLASH_ITF_OB_TIMEOUT       1000U                             /*!< FLASH default OB timeout */
#define FLASH_ITF_OB_LOW_PWR_MSK   (HAL_FLASH_ITF_OB_STOP_MODE \
                                    | HAL_FLASH_ITF_OB_STANDBY_MODE) /*!< FLASH low power mask     */
#define FLASH_ITF_OB_WDG_MSK       (HAL_FLASH_ITF_OB_IWDG)           /*!< FLASH wdg mask           */
#define FLASH_ITF_OB_SRAM_ECC_MSK  (HAL_FLASH_ITF_OB_SRAM)           /*!< FLASH sram ecc mask      */
#define FLASH_ITF_OB_VDDIO_MSK     (HAL_FLASH_ITF_OB_VDDIO)          /*!< FLASH vdd mask           */
#define FLASH_ITF_OB_OTP_BLOCK_NBR 16U                               /*!< FLASH OTP block number   */
#define FLASH_WRP_GROUP_WIDTH      4U                                /*!< FLASH WRP group width    */
#define FLASH_OB_KEY_NBR           32U                               /*!< FLASH OB key number      */
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Private_Macros FLASH ITF Private Macros
  * @{
  */

/*! Macro to get the FLASH physical instance from the HAL instance */
#define FLASH_GET_ITF_INSTANCE(instance) ((FLASH_TypeDef *)((uint32_t)(instance)))

/*! Macro to check FLASH instance */
#define IS_FLASH_INSTANCE(instance) ((instance) == HAL_FLASH)

/*! Macro to check FLASH memory bank */
#define IS_FLASH_BANK(value) (((value) == HAL_FLASH_BANK_1) || ((value) == HAL_FLASH_BANK_2))

/*! Macro to check FLASH ITF latency */
#define IS_FLASH_ITF_LATENCY(value) (((value) == HAL_FLASH_ITF_LATENCY_0)     \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_1)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_2)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_3)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_4)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_5)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_6)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_7)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_8)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_9)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_10) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_11) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_12) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_13) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_14) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_15))

/*! Macro to check FLASH memory programming delay */
#define IS_FLASH_ITF_PROGRAM_DELAY(value) (((value) == HAL_FLASH_ITF_PROGRAM_DELAY_0)    \
                                           || ((value) == HAL_FLASH_ITF_PROGRAM_DELAY_1) \
                                           || ((value) == HAL_FLASH_ITF_PROGRAM_DELAY_2) \
                                           || ((value) == HAL_FLASH_ITF_PROGRAM_DELAY_3))

/*! Macro to check FLASH ITF hdp extension state */
#define IS_FLASH_ITF_HDP_EXT_STATE(value) (((value) == HAL_FLASH_ITF_HDP_NO_ACCESS_PROTECTION)  \
                                           || ((value) == HAL_FLASH_ITF_HDP_ONLY_AREA_ACCESS_PROTECTION) \
                                           || ((value) == HAL_FLASH_ITF_HDP_ALL_ACCESS_PROTECTION))

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/*! Macro to check FLASH ITF ECC interrupt */
#define IS_FLASH_ITF_ECC_INTERRUPT(value) ((((value) & (HAL_FLASH_ITF_IT_ECC_SINGLE \
                                                        | HAL_FLASH_ITF_IT_ECC_DOUBLE)) != 0U) \
                                           && (((value) & (~(HAL_FLASH_ITF_IT_ECC_SINGLE \
                                                             | HAL_FLASH_ITF_IT_ECC_DOUBLE))) == 0U))

/*! Macro to check FLASH ITF GET ECC interrupt */
#define IS_FLASH_ITF_GET_ECC_INTERRUPT(value) (((value) == HAL_FLASH_ITF_IT_ECC_SINGLE) \
                                               || ((value) == HAL_FLASH_ITF_IT_ECC_DOUBLE))
#endif /* USE_HAL_FLASH_ECC */

/*! Macro to check FLASH ITF OB bank area */
#define IS_FLASH_ITF_OB_BANK_AREA(value) (((value) == HAL_FLASH_ITF_OB_BANK_AREA_A) \
                                          || ((value) == HAL_FLASH_ITF_OB_BANK_AREA_B))

/*! Macro to check FLASH ITF OB key hdp level */
#define IS_FLASH_ITF_OBK_HDPL(value) (((value) == HAL_FLASH_ITF_OBK_HDPL_0) \
                                      || ((value) == HAL_FLASH_ITF_OBK_HDPL_1))

/*! Macro to check FLASH ITF OB debug authentication method */
#define IS_FLASH_ITF_OB_DBG_AUTH(value) (((value) == HAL_FLASH_ITF_OB_DBG_AUTH_DEFAULT) \
                                         || ((value) == HAL_FLASH_ITF_OB_DBG_AUTH_PASSWORD) \
                                         || ((value) == HAL_FLASH_ITF_OB_DBG_AUTH_LOCKED))

/*! Macro to check FLASH ITF OB OEM provisioning state */
#define IS_FLASH_ITF_OB_OEM_PROV(value) (((value) == HAL_FLASH_ITF_OB_OEM_PROVD_ENABLE) \
                                         || ((value) == HAL_FLASH_ITF_OB_OEM_PROVD_DEFAULT))

/*! Macro to check FLASH ITF OB boot lock state */
#define IS_FLASH_ITF_OB_BOOT_LOCK_STATE(value) (((value) == HAL_FLASH_ITF_OB_BOOT_UNLOCKED) \
                                                || ((value) == HAL_FLASH_ITF_OB_BOOT_LOCKED))

/*! Macro to check FLASH ITF OB bor level */
#define IS_FLASH_ITF_OB_BOR_LEVEL(value) (((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_0) \
                                          || ((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_1) \
                                          || ((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_2) \
                                          || ((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_3))

/*! Macro to check FLASH ITF OB non-volatile state */
#define IS_FLASH_ITF_OB_NVSTATE(value) (((value) == HAL_FLASH_ITF_OB_NVSTATE_OPEN) \
                                        || ((value) == HAL_FLASH_ITF_OB_NVSTATE_CLOSE))

/*! Macro to check FLASH ITF OB low power mode */
#define IS_FLASH_ITF_OB_LOW_PWR_MODE(value) (((value) == HAL_FLASH_ITF_OB_STOP_MODE) \
                                             || ((value) == HAL_FLASH_ITF_OB_STANDBY_MODE))

/*! Macro to check FLASH ITF OB low power reset generation */
#define IS_FLASH_ITF_OB_RST_GENERATION_STATUS(value) (((value) == HAL_FLASH_ITF_OB_RST_GENERATION) \
                                                      || ((value) == HAL_FLASH_ITF_OB_NO_RST_GENERATION))

/*! Macro to check FLASH ITF OB wdg */
#define IS_FLASH_ITF_OB_WDG(value) (((value) == HAL_FLASH_ITF_OB_IWDG))

/*! Macro to check FLASH ITF OB wdg hardware/software mode */
#define IS_FLASH_ITF_OB_WDG_HW_SW_MODE(value) (((value) == HAL_FLASH_ITF_OB_WDG_HARDWARE) \
                                               || ((value) == HAL_FLASH_ITF_OB_WDG_SOFTWARE))

/*! Macro to check FLASH ITF OB swap bank */
#define IS_FLASH_ITF_OB_SWAP_BANK(value) (((value) == HAL_FLASH_ITF_OB_BANK_NO_SWAP) \
                                          || ((value) == HAL_FLASH_ITF_OB_BANK_SWAP))

/*! Macro to check FLASH ITF OB single dual bank */
#define IS_FLASH_ITF_OB_SINGLE_DUAL_BANK(value) (((value) == HAL_FLASH_ITF_OB_SINGLE_BANK) \
                                                 || ((value) == HAL_FLASH_ITF_OB_DUAL_BANK))

/*! Macro to check FLASH ITF OB sram ecc */
#define IS_FLASH_ITF_OB_SRAM_ECC(value) (((value) == HAL_FLASH_ITF_OB_ALL_SRAM))

/*! Macro to check FLASH ITF OB vdd */
#define IS_FLASH_ITF_OB_VDD(value) (((value) == HAL_FLASH_ITF_OB_VDDIO))
/**
  * @}
  */

/* Private Functions Prototypes --------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Private_Functions FLASH ITF Private Functions
  * @{
  */
static hal_status_t FLASH_ITF_IsReadyForOperation(hal_flash_t instance, hal_flash_bank_t bank);
static uint32_t FLASH_ITF_GetBankReg(hal_flash_t instance, hal_flash_bank_t bank);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup FLASH_ITF_Exported_Functions
  * @{
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group1
  * @{

This subsection provides a set of functions allowing to lock/unlock and configure the FLASH ITF peripheral:

- Call the function HAL_FLASH_ITF_Lock() to lock the access to the FLASH control register for both bank.

- Call the function HAL_FLASH_ITF_Unlock() to unlock the access to the FLASH control register for both bank.

- Call the function HAL_FLASH_ITF_IsLocked() to check the lock access state to the FLASH control register for both bank.

- Call the function HAL_FLASH_ITF_LockBank() to lock the access to the FLASH control register by bank.

- Call the function HAL_FLASH_ITF_UnlockBank() to unlock the access to the FLASH control register by bank.

- Call the function HAL_FLASH_ITF_IsLockedBank() to check the lock access state to the FLASH control register by bank.

- Call the function HAL_FLASH_ITF_SetLatency() to set the latency according to selected parameter within
  hal_flash_itf_latency_t enumeration.

- Call the function HAL_FLASH_ITF_GetLatency() to get the current configured latency.

- Call the function HAL_FLASH_ITF_SetProgrammingDelay() to set the programming delay according to selected parameter
  within hal_flash_itf_program_delay_t enumeration.

- Call the function HAL_FLASH_ITF_GetProgrammingDelay() to get the current configured programming delay.

- Call the function HAL_FLASH_ITF_SetHDPExtArea() to set the HDP extended area.

- Call the function HAL_FLASH_ITF_GetHDPExtArea() to get the HDP extended area.

- Call the function HAL_FLASH_ITF_SetHDPExtAccessProtection() to set the HDP extended access protection according to
  selected parameter within hal_flash_itf_hdp_access_protection_t enumeration.

- Call the function HAL_FLASH_ITF_GetHDPExtAccessProtection() to get the HDP extended access protection.

- call the function HAL_FLASH_ITF_ECC_EnableIT() to enable the FLASH ECC interrupt.

- call the function HAL_FLASH_ITF_ECC_DisableIT() to disable the FLASH ECC interrupt.

- call the function HAL_FLASH_ITF_ECC_IsEnabledIT() to check if the FLASH ECC interrupt is enabled or disabled.

- call the function HAL_FLASH_ITF_OBK_EnableErrorIT() to enable the OBK error interrupt.
  */

/**
  * @brief  Lock the FLASH ITF control register access for both bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval HAL_OK    The FLASH registers access locked.
  * @retval HAL_ERROR Failed to lock FLASH control register access.
  */
hal_status_t HAL_FLASH_ITF_Lock(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  LL_FLASH_Lock(FLASH_GET_ITF_INSTANCE(instance), LL_FLASH_BANK_1);
  LL_FLASH_Lock(FLASH_GET_ITF_INSTANCE(instance), LL_FLASH_BANK_2);

  if (LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), LL_FLASH_BANK_1) == 0U)
  {
    return HAL_ERROR;
  }

  if (LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), LL_FLASH_BANK_2) == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Unlock the FLASH ITF control register access for both bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval HAL_OK    The FLASH registers access unlocked.
  * @retval HAL_ERROR Failed to unlock FLASH control register access.
  */
hal_status_t HAL_FLASH_ITF_Unlock(hal_flash_t instance)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  bank_reg = FLASH_ITF_GetBankReg(instance, HAL_FLASH_BANK_1);
  if (LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), bank_reg) != 0U)
  {
    LL_FLASH_SetUnlockKey(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_KEY1);
    LL_FLASH_SetUnlockKey(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_KEY2);

    if (LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), bank_reg) != 0U)
    {
      return HAL_ERROR;
    }
  }

  bank_reg = FLASH_ITF_GetBankReg(instance, HAL_FLASH_BANK_2);
  if (LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), bank_reg) != 0U)
  {
    LL_FLASH_SetUnlockKey(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_KEY1);
    LL_FLASH_SetUnlockKey(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_KEY2);

    if (LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), bank_reg) != 0U)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH ITF control register access is locked or unlocked for both bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_lock_status_t FLASH control register access lock status.
  */
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLocked(hal_flash_t instance)
{
  uint32_t is_locked;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  is_locked = LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), LL_FLASH_BANK_1);
  is_locked = (is_locked == 0U) ? LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), LL_FLASH_BANK_2) : 1U;

  return ((hal_flash_itf_lock_status_t)is_locked);
}

/**
  * @brief  Lock the FLASH ITF control register access by bank.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank      This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_OK    The FLASH registers access locked.
  * @retval HAL_ERROR Failed to lock FLASH control register access.
  */
hal_status_t HAL_FLASH_ITF_LockBank(hal_flash_t instance, hal_flash_bank_t bank)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  LL_FLASH_Lock(FLASH_GET_ITF_INSTANCE(instance), bank_reg);

  if (LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), bank_reg) == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Unlock the FLASH ITF control register access by bank.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank      This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_OK    The FLASH registers access unlocked.
  * @retval HAL_ERROR Failed to unlock FLASH control register access.
  */
hal_status_t HAL_FLASH_ITF_UnlockBank(hal_flash_t instance, hal_flash_bank_t bank)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  if (LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), bank_reg) != 0U)
  {
    LL_FLASH_SetUnlockKey(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_KEY1);
    LL_FLASH_SetUnlockKey(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_KEY2);

    if (LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), bank_reg) != 0U)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH ITF control register access is locked or unlocked by bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval hal_flash_itf_lock_status_t FLASH control register access lock status.
  */
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLockedBank(hal_flash_t instance, hal_flash_bank_t bank)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  return ((hal_flash_itf_lock_status_t)LL_FLASH_IsLocked(FLASH_GET_ITF_INSTANCE(instance), bank_reg));
}

/**
  * @brief  Set the FLASH ITF latency configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  latency This parameter is one element of \ref hal_flash_itf_latency_t enumeration.
  * @retval HAL_OK  Latency is successfully configured.
  */
hal_status_t HAL_FLASH_ITF_SetLatency(hal_flash_t instance, hal_flash_itf_latency_t latency)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_LATENCY(latency));

  LL_FLASH_SetLatency(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)latency);

  if (LL_FLASH_GetLatency(FLASH_GET_ITF_INSTANCE(instance)) != ((uint32_t)latency))
  {
    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

/**
  * @brief  Get the FLASH ITF latency configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_latency_t Latency value.
  */
hal_flash_itf_latency_t HAL_FLASH_ITF_GetLatency(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_latency_t)LL_FLASH_GetLatency(FLASH_GET_ITF_INSTANCE(instance)));
}

/**
  * @brief  Set the FLASH programming delay configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  prog_delay This parameter is one element of \ref hal_flash_itf_program_delay_t enumeration.
  * @retval HAL_OK  Programming Delay is successfully configured.
  */
hal_status_t HAL_FLASH_ITF_SetProgrammingDelay(hal_flash_t instance, hal_flash_itf_program_delay_t prog_delay)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_PROGRAM_DELAY(prog_delay));

  LL_FLASH_SetProgrammingDelay(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)prog_delay);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH programming delay configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_program_delay_t programming delay value.
  */
hal_flash_itf_program_delay_t HAL_FLASH_ITF_GetProgrammingDelay(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_program_delay_t)LL_FLASH_GetProgrammingDelay(FLASH_GET_ITF_INSTANCE(instance)));
}

/**
  * @brief  Set the HDP Extended area.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank      This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  block_nbr This parameter can be any value between 0 and the maximum number of blocks per bank.
  * @retval HAL_OK HDP Extended area number of blocks set.
  */
hal_status_t HAL_FLASH_ITF_SetHDPExtArea(hal_flash_t instance, hal_flash_bank_t bank, uint32_t block_nbr)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(block_nbr < (FLASH_PAGE_NB * 32U));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  LL_FLASH_SetHDPExtArea(FLASH_GET_ITF_INSTANCE(instance), bank_reg, block_nbr);

  return HAL_OK;
}

/**
  * @brief  Get the HDP Extended area.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval uint32_t HDP Extended area number of blocks value, between 0 and the maximum number of blocks per bank.
  */
uint32_t HAL_FLASH_ITF_GetHDPExtArea(hal_flash_t instance, hal_flash_bank_t bank)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  return LL_FLASH_GetHDPExtArea(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
}

/**
  * @brief  Set the HDP Extended state.
  * @param  instance          This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  access_protection This parameter is one element of \ref hal_flash_itf_hdp_access_protection_t enumeration.
  * @retval HAL_OK HDP Extended state set.
  */
hal_status_t HAL_FLASH_ITF_SetHDPExtAccessProtection(hal_flash_t instance,
                                                     hal_flash_bank_t bank,
                                                     hal_flash_itf_hdp_access_protection_t access_protection)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_HDP_EXT_STATE(access_protection));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  LL_FLASH_SetHDPExtAccessProtection(FLASH_GET_ITF_INSTANCE(instance), bank_reg, (uint32_t)access_protection);

  return HAL_OK;
}

/**
  * @brief  Get the HDP Extended state.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval hal_flash_itf_hdp_access_protection_t HDP extension state.
  */
hal_flash_itf_hdp_access_protection_t HAL_FLASH_ITF_GetHDPExtAccessProtection(hal_flash_t instance,
                                                                              hal_flash_bank_t bank)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  return (hal_flash_itf_hdp_access_protection_t)LL_FLASH_GetHDPExtAccessProtection(FLASH_GET_ITF_INSTANCE(instance),
         bank_reg);
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/**
  * @brief  Enable the given FLASH ECC interrupt.
  * @param  instance  The FLASH instance.
  * @param  bank      This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  interrupt The ECC interrupt to enable.
  * @retval HAL_OK ECC interruption enabled.
  */
hal_status_t HAL_FLASH_ITF_ECC_EnableIT(hal_flash_t instance, hal_flash_bank_t bank, uint32_t interrupt)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_ECC_INTERRUPT(interrupt));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  if ((interrupt & HAL_FLASH_ITF_IT_ECC_SINGLE) == HAL_FLASH_ITF_IT_ECC_SINGLE)
  {
    LL_FLASH_EnableIT_SNECCERR(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
  }

  if ((interrupt & HAL_FLASH_ITF_IT_ECC_DOUBLE) == HAL_FLASH_ITF_IT_ECC_DOUBLE)
  {
    LL_FLASH_EnableIT_DBECCERR(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
  }

  return HAL_OK;
}

/**
  * @brief  Disable the given FLASH ECC interrupt.
  * @param  instance  The FLASH instance.
  * @param  bank      This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  interrupt The ECC interrupt to disable.
  * @retval HAL_OK ECC interruption disabled.
  */
hal_status_t HAL_FLASH_ITF_ECC_DisableIT(hal_flash_t instance, hal_flash_bank_t bank, uint32_t interrupt)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_ECC_INTERRUPT(interrupt));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  if ((interrupt & HAL_FLASH_ITF_IT_ECC_SINGLE) == HAL_FLASH_ITF_IT_ECC_SINGLE)
  {
    LL_FLASH_DisableIT_SNECCERR(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
  }

  if ((interrupt & HAL_FLASH_ITF_IT_ECC_DOUBLE) == HAL_FLASH_ITF_IT_ECC_DOUBLE)
  {
    LL_FLASH_DisableIT_DBECCERR(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
  }

  return HAL_OK;
}

/**
  * @brief  Check if the given FLASH ECC interrupt is enabled or disabled.
  * @param  instance  The FLASH instance.
  * @param  bank      This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  interrupt The ECC interrupt to check.
  * @retval Return value can be one element of \ref hal_flash_itf_ecc_it_status_t enumeration.
  */
hal_flash_itf_ecc_it_status_t HAL_FLASH_ITF_ECC_IsEnabledIT(hal_flash_t instance,
                                                            hal_flash_bank_t bank,
                                                            uint32_t interrupt)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_GET_ECC_INTERRUPT(interrupt));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  if (interrupt == HAL_FLASH_ITF_IT_ECC_SINGLE)
  {
    return (hal_flash_itf_ecc_it_status_t)LL_FLASH_IsEnabledIT_SNECCERR(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
  }
  else
  {
    return (hal_flash_itf_ecc_it_status_t)LL_FLASH_IsEnabledIT_DBECCERR(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
  }
}
#endif /* USE_HAL_FLASH_ECC */

/**
  * @brief  Enable the option bytes key error interrupt.
  * @param  instance  The FLASH instance.
  * @retval HAL_OK Option bytes key error interruption enabled.
  */
hal_status_t HAL_FLASH_ITF_OBK_EnableErrorIT(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  LL_FLASH_EnableIT_OBKERR(FLASH_GET_ITF_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group2
  * @{

This subsection provides a set of functions allowing to to lock/unlock and configure the FLASH ITF peripheral option
bytes :

- Call the HAL_FLASH_ITF_OB_Lock() function to lock the access to the FLASH option bytes registers.

- Call the HAL_FLASH_ITF_OB_Unlock() function to unlock the access to the FLASH option bytes registers.

- Call the HAL_FLASH_ITF_OB_IsLocked() function to check the lock state of the access to the FLASH option bytes

- Call the HAL_FLASH_ITF_OB_EnablePageWRP() function to enable the FLASH ITF OB pagewise write protection area
  configuration.

- Call the HAL_FLASH_ITF_OB_DisablePageWRP() function to disable the FLASH ITF OB pagewise write protection area
  configuration.

- Call the HAL_FLASH_ITF_OB_IsEnabledPageWRP() function to check if the FLASH ITF OB pagewise write protection area
  configuration is enabled or disabled.

- Call the HAL_FLASH_ITF_OB_SetHDPArea() function to set the FLASH ITF OB hide protection area configuration.

- Call the HAL_FLASH_ITF_OB_GetHDPArea() function to get the FLASH ITF OB hide protection area configuration.

- Call the HAL_FLASH_ITF_OB_LockOTPBlock() function to lock the selected OTP blocks.

- Call the HAL_FLASH_ITF_OB_IsLockedOTPBlock() function to check if the selected OTP block is locked.

- Call the function HAL_FLASH_ITF_OB_SetNVState() to set the FLASH ITF OB non-volatile state.

- Call the function HAL_FLASH_ITF_OB_GetNVState() to get the FLASH ITF OB non-volatile state.

- Call the function HAL_FLASH_ITF_OB_LockBootConfig() to lock the FLASH ITF OB secure boot address configuration.

- Call the function HAL_FLASH_ITF_OB_UnlockBootConfig() to unlock the FLASH ITF OB secure boot address configuration.

- Call the function HAL_FLASH_ITF_OB_IsLockedBootConfig() to Check if the FLASH ITF OB secure boot address
  configuration is locked or unlocked.

- Call the function HAL_FLASH_ITF_OB_GetDebugAuthenticationMethod() to get the FLASH ITF OB debug authentication method.

- Call the function HAL_FLASH_ITF_OB_GetOEMProvisioning() to get the FLASH ITF OB OEM provisioning.

- Call the function HAL_FLASH_ITF_OB_SetBORLevel() to set the FLASH ITF OB BOR level.

- Call the function HAL_FLASH_ITF_OB_GetBORLevel() to get the FLASH ITF OB BOR level.

- Call the HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration() function to set the FLASH ITF OB enter stop mode,
  or standby mode reset generation configuration.

- Call the HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration() function to get the FLASH ITF OB enter stop mode,
  or standby mode reset generation configuration.

- Call the HAL_FLASH_ITF_OB_SetIWDGMode() function to set the FLASH ITF OB IWDG mode configuration.

- Call the HAL_FLASH_ITF_OB_GetIWDGMode() function to get the FLASH ITF OB IWDG mode configuration.

- Call the HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode() function to freeze the FLASH ITF OB IWDG for stop and standby
  counter configuration.

- Call the HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode() function to unfreeze the FLASH ITF OB IWDG stop and standby
  counter configuration.

- Call the HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode() function to check the FLASH ITF OB IWDG stop and standby
  counter configuration is enabled.

- Call the function HAL_FLASH_ITF_OB_SetBankSwap() to set the FLASH ITF OB bank swapping configuration.

- Call the function HAL_FLASH_ITF_OB_GetBankSwap() to get the FLASH ITF OB bank swapping configuration.

- Call the function HAL_FLASH_ITF_OB_IsBankSwapped() to check the FLASH ITF OB swap bank.

- Call the function HAL_FLASH_ITF_OB_EnableSRAMECC() to enable the FLASH ITF OB SRAM ECC configuration.

- Call the function HAL_FLASH_ITF_OB_DisableSRAMECC() to disable the FLASH ITF OB SRAM ECC configuration.

- Call the function HAL_FLASH_ITF_OB_IsEnabledSRAMECC() to check the FLASH ITF OB SRAM ECC configuration
  is enabled.

- Call the function HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage() to enable the FLASH ITF OB High speed Low VDDIO
  and VDDIO2 configuration.

- Call the function HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage() to disable the FLASH ITF OB High speed Low VDDIO
  and VDDIO2 configuration.

- Call the function HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage() to check the FLASH ITF OB High speed Low VDDIO
  and VDDIO2 configuration is enabled.

- Call the HAL_FLASH_ITF_OB_ProgramKey() function to program the option byte key.

- Call the HAL_FLASH_ITF_OB_ReadKey() function to read the programmed option byte key.

- Call the HAL_FLASH_ITF_OB_EraseKey() function to erase the option byte key.
  */

/**
  * @brief   Lock the FLASH ITF OB control register access.
  * @param   instance This parameter is one element of \ref hal_flash_t enumeration.
  * @warning When locking the flash OB, the flash will not be locked.
  * @retval  HAL_OK    FLASH ITF OB is successfully locked.
  * @retval  HAL_ERROR Failed to lock FLASH OB control register access.
  */
hal_status_t HAL_FLASH_ITF_OB_Lock(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  LL_FLASH_OB_Lock(FLASH_GET_ITF_INSTANCE(instance));

  /* Verify that the Option-Bytes are locked */
  if (LL_FLASH_OB_IsLocked(FLASH_GET_ITF_INSTANCE(instance)) == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief   Unlock the FLASH ITF OB control register access.
  * @param   instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval  HAL_OK    FLASH ITF OB is successfully unlocked.
  * @retval  HAL_ERROR Failed to unlock FLASH OB control register access.
  */
hal_status_t HAL_FLASH_ITF_OB_Unlock(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  if (LL_FLASH_OB_IsLocked(FLASH_GET_ITF_INSTANCE(instance)) == 1U)
  {
    LL_FLASH_OB_SetUnlockKey(FLASH_GET_ITF_INSTANCE(instance), LL_FLASH_OB_OPTKEY1);
    LL_FLASH_OB_SetUnlockKey(FLASH_GET_ITF_INSTANCE(instance), LL_FLASH_OB_OPTKEY2);

    /* Verify that the Option-Bytes are unlocked */
    if (LL_FLASH_OB_IsLocked(FLASH_GET_ITF_INSTANCE(instance)) != 0U)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH ITF OB control register access is locked or unlocked.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_ob_lock_status_t FLASH ITF OB control register access lock status.
  */
hal_flash_itf_ob_lock_status_t HAL_FLASH_ITF_OB_IsLocked(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return (hal_flash_itf_ob_lock_status_t)LL_FLASH_OB_IsLocked(FLASH_GET_ITF_INSTANCE(instance));
}

/**
  * @brief  Enable the write protection feature on the selected pages of the given bank.
  * @param  instance   This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank       This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  start_page This parameter can be any value between 0 and the maximum number of pages per bank.
  * @param  page_nbr   This parameter can be any value between 1 and the maximum number of pages per bank.
  * @note   To configure the write protected pages, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  * @retval HAL_OK            FLASH OB write protection area is successfully configured.
  * @retval HAL_ERROR         FLASH OB write error generated.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  */
hal_status_t HAL_FLASH_ITF_OB_EnablePageWRP(hal_flash_t instance,
                                            hal_flash_bank_t bank,
                                            uint32_t start_page,
                                            uint32_t page_nbr)
{
  uint32_t page_mask = 0U;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(start_page < FLASH_PAGE_NB);
  ASSERT_DBG_PARAM((page_nbr != 0U) && (page_nbr <= FLASH_PAGE_NB));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((start_page + page_nbr) > FLASH_PAGE_NB)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_ITF_IsReadyForOperation(instance, bank) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Repeat for page number to be protected */
  for (uint32_t count = 0U; count < page_nbr; count++)
  {
    page_mask |= (1UL << ((start_page + count) / FLASH_WRP_GROUP_WIDTH));
  }

  LL_FLASH_OB_EnablePageWRP(FLASH_GET_ITF_INSTANCE(instance), bank_reg, page_mask);

  return HAL_OK;
}

/**
  * @brief  Disable the write protection feature on the selected pages of the given bank.
  * @param  instance   This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank       This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  start_page This parameter can be any value between 0 and the maximum number of pages per bank.
  * @param  page_nbr   This parameter can be any value between 1 and the maximum number of pages per bank.
  * @note   To configure the write protected pages, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  * @retval HAL_OK            FLASH OB write protection area is successfully configured.
  * @retval HAL_ERROR         FLASH OB write error generated.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  */
hal_status_t HAL_FLASH_ITF_OB_DisablePageWRP(hal_flash_t instance,
                                             hal_flash_bank_t bank,
                                             uint32_t start_page,
                                             uint32_t page_nbr)
{
  uint32_t page_mask = 0U;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(start_page < FLASH_PAGE_NB);
  ASSERT_DBG_PARAM((page_nbr != 0U) && (page_nbr <= FLASH_PAGE_NB));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((start_page + page_nbr) > FLASH_PAGE_NB)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_ITF_IsReadyForOperation(instance, bank) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Repeat for page number to be protected */
  for (uint32_t count = 0U; count < page_nbr; count++)
  {
    page_mask |= (1UL << ((start_page + count) / FLASH_WRP_GROUP_WIDTH));
  }

  LL_FLASH_OB_DisablePageWRP(FLASH_GET_ITF_INSTANCE(instance), bank_reg, page_mask);

  return HAL_OK;
}

/**
  * @brief  Get the state  of page write protection configuration for the selected pages of the given bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page     This parameter can be any value between 0 and the maximum number of pages per bank.
  * @retval 1 if all selected pages are write protected, 0 otherwise.
  */
hal_flash_itf_ob_wrp_page_status_t HAL_FLASH_ITF_OB_IsEnabledPageWRP(hal_flash_t instance,
                                                                     hal_flash_bank_t bank,
                                                                     uint32_t page)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM((IS_FLASH_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  return (hal_flash_itf_ob_wrp_page_status_t)LL_FLASH_OB_IsEnabledPageWRP(FLASH_GET_ITF_INSTANCE(instance), bank_reg, \
                                                                          (1UL << (page / FLASH_WRP_GROUP_WIDTH)));
}

/**
  * @brief  Set the HDP area start block.
  * @param  instance   This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank       This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  start_block This parameter can take any value between 0 and the maximum number of blocks.
  * @param  block_nbr   This parameter can take any value between 0 and the maximum number of blocks per bank.
  * @note   To configure the locked OTP blocks, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  * @note   The start block and the number of blocks are defined with a granularity of 256 bytes.
  * @retval HAL_OK     FLASH OB HDP area start block is successfully configured.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetHDPArea(hal_flash_t instance,
                                         hal_flash_bank_t bank,
                                         uint32_t start_block,
                                         uint32_t block_nbr)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(start_block < (FLASH_PAGE_NB * 32U));
  ASSERT_DBG_PARAM(block_nbr <= (FLASH_PAGE_NB * 32U));

  if (FLASH_ITF_IsReadyForOperation(instance, bank) != HAL_OK)
  {
    return HAL_ERROR;
  }

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  LL_FLASH_OB_ConfigHDPArea(FLASH_GET_ITF_INSTANCE(instance), bank_reg, start_block, start_block + block_nbr - 1U);

  return HAL_OK;
}

/**
  * @brief  Get the HDP area start block.
  * @param  bank          This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  instance      This parameter is one element of \ref hal_flash_t enumeration.
  * @param  p_start_block Pointer to the variable that will receive the HDP area start block.
  * @param  p_block_nbr   Pointer to the variable that will receive the number of blocks in the HDP area.
  * @note   The start block and the number of blocks are defined with a granularity of 256 bytes.
  */
void HAL_FLASH_ITF_OB_GetHDPArea(hal_flash_t instance,
                                 hal_flash_bank_t bank,
                                 uint32_t *p_start_block,
                                 uint32_t *p_block_nbr)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(p_start_block != NULL);
  ASSERT_DBG_PARAM(p_block_nbr != NULL);

  bank_reg = FLASH_ITF_GetBankReg(instance, bank);

  *p_start_block = LL_FLASH_OB_GetHDPAreaStartBlock(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
  *p_block_nbr   = (LL_FLASH_OB_GetHDPAreaEndBlock(FLASH_GET_ITF_INSTANCE(instance), bank_reg) \
                    - *p_start_block + 1U);
}

/**
  * @brief  Lock the selected blocks of the OTP flash area.
  * @param  instance  The FLASH instance.
  * @param  start_otp_block  Start OTP block.
  *                          This parameter can take any value from 0 to 23.
  * @param  otp_block_nbr    OTP block number.
  *                          This parameter can take any value from 1 to 24.
  * @note   To configure the locked OTP blocks, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  * @retval HAL_OK            FLASH OB OTP blocks are successfully locked.
  * @retval HAL_ERROR         FLASH OB write error generated.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  */
hal_status_t HAL_FLASH_ITF_OB_LockOTPBlock(hal_flash_t instance, uint32_t start_otp_block, uint32_t otp_block_nbr)
{
  uint32_t otp_blk_mask = 0U;

  ASSERT_DBG_PARAM((IS_FLASH_INSTANCE(instance)));
  ASSERT_DBG_PARAM(start_otp_block < FLASH_ITF_OB_OTP_BLOCK_NBR);
  ASSERT_DBG_PARAM((otp_block_nbr != 0U) && (otp_block_nbr <= FLASH_ITF_OB_OTP_BLOCK_NBR));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check that the OTP blocks range is valid */
  if ((start_otp_block + otp_block_nbr) > FLASH_ITF_OB_OTP_BLOCK_NBR)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Repeat for page number to be protected */
  for (uint32_t count = 0U; count < otp_block_nbr; count++)
  {
    otp_blk_mask |= (1UL << (start_otp_block + count));
  }

  LL_FLASH_OB_LockOTPBlock(FLASH_GET_ITF_INSTANCE(instance), otp_blk_mask);

  return HAL_OK;
}

/**
  * @brief  Check if the selected OTP blocks are locked.
  * @param  instance The FLASH instance.
  * @param  otp_block OTP block to check.
  *                   This parameter can take any value from 0 to 23.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_otp_blk_lock_status_t enumeration.
  */
hal_flash_itf_ob_otp_blk_lock_status_t HAL_FLASH_ITF_OB_IsLockedOTPBlock(hal_flash_t instance, uint32_t otp_block)
{
  ASSERT_DBG_PARAM((IS_FLASH_INSTANCE(instance)));

  return (hal_flash_itf_ob_otp_blk_lock_status_t)LL_FLASH_OB_IsLockedOTPBlock(FLASH_GET_ITF_INSTANCE(instance), \
                                                                              (1UL << otp_block));
}

/**
  * @brief  Set the non-volatile state configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  nv_state This parameter is one element of \ref hal_flash_itf_ob_nv_state_t enumeration.
  * @retval HAL_OK     FLASH OB non-volatile state is successfully configured.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetNVState(hal_flash_t instance, hal_flash_itf_ob_nv_state_t nv_state)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_NVSTATE(nv_state));

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetNVState(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)nv_state);

  return HAL_OK;
}

/**
  * @brief  Get the Non-Volatile state configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_nv_state_t enumeration..
  */
hal_flash_itf_ob_nv_state_t HAL_FLASH_ITF_OB_GetNVState(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_nv_state_t)LL_FLASH_OB_GetNVState(FLASH_GET_ITF_INSTANCE(instance)));
}

/**
  * @brief  Lock the boot configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval HAL_OK     FLASH OB boot configuration has been successfully locked.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_LockBootConfig(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_LockBootConfig(FLASH_GET_ITF_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Unlock the boot configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval HAL_OK     FLASH OB boot configuration has been successfully unlocked.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_UnlockBootConfig(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_UnlockBootConfig(FLASH_GET_ITF_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Get the boot configuration lock state.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_boot_lock_status_t enumeration..
  */
hal_flash_itf_ob_boot_lock_status_t HAL_FLASH_ITF_OB_IsLockedBootConfig(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_boot_lock_status_t)LL_FLASH_OB_IsLockedBootConfig(FLASH_GET_ITF_INSTANCE(instance)));
}

/**
  * @brief  Get the debug authentication method configuration state.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_dbg_auth_t enumeration.
  */
hal_flash_itf_ob_dbg_auth_t HAL_FLASH_ITF_OB_GetDebugAuthenticationMethod(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_dbg_auth_t)LL_FLASH_OB_GetDebugAuthenticationMethod(FLASH_GET_ITF_INSTANCE(instance)));
}

/**
  * @brief  Get the OEM provisioning configuration state.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_oem_provd_t enumeration..
  */
hal_flash_itf_ob_oem_provd_t HAL_FLASH_ITF_OB_GetOEMProvisioning(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_oem_provd_t)LL_FLASH_OB_GetOEMProvisioningState(FLASH_GET_ITF_INSTANCE(instance)));
}

/**
  * @brief  Set the FLASH ITF OB BOR level.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bor_level This parameter is one element of \ref hal_flash_itf_ob_bor_level_t enumeration.
  * @retval HAL_OK    FLASH ITF OB BOR level is successfully configured.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBORLevel(hal_flash_t instance, hal_flash_itf_ob_bor_level_t bor_level)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BOR_LEVEL(bor_level));

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBORLevel(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)bor_level);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB BOR level.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_ob_bor_level_t FLASH ITF OB BOR level.
  */
hal_flash_itf_ob_bor_level_t HAL_FLASH_ITF_OB_GetBORLevel(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_bor_level_t)((uint32_t)LL_FLASH_OB_GetBORLevel(FLASH_GET_ITF_INSTANCE(instance))));
}

/**
  * @brief  Set the FLASH ITF OB low power mode reset generation configuration.
  * @param  instance     This parameter is one element of \ref hal_flash_t enumeration.
  * @param  low_pwr_mode low power mode param selection.
  * @param  rst_gen      Element from the \ref hal_flash_itf_ob_rst_generation_status_t enumeration.
  * @retval HAL_OK       FLASH ITF OB low power mode reset generation is successfully configured.
  * @retval HAL_ERROR    FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration(hal_flash_t instance, uint32_t low_pwr_mode,
                                                              hal_flash_itf_ob_rst_generation_status_t rst_gen)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM((low_pwr_mode & FLASH_ITF_OB_LOW_PWR_MSK) == low_pwr_mode);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_RST_GENERATION_STATUS(rst_gen));

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_SetNRSTStopMode(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)rst_gen * LL_FLASH_OB_NO_RST_STOP_MODE);
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_SetNRSTStandbyMode(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)rst_gen * LL_FLASH_OB_NO_RST_STDBY_MODE);
  }

  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB low power reset generation configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  low_pwr_mode low power mode selection.
  * @retval hal_flash_itf_ob_rst_generation_status_t FLASH ITF OB low power mode reset generation configuration.
  */
hal_flash_itf_ob_rst_generation_status_t HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration(hal_flash_t instance,
    uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_LOW_PWR_MODE(low_pwr_mode));

  if (low_pwr_mode == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    return (hal_flash_itf_ob_rst_generation_status_t)
           ((uint32_t)(LL_FLASH_OB_GetNRSTStopMode(FLASH_GET_ITF_INSTANCE(instance)) >> FLASH_OBW1SR_NRST_STOP_Pos));
  }
  else
  {
    return (hal_flash_itf_ob_rst_generation_status_t)
           ((uint32_t)(LL_FLASH_OB_GetNRSTStandbyMode(FLASH_GET_ITF_INSTANCE(instance)) >> FLASH_OBW1SR_NRST_STBY_Pos));
  }
}

/**
  * @brief  Set the FLASH ITF OB WDG mode configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  mode      Element from the \ref hal_flash_itf_ob_wdg_mode_t enumeration.
  * @retval HAL_OK    FLASH ITF OB WDG mode is successfully configured.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetIWDGMode(hal_flash_t instance, hal_flash_itf_ob_wdg_mode_t mode)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_WDG_HW_SW_MODE(mode));

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetIWDGSelection(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)mode * LL_FLASH_OB_IWDG_SW);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB xWDG mode configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_ob_wdg_mode_t FLASH ITF OB xWDG mode configuration.
  */
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetIWDGMode(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return (hal_flash_itf_ob_wdg_mode_t)
         ((uint32_t)(LL_FLASH_OB_GetIWDGSelection(FLASH_GET_ITF_INSTANCE(instance)) >> FLASH_OBW1SR_IWDG_HW_Pos));
}

/**
  * @brief  Freeze the FLASH ITF OB IWDG low power counter configuration.
  * @param  instance     This parameter is one element of \ref hal_flash_t enumeration.
  * @param  low_pwr_mode low power mode selection.
  * @retval HAL_OK       FLASH ITF OB IWDG low power counter is frozen.
  * @retval HAL_ERROR    FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode(hal_flash_t instance, uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM((low_pwr_mode & FLASH_ITF_OB_LOW_PWR_MSK) == low_pwr_mode);

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_FreezeIWDGStopMode(FLASH_GET_ITF_INSTANCE(instance));
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_FreezeIWDGStandbyMode(FLASH_GET_ITF_INSTANCE(instance));
  }

  return HAL_OK;
}

/**
  * @brief  Unfreeze the FLASH ITF OB IWDG low power counter configuration.
  * @param  instance     This parameter is one element of \ref hal_flash_t enumeration.
  * @param  low_pwr_mode low power mode selection.
  * @retval HAL_OK       FLASH ITF OB IWDG low power mode counter is not frozen.
  * @retval HAL_ERROR    FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode(hal_flash_t instance, uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM((low_pwr_mode & FLASH_ITF_OB_LOW_PWR_MSK) == low_pwr_mode);

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_UnfreezeIWDGStopMode(FLASH_GET_ITF_INSTANCE(instance));
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_UnfreezeIWDGStandbyMode(FLASH_GET_ITF_INSTANCE(instance));
  }

  return HAL_OK;
}

/**
  * @brief  Check the FLASH ITF OB IWDG low power counter configuration is frozen.
  * @param  instance     This parameter is one element of \ref hal_flash_t enumeration.
  * @param  low_pwr_mode low power mode selection.
  * @retval hal_flash_itf_ob_wdg_freeze_status_t FLASH ITF OB IWDG low power counter configuration status.
  */
hal_flash_itf_ob_wdg_freeze_status_t HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode(hal_flash_t instance,
    uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_LOW_PWR_MODE(low_pwr_mode));

  if (low_pwr_mode == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    return (hal_flash_itf_ob_wdg_freeze_status_t)LL_FLASH_OB_IsFrozenIWDGStopMode(FLASH_GET_ITF_INSTANCE(instance));
  }
  else
  {
    return (hal_flash_itf_ob_wdg_freeze_status_t)LL_FLASH_OB_IsFrozenIWDGStandbyMode(FLASH_GET_ITF_INSTANCE(instance));
  }
}

/**
  * @brief  Set the FLASH ITF OB bank swapping configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank_swap This parameter is one element of \ref hal_flash_itf_ob_bank_swap_t enumeration.
  * @retval HAL_OK    FLASH ITF OB bank swapping is successfully configured.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBankSwap(hal_flash_t instance, hal_flash_itf_ob_bank_swap_t bank_swap)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SWAP_BANK(bank_swap));

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetSwapBank(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)bank_swap);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB bank swapping configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_ob_bank_swap_t FLASH ITF OB bank swapping configuration.
  */
hal_flash_itf_ob_bank_swap_t HAL_FLASH_ITF_OB_GetBankSwap(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_bank_swap_t)LL_FLASH_OB_GetSwapBank(FLASH_GET_ITF_INSTANCE(instance)));
}

/**
  * @brief  Check the FLASH OB bank swapping state.
  * @param  instance The FLASH instance.
  * @note   This function returns the current effective bank swapping status.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_bank_swap_status_t enumeration.
  */
hal_flash_itf_ob_bank_swap_status_t HAL_FLASH_ITF_OB_IsBankSwapped(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_bank_swap_status_t)LL_FLASH_OB_IsBankSwapped(FLASH_GET_ITF_INSTANCE(instance)));
}

/**
  * @brief  Enable the FLASH ITF OB BKPRAM ECC configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  sram      SRAM to be enabled.
  * @retval HAL_OK    FLASH ITF OB BKPRAM ECC is successfully enabled.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_EnableSRAMECC(hal_flash_t instance, uint32_t sram)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SRAM_ECC(sram));

  STM32_UNUSED(sram);

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_EnableEccOnSram(FLASH_GET_ITF_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Disable the FLASH ITF OB BKPRAM ECC configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  sram      SRAM to be disabled.
  * @retval HAL_OK    FLASH ITF OB memories ECC is successfully configured.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_DisableSRAMECC(hal_flash_t instance, uint32_t sram)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SRAM_ECC(sram));

  STM32_UNUSED(sram);

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_DisableEccOnSram(FLASH_GET_ITF_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Check the FLASH ITF OB BKPRAM ECC configuration is enabled or disabled.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  sram     SRAM to be checked.
  * @retval hal_flash_itf_ob_sram_ecc_status_t FLASH ITF OB BKPRAM ECC configuration status.
  */
hal_flash_itf_ob_sram_ecc_status_t HAL_FLASH_ITF_OB_IsEnabledSRAMECC(hal_flash_t instance, uint32_t sram)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SRAM_ECC(sram));

  STM32_UNUSED(sram);

  return (hal_flash_itf_ob_sram_ecc_status_t)LL_FLASH_OB_IsEnabledEccOnSram(FLASH_GET_ITF_INSTANCE(instance));
}

/**
  * @brief  Enable the FLASH ITF OB high speed low VDD io configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  vdd       Vdd high speed low voltage selection.
  * @retval HAL_OK    FLASH ITF OB high speed low VDD io is successfully enabled.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage(hal_flash_t instance, uint32_t vdd)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_VDD(vdd));

  STM32_UNUSED(vdd);

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_EnableHighSpeedLowVddIO(FLASH_GET_ITF_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Disable the FLASH ITF OB high speed low VDD io configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  vdd       Vdd high speed low voltage selection.
  * @retval HAL_OK    FLASH ITF OB high speed low VDD io is successfully disabled.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage(hal_flash_t instance, uint32_t vdd)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_VDD(vdd));

  STM32_UNUSED(vdd);

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_DisableHighSpeedLowVddIO(FLASH_GET_ITF_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Check the FLASH ITF OB high speed low VDD io configuration is enabled or disabled.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  vdd      Vdd high speed low voltage selection.
  * @retval hal_flash_itf_ob_vddio_hslv_status_t FLASH ITF OB high speed low VDD io configuration status.
  */
hal_flash_itf_ob_vddx_hslv_status_t HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage(hal_flash_t instance,
    uint32_t vdd)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_VDD(vdd));

  STM32_UNUSED(vdd);

  return (hal_flash_itf_ob_vddx_hslv_status_t)LL_FLASH_OB_IsEnabledHighSpeedLowVddIO(FLASH_GET_ITF_INSTANCE(instance));
}

/**
  * @brief  Program the option byte key.
  * @param  instance    This parameter is one element of \ref hal_flash_t enumeration.
  * @param  hdp_level   This parameter is one element of \ref hal_flash_itf_obk_hpdl_t enumeration.
  * @param  key_index   This parameter is the index of the key to be programmed.
  * @param  key         Pointer to the buffer containing the key data to be programmed.
  * @retval HAL_TIMEOUT Timeout occurred.
  * @retval HAL_ERROR   Returned an error occurred.
  * @retval HAL_OK      Returned when the programming option byte key complete successfully.
  */
hal_status_t HAL_FLASH_ITF_OB_ProgramKey(hal_flash_t instance,
                                         hal_flash_itf_obk_hpdl_t hdp_level,
                                         uint32_t key_index,
                                         const hal_flash_itf_ob_obk_t *key)
{
  uint32_t val0;
  uint32_t val1;
  uint32_t val2;
  uint32_t val3;
  uint32_t tick_start;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OBK_HDPL(hdp_level));
  ASSERT_DBG_PARAM(key_index < FLASH_OB_KEY_NBR);
  ASSERT_DBG_PARAM(key != NULL);

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_2) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_SetOBKData0(FLASH_GET_ITF_INSTANCE(instance), key->key_w0);
  LL_FLASH_SetOBKData1(FLASH_GET_ITF_INSTANCE(instance), key->key_w1);
  LL_FLASH_SetOBKData2(FLASH_GET_ITF_INSTANCE(instance), key->key_w2);
  LL_FLASH_SetOBKData3(FLASH_GET_ITF_INSTANCE(instance), key->key_w3);

  LL_FLASH_SetOBKIndex(FLASH_GET_ITF_INSTANCE(instance), key_index);
  LL_FLASH_SetOBKeyNextHDPLevel(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)hdp_level);

  LL_FLASH_EnableOBKeyProgramming(FLASH_GET_ITF_INSTANCE(instance));
  LL_FLASH_StartOBKeyOperation(FLASH_GET_ITF_INSTANCE(instance));

  tick_start = HAL_GetTick();

  while (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_GET_ITF_INSTANCE(instance)) != 0U)
  {
    if ((HAL_GetTick() - tick_start) > FLASH_ITF_OB_TIMEOUT)
    {
      if (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_GET_ITF_INSTANCE(instance)) != 0U)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  LL_FLASH_DisableOBKeyProgramming(FLASH_GET_ITF_INSTANCE(instance));
  LL_FLASH_StartOBKeyOperation(FLASH_GET_ITF_INSTANCE(instance));

  tick_start = HAL_GetTick();

  while (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_GET_ITF_INSTANCE(instance)) != 0U)
  {
    if ((HAL_GetTick() - tick_start) > FLASH_ITF_OB_TIMEOUT)
    {
      if (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_GET_ITF_INSTANCE(instance)) != 0U)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  val0 = LL_FLASH_GetOBKData0(FLASH_GET_ITF_INSTANCE(instance));
  val1 = LL_FLASH_GetOBKData1(FLASH_GET_ITF_INSTANCE(instance));
  val2 = LL_FLASH_GetOBKData2(FLASH_GET_ITF_INSTANCE(instance));
  val3 = LL_FLASH_GetOBKData3(FLASH_GET_ITF_INSTANCE(instance));

  if ((val0 != key->key_w0) || (val1 != key->key_w1) || (val2 != key->key_w2) || (val3 != key->key_w3))
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Erase the option byte key.
  * @param  instance    This parameter is one element of \ref hal_flash_t enumeration.
  * @param  hdp_level   This parameter is one element of \ref hal_flash_itf_obk_hpdl_t enumeration.
  * @param  key_mask    This parameter is the mask of the keys to be erased.
  * @retval HAL_TIMEOUT Timeout occurred.
  * @retval HAL_ERROR   Returned an error occurred.
  * @retval HAL_OK      Returned when the erase option byte key complete successfully.
  */
hal_status_t HAL_FLASH_ITF_OB_EraseKey(hal_flash_t instance,
                                       hal_flash_itf_obk_hpdl_t hdp_level,
                                       uint32_t key_mask)
{
  uint32_t tick_start;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OBK_HDPL(hdp_level));

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_2) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_SetOBKEraseKeyIndex(FLASH_GET_ITF_INSTANCE(instance), key_mask);
  LL_FLASH_SetOBKeyNextHDPLevel(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)hdp_level);

  LL_FLASH_EnableOBKeyErase(FLASH_GET_ITF_INSTANCE(instance));
  LL_FLASH_StartOBKeyOperation(FLASH_GET_ITF_INSTANCE(instance));

  tick_start = HAL_GetTick();

  while (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_GET_ITF_INSTANCE(instance)) != 0U)
  {
    if ((HAL_GetTick() - tick_start) > FLASH_ITF_OB_TIMEOUT)
    {
      if (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_GET_ITF_INSTANCE(instance)) != 0U)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  LL_FLASH_DisableOBKeyErase(FLASH_GET_ITF_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Get the option byte key.
  * @param  instance    This parameter is one element of \ref hal_flash_t enumeration.
  * @param  hdp_level   This parameter is one element of \ref hal_flash_itf_obk_hpdl_t enumeration.
  * @param  key_index   This parameter is the index of the key to be read.
  * @param  key         Pointer to the buffer where the read key data will be stored.
  * @retval HAL_TIMEOUT Timeout occurred.
  * @retval HAL_ERROR   Returned an error occurred.
  * @retval HAL_OK      Returned when the retrieve of the option byte key complete successfully.
  */
hal_status_t HAL_FLASH_ITF_OB_ReadKey(hal_flash_t instance,
                                      hal_flash_itf_obk_hpdl_t hdp_level,
                                      uint32_t key_index,
                                      hal_flash_itf_ob_obk_t *key)
{
  uint32_t tick_start;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OBK_HDPL(hdp_level));
  ASSERT_DBG_PARAM(key_index < FLASH_OB_KEY_NBR);
  ASSERT_DBG_PARAM(key != NULL);

  if (FLASH_ITF_IsReadyForOperation(instance, HAL_FLASH_BANK_2) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_DisableOBKeyErase(FLASH_GET_ITF_INSTANCE(instance));
  LL_FLASH_DisableOBKeyProgramming(FLASH_GET_ITF_INSTANCE(instance));

  LL_FLASH_SetOBKIndex(FLASH_GET_ITF_INSTANCE(instance), key_index);
  LL_FLASH_SetOBKeyNextHDPLevel(FLASH_GET_ITF_INSTANCE(instance), (uint32_t)hdp_level);

  LL_FLASH_StartOBKeyOperation(FLASH_GET_ITF_INSTANCE(instance));

  tick_start = HAL_GetTick();

  while (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_GET_ITF_INSTANCE(instance)) != 0U)
  {
    if ((HAL_GetTick() - tick_start) > FLASH_ITF_OB_TIMEOUT)
    {
      if (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_GET_ITF_INSTANCE(instance)) != 0U)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  key->key_w0 = LL_FLASH_GetOBKData0(FLASH_GET_ITF_INSTANCE(instance));
  key->key_w1 = LL_FLASH_GetOBKData1(FLASH_GET_ITF_INSTANCE(instance));
  key->key_w2 = LL_FLASH_GetOBKData2(FLASH_GET_ITF_INSTANCE(instance));
  key->key_w3 = LL_FLASH_GetOBKData3(FLASH_GET_ITF_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group3
  * @{
This subsection provides a set of functions allowing to handle the FLASH ITF ECC interrupt subroutines:

- Call the function HAL_FLASH_ITF_IRQHandler() to handle Flash OB write operations.

- Call the function HAL_FLASH_ITF_OB_ProgramCpltCallback() to be redefined within application for the OB complete write
  operation callback.

- Call the function HAL_FLASH_ITF_OB_ErrorCallback() to be redefined within application the OB write error operation
  callback.

- Call the function HAL_FLASH_ITF_OBK_ErrorCallback() to be redefined within application the OB key error operation
  callback.
  */

/**
  * @brief Handle the FLASH ITF interrupt request.
  * @param instance The FLASH instance.
  */
void HAL_FLASH_ITF_IRQHandler(hal_flash_t instance)
{
  uint32_t flags;
  uint32_t its;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  bank_reg = FLASH_ITF_GetBankReg(instance, HAL_FLASH_BANK_1);

  its = (((bank_reg == LL_FLASH_BANK_1) \
          ? LL_FLASH_READ_REG(FLASH_GET_ITF_INSTANCE(instance), AIER) \
          : LL_FLASH_READ_REG(FLASH_GET_ITF_INSTANCE(instance), BIER)) & LL_FLASH_IT_EOP);
  its |= (LL_FLASH_READ_REG(FLASH_GET_ITF_INSTANCE(instance), OPTCR) & LL_FLASH_IT_OPTERR);
  its |= (LL_FLASH_READ_REG(FLASH_GET_ITF_INSTANCE(instance), OPTCR) & LL_FLASH_IT_OBKERR);

  flags = LL_FLASH_ReadFlag(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_FLAG_EOPF);
  flags |= (LL_FLASH_READ_REG(FLASH_GET_ITF_INSTANCE(instance), OPTISR) & LL_FLASH_FLAG_OPTERR);
  flags |= (LL_FLASH_READ_REG(FLASH_GET_ITF_INSTANCE(instance), OPTISR) & LL_FLASH_FLAG_OBKERR);

  if ((STM32_READ_BIT(flags, its) & LL_FLASH_FLAG_OPTERR) != 0U)
  {
    LL_FLASH_ClearFlag_EOPF(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
    LL_FLASH_DisableIT_EOP(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
    LL_FLASH_ClearFlag_OPTERRF(FLASH_GET_ITF_INSTANCE(instance));
    LL_FLASH_DisableIT_OPTERR(FLASH_GET_ITF_INSTANCE(instance));
    HAL_FLASH_ITF_OB_ErrorCallback(instance);
  }
  else if ((STM32_READ_BIT(flags, its) & LL_FLASH_FLAG_EOPF) != 0U)
  {
    LL_FLASH_ClearFlag_EOPF(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
    LL_FLASH_DisableIT_EOP(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
    LL_FLASH_DisableIT_OPTERR(FLASH_GET_ITF_INSTANCE(instance));
    HAL_FLASH_ITF_OB_ProgramCpltCallback(instance);
  }
  else
  {
  }

  if ((STM32_READ_BIT(flags, its) & LL_FLASH_FLAG_OBKERR) != 0U)
  {
    LL_FLASH_ClearFlag_OBKERRF(FLASH_GET_ITF_INSTANCE(instance));
    LL_FLASH_DisableIT_OBKERR(FLASH_GET_ITF_INSTANCE(instance));
    LL_FLASH_DisableOBKeyErase(FLASH_GET_ITF_INSTANCE(instance));
    LL_FLASH_DisableOBKeyProgramming(FLASH_GET_ITF_INSTANCE(instance));
    HAL_FLASH_ITF_OBK_ErrorCallback(instance);
  }
}

/**
  * @brief FLASH ITF option bytes write complete callback.
  * @param instance The FLASH instance.
  */
__WEAK void HAL_FLASH_ITF_OB_ProgramCpltCallback(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(instance);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed, the
                      HAL_FLASH_ITF_OB_ProgramCpltCallback() could be implemented in the user file */
}

/**
  * @brief FLASH ITF option bytes write error callback.
  * @param instance The FLASH instance.
  */
__WEAK void HAL_FLASH_ITF_OB_ErrorCallback(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(instance);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed, the
                      HAL_FLASH_ITF_OB_ErrorCallback() could be implemented in the user file */
}

/**
  * @brief FLASH ITF option bytes key error callback.
  * @param instance The FLASH instance.
  */
__WEAK void HAL_FLASH_ITF_OBK_ErrorCallback(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(instance);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed, the
                      HAL_FLASH_ITF_OBK_ErrorCallback() could be implemented in the user file */
}

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to program the option-bytes functions configuration:

- Call the function HAL_FLASH_ITF_OB_Program() to program the FLASH option bytes in polling mode.
- Call the function HAL_FLASH_ITF_OB_Program_IT() to program the FLASH option bytes in interrupt mode.
  */

/**
  * @brief  Program the FLASH ITF option-bytes.
  * @param  instance    This parameter is one element of \ref hal_flash_t enumeration.
  * @retval HAL_ERROR   Generated when an error occurred.
  * @retval HAL_TIMEOUT Timeout occurred.
  * @retval HAL_OK      No error occurred.
  */
hal_status_t HAL_FLASH_ITF_OB_Program(hal_flash_t instance)
{
  uint32_t tick_start;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  bank_reg = FLASH_ITF_GetBankReg(instance, HAL_FLASH_BANK_1);

  LL_FLASH_OB_StartModification(FLASH_GET_ITF_INSTANCE(instance));

  tick_start = HAL_GetTick();

  /* Wait for BSY flag to be cleared */
  while (LL_FLASH_IsActiveFlag_QW(FLASH_GET_ITF_INSTANCE(instance), bank_reg) != 0U)
  {
    if ((HAL_GetTick() - tick_start) > FLASH_ITF_OB_TIMEOUT)
    {
      if (LL_FLASH_IsActiveFlag_QW(FLASH_GET_ITF_INSTANCE(instance), bank_reg) != 0U)
      {
        /* Timeout occurred while waiting for end of operation */
        return HAL_TIMEOUT;
      }
    }
  }

  if (LL_FLASH_ReadFlag(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_FLAG_ERRORS_ALL) != 0U)
  {
    LL_FLASH_ClearFlag(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_FLAG_ERRORS_ALL);

    return HAL_ERROR;
  }

  LL_FLASH_ClearFlag_EOPF(FLASH_GET_ITF_INSTANCE(instance), bank_reg);

  return HAL_OK;
}

/**
  * @brief  Program the FLASH Option Bytes interface settings in interrupt mode.
  * @param  instance  Specifies the FLASH instance based on \ref hal_flash_t enumeration.
  * @retval HAL_OK    FLASH Option Bytes settings successfully programmed.
  */
hal_status_t HAL_FLASH_ITF_OB_Program_IT(hal_flash_t instance)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  bank_reg = FLASH_ITF_GetBankReg(instance, HAL_FLASH_BANK_1);

  LL_FLASH_ClearFlag_EOPF(FLASH_GET_ITF_INSTANCE(instance), bank_reg);
  LL_FLASH_EnableIT_EOP(FLASH_GET_ITF_INSTANCE(instance), bank_reg);

  LL_FLASH_ClearFlag_OPTERRF(FLASH_GET_ITF_INSTANCE(instance));
  LL_FLASH_EnableIT_OPTERR(FLASH_GET_ITF_INSTANCE(instance));

  LL_FLASH_OB_StartModification(FLASH_GET_ITF_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Private_Functions
  * @{
  */
/**
  * @brief  Check if the FLASH operation for a new operation.
  * @param  instance  Specifies the FLASH instance based on \ref hal_flash_t enumeration.
  * @param  bank      This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_ERROR FLASH not ready to launch new operation.
  */
static hal_status_t FLASH_ITF_IsReadyForOperation(hal_flash_t instance, hal_flash_bank_t bank)
{
  uint32_t bank_reg     = FLASH_ITF_GetBankReg(instance, bank);
  uint32_t errors_flags = LL_FLASH_ReadFlag(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_FLAG_ERRORS_ALL);
  uint32_t status_flags = LL_FLASH_IsActiveFlag(FLASH_GET_ITF_INSTANCE(instance), bank_reg, LL_FLASH_FLAG_STATUS_ALL);

  if ((status_flags != 0U) || ((errors_flags & LL_FLASH_FLAG_ERRORS_ALL) != 0U))
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Get the bank register of the given bank.
  * @param  instance Specifies the FLASH instance based on \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval uint32_t return the bank register to be modified.
  */
static uint32_t FLASH_ITF_GetBankReg(hal_flash_t instance, hal_flash_bank_t bank)
{
  if (LL_FLASH_OB_IsBankSwapped(FLASH_GET_ITF_INSTANCE(instance)) == 0U)
  {
    return (uint32_t)bank;
  }
  else
  {
    return ((uint32_t)bank ^ 1U);
  }
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_FLASH_MODULE */
#endif /* FLASH */

/**
  * @}
  */
