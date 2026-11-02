/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_sdram.c
  * @brief   SDRAM HAL module driver.
  *          This file provides a generic firmware to drive SDRAM memories mounted as external device.
  *
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
#if defined (FMC_SDRAM_BK5)
#if defined(USE_HAL_SDRAM_MODULE) && (USE_HAL_SDRAM_MODULE == 1U)

/** @addtogroup SDRAM
  * @{
  */
/** @defgroup SDRAM_Introduction SDRAM Introduction
  * @{

  - The SDRAM hardware abstraction layer provides a set of APIs to interface with SDRAM devices via the STM32
    Flexible Memory Controller (FMC) peripheral.

  - The SDRAM HAL driver simplifies the initialization, configuration and the sending of the required commands,
    ensuring that the memory is correctly prepared, fully accessible and ready for use.

  - This abstraction layer ensures portability and ease of use across different STM32 series.

  */
/**
  * @}
  */

/** @defgroup SDRAM_How_To_Use SDRAM How To Use
  * @{
# How to use the SDRAM HAL module driver

## The FMC SDRAM main features:

This SDRAM HAL driver is a generic driver which contains a set of APIs used to configure the FMC SDRAM devices
to interface with external memories.

The FMC SDRAM peripheral supports the write protection feature.

## The SDRAM HAL driver can be used as follows:

This module provides these different sets of APIs that allows to:

1. Initialize, deinitialize the logical FMC SDRAM object ( @ref hal_sdram_handle_t) and retrieve the associated
   SDRAM peripheral instance:
  - Initialize the logical FMC SDRAM object and associate it to a physical instance.
    This functionality is ensured by HAL_SDRAM_Init() function.
  - Deinitialize the logical FMC SDRAM object and disable the SDRAM devices.
    This functionality is ensured by HAL_SDRAM_DeInit() function.
  - Retrieve the SDRAM instance by calling HAL_SDRAM_GetInstance().

Note: The FMC clock can be enabled in the HAL_SDRAM_Init() function if USE_FMC_CLK_ENABLE_MODEL
set to HAL_CLK_ENABLE_NO.

   At this stage, the mapping of FMC SDRAM regions can be modified, if required, allowing to access the SDRAM
   devices at two different address mappings by calling HAL_SDRAM_SetRegionRemap().
   The current memory region remap can be retrieved by calling HAL_SDRAM_GetRegionRemap().

2. Configure the low level hardware (Clock, NVIC,...):
  - Enable the SDRAMx clock if USE_FMC_CLK_ENABLE_MODEL is not defined or defined to "HAL_CLK_ENABLE_NO".
  - NVIC configuration if you need to use interrupt process.
    - Configure the SDRAMx interrupt priority.
    - Enable the NVIC SDRAMx IRQ handle.

3. Configure the FMC SDRAM common configuration (timing configuration) by calling HAL_SDRAM_SetConfig().
   This common configuration can be retrieved by calling HAL_SDRAM_GetConfig().

   At this stage, the HAL performs the common configuration for both devices, but the SDRAM remains not ready to use.

4. Configure the FMC SDRAM memory configuration (device configuration) per device
   by calling HAL_SDRAM_SetConfigMemory().
   This memory configuration can be retrieved by calling HAL_SDRAM_GetConfigMemory().

   At this stage, the common and device configuration are performed, but the SDRAM is not ready to use.

5. Send a sequence of commands called the initialization sequence to the external memory, as specified
   in the memory datasheet by calling the HAL_SDRAM_SendCommand().

6. Set the refresh rate period by calling the HAL_SDRAM_SetRefreshRate().

7. Complete the initialization sequence by calling the HAL_SDRAM_CompleteInitSequence() to inform FMC hardware
   controller that the SDRAM memory is ready to be used.

   At this stage, the memory is fully configured, the initialization sequence is performed,
   and the refresh rate is set, the SDRAM is ready to use.

   To identify the base address of the FMC SDRAM memory region before performing any read or write operations,
   the region start address can be retrieved by calling HAL_SDRAM_GetDeviceBaseAddress().

8. Manage the FMC SDRAM peripheral access when it's fully configured:

  - Enable the FMC SDRAM write protection (when disabled) to prevent any write access to the external device
    by calling HAL_SDRAM_EnableWriteProtection().

  - Disable the FMC SDRAM write protection (when enabled) to allow any write access to the external device
    by calling HAL_SDRAM_DisableWriteProtection().

  - Check the FMC SDRAM device write protection status by calling HAL_SDRAM_IsEnabledWriteProtection().

9. Interface with the FMC SDRAM when it's fully configured:

  - Send the specified command to the SDRAM device by calling HAL_SDRAM_SendCommand().
  - Set the SDRAM memory refresh rate by calling HAL_SDRAM_SetRefreshRate().
  - Get the SDRAM memory refresh rate value by calling HAL_SDRAM_GetRefreshRate().
  - Return the indicated FMC SDRAM device mode by calling HAL_SDRAM_GetDeviceMode().
  - Enable the SDRAM clock by calling HAL_SDRAM_EnableSDCLK() in the self refresh mode.
  - Disable the SDRAM kernel clock by calling HAL_SDRAM_DisableSDCLK() in the self refresh mode.
  - Check whether the SDRAM kernel clock is enabled or not by calling HAL_SDRAM_IsEnabledSDCLK().

10. Store and retrieve user data:

  - Store user data pointer into the handle by calling HAL_SDRAM_SetUserData().
  - Retrieve user data pointer from the handle by calling HAL_SDRAM_GetUserData().

11. Retrieve the global state, device state and the kernel clock frequency:

  - Retrieve the global state by calling HAL_SDRAM_GetState().
  - Retrieve the device state by calling HAL_SDRAM_GetDeviceState().
  - Retrieve the clock frequency by calling HAL_SDRAM_GetClockFreq().

12. The read and write process must be managed within the application side (outside the HAL SDRAM module) after fully
    configuring the FMC SDRAM.

## Callback registration in interrupt mode:

  By default, after the HAL_SDRAM_Init(), all callbacks are set to the corresponding legacy weak functions:
  HAL_SDRAM_RefreshErrorCallback().

  The compilation define USE_HAL_SDRAM_REGISTER_CALLBACKS when set to 1 allows the user to configure
  dynamically the driver callback: HAL_SDRAM_RegisterRefreshErrorCallback()

  When the compilation define USE_HAL_SDRAM_REGISTER_CALLBACKS is set to 0 or not defined,
  the callback registration feature is not available and weak callbacks are used.

Callback name               | Default value                      | Callback registration function
----------------------------| -----------------------------------| --------------------------------------------
RefreshErrorCallback        | HAL_SDRAM_RefreshErrorCallback()   | HAL_SDRAM_RegisterRefreshErrorCallback()
  */
/**
  * @}
  */

/** @defgroup SDRAM_Configuration_Table SDRAM Configuration Table
  * @{
## Configuration inside the HAL SDRAM driver

Prepocessor flags                | Default value     | Comment
---------------------------------| ----------------- | ------------------------------------------------
USE_HAL_SDRAM_MODULE             | 1                 | Enable HAL SDRAM driver module
USE_HAL_SDRAM_REGISTER_CALLBACKS | 0                 | Allow the user to define their own callback
USE_HAL_CHECK_PARAM              | 0                 | Enable runtime parameter check
USE_FMC_CLK_ENABLE_MODEL         | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_CHECK_PROCESS_STATE      | 0                 | Enable atomicity of process state check
USE_HAL_SDRAM_USER_DATA          | 0                 | Add a user data inside HAL SDRAM handle

Software configuration defined in preprocessor environment:
Prepocessor flags    | Default value | Comment
-------------------- | --------------| ------------------------------------------------
USE_ASSERT_DBG_PARAM | Not defined   | Enable check param for HAL
USE_ASSERT_DBG_STATE | Not defined   | Enable check state for HAL
  */
