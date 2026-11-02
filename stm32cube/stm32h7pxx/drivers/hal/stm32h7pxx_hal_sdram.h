/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_sdram.h
  * @brief   Header file of SDRAM HAL module.
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
#ifndef STM32H7PXX_HAL_SDRAM_H
#define STM32H7PXX_HAL_SDRAM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_fmc_core.h"

/** @addtogroup STM32H7PXX_HAL_Driver
  * @{
  */

#if defined (FMC_SDRAM_BK5)
/** @defgroup SDRAM SDRAM
  * @{
  */

/* Exported constants -----------------------------------------------------------------------------------------------*/
/** @defgroup SDRAM_Exported_Constants HAL SDRAM Constants
  * @{
  */

/** @defgroup SDRAM_Interrupts_Definitions SDRAM Interrupts Definitions
  * @{
  */
#define HAL_SDRAM_IT_REFRESH_ERROR FMC_SDRAM_IT_REFRESH_ERROR /*!< Interrupt enable for refresh error */
/**
  * @}
  */

/** @defgroup SDRAM_Flag_Definitions SDRAM Flag Definitions
  * @{
  */
#define HAL_SDRAM_FLAG_CLEAR_REFRESH_ERROR FMC_SDRAM_FLAG_CLEAR_REFRESH_ERROR /*!< Clear refresh error flag     */
#define HAL_SDRAM_FLAG_REFRESH_ERROR       FMC_SDRAM_FLAG_REFRESH_ERROR       /*!< Refresh error flag           */
/**
  * @}
  */

/**
  * @}
  */

/* Exported typedef --------------------------------------------------------------------------------------------------*/
/** @defgroup SDRAM_Exported_Types HAL SDRAM Types
  * @{
  */

/**
  * @brief HAL SDRAM Instance Definition
  */
typedef enum
{
  HAL_SDRAM = FMC_SDRAM_BASE, /*!< FMC SDRAM Instance */
} hal_sdram_t;

/**
  * @brief HAL SDRAM State Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_STATE_RESET      = 0UL,          /*!< SDRAM not yet initialized                                */
  HAL_SDRAM_STATE_INIT       = (1UL << 31U), /*!< SDRAM initialized but not yet configured                 */
  HAL_SDRAM_STATE_CONFIGURED = (1UL << 30U)  /*!< SDRAM initialized and common configured for both devices */
} hal_sdram_state_t;

/**
  * @brief HAL SDRAM Device State Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_DEVICE_STATE_RESET             = (1UL << 31U), /*!< SDRAM device not yet configured                 */
  HAL_SDRAM_DEVICE_STATE_MEMORY_CONFIGURED = (1UL << 30U), /*!< SDRAM device memory configured                  */
  HAL_SDRAM_DEVICE_STATE_MEMORY_IDLE       = (1UL << 29U), /*!< SDRAM device memory configured and ready to use */
  HAL_SDRAM_DEVICE_STATE_ACTIVE            = (1UL << 28U)  /*!< SDRAM device process is ongoing                 */
} hal_sdram_device_state_t;

/**
  * @brief SDRAM Device Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_DEVICE1 = FMC_SDRAM_DEVICE1, /*!< SDRAM Device 1 */
  HAL_SDRAM_DEVICE2 = FMC_SDRAM_DEVICE2  /*!< SDRAM Device 2 */
} hal_sdram_device_t;

/**
  * @brief SDRAM Write Protection Status Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_WR_NOT_PROTECTED = 0U, /*!< SDRAM Write access is not protected */
  HAL_SDRAM_WR_PROTECTED     = 1U  /*!< SDRAM Write access is protected     */
} hal_sdram_wr_protection_status_t;

/**
  * @brief SDRAM Clock Status Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_FMC_KER_CK_DISABLED  = 0U, /*!< SDRAM clock is disabled */
  HAL_SDRAM_FMC_KER_CK_ENABLED   = 1U  /*!< SDRAM clock is enabled  */
} hal_sdram_fmc_ker_ck_status_t;

