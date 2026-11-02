/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_nand.c
  * @brief   NAND HAL module driver.
  *          This file provides a generic firmware to drive NAND memories mounted as external device.
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
#if defined (FMC_NAND_BK)
#if defined(USE_HAL_NAND_MODULE) && (USE_HAL_NAND_MODULE == 1U)

/** @addtogroup NAND
  * @{
  */
/** @defgroup NAND_Introduction NAND Introduction
  * @{

  - The NAND hardware abstraction layer provides a set of APIs to interface with NAND flash memory devices
    via the STM32 Flexible Memory Controller (FMC) peripheral.

  - The NAND HAL driver streamlines common memory operations, such as read and program accesses,
    by handling peripheral initialization, configuration, command sequencing, and data transfers.

  - This abstraction layer ensures portability and ease of use across different STM32 series.

  */
/**
  * @}
  */

/** @defgroup NAND_How_To_Use NAND How To Use
  * @{

# How to use the NAND HAL module driver

## The FMC NAND main features:

This NAND HAL driver is a generic driver which contains a set of APIs used to configure the FMC NAND banks and to
interface with legacy and ONFI (Open NAND Flash Interface) NAND memories.

## The NAND HAL driver can be used as follows:

This module provides these different sets of APIs that allow to :

1- Initialize and deinitialize the logical FMC NAND object ( @ref hal_nand_handle_t) and retrieve the associated
   NAND peripheral instance :
  - Initialize the logical FMC NAND object and associate it to a physical instance.
    This functionality is ensured by HAL_NAND_Init() function.
  - Deinitialize the logical FMC NAND object and disable the NAND bank.
    This functionality is ensured by HAL_NAND_DeInit() function.
  - Retrieve the NAND instance by calling HAL_NAND_GetInstance().

2- Configure the FMC NAND to be ready to use and retrieve the current configuration :

  - Configure the FMC NAND through these steps by following the order below :

    - Step 1 (FMC configuration) : is the first step to perform once the HAL NAND driver is initialized.
      This functionality is ensured by HAL_NAND_SetConfig() function.

      At this stage, the NAND is partially configured but not yet ready to use.

    - Step 2 (Memory configuration) : is the second step to perform once the FMC is configured.
      This functionality is ensured by HAL_NAND_SetConfigMemory() function.

    - Step 3 (Optional based on the external memory) : is the third step to perform optionally once the FMC and
      memory are configured. It sets a different timing configuration for the last write access when needed.
      This functionality is ensured by HAL_NAND_SetLastWriteAccessTiming() function, and it must be called after
      HAL_NAND_SetConfigMemory().

      At this stage, the memory is partially configured but not ready to use.

    - Step 4 (Partition configuration) : is the fourth step to perform once the FMC and memory are configured.
      This functionality is ensured by one of these two functions :
       - HAL_NAND_SetConfigPartition() function to set the NAND memory partition configuration.
       - HAL_NAND_SetConfigPartitionONFI() function to retrieve automatically and set the NAND partition configuration
         from the ONFI compliant memory.

      At this stage, the memory is fully configured and ready to use for polling process.

    For polling process, the timeout values can be modified when the memory is fully configured.
      This functionality is ensured by these functions :
        - HAL_NAND_SetExtraCmdTimeout() function to update the extra command timeout.
        - HAL_NAND_SetPageProgramTimeout() function to update the page program timeout.
        - HAL_NAND_SetBlockEraseTimeout() function to update the block erase timeout.

  - Retrieve the current configuration through the following functions :

    - Retrieve the FMC configuration :
      This functionality is ensured by HAL_NAND_GetConfig().
    - Retrieve the memory configuration :
      This functionality is ensured by HAL_NAND_GetConfigMemory().
    - Retrieve the timing configuration for the last write access :
      This functionality is ensured by HAL_NAND_GetLastWriteAccessTiming()
    - Retrieve the memory partition configuration :
       This functionality is ensured by HAL_NAND_GetConfigPartition().
    - Retrieve the NAND start region address :
       This functionality is ensured by HAL_NAND_GetRegionBaseAddress().
    - Retrieve the process timeout values :
      This functionality is ensured by these 3 functions depending on the process :
       - HAL_NAND_GetExtraCmdTimeout() function to get the extra command timeout.
       - HAL_NAND_GetPageProgramTimeout() function to get page program timeout.
       - HAL_NAND_GetBlockEraseTimeout() function to get block erase timeout.
    - Retrieve the algorithm used for the ECC computation :
       This functionality is ensured by HAL_NAND_ECC_GetAlgo().

3- Interface with legacy and ONFI NAND memories by controlling the input and output access operations.

- Blocking mode :

  This functionality is ensured by these polling functions :
    - HAL_NAND_Reset() function to reset the NAND memory.
    - HAL_NAND_ReadID() function to read the NAND device identifier.
    - HAL_NAND_ONFIDetect() function to check whether the NAND memory is ONFI compliant.
    - HAL_NAND_ONFIReadParameterPage() function to read data structure describing the device's organization, features,
      timings and other behavioral parameters.
    - HAL_NAND_ReadPage() function to read a page from NAND memory data area.
    - HAL_NAND_ProgramPage() function to program a page in the NAND flash data area.
    - HAL_NAND_ReadPageSpareArea() function to read the NAND memory spare area.
    - HAL_NAND_ProgramPageSpareArea() function to program the NAND memory spare area.
    - HAL_NAND_EraseBlock() function to erase a specified block of the NAND flash memory.
    - HAL_NAND_ReadStatus() function to read the NAND flash operation status.
    - HAL_NAND_ReadInPage() function to read data starting at a specified column offset within the selected page.
    - HAL_NAND_ProgramInPage() function to program data starting at a specified column offset within the selected page.
    - HAL_NAND_CopyBackRead() function to read data from source location and copy it temporarily in the NAND memory's
      internal buffer.
    - HAL_NAND_CopyBackProgram() function to copy the data held in the NAND internal buffer to a new destination
      location.
    - HAL_NAND_ECC_ProgramPage() function to program a page in the NAND flash data area with chunk-by-chunk
      ECC computation and to store the resulting parity bits in the spare area.
    - HAL_NAND_ECC_ReadPage() function to read a page from the NAND flash data area with chunk-by-chunk ECC computation
      and to correct errors using the stored parity bits.
    - HAL_NAND_ECC_GetErrors() function to retrieve the positions where errors are detected during a read operation.

- Non-blocking mode :

  The NAND driver provides also control over input and output operations of both ONFI and legacy compliant NAND memories
  in non-blocking mode.

    Send only the read and program commands then it is up to the application to handle data transmit and receive.
    This functionality is ensured by these functions :
      - HAL_NAND_SendReadPageCmd() function to send the read page command.
      - HAL_NAND_EndReadPage() function to finalize the read page process.
      - HAL_NAND_SendProgramPageCmd() function to send program page command.
      - HAL_NAND_EndProgramPage() function to finalize the program page process.


4- Manage the FMC NAND peripheral access when it is fully configured :
   This functionality is ensured by these functions :

  - HAL_NAND_Enable() function to enable the FMC NAND bank (when disabled).
  - HAL_NAND_Disable() function to disable the FMC NAND bank (when enabled).
  - HAL_NAND_IsEnabled() function to retrieve the FMC NAND bank status.

5- Store and retrieve user data :
   This functionality is ensured by these functions :
  - HAL_NAND_SetUserData() function to store user data pointer into the handle.
  - HAL_NAND_GetUserData() function to retrieve user data pointer from the handle.

6- Retrieve the global state, the kernel clock frequency and the NAND instance :
   This functionality is ensured by these functions :
  - HAL_NAND_GetState() function to retrieve the global state.
  - HAL_NAND_GetClockFreq() function to retrieve the clock frequency.

  */
/**
  * @}
  */

/** @defgroup NAND_Configuration_Table NAND Configuration Table
  * @{
## Configuration inside the NAND driver
Config defines               | Description     | Default value     | Note
-----------------------------| --------------- | ----------------- | ---------------------------------------------------
USE_ASSERT_DBG_PARAM         | from IDE        |      None         | Allows to use the assert check parameters.
USE_ASSERT_DBG_STATE         | from IDE        |      None         | Allows to use the assert check states.
USE_HAL_CHECK_PARAM          | from hal_conf.h |        0          | Allows to use the run-time check parameters.
USE_HAL_NAND_MODULE          | from hal_conf.h |        1          | Allows to use the HAL NAND module.
USE_FMC_CLK_ENABLE_MODEL     | from hal_conf.h | HAL_CLK_ENABLE_NO | Allows to enable the FMC clock.
USE_HAL_NAND_USER_DATA       | from hal_conf.h |        0          | Allows to use user data.
USE_HAL_NAND_ECC             | from hal_conf.h |        1          | Allows to use the FMC ECC mechanism computation.
USE_HAL_NAND_EXTRA_CMD       | from hal_conf.h |        1          | Allows to use the extra command for read operation.
  */
/**
  * @}
  */

/* Private constant --------------------------------------------------------------------------------------------------*/
/** @defgroup NAND_Private_Constants NAND Private Constants
  * @{
  */
#define NAND_OPT_DMA_SHIFT                 (16U)                /*!< Optional interruptions literals
                                                                     HAL_NAND_OPT_DMA_x bitfield shift for
                                                                     compliance with literals HAL_NAND_OPT_IT_x      */
#define NAND_CYCLE_DIVIDER                 (216U)               /*!< Divider to scale SYSCLK for NAND
                                                                     polling timing                                  */

#define NAND_ONFI_TAG                      (0x49464E4FU)        /*!< NAND ONFI tag: ASCII "ONFI"                     */
#if defined(USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
#define NAND_HAMMING_TIMEOUT_MSEC          (0x01000000UL)       /*!< Nand hamming timeout in milliseconds            */
#define NAND_ECC_HAMMING_BASE_LENGTH       (22U)                /*!< Nand Hamming base length                        */
#define NAND_ECC_HAMMING_SIZE_BYTE         (4U)                 /*!< Nand Hamming size in bytes                      */
#define NAND_ECC_MAX_VALUE                 (1U)                 /*!< Nand maximum ECC value                          */
#endif /* USE_HAL_NAND_ECC */
#define NAND_PAGE_START_OFFSET             (0x0U)               /*!< NAND page start offset                          */
/* ONFI parameter page dummy / reserved regions */
#define NAND_ONFI_RESERVED_PARTITION_START_LEN_BYTES           (80U) /*!< region reserved before partition page
                                                                          fields                                     */
#define NAND_ONFI_RESERVED_PARTITION_BEFORE_PAGE_NBR_LEN_BYTES (6U)  /*!< region reserved before page_nbr_per_block  */
#define NAND_ONFI_RESERVED1_LEN_BYTES                          (22U) /*!< region reserved before manufacturer        */
#define NAND_ONFI_RESERVED2_LEN_BYTES                          (15U) /*!< region reserved before page_size           */
#define NAND_ONFI_RESERVED3_LEN_BYTES                          (6U)  /*!< region reserved before page_nbr_per_block  */
#define NAND_ONFI_RESERVED4_LEN_BYTES                          (1U)  /*!< region reserved after program_page_nbr     */
#define NAND_ONFI_RESERVED5_LEN_BYTES                          (14U) /*!< region reserved before SDR timing          */
#define NAND_ONFI_RESERVED6_LEN_BYTES                          (20U) /*!< region reserved before driver strength     */
#define NAND_ONFI_RESERVED7_LEN_BYTES                          (7U)  /*!< region reserved before warmup_cycles       */
#define NAND_ONFI_RESERVED8_LEN_BYTES                          (4U)  /*!< region reserved before vendor_revision     */
#define NAND_ONFI_RESERVED9_LEN_BYTES                          (88U) /*!< vendor-specific area reserved before CRC   */
#define NAND_ONFI_RESERVED10_LEN_BYTES                         (1U)  /*!< region reserved instead of JEDEC ID when
                                                                          length equal to zero                       */
/**
  * @}
  */

/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup NAND_Private_Macros NAND Private Macros
  * @{
  */
/*! Check the wait feature parameter */
#define IS_NAND_WAIT_FEATURE(wait) (((wait) == HAL_NAND_WAIT_FEATURE_DISABLED) \
                                    || ((wait) == HAL_NAND_WAIT_FEATURE_ENABLED))

/*! Check the data width parameter */
#define IS_NAND_DATA_WIDTH(width) (((width) == HAL_NAND_DATA_BUS_WIDTH_8_BIT) \
                                   || ((width) == HAL_NAND_DATA_BUS_WIDTH_16_BIT))

#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
/*! Check the ECC algorithm parameter */
#define IS_NAND_ECC_ALGORITHM(algorithm) (((algorithm) == HAL_NAND_ECC_ALGO_NONE) \
                                          || ((algorithm) == HAL_NAND_ECC_ALGO_HAMMING))