/**
  * @}
  */

/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup SDRAM_Private_Macros SDRAM Private Macros
  * @{
  */
/*! Check the memory width parameter */
#define IS_SDRAM_MEMORY_BUS_WIDTH(width) (((width) == HAL_SDRAM_MEMORY_BUS_WIDTH_8_BIT)     \
                                          || ((width) == HAL_SDRAM_MEMORY_BUS_WIDTH_16_BIT) \
                                          || ((width) == HAL_SDRAM_MEMORY_BUS_WIDTH_32_BIT))

/*! Check the read pipe delay parameter */
#define IS_SDRAM_READ_PIPE_DELAY(delay) (((delay) == HAL_SDRAM_READ_PIPE_DELAY_0_CYCLE)    \
                                         || ((delay) == HAL_SDRAM_READ_PIPE_DELAY_1_CYCLE) \
                                         || ((delay) == HAL_SDRAM_READ_PIPE_DELAY_2_CYCLE))

/*! Check the read burst parameter */
#define IS_SDRAM_READ_BURST(burst) (((burst) == HAL_SDRAM_READ_BURST_DISABLE) \
                                    || ((burst) == HAL_SDRAM_READ_BURST_ENABLE))

/*! Check the SDRAM kernel clock divider parameter */
#define IS_FMC_SDRAM_KERNEL_CLK_DIV(divider) (((divider) == HAL_SDRAM_FMC_KER_CK_DIV_2) \
                                              || ((divider) == HAL_SDRAM_FMC_KER_CK_DIV_3))

/*! Check the CAS latency parameter */
#define IS_SDRAM_CAS_LATENCY(latency)  (((latency) == HAL_SDRAM_CAS_LATENCY_1_CYCLE)    \
                                        || ((latency) == HAL_SDRAM_CAS_LATENCY_2_CYCLE) \
                                        || ((latency) == HAL_SDRAM_CAS_LATENCY_3_CYCLE))

/*! Check the column address width parameter */
#define IS_SDRAM_COLUMN_ADDR_WIDTH(column) (((column) == HAL_SDRAM_COLUMN_ADDR_WIDTH_8_BIT)     \
                                            || ((column) == HAL_SDRAM_COLUMN_ADDR_WIDTH_9_BIT)  \
                                            || ((column) == HAL_SDRAM_COLUMN_ADDR_WIDTH_10_BIT) \
                                            || ((column) == HAL_SDRAM_COLUMN_ADDR_WIDTH_11_BIT))

/*! Check the row address width parameter */
#define IS_SDRAM_ROW_ADDR_WIDTH(row) (((row) == HAL_SDRAM_ROW_ADDR_WIDTH_11_BIT)    \
                                      || ((row) == HAL_SDRAM_ROW_ADDR_WIDTH_12_BIT) \
                                      || ((row) == HAL_SDRAM_ROW_ADDR_WIDTH_13_BIT))

/*! Check the internal banks parameter */
#define IS_SDRAM_INTERN_BANKS_NUMBER(number) (((number) == HAL_SDRAM_INTERN_BANKS_NUMBER_2) \
                                              || ((number) == HAL_SDRAM_INTERN_BANKS_NUMBER_4))

/*! Check the command mode parameter */
#define IS_SDRAM_COMMAND(command) (((command) == HAL_SDRAM_COMMAND_NORMAL)         \
                                   || ((command) == HAL_SDRAM_COMMAND_CLK_ENABLE)  \
                                   || ((command) == HAL_SDRAM_COMMAND_PALL)        \
                                   || ((command) == HAL_SDRAM_COMMAND_AUTOREFRESH) \
                                   || ((command) == HAL_SDRAM_COMMAND_LOAD)        \
                                   || ((command) == HAL_SDRAM_COMMAND_SELFREFRESH) \
                                   || ((command) == HAL_SDRAM_COMMAND_POWERDOWN))

/*! Check the SDRAM devices parameter */
#define IS_SDRAM_ALL_DEVICES(device) (((device) == HAL_SDRAM_DEVICE1)   \
                                      || ((device) == HAL_SDRAM_DEVICE2))

/*! Get the handle instance */
#define SDRAM_GET_INSTANCE(handle) ((FMC_SDRAM_TypeDef *)((uint32_t)(handle)->instance))

/*! Check the SDRAM refresh rate value */
#define IS_SDRAM_REFRESH_RATE_VALUE(refresh_rate) (((refresh_rate) > 0U) \
                                                   && ((refresh_rate) <= FMC_SDRAM_MAX_REFRESH_RATE_VALUE))

/*! Check the SDRAM command parameter value */
#define IS_SDRAM_COMMAND_PARAMETER(command, parameter) ((((command) == HAL_SDRAM_COMMAND_LOAD)              \
                                                         && ((parameter) <= FMC_SDRAM_MAX_LOAD_MODE_VALUE)) \
                                                        || (((command) == HAL_SDRAM_COMMAND_AUTOREFRESH)    \
                                                            && ((parameter) >= 1U)                          \
                                                            && ((parameter) <= 16U))                        \
                                                        || (((command) != HAL_SDRAM_COMMAND_LOAD)           \
                                                            && ((command) != HAL_SDRAM_COMMAND_AUTOREFRESH)))

/*! Check the SDRAM region remap parameter value */
#define IS_SDRAM_REGION_REMAP(remap) (((remap) == HAL_SDRAM_DEVICE1_REGION5_NOR_SRAM_REGION1) \
                                      || ((remap) == HAL_SDRAM_DEVICE1_REGION1_NOR_SRAM_REGION5))

