/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_nand.h
  * @brief   Header file of NAND HAL module.
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
#ifndef STM32H7PXX_HAL_NAND_H
#define STM32H7PXX_HAL_NAND_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_fmc_core.h"

/** @addtogroup STM32H7PXX_HAL_Driver
  * @{
  */

#if defined (FMC_NAND_BK)
/** @defgroup NAND NAND
  * @{
  */

/* Exported typedef --------------------------------------------------------------------------------------------------*/
/** @defgroup NAND_Exported_Types HAL NAND Types
  * @{
  */

/**
  * @brief NAND Instance Enumeration Definition
  */
typedef enum
{
  HAL_NAND1 = FMC_NAND_BASE, /*!< NAND instance */
} hal_nand_t;

/**
  * @brief NAND State Enumeration Definition
  */
typedef enum
{
  HAL_NAND_STATE_RESET             = 0U,           /*!< NAND not yet initialized                                      */
  HAL_NAND_STATE_INIT              = (1UL << 31U), /*!< NAND initialized but not yet configured                       */
  HAL_NAND_STATE_CONFIGURED        = (1UL << 30U), /*!< NAND initialized, FMC peripheral configured but not yet ready
                                                       to use                                                         */
  HAL_NAND_STATE_MEMORY_CONFIGURED = (1UL << 29U), /*!< NAND initialized, FMC, memory and timing configured but not yet
                                                       ready for use                                                  */
  HAL_NAND_STATE_IDLE              = (1UL << 28U), /*!< NAND initialized, FMC, memory, timing, partition configured,
                                                       NAND is enabled and ready to use                               */
  HAL_NAND_STATE_ACTIVE            = (1UL << 27U)  /*!< NAND internal processing is ongoing                           */
} hal_nand_state_t;


/**
  * @brief NAND device Status Enumeration Definition
  */
typedef enum
{
  HAL_NAND_DEVICE_STATE_BUSY  = 0x00000000UL, /*!< NAND internal processing is ongoing */
  HAL_NAND_DEVICE_STATE_ERROR = 0x00000001UL, /*!< NAND internal processing failure    */
  HAL_NAND_DEVICE_STATE_READY = 0x00000040UL  /*!< NAND device is ready                */
} hal_nand_device_status_t;

/**
  * @brief NAND Status Enumeration Definition
  */
typedef enum
{
  HAL_NAND_DISABLED = 0U, /*!< NAND is disabled */
  HAL_NAND_ENABLED  = 1U  /*!< NAND is enabled  */
} hal_nand_status_t;

/**
  * @brief NAND Wait Feature Status Enumeration Definition
  */
typedef enum
{
  HAL_NAND_WAIT_FEATURE_DISABLED = FMC_NAND_WAIT_FEATURE_DISABLED, /*!< NAND wait feature disabled */
  HAL_NAND_WAIT_FEATURE_ENABLED  = FMC_NAND_WAIT_FEATURE_ENABLED   /*!< NAND wait feature enabled  */
} hal_nand_wait_feature_status_t;

/**
  * @brief NAND device ONFI Compliant Status Enumeration Definition
  */
typedef enum
{
  HAL_NAND_IS_ONFI_COMPLIANT     = 0U, /*!< NAND device is ONFI compliant */
  HAL_NAND_IS_NOT_ONFI_COMPLIANT = 1U  /*!< NAND device is not ONFI compliant */
} hal_nand_onfi_status_t;

/**
  * @brief NAND Data width Enumeration Definition
  */
typedef enum
{
  HAL_NAND_DATA_BUS_WIDTH_8_BIT  = FMC_NAND_DATA_BUS_WIDTH_8_BIT, /*!< NAND data bus width 8 bits  */
  HAL_NAND_DATA_BUS_WIDTH_16_BIT = FMC_NAND_DATA_BUS_WIDTH_16_BIT /*!< NAND data bus width 16 bits */
} hal_nand_data_width_t;