/*! Check the chunk size parameter */
#define IS_NAND_CHUNK_SIZE(size) (((size) == HAL_NAND_CHUNK_SIZE_256_BYTE)     \
                                  || ((size) == HAL_NAND_CHUNK_SIZE_512_BYTE)  \
                                  || ((size) == HAL_NAND_CHUNK_SIZE_1024_BYTE) \
                                  || ((size) == HAL_NAND_CHUNK_SIZE_2048_BYTE) \
                                  || ((size) == HAL_NAND_CHUNK_SIZE_4096_BYTE) \
                                  || ((size) == HAL_NAND_CHUNK_SIZE_8192_BYTE))
/*! Check the ecc size byte parameter */
#define IS_NAND_ECC_SIZE_VALID(hnand, ecc_size_byte) \
  (((ecc_size_byte) != 0U) && ((ecc_size_byte) == (NAND_GetEccWordsPerChunk(hnand) * 4U * \
                                                   ((hnand)->partition_config.page_size_byte \
                                                    / (hnand)->chunk_size_byte))))
/*! Check the chunk index parameter */
#define IS_NAND_CHUNK_INDEX_VALID(hnand, chunk_index) \
  ((chunk_index) < ((hnand)->partition_config.page_size_byte / (hnand)->chunk_size_byte))
#endif /* USE_HAL_NAND_ECC */
/*! Check the page size parameter */
#define IS_NAND_PAGE_SIZE_VALID(handle, size_byte) \
  (((size_byte) != 0U) && ((size_byte) <= (handle)->partition_config.page_size_byte))

/*! Check the page index parameter */
#define IS_NAND_PAGE_INDEX_VALID(handle, page_index) \
  ((page_index) < ((handle)->partition_config.page_nbr_per_block * (handle)->partition_config.block_nbr_per_lun * \
                   (handle)->partition_config.lun_nbr_per_device))

/*! Check the column size parameter */
#define IS_NAND_COLUMN_INDEX_VALID(handle, column_index) \
  ((column_index) < ((handle)->partition_config.page_size_byte))

/*! Check the block index parameter */
#define IS_NAND_BLOCK_INDEX_VALID(handle, block_index) \
  ((block_index) < ((handle)->partition_config.block_nbr_per_lun * (handle)->partition_config.lun_nbr_per_device))

/*! Check the spare area size parameter */
#define IS_NAND_SPARE_AREA_SIZE_VALID(handle, size_byte) \
  (((size_byte) != 0U) && ((size_byte) <= (handle)->partition_config.spare_area_size_byte))

/*! Check the partition configuration parameters */
#define IS_NAND_PARTITION_CONFIG_VALID(config) (((config)->page_size_byte != 0U)            \
                                                && ((config)->spare_area_size_byte != 0U)   \
                                                && ((config)->page_nbr_per_block != 0U)     \
                                                && ((config)->block_nbr_per_lun != 0U)      \
                                                && ((config)->lun_nbr_per_device != 0U))

/*! Check the extra command state parameter */
#define IS_NAND_EXTRA_COMMAND_STATE(state) (((state) == HAL_NAND_EXTRA_COMMAND_DISABLED) \
                                            || ((state) == HAL_NAND_EXTRA_COMMAND_ENABLED))

/*! Get the handle instance */
#define NAND_GET_INSTANCE(handle) ((FMC_NAND_TypeDef *)((uint32_t)(handle)->instance))

