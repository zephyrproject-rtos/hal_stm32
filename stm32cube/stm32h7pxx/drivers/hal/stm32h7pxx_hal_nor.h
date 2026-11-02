/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_nor.h
  * @brief   Header file of NOR HAL module.
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
#ifndef STM32H7PXX_HAL_NOR_H
#define STM32H7PXX_HAL_NOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_fmc_core.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

#if defined (FMC_NORSRAM_BK1)
/** @defgroup NOR NOR
  * @{
  */

/* Exported typedef --------------------------------------------------------------------------------------------------*/
/** @defgroup NOR_Exported_Types HAL NOR Types
  * @{
  */
/**
  * @brief NOR Instance Enumeration Definition
  */
typedef enum
{
  HAL_NOR1 = FMC_NORSRAM1_SUBBANK1_BASE, /*!< NOR1 Bank1 */
  HAL_NOR2 = FMC_NORSRAM1_SUBBANK2_BASE, /*!< NOR2 Bank1 */
  HAL_NOR3 = FMC_NORSRAM1_SUBBANK3_BASE, /*!< NOR3 Bank1 */
  HAL_NOR4 = FMC_NORSRAM1_SUBBANK4_BASE  /*!< NOR4 Bank1 */
} hal_nor_t;

/**
  * @brief NOR State Enumeration Definition
  */
typedef enum
{
  HAL_NOR_STATE_RESET             = (0UL),        /*!< NOR not yet initialized                                        */
  HAL_NOR_STATE_INIT              = (1UL << 31U), /*!< NOR initialized but not yet configured                         */
  HAL_NOR_STATE_CONFIGURED        = (1UL << 30U), /*!< NOR initialized, FMC peripheral configured but not yet ready
                                                       for use                                                        */
  HAL_NOR_STATE_MEMORY_CONFIGURED = (1UL << 29U), /*!< NOR initialized, FMC, memory configured but not yet ready
                                                       for use                                                        */
  HAL_NOR_STATE_IDLE              = (1UL << 28U), /*!< NOR initialized, FMC, memory configured, NOR enabled and ready
                                                       to use                                                         */
  HAL_NOR_STATE_PROGRAM_ACTIVE    = (1UL << 27U), /*!< NOR internal program processing is ongoing                     */
  HAL_NOR_STATE_ERASE_ACTIVE      = (1UL << 26U), /*!< NOR internal erase processing is ongoing                       */
  HAL_NOR_STATE_READ_ACTIVE       = (1UL << 25U), /*!< NOR internal read processing is ongoing                        */
  HAL_NOR_STATE_PROGRAM_SUSPENDED = (1UL << 24U), /*!< NOR program is suspended                                       */
  HAL_NOR_STATE_ERASE_SUSPENDED   = (1UL << 23U), /*!< NOR erase is suspended                                         */
  HAL_NOR_STATE_FAULT             = (1UL << 22U)  /*!< NOR internal processing encountered an error                   */
} hal_nor_state_t;

/**
  * @brief NOR Status Enumeration Definition
  */
typedef enum
{
  HAL_NOR_DEVICE_STATE_SUCCESS = 0U, /*!< NOR internal processing successfully completed */
  HAL_NOR_DEVICE_STATE_ONGOING = 1U, /*!< NOR internal processing is ongoing             */
  HAL_NOR_DEVICE_STATE_ERROR   = 2U  /*!< NOR internal processing is failed              */
} hal_nor_device_status_t;

/**
  * @brief NOR Write Protection State Enumeration Definition
  */
typedef enum
{
  HAL_NOR_WR_PROTECTION_DISABLED = 0U, /*!< NOR Write access is not protected */
  HAL_NOR_WR_PROTECTION_ENABLED  = 1U  /*!< NOR Write access is protected     */
} hal_nor_wr_protection_status_t;

/**
  * @brief NOR Data Address Bus Multiplexing Enumeration Definition
  */
typedef enum
{
  HAL_NOR_MUX_DATA_ADDR_DISABLE = FMC_MUX_DATA_ADDR_DISABLE, /*!< NOR data/address non multiplexed */
  HAL_NOR_MUX_DATA_ADDR_ENABLE  = FMC_MUX_DATA_ADDR_ENABLE   /*!< NOR data/address multiplexed     */
} hal_nor_mux_data_addr_state_t;