/**
  * @brief SDRAM Read Pipe Delay Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_READ_PIPE_DELAY_0_CYCLE = FMC_SDRAM_READ_PIPE_DELAY_0_CYCLE, /*!< SDRAM read pipe delay 0 memory clock
                                                                              cycle  */
  HAL_SDRAM_READ_PIPE_DELAY_1_CYCLE = FMC_SDRAM_READ_PIPE_DELAY_1_CYCLE, /*!< SDRAM read pipe delay 1 memory clock
                                                                              cycle  */
  HAL_SDRAM_READ_PIPE_DELAY_2_CYCLE = FMC_SDRAM_READ_PIPE_DELAY_2_CYCLE  /*!< SDRAM read pipe delay 2 memory clock
                                                                              cycles */
} hal_sdram_read_pipe_delay_t;

/**
  * @brief SDRAM Kernel Clock Divider Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_FMC_KER_CK_DIV_2 = FMC_SDRAM_CLOCK_PERIOD_MULT_2, /*!< SDRAM SDCLK period = fmc_ker_ck divided by 2 */
  HAL_SDRAM_FMC_KER_CK_DIV_3 = FMC_SDRAM_CLOCK_PERIOD_MULT_3  /*!< SDRAM SDCLK period = fmc_ker_ck divided by 3 */
} hal_sdram_fmc_ker_ck_div_t;

/**
  * @brief SDRAM Read Burst Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_READ_BURST_DISABLE = FMC_SDRAM_READ_BURST_DISABLE, /*!< SDRAM read burst disable */
  HAL_SDRAM_READ_BURST_ENABLE  = FMC_SDRAM_READ_BURST_ENABLE   /*!< SDRAM read burst enable  */
} hal_sdram_read_burst_state_t;

/**
  * @brief SDRAM CAS Latency Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_CAS_LATENCY_1_CYCLE  = FMC_SDRAM_CAS_LATENCY_1_CYCLE, /*!< SDRAM CAS latency 1 memory clock cycle  */
  HAL_SDRAM_CAS_LATENCY_2_CYCLE  = FMC_SDRAM_CAS_LATENCY_2_CYCLE, /*!< SDRAM CAS latency 2 memory clock cycles */
  HAL_SDRAM_CAS_LATENCY_3_CYCLE  = FMC_SDRAM_CAS_LATENCY_3_CYCLE  /*!< SDRAM CAS latency 3 memory clock cycles */
} hal_sdram_cas_latency_t;

/**
  * @brief SDRAM Data Width Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_MEMORY_BUS_WIDTH_8_BIT  = FMC_SDRAM_MEM_BUS_WIDTH_8_BIT,  /*!< SDRAM bus width 8 bits  */
  HAL_SDRAM_MEMORY_BUS_WIDTH_16_BIT = FMC_SDRAM_MEM_BUS_WIDTH_16_BIT, /*!< SDRAM bus width 16 bits */
  HAL_SDRAM_MEMORY_BUS_WIDTH_32_BIT = FMC_SDRAM_MEM_BUS_WIDTH_32_BIT  /*!< SDRAM bus width 32 bits */
} hal_sdram_memory_bus_width_t;

/**
  * @brief SDRAM Internal Banks Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_INTERN_BANKS_NUMBER_2 = FMC_SDRAM_INTERN_BANKS_NUMBER_2, /*!< SDRAM 2 internal banks */
  HAL_SDRAM_INTERN_BANKS_NUMBER_4 = FMC_SDRAM_INTERN_BANKS_NUMBER_4  /*!< SDRAM 4 internal banks */
} hal_sdram_intern_banks_number_t;