/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup NAND_Private_Functions NAND Private Functions
  * @{
  */
static uint32_t NAND_RowAddress(const hal_nand_handle_t *hnand, uint32_t block_index);
static void NAND_SetAddress(const hal_nand_handle_t *hnand, uint32_t row_addr, uint16_t column_addr);
static void NAND_StartReadParameterPage(const hal_nand_handle_t *hnand);
static void NAND_StartReadPage(hal_nand_handle_t *hnand, uint32_t page_index);
static void NAND_StartProgramPage(hal_nand_handle_t *hnand, uint32_t page_index);
static hal_status_t NAND_EndProgramPage(hal_nand_handle_t *hnand);
static void NAND_ChangeReadColumn(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index,
                                  uint8_t *p_data, uint32_t size_byte);
static void NAND_ChangeWriteColumn(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index,
                                   const uint8_t *p_data, uint32_t size_byte);
static hal_nand_device_status_t NAND_ReadStatus(const hal_nand_handle_t *hnand);
static hal_status_t NAND_PollForOperationStatus(const hal_nand_handle_t *hnand, uint32_t timeout_usec);
static hal_status_t NAND_PollForEraseOperationStatus(const hal_nand_handle_t *hnand, uint32_t timeout_msec);
#if defined(USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
static uint32_t NAND_GetEccWordsPerChunk(const hal_nand_handle_t *hnand);
static void NAND_ECC_ProgramChunkSpareArea(hal_nand_handle_t *hnand, uint32_t ecc_offset_byte);
static hal_status_t NAND_ECC_GetHammingErrorPositions(const hal_nand_handle_t *hnand, uint32_t ecc_program,
                                                      uint32_t ecc_read, hal_nand_ecc_error_t *p_ecc_error);
static hal_status_t NAND_ECC_GetChunkResults(hal_nand_handle_t *hnand, void *p_ecc, uint32_t ecc_offset_byte);
static hal_status_t NAND_PollForHammingStatus(hal_nand_handle_t *hnand);
#endif /* USE_HAL_NAND_ECC */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup NAND_Exported_Functions
  * @{
  */

/** @addtogroup NAND_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and de-initialize the NAND driver :
- The HAL_NAND_Init() API : allows to initialize the NAND handle and enable the peripheral clock when
  USE_FMC_CLK_ENABLE_MODEL is different from HAL_CLK_ENABLE_NO.
  In case of the USE_FMC_CLK_ENABLE_MODEL compilation is not defined or define to HAL_CLK_ENABLE_NO, the application
  needs to explicitly call the HAL RCC API in order to enable the clock of FMC controller.

- The HAL_NAND_DeInit() API : allows to de-initialize the HAL NAND driver for the given handle and
                              disable the NAND bank.
- The HAL_NAND_GetInstance(): allows to retrieve the NAND instance.
  */

/**
  * @brief  Initialize the NAND handle field and associate a physical instance.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  instance          @ref hal_nand_t enumerated type variable to be set according to the physical instance.
  * @note   The FMC clock can be activated within the HAL_NAND_Init() function by setting the USE_FMC_CLK_ENABLE_MODEL
  *         flag to HAL_CLK_ENABLE_PERIPH_ONLY in the configuration file stm32h7pxx_hal_conf.h or by explicitly
  *         calling the HAL_RCC_FMC_EnableClock() API within the application when the USE_FMC_CLK_ENABLE_MODEL is not
  *         defined or defined to flag HAL_CLK_ENABLE_NO.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the NAND handle is NULL.
  * @retval HAL_OK            The HAL NAND driver is initialized according to the given handle and instance.
  */
hal_status_t HAL_NAND_Init(hal_nand_handle_t *hnand, hal_nand_t instance)
{
  ASSERT_DBG_PARAM(hnand != NULL);
  ASSERT_DBG_PARAM(IS_FMC_NAND_ALL_INSTANCE((FMC_NAND_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hnand == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hnand->instance         = instance;
  hnand->attribute_timing = 0U;

#if defined (USE_FMC_CLK_ENABLE_MODEL) && (USE_FMC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_FMC_EnableClock();
#endif /* USE_FMC_CLK_ENABLE_MODEL */


#if defined(USE_HAL_NAND_USER_DATA) && (USE_HAL_NAND_USER_DATA == 1U)
  hnand->p_user_data = NULL;
#endif /* USE_HAL_NAND_USER_DATA */

  hnand->global_state = HAL_NAND_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief   Deinitialize the HAL NAND driver for the given handle and disable the NAND bank.
  * @param   hnand  Pointer to @ref hal_nand_handle_t structure.
  * @warning This API disables the NAND flash memory region. It must be called only after all
  *          NAND flash controller commands and related transfers are completed. Accessing
  *          a disabled NAND memory region while a transfer is still ongoing causes an AXI
  *          bus error.
  */
void HAL_NAND_DeInit(hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);
  ASSERT_DBG_PARAM(IS_FMC_NAND_ALL_INSTANCE(NAND_GET_INSTANCE(hnand)));


  FMC_NAND_Disable(NAND_GET_INSTANCE(hnand));

  hnand->global_state = HAL_NAND_STATE_RESET;
}

/**
  * @brief  Get the NAND instance.
  * @param  hnand    Pointer to a @ref hal_nand_handle_t structure.
  * @return HAL_NAND The HAL NAND instance.
  */
hal_nand_t HAL_NAND_GetInstance(const hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);
  ASSERT_DBG_PARAM(IS_FMC_NAND_ALL_INSTANCE(NAND_GET_INSTANCE(hnand)));

  return hnand->instance;
}

/**
  * @}
  */

/** @addtogroup NAND_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to configure the FMC NAND bank and to retrieve the current
configuration.

There are 2 categories of HAL configuration APIs :

- Global configuration APIs :
  The full configuration is done through these steps and following the order below :
  - Step 1 (Static configuration of FMC peripheral) :
    - HAL_NAND_SetConfig() : used to apply the user static configuration of the FMC peripheral based on FMC features,
                             within the  \ref hal_nand_config_t structure.

  - Step 2 (Memory configuration) :
    - HAL_NAND_SetConfigMemory()        : used to apply the user memory configuration that depends on the device within
                                          @ref hal_nand_memory_config_t structure.
                                          @note when different timing configuration for the last write access is needed,
                                          the HAL_NAND_SetLastWriteAccessTiming() API must be called after
                                          HAL_NAND_SetConfigMemory(), to set the last write access timing parameters.

  - Step 3 (Optional based on the external memory) :
    - HAL_NAND_SetLastWriteAccessTiming()  : used to apply different timing configuration for the last write access,
                                             when required, within @ref hal_nand_timings_t structure.

  - Step 4 (Partition configuration) :
    - HAL_NAND_SetConfigPartition()     : used to apply the user partition configuration within
                                          @ref hal_nand_partition_config_t structure.
    - HAL_NAND_SetConfigPartitionONFI() : used to set the partition configuration, retrieved automatically from the
                                          memory, within @ref hal_nand_partition_config_t structure.


 The configuration parameters are retrieved through these APIs :
  - Static configuration of FMC peripheral :
    - HAL_NAND_GetConfig() : used to retrieve the user FMC configuration and to fill it into @ref hal_nand_config_t
                             structure.
  - Memory configuration :
    - HAL_NAND_GetConfigMemory()        : used to retrieve the user memory configuration and to fill it into
                                          @ref hal_nand_memory_config_t structure.
    - HAL_NAND_GetLastWriteAccessTiming()  : used to retrieve the user timing configuration for the last write access,
                                             when it differs from the previous access, and to fill it into
                                             @ref hal_nand_timings_t structure.
  - Partition configuration :
    - HAL_NAND_GetConfigPartition() : used to retrieve the user partition configuration and to fill it into
                                      @ref hal_nand_partition_config_t structure.

  - NAND start region address retrieval function :
    - HAL_NAND_GetRegionBaseAddress() : used to retrieve the start address of a specific NAND region.

  - Algorithm configuration API :
    - HAL_NAND_ECC_GetAlgo() : used to retrieve the algorithm used for the ECC computation.

- Unitary configuration APIs :
  These APIs allow to set and dynamically modify and retrieve timeouts :
  - HAL_NAND_SetExtraCmdTimeout()    : used to set the extra command timeout.
  - HAL_NAND_GetExtraCmdTimeout()    : used to retrieve the extra command timeout.
  - HAL_NAND_SetPageProgramTimeout() : used to set the page program timeout.
  - HAL_NAND_GetPageProgramTimeout() : used to retrieve the page program timeout.
  - HAL_NAND_SetBlockEraseTimeout()  : used to set the block erase timeout.
  - HAL_NAND_GetBlockEraseTimeout()  : used to retrieve the block erase timeout.
  */

/**
  * @brief   Set the static configuration of FMC peripheral.
  * @param   hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param   p_config          Pointer to @ref hal_nand_config_t structure.
  * @warning This API is the first API to call once the HAL NAND driver is initialized.
  * @retval  HAL_INVALID_PARAM Invalid parameter return when the configuration structure pointer is NULL.
  * @retval  HAL_OK            The static FMC configuration is successfully configured.
  */
hal_status_t HAL_NAND_SetConfig(hal_nand_handle_t *hnand, const hal_nand_config_t *p_config)
{
  uint32_t config_mask;

  ASSERT_DBG_PARAM(hnand    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_PARAM(IS_NAND_WAIT_FEATURE(p_config->wait_feature_status));
#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
  ASSERT_DBG_PARAM(IS_NAND_CHUNK_SIZE(p_config->chunk_size_byte));
  ASSERT_DBG_PARAM(IS_NAND_ECC_ALGORITHM(p_config->ecc_algorithm));
#endif /* USE_HAL_NAND_ECC */
  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_INIT);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  FMC_Disable();

  config_mask = (uint32_t)p_config->wait_feature_status;
#if defined(USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
  STM32_SET_BIT(config_mask, (uint32_t)p_config->chunk_size_byte);
  hnand->chunk_size_byte = FMC_NAND_CalculateChunkSize((uint32_t)p_config->chunk_size_byte);
  if (p_config->ecc_algorithm != HAL_NAND_ECC_ALGO_NONE)
  {
    STM32_SET_BIT(config_mask, (uint32_t)p_config->ecc_algorithm);
  }
  hnand->ecc_algorithm = p_config->ecc_algorithm;
#endif /* USE_HAL_NAND_ECC */

  FMC_NAND_SetConfig(NAND_GET_INSTANCE(hnand), config_mask);

  FMC_Enable();

  hnand->global_state = HAL_NAND_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the static configuration of FMC peripheral.
  * @param hnand    Pointer to @ref hal_nand_handle_t structure.
  * @param p_config Pointer to @ref hal_nand_config_t structure filled with the retrieved static FMC peripheral
  *        configuration.
  */
void HAL_NAND_GetConfig(const hal_nand_handle_t *hnand, hal_nand_config_t *p_config)
{
  uint32_t config;

  ASSERT_DBG_PARAM(hnand    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_CONFIGURED
                   | (uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_NAND_STATE_IDLE
                   | (uint32_t)HAL_NAND_STATE_ACTIVE);

  FMC_NAND_GetConfig(NAND_GET_INSTANCE(hnand), &config);

  p_config->wait_feature_status = (hal_nand_wait_feature_status_t)(uint32_t)STM32_READ_BIT(config, FMC_PCR_PWAITEN);
#if defined(USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
  p_config->chunk_size_byte = (hal_nand_chunk_size_t)(uint32_t)STM32_READ_BIT(config, FMC_PCR_ECCPS);
  p_config->ecc_algorithm  = (hal_nand_ecc_algorithm_t)hnand->ecc_algorithm;
#endif /* USE_HAL_NAND_ECC */
}

/**
  * @brief   Set the memory configuration.
  * @param   hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param   p_config          Pointer to @ref hal_nand_memory_config_t structure.
  * @warning The first use of this API must be done after calling HAL_NAND_SetConfig() API for NAND memories then,
  *          it can be reused multiple times to adjust memory parameters when needed.
  * @retval  HAL_INVALID_PARAM Invalid parameter return when the configuration structure pointer is NULL or the clock
  *                            frequency is equal to zero.
  * @retval  HAL_OK            The memory is successfully configured.
  */
hal_status_t HAL_NAND_SetConfigMemory(hal_nand_handle_t *hnand, const hal_nand_memory_config_t *p_config)
{
  uint32_t timing_mask;
  uint32_t control_mask;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hnand    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_NAND_DATA_WIDTH(p_config->data_width));
#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
  ASSERT_DBG_PARAM(IS_NAND_EXTRA_COMMAND_STATE(p_config->extra_command_status));
#endif /* USE_HAL_NAND_EXTRA_CMD */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_config == NULL) || (clk_freq_hz == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t tclr_setup_tmp = FMC_ConvertNanosecondsToClockCycle(p_config->tclr_setup_time_nsec, clk_freq_hz);
  uint32_t tar_setup_tmp  = FMC_ConvertNanosecondsToClockCycle(p_config->tar_setup_time_nsec, clk_freq_hz);
  uint32_t mem_setup_tmp  = FMC_ConvertNanosecondsToClockCycle(p_config->timing.setup_time_nsec, clk_freq_hz);
  uint32_t mem_wait_tmp   = FMC_ConvertNanosecondsToClockCycle(p_config->timing.wait_time_nsec, clk_freq_hz);
  uint32_t mem_hold_tmp   = FMC_ConvertNanosecondsToClockCycle(p_config->timing.hold_time_nsec, clk_freq_hz);
  uint32_t mem_hiz_tmp    = FMC_ConvertNanosecondsToClockCycle(p_config->timing.hiz_time_nsec, clk_freq_hz);

  ASSERT_DBG_PARAM(IS_FMC_TCLR_TIME(tclr_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_TAR_TIME(tar_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_SETUP_TIME(mem_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_WAIT_TIME(mem_wait_tmp));
  ASSERT_DBG_PARAM(IS_FMC_HOLD_TIME(mem_hold_tmp));
  ASSERT_DBG_PARAM(IS_FMC_HIZ_COMMON_TIME(mem_hiz_tmp));

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_CONFIGURED
                   | (uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED);

#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
  hnand->extra_command_status     = p_config->extra_command_status;
  hnand->extra_command_timeout_usec = p_config->extra_command_timeout_usec;
#endif /* USE_HAL_NAND_EXTRA_CMD */

  hnand->program_timeout_usec   = p_config->program_timeout_usec;
  hnand->erase_timeout_msec     = p_config->erase_timeout_msec;
#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
  hnand->ecc_offset_byte = p_config->ecc_offset_byte;
#endif /* USE_HAL_NAND_ECC */

  control_mask = (uint32_t)p_config->data_width
                 | FMC_WRITE_FIELD(tclr_setup_tmp - 1U, FMC_PCR_TCLR_Msk, FMC_PCR_TCLR_Pos)
                 | FMC_WRITE_FIELD(tar_setup_tmp - 1U, FMC_PCR_TAR_Msk, FMC_PCR_TAR_Pos) | FMC_PCR_PBKEN_Msk;

  timing_mask = (mem_setup_tmp - 1U) | FMC_WRITE_FIELD(mem_wait_tmp - 1U, FMC_PMEM_MEMWAIT_Msk, FMC_PMEM_MEMWAIT_Pos)
                | FMC_WRITE_FIELD(mem_hold_tmp - 1U, FMC_PMEM_MEMHOLD_Msk, FMC_PMEM_MEMHOLD_Pos)
                | FMC_WRITE_FIELD(mem_hiz_tmp - 1U, FMC_PMEM_MEMHIZ_Msk, FMC_PMEM_MEMHIZ_Pos);
  FMC_Disable();

  FMC_NAND_SetConfigMemory(NAND_GET_INSTANCE(hnand), control_mask, timing_mask);

  FMC_Enable();

  hnand->global_state = HAL_NAND_STATE_MEMORY_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief Retrieve the memory configuration.
  * @param hnand     Pointer to @ref hal_nand_handle_t structure.
  * @param p_config  Pointer to @ref hal_nand_memory_config_t structure filled with the retrieved memory
                     configuration.
  * @note  If all retrieved timing parameters are zero, check the clock frequency settings to ensure they are properly
  *        set.
  */
void HAL_NAND_GetConfigMemory(const hal_nand_handle_t *hnand, hal_nand_memory_config_t *p_config)
{
  uint32_t memory_cfg;
  uint32_t timing_cfg;

  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hnand    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_NAND_STATE_IDLE
                   | (uint32_t)HAL_NAND_STATE_ACTIVE);

  FMC_NAND_GetConfigMemory(NAND_GET_INSTANCE(hnand), &memory_cfg, &timing_cfg);

  p_config->data_width = (hal_nand_data_width_t)(uint32_t)STM32_READ_BIT(memory_cfg, FMC_PCR_PWID);
#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
  p_config->extra_command_status = hnand->extra_command_status;
  p_config-> extra_command_timeout_usec = hnand->extra_command_timeout_usec;
#endif /* USE_HAL_NAND_EXTRA_CMD */

  p_config->program_timeout_usec   = hnand->program_timeout_usec;
  p_config->erase_timeout_msec     = hnand->erase_timeout_msec;
#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
  p_config->ecc_offset_byte = hnand->ecc_offset_byte;
#endif /* USE_HAL_NAND_ECC */
  p_config->tclr_setup_time_nsec   = FMC_ConvertClockCycleToNanoseconds((STM32_READ_BIT(memory_cfg, FMC_PCR_TCLR) + 1U),
                                                                        clk_freq_hz);
  p_config->tar_setup_time_nsec    = FMC_ConvertClockCycleToNanoseconds((FMC_READ_FIELD(memory_cfg, FMC_PCR_TAR_Msk,
                                                                         FMC_PCR_TAR_Pos) + 1U),
                                                                        clk_freq_hz);
  p_config->timing.setup_time_nsec = FMC_ConvertClockCycleToNanoseconds((STM32_READ_BIT(timing_cfg, FMC_PMEM_MEMSET)
                                                                         + 1U), clk_freq_hz);
  p_config->timing.wait_time_nsec  = FMC_ConvertClockCycleToNanoseconds((FMC_READ_FIELD(timing_cfg,
                                                                         FMC_PMEM_MEMWAIT_Msk, FMC_PMEM_MEMWAIT_Pos)
                                                                         + 1U), clk_freq_hz);
  p_config->timing.hold_time_nsec  = FMC_ConvertClockCycleToNanoseconds((FMC_READ_FIELD(timing_cfg,
                                                                         FMC_PMEM_MEMHOLD_Msk, FMC_PMEM_MEMHOLD_Pos)
                                                                         + 1U), clk_freq_hz);
  p_config->timing.hiz_time_nsec   = FMC_ConvertClockCycleToNanoseconds((FMC_READ_FIELD(timing_cfg,
                                                                         FMC_PMEM_MEMHIZ_Msk, FMC_PMEM_MEMHIZ_Pos)
                                                                         + 1U), clk_freq_hz);
}

/**
  * @brief   Set timing configuration for the last write access.
  * @param   hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param   p_timings         Pointer to @ref hal_nand_timings_t structure.
  * @warning                   This API must be called only when different timing configuration for the last write
  *                            access is needed, to set the timing parameters for last write access.
  * @retval  HAL_INVALID_PARAM Invalid parameter return when the timing configuration structure pointer is NULL
  *                            or the clock frequency is equal to zero.
  * @retval  HAL_OK            The last write access timing configuration is successfully set.
  */
hal_status_t HAL_NAND_SetLastWriteAccessTiming(hal_nand_handle_t *hnand, const hal_nand_timings_t *p_timings)
{
  uint32_t timing_cfg;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hnand     != NULL);
  ASSERT_DBG_PARAM(p_timings != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_timings == NULL) || (clk_freq_hz == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t mem_setup_tmp  = FMC_ConvertNanosecondsToClockCycle(p_timings->setup_time_nsec, clk_freq_hz);
  uint32_t mem_wait_tmp   = FMC_ConvertNanosecondsToClockCycle(p_timings->wait_time_nsec, clk_freq_hz);
  uint32_t mem_hold_tmp   = FMC_ConvertNanosecondsToClockCycle(p_timings->hold_time_nsec, clk_freq_hz);
  uint32_t mem_hiz_tmp    = FMC_ConvertNanosecondsToClockCycle(p_timings->hiz_time_nsec, clk_freq_hz);

  ASSERT_DBG_PARAM(IS_FMC_SETUP_TIME(mem_setup_tmp));
  ASSERT_DBG_PARAM(IS_FMC_WAIT_TIME(mem_wait_tmp));
  ASSERT_DBG_PARAM(IS_FMC_HOLD_TIME(mem_hold_tmp));
  ASSERT_DBG_PARAM(IS_FMC_HIZ_COMMON_TIME(mem_hiz_tmp));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_MEMORY_CONFIGURED);

  timing_cfg = (mem_setup_tmp - 1U) | FMC_WRITE_FIELD(mem_wait_tmp - 1U, FMC_PATT_ATTWAIT_Msk, FMC_PATT_ATTWAIT_Pos)
               | FMC_WRITE_FIELD(mem_hold_tmp - 1U, FMC_PATT_ATTHOLD_Msk, FMC_PATT_ATTHOLD_Pos)
               | FMC_WRITE_FIELD(mem_hiz_tmp - 1U, FMC_PATT_ATTHIZ_Msk, FMC_PATT_ATTHIZ_Pos);

  FMC_Disable();

  FMC_NAND_SetLastWriteAccessTiming(NAND_GET_INSTANCE(hnand), timing_cfg);

  FMC_Enable();

  hnand->attribute_timing = 1U;

  return HAL_OK;
}

/**
  * @brief Retrieve the timing configuration for the last write access.
  * @param hnand     Pointer to @ref hal_nand_handle_t structure.
  * @param p_timings Pointer to @ref hal_nand_timings_t structure filled with the retrieved last write access timing.
  * @note  If all retrieved timing parameters are zero, check the clock frequency settings to ensure they are properly
  *        set.
  */
void HAL_NAND_GetLastWriteAccessTiming(const hal_nand_handle_t *hnand, hal_nand_timings_t *p_timings)
{
  uint32_t timing_cfg;
  uint32_t clk_freq_hz = HAL_RCC_FMC_GetKernelClkFreq();

  ASSERT_DBG_PARAM(hnand     != NULL);
  ASSERT_DBG_PARAM(p_timings != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_NAND_STATE_IDLE
                   | (uint32_t)HAL_NAND_STATE_ACTIVE);

  FMC_NAND_GetLastWriteAccessTiming(NAND_GET_INSTANCE(hnand), &timing_cfg);

  p_timings->setup_time_nsec = FMC_ConvertClockCycleToNanoseconds((STM32_READ_BIT(timing_cfg, FMC_PATT_ATTSET) + 1U),
                                                                  clk_freq_hz);
  p_timings->wait_time_nsec  = FMC_ConvertClockCycleToNanoseconds((FMC_READ_FIELD(timing_cfg, FMC_PATT_ATTWAIT_Msk,
                                                                                  FMC_PATT_ATTWAIT_Pos) + 1U),
                                                                  clk_freq_hz);
  p_timings->hold_time_nsec  = FMC_ConvertClockCycleToNanoseconds((FMC_READ_FIELD(timing_cfg, FMC_PATT_ATTHOLD_Msk,
                                                                                  FMC_PATT_ATTHOLD_Pos)
                                                                   + 1U), clk_freq_hz);
  p_timings->hiz_time_nsec   = FMC_ConvertClockCycleToNanoseconds((FMC_READ_FIELD(timing_cfg, FMC_PATT_ATTHIZ_Msk,
                                                                                  FMC_PATT_ATTHIZ_Pos)
                                                                   + 1U), clk_freq_hz);
}

/**
  * @brief   Set the partition configuration parameters.
  * @param   hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param   p_config          Pointer to @ref hal_nand_partition_config_t structure.
  * @warning This API must be called after setting the static FMC and the memory configuration.
   * @retval  HAL_INVALID_PARAM Invalid parameter return when the partition configuration structure pointer is NULL
   *                            or when any partition dimension is equal to zero.
  * @retval  HAL_OK            The partition is successfully configured.
  */
hal_status_t HAL_NAND_SetConfigPartition(hal_nand_handle_t *hnand, const hal_nand_partition_config_t *p_config)
{
  ASSERT_DBG_PARAM(hnand    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PARTITION_CONFIG_VALID(p_config));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_MEMORY_CONFIGURED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_config == NULL) || (p_config->page_size_byte == 0U) || (p_config->spare_area_size_byte == 0U)
      || (p_config->page_nbr_per_block == 0U) || (p_config->block_nbr_per_lun == 0U)
      || (p_config->lun_nbr_per_device == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hnand->partition_config.page_size_byte       = p_config->page_size_byte;
  hnand->partition_config.spare_area_size_byte = p_config->spare_area_size_byte;
  hnand->partition_config.page_nbr_per_block   = p_config->page_nbr_per_block;
  hnand->partition_config.block_nbr_per_lun    = p_config->block_nbr_per_lun;
  hnand->partition_config.lun_nbr_per_device   = p_config->lun_nbr_per_device;

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief   Set the partition configuration parameters to an ONFI compliant NAND memory.
  * @param   hnand    Pointer to @ref hal_nand_handle_t structure.
  * @warning This API must be called after setting the static FMC and memory configuration, it sets automatically
  *          the partition configuration retrieved from the ONFI compliant NAND memory into
  *          the @ref hal_nand_partition_config_t structure stored within the handle.
  * @retval  HAL_BUSY NAND state is active when calling this API.
  * @retval  HAL_OK   The partition is successfully configured.
  */
hal_status_t HAL_NAND_SetConfigPartitionONFI(hal_nand_handle_t *hnand)
{
  FMC_NAND_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_MEMORY_CONFIGURED);

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_MEMORY_CONFIGURED, HAL_NAND_STATE_ACTIVE);

  p_instance = NAND_GET_INSTANCE(hnand);

  NAND_StartReadParameterPage(hnand);

  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED_PARTITION_START_LEN_BYTES);
  hnand->partition_config.page_size_byte       = *(volatile uint32_t *)(FMC_NAND_DEVICE_ADDRESS(p_instance));
  hnand->partition_config.spare_area_size_byte = *(volatile uint16_t *)(FMC_NAND_DEVICE_ADDRESS(p_instance));
  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED_PARTITION_BEFORE_PAGE_NBR_LEN_BYTES);
  hnand->partition_config.page_nbr_per_block   = *(volatile uint32_t *)(FMC_NAND_DEVICE_ADDRESS(p_instance));
  hnand->partition_config.block_nbr_per_lun    = *(volatile uint32_t *)(FMC_NAND_DEVICE_ADDRESS(p_instance));
  hnand->partition_config.lun_nbr_per_device   = *(volatile uint8_t *)(FMC_NAND_DEVICE_ADDRESS(p_instance));

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Retrieve the NAND partition configuration.
  * @param  hnand    Pointer to @ref hal_nand_handle_t structure.
  * @param  p_config Pointer to @ref hal_nand_partition_config_t structure.
  */
void HAL_NAND_GetConfigPartition(const hal_nand_handle_t *hnand, hal_nand_partition_config_t *p_config)
{
  ASSERT_DBG_PARAM(hnand    != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_IDLE | (uint32_t)HAL_NAND_STATE_ACTIVE);

  p_config->page_size_byte       = hnand->partition_config.page_size_byte;
  p_config->spare_area_size_byte = hnand->partition_config.spare_area_size_byte;
  p_config->page_nbr_per_block   = hnand->partition_config.page_nbr_per_block;
  p_config->block_nbr_per_lun    = hnand->partition_config.block_nbr_per_lun;
  p_config->lun_nbr_per_device   = hnand->partition_config.lun_nbr_per_device;
}

/**
  * @brief  Retrieve NAND start region address.
  * @param  hnand Pointer to @ref hal_nand_handle_t structure.
  * @return NAND start region address.
  */
uint32_t HAL_NAND_GetRegionBaseAddress(const hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);
  ASSERT_DBG_STATE(hnand->global_state, (uint32_t) HAL_NAND_STATE_INIT | (uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED
                   | (uint32_t)HAL_NAND_STATE_IDLE | (uint32_t)HAL_NAND_STATE_ACTIVE);


  return (uint32_t)FMC_NAND_DEVICE_ADDRESS(NAND_GET_INSTANCE(hnand));
}

#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
/**
  * @brief  Set the read extra command timeout.
  * @param  hnand      Pointer to @ref hal_nand_handle_t structure.
  * @param  timeout_usec Extra timeout value in microseconds.
  * @retval HAL_OK     The timeout is successfully set.
  */
hal_status_t HAL_NAND_SetExtraCmdTimeout(hal_nand_handle_t *hnand, uint32_t timeout_usec)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

  hnand->extra_command_timeout_usec = timeout_usec;

  return HAL_OK;
}

/**
  * @brief  Retrieve the read extra command timeout.
  * @param  hnand Pointer to @ref hal_nand_handle_t structure.
  * @return uint32_t Read extra command timeout in microseconds.
  */
uint32_t HAL_NAND_GetExtraCmdTimeout(const hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_IDLE | (uint32_t)HAL_NAND_STATE_ACTIVE);

  return hnand->extra_command_timeout_usec;
}
#endif /* USE_HAL_NAND_EXTRA_CMD */

/**
  * @brief  Set the page program timeout.
  * @param  hnand      Pointer to @ref hal_nand_handle_t structure.
  * @param  timeout_usec Page program timeout value in microseconds.
  * @retval HAL_OK       The timeout is successfully set.
  */
hal_status_t HAL_NAND_SetPageProgramTimeout(hal_nand_handle_t *hnand, uint32_t timeout_usec)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

  hnand->program_timeout_usec = timeout_usec;

  return HAL_OK;
}

/**
  * @brief  Retrieve the page program timeout.
  * @param  hnand Pointer to @ref hal_nand_handle_t structure.
  * @return uint32_t Page program timeout in microseconds.
  */
uint32_t HAL_NAND_GetPageProgramTimeout(const hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_IDLE | (uint32_t)HAL_NAND_STATE_ACTIVE);

  return hnand->program_timeout_usec;
}

/**
  * @brief  Set the block erase timeout.
  * @param  hnand      Pointer to @ref hal_nand_handle_t structure.
  * @param  timeout_msec Block erase timeout value in milliseconds.
  * @retval HAL_OK     The timeout is successfully set.
  */
hal_status_t HAL_NAND_SetBlockEraseTimeout(hal_nand_handle_t *hnand, uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

  hnand->erase_timeout_msec = timeout_msec;

  return HAL_OK;
}

/**
  * @brief  Retrieve the block erase timeout.
  * @param  hnand Pointer to @ref hal_nand_handle_t structure.
  * @return uint32_t Block erase timeout in milliseconds.
  */
uint32_t HAL_NAND_GetBlockEraseTimeout(const hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_IDLE | (uint32_t)HAL_NAND_STATE_ACTIVE);

  return hnand->erase_timeout_msec;
}