/**
  * @brief NOR Write FIFO Enumeration Definition
  */
typedef enum
{
  HAL_NOR_WRITE_FIFO_DISABLE = FMC_WRITE_FIFO_DISABLE, /*!< NOR write FIFO disable */
  HAL_NOR_WRITE_FIFO_ENABLE  = FMC_WRITE_FIFO_ENABLE   /*!< NOR write FIFO enable  */
} hal_nor_write_fifo_state_t;

/**
  * @brief NOR Wait Signal Polarity Enumeration Definition
  */
typedef enum
{
  HAL_NOR_WAIT_SIGNAL_POLARITY_LOW  = FMC_WAIT_SIGNAL_POLARITY_LOW, /*!< NOR wait signal polarity low  */
  HAL_NOR_WAIT_SIGNAL_POLARITY_HIGH = FMC_WAIT_SIGNAL_POLARITY_HIGH /*!< NOR wait signal polarity high */
} hal_nor_wait_signal_polarity_t;

/**
  * @brief NOR Synchronous Wait Signal State Enumeration Definition
  */
typedef enum
{
  HAL_NOR_SYNC_WAIT_SIGNAL_DISABLE = FMC_SYNC_WAIT_SIGNAL_DISABLE, /*!< NOR synchronous wait signal disable */
  HAL_NOR_SYNC_WAIT_SIGNAL_ENABLE  = FMC_SYNC_WAIT_SIGNAL_ENABLE   /*!< NOR synchronous wait signal enable  */
} hal_nor_sync_wait_signal_state_t;

/**
  * @brief NOR Synchronous Wait Timing Configuration Enumeration Definition
  */
typedef enum
{
  HAL_NOR_WAIT_TIMING_CONFIG_BEFORE_WAITSTATE = FMC_WAIT_TIMING_CONFIG_BEFORE_WAITSTAT, /*!< NOR synchronous wait
                                                                                             timing before wait
                                                                                             state */
  HAL_NOR_WAIT_TIMING_CONFIG_DURING_WAITSTATE = FMC_WAIT_TIMING_CONFIG_DURING_WAITSTAT  /*!< NOR synchronous wait
                                                                                             timing during wait
                                                                                             state  */
} hal_nor_wait_timing_config_t;

/**
  * @brief NOR Asynchronous Wait Signal State Enumeration Definition
  */
typedef enum
{
  HAL_NOR_ASYNC_WAIT_SIGNAL_DISABLE = FMC_ASYNC_WAIT_SIGNAL_DISABLE, /*!< NOR asynchronous wait signal disable */
  HAL_NOR_ASYNC_WAIT_SIGNAL_ENABLE  = FMC_ASYNC_WAIT_SIGNAL_ENABLE   /*!< NOR asynchronous wait signal enable  */
} hal_nor_async_wait_signal_state_t;

/**
  * @brief NOR Continuous Clock Enumeration Definition
  */
typedef enum
{
  HAL_NOR_CONTINUOUS_CLOCK_SYNC_ONLY  = FMC_CONTINUOUS_CLOCK_SYNC_ONLY, /*!< NOR clock only in sync access      */
  HAL_NOR_CONTINUOUS_CLOCK_SYNC_ASYNC = FMC_CONTINUOUS_CLOCK_SYNC_ASYNC /*!< NOR clock in async and sync access */
} hal_nor_continuous_clock_t;

/**
  * @brief NOR Access Mode Enumeration Definition
  */
typedef enum
{
  HAL_NOR_ACCESS_MODE_B = FMC_ACCESS_MODE_B, /*!< NOR access mode B */
  HAL_NOR_ACCESS_MODE_C = FMC_ACCESS_MODE_C  /*!< NOR access mode C */
} hal_nor_access_mode_t;

/**
  * @brief NOR Region Remap Enumeration Definition
  * @note
  *  | FMC region      | HAL_NOR_SRAM_REGION1_SDRAM_DEVICE1_REGION5 | HAL_NOR_SRAM_REGION5_SDRAM_DEVICE1_REGION1 |
  *  |-----------------|--------------------------------------------|--------------------------------------------|
  *  | Memory region 1 | NOR/PSRAM/SRAM                             | SDRAM device 1                             |
  *  | Memory region 5 | SDRAM device 1                             | NOR/PSRAM/SRAM                             |
  *  | Memory region 6 | SDRAM device 2                             | SDRAM device 2                             |
  */