/**
  * @brief SDRAM Row Address Width Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_ROW_ADDR_WIDTH_11_BIT = FMC_SDRAM_ROW_ADDR_WIDTH_11_BIT, /*!< SDRAM row address width 11 bits */
  HAL_SDRAM_ROW_ADDR_WIDTH_12_BIT = FMC_SDRAM_ROW_ADDR_WIDTH_12_BIT, /*!< SDRAM row address width 12 bits */
  HAL_SDRAM_ROW_ADDR_WIDTH_13_BIT = FMC_SDRAM_ROW_ADDR_WIDTH_13_BIT  /*!< SDRAM row address width 13 bits */
} hal_sdram_row_addr_width_t;

/**
  * @brief SDRAM Column Address Width Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_COLUMN_ADDR_WIDTH_8_BIT  = FMC_SDRAM_COLUMN_ADDR_WIDTH_8_BIT,  /*!< SDRAM column address width 8 bits  */
  HAL_SDRAM_COLUMN_ADDR_WIDTH_9_BIT  = FMC_SDRAM_COLUMN_ADDR_WIDTH_9_BIT,  /*!< SDRAM column address width 9 bits  */
  HAL_SDRAM_COLUMN_ADDR_WIDTH_10_BIT = FMC_SDRAM_COLUMN_ADDR_WIDTH_10_BIT, /*!< SDRAM column address width 10 bits */
  HAL_SDRAM_COLUMN_ADDR_WIDTH_11_BIT = FMC_SDRAM_COLUMN_ADDR_WIDTH_11_BIT  /*!< SDRAM column address width 11 bits */
} hal_sdram_column_addr_width_t;

/**
  * @brief SDRAM Command Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_COMMAND_NORMAL      = FMC_SDRAM_COMMAND_NORMAL,      /*!< SDRAM normal command             */
  HAL_SDRAM_COMMAND_CLK_ENABLE  = FMC_SDRAM_COMMAND_CLK_ENABLE,  /*!< SDRAM clock enable command       */
  HAL_SDRAM_COMMAND_PALL        = FMC_SDRAM_COMMAND_PALL,        /*!< SDRAM all bank precharge command */
  HAL_SDRAM_COMMAND_AUTOREFRESH = FMC_SDRAM_COMMAND_AUTOREFRESH, /*!< SDRAM auto refresh command       */
  HAL_SDRAM_COMMAND_LOAD        = FMC_SDRAM_COMMAND_LOAD,        /*!< SDRAM load command               */
  HAL_SDRAM_COMMAND_SELFREFRESH = FMC_SDRAM_COMMAND_SELFREFRESH, /*!< SDRAM self refresh command       */
  HAL_SDRAM_COMMAND_POWERDOWN   = FMC_SDRAM_COMMAND_POWERDOWN    /*!< SDRAM power down command         */
} hal_sdram_command_code_t;

/**
  * @brief SDRAM Device Mode Enumeration Definition
  */
typedef enum
{
  HAL_SDRAM_DEVICE_NORMAL_MODE  = FMC_SDRAM_DEVICE_NORMAL_MODE,  /*!< SDRAM device normal mode  */
  HAL_SDRAM_DEVICE_SELF_REFRESH = FMC_SDRAM_DEVICE_SELF_REFRESH, /*!< SDRAM device self refresh */
  HAL_SDRAM_DEVICE_POWER_DOWN   = FMC_SDRAM_DEVICE_POWER_DOWN    /*!< SDRAM device power down   */
} hal_sdram_device_mode_t;

/**
  * @brief SDRAM Region Remap Enumeration Definition
  * @note
  *  | FMC region      | HAL_SDRAM_DEVICE1_REGION5_NOR_SRAM_REGION1 | HAL_SDRAM_DEVICE1_REGION1_NOR_SRAM_REGION5 |
  *  |-----------------|--------------------------------------------|--------------------------------------------|
  *  | Memory region 1 | NOR/PSRAM/SRAM                             | SDRAM device 1                             |
  *  | Memory region 5 | SDRAM device 1                             | NOR/PSRAM/SRAM                             |
  *  | Memory region 6 | SDRAM device 2                             | SDRAM device 2                             |
  */