#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
/**
  * @brief  Retrieve the error code correction algorithm used.
  * @param  hnand                      Pointer to @ref hal_nand_handle_t structure.
  * @retval HAL_NAND_ECC_ALGO_NONE     The ECC computation is disabled.
  * @retval HAL_NAND_ECC_ALGO_HAMMING  The ECC Hamming computation is enabled.
  * @retval HAL_NAND_ECC_ALGO_BCH_4BIT The ECC ECC BCH 4-bit computation is enabled.
  * @retval HAL_NAND_ECC_ALGO_BCH_8BIT The ECC ECC BCH 8-bit computation is enabled.
  */
hal_nand_ecc_algorithm_t HAL_NAND_ECC_GetAlgo(const hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_CONFIGURED
                   | (uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED
                   | (uint32_t)HAL_NAND_STATE_IDLE | (uint32_t)HAL_NAND_STATE_ACTIVE);

  return hnand->ecc_algorithm;
}
#endif /* USE_HAL_NAND_ECC */


/**
  * @}
  */

/** @addtogroup NAND_Exported_Functions_Group3
  * @{
This subsection provides a set of functions allowing to control the input and output operations of the ONFI
and legacy compliant NAND memories.

Blocking mode:
- HAL_NAND_Reset()
- HAL_NAND_ReadID()
- HAL_NAND_ONFIDetect()
- HAL_NAND_ONFIReadParameterPage()
- HAL_NAND_ReadPage()
- HAL_NAND_ProgramPage()
- HAL_NAND_ReadPageSpareArea()
- HAL_NAND_ProgramPageSpareArea()
- HAL_NAND_EraseBlock()
- HAL_NAND_ReadStatus()
- HAL_NAND_ReadInPage()
- HAL_NAND_ProgramInPage()
- HAL_NAND_CopyBackRead()
- HAL_NAND_CopyBackProgram()

Non-blocking mode:
- HAL_NAND_SendReadPageCmd()
- HAL_NAND_EndReadPage()
- HAL_NAND_SendProgramPageCmd()
- HAL_NAND_EndProgramPage()

  */

/**
  * @brief  Reset the NAND flash device.
  * @param  hnand    Pointer to @ref hal_nand_handle_t structure.
  * @retval HAL_BUSY NAND state is active when calling this API.
  * @retval HAL_OK   The NAND flash device is reset successfully.
  */
hal_status_t HAL_NAND_Reset(hal_nand_handle_t *hnand)
{
  volatile hal_nand_state_t previous_state;

  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED | (uint32_t)HAL_NAND_STATE_IDLE);

  FMC_CHECK_UPDATE_STATE(hnand, global_state,
                         ((uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED
                          | (uint32_t)HAL_NAND_STATE_IDLE), HAL_NAND_STATE_ACTIVE, previous_state);

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_RESET);

  hnand->global_state = previous_state;

  return HAL_OK;
}

/**
  * @brief  Read the device identifier.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  p_nand_id         Pointer to @ref hal_nand_id_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the device identifier structure pointer is NULL.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_OK            The device identifier is successfully read.
  */
hal_status_t HAL_NAND_ReadID(hal_nand_handle_t *hnand, hal_nand_id_t *p_nand_id)
{
  volatile uint32_t data = 0U;

  ASSERT_DBG_PARAM(hnand     != NULL);
  ASSERT_DBG_PARAM(p_nand_id != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_nand_id == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_READ_ID);

  FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_ADDR_AREA_A);

  data = *(volatile uint32_t *)FMC_NAND_DEVICE_ADDRESS(NAND_GET_INSTANCE(hnand));

  volatile uint8_t *id_bytes   = (volatile uint8_t *)&data;
  p_nand_id->manufacturer_code = id_bytes[0];
  p_nand_id->device_id         = id_bytes[1];
  p_nand_id->third_id          = id_bytes[2];
  p_nand_id->fourth_id         = id_bytes[3];

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Check whether the NAND memory is ONFI compliant.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  p_onfi_status     Pointer to the ONFI status output.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the device ONFI status pointer is NULL.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_OK            The device ONFI status is successfully read.
  */
