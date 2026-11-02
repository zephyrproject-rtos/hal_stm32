/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_sram.c
  * @brief   SRAM HAL module driver.
  *          This file provides a generic firmware to drive SRAM memories mounted as external device.
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

#if defined (FMC_NORSRAM_BK1)
#if defined(USE_HAL_SRAM_MODULE) && (USE_HAL_SRAM_MODULE == 1)
/** @addtogroup SRAM
  * @{
  */
/** @defgroup SRAM_Introduction SRAM Introduction
  * @{

  - The SRAM hardware abstraction layer provides a set of APIs to interface with SRAM memory devices
    via the STM32 Flexible Memory Controller (FMC) peripheral.

  - The SRAM HAL driver simplifies the initialization and configuration, ensuring the memory is accessible
    and ready for use.

  - This abstraction layer ensures portability and ease of use across different STM32 series.

  */
/**
  * @}
  */

/** @defgroup SRAM_How_To_Use SRAM How To Use
  * @{

# How to use the SRAM HAL module driver

## The FMC SRAM main features :

This SRAM HAL driver is a generic driver which contains a set of APIs used to configure the FMC SRAM sub-banks
to interface with SRAM, PSRAM and CRAM memories.

The FMC SRAM peripheral supports the following read and write access modes :

 - SRAM memories :
   - Asynchronous read and asynchronous write with identical timing for both operations.
   - Asynchronous read and asynchronous write with distinct timing for each operation.

 - PSRAM/CRAM memories :
   - Asynchronous read and asynchronous write with identical timing for both operations.
   - Asynchronous read and asynchronous write with distinct timing for each operation.
   - Synchronous read and synchronous write.
   - Synchronous read and asynchronous write.
   - Asynchronous read and synchronous write.

The FMC SRAM peripheral supports the write protection feature.

## The SRAM HAL driver can be used as follows :

This module provides 5 different set of APIs that allows to :

  - Initialize and de-initialize the logical FMC SRAM object ( @ref hal_sram_handle_t), retrieve the associated SRAM
    peripheral instance, set and get region remap :
  - Initialize the logical FMC SRAM object and associate it to a physical instance (sub-bank).
    This functionality is ensured by HAL_SRAM_Init() function.
  - De-initialize the logical FMC SRAM object and disable the SRAM sub-bank.
    This functionality is ensured by HAL_SRAM_DeInit() function.
  - Retrieve the SRAM instance by calling HAL_SRAM_GetInstance().
  - At this stage, the mapping of FMC SRAM regions can be modified, if required, allowing to access the SRAM memory
    at two different address mappings by calling HAL_SRAM_SetRegionRemap().
  - Retrieve the current memory region remap by calling HAL_SRAM_GetRegionRemap().

- Configure the FMC SRAM to be ready to use and retrieve the current configuration :

  - Configure the FMC SRAM through three steps by following the order below :

    - Step 1 (FMC configuration) : is the first step to perform once the HAL SRAM driver is initialized.
      This functionality is ensured by HAL_SRAM_SetConfig() function.

      At this stage, the SRAM is partially configured but not yet ready to use.

    - Step 2 (Memory configuration) : is the second step to perform once the FMC is configured.
      This functionality is ensured by one of these 5 functions depending on the external device access mode :
      - HAL_SRAM_SetConfigRdWrAsyncMemory() function to set the configuration for memories with asynchronous read and
        asynchronous write access mode. This API sets identical timing for both access.
      - HAL_SRAM_SetWrAsyncTimings() function to be called after HAL_SRAM_SetConfigRdWrAsyncMemory(), when memory with
        asynchronous read and asynchronous write access mode requires a different timing configuration for write
        transactions.
      - HAL_SRAM_SetConfigRdWrSyncMemory() function to set the configuration for memories with synchronous read and
        synchronous write access mode.
      - HAL_SRAM_SetConfigRdSyncWrAsyncMemory() function to set the configuration for memories with synchronous read and
        asynchronous write access mode.
      - HAL_SRAM_SetConfigRdAsyncWrSyncMemory() function to set the configuration for memories with asynchronous read
        and synchronous write access mode.

        At this stage, the SRAM is fully configured but not yet ready to use.

    - Step 3 (Memory enable/disable) : is the third step to perform once the SRAM is fully configured.
      This functionality is ensured by HAL_SRAM_EnableMemory() and HAL_SRAM_DisableMemory() functions.
      - HAL_SRAM_EnableMemory() : function to enable the SRAM sub-bank and make it accessible for read and write
        operations.
      - HAL_SRAM_DisableMemory() : function to disable the SRAM sub-bank which is useful when memory configuration
        adjustments are needed or to save power. The HAL_SRAM_EnableMemory() must be recalled to enable the memory
        and make it accessible.

        At this stage, the SRAM is fully configured, enabled and ready for use.

  - Retrieve the current configuration through the following functions :

    - Retrieve the FMC configuration :
      This functionality is ensured by HAL_SRAM_GetConfig().

    - Retrieve the memory configuration :
      This functionality is ensured by one of these 5 functions depending on the external device access mode :
      - HAL_SRAM_GetConfigRdWrAsyncMemory() function to get the memory configuration for memories with asynchronous read
        and asynchronous write access mode.
      - HAL_SRAM_GetWrAsyncTimings() function to get the timing configuration for write operations, when the memory with
        asynchronous read and asynchronous write access mode has a different timing configuration for write
        transactions.
      - HAL_SRAM_GetConfigRdWrSyncMemory() function to get the memory configuration for memories with synchronous read
       and synchronous write access mode.
      - HAL_SRAM_GetConfigRdSyncWrAsyncMemory() function to get the memory configuration for memories with synchronous
        read and asynchronous write access mode.
      - HAL_SRAM_GetConfigRdAsyncWrSyncMemory() function to get the memory configuration for memories with asynchronous
        read and synchronous write access mode.
      - To identify the base address of the FMC SRAM memory region before performing any read or write operations,
        the region start address can be retrieved by calling HAL_SRAM_GetRegionBaseAddress().

- Manage the FMC SRAM peripheral access when it is fully configured :

  - Enable the FMC SRAM write protection (when disabled) to prevent any write access to the external device.
    This functionality is ensured by HAL_SRAM_EnableWriteProtection() function.

  - Disable the FMC SRAM write protection (when enabled) to allow any write access to the external device.
    This functionality is ensured by HAL_SRAM_DisableWriteProtection() function.

  - Retrieve the FMC SRAM sub-bank write protection state.
    This functionality is ensured by HAL_SRAM_IsEnabledWriteProtection() function.

- Store and retrieve user data :

  - Store user data pointer into the handle.
    This functionality is ensured by HAL_SRAM_SetUserData() function.

  - Retrieve user data pointer from the handle.
    This functionality is ensured by HAL_SRAM_GetUserData() function.

- Retrieve the HAL SRAM state and clock frequency :

  - Retrieve the HAL SRAM state.
    This functionality is ensured by HAL_SRAM_GetState() function.

  - Retrieve the clock frequency.
    This functionality is ensured by HAL_SRAM_GetClockFreq() function.

- The read and write process must be managed within the application side (outside the HAL SRAM module) after fully
  configuring the FMC SRAM.
  */
/**
  * @}
  */

/** @defgroup SRAM_Configuration_Table SRAM Configuration Table
  * @{
## Configuration inside the SRAM driver

Config defines                | Description     | Default value     | Note
----------------------------- | --------------- | ----------------- | -------------------------------------------------
USE_ASSERT_DBG_PARAM          | from IDE        | NA                | Allows to use the assert check parameters.
USE_ASSERT_DBG_STATE          | from IDE        | NA                | Allows to use the assert check states.
USE_HAL_CHECK_PARAM           | from hal_conf.h | 0U                | Allows to use the run-time check parameters.
USE_HAL_SRAM_MODULE           | from hal_conf.h | 1U                | Allows to use the HAL SRAM module.
USE_FMC_CLK_ENABLE_MODEL      | from hal_conf.h | HAL_CLK_ENABLE_NO | Allows to enable the FMC clock.
USE_HAL_SRAM_USER_DATA        | from hal_conf.h | 0U                | Allows to use user data.
  */

/**
  * @}
  */