#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
/**
  * @brief NAND ECC Algorithm mode Enumeration Definition
  */
typedef enum
{
  HAL_NAND_ECC_ALGO_NONE    = FMC_NAND_ECC_ALGO_NONE,   /*!< ECC computation disable        */
  HAL_NAND_ECC_ALGO_HAMMING = FMC_NAND_ECC_ALGO_HAMMING /*!< ECC Hamming computation enable */
} hal_nand_ecc_algorithm_t;
#endif /* USE_HAL_NAND_ECC */

#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
/**
  * @brief NAND Chunk Size Enumeration Definition
  */
typedef enum
{
  HAL_NAND_CHUNK_SIZE_256_BYTE  = FMC_NAND_CHUNK_SIZE_256_BYTE,  /*!< NAND chunk size 256 bytes  */
  HAL_NAND_CHUNK_SIZE_512_BYTE  = FMC_NAND_CHUNK_SIZE_512_BYTE,  /*!< NAND chunk size 512 bytes  */
  HAL_NAND_CHUNK_SIZE_1024_BYTE = FMC_NAND_CHUNK_SIZE_1024_BYTE, /*!< NAND chunk size 1024 bytes */
  HAL_NAND_CHUNK_SIZE_2048_BYTE = FMC_NAND_CHUNK_SIZE_2048_BYTE, /*!< NAND chunk size 2048 bytes */
  HAL_NAND_CHUNK_SIZE_4096_BYTE = FMC_NAND_CHUNK_SIZE_4096_BYTE, /*!< NAND chunk size 4096 bytes */
  HAL_NAND_CHUNK_SIZE_8192_BYTE = FMC_NAND_CHUNK_SIZE_8192_BYTE  /*!< NAND chunk size 8192 bytes */
} hal_nand_chunk_size_t;
#endif /* USE_HAL_NAND_ECC */

#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
/**
  * @brief NAND Extra Command Enumeration Definition
  */
typedef enum
{
  HAL_NAND_EXTRA_COMMAND_DISABLED = 0U, /*!< Extra command disabled */
  HAL_NAND_EXTRA_COMMAND_ENABLED  = 1U  /*!< Extra command enabled  */
} hal_nand_extra_command_status_t;
#endif /* USE_HAL_NAND_EXTRA_CMD */

#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
/**
  * @brief NAND ECC decoding results.
  * @note error_count is at most 1
  */
typedef struct
{
  uint16_t  error_bit_position_1; /*!< Error bit position for error number 1 */
  uint8_t   error_count;          /*!< Total number of detected errors       */
} hal_nand_ecc_error_t;
#endif /* USE_HAL_NAND_ECC */

/**
  * @brief  NAND Partition Parameters Structure Definition
  */
typedef struct
{
  uint32_t page_size_byte;       /*!< NAND memory page in bytes, excluding the spare area   */

  uint32_t spare_area_size_byte; /*!< NAND memory spare area size in bytes                  */

  uint32_t page_nbr_per_block;   /*!< NAND memory number of pages per block                 */

  uint32_t block_nbr_per_lun;    /*!< NAND memory number of blocks per logical unit (LUN)   */

  uint32_t lun_nbr_per_device;   /*!< NAND memory number of logical units (LUNs) per device */
} hal_nand_partition_config_t;

/**
  * @brief NAND Configuration Parameters Structure Definition
  */
typedef struct
{
  hal_nand_wait_feature_status_t wait_feature_status; /*!< Enables or disables the wait feature
                                                           for the NAND Memory device       */
#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
  hal_nand_ecc_algorithm_t       ecc_algorithm;       /*!< Defines the ECC algorithm        */
#endif /* USE_HAL_NAND_ECC */
#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
  hal_nand_chunk_size_t          chunk_size_byte;     /*!< Size of chunks in a page in bytes */
#endif /* USE_HAL_NAND_ECC */
} hal_nand_config_t;

/**
  * @brief NAND Timing Parameters Structure Definition
  */