/* Timing constants for SDRAM polling operation */
#define POLLING_CYCLE_DIVIDER   (138U)  /*!< Divider to scale SYSCLK for SDRAM polling timing */
#define MILLISECONDS_PER_SECOND (1000U) /*!< Number of milliseconds in one second             */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup SDRAM_Exported_Functions
  * @{
  */

/** @addtogroup SDRAM_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and de-initialize the SDRAM driver:
- The HAL_SDRAM_Init() API: allows to initialize the SDRAM handle and enable the peripheral clock when
  USE_FMC_CLK_ENABLE_MODEL is different from HAL_CLK_ENABLE_NO.
  In case of the USE_FMC_CLK_ENABLE_MODEL compilation is not defined or define to HAL_CLK_ENABLE_NO,
  the application needs to explicitly call the HAL RCC API HAL_RCC_FMC_EnableClock() in order to enable
  the clock of FMC controller.

- The HAL_SDRAM_DeInit() API: allows to de-init the HAL SDRAM driver for the given handle and disable the write
  protection and the corresponding SDRAM device.

- The HAL_SDRAM_GetInstance(): allows to retrieve the SDRAM instance.

- The HAL_SDRAM_SetRegionRemap(): allows to set the FMC SDRAM region remap.

- The HAL_SDRAM_GetRegionRemap(): allows to retrieve the FMC SDRAM region remap.
  */

/**
  * @brief  Initialize the SDRAM handle field and associate a physical instance.
  * @param  hsdram            Pointer to a @ref hal_sdram_handle_t structure.
  * @param  instance          @ref hal_sdram_t enumerated type variable to be set according to the physical instance.
  * @note   The FMC clock can be activated within the HAL_SDRAM_Init() function by setting the USE_FMC_CLK_ENABLE_MODEL
  *         flag to HAL_CLK_ENABLE_PERIPH_ONLY in the configuration file stm32h7pxx_hal_conf.h or by explicitly calling
  *         the HAL_RCC_FMC_EnableClock() API within the application when the USE_FMC_CLK_ENABLE_MODEL is not
  *         defined or defined to flag HAL_CLK_ENABLE_NO
  * @retval HAL_INVALID_PARAM Invalid parameter return when the SDRAM handle is NULL.
  * @retval HAL_OK            The HAL SDRAM driver is initialized according to the given handle and instance.
  */
hal_status_t HAL_SDRAM_Init(hal_sdram_handle_t *hsdram, hal_sdram_t instance)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_FMC_SDRAM_ALL_INSTANCE((FMC_SDRAM_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hsdram == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsdram->instance = instance;

#if defined (USE_FMC_CLK_ENABLE_MODEL) && (USE_FMC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_FMC_EnableClock();
#endif /* USE_FMC_CLK_ENABLE_MODEL */

#if defined(USE_HAL_SDRAM_USER_DATA) && (USE_HAL_SDRAM_USER_DATA == 1U)
  hsdram->p_user_data = NULL;
#endif /* USE_HAL_SDRAM_USER_DATA */

#if defined (USE_HAL_SDRAM_REGISTER_CALLBACKS) && (USE_HAL_SDRAM_REGISTER_CALLBACKS == 1U)
  hsdram->p_refresh_error_cb = HAL_SDRAM_RefreshErrorCallback;
#endif /* USE_HAL_SDRAM_REGISTER_CALLBACKS */

  hsdram->wr_protection_status[HAL_SDRAM_DEVICE1] = HAL_SDRAM_WR_NOT_PROTECTED;
  hsdram->wr_protection_status[HAL_SDRAM_DEVICE2] = HAL_SDRAM_WR_NOT_PROTECTED;

  hsdram->device_state[HAL_SDRAM_DEVICE1] = HAL_SDRAM_DEVICE_STATE_RESET;
  hsdram->device_state[HAL_SDRAM_DEVICE2] = HAL_SDRAM_DEVICE_STATE_RESET;

  hsdram->global_state = HAL_SDRAM_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief De-init the HAL SDRAM driver for the given handle and disable the write protection and the
  *        corresponding SDRAM device.
  * @param hsdram Pointer to a @ref hal_sdram_handle_t structure.
  */
void HAL_SDRAM_DeInit(hal_sdram_handle_t *hsdram)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_FMC_SDRAM_ALL_INSTANCE(SDRAM_GET_INSTANCE(hsdram)));

  FMC_SDRAM_DisableWriteProtection(SDRAM_GET_INSTANCE(hsdram), (uint32_t)HAL_SDRAM_DEVICE1);
  FMC_SDRAM_DisableWriteProtection(SDRAM_GET_INSTANCE(hsdram), (uint32_t)HAL_SDRAM_DEVICE2);

  hsdram->global_state = HAL_SDRAM_STATE_RESET;
}

/**
  * @brief  Get the SDRAM instance.
  * @param  hsdram    Pointer to a @ref hal_sdram_handle_t structure.
  * @retval HAL_SDRAM The HAL SDRAM instance.
  */
hal_sdram_t HAL_SDRAM_GetInstance(const hal_sdram_handle_t *hsdram)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_FMC_SDRAM_ALL_INSTANCE(SDRAM_GET_INSTANCE(hsdram)));

  return hsdram->instance;
}

/**
  * @brief  Set the SDRAM region remap.
  * @param  hsdram Pointer to a @ref hal_sdram_handle_t structure.
  * @param  remap  Element of the @ref hal_sdram_region_remap_t enumeration.
  * @retval HAL_OK The Remap is set successfully.
  */
hal_status_t HAL_SDRAM_SetRegionRemap(const hal_sdram_handle_t *hsdram, hal_sdram_region_remap_t remap)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_SDRAM_REGION_REMAP(remap));

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_INIT);

  STM32_UNUSED(hsdram);

  FMC_Disable();
  FMC_SetRegionRemap((uint32_t)remap);

  return HAL_OK;
}

/**
  * @brief  Get the SDRAM region remap.
  * @param  hsdram                          Pointer to a @ref hal_sdram_handle_t structure.
  * @retval HAL_SDRAM_DEVICE1_REGION5_NOR_SRAM_REGION1 The SDRAM device 1 is remapped to the region 5 and the
  *                                                    NOR/PSRAM/SRAM is remapped to region 1.
  * @retval HAL_SDRAM_DEVICE1_REGION1_NOR_SRAM_REGION5 The SDRAM device 1 is remapped to the region 1 and the
  *                                                    NOR/PSRAM/SRAM is remapped to region 5.
  */
hal_sdram_region_remap_t HAL_SDRAM_GetRegionRemap(const hal_sdram_handle_t *hsdram)
{
  ASSERT_DBG_PARAM(hsdram != NULL);

  ASSERT_DBG_STATE(hsdram->global_state, (uint32_t)HAL_SDRAM_STATE_INIT | (uint32_t)HAL_SDRAM_STATE_CONFIGURED);

  STM32_UNUSED(hsdram);

  return ((hal_sdram_region_remap_t)FMC_GetRegionRemap());
}
/**
  * @}
  */

/** @addtogroup SDRAM_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to configure the FMC SDRAM devices and to
retrieve the current configuration.

The full configuration is done through five steps and following the order below:
- Step 1 (Common configuration for all devices):
  - HAL_SDRAM_SetConfig(): used to apply the user common configuration specified within
    @ref hal_sdram_common_config_t structure.

- Step 2 (Memory configuration per device):
  - HAL_SDRAM_SetConfigMemory(): used to apply the selected device memory configuration
    within @ref hal_sdram_memory_config_t structure and to enable it.

- Step 3 (Initialization sequence):
  - The init sequence of SDRAM can be different depends on SDRAM device, as an example,
    the initialization sequence can be to send in this order a command PALL,
    then AUTO REFRESH, then LOAD.

- Step 4: Set the refresh rate of the external memory.

- Step 5: (Initialization sequence completion)
  - HAL_SDRAM_CompleteInitSequence(): used to finalize the SDRAM configuration sequence,
    making the memory ready for use and accessible.

The configuration parameters are retrieved through these APIs:

- Common configuration for all devices:
  - HAL_SDRAM_GetConfig(): used to retrieve the user memory configuration and to fill it into
                           @ref hal_sdram_common_config_t structure.

- Memory configuration per device:
  - HAL_SDRAM_GetConfigMemory(): used to retrieve the user memory configuration per device and to fill it into
                                @ref hal_sdram_memory_config_t structure.

- The FMC SDRAM device base address is retrieved through this API:
  - HAL_SDRAM_GetDeviceBaseAddress(): used to retrieve the FMC SDRAM device base address.
  */

/**
  * @brief   Set the common configuration for all devices.
  * @param   hsdram            Pointer to a @ref hal_sdram_handle_t structure.
  * @param   p_config          Pointer to a @ref hal_sdram_common_config_t structure.
  * @warning This API is the first API to call once the HAL SDRAM driver is initialized.
  * @retval  HAL_INVALID_PARAM The memory configuration structure pointer is NULL or the clock frequency is equal to 0.
  * @retval  HAL_OK            The common configuration is successfully configured.
  */