/* Private constant --------------------------------------------------------------------------------------------------*/
/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup SRAM_Private_Macros SRAM Private Macros
  * @{
  */
/*! Check the memory type parameter */
#define IS_SRAM_MEMORY(memory) (((memory) == HAL_SRAM_MEMORY_TYPE_SRAM) || ((memory) == HAL_SRAM_MEMORY_TYPE_PSRAM))

/*! Check the data address multiplexing parameter */
#define IS_SRAM_MUX(mux) (((mux) == HAL_SRAM_MUX_DATA_ADDR_DISABLE) || ((mux) == HAL_SRAM_MUX_DATA_ADDR_ENABLE))

/*! Check the data width parameter */
#define IS_SRAM_MEMORY_WIDTH(width) (((width) == HAL_SRAM_DATA_BUS_WIDTH_8_BIT) \
                                     || ((width) == HAL_SRAM_DATA_BUS_WIDTH_16_BIT))

/*! Check the write fifo parameter */
#define IS_SRAM_WRITE_FIFO(fifo) (((fifo) == HAL_SRAM_WRITE_FIFO_DISABLE) || ((fifo) == HAL_SRAM_WRITE_FIFO_ENABLE))

/*! Check the wait signal polarity parameter */
#define IS_SRAM_WAIT_POLARITY(polarity) (((polarity) == HAL_SRAM_WAIT_SIGNAL_POLARITY_LOW) \
                                         || ((polarity) == HAL_SRAM_WAIT_SIGNAL_POLARITY_HIGH))

/*! Check the synchronous wait signal state parameter */
#define IS_SRAM_SYNC_WAIT_SIGNAL(signal) (((signal) == HAL_SRAM_SYNC_WAIT_SIGNAL_DISABLE) \
                                          || ((signal) == HAL_SRAM_SYNC_WAIT_SIGNAL_ENABLE))

/*! Check the asynchronous wait signal state parameter */
#define IS_SRAM_ASYNC_WAIT_SIGNAL(signal) (((signal) == HAL_SRAM_ASYNC_WAIT_SIGNAL_DISABLE) \
                                           || ((signal) == HAL_SRAM_ASYNC_WAIT_SIGNAL_ENABLE))

/*! Check the continuous clock parameter */
#define IS_SRAM_CONTINOUS_CLOCK(clock) (((clock) == HAL_SRAM_CONTINUOUS_CLOCK_SYNC_ONLY) \
                                        || ((clock) == HAL_SRAM_CONTINUOUS_CLOCK_SYNC_ASYNC))

/*! Check the CRAM page size parameter */
#define IS_SRAM_PAGE_SIZE(size) (((size) == HAL_SRAM_CRAM_PAGE_SIZE_NONE)        \
                                 || ((size) == HAL_SRAM_CRAM_PAGE_SIZE_128_BYTE) \
                                 || ((size) == HAL_SRAM_CRAM_PAGE_SIZE_256_BYTE) \
                                 || ((size) == HAL_SRAM_CRAM_PAGE_SIZE_512_BYTE) \
                                 || ((size) == HAL_SRAM_CRAM_PAGE_SIZE_1024_BYTE))

/*! Check the access mode parameter */
#define IS_SRAM_ACCESS_MODE(mode) (((mode) == HAL_SRAM_ACCESS_MODE_A) \
                                   || ((mode) == HAL_SRAM_ACCESS_MODE_D))

/*! Get the handle instance */
#define SRAM_GET_INSTANCE(handle) ((FMC_NORSRAM_SUBBANK_TypeDef *)((uint32_t)(handle)->instance))