typedef struct
{
  uint32_t setup_time_nsec; /*!< Defines the setup time in nanoseconds         */

  uint32_t wait_time_nsec;  /*!< Defines the wait time in nanoseconds          */

  uint32_t hold_time_nsec;  /*!< Defines the hold time in nanoseconds          */

  uint32_t hiz_time_nsec;   /*!< Defines the data bus HI-Z time in nanoseconds */
} hal_nand_timings_t;

/**
  * @brief NAND Memory Configuration Parameters Structure Definition
  */
typedef struct
{
  hal_nand_data_width_t           data_width;                 /*!< Specifies the external memory device width */
#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
  uint32_t                        ecc_offset_byte;            /*!< Spare area offset in bytes                 */
#endif /* USE_HAL_NAND_ECC */
#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
  hal_nand_extra_command_status_t extra_command_status;       /*!< NAND extra command needed for page reading mode. This
                                                                   parameter is mandatory for some NAND parts after the
                                                                   read command (NAND_CMD_AREA_TRUE1) and before DATA
                                                                   reading sequence. This parameter could be enabled
                                                                   or disabled. Please check the Read Mode sequence
                                                                   in the NAND device datasheet                */

  uint32_t                        extra_command_timeout_usec; /*!< NAND extra command timeout in us            */
#endif /* USE_HAL_NAND_EXTRA_CMD */
  uint32_t                        program_timeout_usec;       /*!< NAND program timeout in us                  */

  uint32_t                        erase_timeout_msec;         /*!< NAND erase timeout in ms                    */

  uint32_t                        tclr_setup_time_nsec;       /*!< Defines the delay between CLE low and RE low
                                                                   in nanoseconds                              */

  uint32_t                        tar_setup_time_nsec;        /*!< Defines the delay between ALE low and RE low
                                                                   in nanoseconds                              */

  hal_nand_timings_t              timing;                     /*!< Defines the timing of the NAND memory       */
} hal_nand_memory_config_t;

/**
  * @brief  NAND Memory Parameter Page Data Structure Definition
  */
typedef struct
{
  uint32_t page_signature;                                        /*!< NAND parameter signature page                  */

  uint32_t page_size_byte;                                        /*!< Size of page in bytes                          */

  uint32_t page_nbr_per_block;                                    /*!< Number of pages per block                      */

  uint32_t block_nbr_per_lun;                                     /*!< Number of blocks per LUN                       */

  uint16_t spare_area_size_byte;                                  /*!< Size of spare area in bytes (per page)         */

  uint16_t revision_nbr;                                          /*!< NAND revision number                           */

  uint16_t supported_features;                                    /*!< NAND supported features                        */

  uint16_t opt_commands;                                          /*!< NAND optional commands supported               */

  uint16_t bad_blocks_nbr;                                        /*!< Maximum bad blocks number per LUN              */

  uint16_t block_endurance;                                       /*!< Block endurance                                */

  uint16_t valid_block_endurance;                                 /*!< Block endurance for guaranteed valid blocks    */

  uint16_t sdr_timing_mode;                                       /*!< SDR timing mode                                */

  uint16_t vendor_revision_nbr;                                   /*!< Vendor specific revision number                */

  uint16_t integrity_crc;                                         /*!< Integrity CRC                                  */

  uint8_t  device_manufacturer[FMC_NAND_DEVICE_MANUFACTURER_LEN]; /*!< NAND device manufacturer                       */

  uint8_t  device_model[FMC_NAND_DEVICE_MODEL_LEN];               /*!< NAND device model                              */

  uint8_t  jedec_id;                                              /*!< NAND JEDEC manufacturer ID                     */

  uint8_t  training_commands;                                     /*!< NAND training commands supported               */

  uint8_t  lun_nbr_per_device;                                    /*!< Number of LUNs per device                      */

  uint8_t  addr_cycle_nbr;                                        /*!< Number of address cycles                       */

  uint8_t  bit_per_cell_nbr;                                      /*!< Number of bits per cell                        */

  uint8_t  valid_block_nbr;                                       /*!< Guaranteed valid blocks at beginning of target */

  uint8_t  program_page_nbr;                                      /*!< Number of programs per page                    */

  uint8_t  ecc_bits_nbr;                                          /*!< Number of bits ECC correctability              */

  uint8_t  plane_address_bits_nbr;                                /*!< Number of plane address bits                   */

  uint8_t  driver_strength;                                       /*!< Driver strength support                        */

  uint8_t  warmup_cycles;                                         /*!< NV-DDR2/3 warm-up cycles                       */
} hal_nand_param_config_t;