typedef enum
{
  HAL_SDRAM_DEVICE1_REGION5_NOR_SRAM_REGION1 = FMC_SDRAM_DEVICE1_REGION5_NOR_SRAM_REGION1, /*!< SDRAM device 1 remap to
                                                                                                region 5, NOR/PSRAM/SRAM
                                                                                                remap to region 1 */
  HAL_SDRAM_DEVICE1_REGION1_NOR_SRAM_REGION5 = FMC_SDRAM_DEVICE1_REGION1_NOR_SRAM_REGION5  /*!< SDRAM device 1 remap to
                                                                                                region 1, NOR/PSRAM/SRAM
                                                                                                remap to region 5 */
} hal_sdram_region_remap_t;

/**
  * @brief SDRAM Common Configuration Structure Definition
  */
typedef struct
{
  hal_sdram_read_pipe_delay_t read_pipe_delay;    /*!< Specifies the delay in system clock cycles on read
                                                      data path                                                 */
  hal_sdram_read_burst_state_t read_burst_state;  /*!< Specifies the read burst state                           */
  hal_sdram_fmc_ker_ck_div_t sdram_clock_divider; /*!< Specifies the SDRAM clock divider. SDRAM clock
                                                       is derivated from fmc_ker_ck.
                                                       SDCLK period = fmc_ker_ck / sdram_clock_divider          */
  uint32_t row_cycle_delay_nsec;                  /*!< Specifies the delay between the refresh command and
                                                      the activate command and the delay between two
                                                      consecutive refresh commands in nanoseconds               */
  uint32_t precharge_command_delay_nsec;          /*!< Specifies the delay between a precharge Command and
                                                    an other command in nanoseconds                             */
  uint32_t rows_number;                           /*!< Specifies the number of rows                             */
} hal_sdram_common_config_t;

/**
  * @brief SDRAM Memory Configuration Structure Definition
  */
typedef struct
{
  hal_sdram_memory_bus_width_t    memory_bus_width;     /*!< Specifies the external memory device width
                                                             multiplexed on the data bus or not in bits        */
  hal_sdram_intern_banks_number_t intern_banks_number;  /*!< Specifies the number of internal banks to use     */
  hal_sdram_row_addr_width_t      row_address_width;    /*!< Specifies the row address width in bits           */
  hal_sdram_column_addr_width_t   column_address_width; /*!< Specifies the column address width in bits        */
  hal_sdram_cas_latency_t         cas_latency;          /*!< Specifies the SDRAM CAS latency in number of memory
                                                             clock cycles                                      */
  uint32_t load_to_active_delay_nsec;                   /*!< Specifies the delay between a load mode register
                                                             command and an active or refresh command in nanoseconds  */
  uint32_t exit_self_refresh_delay_nsec;                /*!< Specifies the delay from releasing the self refresh
                                                             command to issuing the activate command in nanoseconds   */
  uint32_t self_refresh_time_nsec;                      /*!< Specifies the minimum self refresh period in nanoseconds */

  uint32_t write_recovery_time_nsec;                    /*!< Specifies the write recovery time in nanoseconds         */

  uint32_t activate_rd_wr_command_delay_nsec;           /*!< Specifies the delay between the activate command and
                                                             a Read/Write command in nanoseconds                      */
} hal_sdram_memory_config_t;

/**
  * @brief SDRAM Command Configuration Structure Definition
  */
typedef struct
{
  hal_sdram_command_code_t command;   /*!< Specifies the command issued to the SDRAM device               */
  uint32_t                 parameter; /*!< Specifies the command parameters, must be auto refresh number
                                           value for the @ref HAL_SDRAM_COMMAND_AUTOREFRESH command, must be the
                                           mode register value for the @ref HAL_SDRAM_COMMAND_LOAD and it is
                                           ignored for other commands                                     */
} hal_sdram_command_t;

typedef struct hal_sdram_handle_s hal_sdram_handle_t; /*!< SDRAM handle type Definition */