/*! Check the SRAM region remap parameter value */
#define IS_SRAM_REGION_REMAP(remap) (((remap) == HAL_SRAM_NOR_REGION1_SDRAM_DEVICE1_REGION5) \
                                     || ((remap) == HAL_SRAM_NOR_REGION5_SDRAM_DEVICE1_REGION1))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup SRAM_Exported_Functions
  * @{
  */

/** @addtogroup SRAM_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and de-initialize the SRAM driver :
- The HAL_SRAM_Init() API : allows to initialize the SRAM handle and enable the peripheral clock when
  USE_FMC_CLK_ENABLE_MODEL is different from HAL_CLK_ENABLE_NO.

- The HAL_SRAM_DeInit() API : allows to de-init the HAL SRAM driver for the given handle and disable the write
  protection and the corresponding SRAM sub-bank.

- The HAL_SRAM_GetInstance(): allows to retrieve the SRAM instance.

- The HAL_SRAM_SetRegionRemap(): allows to set the FMC SRAM region remap.

- The HAL_SRAM_GetRegionRemap(): allows to retrieve the FMC SRAM region remap.
  */

/**
  * @brief  Initialize the SRAM handle field and associate a physical instance.
  * @param  hsram             Pointer to a @ref hal_sram_handle_t structure.
  * @param  instance          @ref hal_sram_t enumerated type variable to be set according to the physical instance.
  * @note   The FMC clock can be activated within the HAL_SRAM_Init() function by setting the USE_FMC_CLK_ENABLE_MODEL
  *         flag to HAL_CLK_ENABLE_PERIPH_ONLY in the configuration file stm32h7pxx_hal_conf.h or by explicitly
  *         calling the HAL_RCC_FMC_EnableClock() API within the application when the USE_FMC_CLK_ENABLE_MODEL is not
  *         defined or defined to flag HAL_CLK_ENABLE_NO.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the SRAM handle is NULL.
  * @retval HAL_OK            The HAL SRAM driver is initialized according to the given handle and instance.
  */
hal_status_t HAL_SRAM_Init(hal_sram_handle_t *hsram, hal_sram_t instance)
{
  ASSERT_DBG_PARAM(hsram != NULL);
  ASSERT_DBG_PARAM(IS_FMC_NORSRAM_ALL_INSTANCE((FMC_NORSRAM_SUBBANK_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hsram == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsram->instance = instance;

#if defined (USE_FMC_CLK_ENABLE_MODEL) && (USE_FMC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_FMC_EnableClock();
#endif /* USE_FMC_CLK_ENABLE_MODEL */

#if defined(USE_HAL_SRAM_USER_DATA) && (USE_HAL_SRAM_USER_DATA == 1U)
  hsram->p_user_data = NULL;
#endif /* USE_HAL_SRAM_USER_DATA */

  hsram->wr_protection_status = HAL_SRAM_WR_PROTECTION_DISABLED;

  hsram->global_state = HAL_SRAM_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief De-init the HAL SRAM driver for the given handle and disable the write protection and the
  *        corresponding SRAM sub-bank.
  * @param hsram Pointer to a @ref hal_sram_handle_t structure.
  * @warning This API disables the SRAM bank. It must be called only after all SRAM transfers are
  *          completed. Accessing a disabled SRAM bank while a transfer is still ongoing causes
  *          an AXI bus error.
  */
void HAL_SRAM_DeInit(hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);
  ASSERT_DBG_PARAM(IS_FMC_NORSRAM_ALL_INSTANCE(SRAM_GET_INSTANCE(hsram)));

  FMC_NOR_SRAM_Disable(SRAM_GET_INSTANCE(hsram));

  FMC_NOR_SRAM_DisableWriteProtection(SRAM_GET_INSTANCE(hsram));

  hsram->wr_protection_status = HAL_SRAM_WR_PROTECTION_DISABLED;

  hsram->global_state = HAL_SRAM_STATE_RESET;
}

/**
  * @brief  Get the SRAM instance.
  * @param  hsram    Pointer to a @ref hal_sram_handle_t structure.
  * @retval HAL_SRAM The HAL SRAM instance.
  */
hal_sram_t HAL_SRAM_GetInstance(const hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);
  ASSERT_DBG_PARAM(IS_FMC_NORSRAM_ALL_INSTANCE(SRAM_GET_INSTANCE(hsram)));

  return hsram->instance;
}

/**
  * @brief  Set the SRAM region remap.
  * @param  hsram Pointer to a @ref hal_sram_handle_t structure.
  * @param  remap Element of the @ref hal_sram_region_remap_t enumeration.
  * @retval HAL_OK The Remap is set successfully.
  */
hal_status_t HAL_SRAM_SetRegionRemap(const hal_sram_handle_t *hsram, hal_sram_region_remap_t remap)
{
  ASSERT_DBG_PARAM(hsram != NULL);
  ASSERT_DBG_PARAM(IS_SRAM_REGION_REMAP(remap));

  ASSERT_DBG_STATE(hsram->global_state, HAL_SRAM_STATE_INIT);

  STM32_UNUSED(hsram);

  FMC_Disable();
  FMC_SetRegionRemap((uint32_t)remap);

  return HAL_OK;
}

/**
  * @brief  Get the SRAM region remap.
  * @param  hsram                                      Pointer to a @ref hal_sram_handle_t structure.
  * @retval HAL_SRAM_NOR_REGION1_SDRAM_DEVICE1_REGION5 The SRAM/PSRAM/NOR is remapped to region 1 and
  *                                                    the SDRAM device 1 is remapped to the region 5.
  * @retval HAL_SRAM_NOR_REGION5_SDRAM_DEVICE1_REGION1 The SRAM/PSRAM/NOR is remapped to region 5 and the
  *                                                    SDRAM device 1 is remapped to the region 1.
  */
hal_sram_region_remap_t HAL_SRAM_GetRegionRemap(const hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);

  ASSERT_DBG_STATE(hsram->global_state, ((uint32_t)HAL_SRAM_STATE_INIT
                                         | (uint32_t)HAL_SRAM_STATE_CONFIGURED
                                         | (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED
                                         | (uint32_t)HAL_SRAM_STATE_IDLE));

  STM32_UNUSED(hsram);

  return ((hal_sram_region_remap_t)FMC_GetRegionRemap());
}
/**
  * @}
  */


/** @addtogroup SRAM_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to configure the the FMC SRAM sub-banks and to retrieve the current
configuration.

The full configuration is done through three steps and following the order below :
- Step 1 (Static configuration of FMC peripheral) :
  - HAL_SRAM_SetConfig() : used to apply the user static configuration of FMC peripheral specified within
                           @ref hal_sram_config_t structure.

- Step 2 (Memory configuration) :
  Depending on the external device, one of these APIs is called :
  - HAL_SRAM_SetConfigRdWrAsyncMemory()     : used to apply the user memory configuration for memories with asynchronous
                                              read and asynchronous write access mode within
                                              @ref hal_sram_rd_wr_async_memory_config_t structure.
                                              @note when separate timing configuration for read and write transactions
                                              is needed, the HAL_SRAM_SetWrAsyncTimings() API must be called after
                                              HAL_SRAM_SetConfigRdWrAsyncMemory(), to set the write timing parameters.
                                              In this case, the HAL_SRAM_SetConfigRdWrAsyncMemory() function sets timing
                                              only for read accesses.
  - HAL_SRAM_SetWrAsyncTimings()            : used to apply a different timing configuration for write transactions, for
                                              memories with asynchronous read and asynchronous write access mode within
                                              @ref hal_sram_wr_async_timings_t structure.
  - HAL_SRAM_SetConfigRdWrSyncMemory()      : used to apply the user memory configuration for memories with synchronous
                                              read and synchronous write access mode within
                                              @ref hal_sram_rd_wr_sync_memory_config_t structure.
  - HAL_SRAM_SetConfigRdSyncWrAsyncMemory() : used to apply the user memory configuration for memories with synchronous
                                              read and asynchronous write access mode within
                                              @ref hal_sram_rd_sync_wr_async_memory_config_t structure.
  - HAL_SRAM_SetConfigRdAsyncWrSyncMemory() : used to apply the user memory configuration for memories with asynchronous
                                              read and synchronous write access mode within
                                              @ref hal_sram_rd_async_wr_sync_memory_config_t structure.
- Step 3 (Memory enable/disable) :
  - HAL_SRAM_EnableMemory()                 : used to enable the SRAM sub-bank and make it accessible for read and write
                                              operations.
  - HAL_SRAM_DisableMemory()                : used to disable the SRAM sub-bank which is useful when memory
                                              configuration adjustments are needed or to save power.

The configuration parameters are retrieved through these APIs :
- Static configuration of FMC peripheral :
  - HAL_SRAM_GetConfig() : used to retrieve the FMC configuration and to fill it into @ref hal_sram_config_t structure.

- Memory configuration :
  - HAL_SRAM_GetConfigRdWrAsyncMemory()     : used to retrieve the user memory configuration for memories with
                                              asynchronous read and asynchronous write access mode and to fill it into
                                              @ref hal_sram_rd_wr_async_memory_config_t structure.
  - HAL_SRAM_GetWrAsyncTimings()            : used to retrieve the user timing configuration for write operations, when
                                              the memory with asynchronous read and asynchronous write access mode has a
                                              different timing configuration for write transactions and to fill it into
                                              @ref hal_sram_wr_async_timings_t structure.
  - HAL_SRAM_GetConfigRdWrSyncMemory()      : used to retrieve the user memory configuration for memories with
                                              synchronous read and synchronous write access mode and to fill it into
                                              @ref hal_sram_rd_wr_sync_memory_config_t structure.
  - HAL_SRAM_GetConfigRdSyncWrAsyncMemory() : used to retrieve the user memory configuration for memories with
                                              synchronous read and asynchronous write access mode and to fill it into
                                              @ref hal_sram_rd_sync_wr_async_memory_config_t structure.
  - HAL_SRAM_GetConfigRdAsyncWrSyncMemory() : used to retrieve the user memory configuration for memories with
                                              asynchronous read and synchronous write access mode and to fill it into
                                              @ref hal_sram_rd_async_wr_sync_memory_config_t structure.
  - HAL_SRAM_GetRegionBaseAddress()         : used to retrieve the FMC SRAM region base address.
  */

/**
  * @brief   Set the static configuration of FMC peripheral.
  * @param   hsram             Pointer to a @ref hal_sram_handle_t structure.
  * @param   p_config          Pointer to a @ref hal_sram_config_t structure.
  * @warning This API is the first API to call once the HAL SRAM driver is initialized.
  * @retval  HAL_INVALID_PARAM Invalid parameter return when the configuration structure pointer is NULL.
  * @retval  HAL_OK            The static FMC configuration is successfully configured.
  */
hal_status_t HAL_SRAM_SetConfig(hal_sram_handle_t *hsram, const hal_sram_config_t *p_config)
{
  ASSERT_DBG_PARAM(hsram    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_PARAM(IS_SRAM_MEMORY(p_config->memory_type));
  ASSERT_DBG_PARAM(IS_SRAM_WRITE_FIFO(p_config->write_fifo));
  ASSERT_DBG_PARAM(IS_SRAM_WAIT_POLARITY(p_config->wait_signal_polarity));

  ASSERT_DBG_STATE(hsram->global_state, HAL_SRAM_STATE_INIT);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_Disable();

  FMC_NOR_SRAM_SetConfig(SRAM_GET_INSTANCE(hsram), ((uint32_t)p_config->memory_type | (uint32_t)p_config->write_fifo
                                                    | (uint32_t)p_config->wait_signal_polarity));

  hsram->global_state = HAL_SRAM_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the static configuration of FMC peripheral.
  * @param hsram    Pointer to a @ref hal_sram_handle_t structure.
  * @param p_config Pointer to a @ref hal_sram_config_t structure filled with the retrieved static
  *                 FMC peripheral configuration.
  */
void HAL_SRAM_GetConfig(const hal_sram_handle_t *hsram, hal_sram_config_t *p_config)
{
  uint32_t config;

  ASSERT_DBG_PARAM(hsram    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hsram->global_state, ((uint32_t)HAL_SRAM_STATE_CONFIGURED
                                         | (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED
                                         | (uint32_t)HAL_SRAM_STATE_IDLE));

  FMC_NOR_SRAM_GetConfig(SRAM_GET_INSTANCE(hsram), &config);

  p_config->memory_type          = (hal_sram_memory_type_t)(uint32_t)STM32_READ_BIT(config, FMC_BCRx_MTYP);
  p_config->write_fifo           = (hal_sram_write_fifo_state_t)(uint32_t)STM32_READ_BIT(config, FMC_BCR1_WFDIS);
  p_config->wait_signal_polarity = (hal_sram_wait_signal_polarity_t)(uint32_t)STM32_READ_BIT(config, FMC_BCRx_WAITPOL);
}

/**
  * @brief   Set the memory configuration for memories with asynchronous read and asynchronous write access mode.
  * @param   hsram             Pointer to a @ref hal_sram_handle_t structure.
  * @param   p_config          Pointer to a @ref hal_sram_rd_wr_async_memory_config_t structure.
  * @warning The first use of this API must be done after calling HAL_SRAM_SetConfig() API for SRAM, PSRAM and CRAM
  *          memories then, it can be reused multi-time to adjust memory configuration when needed.
  * @retval  HAL_INVALID_PARAM The memory configuration structure pointer is NULL or the clock frequency is equal
  *                            to zero.
  * @retval  HAL_OK            The memory is successfully configured.
  */
hal_status_t HAL_SRAM_SetConfigRdWrAsyncMemory(hal_sram_handle_t *hsram,
                                               const hal_sram_rd_wr_async_memory_config_t *p_config)
{
  uint32_t timing_mask;
  uint32_t control_mask;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hsram    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_SRAM_MEMORY_WIDTH(p_config->memory.data_bus_width));
  ASSERT_DBG_PARAM(IS_SRAM_PAGE_SIZE(p_config->memory.cram_page_size_byte));
  ASSERT_DBG_PARAM(IS_SRAM_MUX(p_config->memory.mux_data_addr));
  ASSERT_DBG_PARAM(IS_SRAM_ASYNC_WAIT_SIGNAL(p_config->timings.async_wait));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_config == NULL) || (clk_freq_hz == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t addr_setup_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.addr_setup_nsec,
                                                               clk_freq_hz);
  uint32_t addr_hold_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.addr_hold_nsec,
                                                              clk_freq_hz);
  uint32_t data_setup_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.data_setup_nsec,
                                                               clk_freq_hz);
  uint32_t bus_turnaround_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.bus_turnaround_nsec, clk_freq_hz);

  ASSERT_DBG_PARAM(IS_FMC_ADDR_SETUP_TIME(addr_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_HOLD_TIME(addr_hold_tmp));
  ASSERT_DBG_PARAM(IS_FMC_DATASETUP_TIME(data_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_TURNAROUND_TIME(bus_turnaround_tmp));

  ASSERT_DBG_STATE(hsram->global_state, (uint32_t)HAL_SRAM_STATE_CONFIGURED
                   | (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED);

  /* Set configuration mask value */
  control_mask = (uint32_t)p_config->memory.data_bus_width  | (uint32_t)p_config->memory.cram_page_size_byte
                 | (uint32_t)p_config->memory.mux_data_addr | (uint32_t)p_config->timings.async_wait;

  timing_mask = addr_setup_tmp | FMC_WRITE_FIELD(addr_hold_tmp, FMC_BTRx_ADDHLD_Msk, FMC_BTRx_ADDHLD_Pos)
                | FMC_WRITE_FIELD(data_setup_tmp, FMC_BTRx_DATAST_Msk, FMC_BTRx_DATAST_Pos)
                | FMC_WRITE_FIELD(bus_turnaround_tmp - 1U, FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)
                | FMC_BTRx_CLKDIV | FMC_BTRx_DATLAT;

  FMC_Disable();

  FMC_NOR_SRAM_SetConfigMemory(SRAM_GET_INSTANCE(hsram), control_mask, timing_mask);

  FMC_Enable();

  hsram->global_state = HAL_SRAM_STATE_MEMORY_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the memory configuration for memories with asynchronous read and asynchronous write access mode.
  * @param hsram    Pointer to a @ref hal_sram_handle_t structure.
  * @param p_config Pointer to a @ref hal_sram_rd_wr_async_memory_config_t structure filled with the retrieved memory
  *                 configuration.
  * @note  If all retrieved timing parameters are zero, check the clock frequency settings to ensure they are properly
  *        set.
  */
void HAL_SRAM_GetConfigRdWrAsyncMemory(const hal_sram_handle_t *hsram, hal_sram_rd_wr_async_memory_config_t *p_config)
{
  uint32_t memory_cfg;
  uint32_t timing_cfg;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hsram    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hsram->global_state, (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_SRAM_STATE_IDLE);

  /* Get configuration value */
  FMC_NOR_SRAM_GetConfigMemory(SRAM_GET_INSTANCE(hsram), &memory_cfg, &timing_cfg);

  p_config->memory.data_bus_width = (hal_sram_data_bus_width_t)(uint32_t)STM32_READ_BIT(memory_cfg, FMC_BCRx_MWID);
  p_config->memory.cram_page_size_byte   = (hal_sram_cram_page_size_t)(uint32_t)STM32_READ_BIT(memory_cfg,
                                           FMC_BCRx_CPSIZE);
  p_config->memory.mux_data_addr         = (hal_sram_mux_data_addr_state_t)(uint32_t)STM32_READ_BIT(memory_cfg,
                                           FMC_BCRx_MUXEN);

  p_config->timings.async_wait = (hal_sram_async_wait_signal_state_t)(uint32_t)STM32_READ_BIT(memory_cfg,
                                 FMC_BCRx_ASYNCWAIT);

  p_config->timings.async_access_timings.addr_setup_nsec = FMC_ConvertClockCycleToNanoseconds(STM32_READ_BIT(timing_cfg,
                                                           FMC_BTRx_ADDSET), clk_freq_hz);

  p_config->timings.async_access_timings.addr_hold_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                          FMC_BTRx_ADDHLD_Msk, FMC_BTRx_ADDHLD_Pos), clk_freq_hz);

  p_config->timings.async_access_timings.data_setup_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                           FMC_BTRx_DATAST_Msk, FMC_BTRx_DATAST_Pos), clk_freq_hz);

  p_config->timings.bus_turnaround_nsec = FMC_ConvertClockCycleToNanoseconds
                                          ((FMC_READ_FIELD(timing_cfg, FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)
                                            + 1U), clk_freq_hz);
}

/**
  * @brief   Set the timing configuration for asynchronous write transactions.
  * @param   hsram             Pointer to a @ref hal_sram_handle_t structure.
  * @param   p_timings         Pointer to a @ref hal_sram_wr_async_timings_t structure.
  * @warning When separate timing configuration for read and write transactions is needed, this API must be called after
  *          HAL_SRAM_SetConfigRdWrAsyncMemory(), to set the write timing parameters, it can be reused multi-time
  *          to adjust timings for write transactions when needed.
  * @retval  HAL_INVALID_PARAM The timing configuration structure pointer is NULL or the clock frequency is equal
  *                            to zero.
  * @retval  HAL_OK            The timing is successfully configured.
  */
hal_status_t HAL_SRAM_SetWrAsyncTimings(hal_sram_handle_t *hsram, const hal_sram_wr_async_timings_t *p_timings)
{
  uint32_t rd_access_mode_mask;
  uint32_t wr_timing_mask;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hsram     != NULL);
  ASSERT_DBG_PARAM(p_timings != NULL);
  ASSERT_DBG_PARAM(IS_SRAM_ACCESS_MODE(p_timings->write_access_mode));
  ASSERT_DBG_PARAM(IS_SRAM_ACCESS_MODE(p_timings->read_access_mode));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_timings == NULL) || (clk_freq_hz == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t addr_setup_tmp = FMC_ConvertNanosecondsToClockCycle(p_timings->async_access_timings.addr_setup_nsec,
                                                               clk_freq_hz);
  uint32_t addr_hold_tmp  = FMC_ConvertNanosecondsToClockCycle(p_timings->async_access_timings.addr_hold_nsec,
                                                               clk_freq_hz);
  uint32_t data_setup_tmp = FMC_ConvertNanosecondsToClockCycle(p_timings->async_access_timings.data_setup_nsec,
                                                               clk_freq_hz);
  uint32_t bus_turnaround_tmp = FMC_ConvertNanosecondsToClockCycle(p_timings->bus_turnaround_nsec, clk_freq_hz);

  ASSERT_DBG_PARAM(IS_FMC_ADDR_SETUP_TIME(addr_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_HOLD_TIME(addr_hold_tmp));
  ASSERT_DBG_PARAM(IS_FMC_DATASETUP_TIME(data_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_TURNAROUND_TIME(bus_turnaround_tmp));

  ASSERT_DBG_STATE(hsram->global_state, (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED);

  /* Set timing mask values */
  wr_timing_mask = addr_setup_tmp | FMC_WRITE_FIELD(addr_hold_tmp, FMC_BWTRx_ADDHLD_Msk, FMC_BWTRx_ADDHLD_Pos)
                   | FMC_WRITE_FIELD(data_setup_tmp, FMC_BWTRx_DATAST_Msk, FMC_BWTRx_DATAST_Pos)
                   | FMC_WRITE_FIELD((bus_turnaround_tmp - 1U), FMC_BWTRx_BUSTURN_Msk, FMC_BWTRx_BUSTURN_Pos)
                   | (uint32_t)p_timings->write_access_mode;

  rd_access_mode_mask = (uint32_t)p_timings->read_access_mode;

  FMC_Disable();

  FMC_NOR_SRAM_SetWrTiming(SRAM_GET_INSTANCE(hsram), rd_access_mode_mask, wr_timing_mask);

  FMC_Enable();

  return HAL_OK;
}

/**
  * @brief Retrieve the timing configuration for asynchronous write transactions.
  * @param hsram     Pointer to a @ref hal_sram_handle_t structure.
  * @param p_timings Pointer to a @ref hal_sram_wr_async_timings_t structure.
  * @note  If all retrieved timing parameters are zero, check the clock frequency settings to ensure they are
  *        properly set.
  */
void HAL_SRAM_GetWrAsyncTimings(const hal_sram_handle_t *hsram, hal_sram_wr_async_timings_t *p_timings)
{
  uint32_t rd_access_mode;
  uint32_t wr_timing_cfg;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hsram     != NULL);
  ASSERT_DBG_PARAM(p_timings != NULL);

  ASSERT_DBG_STATE(hsram->global_state, (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_SRAM_STATE_IDLE);

  /* Get timings configuration */
  FMC_NOR_SRAM_GetWrTiming(SRAM_GET_INSTANCE(hsram), &rd_access_mode, &wr_timing_cfg);

  p_timings->async_access_timings.addr_setup_nsec = FMC_ConvertClockCycleToNanoseconds(STM32_READ_BIT(wr_timing_cfg,
                                                    FMC_BWTRx_ADDSET), clk_freq_hz);

  p_timings->async_access_timings.addr_hold_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(wr_timing_cfg,
                                                   FMC_BWTRx_ADDHLD_Msk, FMC_BWTRx_ADDHLD_Pos), clk_freq_hz);

  p_timings->async_access_timings.data_setup_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(wr_timing_cfg,
                                                    FMC_BWTRx_DATAST_Msk, FMC_BWTRx_DATAST_Pos), clk_freq_hz);

  p_timings->bus_turnaround_nsec = FMC_ConvertClockCycleToNanoseconds
                                   ((FMC_READ_FIELD(wr_timing_cfg, FMC_BWTRx_BUSTURN_Msk, FMC_BWTRx_BUSTURN_Pos) + 1U),
                                    clk_freq_hz);

  p_timings->read_access_mode = (hal_sram_access_mode_t)rd_access_mode;

  p_timings->write_access_mode = (hal_sram_access_mode_t)(uint32_t)STM32_READ_BIT(wr_timing_cfg, FMC_BWTRx_ACCMOD);
}

/**
  * @brief   Set the memory configuration for memories with synchronous read and synchronous write access mode.
  * @param   hsram             Pointer to a @ref hal_sram_handle_t structure.
  * @param   p_config          Pointer to a @ref hal_sram_rd_wr_sync_memory_config_t structure.
  * @warning The first use of this API must be done after calling HAL_SRAM_SetConfig() API for PSRAM and CRAM
  *          memories then, it can be reused multi-time to adjust memory configuration when needed.
  * @retval  HAL_INVALID_PARAM The memory configuration structure pointer is NULL or the clock frequency is equal
  *                            to zero.
  * @retval  HAL_OK            The memory is successfully configured.
  */
hal_status_t HAL_SRAM_SetConfigRdWrSyncMemory(hal_sram_handle_t *hsram,
                                              const hal_sram_rd_wr_sync_memory_config_t *p_config)
{
  uint32_t control_mask;
  uint32_t timing_mask;
  uint32_t clk_period_mask;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hsram    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_SRAM_MEMORY_WIDTH(p_config->memory.data_bus_width));
  ASSERT_DBG_PARAM(IS_SRAM_PAGE_SIZE(p_config->memory.cram_page_size_byte));
  ASSERT_DBG_PARAM(IS_SRAM_MUX(p_config->memory.mux_data_addr));
  ASSERT_DBG_PARAM(IS_SRAM_SYNC_WAIT_SIGNAL(p_config->timings.sync_protocol.wait_signal_state));
  ASSERT_DBG_PARAM(IS_SRAM_CONTINOUS_CLOCK(p_config->timings.sync_protocol.continuous_clock));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_config == NULL) || (clk_freq_hz == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t clk_period_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.sync_protocol.clk_period_nsec,
                                                               clk_freq_hz);
  uint32_t bus_turnaround_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.bus_turnaround_nsec, clk_freq_hz);

  ASSERT_DBG_PARAM(IS_FMC_CLK_DIV(clk_period_tmp));
  ASSERT_DBG_PARAM(IS_FMC_TURNAROUND_TIME(bus_turnaround_tmp));

  ASSERT_DBG_STATE(hsram->global_state, (uint32_t)HAL_SRAM_STATE_CONFIGURED
                   | (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED);

  /* Set configuration mask value */
  control_mask = (uint32_t)p_config->memory.mux_data_addr | (uint32_t)p_config->memory.data_bus_width
                 | (uint32_t)p_config->memory.cram_page_size_byte
                 | (uint32_t)p_config->timings.sync_protocol.continuous_clock
                 | (uint32_t)p_config->timings.sync_protocol.wait_signal_state
                 | FMC_BCRx_BURSTEN | FMC_BCRx_CBURSTRW;

  clk_period_mask = FMC_WRITE_FIELD((clk_period_tmp - 1U), FMC_BTRx_CLKDIV_Msk, FMC_BTRx_CLKDIV_Pos);

  timing_mask = FMC_BTRx_ADDSET | FMC_BTRx_ADDHLD | FMC_BTRx_DATAST
                | FMC_WRITE_FIELD((bus_turnaround_tmp - 1U), FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)
                | FMC_WRITE_FIELD((clk_period_tmp - 1U), FMC_BTRx_CLKDIV_Msk, FMC_BTRx_CLKDIV_Pos);

  FMC_Disable();

  FMC_NOR_SRAM_SetConfigMemory(SRAM_GET_INSTANCE(hsram), control_mask, timing_mask);

  FMC_NOR_SRAM_SetClock((uint32_t)p_config->timings.sync_protocol.continuous_clock, clk_period_mask);

  FMC_Enable();

  hsram->global_state = HAL_SRAM_STATE_MEMORY_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the memory configuration for memories with synchronous read and synchronous write access mode.
  * @param hsram     Pointer to a @ref hal_sram_handle_t structure.
  * @param p_config  Pointer to a @ref hal_sram_rd_wr_sync_memory_config_t structure filled with the retrieved memory
  *                  configuration.
  * @note  If all retrieved timing parameters are zero, check the clock frequency settings to ensure they are properly
  *        set.
  */
void HAL_SRAM_GetConfigRdWrSyncMemory(const hal_sram_handle_t *hsram, hal_sram_rd_wr_sync_memory_config_t *p_config)
{
  uint32_t control_cfg;
  uint32_t timing_cfg;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hsram    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hsram->global_state, (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_SRAM_STATE_IDLE);

  /* Get configuration value */
  FMC_NOR_SRAM_GetConfigMemory(SRAM_GET_INSTANCE(hsram), &control_cfg, &timing_cfg);

  p_config->memory.data_bus_width = (hal_sram_data_bus_width_t)(uint32_t)STM32_READ_BIT(control_cfg, FMC_BCRx_MWID);
  p_config->memory.cram_page_size_byte   = (hal_sram_cram_page_size_t)(uint32_t)STM32_READ_BIT(control_cfg,
                                           FMC_BCRx_CPSIZE);
  p_config->memory.mux_data_addr         = (hal_sram_mux_data_addr_state_t)(uint32_t)STM32_READ_BIT(control_cfg,
                                           FMC_BCRx_MUXEN);

  p_config->timings.sync_protocol.wait_signal_state = (hal_sram_sync_wait_signal_state_t)
                                                      (uint32_t)STM32_READ_BIT(control_cfg, FMC_BCRx_WAITEN);

  p_config->timings.sync_protocol.continuous_clock = (hal_sram_continuous_clock_t)(uint32_t)STM32_READ_BIT(control_cfg,
                                                     FMC_BCR1_CCLKEN);

  p_config->timings.sync_protocol.clk_period_nsec = FMC_ConvertClockCycleToNanoseconds((FMC_READ_FIELD(timing_cfg,
                                                    FMC_BTRx_CLKDIV_Msk, FMC_BTRx_CLKDIV_Pos) + 1U), clk_freq_hz);

  p_config->timings.bus_turnaround_nsec = FMC_ConvertClockCycleToNanoseconds
                                          ((FMC_READ_FIELD(timing_cfg, FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)
                                            + 1U), clk_freq_hz);
}

/**
  * @brief   Set the memory configuration for memories with synchronous read and asynchronous write access mode.
  * @param   hsram             Pointer to a @ref hal_sram_handle_t structure.
  * @param   p_config          Pointer to a @ref hal_sram_rd_sync_wr_async_memory_config_t structure.
  * @warning The first use of this API must be done after calling HAL_SRAM_SetConfig() API for PSRAM and CRAM
  *          memories then, it can be reused multi-time to adjust memory configuration when needed.
  * @retval  HAL_INVALID_PARAM The memory configuration structure pointer is NULL or the clock frequency is equal
  *                            to zero.
  * @retval  HAL_OK            The memory is successfully configured.
  */
hal_status_t HAL_SRAM_SetConfigRdSyncWrAsyncMemory(hal_sram_handle_t *hsram,
                                                   const hal_sram_rd_sync_wr_async_memory_config_t *p_config)
{
  uint32_t control_mask;
  uint32_t timing_mask;
  uint32_t clk_period_mask;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hsram    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_SRAM_MEMORY_WIDTH(p_config->memory.data_bus_width));
  ASSERT_DBG_PARAM(IS_SRAM_PAGE_SIZE(p_config->memory.cram_page_size_byte));
  ASSERT_DBG_PARAM(IS_SRAM_MUX(p_config->memory.mux_data_addr));
  ASSERT_DBG_PARAM(IS_SRAM_SYNC_WAIT_SIGNAL(p_config->timings.sync_protocol.wait_signal_state));
  ASSERT_DBG_PARAM(IS_SRAM_CONTINOUS_CLOCK(p_config->timings.sync_protocol.continuous_clock));
  ASSERT_DBG_PARAM(IS_SRAM_ASYNC_WAIT_SIGNAL(p_config->timings.async_wait));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_config == NULL) || (clk_freq_hz == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t clk_period_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.sync_protocol.clk_period_nsec,
                                                               clk_freq_hz);
  uint32_t addr_setup_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.addr_setup_nsec,
                                                               clk_freq_hz);
  uint32_t addr_hold_tmp  = FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.addr_hold_nsec,
                                                               clk_freq_hz);
  uint32_t data_setup_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.data_setup_nsec,
                                                               clk_freq_hz);
  uint32_t bus_turnaround_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.bus_turnaround_nsec, clk_freq_hz);

  ASSERT_DBG_PARAM(IS_FMC_CLK_DIV(clk_period_tmp));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_SETUP_TIME(addr_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_HOLD_TIME(addr_hold_tmp));
  ASSERT_DBG_PARAM(IS_FMC_DATASETUP_TIME(data_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_TURNAROUND_TIME(bus_turnaround_tmp));

  ASSERT_DBG_STATE(hsram->global_state, (uint32_t)HAL_SRAM_STATE_CONFIGURED
                   | (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED);

  /* Set configuration mask value */
  control_mask = (uint32_t) p_config->memory.mux_data_addr
                 | (uint32_t) p_config->memory.data_bus_width
                 | (uint32_t) p_config->memory.cram_page_size_byte
                 | (uint32_t) p_config->timings.sync_protocol.continuous_clock
                 | (uint32_t) p_config->timings.sync_protocol.wait_signal_state
                 | (uint32_t) p_config->timings.async_wait | FMC_BCRx_BURSTEN;

  clk_period_mask = FMC_WRITE_FIELD((clk_period_tmp - 1U), FMC_BTRx_CLKDIV_Msk, FMC_BTRx_CLKDIV_Pos);

  timing_mask = (addr_setup_tmp | FMC_WRITE_FIELD(addr_hold_tmp, FMC_BTRx_ADDHLD_Msk, FMC_BTRx_ADDHLD_Pos)
                 | FMC_WRITE_FIELD(data_setup_tmp, FMC_BTRx_DATAST_Msk, FMC_BTRx_DATAST_Pos)
                 | FMC_WRITE_FIELD((bus_turnaround_tmp - 1U), FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)
                 | FMC_WRITE_FIELD((clk_period_tmp - 1U), FMC_BTRx_CLKDIV_Msk, FMC_BTRx_CLKDIV_Pos)
                 | FMC_BTRx_DATLAT);

  FMC_Disable();

  FMC_NOR_SRAM_SetConfigMemory(SRAM_GET_INSTANCE(hsram), control_mask, timing_mask);

  FMC_NOR_SRAM_SetClock((uint32_t)p_config->timings.sync_protocol.continuous_clock, clk_period_mask);

  FMC_Enable();

  hsram->global_state = HAL_SRAM_STATE_MEMORY_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the memory configuration for memories with synchronous read and asynchronous write access mode.
  * @param hsram     Pointer to a @ref hal_sram_handle_t structure.
  * @param p_config  Pointer to a @ref hal_sram_rd_sync_wr_async_memory_config_t structure filled with the retrieved
  *                  memory configuration.
  * @note  If all retrieved timing parameters are zero, check the clock frequency settings to ensure they are properly
  *        set.
  */
void HAL_SRAM_GetConfigRdSyncWrAsyncMemory(const hal_sram_handle_t *hsram,
                                           hal_sram_rd_sync_wr_async_memory_config_t *p_config)
{
  uint32_t control_cfg;
  uint32_t timing_cfg;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hsram    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hsram->global_state, (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_SRAM_STATE_IDLE);

  /* Get configuration value */
  FMC_NOR_SRAM_GetConfigMemory(SRAM_GET_INSTANCE(hsram), &control_cfg, &timing_cfg);

  p_config->memory.data_bus_width = (hal_sram_data_bus_width_t)(uint32_t)STM32_READ_BIT(control_cfg, FMC_BCRx_MWID);
  p_config->memory.cram_page_size_byte   = (hal_sram_cram_page_size_t)(uint32_t)STM32_READ_BIT(control_cfg,
                                           FMC_BCRx_CPSIZE);
  p_config->memory.mux_data_addr         = (hal_sram_mux_data_addr_state_t)(uint32_t)STM32_READ_BIT(control_cfg,
                                           FMC_BCRx_MUXEN);

  p_config->timings.sync_protocol.wait_signal_state = (hal_sram_sync_wait_signal_state_t)
                                                      (uint32_t)STM32_READ_BIT(control_cfg, FMC_BCRx_WAITEN);

  p_config->timings.sync_protocol.continuous_clock = (hal_sram_continuous_clock_t)(uint32_t)STM32_READ_BIT(control_cfg,
                                                     FMC_BCR1_CCLKEN);

  p_config->timings.sync_protocol.clk_period_nsec = FMC_ConvertClockCycleToNanoseconds
                                                    ((FMC_READ_FIELD(timing_cfg, FMC_BTRx_CLKDIV_Msk,
                                                                     FMC_BTRx_CLKDIV_Pos) + 1U), clk_freq_hz);
  p_config->timings.async_wait = (hal_sram_async_wait_signal_state_t)(uint32_t)STM32_READ_BIT(control_cfg,
                                 FMC_BCRx_ASYNCWAIT);

  p_config->timings.async_access_timings.addr_setup_nsec = FMC_ConvertClockCycleToNanoseconds(STM32_READ_BIT(timing_cfg,
                                                           FMC_BTRx_ADDSET), clk_freq_hz);

  p_config->timings.async_access_timings.addr_hold_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                          FMC_BTRx_ADDHLD_Msk, FMC_BTRx_ADDHLD_Pos), clk_freq_hz);

  p_config->timings.async_access_timings.data_setup_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                           FMC_BTRx_DATAST_Msk, FMC_BTRx_DATAST_Pos), clk_freq_hz);


  p_config->timings.bus_turnaround_nsec = FMC_ConvertClockCycleToNanoseconds
                                          ((FMC_READ_FIELD(timing_cfg, FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)
                                            + 1U), clk_freq_hz);
}