hal_status_t HAL_NAND_ONFIDetect(hal_nand_handle_t *hnand, hal_nand_onfi_status_t *p_onfi_status)
{
  uint32_t page_signature;

  ASSERT_DBG_PARAM(hnand         != NULL);
  ASSERT_DBG_PARAM(p_onfi_status != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_onfi_status == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  NAND_StartReadParameterPage(hnand);

  page_signature = *(volatile uint32_t *)(FMC_NAND_DEVICE_ADDRESS(NAND_GET_INSTANCE(hnand)));

  if (page_signature == NAND_ONFI_TAG)
  {
    *p_onfi_status = HAL_NAND_IS_ONFI_COMPLIANT;
  }
  else
  {
    *p_onfi_status = HAL_NAND_IS_NOT_ONFI_COMPLIANT;
  }

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Read the data structure describing the device's organization, features, timings and other behavioral
  *         parameters.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  p_param_config    Pointer to @ref hal_nand_param_config_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the parameter page data structure pointer is NULL.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_OK            The parameter page is successfully read.
  */
hal_status_t HAL_NAND_ONFIReadParameterPage(hal_nand_handle_t *hnand, hal_nand_param_config_t *p_param_config)
{
  uint32_t nand_address;
  ASSERT_DBG_PARAM(hnand          != NULL);
  ASSERT_DBG_PARAM(p_param_config != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_param_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  FMC_NAND_TypeDef *p_instance = NAND_GET_INSTANCE(hnand);

  NAND_StartReadParameterPage(hnand);

  nand_address = (uint32_t)FMC_NAND_DEVICE_ADDRESS(p_instance);
  p_param_config->page_signature     = *(volatile uint32_t *)(nand_address);
  p_param_config->revision_nbr       = *(volatile uint16_t *)(nand_address);
  p_param_config->supported_features = *(volatile uint16_t *)(nand_address);
  p_param_config->opt_commands       = *(volatile uint16_t *)(nand_address);
  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED1_LEN_BYTES);
  for (uint8_t i = 0U; i < FMC_NAND_DEVICE_MANUFACTURER_LEN; i++)
  {
    p_param_config->device_manufacturer[i] = *(volatile uint8_t *)(nand_address);
  }
  for (uint8_t i = 0U; i < FMC_NAND_DEVICE_MODEL_LEN; i++)
  {
    p_param_config->device_model[i] = *(volatile uint8_t *)(nand_address);
  }
  p_param_config->jedec_id = *(volatile uint8_t *)(nand_address);
  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED2_LEN_BYTES);
  p_param_config->page_size_byte = *(volatile uint32_t *)(nand_address);
  p_param_config->spare_area_size_byte = *(volatile uint16_t *)(nand_address);
  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED3_LEN_BYTES);
  p_param_config->page_nbr_per_block = *(volatile uint32_t *)(nand_address);
  p_param_config->block_nbr_per_lun  = *(volatile uint32_t *)(nand_address);
  p_param_config->lun_nbr_per_device = *(volatile uint8_t *)(nand_address);
  p_param_config->addr_cycle_nbr     = *(volatile uint8_t *)(nand_address);
  p_param_config->bit_per_cell_nbr   = *(volatile uint8_t *)(nand_address);
  p_param_config->bad_blocks_nbr     = *(volatile uint16_t *)(nand_address);
  p_param_config->block_endurance    = *(volatile uint16_t *)(nand_address);
  p_param_config->valid_block_nbr    = *(volatile uint8_t *)(nand_address);
  p_param_config->valid_block_endurance = *(volatile uint16_t *)(nand_address);
  p_param_config->program_page_nbr   = *(volatile uint8_t *)(nand_address);
  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED4_LEN_BYTES);
  p_param_config->ecc_bits_nbr       = *(volatile uint8_t *)(nand_address);
  p_param_config->plane_address_bits_nbr = *(volatile uint8_t *)(nand_address);
  p_param_config->training_commands      = *(volatile uint8_t *)(nand_address);
  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED5_LEN_BYTES);
  p_param_config->sdr_timing_mode        = *(volatile uint16_t *)(nand_address);
  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED6_LEN_BYTES);
  p_param_config->driver_strength        = *(volatile uint8_t *)(nand_address);
  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED7_LEN_BYTES);
  p_param_config->warmup_cycles          = *(volatile uint8_t *)(nand_address);
  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED8_LEN_BYTES);
  p_param_config->vendor_revision_nbr    = *(volatile uint16_t *)(nand_address);
  FMC_NAND_DummyRead(p_instance, NAND_ONFI_RESERVED9_LEN_BYTES);
  p_param_config->integrity_crc          = *(volatile uint16_t *)(nand_address);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Read a page from the NAND memory data area.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to read from.
  * @param  p_data            Pointer to the data read from the NAND memory.
  * @param  size_byte         Number of bytes to read.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data is NULL, when size_byte is 0 or exceeds the
  *                           configured page size, or when page_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_TIMEOUT       NAND internal processing exceeded the timeout when using NAND extra command.
  * @retval HAL_ERROR         NAND device is not ready or the read operation status reports a device failure.
  * @retval HAL_OK            The data is successfully read.
  */
hal_status_t HAL_NAND_ReadPage(hal_nand_handle_t *hnand, uint32_t page_index, void *p_data, uint32_t size_byte)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hnand  != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_SIZE_VALID(hnand, size_byte));
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U) || (size_byte > hnand->partition_config.page_size_byte)
      || (page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                         * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  NAND_StartReadPage(hnand, page_index);

#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
  if (hnand->extra_command_status == HAL_NAND_EXTRA_COMMAND_ENABLED)
  {
    status = NAND_PollForOperationStatus(hnand, hnand->extra_command_timeout_usec);

    if (status != HAL_OK)
    {
      hnand->global_state = HAL_NAND_STATE_IDLE;

      return status;
    }
    FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_AREA_A);
  }
#endif /* USE_HAL_NAND_EXTRA_CMD */

  FMC_NAND_ReadFromDevice(NAND_GET_INSTANCE(hnand), p_data, size_byte);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return status;
}

/**
  * @brief  Program a page to the NAND memory data area.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to write in.
  * @param  p_data            Pointer to the buffer to write in the NAND memory.
  * @param  size_byte         Number of bytes to write.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data is NULL, when size_byte is 0 or exceeds the
  *                           configured page size, or when page_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_TIMEOUT       NAND internal processing exceeded the timeout.
  * @retval HAL_ERROR         NAND device is not ready, or an internal error occurred during
  *                           programming.
  * @retval HAL_OK            The data is successfully programmed.
  */
hal_status_t HAL_NAND_ProgramPage(hal_nand_handle_t *hnand, uint32_t page_index, const void *p_data, uint32_t size_byte)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hnand  != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_SIZE_VALID(hnand, size_byte));
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U) || (size_byte > hnand->partition_config.page_size_byte)
      || (page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                         * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  NAND_StartProgramPage(hnand, page_index);

  FMC_NAND_WriteToDevice(NAND_GET_INSTANCE(hnand), p_data, size_byte);

  status = NAND_EndProgramPage(hnand);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return status;
}

/**
  * @brief  Read the NAND memory spare area.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to read from.
  * @param  p_data            Pointer to the buffer read from the NAND memory.
  * @param  size_byte         Number of bytes to read.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data is NULL, when size_byte is 0 or exceeds the
  *                           configured spare area size, or when page_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_TIMEOUT       The read extra timeout exceeds the hardcoded value when using an extra command timeout.
  * @retval HAL_ERROR         NAND device is not ready, or an internal error occurred during reading.
  * @retval HAL_OK            The spare area is successfully read.
  */
hal_status_t HAL_NAND_ReadPageSpareArea(hal_nand_handle_t *hnand, uint32_t page_index, void *p_data, uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hnand  != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_NAND_SPARE_AREA_SIZE_VALID(hnand, size_byte));
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U) || (size_byte > hnand->partition_config.spare_area_size_byte)
      || (page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                         * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  if (hnand->partition_config.page_size_byte <= FMC_NAND_PAGE_SIZE_512)
  {
    FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_AREA_C);
    NAND_SetAddress(hnand, page_index, NAND_PAGE_START_OFFSET);
  }
  else
  {
    FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_AREA_A);
    NAND_SetAddress(hnand, page_index, (uint16_t)hnand->partition_config.page_size_byte);
  }

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_AREA_TRUE1);

#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
  hal_status_t status;
  if (hnand->extra_command_status == HAL_NAND_EXTRA_COMMAND_ENABLED)
  {
    status = NAND_PollForOperationStatus(hnand, hnand->extra_command_timeout_usec);
    if (status != HAL_OK)
    {
      hnand->global_state = HAL_NAND_STATE_IDLE;

      return status;
    }
    FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_AREA_A);
  }
#endif /* USE_HAL_NAND_EXTRA_CMD */

  FMC_NAND_ReadFromDevice(NAND_GET_INSTANCE(hnand), p_data, size_byte);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Program the NAND memory spare area.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to write in.
  * @param  p_data            Pointer to the buffer to write in the NAND memory.
  * @param  size_byte         Number of bytes to write.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data is NULL, when size_byte is 0 or exceeds the
  *                           configured spare area size, or when page_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_TIMEOUT       NAND internal processing exceeded the timeout.
  * @retval HAL_ERROR         NAND device is not ready or an internal error occurred during programming.
  * @retval HAL_OK            The spare area is successfully programmed.
  */
hal_status_t HAL_NAND_ProgramPageSpareArea(hal_nand_handle_t *hnand, uint32_t page_index, const void *p_data,
                                           uint32_t size_byte)
{
  FMC_NAND_TypeDef *p_instance;
  hal_status_t status;

  ASSERT_DBG_PARAM(hnand  != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_NAND_SPARE_AREA_SIZE_VALID(hnand, size_byte));
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U) || (size_byte > hnand->partition_config.spare_area_size_byte)
      || (page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                         * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  p_instance = NAND_GET_INSTANCE(hnand);

  if (hnand->partition_config.page_size_byte <= FMC_NAND_PAGE_SIZE_512)
  {
    FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_AREA_C);
    FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_WRITE0);
    NAND_SetAddress(hnand, page_index, NAND_PAGE_START_OFFSET);
  }
  else
  {
    FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_AREA_A);
    FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_WRITE0);
    NAND_SetAddress(hnand, page_index, (uint16_t)hnand->partition_config.page_size_byte);
  }

  FMC_NAND_WriteToDevice(NAND_GET_INSTANCE(hnand), p_data, size_byte);

  status = NAND_EndProgramPage(hnand);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return status;
}

/**
  * @brief  Erase a specified block of the NAND flash memory.
  * @param  hnand             Pointer to  @ref hal_nand_handle_t structure.
  * @param  block_index       NAND memory block index to erase.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_TIMEOUT       NAND internal processing exceeded the timeout.
  * @retval HAL_INVALID_PARAM Invalid parameter return when the block index exceeds the NAND block range.
  * @retval HAL_ERROR         NAND device is not ready.
  * @retval HAL_OK            The block is successfully erased.
  */
hal_status_t HAL_NAND_EraseBlock(hal_nand_handle_t *hnand, uint32_t block_index)
{
  FMC_NAND_TypeDef *p_instance;
  hal_status_t status;
  uint32_t row_addr = 0U;

  ASSERT_DBG_PARAM(hnand != NULL);
  ASSERT_DBG_PARAM(IS_NAND_BLOCK_INDEX_VALID(hnand, block_index));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (block_index >= (hnand->partition_config.block_nbr_per_lun * hnand->partition_config.lun_nbr_per_device))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  p_instance = NAND_GET_INSTANCE(hnand);

  FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_ERASE0);

  row_addr = NAND_RowAddress(hnand, block_index);

  FMC_NAND_WriteAddress(p_instance, FMC_NAND_ADDR_1ST_CYCLE(row_addr));

  FMC_NAND_WriteAddress(p_instance, FMC_NAND_ADDR_2ND_CYCLE(row_addr));

  FMC_NAND_WriteAddress(p_instance, FMC_NAND_ADDR_3RD_CYCLE(row_addr));

  FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_ERASE1);

  status = NAND_PollForEraseOperationStatus(hnand, hnand->erase_timeout_msec);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return status;
}

/**
  * @brief  Read the NAND flash memory operation status.
  * @param  hnand                       Pointer to @ref hal_nand_handle_t structure.
  * @retval HAL_NAND_DEVICE_STATE_BUSY  NAND internal processing is ongoing.
  * @retval HAL_NAND_DEVICE_STATE_ERROR NAND internal processing is failed.
  * @retval HAL_NAND_DEVICE_STATE_READY NAND internal processing successfully completed.
  */