/**
  * @brief NAND Memory device ID Structure Definition
  */
typedef struct
{
  uint8_t manufacturer_code; /*!< Manufacturer code */

  uint8_t device_id;         /*!< Device ID         */

  uint8_t third_id;          /*!< Third device ID   */

  uint8_t fourth_id;         /*!< Fourth device ID  */
} hal_nand_id_t;

typedef struct hal_nand_handle_s hal_nand_handle_t; /*!< NAND Handle Structure type */

/**
  * @brief NAND Handle Structure Definition
  */
struct hal_nand_handle_s
{
  hal_nand_t                      instance;                 /*!< NAND instance                                      */

  volatile hal_nand_state_t       global_state;             /*!< NAND global state                                  */

  hal_nand_partition_config_t     partition_config;         /*!< NAND partition configuration                       */

#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
  uint16_t                        chunk_size_byte;          /*!< Size of chunks in a page in bytes                 */
#endif /* USE_HAL_NAND_ECC */
#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
  hal_nand_extra_command_status_t extra_command_status;       /*!< NAND extra command needed for page reading mode  */

  uint32_t                        extra_command_timeout_usec; /*!< NAND extra command timeout in usec               */
#endif /* USE_HAL_NAND_EXTRA_CMD */

  uint32_t                        program_timeout_usec;       /*!< NAND program timeout in usec                     */

  uint32_t                        erase_timeout_msec;         /*!< NAND erase timeout in msec                       */

#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
  hal_nand_ecc_algorithm_t        ecc_algorithm;              /*!< NAND ECC algorithm                               */

  uint32_t                        ecc_offset_byte;            /*!< ECC address offset in the spare area in bytes    */
#endif /* USE_HAL_NAND_ECC */