/**
  * @brief   Set the memory configuration for memories with asynchronous read and synchronous write access mode.
  * @param   hsram             Pointer to a @ref hal_sram_handle_t structure.
  * @param   p_config          Pointer to a @ref hal_sram_rd_async_wr_sync_memory_config_t structure.
  * @warning The first use of this API must be done after calling HAL_SRAM_SetConfig() API for PSRAM and CRAM
  *          memories then, it can be reused multi-time to adjust memory configuration when needed.
  * @retval  HAL_INVALID_PARAM The memory configuration structure pointer is NULL or the clock frequency is equal
  *                            to zero.
  * @retval  HAL_OK            The memory is successfully configured.
  */
hal_status_t HAL_SRAM_SetConfigRdAsyncWrSyncMemory(hal_sram_handle_t *hsram,
                                                   const hal_sram_rd_async_wr_sync_memory_config_t *p_config)
{
  uint32_t control_mask;
  uint32_t timing_mask;
  uint32_t clk_period_mask;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hsram    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_SRAM_MEMORY_WIDTH(p_config->memory.data_bus_width));
  ASSERT_DBG_PARAM(IS_SRAM_PAGE_SIZE(p_config->memory.cram_page_size_byte));
  ASSERT_DBG_PARAM(IS_SRAM_MUX(p_config->memory.mux_data_addr));
  ASSERT_DBG_PARAM(IS_SRAM_SYNC_WAIT_SIGNAL(p_config->timings.sync_protocol.wait_signal_state));
  ASSERT_DBG_PARAM(IS_SRAM_CONTINOUS_CLOCK(p_config->timings.sync_protocol.continuous_clock));
  ASSERT_DBG_PARAM(IS_SRAM_ASYNC_WAIT_SIGNAL(p_config->timings.async_wait));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_config == NULL) || (clk_freq_hz == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t clk_period_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.sync_protocol.clk_period_nsec,
                                                               clk_freq_hz);
  uint32_t addr_setup_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.addr_setup_nsec,
                                                               clk_freq_hz);
  uint32_t addr_hold_tmp  = FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.addr_hold_nsec,
                                                               clk_freq_hz);
  uint32_t data_setup_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.async_access_timings.data_setup_nsec,
                                                               clk_freq_hz);
  uint32_t bus_turnaround_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->timings.bus_turnaround_nsec, clk_freq_hz);

  ASSERT_DBG_PARAM(IS_FMC_CLK_DIV(clk_period_tmp));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_SETUP_TIME(addr_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_ADDR_HOLD_TIME(addr_hold_tmp));
  ASSERT_DBG_PARAM(IS_FMC_DATASETUP_TIME(data_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_TURNAROUND_TIME(bus_turnaround_tmp));

  ASSERT_DBG_STATE(hsram->global_state, (uint32_t)HAL_SRAM_STATE_CONFIGURED
                   | (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED);

  /* Set configuration mask values */
  control_mask = (uint32_t)p_config->memory.mux_data_addr
                 | (uint32_t)p_config->memory.data_bus_width
                 | (uint32_t)p_config->memory.cram_page_size_byte
                 | (uint32_t)p_config->timings.sync_protocol.continuous_clock
                 | (uint32_t)p_config->timings.sync_protocol.wait_signal_state
                 | (uint32_t)p_config->timings.async_wait | FMC_BCRx_CBURSTRW;

  clk_period_mask = FMC_WRITE_FIELD((clk_period_tmp - 1U), FMC_BTRx_CLKDIV_Msk, FMC_BTRx_CLKDIV_Pos);

  timing_mask = (addr_setup_tmp | FMC_WRITE_FIELD(addr_hold_tmp, FMC_BTRx_ADDHLD_Msk, FMC_BTRx_ADDHLD_Pos)
                 | FMC_WRITE_FIELD(data_setup_tmp, FMC_BTRx_DATAST_Msk, FMC_BTRx_DATAST_Pos)
                 | FMC_WRITE_FIELD((bus_turnaround_tmp - 1U), FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)
                 | FMC_WRITE_FIELD((clk_period_tmp - 1U), FMC_BTRx_CLKDIV_Msk, FMC_BTRx_CLKDIV_Pos)
                 | FMC_BTRx_DATLAT);

  FMC_Disable();

  FMC_NOR_SRAM_SetConfigMemory(SRAM_GET_INSTANCE(hsram), control_mask, timing_mask);

  FMC_NOR_SRAM_SetClock((uint32_t)p_config->timings.sync_protocol.continuous_clock, clk_period_mask);

  FMC_Enable();

  hsram->global_state = HAL_SRAM_STATE_MEMORY_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the memory configuration for memories with asynchronous read and synchronous write access mode.
  * @param hsram     Pointer to a @ref hal_sram_handle_t structure.
  * @param p_config  Pointer to a @ref hal_sram_rd_async_wr_sync_memory_config_t structure filled with the retrieved
  *                  memory configuration.
  * @note  If all retrieved timing parameters are zero, check the clock frequency settings to ensure they are properly
  *        set.
  */
void HAL_SRAM_GetConfigRdAsyncWrSyncMemory(const hal_sram_handle_t *hsram,
                                           hal_sram_rd_async_wr_sync_memory_config_t *p_config)
{
  uint32_t control_cfg;
  uint32_t timing_cfg;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hsram    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hsram->global_state, (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_SRAM_STATE_IDLE);

  /* Get configuration value */
  FMC_NOR_SRAM_GetConfigMemory(SRAM_GET_INSTANCE(hsram), &control_cfg, &timing_cfg);

  p_config->memory.data_bus_width = (hal_sram_data_bus_width_t)(uint32_t)STM32_READ_BIT(control_cfg, FMC_BCRx_MWID);
  p_config->memory.cram_page_size_byte   = (hal_sram_cram_page_size_t)(uint32_t)STM32_READ_BIT(control_cfg,
                                           FMC_BCRx_CPSIZE);
  p_config->memory.mux_data_addr         = (hal_sram_mux_data_addr_state_t)(uint32_t)STM32_READ_BIT(control_cfg,
                                           FMC_BCRx_MUXEN);

  p_config->timings.sync_protocol.wait_signal_state = (hal_sram_sync_wait_signal_state_t)
                                                      (uint32_t)STM32_READ_BIT(control_cfg, FMC_BCRx_WAITEN);

  p_config->timings.sync_protocol.continuous_clock = (hal_sram_continuous_clock_t)(uint32_t)STM32_READ_BIT(control_cfg,
                                                     FMC_BCR1_CCLKEN);

  p_config->timings.sync_protocol.clk_period_nsec = FMC_ConvertClockCycleToNanoseconds((FMC_READ_FIELD(timing_cfg,
                                                    FMC_BTRx_CLKDIV_Msk, FMC_BTRx_CLKDIV_Pos) + 1U), clk_freq_hz);

  p_config->timings.async_wait =
    (hal_sram_async_wait_signal_state_t)(uint32_t)STM32_READ_BIT(control_cfg, FMC_BCRx_ASYNCWAIT);

  p_config->timings.async_access_timings.data_setup_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                           FMC_BTRx_DATAST_Msk, FMC_BTRx_DATAST_Pos), clk_freq_hz);


  p_config->timings.async_access_timings.addr_setup_nsec = FMC_ConvertClockCycleToNanoseconds(STM32_READ_BIT(timing_cfg,
                                                           FMC_BTRx_ADDSET), clk_freq_hz);

  p_config->timings.async_access_timings.addr_hold_nsec = FMC_ConvertClockCycleToNanoseconds(FMC_READ_FIELD(timing_cfg,
                                                          FMC_BTRx_ADDHLD_Msk, FMC_BTRx_ADDHLD_Pos), clk_freq_hz);

  p_config->timings.bus_turnaround_nsec = FMC_ConvertClockCycleToNanoseconds
                                          ((FMC_READ_FIELD(timing_cfg, FMC_BTRx_BUSTURN_Msk, FMC_BTRx_BUSTURN_Pos)
                                            + 1U), clk_freq_hz);
}