hal_status_t HAL_SDRAM_SetConfig(hal_sdram_handle_t *hsdram, const hal_sdram_common_config_t *p_config)
{
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();
  uint32_t control_mask;
  uint32_t timing_mask;

  ASSERT_DBG_PARAM(hsdram   != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_config == NULL) || (clk_freq_hz == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_FMC_SDRAM_KERNEL_CLK_DIV(p_config->sdram_clock_divider));
  ASSERT_DBG_PARAM(IS_SDRAM_READ_PIPE_DELAY(p_config->read_pipe_delay));
  ASSERT_DBG_PARAM(IS_SDRAM_READ_BURST(p_config->read_burst_state));

  if (FMC_SDRAM_GetClockDivider(SDRAM_GET_INSTANCE(hsdram)) != 0U)
  {
    FMC_Disable();
    FMC_SDRAM_DisableSDCLK(SDRAM_GET_INSTANCE(hsdram));
  }

  uint32_t sdclk_freq_hz = FMC_SDRAM_CalculateClockFrequency(clk_freq_hz, (uint32_t)p_config->sdram_clock_divider);
  uint32_t row_cycle_delay_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->row_cycle_delay_nsec,
                                                                    sdclk_freq_hz);
  uint32_t precharge_command_delay_tmp = FMC_ConvertNanosecondsToClockCycle(
                                           p_config->precharge_command_delay_nsec, sdclk_freq_hz);

  ASSERT_DBG_PARAM(IS_FMC_ROW_CYCLE_DELAY(row_cycle_delay_tmp));
  ASSERT_DBG_PARAM(IS_FMC_ROW_PRECHARGE_DELAY(precharge_command_delay_tmp));

  ASSERT_DBG_STATE(hsdram->global_state, (uint32_t)HAL_SDRAM_STATE_INIT | (uint32_t)HAL_SDRAM_STATE_CONFIGURED);

  control_mask = (uint32_t)p_config->read_burst_state | (uint32_t)p_config->read_pipe_delay |
                 FMC_WRITE_FIELD((uint32_t)p_config->sdram_clock_divider, FMC_SDCR_SDCLK_Msk,
                                 FMC_SDCR_SDCLK_Pos);

  timing_mask = FMC_WRITE_FIELD((row_cycle_delay_tmp - 1U),
                                FMC_SDTR_TRC_Msk, FMC_SDTR_TRC_Pos)   |
                FMC_WRITE_FIELD((precharge_command_delay_tmp - 1U),
                                FMC_SDTR_TRP_Msk, FMC_SDTR_TRP_Pos);

  FMC_Disable();

  FMC_SDRAM_SetConfig(SDRAM_GET_INSTANCE(hsdram), control_mask, timing_mask);

  hsdram->rows_number = p_config->rows_number;
  hsdram->sdram_clock_divider = p_config->sdram_clock_divider;
  hsdram->global_state = HAL_SDRAM_STATE_CONFIGURED;
  hsdram->device_state[HAL_SDRAM_DEVICE1] = HAL_SDRAM_DEVICE_STATE_RESET;
  hsdram->device_state[HAL_SDRAM_DEVICE2] = HAL_SDRAM_DEVICE_STATE_RESET;

  return HAL_OK;
}

/**
  * @brief  Retrieve the common configuration for all devices.
  * @param  hsdram   Pointer to a @ref hal_sdram_handle_t structure.
  * @param  p_config Pointer to a @ref hal_sdram_common_config_t structure filled with the retrieved memory
  *                  configuration.
  * @note   If all retrieved timing parameters are zero, verify that the SDRAM clock frequency configuration is valid.
  *         In particular, ensure that the SDRAM clock is not disabled and that the kernel clock
  *         frequency is correctly set. If SDCLK is disabled, timing conversions are not be meaningful.
  */
void HAL_SDRAM_GetConfig(const hal_sdram_handle_t *hsdram, hal_sdram_common_config_t *p_config)
{
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();
  uint32_t control_cfg;
  uint32_t timing_cfg;
  uint32_t sdclk_freq_hz;

  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);

  FMC_SDRAM_GetConfig(SDRAM_GET_INSTANCE(hsdram), &control_cfg, &timing_cfg);

  p_config->read_pipe_delay = (hal_sdram_read_pipe_delay_t)(uint32_t)STM32_READ_BIT(control_cfg, FMC_SDCR_RPIPE);
  p_config->read_burst_state = (hal_sdram_read_burst_state_t)(uint32_t)STM32_READ_BIT(control_cfg, FMC_SDCR_RBURST);

  p_config->sdram_clock_divider = (hal_sdram_fmc_ker_ck_div_t)
                                  (uint32_t)STM32_READ_BIT(control_cfg, FMC_SDCR_SDCLK);

  sdclk_freq_hz = FMC_SDRAM_CalculateClockFrequency(clk_freq_hz, (uint32_t)p_config->sdram_clock_divider);
  p_config->row_cycle_delay_nsec = FMC_ConvertClockCycleToNanoseconds
                                   ((FMC_READ_FIELD(timing_cfg, FMC_SDTR_TRC_Msk, FMC_SDTR_TRC_Pos) + 1U),
                                    sdclk_freq_hz);
  p_config->precharge_command_delay_nsec = FMC_ConvertClockCycleToNanoseconds
                                           ((FMC_READ_FIELD(timing_cfg, FMC_SDTR_TRP_Msk, FMC_SDTR_TRP_Pos) + 1U),
                                            sdclk_freq_hz);
  p_config->rows_number = hsdram->rows_number;
}

/**
  * @brief   Set the memory configuration per device.
  * @param   hsdram             Pointer to a @ref hal_sdram_handle_t structure.
  * @param   device             Element of the @ref hal_sdram_device_t enumeration.
  * @param   p_config           Pointer to a @ref hal_sdram_memory_config_t structure.
  * @warning The first use of this API must be done after calling HAL_SDRAM_SetConfig() API.
  * @retval  HAL_INVALID_PARAM  The memory configuration structure pointer is NULL or the clock frequency is equal to 0.
  * @retval  HAL_OK             The common configuration is successfully configured.
  */