  uint32_t                        attribute_timing;           /*!< NAND timing for the last write access            */
#if defined(USE_HAL_NAND_USER_DATA) && (USE_HAL_NAND_USER_DATA == 1U)
  const void                      *p_user_data;                /*!< NAND user data pointer                            */
#endif /* USE_HAL_NAND_USER_DATA */
};
/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup NAND_Exported_Constants HAL NAND Constants
  * @{
  */
/** @defgroup NAND_Flag Flags
  * @{
  */
#define HAL_NAND_FLAG_FIFO_EMPTY                      FMC_NAND_FLAG_FIFO_EMPTY /*!<NAND FIFO empty flag */

/**
  * @}
  */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup NAND_Exported_Functions HAL NAND Functions
  * @{
  */

/** @defgroup NAND_Exported_Functions_Group1 Initialization, deinitialization and retrieve instance functions
  * @{
  */
hal_status_t HAL_NAND_Init(hal_nand_handle_t *hnand, hal_nand_t instance);
void HAL_NAND_DeInit(hal_nand_handle_t *hnand);
hal_nand_t HAL_NAND_GetInstance(const hal_nand_handle_t *hnand);
/**
  * @}
  */

/** @defgroup NAND_Exported_Functions_Group2 Configuration functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_NAND_SetConfig(hal_nand_handle_t *hnand, const hal_nand_config_t *p_config);
void HAL_NAND_GetConfig(const hal_nand_handle_t *hnand, hal_nand_config_t *p_config);

/* Memory configuration functions */
hal_status_t HAL_NAND_SetConfigMemory(hal_nand_handle_t *hnand, const hal_nand_memory_config_t *p_config);
void HAL_NAND_GetConfigMemory(const hal_nand_handle_t *hnand, hal_nand_memory_config_t *p_config);

/* Optional functions for cases where different timings are needed for the last write access */
hal_status_t HAL_NAND_SetLastWriteAccessTiming(hal_nand_handle_t *hnand, const hal_nand_timings_t *p_timings);
void HAL_NAND_GetLastWriteAccessTiming(const hal_nand_handle_t *hnand, hal_nand_timings_t *p_timings);

/* Partition configuration functions */
hal_status_t HAL_NAND_SetConfigPartition(hal_nand_handle_t *hnand, const hal_nand_partition_config_t *p_config);
hal_status_t HAL_NAND_SetConfigPartitionONFI(hal_nand_handle_t *hnand);
void HAL_NAND_GetConfigPartition(const hal_nand_handle_t *hnand, hal_nand_partition_config_t *p_config);

/* NAND start region address retrieval function */
uint32_t HAL_NAND_GetRegionBaseAddress(const hal_nand_handle_t *hnand);

/* Device timeout configuration functions */
#if defined (USE_HAL_NAND_EXTRA_CMD) && (USE_HAL_NAND_EXTRA_CMD == 1U)
hal_status_t HAL_NAND_SetExtraCmdTimeout(hal_nand_handle_t *hnand, uint32_t timeout_usec);
uint32_t     HAL_NAND_GetExtraCmdTimeout(const hal_nand_handle_t *hnand);
#endif /* USE_HAL_NAND_EXTRA_CMD */
hal_status_t HAL_NAND_SetPageProgramTimeout(hal_nand_handle_t *hnand, uint32_t timeout_usec);
uint32_t     HAL_NAND_GetPageProgramTimeout(const hal_nand_handle_t *hnand);
hal_status_t HAL_NAND_SetBlockEraseTimeout(hal_nand_handle_t *hnand, uint32_t timeout_msec);
uint32_t     HAL_NAND_GetBlockEraseTimeout(const hal_nand_handle_t *hnand);

/* Algorithm configuration function */
#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
hal_nand_ecc_algorithm_t  HAL_NAND_ECC_GetAlgo(const hal_nand_handle_t *hnand);
#endif /* USE_HAL_NAND_ECC */
/**
  * @}
  */

/** @defgroup NAND_Exported_Functions_Group3 I/O common operation functions
  * @{
  */
hal_status_t HAL_NAND_Reset(hal_nand_handle_t *hnand);
hal_status_t HAL_NAND_ReadID(hal_nand_handle_t *hnand, hal_nand_id_t *p_nand_id);
hal_status_t HAL_NAND_ONFIDetect(hal_nand_handle_t *hnand, hal_nand_onfi_status_t *p_onfi_status);
hal_status_t HAL_NAND_ONFIReadParameterPage(hal_nand_handle_t *hnand, hal_nand_param_config_t *p_param_config);
hal_nand_device_status_t HAL_NAND_ReadStatus(const hal_nand_handle_t *hnand);

/* NAND read & program & erase functions */
hal_status_t HAL_NAND_ReadPage(hal_nand_handle_t *hnand, uint32_t page_index, void *p_data, uint32_t size_byte);
hal_status_t HAL_NAND_ProgramPage(hal_nand_handle_t *hnand, uint32_t page_index, const void *p_data,
                                  uint32_t size_byte);
hal_status_t HAL_NAND_ReadPageSpareArea(hal_nand_handle_t *hnand, uint32_t page_index, void *p_data,
                                        uint32_t size_byte);
hal_status_t HAL_NAND_ProgramPageSpareArea(hal_nand_handle_t *hnand, uint32_t page_index, const void *p_data,
                                           uint32_t size_byte);
hal_status_t HAL_NAND_EraseBlock(hal_nand_handle_t *hnand, uint32_t block_index);
hal_status_t HAL_NAND_ReadInPage(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index,
                                 void *p_data, uint32_t size_byte);
hal_status_t HAL_NAND_ProgramInPage(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index,
                                    const void *p_data, uint32_t size_byte);
hal_status_t HAL_NAND_CopyBackRead(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index);
hal_status_t HAL_NAND_CopyBackProgram(hal_nand_handle_t *hnand, uint32_t page_index, uint16_t column_index);

/* NAND send command read & program functions */
hal_status_t HAL_NAND_SendReadPageCmd(hal_nand_handle_t *hnand, uint32_t page_index);
hal_status_t HAL_NAND_EndReadPage(hal_nand_handle_t *hnand);
hal_status_t HAL_NAND_SendProgramPageCmd(hal_nand_handle_t *hnand, uint32_t page_index);
hal_status_t HAL_NAND_EndProgramPage(hal_nand_handle_t *hnand);
/**
  * @}
  */

#if defined (USE_HAL_NAND_ECC) && (USE_HAL_NAND_ECC == 1U)
/** @defgroup NAND_Exported_Functions_Group4 I/O ECC operation functions
  * @{
  */
hal_status_t HAL_NAND_ECC_ProgramPage(hal_nand_handle_t *hnand, uint32_t page_index, const void *p_data,
                                      uint32_t size_byte);
hal_status_t HAL_NAND_ECC_ReadPage(hal_nand_handle_t *hnand, uint32_t page_index, void *p_data, uint32_t size_byte,
                                   void *p_ecc, uint32_t ecc_size_byte);
hal_status_t HAL_NAND_ECC_GetErrors(hal_nand_handle_t *hnand, uint32_t page_index, uint32_t chunk_index,
                                    const void *p_ecc, uint32_t ecc_size_byte, hal_nand_ecc_error_t *p_ecc_error);
/**
  * @}
  */
#endif /* USE_HAL_NAND_ECC */

/** @defgroup NAND_Exported_Functions_Group5 Control functions
  * @{
  */
hal_status_t HAL_NAND_Enable(hal_nand_handle_t *hnand);
hal_status_t HAL_NAND_Disable(hal_nand_handle_t *hnand);
hal_nand_status_t HAL_NAND_IsEnabled(const hal_nand_handle_t *hnand);
/**
  * @}
  */

#if defined(USE_HAL_NAND_USER_DATA) && (USE_HAL_NAND_USER_DATA == 1U)
/** @defgroup NAND_Exported_Functions_Group6 User data functions
  * @{
  */
void HAL_NAND_SetUserData(hal_nand_handle_t *hnand, const void *p_user_data);
const void *HAL_NAND_GetUserData(const hal_nand_handle_t *hnand);
/**
  * @}
  */
#endif /* USE_HAL_NAND_USER_DATA */

/** @defgroup NAND_Exported_Functions_Group7 Peripheral current frequency and state functions
  * @{
  */
uint32_t HAL_NAND_GetClockFreq(const hal_nand_handle_t *hnand);
hal_nand_state_t HAL_NAND_GetState(const hal_nand_handle_t *hnand);
/**
  * @}
  */

/** @defgroup NAND_Exported_Functions_Group8 Interrupt functions
  * @{
  */
/**
  * @brief  Check whether the selected flag is set or not.
  * @param  hnand  Pointer to a @ref hal_nand_handle_t structure.
  * @param  flag   Specifies the flag to check.
  *                This parameter can be any combination of the following values:
  *                  @arg HAL_NAND_FLAG_FIFO_EMPTY : FIFO empty flag.
  * @retval The state of flag (SET or RESET).
  */
__STATIC_INLINE uint32_t HAL_NAND_IsActiveFlag(const hal_nand_handle_t *hnand, uint32_t flag)
{
  return (uint32_t)FMC_NAND_IsActiveFlag((FMC_NAND_TypeDef *)((uint32_t)hnand->instance), flag);
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
#endif /* FMC_NAND_BK */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_HAL_NAND_H */