/**
  * @brief   Enable the corresponding SRAM device.
  * @param   hsram  Pointer to a @ref hal_sram_handle_t structure.
  * @warning This API can be used once the SRAM is fully configured.
  * @retval  HAL_OK The SRAM is successfully enabled.
  */
hal_status_t HAL_SRAM_EnableMemory(hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);

  ASSERT_DBG_STATE(hsram->global_state, HAL_SRAM_STATE_MEMORY_CONFIGURED);

  FMC_NOR_SRAM_Enable(SRAM_GET_INSTANCE(hsram));

  hsram->global_state = HAL_SRAM_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief   Disable the corresponding SRAM device.
  * @param   hsram  Pointer to a @ref hal_sram_handle_t structure.
  * @warning This API must be called when a memory configuration adjustment is needed
  *          or to save power. The HAL_SRAM_EnableMemory() must be recalled to enable
  *          the memory and make it accessible.
  * @retval  HAL_OK The SRAM is successfully disabled.
  */
hal_status_t HAL_SRAM_DisableMemory(hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);

  ASSERT_DBG_STATE(hsram->global_state, HAL_SRAM_STATE_IDLE);

  FMC_NOR_SRAM_Disable(SRAM_GET_INSTANCE(hsram));

  hsram->global_state = HAL_SRAM_STATE_MEMORY_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief  Retrieve the current base address of the SRAM memory region.
  * @param  hsram    Pointer to a @ref hal_sram_handle_t structure.
  * @return uint32_t Base address of the SRAM memory region.
  */