hal_nand_device_status_t HAL_NAND_ReadStatus(const hal_nand_handle_t *hnand)
{
  hal_nand_device_status_t status;

  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED
                   | (uint32_t)HAL_NAND_STATE_IDLE | (uint32_t)HAL_NAND_STATE_ACTIVE);

  status = NAND_ReadStatus(hnand);

  return status;
}

/**
  * @brief  Read data starting at a specified column offset within the selected page.
  * @param  hnand             Pointer to  @ref hal_nand_handle_t structure.
  * @param  page_index        Page index to read from.
  * @param  column_index      Column index to read from.
  * @param  p_data            Pointer to the buffer read from the NAND memory.
  * @param  size_byte         Number of bytes to read.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data is NULL, when size_byte is 0 or exceeds the
  *                           configured page size, or when page_index or column_index is out of range.
  * @retval HAL_ERROR         NAND device is not ready.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_OK            The data is successfully read.
  */
hal_status_t HAL_NAND_ReadInPage(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index,
                                 void *p_data, uint32_t size_byte)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hnand  != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));
  ASSERT_DBG_PARAM(IS_NAND_COLUMN_INDEX_VALID(hnand, column_index));
  ASSERT_DBG_PARAM(IS_NAND_PAGE_SIZE_VALID(hnand, column_index + size_byte));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U) || ((column_index + size_byte) > hnand->partition_config.page_size_byte)
      || (column_index >= hnand->partition_config.page_size_byte)
      || (page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                         * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  NAND_ChangeReadColumn(hnand, page_index, column_index, (uint8_t *)p_data, size_byte);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return status;
}

/**
  * @brief  Program data starting at a specified column offset within the selected page.
  * @param  hnand             Pointer to  @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to write in.
  * @param  column_index      Column index to write in.
  * @param  p_data            Pointer to the buffer to write in the NAND memory.
  * @param  size_byte         Number of bytes to write.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data is NULL, when size_byte is 0 or exceeds the
  *                           configured page size, or when page_index or column_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_TIMEOUT       NAND internal processing exceeded the timeout.
  * @retval HAL_ERROR         NAND device is not ready or an internal error occurred during programming.
  * @retval HAL_OK            The data is successfully written.
  */
hal_status_t HAL_NAND_ProgramInPage(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index,
                                    const void *p_data, uint32_t size_byte)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hnand  != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));
  ASSERT_DBG_PARAM(IS_NAND_COLUMN_INDEX_VALID(hnand, column_index));
  ASSERT_DBG_PARAM(IS_NAND_PAGE_SIZE_VALID(hnand, column_index + size_byte));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U) || ((column_index + size_byte) > hnand->partition_config.page_size_byte)
      || (column_index >= hnand->partition_config.page_size_byte)
      || (page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                         * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  NAND_ChangeWriteColumn(hnand, page_index, column_index, (const uint8_t *)p_data, size_byte);

  status = NAND_EndProgramPage(hnand);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return status;
}

/**
  * @brief  Read data from source location and copy it temporarily in the NAND memory's internal buffer.
  * @param  hnand             Pointer to  @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to read from.
  * @param  column_index      Column index to start reading from.
  * @retval HAL_INVALID_PARAM Invalid parameter return when page_index or column_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_TIMEOUT       The read extra timeout exceeds the hardcoded value when using an extra command timeout.
  * @retval HAL_ERROR         NAND device is not ready or an internal error occurred during the read operation.
  * @retval HAL_OK            The data is successfully read and copied the NAND memory's internal buffer.
  */
hal_status_t HAL_NAND_CopyBackRead(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index)
{
  ASSERT_DBG_PARAM(hnand != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));
  ASSERT_DBG_PARAM(IS_NAND_COLUMN_INDEX_VALID(hnand, column_index));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                      * hnand->partition_config.lun_nbr_per_device))
      || (column_index >= hnand->partition_config.page_size_byte))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_AREA_A);

  NAND_SetAddress(hnand, page_index, column_index);

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_READ_COPY_BACK);

#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)

  if (hnand->extra_command_status == HAL_NAND_EXTRA_COMMAND_ENABLED)
  {
    hal_status_t status;

    status = NAND_PollForOperationStatus(hnand, hnand->extra_command_timeout_usec);

    if (status != HAL_OK)
    {
      hnand->global_state = HAL_NAND_STATE_IDLE;

      return status;
    }

    FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_AREA_A);
  }
#endif /* USE_HAL_NAND_EXTRA_CMD */

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return  HAL_OK;
}

/**
  * @brief  Copy the data held in the NAND internal buffer to a new destination location.
  * @param  hnand             Pointer to  @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to write in.
  * @param  column_index      Column index to start writing in.
  * @retval HAL_INVALID_PARAM Invalid parameter return when page_index or column_index is out of range .
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_TIMEOUT       NAND internal processing exceeded the program timeout.
  * @retval HAL_ERROR         NAND device is not ready or an internal error occurred during the programming operation.
  * @retval HAL_OK            The data is successfully copied in the new destination location.
  */
hal_status_t HAL_NAND_CopyBackProgram(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hnand != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));
  ASSERT_DBG_PARAM(IS_NAND_COLUMN_INDEX_VALID(hnand, column_index));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                      * hnand->partition_config.lun_nbr_per_device))
      || (column_index >= hnand->partition_config.page_size_byte))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_RANDOM_INPUT);

  NAND_SetAddress(hnand, page_index, column_index);

  status = NAND_EndProgramPage(hnand);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return  status;
}

/**
  * @brief  Send read page command.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to read from.
  * @retval HAL_INVALID_PARAM Invalid parameter return when page_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_TIMEOUT       NAND internal processing exceeded the timeout when using NAND extra command.
  * @retval HAL_ERROR         NAND device is not ready.
  * @retval HAL_OK            The read command is sent successfully.
  */
hal_status_t HAL_NAND_SendReadPageCmd(hal_nand_handle_t *hnand, uint32_t page_index)
{
  ASSERT_DBG_PARAM(hnand != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                      * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  NAND_StartReadPage(hnand, page_index);

#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
  hal_status_t status;

  if (hnand->extra_command_status == HAL_NAND_EXTRA_COMMAND_ENABLED)
  {
    status = NAND_PollForOperationStatus(hnand, hnand->extra_command_timeout_usec);

    if (status != HAL_OK)
    {
      hnand->global_state = HAL_NAND_STATE_IDLE;

      return status;
    }

    FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_AREA_A);
  }
#endif /* USE_HAL_NAND_EXTRA_CMD */

  return HAL_OK;
}

/**
  * @brief  Finalize the read page process.
  * @param  hnand  Pointer to @ref hal_nand_handle_t structure.
  * @retval HAL_OK The read process is completed successfully.
  */
hal_status_t HAL_NAND_EndReadPage(hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_ACTIVE);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Send program page command.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to write in.
  * @retval HAL_INVALID_PARAM Invalid parameter return when page_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_ERROR         NAND device is not ready.
  * @retval HAL_OK            The program command is sent successfully.
  */
hal_status_t HAL_NAND_SendProgramPageCmd(hal_nand_handle_t *hnand, uint32_t page_index)
{
  ASSERT_DBG_PARAM(hnand != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                      * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  NAND_StartProgramPage(hnand, page_index);

  return HAL_OK;
}

/**
  * @brief  Finalize the program page process.
  * @param  hnand       Pointer to @ref hal_nand_handle_t structure.
  * @retval HAL_TIMEOUT NAND internal processing exceeded the timeout.
  * @retval HAL_ERROR   NAND device is not ready or an internal error occurred during programming.
  * @retval HAL_OK      The program process is completed successfully.
  */
hal_status_t HAL_NAND_EndProgramPage(hal_nand_handle_t *hnand)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_ACTIVE);

  status = NAND_EndProgramPage(hnand);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return status;
}

/**
  * @}
  */

#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
/** @addtogroup NAND_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to manage error code correction ECC processes in blocking mode :
- HAL_NAND_ECC_ReadPage()
- HAL_NAND_ECC_ProgramPage()
- HAL_NAND_ECC_GetErrors()

  */
/**
  * @brief  Read a page from the NAND memory data area with the ECC computation.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to read from.
  * @param  p_data            Pointer to data buffer to read from the NAND memory.
  * @param  size_byte         Number of bytes to read.
  * @param  p_ecc             Pointer to ECC buffer to read from the NAND memory.
  * @param  ecc_size_byte     Number of bytes to read from the ECC buffer.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data is NULL, when size_byte is 0 or exceeds the
  *                           configured page size, when p_ecc is NULL, when ecc_size_byte is 0 or invalid, or when
  *                           page_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_ERROR         NAND device is not ready or the ECC computation failed.
  * @retval HAL_OK            The data is successfully read.
  */
hal_status_t HAL_NAND_ECC_ReadPage(hal_nand_handle_t *hnand, uint32_t page_index, void *p_data, uint32_t size_byte,
                                   void *p_ecc, uint32_t ecc_size_byte)
{
  hal_status_t status;
  uint32_t chunk_offset    = 0U;
  uint32_t ecc_offset_byte = 0U;
  uint32_t ecc_size        = 0U;
  ASSERT_DBG_PARAM(hnand  != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(p_ecc  != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_SIZE_VALID(hnand, size_byte));
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));
  ASSERT_DBG_PARAM(IS_NAND_ECC_SIZE_VALID(hnand, ecc_size_byte));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U) || (size_byte > hnand->partition_config.page_size_byte)
      || (page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                         * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }

  if ((p_ecc == NULL) || (ecc_size_byte == 0U)
      || (ecc_size_byte != (NAND_GetEccWordsPerChunk(hnand) * 4U
                            * (hnand->partition_config.page_size_byte / hnand->chunk_size_byte))))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }


  ecc_offset_byte = hnand->partition_config.page_size_byte + hnand->ecc_offset_byte;

  NAND_StartReadPage(hnand, page_index);

  do
  {
    FMC_NAND_ECC_Enable(NAND_GET_INSTANCE(hnand));

    FMC_NAND_ECC_ChunkRead(NAND_GET_INSTANCE(hnand), chunk_offset, &((uint8_t *)p_data)[chunk_offset],
                           hnand->chunk_size_byte);

    if (hnand->ecc_algorithm == HAL_NAND_ECC_ALGO_HAMMING)
    {
      status = NAND_PollForHammingStatus(hnand);
      if (status != HAL_OK)
      {
        hnand->global_state = HAL_NAND_STATE_IDLE;

        return status;
      }
    }

    status = NAND_ECC_GetChunkResults(hnand, ((uint8_t *)p_ecc) + ecc_size, ecc_offset_byte);

    FMC_NAND_ECC_Disable(NAND_GET_INSTANCE(hnand));

    ecc_size =  ecc_size + (NAND_GetEccWordsPerChunk(hnand) * 4U);

    chunk_offset = chunk_offset + hnand->chunk_size_byte;

    ecc_offset_byte = ecc_offset_byte + (NAND_GetEccWordsPerChunk(hnand) * 4U);

  } while (chunk_offset < hnand->partition_config.page_size_byte);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return status;
}

/**
  * @brief  Program a page in the NAND memory data area with the ECC computation.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to write in.
  * @param  p_data            Pointer to data buffer to write in the NAND memory.
  * @param  size_byte         Number of bytes to write.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_data is NULL, when size_byte is 0 or exceeds the
  *                           configured page size, or when page_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_TIMEOUT       NAND internal processing exceeded the program timeout.
  * @retval HAL_ERROR         NAND device is not ready or ECC computation failed.
  * @retval HAL_OK            The data is successfully written.
  */
hal_status_t HAL_NAND_ECC_ProgramPage(hal_nand_handle_t *hnand, uint32_t page_index, const void *p_data,
                                      uint32_t size_byte)
{
  hal_status_t status;
  uint32_t chunk_offset    = 0U;
  uint32_t ecc_offset_byte = 0U;

  ASSERT_DBG_PARAM(hnand  != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));
  ASSERT_DBG_PARAM(IS_NAND_PAGE_SIZE_VALID(hnand, size_byte));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (size_byte == 0U) || (size_byte > hnand->partition_config.page_size_byte)
      || (page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                         * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  ecc_offset_byte = hnand->partition_config.page_size_byte + hnand->ecc_offset_byte;

  NAND_StartProgramPage(hnand, page_index);

  do
  {
    FMC_NAND_ECC_Enable(NAND_GET_INSTANCE(hnand));

    FMC_NAND_ECC_ChunkProgram(NAND_GET_INSTANCE(hnand), chunk_offset, &((const uint8_t *)p_data)[chunk_offset],
                              hnand->chunk_size_byte);
    if (hnand->ecc_algorithm == HAL_NAND_ECC_ALGO_HAMMING)
    {
      status = NAND_PollForHammingStatus(hnand);
    }
    else
    {
      status = HAL_ERROR;
    }

    if (status != HAL_OK)
    {
      hnand->global_state = HAL_NAND_STATE_IDLE;

      return status;
    }

    NAND_ECC_ProgramChunkSpareArea(hnand, ecc_offset_byte);

    FMC_NAND_ECC_Disable(NAND_GET_INSTANCE(hnand));

    chunk_offset = chunk_offset + hnand->chunk_size_byte;

    ecc_offset_byte = ecc_offset_byte + (NAND_GetEccWordsPerChunk(hnand) * 4U);

  } while (chunk_offset < hnand->partition_config.page_size_byte);

  status = NAND_EndProgramPage(hnand);

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return status;
}