typedef enum
{
  HAL_NOR_SRAM_REGION1_SDRAM_DEVICE1_REGION5 = FMC_SDRAM_DEVICE1_REGION5_NOR_SRAM_REGION1, /*!< NOR/PSRAM/SRAM remap to
                                                                                                region 1, SDRAM device 1
                                                                                                remap to region 5 */
  HAL_NOR_SRAM_REGION5_SDRAM_DEVICE1_REGION1 = FMC_SDRAM_DEVICE1_REGION1_NOR_SRAM_REGION5  /*!< NOR/PSRAM/SRAM remap to
                                                                                                region 5, SDRAM device 1
                                                                                                remap to region 1 */
} hal_nor_region_remap_t;

/**
  * @brief NOR Configuration Parameters Structure Definition
  */
typedef struct
{
  hal_nor_write_fifo_state_t     write_fifo;           /*!< Enable or disable the write FIFO used by the FMC
                                                            controller                                       */
  hal_nor_wait_signal_polarity_t wait_signal_polarity; /*!< Specify the wait signal polarity, when asserting
                                                            the wait state management                        */
} hal_nor_config_t;

/**
  * @brief NOR Memory Configuration Parameters Structure Definition
  */
typedef struct
{
  hal_nor_mux_data_addr_state_t mux_data_addr; /*!< Specify whether the address and data values are multiplexed
                                                    on the data bus or not        */
} hal_nor_memory_config_t;

/**
  * @brief NOR Timing Parameters Structure Definition
  */
typedef struct
{
  uint32_t addr_setup_nsec; /*!< Define the duration of the address setup timing in nanoseconds */

  uint32_t addr_hold_nsec;  /*!< Define the duration of the address hold timing in nanoseconds  */

  uint32_t data_setup_nsec; /*!< Define the duration of the data setup timing in nanoseconds    */

} hal_nor_timings_t;

/**
  * @brief NOR Read Asynchronous And Write Asynchronous Structure Definition
  */
typedef struct
{
  hal_nor_async_wait_signal_state_t async_wait;          /*!< Enable or disable the asynchronous wait state       */

  hal_nor_timings_t                 access_timings;      /*!< Define the timings for both read and write access.
                                                              @note when separate timing configurations for read and
                                                              write transactions are needed, the
                                                              HAL_NOR_SetWrAsyncTimings() API must be called to set
                                                              the write timing parameters. In this case, this field
                                                              defines timing only for read access                 */

  uint32_t                          bus_turnaround_nsec; /*!< Define the duration of the bus turnaround phase to
                                                              configure in nanoseconds for both read and write
                                                              access.
                                                              @note when separate timing configurations for read and
                                                              write transactions are needed,the
                                                              HAL_NOR_SetWrAsyncTimings() API must be called to set
                                                              the write bus turnaround parameter. In this case, this
                                                              field defines bus turnaround only for read access   */
} hal_nor_rd_wr_async_timings_t;

/**
  * @brief NOR Synchronous Protocol Parameters Structure Definition
  */
typedef struct
{
  hal_nor_sync_wait_signal_state_t wait_signal_state;  /*!< Enable or disable the synchronous wait state              */

  hal_nor_wait_timing_config_t     wait_timing_config; /*!< Specify if the wait signal is asserted by the memory one
                                                            clock cycle before the wait state or during the wait
                                                            state                                                     */

  hal_nor_continuous_clock_t       continuous_clock;   /*!< Enable or disable the FMC clock output to external memory
                                                            devices                                                   */

  uint32_t                         clk_period_nsec;    /*!< Define the clock period of the output signal expressed in
                                                            nanoseconds.
                                                            @note If the continuous clock bit is set, the synchronous
                                                            memories connected to other banks than NOR bank 1 are
                                                            clocked by the same clock                                 */

  uint32_t                         data_latency_nsec;  /*!< Define the number of memory clock cycles to issue to the
                                                            memory before getting the first data                      */
} hal_nor_sync_protocol_config_t;