uint32_t HAL_SRAM_GetRegionBaseAddress(const hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);

  ASSERT_DBG_STATE(hsram->global_state, ((uint32_t)HAL_SRAM_STATE_INIT
                                         | (uint32_t)HAL_SRAM_STATE_CONFIGURED
                                         | (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED
                                         | (uint32_t)HAL_SRAM_STATE_IDLE));

  STM32_UNUSED(hsram);

  return FMC_NOR_SRAM_GetRegionBaseAddress();
}
/**
  * @}
  */

/** @addtogroup SRAM_Exported_Functions_Group3
  * @{
This subsection provides a set of functions allowing to control the SRAM device :

- HAL_SRAM_EnableWriteProtection()    : used to enable the write protection of the corresponding SRAM device.
- HAL_SRAM_DisableWriteProtection()   : used to disable the write protection of the corresponding SRAM device.
- HAL_SRAM_IsEnabledWriteProtection() : used to get the corresponding SRAM device write protection status.
  */

/**
  * @brief   Enable the corresponding SRAM device write protection.
  * @param   hsram  Pointer to a @ref hal_sram_handle_t structure.
  * @warning This API can be used once the SRAM is fully configured and ready to use.
  * @retval  HAL_OK The write protection is successfully enabled.
  */
hal_status_t HAL_SRAM_EnableWriteProtection(hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);

  ASSERT_DBG_STATE(hsram->global_state, HAL_SRAM_STATE_IDLE);

  FMC_NOR_SRAM_EnableWriteProtection(SRAM_GET_INSTANCE(hsram));

  hsram->wr_protection_status = HAL_SRAM_WR_PROTECTION_ENABLED;

  return HAL_OK;
}