/**
  * @brief  Retrieve chunk positions where errors are detected during a read operation.
  * @param  hnand             Pointer to  @ref hal_nand_handle_t structure.
  * @param  page_index        NAND memory page index to get the ECC errors from.
  * @param  chunk_index       Index of the chunk, starting from 0.
  * @param  p_ecc             Pointer to ECC buffer read to get the ECC errors from.
  * @param  ecc_size_byte     Number of bytes to read from the ECC buffer.
  * @param  p_ecc_error       Pointer to @ref hal_nand_ecc_error_t structure, storing chunk error positions.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_ecc_error is NULL, when p_ecc is NULL, when
  *                           ecc_size_byte is 0 or invalid, or when page_index is out of range.
  * @retval HAL_BUSY          NAND state is active when calling this API.
  * @retval HAL_ERROR         NAND device is not ready, an error is detected in the ECC codes, or the ECC algorithm
  *                           is unsupported for decoding.
  * @retval HAL_OK            No error is detected.
  */
hal_status_t HAL_NAND_ECC_GetErrors(hal_nand_handle_t *hnand, uint32_t page_index, uint32_t chunk_index,
                                    const void *p_ecc, uint32_t ecc_size_byte, hal_nand_ecc_error_t *p_ecc_error)
{
  hal_status_t status;
  uint32_t ecc_size_per_chunk;
  uint32_t ecc_program;
  uint32_t ecc_read;
  uint32_t chunk_ecc_offset;
  const uint32_t *p_ecc_read_words  = (const uint32_t *)p_ecc;
  uint8_t  ecc_buffer[NAND_ECC_HAMMING_SIZE_BYTE] = {0U};

  ASSERT_DBG_PARAM(hnand       != NULL);
  ASSERT_DBG_PARAM(p_ecc       != NULL);
  ASSERT_DBG_PARAM(p_ecc_error != NULL);
  ASSERT_DBG_PARAM(IS_NAND_PAGE_INDEX_VALID(hnand, page_index));
  ASSERT_DBG_PARAM(IS_NAND_CHUNK_INDEX_VALID(hnand, chunk_index));
  ASSERT_DBG_PARAM(IS_NAND_ECC_SIZE_VALID(hnand, ecc_size_byte));

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((page_index >= (hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                      * hnand->partition_config.lun_nbr_per_device)))
  {
    return HAL_INVALID_PARAM;
  }

  if (p_ecc_error == NULL)
  {
    return HAL_INVALID_PARAM;
  }

  if ((p_ecc == NULL) || (ecc_size_byte == 0U)
      || (ecc_size_byte != (NAND_GetEccWordsPerChunk(hnand) * 4U
                            * (hnand->partition_config.page_size_byte / hnand->chunk_size_byte))))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hnand, global_state, HAL_NAND_STATE_IDLE, HAL_NAND_STATE_ACTIVE);

  if (NAND_ReadStatus(hnand) != HAL_NAND_DEVICE_STATE_READY)
  {
    hnand->global_state = HAL_NAND_STATE_IDLE;

    return HAL_ERROR;
  }

  switch (hnand->ecc_algorithm)
  {
    case HAL_NAND_ECC_ALGO_HAMMING:
    {
      ecc_size_per_chunk = NAND_GetEccWordsPerChunk(hnand) * 4U;

      chunk_ecc_offset = hnand->partition_config.page_size_byte + hnand->ecc_offset_byte
                         + (chunk_index * ecc_size_per_chunk);

      NAND_ChangeReadColumn(hnand, page_index, (uint16_t)chunk_ecc_offset, ecc_buffer, ecc_size_per_chunk);

      ecc_program = FMC_NAND_ECC_ReadHamming(ecc_buffer);

      ecc_read = p_ecc_read_words[chunk_index];

      status = NAND_ECC_GetHammingErrorPositions(hnand, ecc_program, ecc_read, p_ecc_error);

      break;
    }
    default:
      status = HAL_ERROR;
      break;
  }

  hnand->global_state = HAL_NAND_STATE_IDLE;

  return status;
}
#endif /* USE_HAL_NAND_ECC */
/**
  * @}
  */

/** @addtogroup NAND_Exported_Functions_Group5
  * @{
This subsection provides a set of functions allowing to control the NAND device :

- HAL_NAND_Enable()
- HAL_NAND_Disable()
- HAL_NAND_IsEnabled()
  */

/**
  * @brief  Enable the NAND device.
  * @param  hnand  Pointer to @ref hal_nand_handle_t structure.
  * @note   The NAND device is already enabled once it is fully configured, so this API is not required
  *         to make the NAND enabled after configuration. It is available to re-enable the NAND
  *         after it has been disabled using HAL_NAND_Disable().
  * @retval HAL_OK The NAND is successfully enabled.
  */
hal_status_t HAL_NAND_Enable(hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

  FMC_NAND_Enable(NAND_GET_INSTANCE(hnand));

  return HAL_OK;
}

/**
   * @brief  Disable the NAND device.
   * @param  hnand  Pointer to @ref hal_nand_handle_t structure.
   * @note   This API can be used once the NAND is fully configured and ready to use. In case no process is running,
   *         this API can be called to save power and maintain the current configuration instead of calling
   *         HAL_NAND_DeInit() API then resuming the configuration sequence.
   * @retval HAL_OK The NAND is successfully disabled.
   */
hal_status_t HAL_NAND_Disable(hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, HAL_NAND_STATE_IDLE);

  FMC_NAND_Disable(NAND_GET_INSTANCE(hnand));

  return HAL_OK;
}

/**
  * @brief  Get the NAND device status.
  * @param  hnand             Pointer to @ref hal_nand_handle_t structure.
  * @retval HAL_NAND_ENABLED  The NAND is enabled.
  * @retval HAL_NAND_DISABLED The NAND is disabled.
  */
hal_nand_status_t HAL_NAND_IsEnabled(const hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_INIT
                   | (uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED
                   | (uint32_t)HAL_NAND_STATE_IDLE
                   | (uint32_t)HAL_NAND_STATE_ACTIVE);

  return ((hal_nand_status_t)(uint32_t)FMC_NAND_IsEnabled(NAND_GET_INSTANCE(hnand)));
}

/**
  * @}
  */

/**
  * @}
  */

#if defined(USE_HAL_NAND_USER_DATA) && (USE_HAL_NAND_USER_DATA == 1U)
/** @addtogroup NAND_Exported_Functions_Group7
  * @{
This subsection provides a set of functions allowing to set and retrieve user specific data :
- The HAL_NAND_SetUserData() API : used to store user data pointer into the handle.
- The HAL_NAND_GetUserData() API : used to retrieve user data pointer from the handle.
  */

/**
  * @brief  Store user data pointer into the handle.
  * @param  hnand       Pointer to @ref hal_nand_handle_t structure.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_NAND_SetUserData(hal_nand_handle_t *hnand, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  hnand->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve user data pointer from the handle.
  * @param  hnand Pointer to @ref hal_nand_handle_t structure.
  * @retval Pointer to the user data.
  */
const void *HAL_NAND_GetUserData(const hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  return (hnand->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_NAND_USER_DATA */

/** @addtogroup NAND_Exported_Functions_Group8
  * @{
This subsection provides 3 functions allowing to read the current peripheral frequency, state and last occurred error.
- HAL_NAND_GetClockFreq()       : used to retrieve the current clock frequency of the NAND peripheral.
- HAL_NAND_GetState()           : used to retrieve current global state.
  */

/** @brief  Get the clock frequency of the NAND peripheral.
  * @param  hnand Pointer to @ref hal_nand_handle_t structure.
  * @return uint32_t Frequency in Hz. (0 : Frequency not calculated)
  */
uint32_t HAL_NAND_GetClockFreq(const hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  ASSERT_DBG_STATE(hnand->global_state, (uint32_t)HAL_NAND_STATE_CONFIGURED | (uint32_t)HAL_NAND_STATE_MEMORY_CONFIGURED
                   | (uint32_t)HAL_NAND_STATE_IDLE | (uint32_t)HAL_NAND_STATE_ACTIVE);

  STM32_UNUSED(hnand);

  return HAL_RCC_FMC_GetKernelClkFreq();
}

/**
  * @brief  Get the current global state.
  * @param  hnand                             Pointer to @ref hal_nand_handle_t structure.
  * @retval HAL_NAND_STATE_RESET              The NAND not yet initialized.
  * @retval HAL_NAND_STATE_INIT               The NAND initialized but not yet configured.
  * @retval HAL_NAND_STATE_CONFIGURED         The NAND initialized,  FMC peripheral configured but not yet ready to use.
  * @retval HAL_NAND_STATE_MEMORY_CONFIGURED  The NAND initialized, FMC, memory configured but not yet ready for use.
  * @retval HAL_NAND_STATE_IDLE               NAND initialized, FMC, memory and partition configured and ready for use.
  * @retval HAL_NAND_STATE_ACTIVE             NAND internal processing is ongoing.
  */
hal_nand_state_t HAL_NAND_GetState(const hal_nand_handle_t *hnand)
{
  ASSERT_DBG_PARAM(hnand != NULL);

  return hnand->global_state;
}

/**
  * @}
  */

/** @addtogroup NAND_Private_Functions
  * @{
  * This subsection provides the following set of functions :
  * - NAND_RowAddress() : Calculates the row address.
  * - NAND_SetAddress() : Sets the NAND address cycles.
  * - NAND_ChangeReadColumn() : Handles read operations.
  * - NAND_ChangeWriteColumn() : Handles program operations.
  * - NAND_StartReadPage() : Starts a page read operation.
  * - NAND_StartProgramPage() : Starts a page program operation.
  * - NAND_EndProgramPage() : Ends a page program operation.
  * - NAND_ReadStatus() : Reads NAND device status.
  * - NAND_PollForOperationStatus() : Polls for NAND device operation status.
  * - NAND_PollForEraseOperationStatus() : Polls for NAND device erase operation status.
  * - NAND_PollForHammingStatus() : Polls for NAND device hamming status.
  */

/**
  * @brief  Calculate the row address.
  * @param  hnand Pointer to @ref hal_nand_handle_t structure.
  * @param  block_index  NAND memory block index.
  * @return uint32_t Row address.
  */
static uint32_t NAND_RowAddress(const hal_nand_handle_t *hnand, uint32_t block_index)
{
  return (block_index * (hnand->partition_config.page_nbr_per_block));
}

/**
  * @brief  Set the NAND memory address for subsequent operations.
  * @param  hnand        Pointer to the @ref hal_nand_handle_t structure.
  * @param  row_addr   NAND row memory address.
  * @param  column_addr  NAND column memory address.
  */
static void NAND_SetAddress(const hal_nand_handle_t *hnand, uint32_t row_addr, uint16_t column_addr)
{
  uint32_t nand_pages_nbr = hnand->partition_config.page_nbr_per_block * hnand->partition_config.block_nbr_per_lun
                            * hnand->partition_config.lun_nbr_per_device;

  if ((hnand->partition_config.page_size_byte) <= FMC_NAND_PAGE_SIZE_512)
  {
    FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), 0x00U);
    FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_ADDR_1ST_CYCLE(row_addr));
    FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_ADDR_2ND_CYCLE(row_addr));
    if (nand_pages_nbr > FMC_NAND_MAX_PAGES_FOR_16BIT_ADDRESS)
    {
      FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_ADDR_3RD_CYCLE(row_addr));
    }
  }
  else
  {
    FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_COLUMN_1ST_CYCLE(column_addr));
    FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_COLUMN_2ND_CYCLE(column_addr));
    FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_ADDR_1ST_CYCLE(row_addr));
    FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_ADDR_2ND_CYCLE(row_addr));
    if (nand_pages_nbr > FMC_NAND_MAX_PAGES_FOR_16BIT_ADDRESS)
    {
      FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_ADDR_3RD_CYCLE(row_addr));
    }
  }
}

/**
  * @brief  Change the column address from which data is being read and read data from the NAND memory.
  * @param  hnand        Pointer to the @ref hal_nand_handle_t structure.
  * @param  page_index   NAND memory page index to read from.
  * @param  column_index Column index to read from.
  * @param  p_data       Pointer to the buffer read from the NAND memory.
  * @param  size_byte    Number of bytes to read.
  */