#if defined(USE_HAL_SDRAM_REGISTER_CALLBACKS) && (USE_HAL_SDRAM_REGISTER_CALLBACKS == 1U)
/**
  * @brief SDRAM Callback pointer definition
  */
typedef void (*hal_sdram_cb_t)(hal_sdram_handle_t *hsdram); /* Pointer to a SDRAM callback function */
#endif /* USE_HAL_SDRAM_REGISTER_CALLBACKS */

/**
  * @brief SDRAM Handle Structure Definition
  */
struct hal_sdram_handle_s
{
  hal_sdram_t                       instance;                           /*!< SDRAM instance                 */
  volatile hal_sdram_state_t        global_state;                       /*!< SDRAM global state             */
  volatile hal_sdram_device_state_t device_state[FMC_SDRAM_MAX_DEVICE]; /*!< SDRAM devices state            */
  hal_sdram_wr_protection_status_t  wr_protection_status[FMC_SDRAM_MAX_DEVICE]; /*!< SDRAM write
                                                                                         protection status  */
#if defined(USE_HAL_SDRAM_USER_DATA) && (USE_HAL_SDRAM_USER_DATA == 1U)
  const void                        *p_user_data;                       /*!< SDRAM user data pointer        */
#endif /* USE_HAL_SDRAM_USER_DATA */
  uint32_t                          rows_number;                        /*!< SDRAM rows number              */
  hal_sdram_fmc_ker_ck_div_t        sdram_clock_divider;                /*!< SDRAM last sdram clock divider */
#if defined(USE_HAL_SDRAM_REGISTER_CALLBACKS) && (USE_HAL_SDRAM_REGISTER_CALLBACKS == 1U)
  hal_sdram_cb_t                     p_refresh_error_cb;                /*!< SDRAM refresh error callback   */
#endif /* USE_HAL_SDRAM_REGISTER_CALLBACKS */
};
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup SDRAM_Exported_Functions HAL SDRAM Functions
  * @{
  */

/** @defgroup SDRAM_Exported_Functions_Group1 Initialization, de-initialization, retrieve instance, set and get region
              remap functions
  * @{
  */
hal_status_t HAL_SDRAM_Init(hal_sdram_handle_t *hsdram, hal_sdram_t instance);
void HAL_SDRAM_DeInit(hal_sdram_handle_t *hsdram);
hal_sdram_t HAL_SDRAM_GetInstance(const hal_sdram_handle_t *hsdram);
hal_status_t HAL_SDRAM_SetRegionRemap(const hal_sdram_handle_t *hsdram, hal_sdram_region_remap_t remap);
hal_sdram_region_remap_t HAL_SDRAM_GetRegionRemap(const hal_sdram_handle_t *hsdram);

/**
  * @}
  */

/** @defgroup SDRAM_Exported_Functions_Group2 Configuration and base address retrieve functions
  * @{
  */
/* Common configuration functions */
hal_status_t HAL_SDRAM_SetConfig(hal_sdram_handle_t *hsdram, const hal_sdram_common_config_t *p_config);
void HAL_SDRAM_GetConfig(const hal_sdram_handle_t *hsdram, hal_sdram_common_config_t *p_config);

/* Memory configuration functions */
hal_status_t HAL_SDRAM_SetConfigMemory(hal_sdram_handle_t *hsdram, hal_sdram_device_t device,
                                       const hal_sdram_memory_config_t *p_config);
void HAL_SDRAM_GetConfigMemory(const hal_sdram_handle_t *hsdram, hal_sdram_device_t device,
                               hal_sdram_memory_config_t *p_config);

/* Memory ready to be used with external memories */
hal_status_t HAL_SDRAM_CompleteInitSequence(hal_sdram_handle_t *hsdram, hal_sdram_device_t device);

/* SDRAM region base address retrieve function */
uint32_t HAL_SDRAM_GetDeviceBaseAddress(const hal_sdram_handle_t *hsdram, hal_sdram_device_t device);
/**
  * @}
  */

/** @defgroup SDRAM_Exported_Functions_Group3 Operation functions
  * @{
  */
/* Unitary command configuration for the refresh rate */
hal_status_t HAL_SDRAM_SetRefreshRate(hal_sdram_handle_t *hsdram, uint32_t refresh_period_ms);
uint32_t HAL_SDRAM_GetRefreshRate(const hal_sdram_handle_t *hsdram);

/* SDRAM Clock configuration functions */
hal_status_t HAL_SDRAM_EnableSDCLK(hal_sdram_handle_t *hsdram);
hal_status_t HAL_SDRAM_DisableSDCLK(const hal_sdram_handle_t *hsdram);
hal_sdram_fmc_ker_ck_status_t HAL_SDRAM_IsEnabledSDCLK(const hal_sdram_handle_t *hsdram);

/* Unitary get device mode function */
hal_sdram_device_mode_t HAL_SDRAM_GetDeviceMode(const hal_sdram_handle_t *hsdram, hal_sdram_device_t device);

/* Send command process function */
hal_status_t HAL_SDRAM_SendCommand(hal_sdram_handle_t *hsdram, hal_sdram_device_t device,
                                   hal_sdram_command_t *p_command_config, uint32_t timeout_ms);
/**
  * @}
  */

/** @defgroup SDRAM_Exported_Functions_Group4 Control functions
  * @{
  */
hal_status_t HAL_SDRAM_EnableWriteProtection(hal_sdram_handle_t *hsdram, hal_sdram_device_t device);
hal_status_t HAL_SDRAM_DisableWriteProtection(hal_sdram_handle_t *hsdram, hal_sdram_device_t device);
hal_sdram_wr_protection_status_t HAL_SDRAM_IsEnabledWriteProtection(const hal_sdram_handle_t *hsdram,
                                                                    hal_sdram_device_t device);
/**
  * @}
  */

#if defined(USE_HAL_SDRAM_USER_DATA) && (USE_HAL_SDRAM_USER_DATA == 1U)
/** @defgroup SDRAM_Exported_Functions_Group5 User data functions
  * @{
  */
void HAL_SDRAM_SetUserData(hal_sdram_handle_t *hsdram, const void *p_user_data);
const void *HAL_SDRAM_GetUserData(const hal_sdram_handle_t *hsdram);
/**
  * @}
  */
#endif /* USE_HAL_SDRAM_USER_DATA */

/** @defgroup SDRAM_Exported_Functions_Group6 Peripheral state, device state and kernel clock frequency
  * @{
  */
hal_sdram_state_t HAL_SDRAM_GetState(const hal_sdram_handle_t *hsdram);
hal_sdram_device_state_t HAL_SDRAM_GetDeviceState(const hal_sdram_handle_t *hsdram, hal_sdram_device_t device);
uint32_t HAL_SDRAM_GetClockFreq(const hal_sdram_handle_t *hsdram);
/**
  * @}
  */

/** @defgroup SDRAM_Exported_Functions_Group7 IRQHandler and Callback Functions
  * @{
  */
void HAL_SDRAM_IRQHandler(hal_sdram_handle_t *hsdram);
void HAL_SDRAM_RefreshErrorCallback(hal_sdram_handle_t *hsdram);

#if defined(USE_HAL_SDRAM_REGISTER_CALLBACKS) && (USE_HAL_SDRAM_REGISTER_CALLBACKS == 1U)
/* Register callbacks */
hal_status_t HAL_SDRAM_RegisterRefreshErrorCallback(hal_sdram_handle_t *hsdram, hal_sdram_cb_t p_callback);
#endif /* USE_HAL_SDRAM_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup SDRAM_Exported_Functions_Group8 Interrupt and Flag management
  * @{
This section provides SDRAM interrupts and flag management functions:
 - HAL_SDRAM_IsActiveFlag() : Used to whether the specified SDRAM flag is set.
 - HAL_SDRAM_ClearFlag()    : Used to clear the specified SDRAM flag.
 - HAL_SDRAM_EnableIT()     : Used to enable the specified SDRAM interrupt.
 - HAL_SDRAM_DisableIT()    : Used to disable the specified SDRAM interrupt.
 - HAL_SDRAM_IsEnabledIT()  : Used to check whether the specified SDRAM interrupt is set.
  */

/**
  * @brief  Check whether the specified SDRAM flag is set.
  * @param  hsdram Pointer to a hal_sdram_handle_t structure
  * @param  flag   The SDRAM check flag.
  *                This parameter must be one of the following values:
  *                @arg @ref HAL_SDRAM_FLAG_CLEAR_REFRESH_ERROR : Refresh error clear interruption flag
  *                @arg @ref HAL_SDRAM_FLAG_REFRESH_ERROR : Refresh error flag
  * @retval The state of SDRAM flag (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_SDRAM_IsActiveFlag(const hal_sdram_handle_t *hsdram, uint32_t flag)
{
  return (uint32_t)FMC_SDRAM_IsActiveFlag((FMC_SDRAM_TypeDef *)((uint32_t)hsdram->instance), flag);
}

/**
  * @brief Clear the specified SDRAM flags.
  * @param  hsdram Pointer to a hal_sdram_handle_t structure
  * @param  flag   The SDRAM clear flag
  *                This parameter must be one of the following values:
  *                @arg @ref HAL_SDRAM_FLAG_CLEAR_REFRESH_ERROR : Refresh error clear interruption flag
  */
__STATIC_INLINE void HAL_SDRAM_ClearFlag(hal_sdram_handle_t *hsdram, uint32_t flag)
{
  FMC_SDRAM_ClearFlag((FMC_SDRAM_TypeDef *)((uint32_t)hsdram->instance), flag);
}

/**
  * @brief Enable the refresh error SDRAM interrupts.
  * @param hsdram    Pointer to a hal_sdram_handle_t structure
  * @param it_source The SDRAM interrupt enable
  *                  This parameter can be the following value:
  *                  @arg @ref HAL_SDRAM_IT_REFRESH_ERROR : Refresh error interrupt enable for refresh error
  */
__STATIC_INLINE void HAL_SDRAM_EnableIT(hal_sdram_handle_t *hsdram, uint32_t it_source)
{
  FMC_SDRAM_EnableIT((FMC_SDRAM_TypeDef *)((uint32_t)hsdram->instance), it_source);
}

/**
  * @brief Disable the refresh error SDRAM interrupts.
  * @param hsdram    Pointer to a hal_sdram_handle_t structure
  * @param it_source The SDRAM interrupt disable
  *                  This parameter can be the following value:
  *                  @arg @ref HAL_SDRAM_IT_REFRESH_ERROR : Refresh error interrupt enable for refresh error
  */
__STATIC_INLINE void HAL_SDRAM_DisableIT(hal_sdram_handle_t *hsdram, uint32_t it_source)
{
  FMC_SDRAM_DisableIT((FMC_SDRAM_TypeDef *)((uint32_t)hsdram->instance), it_source);
}

/**
  * @brief  Check whether or not the specified SDRAM interrupt is enabled.
  * @param hsdram    Pointer to a hal_sdram_handle_t structure
  * @param it_source The SDRAM check interrupt
  *                  This parameter can be the following value:
  *                  @arg @ref HAL_SDRAM_IT_REFRESH_ERROR : Refresh error interrupt enable for refresh error
  * @retval The state of SDRAM interruption (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_SDRAM_IsEnabledIT(hal_sdram_handle_t *hsdram, uint32_t it_source)
{
  return (uint32_t)FMC_SDRAM_IsEnabledIT((FMC_SDRAM_TypeDef *)((uint32_t)hsdram->instance), it_source);
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
#endif /* FMC_SDRAM_BK5 */
/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_HAL_SDRAM_H */