/**
  * @brief   Disable the corresponding SRAM device write protection.
  * @param   hsram  Pointer to a @ref hal_sram_handle_t structure.
  * @warning This API can be used once the SRAM is fully configured and ready to use.
  * @retval  HAL_OK The write protection is successfully disabled.
  */
hal_status_t HAL_SRAM_DisableWriteProtection(hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);

  ASSERT_DBG_STATE(hsram->global_state, HAL_SRAM_STATE_IDLE);

  FMC_NOR_SRAM_DisableWriteProtection(SRAM_GET_INSTANCE(hsram));

  hsram->wr_protection_status = HAL_SRAM_WR_PROTECTION_DISABLED;

  return HAL_OK;
}

/**
  * @brief  Get the corresponding SRAM device write protection status.
  * @param  hsram                           Pointer to a @ref hal_sram_handle_t structure.
  * @retval HAL_SRAM_WR_PROTECTION_DISABLED The SRAM write protection is disabled.
  * @retval HAL_SRAM_WR_PROTECTION_ENABLED  The SRAM write protection is enabled.
  */
hal_sram_wr_protection_status_t HAL_SRAM_IsEnabledWriteProtection(const hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);

  ASSERT_DBG_STATE(hsram->global_state, ((uint32_t)HAL_SRAM_STATE_INIT
                                         | (uint32_t)HAL_SRAM_STATE_CONFIGURED
                                         | (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED
                                         | (uint32_t)HAL_SRAM_STATE_IDLE));

  return ((hal_sram_wr_protection_status_t)(uint32_t)FMC_NOR_SRAM_IsEnabledWriteProtection(SRAM_GET_INSTANCE(hsram)));
}
/**
  * @}
  */