hal_status_t HAL_SDRAM_SetConfigMemory(hal_sdram_handle_t *hsdram, hal_sdram_device_t device,
                                       const hal_sdram_memory_config_t *p_config)
{
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();
  uint32_t memory_msk;
  uint32_t timing_msk;

  ASSERT_DBG_PARAM(hsdram    != NULL);
  ASSERT_DBG_PARAM(IS_FMC_SDRAM_KERNEL_CLK_DIV(hsdram->sdram_clock_divider));
  ASSERT_DBG_PARAM(IS_SDRAM_ALL_DEVICES(device));
  ASSERT_DBG_PARAM(p_config  != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_config == NULL) || (clk_freq_hz == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_SDRAM_MEMORY_BUS_WIDTH(p_config->memory_bus_width));
  ASSERT_DBG_PARAM(IS_SDRAM_INTERN_BANKS_NUMBER(p_config->intern_banks_number));
  ASSERT_DBG_PARAM(IS_SDRAM_COLUMN_ADDR_WIDTH(p_config->column_address_width));
  ASSERT_DBG_PARAM(IS_SDRAM_ROW_ADDR_WIDTH(p_config->row_address_width));
  ASSERT_DBG_PARAM(IS_SDRAM_CAS_LATENCY(p_config->cas_latency));

  uint32_t sdclk_freq_hz = FMC_SDRAM_CalculateClockFrequency(clk_freq_hz,
                                                             (uint32_t)hsdram->sdram_clock_divider);
  uint32_t load_to_active_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->load_to_active_delay_nsec,
                                                                   sdclk_freq_hz);
  uint32_t exit_self_refresh_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->exit_self_refresh_delay_nsec,
                                                                      sdclk_freq_hz);
  uint32_t self_refresh_time_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->self_refresh_time_nsec,
                                                                      sdclk_freq_hz);
  uint32_t write_recovery_time_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->write_recovery_time_nsec,
                                                                        sdclk_freq_hz);
  uint32_t activate_rd_wr_command_delay_tmp = FMC_ConvertNanosecondsToClockCycle(
                                                p_config->activate_rd_wr_command_delay_nsec, sdclk_freq_hz);

  ASSERT_DBG_PARAM(IS_FMC_LOAD_TO_ACTIVE_DELAY(load_to_active_tmp));
  ASSERT_DBG_PARAM(IS_FMC_EXIT_SELFREFRESH_DELAY(exit_self_refresh_tmp));
  ASSERT_DBG_PARAM(IS_FMC_SELFREFRESH_TIME(self_refresh_time_tmp));
  ASSERT_DBG_PARAM(IS_FMC_WRITE_RECOVERY_TIME(write_recovery_time_tmp));
  ASSERT_DBG_PARAM(IS_FMC_ROW_TO_COLUMN_DELAY(activate_rd_wr_command_delay_tmp));

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hsdram->device_state[device], HAL_SDRAM_DEVICE_STATE_RESET);

  memory_msk = ((uint32_t)p_config->memory_bus_width
                | (uint32_t)p_config->intern_banks_number
                | (uint32_t)p_config->row_address_width
                | (uint32_t)p_config->column_address_width
                | (uint32_t)p_config->cas_latency);

  timing_msk = (load_to_active_tmp - 1U) |
               FMC_WRITE_FIELD((exit_self_refresh_tmp - 1U),
                               FMC_SDTR_TXSR_Msk, FMC_SDTR_TXSR_Pos) |
               FMC_WRITE_FIELD((self_refresh_time_tmp - 1U),
                               FMC_SDTR_TRAS_Msk, FMC_SDTR_TRAS_Pos) |
               FMC_WRITE_FIELD((write_recovery_time_tmp - 1U),
                               FMC_SDTR_TWR_Msk, FMC_SDTR_TWR_Pos)   |
               FMC_WRITE_FIELD((activate_rd_wr_command_delay_tmp - 1U),
                               FMC_SDTR_TRCD_Msk, FMC_SDTR_TRCD_Pos);


  FMC_SDRAM_SetConfigMemory(SDRAM_GET_INSTANCE(hsdram), (uint32_t)device, memory_msk, timing_msk);

  FMC_Enable();

  hsdram->device_state[device] = HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the memory configuration per device.
  * @param hsdram   Pointer to a @ref hal_sdram_handle_t structure.
  * @param device   Element of the @ref hal_sdram_device_t enumeration.
  * @param p_config Pointer to a @ref hal_sdram_memory_config_t structure filled with the retrieved memory
  *                 configuration.
  * @note   If all retrieved timing parameters are zero, verify that the SDRAM clock frequency configuration is valid.
  *         In particular, ensure that the SDRAM clock is not disabled and that the kernel clock
  *         frequency is correctly set. If SDCLK is disabled, timing conversions are not be meaningful.
  */
void HAL_SDRAM_GetConfigMemory(const hal_sdram_handle_t *hsdram, hal_sdram_device_t device,
                               hal_sdram_memory_config_t *p_config)
{
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();
  uint32_t memory_cfg;
  uint32_t timing_cfg;

  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_FMC_SDRAM_KERNEL_CLK_DIV(hsdram->sdram_clock_divider));
  ASSERT_DBG_PARAM(IS_SDRAM_ALL_DEVICES(device));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hsdram->device_state[device], (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_ACTIVE);

  FMC_SDRAM_GetConfigMemory(SDRAM_GET_INSTANCE(hsdram), (uint32_t)device, &memory_cfg, &timing_cfg);


  p_config->memory_bus_width      = (hal_sdram_memory_bus_width_t)(uint32_t)STM32_READ_BIT(memory_cfg, FMC_SDCR_MWID);
  p_config->intern_banks_number   = (hal_sdram_intern_banks_number_t)(uint32_t)STM32_READ_BIT(memory_cfg, FMC_SDCR_NB);
  p_config->row_address_width     = (hal_sdram_row_addr_width_t)(uint32_t)STM32_READ_BIT(memory_cfg, FMC_SDCR_NR);
  p_config->column_address_width  = (hal_sdram_column_addr_width_t)(uint32_t)STM32_READ_BIT(memory_cfg, FMC_SDCR_NC);
  p_config->cas_latency           = (hal_sdram_cas_latency_t)(uint32_t)STM32_READ_BIT(memory_cfg, FMC_SDCR_CAS);
  uint32_t sdclk_freq_hz = FMC_SDRAM_CalculateClockFrequency(clk_freq_hz,
                                                             (uint32_t)hsdram->sdram_clock_divider);
  p_config->load_to_active_delay_nsec = FMC_ConvertClockCycleToNanoseconds
                                        ((FMC_READ_FIELD(timing_cfg, FMC_SDTR_TMRD_Msk, FMC_SDTR_TMRD_Pos) + 1U),
                                         sdclk_freq_hz);
  p_config->exit_self_refresh_delay_nsec = FMC_ConvertClockCycleToNanoseconds
                                           ((FMC_READ_FIELD(timing_cfg, FMC_SDTR_TXSR_Msk, FMC_SDTR_TXSR_Pos) + 1U),
                                            sdclk_freq_hz);
  p_config->self_refresh_time_nsec = FMC_ConvertClockCycleToNanoseconds
                                     ((FMC_READ_FIELD(timing_cfg, FMC_SDTR_TRAS_Msk, FMC_SDTR_TRAS_Pos) + 1U),
                                      sdclk_freq_hz);
  p_config->write_recovery_time_nsec = FMC_ConvertClockCycleToNanoseconds
                                       ((FMC_READ_FIELD(timing_cfg, FMC_SDTR_TWR_Msk, FMC_SDTR_TWR_Pos) + 1U),
                                        sdclk_freq_hz);
  p_config->activate_rd_wr_command_delay_nsec = FMC_ConvertClockCycleToNanoseconds
                                                ((FMC_READ_FIELD
                                                  (timing_cfg, FMC_SDTR_TRCD_Msk, FMC_SDTR_TRCD_Pos) + 1U),
                                                 sdclk_freq_hz);
}

/**
  * @brief   Complete the initialization sequence and make the memory ready for use and accessible.
  * @param   hsdram Pointer to a @ref hal_sdram_handle_t structure.
  * @param   device Element of the @ref hal_sdram_device_t enumeration.
  * @warning This API is called once the common, device configuration and the initialization sequence are performed,
  *          and the refresh rate is set.
  * @retval  HAL_OK The initialization sequence is done successfully.
  */
hal_status_t HAL_SDRAM_CompleteInitSequence(hal_sdram_handle_t *hsdram, hal_sdram_device_t device)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_SDRAM_ALL_DEVICES(device));

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hsdram->device_state[device], (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED);

  hsdram->device_state[device] = HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE;

  return HAL_OK;
}

/**
  * @brief  Retrieve the current base address of the selected SDRAM device.
  * @param  hsdram   Pointer to a @ref hal_sdram_handle_t structure.
  * @param  device   Element of the @ref hal_sdram_device_t enumeration.
  * @return uint32_t Base address of the selected SDRAM device.
  */
uint32_t HAL_SDRAM_GetDeviceBaseAddress(const hal_sdram_handle_t *hsdram, hal_sdram_device_t device)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_SDRAM_ALL_DEVICES(device));

  ASSERT_DBG_STATE(hsdram->global_state, (uint32_t)HAL_SDRAM_STATE_INIT | (uint32_t)HAL_SDRAM_STATE_CONFIGURED);

  STM32_UNUSED(hsdram);

  return FMC_SDRAM_GetDeviceBaseAddress((uint32_t)device);
}