/**
  * @brief NOR Read Synchronous And Write Asynchronous Structure Definition
  */
typedef struct
{
  hal_nor_sync_protocol_config_t    sync_protocol;        /*!< Define the configuration for the synchronous access   */

  hal_nor_async_wait_signal_state_t async_wait;           /*!< Enable or disables the asynchronous wait state access */

  hal_nor_timings_t                 async_access_timings; /*!< Define the timing for the asynchronous access         */

  uint32_t                          bus_turnaround_nsec;  /*!< Define the duration of the bus turnaround phase to
                                                               configure in nanoseconds                              */
} hal_nor_sync_async_timings_t;


/**
  * @brief NOR Read and Write Asynchronous Memory Configuration Structure Definition
  */
typedef struct
{
  hal_nor_memory_config_t       memory;  /*!< Configure memory parameters                       */

  hal_nor_rd_wr_async_timings_t timings; /*!< Configure the read and write asynchronous timings */

} hal_nor_rd_wr_async_memory_config_t;

/**
  * @brief NOR Timing Write Asynchronous Parameters Structure Definition
  */
typedef struct
{
  hal_nor_timings_t     async_access_timings; /*!< Define the timings for write access                */

  uint32_t              bus_turnaround_nsec;  /*!< Define the duration of the bus turnaround
                                                   phase to configure in nanoseconds for write access */

  hal_nor_access_mode_t write_access_mode;    /*!< Define the write access mode                       */

  hal_nor_access_mode_t read_access_mode;     /*!< Define the read access mode                        */

} hal_nor_wr_async_timings_t;

/**
  * @brief NOR Read Synchronous Write Asynchronous Memory Configuration Structure Definition
  */
typedef struct
{
  hal_nor_memory_config_t      memory;  /*!< Configure memory parameters                        */

  hal_nor_sync_async_timings_t timings; /*!< Configure the synchronous and asynchronous timings */

} hal_nor_rd_sync_wr_async_memory_config_t;

/**
  * @brief NOR Command Set ID 0001 and ID 0003 Structure Definition
  */
typedef struct
{
  uint16_t device_manufacturer_code; /*!< Define the device's manufacturer code */

  uint16_t device_code;              /*!< Define the device's code              */
} hal_nor_cfi_0001_device_id_t, hal_nor_cfi_0003_device_id_t;

/**
  * @brief NOR Command Set ID 0002 Structure Definition
  */
typedef struct
{
  uint16_t device_manufacturer_code; /*!< Define the device's manufacturer code */

  uint16_t device_code_1;            /*!< Define the device's code 1            */

  uint16_t device_code_2;            /*!< Define the device's code 2            */

  uint16_t device_code_3;            /*!< Define the device's code 3            */

  uint16_t indicator_bits;           /*!< Define the indicator bits             */
} hal_nor_cfi_0002_device_id_t;

/**
  * @brief NOR CFI Device Info Structure Definition
  */
typedef struct
{
  uint32_t device_supply_min_mvolt;          /*!< Define the logic supply minimum voltage in millivolts          */

  uint32_t device_supply_max_mvolt;          /*!< Define the logic supply maximum voltage in millivolts          */

  uint32_t erase_program_supply_min_mvolt;   /*!< Define the minimum program/erase voltage in millivolts         */

  uint32_t erase_program_supply_max_mvolt;   /*!< Define the maximum program/erase voltage in millivolts         */

  uint32_t word_program_timeout_usec;        /*!< Define the typical single word program timeout in microseconds */

  uint32_t buffer_program_timeout_usec;      /*!< Define the typical full buffer write timeout in microseconds   */

  uint32_t block_erase_timeout_msec;         /*!< Define the typical block erase timeout in milliseconds         */

  uint32_t full_erase_timeout_msec;          /*!< Define the typical full chip erase timeout in milliseconds     */

  uint32_t max_word_program_timeout_usec;    /*!< Define the maximum single word program timeout in microseconds */

  uint32_t max_buffer_program_timeout_usec;  /*!< Define the maximum full buffer write timeout in microseconds   */

  uint32_t max_block_erase_timeout_msec;     /*!< Define the maximum block erase timeout in milliseconds         */

  uint32_t max_full_erase_timeout_msec;      /*!< Define the maximum full chip erase timeout in milliseconds     */

  uint32_t device_size_byte;                 /*!< Define the device size in bytes                                */

  uint32_t max_buffer_byte;                  /*!< Define the maximum number of bytes in buffer program           */

  uint16_t primary_command_set;              /*!< Define the ID code for vendor-specified algorithms             */

  uint16_t extended_primary_table_address;   /*!< Define the extended query table primary algorithm address      */

  uint16_t alternate_command_set;            /*!< Define the alternate vendor command set and control interface
                                                  ID code                                                        */

  uint16_t extended_secondary_table_address; /*!< Define the secondary algorithm extended query table address    */

  uint16_t device_interface_code;            /*!< Define the flash device interface code assignment              */

  uint8_t  query_unique_ascii[3];            /*!< Define the query unique ascii                                  */


  uint8_t  erase_block_region_nb;            /*!< Define the number of erase block regions within the device     */
} hal_nor_cfi_device_info_t;