static void NAND_ChangeReadColumn(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index,
                                  uint8_t *p_data, uint32_t size_byte)
{
  NAND_StartReadPage(hnand, page_index);

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_RANDOM_OUTPUT_0);

  FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_COLUMN_1ST_CYCLE(column_index));

  FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_COLUMN_2ND_CYCLE(column_index));

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_RANDOM_OUTPUT_1);

  FMC_NAND_ReadFromDevice(NAND_GET_INSTANCE(hnand), p_data, size_byte);
}

/**
  * @brief  Change the column address being written and program data to the NAND memory.
  * @param  hnand        Pointer to the @ref hal_nand_handle_t structure.
  * @param  page_index   NAND memory page index to write in.
  * @param  column_index Column index to write in.
  * @param  p_data       Pointer to the buffer to write in the NAND memory.
  * @param  size_byte    Number of bytes to write.
  */
static void NAND_ChangeWriteColumn(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index,
                                   const uint8_t *p_data, uint32_t size_byte)
{
  NAND_StartProgramPage(hnand, page_index);

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_RANDOM_INPUT);

  FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_COLUMN_1ST_CYCLE(column_index));

  FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_COLUMN_2ND_CYCLE(column_index));

  FMC_NAND_WriteToDevice(NAND_GET_INSTANCE(hnand), p_data, size_byte);
}

/**
  * @brief  Start reading the NAND ONFI parameter page.
  */
static void NAND_StartReadParameterPage(const hal_nand_handle_t *hnand)
{
  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_READ_PARAMETER_PAGE);

  FMC_NAND_WriteAddress(NAND_GET_INSTANCE(hnand), FMC_NAND_ADDR_AREA_A);
}

/**
  * @brief  Start read data from the NAND memory by sending the read command
  *         and the address of page to read from.
  * @param  hnand      Pointer to the @ref hal_nand_handle_t structure.
  * @param  page_index NAND memory page index to read from.
  */
static void NAND_StartReadPage(hal_nand_handle_t *hnand, uint32_t page_index)
{
  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_AREA_A);

  NAND_SetAddress(hnand, page_index, NAND_PAGE_START_OFFSET);

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_AREA_TRUE1);
}

/**
  * @brief  Start program data to the NAND memory by sending the write command
  *         and the address of page to write to.
  * @param  hnand      Pointer to the @ref hal_nand_handle_t structure.
  * @param  page_index NAND memory page index to write to.
  */
static void NAND_StartProgramPage(hal_nand_handle_t *hnand, uint32_t page_index)
{
  FMC_NAND_TypeDef *p_instance = NAND_GET_INSTANCE(hnand);

  FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_AREA_A);

  FMC_NAND_SendCommonCommand(p_instance, FMC_NAND_CMD_WRITE0);

  NAND_SetAddress(hnand, page_index, NAND_PAGE_START_OFFSET);
}

/**
  * @brief  Finalize page programming by issuing the confirm command and
  *         polling the NAND status until completion or timeout.
  * @param  hnand Pointer to the NAND handle.
  * @retval HAL_OK      NAND page programming completed successfully.
  * @retval HAL_ERROR   NAND page programming failed (device reported error).
  * @retval HAL_TIMEOUT NAND page programming did not complete before timeout.
  */
static hal_status_t NAND_EndProgramPage(hal_nand_handle_t *hnand)
{
  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_WRITE_TRUE1);

  return (NAND_PollForOperationStatus(hnand, hnand->program_timeout_usec));
}

/**
  * @brief  Read the NAND flash memory operation status.
  * @retval HAL_NAND_DEVICE_STATE_BUSY  NAND internal processing is ongoing.
  * @retval HAL_NAND_DEVICE_STATE_ERROR NAND internal processing is failed.
  * @retval HAL_NAND_DEVICE_STATE_READY NAND internal processing successfully completed.
  */
static hal_nand_device_status_t NAND_ReadStatus(const hal_nand_handle_t *hnand)
{
  uint32_t data;

  FMC_NAND_SendCommonCommand(NAND_GET_INSTANCE(hnand), FMC_NAND_CMD_STATUS);

  data = *(volatile uint8_t *)FMC_NAND_DEVICE_ADDRESS(NAND_GET_INSTANCE(hnand));

  if ((data & (uint32_t)HAL_NAND_DEVICE_STATE_ERROR) == (uint32_t)HAL_NAND_DEVICE_STATE_ERROR)
  {
    return HAL_NAND_DEVICE_STATE_ERROR;
  }
  else if ((data & (uint32_t)HAL_NAND_DEVICE_STATE_READY) == (uint32_t)HAL_NAND_DEVICE_STATE_READY)
  {
    return HAL_NAND_DEVICE_STATE_READY;
  }
  else
  {
    return HAL_NAND_DEVICE_STATE_BUSY;
  }
}

/**
  * @brief  Poll NAND operation status.
  * @param  timeout_usec Timeout value in microseconds.
  * @retval HAL_TIMEOUT NAND internal processing exceeded the timeout.
  * @retval HAL_ERROR   NAND internal processing failed (device reported error).
  * @retval HAL_OK      NAND internal processing is successfully completed.
  */
static hal_status_t NAND_PollForOperationStatus(const hal_nand_handle_t *hnand, uint32_t timeout_usec)
{
  uint64_t timeout = (((uint64_t)timeout_usec * (uint64_t)HAL_RCC_GetSYSCLKFreq()) / NAND_CYCLE_DIVIDER /
                      FMC_MICROSECONDS_PER_SECOND);
  hal_nand_device_status_t status = HAL_NAND_DEVICE_STATE_BUSY;
  while ((status != HAL_NAND_DEVICE_STATE_READY) && (timeout > 0U))
  {
    status = NAND_ReadStatus(hnand);
    if (status == HAL_NAND_DEVICE_STATE_ERROR)
    {
      return  HAL_ERROR;
    }
    timeout--;
  }
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }
  return HAL_OK;
}

/**
  * @brief  Poll NAND erase operation status.
  * @param  timeout_msec Timeout value in milliseconds.
  * @retval HAL_TIMEOUT NAND internal processing exceeded the timeout.
  * @retval HAL_ERROR   NAND internal processing failed (device reported error).
  * @retval HAL_OK      NAND internal processing is successfully completed.
  */
static hal_status_t NAND_PollForEraseOperationStatus(const hal_nand_handle_t *hnand, uint32_t timeout_msec)
{
  uint64_t timeout = (((uint64_t)timeout_msec * (uint64_t)HAL_RCC_GetSYSCLKFreq()) / NAND_CYCLE_DIVIDER /
                      FMC_MILLISECONDS_PER_SECOND);
  hal_nand_device_status_t status = HAL_NAND_DEVICE_STATE_BUSY;
  while ((status != HAL_NAND_DEVICE_STATE_READY) && (timeout > 0U))
  {
    status = NAND_ReadStatus(hnand);
    if (status == HAL_NAND_DEVICE_STATE_ERROR)
    {
      return  HAL_ERROR;
    }
    timeout--;
  }
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }
  return HAL_OK;
}

#if defined(USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
/**
  * @brief  Program the ECC value for a chunk in the spare area of the NAND memory.
  * @param  hnand      Pointer to @ref hal_nand_handle_t structure.
  * @param  ecc_offset_byte Offset in the page to write the ECC value to.
 */
static void NAND_ECC_ProgramChunkSpareArea(hal_nand_handle_t *hnand, uint32_t ecc_offset_byte)
{
  uint32_t    p_data[NAND_ECC_MAX_VALUE] = {0};
  uint32_t    ecc_size_byte;
  FMC_NAND_TypeDef *p_instance;

  p_instance = NAND_GET_INSTANCE(hnand);
  p_data[0] = FMC_NAND_ECC_GetHammingValue(p_instance);
  ecc_size_byte = NAND_ECC_HAMMING_SIZE_BYTE;

  FMC_NAND_ECC_ChunkProgram(NAND_GET_INSTANCE(hnand), ecc_offset_byte, p_data, ecc_size_byte);

}

/**
  * @brief  Compute the number of 32-bit words needed to store the ECC of a chunk.
  * @param  hnand      Pointer to @ref hal_nand_handle_t structure.
  * @return uint32_t Number of words needed to store ECC for a chunk.
  */
static uint32_t NAND_GetEccWordsPerChunk(const hal_nand_handle_t *hnand)
{
  STM32_UNUSED(hnand);
  return (uint32_t)1U; /* ECCR */
}

/**
  * @brief  Get the ECC value calculated for the data chunk read from the NAND memory.
  * @param  hnand      Pointer to @ref hal_nand_handle_t structure.
  * @param  p_ecc      Pointer to ECC buffer to store the ECC value.
  * @param  ecc_offset_byte Offset in the page to read the ECC value from.
  * @retval HAL_ERROR  ECC result retrieval/decoder status failed or the ECC algorithm is unsupported.
  * @retval HAL_OK     The ECC value is successfully retrieved.
  */
static hal_status_t NAND_ECC_GetChunkResults(hal_nand_handle_t *hnand, void *p_ecc, uint32_t ecc_offset_byte)
{
  STM32_UNUSED(ecc_offset_byte);
  hal_status_t status = HAL_OK;
  uint32_t ecc_read       = 0U;
  uint32_t *p_ecc_u32     = (uint32_t *)p_ecc;
  switch (hnand->ecc_algorithm)
  {
    case HAL_NAND_ECC_ALGO_HAMMING:
    {
      ecc_read      = FMC_NAND_ECC_GetHammingValue(NAND_GET_INSTANCE(hnand));
      *p_ecc_u32    = ecc_read;
      break;
    }
    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief  Compute the error bit position for Hamming ECC on a single chunk.
  * @param  hnand        Pointer to the NAND handle.
  * @param  ecc_program  ECC value programmed in OOB for the chunk.
  * @param  ecc_read     ECC value recomputed / read by the controller.
  * @param  p_ecc_error  Pointer to the result structure to be filled
  * @retval HAL_OK       If no error.
  * @retval HAL_ERROR    If the ECC pattern is inconsistent (uncorrectable error
  *                      or a correctable error has been decoded).
  */
static hal_status_t NAND_ECC_GetHammingErrorPositions(const hal_nand_handle_t *hnand, uint32_t ecc_program,
                                                      uint32_t ecc_read, hal_nand_ecc_error_t *p_ecc_error)
{
  uint32_t xored_ecc;
  uint32_t bit_position;
  uint32_t shifting;
  uint8_t  length;

  /* XOR the stored and recomputed ECC values to calculate the error syndrome bits */
  xored_ecc = ecc_program ^ ecc_read;
  if (xored_ecc == 0U)
  {
    p_ecc_error->error_count = 0U;
    return HAL_OK;
  }
  length = (uint8_t)(NAND_ECC_HAMMING_BASE_LENGTH + (2U * FMC_READ_FIELD(NAND_GET_INSTANCE(hnand)->PCR,
                                                                         FMC_PCR_ECCPS_Msk, FMC_PCR_ECCPS_Pos)));

  bit_position = 0U;
  shifting     = 1U;
  do
  {
    switch (xored_ecc % 4U)
    {
      case 1U:
        /* Parity bits only; no bit position update is needed. */
        break;
      case 2U:
        /* data bit error contribution */
        bit_position += shifting;
        break;
      default:
        /* Pattern is not coherent; the error is uncorrectable. */
        p_ecc_error->error_count = 0xFFU;
        return HAL_ERROR;
        break;
    }
    shifting   <<= 1U;
    xored_ecc >>= 2U;
    length     -= 2U;
  } while (length > 0U);

  p_ecc_error->error_count      = 1U;
  p_ecc_error->error_bit_position_1 = (uint16_t)bit_position;

  return HAL_ERROR;
}


/**
  * @brief  Poll for NAND hamming status.
  * @param  hnand     Pointer to NAND handle.
  * @retval HAL_ERROR NAND internal processing exceeded the timeout.
  * @retval HAL_OK    NAND internal processing is successfully completed.
  */
static hal_status_t NAND_PollForHammingStatus(hal_nand_handle_t *hnand)
{
  uint64_t timeout = (((uint64_t)NAND_HAMMING_TIMEOUT_MSEC * (uint64_t)HAL_RCC_GetSYSCLKFreq()) /
                      NAND_CYCLE_DIVIDER / FMC_MILLISECONDS_PER_SECOND);
  while ((FMC_NAND_IsECCHammingReady(NAND_GET_INSTANCE(hnand)) != 1U) && (timeout > 0U))
  {
    timeout--;
  }
  if (timeout == 0U)
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}

#endif /* USE_HAL_NAND_ECC */


/**
  * @}
  */
#endif /* HAL_NAND_MODULE_ENABLED */
#endif /* FMC_NAND_BK */
/**
  * @}
  */