/**
  * @}
  */

/** @addtogroup SDRAM_Exported_Functions_Group3
  * @{
This subsection provides a set of functions allowing to interface with the SDRAM device:
- HAL_SDRAM_SetRefreshRate(): used to set the refresh period of the SDRAM.
- HAL_SDRAM_GetRefreshRate(): used to get the refresh period value of the SDRAM memory device.
- HAL_SDRAM_GetDeviceMode() : used to return the SDRAM memory current device mode.
- HAL_SDRAM_SendCommand()   : used to issue a command to a specified SDRAM devices (device 1 or device 2).
- HAL_SDRAM_EnableSDCLK()   : used to enable the SDRAM clock during self-refresh mode.
- HAL_SDRAM_DisableSDCLK()  : used to disable the SDRAM clock during self-refresh mode.
- HAL_SDRAM_IsEnabledSDCLK(): used to get the SDRAM clock status.
  */

/**
  * @brief  Configure the refresh cycle interval to maintain SDRAM data integrity.
  * @param  hsdram             Pointer to a @ref hal_sdram_handle_t structure.
  * @param  refresh_period_ms  The SDRAM refresh period in milliseconds.
  * @note   This function configures the interval between refresh commands sent automatically by the FMC controller.
  *         The optimal period depends on SDRAM specifications and system clock frequency.
  * @retval HAL_OK             The refresh rate is set successfully.
  */
hal_status_t HAL_SDRAM_SetRefreshRate(hal_sdram_handle_t *hsdram, uint32_t refresh_period_ms)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_FMC_SDRAM_KERNEL_CLK_DIV(hsdram->sdram_clock_divider));

  uint32_t sdclk_freq_hz = FMC_SDRAM_CalculateClockFrequency(HAL_RCC_FMC_GetKernelClkFreq(),
                                                             (uint32_t)hsdram->sdram_clock_divider);
  uint32_t refresh_rate_tmp = FMC_SDRAM_AdjustRefreshPeriodCycle(refresh_period_ms, sdclk_freq_hz, hsdram->rows_number);

  ASSERT_DBG_PARAM(IS_SDRAM_REFRESH_RATE_VALUE(refresh_rate_tmp));

  uint32_t device_state1 = (uint32_t)hsdram->device_state[HAL_SDRAM_DEVICE1];

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);
  ASSERT_DBG_STATE((uint32_t)device_state1 | (uint32_t)hsdram->device_state[HAL_SDRAM_DEVICE2],
                   (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE);

  STM32_UNUSED(device_state1);

  FMC_SDRAM_SetRefreshRate(SDRAM_GET_INSTANCE(hsdram), refresh_rate_tmp);

  return HAL_OK;
}

/**
  * @brief  Get the SDRAM memory refresh rate.
  * @param  hsdram   Pointer to a @ref hal_sdram_handle_t structure.
  * @note   If the retrieved refresh period value is zero, check the clock frequency settings to ensure they are
  *         properly set.
  * @return uint32_t SDRAM refresh period in milliseconds.
  */
uint32_t HAL_SDRAM_GetRefreshRate(const hal_sdram_handle_t *hsdram)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_FMC_SDRAM_KERNEL_CLK_DIV(hsdram->sdram_clock_divider));

  uint32_t sdclk_freq_hz = FMC_SDRAM_CalculateClockFrequency(HAL_RCC_FMC_GetKernelClkFreq(),
                                                             (uint32_t)hsdram->sdram_clock_divider);
  uint32_t device_state1 = (uint32_t)hsdram->device_state[HAL_SDRAM_DEVICE1];

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);
  ASSERT_DBG_STATE((uint32_t)device_state1 | (uint32_t)hsdram->device_state[HAL_SDRAM_DEVICE2],
                   (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_ACTIVE);

  STM32_UNUSED(device_state1);

  return FMC_SDRAM_AdjustRefreshPeriodNanoseconds(FMC_SDRAM_GetRefreshRate(SDRAM_GET_INSTANCE(hsdram)),
                                                  sdclk_freq_hz, hsdram->rows_number);
}

/**
  * @brief  Return the SDRAM device current mode.
  * @param  hsdram                 Pointer to a @ref hal_sdram_handle_t structure.
  * @param  device                 Defines an element of the @ref hal_sdram_device_t enumeration.
  * @retval HAL_SDRAM_DEVICE_NORMAL_MODE  The SDRAM device is in normal mode.
  * @retval HAL_SDRAM_DEVICE_SELF_REFRESH The SDRAM device is in self refresh mode.
  * @retval HAL_SDRAM_DEVICE_POWER_DOWN   The SDRAM device is in the power down mode.
  */
hal_sdram_device_mode_t HAL_SDRAM_GetDeviceMode(const hal_sdram_handle_t *hsdram, hal_sdram_device_t device)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_SDRAM_ALL_DEVICES(device));

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hsdram->device_state[device],
                   (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_ACTIVE);

  return (hal_sdram_device_mode_t)(uint32_t)FMC_SDRAM_GetDeviceMode(SDRAM_GET_INSTANCE(hsdram),
                                                                    (uint32_t)device);
}

/**
  * @brief   Enable the SDRAM clock (SDCLK) during self-refresh mode.
  * @param   hsdram    Pointer to the SDRAM handle.
  * @note    The clock frequency is set to the same value configured before the clock disable.
  * @warning Call this API before exiting self-refresh mode to re-enable the clock disabled during self-refresh
  *          to save power.
  * @retval  HAL_OK    Clock enabled successfully.
  * @retval  HAL_ERROR At least one of the devices that are already configured and initialized is currently
  *          not in self-refresh mode.
  */