#if defined(USE_HAL_SRAM_USER_DATA) && (USE_HAL_SRAM_USER_DATA == 1U)

/** @addtogroup SRAM_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to set and retrieve user specific data :
- The HAL_SRAM_SetUserData() API : used to store user data pointer into the handle.
- The HAL_SRAM_GetUserData() API : used to retrieve user data pointer from the handle.
  */

/**
  * @brief Store user data pointer into the handle.
  * @param hsram       Pointer to a @ref hal_sram_handle_t structure.
  * @param p_user_data Pointer to the user data.
  */
void HAL_SRAM_SetUserData(hal_sram_handle_t *hsram, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hsram != NULL);

  hsram->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve user data pointer from the handle.
  * @param  hsram Pointer to a @ref hal_sram_handle_t structure.
  * @retval Pointer to the user data.
  */
const void *HAL_SRAM_GetUserData(const hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);

  return (hsram->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_SRAM_USER_DATA */

/** @addtogroup SRAM_Exported_Functions_Group5
  * @{
This subsection provides a set of functions allowing to retrieve the SRAM global state and the clock frequency :
- HAL_SRAM_GetClockFreq() : used to retrieve clock frequency.
- HAL_SRAM_GetState()     : used to retrieve current global state.
  */

/**
  * @brief  Get the clock frequency.
  * @param  hsram    Pointer to a @ref hal_sram_handle_t structure.
  * @retval uint32_t Frequency in Hz. (0: Frequency not calculated)
  */
uint32_t HAL_SRAM_GetClockFreq(const hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM((hsram != NULL));
  ASSERT_DBG_STATE(hsram->global_state, ((uint32_t)HAL_SRAM_STATE_CONFIGURED
                                         | (uint32_t)HAL_SRAM_STATE_MEMORY_CONFIGURED
                                         | (uint32_t)HAL_SRAM_STATE_IDLE));
  STM32_UNUSED(hsram);

  return HAL_RCC_FMC_GetKernelClkFreq();
}

/**
  * @brief  Get the current global state.
  * @param  hsram                            Pointer to a @ref hal_sram_handle_t structure.
  * @retval HAL_SRAM_STATE_RESET             The SRAM not yet initialized.
  * @retval HAL_SRAM_STATE_INIT              The SRAM initialized but not yet configured.
  * @retval HAL_SRAM_STATE_CONFIGURED        The SRAM initialized, FMC peripheral configured but not yet ready to use.
  * @retval HAL_SRAM_STATE_MEMORY_CONFIGURED The SRAM initialized, FMC, memory configured but not yet ready to use.
  * @retval HAL_SRAM_STATE_IDLE              The SRAM initialized, FMC, memory configured, SRAM is enabled and ready to
                                             use.
  */
hal_sram_state_t HAL_SRAM_GetState(const hal_sram_handle_t *hsram)
{
  ASSERT_DBG_PARAM(hsram != NULL);

  return hsram->global_state;
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
#endif /* USE_HAL_SRAM_MODULE */
#endif /* defined(FMC_NORSRAM_BK1) */
/**
  * @}
  */