/**
  * @brief NOR CFI Region Information Structure Definition
  */
typedef struct
{
  uint32_t block_size_byte; /*!< Define the block size in bytes                   */

  uint16_t block_nbr;       /*!< Define the number of identical size erase blocks */
} hal_nor_cfi_device_region_info_t;

/**
  * @brief NOR Handle Structure Definition
  */
typedef struct
{
  hal_nor_t                               instance;             /*!< NOR instance                */

  volatile hal_nor_state_t                global_state;         /*!< NOR global state            */

  volatile hal_nor_wr_protection_status_t wr_protection_status; /*!< NOR write protection status */

#if defined(USE_HAL_NOR_USER_DATA) && (USE_HAL_NOR_USER_DATA == 1U)
  const void                              *p_user_data;         /*!< NOR user data pointer       */
#endif /* USE_HAL_NOR_USER_DATA */
} hal_nor_handle_t;
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup NOR_Exported_Functions HAL NOR Functions
  * @{
  */

/** @defgroup NOR_Exported_Functions_Group1 Initialization, de-initialization, retrieve instance, set and get region
              remap functions
  * @{
  */
hal_status_t HAL_NOR_Init(hal_nor_handle_t *hnor, hal_nor_t instance);
void HAL_NOR_DeInit(hal_nor_handle_t *hnor);
hal_nor_t HAL_NOR_GetInstance(const hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_SetRegionRemap(const hal_nor_handle_t *hnor, hal_nor_region_remap_t remap);
hal_nor_region_remap_t HAL_NOR_GetRegionRemap(const hal_nor_handle_t *hnor);
/**
  * @}
  */

/** @defgroup NOR_Exported_Functions_Group2 Configuration and base address retrieve functions
  * @{
  */
/* Configuration functions */
hal_status_t HAL_NOR_SetConfig(hal_nor_handle_t *hnor, const hal_nor_config_t *p_config);
void HAL_NOR_GetConfig(const hal_nor_handle_t *hnor, hal_nor_config_t *p_config);

/* Asynchronous memory configuration functions */
hal_status_t HAL_NOR_SetConfigRdWrAsyncMemory(hal_nor_handle_t *hnor,
                                              const hal_nor_rd_wr_async_memory_config_t *p_config);
void HAL_NOR_GetConfigRdWrAsyncMemory(const hal_nor_handle_t *hnor, hal_nor_rd_wr_async_memory_config_t *p_config);

/* Optional functions when different timings for write transactions is needed */
hal_status_t HAL_NOR_SetWrAsyncTimings(hal_nor_handle_t *hnor, const hal_nor_wr_async_timings_t *p_timings);
void HAL_NOR_GetWrAsyncTimings(const hal_nor_handle_t *hnor, hal_nor_wr_async_timings_t *p_timings);

/* Synchronous/Asynchronous memory configuration functions */
hal_status_t HAL_NOR_SetConfigRdSyncWrAsyncMemory(hal_nor_handle_t *hnor,
                                                  const hal_nor_rd_sync_wr_async_memory_config_t *p_config);
void HAL_NOR_GetConfigRdSyncWrAsyncMemory(const hal_nor_handle_t *hnor,
                                          hal_nor_rd_sync_wr_async_memory_config_t *p_config);

/* Enable and disable memory functions */
hal_status_t HAL_NOR_EnableMemory(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_DisableMemory(hal_nor_handle_t *hnor);

/* NOR region base address retrieve function */
uint32_t HAL_NOR_GetRegionBaseAddress(const hal_nor_handle_t *hnor);
/**
  * @}
  */

/** @defgroup NOR_Exported_Functions_Group3 I/O common operation functions
  * @{
  */
hal_status_t HAL_NOR_CFI_ReadDeviceInfo(hal_nor_handle_t *hnor, hal_nor_cfi_device_info_t *p_device_info);
hal_status_t HAL_NOR_CFI_ReadDeviceRegionInfo(hal_nor_handle_t *hnor, uint8_t region_index,
                                              hal_nor_cfi_device_region_info_t *p_region_info);
/**
  * @}
  */

/** @defgroup NOR_Exported_Functions_Group4 I/O command set 0001 operation functions
  * @{
  */
hal_status_t HAL_NOR_CFI_0001_Reset(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0001_ReadArray(hal_nor_handle_t *hnor, uint32_t offset_byte, void *p_data, uint32_t size_byte);
hal_status_t HAL_NOR_CFI_0001_ReadDeviceIdentifier(hal_nor_handle_t *hnor, hal_nor_cfi_0001_device_id_t *p_nor_id);
hal_nor_device_status_t HAL_NOR_CFI_0001_ReadStatusRegister(hal_nor_handle_t *hnor, uint32_t offset_byte);
hal_status_t HAL_NOR_CFI_0001_ClearStatusRegister(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0001_Program(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0001_BufferedProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, const void *p_data,
                                              uint32_t size_byte, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0001_BufferedEnhancedFactoryProgram(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                             const void *p_data, uint32_t size_byte,
                                                             uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0001_BlockErase(hal_nor_handle_t *hnor, uint32_t block_offset_byte, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0001_ProgramSuspend(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0001_EraseSuspend(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0001_ProgramResume(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0001_EraseResume(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0001_BlockLock(hal_nor_handle_t *hnor, uint32_t block_offset_byte);
hal_status_t HAL_NOR_CFI_0001_BlockUnlock(hal_nor_handle_t *hnor, uint32_t block_offset_byte);
hal_status_t HAL_NOR_CFI_0001_BlockLockDown(hal_nor_handle_t *hnor, uint32_t block_offset_byte);
hal_status_t HAL_NOR_CFI_0001_ConfigureReadConfigurationRegister(hal_nor_handle_t *hnor, uint16_t data);
hal_status_t HAL_NOR_CFI_0001_BlockBlankCheck(hal_nor_handle_t *hnor, uint32_t block_offset_byte, uint32_t timeout_ms);
#if defined(USE_HAL_NOR_PROTECTION) && (USE_HAL_NOR_PROTECTION == 1U)
hal_status_t HAL_NOR_CFI_0001_ProgramProtectionRegister(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data);
hal_status_t HAL_NOR_CFI_0001_ProgramLockRegister(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data);
#endif /* USE_HAL_NOR_PROTECTION */
/**
  * @}
  */

/** @defgroup NOR_Exported_Functions_Group5 I/O command set 0002 operation functions
  * @{
  */
hal_status_t HAL_NOR_CFI_0002_Reset(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0002_Read(hal_nor_handle_t *hnor, uint32_t offset_byte, void *p_data, uint32_t size_byte);
hal_status_t HAL_NOR_CFI_0002_ReadDeviceIdentifier(hal_nor_handle_t *hnor, hal_nor_cfi_0002_device_id_t *p_nor_id);
hal_nor_device_status_t HAL_NOR_CFI_0002_ReadStatusRegister(hal_nor_handle_t *hnor, uint32_t offset_byte);
hal_status_t HAL_NOR_CFI_0002_UnlockBypass(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0002_UnlockBypassReset(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0002_Program(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_UnlockBypassProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data,
                                                  uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_DoubleDataProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, uint32_t data,
                                                uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_QuadrupleDataProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, uint32_t data_msb,
                                                   uint32_t data_lsb, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_BufferedProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, const void *p_data,
                                              uint32_t size_byte, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_EnhancedBufferedProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, const void *p_data,
                                                      uint32_t size_byte, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_UnlockBypassBufferedProgram(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                          const void *p_data, uint32_t size_byte, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_UnlockBypassEnhancedBufferedProgram(hal_nor_handle_t *hnor, uint32_t offset_byte,
                                                                  const void *p_data, uint32_t size_byte,
                                                                  uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_ProgramSuspend(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0002_EraseSuspend(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0002_ProgramResume(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0002_EraseResume(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0002_ChipErase(hal_nor_handle_t *hnor, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_UnlockBypassChipErase(hal_nor_handle_t *hnor, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_BlockErase(hal_nor_handle_t *hnor, uint32_t block_offset_byte, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_UnlockBypassBlockErase(hal_nor_handle_t *hnor, uint32_t block_offset_byte,
                                                     uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0002_BlockBlankCheck(hal_nor_handle_t *hnor, uint32_t block_offset_byte, uint32_t timeout_ms);
/**
  * @}
  */

/** @defgroup NOR_Exported_Functions_Group6 I/O command set 0003 operation functions
  * @{
  */
hal_status_t HAL_NOR_CFI_0003_Reset(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0003_ReadArray(hal_nor_handle_t *hnor, uint32_t offset_byte, void *p_data, uint32_t size_byte);
hal_status_t HAL_NOR_CFI_0003_ReadDeviceIdentifier(hal_nor_handle_t *hnor, hal_nor_cfi_0003_device_id_t *p_nor_id);
hal_nor_device_status_t HAL_NOR_CFI_0003_ReadStatusRegister(hal_nor_handle_t *hnor, uint32_t offset_byte);
hal_status_t HAL_NOR_CFI_0003_ClearStatusRegister(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0003_Program(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0003_DoubleDataProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, uint32_t data,
                                                uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0003_QuadrupleDataProgram(hal_nor_handle_t *hnor, uint32_t offset_byte, uint32_t data_msb,
                                                   uint32_t data_lsb, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0003_BlockErase(hal_nor_handle_t *hnor, uint32_t block_offset_byte, uint32_t timeout_ms);
hal_status_t HAL_NOR_CFI_0003_ProgramSuspend(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0003_EraseSuspend(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0003_ProgramResume(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0003_EraseResume(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_CFI_0003_BlockLock(hal_nor_handle_t *hnor, uint32_t block_offset_byte);
hal_status_t HAL_NOR_CFI_0003_BlockLockDown(hal_nor_handle_t *hnor, uint32_t block_offset_byte);
hal_status_t HAL_NOR_CFI_0003_BlockUnlock(hal_nor_handle_t *hnor, uint32_t block_offset_byte);
#if defined(USE_HAL_NOR_PROTECTION) && (USE_HAL_NOR_PROTECTION == 1U)
hal_status_t HAL_NOR_CFI_0003_ProgramProtectionRegister(hal_nor_handle_t *hnor, uint32_t offset_byte, uint16_t data);
#endif /* USE_HAL_NOR_PROTECTION */
/**
  * @}
  */

/** @defgroup NOR_Exported_Functions_Group7 Control functions
  * @{
  */
hal_status_t HAL_NOR_EnableWriteProtection(hal_nor_handle_t *hnor);
hal_status_t HAL_NOR_DisableWriteProtection(hal_nor_handle_t *hnor);
hal_nor_wr_protection_status_t HAL_NOR_IsEnabledWriteProtection(const hal_nor_handle_t *hnor);

/**
  * @}
  */

#if defined(USE_HAL_NOR_USER_DATA) && (USE_HAL_NOR_USER_DATA == 1U)
/** @defgroup NOR_Exported_Functions_Group8 User data functions
  * @{
  */
void HAL_NOR_SetUserData(hal_nor_handle_t *hnor, const void *p_user_data);
const void *HAL_NOR_GetUserData(const hal_nor_handle_t *hnor);
/**
  * @}
  */
#endif /* USE_HAL_NOR_USER_DATA */

/** @defgroup NOR_Exported_Functions_Group9 Peripheral state functions, clock frequency
  * @{
  */
uint32_t HAL_NOR_GetClockFreq(const hal_nor_handle_t *hnor);
hal_nor_state_t HAL_NOR_GetState(const hal_nor_handle_t *hnor);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* FMC_NORSRAM_BK1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7PXX_HAL_NOR_H */