hal_status_t HAL_SDRAM_EnableSDCLK(hal_sdram_handle_t *hsdram)
{
  FMC_SDRAM_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hsdram != NULL);

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);

  hal_sdram_device_state_t device1_state = hsdram->device_state[HAL_SDRAM_DEVICE1];
  hal_sdram_device_state_t device2_state = hsdram->device_state[HAL_SDRAM_DEVICE2];

  ASSERT_DBG_STATE(device1_state, (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_RESET);
  ASSERT_DBG_STATE(device2_state, (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_RESET);
  ASSERT_DBG_STATE(((uint32_t)device1_state | (uint32_t)device2_state), HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE);

  p_instance = SDRAM_GET_INSTANCE(hsdram);

  /* Check that both devices are currently in self refresh mode */
  if (device1_state == HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE)
  {
    hal_sdram_device_mode_t device1_mode =
      (hal_sdram_device_mode_t)FMC_SDRAM_GetDeviceMode(p_instance, (uint32_t)HAL_SDRAM_DEVICE1);
    if (device1_mode != HAL_SDRAM_DEVICE_SELF_REFRESH)
    {
      return HAL_ERROR;
    }
  }

  if (device2_state == HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE)
  {
    hal_sdram_device_mode_t device2_mode =
      (hal_sdram_device_mode_t)FMC_SDRAM_GetDeviceMode(p_instance, (uint32_t)HAL_SDRAM_DEVICE2);
    if (device2_mode != HAL_SDRAM_DEVICE_SELF_REFRESH)
    {
      return HAL_ERROR;
    }
  }

  FMC_Disable();
  FMC_SDRAM_SetClockDivider(p_instance, (uint32_t)hsdram->sdram_clock_divider);
  FMC_Enable();

  return HAL_OK;
}

/**
  * @brief   Disable the SDRAM clock (SDCLK) during self-refresh mode.
  * @param   hsdram    Pointer to the SDRAM handle.
  * @note    The clock is disabled for all devices; therefore, ensure that both devices are in self-refresh mode,
  *          or that one is in self-refresh mode and the other is not in use.
  * @warning This API must be called only when the SDRAM device is in self-refresh mode to safely reduce power
  *          consumption, as the memory is internally clocked.
  *          Disabling the clock outside the self-refresh might case data loss or malfunction.
  * @retval  HAL_OK    Clock disabled successfully.
  * @retval  HAL_ERROR At least one of the devices, that has already been configured and initialized
  *                    is not currently in self-refresh mode.
  */
hal_status_t HAL_SDRAM_DisableSDCLK(const hal_sdram_handle_t *hsdram)
{
  FMC_SDRAM_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);

  hal_sdram_device_state_t device1_state = hsdram->device_state[HAL_SDRAM_DEVICE1];
  hal_sdram_device_state_t device2_state = hsdram->device_state[HAL_SDRAM_DEVICE2];

  ASSERT_DBG_STATE(device1_state, (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_RESET);
  ASSERT_DBG_STATE(device2_state, (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_RESET);
  ASSERT_DBG_STATE(((uint32_t)device1_state | (uint32_t)device2_state), HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE);

  p_instance = SDRAM_GET_INSTANCE(hsdram);

  /* Check that both devices are currently in self refresh mode */
  if (device1_state == HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE)
  {
    hal_sdram_device_mode_t device1_mode =
      (hal_sdram_device_mode_t)FMC_SDRAM_GetDeviceMode(p_instance, (uint32_t)HAL_SDRAM_DEVICE1);
    if (device1_mode != HAL_SDRAM_DEVICE_SELF_REFRESH)
    {
      return HAL_ERROR;
    }
  }

  if (device2_state == HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE)
  {
    hal_sdram_device_mode_t device2_mode =
      (hal_sdram_device_mode_t)FMC_SDRAM_GetDeviceMode(p_instance, (uint32_t)HAL_SDRAM_DEVICE2);
    if (device2_mode != HAL_SDRAM_DEVICE_SELF_REFRESH)
    {
      return HAL_ERROR;
    }
  }

  FMC_Disable();
  FMC_SDRAM_DisableSDCLK(p_instance);
  FMC_Enable();

  return HAL_OK;
}

/**
  * @brief  Get the SDRAM clock status.
  * @param  hsdram                  Pointer to a @ref hal_sdram_handle_t structure.
  * @retval HAL_SDRAM_FMC_KER_CK_DISABLED SDCLK is disabled.
  * @retval HAL_SDRAM_FMC_KER_CK_ENABLED  SDCLK is enabled.
  */
hal_sdram_fmc_ker_ck_status_t HAL_SDRAM_IsEnabledSDCLK(const hal_sdram_handle_t *hsdram)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);

  return (hal_sdram_fmc_ker_ck_status_t)FMC_SDRAM_IsEnabledSDCLK(SDRAM_GET_INSTANCE(hsdram));
}

/**
  * @brief  Send Command to the SDRAM device.
  * @param  hsdram            Pointer to a @ref hal_sdram_handle_t structure.
  * @param  device            Element of the @ref hal_sdram_device_t enumeration.
  * @param  p_command_config  Pointer to a @ref hal_sdram_command_t structure.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the command configuration structure pointer is NULL.
  */
hal_status_t HAL_SDRAM_SendCommand(hal_sdram_handle_t *hsdram, hal_sdram_device_t device,
                                   hal_sdram_command_t *p_command_config, uint32_t timeout_ms)
{
  volatile hal_sdram_device_state_t previous_state;
  FMC_SDRAM_TypeDef *p_instance;
  STM32_UNUSED(timeout_ms);

  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_SDRAM_ALL_DEVICES(device));
  ASSERT_DBG_PARAM(p_command_config  != NULL);

  ASSERT_DBG_PARAM(IS_SDRAM_COMMAND(p_command_config->command));
  ASSERT_DBG_PARAM(IS_SDRAM_COMMAND_PARAMETER(p_command_config->command, p_command_config->parameter));

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hsdram->device_state[device], (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE);

  p_instance = SDRAM_GET_INSTANCE(hsdram);
  uint32_t parameter_msk = 0U;

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_command_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_CHECK_UPDATE_STATE(hsdram, device_state[device],
                         ((uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED |
                          (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE),
                         HAL_SDRAM_DEVICE_STATE_ACTIVE, previous_state);

  switch (p_command_config->command)
  {
    case HAL_SDRAM_COMMAND_AUTOREFRESH:
      parameter_msk = FMC_WRITE_FIELD(p_command_config->parameter - 1U,
                                      FMC_SDCMR_NRFS_Msk, FMC_SDCMR_NRFS_Pos);
      break;

    case HAL_SDRAM_COMMAND_LOAD:
      parameter_msk = FMC_WRITE_FIELD(p_command_config->parameter,
                                      FMC_SDCMR_MRD_Msk, FMC_SDCMR_MRD_Pos);
      break;

    default:
      break;
  }

  if (device ==  HAL_SDRAM_DEVICE1)
  {
    parameter_msk |= FMC_WRITE_FIELD(1U, FMC_SDCMR_CTB1_Msk, FMC_SDCMR_CTB1_Pos);
  }
  else
  {
    parameter_msk |= FMC_WRITE_FIELD(1U, FMC_SDCMR_CTB2_Msk, FMC_SDCMR_CTB2_Pos);
  }

  FMC_SDRAM_SendCommand(p_instance, ((uint32_t)p_command_config->command
                                     | (uint32_t)parameter_msk));

  hsdram->device_state[device] = previous_state;


  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup SDRAM_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to control the SDRAM device:
- HAL_SDRAM_EnableWriteProtection()   : used to enable the write protection of the corresponding SDRAM device.
- HAL_SDRAM_DisableWriteProtection()  : used to disable the write protection of the corresponding SDRAM device.
- HAL_SDRAM_IsEnabledWriteProtection(): used to get the corresponding SDRAM device write protection status.
  */

/**
  * @brief   Enable the corresponding SDRAM device write protection.
  * @param   hsdram Pointer to a @ref hal_sdram_handle_t structure.
  * @param   device Defines an element of the @ref hal_sdram_device_t enumeration.
  * @warning This API can be used once the SDRAM device state is fully configured and ready for use.
  * @retval  HAL_OK The write protection is successfully enabled.
  */
hal_status_t HAL_SDRAM_EnableWriteProtection(hal_sdram_handle_t *hsdram, hal_sdram_device_t device)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_SDRAM_ALL_DEVICES(device));

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hsdram->device_state[device], (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE);

  FMC_SDRAM_EnableWriteProtection(SDRAM_GET_INSTANCE(hsdram), (uint32_t)device);

  hsdram->wr_protection_status[device] = HAL_SDRAM_WR_PROTECTED;

  return HAL_OK;
}

/**
  * @brief   Disable the corresponding SDRAM device write protection.
  * @param   hsdram Pointer to a @ref hal_sdram_handle_t structure.
  * @param   device Defines an element of the @ref hal_sdram_device_t enumeration.
  * @warning This API can be used once the SDRAM device state is fully configured and ready for use.
  * @retval  HAL_OK The write protection is successfully disabled.
  */
hal_status_t HAL_SDRAM_DisableWriteProtection(hal_sdram_handle_t *hsdram, hal_sdram_device_t device)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_SDRAM_ALL_DEVICES(device));

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hsdram->device_state[device], (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED
                   | (uint32_t)HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE);

  FMC_SDRAM_DisableWriteProtection(SDRAM_GET_INSTANCE(hsdram), (uint32_t)device);

  hsdram->wr_protection_status[device] = HAL_SDRAM_WR_NOT_PROTECTED;

  return HAL_OK;
}

/**
  * @brief  Get the corresponding SDRAM device write protection status.
  * @param  hsdram                     Pointer to a @ref hal_sdram_handle_t structure.
  * @param  device                     Defines an element of the @ref hal_sdram_device_t enumeration.
  * @retval HAL_SDRAM_WR_NOT_PROTECTED The SDRAM write protection is disabled.
  * @retval HAL_SDRAM_WR_PROTECTED     The SDRAM write protection is enabled.
  */
hal_sdram_wr_protection_status_t HAL_SDRAM_IsEnabledWriteProtection(const hal_sdram_handle_t *hsdram,
                                                                    hal_sdram_device_t device)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_SDRAM_ALL_DEVICES(device));

  ASSERT_DBG_STATE(hsdram->global_state, (uint32_t)HAL_SDRAM_STATE_INIT | (uint32_t)HAL_SDRAM_STATE_CONFIGURED);

  return (hal_sdram_wr_protection_status_t)FMC_SDRAM_IsEnabledWriteProtection(SDRAM_GET_INSTANCE(hsdram),
                                                                              (uint32_t)device);
}
/**
  * @}
  */

#if defined(USE_HAL_SDRAM_USER_DATA) && (USE_HAL_SDRAM_USER_DATA == 1U)

/** @addtogroup SDRAM_Exported_Functions_Group5
  * @{
This subsection provides a set of functions allowing to set and retrieve user specific data:
- The HAL_SDRAM_SetUserData(): used to store user data pointer into the handle.
- The HAL_SDRAM_GetUserData(): used to retrieve user data pointer from the handle.
  */

/**
  * @brief Store user data pointer into the handle.
  * @param hsdram      Pointer to a hal_sdram_handle_t structure.
  * @param p_user_data Pointer to the user data.
  */
void HAL_SDRAM_SetUserData(hal_sdram_handle_t *hsdram, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hsdram != NULL);

  hsdram->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve user data pointer from the handle.
  * @param  hsdram Pointer to a hal_sdram_handle_t structure.
  * @return Pointer to the user data.
  */
const void *HAL_SDRAM_GetUserData(const hal_sdram_handle_t *hsdram)
{
  ASSERT_DBG_PARAM(hsdram != NULL);

  return (hsdram->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_SDRAM_USER_DATA */

/** @addtogroup SDRAM_Exported_Functions_Group6
  * @{
This subsection provides a set of functions allowing to retrieve the SDRAM global state,
device state and the kernel clock frequency:
- The HAL_SDRAM_GetState()      : used to retrieve the SDRAM global state.
- The HAL_SDRAM_GetDeviceState(): used to retrieve the SDRAM device state.
- The HAL_SDRAM_GetClockFreq()  : used to retrieve the FMC kernel clock frequency.
  */

/**
  * @brief  Get the current global state.
  * @param  hsdram                      Pointer to a @ref hal_sdram_handle_t structure.
  * @retval HAL_SDRAM_STATE_RESET       The SDRAM not yet initialized.
  * @retval HAL_SDRAM_STATE_INIT        The SDRAM initialized but not yet configured.
  * @retval HAL_SDRAM_STATE_CONFIGURED  The SDRAM common configuration is performed for all devices.
  */
hal_sdram_state_t HAL_SDRAM_GetState(const hal_sdram_handle_t *hsdram)
{
  ASSERT_DBG_PARAM(hsdram != NULL);

  return hsdram->global_state;
}

/**
  * @brief  Get the current device state.
  * @param  hsdram                                   Pointer to a @ref hal_sdram_handle_t structure.
  * @param  device                                   Defines an element of the @ref hal_sdram_device_t enumeration.
  * @retval HAL_SDRAM_DEVICE_STATE_RESET             The SDRAM device not yet memory configured.
  * @retval HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED The SDRAM device initialized and memory configured.
  * @retval HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE       The SDRAM device is initialized, memory configured and ready
  *                                                  to be used.
  * @retval HAL_SDRAM_DEVICE_STATE_ACTIVE            The SDRAM device is in ongoing process.
  */
hal_sdram_device_state_t HAL_SDRAM_GetDeviceState(const hal_sdram_handle_t *hsdram, hal_sdram_device_t device)
{
  ASSERT_DBG_PARAM(hsdram != NULL);
  ASSERT_DBG_PARAM(IS_SDRAM_ALL_DEVICES(device));

  return hsdram->device_state[device];
}

/**
  * @brief  Get the current kernel clock frequency.
  * @param  hsdram Pointer to a @ref hal_sdram_handle_t structure.
  * @return Frequency in Hz.
  */
uint32_t HAL_SDRAM_GetClockFreq(const hal_sdram_handle_t *hsdram)
{
  ASSERT_DBG_PARAM((hsdram != NULL));

  ASSERT_DBG_STATE(hsdram->global_state, HAL_SDRAM_STATE_CONFIGURED);

  STM32_UNUSED(hsdram);

  return HAL_RCC_FMC_GetKernelClkFreq();
}
/**
  * @}
  */

/** @addtogroup SDRAM_Exported_Functions_Group7
  * @{
This section provides SDRAM IRQ handler and callback functions:
  - HAL_SDRAM_IRQHandler(): used to handle the SDRAM refresh error interrupt request.
  - HAL_SDRAM_RefreshErrorCallback(): weak refresh error callback function.
  - HAL_SDRAM_RegisterRefreshErrorCallback(): used to register a specific refresh error callback.
  */

/**
  * @brief Handle the SDRAM refresh error interrupt request.
  * @param hsdram Pointer to a hal_sdram_handle_t structure.
  */
void HAL_SDRAM_IRQHandler(hal_sdram_handle_t *hsdram)
{
  ASSERT_DBG_PARAM(hsdram != NULL);

  if (FMC_SDRAM_IsActiveFlag(SDRAM_GET_INSTANCE(hsdram), HAL_SDRAM_FLAG_REFRESH_ERROR) != 0U)
  {
    FMC_SDRAM_ClearFlag(SDRAM_GET_INSTANCE(hsdram), HAL_SDRAM_FLAG_CLEAR_REFRESH_ERROR);

#if defined(USE_HAL_SDRAM_REGISTER_CALLBACKS) && (USE_HAL_SDRAM_REGISTER_CALLBACKS == 1U)
    hsdram->p_refresh_error_cb(hsdram);
#else
    HAL_SDRAM_RefreshErrorCallback(hsdram);
#endif /* USE_HAL_SDRAM_REGISTER_CALLBACKS */
  }
}

#if defined (USE_HAL_SDRAM_REGISTER_CALLBACKS) && (USE_HAL_SDRAM_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register the SDRAM refresh error callback to be used instead of the weak HAL_SDRAM_RefreshErrorCallback()
  *         predefined callback.
  * @param  hsdram            Pointer to a @ref hal_sdram_handle_t structure.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_SDRAM_RegisterRefreshErrorCallback(hal_sdram_handle_t *hsdram, hal_sdram_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hsdram != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsdram->p_refresh_error_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_SDRAM_REGISTER_CALLBACKS */

/**
  * @brief SDRAM Refresh error callback.
  * @param hsdram Pointer to a @ref hal_sdram_handle_t structure.
  */
__WEAK void HAL_SDRAM_RefreshErrorCallback(hal_sdram_handle_t *hsdram)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hsdram);

  /* WARNING: This function must not be modified, when the callback is needed,
            the HAL_SDRAM_RefreshErrorCallback can be implemented in the user file
  */
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
#endif /* USE_HAL_SDRAM_MODULE */
#endif /* FMC_SDRAM_BK5 */

/**
  * @}
  */
